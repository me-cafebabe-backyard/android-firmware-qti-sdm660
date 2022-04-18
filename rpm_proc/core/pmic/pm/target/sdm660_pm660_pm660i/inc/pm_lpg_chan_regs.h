#ifndef __PM_LPG_CHAN_REGS_H__
#define __PM_LPG_CHAN_REGS_H__
/*
===========================================================================
*/
/**
  @file pm_lpg_chan_regs.h
  @brief Auto-generated PMIO interface include file.

  This file contains PMIO register definitions for the following modules:
    LPG_CHAN1

  'Include' filters applied: <none>
  'Exclude' filters applied: RESERVED DUMMY 
*/
/*
  ===========================================================================

  Copyright (c) 2014-2016 Qualcomm Technologies Incorporated.
  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ===========================================================================

  $Header: //components/rel/rpm.bf/1.8/core/pmic/pm/target/sdm660_pm660_pm660i/inc/pm_lpg_chan_regs.h#1 $
  $DateTime: 2016/11/03 00:13:13 $   
  $Author: pwbldsvc $

  ===========================================================================
*/

/*----------------------------------------------------------------------------
 * PERIPHERAL: LPG_CHAN_LPG_CHAN
 *--------------------------------------------------------------------------*/

#define PMIO_LPG_CHAN_REVISION1_ADDR(x)                                            ((x) + 0x00000000)
#define PMIO_LPG_CHAN_REVISION1_OFFS                                               0x00000000
#define PMIO_LPG_CHAN_REVISION1_RMSK                                                     0xff
#define PMIO_LPG_CHAN_REVISION1_IN(ctxt, pmic, base, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_REVISION1_ADDR(base), PMIO_LPG_CHAN_REVISION1_RMSK, 0, val)
#define PMIO_LPG_CHAN_REVISION1_INF(ctxt, pmic, base, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_REVISION1_ADDR(base), mask, shift, val)
#define PMIO_LPG_CHAN_REVISION1_DIG_MINOR_BMSK                                           0xff
#define PMIO_LPG_CHAN_REVISION1_DIG_MINOR_SHFT                                            0x0

#define PMIO_LPG_CHAN_REVISION2_ADDR(x)                                            ((x) + 0x00000001)
#define PMIO_LPG_CHAN_REVISION2_OFFS                                               0x00000001
#define PMIO_LPG_CHAN_REVISION2_RMSK                                                     0xff
#define PMIO_LPG_CHAN_REVISION2_IN(ctxt, pmic, base, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_REVISION2_ADDR(base), PMIO_LPG_CHAN_REVISION2_RMSK, 0, val)
#define PMIO_LPG_CHAN_REVISION2_INF(ctxt, pmic, base, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_REVISION2_ADDR(base), mask, shift, val)
#define PMIO_LPG_CHAN_REVISION2_DIG_MAJOR_BMSK                                           0xff
#define PMIO_LPG_CHAN_REVISION2_DIG_MAJOR_SHFT                                            0x0

#define PMIO_LPG_CHAN_PERPH_TYPE_ADDR(x)                                           ((x) + 0x00000004)
#define PMIO_LPG_CHAN_PERPH_TYPE_OFFS                                              0x00000004
#define PMIO_LPG_CHAN_PERPH_TYPE_RMSK                                                    0xff
#define PMIO_LPG_CHAN_PERPH_TYPE_IN(ctxt, pmic, base, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_PERPH_TYPE_ADDR(base), PMIO_LPG_CHAN_PERPH_TYPE_RMSK, 0, val)
#define PMIO_LPG_CHAN_PERPH_TYPE_INF(ctxt, pmic, base, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_PERPH_TYPE_ADDR(base), mask, shift, val)
#define PMIO_LPG_CHAN_PERPH_TYPE_TYPE_BMSK                                               0xff
#define PMIO_LPG_CHAN_PERPH_TYPE_TYPE_SHFT                                                0x0

#define PMIO_LPG_CHAN_PERPH_SUBTYPE_ADDR(x)                                        ((x) + 0x00000005)
#define PMIO_LPG_CHAN_PERPH_SUBTYPE_OFFS                                           0x00000005
#define PMIO_LPG_CHAN_PERPH_SUBTYPE_RMSK                                                 0xff
#define PMIO_LPG_CHAN_PERPH_SUBTYPE_IN(ctxt, pmic, base, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_PERPH_SUBTYPE_ADDR(base), PMIO_LPG_CHAN_PERPH_SUBTYPE_RMSK, 0, val)
#define PMIO_LPG_CHAN_PERPH_SUBTYPE_INF(ctxt, pmic, base, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_PERPH_SUBTYPE_ADDR(base), mask, shift, val)
#define PMIO_LPG_CHAN_PERPH_SUBTYPE_SUBTYPE_BMSK                                         0xff
#define PMIO_LPG_CHAN_PERPH_SUBTYPE_SUBTYPE_SHFT                                          0x0

#define PMIO_LPG_CHAN_INT_RT_STS_ADDR(x)                                           ((x) + 0x00000010)
#define PMIO_LPG_CHAN_INT_RT_STS_OFFS                                              0x00000010
#define PMIO_LPG_CHAN_INT_RT_STS_RMSK                                                     0x1
#define PMIO_LPG_CHAN_INT_RT_STS_IN(ctxt, pmic, base, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_INT_RT_STS_ADDR(base), PMIO_LPG_CHAN_INT_RT_STS_RMSK, 0, val)
#define PMIO_LPG_CHAN_INT_RT_STS_INF(ctxt, pmic, base, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_INT_RT_STS_ADDR(base), mask, shift, val)
#define PMIO_LPG_CHAN_INT_RT_STS_LPG_INT_RT_STS_BMSK                                      0x1
#define PMIO_LPG_CHAN_INT_RT_STS_LPG_INT_RT_STS_SHFT                                      0x0

#define PMIO_LPG_CHAN_INT_SET_TYPE_ADDR(x)                                         ((x) + 0x00000011)
#define PMIO_LPG_CHAN_INT_SET_TYPE_OFFS                                            0x00000011
#define PMIO_LPG_CHAN_INT_SET_TYPE_RMSK                                                   0x1
#define PMIO_LPG_CHAN_INT_SET_TYPE_IN(ctxt, pmic, base, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_INT_SET_TYPE_ADDR(base), PMIO_LPG_CHAN_INT_SET_TYPE_RMSK, 0, val)
#define PMIO_LPG_CHAN_INT_SET_TYPE_INF(ctxt, pmic, base, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_INT_SET_TYPE_ADDR(base), mask, shift, val)
#define PMIO_LPG_CHAN_INT_SET_TYPE_OUT(ctxt, pmic, base, val)\
        out_pmio(ctxt, pmic, PMIO_LPG_CHAN_INT_SET_TYPE_ADDR(base), val)
#define PMIO_LPG_CHAN_INT_SET_TYPE_OUTF(ctxt, pmic, base, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_INT_SET_TYPE_ADDR(base), mask, shift, val)
#define PMIO_LPG_CHAN_INT_SET_TYPE_LPG_INT_TYPE_BMSK                                      0x1
#define PMIO_LPG_CHAN_INT_SET_TYPE_LPG_INT_TYPE_SHFT                                      0x0

