#ifndef __TIMERHWIO_H__
#define __TIMERHWIO_H__
/*
===========================================================================
*/
/**
  @file TimerHWIO.h
  @brief Auto-generated HWIO interface include file.

  This file contains HWIO register definitions for the following modules:
    QTMR_V1

  'Include' filters applied: QTMR[QTMR_V1] 
  'Exclude' filters applied: RESERVED DUMMY 
*/
/*
  ===========================================================================

  Copyright (c) 2011 Qualcomm Technologies Incorporated.
  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ===========================================================================

  $Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/busywait/src/slpi/busywaitTimerHWIO.h#1 $
  $DateTime: 2020/02/10 01:57:30 $
  $Author: pwbldsvc $

  ===========================================================================
*/
#include "msmhwiobase.h"


/*----------------------------------------------------------------------------
 * MODULE: QTIMER_AC1
 *--------------------------------------------------------------------------*/

#define HWIO_QTMR_AC_CNTFRQ_ADDR(BASE)                           (BASE      + 0x00000000)
#define HWIO_QTMR_AC_CNTFRQ_RMSK                           0xffffffff
#define HWIO_QTMR_AC_CNTFRQ_IN(BASE)          \
        in_dword_masked(HWIO_QTMR_AC_CNTFRQ_ADDR(BASE), HWIO_QTMR_AC_CNTFRQ_RMSK)
#define HWIO_QTMR_AC_CNTFRQ_INM(BASE,m)      \
        in_dword_masked(HWIO_QTMR_AC_CNTFRQ_ADDR(BASE), m)
#define HWIO_QTMR_AC_CNTFRQ_OUT(BASE,v)      \
        out_dword(HWIO_QTMR_AC_CNTFRQ_ADDR(BASE),v)
#define HWIO_QTMR_AC_CNTFRQ_OUTM(BASE,m,v) \
        out_dword_masked_ns(HWIO_QTMR_AC_CNTFRQ_ADDR(BASE),m,v,HWIO_QTMR_AC_CNTFRQ_IN(BASE))
#define HWIO_QTMR_AC_CNTFRQ_CNTFRQ_BMSK                    0xffffffff
#define HWIO_QTMR_AC_CNTFRQ_CNTFRQ_SHFT                           0x0

#define HWIO_QTMR_AC_CNTSR_ADDR(BASE)                            (BASE      + 0x00000004)
#define HWIO_QTMR_AC_CNTSR_RMSK                                  0x1f
#define HWIO_QTMR_AC_CNTSR_IN(BASE)          \
        in_dword_masked(HWIO_QTMR_AC_CNTSR_ADDR(BASE), HWIO_QTMR_AC_CNTSR_RMSK)
#define HWIO_QTMR_AC_CNTSR_INM(BASE,m)      \
        in_dword_masked(HWIO_QTMR_AC_CNTSR_ADDR(BASE), m)
#define HWIO_QTMR_AC_CNTSR_OUT(BASE,v)      \
        out_dword(HWIO_QTMR_AC_CNTSR_ADDR(BASE),v)
#define HWIO_QTMR_AC_CNTSR_OUTM(BASE,m,v) \
        out_dword_masked_ns(HWIO_QTMR_AC_CNTSR_ADDR(BASE),m,v,HWIO_QTMR_AC_CNTSR_IN(BASE))
#define HWIO_QTMR_AC_CNTSR_NSN_BMSK                              0x1f
#define HWIO_QTMR_AC_CNTSR_NSN_SHFT                               0x0

#define HWIO_QTMR_AC_CNTTID_ADDR(BASE)                           (BASE      + 0x00000008)
#define HWIO_QTMR_AC_CNTTID_RMSK                           0xffffffff
#define HWIO_QTMR_AC_CNTTID_IN(BASE)          \
        in_dword_masked(HWIO_QTMR_AC_CNTTID_ADDR(BASE), HWIO_QTMR_AC_CNTTID_RMSK)
#define HWIO_QTMR_AC_CNTTID_INM(BASE,m)      \
        in_dword_masked(HWIO_QTMR_AC_CNTTID_ADDR(BASE), m)
#define HWIO_QTMR_AC_CNTTID_F7_CFG_BMSK                    0xf0000000
#define HWIO_QTMR_AC_CNTTID_F7_CFG_SHFT                          0x1c
#define HWIO_QTMR_AC_CNTTID_F6_CFG_BMSK                     0xf000000
#define HWIO_QTMR_AC_CNTTID_F6_CFG_SHFT                          0x18
#define HWIO_QTMR_AC_CNTTID_F5_CFG_BMSK                      0xf00000
#define HWIO_QTMR_AC_CNTTID_F5_CFG_SHFT                          0x14
#define HWIO_QTMR_AC_CNTTID_F4_CFG_BMSK                       0xf0000
#define HWIO_QTMR_AC_CNTTID_F4_CFG_SHFT                          0x10
#define HWIO_QTMR_AC_CNTTID_F3_CFG_BMSK                        0xf000
#define HWIO_QTMR_AC_CNTTID_F3_CFG_SHFT                           0xc
#define HWIO_QTMR_AC_CNTTID_F2_CFG_BMSK                         0xf00
#define HWIO_QTMR_AC_CNTTID_F2_CFG_SHFT                           0x8
#define HWIO_QTMR_AC_CNTTID_F1_CFG_BMSK                          0xf0
#define HWIO_QTMR_AC_CNTTID_F1_CFG_SHFT                           0x4
#define HWIO_QTMR_AC_CNTTID_F0_CFG_BMSK                           0xf
#define HWIO_QTMR_AC_CNTTID_F0_CFG_SHFT                           0x0

#define HWIO_QTMR_AC_CNTACR_n_ADDR(BASE,n)                      (BASE      + 0x00000040 + 0x4 * (n))
#define HWIO_QTMR_AC_CNTACR_n_RMSK                               0x3f
#define HWIO_QTMR_AC_CNTACR_n_MAXn                                  4
#define HWIO_QTMR_AC_CNTACR_n_INI(n)        \
        in_dword_masked(HWIO_QTMR_AC_CNTACR_n_ADDR(BASE,n), HWIO_QTMR_AC_CNTACR_n_RMSK)
#define HWIO_QTMR_AC_CNTACR_n_INMI(BASE,n,mask)    \
        in_dword_masked(HWIO_QTMR_AC_CNTACR_n_ADDR(BASE,n), (mask))
#define HWIO_QTMR_AC_CNTACR_n_OUTI(BASE,n,val)    \
        out_dword(HWIO_QTMR_AC_CNTACR_n_ADDR(BASE,n),val)
#define HWIO_QTMR_AC_CNTACR_n_OUTMI(BASE,n,mask,val) \
        out_dword_masked_ns(HWIO_QTMR_AC_CNTACR_n_ADDR(BASE,n),mask,val,HWIO_QTMR_AC_CNTACR_n_INI(n))
#define HWIO_QTMR_AC_CNTACR_n_RWPT_BMSK                          0x20
#define HWIO_QTMR_AC_CNTACR_n_RWPT_SHFT                           0x5
#define HWIO_QTMR_AC_CNTACR_n_RWVT_BMSK                          0x10
#define HWIO_QTMR_AC_CNTACR_n_RWVT_SHFT                           0x4
#define HWIO_QTMR_AC_CNTACR_n_RVOFF_BMSK                          0x8
#define HWIO_QTMR_AC_CNTACR_n_RVOFF_SHFT                          0x3
#define HWIO_QTMR_AC_CNTACR_n_RFRQ_BMSK                           0x4
#define HWIO_QTMR_AC_CNTACR_n_RFRQ_SHFT                           0x2
#define HWIO_QTMR_AC_CNTACR_n_RPVCT_BMSK                          0x2
#define HWIO_QTMR_AC_CNTACR_n_RPVCT_SHFT                          0x1
#define HWIO_QTMR_AC_CNTACR_n_RPCT_BMSK                           0x1
#define HWIO_QTMR_AC_CNTACR_n_RPCT_SHFT                           0x0

#define HWIO_QTMR_AC_CNTVOFF_LO_n_ADDR(BASE,n)                  (BASE      + 0x00000080 + 0x8 * (n))
#define HWIO_QTMR_AC_CNTVOFF_LO_n_RMSK                     0xffffffff
#define HWIO_QTMR_AC_CNTVOFF_LO_n_MAXn                              4
#define HWIO_QTMR_AC_CNTVOFF_LO_n_INI(n)        \
        in_dword_masked(HWIO_QTMR_AC_CNTVOFF_LO_n_ADDR(BASE,n), HWIO_QTMR_AC_CNTVOFF_LO_n_RMSK)
#define HWIO_QTMR_AC_CNTVOFF_LO_n_INMI(BASE,n,mask)    \
        in_dword_masked(HWIO_QTMR_AC_CNTVOFF_LO_n_ADDR(BASE,n), (mask))
#define HWIO_QTMR_AC_CNTVOFF_LO_n_OUTI(BASE,n,val)    \
        out_dword(HWIO_QTMR_AC_CNTVOFF_LO_n_ADDR(n),val)
#define HWIO_QTMR_AC_CNTVOFF_LO_n_OUTMI(BASE,n,mask,val) \
        out_dword_masked_ns(HWIO_QTMR_AC_CNTVOFF_LO_n_ADDR(BASE,n),mask,val,HWIO_QTMR_AC_CNTVOFF_LO_n_INI(BASE,n))
#define HWIO_QTMR_AC_CNTVOFF_LO_n_CNTVOFF_LO_BMSK          0xffffffff
#define HWIO_QTMR_AC_CNTVOFF_LO_n_CNTVOFF_LO_SHFT                 0x0

#define HWIO_QTMR_AC_CNTVOFF_HI_n_ADDR(BASE,n)                  (BASE      + 0x00000084 + 0x8 * (n))
#define HWIO_QTMR_AC_CNTVOFF_HI_n_RMSK                     0xffffff
#define HWIO_QTMR_AC_CNTVOFF_HI_n_MAXn                              4
#define HWIO_QTMR_AC_CNTVOFF_HI_n_INI(n)        \
        in_dword_masked(HWIO_QTMR_AC_CNTVOFF_HI_n_ADDR(BASE,n), HWIO_QTMR_AC_CNTVOFF_HI_n_RMSK)
#define HWIO_QTMR_AC_CNTVOFF_HI_n_INMI(BASE,n,mask)    \
        in_dword_masked(HWIO_QTMR_AC_CNTVOFF_HI_n_ADDR(BASE,n), (mask))
#define HWIO_QTMR_AC_CNTVOFF_HI_n_OUTI(BASE,n,val)    \
        out_dword(HWIO_QTMR_AC_CNTVOFF_HI_n_ADDR(BASE,n),val)
#define HWIO_QTMR_AC_CNTVOFF_HI_n_OUTMI(BASE,n,mask,val) \
        out_dword_masked_ns(HWIO_QTMR_AC_CNTVOFF_HI_n_ADDR(BASE,n),mask,val,HWIO_QTMR_AC_CNTVOFF_HI_n_INI(BASE,n))
#define HWIO_QTMR_AC_CNTVOFF_HI_n_CNTVOFF_HI_BMSK          0xffffff
#define HWIO_QTMR_AC_CNTVOFF_HI_n_CNTVOFF_HI_SHFT                 0x0

#define HWIO_QTMR_AC_VERSION_ADDR(BASE)                             (BASE      + 0x00000fd0)
#define HWIO_QTMR_AC_VERSION_RMSK                             0xffffffff
#define HWIO_QTMR_AC_VERSION_IN(BASE)          \
        in_dword_masked(HWIO_QTMR_AC_VERSION_ADDR(BASE), HWIO_QTMR_AC_VERSION_RMSK)
#define HWIO_QTMR_AC_VERSION_INM(BASE,m)      \
        in_dword_masked(HWIO_QTMR_VERSION_ADDR(BASE), m)
#define HWIO_QTMR_AC_VERSION_MAJOR_BMSK                       0xf0000000
#define HWIO_QTMR_AC_VERSION_MAJOR_SHFT                             0x1c
#define HWIO_QTMR_AC_VERSION_MINOR_BMSK                        0xfff0000
#define HWIO_QTMR_AC_VERSION_MINOR_SHFT                             0x10
#define HWIO_QTMR_AC_VERSION_STEP_BMSK                            0xffff
#define HWIO_QTMR_AC_VERSION_STEP_SHFT                               0x0


/*----------------------------------------------------------------------------
 * MODULE: QTMR_V1
 *--------------------------------------------------------------------------*/

#define HWIO_QTMR_CNTPCT_LO_ADDR(BASE)                          (BASE      + 0x00000000)
#define HWIO_QTMR_CNTPCT_LO_RMSK                          0xffffffff
#define HWIO_QTMR_CNTPCT_LO_IN(BASE)          \
        in_dword_masked(HWIO_QTMR_CNTPCT_LO_ADDR(BASE), HWIO_QTMR_CNTPCT_LO_RMSK)
#define HWIO_QTMR_CNTPCT_LO_INM(BASE,m)      \
        in_dword_masked(HWIO_QTMR_CNTPCT_LO_ADDR(BASE), m)
#define HWIO_QTMR_CNTPCT_LO_CNTPCT_LO_BMSK                0xffffffff
#define HWIO_QTMR_CNTPCT_LO_CNTPCT_LO_SHFT                       0x0

#define HWIO_QTMR_CNTPCT_HI_ADDR(BASE)                          (BASE      + 0x00000004)
#define HWIO_QTMR_CNTPCT_HI_RMSK                          0xffffff
#define HWIO_QTMR_CNTPCT_HI_IN(BASE)          \
        in_dword_masked(HWIO_QTMR_CNTPCT_HI_ADDR(BASE), HWIO_QTMR_CNTPCT_HI_RMSK)
#define HWIO_QTMR_CNTPCT_HI_INM(BASE,m)      \
        in_dword_masked(HWIO_QTMR_CNTPCT_HI_ADDR(BASE), m)
#define HWIO_QTMR_CNTPCT_HI_CNTPCT_HI_BMSK                0xffffff
#define HWIO_QTMR_CNTPCT_HI_CNTPCT_HI_SHFT                       0x0

#define HWIO_QTMR_CNTVCT_LO_ADDR(BASE)                          (BASE      + 0x00000008)
#define HWIO_QTMR_CNTVCT_LO_RMSK                          0xffffffff
#define HWIO_QTMR_CNTVCT_LO_IN(BASE)          \
        in_dword_masked(HWIO_QTMR_CNTVCT_LO_ADDR(BASE), HWIO_QTMR_CNTVCT_LO_RMSK)
#define HWIO_QTMR_CNTVCT_LO_INM(BASE,m)      \
        in_dword_masked(HWIO_QTMR_CNTVCT_LO_ADDR(BASE), m)
#define HWIO_QTMR_CNTVCT_LO_CNTVCT_LO_BMSK                0xffffffff
#define HWIO_QTMR_CNTVCT_LO_CNTVCT_LO_SHFT                       0x0

#define HWIO_QTMR_CNTVCT_HI_ADDR(BASE)                          (BASE      + 0x0000000c)
#define HWIO_QTMR_CNTVCT_HI_RMSK                          0xffffff
#define HWIO_QTMR_CNTVCT_HI_IN(BASE)          \
        in_dword_masked(HWIO_QTMR_CNTVCT_HI_ADDR(BASE), HWIO_QTMR_CNTVCT_HI_RMSK)
#define HWIO_QTMR_CNTVCT_HI_INM(BASE,m)      \
        in_dword_masked(HWIO_QTMR_CNTVCT_HI_ADDR(BASE), m)
#define HWIO_QTMR_CNTVCT_HI_CNTVCT_HI_BMSK                0xffffff
#define HWIO_QTMR_CNTVCT_HI_CNTVCT_HI_SHFT                       0x0

#define HWIO_QTMR_CNTFRQ_ADDR(BASE)                             (BASE      + 0x00000010)
#define HWIO_QTMR_CNTFRQ_RMSK                             0xffffffff
#define HWIO_QTMR_CNTFRQ_IN(BASE)          \
        in_dword_masked(HWIO_QTMR_CNTFRQ_ADDR(BASE), HWIO_QTMR_CNTFRQ_RMSK)
#define HWIO_QTMR_CNTFRQ_INM(BASE,m)      \
        in_dword_masked(HWIO_QTMR_CNTFRQ_ADDR(BASE), m)
#define HWIO_QTMR_CNTFRQ_CNTFRQ_BMSK                      0xffffffff
#define HWIO_QTMR_CNTFRQ_CNTFRQ_SHFT                             0x0

#define HWIO_QTMR_CNTPL0AC_ADDR(BASE)                           (BASE      + 0x00000014)
#define HWIO_QTMR_CNTPL0AC_RMSK                                0x303
#define HWIO_QTMR_CNTPL0AC_IN(BASE)          \
        in_dword_masked(HWIO_QTMR_CNTPL0AC_ADDR(BASE), HWIO_QTMR_CNTPL0AC_RMSK)
