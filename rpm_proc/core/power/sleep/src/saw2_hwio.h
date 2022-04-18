#ifndef __SAW2_HWIO_H__
#define __SAW2_HWIO_H__
/*
===========================================================================
*/
/**
  @file saw2_hwio.h
  @brief Auto-generated HWIO interface include file.

  This file contains HWIO register definitions for the following modules:
    APCS_L2_KPSS_L2_SAW2
    APCS_BANKED_SAW2
    APCS_ALIAS0_SAW2
    APCS_ALIAS1_SAW2
    APCS_ALIAS2_SAW2
    APCS_ALIAS3_SAW2

  'Include' filters applied: <none>
  'Exclude' filters applied: RESERVED DUMMY
*/
/*
  ===========================================================================

  Copyright (c) 2013 Qualcomm Technologies, Inc.
  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ===========================================================================

  $Header: //components/rel/rpm.bf/1.8/core/power/sleep/src/saw2_hwio.h#1 $
  $DateTime: 2016/11/03 00:13:13 $
  $Author: pwbldsvc $

  ===========================================================================
*/

/*
 * HWIO base definitions
 */
#define KPSS_BASE  0xF9000000

/*----------------------------------------------------------------------------
 * MODULE: APCS_L2_KPSS_L2_SAW2
 *--------------------------------------------------------------------------*/

#define APCS_L2_KPSS_L2_SAW2_REG_BASE                            (KPSS_BASE      + 0x00012000)

#define HWIO_APCS_L2_SAW2_SECURE_ADDR                            (APCS_L2_KPSS_L2_SAW2_REG_BASE      + 0x00000000)
#define HWIO_APCS_L2_SAW2_SECURE_RMSK                                   0x7
#define HWIO_APCS_L2_SAW2_SECURE_IN          \
        in_dword_masked(HWIO_APCS_L2_SAW2_SECURE_ADDR, HWIO_APCS_L2_SAW2_SECURE_RMSK)
#define HWIO_APCS_L2_SAW2_SECURE_INM(m)      \
        in_dword_masked(HWIO_APCS_L2_SAW2_SECURE_ADDR, m)
#define HWIO_APCS_L2_SAW2_SECURE_OUT(v)      \
        out_dword(HWIO_APCS_L2_SAW2_SECURE_ADDR,v)
#define HWIO_APCS_L2_SAW2_SECURE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_L2_SAW2_SECURE_ADDR,m,v,HWIO_APCS_L2_SAW2_SECURE_IN)
#define HWIO_APCS_L2_SAW2_SECURE_SAW_CTL_BMSK                           0x4
#define HWIO_APCS_L2_SAW2_SECURE_SAW_CTL_SHFT                           0x2
#define HWIO_APCS_L2_SAW2_SECURE_PWR_CTL_BMSK                           0x2
#define HWIO_APCS_L2_SAW2_SECURE_PWR_CTL_SHFT                           0x1
#define HWIO_APCS_L2_SAW2_SECURE_VLT_CTL_BMSK                           0x1
#define HWIO_APCS_L2_SAW2_SECURE_VLT_CTL_SHFT                           0x0

#define HWIO_APCS_L2_SAW2_ID_ADDR                                (APCS_L2_KPSS_L2_SAW2_REG_BASE      + 0x00000004)
#define HWIO_APCS_L2_SAW2_ID_RMSK                                0x3f1f1f7f
#define HWIO_APCS_L2_SAW2_ID_IN          \
        in_dword_masked(HWIO_APCS_L2_SAW2_ID_ADDR, HWIO_APCS_L2_SAW2_ID_RMSK)
#define HWIO_APCS_L2_SAW2_ID_INM(m)      \
        in_dword_masked(HWIO_APCS_L2_SAW2_ID_ADDR, m)
#define HWIO_APCS_L2_SAW2_ID_NUM_SPM_ENTRY_BMSK                  0x3f000000
#define HWIO_APCS_L2_SAW2_ID_NUM_SPM_ENTRY_SHFT                        0x18
#define HWIO_APCS_L2_SAW2_ID_NUM_PWR_CTL_BMSK                      0x1f0000
#define HWIO_APCS_L2_SAW2_ID_NUM_PWR_CTL_SHFT                          0x10
#define HWIO_APCS_L2_SAW2_ID_PMIC_DATA_WIDTH_BMSK                    0x1f00
#define HWIO_APCS_L2_SAW2_ID_PMIC_DATA_WIDTH_SHFT                       0x8
#define HWIO_APCS_L2_SAW2_ID_NUM_PMIC_DATA_BMSK                        0x70
#define HWIO_APCS_L2_SAW2_ID_NUM_PMIC_DATA_SHFT                         0x4
#define HWIO_APCS_L2_SAW2_ID_CFG_NS_ACCESS_BMSK                         0x8
#define HWIO_APCS_L2_SAW2_ID_CFG_NS_ACCESS_SHFT                         0x3
#define HWIO_APCS_L2_SAW2_ID_PMIC_ARB_INTF_BMSK                         0x4
#define HWIO_APCS_L2_SAW2_ID_PMIC_ARB_INTF_SHFT                         0x2
#define HWIO_APCS_L2_SAW2_ID_AVS_PRESENT_BMSK                           0x2
#define HWIO_APCS_L2_SAW2_ID_AVS_PRESENT_SHFT                           0x1
#define HWIO_APCS_L2_SAW2_ID_SPM_PRESENT_BMSK                           0x1
#define HWIO_APCS_L2_SAW2_ID_SPM_PRESENT_SHFT                           0x0

#define HWIO_APCS_L2_SAW2_CFG_ADDR                               (APCS_L2_KPSS_L2_SAW2_REG_BASE      + 0x00000008)
#define HWIO_APCS_L2_SAW2_CFG_RMSK                                    0x31f
#define HWIO_APCS_L2_SAW2_CFG_IN          \
        in_dword_masked(HWIO_APCS_L2_SAW2_CFG_ADDR, HWIO_APCS_L2_SAW2_CFG_RMSK)
#define HWIO_APCS_L2_SAW2_CFG_INM(m)      \
        in_dword_masked(HWIO_APCS_L2_SAW2_CFG_ADDR, m)
#define HWIO_APCS_L2_SAW2_CFG_OUT(v)      \
        out_dword(HWIO_APCS_L2_SAW2_CFG_ADDR,v)
#define HWIO_APCS_L2_SAW2_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_L2_SAW2_CFG_ADDR,m,v,HWIO_APCS_L2_SAW2_CFG_IN)
#define HWIO_APCS_L2_SAW2_CFG_TEST_BUS_EN_BMSK                        0x200
#define HWIO_APCS_L2_SAW2_CFG_TEST_BUS_EN_SHFT                          0x9
#define HWIO_APCS_L2_SAW2_CFG_FRC_REF_CLK_ON_BMSK                     0x100
#define HWIO_APCS_L2_SAW2_CFG_FRC_REF_CLK_ON_SHFT                       0x8
#define HWIO_APCS_L2_SAW2_CFG_CLK_DIV_BMSK                             0x1f
#define HWIO_APCS_L2_SAW2_CFG_CLK_DIV_SHFT                              0x0

#define HWIO_APCS_L2_SAW2_SPM_STS_ADDR                           (APCS_L2_KPSS_L2_SAW2_REG_BASE      + 0x0000000c)
#define HWIO_APCS_L2_SAW2_SPM_STS_RMSK                            0xffff1ff
#define HWIO_APCS_L2_SAW2_SPM_STS_IN          \
        in_dword_masked(HWIO_APCS_L2_SAW2_SPM_STS_ADDR, HWIO_APCS_L2_SAW2_SPM_STS_RMSK)
#define HWIO_APCS_L2_SAW2_SPM_STS_INM(m)      \
        in_dword_masked(HWIO_APCS_L2_SAW2_SPM_STS_ADDR, m)
#define HWIO_APCS_L2_SAW2_SPM_STS_CURR_PWR_CTL_BMSK               0xfff0000
#define HWIO_APCS_L2_SAW2_SPM_STS_CURR_PWR_CTL_SHFT                    0x10
#define HWIO_APCS_L2_SAW2_SPM_STS_SHTDWN_REQ_BMSK                    0x8000
#define HWIO_APCS_L2_SAW2_SPM_STS_SHTDWN_REQ_SHFT                       0xf
#define HWIO_APCS_L2_SAW2_SPM_STS_SHTDWN_ACK_BMSK                    0x4000
#define HWIO_APCS_L2_SAW2_SPM_STS_SHTDWN_ACK_SHFT                       0xe
#define HWIO_APCS_L2_SAW2_SPM_STS_BRNGUP_REQ_BMSK                    0x2000
#define HWIO_APCS_L2_SAW2_SPM_STS_BRNGUP_REQ_SHFT                       0xd
#define HWIO_APCS_L2_SAW2_SPM_STS_BRNGUP_ACK_BMSK                    0x1000
#define HWIO_APCS_L2_SAW2_SPM_STS_BRNGUP_ACK_SHFT                       0xc
#define HWIO_APCS_L2_SAW2_SPM_STS_RPM_STATE_BMSK                      0x180
#define HWIO_APCS_L2_SAW2_SPM_STS_RPM_STATE_SHFT                        0x7
#define HWIO_APCS_L2_SAW2_SPM_STS_SPM_CMD_ADDR_BMSK                    0x7f
#define HWIO_APCS_L2_SAW2_SPM_STS_SPM_CMD_ADDR_SHFT                     0x0

#define HWIO_APCS_L2_SAW2_AVS_STS_ADDR                           (APCS_L2_KPSS_L2_SAW2_REG_BASE      + 0x00000010)
#define HWIO_APCS_L2_SAW2_AVS_STS_RMSK                             0xff003f
#define HWIO_APCS_L2_SAW2_AVS_STS_IN          \
        in_dword_masked(HWIO_APCS_L2_SAW2_AVS_STS_ADDR, HWIO_APCS_L2_SAW2_AVS_STS_RMSK)
#define HWIO_APCS_L2_SAW2_AVS_STS_INM(m)      \
        in_dword_masked(HWIO_APCS_L2_SAW2_AVS_STS_ADDR, m)
#define HWIO_APCS_L2_SAW2_AVS_STS_SPM_EVENT_BMSK                   0xff0000
#define HWIO_APCS_L2_SAW2_AVS_STS_SPM_EVENT_SHFT                       0x10
#define HWIO_APCS_L2_SAW2_AVS_STS_MAX_INT_BMSK                         0x20
#define HWIO_APCS_L2_SAW2_AVS_STS_MAX_INT_SHFT                          0x5
#define HWIO_APCS_L2_SAW2_AVS_STS_MIN_INT_BMSK                         0x10
#define HWIO_APCS_L2_SAW2_AVS_STS_MIN_INT_SHFT                          0x4
#define HWIO_APCS_L2_SAW2_AVS_STS_CPU_UP_BMSK                           0x8
#define HWIO_APCS_L2_SAW2_AVS_STS_CPU_UP_SHFT                           0x3
#define HWIO_APCS_L2_SAW2_AVS_STS_CPU_DN_BMSK                           0x4
#define HWIO_APCS_L2_SAW2_AVS_STS_CPU_DN_SHFT                           0x2
#define HWIO_APCS_L2_SAW2_AVS_STS_SW_WR_PEND_BMSK                       0x2
#define HWIO_APCS_L2_SAW2_AVS_STS_SW_WR_PEND_SHFT                       0x1
#define HWIO_APCS_L2_SAW2_AVS_STS_AVS_STATE_BMSK                        0x1
#define HWIO_APCS_L2_SAW2_AVS_STS_AVS_STATE_SHFT                        0x0

#define HWIO_APCS_L2_SAW2_PMIC_STS_ADDR                          (APCS_L2_KPSS_L2_SAW2_REG_BASE      + 0x00000014)
#define HWIO_APCS_L2_SAW2_PMIC_STS_RMSK                          0x3ff700ff
#define HWIO_APCS_L2_SAW2_PMIC_STS_IN          \
        in_dword_masked(HWIO_APCS_L2_SAW2_PMIC_STS_ADDR, HWIO_APCS_L2_SAW2_PMIC_STS_RMSK)
#define HWIO_APCS_L2_SAW2_PMIC_STS_INM(m)      \
        in_dword_masked(HWIO_APCS_L2_SAW2_PMIC_STS_ADDR, m)
#define HWIO_APCS_L2_SAW2_PMIC_STS_CURR_DLY_BMSK                 0x3ff00000
#define HWIO_APCS_L2_SAW2_PMIC_STS_CURR_DLY_SHFT                       0x14
#define HWIO_APCS_L2_SAW2_PMIC_STS_CURR_PMIC_SIZE_BMSK              0x40000
#define HWIO_APCS_L2_SAW2_PMIC_STS_CURR_PMIC_SIZE_SHFT                 0x12
#define HWIO_APCS_L2_SAW2_PMIC_STS_PMIC_STATE_BMSK                  0x30000
#define HWIO_APCS_L2_SAW2_PMIC_STS_PMIC_STATE_SHFT                     0x10
#define HWIO_APCS_L2_SAW2_PMIC_STS_CURR_PMIC_DATA_BMSK                 0xff
#define HWIO_APCS_L2_SAW2_PMIC_STS_CURR_PMIC_DATA_SHFT                  0x0

#define HWIO_APCS_L2_SAW2_RST_ADDR                               (APCS_L2_KPSS_L2_SAW2_REG_BASE      + 0x00000018)
#define HWIO_APCS_L2_SAW2_RST_RMSK                                      0x1
#define HWIO_APCS_L2_SAW2_RST_IN          \
        in_dword_masked(HWIO_APCS_L2_SAW2_RST_ADDR, HWIO_APCS_L2_SAW2_RST_RMSK)
#define HWIO_APCS_L2_SAW2_RST_INM(m)      \
        in_dword_masked(HWIO_APCS_L2_SAW2_RST_ADDR, m)
#define HWIO_APCS_L2_SAW2_RST_OUT(v)      \
        out_dword(HWIO_APCS_L2_SAW2_RST_ADDR,v)
#define HWIO_APCS_L2_SAW2_RST_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_L2_SAW2_RST_ADDR,m,v,HWIO_APCS_L2_SAW2_RST_IN)
#define HWIO_APCS_L2_SAW2_RST_RST_BMSK                                  0x1
#define HWIO_APCS_L2_SAW2_RST_RST_SHFT                                  0x0

#define HWIO_APCS_L2_SAW2_VCTL_ADDR                              (APCS_L2_KPSS_L2_SAW2_REG_BASE      + 0x0000001c)
#define HWIO_APCS_L2_SAW2_VCTL_RMSK                                0x1700ff
#define HWIO_APCS_L2_SAW2_VCTL_IN          \
        in_dword_masked(HWIO_APCS_L2_SAW2_VCTL_ADDR, HWIO_APCS_L2_SAW2_VCTL_RMSK)
#define HWIO_APCS_L2_SAW2_VCTL_INM(m)      \
        in_dword_masked(HWIO_APCS_L2_SAW2_VCTL_ADDR, m)
#define HWIO_APCS_L2_SAW2_VCTL_OUT(v)      \
        out_dword(HWIO_APCS_L2_SAW2_VCTL_ADDR,v)
#define HWIO_APCS_L2_SAW2_VCTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_L2_SAW2_VCTL_ADDR,m,v,HWIO_APCS_L2_SAW2_VCTL_IN)
#define HWIO_APCS_L2_SAW2_VCTL_SIZE_BMSK                           0x100000
#define HWIO_APCS_L2_SAW2_VCTL_SIZE_SHFT                               0x14
#define HWIO_APCS_L2_SAW2_VCTL_ADR_IDX_BMSK                         0x70000
#define HWIO_APCS_L2_SAW2_VCTL_ADR_IDX_SHFT                            0x10
#define HWIO_APCS_L2_SAW2_VCTL_PMIC_DATA_BMSK                          0xff
#define HWIO_APCS_L2_SAW2_VCTL_PMIC_DATA_SHFT                           0x0

#define HWIO_APCS_L2_SAW2_AVS_CTL_ADDR                           (APCS_L2_KPSS_L2_SAW2_REG_BASE      + 0x00000020)
#define HWIO_APCS_L2_SAW2_AVS_CTL_RMSK                               0x130f
#define HWIO_APCS_L2_SAW2_AVS_CTL_IN          \
        in_dword_masked(HWIO_APCS_L2_SAW2_AVS_CTL_ADDR, HWIO_APCS_L2_SAW2_AVS_CTL_RMSK)
#define HWIO_APCS_L2_SAW2_AVS_CTL_INM(m)      \
        in_dword_masked(HWIO_APCS_L2_SAW2_AVS_CTL_ADDR, m)
#define HWIO_APCS_L2_SAW2_AVS_CTL_OUT(v)      \
        out_dword(HWIO_APCS_L2_SAW2_AVS_CTL_ADDR,v)
#define HWIO_APCS_L2_SAW2_AVS_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_L2_SAW2_AVS_CTL_ADDR,m,v,HWIO_APCS_L2_SAW2_AVS_CTL_IN)
#define HWIO_APCS_L2_SAW2_AVS_CTL_VLVL_WIDTH_BMSK                    0x1000
#define HWIO_APCS_L2_SAW2_AVS_CTL_VLVL_WIDTH_SHFT                       0xc
#define HWIO_APCS_L2_SAW2_AVS_CTL_VLVL_STEP_BMSK                      0x300
#define HWIO_APCS_L2_SAW2_AVS_CTL_VLVL_STEP_SHFT                        0x8
#define HWIO_APCS_L2_SAW2_AVS_CTL_SW_DONE_INT_EN_BMSK                   0x8
#define HWIO_APCS_L2_SAW2_AVS_CTL_SW_DONE_INT_EN_SHFT                   0x3
#define HWIO_APCS_L2_SAW2_AVS_CTL_MAX_INT_EN_BMSK                       0x4
#define HWIO_APCS_L2_SAW2_AVS_CTL_MAX_INT_EN_SHFT                       0x2
#define HWIO_APCS_L2_SAW2_AVS_CTL_MIN_INT_EN_BMSK                       0x2
#define HWIO_APCS_L2_SAW2_AVS_CTL_MIN_INT_EN_SHFT                       0x1
#define HWIO_APCS_L2_SAW2_AVS_CTL_EN_BMSK                               0x1
#define HWIO_APCS_L2_SAW2_AVS_CTL_EN_SHFT                               0x0

#define HWIO_APCS_L2_SAW2_AVS_LIMIT_ADDR                         (APCS_L2_KPSS_L2_SAW2_REG_BASE      + 0x00000024)
#define HWIO_APCS_L2_SAW2_AVS_LIMIT_RMSK                           0xff00ff
#define HWIO_APCS_L2_SAW2_AVS_LIMIT_IN          \
        in_dword_masked(HWIO_APCS_L2_SAW2_AVS_LIMIT_ADDR, HWIO_APCS_L2_SAW2_AVS_LIMIT_RMSK)
#define HWIO_APCS_L2_SAW2_AVS_LIMIT_INM(m)      \
        in_dword_masked(HWIO_APCS_L2_SAW2_AVS_LIMIT_ADDR, m)
#define HWIO_APCS_L2_SAW2_AVS_LIMIT_OUT(v)      \
        out_dword(HWIO_APCS_L2_SAW2_AVS_LIMIT_ADDR,v)
#define HWIO_APCS_L2_SAW2_AVS_LIMIT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_L2_SAW2_AVS_LIMIT_ADDR,m,v,HWIO_APCS_L2_SAW2_AVS_LIMIT_IN)
#define HWIO_APCS_L2_SAW2_AVS_LIMIT_MAX_VLVL_BMSK                  0xff0000
#define HWIO_APCS_L2_SAW2_AVS_LIMIT_MAX_VLVL_SHFT                      0x10
#define HWIO_APCS_L2_SAW2_AVS_LIMIT_MIN_VLVL_BMSK                      0xff
#define HWIO_APCS_L2_SAW2_AVS_LIMIT_MIN_VLVL_SHFT                       0x0

#define HWIO_APCS_L2_SAW2_AVS_DLY_ADDR                           (APCS_L2_KPSS_L2_SAW2_REG_BASE      + 0x00000028)
#define HWIO_APCS_L2_SAW2_AVS_DLY_RMSK                                0x3ff
#define HWIO_APCS_L2_SAW2_AVS_DLY_IN          \
        in_dword_masked(HWIO_APCS_L2_SAW2_AVS_DLY_ADDR, HWIO_APCS_L2_SAW2_AVS_DLY_RMSK)
#define HWIO_APCS_L2_SAW2_AVS_DLY_INM(m)      \
        in_dword_masked(HWIO_APCS_L2_SAW2_AVS_DLY_ADDR, m)
#define HWIO_APCS_L2_SAW2_AVS_DLY_OUT(v)      \
        out_dword(HWIO_APCS_L2_SAW2_AVS_DLY_ADDR,v)
#define HWIO_APCS_L2_SAW2_AVS_DLY_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_L2_SAW2_AVS_DLY_ADDR,m,v,HWIO_APCS_L2_SAW2_AVS_DLY_IN)
#define HWIO_APCS_L2_SAW2_AVS_DLY_AVS_DELAY_BMSK                      0x3ff
#define HWIO_APCS_L2_SAW2_AVS_DLY_AVS_DELAY_SHFT                        0x0

#define HWIO_APCS_L2_SAW2_AVS_HYSTERESIS_ADDR                    (APCS_L2_KPSS_L2_SAW2_REG_BASE      + 0x0000002c)
#define HWIO_APCS_L2_SAW2_AVS_HYSTERESIS_RMSK                      0xff00ff
#define HWIO_APCS_L2_SAW2_AVS_HYSTERESIS_IN          \
        in_dword_masked(HWIO_APCS_L2_SAW2_AVS_HYSTERESIS_ADDR, HWIO_APCS_L2_SAW2_AVS_HYSTERESIS_RMSK)
#define HWIO_APCS_L2_SAW2_AVS_HYSTERESIS_INM(m)      \
        in_dword_masked(HWIO_APCS_L2_SAW2_AVS_HYSTERESIS_ADDR, m)
#define HWIO_APCS_L2_SAW2_AVS_HYSTERESIS_OUT(v)      \
        out_dword(HWIO_APCS_L2_SAW2_AVS_HYSTERESIS_ADDR,v)
#define HWIO_APCS_L2_SAW2_AVS_HYSTERESIS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_L2_SAW2_AVS_HYSTERESIS_ADDR,m,v,HWIO_APCS_L2_SAW2_AVS_HYSTERESIS_IN)
#define HWIO_APCS_L2_SAW2_AVS_HYSTERESIS_DN_COUNT_BMSK             0xff0000
#define HWIO_APCS_L2_SAW2_AVS_HYSTERESIS_DN_COUNT_SHFT                 0x10
#define HWIO_APCS_L2_SAW2_AVS_HYSTERESIS_UP_COUNT_BMSK                 0xff
#define HWIO_APCS_L2_SAW2_AVS_HYSTERESIS_UP_COUNT_SHFT                  0x0

#define HWIO_APCS_L2_SAW2_SPM_CTL_ADDR                           (APCS_L2_KPSS_L2_SAW2_REG_BASE      + 0x00000030)
#define HWIO_APCS_L2_SAW2_SPM_CTL_RMSK                              0x107ff
#define HWIO_APCS_L2_SAW2_SPM_CTL_IN          \
        in_dword_masked(HWIO_APCS_L2_SAW2_SPM_CTL_ADDR, HWIO_APCS_L2_SAW2_SPM_CTL_RMSK)
#define HWIO_APCS_L2_SAW2_SPM_CTL_INM(m)      \
        in_dword_masked(HWIO_APCS_L2_SAW2_SPM_CTL_ADDR, m)
#define HWIO_APCS_L2_SAW2_SPM_CTL_OUT(v)      \
        out_dword(HWIO_APCS_L2_SAW2_SPM_CTL_ADDR,v)
#define HWIO_APCS_L2_SAW2_SPM_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_L2_SAW2_SPM_CTL_ADDR,m,v,HWIO_APCS_L2_SAW2_SPM_CTL_IN)
#define HWIO_APCS_L2_SAW2_SPM_CTL_SPM_SYS_PC_MODE_BMSK              0x10000
#define HWIO_APCS_L2_SAW2_SPM_CTL_SPM_SYS_PC_MODE_SHFT                 0x10
#define HWIO_APCS_L2_SAW2_SPM_CTL_SPM_START_ADR_BMSK                  0x7f0
#define HWIO_APCS_L2_SAW2_SPM_CTL_SPM_START_ADR_SHFT                    0x4
#define HWIO_APCS_L2_SAW2_SPM_CTL_ISAR_BMSK                             0x8
#define HWIO_APCS_L2_SAW2_SPM_CTL_ISAR_SHFT                             0x3
#define HWIO_APCS_L2_SAW2_SPM_CTL_WAKEUP_CONFIG_BMSK                    0x6
#define HWIO_APCS_L2_SAW2_SPM_CTL_WAKEUP_CONFIG_SHFT                    0x1
#define HWIO_APCS_L2_SAW2_SPM_CTL_SPM_EN_BMSK                           0x1
#define HWIO_APCS_L2_SAW2_SPM_CTL_SPM_EN_SHFT                           0x0

#define HWIO_APCS_L2_SAW2_SPM_DLY_ADDR                           (APCS_L2_KPSS_L2_SAW2_REG_BASE      + 0x00000034)
#define HWIO_APCS_L2_SAW2_SPM_DLY_RMSK                           0x3fffffff
#define HWIO_APCS_L2_SAW2_SPM_DLY_IN          \
        in_dword_masked(HWIO_APCS_L2_SAW2_SPM_DLY_ADDR, HWIO_APCS_L2_SAW2_SPM_DLY_RMSK)
#define HWIO_APCS_L2_SAW2_SPM_DLY_INM(m)      \
        in_dword_masked(HWIO_APCS_L2_SAW2_SPM_DLY_ADDR, m)
#define HWIO_APCS_L2_SAW2_SPM_DLY_OUT(v)      \
        out_dword(HWIO_APCS_L2_SAW2_SPM_DLY_ADDR,v)
#define HWIO_APCS_L2_SAW2_SPM_DLY_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_L2_SAW2_SPM_DLY_ADDR,m,v,HWIO_APCS_L2_SAW2_SPM_DLY_IN)
#define HWIO_APCS_L2_SAW2_SPM_DLY_DLY3_BMSK                      0x3ff00000
#define HWIO_APCS_L2_SAW2_SPM_DLY_DLY3_SHFT                            0x14
#define HWIO_APCS_L2_SAW2_SPM_DLY_DLY2_BMSK                         0xffc00
#define HWIO_APCS_L2_SAW2_SPM_DLY_DLY2_SHFT                             0xa
#define HWIO_APCS_L2_SAW2_SPM_DLY_DLY1_BMSK                           0x3ff
#define HWIO_APCS_L2_SAW2_SPM_DLY_DLY1_SHFT                             0x0

#define HWIO_APCS_L2_SAW2_SPM_SLP_SEQ_ENTRY_n_ADDR(n)            (APCS_L2_KPSS_L2_SAW2_REG_BASE      + 0x00000080 + 0x4 * (n))
#define HWIO_APCS_L2_SAW2_SPM_SLP_SEQ_ENTRY_n_RMSK               0xffffffff
#define HWIO_APCS_L2_SAW2_SPM_SLP_SEQ_ENTRY_n_MAXn                       19
#define HWIO_APCS_L2_SAW2_SPM_SLP_SEQ_ENTRY_n_INI(n)        \
        in_dword_masked(HWIO_APCS_L2_SAW2_SPM_SLP_SEQ_ENTRY_n_ADDR(n), HWIO_APCS_L2_SAW2_SPM_SLP_SEQ_ENTRY_n_RMSK)
#define HWIO_APCS_L2_SAW2_SPM_SLP_SEQ_ENTRY_n_INMI(n,mask)    \
        in_dword_masked(HWIO_APCS_L2_SAW2_SPM_SLP_SEQ_ENTRY_n_ADDR(n), mask)
#define HWIO_APCS_L2_SAW2_SPM_SLP_SEQ_ENTRY_n_OUTI(n,val)    \
        out_dword(HWIO_APCS_L2_SAW2_SPM_SLP_SEQ_ENTRY_n_ADDR(n),val)