#define PMIO_LPG_CHAN_INT_POLARITY_HIGH_ADDR(x)                                    ((x) + 0x00000012)
#define PMIO_LPG_CHAN_INT_POLARITY_HIGH_OFFS                                       0x00000012
#define PMIO_LPG_CHAN_INT_POLARITY_HIGH_RMSK                                              0x1
#define PMIO_LPG_CHAN_INT_POLARITY_HIGH_IN(ctxt, pmic, base, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_INT_POLARITY_HIGH_ADDR(base), PMIO_LPG_CHAN_INT_POLARITY_HIGH_RMSK, 0, val)
#define PMIO_LPG_CHAN_INT_POLARITY_HIGH_INF(ctxt, pmic, base, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_INT_POLARITY_HIGH_ADDR(base), mask, shift, val)
#define PMIO_LPG_CHAN_INT_POLARITY_HIGH_OUT(ctxt, pmic, base, val)\
        out_pmio(ctxt, pmic, PMIO_LPG_CHAN_INT_POLARITY_HIGH_ADDR(base), val)
#define PMIO_LPG_CHAN_INT_POLARITY_HIGH_OUTF(ctxt, pmic, base, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_INT_POLARITY_HIGH_ADDR(base), mask, shift, val)
#define PMIO_LPG_CHAN_INT_POLARITY_HIGH_LPG_INT_HIGH_BMSK                                 0x1
#define PMIO_LPG_CHAN_INT_POLARITY_HIGH_LPG_INT_HIGH_SHFT                                 0x0

#define PMIO_LPG_CHAN_INT_POLARITY_LOW_ADDR(x)                                     ((x) + 0x00000013)
#define PMIO_LPG_CHAN_INT_POLARITY_LOW_OFFS                                        0x00000013
#define PMIO_LPG_CHAN_INT_POLARITY_LOW_RMSK                                               0x1
#define PMIO_LPG_CHAN_INT_POLARITY_LOW_IN(ctxt, pmic, base, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_INT_POLARITY_LOW_ADDR(base), PMIO_LPG_CHAN_INT_POLARITY_LOW_RMSK, 0, val)
#define PMIO_LPG_CHAN_INT_POLARITY_LOW_INF(ctxt, pmic, base, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_INT_POLARITY_LOW_ADDR(base), mask, shift, val)
#define PMIO_LPG_CHAN_INT_POLARITY_LOW_OUT(ctxt, pmic, base, val)\
        out_pmio(ctxt, pmic, PMIO_LPG_CHAN_INT_POLARITY_LOW_ADDR(base), val)
#define PMIO_LPG_CHAN_INT_POLARITY_LOW_OUTF(ctxt, pmic, base, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_INT_POLARITY_LOW_ADDR(base), mask, shift, val)
#define PMIO_LPG_CHAN_INT_POLARITY_LOW_LPG_INT_LOW_BMSK                                   0x1
#define PMIO_LPG_CHAN_INT_POLARITY_LOW_LPG_INT_LOW_SHFT                                   0x0

#define PMIO_LPG_CHAN_INT_LATCHED_CLR_ADDR(x)                                      ((x) + 0x00000014)
#define PMIO_LPG_CHAN_INT_LATCHED_CLR_OFFS                                         0x00000014
#define PMIO_LPG_CHAN_INT_LATCHED_CLR_RMSK                                                0x1
#define PMIO_LPG_CHAN_INT_LATCHED_CLR_OUT(ctxt, pmic, base, val)\
        out_pmio(ctxt, pmic, PMIO_LPG_CHAN_INT_LATCHED_CLR_ADDR(base), val)
#define PMIO_LPG_CHAN_INT_LATCHED_CLR_LPG_INT_LATCHED_CLR_BMSK                            0x1
#define PMIO_LPG_CHAN_INT_LATCHED_CLR_LPG_INT_LATCHED_CLR_SHFT                            0x0

#define PMIO_LPG_CHAN_INT_EN_SET_ADDR(x)                                           ((x) + 0x00000015)
#define PMIO_LPG_CHAN_INT_EN_SET_OFFS                                              0x00000015
#define PMIO_LPG_CHAN_INT_EN_SET_RMSK                                                     0x1
#define PMIO_LPG_CHAN_INT_EN_SET_IN(ctxt, pmic, base, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_INT_EN_SET_ADDR(base), PMIO_LPG_CHAN_INT_EN_SET_RMSK, 0, val)
#define PMIO_LPG_CHAN_INT_EN_SET_INF(ctxt, pmic, base, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_INT_EN_SET_ADDR(base), mask, shift, val)
#define PMIO_LPG_CHAN_INT_EN_SET_OUT(ctxt, pmic, base, val)\
        out_pmio(ctxt, pmic, PMIO_LPG_CHAN_INT_EN_SET_ADDR(base), val)
#define PMIO_LPG_CHAN_INT_EN_SET_OUTF(ctxt, pmic, base, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_INT_EN_SET_ADDR(base), mask, shift, val)
#define PMIO_LPG_CHAN_INT_EN_SET_LPG_INT_EN_SET_BMSK                                      0x1
#define PMIO_LPG_CHAN_INT_EN_SET_LPG_INT_EN_SET_SHFT                                      0x0

#define PMIO_LPG_CHAN_INT_EN_CLR_ADDR(x)                                           ((x) + 0x00000016)
#define PMIO_LPG_CHAN_INT_EN_CLR_OFFS                                              0x00000016
#define PMIO_LPG_CHAN_INT_EN_CLR_RMSK                                                     0x1
#define PMIO_LPG_CHAN_INT_EN_CLR_IN(ctxt, pmic, base, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_INT_EN_CLR_ADDR(base), PMIO_LPG_CHAN_INT_EN_CLR_RMSK, 0, val)
#define PMIO_LPG_CHAN_INT_EN_CLR_INF(ctxt, pmic, base, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_INT_EN_CLR_ADDR(base), mask, shift, val)
#define PMIO_LPG_CHAN_INT_EN_CLR_OUT(ctxt, pmic, base, val)\
        out_pmio(ctxt, pmic, PMIO_LPG_CHAN_INT_EN_CLR_ADDR(base), val)
#define PMIO_LPG_CHAN_INT_EN_CLR_OUTF(ctxt, pmic, base, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_INT_EN_CLR_ADDR(base), mask, shift, val)
#define PMIO_LPG_CHAN_INT_EN_CLR_LPG_INT_EN_CLR_BMSK                                      0x1
#define PMIO_LPG_CHAN_INT_EN_CLR_LPG_INT_EN_CLR_SHFT                                      0x0