#define HWIO_QTMR_CNTPL0AC_INM(BASE,m)      \
        in_dword_masked(HWIO_QTMR_CNTPL0AC_ADDR(BASE, m)
#define HWIO_QTMR_CNTPL0AC_OUT(BASE,v)      \
        out_dword(HWIO_QTMR_CNTPL0AC_ADDR(BASE),v)
#define HWIO_QTMR_CNTPL0AC_OUTM(BASE,m,v) \
        out_dword_masked_ns(HWIO_QTMR_CNTPL0AC_ADDR(BASE,m,v,HWIO_QTMR_CNTPL0AC_IN)
#define HWIO_QTMR_CNTPL0AC_PL0CTEN_BMSK                        0x200
#define HWIO_QTMR_CNTPL0AC_PL0CTEN_SHFT                          0x9
#define HWIO_QTMR_CNTPL0AC_PL0VTEN_BMSK                        0x100
#define HWIO_QTMR_CNTPL0AC_PL0VTEN_SHFT                          0x8
#define HWIO_QTMR_CNTPL0AC_PL0VCTEN_BMSK                         0x2
#define HWIO_QTMR_CNTPL0AC_PL0VCTEN_SHFT                         0x1
#define HWIO_QTMR_CNTPL0AC_PL0PCTEN_BMSK                         0x1
#define HWIO_QTMR_CNTPL0AC_PL0PCTEN_SHFT                         0x0

#define HWIO_QTMR_CNTVOFF_LO_ADDR(BASE)                         (BASE      + 0x00000018)
#define HWIO_QTMR_CNTVOFF_LO_RMSK                         0xffffffff
#define HWIO_QTMR_CNTVOFF_LO_IN(BASE)          \
        in_dword_masked(HWIO_QTMR_CNTVOFF_LO_ADDR(BASE), HWIO_QTMR_CNTVOFF_LO_RMSK)
#define HWIO_QTMR_CNTVOFF_LO_INM(BASE,m)      \
        in_dword_masked(HWIO_QTMR_CNTVOFF_LO_ADDR(BASE), m)
#define HWIO_QTMR_CNTVOFF_LO_CNTVOFF_L0_BMSK              0xffffffff
#define HWIO_QTMR_CNTVOFF_LO_CNTVOFF_L0_SHFT                     0x0

#define HWIO_QTMR_CNTVOFF_HI_ADDR(BASE)                         (BASE      + 0x0000001c)
#define HWIO_QTMR_CNTVOFF_HI_RMSK                         0xffffff
#define HWIO_QTMR_CNTVOFF_HI_IN(BASE)          \
        in_dword_masked(HWIO_QTMR_CNTVOFF_HI_ADDR(BASE), HWIO_QTMR_CNTVOFF_HI_RMSK)
#define HWIO_QTMR_CNTVOFF_HI_INM(BASE,m)      \
        in_dword_masked(HWIO_QTMR_CNTVOFF_HI_ADDR(BASE), m)
#define HWIO_QTMR_CNTVOFF_HI_CNTVOFF_HI_BMSK              0xffffff
#define HWIO_QTMR_CNTVOFF_HI_CNTVOFF_HI_SHFT                     0x0

#define HWIO_QTMR_CNTP_CVAL_LO_ADDR(BASE)                       (BASE      + 0x00000020)
#define HWIO_QTMR_CNTP_CVAL_LO_RMSK                       0xffffffff
#define HWIO_QTMR_CNTP_CVAL_LO_IN(BASE)          \
        in_dword_masked(HWIO_QTMR_CNTP_CVAL_LO_ADDR(BASE), HWIO_QTMR_CNTP_CVAL_LO_RMSK)
#define HWIO_QTMR_CNTP_CVAL_LO_INM(BAE,m)      \
        in_dword_masked(HWIO_QTMR_CNTP_CVAL_LO_ADDR(BASE), m)
#define HWIO_QTMR_CNTP_CVAL_LO_OUT(BASE,v)      \
        out_dword(HWIO_QTMR_CNTP_CVAL_LO_ADDR(BASE),v)
#define HWIO_QTMR_CNTP_CVAL_LO_OUTM(BAE,m,v) \
        out_dword_masked_ns(HWIO_QTMR_CNTP_CVAL_LO_ADDR(BASE),m,v,HWIO_QTMR_CNTP_CVAL_LO_IN)
#define HWIO_QTMR_CNTP_CVAL_LO_CNTP_CVAL_L0_BMSK          0xffffffff
#define HWIO_QTMR_CNTP_CVAL_LO_CNTP_CVAL_L0_SHFT                 0x0

#define HWIO_QTMR_CNTP_CVAL_HI_ADDR(BASE)                       (BASE      + 0x00000024)
#define HWIO_QTMR_CNTP_CVAL_HI_RMSK                       0xffffff
#define HWIO_QTMR_CNTP_CVAL_HI_IN(BASE)          \
        in_dword_masked(HWIO_QTMR_CNTP_CVAL_HI_ADDR(BASE), HWIO_QTMR_CNTP_CVAL_HI_RMSK)
#define HWIO_QTMR_CNTP_CVAL_HI_INM(BASE,m)      \
        in_dword_masked(HWIO_QTMR_CNTP_CVAL_HI_ADDR(BASE), m)
#define HWIO_QTMR_CNTP_CVAL_HI_OUT(BASE,v)      \
        out_dword(HWIO_QTMR_CNTP_CVAL_HI_ADDR(BASE),v)
#define HWIO_QTMR_CNTP_CVAL_HI_OUTM(BASE,m,v) \
        out_dword_masked_ns(HWIO_QTMR_CNTP_CVAL_HI_ADDR(BASE),m,v,HWIO_QTMR_CNTP_CVAL_HI_IN(BASE))
#define HWIO_QTMR_CNTP_CVAL_HI_CNTP_CVAL_HI_BMSK          0xffffff
#define HWIO_QTMR_CNTP_CVAL_HI_CNTP_CVAL_HI_SHFT                 0x0

#define HWIO_QTMR_CNTP_TVAL_ADDR(BASE)                          (BASE      + 0x00000028)
#define HWIO_QTMR_CNTP_TVAL_RMSK                          0xffffffff
#define HWIO_QTMR_CNTP_TVAL_IN(BASE)          \
        in_dword_masked(HWIO_QTMR_CNTP_TVAL_ADDR(BASE), HWIO_QTMR_CNTP_TVAL_RMSK)
#define HWIO_QTMR_CNTP_TVAL_INM(BASE,m)      \
        in_dword_masked(HWIO_QTMR_CNTP_TVAL_ADDR(BASE), m)
#define HWIO_QTMR_CNTP_TVAL_OUT(BASE,v)      \
        out_dword(HWIO_QTMR_CNTP_TVAL_ADDR(BASE),v)
#define HWIO_QTMR_CNTP_TVAL_OUTM(BASE,m,v) \
        out_dword_masked_ns(HWIO_QTMR_CNTP_TVAL_ADDR(BASE),m,v,HWIO_QTMR_CNTP_TVAL_IN(BASE))
#define HWIO_QTMR_CNTP_TVAL_CNTP_TVAL_BMSK                0xffffffff
#define HWIO_QTMR_CNTP_TVAL_CNTP_TVAL_SHFT                       0x0

#define HWIO_QTMR_CNTP_CTL_ADDR(BASE)                           (BASE      + 0x0000002c)
#define HWIO_QTMR_CNTP_CTL_RMSK                                  0x7
#define HWIO_QTMR_CNTP_CTL_IN(BASE)          \
        in_dword_masked(HWIO_QTMR_CNTP_CTL_ADDR(BASE), HWIO_QTMR_CNTP_CTL_RMSK)
#define HWIO_QTMR_CNTP_CTL_INM(BASE,m)      \
        in_dword_masked(HWIO_QTMR_CNTP_CTL_ADDR(BASE), m)
#define HWIO_QTMR_CNTP_CTL_OUT(BASE,v)      \
        out_dword(HWIO_QTMR_CNTP_CTL_ADDR(BASE),v)
#define HWIO_QTMR_CNTP_CTL_OUTM(BASE,m,v) \
        out_dword_masked_ns(HWIO_QTMR_CNTP_CTL_ADDR(BASE),m,v,HWIO_QTMR_CNTP_CTL_IN(BASE))
#define HWIO_QTMR_CNTP_CTL_ISTAT_BMSK                            0x4
#define HWIO_QTMR_CNTP_CTL_ISTAT_SHFT                            0x2
#define HWIO_QTMR_CNTP_CTL_IMSK_BMSK                             0x2
#define HWIO_QTMR_CNTP_CTL_IMSK_SHFT                             0x1
#define HWIO_QTMR_CNTP_CTL_EN_BMSK                               0x1
#define HWIO_QTMR_CNTP_CTL_EN_SHFT                               0x0

#define HWIO_QTMR_CNTV_CVAL_LO_ADDR(BASE)                       (BASE      + 0x00000030)
#define HWIO_QTMR_CNTV_CVAL_LO_RMSK                       0xffffffff
#define HWIO_QTMR_CNTV_CVAL_LO_IN(BASE)          \
        in_dword_masked(HWIO_QTMR_CNTV_CVAL_LO_ADDR(BASE), HWIO_QTMR_CNTV_CVAL_LO_RMSK)
#define HWIO_QTMR_CNTV_CVAL_LO_INM(BASE,m)      \
        in_dword_masked(HWIO_QTMR_CNTV_CVAL_LO_ADDR(BASE), m)
#define HWIO_QTMR_CNTV_CVAL_LO_OUT(BASE,v)      \
        out_dword(HWIO_QTMR_CNTV_CVAL_LO_ADDR(BASE),v)
#define HWIO_QTMR_CNTV_CVAL_LO_OUTM(BASE,m,v) \
        out_dword_masked_ns(HWIO_QTMR_CNTV_CVAL_LO_ADDR(BASE),m,v,HWIO_QTMR_CNTV_CVAL_LO_IN(BASE))
#define HWIO_QTMR_CNTV_CVAL_LO_CNTV_CVAL_L0_BMSK          0xffffffff
#define HWIO_QTMR_CNTV_CVAL_LO_CNTV_CVAL_L0_SHFT                 0x0

#define HWIO_QTMR_CNTV_CVAL_HI_ADDR(BASE)                       (BASE      + 0x00000034)
#define HWIO_QTMR_CNTV_CVAL_HI_RMSK                       0xffffff
#define HWIO_QTMR_CNTV_CVAL_HI_IN(BASE)          \
        in_dword_masked(HWIO_QTMR_CNTV_CVAL_HI_ADDR(BASE), HWIO_QTMR_CNTV_CVAL_HI_RMSK)
#define HWIO_QTMR_CNTV_CVAL_HI_INM(BASE,m)      \
        in_dword_masked(HWIO_QTMR_CNTV_CVAL_HI_ADDR(BASE), m)
#define HWIO_QTMR_CNTV_CVAL_HI_OUT(BASE,v)      \
        out_dword(HWIO_QTMR_CNTV_CVAL_HI_ADDR(BASE),v)
#define HWIO_QTMR_CNTV_CVAL_HI_OUTM(BASE,m,v) \
        out_dword_masked_ns(HWIO_QTMR_CNTV_CVAL_HI_ADDR(BASE),m,v,HWIO_QTMR_CNTV_CVAL_HI_IN(BASE))
#define HWIO_QTMR_CNTV_CVAL_HI_CNTV_CVAL_HI_BMSK          0xffffff
#define HWIO_QTMR_CNTV_CVAL_HI_CNTV_CVAL_HI_SHFT                 0x0

#define HWIO_QTMR_CNTV_TVAL_ADDR(BASE)                          (BASE      + 0x00000038)
#define HWIO_QTMR_CNTV_TVAL_RMSK                          0xffffffff
#define HWIO_QTMR_CNTV_TVAL_IN(BASE)          \
        in_dword_masked(HWIO_QTMR_CNTV_TVAL_ADDR(BASE), HWIO_QTMR_CNTV_TVAL_RMSK)
#define HWIO_QTMR_CNTV_TVAL_INM(BASE,m)      \
        in_dword_masked(HWIO_QTMR_CNTV_TVAL_ADDR(BASE), m)
#define HWIO_QTMR_CNTV_TVAL_OUT(BASE,v)      \
        out_dword(HWIO_QTMR_CNTV_TVAL_ADDR(BASE),v)
#define HWIO_QTMR_CNTV_TVAL_OUTM(BASE,m,v) \
        out_dword_masked_ns(HWIO_QTMR_CNTV_TVAL_ADDR(BASE),m,v,HWIO_QTMR_CNTV_TVAL_IN(BASE))
#define HWIO_QTMR_CNTV_TVAL_CNTV_TVAL_BMSK                0xffffffff
#define HWIO_QTMR_CNTV_TVAL_CNTV_TVAL_SHFT                       0x0

#define HWIO_QTMR_CNTV_CTL_ADDR(BASE)                           (BASE      + 0x0000003c)
#define HWIO_QTMR_CNTV_CTL_RMSK                                  0x7
#define HWIO_QTMR_CNTV_CTL_IN(BASE)          \
        in_dword_masked(HWIO_QTMR_CNTV_CTL_ADDR(BASE), HWIO_QTMR_CNTV_CTL_RMSK)
#define HWIO_QTMR_CNTV_CTL_INM(BASE,m)      \
        in_dword_masked(HWIO_QTMR_CNTV_CTL_ADDR(BASE), m)
#define HWIO_QTMR_CNTV_CTL_OUT(BASE,v)      \
        out_dword(HWIO_QTMR_CNTV_CTL_ADDR(BASE),v)
#define HWIO_QTMR_CNTV_CTL_OUTM(BASE,m,v) \
        out_dword_masked_ns(HWIO_QTMR_CNTV_CTL_ADDR(BASE),m,v,HWIO_QTMR_CNTV_CTL_IN(BASE))
#define HWIO_QTMR_CNTV_CTL_ISTAT_BMSK                            0x4
#define HWIO_QTMR_CNTV_CTL_ISTAT_SHFT                            0x2
#define HWIO_QTMR_CNTV_CTL_IMSK_BMSK                             0x2
#define HWIO_QTMR_CNTV_CTL_IMSK_SHFT                             0x1
#define HWIO_QTMR_CNTV_CTL_EN_BMSK                               0x1
#define HWIO_QTMR_CNTV_CTL_EN_SHFT                               0x0

#define HWIO_QTMR_VERSION_ADDR(BASE)                            (BASE      + 0x00000fd0)
#define HWIO_QTMR_VERSION_RMSK                            0xffffffff
#define HWIO_QTMR_VERSION_IN(BASE)          \
        in_dword_masked(HWIO_QTMR_VERSION_ADDR(BASE), HWIO_QTMR_VERSION_RMSK)
#define HWIO_QTMR_VERSION_INM(m)      \
        in_dword_masked(HWIO_QTMR_VERSION_ADDR(BASE), m)
#define HWIO_QTMR_VERSION_MAJOR_BMSK                      0xf0000000
#define HWIO_QTMR_VERSION_MAJOR_SHFT                            0x1c
#define HWIO_QTMR_VERSION_MINOR_BMSK                       0xfff0000
#define HWIO_QTMR_VERSION_MINOR_SHFT                            0x10
#define HWIO_QTMR_VERSION_STEP_BMSK                           0xffff
#define HWIO_QTMR_VERSION_STEP_SHFT                              0x0




/*----------------------------------------------------------------------------
 * MODULE: SSC_MCC_REGS
 *--------------------------------------------------------------------------*/

#define SSC_MCC_REGS_REG_BASE                                                      (SSC_BASE      + 0x00600000)
#define SSC_MCC_REGS_REG_BASE_PHYS                                                 (SSC_BASE_PHYS + 0x00600000)
#define SSC_MCC_REGS_REG_BASE_OFFS                                                 0x00600000

#define HWIO_SSCAON_SPARE_ADDR(x)                                                  ((x) + 0x00000000)
#define HWIO_SSCAON_SPARE_PHYS(x)                                                  ((x) + 0x00000000)
#define HWIO_SSCAON_SPARE_OFFS                                                     (0x00000000)
#define HWIO_SSCAON_SPARE_RMSK                                                     0xffffffff
#define HWIO_SSCAON_SPARE_POR                                                      0x00000000
#define HWIO_SSCAON_SPARE_POR_RMSK                                                 0xffffffff
#define HWIO_SSCAON_SPARE_ATTR                                                            0x3
#define HWIO_SSCAON_SPARE_IN(x)      \
        in_dword_masked(HWIO_SSCAON_SPARE_ADDR(x), HWIO_SSCAON_SPARE_RMSK)
#define HWIO_SSCAON_SPARE_INM(x, m)      \
        in_dword_masked(HWIO_SSCAON_SPARE_ADDR(x), m)
#define HWIO_SSCAON_SPARE_OUT(x, v)      \
        out_dword(HWIO_SSCAON_SPARE_ADDR(x),v)
#define HWIO_SSCAON_SPARE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SSCAON_SPARE_ADDR(x),m,v,HWIO_SSCAON_SPARE_IN(x))
#define HWIO_SSCAON_SPARE_SSCAON_SSC_SPARE_IN_BMSK                                 0xffff0000
#define HWIO_SSCAON_SPARE_SSCAON_SSC_SPARE_IN_SHFT                                       0x10
#define HWIO_SSCAON_SPARE_SSCAON_SSC_SPARE_OUT_BMSK                                    0xffff
#define HWIO_SSCAON_SPARE_SSCAON_SSC_SPARE_OUT_SHFT                                       0x0

#define HWIO_SSCAON_COUNTER_CFG_ADDR(x)                                            ((x) + 0x00000004)
#define HWIO_SSCAON_COUNTER_CFG_PHYS(x)                                            ((x) + 0x00000004)
#define HWIO_SSCAON_COUNTER_CFG_OFFS                                               (0x00000004)
#define HWIO_SSCAON_COUNTER_CFG_RMSK                                                      0x1
#define HWIO_SSCAON_COUNTER_CFG_POR                                                0x00000000
#define HWIO_SSCAON_COUNTER_CFG_POR_RMSK                                           0xffffffff
#define HWIO_SSCAON_COUNTER_CFG_ATTR                                                      0x3
#define HWIO_SSCAON_COUNTER_CFG_IN(x)      \
        in_dword_masked(HWIO_SSCAON_COUNTER_CFG_ADDR(x), HWIO_SSCAON_COUNTER_CFG_RMSK)
#define HWIO_SSCAON_COUNTER_CFG_INM(x, m)      \
        in_dword_masked(HWIO_SSCAON_COUNTER_CFG_ADDR(x), m)
#define HWIO_SSCAON_COUNTER_CFG_OUT(x, v)      \
        out_dword(HWIO_SSCAON_COUNTER_CFG_ADDR(x),v)
#define HWIO_SSCAON_COUNTER_CFG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SSCAON_COUNTER_CFG_ADDR(x),m,v,HWIO_SSCAON_COUNTER_CFG_IN(x))
#define HWIO_SSCAON_COUNTER_CFG_SSC_SSCAON_QCNTR_EN_BMSK                                  0x1
#define HWIO_SSCAON_COUNTER_CFG_SSC_SSCAON_QCNTR_EN_SHFT                                  0x0

#define HWIO_SSCAON_COUNTER_CTL_STAT_ADDR(x)                                       ((x) + 0x00000008)
#define HWIO_SSCAON_COUNTER_CTL_STAT_PHYS(x)                                       ((x) + 0x00000008)
#define HWIO_SSCAON_COUNTER_CTL_STAT_OFFS                                          (0x00000008)
#define HWIO_SSCAON_COUNTER_CTL_STAT_RMSK                                             0x18003
#define HWIO_SSCAON_COUNTER_CTL_STAT_POR                                           0x00000000
#define HWIO_SSCAON_COUNTER_CTL_STAT_POR_RMSK                                      0xffffffff
#define HWIO_SSCAON_COUNTER_CTL_STAT_ATTR                                                 0x3
#define HWIO_SSCAON_COUNTER_CTL_STAT_IN(x)      \
        in_dword_masked(HWIO_SSCAON_COUNTER_CTL_STAT_ADDR(x), HWIO_SSCAON_COUNTER_CTL_STAT_RMSK)
#define HWIO_SSCAON_COUNTER_CTL_STAT_INM(x, m)      \
        in_dword_masked(HWIO_SSCAON_COUNTER_CTL_STAT_ADDR(x), m)
#define HWIO_SSCAON_COUNTER_CTL_STAT_OUT(x, v)      \
        out_dword(HWIO_SSCAON_COUNTER_CTL_STAT_ADDR(x),v)
#define HWIO_SSCAON_COUNTER_CTL_STAT_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SSCAON_COUNTER_CTL_STAT_ADDR(x),m,v,HWIO_SSCAON_COUNTER_CTL_STAT_IN(x))
#define HWIO_SSCAON_COUNTER_CTL_STAT_SSCAON_SSC_QCNTR_LD_COMPL_BMSK                   0x10000
#define HWIO_SSCAON_COUNTER_CTL_STAT_SSCAON_SSC_QCNTR_LD_COMPL_SHFT                      0x10
#define HWIO_SSCAON_COUNTER_CTL_STAT_SSCAON_SSC_QCNTR_SYNC_COMPL_BMSK                  0x8000
#define HWIO_SSCAON_COUNTER_CTL_STAT_SSCAON_SSC_QCNTR_SYNC_COMPL_SHFT                     0xf
#define HWIO_SSCAON_COUNTER_CTL_STAT_SSC_SSCAON_QCNTR_SYNC_PULSE_BMSK                     0x2
#define HWIO_SSCAON_COUNTER_CTL_STAT_SSC_SSCAON_QCNTR_SYNC_PULSE_SHFT                     0x1
#define HWIO_SSCAON_COUNTER_CTL_STAT_SSC_SSCAON_QCNTR_PRE_LD_BMSK                         0x1
#define HWIO_SSCAON_COUNTER_CTL_STAT_SSC_SSCAON_QCNTR_PRE_LD_SHFT                         0x0

#define HWIO_SSCAON_COUNTER_OFF_ADDR(x)                                            ((x) + 0x0000000c)
#define HWIO_SSCAON_COUNTER_OFF_PHYS(x)                                            ((x) + 0x0000000c)
#define HWIO_SSCAON_COUNTER_OFF_OFFS                                               (0x0000000c)
#define HWIO_SSCAON_COUNTER_OFF_RMSK                                                   0xffff
#define HWIO_SSCAON_COUNTER_OFF_POR                                                0x00000494
#define HWIO_SSCAON_COUNTER_OFF_POR_RMSK                                           0xffffffff
#define HWIO_SSCAON_COUNTER_OFF_ATTR                                                      0x3
#define HWIO_SSCAON_COUNTER_OFF_IN(x)      \
        in_dword_masked(HWIO_SSCAON_COUNTER_OFF_ADDR(x), HWIO_SSCAON_COUNTER_OFF_RMSK)
#define HWIO_SSCAON_COUNTER_OFF_INM(x, m)      \
        in_dword_masked(HWIO_SSCAON_COUNTER_OFF_ADDR(x), m)
#define HWIO_SSCAON_COUNTER_OFF_OUT(x, v)      \
        out_dword(HWIO_SSCAON_COUNTER_OFF_ADDR(x),v)
#define HWIO_SSCAON_COUNTER_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SSCAON_COUNTER_OFF_ADDR(x),m,v,HWIO_SSCAON_COUNTER_OFF_IN(x))
#define HWIO_SSCAON_COUNTER_OFF_SSC_SSCAON_QCNTR_OFFSET_BMSK                           0xffff
#define HWIO_SSCAON_COUNTER_OFF_SSC_SSCAON_QCNTR_OFFSET_SHFT                              0x0

#define HWIO_SSCAON_SLP_TMR_CTL_ADDR(x)                                            ((x) + 0x00000010)
#define HWIO_SSCAON_SLP_TMR_CTL_PHYS(x)                                            ((x) + 0x00000010)
#define HWIO_SSCAON_SLP_TMR_CTL_OFFS                                               (0x00000010)
#define HWIO_SSCAON_SLP_TMR_CTL_RMSK                                                  0x18003
#define HWIO_SSCAON_SLP_TMR_CTL_POR                                                0x00000000
#define HWIO_SSCAON_SLP_TMR_CTL_POR_RMSK                                           0xffffffff
#define HWIO_SSCAON_SLP_TMR_CTL_ATTR                                                      0x3
#define HWIO_SSCAON_SLP_TMR_CTL_IN(x)      \
        in_dword_masked(HWIO_SSCAON_SLP_TMR_CTL_ADDR(x), HWIO_SSCAON_SLP_TMR_CTL_RMSK)
#define HWIO_SSCAON_SLP_TMR_CTL_INM(x, m)      \
        in_dword_masked(HWIO_SSCAON_SLP_TMR_CTL_ADDR(x), m)
#define HWIO_SSCAON_SLP_TMR_CTL_OUT(x, v)      \
        out_dword(HWIO_SSCAON_SLP_TMR_CTL_ADDR(x),v)
#define HWIO_SSCAON_SLP_TMR_CTL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SSCAON_SLP_TMR_CTL_ADDR(x),m,v,HWIO_SSCAON_SLP_TMR_CTL_IN(x))
#define HWIO_SSCAON_SLP_TMR_CTL_SSC_SSCAON_SW_SLP_TMR_INT_RAW_BMSK                    0x10000
#define HWIO_SSCAON_SLP_TMR_CTL_SSC_SSCAON_SW_SLP_TMR_INT_RAW_SHFT                       0x10
#define HWIO_SSCAON_SLP_TMR_CTL_SSC_SSCAON_SW_SLP_TMR_INT_BMSK                         0x8000
#define HWIO_SSCAON_SLP_TMR_CTL_SSC_SSCAON_SW_SLP_TMR_INT_SHFT                            0xf
#define HWIO_SSCAON_SLP_TMR_CTL_SSC_SSCAON_SW_SLP_TMR_EXP_WR_BMSK                         0x2
#define HWIO_SSCAON_SLP_TMR_CTL_SSC_SSCAON_SW_SLP_TMR_EXP_WR_SHFT                         0x1
#define HWIO_SSCAON_SLP_TMR_CTL_SSC_SSCAON_SW_SLP_TMR_INT_CLR_BMSK                        0x1
#define HWIO_SSCAON_SLP_TMR_CTL_SSC_SSCAON_SW_SLP_TMR_INT_CLR_SHFT                        0x0

#define HWIO_SSCAON_SLP_TMR_EXP_LO_ADDR(x)                                         ((x) + 0x00000014)
#define HWIO_SSCAON_SLP_TMR_EXP_LO_PHYS(x)                                         ((x) + 0x00000014)
#define HWIO_SSCAON_SLP_TMR_EXP_LO_OFFS                                            (0x00000014)
#define HWIO_SSCAON_SLP_TMR_EXP_LO_RMSK                                            0xffffffff
#define HWIO_SSCAON_SLP_TMR_EXP_LO_POR                                             0x00000000
#define HWIO_SSCAON_SLP_TMR_EXP_LO_POR_RMSK                                        0xffffffff
#define HWIO_SSCAON_SLP_TMR_EXP_LO_ATTR                                                   0x3
#define HWIO_SSCAON_SLP_TMR_EXP_LO_IN(x)      \
        in_dword_masked(HWIO_SSCAON_SLP_TMR_EXP_LO_ADDR(x), HWIO_SSCAON_SLP_TMR_EXP_LO_RMSK)
#define HWIO_SSCAON_SLP_TMR_EXP_LO_INM(x, m)      \
        in_dword_masked(HWIO_SSCAON_SLP_TMR_EXP_LO_ADDR(x), m)
#define HWIO_SSCAON_SLP_TMR_EXP_LO_OUT(x, v)      \
        out_dword(HWIO_SSCAON_SLP_TMR_EXP_LO_ADDR(x),v)
#define HWIO_SSCAON_SLP_TMR_EXP_LO_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SSCAON_SLP_TMR_EXP_LO_ADDR(x),m,v,HWIO_SSCAON_SLP_TMR_EXP_LO_IN(x))
#define HWIO_SSCAON_SLP_TMR_EXP_LO_SSC_SSCAON_SW_SLP_TMR_EXP_LO_BMSK               0xffffffff
#define HWIO_SSCAON_SLP_TMR_EXP_LO_SSC_SSCAON_SW_SLP_TMR_EXP_LO_SHFT                      0x0

#define HWIO_SSCAON_SLP_TMR_EXP_HI_ADDR(x)                                         ((x) + 0x00000018)
#define HWIO_SSCAON_SLP_TMR_EXP_HI_PHYS(x)                                         ((x) + 0x00000018)
#define HWIO_SSCAON_SLP_TMR_EXP_HI_OFFS                                            (0x00000018)
#define HWIO_SSCAON_SLP_TMR_EXP_HI_RMSK                                              0xffffff
#define HWIO_SSCAON_SLP_TMR_EXP_HI_POR                                             0x00000000
#define HWIO_SSCAON_SLP_TMR_EXP_HI_POR_RMSK                                        0xffffffff
#define HWIO_SSCAON_SLP_TMR_EXP_HI_ATTR                                                   0x3
#define HWIO_SSCAON_SLP_TMR_EXP_HI_IN(x)      \
        in_dword_masked(HWIO_SSCAON_SLP_TMR_EXP_HI_ADDR(x), HWIO_SSCAON_SLP_TMR_EXP_HI_RMSK)
#define HWIO_SSCAON_SLP_TMR_EXP_HI_INM(x, m)      \
        in_dword_masked(HWIO_SSCAON_SLP_TMR_EXP_HI_ADDR(x), m)
#define HWIO_SSCAON_SLP_TMR_EXP_HI_OUT(x, v)      \
        out_dword(HWIO_SSCAON_SLP_TMR_EXP_HI_ADDR(x),v)
#define HWIO_SSCAON_SLP_TMR_EXP_HI_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SSCAON_SLP_TMR_EXP_HI_ADDR(x),m,v,HWIO_SSCAON_SLP_TMR_EXP_HI_IN(x))
#define HWIO_SSCAON_SLP_TMR_EXP_HI_SSC_SSCAON_SW_SLP_TMR_EXP_HI_BMSK                 0xffffff
#define HWIO_SSCAON_SLP_TMR_EXP_HI_SSC_SSCAON_SW_SLP_TMR_EXP_HI_SHFT                      0x0

#define HWIO_SSCAON_SM_CSR0_ADDR(x)                                                ((x) + 0x00000024)
#define HWIO_SSCAON_SM_CSR0_PHYS(x)                                                ((x) + 0x00000024)
#define HWIO_SSCAON_SM_CSR0_OFFS                                                   (0x00000024)
#define HWIO_SSCAON_SM_CSR0_RMSK                                                   0xf0000c07
#define HWIO_SSCAON_SM_CSR0_POR                                                    0x00000404
#define HWIO_SSCAON_SM_CSR0_POR_RMSK                                               0xffffffff
#define HWIO_SSCAON_SM_CSR0_ATTR                                                          0x3
#define HWIO_SSCAON_SM_CSR0_IN(x)      \
        in_dword_masked(HWIO_SSCAON_SM_CSR0_ADDR(x), HWIO_SSCAON_SM_CSR0_RMSK)
#define HWIO_SSCAON_SM_CSR0_INM(x, m)      \
        in_dword_masked(HWIO_SSCAON_SM_CSR0_ADDR(x), m)
#define HWIO_SSCAON_SM_CSR0_OUT(x, v)      \
        out_dword(HWIO_SSCAON_SM_CSR0_ADDR(x),v)
#define HWIO_SSCAON_SM_CSR0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SSCAON_SM_CSR0_ADDR(x),m,v,HWIO_SSCAON_SM_CSR0_IN(x))
#define HWIO_SSCAON_SM_CSR0_SSCAON_SSC_PMU_AON_SM_BMSK                             0xf0000000
#define HWIO_SSCAON_SM_CSR0_SSCAON_SSC_PMU_AON_SM_SHFT                                   0x1c
#define HWIO_SSCAON_SM_CSR0_SSC_SSCAON_PWRDN_REQ_BMSK                                   0x800
#define HWIO_SSCAON_SM_CSR0_SSC_SSCAON_PWRDN_REQ_SHFT                                     0xb
#define HWIO_SSCAON_SM_CSR0_SSC_PEEL_MODE_OVRD_BMSK                                     0x400
#define HWIO_SSCAON_SM_CSR0_SSC_PEEL_MODE_OVRD_SHFT                                       0xa
#define HWIO_SSCAON_SM_CSR0_SSC_SSCAON_FAST_WAKEUP_EN_BMSK                                0x4
#define HWIO_SSCAON_SM_CSR0_SSC_SSCAON_FAST_WAKEUP_EN_SHFT                                0x2
#define HWIO_SSCAON_SM_CSR0_SSC_SSCAON_NO_RET_MSM_BMSK                                    0x2
#define HWIO_SSCAON_SM_CSR0_SSC_SSCAON_NO_RET_MSM_SHFT                                    0x1
#define HWIO_SSCAON_SM_CSR0_SSC_SSCAON_NO_RETENTION_BMSK                                  0x1
#define HWIO_SSCAON_SM_CSR0_SSC_SSCAON_NO_RETENTION_SHFT                                  0x0

#define HWIO_SSCAON_SM_CSR1_ADDR(x)                                                ((x) + 0x00000028)
#define HWIO_SSCAON_SM_CSR1_PHYS(x)                                                ((x) + 0x00000028)
#define HWIO_SSCAON_SM_CSR1_OFFS                                                   (0x00000028)
#define HWIO_SSCAON_SM_CSR1_RMSK                                                        0x1ff
#define HWIO_SSCAON_SM_CSR1_POR                                                    0x00000000
#define HWIO_SSCAON_SM_CSR1_POR_RMSK                                               0xffffffff
#define HWIO_SSCAON_SM_CSR1_ATTR                                                          0x3
#define HWIO_SSCAON_SM_CSR1_IN(x)      \
        in_dword_masked(HWIO_SSCAON_SM_CSR1_ADDR(x), HWIO_SSCAON_SM_CSR1_RMSK)
#define HWIO_SSCAON_SM_CSR1_INM(x, m)      \
        in_dword_masked(HWIO_SSCAON_SM_CSR1_ADDR(x), m)
#define HWIO_SSCAON_SM_CSR1_OUT(x, v)      \
        out_dword(HWIO_SSCAON_SM_CSR1_ADDR(x),v)
#define HWIO_SSCAON_SM_CSR1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SSCAON_SM_CSR1_ADDR(x),m,v,HWIO_SSCAON_SM_CSR1_IN(x))
#define HWIO_SSCAON_SM_CSR1_SSC_SSCAON_PEEL_TMR_EN_BMSK                                 0x100
#define HWIO_SSCAON_SM_CSR1_SSC_SSCAON_PEEL_TMR_EN_SHFT                                   0x8
#define HWIO_SSCAON_SM_CSR1_SSC_SSCAON_PEEL_LOCKDLY_WR_BMSK                              0x80
#define HWIO_SSCAON_SM_CSR1_SSC_SSCAON_PEEL_LOCKDLY_WR_SHFT                               0x7
#define HWIO_SSCAON_SM_CSR1_SSC_SSCAON_PEEL_LOCKDLY_BMSK                                 0x7f
#define HWIO_SSCAON_SM_CSR1_SSC_SSCAON_PEEL_LOCKDLY_SHFT                                  0x0

#define HWIO_SSCAON_SWITCHER_DLY_ADDR(x)                                           ((x) + 0x0000002c)
#define HWIO_SSCAON_SWITCHER_DLY_PHYS(x)                                           ((x) + 0x0000002c)
#define HWIO_SSCAON_SWITCHER_DLY_OFFS                                              (0x0000002c)
#define HWIO_SSCAON_SWITCHER_DLY_RMSK                                              0xffffffff
#define HWIO_SSCAON_SWITCHER_DLY_POR                                               0x00000020
#define HWIO_SSCAON_SWITCHER_DLY_POR_RMSK                                          0xffffffff
#define HWIO_SSCAON_SWITCHER_DLY_ATTR                                                     0x3
#define HWIO_SSCAON_SWITCHER_DLY_IN(x)      \
        in_dword_masked(HWIO_SSCAON_SWITCHER_DLY_ADDR(x), HWIO_SSCAON_SWITCHER_DLY_RMSK)
#define HWIO_SSCAON_SWITCHER_DLY_INM(x, m)      \
        in_dword_masked(HWIO_SSCAON_SWITCHER_DLY_ADDR(x), m)
#define HWIO_SSCAON_SWITCHER_DLY_OUT(x, v)      \
        out_dword(HWIO_SSCAON_SWITCHER_DLY_ADDR(x),v)
#define HWIO_SSCAON_SWITCHER_DLY_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SSCAON_SWITCHER_DLY_ADDR(x),m,v,HWIO_SSCAON_SWITCHER_DLY_IN(x))
#define HWIO_SSCAON_SWITCHER_DLY_SSC_SSCAON_SWITCHER_DLY_WR_BMSK                   0x80000000
#define HWIO_SSCAON_SWITCHER_DLY_SSC_SSCAON_SWITCHER_DLY_WR_SHFT                         0x1f
#define HWIO_SSCAON_SWITCHER_DLY_SSC_SSCAON_PBS_WAIT_DLY_BMSK                      0x7fff0000
#define HWIO_SSCAON_SWITCHER_DLY_SSC_SSCAON_PBS_WAIT_DLY_SHFT                            0x10
#define HWIO_SSCAON_SWITCHER_DLY_SSC_SSCAON_SWITCHER_DLY_BMSK                          0xffff
#define HWIO_SSCAON_SWITCHER_DLY_SSC_SSCAON_SWITCHER_DLY_SHFT                             0x0

#define HWIO_SSCAON_INT_ISO_ADDR(x)                                                ((x) + 0x00000030)
#define HWIO_SSCAON_INT_ISO_PHYS(x)                                                ((x) + 0x00000030)
#define HWIO_SSCAON_INT_ISO_OFFS                                                   (0x00000030)
#define HWIO_SSCAON_INT_ISO_RMSK                                                          0x1
#define HWIO_SSCAON_INT_ISO_POR                                                    0x00000000
#define HWIO_SSCAON_INT_ISO_POR_RMSK                                               0xffffffff
#define HWIO_SSCAON_INT_ISO_ATTR                                                          0x2
#define HWIO_SSCAON_INT_ISO_OUT(x, v)      \
        out_dword(HWIO_SSCAON_INT_ISO_ADDR(x),v)
#define HWIO_SSCAON_INT_ISO_SSC_SSCAON_INT_ISO_REQ_BMSK                                   0x1
#define HWIO_SSCAON_INT_ISO_SSC_SSCAON_INT_ISO_REQ_SHFT                                   0x0

#define HWIO_SSCAON_INT_CLR0_ADDR(x)                                               ((x) + 0x00000034)
#define HWIO_SSCAON_INT_CLR0_PHYS(x)                                               ((x) + 0x00000034)
#define HWIO_SSCAON_INT_CLR0_OFFS                                                  (0x00000034)
#define HWIO_SSCAON_INT_CLR0_RMSK                                                  0xffffffff
#define HWIO_SSCAON_INT_CLR0_POR                                                   0x00000000
#define HWIO_SSCAON_INT_CLR0_POR_RMSK                                              0xffffffff
#define HWIO_SSCAON_INT_CLR0_ATTR                                                         0x2
#define HWIO_SSCAON_INT_CLR0_OUT(x, v)      \
        out_dword(HWIO_SSCAON_INT_CLR0_ADDR(x),v)
#define HWIO_SSCAON_INT_CLR0_SSC_SSCAON_INT_CLR0_BMSK                              0xffffffff
#define HWIO_SSCAON_INT_CLR0_SSC_SSCAON_INT_CLR0_SHFT                                     0x0

#define HWIO_SSCAON_INT_CLR1_ADDR(x)                                               ((x) + 0x00000038)
#define HWIO_SSCAON_INT_CLR1_PHYS(x)                                               ((x) + 0x00000038)
#define HWIO_SSCAON_INT_CLR1_OFFS                                                  (0x00000038)
#define HWIO_SSCAON_INT_CLR1_RMSK                                                  0xffffffff
#define HWIO_SSCAON_INT_CLR1_POR                                                   0x00000000
#define HWIO_SSCAON_INT_CLR1_POR_RMSK                                              0xffffffff
#define HWIO_SSCAON_INT_CLR1_ATTR                                                         0x2
#define HWIO_SSCAON_INT_CLR1_OUT(x, v)      \
        out_dword(HWIO_SSCAON_INT_CLR1_ADDR(x),v)
#define HWIO_SSCAON_INT_CLR1_SSC_SSCAON_INT_CLR1_BMSK                              0xffffffff
#define HWIO_SSCAON_INT_CLR1_SSC_SSCAON_INT_CLR1_SHFT                                     0x0

#define HWIO_SSCAON_INT_CLR2_ADDR(x)                                               ((x) + 0x0000003c)
#define HWIO_SSCAON_INT_CLR2_PHYS(x)                                               ((x) + 0x0000003c)
#define HWIO_SSCAON_INT_CLR2_OFFS                                                  (0x0000003c)
#define HWIO_SSCAON_INT_CLR2_RMSK                                                  0xffffffff
#define HWIO_SSCAON_INT_CLR2_POR                                                   0x00000000
#define HWIO_SSCAON_INT_CLR2_POR_RMSK                                              0xffffffff
#define HWIO_SSCAON_INT_CLR2_ATTR                                                         0x2
#define HWIO_SSCAON_INT_CLR2_OUT(x, v)      \
        out_dword(HWIO_SSCAON_INT_CLR2_ADDR(x),v)
#define HWIO_SSCAON_INT_CLR2_SSC_SSCAON_INT_CLR2_BMSK                              0xffffffff
#define HWIO_SSCAON_INT_CLR2_SSC_SSCAON_INT_CLR2_SHFT                                     0x0

#define HWIO_SSCAON_INT_POL0_ADDR(x)                                               ((x) + 0x00000040)
#define HWIO_SSCAON_INT_POL0_PHYS(x)                                               ((x) + 0x00000040)
#define HWIO_SSCAON_INT_POL0_OFFS                                                  (0x00000040)
#define HWIO_SSCAON_INT_POL0_RMSK                                                  0xffffffff
#define HWIO_SSCAON_INT_POL0_POR                                                   0x00000000
#define HWIO_SSCAON_INT_POL0_POR_RMSK                                              0xffffffff
#define HWIO_SSCAON_INT_POL0_ATTR                                                         0x3
#define HWIO_SSCAON_INT_POL0_IN(x)      \
        in_dword_masked(HWIO_SSCAON_INT_POL0_ADDR(x), HWIO_SSCAON_INT_POL0_RMSK)
#define HWIO_SSCAON_INT_POL0_INM(x, m)      \
        in_dword_masked(HWIO_SSCAON_INT_POL0_ADDR(x), m)
#define HWIO_SSCAON_INT_POL0_OUT(x, v)      \
        out_dword(HWIO_SSCAON_INT_POL0_ADDR(x),v)
#define HWIO_SSCAON_INT_POL0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SSCAON_INT_POL0_ADDR(x),m,v,HWIO_SSCAON_INT_POL0_IN(x))
#define HWIO_SSCAON_INT_POL0_SSC_SSCAON_INT_POL0_BMSK                              0xffffffff
#define HWIO_SSCAON_INT_POL0_SSC_SSCAON_INT_POL0_SHFT                                     0x0

#define HWIO_SSCAON_INT_POL1_ADDR(x)                                               ((x) + 0x00000044)
#define HWIO_SSCAON_INT_POL1_PHYS(x)                                               ((x) + 0x00000044)
#define HWIO_SSCAON_INT_POL1_OFFS                                                  (0x00000044)
#define HWIO_SSCAON_INT_POL1_RMSK                                                  0xffffffff
#define HWIO_SSCAON_INT_POL1_POR                                                   0x00000000
#define HWIO_SSCAON_INT_POL1_POR_RMSK                                              0xffffffff
#define HWIO_SSCAON_INT_POL1_ATTR                                                         0x3
#define HWIO_SSCAON_INT_POL1_IN(x)      \
        in_dword_masked(HWIO_SSCAON_INT_POL1_ADDR(x), HWIO_SSCAON_INT_POL1_RMSK)
#define HWIO_SSCAON_INT_POL1_INM(x, m)      \
        in_dword_masked(HWIO_SSCAON_INT_POL1_ADDR(x), m)
#define HWIO_SSCAON_INT_POL1_OUT(x, v)      \
        out_dword(HWIO_SSCAON_INT_POL1_ADDR(x),v)
#define HWIO_SSCAON_INT_POL1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SSCAON_INT_POL1_ADDR(x),m,v,HWIO_SSCAON_INT_POL1_IN(x))
#define HWIO_SSCAON_INT_POL1_SSC_SSCAON_INT_POL1_BMSK                              0xffffffff
#define HWIO_SSCAON_INT_POL1_SSC_SSCAON_INT_POL1_SHFT                                     0x0

#define HWIO_SSCAON_INT_POL2_ADDR(x)                                               ((x) + 0x00000048)
#define HWIO_SSCAON_INT_POL2_PHYS(x)                                               ((x) + 0x00000048)
#define HWIO_SSCAON_INT_POL2_OFFS                                                  (0x00000048)
#define HWIO_SSCAON_INT_POL2_RMSK                                                  0xffffffff
#define HWIO_SSCAON_INT_POL2_POR                                                   0x00000000
#define HWIO_SSCAON_INT_POL2_POR_RMSK                                              0xffffffff
#define HWIO_SSCAON_INT_POL2_ATTR                                                         0x3
#define HWIO_SSCAON_INT_POL2_IN(x)      \
        in_dword_masked(HWIO_SSCAON_INT_POL2_ADDR(x), HWIO_SSCAON_INT_POL2_RMSK)
#define HWIO_SSCAON_INT_POL2_INM(x, m)      \
        in_dword_masked(HWIO_SSCAON_INT_POL2_ADDR(x), m)
#define HWIO_SSCAON_INT_POL2_OUT(x, v)      \
        out_dword(HWIO_SSCAON_INT_POL2_ADDR(x),v)
#define HWIO_SSCAON_INT_POL2_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SSCAON_INT_POL2_ADDR(x),m,v,HWIO_SSCAON_INT_POL2_IN(x))
#define HWIO_SSCAON_INT_POL2_SSC_SSCAON_INT_POL2_BMSK                              0xffffffff
#define HWIO_SSCAON_INT_POL2_SSC_SSCAON_INT_POL2_SHFT                                     0x0

#define HWIO_SSCAON_INT_POS_EDGE_EN0_ADDR(x)                                       ((x) + 0x0000004c)
#define HWIO_SSCAON_INT_POS_EDGE_EN0_PHYS(x)                                       ((x) + 0x0000004c)
#define HWIO_SSCAON_INT_POS_EDGE_EN0_OFFS                                          (0x0000004c)
#define HWIO_SSCAON_INT_POS_EDGE_EN0_RMSK                                          0xffffffff
#define HWIO_SSCAON_INT_POS_EDGE_EN0_POR                                           0x00000000
#define HWIO_SSCAON_INT_POS_EDGE_EN0_POR_RMSK                                      0xffffffff
#define HWIO_SSCAON_INT_POS_EDGE_EN0_ATTR                                                 0x3
#define HWIO_SSCAON_INT_POS_EDGE_EN0_IN(x)      \
        in_dword_masked(HWIO_SSCAON_INT_POS_EDGE_EN0_ADDR(x), HWIO_SSCAON_INT_POS_EDGE_EN0_RMSK)
#define HWIO_SSCAON_INT_POS_EDGE_EN0_INM(x, m)      \
        in_dword_masked(HWIO_SSCAON_INT_POS_EDGE_EN0_ADDR(x), m)
#define HWIO_SSCAON_INT_POS_EDGE_EN0_OUT(x, v)      \
        out_dword(HWIO_SSCAON_INT_POS_EDGE_EN0_ADDR(x),v)
#define HWIO_SSCAON_INT_POS_EDGE_EN0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SSCAON_INT_POS_EDGE_EN0_ADDR(x),m,v,HWIO_SSCAON_INT_POS_EDGE_EN0_IN(x))
#define HWIO_SSCAON_INT_POS_EDGE_EN0_SSC_SSCAON_INT_POS_EDGE_EN0_BMSK              0xffffffff
#define HWIO_SSCAON_INT_POS_EDGE_EN0_SSC_SSCAON_INT_POS_EDGE_EN0_SHFT                     0x0

#define HWIO_SSCAON_INT_POS_EDGE_EN1_ADDR(x)                                       ((x) + 0x00000050)
#define HWIO_SSCAON_INT_POS_EDGE_EN1_PHYS(x)                                       ((x) + 0x00000050)
#define HWIO_SSCAON_INT_POS_EDGE_EN1_OFFS                                          (0x00000050)
#define HWIO_SSCAON_INT_POS_EDGE_EN1_RMSK                                          0xffffffff
#define HWIO_SSCAON_INT_POS_EDGE_EN1_POR                                           0x00000000
#define HWIO_SSCAON_INT_POS_EDGE_EN1_POR_RMSK                                      0xffffffff
#define HWIO_SSCAON_INT_POS_EDGE_EN1_ATTR                                                 0x3
#define HWIO_SSCAON_INT_POS_EDGE_EN1_IN(x)      \
        in_dword_masked(HWIO_SSCAON_INT_POS_EDGE_EN1_ADDR(x), HWIO_SSCAON_INT_POS_EDGE_EN1_RMSK)
#define HWIO_SSCAON_INT_POS_EDGE_EN1_INM(x, m)      \
        in_dword_masked(HWIO_SSCAON_INT_POS_EDGE_EN1_ADDR(x), m)
#define HWIO_SSCAON_INT_POS_EDGE_EN1_OUT(x, v)      \
        out_dword(HWIO_SSCAON_INT_POS_EDGE_EN1_ADDR(x),v)
#define HWIO_SSCAON_INT_POS_EDGE_EN1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SSCAON_INT_POS_EDGE_EN1_ADDR(x),m,v,HWIO_SSCAON_INT_POS_EDGE_EN1_IN(x))
#define HWIO_SSCAON_INT_POS_EDGE_EN1_SSC_SSCAON_INT_POS_EDGE_EN1_BMSK              0xffffffff
#define HWIO_SSCAON_INT_POS_EDGE_EN1_SSC_SSCAON_INT_POS_EDGE_EN1_SHFT                     0x0

#define HWIO_SSCAON_INT_POS_EDGE_EN2_ADDR(x)                                       ((x) + 0x00000054)
#define HWIO_SSCAON_INT_POS_EDGE_EN2_PHYS(x)                                       ((x) + 0x00000054)
#define HWIO_SSCAON_INT_POS_EDGE_EN2_OFFS                                          (0x00000054)
#define HWIO_SSCAON_INT_POS_EDGE_EN2_RMSK                                          0xffffffff
#define HWIO_SSCAON_INT_POS_EDGE_EN2_POR                                           0x00000000
#define HWIO_SSCAON_INT_POS_EDGE_EN2_POR_RMSK                                      0xffffffff
#define HWIO_SSCAON_INT_POS_EDGE_EN2_ATTR                                                 0x3
#define HWIO_SSCAON_INT_POS_EDGE_EN2_IN(x)      \
        in_dword_masked(HWIO_SSCAON_INT_POS_EDGE_EN2_ADDR(x), HWIO_SSCAON_INT_POS_EDGE_EN2_RMSK)
#define HWIO_SSCAON_INT_POS_EDGE_EN2_INM(x, m)      \
        in_dword_masked(HWIO_SSCAON_INT_POS_EDGE_EN2_ADDR(x), m)
#define HWIO_SSCAON_INT_POS_EDGE_EN2_OUT(x, v)      \
        out_dword(HWIO_SSCAON_INT_POS_EDGE_EN2_ADDR(x),v)
#define HWIO_SSCAON_INT_POS_EDGE_EN2_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SSCAON_INT_POS_EDGE_EN2_ADDR(x),m,v,HWIO_SSCAON_INT_POS_EDGE_EN2_IN(x))
#define HWIO_SSCAON_INT_POS_EDGE_EN2_SSC_SSCAON_INT_POS_EDGE_EN2_BMSK              0xffffffff
#define HWIO_SSCAON_INT_POS_EDGE_EN2_SSC_SSCAON_INT_POS_EDGE_EN2_SHFT                     0x0

#define HWIO_SSCAON_INT_NEG_EDGE_EN0_ADDR(x)                                       ((x) + 0x00000058)
#define HWIO_SSCAON_INT_NEG_EDGE_EN0_PHYS(x)                                       ((x) + 0x00000058)
#define HWIO_SSCAON_INT_NEG_EDGE_EN0_OFFS                                          (0x00000058)
#define HWIO_SSCAON_INT_NEG_EDGE_EN0_RMSK                                          0xffffffff
#define HWIO_SSCAON_INT_NEG_EDGE_EN0_POR                                           0x00000000
#define HWIO_SSCAON_INT_NEG_EDGE_EN0_POR_RMSK                                      0xffffffff
#define HWIO_SSCAON_INT_NEG_EDGE_EN0_ATTR                                                 0x3
#define HWIO_SSCAON_INT_NEG_EDGE_EN0_IN(x)      \
        in_dword_masked(HWIO_SSCAON_INT_NEG_EDGE_EN0_ADDR(x), HWIO_SSCAON_INT_NEG_EDGE_EN0_RMSK)
#define HWIO_SSCAON_INT_NEG_EDGE_EN0_INM(x, m)      \
        in_dword_masked(HWIO_SSCAON_INT_NEG_EDGE_EN0_ADDR(x), m)
#define HWIO_SSCAON_INT_NEG_EDGE_EN0_OUT(x, v)      \
        out_dword(HWIO_SSCAON_INT_NEG_EDGE_EN0_ADDR(x),v)
#define HWIO_SSCAON_INT_NEG_EDGE_EN0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SSCAON_INT_NEG_EDGE_EN0_ADDR(x),m,v,HWIO_SSCAON_INT_NEG_EDGE_EN0_IN(x))
#define HWIO_SSCAON_INT_NEG_EDGE_EN0_SSC_SSCAON_INT_NEG_EDGE_EN0_BMSK              0xffffffff
#define HWIO_SSCAON_INT_NEG_EDGE_EN0_SSC_SSCAON_INT_NEG_EDGE_EN0_SHFT                     0x0

#define HWIO_SSCAON_INT_NEG_EDGE_EN1_ADDR(x)                                       ((x) + 0x0000005c)
#define HWIO_SSCAON_INT_NEG_EDGE_EN1_PHYS(x)                                       ((x) + 0x0000005c)
#define HWIO_SSCAON_INT_NEG_EDGE_EN1_OFFS                                          (0x0000005c)
#define HWIO_SSCAON_INT_NEG_EDGE_EN1_RMSK                                          0xffffffff
#define HWIO_SSCAON_INT_NEG_EDGE_EN1_POR                                           0x00000000
#define HWIO_SSCAON_INT_NEG_EDGE_EN1_POR_RMSK                                      0xffffffff
#define HWIO_SSCAON_INT_NEG_EDGE_EN1_ATTR                                                 0x3
#define HWIO_SSCAON_INT_NEG_EDGE_EN1_IN(x)      \
        in_dword_masked(HWIO_SSCAON_INT_NEG_EDGE_EN1_ADDR(x), HWIO_SSCAON_INT_NEG_EDGE_EN1_RMSK)
#define HWIO_SSCAON_INT_NEG_EDGE_EN1_INM(x, m)      \
        in_dword_masked(HWIO_SSCAON_INT_NEG_EDGE_EN1_ADDR(x), m)
#define HWIO_SSCAON_INT_NEG_EDGE_EN1_OUT(x, v)      \
        out_dword(HWIO_SSCAON_INT_NEG_EDGE_EN1_ADDR(x),v)
#define HWIO_SSCAON_INT_NEG_EDGE_EN1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SSCAON_INT_NEG_EDGE_EN1_ADDR(x),m,v,HWIO_SSCAON_INT_NEG_EDGE_EN1_IN(x))
#define HWIO_SSCAON_INT_NEG_EDGE_EN1_SSC_SSCAON_INT_NEG_EDGE_EN1_BMSK              0xffffffff
#define HWIO_SSCAON_INT_NEG_EDGE_EN1_SSC_SSCAON_INT_NEG_EDGE_EN1_SHFT                     0x0

#define HWIO_SSCAON_INT_NEG_EDGE_EN2_ADDR(x)                                       ((x) + 0x00000060)
#define HWIO_SSCAON_INT_NEG_EDGE_EN2_PHYS(x)                                       ((x) + 0x00000060)
#define HWIO_SSCAON_INT_NEG_EDGE_EN2_OFFS                                          (0x00000060)
#define HWIO_SSCAON_INT_NEG_EDGE_EN2_RMSK                                          0xffffffff
#define HWIO_SSCAON_INT_NEG_EDGE_EN2_POR                                           0x00000000
#define HWIO_SSCAON_INT_NEG_EDGE_EN2_POR_RMSK                                      0xffffffff
#define HWIO_SSCAON_INT_NEG_EDGE_EN2_ATTR                                                 0x3
#define HWIO_SSCAON_INT_NEG_EDGE_EN2_IN(x)      \
        in_dword_masked(HWIO_SSCAON_INT_NEG_EDGE_EN2_ADDR(x), HWIO_SSCAON_INT_NEG_EDGE_EN2_RMSK)
#define HWIO_SSCAON_INT_NEG_EDGE_EN2_INM(x, m)      \
        in_dword_masked(HWIO_SSCAON_INT_NEG_EDGE_EN2_ADDR(x), m)
#define HWIO_SSCAON_INT_NEG_EDGE_EN2_OUT(x, v)      \
        out_dword(HWIO_SSCAON_INT_NEG_EDGE_EN2_ADDR(x),v)
#define HWIO_SSCAON_INT_NEG_EDGE_EN2_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SSCAON_INT_NEG_EDGE_EN2_ADDR(x),m,v,HWIO_SSCAON_INT_NEG_EDGE_EN2_IN(x))
#define HWIO_SSCAON_INT_NEG_EDGE_EN2_SSC_SSCAON_INT_NEG_EDGE_EN2_BMSK              0xffffffff
#define HWIO_SSCAON_INT_NEG_EDGE_EN2_SSC_SSCAON_INT_NEG_EDGE_EN2_SHFT                     0x0

#define HWIO_SSCAON_INT_EN0_ADDR(x)                                                ((x) + 0x00000064)
#define HWIO_SSCAON_INT_EN0_PHYS(x)                                                ((x) + 0x00000064)
#define HWIO_SSCAON_INT_EN0_OFFS                                                   (0x00000064)
#define HWIO_SSCAON_INT_EN0_RMSK                                                   0xffffffff
#define HWIO_SSCAON_INT_EN0_POR                                                    0x00000000
#define HWIO_SSCAON_INT_EN0_POR_RMSK                                               0xffffffff
#define HWIO_SSCAON_INT_EN0_ATTR                                                          0x3
#define HWIO_SSCAON_INT_EN0_IN(x)      \
        in_dword_masked(HWIO_SSCAON_INT_EN0_ADDR(x), HWIO_SSCAON_INT_EN0_RMSK)
#define HWIO_SSCAON_INT_EN0_INM(x, m)      \
        in_dword_masked(HWIO_SSCAON_INT_EN0_ADDR(x), m)
#define HWIO_SSCAON_INT_EN0_OUT(x, v)      \
        out_dword(HWIO_SSCAON_INT_EN0_ADDR(x),v)
#define HWIO_SSCAON_INT_EN0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SSCAON_INT_EN0_ADDR(x),m,v,HWIO_SSCAON_INT_EN0_IN(x))
#define HWIO_SSCAON_INT_EN0_SSC_SSCAON_INT_EN0_BMSK                                0xffffffff
#define HWIO_SSCAON_INT_EN0_SSC_SSCAON_INT_EN0_SHFT                                       0x0

#define HWIO_SSCAON_INT_EN1_ADDR(x)                                                ((x) + 0x00000068)
#define HWIO_SSCAON_INT_EN1_PHYS(x)                                                ((x) + 0x00000068)
#define HWIO_SSCAON_INT_EN1_OFFS                                                   (0x00000068)
#define HWIO_SSCAON_INT_EN1_RMSK                                                   0xffffffff
#define HWIO_SSCAON_INT_EN1_POR                                                    0x00000000
#define HWIO_SSCAON_INT_EN1_POR_RMSK                                               0xffffffff
#define HWIO_SSCAON_INT_EN1_ATTR                                                          0x3
#define HWIO_SSCAON_INT_EN1_IN(x)      \
        in_dword_masked(HWIO_SSCAON_INT_EN1_ADDR(x), HWIO_SSCAON_INT_EN1_RMSK)
#define HWIO_SSCAON_INT_EN1_INM(x, m)      \
        in_dword_masked(HWIO_SSCAON_INT_EN1_ADDR(x), m)
#define HWIO_SSCAON_INT_EN1_OUT(x, v)      \
        out_dword(HWIO_SSCAON_INT_EN1_ADDR(x),v)
#define HWIO_SSCAON_INT_EN1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SSCAON_INT_EN1_ADDR(x),m,v,HWIO_SSCAON_INT_EN1_IN(x))
#define HWIO_SSCAON_INT_EN1_SSC_SSCAON_INT_EN1_BMSK                                0xffffffff
#define HWIO_SSCAON_INT_EN1_SSC_SSCAON_INT_EN1_SHFT                                       0x0

#define HWIO_SSCAON_INT_EN2_ADDR(x)                                                ((x) + 0x0000006c)
#define HWIO_SSCAON_INT_EN2_PHYS(x)                                                ((x) + 0x0000006c)
#define HWIO_SSCAON_INT_EN2_OFFS                                                   (0x0000006c)
#define HWIO_SSCAON_INT_EN2_RMSK                                                   0xffffffff
#define HWIO_SSCAON_INT_EN2_POR                                                    0x00000000
#define HWIO_SSCAON_INT_EN2_POR_RMSK                                               0xffffffff
#define HWIO_SSCAON_INT_EN2_ATTR                                                          0x3
#define HWIO_SSCAON_INT_EN2_IN(x)      \
        in_dword_masked(HWIO_SSCAON_INT_EN2_ADDR(x), HWIO_SSCAON_INT_EN2_RMSK)
#define HWIO_SSCAON_INT_EN2_INM(x, m)      \
        in_dword_masked(HWIO_SSCAON_INT_EN2_ADDR(x), m)
#define HWIO_SSCAON_INT_EN2_OUT(x, v)      \
        out_dword(HWIO_SSCAON_INT_EN2_ADDR(x),v)
#define HWIO_SSCAON_INT_EN2_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SSCAON_INT_EN2_ADDR(x),m,v,HWIO_SSCAON_INT_EN2_IN(x))
#define HWIO_SSCAON_INT_EN2_SSC_SSCAON_INT_EN2_BMSK                                0xffffffff
#define HWIO_SSCAON_INT_EN2_SSC_SSCAON_INT_EN2_SHFT                                       0x0

#define HWIO_SSCAON_INT_STAT0_ADDR(x)                                              ((x) + 0x00000070)
#define HWIO_SSCAON_INT_STAT0_PHYS(x)                                              ((x) + 0x00000070)
#define HWIO_SSCAON_INT_STAT0_OFFS                                                 (0x00000070)
#define HWIO_SSCAON_INT_STAT0_RMSK                                                 0xffffffff
#define HWIO_SSCAON_INT_STAT0_POR                                                  0x00000000
#define HWIO_SSCAON_INT_STAT0_POR_RMSK                                             0xffffffff
#define HWIO_SSCAON_INT_STAT0_ATTR                                                        0x1
#define HWIO_SSCAON_INT_STAT0_IN(x)      \
        in_dword_masked(HWIO_SSCAON_INT_STAT0_ADDR(x), HWIO_SSCAON_INT_STAT0_RMSK)
#define HWIO_SSCAON_INT_STAT0_INM(x, m)      \
        in_dword_masked(HWIO_SSCAON_INT_STAT0_ADDR(x), m)
#define HWIO_SSCAON_INT_STAT0_SSC_SSCAON_INT_STAT0_BMSK                            0xffffffff
#define HWIO_SSCAON_INT_STAT0_SSC_SSCAON_INT_STAT0_SHFT                                   0x0

#define HWIO_SSCAON_INT_STAT1_ADDR(x)                                              ((x) + 0x00000074)
#define HWIO_SSCAON_INT_STAT1_PHYS(x)                                              ((x) + 0x00000074)
#define HWIO_SSCAON_INT_STAT1_OFFS                                                 (0x00000074)
#define HWIO_SSCAON_INT_STAT1_RMSK                                                 0xffffffff
#define HWIO_SSCAON_INT_STAT1_POR                                                  0x00000000
#define HWIO_SSCAON_INT_STAT1_POR_RMSK                                             0xffffffff
#define HWIO_SSCAON_INT_STAT1_ATTR                                                        0x1
#define HWIO_SSCAON_INT_STAT1_IN(x)      \
        in_dword_masked(HWIO_SSCAON_INT_STAT1_ADDR(x), HWIO_SSCAON_INT_STAT1_RMSK)
#define HWIO_SSCAON_INT_STAT1_INM(x, m)      \
        in_dword_masked(HWIO_SSCAON_INT_STAT1_ADDR(x), m)
#define HWIO_SSCAON_INT_STAT1_SSC_SSCAON_INT_STAT1_BMSK                            0xffffffff
#define HWIO_SSCAON_INT_STAT1_SSC_SSCAON_INT_STAT1_SHFT                                   0x0

#define HWIO_SSCAON_INT_STAT2_ADDR(x)                                              ((x) + 0x00000078)
#define HWIO_SSCAON_INT_STAT2_PHYS(x)                                              ((x) + 0x00000078)
#define HWIO_SSCAON_INT_STAT2_OFFS                                                 (0x00000078)
#define HWIO_SSCAON_INT_STAT2_RMSK                                                 0xffffffff
#define HWIO_SSCAON_INT_STAT2_POR                                                  0x00000000
#define HWIO_SSCAON_INT_STAT2_POR_RMSK                                             0xffffffff
#define HWIO_SSCAON_INT_STAT2_ATTR                                                        0x1
#define HWIO_SSCAON_INT_STAT2_IN(x)      \
        in_dword_masked(HWIO_SSCAON_INT_STAT2_ADDR(x), HWIO_SSCAON_INT_STAT2_RMSK)
#define HWIO_SSCAON_INT_STAT2_INM(x, m)      \
        in_dword_masked(HWIO_SSCAON_INT_STAT2_ADDR(x), m)
#define HWIO_SSCAON_INT_STAT2_SSC_SSCAON_INT_STAT2_BMSK                            0xffffffff
#define HWIO_SSCAON_INT_STAT2_SSC_SSCAON_INT_STAT2_SHFT                                   0x0

#define HWIO_SSCAON_INT_RAW_STAT0_ADDR(x)                                          ((x) + 0x0000007c)
#define HWIO_SSCAON_INT_RAW_STAT0_PHYS(x)                                          ((x) + 0x0000007c)
#define HWIO_SSCAON_INT_RAW_STAT0_OFFS                                             (0x0000007c)
#define HWIO_SSCAON_INT_RAW_STAT0_RMSK                                             0xffffffff
#define HWIO_SSCAON_INT_RAW_STAT0_POR                                              0x00000000
#define HWIO_SSCAON_INT_RAW_STAT0_POR_RMSK                                         0xffffffff
#define HWIO_SSCAON_INT_RAW_STAT0_ATTR                                                    0x1
#define HWIO_SSCAON_INT_RAW_STAT0_IN(x)      \
        in_dword_masked(HWIO_SSCAON_INT_RAW_STAT0_ADDR(x), HWIO_SSCAON_INT_RAW_STAT0_RMSK)
#define HWIO_SSCAON_INT_RAW_STAT0_INM(x, m)      \
        in_dword_masked(HWIO_SSCAON_INT_RAW_STAT0_ADDR(x), m)
#define HWIO_SSCAON_INT_RAW_STAT0_SSC_SSCAON_INT_RAW_STAT0_BMSK                    0xffffffff
#define HWIO_SSCAON_INT_RAW_STAT0_SSC_SSCAON_INT_RAW_STAT0_SHFT                           0x0

#define HWIO_SSCAON_INT_RAW_STAT1_ADDR(x)                                          ((x) + 0x00000080)
#define HWIO_SSCAON_INT_RAW_STAT1_PHYS(x)                                          ((x) + 0x00000080)
#define HWIO_SSCAON_INT_RAW_STAT1_OFFS                                             (0x00000080)
#define HWIO_SSCAON_INT_RAW_STAT1_RMSK                                             0xffffffff
#define HWIO_SSCAON_INT_RAW_STAT1_POR                                              0x00000000
#define HWIO_SSCAON_INT_RAW_STAT1_POR_RMSK                                         0xffffffff
#define HWIO_SSCAON_INT_RAW_STAT1_ATTR                                                    0x1
#define HWIO_SSCAON_INT_RAW_STAT1_IN(x)      \
        in_dword_masked(HWIO_SSCAON_INT_RAW_STAT1_ADDR(x), HWIO_SSCAON_INT_RAW_STAT1_RMSK)
#define HWIO_SSCAON_INT_RAW_STAT1_INM(x, m)      \
        in_dword_masked(HWIO_SSCAON_INT_RAW_STAT1_ADDR(x), m)
#define HWIO_SSCAON_INT_RAW_STAT1_SSC_SSCAON_INT_RAW_STAT1_BMSK                    0xffffffff
#define HWIO_SSCAON_INT_RAW_STAT1_SSC_SSCAON_INT_RAW_STAT1_SHFT                           0x0

#define HWIO_SSCAON_INT_RAW_STAT2_ADDR(x)                                          ((x) + 0x00000084)
#define HWIO_SSCAON_INT_RAW_STAT2_PHYS(x)                                          ((x) + 0x00000084)
#define HWIO_SSCAON_INT_RAW_STAT2_OFFS                                             (0x00000084)
#define HWIO_SSCAON_INT_RAW_STAT2_RMSK                                             0xffffffff
#define HWIO_SSCAON_INT_RAW_STAT2_POR                                              0x00000000
#define HWIO_SSCAON_INT_RAW_STAT2_POR_RMSK                                         0xffffffff
#define HWIO_SSCAON_INT_RAW_STAT2_ATTR                                                    0x1
#define HWIO_SSCAON_INT_RAW_STAT2_IN(x)      \
        in_dword_masked(HWIO_SSCAON_INT_RAW_STAT2_ADDR(x), HWIO_SSCAON_INT_RAW_STAT2_RMSK)
#define HWIO_SSCAON_INT_RAW_STAT2_INM(x, m)      \
        in_dword_masked(HWIO_SSCAON_INT_RAW_STAT2_ADDR(x), m)
#define HWIO_SSCAON_INT_RAW_STAT2_SSC_SSCAON_INT_RAW_STAT2_BMSK                    0xffffffff
#define HWIO_SSCAON_INT_RAW_STAT2_SSC_SSCAON_INT_RAW_STAT2_SHFT                           0x0

#define HWIO_SSCAON_INT_TO_TMR_IRQ_CLR_ADDR(x)                                     ((x) + 0x00000088)
#define HWIO_SSCAON_INT_TO_TMR_IRQ_CLR_PHYS(x)                                     ((x) + 0x00000088)
#define HWIO_SSCAON_INT_TO_TMR_IRQ_CLR_OFFS                                        (0x00000088)
#define HWIO_SSCAON_INT_TO_TMR_IRQ_CLR_RMSK                                               0x1
#define HWIO_SSCAON_INT_TO_TMR_IRQ_CLR_POR                                         0x00000000
#define HWIO_SSCAON_INT_TO_TMR_IRQ_CLR_POR_RMSK                                    0xffffffff
#define HWIO_SSCAON_INT_TO_TMR_IRQ_CLR_ATTR                                               0x2
#define HWIO_SSCAON_INT_TO_TMR_IRQ_CLR_OUT(x, v)      \
        out_dword(HWIO_SSCAON_INT_TO_TMR_IRQ_CLR_ADDR(x),v)
#define HWIO_SSCAON_INT_TO_TMR_IRQ_CLR_SSC_SSCAON_TO_TMR_IRQ_CLR_BMSK                     0x1
#define HWIO_SSCAON_INT_TO_TMR_IRQ_CLR_SSC_SSCAON_TO_TMR_IRQ_CLR_SHFT                     0x0

#define HWIO_SSC_TEST_BUS_SEL_CFG_ADDR(x)                                          ((x) + 0x00001000)
#define HWIO_SSC_TEST_BUS_SEL_CFG_PHYS(x)                                          ((x) + 0x00001000)
#define HWIO_SSC_TEST_BUS_SEL_CFG_OFFS                                             (0x00001000)
#define HWIO_SSC_TEST_BUS_SEL_CFG_RMSK                                                    0x1
#define HWIO_SSC_TEST_BUS_SEL_CFG_POR                                              0x00000000
#define HWIO_SSC_TEST_BUS_SEL_CFG_POR_RMSK                                         0xffffffff
#define HWIO_SSC_TEST_BUS_SEL_CFG_ATTR                                                    0x3
#define HWIO_SSC_TEST_BUS_SEL_CFG_IN(x)      \
        in_dword_masked(HWIO_SSC_TEST_BUS_SEL_CFG_ADDR(x), HWIO_SSC_TEST_BUS_SEL_CFG_RMSK)
#define HWIO_SSC_TEST_BUS_SEL_CFG_INM(x, m)      \
        in_dword_masked(HWIO_SSC_TEST_BUS_SEL_CFG_ADDR(x), m)
#define HWIO_SSC_TEST_BUS_SEL_CFG_OUT(x, v)      \
        out_dword(HWIO_SSC_TEST_BUS_SEL_CFG_ADDR(x),v)
#define HWIO_SSC_TEST_BUS_SEL_CFG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SSC_TEST_BUS_SEL_CFG_ADDR(x),m,v,HWIO_SSC_TEST_BUS_SEL_CFG_IN(x))
#define HWIO_SSC_TEST_BUS_SEL_CFG_SSC_TEST_BUS_SEL_BMSK                                   0x1
#define HWIO_SSC_TEST_BUS_SEL_CFG_SSC_TEST_BUS_SEL_SHFT                                   0x0

#define HWIO_SSC_HW_VERSION_ADDR(x)                                                ((x) + 0x00001004)
#define HWIO_SSC_HW_VERSION_PHYS(x)                                                ((x) + 0x00001004)
#define HWIO_SSC_HW_VERSION_OFFS                                                   (0x00001004)
#define HWIO_SSC_HW_VERSION_RMSK                                                   0xffffffff
#define HWIO_SSC_HW_VERSION_POR                                                    0x10000000
#define HWIO_SSC_HW_VERSION_POR_RMSK                                               0xffffffff
#define HWIO_SSC_HW_VERSION_ATTR                                                          0x1
#define HWIO_SSC_HW_VERSION_IN(x)      \
        in_dword_masked(HWIO_SSC_HW_VERSION_ADDR(x), HWIO_SSC_HW_VERSION_RMSK)
#define HWIO_SSC_HW_VERSION_INM(x, m)      \
        in_dword_masked(HWIO_SSC_HW_VERSION_ADDR(x), m)
#define HWIO_SSC_HW_VERSION_MAJOR_BMSK                                             0xf0000000
#define HWIO_SSC_HW_VERSION_MAJOR_SHFT                                                   0x1c
#define HWIO_SSC_HW_VERSION_MINOR_BMSK                                              0xfff0000
#define HWIO_SSC_HW_VERSION_MINOR_SHFT                                                   0x10
#define HWIO_SSC_HW_VERSION_STEP_BMSK                                                  0xffff
#define HWIO_SSC_HW_VERSION_STEP_SHFT                                                     0x0

#define HWIO_SSC_XO_CLK_GATE_ADDR(x)                                               ((x) + 0x00001008)
#define HWIO_SSC_XO_CLK_GATE_PHYS(x)                                               ((x) + 0x00001008)
#define HWIO_SSC_XO_CLK_GATE_OFFS                                                  (0x00001008)
#define HWIO_SSC_XO_CLK_GATE_RMSK                                                         0x1
#define HWIO_SSC_XO_CLK_GATE_POR                                                   0x00000001
#define HWIO_SSC_XO_CLK_GATE_POR_RMSK                                              0xffffffff
#define HWIO_SSC_XO_CLK_GATE_ATTR                                                         0x3
#define HWIO_SSC_XO_CLK_GATE_IN(x)      \
        in_dword_masked(HWIO_SSC_XO_CLK_GATE_ADDR(x), HWIO_SSC_XO_CLK_GATE_RMSK)
#define HWIO_SSC_XO_CLK_GATE_INM(x, m)      \
        in_dword_masked(HWIO_SSC_XO_CLK_GATE_ADDR(x), m)
#define HWIO_SSC_XO_CLK_GATE_OUT(x, v)      \
        out_dword(HWIO_SSC_XO_CLK_GATE_ADDR(x),v)
#define HWIO_SSC_XO_CLK_GATE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SSC_XO_CLK_GATE_ADDR(x),m,v,HWIO_SSC_XO_CLK_GATE_IN(x))
#define HWIO_SSC_XO_CLK_GATE_SSC_XO_CLK_GATE_EN_BMSK                                      0x1
#define HWIO_SSC_XO_CLK_GATE_SSC_XO_CLK_GATE_EN_SHFT                                      0x0

#define HWIO_SSC_I2C_CFG_ADDR(x)                                                   ((x) + 0x0000100c)
#define HWIO_SSC_I2C_CFG_PHYS(x)                                                   ((x) + 0x0000100c)
#define HWIO_SSC_I2C_CFG_OFFS                                                      (0x0000100c)
#define HWIO_SSC_I2C_CFG_RMSK                                                             0xf
#define HWIO_SSC_I2C_CFG_POR                                                       0x00000000
#define HWIO_SSC_I2C_CFG_POR_RMSK                                                  0xffffffff
#define HWIO_SSC_I2C_CFG_ATTR                                                             0x3
#define HWIO_SSC_I2C_CFG_IN(x)      \
        in_dword_masked(HWIO_SSC_I2C_CFG_ADDR(x), HWIO_SSC_I2C_CFG_RMSK)
#define HWIO_SSC_I2C_CFG_INM(x, m)      \
        in_dword_masked(HWIO_SSC_I2C_CFG_ADDR(x), m)
#define HWIO_SSC_I2C_CFG_OUT(x, v)      \
        out_dword(HWIO_SSC_I2C_CFG_ADDR(x),v)
#define HWIO_SSC_I2C_CFG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SSC_I2C_CFG_ADDR(x),m,v,HWIO_SSC_I2C_CFG_IN(x))
#define HWIO_SSC_I2C_CFG_MODE_1_BMSK                                                      0xc
#define HWIO_SSC_I2C_CFG_MODE_1_SHFT                                                      0x2
#define HWIO_SSC_I2C_CFG_MODE_0_BMSK                                                      0x3
#define HWIO_SSC_I2C_CFG_MODE_0_SHFT                                                      0x0

#define HWIO_SSC_IEC_CTL_ADDR(x)                                                   ((x) + 0x00002000)
#define HWIO_SSC_IEC_CTL_PHYS(x)                                                   ((x) + 0x00002000)
#define HWIO_SSC_IEC_CTL_OFFS                                                      (0x00002000)
#define HWIO_SSC_IEC_CTL_RMSK                                                            0x7f
#define HWIO_SSC_IEC_CTL_POR                                                       0x00000000
#define HWIO_SSC_IEC_CTL_POR_RMSK                                                  0xffffffff
#define HWIO_SSC_IEC_CTL_ATTR                                                             0x3
#define HWIO_SSC_IEC_CTL_IN(x)      \
        in_dword_masked(HWIO_SSC_IEC_CTL_ADDR(x), HWIO_SSC_IEC_CTL_RMSK)
#define HWIO_SSC_IEC_CTL_INM(x, m)      \
        in_dword_masked(HWIO_SSC_IEC_CTL_ADDR(x), m)
#define HWIO_SSC_IEC_CTL_OUT(x, v)      \
        out_dword(HWIO_SSC_IEC_CTL_ADDR(x),v)
#define HWIO_SSC_IEC_CTL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SSC_IEC_CTL_ADDR(x),m,v,HWIO_SSC_IEC_CTL_IN(x))
#define HWIO_SSC_IEC_CTL_BUS_ISO_ENTER_ISLAND_DIS_BMSK                                   0x40
#define HWIO_SSC_IEC_CTL_BUS_ISO_ENTER_ISLAND_DIS_SHFT                                    0x6
#define HWIO_SSC_IEC_CTL_L2_MISS_ISLAND_EXIT_EN_BMSK                                     0x20
#define HWIO_SSC_IEC_CTL_L2_MISS_ISLAND_EXIT_EN_SHFT                                      0x5
#define HWIO_SSC_IEC_CTL_ISO_AHB_MASTER_BYPASS_BMSK                                      0x10
#define HWIO_SSC_IEC_CTL_ISO_AHB_MASTER_BYPASS_SHFT                                       0x4
#define HWIO_SSC_IEC_CTL_ISO_AHB_SLAVE_BYPASS_BMSK                                        0x8
#define HWIO_SSC_IEC_CTL_ISO_AHB_SLAVE_BYPASS_SHFT                                        0x3
#define HWIO_SSC_IEC_CTL_AHB_REQPEND_CLR_BMSK                                             0x4
#define HWIO_SSC_IEC_CTL_AHB_REQPEND_CLR_SHFT                                             0x2
#define HWIO_SSC_IEC_CTL_ENTER_ISLAND_MODE_IRQ_CLR_BMSK                                   0x2
#define HWIO_SSC_IEC_CTL_ENTER_ISLAND_MODE_IRQ_CLR_SHFT                                   0x1
#define HWIO_SSC_IEC_CTL_EXIT_ISLAND_MODE_TRIG_BMSK                                       0x1
#define HWIO_SSC_IEC_CTL_EXIT_ISLAND_MODE_TRIG_SHFT                                       0x0

#define HWIO_SSC_IEC_STAT_ADDR(x)                                                  ((x) + 0x00002004)
#define HWIO_SSC_IEC_STAT_PHYS(x)                                                  ((x) + 0x00002004)
#define HWIO_SSC_IEC_STAT_OFFS                                                     (0x00002004)
#define HWIO_SSC_IEC_STAT_RMSK                                                            0x1
#define HWIO_SSC_IEC_STAT_POR                                                      0x00000000
#define HWIO_SSC_IEC_STAT_POR_RMSK                                                 0xffffffff
#define HWIO_SSC_IEC_STAT_ATTR                                                            0x1
#define HWIO_SSC_IEC_STAT_IN(x)      \
        in_dword_masked(HWIO_SSC_IEC_STAT_ADDR(x), HWIO_SSC_IEC_STAT_RMSK)
#define HWIO_SSC_IEC_STAT_INM(x, m)      \
        in_dword_masked(HWIO_SSC_IEC_STAT_ADDR(x), m)
#define HWIO_SSC_IEC_STAT_ISLAND_MODE_BMSK                                                0x1
#define HWIO_SSC_IEC_STAT_ISLAND_MODE_SHFT                                                0x0

#define HWIO_SSC_IEC_BSY_WAIT_ADDR(x)                                              ((x) + 0x00002008)
#define HWIO_SSC_IEC_BSY_WAIT_PHYS(x)                                              ((x) + 0x00002008)
#define HWIO_SSC_IEC_BSY_WAIT_OFFS                                                 (0x00002008)
#define HWIO_SSC_IEC_BSY_WAIT_RMSK                                                        0x3
#define HWIO_SSC_IEC_BSY_WAIT_POR                                                  0x00000000
#define HWIO_SSC_IEC_BSY_WAIT_POR_RMSK                                             0xffffffff
#define HWIO_SSC_IEC_BSY_WAIT_ATTR                                                        0x3
#define HWIO_SSC_IEC_BSY_WAIT_IN(x)      \
        in_dword_masked(HWIO_SSC_IEC_BSY_WAIT_ADDR(x), HWIO_SSC_IEC_BSY_WAIT_RMSK)
#define HWIO_SSC_IEC_BSY_WAIT_INM(x, m)      \
        in_dword_masked(HWIO_SSC_IEC_BSY_WAIT_ADDR(x), m)
#define HWIO_SSC_IEC_BSY_WAIT_OUT(x, v)      \
        out_dword(HWIO_SSC_IEC_BSY_WAIT_ADDR(x),v)
#define HWIO_SSC_IEC_BSY_WAIT_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SSC_IEC_BSY_WAIT_ADDR(x),m,v,HWIO_SSC_IEC_BSY_WAIT_IN(x))
#define HWIO_SSC_IEC_BSY_WAIT_BUSY_WAIT_EN_BMSK                                           0x2
#define HWIO_SSC_IEC_BSY_WAIT_BUSY_WAIT_EN_SHFT                                           0x1
#define HWIO_SSC_IEC_BSY_WAIT_BUSY_WAIT_RST_BMSK                                          0x1
#define HWIO_SSC_IEC_BSY_WAIT_BUSY_WAIT_RST_SHFT                                          0x0

#define HWIO_SSC_IEC_SQCNTR_VAL0_ADDR(x)                                           ((x) + 0x0000200c)
#define HWIO_SSC_IEC_SQCNTR_VAL0_PHYS(x)                                           ((x) + 0x0000200c)
#define HWIO_SSC_IEC_SQCNTR_VAL0_OFFS                                              (0x0000200c)
#define HWIO_SSC_IEC_SQCNTR_VAL0_RMSK                                              0xffffffff
#define HWIO_SSC_IEC_SQCNTR_VAL0_POR                                               0x00000000
#define HWIO_SSC_IEC_SQCNTR_VAL0_POR_RMSK                                          0xffffffff
#define HWIO_SSC_IEC_SQCNTR_VAL0_ATTR                                                     0x1
#define HWIO_SSC_IEC_SQCNTR_VAL0_IN(x)      \
        in_dword_masked(HWIO_SSC_IEC_SQCNTR_VAL0_ADDR(x), HWIO_SSC_IEC_SQCNTR_VAL0_RMSK)
#define HWIO_SSC_IEC_SQCNTR_VAL0_INM(x, m)      \
        in_dword_masked(HWIO_SSC_IEC_SQCNTR_VAL0_ADDR(x), m)
#define HWIO_SSC_IEC_SQCNTR_VAL0_SQCNTR_VAL0_BMSK                                  0xffffffff
#define HWIO_SSC_IEC_SQCNTR_VAL0_SQCNTR_VAL0_SHFT                                         0x0

#define HWIO_SSC_IEC_SQCNTR_VAL1_ADDR(x)                                           ((x) + 0x00002010)
#define HWIO_SSC_IEC_SQCNTR_VAL1_PHYS(x)                                           ((x) + 0x00002010)
#define HWIO_SSC_IEC_SQCNTR_VAL1_OFFS                                              (0x00002010)
#define HWIO_SSC_IEC_SQCNTR_VAL1_RMSK                                                0xffffff
#define HWIO_SSC_IEC_SQCNTR_VAL1_POR                                               0x00000000
#define HWIO_SSC_IEC_SQCNTR_VAL1_POR_RMSK                                          0xffffffff
#define HWIO_SSC_IEC_SQCNTR_VAL1_ATTR                                                     0x1
#define HWIO_SSC_IEC_SQCNTR_VAL1_IN(x)      \
        in_dword_masked(HWIO_SSC_IEC_SQCNTR_VAL1_ADDR(x), HWIO_SSC_IEC_SQCNTR_VAL1_RMSK)
#define HWIO_SSC_IEC_SQCNTR_VAL1_INM(x, m)      \
        in_dword_masked(HWIO_SSC_IEC_SQCNTR_VAL1_ADDR(x), m)
#define HWIO_SSC_IEC_SQCNTR_VAL1_SQCNTR_VAL1_BMSK                                    0xffffff
#define HWIO_SSC_IEC_SQCNTR_VAL1_SQCNTR_VAL1_SHFT                                         0x0

#define HWIO_SSC_IEC_BUSY_WAIT_CNTR_VAL0_ADDR(x)                                   ((x) + 0x00002014)
#define HWIO_SSC_IEC_BUSY_WAIT_CNTR_VAL0_PHYS(x)                                   ((x) + 0x00002014)
#define HWIO_SSC_IEC_BUSY_WAIT_CNTR_VAL0_OFFS                                      (0x00002014)
#define HWIO_SSC_IEC_BUSY_WAIT_CNTR_VAL0_RMSK                                      0xffffffff
#define HWIO_SSC_IEC_BUSY_WAIT_CNTR_VAL0_POR                                       0x00000000
#define HWIO_SSC_IEC_BUSY_WAIT_CNTR_VAL0_POR_RMSK                                  0xffffffff
#define HWIO_SSC_IEC_BUSY_WAIT_CNTR_VAL0_ATTR                                             0x1
#define HWIO_SSC_IEC_BUSY_WAIT_CNTR_VAL0_IN(x)      \
        in_dword_masked(HWIO_SSC_IEC_BUSY_WAIT_CNTR_VAL0_ADDR(x), HWIO_SSC_IEC_BUSY_WAIT_CNTR_VAL0_RMSK)
#define HWIO_SSC_IEC_BUSY_WAIT_CNTR_VAL0_INM(x, m)      \
        in_dword_masked(HWIO_SSC_IEC_BUSY_WAIT_CNTR_VAL0_ADDR(x), m)
#define HWIO_SSC_IEC_BUSY_WAIT_CNTR_VAL0_BUSY_WAIT_CNTR_VAL0_BMSK                  0xffffffff
#define HWIO_SSC_IEC_BUSY_WAIT_CNTR_VAL0_BUSY_WAIT_CNTR_VAL0_SHFT                         0x0

#define HWIO_SSC_IEC_BUSY_WAIT_CNTR_VAL1_ADDR(x)                                   ((x) + 0x00002018)
#define HWIO_SSC_IEC_BUSY_WAIT_CNTR_VAL1_PHYS(x)                                   ((x) + 0x00002018)
#define HWIO_SSC_IEC_BUSY_WAIT_CNTR_VAL1_OFFS                                      (0x00002018)
#define HWIO_SSC_IEC_BUSY_WAIT_CNTR_VAL1_RMSK                                        0xffffff
#define HWIO_SSC_IEC_BUSY_WAIT_CNTR_VAL1_POR                                       0x00000000
#define HWIO_SSC_IEC_BUSY_WAIT_CNTR_VAL1_POR_RMSK                                  0xffffffff
#define HWIO_SSC_IEC_BUSY_WAIT_CNTR_VAL1_ATTR                                             0x1
#define HWIO_SSC_IEC_BUSY_WAIT_CNTR_VAL1_IN(x)      \
        in_dword_masked(HWIO_SSC_IEC_BUSY_WAIT_CNTR_VAL1_ADDR(x), HWIO_SSC_IEC_BUSY_WAIT_CNTR_VAL1_RMSK)
#define HWIO_SSC_IEC_BUSY_WAIT_CNTR_VAL1_INM(x, m)      \
        in_dword_masked(HWIO_SSC_IEC_BUSY_WAIT_CNTR_VAL1_ADDR(x), m)
#define HWIO_SSC_IEC_BUSY_WAIT_CNTR_VAL1_BUSY_WAIT_CNTR_VAL1_BMSK                    0xffffff
#define HWIO_SSC_IEC_BUSY_WAIT_CNTR_VAL1_BUSY_WAIT_CNTR_VAL1_SHFT                         0x0

#define HWIO_SSC_IEC_HADDR_VAL0_ADDR(x)                                            ((x) + 0x0000201c)
#define HWIO_SSC_IEC_HADDR_VAL0_PHYS(x)                                            ((x) + 0x0000201c)
#define HWIO_SSC_IEC_HADDR_VAL0_OFFS                                               (0x0000201c)
#define HWIO_SSC_IEC_HADDR_VAL0_RMSK                                               0xffffffff
#define HWIO_SSC_IEC_HADDR_VAL0_POR                                                0x00000000
#define HWIO_SSC_IEC_HADDR_VAL0_POR_RMSK                                           0xffffffff
#define HWIO_SSC_IEC_HADDR_VAL0_ATTR                                                      0x1
#define HWIO_SSC_IEC_HADDR_VAL0_IN(x)      \
        in_dword_masked(HWIO_SSC_IEC_HADDR_VAL0_ADDR(x), HWIO_SSC_IEC_HADDR_VAL0_RMSK)
#define HWIO_SSC_IEC_HADDR_VAL0_INM(x, m)      \
        in_dword_masked(HWIO_SSC_IEC_HADDR_VAL0_ADDR(x), m)
#define HWIO_SSC_IEC_HADDR_VAL0_HADDR_VAL0_BMSK                                    0xffffffff
#define HWIO_SSC_IEC_HADDR_VAL0_HADDR_VAL0_SHFT                                           0x0

#define HWIO_SSC_IEC_HADDR_VAL1_ADDR(x)                                            ((x) + 0x00002020)
#define HWIO_SSC_IEC_HADDR_VAL1_PHYS(x)                                            ((x) + 0x00002020)
#define HWIO_SSC_IEC_HADDR_VAL1_OFFS                                               (0x00002020)
#define HWIO_SSC_IEC_HADDR_VAL1_RMSK                                                      0xf
#define HWIO_SSC_IEC_HADDR_VAL1_POR                                                0x00000000
#define HWIO_SSC_IEC_HADDR_VAL1_POR_RMSK                                           0xffffffff
#define HWIO_SSC_IEC_HADDR_VAL1_ATTR                                                      0x1
#define HWIO_SSC_IEC_HADDR_VAL1_IN(x)      \
        in_dword_masked(HWIO_SSC_IEC_HADDR_VAL1_ADDR(x), HWIO_SSC_IEC_HADDR_VAL1_RMSK)
#define HWIO_SSC_IEC_HADDR_VAL1_INM(x, m)      \
        in_dword_masked(HWIO_SSC_IEC_HADDR_VAL1_ADDR(x), m)
#define HWIO_SSC_IEC_HADDR_VAL1_HADDR_VAL1_BMSK                                           0xf
#define HWIO_SSC_IEC_HADDR_VAL1_HADDR_VAL1_SHFT                                           0x0

#define HWIO_SSC_IEC_HMID_VAL_ADDR(x)                                              ((x) + 0x00002024)
#define HWIO_SSC_IEC_HMID_VAL_PHYS(x)                                              ((x) + 0x00002024)
#define HWIO_SSC_IEC_HMID_VAL_OFFS                                                 (0x00002024)
#define HWIO_SSC_IEC_HMID_VAL_RMSK                                                       0xff
#define HWIO_SSC_IEC_HMID_VAL_POR                                                  0x00000000
#define HWIO_SSC_IEC_HMID_VAL_POR_RMSK                                             0xffffffff
#define HWIO_SSC_IEC_HMID_VAL_ATTR                                                        0x1
#define HWIO_SSC_IEC_HMID_VAL_IN(x)      \
        in_dword_masked(HWIO_SSC_IEC_HMID_VAL_ADDR(x), HWIO_SSC_IEC_HMID_VAL_RMSK)
#define HWIO_SSC_IEC_HMID_VAL_INM(x, m)      \
        in_dword_masked(HWIO_SSC_IEC_HMID_VAL_ADDR(x), m)
#define HWIO_SSC_IEC_HMID_VAL_SSC_IEC_HMID_VAL_BMSK                                      0xff
#define HWIO_SSC_IEC_HMID_VAL_SSC_IEC_HMID_VAL_SHFT                                       0x0

#define HWIO_SSC_IEC_HWEVENTS_SEL0_ADDR(x)                                         ((x) + 0x00002028)
#define HWIO_SSC_IEC_HWEVENTS_SEL0_PHYS(x)                                         ((x) + 0x00002028)
#define HWIO_SSC_IEC_HWEVENTS_SEL0_OFFS                                            (0x00002028)
#define HWIO_SSC_IEC_HWEVENTS_SEL0_RMSK                                            0xffffffff
#define HWIO_SSC_IEC_HWEVENTS_SEL0_POR                                             0x00000000
#define HWIO_SSC_IEC_HWEVENTS_SEL0_POR_RMSK                                        0xffffffff
#define HWIO_SSC_IEC_HWEVENTS_SEL0_ATTR                                                   0x3
#define HWIO_SSC_IEC_HWEVENTS_SEL0_IN(x)      \
        in_dword_masked(HWIO_SSC_IEC_HWEVENTS_SEL0_ADDR(x), HWIO_SSC_IEC_HWEVENTS_SEL0_RMSK)
#define HWIO_SSC_IEC_HWEVENTS_SEL0_INM(x, m)      \
        in_dword_masked(HWIO_SSC_IEC_HWEVENTS_SEL0_ADDR(x), m)
#define HWIO_SSC_IEC_HWEVENTS_SEL0_OUT(x, v)      \
        out_dword(HWIO_SSC_IEC_HWEVENTS_SEL0_ADDR(x),v)
#define HWIO_SSC_IEC_HWEVENTS_SEL0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SSC_IEC_HWEVENTS_SEL0_ADDR(x),m,v,HWIO_SSC_IEC_HWEVENTS_SEL0_IN(x))
#define HWIO_SSC_IEC_HWEVENTS_SEL0_SSC_HWEVENTS_SEL0_BMSK                          0xffffffff
#define HWIO_SSC_IEC_HWEVENTS_SEL0_SSC_HWEVENTS_SEL0_SHFT                                 0x0

#define HWIO_SSC_IEC_HWEVENTS_SEL1_ADDR(x)                                         ((x) + 0x0000202c)
#define HWIO_SSC_IEC_HWEVENTS_SEL1_PHYS(x)                                         ((x) + 0x0000202c)
#define HWIO_SSC_IEC_HWEVENTS_SEL1_OFFS                                            (0x0000202c)
#define HWIO_SSC_IEC_HWEVENTS_SEL1_RMSK                                            0xffffffff
#define HWIO_SSC_IEC_HWEVENTS_SEL1_POR                                             0x00000000
#define HWIO_SSC_IEC_HWEVENTS_SEL1_POR_RMSK                                        0xffffffff
#define HWIO_SSC_IEC_HWEVENTS_SEL1_ATTR                                                   0x3
#define HWIO_SSC_IEC_HWEVENTS_SEL1_IN(x)      \
        in_dword_masked(HWIO_SSC_IEC_HWEVENTS_SEL1_ADDR(x), HWIO_SSC_IEC_HWEVENTS_SEL1_RMSK)
#define HWIO_SSC_IEC_HWEVENTS_SEL1_INM(x, m)      \
        in_dword_masked(HWIO_SSC_IEC_HWEVENTS_SEL1_ADDR(x), m)
#define HWIO_SSC_IEC_HWEVENTS_SEL1_OUT(x, v)      \
        out_dword(HWIO_SSC_IEC_HWEVENTS_SEL1_ADDR(x),v)
#define HWIO_SSC_IEC_HWEVENTS_SEL1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SSC_IEC_HWEVENTS_SEL1_ADDR(x),m,v,HWIO_SSC_IEC_HWEVENTS_SEL1_IN(x))
#define HWIO_SSC_IEC_HWEVENTS_SEL1_SSC_HWEVENTS_SEL1_BMSK                          0xffffffff
#define HWIO_SSC_IEC_HWEVENTS_SEL1_SSC_HWEVENTS_SEL1_SHFT                                 0x0

#define HWIO_SSC_IEC_HWEVENTS_SEL2_ADDR(x)                                         ((x) + 0x00002030)
#define HWIO_SSC_IEC_HWEVENTS_SEL2_PHYS(x)                                         ((x) + 0x00002030)
#define HWIO_SSC_IEC_HWEVENTS_SEL2_OFFS                                            (0x00002030)
#define HWIO_SSC_IEC_HWEVENTS_SEL2_RMSK                                            0xffffffff
#define HWIO_SSC_IEC_HWEVENTS_SEL2_POR                                             0x00000000
#define HWIO_SSC_IEC_HWEVENTS_SEL2_POR_RMSK                                        0xffffffff
#define HWIO_SSC_IEC_HWEVENTS_SEL2_ATTR                                                   0x3
#define HWIO_SSC_IEC_HWEVENTS_SEL2_IN(x)      \
        in_dword_masked(HWIO_SSC_IEC_HWEVENTS_SEL2_ADDR(x), HWIO_SSC_IEC_HWEVENTS_SEL2_RMSK)
#define HWIO_SSC_IEC_HWEVENTS_SEL2_INM(x, m)      \
        in_dword_masked(HWIO_SSC_IEC_HWEVENTS_SEL2_ADDR(x), m)
#define HWIO_SSC_IEC_HWEVENTS_SEL2_OUT(x, v)      \
        out_dword(HWIO_SSC_IEC_HWEVENTS_SEL2_ADDR(x),v)
#define HWIO_SSC_IEC_HWEVENTS_SEL2_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SSC_IEC_HWEVENTS_SEL2_ADDR(x),m,v,HWIO_SSC_IEC_HWEVENTS_SEL2_IN(x))
#define HWIO_SSC_IEC_HWEVENTS_SEL2_SSC_HWEVENTS_SEL2_BMSK                          0xffffffff
#define HWIO_SSC_IEC_HWEVENTS_SEL2_SSC_HWEVENTS_SEL2_SHFT                                 0x0

#define HWIO_SSC_IEC_HWEVENTS_SEL3_ADDR(x)                                         ((x) + 0x00002034)
#define HWIO_SSC_IEC_HWEVENTS_SEL3_PHYS(x)                                         ((x) + 0x00002034)
#define HWIO_SSC_IEC_HWEVENTS_SEL3_OFFS                                            (0x00002034)
#define HWIO_SSC_IEC_HWEVENTS_SEL3_RMSK                                            0xffffffff
#define HWIO_SSC_IEC_HWEVENTS_SEL3_POR                                             0x00000000
#define HWIO_SSC_IEC_HWEVENTS_SEL3_POR_RMSK                                        0xffffffff
#define HWIO_SSC_IEC_HWEVENTS_SEL3_ATTR                                                   0x3
#define HWIO_SSC_IEC_HWEVENTS_SEL3_IN(x)      \
        in_dword_masked(HWIO_SSC_IEC_HWEVENTS_SEL3_ADDR(x), HWIO_SSC_IEC_HWEVENTS_SEL3_RMSK)
#define HWIO_SSC_IEC_HWEVENTS_SEL3_INM(x, m)      \
        in_dword_masked(HWIO_SSC_IEC_HWEVENTS_SEL3_ADDR(x), m)
#define HWIO_SSC_IEC_HWEVENTS_SEL3_OUT(x, v)      \
        out_dword(HWIO_SSC_IEC_HWEVENTS_SEL3_ADDR(x),v)
#define HWIO_SSC_IEC_HWEVENTS_SEL3_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SSC_IEC_HWEVENTS_SEL3_ADDR(x),m,v,HWIO_SSC_IEC_HWEVENTS_SEL3_IN(x))
#define HWIO_SSC_IEC_HWEVENTS_SEL3_SSC_HWEVENTS_SEL3_BMSK                          0xffffffff
#define HWIO_SSC_IEC_HWEVENTS_SEL3_SSC_HWEVENTS_SEL3_SHFT                                 0x0

#define HWIO_SSC_IEC_HWEVENTS_EN_ADDR(x)                                           ((x) + 0x00002038)
#define HWIO_SSC_IEC_HWEVENTS_EN_PHYS(x)                                           ((x) + 0x00002038)
#define HWIO_SSC_IEC_HWEVENTS_EN_OFFS                                              (0x00002038)
#define HWIO_SSC_IEC_HWEVENTS_EN_RMSK                                              0xffffffff
#define HWIO_SSC_IEC_HWEVENTS_EN_POR                                               0x00000000
#define HWIO_SSC_IEC_HWEVENTS_EN_POR_RMSK                                          0xffffffff
#define HWIO_SSC_IEC_HWEVENTS_EN_ATTR                                                     0x3
#define HWIO_SSC_IEC_HWEVENTS_EN_IN(x)      \
        in_dword_masked(HWIO_SSC_IEC_HWEVENTS_EN_ADDR(x), HWIO_SSC_IEC_HWEVENTS_EN_RMSK)
#define HWIO_SSC_IEC_HWEVENTS_EN_INM(x, m)      \
        in_dword_masked(HWIO_SSC_IEC_HWEVENTS_EN_ADDR(x), m)
#define HWIO_SSC_IEC_HWEVENTS_EN_OUT(x, v)      \
        out_dword(HWIO_SSC_IEC_HWEVENTS_EN_ADDR(x),v)
#define HWIO_SSC_IEC_HWEVENTS_EN_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SSC_IEC_HWEVENTS_EN_ADDR(x),m,v,HWIO_SSC_IEC_HWEVENTS_EN_IN(x))
#define HWIO_SSC_IEC_HWEVENTS_EN_HWEVENTS_EN_BMSK                                  0xffffffff
#define HWIO_SSC_IEC_HWEVENTS_EN_HWEVENTS_EN_SHFT                                         0x0

#define HWIO_SSC_DATA_BUS_CONFIG_ADDR(x)                                           ((x) + 0x00003000)
#define HWIO_SSC_DATA_BUS_CONFIG_PHYS(x)                                           ((x) + 0x00003000)
#define HWIO_SSC_DATA_BUS_CONFIG_OFFS                                              (0x00003000)
#define HWIO_SSC_DATA_BUS_CONFIG_RMSK                                                   0xfff
#define HWIO_SSC_DATA_BUS_CONFIG_POR                                               0x00000001
#define HWIO_SSC_DATA_BUS_CONFIG_POR_RMSK                                          0xffffffff
#define HWIO_SSC_DATA_BUS_CONFIG_ATTR                                                     0x3
#define HWIO_SSC_DATA_BUS_CONFIG_IN(x)      \
        in_dword_masked(HWIO_SSC_DATA_BUS_CONFIG_ADDR(x), HWIO_SSC_DATA_BUS_CONFIG_RMSK)
#define HWIO_SSC_DATA_BUS_CONFIG_INM(x, m)      \
        in_dword_masked(HWIO_SSC_DATA_BUS_CONFIG_ADDR(x), m)
#define HWIO_SSC_DATA_BUS_CONFIG_OUT(x, v)      \
        out_dword(HWIO_SSC_DATA_BUS_CONFIG_ADDR(x),v)
#define HWIO_SSC_DATA_BUS_CONFIG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SSC_DATA_BUS_CONFIG_ADDR(x),m,v,HWIO_SSC_DATA_BUS_CONFIG_IN(x))
#define HWIO_SSC_DATA_BUS_CONFIG_AHBE_GLOBAL_EN_BMSK                                    0x800
#define HWIO_SSC_DATA_BUS_CONFIG_AHBE_GLOBAL_EN_SHFT                                      0xb
#define HWIO_SSC_DATA_BUS_CONFIG_AHBE_TIMEBASE_BMSK                                     0x400
#define HWIO_SSC_DATA_BUS_CONFIG_AHBE_TIMEBASE_SHFT                                       0xa
#define HWIO_SSC_DATA_BUS_CONFIG_LOCK_EN_ARRAY_BMSK                                     0x380
#define HWIO_SSC_DATA_BUS_CONFIG_LOCK_EN_ARRAY_SHFT                                       0x7
#define HWIO_SSC_DATA_BUS_CONFIG_PRIORITY_ARRAY_BMSK                                     0x7e
#define HWIO_SSC_DATA_BUS_CONFIG_PRIORITY_ARRAY_SHFT                                      0x1
#define HWIO_SSC_DATA_BUS_CONFIG_ARB_SCHEME_SEL_BMSK                                      0x1
#define HWIO_SSC_DATA_BUS_CONFIG_ARB_SCHEME_SEL_SHFT                                      0x0

#define HWIO_SSC_DATA_BUS_STATUS_ADDR(x)                                           ((x) + 0x00003004)
#define HWIO_SSC_DATA_BUS_STATUS_PHYS(x)                                           ((x) + 0x00003004)
#define HWIO_SSC_DATA_BUS_STATUS_OFFS                                              (0x00003004)
#define HWIO_SSC_DATA_BUS_STATUS_RMSK                                                     0x7
#define HWIO_SSC_DATA_BUS_STATUS_POR                                               0x00000000
#define HWIO_SSC_DATA_BUS_STATUS_POR_RMSK                                          0xffffffff
#define HWIO_SSC_DATA_BUS_STATUS_ATTR                                                     0x1
#define HWIO_SSC_DATA_BUS_STATUS_IN(x)      \
        in_dword_masked(HWIO_SSC_DATA_BUS_STATUS_ADDR(x), HWIO_SSC_DATA_BUS_STATUS_RMSK)
#define HWIO_SSC_DATA_BUS_STATUS_INM(x, m)      \
        in_dword_masked(HWIO_SSC_DATA_BUS_STATUS_ADDR(x), m)
#define HWIO_SSC_DATA_BUS_STATUS_AHBE_STATUS_BMSK                                         0x7
#define HWIO_SSC_DATA_BUS_STATUS_AHBE_STATUS_SHFT                                         0x0

#define HWIO_SSC_CFG_BUS_CONFIG_ADDR(x)                                            ((x) + 0x00004000)
#define HWIO_SSC_CFG_BUS_CONFIG_PHYS(x)                                            ((x) + 0x00004000)
#define HWIO_SSC_CFG_BUS_CONFIG_OFFS                                               (0x00004000)
#define HWIO_SSC_CFG_BUS_CONFIG_RMSK                                                     0x7f
#define HWIO_SSC_CFG_BUS_CONFIG_POR                                                0x00000001
#define HWIO_SSC_CFG_BUS_CONFIG_POR_RMSK                                           0xffffffff
#define HWIO_SSC_CFG_BUS_CONFIG_ATTR                                                      0x3
#define HWIO_SSC_CFG_BUS_CONFIG_IN(x)      \
        in_dword_masked(HWIO_SSC_CFG_BUS_CONFIG_ADDR(x), HWIO_SSC_CFG_BUS_CONFIG_RMSK)
#define HWIO_SSC_CFG_BUS_CONFIG_INM(x, m)      \
        in_dword_masked(HWIO_SSC_CFG_BUS_CONFIG_ADDR(x), m)
#define HWIO_SSC_CFG_BUS_CONFIG_OUT(x, v)      \
        out_dword(HWIO_SSC_CFG_BUS_CONFIG_ADDR(x),v)
#define HWIO_SSC_CFG_BUS_CONFIG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SSC_CFG_BUS_CONFIG_ADDR(x),m,v,HWIO_SSC_CFG_BUS_CONFIG_IN(x))
#define HWIO_SSC_CFG_BUS_CONFIG_AHBE_GLOBAL_EN_BMSK                                      0x40
#define HWIO_SSC_CFG_BUS_CONFIG_AHBE_GLOBAL_EN_SHFT                                       0x6
#define HWIO_SSC_CFG_BUS_CONFIG_AHBE_TIMEBASE_BMSK                                       0x20
#define HWIO_SSC_CFG_BUS_CONFIG_AHBE_TIMEBASE_SHFT                                        0x5
#define HWIO_SSC_CFG_BUS_CONFIG_LOCK_EN_ARRAY_BMSK                                       0x18
#define HWIO_SSC_CFG_BUS_CONFIG_LOCK_EN_ARRAY_SHFT                                        0x3
#define HWIO_SSC_CFG_BUS_CONFIG_PRIORITY_ARRAY_BMSK                                       0x6
#define HWIO_SSC_CFG_BUS_CONFIG_PRIORITY_ARRAY_SHFT                                       0x1
#define HWIO_SSC_CFG_BUS_CONFIG_ARB_SCHEME_SEL_BMSK                                       0x1
#define HWIO_SSC_CFG_BUS_CONFIG_ARB_SCHEME_SEL_SHFT                                       0x0

#define HWIO_SSC_CFG_BUS_STATUS_ADDR(x)                                            ((x) + 0x00004004)
#define HWIO_SSC_CFG_BUS_STATUS_PHYS(x)                                            ((x) + 0x00004004)
#define HWIO_SSC_CFG_BUS_STATUS_OFFS                                               (0x00004004)
#define HWIO_SSC_CFG_BUS_STATUS_RMSK                                                      0x7
#define HWIO_SSC_CFG_BUS_STATUS_POR                                                0x00000000
#define HWIO_SSC_CFG_BUS_STATUS_POR_RMSK                                           0xffffffff
#define HWIO_SSC_CFG_BUS_STATUS_ATTR                                                      0x1
#define HWIO_SSC_CFG_BUS_STATUS_IN(x)      \
        in_dword_masked(HWIO_SSC_CFG_BUS_STATUS_ADDR(x), HWIO_SSC_CFG_BUS_STATUS_RMSK)
#define HWIO_SSC_CFG_BUS_STATUS_INM(x, m)      \
        in_dword_masked(HWIO_SSC_CFG_BUS_STATUS_ADDR(x), m)
#define HWIO_SSC_CFG_BUS_STATUS_AHBE_STATUS_BMSK                                          0x7
#define HWIO_SSC_CFG_BUS_STATUS_AHBE_STATUS_SHFT                                          0x0

#define HWIO_SSC_TSGEN_PRELOAD_LO_ADDR(x)                                          ((x) + 0x00005000)
#define HWIO_SSC_TSGEN_PRELOAD_LO_PHYS(x)                                          ((x) + 0x00005000)
#define HWIO_SSC_TSGEN_PRELOAD_LO_OFFS                                             (0x00005000)
#define HWIO_SSC_TSGEN_PRELOAD_LO_RMSK                                             0xffffffff
#define HWIO_SSC_TSGEN_PRELOAD_LO_POR                                              0x00000000
#define HWIO_SSC_TSGEN_PRELOAD_LO_POR_RMSK                                         0xffffffff
#define HWIO_SSC_TSGEN_PRELOAD_LO_ATTR                                                    0x3
#define HWIO_SSC_TSGEN_PRELOAD_LO_IN(x)      \
        in_dword_masked(HWIO_SSC_TSGEN_PRELOAD_LO_ADDR(x), HWIO_SSC_TSGEN_PRELOAD_LO_RMSK)
#define HWIO_SSC_TSGEN_PRELOAD_LO_INM(x, m)      \
        in_dword_masked(HWIO_SSC_TSGEN_PRELOAD_LO_ADDR(x), m)
#define HWIO_SSC_TSGEN_PRELOAD_LO_OUT(x, v)      \
        out_dword(HWIO_SSC_TSGEN_PRELOAD_LO_ADDR(x),v)
#define HWIO_SSC_TSGEN_PRELOAD_LO_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SSC_TSGEN_PRELOAD_LO_ADDR(x),m,v,HWIO_SSC_TSGEN_PRELOAD_LO_IN(x))
#define HWIO_SSC_TSGEN_PRELOAD_LO_TSGEN_PRELOAD_LO_BMSK                            0xffffffff
#define HWIO_SSC_TSGEN_PRELOAD_LO_TSGEN_PRELOAD_LO_SHFT                                   0x0

#define HWIO_SSC_TSGEN_PRELOAD_HI_ADDR(x)                                          ((x) + 0x00005004)
#define HWIO_SSC_TSGEN_PRELOAD_HI_PHYS(x)                                          ((x) + 0x00005004)
#define HWIO_SSC_TSGEN_PRELOAD_HI_OFFS                                             (0x00005004)
#define HWIO_SSC_TSGEN_PRELOAD_HI_RMSK                                             0xffffffff
#define HWIO_SSC_TSGEN_PRELOAD_HI_POR                                              0x00000000
#define HWIO_SSC_TSGEN_PRELOAD_HI_POR_RMSK                                         0xffffffff
#define HWIO_SSC_TSGEN_PRELOAD_HI_ATTR                                                    0x3
#define HWIO_SSC_TSGEN_PRELOAD_HI_IN(x)      \
        in_dword_masked(HWIO_SSC_TSGEN_PRELOAD_HI_ADDR(x), HWIO_SSC_TSGEN_PRELOAD_HI_RMSK)
#define HWIO_SSC_TSGEN_PRELOAD_HI_INM(x, m)      \
        in_dword_masked(HWIO_SSC_TSGEN_PRELOAD_HI_ADDR(x), m)
#define HWIO_SSC_TSGEN_PRELOAD_HI_OUT(x, v)      \
        out_dword(HWIO_SSC_TSGEN_PRELOAD_HI_ADDR(x),v)
#define HWIO_SSC_TSGEN_PRELOAD_HI_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SSC_TSGEN_PRELOAD_HI_ADDR(x),m,v,HWIO_SSC_TSGEN_PRELOAD_HI_IN(x))
#define HWIO_SSC_TSGEN_PRELOAD_HI_TSGEN_PRELOAD_HI_BMSK                            0xffffffff
#define HWIO_SSC_TSGEN_PRELOAD_HI_TSGEN_PRELOAD_HI_SHFT                                   0x0

#define HWIO_SSC_TSGEN_CTR_LO_ADDR(x)                                              ((x) + 0x00005008)
#define HWIO_SSC_TSGEN_CTR_LO_PHYS(x)                                              ((x) + 0x00005008)
#define HWIO_SSC_TSGEN_CTR_LO_OFFS                                                 (0x00005008)
#define HWIO_SSC_TSGEN_CTR_LO_RMSK                                                 0xffffffff
#define HWIO_SSC_TSGEN_CTR_LO_POR                                                  0x00000000
#define HWIO_SSC_TSGEN_CTR_LO_POR_RMSK                                             0xffffffff
#define HWIO_SSC_TSGEN_CTR_LO_ATTR                                                        0x1
#define HWIO_SSC_TSGEN_CTR_LO_IN(x)      \
        in_dword_masked(HWIO_SSC_TSGEN_CTR_LO_ADDR(x), HWIO_SSC_TSGEN_CTR_LO_RMSK)
#define HWIO_SSC_TSGEN_CTR_LO_INM(x, m)      \
        in_dword_masked(HWIO_SSC_TSGEN_CTR_LO_ADDR(x), m)
#define HWIO_SSC_TSGEN_CTR_LO_TSGEN_CTR_LO_BMSK                                    0xffffffff
#define HWIO_SSC_TSGEN_CTR_LO_TSGEN_CTR_LO_SHFT                                           0x0

#define HWIO_SSC_TSGEN_CTR_HI_ADDR(x)                                              ((x) + 0x0000500c)
#define HWIO_SSC_TSGEN_CTR_HI_PHYS(x)                                              ((x) + 0x0000500c)
#define HWIO_SSC_TSGEN_CTR_HI_OFFS                                                 (0x0000500c)
#define HWIO_SSC_TSGEN_CTR_HI_RMSK                                                 0xffffffff
#define HWIO_SSC_TSGEN_CTR_HI_POR                                                  0x00000000
#define HWIO_SSC_TSGEN_CTR_HI_POR_RMSK                                             0xffffffff
#define HWIO_SSC_TSGEN_CTR_HI_ATTR                                                        0x1
#define HWIO_SSC_TSGEN_CTR_HI_IN(x)      \
        in_dword_masked(HWIO_SSC_TSGEN_CTR_HI_ADDR(x), HWIO_SSC_TSGEN_CTR_HI_RMSK)
#define HWIO_SSC_TSGEN_CTR_HI_INM(x, m)      \
        in_dword_masked(HWIO_SSC_TSGEN_CTR_HI_ADDR(x), m)
#define HWIO_SSC_TSGEN_CTR_HI_TSGEN_CTR_HI_BMSK                                    0xffffffff
#define HWIO_SSC_TSGEN_CTR_HI_TSGEN_CTR_HI_SHFT                                           0x0

#define HWIO_SSC_TSGEN_CTL_ADDR(x)                                                 ((x) + 0x00005010)
#define HWIO_SSC_TSGEN_CTL_PHYS(x)                                                 ((x) + 0x00005010)
#define HWIO_SSC_TSGEN_CTL_OFFS                                                    (0x00005010)
#define HWIO_SSC_TSGEN_CTL_RMSK                                                           0x3
#define HWIO_SSC_TSGEN_CTL_POR                                                     0x00000001
#define HWIO_SSC_TSGEN_CTL_POR_RMSK                                                0xffffffff
#define HWIO_SSC_TSGEN_CTL_ATTR                                                           0x3
#define HWIO_SSC_TSGEN_CTL_IN(x)      \
        in_dword_masked(HWIO_SSC_TSGEN_CTL_ADDR(x), HWIO_SSC_TSGEN_CTL_RMSK)
#define HWIO_SSC_TSGEN_CTL_INM(x, m)      \
        in_dword_masked(HWIO_SSC_TSGEN_CTL_ADDR(x), m)
#define HWIO_SSC_TSGEN_CTL_OUT(x, v)      \
        out_dword(HWIO_SSC_TSGEN_CTL_ADDR(x),v)
#define HWIO_SSC_TSGEN_CTL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SSC_TSGEN_CTL_ADDR(x),m,v,HWIO_SSC_TSGEN_CTL_IN(x))
#define HWIO_SSC_TSGEN_CTL_TSGEN_PRELOAD_EN_BMSK                                          0x2
#define HWIO_SSC_TSGEN_CTL_TSGEN_PRELOAD_EN_SHFT                                          0x1
#define HWIO_SSC_TSGEN_CTL_TSGEN_DISABLE_CNT_BMSK                                         0x1
#define HWIO_SSC_TSGEN_CTL_TSGEN_DISABLE_CNT_SHFT                                         0x0

#define HWIO_SSC_HM_TESTBUS_SEL_ADDR(x)                                            ((x) + 0x00006000)
#define HWIO_SSC_HM_TESTBUS_SEL_PHYS(x)                                            ((x) + 0x00006000)
#define HWIO_SSC_HM_TESTBUS_SEL_OFFS                                               (0x00006000)
#define HWIO_SSC_HM_TESTBUS_SEL_RMSK                                                   0xffff
#define HWIO_SSC_HM_TESTBUS_SEL_POR                                                0x00000000
#define HWIO_SSC_HM_TESTBUS_SEL_POR_RMSK                                           0xffffffff
#define HWIO_SSC_HM_TESTBUS_SEL_ATTR                                                      0x3
#define HWIO_SSC_HM_TESTBUS_SEL_IN(x)      \
        in_dword_masked(HWIO_SSC_HM_TESTBUS_SEL_ADDR(x), HWIO_SSC_HM_TESTBUS_SEL_RMSK)
#define HWIO_SSC_HM_TESTBUS_SEL_INM(x, m)      \
        in_dword_masked(HWIO_SSC_HM_TESTBUS_SEL_ADDR(x), m)
#define HWIO_SSC_HM_TESTBUS_SEL_OUT(x, v)      \
        out_dword(HWIO_SSC_HM_TESTBUS_SEL_ADDR(x),v)
#define HWIO_SSC_HM_TESTBUS_SEL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SSC_HM_TESTBUS_SEL_ADDR(x),m,v,HWIO_SSC_HM_TESTBUS_SEL_IN(x))
#define HWIO_SSC_HM_TESTBUS_SEL_I_TESTBUS_SEL_BMSK                                     0xffff
#define HWIO_SSC_HM_TESTBUS_SEL_I_TESTBUS_SEL_SHFT                                        0x0

#define HWIO_SSC_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_ADDR(x)                             ((x) + 0x00007000)
#define HWIO_SSC_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_PHYS(x)                             ((x) + 0x00007000)
#define HWIO_SSC_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_OFFS                                (0x00007000)
#define HWIO_SSC_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_RMSK                                0xffffffff
#define HWIO_SSC_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_POR                                 0x00000000
#define HWIO_SSC_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_POR_RMSK                            0xffffffff
#define HWIO_SSC_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_ATTR                                       0x3
#define HWIO_SSC_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_IN(x)      \
        in_dword_masked(HWIO_SSC_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_ADDR(x), HWIO_SSC_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_RMSK)
#define HWIO_SSC_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_INM(x, m)      \
        in_dword_masked(HWIO_SSC_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_ADDR(x), m)
#define HWIO_SSC_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_OUT(x, v)      \
        out_dword(HWIO_SSC_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_ADDR(x),v)
#define HWIO_SSC_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_ADDR(x),m,v,HWIO_SSC_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_IN(x))
#define HWIO_SSC_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_RFU_BMSK                            0xfffffffc
#define HWIO_SSC_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_RFU_SHFT                                   0x2
#define HWIO_SSC_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_TIMESTAMPENABLE_BMSK                       0x2
#define HWIO_SSC_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_TIMESTAMPENABLE_SHFT                       0x1
#define HWIO_SSC_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_CAPTURE_BMSK                               0x1
#define HWIO_SSC_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_CAPTURE_SHFT                               0x0

#define HWIO_SSC_QDSS_CS_QDSSCSR_AOTIMEVAL0_ADDR(x)                                ((x) + 0x00007004)
#define HWIO_SSC_QDSS_CS_QDSSCSR_AOTIMEVAL0_PHYS(x)                                ((x) + 0x00007004)
#define HWIO_SSC_QDSS_CS_QDSSCSR_AOTIMEVAL0_OFFS                                   (0x00007004)
#define HWIO_SSC_QDSS_CS_QDSSCSR_AOTIMEVAL0_RMSK                                   0xffffffff
#define HWIO_SSC_QDSS_CS_QDSSCSR_AOTIMEVAL0_POR                                    0x00000000
#define HWIO_SSC_QDSS_CS_QDSSCSR_AOTIMEVAL0_POR_RMSK                               0xffffffff
#define HWIO_SSC_QDSS_CS_QDSSCSR_AOTIMEVAL0_ATTR                                          0x1
#define HWIO_SSC_QDSS_CS_QDSSCSR_AOTIMEVAL0_IN(x)      \
        in_dword_masked(HWIO_SSC_QDSS_CS_QDSSCSR_AOTIMEVAL0_ADDR(x), HWIO_SSC_QDSS_CS_QDSSCSR_AOTIMEVAL0_RMSK)
#define HWIO_SSC_QDSS_CS_QDSSCSR_AOTIMEVAL0_INM(x, m)      \
        in_dword_masked(HWIO_SSC_QDSS_CS_QDSSCSR_AOTIMEVAL0_ADDR(x), m)
#define HWIO_SSC_QDSS_CS_QDSSCSR_AOTIMEVAL0_TIMEVAL_BMSK                           0xffffffff
#define HWIO_SSC_QDSS_CS_QDSSCSR_AOTIMEVAL0_TIMEVAL_SHFT                                  0x0

#define HWIO_SSC_QDSS_CS_QDSSCSR_AOTIMEVAL1_ADDR(x)                                ((x) + 0x00007008)
#define HWIO_SSC_QDSS_CS_QDSSCSR_AOTIMEVAL1_PHYS(x)                                ((x) + 0x00007008)
#define HWIO_SSC_QDSS_CS_QDSSCSR_AOTIMEVAL1_OFFS                                   (0x00007008)
#define HWIO_SSC_QDSS_CS_QDSSCSR_AOTIMEVAL1_RMSK                                   0xffffffff
#define HWIO_SSC_QDSS_CS_QDSSCSR_AOTIMEVAL1_POR                                    0x00000000
#define HWIO_SSC_QDSS_CS_QDSSCSR_AOTIMEVAL1_POR_RMSK                               0xffffffff
#define HWIO_SSC_QDSS_CS_QDSSCSR_AOTIMEVAL1_ATTR                                          0x1
#define HWIO_SSC_QDSS_CS_QDSSCSR_AOTIMEVAL1_IN(x)      \
        in_dword_masked(HWIO_SSC_QDSS_CS_QDSSCSR_AOTIMEVAL1_ADDR(x), HWIO_SSC_QDSS_CS_QDSSCSR_AOTIMEVAL1_RMSK)
#define HWIO_SSC_QDSS_CS_QDSSCSR_AOTIMEVAL1_INM(x, m)      \
        in_dword_masked(HWIO_SSC_QDSS_CS_QDSSCSR_AOTIMEVAL1_ADDR(x), m)
#define HWIO_SSC_QDSS_CS_QDSSCSR_AOTIMEVAL1_TIMEVAL_BMSK                           0xffffffff
#define HWIO_SSC_QDSS_CS_QDSSCSR_AOTIMEVAL1_TIMEVAL_SHFT                                  0x0

#define HWIO_SSC_QDSS_CS_QDSSCSR_QDSSTIMEVAL0_ADDR(x)                              ((x) + 0x0000700c)
#define HWIO_SSC_QDSS_CS_QDSSCSR_QDSSTIMEVAL0_PHYS(x)                              ((x) + 0x0000700c)
#define HWIO_SSC_QDSS_CS_QDSSCSR_QDSSTIMEVAL0_OFFS                                 (0x0000700c)
#define HWIO_SSC_QDSS_CS_QDSSCSR_QDSSTIMEVAL0_RMSK                                 0xffffffff
#define HWIO_SSC_QDSS_CS_QDSSCSR_QDSSTIMEVAL0_POR                                  0x00000000
#define HWIO_SSC_QDSS_CS_QDSSCSR_QDSSTIMEVAL0_POR_RMSK                             0xffffffff
#define HWIO_SSC_QDSS_CS_QDSSCSR_QDSSTIMEVAL0_ATTR                                        0x1
#define HWIO_SSC_QDSS_CS_QDSSCSR_QDSSTIMEVAL0_IN(x)      \
        in_dword_masked(HWIO_SSC_QDSS_CS_QDSSCSR_QDSSTIMEVAL0_ADDR(x), HWIO_SSC_QDSS_CS_QDSSCSR_QDSSTIMEVAL0_RMSK)
#define HWIO_SSC_QDSS_CS_QDSSCSR_QDSSTIMEVAL0_INM(x, m)      \
        in_dword_masked(HWIO_SSC_QDSS_CS_QDSSCSR_QDSSTIMEVAL0_ADDR(x), m)
#define HWIO_SSC_QDSS_CS_QDSSCSR_QDSSTIMEVAL0_TIMEVAL_BMSK                         0xffffffff
#define HWIO_SSC_QDSS_CS_QDSSCSR_QDSSTIMEVAL0_TIMEVAL_SHFT                                0x0

#define HWIO_SSC_QDSS_CS_QDSSCSR_QDSSTIMEVAL1_ADDR(x)                              ((x) + 0x00007010)
#define HWIO_SSC_QDSS_CS_QDSSCSR_QDSSTIMEVAL1_PHYS(x)                              ((x) + 0x00007010)
#define HWIO_SSC_QDSS_CS_QDSSCSR_QDSSTIMEVAL1_OFFS                                 (0x00007010)
#define HWIO_SSC_QDSS_CS_QDSSCSR_QDSSTIMEVAL1_RMSK                                 0xffffffff
#define HWIO_SSC_QDSS_CS_QDSSCSR_QDSSTIMEVAL1_POR                                  0x00000000
#define HWIO_SSC_QDSS_CS_QDSSCSR_QDSSTIMEVAL1_POR_RMSK                             0xffffffff
#define HWIO_SSC_QDSS_CS_QDSSCSR_QDSSTIMEVAL1_ATTR                                        0x1
#define HWIO_SSC_QDSS_CS_QDSSCSR_QDSSTIMEVAL1_IN(x)      \
        in_dword_masked(HWIO_SSC_QDSS_CS_QDSSCSR_QDSSTIMEVAL1_ADDR(x), HWIO_SSC_QDSS_CS_QDSSCSR_QDSSTIMEVAL1_RMSK)
#define HWIO_SSC_QDSS_CS_QDSSCSR_QDSSTIMEVAL1_INM(x, m)      \
        in_dword_masked(HWIO_SSC_QDSS_CS_QDSSCSR_QDSSTIMEVAL1_ADDR(x), m)
#define HWIO_SSC_QDSS_CS_QDSSCSR_QDSSTIMEVAL1_TIMEVAL_BMSK                         0xffffffff
#define HWIO_SSC_QDSS_CS_QDSSCSR_QDSSTIMEVAL1_TIMEVAL_SHFT                                0x0

#define HWIO_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD0_ADDR(x)                             ((x) + 0x00007014)
#define HWIO_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD0_PHYS(x)                             ((x) + 0x00007014)
#define HWIO_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD0_OFFS                                (0x00007014)
#define HWIO_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD0_RMSK                                0xffffffff
#define HWIO_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD0_POR                                 0x00000000
#define HWIO_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD0_POR_RMSK                            0xffffffff
#define HWIO_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD0_ATTR                                       0x3
#define HWIO_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD0_IN(x)      \
        in_dword_masked(HWIO_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD0_ADDR(x), HWIO_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD0_RMSK)
#define HWIO_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD0_INM(x, m)      \
        in_dword_masked(HWIO_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD0_ADDR(x), m)
#define HWIO_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD0_OUT(x, v)      \
        out_dword(HWIO_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD0_ADDR(x),v)
#define HWIO_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD0_ADDR(x),m,v,HWIO_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD0_IN(x))
#define HWIO_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD0_TIMELOAD_BMSK                       0xffffffff
#define HWIO_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD0_TIMELOAD_SHFT                              0x0

#define HWIO_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD1_ADDR(x)                             ((x) + 0x00007018)
#define HWIO_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD1_PHYS(x)                             ((x) + 0x00007018)
#define HWIO_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD1_OFFS                                (0x00007018)
#define HWIO_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD1_RMSK                                0xffffffff
#define HWIO_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD1_POR                                 0x00000000
#define HWIO_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD1_POR_RMSK                            0xffffffff
#define HWIO_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD1_ATTR                                       0x3
#define HWIO_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD1_IN(x)      \
        in_dword_masked(HWIO_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD1_ADDR(x), HWIO_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD1_RMSK)
#define HWIO_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD1_INM(x, m)      \
        in_dword_masked(HWIO_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD1_ADDR(x), m)
#define HWIO_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD1_OUT(x, v)      \
        out_dword(HWIO_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD1_ADDR(x),v)
#define HWIO_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD1_ADDR(x),m,v,HWIO_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD1_IN(x))
#define HWIO_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD1_TIMELOAD_BMSK                       0xffffffff
#define HWIO_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD1_TIMELOAD_SHFT                              0x0

#define HWIO_SSC_WAKEUP_PRIMARY_IE_ADDR(x)                                         ((x) + 0x00008000)
#define HWIO_SSC_WAKEUP_PRIMARY_IE_PHYS(x)                                         ((x) + 0x00008000)
#define HWIO_SSC_WAKEUP_PRIMARY_IE_OFFS                                            (0x00008000)
#define HWIO_SSC_WAKEUP_PRIMARY_IE_RMSK                                                 0x1ff
#define HWIO_SSC_WAKEUP_PRIMARY_IE_POR                                             0x00000000
#define HWIO_SSC_WAKEUP_PRIMARY_IE_POR_RMSK                                        0xffffffff
#define HWIO_SSC_WAKEUP_PRIMARY_IE_ATTR                                                   0x3
#define HWIO_SSC_WAKEUP_PRIMARY_IE_IN(x)      \
        in_dword_masked(HWIO_SSC_WAKEUP_PRIMARY_IE_ADDR(x), HWIO_SSC_WAKEUP_PRIMARY_IE_RMSK)
#define HWIO_SSC_WAKEUP_PRIMARY_IE_INM(x, m)      \
        in_dword_masked(HWIO_SSC_WAKEUP_PRIMARY_IE_ADDR(x), m)
#define HWIO_SSC_WAKEUP_PRIMARY_IE_OUT(x, v)      \
        out_dword(HWIO_SSC_WAKEUP_PRIMARY_IE_ADDR(x),v)
#define HWIO_SSC_WAKEUP_PRIMARY_IE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SSC_WAKEUP_PRIMARY_IE_ADDR(x),m,v,HWIO_SSC_WAKEUP_PRIMARY_IE_IN(x))
#define HWIO_SSC_WAKEUP_PRIMARY_IE_WAKEUP_IE_BMSK                                       0x1ff
#define HWIO_SSC_WAKEUP_PRIMARY_IE_WAKEUP_IE_SHFT                                         0x0

#define HWIO_SSC_WAKEUP_SECONDARY_IE_ADDR(x)                                       ((x) + 0x00009000)
#define HWIO_SSC_WAKEUP_SECONDARY_IE_PHYS(x)                                       ((x) + 0x00009000)
#define HWIO_SSC_WAKEUP_SECONDARY_IE_OFFS                                          (0x00009000)
#define HWIO_SSC_WAKEUP_SECONDARY_IE_RMSK                                               0x1ff
#define HWIO_SSC_WAKEUP_SECONDARY_IE_POR                                           0x00000000
#define HWIO_SSC_WAKEUP_SECONDARY_IE_POR_RMSK                                      0xffffffff
#define HWIO_SSC_WAKEUP_SECONDARY_IE_ATTR                                                 0x3
#define HWIO_SSC_WAKEUP_SECONDARY_IE_IN(x)      \
        in_dword_masked(HWIO_SSC_WAKEUP_SECONDARY_IE_ADDR(x), HWIO_SSC_WAKEUP_SECONDARY_IE_RMSK)
#define HWIO_SSC_WAKEUP_SECONDARY_IE_INM(x, m)      \
        in_dword_masked(HWIO_SSC_WAKEUP_SECONDARY_IE_ADDR(x), m)
#define HWIO_SSC_WAKEUP_SECONDARY_IE_OUT(x, v)      \
        out_dword(HWIO_SSC_WAKEUP_SECONDARY_IE_ADDR(x),v)
#define HWIO_SSC_WAKEUP_SECONDARY_IE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SSC_WAKEUP_SECONDARY_IE_ADDR(x),m,v,HWIO_SSC_WAKEUP_SECONDARY_IE_IN(x))
#define HWIO_SSC_WAKEUP_SECONDARY_IE_WAKEUP_IE_BMSK                                     0x1ff
#define HWIO_SSC_WAKEUP_SECONDARY_IE_WAKEUP_IE_SHFT                                       0x0

#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_0_ADDR(x)                                   ((x) + 0x0000a000)
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_0_PHYS(x)                                   ((x) + 0x0000a000)
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_0_OFFS                                      (0x0000a000)
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_0_RMSK                                      0xffffffff
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_0_POR                                       0x00000000
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_0_POR_RMSK                                  0xffffffff
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_0_ATTR                                             0x3
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_0_IN(x)      \
        in_dword_masked(HWIO_SSC_VSENSE_SENSOR0_CONFIG_0_ADDR(x), HWIO_SSC_VSENSE_SENSOR0_CONFIG_0_RMSK)
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_0_INM(x, m)      \
        in_dword_masked(HWIO_SSC_VSENSE_SENSOR0_CONFIG_0_ADDR(x), m)
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_0_OUT(x, v)      \
        out_dword(HWIO_SSC_VSENSE_SENSOR0_CONFIG_0_ADDR(x),v)
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SSC_VSENSE_SENSOR0_CONFIG_0_ADDR(x),m,v,HWIO_SSC_VSENSE_SENSOR0_CONFIG_0_IN(x))
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_0_THRESHOLD_SLOPE_BMSK                      0xff000000
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_0_THRESHOLD_SLOPE_SHFT                            0x18
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_0_THRESHOLD_MAX_BMSK                          0xff0000
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_0_THRESHOLD_MAX_SHFT                              0x10
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_0_THRESHOLD_MIN_BMSK                            0xff00
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_0_THRESHOLD_MIN_SHFT                               0x8
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_0_CAPTURE_DELAY_BMSK                              0xf0
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_0_CAPTURE_DELAY_SHFT                               0x4
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_0_TRIG_POS_BMSK                                    0xc
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_0_TRIG_POS_SHFT                                    0x2
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_0_TRIG_POS_PRE_TRIG_FVAL                           0x0
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_0_TRIG_POS_MID_TRIG_FVAL                           0x1
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_0_TRIG_POS_POST_TRIG_FVAL                          0x2
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_0_RSVD_BITS1_0_BMSK                                0x3
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_0_RSVD_BITS1_0_SHFT                                0x0

#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_1_ADDR(x)                                   ((x) + 0x0000a004)
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_1_PHYS(x)                                   ((x) + 0x0000a004)
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_1_OFFS                                      (0x0000a004)
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_1_RMSK                                      0xffffffff
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_1_POR                                       0x00000000
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_1_POR_RMSK                                  0xffffffff
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_1_ATTR                                             0x3
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_1_IN(x)      \
        in_dword_masked(HWIO_SSC_VSENSE_SENSOR0_CONFIG_1_ADDR(x), HWIO_SSC_VSENSE_SENSOR0_CONFIG_1_RMSK)
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_1_INM(x, m)      \
        in_dword_masked(HWIO_SSC_VSENSE_SENSOR0_CONFIG_1_ADDR(x), m)
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_1_OUT(x, v)      \
        out_dword(HWIO_SSC_VSENSE_SENSOR0_CONFIG_1_ADDR(x),v)
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SSC_VSENSE_SENSOR0_CONFIG_1_ADDR(x),m,v,HWIO_SSC_VSENSE_SENSOR0_CONFIG_1_IN(x))
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_1_RSVD_BITS31_24_BMSK                       0xff000000
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_1_RSVD_BITS31_24_SHFT                             0x18
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_1_FIFO_RD_ADDRESS_BMSK                        0xfc0000
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_1_FIFO_RD_ADDRESS_SHFT                            0x12
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_1_ALARM_SLOPE_NEG_EN_BMSK                      0x20000
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_1_ALARM_SLOPE_NEG_EN_SHFT                         0x11
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_1_ALARM_SLOPE_POS_EN_BMSK                      0x10000
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_1_ALARM_SLOPE_POS_EN_SHFT                         0x10
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_1_ALARM_MIN_EN_BMSK                             0x8000
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_1_ALARM_MIN_EN_SHFT                                0xf
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_1_ALARM_MAX_EN_BMSK                             0x4000
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_1_ALARM_MAX_EN_SHFT                                0xe
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_1_POWER_EN_BMSK                                 0x2000
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_1_POWER_EN_SHFT                                    0xd
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_1_FUNC_EN_BMSK                                  0x1000
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_1_FUNC_EN_SHFT                                     0xc
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_1_CLEAR_BMSK                                     0x800
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_1_CLEAR_SHFT                                       0xb
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_1_RSVD_BIT10_BMSK                                0x400
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_1_RSVD_BIT10_SHFT                                  0xa
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_1_HW_CAPTURE_EN_BMSK                             0x200
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_1_HW_CAPTURE_EN_SHFT                               0x9
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_1_SW_CAPTURE_BMSK                                0x100
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_1_SW_CAPTURE_SHFT                                  0x8
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_1_TRIG_SEL_BMSK                                   0xe0
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_1_TRIG_SEL_SHFT                                    0x5
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_1_TRIG_SEL_TRIG_SEL0_FVAL                          0x0
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_1_TRIG_SEL_TRIG_SEL1_FVAL                          0x1
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_1_TRIG_SEL_TRIG_SEL2_FVAL                          0x2
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_1_TRIG_SEL_TRIG_SEL3_FVAL                          0x3
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_1_TRIG_SEL_TRIG_SEL4_FVAL                          0x4
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_1_TRIG_SEL_TRIG_SEL5_FVAL                          0x5
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_1_TRIG_SEL_TRIG_SEL6_FVAL                          0x6
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_1_TRIG_SEL_TRIG_SEL7_FVAL                          0x7
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_1_MODE_SEL_BMSK                                   0x10
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_1_MODE_SEL_SHFT                                    0x4
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_1_MODE_SEL_ON_CHIP_SCOPING_FVAL                    0x0
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_1_MODE_SEL_FIND_VDD_MIN_MAX_FVAL                   0x1
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_1_RSVD_BIT3_BMSK                                   0x8
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_1_RSVD_BIT3_SHFT                                   0x3
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_1_SLOPE_DELTA_CYC_BMSK                             0x7
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_1_SLOPE_DELTA_CYC_SHFT                             0x0
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_1_SLOPE_DELTA_CYC_SLOPE_DELTA_LATEST_N_LATEST_MINUS_1_FVAL        0x0
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_1_SLOPE_DELTA_CYC_SLOPE_DELTA_LATEST_N_LATEST_MINUS_2_FVAL        0x1
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_1_SLOPE_DELTA_CYC_SLOPE_DELTA_LATEST_N_LATEST_MINUS_4_FVAL        0x2
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_1_SLOPE_DELTA_CYC_SLOPE_DELTA_LATEST_N_LATEST_MINUS_8_FVAL        0x3
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_1_SLOPE_DELTA_CYC_SLOPE_DELTA_LATEST_N_LATEST_MINUS_16_FVAL        0x4
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_1_SLOPE_DELTA_CYC_SLOPE_DELTA_LATEST_N_LATEST_MINUS_32_FVAL        0x5
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_1_SLOPE_DELTA_CYC_SLOPE_DELTA_LATEST_N_LATEST_MINUS_48_FVAL        0x6
#define HWIO_SSC_VSENSE_SENSOR0_CONFIG_1_SLOPE_DELTA_CYC_SLOPE_DELTA_LATEST_N_LATEST_MINUS_63_FVAL        0x7

