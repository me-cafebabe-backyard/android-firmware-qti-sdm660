#ifndef __HALAVSHWIOSAW4_H__
#define __HALAVSHWIOSAW4_H__
/*
===========================================================================
*/
/**
  @file HALavsHWIOSAW4.h
  @brief Auto-generated HWIO interface include file.

  This file contains HWIO register definitions for the following modules:
    APCLUS0_L2_SAW4_1_1_AVS
    APCLUS0_L2_SAW4_1_1_HMSS_CBF_PDW16_WRAPPER
    APCLUS0_L2_SAW4_1_1_SPM
    APCLUS0_L2_SAW4_1_1_STS

  'Include' filters applied: <none>
  'Exclude' filters applied: DUMMY RESERVED
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

  $Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/HALclkLib/HALavsHWIOSAW4.h#1 $
  $DateTime: 2016/12/15 20:05:04 $
  $Author: pwbldsvc $

  ===========================================================================
*/

/*----------------------------------------------------------------------------
 * MODULE: SAW4_SPM
 *--------------------------------------------------------------------------*/

#define HWIO_SAW4_SPM_CTL_ADDR(core)                     ((core) + 0x00000000)
#define HWIO_SAW4_SPM_CTL_RMSK                           0xff7e1fff
#define HWIO_SAW4_SPM_CTL_IN(core)    \
        in_dword_masked(HWIO_SAW4_SPM_CTL_ADDR(core), HWIO_SAW4_SPM_CTL_RMSK)
#define HWIO_SAW4_SPM_CTL_INM(core,m)      \
        in_dword_masked(HWIO_SAW4_SPM_CTL_ADDR(core), m)
#define HWIO_SAW4_SPM_CTL_OUT(core,v)      \
        out_dword(HWIO_SAW4_SPM_CTL_ADDR(core),v)
#define HWIO_SAW4_SPM_CTL_OUTM(core,m,v) \
        out_dword_masked_ns(HWIO_SAW4_SPM_CTL_ADDR(core),m,v,HWIO_SAW4_SPM_CTL_IN(core))
#define HWIO_SAW4_SPM_CTL_EVENT_SYNC_BMSK                0xff000000
#define HWIO_SAW4_SPM_CTL_EVENT_SYNC_SHFT                      0x18
#define HWIO_SAW4_SPM_CTL_PWR_STATE_IDX_BMSK               0x700000
#define HWIO_SAW4_SPM_CTL_PWR_STATE_IDX_SHFT                   0x14
#define HWIO_SAW4_SPM_CTL_SLEEP_REQ_BMSK                    0x80000
#define HWIO_SAW4_SPM_CTL_SLEEP_REQ_SHFT                       0x13
#define HWIO_SAW4_SPM_CTL_WAKEUP_REQ_BMSK                   0x40000
#define HWIO_SAW4_SPM_CTL_WAKEUP_REQ_SHFT                      0x12
#define HWIO_SAW4_SPM_CTL_SLP_CMD_MODE_BMSK                 0x20000
#define HWIO_SAW4_SPM_CTL_SLP_CMD_MODE_SHFT                    0x11
#define HWIO_SAW4_SPM_CTL_SPM_START_ADR_BMSK                 0x1ff0
#define HWIO_SAW4_SPM_CTL_SPM_START_ADR_SHFT                    0x4
#define HWIO_SAW4_SPM_CTL_ISAR_BMSK                             0x8
#define HWIO_SAW4_SPM_CTL_ISAR_SHFT                             0x3
#define HWIO_SAW4_SPM_CTL_WAKEUP_CONFIG_BMSK                    0x6
#define HWIO_SAW4_SPM_CTL_WAKEUP_CONFIG_SHFT                    0x1
#define HWIO_SAW4_SPM_CTL_SPM_EN_BMSK                           0x1
#define HWIO_SAW4_SPM_CTL_SPM_EN_SHFT                           0x0

#define HWIO_SAW4_SPM_DLY_ADDR(core)                     ((core) + 0x00000004)
#define HWIO_SAW4_SPM_DLY_RMSK                           0x3fffffff
#define HWIO_SAW4_SPM_DLY_IN(core)    \
        in_dword_masked(HWIO_SAW4_SPM_DLY_ADDR(core), HWIO_SAW4_SPM_DLY_RMSK)
#define HWIO_SAW4_SPM_DLY_INM(core,m)      \
        in_dword_masked(HWIO_SAW4_SPM_DLY_ADDR(core), m)
#define HWIO_SAW4_SPM_DLY_OUT(core,v)      \
        out_dword(HWIO_SAW4_SPM_DLY_ADDR(core),v)
#define HWIO_SAW4_SPM_DLY_OUTM(core,m,v) \
        out_dword_masked_ns(HWIO_SAW4_SPM_DLY_ADDR(core),m,v,HWIO_SAW4_SPM_DLY_IN(core))
#define HWIO_SAW4_SPM_DLY_DLY3_BMSK                      0x3ff00000
#define HWIO_SAW4_SPM_DLY_DLY3_SHFT                            0x14
#define HWIO_SAW4_SPM_DLY_DLY2_BMSK                         0xffc00
#define HWIO_SAW4_SPM_DLY_DLY2_SHFT                             0xa
#define HWIO_SAW4_SPM_DLY_DLY1_BMSK                           0x3ff
#define HWIO_SAW4_SPM_DLY_DLY1_SHFT                             0x0

#define HWIO_SAW4_SPM_WAKEUP_CNT_ADDR(core)              ((core) + 0x00000008)
#define HWIO_SAW4_SPM_WAKEUP_CNT_RMSK                    0xffffffff
#define HWIO_SAW4_SPM_WAKEUP_CNT_IN(core)    \
        in_dword_masked(HWIO_SAW4_SPM_WAKEUP_CNT_ADDR(core), HWIO_SAW4_SPM_WAKEUP_CNT_RMSK)
#define HWIO_SAW4_SPM_WAKEUP_CNT_INM(core,m)      \
        in_dword_masked(HWIO_SAW4_SPM_WAKEUP_CNT_ADDR(core), m)
#define HWIO_SAW4_SPM_WAKEUP_CNT_OUT(core,v)      \
        out_dword(HWIO_SAW4_SPM_WAKEUP_CNT_ADDR(core),v)
#define HWIO_SAW4_SPM_WAKEUP_CNT_OUTM(core,m,v) \
        out_dword_masked_ns(HWIO_SAW4_SPM_WAKEUP_CNT_ADDR(core),m,v,HWIO_SAW4_SPM_WAKEUP_CNT_IN(core))
#define HWIO_SAW4_SPM_WAKEUP_CNT_CNT_BMSK                0xffffffff
#define HWIO_SAW4_SPM_WAKEUP_CNT_CNT_SHFT                       0x0

#define HWIO_SAW4_CFG_ADDR(core)                         ((core) + 0x0000000c)
#define HWIO_SAW4_CFG_RMSK                                    0x31f
#define HWIO_SAW4_CFG_IN(core)    \
        in_dword_masked(HWIO_SAW4_CFG_ADDR(core), HWIO_SAW4_CFG_RMSK)
#define HWIO_SAW4_CFG_INM(core,m)      \
        in_dword_masked(HWIO_SAW4_CFG_ADDR(core), m)
#define HWIO_SAW4_CFG_OUT(core,v)      \
        out_dword(HWIO_SAW4_CFG_ADDR(core),v)
#define HWIO_SAW4_CFG_OUTM(core,m,v) \
        out_dword_masked_ns(HWIO_SAW4_CFG_ADDR(core),m,v,HWIO_SAW4_CFG_IN(core))
#define HWIO_SAW4_CFG_TEST_BUS_EN_BMSK                        0x200
#define HWIO_SAW4_CFG_TEST_BUS_EN_SHFT                          0x9
#define HWIO_SAW4_CFG_FRC_REF_CLK_ON_BMSK                     0x100
#define HWIO_SAW4_CFG_FRC_REF_CLK_ON_SHFT                       0x8
#define HWIO_SAW4_CFG_CLK_DIV_BMSK                             0x1f
#define HWIO_SAW4_CFG_CLK_DIV_SHFT                              0x0

#define HWIO_SAW4_SPM_SLP_SEQ_ENTRY_n_ADDR(core,n)       ((core) + 0x00000400 + 0x4 * (n))
#define HWIO_SAW4_SPM_SLP_SEQ_ENTRY_n_RMSK               0xffffffff
#define HWIO_SAW4_SPM_SLP_SEQ_ENTRY_n_MAXn                       31
#define HWIO_SAW4_SPM_SLP_SEQ_ENTRY_n_INI(core,n)        \
        in_dword_masked(HWIO_SAW4_SPM_SLP_SEQ_ENTRY_n_ADDR(core,n), HWIO_SAW4_SPM_SLP_SEQ_ENTRY_n_RMSK)
#define HWIO_SAW4_SPM_SLP_SEQ_ENTRY_n_INMI(core,n,mask)    \
        in_dword_masked(HWIO_SAW4_SPM_SLP_SEQ_ENTRY_n_ADDR(core,n), mask)
