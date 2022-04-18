#ifndef __CLOCKLPASSHWIO_H__
#define __CLOCKLPASSHWIO_H__
/*
===========================================================================
*/
/**
  @file ClockLPASSHWIO.h
  @brief Auto-generated HWIO interface include file.

  Reference chip release:
    SDM660 (Starlord) [starlord_v1.0.1_p3q3r103_MTO]
 
  This file contains HWIO register definitions for the following modules:
    LPASS_CC
    LPASS_QDSP6V60SS_PUB
    LPASS_QDSP6V60SS_CSR
    LPASS_PMU_REGS

  'Include' filters applied: STRAP_ACC[LPASS_QDSP6V60SS_PUB] RCGR[LPASS_QDSP6V60SS_PUB] SWITCHER_DLY[LPASS_PMU_REGS] LPASS_LPA_PLL_VOTE_LPASS_HW[LPASS_CC] QDSP6SS_SPM_EVENT_CTL[LPASS_QDSP6V60SS_CSR] 
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

  $Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/clock/hw/sdm660/adsp_slpi/inc/ClockLPASSHWIO.h#1 $
  $DateTime: 2020/02/10 01:57:30 $
  $Author: pwbldsvc $

  ===========================================================================
*/
#include "HALhwio.h"

/*=========================================================================
      Type Definitions
==========================================================================*/

extern uint32         Clock_nHWIOBaseLPASS;
#define LPASS_BASE    Clock_nHWIOBaseLPASS


/*----------------------------------------------------------------------------
 * MODULE: LPASS_CC
 *--------------------------------------------------------------------------*/

#define LPASS_CC_REG_BASE                                                                                             (LPASS_BASE      + 0x00000000)

#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_ADDR                                                                         (LPASS_CC_REG_BASE      + 0x00007000)
#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_RMSK                                                                               0xff
#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_IN          \
        in_dword_masked(HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_ADDR, HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_RMSK)
#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_ADDR, m)
#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_OUT(v)      \
        out_dword(HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_ADDR,v)
#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_ADDR,m,v,HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_IN)
#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_RESERVE_BITS7_3_BMSK                                                               0xf8
#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_RESERVE_BITS7_3_SHFT                                                                0x3
#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_QDSP6SS_PLL_BMSK                                                                    0x4
#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_QDSP6SS_PLL_SHFT                                                                    0x2
#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_LPAAUDIO_DIG_PLL_BMSK                                                               0x2
#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_LPAAUDIO_DIG_PLL_SHFT                                                               0x1
#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_LPAAUDIO_PLL_BMSK                                                                   0x1
#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_LPAAUDIO_PLL_SHFT                                                                   0x0

/*----------------------------------------------------------------------------
 * MODULE: LPASS_QDSP6V60SS_PUB
 *--------------------------------------------------------------------------*/

#define LPASS_QDSP6V60SS_PUB_REG_BASE                                             (LPASS_BASE      + 0x00700000)

#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_ADDR                                     (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000028)
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_RMSK                                     0x80000013
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_ADDR, HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_RMSK)
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_ADDR,m,v,HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_IN)
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_ROOT_OFF_BMSK                            0x80000000
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_ROOT_OFF_SHFT                                  0x1f
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                            0x10
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                             0x4
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_ROOT_EN_BMSK                                    0x2
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_ROOT_EN_SHFT                                    0x1
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_UPDATE_BMSK                                     0x1
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_UPDATE_SHFT                                     0x0

#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_ADDR                                     (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x0000002c)
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_RMSK                                        0x1071f
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_ADDR, HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_RMSK)
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_ADDR,m,v,HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_IN)
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_RCGLITE_DISABLE_BMSK                        0x10000
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_RCGLITE_DISABLE_SHFT                           0x10
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_SEL_BMSK                                  0x700
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_SEL_SHFT                                    0x8
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_DIV_BMSK                                   0x1f
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_DIV_SHFT                                    0x0

#define HWIO_LPASS_QDSP6SS_STRAP_ACC_ADDR                                         (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000110)
#define HWIO_LPASS_QDSP6SS_STRAP_ACC_RMSK                                         0xffffffff
#define HWIO_LPASS_QDSP6SS_STRAP_ACC_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_ACC_ADDR, HWIO_LPASS_QDSP6SS_STRAP_ACC_RMSK)
#define HWIO_LPASS_QDSP6SS_STRAP_ACC_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_ACC_ADDR, m)
#define HWIO_LPASS_QDSP6SS_STRAP_ACC_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_STRAP_ACC_ADDR,v)
#define HWIO_LPASS_QDSP6SS_STRAP_ACC_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_STRAP_ACC_ADDR,m,v,HWIO_LPASS_QDSP6SS_STRAP_ACC_IN)
#define HWIO_LPASS_QDSP6SS_STRAP_ACC_DATA_BMSK                                    0xffffffff
#define HWIO_LPASS_QDSP6SS_STRAP_ACC_DATA_SHFT                                           0x0

/*----------------------------------------------------------------------------
 * MODULE: LPASS_QDSP6V60SS_CSR
 *--------------------------------------------------------------------------*/

#define LPASS_QDSP6V60SS_CSR_REG_BASE                                                      (LPASS_BASE      + 0x00780000)

#define HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_ADDR                                              (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x00007050)
#define HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_RMSK                                                   0x3ff
#define HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_ADDR, HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_IN)
#define HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_PLL_FINE_OVRRD_BMSK                                    0x200
#define HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_PLL_FINE_OVRRD_SHFT                                      0x9
#define HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_LDO_READY_OVRRD_BMSK                                   0x100
#define HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_LDO_READY_OVRRD_SHFT                                     0x8
#define HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_SMMU_STATUS_OVRRD_BMSK                                  0x80
#define HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_SMMU_STATUS_OVRRD_SHFT                                   0x7
#define HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_AXIM2_HALTACK_OVRRD_BMSK                                0x40
#define HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_AXIM2_HALTACK_OVRRD_SHFT                                 0x6
#define HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_AXIM_HALTACK_OVRRD_BMSK                                 0x20
#define HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_AXIM_HALTACK_OVRRD_SHFT                                  0x5
#define HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_ALL_HALTACK_OVRRD_BMSK                                  0x10
#define HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_ALL_HALTACK_OVRRD_SHFT                                   0x4
#define HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_CORE_CLK_OFF_OVRRD_BMSK                                  0x8
#define HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_CORE_CLK_OFF_OVRRD_SHFT                                  0x3
#define HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_BHS_ACK_OVRRD_BMSK                                       0x4
#define HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_BHS_ACK_OVRRD_SHFT                                       0x2
#define HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_PLL_OVRRD_BMSK                                           0x2
#define HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_PLL_OVRRD_SHFT                                           0x1
#define HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_EXT_PLL_OVRRD_BMSK                                       0x1
#define HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_EXT_PLL_OVRRD_SHFT                                       0x0

/*----------------------------------------------------------------------------
 * MODULE: LPASS_PMU_REGS
 *--------------------------------------------------------------------------*/

#define LPASS_PMU_REGS_REG_BASE                                            (LPASS_BASE      + 0x00060000)

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


#endif /* __CLOCKLPASSHWIO_H__ */
