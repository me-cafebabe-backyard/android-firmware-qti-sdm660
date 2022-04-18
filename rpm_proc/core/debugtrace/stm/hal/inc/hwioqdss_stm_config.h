#ifndef __HWIOQDSS_STM_CONFIG_H__
#define __HWIOQDSS_STM_CONFIG_H__
/*
===========================================================================
*/
/**
  @file hwioqdss_stm_config.h
  @brief Auto-generated HWIO interface include file.

  Reference chip release:
    SDM660 (Starlord) [starlord_v1.0_p3q2r83]
 
  This file contains HWIO register definitions for the following modules:
    QDSS_QDSS_CXSTM_8_32_32_TRUE

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

==============================================================================
 $Header: //components/rel/rpm.bf/1.8/core/debugtrace/stm/hal/inc/hwioqdss_stm_config.h#2 $
=========================================================================== */


/*----------------------------------------------------------------------------
 * MODULE: QDSS_QDSS_CXSTM_8_32_32_TRUE
 *--------------------------------------------------------------------------*/

#define QDSS_STM_BASE QDSS_STM_BASE_PTR

#define QDSS_STM_REG_BASE                                                                           (QDSS_STM_BASE)
#define QDSS_STM_REG_BASE_PHYS                                                                      (QDSS_STM_BASE_PHYS + 0x00000000)


#define HWIO_QDSS_STMDMASTARTR_ADDR                            (QDSS_STM_REG_BASE      + 0x00000c04)
#define HWIO_QDSS_STMDMASTARTR_PHYS                            (QDSS_STM_REG_BASE_PHYS + 0x00000c04)
#define HWIO_QDSS_STMDMASTARTR_RMSK                                   0x1
#define HWIO_QDSS_STMDMASTARTR_OUT(v)      \
        out_dword(HWIO_QDSS_STMDMASTARTR_ADDR,v)
#define HWIO_QDSS_STMDMASTARTR_START_BMSK                             0x1
#define HWIO_QDSS_STMDMASTARTR_START_SHFT                             0x0
#define HWIO_QDSS_STMDMASTARTR_START_START_FVAL                       0x1

#define HWIO_QDSS_STMDMASTOPR_ADDR                             (QDSS_STM_REG_BASE      + 0x00000c08)
#define HWIO_QDSS_STMDMASTOPR_PHYS                             (QDSS_STM_REG_BASE_PHYS + 0x00000c08)
#define HWIO_QDSS_STMDMASTOPR_RMSK                                    0x1
#define HWIO_QDSS_STMDMASTOPR_OUT(v)      \
        out_dword(HWIO_QDSS_STMDMASTOPR_ADDR,v)
#define HWIO_QDSS_STMDMASTOPR_STOP_BMSK                               0x1
#define HWIO_QDSS_STMDMASTOPR_STOP_SHFT                               0x0
#define HWIO_QDSS_STMDMASTOPR_STOP_STOP_FVAL                          0x1

#define HWIO_QDSS_STMDMASTATR_ADDR                             (QDSS_STM_REG_BASE      + 0x00000c0c)
#define HWIO_QDSS_STMDMASTATR_PHYS                             (QDSS_STM_REG_BASE_PHYS + 0x00000c0c)
#define HWIO_QDSS_STMDMASTATR_RMSK                                    0x1
#define HWIO_QDSS_STMDMASTATR_IN          \
        in_dword_masked(HWIO_QDSS_STMDMASTATR_ADDR, HWIO_QDSS_STMDMASTATR_RMSK)
#define HWIO_QDSS_STMDMASTATR_INM(m)      \
        in_dword_masked(HWIO_QDSS_STMDMASTATR_ADDR, m)
#define HWIO_QDSS_STMDMASTATR_STATUS_BMSK                             0x1
#define HWIO_QDSS_STMDMASTATR_STATUS_SHFT                             0x0
#define HWIO_QDSS_STMDMASTATR_STATUS_IDLE_FVAL                        0x0
#define HWIO_QDSS_STMDMASTATR_STATUS_ACTIVE_FVAL                      0x1

#define HWIO_QDSS_STMDMACTLR_ADDR                              (QDSS_STM_REG_BASE      + 0x00000c10)
#define HWIO_QDSS_STMDMACTLR_PHYS                              (QDSS_STM_REG_BASE_PHYS + 0x00000c10)
#define HWIO_QDSS_STMDMACTLR_RMSK                                     0xc
#define HWIO_QDSS_STMDMACTLR_IN          \
        in_dword_masked(HWIO_QDSS_STMDMACTLR_ADDR, HWIO_QDSS_STMDMACTLR_RMSK)
#define HWIO_QDSS_STMDMACTLR_INM(m)      \
        in_dword_masked(HWIO_QDSS_STMDMACTLR_ADDR, m)
#define HWIO_QDSS_STMDMACTLR_OUT(v)      \
        out_dword(HWIO_QDSS_STMDMACTLR_ADDR,v)
#define HWIO_QDSS_STMDMACTLR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QDSS_STMDMACTLR_ADDR,m,v,HWIO_QDSS_STMDMACTLR_IN)
#define HWIO_QDSS_STMDMACTLR_SENS_BMSK                                0xc
#define HWIO_QDSS_STMDMACTLR_SENS_SHFT                                0x2
#define HWIO_QDSS_STMDMACTLR_SENS_EMPTY_FVAL                          0x0
#define HWIO_QDSS_STMDMACTLR_SENS_ENUM_25_FVAL                        0x1
#define HWIO_QDSS_STMDMACTLR_SENS_ENUM_50_FVAL                        0x2
#define HWIO_QDSS_STMDMACTLR_SENS_ENUM_75_FVAL                        0x3

#define HWIO_QDSS_STMDMAIDR_ADDR                               (QDSS_STM_REG_BASE      + 0x00000cfc)
#define HWIO_QDSS_STMDMAIDR_PHYS                               (QDSS_STM_REG_BASE_PHYS + 0x00000cfc)
#define HWIO_QDSS_STMDMAIDR_RMSK                                    0xfff
#define HWIO_QDSS_STMDMAIDR_IN          \
        in_dword_masked(HWIO_QDSS_STMDMAIDR_ADDR, HWIO_QDSS_STMDMAIDR_RMSK)
#define HWIO_QDSS_STMDMAIDR_INM(m)      \
        in_dword_masked(HWIO_QDSS_STMDMAIDR_ADDR, m)
#define HWIO_QDSS_STMDMAIDR_VENDSPEC_BMSK                           0xf00
#define HWIO_QDSS_STMDMAIDR_VENDSPEC_SHFT                             0x8
#define HWIO_QDSS_STMDMAIDR_VENDSPEC_VENDSPEC_FVAL                    0x0
#define HWIO_QDSS_STMDMAIDR_CLASSREV_BMSK                            0xf0
#define HWIO_QDSS_STMDMAIDR_CLASSREV_SHFT                             0x4
#define HWIO_QDSS_STMDMAIDR_CLASSREV_REVISION_CONTROL_FVAL            0x0
#define HWIO_QDSS_STMDMAIDR_CLASS_BMSK                                0xf
#define HWIO_QDSS_STMDMAIDR_CLASS_SHFT                                0x0
#define HWIO_QDSS_STMDMAIDR_CLASS_CONTROL_FVAL                        0x2

#define HWIO_QDSS_STMHEER_ADDR                                 (QDSS_STM_REG_BASE      + 0x00000d00)
#define HWIO_QDSS_STMHEER_PHYS                                 (QDSS_STM_REG_BASE_PHYS + 0x00000d00)
#define HWIO_QDSS_STMHEER_RMSK                                 0xffffffff
#define HWIO_QDSS_STMHEER_IN          \
        in_dword_masked(HWIO_QDSS_STMHEER_ADDR, HWIO_QDSS_STMHEER_RMSK)
#define HWIO_QDSS_STMHEER_INM(m)      \
        in_dword_masked(HWIO_QDSS_STMHEER_ADDR, m)
#define HWIO_QDSS_STMHEER_OUT(v)      \
        out_dword(HWIO_QDSS_STMHEER_ADDR,v)
#define HWIO_QDSS_STMHEER_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QDSS_STMHEER_ADDR,m,v,HWIO_QDSS_STMHEER_IN)
#define HWIO_QDSS_STMHEER_HEE_BMSK                             0xffffffff
#define HWIO_QDSS_STMHEER_HEE_SHFT                                    0x0

#define HWIO_QDSS_STMHETER_ADDR                                (QDSS_STM_REG_BASE      + 0x00000d20)
#define HWIO_QDSS_STMHETER_PHYS                                (QDSS_STM_REG_BASE_PHYS + 0x00000d20)
#define HWIO_QDSS_STMHETER_RMSK                                0xffffffff
#define HWIO_QDSS_STMHETER_IN          \
        in_dword_masked(HWIO_QDSS_STMHETER_ADDR, HWIO_QDSS_STMHETER_RMSK)
#define HWIO_QDSS_STMHETER_INM(m)      \
        in_dword_masked(HWIO_QDSS_STMHETER_ADDR, m)
#define HWIO_QDSS_STMHETER_OUT(v)      \
        out_dword(HWIO_QDSS_STMHETER_ADDR,v)
#define HWIO_QDSS_STMHETER_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QDSS_STMHETER_ADDR,m,v,HWIO_QDSS_STMHETER_IN)
#define HWIO_QDSS_STMHETER_HETE_BMSK                           0xffffffff
#define HWIO_QDSS_STMHETER_HETE_SHFT                                  0x0

#define HWIO_QDSS_STMHEMCR_ADDR                                (QDSS_STM_REG_BASE      + 0x00000d64)
#define HWIO_QDSS_STMHEMCR_PHYS                                (QDSS_STM_REG_BASE_PHYS + 0x00000d64)
#define HWIO_QDSS_STMHEMCR_RMSK                                      0xf7
#define HWIO_QDSS_STMHEMCR_IN          \
        in_dword_masked(HWIO_QDSS_STMHEMCR_ADDR, HWIO_QDSS_STMHEMCR_RMSK)
#define HWIO_QDSS_STMHEMCR_INM(m)      \
        in_dword_masked(HWIO_QDSS_STMHEMCR_ADDR, m)
#define HWIO_QDSS_STMHEMCR_OUT(v)      \
        out_dword(HWIO_QDSS_STMHEMCR_ADDR,v)
