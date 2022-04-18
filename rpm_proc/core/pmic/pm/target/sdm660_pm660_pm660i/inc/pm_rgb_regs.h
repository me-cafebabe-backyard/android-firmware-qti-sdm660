#ifndef __PM_RGB_REGS_H__
#define __PM_RGB_REGS_H__
/*
===========================================================================
*/
/**
  @file pm_rgb_regs.h
  @brief Auto-generated PMIO interface include file.

  This file contains PMIO register definitions for the following modules:
    TRI_LED

  'Include' filters applied: <none>
  'Exclude' filters applied: RESERVED DUMMY 
*/
/*
  ===========================================================================

  Copyright (c) 2013-2016 Qualcomm Technologies Incorporated.
  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  
===========================================================================

   $Header: //components/rel/rpm.bf/1.8/core/pmic/pm/target/sdm660_pm660_pm660i/inc/pm_rgb_regs.h#1 $
  $DateTime: 2016/11/03 00:13:13 $   
  $Author: pwbldsvc $


  ===========================================================================
*/

/*----------------------------------------------------------------------------
 * PERIPHERAL: TRI_LED
 *--------------------------------------------------------------------------*/

#define PMIO_TRI_LED_REVISION1_ADDR(x)                                         ((x) + 0x00000000)
#define PMIO_TRI_LED_REVISION1_OFFS                                            0x00000000
#define PMIO_TRI_LED_REVISION1_RMSK                                                  0xff
#define PMIO_TRI_LED_REVISION1_IN(ctxt, pmic, base, val)\
        in_pmio_field(ctxt, pmic, PMIO_TRI_LED_REVISION1_ADDR(base), PMIO_TRI_LED_REVISION1_RMSK, 0, val)
#define PMIO_TRI_LED_REVISION1_INF(ctxt, pmic, base, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_TRI_LED_REVISION1_ADDR(base), mask, shift, val)
#define PMIO_TRI_LED_REVISION1_DIG_MINOR_BMSK                                        0xff
#define PMIO_TRI_LED_REVISION1_DIG_MINOR_SHFT                                         0x0

#define PMIO_TRI_LED_REVISION2_ADDR(x)                                         ((x) + 0x00000001)
#define PMIO_TRI_LED_REVISION2_OFFS                                            0x00000001
#define PMIO_TRI_LED_REVISION2_RMSK                                                  0xff
#define PMIO_TRI_LED_REVISION2_IN(ctxt, pmic, base, val)\
        in_pmio_field(ctxt, pmic, PMIO_TRI_LED_REVISION2_ADDR(base), PMIO_TRI_LED_REVISION2_RMSK, 0, val)
#define PMIO_TRI_LED_REVISION2_INF(ctxt, pmic, base, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_TRI_LED_REVISION2_ADDR(base), mask, shift, val)
#define PMIO_TRI_LED_REVISION2_DIG_MAJOR_BMSK                                        0xff
#define PMIO_TRI_LED_REVISION2_DIG_MAJOR_SHFT                                         0x0

#define PMIO_TRI_LED_REVISION3_ADDR(x)                                         ((x) + 0x00000002)
#define PMIO_TRI_LED_REVISION3_OFFS                                            0x00000002
#define PMIO_TRI_LED_REVISION3_RMSK                                                  0xff
#define PMIO_TRI_LED_REVISION3_IN(ctxt, pmic, base, val)\
        in_pmio_field(ctxt, pmic, PMIO_TRI_LED_REVISION3_ADDR(base), PMIO_TRI_LED_REVISION3_RMSK, 0, val)
#define PMIO_TRI_LED_REVISION3_INF(ctxt, pmic, base, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_TRI_LED_REVISION3_ADDR(base), mask, shift, val)
#define PMIO_TRI_LED_REVISION3_ANA_MINOR_BMSK                                        0xff
#define PMIO_TRI_LED_REVISION3_ANA_MINOR_SHFT                                         0x0

#define PMIO_TRI_LED_REVISION4_ADDR(x)                                         ((x) + 0x00000003)
#define PMIO_TRI_LED_REVISION4_OFFS                                            0x00000003
#define PMIO_TRI_LED_REVISION4_RMSK                                                  0xff
#define PMIO_TRI_LED_REVISION4_IN(ctxt, pmic, base, val)\
        in_pmio_field(ctxt, pmic, PMIO_TRI_LED_REVISION4_ADDR(base), PMIO_TRI_LED_REVISION4_RMSK, 0, val)