#define PMIO_LPG_CHAN_INT_LATCHED_STS_ADDR(x)                                      ((x) + 0x00000018)
#define PMIO_LPG_CHAN_INT_LATCHED_STS_OFFS                                         0x00000018
#define PMIO_LPG_CHAN_INT_LATCHED_STS_RMSK                                                0x1
#define PMIO_LPG_CHAN_INT_LATCHED_STS_IN(ctxt, pmic, base, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_INT_LATCHED_STS_ADDR(base), PMIO_LPG_CHAN_INT_LATCHED_STS_RMSK, 0, val)
#define PMIO_LPG_CHAN_INT_LATCHED_STS_INF(ctxt, pmic, base, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_INT_LATCHED_STS_ADDR(base), mask, shift, val)
#define PMIO_LPG_CHAN_INT_LATCHED_STS_LPG_INT_LATCHED_STS_BMSK                            0x1
#define PMIO_LPG_CHAN_INT_LATCHED_STS_LPG_INT_LATCHED_STS_SHFT                            0x0

#define PMIO_LPG_CHAN_INT_PENDING_STS_ADDR(x)                                      ((x) + 0x00000019)
#define PMIO_LPG_CHAN_INT_PENDING_STS_OFFS                                         0x00000019
#define PMIO_LPG_CHAN_INT_PENDING_STS_RMSK                                                0x1
#define PMIO_LPG_CHAN_INT_PENDING_STS_IN(ctxt, pmic, base, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_INT_PENDING_STS_ADDR(base), PMIO_LPG_CHAN_INT_PENDING_STS_RMSK, 0, val)
#define PMIO_LPG_CHAN_INT_PENDING_STS_INF(ctxt, pmic, base, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_INT_PENDING_STS_ADDR(base), mask, shift, val)
#define PMIO_LPG_CHAN_INT_PENDING_STS_LPG_INT_PENDING_STS_BMSK                            0x1
#define PMIO_LPG_CHAN_INT_PENDING_STS_LPG_INT_PENDING_STS_SHFT                            0x0

#define PMIO_LPG_CHAN_INT_MID_SEL_ADDR(x)                                          ((x) + 0x0000001a)
#define PMIO_LPG_CHAN_INT_MID_SEL_OFFS                                             0x0000001a
#define PMIO_LPG_CHAN_INT_MID_SEL_RMSK                                                    0x3
#define PMIO_LPG_CHAN_INT_MID_SEL_IN(ctxt, pmic, base, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_INT_MID_SEL_ADDR(base), PMIO_LPG_CHAN_INT_MID_SEL_RMSK, 0, val)
#define PMIO_LPG_CHAN_INT_MID_SEL_INF(ctxt, pmic, base, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_INT_MID_SEL_ADDR(base), mask, shift, val)
#define PMIO_LPG_CHAN_INT_MID_SEL_OUT(ctxt, pmic, base, val)\
        out_pmio(ctxt, pmic, PMIO_LPG_CHAN_INT_MID_SEL_ADDR(base), val)
#define PMIO_LPG_CHAN_INT_MID_SEL_OUTF(ctxt, pmic, base, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_INT_MID_SEL_ADDR(base), mask, shift, val)
#define PMIO_LPG_CHAN_INT_MID_SEL_INT_MID_SEL_BMSK                                        0x3
#define PMIO_LPG_CHAN_INT_MID_SEL_INT_MID_SEL_SHFT                                        0x0

#define PMIO_LPG_CHAN_INT_PRIORITY_ADDR(x)                                         ((x) + 0x0000001b)
#define PMIO_LPG_CHAN_INT_PRIORITY_OFFS                                            0x0000001b
#define PMIO_LPG_CHAN_INT_PRIORITY_RMSK                                                   0x1
#define PMIO_LPG_CHAN_INT_PRIORITY_IN(ctxt, pmic, base, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_INT_PRIORITY_ADDR(base), PMIO_LPG_CHAN_INT_PRIORITY_RMSK, 0, val)
#define PMIO_LPG_CHAN_INT_PRIORITY_INF(ctxt, pmic, base, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_INT_PRIORITY_ADDR(base), mask, shift, val)
#define PMIO_LPG_CHAN_INT_PRIORITY_OUT(ctxt, pmic, base, val)\
        out_pmio(ctxt, pmic, PMIO_LPG_CHAN_INT_PRIORITY_ADDR(base), val)
#define PMIO_LPG_CHAN_INT_PRIORITY_OUTF(ctxt, pmic, base, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_INT_PRIORITY_ADDR(base), mask, shift, val)
#define PMIO_LPG_CHAN_INT_PRIORITY_INT_PRIORITY_BMSK                                      0x1
#define PMIO_LPG_CHAN_INT_PRIORITY_INT_PRIORITY_SHFT                                      0x0

#define PMIO_LPG_CHAN_LPG_PATTERN_CONFIG_ADDR(x)                                   ((x) + 0x00000040)
#define PMIO_LPG_CHAN_LPG_PATTERN_CONFIG_OFFS                                      0x00000040
#define PMIO_LPG_CHAN_LPG_PATTERN_CONFIG_RMSK                                            0x1f
#define PMIO_LPG_CHAN_LPG_PATTERN_CONFIG_IN(ctxt, pmic, base, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_LPG_PATTERN_CONFIG_ADDR(base), PMIO_LPG_CHAN_LPG_PATTERN_CONFIG_RMSK, 0, val)
#define PMIO_LPG_CHAN_LPG_PATTERN_CONFIG_INF(ctxt, pmic, base, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_LPG_PATTERN_CONFIG_ADDR(base), mask, shift, val)
#define PMIO_LPG_CHAN_LPG_PATTERN_CONFIG_OUT(ctxt, pmic, base, val)\
        out_pmio(ctxt, pmic, PMIO_LPG_CHAN_LPG_PATTERN_CONFIG_ADDR(base), val)
#define PMIO_LPG_CHAN_LPG_PATTERN_CONFIG_OUTF(ctxt, pmic, base, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_LPG_PATTERN_CONFIG_ADDR(base), mask, shift, val)
#define PMIO_LPG_CHAN_LPG_PATTERN_CONFIG_RAMP_DIRECTION_BMSK                             0x10
#define PMIO_LPG_CHAN_LPG_PATTERN_CONFIG_RAMP_DIRECTION_SHFT                              0x4
#define PMIO_LPG_CHAN_LPG_PATTERN_CONFIG_PATTERN_REPEAT_BMSK                              0x8
#define PMIO_LPG_CHAN_LPG_PATTERN_CONFIG_PATTERN_REPEAT_SHFT                              0x3
#define PMIO_LPG_CHAN_LPG_PATTERN_CONFIG_RAMP_TOGGLE_BMSK                                 0x4
#define PMIO_LPG_CHAN_LPG_PATTERN_CONFIG_RAMP_TOGGLE_SHFT                                 0x2
#define PMIO_LPG_CHAN_LPG_PATTERN_CONFIG_EN_PAUSE_HI_BMSK                                 0x2
#define PMIO_LPG_CHAN_LPG_PATTERN_CONFIG_EN_PAUSE_HI_SHFT                                 0x1
#define PMIO_LPG_CHAN_LPG_PATTERN_CONFIG_EN_PAUSE_LO_BMSK                                 0x1
#define PMIO_LPG_CHAN_LPG_PATTERN_CONFIG_EN_PAUSE_LO_SHFT                                 0x0

