#ifndef __HWIO_TLMM_UFS_H__
#define __HWIO_TLMM_UFS_H__
/*
===========================================================================
*/
/**
  @file hwio_tlmm_ufs.h
  @brief Auto-generated HWIO interface include file.

  Reference chip release:
    SDM660 (Starlord) [starlord_v1.0.2_p3q3r108_MTO]
 
  This file contains HWIO register definitions for the following modules:
    TLMM_NORTH


  Generation parameters: 
  { u'filename': u'hwio_tlmm_ufs.h',
    u'module-filter-exclude': { },
    u'module-filter-include': { },
    u'modules': [u'TLMM_NORTH']}
*/
/*
  ===========================================================================

  Copyright (c) 2018 Qualcomm Technologies, Inc.
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

  $Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Settings/UFS/inc/hwio_tlmm_ufs.h#1 $
  $DateTime: 2018/10/16 09:22:30 $
  $Author: pwbldsvc $

  ===========================================================================
*/

/*----------------------------------------------------------------------------
 * MODULE: TLMM_NORTH
 *--------------------------------------------------------------------------*/

#define TLMM_BASE                            0x03000000
 
#define TLMM_NORTH_REG_BASE                                                (TLMM_BASE      + 0x00900000)
#define TLMM_NORTH_REG_BASE_SIZE                                           0x300000
#define TLMM_NORTH_REG_BASE_USED                                           0xaa004

#define HWIO_TLMM_UFS_REF_CLK_CTL_ADDR                                     (TLMM_NORTH_REG_BASE      + 0x000a1000)
#define HWIO_TLMM_UFS_REF_CLK_CTL_RMSK                                           0x1f
#define HWIO_TLMM_UFS_REF_CLK_CTL_IN          \
        in_dword(HWIO_TLMM_UFS_REF_CLK_CTL_ADDR)
#define HWIO_TLMM_UFS_REF_CLK_CTL_INM(m)      \
        in_dword_masked(HWIO_TLMM_UFS_REF_CLK_CTL_ADDR, m)
#define HWIO_TLMM_UFS_REF_CLK_CTL_OUT(v)      \
        out_dword(HWIO_TLMM_UFS_REF_CLK_CTL_ADDR,v)
#define HWIO_TLMM_UFS_REF_CLK_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_UFS_REF_CLK_CTL_ADDR,m,v,HWIO_TLMM_UFS_REF_CLK_CTL_IN)
#define HWIO_TLMM_UFS_REF_CLK_CTL_UFS_REF_CLK_PULL_BMSK                          0x18
#define HWIO_TLMM_UFS_REF_CLK_CTL_UFS_REF_CLK_PULL_SHFT                           0x3
#define HWIO_TLMM_UFS_REF_CLK_CTL_UFS_REF_CLK_HDRV_BMSK                           0x7
#define HWIO_TLMM_UFS_REF_CLK_CTL_UFS_REF_CLK_HDRV_SHFT                           0x0

#define HWIO_TLMM_UFS_RESET_CTL_ADDR                                       (TLMM_NORTH_REG_BASE      + 0x000a3000)
#define HWIO_TLMM_UFS_RESET_CTL_RMSK                                             0x1f
#define HWIO_TLMM_UFS_RESET_CTL_IN          \
        in_dword(HWIO_TLMM_UFS_RESET_CTL_ADDR)
#define HWIO_TLMM_UFS_RESET_CTL_INM(m)      \
        in_dword_masked(HWIO_TLMM_UFS_RESET_CTL_ADDR, m)
#define HWIO_TLMM_UFS_RESET_CTL_OUT(v)      \
        out_dword(HWIO_TLMM_UFS_RESET_CTL_ADDR,v)
#define HWIO_TLMM_UFS_RESET_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_UFS_RESET_CTL_ADDR,m,v,HWIO_TLMM_UFS_RESET_CTL_IN)
#define HWIO_TLMM_UFS_RESET_CTL_UFS_RESET_PULL_BMSK                              0x18
#define HWIO_TLMM_UFS_RESET_CTL_UFS_RESET_PULL_SHFT                               0x3
#define HWIO_TLMM_UFS_RESET_CTL_UFS_RESET_HDRV_BMSK                               0x7
#define HWIO_TLMM_UFS_RESET_CTL_UFS_RESET_HDRV_SHFT                               0x0

#define HWIO_TLMM_UFS_RESET_ADDR                                           (TLMM_NORTH_REG_BASE      + 0x000a3004)
#define HWIO_TLMM_UFS_RESET_RMSK                                                  0x1
#define HWIO_TLMM_UFS_RESET_IN          \
        in_dword(HWIO_TLMM_UFS_RESET_ADDR)
#define HWIO_TLMM_UFS_RESET_INM(m)      \
        in_dword_masked(HWIO_TLMM_UFS_RESET_ADDR, m)
#define HWIO_TLMM_UFS_RESET_OUT(v)      \
        out_dword(HWIO_TLMM_UFS_RESET_ADDR,v)
#define HWIO_TLMM_UFS_RESET_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_UFS_RESET_ADDR,m,v,HWIO_TLMM_UFS_RESET_IN)
#define HWIO_TLMM_UFS_RESET_UFS_RESET_BMSK                                        0x1
#define HWIO_TLMM_UFS_RESET_UFS_RESET_SHFT                                        0x0


#endif /* __HWIO_TLMM_UFS_H__ */