#define PMIO_TRI_LED_REVISION4_INF(ctxt, pmic, base, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_TRI_LED_REVISION4_ADDR(base), mask, shift, val)
#define PMIO_TRI_LED_REVISION4_ANA_MAJOR_BMSK                                        0xff
#define PMIO_TRI_LED_REVISION4_ANA_MAJOR_SHFT                                         0x0

#define PMIO_TRI_LED_PERPH_TYPE_ADDR(x)                                        ((x) + 0x00000004)
#define PMIO_TRI_LED_PERPH_TYPE_OFFS                                           0x00000004
#define PMIO_TRI_LED_PERPH_TYPE_RMSK                                                 0xff
#define PMIO_TRI_LED_PERPH_TYPE_IN(ctxt, pmic, base, val)\
        in_pmio_field(ctxt, pmic, PMIO_TRI_LED_PERPH_TYPE_ADDR(base), PMIO_TRI_LED_PERPH_TYPE_RMSK, 0, val)
#define PMIO_TRI_LED_PERPH_TYPE_INF(ctxt, pmic, base, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_TRI_LED_PERPH_TYPE_ADDR(base), mask, shift, val)
#define PMIO_TRI_LED_PERPH_TYPE_TYPE_BMSK                                            0xff
#define PMIO_TRI_LED_PERPH_TYPE_TYPE_SHFT                                             0x0

#define PMIO_TRI_LED_PERPH_SUBTYPE_ADDR(x)                                     ((x) + 0x00000005)
#define PMIO_TRI_LED_PERPH_SUBTYPE_OFFS                                        0x00000005
#define PMIO_TRI_LED_PERPH_SUBTYPE_RMSK                                              0xff
#define PMIO_TRI_LED_PERPH_SUBTYPE_IN(ctxt, pmic, base, val)\
        in_pmio_field(ctxt, pmic, PMIO_TRI_LED_PERPH_SUBTYPE_ADDR(base), PMIO_TRI_LED_PERPH_SUBTYPE_RMSK, 0, val)
#define PMIO_TRI_LED_PERPH_SUBTYPE_INF(ctxt, pmic, base, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_TRI_LED_PERPH_SUBTYPE_ADDR(base), mask, shift, val)
#define PMIO_TRI_LED_PERPH_SUBTYPE_SUBTYPE_BMSK                                      0xff
#define PMIO_TRI_LED_PERPH_SUBTYPE_SUBTYPE_SHFT                                       0x0

#define PMIO_TRI_LED_LED_SRC_SEL_ADDR(x)                                       ((x) + 0x00000045)
#define PMIO_TRI_LED_LED_SRC_SEL_OFFS                                          0x00000045
#define PMIO_TRI_LED_LED_SRC_SEL_RMSK                                                 0x3
#define PMIO_TRI_LED_LED_SRC_SEL_IN(ctxt, pmic, base, val)\
        in_pmio_field(ctxt, pmic, PMIO_TRI_LED_LED_SRC_SEL_ADDR(base), PMIO_TRI_LED_LED_SRC_SEL_RMSK, 0, val)
#define PMIO_TRI_LED_LED_SRC_SEL_INF(ctxt, pmic, base, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_TRI_LED_LED_SRC_SEL_ADDR(base), mask, shift, val)
#define PMIO_TRI_LED_LED_SRC_SEL_OUT(ctxt, pmic, base, val)\
        out_pmio(ctxt, pmic, PMIO_TRI_LED_LED_SRC_SEL_ADDR(base), val)
#define PMIO_TRI_LED_LED_SRC_SEL_OUTF(ctxt, pmic, base, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_TRI_LED_LED_SRC_SEL_ADDR(base), mask, shift, val)
#define PMIO_TRI_LED_LED_SRC_SEL_LED_SRC_SEL_BMSK                                     0x3
#define PMIO_TRI_LED_LED_SRC_SEL_LED_SRC_SEL_SHFT                                     0x0