#define HWIO_QDSS_STMHEMCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QDSS_STMHEMCR_ADDR,m,v,HWIO_QDSS_STMHEMCR_IN)
#define HWIO_QDSS_STMHEMCR_ATBTRIGEN_BMSK                            0x80
#define HWIO_QDSS_STMHEMCR_ATBTRIGEN_SHFT                             0x7
#define HWIO_QDSS_STMHEMCR_ATBTRIGEN_DISABLE_FVAL                     0x0
#define HWIO_QDSS_STMHEMCR_ATBTRIGEN_ENABLE_FVAL                      0x1
#define HWIO_QDSS_STMHEMCR_TRIGCLEAR_BMSK                            0x40
#define HWIO_QDSS_STMHEMCR_TRIGCLEAR_SHFT                             0x6
#define HWIO_QDSS_STMHEMCR_TRIGCLEAR_NO_EFFECT_FVAL                   0x0
#define HWIO_QDSS_STMHEMCR_TRIGCLEAR_CLEAR_FVAL                       0x1
#define HWIO_QDSS_STMHEMCR_TRIGSTATUS_BMSK                           0x20
#define HWIO_QDSS_STMHEMCR_TRIGSTATUS_SHFT                            0x5
#define HWIO_QDSS_STMHEMCR_TRIGSTATUS_NOT_OCCURRED_FVAL               0x0
#define HWIO_QDSS_STMHEMCR_TRIGSTATUS_OCCURRED_FVAL                   0x1
#define HWIO_QDSS_STMHEMCR_TRIGCTL_BMSK                              0x10
#define HWIO_QDSS_STMHEMCR_TRIGCTL_SHFT                               0x4
#define HWIO_QDSS_STMHEMCR_TRIGCTL_MULTI_SHOT_FVAL                    0x0
#define HWIO_QDSS_STMHEMCR_TRIGCTL_SINGLE_SHOT_FVAL                   0x1
#define HWIO_QDSS_STMHEMCR_ERRDETECT_BMSK                             0x4
#define HWIO_QDSS_STMHEMCR_ERRDETECT_SHFT                             0x2
#define HWIO_QDSS_STMHEMCR_ERRDETECT_DISABLE_FVAL                     0x0
#define HWIO_QDSS_STMHEMCR_ERRDETECT_ENABLE_FVAL                      0x1
#define HWIO_QDSS_STMHEMCR_COMPEN_BMSK                                0x2
#define HWIO_QDSS_STMHEMCR_COMPEN_SHFT                                0x1
#define HWIO_QDSS_STMHEMCR_COMPEN_DISABLE_FVAL                        0x0
#define HWIO_QDSS_STMHEMCR_COMPEN_ENABLE_FVAL                         0x1
#define HWIO_QDSS_STMHEMCR_EN_BMSK                                    0x1
#define HWIO_QDSS_STMHEMCR_EN_SHFT                                    0x0
#define HWIO_QDSS_STMHEMCR_EN_DISABLE_FVAL                            0x0
#define HWIO_QDSS_STMHEMCR_EN_ENABLE_FVAL                             0x1

#define HWIO_QDSS_STMHEMASTR_ADDR                              (QDSS_STM_REG_BASE      + 0x00000df4)
#define HWIO_QDSS_STMHEMASTR_PHYS                              (QDSS_STM_REG_BASE_PHYS + 0x00000df4)
#define HWIO_QDSS_STMHEMASTR_RMSK                                  0xffff
#define HWIO_QDSS_STMHEMASTR_IN          \
        in_dword_masked(HWIO_QDSS_STMHEMASTR_ADDR, HWIO_QDSS_STMHEMASTR_RMSK)
#define HWIO_QDSS_STMHEMASTR_INM(m)      \
        in_dword_masked(HWIO_QDSS_STMHEMASTR_ADDR, m)
#define HWIO_QDSS_STMHEMASTR_MASTER_BMSK                           0xffff
#define HWIO_QDSS_STMHEMASTR_MASTER_SHFT                              0x0
#define HWIO_QDSS_STMHEMASTR_MASTER_MASTER_1_FVAL                    0x80

#define HWIO_QDSS_STMHEFEAT1R_ADDR                             (QDSS_STM_REG_BASE      + 0x00000df8)
#define HWIO_QDSS_STMHEFEAT1R_PHYS                             (QDSS_STM_REG_BASE_PHYS + 0x00000df8)
#define HWIO_QDSS_STMHEFEAT1R_RMSK                               0xff803d
#define HWIO_QDSS_STMHEFEAT1R_IN          \
        in_dword_masked(HWIO_QDSS_STMHEFEAT1R_ADDR, HWIO_QDSS_STMHEFEAT1R_RMSK)
#define HWIO_QDSS_STMHEFEAT1R_INM(m)      \
        in_dword_masked(HWIO_QDSS_STMHEFEAT1R_ADDR, m)
#define HWIO_QDSS_STMHEFEAT1R_NUMHE_BMSK                         0xff8000
#define HWIO_QDSS_STMHEFEAT1R_NUMHE_SHFT                              0xf
#define HWIO_QDSS_STMHEFEAT1R_NUMHE_EVENTS_FVAL                      0x20
#define HWIO_QDSS_STMHEFEAT1R_HECOMP_BMSK                            0x30
#define HWIO_QDSS_STMHEFEAT1R_HECOMP_SHFT                             0x4
#define HWIO_QDSS_STMHEFEAT1R_HECOMP_RO_FVAL                          0x3
#define HWIO_QDSS_STMHEFEAT1R_HEMASTR_BMSK                            0x8
#define HWIO_QDSS_STMHEFEAT1R_HEMASTR_SHFT                            0x3
#define HWIO_QDSS_STMHEFEAT1R_HEMASTR_RO_FVAL                         0x0
#define HWIO_QDSS_STMHEFEAT1R_HEERR_BMSK                              0x4
#define HWIO_QDSS_STMHEFEAT1R_HEERR_SHFT                              0x2
#define HWIO_QDSS_STMHEFEAT1R_HEERR_IMPLEMENTED_FVAL                  0x1
#define HWIO_QDSS_STMHEFEAT1R_HETER_BMSK                              0x1
#define HWIO_QDSS_STMHEFEAT1R_HETER_SHFT                              0x0
#define HWIO_QDSS_STMHEFEAT1R_HETER_IMPLEMENTED_FVAL                  0x1

#define HWIO_QDSS_STMHEIDR_ADDR                                (QDSS_STM_REG_BASE      + 0x00000dfc)
#define HWIO_QDSS_STMHEIDR_PHYS                                (QDSS_STM_REG_BASE_PHYS + 0x00000dfc)
#define HWIO_QDSS_STMHEIDR_RMSK                                     0xfff
#define HWIO_QDSS_STMHEIDR_IN          \
        in_dword_masked(HWIO_QDSS_STMHEIDR_ADDR, HWIO_QDSS_STMHEIDR_RMSK)
#define HWIO_QDSS_STMHEIDR_INM(m)      \
        in_dword_masked(HWIO_QDSS_STMHEIDR_ADDR, m)
#define HWIO_QDSS_STMHEIDR_VENDSPEC_BMSK                            0xf00
#define HWIO_QDSS_STMHEIDR_VENDSPEC_SHFT                              0x8
#define HWIO_QDSS_STMHEIDR_VENDSPEC_VENDSPEC_FVAL                     0x0
#define HWIO_QDSS_STMHEIDR_CLASSREV_BMSK                             0xf0
#define HWIO_QDSS_STMHEIDR_CLASSREV_SHFT                              0x4
#define HWIO_QDSS_STMHEIDR_CLASSREV_REVISION_CONTROL_FVAL             0x0
#define HWIO_QDSS_STMHEIDR_CLASS_BMSK                                 0xf
#define HWIO_QDSS_STMHEIDR_CLASS_SHFT                                 0x0
#define HWIO_QDSS_STMHEIDR_CLASS_CONTROL_FVAL                         0x1

#define HWIO_QDSS_STMSPER_ADDR                                 (QDSS_STM_REG_BASE      + 0x00000e00)
#define HWIO_QDSS_STMSPER_PHYS                                 (QDSS_STM_REG_BASE_PHYS + 0x00000e00)
#define HWIO_QDSS_STMSPER_RMSK                                 0xffffffff
#define HWIO_QDSS_STMSPER_IN          \
        in_dword_masked(HWIO_QDSS_STMSPER_ADDR, HWIO_QDSS_STMSPER_RMSK)
#define HWIO_QDSS_STMSPER_INM(m)      \
        in_dword_masked(HWIO_QDSS_STMSPER_ADDR, m)
#define HWIO_QDSS_STMSPER_OUT(v)      \
        out_dword(HWIO_QDSS_STMSPER_ADDR,v)
#define HWIO_QDSS_STMSPER_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QDSS_STMSPER_ADDR,m,v,HWIO_QDSS_STMSPER_IN)
#define HWIO_QDSS_STMSPER_SPE_BMSK                             0xffffffff
#define HWIO_QDSS_STMSPER_SPE_SHFT                                    0x0

#define HWIO_QDSS_STMSPTER_ADDR                                (QDSS_STM_REG_BASE      + 0x00000e20)
#define HWIO_QDSS_STMSPTER_PHYS                                (QDSS_STM_REG_BASE_PHYS + 0x00000e20)
#define HWIO_QDSS_STMSPTER_RMSK                                0xffffffff
#define HWIO_QDSS_STMSPTER_IN          \
        in_dword_masked(HWIO_QDSS_STMSPTER_ADDR, HWIO_QDSS_STMSPTER_RMSK)
#define HWIO_QDSS_STMSPTER_INM(m)      \
        in_dword_masked(HWIO_QDSS_STMSPTER_ADDR, m)
#define HWIO_QDSS_STMSPTER_OUT(v)      \
        out_dword(HWIO_QDSS_STMSPTER_ADDR,v)
#define HWIO_QDSS_STMSPTER_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QDSS_STMSPTER_ADDR,m,v,HWIO_QDSS_STMSPTER_IN)
#define HWIO_QDSS_STMSPTER_SPTE_BMSK                           0xffffffff
#define HWIO_QDSS_STMSPTER_SPTE_SHFT                                  0x0

#define HWIO_QDSS_STMSPSCR_ADDR                                (QDSS_STM_REG_BASE      + 0x00000e60)
#define HWIO_QDSS_STMSPSCR_PHYS                                (QDSS_STM_REG_BASE_PHYS + 0x00000e60)
#define HWIO_QDSS_STMSPSCR_RMSK                                0xfff00003
#define HWIO_QDSS_STMSPSCR_IN          \
        in_dword_masked(HWIO_QDSS_STMSPSCR_ADDR, HWIO_QDSS_STMSPSCR_RMSK)
#define HWIO_QDSS_STMSPSCR_INM(m)      \
        in_dword_masked(HWIO_QDSS_STMSPSCR_ADDR, m)
#define HWIO_QDSS_STMSPSCR_OUT(v)      \
        out_dword(HWIO_QDSS_STMSPSCR_ADDR,v)
