#ifndef __APCS_GIC_HWIO_H__
#define __APCS_GIC_HWIO_H__
/*
===========================================================================
*/
/**
  @file apcs_gic_hwio.h
  @brief Auto-generated HWIO interface include file.

  Reference chip release:
    SDM660 (Starlord) [starlord_v1.0.2_p3q3r107_MTO]
 
  This file contains HWIO register definitions for the following modules:
    APCS_GIC500_GICD

  'Include' filters applied: APCS_GICD_CTLR[APCS_GIC500_GICD] 
  'Exclude' filters applied: 
*/
/*
  ===========================================================================

  Copyright (c) 2017 Qualcomm Technologies Incorporated.
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

  $Header: //components/rel/rpm.bf/1.8/core/power/sleep/src/660/apcs_gic_hwio.h#1 $
  $DateTime: 2017/02/22 05:07:30 $
  $Author: pwbldsvc $

  ===========================================================================
*/

#define A53SS_BASE 0x77800000

/*----------------------------------------------------------------------------
 * MODULE: APCS_GIC500_GICD
 *--------------------------------------------------------------------------*/

#define APCS_GIC500_GICD_REG_BASE                            (A53SS_BASE      + 0x00200000)

#define HWIO_APCS_GICD_CTLR_ADDR                             (APCS_GIC500_GICD_REG_BASE      + 0x00000000)
#define HWIO_APCS_GICD_CTLR_RMSK                             0x800000f7
#define HWIO_APCS_GICD_CTLR_IN          \
        in_dword_masked(HWIO_APCS_GICD_CTLR_ADDR, HWIO_APCS_GICD_CTLR_RMSK)
#define HWIO_APCS_GICD_CTLR_INM(m)      \
        in_dword_masked(HWIO_APCS_GICD_CTLR_ADDR, m)
#define HWIO_APCS_GICD_CTLR_OUT(v)      \
        out_dword(HWIO_APCS_GICD_CTLR_ADDR,v)
#define HWIO_APCS_GICD_CTLR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_GICD_CTLR_ADDR,m,v,HWIO_APCS_GICD_CTLR_IN)
#define HWIO_APCS_GICD_CTLR_RWP_BMSK                         0x80000000
#define HWIO_APCS_GICD_CTLR_RWP_SHFT                               0x1f
#define HWIO_APCS_GICD_CTLR_E1NWF_BMSK                             0x80
#define HWIO_APCS_GICD_CTLR_E1NWF_SHFT                              0x7
#define HWIO_APCS_GICD_CTLR_DS_BMSK                                0x40
#define HWIO_APCS_GICD_CTLR_DS_SHFT                                 0x6
#define HWIO_APCS_GICD_CTLR_ARE_NS_BMSK                            0x20
#define HWIO_APCS_GICD_CTLR_ARE_NS_SHFT                             0x5
#define HWIO_APCS_GICD_CTLR_ARE_S_BMSK                             0x10
#define HWIO_APCS_GICD_CTLR_ARE_S_SHFT                              0x4
#define HWIO_APCS_GICD_CTLR_ENABLE_GRP1_SEC_BMSK                    0x4
#define HWIO_APCS_GICD_CTLR_ENABLE_GRP1_SEC_SHFT                    0x2
#define HWIO_APCS_GICD_CTLR_ENABLE_GRP1_BMSK                        0x2
#define HWIO_APCS_GICD_CTLR_ENABLE_GRP1_SHFT                        0x1
#define HWIO_APCS_GICD_CTLR_ENABLE_GRP0_BMSK                        0x1
#define HWIO_APCS_GICD_CTLR_ENABLE_GRP0_SHFT                        0x0


#endif /* __APCS_GIC_HWIO_H__ */
