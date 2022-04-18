#ifndef __HWIO_GCC_UFS_H__
#define __HWIO_GCC_UFS_H__
/*
===========================================================================
*/
/**
  @file hwio_gcc_ufs.h
  @brief Auto-generated HWIO interface include file.

  Reference chip release:
    SDM660 (Starlord) [starlord_v1.0.2_p3q3r108_MTO]
 
  This file contains HWIO register definitions for the following modules:
    GCC_CLK_CTL_REG


  Generation parameters: 
  { u'filename': u'hwio_gcc_ufs.h',
    u'module-filter-exclude': { },
    u'module-filter-include': { },
    u'modules': [u'GCC_CLK_CTL_REG']}
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

  $Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Settings/UFS/inc/hwio_gcc_ufs.h#1 $
  $DateTime: 2018/10/16 09:22:30 $
  $Author: pwbldsvc $

  ===========================================================================
*/

/*----------------------------------------------------------------------------
 * MODULE: GCC_CLK_CTL_REG
 *--------------------------------------------------------------------------*/

#define CLK_CTL_BASE                                                0x00100000

#define GCC_CLK_CTL_REG_REG_BASE                                                                  (CLK_CTL_BASE      + 0x00000000)
#define GCC_CLK_CTL_REG_REG_BASE_SIZE                                                             0xb0000
#define GCC_CLK_CTL_REG_REG_BASE_USED                                                             0x94000

#define HWIO_GCC_UFS_BCR_ADDR                                                                     (GCC_CLK_CTL_REG_REG_BASE      + 0x00075000)
#define HWIO_GCC_UFS_BCR_RMSK                                                                            0x1
#define HWIO_GCC_UFS_BCR_IN          \
        in_dword(HWIO_GCC_UFS_BCR_ADDR)
#define HWIO_GCC_UFS_BCR_INM(m)      \
        in_dword_masked(HWIO_GCC_UFS_BCR_ADDR, m)
#define HWIO_GCC_UFS_BCR_OUT(v)      \
        out_dword(HWIO_GCC_UFS_BCR_ADDR,v)
#define HWIO_GCC_UFS_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_UFS_BCR_ADDR,m,v,HWIO_GCC_UFS_BCR_IN)
#define HWIO_GCC_UFS_BCR_BLK_ARES_BMSK                                                                   0x1
#define HWIO_GCC_UFS_BCR_BLK_ARES_SHFT                                                                   0x0


#endif /* __HWIO_GCC_UFS_H__ */