#define HWIO_SSC_VSENSE_SENSOR0_SUMMARY_ADDR(x)                                    ((x) + 0x0000a008)
#define HWIO_SSC_VSENSE_SENSOR0_SUMMARY_PHYS(x)                                    ((x) + 0x0000a008)
#define HWIO_SSC_VSENSE_SENSOR0_SUMMARY_OFFS                                       (0x0000a008)
#define HWIO_SSC_VSENSE_SENSOR0_SUMMARY_RMSK                                          0x3ffff
#define HWIO_SSC_VSENSE_SENSOR0_SUMMARY_POR                                        0x00000000
#define HWIO_SSC_VSENSE_SENSOR0_SUMMARY_POR_RMSK                                   0xffffffff
#define HWIO_SSC_VSENSE_SENSOR0_SUMMARY_ATTR                                              0x1
#define HWIO_SSC_VSENSE_SENSOR0_SUMMARY_IN(x)      \
        in_dword_masked(HWIO_SSC_VSENSE_SENSOR0_SUMMARY_ADDR(x), HWIO_SSC_VSENSE_SENSOR0_SUMMARY_RMSK)
#define HWIO_SSC_VSENSE_SENSOR0_SUMMARY_INM(x, m)      \
        in_dword_masked(HWIO_SSC_VSENSE_SENSOR0_SUMMARY_ADDR(x), m)