#define PMIO_LPG_CHAN_LPG_PWM_SIZE_CLK_ADDR(x)                                     ((x) + 0x00000041)
#define PMIO_LPG_CHAN_LPG_PWM_SIZE_CLK_OFFS                                        0x00000041
#define PMIO_LPG_CHAN_LPG_PWM_SIZE_CLK_RMSK                                              0x13
#define PMIO_LPG_CHAN_LPG_PWM_SIZE_CLK_IN(ctxt, pmic, base, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_LPG_PWM_SIZE_CLK_ADDR(base), PMIO_LPG_CHAN_LPG_PWM_SIZE_CLK_RMSK, 0, val)
#define PMIO_LPG_CHAN_LPG_PWM_SIZE_CLK_INF(ctxt, pmic, base, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_LPG_PWM_SIZE_CLK_ADDR(base), mask, shift, val)
#define PMIO_LPG_CHAN_LPG_PWM_SIZE_CLK_OUT(ctxt, pmic, base, val)\
        out_pmio(ctxt, pmic, PMIO_LPG_CHAN_LPG_PWM_SIZE_CLK_ADDR(base), val)
#define PMIO_LPG_CHAN_LPG_PWM_SIZE_CLK_OUTF(ctxt, pmic, base, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_LPG_PWM_SIZE_CLK_ADDR(base), mask, shift, val)
#define PMIO_LPG_CHAN_LPG_PWM_SIZE_CLK_PWM_SIZE_BMSK                                     0x10
#define PMIO_LPG_CHAN_LPG_PWM_SIZE_CLK_PWM_SIZE_SHFT                                      0x4
#define PMIO_LPG_CHAN_LPG_PWM_SIZE_CLK_PWM_FREQ_CLK_SELECT_BMSK                           0x3
#define PMIO_LPG_CHAN_LPG_PWM_SIZE_CLK_PWM_FREQ_CLK_SELECT_SHFT                           0x0

#define PMIO_LPG_CHAN_LPG_PWM_FREQ_PREDIV_CLK_ADDR(x)                              ((x) + 0x00000042)
#define PMIO_LPG_CHAN_LPG_PWM_FREQ_PREDIV_CLK_OFFS                                 0x00000042
#define PMIO_LPG_CHAN_LPG_PWM_FREQ_PREDIV_CLK_RMSK                                       0x67
#define PMIO_LPG_CHAN_LPG_PWM_FREQ_PREDIV_CLK_IN(ctxt, pmic, base, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_LPG_PWM_FREQ_PREDIV_CLK_ADDR(base), PMIO_LPG_CHAN_LPG_PWM_FREQ_PREDIV_CLK_RMSK, 0, val)
#define PMIO_LPG_CHAN_LPG_PWM_FREQ_PREDIV_CLK_INF(ctxt, pmic, base, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_LPG_PWM_FREQ_PREDIV_CLK_ADDR(base), mask, shift, val)
#define PMIO_LPG_CHAN_LPG_PWM_FREQ_PREDIV_CLK_OUT(ctxt, pmic, base, val)\
        out_pmio(ctxt, pmic, PMIO_LPG_CHAN_LPG_PWM_FREQ_PREDIV_CLK_ADDR(base), val)
#define PMIO_LPG_CHAN_LPG_PWM_FREQ_PREDIV_CLK_OUTF(ctxt, pmic, base, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_LPG_PWM_FREQ_PREDIV_CLK_ADDR(base), mask, shift, val)
#define PMIO_LPG_CHAN_LPG_PWM_FREQ_PREDIV_CLK_PWM_FREQ_PRE_DIVIDE_BMSK                   0x60
#define PMIO_LPG_CHAN_LPG_PWM_FREQ_PREDIV_CLK_PWM_FREQ_PRE_DIVIDE_SHFT                    0x5
#define PMIO_LPG_CHAN_LPG_PWM_FREQ_PREDIV_CLK_PWM_FREQ_EXPONENT_BMSK                      0x7
#define PMIO_LPG_CHAN_LPG_PWM_FREQ_PREDIV_CLK_PWM_FREQ_EXPONENT_SHFT                      0x0

#define PMIO_LPG_CHAN_LPG_PWM_TYPE_CONFIG_ADDR(x)                                  ((x) + 0x00000043)
#define PMIO_LPG_CHAN_LPG_PWM_TYPE_CONFIG_OFFS                                     0x00000043
#define PMIO_LPG_CHAN_LPG_PWM_TYPE_CONFIG_RMSK                                           0x20
#define PMIO_LPG_CHAN_LPG_PWM_TYPE_CONFIG_IN(ctxt, pmic, base, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_LPG_PWM_TYPE_CONFIG_ADDR(base), PMIO_LPG_CHAN_LPG_PWM_TYPE_CONFIG_RMSK, 0, val)
#define PMIO_LPG_CHAN_LPG_PWM_TYPE_CONFIG_INF(ctxt, pmic, base, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_LPG_PWM_TYPE_CONFIG_ADDR(base), mask, shift, val)
#define PMIO_LPG_CHAN_LPG_PWM_TYPE_CONFIG_OUT(ctxt, pmic, base, val)\
        out_pmio(ctxt, pmic, PMIO_LPG_CHAN_LPG_PWM_TYPE_CONFIG_ADDR(base), val)
#define PMIO_LPG_CHAN_LPG_PWM_TYPE_CONFIG_OUTF(ctxt, pmic, base, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_LPG_PWM_TYPE_CONFIG_ADDR(base), mask, shift, val)
#define PMIO_LPG_CHAN_LPG_PWM_TYPE_CONFIG_EN_GLITCH_REMOVAL_BMSK                         0x20
#define PMIO_LPG_CHAN_LPG_PWM_TYPE_CONFIG_EN_GLITCH_REMOVAL_SHFT                          0x5

#define PMIO_LPG_CHAN_PWM_VALUE_LSB_ADDR(x)                                        ((x) + 0x00000044)
#define PMIO_LPG_CHAN_PWM_VALUE_LSB_OFFS                                           0x00000044
#define PMIO_LPG_CHAN_PWM_VALUE_LSB_RMSK                                                 0xff
#define PMIO_LPG_CHAN_PWM_VALUE_LSB_IN(ctxt, pmic, base, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_PWM_VALUE_LSB_ADDR(base), PMIO_LPG_CHAN_PWM_VALUE_LSB_RMSK, 0, val)
#define PMIO_LPG_CHAN_PWM_VALUE_LSB_INF(ctxt, pmic, base, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_PWM_VALUE_LSB_ADDR(base), mask, shift, val)
#define PMIO_LPG_CHAN_PWM_VALUE_LSB_OUT(ctxt, pmic, base, val)\
        out_pmio(ctxt, pmic, PMIO_LPG_CHAN_PWM_VALUE_LSB_ADDR(base), val)
#define PMIO_LPG_CHAN_PWM_VALUE_LSB_OUTF(ctxt, pmic, base, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_PWM_VALUE_LSB_ADDR(base), mask, shift, val)
#define PMIO_LPG_CHAN_PWM_VALUE_LSB_PWM_VALUE_LSB_BMSK                                   0xff
#define PMIO_LPG_CHAN_PWM_VALUE_LSB_PWM_VALUE_LSB_SHFT                                    0x0