#define PMIO_TRI_LED_EN_CTL_ADDR(x)                                            ((x) + 0x00000046)
#define PMIO_TRI_LED_EN_CTL_OFFS                                               0x00000046
#define PMIO_TRI_LED_EN_CTL_RMSK                                                     0xe0
#define PMIO_TRI_LED_EN_CTL_IN(ctxt, pmic, base, val)\
        in_pmio_field(ctxt, pmic, PMIO_TRI_LED_EN_CTL_ADDR(base), PMIO_TRI_LED_EN_CTL_RMSK, 0, val)
#define PMIO_TRI_LED_EN_CTL_INF(ctxt, pmic, base, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_TRI_LED_EN_CTL_ADDR(base), mask, shift, val)
#define PMIO_TRI_LED_EN_CTL_OUT(ctxt, pmic, base, val)\
        out_pmio(ctxt, pmic, PMIO_TRI_LED_EN_CTL_ADDR(base), val)
#define PMIO_TRI_LED_EN_CTL_OUTF(ctxt, pmic, base, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_TRI_LED_EN_CTL_ADDR(base), mask, shift, val)
#define PMIO_TRI_LED_EN_CTL_RED_EN_BMSK                                              0x80
#define PMIO_TRI_LED_EN_CTL_RED_EN_SHFT                                               0x7
#define PMIO_TRI_LED_EN_CTL_GREEN_EN_BMSK                                            0x40
#define PMIO_TRI_LED_EN_CTL_GREEN_EN_SHFT                                             0x6
#define PMIO_TRI_LED_EN_CTL_BLUE_EN_BMSK                                             0x20
#define PMIO_TRI_LED_EN_CTL_BLUE_EN_SHFT                                              0x5

#define PMIO_TRI_LED_EN_CTL_ATC_ADDR(x)                                        ((x) + 0x00000047)
#define PMIO_TRI_LED_EN_CTL_ATC_OFFS                                           0x00000047
#define PMIO_TRI_LED_EN_CTL_ATC_RMSK                                                 0xe0
#define PMIO_TRI_LED_EN_CTL_ATC_IN(ctxt, pmic, base, val)\
        in_pmio_field(ctxt, pmic, PMIO_TRI_LED_EN_CTL_ATC_ADDR(base), PMIO_TRI_LED_EN_CTL_ATC_RMSK, 0, val)
#define PMIO_TRI_LED_EN_CTL_ATC_INF(ctxt, pmic, base, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_TRI_LED_EN_CTL_ATC_ADDR(base), mask, shift, val)
#define PMIO_TRI_LED_EN_CTL_ATC_OUT(ctxt, pmic, base, val)\
        out_pmio(ctxt, pmic, PMIO_TRI_LED_EN_CTL_ATC_ADDR(base), val)
#define PMIO_TRI_LED_EN_CTL_ATC_OUTF(ctxt, pmic, base, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_TRI_LED_EN_CTL_ATC_ADDR(base), mask, shift, val)
#define PMIO_TRI_LED_EN_CTL_ATC_RED_ATC_EN_BMSK                                      0x80
#define PMIO_TRI_LED_EN_CTL_ATC_RED_ATC_EN_SHFT                                       0x7
#define PMIO_TRI_LED_EN_CTL_ATC_GREEN_ATC_EN_BMSK                                    0x40
#define PMIO_TRI_LED_EN_CTL_ATC_GREEN_ATC_EN_SHFT                                     0x6
#define PMIO_TRI_LED_EN_CTL_ATC_BLUE_ATC_EN_BMSK                                     0x20
#define PMIO_TRI_LED_EN_CTL_ATC_BLUE_ATC_EN_SHFT                                      0x5

#define PMIO_TRI_LED_SEC_ACCESS_ADDR(x)                                        ((x) + 0x000000d0)
#define PMIO_TRI_LED_SEC_ACCESS_OFFS                                           0x000000d0
#define PMIO_TRI_LED_SEC_ACCESS_RMSK                                                 0xff
#define PMIO_TRI_LED_SEC_ACCESS_IN(ctxt, pmic, base, val)\
        in_pmio_field(ctxt, pmic, PMIO_TRI_LED_SEC_ACCESS_ADDR(base), PMIO_TRI_LED_SEC_ACCESS_RMSK, 0, val)
#define PMIO_TRI_LED_SEC_ACCESS_INF(ctxt, pmic, base, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_TRI_LED_SEC_ACCESS_ADDR(base), mask, shift, val)
#define PMIO_TRI_LED_SEC_ACCESS_OUT(ctxt, pmic, base, val)\
        out_pmio(ctxt, pmic, PMIO_TRI_LED_SEC_ACCESS_ADDR(base), val)