#define HWIO_SAW4_SPM_SLP_SEQ_ENTRY_n_OUTI(core,n,val)    \
        out_dword(HWIO_SAW4_SPM_SLP_SEQ_ENTRY_n_ADDR(core,n),val)
#define HWIO_SAW4_SPM_SLP_SEQ_ENTRY_n_OUTMI(core,n,mask,val) \
        out_dword_masked_ns(HWIO_SAW4_SPM_SLP_SEQ_ENTRY_n_ADDR(core,n),mask,val,HWIO_SAW4_SPM_SLP_SEQ_ENTRY_n_INI(core,n))
#define HWIO_SAW4_SPM_SLP_SEQ_ENTRY_n_CMD3_BMSK          0xff000000
#define HWIO_SAW4_SPM_SLP_SEQ_ENTRY_n_CMD3_SHFT                0x18
#define HWIO_SAW4_SPM_SLP_SEQ_ENTRY_n_CMD2_BMSK            0xff0000
#define HWIO_SAW4_SPM_SLP_SEQ_ENTRY_n_CMD2_SHFT                0x10
#define HWIO_SAW4_SPM_SLP_SEQ_ENTRY_n_CMD1_BMSK              0xff00
#define HWIO_SAW4_SPM_SLP_SEQ_ENTRY_n_CMD1_SHFT                 0x8
#define HWIO_SAW4_SPM_SLP_SEQ_ENTRY_n_CMD0_BMSK                0xff
#define HWIO_SAW4_SPM_SLP_SEQ_ENTRY_n_CMD0_SHFT                 0x0

#define HWIO_SAW4_SPM_PMIC_DATA_n_ADDR(core,n)           ((core) + 0x00000040 + 0x4 * (n))
#define HWIO_SAW4_SPM_PMIC_DATA_n_RMSK                    0x717ffff
#define HWIO_SAW4_SPM_PMIC_DATA_n_MAXn                            5
#define HWIO_SAW4_SPM_PMIC_DATA_n_INI(core,n)        \
        in_dword_masked(HWIO_SAW4_SPM_PMIC_DATA_n_ADDR(core,n), HWIO_SAW4_SPM_PMIC_DATA_n_RMSK)
#define HWIO_SAW4_SPM_PMIC_DATA_n_INMI(core,n,mask)    \
        in_dword_masked(HWIO_SAW4_SPM_PMIC_DATA_n_ADDR(core,n), mask)
#define HWIO_SAW4_SPM_PMIC_DATA_n_OUTI(core,n,val)    \
        out_dword(HWIO_SAW4_SPM_PMIC_DATA_n_ADDR(core,n),val)
#define HWIO_SAW4_SPM_PMIC_DATA_n_OUTMI(core,n,mask,val) \
        out_dword_masked_ns(HWIO_SAW4_SPM_PMIC_DATA_n_ADDR(core,n),mask,val,HWIO_SAW4_SPM_PMIC_DATA_n_INI(core,n))
#define HWIO_SAW4_SPM_PMIC_DATA_n_DLY_BMSK                0x7000000
#define HWIO_SAW4_SPM_PMIC_DATA_n_DLY_SHFT                     0x18
#define HWIO_SAW4_SPM_PMIC_DATA_n_SIZE_BMSK                0x100000
#define HWIO_SAW4_SPM_PMIC_DATA_n_SIZE_SHFT                    0x14
#define HWIO_SAW4_SPM_PMIC_DATA_n_ADR_IDX_BMSK              0x70000
#define HWIO_SAW4_SPM_PMIC_DATA_n_ADR_IDX_SHFT                 0x10
#define HWIO_SAW4_SPM_PMIC_DATA_n_DATA_BMSK                  0xffff
#define HWIO_SAW4_SPM_PMIC_DATA_n_DATA_SHFT                     0x0

/*----------------------------------------------------------------------------
 * MODULE: SAW4_AVS
 *--------------------------------------------------------------------------*/

#define SAW4_AVS_REG_BASE_OFFS                                0x800

#define HWIO_SAW4_DCM_CTL_ADDR(core)                              ((core) + SAW4_AVS_REG_BASE_OFFS + 0x00000000)
#define HWIO_SAW4_DCM_CTL_OFFS                                    (SAW4_AVS_REG_BASE_OFFS + 0x00000000)
#define HWIO_SAW4_DCM_CTL_RMSK                                         0x17f
#define HWIO_SAW4_DCM_CTL_IN(core)    \
        in_dword_masked(HWIO_SAW4_DCM_CTL_ADDR(core), HWIO_SAW4_DCM_CTL_RMSK)
#define HWIO_SAW4_DCM_CTL_INM(core,m)      \
        in_dword_masked(HWIO_SAW4_DCM_CTL_ADDR(core), m)
#define HWIO_SAW4_DCM_CTL_OUT(core,v)      \
        out_dword(HWIO_SAW4_DCM_CTL_ADDR(core),v)
#define HWIO_SAW4_DCM_CTL_OUTM(core,m,v) \
        out_dword_masked_ns(HWIO_SAW4_DCM_CTL_ADDR(core),m,v,HWIO_SAW4_DCM_CTL_IN(core))
#define HWIO_SAW4_DCM_CTL_DSBL_TRTL_BMSK                               0x100
#define HWIO_SAW4_DCM_CTL_DSBL_TRTL_SHFT                                 0x8
#define HWIO_SAW4_DCM_CTL_MIN_MODE_BMSK                                 0x70
#define HWIO_SAW4_DCM_CTL_MIN_MODE_SHFT                                  0x4
#define HWIO_SAW4_DCM_CTL_DLM_REQ_EN_BMSK                                0x8
#define HWIO_SAW4_DCM_CTL_DLM_REQ_EN_SHFT                                0x3
#define HWIO_SAW4_DCM_CTL_LMT_TRTL_EN_BMSK                               0x4
#define HWIO_SAW4_DCM_CTL_LMT_TRTL_EN_SHFT                               0x2
#define HWIO_SAW4_DCM_CTL_MAX_EFF_EN_BMSK                                0x2
#define HWIO_SAW4_DCM_CTL_MAX_EFF_EN_SHFT                                0x1
#define HWIO_SAW4_DCM_CTL_DCM_EN_BMSK                                    0x1
#define HWIO_SAW4_DCM_CTL_DCM_EN_SHFT                                    0x0

#define HWIO_SAW4_DCM_HYSTERESIS_ADDR(core)                       ((core) + SAW4_AVS_REG_BASE_OFFS + 0x00000004)
#define HWIO_SAW4_DCM_HYSTERESIS_OFFS                             (SAW4_AVS_REG_BASE_OFFS + 0x00000004)
#define HWIO_SAW4_DCM_HYSTERESIS_RMSK                                0x71f1f
#define HWIO_SAW4_DCM_HYSTERESIS_IN(core)    \
        in_dword_masked(HWIO_SAW4_DCM_HYSTERESIS_ADDR(core), HWIO_SAW4_DCM_HYSTERESIS_RMSK)
#define HWIO_SAW4_DCM_HYSTERESIS_INM(core,m)      \
        in_dword_masked(HWIO_SAW4_DCM_HYSTERESIS_ADDR(core), m)
#define HWIO_SAW4_DCM_HYSTERESIS_OUT(core,v)      \
        out_dword(HWIO_SAW4_DCM_HYSTERESIS_ADDR(core),v)
#define HWIO_SAW4_DCM_HYSTERESIS_OUTM(core,m,v) \
        out_dword_masked_ns(HWIO_SAW4_DCM_HYSTERESIS_ADDR(core),m,v,HWIO_SAW4_DCM_HYSTERESIS_IN(core))
#define HWIO_SAW4_DCM_HYSTERESIS_LMT_CNT_BMSK                        0x70000
#define HWIO_SAW4_DCM_HYSTERESIS_LMT_CNT_SHFT                           0x10
#define HWIO_SAW4_DCM_HYSTERESIS_CNT_PH_DN_BMSK                       0x1f00
#define HWIO_SAW4_DCM_HYSTERESIS_CNT_PH_DN_SHFT                          0x8
#define HWIO_SAW4_DCM_HYSTERESIS_CNT_PH_UP_BMSK                         0x1f
#define HWIO_SAW4_DCM_HYSTERESIS_CNT_PH_UP_SHFT                          0x0

#define HWIO_SAW4_DCM_PMIC_CTL_ADDR(core)                         ((core) + SAW4_AVS_REG_BASE_OFFS + 0x00000008)
#define HWIO_SAW4_DCM_PMIC_CTL_OFFS                               (SAW4_AVS_REG_BASE_OFFS + 0x00000008)
#define HWIO_SAW4_DCM_PMIC_CTL_RMSK                               0xff17ff17
#define HWIO_SAW4_DCM_PMIC_CTL_IN(core)    \
        in_dword_masked(HWIO_SAW4_DCM_PMIC_CTL_ADDR(core), HWIO_SAW4_DCM_PMIC_CTL_RMSK)
#define HWIO_SAW4_DCM_PMIC_CTL_INM(core,m)      \
        in_dword_masked(HWIO_SAW4_DCM_PMIC_CTL_ADDR(core), m)
#define HWIO_SAW4_DCM_PMIC_CTL_OUT(core,v)      \
        out_dword(HWIO_SAW4_DCM_PMIC_CTL_ADDR(core),v)
