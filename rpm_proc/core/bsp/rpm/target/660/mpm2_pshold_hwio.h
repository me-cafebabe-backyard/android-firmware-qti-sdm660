#ifndef __MPM2_PSHOLD_HWIO_H__
#define __MPM2_PSHOLD_HWIO_H__
/*
===========================================================================
*/
/**
  @file mpm2_pshold_hwio.h
  @brief Auto-generated HWIO interface include file.

  Reference chip release:
    SDM660 (Starlord) [starlord_v1.0_p1qxr28]
 
  This file contains HWIO register definitions for the following modules:
    MPM2_PSHOLD

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

  $Header: //components/rel/rpm.bf/1.8/core/bsp/rpm/target/660/mpm2_pshold_hwio.h#1 $
  $DateTime: 2016/11/03 00:13:13 $
  $Author: pwbldsvc $

  ===========================================================================
*/

#include "msmhwiobase.h"

/*----------------------------------------------------------------------------
 * MODULE: MPM2_PSHOLD
 *--------------------------------------------------------------------------*/

#define MPM2_PSHOLD_REG_BASE                                                    (MPM2_MPM_BASE      + 0x0000c000)

#define HWIO_MPM2_MPM_PS_HOLD_ADDR                                              (MPM2_PSHOLD_REG_BASE      + 0x00000000)
#define HWIO_MPM2_MPM_PS_HOLD_RMSK                                                     0x1
#define HWIO_MPM2_MPM_PS_HOLD_IN          \
        in_dword_masked(HWIO_MPM2_MPM_PS_HOLD_ADDR, HWIO_MPM2_MPM_PS_HOLD_RMSK)
#define HWIO_MPM2_MPM_PS_HOLD_INM(m)      \
        in_dword_masked(HWIO_MPM2_MPM_PS_HOLD_ADDR, m)
#define HWIO_MPM2_MPM_PS_HOLD_OUT(v)      \
        out_dword(HWIO_MPM2_MPM_PS_HOLD_ADDR,v)
#define HWIO_MPM2_MPM_PS_HOLD_OUTM(m,v) \
        out_dword_masked_ns(HWIO_MPM2_MPM_PS_HOLD_ADDR,m,v,HWIO_MPM2_MPM_PS_HOLD_IN)
#define HWIO_MPM2_MPM_PS_HOLD_PSHOLD_BMSK                                              0x1
#define HWIO_MPM2_MPM_PS_HOLD_PSHOLD_SHFT                                              0x0

#define HWIO_MPM2_MPM_DDR_PHY_FREEZEIO_EBI1_ADDR                                (MPM2_PSHOLD_REG_BASE      + 0x00000004)
#define HWIO_MPM2_MPM_DDR_PHY_FREEZEIO_EBI1_RMSK                                       0x1
#define HWIO_MPM2_MPM_DDR_PHY_FREEZEIO_EBI1_IN          \
        in_dword_masked(HWIO_MPM2_MPM_DDR_PHY_FREEZEIO_EBI1_ADDR, HWIO_MPM2_MPM_DDR_PHY_FREEZEIO_EBI1_RMSK)
#define HWIO_MPM2_MPM_DDR_PHY_FREEZEIO_EBI1_INM(m)      \
        in_dword_masked(HWIO_MPM2_MPM_DDR_PHY_FREEZEIO_EBI1_ADDR, m)
#define HWIO_MPM2_MPM_DDR_PHY_FREEZEIO_EBI1_OUT(v)      \
        out_dword(HWIO_MPM2_MPM_DDR_PHY_FREEZEIO_EBI1_ADDR,v)
#define HWIO_MPM2_MPM_DDR_PHY_FREEZEIO_EBI1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_MPM2_MPM_DDR_PHY_FREEZEIO_EBI1_ADDR,m,v,HWIO_MPM2_MPM_DDR_PHY_FREEZEIO_EBI1_IN)
#define HWIO_MPM2_MPM_DDR_PHY_FREEZEIO_EBI1_DDR_PHY_FREEZEIO_EBI1_BMSK                 0x1
#define HWIO_MPM2_MPM_DDR_PHY_FREEZEIO_EBI1_DDR_PHY_FREEZEIO_EBI1_SHFT                 0x0