#define HWIO_APCS_L2_SAW2_SPM_SLP_SEQ_ENTRY_n_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_APCS_L2_SAW2_SPM_SLP_SEQ_ENTRY_n_ADDR(n),mask,val,HWIO_APCS_L2_SAW2_SPM_SLP_SEQ_ENTRY_n_INI(n))
#define HWIO_APCS_L2_SAW2_SPM_SLP_SEQ_ENTRY_n_CMD3_BMSK          0xff000000
#define HWIO_APCS_L2_SAW2_SPM_SLP_SEQ_ENTRY_n_CMD3_SHFT                0x18
#define HWIO_APCS_L2_SAW2_SPM_SLP_SEQ_ENTRY_n_CMD2_BMSK            0xff0000
#define HWIO_APCS_L2_SAW2_SPM_SLP_SEQ_ENTRY_n_CMD2_SHFT                0x10
#define HWIO_APCS_L2_SAW2_SPM_SLP_SEQ_ENTRY_n_CMD1_BMSK              0xff00
#define HWIO_APCS_L2_SAW2_SPM_SLP_SEQ_ENTRY_n_CMD1_SHFT                 0x8
#define HWIO_APCS_L2_SAW2_SPM_SLP_SEQ_ENTRY_n_CMD0_BMSK                0xff
#define HWIO_APCS_L2_SAW2_SPM_SLP_SEQ_ENTRY_n_CMD0_SHFT                 0x0

#define HWIO_APCS_L2_SAW2_SPM_PMIC_DATA_n_ADDR(n)                (APCS_L2_KPSS_L2_SAW2_REG_BASE      + 0x00000040 + 0x4 * (n))
#define HWIO_APCS_L2_SAW2_SPM_PMIC_DATA_n_RMSK                    0x71700ff
#define HWIO_APCS_L2_SAW2_SPM_PMIC_DATA_n_MAXn                            5
#define HWIO_APCS_L2_SAW2_SPM_PMIC_DATA_n_INI(n)        \
        in_dword_masked(HWIO_APCS_L2_SAW2_SPM_PMIC_DATA_n_ADDR(n), HWIO_APCS_L2_SAW2_SPM_PMIC_DATA_n_RMSK)
#define HWIO_APCS_L2_SAW2_SPM_PMIC_DATA_n_INMI(n,mask)    \
        in_dword_masked(HWIO_APCS_L2_SAW2_SPM_PMIC_DATA_n_ADDR(n), mask)
#define HWIO_APCS_L2_SAW2_SPM_PMIC_DATA_n_OUTI(n,val)    \
        out_dword(HWIO_APCS_L2_SAW2_SPM_PMIC_DATA_n_ADDR(n),val)
#define HWIO_APCS_L2_SAW2_SPM_PMIC_DATA_n_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_APCS_L2_SAW2_SPM_PMIC_DATA_n_ADDR(n),mask,val,HWIO_APCS_L2_SAW2_SPM_PMIC_DATA_n_INI(n))
#define HWIO_APCS_L2_SAW2_SPM_PMIC_DATA_n_DLY_BMSK                0x7000000
#define HWIO_APCS_L2_SAW2_SPM_PMIC_DATA_n_DLY_SHFT                     0x18
#define HWIO_APCS_L2_SAW2_SPM_PMIC_DATA_n_SIZE_BMSK                0x100000
#define HWIO_APCS_L2_SAW2_SPM_PMIC_DATA_n_SIZE_SHFT                    0x14
#define HWIO_APCS_L2_SAW2_SPM_PMIC_DATA_n_ADR_IDX_BMSK              0x70000
#define HWIO_APCS_L2_SAW2_SPM_PMIC_DATA_n_ADR_IDX_SHFT                 0x10
#define HWIO_APCS_L2_SAW2_SPM_PMIC_DATA_n_DATA_BMSK                    0xff
#define HWIO_APCS_L2_SAW2_SPM_PMIC_DATA_n_DATA_SHFT                     0x0

#define HWIO_APCS_L2_SAW2_VERSION_ADDR                           (APCS_L2_KPSS_L2_SAW2_REG_BASE      + 0x00000fd0)
#define HWIO_APCS_L2_SAW2_VERSION_RMSK                           0xffffffff
#define HWIO_APCS_L2_SAW2_VERSION_IN          \
        in_dword_masked(HWIO_APCS_L2_SAW2_VERSION_ADDR, HWIO_APCS_L2_SAW2_VERSION_RMSK)
#define HWIO_APCS_L2_SAW2_VERSION_INM(m)      \
        in_dword_masked(HWIO_APCS_L2_SAW2_VERSION_ADDR, m)
#define HWIO_APCS_L2_SAW2_VERSION_MAJOR_BMSK                     0xf0000000
#define HWIO_APCS_L2_SAW2_VERSION_MAJOR_SHFT                           0x1c
#define HWIO_APCS_L2_SAW2_VERSION_MINOR_BMSK                      0xfff0000
#define HWIO_APCS_L2_SAW2_VERSION_MINOR_SHFT                           0x10
#define HWIO_APCS_L2_SAW2_VERSION_STEP_BMSK                          0xffff
#define HWIO_APCS_L2_SAW2_VERSION_STEP_SHFT                             0x0

#define HWIO_APCS_L2_DCM_CTL_ADDR                                (APCS_L2_KPSS_L2_SAW2_REG_BASE      + 0x00000800)
#define HWIO_APCS_L2_DCM_CTL_RMSK                                     0x177
#define HWIO_APCS_L2_DCM_CTL_IN          \
        in_dword_masked(HWIO_APCS_L2_DCM_CTL_ADDR, HWIO_APCS_L2_DCM_CTL_RMSK)
#define HWIO_APCS_L2_DCM_CTL_INM(m)      \
        in_dword_masked(HWIO_APCS_L2_DCM_CTL_ADDR, m)
#define HWIO_APCS_L2_DCM_CTL_OUT(v)      \
        out_dword(HWIO_APCS_L2_DCM_CTL_ADDR,v)
#define HWIO_APCS_L2_DCM_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_L2_DCM_CTL_ADDR,m,v,HWIO_APCS_L2_DCM_CTL_IN)
#define HWIO_APCS_L2_DCM_CTL_DSBL_L2_TRTL_BMSK                        0x100
#define HWIO_APCS_L2_DCM_CTL_DSBL_L2_TRTL_SHFT                          0x8
#define HWIO_APCS_L2_DCM_CTL_MIN_MODE_BMSK                             0x70
#define HWIO_APCS_L2_DCM_CTL_MIN_MODE_SHFT                              0x4
#define HWIO_APCS_L2_DCM_CTL_LMT_TRTL_EN_BMSK                           0x4
#define HWIO_APCS_L2_DCM_CTL_LMT_TRTL_EN_SHFT                           0x2
#define HWIO_APCS_L2_DCM_CTL_MAX_EFF_EN_BMSK                            0x2
#define HWIO_APCS_L2_DCM_CTL_MAX_EFF_EN_SHFT                            0x1
#define HWIO_APCS_L2_DCM_CTL_DCM_EN_BMSK                                0x1
#define HWIO_APCS_L2_DCM_CTL_DCM_EN_SHFT                                0x0

#define HWIO_APCS_L2_DCM_HYSTERESIS_ADDR                         (APCS_L2_KPSS_L2_SAW2_REG_BASE      + 0x00000804)
#define HWIO_APCS_L2_DCM_HYSTERESIS_RMSK                            0x71f1f
#define HWIO_APCS_L2_DCM_HYSTERESIS_IN          \
        in_dword_masked(HWIO_APCS_L2_DCM_HYSTERESIS_ADDR, HWIO_APCS_L2_DCM_HYSTERESIS_RMSK)
#define HWIO_APCS_L2_DCM_HYSTERESIS_INM(m)      \
        in_dword_masked(HWIO_APCS_L2_DCM_HYSTERESIS_ADDR, m)
#define HWIO_APCS_L2_DCM_HYSTERESIS_OUT(v)      \
        out_dword(HWIO_APCS_L2_DCM_HYSTERESIS_ADDR,v)
#define HWIO_APCS_L2_DCM_HYSTERESIS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_L2_DCM_HYSTERESIS_ADDR,m,v,HWIO_APCS_L2_DCM_HYSTERESIS_IN)
#define HWIO_APCS_L2_DCM_HYSTERESIS_LMT_CNT_BMSK                    0x70000
#define HWIO_APCS_L2_DCM_HYSTERESIS_LMT_CNT_SHFT                       0x10
#define HWIO_APCS_L2_DCM_HYSTERESIS_CNT_PH_DN_BMSK                   0x1f00
#define HWIO_APCS_L2_DCM_HYSTERESIS_CNT_PH_DN_SHFT                      0x8
#define HWIO_APCS_L2_DCM_HYSTERESIS_CNT_PH_UP_BMSK                     0x1f
#define HWIO_APCS_L2_DCM_HYSTERESIS_CNT_PH_UP_SHFT                      0x0

#define HWIO_APCS_L2_DCM_PMIC_CTL_ADDR                           (APCS_L2_KPSS_L2_SAW2_REG_BASE      + 0x00000808)
#define HWIO_APCS_L2_DCM_PMIC_CTL_RMSK                           0xff17ff17
#define HWIO_APCS_L2_DCM_PMIC_CTL_IN          \
        in_dword_masked(HWIO_APCS_L2_DCM_PMIC_CTL_ADDR, HWIO_APCS_L2_DCM_PMIC_CTL_RMSK)
#define HWIO_APCS_L2_DCM_PMIC_CTL_INM(m)      \
        in_dword_masked(HWIO_APCS_L2_DCM_PMIC_CTL_ADDR, m)
#define HWIO_APCS_L2_DCM_PMIC_CTL_OUT(v)      \
        out_dword(HWIO_APCS_L2_DCM_PMIC_CTL_ADDR,v)
#define HWIO_APCS_L2_DCM_PMIC_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_L2_DCM_PMIC_CTL_ADDR,m,v,HWIO_APCS_L2_DCM_PMIC_CTL_IN)
#define HWIO_APCS_L2_DCM_PMIC_CTL_MODE_CTL_DLY_BMSK              0xff000000
#define HWIO_APCS_L2_DCM_PMIC_CTL_MODE_CTL_DLY_SHFT                    0x18
#define HWIO_APCS_L2_DCM_PMIC_CTL_MODE_CTL_SIZE_BMSK               0x100000
#define HWIO_APCS_L2_DCM_PMIC_CTL_MODE_CTL_SIZE_SHFT                   0x14
#define HWIO_APCS_L2_DCM_PMIC_CTL_MODE_CTL_ADR_IDX_BMSK             0x70000
#define HWIO_APCS_L2_DCM_PMIC_CTL_MODE_CTL_ADR_IDX_SHFT                0x10
#define HWIO_APCS_L2_DCM_PMIC_CTL_PH_CNT_DLY_BMSK                    0xff00
#define HWIO_APCS_L2_DCM_PMIC_CTL_PH_CNT_DLY_SHFT                       0x8
#define HWIO_APCS_L2_DCM_PMIC_CTL_PH_CNT_SIZE_BMSK                     0x10
#define HWIO_APCS_L2_DCM_PMIC_CTL_PH_CNT_SIZE_SHFT                      0x4
#define HWIO_APCS_L2_DCM_PMIC_CTL_PH_CNT_ADR_IDX_BMSK                   0x7
#define HWIO_APCS_L2_DCM_PMIC_CTL_PH_CNT_ADR_IDX_SHFT                   0x0

#define HWIO_APCS_L2_DCM_STS_ADDR                                (APCS_L2_KPSS_L2_SAW2_REG_BASE      + 0x0000080c)
#define HWIO_APCS_L2_DCM_STS_RMSK                                 0xfff0377
#define HWIO_APCS_L2_DCM_STS_IN          \
        in_dword_masked(HWIO_APCS_L2_DCM_STS_ADDR, HWIO_APCS_L2_DCM_STS_RMSK)
#define HWIO_APCS_L2_DCM_STS_INM(m)      \
        in_dword_masked(HWIO_APCS_L2_DCM_STS_ADDR, m)
#define HWIO_APCS_L2_DCM_STS_IMEAS_SUM_BMSK                       0xfff0000
#define HWIO_APCS_L2_DCM_STS_IMEAS_SUM_SHFT                            0x10
#define HWIO_APCS_L2_DCM_STS_CPU_THRTL_STKY_BMSK                      0x200
#define HWIO_APCS_L2_DCM_STS_CPU_THRTL_STKY_SHFT                        0x9
#define HWIO_APCS_L2_DCM_STS_CPU_THRTL_BMSK                           0x100
#define HWIO_APCS_L2_DCM_STS_CPU_THRTL_SHFT                             0x8
#define HWIO_APCS_L2_DCM_STS_NEW_MODE_BMSK                             0x70
#define HWIO_APCS_L2_DCM_STS_NEW_MODE_SHFT                              0x4
#define HWIO_APCS_L2_DCM_STS_CURR_MODE_BMSK                             0x7
#define HWIO_APCS_L2_DCM_STS_CURR_MODE_SHFT                             0x0

#define HWIO_APCS_L2_DCM_PFM_LIMIT_ADDR                          (APCS_L2_KPSS_L2_SAW2_REG_BASE      + 0x00000810)
#define HWIO_APCS_L2_DCM_PFM_LIMIT_RMSK                               0xfff
#define HWIO_APCS_L2_DCM_PFM_LIMIT_IN          \
        in_dword_masked(HWIO_APCS_L2_DCM_PFM_LIMIT_ADDR, HWIO_APCS_L2_DCM_PFM_LIMIT_RMSK)
#define HWIO_APCS_L2_DCM_PFM_LIMIT_INM(m)      \
        in_dword_masked(HWIO_APCS_L2_DCM_PFM_LIMIT_ADDR, m)
#define HWIO_APCS_L2_DCM_PFM_LIMIT_OUT(v)      \
        out_dword(HWIO_APCS_L2_DCM_PFM_LIMIT_ADDR,v)
#define HWIO_APCS_L2_DCM_PFM_LIMIT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_L2_DCM_PFM_LIMIT_ADDR,m,v,HWIO_APCS_L2_DCM_PFM_LIMIT_IN)
#define HWIO_APCS_L2_DCM_PFM_LIMIT_LIMIT_BMSK                         0xfff
#define HWIO_APCS_L2_DCM_PFM_LIMIT_LIMIT_SHFT                           0x0

#define HWIO_APCS_L2_DCM_PH1_LIMIT_ADDR                          (APCS_L2_KPSS_L2_SAW2_REG_BASE      + 0x00000814)
#define HWIO_APCS_L2_DCM_PH1_LIMIT_RMSK                               0xfff
#define HWIO_APCS_L2_DCM_PH1_LIMIT_IN          \
        in_dword_masked(HWIO_APCS_L2_DCM_PH1_LIMIT_ADDR, HWIO_APCS_L2_DCM_PH1_LIMIT_RMSK)
#define HWIO_APCS_L2_DCM_PH1_LIMIT_INM(m)      \
        in_dword_masked(HWIO_APCS_L2_DCM_PH1_LIMIT_ADDR, m)
#define HWIO_APCS_L2_DCM_PH1_LIMIT_OUT(v)      \
        out_dword(HWIO_APCS_L2_DCM_PH1_LIMIT_ADDR,v)
#define HWIO_APCS_L2_DCM_PH1_LIMIT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_L2_DCM_PH1_LIMIT_ADDR,m,v,HWIO_APCS_L2_DCM_PH1_LIMIT_IN)
#define HWIO_APCS_L2_DCM_PH1_LIMIT_LIMIT_BMSK                         0xfff
#define HWIO_APCS_L2_DCM_PH1_LIMIT_LIMIT_SHFT                           0x0

#define HWIO_APCS_L2_DCM_PH2_LIMIT_ADDR                          (APCS_L2_KPSS_L2_SAW2_REG_BASE      + 0x00000818)
#define HWIO_APCS_L2_DCM_PH2_LIMIT_RMSK                               0xfff
#define HWIO_APCS_L2_DCM_PH2_LIMIT_IN          \
        in_dword_masked(HWIO_APCS_L2_DCM_PH2_LIMIT_ADDR, HWIO_APCS_L2_DCM_PH2_LIMIT_RMSK)
#define HWIO_APCS_L2_DCM_PH2_LIMIT_INM(m)      \
        in_dword_masked(HWIO_APCS_L2_DCM_PH2_LIMIT_ADDR, m)
#define HWIO_APCS_L2_DCM_PH2_LIMIT_OUT(v)      \
        out_dword(HWIO_APCS_L2_DCM_PH2_LIMIT_ADDR,v)
#define HWIO_APCS_L2_DCM_PH2_LIMIT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_L2_DCM_PH2_LIMIT_ADDR,m,v,HWIO_APCS_L2_DCM_PH2_LIMIT_IN)
#define HWIO_APCS_L2_DCM_PH2_LIMIT_LIMIT_BMSK                         0xfff
#define HWIO_APCS_L2_DCM_PH2_LIMIT_LIMIT_SHFT                           0x0

#define HWIO_APCS_L2_DCM_PH4_LIMIT_ADDR                          (APCS_L2_KPSS_L2_SAW2_REG_BASE      + 0x0000081c)
#define HWIO_APCS_L2_DCM_PH4_LIMIT_RMSK                               0xfff
#define HWIO_APCS_L2_DCM_PH4_LIMIT_IN          \
        in_dword_masked(HWIO_APCS_L2_DCM_PH4_LIMIT_ADDR, HWIO_APCS_L2_DCM_PH4_LIMIT_RMSK)
#define HWIO_APCS_L2_DCM_PH4_LIMIT_INM(m)      \
        in_dword_masked(HWIO_APCS_L2_DCM_PH4_LIMIT_ADDR, m)
#define HWIO_APCS_L2_DCM_PH4_LIMIT_OUT(v)      \
        out_dword(HWIO_APCS_L2_DCM_PH4_LIMIT_ADDR,v)
#define HWIO_APCS_L2_DCM_PH4_LIMIT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_L2_DCM_PH4_LIMIT_ADDR,m,v,HWIO_APCS_L2_DCM_PH4_LIMIT_IN)
#define HWIO_APCS_L2_DCM_PH4_LIMIT_LIMIT_BMSK                         0xfff
#define HWIO_APCS_L2_DCM_PH4_LIMIT_LIMIT_SHFT                           0x0

#define HWIO_APCS_L2_DCM_PFM_EFF_MAX_ADDR                        (APCS_L2_KPSS_L2_SAW2_REG_BASE      + 0x00000820)
#define HWIO_APCS_L2_DCM_PFM_EFF_MAX_RMSK                             0xfff
#define HWIO_APCS_L2_DCM_PFM_EFF_MAX_IN          \
        in_dword_masked(HWIO_APCS_L2_DCM_PFM_EFF_MAX_ADDR, HWIO_APCS_L2_DCM_PFM_EFF_MAX_RMSK)
#define HWIO_APCS_L2_DCM_PFM_EFF_MAX_INM(m)      \
        in_dword_masked(HWIO_APCS_L2_DCM_PFM_EFF_MAX_ADDR, m)
#define HWIO_APCS_L2_DCM_PFM_EFF_MAX_OUT(v)      \
        out_dword(HWIO_APCS_L2_DCM_PFM_EFF_MAX_ADDR,v)
#define HWIO_APCS_L2_DCM_PFM_EFF_MAX_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_L2_DCM_PFM_EFF_MAX_ADDR,m,v,HWIO_APCS_L2_DCM_PFM_EFF_MAX_IN)
#define HWIO_APCS_L2_DCM_PFM_EFF_MAX_EFF_MAX_BMSK                     0xfff
#define HWIO_APCS_L2_DCM_PFM_EFF_MAX_EFF_MAX_SHFT                       0x0

#define HWIO_APCS_L2_DCM_PH1_EFF_MAX_ADDR                        (APCS_L2_KPSS_L2_SAW2_REG_BASE      + 0x00000824)
#define HWIO_APCS_L2_DCM_PH1_EFF_MAX_RMSK                             0xfff
#define HWIO_APCS_L2_DCM_PH1_EFF_MAX_IN          \
        in_dword_masked(HWIO_APCS_L2_DCM_PH1_EFF_MAX_ADDR, HWIO_APCS_L2_DCM_PH1_EFF_MAX_RMSK)
#define HWIO_APCS_L2_DCM_PH1_EFF_MAX_INM(m)      \
        in_dword_masked(HWIO_APCS_L2_DCM_PH1_EFF_MAX_ADDR, m)
#define HWIO_APCS_L2_DCM_PH1_EFF_MAX_OUT(v)      \
        out_dword(HWIO_APCS_L2_DCM_PH1_EFF_MAX_ADDR,v)
#define HWIO_APCS_L2_DCM_PH1_EFF_MAX_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_L2_DCM_PH1_EFF_MAX_ADDR,m,v,HWIO_APCS_L2_DCM_PH1_EFF_MAX_IN)
#define HWIO_APCS_L2_DCM_PH1_EFF_MAX_EFF_MAX_BMSK                     0xfff
#define HWIO_APCS_L2_DCM_PH1_EFF_MAX_EFF_MAX_SHFT                       0x0

#define HWIO_APCS_L2_DCM_PH2_EFF_MAX_ADDR                        (APCS_L2_KPSS_L2_SAW2_REG_BASE      + 0x00000828)
#define HWIO_APCS_L2_DCM_PH2_EFF_MAX_RMSK                             0xfff
#define HWIO_APCS_L2_DCM_PH2_EFF_MAX_IN          \
        in_dword_masked(HWIO_APCS_L2_DCM_PH2_EFF_MAX_ADDR, HWIO_APCS_L2_DCM_PH2_EFF_MAX_RMSK)
#define HWIO_APCS_L2_DCM_PH2_EFF_MAX_INM(m)      \
        in_dword_masked(HWIO_APCS_L2_DCM_PH2_EFF_MAX_ADDR, m)
#define HWIO_APCS_L2_DCM_PH2_EFF_MAX_OUT(v)      \
        out_dword(HWIO_APCS_L2_DCM_PH2_EFF_MAX_ADDR,v)
#define HWIO_APCS_L2_DCM_PH2_EFF_MAX_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_L2_DCM_PH2_EFF_MAX_ADDR,m,v,HWIO_APCS_L2_DCM_PH2_EFF_MAX_IN)
#define HWIO_APCS_L2_DCM_PH2_EFF_MAX_EFF_MAX_BMSK                     0xfff
#define HWIO_APCS_L2_DCM_PH2_EFF_MAX_EFF_MAX_SHFT                       0x0

#define HWIO_APCS_L2_DCM_LPM_PMIC_DATA_ADDR                      (APCS_L2_KPSS_L2_SAW2_REG_BASE      + 0x0000082c)
#define HWIO_APCS_L2_DCM_LPM_PMIC_DATA_RMSK                            0xff
#define HWIO_APCS_L2_DCM_LPM_PMIC_DATA_IN          \
        in_dword_masked(HWIO_APCS_L2_DCM_LPM_PMIC_DATA_ADDR, HWIO_APCS_L2_DCM_LPM_PMIC_DATA_RMSK)
#define HWIO_APCS_L2_DCM_LPM_PMIC_DATA_INM(m)      \
        in_dword_masked(HWIO_APCS_L2_DCM_LPM_PMIC_DATA_ADDR, m)
#define HWIO_APCS_L2_DCM_LPM_PMIC_DATA_OUT(v)      \
        out_dword(HWIO_APCS_L2_DCM_LPM_PMIC_DATA_ADDR,v)
#define HWIO_APCS_L2_DCM_LPM_PMIC_DATA_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_L2_DCM_LPM_PMIC_DATA_ADDR,m,v,HWIO_APCS_L2_DCM_LPM_PMIC_DATA_IN)
#define HWIO_APCS_L2_DCM_LPM_PMIC_DATA_DATA_BMSK                       0xff
#define HWIO_APCS_L2_DCM_LPM_PMIC_DATA_DATA_SHFT                        0x0

#define HWIO_APCS_L2_DCM_NPM_PMIC_DATA_ADDR                      (APCS_L2_KPSS_L2_SAW2_REG_BASE      + 0x00000830)
#define HWIO_APCS_L2_DCM_NPM_PMIC_DATA_RMSK                            0xff
#define HWIO_APCS_L2_DCM_NPM_PMIC_DATA_IN          \
        in_dword_masked(HWIO_APCS_L2_DCM_NPM_PMIC_DATA_ADDR, HWIO_APCS_L2_DCM_NPM_PMIC_DATA_RMSK)
#define HWIO_APCS_L2_DCM_NPM_PMIC_DATA_INM(m)      \
        in_dword_masked(HWIO_APCS_L2_DCM_NPM_PMIC_DATA_ADDR, m)
#define HWIO_APCS_L2_DCM_NPM_PMIC_DATA_OUT(v)      \
        out_dword(HWIO_APCS_L2_DCM_NPM_PMIC_DATA_ADDR,v)
#define HWIO_APCS_L2_DCM_NPM_PMIC_DATA_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_L2_DCM_NPM_PMIC_DATA_ADDR,m,v,HWIO_APCS_L2_DCM_NPM_PMIC_DATA_IN)
#define HWIO_APCS_L2_DCM_NPM_PMIC_DATA_DATA_BMSK                       0xff
#define HWIO_APCS_L2_DCM_NPM_PMIC_DATA_DATA_SHFT                        0x0

#define HWIO_APCS_L2_DCM_PH1_PMIC_DATA_ADDR                      (APCS_L2_KPSS_L2_SAW2_REG_BASE      + 0x00000834)
#define HWIO_APCS_L2_DCM_PH1_PMIC_DATA_RMSK                            0xff
#define HWIO_APCS_L2_DCM_PH1_PMIC_DATA_IN          \
        in_dword_masked(HWIO_APCS_L2_DCM_PH1_PMIC_DATA_ADDR, HWIO_APCS_L2_DCM_PH1_PMIC_DATA_RMSK)
#define HWIO_APCS_L2_DCM_PH1_PMIC_DATA_INM(m)      \
        in_dword_masked(HWIO_APCS_L2_DCM_PH1_PMIC_DATA_ADDR, m)
#define HWIO_APCS_L2_DCM_PH1_PMIC_DATA_OUT(v)      \
        out_dword(HWIO_APCS_L2_DCM_PH1_PMIC_DATA_ADDR,v)
#define HWIO_APCS_L2_DCM_PH1_PMIC_DATA_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_L2_DCM_PH1_PMIC_DATA_ADDR,m,v,HWIO_APCS_L2_DCM_PH1_PMIC_DATA_IN)
#define HWIO_APCS_L2_DCM_PH1_PMIC_DATA_DATA_BMSK                       0xff
#define HWIO_APCS_L2_DCM_PH1_PMIC_DATA_DATA_SHFT                        0x0

#define HWIO_APCS_L2_DCM_PH2_PMIC_DATA_ADDR                      (APCS_L2_KPSS_L2_SAW2_REG_BASE      + 0x00000838)
#define HWIO_APCS_L2_DCM_PH2_PMIC_DATA_RMSK                            0xff
#define HWIO_APCS_L2_DCM_PH2_PMIC_DATA_IN          \
        in_dword_masked(HWIO_APCS_L2_DCM_PH2_PMIC_DATA_ADDR, HWIO_APCS_L2_DCM_PH2_PMIC_DATA_RMSK)
#define HWIO_APCS_L2_DCM_PH2_PMIC_DATA_INM(m)      \
        in_dword_masked(HWIO_APCS_L2_DCM_PH2_PMIC_DATA_ADDR, m)
#define HWIO_APCS_L2_DCM_PH2_PMIC_DATA_OUT(v)      \
        out_dword(HWIO_APCS_L2_DCM_PH2_PMIC_DATA_ADDR,v)
#define HWIO_APCS_L2_DCM_PH2_PMIC_DATA_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_L2_DCM_PH2_PMIC_DATA_ADDR,m,v,HWIO_APCS_L2_DCM_PH2_PMIC_DATA_IN)
#define HWIO_APCS_L2_DCM_PH2_PMIC_DATA_DATA_BMSK                       0xff
#define HWIO_APCS_L2_DCM_PH2_PMIC_DATA_DATA_SHFT                        0x0

#define HWIO_APCS_L2_DCM_PH4_PMIC_DATA_ADDR                      (APCS_L2_KPSS_L2_SAW2_REG_BASE      + 0x0000083c)
#define HWIO_APCS_L2_DCM_PH4_PMIC_DATA_RMSK                            0xff
#define HWIO_APCS_L2_DCM_PH4_PMIC_DATA_IN          \
        in_dword_masked(HWIO_APCS_L2_DCM_PH4_PMIC_DATA_ADDR, HWIO_APCS_L2_DCM_PH4_PMIC_DATA_RMSK)
#define HWIO_APCS_L2_DCM_PH4_PMIC_DATA_INM(m)      \
        in_dword_masked(HWIO_APCS_L2_DCM_PH4_PMIC_DATA_ADDR, m)
#define HWIO_APCS_L2_DCM_PH4_PMIC_DATA_OUT(v)      \
        out_dword(HWIO_APCS_L2_DCM_PH4_PMIC_DATA_ADDR,v)
#define HWIO_APCS_L2_DCM_PH4_PMIC_DATA_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_L2_DCM_PH4_PMIC_DATA_ADDR,m,v,HWIO_APCS_L2_DCM_PH4_PMIC_DATA_IN)
#define HWIO_APCS_L2_DCM_PH4_PMIC_DATA_DATA_BMSK                       0xff
#define HWIO_APCS_L2_DCM_PH4_PMIC_DATA_DATA_SHFT                        0x0