#define HWIO_SAW4_DCM_PMIC_CTL_OUTM(core,m,v) \
        out_dword_masked_ns(HWIO_SAW4_DCM_PMIC_CTL_ADDR(core),m,v,HWIO_SAW4_DCM_PMIC_CTL_IN(core))
#define HWIO_SAW4_DCM_PMIC_CTL_MODE_CTL_DLY_BMSK                  0xff000000
#define HWIO_SAW4_DCM_PMIC_CTL_MODE_CTL_DLY_SHFT                        0x18
#define HWIO_SAW4_DCM_PMIC_CTL_MODE_CTL_SIZE_BMSK                   0x100000
#define HWIO_SAW4_DCM_PMIC_CTL_MODE_CTL_SIZE_SHFT                       0x14
#define HWIO_SAW4_DCM_PMIC_CTL_MODE_CTL_ADR_IDX_BMSK                 0x70000
#define HWIO_SAW4_DCM_PMIC_CTL_MODE_CTL_ADR_IDX_SHFT                    0x10
#define HWIO_SAW4_DCM_PMIC_CTL_PH_CNT_DLY_BMSK                        0xff00
#define HWIO_SAW4_DCM_PMIC_CTL_PH_CNT_DLY_SHFT                           0x8
#define HWIO_SAW4_DCM_PMIC_CTL_PH_CNT_SIZE_BMSK                         0x10
#define HWIO_SAW4_DCM_PMIC_CTL_PH_CNT_SIZE_SHFT                          0x4
#define HWIO_SAW4_DCM_PMIC_CTL_PH_CNT_ADR_IDX_BMSK                       0x7
#define HWIO_SAW4_DCM_PMIC_CTL_PH_CNT_ADR_IDX_SHFT                       0x0

#define HWIO_SAW4_DCM_STS_ADDR(core)                              ((core) + SAW4_AVS_REG_BASE_OFFS + 0x0000000c)
#define HWIO_SAW4_DCM_STS_OFFS                                    (SAW4_AVS_REG_BASE_OFFS + 0x0000000c)
#define HWIO_SAW4_DCM_STS_RMSK                                    0xffff0377
#define HWIO_SAW4_DCM_STS_IN(core)    \
        in_dword_masked(HWIO_SAW4_DCM_STS_ADDR(core), HWIO_SAW4_DCM_STS_RMSK)
#define HWIO_SAW4_DCM_STS_INM(core,m)      \
        in_dword_masked(HWIO_SAW4_DCM_STS_ADDR(core), m)
#define HWIO_SAW4_DCM_STS_DLM_MODE_BMSK                           0xe0000000
#define HWIO_SAW4_DCM_STS_DLM_MODE_SHFT                                 0x1d
#define HWIO_SAW4_DCM_STS_IMEAS_SUM_BMSK                          0x1fff0000
#define HWIO_SAW4_DCM_STS_IMEAS_SUM_SHFT                                0x10
#define HWIO_SAW4_DCM_STS_CPU_THRTL_STKY_BMSK                          0x200
#define HWIO_SAW4_DCM_STS_CPU_THRTL_STKY_SHFT                            0x9
#define HWIO_SAW4_DCM_STS_CPU_THRTL_BMSK                               0x100
#define HWIO_SAW4_DCM_STS_CPU_THRTL_SHFT                                 0x8
#define HWIO_SAW4_DCM_STS_NEW_MODE_BMSK                                 0x70
#define HWIO_SAW4_DCM_STS_NEW_MODE_SHFT                                  0x4
#define HWIO_SAW4_DCM_STS_CURR_MODE_BMSK                                 0x7
#define HWIO_SAW4_DCM_STS_CURR_MODE_SHFT                                 0x0

#define HWIO_SAW4_DCM_PFM_LIMIT_ADDR(core)                        ((core) + SAW4_AVS_REG_BASE_OFFS + 0x00000010)
#define HWIO_SAW4_DCM_PFM_LIMIT_OFFS                              (SAW4_AVS_REG_BASE_OFFS + 0x00000010)
#define HWIO_SAW4_DCM_PFM_LIMIT_RMSK                                  0x1fff
#define HWIO_SAW4_DCM_PFM_LIMIT_IN(core)    \
        in_dword_masked(HWIO_SAW4_DCM_PFM_LIMIT_ADDR(core), HWIO_SAW4_DCM_PFM_LIMIT_RMSK)
#define HWIO_SAW4_DCM_PFM_LIMIT_INM(core,m)      \
        in_dword_masked(HWIO_SAW4_DCM_PFM_LIMIT_ADDR(core), m)
#define HWIO_SAW4_DCM_PFM_LIMIT_OUT(core,v)      \
        out_dword(HWIO_SAW4_DCM_PFM_LIMIT_ADDR(core),v)
#define HWIO_SAW4_DCM_PFM_LIMIT_OUTM(core,m,v) \
        out_dword_masked_ns(HWIO_SAW4_DCM_PFM_LIMIT_ADDR(core),m,v,HWIO_SAW4_DCM_PFM_LIMIT_IN(core))
#define HWIO_SAW4_DCM_PFM_LIMIT_LIMIT_BMSK                            0x1fff
#define HWIO_SAW4_DCM_PFM_LIMIT_LIMIT_SHFT                               0x0

#define HWIO_SAW4_DCM_PH1_LIMIT_ADDR(core)                        ((core) + SAW4_AVS_REG_BASE_OFFS + 0x00000014)
#define HWIO_SAW4_DCM_PH1_LIMIT_OFFS                              (SAW4_AVS_REG_BASE_OFFS + 0x00000014)
#define HWIO_SAW4_DCM_PH1_LIMIT_RMSK                                  0x1fff
#define HWIO_SAW4_DCM_PH1_LIMIT_IN(core)    \
        in_dword_masked(HWIO_SAW4_DCM_PH1_LIMIT_ADDR(core), HWIO_SAW4_DCM_PH1_LIMIT_RMSK)
#define HWIO_SAW4_DCM_PH1_LIMIT_INM(core,m)      \
        in_dword_masked(HWIO_SAW4_DCM_PH1_LIMIT_ADDR(core), m)
#define HWIO_SAW4_DCM_PH1_LIMIT_OUT(core,v)      \
        out_dword(HWIO_SAW4_DCM_PH1_LIMIT_ADDR(core),v)
#define HWIO_SAW4_DCM_PH1_LIMIT_OUTM(core,m,v) \
        out_dword_masked_ns(HWIO_SAW4_DCM_PH1_LIMIT_ADDR(core),m,v,HWIO_SAW4_DCM_PH1_LIMIT_IN(core))
#define HWIO_SAW4_DCM_PH1_LIMIT_LIMIT_BMSK                            0x1fff
#define HWIO_SAW4_DCM_PH1_LIMIT_LIMIT_SHFT                               0x0

#define HWIO_SAW4_DCM_PH2_LIMIT_ADDR(core)                        ((core) + SAW4_AVS_REG_BASE_OFFS + 0x00000018)
#define HWIO_SAW4_DCM_PH2_LIMIT_OFFS                              (SAW4_AVS_REG_BASE_OFFS + 0x00000018)
#define HWIO_SAW4_DCM_PH2_LIMIT_RMSK                                  0x1fff
#define HWIO_SAW4_DCM_PH2_LIMIT_IN(core)    \
        in_dword_masked(HWIO_SAW4_DCM_PH2_LIMIT_ADDR(core), HWIO_SAW4_DCM_PH2_LIMIT_RMSK)
#define HWIO_SAW4_DCM_PH2_LIMIT_INM(core,m)      \
        in_dword_masked(HWIO_SAW4_DCM_PH2_LIMIT_ADDR(core), m)
#define HWIO_SAW4_DCM_PH2_LIMIT_OUT(core,v)      \
        out_dword(HWIO_SAW4_DCM_PH2_LIMIT_ADDR(core),v)
#define HWIO_SAW4_DCM_PH2_LIMIT_OUTM(core,m,v) \
        out_dword_masked_ns(HWIO_SAW4_DCM_PH2_LIMIT_ADDR(core),m,v,HWIO_SAW4_DCM_PH2_LIMIT_IN(core))
#define HWIO_SAW4_DCM_PH2_LIMIT_LIMIT_BMSK                            0x1fff
#define HWIO_SAW4_DCM_PH2_LIMIT_LIMIT_SHFT                               0x0

#define HWIO_SAW4_DCM_PH4_LIMIT_ADDR(core)                        ((core) + SAW4_AVS_REG_BASE_OFFS + 0x0000001c)
#define HWIO_SAW4_DCM_PH4_LIMIT_OFFS                              (SAW4_AVS_REG_BASE_OFFS + 0x0000001c)
#define HWIO_SAW4_DCM_PH4_LIMIT_RMSK                                  0x1fff
#define HWIO_SAW4_DCM_PH4_LIMIT_IN(core)    \
        in_dword_masked(HWIO_SAW4_DCM_PH4_LIMIT_ADDR(core), HWIO_SAW4_DCM_PH4_LIMIT_RMSK)
#define HWIO_SAW4_DCM_PH4_LIMIT_INM(core,m)      \
        in_dword_masked(HWIO_SAW4_DCM_PH4_LIMIT_ADDR(core), m)