#define PMIO_TRI_LED_SEC_ACCESS_OUTF(ctxt, pmic, base, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_TRI_LED_SEC_ACCESS_ADDR(base), mask, shift, val)
#define PMIO_TRI_LED_SEC_ACCESS_SEC_UNLOCK_BMSK                                      0xff
#define PMIO_TRI_LED_SEC_ACCESS_SEC_UNLOCK_SHFT                                       0x0

#define PMIO_TRI_LED_PERPH_RESET_CTL1_ADDR(x)                                  ((x) + 0x000000d8)
#define PMIO_TRI_LED_PERPH_RESET_CTL1_OFFS                                     0x000000d8
#define PMIO_TRI_LED_PERPH_RESET_CTL1_RMSK                                            0x1
#define PMIO_TRI_LED_PERPH_RESET_CTL1_IN(ctxt, pmic, base, val)\
        in_pmio_field(ctxt, pmic, PMIO_TRI_LED_PERPH_RESET_CTL1_ADDR(base), PMIO_TRI_LED_PERPH_RESET_CTL1_RMSK, 0, val)
#define PMIO_TRI_LED_PERPH_RESET_CTL1_INF(ctxt, pmic, base, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_TRI_LED_PERPH_RESET_CTL1_ADDR(base), mask, shift, val)
#define PMIO_TRI_LED_PERPH_RESET_CTL1_OUT(ctxt, pmic, base, val)\
        out_pmio(ctxt, pmic, PMIO_TRI_LED_PERPH_RESET_CTL1_ADDR(base), val)
#define PMIO_TRI_LED_PERPH_RESET_CTL1_OUTF(ctxt, pmic, base, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_TRI_LED_PERPH_RESET_CTL1_ADDR(base), mask, shift, val)
#define PMIO_TRI_LED_PERPH_RESET_CTL1_ENABLE_PRESET_BMSK                              0x1
#define PMIO_TRI_LED_PERPH_RESET_CTL1_ENABLE_PRESET_SHFT                              0x0

#define PMIO_TRI_LED_PERPH_RESET_CTL2_ADDR(x)                                  ((x) + 0x000000d9)
#define PMIO_TRI_LED_PERPH_RESET_CTL2_OFFS                                     0x000000d9
#define PMIO_TRI_LED_PERPH_RESET_CTL2_RMSK                                            0x1
#define PMIO_TRI_LED_PERPH_RESET_CTL2_IN(ctxt, pmic, base, val)\
        in_pmio_field(ctxt, pmic, PMIO_TRI_LED_PERPH_RESET_CTL2_ADDR(base), PMIO_TRI_LED_PERPH_RESET_CTL2_RMSK, 0, val)
#define PMIO_TRI_LED_PERPH_RESET_CTL2_INF(ctxt, pmic, base, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_TRI_LED_PERPH_RESET_CTL2_ADDR(base), mask, shift, val)
#define PMIO_TRI_LED_PERPH_RESET_CTL2_OUT(ctxt, pmic, base, val)\
        out_pmio(ctxt, pmic, PMIO_TRI_LED_PERPH_RESET_CTL2_ADDR(base), val)
#define PMIO_TRI_LED_PERPH_RESET_CTL2_OUTF(ctxt, pmic, base, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_TRI_LED_PERPH_RESET_CTL2_ADDR(base), mask, shift, val)
#define PMIO_TRI_LED_PERPH_RESET_CTL2_FOLLOW_GLOBAL_SOFT_RB_BMSK                      0x1
#define PMIO_TRI_LED_PERPH_RESET_CTL2_FOLLOW_GLOBAL_SOFT_RB_SHFT                      0x0

#define PMIO_TRI_LED_PERPH_RESET_CTL3_ADDR(x)                                  ((x) + 0x000000da)
#define PMIO_TRI_LED_PERPH_RESET_CTL3_OFFS                                     0x000000da
#define PMIO_TRI_LED_PERPH_RESET_CTL3_RMSK                                            0xf
#define PMIO_TRI_LED_PERPH_RESET_CTL3_IN(ctxt, pmic, base, val)\
        in_pmio_field(ctxt, pmic, PMIO_TRI_LED_PERPH_RESET_CTL3_ADDR(base), PMIO_TRI_LED_PERPH_RESET_CTL3_RMSK, 0, val)