#define HWIO_MPM2_MPM_SSCAON_CONFIG0_ADDR                                       (MPM2_PSHOLD_REG_BASE      + 0x00000008)
#define HWIO_MPM2_MPM_SSCAON_CONFIG0_RMSK                                       0xffffffff
#define HWIO_MPM2_MPM_SSCAON_CONFIG0_IN          \
        in_dword_masked(HWIO_MPM2_MPM_SSCAON_CONFIG0_ADDR, HWIO_MPM2_MPM_SSCAON_CONFIG0_RMSK)
#define HWIO_MPM2_MPM_SSCAON_CONFIG0_INM(m)      \
        in_dword_masked(HWIO_MPM2_MPM_SSCAON_CONFIG0_ADDR, m)
#define HWIO_MPM2_MPM_SSCAON_CONFIG0_OUT(v)      \
        out_dword(HWIO_MPM2_MPM_SSCAON_CONFIG0_ADDR,v)
#define HWIO_MPM2_MPM_SSCAON_CONFIG0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_MPM2_MPM_SSCAON_CONFIG0_ADDR,m,v,HWIO_MPM2_MPM_SSCAON_CONFIG0_IN)
#define HWIO_MPM2_MPM_SSCAON_CONFIG0_SSCAON_CONFIG0_BMSK                        0xffffffff
#define HWIO_MPM2_MPM_SSCAON_CONFIG0_SSCAON_CONFIG0_SHFT                               0x0

#define HWIO_MPM2_MPM_SSCAON_STATUS0_ADDR                                       (MPM2_PSHOLD_REG_BASE      + 0x0000000c)
#define HWIO_MPM2_MPM_SSCAON_STATUS0_RMSK                                       0xffffffff
#define HWIO_MPM2_MPM_SSCAON_STATUS0_IN          \
        in_dword_masked(HWIO_MPM2_MPM_SSCAON_STATUS0_ADDR, HWIO_MPM2_MPM_SSCAON_STATUS0_RMSK)
#define HWIO_MPM2_MPM_SSCAON_STATUS0_INM(m)      \
        in_dword_masked(HWIO_MPM2_MPM_SSCAON_STATUS0_ADDR, m)
#define HWIO_MPM2_MPM_SSCAON_STATUS0_SSCAON_STATUS0_BMSK                        0xffffffff
#define HWIO_MPM2_MPM_SSCAON_STATUS0_SSCAON_STATUS0_SHFT                               0x0

#define HWIO_MPM2_MPM_SSCAON_CONFIG1_ADDR                                       (MPM2_PSHOLD_REG_BASE      + 0x00000010)
#define HWIO_MPM2_MPM_SSCAON_CONFIG1_RMSK                                       0xffffffff
#define HWIO_MPM2_MPM_SSCAON_CONFIG1_IN          \
        in_dword_masked(HWIO_MPM2_MPM_SSCAON_CONFIG1_ADDR, HWIO_MPM2_MPM_SSCAON_CONFIG1_RMSK)
#define HWIO_MPM2_MPM_SSCAON_CONFIG1_INM(m)      \
        in_dword_masked(HWIO_MPM2_MPM_SSCAON_CONFIG1_ADDR, m)
#define HWIO_MPM2_MPM_SSCAON_CONFIG1_OUT(v)      \
        out_dword(HWIO_MPM2_MPM_SSCAON_CONFIG1_ADDR,v)
#define HWIO_MPM2_MPM_SSCAON_CONFIG1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_MPM2_MPM_SSCAON_CONFIG1_ADDR,m,v,HWIO_MPM2_MPM_SSCAON_CONFIG1_IN)
#define HWIO_MPM2_MPM_SSCAON_CONFIG1_SSCAON_CONFIG1_BMSK                        0xffffffff
#define HWIO_MPM2_MPM_SSCAON_CONFIG1_SSCAON_CONFIG1_SHFT                               0x0