#define HWIO_SAW4_DCM_PH4_LIMIT_OUT(core,v)      \
        out_dword(HWIO_SAW4_DCM_PH4_LIMIT_ADDR(core),v)
#define HWIO_SAW4_DCM_PH4_LIMIT_OUTM(core,m,v) \
        out_dword_masked_ns(HWIO_SAW4_DCM_PH4_LIMIT_ADDR(core),m,v,HWIO_SAW4_DCM_PH4_LIMIT_IN(core))
#define HWIO_SAW4_DCM_PH4_LIMIT_LIMIT_BMSK                            0x1fff
#define HWIO_SAW4_DCM_PH4_LIMIT_LIMIT_SHFT                               0x0

#define HWIO_SAW4_DCM_PFM_EFF_MAX_ADDR(core)                      ((core) + SAW4_AVS_REG_BASE_OFFS + 0x00000020)
#define HWIO_SAW4_DCM_PFM_EFF_MAX_OFFS                            (SAW4_AVS_REG_BASE_OFFS + 0x00000020)
#define HWIO_SAW4_DCM_PFM_EFF_MAX_RMSK                                0x1fff
#define HWIO_SAW4_DCM_PFM_EFF_MAX_IN(core)    \
        in_dword_masked(HWIO_SAW4_DCM_PFM_EFF_MAX_ADDR(core), HWIO_SAW4_DCM_PFM_EFF_MAX_RMSK)
#define HWIO_SAW4_DCM_PFM_EFF_MAX_INM(core,m)      \
        in_dword_masked(HWIO_SAW4_DCM_PFM_EFF_MAX_ADDR(core), m)
#define HWIO_SAW4_DCM_PFM_EFF_MAX_OUT(core,v)      \
        out_dword(HWIO_SAW4_DCM_PFM_EFF_MAX_ADDR(core),v)
#define HWIO_SAW4_DCM_PFM_EFF_MAX_OUTM(core,m,v) \
        out_dword_masked_ns(HWIO_SAW4_DCM_PFM_EFF_MAX_ADDR(core),m,v,HWIO_SAW4_DCM_PFM_EFF_MAX_IN(core))
#define HWIO_SAW4_DCM_PFM_EFF_MAX_EFF_MAX_BMSK                        0x1fff
#define HWIO_SAW4_DCM_PFM_EFF_MAX_EFF_MAX_SHFT                           0x0

#define HWIO_SAW4_DCM_PH1_EFF_MAX_ADDR(core)                      ((core) + SAW4_AVS_REG_BASE_OFFS + 0x00000024)
#define HWIO_SAW4_DCM_PH1_EFF_MAX_OFFS                            (SAW4_AVS_REG_BASE_OFFS + 0x00000024)
#define HWIO_SAW4_DCM_PH1_EFF_MAX_RMSK                                0x1fff
#define HWIO_SAW4_DCM_PH1_EFF_MAX_IN(core)    \
        in_dword_masked(HWIO_SAW4_DCM_PH1_EFF_MAX_ADDR(core), HWIO_SAW4_DCM_PH1_EFF_MAX_RMSK)
#define HWIO_SAW4_DCM_PH1_EFF_MAX_INM(core,m)      \
        in_dword_masked(HWIO_SAW4_DCM_PH1_EFF_MAX_ADDR(core), m)
#define HWIO_SAW4_DCM_PH1_EFF_MAX_OUT(core,v)      \
        out_dword(HWIO_SAW4_DCM_PH1_EFF_MAX_ADDR(core),v)
#define HWIO_SAW4_DCM_PH1_EFF_MAX_OUTM(core,m,v) \
        out_dword_masked_ns(HWIO_SAW4_DCM_PH1_EFF_MAX_ADDR(core),m,v,HWIO_SAW4_DCM_PH1_EFF_MAX_IN(core))
#define HWIO_SAW4_DCM_PH1_EFF_MAX_EFF_MAX_BMSK                        0x1fff
#define HWIO_SAW4_DCM_PH1_EFF_MAX_EFF_MAX_SHFT                           0x0

#define HWIO_SAW4_DCM_PH2_EFF_MAX_ADDR(core)                      ((core) + SAW4_AVS_REG_BASE_OFFS + 0x00000028)
#define HWIO_SAW4_DCM_PH2_EFF_MAX_OFFS                            (SAW4_AVS_REG_BASE_OFFS + 0x00000028)
#define HWIO_SAW4_DCM_PH2_EFF_MAX_RMSK                                0x1fff
#define HWIO_SAW4_DCM_PH2_EFF_MAX_IN(core)    \
        in_dword_masked(HWIO_SAW4_DCM_PH2_EFF_MAX_ADDR(core), HWIO_SAW4_DCM_PH2_EFF_MAX_RMSK)
#define HWIO_SAW4_DCM_PH2_EFF_MAX_INM(core,m)      \
        in_dword_masked(HWIO_SAW4_DCM_PH2_EFF_MAX_ADDR(core), m)
#define HWIO_SAW4_DCM_PH2_EFF_MAX_OUT(core,v)      \
        out_dword(HWIO_SAW4_DCM_PH2_EFF_MAX_ADDR(core),v)
#define HWIO_SAW4_DCM_PH2_EFF_MAX_OUTM(core,m,v) \
        out_dword_masked_ns(HWIO_SAW4_DCM_PH2_EFF_MAX_ADDR(core),m,v,HWIO_SAW4_DCM_PH2_EFF_MAX_IN(core))
#define HWIO_SAW4_DCM_PH2_EFF_MAX_EFF_MAX_BMSK                        0x1fff
#define HWIO_SAW4_DCM_PH2_EFF_MAX_EFF_MAX_SHFT                           0x0

#define HWIO_SAW4_DCM_LPM_PMIC_DATA_ADDR(core)                    ((core) + SAW4_AVS_REG_BASE_OFFS + 0x0000002c)
#define HWIO_SAW4_DCM_LPM_PMIC_DATA_OFFS                          (SAW4_AVS_REG_BASE_OFFS + 0x0000002c)
#define HWIO_SAW4_DCM_LPM_PMIC_DATA_RMSK                              0xffff
#define HWIO_SAW4_DCM_LPM_PMIC_DATA_IN(core)    \
        in_dword_masked(HWIO_SAW4_DCM_LPM_PMIC_DATA_ADDR(core), HWIO_SAW4_DCM_LPM_PMIC_DATA_RMSK)
#define HWIO_SAW4_DCM_LPM_PMIC_DATA_INM(core,m)      \
        in_dword_masked(HWIO_SAW4_DCM_LPM_PMIC_DATA_ADDR(core), m)
#define HWIO_SAW4_DCM_LPM_PMIC_DATA_OUT(core,v)      \
        out_dword(HWIO_SAW4_DCM_LPM_PMIC_DATA_ADDR(core),v)
#define HWIO_SAW4_DCM_LPM_PMIC_DATA_OUTM(core,m,v) \
        out_dword_masked_ns(HWIO_SAW4_DCM_LPM_PMIC_DATA_ADDR(core),m,v,HWIO_SAW4_DCM_LPM_PMIC_DATA_IN(core))
#define HWIO_SAW4_DCM_LPM_PMIC_DATA_DATA_BMSK                         0xffff
#define HWIO_SAW4_DCM_LPM_PMIC_DATA_DATA_SHFT                            0x0

#define HWIO_SAW4_DCM_NPM_PMIC_DATA_ADDR(core)                    ((core) + SAW4_AVS_REG_BASE_OFFS + 0x00000030)
#define HWIO_SAW4_DCM_NPM_PMIC_DATA_OFFS                          (SAW4_AVS_REG_BASE_OFFS + 0x00000030)
#define HWIO_SAW4_DCM_NPM_PMIC_DATA_RMSK                              0xffff
#define HWIO_SAW4_DCM_NPM_PMIC_DATA_IN(core)    \
        in_dword_masked(HWIO_SAW4_DCM_NPM_PMIC_DATA_ADDR(core), HWIO_SAW4_DCM_NPM_PMIC_DATA_RMSK)
#define HWIO_SAW4_DCM_NPM_PMIC_DATA_INM(core,m)      \
        in_dword_masked(HWIO_SAW4_DCM_NPM_PMIC_DATA_ADDR(core), m)
#define HWIO_SAW4_DCM_NPM_PMIC_DATA_OUT(core,v)      \
        out_dword(HWIO_SAW4_DCM_NPM_PMIC_DATA_ADDR(core),v)
#define HWIO_SAW4_DCM_NPM_PMIC_DATA_OUTM(core,m,v) \
        out_dword_masked_ns(HWIO_SAW4_DCM_NPM_PMIC_DATA_ADDR(core),m,v,HWIO_SAW4_DCM_NPM_PMIC_DATA_IN(core))
#define HWIO_SAW4_DCM_NPM_PMIC_DATA_DATA_BMSK                         0xffff
#define HWIO_SAW4_DCM_NPM_PMIC_DATA_DATA_SHFT                            0x0