#define PMIO_TRI_LED_PERPH_RESET_CTL3_INF(ctxt, pmic, base, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_TRI_LED_PERPH_RESET_CTL3_ADDR(base), mask, shift, val)
#define PMIO_TRI_LED_PERPH_RESET_CTL3_OUT(ctxt, pmic, base, val)\
        out_pmio(ctxt, pmic, PMIO_TRI_LED_PERPH_RESET_CTL3_ADDR(base), val)
#define PMIO_TRI_LED_PERPH_RESET_CTL3_OUTF(ctxt, pmic, base, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_TRI_LED_PERPH_RESET_CTL3_ADDR(base), mask, shift, val)
#define PMIO_TRI_LED_PERPH_RESET_CTL3_FOLLOW_OTST2_RB_BMSK                            0x8
#define PMIO_TRI_LED_PERPH_RESET_CTL3_FOLLOW_OTST2_RB_SHFT                            0x3
#define PMIO_TRI_LED_PERPH_RESET_CTL3_FOLLOW_WARM_RB_BMSK                             0x4
#define PMIO_TRI_LED_PERPH_RESET_CTL3_FOLLOW_WARM_RB_SHFT                             0x2
#define PMIO_TRI_LED_PERPH_RESET_CTL3_FOLLOW_SHUTDOWN1_RB_BMSK                        0x2
#define PMIO_TRI_LED_PERPH_RESET_CTL3_FOLLOW_SHUTDOWN1_RB_SHFT                        0x1
#define PMIO_TRI_LED_PERPH_RESET_CTL3_FOLLOW_SHUTDOWN2_RB_BMSK                        0x1
#define PMIO_TRI_LED_PERPH_RESET_CTL3_FOLLOW_SHUTDOWN2_RB_SHFT                        0x0

#define PMIO_TRI_LED_PERPH_RESET_CTL4_ADDR(x)                                  ((x) + 0x000000db)
#define PMIO_TRI_LED_PERPH_RESET_CTL4_OFFS                                     0x000000db
#define PMIO_TRI_LED_PERPH_RESET_CTL4_RMSK                                            0x1
#define PMIO_TRI_LED_PERPH_RESET_CTL4_IN(ctxt, pmic, base, val)\
        in_pmio_field(ctxt, pmic, PMIO_TRI_LED_PERPH_RESET_CTL4_ADDR(base), PMIO_TRI_LED_PERPH_RESET_CTL4_RMSK, 0, val)
#define PMIO_TRI_LED_PERPH_RESET_CTL4_INF(ctxt, pmic, base, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_TRI_LED_PERPH_RESET_CTL4_ADDR(base), mask, shift, val)
#define PMIO_TRI_LED_PERPH_RESET_CTL4_OUT(ctxt, pmic, base, val)\
        out_pmio(ctxt, pmic, PMIO_TRI_LED_PERPH_RESET_CTL4_ADDR(base), val)
#define PMIO_TRI_LED_PERPH_RESET_CTL4_OUTF(ctxt, pmic, base, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_TRI_LED_PERPH_RESET_CTL4_ADDR(base), mask, shift, val)
#define PMIO_TRI_LED_PERPH_RESET_CTL4_LOCAL_SOFT_RESET_BMSK                           0x1
#define PMIO_TRI_LED_PERPH_RESET_CTL4_LOCAL_SOFT_RESET_SHFT                           0x0

#define PMIO_TRI_LED_TEST1_ADDR(x)                                             ((x) + 0x000000e2)
#define PMIO_TRI_LED_TEST1_OFFS                                                0x000000e2
#define PMIO_TRI_LED_TEST1_RMSK                                                      0x3f
#define PMIO_TRI_LED_TEST1_IN(ctxt, pmic, base, val)\
        in_pmio_field(ctxt, pmic, PMIO_TRI_LED_TEST1_ADDR(base), PMIO_TRI_LED_TEST1_RMSK, 0, val)
#define PMIO_TRI_LED_TEST1_INF(ctxt, pmic, base, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_TRI_LED_TEST1_ADDR(base), mask, shift, val)
#define PMIO_TRI_LED_TEST1_OUT(ctxt, pmic, base, val)\
        out_pmio(ctxt, pmic, PMIO_TRI_LED_TEST1_ADDR(base), val)