#define HWIO_QDSS_STMSPSCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QDSS_STMSPSCR_ADDR,m,v,HWIO_QDSS_STMSPSCR_IN)
#define HWIO_QDSS_STMSPSCR_PORTSEL_BMSK                        0xfff00000
#define HWIO_QDSS_STMSPSCR_PORTSEL_SHFT                              0x14
#define HWIO_QDSS_STMSPSCR_PORTCTL_BMSK                               0x3
#define HWIO_QDSS_STMSPSCR_PORTCTL_SHFT                               0x0
#define HWIO_QDSS_STMSPSCR_PORTCTL_NOT_USED_FVAL                      0x0
#define HWIO_QDSS_STMSPSCR_PORTCTL_STMSPTER_ONLY_FVAL                 0x1
#define HWIO_QDSS_STMSPSCR_PORTCTL_RESERVED_FVAL                      0x2
#define HWIO_QDSS_STMSPSCR_PORTCTL_STMSPER_AND_STMSPTER_FVAL          0x3

#define HWIO_QDSS_STMSPMSCR_ADDR                               (QDSS_STM_REG_BASE      + 0x00000e64)
#define HWIO_QDSS_STMSPMSCR_PHYS                               (QDSS_STM_REG_BASE_PHYS + 0x00000e64)
#define HWIO_QDSS_STMSPMSCR_RMSK                                 0x7f8001
#define HWIO_QDSS_STMSPMSCR_IN          \
        in_dword_masked(HWIO_QDSS_STMSPMSCR_ADDR, HWIO_QDSS_STMSPMSCR_RMSK)
#define HWIO_QDSS_STMSPMSCR_INM(m)      \
        in_dword_masked(HWIO_QDSS_STMSPMSCR_ADDR, m)
#define HWIO_QDSS_STMSPMSCR_OUT(v)      \
        out_dword(HWIO_QDSS_STMSPMSCR_ADDR,v)
#define HWIO_QDSS_STMSPMSCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QDSS_STMSPMSCR_ADDR,m,v,HWIO_QDSS_STMSPMSCR_IN)
#define HWIO_QDSS_STMSPMSCR_MASTSEL_BMSK                         0x7f8000
#define HWIO_QDSS_STMSPMSCR_MASTSEL_SHFT                              0xf
#define HWIO_QDSS_STMSPMSCR_MASTCTL_BMSK                              0x1
#define HWIO_QDSS_STMSPMSCR_MASTCTL_SHFT                              0x0
#define HWIO_QDSS_STMSPMSCR_MASTCTL_NOT_USED_FVAL                     0x0
#define HWIO_QDSS_STMSPMSCR_MASTCTL_STMSPSCR_FVAL                     0x1

#define HWIO_QDSS_STMSPOVERRIDER_ADDR                          (QDSS_STM_REG_BASE      + 0x00000e68)
#define HWIO_QDSS_STMSPOVERRIDER_PHYS                          (QDSS_STM_REG_BASE_PHYS + 0x00000e68)
#define HWIO_QDSS_STMSPOVERRIDER_RMSK                          0xffff8007
#define HWIO_QDSS_STMSPOVERRIDER_IN          \
        in_dword_masked(HWIO_QDSS_STMSPOVERRIDER_ADDR, HWIO_QDSS_STMSPOVERRIDER_RMSK)
#define HWIO_QDSS_STMSPOVERRIDER_INM(m)      \
        in_dword_masked(HWIO_QDSS_STMSPOVERRIDER_ADDR, m)
#define HWIO_QDSS_STMSPOVERRIDER_OUT(v)      \
        out_dword(HWIO_QDSS_STMSPOVERRIDER_ADDR,v)
#define HWIO_QDSS_STMSPOVERRIDER_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QDSS_STMSPOVERRIDER_ADDR,m,v,HWIO_QDSS_STMSPOVERRIDER_IN)
#define HWIO_QDSS_STMSPOVERRIDER_PORTSEL_BMSK                  0xffff8000
#define HWIO_QDSS_STMSPOVERRIDER_PORTSEL_SHFT                         0xf
#define HWIO_QDSS_STMSPOVERRIDER_OVERTS_BMSK                          0x4
#define HWIO_QDSS_STMSPOVERRIDER_OVERTS_SHFT                          0x2
#define HWIO_QDSS_STMSPOVERRIDER_OVERTS_DISABLED_FVAL                 0x0
#define HWIO_QDSS_STMSPOVERRIDER_OVERTS_ENABLED_FVAL                  0x1
#define HWIO_QDSS_STMSPOVERRIDER_OVERCTL_BMSK                         0x3
#define HWIO_QDSS_STMSPOVERRIDER_OVERCTL_SHFT                         0x0
#define HWIO_QDSS_STMSPOVERRIDER_OVERCTL_DISABLED_FVAL                0x0
#define HWIO_QDSS_STMSPOVERRIDER_OVERCTL_GUARANTEED_FVAL              0x1
#define HWIO_QDSS_STMSPOVERRIDER_OVERCTL_INVARIANT_TIMING_FVAL        0x2
#define HWIO_QDSS_STMSPOVERRIDER_OVERCTL_RESERVED_FVAL                0x3

#define HWIO_QDSS_STMSPMOVERRIDER_ADDR                         (QDSS_STM_REG_BASE      + 0x00000e6c)
#define HWIO_QDSS_STMSPMOVERRIDER_PHYS                         (QDSS_STM_REG_BASE_PHYS + 0x00000e6c)
#define HWIO_QDSS_STMSPMOVERRIDER_RMSK                           0x7f8001
#define HWIO_QDSS_STMSPMOVERRIDER_IN          \
        in_dword_masked(HWIO_QDSS_STMSPMOVERRIDER_ADDR, HWIO_QDSS_STMSPMOVERRIDER_RMSK)
#define HWIO_QDSS_STMSPMOVERRIDER_INM(m)      \
        in_dword_masked(HWIO_QDSS_STMSPMOVERRIDER_ADDR, m)
#define HWIO_QDSS_STMSPMOVERRIDER_OUT(v)      \
        out_dword(HWIO_QDSS_STMSPMOVERRIDER_ADDR,v)
#define HWIO_QDSS_STMSPMOVERRIDER_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QDSS_STMSPMOVERRIDER_ADDR,m,v,HWIO_QDSS_STMSPMOVERRIDER_IN)
#define HWIO_QDSS_STMSPMOVERRIDER_MASTSEL_BMSK                   0x7f8000
#define HWIO_QDSS_STMSPMOVERRIDER_MASTSEL_SHFT                        0xf
#define HWIO_QDSS_STMSPMOVERRIDER_MASTCTL_BMSK                        0x1
#define HWIO_QDSS_STMSPMOVERRIDER_MASTCTL_SHFT                        0x0
#define HWIO_QDSS_STMSPMOVERRIDER_MASTCTL_DISABLED_FVAL               0x0
#define HWIO_QDSS_STMSPMOVERRIDER_MASTCTL_ENABLED_FVAL                0x1

#define HWIO_QDSS_STMSPTRIGCSR_ADDR                            (QDSS_STM_REG_BASE      + 0x00000e70)
#define HWIO_QDSS_STMSPTRIGCSR_PHYS                            (QDSS_STM_REG_BASE_PHYS + 0x00000e70)
#define HWIO_QDSS_STMSPTRIGCSR_RMSK                                  0x1f
#define HWIO_QDSS_STMSPTRIGCSR_IN          \
        in_dword_masked(HWIO_QDSS_STMSPTRIGCSR_ADDR, HWIO_QDSS_STMSPTRIGCSR_RMSK)
#define HWIO_QDSS_STMSPTRIGCSR_INM(m)      \
        in_dword_masked(HWIO_QDSS_STMSPTRIGCSR_ADDR, m)
#define HWIO_QDSS_STMSPTRIGCSR_OUT(v)      \
        out_dword(HWIO_QDSS_STMSPTRIGCSR_ADDR,v)
#define HWIO_QDSS_STMSPTRIGCSR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QDSS_STMSPTRIGCSR_ADDR,m,v,HWIO_QDSS_STMSPTRIGCSR_IN)
#define HWIO_QDSS_STMSPTRIGCSR_ATBTRIGEN_DIR_BMSK                    0x10
#define HWIO_QDSS_STMSPTRIGCSR_ATBTRIGEN_DIR_SHFT                     0x4
#define HWIO_QDSS_STMSPTRIGCSR_ATBTRIGEN_DIR_DISABLE_FVAL             0x0
#define HWIO_QDSS_STMSPTRIGCSR_ATBTRIGEN_DIR_ENABLE_FVAL              0x1
#define HWIO_QDSS_STMSPTRIGCSR_ATBTRIGEN_TE_BMSK                      0x8
#define HWIO_QDSS_STMSPTRIGCSR_ATBTRIGEN_TE_SHFT                      0x3
#define HWIO_QDSS_STMSPTRIGCSR_ATBTRIGEN_TE_DISABLE_FVAL              0x0
#define HWIO_QDSS_STMSPTRIGCSR_ATBTRIGEN_TE_ENABLE_FVAL               0x1
#define HWIO_QDSS_STMSPTRIGCSR_TRIGCLEAR_BMSK                         0x4
#define HWIO_QDSS_STMSPTRIGCSR_TRIGCLEAR_SHFT                         0x2
#define HWIO_QDSS_STMSPTRIGCSR_TRIGCLEAR_NO_EFFECT_FVAL               0x0
#define HWIO_QDSS_STMSPTRIGCSR_TRIGCLEAR_CLEAR_FVAL                   0x1
#define HWIO_QDSS_STMSPTRIGCSR_TRIGSTATUS_BMSK                        0x2
#define HWIO_QDSS_STMSPTRIGCSR_TRIGSTATUS_SHFT                        0x1
#define HWIO_QDSS_STMSPTRIGCSR_TRIGSTATUS_NOT_OCCURRED_FVAL           0x0
#define HWIO_QDSS_STMSPTRIGCSR_TRIGSTATUS_OCCURRED_FVAL               0x1
#define HWIO_QDSS_STMSPTRIGCSR_TRIGCTL_BMSK                           0x1
#define HWIO_QDSS_STMSPTRIGCSR_TRIGCTL_SHFT                           0x0
#define HWIO_QDSS_STMSPTRIGCSR_TRIGCTL_MULTI_SHOT_FVAL                0x0
#define HWIO_QDSS_STMSPTRIGCSR_TRIGCTL_SINGLE_SHOT_FVAL               0x1

#define HWIO_QDSS_STMTCSR_ADDR                                 (QDSS_STM_REG_BASE      + 0x00000e80)
#define HWIO_QDSS_STMTCSR_PHYS                                 (QDSS_STM_REG_BASE_PHYS + 0x00000e80)
#define HWIO_QDSS_STMTCSR_RMSK                                   0xff0027
#define HWIO_QDSS_STMTCSR_IN          \
        in_dword_masked(HWIO_QDSS_STMTCSR_ADDR, HWIO_QDSS_STMTCSR_RMSK)