#define HWIO_SAW4_DCM_PH1_PMIC_DATA_ADDR(core)                    ((core) + SAW4_AVS_REG_BASE_OFFS + 0x00000034)
#define HWIO_SAW4_DCM_PH1_PMIC_DATA_OFFS                          (SAW4_AVS_REG_BASE_OFFS + 0x00000034)
#define HWIO_SAW4_DCM_PH1_PMIC_DATA_RMSK                              0xffff
#define HWIO_SAW4_DCM_PH1_PMIC_DATA_IN(core)    \
        in_dword_masked(HWIO_SAW4_DCM_PH1_PMIC_DATA_ADDR(core), HWIO_SAW4_DCM_PH1_PMIC_DATA_RMSK)
#define HWIO_SAW4_DCM_PH1_PMIC_DATA_INM(core,m)      \
        in_dword_masked(HWIO_SAW4_DCM_PH1_PMIC_DATA_ADDR(core), m)
#define HWIO_SAW4_DCM_PH1_PMIC_DATA_OUT(core,v)      \
        out_dword(HWIO_SAW4_DCM_PH1_PMIC_DATA_ADDR(core),v)
#define HWIO_SAW4_DCM_PH1_PMIC_DATA_OUTM(core,m,v) \
        out_dword_masked_ns(HWIO_SAW4_DCM_PH1_PMIC_DATA_ADDR(core),m,v,HWIO_SAW4_DCM_PH1_PMIC_DATA_IN(core))
#define HWIO_SAW4_DCM_PH1_PMIC_DATA_DATA_BMSK                         0xffff
#define HWIO_SAW4_DCM_PH1_PMIC_DATA_DATA_SHFT                            0x0

#define HWIO_SAW4_DCM_PH2_PMIC_DATA_ADDR(core)                    ((core) + SAW4_AVS_REG_BASE_OFFS + 0x00000038)
#define HWIO_SAW4_DCM_PH2_PMIC_DATA_OFFS                          (SAW4_AVS_REG_BASE_OFFS + 0x00000038)
#define HWIO_SAW4_DCM_PH2_PMIC_DATA_RMSK                              0xffff
#define HWIO_SAW4_DCM_PH2_PMIC_DATA_IN(core)    \
        in_dword_masked(HWIO_SAW4_DCM_PH2_PMIC_DATA_ADDR(core), HWIO_SAW4_DCM_PH2_PMIC_DATA_RMSK)
#define HWIO_SAW4_DCM_PH2_PMIC_DATA_INM(core,m)      \
        in_dword_masked(HWIO_SAW4_DCM_PH2_PMIC_DATA_ADDR(core), m)
#define HWIO_SAW4_DCM_PH2_PMIC_DATA_OUT(core,v)      \
        out_dword(HWIO_SAW4_DCM_PH2_PMIC_DATA_ADDR(core),v)
#define HWIO_SAW4_DCM_PH2_PMIC_DATA_OUTM(core,m,v) \
        out_dword_masked_ns(HWIO_SAW4_DCM_PH2_PMIC_DATA_ADDR(core),m,v,HWIO_SAW4_DCM_PH2_PMIC_DATA_IN(core))
#define HWIO_SAW4_DCM_PH2_PMIC_DATA_DATA_BMSK                         0xffff
#define HWIO_SAW4_DCM_PH2_PMIC_DATA_DATA_SHFT                            0x0

#define HWIO_SAW4_DCM_PH4_PMIC_DATA_ADDR(core)                    ((core) + SAW4_AVS_REG_BASE_OFFS + 0x0000003c)
#define HWIO_SAW4_DCM_PH4_PMIC_DATA_OFFS                          (SAW4_AVS_REG_BASE_OFFS + 0x0000003c)
#define HWIO_SAW4_DCM_PH4_PMIC_DATA_RMSK                              0xffff
#define HWIO_SAW4_DCM_PH4_PMIC_DATA_IN(core)    \
        in_dword_masked(HWIO_SAW4_DCM_PH4_PMIC_DATA_ADDR(core), HWIO_SAW4_DCM_PH4_PMIC_DATA_RMSK)
#define HWIO_SAW4_DCM_PH4_PMIC_DATA_INM(core,m)      \
        in_dword_masked(HWIO_SAW4_DCM_PH4_PMIC_DATA_ADDR(core), m)
#define HWIO_SAW4_DCM_PH4_PMIC_DATA_OUT(core,v)      \
        out_dword(HWIO_SAW4_DCM_PH4_PMIC_DATA_ADDR(core),v)
#define HWIO_SAW4_DCM_PH4_PMIC_DATA_OUTM(core,m,v) \
        out_dword_masked_ns(HWIO_SAW4_DCM_PH4_PMIC_DATA_ADDR(core),m,v,HWIO_SAW4_DCM_PH4_PMIC_DATA_IN(core))
#define HWIO_SAW4_DCM_PH4_PMIC_DATA_DATA_BMSK                         0xffff
#define HWIO_SAW4_DCM_PH4_PMIC_DATA_DATA_SHFT                            0x0

#define HWIO_SAW4_DCM_IMEAS_n_ADDR(core,n)                        ((core) + SAW4_AVS_REG_BASE_OFFS + 0x00000040 + 0x4 * (n))
#define HWIO_SAW4_DCM_IMEAS_n_OFFS(core,n)                        (SAW4_AVS_REG_BASE_OFFS + 0x00000040 + 0x4 * (n))
#define HWIO_SAW4_DCM_IMEAS_n_RMSK                                0x800003ff
#define HWIO_SAW4_DCM_IMEAS_n_MAXn                                         5
#define HWIO_SAW4_DCM_IMEAS_n_INI(core,n)        \
        in_dword_masked(HWIO_SAW4_DCM_IMEAS_n_ADDR(core,n), HWIO_SAW4_DCM_IMEAS_n_RMSK)
#define HWIO_SAW4_DCM_IMEAS_n_INMI(core,n,mask)    \
        in_dword_masked(HWIO_SAW4_DCM_IMEAS_n_ADDR(core,n), mask)
#define HWIO_SAW4_DCM_IMEAS_n_IMEAS_VLD_BMSK                      0x80000000
#define HWIO_SAW4_DCM_IMEAS_n_IMEAS_VLD_SHFT                            0x1f
#define HWIO_SAW4_DCM_IMEAS_n_IMEAS_DIG_BMSK                           0x3ff
#define HWIO_SAW4_DCM_IMEAS_n_IMEAS_DIG_SHFT                             0x0

#define HWIO_SAW4_DCM_STATIC_CURRENT_ADDR(core)                   ((core) + SAW4_AVS_REG_BASE_OFFS + 0x00000080)
#define HWIO_SAW4_DCM_STATIC_CURRENT_OFFS                         (SAW4_AVS_REG_BASE_OFFS + 0x00000080)
#define HWIO_SAW4_DCM_STATIC_CURRENT_RMSK                              0x3ff
#define HWIO_SAW4_DCM_STATIC_CURRENT_IN(core)    \
        in_dword_masked(HWIO_SAW4_DCM_STATIC_CURRENT_ADDR(core), HWIO_SAW4_DCM_STATIC_CURRENT_RMSK)
#define HWIO_SAW4_DCM_STATIC_CURRENT_INM(core,m)      \
        in_dword_masked(HWIO_SAW4_DCM_STATIC_CURRENT_ADDR(core), m)
#define HWIO_SAW4_DCM_STATIC_CURRENT_OUT(core,v)      \
        out_dword(HWIO_SAW4_DCM_STATIC_CURRENT_ADDR(core),v)
#define HWIO_SAW4_DCM_STATIC_CURRENT_OUTM(core,m,v) \
        out_dword_masked_ns(HWIO_SAW4_DCM_STATIC_CURRENT_ADDR(core),m,v,HWIO_SAW4_DCM_STATIC_CURRENT_IN(core))
#define HWIO_SAW4_DCM_STATIC_CURRENT_STATIC_CURRENT_BMSK               0x3ff
#define HWIO_SAW4_DCM_STATIC_CURRENT_STATIC_CURRENT_SHFT                 0x0

#define HWIO_SAW4_VCTL_ADDR(core)                                 ((core) + SAW4_AVS_REG_BASE_OFFS + 0x00000100)
#define HWIO_SAW4_VCTL_OFFS                                       (SAW4_AVS_REG_BASE_OFFS + 0x00000100)
#define HWIO_SAW4_VCTL_RMSK                                         0x17ffff
#define HWIO_SAW4_VCTL_IN(core)    \
        in_dword_masked(HWIO_SAW4_VCTL_ADDR(core), HWIO_SAW4_VCTL_RMSK)
#define HWIO_SAW4_VCTL_INM(core,m)      \
        in_dword_masked(HWIO_SAW4_VCTL_ADDR(core), m)
#define HWIO_SAW4_VCTL_OUT(core,v)      \
        out_dword(HWIO_SAW4_VCTL_ADDR(core),v)
#define HWIO_SAW4_VCTL_OUTM(core,m,v) \
        out_dword_masked_ns(HWIO_SAW4_VCTL_ADDR(core),m,v,HWIO_SAW4_VCTL_IN(core))