#define HWIO_APCS_L2_DCM_APC0_IMEAS_ADDR                         (APCS_L2_KPSS_L2_SAW2_REG_BASE      + 0x00000840)
#define HWIO_APCS_L2_DCM_APC0_IMEAS_RMSK                         0x800003ff
#define HWIO_APCS_L2_DCM_APC0_IMEAS_IN          \
        in_dword_masked(HWIO_APCS_L2_DCM_APC0_IMEAS_ADDR, HWIO_APCS_L2_DCM_APC0_IMEAS_RMSK)
#define HWIO_APCS_L2_DCM_APC0_IMEAS_INM(m)      \
        in_dword_masked(HWIO_APCS_L2_DCM_APC0_IMEAS_ADDR, m)
#define HWIO_APCS_L2_DCM_APC0_IMEAS_IMEAS_VLD_BMSK               0x80000000
#define HWIO_APCS_L2_DCM_APC0_IMEAS_IMEAS_VLD_SHFT                     0x1f
#define HWIO_APCS_L2_DCM_APC0_IMEAS_IMEAS_DIG_BMSK                    0x3ff
#define HWIO_APCS_L2_DCM_APC0_IMEAS_IMEAS_DIG_SHFT                      0x0

#define HWIO_APCS_L2_DCM_APC1_IMEAS_ADDR                         (APCS_L2_KPSS_L2_SAW2_REG_BASE      + 0x00000844)
#define HWIO_APCS_L2_DCM_APC1_IMEAS_RMSK                         0x800003ff
#define HWIO_APCS_L2_DCM_APC1_IMEAS_IN          \
        in_dword_masked(HWIO_APCS_L2_DCM_APC1_IMEAS_ADDR, HWIO_APCS_L2_DCM_APC1_IMEAS_RMSK)
#define HWIO_APCS_L2_DCM_APC1_IMEAS_INM(m)      \
        in_dword_masked(HWIO_APCS_L2_DCM_APC1_IMEAS_ADDR, m)
#define HWIO_APCS_L2_DCM_APC1_IMEAS_IMEAS_VLD_BMSK               0x80000000
#define HWIO_APCS_L2_DCM_APC1_IMEAS_IMEAS_VLD_SHFT                     0x1f
#define HWIO_APCS_L2_DCM_APC1_IMEAS_IMEAS_DIG_BMSK                    0x3ff
#define HWIO_APCS_L2_DCM_APC1_IMEAS_IMEAS_DIG_SHFT                      0x0

#define HWIO_APCS_L2_DCM_APC2_IMEAS_ADDR                         (APCS_L2_KPSS_L2_SAW2_REG_BASE      + 0x00000848)
#define HWIO_APCS_L2_DCM_APC2_IMEAS_RMSK                         0x800003ff
#define HWIO_APCS_L2_DCM_APC2_IMEAS_IN          \
        in_dword_masked(HWIO_APCS_L2_DCM_APC2_IMEAS_ADDR, HWIO_APCS_L2_DCM_APC2_IMEAS_RMSK)
#define HWIO_APCS_L2_DCM_APC2_IMEAS_INM(m)      \
        in_dword_masked(HWIO_APCS_L2_DCM_APC2_IMEAS_ADDR, m)
#define HWIO_APCS_L2_DCM_APC2_IMEAS_IMEAS_VLD_BMSK               0x80000000
#define HWIO_APCS_L2_DCM_APC2_IMEAS_IMEAS_VLD_SHFT                     0x1f
#define HWIO_APCS_L2_DCM_APC2_IMEAS_IMEAS_DIG_BMSK                    0x3ff
#define HWIO_APCS_L2_DCM_APC2_IMEAS_IMEAS_DIG_SHFT                      0x0

#define HWIO_APCS_L2_DCM_APC3_IMEAS_ADDR                         (APCS_L2_KPSS_L2_SAW2_REG_BASE      + 0x0000084c)
#define HWIO_APCS_L2_DCM_APC3_IMEAS_RMSK                         0x800003ff
#define HWIO_APCS_L2_DCM_APC3_IMEAS_IN          \
        in_dword_masked(HWIO_APCS_L2_DCM_APC3_IMEAS_ADDR, HWIO_APCS_L2_DCM_APC3_IMEAS_RMSK)
#define HWIO_APCS_L2_DCM_APC3_IMEAS_INM(m)      \
        in_dword_masked(HWIO_APCS_L2_DCM_APC3_IMEAS_ADDR, m)
#define HWIO_APCS_L2_DCM_APC3_IMEAS_IMEAS_VLD_BMSK               0x80000000
#define HWIO_APCS_L2_DCM_APC3_IMEAS_IMEAS_VLD_SHFT                     0x1f
#define HWIO_APCS_L2_DCM_APC3_IMEAS_IMEAS_DIG_BMSK                    0x3ff
#define HWIO_APCS_L2_DCM_APC3_IMEAS_IMEAS_DIG_SHFT                      0x0

/*----------------------------------------------------------------------------
 * MODULE: APCS_BANKED_SAW2
 *--------------------------------------------------------------------------*/

#define APCS_BANKED_SAW2_REG_BASE                                    (KPSS_BASE      + 0x00009000)

#define HWIO_APCS_BANKED_SAW2_SECURE_ADDR                            (APCS_BANKED_SAW2_REG_BASE      + 0x00000000)
#define HWIO_APCS_BANKED_SAW2_SECURE_RMSK                                   0x7
#define HWIO_APCS_BANKED_SAW2_SECURE_IN          \
        in_dword_masked(HWIO_APCS_BANKED_SAW2_SECURE_ADDR, HWIO_APCS_BANKED_SAW2_SECURE_RMSK)
#define HWIO_APCS_BANKED_SAW2_SECURE_INM(m)      \
        in_dword_masked(HWIO_APCS_BANKED_SAW2_SECURE_ADDR, m)
#define HWIO_APCS_BANKED_SAW2_SECURE_OUT(v)      \
        out_dword(HWIO_APCS_BANKED_SAW2_SECURE_ADDR,v)
#define HWIO_APCS_BANKED_SAW2_SECURE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_BANKED_SAW2_SECURE_ADDR,m,v,HWIO_APCS_BANKED_SAW2_SECURE_IN)
#define HWIO_APCS_BANKED_SAW2_SECURE_SAW_CTL_BMSK                           0x4
#define HWIO_APCS_BANKED_SAW2_SECURE_SAW_CTL_SHFT                           0x2
#define HWIO_APCS_BANKED_SAW2_SECURE_PWR_CTL_BMSK                           0x2
#define HWIO_APCS_BANKED_SAW2_SECURE_PWR_CTL_SHFT                           0x1
#define HWIO_APCS_BANKED_SAW2_SECURE_VLT_CTL_BMSK                           0x1
#define HWIO_APCS_BANKED_SAW2_SECURE_VLT_CTL_SHFT                           0x0

#define HWIO_APCS_BANKED_SAW2_ID_ADDR                                (APCS_BANKED_SAW2_REG_BASE      + 0x00000004)
#define HWIO_APCS_BANKED_SAW2_ID_RMSK                                0x3f1f1f7f
#define HWIO_APCS_BANKED_SAW2_ID_IN          \
        in_dword_masked(HWIO_APCS_BANKED_SAW2_ID_ADDR, HWIO_APCS_BANKED_SAW2_ID_RMSK)
#define HWIO_APCS_BANKED_SAW2_ID_INM(m)      \
        in_dword_masked(HWIO_APCS_BANKED_SAW2_ID_ADDR, m)
#define HWIO_APCS_BANKED_SAW2_ID_NUM_SPM_ENTRY_BMSK                  0x3f000000
#define HWIO_APCS_BANKED_SAW2_ID_NUM_SPM_ENTRY_SHFT                        0x18
#define HWIO_APCS_BANKED_SAW2_ID_NUM_PWR_CTL_BMSK                      0x1f0000
#define HWIO_APCS_BANKED_SAW2_ID_NUM_PWR_CTL_SHFT                          0x10
#define HWIO_APCS_BANKED_SAW2_ID_PMIC_DATA_WIDTH_BMSK                    0x1f00
#define HWIO_APCS_BANKED_SAW2_ID_PMIC_DATA_WIDTH_SHFT                       0x8
#define HWIO_APCS_BANKED_SAW2_ID_NUM_PMIC_DATA_BMSK                        0x70
#define HWIO_APCS_BANKED_SAW2_ID_NUM_PMIC_DATA_SHFT                         0x4
#define HWIO_APCS_BANKED_SAW2_ID_CFG_NS_ACCESS_BMSK                         0x8
#define HWIO_APCS_BANKED_SAW2_ID_CFG_NS_ACCESS_SHFT                         0x3
#define HWIO_APCS_BANKED_SAW2_ID_PMIC_ARB_INTF_BMSK                         0x4
#define HWIO_APCS_BANKED_SAW2_ID_PMIC_ARB_INTF_SHFT                         0x2
#define HWIO_APCS_BANKED_SAW2_ID_AVS_PRESENT_BMSK                           0x2
#define HWIO_APCS_BANKED_SAW2_ID_AVS_PRESENT_SHFT                           0x1
#define HWIO_APCS_BANKED_SAW2_ID_SPM_PRESENT_BMSK                           0x1
#define HWIO_APCS_BANKED_SAW2_ID_SPM_PRESENT_SHFT                           0x0

#define HWIO_APCS_BANKED_SAW2_CFG_ADDR                               (APCS_BANKED_SAW2_REG_BASE      + 0x00000008)
#define HWIO_APCS_BANKED_SAW2_CFG_RMSK                                    0x31f
#define HWIO_APCS_BANKED_SAW2_CFG_IN          \
        in_dword_masked(HWIO_APCS_BANKED_SAW2_CFG_ADDR, HWIO_APCS_BANKED_SAW2_CFG_RMSK)
#define HWIO_APCS_BANKED_SAW2_CFG_INM(m)      \
        in_dword_masked(HWIO_APCS_BANKED_SAW2_CFG_ADDR, m)
#define HWIO_APCS_BANKED_SAW2_CFG_OUT(v)      \
        out_dword(HWIO_APCS_BANKED_SAW2_CFG_ADDR,v)
#define HWIO_APCS_BANKED_SAW2_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_BANKED_SAW2_CFG_ADDR,m,v,HWIO_APCS_BANKED_SAW2_CFG_IN)
#define HWIO_APCS_BANKED_SAW2_CFG_TEST_BUS_EN_BMSK                        0x200
#define HWIO_APCS_BANKED_SAW2_CFG_TEST_BUS_EN_SHFT                          0x9
#define HWIO_APCS_BANKED_SAW2_CFG_FRC_REF_CLK_ON_BMSK                     0x100
#define HWIO_APCS_BANKED_SAW2_CFG_FRC_REF_CLK_ON_SHFT                       0x8
#define HWIO_APCS_BANKED_SAW2_CFG_CLK_DIV_BMSK                             0x1f
#define HWIO_APCS_BANKED_SAW2_CFG_CLK_DIV_SHFT                              0x0

#define HWIO_APCS_BANKED_SAW2_SPM_STS_ADDR                           (APCS_BANKED_SAW2_REG_BASE      + 0x0000000c)
#define HWIO_APCS_BANKED_SAW2_SPM_STS_RMSK                           0xfffff1ff
#define HWIO_APCS_BANKED_SAW2_SPM_STS_IN          \
        in_dword_masked(HWIO_APCS_BANKED_SAW2_SPM_STS_ADDR, HWIO_APCS_BANKED_SAW2_SPM_STS_RMSK)
#define HWIO_APCS_BANKED_SAW2_SPM_STS_INM(m)      \
        in_dword_masked(HWIO_APCS_BANKED_SAW2_SPM_STS_ADDR, m)
#define HWIO_APCS_BANKED_SAW2_SPM_STS_CURR_PWR_CTL_BMSK              0xffff0000
#define HWIO_APCS_BANKED_SAW2_SPM_STS_CURR_PWR_CTL_SHFT                    0x10
#define HWIO_APCS_BANKED_SAW2_SPM_STS_SHTDWN_REQ_BMSK                    0x8000
#define HWIO_APCS_BANKED_SAW2_SPM_STS_SHTDWN_REQ_SHFT                       0xf
#define HWIO_APCS_BANKED_SAW2_SPM_STS_SHTDWN_ACK_BMSK                    0x4000
#define HWIO_APCS_BANKED_SAW2_SPM_STS_SHTDWN_ACK_SHFT                       0xe
#define HWIO_APCS_BANKED_SAW2_SPM_STS_BRNGUP_REQ_BMSK                    0x2000
#define HWIO_APCS_BANKED_SAW2_SPM_STS_BRNGUP_REQ_SHFT                       0xd
#define HWIO_APCS_BANKED_SAW2_SPM_STS_BRNGUP_ACK_BMSK                    0x1000
#define HWIO_APCS_BANKED_SAW2_SPM_STS_BRNGUP_ACK_SHFT                       0xc
#define HWIO_APCS_BANKED_SAW2_SPM_STS_RPM_STATE_BMSK                      0x180
#define HWIO_APCS_BANKED_SAW2_SPM_STS_RPM_STATE_SHFT                        0x7
#define HWIO_APCS_BANKED_SAW2_SPM_STS_SPM_CMD_ADDR_BMSK                    0x7f
#define HWIO_APCS_BANKED_SAW2_SPM_STS_SPM_CMD_ADDR_SHFT                     0x0

#define HWIO_APCS_BANKED_SAW2_AVS_STS_ADDR                           (APCS_BANKED_SAW2_REG_BASE      + 0x00000010)
#define HWIO_APCS_BANKED_SAW2_AVS_STS_RMSK                             0xff003f
#define HWIO_APCS_BANKED_SAW2_AVS_STS_IN          \
        in_dword_masked(HWIO_APCS_BANKED_SAW2_AVS_STS_ADDR, HWIO_APCS_BANKED_SAW2_AVS_STS_RMSK)
#define HWIO_APCS_BANKED_SAW2_AVS_STS_INM(m)      \
        in_dword_masked(HWIO_APCS_BANKED_SAW2_AVS_STS_ADDR, m)
#define HWIO_APCS_BANKED_SAW2_AVS_STS_SPM_EVENT_BMSK                   0xff0000
#define HWIO_APCS_BANKED_SAW2_AVS_STS_SPM_EVENT_SHFT                       0x10
#define HWIO_APCS_BANKED_SAW2_AVS_STS_MAX_INT_BMSK                         0x20
#define HWIO_APCS_BANKED_SAW2_AVS_STS_MAX_INT_SHFT                          0x5
#define HWIO_APCS_BANKED_SAW2_AVS_STS_MIN_INT_BMSK                         0x10
#define HWIO_APCS_BANKED_SAW2_AVS_STS_MIN_INT_SHFT                          0x4
#define HWIO_APCS_BANKED_SAW2_AVS_STS_CPU_UP_BMSK                           0x8
#define HWIO_APCS_BANKED_SAW2_AVS_STS_CPU_UP_SHFT                           0x3
#define HWIO_APCS_BANKED_SAW2_AVS_STS_CPU_DN_BMSK                           0x4
#define HWIO_APCS_BANKED_SAW2_AVS_STS_CPU_DN_SHFT                           0x2
#define HWIO_APCS_BANKED_SAW2_AVS_STS_SW_WR_PEND_BMSK                       0x2
#define HWIO_APCS_BANKED_SAW2_AVS_STS_SW_WR_PEND_SHFT                       0x1
#define HWIO_APCS_BANKED_SAW2_AVS_STS_AVS_STATE_BMSK                        0x1
#define HWIO_APCS_BANKED_SAW2_AVS_STS_AVS_STATE_SHFT                        0x0

#define HWIO_APCS_BANKED_SAW2_PMIC_STS_ADDR                          (APCS_BANKED_SAW2_REG_BASE      + 0x00000014)
#define HWIO_APCS_BANKED_SAW2_PMIC_STS_RMSK                          0x3ff300ff
#define HWIO_APCS_BANKED_SAW2_PMIC_STS_IN          \
        in_dword_masked(HWIO_APCS_BANKED_SAW2_PMIC_STS_ADDR, HWIO_APCS_BANKED_SAW2_PMIC_STS_RMSK)
#define HWIO_APCS_BANKED_SAW2_PMIC_STS_INM(m)      \
        in_dword_masked(HWIO_APCS_BANKED_SAW2_PMIC_STS_ADDR, m)
#define HWIO_APCS_BANKED_SAW2_PMIC_STS_CURR_DLY_BMSK                 0x3ff00000
#define HWIO_APCS_BANKED_SAW2_PMIC_STS_CURR_DLY_SHFT                       0x14
#define HWIO_APCS_BANKED_SAW2_PMIC_STS_PMIC_STATE_BMSK                  0x30000
#define HWIO_APCS_BANKED_SAW2_PMIC_STS_PMIC_STATE_SHFT                     0x10
#define HWIO_APCS_BANKED_SAW2_PMIC_STS_CURR_PMIC_DATA_BMSK                 0xff
#define HWIO_APCS_BANKED_SAW2_PMIC_STS_CURR_PMIC_DATA_SHFT                  0x0

#define HWIO_APCS_BANKED_SAW2_RST_ADDR                               (APCS_BANKED_SAW2_REG_BASE      + 0x00000018)
#define HWIO_APCS_BANKED_SAW2_RST_RMSK                                      0x1
#define HWIO_APCS_BANKED_SAW2_RST_IN          \
        in_dword_masked(HWIO_APCS_BANKED_SAW2_RST_ADDR, HWIO_APCS_BANKED_SAW2_RST_RMSK)
#define HWIO_APCS_BANKED_SAW2_RST_INM(m)      \
        in_dword_masked(HWIO_APCS_BANKED_SAW2_RST_ADDR, m)
#define HWIO_APCS_BANKED_SAW2_RST_OUT(v)      \
        out_dword(HWIO_APCS_BANKED_SAW2_RST_ADDR,v)
#define HWIO_APCS_BANKED_SAW2_RST_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_BANKED_SAW2_RST_ADDR,m,v,HWIO_APCS_BANKED_SAW2_RST_IN)
#define HWIO_APCS_BANKED_SAW2_RST_RST_BMSK                                  0x1
#define HWIO_APCS_BANKED_SAW2_RST_RST_SHFT                                  0x0

#define HWIO_APCS_BANKED_SAW2_VCTL_ADDR                              (APCS_BANKED_SAW2_REG_BASE      + 0x0000001c)
#define HWIO_APCS_BANKED_SAW2_VCTL_RMSK                                0x1700ff
#define HWIO_APCS_BANKED_SAW2_VCTL_IN          \
        in_dword_masked(HWIO_APCS_BANKED_SAW2_VCTL_ADDR, HWIO_APCS_BANKED_SAW2_VCTL_RMSK)
#define HWIO_APCS_BANKED_SAW2_VCTL_INM(m)      \
        in_dword_masked(HWIO_APCS_BANKED_SAW2_VCTL_ADDR, m)
#define HWIO_APCS_BANKED_SAW2_VCTL_OUT(v)      \
        out_dword(HWIO_APCS_BANKED_SAW2_VCTL_ADDR,v)
#define HWIO_APCS_BANKED_SAW2_VCTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_BANKED_SAW2_VCTL_ADDR,m,v,HWIO_APCS_BANKED_SAW2_VCTL_IN)
#define HWIO_APCS_BANKED_SAW2_VCTL_SIZE_BMSK                           0x100000
#define HWIO_APCS_BANKED_SAW2_VCTL_SIZE_SHFT                               0x14
#define HWIO_APCS_BANKED_SAW2_VCTL_ADR_IDX_BMSK                         0x70000
#define HWIO_APCS_BANKED_SAW2_VCTL_ADR_IDX_SHFT                            0x10
#define HWIO_APCS_BANKED_SAW2_VCTL_PMIC_DATA_BMSK                          0xff
#define HWIO_APCS_BANKED_SAW2_VCTL_PMIC_DATA_SHFT                           0x0

#define HWIO_APCS_BANKED_SAW2_AVS_CTL_ADDR                           (APCS_BANKED_SAW2_REG_BASE      + 0x00000020)
#define HWIO_APCS_BANKED_SAW2_AVS_CTL_RMSK                               0x130f
#define HWIO_APCS_BANKED_SAW2_AVS_CTL_IN          \
        in_dword_masked(HWIO_APCS_BANKED_SAW2_AVS_CTL_ADDR, HWIO_APCS_BANKED_SAW2_AVS_CTL_RMSK)
#define HWIO_APCS_BANKED_SAW2_AVS_CTL_INM(m)      \
        in_dword_masked(HWIO_APCS_BANKED_SAW2_AVS_CTL_ADDR, m)
#define HWIO_APCS_BANKED_SAW2_AVS_CTL_OUT(v)      \
        out_dword(HWIO_APCS_BANKED_SAW2_AVS_CTL_ADDR,v)
#define HWIO_APCS_BANKED_SAW2_AVS_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_BANKED_SAW2_AVS_CTL_ADDR,m,v,HWIO_APCS_BANKED_SAW2_AVS_CTL_IN)
#define HWIO_APCS_BANKED_SAW2_AVS_CTL_VLVL_WIDTH_BMSK                    0x1000
#define HWIO_APCS_BANKED_SAW2_AVS_CTL_VLVL_WIDTH_SHFT                       0xc
#define HWIO_APCS_BANKED_SAW2_AVS_CTL_VLVL_STEP_BMSK                      0x300
#define HWIO_APCS_BANKED_SAW2_AVS_CTL_VLVL_STEP_SHFT                        0x8
#define HWIO_APCS_BANKED_SAW2_AVS_CTL_SW_DONE_INT_EN_BMSK                   0x8
#define HWIO_APCS_BANKED_SAW2_AVS_CTL_SW_DONE_INT_EN_SHFT                   0x3
#define HWIO_APCS_BANKED_SAW2_AVS_CTL_MAX_INT_EN_BMSK                       0x4
#define HWIO_APCS_BANKED_SAW2_AVS_CTL_MAX_INT_EN_SHFT                       0x2
#define HWIO_APCS_BANKED_SAW2_AVS_CTL_MIN_INT_EN_BMSK                       0x2
#define HWIO_APCS_BANKED_SAW2_AVS_CTL_MIN_INT_EN_SHFT                       0x1
#define HWIO_APCS_BANKED_SAW2_AVS_CTL_EN_BMSK                               0x1
#define HWIO_APCS_BANKED_SAW2_AVS_CTL_EN_SHFT                               0x0

#define HWIO_APCS_BANKED_SAW2_AVS_LIMIT_ADDR                         (APCS_BANKED_SAW2_REG_BASE      + 0x00000024)
#define HWIO_APCS_BANKED_SAW2_AVS_LIMIT_RMSK                           0xff00ff
#define HWIO_APCS_BANKED_SAW2_AVS_LIMIT_IN          \
        in_dword_masked(HWIO_APCS_BANKED_SAW2_AVS_LIMIT_ADDR, HWIO_APCS_BANKED_SAW2_AVS_LIMIT_RMSK)
#define HWIO_APCS_BANKED_SAW2_AVS_LIMIT_INM(m)      \
        in_dword_masked(HWIO_APCS_BANKED_SAW2_AVS_LIMIT_ADDR, m)
#define HWIO_APCS_BANKED_SAW2_AVS_LIMIT_OUT(v)      \
        out_dword(HWIO_APCS_BANKED_SAW2_AVS_LIMIT_ADDR,v)
#define HWIO_APCS_BANKED_SAW2_AVS_LIMIT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_BANKED_SAW2_AVS_LIMIT_ADDR,m,v,HWIO_APCS_BANKED_SAW2_AVS_LIMIT_IN)
#define HWIO_APCS_BANKED_SAW2_AVS_LIMIT_MAX_VLVL_BMSK                  0xff0000
#define HWIO_APCS_BANKED_SAW2_AVS_LIMIT_MAX_VLVL_SHFT                      0x10
#define HWIO_APCS_BANKED_SAW2_AVS_LIMIT_MIN_VLVL_BMSK                      0xff
#define HWIO_APCS_BANKED_SAW2_AVS_LIMIT_MIN_VLVL_SHFT                       0x0

#define HWIO_APCS_BANKED_SAW2_AVS_DLY_ADDR                           (APCS_BANKED_SAW2_REG_BASE      + 0x00000028)
#define HWIO_APCS_BANKED_SAW2_AVS_DLY_RMSK                                0x3ff
#define HWIO_APCS_BANKED_SAW2_AVS_DLY_IN          \
        in_dword_masked(HWIO_APCS_BANKED_SAW2_AVS_DLY_ADDR, HWIO_APCS_BANKED_SAW2_AVS_DLY_RMSK)
#define HWIO_APCS_BANKED_SAW2_AVS_DLY_INM(m)      \
        in_dword_masked(HWIO_APCS_BANKED_SAW2_AVS_DLY_ADDR, m)
#define HWIO_APCS_BANKED_SAW2_AVS_DLY_OUT(v)      \
        out_dword(HWIO_APCS_BANKED_SAW2_AVS_DLY_ADDR,v)
#define HWIO_APCS_BANKED_SAW2_AVS_DLY_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_BANKED_SAW2_AVS_DLY_ADDR,m,v,HWIO_APCS_BANKED_SAW2_AVS_DLY_IN)
#define HWIO_APCS_BANKED_SAW2_AVS_DLY_AVS_DELAY_BMSK                      0x3ff
#define HWIO_APCS_BANKED_SAW2_AVS_DLY_AVS_DELAY_SHFT                        0x0

#define HWIO_APCS_BANKED_SAW2_AVS_HYSTERESIS_ADDR                    (APCS_BANKED_SAW2_REG_BASE      + 0x0000002c)
#define HWIO_APCS_BANKED_SAW2_AVS_HYSTERESIS_RMSK                      0xff00ff
#define HWIO_APCS_BANKED_SAW2_AVS_HYSTERESIS_IN          \
        in_dword_masked(HWIO_APCS_BANKED_SAW2_AVS_HYSTERESIS_ADDR, HWIO_APCS_BANKED_SAW2_AVS_HYSTERESIS_RMSK)
#define HWIO_APCS_BANKED_SAW2_AVS_HYSTERESIS_INM(m)      \
        in_dword_masked(HWIO_APCS_BANKED_SAW2_AVS_HYSTERESIS_ADDR, m)
#define HWIO_APCS_BANKED_SAW2_AVS_HYSTERESIS_OUT(v)      \
        out_dword(HWIO_APCS_BANKED_SAW2_AVS_HYSTERESIS_ADDR,v)
#define HWIO_APCS_BANKED_SAW2_AVS_HYSTERESIS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_BANKED_SAW2_AVS_HYSTERESIS_ADDR,m,v,HWIO_APCS_BANKED_SAW2_AVS_HYSTERESIS_IN)
#define HWIO_APCS_BANKED_SAW2_AVS_HYSTERESIS_DN_COUNT_BMSK             0xff0000
#define HWIO_APCS_BANKED_SAW2_AVS_HYSTERESIS_DN_COUNT_SHFT                 0x10
#define HWIO_APCS_BANKED_SAW2_AVS_HYSTERESIS_UP_COUNT_BMSK                 0xff
#define HWIO_APCS_BANKED_SAW2_AVS_HYSTERESIS_UP_COUNT_SHFT                  0x0

#define HWIO_APCS_BANKED_SAW2_SPM_CTL_ADDR                           (APCS_BANKED_SAW2_REG_BASE      + 0x00000030)
#define HWIO_APCS_BANKED_SAW2_SPM_CTL_RMSK                              0x107ff
#define HWIO_APCS_BANKED_SAW2_SPM_CTL_IN          \
        in_dword_masked(HWIO_APCS_BANKED_SAW2_SPM_CTL_ADDR, HWIO_APCS_BANKED_SAW2_SPM_CTL_RMSK)
#define HWIO_APCS_BANKED_SAW2_SPM_CTL_INM(m)      \
        in_dword_masked(HWIO_APCS_BANKED_SAW2_SPM_CTL_ADDR, m)
#define HWIO_APCS_BANKED_SAW2_SPM_CTL_OUT(v)      \
        out_dword(HWIO_APCS_BANKED_SAW2_SPM_CTL_ADDR,v)