#define PMIO_LPG_CHAN_PWM_VALUE_MSB_ADDR(x)                                        ((x) + 0x00000045)
#define PMIO_LPG_CHAN_PWM_VALUE_MSB_OFFS                                           0x00000045
#define PMIO_LPG_CHAN_PWM_VALUE_MSB_RMSK                                                  0x1
#define PMIO_LPG_CHAN_PWM_VALUE_MSB_IN(ctxt, pmic, base, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_PWM_VALUE_MSB_ADDR(base), PMIO_LPG_CHAN_PWM_VALUE_MSB_RMSK, 0, val)
#define PMIO_LPG_CHAN_PWM_VALUE_MSB_INF(ctxt, pmic, base, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_PWM_VALUE_MSB_ADDR(base), mask, shift, val)
#define PMIO_LPG_CHAN_PWM_VALUE_MSB_OUT(ctxt, pmic, base, val)\
        out_pmio(ctxt, pmic, PMIO_LPG_CHAN_PWM_VALUE_MSB_ADDR(base), val)
#define PMIO_LPG_CHAN_PWM_VALUE_MSB_OUTF(ctxt, pmic, base, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_PWM_VALUE_MSB_ADDR(base), mask, shift, val)
#define PMIO_LPG_CHAN_PWM_VALUE_MSB_PWM_VALUE_MSB_BMSK                                    0x1
#define PMIO_LPG_CHAN_PWM_VALUE_MSB_PWM_VALUE_MSB_SHFT                                    0x0

#define PMIO_LPG_CHAN_ENABLE_CONTROL_ADDR(x)                                       ((x) + 0x00000046)
#define PMIO_LPG_CHAN_ENABLE_CONTROL_OFFS                                          0x00000046
#define PMIO_LPG_CHAN_ENABLE_CONTROL_RMSK                                                0xa6
#define PMIO_LPG_CHAN_ENABLE_CONTROL_IN(ctxt, pmic, base, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_ENABLE_CONTROL_ADDR(base), PMIO_LPG_CHAN_ENABLE_CONTROL_RMSK, 0, val)
#define PMIO_LPG_CHAN_ENABLE_CONTROL_INF(ctxt, pmic, base, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_ENABLE_CONTROL_ADDR(base), mask, shift, val)
#define PMIO_LPG_CHAN_ENABLE_CONTROL_OUT(ctxt, pmic, base, val)\
        out_pmio(ctxt, pmic, PMIO_LPG_CHAN_ENABLE_CONTROL_ADDR(base), val)
#define PMIO_LPG_CHAN_ENABLE_CONTROL_OUTF(ctxt, pmic, base, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_ENABLE_CONTROL_ADDR(base), mask, shift, val)
#define PMIO_LPG_CHAN_ENABLE_CONTROL_EN_SLICE_BMSK                                       0x80
#define PMIO_LPG_CHAN_ENABLE_CONTROL_EN_SLICE_SHFT                                        0x7
#define PMIO_LPG_CHAN_ENABLE_CONTROL_EN_PWM_OUTPUT_BMSK                                  0x20
#define PMIO_LPG_CHAN_ENABLE_CONTROL_EN_PWM_OUTPUT_SHFT                                   0x5
#define PMIO_LPG_CHAN_ENABLE_CONTROL_PWM_SRC_SELECT_BMSK                                  0x4
#define PMIO_LPG_CHAN_ENABLE_CONTROL_PWM_SRC_SELECT_SHFT                                  0x2
#define PMIO_LPG_CHAN_ENABLE_CONTROL_EN_RAMP_GEN_BMSK                                     0x2
#define PMIO_LPG_CHAN_ENABLE_CONTROL_EN_RAMP_GEN_SHFT                                     0x1

#define PMIO_LPG_CHAN_PWM_SYNC_ADDR(x)                                             ((x) + 0x00000047)
#define PMIO_LPG_CHAN_PWM_SYNC_OFFS                                                0x00000047
#define PMIO_LPG_CHAN_PWM_SYNC_RMSK                                                       0x1
#define PMIO_LPG_CHAN_PWM_SYNC_OUT(ctxt, pmic, base, val)\
        out_pmio(ctxt, pmic, PMIO_LPG_CHAN_PWM_SYNC_ADDR(base), val)
#define PMIO_LPG_CHAN_PWM_SYNC_SYNC_PWM_BMSK                                              0x1
#define PMIO_LPG_CHAN_PWM_SYNC_SYNC_PWM_SHFT                                              0x0

#define PMIO_LPG_CHAN_RAMP_STEP_DURATION_LSB_ADDR(x)                               ((x) + 0x00000050)
#define PMIO_LPG_CHAN_RAMP_STEP_DURATION_LSB_OFFS                                  0x00000050
#define PMIO_LPG_CHAN_RAMP_STEP_DURATION_LSB_RMSK                                        0xff
#define PMIO_LPG_CHAN_RAMP_STEP_DURATION_LSB_IN(ctxt, pmic, base, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_RAMP_STEP_DURATION_LSB_ADDR(base), PMIO_LPG_CHAN_RAMP_STEP_DURATION_LSB_RMSK, 0, val)
#define PMIO_LPG_CHAN_RAMP_STEP_DURATION_LSB_INF(ctxt, pmic, base, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_RAMP_STEP_DURATION_LSB_ADDR(base), mask, shift, val)
#define PMIO_LPG_CHAN_RAMP_STEP_DURATION_LSB_OUT(ctxt, pmic, base, val)\
        out_pmio(ctxt, pmic, PMIO_LPG_CHAN_RAMP_STEP_DURATION_LSB_ADDR(base), val)
#define PMIO_LPG_CHAN_RAMP_STEP_DURATION_LSB_OUTF(ctxt, pmic, base, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_RAMP_STEP_DURATION_LSB_ADDR(base), mask, shift, val)
#define PMIO_LPG_CHAN_RAMP_STEP_DURATION_LSB_RAMP_STEP_DURATION_LSB_BMSK                 0xff
#define PMIO_LPG_CHAN_RAMP_STEP_DURATION_LSB_RAMP_STEP_DURATION_LSB_SHFT                  0x0

#define PMIO_LPG_CHAN_RAMP_STEP_DURATION_MSB_ADDR(x)                               ((x) + 0x00000051)
#define PMIO_LPG_CHAN_RAMP_STEP_DURATION_MSB_OFFS                                  0x00000051
#define PMIO_LPG_CHAN_RAMP_STEP_DURATION_MSB_RMSK                                         0x1
#define PMIO_LPG_CHAN_RAMP_STEP_DURATION_MSB_IN(ctxt, pmic, base, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_RAMP_STEP_DURATION_MSB_ADDR(base), PMIO_LPG_CHAN_RAMP_STEP_DURATION_MSB_RMSK, 0, val)
#define PMIO_LPG_CHAN_RAMP_STEP_DURATION_MSB_INF(ctxt, pmic, base, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_RAMP_STEP_DURATION_MSB_ADDR(base), mask, shift, val)
#define PMIO_LPG_CHAN_RAMP_STEP_DURATION_MSB_OUT(ctxt, pmic, base, val)\
        out_pmio(ctxt, pmic, PMIO_LPG_CHAN_RAMP_STEP_DURATION_MSB_ADDR(base), val)
