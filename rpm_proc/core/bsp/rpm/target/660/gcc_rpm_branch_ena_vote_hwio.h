#ifndef __GCC_RPM_BRANCH_ENA_VOTE_HWIO_H__
#define __GCC_RPM_BRANCH_ENA_VOTE_HWIO_H__
/*
===========================================================================
*/
/**
  @file gcc_rpm_branch_ena_vote_hwio.h
  @brief Auto-generated HWIO interface include file.

  This file contains HWIO register definitions for the following modules:
    GCC_CLK_CTL_REG

  'Include' filters applied: RPM_CLOCK_BRANCH_ENA_VOTE[GCC_CLK_CTL_REG] 
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

  $Header: //components/rel/rpm.bf/1.8/core/bsp/rpm/target/660/gcc_rpm_branch_ena_vote_hwio.h#2 $
  $DateTime: 2016/11/07 22:46:44 $
  $Author: pwbldsvc $

  ===========================================================================
*/

#include "msmhwiobase.h"

/*----------------------------------------------------------------------------
 * MODULE: GCC_CLK_CTL_REG
 *--------------------------------------------------------------------------*/

#define GCC_CLK_CTL_REG_REG_BASE                                                                  (CLK_CTL_BASE      + 0x00000000)

#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_ADDR                                                   (GCC_CLK_CTL_REG_REG_BASE      + 0x00051004)
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_RMSK                                                   0xffffffff
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_IN          \
        in_dword_masked(HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_ADDR, HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_RMSK)
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_INM(m)      \
        in_dword_masked(HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_ADDR, m)
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_OUT(v)      \
        out_dword(HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_ADDR,v)
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_ADDR,m,v,HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_IN)
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_TCSR_AHB_CLK_ENA_BMSK                                  0x80000000
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_TCSR_AHB_CLK_ENA_SHFT                                        0x1f
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_TCSR_AHB_CLK_ENA_DISABLE_FVAL                                 0x0
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_TCSR_AHB_CLK_ENA_ENABLE_FVAL                                  0x1
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_RESERVE_BIT30_BMSK                                     0x40000000
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_RESERVE_BIT30_SHFT                                           0x1e
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_RESERVE_BIT29_BMSK                                     0x20000000
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_RESERVE_BIT29_SHFT                                           0x1d
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_RESERVE_BIT28_BMSK                                     0x10000000
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_RESERVE_BIT28_SHFT                                           0x1c
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_RESERVE_BIT27_BMSK                                      0x8000000
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_RESERVE_BIT27_SHFT                                           0x1b
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_RESERVE_BIT26_BMSK                                      0x4000000
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_RESERVE_BIT26_SHFT                                           0x1a
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_RESERVE_BIT25_BMSK                                      0x2000000
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_RESERVE_BIT25_SHFT                                           0x19
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_IMEM_AXI_CLK_ENA_BMSK                                   0x1000000
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_IMEM_AXI_CLK_ENA_SHFT                                        0x18
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_IMEM_AXI_CLK_ENA_DISABLE_FVAL                                 0x0
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_IMEM_AXI_CLK_ENA_ENABLE_FVAL                                  0x1
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_SYS_NOC_HMSS_AHB_CLK_ENA_BMSK                            0x800000
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_SYS_NOC_HMSS_AHB_CLK_ENA_SHFT                                0x17
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_SYS_NOC_HMSS_AHB_CLK_ENA_DISABLE_FVAL                         0x0
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_SYS_NOC_HMSS_AHB_CLK_ENA_ENABLE_FVAL                          0x1
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_BIMC_HMSS_AXI_CLK_ENA_BMSK                               0x400000
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_BIMC_HMSS_AXI_CLK_ENA_SHFT                                   0x16
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_BIMC_HMSS_AXI_CLK_ENA_DISABLE_FVAL                            0x0
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_BIMC_HMSS_AXI_CLK_ENA_ENABLE_FVAL                             0x1
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_HMSS_AHB_CLK_ENA_BMSK                                    0x200000
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_HMSS_AHB_CLK_ENA_SHFT                                        0x15
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_HMSS_AHB_CLK_ENA_DISABLE_FVAL                                 0x0
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_HMSS_AHB_CLK_ENA_ENABLE_FVAL                                  0x1
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_RESERVE_BIT20_BMSK                                       0x100000
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_RESERVE_BIT20_SHFT                                           0x14
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_MPM_AHB_CLK_ENA_BMSK                                      0x80000
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_MPM_AHB_CLK_ENA_SHFT                                         0x13
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_MPM_AHB_CLK_ENA_DISABLE_FVAL                                  0x0
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_MPM_AHB_CLK_ENA_ENABLE_FVAL                                   0x1
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_RESERVE_BIT18_BMSK                                        0x40000
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_RESERVE_BIT18_SHFT                                           0x12
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_BLSP1_AHB_CLK_ENA_BMSK                                    0x20000
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_BLSP1_AHB_CLK_ENA_SHFT                                       0x11
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_BLSP1_AHB_CLK_ENA_DISABLE_FVAL                                0x0
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_BLSP1_AHB_CLK_ENA_ENABLE_FVAL                                 0x1
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_BLSP1_SLEEP_CLK_ENA_BMSK                                  0x10000
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_BLSP1_SLEEP_CLK_ENA_SHFT                                     0x10
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_BLSP1_SLEEP_CLK_ENA_DISABLE_FVAL                              0x0
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_BLSP1_SLEEP_CLK_ENA_ENABLE_FVAL                               0x1
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_BLSP2_AHB_CLK_ENA_BMSK                                     0x8000
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_BLSP2_AHB_CLK_ENA_SHFT                                        0xf
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_BLSP2_AHB_CLK_ENA_DISABLE_FVAL                                0x0
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_BLSP2_AHB_CLK_ENA_ENABLE_FVAL                                 0x1
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_BLSP2_SLEEP_CLK_ENA_BMSK                                   0x4000
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_BLSP2_SLEEP_CLK_ENA_SHFT                                      0xe
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_BLSP2_SLEEP_CLK_ENA_DISABLE_FVAL                              0x0
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_BLSP2_SLEEP_CLK_ENA_ENABLE_FVAL                               0x1
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_PRNG_AHB_CLK_ENA_BMSK                                      0x2000
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_PRNG_AHB_CLK_ENA_SHFT                                         0xd
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_PRNG_AHB_CLK_ENA_DISABLE_FVAL                                 0x0
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_PRNG_AHB_CLK_ENA_ENABLE_FVAL                                  0x1
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_TLMM_CENTRE_AHB_CLK_ENA_BMSK                               0x1000
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_TLMM_CENTRE_AHB_CLK_ENA_SHFT                                  0xc
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_TLMM_CENTRE_AHB_CLK_ENA_DISABLE_FVAL                          0x0
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_TLMM_CENTRE_AHB_CLK_ENA_ENABLE_FVAL                           0x1
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_TLMM_NORTH_AHB_CLK_ENA_BMSK                                 0x800
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_TLMM_NORTH_AHB_CLK_ENA_SHFT                                   0xb
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_TLMM_NORTH_AHB_CLK_ENA_DISABLE_FVAL                           0x0
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_TLMM_NORTH_AHB_CLK_ENA_ENABLE_FVAL                            0x1
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_BOOT_ROM_AHB_CLK_ENA_BMSK                                   0x400
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_BOOT_ROM_AHB_CLK_ENA_SHFT                                     0xa
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_BOOT_ROM_AHB_CLK_ENA_DISABLE_FVAL                             0x0
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_BOOT_ROM_AHB_CLK_ENA_ENABLE_FVAL                              0x1
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_MSG_RAM_AHB_CLK_ENA_BMSK                                    0x200
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_MSG_RAM_AHB_CLK_ENA_SHFT                                      0x9
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_MSG_RAM_AHB_CLK_ENA_DISABLE_FVAL                              0x0
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_MSG_RAM_AHB_CLK_ENA_ENABLE_FVAL                               0x1
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_TLMM_SOUTH_AHB_CLK_ENA_BMSK                                 0x100
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_TLMM_SOUTH_AHB_CLK_ENA_SHFT                                   0x8
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_TLMM_SOUTH_AHB_CLK_ENA_DISABLE_FVAL                           0x0
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_TLMM_SOUTH_AHB_CLK_ENA_ENABLE_FVAL                            0x1
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_TLMM_CLK_ENA_BMSK                                            0x80
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_TLMM_CLK_ENA_SHFT                                             0x7
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_TLMM_CLK_ENA_DISABLE_FVAL                                     0x0
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_TLMM_CLK_ENA_ENABLE_FVAL                                      0x1
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_SPMI_CNOC_AHB_CLK_ENA_BMSK                                   0x40
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_SPMI_CNOC_AHB_CLK_ENA_SHFT                                    0x6
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_SPMI_CNOC_AHB_CLK_ENA_DISABLE_FVAL                            0x0
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_SPMI_CNOC_AHB_CLK_ENA_ENABLE_FVAL                             0x1
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_CE1_CLK_ENA_BMSK                                             0x20
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_CE1_CLK_ENA_SHFT                                              0x5
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_CE1_CLK_ENA_DISABLE_FVAL                                      0x0
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_CE1_CLK_ENA_ENABLE_FVAL                                       0x1
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_CE1_AXI_CLK_ENA_BMSK                                         0x10
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_CE1_AXI_CLK_ENA_SHFT                                          0x4
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_CE1_AXI_CLK_ENA_DISABLE_FVAL                                  0x0
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_CE1_AXI_CLK_ENA_ENABLE_FVAL                                   0x1
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_CE1_AHB_CLK_ENA_BMSK                                          0x8
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_CE1_AHB_CLK_ENA_SHFT                                          0x3
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_CE1_AHB_CLK_ENA_DISABLE_FVAL                                  0x0
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_CE1_AHB_CLK_ENA_ENABLE_FVAL                                   0x1
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_RESERVE_BIT2_BMSK                                             0x4
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_RESERVE_BIT2_SHFT                                             0x2
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_RESERVE_BIT1_BMSK                                             0x2
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_RESERVE_BIT1_SHFT                                             0x1
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_RESERVE_BIT0_BMSK                                             0x1
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_RESERVE_BIT0_SHFT                                             0x0