#define HWIO_APCS_BANKED_SAW2_SPM_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_BANKED_SAW2_SPM_CTL_ADDR,m,v,HWIO_APCS_BANKED_SAW2_SPM_CTL_IN)
#define HWIO_APCS_BANKED_SAW2_SPM_CTL_SPM_SYS_PC_MODE_BMSK              0x10000
#define HWIO_APCS_BANKED_SAW2_SPM_CTL_SPM_SYS_PC_MODE_SHFT                 0x10
#define HWIO_APCS_BANKED_SAW2_SPM_CTL_SPM_START_ADR_BMSK                  0x7f0
#define HWIO_APCS_BANKED_SAW2_SPM_CTL_SPM_START_ADR_SHFT                    0x4
#define HWIO_APCS_BANKED_SAW2_SPM_CTL_ISAR_BMSK                             0x8
#define HWIO_APCS_BANKED_SAW2_SPM_CTL_ISAR_SHFT                             0x3
#define HWIO_APCS_BANKED_SAW2_SPM_CTL_WAKEUP_CONFIG_BMSK                    0x6
#define HWIO_APCS_BANKED_SAW2_SPM_CTL_WAKEUP_CONFIG_SHFT                    0x1
#define HWIO_APCS_BANKED_SAW2_SPM_CTL_SPM_EN_BMSK                           0x1
#define HWIO_APCS_BANKED_SAW2_SPM_CTL_SPM_EN_SHFT                           0x0

#define HWIO_APCS_BANKED_SAW2_SPM_DLY_ADDR                           (APCS_BANKED_SAW2_REG_BASE      + 0x00000034)
#define HWIO_APCS_BANKED_SAW2_SPM_DLY_RMSK                           0x3fffffff
#define HWIO_APCS_BANKED_SAW2_SPM_DLY_IN          \
        in_dword_masked(HWIO_APCS_BANKED_SAW2_SPM_DLY_ADDR, HWIO_APCS_BANKED_SAW2_SPM_DLY_RMSK)
#define HWIO_APCS_BANKED_SAW2_SPM_DLY_INM(m)      \
        in_dword_masked(HWIO_APCS_BANKED_SAW2_SPM_DLY_ADDR, m)
#define HWIO_APCS_BANKED_SAW2_SPM_DLY_OUT(v)      \
        out_dword(HWIO_APCS_BANKED_SAW2_SPM_DLY_ADDR,v)
#define HWIO_APCS_BANKED_SAW2_SPM_DLY_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_BANKED_SAW2_SPM_DLY_ADDR,m,v,HWIO_APCS_BANKED_SAW2_SPM_DLY_IN)
#define HWIO_APCS_BANKED_SAW2_SPM_DLY_DLY3_BMSK                      0x3ff00000
#define HWIO_APCS_BANKED_SAW2_SPM_DLY_DLY3_SHFT                            0x14
#define HWIO_APCS_BANKED_SAW2_SPM_DLY_DLY2_BMSK                         0xffc00
#define HWIO_APCS_BANKED_SAW2_SPM_DLY_DLY2_SHFT                             0xa
#define HWIO_APCS_BANKED_SAW2_SPM_DLY_DLY1_BMSK                           0x3ff
#define HWIO_APCS_BANKED_SAW2_SPM_DLY_DLY1_SHFT                             0x0

#define HWIO_APCS_BANKED_SAW2_SPM_SLP_SEQ_ENTRY_n_ADDR(n)            (APCS_BANKED_SAW2_REG_BASE      + 0x00000080 + 0x4 * (n))
#define HWIO_APCS_BANKED_SAW2_SPM_SLP_SEQ_ENTRY_n_RMSK               0xffffffff
#define HWIO_APCS_BANKED_SAW2_SPM_SLP_SEQ_ENTRY_n_MAXn                       17
#define HWIO_APCS_BANKED_SAW2_SPM_SLP_SEQ_ENTRY_n_INI(n)        \
        in_dword_masked(HWIO_APCS_BANKED_SAW2_SPM_SLP_SEQ_ENTRY_n_ADDR(n), HWIO_APCS_BANKED_SAW2_SPM_SLP_SEQ_ENTRY_n_RMSK)
#define HWIO_APCS_BANKED_SAW2_SPM_SLP_SEQ_ENTRY_n_INMI(n,mask)    \
        in_dword_masked(HWIO_APCS_BANKED_SAW2_SPM_SLP_SEQ_ENTRY_n_ADDR(n), mask)
#define HWIO_APCS_BANKED_SAW2_SPM_SLP_SEQ_ENTRY_n_OUTI(n,val)    \
        out_dword(HWIO_APCS_BANKED_SAW2_SPM_SLP_SEQ_ENTRY_n_ADDR(n),val)
#define HWIO_APCS_BANKED_SAW2_SPM_SLP_SEQ_ENTRY_n_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_APCS_BANKED_SAW2_SPM_SLP_SEQ_ENTRY_n_ADDR(n),mask,val,HWIO_APCS_BANKED_SAW2_SPM_SLP_SEQ_ENTRY_n_INI(n))
#define HWIO_APCS_BANKED_SAW2_SPM_SLP_SEQ_ENTRY_n_CMD3_BMSK          0xff000000
#define HWIO_APCS_BANKED_SAW2_SPM_SLP_SEQ_ENTRY_n_CMD3_SHFT                0x18
#define HWIO_APCS_BANKED_SAW2_SPM_SLP_SEQ_ENTRY_n_CMD2_BMSK            0xff0000
#define HWIO_APCS_BANKED_SAW2_SPM_SLP_SEQ_ENTRY_n_CMD2_SHFT                0x10
#define HWIO_APCS_BANKED_SAW2_SPM_SLP_SEQ_ENTRY_n_CMD1_BMSK              0xff00
#define HWIO_APCS_BANKED_SAW2_SPM_SLP_SEQ_ENTRY_n_CMD1_SHFT                 0x8
#define HWIO_APCS_BANKED_SAW2_SPM_SLP_SEQ_ENTRY_n_CMD0_BMSK                0xff
#define HWIO_APCS_BANKED_SAW2_SPM_SLP_SEQ_ENTRY_n_CMD0_SHFT                 0x0

#define HWIO_APCS_BANKED_SAW2_SPM_PMIC_DATA_n_ADDR(n)                (APCS_BANKED_SAW2_REG_BASE      + 0x00000040 + 0x4 * (n))
#define HWIO_APCS_BANKED_SAW2_SPM_PMIC_DATA_n_RMSK                    0x71700ff
#define HWIO_APCS_BANKED_SAW2_SPM_PMIC_DATA_n_MAXn                            5
#define HWIO_APCS_BANKED_SAW2_SPM_PMIC_DATA_n_INI(n)        \
        in_dword_masked(HWIO_APCS_BANKED_SAW2_SPM_PMIC_DATA_n_ADDR(n), HWIO_APCS_BANKED_SAW2_SPM_PMIC_DATA_n_RMSK)
#define HWIO_APCS_BANKED_SAW2_SPM_PMIC_DATA_n_INMI(n,mask)    \
        in_dword_masked(HWIO_APCS_BANKED_SAW2_SPM_PMIC_DATA_n_ADDR(n), mask)
#define HWIO_APCS_BANKED_SAW2_SPM_PMIC_DATA_n_OUTI(n,val)    \
        out_dword(HWIO_APCS_BANKED_SAW2_SPM_PMIC_DATA_n_ADDR(n),val)
#define HWIO_APCS_BANKED_SAW2_SPM_PMIC_DATA_n_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_APCS_BANKED_SAW2_SPM_PMIC_DATA_n_ADDR(n),mask,val,HWIO_APCS_BANKED_SAW2_SPM_PMIC_DATA_n_INI(n))
#define HWIO_APCS_BANKED_SAW2_SPM_PMIC_DATA_n_DLY_BMSK                0x7000000
#define HWIO_APCS_BANKED_SAW2_SPM_PMIC_DATA_n_DLY_SHFT                     0x18
#define HWIO_APCS_BANKED_SAW2_SPM_PMIC_DATA_n_SIZE_BMSK                0x100000
#define HWIO_APCS_BANKED_SAW2_SPM_PMIC_DATA_n_SIZE_SHFT                    0x14
#define HWIO_APCS_BANKED_SAW2_SPM_PMIC_DATA_n_ADR_IDX_BMSK              0x70000
#define HWIO_APCS_BANKED_SAW2_SPM_PMIC_DATA_n_ADR_IDX_SHFT                 0x10
#define HWIO_APCS_BANKED_SAW2_SPM_PMIC_DATA_n_DATA_BMSK                    0xff
#define HWIO_APCS_BANKED_SAW2_SPM_PMIC_DATA_n_DATA_SHFT                     0x0

#define HWIO_APCS_BANKED_SAW2_VERSION_ADDR                           (APCS_BANKED_SAW2_REG_BASE      + 0x00000fd0)
#define HWIO_APCS_BANKED_SAW2_VERSION_RMSK                           0xffffffff
#define HWIO_APCS_BANKED_SAW2_VERSION_IN          \
        in_dword_masked(HWIO_APCS_BANKED_SAW2_VERSION_ADDR, HWIO_APCS_BANKED_SAW2_VERSION_RMSK)
#define HWIO_APCS_BANKED_SAW2_VERSION_INM(m)      \
        in_dword_masked(HWIO_APCS_BANKED_SAW2_VERSION_ADDR, m)
#define HWIO_APCS_BANKED_SAW2_VERSION_MAJOR_BMSK                     0xf0000000
#define HWIO_APCS_BANKED_SAW2_VERSION_MAJOR_SHFT                           0x1c
#define HWIO_APCS_BANKED_SAW2_VERSION_MINOR_BMSK                      0xfff0000
#define HWIO_APCS_BANKED_SAW2_VERSION_MINOR_SHFT                           0x10
#define HWIO_APCS_BANKED_SAW2_VERSION_STEP_BMSK                          0xffff
#define HWIO_APCS_BANKED_SAW2_VERSION_STEP_SHFT                             0x0

/*----------------------------------------------------------------------------
 * MODULE: APCS_ALIAS0_SAW2
 *--------------------------------------------------------------------------*/

#define APCS_ALIAS0_SAW2_REG_BASE                                    (KPSS_BASE      + 0x00089000)

#define HWIO_APCS_ALIAS0_SAW2_SECURE_ADDR                            (APCS_ALIAS0_SAW2_REG_BASE      + 0x00000000)
#define HWIO_APCS_ALIAS0_SAW2_SECURE_RMSK                                   0x7
#define HWIO_APCS_ALIAS0_SAW2_SECURE_IN          \
        in_dword_masked(HWIO_APCS_ALIAS0_SAW2_SECURE_ADDR, HWIO_APCS_ALIAS0_SAW2_SECURE_RMSK)
#define HWIO_APCS_ALIAS0_SAW2_SECURE_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS0_SAW2_SECURE_ADDR, m)
#define HWIO_APCS_ALIAS0_SAW2_SECURE_OUT(v)      \
        out_dword(HWIO_APCS_ALIAS0_SAW2_SECURE_ADDR,v)
#define HWIO_APCS_ALIAS0_SAW2_SECURE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_ALIAS0_SAW2_SECURE_ADDR,m,v,HWIO_APCS_ALIAS0_SAW2_SECURE_IN)
#define HWIO_APCS_ALIAS0_SAW2_SECURE_SAW_CTL_BMSK                           0x4
#define HWIO_APCS_ALIAS0_SAW2_SECURE_SAW_CTL_SHFT                           0x2
#define HWIO_APCS_ALIAS0_SAW2_SECURE_PWR_CTL_BMSK                           0x2
#define HWIO_APCS_ALIAS0_SAW2_SECURE_PWR_CTL_SHFT                           0x1
#define HWIO_APCS_ALIAS0_SAW2_SECURE_VLT_CTL_BMSK                           0x1
#define HWIO_APCS_ALIAS0_SAW2_SECURE_VLT_CTL_SHFT                           0x0

#define HWIO_APCS_ALIAS0_SAW2_ID_ADDR                                (APCS_ALIAS0_SAW2_REG_BASE      + 0x00000004)
#define HWIO_APCS_ALIAS0_SAW2_ID_RMSK                                0x3f1f1f7f
#define HWIO_APCS_ALIAS0_SAW2_ID_IN          \
        in_dword_masked(HWIO_APCS_ALIAS0_SAW2_ID_ADDR, HWIO_APCS_ALIAS0_SAW2_ID_RMSK)
#define HWIO_APCS_ALIAS0_SAW2_ID_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS0_SAW2_ID_ADDR, m)
#define HWIO_APCS_ALIAS0_SAW2_ID_NUM_SPM_ENTRY_BMSK                  0x3f000000
#define HWIO_APCS_ALIAS0_SAW2_ID_NUM_SPM_ENTRY_SHFT                        0x18
#define HWIO_APCS_ALIAS0_SAW2_ID_NUM_PWR_CTL_BMSK                      0x1f0000
#define HWIO_APCS_ALIAS0_SAW2_ID_NUM_PWR_CTL_SHFT                          0x10
#define HWIO_APCS_ALIAS0_SAW2_ID_PMIC_DATA_WIDTH_BMSK                    0x1f00
#define HWIO_APCS_ALIAS0_SAW2_ID_PMIC_DATA_WIDTH_SHFT                       0x8
#define HWIO_APCS_ALIAS0_SAW2_ID_NUM_PMIC_DATA_BMSK                        0x70
#define HWIO_APCS_ALIAS0_SAW2_ID_NUM_PMIC_DATA_SHFT                         0x4
#define HWIO_APCS_ALIAS0_SAW2_ID_CFG_NS_ACCESS_BMSK                         0x8
#define HWIO_APCS_ALIAS0_SAW2_ID_CFG_NS_ACCESS_SHFT                         0x3
#define HWIO_APCS_ALIAS0_SAW2_ID_PMIC_ARB_INTF_BMSK                         0x4
#define HWIO_APCS_ALIAS0_SAW2_ID_PMIC_ARB_INTF_SHFT                         0x2
#define HWIO_APCS_ALIAS0_SAW2_ID_AVS_PRESENT_BMSK                           0x2
#define HWIO_APCS_ALIAS0_SAW2_ID_AVS_PRESENT_SHFT                           0x1
#define HWIO_APCS_ALIAS0_SAW2_ID_SPM_PRESENT_BMSK                           0x1
#define HWIO_APCS_ALIAS0_SAW2_ID_SPM_PRESENT_SHFT                           0x0

#define HWIO_APCS_ALIAS0_SAW2_CFG_ADDR                               (APCS_ALIAS0_SAW2_REG_BASE      + 0x00000008)
#define HWIO_APCS_ALIAS0_SAW2_CFG_RMSK                                    0x31f
#define HWIO_APCS_ALIAS0_SAW2_CFG_IN          \
        in_dword_masked(HWIO_APCS_ALIAS0_SAW2_CFG_ADDR, HWIO_APCS_ALIAS0_SAW2_CFG_RMSK)
#define HWIO_APCS_ALIAS0_SAW2_CFG_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS0_SAW2_CFG_ADDR, m)
#define HWIO_APCS_ALIAS0_SAW2_CFG_OUT(v)      \
        out_dword(HWIO_APCS_ALIAS0_SAW2_CFG_ADDR,v)
#define HWIO_APCS_ALIAS0_SAW2_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_ALIAS0_SAW2_CFG_ADDR,m,v,HWIO_APCS_ALIAS0_SAW2_CFG_IN)
#define HWIO_APCS_ALIAS0_SAW2_CFG_TEST_BUS_EN_BMSK                        0x200
#define HWIO_APCS_ALIAS0_SAW2_CFG_TEST_BUS_EN_SHFT                          0x9
#define HWIO_APCS_ALIAS0_SAW2_CFG_FRC_REF_CLK_ON_BMSK                     0x100
#define HWIO_APCS_ALIAS0_SAW2_CFG_FRC_REF_CLK_ON_SHFT                       0x8
#define HWIO_APCS_ALIAS0_SAW2_CFG_CLK_DIV_BMSK                             0x1f
#define HWIO_APCS_ALIAS0_SAW2_CFG_CLK_DIV_SHFT                              0x0

#define HWIO_APCS_ALIAS0_SAW2_SPM_STS_ADDR                           (APCS_ALIAS0_SAW2_REG_BASE      + 0x0000000c)
#define HWIO_APCS_ALIAS0_SAW2_SPM_STS_RMSK                           0xfffff1ff
#define HWIO_APCS_ALIAS0_SAW2_SPM_STS_IN          \
        in_dword_masked(HWIO_APCS_ALIAS0_SAW2_SPM_STS_ADDR, HWIO_APCS_ALIAS0_SAW2_SPM_STS_RMSK)
#define HWIO_APCS_ALIAS0_SAW2_SPM_STS_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS0_SAW2_SPM_STS_ADDR, m)
#define HWIO_APCS_ALIAS0_SAW2_SPM_STS_CURR_PWR_CTL_BMSK              0xffff0000
#define HWIO_APCS_ALIAS0_SAW2_SPM_STS_CURR_PWR_CTL_SHFT                    0x10
#define HWIO_APCS_ALIAS0_SAW2_SPM_STS_SHTDWN_REQ_BMSK                    0x8000
#define HWIO_APCS_ALIAS0_SAW2_SPM_STS_SHTDWN_REQ_SHFT                       0xf
#define HWIO_APCS_ALIAS0_SAW2_SPM_STS_SHTDWN_ACK_BMSK                    0x4000
#define HWIO_APCS_ALIAS0_SAW2_SPM_STS_SHTDWN_ACK_SHFT                       0xe
#define HWIO_APCS_ALIAS0_SAW2_SPM_STS_BRNGUP_REQ_BMSK                    0x2000
#define HWIO_APCS_ALIAS0_SAW2_SPM_STS_BRNGUP_REQ_SHFT                       0xd
#define HWIO_APCS_ALIAS0_SAW2_SPM_STS_BRNGUP_ACK_BMSK                    0x1000
#define HWIO_APCS_ALIAS0_SAW2_SPM_STS_BRNGUP_ACK_SHFT                       0xc
#define HWIO_APCS_ALIAS0_SAW2_SPM_STS_RPM_STATE_BMSK                      0x180
#define HWIO_APCS_ALIAS0_SAW2_SPM_STS_RPM_STATE_SHFT                        0x7
#define HWIO_APCS_ALIAS0_SAW2_SPM_STS_SPM_CMD_ADDR_BMSK                    0x7f
#define HWIO_APCS_ALIAS0_SAW2_SPM_STS_SPM_CMD_ADDR_SHFT                     0x0

#define HWIO_APCS_ALIAS0_SAW2_AVS_STS_ADDR                           (APCS_ALIAS0_SAW2_REG_BASE      + 0x00000010)
#define HWIO_APCS_ALIAS0_SAW2_AVS_STS_RMSK                             0xff003f
#define HWIO_APCS_ALIAS0_SAW2_AVS_STS_IN          \
        in_dword_masked(HWIO_APCS_ALIAS0_SAW2_AVS_STS_ADDR, HWIO_APCS_ALIAS0_SAW2_AVS_STS_RMSK)
#define HWIO_APCS_ALIAS0_SAW2_AVS_STS_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS0_SAW2_AVS_STS_ADDR, m)
#define HWIO_APCS_ALIAS0_SAW2_AVS_STS_SPM_EVENT_BMSK                   0xff0000
#define HWIO_APCS_ALIAS0_SAW2_AVS_STS_SPM_EVENT_SHFT                       0x10
#define HWIO_APCS_ALIAS0_SAW2_AVS_STS_MAX_INT_BMSK                         0x20
#define HWIO_APCS_ALIAS0_SAW2_AVS_STS_MAX_INT_SHFT                          0x5
#define HWIO_APCS_ALIAS0_SAW2_AVS_STS_MIN_INT_BMSK                         0x10
#define HWIO_APCS_ALIAS0_SAW2_AVS_STS_MIN_INT_SHFT                          0x4
#define HWIO_APCS_ALIAS0_SAW2_AVS_STS_CPU_UP_BMSK                           0x8
#define HWIO_APCS_ALIAS0_SAW2_AVS_STS_CPU_UP_SHFT                           0x3
#define HWIO_APCS_ALIAS0_SAW2_AVS_STS_CPU_DN_BMSK                           0x4
#define HWIO_APCS_ALIAS0_SAW2_AVS_STS_CPU_DN_SHFT                           0x2
#define HWIO_APCS_ALIAS0_SAW2_AVS_STS_SW_WR_PEND_BMSK                       0x2
#define HWIO_APCS_ALIAS0_SAW2_AVS_STS_SW_WR_PEND_SHFT                       0x1
#define HWIO_APCS_ALIAS0_SAW2_AVS_STS_AVS_STATE_BMSK                        0x1
#define HWIO_APCS_ALIAS0_SAW2_AVS_STS_AVS_STATE_SHFT                        0x0

#define HWIO_APCS_ALIAS0_SAW2_PMIC_STS_ADDR                          (APCS_ALIAS0_SAW2_REG_BASE      + 0x00000014)
#define HWIO_APCS_ALIAS0_SAW2_PMIC_STS_RMSK                          0x3ff300ff
#define HWIO_APCS_ALIAS0_SAW2_PMIC_STS_IN          \
        in_dword_masked(HWIO_APCS_ALIAS0_SAW2_PMIC_STS_ADDR, HWIO_APCS_ALIAS0_SAW2_PMIC_STS_RMSK)
#define HWIO_APCS_ALIAS0_SAW2_PMIC_STS_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS0_SAW2_PMIC_STS_ADDR, m)
#define HWIO_APCS_ALIAS0_SAW2_PMIC_STS_CURR_DLY_BMSK                 0x3ff00000
#define HWIO_APCS_ALIAS0_SAW2_PMIC_STS_CURR_DLY_SHFT                       0x14
#define HWIO_APCS_ALIAS0_SAW2_PMIC_STS_PMIC_STATE_BMSK                  0x30000
#define HWIO_APCS_ALIAS0_SAW2_PMIC_STS_PMIC_STATE_SHFT                     0x10
#define HWIO_APCS_ALIAS0_SAW2_PMIC_STS_CURR_PMIC_DATA_BMSK                 0xff
#define HWIO_APCS_ALIAS0_SAW2_PMIC_STS_CURR_PMIC_DATA_SHFT                  0x0

#define HWIO_APCS_ALIAS0_SAW2_RST_ADDR                               (APCS_ALIAS0_SAW2_REG_BASE      + 0x00000018)
#define HWIO_APCS_ALIAS0_SAW2_RST_RMSK                                      0x1
#define HWIO_APCS_ALIAS0_SAW2_RST_IN          \
        in_dword_masked(HWIO_APCS_ALIAS0_SAW2_RST_ADDR, HWIO_APCS_ALIAS0_SAW2_RST_RMSK)
#define HWIO_APCS_ALIAS0_SAW2_RST_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS0_SAW2_RST_ADDR, m)
#define HWIO_APCS_ALIAS0_SAW2_RST_OUT(v)      \
        out_dword(HWIO_APCS_ALIAS0_SAW2_RST_ADDR,v)
#define HWIO_APCS_ALIAS0_SAW2_RST_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_ALIAS0_SAW2_RST_ADDR,m,v,HWIO_APCS_ALIAS0_SAW2_RST_IN)
#define HWIO_APCS_ALIAS0_SAW2_RST_RST_BMSK                                  0x1
#define HWIO_APCS_ALIAS0_SAW2_RST_RST_SHFT                                  0x0

#define HWIO_APCS_ALIAS0_SAW2_VCTL_ADDR                              (APCS_ALIAS0_SAW2_REG_BASE      + 0x0000001c)
#define HWIO_APCS_ALIAS0_SAW2_VCTL_RMSK                                0x1700ff
#define HWIO_APCS_ALIAS0_SAW2_VCTL_IN          \
        in_dword_masked(HWIO_APCS_ALIAS0_SAW2_VCTL_ADDR, HWIO_APCS_ALIAS0_SAW2_VCTL_RMSK)
#define HWIO_APCS_ALIAS0_SAW2_VCTL_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS0_SAW2_VCTL_ADDR, m)
#define HWIO_APCS_ALIAS0_SAW2_VCTL_OUT(v)      \
        out_dword(HWIO_APCS_ALIAS0_SAW2_VCTL_ADDR,v)
#define HWIO_APCS_ALIAS0_SAW2_VCTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_ALIAS0_SAW2_VCTL_ADDR,m,v,HWIO_APCS_ALIAS0_SAW2_VCTL_IN)
#define HWIO_APCS_ALIAS0_SAW2_VCTL_SIZE_BMSK                           0x100000
#define HWIO_APCS_ALIAS0_SAW2_VCTL_SIZE_SHFT                               0x14
#define HWIO_APCS_ALIAS0_SAW2_VCTL_ADR_IDX_BMSK                         0x70000
#define HWIO_APCS_ALIAS0_SAW2_VCTL_ADR_IDX_SHFT                            0x10
#define HWIO_APCS_ALIAS0_SAW2_VCTL_PMIC_DATA_BMSK                          0xff
#define HWIO_APCS_ALIAS0_SAW2_VCTL_PMIC_DATA_SHFT                           0x0

#define HWIO_APCS_ALIAS0_SAW2_AVS_CTL_ADDR                           (APCS_ALIAS0_SAW2_REG_BASE      + 0x00000020)
#define HWIO_APCS_ALIAS0_SAW2_AVS_CTL_RMSK                               0x130f
#define HWIO_APCS_ALIAS0_SAW2_AVS_CTL_IN          \
        in_dword_masked(HWIO_APCS_ALIAS0_SAW2_AVS_CTL_ADDR, HWIO_APCS_ALIAS0_SAW2_AVS_CTL_RMSK)
#define HWIO_APCS_ALIAS0_SAW2_AVS_CTL_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS0_SAW2_AVS_CTL_ADDR, m)
#define HWIO_APCS_ALIAS0_SAW2_AVS_CTL_OUT(v)      \
        out_dword(HWIO_APCS_ALIAS0_SAW2_AVS_CTL_ADDR,v)
#define HWIO_APCS_ALIAS0_SAW2_AVS_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_ALIAS0_SAW2_AVS_CTL_ADDR,m,v,HWIO_APCS_ALIAS0_SAW2_AVS_CTL_IN)
#define HWIO_APCS_ALIAS0_SAW2_AVS_CTL_VLVL_WIDTH_BMSK                    0x1000
#define HWIO_APCS_ALIAS0_SAW2_AVS_CTL_VLVL_WIDTH_SHFT                       0xc
#define HWIO_APCS_ALIAS0_SAW2_AVS_CTL_VLVL_STEP_BMSK                      0x300
#define HWIO_APCS_ALIAS0_SAW2_AVS_CTL_VLVL_STEP_SHFT                        0x8
#define HWIO_APCS_ALIAS0_SAW2_AVS_CTL_SW_DONE_INT_EN_BMSK                   0x8
#define HWIO_APCS_ALIAS0_SAW2_AVS_CTL_SW_DONE_INT_EN_SHFT                   0x3
#define HWIO_APCS_ALIAS0_SAW2_AVS_CTL_MAX_INT_EN_BMSK                       0x4
#define HWIO_APCS_ALIAS0_SAW2_AVS_CTL_MAX_INT_EN_SHFT                       0x2
#define HWIO_APCS_ALIAS0_SAW2_AVS_CTL_MIN_INT_EN_BMSK                       0x2
#define HWIO_APCS_ALIAS0_SAW2_AVS_CTL_MIN_INT_EN_SHFT                       0x1
#define HWIO_APCS_ALIAS0_SAW2_AVS_CTL_EN_BMSK                               0x1
#define HWIO_APCS_ALIAS0_SAW2_AVS_CTL_EN_SHFT                               0x0

#define HWIO_APCS_ALIAS0_SAW2_AVS_LIMIT_ADDR                         (APCS_ALIAS0_SAW2_REG_BASE      + 0x00000024)
#define HWIO_APCS_ALIAS0_SAW2_AVS_LIMIT_RMSK                           0xff00ff
#define HWIO_APCS_ALIAS0_SAW2_AVS_LIMIT_IN          \
        in_dword_masked(HWIO_APCS_ALIAS0_SAW2_AVS_LIMIT_ADDR, HWIO_APCS_ALIAS0_SAW2_AVS_LIMIT_RMSK)
#define HWIO_APCS_ALIAS0_SAW2_AVS_LIMIT_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS0_SAW2_AVS_LIMIT_ADDR, m)
#define HWIO_APCS_ALIAS0_SAW2_AVS_LIMIT_OUT(v)      \
        out_dword(HWIO_APCS_ALIAS0_SAW2_AVS_LIMIT_ADDR,v)
#define HWIO_APCS_ALIAS0_SAW2_AVS_LIMIT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_ALIAS0_SAW2_AVS_LIMIT_ADDR,m,v,HWIO_APCS_ALIAS0_SAW2_AVS_LIMIT_IN)
#define HWIO_APCS_ALIAS0_SAW2_AVS_LIMIT_MAX_VLVL_BMSK                  0xff0000
#define HWIO_APCS_ALIAS0_SAW2_AVS_LIMIT_MAX_VLVL_SHFT                      0x10
#define HWIO_APCS_ALIAS0_SAW2_AVS_LIMIT_MIN_VLVL_BMSK                      0xff
#define HWIO_APCS_ALIAS0_SAW2_AVS_LIMIT_MIN_VLVL_SHFT                       0x0