#define HWIO_QDSS_STMTCSR_INM(m)      \
        in_dword_masked(HWIO_QDSS_STMTCSR_ADDR, m)
#define HWIO_QDSS_STMTCSR_OUT(v)      \
        out_dword(HWIO_QDSS_STMTCSR_ADDR,v)
#define HWIO_QDSS_STMTCSR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QDSS_STMTCSR_ADDR,m,v,HWIO_QDSS_STMTCSR_IN)
#define HWIO_QDSS_STMTCSR_BUSY_BMSK                              0x800000
#define HWIO_QDSS_STMTCSR_BUSY_SHFT                                  0x17
#define HWIO_QDSS_STMTCSR_BUSY_IDLE_FVAL                              0x0
#define HWIO_QDSS_STMTCSR_BUSY_BUSY_FVAL                              0x1
#define HWIO_QDSS_STMTCSR_TRACEID_BMSK                           0x7f0000
#define HWIO_QDSS_STMTCSR_TRACEID_SHFT                               0x10
#define HWIO_QDSS_STMTCSR_COMPEN_BMSK                                0x20
#define HWIO_QDSS_STMTCSR_COMPEN_SHFT                                 0x5
#define HWIO_QDSS_STMTCSR_COMPEN_DISABLED_FVAL                        0x0
#define HWIO_QDSS_STMTCSR_COMPEN_ENABLED_FVAL                         0x1
#define HWIO_QDSS_STMTCSR_SYNCEN_BMSK                                 0x4
#define HWIO_QDSS_STMTCSR_SYNCEN_SHFT                                 0x2
#define HWIO_QDSS_STMTCSR_SYNCEN_RAO_FVAL                             0x1
#define HWIO_QDSS_STMTCSR_TSEN_BMSK                                   0x2
#define HWIO_QDSS_STMTCSR_TSEN_SHFT                                   0x1
#define HWIO_QDSS_STMTCSR_TSEN_DISABLE_FVAL                           0x0
#define HWIO_QDSS_STMTCSR_TSEN_ENABLE_FVAL                            0x1
#define HWIO_QDSS_STMTCSR_EN_BMSK                                     0x1
#define HWIO_QDSS_STMTCSR_EN_SHFT                                     0x0
#define HWIO_QDSS_STMTCSR_EN_DISABLE_FVAL                             0x0
#define HWIO_QDSS_STMTCSR_EN_ENABLE_FVAL                              0x1

#define HWIO_QDSS_STMTSSTIMR_ADDR                              (QDSS_STM_REG_BASE      + 0x00000e84)
#define HWIO_QDSS_STMTSSTIMR_PHYS                              (QDSS_STM_REG_BASE_PHYS + 0x00000e84)
#define HWIO_QDSS_STMTSSTIMR_RMSK                                     0x1
#define HWIO_QDSS_STMTSSTIMR_OUT(v)      \
        out_dword(HWIO_QDSS_STMTSSTIMR_ADDR,v)
#define HWIO_QDSS_STMTSSTIMR_FORCETS_BMSK                             0x1
#define HWIO_QDSS_STMTSSTIMR_FORCETS_SHFT                             0x0
#define HWIO_QDSS_STMTSSTIMR_FORCETS_FORCETS_FVAL                     0x1

#define HWIO_QDSS_STMTSFREQR_ADDR                              (QDSS_STM_REG_BASE      + 0x00000e8c)
#define HWIO_QDSS_STMTSFREQR_PHYS                              (QDSS_STM_REG_BASE_PHYS + 0x00000e8c)
#define HWIO_QDSS_STMTSFREQR_RMSK                              0xffffffff
#define HWIO_QDSS_STMTSFREQR_IN          \
        in_dword_masked(HWIO_QDSS_STMTSFREQR_ADDR, HWIO_QDSS_STMTSFREQR_RMSK)
#define HWIO_QDSS_STMTSFREQR_INM(m)      \
        in_dword_masked(HWIO_QDSS_STMTSFREQR_ADDR, m)
#define HWIO_QDSS_STMTSFREQR_OUT(v)      \
        out_dword(HWIO_QDSS_STMTSFREQR_ADDR,v)
#define HWIO_QDSS_STMTSFREQR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QDSS_STMTSFREQR_ADDR,m,v,HWIO_QDSS_STMTSFREQR_IN)
#define HWIO_QDSS_STMTSFREQR_FREQ_BMSK                         0xffffffff
#define HWIO_QDSS_STMTSFREQR_FREQ_SHFT                                0x0

#define HWIO_QDSS_STMSYNCR_ADDR                                (QDSS_STM_REG_BASE      + 0x00000e90)
#define HWIO_QDSS_STMSYNCR_PHYS                                (QDSS_STM_REG_BASE_PHYS + 0x00000e90)
#define HWIO_QDSS_STMSYNCR_RMSK                                    0x1ffc
#define HWIO_QDSS_STMSYNCR_IN          \
        in_dword_masked(HWIO_QDSS_STMSYNCR_ADDR, HWIO_QDSS_STMSYNCR_RMSK)
#define HWIO_QDSS_STMSYNCR_INM(m)      \
        in_dword_masked(HWIO_QDSS_STMSYNCR_ADDR, m)
#define HWIO_QDSS_STMSYNCR_OUT(v)      \
        out_dword(HWIO_QDSS_STMSYNCR_ADDR,v)
#define HWIO_QDSS_STMSYNCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QDSS_STMSYNCR_ADDR,m,v,HWIO_QDSS_STMSYNCR_IN)
#define HWIO_QDSS_STMSYNCR_MODE_BMSK                               0x1000
#define HWIO_QDSS_STMSYNCR_MODE_SHFT                                  0xc
#define HWIO_QDSS_STMSYNCR_MODE_N_BYTES_FVAL                          0x0
#define HWIO_QDSS_STMSYNCR_MODE_ENUM_2_N_BYTES_FVAL                   0x1
#define HWIO_QDSS_STMSYNCR_COUNT_BMSK                               0xffc
#define HWIO_QDSS_STMSYNCR_COUNT_SHFT                                 0x2

#define HWIO_QDSS_STMAUXCR_ADDR                                (QDSS_STM_REG_BASE      + 0x00000e94)
#define HWIO_QDSS_STMAUXCR_PHYS                                (QDSS_STM_REG_BASE_PHYS + 0x00000e94)
#define HWIO_QDSS_STMAUXCR_RMSK                                      0x1f
#define HWIO_QDSS_STMAUXCR_IN          \
        in_dword_masked(HWIO_QDSS_STMAUXCR_ADDR, HWIO_QDSS_STMAUXCR_RMSK)
#define HWIO_QDSS_STMAUXCR_INM(m)      \
        in_dword_masked(HWIO_QDSS_STMAUXCR_ADDR, m)
#define HWIO_QDSS_STMAUXCR_OUT(v)      \
        out_dword(HWIO_QDSS_STMAUXCR_ADDR,v)
#define HWIO_QDSS_STMAUXCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QDSS_STMAUXCR_ADDR,m,v,HWIO_QDSS_STMAUXCR_IN)
#define HWIO_QDSS_STMAUXCR_AFREADYHIGH_BMSK                          0x10
#define HWIO_QDSS_STMAUXCR_AFREADYHIGH_SHFT                           0x4
#define HWIO_QDSS_STMAUXCR_AFREADYHIGH_NO_OVERRIDE_FVAL               0x0
#define HWIO_QDSS_STMAUXCR_AFREADYHIGH_OVERRIDE_FVAL                  0x1
#define HWIO_QDSS_STMAUXCR_CLKON_BMSK                                 0x8
#define HWIO_QDSS_STMAUXCR_CLKON_SHFT                                 0x3
#define HWIO_QDSS_STMAUXCR_CLKON_NO_OVERRIDE_FVAL                     0x0
#define HWIO_QDSS_STMAUXCR_CLKON_OVERRIDE_FVAL                        0x1
#define HWIO_QDSS_STMAUXCR_PRIORINVDIS_BMSK                           0x4
#define HWIO_QDSS_STMAUXCR_PRIORINVDIS_SHFT                           0x2
#define HWIO_QDSS_STMAUXCR_PRIORINVDIS_INVERSION_ENABLED_FVAL         0x0
#define HWIO_QDSS_STMAUXCR_PRIORINVDIS_INVERSION_DISABLED_FVAL        0x1
#define HWIO_QDSS_STMAUXCR_ASYNCPE_BMSK                               0x2
#define HWIO_QDSS_STMAUXCR_ASYNCPE_SHFT                               0x1
#define HWIO_QDSS_STMAUXCR_ASYNCPE_DISABLE_FVAL                       0x0
#define HWIO_QDSS_STMAUXCR_ASYNCPE_ENABLE_FVAL                        0x1
#define HWIO_QDSS_STMAUXCR_FIFOAF_BMSK                                0x1
#define HWIO_QDSS_STMAUXCR_FIFOAF_SHFT                                0x0
#define HWIO_QDSS_STMAUXCR_FIFOAF_DISABLED_FVAL                       0x0
#define HWIO_QDSS_STMAUXCR_FIFOAF_ENABLED_FVAL                        0x1

#define HWIO_QDSS_STMSPFEAT1R_ADDR                             (QDSS_STM_REG_BASE      + 0x00000ea0)
#define HWIO_QDSS_STMSPFEAT1R_PHYS                             (QDSS_STM_REG_BASE_PHYS + 0x00000ea0)
#define HWIO_QDSS_STMSPFEAT1R_RMSK                               0xffffff
#define HWIO_QDSS_STMSPFEAT1R_IN          \
        in_dword_masked(HWIO_QDSS_STMSPFEAT1R_ADDR, HWIO_QDSS_STMSPFEAT1R_RMSK)
#define HWIO_QDSS_STMSPFEAT1R_INM(m)      \
        in_dword_masked(HWIO_QDSS_STMSPFEAT1R_ADDR, m)