#define HWIO_MPM2_MPM_SSCAON_STATUS1_ADDR                                       (MPM2_PSHOLD_REG_BASE      + 0x00000014)
#define HWIO_MPM2_MPM_SSCAON_STATUS1_RMSK                                       0xffffffff
#define HWIO_MPM2_MPM_SSCAON_STATUS1_IN          \
        in_dword_masked(HWIO_MPM2_MPM_SSCAON_STATUS1_ADDR, HWIO_MPM2_MPM_SSCAON_STATUS1_RMSK)
#define HWIO_MPM2_MPM_SSCAON_STATUS1_INM(m)      \
        in_dword_masked(HWIO_MPM2_MPM_SSCAON_STATUS1_ADDR, m)
#define HWIO_MPM2_MPM_SSCAON_STATUS1_SSCAON_STATUS1_BMSK                        0xffffffff
#define HWIO_MPM2_MPM_SSCAON_STATUS1_SSCAON_STATUS1_SHFT                               0x0

#define HWIO_MPM2_MPM_WCSSAON_CONFIG_ADDR                                       (MPM2_PSHOLD_REG_BASE      + 0x00000018)
#define HWIO_MPM2_MPM_WCSSAON_CONFIG_RMSK                                         0x3ff3ff
#define HWIO_MPM2_MPM_WCSSAON_CONFIG_IN          \
        in_dword_masked(HWIO_MPM2_MPM_WCSSAON_CONFIG_ADDR, HWIO_MPM2_MPM_WCSSAON_CONFIG_RMSK)
#define HWIO_MPM2_MPM_WCSSAON_CONFIG_INM(m)      \
        in_dword_masked(HWIO_MPM2_MPM_WCSSAON_CONFIG_ADDR, m)
#define HWIO_MPM2_MPM_WCSSAON_CONFIG_OUT(v)      \
        out_dword(HWIO_MPM2_MPM_WCSSAON_CONFIG_ADDR,v)
