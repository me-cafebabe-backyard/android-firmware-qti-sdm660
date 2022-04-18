#ifndef __GCC_RESET_HWIO_H__
#define __GCC_RESET_HWIO_H__
/*
===========================================================================
*/
/**
  @file gcc_reset_hwio.h
  @brief Auto-generated HWIO interface include file.

  Reference chip release:
    SDM660 (Starlord) [starlord_v1.0.2_p3q3r108_MTO]
 
  This file contains HWIO register definitions for the following modules:
    GCC_CLK_CTL_REG

  'Include' filters applied: GCC_RESET_STATUS[GCC_CLK_CTL_REG] 
  'Exclude' filters applied: RESERVED DUMMY 
*/
/*
  ===========================================================================

  Copyright (c) 2017 Qualcomm Technologies, Inc.
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

  $Header: //components/rel/rpm.bf/1.8/core/bsp/rpm/inc/gcc_reset_hwio.h#2 $
  $DateTime: 2017/04/20 03:39:35 $
  $Author: pwbldsvc $

  ===========================================================================
*/

#include "msmhwiobase.h"
/*----------------------------------------------------------------------------
 * MODULE: GCC_CLK_CTL_REG
 *--------------------------------------------------------------------------*/

#define GCC_CLK_CTL_REG_REG_BASE                                                                 (CLK_CTL_BASE      + 0x00000000)

#define HWIO_GCC_RESET_STATUS_ADDR                                                                (GCC_CLK_CTL_REG_REG_BASE      + 0x00061020)
#define HWIO_GCC_RESET_STATUS_RMSK                                                                     0x3ff
#define HWIO_GCC_RESET_STATUS_IN          \
        in_dword_masked(HWIO_GCC_RESET_STATUS_ADDR, HWIO_GCC_RESET_STATUS_RMSK)
#define HWIO_GCC_RESET_STATUS_INM(m)      \
        in_dword_masked(HWIO_GCC_RESET_STATUS_ADDR, m)
#define HWIO_GCC_RESET_STATUS_OUT(v)      \
        out_dword(HWIO_GCC_RESET_STATUS_ADDR,v)
#define HWIO_GCC_RESET_STATUS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_RESET_STATUS_ADDR,m,v,HWIO_GCC_RESET_STATUS_IN)
#define HWIO_GCC_RESET_STATUS_PS_HOLD_STATUS_BMSK                                                      0x200
#define HWIO_GCC_RESET_STATUS_PS_HOLD_STATUS_SHFT                                                        0x9
#define HWIO_GCC_RESET_STATUS_QDSS_SW_SRST_RESET_STATUS_BMSK                                           0x100
#define HWIO_GCC_RESET_STATUS_QDSS_SW_SRST_RESET_STATUS_SHFT                                             0x8
#define HWIO_GCC_RESET_STATUS_EUD_SRST_RESET_STATUS_BMSK                                                0x80
#define HWIO_GCC_RESET_STATUS_EUD_SRST_RESET_STATUS_SHFT                                                 0x7
#define HWIO_GCC_RESET_STATUS_PMIC_ABNORMAL_RESIN_RESET_STATUS_BMSK                                     0x40
#define HWIO_GCC_RESET_STATUS_PMIC_ABNORMAL_RESIN_RESET_STATUS_SHFT                                      0x6
#define HWIO_GCC_RESET_STATUS_MSM_TSENSE1_RESET_STATUS_BMSK                                            0x20
#define HWIO_GCC_RESET_STATUS_MSM_TSENSE1_RESET_STATUS_SHFT                                             0x5
#define HWIO_GCC_RESET_STATUS_PROC_HALT_CTI_STATUS_BMSK                                                0x10
#define HWIO_GCC_RESET_STATUS_PROC_HALT_CTI_STATUS_SHFT                                                 0x4
#define HWIO_GCC_RESET_STATUS_SRST_RESET_STATUS_BMSK                                                    0x8
#define HWIO_GCC_RESET_STATUS_SRST_RESET_STATUS_SHFT                                                    0x3
#define HWIO_GCC_RESET_STATUS_MSM_TSENSE0_RESET_STATUS_BMSK                                             0x4
#define HWIO_GCC_RESET_STATUS_MSM_TSENSE0_RESET_STATUS_SHFT                                             0x2
#define HWIO_GCC_RESET_STATUS_PMIC_RESIN_RESET_STATUS_BMSK                                              0x2
#define HWIO_GCC_RESET_STATUS_PMIC_RESIN_RESET_STATUS_SHFT                                              0x1
#define HWIO_GCC_RESET_STATUS_SECURE_WDOG_EXPIRE_RESET_STATUS_BMSK                                      0x1
#define HWIO_GCC_RESET_STATUS_SECURE_WDOG_EXPIRE_RESET_STATUS_SHFT                                      0x0


#endif /* __GCC_RESET_HWIO_H__ */