#define HWIO_QDSS_STMSPFEAT1R_SWOEN_BMSK                         0xc00000
#define HWIO_QDSS_STMSPFEAT1R_SWOEN_SHFT                             0x16
#define HWIO_QDSS_STMSPFEAT1R_SWOEN_NOT_IMPLEMENTED_FVAL              0x1
#define HWIO_QDSS_STMSPFEAT1R_SYNCEN_BMSK                        0x300000
#define HWIO_QDSS_STMSPFEAT1R_SYNCEN_SHFT                            0x14
#define HWIO_QDSS_STMSPFEAT1R_SYNCEN_RAO_FVAL                         0x2
#define HWIO_QDSS_STMSPFEAT1R_HWTEN_BMSK                          0xc0000
#define HWIO_QDSS_STMSPFEAT1R_HWTEN_SHFT                             0x12
#define HWIO_QDSS_STMSPFEAT1R_HWTEN_NOT_IMPLEMENTED_FVAL              0x1
#define HWIO_QDSS_STMSPFEAT1R_TSPRESCALE_BMSK                     0x30000
#define HWIO_QDSS_STMSPFEAT1R_TSPRESCALE_SHFT                        0x10
#define HWIO_QDSS_STMSPFEAT1R_TSPRESCALE_NOT_IMPLEMENTED_FVAL         0x1
#define HWIO_QDSS_STMSPFEAT1R_TRIGCTL_BMSK                         0xc000
#define HWIO_QDSS_STMSPFEAT1R_TRIGCTL_SHFT                            0xe
#define HWIO_QDSS_STMSPFEAT1R_TRIGCTL_MULTI_SHOT_AND_SINGLE_SHOT_FVAL        0x2
#define HWIO_QDSS_STMSPFEAT1R_TRACEBUS_BMSK                        0x3c00
#define HWIO_QDSS_STMSPFEAT1R_TRACEBUS_SHFT                           0xa
#define HWIO_QDSS_STMSPFEAT1R_TRACEBUS_ATB_WITH_TRIGGER_FVAL          0x1
#define HWIO_QDSS_STMSPFEAT1R_SYNC_BMSK                             0x300
#define HWIO_QDSS_STMSPFEAT1R_SYNC_SHFT                               0x8
#define HWIO_QDSS_STMSPFEAT1R_SYNC_MODE_FVAL                          0x3
#define HWIO_QDSS_STMSPFEAT1R_FORCETS_BMSK                           0x80
#define HWIO_QDSS_STMSPFEAT1R_FORCETS_SHFT                            0x7
#define HWIO_QDSS_STMSPFEAT1R_FORCETS_IMPLEMENTED_FVAL                0x1
#define HWIO_QDSS_STMSPFEAT1R_TSFREQ_BMSK                            0x40
#define HWIO_QDSS_STMSPFEAT1R_TSFREQ_SHFT                             0x6
#define HWIO_QDSS_STMSPFEAT1R_TSFREQ_RW_FVAL                          0x1
#define HWIO_QDSS_STMSPFEAT1R_TS_BMSK                                0x30
#define HWIO_QDSS_STMSPFEAT1R_TS_SHFT                                 0x4
#define HWIO_QDSS_STMSPFEAT1R_TS_ABSOLUT_FVAL                         0x1
#define HWIO_QDSS_STMSPFEAT1R_PROT_BMSK                               0xf
#define HWIO_QDSS_STMSPFEAT1R_PROT_SHFT                               0x0
#define HWIO_QDSS_STMSPFEAT1R_PROT_STPV2_FVAL                         0x1

#define HWIO_QDSS_STMSPFEAT2R_ADDR                             (QDSS_STM_REG_BASE      + 0x00000ea4)
#define HWIO_QDSS_STMSPFEAT2R_PHYS                             (QDSS_STM_REG_BASE_PHYS + 0x00000ea4)
#define HWIO_QDSS_STMSPFEAT2R_RMSK                                0x3f7f7
#define HWIO_QDSS_STMSPFEAT2R_IN          \
        in_dword_masked(HWIO_QDSS_STMSPFEAT2R_ADDR, HWIO_QDSS_STMSPFEAT2R_RMSK)
#define HWIO_QDSS_STMSPFEAT2R_INM(m)      \
        in_dword_masked(HWIO_QDSS_STMSPFEAT2R_ADDR, m)
#define HWIO_QDSS_STMSPFEAT2R_SPTYPE_BMSK                         0x30000
#define HWIO_QDSS_STMSPFEAT2R_SPTYPE_SHFT                            0x10
#define HWIO_QDSS_STMSPFEAT2R_SPTYPE_EXTENDED_ONLY_FVAL               0x1
#define HWIO_QDSS_STMSPFEAT2R_DSIZE_BMSK                           0xf000
#define HWIO_QDSS_STMSPFEAT2R_DSIZE_SHFT                              0xc
#define HWIO_QDSS_STMSPFEAT2R_DSIZE_ENUM_32_BIT_FVAL                  0x0
#define HWIO_QDSS_STMSPFEAT2R_SPTRTYPE_BMSK                         0x600
#define HWIO_QDSS_STMSPFEAT2R_SPTRTYPE_SHFT                           0x9
#define HWIO_QDSS_STMSPFEAT2R_SPTRTYPE_INVARIANT_TIMING_AND_GUARANTEED_FVAL        0x2
#define HWIO_QDSS_STMSPFEAT2R_PRIVMASK_BMSK                         0x180
#define HWIO_QDSS_STMSPFEAT2R_PRIVMASK_SHFT                           0x7
#define HWIO_QDSS_STMSPFEAT2R_PRIVMASK_NOT_IMPLEMENTED_FVAL           0x1
#define HWIO_QDSS_STMSPFEAT2R_SPOVERRIDE_BMSK                        0x40
#define HWIO_QDSS_STMSPFEAT2R_SPOVERRIDE_SHFT                         0x6
#define HWIO_QDSS_STMSPFEAT2R_SPOVERRIDE_IMPLEMENTED_FVAL             0x1
#define HWIO_QDSS_STMSPFEAT2R_SPCOMP_BMSK                            0x30
#define HWIO_QDSS_STMSPFEAT2R_SPCOMP_SHFT                             0x4
#define HWIO_QDSS_STMSPFEAT2R_SPCOMP_PROGRAMMABLE_FVAL                0x3
#define HWIO_QDSS_STMSPFEAT2R_SPER_BMSK                               0x4
#define HWIO_QDSS_STMSPFEAT2R_SPER_SHFT                               0x2
#define HWIO_QDSS_STMSPFEAT2R_SPER_IMPLEMENTED_FVAL                   0x0
#define HWIO_QDSS_STMSPFEAT2R_SPTER_BMSK                              0x3
#define HWIO_QDSS_STMSPFEAT2R_SPTER_SHFT                              0x0
#define HWIO_QDSS_STMSPFEAT2R_SPTER_IMPLEMENTED_FVAL                  0x2

#define HWIO_QDSS_STMSPFEAT3R_ADDR                             (QDSS_STM_REG_BASE      + 0x00000ea8)
#define HWIO_QDSS_STMSPFEAT3R_PHYS                             (QDSS_STM_REG_BASE_PHYS + 0x00000ea8)
#define HWIO_QDSS_STMSPFEAT3R_RMSK                                   0x7f
#define HWIO_QDSS_STMSPFEAT3R_IN          \
        in_dword_masked(HWIO_QDSS_STMSPFEAT3R_ADDR, HWIO_QDSS_STMSPFEAT3R_RMSK)
#define HWIO_QDSS_STMSPFEAT3R_INM(m)      \
        in_dword_masked(HWIO_QDSS_STMSPFEAT3R_ADDR, m)
#define HWIO_QDSS_STMSPFEAT3R_NUMMAST_BMSK                           0x7f
#define HWIO_QDSS_STMSPFEAT3R_NUMMAST_SHFT                            0x0
#define HWIO_QDSS_STMSPFEAT3R_NUMMAST_NUMMAST_FVAL                   0x7f

#define HWIO_QDSS_STMITTRIGGER_ADDR                            (QDSS_STM_REG_BASE      + 0x00000ee8)
#define HWIO_QDSS_STMITTRIGGER_PHYS                            (QDSS_STM_REG_BASE_PHYS + 0x00000ee8)
#define HWIO_QDSS_STMITTRIGGER_RMSK                                   0xf
#define HWIO_QDSS_STMITTRIGGER_OUT(v)      \
        out_dword(HWIO_QDSS_STMITTRIGGER_ADDR,v)
#define HWIO_QDSS_STMITTRIGGER_ASYNCOUT_W_BMSK                        0x8
#define HWIO_QDSS_STMITTRIGGER_ASYNCOUT_W_SHFT                        0x3
#define HWIO_QDSS_STMITTRIGGER_ASYNCOUT_W_LOW_FVAL                    0x0
#define HWIO_QDSS_STMITTRIGGER_ASYNCOUT_W_HIGH_FVAL                   0x1
#define HWIO_QDSS_STMITTRIGGER_TRIGOUTHETE_W_BMSK                     0x4
#define HWIO_QDSS_STMITTRIGGER_TRIGOUTHETE_W_SHFT                     0x2
#define HWIO_QDSS_STMITTRIGGER_TRIGOUTHETE_W_LOW_FVAL                 0x0
#define HWIO_QDSS_STMITTRIGGER_TRIGOUTHETE_W_HIGH_FVAL                0x1
#define HWIO_QDSS_STMITTRIGGER_TRIGOUTSW_W_BMSK                       0x2
#define HWIO_QDSS_STMITTRIGGER_TRIGOUTSW_W_SHFT                       0x1
#define HWIO_QDSS_STMITTRIGGER_TRIGOUTSW_W_LOW_FVAL                   0x0
#define HWIO_QDSS_STMITTRIGGER_TRIGOUTSW_W_HIGH_FVAL                  0x1
#define HWIO_QDSS_STMITTRIGGER_TRIGOUTSPTE_W_BMSK                     0x1
#define HWIO_QDSS_STMITTRIGGER_TRIGOUTSPTE_W_SHFT                     0x0
#define HWIO_QDSS_STMITTRIGGER_TRIGOUTSPTE_W_LOW_FVAL                 0x0
#define HWIO_QDSS_STMITTRIGGER_TRIGOUTSPTE_W_HIGH_FVAL                0x1

#define HWIO_QDSS_STMITATBDATA0_ADDR                           (QDSS_STM_REG_BASE      + 0x00000eec)
#define HWIO_QDSS_STMITATBDATA0_PHYS                           (QDSS_STM_REG_BASE_PHYS + 0x00000eec)
#define HWIO_QDSS_STMITATBDATA0_RMSK                                 0x1f
#define HWIO_QDSS_STMITATBDATA0_OUT(v)      \
        out_dword(HWIO_QDSS_STMITATBDATA0_ADDR,v)