#define PMIO_LPG_CHAN_RAMP_STEP_DURATION_MSB_OUTF(ctxt, pmic, base, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_RAMP_STEP_DURATION_MSB_ADDR(base), mask, shift, val)
#define PMIO_LPG_CHAN_RAMP_STEP_DURATION_MSB_RAMP_STEP_DURATION_MSB_BMSK                  0x1
#define PMIO_LPG_CHAN_RAMP_STEP_DURATION_MSB_RAMP_STEP_DURATION_MSB_SHFT                  0x0

#define PMIO_LPG_CHAN_PAUSE_HI_MULTIPLIER_ADDR(x)                                  ((x) + 0x00000052)
#define PMIO_LPG_CHAN_PAUSE_HI_MULTIPLIER_OFFS                                     0x00000052
#define PMIO_LPG_CHAN_PAUSE_HI_MULTIPLIER_RMSK                                           0xff
#define PMIO_LPG_CHAN_PAUSE_HI_MULTIPLIER_IN(ctxt, pmic, base, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_PAUSE_HI_MULTIPLIER_ADDR(base), PMIO_LPG_CHAN_PAUSE_HI_MULTIPLIER_RMSK, 0, val)
#define PMIO_LPG_CHAN_PAUSE_HI_MULTIPLIER_INF(ctxt, pmic, base, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_PAUSE_HI_MULTIPLIER_ADDR(base), mask, shift, val)
#define PMIO_LPG_CHAN_PAUSE_HI_MULTIPLIER_OUT(ctxt, pmic, base, val)\
        out_pmio(ctxt, pmic, PMIO_LPG_CHAN_PAUSE_HI_MULTIPLIER_ADDR(base), val)
#define PMIO_LPG_CHAN_PAUSE_HI_MULTIPLIER_OUTF(ctxt, pmic, base, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_PAUSE_HI_MULTIPLIER_ADDR(base), mask, shift, val)
#define PMIO_LPG_CHAN_PAUSE_HI_MULTIPLIER_PAUSE_HI_MULT_BMSK                             0xff
#define PMIO_LPG_CHAN_PAUSE_HI_MULTIPLIER_PAUSE_HI_MULT_SHFT                              0x0

#define PMIO_LPG_CHAN_PAUSE_LO_MULTIPLIER_ADDR(x)                                  ((x) + 0x00000054)
#define PMIO_LPG_CHAN_PAUSE_LO_MULTIPLIER_OFFS                                     0x00000054
#define PMIO_LPG_CHAN_PAUSE_LO_MULTIPLIER_RMSK                                           0xff
#define PMIO_LPG_CHAN_PAUSE_LO_MULTIPLIER_IN(ctxt, pmic, base, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_PAUSE_LO_MULTIPLIER_ADDR(base), PMIO_LPG_CHAN_PAUSE_LO_MULTIPLIER_RMSK, 0, val)
#define PMIO_LPG_CHAN_PAUSE_LO_MULTIPLIER_INF(ctxt, pmic, base, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_PAUSE_LO_MULTIPLIER_ADDR(base), mask, shift, val)
#define PMIO_LPG_CHAN_PAUSE_LO_MULTIPLIER_OUT(ctxt, pmic, base, val)\
        out_pmio(ctxt, pmic, PMIO_LPG_CHAN_PAUSE_LO_MULTIPLIER_ADDR(base), val)
#define PMIO_LPG_CHAN_PAUSE_LO_MULTIPLIER_OUTF(ctxt, pmic, base, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_PAUSE_LO_MULTIPLIER_ADDR(base), mask, shift, val)
#define PMIO_LPG_CHAN_PAUSE_LO_MULTIPLIER_PAUSE_LO_MULT_BMSK                             0xff
#define PMIO_LPG_CHAN_PAUSE_LO_MULTIPLIER_PAUSE_LO_MULT_SHFT                              0x0

#define PMIO_LPG_CHAN_HI_INDEX_ADDR(x)                                             ((x) + 0x00000056)
#define PMIO_LPG_CHAN_HI_INDEX_OFFS                                                0x00000056
#define PMIO_LPG_CHAN_HI_INDEX_RMSK                                                      0x1f
#define PMIO_LPG_CHAN_HI_INDEX_IN(ctxt, pmic, base, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_HI_INDEX_ADDR(base), PMIO_LPG_CHAN_HI_INDEX_RMSK, 0, val)
#define PMIO_LPG_CHAN_HI_INDEX_INF(ctxt, pmic, base, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_HI_INDEX_ADDR(base), mask, shift, val)
#define PMIO_LPG_CHAN_HI_INDEX_OUT(ctxt, pmic, base, val)\
        out_pmio(ctxt, pmic, PMIO_LPG_CHAN_HI_INDEX_ADDR(base), val)
#define PMIO_LPG_CHAN_HI_INDEX_OUTF(ctxt, pmic, base, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_HI_INDEX_ADDR(base), mask, shift, val)
#define PMIO_LPG_CHAN_HI_INDEX_HI_INDEX_BMSK                                             0x1f
#define PMIO_LPG_CHAN_HI_INDEX_HI_INDEX_SHFT                                              0x0

#define PMIO_LPG_CHAN_LO_INDEX_ADDR(x)                                             ((x) + 0x00000057)
#define PMIO_LPG_CHAN_LO_INDEX_OFFS                                                0x00000057
#define PMIO_LPG_CHAN_LO_INDEX_RMSK                                                      0x1f
#define PMIO_LPG_CHAN_LO_INDEX_IN(ctxt, pmic, base, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_LO_INDEX_ADDR(base), PMIO_LPG_CHAN_LO_INDEX_RMSK, 0, val)
#define PMIO_LPG_CHAN_LO_INDEX_INF(ctxt, pmic, base, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_LO_INDEX_ADDR(base), mask, shift, val)
#define PMIO_LPG_CHAN_LO_INDEX_OUT(ctxt, pmic, base, val)\
        out_pmio(ctxt, pmic, PMIO_LPG_CHAN_LO_INDEX_ADDR(base), val)
#define PMIO_LPG_CHAN_LO_INDEX_OUTF(ctxt, pmic, base, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_LO_INDEX_ADDR(base), mask, shift, val)
#define PMIO_LPG_CHAN_LO_INDEX_LO_INDEX_BMSK                                             0x1f
#define PMIO_LPG_CHAN_LO_INDEX_LO_INDEX_SHFT                                              0x0