#define PMIO_TRI_LED_TEST1_OUTF(ctxt, pmic, base, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_TRI_LED_TEST1_ADDR(base), mask, shift, val)
#define PMIO_TRI_LED_TEST1_CLOSE_LOOP_TEST_EN_BMSK                                   0x30
#define PMIO_TRI_LED_TEST1_CLOSE_LOOP_TEST_EN_SHFT                                    0x4
#define PMIO_TRI_LED_TEST1_OPEN_LOOP_CAL_EN_BMSK                                      0x8
#define PMIO_TRI_LED_TEST1_OPEN_LOOP_CAL_EN_SHFT                                      0x3
#define PMIO_TRI_LED_TEST1_ATEST_MODE_EN_BMSK                                         0x4
#define PMIO_TRI_LED_TEST1_ATEST_MODE_EN_SHFT                                         0x2
#define PMIO_TRI_LED_TEST1_PWM_8MA_SEL_BMSK                                           0x2
#define PMIO_TRI_LED_TEST1_PWM_8MA_SEL_SHFT                                           0x1
#define PMIO_TRI_LED_TEST1_PWM_4MA_SEL_BMSK                                           0x1
#define PMIO_TRI_LED_TEST1_PWM_4MA_SEL_SHFT                                           0x0

#define PMIO_TRI_LED_TRIM_NUM_ADDR(x)                                          ((x) + 0x000000f0)
#define PMIO_TRI_LED_TRIM_NUM_OFFS                                             0x000000f0
#define PMIO_TRI_LED_TRIM_NUM_RMSK                                                   0xff
#define PMIO_TRI_LED_TRIM_NUM_IN(ctxt, pmic, base, val)\
        in_pmio_field(ctxt, pmic, PMIO_TRI_LED_TRIM_NUM_ADDR(base), PMIO_TRI_LED_TRIM_NUM_RMSK, 0, val)
#define PMIO_TRI_LED_TRIM_NUM_INF(ctxt, pmic, base, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_TRI_LED_TRIM_NUM_ADDR(base), mask, shift, val)
#define PMIO_TRI_LED_TRIM_NUM_TRIM_NUM_BMSK                                          0xff
#define PMIO_TRI_LED_TRIM_NUM_TRIM_NUM_SHFT                                           0x0

#define PMIO_TRI_LED_R_LED_AMP_OFFSET_TRIM_ADDR(x)                             ((x) + 0x000000f1)
#define PMIO_TRI_LED_R_LED_AMP_OFFSET_TRIM_OFFS                                0x000000f1
#define PMIO_TRI_LED_R_LED_AMP_OFFSET_TRIM_RMSK                                       0xf
#define PMIO_TRI_LED_R_LED_AMP_OFFSET_TRIM_IN(ctxt, pmic, base, val)\
        in_pmio_field(ctxt, pmic, PMIO_TRI_LED_R_LED_AMP_OFFSET_TRIM_ADDR(base), PMIO_TRI_LED_R_LED_AMP_OFFSET_TRIM_RMSK, 0, val)
#define PMIO_TRI_LED_R_LED_AMP_OFFSET_TRIM_INF(ctxt, pmic, base, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_TRI_LED_R_LED_AMP_OFFSET_TRIM_ADDR(base), mask, shift, val)
#define PMIO_TRI_LED_R_LED_AMP_OFFSET_TRIM_OUT(ctxt, pmic, base, val)\
        out_pmio(ctxt, pmic, PMIO_TRI_LED_R_LED_AMP_OFFSET_TRIM_ADDR(base), val)
#define PMIO_TRI_LED_R_LED_AMP_OFFSET_TRIM_OUTF(ctxt, pmic, base, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_TRI_LED_R_LED_AMP_OFFSET_TRIM_ADDR(base), mask, shift, val)
#define PMIO_TRI_LED_R_LED_AMP_OFFSET_TRIM_R_LED_AMP_OFFSET_TRIM_BMSK                 0xf
#define PMIO_TRI_LED_R_LED_AMP_OFFSET_TRIM_R_LED_AMP_OFFSET_TRIM_SHFT                 0x0