#define HWIO_QDSS_STMITATBDATA0_ATDATAM31_W_BMSK                     0x10
#define HWIO_QDSS_STMITATBDATA0_ATDATAM31_W_SHFT                      0x4
#define HWIO_QDSS_STMITATBDATA0_ATDATAM31_W_LOW_FVAL                  0x0
#define HWIO_QDSS_STMITATBDATA0_ATDATAM31_W_HIGH_FVAL                 0x1
#define HWIO_QDSS_STMITATBDATA0_ATDATAM23_W_BMSK                      0x8
#define HWIO_QDSS_STMITATBDATA0_ATDATAM23_W_SHFT                      0x3
#define HWIO_QDSS_STMITATBDATA0_ATDATAM23_W_LOW_FVAL                  0x0
#define HWIO_QDSS_STMITATBDATA0_ATDATAM23_W_HIGH_FVAL                 0x1
#define HWIO_QDSS_STMITATBDATA0_ATDATAM15_W_BMSK                      0x4
#define HWIO_QDSS_STMITATBDATA0_ATDATAM15_W_SHFT                      0x2
#define HWIO_QDSS_STMITATBDATA0_ATDATAM15_W_LOW_FVAL                  0x0
#define HWIO_QDSS_STMITATBDATA0_ATDATAM15_W_HIGH_FVAL                 0x1
#define HWIO_QDSS_STMITATBDATA0_ATDATAM7_W_BMSK                       0x2
#define HWIO_QDSS_STMITATBDATA0_ATDATAM7_W_SHFT                       0x1
#define HWIO_QDSS_STMITATBDATA0_ATDATAM7_W_LOW_FVAL                   0x0
#define HWIO_QDSS_STMITATBDATA0_ATDATAM7_W_HIGH_FVAL                  0x1
#define HWIO_QDSS_STMITATBDATA0_ATDATAM0_W_BMSK                       0x1
#define HWIO_QDSS_STMITATBDATA0_ATDATAM0_W_SHFT                       0x0
#define HWIO_QDSS_STMITATBDATA0_ATDATAM0_W_LOW_FVAL                   0x0
#define HWIO_QDSS_STMITATBDATA0_ATDATAM0_W_HIGH_FVAL                  0x1

#define HWIO_QDSS_STMITATBCTR2_ADDR                            (QDSS_STM_REG_BASE      + 0x00000ef0)
#define HWIO_QDSS_STMITATBCTR2_PHYS                            (QDSS_STM_REG_BASE_PHYS + 0x00000ef0)
#define HWIO_QDSS_STMITATBCTR2_RMSK                                   0x3
#define HWIO_QDSS_STMITATBCTR2_IN          \
        in_dword_masked(HWIO_QDSS_STMITATBCTR2_ADDR, HWIO_QDSS_STMITATBCTR2_RMSK)
#define HWIO_QDSS_STMITATBCTR2_INM(m)      \
        in_dword_masked(HWIO_QDSS_STMITATBCTR2_ADDR, m)
#define HWIO_QDSS_STMITATBCTR2_AFVALIDM_R_BMSK                        0x2
#define HWIO_QDSS_STMITATBCTR2_AFVALIDM_R_SHFT                        0x1
#define HWIO_QDSS_STMITATBCTR2_AFVALIDM_R_LOW_FVAL                    0x0
#define HWIO_QDSS_STMITATBCTR2_AFVALIDM_R_HIGH_FVAL                   0x1
#define HWIO_QDSS_STMITATBCTR2_ATREADYM_R_BMSK                        0x1
#define HWIO_QDSS_STMITATBCTR2_ATREADYM_R_SHFT                        0x0
#define HWIO_QDSS_STMITATBCTR2_ATREADYM_R_LOW_FVAL                    0x0
#define HWIO_QDSS_STMITATBCTR2_ATREADYM_R_HIGH_FVAL                   0x1

#define HWIO_QDSS_STMITATBID_ADDR                              (QDSS_STM_REG_BASE      + 0x00000ef4)
#define HWIO_QDSS_STMITATBID_PHYS                              (QDSS_STM_REG_BASE_PHYS + 0x00000ef4)
#define HWIO_QDSS_STMITATBID_RMSK                                    0x7f
#define HWIO_QDSS_STMITATBID_OUT(v)      \
        out_dword(HWIO_QDSS_STMITATBID_ADDR,v)
#define HWIO_QDSS_STMITATBID_ATIDM_W_BMSK                            0x7f
#define HWIO_QDSS_STMITATBID_ATIDM_W_SHFT                             0x0

#define HWIO_QDSS_STMITATBCTR0_ADDR                            (QDSS_STM_REG_BASE      + 0x00000ef8)
#define HWIO_QDSS_STMITATBCTR0_PHYS                            (QDSS_STM_REG_BASE_PHYS + 0x00000ef8)
#define HWIO_QDSS_STMITATBCTR0_RMSK                                 0x303
#define HWIO_QDSS_STMITATBCTR0_OUT(v)      \
        out_dword(HWIO_QDSS_STMITATBCTR0_ADDR,v)
#define HWIO_QDSS_STMITATBCTR0_ATBYTESM_W_BMSK                      0x300
#define HWIO_QDSS_STMITATBCTR0_ATBYTESM_W_SHFT                        0x8
#define HWIO_QDSS_STMITATBCTR0_ATBYTESM_W_ENUM_00_FVAL                0x0
#define HWIO_QDSS_STMITATBCTR0_ATBYTESM_W_ENUM_01_FVAL                0x1
#define HWIO_QDSS_STMITATBCTR0_ATBYTESM_W_ENUM_10_FVAL                0x2
#define HWIO_QDSS_STMITATBCTR0_ATBYTESM_W_ENUM_11_FVAL                0x3
#define HWIO_QDSS_STMITATBCTR0_AFREADYM_W_BMSK                        0x2
#define HWIO_QDSS_STMITATBCTR0_AFREADYM_W_SHFT                        0x1
#define HWIO_QDSS_STMITATBCTR0_AFREADYM_W_LOW_FVAL                    0x0
#define HWIO_QDSS_STMITATBCTR0_AFREADYM_W_HIGH_FVAL                   0x1
#define HWIO_QDSS_STMITATBCTR0_ATVALIDM_W_BMSK                        0x1
#define HWIO_QDSS_STMITATBCTR0_ATVALIDM_W_SHFT                        0x0
#define HWIO_QDSS_STMITATBCTR0_ATVALIDM_W_LOW_FVAL                    0x0
#define HWIO_QDSS_STMITATBCTR0_ATVALIDM_W_HIGH_FVAL                   0x1

#define HWIO_QDSS_STMITCTRL_ADDR                               (QDSS_STM_REG_BASE      + 0x00000f00)
#define HWIO_QDSS_STMITCTRL_PHYS                               (QDSS_STM_REG_BASE_PHYS + 0x00000f00)
#define HWIO_QDSS_STMITCTRL_RMSK                                      0x1
#define HWIO_QDSS_STMITCTRL_IN          \
        in_dword_masked(HWIO_QDSS_STMITCTRL_ADDR, HWIO_QDSS_STMITCTRL_RMSK)
#define HWIO_QDSS_STMITCTRL_INM(m)      \
        in_dword_masked(HWIO_QDSS_STMITCTRL_ADDR, m)
#define HWIO_QDSS_STMITCTRL_OUT(v)      \
        out_dword(HWIO_QDSS_STMITCTRL_ADDR,v)
#define HWIO_QDSS_STMITCTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QDSS_STMITCTRL_ADDR,m,v,HWIO_QDSS_STMITCTRL_IN)
#define HWIO_QDSS_STMITCTRL_INTEGRATION_MODE_BMSK                     0x1
#define HWIO_QDSS_STMITCTRL_INTEGRATION_MODE_SHFT                     0x0
#define HWIO_QDSS_STMITCTRL_INTEGRATION_MODE_FUNCTIONAL_MODE_FVAL        0x0
#define HWIO_QDSS_STMITCTRL_INTEGRATION_MODE_INTEGRATION_MODE_FVAL        0x1

#define HWIO_QDSS_STMCLAIMSET_ADDR                             (QDSS_STM_REG_BASE      + 0x00000fa0)
#define HWIO_QDSS_STMCLAIMSET_PHYS                             (QDSS_STM_REG_BASE_PHYS + 0x00000fa0)
#define HWIO_QDSS_STMCLAIMSET_RMSK                                    0xf
#define HWIO_QDSS_STMCLAIMSET_IN          \
        in_dword_masked(HWIO_QDSS_STMCLAIMSET_ADDR, HWIO_QDSS_STMCLAIMSET_RMSK)
#define HWIO_QDSS_STMCLAIMSET_INM(m)      \
        in_dword_masked(HWIO_QDSS_STMCLAIMSET_ADDR, m)
#define HWIO_QDSS_STMCLAIMSET_OUT(v)      \
        out_dword(HWIO_QDSS_STMCLAIMSET_ADDR,v)
#define HWIO_QDSS_STMCLAIMSET_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QDSS_STMCLAIMSET_ADDR,m,v,HWIO_QDSS_STMCLAIMSET_IN)
#define HWIO_QDSS_STMCLAIMSET_CLAIMSET_BMSK                           0xf
#define HWIO_QDSS_STMCLAIMSET_CLAIMSET_SHFT                           0x0
#define HWIO_QDSS_STMCLAIMSET_CLAIMSET_CLAIM_TAG_IMPLEMENTED_BITS_FVAL        0xf

#define HWIO_QDSS_STMCLAIMCLR_ADDR                             (QDSS_STM_REG_BASE      + 0x00000fa4)
#define HWIO_QDSS_STMCLAIMCLR_PHYS                             (QDSS_STM_REG_BASE_PHYS + 0x00000fa4)
#define HWIO_QDSS_STMCLAIMCLR_RMSK                                    0xf
#define HWIO_QDSS_STMCLAIMCLR_IN          \
        in_dword_masked(HWIO_QDSS_STMCLAIMCLR_ADDR, HWIO_QDSS_STMCLAIMCLR_RMSK)
#define HWIO_QDSS_STMCLAIMCLR_INM(m)      \
        in_dword_masked(HWIO_QDSS_STMCLAIMCLR_ADDR, m)
#define HWIO_QDSS_STMCLAIMCLR_OUT(v)      \
        out_dword(HWIO_QDSS_STMCLAIMCLR_ADDR,v)
#define HWIO_QDSS_STMCLAIMCLR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QDSS_STMCLAIMCLR_ADDR,m,v,HWIO_QDSS_STMCLAIMCLR_IN)
#define HWIO_QDSS_STMCLAIMCLR_CLAIMCLR_BMSK                           0xf
#define HWIO_QDSS_STMCLAIMCLR_CLAIMCLR_SHFT                           0x0

#define HWIO_QDSS_STMLAR_ADDR                                  (QDSS_STM_REG_BASE      + 0x00000fb0)
#define HWIO_QDSS_STMLAR_PHYS                                  (QDSS_STM_REG_BASE_PHYS + 0x00000fb0)
#define HWIO_QDSS_STMLAR_RMSK                                  0xffffffff
#define HWIO_QDSS_STMLAR_OUT(v)      \
        out_dword(HWIO_QDSS_STMLAR_ADDR,v)
#define HWIO_QDSS_STMLAR_ACCESS_W_BMSK                         0xffffffff
#define HWIO_QDSS_STMLAR_ACCESS_W_SHFT                                0x0
#define HWIO_QDSS_STMLAR_ACCESS_W_UNLOCK_FVAL                  0xc5acce55