#define HWIO_SSC_VSENSE_SENSOR0_SUMMARY_FIFO_DATA_BMSK                                0x3fc00
#define HWIO_SSC_VSENSE_SENSOR0_SUMMARY_FIFO_DATA_SHFT                                    0xa
#define HWIO_SSC_VSENSE_SENSOR0_SUMMARY_FSM_STATE_BMSK                                  0x3c0
#define HWIO_SSC_VSENSE_SENSOR0_SUMMARY_FSM_STATE_SHFT                                    0x6
#define HWIO_SSC_VSENSE_SENSOR0_SUMMARY_FIFO_COMPLETE_BMSK                               0x20
#define HWIO_SSC_VSENSE_SENSOR0_SUMMARY_FIFO_COMPLETE_SHFT                                0x5
#define HWIO_SSC_VSENSE_SENSOR0_SUMMARY_FIFO_ACTIVE_BMSK                                 0x10
#define HWIO_SSC_VSENSE_SENSOR0_SUMMARY_FIFO_ACTIVE_SHFT                                  0x4
#define HWIO_SSC_VSENSE_SENSOR0_SUMMARY_ALARM_MAX_BMSK                                    0x8
#define HWIO_SSC_VSENSE_SENSOR0_SUMMARY_ALARM_MAX_SHFT                                    0x3
#define HWIO_SSC_VSENSE_SENSOR0_SUMMARY_ALARM_MIN_BMSK                                    0x4
#define HWIO_SSC_VSENSE_SENSOR0_SUMMARY_ALARM_MIN_SHFT                                    0x2
#define HWIO_SSC_VSENSE_SENSOR0_SUMMARY_ALARM_SLOPE_NEG_BMSK                              0x2
#define HWIO_SSC_VSENSE_SENSOR0_SUMMARY_ALARM_SLOPE_NEG_SHFT                              0x1
#define HWIO_SSC_VSENSE_SENSOR0_SUMMARY_ALARM_SLOPE_POS_BMSK                              0x1
#define HWIO_SSC_VSENSE_SENSOR0_SUMMARY_ALARM_SLOPE_POS_SHFT                              0x0