#define PMIO_TRI_LED_G_LED_AMP_OFFSET_TRIM_ADDR(x)                             ((x) + 0x000000f2)
#define PMIO_TRI_LED_G_LED_AMP_OFFSET_TRIM_OFFS                                0x000000f2
#define PMIO_TRI_LED_G_LED_AMP_OFFSET_TRIM_RMSK                                       0xf
#define PMIO_TRI_LED_G_LED_AMP_OFFSET_TRIM_IN(ctxt, pmic, base, val)\
        in_pmio_field(ctxt, pmic, PMIO_TRI_LED_G_LED_AMP_OFFSET_TRIM_ADDR(base), PMIO_TRI_LED_G_LED_AMP_OFFSET_TRIM_RMSK, 0, val)
#define PMIO_TRI_LED_G_LED_AMP_OFFSET_TRIM_INF(ctxt, pmic, base, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_TRI_LED_G_LED_AMP_OFFSET_TRIM_ADDR(base), mask, shift, val)
#define PMIO_TRI_LED_G_LED_AMP_OFFSET_TRIM_OUT(ctxt, pmic, base, val)\
        out_pmio(ctxt, pmic, PMIO_TRI_LED_G_LED_AMP_OFFSET_TRIM_ADDR(base), val)
#define PMIO_TRI_LED_G_LED_AMP_OFFSET_TRIM_OUTF(ctxt, pmic, base, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_TRI_LED_G_LED_AMP_OFFSET_TRIM_ADDR(base), mask, shift, val)
#define PMIO_TRI_LED_G_LED_AMP_OFFSET_TRIM_G_LED_AMP_OFFSET_TRIM_BMSK                 0xf
#define PMIO_TRI_LED_G_LED_AMP_OFFSET_TRIM_G_LED_AMP_OFFSET_TRIM_SHFT                 0x0

#define PMIO_TRI_LED_B_LED_AMP_OFFSET_TRIM_ADDR(x)                             ((x) + 0x000000f3)
#define PMIO_TRI_LED_B_LED_AMP_OFFSET_TRIM_OFFS                                0x000000f3
#define PMIO_TRI_LED_B_LED_AMP_OFFSET_TRIM_RMSK                                       0xf
#define PMIO_TRI_LED_B_LED_AMP_OFFSET_TRIM_IN(ctxt, pmic, base, val)\
        in_pmio_field(ctxt, pmic, PMIO_TRI_LED_B_LED_AMP_OFFSET_TRIM_ADDR(base), PMIO_TRI_LED_B_LED_AMP_OFFSET_TRIM_RMSK, 0, val)
#define PMIO_TRI_LED_B_LED_AMP_OFFSET_TRIM_INF(ctxt, pmic, base, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_TRI_LED_B_LED_AMP_OFFSET_TRIM_ADDR(base), mask, shift, val)
#define PMIO_TRI_LED_B_LED_AMP_OFFSET_TRIM_OUT(ctxt, pmic, base, val)\
        out_pmio(ctxt, pmic, PMIO_TRI_LED_B_LED_AMP_OFFSET_TRIM_ADDR(base), val)
#define PMIO_TRI_LED_B_LED_AMP_OFFSET_TRIM_OUTF(ctxt, pmic, base, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_TRI_LED_B_LED_AMP_OFFSET_TRIM_ADDR(base), mask, shift, val)
#define PMIO_TRI_LED_B_LED_AMP_OFFSET_TRIM_B_LED_AMP_OFFSET_TRIM_BMSK                 0xf
#define PMIO_TRI_LED_B_LED_AMP_OFFSET_TRIM_B_LED_AMP_OFFSET_TRIM_SHFT                 0x0

#define PMIO_TRI_LED_R_12MA_CURRENT_TRIM_ADDR(x)                               ((x) + 0x000000f4)
#define PMIO_TRI_LED_R_12MA_CURRENT_TRIM_OFFS                                  0x000000f4
#define PMIO_TRI_LED_R_12MA_CURRENT_TRIM_RMSK                                        0x1f
#define PMIO_TRI_LED_R_12MA_CURRENT_TRIM_IN(ctxt, pmic, base, val)\
        in_pmio_field(ctxt, pmic, PMIO_TRI_LED_R_12MA_CURRENT_TRIM_ADDR(base), PMIO_TRI_LED_R_12MA_CURRENT_TRIM_RMSK, 0, val)
