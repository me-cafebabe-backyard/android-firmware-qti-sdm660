#ifndef __TCSR_HWIO_H__
#define __TCSR_HWIO_H__
/*
===========================================================================
*/
/**
  @file tcsr_hwio.h
  @brief Auto-generated HWIO interface include file.

  This file contains HWIO register definitions for the following modules:
    TCSR_TCSR_REGS

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

  $Header: //components/rel/rpm.bf/1.8/core/power/mpm/hal/include/660/tcsr_hwio.h#2 $
  $DateTime: 2016/11/07 22:46:44 $
  $Author: pwbldsvc $

  ===========================================================================
*/

#include "msmhwiobase.h"



/*----------------------------------------------------------------------------
 * MODULE: TCSR_TCSR_REGS
 *--------------------------------------------------------------------------*/

#define TCSR_TCSR_REGS_REG_BASE                                                                                    (CORE_TOP_CSR_BASE      + 0x000c0000)

#define HWIO_TCSR_TIMEOUT_SLAVE_GLB_EN_ADDR                                                                        (TCSR_TCSR_REGS_REG_BASE      + 0x00000800)
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

#define HWIO_TCSR_XPU_NSEN_STATUS_ADDR                                                                             (TCSR_TCSR_REGS_REG_BASE      + 0x00000820)
#define HWIO_TCSR_XPU_NSEN_STATUS_RMSK                                                                                    0x3
#define HWIO_TCSR_XPU_NSEN_STATUS_IN          \
        in_dword_masked(HWIO_TCSR_XPU_NSEN_STATUS_ADDR, HWIO_TCSR_XPU_NSEN_STATUS_RMSK)
#define HWIO_TCSR_XPU_NSEN_STATUS_INM(m)      \
        in_dword_masked(HWIO_TCSR_XPU_NSEN_STATUS_ADDR, m)
#define HWIO_TCSR_XPU_NSEN_STATUS_REGS_XPU_NSEN_STATUS_BMSK                                                               0x2
#define HWIO_TCSR_XPU_NSEN_STATUS_REGS_XPU_NSEN_STATUS_SHFT                                                               0x1
#define HWIO_TCSR_XPU_NSEN_STATUS_MUTEX_XPU_NSEN_STATUS_BMSK                                                              0x1
#define HWIO_TCSR_XPU_NSEN_STATUS_MUTEX_XPU_NSEN_STATUS_SHFT                                                              0x0

#define HWIO_TCSR_XPU_VMIDEN_STATUS_ADDR                                                                           (TCSR_TCSR_REGS_REG_BASE      + 0x00000824)
#define HWIO_TCSR_XPU_VMIDEN_STATUS_RMSK                                                                                  0x3
#define HWIO_TCSR_XPU_VMIDEN_STATUS_IN          \
        in_dword_masked(HWIO_TCSR_XPU_VMIDEN_STATUS_ADDR, HWIO_TCSR_XPU_VMIDEN_STATUS_RMSK)
#define HWIO_TCSR_XPU_VMIDEN_STATUS_INM(m)      \
        in_dword_masked(HWIO_TCSR_XPU_VMIDEN_STATUS_ADDR, m)
#define HWIO_TCSR_XPU_VMIDEN_STATUS_REGS_XPU_VMIDEN_STATUS_BMSK                                                           0x2
#define HWIO_TCSR_XPU_VMIDEN_STATUS_REGS_XPU_VMIDEN_STATUS_SHFT                                                           0x1
#define HWIO_TCSR_XPU_VMIDEN_STATUS_MUTEX_XPU_VMIDEN_STATUS_BMSK                                                          0x1
#define HWIO_TCSR_XPU_VMIDEN_STATUS_MUTEX_XPU_VMIDEN_STATUS_SHFT                                                          0x0

#define HWIO_TCSR_XPU_MSAEN_STATUS_ADDR                                                                            (TCSR_TCSR_REGS_REG_BASE      + 0x00000828)
#define HWIO_TCSR_XPU_MSAEN_STATUS_RMSK                                                                                   0x3
#define HWIO_TCSR_XPU_MSAEN_STATUS_IN          \
        in_dword_masked(HWIO_TCSR_XPU_MSAEN_STATUS_ADDR, HWIO_TCSR_XPU_MSAEN_STATUS_RMSK)
#define HWIO_TCSR_XPU_MSAEN_STATUS_INM(m)      \
        in_dword_masked(HWIO_TCSR_XPU_MSAEN_STATUS_ADDR, m)
#define HWIO_TCSR_XPU_MSAEN_STATUS_REGS_XPU_MSAEN_STATUS_BMSK                                                             0x2
#define HWIO_TCSR_XPU_MSAEN_STATUS_REGS_XPU_MSAEN_STATUS_SHFT                                                             0x1
#define HWIO_TCSR_XPU_MSAEN_STATUS_MUTEX_XPU_MSAEN_STATUS_BMSK                                                            0x1
#define HWIO_TCSR_XPU_MSAEN_STATUS_MUTEX_XPU_MSAEN_STATUS_SHFT                                                            0x0

#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ADDR                                                                        (TCSR_TCSR_REGS_REG_BASE      + 0x00002000)
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_RMSK                                                                        0xffffffff
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_IN          \
        in_dword_masked(HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ADDR, HWIO_TCSR_SS_XPU_NON_SEC_INTR0_RMSK)
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_INM(m)      \
        in_dword_masked(HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ADDR, m)
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_RESERVE_31_BMSK                                                             0x80000000
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_RESERVE_31_SHFT                                                                   0x1f
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_BOOT_ROM_MSA_INTR_XPU_NON_SEC_INTR0_BMSK                                    0x40000000
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_BOOT_ROM_MSA_INTR_XPU_NON_SEC_INTR0_SHFT                                          0x1e
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_SDC1_ICE_XPU_NON_SEC_INTR0_BMSK                                             0x20000000
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_SDC1_ICE_XPU_NON_SEC_INTR0_SHFT                                                   0x1d
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_MSS_MPU_XPU_NON_SEC_INTR0_BMSK                                              0x10000000
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_MSS_MPU_XPU_NON_SEC_INTR0_SHFT                                                    0x1c
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_TLMM_CENTER_XPU_NON_SEC_INTR0_BMSK                                           0x8000000
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_TLMM_CENTER_XPU_NON_SEC_INTR0_SHFT                                                0x1b
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_SPDM_XPU_NON_SEC_INTR0_BMSK                                                  0x4000000
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_SPDM_XPU_NON_SEC_INTR0_SHFT                                                       0x1a
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_PMIC_ARB_XPU_NON_SEC_INTR0_BMSK                                              0x2000000
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_PMIC_ARB_XPU_NON_SEC_INTR0_SHFT                                                   0x19
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_UFS_ICE_XPU_NON_SEC_INTR0_BMSK                                               0x1000000
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_UFS_ICE_XPU_NON_SEC_INTR0_SHFT                                                    0x18
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_QHS_SNOC_XPU_XPU_NON_SEC_INTR0_BMSK                                           0x800000
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_QHS_SNOC_XPU_XPU_NON_SEC_INTR0_SHFT                                               0x17
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_QHS_QDSS_CFG_XPU_NON_SEC_INTR0_BMSK                                           0x400000
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_QHS_QDSS_CFG_XPU_NON_SEC_INTR0_SHFT                                               0x16
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_QHS_A2NOC_CFG_XPU_NON_SEC_INTR0_BMSK                                          0x200000
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_QHS_A2NOC_CFG_XPU_NON_SEC_INTR0_SHFT                                              0x15
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_QXM_SNOC_MS_XPU_NON_SEC_INTR0_BMSK                                            0x100000
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_QXM_SNOC_MS_XPU_NON_SEC_INTR0_SHFT                                                0x14
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_GCC_RPU_XPU_NON_SEC_INTR0_BMSK                                                 0x80000
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_GCC_RPU_XPU_NON_SEC_INTR0_SHFT                                                    0x13
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_BIMC_CH1_XPU_NON_SEC_INTR0_BMSK                                                0x40000
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_BIMC_CH1_XPU_NON_SEC_INTR0_SHFT                                                   0x12
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_BIMC_CH0_XPU_NON_SEC_INTR0_BMSK                                                0x20000
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_BIMC_CH0_XPU_NON_SEC_INTR0_SHFT                                                   0x11
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_BIMC_CFG_XPU_NON_SEC_INTR0_BMSK                                                0x10000
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_BIMC_CFG_XPU_NON_SEC_INTR0_SHFT                                                   0x10
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_QXM_MSS_NAV_CE_XPU_NON_SEC_INTR0_BMSK                                           0x8000
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_QXM_MSS_NAV_CE_XPU_NON_SEC_INTR0_SHFT                                              0xf
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_PIMEM_MPU_XPU_NON_SEC_INTR0_BMSK                                                0x4000
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_PIMEM_MPU_XPU_NON_SEC_INTR0_SHFT                                                   0xe
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_PIMEM_APU_XPU_NON_SEC_INTR0_BMSK                                                0x2000
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_PIMEM_APU_XPU_NON_SEC_INTR0_SHFT                                                   0xd
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_TURING_XPU_IRQ_XPU_NON_SEC_INTR0_BMSK                                           0x1000
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_TURING_XPU_IRQ_XPU_NON_SEC_INTR0_SHFT                                              0xc
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_LPASS_XPU_IRQ_APPS_1_XPU_NON_SEC_INTR0_BMSK                                      0x800
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_LPASS_XPU_IRQ_APPS_1_XPU_NON_SEC_INTR0_SHFT                                        0xb
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_LPASS_XPU_IRQ_APPS_SPARE_XPU_NON_SEC_INTR0_BMSK                                  0x400
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_LPASS_XPU_IRQ_APPS_SPARE_XPU_NON_SEC_INTR0_SHFT                                    0xa
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_SEC_CTRL_APU_XPU_NON_SEC_INTR0_BMSK                                              0x200
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_SEC_CTRL_APU_XPU_NON_SEC_INTR0_SHFT                                                0x9
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_DCC_XPU_NON_SEC_INTR0_BMSK                                                       0x100
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_DCC_XPU_NON_SEC_INTR0_SHFT                                                         0x8
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_OCIMEM_RPU_XPU_NON_SEC_INTR0_BMSK                                                 0x80
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_OCIMEM_RPU_XPU_NON_SEC_INTR0_SHFT                                                  0x7
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_CRYPTO0_BAM_XPU_NON_SEC_INTR0_BMSK                                                0x40
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_CRYPTO0_BAM_XPU_NON_SEC_INTR0_SHFT                                                 0x6
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_O_TCSR_MUTEX_XPU_NON_SEC_INTR0_BMSK                                               0x20
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_O_TCSR_MUTEX_XPU_NON_SEC_INTR0_SHFT                                                0x5
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_APSS_XPU_NON_SEC_INTR0_BMSK                                                       0x10
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_APSS_XPU_NON_SEC_INTR0_SHFT                                                        0x4
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_O_TCSR_REGS_XPU_NON_SEC_INTR0_BMSK                                                 0x8
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_O_TCSR_REGS_XPU_NON_SEC_INTR0_SHFT                                                 0x3
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_MMSS_NOC_XPU_NON_SEC_INTR0_BMSK                                                    0x4
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_MMSS_NOC_XPU_NON_SEC_INTR0_SHFT                                                    0x2
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_RESERVE_1_BMSK                                                                     0x2
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_RESERVE_1_SHFT                                                                     0x1
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_MMSS_QM_XPU_NON_SEC_INTR0_BMSK                                                     0x1
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_MMSS_QM_XPU_NON_SEC_INTR0_SHFT                                                     0x0

#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_ADDR                                                                        (TCSR_TCSR_REGS_REG_BASE      + 0x00002004)
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_RMSK                                                                           0x3ffff
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_IN          \
        in_dword_masked(HWIO_TCSR_SS_XPU_NON_SEC_INTR1_ADDR, HWIO_TCSR_SS_XPU_NON_SEC_INTR1_RMSK)
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_INM(m)      \
        in_dword_masked(HWIO_TCSR_SS_XPU_NON_SEC_INTR1_ADDR, m)
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_LPASS_IRQ_OUT_SECURITY_19_XPU_NON_SEC_INTR1_BMSK                               0x20000
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_LPASS_IRQ_OUT_SECURITY_19_XPU_NON_SEC_INTR1_SHFT                                  0x11
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_MMSS_XPU_MMSS_CC_XPU_NON_SEC_INTR1_BMSK                                        0x10000
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_MMSS_XPU_MMSS_CC_XPU_NON_SEC_INTR1_SHFT                                           0x10
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_TLMM_NORTH_XPU_NON_SEC_INTR1_BMSK                                               0x8000
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_TLMM_NORTH_XPU_NON_SEC_INTR1_SHFT                                                  0xf
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_SKL_XPU_XPU_NON_SEC_INTR1_BMSK                                                  0x4000
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_SKL_XPU_XPU_NON_SEC_INTR1_SHFT                                                     0xe
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_ANOC1_MPU_XPU_NON_SEC_INTR1_BMSK                                                0x2000
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_ANOC1_MPU_XPU_NON_SEC_INTR1_SHFT                                                   0xd
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_ANOC2_MPU_XPU_NON_SEC_INTR1_BMSK                                                0x1000
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_ANOC2_MPU_XPU_NON_SEC_INTR1_SHFT                                                   0xc
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_IPA_0_XPU_NON_SEC_INTR1_BMSK                                                     0x800
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_IPA_0_XPU_NON_SEC_INTR1_SHFT                                                       0xb
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_MSS_Q6_MPU_XPU_NON_SEC_INTR1_BMSK                                                0x400
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_MSS_Q6_MPU_XPU_NON_SEC_INTR1_SHFT                                                  0xa
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_RPM_MPU_XPU_NON_SEC_INTR1_BMSK                                                   0x200
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_RPM_MPU_XPU_NON_SEC_INTR1_SHFT                                                     0x9
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_LPASS_IRQ_OUT_SECURITY_9_XPU_NON_SEC_INTR1_BMSK                                  0x100
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_LPASS_IRQ_OUT_SECURITY_9_XPU_NON_SEC_INTR1_SHFT                                    0x8
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_MDSS_XPU_XPU_NON_SEC_INTR1_BMSK                                                   0x80
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_MDSS_XPU_XPU_NON_SEC_INTR1_SHFT                                                    0x7
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_QDSS_BAM_XPU_NON_SEC_INTR1_BMSK                                                   0x40
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_QDSS_BAM_XPU_NON_SEC_INTR1_SHFT                                                    0x6
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_MPM2_XPU_NON_SEC_INTR1_BMSK                                                       0x20
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_MPM2_XPU_NON_SEC_INTR1_SHFT                                                        0x5
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_DDR_REGS_CFG_XPU_NON_SEC_INTR1_BMSK                                               0x10
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_DDR_REGS_CFG_XPU_NON_SEC_INTR1_SHFT                                                0x4
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_TLMM_SOUTH_XPU_NON_SEC_INTR1_BMSK                                                  0x8
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_TLMM_SOUTH_XPU_NON_SEC_INTR1_SHFT                                                  0x3
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_PERIPH_SS_BLSP2_BLSP_BAM_XPU_NON_SEC_INTR1_BMSK                                    0x4
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_PERIPH_SS_BLSP2_BLSP_BAM_XPU_NON_SEC_INTR1_SHFT                                    0x2
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_PERIPH_SS_BLSP1_BLSP_BAM_XPU_NON_SEC_INTR1_BMSK                                    0x2
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_PERIPH_SS_BLSP1_BLSP_BAM_XPU_NON_SEC_INTR1_SHFT                                    0x1
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_OCIMEM_RPU_XPU_NON_SEC_INTR1_BMSK                                                  0x1
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_OCIMEM_RPU_XPU_NON_SEC_INTR1_SHFT                                                  0x0

#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_ADDR                                                                 (TCSR_TCSR_REGS_REG_BASE      + 0x00002040)
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_RMSK                                                                 0xffffffff
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_IN          \
        in_dword_masked(HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_ADDR, HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_RMSK)
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_INM(m)      \
        in_dword_masked(HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_ADDR, m)
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_OUT(v)      \
        out_dword(HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_ADDR,v)
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_ADDR,m,v,HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_IN)
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_RESERVE_31_BMSK                                                      0x80000000
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_RESERVE_31_SHFT                                                            0x1f
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_BOOT_ROM_MSA_INTR_XPU_NON_SEC_INTR0_ENABLE_BMSK                      0x40000000
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_BOOT_ROM_MSA_INTR_XPU_NON_SEC_INTR0_ENABLE_SHFT                            0x1e
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_SDC1_ICE_XPU_NON_SEC_INTR0_ENABLE_BMSK                               0x20000000
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_SDC1_ICE_XPU_NON_SEC_INTR0_ENABLE_SHFT                                     0x1d
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_MSS_MPU_XPU_NON_SEC_INTR0_ENABLE_BMSK                                0x10000000
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_MSS_MPU_XPU_NON_SEC_INTR0_ENABLE_SHFT                                      0x1c
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_TLMM_CENTER_XPU_NON_SEC_INTR0_ENABLE_BMSK                             0x8000000
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_TLMM_CENTER_XPU_NON_SEC_INTR0_ENABLE_SHFT                                  0x1b
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_SPDM_XPU_NON_SEC_INTR0_ENABLE_BMSK                                    0x4000000
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_SPDM_XPU_NON_SEC_INTR0_ENABLE_SHFT                                         0x1a
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_PMIC_ARB_XPU_NON_SEC_INTR0_ENABLE_BMSK                                0x2000000
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_PMIC_ARB_XPU_NON_SEC_INTR0_ENABLE_SHFT                                     0x19
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_UFS_ICE_XPU_NON_SEC_INTR0_ENABLE_BMSK                                 0x1000000
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_UFS_ICE_XPU_NON_SEC_INTR0_ENABLE_SHFT                                      0x18
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_QHS_SNOC_XPU_XPU_NON_SEC_INTR0_ENABLE_BMSK                             0x800000
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_QHS_SNOC_XPU_XPU_NON_SEC_INTR0_ENABLE_SHFT                                 0x17
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_QHS_QDSS_CFG_XPU_NON_SEC_INTR0_ENABLE_BMSK                             0x400000
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_QHS_QDSS_CFG_XPU_NON_SEC_INTR0_ENABLE_SHFT                                 0x16
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_QHS_A2NOC_CFG_XPU_NON_SEC_INTR0_ENABLE_BMSK                            0x200000
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_QHS_A2NOC_CFG_XPU_NON_SEC_INTR0_ENABLE_SHFT                                0x15
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_QXM_SNOC_MS_XPU_NON_SEC_INTR0_ENABLE_BMSK                              0x100000
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_QXM_SNOC_MS_XPU_NON_SEC_INTR0_ENABLE_SHFT                                  0x14
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_GCC_RPU_XPU_NON_SEC_INTR0_ENABLE_BMSK                                   0x80000
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_GCC_RPU_XPU_NON_SEC_INTR0_ENABLE_SHFT                                      0x13
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_BIMC_CH1_XPU_NON_SEC_INTR0_ENABLE_BMSK                                  0x40000
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_BIMC_CH1_XPU_NON_SEC_INTR0_ENABLE_SHFT                                     0x12
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_BIMC_CH0_XPU_NON_SEC_INTR0_ENABLE_BMSK                                  0x20000
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_BIMC_CH0_XPU_NON_SEC_INTR0_ENABLE_SHFT                                     0x11
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_BIMC_CFG_XPU_NON_SEC_INTR0_ENABLE_BMSK                                  0x10000
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_BIMC_CFG_XPU_NON_SEC_INTR0_ENABLE_SHFT                                     0x10
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_QXM_MSS_NAV_CE_XPU_NON_SEC_INTR0_ENABLE_BMSK                             0x8000
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_QXM_MSS_NAV_CE_XPU_NON_SEC_INTR0_ENABLE_SHFT                                0xf
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_PIMEM_MPU_XPU_NON_SEC_INTR0_ENABLE_BMSK                                  0x4000
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_PIMEM_MPU_XPU_NON_SEC_INTR0_ENABLE_SHFT                                     0xe
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_PIMEM_APU_XPU_NON_SEC_INTR0_ENABLE_BMSK                                  0x2000
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_PIMEM_APU_XPU_NON_SEC_INTR0_ENABLE_SHFT                                     0xd
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_TURING_XPU_IRQ_XPU_NON_SEC_INTR0_ENABLE_BMSK                             0x1000
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_TURING_XPU_IRQ_XPU_NON_SEC_INTR0_ENABLE_SHFT                                0xc
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_LPASS_XPU_IRQ_APPS_1_XPU_NON_SEC_INTR0_ENABLE_BMSK                        0x800
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_LPASS_XPU_IRQ_APPS_1_XPU_NON_SEC_INTR0_ENABLE_SHFT                          0xb
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_LPASS_XPU_IRQ_APPS_SPARE_XPU_NON_SEC_INTR0_ENABLE_BMSK                    0x400
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_LPASS_XPU_IRQ_APPS_SPARE_XPU_NON_SEC_INTR0_ENABLE_SHFT                      0xa
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_SEC_CTRL_APU_XPU_NON_SEC_INTR0_ENABLE_BMSK                                0x200
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_SEC_CTRL_APU_XPU_NON_SEC_INTR0_ENABLE_SHFT                                  0x9
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_DCC_XPU_NON_SEC_INTR0_ENABLE_BMSK                                         0x100
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_DCC_XPU_NON_SEC_INTR0_ENABLE_SHFT                                           0x8
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_OCIMEM_RPU_XPU_NON_SEC_INTR0_ENABLE_BMSK                                   0x80
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_OCIMEM_RPU_XPU_NON_SEC_INTR0_ENABLE_SHFT                                    0x7
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_CRYPTO0_BAM_XPU_NON_SEC_INTR0_ENABLE_BMSK                                  0x40
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_CRYPTO0_BAM_XPU_NON_SEC_INTR0_ENABLE_SHFT                                   0x6
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_O_TCSR_MUTEX_XPU_NON_SEC_INTR0_ENABLE_BMSK                                 0x20
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_O_TCSR_MUTEX_XPU_NON_SEC_INTR0_ENABLE_SHFT                                  0x5
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_APSS_XPU_NON_SEC_INTR0_ENABLE_BMSK                                         0x10
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_APSS_XPU_NON_SEC_INTR0_ENABLE_SHFT                                          0x4
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_O_TCSR_REGS_XPU_NON_SEC_INTR0_ENABLE_BMSK                                   0x8
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_O_TCSR_REGS_XPU_NON_SEC_INTR0_ENABLE_SHFT                                   0x3
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_MMSS_NOC_XPU_NON_SEC_INTR0_ENABLE_BMSK                                      0x4
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_MMSS_NOC_XPU_NON_SEC_INTR0_ENABLE_SHFT                                      0x2
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_RESERVE_1_BMSK                                                              0x2
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_RESERVE_1_SHFT                                                              0x1
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_MMSS_QM_XPU_NON_SEC_INTR0_ENABLE_BMSK                                       0x1
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR0_ENABLE_MMSS_QM_XPU_NON_SEC_INTR0_ENABLE_SHFT                                       0x0

#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_ENABLE_ADDR                                                                 (TCSR_TCSR_REGS_REG_BASE      + 0x00002044)
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_ENABLE_RMSK                                                                    0x3ffff
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_ENABLE_IN          \
        in_dword_masked(HWIO_TCSR_SS_XPU_NON_SEC_INTR1_ENABLE_ADDR, HWIO_TCSR_SS_XPU_NON_SEC_INTR1_ENABLE_RMSK)
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_ENABLE_INM(m)      \
        in_dword_masked(HWIO_TCSR_SS_XPU_NON_SEC_INTR1_ENABLE_ADDR, m)
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_ENABLE_OUT(v)      \
        out_dword(HWIO_TCSR_SS_XPU_NON_SEC_INTR1_ENABLE_ADDR,v)
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SS_XPU_NON_SEC_INTR1_ENABLE_ADDR,m,v,HWIO_TCSR_SS_XPU_NON_SEC_INTR1_ENABLE_IN)
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_ENABLE_LPASS_IRQ_OUT_SECURITY_19_XPU_NON_SEC_INTR1_ENABLE_BMSK                 0x20000
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_ENABLE_LPASS_IRQ_OUT_SECURITY_19_XPU_NON_SEC_INTR1_ENABLE_SHFT                    0x11
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_ENABLE_MMSS_XPU_MMSS_CC_XPU_NON_SEC_INTR1_ENABLE_BMSK                          0x10000
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_ENABLE_MMSS_XPU_MMSS_CC_XPU_NON_SEC_INTR1_ENABLE_SHFT                             0x10
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_ENABLE_TLMM_NORTH_XPU_NON_SEC_INTR1_ENABLE_BMSK                                 0x8000
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_ENABLE_TLMM_NORTH_XPU_NON_SEC_INTR1_ENABLE_SHFT                                    0xf
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_ENABLE_SKL_XPU_XPU_NON_SEC_INTR1_ENABLE_BMSK                                    0x4000
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_ENABLE_SKL_XPU_XPU_NON_SEC_INTR1_ENABLE_SHFT                                       0xe
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_ENABLE_ANOC1_MPU_XPU_NON_SEC_INTR1_ENABLE_BMSK                                  0x2000
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_ENABLE_ANOC1_MPU_XPU_NON_SEC_INTR1_ENABLE_SHFT                                     0xd
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_ENABLE_ANOC2_MPU_XPU_NON_SEC_INTR1_ENABLE_BMSK                                  0x1000
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_ENABLE_ANOC2_MPU_XPU_NON_SEC_INTR1_ENABLE_SHFT                                     0xc
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_ENABLE_IPA_0_XPU_NON_SEC_INTR1_ENABLE_BMSK                                       0x800
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_ENABLE_IPA_0_XPU_NON_SEC_INTR1_ENABLE_SHFT                                         0xb
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_ENABLE_MSS_Q6_MPU_XPU_NON_SEC_INTR1_ENABLE_BMSK                                  0x400
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_ENABLE_MSS_Q6_MPU_XPU_NON_SEC_INTR1_ENABLE_SHFT                                    0xa
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_ENABLE_RPM_MPU_XPU_NON_SEC_INTR1_ENABLE_BMSK                                     0x200
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_ENABLE_RPM_MPU_XPU_NON_SEC_INTR1_ENABLE_SHFT                                       0x9
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_ENABLE_LPASS_IRQ_OUT_SECURITY_9_XPU_NON_SEC_INTR1_ENABLE_BMSK                    0x100
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_ENABLE_LPASS_IRQ_OUT_SECURITY_9_XPU_NON_SEC_INTR1_ENABLE_SHFT                      0x8
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_ENABLE_MDSS_XPU_XPU_NON_SEC_INTR1_ENABLE_BMSK                                     0x80
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_ENABLE_MDSS_XPU_XPU_NON_SEC_INTR1_ENABLE_SHFT                                      0x7
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_ENABLE_QDSS_BAM_XPU_NON_SEC_INTR1_ENABLE_BMSK                                     0x40
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_ENABLE_QDSS_BAM_XPU_NON_SEC_INTR1_ENABLE_SHFT                                      0x6
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_ENABLE_MPM2_XPU_NON_SEC_INTR1_ENABLE_BMSK                                         0x20
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_ENABLE_MPM2_XPU_NON_SEC_INTR1_ENABLE_SHFT                                          0x5
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_ENABLE_DDR_REGS_CFG_XPU_NON_SEC_INTR1_ENABLE_BMSK                                 0x10
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_ENABLE_DDR_REGS_CFG_XPU_NON_SEC_INTR1_ENABLE_SHFT                                  0x4
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_ENABLE_TLMM_SOUTH_XPU_NON_SEC_INTR1_ENABLE_BMSK                                    0x8
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_ENABLE_TLMM_SOUTH_XPU_NON_SEC_INTR1_ENABLE_SHFT                                    0x3
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_ENABLE_PERIPH_SS_BLSP2_BLSP_BAM_XPU_NON_SEC_INTR1_ENABLE_BMSK                      0x4
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_ENABLE_PERIPH_SS_BLSP2_BLSP_BAM_XPU_NON_SEC_INTR1_ENABLE_SHFT                      0x2
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_ENABLE_PERIPH_SS_BLSP1_BLSP_BAM_XPU_NON_SEC_INTR1_ENABLE_BMSK                      0x2
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_ENABLE_PERIPH_SS_BLSP1_BLSP_BAM_XPU_NON_SEC_INTR1_ENABLE_SHFT                      0x1
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_ENABLE_OCIMEM_RPU_XPU_NON_SEC_INTR1_ENABLE_BMSK                                    0x1
#define HWIO_TCSR_SS_XPU_NON_SEC_INTR1_ENABLE_OCIMEM_RPU_XPU_NON_SEC_INTR1_ENABLE_SHFT                                    0x0

#define HWIO_TCSR_SS_XPU_SEC_INTR0_ADDR                                                                            (TCSR_TCSR_REGS_REG_BASE      + 0x00004000)
#define HWIO_TCSR_SS_XPU_SEC_INTR0_RMSK                                                                            0xffffffff
#define HWIO_TCSR_SS_XPU_SEC_INTR0_IN          \
        in_dword_masked(HWIO_TCSR_SS_XPU_SEC_INTR0_ADDR, HWIO_TCSR_SS_XPU_SEC_INTR0_RMSK)
#define HWIO_TCSR_SS_XPU_SEC_INTR0_INM(m)      \
        in_dword_masked(HWIO_TCSR_SS_XPU_SEC_INTR0_ADDR, m)
#define HWIO_TCSR_SS_XPU_SEC_INTR0_RESERVE_31_BMSK                                                                 0x80000000
#define HWIO_TCSR_SS_XPU_SEC_INTR0_RESERVE_31_SHFT                                                                       0x1f
#define HWIO_TCSR_SS_XPU_SEC_INTR0_BOOT_ROM_MSA_INTR_XPU_SEC_INTR0_BMSK                                            0x40000000
#define HWIO_TCSR_SS_XPU_SEC_INTR0_BOOT_ROM_MSA_INTR_XPU_SEC_INTR0_SHFT                                                  0x1e
#define HWIO_TCSR_SS_XPU_SEC_INTR0_SDC1_ICE_XPU_SEC_INTR0_BMSK                                                     0x20000000
#define HWIO_TCSR_SS_XPU_SEC_INTR0_SDC1_ICE_XPU_SEC_INTR0_SHFT                                                           0x1d
#define HWIO_TCSR_SS_XPU_SEC_INTR0_MSS_MPU_XPU_SEC_INTR0_BMSK                                                      0x10000000
#define HWIO_TCSR_SS_XPU_SEC_INTR0_MSS_MPU_XPU_SEC_INTR0_SHFT                                                            0x1c
#define HWIO_TCSR_SS_XPU_SEC_INTR0_TLMM_CENTER_XPU_SEC_INTR0_BMSK                                                   0x8000000
#define HWIO_TCSR_SS_XPU_SEC_INTR0_TLMM_CENTER_XPU_SEC_INTR0_SHFT                                                        0x1b
#define HWIO_TCSR_SS_XPU_SEC_INTR0_SPDM_XPU_SEC_INTR0_BMSK                                                          0x4000000
#define HWIO_TCSR_SS_XPU_SEC_INTR0_SPDM_XPU_SEC_INTR0_SHFT                                                               0x1a
#define HWIO_TCSR_SS_XPU_SEC_INTR0_PMIC_ARB_XPU_SEC_INTR0_BMSK                                                      0x2000000
#define HWIO_TCSR_SS_XPU_SEC_INTR0_PMIC_ARB_XPU_SEC_INTR0_SHFT                                                           0x19
#define HWIO_TCSR_SS_XPU_SEC_INTR0_UFS_ICE_XPU_SEC_INTR0_BMSK                                                       0x1000000
#define HWIO_TCSR_SS_XPU_SEC_INTR0_UFS_ICE_XPU_SEC_INTR0_SHFT                                                            0x18
#define HWIO_TCSR_SS_XPU_SEC_INTR0_QHS_SNOC_XPU_XPU_SEC_INTR0_BMSK                                                   0x800000
#define HWIO_TCSR_SS_XPU_SEC_INTR0_QHS_SNOC_XPU_XPU_SEC_INTR0_SHFT                                                       0x17
#define HWIO_TCSR_SS_XPU_SEC_INTR0_QHS_QDSS_CFG_XPU_SEC_INTR0_BMSK                                                   0x400000
#define HWIO_TCSR_SS_XPU_SEC_INTR0_QHS_QDSS_CFG_XPU_SEC_INTR0_SHFT                                                       0x16
#define HWIO_TCSR_SS_XPU_SEC_INTR0_QHS_A2NOC_CFG_XPU_SEC_INTR0_BMSK                                                  0x200000
#define HWIO_TCSR_SS_XPU_SEC_INTR0_QHS_A2NOC_CFG_XPU_SEC_INTR0_SHFT                                                      0x15
#define HWIO_TCSR_SS_XPU_SEC_INTR0_QXM_SNOC_MS_XPU_SEC_INTR0_BMSK                                                    0x100000
#define HWIO_TCSR_SS_XPU_SEC_INTR0_QXM_SNOC_MS_XPU_SEC_INTR0_SHFT                                                        0x14
#define HWIO_TCSR_SS_XPU_SEC_INTR0_GCC_RPU_XPU_SEC_INTR0_BMSK                                                         0x80000
#define HWIO_TCSR_SS_XPU_SEC_INTR0_GCC_RPU_XPU_SEC_INTR0_SHFT                                                            0x13
#define HWIO_TCSR_SS_XPU_SEC_INTR0_BIMC_CH1_XPU_SEC_INTR0_BMSK                                                        0x40000
#define HWIO_TCSR_SS_XPU_SEC_INTR0_BIMC_CH1_XPU_SEC_INTR0_SHFT                                                           0x12
#define HWIO_TCSR_SS_XPU_SEC_INTR0_BIMC_CH0_XPU_SEC_INTR0_BMSK                                                        0x20000
#define HWIO_TCSR_SS_XPU_SEC_INTR0_BIMC_CH0_XPU_SEC_INTR0_SHFT                                                           0x11
#define HWIO_TCSR_SS_XPU_SEC_INTR0_BIMC_CFG_XPU_SEC_INTR0_BMSK                                                        0x10000
#define HWIO_TCSR_SS_XPU_SEC_INTR0_BIMC_CFG_XPU_SEC_INTR0_SHFT                                                           0x10
#define HWIO_TCSR_SS_XPU_SEC_INTR0_QXM_MSS_NAV_CE_XPU_SEC_INTR0_BMSK                                                   0x8000
#define HWIO_TCSR_SS_XPU_SEC_INTR0_QXM_MSS_NAV_CE_XPU_SEC_INTR0_SHFT                                                      0xf
#define HWIO_TCSR_SS_XPU_SEC_INTR0_PIMEM_MPU_XPU_SEC_INTR0_BMSK                                                        0x4000
#define HWIO_TCSR_SS_XPU_SEC_INTR0_PIMEM_MPU_XPU_SEC_INTR0_SHFT                                                           0xe
#define HWIO_TCSR_SS_XPU_SEC_INTR0_PIMEM_APU_XPU_SEC_INTR0_BMSK                                                        0x2000
#define HWIO_TCSR_SS_XPU_SEC_INTR0_PIMEM_APU_XPU_SEC_INTR0_SHFT                                                           0xd
#define HWIO_TCSR_SS_XPU_SEC_INTR0_TURING_XPU_IRQ_XPU_SEC_INTR0_BMSK                                                   0x1000
#define HWIO_TCSR_SS_XPU_SEC_INTR0_TURING_XPU_IRQ_XPU_SEC_INTR0_SHFT                                                      0xc
#define HWIO_TCSR_SS_XPU_SEC_INTR0_LPASS_XPU_IRQ_0_XPU_SEC_INTR0_BMSK                                                   0x800
#define HWIO_TCSR_SS_XPU_SEC_INTR0_LPASS_XPU_IRQ_0_XPU_SEC_INTR0_SHFT                                                     0xb
#define HWIO_TCSR_SS_XPU_SEC_INTR0_LPASS_XPU_IRQ_SPARE_BMSK                                                             0x400
#define HWIO_TCSR_SS_XPU_SEC_INTR0_LPASS_XPU_IRQ_SPARE_SHFT                                                               0xa
#define HWIO_TCSR_SS_XPU_SEC_INTR0_SEC_CTRL_APU_XPU_SEC_INTR0_BMSK                                                      0x200
#define HWIO_TCSR_SS_XPU_SEC_INTR0_SEC_CTRL_APU_XPU_SEC_INTR0_SHFT                                                        0x9
#define HWIO_TCSR_SS_XPU_SEC_INTR0_DCC_XPU_SEC_INTR0_BMSK                                                               0x100
#define HWIO_TCSR_SS_XPU_SEC_INTR0_DCC_XPU_SEC_INTR0_SHFT                                                                 0x8
#define HWIO_TCSR_SS_XPU_SEC_INTR0_OCIMEM_RPU_XPU_SEC_INTR0_BMSK                                                         0x80
#define HWIO_TCSR_SS_XPU_SEC_INTR0_OCIMEM_RPU_XPU_SEC_INTR0_SHFT                                                          0x7
#define HWIO_TCSR_SS_XPU_SEC_INTR0_CRYPTO0_BAM_XPU_SEC_INTR0_BMSK                                                        0x40
#define HWIO_TCSR_SS_XPU_SEC_INTR0_CRYPTO0_BAM_XPU_SEC_INTR0_SHFT                                                         0x6
#define HWIO_TCSR_SS_XPU_SEC_INTR0_O_TCSR_MUTEX_XPU_SEC_INTR0_BMSK                                                       0x20
#define HWIO_TCSR_SS_XPU_SEC_INTR0_O_TCSR_MUTEX_XPU_SEC_INTR0_SHFT                                                        0x5
#define HWIO_TCSR_SS_XPU_SEC_INTR0_APSS_XPU_SEC_INTR0_BMSK                                                               0x10
#define HWIO_TCSR_SS_XPU_SEC_INTR0_APSS_XPU_SEC_INTR0_SHFT                                                                0x4
#define HWIO_TCSR_SS_XPU_SEC_INTR0_O_TCSR_REGS_XPU_SEC_INTR0_BMSK                                                         0x8
#define HWIO_TCSR_SS_XPU_SEC_INTR0_O_TCSR_REGS_XPU_SEC_INTR0_SHFT                                                         0x3
#define HWIO_TCSR_SS_XPU_SEC_INTR0_MMSS_NOC_XPU_SEC_INTR0_BMSK                                                            0x4
#define HWIO_TCSR_SS_XPU_SEC_INTR0_MMSS_NOC_XPU_SEC_INTR0_SHFT                                                            0x2
#define HWIO_TCSR_SS_XPU_SEC_INTR0_RESERVE_1_BMSK                                                                         0x2
#define HWIO_TCSR_SS_XPU_SEC_INTR0_RESERVE_1_SHFT                                                                         0x1
#define HWIO_TCSR_SS_XPU_SEC_INTR0_MMSS_QM_XPU_SEC_INTR0_BMSK                                                             0x1
#define HWIO_TCSR_SS_XPU_SEC_INTR0_MMSS_QM_XPU_SEC_INTR0_SHFT                                                             0x0

#define HWIO_TCSR_SS_XPU_SEC_INTR1_ADDR                                                                            (TCSR_TCSR_REGS_REG_BASE      + 0x00004004)
#define HWIO_TCSR_SS_XPU_SEC_INTR1_RMSK                                                                               0x3ffff
#define HWIO_TCSR_SS_XPU_SEC_INTR1_IN          \
        in_dword_masked(HWIO_TCSR_SS_XPU_SEC_INTR1_ADDR, HWIO_TCSR_SS_XPU_SEC_INTR1_RMSK)
#define HWIO_TCSR_SS_XPU_SEC_INTR1_INM(m)      \
        in_dword_masked(HWIO_TCSR_SS_XPU_SEC_INTR1_ADDR, m)
#define HWIO_TCSR_SS_XPU_SEC_INTR1_LPASS_IRQ_OUT_SECURITY_18_XPU_SEC_INTR1_BMSK                                       0x20000
#define HWIO_TCSR_SS_XPU_SEC_INTR1_LPASS_IRQ_OUT_SECURITY_18_XPU_SEC_INTR1_SHFT                                          0x11
#define HWIO_TCSR_SS_XPU_SEC_INTR1_MMSS_XPU_MMSS_CC_XPU_SEC_INTR1_BMSK                                                0x10000
#define HWIO_TCSR_SS_XPU_SEC_INTR1_MMSS_XPU_MMSS_CC_XPU_SEC_INTR1_SHFT                                                   0x10
#define HWIO_TCSR_SS_XPU_SEC_INTR1_TLMM_NORTH_XPU_SEC_INTR1_BMSK                                                       0x8000
#define HWIO_TCSR_SS_XPU_SEC_INTR1_TLMM_NORTH_XPU_SEC_INTR1_SHFT                                                          0xf
#define HWIO_TCSR_SS_XPU_SEC_INTR1_SKL_XPU_XPU_SEC_INTR1_BMSK                                                          0x4000
#define HWIO_TCSR_SS_XPU_SEC_INTR1_SKL_XPU_XPU_SEC_INTR1_SHFT                                                             0xe
#define HWIO_TCSR_SS_XPU_SEC_INTR1_ANOC1_MPU_XPU_SEC_INTR1_BMSK                                                        0x2000
#define HWIO_TCSR_SS_XPU_SEC_INTR1_ANOC1_MPU_XPU_SEC_INTR1_SHFT                                                           0xd
#define HWIO_TCSR_SS_XPU_SEC_INTR1_ANOC2_MPU_XPU_SEC_INTR1_BMSK                                                        0x1000
#define HWIO_TCSR_SS_XPU_SEC_INTR1_ANOC2_MPU_XPU_SEC_INTR1_SHFT                                                           0xc
#define HWIO_TCSR_SS_XPU_SEC_INTR1_IPA_0_XPU_SEC_INTR1_BMSK                                                             0x800
#define HWIO_TCSR_SS_XPU_SEC_INTR1_IPA_0_XPU_SEC_INTR1_SHFT                                                               0xb
#define HWIO_TCSR_SS_XPU_SEC_INTR1_MSS_Q6_MPU_XPU_SEC_INTR1_BMSK                                                        0x400
#define HWIO_TCSR_SS_XPU_SEC_INTR1_MSS_Q6_MPU_XPU_SEC_INTR1_SHFT                                                          0xa
#define HWIO_TCSR_SS_XPU_SEC_INTR1_RPM_MPU_XPU_SEC_INTR1_BMSK                                                           0x200
#define HWIO_TCSR_SS_XPU_SEC_INTR1_RPM_MPU_XPU_SEC_INTR1_SHFT                                                             0x9
#define HWIO_TCSR_SS_XPU_SEC_INTR1_LPASS_IRQ_OUT_SECURITY_8_XPU_SEC_INTR1_BMSK                                          0x100
#define HWIO_TCSR_SS_XPU_SEC_INTR1_LPASS_IRQ_OUT_SECURITY_8_XPU_SEC_INTR1_SHFT                                            0x8
#define HWIO_TCSR_SS_XPU_SEC_INTR1_MDSS_XPU_XPU_SEC_INTR1_BMSK                                                           0x80
#define HWIO_TCSR_SS_XPU_SEC_INTR1_MDSS_XPU_XPU_SEC_INTR1_SHFT                                                            0x7
#define HWIO_TCSR_SS_XPU_SEC_INTR1_QDSS_BAM_XPU_SEC_INTR1_BMSK                                                           0x40
#define HWIO_TCSR_SS_XPU_SEC_INTR1_QDSS_BAM_XPU_SEC_INTR1_SHFT                                                            0x6
#define HWIO_TCSR_SS_XPU_SEC_INTR1_MPM2_XPU_SEC_INTR1_BMSK                                                               0x20
#define HWIO_TCSR_SS_XPU_SEC_INTR1_MPM2_XPU_SEC_INTR1_SHFT                                                                0x5
#define HWIO_TCSR_SS_XPU_SEC_INTR1_DDR_REGS_CFG_XPU_SEC_INTR1_BMSK                                                       0x10
#define HWIO_TCSR_SS_XPU_SEC_INTR1_DDR_REGS_CFG_XPU_SEC_INTR1_SHFT                                                        0x4
#define HWIO_TCSR_SS_XPU_SEC_INTR1_TLMM_SOUTH_XPU_SEC_INTR1_BMSK                                                          0x8
#define HWIO_TCSR_SS_XPU_SEC_INTR1_TLMM_SOUTH_XPU_SEC_INTR1_SHFT                                                          0x3
#define HWIO_TCSR_SS_XPU_SEC_INTR1_PERIPH_SS_BLSP2_BLSP_BAM_XPU_SEC_INTR1_BMSK                                            0x4
#define HWIO_TCSR_SS_XPU_SEC_INTR1_PERIPH_SS_BLSP2_BLSP_BAM_XPU_SEC_INTR1_SHFT                                            0x2
#define HWIO_TCSR_SS_XPU_SEC_INTR1_PERIPH_SS_BLSP1_BLSP_BAM_XPU_SEC_INTR1_BMSK                                            0x2
#define HWIO_TCSR_SS_XPU_SEC_INTR1_PERIPH_SS_BLSP1_BLSP_BAM_XPU_SEC_INTR1_SHFT                                            0x1
#define HWIO_TCSR_SS_XPU_SEC_INTR1_OCIMEM_RPU_XPU_SEC_INTR1_BMSK                                                          0x1
#define HWIO_TCSR_SS_XPU_SEC_INTR1_OCIMEM_RPU_XPU_SEC_INTR1_SHFT                                                          0x0

#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_ADDR                                                                     (TCSR_TCSR_REGS_REG_BASE      + 0x00004040)
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_RMSK                                                                     0xffffffff
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_IN          \
        in_dword_masked(HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_ADDR, HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_RMSK)
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_INM(m)      \
        in_dword_masked(HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_ADDR, m)
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_OUT(v)      \
        out_dword(HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_ADDR,v)
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_ADDR,m,v,HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_IN)
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_RESERVE_31_BMSK                                                          0x80000000
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_RESERVE_31_SHFT                                                                0x1f
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_BOOT_ROM_MSA_INTR_XPU_SEC_INTR0_ENABLE_BMSK                              0x40000000
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_BOOT_ROM_MSA_INTR_XPU_SEC_INTR0_ENABLE_SHFT                                    0x1e
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_SDC1_ICE_XPU_SEC_INTR0_ENABLE_BMSK                                       0x20000000
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_SDC1_ICE_XPU_SEC_INTR0_ENABLE_SHFT                                             0x1d
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_MSS_MPU_XPU_SEC_INTR0_ENABLE_BMSK                                        0x10000000
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_MSS_MPU_XPU_SEC_INTR0_ENABLE_SHFT                                              0x1c
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_TLMM_CENTER_XPU_SEC_INTR0_ENABLE_BMSK                                     0x8000000
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_TLMM_CENTER_XPU_SEC_INTR0_ENABLE_SHFT                                          0x1b
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_SPDM_XPU_SEC_INTR0_ENABLE_BMSK                                            0x4000000
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_SPDM_XPU_SEC_INTR0_ENABLE_SHFT                                                 0x1a
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_PMIC_ARB_XPU_SEC_INTR0_ENABLE_BMSK                                        0x2000000
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_PMIC_ARB_XPU_SEC_INTR0_ENABLE_SHFT                                             0x19
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_UFS_ICE_XPU_SEC_INTR0_ENABLE_BMSK                                         0x1000000
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_UFS_ICE_XPU_SEC_INTR0_ENABLE_SHFT                                              0x18
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_QHS_SNOC_XPU_XPU_SEC_INTR0_ENABLE_BMSK                                     0x800000
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_QHS_SNOC_XPU_XPU_SEC_INTR0_ENABLE_SHFT                                         0x17
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_QHS_QDSS_CFG_XPU_SEC_INTR0_ENABLE_BMSK                                     0x400000
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_QHS_QDSS_CFG_XPU_SEC_INTR0_ENABLE_SHFT                                         0x16
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_QHS_A2NOC_CFG_XPU_SEC_INTR0_ENABLE_BMSK                                    0x200000
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_QHS_A2NOC_CFG_XPU_SEC_INTR0_ENABLE_SHFT                                        0x15
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_QXM_SNOC_MS_XPU_SEC_INTR0_ENABLE_BMSK                                      0x100000
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_QXM_SNOC_MS_XPU_SEC_INTR0_ENABLE_SHFT                                          0x14
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_GCC_RPU_XPU_SEC_INTR0_ENABLE_BMSK                                           0x80000
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_GCC_RPU_XPU_SEC_INTR0_ENABLE_SHFT                                              0x13
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_BIMC_CH1_XPU_SEC_INTR0_ENABLE_BMSK                                          0x40000
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_BIMC_CH1_XPU_SEC_INTR0_ENABLE_SHFT                                             0x12
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_BIMC_CH0_XPU_SEC_INTR0_ENABLE_BMSK                                          0x20000
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_BIMC_CH0_XPU_SEC_INTR0_ENABLE_SHFT                                             0x11
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_BIMC_CFG_XPU_SEC_INTR0_ENABLE_BMSK                                          0x10000
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_BIMC_CFG_XPU_SEC_INTR0_ENABLE_SHFT                                             0x10
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_QXM_MSS_NAV_CE_XPU_SEC_INTR0_ENABLE_BMSK                                     0x8000
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_QXM_MSS_NAV_CE_XPU_SEC_INTR0_ENABLE_SHFT                                        0xf
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_PIMEM_MPU_XPU_SEC_INTR0_ENABLE_BMSK                                          0x4000
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_PIMEM_MPU_XPU_SEC_INTR0_ENABLE_SHFT                                             0xe
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_PIMEM_APU_XPU_SEC_INTR0_ENABLE_BMSK                                          0x2000
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_PIMEM_APU_XPU_SEC_INTR0_ENABLE_SHFT                                             0xd
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_TURING_XPU_IRQ_XPU_SEC_INTR0_ENABLE_BMSK                                     0x1000
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_TURING_XPU_IRQ_XPU_SEC_INTR0_ENABLE_SHFT                                        0xc
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_LPASS_XPU_IRQ_APPS_0_XPU_SEC_INTR0_ENABLE_BMSK                                0x800
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_LPASS_XPU_IRQ_APPS_0_XPU_SEC_INTR0_ENABLE_SHFT                                  0xb
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_LPASS_XPU_IRQ_APPS_SPARE_XPU_SEC_INTR0_ENABLE_BMSK                            0x400
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_LPASS_XPU_IRQ_APPS_SPARE_XPU_SEC_INTR0_ENABLE_SHFT                              0xa
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_SEC_CTRL_APU_XPU_SEC_INTR0_ENABLE_BMSK                                        0x200
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_SEC_CTRL_APU_XPU_SEC_INTR0_ENABLE_SHFT                                          0x9
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_DCC_XPU_SEC_INTR0_ENABLE_BMSK                                                 0x100
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_DCC_XPU_SEC_INTR0_ENABLE_SHFT                                                   0x8
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_OCIMEM_RPU_XPU_SEC_INTR0_ENABLE_BMSK                                           0x80
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_OCIMEM_RPU_XPU_SEC_INTR0_ENABLE_SHFT                                            0x7
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_CRYPTO0_BAM_XPU_SEC_INTR0_ENABLE_BMSK                                          0x40
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_CRYPTO0_BAM_XPU_SEC_INTR0_ENABLE_SHFT                                           0x6
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_O_TCSR_MUTEX_XPU_SEC_INTR0_ENABLE_BMSK                                         0x20
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_O_TCSR_MUTEX_XPU_SEC_INTR0_ENABLE_SHFT                                          0x5
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_APSS_XPU_SEC_INTR0_ENABLE_BMSK                                                 0x10
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_APSS_XPU_SEC_INTR0_ENABLE_SHFT                                                  0x4
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_O_TCSR_REGS_XPU_SEC_INTR0_ENABLE_BMSK                                           0x8
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_O_TCSR_REGS_XPU_SEC_INTR0_ENABLE_SHFT                                           0x3
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_MMSS_NOC_XPU_SEC_INTR0_ENABLE_BMSK                                              0x4
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_MMSS_NOC_XPU_SEC_INTR0_ENABLE_SHFT                                              0x2
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_RESERVE_1_BMSK                                                                  0x2
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_RESERVE_1_SHFT                                                                  0x1
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_MMSS_QM_XPU_SEC_INTR0_ENABLE_BMSK                                               0x1
#define HWIO_TCSR_SS_XPU_SEC_INTR0_ENABLE_MMSS_QM_XPU_SEC_INTR0_ENABLE_SHFT                                               0x0

#define HWIO_TCSR_SS_XPU_SEC_INTR1_ENABLE_ADDR                                                                     (TCSR_TCSR_REGS_REG_BASE      + 0x00004044)
#define HWIO_TCSR_SS_XPU_SEC_INTR1_ENABLE_RMSK                                                                        0x3ffff
#define HWIO_TCSR_SS_XPU_SEC_INTR1_ENABLE_IN          \
        in_dword_masked(HWIO_TCSR_SS_XPU_SEC_INTR1_ENABLE_ADDR, HWIO_TCSR_SS_XPU_SEC_INTR1_ENABLE_RMSK)
#define HWIO_TCSR_SS_XPU_SEC_INTR1_ENABLE_INM(m)      \
        in_dword_masked(HWIO_TCSR_SS_XPU_SEC_INTR1_ENABLE_ADDR, m)
#define HWIO_TCSR_SS_XPU_SEC_INTR1_ENABLE_OUT(v)      \
        out_dword(HWIO_TCSR_SS_XPU_SEC_INTR1_ENABLE_ADDR,v)
#define HWIO_TCSR_SS_XPU_SEC_INTR1_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SS_XPU_SEC_INTR1_ENABLE_ADDR,m,v,HWIO_TCSR_SS_XPU_SEC_INTR1_ENABLE_IN)
#define HWIO_TCSR_SS_XPU_SEC_INTR1_ENABLE_LPASS_IRQ_OUT_SECURITY_18_XPU_SEC_INTR1_ENABLE_BMSK                         0x20000
#define HWIO_TCSR_SS_XPU_SEC_INTR1_ENABLE_LPASS_IRQ_OUT_SECURITY_18_XPU_SEC_INTR1_ENABLE_SHFT                            0x11
#define HWIO_TCSR_SS_XPU_SEC_INTR1_ENABLE_MMSS_XPU_MMSS_CC_XPU_SEC_INTR1_ENABLE_BMSK                                  0x10000
#define HWIO_TCSR_SS_XPU_SEC_INTR1_ENABLE_MMSS_XPU_MMSS_CC_XPU_SEC_INTR1_ENABLE_SHFT                                     0x10
#define HWIO_TCSR_SS_XPU_SEC_INTR1_ENABLE_TLMM_NORTH_XPU_SEC_INTR1_ENABLE_BMSK                                         0x8000
#define HWIO_TCSR_SS_XPU_SEC_INTR1_ENABLE_TLMM_NORTH_XPU_SEC_INTR1_ENABLE_SHFT                                            0xf
#define HWIO_TCSR_SS_XPU_SEC_INTR1_ENABLE_SKL_XPU_XPU_SEC_INTR1_ENABLE_BMSK                                            0x4000
#define HWIO_TCSR_SS_XPU_SEC_INTR1_ENABLE_SKL_XPU_XPU_SEC_INTR1_ENABLE_SHFT                                               0xe
#define HWIO_TCSR_SS_XPU_SEC_INTR1_ENABLE_ANOC1_MPU_XPU_SEC_INTR1_ENABLE_BMSK                                          0x2000
#define HWIO_TCSR_SS_XPU_SEC_INTR1_ENABLE_ANOC1_MPU_XPU_SEC_INTR1_ENABLE_SHFT                                             0xd
#define HWIO_TCSR_SS_XPU_SEC_INTR1_ENABLE_ANOC2_MPU_XPU_SEC_INTR1_ENABLE_BMSK                                          0x1000
#define HWIO_TCSR_SS_XPU_SEC_INTR1_ENABLE_ANOC2_MPU_XPU_SEC_INTR1_ENABLE_SHFT                                             0xc
#define HWIO_TCSR_SS_XPU_SEC_INTR1_ENABLE_IPA_0_XPU_SEC_INTR1_ENABLE_BMSK                                               0x800
#define HWIO_TCSR_SS_XPU_SEC_INTR1_ENABLE_IPA_0_XPU_SEC_INTR1_ENABLE_SHFT                                                 0xb
#define HWIO_TCSR_SS_XPU_SEC_INTR1_ENABLE_MSS_Q6_MPU_XPU_SEC_INTR1_ENABLE_BMSK                                          0x400
#define HWIO_TCSR_SS_XPU_SEC_INTR1_ENABLE_MSS_Q6_MPU_XPU_SEC_INTR1_ENABLE_SHFT                                            0xa
#define HWIO_TCSR_SS_XPU_SEC_INTR1_ENABLE_RPM_MPU_XPU_SEC_INTR1_ENABLE_BMSK                                             0x200
#define HWIO_TCSR_SS_XPU_SEC_INTR1_ENABLE_RPM_MPU_XPU_SEC_INTR1_ENABLE_SHFT                                               0x9
#define HWIO_TCSR_SS_XPU_SEC_INTR1_ENABLE_LPASS_IRQ_OUT_SECURITY_8_XPU_SEC_INTR1_ENABLE_BMSK                            0x100
#define HWIO_TCSR_SS_XPU_SEC_INTR1_ENABLE_LPASS_IRQ_OUT_SECURITY_8_XPU_SEC_INTR1_ENABLE_SHFT                              0x8
#define HWIO_TCSR_SS_XPU_SEC_INTR1_ENABLE_MDSS_XPU_XPU_SEC_INTR1_ENABLE_BMSK                                             0x80
#define HWIO_TCSR_SS_XPU_SEC_INTR1_ENABLE_MDSS_XPU_XPU_SEC_INTR1_ENABLE_SHFT                                              0x7
#define HWIO_TCSR_SS_XPU_SEC_INTR1_ENABLE_QDSS_BAM_XPU_SEC_INTR1_ENABLE_BMSK                                             0x40
#define HWIO_TCSR_SS_XPU_SEC_INTR1_ENABLE_QDSS_BAM_XPU_SEC_INTR1_ENABLE_SHFT                                              0x6
#define HWIO_TCSR_SS_XPU_SEC_INTR1_ENABLE_MPM2_XPU_SEC_INTR1_ENABLE_BMSK                                                 0x20
#define HWIO_TCSR_SS_XPU_SEC_INTR1_ENABLE_MPM2_XPU_SEC_INTR1_ENABLE_SHFT                                                  0x5
#define HWIO_TCSR_SS_XPU_SEC_INTR1_ENABLE_DDR_REGS_CFG_XPU_SEC_INTR1_ENABLE_BMSK                                         0x10
#define HWIO_TCSR_SS_XPU_SEC_INTR1_ENABLE_DDR_REGS_CFG_XPU_SEC_INTR1_ENABLE_SHFT                                          0x4
#define HWIO_TCSR_SS_XPU_SEC_INTR1_ENABLE_TLMM_SOUTH_XPU_SEC_INTR1_ENABLE_BMSK                                            0x8
#define HWIO_TCSR_SS_XPU_SEC_INTR1_ENABLE_TLMM_SOUTH_XPU_SEC_INTR1_ENABLE_SHFT                                            0x3
#define HWIO_TCSR_SS_XPU_SEC_INTR1_ENABLE_PERIPH_SS_BLSP2_BLSP_BAM_XPU_SEC_INTR1_ENABLE_BMSK                              0x4
#define HWIO_TCSR_SS_XPU_SEC_INTR1_ENABLE_PERIPH_SS_BLSP2_BLSP_BAM_XPU_SEC_INTR1_ENABLE_SHFT                              0x2
#define HWIO_TCSR_SS_XPU_SEC_INTR1_ENABLE_PERIPH_SS_BLSP1_BLSP_BAM_XPU_SEC_INTR1_ENABLE_BMSK                              0x2
#define HWIO_TCSR_SS_XPU_SEC_INTR1_ENABLE_PERIPH_SS_BLSP1_BLSP_BAM_XPU_SEC_INTR1_ENABLE_SHFT                              0x1
#define HWIO_TCSR_SS_XPU_SEC_INTR1_ENABLE_OCIMEM_RPU_XPU_SEC_INTR1_ENABLE_BMSK                                            0x1
#define HWIO_TCSR_SS_XPU_SEC_INTR1_ENABLE_OCIMEM_RPU_XPU_SEC_INTR1_ENABLE_SHFT                                            0x0

#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ADDR                                                               (TCSR_TCSR_REGS_REG_BASE      + 0x00002010)
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_RMSK                                                                   0x1fe3
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_IN          \
        in_dword_masked(HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ADDR, HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_RMSK)
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_INM(m)      \
        in_dword_masked(HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ADDR, m)
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_SPDM_VMID_NSGIRPT_BMSK                                                 0x1000
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_SPDM_VMID_NSGIRPT_SHFT                                                    0xc
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_QDSS_DAP_VMIDMT_NSGIRPT_BMSK                                            0x800
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_QDSS_DAP_VMIDMT_NSGIRPT_SHFT                                              0xb
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_QDSS_TRACE_VMIDMT_NSGIRPT_BMSK                                          0x400
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_QDSS_TRACE_VMIDMT_NSGIRPT_SHFT                                            0xa
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_IPA_VMIDMT_NSGIRPT_BMSK                                                 0x200
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_IPA_VMIDMT_NSGIRPT_SHFT                                                   0x9
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_BLSP2_VMIDMT_NSGIRPT_BMSK                                               0x100
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_BLSP2_VMIDMT_NSGIRPT_SHFT                                                 0x8
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_BLSP1_VMIDMT_NSGIRPT_BMSK                                                0x80
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_BLSP1_VMIDMT_NSGIRPT_SHFT                                                 0x7
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_LPASS_6_SENSOR_BLSP_BAM_VMIDMT_NSGIRPT_BMSK                              0x40
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_LPASS_6_SENSOR_BLSP_BAM_VMIDMT_NSGIRPT_SHFT                               0x6
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_QDSS_BAM_VMIDMT_NSGIRPT_BMSK                                             0x20
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_QDSS_BAM_VMIDMT_NSGIRPT_SHFT                                              0x5
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_RPM_VMIDMT_CLIENT_INTR_BMSK                                               0x2
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_RPM_VMIDMT_CLIENT_INTR_SHFT                                               0x1
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_CRYPTO0_VMIDMT_NSGIRPT_BMSK                                               0x1
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_CRYPTO0_VMIDMT_NSGIRPT_SHFT                                               0x0

#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ADDR                                                                  (TCSR_TCSR_REGS_REG_BASE      + 0x00002014)
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_RMSK                                                                      0x7e42
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_IN          \
        in_dword_masked(HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ADDR, HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_RMSK)
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_INM(m)      \
        in_dword_masked(HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ADDR, m)
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_TURING_SPARE_IRQ_OUT_SECURITY_BMSK                                        0x4000
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_TURING_SPARE_IRQ_OUT_SECURITY_SHFT                                           0xe
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_TURING_13_IRQ_OUT_SECURITY_BMSK                                           0x2000
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_TURING_13_IRQ_OUT_SECURITY_SHFT                                              0xd
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_LPASS_15_IRQ_OUT_SECURITY_BMSK                                            0x1000
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_LPASS_15_IRQ_OUT_SECURITY_SHFT                                               0xc
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_LPASS_SPARE_IRQ_OUT_SECURITY_BMSK                                          0x800
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_LPASS_SPARE_IRQ_OUT_SECURITY_SHFT                                            0xb
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_AGGR2_NOC_SMMU_MMU_NSGIRPT_BMSK                                            0x400
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_AGGR2_NOC_SMMU_MMU_NSGIRPT_SHFT                                              0xa
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_AGGR1_NOC_SMMU_MMU_NSGIRPT_BMSK                                            0x200
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_AGGR1_NOC_SMMU_MMU_NSGIRPT_SHFT                                              0x9
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_OGPU_MMU_NSGIRPT_BMSK                                                       0x40
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_OGPU_MMU_NSGIRPT_SHFT                                                        0x6
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_MMSS_BIMC_SMMU_NSGIRPT_BMSK                                                  0x2
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_MMSS_BIMC_SMMU_NSGIRPT_SHFT                                                  0x1

#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_ADDR                                                        (TCSR_TCSR_REGS_REG_BASE      + 0x00002050)
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_RMSK                                                            0x1fe3
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_IN          \
        in_dword_masked(HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_ADDR, HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_RMSK)
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_INM(m)      \
        in_dword_masked(HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_ADDR, m)
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_OUT(v)      \
        out_dword(HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_ADDR,v)
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_ADDR,m,v,HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_IN)
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_SPDM_VMID_NSGIRPT_ENABLE_BMSK                                   0x1000
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_SPDM_VMID_NSGIRPT_ENABLE_SHFT                                      0xc
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_QDSS_DAP_VMIDMT_NSGIRPT_ENABLE_BMSK                              0x800
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_QDSS_DAP_VMIDMT_NSGIRPT_ENABLE_SHFT                                0xb
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_QDSS_TRACE_VMIDMT_NSGIRPT_ENABLE_BMSK                            0x400
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_QDSS_TRACE_VMIDMT_NSGIRPT_ENABLE_SHFT                              0xa
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_IPA_VMIDMT_NSGIRPT_ENABLE_BMSK                                   0x200
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_IPA_VMIDMT_NSGIRPT_ENABLE_SHFT                                     0x9
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_BLSP2_VMIDMT_NSGIRPT_ENABLE_BMSK                                 0x100
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_BLSP2_VMIDMT_NSGIRPT_ENABLE_SHFT                                   0x8
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_BLSP1_VMIDMT_NSGIRPT_ENABLE_BMSK                                  0x80
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_BLSP1_VMIDMT_NSGIRPT_ENABLE_SHFT                                   0x7
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_LPASS_6_SENSOR_BLSP_BAM_VMIDMT_NSGIRPT_ENABLE_BMSK                0x40
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_LPASS_6_SENSOR_BLSP_BAM_VMIDMT_NSGIRPT_ENABLE_SHFT                 0x6
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_QDSS_BAM_VMIDMT_NSGIRPT_ENABLE_BMSK                               0x20
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_QDSS_BAM_VMIDMT_NSGIRPT_ENABLE_SHFT                                0x5
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_RPM_VMIDMT_CLIENT_NSGIRPT_ENABLE_BMSK                              0x2
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_RPM_VMIDMT_CLIENT_NSGIRPT_ENABLE_SHFT                              0x1
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_CRYPTO0_VMIDMT_NSGIRPT_ENABLE_BMSK                                 0x1
#define HWIO_TCSR_SS_VMIDMT_CLIENT_NON_SEC_INTR_ENABLE_CRYPTO0_VMIDMT_NSGIRPT_ENABLE_SHFT                                 0x0

#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ENABLE_ADDR                                                           (TCSR_TCSR_REGS_REG_BASE      + 0x00002054)
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ENABLE_RMSK                                                               0x7e42
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ENABLE_IN          \
        in_dword_masked(HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ENABLE_ADDR, HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ENABLE_RMSK)
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ENABLE_INM(m)      \
        in_dword_masked(HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ENABLE_ADDR, m)
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ENABLE_OUT(v)      \
        out_dword(HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ENABLE_ADDR,v)
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ENABLE_ADDR,m,v,HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ENABLE_IN)
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ENABLE_TURING_SPARE_IRQ_OUT_SECURITY_INTR_ENABLE_BMSK                     0x4000
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ENABLE_TURING_SPARE_IRQ_OUT_SECURITY_INTR_ENABLE_SHFT                        0xe
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ENABLE_TURING_13_IRQ_OUT_SECURITY_INTR_ENABLE_BMSK                        0x2000
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ENABLE_TURING_13_IRQ_OUT_SECURITY_INTR_ENABLE_SHFT                           0xd
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ENABLE_LPASS_15_IRQ_OUT_SECURITY_INTR_ENABLE_BMSK                         0x1000
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ENABLE_LPASS_15_IRQ_OUT_SECURITY_INTR_ENABLE_SHFT                            0xc
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ENABLE_LPASS_SPARE_IRQ_OUT_SECURITY_INTR_ENABLE_BMSK                       0x800
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ENABLE_LPASS_SPARE_IRQ_OUT_SECURITY_INTR_ENABLE_SHFT                         0xb
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ENABLE_AGGR2_NOC_SMMU_MMU_NSGIRPT_ENABLE_BMSK                              0x400
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ENABLE_AGGR2_NOC_SMMU_MMU_NSGIRPT_ENABLE_SHFT                                0xa
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ENABLE_AGGR1_NOC_SMMU_MMU_NSGIRPT_ENABLE_BMSK                              0x200
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ENABLE_AGGR1_NOC_SMMU_MMU_NSGIRPT_ENABLE_SHFT                                0x9
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ENABLE_OGPU_MMU_NSGIRPT_ENABLE_BMSK                                         0x40
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ENABLE_OGPU_MMU_NSGIRPT_ENABLE_SHFT                                          0x6
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ENABLE_MMSS_BIMC_SMMU_NSGIRPT_ENABLE_BMSK                                    0x2
#define HWIO_TCSR_SS_MMU_CLIENT_NON_SEC_INTR_ENABLE_MMSS_BIMC_SMMU_NSGIRPT_ENABLE_SHFT                                    0x1

#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ADDR                                                                  (TCSR_TCSR_REGS_REG_BASE      + 0x00003000)
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_RMSK                                                                      0x1fe3
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_IN          \
        in_dword_masked(HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ADDR, HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_RMSK)
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_INM(m)      \
        in_dword_masked(HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ADDR, m)
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_SPDM_VMID_NSGCFGIRPT_BMSK                                                 0x1000
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_SPDM_VMID_NSGCFGIRPT_SHFT                                                    0xc
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_QDSS_DAP_VMIDMT_NSGCFGIRPT_BMSK                                            0x800
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_QDSS_DAP_VMIDMT_NSGCFGIRPT_SHFT                                              0xb
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_QDSS_TRACE_VMIDMT_NSGCFGIRPT_BMSK                                          0x400
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_QDSS_TRACE_VMIDMT_NSGCFGIRPT_SHFT                                            0xa
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_IPA_VMIDMT_NSGCFGIRPT_BMSK                                                 0x200
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_IPA_VMIDMT_NSGCFGIRPT_SHFT                                                   0x9
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_BLSP2_VMIDMT_NSGCFGIRPT_BMSK                                               0x100
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_BLSP2_VMIDMT_NSGCFGIRPT_SHFT                                                 0x8
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_BLSP1_VMIDMT_NSGCFGIRPT_BMSK                                                0x80
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_BLSP1_VMIDMT_NSGCFGIRPT_SHFT                                                 0x7
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_LPASS_4_SENSOR_BLSP_BAM_VMIDMT_NSGCFGIRPT_BMSK                              0x40
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_LPASS_4_SENSOR_BLSP_BAM_VMIDMT_NSGCFGIRPT_SHFT                               0x6
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_QDSS_BAM_VMIDMT_NSGCFGIRPT_BMSK                                             0x20
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_QDSS_BAM_VMIDMT_NSGCFGIRPT_SHFT                                              0x5
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_RPM_VMIDMT_CLIENT_INTR_BMSK                                                  0x2
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_RPM_VMIDMT_CLIENT_INTR_SHFT                                                  0x1
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_CRYPTO0_VMIDMT_NSGCFGIRPT_BMSK                                               0x1
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_CRYPTO0_VMIDMT_NSGCFGIRPT_SHFT                                               0x0

#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ADDR                                                                     (TCSR_TCSR_REGS_REG_BASE      + 0x00003004)
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_RMSK                                                                         0x7e42
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_IN          \
        in_dword_masked(HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ADDR, HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_RMSK)
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_INM(m)      \
        in_dword_masked(HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ADDR, m)
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_OUT(v)      \
        out_dword(HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ADDR,v)
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ADDR,m,v,HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_IN)
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_TURING_SPARE_IRQ_OUT_SECURITY_BMSK                                           0x4000
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_TURING_SPARE_IRQ_OUT_SECURITY_SHFT                                              0xe
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_TURING_12_IRQ_OUT_SECURITY_BMSK                                              0x2000
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_TURING_12_IRQ_OUT_SECURITY_SHFT                                                 0xd
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_LPASS_14_IRQ_OUT_SECURITY_BMSK                                               0x1000
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_LPASS_14_IRQ_OUT_SECURITY_SHFT                                                  0xc
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_LPASS_SPARE_IRQ_OUT_SECURITY_BMSK                                             0x800
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_LPASS_SPARE_IRQ_OUT_SECURITY_SHFT                                               0xb
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_AGGR2_NOC_SMMU_MMU_NSGCFGIRPT_BMSK                                            0x400
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_AGGR2_NOC_SMMU_MMU_NSGCFGIRPT_SHFT                                              0xa
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_AGGR1_NOC_SMMU_MMU_NSGCFGIRPT_BMSK                                            0x200
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_AGGR1_NOC_SMMU_MMU_NSGCFGIRPT_SHFT                                              0x9
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_OGPU_MMU_NSGCFGIRPT_BMSK                                                       0x40
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_OGPU_MMU_NSGCFGIRPT_SHFT                                                        0x6
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_MMSS_BIMC_SMMU_NSGCFGIRPT_BMSK                                                  0x2
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_MMSS_BIMC_SMMU_NSGCFGIRPT_SHFT                                                  0x1

#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_ADDR                                                           (TCSR_TCSR_REGS_REG_BASE      + 0x00003040)
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_RMSK                                                               0x1fe3
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_IN          \
        in_dword_masked(HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_ADDR, HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_RMSK)
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_INM(m)      \
        in_dword_masked(HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_ADDR, m)
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_OUT(v)      \
        out_dword(HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_ADDR,v)
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_ADDR,m,v,HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_IN)
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_SPDM_VMID_NSGCFGIRPT_ENABLE_BMSK                                   0x1000
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_SPDM_VMID_NSGCFGIRPT_ENABLE_SHFT                                      0xc
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_QDSS_DAP_VMIDMT_NSGCFGIRPT_ENABLE_BMSK                              0x800
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_QDSS_DAP_VMIDMT_NSGCFGIRPT_ENABLE_SHFT                                0xb
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_QDSS_TRACE_VMIDMT_NSGCFGIRPT_ENABLE_BMSK                            0x400
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_QDSS_TRACE_VMIDMT_NSGCFGIRPT_ENABLE_SHFT                              0xa
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_IPA_VMIDMT_NSGCFGIRPT_ENABLE_BMSK                                   0x200
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_IPA_VMIDMT_NSGCFGIRPT_ENABLE_SHFT                                     0x9
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_BLSP2_VMIDMT_NSGCFGIRPT_ENABLE_BMSK                                 0x100
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_BLSP2_VMIDMT_NSGCFGIRPT_ENABLE_SHFT                                   0x8
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_BLSP1_VMIDMT_NSGCFGIRPT_ENABLE_BMSK                                  0x80
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_BLSP1_VMIDMT_NSGCFGIRPT_ENABLE_SHFT                                   0x7
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_LPASS_4_SENSOR_BLSP_BAM_VMIDMT_NSGCFGIRPT_ENABLE_BMSK                0x40
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_LPASS_4_SENSOR_BLSP_BAM_VMIDMT_NSGCFGIRPT_ENABLE_SHFT                 0x6
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_QDSS_BAM_VMIDMT_NSGCFGIRPT_ENABLE_BMSK                               0x20
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_QDSS_BAM_VMIDMT_NSGCFGIRPT_ENABLE_SHFT                                0x5
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_RPM_VMIDMT_CLIENT_NSGCFGIRPT_ENABLE_BMSK                              0x2
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_RPM_VMIDMT_CLIENT_NSGCFGIRPT_ENABLE_SHFT                              0x1
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_CRYPTO0_VMIDMT_NSGCFGIRPT_ENABLE_BMSK                                 0x1
#define HWIO_TCSR_SS_VMIDMT_CFG_NON_SEC_INTR_ENABLE_CRYPTO0_VMIDMT_NSGCFGIRPT_ENABLE_SHFT                                 0x0

#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ENABLE_ADDR                                                              (TCSR_TCSR_REGS_REG_BASE      + 0x00003044)
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ENABLE_RMSK                                                                  0x7e42
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ENABLE_IN          \
        in_dword_masked(HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ENABLE_ADDR, HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ENABLE_RMSK)
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ENABLE_INM(m)      \
        in_dword_masked(HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ENABLE_ADDR, m)
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ENABLE_OUT(v)      \
        out_dword(HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ENABLE_ADDR,v)
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ENABLE_ADDR,m,v,HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ENABLE_IN)
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ENABLE_TURING_SPARE_IRQ_OUT_SECURITY_INTR_ENABLE_BMSK                        0x4000
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ENABLE_TURING_SPARE_IRQ_OUT_SECURITY_INTR_ENABLE_SHFT                           0xe
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ENABLE_TURING_12_IRQ_OUT_SECURITY_INTR_ENABLE_BMSK                           0x2000
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ENABLE_TURING_12_IRQ_OUT_SECURITY_INTR_ENABLE_SHFT                              0xd
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ENABLE_LPASS_14_IRQ_OUT_SECURITY_INTR_ENABLE_BMSK                            0x1000
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ENABLE_LPASS_14_IRQ_OUT_SECURITY_INTR_ENABLE_SHFT                               0xc
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ENABLE_LPASS_SPARE_IRQ_OUT_SECURITY_INTR_ENABLE_BMSK                          0x800
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ENABLE_LPASS_SPARE_IRQ_OUT_SECURITY_INTR_ENABLE_SHFT                            0xb
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ENABLE_AGGR2_NOC_SMMU_MMU_NSGCFGIRPT_ENABLE_BMSK                              0x400
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ENABLE_AGGR2_NOC_SMMU_MMU_NSGCFGIRPT_ENABLE_SHFT                                0xa
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ENABLE_AGGR1_NOC_SMMU_MMU_NSGCFGIRPT_ENABLE_BMSK                              0x200
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ENABLE_AGGR1_NOC_SMMU_MMU_NSGCFGIRPT_ENABLE_SHFT                                0x9
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ENABLE_OGPU_MMU_NSGCFGIRPT_ENABLE_BMSK                                         0x40
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ENABLE_OGPU_MMU_NSGCFGIRPT_ENABLE_SHFT                                          0x6
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ENABLE_MMSS_BIMC_SMMU_NSGCFGIRPT_ENABLE_BMSK                                    0x2
#define HWIO_TCSR_SS_MMU_CFG_NON_SEC_INTR_ENABLE_MMSS_BIMC_SMMU_NSGCFGIRPT_ENABLE_SHFT                                    0x1

#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ADDR                                                                   (TCSR_TCSR_REGS_REG_BASE      + 0x00004010)
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_RMSK                                                                       0x1fe3
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_IN          \
        in_dword_masked(HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ADDR, HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_RMSK)
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_INM(m)      \
        in_dword_masked(HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ADDR, m)
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_SPDM_VMID_GIRPT_BMSK                                                       0x1000
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_SPDM_VMID_GIRPT_SHFT                                                          0xc
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_QDSS_DAP_VMIDMT_GIRPT_BMSK                                                  0x800
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_QDSS_DAP_VMIDMT_GIRPT_SHFT                                                    0xb
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_QDSS_TRACE_VMIDMT_GIRPT_BMSK                                                0x400
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_QDSS_TRACE_VMIDMT_GIRPT_SHFT                                                  0xa
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_IPA_VMIDMT_GIRPT_BMSK                                                       0x200
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_IPA_VMIDMT_GIRPT_SHFT                                                         0x9
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_BLSP2_VMIDMT_GIRPT_BMSK                                                     0x100
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_BLSP2_VMIDMT_GIRPT_SHFT                                                       0x8
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_BLSP1_VMIDMT_GIRPT_BMSK                                                      0x80
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_BLSP1_VMIDMT_GIRPT_SHFT                                                       0x7
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_LPASS_7_SENSOR_BLSP_BAM_VMIDMT_GIRPT_BMSK                                    0x40
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_LPASS_7_SENSOR_BLSP_BAM_VMIDMT_GIRPT_SHFT                                     0x6
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_QDSS_BAM_VMIDMT_GIRPT_BMSK                                                   0x20
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_QDSS_BAM_VMIDMT_GIRPT_SHFT                                                    0x5
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_RPM_VMIDMT_CLIENT_INTR_BMSK                                                   0x2
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_RPM_VMIDMT_CLIENT_INTR_SHFT                                                   0x1
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_CRYPTO0_VMIDMT_GIRPT_BMSK                                                     0x1
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_CRYPTO0_VMIDMT_GIRPT_SHFT                                                     0x0

#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ADDR                                                                      (TCSR_TCSR_REGS_REG_BASE      + 0x00004014)
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_RMSK                                                                          0x7e42
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_IN          \
        in_dword_masked(HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ADDR, HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_RMSK)
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_INM(m)      \
        in_dword_masked(HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ADDR, m)
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_TURING_SPARE_IRQ_OUT_SECURITY_BMSK                                            0x4000
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_TURING_SPARE_IRQ_OUT_SECURITY_SHFT                                               0xe
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_TURING_15_IRQ_OUT_SECURITY_BMSK                                               0x2000
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_TURING_15_IRQ_OUT_SECURITY_SHFT                                                  0xd
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_LPASS_17_IRQ_OUT_SECURITY_BMSK                                                0x1000
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_LPASS_17_IRQ_OUT_SECURITY_SHFT                                                   0xc
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_LPASS_SPARE_IRQ_OUT_SECURITY_BMSK                                              0x800
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_LPASS_SPARE_IRQ_OUT_SECURITY_SHFT                                                0xb
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_AGGR2_NOC_SMMU_MMU_GIRPT_BMSK                                                  0x400
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_AGGR2_NOC_SMMU_MMU_GIRPT_SHFT                                                    0xa
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_AGGR1_NOC_SMMU_MMU_GIRPT_BMSK                                                  0x200
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_AGGR1_NOC_SMMU_MMU_GIRPT_SHFT                                                    0x9
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_OGPU_MMU_GIRPT_BMSK                                                             0x40
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_OGPU_MMU_GIRPT_SHFT                                                              0x6
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_MMSS_BIMC_SMMU_GIRPT_BMSK                                                        0x2
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_MMSS_BIMC_SMMU_GIRPT_SHFT                                                        0x1

#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_ADDR                                                            (TCSR_TCSR_REGS_REG_BASE      + 0x00004050)
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_RMSK                                                                0x1fe3
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_IN          \
        in_dword_masked(HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_ADDR, HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_RMSK)
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_INM(m)      \
        in_dword_masked(HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_ADDR, m)
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_OUT(v)      \
        out_dword(HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_ADDR,v)
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_ADDR,m,v,HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_IN)
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_SPDM_VMID_GIRPT_ENABLE_BMSK                                         0x1000
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_SPDM_VMID_GIRPT_ENABLE_SHFT                                            0xc
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_QDSS_DAP_VMIDMT_GIRPT_ENABLE_BMSK                                    0x800
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_QDSS_DAP_VMIDMT_GIRPT_ENABLE_SHFT                                      0xb
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_QDSS_TRACE_VMIDMT_GIRPT_ENABLE_BMSK                                  0x400
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_QDSS_TRACE_VMIDMT_GIRPT_ENABLE_SHFT                                    0xa
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_IPA_VMIDMT_GIRPT_ENABLE_BMSK                                         0x200
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_IPA_VMIDMT_GIRPT_ENABLE_SHFT                                           0x9
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_BLSP2_VMIDMT_GIRPT_ENABLE_BMSK                                       0x100
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_BLSP2_VMIDMT_GIRPT_ENABLE_SHFT                                         0x8
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_BLSP1_VMIDMT_GIRPT_ENABLE_BMSK                                        0x80
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_BLSP1_VMIDMT_GIRPT_ENABLE_SHFT                                         0x7
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_LPASS_7_SENSOR_BLSP_BAM_VMIDMT_GIRPT_ENABLE_BMSK                      0x40
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_LPASS_7_SENSOR_BLSP_BAM_VMIDMT_GIRPT_ENABLE_SHFT                       0x6
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_QDSS_BAM_VMIDMT_GIRPT_ENABLE_BMSK                                     0x20
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_QDSS_BAM_VMIDMT_GIRPT_ENABLE_SHFT                                      0x5
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_RPM_VMIDMT_CLIENT_GIRPT_ENABLE_BMSK                                    0x2
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_RPM_VMIDMT_CLIENT_GIRPT_ENABLE_SHFT                                    0x1
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_CRYPTO0_VMIDMT_GIRPT_ENABLE_BMSK                                       0x1
#define HWIO_TCSR_SS_VMIDMT_CLIENT_SEC_INTR_ENABLE_CRYPTO0_VMIDMT_GIRPT_ENABLE_SHFT                                       0x0

#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ENABLE_ADDR                                                               (TCSR_TCSR_REGS_REG_BASE      + 0x00004054)
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ENABLE_RMSK                                                                   0x7e42
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ENABLE_IN          \
        in_dword_masked(HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ENABLE_ADDR, HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ENABLE_RMSK)
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ENABLE_INM(m)      \
        in_dword_masked(HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ENABLE_ADDR, m)
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ENABLE_OUT(v)      \
        out_dword(HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ENABLE_ADDR,v)
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ENABLE_ADDR,m,v,HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ENABLE_IN)
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ENABLE_TURING_SPARE_IRQ_OUT_SECURITY_INTR_ENABLE_BMSK                         0x4000
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ENABLE_TURING_SPARE_IRQ_OUT_SECURITY_INTR_ENABLE_SHFT                            0xe
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ENABLE_TURING_15_IRQ_OUT_SECURITY_INTR_ENABLE_BMSK                            0x2000
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ENABLE_TURING_15_IRQ_OUT_SECURITY_INTR_ENABLE_SHFT                               0xd
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ENABLE_LPASS_17_IRQ_OUT_SECURITY_INTR_ENABLE_BMSK                             0x1000
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ENABLE_LPASS_17_IRQ_OUT_SECURITY_INTR_ENABLE_SHFT                                0xc
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ENABLE_LPASS_SPARE_IRQ_OUT_SECURITY_INTR_ENABLE_BMSK                           0x800
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ENABLE_LPASS_SPARE_IRQ_OUT_SECURITY_INTR_ENABLE_SHFT                             0xb
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ENABLE_AGGR2_NOC_SMMU_MMU_GIRPT_ENABLE_BMSK                                    0x400
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ENABLE_AGGR2_NOC_SMMU_MMU_GIRPT_ENABLE_SHFT                                      0xa
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ENABLE_AGGR1_NOC_SMMU_MMU_GIRPT_ENABLE_BMSK                                    0x200
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ENABLE_AGGR1_NOC_SMMU_MMU_GIRPT_ENABLE_SHFT                                      0x9
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ENABLE_OGPU_MMU_GIRPT_ENABLE_BMSK                                               0x40
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ENABLE_OGPU_MMU_GIRPT_ENABLE_SHFT                                                0x6
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ENABLE_MMSS_BIMC_SMMU_GIRPT_ENABLE_BMSK                                          0x2
#define HWIO_TCSR_SS_MMU_CLIENT_SEC_INTR_ENABLE_MMSS_BIMC_SMMU_GIRPT_ENABLE_SHFT                                          0x1

#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ADDR                                                                      (TCSR_TCSR_REGS_REG_BASE      + 0x00005000)
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_RMSK                                                                          0x1fe3
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_IN          \
        in_dword_masked(HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ADDR, HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_RMSK)
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_INM(m)      \
        in_dword_masked(HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ADDR, m)
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_SPDM_VMID_GCFGIRPT_BMSK                                                       0x1000
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_SPDM_VMID_GCFGIRPT_SHFT                                                          0xc
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_QDSS_DAP_VMIDMT_GCFGIRPT_BMSK                                                  0x800
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_QDSS_DAP_VMIDMT_GCFGIRPT_SHFT                                                    0xb
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_QDSS_TRACE_VMIDMT_GCFGIRPT_BMSK                                                0x400
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_QDSS_TRACE_VMIDMT_GCFGIRPT_SHFT                                                  0xa
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_IPA_VMIDMT_GCFGIRPT_BMSK                                                       0x200
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_IPA_VMIDMT_GCFGIRPT_SHFT                                                         0x9
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_BLSP2_VMIDMT_GCFGIRPT_BMSK                                                     0x100
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_BLSP2_VMIDMT_GCFGIRPT_SHFT                                                       0x8
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_BLSP1_VMIDMT_GCFGIRPT_BMSK                                                      0x80
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_BLSP1_VMIDMT_GCFGIRPT_SHFT                                                       0x7
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_LPASS_5_SENSOR_BLSP_BAM_VMIDMT_GCFGIRPT_BMSK                                    0x40
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_LPASS_5_SENSOR_BLSP_BAM_VMIDMT_GCFGIRPT_SHFT                                     0x6
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_QDSS_BAM_VMIDMT_GCFGIRPT_BMSK                                                   0x20
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_QDSS_BAM_VMIDMT_GCFGIRPT_SHFT                                                    0x5
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_RPM_VMIDMT_CLIENT_INTR_BMSK                                                      0x2
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_RPM_VMIDMT_CLIENT_INTR_SHFT                                                      0x1
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_CRYPTO0_VMIDMT_GCFGIRPT_BMSK                                                     0x1
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_CRYPTO0_VMIDMT_GCFGIRPT_SHFT                                                     0x0

#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ADDR                                                                         (TCSR_TCSR_REGS_REG_BASE      + 0x00005004)
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_RMSK                                                                             0x7e42
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_IN          \
        in_dword_masked(HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ADDR, HWIO_TCSR_SS_MMU_CFG_SEC_INTR_RMSK)
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_INM(m)      \
        in_dword_masked(HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ADDR, m)
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_OUT(v)      \
        out_dword(HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ADDR,v)
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ADDR,m,v,HWIO_TCSR_SS_MMU_CFG_SEC_INTR_IN)
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_TURING_SPARE_IRQ_OUT_SECURITY_BMSK                                               0x4000
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_TURING_SPARE_IRQ_OUT_SECURITY_SHFT                                                  0xe
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_TURING_14_IRQ_OUT_SECURITY_BMSK                                                  0x2000
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_TURING_14_IRQ_OUT_SECURITY_SHFT                                                     0xd
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_LPASS_16_IRQ_OUT_SECURITY_BMSK                                                   0x1000
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_LPASS_16_IRQ_OUT_SECURITY_SHFT                                                      0xc
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_LPASS_SPARE_IRQ_OUT_SECURITY_BMSK                                                 0x800
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_LPASS_SPARE_IRQ_OUT_SECURITY_SHFT                                                   0xb
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_AGGR2_NOC_SMMU_MMU_GCFGIRPT_BMSK                                                  0x400
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_AGGR2_NOC_SMMU_MMU_GCFGIRPT_SHFT                                                    0xa
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_AGGR1_NOC_SMMU_MMU_GCFGIRPT_BMSK                                                  0x200
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_AGGR1_NOC_SMMU_MMU_GCFGIRPT_SHFT                                                    0x9
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_OGPU_MMU_GCFGIRPT_BMSK                                                             0x40
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_OGPU_MMU_GCFGIRPT_SHFT                                                              0x6
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_MMSS_BIMC_SMMU_GCFGIRPT_BMSK                                                        0x2
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_MMSS_BIMC_SMMU_GCFGIRPT_SHFT                                                        0x1

#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_ADDR                                                               (TCSR_TCSR_REGS_REG_BASE      + 0x00005040)
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_RMSK                                                                   0x1fe3
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_IN          \
        in_dword_masked(HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_ADDR, HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_RMSK)
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_INM(m)      \
        in_dword_masked(HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_ADDR, m)
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_OUT(v)      \
        out_dword(HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_ADDR,v)
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_ADDR,m,v,HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_IN)
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_SPDM_VMID_GCFGIRPT_ENABLE_BMSK                                         0x1000
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_SPDM_VMID_GCFGIRPT_ENABLE_SHFT                                            0xc
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_QDSS_DAP_VMIDMT_GCFGIRPT_ENABLE_BMSK                                    0x800
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_QDSS_DAP_VMIDMT_GCFGIRPT_ENABLE_SHFT                                      0xb
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_QDSS_TRACE_VMIDMT_GCFGIRPT_ENABLE_BMSK                                  0x400
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_QDSS_TRACE_VMIDMT_GCFGIRPT_ENABLE_SHFT                                    0xa
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_IPA_VMIDMT_GCFGIRPT_ENABLE_BMSK                                         0x200
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_IPA_VMIDMT_GCFGIRPT_ENABLE_SHFT                                           0x9
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_BLSP2_VMIDMT_GCFGIRPT_ENABLE_BMSK                                       0x100
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_BLSP2_VMIDMT_GCFGIRPT_ENABLE_SHFT                                         0x8
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_BLSP1_VMIDMT_GCFGIRPT_ENABLE_BMSK                                        0x80
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_BLSP1_VMIDMT_GCFGIRPT_ENABLE_SHFT                                         0x7
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_LPASS_5_SENSOR_BLSP_BAM_VMIDMT_GCFGIRPT_ENABLE_BMSK                      0x40
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_LPASS_5_SENSOR_BLSP_BAM_VMIDMT_GCFGIRPT_ENABLE_SHFT                       0x6
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_QDSS_BAM_VMIDMT_GCFGIRPT_ENABLE_BMSK                                     0x20
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_QDSS_BAM_VMIDMT_GCFGIRPT_ENABLE_SHFT                                      0x5
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_RPM_VMIDMT_CLIENT_GCFGIRPT_ENABLE_BMSK                                    0x2
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_RPM_VMIDMT_CLIENT_GCFGIRPT_ENABLE_SHFT                                    0x1
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_CRYPTO0_VMIDMT_GCFGIRPT_ENABLE_BMSK                                       0x1
#define HWIO_TCSR_SS_VMIDMT_CFG_SEC_INTR_ENABLE_CRYPTO0_VMIDMT_GCFGIRPT_ENABLE_SHFT                                       0x0

#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ENABLE_ADDR                                                                  (TCSR_TCSR_REGS_REG_BASE      + 0x00005044)
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ENABLE_RMSK                                                                      0x7e42
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ENABLE_IN          \
        in_dword_masked(HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ENABLE_ADDR, HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ENABLE_RMSK)
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ENABLE_INM(m)      \
        in_dword_masked(HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ENABLE_ADDR, m)
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ENABLE_OUT(v)      \
        out_dword(HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ENABLE_ADDR,v)
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ENABLE_ADDR,m,v,HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ENABLE_IN)
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ENABLE_TURING_SPARE_IRQ_OUT_SECURITY_INTR_ENABLE_BMSK                            0x4000
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ENABLE_TURING_SPARE_IRQ_OUT_SECURITY_INTR_ENABLE_SHFT                               0xe
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ENABLE_TURING_14_IRQ_OUT_SECURITY_INTR_ENABLE_BMSK                               0x2000
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ENABLE_TURING_14_IRQ_OUT_SECURITY_INTR_ENABLE_SHFT                                  0xd
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ENABLE_LPASS_16_IRQ_OUT_SECURITY_INTR_ENABLE_BMSK                                0x1000
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ENABLE_LPASS_16_IRQ_OUT_SECURITY_INTR_ENABLE_SHFT                                   0xc
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ENABLE_LPASS_SPARE_IRQ_OUT_SECURITY_INTR_ENABLE_BMSK                              0x800
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ENABLE_LPASS_SPARE_IRQ_OUT_SECURITY_INTR_ENABLE_SHFT                                0xb
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ENABLE_AGGR2_NOC_SMMU_MMU_GCFGIRPT_ENABLE_BMSK                                    0x400
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ENABLE_AGGR2_NOC_SMMU_MMU_GCFGIRPT_ENABLE_SHFT                                      0xa
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ENABLE_AGGR1_NOC_SMMU_MMU_GCFGIRPT_ENABLE_BMSK                                    0x200
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ENABLE_AGGR1_NOC_SMMU_MMU_GCFGIRPT_ENABLE_SHFT                                      0x9
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ENABLE_OGPU_MMU_GCFGIRPT_ENABLE_BMSK                                               0x40
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ENABLE_OGPU_MMU_GCFGIRPT_ENABLE_SHFT                                                0x6
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ENABLE_MMSS_BIMC_SMMU_GCFGIRPT_ENABLE_BMSK                                          0x2
#define HWIO_TCSR_SS_MMU_CFG_SEC_INTR_ENABLE_MMSS_BIMC_SMMU_GCFGIRPT_ENABLE_SHFT                                          0x1

#define HWIO_TCSR_SS_XPU_MSA_INTR0_ADDR                                                                            (TCSR_TCSR_REGS_REG_BASE      + 0x00006000)
#define HWIO_TCSR_SS_XPU_MSA_INTR0_RMSK                                                                            0xffffffff
#define HWIO_TCSR_SS_XPU_MSA_INTR0_IN          \
        in_dword_masked(HWIO_TCSR_SS_XPU_MSA_INTR0_ADDR, HWIO_TCSR_SS_XPU_MSA_INTR0_RMSK)
#define HWIO_TCSR_SS_XPU_MSA_INTR0_INM(m)      \
        in_dword_masked(HWIO_TCSR_SS_XPU_MSA_INTR0_ADDR, m)
#define HWIO_TCSR_SS_XPU_MSA_INTR0_RESERVE_31_BMSK                                                                 0x80000000
#define HWIO_TCSR_SS_XPU_MSA_INTR0_RESERVE_31_SHFT                                                                       0x1f
#define HWIO_TCSR_SS_XPU_MSA_INTR0_BOOT_ROM_MSA_INTR_BMSK                                                          0x40000000
#define HWIO_TCSR_SS_XPU_MSA_INTR0_BOOT_ROM_MSA_INTR_SHFT                                                                0x1e
#define HWIO_TCSR_SS_XPU_MSA_INTR0_SDC1_ICE_XPU_MSA_INTR_BMSK                                                      0x20000000
#define HWIO_TCSR_SS_XPU_MSA_INTR0_SDC1_ICE_XPU_MSA_INTR_SHFT                                                            0x1d
#define HWIO_TCSR_SS_XPU_MSA_INTR0_MSS_MPU_XPU_MSA_INTR_BMSK                                                       0x10000000
#define HWIO_TCSR_SS_XPU_MSA_INTR0_MSS_MPU_XPU_MSA_INTR_SHFT                                                             0x1c
#define HWIO_TCSR_SS_XPU_MSA_INTR0_TLMM_CENTER_XPU_MSA_INTR_BMSK                                                    0x8000000
#define HWIO_TCSR_SS_XPU_MSA_INTR0_TLMM_CENTER_XPU_MSA_INTR_SHFT                                                         0x1b
#define HWIO_TCSR_SS_XPU_MSA_INTR0_SPDM_XPU_MSA_INTR_BMSK                                                           0x4000000
#define HWIO_TCSR_SS_XPU_MSA_INTR0_SPDM_XPU_MSA_INTR_SHFT                                                                0x1a
#define HWIO_TCSR_SS_XPU_MSA_INTR0_PMIC_ARB_XPU_MSA_INTR_BMSK                                                       0x2000000
#define HWIO_TCSR_SS_XPU_MSA_INTR0_PMIC_ARB_XPU_MSA_INTR_SHFT                                                            0x19
#define HWIO_TCSR_SS_XPU_MSA_INTR0_UFS_ICE_XPU_MSA_INTR_BMSK                                                        0x1000000
#define HWIO_TCSR_SS_XPU_MSA_INTR0_UFS_ICE_XPU_MSA_INTR_SHFT                                                             0x18
#define HWIO_TCSR_SS_XPU_MSA_INTR0_QHS_SNOC_XPU_MSA_INTERRUPT_BMSK                                                   0x800000
#define HWIO_TCSR_SS_XPU_MSA_INTR0_QHS_SNOC_XPU_MSA_INTERRUPT_SHFT                                                       0x17
#define HWIO_TCSR_SS_XPU_MSA_INTR0_QHS_QDSS_CFG_MSA_INTERRUPT_BMSK                                                   0x400000
#define HWIO_TCSR_SS_XPU_MSA_INTR0_QHS_QDSS_CFG_MSA_INTERRUPT_SHFT                                                       0x16
#define HWIO_TCSR_SS_XPU_MSA_INTR0_QHS_A2NOC_CFG_XPU_MSA_INTERRUPT_BMSK                                              0x200000
#define HWIO_TCSR_SS_XPU_MSA_INTR0_QHS_A2NOC_CFG_XPU_MSA_INTERRUPT_SHFT                                                  0x15
#define HWIO_TCSR_SS_XPU_MSA_INTR0_QXM_SNOC_MS_XPU_MSA_INTERRUPT_BMSK                                                0x100000
#define HWIO_TCSR_SS_XPU_MSA_INTR0_QXM_SNOC_MS_XPU_MSA_INTERRUPT_SHFT                                                    0x14
#define HWIO_TCSR_SS_XPU_MSA_INTR0_GCC_RPU_XPU_MSA_INTR_BMSK                                                          0x80000
#define HWIO_TCSR_SS_XPU_MSA_INTR0_GCC_RPU_XPU_MSA_INTR_SHFT                                                             0x13
#define HWIO_TCSR_SS_XPU_MSA_INTR0_BIMC_CH1_XPU_MSA_INTR_BMSK                                                         0x40000
#define HWIO_TCSR_SS_XPU_MSA_INTR0_BIMC_CH1_XPU_MSA_INTR_SHFT                                                            0x12
#define HWIO_TCSR_SS_XPU_MSA_INTR0_BIMC_CH0_XPU_MSA_INTR_BMSK                                                         0x20000
#define HWIO_TCSR_SS_XPU_MSA_INTR0_BIMC_CH0_XPU_MSA_INTR_SHFT                                                            0x11
#define HWIO_TCSR_SS_XPU_MSA_INTR0_BIMC_CFG_XPU_MSA_INTR_BMSK                                                         0x10000
#define HWIO_TCSR_SS_XPU_MSA_INTR0_BIMC_CFG_XPU_MSA_INTR_SHFT                                                            0x10
#define HWIO_TCSR_SS_XPU_MSA_INTR0_QXM_MSS_NAV_CE_XPU_MSA_INTR_BMSK                                                    0x8000
#define HWIO_TCSR_SS_XPU_MSA_INTR0_QXM_MSS_NAV_CE_XPU_MSA_INTR_SHFT                                                       0xf
#define HWIO_TCSR_SS_XPU_MSA_INTR0_PIMEM_MPU_MSA_IRQ_BMSK                                                              0x4000
#define HWIO_TCSR_SS_XPU_MSA_INTR0_PIMEM_MPU_MSA_IRQ_SHFT                                                                 0xe
#define HWIO_TCSR_SS_XPU_MSA_INTR0_PIMEM_APU_MSA_IRQ_BMSK                                                              0x2000
#define HWIO_TCSR_SS_XPU_MSA_INTR0_PIMEM_APU_MSA_IRQ_SHFT                                                                 0xd
#define HWIO_TCSR_SS_XPU_MSA_INTR0_TURING_XPU_IRQ_BMSK                                                                 0x1000
#define HWIO_TCSR_SS_XPU_MSA_INTR0_TURING_XPU_IRQ_SHFT                                                                    0xc
#define HWIO_TCSR_SS_XPU_MSA_INTR0_LPASS_XPU_IRQ_APPS_12_BMSK                                                           0x800
#define HWIO_TCSR_SS_XPU_MSA_INTR0_LPASS_XPU_IRQ_APPS_12_SHFT                                                             0xb
#define HWIO_TCSR_SS_XPU_MSA_INTR0_LPASS_XPU_IRQ_APPS_2_BMSK                                                            0x400
#define HWIO_TCSR_SS_XPU_MSA_INTR0_LPASS_XPU_IRQ_APPS_2_SHFT                                                              0xa
#define HWIO_TCSR_SS_XPU_MSA_INTR0_SEC_CTRL_APU_XPU_MSA_INTR_BMSK                                                       0x200
#define HWIO_TCSR_SS_XPU_MSA_INTR0_SEC_CTRL_APU_XPU_MSA_INTR_SHFT                                                         0x9
#define HWIO_TCSR_SS_XPU_MSA_INTR0_DCC_XPU_MSA_INTR_BMSK                                                                0x100
#define HWIO_TCSR_SS_XPU_MSA_INTR0_DCC_XPU_MSA_INTR_SHFT                                                                  0x8
#define HWIO_TCSR_SS_XPU_MSA_INTR0_OCIMEM_RPU_MSA_INTR_BMSK                                                              0x80
#define HWIO_TCSR_SS_XPU_MSA_INTR0_OCIMEM_RPU_MSA_INTR_SHFT                                                               0x7
#define HWIO_TCSR_SS_XPU_MSA_INTR0_CRYPTO0_BAM_XPU_MSA_INTR_BMSK                                                         0x40
#define HWIO_TCSR_SS_XPU_MSA_INTR0_CRYPTO0_BAM_XPU_MSA_INTR_SHFT                                                          0x6
#define HWIO_TCSR_SS_XPU_MSA_INTR0_O_TCSR_MUTEX_MSA_INTR_BMSK                                                            0x20
#define HWIO_TCSR_SS_XPU_MSA_INTR0_O_TCSR_MUTEX_MSA_INTR_SHFT                                                             0x5
#define HWIO_TCSR_SS_XPU_MSA_INTR0_APSS_MSA_INTR_BMSK                                                                    0x10
#define HWIO_TCSR_SS_XPU_MSA_INTR0_APSS_MSA_INTR_SHFT                                                                     0x4
#define HWIO_TCSR_SS_XPU_MSA_INTR0_O_TCSR_REGS_MSA_INTR_BMSK                                                              0x8
#define HWIO_TCSR_SS_XPU_MSA_INTR0_O_TCSR_REGS_MSA_INTR_SHFT                                                              0x3
#define HWIO_TCSR_SS_XPU_MSA_INTR0_MMSS_NOC_XPU_MSA_INTR_BMSK                                                             0x4
#define HWIO_TCSR_SS_XPU_MSA_INTR0_MMSS_NOC_XPU_MSA_INTR_SHFT                                                             0x2
#define HWIO_TCSR_SS_XPU_MSA_INTR0_RESERVE_1_BMSK                                                                         0x2
#define HWIO_TCSR_SS_XPU_MSA_INTR0_RESERVE_1_SHFT                                                                         0x1
#define HWIO_TCSR_SS_XPU_MSA_INTR0_MMSS_QM_XPU_MSA_INTR_BMSK                                                              0x1
#define HWIO_TCSR_SS_XPU_MSA_INTR0_MMSS_QM_XPU_MSA_INTR_SHFT                                                              0x0

#define HWIO_TCSR_SS_XPU_MSA_INTR1_ADDR                                                                            (TCSR_TCSR_REGS_REG_BASE      + 0x00006004)
#define HWIO_TCSR_SS_XPU_MSA_INTR1_RMSK                                                                               0x3ffff
#define HWIO_TCSR_SS_XPU_MSA_INTR1_IN          \
        in_dword_masked(HWIO_TCSR_SS_XPU_MSA_INTR1_ADDR, HWIO_TCSR_SS_XPU_MSA_INTR1_RMSK)
#define HWIO_TCSR_SS_XPU_MSA_INTR1_INM(m)      \
        in_dword_masked(HWIO_TCSR_SS_XPU_MSA_INTR1_ADDR, m)
#define HWIO_TCSR_SS_XPU_MSA_INTR1_LPASS_IRQ_OUT_SECURITY_22_BMSK                                                     0x20000
#define HWIO_TCSR_SS_XPU_MSA_INTR1_LPASS_IRQ_OUT_SECURITY_22_SHFT                                                        0x11
#define HWIO_TCSR_SS_XPU_MSA_INTR1_MMSS_XPU_MMSS_CC_XPU_MSA_INTR_BMSK                                                 0x10000
#define HWIO_TCSR_SS_XPU_MSA_INTR1_MMSS_XPU_MMSS_CC_XPU_MSA_INTR_SHFT                                                    0x10
#define HWIO_TCSR_SS_XPU_MSA_INTR1_TLMM_NORTH_XPU_MSA_INTR_BMSK                                                        0x8000
#define HWIO_TCSR_SS_XPU_MSA_INTR1_TLMM_NORTH_XPU_MSA_INTR_SHFT                                                           0xf
#define HWIO_TCSR_SS_XPU_MSA_INTR1_SKL_XPU_MSA_INTR_BMSK                                                               0x4000
#define HWIO_TCSR_SS_XPU_MSA_INTR1_SKL_XPU_MSA_INTR_SHFT                                                                  0xe
#define HWIO_TCSR_SS_XPU_MSA_INTR1_ANOC1_MPU_XPU_MSA_INTR_BMSK                                                         0x2000
#define HWIO_TCSR_SS_XPU_MSA_INTR1_ANOC1_MPU_XPU_MSA_INTR_SHFT                                                            0xd
#define HWIO_TCSR_SS_XPU_MSA_INTR1_ANOC2_MPU_XPU_MSA_INTR_BMSK                                                         0x1000
#define HWIO_TCSR_SS_XPU_MSA_INTR1_ANOC2_MPU_XPU_MSA_INTR_SHFT                                                            0xc
#define HWIO_TCSR_SS_XPU_MSA_INTR1_IPA_0_XPU_MSA_INTR_BMSK                                                              0x800
#define HWIO_TCSR_SS_XPU_MSA_INTR1_IPA_0_XPU_MSA_INTR_SHFT                                                                0xb
#define HWIO_TCSR_SS_XPU_MSA_INTR1_MSS_Q6_MPU_XPU_MSA_INTR_BMSK                                                         0x400
#define HWIO_TCSR_SS_XPU_MSA_INTR1_MSS_Q6_MPU_XPU_MSA_INTR_SHFT                                                           0xa
#define HWIO_TCSR_SS_XPU_MSA_INTR1_RPM_MPU_MSA_INTR_BMSK                                                                0x200
#define HWIO_TCSR_SS_XPU_MSA_INTR1_RPM_MPU_MSA_INTR_SHFT                                                                  0x9
#define HWIO_TCSR_SS_XPU_MSA_INTR1_LPASS_IRQ_OUT_SECURITY_20_BMSK                                                       0x100
#define HWIO_TCSR_SS_XPU_MSA_INTR1_LPASS_IRQ_OUT_SECURITY_20_SHFT                                                         0x8
#define HWIO_TCSR_SS_XPU_MSA_INTR1_MDSS_XPU_XPU_MSA_INTR_BMSK                                                            0x80
#define HWIO_TCSR_SS_XPU_MSA_INTR1_MDSS_XPU_XPU_MSA_INTR_SHFT                                                             0x7
#define HWIO_TCSR_SS_XPU_MSA_INTR1_QDSS_BAM_XPU_MSA_INTR_BMSK                                                            0x40
#define HWIO_TCSR_SS_XPU_MSA_INTR1_QDSS_BAM_XPU_MSA_INTR_SHFT                                                             0x6
#define HWIO_TCSR_SS_XPU_MSA_INTR1_MPM2_XPU_MSA_INTR_BMSK                                                                0x20
#define HWIO_TCSR_SS_XPU_MSA_INTR1_MPM2_XPU_MSA_INTR_SHFT                                                                 0x5
#define HWIO_TCSR_SS_XPU_MSA_INTR1_DDR_REGS_CFG_XPU_MSA_INTR_BMSK                                                        0x10
#define HWIO_TCSR_SS_XPU_MSA_INTR1_DDR_REGS_CFG_XPU_MSA_INTR_SHFT                                                         0x4
#define HWIO_TCSR_SS_XPU_MSA_INTR1_TLMM_SOUTH_XPU_MSA_INTR_BMSK                                                           0x8
#define HWIO_TCSR_SS_XPU_MSA_INTR1_TLMM_SOUTH_XPU_MSA_INTR_SHFT                                                           0x3
#define HWIO_TCSR_SS_XPU_MSA_INTR1_PERIPH_SS_BLSP2_BLSP_BAM_XPU_MSA_INTR_BMSK                                             0x4
#define HWIO_TCSR_SS_XPU_MSA_INTR1_PERIPH_SS_BLSP2_BLSP_BAM_XPU_MSA_INTR_SHFT                                             0x2
#define HWIO_TCSR_SS_XPU_MSA_INTR1_PERIPH_SS_BLSP1_BLSP_BAM_XPU_MSA_INTR_BMSK                                             0x2
#define HWIO_TCSR_SS_XPU_MSA_INTR1_PERIPH_SS_BLSP1_BLSP_BAM_XPU_MSA_INTR_SHFT                                             0x1
#define HWIO_TCSR_SS_XPU_MSA_INTR1_OCIMEM_RPU_MSA_INTR_BMSK                                                               0x1
#define HWIO_TCSR_SS_XPU_MSA_INTR1_OCIMEM_RPU_MSA_INTR_SHFT                                                               0x0

#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_ADDR                                                                     (TCSR_TCSR_REGS_REG_BASE      + 0x00006040)
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_RMSK                                                                     0xffffffff
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_IN          \
        in_dword_masked(HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_ADDR, HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_RMSK)
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_INM(m)      \
        in_dword_masked(HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_ADDR, m)
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_OUT(v)      \
        out_dword(HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_ADDR,v)
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_ADDR,m,v,HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_IN)
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_RESERVE_31_BMSK                                                          0x80000000
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_RESERVE_31_SHFT                                                                0x1f
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_BOOT_ROM_MSA_INTR_ENABLE_BMSK                                            0x40000000
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_BOOT_ROM_MSA_INTR_ENABLE_SHFT                                                  0x1e
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_SDC1_ICE_XPU_MSA_INTR_ENABLE_BMSK                                        0x20000000
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_SDC1_ICE_XPU_MSA_INTR_ENABLE_SHFT                                              0x1d
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_MSS_MPU_XPU_MSA_INTR_ENABLE_BMSK                                         0x10000000
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_MSS_MPU_XPU_MSA_INTR_ENABLE_SHFT                                               0x1c
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_TLMM_CENTER_XPU_MSA_INTR_ENABLE_BMSK                                      0x8000000
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_TLMM_CENTER_XPU_MSA_INTR_ENABLE_SHFT                                           0x1b
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_SPDM_XPU_MSA_INTR_ENABLE_BMSK                                             0x4000000
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_SPDM_XPU_MSA_INTR_ENABLE_SHFT                                                  0x1a
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_PMIC_ARB_XPU_MSA_INTR_ENABLE_BMSK                                         0x2000000
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_PMIC_ARB_XPU_MSA_INTR_ENABLE_SHFT                                              0x19
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_UFS_ICE_XPU_MSA_INTR_ENABLE_BMSK                                          0x1000000
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_UFS_ICE_XPU_MSA_INTR_ENABLE_SHFT                                               0x18
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_QHS_SNOC_XPU_MSA_INTERRUPT_ENABLE_BMSK                                     0x800000
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_QHS_SNOC_XPU_MSA_INTERRUPT_ENABLE_SHFT                                         0x17
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_QHS_QDSS_CFG_MSA_INTERRUPT_ENABLE_BMSK                                     0x400000
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_QHS_QDSS_CFG_MSA_INTERRUPT_ENABLE_SHFT                                         0x16
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_QHS_A2NOC_CFG_XPU_MSA_INTERRUPT_ENABLE_BMSK                                0x200000
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_QHS_A2NOC_CFG_XPU_MSA_INTERRUPT_ENABLE_SHFT                                    0x15
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_QXM_SNOC_MS_XPU_MSA_INTERRUPT_ENABLE_BMSK                                  0x100000
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_QXM_SNOC_MS_XPU_MSA_INTERRUPT_ENABLE_SHFT                                      0x14
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_GCC_RPU_XPU_MSA_INTR_ENABLE_BMSK                                            0x80000
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_GCC_RPU_XPU_MSA_INTR_ENABLE_SHFT                                               0x13
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_BIMC_CH1_XPU_MSA_INTR_ENABLE_BMSK                                           0x40000
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_BIMC_CH1_XPU_MSA_INTR_ENABLE_SHFT                                              0x12
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_BIMC_CH0_XPU_MSA_INTR_ENABLE_BMSK                                           0x20000
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_BIMC_CH0_XPU_MSA_INTR_ENABLE_SHFT                                              0x11
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_BIMC_CFG_XPU_MSA_INTR_ENABLE_BMSK                                           0x10000
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_BIMC_CFG_XPU_MSA_INTR_ENABLE_SHFT                                              0x10
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_QXM_MSS_NAV_CE_XPU_MSA_INTR_ENABLE_BMSK                                      0x8000
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_QXM_MSS_NAV_CE_XPU_MSA_INTR_ENABLE_SHFT                                         0xf
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_PIMEM_MPU_MSA_IRQ_ENABLE_BMSK                                                0x4000
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_PIMEM_MPU_MSA_IRQ_ENABLE_SHFT                                                   0xe
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_PIMEM_APU_MSA_IRQ_ENABLE_BMSK                                                0x2000
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_PIMEM_APU_MSA_IRQ_ENABLE_SHFT                                                   0xd
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_TURING_XPU_ENABLE_BMSK                                                       0x1000
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_TURING_XPU_ENABLE_SHFT                                                          0xc
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_LPASS_XPU_IRQ_APPS_12_ENABLE_BMSK                                             0x800
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_LPASS_XPU_IRQ_APPS_12_ENABLE_SHFT                                               0xb
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_LPASS_XPU_IRQ_APPS_2_ENABLE_BMSK                                              0x400
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_LPASS_XPU_IRQ_APPS_2_ENABLE_SHFT                                                0xa
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_SEC_CTRL_APU_XPU_MSA_INTR_ENABLE_BMSK                                         0x200
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_SEC_CTRL_APU_XPU_MSA_INTR_ENABLE_SHFT                                           0x9
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_DCC_XPU_MSA_INTR_ENABLE_BMSK                                                  0x100
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_DCC_XPU_MSA_INTR_ENABLE_SHFT                                                    0x8
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_OCIMEM_RPU_MSA_INTR_ENABLE_BMSK                                                0x80
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_OCIMEM_RPU_MSA_INTR_ENABLE_SHFT                                                 0x7
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_CRYPTO0_BAM_XPU_MSA_INTR_ENABLE_BMSK                                           0x40
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_CRYPTO0_BAM_XPU_MSA_INTR_ENABLE_SHFT                                            0x6
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_O_TCSR_MUTEX_MSA_INTR_ENABLE_BMSK                                              0x20
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_O_TCSR_MUTEX_MSA_INTR_ENABLE_SHFT                                               0x5
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_APSS_MSA_INTR_ENABLE_BMSK                                                      0x10
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_APSS_MSA_INTR_ENABLE_SHFT                                                       0x4
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_O_TCSR_REGS_MSA_INTR_ENABLE_BMSK                                                0x8
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_O_TCSR_REGS_MSA_INTR_ENABLE_SHFT                                                0x3
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_MMSS_NOC_XPU_MSA_INTR_ENABLE_BMSK                                               0x4
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_MMSS_NOC_XPU_MSA_INTR_ENABLE_SHFT                                               0x2
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_RESERVE_1_BMSK                                                                  0x2
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_RESERVE_1_SHFT                                                                  0x1
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_MMSS_QM_XPU_MSA_INTR_ENABLE_BMSK                                                0x1
#define HWIO_TCSR_SS_XPU_MSA_INTR0_ENABLE_MMSS_QM_XPU_MSA_INTR_ENABLE_SHFT                                                0x0

#define HWIO_TCSR_SS_XPU_MSA_INTR1_ENABLE_ADDR                                                                     (TCSR_TCSR_REGS_REG_BASE      + 0x00006044)
#define HWIO_TCSR_SS_XPU_MSA_INTR1_ENABLE_RMSK                                                                        0x3ffff
#define HWIO_TCSR_SS_XPU_MSA_INTR1_ENABLE_IN          \
        in_dword_masked(HWIO_TCSR_SS_XPU_MSA_INTR1_ENABLE_ADDR, HWIO_TCSR_SS_XPU_MSA_INTR1_ENABLE_RMSK)
#define HWIO_TCSR_SS_XPU_MSA_INTR1_ENABLE_INM(m)      \
        in_dword_masked(HWIO_TCSR_SS_XPU_MSA_INTR1_ENABLE_ADDR, m)
#define HWIO_TCSR_SS_XPU_MSA_INTR1_ENABLE_OUT(v)      \
        out_dword(HWIO_TCSR_SS_XPU_MSA_INTR1_ENABLE_ADDR,v)
#define HWIO_TCSR_SS_XPU_MSA_INTR1_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SS_XPU_MSA_INTR1_ENABLE_ADDR,m,v,HWIO_TCSR_SS_XPU_MSA_INTR1_ENABLE_IN)
#define HWIO_TCSR_SS_XPU_MSA_INTR1_ENABLE_LPASS_IRQ_OUT_SECURITY_22_ENABLE_BMSK                                       0x20000
#define HWIO_TCSR_SS_XPU_MSA_INTR1_ENABLE_LPASS_IRQ_OUT_SECURITY_22_ENABLE_SHFT                                          0x11
#define HWIO_TCSR_SS_XPU_MSA_INTR1_ENABLE_MMSS_XPU_MMSS_CC_XPU_MSA_INTR_ENABLE_BMSK                                   0x10000
#define HWIO_TCSR_SS_XPU_MSA_INTR1_ENABLE_MMSS_XPU_MMSS_CC_XPU_MSA_INTR_ENABLE_SHFT                                      0x10
#define HWIO_TCSR_SS_XPU_MSA_INTR1_ENABLE_TLMM_NORTH_XPU_MSA_INTR_ENABLE_BMSK                                          0x8000
#define HWIO_TCSR_SS_XPU_MSA_INTR1_ENABLE_TLMM_NORTH_XPU_MSA_INTR_ENABLE_SHFT                                             0xf
#define HWIO_TCSR_SS_XPU_MSA_INTR1_ENABLE_SKL_XPU_MSA_INTR_ENABLE_BMSK                                                 0x4000
#define HWIO_TCSR_SS_XPU_MSA_INTR1_ENABLE_SKL_XPU_MSA_INTR_ENABLE_SHFT                                                    0xe
#define HWIO_TCSR_SS_XPU_MSA_INTR1_ENABLE_ANOC1_MPU_XPU_MSA_INTR_ENABLE_BMSK                                           0x2000
#define HWIO_TCSR_SS_XPU_MSA_INTR1_ENABLE_ANOC1_MPU_XPU_MSA_INTR_ENABLE_SHFT                                              0xd
#define HWIO_TCSR_SS_XPU_MSA_INTR1_ENABLE_ANOC2_MPU_XPU_MSA_INTR_ENABLE_BMSK                                           0x1000
#define HWIO_TCSR_SS_XPU_MSA_INTR1_ENABLE_ANOC2_MPU_XPU_MSA_INTR_ENABLE_SHFT                                              0xc
#define HWIO_TCSR_SS_XPU_MSA_INTR1_ENABLE_IPA_0_XPU_MSA_INTR_ENABLE_BMSK                                                0x800
#define HWIO_TCSR_SS_XPU_MSA_INTR1_ENABLE_IPA_0_XPU_MSA_INTR_ENABLE_SHFT                                                  0xb
#define HWIO_TCSR_SS_XPU_MSA_INTR1_ENABLE_MSS_Q6_MPU_XPU_MSA_INTR_ENABLE_BMSK                                           0x400
#define HWIO_TCSR_SS_XPU_MSA_INTR1_ENABLE_MSS_Q6_MPU_XPU_MSA_INTR_ENABLE_SHFT                                             0xa
#define HWIO_TCSR_SS_XPU_MSA_INTR1_ENABLE_RPM_MPU_MSA_INTR_ENABLE_BMSK                                                  0x200
#define HWIO_TCSR_SS_XPU_MSA_INTR1_ENABLE_RPM_MPU_MSA_INTR_ENABLE_SHFT                                                    0x9
#define HWIO_TCSR_SS_XPU_MSA_INTR1_ENABLE_LPASS_IRQ_OUT_SECURITY_20_ENABLE_BMSK                                         0x100
#define HWIO_TCSR_SS_XPU_MSA_INTR1_ENABLE_LPASS_IRQ_OUT_SECURITY_20_ENABLE_SHFT                                           0x8
#define HWIO_TCSR_SS_XPU_MSA_INTR1_ENABLE_MDSS_XPU_XPU_MSA_INTR_ENABLE_BMSK                                              0x80
#define HWIO_TCSR_SS_XPU_MSA_INTR1_ENABLE_MDSS_XPU_XPU_MSA_INTR_ENABLE_SHFT                                               0x7
#define HWIO_TCSR_SS_XPU_MSA_INTR1_ENABLE_QDSS_BAM_XPU_MSA_INTR_ENABLE_BMSK                                              0x40
#define HWIO_TCSR_SS_XPU_MSA_INTR1_ENABLE_QDSS_BAM_XPU_MSA_INTR_ENABLE_SHFT                                               0x6
#define HWIO_TCSR_SS_XPU_MSA_INTR1_ENABLE_MPM2_XPU_MSA_INTR_ENABLE_BMSK                                                  0x20
#define HWIO_TCSR_SS_XPU_MSA_INTR1_ENABLE_MPM2_XPU_MSA_INTR_ENABLE_SHFT                                                   0x5
#define HWIO_TCSR_SS_XPU_MSA_INTR1_ENABLE_DDR_REGS_CFG_XPU_MSA_INTR_ENABLE_BMSK                                          0x10
#define HWIO_TCSR_SS_XPU_MSA_INTR1_ENABLE_DDR_REGS_CFG_XPU_MSA_INTR_ENABLE_SHFT                                           0x4
#define HWIO_TCSR_SS_XPU_MSA_INTR1_ENABLE_TLMM_SOUTH_XPU_MSA_INTR_ENABLE_BMSK                                             0x8
#define HWIO_TCSR_SS_XPU_MSA_INTR1_ENABLE_TLMM_SOUTH_XPU_MSA_INTR_ENABLE_SHFT                                             0x3
#define HWIO_TCSR_SS_XPU_MSA_INTR1_ENABLE_PERIPH_SS_BLSP2_BLSP_BAM_XPU_MSA_INTR_ENABLE_BMSK                               0x4
#define HWIO_TCSR_SS_XPU_MSA_INTR1_ENABLE_PERIPH_SS_BLSP2_BLSP_BAM_XPU_MSA_INTR_ENABLE_SHFT                               0x2
#define HWIO_TCSR_SS_XPU_MSA_INTR1_ENABLE_PERIPH_SS_BLSP1_BLSP_BAM_XPU_MSA_INTR_ENABLE_BMSK                               0x2
#define HWIO_TCSR_SS_XPU_MSA_INTR1_ENABLE_PERIPH_SS_BLSP1_BLSP_BAM_XPU_MSA_INTR_ENABLE_SHFT                               0x1
#define HWIO_TCSR_SS_XPU_MSA_INTR1_ENABLE_OCIMEM_RPU_MSA_INTR_ENABLE_BMSK                                                 0x1
#define HWIO_TCSR_SS_XPU_MSA_INTR1_ENABLE_OCIMEM_RPU_MSA_INTR_ENABLE_SHFT                                                 0x0

#define HWIO_TCSR_SPDM_CNT_CLK_CTRL_ADDR                                                                           (TCSR_TCSR_REGS_REG_BASE      + 0x00007000)
#define HWIO_TCSR_SPDM_CNT_CLK_CTRL_RMSK                                                                               0xffff
#define HWIO_TCSR_SPDM_CNT_CLK_CTRL_IN          \
        in_dword_masked(HWIO_TCSR_SPDM_CNT_CLK_CTRL_ADDR, HWIO_TCSR_SPDM_CNT_CLK_CTRL_RMSK)
#define HWIO_TCSR_SPDM_CNT_CLK_CTRL_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPDM_CNT_CLK_CTRL_ADDR, m)
#define HWIO_TCSR_SPDM_CNT_CLK_CTRL_OUT(v)      \
        out_dword(HWIO_TCSR_SPDM_CNT_CLK_CTRL_ADDR,v)
#define HWIO_TCSR_SPDM_CNT_CLK_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPDM_CNT_CLK_CTRL_ADDR,m,v,HWIO_TCSR_SPDM_CNT_CLK_CTRL_IN)
#define HWIO_TCSR_SPDM_CNT_CLK_CTRL_SPDM_CNT_CLK_MUX_SEL_BMSK                                                          0xffff
#define HWIO_TCSR_SPDM_CNT_CLK_CTRL_SPDM_CNT_CLK_MUX_SEL_SHFT                                                             0x0

#define HWIO_TCSR_SPDM_DLY_FIFO_EN_ADDR                                                                            (TCSR_TCSR_REGS_REG_BASE      + 0x00007004)
#define HWIO_TCSR_SPDM_DLY_FIFO_EN_RMSK                                                                            0xffffffff
#define HWIO_TCSR_SPDM_DLY_FIFO_EN_IN          \
        in_dword_masked(HWIO_TCSR_SPDM_DLY_FIFO_EN_ADDR, HWIO_TCSR_SPDM_DLY_FIFO_EN_RMSK)
#define HWIO_TCSR_SPDM_DLY_FIFO_EN_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPDM_DLY_FIFO_EN_ADDR, m)
#define HWIO_TCSR_SPDM_DLY_FIFO_EN_OUT(v)      \
        out_dword(HWIO_TCSR_SPDM_DLY_FIFO_EN_ADDR,v)
#define HWIO_TCSR_SPDM_DLY_FIFO_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPDM_DLY_FIFO_EN_ADDR,m,v,HWIO_TCSR_SPDM_DLY_FIFO_EN_IN)
#define HWIO_TCSR_SPDM_DLY_FIFO_EN_SPDM_DLY_FIFO_EN_BMSK                                                           0xffffffff
#define HWIO_TCSR_SPDM_DLY_FIFO_EN_SPDM_DLY_FIFO_EN_SHFT                                                                  0x0

#define HWIO_TCSR_SPDM_STG1_MUX_SEL_ADDR                                                                           (TCSR_TCSR_REGS_REG_BASE      + 0x00007008)
#define HWIO_TCSR_SPDM_STG1_MUX_SEL_RMSK                                                                               0xffff
#define HWIO_TCSR_SPDM_STG1_MUX_SEL_IN          \
        in_dword_masked(HWIO_TCSR_SPDM_STG1_MUX_SEL_ADDR, HWIO_TCSR_SPDM_STG1_MUX_SEL_RMSK)
#define HWIO_TCSR_SPDM_STG1_MUX_SEL_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPDM_STG1_MUX_SEL_ADDR, m)
#define HWIO_TCSR_SPDM_STG1_MUX_SEL_OUT(v)      \
        out_dword(HWIO_TCSR_SPDM_STG1_MUX_SEL_ADDR,v)
#define HWIO_TCSR_SPDM_STG1_MUX_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPDM_STG1_MUX_SEL_ADDR,m,v,HWIO_TCSR_SPDM_STG1_MUX_SEL_IN)
#define HWIO_TCSR_SPDM_STG1_MUX_SEL_SPDM_STG1_MUX_SEL_BMSK                                                             0xffff
#define HWIO_TCSR_SPDM_STG1_MUX_SEL_SPDM_STG1_MUX_SEL_SHFT                                                                0x0

#define HWIO_TCSR_SPDM_STG2_A_MUX_SEL_ADDR                                                                         (TCSR_TCSR_REGS_REG_BASE      + 0x0000700c)
#define HWIO_TCSR_SPDM_STG2_A_MUX_SEL_RMSK                                                                         0xffffffff
#define HWIO_TCSR_SPDM_STG2_A_MUX_SEL_IN          \
        in_dword_masked(HWIO_TCSR_SPDM_STG2_A_MUX_SEL_ADDR, HWIO_TCSR_SPDM_STG2_A_MUX_SEL_RMSK)
#define HWIO_TCSR_SPDM_STG2_A_MUX_SEL_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPDM_STG2_A_MUX_SEL_ADDR, m)
#define HWIO_TCSR_SPDM_STG2_A_MUX_SEL_OUT(v)      \
        out_dword(HWIO_TCSR_SPDM_STG2_A_MUX_SEL_ADDR,v)
#define HWIO_TCSR_SPDM_STG2_A_MUX_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPDM_STG2_A_MUX_SEL_ADDR,m,v,HWIO_TCSR_SPDM_STG2_A_MUX_SEL_IN)
#define HWIO_TCSR_SPDM_STG2_A_MUX_SEL_SPDM_STG2_A_MUX_SEL_BMSK                                                     0xffffffff
#define HWIO_TCSR_SPDM_STG2_A_MUX_SEL_SPDM_STG2_A_MUX_SEL_SHFT                                                            0x0

#define HWIO_TCSR_SPDM_STG2_B_MUX_SEL_ADDR                                                                         (TCSR_TCSR_REGS_REG_BASE      + 0x00007010)
#define HWIO_TCSR_SPDM_STG2_B_MUX_SEL_RMSK                                                                         0xffffffff
#define HWIO_TCSR_SPDM_STG2_B_MUX_SEL_IN          \
        in_dword_masked(HWIO_TCSR_SPDM_STG2_B_MUX_SEL_ADDR, HWIO_TCSR_SPDM_STG2_B_MUX_SEL_RMSK)
#define HWIO_TCSR_SPDM_STG2_B_MUX_SEL_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPDM_STG2_B_MUX_SEL_ADDR, m)
#define HWIO_TCSR_SPDM_STG2_B_MUX_SEL_OUT(v)      \
        out_dword(HWIO_TCSR_SPDM_STG2_B_MUX_SEL_ADDR,v)
#define HWIO_TCSR_SPDM_STG2_B_MUX_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPDM_STG2_B_MUX_SEL_ADDR,m,v,HWIO_TCSR_SPDM_STG2_B_MUX_SEL_IN)
#define HWIO_TCSR_SPDM_STG2_B_MUX_SEL_SPDM_STG2_B_MUX_SEL_BMSK                                                     0xffffffff
#define HWIO_TCSR_SPDM_STG2_B_MUX_SEL_SPDM_STG2_B_MUX_SEL_SHFT                                                            0x0

#define HWIO_TCSR_SPDM_STG3_A_MUX_SEL_ADDR                                                                         (TCSR_TCSR_REGS_REG_BASE      + 0x00007014)
#define HWIO_TCSR_SPDM_STG3_A_MUX_SEL_RMSK                                                                         0xffffffff
#define HWIO_TCSR_SPDM_STG3_A_MUX_SEL_IN          \
        in_dword_masked(HWIO_TCSR_SPDM_STG3_A_MUX_SEL_ADDR, HWIO_TCSR_SPDM_STG3_A_MUX_SEL_RMSK)
#define HWIO_TCSR_SPDM_STG3_A_MUX_SEL_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPDM_STG3_A_MUX_SEL_ADDR, m)
#define HWIO_TCSR_SPDM_STG3_A_MUX_SEL_OUT(v)      \
        out_dword(HWIO_TCSR_SPDM_STG3_A_MUX_SEL_ADDR,v)
#define HWIO_TCSR_SPDM_STG3_A_MUX_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPDM_STG3_A_MUX_SEL_ADDR,m,v,HWIO_TCSR_SPDM_STG3_A_MUX_SEL_IN)
#define HWIO_TCSR_SPDM_STG3_A_MUX_SEL_SPDM_STG3_A_MUX_SEL_BMSK                                                     0xffffffff
#define HWIO_TCSR_SPDM_STG3_A_MUX_SEL_SPDM_STG3_A_MUX_SEL_SHFT                                                            0x0

#define HWIO_TCSR_SPDM_STG3_B_MUX_SEL_ADDR                                                                         (TCSR_TCSR_REGS_REG_BASE      + 0x00007018)
#define HWIO_TCSR_SPDM_STG3_B_MUX_SEL_RMSK                                                                         0xffffffff
#define HWIO_TCSR_SPDM_STG3_B_MUX_SEL_IN          \
        in_dword_masked(HWIO_TCSR_SPDM_STG3_B_MUX_SEL_ADDR, HWIO_TCSR_SPDM_STG3_B_MUX_SEL_RMSK)
#define HWIO_TCSR_SPDM_STG3_B_MUX_SEL_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPDM_STG3_B_MUX_SEL_ADDR, m)
#define HWIO_TCSR_SPDM_STG3_B_MUX_SEL_OUT(v)      \
        out_dword(HWIO_TCSR_SPDM_STG3_B_MUX_SEL_ADDR,v)
#define HWIO_TCSR_SPDM_STG3_B_MUX_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPDM_STG3_B_MUX_SEL_ADDR,m,v,HWIO_TCSR_SPDM_STG3_B_MUX_SEL_IN)
#define HWIO_TCSR_SPDM_STG3_B_MUX_SEL_SPDM_STG3_B_MUX_SEL_BMSK                                                     0xffffffff
#define HWIO_TCSR_SPDM_STG3_B_MUX_SEL_SPDM_STG3_B_MUX_SEL_SHFT                                                            0x0

#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL0_ADDR                                                                       (TCSR_TCSR_REGS_REG_BASE      + 0x0000701c)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL0_RMSK                                                                       0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL0_IN          \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL0_ADDR, HWIO_TCSR_SPDM_WRP_RT_INTF_CTL0_RMSK)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL0_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL0_ADDR, m)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL0_OUT(v)      \
        out_dword(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL0_ADDR,v)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL0_ADDR,m,v,HWIO_TCSR_SPDM_WRP_RT_INTF_CTL0_IN)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL0_SPDM_WRP_RT_INTF_CTL0_BMSK                                                 0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL0_SPDM_WRP_RT_INTF_CTL0_SHFT                                                        0x0

#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL1_ADDR                                                                       (TCSR_TCSR_REGS_REG_BASE      + 0x00007020)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL1_RMSK                                                                       0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL1_IN          \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL1_ADDR, HWIO_TCSR_SPDM_WRP_RT_INTF_CTL1_RMSK)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL1_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL1_ADDR, m)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL1_OUT(v)      \
        out_dword(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL1_ADDR,v)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL1_ADDR,m,v,HWIO_TCSR_SPDM_WRP_RT_INTF_CTL1_IN)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL1_SPDM_WRP_RT_INTF_CTL1_BMSK                                                 0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL1_SPDM_WRP_RT_INTF_CTL1_SHFT                                                        0x0

#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL2_ADDR                                                                       (TCSR_TCSR_REGS_REG_BASE      + 0x00007024)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL2_RMSK                                                                       0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL2_IN          \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL2_ADDR, HWIO_TCSR_SPDM_WRP_RT_INTF_CTL2_RMSK)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL2_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL2_ADDR, m)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL2_OUT(v)      \
        out_dword(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL2_ADDR,v)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL2_ADDR,m,v,HWIO_TCSR_SPDM_WRP_RT_INTF_CTL2_IN)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL2_SPDM_WRP_RT_INTF_CTL2_BMSK                                                 0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL2_SPDM_WRP_RT_INTF_CTL2_SHFT                                                        0x0

#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL3_ADDR                                                                       (TCSR_TCSR_REGS_REG_BASE      + 0x00007028)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL3_RMSK                                                                       0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL3_IN          \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL3_ADDR, HWIO_TCSR_SPDM_WRP_RT_INTF_CTL3_RMSK)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL3_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL3_ADDR, m)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL3_OUT(v)      \
        out_dword(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL3_ADDR,v)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL3_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL3_ADDR,m,v,HWIO_TCSR_SPDM_WRP_RT_INTF_CTL3_IN)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL3_SPDM_WRP_RT_INTF_CTL3_BMSK                                                 0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL3_SPDM_WRP_RT_INTF_CTL3_SHFT                                                        0x0

#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL4_ADDR                                                                       (TCSR_TCSR_REGS_REG_BASE      + 0x0000702c)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL4_RMSK                                                                       0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL4_IN          \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL4_ADDR, HWIO_TCSR_SPDM_WRP_RT_INTF_CTL4_RMSK)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL4_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL4_ADDR, m)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL4_OUT(v)      \
        out_dword(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL4_ADDR,v)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL4_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL4_ADDR,m,v,HWIO_TCSR_SPDM_WRP_RT_INTF_CTL4_IN)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL4_SPDM_WRP_RT_INTF_CTL4_BMSK                                                 0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL4_SPDM_WRP_RT_INTF_CTL4_SHFT                                                        0x0

#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL5_ADDR                                                                       (TCSR_TCSR_REGS_REG_BASE      + 0x00007030)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL5_RMSK                                                                       0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL5_IN          \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL5_ADDR, HWIO_TCSR_SPDM_WRP_RT_INTF_CTL5_RMSK)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL5_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL5_ADDR, m)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL5_OUT(v)      \
        out_dword(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL5_ADDR,v)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL5_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL5_ADDR,m,v,HWIO_TCSR_SPDM_WRP_RT_INTF_CTL5_IN)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL5_SPDM_WRP_RT_INTF_CTL5_BMSK                                                 0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL5_SPDM_WRP_RT_INTF_CTL5_SHFT                                                        0x0

#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL6_ADDR                                                                       (TCSR_TCSR_REGS_REG_BASE      + 0x00007034)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL6_RMSK                                                                       0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL6_IN          \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL6_ADDR, HWIO_TCSR_SPDM_WRP_RT_INTF_CTL6_RMSK)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL6_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL6_ADDR, m)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL6_OUT(v)      \
        out_dword(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL6_ADDR,v)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL6_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL6_ADDR,m,v,HWIO_TCSR_SPDM_WRP_RT_INTF_CTL6_IN)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL6_SPDM_WRP_RT_INTF_CTL6_BMSK                                                 0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL6_SPDM_WRP_RT_INTF_CTL6_SHFT                                                        0x0

#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL7_ADDR                                                                       (TCSR_TCSR_REGS_REG_BASE      + 0x00007038)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL7_RMSK                                                                       0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL7_IN          \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL7_ADDR, HWIO_TCSR_SPDM_WRP_RT_INTF_CTL7_RMSK)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL7_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL7_ADDR, m)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL7_OUT(v)      \
        out_dword(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL7_ADDR,v)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL7_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL7_ADDR,m,v,HWIO_TCSR_SPDM_WRP_RT_INTF_CTL7_IN)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL7_SPDM_WRP_RT_INTF_CTL7_BMSK                                                 0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL7_SPDM_WRP_RT_INTF_CTL7_SHFT                                                        0x0

#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL8_ADDR                                                                       (TCSR_TCSR_REGS_REG_BASE      + 0x0000703c)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL8_RMSK                                                                       0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL8_IN          \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL8_ADDR, HWIO_TCSR_SPDM_WRP_RT_INTF_CTL8_RMSK)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL8_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL8_ADDR, m)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL8_OUT(v)      \
        out_dword(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL8_ADDR,v)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL8_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL8_ADDR,m,v,HWIO_TCSR_SPDM_WRP_RT_INTF_CTL8_IN)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL8_SPDM_WRP_RT_INTF_CTL8_BMSK                                                 0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL8_SPDM_WRP_RT_INTF_CTL8_SHFT                                                        0x0

#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL9_ADDR                                                                       (TCSR_TCSR_REGS_REG_BASE      + 0x00007040)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL9_RMSK                                                                       0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL9_IN          \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL9_ADDR, HWIO_TCSR_SPDM_WRP_RT_INTF_CTL9_RMSK)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL9_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL9_ADDR, m)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL9_OUT(v)      \
        out_dword(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL9_ADDR,v)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL9_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL9_ADDR,m,v,HWIO_TCSR_SPDM_WRP_RT_INTF_CTL9_IN)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL9_SPDM_WRP_RT_INTF_CTL9_BMSK                                                 0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL9_SPDM_WRP_RT_INTF_CTL9_SHFT                                                        0x0

#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL10_ADDR                                                                      (TCSR_TCSR_REGS_REG_BASE      + 0x00007044)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL10_RMSK                                                                      0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL10_IN          \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL10_ADDR, HWIO_TCSR_SPDM_WRP_RT_INTF_CTL10_RMSK)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL10_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL10_ADDR, m)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL10_OUT(v)      \
        out_dword(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL10_ADDR,v)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL10_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL10_ADDR,m,v,HWIO_TCSR_SPDM_WRP_RT_INTF_CTL10_IN)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL10_SPDM_WRP_RT_INTF_CTL10_BMSK                                               0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL10_SPDM_WRP_RT_INTF_CTL10_SHFT                                                      0x0

#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL11_ADDR                                                                      (TCSR_TCSR_REGS_REG_BASE      + 0x00007048)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL11_RMSK                                                                      0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL11_IN          \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL11_ADDR, HWIO_TCSR_SPDM_WRP_RT_INTF_CTL11_RMSK)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL11_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL11_ADDR, m)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL11_OUT(v)      \
        out_dword(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL11_ADDR,v)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL11_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL11_ADDR,m,v,HWIO_TCSR_SPDM_WRP_RT_INTF_CTL11_IN)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL11_SPDM_WRP_RT_INTF_CTL11_BMSK                                               0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL11_SPDM_WRP_RT_INTF_CTL11_SHFT                                                      0x0

#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL12_ADDR                                                                      (TCSR_TCSR_REGS_REG_BASE      + 0x0000704c)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL12_RMSK                                                                      0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL12_IN          \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL12_ADDR, HWIO_TCSR_SPDM_WRP_RT_INTF_CTL12_RMSK)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL12_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL12_ADDR, m)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL12_OUT(v)      \
        out_dword(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL12_ADDR,v)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL12_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL12_ADDR,m,v,HWIO_TCSR_SPDM_WRP_RT_INTF_CTL12_IN)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL12_SPDM_WRP_RT_INTF_CTL12_BMSK                                               0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL12_SPDM_WRP_RT_INTF_CTL12_SHFT                                                      0x0

#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL13_ADDR                                                                      (TCSR_TCSR_REGS_REG_BASE      + 0x00007050)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL13_RMSK                                                                      0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL13_IN          \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL13_ADDR, HWIO_TCSR_SPDM_WRP_RT_INTF_CTL13_RMSK)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL13_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL13_ADDR, m)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL13_OUT(v)      \
        out_dword(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL13_ADDR,v)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL13_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL13_ADDR,m,v,HWIO_TCSR_SPDM_WRP_RT_INTF_CTL13_IN)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL13_SPDM_WRP_RT_INTF_CTL13_BMSK                                               0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL13_SPDM_WRP_RT_INTF_CTL13_SHFT                                                      0x0

#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL14_ADDR                                                                      (TCSR_TCSR_REGS_REG_BASE      + 0x00007054)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL14_RMSK                                                                      0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL14_IN          \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL14_ADDR, HWIO_TCSR_SPDM_WRP_RT_INTF_CTL14_RMSK)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL14_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL14_ADDR, m)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL14_OUT(v)      \
        out_dword(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL14_ADDR,v)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL14_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL14_ADDR,m,v,HWIO_TCSR_SPDM_WRP_RT_INTF_CTL14_IN)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL14_SPDM_WRP_RT_INTF_CTL14_BMSK                                               0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL14_SPDM_WRP_RT_INTF_CTL14_SHFT                                                      0x0

#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL15_ADDR                                                                      (TCSR_TCSR_REGS_REG_BASE      + 0x00007058)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL15_RMSK                                                                      0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL15_IN          \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL15_ADDR, HWIO_TCSR_SPDM_WRP_RT_INTF_CTL15_RMSK)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL15_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL15_ADDR, m)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL15_OUT(v)      \
        out_dword(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL15_ADDR,v)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL15_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPDM_WRP_RT_INTF_CTL15_ADDR,m,v,HWIO_TCSR_SPDM_WRP_RT_INTF_CTL15_IN)
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL15_SPDM_WRP_RT_INTF_CTL15_BMSK                                               0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_INTF_CTL15_SPDM_WRP_RT_INTF_CTL15_SHFT                                                      0x0

#define HWIO_TCSR_SPDM_WRP_CTI_CTL0_ADDR                                                                           (TCSR_TCSR_REGS_REG_BASE      + 0x0000705c)
#define HWIO_TCSR_SPDM_WRP_CTI_CTL0_RMSK                                                                           0xffffffff
#define HWIO_TCSR_SPDM_WRP_CTI_CTL0_IN          \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_CTI_CTL0_ADDR, HWIO_TCSR_SPDM_WRP_CTI_CTL0_RMSK)
#define HWIO_TCSR_SPDM_WRP_CTI_CTL0_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_CTI_CTL0_ADDR, m)
#define HWIO_TCSR_SPDM_WRP_CTI_CTL0_OUT(v)      \
        out_dword(HWIO_TCSR_SPDM_WRP_CTI_CTL0_ADDR,v)
#define HWIO_TCSR_SPDM_WRP_CTI_CTL0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPDM_WRP_CTI_CTL0_ADDR,m,v,HWIO_TCSR_SPDM_WRP_CTI_CTL0_IN)
#define HWIO_TCSR_SPDM_WRP_CTI_CTL0_SPDM_WRP_CTI_CTL0_BMSK                                                         0xffffffff
#define HWIO_TCSR_SPDM_WRP_CTI_CTL0_SPDM_WRP_CTI_CTL0_SHFT                                                                0x0

#define HWIO_TCSR_SPDM_WRP_CTI_CTL1_ADDR                                                                           (TCSR_TCSR_REGS_REG_BASE      + 0x00007060)
#define HWIO_TCSR_SPDM_WRP_CTI_CTL1_RMSK                                                                           0xffffffff
#define HWIO_TCSR_SPDM_WRP_CTI_CTL1_IN          \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_CTI_CTL1_ADDR, HWIO_TCSR_SPDM_WRP_CTI_CTL1_RMSK)
#define HWIO_TCSR_SPDM_WRP_CTI_CTL1_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_CTI_CTL1_ADDR, m)
#define HWIO_TCSR_SPDM_WRP_CTI_CTL1_OUT(v)      \
        out_dword(HWIO_TCSR_SPDM_WRP_CTI_CTL1_ADDR,v)
#define HWIO_TCSR_SPDM_WRP_CTI_CTL1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPDM_WRP_CTI_CTL1_ADDR,m,v,HWIO_TCSR_SPDM_WRP_CTI_CTL1_IN)
#define HWIO_TCSR_SPDM_WRP_CTI_CTL1_SPDM_WRP_CTI_CTL1_BMSK                                                         0xffffffff
#define HWIO_TCSR_SPDM_WRP_CTI_CTL1_SPDM_WRP_CTI_CTL1_SHFT                                                                0x0

#define HWIO_TCSR_SPDM_WRP_CTI_CTL2_ADDR                                                                           (TCSR_TCSR_REGS_REG_BASE      + 0x00007064)
#define HWIO_TCSR_SPDM_WRP_CTI_CTL2_RMSK                                                                           0xffffffff
#define HWIO_TCSR_SPDM_WRP_CTI_CTL2_IN          \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_CTI_CTL2_ADDR, HWIO_TCSR_SPDM_WRP_CTI_CTL2_RMSK)
#define HWIO_TCSR_SPDM_WRP_CTI_CTL2_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_CTI_CTL2_ADDR, m)
#define HWIO_TCSR_SPDM_WRP_CTI_CTL2_OUT(v)      \
        out_dword(HWIO_TCSR_SPDM_WRP_CTI_CTL2_ADDR,v)
#define HWIO_TCSR_SPDM_WRP_CTI_CTL2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPDM_WRP_CTI_CTL2_ADDR,m,v,HWIO_TCSR_SPDM_WRP_CTI_CTL2_IN)
#define HWIO_TCSR_SPDM_WRP_CTI_CTL2_SPDM_WRP_CTI_CTL2_BMSK                                                         0xffffffff
#define HWIO_TCSR_SPDM_WRP_CTI_CTL2_SPDM_WRP_CTI_CTL2_SHFT                                                                0x0

#define HWIO_TCSR_SPDM_WRP_CTI_CTL3_ADDR                                                                           (TCSR_TCSR_REGS_REG_BASE      + 0x00007068)
#define HWIO_TCSR_SPDM_WRP_CTI_CTL3_RMSK                                                                           0xffffffff
#define HWIO_TCSR_SPDM_WRP_CTI_CTL3_IN          \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_CTI_CTL3_ADDR, HWIO_TCSR_SPDM_WRP_CTI_CTL3_RMSK)
#define HWIO_TCSR_SPDM_WRP_CTI_CTL3_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_CTI_CTL3_ADDR, m)
#define HWIO_TCSR_SPDM_WRP_CTI_CTL3_OUT(v)      \
        out_dword(HWIO_TCSR_SPDM_WRP_CTI_CTL3_ADDR,v)
#define HWIO_TCSR_SPDM_WRP_CTI_CTL3_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPDM_WRP_CTI_CTL3_ADDR,m,v,HWIO_TCSR_SPDM_WRP_CTI_CTL3_IN)
#define HWIO_TCSR_SPDM_WRP_CTI_CTL3_SPDM_WRP_CTI_CTL3_BMSK                                                         0xffffffff
#define HWIO_TCSR_SPDM_WRP_CTI_CTL3_SPDM_WRP_CTI_CTL3_SHFT                                                                0x0

#define HWIO_TCSR_SPDM_WRP_RT_CTL_COMMON_ADDR                                                                      (TCSR_TCSR_REGS_REG_BASE      + 0x0000706c)
#define HWIO_TCSR_SPDM_WRP_RT_CTL_COMMON_RMSK                                                                      0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_CTL_COMMON_IN          \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_CTL_COMMON_ADDR, HWIO_TCSR_SPDM_WRP_RT_CTL_COMMON_RMSK)
#define HWIO_TCSR_SPDM_WRP_RT_CTL_COMMON_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_RT_CTL_COMMON_ADDR, m)
#define HWIO_TCSR_SPDM_WRP_RT_CTL_COMMON_OUT(v)      \
        out_dword(HWIO_TCSR_SPDM_WRP_RT_CTL_COMMON_ADDR,v)
#define HWIO_TCSR_SPDM_WRP_RT_CTL_COMMON_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPDM_WRP_RT_CTL_COMMON_ADDR,m,v,HWIO_TCSR_SPDM_WRP_RT_CTL_COMMON_IN)
#define HWIO_TCSR_SPDM_WRP_RT_CTL_COMMON_SPDM_WRP_CTL_COMMON_BMSK                                                  0xffffffff
#define HWIO_TCSR_SPDM_WRP_RT_CTL_COMMON_SPDM_WRP_CTL_COMMON_SHFT                                                         0x0

#define HWIO_TCSR_SPDM_WRP_CTI_CTL_ADDR                                                                            (TCSR_TCSR_REGS_REG_BASE      + 0x00007070)
#define HWIO_TCSR_SPDM_WRP_CTI_CTL_RMSK                                                                                   0x7
#define HWIO_TCSR_SPDM_WRP_CTI_CTL_IN          \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_CTI_CTL_ADDR, HWIO_TCSR_SPDM_WRP_CTI_CTL_RMSK)
#define HWIO_TCSR_SPDM_WRP_CTI_CTL_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPDM_WRP_CTI_CTL_ADDR, m)
#define HWIO_TCSR_SPDM_WRP_CTI_CTL_OUT(v)      \
        out_dword(HWIO_TCSR_SPDM_WRP_CTI_CTL_ADDR,v)
#define HWIO_TCSR_SPDM_WRP_CTI_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPDM_WRP_CTI_CTL_ADDR,m,v,HWIO_TCSR_SPDM_WRP_CTI_CTL_IN)
#define HWIO_TCSR_SPDM_WRP_CTI_CTL_SPDM_WRP_CTI_CTL_BMSK                                                                  0x7
#define HWIO_TCSR_SPDM_WRP_CTI_CTL_SPDM_WRP_CTI_CTL_SHFT                                                                  0x0

#define HWIO_TCSR_SOC_HW_VERSION_ADDR                                                                              (TCSR_TCSR_REGS_REG_BASE      + 0x00008000)
#define HWIO_TCSR_SOC_HW_VERSION_RMSK                                                                              0xffffffff
#define HWIO_TCSR_SOC_HW_VERSION_IN          \
        in_dword_masked(HWIO_TCSR_SOC_HW_VERSION_ADDR, HWIO_TCSR_SOC_HW_VERSION_RMSK)
#define HWIO_TCSR_SOC_HW_VERSION_INM(m)      \
        in_dword_masked(HWIO_TCSR_SOC_HW_VERSION_ADDR, m)
#define HWIO_TCSR_SOC_HW_VERSION_FAMILY_NUMBER_BMSK                                                                0xf0000000
#define HWIO_TCSR_SOC_HW_VERSION_FAMILY_NUMBER_SHFT                                                                      0x1c
#define HWIO_TCSR_SOC_HW_VERSION_DEVICE_NUMBER_BMSK                                                                 0xfff0000
#define HWIO_TCSR_SOC_HW_VERSION_DEVICE_NUMBER_SHFT                                                                      0x10
#define HWIO_TCSR_SOC_HW_VERSION_MAJOR_VERSION_BMSK                                                                    0xff00
#define HWIO_TCSR_SOC_HW_VERSION_MAJOR_VERSION_SHFT                                                                       0x8
#define HWIO_TCSR_SOC_HW_VERSION_MINOR_VERSION_BMSK                                                                      0xff
#define HWIO_TCSR_SOC_HW_VERSION_MINOR_VERSION_SHFT                                                                       0x0

#define HWIO_TCSR_TIMEOUT_INTR_STATUS_ADDR                                                                         (TCSR_TCSR_REGS_REG_BASE      + 0x00008020)
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_RMSK                                                                         0xffffffff
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_IN          \
        in_dword_masked(HWIO_TCSR_TIMEOUT_INTR_STATUS_ADDR, HWIO_TCSR_TIMEOUT_INTR_STATUS_RMSK)
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_INM(m)      \
        in_dword_masked(HWIO_TCSR_TIMEOUT_INTR_STATUS_ADDR, m)
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_SNOC_S3_IRQ_BMSK                                                 0x80000000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_SNOC_S3_IRQ_SHFT                                                       0x1f
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_SOUTH_S3_IRQ_BMSK                                           0x40000000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_SOUTH_S3_IRQ_SHFT                                                 0x1e
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_SOUTH_S2_IRQ_BMSK                                           0x20000000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_SOUTH_S2_IRQ_SHFT                                                 0x1d
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_TURING_IRQ_OUT_AHB_TIMEOUT_1_BMSK                                            0x10000000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_TURING_IRQ_OUT_AHB_TIMEOUT_1_SHFT                                                  0x1c
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_SOUTH_S0_IRQ_BMSK                                            0x8000000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_SOUTH_S0_IRQ_SHFT                                                 0x1b
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_SNOC_LPASS_IRQ_BMSK                                               0x4000000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_SNOC_LPASS_IRQ_SHFT                                                    0x1a
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_QHS_MMSS3_BUS_TIMEOUT_IRQ_BMSK                                                0x2000000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_QHS_MMSS3_BUS_TIMEOUT_IRQ_SHFT                                                     0x19
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_WCSS_ECAHB_TSLV_INTR_BMSK                                                     0x1000000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_WCSS_ECAHB_TSLV_INTR_SHFT                                                          0x18
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_SNOC_CDSP_IRQ_BMSK                                                 0x800000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_SNOC_CDSP_IRQ_SHFT                                                     0x17
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_LPASS_IRQ_OUT_AHB_TIMEOUT1_BMSK                                                0x400000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_LPASS_IRQ_OUT_AHB_TIMEOUT1_SHFT                                                    0x16
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_LPASS_IRQ_OUT_AHB_TIMEOUT0_BMSK                                                0x200000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_LPASS_IRQ_OUT_AHB_TIMEOUT0_SHFT                                                    0x15
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_WCSS_TCSR_WAHB_TSLV_INTR_BMSK                                                  0x100000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_WCSS_TCSR_WAHB_TSLV_INTR_SHFT                                                      0x14
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_QHS_MMSS2_BUS_TIMEOUT_IRQ_BMSK                                                  0x80000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_QHS_MMSS2_BUS_TIMEOUT_IRQ_SHFT                                                     0x13
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_QHS_MMSS1_BUS_TIMEOUT_IRQ_BMSK                                                  0x40000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_QHS_MMSS1_BUS_TIMEOUT_IRQ_SHFT                                                     0x12
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_QHS_MMSS_BUS_TIMEOUT_IRQ_BMSK                                                   0x20000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_QHS_MMSS_BUS_TIMEOUT_IRQ_SHFT                                                      0x11
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_CENTER_LEFT_S1_IRQ_BMSK                                        0x10000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_CENTER_LEFT_S1_IRQ_SHFT                                           0x10
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_MM_CFG_IRQ_BMSK                                                 0x8000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_MM_CFG_IRQ_SHFT                                                    0xf
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_NORTH_S1_IRQ_BMSK                                               0x4000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_NORTH_S1_IRQ_SHFT                                                  0xe
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_NORTH_S0_IRQ_BMSK                                               0x2000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_NORTH_S0_IRQ_SHFT                                                  0xd
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_NORTH_S2_IRQ_BMSK                                               0x1000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_NORTH_S2_IRQ_SHFT                                                  0xc
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_WCSS_TCSR_WAPB_TSLV_IRQ_BMSK                                                      0x800
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_WCSS_TCSR_WAPB_TSLV_IRQ_SHFT                                                        0xb
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_MSS_CONFIG_TIMEOUT_SLAVE_IRQ_BMSK                                                 0x400
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_MSS_CONFIG_TIMEOUT_SLAVE_IRQ_SHFT                                                   0xa
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_SNOC_IPA_IRQ_BMSK                                                     0x200
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_SNOC_IPA_IRQ_SHFT                                                       0x9
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_CENTER_LEFT_S0_IRQ_BMSK                                          0x100
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_CENTER_LEFT_S0_IRQ_SHFT                                            0x8
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_TURING_IRQ_OUT_AHB_TIMEOUT_0_BMSK                                                  0x80
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_TURING_IRQ_OUT_AHB_TIMEOUT_0_SHFT                                                   0x7
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_WCSS_TCSR_NOC_INTR_BMSK                                                            0x40
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_WCSS_TCSR_NOC_INTR_SHFT                                                             0x6
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_CTR_S5_IRQ_BMSK                                                   0x20
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_CTR_S5_IRQ_SHFT                                                    0x5
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_CTR_S4_IRQ_BMSK                                                   0x10
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_CTR_S4_IRQ_SHFT                                                    0x4
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_CTR_S3_IRQ_BMSK                                                    0x8
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_CTR_S3_IRQ_SHFT                                                    0x3
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_CTR_S2_IRQ_BMSK                                                    0x4
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_CTR_S2_IRQ_SHFT                                                    0x2
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_CTR_S1_IRQ_BMSK                                                    0x2
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_CTR_S1_IRQ_SHFT                                                    0x1
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_CTR_S0_IRQ_BMSK                                                    0x1
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_CTR_S0_IRQ_SHFT                                                    0x0

#define HWIO_TCSR_TIMEOUT_INTR_STATUS1_ADDR                                                                        (TCSR_TCSR_REGS_REG_BASE      + 0x00008024)
#define HWIO_TCSR_TIMEOUT_INTR_STATUS1_RMSK                                                                               0x3
#define HWIO_TCSR_TIMEOUT_INTR_STATUS1_IN          \
        in_dword_masked(HWIO_TCSR_TIMEOUT_INTR_STATUS1_ADDR, HWIO_TCSR_TIMEOUT_INTR_STATUS1_RMSK)
#define HWIO_TCSR_TIMEOUT_INTR_STATUS1_INM(m)      \
        in_dword_masked(HWIO_TCSR_TIMEOUT_INTR_STATUS1_ADDR, m)
#define HWIO_TCSR_TIMEOUT_INTR_STATUS1_BUS_TIMEOUT_4_LPASS_IRQ_BMSK                                                       0x2
#define HWIO_TCSR_TIMEOUT_INTR_STATUS1_BUS_TIMEOUT_4_LPASS_IRQ_SHFT                                                       0x1
#define HWIO_TCSR_TIMEOUT_INTR_STATUS1_BUS_TIMEOUT_3_LPASS_IRQ_BMSK                                                       0x1
#define HWIO_TCSR_TIMEOUT_INTR_STATUS1_BUS_TIMEOUT_3_LPASS_IRQ_SHFT                                                       0x0

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
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_SNOC_S3_IRQ_ENABLE_BMSK                                      0x80000000
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_SNOC_S3_IRQ_ENABLE_SHFT                                            0x1f
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_CNOC_SOUTH_S3_IRQ_ENABLE_BMSK                                0x40000000
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_CNOC_SOUTH_S3_IRQ_ENABLE_SHFT                                      0x1e
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_CNOC_SOUTH_S2_IRQ_ENABLE_BMSK                                0x20000000
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_CNOC_SOUTH_S2_IRQ_ENABLE_SHFT                                      0x1d
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_TURING_IRQ_OUT_AHB_TIMEOUT_1_ENABLE_BMSK                                 0x10000000
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_TURING_IRQ_OUT_AHB_TIMEOUT_1_ENABLE_SHFT                                       0x1c
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_CNOC_SOUTH_S0_IRQ_ENABLE_BMSK                                 0x8000000
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_CNOC_SOUTH_S0_IRQ_ENABLE_SHFT                                      0x1b
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_SNOC_LPASS_IRQ_ENABLE_BMSK                                    0x4000000
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_SNOC_LPASS_IRQ_ENABLE_SHFT                                         0x1a
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_QHS_MMSS3_BUS_TIMEOUT_IRQ_ENABLE_BMSK                                     0x2000000
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_QHS_MMSS3_BUS_TIMEOUT_IRQ_ENABLE_SHFT                                          0x19
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_WCSS_ECAHB_TSLV_INTR_ENABLE_BMSK                                          0x1000000
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_WCSS_ECAHB_TSLV_INTR_ENABLE_SHFT                                               0x18
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_SNOC_CDSP_IRQ_ENABLE_BMSK                                      0x800000
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_SNOC_CDSP_IRQ_ENABLE_SHFT                                          0x17
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
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_SNOC_IPA_IRQ_ENABLE_BMSK                                          0x200
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_SNOC_IPA_IRQ_ENABLE_SHFT                                            0x9
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
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE1_BUS_TIMEOUT_3_LPASS_IRQ_ENABLE_BMSK                                            0x1
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE1_BUS_TIMEOUT_3_LPASS_IRQ_ENABLE_SHFT                                            0x0

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
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_SNOC_S3_IRQ_ENABLE_BMSK                                     0x80000000
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_SNOC_S3_IRQ_ENABLE_SHFT                                           0x1f
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_CNOC_SOUTH_S3_IRQ_ENABLE_BMSK                               0x40000000
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_CNOC_SOUTH_S3_IRQ_ENABLE_SHFT                                     0x1e
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_CNOC_SOUTH_S2_IRQ_ENABLE_BMSK                               0x20000000
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_CNOC_SOUTH_S2_IRQ_ENABLE_SHFT                                     0x1d
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_TURING_IRQ_OUT_AHB_TIMEOUT_1_ENABLE_BMSK                                0x10000000
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_TURING_IRQ_OUT_AHB_TIMEOUT_1_ENABLE_SHFT                                      0x1c
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_CNOC_SOUTH_S0_IRQ_ENABLE_BMSK                                0x8000000
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_CNOC_SOUTH_S0_IRQ_ENABLE_SHFT                                     0x1b
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_SNOC_LPASS_IRQ_ENABLE_BMSK                                   0x4000000
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_SNOC_LPASS_IRQ_ENABLE_SHFT                                        0x1a
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_QHS_MMSS3_BUS_TIMEOUT_IRQ_ENABLE_BMSK                                    0x2000000
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_QHS_MMSS3_BUS_TIMEOUT_IRQ_ENABLE_SHFT                                         0x19
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_WCSS_ECAHB_TSLV_INTR_ENABLE_BMSK                                         0x1000000
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_WCSS_ECAHB_TSLV_INTR_ENABLE_SHFT                                              0x18
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_SNOC_CDSP_IRQ_ENABLE_BMSK                                     0x800000
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_SNOC_CDSP_IRQ_ENABLE_SHFT                                         0x17
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
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_SNOC_IPA_IRQ_ENABLE_BMSK                                         0x200
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_SNOC_IPA_IRQ_ENABLE_SHFT                                           0x9
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
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE1_BUS_TIMEOUT_3_LPASS_IRQ_ENABLE_BMSK                                           0x2
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE1_BUS_TIMEOUT_3_LPASS_IRQ_ENABLE_SHFT                                           0x1
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE1_BUS_TIMEOUT_4_LPASS_IRQ_ENABLE_BMSK                                           0x1
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE1_BUS_TIMEOUT_4_LPASS_IRQ_ENABLE_SHFT                                           0x0

#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_ADDR                                                                   (TCSR_TCSR_REGS_REG_BASE      + 0x00008050)
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_RMSK                                                                   0xffffffff
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_IN          \
        in_dword_masked(HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_ADDR, HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_RMSK)
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_INM(m)      \
        in_dword_masked(HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_ADDR, m)
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_OUT(v)      \
        out_dword(HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_ADDR,v)
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_ADDR,m,v,HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_IN)
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_SNOC_S3_IRQ_ENABLE_BMSK                                    0x80000000
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_SNOC_S3_IRQ_ENABLE_SHFT                                          0x1f
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_CNOC_SOUTH_S3_IRQ_ENABLE_BMSK                              0x40000000
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_CNOC_SOUTH_S3_IRQ_ENABLE_SHFT                                    0x1e
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_CNOC_SOUTH_S2_IRQ_ENABLE_BMSK                              0x20000000
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_CNOC_SOUTH_S2_IRQ_ENABLE_SHFT                                    0x1d
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_TURING_IRQ_OUT_AHB_TIMEOUT_1_ENABLE_BMSK                               0x10000000
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_TURING_IRQ_OUT_AHB_TIMEOUT_1_ENABLE_SHFT                                     0x1c
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_CNOC_SOUTH_S0_IRQ_ENABLE_BMSK                               0x8000000
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_CNOC_SOUTH_S0_IRQ_ENABLE_SHFT                                    0x1b
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_SNOC_LPASS_IRQ_ENABLE_BMSK                                  0x4000000
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_SNOC_LPASS_IRQ_ENABLE_SHFT                                       0x1a
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_QHS_MMSS3_BUS_TIMEOUT_IRQ_ENABLE_BMSK                                   0x2000000
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_QHS_MMSS3_BUS_TIMEOUT_IRQ_ENABLE_SHFT                                        0x19
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_WCSS_ECAHB_TSLV_INTR_ENABLE_BMSK                                        0x1000000
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_WCSS_ECAHB_TSLV_INTR_ENABLE_SHFT                                             0x18
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_SNOC_CDSP_IRQ_ENABLE_BMSK                                    0x800000
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_SNOC_CDSP_IRQ_ENABLE_SHFT                                        0x17
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
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_SNOC_IPA_IRQ_ENABLE_BMSK                                        0x200
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_SNOC_IPA_IRQ_ENABLE_SHFT                                          0x9
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
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE1_BUS_TIMEOUT_3_LPASS_IRQ_ENABLE_BMSK                                          0x1
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE1_BUS_TIMEOUT_3_LPASS_IRQ_ENABLE_SHFT                                          0x0

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
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_SNOC_S3_IRQ_ENABLE_BMSK                                      0x80000000
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_SNOC_S3_IRQ_ENABLE_SHFT                                            0x1f
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_CNOC_SOUTH_S3_IRQ_ENABLE_BMSK                                0x40000000
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_CNOC_SOUTH_S3_IRQ_ENABLE_SHFT                                      0x1e
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_CNOC_SOUTH_S2_IRQ_ENABLE_BMSK                                0x20000000
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_CNOC_SOUTH_S2_IRQ_ENABLE_SHFT                                      0x1d
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_TURING_IRQ_OUT_AHB_TIMEOUT_1_ENABLE_BMSK                                 0x10000000
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_TURING_IRQ_OUT_AHB_TIMEOUT_1_ENABLE_SHFT                                       0x1c
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_CNOC_SOUTH_S0_IRQ_ENABLE_BMSK                                 0x8000000
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_CNOC_SOUTH_S0_IRQ_ENABLE_SHFT                                      0x1b
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_SNOC_LPASS_IRQ_ENABLE_BMSK                                    0x4000000
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_SNOC_LPASS_IRQ_ENABLE_SHFT                                         0x1a
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_QHS_MMSS3_BUS_TIMEOUT_IRQ_ENABLE_BMSK                                     0x2000000
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_QHS_MMSS3_BUS_TIMEOUT_IRQ_ENABLE_SHFT                                          0x19
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_WCSS_ECAHB_TSLV_INTR_ENABLE_BMSK                                          0x1000000
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_WCSS_ECAHB_TSLV_INTR_ENABLE_SHFT                                               0x18
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_SNOC_CDSP_IRQ_ENABLE_BMSK                                      0x800000
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_SNOC_CDSP_IRQ_ENABLE_SHFT                                          0x17
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
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_SNOC_IPA_IRQ_ENABLE_BMSK                                          0x200
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_SNOC_IPA_IRQ_ENABLE_SHFT                                            0x9
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
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE1_BUS_TIMEOUT_3_LPASS_IRQ_ENABLE_BMSK                                            0x1
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE1_BUS_TIMEOUT_3_LPASS_IRQ_ENABLE_SHFT                                            0x0

#define HWIO_TCSR_SRAM_REDUNDANCY_CRC_ERR_ADDR                                                                     (TCSR_TCSR_REGS_REG_BASE      + 0x00008068)
#define HWIO_TCSR_SRAM_REDUNDANCY_CRC_ERR_RMSK                                                                            0x1
#define HWIO_TCSR_SRAM_REDUNDANCY_CRC_ERR_IN          \
        in_dword_masked(HWIO_TCSR_SRAM_REDUNDANCY_CRC_ERR_ADDR, HWIO_TCSR_SRAM_REDUNDANCY_CRC_ERR_RMSK)
#define HWIO_TCSR_SRAM_REDUNDANCY_CRC_ERR_INM(m)      \
        in_dword_masked(HWIO_TCSR_SRAM_REDUNDANCY_CRC_ERR_ADDR, m)
#define HWIO_TCSR_SRAM_REDUNDANCY_CRC_ERR_SRAM_REDUNDANCY_CRC_ERR_BMSK                                                    0x1
#define HWIO_TCSR_SRAM_REDUNDANCY_CRC_ERR_SRAM_REDUNDANCY_CRC_ERR_SHFT                                                    0x0

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
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_BUS_TIMEOUT_SNOC_S3_IRQ_ENABLE_BMSK                                   0x80000000
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_BUS_TIMEOUT_SNOC_S3_IRQ_ENABLE_SHFT                                         0x1f
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_BUS_TIMEOUT_CNOC_SOUTH_S3_IRQ_ENABLE_BMSK                             0x40000000
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_BUS_TIMEOUT_CNOC_SOUTH_S3_IRQ_ENABLE_SHFT                                   0x1e
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_BUS_TIMEOUT_CNOC_SOUTH_S2_IRQ_ENABLE_BMSK                             0x20000000
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_BUS_TIMEOUT_CNOC_SOUTH_S2_IRQ_ENABLE_SHFT                                   0x1d
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_TURING_IRQ_OUT_AHB_TIMEOUT_1_ENABLE_BMSK                              0x10000000
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_TURING_IRQ_OUT_AHB_TIMEOUT_1_ENABLE_SHFT                                    0x1c
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_BUS_TIMEOUT_CNOC_SOUTH_S0_IRQ_ENABLE_BMSK                              0x8000000
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_BUS_TIMEOUT_CNOC_SOUTH_S0_IRQ_ENABLE_SHFT                                   0x1b
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_BUS_TIMEOUT_SNOC_LPASS_IRQ_ENABLE_BMSK                                 0x4000000
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_BUS_TIMEOUT_SNOC_LPASS_IRQ_ENABLE_SHFT                                      0x1a
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_QHS_MMSS3_BUS_TIMEOUT_IRQ_ENABLE_BMSK                                  0x2000000
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_QHS_MMSS3_BUS_TIMEOUT_IRQ_ENABLE_SHFT                                       0x19
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_WCSS_ECAHB_TSLV_INTR_ENABLE_BMSK                                       0x1000000
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_WCSS_ECAHB_TSLV_INTR_ENABLE_SHFT                                            0x18
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_BUS_TIMEOUT_SNOC_CDSP_IRQ_ENABLE_BMSK                                   0x800000
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_BUS_TIMEOUT_SNOC_CDSP_IRQ_ENABLE_SHFT                                       0x17
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
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_BUS_TIMEOUT_SNOC_IPA_IRQ_ENABLE_BMSK                                       0x200
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_BUS_TIMEOUT_SNOC_IPA_IRQ_ENABLE_SHFT                                         0x9
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
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE1_BUS_TIMEOUT_3_LPASS_IRQ_ENABLE_BMSK                                         0x1
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE1_BUS_TIMEOUT_3_LPASS_IRQ_ENABLE_SHFT                                         0x0

#define HWIO_TCSR_TCSR_CLK_EN_ADDR                                                                                 (TCSR_TCSR_REGS_REG_BASE      + 0x0000907c)
#define HWIO_TCSR_TCSR_CLK_EN_RMSK                                                                                        0x1
#define HWIO_TCSR_TCSR_CLK_EN_IN          \
        in_dword_masked(HWIO_TCSR_TCSR_CLK_EN_ADDR, HWIO_TCSR_TCSR_CLK_EN_RMSK)
#define HWIO_TCSR_TCSR_CLK_EN_INM(m)      \
        in_dword_masked(HWIO_TCSR_TCSR_CLK_EN_ADDR, m)
#define HWIO_TCSR_TCSR_CLK_EN_OUT(v)      \
        out_dword(HWIO_TCSR_TCSR_CLK_EN_ADDR,v)
#define HWIO_TCSR_TCSR_CLK_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_TCSR_CLK_EN_ADDR,m,v,HWIO_TCSR_TCSR_CLK_EN_IN)
#define HWIO_TCSR_TCSR_CLK_EN_TCSR_CLK_EN_BMSK                                                                            0x1
#define HWIO_TCSR_TCSR_CLK_EN_TCSR_CLK_EN_SHFT                                                                            0x0

#define HWIO_TCSR_TCSR_IPA_WARMBOOT_EN_ADDR                                                                        (TCSR_TCSR_REGS_REG_BASE      + 0x0000a100)
#define HWIO_TCSR_TCSR_IPA_WARMBOOT_EN_RMSK                                                                               0x1
#define HWIO_TCSR_TCSR_IPA_WARMBOOT_EN_IN          \
        in_dword_masked(HWIO_TCSR_TCSR_IPA_WARMBOOT_EN_ADDR, HWIO_TCSR_TCSR_IPA_WARMBOOT_EN_RMSK)
#define HWIO_TCSR_TCSR_IPA_WARMBOOT_EN_INM(m)      \
        in_dword_masked(HWIO_TCSR_TCSR_IPA_WARMBOOT_EN_ADDR, m)
#define HWIO_TCSR_TCSR_IPA_WARMBOOT_EN_OUT(v)      \
        out_dword(HWIO_TCSR_TCSR_IPA_WARMBOOT_EN_ADDR,v)
#define HWIO_TCSR_TCSR_IPA_WARMBOOT_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_TCSR_IPA_WARMBOOT_EN_ADDR,m,v,HWIO_TCSR_TCSR_IPA_WARMBOOT_EN_IN)
#define HWIO_TCSR_TCSR_IPA_WARMBOOT_EN_TCSR_IPA_WARMBOOT_EN_BMSK                                                          0x1
#define HWIO_TCSR_TCSR_IPA_WARMBOOT_EN_TCSR_IPA_WARMBOOT_EN_SHFT                                                          0x0

#define HWIO_TCSR_SYS_POWER_CTRL_ADDR                                                                              (TCSR_TCSR_REGS_REG_BASE      + 0x0000a000)
#define HWIO_TCSR_SYS_POWER_CTRL_RMSK                                                                                  0xffff
#define HWIO_TCSR_SYS_POWER_CTRL_IN          \
        in_dword_masked(HWIO_TCSR_SYS_POWER_CTRL_ADDR, HWIO_TCSR_SYS_POWER_CTRL_RMSK)
#define HWIO_TCSR_SYS_POWER_CTRL_INM(m)      \
        in_dword_masked(HWIO_TCSR_SYS_POWER_CTRL_ADDR, m)
#define HWIO_TCSR_SYS_POWER_CTRL_OUT(v)      \
        out_dword(HWIO_TCSR_SYS_POWER_CTRL_ADDR,v)
#define HWIO_TCSR_SYS_POWER_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SYS_POWER_CTRL_ADDR,m,v,HWIO_TCSR_SYS_POWER_CTRL_IN)
#define HWIO_TCSR_SYS_POWER_CTRL_SYS_POWER_CTRL_BMSK                                                                   0xffff
#define HWIO_TCSR_SYS_POWER_CTRL_SYS_POWER_CTRL_SHFT                                                                      0x0

#define HWIO_TCSR_USB_CORE_ID_ADDR                                                                                 (TCSR_TCSR_REGS_REG_BASE      + 0x0000a004)
#define HWIO_TCSR_USB_CORE_ID_RMSK                                                                                        0x3
#define HWIO_TCSR_USB_CORE_ID_IN          \
        in_dword_masked(HWIO_TCSR_USB_CORE_ID_ADDR, HWIO_TCSR_USB_CORE_ID_RMSK)
#define HWIO_TCSR_USB_CORE_ID_INM(m)      \
        in_dword_masked(HWIO_TCSR_USB_CORE_ID_ADDR, m)
#define HWIO_TCSR_USB_CORE_ID_OUT(v)      \
        out_dword(HWIO_TCSR_USB_CORE_ID_ADDR,v)
#define HWIO_TCSR_USB_CORE_ID_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_USB_CORE_ID_ADDR,m,v,HWIO_TCSR_USB_CORE_ID_IN)
#define HWIO_TCSR_USB_CORE_ID_USB_CORE_ID_BMSK                                                                            0x3
#define HWIO_TCSR_USB_CORE_ID_USB_CORE_ID_SHFT                                                                            0x0

#define HWIO_TCSR_SPARE_REG0_ADDR                                                                                  (TCSR_TCSR_REGS_REG_BASE      + 0x0000a044)
#define HWIO_TCSR_SPARE_REG0_RMSK                                                                                  0xffffffff
#define HWIO_TCSR_SPARE_REG0_IN          \
        in_dword_masked(HWIO_TCSR_SPARE_REG0_ADDR, HWIO_TCSR_SPARE_REG0_RMSK)
#define HWIO_TCSR_SPARE_REG0_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPARE_REG0_ADDR, m)
#define HWIO_TCSR_SPARE_REG0_OUT(v)      \
        out_dword(HWIO_TCSR_SPARE_REG0_ADDR,v)
#define HWIO_TCSR_SPARE_REG0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPARE_REG0_ADDR,m,v,HWIO_TCSR_SPARE_REG0_IN)
#define HWIO_TCSR_SPARE_REG0_SPARE_REG0_BMSK                                                                       0xffffffff
#define HWIO_TCSR_SPARE_REG0_SPARE_REG0_SHFT                                                                              0x0

#define HWIO_TCSR_SPARE_REG1_ADDR                                                                                  (TCSR_TCSR_REGS_REG_BASE      + 0x0000a048)
#define HWIO_TCSR_SPARE_REG1_RMSK                                                                                  0xffffffff
#define HWIO_TCSR_SPARE_REG1_IN          \
        in_dword_masked(HWIO_TCSR_SPARE_REG1_ADDR, HWIO_TCSR_SPARE_REG1_RMSK)
#define HWIO_TCSR_SPARE_REG1_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPARE_REG1_ADDR, m)
#define HWIO_TCSR_SPARE_REG1_OUT(v)      \
        out_dword(HWIO_TCSR_SPARE_REG1_ADDR,v)
#define HWIO_TCSR_SPARE_REG1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPARE_REG1_ADDR,m,v,HWIO_TCSR_SPARE_REG1_IN)
#define HWIO_TCSR_SPARE_REG1_SPARE_REG1_BMSK                                                                       0xffffffff
#define HWIO_TCSR_SPARE_REG1_SPARE_REG1_SHFT                                                                              0x0

#define HWIO_TCSR_SPARE_REG2_ADDR                                                                                  (TCSR_TCSR_REGS_REG_BASE      + 0x0000a04c)
#define HWIO_TCSR_SPARE_REG2_RMSK                                                                                        0xff
#define HWIO_TCSR_SPARE_REG2_IN          \
        in_dword_masked(HWIO_TCSR_SPARE_REG2_ADDR, HWIO_TCSR_SPARE_REG2_RMSK)
#define HWIO_TCSR_SPARE_REG2_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPARE_REG2_ADDR, m)
#define HWIO_TCSR_SPARE_REG2_OUT(v)      \
        out_dword(HWIO_TCSR_SPARE_REG2_ADDR,v)
#define HWIO_TCSR_SPARE_REG2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPARE_REG2_ADDR,m,v,HWIO_TCSR_SPARE_REG2_IN)
#define HWIO_TCSR_SPARE_REG2_SPARE_REG2_BMSK                                                                             0xff
#define HWIO_TCSR_SPARE_REG2_SPARE_REG2_SHFT                                                                              0x0

#define HWIO_TCSR_SPARE_REG3_ADDR                                                                                  (TCSR_TCSR_REGS_REG_BASE      + 0x0000a050)
#define HWIO_TCSR_SPARE_REG3_RMSK                                                                                        0xff
#define HWIO_TCSR_SPARE_REG3_IN          \
        in_dword_masked(HWIO_TCSR_SPARE_REG3_ADDR, HWIO_TCSR_SPARE_REG3_RMSK)
#define HWIO_TCSR_SPARE_REG3_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPARE_REG3_ADDR, m)
#define HWIO_TCSR_SPARE_REG3_OUT(v)      \
        out_dword(HWIO_TCSR_SPARE_REG3_ADDR,v)
#define HWIO_TCSR_SPARE_REG3_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPARE_REG3_ADDR,m,v,HWIO_TCSR_SPARE_REG3_IN)
#define HWIO_TCSR_SPARE_REG3_SPARE_REG3_BMSK                                                                             0xff
#define HWIO_TCSR_SPARE_REG3_SPARE_REG3_SHFT                                                                              0x0

#define HWIO_TCSR_SPARE_REG4_ADDR                                                                                  (TCSR_TCSR_REGS_REG_BASE      + 0x0000a054)
#define HWIO_TCSR_SPARE_REG4_RMSK                                                                                        0xff
#define HWIO_TCSR_SPARE_REG4_IN          \
        in_dword_masked(HWIO_TCSR_SPARE_REG4_ADDR, HWIO_TCSR_SPARE_REG4_RMSK)
#define HWIO_TCSR_SPARE_REG4_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPARE_REG4_ADDR, m)
#define HWIO_TCSR_SPARE_REG4_OUT(v)      \
        out_dword(HWIO_TCSR_SPARE_REG4_ADDR,v)
#define HWIO_TCSR_SPARE_REG4_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPARE_REG4_ADDR,m,v,HWIO_TCSR_SPARE_REG4_IN)
#define HWIO_TCSR_SPARE_REG4_SPARE_REG4_BMSK                                                                             0xff
#define HWIO_TCSR_SPARE_REG4_SPARE_REG4_SHFT                                                                              0x0

#define HWIO_TCSR_SPARE_REG5_ADDR                                                                                  (TCSR_TCSR_REGS_REG_BASE      + 0x0000a058)
#define HWIO_TCSR_SPARE_REG5_RMSK                                                                                        0xff
#define HWIO_TCSR_SPARE_REG5_IN          \
        in_dword_masked(HWIO_TCSR_SPARE_REG5_ADDR, HWIO_TCSR_SPARE_REG5_RMSK)
#define HWIO_TCSR_SPARE_REG5_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPARE_REG5_ADDR, m)
#define HWIO_TCSR_SPARE_REG5_OUT(v)      \
        out_dword(HWIO_TCSR_SPARE_REG5_ADDR,v)
#define HWIO_TCSR_SPARE_REG5_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPARE_REG5_ADDR,m,v,HWIO_TCSR_SPARE_REG5_IN)
#define HWIO_TCSR_SPARE_REG5_SPARE_REG5_BMSK                                                                             0xff
#define HWIO_TCSR_SPARE_REG5_SPARE_REG5_SHFT                                                                              0x0

#define HWIO_TCSR_SPARE_QGIC_INTERRUPTS_ADDR                                                                       (TCSR_TCSR_REGS_REG_BASE      + 0x0000a05c)
#define HWIO_TCSR_SPARE_QGIC_INTERRUPTS_RMSK                                                                       0xffffffff
#define HWIO_TCSR_SPARE_QGIC_INTERRUPTS_IN          \
        in_dword_masked(HWIO_TCSR_SPARE_QGIC_INTERRUPTS_ADDR, HWIO_TCSR_SPARE_QGIC_INTERRUPTS_RMSK)
#define HWIO_TCSR_SPARE_QGIC_INTERRUPTS_INM(m)      \
        in_dword_masked(HWIO_TCSR_SPARE_QGIC_INTERRUPTS_ADDR, m)
#define HWIO_TCSR_SPARE_QGIC_INTERRUPTS_OUT(v)      \
        out_dword(HWIO_TCSR_SPARE_QGIC_INTERRUPTS_ADDR,v)
#define HWIO_TCSR_SPARE_QGIC_INTERRUPTS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SPARE_QGIC_INTERRUPTS_ADDR,m,v,HWIO_TCSR_SPARE_QGIC_INTERRUPTS_IN)
#define HWIO_TCSR_SPARE_QGIC_INTERRUPTS_SPARE_QGIC_INTERRUPTS_BMSK                                                 0xffffffff
#define HWIO_TCSR_SPARE_QGIC_INTERRUPTS_SPARE_QGIC_INTERRUPTS_SHFT                                                        0x0

#define HWIO_TCSR_UFS_SCM_FAULT_IRQ_ADDR                                                                           (TCSR_TCSR_REGS_REG_BASE      + 0x0000a070)
#define HWIO_TCSR_UFS_SCM_FAULT_IRQ_RMSK                                                                                  0x1
#define HWIO_TCSR_UFS_SCM_FAULT_IRQ_IN          \
        in_dword_masked(HWIO_TCSR_UFS_SCM_FAULT_IRQ_ADDR, HWIO_TCSR_UFS_SCM_FAULT_IRQ_RMSK)
#define HWIO_TCSR_UFS_SCM_FAULT_IRQ_INM(m)      \
        in_dword_masked(HWIO_TCSR_UFS_SCM_FAULT_IRQ_ADDR, m)
#define HWIO_TCSR_UFS_SCM_FAULT_IRQ_UFS_SCM_FAULT_IRQ_BMSK                                                                0x1
#define HWIO_TCSR_UFS_SCM_FAULT_IRQ_UFS_SCM_FAULT_IRQ_SHFT                                                                0x0

#define HWIO_TCSR_SDCC5_SCM_FAULT_IRQ_ADDR                                                                         (TCSR_TCSR_REGS_REG_BASE      + 0x0000a074)
#define HWIO_TCSR_SDCC5_SCM_FAULT_IRQ_RMSK                                                                                0x1
#define HWIO_TCSR_SDCC5_SCM_FAULT_IRQ_IN          \
        in_dword_masked(HWIO_TCSR_SDCC5_SCM_FAULT_IRQ_ADDR, HWIO_TCSR_SDCC5_SCM_FAULT_IRQ_RMSK)
#define HWIO_TCSR_SDCC5_SCM_FAULT_IRQ_INM(m)      \
        in_dword_masked(HWIO_TCSR_SDCC5_SCM_FAULT_IRQ_ADDR, m)
#define HWIO_TCSR_SDCC5_SCM_FAULT_IRQ_SDCC5_SCM_FAULT_IRQ_BMSK                                                            0x1
#define HWIO_TCSR_SDCC5_SCM_FAULT_IRQ_SDCC5_SCM_FAULT_IRQ_SHFT                                                            0x0

#define HWIO_TCSR_SDCC1_SCM_FAULT_IRQ_ADDR                                                                         (TCSR_TCSR_REGS_REG_BASE      + 0x0000a078)
#define HWIO_TCSR_SDCC1_SCM_FAULT_IRQ_RMSK                                                                                0x1
#define HWIO_TCSR_SDCC1_SCM_FAULT_IRQ_IN          \
        in_dword_masked(HWIO_TCSR_SDCC1_SCM_FAULT_IRQ_ADDR, HWIO_TCSR_SDCC1_SCM_FAULT_IRQ_RMSK)
#define HWIO_TCSR_SDCC1_SCM_FAULT_IRQ_INM(m)      \
        in_dword_masked(HWIO_TCSR_SDCC1_SCM_FAULT_IRQ_ADDR, m)
#define HWIO_TCSR_SDCC1_SCM_FAULT_IRQ_SDCC1_SCM_FAULT_IRQ_BMSK                                                            0x1
#define HWIO_TCSR_SDCC1_SCM_FAULT_IRQ_SDCC1_SCM_FAULT_IRQ_SHFT                                                            0x0

#define HWIO_TCSR_PHSS_TEST_BUS_SEL_ADDR                                                                           (TCSR_TCSR_REGS_REG_BASE      + 0x0000b008)
#define HWIO_TCSR_PHSS_TEST_BUS_SEL_RMSK                                                                                  0x3
#define HWIO_TCSR_PHSS_TEST_BUS_SEL_IN          \
        in_dword_masked(HWIO_TCSR_PHSS_TEST_BUS_SEL_ADDR, HWIO_TCSR_PHSS_TEST_BUS_SEL_RMSK)
#define HWIO_TCSR_PHSS_TEST_BUS_SEL_INM(m)      \
        in_dword_masked(HWIO_TCSR_PHSS_TEST_BUS_SEL_ADDR, m)
#define HWIO_TCSR_PHSS_TEST_BUS_SEL_OUT(v)      \
        out_dword(HWIO_TCSR_PHSS_TEST_BUS_SEL_ADDR,v)
#define HWIO_TCSR_PHSS_TEST_BUS_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_PHSS_TEST_BUS_SEL_ADDR,m,v,HWIO_TCSR_PHSS_TEST_BUS_SEL_IN)
#define HWIO_TCSR_PHSS_TEST_BUS_SEL_PHSS_TEST_BUS_SEL_BMSK                                                                0x3
#define HWIO_TCSR_PHSS_TEST_BUS_SEL_PHSS_TEST_BUS_SEL_SHFT                                                                0x0

#define HWIO_TCSR_PHSS_UART_LPASS_INT_SEL_n_ADDR(n)                                                                (TCSR_TCSR_REGS_REG_BASE      + 0x0000b040 + 0x10 * (n))
#define HWIO_TCSR_PHSS_UART_LPASS_INT_SEL_n_RMSK                                                                        0xfff
#define HWIO_TCSR_PHSS_UART_LPASS_INT_SEL_n_MAXn                                                                            1
#define HWIO_TCSR_PHSS_UART_LPASS_INT_SEL_n_INI(n)        \
        in_dword_masked(HWIO_TCSR_PHSS_UART_LPASS_INT_SEL_n_ADDR(n), HWIO_TCSR_PHSS_UART_LPASS_INT_SEL_n_RMSK)
#define HWIO_TCSR_PHSS_UART_LPASS_INT_SEL_n_INMI(n,mask)    \
        in_dword_masked(HWIO_TCSR_PHSS_UART_LPASS_INT_SEL_n_ADDR(n), mask)
#define HWIO_TCSR_PHSS_UART_LPASS_INT_SEL_n_OUTI(n,val)    \
        out_dword(HWIO_TCSR_PHSS_UART_LPASS_INT_SEL_n_ADDR(n),val)
#define HWIO_TCSR_PHSS_UART_LPASS_INT_SEL_n_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TCSR_PHSS_UART_LPASS_INT_SEL_n_ADDR(n),mask,val,HWIO_TCSR_PHSS_UART_LPASS_INT_SEL_n_INI(n))
#define HWIO_TCSR_PHSS_UART_LPASS_INT_SEL_n_LPASS_BLSP_UART_IRQ_ENABLE_BMSK                                             0xfff
#define HWIO_TCSR_PHSS_UART_LPASS_INT_SEL_n_LPASS_BLSP_UART_IRQ_ENABLE_SHFT                                               0x0

#define HWIO_TCSR_PHSS_UART_TURING_INT_SEL_n_ADDR(n)                                                               (TCSR_TCSR_REGS_REG_BASE      + 0x0000b080 + 0x10 * (n))
#define HWIO_TCSR_PHSS_UART_TURING_INT_SEL_n_RMSK                                                                       0xfff
#define HWIO_TCSR_PHSS_UART_TURING_INT_SEL_n_MAXn                                                                           1
#define HWIO_TCSR_PHSS_UART_TURING_INT_SEL_n_INI(n)        \
        in_dword_masked(HWIO_TCSR_PHSS_UART_TURING_INT_SEL_n_ADDR(n), HWIO_TCSR_PHSS_UART_TURING_INT_SEL_n_RMSK)
#define HWIO_TCSR_PHSS_UART_TURING_INT_SEL_n_INMI(n,mask)    \
        in_dword_masked(HWIO_TCSR_PHSS_UART_TURING_INT_SEL_n_ADDR(n), mask)
#define HWIO_TCSR_PHSS_UART_TURING_INT_SEL_n_OUTI(n,val)    \
        out_dword(HWIO_TCSR_PHSS_UART_TURING_INT_SEL_n_ADDR(n),val)
#define HWIO_TCSR_PHSS_UART_TURING_INT_SEL_n_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TCSR_PHSS_UART_TURING_INT_SEL_n_ADDR(n),mask,val,HWIO_TCSR_PHSS_UART_TURING_INT_SEL_n_INI(n))
#define HWIO_TCSR_PHSS_UART_TURING_INT_SEL_n_TURING_BLSP_UART_IRQ_ENABLE_BMSK                                           0xfff
#define HWIO_TCSR_PHSS_UART_TURING_INT_SEL_n_TURING_BLSP_UART_IRQ_ENABLE_SHFT                                             0x0

#define HWIO_TCSR_PHSS_UART_MSS_INT_SEL_n_ADDR(n)                                                                  (TCSR_TCSR_REGS_REG_BASE      + 0x0000b0c0 + 0x10 * (n))
#define HWIO_TCSR_PHSS_UART_MSS_INT_SEL_n_RMSK                                                                          0xfff
#define HWIO_TCSR_PHSS_UART_MSS_INT_SEL_n_MAXn                                                                              1
#define HWIO_TCSR_PHSS_UART_MSS_INT_SEL_n_INI(n)        \
        in_dword_masked(HWIO_TCSR_PHSS_UART_MSS_INT_SEL_n_ADDR(n), HWIO_TCSR_PHSS_UART_MSS_INT_SEL_n_RMSK)
#define HWIO_TCSR_PHSS_UART_MSS_INT_SEL_n_INMI(n,mask)    \
        in_dword_masked(HWIO_TCSR_PHSS_UART_MSS_INT_SEL_n_ADDR(n), mask)
#define HWIO_TCSR_PHSS_UART_MSS_INT_SEL_n_OUTI(n,val)    \
        out_dword(HWIO_TCSR_PHSS_UART_MSS_INT_SEL_n_ADDR(n),val)
#define HWIO_TCSR_PHSS_UART_MSS_INT_SEL_n_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TCSR_PHSS_UART_MSS_INT_SEL_n_ADDR(n),mask,val,HWIO_TCSR_PHSS_UART_MSS_INT_SEL_n_INI(n))
#define HWIO_TCSR_PHSS_UART_MSS_INT_SEL_n_MSS_BLSP_UART_IRQ_ENABLE_BMSK                                                 0xfff
#define HWIO_TCSR_PHSS_UART_MSS_INT_SEL_n_MSS_BLSP_UART_IRQ_ENABLE_SHFT                                                   0x0

#define HWIO_TCSR_PHSS_QUP_TURING_INT_SEL_n_ADDR(n)                                                                (TCSR_TCSR_REGS_REG_BASE      + 0x0000b100 + 0x10 * (n))
#define HWIO_TCSR_PHSS_QUP_TURING_INT_SEL_n_RMSK                                                                        0xfff
#define HWIO_TCSR_PHSS_QUP_TURING_INT_SEL_n_MAXn                                                                            1
#define HWIO_TCSR_PHSS_QUP_TURING_INT_SEL_n_INI(n)        \
        in_dword_masked(HWIO_TCSR_PHSS_QUP_TURING_INT_SEL_n_ADDR(n), HWIO_TCSR_PHSS_QUP_TURING_INT_SEL_n_RMSK)
#define HWIO_TCSR_PHSS_QUP_TURING_INT_SEL_n_INMI(n,mask)    \
        in_dword_masked(HWIO_TCSR_PHSS_QUP_TURING_INT_SEL_n_ADDR(n), mask)
#define HWIO_TCSR_PHSS_QUP_TURING_INT_SEL_n_OUTI(n,val)    \
        out_dword(HWIO_TCSR_PHSS_QUP_TURING_INT_SEL_n_ADDR(n),val)
#define HWIO_TCSR_PHSS_QUP_TURING_INT_SEL_n_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TCSR_PHSS_QUP_TURING_INT_SEL_n_ADDR(n),mask,val,HWIO_TCSR_PHSS_QUP_TURING_INT_SEL_n_INI(n))
#define HWIO_TCSR_PHSS_QUP_TURING_INT_SEL_n_TURING_BLSP_QUP_IRQ_ENABLE_BMSK                                             0xfff
#define HWIO_TCSR_PHSS_QUP_TURING_INT_SEL_n_TURING_BLSP_QUP_IRQ_ENABLE_SHFT                                               0x0

#define HWIO_TCSR_PHSS_QUP_MSS_INT_SEL_n_ADDR(n)                                                                   (TCSR_TCSR_REGS_REG_BASE      + 0x0000b140 + 0x10 * (n))
#define HWIO_TCSR_PHSS_QUP_MSS_INT_SEL_n_RMSK                                                                           0xfff
#define HWIO_TCSR_PHSS_QUP_MSS_INT_SEL_n_MAXn                                                                               1
#define HWIO_TCSR_PHSS_QUP_MSS_INT_SEL_n_INI(n)        \
        in_dword_masked(HWIO_TCSR_PHSS_QUP_MSS_INT_SEL_n_ADDR(n), HWIO_TCSR_PHSS_QUP_MSS_INT_SEL_n_RMSK)
#define HWIO_TCSR_PHSS_QUP_MSS_INT_SEL_n_INMI(n,mask)    \
        in_dword_masked(HWIO_TCSR_PHSS_QUP_MSS_INT_SEL_n_ADDR(n), mask)
#define HWIO_TCSR_PHSS_QUP_MSS_INT_SEL_n_OUTI(n,val)    \
        out_dword(HWIO_TCSR_PHSS_QUP_MSS_INT_SEL_n_ADDR(n),val)
#define HWIO_TCSR_PHSS_QUP_MSS_INT_SEL_n_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TCSR_PHSS_QUP_MSS_INT_SEL_n_ADDR(n),mask,val,HWIO_TCSR_PHSS_QUP_MSS_INT_SEL_n_INI(n))
#define HWIO_TCSR_PHSS_QUP_MSS_INT_SEL_n_MSS_BLSP_QUP_IRQ_ENABLE_BMSK                                                   0xfff
#define HWIO_TCSR_PHSS_QUP_MSS_INT_SEL_n_MSS_BLSP_QUP_IRQ_ENABLE_SHFT                                                     0x0

#define HWIO_TCSR_LPASS_QUP_INT_SEL_ADDR                                                                           (TCSR_TCSR_REGS_REG_BASE      + 0x0000b800)
#define HWIO_TCSR_LPASS_QUP_INT_SEL_RMSK                                                                                  0x7
#define HWIO_TCSR_LPASS_QUP_INT_SEL_IN          \
        in_dword_masked(HWIO_TCSR_LPASS_QUP_INT_SEL_ADDR, HWIO_TCSR_LPASS_QUP_INT_SEL_RMSK)
#define HWIO_TCSR_LPASS_QUP_INT_SEL_INM(m)      \
        in_dword_masked(HWIO_TCSR_LPASS_QUP_INT_SEL_ADDR, m)
#define HWIO_TCSR_LPASS_QUP_INT_SEL_OUT(v)      \
        out_dword(HWIO_TCSR_LPASS_QUP_INT_SEL_ADDR,v)
#define HWIO_TCSR_LPASS_QUP_INT_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_LPASS_QUP_INT_SEL_ADDR,m,v,HWIO_TCSR_LPASS_QUP_INT_SEL_IN)
#define HWIO_TCSR_LPASS_QUP_INT_SEL_LPASS_QUP_INT_ENABLE_BMSK                                                             0x7
#define HWIO_TCSR_LPASS_QUP_INT_SEL_LPASS_QUP_INT_ENABLE_SHFT                                                             0x0

#define HWIO_TCSR_LPASS_UART_INT_SEL_ADDR                                                                          (TCSR_TCSR_REGS_REG_BASE      + 0x0000bc00)
#define HWIO_TCSR_LPASS_UART_INT_SEL_RMSK                                                                                 0x7
#define HWIO_TCSR_LPASS_UART_INT_SEL_IN          \
        in_dword_masked(HWIO_TCSR_LPASS_UART_INT_SEL_ADDR, HWIO_TCSR_LPASS_UART_INT_SEL_RMSK)
#define HWIO_TCSR_LPASS_UART_INT_SEL_INM(m)      \
        in_dword_masked(HWIO_TCSR_LPASS_UART_INT_SEL_ADDR, m)
#define HWIO_TCSR_LPASS_UART_INT_SEL_OUT(v)      \
        out_dword(HWIO_TCSR_LPASS_UART_INT_SEL_ADDR,v)
#define HWIO_TCSR_LPASS_UART_INT_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_LPASS_UART_INT_SEL_ADDR,m,v,HWIO_TCSR_LPASS_UART_INT_SEL_IN)
#define HWIO_TCSR_LPASS_UART_INT_SEL_LPASS_UART_INT_ENABLE_BMSK                                                           0x7
#define HWIO_TCSR_LPASS_UART_INT_SEL_LPASS_UART_INT_ENABLE_SHFT                                                           0x0

#define HWIO_TCSR_TCSR_LDO_MISC_ADDR                                                                               (TCSR_TCSR_REGS_REG_BASE      + 0x0000b22c)
#define HWIO_TCSR_TCSR_LDO_MISC_RMSK                                                                               0xffffffff
#define HWIO_TCSR_TCSR_LDO_MISC_IN          \
        in_dword_masked(HWIO_TCSR_TCSR_LDO_MISC_ADDR, HWIO_TCSR_TCSR_LDO_MISC_RMSK)
#define HWIO_TCSR_TCSR_LDO_MISC_INM(m)      \
        in_dword_masked(HWIO_TCSR_TCSR_LDO_MISC_ADDR, m)
#define HWIO_TCSR_TCSR_LDO_MISC_OUT(v)      \
        out_dword(HWIO_TCSR_TCSR_LDO_MISC_ADDR,v)
#define HWIO_TCSR_TCSR_LDO_MISC_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_TCSR_LDO_MISC_ADDR,m,v,HWIO_TCSR_TCSR_LDO_MISC_IN)
#define HWIO_TCSR_TCSR_LDO_MISC_TCSR_LDO_MISC_BMSK                                                                 0xffffffff
#define HWIO_TCSR_TCSR_LDO_MISC_TCSR_LDO_MISC_SHFT                                                                        0x0

#define HWIO_TCSR_TCSR_USB_PHY_VLS_CLAMP_ADDR                                                                      (TCSR_TCSR_REGS_REG_BASE      + 0x0000b244)
#define HWIO_TCSR_TCSR_USB_PHY_VLS_CLAMP_RMSK                                                                      0xffffffff
#define HWIO_TCSR_TCSR_USB_PHY_VLS_CLAMP_IN          \
        in_dword_masked(HWIO_TCSR_TCSR_USB_PHY_VLS_CLAMP_ADDR, HWIO_TCSR_TCSR_USB_PHY_VLS_CLAMP_RMSK)
#define HWIO_TCSR_TCSR_USB_PHY_VLS_CLAMP_INM(m)      \
        in_dword_masked(HWIO_TCSR_TCSR_USB_PHY_VLS_CLAMP_ADDR, m)
#define HWIO_TCSR_TCSR_USB_PHY_VLS_CLAMP_OUT(v)      \
        out_dword(HWIO_TCSR_TCSR_USB_PHY_VLS_CLAMP_ADDR,v)
#define HWIO_TCSR_TCSR_USB_PHY_VLS_CLAMP_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_TCSR_USB_PHY_VLS_CLAMP_ADDR,m,v,HWIO_TCSR_TCSR_USB_PHY_VLS_CLAMP_IN)
#define HWIO_TCSR_TCSR_USB_PHY_VLS_CLAMP_TCSR_USB_PHY_VLS_CLAMP_BMSK                                               0xffffffff
#define HWIO_TCSR_TCSR_USB_PHY_VLS_CLAMP_TCSR_USB_PHY_VLS_CLAMP_SHFT                                                      0x0

#define HWIO_TCSR_USB3_DP_PHYMODE_ADDR                                                                             (TCSR_TCSR_REGS_REG_BASE      + 0x0000b248)
#define HWIO_TCSR_USB3_DP_PHYMODE_RMSK                                                                                    0x1
#define HWIO_TCSR_USB3_DP_PHYMODE_IN          \
        in_dword_masked(HWIO_TCSR_USB3_DP_PHYMODE_ADDR, HWIO_TCSR_USB3_DP_PHYMODE_RMSK)
#define HWIO_TCSR_USB3_DP_PHYMODE_INM(m)      \
        in_dword_masked(HWIO_TCSR_USB3_DP_PHYMODE_ADDR, m)
#define HWIO_TCSR_USB3_DP_PHYMODE_OUT(v)      \
        out_dword(HWIO_TCSR_USB3_DP_PHYMODE_ADDR,v)
#define HWIO_TCSR_USB3_DP_PHYMODE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_USB3_DP_PHYMODE_ADDR,m,v,HWIO_TCSR_USB3_DP_PHYMODE_IN)
#define HWIO_TCSR_USB3_DP_PHYMODE_USB3_DP_PHYMODE_BMSK                                                                    0x1
#define HWIO_TCSR_USB3_DP_PHYMODE_USB3_DP_PHYMODE_SHFT                                                                    0x0

#define HWIO_TCSR_QUSB2PHY_CLAMP_DIG_N_1P8_ADDR                                                                    (TCSR_TCSR_REGS_REG_BASE      + 0x0000b24c)
#define HWIO_TCSR_QUSB2PHY_CLAMP_DIG_N_1P8_RMSK                                                                           0x1
#define HWIO_TCSR_QUSB2PHY_CLAMP_DIG_N_1P8_IN          \
        in_dword_masked(HWIO_TCSR_QUSB2PHY_CLAMP_DIG_N_1P8_ADDR, HWIO_TCSR_QUSB2PHY_CLAMP_DIG_N_1P8_RMSK)
#define HWIO_TCSR_QUSB2PHY_CLAMP_DIG_N_1P8_INM(m)      \
        in_dword_masked(HWIO_TCSR_QUSB2PHY_CLAMP_DIG_N_1P8_ADDR, m)
#define HWIO_TCSR_QUSB2PHY_CLAMP_DIG_N_1P8_OUT(v)      \
        out_dword(HWIO_TCSR_QUSB2PHY_CLAMP_DIG_N_1P8_ADDR,v)
#define HWIO_TCSR_QUSB2PHY_CLAMP_DIG_N_1P8_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_QUSB2PHY_CLAMP_DIG_N_1P8_ADDR,m,v,HWIO_TCSR_QUSB2PHY_CLAMP_DIG_N_1P8_IN)
#define HWIO_TCSR_QUSB2PHY_CLAMP_DIG_N_1P8_QUSB2PHY_CLAMP_DIG_N_1P8_BMSK                                                  0x1
#define HWIO_TCSR_QUSB2PHY_CLAMP_DIG_N_1P8_QUSB2PHY_CLAMP_DIG_N_1P8_SHFT                                                  0x0

#define HWIO_TCSR_COPSS_USB_CONTROL_WITH_JDR_ADDR                                                                  (TCSR_TCSR_REGS_REG_BASE      + 0x0000b204)
#define HWIO_TCSR_COPSS_USB_CONTROL_WITH_JDR_RMSK                                                                  0xffffffff
#define HWIO_TCSR_COPSS_USB_CONTROL_WITH_JDR_IN          \
        in_dword_masked(HWIO_TCSR_COPSS_USB_CONTROL_WITH_JDR_ADDR, HWIO_TCSR_COPSS_USB_CONTROL_WITH_JDR_RMSK)
#define HWIO_TCSR_COPSS_USB_CONTROL_WITH_JDR_INM(m)      \
        in_dword_masked(HWIO_TCSR_COPSS_USB_CONTROL_WITH_JDR_ADDR, m)
#define HWIO_TCSR_COPSS_USB_CONTROL_WITH_JDR_OUT(v)      \
        out_dword(HWIO_TCSR_COPSS_USB_CONTROL_WITH_JDR_ADDR,v)
#define HWIO_TCSR_COPSS_USB_CONTROL_WITH_JDR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_COPSS_USB_CONTROL_WITH_JDR_ADDR,m,v,HWIO_TCSR_COPSS_USB_CONTROL_WITH_JDR_IN)
#define HWIO_TCSR_COPSS_USB_CONTROL_WITH_JDR_COPSS_USB_CONTROL_WITH_JDR_BMSK                                       0xffffffff
#define HWIO_TCSR_COPSS_USB_CONTROL_WITH_JDR_COPSS_USB_CONTROL_WITH_JDR_SHFT                                              0x0

#define HWIO_TCSR_UFS_SATA_CONTROL_WITH_JDR_ADDR                                                                   (TCSR_TCSR_REGS_REG_BASE      + 0x0000b20c)
#define HWIO_TCSR_UFS_SATA_CONTROL_WITH_JDR_RMSK                                                                          0x1
#define HWIO_TCSR_UFS_SATA_CONTROL_WITH_JDR_IN          \
        in_dword_masked(HWIO_TCSR_UFS_SATA_CONTROL_WITH_JDR_ADDR, HWIO_TCSR_UFS_SATA_CONTROL_WITH_JDR_RMSK)
#define HWIO_TCSR_UFS_SATA_CONTROL_WITH_JDR_INM(m)      \
        in_dword_masked(HWIO_TCSR_UFS_SATA_CONTROL_WITH_JDR_ADDR, m)
#define HWIO_TCSR_UFS_SATA_CONTROL_WITH_JDR_OUT(v)      \
        out_dword(HWIO_TCSR_UFS_SATA_CONTROL_WITH_JDR_ADDR,v)
#define HWIO_TCSR_UFS_SATA_CONTROL_WITH_JDR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_UFS_SATA_CONTROL_WITH_JDR_ADDR,m,v,HWIO_TCSR_UFS_SATA_CONTROL_WITH_JDR_IN)
#define HWIO_TCSR_UFS_SATA_CONTROL_WITH_JDR_UFS_SATA_CTRL_SEL_BMSK                                                        0x1
#define HWIO_TCSR_UFS_SATA_CONTROL_WITH_JDR_UFS_SATA_CTRL_SEL_SHFT                                                        0x0

#define HWIO_TCSR_PHSS_QDSS_HW_EVENTS_CTRL_n_ADDR(n)                                                               (TCSR_TCSR_REGS_REG_BASE      + 0x0000b160 + 0x4 * (n))
#define HWIO_TCSR_PHSS_QDSS_HW_EVENTS_CTRL_n_RMSK                                                                  0x8000007f
#define HWIO_TCSR_PHSS_QDSS_HW_EVENTS_CTRL_n_MAXn                                                                          31
#define HWIO_TCSR_PHSS_QDSS_HW_EVENTS_CTRL_n_INI(n)        \
        in_dword_masked(HWIO_TCSR_PHSS_QDSS_HW_EVENTS_CTRL_n_ADDR(n), HWIO_TCSR_PHSS_QDSS_HW_EVENTS_CTRL_n_RMSK)
#define HWIO_TCSR_PHSS_QDSS_HW_EVENTS_CTRL_n_INMI(n,mask)    \
        in_dword_masked(HWIO_TCSR_PHSS_QDSS_HW_EVENTS_CTRL_n_ADDR(n), mask)
#define HWIO_TCSR_PHSS_QDSS_HW_EVENTS_CTRL_n_OUTI(n,val)    \
        out_dword(HWIO_TCSR_PHSS_QDSS_HW_EVENTS_CTRL_n_ADDR(n),val)
#define HWIO_TCSR_PHSS_QDSS_HW_EVENTS_CTRL_n_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TCSR_PHSS_QDSS_HW_EVENTS_CTRL_n_ADDR(n),mask,val,HWIO_TCSR_PHSS_QDSS_HW_EVENTS_CTRL_n_INI(n))
#define HWIO_TCSR_PHSS_QDSS_HW_EVENTS_CTRL_n_PHSS_QDSS_HW_EVENTS_EN_BMSK                                           0x80000000
#define HWIO_TCSR_PHSS_QDSS_HW_EVENTS_CTRL_n_PHSS_QDSS_HW_EVENTS_EN_SHFT                                                 0x1f
#define HWIO_TCSR_PHSS_QDSS_HW_EVENTS_CTRL_n_PHSS_QDSS_HW_EVENTS_SEL_BMSK                                                0x7f
#define HWIO_TCSR_PHSS_QDSS_HW_EVENTS_CTRL_n_PHSS_QDSS_HW_EVENTS_SEL_SHFT                                                 0x0

#define HWIO_TCSR_TCSR_GEN_QDSS_HW_EVENTS_CTRL_n_ADDR(n)                                                           (TCSR_TCSR_REGS_REG_BASE      + 0x0000b360 + 0x4 * (n))
#define HWIO_TCSR_TCSR_GEN_QDSS_HW_EVENTS_CTRL_n_RMSK                                                              0x8000001f
#define HWIO_TCSR_TCSR_GEN_QDSS_HW_EVENTS_CTRL_n_MAXn                                                                      31
#define HWIO_TCSR_TCSR_GEN_QDSS_HW_EVENTS_CTRL_n_INI(n)        \
        in_dword_masked(HWIO_TCSR_TCSR_GEN_QDSS_HW_EVENTS_CTRL_n_ADDR(n), HWIO_TCSR_TCSR_GEN_QDSS_HW_EVENTS_CTRL_n_RMSK)
#define HWIO_TCSR_TCSR_GEN_QDSS_HW_EVENTS_CTRL_n_INMI(n,mask)    \
        in_dword_masked(HWIO_TCSR_TCSR_GEN_QDSS_HW_EVENTS_CTRL_n_ADDR(n), mask)
#define HWIO_TCSR_TCSR_GEN_QDSS_HW_EVENTS_CTRL_n_OUTI(n,val)    \
        out_dword(HWIO_TCSR_TCSR_GEN_QDSS_HW_EVENTS_CTRL_n_ADDR(n),val)
#define HWIO_TCSR_TCSR_GEN_QDSS_HW_EVENTS_CTRL_n_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TCSR_TCSR_GEN_QDSS_HW_EVENTS_CTRL_n_ADDR(n),mask,val,HWIO_TCSR_TCSR_GEN_QDSS_HW_EVENTS_CTRL_n_INI(n))
#define HWIO_TCSR_TCSR_GEN_QDSS_HW_EVENTS_CTRL_n_TCSR_GEN_QDSS_HW_EVENTS_EN_BMSK                                   0x80000000
#define HWIO_TCSR_TCSR_GEN_QDSS_HW_EVENTS_CTRL_n_TCSR_GEN_QDSS_HW_EVENTS_EN_SHFT                                         0x1f
#define HWIO_TCSR_TCSR_GEN_QDSS_HW_EVENTS_CTRL_n_TCSR_GEN_QDSS_HW_EVENTS_SEL_BMSK                                        0x1f
#define HWIO_TCSR_TCSR_GEN_QDSS_HW_EVENTS_CTRL_n_TCSR_GEN_QDSS_HW_EVENTS_SEL_SHFT                                         0x0

#define HWIO_TCSR_TCSR_GEN_MSS0_QDSS_HW_EVENTS_CTRL_n_ADDR(n)                                                      (TCSR_TCSR_REGS_REG_BASE      + 0x0000b760 + 0x4 * (n))
#define HWIO_TCSR_TCSR_GEN_MSS0_QDSS_HW_EVENTS_CTRL_n_RMSK                                                         0x80000001
#define HWIO_TCSR_TCSR_GEN_MSS0_QDSS_HW_EVENTS_CTRL_n_MAXn                                                                 31
#define HWIO_TCSR_TCSR_GEN_MSS0_QDSS_HW_EVENTS_CTRL_n_INI(n)        \
        in_dword_masked(HWIO_TCSR_TCSR_GEN_MSS0_QDSS_HW_EVENTS_CTRL_n_ADDR(n), HWIO_TCSR_TCSR_GEN_MSS0_QDSS_HW_EVENTS_CTRL_n_RMSK)
#define HWIO_TCSR_TCSR_GEN_MSS0_QDSS_HW_EVENTS_CTRL_n_INMI(n,mask)    \
        in_dword_masked(HWIO_TCSR_TCSR_GEN_MSS0_QDSS_HW_EVENTS_CTRL_n_ADDR(n), mask)
#define HWIO_TCSR_TCSR_GEN_MSS0_QDSS_HW_EVENTS_CTRL_n_OUTI(n,val)    \
        out_dword(HWIO_TCSR_TCSR_GEN_MSS0_QDSS_HW_EVENTS_CTRL_n_ADDR(n),val)
#define HWIO_TCSR_TCSR_GEN_MSS0_QDSS_HW_EVENTS_CTRL_n_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TCSR_TCSR_GEN_MSS0_QDSS_HW_EVENTS_CTRL_n_ADDR(n),mask,val,HWIO_TCSR_TCSR_GEN_MSS0_QDSS_HW_EVENTS_CTRL_n_INI(n))
#define HWIO_TCSR_TCSR_GEN_MSS0_QDSS_HW_EVENTS_CTRL_n_TCSR_GEN_MSS0_QDSS_HW_EVENTS_EN_BMSK                         0x80000000
#define HWIO_TCSR_TCSR_GEN_MSS0_QDSS_HW_EVENTS_CTRL_n_TCSR_GEN_MSS0_QDSS_HW_EVENTS_EN_SHFT                               0x1f
#define HWIO_TCSR_TCSR_GEN_MSS0_QDSS_HW_EVENTS_CTRL_n_TCSR_GEN_MSS0_QDSS_HW_EVENTS_SEL_BMSK                               0x1
#define HWIO_TCSR_TCSR_GEN_MSS0_QDSS_HW_EVENTS_CTRL_n_TCSR_GEN_MSS0_QDSS_HW_EVENTS_SEL_SHFT                               0x0

#define HWIO_TCSR_TCSR_GEN_MSS1_QDSS_HW_EVENTS_CTRL_n_ADDR(n)                                                      (TCSR_TCSR_REGS_REG_BASE      + 0x0000bf60 + 0x4 * (n))
#define HWIO_TCSR_TCSR_GEN_MSS1_QDSS_HW_EVENTS_CTRL_n_RMSK                                                         0x80000007
#define HWIO_TCSR_TCSR_GEN_MSS1_QDSS_HW_EVENTS_CTRL_n_MAXn                                                                 31
#define HWIO_TCSR_TCSR_GEN_MSS1_QDSS_HW_EVENTS_CTRL_n_INI(n)        \
        in_dword_masked(HWIO_TCSR_TCSR_GEN_MSS1_QDSS_HW_EVENTS_CTRL_n_ADDR(n), HWIO_TCSR_TCSR_GEN_MSS1_QDSS_HW_EVENTS_CTRL_n_RMSK)
#define HWIO_TCSR_TCSR_GEN_MSS1_QDSS_HW_EVENTS_CTRL_n_INMI(n,mask)    \
        in_dword_masked(HWIO_TCSR_TCSR_GEN_MSS1_QDSS_HW_EVENTS_CTRL_n_ADDR(n), mask)
#define HWIO_TCSR_TCSR_GEN_MSS1_QDSS_HW_EVENTS_CTRL_n_OUTI(n,val)    \
        out_dword(HWIO_TCSR_TCSR_GEN_MSS1_QDSS_HW_EVENTS_CTRL_n_ADDR(n),val)
#define HWIO_TCSR_TCSR_GEN_MSS1_QDSS_HW_EVENTS_CTRL_n_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TCSR_TCSR_GEN_MSS1_QDSS_HW_EVENTS_CTRL_n_ADDR(n),mask,val,HWIO_TCSR_TCSR_GEN_MSS1_QDSS_HW_EVENTS_CTRL_n_INI(n))
#define HWIO_TCSR_TCSR_GEN_MSS1_QDSS_HW_EVENTS_CTRL_n_TCSR_GEN_MSS1_QDSS_HW_EVENTS_EN_BMSK                         0x80000000
#define HWIO_TCSR_TCSR_GEN_MSS1_QDSS_HW_EVENTS_CTRL_n_TCSR_GEN_MSS1_QDSS_HW_EVENTS_EN_SHFT                               0x1f
#define HWIO_TCSR_TCSR_GEN_MSS1_QDSS_HW_EVENTS_CTRL_n_TCSR_GEN_MSS1_QDSS_HW_EVENTS_SEL_LAST_BMSK                          0x4
#define HWIO_TCSR_TCSR_GEN_MSS1_QDSS_HW_EVENTS_CTRL_n_TCSR_GEN_MSS1_QDSS_HW_EVENTS_SEL_LAST_SHFT                          0x2
#define HWIO_TCSR_TCSR_GEN_MSS1_QDSS_HW_EVENTS_CTRL_n_TCSR_GEN_MSS1_QDSS_HW_EVENTS_SEL_BMSK                               0x3
#define HWIO_TCSR_TCSR_GEN_MSS1_QDSS_HW_EVENTS_CTRL_n_TCSR_GEN_MSS1_QDSS_HW_EVENTS_SEL_SHFT                               0x0

#define HWIO_TCSR_QPDI_DISABLE_CFG_ADDR                                                                            (TCSR_TCSR_REGS_REG_BASE      + 0x00001000)
#define HWIO_TCSR_QPDI_DISABLE_CFG_RMSK                                                                                 0x303
#define HWIO_TCSR_QPDI_DISABLE_CFG_IN          \
        in_dword_masked(HWIO_TCSR_QPDI_DISABLE_CFG_ADDR, HWIO_TCSR_QPDI_DISABLE_CFG_RMSK)
#define HWIO_TCSR_QPDI_DISABLE_CFG_INM(m)      \
        in_dword_masked(HWIO_TCSR_QPDI_DISABLE_CFG_ADDR, m)
#define HWIO_TCSR_QPDI_DISABLE_CFG_OUT(v)      \
        out_dword(HWIO_TCSR_QPDI_DISABLE_CFG_ADDR,v)
#define HWIO_TCSR_QPDI_DISABLE_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_QPDI_DISABLE_CFG_ADDR,m,v,HWIO_TCSR_QPDI_DISABLE_CFG_IN)
#define HWIO_TCSR_QPDI_DISABLE_CFG_QPDI_SPMI_DBG_ACK_BMSK                                                               0x200
#define HWIO_TCSR_QPDI_DISABLE_CFG_QPDI_SPMI_DBG_ACK_SHFT                                                                 0x9
#define HWIO_TCSR_QPDI_DISABLE_CFG_QPDI_SPMI_DBG_REQ_BMSK                                                               0x100
#define HWIO_TCSR_QPDI_DISABLE_CFG_QPDI_SPMI_DBG_REQ_SHFT                                                                 0x8
#define HWIO_TCSR_QPDI_DISABLE_CFG_SPMI_HANDSHAKE_DISABLE_BMSK                                                            0x2
#define HWIO_TCSR_QPDI_DISABLE_CFG_SPMI_HANDSHAKE_DISABLE_SHFT                                                            0x1
#define HWIO_TCSR_QPDI_DISABLE_CFG_QPDI_DISABLE_CFG_BMSK                                                                  0x1
#define HWIO_TCSR_QPDI_DISABLE_CFG_QPDI_DISABLE_CFG_SHFT                                                                  0x0

#define HWIO_TCSR_DIFFERENTIAL_TEST_CLOCK_1_ADDR                                                                   (TCSR_TCSR_REGS_REG_BASE      + 0x00016000)
#define HWIO_TCSR_DIFFERENTIAL_TEST_CLOCK_1_RMSK                                                                          0x3
#define HWIO_TCSR_DIFFERENTIAL_TEST_CLOCK_1_IN          \
        in_dword_masked(HWIO_TCSR_DIFFERENTIAL_TEST_CLOCK_1_ADDR, HWIO_TCSR_DIFFERENTIAL_TEST_CLOCK_1_RMSK)
#define HWIO_TCSR_DIFFERENTIAL_TEST_CLOCK_1_INM(m)      \
        in_dword_masked(HWIO_TCSR_DIFFERENTIAL_TEST_CLOCK_1_ADDR, m)
#define HWIO_TCSR_DIFFERENTIAL_TEST_CLOCK_1_OUT(v)      \
        out_dword(HWIO_TCSR_DIFFERENTIAL_TEST_CLOCK_1_ADDR,v)
#define HWIO_TCSR_DIFFERENTIAL_TEST_CLOCK_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_DIFFERENTIAL_TEST_CLOCK_1_ADDR,m,v,HWIO_TCSR_DIFFERENTIAL_TEST_CLOCK_1_IN)
#define HWIO_TCSR_DIFFERENTIAL_TEST_CLOCK_1_TEST_EN_1_BMSK                                                                0x2
#define HWIO_TCSR_DIFFERENTIAL_TEST_CLOCK_1_TEST_EN_1_SHFT                                                                0x1
#define HWIO_TCSR_DIFFERENTIAL_TEST_CLOCK_1_TEST_DATA_1_BMSK                                                              0x1
#define HWIO_TCSR_DIFFERENTIAL_TEST_CLOCK_1_TEST_DATA_1_SHFT                                                              0x0

#define HWIO_TCSR_DIFFERENTIAL_TEST_CLOCK_0_ADDR                                                                   (TCSR_TCSR_REGS_REG_BASE      + 0x00016004)
#define HWIO_TCSR_DIFFERENTIAL_TEST_CLOCK_0_RMSK                                                                          0x3
#define HWIO_TCSR_DIFFERENTIAL_TEST_CLOCK_0_IN          \
        in_dword_masked(HWIO_TCSR_DIFFERENTIAL_TEST_CLOCK_0_ADDR, HWIO_TCSR_DIFFERENTIAL_TEST_CLOCK_0_RMSK)
#define HWIO_TCSR_DIFFERENTIAL_TEST_CLOCK_0_INM(m)      \
        in_dword_masked(HWIO_TCSR_DIFFERENTIAL_TEST_CLOCK_0_ADDR, m)
#define HWIO_TCSR_DIFFERENTIAL_TEST_CLOCK_0_OUT(v)      \
        out_dword(HWIO_TCSR_DIFFERENTIAL_TEST_CLOCK_0_ADDR,v)
#define HWIO_TCSR_DIFFERENTIAL_TEST_CLOCK_0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_DIFFERENTIAL_TEST_CLOCK_0_ADDR,m,v,HWIO_TCSR_DIFFERENTIAL_TEST_CLOCK_0_IN)
#define HWIO_TCSR_DIFFERENTIAL_TEST_CLOCK_0_TEST_EN_0_BMSK                                                                0x2
#define HWIO_TCSR_DIFFERENTIAL_TEST_CLOCK_0_TEST_EN_0_SHFT                                                                0x1
#define HWIO_TCSR_DIFFERENTIAL_TEST_CLOCK_0_TEST_DATA_0_BMSK                                                              0x1
#define HWIO_TCSR_DIFFERENTIAL_TEST_CLOCK_0_TEST_DATA_0_SHFT                                                              0x0

#define HWIO_TCSR_BIAS_REF_LS_ATEST_ADDR                                                                           (TCSR_TCSR_REGS_REG_BASE      + 0x00017000)
#define HWIO_TCSR_BIAS_REF_LS_ATEST_RMSK                                                                                 0xff
#define HWIO_TCSR_BIAS_REF_LS_ATEST_IN          \
        in_dword_masked(HWIO_TCSR_BIAS_REF_LS_ATEST_ADDR, HWIO_TCSR_BIAS_REF_LS_ATEST_RMSK)
#define HWIO_TCSR_BIAS_REF_LS_ATEST_INM(m)      \
        in_dword_masked(HWIO_TCSR_BIAS_REF_LS_ATEST_ADDR, m)
#define HWIO_TCSR_BIAS_REF_LS_ATEST_OUT(v)      \
        out_dword(HWIO_TCSR_BIAS_REF_LS_ATEST_ADDR,v)
#define HWIO_TCSR_BIAS_REF_LS_ATEST_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_BIAS_REF_LS_ATEST_ADDR,m,v,HWIO_TCSR_BIAS_REF_LS_ATEST_IN)
#define HWIO_TCSR_BIAS_REF_LS_ATEST_AUXBUF_EN_SAPRE_BMSK                                                                 0x80
#define HWIO_TCSR_BIAS_REF_LS_ATEST_AUXBUF_EN_SAPRE_SHFT                                                                  0x7
#define HWIO_TCSR_BIAS_REF_LS_ATEST_ATEST_EN_SPARE_BMSK                                                                  0x40
#define HWIO_TCSR_BIAS_REF_LS_ATEST_ATEST_EN_SPARE_SHFT                                                                   0x6
#define HWIO_TCSR_BIAS_REF_LS_ATEST_AUXBUF_EN_3_BMSK                                                                     0x20
#define HWIO_TCSR_BIAS_REF_LS_ATEST_AUXBUF_EN_3_SHFT                                                                      0x5
#define HWIO_TCSR_BIAS_REF_LS_ATEST_ATEST_EN_3_BMSK                                                                      0x10
#define HWIO_TCSR_BIAS_REF_LS_ATEST_ATEST_EN_3_SHFT                                                                       0x4
#define HWIO_TCSR_BIAS_REF_LS_ATEST_AUXBUF_EN_2_BMSK                                                                      0x8
#define HWIO_TCSR_BIAS_REF_LS_ATEST_AUXBUF_EN_2_SHFT                                                                      0x3
#define HWIO_TCSR_BIAS_REF_LS_ATEST_ATEST_EN_2_BMSK                                                                       0x4
#define HWIO_TCSR_BIAS_REF_LS_ATEST_ATEST_EN_2_SHFT                                                                       0x2
#define HWIO_TCSR_BIAS_REF_LS_ATEST_AUXBUF_EN_1_BMSK                                                                      0x2
#define HWIO_TCSR_BIAS_REF_LS_ATEST_AUXBUF_EN_1_SHFT                                                                      0x1
#define HWIO_TCSR_BIAS_REF_LS_ATEST_ATEST_EN_1_BMSK                                                                       0x1
#define HWIO_TCSR_BIAS_REF_LS_ATEST_ATEST_EN_1_SHFT                                                                       0x0

#define HWIO_TCSR_LDO_SLEEP_CTRL_ADDR                                                                              (TCSR_TCSR_REGS_REG_BASE      + 0x0000c000)
#define HWIO_TCSR_LDO_SLEEP_CTRL_RMSK                                                                                     0x1
#define HWIO_TCSR_LDO_SLEEP_CTRL_IN          \
        in_dword_masked(HWIO_TCSR_LDO_SLEEP_CTRL_ADDR, HWIO_TCSR_LDO_SLEEP_CTRL_RMSK)
#define HWIO_TCSR_LDO_SLEEP_CTRL_INM(m)      \
        in_dword_masked(HWIO_TCSR_LDO_SLEEP_CTRL_ADDR, m)
#define HWIO_TCSR_LDO_SLEEP_CTRL_OUT(v)      \
        out_dword(HWIO_TCSR_LDO_SLEEP_CTRL_ADDR,v)
#define HWIO_TCSR_LDO_SLEEP_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_LDO_SLEEP_CTRL_ADDR,m,v,HWIO_TCSR_LDO_SLEEP_CTRL_IN)
#define HWIO_TCSR_LDO_SLEEP_CTRL_LDO_SLEEP_BMSK                                                                           0x1
#define HWIO_TCSR_LDO_SLEEP_CTRL_LDO_SLEEP_SHFT                                                                           0x0

#define HWIO_TCSR_LDO_UPDATE_STATE_CTRL_ADDR                                                                       (TCSR_TCSR_REGS_REG_BASE      + 0x0000c004)
#define HWIO_TCSR_LDO_UPDATE_STATE_CTRL_RMSK                                                                              0x1
#define HWIO_TCSR_LDO_UPDATE_STATE_CTRL_IN          \
        in_dword_masked(HWIO_TCSR_LDO_UPDATE_STATE_CTRL_ADDR, HWIO_TCSR_LDO_UPDATE_STATE_CTRL_RMSK)
#define HWIO_TCSR_LDO_UPDATE_STATE_CTRL_INM(m)      \
        in_dword_masked(HWIO_TCSR_LDO_UPDATE_STATE_CTRL_ADDR, m)
#define HWIO_TCSR_LDO_UPDATE_STATE_CTRL_OUT(v)      \
        out_dword(HWIO_TCSR_LDO_UPDATE_STATE_CTRL_ADDR,v)
#define HWIO_TCSR_LDO_UPDATE_STATE_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_LDO_UPDATE_STATE_CTRL_ADDR,m,v,HWIO_TCSR_LDO_UPDATE_STATE_CTRL_IN)
#define HWIO_TCSR_LDO_UPDATE_STATE_CTRL_LDO_UPDATE_STATE_BMSK                                                             0x1
#define HWIO_TCSR_LDO_UPDATE_STATE_CTRL_LDO_UPDATE_STATE_SHFT                                                             0x0

#define HWIO_TCSR_LDO_OBIAS_CTRL_ADDR                                                                              (TCSR_TCSR_REGS_REG_BASE      + 0x0000c008)
#define HWIO_TCSR_LDO_OBIAS_CTRL_RMSK                                                                                     0x1
#define HWIO_TCSR_LDO_OBIAS_CTRL_IN          \
        in_dword_masked(HWIO_TCSR_LDO_OBIAS_CTRL_ADDR, HWIO_TCSR_LDO_OBIAS_CTRL_RMSK)
#define HWIO_TCSR_LDO_OBIAS_CTRL_INM(m)      \
        in_dword_masked(HWIO_TCSR_LDO_OBIAS_CTRL_ADDR, m)
#define HWIO_TCSR_LDO_OBIAS_CTRL_OUT(v)      \
        out_dword(HWIO_TCSR_LDO_OBIAS_CTRL_ADDR,v)
#define HWIO_TCSR_LDO_OBIAS_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_LDO_OBIAS_CTRL_ADDR,m,v,HWIO_TCSR_LDO_OBIAS_CTRL_IN)
#define HWIO_TCSR_LDO_OBIAS_CTRL_LDO_OBIAS_ON_BMSK                                                                        0x1
#define HWIO_TCSR_LDO_OBIAS_CTRL_LDO_OBIAS_ON_SHFT                                                                        0x0

#define HWIO_TCSR_LDO_VREF_CONFIG_ADDR                                                                             (TCSR_TCSR_REGS_REG_BASE      + 0x0000c00c)
#define HWIO_TCSR_LDO_VREF_CONFIG_RMSK                                                                                    0xf
#define HWIO_TCSR_LDO_VREF_CONFIG_IN          \
        in_dword_masked(HWIO_TCSR_LDO_VREF_CONFIG_ADDR, HWIO_TCSR_LDO_VREF_CONFIG_RMSK)
#define HWIO_TCSR_LDO_VREF_CONFIG_INM(m)      \
        in_dword_masked(HWIO_TCSR_LDO_VREF_CONFIG_ADDR, m)
#define HWIO_TCSR_LDO_VREF_CONFIG_OUT(v)      \
        out_dword(HWIO_TCSR_LDO_VREF_CONFIG_ADDR,v)
#define HWIO_TCSR_LDO_VREF_CONFIG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_LDO_VREF_CONFIG_ADDR,m,v,HWIO_TCSR_LDO_VREF_CONFIG_IN)
#define HWIO_TCSR_LDO_VREF_CONFIG_LDO_VREF_CONFIG_BMSK                                                                    0xf
#define HWIO_TCSR_LDO_VREF_CONFIG_LDO_VREF_CONFIG_SHFT                                                                    0x0

#define HWIO_TCSR_LDO_IB_CONFIG_ADDR                                                                               (TCSR_TCSR_REGS_REG_BASE      + 0x0000c010)
#define HWIO_TCSR_LDO_IB_CONFIG_RMSK                                                                                      0x7
#define HWIO_TCSR_LDO_IB_CONFIG_IN          \
        in_dword_masked(HWIO_TCSR_LDO_IB_CONFIG_ADDR, HWIO_TCSR_LDO_IB_CONFIG_RMSK)
#define HWIO_TCSR_LDO_IB_CONFIG_INM(m)      \
        in_dword_masked(HWIO_TCSR_LDO_IB_CONFIG_ADDR, m)
#define HWIO_TCSR_LDO_IB_CONFIG_OUT(v)      \
        out_dword(HWIO_TCSR_LDO_IB_CONFIG_ADDR,v)
#define HWIO_TCSR_LDO_IB_CONFIG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_LDO_IB_CONFIG_ADDR,m,v,HWIO_TCSR_LDO_IB_CONFIG_IN)
#define HWIO_TCSR_LDO_IB_CONFIG_LDO_IB_CONFIG_BMSK                                                                        0x7
#define HWIO_TCSR_LDO_IB_CONFIG_LDO_IB_CONFIG_SHFT                                                                        0x0

#define HWIO_TCSR_LDO_BGC_CONFIG_ADDR                                                                              (TCSR_TCSR_REGS_REG_BASE      + 0x0000c014)
#define HWIO_TCSR_LDO_BGC_CONFIG_RMSK                                                                                     0x7
#define HWIO_TCSR_LDO_BGC_CONFIG_IN          \
        in_dword_masked(HWIO_TCSR_LDO_BGC_CONFIG_ADDR, HWIO_TCSR_LDO_BGC_CONFIG_RMSK)
#define HWIO_TCSR_LDO_BGC_CONFIG_INM(m)      \
        in_dword_masked(HWIO_TCSR_LDO_BGC_CONFIG_ADDR, m)
#define HWIO_TCSR_LDO_BGC_CONFIG_OUT(v)      \
        out_dword(HWIO_TCSR_LDO_BGC_CONFIG_ADDR,v)
#define HWIO_TCSR_LDO_BGC_CONFIG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_LDO_BGC_CONFIG_ADDR,m,v,HWIO_TCSR_LDO_BGC_CONFIG_IN)
#define HWIO_TCSR_LDO_BGC_CONFIG_LDO_BGC_BMSK                                                                             0x7
#define HWIO_TCSR_LDO_BGC_CONFIG_LDO_BGC_SHFT                                                                             0x0

#define HWIO_TCSR_LDO_VREF_CTRL_ADDR                                                                               (TCSR_TCSR_REGS_REG_BASE      + 0x0000c018)
#define HWIO_TCSR_LDO_VREF_CTRL_RMSK                                                                                  0x10001
#define HWIO_TCSR_LDO_VREF_CTRL_IN          \
        in_dword_masked(HWIO_TCSR_LDO_VREF_CTRL_ADDR, HWIO_TCSR_LDO_VREF_CTRL_RMSK)
#define HWIO_TCSR_LDO_VREF_CTRL_INM(m)      \
        in_dword_masked(HWIO_TCSR_LDO_VREF_CTRL_ADDR, m)
#define HWIO_TCSR_LDO_VREF_CTRL_OUT(v)      \
        out_dword(HWIO_TCSR_LDO_VREF_CTRL_ADDR,v)
#define HWIO_TCSR_LDO_VREF_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_LDO_VREF_CTRL_ADDR,m,v,HWIO_TCSR_LDO_VREF_CTRL_IN)
#define HWIO_TCSR_LDO_VREF_CTRL_LDO_VREF_SEL_OVR_BMSK                                                                 0x10000
#define HWIO_TCSR_LDO_VREF_CTRL_LDO_VREF_SEL_OVR_SHFT                                                                    0x10
#define HWIO_TCSR_LDO_VREF_CTRL_LDO_VREF_SEL_SW_BMSK                                                                      0x1
#define HWIO_TCSR_LDO_VREF_CTRL_LDO_VREF_SEL_SW_SHFT                                                                      0x0

#define HWIO_TCSR_LDO_LD_EN_ADDR                                                                                   (TCSR_TCSR_REGS_REG_BASE      + 0x0000c01c)
#define HWIO_TCSR_LDO_LD_EN_RMSK                                                                                   0x80000000
#define HWIO_TCSR_LDO_LD_EN_IN          \
        in_dword_masked(HWIO_TCSR_LDO_LD_EN_ADDR, HWIO_TCSR_LDO_LD_EN_RMSK)
#define HWIO_TCSR_LDO_LD_EN_INM(m)      \
        in_dword_masked(HWIO_TCSR_LDO_LD_EN_ADDR, m)
#define HWIO_TCSR_LDO_LD_EN_OUT(v)      \
        out_dword(HWIO_TCSR_LDO_LD_EN_ADDR,v)
#define HWIO_TCSR_LDO_LD_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_LDO_LD_EN_ADDR,m,v,HWIO_TCSR_LDO_LD_EN_IN)
#define HWIO_TCSR_LDO_LD_EN_LDO_LD_EN_BMSK                                                                         0x80000000
#define HWIO_TCSR_LDO_LD_EN_LDO_LD_EN_SHFT                                                                               0x1f

#define HWIO_TCSR_LDO_LD_CTRL_ADDR                                                                                 (TCSR_TCSR_REGS_REG_BASE      + 0x0000c020)
#define HWIO_TCSR_LDO_LD_CTRL_RMSK                                                                                   0xff00ff
#define HWIO_TCSR_LDO_LD_CTRL_IN          \
        in_dword_masked(HWIO_TCSR_LDO_LD_CTRL_ADDR, HWIO_TCSR_LDO_LD_CTRL_RMSK)
#define HWIO_TCSR_LDO_LD_CTRL_INM(m)      \
        in_dword_masked(HWIO_TCSR_LDO_LD_CTRL_ADDR, m)
#define HWIO_TCSR_LDO_LD_CTRL_OUT(v)      \
        out_dword(HWIO_TCSR_LDO_LD_CTRL_ADDR,v)
#define HWIO_TCSR_LDO_LD_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_LDO_LD_CTRL_ADDR,m,v,HWIO_TCSR_LDO_LD_CTRL_IN)
#define HWIO_TCSR_LDO_LD_CTRL_LDO_LD_MSB_BMSK                                                                        0xff0000
#define HWIO_TCSR_LDO_LD_CTRL_LDO_LD_MSB_SHFT                                                                            0x10
#define HWIO_TCSR_LDO_LD_CTRL_LDO_LD_LSB_BMSK                                                                            0xff
#define HWIO_TCSR_LDO_LD_CTRL_LDO_LD_LSB_SHFT                                                                             0x0

#define HWIO_TCSR_LDO_OSC_RESETB_ADDR                                                                              (TCSR_TCSR_REGS_REG_BASE      + 0x0000c024)
#define HWIO_TCSR_LDO_OSC_RESETB_RMSK                                                                              0x80000000
#define HWIO_TCSR_LDO_OSC_RESETB_IN          \
        in_dword_masked(HWIO_TCSR_LDO_OSC_RESETB_ADDR, HWIO_TCSR_LDO_OSC_RESETB_RMSK)
#define HWIO_TCSR_LDO_OSC_RESETB_INM(m)      \
        in_dword_masked(HWIO_TCSR_LDO_OSC_RESETB_ADDR, m)
#define HWIO_TCSR_LDO_OSC_RESETB_OUT(v)      \
        out_dword(HWIO_TCSR_LDO_OSC_RESETB_ADDR,v)
#define HWIO_TCSR_LDO_OSC_RESETB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_LDO_OSC_RESETB_ADDR,m,v,HWIO_TCSR_LDO_OSC_RESETB_IN)
#define HWIO_TCSR_LDO_OSC_RESETB_LDO_OSC_RESETB_BMSK                                                               0x80000000
#define HWIO_TCSR_LDO_OSC_RESETB_LDO_OSC_RESETB_SHFT                                                                     0x1f

#define HWIO_TCSR_LDO_OSC_CTRL_ADDR                                                                                (TCSR_TCSR_REGS_REG_BASE      + 0x0000c028)
#define HWIO_TCSR_LDO_OSC_CTRL_RMSK                                                                                       0x3
#define HWIO_TCSR_LDO_OSC_CTRL_IN          \
        in_dword_masked(HWIO_TCSR_LDO_OSC_CTRL_ADDR, HWIO_TCSR_LDO_OSC_CTRL_RMSK)
#define HWIO_TCSR_LDO_OSC_CTRL_INM(m)      \
        in_dword_masked(HWIO_TCSR_LDO_OSC_CTRL_ADDR, m)
#define HWIO_TCSR_LDO_OSC_CTRL_OUT(v)      \
        out_dword(HWIO_TCSR_LDO_OSC_CTRL_ADDR,v)
#define HWIO_TCSR_LDO_OSC_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_LDO_OSC_CTRL_ADDR,m,v,HWIO_TCSR_LDO_OSC_CTRL_IN)
#define HWIO_TCSR_LDO_OSC_CTRL_LDO_OSC_CTRL_BMSK                                                                          0x3
#define HWIO_TCSR_LDO_OSC_CTRL_LDO_OSC_CTRL_SHFT                                                                          0x0

#define HWIO_TCSR_LDO_DFT_EN_CTRL_ADDR                                                                             (TCSR_TCSR_REGS_REG_BASE      + 0x0000c02c)
#define HWIO_TCSR_LDO_DFT_EN_CTRL_RMSK                                                                             0x80000000
#define HWIO_TCSR_LDO_DFT_EN_CTRL_IN          \
        in_dword_masked(HWIO_TCSR_LDO_DFT_EN_CTRL_ADDR, HWIO_TCSR_LDO_DFT_EN_CTRL_RMSK)
#define HWIO_TCSR_LDO_DFT_EN_CTRL_INM(m)      \
        in_dword_masked(HWIO_TCSR_LDO_DFT_EN_CTRL_ADDR, m)
#define HWIO_TCSR_LDO_DFT_EN_CTRL_OUT(v)      \
        out_dword(HWIO_TCSR_LDO_DFT_EN_CTRL_ADDR,v)
#define HWIO_TCSR_LDO_DFT_EN_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_LDO_DFT_EN_CTRL_ADDR,m,v,HWIO_TCSR_LDO_DFT_EN_CTRL_IN)
#define HWIO_TCSR_LDO_DFT_EN_CTRL_LDO_DFT_EN_BMSK                                                                  0x80000000
#define HWIO_TCSR_LDO_DFT_EN_CTRL_LDO_DFT_EN_SHFT                                                                        0x1f

#define HWIO_TCSR_LDO_DFT_CTRL_ADDR                                                                                (TCSR_TCSR_REGS_REG_BASE      + 0x0000c030)
#define HWIO_TCSR_LDO_DFT_CTRL_RMSK                                                                                       0x7
#define HWIO_TCSR_LDO_DFT_CTRL_IN          \
        in_dword_masked(HWIO_TCSR_LDO_DFT_CTRL_ADDR, HWIO_TCSR_LDO_DFT_CTRL_RMSK)
#define HWIO_TCSR_LDO_DFT_CTRL_INM(m)      \
        in_dword_masked(HWIO_TCSR_LDO_DFT_CTRL_ADDR, m)
#define HWIO_TCSR_LDO_DFT_CTRL_OUT(v)      \
        out_dword(HWIO_TCSR_LDO_DFT_CTRL_ADDR,v)
#define HWIO_TCSR_LDO_DFT_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_LDO_DFT_CTRL_ADDR,m,v,HWIO_TCSR_LDO_DFT_CTRL_IN)
#define HWIO_TCSR_LDO_DFT_CTRL_LDO_DFT_CONFIG_BMSK                                                                        0x7
#define HWIO_TCSR_LDO_DFT_CTRL_LDO_DFT_CONFIG_SHFT                                                                        0x0

#define HWIO_TCSR_COMPILER_VDDLPI_ACC_0_ADDR                                                                       (TCSR_TCSR_REGS_REG_BASE      + 0x0000d000)
#define HWIO_TCSR_COMPILER_VDDLPI_ACC_0_RMSK                                                                       0xffffffff
#define HWIO_TCSR_COMPILER_VDDLPI_ACC_0_IN          \
        in_dword_masked(HWIO_TCSR_COMPILER_VDDLPI_ACC_0_ADDR, HWIO_TCSR_COMPILER_VDDLPI_ACC_0_RMSK)
#define HWIO_TCSR_COMPILER_VDDLPI_ACC_0_INM(m)      \
        in_dword_masked(HWIO_TCSR_COMPILER_VDDLPI_ACC_0_ADDR, m)
#define HWIO_TCSR_COMPILER_VDDLPI_ACC_0_COMPILER_VDDLPI_ACC_0_BMSK                                                 0xffffffff
#define HWIO_TCSR_COMPILER_VDDLPI_ACC_0_COMPILER_VDDLPI_ACC_0_SHFT                                                        0x0

#define HWIO_TCSR_COMPILER_VDDLPI_ACC_1_ADDR                                                                       (TCSR_TCSR_REGS_REG_BASE      + 0x0000d004)
#define HWIO_TCSR_COMPILER_VDDLPI_ACC_1_RMSK                                                                       0xffffffff
#define HWIO_TCSR_COMPILER_VDDLPI_ACC_1_IN          \
        in_dword_masked(HWIO_TCSR_COMPILER_VDDLPI_ACC_1_ADDR, HWIO_TCSR_COMPILER_VDDLPI_ACC_1_RMSK)
#define HWIO_TCSR_COMPILER_VDDLPI_ACC_1_INM(m)      \
        in_dword_masked(HWIO_TCSR_COMPILER_VDDLPI_ACC_1_ADDR, m)
#define HWIO_TCSR_COMPILER_VDDLPI_ACC_1_COMPILER_VDDLPI_ACC_1_BMSK                                                 0xffffffff
#define HWIO_TCSR_COMPILER_VDDLPI_ACC_1_COMPILER_VDDLPI_ACC_1_SHFT                                                        0x0

#define HWIO_TCSR_COMPILER_VDDCX_ACC_0_ADDR                                                                        (TCSR_TCSR_REGS_REG_BASE      + 0x0000d080)
#define HWIO_TCSR_COMPILER_VDDCX_ACC_0_RMSK                                                                        0xffffffff
#define HWIO_TCSR_COMPILER_VDDCX_ACC_0_IN          \
        in_dword_masked(HWIO_TCSR_COMPILER_VDDCX_ACC_0_ADDR, HWIO_TCSR_COMPILER_VDDCX_ACC_0_RMSK)
#define HWIO_TCSR_COMPILER_VDDCX_ACC_0_INM(m)      \
        in_dword_masked(HWIO_TCSR_COMPILER_VDDCX_ACC_0_ADDR, m)
#define HWIO_TCSR_COMPILER_VDDCX_ACC_0_COMPILER_VDDCX_ACC_0_BMSK                                                   0xffffffff
#define HWIO_TCSR_COMPILER_VDDCX_ACC_0_COMPILER_VDDCX_ACC_0_SHFT                                                          0x0

#define HWIO_TCSR_COMPILER_VDDCX_ACC_1_ADDR                                                                        (TCSR_TCSR_REGS_REG_BASE      + 0x0000d084)
#define HWIO_TCSR_COMPILER_VDDCX_ACC_1_RMSK                                                                        0xffffffff
#define HWIO_TCSR_COMPILER_VDDCX_ACC_1_IN          \
        in_dword_masked(HWIO_TCSR_COMPILER_VDDCX_ACC_1_ADDR, HWIO_TCSR_COMPILER_VDDCX_ACC_1_RMSK)
#define HWIO_TCSR_COMPILER_VDDCX_ACC_1_INM(m)      \
        in_dword_masked(HWIO_TCSR_COMPILER_VDDCX_ACC_1_ADDR, m)
#define HWIO_TCSR_COMPILER_VDDCX_ACC_1_COMPILER_VDDCX_ACC_1_BMSK                                                   0xffffffff
#define HWIO_TCSR_COMPILER_VDDCX_ACC_1_COMPILER_VDDCX_ACC_1_SHFT                                                          0x0

#define HWIO_TCSR_COMPILER_VDDGFX_ACC_0_ADDR                                                                       (TCSR_TCSR_REGS_REG_BASE      + 0x0000d100)
#define HWIO_TCSR_COMPILER_VDDGFX_ACC_0_RMSK                                                                       0xffffffff
#define HWIO_TCSR_COMPILER_VDDGFX_ACC_0_IN          \
        in_dword_masked(HWIO_TCSR_COMPILER_VDDGFX_ACC_0_ADDR, HWIO_TCSR_COMPILER_VDDGFX_ACC_0_RMSK)
#define HWIO_TCSR_COMPILER_VDDGFX_ACC_0_INM(m)      \
        in_dword_masked(HWIO_TCSR_COMPILER_VDDGFX_ACC_0_ADDR, m)
#define HWIO_TCSR_COMPILER_VDDGFX_ACC_0_COMPILER_VDDGFX_ACC_0_BMSK                                                 0xffffffff
#define HWIO_TCSR_COMPILER_VDDGFX_ACC_0_COMPILER_VDDGFX_ACC_0_SHFT                                                        0x0

#define HWIO_TCSR_COMPILER_VDDGFX_ACC_1_ADDR                                                                       (TCSR_TCSR_REGS_REG_BASE      + 0x0000d104)
#define HWIO_TCSR_COMPILER_VDDGFX_ACC_1_RMSK                                                                       0xffffffff
#define HWIO_TCSR_COMPILER_VDDGFX_ACC_1_IN          \
        in_dword_masked(HWIO_TCSR_COMPILER_VDDGFX_ACC_1_ADDR, HWIO_TCSR_COMPILER_VDDGFX_ACC_1_RMSK)
#define HWIO_TCSR_COMPILER_VDDGFX_ACC_1_INM(m)      \
        in_dword_masked(HWIO_TCSR_COMPILER_VDDGFX_ACC_1_ADDR, m)
#define HWIO_TCSR_COMPILER_VDDGFX_ACC_1_COMPILER_VDDGFX_ACC_1_BMSK                                                 0xffffffff
#define HWIO_TCSR_COMPILER_VDDGFX_ACC_1_COMPILER_VDDGFX_ACC_1_SHFT                                                        0x0

#define HWIO_TCSR_COMPILER_VDDMSS_ACC_0_ADDR                                                                       (TCSR_TCSR_REGS_REG_BASE      + 0x0000d1c0)
#define HWIO_TCSR_COMPILER_VDDMSS_ACC_0_RMSK                                                                       0xffffffff
#define HWIO_TCSR_COMPILER_VDDMSS_ACC_0_IN          \
        in_dword_masked(HWIO_TCSR_COMPILER_VDDMSS_ACC_0_ADDR, HWIO_TCSR_COMPILER_VDDMSS_ACC_0_RMSK)
#define HWIO_TCSR_COMPILER_VDDMSS_ACC_0_INM(m)      \
        in_dword_masked(HWIO_TCSR_COMPILER_VDDMSS_ACC_0_ADDR, m)
#define HWIO_TCSR_COMPILER_VDDMSS_ACC_0_COMPILER_VDDMSS_ACC_0_BMSK                                                 0xffffffff
#define HWIO_TCSR_COMPILER_VDDMSS_ACC_0_COMPILER_VDDMSS_ACC_0_SHFT                                                        0x0

#define HWIO_TCSR_COMPILER_VDDMSS_ACC_1_ADDR                                                                       (TCSR_TCSR_REGS_REG_BASE      + 0x0000d1c4)
#define HWIO_TCSR_COMPILER_VDDMSS_ACC_1_RMSK                                                                       0xffffffff
#define HWIO_TCSR_COMPILER_VDDMSS_ACC_1_IN          \
        in_dword_masked(HWIO_TCSR_COMPILER_VDDMSS_ACC_1_ADDR, HWIO_TCSR_COMPILER_VDDMSS_ACC_1_RMSK)
#define HWIO_TCSR_COMPILER_VDDMSS_ACC_1_INM(m)      \
        in_dword_masked(HWIO_TCSR_COMPILER_VDDMSS_ACC_1_ADDR, m)
#define HWIO_TCSR_COMPILER_VDDMSS_ACC_1_COMPILER_VDDMSS_ACC_1_BMSK                                                 0xffffffff
#define HWIO_TCSR_COMPILER_VDDMSS_ACC_1_COMPILER_VDDMSS_ACC_1_SHFT                                                        0x0

#define HWIO_TCSR_CUSTOM_ACC_QCRF4221_CUSTOM4P_VDDMSS_ADDR                                                         (TCSR_TCSR_REGS_REG_BASE      + 0x0000d1d0)
#define HWIO_TCSR_CUSTOM_ACC_QCRF4221_CUSTOM4P_VDDMSS_RMSK                                                               0xff
#define HWIO_TCSR_CUSTOM_ACC_QCRF4221_CUSTOM4P_VDDMSS_IN          \
        in_dword_masked(HWIO_TCSR_CUSTOM_ACC_QCRF4221_CUSTOM4P_VDDMSS_ADDR, HWIO_TCSR_CUSTOM_ACC_QCRF4221_CUSTOM4P_VDDMSS_RMSK)
#define HWIO_TCSR_CUSTOM_ACC_QCRF4221_CUSTOM4P_VDDMSS_INM(m)      \
        in_dword_masked(HWIO_TCSR_CUSTOM_ACC_QCRF4221_CUSTOM4P_VDDMSS_ADDR, m)
#define HWIO_TCSR_CUSTOM_ACC_QCRF4221_CUSTOM4P_VDDMSS_CUSTOM_ACC_QCRF4221_CUSTOM4P_VDDMSS_BMSK                           0xff
#define HWIO_TCSR_CUSTOM_ACC_QCRF4221_CUSTOM4P_VDDMSS_CUSTOM_ACC_QCRF4221_CUSTOM4P_VDDMSS_SHFT                            0x0

#define HWIO_TCSR_CUSTOM_ACC_SPARE_VDDMSS_ADDR                                                                     (TCSR_TCSR_REGS_REG_BASE      + 0x0000d1d4)
#define HWIO_TCSR_CUSTOM_ACC_SPARE_VDDMSS_RMSK                                                                           0xff
#define HWIO_TCSR_CUSTOM_ACC_SPARE_VDDMSS_IN          \
        in_dword_masked(HWIO_TCSR_CUSTOM_ACC_SPARE_VDDMSS_ADDR, HWIO_TCSR_CUSTOM_ACC_SPARE_VDDMSS_RMSK)
#define HWIO_TCSR_CUSTOM_ACC_SPARE_VDDMSS_INM(m)      \
        in_dword_masked(HWIO_TCSR_CUSTOM_ACC_SPARE_VDDMSS_ADDR, m)
#define HWIO_TCSR_CUSTOM_ACC_SPARE_VDDMSS_CUSTOM_ACC_SPARE_VDDMSS_BMSK                                                   0xff
#define HWIO_TCSR_CUSTOM_ACC_SPARE_VDDMSS_CUSTOM_ACC_SPARE_VDDMSS_SHFT                                                    0x0

#define HWIO_TCSR_CUSTOM_ACC_Q6_VDDCX_ADDR                                                                         (TCSR_TCSR_REGS_REG_BASE      + 0x0000d1e0)
#define HWIO_TCSR_CUSTOM_ACC_Q6_VDDCX_RMSK                                                                               0xff
#define HWIO_TCSR_CUSTOM_ACC_Q6_VDDCX_IN          \
        in_dword_masked(HWIO_TCSR_CUSTOM_ACC_Q6_VDDCX_ADDR, HWIO_TCSR_CUSTOM_ACC_Q6_VDDCX_RMSK)
#define HWIO_TCSR_CUSTOM_ACC_Q6_VDDCX_INM(m)      \
        in_dword_masked(HWIO_TCSR_CUSTOM_ACC_Q6_VDDCX_ADDR, m)
#define HWIO_TCSR_CUSTOM_ACC_Q6_VDDCX_CUSTOM_ACC_Q6_VDDCX_BMSK                                                           0xff
#define HWIO_TCSR_CUSTOM_ACC_Q6_VDDCX_CUSTOM_ACC_Q6_VDDCX_SHFT                                                            0x0

#define HWIO_TCSR_CUSTOM_ACC_SPARE_VDDCX_ADDR                                                                      (TCSR_TCSR_REGS_REG_BASE      + 0x0000d1e4)
#define HWIO_TCSR_CUSTOM_ACC_SPARE_VDDCX_RMSK                                                                            0xff
#define HWIO_TCSR_CUSTOM_ACC_SPARE_VDDCX_IN          \
        in_dword_masked(HWIO_TCSR_CUSTOM_ACC_SPARE_VDDCX_ADDR, HWIO_TCSR_CUSTOM_ACC_SPARE_VDDCX_RMSK)
#define HWIO_TCSR_CUSTOM_ACC_SPARE_VDDCX_INM(m)      \
        in_dword_masked(HWIO_TCSR_CUSTOM_ACC_SPARE_VDDCX_ADDR, m)
#define HWIO_TCSR_CUSTOM_ACC_SPARE_VDDCX_CUSTOM_ACC_SPARE_VDDCX_BMSK                                                     0xff
#define HWIO_TCSR_CUSTOM_ACC_SPARE_VDDCX_CUSTOM_ACC_SPARE_VDDCX_SHFT                                                      0x0

#define HWIO_TCSR_CUSTOM_ACC_QCRF3211_CUSTOM3P_VDDGFX_ADDR                                                         (TCSR_TCSR_REGS_REG_BASE      + 0x0000d110)
#define HWIO_TCSR_CUSTOM_ACC_QCRF3211_CUSTOM3P_VDDGFX_RMSK                                                               0xff
#define HWIO_TCSR_CUSTOM_ACC_QCRF3211_CUSTOM3P_VDDGFX_IN          \
        in_dword_masked(HWIO_TCSR_CUSTOM_ACC_QCRF3211_CUSTOM3P_VDDGFX_ADDR, HWIO_TCSR_CUSTOM_ACC_QCRF3211_CUSTOM3P_VDDGFX_RMSK)
#define HWIO_TCSR_CUSTOM_ACC_QCRF3211_CUSTOM3P_VDDGFX_INM(m)      \
        in_dword_masked(HWIO_TCSR_CUSTOM_ACC_QCRF3211_CUSTOM3P_VDDGFX_ADDR, m)
#define HWIO_TCSR_CUSTOM_ACC_QCRF3211_CUSTOM3P_VDDGFX_CUSTOM_ACC_QCRF3211_CUSTOM3P_VDDGFX_BMSK                           0xff
#define HWIO_TCSR_CUSTOM_ACC_QCRF3211_CUSTOM3P_VDDGFX_CUSTOM_ACC_QCRF3211_CUSTOM3P_VDDGFX_SHFT                            0x0

#define HWIO_TCSR_CUSTOM_ACC_SPARE_VDDGFX_ADDR                                                                     (TCSR_TCSR_REGS_REG_BASE      + 0x0000d114)
#define HWIO_TCSR_CUSTOM_ACC_SPARE_VDDGFX_RMSK                                                                           0xff
#define HWIO_TCSR_CUSTOM_ACC_SPARE_VDDGFX_IN          \
        in_dword_masked(HWIO_TCSR_CUSTOM_ACC_SPARE_VDDGFX_ADDR, HWIO_TCSR_CUSTOM_ACC_SPARE_VDDGFX_RMSK)
#define HWIO_TCSR_CUSTOM_ACC_SPARE_VDDGFX_INM(m)      \
        in_dword_masked(HWIO_TCSR_CUSTOM_ACC_SPARE_VDDGFX_ADDR, m)
#define HWIO_TCSR_CUSTOM_ACC_SPARE_VDDGFX_CUSTOM_ACC_SPARE_VDDGFX_BMSK                                                   0xff
#define HWIO_TCSR_CUSTOM_ACC_SPARE_VDDGFX_CUSTOM_ACC_SPARE_VDDGFX_SHFT                                                    0x0

#define HWIO_TCSR_CUSTOM_ACC_QCSRAM1111_BOLTMEM_VDDMSS_ADDR                                                        (TCSR_TCSR_REGS_REG_BASE      + 0x0000d1e8)
#define HWIO_TCSR_CUSTOM_ACC_QCSRAM1111_BOLTMEM_VDDMSS_RMSK                                                              0xff
#define HWIO_TCSR_CUSTOM_ACC_QCSRAM1111_BOLTMEM_VDDMSS_IN          \
        in_dword_masked(HWIO_TCSR_CUSTOM_ACC_QCSRAM1111_BOLTMEM_VDDMSS_ADDR, HWIO_TCSR_CUSTOM_ACC_QCSRAM1111_BOLTMEM_VDDMSS_RMSK)
#define HWIO_TCSR_CUSTOM_ACC_QCSRAM1111_BOLTMEM_VDDMSS_INM(m)      \
        in_dword_masked(HWIO_TCSR_CUSTOM_ACC_QCSRAM1111_BOLTMEM_VDDMSS_ADDR, m)
#define HWIO_TCSR_CUSTOM_ACC_QCSRAM1111_BOLTMEM_VDDMSS_CUSTOM_ACC_QCSRAM1111_BOLTMEM_VDDMSS_BMSK                         0xff
#define HWIO_TCSR_CUSTOM_ACC_QCSRAM1111_BOLTMEM_VDDMSS_CUSTOM_ACC_QCSRAM1111_BOLTMEM_VDDMSS_SHFT                          0x0

#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE5_ADDR                                                                (TCSR_TCSR_REGS_REG_BASE      + 0x0000d1ec)
#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE5_RMSK                                                                      0xff
#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE5_IN          \
        in_dword_masked(HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE5_ADDR, HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE5_RMSK)
#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE5_INM(m)      \
        in_dword_masked(HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE5_ADDR, m)
#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE5_CUSTOM_ACC_KRYOBSILVER_TYPE5_BMSK                                         0xff
#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE5_CUSTOM_ACC_KRYOBSILVER_TYPE5_SHFT                                          0x0

#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE6_ADDR                                                                (TCSR_TCSR_REGS_REG_BASE      + 0x0000d1f0)
#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE6_RMSK                                                                      0xff
#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE6_IN          \
        in_dword_masked(HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE6_ADDR, HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE6_RMSK)
#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE6_INM(m)      \
        in_dword_masked(HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE6_ADDR, m)
#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE6_CUSTOM_ACC_KRYOBSILVER_TYPE6_BMSK                                         0xff
#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE6_CUSTOM_ACC_KRYOBSILVER_TYPE6_SHFT                                          0x0

#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE7_ADDR                                                                (TCSR_TCSR_REGS_REG_BASE      + 0x0000d1f4)
#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE7_RMSK                                                                      0xff
#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE7_IN          \
        in_dword_masked(HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE7_ADDR, HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE7_RMSK)
#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE7_INM(m)      \
        in_dword_masked(HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE7_ADDR, m)
#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE7_CUSTOM_ACC_KRYOBSILVER_TYPE7_BMSK                                         0xff
#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE7_CUSTOM_ACC_KRYOBSILVER_TYPE7_SHFT                                          0x0

#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE8_ADDR                                                                (TCSR_TCSR_REGS_REG_BASE      + 0x0000d1f8)
#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE8_RMSK                                                                      0xff
#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE8_IN          \
        in_dword_masked(HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE8_ADDR, HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE8_RMSK)
#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE8_INM(m)      \
        in_dword_masked(HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE8_ADDR, m)
#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE8_CUSTOM_ACC_KRYOBSILVER_TYPE8_BMSK                                         0xff
#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE8_CUSTOM_ACC_KRYOBSILVER_TYPE8_SHFT                                          0x0

#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE9_ADDR                                                                (TCSR_TCSR_REGS_REG_BASE      + 0x0000d1fc)
#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE9_RMSK                                                                      0xff
#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE9_IN          \
        in_dword_masked(HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE9_ADDR, HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE9_RMSK)
#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE9_INM(m)      \
        in_dword_masked(HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE9_ADDR, m)
#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE9_CUSTOM_ACC_KRYOBSILVER_TYPE9_BMSK                                         0xff
#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE9_CUSTOM_ACC_KRYOBSILVER_TYPE9_SHFT                                          0x0

#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE10_ADDR                                                               (TCSR_TCSR_REGS_REG_BASE      + 0x0000d200)
#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE10_RMSK                                                                     0xff
#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE10_IN          \
        in_dword_masked(HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE10_ADDR, HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE10_RMSK)
#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE10_INM(m)      \
        in_dword_masked(HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE10_ADDR, m)
#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE10_CUSTOM_ACC_KRYOBSILVER_TYPE10_BMSK                                       0xff
#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE10_CUSTOM_ACC_KRYOBSILVER_TYPE10_SHFT                                        0x0

#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE11_ADDR                                                               (TCSR_TCSR_REGS_REG_BASE      + 0x0000d204)
#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE11_RMSK                                                                     0xff
#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE11_IN          \
        in_dword_masked(HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE11_ADDR, HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE11_RMSK)
#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE11_INM(m)      \
        in_dword_masked(HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE11_ADDR, m)
#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE11_CUSTOM_ACC_KRYOBSILVER_TYPE11_BMSK                                       0xff
#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE11_CUSTOM_ACC_KRYOBSILVER_TYPE11_SHFT                                        0x0

#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE12_ADDR                                                               (TCSR_TCSR_REGS_REG_BASE      + 0x0000d208)
#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE12_RMSK                                                                     0xff
#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE12_IN          \
        in_dword_masked(HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE12_ADDR, HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE12_RMSK)
#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE12_INM(m)      \
        in_dword_masked(HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE12_ADDR, m)
#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE12_CUSTOM_ACC_KRYOBSILVER_TYPE12_BMSK                                       0xff
#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE12_CUSTOM_ACC_KRYOBSILVER_TYPE12_SHFT                                        0x0

#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE13_ADDR                                                               (TCSR_TCSR_REGS_REG_BASE      + 0x0000d20c)
#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE13_RMSK                                                                     0xff
#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE13_IN          \
        in_dword_masked(HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE13_ADDR, HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE13_RMSK)
#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE13_INM(m)      \
        in_dword_masked(HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE13_ADDR, m)
#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE13_CUSTOM_ACC_KRYOBSILVER_TYPE13_BMSK                                       0xff
#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE13_CUSTOM_ACC_KRYOBSILVER_TYPE13_SHFT                                        0x0

#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE14_ADDR                                                               (TCSR_TCSR_REGS_REG_BASE      + 0x0000d210)
#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE14_RMSK                                                                     0xff
#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE14_IN          \
        in_dword_masked(HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE14_ADDR, HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE14_RMSK)
#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE14_INM(m)      \
        in_dword_masked(HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE14_ADDR, m)
#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE14_CUSTOM_ACC_KRYOBSILVER_TYPE14_BMSK                                       0xff
#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE14_CUSTOM_ACC_KRYOBSILVER_TYPE14_SHFT                                        0x0

#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE15_ADDR                                                               (TCSR_TCSR_REGS_REG_BASE      + 0x0000d214)
#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE15_RMSK                                                                     0xff
#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE15_IN          \
        in_dword_masked(HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE15_ADDR, HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE15_RMSK)
#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE15_INM(m)      \
        in_dword_masked(HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE15_ADDR, m)
#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE15_CUSTOM_ACC_KRYOBSILVER_TYPE15_BMSK                                       0xff
#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE15_CUSTOM_ACC_KRYOBSILVER_TYPE15_SHFT                                        0x0

#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE16_ADDR                                                               (TCSR_TCSR_REGS_REG_BASE      + 0x0000d218)
#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE16_RMSK                                                                     0xff
#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE16_IN          \
        in_dword_masked(HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE16_ADDR, HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE16_RMSK)
#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE16_INM(m)      \
        in_dword_masked(HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE16_ADDR, m)
#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE16_CUSTOM_ACC_KRYOBSILVER_TYPE16_BMSK                                       0xff
#define HWIO_TCSR_CUSTOM_ACC_KRYOBSILVER_TYPE16_CUSTOM_ACC_KRYOBSILVER_TYPE16_SHFT                                        0x0

#define HWIO_TCSR_CUSTOM_ACC_2PRF_2S_VDDMSS_ADDR                                                                   (TCSR_TCSR_REGS_REG_BASE      + 0x0000d21c)
#define HWIO_TCSR_CUSTOM_ACC_2PRF_2S_VDDMSS_RMSK                                                                         0xff
#define HWIO_TCSR_CUSTOM_ACC_2PRF_2S_VDDMSS_IN          \
        in_dword_masked(HWIO_TCSR_CUSTOM_ACC_2PRF_2S_VDDMSS_ADDR, HWIO_TCSR_CUSTOM_ACC_2PRF_2S_VDDMSS_RMSK)
#define HWIO_TCSR_CUSTOM_ACC_2PRF_2S_VDDMSS_INM(m)      \
        in_dword_masked(HWIO_TCSR_CUSTOM_ACC_2PRF_2S_VDDMSS_ADDR, m)
#define HWIO_TCSR_CUSTOM_ACC_2PRF_2S_VDDMSS_CUSTOM_ACC_2PRF_2S_VDDMSS_BMSK                                               0xff
#define HWIO_TCSR_CUSTOM_ACC_2PRF_2S_VDDMSS_CUSTOM_ACC_2PRF_2S_VDDMSS_SHFT                                                0x0

#define HWIO_TCSR_MEM_ARRY_STBY_ADDR                                                                               (TCSR_TCSR_REGS_REG_BASE      + 0x0000d180)
#define HWIO_TCSR_MEM_ARRY_STBY_RMSK                                                                                      0x1
#define HWIO_TCSR_MEM_ARRY_STBY_IN          \
        in_dword_masked(HWIO_TCSR_MEM_ARRY_STBY_ADDR, HWIO_TCSR_MEM_ARRY_STBY_RMSK)
#define HWIO_TCSR_MEM_ARRY_STBY_INM(m)      \
        in_dword_masked(HWIO_TCSR_MEM_ARRY_STBY_ADDR, m)
#define HWIO_TCSR_MEM_ARRY_STBY_OUT(v)      \
        out_dword(HWIO_TCSR_MEM_ARRY_STBY_ADDR,v)
#define HWIO_TCSR_MEM_ARRY_STBY_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_MEM_ARRY_STBY_ADDR,m,v,HWIO_TCSR_MEM_ARRY_STBY_IN)
#define HWIO_TCSR_MEM_ARRY_STBY_MEM_ARRY_STBY_N_BMSK                                                                      0x1
#define HWIO_TCSR_MEM_ARRY_STBY_MEM_ARRY_STBY_N_SHFT                                                                      0x0

#define HWIO_TCSR_MEM_SVS_SEL_VDDCX_ADDR                                                                           (TCSR_TCSR_REGS_REG_BASE      + 0x0000e004)
#define HWIO_TCSR_MEM_SVS_SEL_VDDCX_RMSK                                                                                  0x1
#define HWIO_TCSR_MEM_SVS_SEL_VDDCX_IN          \
        in_dword_masked(HWIO_TCSR_MEM_SVS_SEL_VDDCX_ADDR, HWIO_TCSR_MEM_SVS_SEL_VDDCX_RMSK)
#define HWIO_TCSR_MEM_SVS_SEL_VDDCX_INM(m)      \
        in_dword_masked(HWIO_TCSR_MEM_SVS_SEL_VDDCX_ADDR, m)
#define HWIO_TCSR_MEM_SVS_SEL_VDDCX_OUT(v)      \
        out_dword(HWIO_TCSR_MEM_SVS_SEL_VDDCX_ADDR,v)
#define HWIO_TCSR_MEM_SVS_SEL_VDDCX_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_MEM_SVS_SEL_VDDCX_ADDR,m,v,HWIO_TCSR_MEM_SVS_SEL_VDDCX_IN)
#define HWIO_TCSR_MEM_SVS_SEL_VDDCX_MEM_SVS_SEL_VDDCX_BMSK                                                                0x1
#define HWIO_TCSR_MEM_SVS_SEL_VDDCX_MEM_SVS_SEL_VDDCX_SHFT                                                                0x0

#define HWIO_TCSR_WCSS_MEM_SVS_SEL_VDDCX_ADDR                                                                      (TCSR_TCSR_REGS_REG_BASE      + 0x0000e008)
#define HWIO_TCSR_WCSS_MEM_SVS_SEL_VDDCX_RMSK                                                                             0x1
#define HWIO_TCSR_WCSS_MEM_SVS_SEL_VDDCX_IN          \
        in_dword_masked(HWIO_TCSR_WCSS_MEM_SVS_SEL_VDDCX_ADDR, HWIO_TCSR_WCSS_MEM_SVS_SEL_VDDCX_RMSK)
#define HWIO_TCSR_WCSS_MEM_SVS_SEL_VDDCX_INM(m)      \
        in_dword_masked(HWIO_TCSR_WCSS_MEM_SVS_SEL_VDDCX_ADDR, m)
#define HWIO_TCSR_WCSS_MEM_SVS_SEL_VDDCX_OUT(v)      \
        out_dword(HWIO_TCSR_WCSS_MEM_SVS_SEL_VDDCX_ADDR,v)
#define HWIO_TCSR_WCSS_MEM_SVS_SEL_VDDCX_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_WCSS_MEM_SVS_SEL_VDDCX_ADDR,m,v,HWIO_TCSR_WCSS_MEM_SVS_SEL_VDDCX_IN)
#define HWIO_TCSR_WCSS_MEM_SVS_SEL_VDDCX_WCSS_MEM_SVS_SEL_VDDCX_BMSK                                                      0x1
#define HWIO_TCSR_WCSS_MEM_SVS_SEL_VDDCX_WCSS_MEM_SVS_SEL_VDDCX_SHFT                                                      0x0

#define HWIO_TCSR_MEM_SVS_SEL_VDDGFX_ADDR                                                                          (TCSR_TCSR_REGS_REG_BASE      + 0x0000f004)
#define HWIO_TCSR_MEM_SVS_SEL_VDDGFX_RMSK                                                                                 0x1
#define HWIO_TCSR_MEM_SVS_SEL_VDDGFX_IN          \
        in_dword_masked(HWIO_TCSR_MEM_SVS_SEL_VDDGFX_ADDR, HWIO_TCSR_MEM_SVS_SEL_VDDGFX_RMSK)
#define HWIO_TCSR_MEM_SVS_SEL_VDDGFX_INM(m)      \
        in_dword_masked(HWIO_TCSR_MEM_SVS_SEL_VDDGFX_ADDR, m)
#define HWIO_TCSR_MEM_SVS_SEL_VDDGFX_OUT(v)      \
        out_dword(HWIO_TCSR_MEM_SVS_SEL_VDDGFX_ADDR,v)
#define HWIO_TCSR_MEM_SVS_SEL_VDDGFX_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_MEM_SVS_SEL_VDDGFX_ADDR,m,v,HWIO_TCSR_MEM_SVS_SEL_VDDGFX_IN)
#define HWIO_TCSR_MEM_SVS_SEL_VDDGFX_MEM_SVS_SEL_VDDGFX_BMSK                                                              0x1
#define HWIO_TCSR_MEM_SVS_SEL_VDDGFX_MEM_SVS_SEL_VDDGFX_SHFT                                                              0x0

#define HWIO_TCSR_MEM_SVS_SEL_VDDLPI_ADDR                                                                          (TCSR_TCSR_REGS_REG_BASE      + 0x00010000)
#define HWIO_TCSR_MEM_SVS_SEL_VDDLPI_RMSK                                                                                 0x1
#define HWIO_TCSR_MEM_SVS_SEL_VDDLPI_IN          \
        in_dword_masked(HWIO_TCSR_MEM_SVS_SEL_VDDLPI_ADDR, HWIO_TCSR_MEM_SVS_SEL_VDDLPI_RMSK)
#define HWIO_TCSR_MEM_SVS_SEL_VDDLPI_INM(m)      \
        in_dword_masked(HWIO_TCSR_MEM_SVS_SEL_VDDLPI_ADDR, m)
#define HWIO_TCSR_MEM_SVS_SEL_VDDLPI_OUT(v)      \
        out_dword(HWIO_TCSR_MEM_SVS_SEL_VDDLPI_ADDR,v)
#define HWIO_TCSR_MEM_SVS_SEL_VDDLPI_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_MEM_SVS_SEL_VDDLPI_ADDR,m,v,HWIO_TCSR_MEM_SVS_SEL_VDDLPI_IN)
#define HWIO_TCSR_MEM_SVS_SEL_VDDLPI_MEM_SVS_SEL_VDDLPI_BMSK                                                              0x1
#define HWIO_TCSR_MEM_SVS_SEL_VDDLPI_MEM_SVS_SEL_VDDLPI_SHFT                                                              0x0

#define HWIO_TCSR_DDR_SS_DEBUG_BUS_SEL_ADDR                                                                        (TCSR_TCSR_REGS_REG_BASE      + 0x0000b220)
#define HWIO_TCSR_DDR_SS_DEBUG_BUS_SEL_RMSK                                                                             0x3ff
#define HWIO_TCSR_DDR_SS_DEBUG_BUS_SEL_IN          \
        in_dword_masked(HWIO_TCSR_DDR_SS_DEBUG_BUS_SEL_ADDR, HWIO_TCSR_DDR_SS_DEBUG_BUS_SEL_RMSK)
#define HWIO_TCSR_DDR_SS_DEBUG_BUS_SEL_INM(m)      \
        in_dword_masked(HWIO_TCSR_DDR_SS_DEBUG_BUS_SEL_ADDR, m)
#define HWIO_TCSR_DDR_SS_DEBUG_BUS_SEL_OUT(v)      \
        out_dword(HWIO_TCSR_DDR_SS_DEBUG_BUS_SEL_ADDR,v)
#define HWIO_TCSR_DDR_SS_DEBUG_BUS_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_DDR_SS_DEBUG_BUS_SEL_ADDR,m,v,HWIO_TCSR_DDR_SS_DEBUG_BUS_SEL_IN)
#define HWIO_TCSR_DDR_SS_DEBUG_BUS_SEL_DDR_SS_DEBUG_BUS_SEL_BMSK                                                        0x3ff
#define HWIO_TCSR_DDR_SS_DEBUG_BUS_SEL_DDR_SS_DEBUG_BUS_SEL_SHFT                                                          0x0

#define HWIO_TCSR_VSENSE_CONTROLLER_ENABLE_REGISTER_ADDR                                                           (TCSR_TCSR_REGS_REG_BASE      + 0x00011000)
#define HWIO_TCSR_VSENSE_CONTROLLER_ENABLE_REGISTER_RMSK                                                                  0x1
#define HWIO_TCSR_VSENSE_CONTROLLER_ENABLE_REGISTER_IN          \
        in_dword_masked(HWIO_TCSR_VSENSE_CONTROLLER_ENABLE_REGISTER_ADDR, HWIO_TCSR_VSENSE_CONTROLLER_ENABLE_REGISTER_RMSK)
#define HWIO_TCSR_VSENSE_CONTROLLER_ENABLE_REGISTER_INM(m)      \
        in_dword_masked(HWIO_TCSR_VSENSE_CONTROLLER_ENABLE_REGISTER_ADDR, m)
#define HWIO_TCSR_VSENSE_CONTROLLER_ENABLE_REGISTER_OUT(v)      \
        out_dword(HWIO_TCSR_VSENSE_CONTROLLER_ENABLE_REGISTER_ADDR,v)
#define HWIO_TCSR_VSENSE_CONTROLLER_ENABLE_REGISTER_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_VSENSE_CONTROLLER_ENABLE_REGISTER_ADDR,m,v,HWIO_TCSR_VSENSE_CONTROLLER_ENABLE_REGISTER_IN)
#define HWIO_TCSR_VSENSE_CONTROLLER_ENABLE_REGISTER_VSENSE_CONTROLLER_ENABLE_REGISTER_BMSK                                0x1
#define HWIO_TCSR_VSENSE_CONTROLLER_ENABLE_REGISTER_VSENSE_CONTROLLER_ENABLE_REGISTER_SHFT                                0x0

#define HWIO_TCSR_TCSR_RESET_DEBUG_SW_ENTRY_ADDR                                                                   (TCSR_TCSR_REGS_REG_BASE      + 0x00012000)
#define HWIO_TCSR_TCSR_RESET_DEBUG_SW_ENTRY_RMSK                                                                   0xffffffff
#define HWIO_TCSR_TCSR_RESET_DEBUG_SW_ENTRY_IN          \
        in_dword_masked(HWIO_TCSR_TCSR_RESET_DEBUG_SW_ENTRY_ADDR, HWIO_TCSR_TCSR_RESET_DEBUG_SW_ENTRY_RMSK)
#define HWIO_TCSR_TCSR_RESET_DEBUG_SW_ENTRY_INM(m)      \
        in_dword_masked(HWIO_TCSR_TCSR_RESET_DEBUG_SW_ENTRY_ADDR, m)
#define HWIO_TCSR_TCSR_RESET_DEBUG_SW_ENTRY_OUT(v)      \
        out_dword(HWIO_TCSR_TCSR_RESET_DEBUG_SW_ENTRY_ADDR,v)
#define HWIO_TCSR_TCSR_RESET_DEBUG_SW_ENTRY_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_TCSR_RESET_DEBUG_SW_ENTRY_ADDR,m,v,HWIO_TCSR_TCSR_RESET_DEBUG_SW_ENTRY_IN)
#define HWIO_TCSR_TCSR_RESET_DEBUG_SW_ENTRY_TCSR_RESET_DEBUG_SW_ENTRY_BMSK                                         0xffffffff
#define HWIO_TCSR_TCSR_RESET_DEBUG_SW_ENTRY_TCSR_RESET_DEBUG_SW_ENTRY_SHFT                                                0x0

#define HWIO_TCSR_TCSR_BOOT_MISC_DETECT_ADDR                                                                       (TCSR_TCSR_REGS_REG_BASE      + 0x00013000)
#define HWIO_TCSR_TCSR_BOOT_MISC_DETECT_RMSK                                                                       0xffffffff
#define HWIO_TCSR_TCSR_BOOT_MISC_DETECT_IN          \
        in_dword_masked(HWIO_TCSR_TCSR_BOOT_MISC_DETECT_ADDR, HWIO_TCSR_TCSR_BOOT_MISC_DETECT_RMSK)
#define HWIO_TCSR_TCSR_BOOT_MISC_DETECT_INM(m)      \
        in_dword_masked(HWIO_TCSR_TCSR_BOOT_MISC_DETECT_ADDR, m)
#define HWIO_TCSR_TCSR_BOOT_MISC_DETECT_OUT(v)      \
        out_dword(HWIO_TCSR_TCSR_BOOT_MISC_DETECT_ADDR,v)
#define HWIO_TCSR_TCSR_BOOT_MISC_DETECT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_TCSR_BOOT_MISC_DETECT_ADDR,m,v,HWIO_TCSR_TCSR_BOOT_MISC_DETECT_IN)
#define HWIO_TCSR_TCSR_BOOT_MISC_DETECT_TCSR_BOOT_MISC_DETECT_BMSK                                                 0xffffffff
#define HWIO_TCSR_TCSR_BOOT_MISC_DETECT_TCSR_BOOT_MISC_DETECT_SHFT                                                        0x0

#define HWIO_TCSR_TZ_WONCE_n_ADDR(n)                                                                               (TCSR_TCSR_REGS_REG_BASE      + 0x00014000 + 0x4 * (n))
#define HWIO_TCSR_TZ_WONCE_n_RMSK                                                                                  0xffffffff
#define HWIO_TCSR_TZ_WONCE_n_MAXn                                                                                          15
#define HWIO_TCSR_TZ_WONCE_n_INI(n)        \
        in_dword_masked(HWIO_TCSR_TZ_WONCE_n_ADDR(n), HWIO_TCSR_TZ_WONCE_n_RMSK)
#define HWIO_TCSR_TZ_WONCE_n_INMI(n,mask)    \
        in_dword_masked(HWIO_TCSR_TZ_WONCE_n_ADDR(n), mask)
#define HWIO_TCSR_TZ_WONCE_n_OUTI(n,val)    \
        out_dword(HWIO_TCSR_TZ_WONCE_n_ADDR(n),val)
#define HWIO_TCSR_TZ_WONCE_n_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TCSR_TZ_WONCE_n_ADDR(n),mask,val,HWIO_TCSR_TZ_WONCE_n_INI(n))
#define HWIO_TCSR_TZ_WONCE_n_TZ_WONCE_ADDRESS_BMSK                                                                 0xffffffff
#define HWIO_TCSR_TZ_WONCE_n_TZ_WONCE_ADDRESS_SHFT                                                                        0x0

#define HWIO_TCSR_QREFS_RPT_CONFIG_ADDR                                                                            (TCSR_TCSR_REGS_REG_BASE      + 0x00015000)
#define HWIO_TCSR_QREFS_RPT_CONFIG_RMSK                                                                                0xffff
#define HWIO_TCSR_QREFS_RPT_CONFIG_IN          \
        in_dword_masked(HWIO_TCSR_QREFS_RPT_CONFIG_ADDR, HWIO_TCSR_QREFS_RPT_CONFIG_RMSK)
#define HWIO_TCSR_QREFS_RPT_CONFIG_INM(m)      \
        in_dword_masked(HWIO_TCSR_QREFS_RPT_CONFIG_ADDR, m)
#define HWIO_TCSR_QREFS_RPT_CONFIG_OUT(v)      \
        out_dword(HWIO_TCSR_QREFS_RPT_CONFIG_ADDR,v)
#define HWIO_TCSR_QREFS_RPT_CONFIG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_QREFS_RPT_CONFIG_ADDR,m,v,HWIO_TCSR_QREFS_RPT_CONFIG_IN)
#define HWIO_TCSR_QREFS_RPT_CONFIG_QREFS_RPT_CONFIG_BUS_SELECT_BMSK                                                    0xffff
#define HWIO_TCSR_QREFS_RPT_CONFIG_QREFS_RPT_CONFIG_BUS_SELECT_SHFT                                                       0x0

#define HWIO_TCSR_QREFS_TXVBG_CONFIG_ADDR                                                                          (TCSR_TCSR_REGS_REG_BASE      + 0x00015004)
#define HWIO_TCSR_QREFS_TXVBG_CONFIG_RMSK                                                                              0xffff
#define HWIO_TCSR_QREFS_TXVBG_CONFIG_IN          \
        in_dword_masked(HWIO_TCSR_QREFS_TXVBG_CONFIG_ADDR, HWIO_TCSR_QREFS_TXVBG_CONFIG_RMSK)
#define HWIO_TCSR_QREFS_TXVBG_CONFIG_INM(m)      \
        in_dword_masked(HWIO_TCSR_QREFS_TXVBG_CONFIG_ADDR, m)
#define HWIO_TCSR_QREFS_TXVBG_CONFIG_OUT(v)      \
        out_dword(HWIO_TCSR_QREFS_TXVBG_CONFIG_ADDR,v)
#define HWIO_TCSR_QREFS_TXVBG_CONFIG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_QREFS_TXVBG_CONFIG_ADDR,m,v,HWIO_TCSR_QREFS_TXVBG_CONFIG_IN)
#define HWIO_TCSR_QREFS_TXVBG_CONFIG_QREFS_TXVBG_CONFIG_BMSK                                                           0xffff
#define HWIO_TCSR_QREFS_TXVBG_CONFIG_QREFS_TXVBG_CONFIG_SHFT                                                              0x0

#define HWIO_TCSR_QREFS_CXO_RX3_CONFIG_ADDR                                                                        (TCSR_TCSR_REGS_REG_BASE      + 0x00015008)
#define HWIO_TCSR_QREFS_CXO_RX3_CONFIG_RMSK                                                                              0xff
#define HWIO_TCSR_QREFS_CXO_RX3_CONFIG_IN          \
        in_dword_masked(HWIO_TCSR_QREFS_CXO_RX3_CONFIG_ADDR, HWIO_TCSR_QREFS_CXO_RX3_CONFIG_RMSK)
#define HWIO_TCSR_QREFS_CXO_RX3_CONFIG_INM(m)      \
        in_dword_masked(HWIO_TCSR_QREFS_CXO_RX3_CONFIG_ADDR, m)
#define HWIO_TCSR_QREFS_CXO_RX3_CONFIG_OUT(v)      \
        out_dword(HWIO_TCSR_QREFS_CXO_RX3_CONFIG_ADDR,v)
#define HWIO_TCSR_QREFS_CXO_RX3_CONFIG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_QREFS_CXO_RX3_CONFIG_ADDR,m,v,HWIO_TCSR_QREFS_CXO_RX3_CONFIG_IN)
#define HWIO_TCSR_QREFS_CXO_RX3_CONFIG_QREFS_CXO_RX3_CONFIG_BMSK                                                         0xff
#define HWIO_TCSR_QREFS_CXO_RX3_CONFIG_QREFS_CXO_RX3_CONFIG_SHFT                                                          0x0

#define HWIO_TCSR_QREFS_CXO_RX2_CONFIG_ADDR                                                                        (TCSR_TCSR_REGS_REG_BASE      + 0x0001500c)
#define HWIO_TCSR_QREFS_CXO_RX2_CONFIG_RMSK                                                                              0xff
#define HWIO_TCSR_QREFS_CXO_RX2_CONFIG_IN          \
        in_dword_masked(HWIO_TCSR_QREFS_CXO_RX2_CONFIG_ADDR, HWIO_TCSR_QREFS_CXO_RX2_CONFIG_RMSK)
#define HWIO_TCSR_QREFS_CXO_RX2_CONFIG_INM(m)      \
        in_dword_masked(HWIO_TCSR_QREFS_CXO_RX2_CONFIG_ADDR, m)
#define HWIO_TCSR_QREFS_CXO_RX2_CONFIG_OUT(v)      \
        out_dword(HWIO_TCSR_QREFS_CXO_RX2_CONFIG_ADDR,v)
#define HWIO_TCSR_QREFS_CXO_RX2_CONFIG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_QREFS_CXO_RX2_CONFIG_ADDR,m,v,HWIO_TCSR_QREFS_CXO_RX2_CONFIG_IN)
#define HWIO_TCSR_QREFS_CXO_RX2_CONFIG_QREFS_CXO_RX2_CONFIG_BMSK                                                         0xff
#define HWIO_TCSR_QREFS_CXO_RX2_CONFIG_QREFS_CXO_RX2_CONFIG_SHFT                                                          0x0

#define HWIO_TCSR_QREFS_CXO_RPT2_CONFIG_ADDR                                                                       (TCSR_TCSR_REGS_REG_BASE      + 0x00015010)
#define HWIO_TCSR_QREFS_CXO_RPT2_CONFIG_RMSK                                                                             0xff
#define HWIO_TCSR_QREFS_CXO_RPT2_CONFIG_IN          \
        in_dword_masked(HWIO_TCSR_QREFS_CXO_RPT2_CONFIG_ADDR, HWIO_TCSR_QREFS_CXO_RPT2_CONFIG_RMSK)
#define HWIO_TCSR_QREFS_CXO_RPT2_CONFIG_INM(m)      \
        in_dword_masked(HWIO_TCSR_QREFS_CXO_RPT2_CONFIG_ADDR, m)
#define HWIO_TCSR_QREFS_CXO_RPT2_CONFIG_OUT(v)      \
        out_dword(HWIO_TCSR_QREFS_CXO_RPT2_CONFIG_ADDR,v)
#define HWIO_TCSR_QREFS_CXO_RPT2_CONFIG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_QREFS_CXO_RPT2_CONFIG_ADDR,m,v,HWIO_TCSR_QREFS_CXO_RPT2_CONFIG_IN)
#define HWIO_TCSR_QREFS_CXO_RPT2_CONFIG_QREFS_CXO_RPT2_CONFIG_BMSK                                                       0xff
#define HWIO_TCSR_QREFS_CXO_RPT2_CONFIG_QREFS_CXO_RPT2_CONFIG_SHFT                                                        0x0

#define HWIO_TCSR_QREFS_CXO_TXVBG1_CONFIG_ADDR                                                                     (TCSR_TCSR_REGS_REG_BASE      + 0x00015014)
#define HWIO_TCSR_QREFS_CXO_TXVBG1_CONFIG_RMSK                                                                         0xffff
#define HWIO_TCSR_QREFS_CXO_TXVBG1_CONFIG_IN          \
        in_dword_masked(HWIO_TCSR_QREFS_CXO_TXVBG1_CONFIG_ADDR, HWIO_TCSR_QREFS_CXO_TXVBG1_CONFIG_RMSK)
#define HWIO_TCSR_QREFS_CXO_TXVBG1_CONFIG_INM(m)      \
        in_dword_masked(HWIO_TCSR_QREFS_CXO_TXVBG1_CONFIG_ADDR, m)
#define HWIO_TCSR_QREFS_CXO_TXVBG1_CONFIG_OUT(v)      \
        out_dword(HWIO_TCSR_QREFS_CXO_TXVBG1_CONFIG_ADDR,v)
#define HWIO_TCSR_QREFS_CXO_TXVBG1_CONFIG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_QREFS_CXO_TXVBG1_CONFIG_ADDR,m,v,HWIO_TCSR_QREFS_CXO_TXVBG1_CONFIG_IN)
#define HWIO_TCSR_QREFS_CXO_TXVBG1_CONFIG_QREFS_CXO_TXVBG1_CONFIG_BMSK                                                 0xffff
#define HWIO_TCSR_QREFS_CXO_TXVBG1_CONFIG_QREFS_CXO_TXVBG1_CONFIG_SHFT                                                    0x0

#define HWIO_TCSR_QREFS_CXO2_RX0_CONFIG_ADDR                                                                       (TCSR_TCSR_REGS_REG_BASE      + 0x00015018)
#define HWIO_TCSR_QREFS_CXO2_RX0_CONFIG_RMSK                                                                             0xff
#define HWIO_TCSR_QREFS_CXO2_RX0_CONFIG_IN          \
        in_dword_masked(HWIO_TCSR_QREFS_CXO2_RX0_CONFIG_ADDR, HWIO_TCSR_QREFS_CXO2_RX0_CONFIG_RMSK)
#define HWIO_TCSR_QREFS_CXO2_RX0_CONFIG_INM(m)      \
        in_dword_masked(HWIO_TCSR_QREFS_CXO2_RX0_CONFIG_ADDR, m)
#define HWIO_TCSR_QREFS_CXO2_RX0_CONFIG_OUT(v)      \
        out_dword(HWIO_TCSR_QREFS_CXO2_RX0_CONFIG_ADDR,v)
#define HWIO_TCSR_QREFS_CXO2_RX0_CONFIG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_QREFS_CXO2_RX0_CONFIG_ADDR,m,v,HWIO_TCSR_QREFS_CXO2_RX0_CONFIG_IN)
#define HWIO_TCSR_QREFS_CXO2_RX0_CONFIG_QREFS_CXO2_RX0_CONFIG_BMSK                                                       0xff
#define HWIO_TCSR_QREFS_CXO2_RX0_CONFIG_QREFS_CXO2_RX0_CONFIG_SHFT                                                        0x0

#define HWIO_TCSR_QREFS_CXO_RPT4_CONFIG_ADDR                                                                       (TCSR_TCSR_REGS_REG_BASE      + 0x0001501c)
#define HWIO_TCSR_QREFS_CXO_RPT4_CONFIG_RMSK                                                                             0xff
#define HWIO_TCSR_QREFS_CXO_RPT4_CONFIG_IN          \
        in_dword_masked(HWIO_TCSR_QREFS_CXO_RPT4_CONFIG_ADDR, HWIO_TCSR_QREFS_CXO_RPT4_CONFIG_RMSK)
#define HWIO_TCSR_QREFS_CXO_RPT4_CONFIG_INM(m)      \
        in_dword_masked(HWIO_TCSR_QREFS_CXO_RPT4_CONFIG_ADDR, m)
#define HWIO_TCSR_QREFS_CXO_RPT4_CONFIG_OUT(v)      \
        out_dword(HWIO_TCSR_QREFS_CXO_RPT4_CONFIG_ADDR,v)
#define HWIO_TCSR_QREFS_CXO_RPT4_CONFIG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_QREFS_CXO_RPT4_CONFIG_ADDR,m,v,HWIO_TCSR_QREFS_CXO_RPT4_CONFIG_IN)
#define HWIO_TCSR_QREFS_CXO_RPT4_CONFIG_QREFS_CXO_RPT4_CONFIG_BMSK                                                       0xff
#define HWIO_TCSR_QREFS_CXO_RPT4_CONFIG_QREFS_CXO_RPT4_CONFIG_SHFT                                                        0x0

#define HWIO_TCSR_QREFS_CXO_RPT3_CONFIG_ADDR                                                                       (TCSR_TCSR_REGS_REG_BASE      + 0x00015020)
#define HWIO_TCSR_QREFS_CXO_RPT3_CONFIG_RMSK                                                                             0xff
#define HWIO_TCSR_QREFS_CXO_RPT3_CONFIG_IN          \
        in_dword_masked(HWIO_TCSR_QREFS_CXO_RPT3_CONFIG_ADDR, HWIO_TCSR_QREFS_CXO_RPT3_CONFIG_RMSK)
#define HWIO_TCSR_QREFS_CXO_RPT3_CONFIG_INM(m)      \
        in_dword_masked(HWIO_TCSR_QREFS_CXO_RPT3_CONFIG_ADDR, m)
#define HWIO_TCSR_QREFS_CXO_RPT3_CONFIG_OUT(v)      \
        out_dword(HWIO_TCSR_QREFS_CXO_RPT3_CONFIG_ADDR,v)
#define HWIO_TCSR_QREFS_CXO_RPT3_CONFIG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_QREFS_CXO_RPT3_CONFIG_ADDR,m,v,HWIO_TCSR_QREFS_CXO_RPT3_CONFIG_IN)
#define HWIO_TCSR_QREFS_CXO_RPT3_CONFIG_QREFS_CXO_RPT3_CONFIG_BMSK                                                       0xff
#define HWIO_TCSR_QREFS_CXO_RPT3_CONFIG_QREFS_CXO_RPT3_CONFIG_SHFT                                                        0x0

#define HWIO_TCSR_QREFS_CXO_RPT1_CONFIG_ADDR                                                                       (TCSR_TCSR_REGS_REG_BASE      + 0x00015024)
#define HWIO_TCSR_QREFS_CXO_RPT1_CONFIG_RMSK                                                                             0xff
#define HWIO_TCSR_QREFS_CXO_RPT1_CONFIG_IN          \
        in_dword_masked(HWIO_TCSR_QREFS_CXO_RPT1_CONFIG_ADDR, HWIO_TCSR_QREFS_CXO_RPT1_CONFIG_RMSK)
#define HWIO_TCSR_QREFS_CXO_RPT1_CONFIG_INM(m)      \
        in_dword_masked(HWIO_TCSR_QREFS_CXO_RPT1_CONFIG_ADDR, m)
#define HWIO_TCSR_QREFS_CXO_RPT1_CONFIG_OUT(v)      \
        out_dword(HWIO_TCSR_QREFS_CXO_RPT1_CONFIG_ADDR,v)
#define HWIO_TCSR_QREFS_CXO_RPT1_CONFIG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_QREFS_CXO_RPT1_CONFIG_ADDR,m,v,HWIO_TCSR_QREFS_CXO_RPT1_CONFIG_IN)
#define HWIO_TCSR_QREFS_CXO_RPT1_CONFIG_QREFS_CXO_RPT1_CONFIG_BMSK                                                       0xff
#define HWIO_TCSR_QREFS_CXO_RPT1_CONFIG_QREFS_CXO_RPT1_CONFIG_SHFT                                                        0x0

#define HWIO_TCSR_QZIP_CTL_ST_ADDR                                                                                 (TCSR_TCSR_REGS_REG_BASE      + 0x00015028)
#define HWIO_TCSR_QZIP_CTL_ST_RMSK                                                                                       0xff
#define HWIO_TCSR_QZIP_CTL_ST_IN          \
        in_dword_masked(HWIO_TCSR_QZIP_CTL_ST_ADDR, HWIO_TCSR_QZIP_CTL_ST_RMSK)
#define HWIO_TCSR_QZIP_CTL_ST_INM(m)      \
        in_dword_masked(HWIO_TCSR_QZIP_CTL_ST_ADDR, m)
#define HWIO_TCSR_QZIP_CTL_ST_OUT(v)      \
        out_dword(HWIO_TCSR_QZIP_CTL_ST_ADDR,v)
#define HWIO_TCSR_QZIP_CTL_ST_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_QZIP_CTL_ST_ADDR,m,v,HWIO_TCSR_QZIP_CTL_ST_IN)
#define HWIO_TCSR_QZIP_CTL_ST_QZIP_CTL_ST_BMSK                                                                           0xff
#define HWIO_TCSR_QZIP_CTL_ST_QZIP_CTL_ST_SHFT                                                                            0x0

#define HWIO_TCSR_TIC_CNOC_NS_ADDR                                                                                 (TCSR_TCSR_REGS_REG_BASE      + 0x0000b3e0)
#define HWIO_TCSR_TIC_CNOC_NS_RMSK                                                                                        0x1
#define HWIO_TCSR_TIC_CNOC_NS_IN          \
        in_dword_masked(HWIO_TCSR_TIC_CNOC_NS_ADDR, HWIO_TCSR_TIC_CNOC_NS_RMSK)
#define HWIO_TCSR_TIC_CNOC_NS_INM(m)      \
        in_dword_masked(HWIO_TCSR_TIC_CNOC_NS_ADDR, m)
#define HWIO_TCSR_TIC_CNOC_NS_OUT(v)      \
        out_dword(HWIO_TCSR_TIC_CNOC_NS_ADDR,v)
#define HWIO_TCSR_TIC_CNOC_NS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_TIC_CNOC_NS_ADDR,m,v,HWIO_TCSR_TIC_CNOC_NS_IN)
#define HWIO_TCSR_TIC_CNOC_NS_TIC_CNOC_NS_BMSK                                                                            0x1
#define HWIO_TCSR_TIC_CNOC_NS_TIC_CNOC_NS_SHFT                                                                            0x0

#define HWIO_TCSR_CONN_BOX_SPARE_0_ADDR                                                                            (TCSR_TCSR_REGS_REG_BASE      + 0x0000b3e4)
#define HWIO_TCSR_CONN_BOX_SPARE_0_RMSK                                                                            0xffffffff
#define HWIO_TCSR_CONN_BOX_SPARE_0_IN          \
        in_dword_masked(HWIO_TCSR_CONN_BOX_SPARE_0_ADDR, HWIO_TCSR_CONN_BOX_SPARE_0_RMSK)
#define HWIO_TCSR_CONN_BOX_SPARE_0_INM(m)      \
        in_dword_masked(HWIO_TCSR_CONN_BOX_SPARE_0_ADDR, m)
#define HWIO_TCSR_CONN_BOX_SPARE_0_OUT(v)      \
        out_dword(HWIO_TCSR_CONN_BOX_SPARE_0_ADDR,v)
#define HWIO_TCSR_CONN_BOX_SPARE_0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_CONN_BOX_SPARE_0_ADDR,m,v,HWIO_TCSR_CONN_BOX_SPARE_0_IN)
#define HWIO_TCSR_CONN_BOX_SPARE_0_CONN_BOX_SPARE_0_BMSK                                                           0xffffffff
#define HWIO_TCSR_CONN_BOX_SPARE_0_CONN_BOX_SPARE_0_SHFT                                                                  0x0

#define HWIO_TCSR_CONN_BOX_SPARE_1_ADDR                                                                            (TCSR_TCSR_REGS_REG_BASE      + 0x0000b3e8)
#define HWIO_TCSR_CONN_BOX_SPARE_1_RMSK                                                                            0xffffffff
#define HWIO_TCSR_CONN_BOX_SPARE_1_IN          \
        in_dword_masked(HWIO_TCSR_CONN_BOX_SPARE_1_ADDR, HWIO_TCSR_CONN_BOX_SPARE_1_RMSK)
#define HWIO_TCSR_CONN_BOX_SPARE_1_INM(m)      \
        in_dword_masked(HWIO_TCSR_CONN_BOX_SPARE_1_ADDR, m)
#define HWIO_TCSR_CONN_BOX_SPARE_1_OUT(v)      \
        out_dword(HWIO_TCSR_CONN_BOX_SPARE_1_ADDR,v)
#define HWIO_TCSR_CONN_BOX_SPARE_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_CONN_BOX_SPARE_1_ADDR,m,v,HWIO_TCSR_CONN_BOX_SPARE_1_IN)
#define HWIO_TCSR_CONN_BOX_SPARE_1_CONN_BOX_SPARE_1_BMSK                                                           0xffffffff
#define HWIO_TCSR_CONN_BOX_SPARE_1_CONN_BOX_SPARE_1_SHFT                                                                  0x0

#define HWIO_TCSR_CONN_BOX_SPARE_2_ADDR                                                                            (TCSR_TCSR_REGS_REG_BASE      + 0x0000b3ec)
#define HWIO_TCSR_CONN_BOX_SPARE_2_RMSK                                                                            0xffffffff
#define HWIO_TCSR_CONN_BOX_SPARE_2_IN          \
        in_dword_masked(HWIO_TCSR_CONN_BOX_SPARE_2_ADDR, HWIO_TCSR_CONN_BOX_SPARE_2_RMSK)
#define HWIO_TCSR_CONN_BOX_SPARE_2_INM(m)      \
        in_dword_masked(HWIO_TCSR_CONN_BOX_SPARE_2_ADDR, m)
#define HWIO_TCSR_CONN_BOX_SPARE_2_OUT(v)      \
        out_dword(HWIO_TCSR_CONN_BOX_SPARE_2_ADDR,v)
#define HWIO_TCSR_CONN_BOX_SPARE_2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_CONN_BOX_SPARE_2_ADDR,m,v,HWIO_TCSR_CONN_BOX_SPARE_2_IN)
#define HWIO_TCSR_CONN_BOX_SPARE_2_CONN_BOX_SPARE_2_BMSK                                                           0xffffffff
#define HWIO_TCSR_CONN_BOX_SPARE_2_CONN_BOX_SPARE_2_SHFT                                                                  0x0

#define HWIO_TCSR_Q6SS_COREPWR_ON_ADDR                                                                             (TCSR_TCSR_REGS_REG_BASE      + 0x0000b3f0)
#define HWIO_TCSR_Q6SS_COREPWR_ON_RMSK                                                                                    0x1
#define HWIO_TCSR_Q6SS_COREPWR_ON_IN          \
        in_dword_masked(HWIO_TCSR_Q6SS_COREPWR_ON_ADDR, HWIO_TCSR_Q6SS_COREPWR_ON_RMSK)
#define HWIO_TCSR_Q6SS_COREPWR_ON_INM(m)      \
        in_dword_masked(HWIO_TCSR_Q6SS_COREPWR_ON_ADDR, m)
#define HWIO_TCSR_Q6SS_COREPWR_ON_Q6SS_COREPWR_ON_BMSK                                                                    0x1
#define HWIO_TCSR_Q6SS_COREPWR_ON_Q6SS_COREPWR_ON_SHFT                                                                    0x0

#define HWIO_TCSR_MASTER_CFG_COMPUTE_SIGNALING_ADDR                                                                (TCSR_TCSR_REGS_REG_BASE      + 0x00018000)
#define HWIO_TCSR_MASTER_CFG_COMPUTE_SIGNALING_RMSK                                                                0xffffffff
#define HWIO_TCSR_MASTER_CFG_COMPUTE_SIGNALING_IN          \
        in_dword_masked(HWIO_TCSR_MASTER_CFG_COMPUTE_SIGNALING_ADDR, HWIO_TCSR_MASTER_CFG_COMPUTE_SIGNALING_RMSK)
#define HWIO_TCSR_MASTER_CFG_COMPUTE_SIGNALING_INM(m)      \
        in_dword_masked(HWIO_TCSR_MASTER_CFG_COMPUTE_SIGNALING_ADDR, m)
#define HWIO_TCSR_MASTER_CFG_COMPUTE_SIGNALING_OUT(v)      \
        out_dword(HWIO_TCSR_MASTER_CFG_COMPUTE_SIGNALING_ADDR,v)
#define HWIO_TCSR_MASTER_CFG_COMPUTE_SIGNALING_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_MASTER_CFG_COMPUTE_SIGNALING_ADDR,m,v,HWIO_TCSR_MASTER_CFG_COMPUTE_SIGNALING_IN)
#define HWIO_TCSR_MASTER_CFG_COMPUTE_SIGNALING_CFG_BITS_SHFT_BMSK                                                  0xffffffff
#define HWIO_TCSR_MASTER_CFG_COMPUTE_SIGNALING_CFG_BITS_SHFT_SHFT                                                         0x0

#define HWIO_TCSR_MASTER_COMPUTE_SIGNALING_USER_0_ADDR                                                             (TCSR_TCSR_REGS_REG_BASE      + 0x00019000)
#define HWIO_TCSR_MASTER_COMPUTE_SIGNALING_USER_0_RMSK                                                             0xffffffff
#define HWIO_TCSR_MASTER_COMPUTE_SIGNALING_USER_0_IN          \
        in_dword_masked(HWIO_TCSR_MASTER_COMPUTE_SIGNALING_USER_0_ADDR, HWIO_TCSR_MASTER_COMPUTE_SIGNALING_USER_0_RMSK)
#define HWIO_TCSR_MASTER_COMPUTE_SIGNALING_USER_0_INM(m)      \
        in_dword_masked(HWIO_TCSR_MASTER_COMPUTE_SIGNALING_USER_0_ADDR, m)
#define HWIO_TCSR_MASTER_COMPUTE_SIGNALING_USER_0_OUT(v)      \
        out_dword(HWIO_TCSR_MASTER_COMPUTE_SIGNALING_USER_0_ADDR,v)
#define HWIO_TCSR_MASTER_COMPUTE_SIGNALING_USER_0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_MASTER_COMPUTE_SIGNALING_USER_0_ADDR,m,v,HWIO_TCSR_MASTER_COMPUTE_SIGNALING_USER_0_IN)
#define HWIO_TCSR_MASTER_COMPUTE_SIGNALING_USER_0_USER_COMPUTE_SIGNALING_WRITE_STATUS_BMSK                         0xffffffff
#define HWIO_TCSR_MASTER_COMPUTE_SIGNALING_USER_0_USER_COMPUTE_SIGNALING_WRITE_STATUS_SHFT                                0x0

#define HWIO_TCSR_MASTER_COMPUTE_SIGNALING_USER_1_ADDR                                                             (TCSR_TCSR_REGS_REG_BASE      + 0x00019004)
#define HWIO_TCSR_MASTER_COMPUTE_SIGNALING_USER_1_RMSK                                                             0xffffffff
#define HWIO_TCSR_MASTER_COMPUTE_SIGNALING_USER_1_IN          \
        in_dword_masked(HWIO_TCSR_MASTER_COMPUTE_SIGNALING_USER_1_ADDR, HWIO_TCSR_MASTER_COMPUTE_SIGNALING_USER_1_RMSK)
#define HWIO_TCSR_MASTER_COMPUTE_SIGNALING_USER_1_INM(m)      \
        in_dword_masked(HWIO_TCSR_MASTER_COMPUTE_SIGNALING_USER_1_ADDR, m)
#define HWIO_TCSR_MASTER_COMPUTE_SIGNALING_USER_1_OUT(v)      \
        out_dword(HWIO_TCSR_MASTER_COMPUTE_SIGNALING_USER_1_ADDR,v)
#define HWIO_TCSR_MASTER_COMPUTE_SIGNALING_USER_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_MASTER_COMPUTE_SIGNALING_USER_1_ADDR,m,v,HWIO_TCSR_MASTER_COMPUTE_SIGNALING_USER_1_IN)
#define HWIO_TCSR_MASTER_COMPUTE_SIGNALING_USER_1_USER_COMPUTE_SIGNALING_WRITE_STATUS_BMSK                         0xffffffff
#define HWIO_TCSR_MASTER_COMPUTE_SIGNALING_USER_1_USER_COMPUTE_SIGNALING_WRITE_STATUS_SHFT                                0x0

#define HWIO_TCSR_PROCESSOR_0_COMPUTE_SIGNAL_STATUS_USER_ADDR                                                      (TCSR_TCSR_REGS_REG_BASE      + 0x0001a000)
#define HWIO_TCSR_PROCESSOR_0_COMPUTE_SIGNAL_STATUS_USER_RMSK                                                      0xffffffff
#define HWIO_TCSR_PROCESSOR_0_COMPUTE_SIGNAL_STATUS_USER_IN          \
        in_dword_masked(HWIO_TCSR_PROCESSOR_0_COMPUTE_SIGNAL_STATUS_USER_ADDR, HWIO_TCSR_PROCESSOR_0_COMPUTE_SIGNAL_STATUS_USER_RMSK)
#define HWIO_TCSR_PROCESSOR_0_COMPUTE_SIGNAL_STATUS_USER_INM(m)      \
        in_dword_masked(HWIO_TCSR_PROCESSOR_0_COMPUTE_SIGNAL_STATUS_USER_ADDR, m)
#define HWIO_TCSR_PROCESSOR_0_COMPUTE_SIGNAL_STATUS_USER_PROCESSOR_0_STATUS_USER_BMSK                              0xffffffff
#define HWIO_TCSR_PROCESSOR_0_COMPUTE_SIGNAL_STATUS_USER_PROCESSOR_0_STATUS_USER_SHFT                                     0x0

#define HWIO_TCSR_PROCESSOR_0_COMPUTE_SIGNAL_CLEAR_USER_ADDR                                                       (TCSR_TCSR_REGS_REG_BASE      + 0x0001a400)
#define HWIO_TCSR_PROCESSOR_0_COMPUTE_SIGNAL_CLEAR_USER_RMSK                                                       0xffffffff
#define HWIO_TCSR_PROCESSOR_0_COMPUTE_SIGNAL_CLEAR_USER_OUT(v)      \
        out_dword(HWIO_TCSR_PROCESSOR_0_COMPUTE_SIGNAL_CLEAR_USER_ADDR,v)
#define HWIO_TCSR_PROCESSOR_0_COMPUTE_SIGNAL_CLEAR_USER_PROCESSOR_0_CLEAR_USER_BMSK                                0xffffffff
#define HWIO_TCSR_PROCESSOR_0_COMPUTE_SIGNAL_CLEAR_USER_PROCESSOR_0_CLEAR_USER_SHFT                                       0x0

#define HWIO_TCSR_PROCESSOR_0_COMPUTE_SIGNAL_MASK_USER_ADDR                                                        (TCSR_TCSR_REGS_REG_BASE      + 0x0001a800)
#define HWIO_TCSR_PROCESSOR_0_COMPUTE_SIGNAL_MASK_USER_RMSK                                                        0xffffffff
#define HWIO_TCSR_PROCESSOR_0_COMPUTE_SIGNAL_MASK_USER_IN          \
        in_dword_masked(HWIO_TCSR_PROCESSOR_0_COMPUTE_SIGNAL_MASK_USER_ADDR, HWIO_TCSR_PROCESSOR_0_COMPUTE_SIGNAL_MASK_USER_RMSK)
#define HWIO_TCSR_PROCESSOR_0_COMPUTE_SIGNAL_MASK_USER_INM(m)      \
        in_dword_masked(HWIO_TCSR_PROCESSOR_0_COMPUTE_SIGNAL_MASK_USER_ADDR, m)
#define HWIO_TCSR_PROCESSOR_0_COMPUTE_SIGNAL_MASK_USER_OUT(v)      \
        out_dword(HWIO_TCSR_PROCESSOR_0_COMPUTE_SIGNAL_MASK_USER_ADDR,v)
#define HWIO_TCSR_PROCESSOR_0_COMPUTE_SIGNAL_MASK_USER_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_PROCESSOR_0_COMPUTE_SIGNAL_MASK_USER_ADDR,m,v,HWIO_TCSR_PROCESSOR_0_COMPUTE_SIGNAL_MASK_USER_IN)
#define HWIO_TCSR_PROCESSOR_0_COMPUTE_SIGNAL_MASK_USER_PROCESSOR_0_MASK_USER_BMSK                                  0xffffffff
#define HWIO_TCSR_PROCESSOR_0_COMPUTE_SIGNAL_MASK_USER_PROCESSOR_0_MASK_USER_SHFT                                         0x0

#define HWIO_TCSR_PROCESSOR_1_COMPUTE_SIGNAL_STATUS_USER_ADDR                                                      (TCSR_TCSR_REGS_REG_BASE      + 0x0001b000)
#define HWIO_TCSR_PROCESSOR_1_COMPUTE_SIGNAL_STATUS_USER_RMSK                                                      0xffffffff
#define HWIO_TCSR_PROCESSOR_1_COMPUTE_SIGNAL_STATUS_USER_IN          \
        in_dword_masked(HWIO_TCSR_PROCESSOR_1_COMPUTE_SIGNAL_STATUS_USER_ADDR, HWIO_TCSR_PROCESSOR_1_COMPUTE_SIGNAL_STATUS_USER_RMSK)
#define HWIO_TCSR_PROCESSOR_1_COMPUTE_SIGNAL_STATUS_USER_INM(m)      \
        in_dword_masked(HWIO_TCSR_PROCESSOR_1_COMPUTE_SIGNAL_STATUS_USER_ADDR, m)
#define HWIO_TCSR_PROCESSOR_1_COMPUTE_SIGNAL_STATUS_USER_PROCESSOR_1_STATUS_USER_BMSK                              0xffffffff
#define HWIO_TCSR_PROCESSOR_1_COMPUTE_SIGNAL_STATUS_USER_PROCESSOR_1_STATUS_USER_SHFT                                     0x0

#define HWIO_TCSR_PROCESSOR_1_COMPUTE_SIGNAL_CLEAR_USER_ADDR                                                       (TCSR_TCSR_REGS_REG_BASE      + 0x0001b400)
#define HWIO_TCSR_PROCESSOR_1_COMPUTE_SIGNAL_CLEAR_USER_RMSK                                                       0xffffffff
#define HWIO_TCSR_PROCESSOR_1_COMPUTE_SIGNAL_CLEAR_USER_OUT(v)      \
        out_dword(HWIO_TCSR_PROCESSOR_1_COMPUTE_SIGNAL_CLEAR_USER_ADDR,v)
#define HWIO_TCSR_PROCESSOR_1_COMPUTE_SIGNAL_CLEAR_USER_PROCESSOR_1_CLEAR_USER_BMSK                                0xffffffff
#define HWIO_TCSR_PROCESSOR_1_COMPUTE_SIGNAL_CLEAR_USER_PROCESSOR_1_CLEAR_USER_SHFT                                       0x0

#define HWIO_TCSR_PROCESSOR_1_COMPUTE_SIGNAL_MASK_USER_ADDR                                                        (TCSR_TCSR_REGS_REG_BASE      + 0x0001b800)
#define HWIO_TCSR_PROCESSOR_1_COMPUTE_SIGNAL_MASK_USER_RMSK                                                        0xffffffff
#define HWIO_TCSR_PROCESSOR_1_COMPUTE_SIGNAL_MASK_USER_IN          \
        in_dword_masked(HWIO_TCSR_PROCESSOR_1_COMPUTE_SIGNAL_MASK_USER_ADDR, HWIO_TCSR_PROCESSOR_1_COMPUTE_SIGNAL_MASK_USER_RMSK)
#define HWIO_TCSR_PROCESSOR_1_COMPUTE_SIGNAL_MASK_USER_INM(m)      \
        in_dword_masked(HWIO_TCSR_PROCESSOR_1_COMPUTE_SIGNAL_MASK_USER_ADDR, m)
#define HWIO_TCSR_PROCESSOR_1_COMPUTE_SIGNAL_MASK_USER_OUT(v)      \
        out_dword(HWIO_TCSR_PROCESSOR_1_COMPUTE_SIGNAL_MASK_USER_ADDR,v)
#define HWIO_TCSR_PROCESSOR_1_COMPUTE_SIGNAL_MASK_USER_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_PROCESSOR_1_COMPUTE_SIGNAL_MASK_USER_ADDR,m,v,HWIO_TCSR_PROCESSOR_1_COMPUTE_SIGNAL_MASK_USER_IN)
#define HWIO_TCSR_PROCESSOR_1_COMPUTE_SIGNAL_MASK_USER_PROCESSOR_1_MASK_USER_BMSK                                  0xffffffff
#define HWIO_TCSR_PROCESSOR_1_COMPUTE_SIGNAL_MASK_USER_PROCESSOR_1_MASK_USER_SHFT                                         0x0

#define HWIO_TCSR_PROCESSOR_2_COMPUTE_SIGNAL_STATUS_USER_ADDR                                                      (TCSR_TCSR_REGS_REG_BASE      + 0x0001c000)
#define HWIO_TCSR_PROCESSOR_2_COMPUTE_SIGNAL_STATUS_USER_RMSK                                                      0xffffffff
#define HWIO_TCSR_PROCESSOR_2_COMPUTE_SIGNAL_STATUS_USER_IN          \
        in_dword_masked(HWIO_TCSR_PROCESSOR_2_COMPUTE_SIGNAL_STATUS_USER_ADDR, HWIO_TCSR_PROCESSOR_2_COMPUTE_SIGNAL_STATUS_USER_RMSK)
#define HWIO_TCSR_PROCESSOR_2_COMPUTE_SIGNAL_STATUS_USER_INM(m)      \
        in_dword_masked(HWIO_TCSR_PROCESSOR_2_COMPUTE_SIGNAL_STATUS_USER_ADDR, m)
#define HWIO_TCSR_PROCESSOR_2_COMPUTE_SIGNAL_STATUS_USER_PROCESSOR_2_STATUS_USER_BMSK                              0xffffffff
#define HWIO_TCSR_PROCESSOR_2_COMPUTE_SIGNAL_STATUS_USER_PROCESSOR_2_STATUS_USER_SHFT                                     0x0

#define HWIO_TCSR_PROCESSOR_2_COMPUTE_SIGNAL_CLEAR_USER_ADDR                                                       (TCSR_TCSR_REGS_REG_BASE      + 0x0001c400)
#define HWIO_TCSR_PROCESSOR_2_COMPUTE_SIGNAL_CLEAR_USER_RMSK                                                       0xffffffff
#define HWIO_TCSR_PROCESSOR_2_COMPUTE_SIGNAL_CLEAR_USER_OUT(v)      \
        out_dword(HWIO_TCSR_PROCESSOR_2_COMPUTE_SIGNAL_CLEAR_USER_ADDR,v)
#define HWIO_TCSR_PROCESSOR_2_COMPUTE_SIGNAL_CLEAR_USER_PROCESSOR_2_CLEAR_USER_BMSK                                0xffffffff
#define HWIO_TCSR_PROCESSOR_2_COMPUTE_SIGNAL_CLEAR_USER_PROCESSOR_2_CLEAR_USER_SHFT                                       0x0

#define HWIO_TCSR_PROCESSOR_2_COMPUTE_SIGNAL_MASK_USER_ADDR                                                        (TCSR_TCSR_REGS_REG_BASE      + 0x0001c800)
#define HWIO_TCSR_PROCESSOR_2_COMPUTE_SIGNAL_MASK_USER_RMSK                                                        0xffffffff
#define HWIO_TCSR_PROCESSOR_2_COMPUTE_SIGNAL_MASK_USER_IN          \
        in_dword_masked(HWIO_TCSR_PROCESSOR_2_COMPUTE_SIGNAL_MASK_USER_ADDR, HWIO_TCSR_PROCESSOR_2_COMPUTE_SIGNAL_MASK_USER_RMSK)
#define HWIO_TCSR_PROCESSOR_2_COMPUTE_SIGNAL_MASK_USER_INM(m)      \
        in_dword_masked(HWIO_TCSR_PROCESSOR_2_COMPUTE_SIGNAL_MASK_USER_ADDR, m)
#define HWIO_TCSR_PROCESSOR_2_COMPUTE_SIGNAL_MASK_USER_OUT(v)      \
        out_dword(HWIO_TCSR_PROCESSOR_2_COMPUTE_SIGNAL_MASK_USER_ADDR,v)
#define HWIO_TCSR_PROCESSOR_2_COMPUTE_SIGNAL_MASK_USER_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_PROCESSOR_2_COMPUTE_SIGNAL_MASK_USER_ADDR,m,v,HWIO_TCSR_PROCESSOR_2_COMPUTE_SIGNAL_MASK_USER_IN)
#define HWIO_TCSR_PROCESSOR_2_COMPUTE_SIGNAL_MASK_USER_PROCESSOR_2_MASK_USER_BMSK                                  0xffffffff
#define HWIO_TCSR_PROCESSOR_2_COMPUTE_SIGNAL_MASK_USER_PROCESSOR_2_MASK_USER_SHFT                                         0x0

#define HWIO_TCSR_MASTER_COMPUTE_SIGNALING_KERNEL_0_ADDR                                                           (TCSR_TCSR_REGS_REG_BASE      + 0x0001d000)
#define HWIO_TCSR_MASTER_COMPUTE_SIGNALING_KERNEL_0_RMSK                                                           0xffffffff
#define HWIO_TCSR_MASTER_COMPUTE_SIGNALING_KERNEL_0_IN          \
        in_dword_masked(HWIO_TCSR_MASTER_COMPUTE_SIGNALING_KERNEL_0_ADDR, HWIO_TCSR_MASTER_COMPUTE_SIGNALING_KERNEL_0_RMSK)
#define HWIO_TCSR_MASTER_COMPUTE_SIGNALING_KERNEL_0_INM(m)      \
        in_dword_masked(HWIO_TCSR_MASTER_COMPUTE_SIGNALING_KERNEL_0_ADDR, m)
#define HWIO_TCSR_MASTER_COMPUTE_SIGNALING_KERNEL_0_OUT(v)      \
        out_dword(HWIO_TCSR_MASTER_COMPUTE_SIGNALING_KERNEL_0_ADDR,v)
#define HWIO_TCSR_MASTER_COMPUTE_SIGNALING_KERNEL_0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_MASTER_COMPUTE_SIGNALING_KERNEL_0_ADDR,m,v,HWIO_TCSR_MASTER_COMPUTE_SIGNALING_KERNEL_0_IN)
#define HWIO_TCSR_MASTER_COMPUTE_SIGNALING_KERNEL_0_KERNEL_COMPUTE_SIGNALING_WRITE_STATUS_BMSK                     0xffffffff
#define HWIO_TCSR_MASTER_COMPUTE_SIGNALING_KERNEL_0_KERNEL_COMPUTE_SIGNALING_WRITE_STATUS_SHFT                            0x0

#define HWIO_TCSR_MASTER_COMPUTE_SIGNALING_KERNEL_1_ADDR                                                           (TCSR_TCSR_REGS_REG_BASE      + 0x0001d004)
#define HWIO_TCSR_MASTER_COMPUTE_SIGNALING_KERNEL_1_RMSK                                                           0xffffffff
#define HWIO_TCSR_MASTER_COMPUTE_SIGNALING_KERNEL_1_IN          \
        in_dword_masked(HWIO_TCSR_MASTER_COMPUTE_SIGNALING_KERNEL_1_ADDR, HWIO_TCSR_MASTER_COMPUTE_SIGNALING_KERNEL_1_RMSK)
#define HWIO_TCSR_MASTER_COMPUTE_SIGNALING_KERNEL_1_INM(m)      \
        in_dword_masked(HWIO_TCSR_MASTER_COMPUTE_SIGNALING_KERNEL_1_ADDR, m)
#define HWIO_TCSR_MASTER_COMPUTE_SIGNALING_KERNEL_1_OUT(v)      \
        out_dword(HWIO_TCSR_MASTER_COMPUTE_SIGNALING_KERNEL_1_ADDR,v)
#define HWIO_TCSR_MASTER_COMPUTE_SIGNALING_KERNEL_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_MASTER_COMPUTE_SIGNALING_KERNEL_1_ADDR,m,v,HWIO_TCSR_MASTER_COMPUTE_SIGNALING_KERNEL_1_IN)
#define HWIO_TCSR_MASTER_COMPUTE_SIGNALING_KERNEL_1_KERNEL_COMPUTE_SIGNALING_WRITE_STATUS_BMSK                     0xffffffff
#define HWIO_TCSR_MASTER_COMPUTE_SIGNALING_KERNEL_1_KERNEL_COMPUTE_SIGNALING_WRITE_STATUS_SHFT                            0x0

#define HWIO_TCSR_PROCESSOR_0_COMPUTE_SIGNAL_STATUS_KERNEL_ADDR                                                    (TCSR_TCSR_REGS_REG_BASE      + 0x0001e000)
#define HWIO_TCSR_PROCESSOR_0_COMPUTE_SIGNAL_STATUS_KERNEL_RMSK                                                    0xffffffff
#define HWIO_TCSR_PROCESSOR_0_COMPUTE_SIGNAL_STATUS_KERNEL_IN          \
        in_dword_masked(HWIO_TCSR_PROCESSOR_0_COMPUTE_SIGNAL_STATUS_KERNEL_ADDR, HWIO_TCSR_PROCESSOR_0_COMPUTE_SIGNAL_STATUS_KERNEL_RMSK)
#define HWIO_TCSR_PROCESSOR_0_COMPUTE_SIGNAL_STATUS_KERNEL_INM(m)      \
        in_dword_masked(HWIO_TCSR_PROCESSOR_0_COMPUTE_SIGNAL_STATUS_KERNEL_ADDR, m)
#define HWIO_TCSR_PROCESSOR_0_COMPUTE_SIGNAL_STATUS_KERNEL_PROCESSOR_0_STATUS_KERNEL_BMSK                          0xffffffff
#define HWIO_TCSR_PROCESSOR_0_COMPUTE_SIGNAL_STATUS_KERNEL_PROCESSOR_0_STATUS_KERNEL_SHFT                                 0x0

#define HWIO_TCSR_PROCESSOR_0_COMPUTE_SIGNAL_CLEAR_KERNEL_ADDR                                                     (TCSR_TCSR_REGS_REG_BASE      + 0x0001e400)
#define HWIO_TCSR_PROCESSOR_0_COMPUTE_SIGNAL_CLEAR_KERNEL_RMSK                                                     0xffffffff
#define HWIO_TCSR_PROCESSOR_0_COMPUTE_SIGNAL_CLEAR_KERNEL_OUT(v)      \
        out_dword(HWIO_TCSR_PROCESSOR_0_COMPUTE_SIGNAL_CLEAR_KERNEL_ADDR,v)
#define HWIO_TCSR_PROCESSOR_0_COMPUTE_SIGNAL_CLEAR_KERNEL_PROCESSOR_0_CLEAR_KERNEL_BMSK                            0xffffffff
#define HWIO_TCSR_PROCESSOR_0_COMPUTE_SIGNAL_CLEAR_KERNEL_PROCESSOR_0_CLEAR_KERNEL_SHFT                                   0x0

#define HWIO_TCSR_PROCESSOR_0_COMPUTE_SIGNAL_MASK_KERNEL_ADDR                                                      (TCSR_TCSR_REGS_REG_BASE      + 0x0001e800)
#define HWIO_TCSR_PROCESSOR_0_COMPUTE_SIGNAL_MASK_KERNEL_RMSK                                                      0xffffffff
#define HWIO_TCSR_PROCESSOR_0_COMPUTE_SIGNAL_MASK_KERNEL_IN          \
        in_dword_masked(HWIO_TCSR_PROCESSOR_0_COMPUTE_SIGNAL_MASK_KERNEL_ADDR, HWIO_TCSR_PROCESSOR_0_COMPUTE_SIGNAL_MASK_KERNEL_RMSK)
#define HWIO_TCSR_PROCESSOR_0_COMPUTE_SIGNAL_MASK_KERNEL_INM(m)      \
        in_dword_masked(HWIO_TCSR_PROCESSOR_0_COMPUTE_SIGNAL_MASK_KERNEL_ADDR, m)
#define HWIO_TCSR_PROCESSOR_0_COMPUTE_SIGNAL_MASK_KERNEL_OUT(v)      \
        out_dword(HWIO_TCSR_PROCESSOR_0_COMPUTE_SIGNAL_MASK_KERNEL_ADDR,v)
#define HWIO_TCSR_PROCESSOR_0_COMPUTE_SIGNAL_MASK_KERNEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_PROCESSOR_0_COMPUTE_SIGNAL_MASK_KERNEL_ADDR,m,v,HWIO_TCSR_PROCESSOR_0_COMPUTE_SIGNAL_MASK_KERNEL_IN)
#define HWIO_TCSR_PROCESSOR_0_COMPUTE_SIGNAL_MASK_KERNEL_PROCESSOR_0_MASK_KERNEL_BMSK                              0xffffffff
#define HWIO_TCSR_PROCESSOR_0_COMPUTE_SIGNAL_MASK_KERNEL_PROCESSOR_0_MASK_KERNEL_SHFT                                     0x0

#define HWIO_TCSR_PROCESSOR_1_COMPUTE_SIGNAL_STATUS_KERNEL_ADDR                                                    (TCSR_TCSR_REGS_REG_BASE      + 0x0001f000)
#define HWIO_TCSR_PROCESSOR_1_COMPUTE_SIGNAL_STATUS_KERNEL_RMSK                                                    0xffffffff
#define HWIO_TCSR_PROCESSOR_1_COMPUTE_SIGNAL_STATUS_KERNEL_IN          \
        in_dword_masked(HWIO_TCSR_PROCESSOR_1_COMPUTE_SIGNAL_STATUS_KERNEL_ADDR, HWIO_TCSR_PROCESSOR_1_COMPUTE_SIGNAL_STATUS_KERNEL_RMSK)
#define HWIO_TCSR_PROCESSOR_1_COMPUTE_SIGNAL_STATUS_KERNEL_INM(m)      \
        in_dword_masked(HWIO_TCSR_PROCESSOR_1_COMPUTE_SIGNAL_STATUS_KERNEL_ADDR, m)
#define HWIO_TCSR_PROCESSOR_1_COMPUTE_SIGNAL_STATUS_KERNEL_PROCESSOR_1_STATUS_KERNEL_BMSK                          0xffffffff
#define HWIO_TCSR_PROCESSOR_1_COMPUTE_SIGNAL_STATUS_KERNEL_PROCESSOR_1_STATUS_KERNEL_SHFT                                 0x0

#define HWIO_TCSR_PROCESSOR_1_COMPUTE_SIGNAL_CLEAR_KERNEL_ADDR                                                     (TCSR_TCSR_REGS_REG_BASE      + 0x0001f400)
#define HWIO_TCSR_PROCESSOR_1_COMPUTE_SIGNAL_CLEAR_KERNEL_RMSK                                                     0xffffffff
#define HWIO_TCSR_PROCESSOR_1_COMPUTE_SIGNAL_CLEAR_KERNEL_OUT(v)      \
        out_dword(HWIO_TCSR_PROCESSOR_1_COMPUTE_SIGNAL_CLEAR_KERNEL_ADDR,v)
#define HWIO_TCSR_PROCESSOR_1_COMPUTE_SIGNAL_CLEAR_KERNEL_PROCESSOR_1_CLEAR_KERNEL_BMSK                            0xffffffff
#define HWIO_TCSR_PROCESSOR_1_COMPUTE_SIGNAL_CLEAR_KERNEL_PROCESSOR_1_CLEAR_KERNEL_SHFT                                   0x0

#define HWIO_TCSR_PROCESSOR_1_COMPUTE_SIGNAL_MASK_KERNEL_ADDR                                                      (TCSR_TCSR_REGS_REG_BASE      + 0x0001f800)
#define HWIO_TCSR_PROCESSOR_1_COMPUTE_SIGNAL_MASK_KERNEL_RMSK                                                      0xffffffff
#define HWIO_TCSR_PROCESSOR_1_COMPUTE_SIGNAL_MASK_KERNEL_IN          \
        in_dword_masked(HWIO_TCSR_PROCESSOR_1_COMPUTE_SIGNAL_MASK_KERNEL_ADDR, HWIO_TCSR_PROCESSOR_1_COMPUTE_SIGNAL_MASK_KERNEL_RMSK)
#define HWIO_TCSR_PROCESSOR_1_COMPUTE_SIGNAL_MASK_KERNEL_INM(m)      \
        in_dword_masked(HWIO_TCSR_PROCESSOR_1_COMPUTE_SIGNAL_MASK_KERNEL_ADDR, m)
#define HWIO_TCSR_PROCESSOR_1_COMPUTE_SIGNAL_MASK_KERNEL_OUT(v)      \
        out_dword(HWIO_TCSR_PROCESSOR_1_COMPUTE_SIGNAL_MASK_KERNEL_ADDR,v)
#define HWIO_TCSR_PROCESSOR_1_COMPUTE_SIGNAL_MASK_KERNEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_PROCESSOR_1_COMPUTE_SIGNAL_MASK_KERNEL_ADDR,m,v,HWIO_TCSR_PROCESSOR_1_COMPUTE_SIGNAL_MASK_KERNEL_IN)
#define HWIO_TCSR_PROCESSOR_1_COMPUTE_SIGNAL_MASK_KERNEL_PROCESSOR_1_MASK_KERNEL_BMSK                              0xffffffff
#define HWIO_TCSR_PROCESSOR_1_COMPUTE_SIGNAL_MASK_KERNEL_PROCESSOR_1_MASK_KERNEL_SHFT                                     0x0

#define HWIO_TCSR_PROCESSOR_2_COMPUTE_SIGNAL_STATUS_KERNEL_ADDR                                                    (TCSR_TCSR_REGS_REG_BASE      + 0x00020000)
#define HWIO_TCSR_PROCESSOR_2_COMPUTE_SIGNAL_STATUS_KERNEL_RMSK                                                    0xffffffff
#define HWIO_TCSR_PROCESSOR_2_COMPUTE_SIGNAL_STATUS_KERNEL_IN          \
        in_dword_masked(HWIO_TCSR_PROCESSOR_2_COMPUTE_SIGNAL_STATUS_KERNEL_ADDR, HWIO_TCSR_PROCESSOR_2_COMPUTE_SIGNAL_STATUS_KERNEL_RMSK)
#define HWIO_TCSR_PROCESSOR_2_COMPUTE_SIGNAL_STATUS_KERNEL_INM(m)      \
        in_dword_masked(HWIO_TCSR_PROCESSOR_2_COMPUTE_SIGNAL_STATUS_KERNEL_ADDR, m)
#define HWIO_TCSR_PROCESSOR_2_COMPUTE_SIGNAL_STATUS_KERNEL_PROCESSOR_2_STATUS_KERNEL_BMSK                          0xffffffff
#define HWIO_TCSR_PROCESSOR_2_COMPUTE_SIGNAL_STATUS_KERNEL_PROCESSOR_2_STATUS_KERNEL_SHFT                                 0x0

#define HWIO_TCSR_PROCESSOR_2_COMPUTE_SIGNAL_CLEAR_KERNEL_ADDR                                                     (TCSR_TCSR_REGS_REG_BASE      + 0x00020400)
#define HWIO_TCSR_PROCESSOR_2_COMPUTE_SIGNAL_CLEAR_KERNEL_RMSK                                                     0xffffffff
#define HWIO_TCSR_PROCESSOR_2_COMPUTE_SIGNAL_CLEAR_KERNEL_OUT(v)      \
        out_dword(HWIO_TCSR_PROCESSOR_2_COMPUTE_SIGNAL_CLEAR_KERNEL_ADDR,v)
#define HWIO_TCSR_PROCESSOR_2_COMPUTE_SIGNAL_CLEAR_KERNEL_PROCESSOR_2_CLEAR_KERNEL_BMSK                            0xffffffff
#define HWIO_TCSR_PROCESSOR_2_COMPUTE_SIGNAL_CLEAR_KERNEL_PROCESSOR_2_CLEAR_KERNEL_SHFT                                   0x0

#define HWIO_TCSR_PROCESSOR_2_COMPUTE_SIGNAL_MASK_KERNEL_ADDR                                                      (TCSR_TCSR_REGS_REG_BASE      + 0x00020800)
#define HWIO_TCSR_PROCESSOR_2_COMPUTE_SIGNAL_MASK_KERNEL_RMSK                                                      0xffffffff
#define HWIO_TCSR_PROCESSOR_2_COMPUTE_SIGNAL_MASK_KERNEL_IN          \
        in_dword_masked(HWIO_TCSR_PROCESSOR_2_COMPUTE_SIGNAL_MASK_KERNEL_ADDR, HWIO_TCSR_PROCESSOR_2_COMPUTE_SIGNAL_MASK_KERNEL_RMSK)
#define HWIO_TCSR_PROCESSOR_2_COMPUTE_SIGNAL_MASK_KERNEL_INM(m)      \
        in_dword_masked(HWIO_TCSR_PROCESSOR_2_COMPUTE_SIGNAL_MASK_KERNEL_ADDR, m)
#define HWIO_TCSR_PROCESSOR_2_COMPUTE_SIGNAL_MASK_KERNEL_OUT(v)      \
        out_dword(HWIO_TCSR_PROCESSOR_2_COMPUTE_SIGNAL_MASK_KERNEL_ADDR,v)
#define HWIO_TCSR_PROCESSOR_2_COMPUTE_SIGNAL_MASK_KERNEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_PROCESSOR_2_COMPUTE_SIGNAL_MASK_KERNEL_ADDR,m,v,HWIO_TCSR_PROCESSOR_2_COMPUTE_SIGNAL_MASK_KERNEL_IN)
#define HWIO_TCSR_PROCESSOR_2_COMPUTE_SIGNAL_MASK_KERNEL_PROCESSOR_2_MASK_KERNEL_BMSK                              0xffffffff
#define HWIO_TCSR_PROCESSOR_2_COMPUTE_SIGNAL_MASK_KERNEL_PROCESSOR_2_MASK_KERNEL_SHFT                                     0x0

#define HWIO_TCSR_SS_XPU_SP_INTR0_ADDR                                                                             (TCSR_TCSR_REGS_REG_BASE      + 0x00021000)
#define HWIO_TCSR_SS_XPU_SP_INTR0_RMSK                                                                             0xffffffff
#define HWIO_TCSR_SS_XPU_SP_INTR0_IN          \
        in_dword_masked(HWIO_TCSR_SS_XPU_SP_INTR0_ADDR, HWIO_TCSR_SS_XPU_SP_INTR0_RMSK)
#define HWIO_TCSR_SS_XPU_SP_INTR0_INM(m)      \
        in_dword_masked(HWIO_TCSR_SS_XPU_SP_INTR0_ADDR, m)
#define HWIO_TCSR_SS_XPU_SP_INTR0_RESERVE_31_BMSK                                                                  0x80000000
#define HWIO_TCSR_SS_XPU_SP_INTR0_RESERVE_31_SHFT                                                                        0x1f
#define HWIO_TCSR_SS_XPU_SP_INTR0_BOOT_ROM_SP_INTR_BMSK                                                            0x40000000
#define HWIO_TCSR_SS_XPU_SP_INTR0_BOOT_ROM_SP_INTR_SHFT                                                                  0x1e
#define HWIO_TCSR_SS_XPU_SP_INTR0_SDC1_ICE_XPU_SP_INTR_BMSK                                                        0x20000000
#define HWIO_TCSR_SS_XPU_SP_INTR0_SDC1_ICE_XPU_SP_INTR_SHFT                                                              0x1d
#define HWIO_TCSR_SS_XPU_SP_INTR0_MSS_MPU_XPU_SP_INTR_BMSK                                                         0x10000000
#define HWIO_TCSR_SS_XPU_SP_INTR0_MSS_MPU_XPU_SP_INTR_SHFT                                                               0x1c
#define HWIO_TCSR_SS_XPU_SP_INTR0_TLMM_CENTER_XPU_SP_INTR_BMSK                                                      0x8000000
#define HWIO_TCSR_SS_XPU_SP_INTR0_TLMM_CENTER_XPU_SP_INTR_SHFT                                                           0x1b
#define HWIO_TCSR_SS_XPU_SP_INTR0_SPDM_XPU_SP_INTR_BMSK                                                             0x4000000
#define HWIO_TCSR_SS_XPU_SP_INTR0_SPDM_XPU_SP_INTR_SHFT                                                                  0x1a
#define HWIO_TCSR_SS_XPU_SP_INTR0_PMIC_ARB_XPU_SP_INTR_BMSK                                                         0x2000000
#define HWIO_TCSR_SS_XPU_SP_INTR0_PMIC_ARB_XPU_SP_INTR_SHFT                                                              0x19
#define HWIO_TCSR_SS_XPU_SP_INTR0_UFS_ICE_XPU_SP_INTR_BMSK                                                          0x1000000
#define HWIO_TCSR_SS_XPU_SP_INTR0_UFS_ICE_XPU_SP_INTR_SHFT                                                               0x18
#define HWIO_TCSR_SS_XPU_SP_INTR0_QHS_SNOC_XPU_SP_INTERRUPT_BMSK                                                     0x800000
#define HWIO_TCSR_SS_XPU_SP_INTR0_QHS_SNOC_XPU_SP_INTERRUPT_SHFT                                                         0x17
#define HWIO_TCSR_SS_XPU_SP_INTR0_QHS_QDSS_CFG_SP_INTERRUPT_BMSK                                                     0x400000
#define HWIO_TCSR_SS_XPU_SP_INTR0_QHS_QDSS_CFG_SP_INTERRUPT_SHFT                                                         0x16
#define HWIO_TCSR_SS_XPU_SP_INTR0_QHS_A2NOC_CFG_XPU_SP_INTERRUPT_BMSK                                                0x200000
#define HWIO_TCSR_SS_XPU_SP_INTR0_QHS_A2NOC_CFG_XPU_SP_INTERRUPT_SHFT                                                    0x15
#define HWIO_TCSR_SS_XPU_SP_INTR0_QXM_SNOC_MS_XPU_SP_INTERRUPT_BMSK                                                  0x100000
#define HWIO_TCSR_SS_XPU_SP_INTR0_QXM_SNOC_MS_XPU_SP_INTERRUPT_SHFT                                                      0x14
#define HWIO_TCSR_SS_XPU_SP_INTR0_GCC_RPU_XPU_SP_INTR_BMSK                                                            0x80000
#define HWIO_TCSR_SS_XPU_SP_INTR0_GCC_RPU_XPU_SP_INTR_SHFT                                                               0x13
#define HWIO_TCSR_SS_XPU_SP_INTR0_BIMC_CH1_XPU_SP_INTR_BMSK                                                           0x40000
#define HWIO_TCSR_SS_XPU_SP_INTR0_BIMC_CH1_XPU_SP_INTR_SHFT                                                              0x12
#define HWIO_TCSR_SS_XPU_SP_INTR0_BIMC_CH0_XPU_SP_INTR_BMSK                                                           0x20000
#define HWIO_TCSR_SS_XPU_SP_INTR0_BIMC_CH0_XPU_SP_INTR_SHFT                                                              0x11
#define HWIO_TCSR_SS_XPU_SP_INTR0_BIMC_CFG_XPU_SP_INTR_BMSK                                                           0x10000
#define HWIO_TCSR_SS_XPU_SP_INTR0_BIMC_CFG_XPU_SP_INTR_SHFT                                                              0x10
#define HWIO_TCSR_SS_XPU_SP_INTR0_QXM_MSS_NAV_CE_XPU_SP_INTR_BMSK                                                      0x8000
#define HWIO_TCSR_SS_XPU_SP_INTR0_QXM_MSS_NAV_CE_XPU_SP_INTR_SHFT                                                         0xf
#define HWIO_TCSR_SS_XPU_SP_INTR0_PIMEM_MPU_SP_IRQ_BMSK                                                                0x4000
#define HWIO_TCSR_SS_XPU_SP_INTR0_PIMEM_MPU_SP_IRQ_SHFT                                                                   0xe
#define HWIO_TCSR_SS_XPU_SP_INTR0_PIMEM_APU_SP_IRQ_BMSK                                                                0x2000
#define HWIO_TCSR_SS_XPU_SP_INTR0_PIMEM_APU_SP_IRQ_SHFT                                                                   0xd
#define HWIO_TCSR_SS_XPU_SP_INTR0_TURING_XPU_IRQ_BMSK                                                                  0x1000
#define HWIO_TCSR_SS_XPU_SP_INTR0_TURING_XPU_IRQ_SHFT                                                                     0xc
#define HWIO_TCSR_SS_XPU_SP_INTR0_LPASS_XPU_IRQ_APPS_13_BMSK                                                            0x800
#define HWIO_TCSR_SS_XPU_SP_INTR0_LPASS_XPU_IRQ_APPS_13_SHFT                                                              0xb
#define HWIO_TCSR_SS_XPU_SP_INTR0_LPASS_XPU_IRQ_APPS_3_BMSK                                                             0x400
#define HWIO_TCSR_SS_XPU_SP_INTR0_LPASS_XPU_IRQ_APPS_3_SHFT                                                               0xa
#define HWIO_TCSR_SS_XPU_SP_INTR0_SEC_CTRL_APU_XPU_SP_INTR_BMSK                                                         0x200
#define HWIO_TCSR_SS_XPU_SP_INTR0_SEC_CTRL_APU_XPU_SP_INTR_SHFT                                                           0x9
#define HWIO_TCSR_SS_XPU_SP_INTR0_DCC_XPU_SP_INTR_BMSK                                                                  0x100
#define HWIO_TCSR_SS_XPU_SP_INTR0_DCC_XPU_SP_INTR_SHFT                                                                    0x8
#define HWIO_TCSR_SS_XPU_SP_INTR0_OCIMEM_RPU_SP_INTR_BMSK                                                                0x80
#define HWIO_TCSR_SS_XPU_SP_INTR0_OCIMEM_RPU_SP_INTR_SHFT                                                                 0x7
#define HWIO_TCSR_SS_XPU_SP_INTR0_CRYPTO0_BAM_XPU_SP_INTR_BMSK                                                           0x40
#define HWIO_TCSR_SS_XPU_SP_INTR0_CRYPTO0_BAM_XPU_SP_INTR_SHFT                                                            0x6
#define HWIO_TCSR_SS_XPU_SP_INTR0_O_TCSR_MUTEX_SP_INTR_BMSK                                                              0x20
#define HWIO_TCSR_SS_XPU_SP_INTR0_O_TCSR_MUTEX_SP_INTR_SHFT                                                               0x5
#define HWIO_TCSR_SS_XPU_SP_INTR0_APSS_SP_INTR_BMSK                                                                      0x10
#define HWIO_TCSR_SS_XPU_SP_INTR0_APSS_SP_INTR_SHFT                                                                       0x4
#define HWIO_TCSR_SS_XPU_SP_INTR0_O_TCSR_REGS_SP_INTR_BMSK                                                                0x8
#define HWIO_TCSR_SS_XPU_SP_INTR0_O_TCSR_REGS_SP_INTR_SHFT                                                                0x3
#define HWIO_TCSR_SS_XPU_SP_INTR0_MMSS_NOC_XPU_SP_INTR_BMSK                                                               0x4
#define HWIO_TCSR_SS_XPU_SP_INTR0_MMSS_NOC_XPU_SP_INTR_SHFT                                                               0x2
#define HWIO_TCSR_SS_XPU_SP_INTR0_RESERVE_1_BMSK                                                                          0x2
#define HWIO_TCSR_SS_XPU_SP_INTR0_RESERVE_1_SHFT                                                                          0x1
#define HWIO_TCSR_SS_XPU_SP_INTR0_MMSS_QM_XPU_SP_INTR_BMSK                                                                0x1
#define HWIO_TCSR_SS_XPU_SP_INTR0_MMSS_QM_XPU_SP_INTR_SHFT                                                                0x0

#define HWIO_TCSR_SS_XPU_SP_INTR1_ADDR                                                                             (TCSR_TCSR_REGS_REG_BASE      + 0x00021004)
#define HWIO_TCSR_SS_XPU_SP_INTR1_RMSK                                                                                0x3ffff
#define HWIO_TCSR_SS_XPU_SP_INTR1_IN          \
        in_dword_masked(HWIO_TCSR_SS_XPU_SP_INTR1_ADDR, HWIO_TCSR_SS_XPU_SP_INTR1_RMSK)
#define HWIO_TCSR_SS_XPU_SP_INTR1_INM(m)      \
        in_dword_masked(HWIO_TCSR_SS_XPU_SP_INTR1_ADDR, m)
#define HWIO_TCSR_SS_XPU_SP_INTR1_LPASS_IRQ_OUT_SECURITY_23_BMSK                                                      0x20000
#define HWIO_TCSR_SS_XPU_SP_INTR1_LPASS_IRQ_OUT_SECURITY_23_SHFT                                                         0x11
#define HWIO_TCSR_SS_XPU_SP_INTR1_MMSS_XPU_MMSS_CC_XPU_SP_INTR_BMSK                                                   0x10000
#define HWIO_TCSR_SS_XPU_SP_INTR1_MMSS_XPU_MMSS_CC_XPU_SP_INTR_SHFT                                                      0x10
#define HWIO_TCSR_SS_XPU_SP_INTR1_TLMM_NORTH_XPU_SP_INTR_BMSK                                                          0x8000
#define HWIO_TCSR_SS_XPU_SP_INTR1_TLMM_NORTH_XPU_SP_INTR_SHFT                                                             0xf
#define HWIO_TCSR_SS_XPU_SP_INTR1_SKL_XPU_SP_INTR_BMSK                                                                 0x4000
#define HWIO_TCSR_SS_XPU_SP_INTR1_SKL_XPU_SP_INTR_SHFT                                                                    0xe
#define HWIO_TCSR_SS_XPU_SP_INTR1_ANOC1_MPU_XPU_SP_INTR_BMSK                                                           0x2000
#define HWIO_TCSR_SS_XPU_SP_INTR1_ANOC1_MPU_XPU_SP_INTR_SHFT                                                              0xd
#define HWIO_TCSR_SS_XPU_SP_INTR1_ANOC2_MPU_XPU_SP_INTR_BMSK                                                           0x1000
#define HWIO_TCSR_SS_XPU_SP_INTR1_ANOC2_MPU_XPU_SP_INTR_SHFT                                                              0xc
#define HWIO_TCSR_SS_XPU_SP_INTR1_IPA_0_XPU_SP_INTR_BMSK                                                                0x800
#define HWIO_TCSR_SS_XPU_SP_INTR1_IPA_0_XPU_SP_INTR_SHFT                                                                  0xb
#define HWIO_TCSR_SS_XPU_SP_INTR1_MSS_Q6_MPU_XPU_SP_INTR_BMSK                                                           0x400
#define HWIO_TCSR_SS_XPU_SP_INTR1_MSS_Q6_MPU_XPU_SP_INTR_SHFT                                                             0xa
#define HWIO_TCSR_SS_XPU_SP_INTR1_RPM_MPU_SP_INTR_BMSK                                                                  0x200
#define HWIO_TCSR_SS_XPU_SP_INTR1_RPM_MPU_SP_INTR_SHFT                                                                    0x9
#define HWIO_TCSR_SS_XPU_SP_INTR1_LPASS_IRQ_OUT_SECURITY_21_BMSK                                                        0x100
#define HWIO_TCSR_SS_XPU_SP_INTR1_LPASS_IRQ_OUT_SECURITY_21_SHFT                                                          0x8
#define HWIO_TCSR_SS_XPU_SP_INTR1_MDSS_XPU_XPU_SP_INTR_BMSK                                                              0x80
#define HWIO_TCSR_SS_XPU_SP_INTR1_MDSS_XPU_XPU_SP_INTR_SHFT                                                               0x7
#define HWIO_TCSR_SS_XPU_SP_INTR1_QDSS_BAM_XPU_SP_INTR_BMSK                                                              0x40
#define HWIO_TCSR_SS_XPU_SP_INTR1_QDSS_BAM_XPU_SP_INTR_SHFT                                                               0x6
#define HWIO_TCSR_SS_XPU_SP_INTR1_MPM2_XPU_SP_INTR_BMSK                                                                  0x20
#define HWIO_TCSR_SS_XPU_SP_INTR1_MPM2_XPU_SP_INTR_SHFT                                                                   0x5
#define HWIO_TCSR_SS_XPU_SP_INTR1_DDR_REGS_CFG_XPU_SP_INTR_BMSK                                                          0x10
#define HWIO_TCSR_SS_XPU_SP_INTR1_DDR_REGS_CFG_XPU_SP_INTR_SHFT                                                           0x4
#define HWIO_TCSR_SS_XPU_SP_INTR1_TLMM_SOUTH_XPU_SP_INTR_BMSK                                                             0x8
#define HWIO_TCSR_SS_XPU_SP_INTR1_TLMM_SOUTH_XPU_SP_INTR_SHFT                                                             0x3
#define HWIO_TCSR_SS_XPU_SP_INTR1_PERIPH_SS_BLSP2_BLSP_BAM_XPU_SP_INTR_BMSK                                               0x4
#define HWIO_TCSR_SS_XPU_SP_INTR1_PERIPH_SS_BLSP2_BLSP_BAM_XPU_SP_INTR_SHFT                                               0x2
#define HWIO_TCSR_SS_XPU_SP_INTR1_PERIPH_SS_BLSP1_BLSP_BAM_XPU_SP_INTR_BMSK                                               0x2
#define HWIO_TCSR_SS_XPU_SP_INTR1_PERIPH_SS_BLSP1_BLSP_BAM_XPU_SP_INTR_SHFT                                               0x1
#define HWIO_TCSR_SS_XPU_SP_INTR1_OCIMEM_RPU_SP_INTR_BMSK                                                                 0x1
#define HWIO_TCSR_SS_XPU_SP_INTR1_OCIMEM_RPU_SP_INTR_SHFT                                                                 0x0

#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_ADDR                                                                      (TCSR_TCSR_REGS_REG_BASE      + 0x00021008)
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_RMSK                                                                      0xffffffff
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_IN          \
        in_dword_masked(HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_ADDR, HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_RMSK)
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_INM(m)      \
        in_dword_masked(HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_ADDR, m)
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_OUT(v)      \
        out_dword(HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_ADDR,v)
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_ADDR,m,v,HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_IN)
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_RESERVE_31_BMSK                                                           0x80000000
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_RESERVE_31_SHFT                                                                 0x1f
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_BOOT_ROM_SP_INTR_ENABLE_BMSK                                              0x40000000
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_BOOT_ROM_SP_INTR_ENABLE_SHFT                                                    0x1e
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_SDC1_ICE_XPU_SP_INTR_ENABLE_BMSK                                          0x20000000
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_SDC1_ICE_XPU_SP_INTR_ENABLE_SHFT                                                0x1d
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_MSS_MPU_XPU_SP_INTR_ENABLE_BMSK                                           0x10000000
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_MSS_MPU_XPU_SP_INTR_ENABLE_SHFT                                                 0x1c
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_TLMM_CENTER_XPU_SP_INTR_ENABLE_BMSK                                        0x8000000
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_TLMM_CENTER_XPU_SP_INTR_ENABLE_SHFT                                             0x1b
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_SPDM_XPU_SP_INTR_ENABLE_BMSK                                               0x4000000
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_SPDM_XPU_SP_INTR_ENABLE_SHFT                                                    0x1a
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_PMIC_ARB_XPU_SP_INTR_ENABLE_BMSK                                           0x2000000
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_PMIC_ARB_XPU_SP_INTR_ENABLE_SHFT                                                0x19
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_UFS_ICE_XPU_SP_INTR_ENABLE_BMSK                                            0x1000000
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_UFS_ICE_XPU_SP_INTR_ENABLE_SHFT                                                 0x18
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_QHS_SNOC_XPU_SP_INTERRUPT_ENABLE_BMSK                                       0x800000
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_QHS_SNOC_XPU_SP_INTERRUPT_ENABLE_SHFT                                           0x17
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_QHS_QDSS_CFG_SP_INTERRUPT_ENABLE_BMSK                                       0x400000
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_QHS_QDSS_CFG_SP_INTERRUPT_ENABLE_SHFT                                           0x16
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_QHS_A2NOC_CFG_XPU_SP_INTERRUPT_ENABLE_BMSK                                  0x200000
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_QHS_A2NOC_CFG_XPU_SP_INTERRUPT_ENABLE_SHFT                                      0x15
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_QXM_SNOC_MS_XPU_SP_INTERRUPT_ENABLE_BMSK                                    0x100000
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_QXM_SNOC_MS_XPU_SP_INTERRUPT_ENABLE_SHFT                                        0x14
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_GCC_RPU_XPU_SP_INTR_ENABLE_BMSK                                              0x80000
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_GCC_RPU_XPU_SP_INTR_ENABLE_SHFT                                                 0x13
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_BIMC_CH1_XPU_SP_INTR_ENABLE_BMSK                                             0x40000
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_BIMC_CH1_XPU_SP_INTR_ENABLE_SHFT                                                0x12
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_BIMC_CH0_XPU_SP_INTR_ENABLE_BMSK                                             0x20000
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_BIMC_CH0_XPU_SP_INTR_ENABLE_SHFT                                                0x11
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_BIMC_CFG_XPU_SP_INTR_ENABLE_BMSK                                             0x10000
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_BIMC_CFG_XPU_SP_INTR_ENABLE_SHFT                                                0x10
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_QXM_MSS_NAV_CE_XPU_SP_INTR_ENABLE_BMSK                                        0x8000
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_QXM_MSS_NAV_CE_XPU_SP_INTR_ENABLE_SHFT                                           0xf
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_PIMEM_MPU_SP_IRQ_ENABLE_BMSK                                                  0x4000
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_PIMEM_MPU_SP_IRQ_ENABLE_SHFT                                                     0xe
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_PIMEM_APU_SP_IRQ_ENABLE_BMSK                                                  0x2000
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_PIMEM_APU_SP_IRQ_ENABLE_SHFT                                                     0xd
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_TURING_XPU_IRQ_ENABLE_BMSK                                                    0x1000
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_TURING_XPU_IRQ_ENABLE_SHFT                                                       0xc
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_LPASS_XPU_IRQ_APPS_13_ENABLE_BMSK                                              0x800
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_LPASS_XPU_IRQ_APPS_13_ENABLE_SHFT                                                0xb
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_LPASS_XPU_IRQ_APPS_3_ENABLE_BMSK                                               0x400
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_LPASS_XPU_IRQ_APPS_3_ENABLE_SHFT                                                 0xa
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_SEC_CTRL_APU_XPU_SP_INTR_ENABLE_BMSK                                           0x200
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_SEC_CTRL_APU_XPU_SP_INTR_ENABLE_SHFT                                             0x9
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_DCC_XPU_SP_INTR_ENABLE_BMSK                                                    0x100
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_DCC_XPU_SP_INTR_ENABLE_SHFT                                                      0x8
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_OCIMEM_RPU_SP_INTR_ENABLE_BMSK                                                  0x80
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_OCIMEM_RPU_SP_INTR_ENABLE_SHFT                                                   0x7
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_CRYPTO0_BAM_XPU_SP_INTR_ENABLE_BMSK                                             0x40
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_CRYPTO0_BAM_XPU_SP_INTR_ENABLE_SHFT                                              0x6
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_O_TCSR_MUTEX_SP_INTR_ENABLE_BMSK                                                0x20
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_O_TCSR_MUTEX_SP_INTR_ENABLE_SHFT                                                 0x5
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_APSS_SP_INTR_ENABLE_BMSK                                                        0x10
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_APSS_SP_INTR_ENABLE_SHFT                                                         0x4
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_O_TCSR_REGS_SP_INTR_ENABLE_BMSK                                                  0x8
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_O_TCSR_REGS_SP_INTR_ENABLE_SHFT                                                  0x3
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_MMSS_NOC_XPU_SP_INTR_ENABLE_BMSK                                                 0x4
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_MMSS_NOC_XPU_SP_INTR_ENABLE_SHFT                                                 0x2
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_RESERVE_1_BMSK                                                                   0x2
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_RESERVE_1_SHFT                                                                   0x1
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_MMSS_QM_XPU_SP_INTR_ENABLE_BMSK                                                  0x1
#define HWIO_TCSR_SS_XPU_SP_INTR0_ENABLE_MMSS_QM_XPU_SP_INTR_ENABLE_SHFT                                                  0x0

#define HWIO_TCSR_SS_XPU_SP_INTR1_ENABLE_ADDR                                                                      (TCSR_TCSR_REGS_REG_BASE      + 0x0002100c)
#define HWIO_TCSR_SS_XPU_SP_INTR1_ENABLE_RMSK                                                                         0x3ffff
#define HWIO_TCSR_SS_XPU_SP_INTR1_ENABLE_IN          \
        in_dword_masked(HWIO_TCSR_SS_XPU_SP_INTR1_ENABLE_ADDR, HWIO_TCSR_SS_XPU_SP_INTR1_ENABLE_RMSK)
#define HWIO_TCSR_SS_XPU_SP_INTR1_ENABLE_INM(m)      \
        in_dword_masked(HWIO_TCSR_SS_XPU_SP_INTR1_ENABLE_ADDR, m)
#define HWIO_TCSR_SS_XPU_SP_INTR1_ENABLE_OUT(v)      \
        out_dword(HWIO_TCSR_SS_XPU_SP_INTR1_ENABLE_ADDR,v)
#define HWIO_TCSR_SS_XPU_SP_INTR1_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_SS_XPU_SP_INTR1_ENABLE_ADDR,m,v,HWIO_TCSR_SS_XPU_SP_INTR1_ENABLE_IN)
#define HWIO_TCSR_SS_XPU_SP_INTR1_ENABLE_LPASS_IRQ_OUT_SECURITY_23_ENABLE_BMSK                                        0x20000
#define HWIO_TCSR_SS_XPU_SP_INTR1_ENABLE_LPASS_IRQ_OUT_SECURITY_23_ENABLE_SHFT                                           0x11
#define HWIO_TCSR_SS_XPU_SP_INTR1_ENABLE_MMSS_XPU_MMSS_CC_XPU_SP_INTR_ENABLE_BMSK                                     0x10000
#define HWIO_TCSR_SS_XPU_SP_INTR1_ENABLE_MMSS_XPU_MMSS_CC_XPU_SP_INTR_ENABLE_SHFT                                        0x10
#define HWIO_TCSR_SS_XPU_SP_INTR1_ENABLE_TLMM_NORTH_XPU_SP_INTR_ENABLE_BMSK                                            0x8000
#define HWIO_TCSR_SS_XPU_SP_INTR1_ENABLE_TLMM_NORTH_XPU_SP_INTR_ENABLE_SHFT                                               0xf
#define HWIO_TCSR_SS_XPU_SP_INTR1_ENABLE_SKL_XPU_SP_INTR_ENABLE_BMSK                                                   0x4000
#define HWIO_TCSR_SS_XPU_SP_INTR1_ENABLE_SKL_XPU_SP_INTR_ENABLE_SHFT                                                      0xe
#define HWIO_TCSR_SS_XPU_SP_INTR1_ENABLE_ANOC1_MPU_XPU_SP_INTR_ENABLE_BMSK                                             0x2000
#define HWIO_TCSR_SS_XPU_SP_INTR1_ENABLE_ANOC1_MPU_XPU_SP_INTR_ENABLE_SHFT                                                0xd
#define HWIO_TCSR_SS_XPU_SP_INTR1_ENABLE_ANOC2_MPU_XPU_SP_INTR_ENABLE_BMSK                                             0x1000
#define HWIO_TCSR_SS_XPU_SP_INTR1_ENABLE_ANOC2_MPU_XPU_SP_INTR_ENABLE_SHFT                                                0xc
#define HWIO_TCSR_SS_XPU_SP_INTR1_ENABLE_IPA_0_XPU_SP_INTR_ENABLE_BMSK                                                  0x800
#define HWIO_TCSR_SS_XPU_SP_INTR1_ENABLE_IPA_0_XPU_SP_INTR_ENABLE_SHFT                                                    0xb
#define HWIO_TCSR_SS_XPU_SP_INTR1_ENABLE_MSS_Q6_MPU_XPU_SP_INTR_ENABLE_BMSK                                             0x400
#define HWIO_TCSR_SS_XPU_SP_INTR1_ENABLE_MSS_Q6_MPU_XPU_SP_INTR_ENABLE_SHFT                                               0xa
#define HWIO_TCSR_SS_XPU_SP_INTR1_ENABLE_RPM_MPU_SP_INTR_ENABLE_BMSK                                                    0x200
#define HWIO_TCSR_SS_XPU_SP_INTR1_ENABLE_RPM_MPU_SP_INTR_ENABLE_SHFT                                                      0x9
#define HWIO_TCSR_SS_XPU_SP_INTR1_ENABLE_LPASS_IRQ_OUT_SECURITY_21_ENABLE_BMSK                                          0x100
#define HWIO_TCSR_SS_XPU_SP_INTR1_ENABLE_LPASS_IRQ_OUT_SECURITY_21_ENABLE_SHFT                                            0x8
#define HWIO_TCSR_SS_XPU_SP_INTR1_ENABLE_MDSS_XPU_XPU_SP_INTR_ENABLE_BMSK                                                0x80
#define HWIO_TCSR_SS_XPU_SP_INTR1_ENABLE_MDSS_XPU_XPU_SP_INTR_ENABLE_SHFT                                                 0x7
#define HWIO_TCSR_SS_XPU_SP_INTR1_ENABLE_QDSS_BAM_XPU_SP_INTR_ENABLE_BMSK                                                0x40
#define HWIO_TCSR_SS_XPU_SP_INTR1_ENABLE_QDSS_BAM_XPU_SP_INTR_ENABLE_SHFT                                                 0x6
#define HWIO_TCSR_SS_XPU_SP_INTR1_ENABLE_MPM2_XPU_SP_INTR_ENABLE_BMSK                                                    0x20
#define HWIO_TCSR_SS_XPU_SP_INTR1_ENABLE_MPM2_XPU_SP_INTR_ENABLE_SHFT                                                     0x5
#define HWIO_TCSR_SS_XPU_SP_INTR1_ENABLE_DDR_REGS_CFG_XPU_SP_INTR_ENABLE_BMSK                                            0x10
#define HWIO_TCSR_SS_XPU_SP_INTR1_ENABLE_DDR_REGS_CFG_XPU_SP_INTR_ENABLE_SHFT                                             0x4
#define HWIO_TCSR_SS_XPU_SP_INTR1_ENABLE_TLMM_SOUTH_XPU_SP_INTR_ENABLE_BMSK                                               0x8
#define HWIO_TCSR_SS_XPU_SP_INTR1_ENABLE_TLMM_SOUTH_XPU_SP_INTR_ENABLE_SHFT                                               0x3
#define HWIO_TCSR_SS_XPU_SP_INTR1_ENABLE_PERIPH_SS_BLSP2_BLSP_BAM_XPU_SP_INTR_ENABLE_BMSK                                 0x4
#define HWIO_TCSR_SS_XPU_SP_INTR1_ENABLE_PERIPH_SS_BLSP2_BLSP_BAM_XPU_SP_INTR_ENABLE_SHFT                                 0x2
#define HWIO_TCSR_SS_XPU_SP_INTR1_ENABLE_PERIPH_SS_BLSP1_BLSP_BAM_XPU_SP_INTR_ENABLE_BMSK                                 0x2
#define HWIO_TCSR_SS_XPU_SP_INTR1_ENABLE_PERIPH_SS_BLSP1_BLSP_BAM_XPU_SP_INTR_ENABLE_SHFT                                 0x1
#define HWIO_TCSR_SS_XPU_SP_INTR1_ENABLE_OCIMEM_RPU_SP_INTR_ENABLE_BMSK                                                   0x1
#define HWIO_TCSR_SS_XPU_SP_INTR1_ENABLE_OCIMEM_RPU_SP_INTR_ENABLE_SHFT                                                   0x0

#define HWIO_TCSR_PHSS_UART_SP_INT_SEL_n_ADDR(n)                                                                   (TCSR_TCSR_REGS_REG_BASE      + 0x00021010 + 0x4 * (n))
#define HWIO_TCSR_PHSS_UART_SP_INT_SEL_n_RMSK                                                                           0xfff
#define HWIO_TCSR_PHSS_UART_SP_INT_SEL_n_MAXn                                                                               1
#define HWIO_TCSR_PHSS_UART_SP_INT_SEL_n_INI(n)        \
        in_dword_masked(HWIO_TCSR_PHSS_UART_SP_INT_SEL_n_ADDR(n), HWIO_TCSR_PHSS_UART_SP_INT_SEL_n_RMSK)
#define HWIO_TCSR_PHSS_UART_SP_INT_SEL_n_INMI(n,mask)    \
        in_dword_masked(HWIO_TCSR_PHSS_UART_SP_INT_SEL_n_ADDR(n), mask)
#define HWIO_TCSR_PHSS_UART_SP_INT_SEL_n_OUTI(n,val)    \
        out_dword(HWIO_TCSR_PHSS_UART_SP_INT_SEL_n_ADDR(n),val)
#define HWIO_TCSR_PHSS_UART_SP_INT_SEL_n_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TCSR_PHSS_UART_SP_INT_SEL_n_ADDR(n),mask,val,HWIO_TCSR_PHSS_UART_SP_INT_SEL_n_INI(n))
#define HWIO_TCSR_PHSS_UART_SP_INT_SEL_n_SP_BLSP_UART_IRQ_ENABLE_BMSK                                                   0xfff
#define HWIO_TCSR_PHSS_UART_SP_INT_SEL_n_SP_BLSP_UART_IRQ_ENABLE_SHFT                                                     0x0

#define HWIO_TCSR_PHSS_QUP_SP_INT_SEL_n_ADDR(n)                                                                    (TCSR_TCSR_REGS_REG_BASE      + 0x00021018 + 0x4 * (n))
#define HWIO_TCSR_PHSS_QUP_SP_INT_SEL_n_RMSK                                                                            0xfff
#define HWIO_TCSR_PHSS_QUP_SP_INT_SEL_n_MAXn                                                                                1
#define HWIO_TCSR_PHSS_QUP_SP_INT_SEL_n_INI(n)        \
        in_dword_masked(HWIO_TCSR_PHSS_QUP_SP_INT_SEL_n_ADDR(n), HWIO_TCSR_PHSS_QUP_SP_INT_SEL_n_RMSK)
#define HWIO_TCSR_PHSS_QUP_SP_INT_SEL_n_INMI(n,mask)    \
        in_dword_masked(HWIO_TCSR_PHSS_QUP_SP_INT_SEL_n_ADDR(n), mask)
#define HWIO_TCSR_PHSS_QUP_SP_INT_SEL_n_OUTI(n,val)    \
        out_dword(HWIO_TCSR_PHSS_QUP_SP_INT_SEL_n_ADDR(n),val)
#define HWIO_TCSR_PHSS_QUP_SP_INT_SEL_n_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TCSR_PHSS_QUP_SP_INT_SEL_n_ADDR(n),mask,val,HWIO_TCSR_PHSS_QUP_SP_INT_SEL_n_INI(n))
#define HWIO_TCSR_PHSS_QUP_SP_INT_SEL_n_SP_BLSP_QUP_IRQ_ENABLE_BMSK                                                     0xfff
#define HWIO_TCSR_PHSS_QUP_SP_INT_SEL_n_SP_BLSP_QUP_IRQ_ENABLE_SHFT                                                       0x0

#define HWIO_TCSR_MBIST_COMPILER_ACC_ADDR                                                                          (TCSR_TCSR_REGS_REG_BASE      + 0x00022000)
#define HWIO_TCSR_MBIST_COMPILER_ACC_RMSK                                                                               0x1ff
#define HWIO_TCSR_MBIST_COMPILER_ACC_IN          \
        in_dword_masked(HWIO_TCSR_MBIST_COMPILER_ACC_ADDR, HWIO_TCSR_MBIST_COMPILER_ACC_RMSK)
#define HWIO_TCSR_MBIST_COMPILER_ACC_INM(m)      \
        in_dword_masked(HWIO_TCSR_MBIST_COMPILER_ACC_ADDR, m)
#define HWIO_TCSR_MBIST_COMPILER_ACC_OUT(v)      \
        out_dword(HWIO_TCSR_MBIST_COMPILER_ACC_ADDR,v)
#define HWIO_TCSR_MBIST_COMPILER_ACC_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_MBIST_COMPILER_ACC_ADDR,m,v,HWIO_TCSR_MBIST_COMPILER_ACC_IN)
#define HWIO_TCSR_MBIST_COMPILER_ACC_MBIST_COMPILER_ACC_BMSK                                                            0x1ff
#define HWIO_TCSR_MBIST_COMPILER_ACC_MBIST_COMPILER_ACC_SHFT                                                              0x0

#define HWIO_TCSR_MBIST_CUSTOM_ACC_ADDR                                                                            (TCSR_TCSR_REGS_REG_BASE      + 0x00022004)
#define HWIO_TCSR_MBIST_CUSTOM_ACC_RMSK                                                                                 0x1ff
#define HWIO_TCSR_MBIST_CUSTOM_ACC_IN          \
        in_dword_masked(HWIO_TCSR_MBIST_CUSTOM_ACC_ADDR, HWIO_TCSR_MBIST_CUSTOM_ACC_RMSK)
#define HWIO_TCSR_MBIST_CUSTOM_ACC_INM(m)      \
        in_dword_masked(HWIO_TCSR_MBIST_CUSTOM_ACC_ADDR, m)
#define HWIO_TCSR_MBIST_CUSTOM_ACC_OUT(v)      \
        out_dword(HWIO_TCSR_MBIST_CUSTOM_ACC_ADDR,v)
#define HWIO_TCSR_MBIST_CUSTOM_ACC_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_MBIST_CUSTOM_ACC_ADDR,m,v,HWIO_TCSR_MBIST_CUSTOM_ACC_IN)
#define HWIO_TCSR_MBIST_CUSTOM_ACC_MBIST_CUSTOM_ACC_BMSK                                                                0x1ff
#define HWIO_TCSR_MBIST_CUSTOM_ACC_MBIST_CUSTOM_ACC_SHFT                                                                  0x0

#define HWIO_TCSR_A1NOC_BYPASS_CHECKTYPE_ADDR                                                                      (TCSR_TCSR_REGS_REG_BASE      + 0x00023000)
#define HWIO_TCSR_A1NOC_BYPASS_CHECKTYPE_RMSK                                                                             0x3
#define HWIO_TCSR_A1NOC_BYPASS_CHECKTYPE_IN          \
        in_dword_masked(HWIO_TCSR_A1NOC_BYPASS_CHECKTYPE_ADDR, HWIO_TCSR_A1NOC_BYPASS_CHECKTYPE_RMSK)
#define HWIO_TCSR_A1NOC_BYPASS_CHECKTYPE_INM(m)      \
        in_dword_masked(HWIO_TCSR_A1NOC_BYPASS_CHECKTYPE_ADDR, m)
#define HWIO_TCSR_A1NOC_BYPASS_CHECKTYPE_OUT(v)      \
        out_dword(HWIO_TCSR_A1NOC_BYPASS_CHECKTYPE_ADDR,v)
#define HWIO_TCSR_A1NOC_BYPASS_CHECKTYPE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_A1NOC_BYPASS_CHECKTYPE_ADDR,m,v,HWIO_TCSR_A1NOC_BYPASS_CHECKTYPE_IN)
#define HWIO_TCSR_A1NOC_BYPASS_CHECKTYPE_A1NOC_SP_BYPASS_CHECK_TYPE_BMSK                                                  0x2
#define HWIO_TCSR_A1NOC_BYPASS_CHECKTYPE_A1NOC_SP_BYPASS_CHECK_TYPE_SHFT                                                  0x1
#define HWIO_TCSR_A1NOC_BYPASS_CHECKTYPE_A1NOC_MSA_BYPASS_CHECK_TYPE_BMSK                                                 0x1
#define HWIO_TCSR_A1NOC_BYPASS_CHECKTYPE_A1NOC_MSA_BYPASS_CHECK_TYPE_SHFT                                                 0x0

#define HWIO_TCSR_A2NOC_BYPASS_CHECKTYPE_ADDR                                                                      (TCSR_TCSR_REGS_REG_BASE      + 0x00023004)
#define HWIO_TCSR_A2NOC_BYPASS_CHECKTYPE_RMSK                                                                             0x3
#define HWIO_TCSR_A2NOC_BYPASS_CHECKTYPE_IN          \
        in_dword_masked(HWIO_TCSR_A2NOC_BYPASS_CHECKTYPE_ADDR, HWIO_TCSR_A2NOC_BYPASS_CHECKTYPE_RMSK)
#define HWIO_TCSR_A2NOC_BYPASS_CHECKTYPE_INM(m)      \
        in_dword_masked(HWIO_TCSR_A2NOC_BYPASS_CHECKTYPE_ADDR, m)
#define HWIO_TCSR_A2NOC_BYPASS_CHECKTYPE_OUT(v)      \
        out_dword(HWIO_TCSR_A2NOC_BYPASS_CHECKTYPE_ADDR,v)
#define HWIO_TCSR_A2NOC_BYPASS_CHECKTYPE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_A2NOC_BYPASS_CHECKTYPE_ADDR,m,v,HWIO_TCSR_A2NOC_BYPASS_CHECKTYPE_IN)
#define HWIO_TCSR_A2NOC_BYPASS_CHECKTYPE_A2NOC_SP_BYPASS_CHECK_TYPE_BMSK                                                  0x2
#define HWIO_TCSR_A2NOC_BYPASS_CHECKTYPE_A2NOC_SP_BYPASS_CHECK_TYPE_SHFT                                                  0x1
#define HWIO_TCSR_A2NOC_BYPASS_CHECKTYPE_A2NOC_MSA_BYPASS_CHECK_TYPE_BMSK                                                 0x1
#define HWIO_TCSR_A2NOC_BYPASS_CHECKTYPE_A2NOC_MSA_BYPASS_CHECK_TYPE_SHFT                                                 0x0

#define HWIO_TCSR_WCSS_TESTBUS_SEL_ADDR                                                                            (TCSR_TCSR_REGS_REG_BASE      + 0x00024000)
#define HWIO_TCSR_WCSS_TESTBUS_SEL_RMSK                                                                                  0xff
#define HWIO_TCSR_WCSS_TESTBUS_SEL_IN          \
        in_dword_masked(HWIO_TCSR_WCSS_TESTBUS_SEL_ADDR, HWIO_TCSR_WCSS_TESTBUS_SEL_RMSK)
#define HWIO_TCSR_WCSS_TESTBUS_SEL_INM(m)      \
        in_dword_masked(HWIO_TCSR_WCSS_TESTBUS_SEL_ADDR, m)
#define HWIO_TCSR_WCSS_TESTBUS_SEL_OUT(v)      \
        out_dword(HWIO_TCSR_WCSS_TESTBUS_SEL_ADDR,v)
#define HWIO_TCSR_WCSS_TESTBUS_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_WCSS_TESTBUS_SEL_ADDR,m,v,HWIO_TCSR_WCSS_TESTBUS_SEL_IN)
#define HWIO_TCSR_WCSS_TESTBUS_SEL_WCSS_TESTBUS_SEL_BMSK                                                                 0xff
#define HWIO_TCSR_WCSS_TESTBUS_SEL_WCSS_TESTBUS_SEL_SHFT                                                                  0x0

#define HWIO_TCSR_WCSS_AHBBM_CTRL_ADDR                                                                             (TCSR_TCSR_REGS_REG_BASE      + 0x00024004)
#define HWIO_TCSR_WCSS_AHBBM_CTRL_RMSK                                                                                    0x7
#define HWIO_TCSR_WCSS_AHBBM_CTRL_IN          \
        in_dword_masked(HWIO_TCSR_WCSS_AHBBM_CTRL_ADDR, HWIO_TCSR_WCSS_AHBBM_CTRL_RMSK)
#define HWIO_TCSR_WCSS_AHBBM_CTRL_INM(m)      \
        in_dword_masked(HWIO_TCSR_WCSS_AHBBM_CTRL_ADDR, m)
#define HWIO_TCSR_WCSS_AHBBM_CTRL_OUT(v)      \
        out_dword(HWIO_TCSR_WCSS_AHBBM_CTRL_ADDR,v)
#define HWIO_TCSR_WCSS_AHBBM_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_WCSS_AHBBM_CTRL_ADDR,m,v,HWIO_TCSR_WCSS_AHBBM_CTRL_IN)
#define HWIO_TCSR_WCSS_AHBBM_CTRL_AHBBM_SOFT_RESET_BMSK                                                                   0x4
#define HWIO_TCSR_WCSS_AHBBM_CTRL_AHBBM_SOFT_RESET_SHFT                                                                   0x2
#define HWIO_TCSR_WCSS_AHBBM_CTRL_AHBBM_CLKGATE_DISABLE_BMSK                                                              0x2
#define HWIO_TCSR_WCSS_AHBBM_CTRL_AHBBM_CLKGATE_DISABLE_SHFT                                                              0x1
#define HWIO_TCSR_WCSS_AHBBM_CTRL_AHBBM_ROOT_CLK_ENABLE_BMSK                                                              0x1
#define HWIO_TCSR_WCSS_AHBBM_CTRL_AHBBM_ROOT_CLK_ENABLE_SHFT                                                              0x0

#define HWIO_TCSR_MEM_SVS_SEL_APC0_ADDR                                                                            (TCSR_TCSR_REGS_REG_BASE      + 0x00025000)
#define HWIO_TCSR_MEM_SVS_SEL_APC0_RMSK                                                                                   0x1
#define HWIO_TCSR_MEM_SVS_SEL_APC0_IN          \
        in_dword_masked(HWIO_TCSR_MEM_SVS_SEL_APC0_ADDR, HWIO_TCSR_MEM_SVS_SEL_APC0_RMSK)
#define HWIO_TCSR_MEM_SVS_SEL_APC0_INM(m)      \
        in_dword_masked(HWIO_TCSR_MEM_SVS_SEL_APC0_ADDR, m)
#define HWIO_TCSR_MEM_SVS_SEL_APC0_OUT(v)      \
        out_dword(HWIO_TCSR_MEM_SVS_SEL_APC0_ADDR,v)
#define HWIO_TCSR_MEM_SVS_SEL_APC0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_MEM_SVS_SEL_APC0_ADDR,m,v,HWIO_TCSR_MEM_SVS_SEL_APC0_IN)
#define HWIO_TCSR_MEM_SVS_SEL_APC0_MEM_SVS_SEL_APC0_BMSK                                                                  0x1
#define HWIO_TCSR_MEM_SVS_SEL_APC0_MEM_SVS_SEL_APC0_SHFT                                                                  0x0

#define HWIO_TCSR_MEM_SVS_SEL_APC1_ADDR                                                                            (TCSR_TCSR_REGS_REG_BASE      + 0x00025004)
#define HWIO_TCSR_MEM_SVS_SEL_APC1_RMSK                                                                                   0x1
#define HWIO_TCSR_MEM_SVS_SEL_APC1_IN          \
        in_dword_masked(HWIO_TCSR_MEM_SVS_SEL_APC1_ADDR, HWIO_TCSR_MEM_SVS_SEL_APC1_RMSK)
#define HWIO_TCSR_MEM_SVS_SEL_APC1_INM(m)      \
        in_dword_masked(HWIO_TCSR_MEM_SVS_SEL_APC1_ADDR, m)
#define HWIO_TCSR_MEM_SVS_SEL_APC1_OUT(v)      \
        out_dword(HWIO_TCSR_MEM_SVS_SEL_APC1_ADDR,v)
#define HWIO_TCSR_MEM_SVS_SEL_APC1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_MEM_SVS_SEL_APC1_ADDR,m,v,HWIO_TCSR_MEM_SVS_SEL_APC1_IN)
#define HWIO_TCSR_MEM_SVS_SEL_APC1_MEM_SVS_SEL_APC1_BMSK                                                                  0x1
#define HWIO_TCSR_MEM_SVS_SEL_APC1_MEM_SVS_SEL_APC1_SHFT                                                                  0x0

#define HWIO_TCSR_KRYO_MUX_SEL_ADDR                                                                                (TCSR_TCSR_REGS_REG_BASE      + 0x00025008)
#define HWIO_TCSR_KRYO_MUX_SEL_RMSK                                                                                       0x3
#define HWIO_TCSR_KRYO_MUX_SEL_IN          \
        in_dword_masked(HWIO_TCSR_KRYO_MUX_SEL_ADDR, HWIO_TCSR_KRYO_MUX_SEL_RMSK)
#define HWIO_TCSR_KRYO_MUX_SEL_INM(m)      \
        in_dword_masked(HWIO_TCSR_KRYO_MUX_SEL_ADDR, m)
#define HWIO_TCSR_KRYO_MUX_SEL_OUT(v)      \
        out_dword(HWIO_TCSR_KRYO_MUX_SEL_ADDR,v)
#define HWIO_TCSR_KRYO_MUX_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_KRYO_MUX_SEL_ADDR,m,v,HWIO_TCSR_KRYO_MUX_SEL_IN)
#define HWIO_TCSR_KRYO_MUX_SEL_KRYO_MUX_SEL_BMSK                                                                          0x3
#define HWIO_TCSR_KRYO_MUX_SEL_KRYO_MUX_SEL_SHFT                                                                          0x0

#define HWIO_TCSR_APSS_BHS_EN_ADDR                                                                                 (TCSR_TCSR_REGS_REG_BASE      + 0x0002500c)
#define HWIO_TCSR_APSS_BHS_EN_RMSK                                                                                       0xff
#define HWIO_TCSR_APSS_BHS_EN_IN          \
        in_dword_masked(HWIO_TCSR_APSS_BHS_EN_ADDR, HWIO_TCSR_APSS_BHS_EN_RMSK)
#define HWIO_TCSR_APSS_BHS_EN_INM(m)      \
        in_dword_masked(HWIO_TCSR_APSS_BHS_EN_ADDR, m)
#define HWIO_TCSR_APSS_BHS_EN_OUT(v)      \
        out_dword(HWIO_TCSR_APSS_BHS_EN_ADDR,v)
#define HWIO_TCSR_APSS_BHS_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_APSS_BHS_EN_ADDR,m,v,HWIO_TCSR_APSS_BHS_EN_IN)
#define HWIO_TCSR_APSS_BHS_EN_APSS_BHS_EN_BMSK                                                                           0xff
#define HWIO_TCSR_APSS_BHS_EN_APSS_BHS_EN_SHFT                                                                            0x0

#define HWIO_TCSR_APSS_BHS_EN_STATUS_ADDR                                                                          (TCSR_TCSR_REGS_REG_BASE      + 0x00025010)
#define HWIO_TCSR_APSS_BHS_EN_STATUS_RMSK                                                                                0xff
#define HWIO_TCSR_APSS_BHS_EN_STATUS_IN          \
        in_dword_masked(HWIO_TCSR_APSS_BHS_EN_STATUS_ADDR, HWIO_TCSR_APSS_BHS_EN_STATUS_RMSK)
#define HWIO_TCSR_APSS_BHS_EN_STATUS_INM(m)      \
        in_dword_masked(HWIO_TCSR_APSS_BHS_EN_STATUS_ADDR, m)
#define HWIO_TCSR_APSS_BHS_EN_STATUS_APSS_BHS_EN_STATUS_BMSK                                                             0xff
#define HWIO_TCSR_APSS_BHS_EN_STATUS_APSS_BHS_EN_STATUS_SHFT                                                              0x0

#define HWIO_TCSR_APSS_SPARE_REG0_ADDR                                                                             (TCSR_TCSR_REGS_REG_BASE      + 0x00025014)
#define HWIO_TCSR_APSS_SPARE_REG0_RMSK                                                                             0xffffffff
#define HWIO_TCSR_APSS_SPARE_REG0_IN          \
        in_dword_masked(HWIO_TCSR_APSS_SPARE_REG0_ADDR, HWIO_TCSR_APSS_SPARE_REG0_RMSK)
#define HWIO_TCSR_APSS_SPARE_REG0_INM(m)      \
        in_dword_masked(HWIO_TCSR_APSS_SPARE_REG0_ADDR, m)
#define HWIO_TCSR_APSS_SPARE_REG0_OUT(v)      \
        out_dword(HWIO_TCSR_APSS_SPARE_REG0_ADDR,v)
#define HWIO_TCSR_APSS_SPARE_REG0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_APSS_SPARE_REG0_ADDR,m,v,HWIO_TCSR_APSS_SPARE_REG0_IN)
#define HWIO_TCSR_APSS_SPARE_REG0_SPARE_REG0_BMSK                                                                  0xffffffff
#define HWIO_TCSR_APSS_SPARE_REG0_SPARE_REG0_SHFT                                                                         0x0

#define HWIO_TCSR_APSS_SPARE_REG1_ADDR                                                                             (TCSR_TCSR_REGS_REG_BASE      + 0x00025018)
#define HWIO_TCSR_APSS_SPARE_REG1_RMSK                                                                             0xffffffff
#define HWIO_TCSR_APSS_SPARE_REG1_IN          \
        in_dword_masked(HWIO_TCSR_APSS_SPARE_REG1_ADDR, HWIO_TCSR_APSS_SPARE_REG1_RMSK)
#define HWIO_TCSR_APSS_SPARE_REG1_INM(m)      \
        in_dword_masked(HWIO_TCSR_APSS_SPARE_REG1_ADDR, m)
#define HWIO_TCSR_APSS_SPARE_REG1_OUT(v)      \
        out_dword(HWIO_TCSR_APSS_SPARE_REG1_ADDR,v)
#define HWIO_TCSR_APSS_SPARE_REG1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_APSS_SPARE_REG1_ADDR,m,v,HWIO_TCSR_APSS_SPARE_REG1_IN)
#define HWIO_TCSR_APSS_SPARE_REG1_SPARE_REG1_BMSK                                                                  0xffffffff
#define HWIO_TCSR_APSS_SPARE_REG1_SPARE_REG1_SHFT                                                                         0x0

#define HWIO_TCSR_APSS_SPARE_REG2_ADDR                                                                             (TCSR_TCSR_REGS_REG_BASE      + 0x0002501c)
#define HWIO_TCSR_APSS_SPARE_REG2_RMSK                                                                             0xffffffff
#define HWIO_TCSR_APSS_SPARE_REG2_IN          \
        in_dword_masked(HWIO_TCSR_APSS_SPARE_REG2_ADDR, HWIO_TCSR_APSS_SPARE_REG2_RMSK)
#define HWIO_TCSR_APSS_SPARE_REG2_INM(m)      \
        in_dword_masked(HWIO_TCSR_APSS_SPARE_REG2_ADDR, m)
#define HWIO_TCSR_APSS_SPARE_REG2_OUT(v)      \
        out_dword(HWIO_TCSR_APSS_SPARE_REG2_ADDR,v)
#define HWIO_TCSR_APSS_SPARE_REG2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_APSS_SPARE_REG2_ADDR,m,v,HWIO_TCSR_APSS_SPARE_REG2_IN)
#define HWIO_TCSR_APSS_SPARE_REG2_SPARE_REG2_BMSK                                                                  0xffffffff
#define HWIO_TCSR_APSS_SPARE_REG2_SPARE_REG2_SHFT                                                                         0x0

#define HWIO_TCSR_APSS_SPARE_REG3_ADDR                                                                             (TCSR_TCSR_REGS_REG_BASE      + 0x00025020)
#define HWIO_TCSR_APSS_SPARE_REG3_RMSK                                                                             0xffffffff
#define HWIO_TCSR_APSS_SPARE_REG3_IN          \
        in_dword_masked(HWIO_TCSR_APSS_SPARE_REG3_ADDR, HWIO_TCSR_APSS_SPARE_REG3_RMSK)
#define HWIO_TCSR_APSS_SPARE_REG3_INM(m)      \
        in_dword_masked(HWIO_TCSR_APSS_SPARE_REG3_ADDR, m)
#define HWIO_TCSR_APSS_SPARE_REG3_OUT(v)      \
        out_dword(HWIO_TCSR_APSS_SPARE_REG3_ADDR,v)
#define HWIO_TCSR_APSS_SPARE_REG3_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_APSS_SPARE_REG3_ADDR,m,v,HWIO_TCSR_APSS_SPARE_REG3_IN)
#define HWIO_TCSR_APSS_SPARE_REG3_SPARE_REG3_BMSK                                                                  0xffffffff
#define HWIO_TCSR_APSS_SPARE_REG3_SPARE_REG3_SHFT                                                                         0x0

#define HWIO_TCSR_APSS_SPARE_REG_RD_0_ADDR                                                                         (TCSR_TCSR_REGS_REG_BASE      + 0x00025024)
#define HWIO_TCSR_APSS_SPARE_REG_RD_0_RMSK                                                                         0xffffffff
#define HWIO_TCSR_APSS_SPARE_REG_RD_0_IN          \
        in_dword_masked(HWIO_TCSR_APSS_SPARE_REG_RD_0_ADDR, HWIO_TCSR_APSS_SPARE_REG_RD_0_RMSK)
#define HWIO_TCSR_APSS_SPARE_REG_RD_0_INM(m)      \
        in_dword_masked(HWIO_TCSR_APSS_SPARE_REG_RD_0_ADDR, m)
#define HWIO_TCSR_APSS_SPARE_REG_RD_0_SPARE_REG_RD_0_BMSK                                                          0xffffffff
#define HWIO_TCSR_APSS_SPARE_REG_RD_0_SPARE_REG_RD_0_SHFT                                                                 0x0

#define HWIO_TCSR_APC_SYSL2REQ_STATUS_ADDR                                                                         (TCSR_TCSR_REGS_REG_BASE      + 0x00025028)
#define HWIO_TCSR_APC_SYSL2REQ_STATUS_RMSK                                                                                0xf
#define HWIO_TCSR_APC_SYSL2REQ_STATUS_IN          \
        in_dword_masked(HWIO_TCSR_APC_SYSL2REQ_STATUS_ADDR, HWIO_TCSR_APC_SYSL2REQ_STATUS_RMSK)
#define HWIO_TCSR_APC_SYSL2REQ_STATUS_INM(m)      \
        in_dword_masked(HWIO_TCSR_APC_SYSL2REQ_STATUS_ADDR, m)
#define HWIO_TCSR_APC_SYSL2REQ_STATUS_APC0_SYSL2BRINGUPREQ_STATUS_BMSK                                                    0x8
#define HWIO_TCSR_APC_SYSL2REQ_STATUS_APC0_SYSL2BRINGUPREQ_STATUS_SHFT                                                    0x3
#define HWIO_TCSR_APC_SYSL2REQ_STATUS_APC1_SYSL2BRINGUPREQ_STATUS_BMSK                                                    0x4
#define HWIO_TCSR_APC_SYSL2REQ_STATUS_APC1_SYSL2BRINGUPREQ_STATUS_SHFT                                                    0x2
#define HWIO_TCSR_APC_SYSL2REQ_STATUS_APC0_SYSL2SHUTDOWNREQ_STATUS_BMSK                                                   0x2
#define HWIO_TCSR_APC_SYSL2REQ_STATUS_APC0_SYSL2SHUTDOWNREQ_STATUS_SHFT                                                   0x1
#define HWIO_TCSR_APC_SYSL2REQ_STATUS_APC1_SYSL2SHUTDOWNREQ_STATUS_BMSK                                                   0x1
#define HWIO_TCSR_APC_SYSL2REQ_STATUS_APC1_SYSL2SHUTDOWNREQ_STATUS_SHFT                                                   0x0

#define HWIO_TCSR_APC_SYSL2REQ_ENABLE_ADDR                                                                         (TCSR_TCSR_REGS_REG_BASE      + 0x00025030)
#define HWIO_TCSR_APC_SYSL2REQ_ENABLE_RMSK                                                                                0xf
#define HWIO_TCSR_APC_SYSL2REQ_ENABLE_IN          \
        in_dword_masked(HWIO_TCSR_APC_SYSL2REQ_ENABLE_ADDR, HWIO_TCSR_APC_SYSL2REQ_ENABLE_RMSK)
#define HWIO_TCSR_APC_SYSL2REQ_ENABLE_INM(m)      \
        in_dword_masked(HWIO_TCSR_APC_SYSL2REQ_ENABLE_ADDR, m)
#define HWIO_TCSR_APC_SYSL2REQ_ENABLE_OUT(v)      \
        out_dword(HWIO_TCSR_APC_SYSL2REQ_ENABLE_ADDR,v)
#define HWIO_TCSR_APC_SYSL2REQ_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_APC_SYSL2REQ_ENABLE_ADDR,m,v,HWIO_TCSR_APC_SYSL2REQ_ENABLE_IN)
#define HWIO_TCSR_APC_SYSL2REQ_ENABLE_APC0_SYSL2BRINGUPREQ_ENABLE_BMSK                                                    0x8
#define HWIO_TCSR_APC_SYSL2REQ_ENABLE_APC0_SYSL2BRINGUPREQ_ENABLE_SHFT                                                    0x3
#define HWIO_TCSR_APC_SYSL2REQ_ENABLE_APC1_SYSL2BRINGUPREQ_ENABLE_BMSK                                                    0x4
#define HWIO_TCSR_APC_SYSL2REQ_ENABLE_APC1_SYSL2BRINGUPREQ_ENABLE_SHFT                                                    0x2
#define HWIO_TCSR_APC_SYSL2REQ_ENABLE_APC0_SYSL2SHUTDOWNREQ_ENABLE_BMSK                                                   0x2
#define HWIO_TCSR_APC_SYSL2REQ_ENABLE_APC0_SYSL2SHUTDOWNREQ_ENABLE_SHFT                                                   0x1
#define HWIO_TCSR_APC_SYSL2REQ_ENABLE_APC1_SYSL2SHUTDOWNREQ_ENABLE_BMSK                                                   0x1
#define HWIO_TCSR_APC_SYSL2REQ_ENABLE_APC1_SYSL2SHUTDOWNREQ_ENABLE_SHFT                                                   0x0

#define HWIO_TCSR_QDSS_SUMMARY_IRQ_STATUS_ADDR                                                                     (TCSR_TCSR_REGS_REG_BASE      + 0x0002502c)
#define HWIO_TCSR_QDSS_SUMMARY_IRQ_STATUS_RMSK                                                                            0x7
#define HWIO_TCSR_QDSS_SUMMARY_IRQ_STATUS_IN          \
        in_dword_masked(HWIO_TCSR_QDSS_SUMMARY_IRQ_STATUS_ADDR, HWIO_TCSR_QDSS_SUMMARY_IRQ_STATUS_RMSK)
#define HWIO_TCSR_QDSS_SUMMARY_IRQ_STATUS_INM(m)      \
        in_dword_masked(HWIO_TCSR_QDSS_SUMMARY_IRQ_STATUS_ADDR, m)
#define HWIO_TCSR_QDSS_SUMMARY_IRQ_STATUS_QDSS_CLK_IRQ_STATUS_BMSK                                                        0x4
#define HWIO_TCSR_QDSS_SUMMARY_IRQ_STATUS_QDSS_CLK_IRQ_STATUS_SHFT                                                        0x2
#define HWIO_TCSR_QDSS_SUMMARY_IRQ_STATUS_QDSS_CSYSPWRUPREQ_STATUS_BMSK                                                   0x2
#define HWIO_TCSR_QDSS_SUMMARY_IRQ_STATUS_QDSS_CSYSPWRUPREQ_STATUS_SHFT                                                   0x1
#define HWIO_TCSR_QDSS_SUMMARY_IRQ_STATUS_QDSS_JTAGSW_STATUS_BMSK                                                         0x1
#define HWIO_TCSR_QDSS_SUMMARY_IRQ_STATUS_QDSS_JTAGSW_STATUS_SHFT                                                         0x0

#define HWIO_TCSR_QDSS_SUMMARY_IRQ_ENABLE_ADDR                                                                     (TCSR_TCSR_REGS_REG_BASE      + 0x00025034)
#define HWIO_TCSR_QDSS_SUMMARY_IRQ_ENABLE_RMSK                                                                            0x7
#define HWIO_TCSR_QDSS_SUMMARY_IRQ_ENABLE_IN          \
        in_dword_masked(HWIO_TCSR_QDSS_SUMMARY_IRQ_ENABLE_ADDR, HWIO_TCSR_QDSS_SUMMARY_IRQ_ENABLE_RMSK)
#define HWIO_TCSR_QDSS_SUMMARY_IRQ_ENABLE_INM(m)      \
        in_dword_masked(HWIO_TCSR_QDSS_SUMMARY_IRQ_ENABLE_ADDR, m)
#define HWIO_TCSR_QDSS_SUMMARY_IRQ_ENABLE_OUT(v)      \
        out_dword(HWIO_TCSR_QDSS_SUMMARY_IRQ_ENABLE_ADDR,v)
#define HWIO_TCSR_QDSS_SUMMARY_IRQ_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_QDSS_SUMMARY_IRQ_ENABLE_ADDR,m,v,HWIO_TCSR_QDSS_SUMMARY_IRQ_ENABLE_IN)
#define HWIO_TCSR_QDSS_SUMMARY_IRQ_ENABLE_QDSS_CLK_IRQ_ENABLE_BMSK                                                        0x4
#define HWIO_TCSR_QDSS_SUMMARY_IRQ_ENABLE_QDSS_CLK_IRQ_ENABLE_SHFT                                                        0x2
#define HWIO_TCSR_QDSS_SUMMARY_IRQ_ENABLE_QDSS_CSYSPWRUPREQ_ENABLE_BMSK                                                   0x2
#define HWIO_TCSR_QDSS_SUMMARY_IRQ_ENABLE_QDSS_CSYSPWRUPREQ_ENABLE_SHFT                                                   0x1
#define HWIO_TCSR_QDSS_SUMMARY_IRQ_ENABLE_QDSS_JTAGSW_ENABLE_BMSK                                                         0x1
#define HWIO_TCSR_QDSS_SUMMARY_IRQ_ENABLE_QDSS_JTAGSW_ENABLE_SHFT                                                         0x0

#define HWIO_TCSR_PMU_CTILE_CONFIG_ADDR                                                                            (TCSR_TCSR_REGS_REG_BASE      + 0x00025038)
#define HWIO_TCSR_PMU_CTILE_CONFIG_RMSK                                                                               0x1ffff
#define HWIO_TCSR_PMU_CTILE_CONFIG_IN          \
        in_dword_masked(HWIO_TCSR_PMU_CTILE_CONFIG_ADDR, HWIO_TCSR_PMU_CTILE_CONFIG_RMSK)
#define HWIO_TCSR_PMU_CTILE_CONFIG_INM(m)      \
        in_dword_masked(HWIO_TCSR_PMU_CTILE_CONFIG_ADDR, m)
#define HWIO_TCSR_PMU_CTILE_CONFIG_OUT(v)      \
        out_dword(HWIO_TCSR_PMU_CTILE_CONFIG_ADDR,v)
#define HWIO_TCSR_PMU_CTILE_CONFIG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_PMU_CTILE_CONFIG_ADDR,m,v,HWIO_TCSR_PMU_CTILE_CONFIG_IN)
#define HWIO_TCSR_PMU_CTILE_CONFIG_DISABLE_PMU_CLAMP_MEM_CX_BMSK                                                      0x10000
#define HWIO_TCSR_PMU_CTILE_CONFIG_DISABLE_PMU_CLAMP_MEM_CX_SHFT                                                         0x10
#define HWIO_TCSR_PMU_CTILE_CONFIG_PMU_DBG_BUS_EN_BMSK                                                                 0x8000
#define HWIO_TCSR_PMU_CTILE_CONFIG_PMU_DBG_BUS_EN_SHFT                                                                    0xf
#define HWIO_TCSR_PMU_CTILE_CONFIG_DISABLE_PMU_FREEZEIO_BMSK                                                           0x4000
#define HWIO_TCSR_PMU_CTILE_CONFIG_DISABLE_PMU_FREEZEIO_SHFT                                                              0xe
#define HWIO_TCSR_PMU_CTILE_CONFIG_DISABLE_PMU_PREFREEZEIO_BMSK                                                        0x2000
#define HWIO_TCSR_PMU_CTILE_CONFIG_DISABLE_PMU_PREFREEZEIO_SHFT                                                           0xd
#define HWIO_TCSR_PMU_CTILE_CONFIG_SW_OVERRIDE_SLEEP_CLK_DISABLE_BMSK                                                  0x1000
#define HWIO_TCSR_PMU_CTILE_CONFIG_SW_OVERRIDE_SLEEP_CLK_DISABLE_SHFT                                                     0xc
#define HWIO_TCSR_PMU_CTILE_CONFIG_SW_OVERRIDE_CXO_CLK_DISABLE_BMSK                                                     0x800
#define HWIO_TCSR_PMU_CTILE_CONFIG_SW_OVERRIDE_CXO_CLK_DISABLE_SHFT                                                       0xb
#define HWIO_TCSR_PMU_CTILE_CONFIG_MOCK_SHUTDOWN_BMSK                                                                   0x400
#define HWIO_TCSR_PMU_CTILE_CONFIG_MOCK_SHUTDOWN_SHFT                                                                     0xa
#define HWIO_TCSR_PMU_CTILE_CONFIG_DLY_PWRUP_RES_BMSK                                                                   0x3c0
#define HWIO_TCSR_PMU_CTILE_CONFIG_DLY_PWRUP_RES_SHFT                                                                     0x6
#define HWIO_TCSR_PMU_CTILE_CONFIG_DLY_PWRUP_FEW_BMSK                                                                    0x3c
#define HWIO_TCSR_PMU_CTILE_CONFIG_DLY_PWRUP_FEW_SHFT                                                                     0x2
#define HWIO_TCSR_PMU_CTILE_CONFIG_MPM_GATING_DIS_BMSK                                                                    0x2
#define HWIO_TCSR_PMU_CTILE_CONFIG_MPM_GATING_DIS_SHFT                                                                    0x1
#define HWIO_TCSR_PMU_CTILE_CONFIG_VDDCX_PC_EN_BMSK                                                                       0x1
#define HWIO_TCSR_PMU_CTILE_CONFIG_VDDCX_PC_EN_SHFT                                                                       0x0

#define HWIO_TCSR_PMU_CTILE_COLLAPSE_INDICATOR_ADDR                                                                (TCSR_TCSR_REGS_REG_BASE      + 0x0002503c)
#define HWIO_TCSR_PMU_CTILE_COLLAPSE_INDICATOR_RMSK                                                                       0x7
#define HWIO_TCSR_PMU_CTILE_COLLAPSE_INDICATOR_IN          \
        in_dword_masked(HWIO_TCSR_PMU_CTILE_COLLAPSE_INDICATOR_ADDR, HWIO_TCSR_PMU_CTILE_COLLAPSE_INDICATOR_RMSK)
#define HWIO_TCSR_PMU_CTILE_COLLAPSE_INDICATOR_INM(m)      \
        in_dword_masked(HWIO_TCSR_PMU_CTILE_COLLAPSE_INDICATOR_ADDR, m)
#define HWIO_TCSR_PMU_CTILE_COLLAPSE_INDICATOR_OUT(v)      \
        out_dword(HWIO_TCSR_PMU_CTILE_COLLAPSE_INDICATOR_ADDR,v)
#define HWIO_TCSR_PMU_CTILE_COLLAPSE_INDICATOR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_PMU_CTILE_COLLAPSE_INDICATOR_ADDR,m,v,HWIO_TCSR_PMU_CTILE_COLLAPSE_INDICATOR_IN)
#define HWIO_TCSR_PMU_CTILE_COLLAPSE_INDICATOR_CTILE_COLLAPSE_IND_HW_STAT_BMSK                                            0x4
#define HWIO_TCSR_PMU_CTILE_COLLAPSE_INDICATOR_CTILE_COLLAPSE_IND_HW_STAT_SHFT                                            0x2
#define HWIO_TCSR_PMU_CTILE_COLLAPSE_INDICATOR_CTILE_PWR_UP_IND_HW_STAT_BMSK                                              0x2
#define HWIO_TCSR_PMU_CTILE_COLLAPSE_INDICATOR_CTILE_PWR_UP_IND_HW_STAT_SHFT                                              0x1
#define HWIO_TCSR_PMU_CTILE_COLLAPSE_INDICATOR_CTILE_PWR_STATE_IND_SW_CLR_BMSK                                            0x1
#define HWIO_TCSR_PMU_CTILE_COLLAPSE_INDICATOR_CTILE_PWR_STATE_IND_SW_CLR_SHFT                                            0x0

#define HWIO_TCSR_CXIP_LM_VOTE_STATUS_ADDR                                                                         (TCSR_TCSR_REGS_REG_BASE      + 0x00025040)
#define HWIO_TCSR_CXIP_LM_VOTE_STATUS_RMSK                                                                             0xffff
#define HWIO_TCSR_CXIP_LM_VOTE_STATUS_IN          \
        in_dword_masked(HWIO_TCSR_CXIP_LM_VOTE_STATUS_ADDR, HWIO_TCSR_CXIP_LM_VOTE_STATUS_RMSK)
#define HWIO_TCSR_CXIP_LM_VOTE_STATUS_INM(m)      \
        in_dword_masked(HWIO_TCSR_CXIP_LM_VOTE_STATUS_ADDR, m)
#define HWIO_TCSR_CXIP_LM_VOTE_STATUS_CLIENT15_VOTE_STATUS_BMSK                                                        0x8000
#define HWIO_TCSR_CXIP_LM_VOTE_STATUS_CLIENT15_VOTE_STATUS_SHFT                                                           0xf
#define HWIO_TCSR_CXIP_LM_VOTE_STATUS_CLIENT14_VOTE_STATUS_BMSK                                                        0x4000
#define HWIO_TCSR_CXIP_LM_VOTE_STATUS_CLIENT14_VOTE_STATUS_SHFT                                                           0xe
#define HWIO_TCSR_CXIP_LM_VOTE_STATUS_CLIENT13_VOTE_STATUS_BMSK                                                        0x2000
#define HWIO_TCSR_CXIP_LM_VOTE_STATUS_CLIENT13_VOTE_STATUS_SHFT                                                           0xd
#define HWIO_TCSR_CXIP_LM_VOTE_STATUS_CLIENT12_VOTE_STATUS_BMSK                                                        0x1000
#define HWIO_TCSR_CXIP_LM_VOTE_STATUS_CLIENT12_VOTE_STATUS_SHFT                                                           0xc
#define HWIO_TCSR_CXIP_LM_VOTE_STATUS_CLIENT11_VOTE_STATUS_BMSK                                                         0x800
#define HWIO_TCSR_CXIP_LM_VOTE_STATUS_CLIENT11_VOTE_STATUS_SHFT                                                           0xb
#define HWIO_TCSR_CXIP_LM_VOTE_STATUS_CLIENT10_VOTE_STATUS_BMSK                                                         0x400
#define HWIO_TCSR_CXIP_LM_VOTE_STATUS_CLIENT10_VOTE_STATUS_SHFT                                                           0xa
#define HWIO_TCSR_CXIP_LM_VOTE_STATUS_CLIENT9_VOTE_STATUS_BMSK                                                          0x200
#define HWIO_TCSR_CXIP_LM_VOTE_STATUS_CLIENT9_VOTE_STATUS_SHFT                                                            0x9
#define HWIO_TCSR_CXIP_LM_VOTE_STATUS_CLIENT8_VOTE_STATUS_BMSK                                                          0x100
#define HWIO_TCSR_CXIP_LM_VOTE_STATUS_CLIENT8_VOTE_STATUS_SHFT                                                            0x8
#define HWIO_TCSR_CXIP_LM_VOTE_STATUS_CLIENT7_VOTE_STATUS_BMSK                                                           0x80
#define HWIO_TCSR_CXIP_LM_VOTE_STATUS_CLIENT7_VOTE_STATUS_SHFT                                                            0x7
#define HWIO_TCSR_CXIP_LM_VOTE_STATUS_CLIENT6_VOTE_STATUS_BMSK                                                           0x40
#define HWIO_TCSR_CXIP_LM_VOTE_STATUS_CLIENT6_VOTE_STATUS_SHFT                                                            0x6
#define HWIO_TCSR_CXIP_LM_VOTE_STATUS_CLIENT5_VOTE_STATUS_BMSK                                                           0x20
#define HWIO_TCSR_CXIP_LM_VOTE_STATUS_CLIENT5_VOTE_STATUS_SHFT                                                            0x5
#define HWIO_TCSR_CXIP_LM_VOTE_STATUS_CLIENT4_VOTE_STATUS_BMSK                                                           0x10
#define HWIO_TCSR_CXIP_LM_VOTE_STATUS_CLIENT4_VOTE_STATUS_SHFT                                                            0x4
#define HWIO_TCSR_CXIP_LM_VOTE_STATUS_CLIENT3_VOTE_STATUS_BMSK                                                            0x8
#define HWIO_TCSR_CXIP_LM_VOTE_STATUS_CLIENT3_VOTE_STATUS_SHFT                                                            0x3
#define HWIO_TCSR_CXIP_LM_VOTE_STATUS_CLIENT2_VOTE_STATUS_BMSK                                                            0x4
#define HWIO_TCSR_CXIP_LM_VOTE_STATUS_CLIENT2_VOTE_STATUS_SHFT                                                            0x2
#define HWIO_TCSR_CXIP_LM_VOTE_STATUS_CLIENT1_VOTE_STATUS_BMSK                                                            0x2
#define HWIO_TCSR_CXIP_LM_VOTE_STATUS_CLIENT1_VOTE_STATUS_SHFT                                                            0x1
#define HWIO_TCSR_CXIP_LM_VOTE_STATUS_CDSP_VOTE_STATUS_BMSK                                                               0x1
#define HWIO_TCSR_CXIP_LM_VOTE_STATUS_CDSP_VOTE_STATUS_SHFT                                                               0x0

#define HWIO_TCSR_CXIP_LM_VOTE_BYPASS_ADDR                                                                         (TCSR_TCSR_REGS_REG_BASE      + 0x00025044)
#define HWIO_TCSR_CXIP_LM_VOTE_BYPASS_RMSK                                                                             0xffff
#define HWIO_TCSR_CXIP_LM_VOTE_BYPASS_IN          \
        in_dword_masked(HWIO_TCSR_CXIP_LM_VOTE_BYPASS_ADDR, HWIO_TCSR_CXIP_LM_VOTE_BYPASS_RMSK)
#define HWIO_TCSR_CXIP_LM_VOTE_BYPASS_INM(m)      \
        in_dword_masked(HWIO_TCSR_CXIP_LM_VOTE_BYPASS_ADDR, m)
#define HWIO_TCSR_CXIP_LM_VOTE_BYPASS_OUT(v)      \
        out_dword(HWIO_TCSR_CXIP_LM_VOTE_BYPASS_ADDR,v)
#define HWIO_TCSR_CXIP_LM_VOTE_BYPASS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_CXIP_LM_VOTE_BYPASS_ADDR,m,v,HWIO_TCSR_CXIP_LM_VOTE_BYPASS_IN)
#define HWIO_TCSR_CXIP_LM_VOTE_BYPASS_CLIENT15_VOTE_BYPASS_BMSK                                                        0x8000
#define HWIO_TCSR_CXIP_LM_VOTE_BYPASS_CLIENT15_VOTE_BYPASS_SHFT                                                           0xf
#define HWIO_TCSR_CXIP_LM_VOTE_BYPASS_CLIENT14_VOTE_BYPASS_BMSK                                                        0x4000
#define HWIO_TCSR_CXIP_LM_VOTE_BYPASS_CLIENT14_VOTE_BYPASS_SHFT                                                           0xe
#define HWIO_TCSR_CXIP_LM_VOTE_BYPASS_CLIENT13_VOTE_BYPASS_BMSK                                                        0x2000
#define HWIO_TCSR_CXIP_LM_VOTE_BYPASS_CLIENT13_VOTE_BYPASS_SHFT                                                           0xd
#define HWIO_TCSR_CXIP_LM_VOTE_BYPASS_CLIENT12_VOTE_BYPASS_BMSK                                                        0x1000
#define HWIO_TCSR_CXIP_LM_VOTE_BYPASS_CLIENT12_VOTE_BYPASS_SHFT                                                           0xc
#define HWIO_TCSR_CXIP_LM_VOTE_BYPASS_CLIENT11_VOTE_BYPASS_BMSK                                                         0x800
#define HWIO_TCSR_CXIP_LM_VOTE_BYPASS_CLIENT11_VOTE_BYPASS_SHFT                                                           0xb
#define HWIO_TCSR_CXIP_LM_VOTE_BYPASS_CLIENT10_VOTE_BYPASS_BMSK                                                         0x400
#define HWIO_TCSR_CXIP_LM_VOTE_BYPASS_CLIENT10_VOTE_BYPASS_SHFT                                                           0xa
#define HWIO_TCSR_CXIP_LM_VOTE_BYPASS_CLIENT9_VOTE_BYPASS_BMSK                                                          0x200
#define HWIO_TCSR_CXIP_LM_VOTE_BYPASS_CLIENT9_VOTE_BYPASS_SHFT                                                            0x9
#define HWIO_TCSR_CXIP_LM_VOTE_BYPASS_CLIENT8_VOTE_BYPASS_BMSK                                                          0x100
#define HWIO_TCSR_CXIP_LM_VOTE_BYPASS_CLIENT8_VOTE_BYPASS_SHFT                                                            0x8
#define HWIO_TCSR_CXIP_LM_VOTE_BYPASS_CLIENT7_VOTE_BYPASS_BMSK                                                           0x80
#define HWIO_TCSR_CXIP_LM_VOTE_BYPASS_CLIENT7_VOTE_BYPASS_SHFT                                                            0x7
#define HWIO_TCSR_CXIP_LM_VOTE_BYPASS_CLIENT6_VOTE_BYPASS_BMSK                                                           0x40
#define HWIO_TCSR_CXIP_LM_VOTE_BYPASS_CLIENT6_VOTE_BYPASS_SHFT                                                            0x6
#define HWIO_TCSR_CXIP_LM_VOTE_BYPASS_CLIENT5_VOTE_BYPASS_BMSK                                                           0x20
#define HWIO_TCSR_CXIP_LM_VOTE_BYPASS_CLIENT5_VOTE_BYPASS_SHFT                                                            0x5
#define HWIO_TCSR_CXIP_LM_VOTE_BYPASS_CLIENT4_VOTE_BYPASS_BMSK                                                           0x10
#define HWIO_TCSR_CXIP_LM_VOTE_BYPASS_CLIENT4_VOTE_BYPASS_SHFT                                                            0x4
#define HWIO_TCSR_CXIP_LM_VOTE_BYPASS_CLIENT3_VOTE_BYPASS_BMSK                                                            0x8
#define HWIO_TCSR_CXIP_LM_VOTE_BYPASS_CLIENT3_VOTE_BYPASS_SHFT                                                            0x3
#define HWIO_TCSR_CXIP_LM_VOTE_BYPASS_CLIENT2_VOTE_BYPASS_BMSK                                                            0x4
#define HWIO_TCSR_CXIP_LM_VOTE_BYPASS_CLIENT2_VOTE_BYPASS_SHFT                                                            0x2
#define HWIO_TCSR_CXIP_LM_VOTE_BYPASS_CLIENT1_VOTE_BYPASS_BMSK                                                            0x2
#define HWIO_TCSR_CXIP_LM_VOTE_BYPASS_CLIENT1_VOTE_BYPASS_SHFT                                                            0x1
#define HWIO_TCSR_CXIP_LM_VOTE_BYPASS_CDSP_VOTE_BYPASS_BMSK                                                               0x1
#define HWIO_TCSR_CXIP_LM_VOTE_BYPASS_CDSP_VOTE_BYPASS_SHFT                                                               0x0

#define HWIO_TCSR_CXIP_LM_VOTE_CLEAR_ADDR                                                                          (TCSR_TCSR_REGS_REG_BASE      + 0x00025048)
#define HWIO_TCSR_CXIP_LM_VOTE_CLEAR_RMSK                                                                              0xffff
#define HWIO_TCSR_CXIP_LM_VOTE_CLEAR_OUT(v)      \
        out_dword(HWIO_TCSR_CXIP_LM_VOTE_CLEAR_ADDR,v)
#define HWIO_TCSR_CXIP_LM_VOTE_CLEAR_CLIENT15_VOTE_CLEAR_BMSK                                                          0x8000
#define HWIO_TCSR_CXIP_LM_VOTE_CLEAR_CLIENT15_VOTE_CLEAR_SHFT                                                             0xf
#define HWIO_TCSR_CXIP_LM_VOTE_CLEAR_CLIENT14_VOTE_CLEAR_BMSK                                                          0x4000
#define HWIO_TCSR_CXIP_LM_VOTE_CLEAR_CLIENT14_VOTE_CLEAR_SHFT                                                             0xe
#define HWIO_TCSR_CXIP_LM_VOTE_CLEAR_CLIENT13_VOTE_CLEAR_BMSK                                                          0x2000
#define HWIO_TCSR_CXIP_LM_VOTE_CLEAR_CLIENT13_VOTE_CLEAR_SHFT                                                             0xd
#define HWIO_TCSR_CXIP_LM_VOTE_CLEAR_CLIENT12_VOTE_CLEAR_BMSK                                                          0x1000
#define HWIO_TCSR_CXIP_LM_VOTE_CLEAR_CLIENT12_VOTE_CLEAR_SHFT                                                             0xc
#define HWIO_TCSR_CXIP_LM_VOTE_CLEAR_CLIENT11_VOTE_CLEAR_BMSK                                                           0x800
#define HWIO_TCSR_CXIP_LM_VOTE_CLEAR_CLIENT11_VOTE_CLEAR_SHFT                                                             0xb
#define HWIO_TCSR_CXIP_LM_VOTE_CLEAR_CLIENT10_VOTE_CLEAR_BMSK                                                           0x400
#define HWIO_TCSR_CXIP_LM_VOTE_CLEAR_CLIENT10_VOTE_CLEAR_SHFT                                                             0xa
#define HWIO_TCSR_CXIP_LM_VOTE_CLEAR_CLIENT9_VOTE_CLEAR_BMSK                                                            0x200
#define HWIO_TCSR_CXIP_LM_VOTE_CLEAR_CLIENT9_VOTE_CLEAR_SHFT                                                              0x9
#define HWIO_TCSR_CXIP_LM_VOTE_CLEAR_CLIENT8_VOTE_CLEAR_BMSK                                                            0x100
#define HWIO_TCSR_CXIP_LM_VOTE_CLEAR_CLIENT8_VOTE_CLEAR_SHFT                                                              0x8
#define HWIO_TCSR_CXIP_LM_VOTE_CLEAR_CLIENT7_VOTE_CLEAR_BMSK                                                             0x80
#define HWIO_TCSR_CXIP_LM_VOTE_CLEAR_CLIENT7_VOTE_CLEAR_SHFT                                                              0x7
#define HWIO_TCSR_CXIP_LM_VOTE_CLEAR_CLIENT6_VOTE_CLEAR_BMSK                                                             0x40
#define HWIO_TCSR_CXIP_LM_VOTE_CLEAR_CLIENT6_VOTE_CLEAR_SHFT                                                              0x6
#define HWIO_TCSR_CXIP_LM_VOTE_CLEAR_CLIENT5_VOTE_CLEAR_BMSK                                                             0x20
#define HWIO_TCSR_CXIP_LM_VOTE_CLEAR_CLIENT5_VOTE_CLEAR_SHFT                                                              0x5
#define HWIO_TCSR_CXIP_LM_VOTE_CLEAR_CLIENT4_VOTE_CLEAR_BMSK                                                             0x10
#define HWIO_TCSR_CXIP_LM_VOTE_CLEAR_CLIENT4_VOTE_CLEAR_SHFT                                                              0x4
#define HWIO_TCSR_CXIP_LM_VOTE_CLEAR_CLIENT3_VOTE_CLEAR_BMSK                                                              0x8
#define HWIO_TCSR_CXIP_LM_VOTE_CLEAR_CLIENT3_VOTE_CLEAR_SHFT                                                              0x3
#define HWIO_TCSR_CXIP_LM_VOTE_CLEAR_CLIENT2_VOTE_CLEAR_BMSK                                                              0x4
#define HWIO_TCSR_CXIP_LM_VOTE_CLEAR_CLIENT2_VOTE_CLEAR_SHFT                                                              0x2
#define HWIO_TCSR_CXIP_LM_VOTE_CLEAR_CLIENT1_VOTE_CLEAR_BMSK                                                              0x2
#define HWIO_TCSR_CXIP_LM_VOTE_CLEAR_CLIENT1_VOTE_CLEAR_SHFT                                                              0x1
#define HWIO_TCSR_CXIP_LM_VOTE_CLEAR_NOT_USED_BMSK                                                                        0x1
#define HWIO_TCSR_CXIP_LM_VOTE_CLEAR_NOT_USED_SHFT                                                                        0x0

#define HWIO_TCSR_CXIP_LM_VOTE_SET_ADDR                                                                            (TCSR_TCSR_REGS_REG_BASE      + 0x0002504c)
#define HWIO_TCSR_CXIP_LM_VOTE_SET_RMSK                                                                                0xffff
#define HWIO_TCSR_CXIP_LM_VOTE_SET_OUT(v)      \
        out_dword(HWIO_TCSR_CXIP_LM_VOTE_SET_ADDR,v)
#define HWIO_TCSR_CXIP_LM_VOTE_SET_CLIENT15_VOTE_SET_BMSK                                                              0x8000
#define HWIO_TCSR_CXIP_LM_VOTE_SET_CLIENT15_VOTE_SET_SHFT                                                                 0xf
#define HWIO_TCSR_CXIP_LM_VOTE_SET_CLIENT14_VOTE_SET_BMSK                                                              0x4000
#define HWIO_TCSR_CXIP_LM_VOTE_SET_CLIENT14_VOTE_SET_SHFT                                                                 0xe
#define HWIO_TCSR_CXIP_LM_VOTE_SET_CLIENT13_VOTE_SET_BMSK                                                              0x2000
#define HWIO_TCSR_CXIP_LM_VOTE_SET_CLIENT13_VOTE_SET_SHFT                                                                 0xd
#define HWIO_TCSR_CXIP_LM_VOTE_SET_CLIENT12_VOTE_SET_BMSK                                                              0x1000
#define HWIO_TCSR_CXIP_LM_VOTE_SET_CLIENT12_VOTE_SET_SHFT                                                                 0xc
#define HWIO_TCSR_CXIP_LM_VOTE_SET_CLIENT11_VOTE_SET_BMSK                                                               0x800
#define HWIO_TCSR_CXIP_LM_VOTE_SET_CLIENT11_VOTE_SET_SHFT                                                                 0xb
#define HWIO_TCSR_CXIP_LM_VOTE_SET_CLIENT10_VOTE_SET_BMSK                                                               0x400
#define HWIO_TCSR_CXIP_LM_VOTE_SET_CLIENT10_VOTE_SET_SHFT                                                                 0xa
#define HWIO_TCSR_CXIP_LM_VOTE_SET_CLIENT9_VOTE_SET_BMSK                                                                0x200
#define HWIO_TCSR_CXIP_LM_VOTE_SET_CLIENT9_VOTE_SET_SHFT                                                                  0x9
#define HWIO_TCSR_CXIP_LM_VOTE_SET_CLIENT8_VOTE_SET_BMSK                                                                0x100
#define HWIO_TCSR_CXIP_LM_VOTE_SET_CLIENT8_VOTE_SET_SHFT                                                                  0x8
#define HWIO_TCSR_CXIP_LM_VOTE_SET_CLIENT7_VOTE_SET_BMSK                                                                 0x80
#define HWIO_TCSR_CXIP_LM_VOTE_SET_CLIENT7_VOTE_SET_SHFT                                                                  0x7
#define HWIO_TCSR_CXIP_LM_VOTE_SET_CLIENT6_VOTE_SET_BMSK                                                                 0x40
#define HWIO_TCSR_CXIP_LM_VOTE_SET_CLIENT6_VOTE_SET_SHFT                                                                  0x6
#define HWIO_TCSR_CXIP_LM_VOTE_SET_CLIENT5_VOTE_SET_BMSK                                                                 0x20
#define HWIO_TCSR_CXIP_LM_VOTE_SET_CLIENT5_VOTE_SET_SHFT                                                                  0x5
#define HWIO_TCSR_CXIP_LM_VOTE_SET_CLIENT4_VOTE_SET_BMSK                                                                 0x10
#define HWIO_TCSR_CXIP_LM_VOTE_SET_CLIENT4_VOTE_SET_SHFT                                                                  0x4
#define HWIO_TCSR_CXIP_LM_VOTE_SET_CLIENT3_VOTE_SET_BMSK                                                                  0x8
#define HWIO_TCSR_CXIP_LM_VOTE_SET_CLIENT3_VOTE_SET_SHFT                                                                  0x3
#define HWIO_TCSR_CXIP_LM_VOTE_SET_CLIENT2_VOTE_SET_BMSK                                                                  0x4
#define HWIO_TCSR_CXIP_LM_VOTE_SET_CLIENT2_VOTE_SET_SHFT                                                                  0x2
#define HWIO_TCSR_CXIP_LM_VOTE_SET_CLIENT1_VOTE_SET_BMSK                                                                  0x2
#define HWIO_TCSR_CXIP_LM_VOTE_SET_CLIENT1_VOTE_SET_SHFT                                                                  0x1
#define HWIO_TCSR_CXIP_LM_VOTE_SET_NOT_USED_BMSK                                                                          0x1
#define HWIO_TCSR_CXIP_LM_VOTE_SET_NOT_USED_SHFT                                                                          0x0

#define HWIO_TCSR_CXIP_LM_VOTE_FEATURE_ENABLE_ADDR                                                                 (TCSR_TCSR_REGS_REG_BASE      + 0x00025050)
#define HWIO_TCSR_CXIP_LM_VOTE_FEATURE_ENABLE_RMSK                                                                        0x1
#define HWIO_TCSR_CXIP_LM_VOTE_FEATURE_ENABLE_IN          \
        in_dword_masked(HWIO_TCSR_CXIP_LM_VOTE_FEATURE_ENABLE_ADDR, HWIO_TCSR_CXIP_LM_VOTE_FEATURE_ENABLE_RMSK)
#define HWIO_TCSR_CXIP_LM_VOTE_FEATURE_ENABLE_INM(m)      \
        in_dword_masked(HWIO_TCSR_CXIP_LM_VOTE_FEATURE_ENABLE_ADDR, m)
#define HWIO_TCSR_CXIP_LM_VOTE_FEATURE_ENABLE_OUT(v)      \
        out_dword(HWIO_TCSR_CXIP_LM_VOTE_FEATURE_ENABLE_ADDR,v)
#define HWIO_TCSR_CXIP_LM_VOTE_FEATURE_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_CXIP_LM_VOTE_FEATURE_ENABLE_ADDR,m,v,HWIO_TCSR_CXIP_LM_VOTE_FEATURE_ENABLE_IN)
#define HWIO_TCSR_CXIP_LM_VOTE_FEATURE_ENABLE_VOTE_FEATURE_ENABLE_BMSK                                                    0x1
#define HWIO_TCSR_CXIP_LM_VOTE_FEATURE_ENABLE_VOTE_FEATURE_ENABLE_SHFT                                                    0x0

#define HWIO_TCSR_CXIP_LM_FNT_SET_ADDR                                                                             (TCSR_TCSR_REGS_REG_BASE      + 0x00025054)
#define HWIO_TCSR_CXIP_LM_FNT_SET_RMSK                                                                                    0x3
#define HWIO_TCSR_CXIP_LM_FNT_SET_OUT(v)      \
        out_dword(HWIO_TCSR_CXIP_LM_FNT_SET_ADDR,v)
#define HWIO_TCSR_CXIP_LM_FNT_SET_T_SET_BMSK                                                                              0x2
#define HWIO_TCSR_CXIP_LM_FNT_SET_T_SET_SHFT                                                                              0x1
#define HWIO_TCSR_CXIP_LM_FNT_SET_F_SET_BMSK                                                                              0x1
#define HWIO_TCSR_CXIP_LM_FNT_SET_F_SET_SHFT                                                                              0x0

#define HWIO_TCSR_CXIP_LM_FNT_CLEAR_ADDR                                                                           (TCSR_TCSR_REGS_REG_BASE      + 0x00025058)
#define HWIO_TCSR_CXIP_LM_FNT_CLEAR_RMSK                                                                                  0x3
#define HWIO_TCSR_CXIP_LM_FNT_CLEAR_OUT(v)      \
        out_dword(HWIO_TCSR_CXIP_LM_FNT_CLEAR_ADDR,v)
#define HWIO_TCSR_CXIP_LM_FNT_CLEAR_T_CLEAR_BMSK                                                                          0x2
#define HWIO_TCSR_CXIP_LM_FNT_CLEAR_T_CLEAR_SHFT                                                                          0x1
#define HWIO_TCSR_CXIP_LM_FNT_CLEAR_F_CLEAR_BMSK                                                                          0x1
#define HWIO_TCSR_CXIP_LM_FNT_CLEAR_F_CLEAR_SHFT                                                                          0x0

#define HWIO_TCSR_CXIP_LM_FNT_STATUS_ADDR                                                                          (TCSR_TCSR_REGS_REG_BASE      + 0x0002505c)
#define HWIO_TCSR_CXIP_LM_FNT_STATUS_RMSK                                                                                 0x3
#define HWIO_TCSR_CXIP_LM_FNT_STATUS_IN          \
        in_dword_masked(HWIO_TCSR_CXIP_LM_FNT_STATUS_ADDR, HWIO_TCSR_CXIP_LM_FNT_STATUS_RMSK)
#define HWIO_TCSR_CXIP_LM_FNT_STATUS_INM(m)      \
        in_dword_masked(HWIO_TCSR_CXIP_LM_FNT_STATUS_ADDR, m)
#define HWIO_TCSR_CXIP_LM_FNT_STATUS_T_STATUS_BMSK                                                                        0x2
#define HWIO_TCSR_CXIP_LM_FNT_STATUS_T_STATUS_SHFT                                                                        0x1
#define HWIO_TCSR_CXIP_LM_FNT_STATUS_F_STATUS_BMSK                                                                        0x1
#define HWIO_TCSR_CXIP_LM_FNT_STATUS_F_STATUS_SHFT                                                                        0x0

#define HWIO_TCSR_CXIP_LM_ACVS_ADDR                                                                                (TCSR_TCSR_REGS_REG_BASE      + 0x00025060)
#define HWIO_TCSR_CXIP_LM_ACVS_RMSK                                                                                       0x1
#define HWIO_TCSR_CXIP_LM_ACVS_IN          \
        in_dword_masked(HWIO_TCSR_CXIP_LM_ACVS_ADDR, HWIO_TCSR_CXIP_LM_ACVS_RMSK)
#define HWIO_TCSR_CXIP_LM_ACVS_INM(m)      \
        in_dword_masked(HWIO_TCSR_CXIP_LM_ACVS_ADDR, m)
#define HWIO_TCSR_CXIP_LM_ACVS_ACVS_BMSK                                                                                  0x1
#define HWIO_TCSR_CXIP_LM_ACVS_ACVS_SHFT                                                                                  0x0

#define HWIO_TCSR_CXIP_LM_TRS_ADDR                                                                                 (TCSR_TCSR_REGS_REG_BASE      + 0x00025064)
#define HWIO_TCSR_CXIP_LM_TRS_RMSK                                                                                        0x1
#define HWIO_TCSR_CXIP_LM_TRS_IN          \
        in_dword_masked(HWIO_TCSR_CXIP_LM_TRS_ADDR, HWIO_TCSR_CXIP_LM_TRS_RMSK)
#define HWIO_TCSR_CXIP_LM_TRS_INM(m)      \
        in_dword_masked(HWIO_TCSR_CXIP_LM_TRS_ADDR, m)
#define HWIO_TCSR_CXIP_LM_TRS_TRS_BMSK                                                                                    0x1
#define HWIO_TCSR_CXIP_LM_TRS_TRS_SHFT                                                                                    0x0

#define HWIO_TCSR_APSS_SPARE_REG_RD_1_ADDR                                                                         (TCSR_TCSR_REGS_REG_BASE      + 0x00002528)
#define HWIO_TCSR_APSS_SPARE_REG_RD_1_RMSK                                                                         0xffffffff
#define HWIO_TCSR_APSS_SPARE_REG_RD_1_IN          \
        in_dword_masked(HWIO_TCSR_APSS_SPARE_REG_RD_1_ADDR, HWIO_TCSR_APSS_SPARE_REG_RD_1_RMSK)
#define HWIO_TCSR_APSS_SPARE_REG_RD_1_INM(m)      \
        in_dword_masked(HWIO_TCSR_APSS_SPARE_REG_RD_1_ADDR, m)
#define HWIO_TCSR_APSS_SPARE_REG_RD_1_SPARE_REG_RD_1_BMSK                                                          0xffffffff
#define HWIO_TCSR_APSS_SPARE_REG_RD_1_SPARE_REG_RD_1_SHFT                                                                 0x0

#define HWIO_TCSR_APSS_SPARE_REG_RD_2_ADDR                                                                         (TCSR_TCSR_REGS_REG_BASE      + 0x0000252c)
#define HWIO_TCSR_APSS_SPARE_REG_RD_2_RMSK                                                                         0xffffffff
#define HWIO_TCSR_APSS_SPARE_REG_RD_2_IN          \
        in_dword_masked(HWIO_TCSR_APSS_SPARE_REG_RD_2_ADDR, HWIO_TCSR_APSS_SPARE_REG_RD_2_RMSK)
#define HWIO_TCSR_APSS_SPARE_REG_RD_2_INM(m)      \
        in_dword_masked(HWIO_TCSR_APSS_SPARE_REG_RD_2_ADDR, m)
#define HWIO_TCSR_APSS_SPARE_REG_RD_2_SPARE_REG_RD_2_BMSK                                                          0xffffffff
#define HWIO_TCSR_APSS_SPARE_REG_RD_2_SPARE_REG_RD_2_SHFT                                                                 0x0

#define HWIO_TCSR_APSS_SPARE_REG_RD_3_ADDR                                                                         (TCSR_TCSR_REGS_REG_BASE      + 0x00002530)
#define HWIO_TCSR_APSS_SPARE_REG_RD_3_RMSK                                                                         0xffffffff
#define HWIO_TCSR_APSS_SPARE_REG_RD_3_IN          \
        in_dword_masked(HWIO_TCSR_APSS_SPARE_REG_RD_3_ADDR, HWIO_TCSR_APSS_SPARE_REG_RD_3_RMSK)
#define HWIO_TCSR_APSS_SPARE_REG_RD_3_INM(m)      \
        in_dword_masked(HWIO_TCSR_APSS_SPARE_REG_RD_3_ADDR, m)
#define HWIO_TCSR_APSS_SPARE_REG_RD_3_SPARE_REG_RD_3_BMSK                                                          0xffffffff
#define HWIO_TCSR_APSS_SPARE_REG_RD_3_SPARE_REG_RD_3_SHFT                                                                 0x0


#endif /* __TCSR_HWIO_H__ */
