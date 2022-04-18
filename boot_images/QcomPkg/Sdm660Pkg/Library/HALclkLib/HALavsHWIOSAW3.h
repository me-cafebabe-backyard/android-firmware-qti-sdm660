#ifndef __HALAVSHWIOSAW2_H__
#define __HALAVSHWIOSAW2_H__


/*
===========================================================================

FILE:         HALavsHWIOSAW2.h

DESCRIPTION:
  This is the hardware abstraction layer interface for the Qualcomm
  Adaptive Voltage Scaling hardware block SAW2.

===========================================================================

                             Edit History


when       who     what, where, why
--------   ---     --------------------------------------------------------
03/15/11   dcf     Created.

===========================================================================
       Copyright (c) 2011 QUALCOMM Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
===========================================================================
*/


#ifdef __cplusplus
extern "C" {
#endif


/*------------------------------------------------------------------------------
 * MODULE: SAW
 *------------------------------------------------------------------------------*/

//#define APCS_CBF_SAW3_REG_BASE                                             (HMSS_BASE      + 0x00210000)
//#define APCS_CBF_SAW3_REG_BASE_OFFS                                        0x00210000

#define HWIO_SAW3_SECURE_ADDR(core)                                     ((core)      + 0x00000000)
#define HWIO_SAW3_SECURE_RMSK                                            0x7
#define HWIO_SAW3_SECURE_IN(core)        \
        in_dword_masked(HWIO_SAW3_SECURE_ADDR(core), HWIO_SAW3_SECURE_RMSK)
#define HWIO_SAW3_SECURE_INM(core,m)      \
        in_dword_masked(HWIO_SAW3_SECURE_ADDR(core), m)
#define HWIO_SAW3_SECURE_OUT(core,v)      \
        out_dword(HWIO_SAW3_SECURE_ADDR(core),v)
#define HWIO_SAW3_SECURE_OUTM(core,m,v) \
        HWIO_INTLOCK(); \
        out_dword_masked_ns(HWIO_SAW3_SECURE_ADDR(core),m,v,HWIO_SAW3_SECURE_IN(core)); \
        HWIO_INTFREE()
#define HWIO_SAW3_SECURE_SAW_CTL_BMSK                                    0x4
#define HWIO_SAW3_SECURE_SAW_CTL_SHFT                                    0x2
#define HWIO_SAW3_SECURE_PWR_CTL_BMSK                                    0x2
#define HWIO_SAW3_SECURE_PWR_CTL_SHFT                                    0x1
#define HWIO_SAW3_SECURE_VLT_CTL_BMSK                                    0x1
#define HWIO_SAW3_SECURE_VLT_CTL_SHFT                                    0x0

#define HWIO_SAW3_ID_ADDR(core)                                         ((core)      + 0x00000004)
#define HWIO_SAW3_ID_RMSK                                         0xff3f1f7f
#define HWIO_SAW3_ID_IN(core)          \
        in_dword_masked(HWIO_SAW3_ID_ADDR(core), HWIO_SAW3_ID_RMSK)
#define HWIO_SAW3_ID_INM(core,m)      \
        in_dword_masked(HWIO_SAW3_ID_ADDR(core), m)
#define HWIO_SAW3_ID_NUM_SPM_ENTRY_BMSK                           0xff000000
#define HWIO_SAW3_ID_NUM_SPM_ENTRY_SHFT                                 0x18
#define HWIO_SAW3_ID_NUM_PWR_CTL_BMSK                               0x3f0000
#define HWIO_SAW3_ID_NUM_PWR_CTL_SHFT                                   0x10
#define HWIO_SAW3_ID_PMIC_DATA_WIDTH_BMSK                             0x1f00
#define HWIO_SAW3_ID_PMIC_DATA_WIDTH_SHFT                                0x8
#define HWIO_SAW3_ID_NUM_PMIC_DATA_BMSK                                 0x70
#define HWIO_SAW3_ID_NUM_PMIC_DATA_SHFT                                  0x4
#define HWIO_SAW3_ID_CFG_NS_ACCESS_BMSK                                  0x8
#define HWIO_SAW3_ID_CFG_NS_ACCESS_SHFT                                  0x3
#define HWIO_SAW3_ID_PMIC_ARB_INTF_BMSK                                  0x4
#define HWIO_SAW3_ID_PMIC_ARB_INTF_SHFT                                  0x2
#define HWIO_SAW3_ID_AVS_PRESENT_BMSK                                    0x2
#define HWIO_SAW3_ID_AVS_PRESENT_SHFT                                    0x1
#define HWIO_SAW3_ID_SPM_PRESENT_BMSK                                    0x1
#define HWIO_SAW3_ID_SPM_PRESENT_SHFT                                    0x0

#define HWIO_SAW3_CFG_ADDR(core)                                        ((core)      + 0x00000008)
#define HWIO_SAW3_CFG_RMSK                                             0x31f
#define HWIO_SAW3_CFG_IN(core)          \
        in_dword_masked(HWIO_SAW3_CFG_ADDR(core), HWIO_SAW3_CFG_RMSK)
#define HWIO_SAW3_CFG_INM(core,m)      \
        in_dword_masked(HWIO_SAW3_CFG_ADDR(core), m)
#define HWIO_SAW3_CFG_OUT(core,v)      \
        out_dword(HWIO_SAW3_CFG_ADDR(core),v)
#define HWIO_SAW3_CFG_OUTM(core,m,v) \
        HWIO_INTLOCK(); \
        out_dword_masked_ns(HWIO_SAW3_CFG_ADDR(core),m,v,HWIO_SAW3_CFG_IN(core)); \
        HWIO_INTFREE()
#define HWIO_SAW3_CFG_TEST_BUS_EN_BMSK                                 0x200
#define HWIO_SAW3_CFG_TEST_BUS_EN_SHFT                                   0x9
#define HWIO_SAW3_CFG_FRC_REF_CLK_ON_BMSK                              0x100
#define HWIO_SAW3_CFG_FRC_REF_CLK_ON_SHFT                                0x8
#define HWIO_SAW3_CFG_CLK_DIV_BMSK                                      0x1f
#define HWIO_SAW3_CFG_CLK_DIV_SHFT                                       0x0

#define HWIO_SAW3_SPM_STS_ADDR(core)                                    ((core)      + 0x0000000c)
#define HWIO_SAW3_SPM_STS_RMSK                                    0xffffffff
#define HWIO_SAW3_SPM_STS_IN(core)          \
        in_dword_masked(HWIO_SAW3_SPM_STS_ADDR(core), HWIO_SAW3_SPM_STS_RMSK)
#define HWIO_SAW3_SPM_STS_INM(core,m)      \
        in_dword_masked(HWIO_SAW3_SPM_STS_ADDR(core), m)
#define HWIO_SAW3_SPM_STS_CURR_PWR_CTL_BMSK                       0xffff0000
#define HWIO_SAW3_SPM_STS_CURR_PWR_CTL_SHFT                             0x10
#define HWIO_SAW3_SPM_STS_SHTDWN_REQ_BMSK                             0x8000
#define HWIO_SAW3_SPM_STS_SHTDWN_REQ_SHFT                                0xf
#define HWIO_SAW3_SPM_STS_SHTDWN_ACK_BMSK                             0x4000
#define HWIO_SAW3_SPM_STS_SHTDWN_ACK_SHFT                                0xe
#define HWIO_SAW3_SPM_STS_BRNGUP_REQ_BMSK                             0x2000
#define HWIO_SAW3_SPM_STS_BRNGUP_REQ_SHFT                                0xd
#define HWIO_SAW3_SPM_STS_BRNGUP_ACK_BMSK                             0x1000
#define HWIO_SAW3_SPM_STS_BRNGUP_ACK_SHFT                                0xc
#define HWIO_SAW3_SPM_STS_RPM_STATE_BMSK                               0xc00
#define HWIO_SAW3_SPM_STS_RPM_STATE_SHFT                                 0xa
#define HWIO_SAW3_SPM_STS_SPM_BUSY_BMSK                                0x200
#define HWIO_SAW3_SPM_STS_SPM_BUSY_SHFT                                  0x9
#define HWIO_SAW3_SPM_STS_SPM_CMD_ADDR_BMSK                            0x1ff
#define HWIO_SAW3_SPM_STS_SPM_CMD_ADDR_SHFT                              0x0

#define HWIO_SAW3_AVS_STS_ADDR(core)                                    ((core)      + 0x00000010)
#define HWIO_SAW3_AVS_STS_RMSK                                    0xffff007f
#define HWIO_SAW3_AVS_STS_IN(core)          \
        in_dword_masked(HWIO_SAW3_AVS_STS_ADDR(core), HWIO_SAW3_AVS_STS_RMSK)
#define HWIO_SAW3_AVS_STS_INM(core,m)      \
        in_dword_masked(HWIO_SAW3_AVS_STS_ADDR(core), m)
#define HWIO_SAW3_AVS_STS_SPM_EVENT_BMSK                          0xffff0000
#define HWIO_SAW3_AVS_STS_SPM_EVENT_SHFT                                0x10
#define HWIO_SAW3_AVS_STS_AVS_FSM_STATE_BMSK                            0x40
#define HWIO_SAW3_AVS_STS_AVS_FSM_STATE_SHFT                             0x6
#define HWIO_SAW3_AVS_STS_MAX_INT_BMSK                                  0x20
#define HWIO_SAW3_AVS_STS_MAX_INT_SHFT                                   0x5
#define HWIO_SAW3_AVS_STS_MIN_INT_BMSK                                  0x10
#define HWIO_SAW3_AVS_STS_MIN_INT_SHFT                                   0x4
#define HWIO_SAW3_AVS_STS_CPU_UP_BMSK                                    0x8
#define HWIO_SAW3_AVS_STS_CPU_UP_SHFT                                    0x3
#define HWIO_SAW3_AVS_STS_CPU_DN_BMSK                                    0x4
#define HWIO_SAW3_AVS_STS_CPU_DN_SHFT                                    0x2
#define HWIO_SAW3_AVS_STS_SW_WR_PEND_BMSK                                0x2
#define HWIO_SAW3_AVS_STS_SW_WR_PEND_SHFT                                0x1
#define HWIO_SAW3_AVS_STS_AVS_STATE_BMSK                                 0x1
#define HWIO_SAW3_AVS_STS_AVS_STATE_SHFT                                 0x0

#define HWIO_SAW3_PMIC_STS_ADDR(core)                                   ((core)      + 0x00000014)
#define HWIO_SAW3_PMIC_STS_RMSK                                   0x3ff700ff
#define HWIO_SAW3_PMIC_STS_IN(core)          \
        in_dword_masked(HWIO_SAW3_PMIC_STS_ADDR(core), HWIO_SAW3_PMIC_STS_RMSK)
#define HWIO_SAW3_PMIC_STS_INM(core,m)      \
        in_dword_masked(HWIO_SAW3_PMIC_STS_ADDR(core), m)
#define HWIO_SAW3_PMIC_STS_CURR_DLY_BMSK                          0x3ff00000
#define HWIO_SAW3_PMIC_STS_CURR_DLY_SHFT                                0x14
#define HWIO_SAW3_PMIC_STS_CURR_PMIC_SIZE_BMSK                       0x40000
#define HWIO_SAW3_PMIC_STS_CURR_PMIC_SIZE_SHFT                          0x12
#define HWIO_SAW3_PMIC_STS_PMIC_STATE_BMSK                           0x30000
#define HWIO_SAW3_PMIC_STS_PMIC_STATE_SHFT                              0x10
#define HWIO_SAW3_PMIC_STS_CURR_PMIC_DATA_BMSK                          0xff
#define HWIO_SAW3_PMIC_STS_CURR_PMIC_DATA_SHFT                           0x0

#define HWIO_SAW3_RST_ADDR(core)                                        ((core)     + 0x00000018)
#define HWIO_SAW3_RST_RMSK                                               0x1
#define HWIO_SAW3_RST_IN(core)          \
        in_dword_masked(HWIO_SAW3_RST_ADDR(core), HWIO_SAW3_RST_RMSK)
#define HWIO_SAW3_RST_INM(core,m)      \
        in_dword_masked(HWIO_SAW3_RST_ADDR(core), m)
#define HWIO_SAW3_RST_OUT(core,v)      \
        out_dword(HWIO_SAW3_RST_ADDR(core),v)
#define HWIO_SAW3_RST_OUTM(core,m,v) \
        out_dword_masked_ns(HWIO_SAW3_RST_ADDR(core),m,v,HWIO_SAW3_RST_IN(core))
#define HWIO_SAW3_RST_RST_BMSK                                           0x1
#define HWIO_SAW3_RST_RST_SHFT                                           0x0

#define HWIO_SAW3_VCTL_ADDR(core)                                       ((core)     + 0x0000001c)
#define HWIO_SAW3_VCTL_RMSK                                         0x1700ff
#define HWIO_SAW3_VCTL_IN(core)          \
        in_dword_masked(HWIO_SAW3_VCTL_ADDR(core), HWIO_SAW3_VCTL_RMSK)
#define HWIO_SAW3_VCTL_INM(core,m)      \
        in_dword_masked(HWIO_SAW3_VCTL_ADDR(core), m)
#define HWIO_SAW3_VCTL_OUT(core,v)      \
        out_dword(HWIO_SAW3_VCTL_ADDR(core),v)
#define HWIO_SAW3_VCTL_OUTM(core,m,v) \
        HWIO_INTLOCK(); \
        out_dword_masked_ns(HWIO_SAW3_VCTL_ADDR(core),m,v,HWIO_SAW3_VCTL_IN(core)); \
        HWIO_INTFREE()
#define HWIO_SAW3_VCTL_SIZE_BMSK                                    0x100000
#define HWIO_SAW3_VCTL_SIZE_SHFT                                        0x14
#define HWIO_SAW3_VCTL_ADR_IDX_BMSK                                  0x70000
#define HWIO_SAW3_VCTL_ADR_IDX_SHFT                                     0x10
#define HWIO_SAW3_VCTL_PMIC_DATA_BMSK                                   0xff
#define HWIO_SAW3_VCTL_PMIC_DATA_SHFT                                    0x0

#define HWIO_SAW3_AVS_CTL_ADDR(core)                                    ((core)     + 0x00000020)
#define HWIO_SAW3_AVS_CTL_RMSK                                        0x130f
#define HWIO_SAW3_AVS_CTL_IN(core)          \
        in_dword_masked(HWIO_SAW3_AVS_CTL_ADDR(core), HWIO_SAW3_AVS_CTL_RMSK)
#define HWIO_SAW3_AVS_CTL_INM(core,m)      \
        in_dword_masked(HWIO_SAW3_AVS_CTL_ADDR(core), m)
#define HWIO_SAW3_AVS_CTL_OUT(core,v)      \
        out_dword(HWIO_SAW3_AVS_CTL_ADDR(core),v)
#define HWIO_SAW3_AVS_CTL_OUTM(core,m,v) \
        HWIO_INTLOCK(); \
        out_dword_masked_ns(HWIO_SAW3_AVS_CTL_ADDR(core),m,v,HWIO_SAW3_AVS_CTL_IN(core)); \
        HWIO_INTFREE()
#define HWIO_SAW3_AVS_CTL_VLVL_WIDTH_BMSK                             0x1000
#define HWIO_SAW3_AVS_CTL_VLVL_WIDTH_SHFT                                0xc
#define HWIO_SAW3_AVS_CTL_VLVL_STEP_BMSK                               0x300
#define HWIO_SAW3_AVS_CTL_VLVL_STEP_SHFT                                 0x8
#define HWIO_SAW3_AVS_CTL_SW_DONE_INT_EN_BMSK                            0x8
#define HWIO_SAW3_AVS_CTL_SW_DONE_INT_EN_SHFT                            0x3
#define HWIO_SAW3_AVS_CTL_MAX_INT_EN_BMSK                                0x4
#define HWIO_SAW3_AVS_CTL_MAX_INT_EN_SHFT                                0x2
#define HWIO_SAW3_AVS_CTL_MIN_INT_EN_BMSK                                0x2
#define HWIO_SAW3_AVS_CTL_MIN_INT_EN_SHFT                                0x1
#define HWIO_SAW3_AVS_CTL_EN_BMSK                                        0x1
#define HWIO_SAW3_AVS_CTL_EN_SHFT                                        0x0

#define HWIO_SAW3_AVS_LIMIT_ADDR(core)                                  ((core)     + 0x00000024)
#define HWIO_SAW3_AVS_LIMIT_RMSK                                    0xff00ff
#define HWIO_SAW3_AVS_LIMIT_IN(core)          \
        in_dword_masked(HWIO_SAW3_AVS_LIMIT_ADDR(core), HWIO_SAW3_AVS_LIMIT_RMSK)
#define HWIO_SAW3_AVS_LIMIT_INM(core,m)      \
        in_dword_masked(HWIO_SAW3_AVS_LIMIT_ADDR(core), m)
#define HWIO_SAW3_AVS_LIMIT_OUT(core,v)      \
        out_dword(HWIO_SAW3_AVS_LIMIT_ADDR(core),v)
#define HWIO_SAW3_AVS_LIMIT_OUTM(core,m,v) \
        out_dword_masked_ns(HWIO_SAW3_AVS_LIMIT_ADDR(core),m,v,HWIO_SAW3_AVS_LIMIT_IN(core))
#define HWIO_SAW3_AVS_LIMIT_MAX_VLVL_BMSK                           0xff0000
#define HWIO_SAW3_AVS_LIMIT_MAX_VLVL_SHFT                               0x10
#define HWIO_SAW3_AVS_LIMIT_MIN_VLVL_BMSK                               0xff
#define HWIO_SAW3_AVS_LIMIT_MIN_VLVL_SHFT                                0x0

#define HWIO_SAW3_AVS_DLY_ADDR(core)                                    ((core)     + 0x00000028)
#define HWIO_SAW3_AVS_DLY_RMSK                                         0x3ff
#define HWIO_SAW3_AVS_DLY_IN(core)          \
        in_dword_masked(HWIO_SAW3_AVS_DLY_ADDR(core), HWIO_SAW3_AVS_DLY_RMSK)
#define HWIO_SAW3_AVS_DLY_INM(core,m)      \
        in_dword_masked(HWIO_SAW3_AVS_DLY_ADDR(core), m)
#define HWIO_SAW3_AVS_DLY_OUT(core,v)      \
        out_dword(HWIO_SAW3_AVS_DLY_ADDR(core),v)
#define HWIO_SAW3_AVS_DLY_OUTM(core,m,v) \
        out_dword_masked_ns(HWIO_SAW3_AVS_DLY_ADDR(core),m,v,HWIO_SAW3_AVS_DLY_IN(core))
#define HWIO_SAW3_AVS_DLY_AVS_DELAY_BMSK                               0x3ff
#define HWIO_SAW3_AVS_DLY_AVS_DELAY_SHFT                                 0x0

#define HWIO_SAW3_AVS_HYSTERESIS_ADDR(core)                             ((core)     + 0x0000002c)
#define HWIO_SAW3_AVS_HYSTERESIS_RMSK                               0xff00ff
#define HWIO_SAW3_AVS_HYSTERESIS_IN(core)          \
        in_dword_masked(HWIO_SAW3_AVS_HYSTERESIS_ADDR(core), HWIO_SAW3_AVS_HYSTERESIS_RMSK)
#define HWIO_SAW3_AVS_HYSTERESIS_INM(core,m)      \
        in_dword_masked(HWIO_SAW3_AVS_HYSTERESIS_ADDR(core), m)
#define HWIO_SAW3_AVS_HYSTERESIS_OUT(core,v)      \
        out_dword(HWIO_SAW3_AVS_HYSTERESIS_ADDR(core),v)
#define HWIO_SAW3_AVS_HYSTERESIS_OUTM(core,m,v) \
        HWIO_INTLOCK(); \
        out_dword_masked_ns(HWIO_SAW3_AVS_HYSTERESIS_ADDR(core),m,v,HWIO_SAW3_AVS_HYSTERESIS_IN(core)); \
        HWIO_INTFREE()
#define HWIO_SAW3_AVS_HYSTERESIS_DN_COUNT_BMSK                      0xff0000
#define HWIO_SAW3_AVS_HYSTERESIS_DN_COUNT_SHFT                          0x10
#define HWIO_SAW3_AVS_HYSTERESIS_UP_COUNT_BMSK                          0xff
#define HWIO_SAW3_AVS_HYSTERESIS_UP_COUNT_SHFT                           0x0

#ifdef __cplusplus
}
#endif

#endif /* __HALAVSHWIOSAW2_H__ */