#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_0_ADDR(x)                                   ((x) + 0x0000a00c)
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_0_PHYS(x)                                   ((x) + 0x0000a00c)
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_0_OFFS                                      (0x0000a00c)
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_0_RMSK                                      0xffffffff
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_0_POR                                       0x00000000
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_0_POR_RMSK                                  0xffffffff
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_0_ATTR                                             0x3
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_0_IN(x)      \
        in_dword_masked(HWIO_SSC_VSENSE_SENSOR1_CONFIG_0_ADDR(x), HWIO_SSC_VSENSE_SENSOR1_CONFIG_0_RMSK)
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_0_INM(x, m)      \
        in_dword_masked(HWIO_SSC_VSENSE_SENSOR1_CONFIG_0_ADDR(x), m)
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_0_OUT(x, v)      \
        out_dword(HWIO_SSC_VSENSE_SENSOR1_CONFIG_0_ADDR(x),v)
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SSC_VSENSE_SENSOR1_CONFIG_0_ADDR(x),m,v,HWIO_SSC_VSENSE_SENSOR1_CONFIG_0_IN(x))
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_0_THRESHOLD_SLOPE_BMSK                      0xff000000
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_0_THRESHOLD_SLOPE_SHFT                            0x18
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_0_THRESHOLD_MAX_BMSK                          0xff0000
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_0_THRESHOLD_MAX_SHFT                              0x10
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_0_THRESHOLD_MIN_BMSK                            0xff00
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_0_THRESHOLD_MIN_SHFT                               0x8
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_0_CAPTURE_DELAY_BMSK                              0xf0
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_0_CAPTURE_DELAY_SHFT                               0x4
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_0_TRIG_POS_BMSK                                    0xc
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_0_TRIG_POS_SHFT                                    0x2
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_0_TRIG_POS_PRE_TRIG_FVAL                           0x0
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_0_TRIG_POS_MID_TRIG_FVAL                           0x1
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_0_TRIG_POS_POST_TRIG_FVAL                          0x2
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_0_RSVD_BITS1_0_BMSK                                0x3
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_0_RSVD_BITS1_0_SHFT                                0x0