#define PMIO_LPG_CHAN_SEC_ACCESS_ADDR(x)                                           ((x) + 0x000000d0)
#define PMIO_LPG_CHAN_SEC_ACCESS_OFFS                                              0x000000d0
#define PMIO_LPG_CHAN_SEC_ACCESS_RMSK                                                    0xff
#define PMIO_LPG_CHAN_SEC_ACCESS_IN(ctxt, pmic, base, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_SEC_ACCESS_ADDR(base), PMIO_LPG_CHAN_SEC_ACCESS_RMSK, 0, val)
#define PMIO_LPG_CHAN_SEC_ACCESS_INF(ctxt, pmic, base, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_SEC_ACCESS_ADDR(base), mask, shift, val)
#define PMIO_LPG_CHAN_SEC_ACCESS_OUT(ctxt, pmic, base, val)\
        out_pmio(ctxt, pmic, PMIO_LPG_CHAN_SEC_ACCESS_ADDR(base), val)
#define PMIO_LPG_CHAN_SEC_ACCESS_OUTF(ctxt, pmic, base, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_SEC_ACCESS_ADDR(base), mask, shift, val)
#define PMIO_LPG_CHAN_SEC_ACCESS_SEC_UNLOCK_BMSK                                         0xff
#define PMIO_LPG_CHAN_SEC_ACCESS_SEC_UNLOCK_SHFT                                          0x0

#define PMIO_LPG_CHAN_PERPH_RESET_CTL2_ADDR(x)                                     ((x) + 0x000000d9)
#define PMIO_LPG_CHAN_PERPH_RESET_CTL2_OFFS                                        0x000000d9
#define PMIO_LPG_CHAN_PERPH_RESET_CTL2_RMSK                                               0x1
#define PMIO_LPG_CHAN_PERPH_RESET_CTL2_IN(ctxt, pmic, base, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_PERPH_RESET_CTL2_ADDR(base), PMIO_LPG_CHAN_PERPH_RESET_CTL2_RMSK, 0, val)
#define PMIO_LPG_CHAN_PERPH_RESET_CTL2_INF(ctxt, pmic, base, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_PERPH_RESET_CTL2_ADDR(base), mask, shift, val)
#define PMIO_LPG_CHAN_PERPH_RESET_CTL2_OUT(ctxt, pmic, base, val)\
        out_pmio(ctxt, pmic, PMIO_LPG_CHAN_PERPH_RESET_CTL2_ADDR(base), val)
#define PMIO_LPG_CHAN_PERPH_RESET_CTL2_OUTF(ctxt, pmic, base, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_PERPH_RESET_CTL2_ADDR(base), mask, shift, val)
#define PMIO_LPG_CHAN_PERPH_RESET_CTL2_FOLLOW_GLOBAL_SOFT_RB_BMSK                         0x1
#define PMIO_LPG_CHAN_PERPH_RESET_CTL2_FOLLOW_GLOBAL_SOFT_RB_SHFT                         0x0

#define PMIO_LPG_CHAN_PERPH_RESET_CTL3_ADDR(x)                                     ((x) + 0x000000da)
#define PMIO_LPG_CHAN_PERPH_RESET_CTL3_OFFS                                        0x000000da
#define PMIO_LPG_CHAN_PERPH_RESET_CTL3_RMSK                                               0xf
#define PMIO_LPG_CHAN_PERPH_RESET_CTL3_IN(ctxt, pmic, base, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_PERPH_RESET_CTL3_ADDR(base), PMIO_LPG_CHAN_PERPH_RESET_CTL3_RMSK, 0, val)
#define PMIO_LPG_CHAN_PERPH_RESET_CTL3_INF(ctxt, pmic, base, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_PERPH_RESET_CTL3_ADDR(base), mask, shift, val)
#define PMIO_LPG_CHAN_PERPH_RESET_CTL3_OUT(ctxt, pmic, base, val)\
        out_pmio(ctxt, pmic, PMIO_LPG_CHAN_PERPH_RESET_CTL3_ADDR(base), val)
#define PMIO_LPG_CHAN_PERPH_RESET_CTL3_OUTF(ctxt, pmic, base, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_PERPH_RESET_CTL3_ADDR(base), mask, shift, val)
#define PMIO_LPG_CHAN_PERPH_RESET_CTL3_FOLLOW_OTST2_RB_BMSK                               0x8
#define PMIO_LPG_CHAN_PERPH_RESET_CTL3_FOLLOW_OTST2_RB_SHFT                               0x3
#define PMIO_LPG_CHAN_PERPH_RESET_CTL3_FOLLOW_WARM_RB_BMSK                                0x4
#define PMIO_LPG_CHAN_PERPH_RESET_CTL3_FOLLOW_WARM_RB_SHFT                                0x2
#define PMIO_LPG_CHAN_PERPH_RESET_CTL3_FOLLOW_SHUTDOWN1_RB_BMSK                           0x2
#define PMIO_LPG_CHAN_PERPH_RESET_CTL3_FOLLOW_SHUTDOWN1_RB_SHFT                           0x1
#define PMIO_LPG_CHAN_PERPH_RESET_CTL3_FOLLOW_SHUTDOWN2_RB_BMSK                           0x1
#define PMIO_LPG_CHAN_PERPH_RESET_CTL3_FOLLOW_SHUTDOWN2_RB_SHFT                           0x0

#define PMIO_LPG_CHAN_PERPH_RESET_CTL4_ADDR(x)                                     ((x) + 0x000000db)
#define PMIO_LPG_CHAN_PERPH_RESET_CTL4_OFFS                                        0x000000db
#define PMIO_LPG_CHAN_PERPH_RESET_CTL4_RMSK                                               0x1
#define PMIO_LPG_CHAN_PERPH_RESET_CTL4_IN(ctxt, pmic, base, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_PERPH_RESET_CTL4_ADDR(base), PMIO_LPG_CHAN_PERPH_RESET_CTL4_RMSK, 0, val)
#define PMIO_LPG_CHAN_PERPH_RESET_CTL4_INF(ctxt, pmic, base, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_PERPH_RESET_CTL4_ADDR(base), mask, shift, val)
#define PMIO_LPG_CHAN_PERPH_RESET_CTL4_OUT(ctxt, pmic, base, val)\
        out_pmio(ctxt, pmic, PMIO_LPG_CHAN_PERPH_RESET_CTL4_ADDR(base), val)
#define PMIO_LPG_CHAN_PERPH_RESET_CTL4_OUTF(ctxt, pmic, base, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_PERPH_RESET_CTL4_ADDR(base), mask, shift, val)
#define PMIO_LPG_CHAN_PERPH_RESET_CTL4_LOCAL_SOFT_RESET_BMSK                              0x1
#define PMIO_LPG_CHAN_PERPH_RESET_CTL4_LOCAL_SOFT_RESET_SHFT                              0x0

#define PMIO_LPG_CHAN_INT_TEST1_ADDR(x)                                            ((x) + 0x000000e0)
#define PMIO_LPG_CHAN_INT_TEST1_OFFS                                               0x000000e0
#define PMIO_LPG_CHAN_INT_TEST1_RMSK                                                     0x80
#define PMIO_LPG_CHAN_INT_TEST1_IN(ctxt, pmic, base, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_INT_TEST1_ADDR(base), PMIO_LPG_CHAN_INT_TEST1_RMSK, 0, val)
#define PMIO_LPG_CHAN_INT_TEST1_INF(ctxt, pmic, base, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_INT_TEST1_ADDR(base), mask, shift, val)
#define PMIO_LPG_CHAN_INT_TEST1_OUT(ctxt, pmic, base, val)\
        out_pmio(ctxt, pmic, PMIO_LPG_CHAN_INT_TEST1_ADDR(base), val)