#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_1_ADDR                                                 (GCC_CLK_CTL_REG_REG_BASE      + 0x0005100c)
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_1_RMSK                                                       0x7f
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_1_IN          \
        in_dword_masked(HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_1_ADDR, HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_1_RMSK)
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_1_INM(m)      \
        in_dword_masked(HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_1_ADDR, m)
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_1_OUT(v)      \
        out_dword(HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_1_ADDR,v)
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_1_ADDR,m,v,HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_1_IN)
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_1_QDSS_DAP_CLK_ENA_BMSK                                      0x40
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_1_QDSS_DAP_CLK_ENA_SHFT                                       0x6
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_1_QDSS_DAP_CLK_ENA_DISABLE_FVAL                               0x0
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_1_QDSS_DAP_CLK_ENA_ENABLE_FVAL                                0x1
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_1_QDSS_CFG_AHB_CLK_ENA_BMSK                                  0x20
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_1_QDSS_CFG_AHB_CLK_ENA_SHFT                                   0x5
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_1_QDSS_CFG_AHB_CLK_ENA_DISABLE_FVAL                           0x0
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_1_QDSS_CFG_AHB_CLK_ENA_ENABLE_FVAL                            0x1
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_1_GPU_GPLL0_CLK_SRC_ENA_BMSK                                 0x10
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_1_GPU_GPLL0_CLK_SRC_ENA_SHFT                                  0x4
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_1_GPU_GPLL0_CLK_SRC_ENA_DISABLE_FVAL                          0x0
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_1_GPU_GPLL0_CLK_SRC_ENA_ENABLE_FVAL                           0x1
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_1_GPU_GPLL0_DIV_CLK_SRC_ENA_BMSK                              0x8
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_1_GPU_GPLL0_DIV_CLK_SRC_ENA_SHFT                              0x3
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_1_GPU_GPLL0_DIV_CLK_SRC_ENA_DISABLE_FVAL                      0x0
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_1_GPU_GPLL0_DIV_CLK_SRC_ENA_ENABLE_FVAL                       0x1
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_1_MSS_GPLL0_DIV_CLK_SRC_ENA_BMSK                              0x4
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_1_MSS_GPLL0_DIV_CLK_SRC_ENA_SHFT                              0x2
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_1_MSS_GPLL0_DIV_CLK_SRC_ENA_DISABLE_FVAL                      0x0
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_1_MSS_GPLL0_DIV_CLK_SRC_ENA_ENABLE_FVAL                       0x1
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_1_MMSS_GPLL0_CLK_SRC_ENA_BMSK                                 0x2
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_1_MMSS_GPLL0_CLK_SRC_ENA_SHFT                                 0x1
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_1_MMSS_GPLL0_CLK_SRC_ENA_DISABLE_FVAL                         0x0
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_1_MMSS_GPLL0_CLK_SRC_ENA_ENABLE_FVAL                          0x1
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_1_MMSS_GPLL0_DIV_CLK_SRC_ENA_BMSK                             0x1
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_1_MMSS_GPLL0_DIV_CLK_SRC_ENA_SHFT                             0x0
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_1_MMSS_GPLL0_DIV_CLK_SRC_ENA_DISABLE_FVAL                     0x0
#define HWIO_GCC_RPM_CLOCK_BRANCH_ENA_VOTE_1_MMSS_GPLL0_DIV_CLK_SRC_ENA_ENABLE_FVAL                      0x1


#endif /* __GCC_RPM_BRANCH_ENA_VOTE_HWIO_H__ */