#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_1_ADDR(x)                                   ((x) + 0x0000a010)
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_1_PHYS(x)                                   ((x) + 0x0000a010)
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_1_OFFS                                      (0x0000a010)
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_1_RMSK                                      0xffffffff
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_1_POR                                       0x00000000
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_1_POR_RMSK                                  0xffffffff
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_1_ATTR                                             0x3
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_1_IN(x)      \
        in_dword_masked(HWIO_SSC_VSENSE_SENSOR1_CONFIG_1_ADDR(x), HWIO_SSC_VSENSE_SENSOR1_CONFIG_1_RMSK)
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_1_INM(x, m)      \
        in_dword_masked(HWIO_SSC_VSENSE_SENSOR1_CONFIG_1_ADDR(x), m)
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_1_OUT(x, v)      \
        out_dword(HWIO_SSC_VSENSE_SENSOR1_CONFIG_1_ADDR(x),v)
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SSC_VSENSE_SENSOR1_CONFIG_1_ADDR(x),m,v,HWIO_SSC_VSENSE_SENSOR1_CONFIG_1_IN(x))
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_1_RSVD_BITS31_24_BMSK                       0xff000000
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_1_RSVD_BITS31_24_SHFT                             0x18
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_1_FIFO_RD_ADDRESS_BMSK                        0xfc0000
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_1_FIFO_RD_ADDRESS_SHFT                            0x12
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_1_ALARM_SLOPE_NEG_EN_BMSK                      0x20000
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_1_ALARM_SLOPE_NEG_EN_SHFT                         0x11
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_1_ALARM_SLOPE_POS_EN_BMSK                      0x10000
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_1_ALARM_SLOPE_POS_EN_SHFT                         0x10
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_1_ALARM_MIN_EN_BMSK                             0x8000
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_1_ALARM_MIN_EN_SHFT                                0xf
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_1_ALARM_MAX_EN_BMSK                             0x4000
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_1_ALARM_MAX_EN_SHFT                                0xe
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_1_POWER_EN_BMSK                                 0x2000
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_1_POWER_EN_SHFT                                    0xd
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_1_FUNC_EN_BMSK                                  0x1000
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_1_FUNC_EN_SHFT                                     0xc
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_1_CLEAR_BMSK                                     0x800
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_1_CLEAR_SHFT                                       0xb
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_1_RSVD_BIT10_BMSK                                0x400
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_1_RSVD_BIT10_SHFT                                  0xa
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_1_HW_CAPTURE_EN_BMSK                             0x200
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_1_HW_CAPTURE_EN_SHFT                               0x9
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_1_SW_CAPTURE_BMSK                                0x100
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_1_SW_CAPTURE_SHFT                                  0x8
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_1_TRIG_SEL_BMSK                                   0xe0
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_1_TRIG_SEL_SHFT                                    0x5
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_1_TRIG_SEL_TRIG_SEL0_FVAL                          0x0
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_1_TRIG_SEL_TRIG_SEL1_FVAL                          0x1
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_1_TRIG_SEL_TRIG_SEL2_FVAL                          0x2
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_1_TRIG_SEL_TRIG_SEL3_FVAL                          0x3
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_1_TRIG_SEL_TRIG_SEL4_FVAL                          0x4
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_1_TRIG_SEL_TRIG_SEL5_FVAL                          0x5
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_1_TRIG_SEL_TRIG_SEL6_FVAL                          0x6
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_1_TRIG_SEL_TRIG_SEL7_FVAL                          0x7
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_1_MODE_SEL_BMSK                                   0x10
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_1_MODE_SEL_SHFT                                    0x4
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_1_MODE_SEL_ON_CHIP_SCOPING_FVAL                    0x0
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_1_MODE_SEL_FIND_VDD_MIN_MAX_FVAL                   0x1
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_1_RSVD_BIT3_BMSK                                   0x8
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_1_RSVD_BIT3_SHFT                                   0x3
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_1_SLOPE_DELTA_CYC_BMSK                             0x7
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_1_SLOPE_DELTA_CYC_SHFT                             0x0
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_1_SLOPE_DELTA_CYC_SLOPE_DELTA_LATEST_N_LATEST_MINUS_1_FVAL        0x0
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_1_SLOPE_DELTA_CYC_SLOPE_DELTA_LATEST_N_LATEST_MINUS_2_FVAL        0x1
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_1_SLOPE_DELTA_CYC_SLOPE_DELTA_LATEST_N_LATEST_MINUS_4_FVAL        0x2
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_1_SLOPE_DELTA_CYC_SLOPE_DELTA_LATEST_N_LATEST_MINUS_8_FVAL        0x3
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_1_SLOPE_DELTA_CYC_SLOPE_DELTA_LATEST_N_LATEST_MINUS_16_FVAL        0x4
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_1_SLOPE_DELTA_CYC_SLOPE_DELTA_LATEST_N_LATEST_MINUS_32_FVAL        0x5
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_1_SLOPE_DELTA_CYC_SLOPE_DELTA_LATEST_N_LATEST_MINUS_48_FVAL        0x6
#define HWIO_SSC_VSENSE_SENSOR1_CONFIG_1_SLOPE_DELTA_CYC_SLOPE_DELTA_LATEST_N_LATEST_MINUS_63_FVAL        0x7