#define PMIO_LPG_CHAN_INT_TEST1_OUTF(ctxt, pmic, base, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_INT_TEST1_ADDR(base), mask, shift, val)
#define PMIO_LPG_CHAN_INT_TEST1_INT_TEST_MODE_EN_BMSK                                    0x80
#define PMIO_LPG_CHAN_INT_TEST1_INT_TEST_MODE_EN_SHFT                                     0x7

#define PMIO_LPG_CHAN_INT_TEST_VAL_ADDR(x)                                         ((x) + 0x000000e1)
#define PMIO_LPG_CHAN_INT_TEST_VAL_OFFS                                            0x000000e1
#define PMIO_LPG_CHAN_INT_TEST_VAL_RMSK                                                   0x1
#define PMIO_LPG_CHAN_INT_TEST_VAL_IN(ctxt, pmic, base, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_INT_TEST_VAL_ADDR(base), PMIO_LPG_CHAN_INT_TEST_VAL_RMSK, 0, val)
#define PMIO_LPG_CHAN_INT_TEST_VAL_INF(ctxt, pmic, base, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_INT_TEST_VAL_ADDR(base), mask, shift, val)
#define PMIO_LPG_CHAN_INT_TEST_VAL_OUT(ctxt, pmic, base, val)\
        out_pmio(ctxt, pmic, PMIO_LPG_CHAN_INT_TEST_VAL_ADDR(base), val)
#define PMIO_LPG_CHAN_INT_TEST_VAL_OUTF(ctxt, pmic, base, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_INT_TEST_VAL_ADDR(base), mask, shift, val)
#define PMIO_LPG_CHAN_INT_TEST_VAL_LPG_INT_TEST_VAL_BMSK                                  0x1
#define PMIO_LPG_CHAN_INT_TEST_VAL_LPG_INT_TEST_VAL_SHFT                                  0x0

#define PMIO_LPG_CHAN_TEST1_ADDR(x)                                                ((x) + 0x000000e2)
#define PMIO_LPG_CHAN_TEST1_OFFS                                                   0x000000e2
#define PMIO_LPG_CHAN_TEST1_RMSK                                                          0x7
#define PMIO_LPG_CHAN_TEST1_IN(ctxt, pmic, base, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_TEST1_ADDR(base), PMIO_LPG_CHAN_TEST1_RMSK, 0, val)
#define PMIO_LPG_CHAN_TEST1_INF(ctxt, pmic, base, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_TEST1_ADDR(base), mask, shift, val)
#define PMIO_LPG_CHAN_TEST1_OUT(ctxt, pmic, base, val)\
        out_pmio(ctxt, pmic, PMIO_LPG_CHAN_TEST1_ADDR(base), val)
#define PMIO_LPG_CHAN_TEST1_OUTF(ctxt, pmic, base, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_TEST1_ADDR(base), mask, shift, val)
#define PMIO_LPG_CHAN_TEST1_DTEST1_BMSK                                                   0x7
#define PMIO_LPG_CHAN_TEST1_DTEST1_SHFT                                                   0x0

#define PMIO_LPG_CHAN_TEST2_ADDR(x)                                                ((x) + 0x000000e3)
#define PMIO_LPG_CHAN_TEST2_OFFS                                                   0x000000e3
#define PMIO_LPG_CHAN_TEST2_RMSK                                                          0x7
#define PMIO_LPG_CHAN_TEST2_IN(ctxt, pmic, base, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_TEST2_ADDR(base), PMIO_LPG_CHAN_TEST2_RMSK, 0, val)
#define PMIO_LPG_CHAN_TEST2_INF(ctxt, pmic, base, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_TEST2_ADDR(base), mask, shift, val)
#define PMIO_LPG_CHAN_TEST2_OUT(ctxt, pmic, base, val)\
        out_pmio(ctxt, pmic, PMIO_LPG_CHAN_TEST2_ADDR(base), val)
#define PMIO_LPG_CHAN_TEST2_OUTF(ctxt, pmic, base, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_TEST2_ADDR(base), mask, shift, val)
#define PMIO_LPG_CHAN_TEST2_DTEST2_BMSK                                                   0x7
#define PMIO_LPG_CHAN_TEST2_DTEST2_SHFT                                                   0x0

#define PMIO_LPG_CHAN_TEST3_ADDR(x)                                                ((x) + 0x000000e4)
#define PMIO_LPG_CHAN_TEST3_OFFS                                                   0x000000e4
#define PMIO_LPG_CHAN_TEST3_RMSK                                                          0x7
#define PMIO_LPG_CHAN_TEST3_IN(ctxt, pmic, base, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_TEST3_ADDR(base), PMIO_LPG_CHAN_TEST3_RMSK, 0, val)
#define PMIO_LPG_CHAN_TEST3_INF(ctxt, pmic, base, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_TEST3_ADDR(base), mask, shift, val)
#define PMIO_LPG_CHAN_TEST3_OUT(ctxt, pmic, base, val)\
        out_pmio(ctxt, pmic, PMIO_LPG_CHAN_TEST3_ADDR(base), val)
#define PMIO_LPG_CHAN_TEST3_OUTF(ctxt, pmic, base, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_TEST3_ADDR(base), mask, shift, val)
#define PMIO_LPG_CHAN_TEST3_DTEST3_BMSK                                                   0x7
#define PMIO_LPG_CHAN_TEST3_DTEST3_SHFT                                                   0x0

#define PMIO_LPG_CHAN_TEST4_ADDR(x)                                                ((x) + 0x000000e5)
#define PMIO_LPG_CHAN_TEST4_OFFS                                                   0x000000e5
#define PMIO_LPG_CHAN_TEST4_RMSK                                                          0x7
#define PMIO_LPG_CHAN_TEST4_IN(ctxt, pmic, base, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_TEST4_ADDR(base), PMIO_LPG_CHAN_TEST4_RMSK, 0, val)
#define PMIO_LPG_CHAN_TEST4_INF(ctxt, pmic, base, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_TEST4_ADDR(base), mask, shift, val)
#define PMIO_LPG_CHAN_TEST4_OUT(ctxt, pmic, base, val)\
        out_pmio(ctxt, pmic, PMIO_LPG_CHAN_TEST4_ADDR(base), val)
#define PMIO_LPG_CHAN_TEST4_OUTF(ctxt, pmic, base, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_LPG_CHAN_TEST4_ADDR(base), mask, shift, val)
#define PMIO_LPG_CHAN_TEST4_DTEST4_BMSK                                                   0x7
#define PMIO_LPG_CHAN_TEST4_DTEST4_SHFT                                                   0x0


#endif /* __PM_LPG_CHAN_REGS_H__ */