#define HWIO_MPM2_MPM_WCSSAON_CONFIG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_MPM2_MPM_WCSSAON_CONFIG_ADDR,m,v,HWIO_MPM2_MPM_WCSSAON_CONFIG_IN)
#define HWIO_MPM2_MPM_WCSSAON_CONFIG_DISCONNECT_CLR_BMSK                          0x200000
#define HWIO_MPM2_MPM_WCSSAON_CONFIG_DISCONNECT_CLR_SHFT                              0x15
#define HWIO_MPM2_MPM_WCSSAON_CONFIG_RCG_CLKGATE_DISABLE_BMSK                     0x100000
#define HWIO_MPM2_MPM_WCSSAON_CONFIG_RCG_CLKGATE_DISABLE_SHFT                         0x14
#define HWIO_MPM2_MPM_WCSSAON_CONFIG_FORCE_XO_EN_BMSK                              0x80000
#define HWIO_MPM2_MPM_WCSSAON_CONFIG_FORCE_XO_EN_SHFT                                 0x13
#define HWIO_MPM2_MPM_WCSSAON_CONFIG_TEST_BUS_SEL_BMSK                             0x78000
#define HWIO_MPM2_MPM_WCSSAON_CONFIG_TEST_BUS_SEL_SHFT                                 0xf
#define HWIO_MPM2_MPM_WCSSAON_CONFIG_FORCE_ACTIVE_BMSK                              0x4000
#define HWIO_MPM2_MPM_WCSSAON_CONFIG_FORCE_ACTIVE_SHFT                                 0xe
#define HWIO_MPM2_MPM_WCSSAON_CONFIG_CLAMP_MEM_ENABLE_BMSK                          0x2000
#define HWIO_MPM2_MPM_WCSSAON_CONFIG_CLAMP_MEM_ENABLE_SHFT                             0xd
#define HWIO_MPM2_MPM_WCSSAON_CONFIG_FORCE_RETENTION_BMSK                           0x1000
#define HWIO_MPM2_MPM_WCSSAON_CONFIG_FORCE_RETENTION_SHFT                              0xc
#define HWIO_MPM2_MPM_WCSSAON_CONFIG_CLK_EN_OVRD_VAL_BMSK                            0x200
#define HWIO_MPM2_MPM_WCSSAON_CONFIG_CLK_EN_OVRD_VAL_SHFT                              0x9
#define HWIO_MPM2_MPM_WCSSAON_CONFIG_CLK_EN_OVRD_BMSK                                0x100
#define HWIO_MPM2_MPM_WCSSAON_CONFIG_CLK_EN_OVRD_SHFT                                  0x8
#define HWIO_MPM2_MPM_WCSSAON_CONFIG_MSM_CLAMP_EN_OVRD_VAL_BMSK                       0x80
#define HWIO_MPM2_MPM_WCSSAON_CONFIG_MSM_CLAMP_EN_OVRD_VAL_SHFT                        0x7
#define HWIO_MPM2_MPM_WCSSAON_CONFIG_MSM_CLAMP_EN_OVRD_BMSK                           0x40
#define HWIO_MPM2_MPM_WCSSAON_CONFIG_MSM_CLAMP_EN_OVRD_SHFT                            0x6
#define HWIO_MPM2_MPM_WCSSAON_CONFIG_CLAMP_EN_OVRD_VAL_BMSK                           0x20
#define HWIO_MPM2_MPM_WCSSAON_CONFIG_CLAMP_EN_OVRD_VAL_SHFT                            0x5
#define HWIO_MPM2_MPM_WCSSAON_CONFIG_CLAMP_EN_OVRD_BMSK                               0x10
#define HWIO_MPM2_MPM_WCSSAON_CONFIG_CLAMP_EN_OVRD_SHFT                                0x4
#define HWIO_MPM2_MPM_WCSSAON_CONFIG_PWR_EN_OVRD_VAL_BMSK                              0x8
#define HWIO_MPM2_MPM_WCSSAON_CONFIG_PWR_EN_OVRD_VAL_SHFT                              0x3
#define HWIO_MPM2_MPM_WCSSAON_CONFIG_PWR_EN_OVRD_BMSK                                  0x4
#define HWIO_MPM2_MPM_WCSSAON_CONFIG_PWR_EN_OVRD_SHFT                                  0x2
#define HWIO_MPM2_MPM_WCSSAON_CONFIG_WLAN_DISABLE_BMSK                                 0x2
#define HWIO_MPM2_MPM_WCSSAON_CONFIG_WLAN_DISABLE_SHFT                                 0x1
#define HWIO_MPM2_MPM_WCSSAON_CONFIG_ARES_N_BMSK                                       0x1
#define HWIO_MPM2_MPM_WCSSAON_CONFIG_ARES_N_SHFT                                       0x0

#define HWIO_MPM2_WCSSAON_MPM_STATUS_ADDR                                       (MPM2_PSHOLD_REG_BASE      + 0x0000001c)
#define HWIO_MPM2_WCSSAON_MPM_STATUS_RMSK                                       0xffffffff
#define HWIO_MPM2_WCSSAON_MPM_STATUS_IN          \
        in_dword_masked(HWIO_MPM2_WCSSAON_MPM_STATUS_ADDR, HWIO_MPM2_WCSSAON_MPM_STATUS_RMSK)
#define HWIO_MPM2_WCSSAON_MPM_STATUS_INM(m)      \
        in_dword_masked(HWIO_MPM2_WCSSAON_MPM_STATUS_ADDR, m)
#define HWIO_MPM2_WCSSAON_MPM_STATUS_WCSSAON_STATUS_BMSK                        0xffffffff
#define HWIO_MPM2_WCSSAON_MPM_STATUS_WCSSAON_STATUS_SHFT                               0x0


#endif /* __MPM2_PSHOLD_HWIO_H__ */
