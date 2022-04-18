#ifndef __UINT_L2VIC_H__
#define __UINT_L2VIC_H__
/*
===========================================================================
*/
/**
  @file uInt_l2vic.h
  @brief Auto-generated HWIO interface include file.

  Reference chip release:
    SDM660 (Starlord) [starlord_v1.0_p3q3r97_MTO]
 
  This file contains HWIO register definitions for the following modules:
    LPASS_QDSP6V60SS_L2VIC

  'Include' filters applied: 
  'Exclude' filters applied: 
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

  $Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/InterruptController/src/qurt/kernel/uimage/uInt_l2vic.h#1 $
  $DateTime: 2020/02/10 01:57:30 $
  $Author: pwbldsvc $

  ===========================================================================
*/
#include "msmhwiobase.h"

/*----------------------------------------------------------------------------
 * MODULE: LPASS_QDSP6V60SS_L2VIC
 *--------------------------------------------------------------------------*/

#define LPASS_QDSP6V60SS_L2VIC_REG_BASE                                (LPASS_BASE      + 0x00790000)

#define HWIO_LPASS_QDSP6SS_L2VIC_VID_ADDR                              (LPASS_QDSP6V60SS_L2VIC_REG_BASE      + 0x00000000)
#define HWIO_LPASS_QDSP6SS_L2VIC_VID_RMSK                                   0x3ff
#define HWIO_LPASS_QDSP6SS_L2VIC_VID_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_L2VIC_VID_ADDR, HWIO_LPASS_QDSP6SS_L2VIC_VID_RMSK)
#define HWIO_LPASS_QDSP6SS_L2VIC_VID_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_L2VIC_VID_ADDR, m)
#define HWIO_LPASS_QDSP6SS_L2VIC_VID_VID_BMSK                               0x3ff
#define HWIO_LPASS_QDSP6SS_L2VIC_VID_VID_SHFT                                 0x0

#define HWIO_LPASS_QDSP6SS_L2VIC_INT_ENABLEn_ADDR(n)                   (LPASS_QDSP6V60SS_L2VIC_REG_BASE      + 0x00000100 + 0x4 * (n))
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_ENABLEn_RMSK                      0xffffffff
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_ENABLEn_MAXn                              31
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_ENABLEn_INI(n)        \
        in_dword_masked(HWIO_LPASS_QDSP6SS_L2VIC_INT_ENABLEn_ADDR(n), HWIO_LPASS_QDSP6SS_L2VIC_INT_ENABLEn_RMSK)
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_ENABLEn_INMI(n,mask)    \
        in_dword_masked(HWIO_LPASS_QDSP6SS_L2VIC_INT_ENABLEn_ADDR(n), mask)
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_ENABLEn_OUTI(n,val)    \
        out_dword(HWIO_LPASS_QDSP6SS_L2VIC_INT_ENABLEn_ADDR(n),val)
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_ENABLEn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_L2VIC_INT_ENABLEn_ADDR(n),mask,val,HWIO_LPASS_QDSP6SS_L2VIC_INT_ENABLEn_INI(n))
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_ENABLEn_ENABLE_BMSK               0xffffffff
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_ENABLEn_ENABLE_SHFT                      0x0

#define HWIO_LPASS_QDSP6SS_L2VIC_INT_ENABLE_CLEARn_ADDR(n)             (LPASS_QDSP6V60SS_L2VIC_REG_BASE      + 0x00000180 + 0x4 * (n))
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_ENABLE_CLEARn_RMSK                0xffffffff
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_ENABLE_CLEARn_MAXn                        31
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_ENABLE_CLEARn_OUTI(n,val)    \
        out_dword(HWIO_LPASS_QDSP6SS_L2VIC_INT_ENABLE_CLEARn_ADDR(n),val)
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_ENABLE_CLEARn_CLEAR_BMSK          0xffffffff
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_ENABLE_CLEARn_CLEAR_SHFT                 0x0

#define HWIO_LPASS_QDSP6SS_L2VIC_INT_ENABLE_SETn_ADDR(n)               (LPASS_QDSP6V60SS_L2VIC_REG_BASE      + 0x00000200 + 0x4 * (n))
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_ENABLE_SETn_RMSK                  0xffffffff
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_ENABLE_SETn_MAXn                          31
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_ENABLE_SETn_OUTI(n,val)    \
        out_dword(HWIO_LPASS_QDSP6SS_L2VIC_INT_ENABLE_SETn_ADDR(n),val)
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_ENABLE_SETn_SET_BMSK              0xffffffff
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_ENABLE_SETn_SET_SHFT                     0x0