#define HWIO_APCS_ALIAS0_SAW2_AVS_DLY_ADDR                           (APCS_ALIAS0_SAW2_REG_BASE      + 0x00000028)
#define HWIO_APCS_ALIAS0_SAW2_AVS_DLY_RMSK                                0x3ff
#define HWIO_APCS_ALIAS0_SAW2_AVS_DLY_IN          \
        in_dword_masked(HWIO_APCS_ALIAS0_SAW2_AVS_DLY_ADDR, HWIO_APCS_ALIAS0_SAW2_AVS_DLY_RMSK)
#define HWIO_APCS_ALIAS0_SAW2_AVS_DLY_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS0_SAW2_AVS_DLY_ADDR, m)
#define HWIO_APCS_ALIAS0_SAW2_AVS_DLY_OUT(v)      \
        out_dword(HWIO_APCS_ALIAS0_SAW2_AVS_DLY_ADDR,v)
#define HWIO_APCS_ALIAS0_SAW2_AVS_DLY_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_ALIAS0_SAW2_AVS_DLY_ADDR,m,v,HWIO_APCS_ALIAS0_SAW2_AVS_DLY_IN)
#define HWIO_APCS_ALIAS0_SAW2_AVS_DLY_AVS_DELAY_BMSK                      0x3ff
#define HWIO_APCS_ALIAS0_SAW2_AVS_DLY_AVS_DELAY_SHFT                        0x0

#define HWIO_APCS_ALIAS0_SAW2_AVS_HYSTERESIS_ADDR                    (APCS_ALIAS0_SAW2_REG_BASE      + 0x0000002c)
#define HWIO_APCS_ALIAS0_SAW2_AVS_HYSTERESIS_RMSK                      0xff00ff
#define HWIO_APCS_ALIAS0_SAW2_AVS_HYSTERESIS_IN          \
        in_dword_masked(HWIO_APCS_ALIAS0_SAW2_AVS_HYSTERESIS_ADDR, HWIO_APCS_ALIAS0_SAW2_AVS_HYSTERESIS_RMSK)
#define HWIO_APCS_ALIAS0_SAW2_AVS_HYSTERESIS_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS0_SAW2_AVS_HYSTERESIS_ADDR, m)
#define HWIO_APCS_ALIAS0_SAW2_AVS_HYSTERESIS_OUT(v)      \
        out_dword(HWIO_APCS_ALIAS0_SAW2_AVS_HYSTERESIS_ADDR,v)
#define HWIO_APCS_ALIAS0_SAW2_AVS_HYSTERESIS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_ALIAS0_SAW2_AVS_HYSTERESIS_ADDR,m,v,HWIO_APCS_ALIAS0_SAW2_AVS_HYSTERESIS_IN)
#define HWIO_APCS_ALIAS0_SAW2_AVS_HYSTERESIS_DN_COUNT_BMSK             0xff0000
#define HWIO_APCS_ALIAS0_SAW2_AVS_HYSTERESIS_DN_COUNT_SHFT                 0x10
#define HWIO_APCS_ALIAS0_SAW2_AVS_HYSTERESIS_UP_COUNT_BMSK                 0xff
#define HWIO_APCS_ALIAS0_SAW2_AVS_HYSTERESIS_UP_COUNT_SHFT                  0x0

#define HWIO_APCS_ALIAS0_SAW2_SPM_CTL_ADDR                           (APCS_ALIAS0_SAW2_REG_BASE      + 0x00000030)
#define HWIO_APCS_ALIAS0_SAW2_SPM_CTL_RMSK                              0x107ff
#define HWIO_APCS_ALIAS0_SAW2_SPM_CTL_IN          \
        in_dword_masked(HWIO_APCS_ALIAS0_SAW2_SPM_CTL_ADDR, HWIO_APCS_ALIAS0_SAW2_SPM_CTL_RMSK)
#define HWIO_APCS_ALIAS0_SAW2_SPM_CTL_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS0_SAW2_SPM_CTL_ADDR, m)
#define HWIO_APCS_ALIAS0_SAW2_SPM_CTL_OUT(v)      \
        out_dword(HWIO_APCS_ALIAS0_SAW2_SPM_CTL_ADDR,v)
#define HWIO_APCS_ALIAS0_SAW2_SPM_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_ALIAS0_SAW2_SPM_CTL_ADDR,m,v,HWIO_APCS_ALIAS0_SAW2_SPM_CTL_IN)
#define HWIO_APCS_ALIAS0_SAW2_SPM_CTL_SPM_SYS_PC_MODE_BMSK              0x10000
#define HWIO_APCS_ALIAS0_SAW2_SPM_CTL_SPM_SYS_PC_MODE_SHFT                 0x10
#define HWIO_APCS_ALIAS0_SAW2_SPM_CTL_SPM_START_ADR_BMSK                  0x7f0
#define HWIO_APCS_ALIAS0_SAW2_SPM_CTL_SPM_START_ADR_SHFT                    0x4
#define HWIO_APCS_ALIAS0_SAW2_SPM_CTL_ISAR_BMSK                             0x8
#define HWIO_APCS_ALIAS0_SAW2_SPM_CTL_ISAR_SHFT                             0x3
#define HWIO_APCS_ALIAS0_SAW2_SPM_CTL_WAKEUP_CONFIG_BMSK                    0x6
#define HWIO_APCS_ALIAS0_SAW2_SPM_CTL_WAKEUP_CONFIG_SHFT                    0x1
#define HWIO_APCS_ALIAS0_SAW2_SPM_CTL_SPM_EN_BMSK                           0x1
#define HWIO_APCS_ALIAS0_SAW2_SPM_CTL_SPM_EN_SHFT                           0x0

#define HWIO_APCS_ALIAS0_SAW2_SPM_DLY_ADDR                           (APCS_ALIAS0_SAW2_REG_BASE      + 0x00000034)
#define HWIO_APCS_ALIAS0_SAW2_SPM_DLY_RMSK                           0x3fffffff
#define HWIO_APCS_ALIAS0_SAW2_SPM_DLY_IN          \
        in_dword_masked(HWIO_APCS_ALIAS0_SAW2_SPM_DLY_ADDR, HWIO_APCS_ALIAS0_SAW2_SPM_DLY_RMSK)
#define HWIO_APCS_ALIAS0_SAW2_SPM_DLY_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS0_SAW2_SPM_DLY_ADDR, m)
#define HWIO_APCS_ALIAS0_SAW2_SPM_DLY_OUT(v)      \
        out_dword(HWIO_APCS_ALIAS0_SAW2_SPM_DLY_ADDR,v)
#define HWIO_APCS_ALIAS0_SAW2_SPM_DLY_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_ALIAS0_SAW2_SPM_DLY_ADDR,m,v,HWIO_APCS_ALIAS0_SAW2_SPM_DLY_IN)
#define HWIO_APCS_ALIAS0_SAW2_SPM_DLY_DLY3_BMSK                      0x3ff00000
#define HWIO_APCS_ALIAS0_SAW2_SPM_DLY_DLY3_SHFT                            0x14
#define HWIO_APCS_ALIAS0_SAW2_SPM_DLY_DLY2_BMSK                         0xffc00
#define HWIO_APCS_ALIAS0_SAW2_SPM_DLY_DLY2_SHFT                             0xa
#define HWIO_APCS_ALIAS0_SAW2_SPM_DLY_DLY1_BMSK                           0x3ff
#define HWIO_APCS_ALIAS0_SAW2_SPM_DLY_DLY1_SHFT                             0x0

#define HWIO_APCS_ALIAS0_SAW2_SPM_SLP_SEQ_ENTRY_n_ADDR(n)            (APCS_ALIAS0_SAW2_REG_BASE      + 0x00000080 + 0x4 * (n))
#define HWIO_APCS_ALIAS0_SAW2_SPM_SLP_SEQ_ENTRY_n_RMSK               0xffffffff
#define HWIO_APCS_ALIAS0_SAW2_SPM_SLP_SEQ_ENTRY_n_MAXn                       17
#define HWIO_APCS_ALIAS0_SAW2_SPM_SLP_SEQ_ENTRY_n_INI(n)        \
        in_dword_masked(HWIO_APCS_ALIAS0_SAW2_SPM_SLP_SEQ_ENTRY_n_ADDR(n), HWIO_APCS_ALIAS0_SAW2_SPM_SLP_SEQ_ENTRY_n_RMSK)
#define HWIO_APCS_ALIAS0_SAW2_SPM_SLP_SEQ_ENTRY_n_INMI(n,mask)    \
        in_dword_masked(HWIO_APCS_ALIAS0_SAW2_SPM_SLP_SEQ_ENTRY_n_ADDR(n), mask)
#define HWIO_APCS_ALIAS0_SAW2_SPM_SLP_SEQ_ENTRY_n_OUTI(n,val)    \
        out_dword(HWIO_APCS_ALIAS0_SAW2_SPM_SLP_SEQ_ENTRY_n_ADDR(n),val)
#define HWIO_APCS_ALIAS0_SAW2_SPM_SLP_SEQ_ENTRY_n_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_APCS_ALIAS0_SAW2_SPM_SLP_SEQ_ENTRY_n_ADDR(n),mask,val,HWIO_APCS_ALIAS0_SAW2_SPM_SLP_SEQ_ENTRY_n_INI(n))
#define HWIO_APCS_ALIAS0_SAW2_SPM_SLP_SEQ_ENTRY_n_CMD3_BMSK          0xff000000
#define HWIO_APCS_ALIAS0_SAW2_SPM_SLP_SEQ_ENTRY_n_CMD3_SHFT                0x18
#define HWIO_APCS_ALIAS0_SAW2_SPM_SLP_SEQ_ENTRY_n_CMD2_BMSK            0xff0000
#define HWIO_APCS_ALIAS0_SAW2_SPM_SLP_SEQ_ENTRY_n_CMD2_SHFT                0x10
#define HWIO_APCS_ALIAS0_SAW2_SPM_SLP_SEQ_ENTRY_n_CMD1_BMSK              0xff00
#define HWIO_APCS_ALIAS0_SAW2_SPM_SLP_SEQ_ENTRY_n_CMD1_SHFT                 0x8
#define HWIO_APCS_ALIAS0_SAW2_SPM_SLP_SEQ_ENTRY_n_CMD0_BMSK                0xff
#define HWIO_APCS_ALIAS0_SAW2_SPM_SLP_SEQ_ENTRY_n_CMD0_SHFT                 0x0

#define HWIO_APCS_ALIAS0_SAW2_SPM_PMIC_DATA_n_ADDR(n)                (APCS_ALIAS0_SAW2_REG_BASE      + 0x00000040 + 0x4 * (n))
#define HWIO_APCS_ALIAS0_SAW2_SPM_PMIC_DATA_n_RMSK                    0x71700ff
#define HWIO_APCS_ALIAS0_SAW2_SPM_PMIC_DATA_n_MAXn                            5
#define HWIO_APCS_ALIAS0_SAW2_SPM_PMIC_DATA_n_INI(n)        \
        in_dword_masked(HWIO_APCS_ALIAS0_SAW2_SPM_PMIC_DATA_n_ADDR(n), HWIO_APCS_ALIAS0_SAW2_SPM_PMIC_DATA_n_RMSK)
#define HWIO_APCS_ALIAS0_SAW2_SPM_PMIC_DATA_n_INMI(n,mask)    \
        in_dword_masked(HWIO_APCS_ALIAS0_SAW2_SPM_PMIC_DATA_n_ADDR(n), mask)
#define HWIO_APCS_ALIAS0_SAW2_SPM_PMIC_DATA_n_OUTI(n,val)    \
        out_dword(HWIO_APCS_ALIAS0_SAW2_SPM_PMIC_DATA_n_ADDR(n),val)
#define HWIO_APCS_ALIAS0_SAW2_SPM_PMIC_DATA_n_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_APCS_ALIAS0_SAW2_SPM_PMIC_DATA_n_ADDR(n),mask,val,HWIO_APCS_ALIAS0_SAW2_SPM_PMIC_DATA_n_INI(n))
#define HWIO_APCS_ALIAS0_SAW2_SPM_PMIC_DATA_n_DLY_BMSK                0x7000000
#define HWIO_APCS_ALIAS0_SAW2_SPM_PMIC_DATA_n_DLY_SHFT                     0x18
#define HWIO_APCS_ALIAS0_SAW2_SPM_PMIC_DATA_n_SIZE_BMSK                0x100000
#define HWIO_APCS_ALIAS0_SAW2_SPM_PMIC_DATA_n_SIZE_SHFT                    0x14
#define HWIO_APCS_ALIAS0_SAW2_SPM_PMIC_DATA_n_ADR_IDX_BMSK              0x70000
#define HWIO_APCS_ALIAS0_SAW2_SPM_PMIC_DATA_n_ADR_IDX_SHFT                 0x10
#define HWIO_APCS_ALIAS0_SAW2_SPM_PMIC_DATA_n_DATA_BMSK                    0xff
#define HWIO_APCS_ALIAS0_SAW2_SPM_PMIC_DATA_n_DATA_SHFT                     0x0

#define HWIO_APCS_ALIAS0_SAW2_VERSION_ADDR                           (APCS_ALIAS0_SAW2_REG_BASE      + 0x00000fd0)
#define HWIO_APCS_ALIAS0_SAW2_VERSION_RMSK                           0xffffffff
#define HWIO_APCS_ALIAS0_SAW2_VERSION_IN          \
        in_dword_masked(HWIO_APCS_ALIAS0_SAW2_VERSION_ADDR, HWIO_APCS_ALIAS0_SAW2_VERSION_RMSK)
#define HWIO_APCS_ALIAS0_SAW2_VERSION_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS0_SAW2_VERSION_ADDR, m)
#define HWIO_APCS_ALIAS0_SAW2_VERSION_MAJOR_BMSK                     0xf0000000
#define HWIO_APCS_ALIAS0_SAW2_VERSION_MAJOR_SHFT                           0x1c
#define HWIO_APCS_ALIAS0_SAW2_VERSION_MINOR_BMSK                      0xfff0000
#define HWIO_APCS_ALIAS0_SAW2_VERSION_MINOR_SHFT                           0x10
#define HWIO_APCS_ALIAS0_SAW2_VERSION_STEP_BMSK                          0xffff
#define HWIO_APCS_ALIAS0_SAW2_VERSION_STEP_SHFT                             0x0

/*----------------------------------------------------------------------------
 * MODULE: APCS_ALIAS1_SAW2
 *--------------------------------------------------------------------------*/

#define APCS_ALIAS1_SAW2_REG_BASE                                    (KPSS_BASE      + 0x00099000)

#define HWIO_APCS_ALIAS1_SAW2_SECURE_ADDR                            (APCS_ALIAS1_SAW2_REG_BASE      + 0x00000000)
#define HWIO_APCS_ALIAS1_SAW2_SECURE_RMSK                                   0x7
#define HWIO_APCS_ALIAS1_SAW2_SECURE_IN          \
        in_dword_masked(HWIO_APCS_ALIAS1_SAW2_SECURE_ADDR, HWIO_APCS_ALIAS1_SAW2_SECURE_RMSK)
#define HWIO_APCS_ALIAS1_SAW2_SECURE_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS1_SAW2_SECURE_ADDR, m)
#define HWIO_APCS_ALIAS1_SAW2_SECURE_OUT(v)      \
        out_dword(HWIO_APCS_ALIAS1_SAW2_SECURE_ADDR,v)
#define HWIO_APCS_ALIAS1_SAW2_SECURE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_ALIAS1_SAW2_SECURE_ADDR,m,v,HWIO_APCS_ALIAS1_SAW2_SECURE_IN)
#define HWIO_APCS_ALIAS1_SAW2_SECURE_SAW_CTL_BMSK                           0x4
#define HWIO_APCS_ALIAS1_SAW2_SECURE_SAW_CTL_SHFT                           0x2
#define HWIO_APCS_ALIAS1_SAW2_SECURE_PWR_CTL_BMSK                           0x2
#define HWIO_APCS_ALIAS1_SAW2_SECURE_PWR_CTL_SHFT                           0x1
#define HWIO_APCS_ALIAS1_SAW2_SECURE_VLT_CTL_BMSK                           0x1
#define HWIO_APCS_ALIAS1_SAW2_SECURE_VLT_CTL_SHFT                           0x0

#define HWIO_APCS_ALIAS1_SAW2_ID_ADDR                                (APCS_ALIAS1_SAW2_REG_BASE      + 0x00000004)
#define HWIO_APCS_ALIAS1_SAW2_ID_RMSK                                0x3f1f1f7f
#define HWIO_APCS_ALIAS1_SAW2_ID_IN          \
        in_dword_masked(HWIO_APCS_ALIAS1_SAW2_ID_ADDR, HWIO_APCS_ALIAS1_SAW2_ID_RMSK)
#define HWIO_APCS_ALIAS1_SAW2_ID_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS1_SAW2_ID_ADDR, m)
#define HWIO_APCS_ALIAS1_SAW2_ID_NUM_SPM_ENTRY_BMSK                  0x3f000000
#define HWIO_APCS_ALIAS1_SAW2_ID_NUM_SPM_ENTRY_SHFT                        0x18
#define HWIO_APCS_ALIAS1_SAW2_ID_NUM_PWR_CTL_BMSK                      0x1f0000
#define HWIO_APCS_ALIAS1_SAW2_ID_NUM_PWR_CTL_SHFT                          0x10
#define HWIO_APCS_ALIAS1_SAW2_ID_PMIC_DATA_WIDTH_BMSK                    0x1f00
#define HWIO_APCS_ALIAS1_SAW2_ID_PMIC_DATA_WIDTH_SHFT                       0x8
#define HWIO_APCS_ALIAS1_SAW2_ID_NUM_PMIC_DATA_BMSK                        0x70
#define HWIO_APCS_ALIAS1_SAW2_ID_NUM_PMIC_DATA_SHFT                         0x4
#define HWIO_APCS_ALIAS1_SAW2_ID_CFG_NS_ACCESS_BMSK                         0x8
#define HWIO_APCS_ALIAS1_SAW2_ID_CFG_NS_ACCESS_SHFT                         0x3
#define HWIO_APCS_ALIAS1_SAW2_ID_PMIC_ARB_INTF_BMSK                         0x4
#define HWIO_APCS_ALIAS1_SAW2_ID_PMIC_ARB_INTF_SHFT                         0x2
#define HWIO_APCS_ALIAS1_SAW2_ID_AVS_PRESENT_BMSK                           0x2
#define HWIO_APCS_ALIAS1_SAW2_ID_AVS_PRESENT_SHFT                           0x1
#define HWIO_APCS_ALIAS1_SAW2_ID_SPM_PRESENT_BMSK                           0x1
#define HWIO_APCS_ALIAS1_SAW2_ID_SPM_PRESENT_SHFT                           0x0

#define HWIO_APCS_ALIAS1_SAW2_CFG_ADDR                               (APCS_ALIAS1_SAW2_REG_BASE      + 0x00000008)
#define HWIO_APCS_ALIAS1_SAW2_CFG_RMSK                                    0x31f
#define HWIO_APCS_ALIAS1_SAW2_CFG_IN          \
        in_dword_masked(HWIO_APCS_ALIAS1_SAW2_CFG_ADDR, HWIO_APCS_ALIAS1_SAW2_CFG_RMSK)
#define HWIO_APCS_ALIAS1_SAW2_CFG_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS1_SAW2_CFG_ADDR, m)
#define HWIO_APCS_ALIAS1_SAW2_CFG_OUT(v)      \
        out_dword(HWIO_APCS_ALIAS1_SAW2_CFG_ADDR,v)
#define HWIO_APCS_ALIAS1_SAW2_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_ALIAS1_SAW2_CFG_ADDR,m,v,HWIO_APCS_ALIAS1_SAW2_CFG_IN)
#define HWIO_APCS_ALIAS1_SAW2_CFG_TEST_BUS_EN_BMSK                        0x200
#define HWIO_APCS_ALIAS1_SAW2_CFG_TEST_BUS_EN_SHFT                          0x9
#define HWIO_APCS_ALIAS1_SAW2_CFG_FRC_REF_CLK_ON_BMSK                     0x100
#define HWIO_APCS_ALIAS1_SAW2_CFG_FRC_REF_CLK_ON_SHFT                       0x8
#define HWIO_APCS_ALIAS1_SAW2_CFG_CLK_DIV_BMSK                             0x1f
#define HWIO_APCS_ALIAS1_SAW2_CFG_CLK_DIV_SHFT                              0x0

#define HWIO_APCS_ALIAS1_SAW2_SPM_STS_ADDR                           (APCS_ALIAS1_SAW2_REG_BASE      + 0x0000000c)
#define HWIO_APCS_ALIAS1_SAW2_SPM_STS_RMSK                           0xfffff1ff
#define HWIO_APCS_ALIAS1_SAW2_SPM_STS_IN          \
        in_dword_masked(HWIO_APCS_ALIAS1_SAW2_SPM_STS_ADDR, HWIO_APCS_ALIAS1_SAW2_SPM_STS_RMSK)
#define HWIO_APCS_ALIAS1_SAW2_SPM_STS_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS1_SAW2_SPM_STS_ADDR, m)
#define HWIO_APCS_ALIAS1_SAW2_SPM_STS_CURR_PWR_CTL_BMSK              0xffff0000
#define HWIO_APCS_ALIAS1_SAW2_SPM_STS_CURR_PWR_CTL_SHFT                    0x10
#define HWIO_APCS_ALIAS1_SAW2_SPM_STS_SHTDWN_REQ_BMSK                    0x8000
#define HWIO_APCS_ALIAS1_SAW2_SPM_STS_SHTDWN_REQ_SHFT                       0xf
#define HWIO_APCS_ALIAS1_SAW2_SPM_STS_SHTDWN_ACK_BMSK                    0x4000
#define HWIO_APCS_ALIAS1_SAW2_SPM_STS_SHTDWN_ACK_SHFT                       0xe
#define HWIO_APCS_ALIAS1_SAW2_SPM_STS_BRNGUP_REQ_BMSK                    0x2000
#define HWIO_APCS_ALIAS1_SAW2_SPM_STS_BRNGUP_REQ_SHFT                       0xd
#define HWIO_APCS_ALIAS1_SAW2_SPM_STS_BRNGUP_ACK_BMSK                    0x1000
#define HWIO_APCS_ALIAS1_SAW2_SPM_STS_BRNGUP_ACK_SHFT                       0xc
#define HWIO_APCS_ALIAS1_SAW2_SPM_STS_RPM_STATE_BMSK                      0x180
#define HWIO_APCS_ALIAS1_SAW2_SPM_STS_RPM_STATE_SHFT                        0x7
#define HWIO_APCS_ALIAS1_SAW2_SPM_STS_SPM_CMD_ADDR_BMSK                    0x7f
#define HWIO_APCS_ALIAS1_SAW2_SPM_STS_SPM_CMD_ADDR_SHFT                     0x0

#define HWIO_APCS_ALIAS1_SAW2_AVS_STS_ADDR                           (APCS_ALIAS1_SAW2_REG_BASE      + 0x00000010)
#define HWIO_APCS_ALIAS1_SAW2_AVS_STS_RMSK                             0xff003f
#define HWIO_APCS_ALIAS1_SAW2_AVS_STS_IN          \
        in_dword_masked(HWIO_APCS_ALIAS1_SAW2_AVS_STS_ADDR, HWIO_APCS_ALIAS1_SAW2_AVS_STS_RMSK)
#define HWIO_APCS_ALIAS1_SAW2_AVS_STS_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS1_SAW2_AVS_STS_ADDR, m)
#define HWIO_APCS_ALIAS1_SAW2_AVS_STS_SPM_EVENT_BMSK                   0xff0000
#define HWIO_APCS_ALIAS1_SAW2_AVS_STS_SPM_EVENT_SHFT                       0x10
#define HWIO_APCS_ALIAS1_SAW2_AVS_STS_MAX_INT_BMSK                         0x20
#define HWIO_APCS_ALIAS1_SAW2_AVS_STS_MAX_INT_SHFT                          0x5
#define HWIO_APCS_ALIAS1_SAW2_AVS_STS_MIN_INT_BMSK                         0x10
#define HWIO_APCS_ALIAS1_SAW2_AVS_STS_MIN_INT_SHFT                          0x4
#define HWIO_APCS_ALIAS1_SAW2_AVS_STS_CPU_UP_BMSK                           0x8
#define HWIO_APCS_ALIAS1_SAW2_AVS_STS_CPU_UP_SHFT                           0x3
#define HWIO_APCS_ALIAS1_SAW2_AVS_STS_CPU_DN_BMSK                           0x4
#define HWIO_APCS_ALIAS1_SAW2_AVS_STS_CPU_DN_SHFT                           0x2
#define HWIO_APCS_ALIAS1_SAW2_AVS_STS_SW_WR_PEND_BMSK                       0x2
#define HWIO_APCS_ALIAS1_SAW2_AVS_STS_SW_WR_PEND_SHFT                       0x1
#define HWIO_APCS_ALIAS1_SAW2_AVS_STS_AVS_STATE_BMSK                        0x1
#define HWIO_APCS_ALIAS1_SAW2_AVS_STS_AVS_STATE_SHFT                        0x0

#define HWIO_APCS_ALIAS1_SAW2_PMIC_STS_ADDR                          (APCS_ALIAS1_SAW2_REG_BASE      + 0x00000014)
#define HWIO_APCS_ALIAS1_SAW2_PMIC_STS_RMSK                          0x3ff300ff
#define HWIO_APCS_ALIAS1_SAW2_PMIC_STS_IN          \
        in_dword_masked(HWIO_APCS_ALIAS1_SAW2_PMIC_STS_ADDR, HWIO_APCS_ALIAS1_SAW2_PMIC_STS_RMSK)
#define HWIO_APCS_ALIAS1_SAW2_PMIC_STS_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS1_SAW2_PMIC_STS_ADDR, m)
#define HWIO_APCS_ALIAS1_SAW2_PMIC_STS_CURR_DLY_BMSK                 0x3ff00000
#define HWIO_APCS_ALIAS1_SAW2_PMIC_STS_CURR_DLY_SHFT                       0x14
#define HWIO_APCS_ALIAS1_SAW2_PMIC_STS_PMIC_STATE_BMSK                  0x30000
#define HWIO_APCS_ALIAS1_SAW2_PMIC_STS_PMIC_STATE_SHFT                     0x10
#define HWIO_APCS_ALIAS1_SAW2_PMIC_STS_CURR_PMIC_DATA_BMSK                 0xff
#define HWIO_APCS_ALIAS1_SAW2_PMIC_STS_CURR_PMIC_DATA_SHFT                  0x0

#define HWIO_APCS_ALIAS1_SAW2_RST_ADDR                               (APCS_ALIAS1_SAW2_REG_BASE      + 0x00000018)
#define HWIO_APCS_ALIAS1_SAW2_RST_RMSK                                      0x1
#define HWIO_APCS_ALIAS1_SAW2_RST_IN          \
        in_dword_masked(HWIO_APCS_ALIAS1_SAW2_RST_ADDR, HWIO_APCS_ALIAS1_SAW2_RST_RMSK)
#define HWIO_APCS_ALIAS1_SAW2_RST_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS1_SAW2_RST_ADDR, m)
#define HWIO_APCS_ALIAS1_SAW2_RST_OUT(v)      \
        out_dword(HWIO_APCS_ALIAS1_SAW2_RST_ADDR,v)
#define HWIO_APCS_ALIAS1_SAW2_RST_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_ALIAS1_SAW2_RST_ADDR,m,v,HWIO_APCS_ALIAS1_SAW2_RST_IN)
#define HWIO_APCS_ALIAS1_SAW2_RST_RST_BMSK                                  0x1
#define HWIO_APCS_ALIAS1_SAW2_RST_RST_SHFT                                  0x0

#define HWIO_APCS_ALIAS1_SAW2_VCTL_ADDR                              (APCS_ALIAS1_SAW2_REG_BASE      + 0x0000001c)
#define HWIO_APCS_ALIAS1_SAW2_VCTL_RMSK                                0x1700ff
#define HWIO_APCS_ALIAS1_SAW2_VCTL_IN          \
        in_dword_masked(HWIO_APCS_ALIAS1_SAW2_VCTL_ADDR, HWIO_APCS_ALIAS1_SAW2_VCTL_RMSK)
#define HWIO_APCS_ALIAS1_SAW2_VCTL_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS1_SAW2_VCTL_ADDR, m)
#define HWIO_APCS_ALIAS1_SAW2_VCTL_OUT(v)      \
        out_dword(HWIO_APCS_ALIAS1_SAW2_VCTL_ADDR,v)