#define HWIO_SAW4_VCTL_SIZE_BMSK                                    0x100000
#define HWIO_SAW4_VCTL_SIZE_SHFT                                        0x14
#define HWIO_SAW4_VCTL_ADR_IDX_BMSK                                  0x70000
#define HWIO_SAW4_VCTL_ADR_IDX_SHFT                                     0x10
#define HWIO_SAW4_VCTL_PMIC_DATA_BMSK                                 0xffff
#define HWIO_SAW4_VCTL_PMIC_DATA_SHFT                                    0x0

#define HWIO_SAW4_AVS_CTL_ADDR(core)                              ((core) + SAW4_AVS_REG_BASE_OFFS + 0x00000104)
#define HWIO_SAW4_AVS_CTL_OFFS                                    (SAW4_AVS_REG_BASE_OFFS + 0x00000104)
#define HWIO_SAW4_AVS_CTL_RMSK                                    0xffffdf3f
#define HWIO_SAW4_AVS_CTL_IN(core)    \
        in_dword_masked(HWIO_SAW4_AVS_CTL_ADDR(core), HWIO_SAW4_AVS_CTL_RMSK)
#define HWIO_SAW4_AVS_CTL_INM(core,m)      \
        in_dword_masked(HWIO_SAW4_AVS_CTL_ADDR(core), m)
#define HWIO_SAW4_AVS_CTL_OUT(core,v)      \
        out_dword(HWIO_SAW4_AVS_CTL_ADDR(core),v)
#define HWIO_SAW4_AVS_CTL_OUTM(core,m,v) \
        out_dword_masked_ns(HWIO_SAW4_AVS_CTL_ADDR(core),m,v,HWIO_SAW4_AVS_CTL_IN(core))
#define HWIO_SAW4_AVS_CTL_VLVL_STEP_DN_BMSK                       0xff000000
#define HWIO_SAW4_AVS_CTL_VLVL_STEP_DN_SHFT                             0x18
#define HWIO_SAW4_AVS_CTL_VLVL_STEP_UP_BMSK                         0xff0000
#define HWIO_SAW4_AVS_CTL_VLVL_STEP_UP_SHFT                             0x10
#define HWIO_SAW4_AVS_CTL_CPR_RAMP_EN_BMSK                            0x8000
#define HWIO_SAW4_AVS_CTL_CPR_RAMP_EN_SHFT                               0xf
#define HWIO_SAW4_AVS_CTL_VCTL_RAMP_EN_BMSK                           0x4000
#define HWIO_SAW4_AVS_CTL_VCTL_RAMP_EN_SHFT                              0xe
#define HWIO_SAW4_AVS_CTL_TMR_CLK_DIV_BMSK                            0x1f00
#define HWIO_SAW4_AVS_CTL_TMR_CLK_DIV_SHFT                               0x8
#define HWIO_SAW4_AVS_CTL_VLVL_WIDTH_BMSK                               0x20
#define HWIO_SAW4_AVS_CTL_VLVL_WIDTH_SHFT                                0x5
#define HWIO_SAW4_AVS_CTL_CTL_SEL_BMSK                                  0x10
#define HWIO_SAW4_AVS_CTL_CTL_SEL_SHFT                                   0x4
#define HWIO_SAW4_AVS_CTL_SW_DONE_INT_EN_BMSK                            0x8
#define HWIO_SAW4_AVS_CTL_SW_DONE_INT_EN_SHFT                            0x3
#define HWIO_SAW4_AVS_CTL_MAX_INT_EN_BMSK                                0x4
#define HWIO_SAW4_AVS_CTL_MAX_INT_EN_SHFT                                0x2
#define HWIO_SAW4_AVS_CTL_MIN_INT_EN_BMSK                                0x2
#define HWIO_SAW4_AVS_CTL_MIN_INT_EN_SHFT                                0x1
#define HWIO_SAW4_AVS_CTL_EN_BMSK                                        0x1
#define HWIO_SAW4_AVS_CTL_EN_SHFT                                        0x0

#define HWIO_SAW4_AVS_LIMIT_ADDR(core)                            ((core) + SAW4_AVS_REG_BASE_OFFS + 0x00000108)
#define HWIO_SAW4_AVS_LIMIT_OFFS                                  (SAW4_AVS_REG_BASE_OFFS + 0x00000108)
#define HWIO_SAW4_AVS_LIMIT_RMSK                                  0xffffffff
#define HWIO_SAW4_AVS_LIMIT_IN(core)    \
        in_dword_masked(HWIO_SAW4_AVS_LIMIT_ADDR(core), HWIO_SAW4_AVS_LIMIT_RMSK)
#define HWIO_SAW4_AVS_LIMIT_INM(core,m)      \
        in_dword_masked(HWIO_SAW4_AVS_LIMIT_ADDR(core), m)
#define HWIO_SAW4_AVS_LIMIT_OUT(core,v)      \
        out_dword(HWIO_SAW4_AVS_LIMIT_ADDR(core),v)
#define HWIO_SAW4_AVS_LIMIT_OUTM(core,m,v) \
        out_dword_masked_ns(HWIO_SAW4_AVS_LIMIT_ADDR(core),m,v,HWIO_SAW4_AVS_LIMIT_IN(core))
#define HWIO_SAW4_AVS_LIMIT_MAX_VLVL_BMSK                         0xffff0000
#define HWIO_SAW4_AVS_LIMIT_MAX_VLVL_SHFT                               0x10
#define HWIO_SAW4_AVS_LIMIT_MIN_VLVL_BMSK                             0xffff
#define HWIO_SAW4_AVS_LIMIT_MIN_VLVL_SHFT                                0x0

#define HWIO_SAW4_AVS_DLY_ADDR(core)                              ((core) + SAW4_AVS_REG_BASE_OFFS + 0x0000010c)
#define HWIO_SAW4_AVS_DLY_OFFS                                    (SAW4_AVS_REG_BASE_OFFS + 0x0000010c)
#define HWIO_SAW4_AVS_DLY_RMSK                                         0x3ff
#define HWIO_SAW4_AVS_DLY_IN(core)    \
        in_dword_masked(HWIO_SAW4_AVS_DLY_ADDR(core), HWIO_SAW4_AVS_DLY_RMSK)
#define HWIO_SAW4_AVS_DLY_INM(core,m)      \
        in_dword_masked(HWIO_SAW4_AVS_DLY_ADDR(core), m)
#define HWIO_SAW4_AVS_DLY_OUT(core,v)      \
        out_dword(HWIO_SAW4_AVS_DLY_ADDR(core),v)
#define HWIO_SAW4_AVS_DLY_OUTM(core,m,v) \
        out_dword_masked_ns(HWIO_SAW4_AVS_DLY_ADDR(core),m,v,HWIO_SAW4_AVS_DLY_IN(core))
#define HWIO_SAW4_AVS_DLY_AVS_DELAY_BMSK                               0x3ff
#define HWIO_SAW4_AVS_DLY_AVS_DELAY_SHFT                                 0x0

#define HWIO_SAW4_VCTL_DLY_ADDR(core)                             ((core) + SAW4_AVS_REG_BASE_OFFS + 0x00000110)
#define HWIO_SAW4_VCTL_DLY_OFFS                                   (SAW4_AVS_REG_BASE_OFFS + 0x00000110)
#define HWIO_SAW4_VCTL_DLY_RMSK                                        0x3ff
#define HWIO_SAW4_VCTL_DLY_IN(core)    \
        in_dword_masked(HWIO_SAW4_VCTL_DLY_ADDR(core), HWIO_SAW4_VCTL_DLY_RMSK)
#define HWIO_SAW4_VCTL_DLY_INM(core,m)      \
        in_dword_masked(HWIO_SAW4_VCTL_DLY_ADDR(core), m)
#define HWIO_SAW4_VCTL_DLY_OUT(core,v)      \
        out_dword(HWIO_SAW4_VCTL_DLY_ADDR(core),v)
#define HWIO_SAW4_VCTL_DLY_OUTM(core,m,v) \
        out_dword_masked_ns(HWIO_SAW4_VCTL_DLY_ADDR(core),m,v,HWIO_SAW4_VCTL_DLY_IN(core))
#define HWIO_SAW4_VCTL_DLY_VCTL_DELAY_BMSK                             0x3ff
#define HWIO_SAW4_VCTL_DLY_VCTL_DELAY_SHFT                               0x0

/*----------------------------------------------------------------------------
 * MODULE: SAW4_STS
 *--------------------------------------------------------------------------*/

#define SAW4_STS_REG_BASE_OFFS                          0xc00

#define HWIO_SAW4_SECURE_ADDR(core)                         ((core) + SAW4_STS_REG_BASE_OFFS + 0x00000000)
#define HWIO_SAW4_SECURE_OFFS                               (SAW4_STS_REG_BASE_OFFS + 0x00000000)
#define HWIO_SAW4_SECURE_RMSK                                      0x7
#define HWIO_SAW4_SECURE_IN(core)    \
        in_dword_masked(HWIO_SAW4_SECURE_ADDR(core), HWIO_SAW4_SECURE_RMSK)
#define HWIO_SAW4_SECURE_INM(core,m)      \
        in_dword_masked(HWIO_SAW4_SECURE_ADDR(core), m)
#define HWIO_SAW4_SECURE_OUT(core,v)      \
        out_dword(HWIO_SAW4_SECURE_ADDR(core),v)