#define HWIO_LPASS_QDSP6SS_L2VIC_INT_TYPEn_ADDR(n)                     (LPASS_QDSP6V60SS_L2VIC_REG_BASE      + 0x00000280 + 0x4 * (n))
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_TYPEn_RMSK                        0xffffffff
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_TYPEn_MAXn                                31
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_TYPEn_INI(n)        \
        in_dword_masked(HWIO_LPASS_QDSP6SS_L2VIC_INT_TYPEn_ADDR(n), HWIO_LPASS_QDSP6SS_L2VIC_INT_TYPEn_RMSK)
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_TYPEn_INMI(n,mask)    \
        in_dword_masked(HWIO_LPASS_QDSP6SS_L2VIC_INT_TYPEn_ADDR(n), mask)
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_TYPEn_OUTI(n,val)    \
        out_dword(HWIO_LPASS_QDSP6SS_L2VIC_INT_TYPEn_ADDR(n),val)
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_TYPEn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_L2VIC_INT_TYPEn_ADDR(n),mask,val,HWIO_LPASS_QDSP6SS_L2VIC_INT_TYPEn_INI(n))
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_TYPEn_SRC_TYPE_BMSK               0xffffffff
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_TYPEn_SRC_TYPE_SHFT                      0x0

#define HWIO_LPASS_QDSP6SS_L2VIC_INT_STATUSn_ADDR(n)                   (LPASS_QDSP6V60SS_L2VIC_REG_BASE      + 0x00000380 + 0x4 * (n))
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_STATUSn_RMSK                      0xffffffff
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_STATUSn_MAXn                              31
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_STATUSn_INI(n)        \
        in_dword_masked(HWIO_LPASS_QDSP6SS_L2VIC_INT_STATUSn_ADDR(n), HWIO_LPASS_QDSP6SS_L2VIC_INT_STATUSn_RMSK)
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_STATUSn_INMI(n,mask)    \
        in_dword_masked(HWIO_LPASS_QDSP6SS_L2VIC_INT_STATUSn_ADDR(n), mask)
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_STATUSn_STATUS_BMSK               0xffffffff
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_STATUSn_STATUS_SHFT                      0x0

#define HWIO_LPASS_QDSP6SS_L2VIC_INT_CLEARn_ADDR(n)                    (LPASS_QDSP6V60SS_L2VIC_REG_BASE      + 0x00000400 + 0x4 * (n))
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_CLEARn_RMSK                       0xffffffff
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_CLEARn_MAXn                               31
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_CLEARn_OUTI(n,val)    \
        out_dword(HWIO_LPASS_QDSP6SS_L2VIC_INT_CLEARn_ADDR(n),val)
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_CLEARn_CLEAR_BMSK                 0xffffffff
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_CLEARn_CLEAR_SHFT                        0x0

#define HWIO_LPASS_QDSP6SS_L2VIC_SOFT_INTn_ADDR(n)                     (LPASS_QDSP6V60SS_L2VIC_REG_BASE      + 0x00000480 + 0x4 * (n))
#define HWIO_LPASS_QDSP6SS_L2VIC_SOFT_INTn_RMSK                        0xffffffff
#define HWIO_LPASS_QDSP6SS_L2VIC_SOFT_INTn_MAXn                                31
#define HWIO_LPASS_QDSP6SS_L2VIC_SOFT_INTn_OUTI(n,val)    \
        out_dword(HWIO_LPASS_QDSP6SS_L2VIC_SOFT_INTn_ADDR(n),val)
#define HWIO_LPASS_QDSP6SS_L2VIC_SOFT_INTn_SW_INT_BMSK                 0xffffffff
#define HWIO_LPASS_QDSP6SS_L2VIC_SOFT_INTn_SW_INT_SHFT                        0x0

#define HWIO_LPASS_QDSP6SS_L2VIC_INT_PENDINGn_ADDR(n)                  (LPASS_QDSP6V60SS_L2VIC_REG_BASE      + 0x00000500 + 0x4 * (n))
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_PENDINGn_RMSK                     0xffffffff
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_PENDINGn_MAXn                             31
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_PENDINGn_INI(n)        \
        in_dword_masked(HWIO_LPASS_QDSP6SS_L2VIC_INT_PENDINGn_ADDR(n), HWIO_LPASS_QDSP6SS_L2VIC_INT_PENDINGn_RMSK)
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_PENDINGn_INMI(n,mask)    \
        in_dword_masked(HWIO_LPASS_QDSP6SS_L2VIC_INT_PENDINGn_ADDR(n), mask)
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_PENDINGn_STATUS_BMSK              0xffffffff
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_PENDINGn_STATUS_SHFT                     0x0


#endif /* __UINT_L2VIC_H__ */