#define HWIO_APCS_ALIAS1_SAW2_VCTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_ALIAS1_SAW2_VCTL_ADDR,m,v,HWIO_APCS_ALIAS1_SAW2_VCTL_IN)
#define HWIO_APCS_ALIAS1_SAW2_VCTL_SIZE_BMSK                           0x100000
#define HWIO_APCS_ALIAS1_SAW2_VCTL_SIZE_SHFT                               0x14
#define HWIO_APCS_ALIAS1_SAW2_VCTL_ADR_IDX_BMSK                         0x70000
#define HWIO_APCS_ALIAS1_SAW2_VCTL_ADR_IDX_SHFT                            0x10
#define HWIO_APCS_ALIAS1_SAW2_VCTL_PMIC_DATA_BMSK                          0xff
#define HWIO_APCS_ALIAS1_SAW2_VCTL_PMIC_DATA_SHFT                           0x0

#define HWIO_APCS_ALIAS1_SAW2_AVS_CTL_ADDR                           (APCS_ALIAS1_SAW2_REG_BASE      + 0x00000020)
#define HWIO_APCS_ALIAS1_SAW2_AVS_CTL_RMSK                               0x130f
#define HWIO_APCS_ALIAS1_SAW2_AVS_CTL_IN          \
        in_dword_masked(HWIO_APCS_ALIAS1_SAW2_AVS_CTL_ADDR, HWIO_APCS_ALIAS1_SAW2_AVS_CTL_RMSK)
#define HWIO_APCS_ALIAS1_SAW2_AVS_CTL_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS1_SAW2_AVS_CTL_ADDR, m)
#define HWIO_APCS_ALIAS1_SAW2_AVS_CTL_OUT(v)      \
        out_dword(HWIO_APCS_ALIAS1_SAW2_AVS_CTL_ADDR,v)
#define HWIO_APCS_ALIAS1_SAW2_AVS_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_ALIAS1_SAW2_AVS_CTL_ADDR,m,v,HWIO_APCS_ALIAS1_SAW2_AVS_CTL_IN)
#define HWIO_APCS_ALIAS1_SAW2_AVS_CTL_VLVL_WIDTH_BMSK                    0x1000
#define HWIO_APCS_ALIAS1_SAW2_AVS_CTL_VLVL_WIDTH_SHFT                       0xc
#define HWIO_APCS_ALIAS1_SAW2_AVS_CTL_VLVL_STEP_BMSK                      0x300
#define HWIO_APCS_ALIAS1_SAW2_AVS_CTL_VLVL_STEP_SHFT                        0x8
#define HWIO_APCS_ALIAS1_SAW2_AVS_CTL_SW_DONE_INT_EN_BMSK                   0x8
#define HWIO_APCS_ALIAS1_SAW2_AVS_CTL_SW_DONE_INT_EN_SHFT                   0x3
#define HWIO_APCS_ALIAS1_SAW2_AVS_CTL_MAX_INT_EN_BMSK                       0x4
#define HWIO_APCS_ALIAS1_SAW2_AVS_CTL_MAX_INT_EN_SHFT                       0x2
#define HWIO_APCS_ALIAS1_SAW2_AVS_CTL_MIN_INT_EN_BMSK                       0x2
#define HWIO_APCS_ALIAS1_SAW2_AVS_CTL_MIN_INT_EN_SHFT                       0x1
#define HWIO_APCS_ALIAS1_SAW2_AVS_CTL_EN_BMSK                               0x1
#define HWIO_APCS_ALIAS1_SAW2_AVS_CTL_EN_SHFT                               0x0

#define HWIO_APCS_ALIAS1_SAW2_AVS_LIMIT_ADDR                         (APCS_ALIAS1_SAW2_REG_BASE      + 0x00000024)
#define HWIO_APCS_ALIAS1_SAW2_AVS_LIMIT_RMSK                           0xff00ff
#define HWIO_APCS_ALIAS1_SAW2_AVS_LIMIT_IN          \
        in_dword_masked(HWIO_APCS_ALIAS1_SAW2_AVS_LIMIT_ADDR, HWIO_APCS_ALIAS1_SAW2_AVS_LIMIT_RMSK)
#define HWIO_APCS_ALIAS1_SAW2_AVS_LIMIT_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS1_SAW2_AVS_LIMIT_ADDR, m)
#define HWIO_APCS_ALIAS1_SAW2_AVS_LIMIT_OUT(v)      \
        out_dword(HWIO_APCS_ALIAS1_SAW2_AVS_LIMIT_ADDR,v)
#define HWIO_APCS_ALIAS1_SAW2_AVS_LIMIT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_ALIAS1_SAW2_AVS_LIMIT_ADDR,m,v,HWIO_APCS_ALIAS1_SAW2_AVS_LIMIT_IN)
#define HWIO_APCS_ALIAS1_SAW2_AVS_LIMIT_MAX_VLVL_BMSK                  0xff0000
#define HWIO_APCS_ALIAS1_SAW2_AVS_LIMIT_MAX_VLVL_SHFT                      0x10
#define HWIO_APCS_ALIAS1_SAW2_AVS_LIMIT_MIN_VLVL_BMSK                      0xff
#define HWIO_APCS_ALIAS1_SAW2_AVS_LIMIT_MIN_VLVL_SHFT                       0x0

#define HWIO_APCS_ALIAS1_SAW2_AVS_DLY_ADDR                           (APCS_ALIAS1_SAW2_REG_BASE      + 0x00000028)
#define HWIO_APCS_ALIAS1_SAW2_AVS_DLY_RMSK                                0x3ff
#define HWIO_APCS_ALIAS1_SAW2_AVS_DLY_IN          \
        in_dword_masked(HWIO_APCS_ALIAS1_SAW2_AVS_DLY_ADDR, HWIO_APCS_ALIAS1_SAW2_AVS_DLY_RMSK)
#define HWIO_APCS_ALIAS1_SAW2_AVS_DLY_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS1_SAW2_AVS_DLY_ADDR, m)
#define HWIO_APCS_ALIAS1_SAW2_AVS_DLY_OUT(v)      \
        out_dword(HWIO_APCS_ALIAS1_SAW2_AVS_DLY_ADDR,v)
#define HWIO_APCS_ALIAS1_SAW2_AVS_DLY_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_ALIAS1_SAW2_AVS_DLY_ADDR,m,v,HWIO_APCS_ALIAS1_SAW2_AVS_DLY_IN)
#define HWIO_APCS_ALIAS1_SAW2_AVS_DLY_AVS_DELAY_BMSK                      0x3ff
#define HWIO_APCS_ALIAS1_SAW2_AVS_DLY_AVS_DELAY_SHFT                        0x0

#define HWIO_APCS_ALIAS1_SAW2_AVS_HYSTERESIS_ADDR                    (APCS_ALIAS1_SAW2_REG_BASE      + 0x0000002c)
#define HWIO_APCS_ALIAS1_SAW2_AVS_HYSTERESIS_RMSK                      0xff00ff
#define HWIO_APCS_ALIAS1_SAW2_AVS_HYSTERESIS_IN          \
        in_dword_masked(HWIO_APCS_ALIAS1_SAW2_AVS_HYSTERESIS_ADDR, HWIO_APCS_ALIAS1_SAW2_AVS_HYSTERESIS_RMSK)
#define HWIO_APCS_ALIAS1_SAW2_AVS_HYSTERESIS_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS1_SAW2_AVS_HYSTERESIS_ADDR, m)
#define HWIO_APCS_ALIAS1_SAW2_AVS_HYSTERESIS_OUT(v)      \
        out_dword(HWIO_APCS_ALIAS1_SAW2_AVS_HYSTERESIS_ADDR,v)
#define HWIO_APCS_ALIAS1_SAW2_AVS_HYSTERESIS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_ALIAS1_SAW2_AVS_HYSTERESIS_ADDR,m,v,HWIO_APCS_ALIAS1_SAW2_AVS_HYSTERESIS_IN)
#define HWIO_APCS_ALIAS1_SAW2_AVS_HYSTERESIS_DN_COUNT_BMSK             0xff0000
#define HWIO_APCS_ALIAS1_SAW2_AVS_HYSTERESIS_DN_COUNT_SHFT                 0x10
#define HWIO_APCS_ALIAS1_SAW2_AVS_HYSTERESIS_UP_COUNT_BMSK                 0xff
#define HWIO_APCS_ALIAS1_SAW2_AVS_HYSTERESIS_UP_COUNT_SHFT                  0x0

#define HWIO_APCS_ALIAS1_SAW2_SPM_CTL_ADDR                           (APCS_ALIAS1_SAW2_REG_BASE      + 0x00000030)
#define HWIO_APCS_ALIAS1_SAW2_SPM_CTL_RMSK                              0x107ff
#define HWIO_APCS_ALIAS1_SAW2_SPM_CTL_IN          \
        in_dword_masked(HWIO_APCS_ALIAS1_SAW2_SPM_CTL_ADDR, HWIO_APCS_ALIAS1_SAW2_SPM_CTL_RMSK)
#define HWIO_APCS_ALIAS1_SAW2_SPM_CTL_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS1_SAW2_SPM_CTL_ADDR, m)
#define HWIO_APCS_ALIAS1_SAW2_SPM_CTL_OUT(v)      \
        out_dword(HWIO_APCS_ALIAS1_SAW2_SPM_CTL_ADDR,v)
#define HWIO_APCS_ALIAS1_SAW2_SPM_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_ALIAS1_SAW2_SPM_CTL_ADDR,m,v,HWIO_APCS_ALIAS1_SAW2_SPM_CTL_IN)
#define HWIO_APCS_ALIAS1_SAW2_SPM_CTL_SPM_SYS_PC_MODE_BMSK              0x10000
#define HWIO_APCS_ALIAS1_SAW2_SPM_CTL_SPM_SYS_PC_MODE_SHFT                 0x10
#define HWIO_APCS_ALIAS1_SAW2_SPM_CTL_SPM_START_ADR_BMSK                  0x7f0
#define HWIO_APCS_ALIAS1_SAW2_SPM_CTL_SPM_START_ADR_SHFT                    0x4
#define HWIO_APCS_ALIAS1_SAW2_SPM_CTL_ISAR_BMSK                             0x8
#define HWIO_APCS_ALIAS1_SAW2_SPM_CTL_ISAR_SHFT                             0x3
#define HWIO_APCS_ALIAS1_SAW2_SPM_CTL_WAKEUP_CONFIG_BMSK                    0x6
#define HWIO_APCS_ALIAS1_SAW2_SPM_CTL_WAKEUP_CONFIG_SHFT                    0x1
#define HWIO_APCS_ALIAS1_SAW2_SPM_CTL_SPM_EN_BMSK                           0x1
#define HWIO_APCS_ALIAS1_SAW2_SPM_CTL_SPM_EN_SHFT                           0x0

#define HWIO_APCS_ALIAS1_SAW2_SPM_DLY_ADDR                           (APCS_ALIAS1_SAW2_REG_BASE      + 0x00000034)
#define HWIO_APCS_ALIAS1_SAW2_SPM_DLY_RMSK                           0x3fffffff
#define HWIO_APCS_ALIAS1_SAW2_SPM_DLY_IN          \
        in_dword_masked(HWIO_APCS_ALIAS1_SAW2_SPM_DLY_ADDR, HWIO_APCS_ALIAS1_SAW2_SPM_DLY_RMSK)
#define HWIO_APCS_ALIAS1_SAW2_SPM_DLY_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS1_SAW2_SPM_DLY_ADDR, m)
#define HWIO_APCS_ALIAS1_SAW2_SPM_DLY_OUT(v)      \
        out_dword(HWIO_APCS_ALIAS1_SAW2_SPM_DLY_ADDR,v)
#define HWIO_APCS_ALIAS1_SAW2_SPM_DLY_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_ALIAS1_SAW2_SPM_DLY_ADDR,m,v,HWIO_APCS_ALIAS1_SAW2_SPM_DLY_IN)
#define HWIO_APCS_ALIAS1_SAW2_SPM_DLY_DLY3_BMSK                      0x3ff00000
#define HWIO_APCS_ALIAS1_SAW2_SPM_DLY_DLY3_SHFT                            0x14
#define HWIO_APCS_ALIAS1_SAW2_SPM_DLY_DLY2_BMSK                         0xffc00
#define HWIO_APCS_ALIAS1_SAW2_SPM_DLY_DLY2_SHFT                             0xa
#define HWIO_APCS_ALIAS1_SAW2_SPM_DLY_DLY1_BMSK                           0x3ff
#define HWIO_APCS_ALIAS1_SAW2_SPM_DLY_DLY1_SHFT                             0x0

#define HWIO_APCS_ALIAS1_SAW2_SPM_SLP_SEQ_ENTRY_n_ADDR(n)            (APCS_ALIAS1_SAW2_REG_BASE      + 0x00000080 + 0x4 * (n))
#define HWIO_APCS_ALIAS1_SAW2_SPM_SLP_SEQ_ENTRY_n_RMSK               0xffffffff
#define HWIO_APCS_ALIAS1_SAW2_SPM_SLP_SEQ_ENTRY_n_MAXn                       17
#define HWIO_APCS_ALIAS1_SAW2_SPM_SLP_SEQ_ENTRY_n_INI(n)        \
        in_dword_masked(HWIO_APCS_ALIAS1_SAW2_SPM_SLP_SEQ_ENTRY_n_ADDR(n), HWIO_APCS_ALIAS1_SAW2_SPM_SLP_SEQ_ENTRY_n_RMSK)
#define HWIO_APCS_ALIAS1_SAW2_SPM_SLP_SEQ_ENTRY_n_INMI(n,mask)    \
        in_dword_masked(HWIO_APCS_ALIAS1_SAW2_SPM_SLP_SEQ_ENTRY_n_ADDR(n), mask)
#define HWIO_APCS_ALIAS1_SAW2_SPM_SLP_SEQ_ENTRY_n_OUTI(n,val)    \
        out_dword(HWIO_APCS_ALIAS1_SAW2_SPM_SLP_SEQ_ENTRY_n_ADDR(n),val)
#define HWIO_APCS_ALIAS1_SAW2_SPM_SLP_SEQ_ENTRY_n_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_APCS_ALIAS1_SAW2_SPM_SLP_SEQ_ENTRY_n_ADDR(n),mask,val,HWIO_APCS_ALIAS1_SAW2_SPM_SLP_SEQ_ENTRY_n_INI(n))
#define HWIO_APCS_ALIAS1_SAW2_SPM_SLP_SEQ_ENTRY_n_CMD3_BMSK          0xff000000
#define HWIO_APCS_ALIAS1_SAW2_SPM_SLP_SEQ_ENTRY_n_CMD3_SHFT                0x18
#define HWIO_APCS_ALIAS1_SAW2_SPM_SLP_SEQ_ENTRY_n_CMD2_BMSK            0xff0000
#define HWIO_APCS_ALIAS1_SAW2_SPM_SLP_SEQ_ENTRY_n_CMD2_SHFT                0x10
#define HWIO_APCS_ALIAS1_SAW2_SPM_SLP_SEQ_ENTRY_n_CMD1_BMSK              0xff00
#define HWIO_APCS_ALIAS1_SAW2_SPM_SLP_SEQ_ENTRY_n_CMD1_SHFT                 0x8
#define HWIO_APCS_ALIAS1_SAW2_SPM_SLP_SEQ_ENTRY_n_CMD0_BMSK                0xff
#define HWIO_APCS_ALIAS1_SAW2_SPM_SLP_SEQ_ENTRY_n_CMD0_SHFT                 0x0

#define HWIO_APCS_ALIAS1_SAW2_SPM_PMIC_DATA_n_ADDR(n)                (APCS_ALIAS1_SAW2_REG_BASE      + 0x00000040 + 0x4 * (n))
#define HWIO_APCS_ALIAS1_SAW2_SPM_PMIC_DATA_n_RMSK                    0x71700ff
#define HWIO_APCS_ALIAS1_SAW2_SPM_PMIC_DATA_n_MAXn                            5
#define HWIO_APCS_ALIAS1_SAW2_SPM_PMIC_DATA_n_INI(n)        \
        in_dword_masked(HWIO_APCS_ALIAS1_SAW2_SPM_PMIC_DATA_n_ADDR(n), HWIO_APCS_ALIAS1_SAW2_SPM_PMIC_DATA_n_RMSK)
#define HWIO_APCS_ALIAS1_SAW2_SPM_PMIC_DATA_n_INMI(n,mask)    \
        in_dword_masked(HWIO_APCS_ALIAS1_SAW2_SPM_PMIC_DATA_n_ADDR(n), mask)
#define HWIO_APCS_ALIAS1_SAW2_SPM_PMIC_DATA_n_OUTI(n,val)    \
        out_dword(HWIO_APCS_ALIAS1_SAW2_SPM_PMIC_DATA_n_ADDR(n),val)
#define HWIO_APCS_ALIAS1_SAW2_SPM_PMIC_DATA_n_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_APCS_ALIAS1_SAW2_SPM_PMIC_DATA_n_ADDR(n),mask,val,HWIO_APCS_ALIAS1_SAW2_SPM_PMIC_DATA_n_INI(n))
#define HWIO_APCS_ALIAS1_SAW2_SPM_PMIC_DATA_n_DLY_BMSK                0x7000000
#define HWIO_APCS_ALIAS1_SAW2_SPM_PMIC_DATA_n_DLY_SHFT                     0x18
#define HWIO_APCS_ALIAS1_SAW2_SPM_PMIC_DATA_n_SIZE_BMSK                0x100000
#define HWIO_APCS_ALIAS1_SAW2_SPM_PMIC_DATA_n_SIZE_SHFT                    0x14
#define HWIO_APCS_ALIAS1_SAW2_SPM_PMIC_DATA_n_ADR_IDX_BMSK              0x70000
#define HWIO_APCS_ALIAS1_SAW2_SPM_PMIC_DATA_n_ADR_IDX_SHFT                 0x10
#define HWIO_APCS_ALIAS1_SAW2_SPM_PMIC_DATA_n_DATA_BMSK                    0xff
#define HWIO_APCS_ALIAS1_SAW2_SPM_PMIC_DATA_n_DATA_SHFT                     0x0

#define HWIO_APCS_ALIAS1_SAW2_VERSION_ADDR                           (APCS_ALIAS1_SAW2_REG_BASE      + 0x00000fd0)
#define HWIO_APCS_ALIAS1_SAW2_VERSION_RMSK                           0xffffffff
#define HWIO_APCS_ALIAS1_SAW2_VERSION_IN          \
        in_dword_masked(HWIO_APCS_ALIAS1_SAW2_VERSION_ADDR, HWIO_APCS_ALIAS1_SAW2_VERSION_RMSK)
#define HWIO_APCS_ALIAS1_SAW2_VERSION_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS1_SAW2_VERSION_ADDR, m)
#define HWIO_APCS_ALIAS1_SAW2_VERSION_MAJOR_BMSK                     0xf0000000
#define HWIO_APCS_ALIAS1_SAW2_VERSION_MAJOR_SHFT                           0x1c
#define HWIO_APCS_ALIAS1_SAW2_VERSION_MINOR_BMSK                      0xfff0000
#define HWIO_APCS_ALIAS1_SAW2_VERSION_MINOR_SHFT                           0x10
#define HWIO_APCS_ALIAS1_SAW2_VERSION_STEP_BMSK                          0xffff
#define HWIO_APCS_ALIAS1_SAW2_VERSION_STEP_SHFT                             0x0

/*----------------------------------------------------------------------------
 * MODULE: APCS_ALIAS2_SAW2
 *--------------------------------------------------------------------------*/

#define APCS_ALIAS2_SAW2_REG_BASE                                    (KPSS_BASE      + 0x000a9000)

#define HWIO_APCS_ALIAS2_SAW2_SECURE_ADDR                            (APCS_ALIAS2_SAW2_REG_BASE      + 0x00000000)
#define HWIO_APCS_ALIAS2_SAW2_SECURE_RMSK                                   0x7
#define HWIO_APCS_ALIAS2_SAW2_SECURE_IN          \
        in_dword_masked(HWIO_APCS_ALIAS2_SAW2_SECURE_ADDR, HWIO_APCS_ALIAS2_SAW2_SECURE_RMSK)
#define HWIO_APCS_ALIAS2_SAW2_SECURE_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS2_SAW2_SECURE_ADDR, m)
#define HWIO_APCS_ALIAS2_SAW2_SECURE_OUT(v)      \
        out_dword(HWIO_APCS_ALIAS2_SAW2_SECURE_ADDR,v)
#define HWIO_APCS_ALIAS2_SAW2_SECURE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_ALIAS2_SAW2_SECURE_ADDR,m,v,HWIO_APCS_ALIAS2_SAW2_SECURE_IN)
#define HWIO_APCS_ALIAS2_SAW2_SECURE_SAW_CTL_BMSK                           0x4
#define HWIO_APCS_ALIAS2_SAW2_SECURE_SAW_CTL_SHFT                           0x2
#define HWIO_APCS_ALIAS2_SAW2_SECURE_PWR_CTL_BMSK                           0x2
#define HWIO_APCS_ALIAS2_SAW2_SECURE_PWR_CTL_SHFT                           0x1
#define HWIO_APCS_ALIAS2_SAW2_SECURE_VLT_CTL_BMSK                           0x1
#define HWIO_APCS_ALIAS2_SAW2_SECURE_VLT_CTL_SHFT                           0x0

#define HWIO_APCS_ALIAS2_SAW2_ID_ADDR                                (APCS_ALIAS2_SAW2_REG_BASE      + 0x00000004)
#define HWIO_APCS_ALIAS2_SAW2_ID_RMSK                                0x3f1f1f7f
#define HWIO_APCS_ALIAS2_SAW2_ID_IN          \
        in_dword_masked(HWIO_APCS_ALIAS2_SAW2_ID_ADDR, HWIO_APCS_ALIAS2_SAW2_ID_RMSK)
#define HWIO_APCS_ALIAS2_SAW2_ID_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS2_SAW2_ID_ADDR, m)
#define HWIO_APCS_ALIAS2_SAW2_ID_NUM_SPM_ENTRY_BMSK                  0x3f000000
#define HWIO_APCS_ALIAS2_SAW2_ID_NUM_SPM_ENTRY_SHFT                        0x18
#define HWIO_APCS_ALIAS2_SAW2_ID_NUM_PWR_CTL_BMSK                      0x1f0000
#define HWIO_APCS_ALIAS2_SAW2_ID_NUM_PWR_CTL_SHFT                          0x10
#define HWIO_APCS_ALIAS2_SAW2_ID_PMIC_DATA_WIDTH_BMSK                    0x1f00
#define HWIO_APCS_ALIAS2_SAW2_ID_PMIC_DATA_WIDTH_SHFT                       0x8
#define HWIO_APCS_ALIAS2_SAW2_ID_NUM_PMIC_DATA_BMSK                        0x70
#define HWIO_APCS_ALIAS2_SAW2_ID_NUM_PMIC_DATA_SHFT                         0x4
#define HWIO_APCS_ALIAS2_SAW2_ID_CFG_NS_ACCESS_BMSK                         0x8
#define HWIO_APCS_ALIAS2_SAW2_ID_CFG_NS_ACCESS_SHFT                         0x3
#define HWIO_APCS_ALIAS2_SAW2_ID_PMIC_ARB_INTF_BMSK                         0x4
#define HWIO_APCS_ALIAS2_SAW2_ID_PMIC_ARB_INTF_SHFT                         0x2
#define HWIO_APCS_ALIAS2_SAW2_ID_AVS_PRESENT_BMSK                           0x2
#define HWIO_APCS_ALIAS2_SAW2_ID_AVS_PRESENT_SHFT                           0x1
#define HWIO_APCS_ALIAS2_SAW2_ID_SPM_PRESENT_BMSK                           0x1
#define HWIO_APCS_ALIAS2_SAW2_ID_SPM_PRESENT_SHFT                           0x0

#define HWIO_APCS_ALIAS2_SAW2_CFG_ADDR                               (APCS_ALIAS2_SAW2_REG_BASE      + 0x00000008)
#define HWIO_APCS_ALIAS2_SAW2_CFG_RMSK                                    0x31f
#define HWIO_APCS_ALIAS2_SAW2_CFG_IN          \
        in_dword_masked(HWIO_APCS_ALIAS2_SAW2_CFG_ADDR, HWIO_APCS_ALIAS2_SAW2_CFG_RMSK)
#define HWIO_APCS_ALIAS2_SAW2_CFG_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS2_SAW2_CFG_ADDR, m)
#define HWIO_APCS_ALIAS2_SAW2_CFG_OUT(v)      \
        out_dword(HWIO_APCS_ALIAS2_SAW2_CFG_ADDR,v)
#define HWIO_APCS_ALIAS2_SAW2_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_ALIAS2_SAW2_CFG_ADDR,m,v,HWIO_APCS_ALIAS2_SAW2_CFG_IN)
#define HWIO_APCS_ALIAS2_SAW2_CFG_TEST_BUS_EN_BMSK                        0x200
#define HWIO_APCS_ALIAS2_SAW2_CFG_TEST_BUS_EN_SHFT                          0x9
#define HWIO_APCS_ALIAS2_SAW2_CFG_FRC_REF_CLK_ON_BMSK                     0x100
#define HWIO_APCS_ALIAS2_SAW2_CFG_FRC_REF_CLK_ON_SHFT                       0x8
#define HWIO_APCS_ALIAS2_SAW2_CFG_CLK_DIV_BMSK                             0x1f
#define HWIO_APCS_ALIAS2_SAW2_CFG_CLK_DIV_SHFT                              0x0

#define HWIO_APCS_ALIAS2_SAW2_SPM_STS_ADDR                           (APCS_ALIAS2_SAW2_REG_BASE      + 0x0000000c)
#define HWIO_APCS_ALIAS2_SAW2_SPM_STS_RMSK                           0xfffff1ff
#define HWIO_APCS_ALIAS2_SAW2_SPM_STS_IN          \
        in_dword_masked(HWIO_APCS_ALIAS2_SAW2_SPM_STS_ADDR, HWIO_APCS_ALIAS2_SAW2_SPM_STS_RMSK)
#define HWIO_APCS_ALIAS2_SAW2_SPM_STS_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS2_SAW2_SPM_STS_ADDR, m)
#define HWIO_APCS_ALIAS2_SAW2_SPM_STS_CURR_PWR_CTL_BMSK              0xffff0000
#define HWIO_APCS_ALIAS2_SAW2_SPM_STS_CURR_PWR_CTL_SHFT                    0x10
#define HWIO_APCS_ALIAS2_SAW2_SPM_STS_SHTDWN_REQ_BMSK                    0x8000
#define HWIO_APCS_ALIAS2_SAW2_SPM_STS_SHTDWN_REQ_SHFT                       0xf
#define HWIO_APCS_ALIAS2_SAW2_SPM_STS_SHTDWN_ACK_BMSK                    0x4000
#define HWIO_APCS_ALIAS2_SAW2_SPM_STS_SHTDWN_ACK_SHFT                       0xe
#define HWIO_APCS_ALIAS2_SAW2_SPM_STS_BRNGUP_REQ_BMSK                    0x2000
#define HWIO_APCS_ALIAS2_SAW2_SPM_STS_BRNGUP_REQ_SHFT                       0xd
#define HWIO_APCS_ALIAS2_SAW2_SPM_STS_BRNGUP_ACK_BMSK                    0x1000
#define HWIO_APCS_ALIAS2_SAW2_SPM_STS_BRNGUP_ACK_SHFT                       0xc
#define HWIO_APCS_ALIAS2_SAW2_SPM_STS_RPM_STATE_BMSK                      0x180
#define HWIO_APCS_ALIAS2_SAW2_SPM_STS_RPM_STATE_SHFT                        0x7
#define HWIO_APCS_ALIAS2_SAW2_SPM_STS_SPM_CMD_ADDR_BMSK                    0x7f
#define HWIO_APCS_ALIAS2_SAW2_SPM_STS_SPM_CMD_ADDR_SHFT                     0x0

#define HWIO_APCS_ALIAS2_SAW2_AVS_STS_ADDR                           (APCS_ALIAS2_SAW2_REG_BASE      + 0x00000010)
#define HWIO_APCS_ALIAS2_SAW2_AVS_STS_RMSK                             0xff003f
#define HWIO_APCS_ALIAS2_SAW2_AVS_STS_IN          \
        in_dword_masked(HWIO_APCS_ALIAS2_SAW2_AVS_STS_ADDR, HWIO_APCS_ALIAS2_SAW2_AVS_STS_RMSK)