#define HWIO_QDSS_STMLSR_ADDR                                  (QDSS_STM_REG_BASE      + 0x00000fb4)
#define HWIO_QDSS_STMLSR_PHYS                                  (QDSS_STM_REG_BASE_PHYS + 0x00000fb4)
#define HWIO_QDSS_STMLSR_RMSK                                         0x7
#define HWIO_QDSS_STMLSR_IN          \
        in_dword_masked(HWIO_QDSS_STMLSR_ADDR, HWIO_QDSS_STMLSR_RMSK)
#define HWIO_QDSS_STMLSR_INM(m)      \
        in_dword_masked(HWIO_QDSS_STMLSR_ADDR, m)
#define HWIO_QDSS_STMLSR_LOCKTYPE_BMSK                                0x4
#define HWIO_QDSS_STMLSR_LOCKTYPE_SHFT                                0x2
#define HWIO_QDSS_STMLSR_LOCKTYPE_ENUM_32_BIT_FVAL                    0x0
#define HWIO_QDSS_STMLSR_LOCKGRANT_BMSK                               0x2
#define HWIO_QDSS_STMLSR_LOCKGRANT_SHFT                               0x1
#define HWIO_QDSS_STMLSR_LOCKGRANT_ACCESS_PERMITTED_FVAL              0x0
#define HWIO_QDSS_STMLSR_LOCKGRANT_DEVICE_LOCKED_FVAL                 0x1
#define HWIO_QDSS_STMLSR_LOCKEXIST_BMSK                               0x1
#define HWIO_QDSS_STMLSR_LOCKEXIST_SHFT                               0x0
#define HWIO_QDSS_STMLSR_LOCKEXIST_LOCK_NOT_PRESENT_FVAL              0x0
#define HWIO_QDSS_STMLSR_LOCKEXIST_LOCK_PRESENT_FVAL                  0x1

#define HWIO_QDSS_STMAUTHSTATUS_ADDR                           (QDSS_STM_REG_BASE      + 0x00000fb8)
#define HWIO_QDSS_STMAUTHSTATUS_PHYS                           (QDSS_STM_REG_BASE_PHYS + 0x00000fb8)
#define HWIO_QDSS_STMAUTHSTATUS_RMSK                                 0xff
#define HWIO_QDSS_STMAUTHSTATUS_IN          \
        in_dword_masked(HWIO_QDSS_STMAUTHSTATUS_ADDR, HWIO_QDSS_STMAUTHSTATUS_RMSK)
#define HWIO_QDSS_STMAUTHSTATUS_INM(m)      \
        in_dword_masked(HWIO_QDSS_STMAUTHSTATUS_ADDR, m)
#define HWIO_QDSS_STMAUTHSTATUS_SNID_BMSK                            0xc0
#define HWIO_QDSS_STMAUTHSTATUS_SNID_SHFT                             0x6
#define HWIO_QDSS_STMAUTHSTATUS_SNID_ENUM_2_B10_FVAL                  0x2
#define HWIO_QDSS_STMAUTHSTATUS_SNID_ENUM_2_B11_FVAL                  0x3
#define HWIO_QDSS_STMAUTHSTATUS_SID_BMSK                             0x30
#define HWIO_QDSS_STMAUTHSTATUS_SID_SHFT                              0x4
#define HWIO_QDSS_STMAUTHSTATUS_SID_ENUM_2_B10_FVAL                   0x2
#define HWIO_QDSS_STMAUTHSTATUS_SID_ENUM_2_B11_FVAL                   0x3
#define HWIO_QDSS_STMAUTHSTATUS_NSNID_BMSK                            0xc
#define HWIO_QDSS_STMAUTHSTATUS_NSNID_SHFT                            0x2
#define HWIO_QDSS_STMAUTHSTATUS_NSNID_ENUM_2_B10_FVAL                 0x2
#define HWIO_QDSS_STMAUTHSTATUS_NSNID_ENUM_2_B11_FVAL                 0x3
#define HWIO_QDSS_STMAUTHSTATUS_NSID_BMSK                             0x3
#define HWIO_QDSS_STMAUTHSTATUS_NSID_SHFT                             0x0
#define HWIO_QDSS_STMAUTHSTATUS_NSID_ENUM_2_B10_FVAL                  0x2
#define HWIO_QDSS_STMAUTHSTATUS_NSID_ENUM_2_B11_FVAL                  0x3

#define HWIO_QDSS_STMDEVID_ADDR                                (QDSS_STM_REG_BASE      + 0x00000fc8)
#define HWIO_QDSS_STMDEVID_PHYS                                (QDSS_STM_REG_BASE_PHYS + 0x00000fc8)
#define HWIO_QDSS_STMDEVID_RMSK                                   0x1ffff
#define HWIO_QDSS_STMDEVID_IN          \
        in_dword_masked(HWIO_QDSS_STMDEVID_ADDR, HWIO_QDSS_STMDEVID_RMSK)
#define HWIO_QDSS_STMDEVID_INM(m)      \
        in_dword_masked(HWIO_QDSS_STMDEVID_ADDR, m)
#define HWIO_QDSS_STMDEVID_NUMSP_BMSK                             0x1ffff
#define HWIO_QDSS_STMDEVID_NUMSP_SHFT                                 0x0
#define HWIO_QDSS_STMDEVID_NUMSP_NUMBER_OF_PORTS_FVAL             0x10000

#define HWIO_QDSS_STMDEVTYPE_ADDR                              (QDSS_STM_REG_BASE      + 0x00000fcc)
#define HWIO_QDSS_STMDEVTYPE_PHYS                              (QDSS_STM_REG_BASE_PHYS + 0x00000fcc)
#define HWIO_QDSS_STMDEVTYPE_RMSK                                    0xff
#define HWIO_QDSS_STMDEVTYPE_IN          \
        in_dword_masked(HWIO_QDSS_STMDEVTYPE_ADDR, HWIO_QDSS_STMDEVTYPE_RMSK)
#define HWIO_QDSS_STMDEVTYPE_INM(m)      \
        in_dword_masked(HWIO_QDSS_STMDEVTYPE_ADDR, m)
#define HWIO_QDSS_STMDEVTYPE_SUB_TYPE_BMSK                           0xf0
#define HWIO_QDSS_STMDEVTYPE_SUB_TYPE_SHFT                            0x4
#define HWIO_QDSS_STMDEVTYPE_SUB_TYPE_CORESIGHT_STM_FVAL              0x6
#define HWIO_QDSS_STMDEVTYPE_MAJOR_TYPE_BMSK                          0xf
#define HWIO_QDSS_STMDEVTYPE_MAJOR_TYPE_SHFT                          0x0
#define HWIO_QDSS_STMDEVTYPE_MAJOR_TYPE_TRACE_SOURCE_FVAL             0x3

#define HWIO_QDSS_STMPIDR0_ADDR                                (QDSS_STM_REG_BASE      + 0x00000fe0)
#define HWIO_QDSS_STMPIDR0_PHYS                                (QDSS_STM_REG_BASE_PHYS + 0x00000fe0)
#define HWIO_QDSS_STMPIDR0_RMSK                                      0xff
#define HWIO_QDSS_STMPIDR0_IN          \
        in_dword_masked(HWIO_QDSS_STMPIDR0_ADDR, HWIO_QDSS_STMPIDR0_RMSK)
#define HWIO_QDSS_STMPIDR0_INM(m)      \
        in_dword_masked(HWIO_QDSS_STMPIDR0_ADDR, m)
#define HWIO_QDSS_STMPIDR0_PART_NUMBER_BITS7TO0_BMSK                 0xff
#define HWIO_QDSS_STMPIDR0_PART_NUMBER_BITS7TO0_SHFT                  0x0
#define HWIO_QDSS_STMPIDR0_PART_NUMBER_BITS7TO0_CORESIGHT_STM_PART_NUMBER_7_0_FVAL       0x62

#define HWIO_QDSS_STMPIDR1_ADDR                                (QDSS_STM_REG_BASE      + 0x00000fe4)
#define HWIO_QDSS_STMPIDR1_PHYS                                (QDSS_STM_REG_BASE_PHYS + 0x00000fe4)
#define HWIO_QDSS_STMPIDR1_RMSK                                      0xff
#define HWIO_QDSS_STMPIDR1_IN          \
        in_dword_masked(HWIO_QDSS_STMPIDR1_ADDR, HWIO_QDSS_STMPIDR1_RMSK)
#define HWIO_QDSS_STMPIDR1_INM(m)      \
        in_dword_masked(HWIO_QDSS_STMPIDR1_ADDR, m)
#define HWIO_QDSS_STMPIDR1_JEP106_BITS3TO0_BMSK                      0xf0
#define HWIO_QDSS_STMPIDR1_JEP106_BITS3TO0_SHFT                       0x4
#define HWIO_QDSS_STMPIDR1_JEP106_BITS3TO0_ARM_JEP106_IDENTITY_CODE_7_0_FVAL        0xb
#define HWIO_QDSS_STMPIDR1_PART_NUMBER_BITS11TO8_BMSK                 0xf
#define HWIO_QDSS_STMPIDR1_PART_NUMBER_BITS11TO8_SHFT                 0x0
#define HWIO_QDSS_STMPIDR1_PART_NUMBER_BITS11TO8_CORESIGHT_STM_PART_NUMBER_11_8_FVAL        0x9

#define HWIO_QDSS_STMPIDR2_ADDR                                (QDSS_STM_REG_BASE      + 0x00000fe8)
#define HWIO_QDSS_STMPIDR2_PHYS                                (QDSS_STM_REG_BASE_PHYS + 0x00000fe8)
#define HWIO_QDSS_STMPIDR2_RMSK                                      0xff
#define HWIO_QDSS_STMPIDR2_IN          \
        in_dword_masked(HWIO_QDSS_STMPIDR2_ADDR, HWIO_QDSS_STMPIDR2_RMSK)
#define HWIO_QDSS_STMPIDR2_INM(m)      \
        in_dword_masked(HWIO_QDSS_STMPIDR2_ADDR, m)
#define HWIO_QDSS_STMPIDR2_REVISION_BMSK                             0xf0
#define HWIO_QDSS_STMPIDR2_REVISION_SHFT                              0x4
#define HWIO_QDSS_STMPIDR2_REVISION_R0P1_FVAL                         0x1
#define HWIO_QDSS_STMPIDR2_JEDEC_BMSK                                 0x8
#define HWIO_QDSS_STMPIDR2_JEDEC_SHFT                                 0x3
#define HWIO_QDSS_STMPIDR2_JEDEC_JEDEC_IDENTITY_FVAL                  0x1
#define HWIO_QDSS_STMPIDR2_JEP106_BITS6TO4_BMSK                       0x7
#define HWIO_QDSS_STMPIDR2_JEP106_BITS6TO4_SHFT                       0x0
#define HWIO_QDSS_STMPIDR2_JEP106_BITS6TO4_ARM_JEP106_IDENTITY_CODE_6_4_FVAL        0x3