#define HWIO_SSC_VSENSE_SENSOR1_SUMMARY_ADDR(x)                                    ((x) + 0x0000a014)
#define HWIO_SSC_VSENSE_SENSOR1_SUMMARY_PHYS(x)                                    ((x) + 0x0000a014)
#define HWIO_SSC_VSENSE_SENSOR1_SUMMARY_OFFS                                       (0x0000a014)
#define HWIO_SSC_VSENSE_SENSOR1_SUMMARY_RMSK                                          0x3ffff
#define HWIO_SSC_VSENSE_SENSOR1_SUMMARY_POR                                        0x00000000
#define HWIO_SSC_VSENSE_SENSOR1_SUMMARY_POR_RMSK                                   0xffffffff
#define HWIO_SSC_VSENSE_SENSOR1_SUMMARY_ATTR                                              0x1
#define HWIO_SSC_VSENSE_SENSOR1_SUMMARY_IN(x)      \
        in_dword_masked(HWIO_SSC_VSENSE_SENSOR1_SUMMARY_ADDR(x), HWIO_SSC_VSENSE_SENSOR1_SUMMARY_RMSK)
#define HWIO_SSC_VSENSE_SENSOR1_SUMMARY_INM(x, m)      \
        in_dword_masked(HWIO_SSC_VSENSE_SENSOR1_SUMMARY_ADDR(x), m)