#define HWIO_APCS_ALIAS2_SAW2_AVS_STS_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS2_SAW2_AVS_STS_ADDR, m)
#define HWIO_APCS_ALIAS2_SAW2_AVS_STS_SPM_EVENT_BMSK                   0xff0000
#define HWIO_APCS_ALIAS2_SAW2_AVS_STS_SPM_EVENT_SHFT                       0x10
#define HWIO_APCS_ALIAS2_SAW2_AVS_STS_MAX_INT_BMSK                         0x20
#define HWIO_APCS_ALIAS2_SAW2_AVS_STS_MAX_INT_SHFT                          0x5
#define HWIO_APCS_ALIAS2_SAW2_AVS_STS_MIN_INT_BMSK                         0x10
#define HWIO_APCS_ALIAS2_SAW2_AVS_STS_MIN_INT_SHFT                          0x4
#define HWIO_APCS_ALIAS2_SAW2_AVS_STS_CPU_UP_BMSK                           0x8
#define HWIO_APCS_ALIAS2_SAW2_AVS_STS_CPU_UP_SHFT                           0x3
#define HWIO_APCS_ALIAS2_SAW2_AVS_STS_CPU_DN_BMSK                           0x4
#define HWIO_APCS_ALIAS2_SAW2_AVS_STS_CPU_DN_SHFT                           0x2
#define HWIO_APCS_ALIAS2_SAW2_AVS_STS_SW_WR_PEND_BMSK                       0x2
#define HWIO_APCS_ALIAS2_SAW2_AVS_STS_SW_WR_PEND_SHFT                       0x1
#define HWIO_APCS_ALIAS2_SAW2_AVS_STS_AVS_STATE_BMSK                        0x1
#define HWIO_APCS_ALIAS2_SAW2_AVS_STS_AVS_STATE_SHFT                        0x0

#define HWIO_APCS_ALIAS2_SAW2_PMIC_STS_ADDR                          (APCS_ALIAS2_SAW2_REG_BASE      + 0x00000014)
#define HWIO_APCS_ALIAS2_SAW2_PMIC_STS_RMSK                          0x3ff300ff
#define HWIO_APCS_ALIAS2_SAW2_PMIC_STS_IN          \
        in_dword_masked(HWIO_APCS_ALIAS2_SAW2_PMIC_STS_ADDR, HWIO_APCS_ALIAS2_SAW2_PMIC_STS_RMSK)
#define HWIO_APCS_ALIAS2_SAW2_PMIC_STS_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS2_SAW2_PMIC_STS_ADDR, m)
#define HWIO_APCS_ALIAS2_SAW2_PMIC_STS_CURR_DLY_BMSK                 0x3ff00000
#define HWIO_APCS_ALIAS2_SAW2_PMIC_STS_CURR_DLY_SHFT                       0x14
#define HWIO_APCS_ALIAS2_SAW2_PMIC_STS_PMIC_STATE_BMSK                  0x30000
#define HWIO_APCS_ALIAS2_SAW2_PMIC_STS_PMIC_STATE_SHFT                     0x10
#define HWIO_APCS_ALIAS2_SAW2_PMIC_STS_CURR_PMIC_DATA_BMSK                 0xff
#define HWIO_APCS_ALIAS2_SAW2_PMIC_STS_CURR_PMIC_DATA_SHFT                  0x0

#define HWIO_APCS_ALIAS2_SAW2_RST_ADDR                               (APCS_ALIAS2_SAW2_REG_BASE      + 0x00000018)
#define HWIO_APCS_ALIAS2_SAW2_RST_RMSK                                      0x1
#define HWIO_APCS_ALIAS2_SAW2_RST_IN          \
        in_dword_masked(HWIO_APCS_ALIAS2_SAW2_RST_ADDR, HWIO_APCS_ALIAS2_SAW2_RST_RMSK)
#define HWIO_APCS_ALIAS2_SAW2_RST_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS2_SAW2_RST_ADDR, m)
#define HWIO_APCS_ALIAS2_SAW2_RST_OUT(v)      \
        out_dword(HWIO_APCS_ALIAS2_SAW2_RST_ADDR,v)
#define HWIO_APCS_ALIAS2_SAW2_RST_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_ALIAS2_SAW2_RST_ADDR,m,v,HWIO_APCS_ALIAS2_SAW2_RST_IN)
#define HWIO_APCS_ALIAS2_SAW2_RST_RST_BMSK                                  0x1
#define HWIO_APCS_ALIAS2_SAW2_RST_RST_SHFT                                  0x0

#define HWIO_APCS_ALIAS2_SAW2_VCTL_ADDR                              (APCS_ALIAS2_SAW2_REG_BASE      + 0x0000001c)
#define HWIO_APCS_ALIAS2_SAW2_VCTL_RMSK                                0x1700ff
#define HWIO_APCS_ALIAS2_SAW2_VCTL_IN          \
        in_dword_masked(HWIO_APCS_ALIAS2_SAW2_VCTL_ADDR, HWIO_APCS_ALIAS2_SAW2_VCTL_RMSK)
#define HWIO_APCS_ALIAS2_SAW2_VCTL_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS2_SAW2_VCTL_ADDR, m)
#define HWIO_APCS_ALIAS2_SAW2_VCTL_OUT(v)      \
        out_dword(HWIO_APCS_ALIAS2_SAW2_VCTL_ADDR,v)
#define HWIO_APCS_ALIAS2_SAW2_VCTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_ALIAS2_SAW2_VCTL_ADDR,m,v,HWIO_APCS_ALIAS2_SAW2_VCTL_IN)
#define HWIO_APCS_ALIAS2_SAW2_VCTL_SIZE_BMSK                           0x100000
#define HWIO_APCS_ALIAS2_SAW2_VCTL_SIZE_SHFT                               0x14
#define HWIO_APCS_ALIAS2_SAW2_VCTL_ADR_IDX_BMSK                         0x70000
#define HWIO_APCS_ALIAS2_SAW2_VCTL_ADR_IDX_SHFT                            0x10
#define HWIO_APCS_ALIAS2_SAW2_VCTL_PMIC_DATA_BMSK                          0xff
#define HWIO_APCS_ALIAS2_SAW2_VCTL_PMIC_DATA_SHFT                           0x0

#define HWIO_APCS_ALIAS2_SAW2_AVS_CTL_ADDR                           (APCS_ALIAS2_SAW2_REG_BASE      + 0x00000020)
#define HWIO_APCS_ALIAS2_SAW2_AVS_CTL_RMSK                               0x130f
#define HWIO_APCS_ALIAS2_SAW2_AVS_CTL_IN          \
        in_dword_masked(HWIO_APCS_ALIAS2_SAW2_AVS_CTL_ADDR, HWIO_APCS_ALIAS2_SAW2_AVS_CTL_RMSK)
#define HWIO_APCS_ALIAS2_SAW2_AVS_CTL_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS2_SAW2_AVS_CTL_ADDR, m)
#define HWIO_APCS_ALIAS2_SAW2_AVS_CTL_OUT(v)      \
        out_dword(HWIO_APCS_ALIAS2_SAW2_AVS_CTL_ADDR,v)
#define HWIO_APCS_ALIAS2_SAW2_AVS_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_ALIAS2_SAW2_AVS_CTL_ADDR,m,v,HWIO_APCS_ALIAS2_SAW2_AVS_CTL_IN)
#define HWIO_APCS_ALIAS2_SAW2_AVS_CTL_VLVL_WIDTH_BMSK                    0x1000
#define HWIO_APCS_ALIAS2_SAW2_AVS_CTL_VLVL_WIDTH_SHFT                       0xc
#define HWIO_APCS_ALIAS2_SAW2_AVS_CTL_VLVL_STEP_BMSK                      0x300
#define HWIO_APCS_ALIAS2_SAW2_AVS_CTL_VLVL_STEP_SHFT                        0x8
#define HWIO_APCS_ALIAS2_SAW2_AVS_CTL_SW_DONE_INT_EN_BMSK                   0x8
#define HWIO_APCS_ALIAS2_SAW2_AVS_CTL_SW_DONE_INT_EN_SHFT                   0x3
#define HWIO_APCS_ALIAS2_SAW2_AVS_CTL_MAX_INT_EN_BMSK                       0x4
#define HWIO_APCS_ALIAS2_SAW2_AVS_CTL_MAX_INT_EN_SHFT                       0x2
#define HWIO_APCS_ALIAS2_SAW2_AVS_CTL_MIN_INT_EN_BMSK                       0x2
#define HWIO_APCS_ALIAS2_SAW2_AVS_CTL_MIN_INT_EN_SHFT                       0x1
#define HWIO_APCS_ALIAS2_SAW2_AVS_CTL_EN_BMSK                               0x1
#define HWIO_APCS_ALIAS2_SAW2_AVS_CTL_EN_SHFT                               0x0

#define HWIO_APCS_ALIAS2_SAW2_AVS_LIMIT_ADDR                         (APCS_ALIAS2_SAW2_REG_BASE      + 0x00000024)
#define HWIO_APCS_ALIAS2_SAW2_AVS_LIMIT_RMSK                           0xff00ff
#define HWIO_APCS_ALIAS2_SAW2_AVS_LIMIT_IN          \
        in_dword_masked(HWIO_APCS_ALIAS2_SAW2_AVS_LIMIT_ADDR, HWIO_APCS_ALIAS2_SAW2_AVS_LIMIT_RMSK)
#define HWIO_APCS_ALIAS2_SAW2_AVS_LIMIT_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS2_SAW2_AVS_LIMIT_ADDR, m)
#define HWIO_APCS_ALIAS2_SAW2_AVS_LIMIT_OUT(v)      \
        out_dword(HWIO_APCS_ALIAS2_SAW2_AVS_LIMIT_ADDR,v)
#define HWIO_APCS_ALIAS2_SAW2_AVS_LIMIT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_ALIAS2_SAW2_AVS_LIMIT_ADDR,m,v,HWIO_APCS_ALIAS2_SAW2_AVS_LIMIT_IN)
#define HWIO_APCS_ALIAS2_SAW2_AVS_LIMIT_MAX_VLVL_BMSK                  0xff0000
#define HWIO_APCS_ALIAS2_SAW2_AVS_LIMIT_MAX_VLVL_SHFT                      0x10
#define HWIO_APCS_ALIAS2_SAW2_AVS_LIMIT_MIN_VLVL_BMSK                      0xff
#define HWIO_APCS_ALIAS2_SAW2_AVS_LIMIT_MIN_VLVL_SHFT                       0x0

#define HWIO_APCS_ALIAS2_SAW2_AVS_DLY_ADDR                           (APCS_ALIAS2_SAW2_REG_BASE      + 0x00000028)
#define HWIO_APCS_ALIAS2_SAW2_AVS_DLY_RMSK                                0x3ff
#define HWIO_APCS_ALIAS2_SAW2_AVS_DLY_IN          \
        in_dword_masked(HWIO_APCS_ALIAS2_SAW2_AVS_DLY_ADDR, HWIO_APCS_ALIAS2_SAW2_AVS_DLY_RMSK)
#define HWIO_APCS_ALIAS2_SAW2_AVS_DLY_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS2_SAW2_AVS_DLY_ADDR, m)
#define HWIO_APCS_ALIAS2_SAW2_AVS_DLY_OUT(v)      \
        out_dword(HWIO_APCS_ALIAS2_SAW2_AVS_DLY_ADDR,v)
#define HWIO_APCS_ALIAS2_SAW2_AVS_DLY_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_ALIAS2_SAW2_AVS_DLY_ADDR,m,v,HWIO_APCS_ALIAS2_SAW2_AVS_DLY_IN)
#define HWIO_APCS_ALIAS2_SAW2_AVS_DLY_AVS_DELAY_BMSK                      0x3ff
#define HWIO_APCS_ALIAS2_SAW2_AVS_DLY_AVS_DELAY_SHFT                        0x0

#define HWIO_APCS_ALIAS2_SAW2_AVS_HYSTERESIS_ADDR                    (APCS_ALIAS2_SAW2_REG_BASE      + 0x0000002c)
#define HWIO_APCS_ALIAS2_SAW2_AVS_HYSTERESIS_RMSK                      0xff00ff
#define HWIO_APCS_ALIAS2_SAW2_AVS_HYSTERESIS_IN          \
        in_dword_masked(HWIO_APCS_ALIAS2_SAW2_AVS_HYSTERESIS_ADDR, HWIO_APCS_ALIAS2_SAW2_AVS_HYSTERESIS_RMSK)
#define HWIO_APCS_ALIAS2_SAW2_AVS_HYSTERESIS_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS2_SAW2_AVS_HYSTERESIS_ADDR, m)
#define HWIO_APCS_ALIAS2_SAW2_AVS_HYSTERESIS_OUT(v)      \
        out_dword(HWIO_APCS_ALIAS2_SAW2_AVS_HYSTERESIS_ADDR,v)
#define HWIO_APCS_ALIAS2_SAW2_AVS_HYSTERESIS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_ALIAS2_SAW2_AVS_HYSTERESIS_ADDR,m,v,HWIO_APCS_ALIAS2_SAW2_AVS_HYSTERESIS_IN)
#define HWIO_APCS_ALIAS2_SAW2_AVS_HYSTERESIS_DN_COUNT_BMSK             0xff0000
#define HWIO_APCS_ALIAS2_SAW2_AVS_HYSTERESIS_DN_COUNT_SHFT                 0x10
#define HWIO_APCS_ALIAS2_SAW2_AVS_HYSTERESIS_UP_COUNT_BMSK                 0xff
#define HWIO_APCS_ALIAS2_SAW2_AVS_HYSTERESIS_UP_COUNT_SHFT                  0x0

#define HWIO_APCS_ALIAS2_SAW2_SPM_CTL_ADDR                           (APCS_ALIAS2_SAW2_REG_BASE      + 0x00000030)
#define HWIO_APCS_ALIAS2_SAW2_SPM_CTL_RMSK                              0x107ff
#define HWIO_APCS_ALIAS2_SAW2_SPM_CTL_IN          \
        in_dword_masked(HWIO_APCS_ALIAS2_SAW2_SPM_CTL_ADDR, HWIO_APCS_ALIAS2_SAW2_SPM_CTL_RMSK)
#define HWIO_APCS_ALIAS2_SAW2_SPM_CTL_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS2_SAW2_SPM_CTL_ADDR, m)
#define HWIO_APCS_ALIAS2_SAW2_SPM_CTL_OUT(v)      \
        out_dword(HWIO_APCS_ALIAS2_SAW2_SPM_CTL_ADDR,v)
#define HWIO_APCS_ALIAS2_SAW2_SPM_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_ALIAS2_SAW2_SPM_CTL_ADDR,m,v,HWIO_APCS_ALIAS2_SAW2_SPM_CTL_IN)
#define HWIO_APCS_ALIAS2_SAW2_SPM_CTL_SPM_SYS_PC_MODE_BMSK              0x10000
#define HWIO_APCS_ALIAS2_SAW2_SPM_CTL_SPM_SYS_PC_MODE_SHFT                 0x10
#define HWIO_APCS_ALIAS2_SAW2_SPM_CTL_SPM_START_ADR_BMSK                  0x7f0
#define HWIO_APCS_ALIAS2_SAW2_SPM_CTL_SPM_START_ADR_SHFT                    0x4
#define HWIO_APCS_ALIAS2_SAW2_SPM_CTL_ISAR_BMSK                             0x8
#define HWIO_APCS_ALIAS2_SAW2_SPM_CTL_ISAR_SHFT                             0x3
#define HWIO_APCS_ALIAS2_SAW2_SPM_CTL_WAKEUP_CONFIG_BMSK                    0x6
#define HWIO_APCS_ALIAS2_SAW2_SPM_CTL_WAKEUP_CONFIG_SHFT                    0x1
#define HWIO_APCS_ALIAS2_SAW2_SPM_CTL_SPM_EN_BMSK                           0x1
#define HWIO_APCS_ALIAS2_SAW2_SPM_CTL_SPM_EN_SHFT                           0x0

#define HWIO_APCS_ALIAS2_SAW2_SPM_DLY_ADDR                           (APCS_ALIAS2_SAW2_REG_BASE      + 0x00000034)
#define HWIO_APCS_ALIAS2_SAW2_SPM_DLY_RMSK                           0x3fffffff
#define HWIO_APCS_ALIAS2_SAW2_SPM_DLY_IN          \
        in_dword_masked(HWIO_APCS_ALIAS2_SAW2_SPM_DLY_ADDR, HWIO_APCS_ALIAS2_SAW2_SPM_DLY_RMSK)
#define HWIO_APCS_ALIAS2_SAW2_SPM_DLY_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS2_SAW2_SPM_DLY_ADDR, m)
#define HWIO_APCS_ALIAS2_SAW2_SPM_DLY_OUT(v)      \
        out_dword(HWIO_APCS_ALIAS2_SAW2_SPM_DLY_ADDR,v)
#define HWIO_APCS_ALIAS2_SAW2_SPM_DLY_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_ALIAS2_SAW2_SPM_DLY_ADDR,m,v,HWIO_APCS_ALIAS2_SAW2_SPM_DLY_IN)
#define HWIO_APCS_ALIAS2_SAW2_SPM_DLY_DLY3_BMSK                      0x3ff00000
#define HWIO_APCS_ALIAS2_SAW2_SPM_DLY_DLY3_SHFT                            0x14
#define HWIO_APCS_ALIAS2_SAW2_SPM_DLY_DLY2_BMSK                         0xffc00
#define HWIO_APCS_ALIAS2_SAW2_SPM_DLY_DLY2_SHFT                             0xa
#define HWIO_APCS_ALIAS2_SAW2_SPM_DLY_DLY1_BMSK                           0x3ff
#define HWIO_APCS_ALIAS2_SAW2_SPM_DLY_DLY1_SHFT                             0x0

#define HWIO_APCS_ALIAS2_SAW2_SPM_SLP_SEQ_ENTRY_n_ADDR(n)            (APCS_ALIAS2_SAW2_REG_BASE      + 0x00000080 + 0x4 * (n))
#define HWIO_APCS_ALIAS2_SAW2_SPM_SLP_SEQ_ENTRY_n_RMSK               0xffffffff
#define HWIO_APCS_ALIAS2_SAW2_SPM_SLP_SEQ_ENTRY_n_MAXn                       17
#define HWIO_APCS_ALIAS2_SAW2_SPM_SLP_SEQ_ENTRY_n_INI(n)        \
        in_dword_masked(HWIO_APCS_ALIAS2_SAW2_SPM_SLP_SEQ_ENTRY_n_ADDR(n), HWIO_APCS_ALIAS2_SAW2_SPM_SLP_SEQ_ENTRY_n_RMSK)
#define HWIO_APCS_ALIAS2_SAW2_SPM_SLP_SEQ_ENTRY_n_INMI(n,mask)    \
        in_dword_masked(HWIO_APCS_ALIAS2_SAW2_SPM_SLP_SEQ_ENTRY_n_ADDR(n), mask)
#define HWIO_APCS_ALIAS2_SAW2_SPM_SLP_SEQ_ENTRY_n_OUTI(n,val)    \
        out_dword(HWIO_APCS_ALIAS2_SAW2_SPM_SLP_SEQ_ENTRY_n_ADDR(n),val)
#define HWIO_APCS_ALIAS2_SAW2_SPM_SLP_SEQ_ENTRY_n_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_APCS_ALIAS2_SAW2_SPM_SLP_SEQ_ENTRY_n_ADDR(n),mask,val,HWIO_APCS_ALIAS2_SAW2_SPM_SLP_SEQ_ENTRY_n_INI(n))
#define HWIO_APCS_ALIAS2_SAW2_SPM_SLP_SEQ_ENTRY_n_CMD3_BMSK          0xff000000
#define HWIO_APCS_ALIAS2_SAW2_SPM_SLP_SEQ_ENTRY_n_CMD3_SHFT                0x18
#define HWIO_APCS_ALIAS2_SAW2_SPM_SLP_SEQ_ENTRY_n_CMD2_BMSK            0xff0000
#define HWIO_APCS_ALIAS2_SAW2_SPM_SLP_SEQ_ENTRY_n_CMD2_SHFT                0x10
#define HWIO_APCS_ALIAS2_SAW2_SPM_SLP_SEQ_ENTRY_n_CMD1_BMSK              0xff00
#define HWIO_APCS_ALIAS2_SAW2_SPM_SLP_SEQ_ENTRY_n_CMD1_SHFT                 0x8
#define HWIO_APCS_ALIAS2_SAW2_SPM_SLP_SEQ_ENTRY_n_CMD0_BMSK                0xff
#define HWIO_APCS_ALIAS2_SAW2_SPM_SLP_SEQ_ENTRY_n_CMD0_SHFT                 0x0

#define HWIO_APCS_ALIAS2_SAW2_SPM_PMIC_DATA_n_ADDR(n)                (APCS_ALIAS2_SAW2_REG_BASE      + 0x00000040 + 0x4 * (n))
#define HWIO_APCS_ALIAS2_SAW2_SPM_PMIC_DATA_n_RMSK                    0x71700ff
#define HWIO_APCS_ALIAS2_SAW2_SPM_PMIC_DATA_n_MAXn                            5
#define HWIO_APCS_ALIAS2_SAW2_SPM_PMIC_DATA_n_INI(n)        \
        in_dword_masked(HWIO_APCS_ALIAS2_SAW2_SPM_PMIC_DATA_n_ADDR(n), HWIO_APCS_ALIAS2_SAW2_SPM_PMIC_DATA_n_RMSK)
#define HWIO_APCS_ALIAS2_SAW2_SPM_PMIC_DATA_n_INMI(n,mask)    \
        in_dword_masked(HWIO_APCS_ALIAS2_SAW2_SPM_PMIC_DATA_n_ADDR(n), mask)
#define HWIO_APCS_ALIAS2_SAW2_SPM_PMIC_DATA_n_OUTI(n,val)    \
        out_dword(HWIO_APCS_ALIAS2_SAW2_SPM_PMIC_DATA_n_ADDR(n),val)
#define HWIO_APCS_ALIAS2_SAW2_SPM_PMIC_DATA_n_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_APCS_ALIAS2_SAW2_SPM_PMIC_DATA_n_ADDR(n),mask,val,HWIO_APCS_ALIAS2_SAW2_SPM_PMIC_DATA_n_INI(n))
#define HWIO_APCS_ALIAS2_SAW2_SPM_PMIC_DATA_n_DLY_BMSK                0x7000000
#define HWIO_APCS_ALIAS2_SAW2_SPM_PMIC_DATA_n_DLY_SHFT                     0x18
#define HWIO_APCS_ALIAS2_SAW2_SPM_PMIC_DATA_n_SIZE_BMSK                0x100000
#define HWIO_APCS_ALIAS2_SAW2_SPM_PMIC_DATA_n_SIZE_SHFT                    0x14
#define HWIO_APCS_ALIAS2_SAW2_SPM_PMIC_DATA_n_ADR_IDX_BMSK              0x70000
#define HWIO_APCS_ALIAS2_SAW2_SPM_PMIC_DATA_n_ADR_IDX_SHFT                 0x10
#define HWIO_APCS_ALIAS2_SAW2_SPM_PMIC_DATA_n_DATA_BMSK                    0xff
#define HWIO_APCS_ALIAS2_SAW2_SPM_PMIC_DATA_n_DATA_SHFT                     0x0

#define HWIO_APCS_ALIAS2_SAW2_VERSION_ADDR                           (APCS_ALIAS2_SAW2_REG_BASE      + 0x00000fd0)
#define HWIO_APCS_ALIAS2_SAW2_VERSION_RMSK                           0xffffffff
#define HWIO_APCS_ALIAS2_SAW2_VERSION_IN          \
        in_dword_masked(HWIO_APCS_ALIAS2_SAW2_VERSION_ADDR, HWIO_APCS_ALIAS2_SAW2_VERSION_RMSK)
#define HWIO_APCS_ALIAS2_SAW2_VERSION_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS2_SAW2_VERSION_ADDR, m)
#define HWIO_APCS_ALIAS2_SAW2_VERSION_MAJOR_BMSK                     0xf0000000
#define HWIO_APCS_ALIAS2_SAW2_VERSION_MAJOR_SHFT                           0x1c
#define HWIO_APCS_ALIAS2_SAW2_VERSION_MINOR_BMSK                      0xfff0000
#define HWIO_APCS_ALIAS2_SAW2_VERSION_MINOR_SHFT                           0x10
#define HWIO_APCS_ALIAS2_SAW2_VERSION_STEP_BMSK                          0xffff
#define HWIO_APCS_ALIAS2_SAW2_VERSION_STEP_SHFT                             0x0

/*----------------------------------------------------------------------------
 * MODULE: APCS_ALIAS3_SAW2
 *--------------------------------------------------------------------------*/

#define APCS_ALIAS3_SAW2_REG_BASE                                    (KPSS_BASE      + 0x000b9000)

#define HWIO_APCS_ALIAS3_SAW2_SECURE_ADDR                            (APCS_ALIAS3_SAW2_REG_BASE      + 0x00000000)
#define HWIO_APCS_ALIAS3_SAW2_SECURE_RMSK                                   0x7
#define HWIO_APCS_ALIAS3_SAW2_SECURE_IN          \
        in_dword_masked(HWIO_APCS_ALIAS3_SAW2_SECURE_ADDR, HWIO_APCS_ALIAS3_SAW2_SECURE_RMSK)
#define HWIO_APCS_ALIAS3_SAW2_SECURE_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS3_SAW2_SECURE_ADDR, m)
#define HWIO_APCS_ALIAS3_SAW2_SECURE_OUT(v)      \
        out_dword(HWIO_APCS_ALIAS3_SAW2_SECURE_ADDR,v)
#define HWIO_APCS_ALIAS3_SAW2_SECURE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_ALIAS3_SAW2_SECURE_ADDR,m,v,HWIO_APCS_ALIAS3_SAW2_SECURE_IN)
#define HWIO_APCS_ALIAS3_SAW2_SECURE_SAW_CTL_BMSK                           0x4
#define HWIO_APCS_ALIAS3_SAW2_SECURE_SAW_CTL_SHFT                           0x2
#define HWIO_APCS_ALIAS3_SAW2_SECURE_PWR_CTL_BMSK                           0x2
#define HWIO_APCS_ALIAS3_SAW2_SECURE_PWR_CTL_SHFT                           0x1
#define HWIO_APCS_ALIAS3_SAW2_SECURE_VLT_CTL_BMSK                           0x1
#define HWIO_APCS_ALIAS3_SAW2_SECURE_VLT_CTL_SHFT                           0x0

#define HWIO_APCS_ALIAS3_SAW2_ID_ADDR                                (APCS_ALIAS3_SAW2_REG_BASE      + 0x00000004)
#define HWIO_APCS_ALIAS3_SAW2_ID_RMSK                                0x3f1f1f7f
#define HWIO_APCS_ALIAS3_SAW2_ID_IN          \
        in_dword_masked(HWIO_APCS_ALIAS3_SAW2_ID_ADDR, HWIO_APCS_ALIAS3_SAW2_ID_RMSK)
#define HWIO_APCS_ALIAS3_SAW2_ID_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS3_SAW2_ID_ADDR, m)
#define HWIO_APCS_ALIAS3_SAW2_ID_NUM_SPM_ENTRY_BMSK                  0x3f000000
#define HWIO_APCS_ALIAS3_SAW2_ID_NUM_SPM_ENTRY_SHFT                        0x18
#define HWIO_APCS_ALIAS3_SAW2_ID_NUM_PWR_CTL_BMSK                      0x1f0000
#define HWIO_APCS_ALIAS3_SAW2_ID_NUM_PWR_CTL_SHFT                          0x10
#define HWIO_APCS_ALIAS3_SAW2_ID_PMIC_DATA_WIDTH_BMSK                    0x1f00
#define HWIO_APCS_ALIAS3_SAW2_ID_PMIC_DATA_WIDTH_SHFT                       0x8
#define HWIO_APCS_ALIAS3_SAW2_ID_NUM_PMIC_DATA_BMSK                        0x70
#define HWIO_APCS_ALIAS3_SAW2_ID_NUM_PMIC_DATA_SHFT                         0x4
#define HWIO_APCS_ALIAS3_SAW2_ID_CFG_NS_ACCESS_BMSK                         0x8
#define HWIO_APCS_ALIAS3_SAW2_ID_CFG_NS_ACCESS_SHFT                         0x3
#define HWIO_APCS_ALIAS3_SAW2_ID_PMIC_ARB_INTF_BMSK                         0x4
#define HWIO_APCS_ALIAS3_SAW2_ID_PMIC_ARB_INTF_SHFT                         0x2
#define HWIO_APCS_ALIAS3_SAW2_ID_AVS_PRESENT_BMSK                           0x2
#define HWIO_APCS_ALIAS3_SAW2_ID_AVS_PRESENT_SHFT                           0x1
#define HWIO_APCS_ALIAS3_SAW2_ID_SPM_PRESENT_BMSK                           0x1
#define HWIO_APCS_ALIAS3_SAW2_ID_SPM_PRESENT_SHFT                           0x0

#define HWIO_APCS_ALIAS3_SAW2_CFG_ADDR                               (APCS_ALIAS3_SAW2_REG_BASE      + 0x00000008)
#define HWIO_APCS_ALIAS3_SAW2_CFG_RMSK                                    0x31f
#define HWIO_APCS_ALIAS3_SAW2_CFG_IN          \
        in_dword_masked(HWIO_APCS_ALIAS3_SAW2_CFG_ADDR, HWIO_APCS_ALIAS3_SAW2_CFG_RMSK)