#define HWIO_QDSS_STMPIDR3_ADDR                                (QDSS_STM_REG_BASE      + 0x00000fec)
#define HWIO_QDSS_STMPIDR3_PHYS                                (QDSS_STM_REG_BASE_PHYS + 0x00000fec)
#define HWIO_QDSS_STMPIDR3_RMSK                                      0xff
#define HWIO_QDSS_STMPIDR3_IN          \
        in_dword_masked(HWIO_QDSS_STMPIDR3_ADDR, HWIO_QDSS_STMPIDR3_RMSK)
#define HWIO_QDSS_STMPIDR3_INM(m)      \
        in_dword_masked(HWIO_QDSS_STMPIDR3_ADDR, m)
#define HWIO_QDSS_STMPIDR3_REVAND_BMSK                               0xf0
#define HWIO_QDSS_STMPIDR3_REVAND_SHFT                                0x4
#define HWIO_QDSS_STMPIDR3_REVAND_NO_MODS_FVAL                        0x0
#define HWIO_QDSS_STMPIDR3_CUSTOMER_MODIFIED_BMSK                     0xf
#define HWIO_QDSS_STMPIDR3_CUSTOMER_MODIFIED_SHFT                     0x0
#define HWIO_QDSS_STMPIDR3_CUSTOMER_MODIFIED_NO_MODS_FVAL             0x0

#define HWIO_QDSS_STMPIDR4_ADDR                                (QDSS_STM_REG_BASE      + 0x00000fd0)
#define HWIO_QDSS_STMPIDR4_PHYS                                (QDSS_STM_REG_BASE_PHYS + 0x00000fd0)
#define HWIO_QDSS_STMPIDR4_RMSK                                      0xff
#define HWIO_QDSS_STMPIDR4_IN          \
        in_dword_masked(HWIO_QDSS_STMPIDR4_ADDR, HWIO_QDSS_STMPIDR4_RMSK)
#define HWIO_QDSS_STMPIDR4_INM(m)      \
        in_dword_masked(HWIO_QDSS_STMPIDR4_ADDR, m)
#define HWIO_QDSS_STMPIDR4_FOURKB_COUNT_BMSK                         0xf0
#define HWIO_QDSS_STMPIDR4_FOURKB_COUNT_SHFT                          0x4
#define HWIO_QDSS_STMPIDR4_FOURKB_COUNT_ENUM_4KB_FVAL                 0x0
#define HWIO_QDSS_STMPIDR4_JEP106_CONT_BMSK                           0xf
#define HWIO_QDSS_STMPIDR4_JEP106_CONT_SHFT                           0x0
#define HWIO_QDSS_STMPIDR4_JEP106_CONT_ARM_JEP106_CONTINUATION_CODE_FVAL        0x4

#define HWIO_QDSS_STMPIDR5_ADDR                                (QDSS_STM_REG_BASE      + 0x00000fd4)
#define HWIO_QDSS_STMPIDR5_PHYS                                (QDSS_STM_REG_BASE_PHYS + 0x00000fd4)
#define HWIO_QDSS_STMPIDR5_RMSK                                0xffffffff
#define HWIO_QDSS_STMPIDR5_IN          \
        in_dword_masked(HWIO_QDSS_STMPIDR5_ADDR, HWIO_QDSS_STMPIDR5_RMSK)
#define HWIO_QDSS_STMPIDR5_INM(m)      \
        in_dword_masked(HWIO_QDSS_STMPIDR5_ADDR, m)
#define HWIO_QDSS_STMPIDR5_OUT(v)      \
        out_dword(HWIO_QDSS_STMPIDR5_ADDR,v)
#define HWIO_QDSS_STMPIDR5_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QDSS_STMPIDR5_ADDR,m,v,HWIO_QDSS_STMPIDR5_IN)
#define HWIO_QDSS_STMPIDR5_STMPIDR5_BMSK                       0xffffffff
#define HWIO_QDSS_STMPIDR5_STMPIDR5_SHFT                              0x0

#define HWIO_QDSS_STMPIDR6_ADDR                                (QDSS_STM_REG_BASE      + 0x00000fd8)
#define HWIO_QDSS_STMPIDR6_PHYS                                (QDSS_STM_REG_BASE_PHYS + 0x00000fd8)
#define HWIO_QDSS_STMPIDR6_RMSK                                0xffffffff
#define HWIO_QDSS_STMPIDR6_IN          \
        in_dword_masked(HWIO_QDSS_STMPIDR6_ADDR, HWIO_QDSS_STMPIDR6_RMSK)
#define HWIO_QDSS_STMPIDR6_INM(m)      \
        in_dword_masked(HWIO_QDSS_STMPIDR6_ADDR, m)
#define HWIO_QDSS_STMPIDR6_OUT(v)      \
        out_dword(HWIO_QDSS_STMPIDR6_ADDR,v)
#define HWIO_QDSS_STMPIDR6_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QDSS_STMPIDR6_ADDR,m,v,HWIO_QDSS_STMPIDR6_IN)
#define HWIO_QDSS_STMPIDR6_STMPIDR6_BMSK                       0xffffffff
#define HWIO_QDSS_STMPIDR6_STMPIDR6_SHFT                              0x0

#define HWIO_QDSS_STMPIDR7_ADDR                                (QDSS_STM_REG_BASE      + 0x00000fdc)
#define HWIO_QDSS_STMPIDR7_PHYS                                (QDSS_STM_REG_BASE_PHYS + 0x00000fdc)
#define HWIO_QDSS_STMPIDR7_RMSK                                0xffffffff
#define HWIO_QDSS_STMPIDR7_IN          \
        in_dword_masked(HWIO_QDSS_STMPIDR7_ADDR, HWIO_QDSS_STMPIDR7_RMSK)
#define HWIO_QDSS_STMPIDR7_INM(m)      \
        in_dword_masked(HWIO_QDSS_STMPIDR7_ADDR, m)
#define HWIO_QDSS_STMPIDR7_OUT(v)      \
        out_dword(HWIO_QDSS_STMPIDR7_ADDR,v)
#define HWIO_QDSS_STMPIDR7_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QDSS_STMPIDR7_ADDR,m,v,HWIO_QDSS_STMPIDR7_IN)
#define HWIO_QDSS_STMPIDR7_STMPIDR7_BMSK                       0xffffffff
#define HWIO_QDSS_STMPIDR7_STMPIDR7_SHFT                              0x0

#define HWIO_QDSS_STMCIDR0_ADDR                                (QDSS_STM_REG_BASE      + 0x00000ff0)
#define HWIO_QDSS_STMCIDR0_PHYS                                (QDSS_STM_REG_BASE_PHYS + 0x00000ff0)
#define HWIO_QDSS_STMCIDR0_RMSK                                      0xff
#define HWIO_QDSS_STMCIDR0_IN          \
        in_dword_masked(HWIO_QDSS_STMCIDR0_ADDR, HWIO_QDSS_STMCIDR0_RMSK)
#define HWIO_QDSS_STMCIDR0_INM(m)      \
        in_dword_masked(HWIO_QDSS_STMCIDR0_ADDR, m)
#define HWIO_QDSS_STMCIDR0_PREAMBLE_BMSK                             0xff
#define HWIO_QDSS_STMCIDR0_PREAMBLE_SHFT                              0x0
#define HWIO_QDSS_STMCIDR0_PREAMBLE_ENUM_0D_FVAL                      0xd

#define HWIO_QDSS_STMCIDR1_ADDR                                (QDSS_STM_REG_BASE      + 0x00000ff4)
#define HWIO_QDSS_STMCIDR1_PHYS                                (QDSS_STM_REG_BASE_PHYS + 0x00000ff4)
#define HWIO_QDSS_STMCIDR1_RMSK                                      0xff
#define HWIO_QDSS_STMCIDR1_IN          \
        in_dword_masked(HWIO_QDSS_STMCIDR1_ADDR, HWIO_QDSS_STMCIDR1_RMSK)
#define HWIO_QDSS_STMCIDR1_INM(m)      \
        in_dword_masked(HWIO_QDSS_STMCIDR1_ADDR, m)
#define HWIO_QDSS_STMCIDR1_CLASS_BMSK                                0xf0
#define HWIO_QDSS_STMCIDR1_CLASS_SHFT                                 0x4
#define HWIO_QDSS_STMCIDR1_CLASS_CORESIGHT_COMPONENT_FVAL             0x9
#define HWIO_QDSS_STMCIDR1_PREAMBLE_BMSK                              0xf
#define HWIO_QDSS_STMCIDR1_PREAMBLE_SHFT                              0x0
#define HWIO_QDSS_STMCIDR1_PREAMBLE_ENUM_0_FVAL                       0x0

#define HWIO_QDSS_STMCIDR2_ADDR                                (QDSS_STM_REG_BASE      + 0x00000ff8)
#define HWIO_QDSS_STMCIDR2_PHYS                                (QDSS_STM_REG_BASE_PHYS + 0x00000ff8)
#define HWIO_QDSS_STMCIDR2_RMSK                                      0xff
#define HWIO_QDSS_STMCIDR2_IN          \
        in_dword_masked(HWIO_QDSS_STMCIDR2_ADDR, HWIO_QDSS_STMCIDR2_RMSK)
#define HWIO_QDSS_STMCIDR2_INM(m)      \
        in_dword_masked(HWIO_QDSS_STMCIDR2_ADDR, m)
#define HWIO_QDSS_STMCIDR2_PREAMBLE_BMSK                             0xff
#define HWIO_QDSS_STMCIDR2_PREAMBLE_SHFT                              0x0
#define HWIO_QDSS_STMCIDR2_PREAMBLE_ENUM_05_FVAL                      0x5

#define HWIO_QDSS_STMCIDR3_ADDR                                (QDSS_STM_REG_BASE      + 0x00000ffc)
#define HWIO_QDSS_STMCIDR3_PHYS                                (QDSS_STM_REG_BASE_PHYS + 0x00000ffc)
#define HWIO_QDSS_STMCIDR3_RMSK                                      0xff
#define HWIO_QDSS_STMCIDR3_IN          \
        in_dword_masked(HWIO_QDSS_STMCIDR3_ADDR, HWIO_QDSS_STMCIDR3_RMSK)
#define HWIO_QDSS_STMCIDR3_INM(m)      \
        in_dword_masked(HWIO_QDSS_STMCIDR3_ADDR, m)
#define HWIO_QDSS_STMCIDR3_PREAMBLE_BMSK                             0xff
#define HWIO_QDSS_STMCIDR3_PREAMBLE_SHFT                              0x0
#define HWIO_QDSS_STMCIDR3_PREAMBLE_B1_FVAL                          0xb1


#endif /*HWIOQDSS_STM_CONFIG_H */