#define HWIO_SAW4_SECURE_OUTM(core,m,v) \
        out_dword_masked_ns(HWIO_SAW4_SECURE_ADDR(core),m,v,HWIO_SAW4_SECURE_IN(core))
#define HWIO_SAW4_SECURE_SAW_CTL_BMSK                              0x4
#define HWIO_SAW4_SECURE_SAW_CTL_SHFT                              0x2
#define HWIO_SAW4_SECURE_PWR_CTL_BMSK                              0x2
#define HWIO_SAW4_SECURE_PWR_CTL_SHFT                              0x1
#define HWIO_SAW4_SECURE_VLT_CTL_BMSK                              0x1
#define HWIO_SAW4_SECURE_VLT_CTL_SHFT                              0x0

#define HWIO_SAW4_ID_ADDR(core)                             ((core) + SAW4_STS_REG_BASE_OFFS + 0x00000004)
#define HWIO_SAW4_ID_OFFS                                   (SAW4_STS_REG_BASE_OFFS + 0x00000004)
#define HWIO_SAW4_ID_RMSK                                   0xff3f1f7f
#define HWIO_SAW4_ID_IN(core)    \
        in_dword_masked(HWIO_SAW4_ID_ADDR(core), HWIO_SAW4_ID_RMSK)
#define HWIO_SAW4_ID_INM(core,m)      \
        in_dword_masked(HWIO_SAW4_ID_ADDR(core), m)
#define HWIO_SAW4_ID_NUM_SPM_ENTRY_BMSK                     0xff000000
#define HWIO_SAW4_ID_NUM_SPM_ENTRY_SHFT                           0x18
#define HWIO_SAW4_ID_NUM_PWR_CTL_BMSK                         0x3f0000
#define HWIO_SAW4_ID_NUM_PWR_CTL_SHFT                             0x10
#define HWIO_SAW4_ID_NUM_CVS_PMIC_DATA_BMSK                     0x1c00
#define HWIO_SAW4_ID_NUM_CVS_PMIC_DATA_SHFT                        0xa
#define HWIO_SAW4_ID_CVS_PRESENT_BMSK                            0x200
#define HWIO_SAW4_ID_CVS_PRESENT_SHFT                              0x9
#define HWIO_SAW4_ID_PMIC_DATA_WIDTH_BMSK                        0x100
#define HWIO_SAW4_ID_PMIC_DATA_WIDTH_SHFT                          0x8
#define HWIO_SAW4_ID_NUM_SPM_PMIC_DATA_BMSK                       0x70
#define HWIO_SAW4_ID_NUM_SPM_PMIC_DATA_SHFT                        0x4
#define HWIO_SAW4_ID_CFG_NS_ACCESS_BMSK                            0x8
#define HWIO_SAW4_ID_CFG_NS_ACCESS_SHFT                            0x3
#define HWIO_SAW4_ID_PMIC_ARB_INTF_BMSK                            0x4
#define HWIO_SAW4_ID_PMIC_ARB_INTF_SHFT                            0x2
#define HWIO_SAW4_ID_AVS_PRESENT_BMSK                              0x2
#define HWIO_SAW4_ID_AVS_PRESENT_SHFT                              0x1
#define HWIO_SAW4_ID_SPM_PRESENT_BMSK                              0x1
#define HWIO_SAW4_ID_SPM_PRESENT_SHFT                              0x0

#define HWIO_SAW4_SPM_STS_ADDR(core)                        ((core) + SAW4_STS_REG_BASE_OFFS + 0x0000000c)
#define HWIO_SAW4_SPM_STS_OFFS                              (SAW4_STS_REG_BASE_OFFS + 0x0000000c)
#define HWIO_SAW4_SPM_STS_RMSK                              0xffffffff
#define HWIO_SAW4_SPM_STS_IN(core)    \
        in_dword_masked(HWIO_SAW4_SPM_STS_ADDR(core), HWIO_SAW4_SPM_STS_RMSK)
#define HWIO_SAW4_SPM_STS_INM(core,m)      \
        in_dword_masked(HWIO_SAW4_SPM_STS_ADDR(core), m)
#define HWIO_SAW4_SPM_STS_SPM_EVENT_BMSK                    0xffff0000
#define HWIO_SAW4_SPM_STS_SPM_EVENT_SHFT                          0x10
#define HWIO_SAW4_SPM_STS_SHTDWN_REQ_BMSK                       0x8000
#define HWIO_SAW4_SPM_STS_SHTDWN_REQ_SHFT                          0xf
#define HWIO_SAW4_SPM_STS_SHTDWN_ACK_BMSK                       0x4000
#define HWIO_SAW4_SPM_STS_SHTDWN_ACK_SHFT                          0xe
#define HWIO_SAW4_SPM_STS_BRNGUP_REQ_BMSK                       0x2000
#define HWIO_SAW4_SPM_STS_BRNGUP_REQ_SHFT                          0xd
#define HWIO_SAW4_SPM_STS_BRNGUP_ACK_BMSK                       0x1000
#define HWIO_SAW4_SPM_STS_BRNGUP_ACK_SHFT                          0xc
#define HWIO_SAW4_SPM_STS_RPM_STATE_BMSK                         0xc00
#define HWIO_SAW4_SPM_STS_RPM_STATE_SHFT                           0xa
#define HWIO_SAW4_SPM_STS_SPM_BUSY_BMSK                          0x200
#define HWIO_SAW4_SPM_STS_SPM_BUSY_SHFT                            0x9
#define HWIO_SAW4_SPM_STS_SPM_CMD_ADDR_BMSK                      0x1ff
#define HWIO_SAW4_SPM_STS_SPM_CMD_ADDR_SHFT                        0x0

#define HWIO_SAW4_SPM_STS2_ADDR(core)                       ((core) + SAW4_STS_REG_BASE_OFFS + 0x00000010)
#define HWIO_SAW4_SPM_STS2_OFFS                             (SAW4_STS_REG_BASE_OFFS + 0x00000010)
#define HWIO_SAW4_SPM_STS2_RMSK                             0xffffffff
#define HWIO_SAW4_SPM_STS2_IN(core)    \
        in_dword_masked(HWIO_SAW4_SPM_STS2_ADDR(core), HWIO_SAW4_SPM_STS2_RMSK)
#define HWIO_SAW4_SPM_STS2_INM(core,m)      \
        in_dword_masked(HWIO_SAW4_SPM_STS2_ADDR(core), m)
#define HWIO_SAW4_SPM_STS2_CURR_PWR_CTL_BMSK                0xffffffff
#define HWIO_SAW4_SPM_STS2_CURR_PWR_CTL_SHFT                       0x0

#define HWIO_SAW4_AVS_STS_ADDR(core)                        ((core) + SAW4_STS_REG_BASE_OFFS + 0x00000014)
#define HWIO_SAW4_AVS_STS_OFFS                              (SAW4_STS_REG_BASE_OFFS + 0x00000014)
#define HWIO_SAW4_AVS_STS_RMSK                              0x3ff00fff
#define HWIO_SAW4_AVS_STS_IN(core)    \
        in_dword_masked(HWIO_SAW4_AVS_STS_ADDR(core), HWIO_SAW4_AVS_STS_RMSK)
#define HWIO_SAW4_AVS_STS_INM(core,m)      \
        in_dword_masked(HWIO_SAW4_AVS_STS_ADDR(core), m)
#define HWIO_SAW4_AVS_STS_AVS_CURR_DLY_BMSK                 0x3ff00000
#define HWIO_SAW4_AVS_STS_AVS_CURR_DLY_SHFT                       0x14
#define HWIO_SAW4_AVS_STS_SIC_SW_DONE_IRQ_BMSK                   0x800
#define HWIO_SAW4_AVS_STS_SIC_SW_DONE_IRQ_SHFT                     0xb
#define HWIO_SAW4_AVS_STS_SIC_IRQ_BMSK                           0x400
#define HWIO_SAW4_AVS_STS_SIC_IRQ_SHFT                             0xa
#define HWIO_SAW4_AVS_STS_AVS_ERR_BMSK                           0x200
#define HWIO_SAW4_AVS_STS_AVS_ERR_SHFT                             0x9
#define HWIO_SAW4_AVS_STS_AVS_ACK_BMSK                           0x100
#define HWIO_SAW4_AVS_STS_AVS_ACK_SHFT                             0x8
#define HWIO_SAW4_AVS_STS_VOLTAGE_RAMP_BMSK                       0x80
#define HWIO_SAW4_AVS_STS_VOLTAGE_RAMP_SHFT                        0x7
#define HWIO_SAW4_AVS_STS_SW_WR_PEND_BMSK                         0x40
#define HWIO_SAW4_AVS_STS_SW_WR_PEND_SHFT                          0x6
#define HWIO_SAW4_AVS_STS_MAX_INT_BMSK                            0x20
#define HWIO_SAW4_AVS_STS_MAX_INT_SHFT                             0x5
#define HWIO_SAW4_AVS_STS_MIN_INT_BMSK                            0x10
#define HWIO_SAW4_AVS_STS_MIN_INT_SHFT                             0x4
#define HWIO_SAW4_AVS_STS_CPU_UP_BMSK                              0x8
#define HWIO_SAW4_AVS_STS_CPU_UP_SHFT                              0x3
#define HWIO_SAW4_AVS_STS_CPU_DN_BMSK                              0x4
#define HWIO_SAW4_AVS_STS_CPU_DN_SHFT                              0x2
#define HWIO_SAW4_AVS_STS_AVS_FSM_STATE_BMSK                       0x3
#define HWIO_SAW4_AVS_STS_AVS_FSM_STATE_SHFT                       0x0