#define HWIO_SSC_VSENSE_SENSOR1_SUMMARY_FIFO_DATA_BMSK                                0x3fc00
#define HWIO_SSC_VSENSE_SENSOR1_SUMMARY_FIFO_DATA_SHFT                                    0xa
#define HWIO_SSC_VSENSE_SENSOR1_SUMMARY_FSM_STATE_BMSK                                  0x3c0
#define HWIO_SSC_VSENSE_SENSOR1_SUMMARY_FSM_STATE_SHFT                                    0x6
#define HWIO_SSC_VSENSE_SENSOR1_SUMMARY_FIFO_COMPLETE_BMSK                               0x20
#define HWIO_SSC_VSENSE_SENSOR1_SUMMARY_FIFO_COMPLETE_SHFT                                0x5
#define HWIO_SSC_VSENSE_SENSOR1_SUMMARY_FIFO_ACTIVE_BMSK                                 0x10
#define HWIO_SSC_VSENSE_SENSOR1_SUMMARY_FIFO_ACTIVE_SHFT                                  0x4
#define HWIO_SSC_VSENSE_SENSOR1_SUMMARY_ALARM_MAX_BMSK                                    0x8
#define HWIO_SSC_VSENSE_SENSOR1_SUMMARY_ALARM_MAX_SHFT                                    0x3
#define HWIO_SSC_VSENSE_SENSOR1_SUMMARY_ALARM_MIN_BMSK                                    0x4
#define HWIO_SSC_VSENSE_SENSOR1_SUMMARY_ALARM_MIN_SHFT                                    0x2
#define HWIO_SSC_VSENSE_SENSOR1_SUMMARY_ALARM_SLOPE_NEG_BMSK                              0x2
#define HWIO_SSC_VSENSE_SENSOR1_SUMMARY_ALARM_SLOPE_NEG_SHFT                              0x1
#define HWIO_SSC_VSENSE_SENSOR1_SUMMARY_ALARM_SLOPE_POS_BMSK                              0x1
#define HWIO_SSC_VSENSE_SENSOR1_SUMMARY_ALARM_SLOPE_POS_SHFT                              0x0

#define HWIO_SSC_EFUSE_Q6SS_EVB_SEL_ADDR(x)                                        ((x) + 0x0000b000)
#define HWIO_SSC_EFUSE_Q6SS_EVB_SEL_PHYS(x)                                        ((x) + 0x0000b000)
#define HWIO_SSC_EFUSE_Q6SS_EVB_SEL_OFFS                                           (0x0000b000)
#define HWIO_SSC_EFUSE_Q6SS_EVB_SEL_RMSK                                                  0x1
#define HWIO_SSC_EFUSE_Q6SS_EVB_SEL_POR                                            0x00000001
#define HWIO_SSC_EFUSE_Q6SS_EVB_SEL_POR_RMSK                                       0xffffffff
#define HWIO_SSC_EFUSE_Q6SS_EVB_SEL_ATTR                                                  0x3
#define HWIO_SSC_EFUSE_Q6SS_EVB_SEL_IN(x)      \
        in_dword_masked(HWIO_SSC_EFUSE_Q6SS_EVB_SEL_ADDR(x), HWIO_SSC_EFUSE_Q6SS_EVB_SEL_RMSK)
#define HWIO_SSC_EFUSE_Q6SS_EVB_SEL_INM(x, m)      \
        in_dword_masked(HWIO_SSC_EFUSE_Q6SS_EVB_SEL_ADDR(x), m)
#define HWIO_SSC_EFUSE_Q6SS_EVB_SEL_OUT(x, v)      \
        out_dword(HWIO_SSC_EFUSE_Q6SS_EVB_SEL_ADDR(x),v)
#define HWIO_SSC_EFUSE_Q6SS_EVB_SEL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SSC_EFUSE_Q6SS_EVB_SEL_ADDR(x),m,v,HWIO_SSC_EFUSE_Q6SS_EVB_SEL_IN(x))
#define HWIO_SSC_EFUSE_Q6SS_EVB_SEL_SEL_BMSK                                              0x1
#define HWIO_SSC_EFUSE_Q6SS_EVB_SEL_SEL_SHFT                                              0x0

#define HWIO_SSC_EFUSE_Q6SS_EVB_ADDR_ADDR(x)                                       ((x) + 0x0000b004)
#define HWIO_SSC_EFUSE_Q6SS_EVB_ADDR_PHYS(x)                                       ((x) + 0x0000b004)
#define HWIO_SSC_EFUSE_Q6SS_EVB_ADDR_OFFS                                          (0x0000b004)
#define HWIO_SSC_EFUSE_Q6SS_EVB_ADDR_RMSK                                           0xfffffff
#define HWIO_SSC_EFUSE_Q6SS_EVB_ADDR_POR                                           0x00000000
#define HWIO_SSC_EFUSE_Q6SS_EVB_ADDR_POR_RMSK                                      0xffffffff
#define HWIO_SSC_EFUSE_Q6SS_EVB_ADDR_ATTR                                                 0x3
#define HWIO_SSC_EFUSE_Q6SS_EVB_ADDR_IN(x)      \
        in_dword_masked(HWIO_SSC_EFUSE_Q6SS_EVB_ADDR_ADDR(x), HWIO_SSC_EFUSE_Q6SS_EVB_ADDR_RMSK)
#define HWIO_SSC_EFUSE_Q6SS_EVB_ADDR_INM(x, m)      \
        in_dword_masked(HWIO_SSC_EFUSE_Q6SS_EVB_ADDR_ADDR(x), m)
#define HWIO_SSC_EFUSE_Q6SS_EVB_ADDR_OUT(x, v)      \
        out_dword(HWIO_SSC_EFUSE_Q6SS_EVB_ADDR_ADDR(x),v)
#define HWIO_SSC_EFUSE_Q6SS_EVB_ADDR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SSC_EFUSE_Q6SS_EVB_ADDR_ADDR(x),m,v,HWIO_SSC_EFUSE_Q6SS_EVB_ADDR_IN(x))
#define HWIO_SSC_EFUSE_Q6SS_EVB_ADDR_ADDR_BMSK                                      0xffffff0
#define HWIO_SSC_EFUSE_Q6SS_EVB_ADDR_ADDR_SHFT                                            0x4
#define HWIO_SSC_EFUSE_Q6SS_EVB_ADDR_RSVD_BIT3_0_BMSK                                     0xf
#define HWIO_SSC_EFUSE_Q6SS_EVB_ADDR_RSVD_BIT3_0_SHFT                                     0x0

#endif /* __TIMERHWIO_H__ */