#define PMIO_TRI_LED_R_12MA_CURRENT_TRIM_INF(ctxt, pmic, base, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_TRI_LED_R_12MA_CURRENT_TRIM_ADDR(base), mask, shift, val)
#define PMIO_TRI_LED_R_12MA_CURRENT_TRIM_OUT(ctxt, pmic, base, val)\
        out_pmio(ctxt, pmic, PMIO_TRI_LED_R_12MA_CURRENT_TRIM_ADDR(base), val)
#define PMIO_TRI_LED_R_12MA_CURRENT_TRIM_OUTF(ctxt, pmic, base, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_TRI_LED_R_12MA_CURRENT_TRIM_ADDR(base), mask, shift, val)
#define PMIO_TRI_LED_R_12MA_CURRENT_TRIM_R_12MA_CURRENT_TRIM_BMSK                    0x1f
#define PMIO_TRI_LED_R_12MA_CURRENT_TRIM_R_12MA_CURRENT_TRIM_SHFT                     0x0

#define PMIO_TRI_LED_G_12MA_CURRENT_TRIM_ADDR(x)                               ((x) + 0x000000f5)
#define PMIO_TRI_LED_G_12MA_CURRENT_TRIM_OFFS                                  0x000000f5
#define PMIO_TRI_LED_G_12MA_CURRENT_TRIM_RMSK                                        0x1f
#define PMIO_TRI_LED_G_12MA_CURRENT_TRIM_IN(ctxt, pmic, base, val)\
        in_pmio_field(ctxt, pmic, PMIO_TRI_LED_G_12MA_CURRENT_TRIM_ADDR(base), PMIO_TRI_LED_G_12MA_CURRENT_TRIM_RMSK, 0, val)
#define PMIO_TRI_LED_G_12MA_CURRENT_TRIM_INF(ctxt, pmic, base, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_TRI_LED_G_12MA_CURRENT_TRIM_ADDR(base), mask, shift, val)
#define PMIO_TRI_LED_G_12MA_CURRENT_TRIM_OUT(ctxt, pmic, base, val)\
        out_pmio(ctxt, pmic, PMIO_TRI_LED_G_12MA_CURRENT_TRIM_ADDR(base), val)
#define PMIO_TRI_LED_G_12MA_CURRENT_TRIM_OUTF(ctxt, pmic, base, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_TRI_LED_G_12MA_CURRENT_TRIM_ADDR(base), mask, shift, val)
#define PMIO_TRI_LED_G_12MA_CURRENT_TRIM_G_12MA_CURRENT_TRIM_BMSK                    0x1f
#define PMIO_TRI_LED_G_12MA_CURRENT_TRIM_G_12MA_CURRENT_TRIM_SHFT                     0x0

#define PMIO_TRI_LED_B_12MA_CURRENT_TRIM_ADDR(x)                               ((x) + 0x000000f6)
#define PMIO_TRI_LED_B_12MA_CURRENT_TRIM_OFFS                                  0x000000f6
#define PMIO_TRI_LED_B_12MA_CURRENT_TRIM_RMSK                                        0x1f
#define PMIO_TRI_LED_B_12MA_CURRENT_TRIM_IN(ctxt, pmic, base, val)\
        in_pmio_field(ctxt, pmic, PMIO_TRI_LED_B_12MA_CURRENT_TRIM_ADDR(base), PMIO_TRI_LED_B_12MA_CURRENT_TRIM_RMSK, 0, val)
#define PMIO_TRI_LED_B_12MA_CURRENT_TRIM_INF(ctxt, pmic, base, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_TRI_LED_B_12MA_CURRENT_TRIM_ADDR(base), mask, shift, val)
#define PMIO_TRI_LED_B_12MA_CURRENT_TRIM_OUT(ctxt, pmic, base, val)\
        out_pmio(ctxt, pmic, PMIO_TRI_LED_B_12MA_CURRENT_TRIM_ADDR(base), val)
#define PMIO_TRI_LED_B_12MA_CURRENT_TRIM_OUTF(ctxt, pmic, base, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_TRI_LED_B_12MA_CURRENT_TRIM_ADDR(base), mask, shift, val)
#define PMIO_TRI_LED_B_12MA_CURRENT_TRIM_B_12MA_CURRENT_TRIM_BMSK                    0x1f
#define PMIO_TRI_LED_B_12MA_CURRENT_TRIM_B_12MA_CURRENT_TRIM_SHFT                     0x0


#endif /* __PM_RGB_REGS_H__ */