#define HWIO_SAW4_PMIC_STS_ADDR(core)                       ((core) + SAW4_STS_REG_BASE_OFFS + 0x00000018)
#define HWIO_SAW4_PMIC_STS_OFFS                             (SAW4_STS_REG_BASE_OFFS + 0x00000018)
#define HWIO_SAW4_PMIC_STS_RMSK                               0xffffff
#define HWIO_SAW4_PMIC_STS_IN(core)    \
        in_dword_masked(HWIO_SAW4_PMIC_STS_ADDR(core), HWIO_SAW4_PMIC_STS_RMSK)
#define HWIO_SAW4_PMIC_STS_INM(core,m)      \
        in_dword_masked(HWIO_SAW4_PMIC_STS_ADDR(core), m)
#define HWIO_SAW4_PMIC_STS_PMIC_DONE_BMSK                     0x800000
#define HWIO_SAW4_PMIC_STS_PMIC_DONE_SHFT                         0x17
#define HWIO_SAW4_PMIC_STS_PMIC_REQ_BMSK                      0x400000
#define HWIO_SAW4_PMIC_STS_PMIC_REQ_SHFT                          0x16
#define HWIO_SAW4_PMIC_STS_CURR_PMIC_ADDR_IDX_BMSK            0x380000
#define HWIO_SAW4_PMIC_STS_CURR_PMIC_ADDR_IDX_SHFT                0x13
#define HWIO_SAW4_PMIC_STS_CURR_PMIC_SIZE_BMSK                 0x40000
#define HWIO_SAW4_PMIC_STS_CURR_PMIC_SIZE_SHFT                    0x12
#define HWIO_SAW4_PMIC_STS_PMIC_STATE_BMSK                     0x30000
#define HWIO_SAW4_PMIC_STS_PMIC_STATE_SHFT                        0x10
#define HWIO_SAW4_PMIC_STS_CURR_PMIC_DATA_BMSK                  0xffff
#define HWIO_SAW4_PMIC_STS_CURR_PMIC_DATA_SHFT                     0x0

#define HWIO_SAW4_RST_ADDR(core)                            ((core) + SAW4_STS_REG_BASE_OFFS + 0x0000001c)
#define HWIO_SAW4_RST_OFFS                                  (SAW4_STS_REG_BASE_OFFS + 0x0000001c)
#define HWIO_SAW4_RST_RMSK                                         0x1
#define HWIO_SAW4_RST_IN(core)    \
        in_dword_masked(HWIO_SAW4_RST_ADDR(core), HWIO_SAW4_RST_RMSK)
#define HWIO_SAW4_RST_INM(core,m)      \
        in_dword_masked(HWIO_SAW4_RST_ADDR(core), m)
#define HWIO_SAW4_RST_OUT(core,v)      \
        out_dword(HWIO_SAW4_RST_ADDR(core),v)
#define HWIO_SAW4_RST_OUTM(core,m,v) \
        out_dword_masked_ns(HWIO_SAW4_RST_ADDR(core),m,v,HWIO_SAW4_RST_IN(core))
#define HWIO_SAW4_RST_RST_BMSK                                     0x1
#define HWIO_SAW4_RST_RST_SHFT                                     0x0

#define HWIO_SAW4_SPM_STS3_ADDR(core)                       ((core) + SAW4_STS_REG_BASE_OFFS + 0x00000020)
#define HWIO_SAW4_SPM_STS3_OFFS                             (SAW4_STS_REG_BASE_OFFS + 0x00000020)
#define HWIO_SAW4_SPM_STS3_RMSK                             0x3ff0001f
#define HWIO_SAW4_SPM_STS3_IN(core)    \
        in_dword_masked(HWIO_SAW4_SPM_STS3_ADDR(core), HWIO_SAW4_SPM_STS3_RMSK)
#define HWIO_SAW4_SPM_STS3_INM(core,m)      \
        in_dword_masked(HWIO_SAW4_SPM_STS3_ADDR(core), m)
#define HWIO_SAW4_SPM_STS3_SPM_CURR_DLY_BMSK                0x3ff00000
#define HWIO_SAW4_SPM_STS3_SPM_CURR_DLY_SHFT                      0x14
#define HWIO_SAW4_SPM_STS3_DBG_STAY_AWAKE_BMSK                    0x10
#define HWIO_SAW4_SPM_STS3_DBG_STAY_AWAKE_SHFT                     0x4
#define HWIO_SAW4_SPM_STS3_SLEEP_STATE_BMSK                        0x8
#define HWIO_SAW4_SPM_STS3_SLEEP_STATE_SHFT                        0x3
#define HWIO_SAW4_SPM_STS3_WAKEUP_BMSK                             0x4
#define HWIO_SAW4_SPM_STS3_WAKEUP_SHFT                             0x2
#define HWIO_SAW4_SPM_STS3_WAIT_ACK_BMSK                           0x2
#define HWIO_SAW4_SPM_STS3_WAIT_ACK_SHFT                           0x1
#define HWIO_SAW4_SPM_STS3_WAIT_REQ_BMSK                           0x1
#define HWIO_SAW4_SPM_STS3_WAIT_REQ_SHFT                           0x0

#define HWIO_SAW4_CVS_STS_ADDR(core)                        ((core) + SAW4_STS_REG_BASE_OFFS + 0x00000040)
#define HWIO_SAW4_CVS_STS_OFFS                              (SAW4_STS_REG_BASE_OFFS + 0x00000040)
#define HWIO_SAW4_CVS_STS_RMSK                              0xffff03ff
#define HWIO_SAW4_CVS_STS_IN(core)    \
        in_dword_masked(HWIO_SAW4_CVS_STS_ADDR(core), HWIO_SAW4_CVS_STS_RMSK)
#define HWIO_SAW4_CVS_STS_INM(core,m)      \
        in_dword_masked(HWIO_SAW4_CVS_STS_ADDR(core), m)
#define HWIO_SAW4_CVS_STS_CVS_EVENT_BMSK                    0xffff0000
#define HWIO_SAW4_CVS_STS_CVS_EVENT_SHFT                          0x10
#define HWIO_SAW4_CVS_STS_CVS_BUSY_BMSK                          0x200
#define HWIO_SAW4_CVS_STS_CVS_BUSY_SHFT                            0x9
#define HWIO_SAW4_CVS_STS_CVS_CMD_ADDR_BMSK                      0x1ff
#define HWIO_SAW4_CVS_STS_CVS_CMD_ADDR_SHFT                        0x0

#define HWIO_SAW4_CVS_STS2_ADDR(core)                       ((core) + SAW4_STS_REG_BASE_OFFS + 0x00000044)
#define HWIO_SAW4_CVS_STS2_OFFS                             (SAW4_STS_REG_BASE_OFFS + 0x00000044)
#define HWIO_SAW4_CVS_STS2_RMSK                             0xffffffff
#define HWIO_SAW4_CVS_STS2_IN(core)    \
        in_dword_masked(HWIO_SAW4_CVS_STS2_ADDR(core), HWIO_SAW4_CVS_STS2_RMSK)
#define HWIO_SAW4_CVS_STS2_INM(core,m)      \
        in_dword_masked(HWIO_SAW4_CVS_STS2_ADDR(core), m)
#define HWIO_SAW4_CVS_STS2_CVS_PWR_CTL_BMSK                 0xffffffff
#define HWIO_SAW4_CVS_STS2_CVS_PWR_CTL_SHFT                        0x0

#define HWIO_SAW4_VERSION_ADDR(core)                        ((core) + SAW4_STS_REG_BASE_OFFS + 0x000003d0)
#define HWIO_SAW4_VERSION_OFFS                              (SAW4_STS_REG_BASE_OFFS + 0x000003d0)
#define HWIO_SAW4_VERSION_RMSK                              0xffffffff
#define HWIO_SAW4_VERSION_IN(core)    \
        in_dword_masked(HWIO_SAW4_VERSION_ADDR(core), HWIO_SAW4_VERSION_RMSK)
#define HWIO_SAW4_VERSION_INM(core,m)      \
        in_dword_masked(HWIO_SAW4_VERSION_ADDR(core), m)
#define HWIO_SAW4_VERSION_MAJOR_BMSK                        0xf0000000
#define HWIO_SAW4_VERSION_MAJOR_SHFT                              0x1c
#define HWIO_SAW4_VERSION_MINOR_BMSK                         0xfff0000
#define HWIO_SAW4_VERSION_MINOR_SHFT                              0x10
#define HWIO_SAW4_VERSION_STEP_BMSK                             0xffff
#define HWIO_SAW4_VERSION_STEP_SHFT                                0x0


#endif /* __HALAVSHWIOSAW4_H__ */