#define HWIO_APCS_ALIAS3_SAW2_CFG_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS3_SAW2_CFG_ADDR, m)
#define HWIO_APCS_ALIAS3_SAW2_CFG_OUT(v)      \
        out_dword(HWIO_APCS_ALIAS3_SAW2_CFG_ADDR,v)
#define HWIO_APCS_ALIAS3_SAW2_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_ALIAS3_SAW2_CFG_ADDR,m,v,HWIO_APCS_ALIAS3_SAW2_CFG_IN)
#define HWIO_APCS_ALIAS3_SAW2_CFG_TEST_BUS_EN_BMSK                        0x200
#define HWIO_APCS_ALIAS3_SAW2_CFG_TEST_BUS_EN_SHFT                          0x9
#define HWIO_APCS_ALIAS3_SAW2_CFG_FRC_REF_CLK_ON_BMSK                     0x100
#define HWIO_APCS_ALIAS3_SAW2_CFG_FRC_REF_CLK_ON_SHFT                       0x8
#define HWIO_APCS_ALIAS3_SAW2_CFG_CLK_DIV_BMSK                             0x1f
#define HWIO_APCS_ALIAS3_SAW2_CFG_CLK_DIV_SHFT                              0x0

#define HWIO_APCS_ALIAS3_SAW2_SPM_STS_ADDR                           (APCS_ALIAS3_SAW2_REG_BASE      + 0x0000000c)
#define HWIO_APCS_ALIAS3_SAW2_SPM_STS_RMSK                           0xfffff1ff
#define HWIO_APCS_ALIAS3_SAW2_SPM_STS_IN          \
        in_dword_masked(HWIO_APCS_ALIAS3_SAW2_SPM_STS_ADDR, HWIO_APCS_ALIAS3_SAW2_SPM_STS_RMSK)
#define HWIO_APCS_ALIAS3_SAW2_SPM_STS_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS3_SAW2_SPM_STS_ADDR, m)
#define HWIO_APCS_ALIAS3_SAW2_SPM_STS_CURR_PWR_CTL_BMSK              0xffff0000
#define HWIO_APCS_ALIAS3_SAW2_SPM_STS_CURR_PWR_CTL_SHFT                    0x10
#define HWIO_APCS_ALIAS3_SAW2_SPM_STS_SHTDWN_REQ_BMSK                    0x8000
#define HWIO_APCS_ALIAS3_SAW2_SPM_STS_SHTDWN_REQ_SHFT                       0xf
#define HWIO_APCS_ALIAS3_SAW2_SPM_STS_SHTDWN_ACK_BMSK                    0x4000
#define HWIO_APCS_ALIAS3_SAW2_SPM_STS_SHTDWN_ACK_SHFT                       0xe
#define HWIO_APCS_ALIAS3_SAW2_SPM_STS_BRNGUP_REQ_BMSK                    0x2000
#define HWIO_APCS_ALIAS3_SAW2_SPM_STS_BRNGUP_REQ_SHFT                       0xd
#define HWIO_APCS_ALIAS3_SAW2_SPM_STS_BRNGUP_ACK_BMSK                    0x1000
#define HWIO_APCS_ALIAS3_SAW2_SPM_STS_BRNGUP_ACK_SHFT                       0xc
#define HWIO_APCS_ALIAS3_SAW2_SPM_STS_RPM_STATE_BMSK                      0x180
#define HWIO_APCS_ALIAS3_SAW2_SPM_STS_RPM_STATE_SHFT                        0x7
#define HWIO_APCS_ALIAS3_SAW2_SPM_STS_SPM_CMD_ADDR_BMSK                    0x7f
#define HWIO_APCS_ALIAS3_SAW2_SPM_STS_SPM_CMD_ADDR_SHFT                     0x0

#define HWIO_APCS_ALIAS3_SAW2_AVS_STS_ADDR                           (APCS_ALIAS3_SAW2_REG_BASE      + 0x00000010)
#define HWIO_APCS_ALIAS3_SAW2_AVS_STS_RMSK                             0xff003f
#define HWIO_APCS_ALIAS3_SAW2_AVS_STS_IN          \
        in_dword_masked(HWIO_APCS_ALIAS3_SAW2_AVS_STS_ADDR, HWIO_APCS_ALIAS3_SAW2_AVS_STS_RMSK)
#define HWIO_APCS_ALIAS3_SAW2_AVS_STS_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS3_SAW2_AVS_STS_ADDR, m)
#define HWIO_APCS_ALIAS3_SAW2_AVS_STS_SPM_EVENT_BMSK                   0xff0000
#define HWIO_APCS_ALIAS3_SAW2_AVS_STS_SPM_EVENT_SHFT                       0x10
#define HWIO_APCS_ALIAS3_SAW2_AVS_STS_MAX_INT_BMSK                         0x20
#define HWIO_APCS_ALIAS3_SAW2_AVS_STS_MAX_INT_SHFT                          0x5
#define HWIO_APCS_ALIAS3_SAW2_AVS_STS_MIN_INT_BMSK                         0x10
#define HWIO_APCS_ALIAS3_SAW2_AVS_STS_MIN_INT_SHFT                          0x4
#define HWIO_APCS_ALIAS3_SAW2_AVS_STS_CPU_UP_BMSK                           0x8
#define HWIO_APCS_ALIAS3_SAW2_AVS_STS_CPU_UP_SHFT                           0x3
#define HWIO_APCS_ALIAS3_SAW2_AVS_STS_CPU_DN_BMSK                           0x4
#define HWIO_APCS_ALIAS3_SAW2_AVS_STS_CPU_DN_SHFT                           0x2
#define HWIO_APCS_ALIAS3_SAW2_AVS_STS_SW_WR_PEND_BMSK                       0x2
#define HWIO_APCS_ALIAS3_SAW2_AVS_STS_SW_WR_PEND_SHFT                       0x1
#define HWIO_APCS_ALIAS3_SAW2_AVS_STS_AVS_STATE_BMSK                        0x1
#define HWIO_APCS_ALIAS3_SAW2_AVS_STS_AVS_STATE_SHFT                        0x0

#define HWIO_APCS_ALIAS3_SAW2_PMIC_STS_ADDR                          (APCS_ALIAS3_SAW2_REG_BASE      + 0x00000014)
#define HWIO_APCS_ALIAS3_SAW2_PMIC_STS_RMSK                          0x3ff300ff
#define HWIO_APCS_ALIAS3_SAW2_PMIC_STS_IN          \
        in_dword_masked(HWIO_APCS_ALIAS3_SAW2_PMIC_STS_ADDR, HWIO_APCS_ALIAS3_SAW2_PMIC_STS_RMSK)
#define HWIO_APCS_ALIAS3_SAW2_PMIC_STS_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS3_SAW2_PMIC_STS_ADDR, m)
#define HWIO_APCS_ALIAS3_SAW2_PMIC_STS_CURR_DLY_BMSK                 0x3ff00000
#define HWIO_APCS_ALIAS3_SAW2_PMIC_STS_CURR_DLY_SHFT                       0x14
#define HWIO_APCS_ALIAS3_SAW2_PMIC_STS_PMIC_STATE_BMSK                  0x30000
#define HWIO_APCS_ALIAS3_SAW2_PMIC_STS_PMIC_STATE_SHFT                     0x10
#define HWIO_APCS_ALIAS3_SAW2_PMIC_STS_CURR_PMIC_DATA_BMSK                 0xff
#define HWIO_APCS_ALIAS3_SAW2_PMIC_STS_CURR_PMIC_DATA_SHFT                  0x0

#define HWIO_APCS_ALIAS3_SAW2_RST_ADDR                               (APCS_ALIAS3_SAW2_REG_BASE      + 0x00000018)
#define HWIO_APCS_ALIAS3_SAW2_RST_RMSK                                      0x1
#define HWIO_APCS_ALIAS3_SAW2_RST_IN          \
        in_dword_masked(HWIO_APCS_ALIAS3_SAW2_RST_ADDR, HWIO_APCS_ALIAS3_SAW2_RST_RMSK)
#define HWIO_APCS_ALIAS3_SAW2_RST_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS3_SAW2_RST_ADDR, m)
#define HWIO_APCS_ALIAS3_SAW2_RST_OUT(v)      \
        out_dword(HWIO_APCS_ALIAS3_SAW2_RST_ADDR,v)
#define HWIO_APCS_ALIAS3_SAW2_RST_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_ALIAS3_SAW2_RST_ADDR,m,v,HWIO_APCS_ALIAS3_SAW2_RST_IN)
#define HWIO_APCS_ALIAS3_SAW2_RST_RST_BMSK                                  0x1
#define HWIO_APCS_ALIAS3_SAW2_RST_RST_SHFT                                  0x0

#define HWIO_APCS_ALIAS3_SAW2_VCTL_ADDR                              (APCS_ALIAS3_SAW2_REG_BASE      + 0x0000001c)
#define HWIO_APCS_ALIAS3_SAW2_VCTL_RMSK                                0x1700ff
#define HWIO_APCS_ALIAS3_SAW2_VCTL_IN          \
        in_dword_masked(HWIO_APCS_ALIAS3_SAW2_VCTL_ADDR, HWIO_APCS_ALIAS3_SAW2_VCTL_RMSK)
#define HWIO_APCS_ALIAS3_SAW2_VCTL_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS3_SAW2_VCTL_ADDR, m)
#define HWIO_APCS_ALIAS3_SAW2_VCTL_OUT(v)      \
        out_dword(HWIO_APCS_ALIAS3_SAW2_VCTL_ADDR,v)
#define HWIO_APCS_ALIAS3_SAW2_VCTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_ALIAS3_SAW2_VCTL_ADDR,m,v,HWIO_APCS_ALIAS3_SAW2_VCTL_IN)
#define HWIO_APCS_ALIAS3_SAW2_VCTL_SIZE_BMSK                           0x100000
#define HWIO_APCS_ALIAS3_SAW2_VCTL_SIZE_SHFT                               0x14
#define HWIO_APCS_ALIAS3_SAW2_VCTL_ADR_IDX_BMSK                         0x70000
#define HWIO_APCS_ALIAS3_SAW2_VCTL_ADR_IDX_SHFT                            0x10
#define HWIO_APCS_ALIAS3_SAW2_VCTL_PMIC_DATA_BMSK                          0xff
#define HWIO_APCS_ALIAS3_SAW2_VCTL_PMIC_DATA_SHFT                           0x0

#define HWIO_APCS_ALIAS3_SAW2_AVS_CTL_ADDR                           (APCS_ALIAS3_SAW2_REG_BASE      + 0x00000020)
#define HWIO_APCS_ALIAS3_SAW2_AVS_CTL_RMSK                               0x130f
#define HWIO_APCS_ALIAS3_SAW2_AVS_CTL_IN          \
        in_dword_masked(HWIO_APCS_ALIAS3_SAW2_AVS_CTL_ADDR, HWIO_APCS_ALIAS3_SAW2_AVS_CTL_RMSK)
#define HWIO_APCS_ALIAS3_SAW2_AVS_CTL_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS3_SAW2_AVS_CTL_ADDR, m)
#define HWIO_APCS_ALIAS3_SAW2_AVS_CTL_OUT(v)      \
        out_dword(HWIO_APCS_ALIAS3_SAW2_AVS_CTL_ADDR,v)
#define HWIO_APCS_ALIAS3_SAW2_AVS_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_ALIAS3_SAW2_AVS_CTL_ADDR,m,v,HWIO_APCS_ALIAS3_SAW2_AVS_CTL_IN)
#define HWIO_APCS_ALIAS3_SAW2_AVS_CTL_VLVL_WIDTH_BMSK                    0x1000
#define HWIO_APCS_ALIAS3_SAW2_AVS_CTL_VLVL_WIDTH_SHFT                       0xc
#define HWIO_APCS_ALIAS3_SAW2_AVS_CTL_VLVL_STEP_BMSK                      0x300
#define HWIO_APCS_ALIAS3_SAW2_AVS_CTL_VLVL_STEP_SHFT                        0x8
#define HWIO_APCS_ALIAS3_SAW2_AVS_CTL_SW_DONE_INT_EN_BMSK                   0x8
#define HWIO_APCS_ALIAS3_SAW2_AVS_CTL_SW_DONE_INT_EN_SHFT                   0x3
#define HWIO_APCS_ALIAS3_SAW2_AVS_CTL_MAX_INT_EN_BMSK                       0x4
#define HWIO_APCS_ALIAS3_SAW2_AVS_CTL_MAX_INT_EN_SHFT                       0x2
#define HWIO_APCS_ALIAS3_SAW2_AVS_CTL_MIN_INT_EN_BMSK                       0x2
#define HWIO_APCS_ALIAS3_SAW2_AVS_CTL_MIN_INT_EN_SHFT                       0x1
#define HWIO_APCS_ALIAS3_SAW2_AVS_CTL_EN_BMSK                               0x1
#define HWIO_APCS_ALIAS3_SAW2_AVS_CTL_EN_SHFT                               0x0

#define HWIO_APCS_ALIAS3_SAW2_AVS_LIMIT_ADDR                         (APCS_ALIAS3_SAW2_REG_BASE      + 0x00000024)
#define HWIO_APCS_ALIAS3_SAW2_AVS_LIMIT_RMSK                           0xff00ff
#define HWIO_APCS_ALIAS3_SAW2_AVS_LIMIT_IN          \
        in_dword_masked(HWIO_APCS_ALIAS3_SAW2_AVS_LIMIT_ADDR, HWIO_APCS_ALIAS3_SAW2_AVS_LIMIT_RMSK)
#define HWIO_APCS_ALIAS3_SAW2_AVS_LIMIT_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS3_SAW2_AVS_LIMIT_ADDR, m)
#define HWIO_APCS_ALIAS3_SAW2_AVS_LIMIT_OUT(v)      \
        out_dword(HWIO_APCS_ALIAS3_SAW2_AVS_LIMIT_ADDR,v)
#define HWIO_APCS_ALIAS3_SAW2_AVS_LIMIT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_ALIAS3_SAW2_AVS_LIMIT_ADDR,m,v,HWIO_APCS_ALIAS3_SAW2_AVS_LIMIT_IN)
#define HWIO_APCS_ALIAS3_SAW2_AVS_LIMIT_MAX_VLVL_BMSK                  0xff0000
#define HWIO_APCS_ALIAS3_SAW2_AVS_LIMIT_MAX_VLVL_SHFT                      0x10
#define HWIO_APCS_ALIAS3_SAW2_AVS_LIMIT_MIN_VLVL_BMSK                      0xff
#define HWIO_APCS_ALIAS3_SAW2_AVS_LIMIT_MIN_VLVL_SHFT                       0x0

#define HWIO_APCS_ALIAS3_SAW2_AVS_DLY_ADDR                           (APCS_ALIAS3_SAW2_REG_BASE      + 0x00000028)
#define HWIO_APCS_ALIAS3_SAW2_AVS_DLY_RMSK                                0x3ff
#define HWIO_APCS_ALIAS3_SAW2_AVS_DLY_IN          \
        in_dword_masked(HWIO_APCS_ALIAS3_SAW2_AVS_DLY_ADDR, HWIO_APCS_ALIAS3_SAW2_AVS_DLY_RMSK)
#define HWIO_APCS_ALIAS3_SAW2_AVS_DLY_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS3_SAW2_AVS_DLY_ADDR, m)
#define HWIO_APCS_ALIAS3_SAW2_AVS_DLY_OUT(v)      \
        out_dword(HWIO_APCS_ALIAS3_SAW2_AVS_DLY_ADDR,v)
#define HWIO_APCS_ALIAS3_SAW2_AVS_DLY_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_ALIAS3_SAW2_AVS_DLY_ADDR,m,v,HWIO_APCS_ALIAS3_SAW2_AVS_DLY_IN)
#define HWIO_APCS_ALIAS3_SAW2_AVS_DLY_AVS_DELAY_BMSK                      0x3ff
#define HWIO_APCS_ALIAS3_SAW2_AVS_DLY_AVS_DELAY_SHFT                        0x0

#define HWIO_APCS_ALIAS3_SAW2_AVS_HYSTERESIS_ADDR                    (APCS_ALIAS3_SAW2_REG_BASE      + 0x0000002c)
#define HWIO_APCS_ALIAS3_SAW2_AVS_HYSTERESIS_RMSK                      0xff00ff
#define HWIO_APCS_ALIAS3_SAW2_AVS_HYSTERESIS_IN          \
        in_dword_masked(HWIO_APCS_ALIAS3_SAW2_AVS_HYSTERESIS_ADDR, HWIO_APCS_ALIAS3_SAW2_AVS_HYSTERESIS_RMSK)
#define HWIO_APCS_ALIAS3_SAW2_AVS_HYSTERESIS_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS3_SAW2_AVS_HYSTERESIS_ADDR, m)
#define HWIO_APCS_ALIAS3_SAW2_AVS_HYSTERESIS_OUT(v)      \
        out_dword(HWIO_APCS_ALIAS3_SAW2_AVS_HYSTERESIS_ADDR,v)
#define HWIO_APCS_ALIAS3_SAW2_AVS_HYSTERESIS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_ALIAS3_SAW2_AVS_HYSTERESIS_ADDR,m,v,HWIO_APCS_ALIAS3_SAW2_AVS_HYSTERESIS_IN)
#define HWIO_APCS_ALIAS3_SAW2_AVS_HYSTERESIS_DN_COUNT_BMSK             0xff0000
#define HWIO_APCS_ALIAS3_SAW2_AVS_HYSTERESIS_DN_COUNT_SHFT                 0x10
#define HWIO_APCS_ALIAS3_SAW2_AVS_HYSTERESIS_UP_COUNT_BMSK                 0xff
#define HWIO_APCS_ALIAS3_SAW2_AVS_HYSTERESIS_UP_COUNT_SHFT                  0x0

#define HWIO_APCS_ALIAS3_SAW2_SPM_CTL_ADDR                           (APCS_ALIAS3_SAW2_REG_BASE      + 0x00000030)
#define HWIO_APCS_ALIAS3_SAW2_SPM_CTL_RMSK                              0x107ff
#define HWIO_APCS_ALIAS3_SAW2_SPM_CTL_IN          \
        in_dword_masked(HWIO_APCS_ALIAS3_SAW2_SPM_CTL_ADDR, HWIO_APCS_ALIAS3_SAW2_SPM_CTL_RMSK)
#define HWIO_APCS_ALIAS3_SAW2_SPM_CTL_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS3_SAW2_SPM_CTL_ADDR, m)
#define HWIO_APCS_ALIAS3_SAW2_SPM_CTL_OUT(v)      \
        out_dword(HWIO_APCS_ALIAS3_SAW2_SPM_CTL_ADDR,v)
#define HWIO_APCS_ALIAS3_SAW2_SPM_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_ALIAS3_SAW2_SPM_CTL_ADDR,m,v,HWIO_APCS_ALIAS3_SAW2_SPM_CTL_IN)
#define HWIO_APCS_ALIAS3_SAW2_SPM_CTL_SPM_SYS_PC_MODE_BMSK              0x10000
#define HWIO_APCS_ALIAS3_SAW2_SPM_CTL_SPM_SYS_PC_MODE_SHFT                 0x10
#define HWIO_APCS_ALIAS3_SAW2_SPM_CTL_SPM_START_ADR_BMSK                  0x7f0
#define HWIO_APCS_ALIAS3_SAW2_SPM_CTL_SPM_START_ADR_SHFT                    0x4
#define HWIO_APCS_ALIAS3_SAW2_SPM_CTL_ISAR_BMSK                             0x8
#define HWIO_APCS_ALIAS3_SAW2_SPM_CTL_ISAR_SHFT                             0x3
#define HWIO_APCS_ALIAS3_SAW2_SPM_CTL_WAKEUP_CONFIG_BMSK                    0x6
#define HWIO_APCS_ALIAS3_SAW2_SPM_CTL_WAKEUP_CONFIG_SHFT                    0x1
#define HWIO_APCS_ALIAS3_SAW2_SPM_CTL_SPM_EN_BMSK                           0x1
#define HWIO_APCS_ALIAS3_SAW2_SPM_CTL_SPM_EN_SHFT                           0x0

#define HWIO_APCS_ALIAS3_SAW2_SPM_DLY_ADDR                           (APCS_ALIAS3_SAW2_REG_BASE      + 0x00000034)
#define HWIO_APCS_ALIAS3_SAW2_SPM_DLY_RMSK                           0x3fffffff
#define HWIO_APCS_ALIAS3_SAW2_SPM_DLY_IN          \
        in_dword_masked(HWIO_APCS_ALIAS3_SAW2_SPM_DLY_ADDR, HWIO_APCS_ALIAS3_SAW2_SPM_DLY_RMSK)
#define HWIO_APCS_ALIAS3_SAW2_SPM_DLY_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS3_SAW2_SPM_DLY_ADDR, m)
#define HWIO_APCS_ALIAS3_SAW2_SPM_DLY_OUT(v)      \
        out_dword(HWIO_APCS_ALIAS3_SAW2_SPM_DLY_ADDR,v)
#define HWIO_APCS_ALIAS3_SAW2_SPM_DLY_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_ALIAS3_SAW2_SPM_DLY_ADDR,m,v,HWIO_APCS_ALIAS3_SAW2_SPM_DLY_IN)
#define HWIO_APCS_ALIAS3_SAW2_SPM_DLY_DLY3_BMSK                      0x3ff00000
#define HWIO_APCS_ALIAS3_SAW2_SPM_DLY_DLY3_SHFT                            0x14
#define HWIO_APCS_ALIAS3_SAW2_SPM_DLY_DLY2_BMSK                         0xffc00
#define HWIO_APCS_ALIAS3_SAW2_SPM_DLY_DLY2_SHFT                             0xa
#define HWIO_APCS_ALIAS3_SAW2_SPM_DLY_DLY1_BMSK                           0x3ff
#define HWIO_APCS_ALIAS3_SAW2_SPM_DLY_DLY1_SHFT                             0x0

#define HWIO_APCS_ALIAS3_SAW2_SPM_SLP_SEQ_ENTRY_n_ADDR(n)            (APCS_ALIAS3_SAW2_REG_BASE      + 0x00000080 + 0x4 * (n))
#define HWIO_APCS_ALIAS3_SAW2_SPM_SLP_SEQ_ENTRY_n_RMSK               0xffffffff
#define HWIO_APCS_ALIAS3_SAW2_SPM_SLP_SEQ_ENTRY_n_MAXn                       17
#define HWIO_APCS_ALIAS3_SAW2_SPM_SLP_SEQ_ENTRY_n_INI(n)        \
        in_dword_masked(HWIO_APCS_ALIAS3_SAW2_SPM_SLP_SEQ_ENTRY_n_ADDR(n), HWIO_APCS_ALIAS3_SAW2_SPM_SLP_SEQ_ENTRY_n_RMSK)
#define HWIO_APCS_ALIAS3_SAW2_SPM_SLP_SEQ_ENTRY_n_INMI(n,mask)    \
        in_dword_masked(HWIO_APCS_ALIAS3_SAW2_SPM_SLP_SEQ_ENTRY_n_ADDR(n), mask)
#define HWIO_APCS_ALIAS3_SAW2_SPM_SLP_SEQ_ENTRY_n_OUTI(n,val)    \
        out_dword(HWIO_APCS_ALIAS3_SAW2_SPM_SLP_SEQ_ENTRY_n_ADDR(n),val)
#define HWIO_APCS_ALIAS3_SAW2_SPM_SLP_SEQ_ENTRY_n_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_APCS_ALIAS3_SAW2_SPM_SLP_SEQ_ENTRY_n_ADDR(n),mask,val,HWIO_APCS_ALIAS3_SAW2_SPM_SLP_SEQ_ENTRY_n_INI(n))
#define HWIO_APCS_ALIAS3_SAW2_SPM_SLP_SEQ_ENTRY_n_CMD3_BMSK          0xff000000
#define HWIO_APCS_ALIAS3_SAW2_SPM_SLP_SEQ_ENTRY_n_CMD3_SHFT                0x18
#define HWIO_APCS_ALIAS3_SAW2_SPM_SLP_SEQ_ENTRY_n_CMD2_BMSK            0xff0000
#define HWIO_APCS_ALIAS3_SAW2_SPM_SLP_SEQ_ENTRY_n_CMD2_SHFT                0x10
#define HWIO_APCS_ALIAS3_SAW2_SPM_SLP_SEQ_ENTRY_n_CMD1_BMSK              0xff00
#define HWIO_APCS_ALIAS3_SAW2_SPM_SLP_SEQ_ENTRY_n_CMD1_SHFT                 0x8
#define HWIO_APCS_ALIAS3_SAW2_SPM_SLP_SEQ_ENTRY_n_CMD0_BMSK                0xff
#define HWIO_APCS_ALIAS3_SAW2_SPM_SLP_SEQ_ENTRY_n_CMD0_SHFT                 0x0

#define HWIO_APCS_ALIAS3_SAW2_SPM_PMIC_DATA_n_ADDR(n)                (APCS_ALIAS3_SAW2_REG_BASE      + 0x00000040 + 0x4 * (n))
#define HWIO_APCS_ALIAS3_SAW2_SPM_PMIC_DATA_n_RMSK                    0x71700ff
#define HWIO_APCS_ALIAS3_SAW2_SPM_PMIC_DATA_n_MAXn                            5
#define HWIO_APCS_ALIAS3_SAW2_SPM_PMIC_DATA_n_INI(n)        \
        in_dword_masked(HWIO_APCS_ALIAS3_SAW2_SPM_PMIC_DATA_n_ADDR(n), HWIO_APCS_ALIAS3_SAW2_SPM_PMIC_DATA_n_RMSK)
#define HWIO_APCS_ALIAS3_SAW2_SPM_PMIC_DATA_n_INMI(n,mask)    \
        in_dword_masked(HWIO_APCS_ALIAS3_SAW2_SPM_PMIC_DATA_n_ADDR(n), mask)
#define HWIO_APCS_ALIAS3_SAW2_SPM_PMIC_DATA_n_OUTI(n,val)    \
        out_dword(HWIO_APCS_ALIAS3_SAW2_SPM_PMIC_DATA_n_ADDR(n),val)
#define HWIO_APCS_ALIAS3_SAW2_SPM_PMIC_DATA_n_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_APCS_ALIAS3_SAW2_SPM_PMIC_DATA_n_ADDR(n),mask,val,HWIO_APCS_ALIAS3_SAW2_SPM_PMIC_DATA_n_INI(n))
#define HWIO_APCS_ALIAS3_SAW2_SPM_PMIC_DATA_n_DLY_BMSK                0x7000000
#define HWIO_APCS_ALIAS3_SAW2_SPM_PMIC_DATA_n_DLY_SHFT                     0x18
#define HWIO_APCS_ALIAS3_SAW2_SPM_PMIC_DATA_n_SIZE_BMSK                0x100000
#define HWIO_APCS_ALIAS3_SAW2_SPM_PMIC_DATA_n_SIZE_SHFT                    0x14
#define HWIO_APCS_ALIAS3_SAW2_SPM_PMIC_DATA_n_ADR_IDX_BMSK              0x70000
#define HWIO_APCS_ALIAS3_SAW2_SPM_PMIC_DATA_n_ADR_IDX_SHFT                 0x10
#define HWIO_APCS_ALIAS3_SAW2_SPM_PMIC_DATA_n_DATA_BMSK                    0xff
#define HWIO_APCS_ALIAS3_SAW2_SPM_PMIC_DATA_n_DATA_SHFT                     0x0

#define HWIO_APCS_ALIAS3_SAW2_VERSION_ADDR                           (APCS_ALIAS3_SAW2_REG_BASE      + 0x00000fd0)
#define HWIO_APCS_ALIAS3_SAW2_VERSION_RMSK                           0xffffffff
#define HWIO_APCS_ALIAS3_SAW2_VERSION_IN          \
        in_dword_masked(HWIO_APCS_ALIAS3_SAW2_VERSION_ADDR, HWIO_APCS_ALIAS3_SAW2_VERSION_RMSK)
#define HWIO_APCS_ALIAS3_SAW2_VERSION_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS3_SAW2_VERSION_ADDR, m)
#define HWIO_APCS_ALIAS3_SAW2_VERSION_MAJOR_BMSK                     0xf0000000
#define HWIO_APCS_ALIAS3_SAW2_VERSION_MAJOR_SHFT                           0x1c
#define HWIO_APCS_ALIAS3_SAW2_VERSION_MINOR_BMSK                      0xfff0000
#define HWIO_APCS_ALIAS3_SAW2_VERSION_MINOR_SHFT                           0x10
#define HWIO_APCS_ALIAS3_SAW2_VERSION_STEP_BMSK                          0xffff
#define HWIO_APCS_ALIAS3_SAW2_VERSION_STEP_SHFT                             0x0


#endif /* __SAW2_HWIO_H__ */
