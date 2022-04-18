#ifndef __HWIO_H__
#define __HWIO_H__
/*
===========================================================================
*/
/**
  @file hwio.h
  @brief Auto-generated HWIO interface include file.

  Reference chip release:
    SDM660 (Starlord) [starlord_v1.0_p3q2r76]
 
  This file contains HWIO register definitions for the following modules:
    LPASS_CSR
    LPASS_CC

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

  ===========================================================================

  $Header: //components/rel/core.qdsp6/1.0.c2/power/qdsp_pm/config/660/adsp_slpi/qdsp_pm_clocks_hwio_660_adsp_slpi.h#1 $
  $DateTime: 2020/02/10 01:57:30 $
  $Author: pwbldsvc $

  ===========================================================================
*/

/*----------------------------------------------------------------------------
 * MODULE: LPASS_CSR
 *--------------------------------------------------------------------------*/

#define LPASS_CSR_REG_BASE                                                                              (LPASS_BASE      + 0x000c0000)
#define LPASS_CSR_REG_BASE_OFFS                                                                         0x000c0000

#define HWIO_LPASS_CSR_GP_CTL_ADDR                                                                      (LPASS_CSR_REG_BASE      + 0x00000000)
#define HWIO_LPASS_CSR_GP_CTL_OFFS                                                                      (LPASS_CSR_REG_BASE_OFFS + 0x00000000)
#define HWIO_LPASS_CSR_GP_CTL_RMSK                                                                      0xffffc01f
#define HWIO_LPASS_CSR_GP_CTL_IN          \
        in_dword_masked(HWIO_LPASS_CSR_GP_CTL_ADDR, HWIO_LPASS_CSR_GP_CTL_RMSK)
#define HWIO_LPASS_CSR_GP_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_CSR_GP_CTL_ADDR, m)
#define HWIO_LPASS_CSR_GP_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_CSR_GP_CTL_ADDR,v)
#define HWIO_LPASS_CSR_GP_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_CSR_GP_CTL_ADDR,m,v,HWIO_LPASS_CSR_GP_CTL_IN)
#define HWIO_LPASS_CSR_GP_CTL_SPARE_LPASS_BMSK                                                          0xfffe0000
#define HWIO_LPASS_CSR_GP_CTL_SPARE_LPASS_SHFT                                                                0x11
#define HWIO_LPASS_CSR_GP_CTL_DRESET_EN_BMSK                                                               0x10000
#define HWIO_LPASS_CSR_GP_CTL_DRESET_EN_SHFT                                                                  0x10
#define HWIO_LPASS_CSR_GP_CTL_DISABLE_AHBI_ABORT_REQ_BMSK                                                   0x8000
#define HWIO_LPASS_CSR_GP_CTL_DISABLE_AHBI_ABORT_REQ_SHFT                                                      0xf
#define HWIO_LPASS_CSR_GP_CTL_DISABLE_AHBL_ABORT_REQ_BMSK                                                   0x4000
#define HWIO_LPASS_CSR_GP_CTL_DISABLE_AHBL_ABORT_REQ_SHFT                                                      0xe
#define HWIO_LPASS_CSR_GP_CTL_AHB2AHB_HMEM_FIX_DISABLE_BMSK                                                   0x10
#define HWIO_LPASS_CSR_GP_CTL_AHB2AHB_HMEM_FIX_DISABLE_SHFT                                                    0x4
#define HWIO_LPASS_CSR_GP_CTL_TLB_PL_HPROT_NB_EN_BMSK                                                          0x8
#define HWIO_LPASS_CSR_GP_CTL_TLB_PL_HPROT_NB_EN_SHFT                                                          0x3
#define HWIO_LPASS_CSR_GP_CTL_SPDIFTX_HPROT_NB_EN_BMSK                                                         0x4
#define HWIO_LPASS_CSR_GP_CTL_SPDIFTX_HPROT_NB_EN_SHFT                                                         0x2
#define HWIO_LPASS_CSR_GP_CTL_DML_HPROT_NB_EN_BMSK                                                             0x2
#define HWIO_LPASS_CSR_GP_CTL_DML_HPROT_NB_EN_SHFT                                                             0x1
#define HWIO_LPASS_CSR_GP_CTL_RESMP_HPROT_NB_EN_BMSK                                                           0x1
#define HWIO_LPASS_CSR_GP_CTL_RESMP_HPROT_NB_EN_SHFT                                                           0x0

#define HWIO_LPASS_CSR_MEMTYPE_CTL_ADDR                                                                 (LPASS_CSR_REG_BASE      + 0x00000004)
#define HWIO_LPASS_CSR_MEMTYPE_CTL_OFFS                                                                 (LPASS_CSR_REG_BASE_OFFS + 0x00000004)
#define HWIO_LPASS_CSR_MEMTYPE_CTL_RMSK                                                                 0xf0ffffff
#define HWIO_LPASS_CSR_MEMTYPE_CTL_IN          \
        in_dword_masked(HWIO_LPASS_CSR_MEMTYPE_CTL_ADDR, HWIO_LPASS_CSR_MEMTYPE_CTL_RMSK)
#define HWIO_LPASS_CSR_MEMTYPE_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_CSR_MEMTYPE_CTL_ADDR, m)
#define HWIO_LPASS_CSR_MEMTYPE_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_CSR_MEMTYPE_CTL_ADDR,v)
#define HWIO_LPASS_CSR_MEMTYPE_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_CSR_MEMTYPE_CTL_ADDR,m,v,HWIO_LPASS_CSR_MEMTYPE_CTL_IN)
#define HWIO_LPASS_CSR_MEMTYPE_CTL_CORE_MEMTYPE_BMSK                                                    0xe0000000
#define HWIO_LPASS_CSR_MEMTYPE_CTL_CORE_MEMTYPE_SHFT                                                          0x1d
#define HWIO_LPASS_CSR_MEMTYPE_CTL_CORE_MEMTYPE_EN_BMSK                                                 0x10000000
#define HWIO_LPASS_CSR_MEMTYPE_CTL_CORE_MEMTYPE_EN_SHFT                                                       0x1c
#define HWIO_LPASS_CSR_MEMTYPE_CTL_TLB_PL_MEMTYPE_BMSK                                                    0xe00000
#define HWIO_LPASS_CSR_MEMTYPE_CTL_TLB_PL_MEMTYPE_SHFT                                                        0x15
#define HWIO_LPASS_CSR_MEMTYPE_CTL_TLB_PL_MEMTYPE_EN_BMSK                                                 0x100000
#define HWIO_LPASS_CSR_MEMTYPE_CTL_TLB_PL_MEMTYPE_EN_SHFT                                                     0x14
#define HWIO_LPASS_CSR_MEMTYPE_CTL_SPDIFTX_MEMTYPE_BMSK                                                    0xe0000
#define HWIO_LPASS_CSR_MEMTYPE_CTL_SPDIFTX_MEMTYPE_SHFT                                                       0x11
#define HWIO_LPASS_CSR_MEMTYPE_CTL_SPDIFTX_MEMTYPE_EN_BMSK                                                 0x10000
#define HWIO_LPASS_CSR_MEMTYPE_CTL_SPDIFTX_MEMTYPE_EN_SHFT                                                    0x10
#define HWIO_LPASS_CSR_MEMTYPE_CTL_HDMIRX_MEMTYPE_BMSK                                                      0xe000
#define HWIO_LPASS_CSR_MEMTYPE_CTL_HDMIRX_MEMTYPE_SHFT                                                         0xd
#define HWIO_LPASS_CSR_MEMTYPE_CTL_HDMIRX_MEMTYPE_EN_BMSK                                                   0x1000
#define HWIO_LPASS_CSR_MEMTYPE_CTL_HDMIRX_MEMTYPE_EN_SHFT                                                      0xc
#define HWIO_LPASS_CSR_MEMTYPE_CTL_RESMP_MEMTYPE_BMSK                                                        0xe00
#define HWIO_LPASS_CSR_MEMTYPE_CTL_RESMP_MEMTYPE_SHFT                                                          0x9
#define HWIO_LPASS_CSR_MEMTYPE_CTL_RESMP_MEMTYPE_EN_BMSK                                                     0x100
#define HWIO_LPASS_CSR_MEMTYPE_CTL_RESMP_MEMTYPE_EN_SHFT                                                       0x8
#define HWIO_LPASS_CSR_MEMTYPE_CTL_LPAIF_MEMTYPE_BMSK                                                         0xe0
#define HWIO_LPASS_CSR_MEMTYPE_CTL_LPAIF_MEMTYPE_SHFT                                                          0x5
#define HWIO_LPASS_CSR_MEMTYPE_CTL_LPAIF_MEMTYPE_EN_BMSK                                                      0x10
#define HWIO_LPASS_CSR_MEMTYPE_CTL_LPAIF_MEMTYPE_EN_SHFT                                                       0x4
#define HWIO_LPASS_CSR_MEMTYPE_CTL_DML_MEMTYPE_BMSK                                                            0xe
#define HWIO_LPASS_CSR_MEMTYPE_CTL_DML_MEMTYPE_SHFT                                                            0x1
#define HWIO_LPASS_CSR_MEMTYPE_CTL_DML_MEMTYPE_EN_BMSK                                                         0x1
#define HWIO_LPASS_CSR_MEMTYPE_CTL_DML_MEMTYPE_EN_SHFT                                                         0x0

#define HWIO_LPASS_CSR_DEBUG_CTL_ADDR                                                                   (LPASS_CSR_REG_BASE      + 0x00000010)
#define HWIO_LPASS_CSR_DEBUG_CTL_OFFS                                                                   (LPASS_CSR_REG_BASE_OFFS + 0x00000010)
#define HWIO_LPASS_CSR_DEBUG_CTL_RMSK                                                                      0x1ff1f
#define HWIO_LPASS_CSR_DEBUG_CTL_IN          \
        in_dword_masked(HWIO_LPASS_CSR_DEBUG_CTL_ADDR, HWIO_LPASS_CSR_DEBUG_CTL_RMSK)
#define HWIO_LPASS_CSR_DEBUG_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_CSR_DEBUG_CTL_ADDR, m)
#define HWIO_LPASS_CSR_DEBUG_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_CSR_DEBUG_CTL_ADDR,v)
#define HWIO_LPASS_CSR_DEBUG_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_CSR_DEBUG_CTL_ADDR,m,v,HWIO_LPASS_CSR_DEBUG_CTL_IN)
#define HWIO_LPASS_CSR_DEBUG_CTL_LPASS_DEBUG_EN_BMSK                                                       0x10000
#define HWIO_LPASS_CSR_DEBUG_CTL_LPASS_DEBUG_EN_SHFT                                                          0x10
#define HWIO_LPASS_CSR_DEBUG_CTL_SEL_ADDR_BMSK                                                              0xff00
#define HWIO_LPASS_CSR_DEBUG_CTL_SEL_ADDR_SHFT                                                                 0x8
#define HWIO_LPASS_CSR_DEBUG_CTL_SEL_BMSK                                                                     0x1f
#define HWIO_LPASS_CSR_DEBUG_CTL_SEL_SHFT                                                                      0x0

#define HWIO_LPASS_CSR_DEBUG_BUS_ADDR                                                                   (LPASS_CSR_REG_BASE      + 0x00000014)
#define HWIO_LPASS_CSR_DEBUG_BUS_OFFS                                                                   (LPASS_CSR_REG_BASE_OFFS + 0x00000014)
#define HWIO_LPASS_CSR_DEBUG_BUS_RMSK                                                                   0xffffffff
#define HWIO_LPASS_CSR_DEBUG_BUS_IN          \
        in_dword_masked(HWIO_LPASS_CSR_DEBUG_BUS_ADDR, HWIO_LPASS_CSR_DEBUG_BUS_RMSK)
#define HWIO_LPASS_CSR_DEBUG_BUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_CSR_DEBUG_BUS_ADDR, m)
#define HWIO_LPASS_CSR_DEBUG_BUS_READ_BMSK                                                              0xffffffff
#define HWIO_LPASS_CSR_DEBUG_BUS_READ_SHFT                                                                     0x0

#define HWIO_LPASS_AHBI_CFG_ADDR                                                                        (LPASS_CSR_REG_BASE      + 0x00001004)
#define HWIO_LPASS_AHBI_CFG_OFFS                                                                        (LPASS_CSR_REG_BASE_OFFS + 0x00001004)
#define HWIO_LPASS_AHBI_CFG_RMSK                                                                             0xff1
#define HWIO_LPASS_AHBI_CFG_IN          \
        in_dword_masked(HWIO_LPASS_AHBI_CFG_ADDR, HWIO_LPASS_AHBI_CFG_RMSK)
#define HWIO_LPASS_AHBI_CFG_INM(m)      \
        in_dword_masked(HWIO_LPASS_AHBI_CFG_ADDR, m)
#define HWIO_LPASS_AHBI_CFG_OUT(v)      \
        out_dword(HWIO_LPASS_AHBI_CFG_ADDR,v)
#define HWIO_LPASS_AHBI_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AHBI_CFG_ADDR,m,v,HWIO_LPASS_AHBI_CFG_IN)
#define HWIO_LPASS_AHBI_CFG_Q6SS_PRIORITY_BMSK                                                               0xf00
#define HWIO_LPASS_AHBI_CFG_Q6SS_PRIORITY_SHFT                                                                 0x8
#define HWIO_LPASS_AHBI_CFG_FABRIC_PRIORITY_BMSK                                                              0xf0
#define HWIO_LPASS_AHBI_CFG_FABRIC_PRIORITY_SHFT                                                               0x4
#define HWIO_LPASS_AHBI_CFG_ROUND_ROBIN_EN_BMSK                                                                0x1
#define HWIO_LPASS_AHBI_CFG_ROUND_ROBIN_EN_SHFT                                                                0x0

#define HWIO_LPASS_AHBI_LOCK_CTL_ADDR                                                                   (LPASS_CSR_REG_BASE      + 0x00001008)
#define HWIO_LPASS_AHBI_LOCK_CTL_OFFS                                                                   (LPASS_CSR_REG_BASE_OFFS + 0x00001008)
#define HWIO_LPASS_AHBI_LOCK_CTL_RMSK                                                                          0x3
#define HWIO_LPASS_AHBI_LOCK_CTL_IN          \
        in_dword_masked(HWIO_LPASS_AHBI_LOCK_CTL_ADDR, HWIO_LPASS_AHBI_LOCK_CTL_RMSK)
#define HWIO_LPASS_AHBI_LOCK_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_AHBI_LOCK_CTL_ADDR, m)
#define HWIO_LPASS_AHBI_LOCK_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_AHBI_LOCK_CTL_ADDR,v)
#define HWIO_LPASS_AHBI_LOCK_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AHBI_LOCK_CTL_ADDR,m,v,HWIO_LPASS_AHBI_LOCK_CTL_IN)
#define HWIO_LPASS_AHBI_LOCK_CTL_Q6SS_LOCK_EN_BMSK                                                             0x2
#define HWIO_LPASS_AHBI_LOCK_CTL_Q6SS_LOCK_EN_SHFT                                                             0x1
#define HWIO_LPASS_AHBI_LOCK_CTL_FABRIC_LOCK_EN_BMSK                                                           0x1
#define HWIO_LPASS_AHBI_LOCK_CTL_FABRIC_LOCK_EN_SHFT                                                           0x0

#define HWIO_LPASS_AHBX_CFG_ADDR                                                                        (LPASS_CSR_REG_BASE      + 0x00001020)
#define HWIO_LPASS_AHBX_CFG_OFFS                                                                        (LPASS_CSR_REG_BASE_OFFS + 0x00001020)
#define HWIO_LPASS_AHBX_CFG_RMSK                                                                        0x7703f77f
#define HWIO_LPASS_AHBX_CFG_IN          \
        in_dword_masked(HWIO_LPASS_AHBX_CFG_ADDR, HWIO_LPASS_AHBX_CFG_RMSK)
#define HWIO_LPASS_AHBX_CFG_INM(m)      \
        in_dword_masked(HWIO_LPASS_AHBX_CFG_ADDR, m)
#define HWIO_LPASS_AHBX_CFG_OUT(v)      \
        out_dword(HWIO_LPASS_AHBX_CFG_ADDR,v)
#define HWIO_LPASS_AHBX_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AHBX_CFG_ADDR,m,v,HWIO_LPASS_AHBX_CFG_IN)
#define HWIO_LPASS_AHBX_CFG_RESAMPLER_PRIORITY_BMSK                                                     0x70000000
#define HWIO_LPASS_AHBX_CFG_RESAMPLER_PRIORITY_SHFT                                                           0x1c
#define HWIO_LPASS_AHBX_CFG_SLIMBUS_PRIORITY_BMSK                                                        0x7000000
#define HWIO_LPASS_AHBX_CFG_SLIMBUS_PRIORITY_SHFT                                                             0x18
#define HWIO_LPASS_AHBX_CFG_SLIMBUS1_PRIORITY_BMSK                                                         0x38000
#define HWIO_LPASS_AHBX_CFG_SLIMBUS1_PRIORITY_SHFT                                                             0xf
#define HWIO_LPASS_AHBX_CFG_DM_PRIORITY_BMSK                                                                0x7000
#define HWIO_LPASS_AHBX_CFG_DM_PRIORITY_SHFT                                                                   0xc
#define HWIO_LPASS_AHBX_CFG_HDMI_PRIORITY_BMSK                                                               0x700
#define HWIO_LPASS_AHBX_CFG_HDMI_PRIORITY_SHFT                                                                 0x8
#define HWIO_LPASS_AHBX_CFG_AUDIO_IF_PRIORITY_BMSK                                                            0x70
#define HWIO_LPASS_AHBX_CFG_AUDIO_IF_PRIORITY_SHFT                                                             0x4
#define HWIO_LPASS_AHBX_CFG_SPDIFTX_PRIORITY_BMSK                                                              0xe
#define HWIO_LPASS_AHBX_CFG_SPDIFTX_PRIORITY_SHFT                                                              0x1
#define HWIO_LPASS_AHBX_CFG_ROUND_ROBIN_EN_BMSK                                                                0x1
#define HWIO_LPASS_AHBX_CFG_ROUND_ROBIN_EN_SHFT                                                                0x0

#define HWIO_LPASS_AHBX_LOCK_CTL_ADDR                                                                   (LPASS_CSR_REG_BASE      + 0x00001024)
#define HWIO_LPASS_AHBX_LOCK_CTL_OFFS                                                                   (LPASS_CSR_REG_BASE_OFFS + 0x00001024)
#define HWIO_LPASS_AHBX_LOCK_CTL_RMSK                                                                        0x7e5
#define HWIO_LPASS_AHBX_LOCK_CTL_IN          \
        in_dword_masked(HWIO_LPASS_AHBX_LOCK_CTL_ADDR, HWIO_LPASS_AHBX_LOCK_CTL_RMSK)
#define HWIO_LPASS_AHBX_LOCK_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_AHBX_LOCK_CTL_ADDR, m)
#define HWIO_LPASS_AHBX_LOCK_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_AHBX_LOCK_CTL_ADDR,v)
#define HWIO_LPASS_AHBX_LOCK_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AHBX_LOCK_CTL_ADDR,m,v,HWIO_LPASS_AHBX_LOCK_CTL_IN)
#define HWIO_LPASS_AHBX_LOCK_CTL_TLB_PL_LOCK_EN_BMSK                                                         0x400
#define HWIO_LPASS_AHBX_LOCK_CTL_TLB_PL_LOCK_EN_SHFT                                                           0xa
#define HWIO_LPASS_AHBX_LOCK_CTL_SLIMBUS1_LOCK_EN_BMSK                                                       0x200
#define HWIO_LPASS_AHBX_LOCK_CTL_SLIMBUS1_LOCK_EN_SHFT                                                         0x9
#define HWIO_LPASS_AHBX_LOCK_CTL_HDMI_LOCK_EN_BMSK                                                           0x100
#define HWIO_LPASS_AHBX_LOCK_CTL_HDMI_LOCK_EN_SHFT                                                             0x8
#define HWIO_LPASS_AHBX_LOCK_CTL_SPDIFTX_LOCK_EN_BMSK                                                         0x80
#define HWIO_LPASS_AHBX_LOCK_CTL_SPDIFTX_LOCK_EN_SHFT                                                          0x7
#define HWIO_LPASS_AHBX_LOCK_CTL_RESAMPLER_LOCK_EN_BMSK                                                       0x40
#define HWIO_LPASS_AHBX_LOCK_CTL_RESAMPLER_LOCK_EN_SHFT                                                        0x6
#define HWIO_LPASS_AHBX_LOCK_CTL_SLIMBUS_LOCK_EN_BMSK                                                         0x20
#define HWIO_LPASS_AHBX_LOCK_CTL_SLIMBUS_LOCK_EN_SHFT                                                          0x5
#define HWIO_LPASS_AHBX_LOCK_CTL_DM_LOCK_EN_BMSK                                                               0x4
#define HWIO_LPASS_AHBX_LOCK_CTL_DM_LOCK_EN_SHFT                                                               0x2
#define HWIO_LPASS_AHBX_LOCK_CTL_AUDIO_IF_LOCK_EN_BMSK                                                         0x1
#define HWIO_LPASS_AHBX_LOCK_CTL_AUDIO_IF_LOCK_EN_SHFT                                                         0x0

#define HWIO_LPASS_AHBX_CFG_EXT_ADDR                                                                    (LPASS_CSR_REG_BASE      + 0x00001028)
#define HWIO_LPASS_AHBX_CFG_EXT_OFFS                                                                    (LPASS_CSR_REG_BASE_OFFS + 0x00001028)
#define HWIO_LPASS_AHBX_CFG_EXT_RMSK                                                                           0x7
#define HWIO_LPASS_AHBX_CFG_EXT_IN          \
        in_dword_masked(HWIO_LPASS_AHBX_CFG_EXT_ADDR, HWIO_LPASS_AHBX_CFG_EXT_RMSK)
#define HWIO_LPASS_AHBX_CFG_EXT_INM(m)      \
        in_dword_masked(HWIO_LPASS_AHBX_CFG_EXT_ADDR, m)
#define HWIO_LPASS_AHBX_CFG_EXT_OUT(v)      \
        out_dword(HWIO_LPASS_AHBX_CFG_EXT_ADDR,v)
#define HWIO_LPASS_AHBX_CFG_EXT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AHBX_CFG_EXT_ADDR,m,v,HWIO_LPASS_AHBX_CFG_EXT_IN)
#define HWIO_LPASS_AHBX_CFG_EXT_TLB_PL_PRIORITY_BMSK                                                           0x7
#define HWIO_LPASS_AHBX_CFG_EXT_TLB_PL_PRIORITY_SHFT                                                           0x0

#define HWIO_LPASS_AHBIX_STATUS_ADDR                                                                    (LPASS_CSR_REG_BASE      + 0x00001030)
#define HWIO_LPASS_AHBIX_STATUS_OFFS                                                                    (LPASS_CSR_REG_BASE_OFFS + 0x00001030)
#define HWIO_LPASS_AHBIX_STATUS_RMSK                                                                         0x1ff
#define HWIO_LPASS_AHBIX_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_AHBIX_STATUS_ADDR, HWIO_LPASS_AHBIX_STATUS_RMSK)
#define HWIO_LPASS_AHBIX_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_AHBIX_STATUS_ADDR, m)
#define HWIO_LPASS_AHBIX_STATUS_AHBL_DECODE_BOUNDARY_ERROR_BMSK                                              0x100
#define HWIO_LPASS_AHBIX_STATUS_AHBL_DECODE_BOUNDARY_ERROR_SHFT                                                0x8
#define HWIO_LPASS_AHBIX_STATUS_AHBL_DECODE_ERROR_BMSK                                                        0x80
#define HWIO_LPASS_AHBIX_STATUS_AHBL_DECODE_ERROR_SHFT                                                         0x7
#define HWIO_LPASS_AHBIX_STATUS_AHBL_MISALIGNED_BMSK                                                          0x40
#define HWIO_LPASS_AHBIX_STATUS_AHBL_MISALIGNED_SHFT                                                           0x6
#define HWIO_LPASS_AHBIX_STATUS_AHBX_DECODE_BOUNDARY_ERROR_BMSK                                               0x20
#define HWIO_LPASS_AHBIX_STATUS_AHBX_DECODE_BOUNDARY_ERROR_SHFT                                                0x5
#define HWIO_LPASS_AHBIX_STATUS_AHBX_DECODE_ERROR_BMSK                                                        0x10
#define HWIO_LPASS_AHBIX_STATUS_AHBX_DECODE_ERROR_SHFT                                                         0x4
#define HWIO_LPASS_AHBIX_STATUS_AHBX_MISALIGNED_BMSK                                                           0x8
#define HWIO_LPASS_AHBIX_STATUS_AHBX_MISALIGNED_SHFT                                                           0x3
#define HWIO_LPASS_AHBIX_STATUS_AHBI_DECODE_BOUNDARY_ERROR_BMSK                                                0x4
#define HWIO_LPASS_AHBIX_STATUS_AHBI_DECODE_BOUNDARY_ERROR_SHFT                                                0x2
#define HWIO_LPASS_AHBIX_STATUS_AHBI_DECODE_ERROR_BMSK                                                         0x2
#define HWIO_LPASS_AHBIX_STATUS_AHBI_DECODE_ERROR_SHFT                                                         0x1
#define HWIO_LPASS_AHBIX_STATUS_AHBI_MISALIGNED_BMSK                                                           0x1
#define HWIO_LPASS_AHBIX_STATUS_AHBI_MISALIGNED_SHFT                                                           0x0

#define HWIO_LPASS_AHBIX_ACK_ADDR                                                                       (LPASS_CSR_REG_BASE      + 0x00001034)
#define HWIO_LPASS_AHBIX_ACK_OFFS                                                                       (LPASS_CSR_REG_BASE_OFFS + 0x00001034)
#define HWIO_LPASS_AHBIX_ACK_RMSK                                                                            0x1ff
#define HWIO_LPASS_AHBIX_ACK_OUT(v)      \
        out_dword(HWIO_LPASS_AHBIX_ACK_ADDR,v)
#define HWIO_LPASS_AHBIX_ACK_AHBL_DECODE_BOUNDARY_ERROR_BMSK                                                 0x100
#define HWIO_LPASS_AHBIX_ACK_AHBL_DECODE_BOUNDARY_ERROR_SHFT                                                   0x8
#define HWIO_LPASS_AHBIX_ACK_AHBL_DECODE_ERROR_BMSK                                                           0x80
#define HWIO_LPASS_AHBIX_ACK_AHBL_DECODE_ERROR_SHFT                                                            0x7
#define HWIO_LPASS_AHBIX_ACK_AHBL_MISALIGNED_BMSK                                                             0x40
#define HWIO_LPASS_AHBIX_ACK_AHBL_MISALIGNED_SHFT                                                              0x6
#define HWIO_LPASS_AHBIX_ACK_AHBX_DECODE_BOUNDARY_ERROR_BMSK                                                  0x20
#define HWIO_LPASS_AHBIX_ACK_AHBX_DECODE_BOUNDARY_ERROR_SHFT                                                   0x5
#define HWIO_LPASS_AHBIX_ACK_AHBX_DECODE_ERROR_BMSK                                                           0x10
#define HWIO_LPASS_AHBIX_ACK_AHBX_DECODE_ERROR_SHFT                                                            0x4
#define HWIO_LPASS_AHBIX_ACK_AHBX_MISALIGNED_BMSK                                                              0x8
#define HWIO_LPASS_AHBIX_ACK_AHBX_MISALIGNED_SHFT                                                              0x3
#define HWIO_LPASS_AHBIX_ACK_AHBI_DECODE_BOUNDARY_ERROR_BMSK                                                   0x4
#define HWIO_LPASS_AHBIX_ACK_AHBI_DECODE_BOUNDARY_ERROR_SHFT                                                   0x2
#define HWIO_LPASS_AHBIX_ACK_AHBI_DECODE_ERROR_BMSK                                                            0x2
#define HWIO_LPASS_AHBIX_ACK_AHBI_DECODE_ERROR_SHFT                                                            0x1
#define HWIO_LPASS_AHBIX_ACK_AHBI_MISALIGNED_BMSK                                                              0x1
#define HWIO_LPASS_AHBIX_ACK_AHBI_MISALIGNED_SHFT                                                              0x0

#define HWIO_LPASS_AHBIX_EN_ADDR                                                                        (LPASS_CSR_REG_BASE      + 0x00001038)
#define HWIO_LPASS_AHBIX_EN_OFFS                                                                        (LPASS_CSR_REG_BASE_OFFS + 0x00001038)
#define HWIO_LPASS_AHBIX_EN_RMSK                                                                             0x1ff
#define HWIO_LPASS_AHBIX_EN_IN          \
        in_dword_masked(HWIO_LPASS_AHBIX_EN_ADDR, HWIO_LPASS_AHBIX_EN_RMSK)
#define HWIO_LPASS_AHBIX_EN_INM(m)      \
        in_dword_masked(HWIO_LPASS_AHBIX_EN_ADDR, m)
#define HWIO_LPASS_AHBIX_EN_OUT(v)      \
        out_dword(HWIO_LPASS_AHBIX_EN_ADDR,v)
#define HWIO_LPASS_AHBIX_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AHBIX_EN_ADDR,m,v,HWIO_LPASS_AHBIX_EN_IN)
#define HWIO_LPASS_AHBIX_EN_AHBL_DECODE_BOUNDARY_ERROR_BMSK                                                  0x100
#define HWIO_LPASS_AHBIX_EN_AHBL_DECODE_BOUNDARY_ERROR_SHFT                                                    0x8
#define HWIO_LPASS_AHBIX_EN_AHBL_DECODE_ERROR_BMSK                                                            0x80
#define HWIO_LPASS_AHBIX_EN_AHBL_DECODE_ERROR_SHFT                                                             0x7
#define HWIO_LPASS_AHBIX_EN_AHBL_MISALIGNED_BMSK                                                              0x40
#define HWIO_LPASS_AHBIX_EN_AHBL_MISALIGNED_SHFT                                                               0x6
#define HWIO_LPASS_AHBIX_EN_AHBX_DECODE_BOUNDARY_ERROR_BMSK                                                   0x20
#define HWIO_LPASS_AHBIX_EN_AHBX_DECODE_BOUNDARY_ERROR_SHFT                                                    0x5
#define HWIO_LPASS_AHBIX_EN_AHBX_DECODE_ERROR_BMSK                                                            0x10
#define HWIO_LPASS_AHBIX_EN_AHBX_DECODE_ERROR_SHFT                                                             0x4
#define HWIO_LPASS_AHBIX_EN_AHBX_MISALIGNED_BMSK                                                               0x8
#define HWIO_LPASS_AHBIX_EN_AHBX_MISALIGNED_SHFT                                                               0x3
#define HWIO_LPASS_AHBIX_EN_AHBI_DECODE_BOUNDARY_ERROR_BMSK                                                    0x4
#define HWIO_LPASS_AHBIX_EN_AHBI_DECODE_BOUNDARY_ERROR_SHFT                                                    0x2
#define HWIO_LPASS_AHBIX_EN_AHBI_DECODE_ERROR_BMSK                                                             0x2
#define HWIO_LPASS_AHBIX_EN_AHBI_DECODE_ERROR_SHFT                                                             0x1
#define HWIO_LPASS_AHBIX_EN_AHBI_MISALIGNED_BMSK                                                               0x1
#define HWIO_LPASS_AHBIX_EN_AHBI_MISALIGNED_SHFT                                                               0x0

#define HWIO_LPASS_AHBIX_EXT_MASTER_CTL_ADDR                                                            (LPASS_CSR_REG_BASE      + 0x0000103c)
#define HWIO_LPASS_AHBIX_EXT_MASTER_CTL_OFFS                                                            (LPASS_CSR_REG_BASE_OFFS + 0x0000103c)
#define HWIO_LPASS_AHBIX_EXT_MASTER_CTL_RMSK                                                                   0x1
#define HWIO_LPASS_AHBIX_EXT_MASTER_CTL_IN          \
        in_dword_masked(HWIO_LPASS_AHBIX_EXT_MASTER_CTL_ADDR, HWIO_LPASS_AHBIX_EXT_MASTER_CTL_RMSK)
#define HWIO_LPASS_AHBIX_EXT_MASTER_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_AHBIX_EXT_MASTER_CTL_ADDR, m)
#define HWIO_LPASS_AHBIX_EXT_MASTER_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_AHBIX_EXT_MASTER_CTL_ADDR,v)
#define HWIO_LPASS_AHBIX_EXT_MASTER_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AHBIX_EXT_MASTER_CTL_ADDR,m,v,HWIO_LPASS_AHBIX_EXT_MASTER_CTL_IN)
#define HWIO_LPASS_AHBIX_EXT_MASTER_CTL_USE_INTERNAL_PATH_FOR_EXT_MASTER_BMSK                                  0x1
#define HWIO_LPASS_AHBIX_EXT_MASTER_CTL_USE_INTERNAL_PATH_FOR_EXT_MASTER_SHFT                                  0x0

#define HWIO_LPASS_AHBL_CFG_ADDR                                                                        (LPASS_CSR_REG_BASE      + 0x00001040)
#define HWIO_LPASS_AHBL_CFG_OFFS                                                                        (LPASS_CSR_REG_BASE_OFFS + 0x00001040)
#define HWIO_LPASS_AHBL_CFG_RMSK                                                                         0xffffff1
#define HWIO_LPASS_AHBL_CFG_IN          \
        in_dword_masked(HWIO_LPASS_AHBL_CFG_ADDR, HWIO_LPASS_AHBL_CFG_RMSK)
#define HWIO_LPASS_AHBL_CFG_INM(m)      \
        in_dword_masked(HWIO_LPASS_AHBL_CFG_ADDR, m)
#define HWIO_LPASS_AHBL_CFG_OUT(v)      \
        out_dword(HWIO_LPASS_AHBL_CFG_ADDR,v)
#define HWIO_LPASS_AHBL_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AHBL_CFG_ADDR,m,v,HWIO_LPASS_AHBL_CFG_IN)
#define HWIO_LPASS_AHBL_CFG_RESAMPLER_PRIORITY_BMSK                                                      0xf000000
#define HWIO_LPASS_AHBL_CFG_RESAMPLER_PRIORITY_SHFT                                                           0x18
#define HWIO_LPASS_AHBL_CFG_SLIMBUS_PRIORITY_BMSK                                                         0xf00000
#define HWIO_LPASS_AHBL_CFG_SLIMBUS_PRIORITY_SHFT                                                             0x14
#define HWIO_LPASS_AHBL_CFG_FABRIC_PRIORITY_BMSK                                                           0xf0000
#define HWIO_LPASS_AHBL_CFG_FABRIC_PRIORITY_SHFT                                                              0x10
#define HWIO_LPASS_AHBL_CFG_DM_PRIORITY_BMSK                                                                0xf000
#define HWIO_LPASS_AHBL_CFG_DM_PRIORITY_SHFT                                                                   0xc
#define HWIO_LPASS_AHBL_CFG_Q6SS_PRIORITY_BMSK                                                               0xf00
#define HWIO_LPASS_AHBL_CFG_Q6SS_PRIORITY_SHFT                                                                 0x8
#define HWIO_LPASS_AHBL_CFG_AUDIO_IF_PRIORITY_BMSK                                                            0xf0
#define HWIO_LPASS_AHBL_CFG_AUDIO_IF_PRIORITY_SHFT                                                             0x4
#define HWIO_LPASS_AHBL_CFG_ROUND_ROBIN_EN_BMSK                                                                0x1
#define HWIO_LPASS_AHBL_CFG_ROUND_ROBIN_EN_SHFT                                                                0x0

#define HWIO_LPASS_AHBL_LOCK_CTL_ADDR                                                                   (LPASS_CSR_REG_BASE      + 0x00001044)
#define HWIO_LPASS_AHBL_LOCK_CTL_OFFS                                                                   (LPASS_CSR_REG_BASE_OFFS + 0x00001044)
#define HWIO_LPASS_AHBL_LOCK_CTL_RMSK                                                                        0x1ff
#define HWIO_LPASS_AHBL_LOCK_CTL_IN          \
        in_dword_masked(HWIO_LPASS_AHBL_LOCK_CTL_ADDR, HWIO_LPASS_AHBL_LOCK_CTL_RMSK)
#define HWIO_LPASS_AHBL_LOCK_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_AHBL_LOCK_CTL_ADDR, m)
#define HWIO_LPASS_AHBL_LOCK_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_AHBL_LOCK_CTL_ADDR,v)
#define HWIO_LPASS_AHBL_LOCK_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AHBL_LOCK_CTL_ADDR,m,v,HWIO_LPASS_AHBL_LOCK_CTL_IN)
#define HWIO_LPASS_AHBL_LOCK_CTL_SLIMBUS1_LOCK_EN_BMSK                                                       0x100
#define HWIO_LPASS_AHBL_LOCK_CTL_SLIMBUS1_LOCK_EN_SHFT                                                         0x8
#define HWIO_LPASS_AHBL_LOCK_CTL_HDMI_LOCK_EN_BMSK                                                            0x80
#define HWIO_LPASS_AHBL_LOCK_CTL_HDMI_LOCK_EN_SHFT                                                             0x7
#define HWIO_LPASS_AHBL_LOCK_CTL_SPDIFTX_LOCK_EN_BMSK                                                         0x40
#define HWIO_LPASS_AHBL_LOCK_CTL_SPDIFTX_LOCK_EN_SHFT                                                          0x6
#define HWIO_LPASS_AHBL_LOCK_CTL_RESAMPLER_LOCK_EN_BMSK                                                       0x20
#define HWIO_LPASS_AHBL_LOCK_CTL_RESAMPLER_LOCK_EN_SHFT                                                        0x5
#define HWIO_LPASS_AHBL_LOCK_CTL_SLIMBUS_LOCK_EN_BMSK                                                         0x10
#define HWIO_LPASS_AHBL_LOCK_CTL_SLIMBUS_LOCK_EN_SHFT                                                          0x4
#define HWIO_LPASS_AHBL_LOCK_CTL_FABRIC_LOCK_EN_BMSK                                                           0x8
#define HWIO_LPASS_AHBL_LOCK_CTL_FABRIC_LOCK_EN_SHFT                                                           0x3
#define HWIO_LPASS_AHBL_LOCK_CTL_DM_LOCK_EN_BMSK                                                               0x4
#define HWIO_LPASS_AHBL_LOCK_CTL_DM_LOCK_EN_SHFT                                                               0x2
#define HWIO_LPASS_AHBL_LOCK_CTL_Q6SS_LOCK_EN_BMSK                                                             0x2
#define HWIO_LPASS_AHBL_LOCK_CTL_Q6SS_LOCK_EN_SHFT                                                             0x1
#define HWIO_LPASS_AHBL_LOCK_CTL_AUDIO_IF_LOCK_EN_BMSK                                                         0x1
#define HWIO_LPASS_AHBL_LOCK_CTL_AUDIO_IF_LOCK_EN_SHFT                                                         0x0

#define HWIO_LPASS_AHBL_CFG_EXT_ADDR                                                                    (LPASS_CSR_REG_BASE      + 0x00001048)
#define HWIO_LPASS_AHBL_CFG_EXT_OFFS                                                                    (LPASS_CSR_REG_BASE_OFFS + 0x00001048)
#define HWIO_LPASS_AHBL_CFG_EXT_RMSK                                                                         0xfff
#define HWIO_LPASS_AHBL_CFG_EXT_IN          \
        in_dword_masked(HWIO_LPASS_AHBL_CFG_EXT_ADDR, HWIO_LPASS_AHBL_CFG_EXT_RMSK)
#define HWIO_LPASS_AHBL_CFG_EXT_INM(m)      \
        in_dword_masked(HWIO_LPASS_AHBL_CFG_EXT_ADDR, m)
#define HWIO_LPASS_AHBL_CFG_EXT_OUT(v)      \
        out_dword(HWIO_LPASS_AHBL_CFG_EXT_ADDR,v)
#define HWIO_LPASS_AHBL_CFG_EXT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AHBL_CFG_EXT_ADDR,m,v,HWIO_LPASS_AHBL_CFG_EXT_IN)
#define HWIO_LPASS_AHBL_CFG_EXT_SLIMBUS1_PRIORITY_BMSK                                                       0xf00
#define HWIO_LPASS_AHBL_CFG_EXT_SLIMBUS1_PRIORITY_SHFT                                                         0x8
#define HWIO_LPASS_AHBL_CFG_EXT_HDMI_PRIORITY_BMSK                                                            0xf0
#define HWIO_LPASS_AHBL_CFG_EXT_HDMI_PRIORITY_SHFT                                                             0x4
#define HWIO_LPASS_AHBL_CFG_EXT_SPDIFTX_PRIORITY_BMSK                                                          0xf
#define HWIO_LPASS_AHBL_CFG_EXT_SPDIFTX_PRIORITY_SHFT                                                          0x0

#define HWIO_LPASS_DML_CTL_ADDR                                                                         (LPASS_CSR_REG_BASE      + 0x00002000)
#define HWIO_LPASS_DML_CTL_OFFS                                                                         (LPASS_CSR_REG_BASE_OFFS + 0x00002000)
#define HWIO_LPASS_DML_CTL_RMSK                                                                         0x8000001f
#define HWIO_LPASS_DML_CTL_IN          \
        in_dword_masked(HWIO_LPASS_DML_CTL_ADDR, HWIO_LPASS_DML_CTL_RMSK)
#define HWIO_LPASS_DML_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_DML_CTL_ADDR, m)
#define HWIO_LPASS_DML_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_DML_CTL_ADDR,v)
#define HWIO_LPASS_DML_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DML_CTL_ADDR,m,v,HWIO_LPASS_DML_CTL_IN)
#define HWIO_LPASS_DML_CTL_SOFT_RESET_BMSK                                                              0x80000000
#define HWIO_LPASS_DML_CTL_SOFT_RESET_SHFT                                                                    0x1f
#define HWIO_LPASS_DML_CTL_CRYPTO_EN_BMSK                                                                     0x10
#define HWIO_LPASS_DML_CTL_CRYPTO_EN_SHFT                                                                      0x4
#define HWIO_LPASS_DML_CTL_SWAP_BMSK                                                                           0xc
#define HWIO_LPASS_DML_CTL_SWAP_SHFT                                                                           0x2
#define HWIO_LPASS_DML_CTL_CMD_BMSK                                                                            0x3
#define HWIO_LPASS_DML_CTL_CMD_SHFT                                                                            0x0

#define HWIO_LPASS_DML_SRC_ADDR                                                                         (LPASS_CSR_REG_BASE      + 0x00002004)
#define HWIO_LPASS_DML_SRC_OFFS                                                                         (LPASS_CSR_REG_BASE_OFFS + 0x00002004)
#define HWIO_LPASS_DML_SRC_RMSK                                                                         0xfffffffc
#define HWIO_LPASS_DML_SRC_IN          \
        in_dword_masked(HWIO_LPASS_DML_SRC_ADDR, HWIO_LPASS_DML_SRC_RMSK)
#define HWIO_LPASS_DML_SRC_INM(m)      \
        in_dword_masked(HWIO_LPASS_DML_SRC_ADDR, m)
#define HWIO_LPASS_DML_SRC_OUT(v)      \
        out_dword(HWIO_LPASS_DML_SRC_ADDR,v)
#define HWIO_LPASS_DML_SRC_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DML_SRC_ADDR,m,v,HWIO_LPASS_DML_SRC_IN)
#define HWIO_LPASS_DML_SRC_ADDR_BMSK                                                                    0xfffffffc
#define HWIO_LPASS_DML_SRC_ADDR_SHFT                                                                           0x2

#define HWIO_LPASS_DML_DST_ADDR                                                                         (LPASS_CSR_REG_BASE      + 0x00002008)
#define HWIO_LPASS_DML_DST_OFFS                                                                         (LPASS_CSR_REG_BASE_OFFS + 0x00002008)
#define HWIO_LPASS_DML_DST_RMSK                                                                         0xfffffffc
#define HWIO_LPASS_DML_DST_IN          \
        in_dword_masked(HWIO_LPASS_DML_DST_ADDR, HWIO_LPASS_DML_DST_RMSK)
#define HWIO_LPASS_DML_DST_INM(m)      \
        in_dword_masked(HWIO_LPASS_DML_DST_ADDR, m)
#define HWIO_LPASS_DML_DST_OUT(v)      \
        out_dword(HWIO_LPASS_DML_DST_ADDR,v)
#define HWIO_LPASS_DML_DST_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DML_DST_ADDR,m,v,HWIO_LPASS_DML_DST_IN)
#define HWIO_LPASS_DML_DST_ADDR_BMSK                                                                    0xfffffffc
#define HWIO_LPASS_DML_DST_ADDR_SHFT                                                                           0x2

#define HWIO_LPASS_DML_TRAN_ADDR                                                                        (LPASS_CSR_REG_BASE      + 0x0000200c)
#define HWIO_LPASS_DML_TRAN_OFFS                                                                        (LPASS_CSR_REG_BASE_OFFS + 0x0000200c)
#define HWIO_LPASS_DML_TRAN_RMSK                                                                           0xffffc
#define HWIO_LPASS_DML_TRAN_IN          \
        in_dword_masked(HWIO_LPASS_DML_TRAN_ADDR, HWIO_LPASS_DML_TRAN_RMSK)
#define HWIO_LPASS_DML_TRAN_INM(m)      \
        in_dword_masked(HWIO_LPASS_DML_TRAN_ADDR, m)
#define HWIO_LPASS_DML_TRAN_OUT(v)      \
        out_dword(HWIO_LPASS_DML_TRAN_ADDR,v)
#define HWIO_LPASS_DML_TRAN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DML_TRAN_ADDR,m,v,HWIO_LPASS_DML_TRAN_IN)
#define HWIO_LPASS_DML_TRAN_LEN_BMSK                                                                       0xffffc
#define HWIO_LPASS_DML_TRAN_LEN_SHFT                                                                           0x2

#define HWIO_LPASS_DML_STATUS_ADDR                                                                      (LPASS_CSR_REG_BASE      + 0x00002010)
#define HWIO_LPASS_DML_STATUS_OFFS                                                                      (LPASS_CSR_REG_BASE_OFFS + 0x00002010)
#define HWIO_LPASS_DML_STATUS_RMSK                                                                        0xffffc3
#define HWIO_LPASS_DML_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_DML_STATUS_ADDR, HWIO_LPASS_DML_STATUS_RMSK)
#define HWIO_LPASS_DML_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_DML_STATUS_ADDR, m)
#define HWIO_LPASS_DML_STATUS_WORDS_BMSK                                                                  0xffffc0
#define HWIO_LPASS_DML_STATUS_WORDS_SHFT                                                                       0x6
#define HWIO_LPASS_DML_STATUS_ERROR_BMSK                                                                       0x2
#define HWIO_LPASS_DML_STATUS_ERROR_SHFT                                                                       0x1
#define HWIO_LPASS_DML_STATUS_DONE_BMSK                                                                        0x1
#define HWIO_LPASS_DML_STATUS_DONE_SHFT                                                                        0x0

#define HWIO_LPASS_DML_ACK_ADDR                                                                         (LPASS_CSR_REG_BASE      + 0x00002014)
#define HWIO_LPASS_DML_ACK_OFFS                                                                         (LPASS_CSR_REG_BASE_OFFS + 0x00002014)
#define HWIO_LPASS_DML_ACK_RMSK                                                                                0x3
#define HWIO_LPASS_DML_ACK_OUT(v)      \
        out_dword(HWIO_LPASS_DML_ACK_ADDR,v)
#define HWIO_LPASS_DML_ACK_ERROR_BMSK                                                                          0x2
#define HWIO_LPASS_DML_ACK_ERROR_SHFT                                                                          0x1
#define HWIO_LPASS_DML_ACK_DONE_BMSK                                                                           0x1
#define HWIO_LPASS_DML_ACK_DONE_SHFT                                                                           0x0

#define HWIO_LPASS_DML_HW_VERSION_ADDR                                                                  (LPASS_CSR_REG_BASE      + 0x00002018)
#define HWIO_LPASS_DML_HW_VERSION_OFFS                                                                  (LPASS_CSR_REG_BASE_OFFS + 0x00002018)
#define HWIO_LPASS_DML_HW_VERSION_RMSK                                                                  0xffffffff
#define HWIO_LPASS_DML_HW_VERSION_IN          \
        in_dword_masked(HWIO_LPASS_DML_HW_VERSION_ADDR, HWIO_LPASS_DML_HW_VERSION_RMSK)
#define HWIO_LPASS_DML_HW_VERSION_INM(m)      \
        in_dword_masked(HWIO_LPASS_DML_HW_VERSION_ADDR, m)
#define HWIO_LPASS_DML_HW_VERSION_MAJOR_BMSK                                                            0xf0000000
#define HWIO_LPASS_DML_HW_VERSION_MAJOR_SHFT                                                                  0x1c
#define HWIO_LPASS_DML_HW_VERSION_MINOR_BMSK                                                             0xfff0000
#define HWIO_LPASS_DML_HW_VERSION_MINOR_SHFT                                                                  0x10
#define HWIO_LPASS_DML_HW_VERSION_STEP_BMSK                                                                 0xffff
#define HWIO_LPASS_DML_HW_VERSION_STEP_SHFT                                                                    0x0

#define HWIO_LPASS_DML_SRC_EXT_ADDR                                                                     (LPASS_CSR_REG_BASE      + 0x0000201c)
#define HWIO_LPASS_DML_SRC_EXT_OFFS                                                                     (LPASS_CSR_REG_BASE_OFFS + 0x0000201c)
#define HWIO_LPASS_DML_SRC_EXT_RMSK                                                                            0xf
#define HWIO_LPASS_DML_SRC_EXT_IN          \
        in_dword_masked(HWIO_LPASS_DML_SRC_EXT_ADDR, HWIO_LPASS_DML_SRC_EXT_RMSK)
#define HWIO_LPASS_DML_SRC_EXT_INM(m)      \
        in_dword_masked(HWIO_LPASS_DML_SRC_EXT_ADDR, m)
#define HWIO_LPASS_DML_SRC_EXT_OUT(v)      \
        out_dword(HWIO_LPASS_DML_SRC_EXT_ADDR,v)
#define HWIO_LPASS_DML_SRC_EXT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DML_SRC_EXT_ADDR,m,v,HWIO_LPASS_DML_SRC_EXT_IN)
#define HWIO_LPASS_DML_SRC_EXT_ADDR_BMSK                                                                       0xf
#define HWIO_LPASS_DML_SRC_EXT_ADDR_SHFT                                                                       0x0

#define HWIO_LPASS_DML_DST_EXT_ADDR                                                                     (LPASS_CSR_REG_BASE      + 0x00002020)
#define HWIO_LPASS_DML_DST_EXT_OFFS                                                                     (LPASS_CSR_REG_BASE_OFFS + 0x00002020)
#define HWIO_LPASS_DML_DST_EXT_RMSK                                                                            0xf
#define HWIO_LPASS_DML_DST_EXT_IN          \
        in_dword_masked(HWIO_LPASS_DML_DST_EXT_ADDR, HWIO_LPASS_DML_DST_EXT_RMSK)
#define HWIO_LPASS_DML_DST_EXT_INM(m)      \
        in_dword_masked(HWIO_LPASS_DML_DST_EXT_ADDR, m)
#define HWIO_LPASS_DML_DST_EXT_OUT(v)      \
        out_dword(HWIO_LPASS_DML_DST_EXT_ADDR,v)
#define HWIO_LPASS_DML_DST_EXT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DML_DST_EXT_ADDR,m,v,HWIO_LPASS_DML_DST_EXT_IN)
#define HWIO_LPASS_DML_DST_EXT_ADDR_BMSK                                                                       0xf
#define HWIO_LPASS_DML_DST_EXT_ADDR_SHFT                                                                       0x0

#define HWIO_LPASS_LPM_CTL_ADDR                                                                         (LPASS_CSR_REG_BASE      + 0x00003000)
#define HWIO_LPASS_LPM_CTL_OFFS                                                                         (LPASS_CSR_REG_BASE_OFFS + 0x00003000)
#define HWIO_LPASS_LPM_CTL_RMSK                                                                         0x80000000
#define HWIO_LPASS_LPM_CTL_IN          \
        in_dword_masked(HWIO_LPASS_LPM_CTL_ADDR, HWIO_LPASS_LPM_CTL_RMSK)
#define HWIO_LPASS_LPM_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPM_CTL_ADDR, m)
#define HWIO_LPASS_LPM_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_LPM_CTL_ADDR,v)
#define HWIO_LPASS_LPM_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPM_CTL_ADDR,m,v,HWIO_LPASS_LPM_CTL_IN)
#define HWIO_LPASS_LPM_CTL_SOFT_RESET_BMSK                                                              0x80000000
#define HWIO_LPASS_LPM_CTL_SOFT_RESET_SHFT                                                                    0x1f

#define HWIO_LPASS_LPM_HW_VERSION_ADDR                                                                  (LPASS_CSR_REG_BASE      + 0x00003004)
#define HWIO_LPASS_LPM_HW_VERSION_OFFS                                                                  (LPASS_CSR_REG_BASE_OFFS + 0x00003004)
#define HWIO_LPASS_LPM_HW_VERSION_RMSK                                                                  0xffffffff
#define HWIO_LPASS_LPM_HW_VERSION_IN          \
        in_dword_masked(HWIO_LPASS_LPM_HW_VERSION_ADDR, HWIO_LPASS_LPM_HW_VERSION_RMSK)
#define HWIO_LPASS_LPM_HW_VERSION_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPM_HW_VERSION_ADDR, m)
#define HWIO_LPASS_LPM_HW_VERSION_MAJOR_BMSK                                                            0xf0000000
#define HWIO_LPASS_LPM_HW_VERSION_MAJOR_SHFT                                                                  0x1c
#define HWIO_LPASS_LPM_HW_VERSION_MINOR_BMSK                                                             0xfff0000
#define HWIO_LPASS_LPM_HW_VERSION_MINOR_SHFT                                                                  0x10
#define HWIO_LPASS_LPM_HW_VERSION_STEP_BMSK                                                                 0xffff
#define HWIO_LPASS_LPM_HW_VERSION_STEP_SHFT                                                                    0x0

#define HWIO_LPASS_RESAMPLER_CTL_ADDR                                                                   (LPASS_CSR_REG_BASE      + 0x00004000)
#define HWIO_LPASS_RESAMPLER_CTL_OFFS                                                                   (LPASS_CSR_REG_BASE_OFFS + 0x00004000)
#define HWIO_LPASS_RESAMPLER_CTL_RMSK                                                                   0xf0000000
#define HWIO_LPASS_RESAMPLER_CTL_IN          \
        in_dword_masked(HWIO_LPASS_RESAMPLER_CTL_ADDR, HWIO_LPASS_RESAMPLER_CTL_RMSK)
#define HWIO_LPASS_RESAMPLER_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_RESAMPLER_CTL_ADDR, m)
#define HWIO_LPASS_RESAMPLER_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_RESAMPLER_CTL_ADDR,v)
#define HWIO_LPASS_RESAMPLER_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_RESAMPLER_CTL_ADDR,m,v,HWIO_LPASS_RESAMPLER_CTL_IN)
#define HWIO_LPASS_RESAMPLER_CTL_SOFT_RESET_BMSK                                                        0x80000000
#define HWIO_LPASS_RESAMPLER_CTL_SOFT_RESET_SHFT                                                              0x1f
#define HWIO_LPASS_RESAMPLER_CTL_FORCE_RESET_BMSK                                                       0x40000000
#define HWIO_LPASS_RESAMPLER_CTL_FORCE_RESET_SHFT                                                             0x1e
#define HWIO_LPASS_RESAMPLER_CTL_FORCE_CORE_CGC_EN_BMSK                                                 0x20000000
#define HWIO_LPASS_RESAMPLER_CTL_FORCE_CORE_CGC_EN_SHFT                                                       0x1d
#define HWIO_LPASS_RESAMPLER_CTL_FORCE_AHB_CGC_EN_BMSK                                                  0x10000000
#define HWIO_LPASS_RESAMPLER_CTL_FORCE_AHB_CGC_EN_SHFT                                                        0x1c

#define HWIO_LPASS_RESAMPLER_STAT_ADDR                                                                  (LPASS_CSR_REG_BASE      + 0x00004004)
#define HWIO_LPASS_RESAMPLER_STAT_OFFS                                                                  (LPASS_CSR_REG_BASE_OFFS + 0x00004004)
#define HWIO_LPASS_RESAMPLER_STAT_RMSK                                                                         0x1
#define HWIO_LPASS_RESAMPLER_STAT_IN          \
        in_dword_masked(HWIO_LPASS_RESAMPLER_STAT_ADDR, HWIO_LPASS_RESAMPLER_STAT_RMSK)
#define HWIO_LPASS_RESAMPLER_STAT_INM(m)      \
        in_dword_masked(HWIO_LPASS_RESAMPLER_STAT_ADDR, m)
#define HWIO_LPASS_RESAMPLER_STAT_SOFT_RESET_STAT_BMSK                                                         0x1
#define HWIO_LPASS_RESAMPLER_STAT_SOFT_RESET_STAT_SHFT                                                         0x0

#define HWIO_LPASS_LPAIF_CTL_ADDR                                                                       (LPASS_CSR_REG_BASE      + 0x00005000)
#define HWIO_LPASS_LPAIF_CTL_OFFS                                                                       (LPASS_CSR_REG_BASE_OFFS + 0x00005000)
#define HWIO_LPASS_LPAIF_CTL_RMSK                                                                       0x80000000
#define HWIO_LPASS_LPAIF_CTL_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_CTL_ADDR, HWIO_LPASS_LPAIF_CTL_RMSK)
#define HWIO_LPASS_LPAIF_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_CTL_ADDR, m)
#define HWIO_LPASS_LPAIF_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_CTL_ADDR,v)
#define HWIO_LPASS_LPAIF_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_CTL_ADDR,m,v,HWIO_LPASS_LPAIF_CTL_IN)
#define HWIO_LPASS_LPAIF_CTL_SOFT_RESET_BMSK                                                            0x80000000
#define HWIO_LPASS_LPAIF_CTL_SOFT_RESET_SHFT                                                                  0x1f

#define HWIO_LPASS_SPDIFTX_CTL_ADDR                                                                     (LPASS_CSR_REG_BASE      + 0x00006000)
#define HWIO_LPASS_SPDIFTX_CTL_OFFS                                                                     (LPASS_CSR_REG_BASE_OFFS + 0x00006000)
#define HWIO_LPASS_SPDIFTX_CTL_RMSK                                                                     0xc0000000
#define HWIO_LPASS_SPDIFTX_CTL_IN          \
        in_dword_masked(HWIO_LPASS_SPDIFTX_CTL_ADDR, HWIO_LPASS_SPDIFTX_CTL_RMSK)
#define HWIO_LPASS_SPDIFTX_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_SPDIFTX_CTL_ADDR, m)
#define HWIO_LPASS_SPDIFTX_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_SPDIFTX_CTL_ADDR,v)
#define HWIO_LPASS_SPDIFTX_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SPDIFTX_CTL_ADDR,m,v,HWIO_LPASS_SPDIFTX_CTL_IN)
#define HWIO_LPASS_SPDIFTX_CTL_SOFT_RESET_BMSK                                                          0x80000000
#define HWIO_LPASS_SPDIFTX_CTL_SOFT_RESET_SHFT                                                                0x1f
#define HWIO_LPASS_SPDIFTX_CTL_FORCE_RESET_BMSK                                                         0x40000000
#define HWIO_LPASS_SPDIFTX_CTL_FORCE_RESET_SHFT                                                               0x1e

#define HWIO_LPASS_SPDIFTX_STAT_ADDR                                                                    (LPASS_CSR_REG_BASE      + 0x00006004)
#define HWIO_LPASS_SPDIFTX_STAT_OFFS                                                                    (LPASS_CSR_REG_BASE_OFFS + 0x00006004)
#define HWIO_LPASS_SPDIFTX_STAT_RMSK                                                                           0x1
#define HWIO_LPASS_SPDIFTX_STAT_IN          \
        in_dword_masked(HWIO_LPASS_SPDIFTX_STAT_ADDR, HWIO_LPASS_SPDIFTX_STAT_RMSK)
#define HWIO_LPASS_SPDIFTX_STAT_INM(m)      \
        in_dword_masked(HWIO_LPASS_SPDIFTX_STAT_ADDR, m)
#define HWIO_LPASS_SPDIFTX_STAT_SOFT_RESET_STAT_BMSK                                                           0x1
#define HWIO_LPASS_SPDIFTX_STAT_SOFT_RESET_STAT_SHFT                                                           0x0

#define HWIO_LPASS_HDMIRX_CTL_ADDR                                                                      (LPASS_CSR_REG_BASE      + 0x00007000)
#define HWIO_LPASS_HDMIRX_CTL_OFFS                                                                      (LPASS_CSR_REG_BASE_OFFS + 0x00007000)
#define HWIO_LPASS_HDMIRX_CTL_RMSK                                                                      0xc0000000
#define HWIO_LPASS_HDMIRX_CTL_IN          \
        in_dword_masked(HWIO_LPASS_HDMIRX_CTL_ADDR, HWIO_LPASS_HDMIRX_CTL_RMSK)
#define HWIO_LPASS_HDMIRX_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_HDMIRX_CTL_ADDR, m)
#define HWIO_LPASS_HDMIRX_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_HDMIRX_CTL_ADDR,v)
#define HWIO_LPASS_HDMIRX_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_HDMIRX_CTL_ADDR,m,v,HWIO_LPASS_HDMIRX_CTL_IN)
#define HWIO_LPASS_HDMIRX_CTL_SOFT_RESET_BMSK                                                           0x80000000
#define HWIO_LPASS_HDMIRX_CTL_SOFT_RESET_SHFT                                                                 0x1f
#define HWIO_LPASS_HDMIRX_CTL_FORCE_RESET_BMSK                                                          0x40000000
#define HWIO_LPASS_HDMIRX_CTL_FORCE_RESET_SHFT                                                                0x1e

#define HWIO_LPASS_HDMIRX_STAT_ADDR                                                                     (LPASS_CSR_REG_BASE      + 0x00007004)
#define HWIO_LPASS_HDMIRX_STAT_OFFS                                                                     (LPASS_CSR_REG_BASE_OFFS + 0x00007004)
#define HWIO_LPASS_HDMIRX_STAT_RMSK                                                                            0x1
#define HWIO_LPASS_HDMIRX_STAT_IN          \
        in_dword_masked(HWIO_LPASS_HDMIRX_STAT_ADDR, HWIO_LPASS_HDMIRX_STAT_RMSK)
#define HWIO_LPASS_HDMIRX_STAT_INM(m)      \
        in_dword_masked(HWIO_LPASS_HDMIRX_STAT_ADDR, m)
#define HWIO_LPASS_HDMIRX_STAT_SOFT_RESET_STAT_BMSK                                                            0x1
#define HWIO_LPASS_HDMIRX_STAT_SOFT_RESET_STAT_SHFT                                                            0x0

#define HWIO_LPASS_HDMITX_CTL_ADDR                                                                      (LPASS_CSR_REG_BASE      + 0x00008000)
#define HWIO_LPASS_HDMITX_CTL_OFFS                                                                      (LPASS_CSR_REG_BASE_OFFS + 0x00008000)
#define HWIO_LPASS_HDMITX_CTL_RMSK                                                                      0xc0000000
#define HWIO_LPASS_HDMITX_CTL_IN          \
        in_dword_masked(HWIO_LPASS_HDMITX_CTL_ADDR, HWIO_LPASS_HDMITX_CTL_RMSK)
#define HWIO_LPASS_HDMITX_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_HDMITX_CTL_ADDR, m)
#define HWIO_LPASS_HDMITX_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_HDMITX_CTL_ADDR,v)
#define HWIO_LPASS_HDMITX_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_HDMITX_CTL_ADDR,m,v,HWIO_LPASS_HDMITX_CTL_IN)
#define HWIO_LPASS_HDMITX_CTL_SOFT_RESET_BMSK                                                           0x80000000
#define HWIO_LPASS_HDMITX_CTL_SOFT_RESET_SHFT                                                                 0x1f
#define HWIO_LPASS_HDMITX_CTL_FORCE_RESET_BMSK                                                          0x40000000
#define HWIO_LPASS_HDMITX_CTL_FORCE_RESET_SHFT                                                                0x1e

#define HWIO_LPASS_HDMITX_STAT_ADDR                                                                     (LPASS_CSR_REG_BASE      + 0x00008004)
#define HWIO_LPASS_HDMITX_STAT_OFFS                                                                     (LPASS_CSR_REG_BASE_OFFS + 0x00008004)
#define HWIO_LPASS_HDMITX_STAT_RMSK                                                                            0x1
#define HWIO_LPASS_HDMITX_STAT_IN          \
        in_dword_masked(HWIO_LPASS_HDMITX_STAT_ADDR, HWIO_LPASS_HDMITX_STAT_RMSK)
#define HWIO_LPASS_HDMITX_STAT_INM(m)      \
        in_dword_masked(HWIO_LPASS_HDMITX_STAT_ADDR, m)
#define HWIO_LPASS_HDMITX_STAT_SOFT_RESET_STAT_BMSK                                                            0x1
#define HWIO_LPASS_HDMITX_STAT_SOFT_RESET_STAT_SHFT                                                            0x0

#define HWIO_LPASS_HDMITX_LEGACY_ADDR                                                                   (LPASS_CSR_REG_BASE      + 0x00008008)
#define HWIO_LPASS_HDMITX_LEGACY_OFFS                                                                   (LPASS_CSR_REG_BASE_OFFS + 0x00008008)
#define HWIO_LPASS_HDMITX_LEGACY_RMSK                                                                          0x1
#define HWIO_LPASS_HDMITX_LEGACY_IN          \
        in_dword_masked(HWIO_LPASS_HDMITX_LEGACY_ADDR, HWIO_LPASS_HDMITX_LEGACY_RMSK)
#define HWIO_LPASS_HDMITX_LEGACY_INM(m)      \
        in_dword_masked(HWIO_LPASS_HDMITX_LEGACY_ADDR, m)
#define HWIO_LPASS_HDMITX_LEGACY_OUT(v)      \
        out_dword(HWIO_LPASS_HDMITX_LEGACY_ADDR,v)
#define HWIO_LPASS_HDMITX_LEGACY_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_HDMITX_LEGACY_ADDR,m,v,HWIO_LPASS_HDMITX_LEGACY_IN)
#define HWIO_LPASS_HDMITX_LEGACY_LEGACY_EN_BMSK                                                                0x1
#define HWIO_LPASS_HDMITX_LEGACY_LEGACY_EN_SHFT                                                                0x0

#define HWIO_LPASS_TLB_PL_CTL_ADDR                                                                      (LPASS_CSR_REG_BASE      + 0x00009000)
#define HWIO_LPASS_TLB_PL_CTL_OFFS                                                                      (LPASS_CSR_REG_BASE_OFFS + 0x00009000)
#define HWIO_LPASS_TLB_PL_CTL_RMSK                                                                      0xc0000000
#define HWIO_LPASS_TLB_PL_CTL_IN          \
        in_dword_masked(HWIO_LPASS_TLB_PL_CTL_ADDR, HWIO_LPASS_TLB_PL_CTL_RMSK)
#define HWIO_LPASS_TLB_PL_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_TLB_PL_CTL_ADDR, m)
#define HWIO_LPASS_TLB_PL_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_TLB_PL_CTL_ADDR,v)
#define HWIO_LPASS_TLB_PL_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_TLB_PL_CTL_ADDR,m,v,HWIO_LPASS_TLB_PL_CTL_IN)
#define HWIO_LPASS_TLB_PL_CTL_SOFT_RESET_BMSK                                                           0x80000000
#define HWIO_LPASS_TLB_PL_CTL_SOFT_RESET_SHFT                                                                 0x1f
#define HWIO_LPASS_TLB_PL_CTL_FORCE_RESET_BMSK                                                          0x40000000
#define HWIO_LPASS_TLB_PL_CTL_FORCE_RESET_SHFT                                                                0x1e

#define HWIO_LPASS_TLB_PL_STAT_ADDR                                                                     (LPASS_CSR_REG_BASE      + 0x00009004)
#define HWIO_LPASS_TLB_PL_STAT_OFFS                                                                     (LPASS_CSR_REG_BASE_OFFS + 0x00009004)
#define HWIO_LPASS_TLB_PL_STAT_RMSK                                                                            0x1
#define HWIO_LPASS_TLB_PL_STAT_IN          \
        in_dword_masked(HWIO_LPASS_TLB_PL_STAT_ADDR, HWIO_LPASS_TLB_PL_STAT_RMSK)
#define HWIO_LPASS_TLB_PL_STAT_INM(m)      \
        in_dword_masked(HWIO_LPASS_TLB_PL_STAT_ADDR, m)
#define HWIO_LPASS_TLB_PL_STAT_SOFT_RESET_STAT_BMSK                                                            0x1
#define HWIO_LPASS_TLB_PL_STAT_SOFT_RESET_STAT_SHFT                                                            0x0

#define HWIO_LPASS_AUDIO_CORE_CORE_CSR_CORE_CGCR_ADDR                                                   (LPASS_CSR_REG_BASE      + 0x0000a000)
#define HWIO_LPASS_AUDIO_CORE_CORE_CSR_CORE_CGCR_OFFS                                                   (LPASS_CSR_REG_BASE_OFFS + 0x0000a000)
#define HWIO_LPASS_AUDIO_CORE_CORE_CSR_CORE_CGCR_RMSK                                                          0x3
#define HWIO_LPASS_AUDIO_CORE_CORE_CSR_CORE_CGCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_CORE_CSR_CORE_CGCR_ADDR, HWIO_LPASS_AUDIO_CORE_CORE_CSR_CORE_CGCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_CORE_CSR_CORE_CGCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_CORE_CSR_CORE_CGCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_CORE_CSR_CORE_CGCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_CORE_CSR_CORE_CGCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_CORE_CSR_CORE_CGCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_CORE_CSR_CORE_CGCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_CORE_CSR_CORE_CGCR_IN)
#define HWIO_LPASS_AUDIO_CORE_CORE_CSR_CORE_CGCR_HW_CTL_BMSK                                                   0x2
#define HWIO_LPASS_AUDIO_CORE_CORE_CSR_CORE_CGCR_HW_CTL_SHFT                                                   0x1
#define HWIO_LPASS_AUDIO_CORE_CORE_CSR_CORE_CGCR_CLK_ENABLE_BMSK                                               0x1
#define HWIO_LPASS_AUDIO_CORE_CORE_CSR_CORE_CGCR_CLK_ENABLE_SHFT                                               0x0

#define HWIO_LPASS_AUDIO_CORE_CORE_CSR_CORE_HYSTERESIS_ADDR                                             (LPASS_CSR_REG_BASE      + 0x0000a004)
#define HWIO_LPASS_AUDIO_CORE_CORE_CSR_CORE_HYSTERESIS_OFFS                                             (LPASS_CSR_REG_BASE_OFFS + 0x0000a004)
#define HWIO_LPASS_AUDIO_CORE_CORE_CSR_CORE_HYSTERESIS_RMSK                                                    0x7
#define HWIO_LPASS_AUDIO_CORE_CORE_CSR_CORE_HYSTERESIS_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_CORE_CSR_CORE_HYSTERESIS_ADDR, HWIO_LPASS_AUDIO_CORE_CORE_CSR_CORE_HYSTERESIS_RMSK)
#define HWIO_LPASS_AUDIO_CORE_CORE_CSR_CORE_HYSTERESIS_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_CORE_CSR_CORE_HYSTERESIS_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_CORE_CSR_CORE_HYSTERESIS_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_CORE_CSR_CORE_HYSTERESIS_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_CORE_CSR_CORE_HYSTERESIS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_CORE_CSR_CORE_HYSTERESIS_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_CORE_CSR_CORE_HYSTERESIS_IN)
#define HWIO_LPASS_AUDIO_CORE_CORE_CSR_CORE_HYSTERESIS_ACTIVE_HYSTSEL_BMSK                                     0x7
#define HWIO_LPASS_AUDIO_CORE_CORE_CSR_CORE_HYSTERESIS_ACTIVE_HYSTSEL_SHFT                                     0x0

#define HWIO_LPASS_AUDIO_CORE_QOS_CORE_CGCR_ADDR                                                        (LPASS_CSR_REG_BASE      + 0x0000b000)
#define HWIO_LPASS_AUDIO_CORE_QOS_CORE_CGCR_OFFS                                                        (LPASS_CSR_REG_BASE_OFFS + 0x0000b000)
#define HWIO_LPASS_AUDIO_CORE_QOS_CORE_CGCR_RMSK                                                               0x3
#define HWIO_LPASS_AUDIO_CORE_QOS_CORE_CGCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_QOS_CORE_CGCR_ADDR, HWIO_LPASS_AUDIO_CORE_QOS_CORE_CGCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_QOS_CORE_CGCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_QOS_CORE_CGCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_QOS_CORE_CGCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_QOS_CORE_CGCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_QOS_CORE_CGCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_QOS_CORE_CGCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_QOS_CORE_CGCR_IN)
#define HWIO_LPASS_AUDIO_CORE_QOS_CORE_CGCR_HW_CTL_BMSK                                                        0x2
#define HWIO_LPASS_AUDIO_CORE_QOS_CORE_CGCR_HW_CTL_SHFT                                                        0x1
#define HWIO_LPASS_AUDIO_CORE_QOS_CORE_CGCR_CLK_ENABLE_BMSK                                                    0x1
#define HWIO_LPASS_AUDIO_CORE_QOS_CORE_CGCR_CLK_ENABLE_SHFT                                                    0x0

#define HWIO_LPASS_AUDIO_CORE_QOS_CORE_HYSTERESIS_ADDR                                                  (LPASS_CSR_REG_BASE      + 0x0000b004)
#define HWIO_LPASS_AUDIO_CORE_QOS_CORE_HYSTERESIS_OFFS                                                  (LPASS_CSR_REG_BASE_OFFS + 0x0000b004)
#define HWIO_LPASS_AUDIO_CORE_QOS_CORE_HYSTERESIS_RMSK                                                         0x7
#define HWIO_LPASS_AUDIO_CORE_QOS_CORE_HYSTERESIS_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_QOS_CORE_HYSTERESIS_ADDR, HWIO_LPASS_AUDIO_CORE_QOS_CORE_HYSTERESIS_RMSK)
#define HWIO_LPASS_AUDIO_CORE_QOS_CORE_HYSTERESIS_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_QOS_CORE_HYSTERESIS_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_QOS_CORE_HYSTERESIS_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_QOS_CORE_HYSTERESIS_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_QOS_CORE_HYSTERESIS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_QOS_CORE_HYSTERESIS_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_QOS_CORE_HYSTERESIS_IN)
#define HWIO_LPASS_AUDIO_CORE_QOS_CORE_HYSTERESIS_ACTIVE_HYSTSEL_BMSK                                          0x7
#define HWIO_LPASS_AUDIO_CORE_QOS_CORE_HYSTERESIS_ACTIVE_HYSTSEL_SHFT                                          0x0

#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CORE_CGCR_ADDR                                                     (LPASS_CSR_REG_BASE      + 0x0000c000)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CORE_CGCR_OFFS                                                     (LPASS_CSR_REG_BASE_OFFS + 0x0000c000)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CORE_CGCR_RMSK                                                            0x3
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CORE_CGCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_AVSYNC_CORE_CGCR_ADDR, HWIO_LPASS_AUDIO_CORE_AVSYNC_CORE_CGCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CORE_CGCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_AVSYNC_CORE_CGCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CORE_CGCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_AVSYNC_CORE_CGCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CORE_CGCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_AVSYNC_CORE_CGCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_AVSYNC_CORE_CGCR_IN)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CORE_CGCR_HW_CTL_BMSK                                                     0x2
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CORE_CGCR_HW_CTL_SHFT                                                     0x1
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CORE_CGCR_CLK_ENABLE_BMSK                                                 0x1
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CORE_CGCR_CLK_ENABLE_SHFT                                                 0x0

#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CORE_HYSTERESIS_ADDR                                               (LPASS_CSR_REG_BASE      + 0x0000c004)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CORE_HYSTERESIS_OFFS                                               (LPASS_CSR_REG_BASE_OFFS + 0x0000c004)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CORE_HYSTERESIS_RMSK                                                      0x7
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CORE_HYSTERESIS_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_AVSYNC_CORE_HYSTERESIS_ADDR, HWIO_LPASS_AUDIO_CORE_AVSYNC_CORE_HYSTERESIS_RMSK)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CORE_HYSTERESIS_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_AVSYNC_CORE_HYSTERESIS_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CORE_HYSTERESIS_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_AVSYNC_CORE_HYSTERESIS_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CORE_HYSTERESIS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_AVSYNC_CORE_HYSTERESIS_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_AVSYNC_CORE_HYSTERESIS_IN)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CORE_HYSTERESIS_ACTIVE_HYSTSEL_BMSK                                       0x7
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_CORE_HYSTERESIS_ACTIVE_HYSTSEL_SHFT                                       0x0

#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CGCR_ADDR                                                        (LPASS_CSR_REG_BASE      + 0x0000d000)
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CGCR_OFFS                                                        (LPASS_CSR_REG_BASE_OFFS + 0x0000d000)
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CGCR_RMSK                                                               0x3
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CGCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPM_CORE_CGCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPM_CORE_CGCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CGCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPM_CORE_CGCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CGCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPM_CORE_CGCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CGCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPM_CORE_CGCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPM_CORE_CGCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CGCR_HW_CTL_BMSK                                                        0x2
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CGCR_HW_CTL_SHFT                                                        0x1
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CGCR_CLK_ENABLE_BMSK                                                    0x1
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CGCR_CLK_ENABLE_SHFT                                                    0x0

#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_HYSTERESIS_ADDR                                                  (LPASS_CSR_REG_BASE      + 0x0000d004)
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_HYSTERESIS_OFFS                                                  (LPASS_CSR_REG_BASE_OFFS + 0x0000d004)
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_HYSTERESIS_RMSK                                                         0x7
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_HYSTERESIS_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPM_CORE_HYSTERESIS_ADDR, HWIO_LPASS_AUDIO_CORE_LPM_CORE_HYSTERESIS_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_HYSTERESIS_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPM_CORE_HYSTERESIS_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_HYSTERESIS_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPM_CORE_HYSTERESIS_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_HYSTERESIS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPM_CORE_HYSTERESIS_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPM_CORE_HYSTERESIS_IN)
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_HYSTERESIS_ACTIVE_HYSTSEL_BMSK                                          0x7
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_HYSTERESIS_ACTIVE_HYSTSEL_SHFT                                          0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CORE_CGCR_ADDR                                                  (LPASS_CSR_REG_BASE      + 0x0000e000)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CORE_CGCR_OFFS                                                  (LPASS_CSR_REG_BASE_OFFS + 0x0000e000)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CORE_CGCR_RMSK                                                         0x3
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CORE_CGCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CORE_CGCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CORE_CGCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CORE_CGCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CORE_CGCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CORE_CGCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CORE_CGCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CORE_CGCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CORE_CGCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CORE_CGCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CORE_CGCR_HW_CTL_BMSK                                                  0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CORE_CGCR_HW_CTL_SHFT                                                  0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CORE_CGCR_CLK_ENABLE_BMSK                                              0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CORE_CGCR_CLK_ENABLE_SHFT                                              0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CORE_HYSTERESIS_ADDR                                            (LPASS_CSR_REG_BASE      + 0x0000e004)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CORE_HYSTERESIS_OFFS                                            (LPASS_CSR_REG_BASE_OFFS + 0x0000e004)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CORE_HYSTERESIS_RMSK                                                   0x7
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CORE_HYSTERESIS_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CORE_HYSTERESIS_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CORE_HYSTERESIS_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CORE_HYSTERESIS_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CORE_HYSTERESIS_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CORE_HYSTERESIS_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CORE_HYSTERESIS_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CORE_HYSTERESIS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CORE_HYSTERESIS_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CORE_HYSTERESIS_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CORE_HYSTERESIS_ACTIVE_HYSTSEL_BMSK                                    0x7
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CORE_HYSTERESIS_ACTIVE_HYSTSEL_SHFT                                    0x0

#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CGCR_ADDR                                                  (LPASS_CSR_REG_BASE      + 0x0000f000)
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CGCR_OFFS                                                  (LPASS_CSR_REG_BASE_OFFS + 0x0000f000)
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CGCR_RMSK                                                         0x3
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CGCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CGCR_ADDR, HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CGCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CGCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CGCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CGCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CGCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CGCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CGCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CGCR_IN)
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CGCR_HW_CTL_BMSK                                                  0x2
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CGCR_HW_CTL_SHFT                                                  0x1
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CGCR_CLK_ENABLE_BMSK                                              0x1
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CGCR_CLK_ENABLE_SHFT                                              0x0

#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_HYSTERESIS_ADDR                                            (LPASS_CSR_REG_BASE      + 0x0000f004)
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_HYSTERESIS_OFFS                                            (LPASS_CSR_REG_BASE_OFFS + 0x0000f004)
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_HYSTERESIS_RMSK                                                   0x7
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_HYSTERESIS_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_HYSTERESIS_ADDR, HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_HYSTERESIS_RMSK)
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_HYSTERESIS_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_HYSTERESIS_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_HYSTERESIS_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_HYSTERESIS_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_HYSTERESIS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_HYSTERESIS_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_HYSTERESIS_IN)
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_HYSTERESIS_ACTIVE_HYSTSEL_BMSK                                    0x7
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_HYSTERESIS_ACTIVE_HYSTSEL_SHFT                                    0x0

#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CGCR_ADDR                                                (LPASS_CSR_REG_BASE      + 0x00010000)
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CGCR_OFFS                                                (LPASS_CSR_REG_BASE_OFFS + 0x00010000)
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CGCR_RMSK                                                       0x3
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CGCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CGCR_ADDR, HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CGCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CGCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CGCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CGCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CGCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CGCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CGCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CGCR_IN)
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CGCR_HW_CTL_BMSK                                                0x2
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CGCR_HW_CTL_SHFT                                                0x1
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CGCR_CLK_ENABLE_BMSK                                            0x1
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CGCR_CLK_ENABLE_SHFT                                            0x0

#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_HYSTERESIS_ADDR                                          (LPASS_CSR_REG_BASE      + 0x00010004)
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_HYSTERESIS_OFFS                                          (LPASS_CSR_REG_BASE_OFFS + 0x00010004)
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_HYSTERESIS_RMSK                                                 0x7
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_HYSTERESIS_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_HYSTERESIS_ADDR, HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_HYSTERESIS_RMSK)
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_HYSTERESIS_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_HYSTERESIS_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_HYSTERESIS_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_HYSTERESIS_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_HYSTERESIS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_HYSTERESIS_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_HYSTERESIS_IN)
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_HYSTERESIS_ACTIVE_HYSTSEL_BMSK                                  0x7
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_HYSTERESIS_ACTIVE_HYSTSEL_SHFT                                  0x0

#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CGCR_ADDR                                                (LPASS_CSR_REG_BASE      + 0x00011000)
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CGCR_OFFS                                                (LPASS_CSR_REG_BASE_OFFS + 0x00011000)
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CGCR_RMSK                                                       0x3
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CGCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CGCR_ADDR, HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CGCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CGCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CGCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CGCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CGCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CGCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CGCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CGCR_IN)
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CGCR_HW_CTL_BMSK                                                0x2
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CGCR_HW_CTL_SHFT                                                0x1
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CGCR_CLK_ENABLE_BMSK                                            0x1
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CGCR_CLK_ENABLE_SHFT                                            0x0

#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_HYSTERESIS_ADDR                                          (LPASS_CSR_REG_BASE      + 0x00011004)
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_HYSTERESIS_OFFS                                          (LPASS_CSR_REG_BASE_OFFS + 0x00011004)
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_HYSTERESIS_RMSK                                                 0x7
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_HYSTERESIS_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_HYSTERESIS_ADDR, HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_HYSTERESIS_RMSK)
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_HYSTERESIS_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_HYSTERESIS_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_HYSTERESIS_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_HYSTERESIS_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_HYSTERESIS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_HYSTERESIS_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_HYSTERESIS_IN)
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_HYSTERESIS_ACTIVE_HYSTSEL_BMSK                                  0x7
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_HYSTERESIS_ACTIVE_HYSTSEL_SHFT                                  0x0

#define HWIO_LPASS_AUDIO_CORE_HDMITX_CORE_CGCR_ADDR                                                     (LPASS_CSR_REG_BASE      + 0x00012000)
#define HWIO_LPASS_AUDIO_CORE_HDMITX_CORE_CGCR_OFFS                                                     (LPASS_CSR_REG_BASE_OFFS + 0x00012000)
#define HWIO_LPASS_AUDIO_CORE_HDMITX_CORE_CGCR_RMSK                                                            0x3
#define HWIO_LPASS_AUDIO_CORE_HDMITX_CORE_CGCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_HDMITX_CORE_CGCR_ADDR, HWIO_LPASS_AUDIO_CORE_HDMITX_CORE_CGCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_HDMITX_CORE_CGCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_HDMITX_CORE_CGCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_HDMITX_CORE_CGCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_HDMITX_CORE_CGCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_HDMITX_CORE_CGCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_HDMITX_CORE_CGCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_HDMITX_CORE_CGCR_IN)
#define HWIO_LPASS_AUDIO_CORE_HDMITX_CORE_CGCR_HW_CTL_BMSK                                                     0x2
#define HWIO_LPASS_AUDIO_CORE_HDMITX_CORE_CGCR_HW_CTL_SHFT                                                     0x1
#define HWIO_LPASS_AUDIO_CORE_HDMITX_CORE_CGCR_CLK_ENABLE_BMSK                                                 0x1
#define HWIO_LPASS_AUDIO_CORE_HDMITX_CORE_CGCR_CLK_ENABLE_SHFT                                                 0x0

#define HWIO_LPASS_AUDIO_CORE_HDMITX_CORE_HYSTERESIS_ADDR                                               (LPASS_CSR_REG_BASE      + 0x00012004)
#define HWIO_LPASS_AUDIO_CORE_HDMITX_CORE_HYSTERESIS_OFFS                                               (LPASS_CSR_REG_BASE_OFFS + 0x00012004)
#define HWIO_LPASS_AUDIO_CORE_HDMITX_CORE_HYSTERESIS_RMSK                                                      0x7
#define HWIO_LPASS_AUDIO_CORE_HDMITX_CORE_HYSTERESIS_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_HDMITX_CORE_HYSTERESIS_ADDR, HWIO_LPASS_AUDIO_CORE_HDMITX_CORE_HYSTERESIS_RMSK)
#define HWIO_LPASS_AUDIO_CORE_HDMITX_CORE_HYSTERESIS_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_HDMITX_CORE_HYSTERESIS_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_HDMITX_CORE_HYSTERESIS_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_HDMITX_CORE_HYSTERESIS_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_HDMITX_CORE_HYSTERESIS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_HDMITX_CORE_HYSTERESIS_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_HDMITX_CORE_HYSTERESIS_IN)
#define HWIO_LPASS_AUDIO_CORE_HDMITX_CORE_HYSTERESIS_ACTIVE_HYSTSEL_BMSK                                       0x7
#define HWIO_LPASS_AUDIO_CORE_HDMITX_CORE_HYSTERESIS_ACTIVE_HYSTSEL_SHFT                                       0x0

#define HWIO_LPASS_AUDIO_CORE_HDMIRX_CORE_CGCR_ADDR                                                     (LPASS_CSR_REG_BASE      + 0x00013000)
#define HWIO_LPASS_AUDIO_CORE_HDMIRX_CORE_CGCR_OFFS                                                     (LPASS_CSR_REG_BASE_OFFS + 0x00013000)
#define HWIO_LPASS_AUDIO_CORE_HDMIRX_CORE_CGCR_RMSK                                                            0x3
#define HWIO_LPASS_AUDIO_CORE_HDMIRX_CORE_CGCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_HDMIRX_CORE_CGCR_ADDR, HWIO_LPASS_AUDIO_CORE_HDMIRX_CORE_CGCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_HDMIRX_CORE_CGCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_HDMIRX_CORE_CGCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_HDMIRX_CORE_CGCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_HDMIRX_CORE_CGCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_HDMIRX_CORE_CGCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_HDMIRX_CORE_CGCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_HDMIRX_CORE_CGCR_IN)
#define HWIO_LPASS_AUDIO_CORE_HDMIRX_CORE_CGCR_HW_CTL_BMSK                                                     0x2
#define HWIO_LPASS_AUDIO_CORE_HDMIRX_CORE_CGCR_HW_CTL_SHFT                                                     0x1
#define HWIO_LPASS_AUDIO_CORE_HDMIRX_CORE_CGCR_CLK_ENABLE_BMSK                                                 0x1
#define HWIO_LPASS_AUDIO_CORE_HDMIRX_CORE_CGCR_CLK_ENABLE_SHFT                                                 0x0

#define HWIO_LPASS_AUDIO_CORE_HDMIRX_CORE_HYSTERESIS_ADDR                                               (LPASS_CSR_REG_BASE      + 0x00013004)
#define HWIO_LPASS_AUDIO_CORE_HDMIRX_CORE_HYSTERESIS_OFFS                                               (LPASS_CSR_REG_BASE_OFFS + 0x00013004)
#define HWIO_LPASS_AUDIO_CORE_HDMIRX_CORE_HYSTERESIS_RMSK                                                      0x7
#define HWIO_LPASS_AUDIO_CORE_HDMIRX_CORE_HYSTERESIS_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_HDMIRX_CORE_HYSTERESIS_ADDR, HWIO_LPASS_AUDIO_CORE_HDMIRX_CORE_HYSTERESIS_RMSK)
#define HWIO_LPASS_AUDIO_CORE_HDMIRX_CORE_HYSTERESIS_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_HDMIRX_CORE_HYSTERESIS_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_HDMIRX_CORE_HYSTERESIS_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_HDMIRX_CORE_HYSTERESIS_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_HDMIRX_CORE_HYSTERESIS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_HDMIRX_CORE_HYSTERESIS_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_HDMIRX_CORE_HYSTERESIS_IN)
#define HWIO_LPASS_AUDIO_CORE_HDMIRX_CORE_HYSTERESIS_ACTIVE_HYSTSEL_BMSK                                       0x7
#define HWIO_LPASS_AUDIO_CORE_HDMIRX_CORE_HYSTERESIS_ACTIVE_HYSTSEL_SHFT                                       0x0

#define HWIO_LPASS_AUDIO_CORE_TLB_PRELOAD_CORE_CGCR_ADDR                                                (LPASS_CSR_REG_BASE      + 0x00014000)
#define HWIO_LPASS_AUDIO_CORE_TLB_PRELOAD_CORE_CGCR_OFFS                                                (LPASS_CSR_REG_BASE_OFFS + 0x00014000)
#define HWIO_LPASS_AUDIO_CORE_TLB_PRELOAD_CORE_CGCR_RMSK                                                       0x3
#define HWIO_LPASS_AUDIO_CORE_TLB_PRELOAD_CORE_CGCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_TLB_PRELOAD_CORE_CGCR_ADDR, HWIO_LPASS_AUDIO_CORE_TLB_PRELOAD_CORE_CGCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_TLB_PRELOAD_CORE_CGCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_TLB_PRELOAD_CORE_CGCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_TLB_PRELOAD_CORE_CGCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_TLB_PRELOAD_CORE_CGCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_TLB_PRELOAD_CORE_CGCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_TLB_PRELOAD_CORE_CGCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_TLB_PRELOAD_CORE_CGCR_IN)
#define HWIO_LPASS_AUDIO_CORE_TLB_PRELOAD_CORE_CGCR_HW_CTL_BMSK                                                0x2
#define HWIO_LPASS_AUDIO_CORE_TLB_PRELOAD_CORE_CGCR_HW_CTL_SHFT                                                0x1
#define HWIO_LPASS_AUDIO_CORE_TLB_PRELOAD_CORE_CGCR_CLK_ENABLE_BMSK                                            0x1
#define HWIO_LPASS_AUDIO_CORE_TLB_PRELOAD_CORE_CGCR_CLK_ENABLE_SHFT                                            0x0

#define HWIO_LPASS_AUDIO_CORE_TLB_PRELOAD_CORE_HYSTERESIS_ADDR                                          (LPASS_CSR_REG_BASE      + 0x00014004)
#define HWIO_LPASS_AUDIO_CORE_TLB_PRELOAD_CORE_HYSTERESIS_OFFS                                          (LPASS_CSR_REG_BASE_OFFS + 0x00014004)
#define HWIO_LPASS_AUDIO_CORE_TLB_PRELOAD_CORE_HYSTERESIS_RMSK                                                 0x7
#define HWIO_LPASS_AUDIO_CORE_TLB_PRELOAD_CORE_HYSTERESIS_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_TLB_PRELOAD_CORE_HYSTERESIS_ADDR, HWIO_LPASS_AUDIO_CORE_TLB_PRELOAD_CORE_HYSTERESIS_RMSK)
#define HWIO_LPASS_AUDIO_CORE_TLB_PRELOAD_CORE_HYSTERESIS_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_TLB_PRELOAD_CORE_HYSTERESIS_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_TLB_PRELOAD_CORE_HYSTERESIS_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_TLB_PRELOAD_CORE_HYSTERESIS_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_TLB_PRELOAD_CORE_HYSTERESIS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_TLB_PRELOAD_CORE_HYSTERESIS_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_TLB_PRELOAD_CORE_HYSTERESIS_IN)
#define HWIO_LPASS_AUDIO_CORE_TLB_PRELOAD_CORE_HYSTERESIS_ACTIVE_HYSTSEL_BMSK                                  0x7
#define HWIO_LPASS_AUDIO_CORE_TLB_PRELOAD_CORE_HYSTERESIS_ACTIVE_HYSTSEL_SHFT                                  0x0

#define HWIO_LPASS_AUDIO_CORE_ATIMER_CORE_CGCR_ADDR                                                     (LPASS_CSR_REG_BASE      + 0x00015000)
#define HWIO_LPASS_AUDIO_CORE_ATIMER_CORE_CGCR_OFFS                                                     (LPASS_CSR_REG_BASE_OFFS + 0x00015000)
#define HWIO_LPASS_AUDIO_CORE_ATIMER_CORE_CGCR_RMSK                                                            0x3
#define HWIO_LPASS_AUDIO_CORE_ATIMER_CORE_CGCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_ATIMER_CORE_CGCR_ADDR, HWIO_LPASS_AUDIO_CORE_ATIMER_CORE_CGCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_ATIMER_CORE_CGCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_ATIMER_CORE_CGCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_ATIMER_CORE_CGCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_ATIMER_CORE_CGCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_ATIMER_CORE_CGCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_ATIMER_CORE_CGCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_ATIMER_CORE_CGCR_IN)
#define HWIO_LPASS_AUDIO_CORE_ATIMER_CORE_CGCR_HW_CTL_BMSK                                                     0x2
#define HWIO_LPASS_AUDIO_CORE_ATIMER_CORE_CGCR_HW_CTL_SHFT                                                     0x1
#define HWIO_LPASS_AUDIO_CORE_ATIMER_CORE_CGCR_CLK_ENABLE_BMSK                                                 0x1
#define HWIO_LPASS_AUDIO_CORE_ATIMER_CORE_CGCR_CLK_ENABLE_SHFT                                                 0x0

#define HWIO_LPASS_AUDIO_CORE_ATIMER_CORE_HYSTERESIS_ADDR                                               (LPASS_CSR_REG_BASE      + 0x00015004)
#define HWIO_LPASS_AUDIO_CORE_ATIMER_CORE_HYSTERESIS_OFFS                                               (LPASS_CSR_REG_BASE_OFFS + 0x00015004)
#define HWIO_LPASS_AUDIO_CORE_ATIMER_CORE_HYSTERESIS_RMSK                                                      0x7
#define HWIO_LPASS_AUDIO_CORE_ATIMER_CORE_HYSTERESIS_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_ATIMER_CORE_HYSTERESIS_ADDR, HWIO_LPASS_AUDIO_CORE_ATIMER_CORE_HYSTERESIS_RMSK)
#define HWIO_LPASS_AUDIO_CORE_ATIMER_CORE_HYSTERESIS_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_ATIMER_CORE_HYSTERESIS_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_ATIMER_CORE_HYSTERESIS_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_ATIMER_CORE_HYSTERESIS_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_ATIMER_CORE_HYSTERESIS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_ATIMER_CORE_HYSTERESIS_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_ATIMER_CORE_HYSTERESIS_IN)
#define HWIO_LPASS_AUDIO_CORE_ATIMER_CORE_HYSTERESIS_ACTIVE_HYSTSEL_BMSK                                       0x7
#define HWIO_LPASS_AUDIO_CORE_ATIMER_CORE_HYSTERESIS_ACTIVE_HYSTSEL_SHFT                                       0x0

#define HWIO_LPASS_AUDIO_CORE_DML_CORE_CGCR_ADDR                                                        (LPASS_CSR_REG_BASE      + 0x00016000)
#define HWIO_LPASS_AUDIO_CORE_DML_CORE_CGCR_OFFS                                                        (LPASS_CSR_REG_BASE_OFFS + 0x00016000)
#define HWIO_LPASS_AUDIO_CORE_DML_CORE_CGCR_RMSK                                                               0x3
#define HWIO_LPASS_AUDIO_CORE_DML_CORE_CGCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_DML_CORE_CGCR_ADDR, HWIO_LPASS_AUDIO_CORE_DML_CORE_CGCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_DML_CORE_CGCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_DML_CORE_CGCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_DML_CORE_CGCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_DML_CORE_CGCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_DML_CORE_CGCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_DML_CORE_CGCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_DML_CORE_CGCR_IN)
#define HWIO_LPASS_AUDIO_CORE_DML_CORE_CGCR_HW_CTL_BMSK                                                        0x2
#define HWIO_LPASS_AUDIO_CORE_DML_CORE_CGCR_HW_CTL_SHFT                                                        0x1
#define HWIO_LPASS_AUDIO_CORE_DML_CORE_CGCR_CLK_ENABLE_BMSK                                                    0x1
#define HWIO_LPASS_AUDIO_CORE_DML_CORE_CGCR_CLK_ENABLE_SHFT                                                    0x0

#define HWIO_LPASS_AUDIO_CORE_DML_CORE_HYSTERESIS_ADDR                                                  (LPASS_CSR_REG_BASE      + 0x00016004)
#define HWIO_LPASS_AUDIO_CORE_DML_CORE_HYSTERESIS_OFFS                                                  (LPASS_CSR_REG_BASE_OFFS + 0x00016004)
#define HWIO_LPASS_AUDIO_CORE_DML_CORE_HYSTERESIS_RMSK                                                         0x7
#define HWIO_LPASS_AUDIO_CORE_DML_CORE_HYSTERESIS_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_DML_CORE_HYSTERESIS_ADDR, HWIO_LPASS_AUDIO_CORE_DML_CORE_HYSTERESIS_RMSK)
#define HWIO_LPASS_AUDIO_CORE_DML_CORE_HYSTERESIS_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_DML_CORE_HYSTERESIS_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_DML_CORE_HYSTERESIS_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_DML_CORE_HYSTERESIS_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_DML_CORE_HYSTERESIS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_DML_CORE_HYSTERESIS_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_DML_CORE_HYSTERESIS_IN)
#define HWIO_LPASS_AUDIO_CORE_DML_CORE_HYSTERESIS_ACTIVE_HYSTSEL_BMSK                                          0x7
#define HWIO_LPASS_AUDIO_CORE_DML_CORE_HYSTERESIS_ACTIVE_HYSTSEL_SHFT                                          0x0

#define HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_CORE_CGCR_ADDR                                                (LPASS_CSR_REG_BASE      + 0x00017000)
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_CORE_CGCR_OFFS                                                (LPASS_CSR_REG_BASE_OFFS + 0x00017000)
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_CORE_CGCR_RMSK                                                       0x3
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_CORE_CGCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_CORE_CGCR_ADDR, HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_CORE_CGCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_CORE_CGCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_CORE_CGCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_CORE_CGCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_CORE_CGCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_CORE_CGCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_CORE_CGCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_CORE_CGCR_IN)
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_CORE_CGCR_HW_CTL_BMSK                                                0x2
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_CORE_CGCR_HW_CTL_SHFT                                                0x1
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_CORE_CGCR_CLK_ENABLE_BMSK                                            0x1
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_CORE_CGCR_CLK_ENABLE_SHFT                                            0x0

#define HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_CORE_HYSTERESIS_ADDR                                          (LPASS_CSR_REG_BASE      + 0x00017004)
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_CORE_HYSTERESIS_OFFS                                          (LPASS_CSR_REG_BASE_OFFS + 0x00017004)
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_CORE_HYSTERESIS_RMSK                                                 0x7
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_CORE_HYSTERESIS_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_CORE_HYSTERESIS_ADDR, HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_CORE_HYSTERESIS_RMSK)
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_CORE_HYSTERESIS_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_CORE_HYSTERESIS_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_CORE_HYSTERESIS_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_CORE_HYSTERESIS_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_CORE_HYSTERESIS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_CORE_HYSTERESIS_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_CORE_HYSTERESIS_IN)
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_CORE_HYSTERESIS_ACTIVE_HYSTSEL_BMSK                                  0x7
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_CORE_HYSTERESIS_ACTIVE_HYSTSEL_SHFT                                  0x0

#define HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_CORE_CGCR_ADDR                                                  (LPASS_CSR_REG_BASE      + 0x00018000)
#define HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_CORE_CGCR_OFFS                                                  (LPASS_CSR_REG_BASE_OFFS + 0x00018000)
#define HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_CORE_CGCR_RMSK                                                         0x3
#define HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_CORE_CGCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_CORE_CGCR_ADDR, HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_CORE_CGCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_CORE_CGCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_CORE_CGCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_CORE_CGCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_CORE_CGCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_CORE_CGCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_CORE_CGCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_CORE_CGCR_IN)
#define HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_CORE_CGCR_HW_CTL_BMSK                                                  0x2
#define HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_CORE_CGCR_HW_CTL_SHFT                                                  0x1
#define HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_CORE_CGCR_CLK_ENABLE_BMSK                                              0x1
#define HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_CORE_CGCR_CLK_ENABLE_SHFT                                              0x0

#define HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_CORE_HYSTERESIS_ADDR                                            (LPASS_CSR_REG_BASE      + 0x00018004)
#define HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_CORE_HYSTERESIS_OFFS                                            (LPASS_CSR_REG_BASE_OFFS + 0x00018004)
#define HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_CORE_HYSTERESIS_RMSK                                                   0x7
#define HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_CORE_HYSTERESIS_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_CORE_HYSTERESIS_ADDR, HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_CORE_HYSTERESIS_RMSK)
#define HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_CORE_HYSTERESIS_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_CORE_HYSTERESIS_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_CORE_HYSTERESIS_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_CORE_HYSTERESIS_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_CORE_HYSTERESIS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_CORE_HYSTERESIS_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_CORE_HYSTERESIS_IN)
#define HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_CORE_HYSTERESIS_ACTIVE_HYSTSEL_BMSK                                    0x7
#define HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_CORE_HYSTERESIS_ACTIVE_HYSTSEL_SHFT                                    0x0

#define HWIO_LPASS_AUDIO_CORE_SPDIFTX_CORE_CGCR_ADDR                                                    (LPASS_CSR_REG_BASE      + 0x00019000)
#define HWIO_LPASS_AUDIO_CORE_SPDIFTX_CORE_CGCR_OFFS                                                    (LPASS_CSR_REG_BASE_OFFS + 0x00019000)
#define HWIO_LPASS_AUDIO_CORE_SPDIFTX_CORE_CGCR_RMSK                                                           0x3
#define HWIO_LPASS_AUDIO_CORE_SPDIFTX_CORE_CGCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_SPDIFTX_CORE_CGCR_ADDR, HWIO_LPASS_AUDIO_CORE_SPDIFTX_CORE_CGCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_SPDIFTX_CORE_CGCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_SPDIFTX_CORE_CGCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_SPDIFTX_CORE_CGCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_SPDIFTX_CORE_CGCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_SPDIFTX_CORE_CGCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_SPDIFTX_CORE_CGCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_SPDIFTX_CORE_CGCR_IN)
#define HWIO_LPASS_AUDIO_CORE_SPDIFTX_CORE_CGCR_HW_CTL_BMSK                                                    0x2
#define HWIO_LPASS_AUDIO_CORE_SPDIFTX_CORE_CGCR_HW_CTL_SHFT                                                    0x1
#define HWIO_LPASS_AUDIO_CORE_SPDIFTX_CORE_CGCR_CLK_ENABLE_BMSK                                                0x1
#define HWIO_LPASS_AUDIO_CORE_SPDIFTX_CORE_CGCR_CLK_ENABLE_SHFT                                                0x0

#define HWIO_LPASS_AUDIO_CORE_SPDIFTX_CORE_HYSTERESIS_ADDR                                              (LPASS_CSR_REG_BASE      + 0x00019004)
#define HWIO_LPASS_AUDIO_CORE_SPDIFTX_CORE_HYSTERESIS_OFFS                                              (LPASS_CSR_REG_BASE_OFFS + 0x00019004)
#define HWIO_LPASS_AUDIO_CORE_SPDIFTX_CORE_HYSTERESIS_RMSK                                                     0x7
#define HWIO_LPASS_AUDIO_CORE_SPDIFTX_CORE_HYSTERESIS_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_SPDIFTX_CORE_HYSTERESIS_ADDR, HWIO_LPASS_AUDIO_CORE_SPDIFTX_CORE_HYSTERESIS_RMSK)
#define HWIO_LPASS_AUDIO_CORE_SPDIFTX_CORE_HYSTERESIS_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_SPDIFTX_CORE_HYSTERESIS_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_SPDIFTX_CORE_HYSTERESIS_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_SPDIFTX_CORE_HYSTERESIS_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_SPDIFTX_CORE_HYSTERESIS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_SPDIFTX_CORE_HYSTERESIS_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_SPDIFTX_CORE_HYSTERESIS_IN)
#define HWIO_LPASS_AUDIO_CORE_SPDIFTX_CORE_HYSTERESIS_ACTIVE_HYSTSEL_BMSK                                      0x7
#define HWIO_LPASS_AUDIO_CORE_SPDIFTX_CORE_HYSTERESIS_ACTIVE_HYSTSEL_SHFT                                      0x0

#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_CGCR_ADDR                                                (LPASS_CSR_REG_BASE      + 0x0001a000)
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_CGCR_OFFS                                                (LPASS_CSR_REG_BASE_OFFS + 0x0001a000)
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_CGCR_RMSK                                                       0x3
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_CGCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_CGCR_ADDR, HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_CGCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_CGCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_CGCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_CGCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_CGCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_CGCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_CGCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_CGCR_IN)
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_CGCR_HW_CTL_BMSK                                                0x2
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_CGCR_HW_CTL_SHFT                                                0x1
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_CGCR_CLK_ENABLE_BMSK                                            0x1
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_CGCR_CLK_ENABLE_SHFT                                            0x0

#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_HYSTERESIS_ADDR                                          (LPASS_CSR_REG_BASE      + 0x0001a004)
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_HYSTERESIS_OFFS                                          (LPASS_CSR_REG_BASE_OFFS + 0x0001a004)
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_HYSTERESIS_RMSK                                                 0x7
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_HYSTERESIS_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_HYSTERESIS_ADDR, HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_HYSTERESIS_RMSK)
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_HYSTERESIS_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_HYSTERESIS_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_HYSTERESIS_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_HYSTERESIS_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_HYSTERESIS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_HYSTERESIS_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_HYSTERESIS_IN)
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_HYSTERESIS_ACTIVE_HYSTSEL_BMSK                                  0x7
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_HYSTERESIS_ACTIVE_HYSTSEL_SHFT                                  0x0

#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_TIMEBASE_CTL_ADDR                                             (LPASS_CSR_REG_BASE      + 0x0001a008)
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_TIMEBASE_CTL_OFFS                                             (LPASS_CSR_REG_BASE_OFFS + 0x0001a008)
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_TIMEBASE_CTL_RMSK                                                    0x1
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_TIMEBASE_CTL_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_TIMEBASE_CTL_ADDR, HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_TIMEBASE_CTL_RMSK)
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_TIMEBASE_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_TIMEBASE_CTL_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_TIMEBASE_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_TIMEBASE_CTL_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_TIMEBASE_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_TIMEBASE_CTL_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_TIMEBASE_CTL_IN)
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_TIMEBASE_CTL_TIMEBASE_EN_BMSK                                        0x1
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_TIMEBASE_CTL_TIMEBASE_EN_SHFT                                        0x0

#define HWIO_LPASS_AUDIO_CORE_QOS_CTL_ADDR                                                              (LPASS_CSR_REG_BASE      + 0x0001b000)
#define HWIO_LPASS_AUDIO_CORE_QOS_CTL_OFFS                                                              (LPASS_CSR_REG_BASE_OFFS + 0x0001b000)
#define HWIO_LPASS_AUDIO_CORE_QOS_CTL_RMSK                                                                     0x1
#define HWIO_LPASS_AUDIO_CORE_QOS_CTL_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_QOS_CTL_ADDR, HWIO_LPASS_AUDIO_CORE_QOS_CTL_RMSK)
#define HWIO_LPASS_AUDIO_CORE_QOS_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_QOS_CTL_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_QOS_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_QOS_CTL_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_QOS_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_QOS_CTL_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_QOS_CTL_IN)
#define HWIO_LPASS_AUDIO_CORE_QOS_CTL_QOS_ENABLE_BMSK                                                          0x1
#define HWIO_LPASS_AUDIO_CORE_QOS_CTL_QOS_ENABLE_SHFT                                                          0x0

#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_AHBL_CORE_CGCR_ADDR                                           (LPASS_CSR_REG_BASE      + 0x0001c000)
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_AHBL_CORE_CGCR_OFFS                                           (LPASS_CSR_REG_BASE_OFFS + 0x0001c000)
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_AHBL_CORE_CGCR_RMSK                                                  0x3
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_AHBL_CORE_CGCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_AHBL_CORE_CGCR_ADDR, HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_AHBL_CORE_CGCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_AHBL_CORE_CGCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_AHBL_CORE_CGCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_AHBL_CORE_CGCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_AHBL_CORE_CGCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_AHBL_CORE_CGCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_AHBL_CORE_CGCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_AHBL_CORE_CGCR_IN)
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_AHBL_CORE_CGCR_HW_CTL_BMSK                                           0x2
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_AHBL_CORE_CGCR_HW_CTL_SHFT                                           0x1
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_AHBL_CORE_CGCR_CLK_ENABLE_BMSK                                       0x1
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_AHBL_CORE_CGCR_CLK_ENABLE_SHFT                                       0x0

#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_AHBL_CORE_HYSTERESIS_ADDR                                     (LPASS_CSR_REG_BASE      + 0x0001c004)
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_AHBL_CORE_HYSTERESIS_OFFS                                     (LPASS_CSR_REG_BASE_OFFS + 0x0001c004)
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_AHBL_CORE_HYSTERESIS_RMSK                                            0x7
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_AHBL_CORE_HYSTERESIS_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_AHBL_CORE_HYSTERESIS_ADDR, HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_AHBL_CORE_HYSTERESIS_RMSK)
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_AHBL_CORE_HYSTERESIS_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_AHBL_CORE_HYSTERESIS_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_AHBL_CORE_HYSTERESIS_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_AHBL_CORE_HYSTERESIS_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_AHBL_CORE_HYSTERESIS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_AHBL_CORE_HYSTERESIS_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_AHBL_CORE_HYSTERESIS_IN)
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_AHBL_CORE_HYSTERESIS_ACTIVE_HYSTSEL_BMSK                             0x7
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_AHBL_CORE_HYSTERESIS_ACTIVE_HYSTSEL_SHFT                             0x0

#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_AHBL_TIMEBASE_CTL_ADDR                                        (LPASS_CSR_REG_BASE      + 0x0001c008)
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_AHBL_TIMEBASE_CTL_OFFS                                        (LPASS_CSR_REG_BASE_OFFS + 0x0001c008)
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_AHBL_TIMEBASE_CTL_RMSK                                               0x1
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_AHBL_TIMEBASE_CTL_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_AHBL_TIMEBASE_CTL_ADDR, HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_AHBL_TIMEBASE_CTL_RMSK)
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_AHBL_TIMEBASE_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_AHBL_TIMEBASE_CTL_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_AHBL_TIMEBASE_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_AHBL_TIMEBASE_CTL_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_AHBL_TIMEBASE_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_AHBL_TIMEBASE_CTL_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_AHBL_TIMEBASE_CTL_IN)
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_AHBL_TIMEBASE_CTL_TIMEBASE_EN_BMSK                                   0x1
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_AHBL_TIMEBASE_CTL_TIMEBASE_EN_SHFT                                   0x0

#define HWIO_LPASS_AUDIO_CORE_AUDIO_CODEC_CGCR_ADDR                                                     (LPASS_CSR_REG_BASE      + 0x0001d000)
#define HWIO_LPASS_AUDIO_CORE_AUDIO_CODEC_CGCR_OFFS                                                     (LPASS_CSR_REG_BASE_OFFS + 0x0001d000)
#define HWIO_LPASS_AUDIO_CORE_AUDIO_CODEC_CGCR_RMSK                                                            0x3
#define HWIO_LPASS_AUDIO_CORE_AUDIO_CODEC_CGCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_AUDIO_CODEC_CGCR_ADDR, HWIO_LPASS_AUDIO_CORE_AUDIO_CODEC_CGCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_AUDIO_CODEC_CGCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_AUDIO_CODEC_CGCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_AUDIO_CODEC_CGCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_AUDIO_CODEC_CGCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_AUDIO_CODEC_CGCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_AUDIO_CODEC_CGCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_AUDIO_CODEC_CGCR_IN)
#define HWIO_LPASS_AUDIO_CORE_AUDIO_CODEC_CGCR_HW_CTL_BMSK                                                     0x2
#define HWIO_LPASS_AUDIO_CORE_AUDIO_CODEC_CGCR_HW_CTL_SHFT                                                     0x1
#define HWIO_LPASS_AUDIO_CORE_AUDIO_CODEC_CGCR_CLK_ENABLE_BMSK                                                 0x1
#define HWIO_LPASS_AUDIO_CORE_AUDIO_CODEC_CGCR_CLK_ENABLE_SHFT                                                 0x0

#define HWIO_LPASS_AUDIO_CORE_AUDIO_CODEC_HYSTERESIS_ADDR                                               (LPASS_CSR_REG_BASE      + 0x0001d004)
#define HWIO_LPASS_AUDIO_CORE_AUDIO_CODEC_HYSTERESIS_OFFS                                               (LPASS_CSR_REG_BASE_OFFS + 0x0001d004)
#define HWIO_LPASS_AUDIO_CORE_AUDIO_CODEC_HYSTERESIS_RMSK                                                      0x7
#define HWIO_LPASS_AUDIO_CORE_AUDIO_CODEC_HYSTERESIS_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_AUDIO_CODEC_HYSTERESIS_ADDR, HWIO_LPASS_AUDIO_CORE_AUDIO_CODEC_HYSTERESIS_RMSK)
#define HWIO_LPASS_AUDIO_CORE_AUDIO_CODEC_HYSTERESIS_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_AUDIO_CODEC_HYSTERESIS_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_AUDIO_CODEC_HYSTERESIS_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_AUDIO_CODEC_HYSTERESIS_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_AUDIO_CODEC_HYSTERESIS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_AUDIO_CODEC_HYSTERESIS_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_AUDIO_CODEC_HYSTERESIS_IN)
#define HWIO_LPASS_AUDIO_CORE_AUDIO_CODEC_HYSTERESIS_ACTIVE_HYSTSEL_BMSK                                       0x7
#define HWIO_LPASS_AUDIO_CORE_AUDIO_CODEC_HYSTERESIS_ACTIVE_HYSTSEL_SHFT                                       0x0

#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_MUX_SPKR_CTL_ADDR                                               (LPASS_CSR_REG_BASE      + 0x0001d008)
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_MUX_SPKR_CTL_OFFS                                               (LPASS_CSR_REG_BASE_OFFS + 0x0001d008)
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_MUX_SPKR_CTL_RMSK                                                    0x3ff
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_MUX_SPKR_CTL_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_DCODEC_GP_MUX_SPKR_CTL_ADDR, HWIO_LPASS_AUDIO_CORE_DCODEC_GP_MUX_SPKR_CTL_RMSK)
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_MUX_SPKR_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_DCODEC_GP_MUX_SPKR_CTL_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_MUX_SPKR_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_DCODEC_GP_MUX_SPKR_CTL_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_MUX_SPKR_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_DCODEC_GP_MUX_SPKR_CTL_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_DCODEC_GP_MUX_SPKR_CTL_IN)
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_MUX_SPKR_CTL_LPAIF_NPL_BYP_EN_BMSK                                   0x200
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_MUX_SPKR_CTL_LPAIF_NPL_BYP_EN_SHFT                                     0x9
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_MUX_SPKR_CTL_LPAIF_I2S0_MST_SLV_CLK_SEL_BMSK                         0x100
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_MUX_SPKR_CTL_LPAIF_I2S0_MST_SLV_CLK_SEL_SHFT                           0x8
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_MUX_SPKR_CTL_DIG_CODEC_INT_CLOCK_OBS_EN_BMSK                          0x80
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_MUX_SPKR_CTL_DIG_CODEC_INT_CLOCK_OBS_EN_SHFT                           0x7
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_MUX_SPKR_CTL_TLMM_TEST_SD1_OUT_OE_BMSK                                0x40
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_MUX_SPKR_CTL_TLMM_TEST_SD1_OUT_OE_SHFT                                 0x6
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_MUX_SPKR_CTL_TLMM_TEST_SD0_OUT_OE_BMSK                                0x20
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_MUX_SPKR_CTL_TLMM_TEST_SD0_OUT_OE_SHFT                                 0x5
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_MUX_SPKR_CTL_LPAIF_I2S1_WS_IN_SEL_BMSK                                0x10
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_MUX_SPKR_CTL_LPAIF_I2S1_WS_IN_SEL_SHFT                                 0x4
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_MUX_SPKR_CTL_DIGITAL_CLOCK_SD1_IN_SEL_BMSK                             0x8
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_MUX_SPKR_CTL_DIGITAL_CLOCK_SD1_IN_SEL_SHFT                             0x3
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_MUX_SPKR_CTL_DIGITAL_CODEC_RX0_RX1_WS_IN_SEL_BMSK                      0x4
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_MUX_SPKR_CTL_DIGITAL_CODEC_RX0_RX1_WS_IN_SEL_SHFT                      0x2
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_MUX_SPKR_CTL_LPAIF_I2S0_WS_IN_SEL_BMSK                                 0x2
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_MUX_SPKR_CTL_LPAIF_I2S0_WS_IN_SEL_SHFT                                 0x1
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_MUX_SPKR_CTL_LPAIF_I2S0_SCLK_SEL_BMSK                                  0x1
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_MUX_SPKR_CTL_LPAIF_I2S0_SCLK_SEL_SHFT                                  0x0

#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_MUX_MIC_CTL_ADDR                                                (LPASS_CSR_REG_BASE      + 0x0001d00c)
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_MUX_MIC_CTL_OFFS                                                (LPASS_CSR_REG_BASE_OFFS + 0x0001d00c)
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_MUX_MIC_CTL_RMSK                                                     0x1ff
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_MUX_MIC_CTL_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_DCODEC_GP_MUX_MIC_CTL_ADDR, HWIO_LPASS_AUDIO_CORE_DCODEC_GP_MUX_MIC_CTL_RMSK)
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_MUX_MIC_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_DCODEC_GP_MUX_MIC_CTL_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_MUX_MIC_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_DCODEC_GP_MUX_MIC_CTL_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_MUX_MIC_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_DCODEC_GP_MUX_MIC_CTL_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_DCODEC_GP_MUX_MIC_CTL_IN)
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_MUX_MIC_CTL_LPAIF_NPL_BYP_EN_BMSK                                    0x100
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_MUX_MIC_CTL_LPAIF_NPL_BYP_EN_SHFT                                      0x8
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_MUX_MIC_CTL_LPAIF_I2S2_MST_SLV_CLK_SEL_BMSK                           0x80
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_MUX_MIC_CTL_LPAIF_I2S2_MST_SLV_CLK_SEL_SHFT                            0x7
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_MUX_MIC_CTL_LPAIF_I2S3_MST_SLV_CLK_SEL_BMSK                           0x40
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_MUX_MIC_CTL_LPAIF_I2S3_MST_SLV_CLK_SEL_SHFT                            0x6
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_MUX_MIC_CTL_DIG_CODEC_INT_CLOCK_TX2_OBS_EN_BMSK                       0x20
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_MUX_MIC_CTL_DIG_CODEC_INT_CLOCK_TX2_OBS_EN_SHFT                        0x5
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_MUX_MIC_CTL_DIG_CODEC_INT_CLOCK_TX_OBS_EN_BMSK                        0x10
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_MUX_MIC_CTL_DIG_CODEC_INT_CLOCK_TX_OBS_EN_SHFT                         0x4
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_MUX_MIC_CTL_TLMM_TEST_SD1_OUT_OE_BMSK                                  0x8
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_MUX_MIC_CTL_TLMM_TEST_SD1_OUT_OE_SHFT                                  0x3
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_MUX_MIC_CTL_TLMM_TEST_SD0_OUT_OE_BMSK                                  0x4
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_MUX_MIC_CTL_TLMM_TEST_SD0_OUT_OE_SHFT                                  0x2
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_MUX_MIC_CTL_LPAIF_I2S2_SCLK_SEL_BMSK                                   0x2
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_MUX_MIC_CTL_LPAIF_I2S2_SCLK_SEL_SHFT                                   0x1
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_MUX_MIC_CTL_LPAIF_I2S3_SCLK_SEL_BMSK                                   0x1
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_MUX_MIC_CTL_LPAIF_I2S3_SCLK_SEL_SHFT                                   0x0

#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_I2S0_TEST_ADDR                                                  (LPASS_CSR_REG_BASE      + 0x0001d010)
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_I2S0_TEST_OFFS                                                  (LPASS_CSR_REG_BASE_OFFS + 0x0001d010)
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_I2S0_TEST_RMSK                                                         0x1
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_I2S0_TEST_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_DCODEC_GP_I2S0_TEST_ADDR, HWIO_LPASS_AUDIO_CORE_DCODEC_GP_I2S0_TEST_RMSK)
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_I2S0_TEST_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_DCODEC_GP_I2S0_TEST_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_I2S0_TEST_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_DCODEC_GP_I2S0_TEST_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_I2S0_TEST_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_DCODEC_GP_I2S0_TEST_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_DCODEC_GP_I2S0_TEST_IN)
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_I2S0_TEST_ENABLE_BMSK                                                  0x1
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_I2S0_TEST_ENABLE_SHFT                                                  0x0

#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_I2S1_TEST_ADDR                                                  (LPASS_CSR_REG_BASE      + 0x0001d014)
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_I2S1_TEST_OFFS                                                  (LPASS_CSR_REG_BASE_OFFS + 0x0001d014)
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_I2S1_TEST_RMSK                                                         0x1
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_I2S1_TEST_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_DCODEC_GP_I2S1_TEST_ADDR, HWIO_LPASS_AUDIO_CORE_DCODEC_GP_I2S1_TEST_RMSK)
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_I2S1_TEST_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_DCODEC_GP_I2S1_TEST_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_I2S1_TEST_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_DCODEC_GP_I2S1_TEST_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_I2S1_TEST_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_DCODEC_GP_I2S1_TEST_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_DCODEC_GP_I2S1_TEST_IN)
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_I2S1_TEST_ENABLE_BMSK                                                  0x1
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_I2S1_TEST_ENABLE_SHFT                                                  0x0

#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_RX0_1_TEST_ADDR                                                 (LPASS_CSR_REG_BASE      + 0x0001d018)
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_RX0_1_TEST_OFFS                                                 (LPASS_CSR_REG_BASE_OFFS + 0x0001d018)
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_RX0_1_TEST_RMSK                                                        0x1
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_RX0_1_TEST_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_DCODEC_GP_RX0_1_TEST_ADDR, HWIO_LPASS_AUDIO_CORE_DCODEC_GP_RX0_1_TEST_RMSK)
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_RX0_1_TEST_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_DCODEC_GP_RX0_1_TEST_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_RX0_1_TEST_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_DCODEC_GP_RX0_1_TEST_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_RX0_1_TEST_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_DCODEC_GP_RX0_1_TEST_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_DCODEC_GP_RX0_1_TEST_IN)
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_RX0_1_TEST_ENABLE_BMSK                                                 0x1
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_RX0_1_TEST_ENABLE_SHFT                                                 0x0

#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_I2S2_TEST_ADDR                                                  (LPASS_CSR_REG_BASE      + 0x0001d01c)
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_I2S2_TEST_OFFS                                                  (LPASS_CSR_REG_BASE_OFFS + 0x0001d01c)
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_I2S2_TEST_RMSK                                                         0x1
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_I2S2_TEST_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_DCODEC_GP_I2S2_TEST_ADDR, HWIO_LPASS_AUDIO_CORE_DCODEC_GP_I2S2_TEST_RMSK)
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_I2S2_TEST_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_DCODEC_GP_I2S2_TEST_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_I2S2_TEST_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_DCODEC_GP_I2S2_TEST_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_I2S2_TEST_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_DCODEC_GP_I2S2_TEST_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_DCODEC_GP_I2S2_TEST_IN)
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_I2S2_TEST_ENABLE_BMSK                                                  0x1
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_I2S2_TEST_ENABLE_SHFT                                                  0x0

#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_I2S3_TEST_ADDR                                                  (LPASS_CSR_REG_BASE      + 0x0001d020)
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_I2S3_TEST_OFFS                                                  (LPASS_CSR_REG_BASE_OFFS + 0x0001d020)
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_I2S3_TEST_RMSK                                                         0x1
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_I2S3_TEST_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_DCODEC_GP_I2S3_TEST_ADDR, HWIO_LPASS_AUDIO_CORE_DCODEC_GP_I2S3_TEST_RMSK)
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_I2S3_TEST_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_DCODEC_GP_I2S3_TEST_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_I2S3_TEST_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_DCODEC_GP_I2S3_TEST_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_I2S3_TEST_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_DCODEC_GP_I2S3_TEST_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_DCODEC_GP_I2S3_TEST_IN)
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_I2S3_TEST_ENABLE_BMSK                                                  0x1
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_I2S3_TEST_ENABLE_SHFT                                                  0x0

#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_TX0_1_TEST_ADDR                                                 (LPASS_CSR_REG_BASE      + 0x0001d024)
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_TX0_1_TEST_OFFS                                                 (LPASS_CSR_REG_BASE_OFFS + 0x0001d024)
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_TX0_1_TEST_RMSK                                                        0x1
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_TX0_1_TEST_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_DCODEC_GP_TX0_1_TEST_ADDR, HWIO_LPASS_AUDIO_CORE_DCODEC_GP_TX0_1_TEST_RMSK)
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_TX0_1_TEST_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_DCODEC_GP_TX0_1_TEST_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_TX0_1_TEST_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_DCODEC_GP_TX0_1_TEST_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_TX0_1_TEST_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_DCODEC_GP_TX0_1_TEST_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_DCODEC_GP_TX0_1_TEST_IN)
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_TX0_1_TEST_ENABLE_BMSK                                                 0x1
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_TX0_1_TEST_ENABLE_SHFT                                                 0x0

#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_TX2_TEST_ADDR                                                   (LPASS_CSR_REG_BASE      + 0x0001d028)
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_TX2_TEST_OFFS                                                   (LPASS_CSR_REG_BASE_OFFS + 0x0001d028)
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_TX2_TEST_RMSK                                                          0x1
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_TX2_TEST_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_DCODEC_GP_TX2_TEST_ADDR, HWIO_LPASS_AUDIO_CORE_DCODEC_GP_TX2_TEST_RMSK)
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_TX2_TEST_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_DCODEC_GP_TX2_TEST_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_TX2_TEST_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_DCODEC_GP_TX2_TEST_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_TX2_TEST_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_DCODEC_GP_TX2_TEST_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_DCODEC_GP_TX2_TEST_IN)
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_TX2_TEST_ENABLE_BMSK                                                   0x1
#define HWIO_LPASS_AUDIO_CORE_DCODEC_GP_TX2_TEST_ENABLE_SHFT                                                   0x0

#define HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_CGCR_ADDR                                                       (LPASS_CSR_REG_BASE      + 0x0001e000)
#define HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_CGCR_OFFS                                                       (LPASS_CSR_REG_BASE_OFFS + 0x0001e000)
#define HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_CGCR_RMSK                                                              0x3
#define HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_CGCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_CGCR_ADDR, HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_CGCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_CGCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_CGCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_CGCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_CGCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_CGCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_CGCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_CGCR_IN)
#define HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_CGCR_HW_CTL_BMSK                                                       0x2
#define HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_CGCR_HW_CTL_SHFT                                                       0x1
#define HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_CGCR_CLK_ENABLE_BMSK                                                   0x1
#define HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_CGCR_CLK_ENABLE_SHFT                                                   0x0

#define HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_HYSTERESIS_ADDR                                                 (LPASS_CSR_REG_BASE      + 0x0001e004)
#define HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_HYSTERESIS_OFFS                                                 (LPASS_CSR_REG_BASE_OFFS + 0x0001e004)
#define HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_HYSTERESIS_RMSK                                                        0x7
#define HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_HYSTERESIS_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_HYSTERESIS_ADDR, HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_HYSTERESIS_RMSK)
#define HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_HYSTERESIS_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_HYSTERESIS_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_HYSTERESIS_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_HYSTERESIS_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_HYSTERESIS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_HYSTERESIS_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_HYSTERESIS_IN)
#define HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_HYSTERESIS_ACTIVE_HYSTSEL_BMSK                                         0x7
#define HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_HYSTERESIS_ACTIVE_HYSTSEL_SHFT                                         0x0

#define HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_GP_SPKR_MIC_MUX_CTL_ADDR                                        (LPASS_CSR_REG_BASE      + 0x0001e008)
#define HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_GP_SPKR_MIC_MUX_CTL_OFFS                                        (LPASS_CSR_REG_BASE_OFFS + 0x0001e008)
#define HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_GP_SPKR_MIC_MUX_CTL_RMSK                                            0x7fff
#define HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_GP_SPKR_MIC_MUX_CTL_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_GP_SPKR_MIC_MUX_CTL_ADDR, HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_GP_SPKR_MIC_MUX_CTL_RMSK)
#define HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_GP_SPKR_MIC_MUX_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_GP_SPKR_MIC_MUX_CTL_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_GP_SPKR_MIC_MUX_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_GP_SPKR_MIC_MUX_CTL_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_GP_SPKR_MIC_MUX_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_GP_SPKR_MIC_MUX_CTL_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_GP_SPKR_MIC_MUX_CTL_IN)
#define HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_GP_SPKR_MIC_MUX_CTL_LPAIF_NPL_BYP_EN_BMSK                           0x4000
#define HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_GP_SPKR_MIC_MUX_CTL_LPAIF_NPL_BYP_EN_SHFT                              0xe
#define HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_GP_SPKR_MIC_MUX_CTL_LPAIF_I2S5_MST_SLV_CLK_SEL_BMSK                 0x2000
#define HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_GP_SPKR_MIC_MUX_CTL_LPAIF_I2S5_MST_SLV_CLK_SEL_SHFT                    0xd
#define HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_GP_SPKR_MIC_MUX_CTL_LPAIF_I2S4_MST_SLV_CLK_SEL_BMSK                 0x1000
#define HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_GP_SPKR_MIC_MUX_CTL_LPAIF_I2S4_MST_SLV_CLK_SEL_SHFT                    0xc
#define HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_GP_SPKR_MIC_MUX_CTL_DIG_CODEC_INT_CLOCK_RX_OBS_EN_BMSK               0x800
#define HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_GP_SPKR_MIC_MUX_CTL_DIG_CODEC_INT_CLOCK_RX_OBS_EN_SHFT                 0xb
#define HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_GP_SPKR_MIC_MUX_CTL_DIG_CODEC_INT_CLOCK_TX_OBS_EN_BMSK               0x400
#define HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_GP_SPKR_MIC_MUX_CTL_DIG_CODEC_INT_CLOCK_TX_OBS_EN_SHFT                 0xa
#define HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_GP_SPKR_MIC_MUX_CTL_SLKC_OUT_RX_TX_SEL_BMSK                          0x200
#define HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_GP_SPKR_MIC_MUX_CTL_SLKC_OUT_RX_TX_SEL_SHFT                            0x9
#define HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_GP_SPKR_MIC_MUX_CTL_TLMM_TEST_SD1_OUT_OE_BMSK                        0x100
#define HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_GP_SPKR_MIC_MUX_CTL_TLMM_TEST_SD1_OUT_OE_SHFT                          0x8
#define HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_GP_SPKR_MIC_MUX_CTL_TLMM_TEST_SD0_OUT_OE_BMSK                         0x80
#define HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_GP_SPKR_MIC_MUX_CTL_TLMM_TEST_SD0_OUT_OE_SHFT                          0x7
#define HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_GP_SPKR_MIC_MUX_CTL_LPAIF_I2S6_WS_IN_SEL_BMSK                         0x40
#define HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_GP_SPKR_MIC_MUX_CTL_LPAIF_I2S6_WS_IN_SEL_SHFT                          0x6
#define HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_GP_SPKR_MIC_MUX_CTL_SWRM_TX_CLOCK_MASTER_SEL_BMSK                     0x20
#define HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_GP_SPKR_MIC_MUX_CTL_SWRM_TX_CLOCK_MASTER_SEL_SHFT                      0x5
#define HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_GP_SPKR_MIC_MUX_CTL_SWRM_TX_WS_IN_SEL_BMSK                            0x10
#define HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_GP_SPKR_MIC_MUX_CTL_SWRM_TX_WS_IN_SEL_SHFT                             0x4
#define HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_GP_SPKR_MIC_MUX_CTL_LPAIF_I2S5_WS_IN_SEL_BMSK                          0x8
#define HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_GP_SPKR_MIC_MUX_CTL_LPAIF_I2S5_WS_IN_SEL_SHFT                          0x3
#define HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_GP_SPKR_MIC_MUX_CTL_LPAIF_I2S5_SCLK_SEL_BMSK                           0x4
#define HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_GP_SPKR_MIC_MUX_CTL_LPAIF_I2S5_SCLK_SEL_SHFT                           0x2
#define HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_GP_SPKR_MIC_MUX_CTL_SWRM_RX_CLOCK_MASTER_SEL_BMSK                      0x2
#define HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_GP_SPKR_MIC_MUX_CTL_SWRM_RX_CLOCK_MASTER_SEL_SHFT                      0x1
#define HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_GP_SPKR_MIC_MUX_CTL_LPAIF_I2S4_SCLK_SEL_BMSK                           0x1
#define HWIO_LPASS_AUDIO_CORE_SOUNDWIRE_GP_SPKR_MIC_MUX_CTL_LPAIF_I2S4_SCLK_SEL_SHFT                           0x0

#define HWIO_LPASS_AUDIO_CORE_SWRM_GP_I2S4_TEST_ADDR                                                    (LPASS_CSR_REG_BASE      + 0x0001e00c)
#define HWIO_LPASS_AUDIO_CORE_SWRM_GP_I2S4_TEST_OFFS                                                    (LPASS_CSR_REG_BASE_OFFS + 0x0001e00c)
#define HWIO_LPASS_AUDIO_CORE_SWRM_GP_I2S4_TEST_RMSK                                                           0x1
#define HWIO_LPASS_AUDIO_CORE_SWRM_GP_I2S4_TEST_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_SWRM_GP_I2S4_TEST_ADDR, HWIO_LPASS_AUDIO_CORE_SWRM_GP_I2S4_TEST_RMSK)
#define HWIO_LPASS_AUDIO_CORE_SWRM_GP_I2S4_TEST_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_SWRM_GP_I2S4_TEST_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_SWRM_GP_I2S4_TEST_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_SWRM_GP_I2S4_TEST_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_SWRM_GP_I2S4_TEST_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_SWRM_GP_I2S4_TEST_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_SWRM_GP_I2S4_TEST_IN)
#define HWIO_LPASS_AUDIO_CORE_SWRM_GP_I2S4_TEST_ENABLE_BMSK                                                    0x1
#define HWIO_LPASS_AUDIO_CORE_SWRM_GP_I2S4_TEST_ENABLE_SHFT                                                    0x0

#define HWIO_LPASS_AUDIO_CORE_SWRM_GP_I2S5_TEST_ADDR                                                    (LPASS_CSR_REG_BASE      + 0x0001e010)
#define HWIO_LPASS_AUDIO_CORE_SWRM_GP_I2S5_TEST_OFFS                                                    (LPASS_CSR_REG_BASE_OFFS + 0x0001e010)
#define HWIO_LPASS_AUDIO_CORE_SWRM_GP_I2S5_TEST_RMSK                                                           0x1
#define HWIO_LPASS_AUDIO_CORE_SWRM_GP_I2S5_TEST_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_SWRM_GP_I2S5_TEST_ADDR, HWIO_LPASS_AUDIO_CORE_SWRM_GP_I2S5_TEST_RMSK)
#define HWIO_LPASS_AUDIO_CORE_SWRM_GP_I2S5_TEST_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_SWRM_GP_I2S5_TEST_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_SWRM_GP_I2S5_TEST_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_SWRM_GP_I2S5_TEST_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_SWRM_GP_I2S5_TEST_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_SWRM_GP_I2S5_TEST_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_SWRM_GP_I2S5_TEST_IN)
#define HWIO_LPASS_AUDIO_CORE_SWRM_GP_I2S5_TEST_ENABLE_BMSK                                                    0x1
#define HWIO_LPASS_AUDIO_CORE_SWRM_GP_I2S5_TEST_ENABLE_SHFT                                                    0x0

#define HWIO_LPASS_AUDIO_CORE_SWRM_GP_RX0_TEST_ADDR                                                     (LPASS_CSR_REG_BASE      + 0x0001e014)
#define HWIO_LPASS_AUDIO_CORE_SWRM_GP_RX0_TEST_OFFS                                                     (LPASS_CSR_REG_BASE_OFFS + 0x0001e014)
#define HWIO_LPASS_AUDIO_CORE_SWRM_GP_RX0_TEST_RMSK                                                            0x1
#define HWIO_LPASS_AUDIO_CORE_SWRM_GP_RX0_TEST_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_SWRM_GP_RX0_TEST_ADDR, HWIO_LPASS_AUDIO_CORE_SWRM_GP_RX0_TEST_RMSK)
#define HWIO_LPASS_AUDIO_CORE_SWRM_GP_RX0_TEST_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_SWRM_GP_RX0_TEST_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_SWRM_GP_RX0_TEST_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_SWRM_GP_RX0_TEST_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_SWRM_GP_RX0_TEST_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_SWRM_GP_RX0_TEST_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_SWRM_GP_RX0_TEST_IN)
#define HWIO_LPASS_AUDIO_CORE_SWRM_GP_RX0_TEST_ENABLE_BMSK                                                     0x1
#define HWIO_LPASS_AUDIO_CORE_SWRM_GP_RX0_TEST_ENABLE_SHFT                                                     0x0

#define HWIO_LPASS_AUDIO_CORE_SWRM_GP_I2S6_TEST_ADDR                                                    (LPASS_CSR_REG_BASE      + 0x0001e018)
#define HWIO_LPASS_AUDIO_CORE_SWRM_GP_I2S6_TEST_OFFS                                                    (LPASS_CSR_REG_BASE_OFFS + 0x0001e018)
#define HWIO_LPASS_AUDIO_CORE_SWRM_GP_I2S6_TEST_RMSK                                                           0x1
#define HWIO_LPASS_AUDIO_CORE_SWRM_GP_I2S6_TEST_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_SWRM_GP_I2S6_TEST_ADDR, HWIO_LPASS_AUDIO_CORE_SWRM_GP_I2S6_TEST_RMSK)
#define HWIO_LPASS_AUDIO_CORE_SWRM_GP_I2S6_TEST_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_SWRM_GP_I2S6_TEST_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_SWRM_GP_I2S6_TEST_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_SWRM_GP_I2S6_TEST_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_SWRM_GP_I2S6_TEST_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_SWRM_GP_I2S6_TEST_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_SWRM_GP_I2S6_TEST_IN)
#define HWIO_LPASS_AUDIO_CORE_SWRM_GP_I2S6_TEST_ENABLE_BMSK                                                    0x1
#define HWIO_LPASS_AUDIO_CORE_SWRM_GP_I2S6_TEST_ENABLE_SHFT                                                    0x0

#define HWIO_LPASS_AUDIO_CORE_SWRM_GP_TX0_1_TEST_ADDR                                                   (LPASS_CSR_REG_BASE      + 0x0001e01c)
#define HWIO_LPASS_AUDIO_CORE_SWRM_GP_TX0_1_TEST_OFFS                                                   (LPASS_CSR_REG_BASE_OFFS + 0x0001e01c)
#define HWIO_LPASS_AUDIO_CORE_SWRM_GP_TX0_1_TEST_RMSK                                                          0x1
#define HWIO_LPASS_AUDIO_CORE_SWRM_GP_TX0_1_TEST_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_SWRM_GP_TX0_1_TEST_ADDR, HWIO_LPASS_AUDIO_CORE_SWRM_GP_TX0_1_TEST_RMSK)
#define HWIO_LPASS_AUDIO_CORE_SWRM_GP_TX0_1_TEST_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_SWRM_GP_TX0_1_TEST_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_SWRM_GP_TX0_1_TEST_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_SWRM_GP_TX0_1_TEST_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_SWRM_GP_TX0_1_TEST_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_SWRM_GP_TX0_1_TEST_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_SWRM_GP_TX0_1_TEST_IN)
#define HWIO_LPASS_AUDIO_CORE_SWRM_GP_TX0_1_TEST_ENABLE_BMSK                                                   0x1
#define HWIO_LPASS_AUDIO_CORE_SWRM_GP_TX0_1_TEST_ENABLE_SHFT                                                   0x0

/*----------------------------------------------------------------------------
 * MODULE: LPASS_CC
 *--------------------------------------------------------------------------*/

#define LPASS_CC_REG_BASE                                                                                             (LPASS_BASE      + 0x00000000)
#define LPASS_CC_REG_BASE_OFFS                                                                                        0x00000000

#define HWIO_LPASS_LPAAUDIO_PLL_MODE_ADDR                                                                             (LPASS_CC_REG_BASE      + 0x00000000)
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_OFFS                                                                             (LPASS_CC_REG_BASE_OFFS + 0x00000000)
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_RMSK                                                                             0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_MODE_ADDR, HWIO_LPASS_LPAAUDIO_PLL_MODE_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_MODE_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_MODE_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_MODE_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_MODE_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_LOCK_DET_BMSK                                                                0x80000000
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_LOCK_DET_SHFT                                                                      0x1f
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_ACTIVE_FLAG_BMSK                                                             0x40000000
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_ACTIVE_FLAG_SHFT                                                                   0x1e
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_ACK_LATCH_BMSK                                                               0x20000000
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_ACK_LATCH_SHFT                                                                     0x1d
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_RESERVE_BITS28_24_BMSK                                                           0x1f000000
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_RESERVE_BITS28_24_SHFT                                                                 0x18
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_HW_UPDATE_LOGIC_BYPASS_BMSK                                                    0x800000
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_HW_UPDATE_LOGIC_BYPASS_SHFT                                                        0x17
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_UPDATE_BMSK                                                                    0x400000
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_UPDATE_SHFT                                                                        0x16
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_VOTE_FSM_RESET_BMSK                                                            0x200000
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_VOTE_FSM_RESET_SHFT                                                                0x15
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_VOTE_FSM_ENA_BMSK                                                              0x100000
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_VOTE_FSM_ENA_SHFT                                                                  0x14
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_BIAS_COUNT_BMSK                                                                 0xfc000
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_BIAS_COUNT_SHFT                                                                     0xe
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_LOCK_COUNT_BMSK                                                                  0x3f00
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_LOCK_COUNT_SHFT                                                                     0x8
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_RESERVE_BITS7_4_BMSK                                                                   0xf0
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_RESERVE_BITS7_4_SHFT                                                                    0x4
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_PLLTEST_BMSK                                                                        0x8
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_PLLTEST_SHFT                                                                        0x3
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_RESET_N_BMSK                                                                        0x4
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_RESET_N_SHFT                                                                        0x2
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_BYPASSNL_BMSK                                                                       0x2
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_BYPASSNL_SHFT                                                                       0x1
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_OUTCTRL_BMSK                                                                        0x1
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_OUTCTRL_SHFT                                                                        0x0

#define HWIO_LPASS_LPAAUDIO_PLL_L_VAL_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x00000004)
#define HWIO_LPASS_LPAAUDIO_PLL_L_VAL_OFFS                                                                            (LPASS_CC_REG_BASE_OFFS + 0x00000004)
#define HWIO_LPASS_LPAAUDIO_PLL_L_VAL_RMSK                                                                            0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_L_VAL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_L_VAL_ADDR, HWIO_LPASS_LPAAUDIO_PLL_L_VAL_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_L_VAL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_L_VAL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_L_VAL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_L_VAL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_L_VAL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_L_VAL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_L_VAL_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_L_VAL_RESERVE_BITS_31_8_BMSK                                                          0xffffff00
#define HWIO_LPASS_LPAAUDIO_PLL_L_VAL_RESERVE_BITS_31_8_SHFT                                                                 0x8
#define HWIO_LPASS_LPAAUDIO_PLL_L_VAL_PLL_L_BMSK                                                                            0xff
#define HWIO_LPASS_LPAAUDIO_PLL_L_VAL_PLL_L_SHFT                                                                             0x0

#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_ADDR                                                                        (LPASS_CC_REG_BASE      + 0x00000008)
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_OFFS                                                                        (LPASS_CC_REG_BASE_OFFS + 0x00000008)
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_RMSK                                                                        0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_ADDR, HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_PLL_ALPHA_31_0_BMSK                                                         0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_PLL_ALPHA_31_0_SHFT                                                                0x0

#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_U_ADDR                                                                      (LPASS_CC_REG_BASE      + 0x0000000c)
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_U_OFFS                                                                      (LPASS_CC_REG_BASE_OFFS + 0x0000000c)
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_U_RMSK                                                                      0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_U_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_U_ADDR, HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_U_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_U_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_U_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_U_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_U_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_U_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_U_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_U_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_U_RESERVE_BITS_31_8_BMSK                                                    0xffffff00
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_U_RESERVE_BITS_31_8_SHFT                                                           0x8
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_U_PLL_ALPHA_39_32_BMSK                                                            0xff
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_U_PLL_ALPHA_39_32_SHFT                                                             0x0

#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_ADDR                                                                         (LPASS_CC_REG_BASE      + 0x00000010)
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_OFFS                                                                         (LPASS_CC_REG_BASE_OFFS + 0x00000010)
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_RMSK                                                                         0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_ADDR, HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_RESERVE_BITS31_25_BMSK                                                       0xfe000000
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_RESERVE_BITS31_25_SHFT                                                             0x19
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_ALPHA_EN_BMSK                                                                 0x1000000
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_ALPHA_EN_SHFT                                                                      0x18
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_RESERVE_BITS23_14_BMSK                                                         0xffc000
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_RESERVE_BITS23_14_SHFT                                                              0xe
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_INCLK_SEL_BMSK                                                                   0x3000
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_INCLK_SEL_SHFT                                                                      0xc
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_RESERVE_BITS11_10_BMSK                                                            0xc00
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_RESERVE_BITS11_10_SHFT                                                              0xa
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_POSTDIV_CTL_BMSK                                                                  0x300
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_POSTDIV_CTL_SHFT                                                                    0x8
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_OUTPUT_INV_BMSK                                                                    0x80
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_OUTPUT_INV_SHFT                                                                     0x7
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_RESERVE_BITS6_5_BMSK                                                               0x60
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_RESERVE_BITS6_5_SHFT                                                                0x5
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_PLLOUT_LV_TEST_BMSK                                                                0x10
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_PLLOUT_LV_TEST_SHFT                                                                 0x4
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_PLLOUT_LV_EARLY_BMSK                                                                0x8
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_PLLOUT_LV_EARLY_SHFT                                                                0x3
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_PLLOUT_LV_AUX2_BMSK                                                                 0x4
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_PLLOUT_LV_AUX2_SHFT                                                                 0x2
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_PLLOUT_LV_AUX_BMSK                                                                  0x2
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_PLLOUT_LV_AUX_SHFT                                                                  0x1
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_PLLOUT_LV_MAIN_BMSK                                                                 0x1
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_PLLOUT_LV_MAIN_SHFT                                                                 0x0

#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_U_ADDR                                                                       (LPASS_CC_REG_BASE      + 0x00000014)
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_U_OFFS                                                                       (LPASS_CC_REG_BASE_OFFS + 0x00000014)
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_U_RMSK                                                                       0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_U_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_U_ADDR, HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_U_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_U_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_U_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_U_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_U_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_U_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_U_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_U_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_U_RESERVE_BITS31_0_BMSK                                                      0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_U_RESERVE_BITS31_0_SHFT                                                             0x0

#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_ADDR                                                                       (LPASS_CC_REG_BASE      + 0x00000018)
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_OFFS                                                                       (LPASS_CC_REG_BASE_OFFS + 0x00000018)
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_RMSK                                                                       0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_ADDR, HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_RESERVE_BITS31_18_BMSK                                                     0xfffc0000
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_RESERVE_BITS31_18_SHFT                                                           0x12
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_DITHER_SEL_BMSK                                                               0x30000
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_DITHER_SEL_SHFT                                                                  0x10
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_CORR_EN_BMSK                                                                   0x8000
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_CORR_EN_SHFT                                                                      0xf
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_RVSIG_DEL_BMSK                                                                 0x6000
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_RVSIG_DEL_SHFT                                                                    0xd
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_PFD_DZSEL_BMSK                                                                 0x1800
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_PFD_DZSEL_SHFT                                                                    0xb
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_FORCE_ISEED_BMSK                                                                0x400
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_FORCE_ISEED_SHFT                                                                  0xa
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_CPI_2X_BMSK                                                                     0x200
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_CPI_2X_SHFT                                                                       0x9
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_CPI_CNT_BMSK                                                                    0x1c0
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_CPI_CNT_SHFT                                                                      0x6
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_FILT_BS_CNTL_BMSK                                                                0x30
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_FILT_BS_CNTL_SHFT                                                                 0x4
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_SEL_IREG_OSC_BMSK                                                                 0xc
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_SEL_IREG_OSC_SHFT                                                                 0x2
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_LCKDET_CNFG_BMSK                                                                  0x3
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_LCKDET_CNFG_SHFT                                                                  0x0

#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ADDR                                                                         (LPASS_CC_REG_BASE      + 0x0000001c)
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_OFFS                                                                         (LPASS_CC_REG_BASE_OFFS + 0x0000001c)
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_RMSK                                                                         0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ADDR, HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_RESERVE_BITS31_23_BMSK                                                       0xff800000
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_RESERVE_BITS31_23_SHFT                                                             0x17
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_EN_BMSK                                                                        0x700000
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_EN_SHFT                                                                            0x14
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_PUP_BMSK                                                                        0x80000
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_PUP_SHFT                                                                           0x13
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_CFG_BMSK                                                                        0x60000
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_CFG_SHFT                                                                           0x11
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_TEST_OUT_SEL_BMSK                                                               0x10000
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_TEST_OUT_SEL_SHFT                                                                  0x10
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_RESERVE_BITS15_10_BMSK                                                           0xfc00
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_RESERVE_BITS15_10_SHFT                                                              0xa
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_SEL_IEXT_BMSK                                                                     0x200
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_SEL_IEXT_SHFT                                                                       0x9
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_DTEST_SEL_BMSK                                                                    0x180
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_DTEST_SEL_SHFT                                                                      0x7
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_BYP_TESTAMP_BMSK                                                                   0x40
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_BYP_TESTAMP_SHFT                                                                    0x6
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ATEST1_SEL_BMSK                                                                    0x30
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ATEST1_SEL_SHFT                                                                     0x4
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ATEST0_SEL_BMSK                                                                     0xc
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ATEST0_SEL_SHFT                                                                     0x2
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ATEST1_EN_BMSK                                                                      0x2
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ATEST1_EN_SHFT                                                                      0x1
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ATEST0_EN_BMSK                                                                      0x1
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ATEST0_EN_SHFT                                                                      0x0

#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_ADDR                                                                       (LPASS_CC_REG_BASE      + 0x00000020)
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_OFFS                                                                       (LPASS_CC_REG_BASE_OFFS + 0x00000020)
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_RMSK                                                                       0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_ADDR, HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_RESERVE_BITS31_0_BMSK                                                      0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_RESERVE_BITS31_0_SHFT                                                             0x0

#define HWIO_LPASS_LPAAUDIO_PLL_STATUS_ADDR                                                                           (LPASS_CC_REG_BASE      + 0x00000024)
#define HWIO_LPASS_LPAAUDIO_PLL_STATUS_OFFS                                                                           (LPASS_CC_REG_BASE_OFFS + 0x00000024)
#define HWIO_LPASS_LPAAUDIO_PLL_STATUS_RMSK                                                                               0xffff
#define HWIO_LPASS_LPAAUDIO_PLL_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_STATUS_ADDR, HWIO_LPASS_LPAAUDIO_PLL_STATUS_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_STATUS_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_STATUS_RESERVE_BITS15_2_BMSK                                                              0xfffc
#define HWIO_LPASS_LPAAUDIO_PLL_STATUS_RESERVE_BITS15_2_SHFT                                                                 0x2
#define HWIO_LPASS_LPAAUDIO_PLL_STATUS_PLL_ACK_LATCH_BMSK                                                                    0x2
#define HWIO_LPASS_LPAAUDIO_PLL_STATUS_PLL_ACK_LATCH_SHFT                                                                    0x1
#define HWIO_LPASS_LPAAUDIO_PLL_STATUS_CLOCK_DETECT_BMSK                                                                     0x1
#define HWIO_LPASS_LPAAUDIO_PLL_STATUS_CLOCK_DETECT_SHFT                                                                     0x0

#define HWIO_LPASS_LPAAUDIO_PLL_FREQ_CTL_ADDR                                                                         (LPASS_CC_REG_BASE      + 0x00000028)
#define HWIO_LPASS_LPAAUDIO_PLL_FREQ_CTL_OFFS                                                                         (LPASS_CC_REG_BASE_OFFS + 0x00000028)
#define HWIO_LPASS_LPAAUDIO_PLL_FREQ_CTL_RMSK                                                                         0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_FREQ_CTL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_FREQ_CTL_ADDR, HWIO_LPASS_LPAAUDIO_PLL_FREQ_CTL_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_FREQ_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_FREQ_CTL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_FREQ_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_FREQ_CTL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_FREQ_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_FREQ_CTL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_FREQ_CTL_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_FREQ_CTL_FREQUENCY_CTL_WORD_BMSK                                                      0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_FREQ_CTL_FREQUENCY_CTL_WORD_SHFT                                                             0x0

#define HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_ADDR                                                                       (LPASS_CC_REG_BASE      + 0x0000002c)
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_OFFS                                                                       (LPASS_CC_REG_BASE_OFFS + 0x0000002c)
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_RMSK                                                                              0x3
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_ADDR, HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_CLK_MAIN_SVS_CGC_EN_BMSK                                                          0x2
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_CLK_MAIN_SVS_CGC_EN_SHFT                                                          0x1
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_CLK_MAIN_CGC_EN_BMSK                                                              0x1
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_CLK_MAIN_CGC_EN_SHFT                                                              0x0

#define HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_ADDR                                                                          (LPASS_CC_REG_BASE      + 0x00000030)
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_OFFS                                                                          (LPASS_CC_REG_BASE_OFFS + 0x00000030)
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_RMSK                                                                                 0x3
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_ADDR, HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_CLK_MAIN_DIV_BMSK                                                                    0x3
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_CLK_MAIN_DIV_SHFT                                                                    0x0

#define HWIO_LPASS_LPAAUDIO_PLL_REF_CLK_SRC_SEL_ADDR                                                                  (LPASS_CC_REG_BASE      + 0x00000034)
#define HWIO_LPASS_LPAAUDIO_PLL_REF_CLK_SRC_SEL_OFFS                                                                  (LPASS_CC_REG_BASE_OFFS + 0x00000034)
#define HWIO_LPASS_LPAAUDIO_PLL_REF_CLK_SRC_SEL_RMSK                                                                         0x1
#define HWIO_LPASS_LPAAUDIO_PLL_REF_CLK_SRC_SEL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_REF_CLK_SRC_SEL_ADDR, HWIO_LPASS_LPAAUDIO_PLL_REF_CLK_SRC_SEL_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_REF_CLK_SRC_SEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_REF_CLK_SRC_SEL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_REF_CLK_SRC_SEL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_REF_CLK_SRC_SEL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_REF_CLK_SRC_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_REF_CLK_SRC_SEL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_REF_CLK_SRC_SEL_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_REF_CLK_SRC_SEL_PLL_CLK_SRC_SEL_BMSK                                                         0x1
#define HWIO_LPASS_LPAAUDIO_PLL_REF_CLK_SRC_SEL_PLL_CLK_SRC_SEL_SHFT                                                         0x0

#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_ADDR                                                                         (LPASS_CC_REG_BASE      + 0x00001000)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_OFFS                                                                         (LPASS_CC_REG_BASE_OFFS + 0x00001000)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_RMSK                                                                         0xffffffff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_ADDR, HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_RMSK)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_ADDR,m,v,HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_IN)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_LOCK_DET_BMSK                                                            0x80000000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_LOCK_DET_SHFT                                                                  0x1f
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_ACTIVE_FLAG_BMSK                                                         0x40000000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_ACTIVE_FLAG_SHFT                                                               0x1e
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_ACK_LATCH_BMSK                                                           0x20000000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_ACK_LATCH_SHFT                                                                 0x1d
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_RESERVE_BITS28_24_BMSK                                                       0x1f000000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_RESERVE_BITS28_24_SHFT                                                             0x18
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_HW_UPDATE_LOGIC_BYPASS_BMSK                                                0x800000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_HW_UPDATE_LOGIC_BYPASS_SHFT                                                    0x17
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_UPDATE_BMSK                                                                0x400000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_UPDATE_SHFT                                                                    0x16
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_VOTE_FSM_RESET_BMSK                                                        0x200000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_VOTE_FSM_RESET_SHFT                                                            0x15
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_VOTE_FSM_ENA_BMSK                                                          0x100000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_VOTE_FSM_ENA_SHFT                                                              0x14
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_BIAS_COUNT_BMSK                                                             0xfc000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_BIAS_COUNT_SHFT                                                                 0xe
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_LOCK_COUNT_BMSK                                                              0x3f00
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_LOCK_COUNT_SHFT                                                                 0x8
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_RESERVE_BITS7_4_BMSK                                                               0xf0
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_RESERVE_BITS7_4_SHFT                                                                0x4
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_PLLTEST_BMSK                                                                    0x8
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_PLLTEST_SHFT                                                                    0x3
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_RESET_N_BMSK                                                                    0x4
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_RESET_N_SHFT                                                                    0x2
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_BYPASSNL_BMSK                                                                   0x2
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_BYPASSNL_SHFT                                                                   0x1
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_OUTCTRL_BMSK                                                                    0x1
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_OUTCTRL_SHFT                                                                    0x0

#define HWIO_LPASS_LPAAUDIO_DIG_PLL_L_VAL_ADDR                                                                        (LPASS_CC_REG_BASE      + 0x00001004)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_L_VAL_OFFS                                                                        (LPASS_CC_REG_BASE_OFFS + 0x00001004)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_L_VAL_RMSK                                                                        0xffffffff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_L_VAL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_L_VAL_ADDR, HWIO_LPASS_LPAAUDIO_DIG_PLL_L_VAL_RMSK)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_L_VAL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_L_VAL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_L_VAL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_DIG_PLL_L_VAL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_L_VAL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_DIG_PLL_L_VAL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_DIG_PLL_L_VAL_IN)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_L_VAL_RESERVE_BITS_31_16_BMSK                                                     0xffff0000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_L_VAL_RESERVE_BITS_31_16_SHFT                                                           0x10
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_L_VAL_PLL_L_BMSK                                                                      0xffff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_L_VAL_PLL_L_SHFT                                                                         0x0

#define HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_ADDR                                                                    (LPASS_CC_REG_BASE      + 0x00001008)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_OFFS                                                                    (LPASS_CC_REG_BASE_OFFS + 0x00001008)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_RMSK                                                                    0xffffffff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_ADDR, HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_RMSK)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_IN)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_PLL_ALPHA_31_0_BMSK                                                     0xffffffff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_PLL_ALPHA_31_0_SHFT                                                            0x0

#define HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_U_ADDR                                                                  (LPASS_CC_REG_BASE      + 0x0000100c)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_U_OFFS                                                                  (LPASS_CC_REG_BASE_OFFS + 0x0000100c)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_U_RMSK                                                                  0xffffffff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_U_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_U_ADDR, HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_U_RMSK)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_U_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_U_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_U_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_U_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_U_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_U_ADDR,m,v,HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_U_IN)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_U_RESERVE_BITS_31_8_BMSK                                                0xffffff00
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_U_RESERVE_BITS_31_8_SHFT                                                       0x8
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_U_PLL_ALPHA_39_32_BMSK                                                        0xff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_U_PLL_ALPHA_39_32_SHFT                                                         0x0

#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_ADDR                                                                     (LPASS_CC_REG_BASE      + 0x00001010)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_OFFS                                                                     (LPASS_CC_REG_BASE_OFFS + 0x00001010)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_RMSK                                                                     0xffffffff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_ADDR, HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_RMSK)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_IN)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_RESERVE_BITS31_28_BMSK                                                   0xf0000000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_RESERVE_BITS31_28_SHFT                                                         0x1c
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_SSC_MODE_CONTROL_BMSK                                                     0x8000000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_SSC_MODE_CONTROL_SHFT                                                          0x1b
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_RESERVE_BITS26_25_BMSK                                                    0x6000000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_RESERVE_BITS26_25_SHFT                                                         0x19
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_ALPHA_EN_BMSK                                                             0x1000000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_ALPHA_EN_SHFT                                                                  0x18
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_RESERVE_BITS23_22_BMSK                                                     0xc00000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_RESERVE_BITS23_22_SHFT                                                         0x16
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_VCO_SEL_BMSK                                                               0x300000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_VCO_SEL_SHFT                                                                   0x14
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_RESERVE_BITS19_18_BMSK                                                      0xc0000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_RESERVE_BITS19_18_SHFT                                                         0x12
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_AUX_POST_DIV_RATIO_BMSK                                                     0x38000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_AUX_POST_DIV_RATIO_SHFT                                                         0xf
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_PRE_DIV_RATIO_BMSK                                                           0x7000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_PRE_DIV_RATIO_SHFT                                                              0xc
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_POST_DIV_RATIO_BMSK                                                           0xf00
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_POST_DIV_RATIO_SHFT                                                             0x8
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_OUTPUT_INV_BMSK                                                                0x80
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_OUTPUT_INV_SHFT                                                                 0x7
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_RESERVE_BITS6_5_BMSK                                                           0x60
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_RESERVE_BITS6_5_SHFT                                                            0x5
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_PLLOUT_LV_TEST_BMSK                                                            0x10
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_PLLOUT_LV_TEST_SHFT                                                             0x4
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_PLLOUT_LV_EARLY_BMSK                                                            0x8
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_PLLOUT_LV_EARLY_SHFT                                                            0x3
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_PLLOUT_LV_AUX2_BMSK                                                             0x4
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_PLLOUT_LV_AUX2_SHFT                                                             0x2
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_PLLOUT_LV_AUX_BMSK                                                              0x2
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_PLLOUT_LV_AUX_SHFT                                                              0x1
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_PLLOUT_LV_MAIN_BMSK                                                             0x1
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_PLLOUT_LV_MAIN_SHFT                                                             0x0

#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_ADDR                                                                   (LPASS_CC_REG_BASE      + 0x00001014)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_OFFS                                                                   (LPASS_CC_REG_BASE_OFFS + 0x00001014)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_RMSK                                                                   0xffffffff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_ADDR, HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_RMSK)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_ADDR,m,v,HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_IN)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_RESERVE_BITS31_12_BMSK                                                 0xfffff000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_RESERVE_BITS31_12_SHFT                                                        0xc
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_LATCH_INTERFACE_BYPASS_BMSK                                                 0x800
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_LATCH_INTERFACE_BYPASS_SHFT                                                   0xb
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_STATUS_REGISTER_BMSK                                                        0x700
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_STATUS_REGISTER_SHFT                                                          0x8
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_DSM_BMSK                                                                     0x80
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_DSM_SHFT                                                                      0x7
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_WRITE_STATE_BMSK                                                             0x40
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_WRITE_STATE_SHFT                                                              0x6
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_TARGET_CTL_BMSK                                                              0x38
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_TARGET_CTL_SHFT                                                               0x3
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_LOCK_DET_BMSK                                                                 0x4
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_LOCK_DET_SHFT                                                                 0x2
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_FREEZE_PLL_BMSK                                                               0x2
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_FREEZE_PLL_SHFT                                                               0x1
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_TOGGLE_DET_BMSK                                                               0x1
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_TOGGLE_DET_SHFT                                                               0x0

#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_ADDR                                                                   (LPASS_CC_REG_BASE      + 0x00001018)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_OFFS                                                                   (LPASS_CC_REG_BASE_OFFS + 0x00001018)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_RMSK                                                                   0xffffffff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_ADDR, HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_RMSK)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_IN)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_SINGLE_DMET_MODE_ENABLE_BMSK                                           0x80000000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_SINGLE_DMET_MODE_ENABLE_SHFT                                                 0x1f
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_DMET_WINDOW_ENABLE_BMSK                                                0x40000000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_DMET_WINDOW_ENABLE_SHFT                                                      0x1e
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_TOGGLE_DET_SAMPLE_INTER_BMSK                                           0x3c000000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_TOGGLE_DET_SAMPLE_INTER_SHFT                                                 0x1a
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_TOGGLE_DET_THRESHOLD_BMSK                                               0x3800000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_TOGGLE_DET_THRESHOLD_SHFT                                                    0x17
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_TOGGLE_DET_SAMPLE_BMSK                                                   0x700000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_TOGGLE_DET_SAMPLE_SHFT                                                       0x14
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_LOCK_DET_THRESHOLD_BMSK                                                   0xff000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_LOCK_DET_THRESHOLD_SHFT                                                       0xc
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_LOCK_DET_SAMPLE_SIZE_BMSK                                                   0xf00
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_LOCK_DET_SAMPLE_SIZE_SHFT                                                     0x8
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_MIN_GLITCH_THRESHOLD_BMSK                                                    0xc0
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_MIN_GLITCH_THRESHOLD_SHFT                                                     0x6
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_REF_CYCLE_BMSK                                                               0x30
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_REF_CYCLE_SHFT                                                                0x4
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_KFN_BMSK                                                                      0xf
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_KFN_SHFT                                                                      0x0

#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_ADDR                                                                     (LPASS_CC_REG_BASE      + 0x0000101c)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_OFFS                                                                     (LPASS_CC_REG_BASE_OFFS + 0x0000101c)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_RMSK                                                                     0xffffffff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_ADDR, HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_RMSK)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_IN)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_BIAS_GEN_TRIM_BMSK                                                       0xe0000000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_BIAS_GEN_TRIM_SHFT                                                             0x1d
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_PROCESS_CALB_BMSK                                                        0x1c000000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_PROCESS_CALB_SHFT                                                              0x1a
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_OVERRIDE_PROCESS_CALB_BMSK                                                0x2000000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_OVERRIDE_PROCESS_CALB_SHFT                                                     0x19
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_FINE_FCW_BMSK                                                             0x1f00000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_FINE_FCW_SHFT                                                                  0x14
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_OVERRIDE_FINE_FCW_BMSK                                                      0x80000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_OVERRIDE_FINE_FCW_SHFT                                                         0x13
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_COARSE_FCW_BMSK                                                             0x7e000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_COARSE_FCW_SHFT                                                                 0xd
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_OVERRIDE_COARSE_BMSK                                                         0x1000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_OVERRIDE_COARSE_SHFT                                                            0xc
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_DISABLE_LFSR_BMSK                                                             0x800
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_DISABLE_LFSR_SHFT                                                               0xb
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_DTEST_SEL_BMSK                                                                0x700
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_DTEST_SEL_SHFT                                                                  0x8
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_DTEST_EN_BMSK                                                                  0x80
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_DTEST_EN_SHFT                                                                   0x7
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_BYP_TESTAMP_BMSK                                                               0x40
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_BYP_TESTAMP_SHFT                                                                0x6
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_ATEST1_SEL_BMSK                                                                0x30
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_ATEST1_SEL_SHFT                                                                 0x4
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_ATEST0_SEL_BMSK                                                                 0xc
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_ATEST0_SEL_SHFT                                                                 0x2
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_ATEST1_EN_BMSK                                                                  0x2
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_ATEST1_EN_SHFT                                                                  0x1
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_ATEST0_EN_BMSK                                                                  0x1
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_ATEST0_EN_SHFT                                                                  0x0

#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_ADDR                                                                   (LPASS_CC_REG_BASE      + 0x00001020)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_OFFS                                                                   (LPASS_CC_REG_BASE_OFFS + 0x00001020)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_RMSK                                                                   0xffffffff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_ADDR, HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_RMSK)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_ADDR,m,v,HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_IN)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_RESERVE_BITS31_22_BMSK                                                 0xffc00000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_RESERVE_BITS31_22_SHFT                                                       0x16
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_GLITCH_DET_CNT_LIMIT_BMSK                                                0x300000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_GLITCH_DET_CNT_LIMIT_SHFT                                                    0x14
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_DIS_GLITCH_PREVENTION_BMSK                                                0x80000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_DIS_GLITCH_PREVENTION_SHFT                                                   0x13
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_DTEST_MODE_SEL_U_BMSK                                                     0x60000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_DTEST_MODE_SEL_U_SHFT                                                        0x11
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_DITHER_SEL_BMSK                                                           0x18000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_DITHER_SEL_SHFT                                                               0xf
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_SEL_2B_3B_CAL_BMSK                                                         0x4000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_SEL_2B_3B_CAL_SHFT                                                            0xe
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_OVERRIDE_FINE_FCW_MSB_BMSK                                                 0x2000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_OVERRIDE_FINE_FCW_MSB_SHFT                                                    0xd
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_DTEST_MODE_SEL_BMSK                                                        0x1800
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_DTEST_MODE_SEL_SHFT                                                           0xb
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_NMO_OSC_SEL_BMSK                                                            0x600
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_NMO_OSC_SEL_SHFT                                                              0x9
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_RESERVE_BIT8_BMSK                                                           0x100
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_RESERVE_BIT8_SHFT                                                             0x8
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_NOISE_MAG_BMSK                                                               0xe0
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_NOISE_MAG_SHFT                                                                0x5
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_NOISE_GEN_BMSK                                                               0x10
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_NOISE_GEN_SHFT                                                                0x4
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_OSC_BIAS_GND_BMSK                                                             0x8
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_OSC_BIAS_GND_SHFT                                                             0x3
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_PLL_TEST_OUT_SEL_BMSK                                                         0x6
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_PLL_TEST_OUT_SEL_SHFT                                                         0x1
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_CAL_CODE_UPDATE_BMSK                                                          0x1
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_CAL_CODE_UPDATE_SHFT                                                          0x0

#define HWIO_LPASS_LPAAUDIO_DIG_PLL_STATUS_ADDR                                                                       (LPASS_CC_REG_BASE      + 0x00001024)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_STATUS_OFFS                                                                       (LPASS_CC_REG_BASE_OFFS + 0x00001024)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_STATUS_RMSK                                                                       0xffffffff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_STATUS_ADDR, HWIO_LPASS_LPAAUDIO_DIG_PLL_STATUS_RMSK)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_STATUS_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_STATUS_STATUS_31_0_BMSK                                                           0xffffffff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_STATUS_STATUS_31_0_SHFT                                                                  0x0

#define HWIO_LPASS_LPAAUDIO_DIG_PLL_FREQ_CTL_ADDR                                                                     (LPASS_CC_REG_BASE      + 0x00001028)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_FREQ_CTL_OFFS                                                                     (LPASS_CC_REG_BASE_OFFS + 0x00001028)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_FREQ_CTL_RMSK                                                                     0xffffffff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_FREQ_CTL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_FREQ_CTL_ADDR, HWIO_LPASS_LPAAUDIO_DIG_PLL_FREQ_CTL_RMSK)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_FREQ_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_FREQ_CTL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_FREQ_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_DIG_PLL_FREQ_CTL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_FREQ_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_DIG_PLL_FREQ_CTL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_DIG_PLL_FREQ_CTL_IN)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_FREQ_CTL_FREQUENCY_CTL_WORD_BMSK                                                  0xffffffff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_FREQ_CTL_FREQUENCY_CTL_WORD_SHFT                                                         0x0

#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_ADDR                                                                   (LPASS_CC_REG_BASE      + 0x0000102c)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_OFFS                                                                   (LPASS_CC_REG_BASE_OFFS + 0x0000102c)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_RMSK                                                                          0xf
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_ADDR, HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_RMSK)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_ADDR,m,v,HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_IN)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_CLK_AUX_CGC_EN_BMSK                                                           0x8
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_CLK_AUX_CGC_EN_SHFT                                                           0x3
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_CLK_MAIN_CGC_EN_BMSK                                                          0x4
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_CLK_MAIN_CGC_EN_SHFT                                                          0x2
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_CLK_EARLY_SVS_CGC_EN_BMSK                                                     0x2
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_CLK_EARLY_SVS_CGC_EN_SHFT                                                     0x1
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_CLK_EARLY_CGC_EN_BMSK                                                         0x1
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_CLK_EARLY_CGC_EN_SHFT                                                         0x0

#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_DIV_ADDR                                                                      (LPASS_CC_REG_BASE      + 0x00001030)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_DIV_OFFS                                                                      (LPASS_CC_REG_BASE_OFFS + 0x00001030)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_DIV_RMSK                                                                             0x3
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_DIV_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_DIV_ADDR, HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_DIV_RMSK)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_DIV_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_DIV_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_DIV_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_DIV_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_DIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_DIV_ADDR,m,v,HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_DIV_IN)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_DIV_CLK_MAIN_DIV_BMSK                                                                0x3
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_DIV_CLK_MAIN_DIV_SHFT                                                                0x0

#define HWIO_LPASS_LPAAUDIO_DIG_PLL_REF_CLK_SRC_SEL_ADDR                                                              (LPASS_CC_REG_BASE      + 0x00001034)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_REF_CLK_SRC_SEL_OFFS                                                              (LPASS_CC_REG_BASE_OFFS + 0x00001034)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_REF_CLK_SRC_SEL_RMSK                                                                     0x3
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_REF_CLK_SRC_SEL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_REF_CLK_SRC_SEL_ADDR, HWIO_LPASS_LPAAUDIO_DIG_PLL_REF_CLK_SRC_SEL_RMSK)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_REF_CLK_SRC_SEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_REF_CLK_SRC_SEL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_REF_CLK_SRC_SEL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_DIG_PLL_REF_CLK_SRC_SEL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_REF_CLK_SRC_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_DIG_PLL_REF_CLK_SRC_SEL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_DIG_PLL_REF_CLK_SRC_SEL_IN)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_REF_CLK_SRC_SEL_PLL_CLK_SRC_SEL_BMSK                                                     0x3
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_REF_CLK_SRC_SEL_PLL_CLK_SRC_SEL_SHFT                                                     0x0

#define HWIO_LPASS_QDSP6SS_PLL_REF_CLK_SRC_SEL_ADDR                                                                   (LPASS_CC_REG_BASE      + 0x00002000)
#define HWIO_LPASS_QDSP6SS_PLL_REF_CLK_SRC_SEL_OFFS                                                                   (LPASS_CC_REG_BASE_OFFS + 0x00002000)
#define HWIO_LPASS_QDSP6SS_PLL_REF_CLK_SRC_SEL_RMSK                                                                          0x3
#define HWIO_LPASS_QDSP6SS_PLL_REF_CLK_SRC_SEL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_REF_CLK_SRC_SEL_ADDR, HWIO_LPASS_QDSP6SS_PLL_REF_CLK_SRC_SEL_RMSK)
#define HWIO_LPASS_QDSP6SS_PLL_REF_CLK_SRC_SEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_REF_CLK_SRC_SEL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PLL_REF_CLK_SRC_SEL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PLL_REF_CLK_SRC_SEL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PLL_REF_CLK_SRC_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_PLL_REF_CLK_SRC_SEL_ADDR,m,v,HWIO_LPASS_QDSP6SS_PLL_REF_CLK_SRC_SEL_IN)
#define HWIO_LPASS_QDSP6SS_PLL_REF_CLK_SRC_SEL_PLL_CLK_SRC_SEL_BMSK                                                          0x3
#define HWIO_LPASS_QDSP6SS_PLL_REF_CLK_SRC_SEL_PLL_CLK_SRC_SEL_SHFT                                                          0x0

#define HWIO_LPASS_LPAAUDIO_XO_CLK_CTL_ADDR                                                                           (LPASS_CC_REG_BASE      + 0x00003000)
#define HWIO_LPASS_LPAAUDIO_XO_CLK_CTL_OFFS                                                                           (LPASS_CC_REG_BASE_OFFS + 0x00003000)
#define HWIO_LPASS_LPAAUDIO_XO_CLK_CTL_RMSK                                                                                  0x1
#define HWIO_LPASS_LPAAUDIO_XO_CLK_CTL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_XO_CLK_CTL_ADDR, HWIO_LPASS_LPAAUDIO_XO_CLK_CTL_RMSK)
#define HWIO_LPASS_LPAAUDIO_XO_CLK_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_XO_CLK_CTL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_XO_CLK_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_XO_CLK_CTL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_XO_CLK_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_XO_CLK_CTL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_XO_CLK_CTL_IN)
#define HWIO_LPASS_LPAAUDIO_XO_CLK_CTL_XO_CLK_CGC_EN_BMSK                                                                    0x1
#define HWIO_LPASS_LPAAUDIO_XO_CLK_CTL_XO_CLK_CGC_EN_SHFT                                                                    0x0

#define HWIO_LPASS_LPAAUDIO_RAW_CLK_CTL_ADDR                                                                          (LPASS_CC_REG_BASE      + 0x00003004)
#define HWIO_LPASS_LPAAUDIO_RAW_CLK_CTL_OFFS                                                                          (LPASS_CC_REG_BASE_OFFS + 0x00003004)
#define HWIO_LPASS_LPAAUDIO_RAW_CLK_CTL_RMSK                                                                                 0x3
#define HWIO_LPASS_LPAAUDIO_RAW_CLK_CTL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_RAW_CLK_CTL_ADDR, HWIO_LPASS_LPAAUDIO_RAW_CLK_CTL_RMSK)
#define HWIO_LPASS_LPAAUDIO_RAW_CLK_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_RAW_CLK_CTL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_RAW_CLK_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_RAW_CLK_CTL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_RAW_CLK_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_RAW_CLK_CTL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_RAW_CLK_CTL_IN)
#define HWIO_LPASS_LPAAUDIO_RAW_CLK_CTL_RAW_CLK_SRC_SEL_BMSK                                                                 0x2
#define HWIO_LPASS_LPAAUDIO_RAW_CLK_CTL_RAW_CLK_SRC_SEL_SHFT                                                                 0x1
#define HWIO_LPASS_LPAAUDIO_RAW_CLK_CTL_RAW_CLK_CGC_EN_BMSK                                                                  0x1
#define HWIO_LPASS_LPAAUDIO_RAW_CLK_CTL_RAW_CLK_CGC_EN_SHFT                                                                  0x0

#define HWIO_LPASS_LPA_PLL_VOTE_APPS_ADDR                                                                             (LPASS_CC_REG_BASE      + 0x00005000)
#define HWIO_LPASS_LPA_PLL_VOTE_APPS_OFFS                                                                             (LPASS_CC_REG_BASE_OFFS + 0x00005000)
#define HWIO_LPASS_LPA_PLL_VOTE_APPS_RMSK                                                                                   0xff
#define HWIO_LPASS_LPA_PLL_VOTE_APPS_IN          \
        in_dword_masked(HWIO_LPASS_LPA_PLL_VOTE_APPS_ADDR, HWIO_LPASS_LPA_PLL_VOTE_APPS_RMSK)
#define HWIO_LPASS_LPA_PLL_VOTE_APPS_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPA_PLL_VOTE_APPS_ADDR, m)
#define HWIO_LPASS_LPA_PLL_VOTE_APPS_OUT(v)      \
        out_dword(HWIO_LPASS_LPA_PLL_VOTE_APPS_ADDR,v)
#define HWIO_LPASS_LPA_PLL_VOTE_APPS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPA_PLL_VOTE_APPS_ADDR,m,v,HWIO_LPASS_LPA_PLL_VOTE_APPS_IN)
#define HWIO_LPASS_LPA_PLL_VOTE_APPS_RESERVE_BITS7_3_BMSK                                                                   0xf8
#define HWIO_LPASS_LPA_PLL_VOTE_APPS_RESERVE_BITS7_3_SHFT                                                                    0x3
#define HWIO_LPASS_LPA_PLL_VOTE_APPS_QDSP6SS_PLL_BMSK                                                                        0x4
#define HWIO_LPASS_LPA_PLL_VOTE_APPS_QDSP6SS_PLL_SHFT                                                                        0x2
#define HWIO_LPASS_LPA_PLL_VOTE_APPS_LPAAUDIO_DIG_PLL_BMSK                                                                   0x2
#define HWIO_LPASS_LPA_PLL_VOTE_APPS_LPAAUDIO_DIG_PLL_SHFT                                                                   0x1
#define HWIO_LPASS_LPA_PLL_VOTE_APPS_LPAAUDIO_PLL_BMSK                                                                       0x1
#define HWIO_LPASS_LPA_PLL_VOTE_APPS_LPAAUDIO_PLL_SHFT                                                                       0x0

#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_ADDR                                                                          (LPASS_CC_REG_BASE      + 0x00006000)
#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_OFFS                                                                          (LPASS_CC_REG_BASE_OFFS + 0x00006000)
#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_RMSK                                                                                0xff
#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_IN          \
        in_dword_masked(HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_ADDR, HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_RMSK)
#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_ADDR, m)
#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_OUT(v)      \
        out_dword(HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_ADDR,v)
#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_ADDR,m,v,HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_IN)
#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_RESERVE_BITS7_3_BMSK                                                                0xf8
#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_RESERVE_BITS7_3_SHFT                                                                 0x3
#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_QDSP6SS_PLL_BMSK                                                                     0x4
#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_QDSP6SS_PLL_SHFT                                                                     0x2
#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_LPAAUDIO_DIG_PLL_BMSK                                                                0x2
#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_LPAAUDIO_DIG_PLL_SHFT                                                                0x1
#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_LPAAUDIO_PLL_BMSK                                                                    0x1
#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_LPAAUDIO_PLL_SHFT                                                                    0x0

#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_ADDR                                                                         (LPASS_CC_REG_BASE      + 0x00007000)
#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_OFFS                                                                         (LPASS_CC_REG_BASE_OFFS + 0x00007000)
#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_RMSK                                                                               0xff
#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_IN          \
        in_dword_masked(HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_ADDR, HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_RMSK)
#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_ADDR, m)
#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_OUT(v)      \
        out_dword(HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_ADDR,v)
#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_ADDR,m,v,HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_IN)
#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_RESERVE_BITS7_3_BMSK                                                               0xf8
#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_RESERVE_BITS7_3_SHFT                                                                0x3
#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_QDSP6SS_PLL_BMSK                                                                    0x4
#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_QDSP6SS_PLL_SHFT                                                                    0x2
#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_LPAAUDIO_DIG_PLL_BMSK                                                               0x2
#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_LPAAUDIO_DIG_PLL_SHFT                                                               0x1
#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_LPAAUDIO_PLL_BMSK                                                                   0x1
#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_LPAAUDIO_PLL_SHFT                                                                   0x0

#define HWIO_LPASS_AUDIO_CORE_BCR_ADDR                                                                                (LPASS_CC_REG_BASE      + 0x00008000)
#define HWIO_LPASS_AUDIO_CORE_BCR_OFFS                                                                                (LPASS_CC_REG_BASE_OFFS + 0x00008000)
#define HWIO_LPASS_AUDIO_CORE_BCR_RMSK                                                                                0xf8000007
#define HWIO_LPASS_AUDIO_CORE_BCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_BCR_ADDR, HWIO_LPASS_AUDIO_CORE_BCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_BCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_BCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_BCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_BCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_BCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_BCR_IN)
#define HWIO_LPASS_AUDIO_CORE_BCR_DFD_STATUS_BMSK                                                                     0x80000000
#define HWIO_LPASS_AUDIO_CORE_BCR_DFD_STATUS_SHFT                                                                           0x1f
#define HWIO_LPASS_AUDIO_CORE_BCR_BCR_RESET_STATE_BMSK                                                                0x60000000
#define HWIO_LPASS_AUDIO_CORE_BCR_BCR_RESET_STATE_SHFT                                                                      0x1d
#define HWIO_LPASS_AUDIO_CORE_BCR_LPASS_BUS_ABORT_ACK_STATUS_BMSK                                                     0x10000000
#define HWIO_LPASS_AUDIO_CORE_BCR_LPASS_BUS_ABORT_ACK_STATUS_SHFT                                                           0x1c
#define HWIO_LPASS_AUDIO_CORE_BCR_PSMMU_ABORT_ACK_STATUS_BMSK                                                          0x8000000
#define HWIO_LPASS_AUDIO_CORE_BCR_PSMMU_ABORT_ACK_STATUS_SHFT                                                               0x1b
#define HWIO_LPASS_AUDIO_CORE_BCR_FORCE_RESET_BMSK                                                                           0x4
#define HWIO_LPASS_AUDIO_CORE_BCR_FORCE_RESET_SHFT                                                                           0x2
#define HWIO_LPASS_AUDIO_CORE_BCR_DFD_EN_BMSK                                                                                0x2
#define HWIO_LPASS_AUDIO_CORE_BCR_DFD_EN_SHFT                                                                                0x1
#define HWIO_LPASS_AUDIO_CORE_BCR_BLK_ARES_BMSK                                                                              0x1
#define HWIO_LPASS_AUDIO_CORE_BCR_BLK_ARES_SHFT                                                                              0x0

#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_ADDR                                                                       (LPASS_CC_REG_BASE      + 0x00008004)
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_OFFS                                                                       (LPASS_CC_REG_BASE_OFFS + 0x00008004)
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_RMSK                                                                       0x80000003
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_CLK_OFF_BMSK                                                               0x80000000
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_CLK_OFF_SHFT                                                                     0x1f
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_HW_CTL_BMSK                                                                       0x2
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_HW_CTL_SHFT                                                                       0x1
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_CLK_ENABLE_BMSK                                                                   0x1
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_CLK_ENABLE_SHFT                                                                   0x0

#define HWIO_LPASS_AUDIO_WRAPPER_BCR_ADDR                                                                             (LPASS_CC_REG_BASE      + 0x00009000)
#define HWIO_LPASS_AUDIO_WRAPPER_BCR_OFFS                                                                             (LPASS_CC_REG_BASE_OFFS + 0x00009000)
#define HWIO_LPASS_AUDIO_WRAPPER_BCR_RMSK                                                                             0x80000003
#define HWIO_LPASS_AUDIO_WRAPPER_BCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_BCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_BCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_BCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_BCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_BCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_BCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_BCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_BCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_BCR_DFD_STATUS_BMSK                                                                  0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_BCR_DFD_STATUS_SHFT                                                                        0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_BCR_DFD_EN_BMSK                                                                             0x2
#define HWIO_LPASS_AUDIO_WRAPPER_BCR_DFD_EN_SHFT                                                                             0x1
#define HWIO_LPASS_AUDIO_WRAPPER_BCR_BLK_ARES_BMSK                                                                           0x1
#define HWIO_LPASS_AUDIO_WRAPPER_BCR_BLK_ARES_SHFT                                                                           0x0

#define HWIO_LPASS_SENSOR_CORE_BCR_ADDR                                                                               (LPASS_CC_REG_BASE      + 0x00009004)
#define HWIO_LPASS_SENSOR_CORE_BCR_OFFS                                                                               (LPASS_CC_REG_BASE_OFFS + 0x00009004)
#define HWIO_LPASS_SENSOR_CORE_BCR_RMSK                                                                               0x70000005
#define HWIO_LPASS_SENSOR_CORE_BCR_IN          \
        in_dword_masked(HWIO_LPASS_SENSOR_CORE_BCR_ADDR, HWIO_LPASS_SENSOR_CORE_BCR_RMSK)
#define HWIO_LPASS_SENSOR_CORE_BCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SENSOR_CORE_BCR_ADDR, m)
#define HWIO_LPASS_SENSOR_CORE_BCR_OUT(v)      \
        out_dword(HWIO_LPASS_SENSOR_CORE_BCR_ADDR,v)
#define HWIO_LPASS_SENSOR_CORE_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SENSOR_CORE_BCR_ADDR,m,v,HWIO_LPASS_SENSOR_CORE_BCR_IN)
#define HWIO_LPASS_SENSOR_CORE_BCR_BCR_RESET_STATE_BMSK                                                               0x60000000
#define HWIO_LPASS_SENSOR_CORE_BCR_BCR_RESET_STATE_SHFT                                                                     0x1d
#define HWIO_LPASS_SENSOR_CORE_BCR_SENSOR_CORE_BUS_ABORT_ACK_STATUS_BMSK                                              0x10000000
#define HWIO_LPASS_SENSOR_CORE_BCR_SENSOR_CORE_BUS_ABORT_ACK_STATUS_SHFT                                                    0x1c
#define HWIO_LPASS_SENSOR_CORE_BCR_FORCE_RESET_BMSK                                                                          0x4
#define HWIO_LPASS_SENSOR_CORE_BCR_FORCE_RESET_SHFT                                                                          0x2
#define HWIO_LPASS_SENSOR_CORE_BCR_BLK_ARES_BMSK                                                                             0x1
#define HWIO_LPASS_SENSOR_CORE_BCR_BLK_ARES_SHFT                                                                             0x0

#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_SLP_CBCR_ADDR                                                           (LPASS_CC_REG_BASE      + 0x00009008)
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_SLP_CBCR_OFFS                                                           (LPASS_CC_REG_BASE_OFFS + 0x00009008)
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_SLP_CBCR_RMSK                                                           0x80000003
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_SLP_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_SLP_CBCR_ADDR, HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_SLP_CBCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_SLP_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_SLP_CBCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_SLP_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_SLP_CBCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_SLP_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_SLP_CBCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_SLP_CBCR_IN)
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_SLP_CBCR_CLK_OFF_BMSK                                                   0x80000000
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_SLP_CBCR_CLK_OFF_SHFT                                                         0x1f
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_SLP_CBCR_HW_CTL_BMSK                                                           0x2
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_SLP_CBCR_HW_CTL_SHFT                                                           0x1
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_SLP_CBCR_CLK_ENABLE_BMSK                                                       0x1
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_SLP_CBCR_CLK_ENABLE_SHFT                                                       0x0

#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_XO_CBCR_ADDR                                                            (LPASS_CC_REG_BASE      + 0x0000900c)
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_XO_CBCR_OFFS                                                            (LPASS_CC_REG_BASE_OFFS + 0x0000900c)
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_XO_CBCR_RMSK                                                            0x80000003
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_XO_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_XO_CBCR_ADDR, HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_XO_CBCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_XO_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_XO_CBCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_XO_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_XO_CBCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_XO_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_XO_CBCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_XO_CBCR_IN)
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_XO_CBCR_CLK_OFF_BMSK                                                    0x80000000
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_XO_CBCR_CLK_OFF_SHFT                                                          0x1f
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_XO_CBCR_HW_CTL_BMSK                                                            0x2
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_XO_CBCR_HW_CTL_SHFT                                                            0x1
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_XO_CBCR_CLK_ENABLE_BMSK                                                        0x1
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_XO_CBCR_CLK_ENABLE_SHFT                                                        0x0

#define HWIO_LPASS_Q6SS_BCR_ADDR                                                                                      (LPASS_CC_REG_BASE      + 0x0000a000)
#define HWIO_LPASS_Q6SS_BCR_OFFS                                                                                      (LPASS_CC_REG_BASE_OFFS + 0x0000a000)
#define HWIO_LPASS_Q6SS_BCR_RMSK                                                                                      0x80000003
#define HWIO_LPASS_Q6SS_BCR_IN          \
        in_dword_masked(HWIO_LPASS_Q6SS_BCR_ADDR, HWIO_LPASS_Q6SS_BCR_RMSK)
#define HWIO_LPASS_Q6SS_BCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_Q6SS_BCR_ADDR, m)
#define HWIO_LPASS_Q6SS_BCR_OUT(v)      \
        out_dword(HWIO_LPASS_Q6SS_BCR_ADDR,v)
#define HWIO_LPASS_Q6SS_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_Q6SS_BCR_ADDR,m,v,HWIO_LPASS_Q6SS_BCR_IN)
#define HWIO_LPASS_Q6SS_BCR_DFD_STATUS_BMSK                                                                           0x80000000
#define HWIO_LPASS_Q6SS_BCR_DFD_STATUS_SHFT                                                                                 0x1f
#define HWIO_LPASS_Q6SS_BCR_DFD_EN_BMSK                                                                                      0x2
#define HWIO_LPASS_Q6SS_BCR_DFD_EN_SHFT                                                                                      0x1
#define HWIO_LPASS_Q6SS_BCR_BLK_ARES_BMSK                                                                                    0x1
#define HWIO_LPASS_Q6SS_BCR_BLK_ARES_SHFT                                                                                    0x0

#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_ADDR                                                                             (LPASS_CC_REG_BASE      + 0x0000a004)
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_OFFS                                                                             (LPASS_CC_REG_BASE_OFFS + 0x0000a004)
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_RMSK                                                                             0x80000003
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_Q6SS_BCR_SLP_CBCR_ADDR, HWIO_LPASS_Q6SS_BCR_SLP_CBCR_RMSK)
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_Q6SS_BCR_SLP_CBCR_ADDR, m)
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_Q6SS_BCR_SLP_CBCR_ADDR,v)
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_Q6SS_BCR_SLP_CBCR_ADDR,m,v,HWIO_LPASS_Q6SS_BCR_SLP_CBCR_IN)
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_CLK_OFF_BMSK                                                                     0x80000000
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_CLK_OFF_SHFT                                                                           0x1f
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_HW_CTL_BMSK                                                                             0x2
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_HW_CTL_SHFT                                                                             0x1
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_CLK_ENABLE_BMSK                                                                         0x1
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_CLK_ENABLE_SHFT                                                                         0x0

#define HWIO_LPASS_AUDIO_CORE_GDSCR_ADDR                                                                              (LPASS_CC_REG_BASE      + 0x0000b000)
#define HWIO_LPASS_AUDIO_CORE_GDSCR_OFFS                                                                              (LPASS_CC_REG_BASE_OFFS + 0x0000b000)
#define HWIO_LPASS_AUDIO_CORE_GDSCR_RMSK                                                                              0xf8ffffff
#define HWIO_LPASS_AUDIO_CORE_GDSCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_GDSCR_ADDR, HWIO_LPASS_AUDIO_CORE_GDSCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_GDSCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_GDSCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_GDSCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_GDSCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_GDSCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_GDSCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_GDSCR_IN)
#define HWIO_LPASS_AUDIO_CORE_GDSCR_PWR_ON_BMSK                                                                       0x80000000
#define HWIO_LPASS_AUDIO_CORE_GDSCR_PWR_ON_SHFT                                                                             0x1f
#define HWIO_LPASS_AUDIO_CORE_GDSCR_GDSC_STATE_BMSK                                                                   0x78000000
#define HWIO_LPASS_AUDIO_CORE_GDSCR_GDSC_STATE_SHFT                                                                         0x1b
#define HWIO_LPASS_AUDIO_CORE_GDSCR_EN_REST_WAIT_BMSK                                                                   0xf00000
#define HWIO_LPASS_AUDIO_CORE_GDSCR_EN_REST_WAIT_SHFT                                                                       0x14
#define HWIO_LPASS_AUDIO_CORE_GDSCR_EN_FEW_WAIT_BMSK                                                                     0xf0000
#define HWIO_LPASS_AUDIO_CORE_GDSCR_EN_FEW_WAIT_SHFT                                                                        0x10
#define HWIO_LPASS_AUDIO_CORE_GDSCR_CLK_DIS_WAIT_BMSK                                                                     0xf000
#define HWIO_LPASS_AUDIO_CORE_GDSCR_CLK_DIS_WAIT_SHFT                                                                        0xc
#define HWIO_LPASS_AUDIO_CORE_GDSCR_RETAIN_FF_ENABLE_BMSK                                                                  0x800
#define HWIO_LPASS_AUDIO_CORE_GDSCR_RETAIN_FF_ENABLE_SHFT                                                                    0xb
#define HWIO_LPASS_AUDIO_CORE_GDSCR_RESTORE_BMSK                                                                           0x400
#define HWIO_LPASS_AUDIO_CORE_GDSCR_RESTORE_SHFT                                                                             0xa
#define HWIO_LPASS_AUDIO_CORE_GDSCR_SAVE_BMSK                                                                              0x200
#define HWIO_LPASS_AUDIO_CORE_GDSCR_SAVE_SHFT                                                                                0x9
#define HWIO_LPASS_AUDIO_CORE_GDSCR_RETAIN_BMSK                                                                            0x100
#define HWIO_LPASS_AUDIO_CORE_GDSCR_RETAIN_SHFT                                                                              0x8
#define HWIO_LPASS_AUDIO_CORE_GDSCR_EN_REST_BMSK                                                                            0x80
#define HWIO_LPASS_AUDIO_CORE_GDSCR_EN_REST_SHFT                                                                             0x7
#define HWIO_LPASS_AUDIO_CORE_GDSCR_EN_FEW_BMSK                                                                             0x40
#define HWIO_LPASS_AUDIO_CORE_GDSCR_EN_FEW_SHFT                                                                              0x6
#define HWIO_LPASS_AUDIO_CORE_GDSCR_CLAMP_IO_BMSK                                                                           0x20
#define HWIO_LPASS_AUDIO_CORE_GDSCR_CLAMP_IO_SHFT                                                                            0x5
#define HWIO_LPASS_AUDIO_CORE_GDSCR_CLK_DISABLE_BMSK                                                                        0x10
#define HWIO_LPASS_AUDIO_CORE_GDSCR_CLK_DISABLE_SHFT                                                                         0x4
#define HWIO_LPASS_AUDIO_CORE_GDSCR_PD_ARES_BMSK                                                                             0x8
#define HWIO_LPASS_AUDIO_CORE_GDSCR_PD_ARES_SHFT                                                                             0x3
#define HWIO_LPASS_AUDIO_CORE_GDSCR_SW_OVERRIDE_BMSK                                                                         0x4
#define HWIO_LPASS_AUDIO_CORE_GDSCR_SW_OVERRIDE_SHFT                                                                         0x2
#define HWIO_LPASS_AUDIO_CORE_GDSCR_HW_CONTROL_BMSK                                                                          0x2
#define HWIO_LPASS_AUDIO_CORE_GDSCR_HW_CONTROL_SHFT                                                                          0x1
#define HWIO_LPASS_AUDIO_CORE_GDSCR_SW_COLLAPSE_BMSK                                                                         0x1
#define HWIO_LPASS_AUDIO_CORE_GDSCR_SW_COLLAPSE_SHFT                                                                         0x0

#define HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_ADDR                                                                       (LPASS_CC_REG_BASE      + 0x0000b004)
#define HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_OFFS                                                                       (LPASS_CC_REG_BASE_OFFS + 0x0000b004)
#define HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_RMSK                                                                       0x80000003
#define HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_CLK_OFF_BMSK                                                               0x80000000
#define HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_CLK_OFF_SHFT                                                                     0x1f
#define HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_HW_CTL_BMSK                                                                       0x2
#define HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_HW_CTL_SHFT                                                                       0x1
#define HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_CLK_ENABLE_BMSK                                                                   0x1
#define HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_CLK_ENABLE_SHFT                                                                   0x0

#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_ADDR                                                                        (LPASS_CC_REG_BASE      + 0x0000b008)
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_OFFS                                                                        (LPASS_CC_REG_BASE_OFFS + 0x0000b008)
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_RMSK                                                                        0xffffffff
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_ADDR, HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_RMSK)
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_IN)
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_POWER_ON_STATUS_BMSK                                                        0x80000000
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_POWER_ON_STATUS_SHFT                                                              0x1f
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_HALT1_PWR_DOWN_ACK_STATUS_BMSK                                              0x78000000
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_HALT1_PWR_DOWN_ACK_STATUS_SHFT                                                    0x1b
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_HALT1_PWR_UP_ACK_STATUS_BMSK                                                 0x7800000
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_HALT1_PWR_UP_ACK_STATUS_SHFT                                                      0x17
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_HALT2_PWR_DOWN_ACK_STATUS_BMSK                                                0x780000
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_HALT2_PWR_DOWN_ACK_STATUS_SHFT                                                    0x13
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_HALT2_PWR_UP_ACK_STATUS_BMSK                                                   0x78000
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_HALT2_PWR_UP_ACK_STATUS_SHFT                                                       0xf
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_COLLAPSE_OUT_BMSK                                                               0x4000
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_COLLAPSE_OUT_SHFT                                                                  0xe
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_RESERVE_BITS13_BMSK                                                             0x2000
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_RESERVE_BITS13_SHFT                                                                0xd
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_HALT_ACK_TIME_OUT_BMSK                                                          0x1fe0
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_HALT_ACK_TIME_OUT_SHFT                                                             0x5
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_GDS_HW_STATE_BMSK                                                                 0x1e
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_GDS_HW_STATE_SHFT                                                                  0x1
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_SW_OVERRIDE_BMSK                                                                   0x1
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_SW_OVERRIDE_SHFT                                                                   0x0

#define HWIO_LPASS_AUDIO_CORE_GDSCR_VOTE_ADDR                                                                         (LPASS_CC_REG_BASE      + 0x0000c000)
#define HWIO_LPASS_AUDIO_CORE_GDSCR_VOTE_OFFS                                                                         (LPASS_CC_REG_BASE_OFFS + 0x0000c000)
#define HWIO_LPASS_AUDIO_CORE_GDSCR_VOTE_RMSK                                                                                0x3
#define HWIO_LPASS_AUDIO_CORE_GDSCR_VOTE_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_GDSCR_VOTE_ADDR, HWIO_LPASS_AUDIO_CORE_GDSCR_VOTE_RMSK)
#define HWIO_LPASS_AUDIO_CORE_GDSCR_VOTE_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_GDSCR_VOTE_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_GDSCR_VOTE_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_GDSCR_VOTE_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_GDSCR_VOTE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_GDSCR_VOTE_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_GDSCR_VOTE_IN)
#define HWIO_LPASS_AUDIO_CORE_GDSCR_VOTE_RETENTION_ENABLE_VOTE_BMSK                                                          0x2
#define HWIO_LPASS_AUDIO_CORE_GDSCR_VOTE_RETENTION_ENABLE_VOTE_SHFT                                                          0x1
#define HWIO_LPASS_AUDIO_CORE_GDSCR_VOTE_SW_OVERRIDE_VOTE_BMSK                                                               0x1
#define HWIO_LPASS_AUDIO_CORE_GDSCR_VOTE_SW_OVERRIDE_VOTE_SHFT                                                               0x0

#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x00010000)
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_OFFS                                                                            (LPASS_CC_REG_BASE_OFFS + 0x00010000)
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_RMSK                                                                            0x800000f3
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PRI_CMD_RCGR_ADDR, HWIO_LPASS_LPAIF_PRI_CMD_RCGR_RMSK)
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PRI_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PRI_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PRI_CMD_RCGR_ADDR,m,v,HWIO_LPASS_LPAIF_PRI_CMD_RCGR_IN)
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_ROOT_OFF_BMSK                                                                   0x80000000
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_ROOT_OFF_SHFT                                                                         0x1f
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_DIRTY_D_BMSK                                                                          0x80
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_DIRTY_D_SHFT                                                                           0x7
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_DIRTY_N_BMSK                                                                          0x40
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_DIRTY_N_SHFT                                                                           0x6
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_DIRTY_M_BMSK                                                                          0x20
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_DIRTY_M_SHFT                                                                           0x5
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                   0x10
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                    0x4
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_ROOT_EN_BMSK                                                                           0x2
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_ROOT_EN_SHFT                                                                           0x1
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_UPDATE_BMSK                                                                            0x1
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_UPDATE_SHFT                                                                            0x0

#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x00010004)
#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_OFFS                                                                            (LPASS_CC_REG_BASE_OFFS + 0x00010004)
#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_RMSK                                                                                0x771f
#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PRI_CFG_RCGR_ADDR, HWIO_LPASS_LPAIF_PRI_CFG_RCGR_RMSK)
#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PRI_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PRI_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PRI_CFG_RCGR_ADDR,m,v,HWIO_LPASS_LPAIF_PRI_CFG_RCGR_IN)
#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                    0x4000
#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                       0xe
#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_MODE_BMSK                                                                           0x3000
#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_MODE_SHFT                                                                              0xc
#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_SRC_SEL_BMSK                                                                         0x700
#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_SRC_SEL_SHFT                                                                           0x8
#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_SRC_DIV_BMSK                                                                          0x1f
#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_SRC_DIV_SHFT                                                                           0x0

#define HWIO_LPASS_LPAIF_PRI_M_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x00010008)
#define HWIO_LPASS_LPAIF_PRI_M_OFFS                                                                                   (LPASS_CC_REG_BASE_OFFS + 0x00010008)
#define HWIO_LPASS_LPAIF_PRI_M_RMSK                                                                                       0xffff
#define HWIO_LPASS_LPAIF_PRI_M_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PRI_M_ADDR, HWIO_LPASS_LPAIF_PRI_M_RMSK)
#define HWIO_LPASS_LPAIF_PRI_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PRI_M_ADDR, m)
#define HWIO_LPASS_LPAIF_PRI_M_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PRI_M_ADDR,v)
#define HWIO_LPASS_LPAIF_PRI_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PRI_M_ADDR,m,v,HWIO_LPASS_LPAIF_PRI_M_IN)
#define HWIO_LPASS_LPAIF_PRI_M_M_BMSK                                                                                     0xffff
#define HWIO_LPASS_LPAIF_PRI_M_M_SHFT                                                                                        0x0

#define HWIO_LPASS_LPAIF_PRI_N_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x0001000c)
#define HWIO_LPASS_LPAIF_PRI_N_OFFS                                                                                   (LPASS_CC_REG_BASE_OFFS + 0x0001000c)
#define HWIO_LPASS_LPAIF_PRI_N_RMSK                                                                                       0xffff
#define HWIO_LPASS_LPAIF_PRI_N_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PRI_N_ADDR, HWIO_LPASS_LPAIF_PRI_N_RMSK)
#define HWIO_LPASS_LPAIF_PRI_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PRI_N_ADDR, m)
#define HWIO_LPASS_LPAIF_PRI_N_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PRI_N_ADDR,v)
#define HWIO_LPASS_LPAIF_PRI_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PRI_N_ADDR,m,v,HWIO_LPASS_LPAIF_PRI_N_IN)
#define HWIO_LPASS_LPAIF_PRI_N_NOT_N_MINUS_M_BMSK                                                                         0xffff
#define HWIO_LPASS_LPAIF_PRI_N_NOT_N_MINUS_M_SHFT                                                                            0x0

#define HWIO_LPASS_LPAIF_PRI_D_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x00010010)
#define HWIO_LPASS_LPAIF_PRI_D_OFFS                                                                                   (LPASS_CC_REG_BASE_OFFS + 0x00010010)
#define HWIO_LPASS_LPAIF_PRI_D_RMSK                                                                                       0xffff
#define HWIO_LPASS_LPAIF_PRI_D_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PRI_D_ADDR, HWIO_LPASS_LPAIF_PRI_D_RMSK)
#define HWIO_LPASS_LPAIF_PRI_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PRI_D_ADDR, m)
#define HWIO_LPASS_LPAIF_PRI_D_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PRI_D_ADDR,v)
#define HWIO_LPASS_LPAIF_PRI_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PRI_D_ADDR,m,v,HWIO_LPASS_LPAIF_PRI_D_IN)
#define HWIO_LPASS_LPAIF_PRI_D_NOT_2D_BMSK                                                                                0xffff
#define HWIO_LPASS_LPAIF_PRI_D_NOT_2D_SHFT                                                                                   0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_ADDR                                                                 (LPASS_CC_REG_BASE      + 0x00010014)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_OFFS                                                                 (LPASS_CC_REG_BASE_OFFS + 0x00010014)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_RMSK                                                                 0x80000003
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_CLK_OFF_BMSK                                                         0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_CLK_OFF_SHFT                                                               0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_HW_CTL_BMSK                                                                 0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_HW_CTL_SHFT                                                                 0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_CLK_ENABLE_BMSK                                                             0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_CLK_ENABLE_SHFT                                                             0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_ADDR                                                                (LPASS_CC_REG_BASE      + 0x00010018)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_OFFS                                                                (LPASS_CC_REG_BASE_OFFS + 0x00010018)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_RMSK                                                                0x81ff0003
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_CLK_OFF_BMSK                                                        0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_CLK_OFF_SHFT                                                              0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_CLK_DIV_BMSK                                                         0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_CLK_DIV_SHFT                                                              0x10
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_HW_CTL_BMSK                                                                0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_HW_CTL_SHFT                                                                0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_CLK_ENABLE_BMSK                                                            0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_CLK_ENABLE_SHFT                                                            0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_ADDR                                                                (LPASS_CC_REG_BASE      + 0x0001001c)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_OFFS                                                                (LPASS_CC_REG_BASE_OFFS + 0x0001001c)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_RMSK                                                                0x80000003
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_CLK_OFF_BMSK                                                        0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_CLK_OFF_SHFT                                                              0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_HW_CTL_BMSK                                                                0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_HW_CTL_SHFT                                                                0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_CLK_ENABLE_BMSK                                                            0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_CLK_ENABLE_SHFT                                                            0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_CLK_INV_ADDR                                                                  (LPASS_CC_REG_BASE      + 0x00010020)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_CLK_INV_OFFS                                                                  (LPASS_CC_REG_BASE_OFFS + 0x00010020)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_CLK_INV_RMSK                                                                         0x3
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_CLK_INV_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_CLK_INV_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_CLK_INV_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_CLK_INV_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_CLK_INV_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_CLK_INV_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_CLK_INV_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_CLK_INV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_CLK_INV_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_CLK_INV_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_CLK_INV_INV_EXT_CLK_BMSK                                                             0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_CLK_INV_INV_EXT_CLK_SHFT                                                             0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_CLK_INV_INV_INT_CLK_BMSK                                                             0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_CLK_INV_INV_INT_CLK_SHFT                                                             0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_ADDR                                                           (LPASS_CC_REG_BASE      + 0x00010024)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_OFFS                                                           (LPASS_CC_REG_BASE_OFFS + 0x00010024)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_RMSK                                                           0x80007f13
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_CLK_INACTIVE_IRQ_BMSK                                          0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_CLK_INACTIVE_IRQ_SHFT                                                0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_CLK_COUNTER_VALUE_BMSK                                             0x7f00
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_CLK_COUNTER_VALUE_SHFT                                                0x8
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_IRQ_CLEAR_BMSK                                                       0x10
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_IRQ_CLEAR_SHFT                                                        0x4
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_CLK_COUNTER_EN_BMSK                                                   0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_CLK_COUNTER_EN_SHFT                                                   0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_IRQ_EN_BMSK                                                           0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_IRQ_EN_SHFT                                                           0x0

#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x00011000)
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_OFFS                                                                            (LPASS_CC_REG_BASE_OFFS + 0x00011000)
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_RMSK                                                                            0x800000f3
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_SEC_CMD_RCGR_ADDR, HWIO_LPASS_LPAIF_SEC_CMD_RCGR_RMSK)
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_SEC_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_SEC_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_SEC_CMD_RCGR_ADDR,m,v,HWIO_LPASS_LPAIF_SEC_CMD_RCGR_IN)
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_ROOT_OFF_BMSK                                                                   0x80000000
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_ROOT_OFF_SHFT                                                                         0x1f
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_DIRTY_D_BMSK                                                                          0x80
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_DIRTY_D_SHFT                                                                           0x7
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_DIRTY_N_BMSK                                                                          0x40
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_DIRTY_N_SHFT                                                                           0x6
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_DIRTY_M_BMSK                                                                          0x20
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_DIRTY_M_SHFT                                                                           0x5
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                   0x10
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                    0x4
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_ROOT_EN_BMSK                                                                           0x2
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_ROOT_EN_SHFT                                                                           0x1
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_UPDATE_BMSK                                                                            0x1
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_UPDATE_SHFT                                                                            0x0

#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x00011004)
#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_OFFS                                                                            (LPASS_CC_REG_BASE_OFFS + 0x00011004)
#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_RMSK                                                                                0x771f
#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_SEC_CFG_RCGR_ADDR, HWIO_LPASS_LPAIF_SEC_CFG_RCGR_RMSK)
#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_SEC_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_SEC_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_SEC_CFG_RCGR_ADDR,m,v,HWIO_LPASS_LPAIF_SEC_CFG_RCGR_IN)
#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                    0x4000
#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                       0xe
#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_MODE_BMSK                                                                           0x3000
#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_MODE_SHFT                                                                              0xc
#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_SRC_SEL_BMSK                                                                         0x700
#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_SRC_SEL_SHFT                                                                           0x8
#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_SRC_DIV_BMSK                                                                          0x1f
#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_SRC_DIV_SHFT                                                                           0x0

#define HWIO_LPASS_LPAIF_SEC_M_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x00011008)
#define HWIO_LPASS_LPAIF_SEC_M_OFFS                                                                                   (LPASS_CC_REG_BASE_OFFS + 0x00011008)
#define HWIO_LPASS_LPAIF_SEC_M_RMSK                                                                                       0xffff
#define HWIO_LPASS_LPAIF_SEC_M_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_SEC_M_ADDR, HWIO_LPASS_LPAIF_SEC_M_RMSK)
#define HWIO_LPASS_LPAIF_SEC_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_SEC_M_ADDR, m)
#define HWIO_LPASS_LPAIF_SEC_M_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_SEC_M_ADDR,v)
#define HWIO_LPASS_LPAIF_SEC_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_SEC_M_ADDR,m,v,HWIO_LPASS_LPAIF_SEC_M_IN)
#define HWIO_LPASS_LPAIF_SEC_M_M_BMSK                                                                                     0xffff
#define HWIO_LPASS_LPAIF_SEC_M_M_SHFT                                                                                        0x0

#define HWIO_LPASS_LPAIF_SEC_N_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x0001100c)
#define HWIO_LPASS_LPAIF_SEC_N_OFFS                                                                                   (LPASS_CC_REG_BASE_OFFS + 0x0001100c)
#define HWIO_LPASS_LPAIF_SEC_N_RMSK                                                                                       0xffff
#define HWIO_LPASS_LPAIF_SEC_N_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_SEC_N_ADDR, HWIO_LPASS_LPAIF_SEC_N_RMSK)
#define HWIO_LPASS_LPAIF_SEC_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_SEC_N_ADDR, m)
#define HWIO_LPASS_LPAIF_SEC_N_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_SEC_N_ADDR,v)
#define HWIO_LPASS_LPAIF_SEC_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_SEC_N_ADDR,m,v,HWIO_LPASS_LPAIF_SEC_N_IN)
#define HWIO_LPASS_LPAIF_SEC_N_NOT_N_MINUS_M_BMSK                                                                         0xffff
#define HWIO_LPASS_LPAIF_SEC_N_NOT_N_MINUS_M_SHFT                                                                            0x0

#define HWIO_LPASS_LPAIF_SEC_D_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x00011010)
#define HWIO_LPASS_LPAIF_SEC_D_OFFS                                                                                   (LPASS_CC_REG_BASE_OFFS + 0x00011010)
#define HWIO_LPASS_LPAIF_SEC_D_RMSK                                                                                       0xffff
#define HWIO_LPASS_LPAIF_SEC_D_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_SEC_D_ADDR, HWIO_LPASS_LPAIF_SEC_D_RMSK)
#define HWIO_LPASS_LPAIF_SEC_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_SEC_D_ADDR, m)
#define HWIO_LPASS_LPAIF_SEC_D_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_SEC_D_ADDR,v)
#define HWIO_LPASS_LPAIF_SEC_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_SEC_D_ADDR,m,v,HWIO_LPASS_LPAIF_SEC_D_IN)
#define HWIO_LPASS_LPAIF_SEC_D_NOT_2D_BMSK                                                                                0xffff
#define HWIO_LPASS_LPAIF_SEC_D_NOT_2D_SHFT                                                                                   0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_ADDR                                                                 (LPASS_CC_REG_BASE      + 0x00011014)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_OFFS                                                                 (LPASS_CC_REG_BASE_OFFS + 0x00011014)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_RMSK                                                                 0x80000003
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_CLK_OFF_BMSK                                                         0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_CLK_OFF_SHFT                                                               0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_HW_CTL_BMSK                                                                 0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_HW_CTL_SHFT                                                                 0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_CLK_ENABLE_BMSK                                                             0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_CLK_ENABLE_SHFT                                                             0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_ADDR                                                                (LPASS_CC_REG_BASE      + 0x00011018)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_OFFS                                                                (LPASS_CC_REG_BASE_OFFS + 0x00011018)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_RMSK                                                                0x81ff0003
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_CLK_OFF_BMSK                                                        0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_CLK_OFF_SHFT                                                              0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_CLK_DIV_BMSK                                                         0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_CLK_DIV_SHFT                                                              0x10
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_HW_CTL_BMSK                                                                0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_HW_CTL_SHFT                                                                0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_CLK_ENABLE_BMSK                                                            0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_CLK_ENABLE_SHFT                                                            0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_ADDR                                                                (LPASS_CC_REG_BASE      + 0x0001101c)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_OFFS                                                                (LPASS_CC_REG_BASE_OFFS + 0x0001101c)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_RMSK                                                                0x80000003
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_CLK_OFF_BMSK                                                        0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_CLK_OFF_SHFT                                                              0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_HW_CTL_BMSK                                                                0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_HW_CTL_SHFT                                                                0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_CLK_ENABLE_BMSK                                                            0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_CLK_ENABLE_SHFT                                                            0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_CLK_INV_ADDR                                                                  (LPASS_CC_REG_BASE      + 0x00011020)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_CLK_INV_OFFS                                                                  (LPASS_CC_REG_BASE_OFFS + 0x00011020)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_CLK_INV_RMSK                                                                         0x3
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_CLK_INV_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_CLK_INV_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_CLK_INV_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_CLK_INV_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_CLK_INV_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_CLK_INV_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_CLK_INV_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_CLK_INV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_CLK_INV_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_CLK_INV_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_CLK_INV_INV_EXT_CLK_BMSK                                                             0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_CLK_INV_INV_EXT_CLK_SHFT                                                             0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_CLK_INV_INV_INT_CLK_BMSK                                                             0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_CLK_INV_INV_INT_CLK_SHFT                                                             0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_ADDR                                                           (LPASS_CC_REG_BASE      + 0x00011024)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_OFFS                                                           (LPASS_CC_REG_BASE_OFFS + 0x00011024)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_RMSK                                                           0x80007f13
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_CLK_INACTIVE_IRQ_BMSK                                          0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_CLK_INACTIVE_IRQ_SHFT                                                0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_CLK_COUNTER_VALUE_BMSK                                             0x7f00
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_CLK_COUNTER_VALUE_SHFT                                                0x8
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_IRQ_CLEAR_BMSK                                                       0x10
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_IRQ_CLEAR_SHFT                                                        0x4
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_CLK_COUNTER_EN_BMSK                                                   0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_CLK_COUNTER_EN_SHFT                                                   0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_IRQ_EN_BMSK                                                           0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_IRQ_EN_SHFT                                                           0x0

#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x00012000)
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_OFFS                                                                            (LPASS_CC_REG_BASE_OFFS + 0x00012000)
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_RMSK                                                                            0x800000f3
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_TER_CMD_RCGR_ADDR, HWIO_LPASS_LPAIF_TER_CMD_RCGR_RMSK)
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_TER_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_TER_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_TER_CMD_RCGR_ADDR,m,v,HWIO_LPASS_LPAIF_TER_CMD_RCGR_IN)
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_ROOT_OFF_BMSK                                                                   0x80000000
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_ROOT_OFF_SHFT                                                                         0x1f
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_DIRTY_D_BMSK                                                                          0x80
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_DIRTY_D_SHFT                                                                           0x7
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_DIRTY_N_BMSK                                                                          0x40
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_DIRTY_N_SHFT                                                                           0x6
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_DIRTY_M_BMSK                                                                          0x20
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_DIRTY_M_SHFT                                                                           0x5
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                   0x10
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                    0x4
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_ROOT_EN_BMSK                                                                           0x2
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_ROOT_EN_SHFT                                                                           0x1
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_UPDATE_BMSK                                                                            0x1
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_UPDATE_SHFT                                                                            0x0

#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x00012004)
#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_OFFS                                                                            (LPASS_CC_REG_BASE_OFFS + 0x00012004)
#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_RMSK                                                                                0x771f
#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_TER_CFG_RCGR_ADDR, HWIO_LPASS_LPAIF_TER_CFG_RCGR_RMSK)
#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_TER_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_TER_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_TER_CFG_RCGR_ADDR,m,v,HWIO_LPASS_LPAIF_TER_CFG_RCGR_IN)
#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                    0x4000
#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                       0xe
#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_MODE_BMSK                                                                           0x3000
#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_MODE_SHFT                                                                              0xc
#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_SRC_SEL_BMSK                                                                         0x700
#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_SRC_SEL_SHFT                                                                           0x8
#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_SRC_DIV_BMSK                                                                          0x1f
#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_SRC_DIV_SHFT                                                                           0x0

#define HWIO_LPASS_LPAIF_TER_M_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x00012008)
#define HWIO_LPASS_LPAIF_TER_M_OFFS                                                                                   (LPASS_CC_REG_BASE_OFFS + 0x00012008)
#define HWIO_LPASS_LPAIF_TER_M_RMSK                                                                                       0xffff
#define HWIO_LPASS_LPAIF_TER_M_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_TER_M_ADDR, HWIO_LPASS_LPAIF_TER_M_RMSK)
#define HWIO_LPASS_LPAIF_TER_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_TER_M_ADDR, m)
#define HWIO_LPASS_LPAIF_TER_M_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_TER_M_ADDR,v)
#define HWIO_LPASS_LPAIF_TER_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_TER_M_ADDR,m,v,HWIO_LPASS_LPAIF_TER_M_IN)
#define HWIO_LPASS_LPAIF_TER_M_M_BMSK                                                                                     0xffff
#define HWIO_LPASS_LPAIF_TER_M_M_SHFT                                                                                        0x0

#define HWIO_LPASS_LPAIF_TER_N_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x0001200c)
#define HWIO_LPASS_LPAIF_TER_N_OFFS                                                                                   (LPASS_CC_REG_BASE_OFFS + 0x0001200c)
#define HWIO_LPASS_LPAIF_TER_N_RMSK                                                                                       0xffff
#define HWIO_LPASS_LPAIF_TER_N_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_TER_N_ADDR, HWIO_LPASS_LPAIF_TER_N_RMSK)
#define HWIO_LPASS_LPAIF_TER_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_TER_N_ADDR, m)
#define HWIO_LPASS_LPAIF_TER_N_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_TER_N_ADDR,v)
#define HWIO_LPASS_LPAIF_TER_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_TER_N_ADDR,m,v,HWIO_LPASS_LPAIF_TER_N_IN)
#define HWIO_LPASS_LPAIF_TER_N_NOT_N_MINUS_M_BMSK                                                                         0xffff
#define HWIO_LPASS_LPAIF_TER_N_NOT_N_MINUS_M_SHFT                                                                            0x0

#define HWIO_LPASS_LPAIF_TER_D_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x00012010)
#define HWIO_LPASS_LPAIF_TER_D_OFFS                                                                                   (LPASS_CC_REG_BASE_OFFS + 0x00012010)
#define HWIO_LPASS_LPAIF_TER_D_RMSK                                                                                       0xffff
#define HWIO_LPASS_LPAIF_TER_D_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_TER_D_ADDR, HWIO_LPASS_LPAIF_TER_D_RMSK)
#define HWIO_LPASS_LPAIF_TER_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_TER_D_ADDR, m)
#define HWIO_LPASS_LPAIF_TER_D_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_TER_D_ADDR,v)
#define HWIO_LPASS_LPAIF_TER_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_TER_D_ADDR,m,v,HWIO_LPASS_LPAIF_TER_D_IN)
#define HWIO_LPASS_LPAIF_TER_D_NOT_2D_BMSK                                                                                0xffff
#define HWIO_LPASS_LPAIF_TER_D_NOT_2D_SHFT                                                                                   0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_ADDR                                                                 (LPASS_CC_REG_BASE      + 0x00012014)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_OFFS                                                                 (LPASS_CC_REG_BASE_OFFS + 0x00012014)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_RMSK                                                                 0x80000003
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_CLK_OFF_BMSK                                                         0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_CLK_OFF_SHFT                                                               0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_HW_CTL_BMSK                                                                 0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_HW_CTL_SHFT                                                                 0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_CLK_ENABLE_BMSK                                                             0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_CLK_ENABLE_SHFT                                                             0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_ADDR                                                                (LPASS_CC_REG_BASE      + 0x00012018)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_OFFS                                                                (LPASS_CC_REG_BASE_OFFS + 0x00012018)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_RMSK                                                                0x81ff0003
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_CLK_OFF_BMSK                                                        0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_CLK_OFF_SHFT                                                              0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_CLK_DIV_BMSK                                                         0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_CLK_DIV_SHFT                                                              0x10
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_HW_CTL_BMSK                                                                0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_HW_CTL_SHFT                                                                0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_CLK_ENABLE_BMSK                                                            0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_CLK_ENABLE_SHFT                                                            0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_ADDR                                                                (LPASS_CC_REG_BASE      + 0x0001201c)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_OFFS                                                                (LPASS_CC_REG_BASE_OFFS + 0x0001201c)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_RMSK                                                                0x80000003
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_CLK_OFF_BMSK                                                        0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_CLK_OFF_SHFT                                                              0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_HW_CTL_BMSK                                                                0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_HW_CTL_SHFT                                                                0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_CLK_ENABLE_BMSK                                                            0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_CLK_ENABLE_SHFT                                                            0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_CLK_INV_ADDR                                                                  (LPASS_CC_REG_BASE      + 0x00012020)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_CLK_INV_OFFS                                                                  (LPASS_CC_REG_BASE_OFFS + 0x00012020)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_CLK_INV_RMSK                                                                         0x3
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_CLK_INV_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_CLK_INV_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_TER_CLK_INV_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_CLK_INV_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_CLK_INV_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_CLK_INV_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_CLK_INV_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_CLK_INV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_CLK_INV_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_TER_CLK_INV_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_CLK_INV_INV_EXT_CLK_BMSK                                                             0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_CLK_INV_INV_EXT_CLK_SHFT                                                             0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_CLK_INV_INV_INT_CLK_BMSK                                                             0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_CLK_INV_INV_INT_CLK_SHFT                                                             0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_ADDR                                                           (LPASS_CC_REG_BASE      + 0x00012024)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_OFFS                                                           (LPASS_CC_REG_BASE_OFFS + 0x00012024)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_RMSK                                                           0x80007f13
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_CLK_INACTIVE_IRQ_BMSK                                          0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_CLK_INACTIVE_IRQ_SHFT                                                0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_CLK_COUNTER_VALUE_BMSK                                             0x7f00
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_CLK_COUNTER_VALUE_SHFT                                                0x8
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_IRQ_CLEAR_BMSK                                                       0x10
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_IRQ_CLEAR_SHFT                                                        0x4
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_CLK_COUNTER_EN_BMSK                                                   0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_CLK_COUNTER_EN_SHFT                                                   0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_IRQ_EN_BMSK                                                           0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_IRQ_EN_SHFT                                                           0x0

#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_ADDR                                                                           (LPASS_CC_REG_BASE      + 0x00013000)
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_OFFS                                                                           (LPASS_CC_REG_BASE_OFFS + 0x00013000)
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_RMSK                                                                           0x800000f3
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_ADDR, HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_RMSK)
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_ADDR,m,v,HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_IN)
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_ROOT_OFF_BMSK                                                                  0x80000000
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_ROOT_OFF_SHFT                                                                        0x1f
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_DIRTY_D_BMSK                                                                         0x80
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_DIRTY_D_SHFT                                                                          0x7
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_DIRTY_N_BMSK                                                                         0x40
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_DIRTY_N_SHFT                                                                          0x6
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_DIRTY_M_BMSK                                                                         0x20
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_DIRTY_M_SHFT                                                                          0x5
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                  0x10
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                   0x4
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_ROOT_EN_BMSK                                                                          0x2
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_ROOT_EN_SHFT                                                                          0x1
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_UPDATE_BMSK                                                                           0x1
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_UPDATE_SHFT                                                                           0x0

#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_ADDR                                                                           (LPASS_CC_REG_BASE      + 0x00013004)
#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_OFFS                                                                           (LPASS_CC_REG_BASE_OFFS + 0x00013004)
#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_RMSK                                                                               0x771f
#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_ADDR, HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_RMSK)
#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_ADDR,m,v,HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_IN)
#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                   0x4000
#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                      0xe
#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_MODE_BMSK                                                                          0x3000
#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_MODE_SHFT                                                                             0xc
#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_SRC_SEL_BMSK                                                                        0x700
#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_SRC_SEL_SHFT                                                                          0x8
#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_SRC_DIV_BMSK                                                                         0x1f
#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_SRC_DIV_SHFT                                                                          0x0

#define HWIO_LPASS_LPAIF_QUAD_M_ADDR                                                                                  (LPASS_CC_REG_BASE      + 0x00013008)
#define HWIO_LPASS_LPAIF_QUAD_M_OFFS                                                                                  (LPASS_CC_REG_BASE_OFFS + 0x00013008)
#define HWIO_LPASS_LPAIF_QUAD_M_RMSK                                                                                      0xffff
#define HWIO_LPASS_LPAIF_QUAD_M_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_QUAD_M_ADDR, HWIO_LPASS_LPAIF_QUAD_M_RMSK)
#define HWIO_LPASS_LPAIF_QUAD_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_QUAD_M_ADDR, m)
#define HWIO_LPASS_LPAIF_QUAD_M_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_QUAD_M_ADDR,v)
#define HWIO_LPASS_LPAIF_QUAD_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_QUAD_M_ADDR,m,v,HWIO_LPASS_LPAIF_QUAD_M_IN)
#define HWIO_LPASS_LPAIF_QUAD_M_M_BMSK                                                                                    0xffff
#define HWIO_LPASS_LPAIF_QUAD_M_M_SHFT                                                                                       0x0

#define HWIO_LPASS_LPAIF_QUAD_N_ADDR                                                                                  (LPASS_CC_REG_BASE      + 0x0001300c)
#define HWIO_LPASS_LPAIF_QUAD_N_OFFS                                                                                  (LPASS_CC_REG_BASE_OFFS + 0x0001300c)
#define HWIO_LPASS_LPAIF_QUAD_N_RMSK                                                                                      0xffff
#define HWIO_LPASS_LPAIF_QUAD_N_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_QUAD_N_ADDR, HWIO_LPASS_LPAIF_QUAD_N_RMSK)
#define HWIO_LPASS_LPAIF_QUAD_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_QUAD_N_ADDR, m)
#define HWIO_LPASS_LPAIF_QUAD_N_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_QUAD_N_ADDR,v)
#define HWIO_LPASS_LPAIF_QUAD_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_QUAD_N_ADDR,m,v,HWIO_LPASS_LPAIF_QUAD_N_IN)
#define HWIO_LPASS_LPAIF_QUAD_N_NOT_N_MINUS_M_BMSK                                                                        0xffff
#define HWIO_LPASS_LPAIF_QUAD_N_NOT_N_MINUS_M_SHFT                                                                           0x0

#define HWIO_LPASS_LPAIF_QUAD_D_ADDR                                                                                  (LPASS_CC_REG_BASE      + 0x00013010)
#define HWIO_LPASS_LPAIF_QUAD_D_OFFS                                                                                  (LPASS_CC_REG_BASE_OFFS + 0x00013010)
#define HWIO_LPASS_LPAIF_QUAD_D_RMSK                                                                                      0xffff
#define HWIO_LPASS_LPAIF_QUAD_D_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_QUAD_D_ADDR, HWIO_LPASS_LPAIF_QUAD_D_RMSK)
#define HWIO_LPASS_LPAIF_QUAD_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_QUAD_D_ADDR, m)
#define HWIO_LPASS_LPAIF_QUAD_D_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_QUAD_D_ADDR,v)
#define HWIO_LPASS_LPAIF_QUAD_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_QUAD_D_ADDR,m,v,HWIO_LPASS_LPAIF_QUAD_D_IN)
#define HWIO_LPASS_LPAIF_QUAD_D_NOT_2D_BMSK                                                                               0xffff
#define HWIO_LPASS_LPAIF_QUAD_D_NOT_2D_SHFT                                                                                  0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_ADDR                                                                (LPASS_CC_REG_BASE      + 0x00013014)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_OFFS                                                                (LPASS_CC_REG_BASE_OFFS + 0x00013014)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_RMSK                                                                0x80000003
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_CLK_OFF_BMSK                                                        0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_CLK_OFF_SHFT                                                              0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_HW_CTL_BMSK                                                                0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_HW_CTL_SHFT                                                                0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_CLK_ENABLE_BMSK                                                            0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_CLK_ENABLE_SHFT                                                            0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_ADDR                                                               (LPASS_CC_REG_BASE      + 0x00013018)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_OFFS                                                               (LPASS_CC_REG_BASE_OFFS + 0x00013018)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_RMSK                                                               0x81ff0003
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_CLK_OFF_BMSK                                                       0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_CLK_OFF_SHFT                                                             0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_CLK_DIV_BMSK                                                        0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_CLK_DIV_SHFT                                                             0x10
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_HW_CTL_BMSK                                                               0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_HW_CTL_SHFT                                                               0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_CLK_ENABLE_BMSK                                                           0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_CLK_ENABLE_SHFT                                                           0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_ADDR                                                               (LPASS_CC_REG_BASE      + 0x0001301c)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_OFFS                                                               (LPASS_CC_REG_BASE_OFFS + 0x0001301c)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_RMSK                                                               0x80000003
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_CLK_OFF_BMSK                                                       0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_CLK_OFF_SHFT                                                             0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_HW_CTL_BMSK                                                               0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_HW_CTL_SHFT                                                               0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_CLK_ENABLE_BMSK                                                           0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_CLK_ENABLE_SHFT                                                           0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_CLK_INV_ADDR                                                                 (LPASS_CC_REG_BASE      + 0x00013020)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_CLK_INV_OFFS                                                                 (LPASS_CC_REG_BASE_OFFS + 0x00013020)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_CLK_INV_RMSK                                                                        0x3
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_CLK_INV_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_CLK_INV_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_CLK_INV_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_CLK_INV_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_CLK_INV_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_CLK_INV_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_CLK_INV_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_CLK_INV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_CLK_INV_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_CLK_INV_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_CLK_INV_INV_EXT_CLK_BMSK                                                            0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_CLK_INV_INV_EXT_CLK_SHFT                                                            0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_CLK_INV_INV_INT_CLK_BMSK                                                            0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_CLK_INV_INV_INT_CLK_SHFT                                                            0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_ADDR                                                          (LPASS_CC_REG_BASE      + 0x00013024)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_OFFS                                                          (LPASS_CC_REG_BASE_OFFS + 0x00013024)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_RMSK                                                          0x80007f13
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_CLK_INACTIVE_IRQ_BMSK                                         0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_CLK_INACTIVE_IRQ_SHFT                                               0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_CLK_COUNTER_VALUE_BMSK                                            0x7f00
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_CLK_COUNTER_VALUE_SHFT                                               0x8
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_IRQ_CLEAR_BMSK                                                      0x10
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_IRQ_CLEAR_SHFT                                                       0x4
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_CLK_COUNTER_EN_BMSK                                                  0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_CLK_COUNTER_EN_SHFT                                                  0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_IRQ_EN_BMSK                                                          0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_IRQ_EN_SHFT                                                          0x0

#define HWIO_LPASS_AON_CMD_RCGR_ADDR                                                                                  (LPASS_CC_REG_BASE      + 0x00014000)
#define HWIO_LPASS_AON_CMD_RCGR_OFFS                                                                                  (LPASS_CC_REG_BASE_OFFS + 0x00014000)
#define HWIO_LPASS_AON_CMD_RCGR_RMSK                                                                                  0x800000f3
#define HWIO_LPASS_AON_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_AON_CMD_RCGR_ADDR, HWIO_LPASS_AON_CMD_RCGR_RMSK)
#define HWIO_LPASS_AON_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AON_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_AON_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_AON_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_AON_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AON_CMD_RCGR_ADDR,m,v,HWIO_LPASS_AON_CMD_RCGR_IN)
#define HWIO_LPASS_AON_CMD_RCGR_ROOT_OFF_BMSK                                                                         0x80000000
#define HWIO_LPASS_AON_CMD_RCGR_ROOT_OFF_SHFT                                                                               0x1f
#define HWIO_LPASS_AON_CMD_RCGR_DIRTY_D_BMSK                                                                                0x80
#define HWIO_LPASS_AON_CMD_RCGR_DIRTY_D_SHFT                                                                                 0x7
#define HWIO_LPASS_AON_CMD_RCGR_DIRTY_N_BMSK                                                                                0x40
#define HWIO_LPASS_AON_CMD_RCGR_DIRTY_N_SHFT                                                                                 0x6
#define HWIO_LPASS_AON_CMD_RCGR_DIRTY_M_BMSK                                                                                0x20
#define HWIO_LPASS_AON_CMD_RCGR_DIRTY_M_SHFT                                                                                 0x5
#define HWIO_LPASS_AON_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                         0x10
#define HWIO_LPASS_AON_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                          0x4
#define HWIO_LPASS_AON_CMD_RCGR_ROOT_EN_BMSK                                                                                 0x2
#define HWIO_LPASS_AON_CMD_RCGR_ROOT_EN_SHFT                                                                                 0x1
#define HWIO_LPASS_AON_CMD_RCGR_UPDATE_BMSK                                                                                  0x1
#define HWIO_LPASS_AON_CMD_RCGR_UPDATE_SHFT                                                                                  0x0

#define HWIO_LPASS_AON_CFG_RCGR_ADDR                                                                                  (LPASS_CC_REG_BASE      + 0x00014004)
#define HWIO_LPASS_AON_CFG_RCGR_OFFS                                                                                  (LPASS_CC_REG_BASE_OFFS + 0x00014004)
#define HWIO_LPASS_AON_CFG_RCGR_RMSK                                                                                      0x771f
#define HWIO_LPASS_AON_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_AON_CFG_RCGR_ADDR, HWIO_LPASS_AON_CFG_RCGR_RMSK)
#define HWIO_LPASS_AON_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AON_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_AON_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_AON_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_AON_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AON_CFG_RCGR_ADDR,m,v,HWIO_LPASS_AON_CFG_RCGR_IN)
#define HWIO_LPASS_AON_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                          0x4000
#define HWIO_LPASS_AON_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                             0xe
#define HWIO_LPASS_AON_CFG_RCGR_MODE_BMSK                                                                                 0x3000
#define HWIO_LPASS_AON_CFG_RCGR_MODE_SHFT                                                                                    0xc
#define HWIO_LPASS_AON_CFG_RCGR_SRC_SEL_BMSK                                                                               0x700
#define HWIO_LPASS_AON_CFG_RCGR_SRC_SEL_SHFT                                                                                 0x8
#define HWIO_LPASS_AON_CFG_RCGR_SRC_DIV_BMSK                                                                                0x1f
#define HWIO_LPASS_AON_CFG_RCGR_SRC_DIV_SHFT                                                                                 0x0

#define HWIO_LPASS_AON_M_ADDR                                                                                         (LPASS_CC_REG_BASE      + 0x00014008)
#define HWIO_LPASS_AON_M_OFFS                                                                                         (LPASS_CC_REG_BASE_OFFS + 0x00014008)
#define HWIO_LPASS_AON_M_RMSK                                                                                               0xff
#define HWIO_LPASS_AON_M_IN          \
        in_dword_masked(HWIO_LPASS_AON_M_ADDR, HWIO_LPASS_AON_M_RMSK)
#define HWIO_LPASS_AON_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_AON_M_ADDR, m)
#define HWIO_LPASS_AON_M_OUT(v)      \
        out_dword(HWIO_LPASS_AON_M_ADDR,v)
#define HWIO_LPASS_AON_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AON_M_ADDR,m,v,HWIO_LPASS_AON_M_IN)
#define HWIO_LPASS_AON_M_M_BMSK                                                                                             0xff
#define HWIO_LPASS_AON_M_M_SHFT                                                                                              0x0

#define HWIO_LPASS_AON_N_ADDR                                                                                         (LPASS_CC_REG_BASE      + 0x0001400c)
#define HWIO_LPASS_AON_N_OFFS                                                                                         (LPASS_CC_REG_BASE_OFFS + 0x0001400c)
#define HWIO_LPASS_AON_N_RMSK                                                                                               0xff
#define HWIO_LPASS_AON_N_IN          \
        in_dword_masked(HWIO_LPASS_AON_N_ADDR, HWIO_LPASS_AON_N_RMSK)
#define HWIO_LPASS_AON_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_AON_N_ADDR, m)
#define HWIO_LPASS_AON_N_OUT(v)      \
        out_dword(HWIO_LPASS_AON_N_ADDR,v)
#define HWIO_LPASS_AON_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AON_N_ADDR,m,v,HWIO_LPASS_AON_N_IN)
#define HWIO_LPASS_AON_N_NOT_N_MINUS_M_BMSK                                                                                 0xff
#define HWIO_LPASS_AON_N_NOT_N_MINUS_M_SHFT                                                                                  0x0

#define HWIO_LPASS_AON_D_ADDR                                                                                         (LPASS_CC_REG_BASE      + 0x00014010)
#define HWIO_LPASS_AON_D_OFFS                                                                                         (LPASS_CC_REG_BASE_OFFS + 0x00014010)
#define HWIO_LPASS_AON_D_RMSK                                                                                               0xff
#define HWIO_LPASS_AON_D_IN          \
        in_dword_masked(HWIO_LPASS_AON_D_ADDR, HWIO_LPASS_AON_D_RMSK)
#define HWIO_LPASS_AON_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_AON_D_ADDR, m)
#define HWIO_LPASS_AON_D_OUT(v)      \
        out_dword(HWIO_LPASS_AON_D_ADDR,v)
#define HWIO_LPASS_AON_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AON_D_ADDR,m,v,HWIO_LPASS_AON_D_IN)
#define HWIO_LPASS_AON_D_NOT_2D_BMSK                                                                                        0xff
#define HWIO_LPASS_AON_D_NOT_2D_SHFT                                                                                         0x0

#define HWIO_LPASS_AUDIO_WRAPPER_AON_CBCR_ADDR                                                                        (LPASS_CC_REG_BASE      + 0x00014014)
#define HWIO_LPASS_AUDIO_WRAPPER_AON_CBCR_OFFS                                                                        (LPASS_CC_REG_BASE_OFFS + 0x00014014)
#define HWIO_LPASS_AUDIO_WRAPPER_AON_CBCR_RMSK                                                                        0x80000003
#define HWIO_LPASS_AUDIO_WRAPPER_AON_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_AON_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_AON_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_AON_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_AON_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_AON_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_AON_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_AON_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_AON_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_AON_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_AON_CBCR_CLK_OFF_BMSK                                                                0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_AON_CBCR_CLK_OFF_SHFT                                                                      0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_AON_CBCR_HW_CTL_BMSK                                                                        0x2
#define HWIO_LPASS_AUDIO_WRAPPER_AON_CBCR_HW_CTL_SHFT                                                                        0x1
#define HWIO_LPASS_AUDIO_WRAPPER_AON_CBCR_CLK_ENABLE_BMSK                                                                    0x1
#define HWIO_LPASS_AUDIO_WRAPPER_AON_CBCR_CLK_ENABLE_SHFT                                                                    0x0

#define HWIO_LPASS_ATIME_CMD_RCGR_ADDR                                                                                (LPASS_CC_REG_BASE      + 0x00015000)
#define HWIO_LPASS_ATIME_CMD_RCGR_OFFS                                                                                (LPASS_CC_REG_BASE_OFFS + 0x00015000)
#define HWIO_LPASS_ATIME_CMD_RCGR_RMSK                                                                                0x800000f3
#define HWIO_LPASS_ATIME_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_ATIME_CMD_RCGR_ADDR, HWIO_LPASS_ATIME_CMD_RCGR_RMSK)
#define HWIO_LPASS_ATIME_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ATIME_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_ATIME_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_ATIME_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_ATIME_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ATIME_CMD_RCGR_ADDR,m,v,HWIO_LPASS_ATIME_CMD_RCGR_IN)
#define HWIO_LPASS_ATIME_CMD_RCGR_ROOT_OFF_BMSK                                                                       0x80000000
#define HWIO_LPASS_ATIME_CMD_RCGR_ROOT_OFF_SHFT                                                                             0x1f
#define HWIO_LPASS_ATIME_CMD_RCGR_DIRTY_D_BMSK                                                                              0x80
#define HWIO_LPASS_ATIME_CMD_RCGR_DIRTY_D_SHFT                                                                               0x7
#define HWIO_LPASS_ATIME_CMD_RCGR_DIRTY_N_BMSK                                                                              0x40
#define HWIO_LPASS_ATIME_CMD_RCGR_DIRTY_N_SHFT                                                                               0x6
#define HWIO_LPASS_ATIME_CMD_RCGR_DIRTY_M_BMSK                                                                              0x20
#define HWIO_LPASS_ATIME_CMD_RCGR_DIRTY_M_SHFT                                                                               0x5
#define HWIO_LPASS_ATIME_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                       0x10
#define HWIO_LPASS_ATIME_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                        0x4
#define HWIO_LPASS_ATIME_CMD_RCGR_ROOT_EN_BMSK                                                                               0x2
#define HWIO_LPASS_ATIME_CMD_RCGR_ROOT_EN_SHFT                                                                               0x1
#define HWIO_LPASS_ATIME_CMD_RCGR_UPDATE_BMSK                                                                                0x1
#define HWIO_LPASS_ATIME_CMD_RCGR_UPDATE_SHFT                                                                                0x0

#define HWIO_LPASS_ATIME_CFG_RCGR_ADDR                                                                                (LPASS_CC_REG_BASE      + 0x00015004)
#define HWIO_LPASS_ATIME_CFG_RCGR_OFFS                                                                                (LPASS_CC_REG_BASE_OFFS + 0x00015004)
#define HWIO_LPASS_ATIME_CFG_RCGR_RMSK                                                                                    0x771f
#define HWIO_LPASS_ATIME_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_ATIME_CFG_RCGR_ADDR, HWIO_LPASS_ATIME_CFG_RCGR_RMSK)
#define HWIO_LPASS_ATIME_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ATIME_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_ATIME_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_ATIME_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_ATIME_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ATIME_CFG_RCGR_ADDR,m,v,HWIO_LPASS_ATIME_CFG_RCGR_IN)
#define HWIO_LPASS_ATIME_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                        0x4000
#define HWIO_LPASS_ATIME_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                           0xe
#define HWIO_LPASS_ATIME_CFG_RCGR_MODE_BMSK                                                                               0x3000
#define HWIO_LPASS_ATIME_CFG_RCGR_MODE_SHFT                                                                                  0xc
#define HWIO_LPASS_ATIME_CFG_RCGR_SRC_SEL_BMSK                                                                             0x700
#define HWIO_LPASS_ATIME_CFG_RCGR_SRC_SEL_SHFT                                                                               0x8
#define HWIO_LPASS_ATIME_CFG_RCGR_SRC_DIV_BMSK                                                                              0x1f
#define HWIO_LPASS_ATIME_CFG_RCGR_SRC_DIV_SHFT                                                                               0x0

#define HWIO_LPASS_ATIME_M_ADDR                                                                                       (LPASS_CC_REG_BASE      + 0x00015008)
#define HWIO_LPASS_ATIME_M_OFFS                                                                                       (LPASS_CC_REG_BASE_OFFS + 0x00015008)
#define HWIO_LPASS_ATIME_M_RMSK                                                                                             0xff
#define HWIO_LPASS_ATIME_M_IN          \
        in_dword_masked(HWIO_LPASS_ATIME_M_ADDR, HWIO_LPASS_ATIME_M_RMSK)
#define HWIO_LPASS_ATIME_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_ATIME_M_ADDR, m)
#define HWIO_LPASS_ATIME_M_OUT(v)      \
        out_dword(HWIO_LPASS_ATIME_M_ADDR,v)
#define HWIO_LPASS_ATIME_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ATIME_M_ADDR,m,v,HWIO_LPASS_ATIME_M_IN)
#define HWIO_LPASS_ATIME_M_M_BMSK                                                                                           0xff
#define HWIO_LPASS_ATIME_M_M_SHFT                                                                                            0x0

#define HWIO_LPASS_ATIME_N_ADDR                                                                                       (LPASS_CC_REG_BASE      + 0x0001500c)
#define HWIO_LPASS_ATIME_N_OFFS                                                                                       (LPASS_CC_REG_BASE_OFFS + 0x0001500c)
#define HWIO_LPASS_ATIME_N_RMSK                                                                                             0xff
#define HWIO_LPASS_ATIME_N_IN          \
        in_dword_masked(HWIO_LPASS_ATIME_N_ADDR, HWIO_LPASS_ATIME_N_RMSK)
#define HWIO_LPASS_ATIME_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_ATIME_N_ADDR, m)
#define HWIO_LPASS_ATIME_N_OUT(v)      \
        out_dword(HWIO_LPASS_ATIME_N_ADDR,v)
#define HWIO_LPASS_ATIME_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ATIME_N_ADDR,m,v,HWIO_LPASS_ATIME_N_IN)
#define HWIO_LPASS_ATIME_N_NOT_N_MINUS_M_BMSK                                                                               0xff
#define HWIO_LPASS_ATIME_N_NOT_N_MINUS_M_SHFT                                                                                0x0

#define HWIO_LPASS_ATIME_D_ADDR                                                                                       (LPASS_CC_REG_BASE      + 0x00015010)
#define HWIO_LPASS_ATIME_D_OFFS                                                                                       (LPASS_CC_REG_BASE_OFFS + 0x00015010)
#define HWIO_LPASS_ATIME_D_RMSK                                                                                             0xff
#define HWIO_LPASS_ATIME_D_IN          \
        in_dword_masked(HWIO_LPASS_ATIME_D_ADDR, HWIO_LPASS_ATIME_D_RMSK)
#define HWIO_LPASS_ATIME_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_ATIME_D_ADDR, m)
#define HWIO_LPASS_ATIME_D_OUT(v)      \
        out_dword(HWIO_LPASS_ATIME_D_ADDR,v)
#define HWIO_LPASS_ATIME_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ATIME_D_ADDR,m,v,HWIO_LPASS_ATIME_D_IN)
#define HWIO_LPASS_ATIME_D_NOT_2D_BMSK                                                                                      0xff
#define HWIO_LPASS_ATIME_D_NOT_2D_SHFT                                                                                       0x0

#define HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_CBCR_ADDR                                                                  (LPASS_CC_REG_BASE      + 0x00015014)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_CBCR_OFFS                                                                  (LPASS_CC_REG_BASE_OFFS + 0x00015014)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_CBCR_RMSK                                                                  0x80000003
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_CBCR_CLK_OFF_BMSK                                                          0x80000000
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_CBCR_CLK_OFF_SHFT                                                                0x1f
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_CBCR_HW_CTL_BMSK                                                                  0x2
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_CBCR_HW_CTL_SHFT                                                                  0x1
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_CBCR_CLK_ENABLE_BMSK                                                              0x1
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_CBCR_CLK_ENABLE_SHFT                                                              0x0

#define HWIO_LPASS_RESAMPLER_CMD_RCGR_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x00016000)
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_OFFS                                                                            (LPASS_CC_REG_BASE_OFFS + 0x00016000)
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_RMSK                                                                            0x800000f3
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_RESAMPLER_CMD_RCGR_ADDR, HWIO_LPASS_RESAMPLER_CMD_RCGR_RMSK)
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_RESAMPLER_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_RESAMPLER_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_RESAMPLER_CMD_RCGR_ADDR,m,v,HWIO_LPASS_RESAMPLER_CMD_RCGR_IN)
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_ROOT_OFF_BMSK                                                                   0x80000000
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_ROOT_OFF_SHFT                                                                         0x1f
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_DIRTY_D_BMSK                                                                          0x80
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_DIRTY_D_SHFT                                                                           0x7
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_DIRTY_N_BMSK                                                                          0x40
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_DIRTY_N_SHFT                                                                           0x6
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_DIRTY_M_BMSK                                                                          0x20
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_DIRTY_M_SHFT                                                                           0x5
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                   0x10
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                    0x4
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_ROOT_EN_BMSK                                                                           0x2
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_ROOT_EN_SHFT                                                                           0x1
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_UPDATE_BMSK                                                                            0x1
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_UPDATE_SHFT                                                                            0x0

#define HWIO_LPASS_RESAMPLER_CFG_RCGR_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x00016004)
#define HWIO_LPASS_RESAMPLER_CFG_RCGR_OFFS                                                                            (LPASS_CC_REG_BASE_OFFS + 0x00016004)
#define HWIO_LPASS_RESAMPLER_CFG_RCGR_RMSK                                                                                0x771f
#define HWIO_LPASS_RESAMPLER_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_RESAMPLER_CFG_RCGR_ADDR, HWIO_LPASS_RESAMPLER_CFG_RCGR_RMSK)
#define HWIO_LPASS_RESAMPLER_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_RESAMPLER_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_RESAMPLER_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_RESAMPLER_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_RESAMPLER_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_RESAMPLER_CFG_RCGR_ADDR,m,v,HWIO_LPASS_RESAMPLER_CFG_RCGR_IN)
#define HWIO_LPASS_RESAMPLER_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                    0x4000
#define HWIO_LPASS_RESAMPLER_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                       0xe
#define HWIO_LPASS_RESAMPLER_CFG_RCGR_MODE_BMSK                                                                           0x3000
#define HWIO_LPASS_RESAMPLER_CFG_RCGR_MODE_SHFT                                                                              0xc
#define HWIO_LPASS_RESAMPLER_CFG_RCGR_SRC_SEL_BMSK                                                                         0x700
#define HWIO_LPASS_RESAMPLER_CFG_RCGR_SRC_SEL_SHFT                                                                           0x8
#define HWIO_LPASS_RESAMPLER_CFG_RCGR_SRC_DIV_BMSK                                                                          0x1f
#define HWIO_LPASS_RESAMPLER_CFG_RCGR_SRC_DIV_SHFT                                                                           0x0

#define HWIO_LPASS_RESAMPLER_M_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x00016008)
#define HWIO_LPASS_RESAMPLER_M_OFFS                                                                                   (LPASS_CC_REG_BASE_OFFS + 0x00016008)
#define HWIO_LPASS_RESAMPLER_M_RMSK                                                                                         0xff
#define HWIO_LPASS_RESAMPLER_M_IN          \
        in_dword_masked(HWIO_LPASS_RESAMPLER_M_ADDR, HWIO_LPASS_RESAMPLER_M_RMSK)
#define HWIO_LPASS_RESAMPLER_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_RESAMPLER_M_ADDR, m)
#define HWIO_LPASS_RESAMPLER_M_OUT(v)      \
        out_dword(HWIO_LPASS_RESAMPLER_M_ADDR,v)
#define HWIO_LPASS_RESAMPLER_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_RESAMPLER_M_ADDR,m,v,HWIO_LPASS_RESAMPLER_M_IN)
#define HWIO_LPASS_RESAMPLER_M_M_BMSK                                                                                       0xff
#define HWIO_LPASS_RESAMPLER_M_M_SHFT                                                                                        0x0

#define HWIO_LPASS_RESAMPLER_N_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x0001600c)
#define HWIO_LPASS_RESAMPLER_N_OFFS                                                                                   (LPASS_CC_REG_BASE_OFFS + 0x0001600c)
#define HWIO_LPASS_RESAMPLER_N_RMSK                                                                                         0xff
#define HWIO_LPASS_RESAMPLER_N_IN          \
        in_dword_masked(HWIO_LPASS_RESAMPLER_N_ADDR, HWIO_LPASS_RESAMPLER_N_RMSK)
#define HWIO_LPASS_RESAMPLER_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_RESAMPLER_N_ADDR, m)
#define HWIO_LPASS_RESAMPLER_N_OUT(v)      \
        out_dword(HWIO_LPASS_RESAMPLER_N_ADDR,v)
#define HWIO_LPASS_RESAMPLER_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_RESAMPLER_N_ADDR,m,v,HWIO_LPASS_RESAMPLER_N_IN)
#define HWIO_LPASS_RESAMPLER_N_NOT_N_MINUS_M_BMSK                                                                           0xff
#define HWIO_LPASS_RESAMPLER_N_NOT_N_MINUS_M_SHFT                                                                            0x0

#define HWIO_LPASS_RESAMPLER_D_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x00016010)
#define HWIO_LPASS_RESAMPLER_D_OFFS                                                                                   (LPASS_CC_REG_BASE_OFFS + 0x00016010)
#define HWIO_LPASS_RESAMPLER_D_RMSK                                                                                         0xff
#define HWIO_LPASS_RESAMPLER_D_IN          \
        in_dword_masked(HWIO_LPASS_RESAMPLER_D_ADDR, HWIO_LPASS_RESAMPLER_D_RMSK)
#define HWIO_LPASS_RESAMPLER_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_RESAMPLER_D_ADDR, m)
#define HWIO_LPASS_RESAMPLER_D_OUT(v)      \
        out_dword(HWIO_LPASS_RESAMPLER_D_ADDR,v)
#define HWIO_LPASS_RESAMPLER_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_RESAMPLER_D_ADDR,m,v,HWIO_LPASS_RESAMPLER_D_IN)
#define HWIO_LPASS_RESAMPLER_D_NOT_2D_BMSK                                                                                  0xff
#define HWIO_LPASS_RESAMPLER_D_NOT_2D_SHFT                                                                                   0x0

#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_ADDR                                                                     (LPASS_CC_REG_BASE      + 0x00016014)
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_OFFS                                                                     (LPASS_CC_REG_BASE_OFFS + 0x00016014)
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_RMSK                                                                     0x80007ff3
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_CLK_OFF_BMSK                                                             0x80000000
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_CLK_OFF_SHFT                                                                   0x1f
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_FORCE_MEM_CORE_ON_BMSK                                                       0x4000
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_FORCE_MEM_CORE_ON_SHFT                                                          0xe
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_FORCE_MEM_PERIPH_ON_BMSK                                                     0x2000
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                                        0xd
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                                                    0x1000
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                                       0xc
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_WAKEUP_BMSK                                                                   0xf00
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_WAKEUP_SHFT                                                                     0x8
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_SLEEP_BMSK                                                                     0xf0
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_SLEEP_SHFT                                                                      0x4
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_HW_CTL_BMSK                                                                     0x2
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_HW_CTL_SHFT                                                                     0x1
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_CLK_ENABLE_BMSK                                                                 0x1
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_CLK_ENABLE_SHFT                                                                 0x0

#define HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_ADDR                                                                          (LPASS_CC_REG_BASE      + 0x00017000)
#define HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_OFFS                                                                          (LPASS_CC_REG_BASE_OFFS + 0x00017000)
#define HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_RMSK                                                                          0x800000f3
#define HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_ADDR, HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_RMSK)
#define HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_ADDR,m,v,HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_IN)
#define HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_ROOT_OFF_BMSK                                                                 0x80000000
#define HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_ROOT_OFF_SHFT                                                                       0x1f
#define HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_DIRTY_D_BMSK                                                                        0x80
#define HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_DIRTY_D_SHFT                                                                         0x7
#define HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_DIRTY_N_BMSK                                                                        0x40
#define HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_DIRTY_N_SHFT                                                                         0x6
#define HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_DIRTY_M_BMSK                                                                        0x20
#define HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_DIRTY_M_SHFT                                                                         0x5
#define HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                 0x10
#define HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                  0x4
#define HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_ROOT_EN_BMSK                                                                         0x2
#define HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_ROOT_EN_SHFT                                                                         0x1
#define HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_UPDATE_BMSK                                                                          0x1
#define HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_UPDATE_SHFT                                                                          0x0

#define HWIO_LPASS_AUD_SLIMBUS_CFG_RCGR_ADDR                                                                          (LPASS_CC_REG_BASE      + 0x00017004)
#define HWIO_LPASS_AUD_SLIMBUS_CFG_RCGR_OFFS                                                                          (LPASS_CC_REG_BASE_OFFS + 0x00017004)
#define HWIO_LPASS_AUD_SLIMBUS_CFG_RCGR_RMSK                                                                              0x771f
#define HWIO_LPASS_AUD_SLIMBUS_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_AUD_SLIMBUS_CFG_RCGR_ADDR, HWIO_LPASS_AUD_SLIMBUS_CFG_RCGR_RMSK)
#define HWIO_LPASS_AUD_SLIMBUS_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUD_SLIMBUS_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_AUD_SLIMBUS_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_AUD_SLIMBUS_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_AUD_SLIMBUS_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUD_SLIMBUS_CFG_RCGR_ADDR,m,v,HWIO_LPASS_AUD_SLIMBUS_CFG_RCGR_IN)
#define HWIO_LPASS_AUD_SLIMBUS_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                  0x4000
#define HWIO_LPASS_AUD_SLIMBUS_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                     0xe
#define HWIO_LPASS_AUD_SLIMBUS_CFG_RCGR_MODE_BMSK                                                                         0x3000
#define HWIO_LPASS_AUD_SLIMBUS_CFG_RCGR_MODE_SHFT                                                                            0xc
#define HWIO_LPASS_AUD_SLIMBUS_CFG_RCGR_SRC_SEL_BMSK                                                                       0x700
#define HWIO_LPASS_AUD_SLIMBUS_CFG_RCGR_SRC_SEL_SHFT                                                                         0x8
#define HWIO_LPASS_AUD_SLIMBUS_CFG_RCGR_SRC_DIV_BMSK                                                                        0x1f
#define HWIO_LPASS_AUD_SLIMBUS_CFG_RCGR_SRC_DIV_SHFT                                                                         0x0

#define HWIO_LPASS_AUD_SLIMBUS_M_ADDR                                                                                 (LPASS_CC_REG_BASE      + 0x00017008)
#define HWIO_LPASS_AUD_SLIMBUS_M_OFFS                                                                                 (LPASS_CC_REG_BASE_OFFS + 0x00017008)
#define HWIO_LPASS_AUD_SLIMBUS_M_RMSK                                                                                       0xff
#define HWIO_LPASS_AUD_SLIMBUS_M_IN          \
        in_dword_masked(HWIO_LPASS_AUD_SLIMBUS_M_ADDR, HWIO_LPASS_AUD_SLIMBUS_M_RMSK)
#define HWIO_LPASS_AUD_SLIMBUS_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUD_SLIMBUS_M_ADDR, m)
#define HWIO_LPASS_AUD_SLIMBUS_M_OUT(v)      \
        out_dword(HWIO_LPASS_AUD_SLIMBUS_M_ADDR,v)
#define HWIO_LPASS_AUD_SLIMBUS_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUD_SLIMBUS_M_ADDR,m,v,HWIO_LPASS_AUD_SLIMBUS_M_IN)
#define HWIO_LPASS_AUD_SLIMBUS_M_M_BMSK                                                                                     0xff
#define HWIO_LPASS_AUD_SLIMBUS_M_M_SHFT                                                                                      0x0

#define HWIO_LPASS_AUD_SLIMBUS_N_ADDR                                                                                 (LPASS_CC_REG_BASE      + 0x0001700c)
#define HWIO_LPASS_AUD_SLIMBUS_N_OFFS                                                                                 (LPASS_CC_REG_BASE_OFFS + 0x0001700c)
#define HWIO_LPASS_AUD_SLIMBUS_N_RMSK                                                                                       0xff
#define HWIO_LPASS_AUD_SLIMBUS_N_IN          \
        in_dword_masked(HWIO_LPASS_AUD_SLIMBUS_N_ADDR, HWIO_LPASS_AUD_SLIMBUS_N_RMSK)
#define HWIO_LPASS_AUD_SLIMBUS_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUD_SLIMBUS_N_ADDR, m)
#define HWIO_LPASS_AUD_SLIMBUS_N_OUT(v)      \
        out_dword(HWIO_LPASS_AUD_SLIMBUS_N_ADDR,v)
#define HWIO_LPASS_AUD_SLIMBUS_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUD_SLIMBUS_N_ADDR,m,v,HWIO_LPASS_AUD_SLIMBUS_N_IN)
#define HWIO_LPASS_AUD_SLIMBUS_N_NOT_N_MINUS_M_BMSK                                                                         0xff
#define HWIO_LPASS_AUD_SLIMBUS_N_NOT_N_MINUS_M_SHFT                                                                          0x0

#define HWIO_LPASS_AUD_SLIMBUS_D_ADDR                                                                                 (LPASS_CC_REG_BASE      + 0x00017010)
#define HWIO_LPASS_AUD_SLIMBUS_D_OFFS                                                                                 (LPASS_CC_REG_BASE_OFFS + 0x00017010)
#define HWIO_LPASS_AUD_SLIMBUS_D_RMSK                                                                                       0xff
#define HWIO_LPASS_AUD_SLIMBUS_D_IN          \
        in_dword_masked(HWIO_LPASS_AUD_SLIMBUS_D_ADDR, HWIO_LPASS_AUD_SLIMBUS_D_RMSK)
#define HWIO_LPASS_AUD_SLIMBUS_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUD_SLIMBUS_D_ADDR, m)
#define HWIO_LPASS_AUD_SLIMBUS_D_OUT(v)      \
        out_dword(HWIO_LPASS_AUD_SLIMBUS_D_ADDR,v)
#define HWIO_LPASS_AUD_SLIMBUS_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUD_SLIMBUS_D_ADDR,m,v,HWIO_LPASS_AUD_SLIMBUS_D_IN)
#define HWIO_LPASS_AUD_SLIMBUS_D_NOT_2D_BMSK                                                                                0xff
#define HWIO_LPASS_AUD_SLIMBUS_D_NOT_2D_SHFT                                                                                 0x0

#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CBCR_ADDR                                                                   (LPASS_CC_REG_BASE      + 0x00017014)
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CBCR_OFFS                                                                   (LPASS_CC_REG_BASE_OFFS + 0x00017014)
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CBCR_RMSK                                                                   0x80000003
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CBCR_CLK_OFF_BMSK                                                           0x80000000
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CBCR_CLK_OFF_SHFT                                                                 0x1f
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CBCR_HW_CTL_BMSK                                                                   0x2
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CBCR_HW_CTL_SHFT                                                                   0x1
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CBCR_CLK_ENABLE_BMSK                                                               0x1
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CBCR_CLK_ENABLE_SHFT                                                               0x0

#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_ADDR                                                              (LPASS_CC_REG_BASE      + 0x00017018)
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_OFFS                                                              (LPASS_CC_REG_BASE_OFFS + 0x00017018)
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_RMSK                                                              0x80007ff3
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_CLK_OFF_BMSK                                                      0x80000000
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_CLK_OFF_SHFT                                                            0x1f
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_FORCE_MEM_CORE_ON_BMSK                                                0x4000
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_FORCE_MEM_CORE_ON_SHFT                                                   0xe
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_FORCE_MEM_PERIPH_ON_BMSK                                              0x2000
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                                 0xd
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                                             0x1000
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                                0xc
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_WAKEUP_BMSK                                                            0xf00
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_WAKEUP_SHFT                                                              0x8
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_SLEEP_BMSK                                                              0xf0
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_SLEEP_SHFT                                                               0x4
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_HW_CTL_BMSK                                                              0x2
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_HW_CTL_SHFT                                                              0x1
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_CLK_ENABLE_BMSK                                                          0x1
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_CLK_ENABLE_SHFT                                                          0x0

#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_NPL_CBCR_ADDR                                                               (LPASS_CC_REG_BASE      + 0x0001701c)
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_NPL_CBCR_OFFS                                                               (LPASS_CC_REG_BASE_OFFS + 0x0001701c)
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_NPL_CBCR_RMSK                                                               0x80000003
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_NPL_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_NPL_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_NPL_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_NPL_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_NPL_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_NPL_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_NPL_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_NPL_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_NPL_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_NPL_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_NPL_CBCR_CLK_OFF_BMSK                                                       0x80000000
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_NPL_CBCR_CLK_OFF_SHFT                                                             0x1f
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_NPL_CBCR_HW_CTL_BMSK                                                               0x2
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_NPL_CBCR_HW_CTL_SHFT                                                               0x1
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_NPL_CBCR_CLK_ENABLE_BMSK                                                           0x1
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_NPL_CBCR_CLK_ENABLE_SHFT                                                           0x0

#define HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_ADDR                                                                          (LPASS_CC_REG_BASE      + 0x00018000)
#define HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_OFFS                                                                          (LPASS_CC_REG_BASE_OFFS + 0x00018000)
#define HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_RMSK                                                                          0x800000f3
#define HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_ADDR, HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_RMSK)
#define HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_ADDR,m,v,HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_IN)
#define HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_ROOT_OFF_BMSK                                                                 0x80000000
#define HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_ROOT_OFF_SHFT                                                                       0x1f
#define HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_DIRTY_D_BMSK                                                                        0x80
#define HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_DIRTY_D_SHFT                                                                         0x7
#define HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_DIRTY_N_BMSK                                                                        0x40
#define HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_DIRTY_N_SHFT                                                                         0x6
#define HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_DIRTY_M_BMSK                                                                        0x20
#define HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_DIRTY_M_SHFT                                                                         0x5
#define HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                 0x10
#define HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                  0x4
#define HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_ROOT_EN_BMSK                                                                         0x2
#define HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_ROOT_EN_SHFT                                                                         0x1
#define HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_UPDATE_BMSK                                                                          0x1
#define HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_UPDATE_SHFT                                                                          0x0

#define HWIO_LPASS_QCA_SLIMBUS_CFG_RCGR_ADDR                                                                          (LPASS_CC_REG_BASE      + 0x00018004)
#define HWIO_LPASS_QCA_SLIMBUS_CFG_RCGR_OFFS                                                                          (LPASS_CC_REG_BASE_OFFS + 0x00018004)
#define HWIO_LPASS_QCA_SLIMBUS_CFG_RCGR_RMSK                                                                              0x771f
#define HWIO_LPASS_QCA_SLIMBUS_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_QCA_SLIMBUS_CFG_RCGR_ADDR, HWIO_LPASS_QCA_SLIMBUS_CFG_RCGR_RMSK)
#define HWIO_LPASS_QCA_SLIMBUS_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_QCA_SLIMBUS_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_QCA_SLIMBUS_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_QCA_SLIMBUS_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_QCA_SLIMBUS_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QCA_SLIMBUS_CFG_RCGR_ADDR,m,v,HWIO_LPASS_QCA_SLIMBUS_CFG_RCGR_IN)
#define HWIO_LPASS_QCA_SLIMBUS_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                  0x4000
#define HWIO_LPASS_QCA_SLIMBUS_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                     0xe
#define HWIO_LPASS_QCA_SLIMBUS_CFG_RCGR_MODE_BMSK                                                                         0x3000
#define HWIO_LPASS_QCA_SLIMBUS_CFG_RCGR_MODE_SHFT                                                                            0xc
#define HWIO_LPASS_QCA_SLIMBUS_CFG_RCGR_SRC_SEL_BMSK                                                                       0x700
#define HWIO_LPASS_QCA_SLIMBUS_CFG_RCGR_SRC_SEL_SHFT                                                                         0x8
#define HWIO_LPASS_QCA_SLIMBUS_CFG_RCGR_SRC_DIV_BMSK                                                                        0x1f
#define HWIO_LPASS_QCA_SLIMBUS_CFG_RCGR_SRC_DIV_SHFT                                                                         0x0

#define HWIO_LPASS_QCA_SLIMBUS_M_ADDR                                                                                 (LPASS_CC_REG_BASE      + 0x00018008)
#define HWIO_LPASS_QCA_SLIMBUS_M_OFFS                                                                                 (LPASS_CC_REG_BASE_OFFS + 0x00018008)
#define HWIO_LPASS_QCA_SLIMBUS_M_RMSK                                                                                       0xff
#define HWIO_LPASS_QCA_SLIMBUS_M_IN          \
        in_dword_masked(HWIO_LPASS_QCA_SLIMBUS_M_ADDR, HWIO_LPASS_QCA_SLIMBUS_M_RMSK)
#define HWIO_LPASS_QCA_SLIMBUS_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_QCA_SLIMBUS_M_ADDR, m)
#define HWIO_LPASS_QCA_SLIMBUS_M_OUT(v)      \
        out_dword(HWIO_LPASS_QCA_SLIMBUS_M_ADDR,v)
#define HWIO_LPASS_QCA_SLIMBUS_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QCA_SLIMBUS_M_ADDR,m,v,HWIO_LPASS_QCA_SLIMBUS_M_IN)
#define HWIO_LPASS_QCA_SLIMBUS_M_M_BMSK                                                                                     0xff
#define HWIO_LPASS_QCA_SLIMBUS_M_M_SHFT                                                                                      0x0

#define HWIO_LPASS_QCA_SLIMBUS_N_ADDR                                                                                 (LPASS_CC_REG_BASE      + 0x0001800c)
#define HWIO_LPASS_QCA_SLIMBUS_N_OFFS                                                                                 (LPASS_CC_REG_BASE_OFFS + 0x0001800c)
#define HWIO_LPASS_QCA_SLIMBUS_N_RMSK                                                                                       0xff
#define HWIO_LPASS_QCA_SLIMBUS_N_IN          \
        in_dword_masked(HWIO_LPASS_QCA_SLIMBUS_N_ADDR, HWIO_LPASS_QCA_SLIMBUS_N_RMSK)
#define HWIO_LPASS_QCA_SLIMBUS_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_QCA_SLIMBUS_N_ADDR, m)
#define HWIO_LPASS_QCA_SLIMBUS_N_OUT(v)      \
        out_dword(HWIO_LPASS_QCA_SLIMBUS_N_ADDR,v)
#define HWIO_LPASS_QCA_SLIMBUS_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QCA_SLIMBUS_N_ADDR,m,v,HWIO_LPASS_QCA_SLIMBUS_N_IN)
#define HWIO_LPASS_QCA_SLIMBUS_N_NOT_N_MINUS_M_BMSK                                                                         0xff
#define HWIO_LPASS_QCA_SLIMBUS_N_NOT_N_MINUS_M_SHFT                                                                          0x0

#define HWIO_LPASS_QCA_SLIMBUS_D_ADDR                                                                                 (LPASS_CC_REG_BASE      + 0x00018010)
#define HWIO_LPASS_QCA_SLIMBUS_D_OFFS                                                                                 (LPASS_CC_REG_BASE_OFFS + 0x00018010)
#define HWIO_LPASS_QCA_SLIMBUS_D_RMSK                                                                                       0xff
#define HWIO_LPASS_QCA_SLIMBUS_D_IN          \
        in_dword_masked(HWIO_LPASS_QCA_SLIMBUS_D_ADDR, HWIO_LPASS_QCA_SLIMBUS_D_RMSK)
#define HWIO_LPASS_QCA_SLIMBUS_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_QCA_SLIMBUS_D_ADDR, m)
#define HWIO_LPASS_QCA_SLIMBUS_D_OUT(v)      \
        out_dword(HWIO_LPASS_QCA_SLIMBUS_D_ADDR,v)
#define HWIO_LPASS_QCA_SLIMBUS_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QCA_SLIMBUS_D_ADDR,m,v,HWIO_LPASS_QCA_SLIMBUS_D_IN)
#define HWIO_LPASS_QCA_SLIMBUS_D_NOT_2D_BMSK                                                                                0xff
#define HWIO_LPASS_QCA_SLIMBUS_D_NOT_2D_SHFT                                                                                 0x0

#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CBCR_ADDR                                                                   (LPASS_CC_REG_BASE      + 0x00018014)
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CBCR_OFFS                                                                   (LPASS_CC_REG_BASE_OFFS + 0x00018014)
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CBCR_RMSK                                                                   0x80000003
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CBCR_CLK_OFF_BMSK                                                           0x80000000
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CBCR_CLK_OFF_SHFT                                                                 0x1f
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CBCR_HW_CTL_BMSK                                                                   0x2
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CBCR_HW_CTL_SHFT                                                                   0x1
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CBCR_CLK_ENABLE_BMSK                                                               0x1
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CBCR_CLK_ENABLE_SHFT                                                               0x0

#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_ADDR                                                              (LPASS_CC_REG_BASE      + 0x00018018)
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_OFFS                                                              (LPASS_CC_REG_BASE_OFFS + 0x00018018)
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_RMSK                                                              0x80007ff3
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_CLK_OFF_BMSK                                                      0x80000000
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_CLK_OFF_SHFT                                                            0x1f
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_FORCE_MEM_CORE_ON_BMSK                                                0x4000
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_FORCE_MEM_CORE_ON_SHFT                                                   0xe
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_FORCE_MEM_PERIPH_ON_BMSK                                              0x2000
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                                 0xd
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                                             0x1000
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                                0xc
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_WAKEUP_BMSK                                                            0xf00
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_WAKEUP_SHFT                                                              0x8
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_SLEEP_BMSK                                                              0xf0
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_SLEEP_SHFT                                                               0x4
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_HW_CTL_BMSK                                                              0x2
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_HW_CTL_SHFT                                                              0x1
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_CLK_ENABLE_BMSK                                                          0x1
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_CLK_ENABLE_SHFT                                                          0x0

#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_ADDR                                                                          (LPASS_CC_REG_BASE      + 0x00019000)
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_OFFS                                                                          (LPASS_CC_REG_BASE_OFFS + 0x00019000)
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_RMSK                                                                          0x800000f3
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_ADDR, HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_RMSK)
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_ADDR,m,v,HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_IN)
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_ROOT_OFF_BMSK                                                                 0x80000000
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_ROOT_OFF_SHFT                                                                       0x1f
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_DIRTY_D_BMSK                                                                        0x80
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_DIRTY_D_SHFT                                                                         0x7
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_DIRTY_N_BMSK                                                                        0x40
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_DIRTY_N_SHFT                                                                         0x6
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_DIRTY_M_BMSK                                                                        0x20
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_DIRTY_M_SHFT                                                                         0x5
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                 0x10
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                  0x4
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_ROOT_EN_BMSK                                                                         0x2
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_ROOT_EN_SHFT                                                                         0x1
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_UPDATE_BMSK                                                                          0x1
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_UPDATE_SHFT                                                                          0x0

#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_ADDR                                                                          (LPASS_CC_REG_BASE      + 0x00019004)
#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_OFFS                                                                          (LPASS_CC_REG_BASE_OFFS + 0x00019004)
#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_RMSK                                                                              0x771f
#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_ADDR, HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_RMSK)
#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_ADDR,m,v,HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_IN)
#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                  0x4000
#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                     0xe
#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_MODE_BMSK                                                                         0x3000
#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_MODE_SHFT                                                                            0xc
#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_SRC_SEL_BMSK                                                                       0x700
#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_SRC_SEL_SHFT                                                                         0x8
#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_SRC_DIV_BMSK                                                                        0x1f
#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_SRC_DIV_SHFT                                                                         0x0

#define HWIO_LPASS_LPAIF_PCMOE_M_ADDR                                                                                 (LPASS_CC_REG_BASE      + 0x00019008)
#define HWIO_LPASS_LPAIF_PCMOE_M_OFFS                                                                                 (LPASS_CC_REG_BASE_OFFS + 0x00019008)
#define HWIO_LPASS_LPAIF_PCMOE_M_RMSK                                                                                       0xff
#define HWIO_LPASS_LPAIF_PCMOE_M_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PCMOE_M_ADDR, HWIO_LPASS_LPAIF_PCMOE_M_RMSK)
#define HWIO_LPASS_LPAIF_PCMOE_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PCMOE_M_ADDR, m)
#define HWIO_LPASS_LPAIF_PCMOE_M_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PCMOE_M_ADDR,v)
#define HWIO_LPASS_LPAIF_PCMOE_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PCMOE_M_ADDR,m,v,HWIO_LPASS_LPAIF_PCMOE_M_IN)
#define HWIO_LPASS_LPAIF_PCMOE_M_M_BMSK                                                                                     0xff
#define HWIO_LPASS_LPAIF_PCMOE_M_M_SHFT                                                                                      0x0

#define HWIO_LPASS_LPAIF_PCMOE_N_ADDR                                                                                 (LPASS_CC_REG_BASE      + 0x0001900c)
#define HWIO_LPASS_LPAIF_PCMOE_N_OFFS                                                                                 (LPASS_CC_REG_BASE_OFFS + 0x0001900c)
#define HWIO_LPASS_LPAIF_PCMOE_N_RMSK                                                                                       0xff
#define HWIO_LPASS_LPAIF_PCMOE_N_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PCMOE_N_ADDR, HWIO_LPASS_LPAIF_PCMOE_N_RMSK)
#define HWIO_LPASS_LPAIF_PCMOE_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PCMOE_N_ADDR, m)
#define HWIO_LPASS_LPAIF_PCMOE_N_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PCMOE_N_ADDR,v)
#define HWIO_LPASS_LPAIF_PCMOE_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PCMOE_N_ADDR,m,v,HWIO_LPASS_LPAIF_PCMOE_N_IN)
#define HWIO_LPASS_LPAIF_PCMOE_N_NOT_N_MINUS_M_BMSK                                                                         0xff
#define HWIO_LPASS_LPAIF_PCMOE_N_NOT_N_MINUS_M_SHFT                                                                          0x0

#define HWIO_LPASS_LPAIF_PCMOE_D_ADDR                                                                                 (LPASS_CC_REG_BASE      + 0x00019010)
#define HWIO_LPASS_LPAIF_PCMOE_D_OFFS                                                                                 (LPASS_CC_REG_BASE_OFFS + 0x00019010)
#define HWIO_LPASS_LPAIF_PCMOE_D_RMSK                                                                                       0xff
#define HWIO_LPASS_LPAIF_PCMOE_D_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PCMOE_D_ADDR, HWIO_LPASS_LPAIF_PCMOE_D_RMSK)
#define HWIO_LPASS_LPAIF_PCMOE_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PCMOE_D_ADDR, m)
#define HWIO_LPASS_LPAIF_PCMOE_D_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PCMOE_D_ADDR,v)
#define HWIO_LPASS_LPAIF_PCMOE_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PCMOE_D_ADDR,m,v,HWIO_LPASS_LPAIF_PCMOE_D_IN)
#define HWIO_LPASS_LPAIF_PCMOE_D_NOT_2D_BMSK                                                                                0xff
#define HWIO_LPASS_LPAIF_PCMOE_D_NOT_2D_SHFT                                                                                 0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_ADDR                                                             (LPASS_CC_REG_BASE      + 0x00019014)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_OFFS                                                             (LPASS_CC_REG_BASE_OFFS + 0x00019014)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_RMSK                                                             0x80000003
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_CLK_OFF_BMSK                                                     0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_CLK_OFF_SHFT                                                           0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_HW_CTL_BMSK                                                             0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_HW_CTL_SHFT                                                             0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_CLK_ENABLE_BMSK                                                         0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_CLK_ENABLE_SHFT                                                         0x0

#define HWIO_LPASS_SLEEP_CMD_RCGR_ADDR                                                                                (LPASS_CC_REG_BASE      + 0x0001a000)
#define HWIO_LPASS_SLEEP_CMD_RCGR_OFFS                                                                                (LPASS_CC_REG_BASE_OFFS + 0x0001a000)
#define HWIO_LPASS_SLEEP_CMD_RCGR_RMSK                                                                                0x800000f3
#define HWIO_LPASS_SLEEP_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_SLEEP_CMD_RCGR_ADDR, HWIO_LPASS_SLEEP_CMD_RCGR_RMSK)
#define HWIO_LPASS_SLEEP_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SLEEP_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_SLEEP_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_SLEEP_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_SLEEP_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SLEEP_CMD_RCGR_ADDR,m,v,HWIO_LPASS_SLEEP_CMD_RCGR_IN)
#define HWIO_LPASS_SLEEP_CMD_RCGR_ROOT_OFF_BMSK                                                                       0x80000000
#define HWIO_LPASS_SLEEP_CMD_RCGR_ROOT_OFF_SHFT                                                                             0x1f
#define HWIO_LPASS_SLEEP_CMD_RCGR_DIRTY_D_BMSK                                                                              0x80
#define HWIO_LPASS_SLEEP_CMD_RCGR_DIRTY_D_SHFT                                                                               0x7
#define HWIO_LPASS_SLEEP_CMD_RCGR_DIRTY_N_BMSK                                                                              0x40
#define HWIO_LPASS_SLEEP_CMD_RCGR_DIRTY_N_SHFT                                                                               0x6
#define HWIO_LPASS_SLEEP_CMD_RCGR_DIRTY_M_BMSK                                                                              0x20
#define HWIO_LPASS_SLEEP_CMD_RCGR_DIRTY_M_SHFT                                                                               0x5
#define HWIO_LPASS_SLEEP_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                       0x10
#define HWIO_LPASS_SLEEP_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                        0x4
#define HWIO_LPASS_SLEEP_CMD_RCGR_ROOT_EN_BMSK                                                                               0x2
#define HWIO_LPASS_SLEEP_CMD_RCGR_ROOT_EN_SHFT                                                                               0x1
#define HWIO_LPASS_SLEEP_CMD_RCGR_UPDATE_BMSK                                                                                0x1
#define HWIO_LPASS_SLEEP_CMD_RCGR_UPDATE_SHFT                                                                                0x0

#define HWIO_LPASS_SLEEP_CFG_RCGR_ADDR                                                                                (LPASS_CC_REG_BASE      + 0x0001a004)
#define HWIO_LPASS_SLEEP_CFG_RCGR_OFFS                                                                                (LPASS_CC_REG_BASE_OFFS + 0x0001a004)
#define HWIO_LPASS_SLEEP_CFG_RCGR_RMSK                                                                                    0x371f
#define HWIO_LPASS_SLEEP_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_SLEEP_CFG_RCGR_ADDR, HWIO_LPASS_SLEEP_CFG_RCGR_RMSK)
#define HWIO_LPASS_SLEEP_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SLEEP_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_SLEEP_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_SLEEP_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_SLEEP_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SLEEP_CFG_RCGR_ADDR,m,v,HWIO_LPASS_SLEEP_CFG_RCGR_IN)
#define HWIO_LPASS_SLEEP_CFG_RCGR_MODE_BMSK                                                                               0x3000
#define HWIO_LPASS_SLEEP_CFG_RCGR_MODE_SHFT                                                                                  0xc
#define HWIO_LPASS_SLEEP_CFG_RCGR_SRC_SEL_BMSK                                                                             0x700
#define HWIO_LPASS_SLEEP_CFG_RCGR_SRC_SEL_SHFT                                                                               0x8
#define HWIO_LPASS_SLEEP_CFG_RCGR_SRC_DIV_BMSK                                                                              0x1f
#define HWIO_LPASS_SLEEP_CFG_RCGR_SRC_DIV_SHFT                                                                               0x0

#define HWIO_LPASS_XO_CMD_RCGR_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x0001b000)
#define HWIO_LPASS_XO_CMD_RCGR_OFFS                                                                                   (LPASS_CC_REG_BASE_OFFS + 0x0001b000)
#define HWIO_LPASS_XO_CMD_RCGR_RMSK                                                                                   0x800000f3
#define HWIO_LPASS_XO_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_XO_CMD_RCGR_ADDR, HWIO_LPASS_XO_CMD_RCGR_RMSK)
#define HWIO_LPASS_XO_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_XO_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_XO_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_XO_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_XO_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_XO_CMD_RCGR_ADDR,m,v,HWIO_LPASS_XO_CMD_RCGR_IN)
#define HWIO_LPASS_XO_CMD_RCGR_ROOT_OFF_BMSK                                                                          0x80000000
#define HWIO_LPASS_XO_CMD_RCGR_ROOT_OFF_SHFT                                                                                0x1f
#define HWIO_LPASS_XO_CMD_RCGR_DIRTY_D_BMSK                                                                                 0x80
#define HWIO_LPASS_XO_CMD_RCGR_DIRTY_D_SHFT                                                                                  0x7
#define HWIO_LPASS_XO_CMD_RCGR_DIRTY_N_BMSK                                                                                 0x40
#define HWIO_LPASS_XO_CMD_RCGR_DIRTY_N_SHFT                                                                                  0x6
#define HWIO_LPASS_XO_CMD_RCGR_DIRTY_M_BMSK                                                                                 0x20
#define HWIO_LPASS_XO_CMD_RCGR_DIRTY_M_SHFT                                                                                  0x5
#define HWIO_LPASS_XO_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                          0x10
#define HWIO_LPASS_XO_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                           0x4
#define HWIO_LPASS_XO_CMD_RCGR_ROOT_EN_BMSK                                                                                  0x2
#define HWIO_LPASS_XO_CMD_RCGR_ROOT_EN_SHFT                                                                                  0x1
#define HWIO_LPASS_XO_CMD_RCGR_UPDATE_BMSK                                                                                   0x1
#define HWIO_LPASS_XO_CMD_RCGR_UPDATE_SHFT                                                                                   0x0

#define HWIO_LPASS_XO_CFG_RCGR_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x0001b004)
#define HWIO_LPASS_XO_CFG_RCGR_OFFS                                                                                   (LPASS_CC_REG_BASE_OFFS + 0x0001b004)
#define HWIO_LPASS_XO_CFG_RCGR_RMSK                                                                                       0x771f
#define HWIO_LPASS_XO_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_XO_CFG_RCGR_ADDR, HWIO_LPASS_XO_CFG_RCGR_RMSK)
#define HWIO_LPASS_XO_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_XO_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_XO_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_XO_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_XO_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_XO_CFG_RCGR_ADDR,m,v,HWIO_LPASS_XO_CFG_RCGR_IN)
#define HWIO_LPASS_XO_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                           0x4000
#define HWIO_LPASS_XO_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                              0xe
#define HWIO_LPASS_XO_CFG_RCGR_MODE_BMSK                                                                                  0x3000
#define HWIO_LPASS_XO_CFG_RCGR_MODE_SHFT                                                                                     0xc
#define HWIO_LPASS_XO_CFG_RCGR_SRC_SEL_BMSK                                                                                0x700
#define HWIO_LPASS_XO_CFG_RCGR_SRC_SEL_SHFT                                                                                  0x8
#define HWIO_LPASS_XO_CFG_RCGR_SRC_DIV_BMSK                                                                                 0x1f
#define HWIO_LPASS_XO_CFG_RCGR_SRC_DIV_SHFT                                                                                  0x0

#define HWIO_LPASS_AUDIO_CORE_AVSYNC_STC_CBCR_ADDR                                                                    (LPASS_CC_REG_BASE      + 0x0001c000)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_STC_CBCR_OFFS                                                                    (LPASS_CC_REG_BASE_OFFS + 0x0001c000)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_STC_CBCR_RMSK                                                                    0x80000003
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_STC_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_AVSYNC_STC_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_AVSYNC_STC_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_STC_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_AVSYNC_STC_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_STC_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_AVSYNC_STC_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_STC_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_AVSYNC_STC_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_AVSYNC_STC_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_STC_CBCR_CLK_OFF_BMSK                                                            0x80000000
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_STC_CBCR_CLK_OFF_SHFT                                                                  0x1f
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_STC_CBCR_HW_CTL_BMSK                                                                    0x2
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_STC_CBCR_HW_CTL_SHFT                                                                    0x1
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_STC_CBCR_CLK_ENABLE_BMSK                                                                0x1
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_STC_CBCR_CLK_ENABLE_SHFT                                                                0x0

#define HWIO_LPASS_CORE_CMD_RCGR_ADDR                                                                                 (LPASS_CC_REG_BASE      + 0x0001d000)
#define HWIO_LPASS_CORE_CMD_RCGR_OFFS                                                                                 (LPASS_CC_REG_BASE_OFFS + 0x0001d000)
#define HWIO_LPASS_CORE_CMD_RCGR_RMSK                                                                                 0x800000f3
#define HWIO_LPASS_CORE_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_CORE_CMD_RCGR_ADDR, HWIO_LPASS_CORE_CMD_RCGR_RMSK)
#define HWIO_LPASS_CORE_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_CORE_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_CORE_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_CORE_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_CORE_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_CORE_CMD_RCGR_ADDR,m,v,HWIO_LPASS_CORE_CMD_RCGR_IN)
#define HWIO_LPASS_CORE_CMD_RCGR_ROOT_OFF_BMSK                                                                        0x80000000
#define HWIO_LPASS_CORE_CMD_RCGR_ROOT_OFF_SHFT                                                                              0x1f
#define HWIO_LPASS_CORE_CMD_RCGR_DIRTY_D_BMSK                                                                               0x80
#define HWIO_LPASS_CORE_CMD_RCGR_DIRTY_D_SHFT                                                                                0x7
#define HWIO_LPASS_CORE_CMD_RCGR_DIRTY_N_BMSK                                                                               0x40
#define HWIO_LPASS_CORE_CMD_RCGR_DIRTY_N_SHFT                                                                                0x6
#define HWIO_LPASS_CORE_CMD_RCGR_DIRTY_M_BMSK                                                                               0x20
#define HWIO_LPASS_CORE_CMD_RCGR_DIRTY_M_SHFT                                                                                0x5
#define HWIO_LPASS_CORE_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                        0x10
#define HWIO_LPASS_CORE_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                         0x4
#define HWIO_LPASS_CORE_CMD_RCGR_ROOT_EN_BMSK                                                                                0x2
#define HWIO_LPASS_CORE_CMD_RCGR_ROOT_EN_SHFT                                                                                0x1
#define HWIO_LPASS_CORE_CMD_RCGR_UPDATE_BMSK                                                                                 0x1
#define HWIO_LPASS_CORE_CMD_RCGR_UPDATE_SHFT                                                                                 0x0

#define HWIO_LPASS_CORE_CFG_RCGR_ADDR                                                                                 (LPASS_CC_REG_BASE      + 0x0001d004)
#define HWIO_LPASS_CORE_CFG_RCGR_OFFS                                                                                 (LPASS_CC_REG_BASE_OFFS + 0x0001d004)
#define HWIO_LPASS_CORE_CFG_RCGR_RMSK                                                                                     0x771f
#define HWIO_LPASS_CORE_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_CORE_CFG_RCGR_ADDR, HWIO_LPASS_CORE_CFG_RCGR_RMSK)
#define HWIO_LPASS_CORE_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_CORE_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_CORE_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_CORE_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_CORE_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_CORE_CFG_RCGR_ADDR,m,v,HWIO_LPASS_CORE_CFG_RCGR_IN)
#define HWIO_LPASS_CORE_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                         0x4000
#define HWIO_LPASS_CORE_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                            0xe
#define HWIO_LPASS_CORE_CFG_RCGR_MODE_BMSK                                                                                0x3000
#define HWIO_LPASS_CORE_CFG_RCGR_MODE_SHFT                                                                                   0xc
#define HWIO_LPASS_CORE_CFG_RCGR_SRC_SEL_BMSK                                                                              0x700
#define HWIO_LPASS_CORE_CFG_RCGR_SRC_SEL_SHFT                                                                                0x8
#define HWIO_LPASS_CORE_CFG_RCGR_SRC_DIV_BMSK                                                                               0x1f
#define HWIO_LPASS_CORE_CFG_RCGR_SRC_DIV_SHFT                                                                                0x0

#define HWIO_LPASS_CORE_M_ADDR                                                                                        (LPASS_CC_REG_BASE      + 0x0001d008)
#define HWIO_LPASS_CORE_M_OFFS                                                                                        (LPASS_CC_REG_BASE_OFFS + 0x0001d008)
#define HWIO_LPASS_CORE_M_RMSK                                                                                              0xff
#define HWIO_LPASS_CORE_M_IN          \
        in_dword_masked(HWIO_LPASS_CORE_M_ADDR, HWIO_LPASS_CORE_M_RMSK)
#define HWIO_LPASS_CORE_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_CORE_M_ADDR, m)
#define HWIO_LPASS_CORE_M_OUT(v)      \
        out_dword(HWIO_LPASS_CORE_M_ADDR,v)
#define HWIO_LPASS_CORE_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_CORE_M_ADDR,m,v,HWIO_LPASS_CORE_M_IN)
#define HWIO_LPASS_CORE_M_M_BMSK                                                                                            0xff
#define HWIO_LPASS_CORE_M_M_SHFT                                                                                             0x0

#define HWIO_LPASS_CORE_N_ADDR                                                                                        (LPASS_CC_REG_BASE      + 0x0001d00c)
#define HWIO_LPASS_CORE_N_OFFS                                                                                        (LPASS_CC_REG_BASE_OFFS + 0x0001d00c)
#define HWIO_LPASS_CORE_N_RMSK                                                                                              0xff
#define HWIO_LPASS_CORE_N_IN          \
        in_dword_masked(HWIO_LPASS_CORE_N_ADDR, HWIO_LPASS_CORE_N_RMSK)
#define HWIO_LPASS_CORE_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_CORE_N_ADDR, m)
#define HWIO_LPASS_CORE_N_OUT(v)      \
        out_dword(HWIO_LPASS_CORE_N_ADDR,v)
#define HWIO_LPASS_CORE_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_CORE_N_ADDR,m,v,HWIO_LPASS_CORE_N_IN)
#define HWIO_LPASS_CORE_N_NOT_N_MINUS_M_BMSK                                                                                0xff
#define HWIO_LPASS_CORE_N_NOT_N_MINUS_M_SHFT                                                                                 0x0

#define HWIO_LPASS_CORE_D_ADDR                                                                                        (LPASS_CC_REG_BASE      + 0x0001d010)
#define HWIO_LPASS_CORE_D_OFFS                                                                                        (LPASS_CC_REG_BASE_OFFS + 0x0001d010)
#define HWIO_LPASS_CORE_D_RMSK                                                                                              0xff
#define HWIO_LPASS_CORE_D_IN          \
        in_dword_masked(HWIO_LPASS_CORE_D_ADDR, HWIO_LPASS_CORE_D_RMSK)
#define HWIO_LPASS_CORE_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_CORE_D_ADDR, m)
#define HWIO_LPASS_CORE_D_OUT(v)      \
        out_dword(HWIO_LPASS_CORE_D_ADDR,v)
#define HWIO_LPASS_CORE_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_CORE_D_ADDR,m,v,HWIO_LPASS_CORE_D_IN)
#define HWIO_LPASS_CORE_D_NOT_2D_BMSK                                                                                       0xff
#define HWIO_LPASS_CORE_D_NOT_2D_SHFT                                                                                        0x0

#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_ADDR                                                                      (LPASS_CC_REG_BASE      + 0x0001e000)
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_OFFS                                                                      (LPASS_CC_REG_BASE_OFFS + 0x0001e000)
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_RMSK                                                                      0x80007ff3
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_CLK_OFF_BMSK                                                              0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_CLK_OFF_SHFT                                                                    0x1f
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_FORCE_MEM_CORE_ON_BMSK                                                        0x4000
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_FORCE_MEM_CORE_ON_SHFT                                                           0xe
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_FORCE_MEM_PERIPH_ON_BMSK                                                      0x2000
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                                         0xd
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                                                     0x1000
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                                        0xc
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_WAKEUP_BMSK                                                                    0xf00
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_WAKEUP_SHFT                                                                      0x8
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_SLEEP_BMSK                                                                      0xf0
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_SLEEP_SHFT                                                                       0x4
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_HW_CTL_BMSK                                                                      0x2
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_HW_CTL_SHFT                                                                      0x1
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_CLK_ENABLE_BMSK                                                                  0x1
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_CLK_ENABLE_SHFT                                                                  0x0

#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_ADDR                                                                 (LPASS_CC_REG_BASE      + 0x0001e004)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_OFFS                                                                 (LPASS_CC_REG_BASE_OFFS + 0x0001e004)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_RMSK                                                                 0x80007ff3
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_CLK_OFF_BMSK                                                         0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_CLK_OFF_SHFT                                                               0x1f
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_FORCE_MEM_CORE_ON_BMSK                                                   0x4000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_FORCE_MEM_CORE_ON_SHFT                                                      0xe
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_FORCE_MEM_PERIPH_ON_BMSK                                                 0x2000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                                    0xd
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                                                0x1000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                                   0xc
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_WAKEUP_BMSK                                                               0xf00
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_WAKEUP_SHFT                                                                 0x8
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_SLEEP_BMSK                                                                 0xf0
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_SLEEP_SHFT                                                                  0x4
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_HW_CTL_BMSK                                                                 0x2
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_HW_CTL_SHFT                                                                 0x1
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_CLK_ENABLE_BMSK                                                             0x1
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_CLK_ENABLE_SHFT                                                             0x0

#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_ADDR                                                                 (LPASS_CC_REG_BASE      + 0x0001e008)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_OFFS                                                                 (LPASS_CC_REG_BASE_OFFS + 0x0001e008)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_RMSK                                                                 0x80007ff3
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_CLK_OFF_BMSK                                                         0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_CLK_OFF_SHFT                                                               0x1f
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_FORCE_MEM_CORE_ON_BMSK                                                   0x4000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_FORCE_MEM_CORE_ON_SHFT                                                      0xe
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_FORCE_MEM_PERIPH_ON_BMSK                                                 0x2000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                                    0xd
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                                                0x1000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                                   0xc
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_WAKEUP_BMSK                                                               0xf00
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_WAKEUP_SHFT                                                                 0x8
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_SLEEP_BMSK                                                                 0xf0
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_SLEEP_SHFT                                                                  0x4
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_HW_CTL_BMSK                                                                 0x2
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_HW_CTL_SHFT                                                                 0x1
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_CLK_ENABLE_BMSK                                                             0x1
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_CLK_ENABLE_SHFT                                                             0x0

#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_ADDR                                                                 (LPASS_CC_REG_BASE      + 0x0001e00c)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_OFFS                                                                 (LPASS_CC_REG_BASE_OFFS + 0x0001e00c)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_RMSK                                                                 0x80007ff3
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_CLK_OFF_BMSK                                                         0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_CLK_OFF_SHFT                                                               0x1f
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_FORCE_MEM_CORE_ON_BMSK                                                   0x4000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_FORCE_MEM_CORE_ON_SHFT                                                      0xe
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_FORCE_MEM_PERIPH_ON_BMSK                                                 0x2000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                                    0xd
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                                                0x1000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                                   0xc
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_WAKEUP_BMSK                                                               0xf00
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_WAKEUP_SHFT                                                                 0x8
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_SLEEP_BMSK                                                                 0xf0
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_SLEEP_SHFT                                                                  0x4
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_HW_CTL_BMSK                                                                 0x2
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_HW_CTL_SHFT                                                                 0x1
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_CLK_ENABLE_BMSK                                                             0x1
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_CLK_ENABLE_SHFT                                                             0x0

#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_ADDR                                                                 (LPASS_CC_REG_BASE      + 0x0001e010)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_OFFS                                                                 (LPASS_CC_REG_BASE_OFFS + 0x0001e010)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_RMSK                                                                 0x80007ff3
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_CLK_OFF_BMSK                                                         0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_CLK_OFF_SHFT                                                               0x1f
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_FORCE_MEM_CORE_ON_BMSK                                                   0x4000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_FORCE_MEM_CORE_ON_SHFT                                                      0xe
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_FORCE_MEM_PERIPH_ON_BMSK                                                 0x2000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                                    0xd
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                                                0x1000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                                   0xc
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_WAKEUP_BMSK                                                               0xf00
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_WAKEUP_SHFT                                                                 0x8
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_SLEEP_BMSK                                                                 0xf0
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_SLEEP_SHFT                                                                  0x4
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_HW_CTL_BMSK                                                                 0x2
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_HW_CTL_SHFT                                                                 0x1
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_CLK_ENABLE_BMSK                                                             0x1
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_CLK_ENABLE_SHFT                                                             0x0

#define HWIO_LPASS_AUDIO_CORE_CORE_CBCR_ADDR                                                                          (LPASS_CC_REG_BASE      + 0x0001f000)
#define HWIO_LPASS_AUDIO_CORE_CORE_CBCR_OFFS                                                                          (LPASS_CC_REG_BASE_OFFS + 0x0001f000)
#define HWIO_LPASS_AUDIO_CORE_CORE_CBCR_RMSK                                                                          0x80000003
#define HWIO_LPASS_AUDIO_CORE_CORE_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_CORE_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_CORE_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_CORE_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_CORE_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_CORE_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_CORE_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_CORE_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_CORE_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_CORE_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_CORE_CBCR_CLK_OFF_BMSK                                                                  0x80000000
#define HWIO_LPASS_AUDIO_CORE_CORE_CBCR_CLK_OFF_SHFT                                                                        0x1f
#define HWIO_LPASS_AUDIO_CORE_CORE_CBCR_HW_CTL_BMSK                                                                          0x2
#define HWIO_LPASS_AUDIO_CORE_CORE_CBCR_HW_CTL_SHFT                                                                          0x1
#define HWIO_LPASS_AUDIO_CORE_CORE_CBCR_CLK_ENABLE_BMSK                                                                      0x1
#define HWIO_LPASS_AUDIO_CORE_CORE_CBCR_CLK_ENABLE_SHFT                                                                      0x0

#define HWIO_LPASS_EXT_MCLK0_CMD_RCGR_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x00020000)
#define HWIO_LPASS_EXT_MCLK0_CMD_RCGR_OFFS                                                                            (LPASS_CC_REG_BASE_OFFS + 0x00020000)
#define HWIO_LPASS_EXT_MCLK0_CMD_RCGR_RMSK                                                                            0x800000f3
#define HWIO_LPASS_EXT_MCLK0_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_EXT_MCLK0_CMD_RCGR_ADDR, HWIO_LPASS_EXT_MCLK0_CMD_RCGR_RMSK)
#define HWIO_LPASS_EXT_MCLK0_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_EXT_MCLK0_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_EXT_MCLK0_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_EXT_MCLK0_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_EXT_MCLK0_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_EXT_MCLK0_CMD_RCGR_ADDR,m,v,HWIO_LPASS_EXT_MCLK0_CMD_RCGR_IN)
#define HWIO_LPASS_EXT_MCLK0_CMD_RCGR_ROOT_OFF_BMSK                                                                   0x80000000
#define HWIO_LPASS_EXT_MCLK0_CMD_RCGR_ROOT_OFF_SHFT                                                                         0x1f
#define HWIO_LPASS_EXT_MCLK0_CMD_RCGR_DIRTY_D_BMSK                                                                          0x80
#define HWIO_LPASS_EXT_MCLK0_CMD_RCGR_DIRTY_D_SHFT                                                                           0x7
#define HWIO_LPASS_EXT_MCLK0_CMD_RCGR_DIRTY_N_BMSK                                                                          0x40
#define HWIO_LPASS_EXT_MCLK0_CMD_RCGR_DIRTY_N_SHFT                                                                           0x6
#define HWIO_LPASS_EXT_MCLK0_CMD_RCGR_DIRTY_M_BMSK                                                                          0x20
#define HWIO_LPASS_EXT_MCLK0_CMD_RCGR_DIRTY_M_SHFT                                                                           0x5
#define HWIO_LPASS_EXT_MCLK0_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                   0x10
#define HWIO_LPASS_EXT_MCLK0_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                    0x4
#define HWIO_LPASS_EXT_MCLK0_CMD_RCGR_ROOT_EN_BMSK                                                                           0x2
#define HWIO_LPASS_EXT_MCLK0_CMD_RCGR_ROOT_EN_SHFT                                                                           0x1
#define HWIO_LPASS_EXT_MCLK0_CMD_RCGR_UPDATE_BMSK                                                                            0x1
#define HWIO_LPASS_EXT_MCLK0_CMD_RCGR_UPDATE_SHFT                                                                            0x0

#define HWIO_LPASS_EXT_MCLK0_CFG_RCGR_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x00020004)
#define HWIO_LPASS_EXT_MCLK0_CFG_RCGR_OFFS                                                                            (LPASS_CC_REG_BASE_OFFS + 0x00020004)
#define HWIO_LPASS_EXT_MCLK0_CFG_RCGR_RMSK                                                                                0x771f
#define HWIO_LPASS_EXT_MCLK0_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_EXT_MCLK0_CFG_RCGR_ADDR, HWIO_LPASS_EXT_MCLK0_CFG_RCGR_RMSK)
#define HWIO_LPASS_EXT_MCLK0_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_EXT_MCLK0_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_EXT_MCLK0_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_EXT_MCLK0_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_EXT_MCLK0_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_EXT_MCLK0_CFG_RCGR_ADDR,m,v,HWIO_LPASS_EXT_MCLK0_CFG_RCGR_IN)
#define HWIO_LPASS_EXT_MCLK0_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                    0x4000
#define HWIO_LPASS_EXT_MCLK0_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                       0xe
#define HWIO_LPASS_EXT_MCLK0_CFG_RCGR_MODE_BMSK                                                                           0x3000
#define HWIO_LPASS_EXT_MCLK0_CFG_RCGR_MODE_SHFT                                                                              0xc
#define HWIO_LPASS_EXT_MCLK0_CFG_RCGR_SRC_SEL_BMSK                                                                         0x700
#define HWIO_LPASS_EXT_MCLK0_CFG_RCGR_SRC_SEL_SHFT                                                                           0x8
#define HWIO_LPASS_EXT_MCLK0_CFG_RCGR_SRC_DIV_BMSK                                                                          0x1f
#define HWIO_LPASS_EXT_MCLK0_CFG_RCGR_SRC_DIV_SHFT                                                                           0x0

#define HWIO_LPASS_EXT_MCLK0_M_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x00020008)
#define HWIO_LPASS_EXT_MCLK0_M_OFFS                                                                                   (LPASS_CC_REG_BASE_OFFS + 0x00020008)
#define HWIO_LPASS_EXT_MCLK0_M_RMSK                                                                                         0xff
#define HWIO_LPASS_EXT_MCLK0_M_IN          \
        in_dword_masked(HWIO_LPASS_EXT_MCLK0_M_ADDR, HWIO_LPASS_EXT_MCLK0_M_RMSK)
#define HWIO_LPASS_EXT_MCLK0_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_EXT_MCLK0_M_ADDR, m)
#define HWIO_LPASS_EXT_MCLK0_M_OUT(v)      \
        out_dword(HWIO_LPASS_EXT_MCLK0_M_ADDR,v)
#define HWIO_LPASS_EXT_MCLK0_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_EXT_MCLK0_M_ADDR,m,v,HWIO_LPASS_EXT_MCLK0_M_IN)
#define HWIO_LPASS_EXT_MCLK0_M_M_BMSK                                                                                       0xff
#define HWIO_LPASS_EXT_MCLK0_M_M_SHFT                                                                                        0x0

#define HWIO_LPASS_EXT_MCLK0_N_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x0002000c)
#define HWIO_LPASS_EXT_MCLK0_N_OFFS                                                                                   (LPASS_CC_REG_BASE_OFFS + 0x0002000c)
#define HWIO_LPASS_EXT_MCLK0_N_RMSK                                                                                         0xff
#define HWIO_LPASS_EXT_MCLK0_N_IN          \
        in_dword_masked(HWIO_LPASS_EXT_MCLK0_N_ADDR, HWIO_LPASS_EXT_MCLK0_N_RMSK)
#define HWIO_LPASS_EXT_MCLK0_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_EXT_MCLK0_N_ADDR, m)
#define HWIO_LPASS_EXT_MCLK0_N_OUT(v)      \
        out_dword(HWIO_LPASS_EXT_MCLK0_N_ADDR,v)
#define HWIO_LPASS_EXT_MCLK0_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_EXT_MCLK0_N_ADDR,m,v,HWIO_LPASS_EXT_MCLK0_N_IN)
#define HWIO_LPASS_EXT_MCLK0_N_NOT_N_MINUS_M_BMSK                                                                           0xff
#define HWIO_LPASS_EXT_MCLK0_N_NOT_N_MINUS_M_SHFT                                                                            0x0

#define HWIO_LPASS_EXT_MCLK0_D_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x00020010)
#define HWIO_LPASS_EXT_MCLK0_D_OFFS                                                                                   (LPASS_CC_REG_BASE_OFFS + 0x00020010)
#define HWIO_LPASS_EXT_MCLK0_D_RMSK                                                                                         0xff
#define HWIO_LPASS_EXT_MCLK0_D_IN          \
        in_dword_masked(HWIO_LPASS_EXT_MCLK0_D_ADDR, HWIO_LPASS_EXT_MCLK0_D_RMSK)
#define HWIO_LPASS_EXT_MCLK0_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_EXT_MCLK0_D_ADDR, m)
#define HWIO_LPASS_EXT_MCLK0_D_OUT(v)      \
        out_dword(HWIO_LPASS_EXT_MCLK0_D_ADDR,v)
#define HWIO_LPASS_EXT_MCLK0_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_EXT_MCLK0_D_ADDR,m,v,HWIO_LPASS_EXT_MCLK0_D_IN)
#define HWIO_LPASS_EXT_MCLK0_D_NOT_2D_BMSK                                                                                  0xff
#define HWIO_LPASS_EXT_MCLK0_D_NOT_2D_SHFT                                                                                   0x0

#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CBCR_ADDR                                                                  (LPASS_CC_REG_BASE      + 0x00020014)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CBCR_OFFS                                                                  (LPASS_CC_REG_BASE_OFFS + 0x00020014)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CBCR_RMSK                                                                  0x80000003
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CBCR_CLK_OFF_BMSK                                                          0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CBCR_CLK_OFF_SHFT                                                                0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CBCR_HW_CTL_BMSK                                                                  0x2
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CBCR_HW_CTL_SHFT                                                                  0x1
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CBCR_CLK_ENABLE_BMSK                                                              0x1
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CBCR_CLK_ENABLE_SHFT                                                              0x0

#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CTRL_CLK_OE_ADDR                                                           (LPASS_CC_REG_BASE      + 0x00020018)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CTRL_CLK_OE_OFFS                                                           (LPASS_CC_REG_BASE_OFFS + 0x00020018)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CTRL_CLK_OE_RMSK                                                                  0x1
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CTRL_CLK_OE_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CTRL_CLK_OE_ADDR, HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CTRL_CLK_OE_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CTRL_CLK_OE_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CTRL_CLK_OE_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CTRL_CLK_OE_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CTRL_CLK_OE_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CTRL_CLK_OE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CTRL_CLK_OE_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CTRL_CLK_OE_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CTRL_CLK_OE_CTRL_CLK_OE_BMSK                                                      0x1
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CTRL_CLK_OE_CTRL_CLK_OE_SHFT                                                      0x0

#define HWIO_LPASS_EXT_MCLK1_CMD_RCGR_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x00021000)
#define HWIO_LPASS_EXT_MCLK1_CMD_RCGR_OFFS                                                                            (LPASS_CC_REG_BASE_OFFS + 0x00021000)
#define HWIO_LPASS_EXT_MCLK1_CMD_RCGR_RMSK                                                                            0x800000f3
#define HWIO_LPASS_EXT_MCLK1_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_EXT_MCLK1_CMD_RCGR_ADDR, HWIO_LPASS_EXT_MCLK1_CMD_RCGR_RMSK)
#define HWIO_LPASS_EXT_MCLK1_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_EXT_MCLK1_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_EXT_MCLK1_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_EXT_MCLK1_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_EXT_MCLK1_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_EXT_MCLK1_CMD_RCGR_ADDR,m,v,HWIO_LPASS_EXT_MCLK1_CMD_RCGR_IN)
#define HWIO_LPASS_EXT_MCLK1_CMD_RCGR_ROOT_OFF_BMSK                                                                   0x80000000
#define HWIO_LPASS_EXT_MCLK1_CMD_RCGR_ROOT_OFF_SHFT                                                                         0x1f
#define HWIO_LPASS_EXT_MCLK1_CMD_RCGR_DIRTY_D_BMSK                                                                          0x80
#define HWIO_LPASS_EXT_MCLK1_CMD_RCGR_DIRTY_D_SHFT                                                                           0x7
#define HWIO_LPASS_EXT_MCLK1_CMD_RCGR_DIRTY_N_BMSK                                                                          0x40
#define HWIO_LPASS_EXT_MCLK1_CMD_RCGR_DIRTY_N_SHFT                                                                           0x6
#define HWIO_LPASS_EXT_MCLK1_CMD_RCGR_DIRTY_M_BMSK                                                                          0x20
#define HWIO_LPASS_EXT_MCLK1_CMD_RCGR_DIRTY_M_SHFT                                                                           0x5
#define HWIO_LPASS_EXT_MCLK1_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                   0x10
#define HWIO_LPASS_EXT_MCLK1_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                    0x4
#define HWIO_LPASS_EXT_MCLK1_CMD_RCGR_ROOT_EN_BMSK                                                                           0x2
#define HWIO_LPASS_EXT_MCLK1_CMD_RCGR_ROOT_EN_SHFT                                                                           0x1
#define HWIO_LPASS_EXT_MCLK1_CMD_RCGR_UPDATE_BMSK                                                                            0x1
#define HWIO_LPASS_EXT_MCLK1_CMD_RCGR_UPDATE_SHFT                                                                            0x0

#define HWIO_LPASS_EXT_MCLK1_CFG_RCGR_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x00021004)
#define HWIO_LPASS_EXT_MCLK1_CFG_RCGR_OFFS                                                                            (LPASS_CC_REG_BASE_OFFS + 0x00021004)
#define HWIO_LPASS_EXT_MCLK1_CFG_RCGR_RMSK                                                                                0x771f
#define HWIO_LPASS_EXT_MCLK1_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_EXT_MCLK1_CFG_RCGR_ADDR, HWIO_LPASS_EXT_MCLK1_CFG_RCGR_RMSK)
#define HWIO_LPASS_EXT_MCLK1_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_EXT_MCLK1_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_EXT_MCLK1_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_EXT_MCLK1_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_EXT_MCLK1_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_EXT_MCLK1_CFG_RCGR_ADDR,m,v,HWIO_LPASS_EXT_MCLK1_CFG_RCGR_IN)
#define HWIO_LPASS_EXT_MCLK1_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                    0x4000
#define HWIO_LPASS_EXT_MCLK1_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                       0xe
#define HWIO_LPASS_EXT_MCLK1_CFG_RCGR_MODE_BMSK                                                                           0x3000
#define HWIO_LPASS_EXT_MCLK1_CFG_RCGR_MODE_SHFT                                                                              0xc
#define HWIO_LPASS_EXT_MCLK1_CFG_RCGR_SRC_SEL_BMSK                                                                         0x700
#define HWIO_LPASS_EXT_MCLK1_CFG_RCGR_SRC_SEL_SHFT                                                                           0x8
#define HWIO_LPASS_EXT_MCLK1_CFG_RCGR_SRC_DIV_BMSK                                                                          0x1f
#define HWIO_LPASS_EXT_MCLK1_CFG_RCGR_SRC_DIV_SHFT                                                                           0x0

#define HWIO_LPASS_EXT_MCLK1_M_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x00021008)
#define HWIO_LPASS_EXT_MCLK1_M_OFFS                                                                                   (LPASS_CC_REG_BASE_OFFS + 0x00021008)
#define HWIO_LPASS_EXT_MCLK1_M_RMSK                                                                                         0xff
#define HWIO_LPASS_EXT_MCLK1_M_IN          \
        in_dword_masked(HWIO_LPASS_EXT_MCLK1_M_ADDR, HWIO_LPASS_EXT_MCLK1_M_RMSK)
#define HWIO_LPASS_EXT_MCLK1_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_EXT_MCLK1_M_ADDR, m)
#define HWIO_LPASS_EXT_MCLK1_M_OUT(v)      \
        out_dword(HWIO_LPASS_EXT_MCLK1_M_ADDR,v)
#define HWIO_LPASS_EXT_MCLK1_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_EXT_MCLK1_M_ADDR,m,v,HWIO_LPASS_EXT_MCLK1_M_IN)
#define HWIO_LPASS_EXT_MCLK1_M_M_BMSK                                                                                       0xff
#define HWIO_LPASS_EXT_MCLK1_M_M_SHFT                                                                                        0x0

#define HWIO_LPASS_EXT_MCLK1_N_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x0002100c)
#define HWIO_LPASS_EXT_MCLK1_N_OFFS                                                                                   (LPASS_CC_REG_BASE_OFFS + 0x0002100c)
#define HWIO_LPASS_EXT_MCLK1_N_RMSK                                                                                         0xff
#define HWIO_LPASS_EXT_MCLK1_N_IN          \
        in_dword_masked(HWIO_LPASS_EXT_MCLK1_N_ADDR, HWIO_LPASS_EXT_MCLK1_N_RMSK)
#define HWIO_LPASS_EXT_MCLK1_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_EXT_MCLK1_N_ADDR, m)
#define HWIO_LPASS_EXT_MCLK1_N_OUT(v)      \
        out_dword(HWIO_LPASS_EXT_MCLK1_N_ADDR,v)
#define HWIO_LPASS_EXT_MCLK1_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_EXT_MCLK1_N_ADDR,m,v,HWIO_LPASS_EXT_MCLK1_N_IN)
#define HWIO_LPASS_EXT_MCLK1_N_NOT_N_MINUS_M_BMSK                                                                           0xff
#define HWIO_LPASS_EXT_MCLK1_N_NOT_N_MINUS_M_SHFT                                                                            0x0

#define HWIO_LPASS_EXT_MCLK1_D_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x00021010)
#define HWIO_LPASS_EXT_MCLK1_D_OFFS                                                                                   (LPASS_CC_REG_BASE_OFFS + 0x00021010)
#define HWIO_LPASS_EXT_MCLK1_D_RMSK                                                                                         0xff
#define HWIO_LPASS_EXT_MCLK1_D_IN          \
        in_dword_masked(HWIO_LPASS_EXT_MCLK1_D_ADDR, HWIO_LPASS_EXT_MCLK1_D_RMSK)
#define HWIO_LPASS_EXT_MCLK1_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_EXT_MCLK1_D_ADDR, m)
#define HWIO_LPASS_EXT_MCLK1_D_OUT(v)      \
        out_dword(HWIO_LPASS_EXT_MCLK1_D_ADDR,v)
#define HWIO_LPASS_EXT_MCLK1_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_EXT_MCLK1_D_ADDR,m,v,HWIO_LPASS_EXT_MCLK1_D_IN)
#define HWIO_LPASS_EXT_MCLK1_D_NOT_2D_BMSK                                                                                  0xff
#define HWIO_LPASS_EXT_MCLK1_D_NOT_2D_SHFT                                                                                   0x0

#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CBCR_ADDR                                                                  (LPASS_CC_REG_BASE      + 0x00021014)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CBCR_OFFS                                                                  (LPASS_CC_REG_BASE_OFFS + 0x00021014)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CBCR_RMSK                                                                  0x80000003
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CBCR_CLK_OFF_BMSK                                                          0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CBCR_CLK_OFF_SHFT                                                                0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CBCR_HW_CTL_BMSK                                                                  0x2
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CBCR_HW_CTL_SHFT                                                                  0x1
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CBCR_CLK_ENABLE_BMSK                                                              0x1
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CBCR_CLK_ENABLE_SHFT                                                              0x0

#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CTRL_CLK_OE_ADDR                                                           (LPASS_CC_REG_BASE      + 0x00021018)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CTRL_CLK_OE_OFFS                                                           (LPASS_CC_REG_BASE_OFFS + 0x00021018)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CTRL_CLK_OE_RMSK                                                                  0x1
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CTRL_CLK_OE_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CTRL_CLK_OE_ADDR, HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CTRL_CLK_OE_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CTRL_CLK_OE_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CTRL_CLK_OE_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CTRL_CLK_OE_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CTRL_CLK_OE_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CTRL_CLK_OE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CTRL_CLK_OE_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CTRL_CLK_OE_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CTRL_CLK_OE_CTRL_CLK_OE_BMSK                                                      0x1
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CTRL_CLK_OE_CTRL_CLK_OE_SHFT                                                      0x0

#define HWIO_LPASS_EXT_MCLK2_CMD_RCGR_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x00022000)
#define HWIO_LPASS_EXT_MCLK2_CMD_RCGR_OFFS                                                                            (LPASS_CC_REG_BASE_OFFS + 0x00022000)
#define HWIO_LPASS_EXT_MCLK2_CMD_RCGR_RMSK                                                                            0x800000f3
#define HWIO_LPASS_EXT_MCLK2_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_EXT_MCLK2_CMD_RCGR_ADDR, HWIO_LPASS_EXT_MCLK2_CMD_RCGR_RMSK)
#define HWIO_LPASS_EXT_MCLK2_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_EXT_MCLK2_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_EXT_MCLK2_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_EXT_MCLK2_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_EXT_MCLK2_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_EXT_MCLK2_CMD_RCGR_ADDR,m,v,HWIO_LPASS_EXT_MCLK2_CMD_RCGR_IN)
#define HWIO_LPASS_EXT_MCLK2_CMD_RCGR_ROOT_OFF_BMSK                                                                   0x80000000
#define HWIO_LPASS_EXT_MCLK2_CMD_RCGR_ROOT_OFF_SHFT                                                                         0x1f
#define HWIO_LPASS_EXT_MCLK2_CMD_RCGR_DIRTY_D_BMSK                                                                          0x80
#define HWIO_LPASS_EXT_MCLK2_CMD_RCGR_DIRTY_D_SHFT                                                                           0x7
#define HWIO_LPASS_EXT_MCLK2_CMD_RCGR_DIRTY_N_BMSK                                                                          0x40
#define HWIO_LPASS_EXT_MCLK2_CMD_RCGR_DIRTY_N_SHFT                                                                           0x6
#define HWIO_LPASS_EXT_MCLK2_CMD_RCGR_DIRTY_M_BMSK                                                                          0x20
#define HWIO_LPASS_EXT_MCLK2_CMD_RCGR_DIRTY_M_SHFT                                                                           0x5
#define HWIO_LPASS_EXT_MCLK2_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                   0x10
#define HWIO_LPASS_EXT_MCLK2_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                    0x4
#define HWIO_LPASS_EXT_MCLK2_CMD_RCGR_ROOT_EN_BMSK                                                                           0x2
#define HWIO_LPASS_EXT_MCLK2_CMD_RCGR_ROOT_EN_SHFT                                                                           0x1
#define HWIO_LPASS_EXT_MCLK2_CMD_RCGR_UPDATE_BMSK                                                                            0x1
#define HWIO_LPASS_EXT_MCLK2_CMD_RCGR_UPDATE_SHFT                                                                            0x0

#define HWIO_LPASS_EXT_MCLK2_CFG_RCGR_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x00022004)
#define HWIO_LPASS_EXT_MCLK2_CFG_RCGR_OFFS                                                                            (LPASS_CC_REG_BASE_OFFS + 0x00022004)
#define HWIO_LPASS_EXT_MCLK2_CFG_RCGR_RMSK                                                                                0x771f
#define HWIO_LPASS_EXT_MCLK2_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_EXT_MCLK2_CFG_RCGR_ADDR, HWIO_LPASS_EXT_MCLK2_CFG_RCGR_RMSK)
#define HWIO_LPASS_EXT_MCLK2_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_EXT_MCLK2_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_EXT_MCLK2_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_EXT_MCLK2_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_EXT_MCLK2_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_EXT_MCLK2_CFG_RCGR_ADDR,m,v,HWIO_LPASS_EXT_MCLK2_CFG_RCGR_IN)
#define HWIO_LPASS_EXT_MCLK2_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                    0x4000
#define HWIO_LPASS_EXT_MCLK2_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                       0xe
#define HWIO_LPASS_EXT_MCLK2_CFG_RCGR_MODE_BMSK                                                                           0x3000
#define HWIO_LPASS_EXT_MCLK2_CFG_RCGR_MODE_SHFT                                                                              0xc
#define HWIO_LPASS_EXT_MCLK2_CFG_RCGR_SRC_SEL_BMSK                                                                         0x700
#define HWIO_LPASS_EXT_MCLK2_CFG_RCGR_SRC_SEL_SHFT                                                                           0x8
#define HWIO_LPASS_EXT_MCLK2_CFG_RCGR_SRC_DIV_BMSK                                                                          0x1f
#define HWIO_LPASS_EXT_MCLK2_CFG_RCGR_SRC_DIV_SHFT                                                                           0x0

#define HWIO_LPASS_EXT_MCLK2_M_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x00022008)
#define HWIO_LPASS_EXT_MCLK2_M_OFFS                                                                                   (LPASS_CC_REG_BASE_OFFS + 0x00022008)
#define HWIO_LPASS_EXT_MCLK2_M_RMSK                                                                                         0xff
#define HWIO_LPASS_EXT_MCLK2_M_IN          \
        in_dword_masked(HWIO_LPASS_EXT_MCLK2_M_ADDR, HWIO_LPASS_EXT_MCLK2_M_RMSK)
#define HWIO_LPASS_EXT_MCLK2_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_EXT_MCLK2_M_ADDR, m)
#define HWIO_LPASS_EXT_MCLK2_M_OUT(v)      \
        out_dword(HWIO_LPASS_EXT_MCLK2_M_ADDR,v)
#define HWIO_LPASS_EXT_MCLK2_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_EXT_MCLK2_M_ADDR,m,v,HWIO_LPASS_EXT_MCLK2_M_IN)
#define HWIO_LPASS_EXT_MCLK2_M_M_BMSK                                                                                       0xff
#define HWIO_LPASS_EXT_MCLK2_M_M_SHFT                                                                                        0x0

#define HWIO_LPASS_EXT_MCLK2_N_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x0002200c)
#define HWIO_LPASS_EXT_MCLK2_N_OFFS                                                                                   (LPASS_CC_REG_BASE_OFFS + 0x0002200c)
#define HWIO_LPASS_EXT_MCLK2_N_RMSK                                                                                         0xff
#define HWIO_LPASS_EXT_MCLK2_N_IN          \
        in_dword_masked(HWIO_LPASS_EXT_MCLK2_N_ADDR, HWIO_LPASS_EXT_MCLK2_N_RMSK)
#define HWIO_LPASS_EXT_MCLK2_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_EXT_MCLK2_N_ADDR, m)
#define HWIO_LPASS_EXT_MCLK2_N_OUT(v)      \
        out_dword(HWIO_LPASS_EXT_MCLK2_N_ADDR,v)
#define HWIO_LPASS_EXT_MCLK2_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_EXT_MCLK2_N_ADDR,m,v,HWIO_LPASS_EXT_MCLK2_N_IN)
#define HWIO_LPASS_EXT_MCLK2_N_NOT_N_MINUS_M_BMSK                                                                           0xff
#define HWIO_LPASS_EXT_MCLK2_N_NOT_N_MINUS_M_SHFT                                                                            0x0

#define HWIO_LPASS_EXT_MCLK2_D_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x00022010)
#define HWIO_LPASS_EXT_MCLK2_D_OFFS                                                                                   (LPASS_CC_REG_BASE_OFFS + 0x00022010)
#define HWIO_LPASS_EXT_MCLK2_D_RMSK                                                                                         0xff
#define HWIO_LPASS_EXT_MCLK2_D_IN          \
        in_dword_masked(HWIO_LPASS_EXT_MCLK2_D_ADDR, HWIO_LPASS_EXT_MCLK2_D_RMSK)
#define HWIO_LPASS_EXT_MCLK2_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_EXT_MCLK2_D_ADDR, m)
#define HWIO_LPASS_EXT_MCLK2_D_OUT(v)      \
        out_dword(HWIO_LPASS_EXT_MCLK2_D_ADDR,v)
#define HWIO_LPASS_EXT_MCLK2_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_EXT_MCLK2_D_ADDR,m,v,HWIO_LPASS_EXT_MCLK2_D_IN)
#define HWIO_LPASS_EXT_MCLK2_D_NOT_2D_BMSK                                                                                  0xff
#define HWIO_LPASS_EXT_MCLK2_D_NOT_2D_SHFT                                                                                   0x0

#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK2_CBCR_ADDR                                                                  (LPASS_CC_REG_BASE      + 0x00022014)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK2_CBCR_OFFS                                                                  (LPASS_CC_REG_BASE_OFFS + 0x00022014)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK2_CBCR_RMSK                                                                  0x80000003
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK2_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK2_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK2_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK2_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK2_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK2_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK2_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK2_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK2_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK2_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK2_CBCR_CLK_OFF_BMSK                                                          0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK2_CBCR_CLK_OFF_SHFT                                                                0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK2_CBCR_HW_CTL_BMSK                                                                  0x2
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK2_CBCR_HW_CTL_SHFT                                                                  0x1
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK2_CBCR_CLK_ENABLE_BMSK                                                              0x1
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK2_CBCR_CLK_ENABLE_SHFT                                                              0x0

#define HWIO_LPASS_AUDIO_CORE_SYSNOC_MPORT_CORE_CBCR_ADDR                                                             (LPASS_CC_REG_BASE      + 0x00023000)
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_MPORT_CORE_CBCR_OFFS                                                             (LPASS_CC_REG_BASE_OFFS + 0x00023000)
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_MPORT_CORE_CBCR_RMSK                                                             0x80000003
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_MPORT_CORE_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_SYSNOC_MPORT_CORE_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_SYSNOC_MPORT_CORE_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_MPORT_CORE_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_SYSNOC_MPORT_CORE_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_MPORT_CORE_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_SYSNOC_MPORT_CORE_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_MPORT_CORE_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_SYSNOC_MPORT_CORE_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_SYSNOC_MPORT_CORE_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_MPORT_CORE_CBCR_CLK_OFF_BMSK                                                     0x80000000
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_MPORT_CORE_CBCR_CLK_OFF_SHFT                                                           0x1f
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_MPORT_CORE_CBCR_HW_CTL_BMSK                                                             0x2
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_MPORT_CORE_CBCR_HW_CTL_SHFT                                                             0x1
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_MPORT_CORE_CBCR_CLK_ENABLE_BMSK                                                         0x1
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_MPORT_CORE_CBCR_CLK_ENABLE_SHFT                                                         0x0

#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_AON_CBCR_ADDR                                                            (LPASS_CC_REG_BASE      + 0x00025000)
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_AON_CBCR_OFFS                                                            (LPASS_CC_REG_BASE_OFFS + 0x00025000)
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_AON_CBCR_RMSK                                                            0x80000003
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_AON_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_AON_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_AON_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_AON_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_AON_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_AON_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_AON_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_AON_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_AON_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_AON_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_AON_CBCR_CLK_OFF_BMSK                                                    0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_AON_CBCR_CLK_OFF_SHFT                                                          0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_AON_CBCR_HW_CTL_BMSK                                                            0x2
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_AON_CBCR_HW_CTL_SHFT                                                            0x1
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_AON_CBCR_CLK_ENABLE_BMSK                                                        0x1
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_AON_CBCR_CLK_ENABLE_SHFT                                                        0x0

#define HWIO_LPASS_Q6SS_AHBM_AON_CBCR_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x00026000)
#define HWIO_LPASS_Q6SS_AHBM_AON_CBCR_OFFS                                                                            (LPASS_CC_REG_BASE_OFFS + 0x00026000)
#define HWIO_LPASS_Q6SS_AHBM_AON_CBCR_RMSK                                                                            0x80000003
#define HWIO_LPASS_Q6SS_AHBM_AON_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_Q6SS_AHBM_AON_CBCR_ADDR, HWIO_LPASS_Q6SS_AHBM_AON_CBCR_RMSK)
#define HWIO_LPASS_Q6SS_AHBM_AON_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_Q6SS_AHBM_AON_CBCR_ADDR, m)
#define HWIO_LPASS_Q6SS_AHBM_AON_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_Q6SS_AHBM_AON_CBCR_ADDR,v)
#define HWIO_LPASS_Q6SS_AHBM_AON_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_Q6SS_AHBM_AON_CBCR_ADDR,m,v,HWIO_LPASS_Q6SS_AHBM_AON_CBCR_IN)
#define HWIO_LPASS_Q6SS_AHBM_AON_CBCR_CLK_OFF_BMSK                                                                    0x80000000
#define HWIO_LPASS_Q6SS_AHBM_AON_CBCR_CLK_OFF_SHFT                                                                          0x1f
#define HWIO_LPASS_Q6SS_AHBM_AON_CBCR_HW_CTL_BMSK                                                                            0x2
#define HWIO_LPASS_Q6SS_AHBM_AON_CBCR_HW_CTL_SHFT                                                                            0x1
#define HWIO_LPASS_Q6SS_AHBM_AON_CBCR_CLK_ENABLE_BMSK                                                                        0x1
#define HWIO_LPASS_Q6SS_AHBM_AON_CBCR_CLK_ENABLE_SHFT                                                                        0x0

#define HWIO_LPASS_EXT_MCLK3_CMD_RCGR_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x00027000)
#define HWIO_LPASS_EXT_MCLK3_CMD_RCGR_OFFS                                                                            (LPASS_CC_REG_BASE_OFFS + 0x00027000)
#define HWIO_LPASS_EXT_MCLK3_CMD_RCGR_RMSK                                                                            0x800000f3
#define HWIO_LPASS_EXT_MCLK3_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_EXT_MCLK3_CMD_RCGR_ADDR, HWIO_LPASS_EXT_MCLK3_CMD_RCGR_RMSK)
#define HWIO_LPASS_EXT_MCLK3_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_EXT_MCLK3_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_EXT_MCLK3_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_EXT_MCLK3_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_EXT_MCLK3_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_EXT_MCLK3_CMD_RCGR_ADDR,m,v,HWIO_LPASS_EXT_MCLK3_CMD_RCGR_IN)
#define HWIO_LPASS_EXT_MCLK3_CMD_RCGR_ROOT_OFF_BMSK                                                                   0x80000000
#define HWIO_LPASS_EXT_MCLK3_CMD_RCGR_ROOT_OFF_SHFT                                                                         0x1f
#define HWIO_LPASS_EXT_MCLK3_CMD_RCGR_DIRTY_D_BMSK                                                                          0x80
#define HWIO_LPASS_EXT_MCLK3_CMD_RCGR_DIRTY_D_SHFT                                                                           0x7
#define HWIO_LPASS_EXT_MCLK3_CMD_RCGR_DIRTY_N_BMSK                                                                          0x40
#define HWIO_LPASS_EXT_MCLK3_CMD_RCGR_DIRTY_N_SHFT                                                                           0x6
#define HWIO_LPASS_EXT_MCLK3_CMD_RCGR_DIRTY_M_BMSK                                                                          0x20
#define HWIO_LPASS_EXT_MCLK3_CMD_RCGR_DIRTY_M_SHFT                                                                           0x5
#define HWIO_LPASS_EXT_MCLK3_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                   0x10
#define HWIO_LPASS_EXT_MCLK3_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                    0x4
#define HWIO_LPASS_EXT_MCLK3_CMD_RCGR_ROOT_EN_BMSK                                                                           0x2
#define HWIO_LPASS_EXT_MCLK3_CMD_RCGR_ROOT_EN_SHFT                                                                           0x1
#define HWIO_LPASS_EXT_MCLK3_CMD_RCGR_UPDATE_BMSK                                                                            0x1
#define HWIO_LPASS_EXT_MCLK3_CMD_RCGR_UPDATE_SHFT                                                                            0x0

#define HWIO_LPASS_EXT_MCLK3_CFG_RCGR_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x00027004)
#define HWIO_LPASS_EXT_MCLK3_CFG_RCGR_OFFS                                                                            (LPASS_CC_REG_BASE_OFFS + 0x00027004)
#define HWIO_LPASS_EXT_MCLK3_CFG_RCGR_RMSK                                                                                0x771f
#define HWIO_LPASS_EXT_MCLK3_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_EXT_MCLK3_CFG_RCGR_ADDR, HWIO_LPASS_EXT_MCLK3_CFG_RCGR_RMSK)
#define HWIO_LPASS_EXT_MCLK3_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_EXT_MCLK3_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_EXT_MCLK3_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_EXT_MCLK3_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_EXT_MCLK3_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_EXT_MCLK3_CFG_RCGR_ADDR,m,v,HWIO_LPASS_EXT_MCLK3_CFG_RCGR_IN)
#define HWIO_LPASS_EXT_MCLK3_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                    0x4000
#define HWIO_LPASS_EXT_MCLK3_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                       0xe
#define HWIO_LPASS_EXT_MCLK3_CFG_RCGR_MODE_BMSK                                                                           0x3000
#define HWIO_LPASS_EXT_MCLK3_CFG_RCGR_MODE_SHFT                                                                              0xc
#define HWIO_LPASS_EXT_MCLK3_CFG_RCGR_SRC_SEL_BMSK                                                                         0x700
#define HWIO_LPASS_EXT_MCLK3_CFG_RCGR_SRC_SEL_SHFT                                                                           0x8
#define HWIO_LPASS_EXT_MCLK3_CFG_RCGR_SRC_DIV_BMSK                                                                          0x1f
#define HWIO_LPASS_EXT_MCLK3_CFG_RCGR_SRC_DIV_SHFT                                                                           0x0

#define HWIO_LPASS_EXT_MCLK3_M_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x00027008)
#define HWIO_LPASS_EXT_MCLK3_M_OFFS                                                                                   (LPASS_CC_REG_BASE_OFFS + 0x00027008)
#define HWIO_LPASS_EXT_MCLK3_M_RMSK                                                                                         0xff
#define HWIO_LPASS_EXT_MCLK3_M_IN          \
        in_dword_masked(HWIO_LPASS_EXT_MCLK3_M_ADDR, HWIO_LPASS_EXT_MCLK3_M_RMSK)
#define HWIO_LPASS_EXT_MCLK3_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_EXT_MCLK3_M_ADDR, m)
#define HWIO_LPASS_EXT_MCLK3_M_OUT(v)      \
        out_dword(HWIO_LPASS_EXT_MCLK3_M_ADDR,v)
#define HWIO_LPASS_EXT_MCLK3_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_EXT_MCLK3_M_ADDR,m,v,HWIO_LPASS_EXT_MCLK3_M_IN)
#define HWIO_LPASS_EXT_MCLK3_M_M_BMSK                                                                                       0xff
#define HWIO_LPASS_EXT_MCLK3_M_M_SHFT                                                                                        0x0

#define HWIO_LPASS_EXT_MCLK3_N_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x0002700c)
#define HWIO_LPASS_EXT_MCLK3_N_OFFS                                                                                   (LPASS_CC_REG_BASE_OFFS + 0x0002700c)
#define HWIO_LPASS_EXT_MCLK3_N_RMSK                                                                                         0xff
#define HWIO_LPASS_EXT_MCLK3_N_IN          \
        in_dword_masked(HWIO_LPASS_EXT_MCLK3_N_ADDR, HWIO_LPASS_EXT_MCLK3_N_RMSK)
#define HWIO_LPASS_EXT_MCLK3_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_EXT_MCLK3_N_ADDR, m)
#define HWIO_LPASS_EXT_MCLK3_N_OUT(v)      \
        out_dword(HWIO_LPASS_EXT_MCLK3_N_ADDR,v)
#define HWIO_LPASS_EXT_MCLK3_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_EXT_MCLK3_N_ADDR,m,v,HWIO_LPASS_EXT_MCLK3_N_IN)
#define HWIO_LPASS_EXT_MCLK3_N_NOT_N_MINUS_M_BMSK                                                                           0xff
#define HWIO_LPASS_EXT_MCLK3_N_NOT_N_MINUS_M_SHFT                                                                            0x0

#define HWIO_LPASS_EXT_MCLK3_D_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x00027010)
#define HWIO_LPASS_EXT_MCLK3_D_OFFS                                                                                   (LPASS_CC_REG_BASE_OFFS + 0x00027010)
#define HWIO_LPASS_EXT_MCLK3_D_RMSK                                                                                         0xff
#define HWIO_LPASS_EXT_MCLK3_D_IN          \
        in_dword_masked(HWIO_LPASS_EXT_MCLK3_D_ADDR, HWIO_LPASS_EXT_MCLK3_D_RMSK)
#define HWIO_LPASS_EXT_MCLK3_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_EXT_MCLK3_D_ADDR, m)
#define HWIO_LPASS_EXT_MCLK3_D_OUT(v)      \
        out_dword(HWIO_LPASS_EXT_MCLK3_D_ADDR,v)
#define HWIO_LPASS_EXT_MCLK3_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_EXT_MCLK3_D_ADDR,m,v,HWIO_LPASS_EXT_MCLK3_D_IN)
#define HWIO_LPASS_EXT_MCLK3_D_NOT_2D_BMSK                                                                                  0xff
#define HWIO_LPASS_EXT_MCLK3_D_NOT_2D_SHFT                                                                                   0x0

#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK3_CBCR_ADDR                                                                  (LPASS_CC_REG_BASE      + 0x00027014)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK3_CBCR_OFFS                                                                  (LPASS_CC_REG_BASE_OFFS + 0x00027014)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK3_CBCR_RMSK                                                                  0x80000003
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK3_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK3_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK3_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK3_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK3_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK3_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK3_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK3_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK3_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK3_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK3_CBCR_CLK_OFF_BMSK                                                          0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK3_CBCR_CLK_OFF_SHFT                                                                0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK3_CBCR_HW_CTL_BMSK                                                                  0x2
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK3_CBCR_HW_CTL_SHFT                                                                  0x1
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK3_CBCR_CLK_ENABLE_BMSK                                                              0x1
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK3_CBCR_CLK_ENABLE_SHFT                                                              0x0

#define HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_AON_CBCR_ADDR                                                                 (LPASS_CC_REG_BASE      + 0x00028000)
#define HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_AON_CBCR_OFFS                                                                 (LPASS_CC_REG_BASE_OFFS + 0x00028000)
#define HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_AON_CBCR_RMSK                                                                 0x80000003
#define HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_AON_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_AON_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_AON_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_AON_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_AON_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_AON_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_AON_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_AON_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_AON_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_AON_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_AON_CBCR_CLK_OFF_BMSK                                                         0x80000000
#define HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_AON_CBCR_CLK_OFF_SHFT                                                               0x1f
#define HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_AON_CBCR_HW_CTL_BMSK                                                                 0x2
#define HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_AON_CBCR_HW_CTL_SHFT                                                                 0x1
#define HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_AON_CBCR_CLK_ENABLE_BMSK                                                             0x1
#define HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_AON_CBCR_CLK_ENABLE_SHFT                                                             0x0

#define HWIO_LPASS_ISLAND_SCC_DBG_BCR_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x0002d000)
#define HWIO_LPASS_ISLAND_SCC_DBG_BCR_OFFS                                                                            (LPASS_CC_REG_BASE_OFFS + 0x0002d000)
#define HWIO_LPASS_ISLAND_SCC_DBG_BCR_RMSK                                                                                   0x1
#define HWIO_LPASS_ISLAND_SCC_DBG_BCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_DBG_BCR_ADDR, HWIO_LPASS_ISLAND_SCC_DBG_BCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_DBG_BCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_DBG_BCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_DBG_BCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_DBG_BCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_DBG_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_DBG_BCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_DBG_BCR_IN)
#define HWIO_LPASS_ISLAND_SCC_DBG_BCR_BLK_ARES_BMSK                                                                          0x1
#define HWIO_LPASS_ISLAND_SCC_DBG_BCR_BLK_ARES_SHFT                                                                          0x0

#define HWIO_LPASS_SCC_AON_DBG_CMD_RCGR_ADDR                                                                          (LPASS_CC_REG_BASE      + 0x0002d004)
#define HWIO_LPASS_SCC_AON_DBG_CMD_RCGR_OFFS                                                                          (LPASS_CC_REG_BASE_OFFS + 0x0002d004)
#define HWIO_LPASS_SCC_AON_DBG_CMD_RCGR_RMSK                                                                          0x800000f3
#define HWIO_LPASS_SCC_AON_DBG_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_SCC_AON_DBG_CMD_RCGR_ADDR, HWIO_LPASS_SCC_AON_DBG_CMD_RCGR_RMSK)
#define HWIO_LPASS_SCC_AON_DBG_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_AON_DBG_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_SCC_AON_DBG_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_AON_DBG_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_SCC_AON_DBG_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_AON_DBG_CMD_RCGR_ADDR,m,v,HWIO_LPASS_SCC_AON_DBG_CMD_RCGR_IN)
#define HWIO_LPASS_SCC_AON_DBG_CMD_RCGR_ROOT_OFF_BMSK                                                                 0x80000000
#define HWIO_LPASS_SCC_AON_DBG_CMD_RCGR_ROOT_OFF_SHFT                                                                       0x1f
#define HWIO_LPASS_SCC_AON_DBG_CMD_RCGR_DIRTY_D_BMSK                                                                        0x80
#define HWIO_LPASS_SCC_AON_DBG_CMD_RCGR_DIRTY_D_SHFT                                                                         0x7
#define HWIO_LPASS_SCC_AON_DBG_CMD_RCGR_DIRTY_N_BMSK                                                                        0x40
#define HWIO_LPASS_SCC_AON_DBG_CMD_RCGR_DIRTY_N_SHFT                                                                         0x6
#define HWIO_LPASS_SCC_AON_DBG_CMD_RCGR_DIRTY_M_BMSK                                                                        0x20
#define HWIO_LPASS_SCC_AON_DBG_CMD_RCGR_DIRTY_M_SHFT                                                                         0x5
#define HWIO_LPASS_SCC_AON_DBG_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                 0x10
#define HWIO_LPASS_SCC_AON_DBG_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                  0x4
#define HWIO_LPASS_SCC_AON_DBG_CMD_RCGR_ROOT_EN_BMSK                                                                         0x2
#define HWIO_LPASS_SCC_AON_DBG_CMD_RCGR_ROOT_EN_SHFT                                                                         0x1
#define HWIO_LPASS_SCC_AON_DBG_CMD_RCGR_UPDATE_BMSK                                                                          0x1
#define HWIO_LPASS_SCC_AON_DBG_CMD_RCGR_UPDATE_SHFT                                                                          0x0

#define HWIO_LPASS_SCC_AON_DBG_CFG_RCGR_ADDR                                                                          (LPASS_CC_REG_BASE      + 0x0002d008)
#define HWIO_LPASS_SCC_AON_DBG_CFG_RCGR_OFFS                                                                          (LPASS_CC_REG_BASE_OFFS + 0x0002d008)
#define HWIO_LPASS_SCC_AON_DBG_CFG_RCGR_RMSK                                                                              0x771f
#define HWIO_LPASS_SCC_AON_DBG_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_SCC_AON_DBG_CFG_RCGR_ADDR, HWIO_LPASS_SCC_AON_DBG_CFG_RCGR_RMSK)
#define HWIO_LPASS_SCC_AON_DBG_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_AON_DBG_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_SCC_AON_DBG_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_AON_DBG_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_SCC_AON_DBG_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_AON_DBG_CFG_RCGR_ADDR,m,v,HWIO_LPASS_SCC_AON_DBG_CFG_RCGR_IN)
#define HWIO_LPASS_SCC_AON_DBG_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                  0x4000
#define HWIO_LPASS_SCC_AON_DBG_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                     0xe
#define HWIO_LPASS_SCC_AON_DBG_CFG_RCGR_MODE_BMSK                                                                         0x3000
#define HWIO_LPASS_SCC_AON_DBG_CFG_RCGR_MODE_SHFT                                                                            0xc
#define HWIO_LPASS_SCC_AON_DBG_CFG_RCGR_SRC_SEL_BMSK                                                                       0x700
#define HWIO_LPASS_SCC_AON_DBG_CFG_RCGR_SRC_SEL_SHFT                                                                         0x8
#define HWIO_LPASS_SCC_AON_DBG_CFG_RCGR_SRC_DIV_BMSK                                                                        0x1f
#define HWIO_LPASS_SCC_AON_DBG_CFG_RCGR_SRC_DIV_SHFT                                                                         0x0

#define HWIO_LPASS_SCC_AON_DBG_M_ADDR                                                                                 (LPASS_CC_REG_BASE      + 0x0002d00c)
#define HWIO_LPASS_SCC_AON_DBG_M_OFFS                                                                                 (LPASS_CC_REG_BASE_OFFS + 0x0002d00c)
#define HWIO_LPASS_SCC_AON_DBG_M_RMSK                                                                                       0xff
#define HWIO_LPASS_SCC_AON_DBG_M_IN          \
        in_dword_masked(HWIO_LPASS_SCC_AON_DBG_M_ADDR, HWIO_LPASS_SCC_AON_DBG_M_RMSK)
#define HWIO_LPASS_SCC_AON_DBG_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_AON_DBG_M_ADDR, m)
#define HWIO_LPASS_SCC_AON_DBG_M_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_AON_DBG_M_ADDR,v)
#define HWIO_LPASS_SCC_AON_DBG_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_AON_DBG_M_ADDR,m,v,HWIO_LPASS_SCC_AON_DBG_M_IN)
#define HWIO_LPASS_SCC_AON_DBG_M_M_BMSK                                                                                     0xff
#define HWIO_LPASS_SCC_AON_DBG_M_M_SHFT                                                                                      0x0

#define HWIO_LPASS_SCC_AON_DBG_N_ADDR                                                                                 (LPASS_CC_REG_BASE      + 0x0002d010)
#define HWIO_LPASS_SCC_AON_DBG_N_OFFS                                                                                 (LPASS_CC_REG_BASE_OFFS + 0x0002d010)
#define HWIO_LPASS_SCC_AON_DBG_N_RMSK                                                                                       0xff
#define HWIO_LPASS_SCC_AON_DBG_N_IN          \
        in_dword_masked(HWIO_LPASS_SCC_AON_DBG_N_ADDR, HWIO_LPASS_SCC_AON_DBG_N_RMSK)
#define HWIO_LPASS_SCC_AON_DBG_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_AON_DBG_N_ADDR, m)
#define HWIO_LPASS_SCC_AON_DBG_N_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_AON_DBG_N_ADDR,v)
#define HWIO_LPASS_SCC_AON_DBG_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_AON_DBG_N_ADDR,m,v,HWIO_LPASS_SCC_AON_DBG_N_IN)
#define HWIO_LPASS_SCC_AON_DBG_N_NOT_N_MINUS_M_BMSK                                                                         0xff
#define HWIO_LPASS_SCC_AON_DBG_N_NOT_N_MINUS_M_SHFT                                                                          0x0

#define HWIO_LPASS_SCC_AON_DBG_D_ADDR                                                                                 (LPASS_CC_REG_BASE      + 0x0002d014)
#define HWIO_LPASS_SCC_AON_DBG_D_OFFS                                                                                 (LPASS_CC_REG_BASE_OFFS + 0x0002d014)
#define HWIO_LPASS_SCC_AON_DBG_D_RMSK                                                                                       0xff
#define HWIO_LPASS_SCC_AON_DBG_D_IN          \
        in_dword_masked(HWIO_LPASS_SCC_AON_DBG_D_ADDR, HWIO_LPASS_SCC_AON_DBG_D_RMSK)
#define HWIO_LPASS_SCC_AON_DBG_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_AON_DBG_D_ADDR, m)
#define HWIO_LPASS_SCC_AON_DBG_D_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_AON_DBG_D_ADDR,v)
#define HWIO_LPASS_SCC_AON_DBG_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_AON_DBG_D_ADDR,m,v,HWIO_LPASS_SCC_AON_DBG_D_IN)
#define HWIO_LPASS_SCC_AON_DBG_D_NOT_2D_BMSK                                                                                0xff
#define HWIO_LPASS_SCC_AON_DBG_D_NOT_2D_SHFT                                                                                 0x0

#define HWIO_LPASS_ISLAND_SCC_AT_CBCR_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x0002d018)
#define HWIO_LPASS_ISLAND_SCC_AT_CBCR_OFFS                                                                            (LPASS_CC_REG_BASE_OFFS + 0x0002d018)
#define HWIO_LPASS_ISLAND_SCC_AT_CBCR_RMSK                                                                            0x80007ff1
#define HWIO_LPASS_ISLAND_SCC_AT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_AT_CBCR_ADDR, HWIO_LPASS_ISLAND_SCC_AT_CBCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_AT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_AT_CBCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_AT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_AT_CBCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_AT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_AT_CBCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_AT_CBCR_IN)
#define HWIO_LPASS_ISLAND_SCC_AT_CBCR_CLK_OFF_BMSK                                                                    0x80000000
#define HWIO_LPASS_ISLAND_SCC_AT_CBCR_CLK_OFF_SHFT                                                                          0x1f
#define HWIO_LPASS_ISLAND_SCC_AT_CBCR_FORCE_MEM_CORE_ON_BMSK                                                              0x4000
#define HWIO_LPASS_ISLAND_SCC_AT_CBCR_FORCE_MEM_CORE_ON_SHFT                                                                 0xe
#define HWIO_LPASS_ISLAND_SCC_AT_CBCR_FORCE_MEM_PERIPH_ON_BMSK                                                            0x2000
#define HWIO_LPASS_ISLAND_SCC_AT_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                                               0xd
#define HWIO_LPASS_ISLAND_SCC_AT_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                                                           0x1000
#define HWIO_LPASS_ISLAND_SCC_AT_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                                              0xc
#define HWIO_LPASS_ISLAND_SCC_AT_CBCR_WAKEUP_BMSK                                                                          0xf00
#define HWIO_LPASS_ISLAND_SCC_AT_CBCR_WAKEUP_SHFT                                                                            0x8
#define HWIO_LPASS_ISLAND_SCC_AT_CBCR_SLEEP_BMSK                                                                            0xf0
#define HWIO_LPASS_ISLAND_SCC_AT_CBCR_SLEEP_SHFT                                                                             0x4
#define HWIO_LPASS_ISLAND_SCC_AT_CBCR_CLK_ENABLE_BMSK                                                                        0x1
#define HWIO_LPASS_ISLAND_SCC_AT_CBCR_CLK_ENABLE_SHFT                                                                        0x0

#define HWIO_LPASS_ISLAND_SCC_Q6_ATBM_CBCR_ADDR                                                                       (LPASS_CC_REG_BASE      + 0x0002d01c)
#define HWIO_LPASS_ISLAND_SCC_Q6_ATBM_CBCR_OFFS                                                                       (LPASS_CC_REG_BASE_OFFS + 0x0002d01c)
#define HWIO_LPASS_ISLAND_SCC_Q6_ATBM_CBCR_RMSK                                                                       0x80000001
#define HWIO_LPASS_ISLAND_SCC_Q6_ATBM_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_Q6_ATBM_CBCR_ADDR, HWIO_LPASS_ISLAND_SCC_Q6_ATBM_CBCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_Q6_ATBM_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_Q6_ATBM_CBCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_Q6_ATBM_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_Q6_ATBM_CBCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_Q6_ATBM_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_Q6_ATBM_CBCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_Q6_ATBM_CBCR_IN)
#define HWIO_LPASS_ISLAND_SCC_Q6_ATBM_CBCR_CLK_OFF_BMSK                                                               0x80000000
#define HWIO_LPASS_ISLAND_SCC_Q6_ATBM_CBCR_CLK_OFF_SHFT                                                                     0x1f
#define HWIO_LPASS_ISLAND_SCC_Q6_ATBM_CBCR_CLK_ENABLE_BMSK                                                                   0x1
#define HWIO_LPASS_ISLAND_SCC_Q6_ATBM_CBCR_CLK_ENABLE_SHFT                                                                   0x0

#define HWIO_LPASS_ISLAND_SCC_PCLKDBG_CBCR_ADDR                                                                       (LPASS_CC_REG_BASE      + 0x0002d020)
#define HWIO_LPASS_ISLAND_SCC_PCLKDBG_CBCR_OFFS                                                                       (LPASS_CC_REG_BASE_OFFS + 0x0002d020)
#define HWIO_LPASS_ISLAND_SCC_PCLKDBG_CBCR_RMSK                                                                       0x80000001
#define HWIO_LPASS_ISLAND_SCC_PCLKDBG_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_PCLKDBG_CBCR_ADDR, HWIO_LPASS_ISLAND_SCC_PCLKDBG_CBCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_PCLKDBG_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_PCLKDBG_CBCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_PCLKDBG_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_PCLKDBG_CBCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_PCLKDBG_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_PCLKDBG_CBCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_PCLKDBG_CBCR_IN)
#define HWIO_LPASS_ISLAND_SCC_PCLKDBG_CBCR_CLK_OFF_BMSK                                                               0x80000000
#define HWIO_LPASS_ISLAND_SCC_PCLKDBG_CBCR_CLK_OFF_SHFT                                                                     0x1f
#define HWIO_LPASS_ISLAND_SCC_PCLKDBG_CBCR_CLK_ENABLE_BMSK                                                                   0x1
#define HWIO_LPASS_ISLAND_SCC_PCLKDBG_CBCR_CLK_ENABLE_SHFT                                                                   0x0

#define HWIO_LPASS_ISLAND_SCC_DBG_TSCTR_BCR_ADDR                                                                      (LPASS_CC_REG_BASE      + 0x0002e000)
#define HWIO_LPASS_ISLAND_SCC_DBG_TSCTR_BCR_OFFS                                                                      (LPASS_CC_REG_BASE_OFFS + 0x0002e000)
#define HWIO_LPASS_ISLAND_SCC_DBG_TSCTR_BCR_RMSK                                                                             0x1
#define HWIO_LPASS_ISLAND_SCC_DBG_TSCTR_BCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_DBG_TSCTR_BCR_ADDR, HWIO_LPASS_ISLAND_SCC_DBG_TSCTR_BCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_DBG_TSCTR_BCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_DBG_TSCTR_BCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_DBG_TSCTR_BCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_DBG_TSCTR_BCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_DBG_TSCTR_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_DBG_TSCTR_BCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_DBG_TSCTR_BCR_IN)
#define HWIO_LPASS_ISLAND_SCC_DBG_TSCTR_BCR_BLK_ARES_BMSK                                                                    0x1
#define HWIO_LPASS_ISLAND_SCC_DBG_TSCTR_BCR_BLK_ARES_SHFT                                                                    0x0

#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CMD_RCGR_ADDR                                                                    (LPASS_CC_REG_BASE      + 0x0002e004)
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CMD_RCGR_OFFS                                                                    (LPASS_CC_REG_BASE_OFFS + 0x0002e004)
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CMD_RCGR_RMSK                                                                    0x800000f3
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_SCC_AON_DBG_TSCTR_CMD_RCGR_ADDR, HWIO_LPASS_SCC_AON_DBG_TSCTR_CMD_RCGR_RMSK)
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_AON_DBG_TSCTR_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_AON_DBG_TSCTR_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_AON_DBG_TSCTR_CMD_RCGR_ADDR,m,v,HWIO_LPASS_SCC_AON_DBG_TSCTR_CMD_RCGR_IN)
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CMD_RCGR_ROOT_OFF_BMSK                                                           0x80000000
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CMD_RCGR_ROOT_OFF_SHFT                                                                 0x1f
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CMD_RCGR_DIRTY_D_BMSK                                                                  0x80
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CMD_RCGR_DIRTY_D_SHFT                                                                   0x7
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CMD_RCGR_DIRTY_N_BMSK                                                                  0x40
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CMD_RCGR_DIRTY_N_SHFT                                                                   0x6
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CMD_RCGR_DIRTY_M_BMSK                                                                  0x20
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CMD_RCGR_DIRTY_M_SHFT                                                                   0x5
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                           0x10
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                            0x4
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CMD_RCGR_ROOT_EN_BMSK                                                                   0x2
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CMD_RCGR_ROOT_EN_SHFT                                                                   0x1
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CMD_RCGR_UPDATE_BMSK                                                                    0x1
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CMD_RCGR_UPDATE_SHFT                                                                    0x0

#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CFG_RCGR_ADDR                                                                    (LPASS_CC_REG_BASE      + 0x0002e008)
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CFG_RCGR_OFFS                                                                    (LPASS_CC_REG_BASE_OFFS + 0x0002e008)
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CFG_RCGR_RMSK                                                                        0x771f
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_SCC_AON_DBG_TSCTR_CFG_RCGR_ADDR, HWIO_LPASS_SCC_AON_DBG_TSCTR_CFG_RCGR_RMSK)
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_AON_DBG_TSCTR_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_AON_DBG_TSCTR_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_AON_DBG_TSCTR_CFG_RCGR_ADDR,m,v,HWIO_LPASS_SCC_AON_DBG_TSCTR_CFG_RCGR_IN)
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CFG_RCGR_ALT_SRC_SEL_BMSK                                                            0x4000
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CFG_RCGR_ALT_SRC_SEL_SHFT                                                               0xe
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CFG_RCGR_MODE_BMSK                                                                   0x3000
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CFG_RCGR_MODE_SHFT                                                                      0xc
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CFG_RCGR_SRC_SEL_BMSK                                                                 0x700
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CFG_RCGR_SRC_SEL_SHFT                                                                   0x8
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CFG_RCGR_SRC_DIV_BMSK                                                                  0x1f
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CFG_RCGR_SRC_DIV_SHFT                                                                   0x0

#define HWIO_LPASS_SCC_AON_DBG_TSCTR_M_ADDR                                                                           (LPASS_CC_REG_BASE      + 0x0002e00c)
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_M_OFFS                                                                           (LPASS_CC_REG_BASE_OFFS + 0x0002e00c)
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_M_RMSK                                                                                 0xff
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_M_IN          \
        in_dword_masked(HWIO_LPASS_SCC_AON_DBG_TSCTR_M_ADDR, HWIO_LPASS_SCC_AON_DBG_TSCTR_M_RMSK)
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_AON_DBG_TSCTR_M_ADDR, m)
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_M_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_AON_DBG_TSCTR_M_ADDR,v)
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_AON_DBG_TSCTR_M_ADDR,m,v,HWIO_LPASS_SCC_AON_DBG_TSCTR_M_IN)
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_M_M_BMSK                                                                               0xff
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_M_M_SHFT                                                                                0x0

#define HWIO_LPASS_SCC_AON_DBG_TSCTR_N_ADDR                                                                           (LPASS_CC_REG_BASE      + 0x0002e010)
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_N_OFFS                                                                           (LPASS_CC_REG_BASE_OFFS + 0x0002e010)
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_N_RMSK                                                                                 0xff
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_N_IN          \
        in_dword_masked(HWIO_LPASS_SCC_AON_DBG_TSCTR_N_ADDR, HWIO_LPASS_SCC_AON_DBG_TSCTR_N_RMSK)
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_AON_DBG_TSCTR_N_ADDR, m)
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_N_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_AON_DBG_TSCTR_N_ADDR,v)
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_AON_DBG_TSCTR_N_ADDR,m,v,HWIO_LPASS_SCC_AON_DBG_TSCTR_N_IN)
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_N_NOT_N_MINUS_M_BMSK                                                                   0xff
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_N_NOT_N_MINUS_M_SHFT                                                                    0x0

#define HWIO_LPASS_SCC_AON_DBG_TSCTR_D_ADDR                                                                           (LPASS_CC_REG_BASE      + 0x0002e014)
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_D_OFFS                                                                           (LPASS_CC_REG_BASE_OFFS + 0x0002e014)
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_D_RMSK                                                                                 0xff
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_D_IN          \
        in_dword_masked(HWIO_LPASS_SCC_AON_DBG_TSCTR_D_ADDR, HWIO_LPASS_SCC_AON_DBG_TSCTR_D_RMSK)
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_AON_DBG_TSCTR_D_ADDR, m)
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_D_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_AON_DBG_TSCTR_D_ADDR,v)
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_AON_DBG_TSCTR_D_ADDR,m,v,HWIO_LPASS_SCC_AON_DBG_TSCTR_D_IN)
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_D_NOT_2D_BMSK                                                                          0xff
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_D_NOT_2D_SHFT                                                                           0x0

#define HWIO_LPASS_ISLAND_SCC_DBG_TSCTR_CBCR_ADDR                                                                     (LPASS_CC_REG_BASE      + 0x0002e018)
#define HWIO_LPASS_ISLAND_SCC_DBG_TSCTR_CBCR_OFFS                                                                     (LPASS_CC_REG_BASE_OFFS + 0x0002e018)
#define HWIO_LPASS_ISLAND_SCC_DBG_TSCTR_CBCR_RMSK                                                                     0x80070001
#define HWIO_LPASS_ISLAND_SCC_DBG_TSCTR_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_DBG_TSCTR_CBCR_ADDR, HWIO_LPASS_ISLAND_SCC_DBG_TSCTR_CBCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_DBG_TSCTR_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_DBG_TSCTR_CBCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_DBG_TSCTR_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_DBG_TSCTR_CBCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_DBG_TSCTR_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_DBG_TSCTR_CBCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_DBG_TSCTR_CBCR_IN)
#define HWIO_LPASS_ISLAND_SCC_DBG_TSCTR_CBCR_CLK_OFF_BMSK                                                             0x80000000
#define HWIO_LPASS_ISLAND_SCC_DBG_TSCTR_CBCR_CLK_OFF_SHFT                                                                   0x1f
#define HWIO_LPASS_ISLAND_SCC_DBG_TSCTR_CBCR_CLK_DIV_BMSK                                                                0x70000
#define HWIO_LPASS_ISLAND_SCC_DBG_TSCTR_CBCR_CLK_DIV_SHFT                                                                   0x10
#define HWIO_LPASS_ISLAND_SCC_DBG_TSCTR_CBCR_CLK_ENABLE_BMSK                                                                 0x1
#define HWIO_LPASS_ISLAND_SCC_DBG_TSCTR_CBCR_CLK_ENABLE_SHFT                                                                 0x0

#define HWIO_LPASS_AUDIO_WRAPPER_MPU_CFG_AON_CBCR_ADDR                                                                (LPASS_CC_REG_BASE      + 0x00031000)
#define HWIO_LPASS_AUDIO_WRAPPER_MPU_CFG_AON_CBCR_OFFS                                                                (LPASS_CC_REG_BASE_OFFS + 0x00031000)
#define HWIO_LPASS_AUDIO_WRAPPER_MPU_CFG_AON_CBCR_RMSK                                                                0x80000003
#define HWIO_LPASS_AUDIO_WRAPPER_MPU_CFG_AON_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_MPU_CFG_AON_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_MPU_CFG_AON_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_MPU_CFG_AON_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_MPU_CFG_AON_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_MPU_CFG_AON_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_MPU_CFG_AON_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_MPU_CFG_AON_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_MPU_CFG_AON_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_MPU_CFG_AON_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_MPU_CFG_AON_CBCR_CLK_OFF_BMSK                                                        0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_MPU_CFG_AON_CBCR_CLK_OFF_SHFT                                                              0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_MPU_CFG_AON_CBCR_HW_CTL_BMSK                                                                0x2
#define HWIO_LPASS_AUDIO_WRAPPER_MPU_CFG_AON_CBCR_HW_CTL_SHFT                                                                0x1
#define HWIO_LPASS_AUDIO_WRAPPER_MPU_CFG_AON_CBCR_CLK_ENABLE_BMSK                                                            0x1
#define HWIO_LPASS_AUDIO_WRAPPER_MPU_CFG_AON_CBCR_CLK_ENABLE_SHFT                                                            0x0

#define HWIO_LPASS_AUDIO_WRAPPER_Q6_AHBM_MPU_AON_CBCR_ADDR                                                            (LPASS_CC_REG_BASE      + 0x00032000)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_AHBM_MPU_AON_CBCR_OFFS                                                            (LPASS_CC_REG_BASE_OFFS + 0x00032000)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_AHBM_MPU_AON_CBCR_RMSK                                                            0x80000003
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_AHBM_MPU_AON_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_Q6_AHBM_MPU_AON_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_Q6_AHBM_MPU_AON_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_AHBM_MPU_AON_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_Q6_AHBM_MPU_AON_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_AHBM_MPU_AON_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_Q6_AHBM_MPU_AON_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_AHBM_MPU_AON_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_Q6_AHBM_MPU_AON_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_Q6_AHBM_MPU_AON_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_AHBM_MPU_AON_CBCR_CLK_OFF_BMSK                                                    0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_AHBM_MPU_AON_CBCR_CLK_OFF_SHFT                                                          0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_AHBM_MPU_AON_CBCR_HW_CTL_BMSK                                                            0x2
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_AHBM_MPU_AON_CBCR_HW_CTL_SHFT                                                            0x1
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_AHBM_MPU_AON_CBCR_CLK_ENABLE_BMSK                                                        0x1
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_AHBM_MPU_AON_CBCR_CLK_ENABLE_SHFT                                                        0x0

#define HWIO_LPASS_Q6SS_AHBS_AON_CBCR_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x00033000)
#define HWIO_LPASS_Q6SS_AHBS_AON_CBCR_OFFS                                                                            (LPASS_CC_REG_BASE_OFFS + 0x00033000)
#define HWIO_LPASS_Q6SS_AHBS_AON_CBCR_RMSK                                                                            0x80000003
#define HWIO_LPASS_Q6SS_AHBS_AON_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_Q6SS_AHBS_AON_CBCR_ADDR, HWIO_LPASS_Q6SS_AHBS_AON_CBCR_RMSK)
#define HWIO_LPASS_Q6SS_AHBS_AON_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_Q6SS_AHBS_AON_CBCR_ADDR, m)
#define HWIO_LPASS_Q6SS_AHBS_AON_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_Q6SS_AHBS_AON_CBCR_ADDR,v)
#define HWIO_LPASS_Q6SS_AHBS_AON_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_Q6SS_AHBS_AON_CBCR_ADDR,m,v,HWIO_LPASS_Q6SS_AHBS_AON_CBCR_IN)
#define HWIO_LPASS_Q6SS_AHBS_AON_CBCR_CLK_OFF_BMSK                                                                    0x80000000
#define HWIO_LPASS_Q6SS_AHBS_AON_CBCR_CLK_OFF_SHFT                                                                          0x1f
#define HWIO_LPASS_Q6SS_AHBS_AON_CBCR_HW_CTL_BMSK                                                                            0x2
#define HWIO_LPASS_Q6SS_AHBS_AON_CBCR_HW_CTL_SHFT                                                                            0x1
#define HWIO_LPASS_Q6SS_AHBS_AON_CBCR_CLK_ENABLE_BMSK                                                                        0x1
#define HWIO_LPASS_Q6SS_AHBS_AON_CBCR_CLK_ENABLE_SHFT                                                                        0x0

#define HWIO_LPASS_DFS_HW_CTL_ADDR                                                                                    (LPASS_CC_REG_BASE      + 0x00034000)
#define HWIO_LPASS_DFS_HW_CTL_OFFS                                                                                    (LPASS_CC_REG_BASE_OFFS + 0x00034000)
#define HWIO_LPASS_DFS_HW_CTL_RMSK                                                                                    0x70000071
#define HWIO_LPASS_DFS_HW_CTL_IN          \
        in_dword_masked(HWIO_LPASS_DFS_HW_CTL_ADDR, HWIO_LPASS_DFS_HW_CTL_RMSK)
#define HWIO_LPASS_DFS_HW_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_HW_CTL_ADDR, m)
#define HWIO_LPASS_DFS_HW_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_HW_CTL_ADDR,v)
#define HWIO_LPASS_DFS_HW_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_HW_CTL_ADDR,m,v,HWIO_LPASS_DFS_HW_CTL_IN)
#define HWIO_LPASS_DFS_HW_CTL_DFS_PERF_STATE_OUT_BMSK                                                                 0x70000000
#define HWIO_LPASS_DFS_HW_CTL_DFS_PERF_STATE_OUT_SHFT                                                                       0x1c
#define HWIO_LPASS_DFS_HW_CTL_DFS_PERF_STATE_BMSK                                                                           0x70
#define HWIO_LPASS_DFS_HW_CTL_DFS_PERF_STATE_SHFT                                                                            0x4
#define HWIO_LPASS_DFS_HW_CTL_DFS_HW_CTL_EN_BMSK                                                                             0x1
#define HWIO_LPASS_DFS_HW_CTL_DFS_HW_CTL_EN_SHFT                                                                             0x0

#define HWIO_LPASS_DFS_PERF0_RCG_SRC_SEL_ADDR                                                                         (LPASS_CC_REG_BASE      + 0x00034004)
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_SEL_OFFS                                                                         (LPASS_CC_REG_BASE_OFFS + 0x00034004)
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_SEL_RMSK                                                                              0x777
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_SEL_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF0_RCG_SRC_SEL_ADDR, HWIO_LPASS_DFS_PERF0_RCG_SRC_SEL_RMSK)
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_SEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF0_RCG_SRC_SEL_ADDR, m)
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_SEL_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF0_RCG_SRC_SEL_ADDR,v)
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF0_RCG_SRC_SEL_ADDR,m,v,HWIO_LPASS_DFS_PERF0_RCG_SRC_SEL_IN)
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_SEL_PERF0_RESAMPLER_RCG_SRC_SEL_BMSK                                                  0x700
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_SEL_PERF0_RESAMPLER_RCG_SRC_SEL_SHFT                                                    0x8
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_SEL_PERF0_CORE_RCG_SRC_SEL_BMSK                                                        0x70
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_SEL_PERF0_CORE_RCG_SRC_SEL_SHFT                                                         0x4
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_SEL_PERF0_AON_RCG_SRC_SEL_BMSK                                                          0x7
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_SEL_PERF0_AON_RCG_SRC_SEL_SHFT                                                          0x0

#define HWIO_LPASS_DFS_PERF1_RCG_SRC_SEL_ADDR                                                                         (LPASS_CC_REG_BASE      + 0x00034008)
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_SEL_OFFS                                                                         (LPASS_CC_REG_BASE_OFFS + 0x00034008)
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_SEL_RMSK                                                                              0x777
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_SEL_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF1_RCG_SRC_SEL_ADDR, HWIO_LPASS_DFS_PERF1_RCG_SRC_SEL_RMSK)
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_SEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF1_RCG_SRC_SEL_ADDR, m)
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_SEL_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF1_RCG_SRC_SEL_ADDR,v)
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF1_RCG_SRC_SEL_ADDR,m,v,HWIO_LPASS_DFS_PERF1_RCG_SRC_SEL_IN)
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_SEL_PERF1_RESAMPLER_RCG_SRC_SEL_BMSK                                                  0x700
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_SEL_PERF1_RESAMPLER_RCG_SRC_SEL_SHFT                                                    0x8
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_SEL_PERF1_CORE_RCG_SRC_SEL_BMSK                                                        0x70
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_SEL_PERF1_CORE_RCG_SRC_SEL_SHFT                                                         0x4
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_SEL_PERF1_AON_RCG_SRC_SEL_BMSK                                                          0x7
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_SEL_PERF1_AON_RCG_SRC_SEL_SHFT                                                          0x0

#define HWIO_LPASS_DFS_PERF2_RCG_SRC_SEL_ADDR                                                                         (LPASS_CC_REG_BASE      + 0x0003400c)
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_SEL_OFFS                                                                         (LPASS_CC_REG_BASE_OFFS + 0x0003400c)
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_SEL_RMSK                                                                              0x777
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_SEL_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF2_RCG_SRC_SEL_ADDR, HWIO_LPASS_DFS_PERF2_RCG_SRC_SEL_RMSK)
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_SEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF2_RCG_SRC_SEL_ADDR, m)
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_SEL_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF2_RCG_SRC_SEL_ADDR,v)
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF2_RCG_SRC_SEL_ADDR,m,v,HWIO_LPASS_DFS_PERF2_RCG_SRC_SEL_IN)
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_SEL_PERF2_RESAMPLER_RCG_SRC_SEL_BMSK                                                  0x700
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_SEL_PERF2_RESAMPLER_RCG_SRC_SEL_SHFT                                                    0x8
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_SEL_PERF2_CORE_RCG_SRC_SEL_BMSK                                                        0x70
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_SEL_PERF2_CORE_RCG_SRC_SEL_SHFT                                                         0x4
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_SEL_PERF2_AON_RCG_SRC_SEL_BMSK                                                          0x7
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_SEL_PERF2_AON_RCG_SRC_SEL_SHFT                                                          0x0

#define HWIO_LPASS_DFS_PERF3_RCG_SRC_SEL_ADDR                                                                         (LPASS_CC_REG_BASE      + 0x00034010)
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_SEL_OFFS                                                                         (LPASS_CC_REG_BASE_OFFS + 0x00034010)
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_SEL_RMSK                                                                              0x777
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_SEL_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF3_RCG_SRC_SEL_ADDR, HWIO_LPASS_DFS_PERF3_RCG_SRC_SEL_RMSK)
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_SEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF3_RCG_SRC_SEL_ADDR, m)
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_SEL_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF3_RCG_SRC_SEL_ADDR,v)
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF3_RCG_SRC_SEL_ADDR,m,v,HWIO_LPASS_DFS_PERF3_RCG_SRC_SEL_IN)
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_SEL_PERF3_RESAMPLER_RCG_SRC_SEL_BMSK                                                  0x700
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_SEL_PERF3_RESAMPLER_RCG_SRC_SEL_SHFT                                                    0x8
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_SEL_PERF3_CORE_RCG_SRC_SEL_BMSK                                                        0x70
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_SEL_PERF3_CORE_RCG_SRC_SEL_SHFT                                                         0x4
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_SEL_PERF3_AON_RCG_SRC_SEL_BMSK                                                          0x7
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_SEL_PERF3_AON_RCG_SRC_SEL_SHFT                                                          0x0

#define HWIO_LPASS_DFS_PERF4_RCG_SRC_SEL_ADDR                                                                         (LPASS_CC_REG_BASE      + 0x00034014)
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_SEL_OFFS                                                                         (LPASS_CC_REG_BASE_OFFS + 0x00034014)
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_SEL_RMSK                                                                              0x777
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_SEL_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF4_RCG_SRC_SEL_ADDR, HWIO_LPASS_DFS_PERF4_RCG_SRC_SEL_RMSK)
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_SEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF4_RCG_SRC_SEL_ADDR, m)
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_SEL_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF4_RCG_SRC_SEL_ADDR,v)
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF4_RCG_SRC_SEL_ADDR,m,v,HWIO_LPASS_DFS_PERF4_RCG_SRC_SEL_IN)
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_SEL_PERF4_RESAMPLER_RCG_SRC_SEL_BMSK                                                  0x700
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_SEL_PERF4_RESAMPLER_RCG_SRC_SEL_SHFT                                                    0x8
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_SEL_PERF4_CORE_RCG_SRC_SEL_BMSK                                                        0x70
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_SEL_PERF4_CORE_RCG_SRC_SEL_SHFT                                                         0x4
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_SEL_PERF4_AON_RCG_SRC_SEL_BMSK                                                          0x7
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_SEL_PERF4_AON_RCG_SRC_SEL_SHFT                                                          0x0

#define HWIO_LPASS_DFS_PERF5_RCG_SRC_SEL_ADDR                                                                         (LPASS_CC_REG_BASE      + 0x00034018)
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_SEL_OFFS                                                                         (LPASS_CC_REG_BASE_OFFS + 0x00034018)
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_SEL_RMSK                                                                              0x777
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_SEL_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF5_RCG_SRC_SEL_ADDR, HWIO_LPASS_DFS_PERF5_RCG_SRC_SEL_RMSK)
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_SEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF5_RCG_SRC_SEL_ADDR, m)
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_SEL_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF5_RCG_SRC_SEL_ADDR,v)
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF5_RCG_SRC_SEL_ADDR,m,v,HWIO_LPASS_DFS_PERF5_RCG_SRC_SEL_IN)
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_SEL_PERF5_RESAMPLER_RCG_SRC_SEL_BMSK                                                  0x700
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_SEL_PERF5_RESAMPLER_RCG_SRC_SEL_SHFT                                                    0x8
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_SEL_PERF5_CORE_RCG_SRC_SEL_BMSK                                                        0x70
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_SEL_PERF5_CORE_RCG_SRC_SEL_SHFT                                                         0x4
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_SEL_PERF5_AON_RCG_SRC_SEL_BMSK                                                          0x7
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_SEL_PERF5_AON_RCG_SRC_SEL_SHFT                                                          0x0

#define HWIO_LPASS_DFS_PERF6_RCG_SRC_SEL_ADDR                                                                         (LPASS_CC_REG_BASE      + 0x0003401c)
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_SEL_OFFS                                                                         (LPASS_CC_REG_BASE_OFFS + 0x0003401c)
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_SEL_RMSK                                                                              0x777
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_SEL_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF6_RCG_SRC_SEL_ADDR, HWIO_LPASS_DFS_PERF6_RCG_SRC_SEL_RMSK)
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_SEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF6_RCG_SRC_SEL_ADDR, m)
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_SEL_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF6_RCG_SRC_SEL_ADDR,v)
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF6_RCG_SRC_SEL_ADDR,m,v,HWIO_LPASS_DFS_PERF6_RCG_SRC_SEL_IN)
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_SEL_PERF6_RESAMPLER_RCG_SRC_SEL_BMSK                                                  0x700
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_SEL_PERF6_RESAMPLER_RCG_SRC_SEL_SHFT                                                    0x8
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_SEL_PERF6_CORE_RCG_SRC_SEL_BMSK                                                        0x70
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_SEL_PERF6_CORE_RCG_SRC_SEL_SHFT                                                         0x4
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_SEL_PERF6_AON_RCG_SRC_SEL_BMSK                                                          0x7
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_SEL_PERF6_AON_RCG_SRC_SEL_SHFT                                                          0x0

#define HWIO_LPASS_DFS_PERF7_RCG_SRC_SEL_ADDR                                                                         (LPASS_CC_REG_BASE      + 0x00034020)
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_SEL_OFFS                                                                         (LPASS_CC_REG_BASE_OFFS + 0x00034020)
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_SEL_RMSK                                                                              0x777
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_SEL_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF7_RCG_SRC_SEL_ADDR, HWIO_LPASS_DFS_PERF7_RCG_SRC_SEL_RMSK)
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_SEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF7_RCG_SRC_SEL_ADDR, m)
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_SEL_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF7_RCG_SRC_SEL_ADDR,v)
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF7_RCG_SRC_SEL_ADDR,m,v,HWIO_LPASS_DFS_PERF7_RCG_SRC_SEL_IN)
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_SEL_PERF7_RESAMPLER_RCG_SRC_SEL_BMSK                                                  0x700
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_SEL_PERF7_RESAMPLER_RCG_SRC_SEL_SHFT                                                    0x8
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_SEL_PERF7_CORE_RCG_SRC_SEL_BMSK                                                        0x70
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_SEL_PERF7_CORE_RCG_SRC_SEL_SHFT                                                         0x4
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_SEL_PERF7_AON_RCG_SRC_SEL_BMSK                                                          0x7
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_SEL_PERF7_AON_RCG_SRC_SEL_SHFT                                                          0x0

#define HWIO_LPASS_DFS_PERF0_RCG_SRC_DIV_ADDR                                                                         (LPASS_CC_REG_BASE      + 0x00034024)
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_DIV_OFFS                                                                         (LPASS_CC_REG_BASE_OFFS + 0x00034024)
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_DIV_RMSK                                                                           0x1f1f1f
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_DIV_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF0_RCG_SRC_DIV_ADDR, HWIO_LPASS_DFS_PERF0_RCG_SRC_DIV_RMSK)
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_DIV_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF0_RCG_SRC_DIV_ADDR, m)
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_DIV_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF0_RCG_SRC_DIV_ADDR,v)
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_DIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF0_RCG_SRC_DIV_ADDR,m,v,HWIO_LPASS_DFS_PERF0_RCG_SRC_DIV_IN)
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_DIV_PERF0_RESAMPLER_RCG_SRC_DIV_BMSK                                               0x1f0000
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_DIV_PERF0_RESAMPLER_RCG_SRC_DIV_SHFT                                                   0x10
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_DIV_PERF0_CORE_RCG_SRC_DIV_BMSK                                                      0x1f00
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_DIV_PERF0_CORE_RCG_SRC_DIV_SHFT                                                         0x8
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_DIV_PERF0_AON_RCG_SRC_DIV_BMSK                                                         0x1f
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_DIV_PERF0_AON_RCG_SRC_DIV_SHFT                                                          0x0

#define HWIO_LPASS_DFS_PERF1_RCG_SRC_DIV_ADDR                                                                         (LPASS_CC_REG_BASE      + 0x00034028)
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_DIV_OFFS                                                                         (LPASS_CC_REG_BASE_OFFS + 0x00034028)
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_DIV_RMSK                                                                           0x1f1f1f
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_DIV_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF1_RCG_SRC_DIV_ADDR, HWIO_LPASS_DFS_PERF1_RCG_SRC_DIV_RMSK)
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_DIV_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF1_RCG_SRC_DIV_ADDR, m)
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_DIV_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF1_RCG_SRC_DIV_ADDR,v)
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_DIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF1_RCG_SRC_DIV_ADDR,m,v,HWIO_LPASS_DFS_PERF1_RCG_SRC_DIV_IN)
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_DIV_PERF1_RESAMPLER_RCG_SRC_DIV_BMSK                                               0x1f0000
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_DIV_PERF1_RESAMPLER_RCG_SRC_DIV_SHFT                                                   0x10
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_DIV_PERF1_CORE_RCG_SRC_DIV_BMSK                                                      0x1f00
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_DIV_PERF1_CORE_RCG_SRC_DIV_SHFT                                                         0x8
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_DIV_PERF1_AON_RCG_SRC_DIV_BMSK                                                         0x1f
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_DIV_PERF1_AON_RCG_SRC_DIV_SHFT                                                          0x0

#define HWIO_LPASS_DFS_PERF2_RCG_SRC_DIV_ADDR                                                                         (LPASS_CC_REG_BASE      + 0x0003402c)
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_DIV_OFFS                                                                         (LPASS_CC_REG_BASE_OFFS + 0x0003402c)
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_DIV_RMSK                                                                           0x1f1f1f
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_DIV_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF2_RCG_SRC_DIV_ADDR, HWIO_LPASS_DFS_PERF2_RCG_SRC_DIV_RMSK)
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_DIV_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF2_RCG_SRC_DIV_ADDR, m)
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_DIV_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF2_RCG_SRC_DIV_ADDR,v)
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_DIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF2_RCG_SRC_DIV_ADDR,m,v,HWIO_LPASS_DFS_PERF2_RCG_SRC_DIV_IN)
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_DIV_PERF2_RESAMPLER_RCG_SRC_DIV_BMSK                                               0x1f0000
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_DIV_PERF2_RESAMPLER_RCG_SRC_DIV_SHFT                                                   0x10
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_DIV_PERF2_CORE_RCG_SRC_DIV_BMSK                                                      0x1f00
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_DIV_PERF2_CORE_RCG_SRC_DIV_SHFT                                                         0x8
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_DIV_PERF2_AON_RCG_SRC_DIV_BMSK                                                         0x1f
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_DIV_PERF2_AON_RCG_SRC_DIV_SHFT                                                          0x0

#define HWIO_LPASS_DFS_PERF3_RCG_SRC_DIV_ADDR                                                                         (LPASS_CC_REG_BASE      + 0x00034030)
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_DIV_OFFS                                                                         (LPASS_CC_REG_BASE_OFFS + 0x00034030)
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_DIV_RMSK                                                                           0x1f1f1f
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_DIV_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF3_RCG_SRC_DIV_ADDR, HWIO_LPASS_DFS_PERF3_RCG_SRC_DIV_RMSK)
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_DIV_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF3_RCG_SRC_DIV_ADDR, m)
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_DIV_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF3_RCG_SRC_DIV_ADDR,v)
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_DIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF3_RCG_SRC_DIV_ADDR,m,v,HWIO_LPASS_DFS_PERF3_RCG_SRC_DIV_IN)
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_DIV_PERF3_RESAMPLER_RCG_SRC_DIV_BMSK                                               0x1f0000
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_DIV_PERF3_RESAMPLER_RCG_SRC_DIV_SHFT                                                   0x10
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_DIV_PERF3_CORE_RCG_SRC_DIV_BMSK                                                      0x1f00
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_DIV_PERF3_CORE_RCG_SRC_DIV_SHFT                                                         0x8
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_DIV_PERF3_AON_RCG_SRC_DIV_BMSK                                                         0x1f
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_DIV_PERF3_AON_RCG_SRC_DIV_SHFT                                                          0x0

#define HWIO_LPASS_DFS_PERF4_RCG_SRC_DIV_ADDR                                                                         (LPASS_CC_REG_BASE      + 0x00034034)
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_DIV_OFFS                                                                         (LPASS_CC_REG_BASE_OFFS + 0x00034034)
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_DIV_RMSK                                                                           0x1f1f1f
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_DIV_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF4_RCG_SRC_DIV_ADDR, HWIO_LPASS_DFS_PERF4_RCG_SRC_DIV_RMSK)
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_DIV_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF4_RCG_SRC_DIV_ADDR, m)
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_DIV_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF4_RCG_SRC_DIV_ADDR,v)
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_DIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF4_RCG_SRC_DIV_ADDR,m,v,HWIO_LPASS_DFS_PERF4_RCG_SRC_DIV_IN)
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_DIV_PERF4_RESAMPLER_RCG_SRC_DIV_BMSK                                               0x1f0000
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_DIV_PERF4_RESAMPLER_RCG_SRC_DIV_SHFT                                                   0x10
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_DIV_PERF4_CORE_RCG_SRC_DIV_BMSK                                                      0x1f00
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_DIV_PERF4_CORE_RCG_SRC_DIV_SHFT                                                         0x8
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_DIV_PERF4_AON_RCG_SRC_DIV_BMSK                                                         0x1f
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_DIV_PERF4_AON_RCG_SRC_DIV_SHFT                                                          0x0

#define HWIO_LPASS_DFS_PERF5_RCG_SRC_DIV_ADDR                                                                         (LPASS_CC_REG_BASE      + 0x00034038)
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_DIV_OFFS                                                                         (LPASS_CC_REG_BASE_OFFS + 0x00034038)
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_DIV_RMSK                                                                           0x1f1f1f
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_DIV_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF5_RCG_SRC_DIV_ADDR, HWIO_LPASS_DFS_PERF5_RCG_SRC_DIV_RMSK)
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_DIV_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF5_RCG_SRC_DIV_ADDR, m)
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_DIV_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF5_RCG_SRC_DIV_ADDR,v)
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_DIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF5_RCG_SRC_DIV_ADDR,m,v,HWIO_LPASS_DFS_PERF5_RCG_SRC_DIV_IN)
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_DIV_PERF5_RESAMPLER_RCG_SRC_DIV_BMSK                                               0x1f0000
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_DIV_PERF5_RESAMPLER_RCG_SRC_DIV_SHFT                                                   0x10
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_DIV_PERF5_CORE_RCG_SRC_DIV_BMSK                                                      0x1f00
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_DIV_PERF5_CORE_RCG_SRC_DIV_SHFT                                                         0x8
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_DIV_PERF5_AON_RCG_SRC_DIV_BMSK                                                         0x1f
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_DIV_PERF5_AON_RCG_SRC_DIV_SHFT                                                          0x0

#define HWIO_LPASS_DFS_PERF6_RCG_SRC_DIV_ADDR                                                                         (LPASS_CC_REG_BASE      + 0x0003403c)
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_DIV_OFFS                                                                         (LPASS_CC_REG_BASE_OFFS + 0x0003403c)
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_DIV_RMSK                                                                           0x1f1f1f
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_DIV_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF6_RCG_SRC_DIV_ADDR, HWIO_LPASS_DFS_PERF6_RCG_SRC_DIV_RMSK)
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_DIV_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF6_RCG_SRC_DIV_ADDR, m)
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_DIV_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF6_RCG_SRC_DIV_ADDR,v)
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_DIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF6_RCG_SRC_DIV_ADDR,m,v,HWIO_LPASS_DFS_PERF6_RCG_SRC_DIV_IN)
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_DIV_PERF6_RESAMPLER_RCG_SRC_DIV_BMSK                                               0x1f0000
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_DIV_PERF6_RESAMPLER_RCG_SRC_DIV_SHFT                                                   0x10
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_DIV_PERF6_CORE_RCG_SRC_DIV_BMSK                                                      0x1f00
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_DIV_PERF6_CORE_RCG_SRC_DIV_SHFT                                                         0x8
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_DIV_PERF6_AON_RCG_SRC_DIV_BMSK                                                         0x1f
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_DIV_PERF6_AON_RCG_SRC_DIV_SHFT                                                          0x0

#define HWIO_LPASS_DFS_PERF7_RCG_SRC_DIV_ADDR                                                                         (LPASS_CC_REG_BASE      + 0x00034040)
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_DIV_OFFS                                                                         (LPASS_CC_REG_BASE_OFFS + 0x00034040)
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_DIV_RMSK                                                                           0x1f1f1f
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_DIV_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF7_RCG_SRC_DIV_ADDR, HWIO_LPASS_DFS_PERF7_RCG_SRC_DIV_RMSK)
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_DIV_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF7_RCG_SRC_DIV_ADDR, m)
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_DIV_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF7_RCG_SRC_DIV_ADDR,v)
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_DIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF7_RCG_SRC_DIV_ADDR,m,v,HWIO_LPASS_DFS_PERF7_RCG_SRC_DIV_IN)
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_DIV_PERF7_RESAMPLER_RCG_SRC_DIV_BMSK                                               0x1f0000
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_DIV_PERF7_RESAMPLER_RCG_SRC_DIV_SHFT                                                   0x10
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_DIV_PERF7_CORE_RCG_SRC_DIV_BMSK                                                      0x1f00
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_DIV_PERF7_CORE_RCG_SRC_DIV_SHFT                                                         0x8
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_DIV_PERF7_AON_RCG_SRC_DIV_BMSK                                                         0x1f
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_DIV_PERF7_AON_RCG_SRC_DIV_SHFT                                                          0x0

#define HWIO_LPASS_DFS_RCG_ASYNC_CLK_EN_ADDR                                                                          (LPASS_CC_REG_BASE      + 0x00034044)
#define HWIO_LPASS_DFS_RCG_ASYNC_CLK_EN_OFFS                                                                          (LPASS_CC_REG_BASE_OFFS + 0x00034044)
#define HWIO_LPASS_DFS_RCG_ASYNC_CLK_EN_RMSK                                                                                 0x7
#define HWIO_LPASS_DFS_RCG_ASYNC_CLK_EN_IN          \
        in_dword_masked(HWIO_LPASS_DFS_RCG_ASYNC_CLK_EN_ADDR, HWIO_LPASS_DFS_RCG_ASYNC_CLK_EN_RMSK)
#define HWIO_LPASS_DFS_RCG_ASYNC_CLK_EN_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_RCG_ASYNC_CLK_EN_ADDR, m)
#define HWIO_LPASS_DFS_RCG_ASYNC_CLK_EN_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_RCG_ASYNC_CLK_EN_ADDR,v)
#define HWIO_LPASS_DFS_RCG_ASYNC_CLK_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_RCG_ASYNC_CLK_EN_ADDR,m,v,HWIO_LPASS_DFS_RCG_ASYNC_CLK_EN_IN)
#define HWIO_LPASS_DFS_RCG_ASYNC_CLK_EN_RESAMPLER_RCG_ASYNC_CLK_EN_BMSK                                                      0x4
#define HWIO_LPASS_DFS_RCG_ASYNC_CLK_EN_RESAMPLER_RCG_ASYNC_CLK_EN_SHFT                                                      0x2
#define HWIO_LPASS_DFS_RCG_ASYNC_CLK_EN_CORE_RCG_ASYNC_CLK_EN_BMSK                                                           0x2
#define HWIO_LPASS_DFS_RCG_ASYNC_CLK_EN_CORE_RCG_ASYNC_CLK_EN_SHFT                                                           0x1
#define HWIO_LPASS_DFS_RCG_ASYNC_CLK_EN_AON_RCG_ASYNC_CLK_EN_BMSK                                                            0x1
#define HWIO_LPASS_DFS_RCG_ASYNC_CLK_EN_AON_RCG_ASYNC_CLK_EN_SHFT                                                            0x0

#define HWIO_LPASS_DFS_PERF0_CDIV_ADDR                                                                                (LPASS_CC_REG_BASE      + 0x00034048)
#define HWIO_LPASS_DFS_PERF0_CDIV_OFFS                                                                                (LPASS_CC_REG_BASE_OFFS + 0x00034048)
#define HWIO_LPASS_DFS_PERF0_CDIV_RMSK                                                                                      0x77
#define HWIO_LPASS_DFS_PERF0_CDIV_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF0_CDIV_ADDR, HWIO_LPASS_DFS_PERF0_CDIV_RMSK)
#define HWIO_LPASS_DFS_PERF0_CDIV_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF0_CDIV_ADDR, m)
#define HWIO_LPASS_DFS_PERF0_CDIV_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF0_CDIV_ADDR,v)
#define HWIO_LPASS_DFS_PERF0_CDIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF0_CDIV_ADDR,m,v,HWIO_LPASS_DFS_PERF0_CDIV_IN)
#define HWIO_LPASS_DFS_PERF0_CDIV_PERF0_LPAAUDIO_PLL_MAIN_SVS_CDIV_BMSK                                                     0x70
#define HWIO_LPASS_DFS_PERF0_CDIV_PERF0_LPAAUDIO_PLL_MAIN_SVS_CDIV_SHFT                                                      0x4
#define HWIO_LPASS_DFS_PERF0_CDIV_PERF0_LPAAUDIO_DIG_PLL_EARLY_SVS_CDIV_BMSK                                                 0x7
#define HWIO_LPASS_DFS_PERF0_CDIV_PERF0_LPAAUDIO_DIG_PLL_EARLY_SVS_CDIV_SHFT                                                 0x0

#define HWIO_LPASS_DFS_PERF1_CDIV_ADDR                                                                                (LPASS_CC_REG_BASE      + 0x0003404c)
#define HWIO_LPASS_DFS_PERF1_CDIV_OFFS                                                                                (LPASS_CC_REG_BASE_OFFS + 0x0003404c)
#define HWIO_LPASS_DFS_PERF1_CDIV_RMSK                                                                                      0x77
#define HWIO_LPASS_DFS_PERF1_CDIV_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF1_CDIV_ADDR, HWIO_LPASS_DFS_PERF1_CDIV_RMSK)
#define HWIO_LPASS_DFS_PERF1_CDIV_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF1_CDIV_ADDR, m)
#define HWIO_LPASS_DFS_PERF1_CDIV_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF1_CDIV_ADDR,v)
#define HWIO_LPASS_DFS_PERF1_CDIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF1_CDIV_ADDR,m,v,HWIO_LPASS_DFS_PERF1_CDIV_IN)
#define HWIO_LPASS_DFS_PERF1_CDIV_PERF1_LPAAUDIO_PLL_MAIN_SVS_CDIV_BMSK                                                     0x70
#define HWIO_LPASS_DFS_PERF1_CDIV_PERF1_LPAAUDIO_PLL_MAIN_SVS_CDIV_SHFT                                                      0x4
#define HWIO_LPASS_DFS_PERF1_CDIV_PERF1_LPAAUDIO_DIG_PLL_EARLY_SVS_CDIV_BMSK                                                 0x7
#define HWIO_LPASS_DFS_PERF1_CDIV_PERF1_LPAAUDIO_DIG_PLL_EARLY_SVS_CDIV_SHFT                                                 0x0

#define HWIO_LPASS_DFS_PERF2_CDIV_ADDR                                                                                (LPASS_CC_REG_BASE      + 0x00034050)
#define HWIO_LPASS_DFS_PERF2_CDIV_OFFS                                                                                (LPASS_CC_REG_BASE_OFFS + 0x00034050)
#define HWIO_LPASS_DFS_PERF2_CDIV_RMSK                                                                                      0x77
#define HWIO_LPASS_DFS_PERF2_CDIV_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF2_CDIV_ADDR, HWIO_LPASS_DFS_PERF2_CDIV_RMSK)
#define HWIO_LPASS_DFS_PERF2_CDIV_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF2_CDIV_ADDR, m)
#define HWIO_LPASS_DFS_PERF2_CDIV_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF2_CDIV_ADDR,v)
#define HWIO_LPASS_DFS_PERF2_CDIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF2_CDIV_ADDR,m,v,HWIO_LPASS_DFS_PERF2_CDIV_IN)
#define HWIO_LPASS_DFS_PERF2_CDIV_PERF2_LPAAUDIO_PLL_MAIN_SVS_CDIV_BMSK                                                     0x70
#define HWIO_LPASS_DFS_PERF2_CDIV_PERF2_LPAAUDIO_PLL_MAIN_SVS_CDIV_SHFT                                                      0x4
#define HWIO_LPASS_DFS_PERF2_CDIV_PERF2_LPAAUDIO_DIG_PLL_EARLY_SVS_CDIV_BMSK                                                 0x7
#define HWIO_LPASS_DFS_PERF2_CDIV_PERF2_LPAAUDIO_DIG_PLL_EARLY_SVS_CDIV_SHFT                                                 0x0

#define HWIO_LPASS_DFS_PERF3_CDIV_ADDR                                                                                (LPASS_CC_REG_BASE      + 0x00034054)
#define HWIO_LPASS_DFS_PERF3_CDIV_OFFS                                                                                (LPASS_CC_REG_BASE_OFFS + 0x00034054)
#define HWIO_LPASS_DFS_PERF3_CDIV_RMSK                                                                                      0x77
#define HWIO_LPASS_DFS_PERF3_CDIV_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF3_CDIV_ADDR, HWIO_LPASS_DFS_PERF3_CDIV_RMSK)
#define HWIO_LPASS_DFS_PERF3_CDIV_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF3_CDIV_ADDR, m)
#define HWIO_LPASS_DFS_PERF3_CDIV_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF3_CDIV_ADDR,v)
#define HWIO_LPASS_DFS_PERF3_CDIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF3_CDIV_ADDR,m,v,HWIO_LPASS_DFS_PERF3_CDIV_IN)
#define HWIO_LPASS_DFS_PERF3_CDIV_PERF3_LPAAUDIO_PLL_MAIN_SVS_CDIV_BMSK                                                     0x70
#define HWIO_LPASS_DFS_PERF3_CDIV_PERF3_LPAAUDIO_PLL_MAIN_SVS_CDIV_SHFT                                                      0x4
#define HWIO_LPASS_DFS_PERF3_CDIV_PERF3_LPAAUDIO_DIG_PLL_EARLY_SVS_CDIV_BMSK                                                 0x7
#define HWIO_LPASS_DFS_PERF3_CDIV_PERF3_LPAAUDIO_DIG_PLL_EARLY_SVS_CDIV_SHFT                                                 0x0

#define HWIO_LPASS_DFS_PERF4_CDIV_ADDR                                                                                (LPASS_CC_REG_BASE      + 0x00034058)
#define HWIO_LPASS_DFS_PERF4_CDIV_OFFS                                                                                (LPASS_CC_REG_BASE_OFFS + 0x00034058)
#define HWIO_LPASS_DFS_PERF4_CDIV_RMSK                                                                                      0x77
#define HWIO_LPASS_DFS_PERF4_CDIV_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF4_CDIV_ADDR, HWIO_LPASS_DFS_PERF4_CDIV_RMSK)
#define HWIO_LPASS_DFS_PERF4_CDIV_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF4_CDIV_ADDR, m)
#define HWIO_LPASS_DFS_PERF4_CDIV_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF4_CDIV_ADDR,v)
#define HWIO_LPASS_DFS_PERF4_CDIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF4_CDIV_ADDR,m,v,HWIO_LPASS_DFS_PERF4_CDIV_IN)
#define HWIO_LPASS_DFS_PERF4_CDIV_PERF4_LPAAUDIO_PLL_MAIN_SVS_CDIV_BMSK                                                     0x70
#define HWIO_LPASS_DFS_PERF4_CDIV_PERF4_LPAAUDIO_PLL_MAIN_SVS_CDIV_SHFT                                                      0x4
#define HWIO_LPASS_DFS_PERF4_CDIV_PERF4_LPAAUDIO_DIG_PLL_EARLY_SVS_CDIV_BMSK                                                 0x7
#define HWIO_LPASS_DFS_PERF4_CDIV_PERF4_LPAAUDIO_DIG_PLL_EARLY_SVS_CDIV_SHFT                                                 0x0

#define HWIO_LPASS_DFS_PERF5_CDIV_ADDR                                                                                (LPASS_CC_REG_BASE      + 0x0003405c)
#define HWIO_LPASS_DFS_PERF5_CDIV_OFFS                                                                                (LPASS_CC_REG_BASE_OFFS + 0x0003405c)
#define HWIO_LPASS_DFS_PERF5_CDIV_RMSK                                                                                      0x77
#define HWIO_LPASS_DFS_PERF5_CDIV_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF5_CDIV_ADDR, HWIO_LPASS_DFS_PERF5_CDIV_RMSK)
#define HWIO_LPASS_DFS_PERF5_CDIV_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF5_CDIV_ADDR, m)
#define HWIO_LPASS_DFS_PERF5_CDIV_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF5_CDIV_ADDR,v)
#define HWIO_LPASS_DFS_PERF5_CDIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF5_CDIV_ADDR,m,v,HWIO_LPASS_DFS_PERF5_CDIV_IN)
#define HWIO_LPASS_DFS_PERF5_CDIV_PERF5_LPAAUDIO_PLL_MAIN_SVS_CDIV_BMSK                                                     0x70
#define HWIO_LPASS_DFS_PERF5_CDIV_PERF5_LPAAUDIO_PLL_MAIN_SVS_CDIV_SHFT                                                      0x4
#define HWIO_LPASS_DFS_PERF5_CDIV_PERF5_LPAAUDIO_DIG_PLL_EARLY_SVS_CDIV_BMSK                                                 0x7
#define HWIO_LPASS_DFS_PERF5_CDIV_PERF5_LPAAUDIO_DIG_PLL_EARLY_SVS_CDIV_SHFT                                                 0x0

#define HWIO_LPASS_DFS_PERF6_CDIV_ADDR                                                                                (LPASS_CC_REG_BASE      + 0x00034060)
#define HWIO_LPASS_DFS_PERF6_CDIV_OFFS                                                                                (LPASS_CC_REG_BASE_OFFS + 0x00034060)
#define HWIO_LPASS_DFS_PERF6_CDIV_RMSK                                                                                      0x77
#define HWIO_LPASS_DFS_PERF6_CDIV_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF6_CDIV_ADDR, HWIO_LPASS_DFS_PERF6_CDIV_RMSK)
#define HWIO_LPASS_DFS_PERF6_CDIV_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF6_CDIV_ADDR, m)
#define HWIO_LPASS_DFS_PERF6_CDIV_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF6_CDIV_ADDR,v)
#define HWIO_LPASS_DFS_PERF6_CDIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF6_CDIV_ADDR,m,v,HWIO_LPASS_DFS_PERF6_CDIV_IN)
#define HWIO_LPASS_DFS_PERF6_CDIV_PERF6_LPAAUDIO_PLL_MAIN_SVS_CDIV_BMSK                                                     0x70
#define HWIO_LPASS_DFS_PERF6_CDIV_PERF6_LPAAUDIO_PLL_MAIN_SVS_CDIV_SHFT                                                      0x4
#define HWIO_LPASS_DFS_PERF6_CDIV_PERF6_LPAAUDIO_DIG_PLL_EARLY_SVS_CDIV_BMSK                                                 0x7
#define HWIO_LPASS_DFS_PERF6_CDIV_PERF6_LPAAUDIO_DIG_PLL_EARLY_SVS_CDIV_SHFT                                                 0x0

#define HWIO_LPASS_DFS_PERF7_CDIV_ADDR                                                                                (LPASS_CC_REG_BASE      + 0x00034064)
#define HWIO_LPASS_DFS_PERF7_CDIV_OFFS                                                                                (LPASS_CC_REG_BASE_OFFS + 0x00034064)
#define HWIO_LPASS_DFS_PERF7_CDIV_RMSK                                                                                      0x77
#define HWIO_LPASS_DFS_PERF7_CDIV_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF7_CDIV_ADDR, HWIO_LPASS_DFS_PERF7_CDIV_RMSK)
#define HWIO_LPASS_DFS_PERF7_CDIV_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF7_CDIV_ADDR, m)
#define HWIO_LPASS_DFS_PERF7_CDIV_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF7_CDIV_ADDR,v)
#define HWIO_LPASS_DFS_PERF7_CDIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF7_CDIV_ADDR,m,v,HWIO_LPASS_DFS_PERF7_CDIV_IN)
#define HWIO_LPASS_DFS_PERF7_CDIV_PERF7_LPAAUDIO_PLL_MAIN_SVS_CDIV_BMSK                                                     0x70
#define HWIO_LPASS_DFS_PERF7_CDIV_PERF7_LPAAUDIO_PLL_MAIN_SVS_CDIV_SHFT                                                      0x4
#define HWIO_LPASS_DFS_PERF7_CDIV_PERF7_LPAAUDIO_DIG_PLL_EARLY_SVS_CDIV_BMSK                                                 0x7
#define HWIO_LPASS_DFS_PERF7_CDIV_PERF7_LPAAUDIO_DIG_PLL_EARLY_SVS_CDIV_SHFT                                                 0x0

#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_ADDR                                                                (LPASS_CC_REG_BASE      + 0x00035000)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_OFFS                                                                (LPASS_CC_REG_BASE_OFFS + 0x00035000)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_RMSK                                                                0x800000f3
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_ADDR, HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_RMSK)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_ADDR,m,v,HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_IN)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_ROOT_OFF_BMSK                                                       0x80000000
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_ROOT_OFF_SHFT                                                             0x1f
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_DIRTY_D_BMSK                                                              0x80
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_DIRTY_D_SHFT                                                               0x7
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_DIRTY_N_BMSK                                                              0x40
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_DIRTY_N_SHFT                                                               0x6
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_DIRTY_M_BMSK                                                              0x20
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_DIRTY_M_SHFT                                                               0x5
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                       0x10
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                        0x4
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_ROOT_EN_BMSK                                                               0x2
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_ROOT_EN_SHFT                                                               0x1
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_UPDATE_BMSK                                                                0x1
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_UPDATE_SHFT                                                                0x0

#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CFG_RCGR_ADDR                                                                (LPASS_CC_REG_BASE      + 0x00035004)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CFG_RCGR_OFFS                                                                (LPASS_CC_REG_BASE_OFFS + 0x00035004)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CFG_RCGR_RMSK                                                                    0x771f
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CFG_RCGR_ADDR, HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CFG_RCGR_RMSK)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CFG_RCGR_ADDR,m,v,HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CFG_RCGR_IN)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CFG_RCGR_ALT_SRC_SEL_BMSK                                                        0x4000
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CFG_RCGR_ALT_SRC_SEL_SHFT                                                           0xe
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CFG_RCGR_MODE_BMSK                                                               0x3000
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CFG_RCGR_MODE_SHFT                                                                  0xc
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CFG_RCGR_SRC_SEL_BMSK                                                             0x700
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CFG_RCGR_SRC_SEL_SHFT                                                               0x8
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CFG_RCGR_SRC_DIV_BMSK                                                              0x1f
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CFG_RCGR_SRC_DIV_SHFT                                                               0x0

#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_M_ADDR                                                                       (LPASS_CC_REG_BASE      + 0x00035008)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_M_OFFS                                                                       (LPASS_CC_REG_BASE_OFFS + 0x00035008)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_M_RMSK                                                                             0xff
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_M_IN          \
        in_dword_masked(HWIO_LPASS_QOS_FIXED_LAT_COUNTER_M_ADDR, HWIO_LPASS_QOS_FIXED_LAT_COUNTER_M_RMSK)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_QOS_FIXED_LAT_COUNTER_M_ADDR, m)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_M_OUT(v)      \
        out_dword(HWIO_LPASS_QOS_FIXED_LAT_COUNTER_M_ADDR,v)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QOS_FIXED_LAT_COUNTER_M_ADDR,m,v,HWIO_LPASS_QOS_FIXED_LAT_COUNTER_M_IN)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_M_M_BMSK                                                                           0xff
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_M_M_SHFT                                                                            0x0

#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_N_ADDR                                                                       (LPASS_CC_REG_BASE      + 0x0003500c)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_N_OFFS                                                                       (LPASS_CC_REG_BASE_OFFS + 0x0003500c)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_N_RMSK                                                                             0xff
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_N_IN          \
        in_dword_masked(HWIO_LPASS_QOS_FIXED_LAT_COUNTER_N_ADDR, HWIO_LPASS_QOS_FIXED_LAT_COUNTER_N_RMSK)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_QOS_FIXED_LAT_COUNTER_N_ADDR, m)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_N_OUT(v)      \
        out_dword(HWIO_LPASS_QOS_FIXED_LAT_COUNTER_N_ADDR,v)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QOS_FIXED_LAT_COUNTER_N_ADDR,m,v,HWIO_LPASS_QOS_FIXED_LAT_COUNTER_N_IN)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_N_NOT_N_MINUS_M_BMSK                                                               0xff
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_N_NOT_N_MINUS_M_SHFT                                                                0x0

#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_D_ADDR                                                                       (LPASS_CC_REG_BASE      + 0x00035010)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_D_OFFS                                                                       (LPASS_CC_REG_BASE_OFFS + 0x00035010)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_D_RMSK                                                                             0xff
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_D_IN          \
        in_dword_masked(HWIO_LPASS_QOS_FIXED_LAT_COUNTER_D_ADDR, HWIO_LPASS_QOS_FIXED_LAT_COUNTER_D_RMSK)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_QOS_FIXED_LAT_COUNTER_D_ADDR, m)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_D_OUT(v)      \
        out_dword(HWIO_LPASS_QOS_FIXED_LAT_COUNTER_D_ADDR,v)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QOS_FIXED_LAT_COUNTER_D_ADDR,m,v,HWIO_LPASS_QOS_FIXED_LAT_COUNTER_D_IN)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_D_NOT_2D_BMSK                                                                      0xff
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_D_NOT_2D_SHFT                                                                       0x0

#define HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBS_AON_CBCR_ADDR                                                               (LPASS_CC_REG_BASE      + 0x00035014)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBS_AON_CBCR_OFFS                                                               (LPASS_CC_REG_BASE_OFFS + 0x00035014)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBS_AON_CBCR_RMSK                                                               0x80000003
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBS_AON_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBS_AON_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBS_AON_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBS_AON_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBS_AON_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBS_AON_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBS_AON_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBS_AON_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBS_AON_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBS_AON_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBS_AON_CBCR_CLK_OFF_BMSK                                                       0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBS_AON_CBCR_CLK_OFF_SHFT                                                             0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBS_AON_CBCR_HW_CTL_BMSK                                                               0x2
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBS_AON_CBCR_HW_CTL_SHFT                                                               0x1
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBS_AON_CBCR_CLK_ENABLE_BMSK                                                           0x1
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBS_AON_CBCR_CLK_ENABLE_SHFT                                                           0x0

#define HWIO_LPASS_AUDIO_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_ADDR                                                         (LPASS_CC_REG_BASE      + 0x00035018)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_OFFS                                                         (LPASS_CC_REG_BASE_OFFS + 0x00035018)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_RMSK                                                         0x80000003
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_CLK_OFF_BMSK                                                 0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_CLK_OFF_SHFT                                                       0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_HW_CTL_BMSK                                                         0x2
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_HW_CTL_SHFT                                                         0x1
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_CLK_ENABLE_BMSK                                                     0x1
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_CLK_ENABLE_SHFT                                                     0x0

#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_ADDR                                             (LPASS_CC_REG_BASE      + 0x0003501c)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_OFFS                                             (LPASS_CC_REG_BASE_OFFS + 0x0003501c)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_RMSK                                             0x80000003
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_CLK_OFF_BMSK                                     0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_CLK_OFF_SHFT                                           0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_HW_CTL_BMSK                                             0x2
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_HW_CTL_SHFT                                             0x1
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_CLK_ENABLE_BMSK                                         0x1
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_CLK_ENABLE_SHFT                                         0x0

#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_ADDR                                               (LPASS_CC_REG_BASE      + 0x00035020)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_OFFS                                               (LPASS_CC_REG_BASE_OFFS + 0x00035020)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_RMSK                                               0x80000003
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_CLK_OFF_BMSK                                       0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_CLK_OFF_SHFT                                             0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_HW_CTL_BMSK                                               0x2
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_HW_CTL_SHFT                                               0x1
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_CLK_ENABLE_BMSK                                           0x1
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_CLK_ENABLE_SHFT                                           0x0

#define HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBM_AON_CBCR_ADDR                                                               (LPASS_CC_REG_BASE      + 0x00035024)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBM_AON_CBCR_OFFS                                                               (LPASS_CC_REG_BASE_OFFS + 0x00035024)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBM_AON_CBCR_RMSK                                                               0x80000003
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBM_AON_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBM_AON_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBM_AON_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBM_AON_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBM_AON_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBM_AON_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBM_AON_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBM_AON_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBM_AON_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBM_AON_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBM_AON_CBCR_CLK_OFF_BMSK                                                       0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBM_AON_CBCR_CLK_OFF_SHFT                                                             0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBM_AON_CBCR_HW_CTL_BMSK                                                               0x2
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBM_AON_CBCR_HW_CTL_SHFT                                                               0x1
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBM_AON_CBCR_CLK_ENABLE_BMSK                                                           0x1
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBM_AON_CBCR_CLK_ENABLE_SHFT                                                           0x0

#define HWIO_LPASS_AUDIO_CORE_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_ADDR                                                (LPASS_CC_REG_BASE      + 0x00036000)
#define HWIO_LPASS_AUDIO_CORE_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_OFFS                                                (LPASS_CC_REG_BASE_OFFS + 0x00036000)
#define HWIO_LPASS_AUDIO_CORE_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_RMSK                                                0x80000003
#define HWIO_LPASS_AUDIO_CORE_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_CLK_OFF_BMSK                                        0x80000000
#define HWIO_LPASS_AUDIO_CORE_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_CLK_OFF_SHFT                                              0x1f
#define HWIO_LPASS_AUDIO_CORE_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_HW_CTL_BMSK                                                0x2
#define HWIO_LPASS_AUDIO_CORE_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_HW_CTL_SHFT                                                0x1
#define HWIO_LPASS_AUDIO_CORE_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_CLK_ENABLE_BMSK                                            0x1
#define HWIO_LPASS_AUDIO_CORE_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_CLK_ENABLE_SHFT                                            0x0

#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_ADDR                                                 (LPASS_CC_REG_BASE      + 0x00037000)
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_OFFS                                                 (LPASS_CC_REG_BASE_OFFS + 0x00037000)
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_RMSK                                                 0x80000003
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_ADDR, HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_RMSK)
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_IN)
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_SEQUENCE_ABORT_BMSK                                  0x80000000
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_SEQUENCE_ABORT_SHFT                                        0x1f
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_SEQUENCE_ABORT_IRQ_EN_APPS_BMSK                             0x2
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_SEQUENCE_ABORT_IRQ_EN_APPS_SHFT                             0x1
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_SEQUENCE_ABORT_IRQ_EN_Q6_BMSK                               0x1
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_SEQUENCE_ABORT_IRQ_EN_Q6_SHFT                               0x0

#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_Q6_ADDR                                                      (LPASS_CC_REG_BASE      + 0x00037004)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_Q6_OFFS                                                      (LPASS_CC_REG_BASE_OFFS + 0x00037004)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_Q6_RMSK                                                             0x3
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_Q6_IN          \
        in_dword_masked(HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_Q6_ADDR, HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_Q6_RMSK)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_Q6_INM(m)      \
        in_dword_masked(HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_Q6_ADDR, m)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_Q6_OUT(v)      \
        out_dword(HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_Q6_ADDR,v)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_Q6_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_Q6_ADDR,m,v,HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_Q6_IN)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_Q6_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_BMSK                      0x2
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_Q6_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_SHFT                      0x1
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_Q6_LPASS_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_BMSK                   0x1
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_Q6_LPASS_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_SHFT                   0x0

#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_Q6_ADDR                                                      (LPASS_CC_REG_BASE      + 0x00037008)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_Q6_OFFS                                                      (LPASS_CC_REG_BASE_OFFS + 0x00037008)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_Q6_RMSK                                                             0x3
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_Q6_IN          \
        in_dword_masked(HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_Q6_ADDR, HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_Q6_RMSK)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_Q6_INM(m)      \
        in_dword_masked(HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_Q6_ADDR, m)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_Q6_OUT(v)      \
        out_dword(HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_Q6_ADDR,v)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_Q6_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_Q6_ADDR,m,v,HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_Q6_IN)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_Q6_Q6_SMMU_SEQUENCE_ABORT_IRQ_EN_BMSK                               0x2
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_Q6_Q6_SMMU_SEQUENCE_ABORT_IRQ_EN_SHFT                               0x1
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_Q6_LPASS_CORE_SEQUENCE_ABORT_IRQ_EN_BMSK                            0x1
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_Q6_LPASS_CORE_SEQUENCE_ABORT_IRQ_EN_SHFT                            0x0

#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_ADDR                                      (LPASS_CC_REG_BASE      + 0x00038000)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_OFFS                                      (LPASS_CC_REG_BASE_OFFS + 0x00038000)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_RMSK                                      0x80000003
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_ADDR, HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_SEQUENCE_ABORT_BMSK                       0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_SEQUENCE_ABORT_SHFT                             0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_SEQUENCE_ABORT_IRQ_EN_APPS_BMSK                  0x2
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_SEQUENCE_ABORT_IRQ_EN_APPS_SHFT                  0x1
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_SEQUENCE_ABORT_IRQ_EN_Q6_BMSK                    0x1
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_SEQUENCE_ABORT_IRQ_EN_Q6_SHFT                    0x0

#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_APPS_ADDR                                                    (LPASS_CC_REG_BASE      + 0x00038004)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_APPS_OFFS                                                    (LPASS_CC_REG_BASE_OFFS + 0x00038004)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_APPS_RMSK                                                           0x3
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_APPS_IN          \
        in_dword_masked(HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_APPS_ADDR, HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_APPS_RMSK)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_APPS_INM(m)      \
        in_dword_masked(HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_APPS_ADDR, m)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_APPS_OUT(v)      \
        out_dword(HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_APPS_ADDR,v)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_APPS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_APPS_ADDR,m,v,HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_APPS_IN)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_APPS_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_BMSK                    0x2
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_APPS_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_SHFT                    0x1
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_APPS_LPASS_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_BMSK                 0x1
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_APPS_LPASS_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_SHFT                 0x0

#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_APPS_ADDR                                                    (LPASS_CC_REG_BASE      + 0x00038008)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_APPS_OFFS                                                    (LPASS_CC_REG_BASE_OFFS + 0x00038008)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_APPS_RMSK                                                           0x3
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_APPS_IN          \
        in_dword_masked(HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_APPS_ADDR, HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_APPS_RMSK)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_APPS_INM(m)      \
        in_dword_masked(HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_APPS_ADDR, m)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_APPS_OUT(v)      \
        out_dword(HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_APPS_ADDR,v)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_APPS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_APPS_ADDR,m,v,HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_APPS_IN)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_APPS_Q6_SMMU_SEQUENCE_ABORT_IRQ_EN_BMSK                             0x2
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_APPS_Q6_SMMU_SEQUENCE_ABORT_IRQ_EN_SHFT                             0x1
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_APPS_LPASS_CORE_SEQUENCE_ABORT_IRQ_EN_BMSK                          0x1
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_APPS_LPASS_CORE_SEQUENCE_ABORT_IRQ_EN_SHFT                          0x0

#define HWIO_LPASS_AUDIO_WRAPPER_Q6_VOTE_LPASS_Q6_SMMU_GDS_ADDR                                                       (LPASS_CC_REG_BASE      + 0x00039000)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_VOTE_LPASS_Q6_SMMU_GDS_OFFS                                                       (LPASS_CC_REG_BASE_OFFS + 0x00039000)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_VOTE_LPASS_Q6_SMMU_GDS_RMSK                                                       0x80000001
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_VOTE_LPASS_Q6_SMMU_GDS_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_Q6_VOTE_LPASS_Q6_SMMU_GDS_ADDR, HWIO_LPASS_AUDIO_WRAPPER_Q6_VOTE_LPASS_Q6_SMMU_GDS_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_VOTE_LPASS_Q6_SMMU_GDS_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_Q6_VOTE_LPASS_Q6_SMMU_GDS_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_VOTE_LPASS_Q6_SMMU_GDS_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_Q6_VOTE_LPASS_Q6_SMMU_GDS_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_VOTE_LPASS_Q6_SMMU_GDS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_Q6_VOTE_LPASS_Q6_SMMU_GDS_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_Q6_VOTE_LPASS_Q6_SMMU_GDS_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_VOTE_LPASS_Q6_SMMU_GDS_Q6_SMMU_PWR_ON_BMSK                                        0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_VOTE_LPASS_Q6_SMMU_GDS_Q6_SMMU_PWR_ON_SHFT                                              0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_VOTE_LPASS_Q6_SMMU_GDS_Q6_SMMU_SW_COLLAPSE_BMSK                                          0x1
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_VOTE_LPASS_Q6_SMMU_GDS_Q6_SMMU_SW_COLLAPSE_SHFT                                          0x0

#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_SPM_CLK_CTL_ADDR                                                             (LPASS_CC_REG_BASE      + 0x00039004)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_SPM_CLK_CTL_OFFS                                                             (LPASS_CC_REG_BASE_OFFS + 0x00039004)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_SPM_CLK_CTL_RMSK                                                                    0x1
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_SPM_CLK_CTL_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_SPM_CLK_CTL_ADDR, HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_SPM_CLK_CTL_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_SPM_CLK_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_SPM_CLK_CTL_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_SPM_CLK_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_SPM_CLK_CTL_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_SPM_CLK_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_SPM_CLK_CTL_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_SPM_CLK_CTL_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_SPM_CLK_CTL_Q6_SMMU_SPM_COLLAPSE_OR_CLK_GATE_SEL_BMSK                               0x1
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_SPM_CLK_CTL_Q6_SMMU_SPM_COLLAPSE_OR_CLK_GATE_SEL_SHFT                               0x0

#define HWIO_LPASS_AUDIO_WRAPPER_BUS_TIMEOUT_AON_CBCR_ADDR                                                            (LPASS_CC_REG_BASE      + 0x0003a000)
#define HWIO_LPASS_AUDIO_WRAPPER_BUS_TIMEOUT_AON_CBCR_OFFS                                                            (LPASS_CC_REG_BASE_OFFS + 0x0003a000)
#define HWIO_LPASS_AUDIO_WRAPPER_BUS_TIMEOUT_AON_CBCR_RMSK                                                            0x80000003
#define HWIO_LPASS_AUDIO_WRAPPER_BUS_TIMEOUT_AON_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_BUS_TIMEOUT_AON_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_BUS_TIMEOUT_AON_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_BUS_TIMEOUT_AON_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_BUS_TIMEOUT_AON_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_BUS_TIMEOUT_AON_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_BUS_TIMEOUT_AON_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_BUS_TIMEOUT_AON_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_BUS_TIMEOUT_AON_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_BUS_TIMEOUT_AON_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_BUS_TIMEOUT_AON_CBCR_CLK_OFF_BMSK                                                    0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_BUS_TIMEOUT_AON_CBCR_CLK_OFF_SHFT                                                          0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_BUS_TIMEOUT_AON_CBCR_HW_CTL_BMSK                                                            0x2
#define HWIO_LPASS_AUDIO_WRAPPER_BUS_TIMEOUT_AON_CBCR_HW_CTL_SHFT                                                            0x1
#define HWIO_LPASS_AUDIO_WRAPPER_BUS_TIMEOUT_AON_CBCR_CLK_ENABLE_BMSK                                                        0x1
#define HWIO_LPASS_AUDIO_WRAPPER_BUS_TIMEOUT_AON_CBCR_CLK_ENABLE_SHFT                                                        0x0

#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_CBCR_ADDR                                                              (LPASS_CC_REG_BASE      + 0x0003b000)
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_CBCR_OFFS                                                              (LPASS_CC_REG_BASE_OFFS + 0x0003b000)
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_CBCR_RMSK                                                              0x80000003
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_CBCR_CLK_OFF_BMSK                                                      0x80000000
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_CBCR_CLK_OFF_SHFT                                                            0x1f
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_CBCR_HW_CTL_BMSK                                                              0x2
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_CBCR_HW_CTL_SHFT                                                              0x1
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_CBCR_CLK_ENABLE_BMSK                                                          0x1
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_CBCR_CLK_ENABLE_SHFT                                                          0x0

#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_TZ_ADDR                                                      (LPASS_CC_REG_BASE      + 0x0003c004)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_TZ_OFFS                                                      (LPASS_CC_REG_BASE_OFFS + 0x0003c004)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_TZ_RMSK                                                             0x3
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_TZ_IN          \
        in_dword_masked(HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_TZ_ADDR, HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_TZ_RMSK)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_TZ_INM(m)      \
        in_dword_masked(HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_TZ_ADDR, m)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_TZ_OUT(v)      \
        out_dword(HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_TZ_ADDR,v)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_TZ_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_TZ_ADDR,m,v,HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_TZ_IN)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_TZ_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_BMSK                      0x2
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_TZ_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_SHFT                      0x1
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_TZ_LPASS_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_BMSK                   0x1
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_TZ_LPASS_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_SHFT                   0x0

#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_TZ_ADDR                                                      (LPASS_CC_REG_BASE      + 0x0003c008)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_TZ_OFFS                                                      (LPASS_CC_REG_BASE_OFFS + 0x0003c008)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_TZ_RMSK                                                             0x3
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_TZ_IN          \
        in_dword_masked(HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_TZ_ADDR, HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_TZ_RMSK)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_TZ_INM(m)      \
        in_dword_masked(HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_TZ_ADDR, m)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_TZ_OUT(v)      \
        out_dword(HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_TZ_ADDR,v)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_TZ_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_TZ_ADDR,m,v,HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_TZ_IN)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_TZ_Q6_SMMU_SEQUENCE_ABORT_IRQ_EN_BMSK                               0x2
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_TZ_Q6_SMMU_SEQUENCE_ABORT_IRQ_EN_SHFT                               0x1
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_TZ_LPASS_CORE_SEQUENCE_ABORT_IRQ_EN_BMSK                            0x1
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_TZ_LPASS_CORE_SEQUENCE_ABORT_IRQ_EN_SHFT                            0x0

#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_HYP_ADDR                                                     (LPASS_CC_REG_BASE      + 0x0003d004)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_HYP_OFFS                                                     (LPASS_CC_REG_BASE_OFFS + 0x0003d004)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_HYP_RMSK                                                            0x3
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_HYP_IN          \
        in_dword_masked(HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_HYP_ADDR, HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_HYP_RMSK)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_HYP_INM(m)      \
        in_dword_masked(HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_HYP_ADDR, m)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_HYP_OUT(v)      \
        out_dword(HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_HYP_ADDR,v)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_HYP_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_HYP_ADDR,m,v,HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_HYP_IN)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_HYP_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_BMSK                     0x2
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_HYP_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_SHFT                     0x1
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_HYP_LPASS_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_BMSK                  0x1
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_HYP_LPASS_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_SHFT                  0x0

#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_HYP_ADDR                                                     (LPASS_CC_REG_BASE      + 0x0003d008)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_HYP_OFFS                                                     (LPASS_CC_REG_BASE_OFFS + 0x0003d008)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_HYP_RMSK                                                            0x3
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_HYP_IN          \
        in_dword_masked(HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_HYP_ADDR, HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_HYP_RMSK)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_HYP_INM(m)      \
        in_dword_masked(HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_HYP_ADDR, m)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_HYP_OUT(v)      \
        out_dword(HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_HYP_ADDR,v)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_HYP_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_HYP_ADDR,m,v,HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_HYP_IN)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_HYP_Q6_SMMU_SEQUENCE_ABORT_IRQ_EN_BMSK                              0x2
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_HYP_Q6_SMMU_SEQUENCE_ABORT_IRQ_EN_SHFT                              0x1
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_HYP_LPASS_CORE_SEQUENCE_ABORT_IRQ_EN_BMSK                           0x1
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_HYP_LPASS_CORE_SEQUENCE_ABORT_IRQ_EN_SHFT                           0x0

#define HWIO_LPASS_SCC_PLL_MODE_ADDR                                                                                  (LPASS_CC_REG_BASE      + 0x0003e000)
#define HWIO_LPASS_SCC_PLL_MODE_OFFS                                                                                  (LPASS_CC_REG_BASE_OFFS + 0x0003e000)
#define HWIO_LPASS_SCC_PLL_MODE_RMSK                                                                                  0xffffffff
#define HWIO_LPASS_SCC_PLL_MODE_IN          \
        in_dword_masked(HWIO_LPASS_SCC_PLL_MODE_ADDR, HWIO_LPASS_SCC_PLL_MODE_RMSK)
#define HWIO_LPASS_SCC_PLL_MODE_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_PLL_MODE_ADDR, m)
#define HWIO_LPASS_SCC_PLL_MODE_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_PLL_MODE_ADDR,v)
#define HWIO_LPASS_SCC_PLL_MODE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_PLL_MODE_ADDR,m,v,HWIO_LPASS_SCC_PLL_MODE_IN)
#define HWIO_LPASS_SCC_PLL_MODE_PLL_LOCK_DET_BMSK                                                                     0x80000000
#define HWIO_LPASS_SCC_PLL_MODE_PLL_LOCK_DET_SHFT                                                                           0x1f
#define HWIO_LPASS_SCC_PLL_MODE_RESERVE_BIT30_BMSK                                                                    0x40000000
#define HWIO_LPASS_SCC_PLL_MODE_RESERVE_BIT30_SHFT                                                                          0x1e
#define HWIO_LPASS_SCC_PLL_MODE_PLL_ACK_LATCH_BMSK                                                                    0x20000000
#define HWIO_LPASS_SCC_PLL_MODE_PLL_ACK_LATCH_SHFT                                                                          0x1d
#define HWIO_LPASS_SCC_PLL_MODE_RESERVE_BITS28_24_BMSK                                                                0x1f000000
#define HWIO_LPASS_SCC_PLL_MODE_RESERVE_BITS28_24_SHFT                                                                      0x18
#define HWIO_LPASS_SCC_PLL_MODE_PLL_HW_UPDATE_LOGIC_BYPASS_BMSK                                                         0x800000
#define HWIO_LPASS_SCC_PLL_MODE_PLL_HW_UPDATE_LOGIC_BYPASS_SHFT                                                             0x17
#define HWIO_LPASS_SCC_PLL_MODE_PLL_UPDATE_BMSK                                                                         0x400000
#define HWIO_LPASS_SCC_PLL_MODE_PLL_UPDATE_SHFT                                                                             0x16
#define HWIO_LPASS_SCC_PLL_MODE_RESERVE_BITS21_3_BMSK                                                                   0x3ffff8
#define HWIO_LPASS_SCC_PLL_MODE_RESERVE_BITS21_3_SHFT                                                                        0x3
#define HWIO_LPASS_SCC_PLL_MODE_PLL_RESET_N_BMSK                                                                             0x4
#define HWIO_LPASS_SCC_PLL_MODE_PLL_RESET_N_SHFT                                                                             0x2
#define HWIO_LPASS_SCC_PLL_MODE_RESERVE_BIT1_BMSK                                                                            0x2
#define HWIO_LPASS_SCC_PLL_MODE_RESERVE_BIT1_SHFT                                                                            0x1
#define HWIO_LPASS_SCC_PLL_MODE_PLL_OUTCTRL_BMSK                                                                             0x1
#define HWIO_LPASS_SCC_PLL_MODE_PLL_OUTCTRL_SHFT                                                                             0x0

#define HWIO_LPASS_SCC_PLL_L_VAL_ADDR                                                                                 (LPASS_CC_REG_BASE      + 0x0003e004)
#define HWIO_LPASS_SCC_PLL_L_VAL_OFFS                                                                                 (LPASS_CC_REG_BASE_OFFS + 0x0003e004)
#define HWIO_LPASS_SCC_PLL_L_VAL_RMSK                                                                                     0xffff
#define HWIO_LPASS_SCC_PLL_L_VAL_IN          \
        in_dword_masked(HWIO_LPASS_SCC_PLL_L_VAL_ADDR, HWIO_LPASS_SCC_PLL_L_VAL_RMSK)
#define HWIO_LPASS_SCC_PLL_L_VAL_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_PLL_L_VAL_ADDR, m)
#define HWIO_LPASS_SCC_PLL_L_VAL_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_PLL_L_VAL_ADDR,v)
#define HWIO_LPASS_SCC_PLL_L_VAL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_PLL_L_VAL_ADDR,m,v,HWIO_LPASS_SCC_PLL_L_VAL_IN)
#define HWIO_LPASS_SCC_PLL_L_VAL_PLL_L_BMSK                                                                               0xffff
#define HWIO_LPASS_SCC_PLL_L_VAL_PLL_L_SHFT                                                                                  0x0

#define HWIO_LPASS_SCC_PLL_CAL_L_VAL_ADDR                                                                             (LPASS_CC_REG_BASE      + 0x0003e008)
#define HWIO_LPASS_SCC_PLL_CAL_L_VAL_OFFS                                                                             (LPASS_CC_REG_BASE_OFFS + 0x0003e008)
#define HWIO_LPASS_SCC_PLL_CAL_L_VAL_RMSK                                                                                 0xffff
#define HWIO_LPASS_SCC_PLL_CAL_L_VAL_IN          \
        in_dword_masked(HWIO_LPASS_SCC_PLL_CAL_L_VAL_ADDR, HWIO_LPASS_SCC_PLL_CAL_L_VAL_RMSK)
#define HWIO_LPASS_SCC_PLL_CAL_L_VAL_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_PLL_CAL_L_VAL_ADDR, m)
#define HWIO_LPASS_SCC_PLL_CAL_L_VAL_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_PLL_CAL_L_VAL_ADDR,v)
#define HWIO_LPASS_SCC_PLL_CAL_L_VAL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_PLL_CAL_L_VAL_ADDR,m,v,HWIO_LPASS_SCC_PLL_CAL_L_VAL_IN)
#define HWIO_LPASS_SCC_PLL_CAL_L_VAL_PLL_CAL_L_BMSK                                                                       0xffff
#define HWIO_LPASS_SCC_PLL_CAL_L_VAL_PLL_CAL_L_SHFT                                                                          0x0

#define HWIO_LPASS_SCC_PLL_USER_CTL_ADDR                                                                              (LPASS_CC_REG_BASE      + 0x0003e00c)
#define HWIO_LPASS_SCC_PLL_USER_CTL_OFFS                                                                              (LPASS_CC_REG_BASE_OFFS + 0x0003e00c)
#define HWIO_LPASS_SCC_PLL_USER_CTL_RMSK                                                                              0xffffffff
#define HWIO_LPASS_SCC_PLL_USER_CTL_IN          \
        in_dword_masked(HWIO_LPASS_SCC_PLL_USER_CTL_ADDR, HWIO_LPASS_SCC_PLL_USER_CTL_RMSK)
#define HWIO_LPASS_SCC_PLL_USER_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_PLL_USER_CTL_ADDR, m)
#define HWIO_LPASS_SCC_PLL_USER_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_PLL_USER_CTL_ADDR,v)
#define HWIO_LPASS_SCC_PLL_USER_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_PLL_USER_CTL_ADDR,m,v,HWIO_LPASS_SCC_PLL_USER_CTL_IN)
#define HWIO_LPASS_SCC_PLL_USER_CTL_RESERVE_BITS31_15_BMSK                                                            0xffff8000
#define HWIO_LPASS_SCC_PLL_USER_CTL_RESERVE_BITS31_15_SHFT                                                                   0xf
#define HWIO_LPASS_SCC_PLL_USER_CTL_PRE_DIV_RATIO_BMSK                                                                    0x7000
#define HWIO_LPASS_SCC_PLL_USER_CTL_PRE_DIV_RATIO_SHFT                                                                       0xc
#define HWIO_LPASS_SCC_PLL_USER_CTL_POST_DIV_RATIO_BMSK                                                                    0xf00
#define HWIO_LPASS_SCC_PLL_USER_CTL_POST_DIV_RATIO_SHFT                                                                      0x8
#define HWIO_LPASS_SCC_PLL_USER_CTL_OUT_CLK_POLARITY_BMSK                                                                   0x80
#define HWIO_LPASS_SCC_PLL_USER_CTL_OUT_CLK_POLARITY_SHFT                                                                    0x7
#define HWIO_LPASS_SCC_PLL_USER_CTL_RESERVE_BITS6_5_BMSK                                                                    0x60
#define HWIO_LPASS_SCC_PLL_USER_CTL_RESERVE_BITS6_5_SHFT                                                                     0x5
#define HWIO_LPASS_SCC_PLL_USER_CTL_PLLOUT_LV_TEST_BMSK                                                                     0x10
#define HWIO_LPASS_SCC_PLL_USER_CTL_PLLOUT_LV_TEST_SHFT                                                                      0x4
#define HWIO_LPASS_SCC_PLL_USER_CTL_RESERVE_BITS3_1_BMSK                                                                     0xe
#define HWIO_LPASS_SCC_PLL_USER_CTL_RESERVE_BITS3_1_SHFT                                                                     0x1
#define HWIO_LPASS_SCC_PLL_USER_CTL_PLLOUT_LV_MAIN_BMSK                                                                      0x1
#define HWIO_LPASS_SCC_PLL_USER_CTL_PLLOUT_LV_MAIN_SHFT                                                                      0x0

#define HWIO_LPASS_SCC_PLL_USER_CTL_U_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x0003e010)
#define HWIO_LPASS_SCC_PLL_USER_CTL_U_OFFS                                                                            (LPASS_CC_REG_BASE_OFFS + 0x0003e010)
#define HWIO_LPASS_SCC_PLL_USER_CTL_U_RMSK                                                                            0xffffffff
#define HWIO_LPASS_SCC_PLL_USER_CTL_U_IN          \
        in_dword_masked(HWIO_LPASS_SCC_PLL_USER_CTL_U_ADDR, HWIO_LPASS_SCC_PLL_USER_CTL_U_RMSK)
#define HWIO_LPASS_SCC_PLL_USER_CTL_U_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_PLL_USER_CTL_U_ADDR, m)
#define HWIO_LPASS_SCC_PLL_USER_CTL_U_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_PLL_USER_CTL_U_ADDR,v)
#define HWIO_LPASS_SCC_PLL_USER_CTL_U_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_PLL_USER_CTL_U_ADDR,m,v,HWIO_LPASS_SCC_PLL_USER_CTL_U_IN)
#define HWIO_LPASS_SCC_PLL_USER_CTL_U_RESERVE_BITS31_13_BMSK                                                          0xffffe000
#define HWIO_LPASS_SCC_PLL_USER_CTL_U_RESERVE_BITS31_13_SHFT                                                                 0xd
#define HWIO_LPASS_SCC_PLL_USER_CTL_U_BIAS_ON_IN_STANDBY_BMSK                                                             0x1000
#define HWIO_LPASS_SCC_PLL_USER_CTL_U_BIAS_ON_IN_STANDBY_SHFT                                                                0xc
#define HWIO_LPASS_SCC_PLL_USER_CTL_U_REF_CLK_AT_OUT_BMSK                                                                  0x800
#define HWIO_LPASS_SCC_PLL_USER_CTL_U_REF_CLK_AT_OUT_SHFT                                                                    0xb
#define HWIO_LPASS_SCC_PLL_USER_CTL_U_SCALE_STATE_ON_RESTART_BMSK                                                          0x600
#define HWIO_LPASS_SCC_PLL_USER_CTL_U_SCALE_STATE_ON_RESTART_SHFT                                                            0x9
#define HWIO_LPASS_SCC_PLL_USER_CTL_U_LATCH_INTERFACE_BYPASS_BMSK                                                          0x100
#define HWIO_LPASS_SCC_PLL_USER_CTL_U_LATCH_INTERFACE_BYPASS_SHFT                                                            0x8
#define HWIO_LPASS_SCC_PLL_USER_CTL_U_STATUS_REGISTER_BMSK                                                                  0xe0
#define HWIO_LPASS_SCC_PLL_USER_CTL_U_STATUS_REGISTER_SHFT                                                                   0x5
#define HWIO_LPASS_SCC_PLL_USER_CTL_U_WRITE_STATE_BMSK                                                                      0x10
#define HWIO_LPASS_SCC_PLL_USER_CTL_U_WRITE_STATE_SHFT                                                                       0x4
#define HWIO_LPASS_SCC_PLL_USER_CTL_U_CALIB_CTRL_BMSK                                                                        0xe
#define HWIO_LPASS_SCC_PLL_USER_CTL_U_CALIB_CTRL_SHFT                                                                        0x1
#define HWIO_LPASS_SCC_PLL_USER_CTL_U_USE_ONLY_FINE_DET_BMSK                                                                 0x1
#define HWIO_LPASS_SCC_PLL_USER_CTL_U_USE_ONLY_FINE_DET_SHFT                                                                 0x0

#define HWIO_LPASS_SCC_PLL_CONFIG_CTL_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x0003e014)
#define HWIO_LPASS_SCC_PLL_CONFIG_CTL_OFFS                                                                            (LPASS_CC_REG_BASE_OFFS + 0x0003e014)
#define HWIO_LPASS_SCC_PLL_CONFIG_CTL_RMSK                                                                            0xffffffff
#define HWIO_LPASS_SCC_PLL_CONFIG_CTL_IN          \
        in_dword_masked(HWIO_LPASS_SCC_PLL_CONFIG_CTL_ADDR, HWIO_LPASS_SCC_PLL_CONFIG_CTL_RMSK)
#define HWIO_LPASS_SCC_PLL_CONFIG_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_PLL_CONFIG_CTL_ADDR, m)
#define HWIO_LPASS_SCC_PLL_CONFIG_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_PLL_CONFIG_CTL_ADDR,v)
#define HWIO_LPASS_SCC_PLL_CONFIG_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_PLL_CONFIG_CTL_ADDR,m,v,HWIO_LPASS_SCC_PLL_CONFIG_CTL_IN)
#define HWIO_LPASS_SCC_PLL_CONFIG_CTL_RESERVE_BIT_31_BMSK                                                             0x80000000
#define HWIO_LPASS_SCC_PLL_CONFIG_CTL_RESERVE_BIT_31_SHFT                                                                   0x1f
#define HWIO_LPASS_SCC_PLL_CONFIG_CTL_USE_BOTH_REF_CLK_EDGE_BMSK                                                      0x40000000
#define HWIO_LPASS_SCC_PLL_CONFIG_CTL_USE_BOTH_REF_CLK_EDGE_SHFT                                                            0x1e
#define HWIO_LPASS_SCC_PLL_CONFIG_CTL_BIAS_WARMUP_TIME_BMSK                                                           0x30000000
#define HWIO_LPASS_SCC_PLL_CONFIG_CTL_BIAS_WARMUP_TIME_SHFT                                                                 0x1c
#define HWIO_LPASS_SCC_PLL_CONFIG_CTL_FINE_LDC_THRESHOLD_BMSK                                                          0xf000000
#define HWIO_LPASS_SCC_PLL_CONFIG_CTL_FINE_LDC_THRESHOLD_SHFT                                                               0x18
#define HWIO_LPASS_SCC_PLL_CONFIG_CTL_COARSE_LDC_THRESHOLD_BMSK                                                         0xf00000
#define HWIO_LPASS_SCC_PLL_CONFIG_CTL_COARSE_LDC_THRESHOLD_SHFT                                                             0x14
#define HWIO_LPASS_SCC_PLL_CONFIG_CTL_COARSE_LOCK_DET_NEG_THRESHOLD_BMSK                                                 0xf0000
#define HWIO_LPASS_SCC_PLL_CONFIG_CTL_COARSE_LOCK_DET_NEG_THRESHOLD_SHFT                                                    0x10
#define HWIO_LPASS_SCC_PLL_CONFIG_CTL_COARSE_LOCK_DET_POS_THRESHOLD_BMSK                                                  0xf000
#define HWIO_LPASS_SCC_PLL_CONFIG_CTL_COARSE_LOCK_DET_POS_THRESHOLD_SHFT                                                     0xc
#define HWIO_LPASS_SCC_PLL_CONFIG_CTL_FINE_LOCK_DET_THRESHOLD_BMSK                                                         0xe00
#define HWIO_LPASS_SCC_PLL_CONFIG_CTL_FINE_LOCK_DET_THRESHOLD_SHFT                                                           0x9
#define HWIO_LPASS_SCC_PLL_CONFIG_CTL_FINE_LOCK_DET_SAMPLE_SIZE_BMSK                                                       0x1c0
#define HWIO_LPASS_SCC_PLL_CONFIG_CTL_FINE_LOCK_DET_SAMPLE_SIZE_SHFT                                                         0x6
#define HWIO_LPASS_SCC_PLL_CONFIG_CTL_MIN_GLITCH_THRESHOLD_BMSK                                                             0x30
#define HWIO_LPASS_SCC_PLL_CONFIG_CTL_MIN_GLITCH_THRESHOLD_SHFT                                                              0x4
#define HWIO_LPASS_SCC_PLL_CONFIG_CTL_KFN_BMSK                                                                               0xf
#define HWIO_LPASS_SCC_PLL_CONFIG_CTL_KFN_SHFT                                                                               0x0

#define HWIO_LPASS_SCC_PLL_TEST_CTL_ADDR                                                                              (LPASS_CC_REG_BASE      + 0x0003e018)
#define HWIO_LPASS_SCC_PLL_TEST_CTL_OFFS                                                                              (LPASS_CC_REG_BASE_OFFS + 0x0003e018)
#define HWIO_LPASS_SCC_PLL_TEST_CTL_RMSK                                                                              0xffffffff
#define HWIO_LPASS_SCC_PLL_TEST_CTL_IN          \
        in_dword_masked(HWIO_LPASS_SCC_PLL_TEST_CTL_ADDR, HWIO_LPASS_SCC_PLL_TEST_CTL_RMSK)
#define HWIO_LPASS_SCC_PLL_TEST_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_PLL_TEST_CTL_ADDR, m)
#define HWIO_LPASS_SCC_PLL_TEST_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_PLL_TEST_CTL_ADDR,v)
#define HWIO_LPASS_SCC_PLL_TEST_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_PLL_TEST_CTL_ADDR,m,v,HWIO_LPASS_SCC_PLL_TEST_CTL_IN)
#define HWIO_LPASS_SCC_PLL_TEST_CTL_NOISE_MAG_BMSK                                                                    0xc0000000
#define HWIO_LPASS_SCC_PLL_TEST_CTL_NOISE_MAG_SHFT                                                                          0x1e
#define HWIO_LPASS_SCC_PLL_TEST_CTL_NOISE_GEN_BMSK                                                                    0x20000000
#define HWIO_LPASS_SCC_PLL_TEST_CTL_NOISE_GEN_SHFT                                                                          0x1d
#define HWIO_LPASS_SCC_PLL_TEST_CTL_OSC_BIAS_GND_BMSK                                                                 0x10000000
#define HWIO_LPASS_SCC_PLL_TEST_CTL_OSC_BIAS_GND_SHFT                                                                       0x1c
#define HWIO_LPASS_SCC_PLL_TEST_CTL_PLL_TEST_OUT_SEL_BMSK                                                              0xc000000
#define HWIO_LPASS_SCC_PLL_TEST_CTL_PLL_TEST_OUT_SEL_SHFT                                                                   0x1a
#define HWIO_LPASS_SCC_PLL_TEST_CTL_COARSE_FCW_BMSK                                                                    0x3fc0000
#define HWIO_LPASS_SCC_PLL_TEST_CTL_COARSE_FCW_SHFT                                                                         0x12
#define HWIO_LPASS_SCC_PLL_TEST_CTL_OVERRIDE_COARSE_FCW_BMSK                                                             0x20000
#define HWIO_LPASS_SCC_PLL_TEST_CTL_OVERRIDE_COARSE_FCW_SHFT                                                                0x11
#define HWIO_LPASS_SCC_PLL_TEST_CTL_COARSE_PCW_BMSK                                                                      0x1c000
#define HWIO_LPASS_SCC_PLL_TEST_CTL_COARSE_PCW_SHFT                                                                          0xe
#define HWIO_LPASS_SCC_PLL_TEST_CTL_OVERRIDE_COARSE_PCW_BMSK                                                              0x2000
#define HWIO_LPASS_SCC_PLL_TEST_CTL_OVERRIDE_COARSE_PCW_SHFT                                                                 0xd
#define HWIO_LPASS_SCC_PLL_TEST_CTL_DISABLE_LFSR_BMSK                                                                     0x1000
#define HWIO_LPASS_SCC_PLL_TEST_CTL_DISABLE_LFSR_SHFT                                                                        0xc
#define HWIO_LPASS_SCC_PLL_TEST_CTL_DTEST_SEL_BMSK                                                                         0xf80
#define HWIO_LPASS_SCC_PLL_TEST_CTL_DTEST_SEL_SHFT                                                                           0x7
#define HWIO_LPASS_SCC_PLL_TEST_CTL_DTEST_EN_BMSK                                                                           0x40
#define HWIO_LPASS_SCC_PLL_TEST_CTL_DTEST_EN_SHFT                                                                            0x6
#define HWIO_LPASS_SCC_PLL_TEST_CTL_ATEST1_SEL_BMSK                                                                         0x30
#define HWIO_LPASS_SCC_PLL_TEST_CTL_ATEST1_SEL_SHFT                                                                          0x4
#define HWIO_LPASS_SCC_PLL_TEST_CTL_ATEST0_SEL_BMSK                                                                          0xc
#define HWIO_LPASS_SCC_PLL_TEST_CTL_ATEST0_SEL_SHFT                                                                          0x2
#define HWIO_LPASS_SCC_PLL_TEST_CTL_ATEST1_EN_BMSK                                                                           0x2
#define HWIO_LPASS_SCC_PLL_TEST_CTL_ATEST1_EN_SHFT                                                                           0x1
#define HWIO_LPASS_SCC_PLL_TEST_CTL_ATEST0_EN_BMSK                                                                           0x1
#define HWIO_LPASS_SCC_PLL_TEST_CTL_ATEST0_EN_SHFT                                                                           0x0

#define HWIO_LPASS_SCC_PLL_TEST_CTL_U_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x0003e01c)
#define HWIO_LPASS_SCC_PLL_TEST_CTL_U_OFFS                                                                            (LPASS_CC_REG_BASE_OFFS + 0x0003e01c)
#define HWIO_LPASS_SCC_PLL_TEST_CTL_U_RMSK                                                                            0xffffffff
#define HWIO_LPASS_SCC_PLL_TEST_CTL_U_IN          \
        in_dword_masked(HWIO_LPASS_SCC_PLL_TEST_CTL_U_ADDR, HWIO_LPASS_SCC_PLL_TEST_CTL_U_RMSK)
#define HWIO_LPASS_SCC_PLL_TEST_CTL_U_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_PLL_TEST_CTL_U_ADDR, m)
#define HWIO_LPASS_SCC_PLL_TEST_CTL_U_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_PLL_TEST_CTL_U_ADDR,v)
#define HWIO_LPASS_SCC_PLL_TEST_CTL_U_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_PLL_TEST_CTL_U_ADDR,m,v,HWIO_LPASS_SCC_PLL_TEST_CTL_U_IN)
#define HWIO_LPASS_SCC_PLL_TEST_CTL_U_RESERVE_BITS31_9_BMSK                                                           0xfffffe00
#define HWIO_LPASS_SCC_PLL_TEST_CTL_U_RESERVE_BITS31_9_SHFT                                                                  0x9
#define HWIO_LPASS_SCC_PLL_TEST_CTL_U_USE_LINEAR_SETTLING_BMSK                                                             0x100
#define HWIO_LPASS_SCC_PLL_TEST_CTL_U_USE_LINEAR_SETTLING_SHFT                                                               0x8
#define HWIO_LPASS_SCC_PLL_TEST_CTL_U_DIS_AUTO_UPDATE_CALIB_CODE_BMSK                                                       0x80
#define HWIO_LPASS_SCC_PLL_TEST_CTL_U_DIS_AUTO_UPDATE_CALIB_CODE_SHFT                                                        0x7
#define HWIO_LPASS_SCC_PLL_TEST_CTL_U_NUM_REF_CYCLE_PER_CALIB_STEP_BMSK                                                     0x60
#define HWIO_LPASS_SCC_PLL_TEST_CTL_U_NUM_REF_CYCLE_PER_CALIB_STEP_SHFT                                                      0x5
#define HWIO_LPASS_SCC_PLL_TEST_CTL_U_GLITCH_DET_COUNT_BMSK                                                                 0x18
#define HWIO_LPASS_SCC_PLL_TEST_CTL_U_GLITCH_DET_COUNT_SHFT                                                                  0x3
#define HWIO_LPASS_SCC_PLL_TEST_CTL_U_DIS_GLITCH_PREV_BMSK                                                                   0x4
#define HWIO_LPASS_SCC_PLL_TEST_CTL_U_DIS_GLITCH_PREV_SHFT                                                                   0x2
#define HWIO_LPASS_SCC_PLL_TEST_CTL_U_NMO_OSC_SEL_BMSK                                                                       0x3
#define HWIO_LPASS_SCC_PLL_TEST_CTL_U_NMO_OSC_SEL_SHFT                                                                       0x0

#define HWIO_LPASS_SCC_PLL_STATUS_ADDR                                                                                (LPASS_CC_REG_BASE      + 0x0003e020)
#define HWIO_LPASS_SCC_PLL_STATUS_OFFS                                                                                (LPASS_CC_REG_BASE_OFFS + 0x0003e020)
#define HWIO_LPASS_SCC_PLL_STATUS_RMSK                                                                                0xffffffff
#define HWIO_LPASS_SCC_PLL_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_SCC_PLL_STATUS_ADDR, HWIO_LPASS_SCC_PLL_STATUS_RMSK)
#define HWIO_LPASS_SCC_PLL_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_PLL_STATUS_ADDR, m)
#define HWIO_LPASS_SCC_PLL_STATUS_STATUS_31_0_BMSK                                                                    0xffffffff
#define HWIO_LPASS_SCC_PLL_STATUS_STATUS_31_0_SHFT                                                                           0x0

#define HWIO_LPASS_SCC_PLL_FREQ_CTL_ADDR                                                                              (LPASS_CC_REG_BASE      + 0x0003e024)
#define HWIO_LPASS_SCC_PLL_FREQ_CTL_OFFS                                                                              (LPASS_CC_REG_BASE_OFFS + 0x0003e024)
#define HWIO_LPASS_SCC_PLL_FREQ_CTL_RMSK                                                                              0xffffffff
#define HWIO_LPASS_SCC_PLL_FREQ_CTL_IN          \
        in_dword_masked(HWIO_LPASS_SCC_PLL_FREQ_CTL_ADDR, HWIO_LPASS_SCC_PLL_FREQ_CTL_RMSK)
#define HWIO_LPASS_SCC_PLL_FREQ_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_PLL_FREQ_CTL_ADDR, m)
#define HWIO_LPASS_SCC_PLL_FREQ_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_PLL_FREQ_CTL_ADDR,v)
#define HWIO_LPASS_SCC_PLL_FREQ_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_PLL_FREQ_CTL_ADDR,m,v,HWIO_LPASS_SCC_PLL_FREQ_CTL_IN)
#define HWIO_LPASS_SCC_PLL_FREQ_CTL_FREQUENCY_CTL_WORD_BMSK                                                           0xffffffff
#define HWIO_LPASS_SCC_PLL_FREQ_CTL_FREQUENCY_CTL_WORD_SHFT                                                                  0x0

#define HWIO_LPASS_SCC_PLL_OPMODE_ADDR                                                                                (LPASS_CC_REG_BASE      + 0x0003e028)
#define HWIO_LPASS_SCC_PLL_OPMODE_OFFS                                                                                (LPASS_CC_REG_BASE_OFFS + 0x0003e028)
#define HWIO_LPASS_SCC_PLL_OPMODE_RMSK                                                                                       0x7
#define HWIO_LPASS_SCC_PLL_OPMODE_IN          \
        in_dword_masked(HWIO_LPASS_SCC_PLL_OPMODE_ADDR, HWIO_LPASS_SCC_PLL_OPMODE_RMSK)
#define HWIO_LPASS_SCC_PLL_OPMODE_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_PLL_OPMODE_ADDR, m)
#define HWIO_LPASS_SCC_PLL_OPMODE_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_PLL_OPMODE_ADDR,v)
#define HWIO_LPASS_SCC_PLL_OPMODE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_PLL_OPMODE_ADDR,m,v,HWIO_LPASS_SCC_PLL_OPMODE_IN)
#define HWIO_LPASS_SCC_PLL_OPMODE_PLL_OPMODE_BMSK                                                                            0x7
#define HWIO_LPASS_SCC_PLL_OPMODE_PLL_OPMODE_SHFT                                                                            0x0

#define HWIO_LPASS_SCC_CBC_MISC_ADDR                                                                                  (LPASS_CC_REG_BASE      + 0x0003e04c)
#define HWIO_LPASS_SCC_CBC_MISC_OFFS                                                                                  (LPASS_CC_REG_BASE_OFFS + 0x0003e04c)
#define HWIO_LPASS_SCC_CBC_MISC_RMSK                                                                                         0x1
#define HWIO_LPASS_SCC_CBC_MISC_IN          \
        in_dword_masked(HWIO_LPASS_SCC_CBC_MISC_ADDR, HWIO_LPASS_SCC_CBC_MISC_RMSK)
#define HWIO_LPASS_SCC_CBC_MISC_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_CBC_MISC_ADDR, m)
#define HWIO_LPASS_SCC_CBC_MISC_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_CBC_MISC_ADDR,v)
#define HWIO_LPASS_SCC_CBC_MISC_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_CBC_MISC_ADDR,m,v,HWIO_LPASS_SCC_CBC_MISC_IN)
#define HWIO_LPASS_SCC_CBC_MISC_SCC_IDDQ_ALL_CBC_DIS_BMSK                                                                    0x1
#define HWIO_LPASS_SCC_CBC_MISC_SCC_IDDQ_ALL_CBC_DIS_SHFT                                                                    0x0

#define HWIO_LPASS_SCC_DEBUG_CLK_CTL_ADDR                                                                             (LPASS_CC_REG_BASE      + 0x0003e050)
#define HWIO_LPASS_SCC_DEBUG_CLK_CTL_OFFS                                                                             (LPASS_CC_REG_BASE_OFFS + 0x0003e050)
#define HWIO_LPASS_SCC_DEBUG_CLK_CTL_RMSK                                                                                    0x7
#define HWIO_LPASS_SCC_DEBUG_CLK_CTL_IN          \
        in_dword_masked(HWIO_LPASS_SCC_DEBUG_CLK_CTL_ADDR, HWIO_LPASS_SCC_DEBUG_CLK_CTL_RMSK)
#define HWIO_LPASS_SCC_DEBUG_CLK_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_DEBUG_CLK_CTL_ADDR, m)
#define HWIO_LPASS_SCC_DEBUG_CLK_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_DEBUG_CLK_CTL_ADDR,v)
#define HWIO_LPASS_SCC_DEBUG_CLK_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_DEBUG_CLK_CTL_ADDR,m,v,HWIO_LPASS_SCC_DEBUG_CLK_CTL_IN)
#define HWIO_LPASS_SCC_DEBUG_CLK_CTL_PLL_TEST_CLK_ENABLE_BMSK                                                                0x4
#define HWIO_LPASS_SCC_DEBUG_CLK_CTL_PLL_TEST_CLK_ENABLE_SHFT                                                                0x2
#define HWIO_LPASS_SCC_DEBUG_CLK_CTL_PLL_TEST_POST_DIV_BMSK                                                                  0x3
#define HWIO_LPASS_SCC_DEBUG_CLK_CTL_PLL_TEST_POST_DIV_SHFT                                                                  0x0

#define HWIO_LPASS_SCC_AON_CTRL_OVRD_REG_ADDR                                                                         (LPASS_CC_REG_BASE      + 0x0003e054)
#define HWIO_LPASS_SCC_AON_CTRL_OVRD_REG_OFFS                                                                         (LPASS_CC_REG_BASE_OFFS + 0x0003e054)
#define HWIO_LPASS_SCC_AON_CTRL_OVRD_REG_RMSK                                                                               0x3f
#define HWIO_LPASS_SCC_AON_CTRL_OVRD_REG_IN          \
        in_dword_masked(HWIO_LPASS_SCC_AON_CTRL_OVRD_REG_ADDR, HWIO_LPASS_SCC_AON_CTRL_OVRD_REG_RMSK)
#define HWIO_LPASS_SCC_AON_CTRL_OVRD_REG_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_AON_CTRL_OVRD_REG_ADDR, m)
#define HWIO_LPASS_SCC_AON_CTRL_OVRD_REG_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_AON_CTRL_OVRD_REG_ADDR,v)
#define HWIO_LPASS_SCC_AON_CTRL_OVRD_REG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_AON_CTRL_OVRD_REG_ADDR,m,v,HWIO_LPASS_SCC_AON_CTRL_OVRD_REG_IN)
#define HWIO_LPASS_SCC_AON_CTRL_OVRD_REG_SLEEP_CLK_SEL_OVRD_VAL_BMSK                                                        0x20
#define HWIO_LPASS_SCC_AON_CTRL_OVRD_REG_SLEEP_CLK_SEL_OVRD_VAL_SHFT                                                         0x5
#define HWIO_LPASS_SCC_AON_CTRL_OVRD_REG_SLEEP_CLK_SEL_OVRD_BMSK                                                            0x10
#define HWIO_LPASS_SCC_AON_CTRL_OVRD_REG_SLEEP_CLK_SEL_OVRD_SHFT                                                             0x4
#define HWIO_LPASS_SCC_AON_CTRL_OVRD_REG_CBC_EN_OVRD_VAL_BMSK                                                                0x8
#define HWIO_LPASS_SCC_AON_CTRL_OVRD_REG_CBC_EN_OVRD_VAL_SHFT                                                                0x3
#define HWIO_LPASS_SCC_AON_CTRL_OVRD_REG_CBC_EN_OVRD_BMSK                                                                    0x4
#define HWIO_LPASS_SCC_AON_CTRL_OVRD_REG_CBC_EN_OVRD_SHFT                                                                    0x2
#define HWIO_LPASS_SCC_AON_CTRL_OVRD_REG_PLL_OUT_CTRL_OVRD_BMSK                                                              0x2
#define HWIO_LPASS_SCC_AON_CTRL_OVRD_REG_PLL_OUT_CTRL_OVRD_SHFT                                                              0x1
#define HWIO_LPASS_SCC_AON_CTRL_OVRD_REG_PLL_OPMODE_CTRL_OVRD_BMSK                                                           0x1
#define HWIO_LPASS_SCC_AON_CTRL_OVRD_REG_PLL_OPMODE_CTRL_OVRD_SHFT                                                           0x0

#define HWIO_LPASS_SCC_PLL_CLK_DIV_ADDR                                                                               (LPASS_CC_REG_BASE      + 0x0003e058)
#define HWIO_LPASS_SCC_PLL_CLK_DIV_OFFS                                                                               (LPASS_CC_REG_BASE_OFFS + 0x0003e058)
#define HWIO_LPASS_SCC_PLL_CLK_DIV_RMSK                                                                                      0xf
#define HWIO_LPASS_SCC_PLL_CLK_DIV_IN          \
        in_dword_masked(HWIO_LPASS_SCC_PLL_CLK_DIV_ADDR, HWIO_LPASS_SCC_PLL_CLK_DIV_RMSK)
#define HWIO_LPASS_SCC_PLL_CLK_DIV_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_PLL_CLK_DIV_ADDR, m)
#define HWIO_LPASS_SCC_PLL_CLK_DIV_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_PLL_CLK_DIV_ADDR,v)
#define HWIO_LPASS_SCC_PLL_CLK_DIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_PLL_CLK_DIV_ADDR,m,v,HWIO_LPASS_SCC_PLL_CLK_DIV_IN)
#define HWIO_LPASS_SCC_PLL_CLK_DIV_CLK_MAIN_DIV_BMSK                                                                         0xf
#define HWIO_LPASS_SCC_PLL_CLK_DIV_CLK_MAIN_DIV_SHFT                                                                         0x0

#define HWIO_LPASS_SCC_PLL_REF_CLK_SRC_SEL_ADDR                                                                       (LPASS_CC_REG_BASE      + 0x0003e05c)
#define HWIO_LPASS_SCC_PLL_REF_CLK_SRC_SEL_OFFS                                                                       (LPASS_CC_REG_BASE_OFFS + 0x0003e05c)
#define HWIO_LPASS_SCC_PLL_REF_CLK_SRC_SEL_RMSK                                                                              0x3
#define HWIO_LPASS_SCC_PLL_REF_CLK_SRC_SEL_IN          \
        in_dword_masked(HWIO_LPASS_SCC_PLL_REF_CLK_SRC_SEL_ADDR, HWIO_LPASS_SCC_PLL_REF_CLK_SRC_SEL_RMSK)
#define HWIO_LPASS_SCC_PLL_REF_CLK_SRC_SEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_PLL_REF_CLK_SRC_SEL_ADDR, m)
#define HWIO_LPASS_SCC_PLL_REF_CLK_SRC_SEL_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_PLL_REF_CLK_SRC_SEL_ADDR,v)
#define HWIO_LPASS_SCC_PLL_REF_CLK_SRC_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_PLL_REF_CLK_SRC_SEL_ADDR,m,v,HWIO_LPASS_SCC_PLL_REF_CLK_SRC_SEL_IN)
#define HWIO_LPASS_SCC_PLL_REF_CLK_SRC_SEL_PLL_CLK_SRC_SEL_BMSK                                                              0x3
#define HWIO_LPASS_SCC_PLL_REF_CLK_SRC_SEL_PLL_CLK_SRC_SEL_SHFT                                                              0x0

#define HWIO_LPASS_SCC_100M_CMD_RCGR_ADDR                                                                             (LPASS_CC_REG_BASE      + 0x0003f000)
#define HWIO_LPASS_SCC_100M_CMD_RCGR_OFFS                                                                             (LPASS_CC_REG_BASE_OFFS + 0x0003f000)
#define HWIO_LPASS_SCC_100M_CMD_RCGR_RMSK                                                                             0x800000f3
#define HWIO_LPASS_SCC_100M_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_SCC_100M_CMD_RCGR_ADDR, HWIO_LPASS_SCC_100M_CMD_RCGR_RMSK)
#define HWIO_LPASS_SCC_100M_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_100M_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_SCC_100M_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_100M_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_SCC_100M_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_100M_CMD_RCGR_ADDR,m,v,HWIO_LPASS_SCC_100M_CMD_RCGR_IN)
#define HWIO_LPASS_SCC_100M_CMD_RCGR_ROOT_OFF_BMSK                                                                    0x80000000
#define HWIO_LPASS_SCC_100M_CMD_RCGR_ROOT_OFF_SHFT                                                                          0x1f
#define HWIO_LPASS_SCC_100M_CMD_RCGR_DIRTY_D_BMSK                                                                           0x80
#define HWIO_LPASS_SCC_100M_CMD_RCGR_DIRTY_D_SHFT                                                                            0x7
#define HWIO_LPASS_SCC_100M_CMD_RCGR_DIRTY_N_BMSK                                                                           0x40
#define HWIO_LPASS_SCC_100M_CMD_RCGR_DIRTY_N_SHFT                                                                            0x6
#define HWIO_LPASS_SCC_100M_CMD_RCGR_DIRTY_M_BMSK                                                                           0x20
#define HWIO_LPASS_SCC_100M_CMD_RCGR_DIRTY_M_SHFT                                                                            0x5
#define HWIO_LPASS_SCC_100M_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                    0x10
#define HWIO_LPASS_SCC_100M_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                     0x4
#define HWIO_LPASS_SCC_100M_CMD_RCGR_ROOT_EN_BMSK                                                                            0x2
#define HWIO_LPASS_SCC_100M_CMD_RCGR_ROOT_EN_SHFT                                                                            0x1
#define HWIO_LPASS_SCC_100M_CMD_RCGR_UPDATE_BMSK                                                                             0x1
#define HWIO_LPASS_SCC_100M_CMD_RCGR_UPDATE_SHFT                                                                             0x0

#define HWIO_LPASS_SCC_100M_CFG_RCGR_ADDR                                                                             (LPASS_CC_REG_BASE      + 0x0003f004)
#define HWIO_LPASS_SCC_100M_CFG_RCGR_OFFS                                                                             (LPASS_CC_REG_BASE_OFFS + 0x0003f004)
#define HWIO_LPASS_SCC_100M_CFG_RCGR_RMSK                                                                                  0x71f
#define HWIO_LPASS_SCC_100M_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_SCC_100M_CFG_RCGR_ADDR, HWIO_LPASS_SCC_100M_CFG_RCGR_RMSK)
#define HWIO_LPASS_SCC_100M_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_100M_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_SCC_100M_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_100M_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_SCC_100M_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_100M_CFG_RCGR_ADDR,m,v,HWIO_LPASS_SCC_100M_CFG_RCGR_IN)
#define HWIO_LPASS_SCC_100M_CFG_RCGR_SRC_SEL_BMSK                                                                          0x700
#define HWIO_LPASS_SCC_100M_CFG_RCGR_SRC_SEL_SHFT                                                                            0x8
#define HWIO_LPASS_SCC_100M_CFG_RCGR_SRC_DIV_BMSK                                                                           0x1f
#define HWIO_LPASS_SCC_100M_CFG_RCGR_SRC_DIV_SHFT                                                                            0x0

#define HWIO_LPASS_ISLAND_SCC_SPI_I2C1_BCR_ADDR                                                                       (LPASS_CC_REG_BASE      + 0x00040000)
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C1_BCR_OFFS                                                                       (LPASS_CC_REG_BASE_OFFS + 0x00040000)
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C1_BCR_RMSK                                                                              0x1
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C1_BCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_SPI_I2C1_BCR_ADDR, HWIO_LPASS_ISLAND_SCC_SPI_I2C1_BCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C1_BCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_SPI_I2C1_BCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C1_BCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_SPI_I2C1_BCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C1_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_SPI_I2C1_BCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_SPI_I2C1_BCR_IN)
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C1_BCR_BLK_ARES_BMSK                                                                     0x1
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C1_BCR_BLK_ARES_SHFT                                                                     0x0

#define HWIO_LPASS_ISLAND_SCC_SPI_I2C1_CLK_CDIV_REG_ADDR                                                              (LPASS_CC_REG_BASE      + 0x00040004)
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C1_CLK_CDIV_REG_OFFS                                                              (LPASS_CC_REG_BASE_OFFS + 0x00040004)
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C1_CLK_CDIV_REG_RMSK                                                                   0x1ff
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C1_CLK_CDIV_REG_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_SPI_I2C1_CLK_CDIV_REG_ADDR, HWIO_LPASS_ISLAND_SCC_SPI_I2C1_CLK_CDIV_REG_RMSK)
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C1_CLK_CDIV_REG_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_SPI_I2C1_CLK_CDIV_REG_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C1_CLK_CDIV_REG_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_SPI_I2C1_CLK_CDIV_REG_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C1_CLK_CDIV_REG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_SPI_I2C1_CLK_CDIV_REG_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_SPI_I2C1_CLK_CDIV_REG_IN)
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C1_CLK_CDIV_REG_CLK_DIV_BMSK                                                           0x1ff
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C1_CLK_CDIV_REG_CLK_DIV_SHFT                                                             0x0

#define HWIO_LPASS_ISLAND_SCC_QUP_SPI1_CBCR_ADDR                                                                      (LPASS_CC_REG_BASE      + 0x00040008)
#define HWIO_LPASS_ISLAND_SCC_QUP_SPI1_CBCR_OFFS                                                                      (LPASS_CC_REG_BASE_OFFS + 0x00040008)
#define HWIO_LPASS_ISLAND_SCC_QUP_SPI1_CBCR_RMSK                                                                      0x80000001
#define HWIO_LPASS_ISLAND_SCC_QUP_SPI1_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_QUP_SPI1_CBCR_ADDR, HWIO_LPASS_ISLAND_SCC_QUP_SPI1_CBCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_QUP_SPI1_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_QUP_SPI1_CBCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_QUP_SPI1_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_QUP_SPI1_CBCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_QUP_SPI1_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_QUP_SPI1_CBCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_QUP_SPI1_CBCR_IN)
#define HWIO_LPASS_ISLAND_SCC_QUP_SPI1_CBCR_CLK_OFF_BMSK                                                              0x80000000
#define HWIO_LPASS_ISLAND_SCC_QUP_SPI1_CBCR_CLK_OFF_SHFT                                                                    0x1f
#define HWIO_LPASS_ISLAND_SCC_QUP_SPI1_CBCR_CLK_ENABLE_BMSK                                                                  0x1
#define HWIO_LPASS_ISLAND_SCC_QUP_SPI1_CBCR_CLK_ENABLE_SHFT                                                                  0x0

#define HWIO_LPASS_ISLAND_SCC_QUP_I2C1_CBCR_ADDR                                                                      (LPASS_CC_REG_BASE      + 0x0004000c)
#define HWIO_LPASS_ISLAND_SCC_QUP_I2C1_CBCR_OFFS                                                                      (LPASS_CC_REG_BASE_OFFS + 0x0004000c)
#define HWIO_LPASS_ISLAND_SCC_QUP_I2C1_CBCR_RMSK                                                                      0x80000001
#define HWIO_LPASS_ISLAND_SCC_QUP_I2C1_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_QUP_I2C1_CBCR_ADDR, HWIO_LPASS_ISLAND_SCC_QUP_I2C1_CBCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_QUP_I2C1_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_QUP_I2C1_CBCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_QUP_I2C1_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_QUP_I2C1_CBCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_QUP_I2C1_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_QUP_I2C1_CBCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_QUP_I2C1_CBCR_IN)
#define HWIO_LPASS_ISLAND_SCC_QUP_I2C1_CBCR_CLK_OFF_BMSK                                                              0x80000000
#define HWIO_LPASS_ISLAND_SCC_QUP_I2C1_CBCR_CLK_OFF_SHFT                                                                    0x1f
#define HWIO_LPASS_ISLAND_SCC_QUP_I2C1_CBCR_CLK_ENABLE_BMSK                                                                  0x1
#define HWIO_LPASS_ISLAND_SCC_QUP_I2C1_CBCR_CLK_ENABLE_SHFT                                                                  0x0

#define HWIO_LPASS_ISLAND_SCC_SPI_I2C2_BCR_ADDR                                                                       (LPASS_CC_REG_BASE      + 0x00041000)
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C2_BCR_OFFS                                                                       (LPASS_CC_REG_BASE_OFFS + 0x00041000)
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C2_BCR_RMSK                                                                              0x1
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C2_BCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_SPI_I2C2_BCR_ADDR, HWIO_LPASS_ISLAND_SCC_SPI_I2C2_BCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C2_BCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_SPI_I2C2_BCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C2_BCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_SPI_I2C2_BCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C2_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_SPI_I2C2_BCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_SPI_I2C2_BCR_IN)
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C2_BCR_BLK_ARES_BMSK                                                                     0x1
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C2_BCR_BLK_ARES_SHFT                                                                     0x0

#define HWIO_LPASS_ISLAND_SCC_SPI_I2C2_CLK_CDIV_REG_ADDR                                                              (LPASS_CC_REG_BASE      + 0x00041004)
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C2_CLK_CDIV_REG_OFFS                                                              (LPASS_CC_REG_BASE_OFFS + 0x00041004)
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C2_CLK_CDIV_REG_RMSK                                                                   0x1ff
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C2_CLK_CDIV_REG_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_SPI_I2C2_CLK_CDIV_REG_ADDR, HWIO_LPASS_ISLAND_SCC_SPI_I2C2_CLK_CDIV_REG_RMSK)
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C2_CLK_CDIV_REG_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_SPI_I2C2_CLK_CDIV_REG_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C2_CLK_CDIV_REG_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_SPI_I2C2_CLK_CDIV_REG_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C2_CLK_CDIV_REG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_SPI_I2C2_CLK_CDIV_REG_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_SPI_I2C2_CLK_CDIV_REG_IN)
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C2_CLK_CDIV_REG_CLK_DIV_BMSK                                                           0x1ff
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C2_CLK_CDIV_REG_CLK_DIV_SHFT                                                             0x0

#define HWIO_LPASS_ISLAND_SCC_QUP_SPI2_CBCR_ADDR                                                                      (LPASS_CC_REG_BASE      + 0x00041008)
#define HWIO_LPASS_ISLAND_SCC_QUP_SPI2_CBCR_OFFS                                                                      (LPASS_CC_REG_BASE_OFFS + 0x00041008)
#define HWIO_LPASS_ISLAND_SCC_QUP_SPI2_CBCR_RMSK                                                                      0x80000001
#define HWIO_LPASS_ISLAND_SCC_QUP_SPI2_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_QUP_SPI2_CBCR_ADDR, HWIO_LPASS_ISLAND_SCC_QUP_SPI2_CBCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_QUP_SPI2_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_QUP_SPI2_CBCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_QUP_SPI2_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_QUP_SPI2_CBCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_QUP_SPI2_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_QUP_SPI2_CBCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_QUP_SPI2_CBCR_IN)
#define HWIO_LPASS_ISLAND_SCC_QUP_SPI2_CBCR_CLK_OFF_BMSK                                                              0x80000000
#define HWIO_LPASS_ISLAND_SCC_QUP_SPI2_CBCR_CLK_OFF_SHFT                                                                    0x1f
#define HWIO_LPASS_ISLAND_SCC_QUP_SPI2_CBCR_CLK_ENABLE_BMSK                                                                  0x1
#define HWIO_LPASS_ISLAND_SCC_QUP_SPI2_CBCR_CLK_ENABLE_SHFT                                                                  0x0

#define HWIO_LPASS_ISLAND_SCC_QUP_I2C2_CBCR_ADDR                                                                      (LPASS_CC_REG_BASE      + 0x0004100c)
#define HWIO_LPASS_ISLAND_SCC_QUP_I2C2_CBCR_OFFS                                                                      (LPASS_CC_REG_BASE_OFFS + 0x0004100c)
#define HWIO_LPASS_ISLAND_SCC_QUP_I2C2_CBCR_RMSK                                                                      0x80000001
#define HWIO_LPASS_ISLAND_SCC_QUP_I2C2_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_QUP_I2C2_CBCR_ADDR, HWIO_LPASS_ISLAND_SCC_QUP_I2C2_CBCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_QUP_I2C2_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_QUP_I2C2_CBCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_QUP_I2C2_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_QUP_I2C2_CBCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_QUP_I2C2_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_QUP_I2C2_CBCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_QUP_I2C2_CBCR_IN)
#define HWIO_LPASS_ISLAND_SCC_QUP_I2C2_CBCR_CLK_OFF_BMSK                                                              0x80000000
#define HWIO_LPASS_ISLAND_SCC_QUP_I2C2_CBCR_CLK_OFF_SHFT                                                                    0x1f
#define HWIO_LPASS_ISLAND_SCC_QUP_I2C2_CBCR_CLK_ENABLE_BMSK                                                                  0x1
#define HWIO_LPASS_ISLAND_SCC_QUP_I2C2_CBCR_CLK_ENABLE_SHFT                                                                  0x0

#define HWIO_LPASS_ISLAND_SCC_SPI_I2C3_BCR_ADDR                                                                       (LPASS_CC_REG_BASE      + 0x00042000)
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C3_BCR_OFFS                                                                       (LPASS_CC_REG_BASE_OFFS + 0x00042000)
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C3_BCR_RMSK                                                                              0x1
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C3_BCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_SPI_I2C3_BCR_ADDR, HWIO_LPASS_ISLAND_SCC_SPI_I2C3_BCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C3_BCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_SPI_I2C3_BCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C3_BCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_SPI_I2C3_BCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C3_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_SPI_I2C3_BCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_SPI_I2C3_BCR_IN)
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C3_BCR_BLK_ARES_BMSK                                                                     0x1
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C3_BCR_BLK_ARES_SHFT                                                                     0x0

#define HWIO_LPASS_ISLAND_SCC_SPI_I2C3_CLK_CDIV_REG_ADDR                                                              (LPASS_CC_REG_BASE      + 0x00042004)
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C3_CLK_CDIV_REG_OFFS                                                              (LPASS_CC_REG_BASE_OFFS + 0x00042004)
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C3_CLK_CDIV_REG_RMSK                                                                   0x1ff
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C3_CLK_CDIV_REG_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_SPI_I2C3_CLK_CDIV_REG_ADDR, HWIO_LPASS_ISLAND_SCC_SPI_I2C3_CLK_CDIV_REG_RMSK)
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C3_CLK_CDIV_REG_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_SPI_I2C3_CLK_CDIV_REG_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C3_CLK_CDIV_REG_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_SPI_I2C3_CLK_CDIV_REG_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C3_CLK_CDIV_REG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_SPI_I2C3_CLK_CDIV_REG_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_SPI_I2C3_CLK_CDIV_REG_IN)
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C3_CLK_CDIV_REG_CLK_DIV_BMSK                                                           0x1ff
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C3_CLK_CDIV_REG_CLK_DIV_SHFT                                                             0x0

#define HWIO_LPASS_ISLAND_SCC_QUP_SPI3_CBCR_ADDR                                                                      (LPASS_CC_REG_BASE      + 0x00042008)
#define HWIO_LPASS_ISLAND_SCC_QUP_SPI3_CBCR_OFFS                                                                      (LPASS_CC_REG_BASE_OFFS + 0x00042008)
#define HWIO_LPASS_ISLAND_SCC_QUP_SPI3_CBCR_RMSK                                                                      0x80000001
#define HWIO_LPASS_ISLAND_SCC_QUP_SPI3_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_QUP_SPI3_CBCR_ADDR, HWIO_LPASS_ISLAND_SCC_QUP_SPI3_CBCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_QUP_SPI3_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_QUP_SPI3_CBCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_QUP_SPI3_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_QUP_SPI3_CBCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_QUP_SPI3_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_QUP_SPI3_CBCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_QUP_SPI3_CBCR_IN)
#define HWIO_LPASS_ISLAND_SCC_QUP_SPI3_CBCR_CLK_OFF_BMSK                                                              0x80000000
#define HWIO_LPASS_ISLAND_SCC_QUP_SPI3_CBCR_CLK_OFF_SHFT                                                                    0x1f
#define HWIO_LPASS_ISLAND_SCC_QUP_SPI3_CBCR_CLK_ENABLE_BMSK                                                                  0x1
#define HWIO_LPASS_ISLAND_SCC_QUP_SPI3_CBCR_CLK_ENABLE_SHFT                                                                  0x0

#define HWIO_LPASS_ISLAND_SCC_QUP_I2C3_CBCR_ADDR                                                                      (LPASS_CC_REG_BASE      + 0x0004200c)
#define HWIO_LPASS_ISLAND_SCC_QUP_I2C3_CBCR_OFFS                                                                      (LPASS_CC_REG_BASE_OFFS + 0x0004200c)
#define HWIO_LPASS_ISLAND_SCC_QUP_I2C3_CBCR_RMSK                                                                      0x80000001
#define HWIO_LPASS_ISLAND_SCC_QUP_I2C3_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_QUP_I2C3_CBCR_ADDR, HWIO_LPASS_ISLAND_SCC_QUP_I2C3_CBCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_QUP_I2C3_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_QUP_I2C3_CBCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_QUP_I2C3_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_QUP_I2C3_CBCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_QUP_I2C3_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_QUP_I2C3_CBCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_QUP_I2C3_CBCR_IN)
#define HWIO_LPASS_ISLAND_SCC_QUP_I2C3_CBCR_CLK_OFF_BMSK                                                              0x80000000
#define HWIO_LPASS_ISLAND_SCC_QUP_I2C3_CBCR_CLK_OFF_SHFT                                                                    0x1f
#define HWIO_LPASS_ISLAND_SCC_QUP_I2C3_CBCR_CLK_ENABLE_BMSK                                                                  0x1
#define HWIO_LPASS_ISLAND_SCC_QUP_I2C3_CBCR_CLK_ENABLE_SHFT                                                                  0x0

#define HWIO_LPASS_ISLAND_SCC_UART1_BCR_ADDR                                                                          (LPASS_CC_REG_BASE      + 0x00043000)
#define HWIO_LPASS_ISLAND_SCC_UART1_BCR_OFFS                                                                          (LPASS_CC_REG_BASE_OFFS + 0x00043000)
#define HWIO_LPASS_ISLAND_SCC_UART1_BCR_RMSK                                                                                 0x1
#define HWIO_LPASS_ISLAND_SCC_UART1_BCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_UART1_BCR_ADDR, HWIO_LPASS_ISLAND_SCC_UART1_BCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_UART1_BCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_UART1_BCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_UART1_BCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_UART1_BCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_UART1_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_UART1_BCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_UART1_BCR_IN)
#define HWIO_LPASS_ISLAND_SCC_UART1_BCR_BLK_ARES_BMSK                                                                        0x1
#define HWIO_LPASS_ISLAND_SCC_UART1_BCR_BLK_ARES_SHFT                                                                        0x0

#define HWIO_LPASS_SCC_UART1_CMD_RCGR_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x00043004)
#define HWIO_LPASS_SCC_UART1_CMD_RCGR_OFFS                                                                            (LPASS_CC_REG_BASE_OFFS + 0x00043004)
#define HWIO_LPASS_SCC_UART1_CMD_RCGR_RMSK                                                                            0x800000f3
#define HWIO_LPASS_SCC_UART1_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_SCC_UART1_CMD_RCGR_ADDR, HWIO_LPASS_SCC_UART1_CMD_RCGR_RMSK)
#define HWIO_LPASS_SCC_UART1_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_UART1_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_SCC_UART1_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_UART1_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_SCC_UART1_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_UART1_CMD_RCGR_ADDR,m,v,HWIO_LPASS_SCC_UART1_CMD_RCGR_IN)
#define HWIO_LPASS_SCC_UART1_CMD_RCGR_ROOT_OFF_BMSK                                                                   0x80000000
#define HWIO_LPASS_SCC_UART1_CMD_RCGR_ROOT_OFF_SHFT                                                                         0x1f
#define HWIO_LPASS_SCC_UART1_CMD_RCGR_DIRTY_D_BMSK                                                                          0x80
#define HWIO_LPASS_SCC_UART1_CMD_RCGR_DIRTY_D_SHFT                                                                           0x7
#define HWIO_LPASS_SCC_UART1_CMD_RCGR_DIRTY_N_BMSK                                                                          0x40
#define HWIO_LPASS_SCC_UART1_CMD_RCGR_DIRTY_N_SHFT                                                                           0x6
#define HWIO_LPASS_SCC_UART1_CMD_RCGR_DIRTY_M_BMSK                                                                          0x20
#define HWIO_LPASS_SCC_UART1_CMD_RCGR_DIRTY_M_SHFT                                                                           0x5
#define HWIO_LPASS_SCC_UART1_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                   0x10
#define HWIO_LPASS_SCC_UART1_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                    0x4
#define HWIO_LPASS_SCC_UART1_CMD_RCGR_ROOT_EN_BMSK                                                                           0x2
#define HWIO_LPASS_SCC_UART1_CMD_RCGR_ROOT_EN_SHFT                                                                           0x1
#define HWIO_LPASS_SCC_UART1_CMD_RCGR_UPDATE_BMSK                                                                            0x1
#define HWIO_LPASS_SCC_UART1_CMD_RCGR_UPDATE_SHFT                                                                            0x0

#define HWIO_LPASS_SCC_UART1_CFG_RCGR_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x00043008)
#define HWIO_LPASS_SCC_UART1_CFG_RCGR_OFFS                                                                            (LPASS_CC_REG_BASE_OFFS + 0x00043008)
#define HWIO_LPASS_SCC_UART1_CFG_RCGR_RMSK                                                                                0x771f
#define HWIO_LPASS_SCC_UART1_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_SCC_UART1_CFG_RCGR_ADDR, HWIO_LPASS_SCC_UART1_CFG_RCGR_RMSK)
#define HWIO_LPASS_SCC_UART1_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_UART1_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_SCC_UART1_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_UART1_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_SCC_UART1_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_UART1_CFG_RCGR_ADDR,m,v,HWIO_LPASS_SCC_UART1_CFG_RCGR_IN)
#define HWIO_LPASS_SCC_UART1_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                    0x4000
#define HWIO_LPASS_SCC_UART1_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                       0xe
#define HWIO_LPASS_SCC_UART1_CFG_RCGR_MODE_BMSK                                                                           0x3000
#define HWIO_LPASS_SCC_UART1_CFG_RCGR_MODE_SHFT                                                                              0xc
#define HWIO_LPASS_SCC_UART1_CFG_RCGR_SRC_SEL_BMSK                                                                         0x700
#define HWIO_LPASS_SCC_UART1_CFG_RCGR_SRC_SEL_SHFT                                                                           0x8
#define HWIO_LPASS_SCC_UART1_CFG_RCGR_SRC_DIV_BMSK                                                                          0x1f
#define HWIO_LPASS_SCC_UART1_CFG_RCGR_SRC_DIV_SHFT                                                                           0x0

#define HWIO_LPASS_SCC_UART1_M_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x0004300c)
#define HWIO_LPASS_SCC_UART1_M_OFFS                                                                                   (LPASS_CC_REG_BASE_OFFS + 0x0004300c)
#define HWIO_LPASS_SCC_UART1_M_RMSK                                                                                       0xffff
#define HWIO_LPASS_SCC_UART1_M_IN          \
        in_dword_masked(HWIO_LPASS_SCC_UART1_M_ADDR, HWIO_LPASS_SCC_UART1_M_RMSK)
#define HWIO_LPASS_SCC_UART1_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_UART1_M_ADDR, m)
#define HWIO_LPASS_SCC_UART1_M_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_UART1_M_ADDR,v)
#define HWIO_LPASS_SCC_UART1_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_UART1_M_ADDR,m,v,HWIO_LPASS_SCC_UART1_M_IN)
#define HWIO_LPASS_SCC_UART1_M_M_BMSK                                                                                     0xffff
#define HWIO_LPASS_SCC_UART1_M_M_SHFT                                                                                        0x0

#define HWIO_LPASS_SCC_UART1_N_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x00043010)
#define HWIO_LPASS_SCC_UART1_N_OFFS                                                                                   (LPASS_CC_REG_BASE_OFFS + 0x00043010)
#define HWIO_LPASS_SCC_UART1_N_RMSK                                                                                       0xffff
#define HWIO_LPASS_SCC_UART1_N_IN          \
        in_dword_masked(HWIO_LPASS_SCC_UART1_N_ADDR, HWIO_LPASS_SCC_UART1_N_RMSK)
#define HWIO_LPASS_SCC_UART1_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_UART1_N_ADDR, m)
#define HWIO_LPASS_SCC_UART1_N_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_UART1_N_ADDR,v)
#define HWIO_LPASS_SCC_UART1_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_UART1_N_ADDR,m,v,HWIO_LPASS_SCC_UART1_N_IN)
#define HWIO_LPASS_SCC_UART1_N_NOT_N_MINUS_M_BMSK                                                                         0xffff
#define HWIO_LPASS_SCC_UART1_N_NOT_N_MINUS_M_SHFT                                                                            0x0

#define HWIO_LPASS_SCC_UART1_D_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x00043014)
#define HWIO_LPASS_SCC_UART1_D_OFFS                                                                                   (LPASS_CC_REG_BASE_OFFS + 0x00043014)
#define HWIO_LPASS_SCC_UART1_D_RMSK                                                                                       0xffff
#define HWIO_LPASS_SCC_UART1_D_IN          \
        in_dword_masked(HWIO_LPASS_SCC_UART1_D_ADDR, HWIO_LPASS_SCC_UART1_D_RMSK)
#define HWIO_LPASS_SCC_UART1_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_UART1_D_ADDR, m)
#define HWIO_LPASS_SCC_UART1_D_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_UART1_D_ADDR,v)
#define HWIO_LPASS_SCC_UART1_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_UART1_D_ADDR,m,v,HWIO_LPASS_SCC_UART1_D_IN)
#define HWIO_LPASS_SCC_UART1_D_NOT_2D_BMSK                                                                                0xffff
#define HWIO_LPASS_SCC_UART1_D_NOT_2D_SHFT                                                                                   0x0

#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART1_CBCR_ADDR                                                                 (LPASS_CC_REG_BASE      + 0x00043018)
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART1_CBCR_OFFS                                                                 (LPASS_CC_REG_BASE_OFFS + 0x00043018)
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART1_CBCR_RMSK                                                                 0x80000001
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART1_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_UART_DM_UART1_CBCR_ADDR, HWIO_LPASS_ISLAND_SCC_UART_DM_UART1_CBCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART1_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_UART_DM_UART1_CBCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART1_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_UART_DM_UART1_CBCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART1_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_UART_DM_UART1_CBCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_UART_DM_UART1_CBCR_IN)
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART1_CBCR_CLK_OFF_BMSK                                                         0x80000000
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART1_CBCR_CLK_OFF_SHFT                                                               0x1f
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART1_CBCR_CLK_ENABLE_BMSK                                                             0x1
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART1_CBCR_CLK_ENABLE_SHFT                                                             0x0

#define HWIO_LPASS_ISLAND_SCC_UART2_BCR_ADDR                                                                          (LPASS_CC_REG_BASE      + 0x00044000)
#define HWIO_LPASS_ISLAND_SCC_UART2_BCR_OFFS                                                                          (LPASS_CC_REG_BASE_OFFS + 0x00044000)
#define HWIO_LPASS_ISLAND_SCC_UART2_BCR_RMSK                                                                                 0x1
#define HWIO_LPASS_ISLAND_SCC_UART2_BCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_UART2_BCR_ADDR, HWIO_LPASS_ISLAND_SCC_UART2_BCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_UART2_BCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_UART2_BCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_UART2_BCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_UART2_BCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_UART2_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_UART2_BCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_UART2_BCR_IN)
#define HWIO_LPASS_ISLAND_SCC_UART2_BCR_BLK_ARES_BMSK                                                                        0x1
#define HWIO_LPASS_ISLAND_SCC_UART2_BCR_BLK_ARES_SHFT                                                                        0x0

#define HWIO_LPASS_SCC_UART2_CMD_RCGR_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x00044004)
#define HWIO_LPASS_SCC_UART2_CMD_RCGR_OFFS                                                                            (LPASS_CC_REG_BASE_OFFS + 0x00044004)
#define HWIO_LPASS_SCC_UART2_CMD_RCGR_RMSK                                                                            0x800000f3
#define HWIO_LPASS_SCC_UART2_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_SCC_UART2_CMD_RCGR_ADDR, HWIO_LPASS_SCC_UART2_CMD_RCGR_RMSK)
#define HWIO_LPASS_SCC_UART2_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_UART2_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_SCC_UART2_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_UART2_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_SCC_UART2_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_UART2_CMD_RCGR_ADDR,m,v,HWIO_LPASS_SCC_UART2_CMD_RCGR_IN)
#define HWIO_LPASS_SCC_UART2_CMD_RCGR_ROOT_OFF_BMSK                                                                   0x80000000
#define HWIO_LPASS_SCC_UART2_CMD_RCGR_ROOT_OFF_SHFT                                                                         0x1f
#define HWIO_LPASS_SCC_UART2_CMD_RCGR_DIRTY_D_BMSK                                                                          0x80
#define HWIO_LPASS_SCC_UART2_CMD_RCGR_DIRTY_D_SHFT                                                                           0x7
#define HWIO_LPASS_SCC_UART2_CMD_RCGR_DIRTY_N_BMSK                                                                          0x40
#define HWIO_LPASS_SCC_UART2_CMD_RCGR_DIRTY_N_SHFT                                                                           0x6
#define HWIO_LPASS_SCC_UART2_CMD_RCGR_DIRTY_M_BMSK                                                                          0x20
#define HWIO_LPASS_SCC_UART2_CMD_RCGR_DIRTY_M_SHFT                                                                           0x5
#define HWIO_LPASS_SCC_UART2_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                   0x10
#define HWIO_LPASS_SCC_UART2_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                    0x4
#define HWIO_LPASS_SCC_UART2_CMD_RCGR_ROOT_EN_BMSK                                                                           0x2
#define HWIO_LPASS_SCC_UART2_CMD_RCGR_ROOT_EN_SHFT                                                                           0x1
#define HWIO_LPASS_SCC_UART2_CMD_RCGR_UPDATE_BMSK                                                                            0x1
#define HWIO_LPASS_SCC_UART2_CMD_RCGR_UPDATE_SHFT                                                                            0x0

#define HWIO_LPASS_SCC_UART2_CFG_RCGR_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x00044008)
#define HWIO_LPASS_SCC_UART2_CFG_RCGR_OFFS                                                                            (LPASS_CC_REG_BASE_OFFS + 0x00044008)
#define HWIO_LPASS_SCC_UART2_CFG_RCGR_RMSK                                                                                0x771f
#define HWIO_LPASS_SCC_UART2_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_SCC_UART2_CFG_RCGR_ADDR, HWIO_LPASS_SCC_UART2_CFG_RCGR_RMSK)
#define HWIO_LPASS_SCC_UART2_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_UART2_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_SCC_UART2_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_UART2_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_SCC_UART2_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_UART2_CFG_RCGR_ADDR,m,v,HWIO_LPASS_SCC_UART2_CFG_RCGR_IN)
#define HWIO_LPASS_SCC_UART2_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                    0x4000
#define HWIO_LPASS_SCC_UART2_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                       0xe
#define HWIO_LPASS_SCC_UART2_CFG_RCGR_MODE_BMSK                                                                           0x3000
#define HWIO_LPASS_SCC_UART2_CFG_RCGR_MODE_SHFT                                                                              0xc
#define HWIO_LPASS_SCC_UART2_CFG_RCGR_SRC_SEL_BMSK                                                                         0x700
#define HWIO_LPASS_SCC_UART2_CFG_RCGR_SRC_SEL_SHFT                                                                           0x8
#define HWIO_LPASS_SCC_UART2_CFG_RCGR_SRC_DIV_BMSK                                                                          0x1f
#define HWIO_LPASS_SCC_UART2_CFG_RCGR_SRC_DIV_SHFT                                                                           0x0

#define HWIO_LPASS_SCC_UART2_M_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x0004400c)
#define HWIO_LPASS_SCC_UART2_M_OFFS                                                                                   (LPASS_CC_REG_BASE_OFFS + 0x0004400c)
#define HWIO_LPASS_SCC_UART2_M_RMSK                                                                                       0xffff
#define HWIO_LPASS_SCC_UART2_M_IN          \
        in_dword_masked(HWIO_LPASS_SCC_UART2_M_ADDR, HWIO_LPASS_SCC_UART2_M_RMSK)
#define HWIO_LPASS_SCC_UART2_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_UART2_M_ADDR, m)
#define HWIO_LPASS_SCC_UART2_M_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_UART2_M_ADDR,v)
#define HWIO_LPASS_SCC_UART2_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_UART2_M_ADDR,m,v,HWIO_LPASS_SCC_UART2_M_IN)
#define HWIO_LPASS_SCC_UART2_M_M_BMSK                                                                                     0xffff
#define HWIO_LPASS_SCC_UART2_M_M_SHFT                                                                                        0x0

#define HWIO_LPASS_SCC_UART2_N_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x00044010)
#define HWIO_LPASS_SCC_UART2_N_OFFS                                                                                   (LPASS_CC_REG_BASE_OFFS + 0x00044010)
#define HWIO_LPASS_SCC_UART2_N_RMSK                                                                                       0xffff
#define HWIO_LPASS_SCC_UART2_N_IN          \
        in_dword_masked(HWIO_LPASS_SCC_UART2_N_ADDR, HWIO_LPASS_SCC_UART2_N_RMSK)
#define HWIO_LPASS_SCC_UART2_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_UART2_N_ADDR, m)
#define HWIO_LPASS_SCC_UART2_N_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_UART2_N_ADDR,v)
#define HWIO_LPASS_SCC_UART2_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_UART2_N_ADDR,m,v,HWIO_LPASS_SCC_UART2_N_IN)
#define HWIO_LPASS_SCC_UART2_N_NOT_N_MINUS_M_BMSK                                                                         0xffff
#define HWIO_LPASS_SCC_UART2_N_NOT_N_MINUS_M_SHFT                                                                            0x0

#define HWIO_LPASS_SCC_UART2_D_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x00044014)
#define HWIO_LPASS_SCC_UART2_D_OFFS                                                                                   (LPASS_CC_REG_BASE_OFFS + 0x00044014)
#define HWIO_LPASS_SCC_UART2_D_RMSK                                                                                       0xffff
#define HWIO_LPASS_SCC_UART2_D_IN          \
        in_dword_masked(HWIO_LPASS_SCC_UART2_D_ADDR, HWIO_LPASS_SCC_UART2_D_RMSK)
#define HWIO_LPASS_SCC_UART2_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_UART2_D_ADDR, m)
#define HWIO_LPASS_SCC_UART2_D_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_UART2_D_ADDR,v)
#define HWIO_LPASS_SCC_UART2_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_UART2_D_ADDR,m,v,HWIO_LPASS_SCC_UART2_D_IN)
#define HWIO_LPASS_SCC_UART2_D_NOT_2D_BMSK                                                                                0xffff
#define HWIO_LPASS_SCC_UART2_D_NOT_2D_SHFT                                                                                   0x0

#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART2_CBCR_ADDR                                                                 (LPASS_CC_REG_BASE      + 0x00044018)
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART2_CBCR_OFFS                                                                 (LPASS_CC_REG_BASE_OFFS + 0x00044018)
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART2_CBCR_RMSK                                                                 0x80000001
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART2_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_UART_DM_UART2_CBCR_ADDR, HWIO_LPASS_ISLAND_SCC_UART_DM_UART2_CBCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART2_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_UART_DM_UART2_CBCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART2_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_UART_DM_UART2_CBCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART2_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_UART_DM_UART2_CBCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_UART_DM_UART2_CBCR_IN)
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART2_CBCR_CLK_OFF_BMSK                                                         0x80000000
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART2_CBCR_CLK_OFF_SHFT                                                               0x1f
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART2_CBCR_CLK_ENABLE_BMSK                                                             0x1
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART2_CBCR_CLK_ENABLE_SHFT                                                             0x0

#define HWIO_LPASS_ISLAND_SCC_UART3_BCR_ADDR                                                                          (LPASS_CC_REG_BASE      + 0x00045000)
#define HWIO_LPASS_ISLAND_SCC_UART3_BCR_OFFS                                                                          (LPASS_CC_REG_BASE_OFFS + 0x00045000)
#define HWIO_LPASS_ISLAND_SCC_UART3_BCR_RMSK                                                                                 0x1
#define HWIO_LPASS_ISLAND_SCC_UART3_BCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_UART3_BCR_ADDR, HWIO_LPASS_ISLAND_SCC_UART3_BCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_UART3_BCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_UART3_BCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_UART3_BCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_UART3_BCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_UART3_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_UART3_BCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_UART3_BCR_IN)
#define HWIO_LPASS_ISLAND_SCC_UART3_BCR_BLK_ARES_BMSK                                                                        0x1
#define HWIO_LPASS_ISLAND_SCC_UART3_BCR_BLK_ARES_SHFT                                                                        0x0

#define HWIO_LPASS_SCC_UART3_CMD_RCGR_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x00045004)
#define HWIO_LPASS_SCC_UART3_CMD_RCGR_OFFS                                                                            (LPASS_CC_REG_BASE_OFFS + 0x00045004)
#define HWIO_LPASS_SCC_UART3_CMD_RCGR_RMSK                                                                            0x800000f3
#define HWIO_LPASS_SCC_UART3_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_SCC_UART3_CMD_RCGR_ADDR, HWIO_LPASS_SCC_UART3_CMD_RCGR_RMSK)
#define HWIO_LPASS_SCC_UART3_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_UART3_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_SCC_UART3_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_UART3_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_SCC_UART3_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_UART3_CMD_RCGR_ADDR,m,v,HWIO_LPASS_SCC_UART3_CMD_RCGR_IN)
#define HWIO_LPASS_SCC_UART3_CMD_RCGR_ROOT_OFF_BMSK                                                                   0x80000000
#define HWIO_LPASS_SCC_UART3_CMD_RCGR_ROOT_OFF_SHFT                                                                         0x1f
#define HWIO_LPASS_SCC_UART3_CMD_RCGR_DIRTY_D_BMSK                                                                          0x80
#define HWIO_LPASS_SCC_UART3_CMD_RCGR_DIRTY_D_SHFT                                                                           0x7
#define HWIO_LPASS_SCC_UART3_CMD_RCGR_DIRTY_N_BMSK                                                                          0x40
#define HWIO_LPASS_SCC_UART3_CMD_RCGR_DIRTY_N_SHFT                                                                           0x6
#define HWIO_LPASS_SCC_UART3_CMD_RCGR_DIRTY_M_BMSK                                                                          0x20
#define HWIO_LPASS_SCC_UART3_CMD_RCGR_DIRTY_M_SHFT                                                                           0x5
#define HWIO_LPASS_SCC_UART3_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                   0x10
#define HWIO_LPASS_SCC_UART3_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                    0x4
#define HWIO_LPASS_SCC_UART3_CMD_RCGR_ROOT_EN_BMSK                                                                           0x2
#define HWIO_LPASS_SCC_UART3_CMD_RCGR_ROOT_EN_SHFT                                                                           0x1
#define HWIO_LPASS_SCC_UART3_CMD_RCGR_UPDATE_BMSK                                                                            0x1
#define HWIO_LPASS_SCC_UART3_CMD_RCGR_UPDATE_SHFT                                                                            0x0

#define HWIO_LPASS_SCC_UART3_CFG_RCGR_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x00045008)
#define HWIO_LPASS_SCC_UART3_CFG_RCGR_OFFS                                                                            (LPASS_CC_REG_BASE_OFFS + 0x00045008)
#define HWIO_LPASS_SCC_UART3_CFG_RCGR_RMSK                                                                                0x771f
#define HWIO_LPASS_SCC_UART3_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_SCC_UART3_CFG_RCGR_ADDR, HWIO_LPASS_SCC_UART3_CFG_RCGR_RMSK)
#define HWIO_LPASS_SCC_UART3_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_UART3_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_SCC_UART3_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_UART3_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_SCC_UART3_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_UART3_CFG_RCGR_ADDR,m,v,HWIO_LPASS_SCC_UART3_CFG_RCGR_IN)
#define HWIO_LPASS_SCC_UART3_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                    0x4000
#define HWIO_LPASS_SCC_UART3_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                       0xe
#define HWIO_LPASS_SCC_UART3_CFG_RCGR_MODE_BMSK                                                                           0x3000
#define HWIO_LPASS_SCC_UART3_CFG_RCGR_MODE_SHFT                                                                              0xc
#define HWIO_LPASS_SCC_UART3_CFG_RCGR_SRC_SEL_BMSK                                                                         0x700
#define HWIO_LPASS_SCC_UART3_CFG_RCGR_SRC_SEL_SHFT                                                                           0x8
#define HWIO_LPASS_SCC_UART3_CFG_RCGR_SRC_DIV_BMSK                                                                          0x1f
#define HWIO_LPASS_SCC_UART3_CFG_RCGR_SRC_DIV_SHFT                                                                           0x0

#define HWIO_LPASS_SCC_UART3_M_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x0004500c)
#define HWIO_LPASS_SCC_UART3_M_OFFS                                                                                   (LPASS_CC_REG_BASE_OFFS + 0x0004500c)
#define HWIO_LPASS_SCC_UART3_M_RMSK                                                                                       0xffff
#define HWIO_LPASS_SCC_UART3_M_IN          \
        in_dword_masked(HWIO_LPASS_SCC_UART3_M_ADDR, HWIO_LPASS_SCC_UART3_M_RMSK)
#define HWIO_LPASS_SCC_UART3_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_UART3_M_ADDR, m)
#define HWIO_LPASS_SCC_UART3_M_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_UART3_M_ADDR,v)
#define HWIO_LPASS_SCC_UART3_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_UART3_M_ADDR,m,v,HWIO_LPASS_SCC_UART3_M_IN)
#define HWIO_LPASS_SCC_UART3_M_M_BMSK                                                                                     0xffff
#define HWIO_LPASS_SCC_UART3_M_M_SHFT                                                                                        0x0

#define HWIO_LPASS_SCC_UART3_N_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x00045010)
#define HWIO_LPASS_SCC_UART3_N_OFFS                                                                                   (LPASS_CC_REG_BASE_OFFS + 0x00045010)
#define HWIO_LPASS_SCC_UART3_N_RMSK                                                                                       0xffff
#define HWIO_LPASS_SCC_UART3_N_IN          \
        in_dword_masked(HWIO_LPASS_SCC_UART3_N_ADDR, HWIO_LPASS_SCC_UART3_N_RMSK)
#define HWIO_LPASS_SCC_UART3_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_UART3_N_ADDR, m)
#define HWIO_LPASS_SCC_UART3_N_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_UART3_N_ADDR,v)
#define HWIO_LPASS_SCC_UART3_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_UART3_N_ADDR,m,v,HWIO_LPASS_SCC_UART3_N_IN)
#define HWIO_LPASS_SCC_UART3_N_NOT_N_MINUS_M_BMSK                                                                         0xffff
#define HWIO_LPASS_SCC_UART3_N_NOT_N_MINUS_M_SHFT                                                                            0x0

#define HWIO_LPASS_SCC_UART3_D_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x00045014)
#define HWIO_LPASS_SCC_UART3_D_OFFS                                                                                   (LPASS_CC_REG_BASE_OFFS + 0x00045014)
#define HWIO_LPASS_SCC_UART3_D_RMSK                                                                                       0xffff
#define HWIO_LPASS_SCC_UART3_D_IN          \
        in_dword_masked(HWIO_LPASS_SCC_UART3_D_ADDR, HWIO_LPASS_SCC_UART3_D_RMSK)
#define HWIO_LPASS_SCC_UART3_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_UART3_D_ADDR, m)
#define HWIO_LPASS_SCC_UART3_D_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_UART3_D_ADDR,v)
#define HWIO_LPASS_SCC_UART3_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_UART3_D_ADDR,m,v,HWIO_LPASS_SCC_UART3_D_IN)
#define HWIO_LPASS_SCC_UART3_D_NOT_2D_BMSK                                                                                0xffff
#define HWIO_LPASS_SCC_UART3_D_NOT_2D_SHFT                                                                                   0x0

#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART3_CBCR_ADDR                                                                 (LPASS_CC_REG_BASE      + 0x00045018)
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART3_CBCR_OFFS                                                                 (LPASS_CC_REG_BASE_OFFS + 0x00045018)
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART3_CBCR_RMSK                                                                 0x80000001
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART3_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_UART_DM_UART3_CBCR_ADDR, HWIO_LPASS_ISLAND_SCC_UART_DM_UART3_CBCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART3_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_UART_DM_UART3_CBCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART3_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_UART_DM_UART3_CBCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART3_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_UART_DM_UART3_CBCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_UART_DM_UART3_CBCR_IN)
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART3_CBCR_CLK_OFF_BMSK                                                         0x80000000
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART3_CBCR_CLK_OFF_SHFT                                                               0x1f
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART3_CBCR_CLK_ENABLE_BMSK                                                             0x1
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART3_CBCR_CLK_ENABLE_SHFT                                                             0x0

#define HWIO_LPASS_ISLAND_SCC_BUS_BCR_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x00046000)
#define HWIO_LPASS_ISLAND_SCC_BUS_BCR_OFFS                                                                            (LPASS_CC_REG_BASE_OFFS + 0x00046000)
#define HWIO_LPASS_ISLAND_SCC_BUS_BCR_RMSK                                                                                   0x1
#define HWIO_LPASS_ISLAND_SCC_BUS_BCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_BUS_BCR_ADDR, HWIO_LPASS_ISLAND_SCC_BUS_BCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_BUS_BCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_BUS_BCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_BUS_BCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_BUS_BCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_BUS_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_BUS_BCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_BUS_BCR_IN)
#define HWIO_LPASS_ISLAND_SCC_BUS_BCR_BLK_ARES_BMSK                                                                          0x1
#define HWIO_LPASS_ISLAND_SCC_BUS_BCR_BLK_ARES_SHFT                                                                          0x0

#define HWIO_LPASS_ISLAND_SCC_BUS_CLK_CDIV_REG_ADDR                                                                   (LPASS_CC_REG_BASE      + 0x00046004)
#define HWIO_LPASS_ISLAND_SCC_BUS_CLK_CDIV_REG_OFFS                                                                   (LPASS_CC_REG_BASE_OFFS + 0x00046004)
#define HWIO_LPASS_ISLAND_SCC_BUS_CLK_CDIV_REG_RMSK                                                                      0x70000
#define HWIO_LPASS_ISLAND_SCC_BUS_CLK_CDIV_REG_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_BUS_CLK_CDIV_REG_ADDR, HWIO_LPASS_ISLAND_SCC_BUS_CLK_CDIV_REG_RMSK)
#define HWIO_LPASS_ISLAND_SCC_BUS_CLK_CDIV_REG_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_BUS_CLK_CDIV_REG_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_BUS_CLK_CDIV_REG_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_BUS_CLK_CDIV_REG_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_BUS_CLK_CDIV_REG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_BUS_CLK_CDIV_REG_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_BUS_CLK_CDIV_REG_IN)
#define HWIO_LPASS_ISLAND_SCC_BUS_CLK_CDIV_REG_CLK_DIV_BMSK                                                              0x70000
#define HWIO_LPASS_ISLAND_SCC_BUS_CLK_CDIV_REG_CLK_DIV_SHFT                                                                 0x10

#define HWIO_LPASS_ISLAND_SCC_CRIF_AON_CBCR_ADDR                                                                      (LPASS_CC_REG_BASE      + 0x00046008)
#define HWIO_LPASS_ISLAND_SCC_CRIF_AON_CBCR_OFFS                                                                      (LPASS_CC_REG_BASE_OFFS + 0x00046008)
#define HWIO_LPASS_ISLAND_SCC_CRIF_AON_CBCR_RMSK                                                                      0x80000000
#define HWIO_LPASS_ISLAND_SCC_CRIF_AON_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_CRIF_AON_CBCR_ADDR, HWIO_LPASS_ISLAND_SCC_CRIF_AON_CBCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_CRIF_AON_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_CRIF_AON_CBCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_CRIF_AON_CBCR_CLK_OFF_BMSK                                                              0x80000000
#define HWIO_LPASS_ISLAND_SCC_CRIF_AON_CBCR_CLK_OFF_SHFT                                                                    0x1f

#define HWIO_LPASS_ISLAND_SCC_CSR_H_AON_CBCR_ADDR                                                                     (LPASS_CC_REG_BASE      + 0x0004600c)
#define HWIO_LPASS_ISLAND_SCC_CSR_H_AON_CBCR_OFFS                                                                     (LPASS_CC_REG_BASE_OFFS + 0x0004600c)
#define HWIO_LPASS_ISLAND_SCC_CSR_H_AON_CBCR_RMSK                                                                     0x80000000
#define HWIO_LPASS_ISLAND_SCC_CSR_H_AON_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_CSR_H_AON_CBCR_ADDR, HWIO_LPASS_ISLAND_SCC_CSR_H_AON_CBCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_CSR_H_AON_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_CSR_H_AON_CBCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_CSR_H_AON_CBCR_CLK_OFF_BMSK                                                             0x80000000
#define HWIO_LPASS_ISLAND_SCC_CSR_H_AON_CBCR_CLK_OFF_SHFT                                                                   0x1f

#define HWIO_LPASS_ISLAND_SCC_DATA_H_AON_CBCR_ADDR                                                                    (LPASS_CC_REG_BASE      + 0x00046010)
#define HWIO_LPASS_ISLAND_SCC_DATA_H_AON_CBCR_OFFS                                                                    (LPASS_CC_REG_BASE_OFFS + 0x00046010)
#define HWIO_LPASS_ISLAND_SCC_DATA_H_AON_CBCR_RMSK                                                                    0x80000001
#define HWIO_LPASS_ISLAND_SCC_DATA_H_AON_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_DATA_H_AON_CBCR_ADDR, HWIO_LPASS_ISLAND_SCC_DATA_H_AON_CBCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_DATA_H_AON_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_DATA_H_AON_CBCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_DATA_H_AON_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_DATA_H_AON_CBCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_DATA_H_AON_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_DATA_H_AON_CBCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_DATA_H_AON_CBCR_IN)
#define HWIO_LPASS_ISLAND_SCC_DATA_H_AON_CBCR_CLK_OFF_BMSK                                                            0x80000000
#define HWIO_LPASS_ISLAND_SCC_DATA_H_AON_CBCR_CLK_OFF_SHFT                                                                  0x1f
#define HWIO_LPASS_ISLAND_SCC_DATA_H_AON_CBCR_CLK_ENABLE_BMSK                                                                0x1
#define HWIO_LPASS_ISLAND_SCC_DATA_H_AON_CBCR_CLK_ENABLE_SHFT                                                                0x0

#define HWIO_LPASS_ISLAND_SCC_CFG_AHB_AON_CBCR_ADDR                                                                   (LPASS_CC_REG_BASE      + 0x00046014)
#define HWIO_LPASS_ISLAND_SCC_CFG_AHB_AON_CBCR_OFFS                                                                   (LPASS_CC_REG_BASE_OFFS + 0x00046014)
#define HWIO_LPASS_ISLAND_SCC_CFG_AHB_AON_CBCR_RMSK                                                                   0x80000000
#define HWIO_LPASS_ISLAND_SCC_CFG_AHB_AON_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_CFG_AHB_AON_CBCR_ADDR, HWIO_LPASS_ISLAND_SCC_CFG_AHB_AON_CBCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_CFG_AHB_AON_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_CFG_AHB_AON_CBCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_CFG_AHB_AON_CBCR_CLK_OFF_BMSK                                                           0x80000000
#define HWIO_LPASS_ISLAND_SCC_CFG_AHB_AON_CBCR_CLK_OFF_SHFT                                                                 0x1f

#define HWIO_LPASS_ISLAND_SCC_Q6_AHB_BCR_ADDR                                                                         (LPASS_CC_REG_BASE      + 0x00046018)
#define HWIO_LPASS_ISLAND_SCC_Q6_AHB_BCR_OFFS                                                                         (LPASS_CC_REG_BASE_OFFS + 0x00046018)
#define HWIO_LPASS_ISLAND_SCC_Q6_AHB_BCR_RMSK                                                                                0x1
#define HWIO_LPASS_ISLAND_SCC_Q6_AHB_BCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_Q6_AHB_BCR_ADDR, HWIO_LPASS_ISLAND_SCC_Q6_AHB_BCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_Q6_AHB_BCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_Q6_AHB_BCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_Q6_AHB_BCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_Q6_AHB_BCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_Q6_AHB_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_Q6_AHB_BCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_Q6_AHB_BCR_IN)
#define HWIO_LPASS_ISLAND_SCC_Q6_AHB_BCR_BLK_ARES_BMSK                                                                       0x1
#define HWIO_LPASS_ISLAND_SCC_Q6_AHB_BCR_BLK_ARES_SHFT                                                                       0x0

#define HWIO_LPASS_ISLAND_SCC_Q6_XPU2_CONFIG_BCR_ADDR                                                                 (LPASS_CC_REG_BASE      + 0x0004601c)
#define HWIO_LPASS_ISLAND_SCC_Q6_XPU2_CONFIG_BCR_OFFS                                                                 (LPASS_CC_REG_BASE_OFFS + 0x0004601c)
#define HWIO_LPASS_ISLAND_SCC_Q6_XPU2_CONFIG_BCR_RMSK                                                                        0x1
#define HWIO_LPASS_ISLAND_SCC_Q6_XPU2_CONFIG_BCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_Q6_XPU2_CONFIG_BCR_ADDR, HWIO_LPASS_ISLAND_SCC_Q6_XPU2_CONFIG_BCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_Q6_XPU2_CONFIG_BCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_Q6_XPU2_CONFIG_BCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_Q6_XPU2_CONFIG_BCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_Q6_XPU2_CONFIG_BCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_Q6_XPU2_CONFIG_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_Q6_XPU2_CONFIG_BCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_Q6_XPU2_CONFIG_BCR_IN)
#define HWIO_LPASS_ISLAND_SCC_Q6_XPU2_CONFIG_BCR_BLK_ARES_BMSK                                                               0x1
#define HWIO_LPASS_ISLAND_SCC_Q6_XPU2_CONFIG_BCR_BLK_ARES_SHFT                                                               0x0

#define HWIO_LPASS_ISLAND_SCC_QDSP_SWAY_AON_CBCR_ADDR                                                                 (LPASS_CC_REG_BASE      + 0x00046020)
#define HWIO_LPASS_ISLAND_SCC_QDSP_SWAY_AON_CBCR_OFFS                                                                 (LPASS_CC_REG_BASE_OFFS + 0x00046020)
#define HWIO_LPASS_ISLAND_SCC_QDSP_SWAY_AON_CBCR_RMSK                                                                 0x80000000
#define HWIO_LPASS_ISLAND_SCC_QDSP_SWAY_AON_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_QDSP_SWAY_AON_CBCR_ADDR, HWIO_LPASS_ISLAND_SCC_QDSP_SWAY_AON_CBCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_QDSP_SWAY_AON_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_QDSP_SWAY_AON_CBCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_QDSP_SWAY_AON_CBCR_CLK_OFF_BMSK                                                         0x80000000
#define HWIO_LPASS_ISLAND_SCC_QDSP_SWAY_AON_CBCR_CLK_OFF_SHFT                                                               0x1f

#define HWIO_LPASS_ISLAND_SCC_BLSP_BCR_ADDR                                                                           (LPASS_CC_REG_BASE      + 0x00047000)
#define HWIO_LPASS_ISLAND_SCC_BLSP_BCR_OFFS                                                                           (LPASS_CC_REG_BASE_OFFS + 0x00047000)
#define HWIO_LPASS_ISLAND_SCC_BLSP_BCR_RMSK                                                                                  0x1
#define HWIO_LPASS_ISLAND_SCC_BLSP_BCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_BLSP_BCR_ADDR, HWIO_LPASS_ISLAND_SCC_BLSP_BCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_BLSP_BCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_BLSP_BCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_BLSP_BCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_BLSP_BCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_BLSP_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_BLSP_BCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_BLSP_BCR_IN)
#define HWIO_LPASS_ISLAND_SCC_BLSP_BCR_BLK_ARES_BMSK                                                                         0x1
#define HWIO_LPASS_ISLAND_SCC_BLSP_BCR_BLK_ARES_SHFT                                                                         0x0

#define HWIO_LPASS_ISLAND_SCC_BLSP_H_CORE_CBCR_ADDR                                                                   (LPASS_CC_REG_BASE      + 0x00047004)
#define HWIO_LPASS_ISLAND_SCC_BLSP_H_CORE_CBCR_OFFS                                                                   (LPASS_CC_REG_BASE_OFFS + 0x00047004)
#define HWIO_LPASS_ISLAND_SCC_BLSP_H_CORE_CBCR_RMSK                                                                   0x80007ff1
#define HWIO_LPASS_ISLAND_SCC_BLSP_H_CORE_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_BLSP_H_CORE_CBCR_ADDR, HWIO_LPASS_ISLAND_SCC_BLSP_H_CORE_CBCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_BLSP_H_CORE_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_BLSP_H_CORE_CBCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_BLSP_H_CORE_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_BLSP_H_CORE_CBCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_BLSP_H_CORE_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_BLSP_H_CORE_CBCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_BLSP_H_CORE_CBCR_IN)
#define HWIO_LPASS_ISLAND_SCC_BLSP_H_CORE_CBCR_CLK_OFF_BMSK                                                           0x80000000
#define HWIO_LPASS_ISLAND_SCC_BLSP_H_CORE_CBCR_CLK_OFF_SHFT                                                                 0x1f
#define HWIO_LPASS_ISLAND_SCC_BLSP_H_CORE_CBCR_FORCE_MEM_CORE_ON_BMSK                                                     0x4000
#define HWIO_LPASS_ISLAND_SCC_BLSP_H_CORE_CBCR_FORCE_MEM_CORE_ON_SHFT                                                        0xe
#define HWIO_LPASS_ISLAND_SCC_BLSP_H_CORE_CBCR_FORCE_MEM_PERIPH_ON_BMSK                                                   0x2000
#define HWIO_LPASS_ISLAND_SCC_BLSP_H_CORE_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                                      0xd
#define HWIO_LPASS_ISLAND_SCC_BLSP_H_CORE_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                                                  0x1000
#define HWIO_LPASS_ISLAND_SCC_BLSP_H_CORE_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                                     0xc
#define HWIO_LPASS_ISLAND_SCC_BLSP_H_CORE_CBCR_WAKEUP_BMSK                                                                 0xf00
#define HWIO_LPASS_ISLAND_SCC_BLSP_H_CORE_CBCR_WAKEUP_SHFT                                                                   0x8
#define HWIO_LPASS_ISLAND_SCC_BLSP_H_CORE_CBCR_SLEEP_BMSK                                                                   0xf0
#define HWIO_LPASS_ISLAND_SCC_BLSP_H_CORE_CBCR_SLEEP_SHFT                                                                    0x4
#define HWIO_LPASS_ISLAND_SCC_BLSP_H_CORE_CBCR_CLK_ENABLE_BMSK                                                               0x1
#define HWIO_LPASS_ISLAND_SCC_BLSP_H_CORE_CBCR_CLK_ENABLE_SHFT                                                               0x0

#define HWIO_LPASS_ISLAND_SCC_SMEM_BCR_ADDR                                                                           (LPASS_CC_REG_BASE      + 0x00047008)
#define HWIO_LPASS_ISLAND_SCC_SMEM_BCR_OFFS                                                                           (LPASS_CC_REG_BASE_OFFS + 0x00047008)
#define HWIO_LPASS_ISLAND_SCC_SMEM_BCR_RMSK                                                                                  0x1
#define HWIO_LPASS_ISLAND_SCC_SMEM_BCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_SMEM_BCR_ADDR, HWIO_LPASS_ISLAND_SCC_SMEM_BCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_SMEM_BCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_SMEM_BCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_SMEM_BCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_SMEM_BCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_SMEM_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_SMEM_BCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_SMEM_BCR_IN)
#define HWIO_LPASS_ISLAND_SCC_SMEM_BCR_BLK_ARES_BMSK                                                                         0x1
#define HWIO_LPASS_ISLAND_SCC_SMEM_BCR_BLK_ARES_SHFT                                                                         0x0

#define HWIO_LPASS_ISLAND_SCC_SMEM_CORE_CBCR_ADDR                                                                     (LPASS_CC_REG_BASE      + 0x0004700c)
#define HWIO_LPASS_ISLAND_SCC_SMEM_CORE_CBCR_OFFS                                                                     (LPASS_CC_REG_BASE_OFFS + 0x0004700c)
#define HWIO_LPASS_ISLAND_SCC_SMEM_CORE_CBCR_RMSK                                                                     0x80007ff1
#define HWIO_LPASS_ISLAND_SCC_SMEM_CORE_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_SMEM_CORE_CBCR_ADDR, HWIO_LPASS_ISLAND_SCC_SMEM_CORE_CBCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_SMEM_CORE_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_SMEM_CORE_CBCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_SMEM_CORE_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_SMEM_CORE_CBCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_SMEM_CORE_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_SMEM_CORE_CBCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_SMEM_CORE_CBCR_IN)
#define HWIO_LPASS_ISLAND_SCC_SMEM_CORE_CBCR_CLK_OFF_BMSK                                                             0x80000000
#define HWIO_LPASS_ISLAND_SCC_SMEM_CORE_CBCR_CLK_OFF_SHFT                                                                   0x1f
#define HWIO_LPASS_ISLAND_SCC_SMEM_CORE_CBCR_FORCE_MEM_CORE_ON_BMSK                                                       0x4000
#define HWIO_LPASS_ISLAND_SCC_SMEM_CORE_CBCR_FORCE_MEM_CORE_ON_SHFT                                                          0xe
#define HWIO_LPASS_ISLAND_SCC_SMEM_CORE_CBCR_FORCE_MEM_PERIPH_ON_BMSK                                                     0x2000
#define HWIO_LPASS_ISLAND_SCC_SMEM_CORE_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                                        0xd
#define HWIO_LPASS_ISLAND_SCC_SMEM_CORE_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                                                    0x1000
#define HWIO_LPASS_ISLAND_SCC_SMEM_CORE_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                                       0xc
#define HWIO_LPASS_ISLAND_SCC_SMEM_CORE_CBCR_WAKEUP_BMSK                                                                   0xf00
#define HWIO_LPASS_ISLAND_SCC_SMEM_CORE_CBCR_WAKEUP_SHFT                                                                     0x8
#define HWIO_LPASS_ISLAND_SCC_SMEM_CORE_CBCR_SLEEP_BMSK                                                                     0xf0
#define HWIO_LPASS_ISLAND_SCC_SMEM_CORE_CBCR_SLEEP_SHFT                                                                      0x4
#define HWIO_LPASS_ISLAND_SCC_SMEM_CORE_CBCR_CLK_ENABLE_BMSK                                                                 0x1
#define HWIO_LPASS_ISLAND_SCC_SMEM_CORE_CBCR_CLK_ENABLE_SHFT                                                                 0x0

#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM0_CORE_CBCR_ADDR                                                                (LPASS_CC_REG_BASE      + 0x00047010)
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM0_CORE_CBCR_OFFS                                                                (LPASS_CC_REG_BASE_OFFS + 0x00047010)
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM0_CORE_CBCR_RMSK                                                                0x80007ff3
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM0_CORE_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_SMEM_MEM0_CORE_CBCR_ADDR, HWIO_LPASS_ISLAND_SCC_SMEM_MEM0_CORE_CBCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM0_CORE_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_SMEM_MEM0_CORE_CBCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM0_CORE_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_SMEM_MEM0_CORE_CBCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM0_CORE_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_SMEM_MEM0_CORE_CBCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_SMEM_MEM0_CORE_CBCR_IN)
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM0_CORE_CBCR_CLK_OFF_BMSK                                                        0x80000000
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM0_CORE_CBCR_CLK_OFF_SHFT                                                              0x1f
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM0_CORE_CBCR_FORCE_MEM_CORE_ON_BMSK                                                  0x4000
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM0_CORE_CBCR_FORCE_MEM_CORE_ON_SHFT                                                     0xe
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM0_CORE_CBCR_FORCE_MEM_PERIPH_ON_BMSK                                                0x2000
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM0_CORE_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                                   0xd
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM0_CORE_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                                               0x1000
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM0_CORE_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                                  0xc
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM0_CORE_CBCR_WAKEUP_BMSK                                                              0xf00
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM0_CORE_CBCR_WAKEUP_SHFT                                                                0x8
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM0_CORE_CBCR_SLEEP_BMSK                                                                0xf0
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM0_CORE_CBCR_SLEEP_SHFT                                                                 0x4
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM0_CORE_CBCR_HW_CTL_BMSK                                                                0x2
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM0_CORE_CBCR_HW_CTL_SHFT                                                                0x1
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM0_CORE_CBCR_CLK_ENABLE_BMSK                                                            0x1
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM0_CORE_CBCR_CLK_ENABLE_SHFT                                                            0x0

#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM1_CORE_CBCR_ADDR                                                                (LPASS_CC_REG_BASE      + 0x00047014)
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM1_CORE_CBCR_OFFS                                                                (LPASS_CC_REG_BASE_OFFS + 0x00047014)
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM1_CORE_CBCR_RMSK                                                                0x80007ff3
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM1_CORE_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_SMEM_MEM1_CORE_CBCR_ADDR, HWIO_LPASS_ISLAND_SCC_SMEM_MEM1_CORE_CBCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM1_CORE_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_SMEM_MEM1_CORE_CBCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM1_CORE_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_SMEM_MEM1_CORE_CBCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM1_CORE_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_SMEM_MEM1_CORE_CBCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_SMEM_MEM1_CORE_CBCR_IN)
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM1_CORE_CBCR_CLK_OFF_BMSK                                                        0x80000000
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM1_CORE_CBCR_CLK_OFF_SHFT                                                              0x1f
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM1_CORE_CBCR_FORCE_MEM_CORE_ON_BMSK                                                  0x4000
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM1_CORE_CBCR_FORCE_MEM_CORE_ON_SHFT                                                     0xe
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM1_CORE_CBCR_FORCE_MEM_PERIPH_ON_BMSK                                                0x2000
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM1_CORE_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                                   0xd
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM1_CORE_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                                               0x1000
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM1_CORE_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                                  0xc
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM1_CORE_CBCR_WAKEUP_BMSK                                                              0xf00
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM1_CORE_CBCR_WAKEUP_SHFT                                                                0x8
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM1_CORE_CBCR_SLEEP_BMSK                                                                0xf0
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM1_CORE_CBCR_SLEEP_SHFT                                                                 0x4
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM1_CORE_CBCR_HW_CTL_BMSK                                                                0x2
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM1_CORE_CBCR_HW_CTL_SHFT                                                                0x1
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM1_CORE_CBCR_CLK_ENABLE_BMSK                                                            0x1
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM1_CORE_CBCR_CLK_ENABLE_SHFT                                                            0x0

#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM2_CORE_CBCR_ADDR                                                                (LPASS_CC_REG_BASE      + 0x00047018)
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM2_CORE_CBCR_OFFS                                                                (LPASS_CC_REG_BASE_OFFS + 0x00047018)
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM2_CORE_CBCR_RMSK                                                                0x80007ff3
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM2_CORE_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_SMEM_MEM2_CORE_CBCR_ADDR, HWIO_LPASS_ISLAND_SCC_SMEM_MEM2_CORE_CBCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM2_CORE_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_SMEM_MEM2_CORE_CBCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM2_CORE_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_SMEM_MEM2_CORE_CBCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM2_CORE_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_SMEM_MEM2_CORE_CBCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_SMEM_MEM2_CORE_CBCR_IN)
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM2_CORE_CBCR_CLK_OFF_BMSK                                                        0x80000000
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM2_CORE_CBCR_CLK_OFF_SHFT                                                              0x1f
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM2_CORE_CBCR_FORCE_MEM_CORE_ON_BMSK                                                  0x4000
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM2_CORE_CBCR_FORCE_MEM_CORE_ON_SHFT                                                     0xe
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM2_CORE_CBCR_FORCE_MEM_PERIPH_ON_BMSK                                                0x2000
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM2_CORE_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                                   0xd
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM2_CORE_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                                               0x1000
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM2_CORE_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                                  0xc
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM2_CORE_CBCR_WAKEUP_BMSK                                                              0xf00
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM2_CORE_CBCR_WAKEUP_SHFT                                                                0x8
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM2_CORE_CBCR_SLEEP_BMSK                                                                0xf0
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM2_CORE_CBCR_SLEEP_SHFT                                                                 0x4
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM2_CORE_CBCR_HW_CTL_BMSK                                                                0x2
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM2_CORE_CBCR_HW_CTL_SHFT                                                                0x1
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM2_CORE_CBCR_CLK_ENABLE_BMSK                                                            0x1
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM2_CORE_CBCR_CLK_ENABLE_SHFT                                                            0x0

#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM3_CORE_CBCR_ADDR                                                                (LPASS_CC_REG_BASE      + 0x0004701c)
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM3_CORE_CBCR_OFFS                                                                (LPASS_CC_REG_BASE_OFFS + 0x0004701c)
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM3_CORE_CBCR_RMSK                                                                0x80007ff3
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM3_CORE_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_SMEM_MEM3_CORE_CBCR_ADDR, HWIO_LPASS_ISLAND_SCC_SMEM_MEM3_CORE_CBCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM3_CORE_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_SMEM_MEM3_CORE_CBCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM3_CORE_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_SMEM_MEM3_CORE_CBCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM3_CORE_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_SMEM_MEM3_CORE_CBCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_SMEM_MEM3_CORE_CBCR_IN)
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM3_CORE_CBCR_CLK_OFF_BMSK                                                        0x80000000
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM3_CORE_CBCR_CLK_OFF_SHFT                                                              0x1f
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM3_CORE_CBCR_FORCE_MEM_CORE_ON_BMSK                                                  0x4000
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM3_CORE_CBCR_FORCE_MEM_CORE_ON_SHFT                                                     0xe
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM3_CORE_CBCR_FORCE_MEM_PERIPH_ON_BMSK                                                0x2000
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM3_CORE_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                                   0xd
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM3_CORE_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                                               0x1000
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM3_CORE_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                                  0xc
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM3_CORE_CBCR_WAKEUP_BMSK                                                              0xf00
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM3_CORE_CBCR_WAKEUP_SHFT                                                                0x8
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM3_CORE_CBCR_SLEEP_BMSK                                                                0xf0
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM3_CORE_CBCR_SLEEP_SHFT                                                                 0x4
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM3_CORE_CBCR_HW_CTL_BMSK                                                                0x2
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM3_CORE_CBCR_HW_CTL_SHFT                                                                0x1
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM3_CORE_CBCR_CLK_ENABLE_BMSK                                                            0x1
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM3_CORE_CBCR_CLK_ENABLE_SHFT                                                            0x0

#define HWIO_LPASS_ISLAND_SCC_AHB_TIMEOUT_BCR_ADDR                                                                    (LPASS_CC_REG_BASE      + 0x00047020)
#define HWIO_LPASS_ISLAND_SCC_AHB_TIMEOUT_BCR_OFFS                                                                    (LPASS_CC_REG_BASE_OFFS + 0x00047020)
#define HWIO_LPASS_ISLAND_SCC_AHB_TIMEOUT_BCR_RMSK                                                                           0x1
#define HWIO_LPASS_ISLAND_SCC_AHB_TIMEOUT_BCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_AHB_TIMEOUT_BCR_ADDR, HWIO_LPASS_ISLAND_SCC_AHB_TIMEOUT_BCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_AHB_TIMEOUT_BCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_AHB_TIMEOUT_BCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_AHB_TIMEOUT_BCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_AHB_TIMEOUT_BCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_AHB_TIMEOUT_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_AHB_TIMEOUT_BCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_AHB_TIMEOUT_BCR_IN)
#define HWIO_LPASS_ISLAND_SCC_AHB_TIMEOUT_BCR_BLK_ARES_BMSK                                                                  0x1
#define HWIO_LPASS_ISLAND_SCC_AHB_TIMEOUT_BCR_BLK_ARES_SHFT                                                                  0x0

#define HWIO_LPASS_ISLAND_SCC_AHB_TIMEOUT_CORE_CBCR_ADDR                                                              (LPASS_CC_REG_BASE      + 0x00047024)
#define HWIO_LPASS_ISLAND_SCC_AHB_TIMEOUT_CORE_CBCR_OFFS                                                              (LPASS_CC_REG_BASE_OFFS + 0x00047024)
#define HWIO_LPASS_ISLAND_SCC_AHB_TIMEOUT_CORE_CBCR_RMSK                                                              0x80000001
#define HWIO_LPASS_ISLAND_SCC_AHB_TIMEOUT_CORE_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_AHB_TIMEOUT_CORE_CBCR_ADDR, HWIO_LPASS_ISLAND_SCC_AHB_TIMEOUT_CORE_CBCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_AHB_TIMEOUT_CORE_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_AHB_TIMEOUT_CORE_CBCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_AHB_TIMEOUT_CORE_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_AHB_TIMEOUT_CORE_CBCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_AHB_TIMEOUT_CORE_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_AHB_TIMEOUT_CORE_CBCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_AHB_TIMEOUT_CORE_CBCR_IN)
#define HWIO_LPASS_ISLAND_SCC_AHB_TIMEOUT_CORE_CBCR_CLK_OFF_BMSK                                                      0x80000000
#define HWIO_LPASS_ISLAND_SCC_AHB_TIMEOUT_CORE_CBCR_CLK_OFF_SHFT                                                            0x1f
#define HWIO_LPASS_ISLAND_SCC_AHB_TIMEOUT_CORE_CBCR_CLK_ENABLE_BMSK                                                          0x1
#define HWIO_LPASS_ISLAND_SCC_AHB_TIMEOUT_CORE_CBCR_CLK_ENABLE_SHFT                                                          0x0

#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_ADDR                                                                    (LPASS_CC_REG_BASE      + 0x00047028)
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_OFFS                                                                    (LPASS_CC_REG_BASE_OFFS + 0x00047028)
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_RMSK                                                                           0x1
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_ADDR, HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_IN)
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_BLK_ARES_BMSK                                                                  0x1
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_BLK_ARES_SHFT                                                                  0x0

#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_CORE_CBCR_ADDR                                                              (LPASS_CC_REG_BASE      + 0x0004702c)
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_CORE_CBCR_OFFS                                                              (LPASS_CC_REG_BASE_OFFS + 0x0004702c)
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_CORE_CBCR_RMSK                                                              0x80000001
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_CORE_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_CORE_CBCR_ADDR, HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_CORE_CBCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_CORE_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_CORE_CBCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_CORE_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_CORE_CBCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_CORE_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_CORE_CBCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_CORE_CBCR_IN)
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_CORE_CBCR_CLK_OFF_BMSK                                                      0x80000000
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_CORE_CBCR_CLK_OFF_SHFT                                                            0x1f
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_CORE_CBCR_CLK_ENABLE_BMSK                                                          0x1
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_CORE_CBCR_CLK_ENABLE_SHFT                                                          0x0

#define HWIO_LPASS_ISLAND_SCC_VS_BCR_ADDR                                                                             (LPASS_CC_REG_BASE      + 0x00048014)
#define HWIO_LPASS_ISLAND_SCC_VS_BCR_OFFS                                                                             (LPASS_CC_REG_BASE_OFFS + 0x00048014)
#define HWIO_LPASS_ISLAND_SCC_VS_BCR_RMSK                                                                                    0x1
#define HWIO_LPASS_ISLAND_SCC_VS_BCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_VS_BCR_ADDR, HWIO_LPASS_ISLAND_SCC_VS_BCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_VS_BCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_VS_BCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_VS_BCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_VS_BCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_VS_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_VS_BCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_VS_BCR_IN)
#define HWIO_LPASS_ISLAND_SCC_VS_BCR_BLK_ARES_BMSK                                                                           0x1
#define HWIO_LPASS_ISLAND_SCC_VS_BCR_BLK_ARES_SHFT                                                                           0x0

#define HWIO_LPASS_SCC_VS_VDDMX_CMD_RCGR_ADDR                                                                         (LPASS_CC_REG_BASE      + 0x00048018)
#define HWIO_LPASS_SCC_VS_VDDMX_CMD_RCGR_OFFS                                                                         (LPASS_CC_REG_BASE_OFFS + 0x00048018)
#define HWIO_LPASS_SCC_VS_VDDMX_CMD_RCGR_RMSK                                                                         0x800000f3
#define HWIO_LPASS_SCC_VS_VDDMX_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_SCC_VS_VDDMX_CMD_RCGR_ADDR, HWIO_LPASS_SCC_VS_VDDMX_CMD_RCGR_RMSK)
#define HWIO_LPASS_SCC_VS_VDDMX_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_VS_VDDMX_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_SCC_VS_VDDMX_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_VS_VDDMX_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_SCC_VS_VDDMX_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_VS_VDDMX_CMD_RCGR_ADDR,m,v,HWIO_LPASS_SCC_VS_VDDMX_CMD_RCGR_IN)
#define HWIO_LPASS_SCC_VS_VDDMX_CMD_RCGR_ROOT_OFF_BMSK                                                                0x80000000
#define HWIO_LPASS_SCC_VS_VDDMX_CMD_RCGR_ROOT_OFF_SHFT                                                                      0x1f
#define HWIO_LPASS_SCC_VS_VDDMX_CMD_RCGR_DIRTY_D_BMSK                                                                       0x80
#define HWIO_LPASS_SCC_VS_VDDMX_CMD_RCGR_DIRTY_D_SHFT                                                                        0x7
#define HWIO_LPASS_SCC_VS_VDDMX_CMD_RCGR_DIRTY_N_BMSK                                                                       0x40
#define HWIO_LPASS_SCC_VS_VDDMX_CMD_RCGR_DIRTY_N_SHFT                                                                        0x6
#define HWIO_LPASS_SCC_VS_VDDMX_CMD_RCGR_DIRTY_M_BMSK                                                                       0x20
#define HWIO_LPASS_SCC_VS_VDDMX_CMD_RCGR_DIRTY_M_SHFT                                                                        0x5
#define HWIO_LPASS_SCC_VS_VDDMX_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                0x10
#define HWIO_LPASS_SCC_VS_VDDMX_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                 0x4
#define HWIO_LPASS_SCC_VS_VDDMX_CMD_RCGR_ROOT_EN_BMSK                                                                        0x2
#define HWIO_LPASS_SCC_VS_VDDMX_CMD_RCGR_ROOT_EN_SHFT                                                                        0x1
#define HWIO_LPASS_SCC_VS_VDDMX_CMD_RCGR_UPDATE_BMSK                                                                         0x1
#define HWIO_LPASS_SCC_VS_VDDMX_CMD_RCGR_UPDATE_SHFT                                                                         0x0

#define HWIO_LPASS_SCC_VS_VDDMX_CFG_RCGR_ADDR                                                                         (LPASS_CC_REG_BASE      + 0x0004801c)
#define HWIO_LPASS_SCC_VS_VDDMX_CFG_RCGR_OFFS                                                                         (LPASS_CC_REG_BASE_OFFS + 0x0004801c)
#define HWIO_LPASS_SCC_VS_VDDMX_CFG_RCGR_RMSK                                                                              0x71f
#define HWIO_LPASS_SCC_VS_VDDMX_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_SCC_VS_VDDMX_CFG_RCGR_ADDR, HWIO_LPASS_SCC_VS_VDDMX_CFG_RCGR_RMSK)
#define HWIO_LPASS_SCC_VS_VDDMX_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_VS_VDDMX_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_SCC_VS_VDDMX_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_VS_VDDMX_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_SCC_VS_VDDMX_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_VS_VDDMX_CFG_RCGR_ADDR,m,v,HWIO_LPASS_SCC_VS_VDDMX_CFG_RCGR_IN)
#define HWIO_LPASS_SCC_VS_VDDMX_CFG_RCGR_SRC_SEL_BMSK                                                                      0x700
#define HWIO_LPASS_SCC_VS_VDDMX_CFG_RCGR_SRC_SEL_SHFT                                                                        0x8
#define HWIO_LPASS_SCC_VS_VDDMX_CFG_RCGR_SRC_DIV_BMSK                                                                       0x1f
#define HWIO_LPASS_SCC_VS_VDDMX_CFG_RCGR_SRC_DIV_SHFT                                                                        0x0

#define HWIO_LPASS_SCC_VS_VDDCX_CMD_RCGR_ADDR                                                                         (LPASS_CC_REG_BASE      + 0x00048030)
#define HWIO_LPASS_SCC_VS_VDDCX_CMD_RCGR_OFFS                                                                         (LPASS_CC_REG_BASE_OFFS + 0x00048030)
#define HWIO_LPASS_SCC_VS_VDDCX_CMD_RCGR_RMSK                                                                         0x800000f3
#define HWIO_LPASS_SCC_VS_VDDCX_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_SCC_VS_VDDCX_CMD_RCGR_ADDR, HWIO_LPASS_SCC_VS_VDDCX_CMD_RCGR_RMSK)
#define HWIO_LPASS_SCC_VS_VDDCX_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_VS_VDDCX_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_SCC_VS_VDDCX_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_VS_VDDCX_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_SCC_VS_VDDCX_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_VS_VDDCX_CMD_RCGR_ADDR,m,v,HWIO_LPASS_SCC_VS_VDDCX_CMD_RCGR_IN)
#define HWIO_LPASS_SCC_VS_VDDCX_CMD_RCGR_ROOT_OFF_BMSK                                                                0x80000000
#define HWIO_LPASS_SCC_VS_VDDCX_CMD_RCGR_ROOT_OFF_SHFT                                                                      0x1f
#define HWIO_LPASS_SCC_VS_VDDCX_CMD_RCGR_DIRTY_D_BMSK                                                                       0x80
#define HWIO_LPASS_SCC_VS_VDDCX_CMD_RCGR_DIRTY_D_SHFT                                                                        0x7
#define HWIO_LPASS_SCC_VS_VDDCX_CMD_RCGR_DIRTY_N_BMSK                                                                       0x40
#define HWIO_LPASS_SCC_VS_VDDCX_CMD_RCGR_DIRTY_N_SHFT                                                                        0x6
#define HWIO_LPASS_SCC_VS_VDDCX_CMD_RCGR_DIRTY_M_BMSK                                                                       0x20
#define HWIO_LPASS_SCC_VS_VDDCX_CMD_RCGR_DIRTY_M_SHFT                                                                        0x5
#define HWIO_LPASS_SCC_VS_VDDCX_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                0x10
#define HWIO_LPASS_SCC_VS_VDDCX_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                 0x4
#define HWIO_LPASS_SCC_VS_VDDCX_CMD_RCGR_ROOT_EN_BMSK                                                                        0x2
#define HWIO_LPASS_SCC_VS_VDDCX_CMD_RCGR_ROOT_EN_SHFT                                                                        0x1
#define HWIO_LPASS_SCC_VS_VDDCX_CMD_RCGR_UPDATE_BMSK                                                                         0x1
#define HWIO_LPASS_SCC_VS_VDDCX_CMD_RCGR_UPDATE_SHFT                                                                         0x0

#define HWIO_LPASS_SCC_VS_VDDCX_CFG_RCGR_ADDR                                                                         (LPASS_CC_REG_BASE      + 0x00048034)
#define HWIO_LPASS_SCC_VS_VDDCX_CFG_RCGR_OFFS                                                                         (LPASS_CC_REG_BASE_OFFS + 0x00048034)
#define HWIO_LPASS_SCC_VS_VDDCX_CFG_RCGR_RMSK                                                                              0x71f
#define HWIO_LPASS_SCC_VS_VDDCX_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_SCC_VS_VDDCX_CFG_RCGR_ADDR, HWIO_LPASS_SCC_VS_VDDCX_CFG_RCGR_RMSK)
#define HWIO_LPASS_SCC_VS_VDDCX_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_VS_VDDCX_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_SCC_VS_VDDCX_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_VS_VDDCX_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_SCC_VS_VDDCX_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_VS_VDDCX_CFG_RCGR_ADDR,m,v,HWIO_LPASS_SCC_VS_VDDCX_CFG_RCGR_IN)
#define HWIO_LPASS_SCC_VS_VDDCX_CFG_RCGR_SRC_SEL_BMSK                                                                      0x700
#define HWIO_LPASS_SCC_VS_VDDCX_CFG_RCGR_SRC_SEL_SHFT                                                                        0x8
#define HWIO_LPASS_SCC_VS_VDDCX_CFG_RCGR_SRC_DIV_BMSK                                                                       0x1f
#define HWIO_LPASS_SCC_VS_VDDCX_CFG_RCGR_SRC_DIV_SHFT                                                                        0x0

#define HWIO_LPASS_ISLAND_SCC_VS_VDDMX_CBCR_ADDR                                                                      (LPASS_CC_REG_BASE      + 0x00048048)
#define HWIO_LPASS_ISLAND_SCC_VS_VDDMX_CBCR_OFFS                                                                      (LPASS_CC_REG_BASE_OFFS + 0x00048048)
#define HWIO_LPASS_ISLAND_SCC_VS_VDDMX_CBCR_RMSK                                                                      0x80000001
#define HWIO_LPASS_ISLAND_SCC_VS_VDDMX_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_VS_VDDMX_CBCR_ADDR, HWIO_LPASS_ISLAND_SCC_VS_VDDMX_CBCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_VS_VDDMX_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_VS_VDDMX_CBCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_VS_VDDMX_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_VS_VDDMX_CBCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_VS_VDDMX_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_VS_VDDMX_CBCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_VS_VDDMX_CBCR_IN)
#define HWIO_LPASS_ISLAND_SCC_VS_VDDMX_CBCR_CLK_OFF_BMSK                                                              0x80000000
#define HWIO_LPASS_ISLAND_SCC_VS_VDDMX_CBCR_CLK_OFF_SHFT                                                                    0x1f
#define HWIO_LPASS_ISLAND_SCC_VS_VDDMX_CBCR_CLK_ENABLE_BMSK                                                                  0x1
#define HWIO_LPASS_ISLAND_SCC_VS_VDDMX_CBCR_CLK_ENABLE_SHFT                                                                  0x0

#define HWIO_LPASS_ISLAND_SCC_VS_VDDCX_CBCR_ADDR                                                                      (LPASS_CC_REG_BASE      + 0x0004804c)
#define HWIO_LPASS_ISLAND_SCC_VS_VDDCX_CBCR_OFFS                                                                      (LPASS_CC_REG_BASE_OFFS + 0x0004804c)
#define HWIO_LPASS_ISLAND_SCC_VS_VDDCX_CBCR_RMSK                                                                      0x80000001
#define HWIO_LPASS_ISLAND_SCC_VS_VDDCX_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_VS_VDDCX_CBCR_ADDR, HWIO_LPASS_ISLAND_SCC_VS_VDDCX_CBCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_VS_VDDCX_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_VS_VDDCX_CBCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_VS_VDDCX_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_VS_VDDCX_CBCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_VS_VDDCX_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_VS_VDDCX_CBCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_VS_VDDCX_CBCR_IN)
#define HWIO_LPASS_ISLAND_SCC_VS_VDDCX_CBCR_CLK_OFF_BMSK                                                              0x80000000
#define HWIO_LPASS_ISLAND_SCC_VS_VDDCX_CBCR_CLK_OFF_SHFT                                                                    0x1f
#define HWIO_LPASS_ISLAND_SCC_VS_VDDCX_CBCR_CLK_ENABLE_BMSK                                                                  0x1
#define HWIO_LPASS_ISLAND_SCC_VS_VDDCX_CBCR_CLK_ENABLE_SHFT                                                                  0x0

#define HWIO_LPASS_Q6_SPM_CMD_RCGR_ADDR                                                                               (LPASS_CC_REG_BASE      + 0x00049000)
#define HWIO_LPASS_Q6_SPM_CMD_RCGR_OFFS                                                                               (LPASS_CC_REG_BASE_OFFS + 0x00049000)
#define HWIO_LPASS_Q6_SPM_CMD_RCGR_RMSK                                                                               0x800000f3
#define HWIO_LPASS_Q6_SPM_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_Q6_SPM_CMD_RCGR_ADDR, HWIO_LPASS_Q6_SPM_CMD_RCGR_RMSK)
#define HWIO_LPASS_Q6_SPM_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_Q6_SPM_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_Q6_SPM_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_Q6_SPM_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_Q6_SPM_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_Q6_SPM_CMD_RCGR_ADDR,m,v,HWIO_LPASS_Q6_SPM_CMD_RCGR_IN)
#define HWIO_LPASS_Q6_SPM_CMD_RCGR_ROOT_OFF_BMSK                                                                      0x80000000
#define HWIO_LPASS_Q6_SPM_CMD_RCGR_ROOT_OFF_SHFT                                                                            0x1f
#define HWIO_LPASS_Q6_SPM_CMD_RCGR_DIRTY_D_BMSK                                                                             0x80
#define HWIO_LPASS_Q6_SPM_CMD_RCGR_DIRTY_D_SHFT                                                                              0x7
#define HWIO_LPASS_Q6_SPM_CMD_RCGR_DIRTY_N_BMSK                                                                             0x40
#define HWIO_LPASS_Q6_SPM_CMD_RCGR_DIRTY_N_SHFT                                                                              0x6
#define HWIO_LPASS_Q6_SPM_CMD_RCGR_DIRTY_M_BMSK                                                                             0x20
#define HWIO_LPASS_Q6_SPM_CMD_RCGR_DIRTY_M_SHFT                                                                              0x5
#define HWIO_LPASS_Q6_SPM_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                      0x10
#define HWIO_LPASS_Q6_SPM_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                       0x4
#define HWIO_LPASS_Q6_SPM_CMD_RCGR_ROOT_EN_BMSK                                                                              0x2
#define HWIO_LPASS_Q6_SPM_CMD_RCGR_ROOT_EN_SHFT                                                                              0x1
#define HWIO_LPASS_Q6_SPM_CMD_RCGR_UPDATE_BMSK                                                                               0x1
#define HWIO_LPASS_Q6_SPM_CMD_RCGR_UPDATE_SHFT                                                                               0x0

#define HWIO_LPASS_Q6_SPM_CFG_RCGR_ADDR                                                                               (LPASS_CC_REG_BASE      + 0x00049004)
#define HWIO_LPASS_Q6_SPM_CFG_RCGR_OFFS                                                                               (LPASS_CC_REG_BASE_OFFS + 0x00049004)
#define HWIO_LPASS_Q6_SPM_CFG_RCGR_RMSK                                                                                   0x771f
#define HWIO_LPASS_Q6_SPM_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_Q6_SPM_CFG_RCGR_ADDR, HWIO_LPASS_Q6_SPM_CFG_RCGR_RMSK)
#define HWIO_LPASS_Q6_SPM_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_Q6_SPM_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_Q6_SPM_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_Q6_SPM_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_Q6_SPM_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_Q6_SPM_CFG_RCGR_ADDR,m,v,HWIO_LPASS_Q6_SPM_CFG_RCGR_IN)
#define HWIO_LPASS_Q6_SPM_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                       0x4000
#define HWIO_LPASS_Q6_SPM_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                          0xe
#define HWIO_LPASS_Q6_SPM_CFG_RCGR_MODE_BMSK                                                                              0x3000
#define HWIO_LPASS_Q6_SPM_CFG_RCGR_MODE_SHFT                                                                                 0xc
#define HWIO_LPASS_Q6_SPM_CFG_RCGR_SRC_SEL_BMSK                                                                            0x700
#define HWIO_LPASS_Q6_SPM_CFG_RCGR_SRC_SEL_SHFT                                                                              0x8
#define HWIO_LPASS_Q6_SPM_CFG_RCGR_SRC_DIV_BMSK                                                                             0x1f
#define HWIO_LPASS_Q6_SPM_CFG_RCGR_SRC_DIV_SHFT                                                                              0x0

#define HWIO_LPASS_ISLAND_SCC_Q6_SPM_BCR_ADDR                                                                         (LPASS_CC_REG_BASE      + 0x00049008)
#define HWIO_LPASS_ISLAND_SCC_Q6_SPM_BCR_OFFS                                                                         (LPASS_CC_REG_BASE_OFFS + 0x00049008)
#define HWIO_LPASS_ISLAND_SCC_Q6_SPM_BCR_RMSK                                                                                0x1
#define HWIO_LPASS_ISLAND_SCC_Q6_SPM_BCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_Q6_SPM_BCR_ADDR, HWIO_LPASS_ISLAND_SCC_Q6_SPM_BCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_Q6_SPM_BCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_Q6_SPM_BCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_Q6_SPM_BCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_Q6_SPM_BCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_Q6_SPM_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_Q6_SPM_BCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_Q6_SPM_BCR_IN)
#define HWIO_LPASS_ISLAND_SCC_Q6_SPM_BCR_BLK_ARES_BMSK                                                                       0x1
#define HWIO_LPASS_ISLAND_SCC_Q6_SPM_BCR_BLK_ARES_SHFT                                                                       0x0

#define HWIO_LPASS_ISLAND_SCC_Q6_SPM_CBCR_ADDR                                                                        (LPASS_CC_REG_BASE      + 0x0004900c)
#define HWIO_LPASS_ISLAND_SCC_Q6_SPM_CBCR_OFFS                                                                        (LPASS_CC_REG_BASE_OFFS + 0x0004900c)
#define HWIO_LPASS_ISLAND_SCC_Q6_SPM_CBCR_RMSK                                                                        0x800f0001
#define HWIO_LPASS_ISLAND_SCC_Q6_SPM_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_Q6_SPM_CBCR_ADDR, HWIO_LPASS_ISLAND_SCC_Q6_SPM_CBCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_Q6_SPM_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_Q6_SPM_CBCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_Q6_SPM_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_Q6_SPM_CBCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_Q6_SPM_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_Q6_SPM_CBCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_Q6_SPM_CBCR_IN)
#define HWIO_LPASS_ISLAND_SCC_Q6_SPM_CBCR_CLK_OFF_BMSK                                                                0x80000000
#define HWIO_LPASS_ISLAND_SCC_Q6_SPM_CBCR_CLK_OFF_SHFT                                                                      0x1f
#define HWIO_LPASS_ISLAND_SCC_Q6_SPM_CBCR_CLK_DIV_BMSK                                                                   0xf0000
#define HWIO_LPASS_ISLAND_SCC_Q6_SPM_CBCR_CLK_DIV_SHFT                                                                      0x10
#define HWIO_LPASS_ISLAND_SCC_Q6_SPM_CBCR_CLK_ENABLE_BMSK                                                                    0x1
#define HWIO_LPASS_ISLAND_SCC_Q6_SPM_CBCR_CLK_ENABLE_SHFT                                                                    0x0

#define HWIO_LPASS_SW_NPL_CMD_RCGR_ADDR                                                                               (LPASS_CC_REG_BASE      + 0x0004d000)
#define HWIO_LPASS_SW_NPL_CMD_RCGR_OFFS                                                                               (LPASS_CC_REG_BASE_OFFS + 0x0004d000)
#define HWIO_LPASS_SW_NPL_CMD_RCGR_RMSK                                                                               0x800000f3
#define HWIO_LPASS_SW_NPL_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_SW_NPL_CMD_RCGR_ADDR, HWIO_LPASS_SW_NPL_CMD_RCGR_RMSK)
#define HWIO_LPASS_SW_NPL_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SW_NPL_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_SW_NPL_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_SW_NPL_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_SW_NPL_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SW_NPL_CMD_RCGR_ADDR,m,v,HWIO_LPASS_SW_NPL_CMD_RCGR_IN)
#define HWIO_LPASS_SW_NPL_CMD_RCGR_ROOT_OFF_BMSK                                                                      0x80000000
#define HWIO_LPASS_SW_NPL_CMD_RCGR_ROOT_OFF_SHFT                                                                            0x1f
#define HWIO_LPASS_SW_NPL_CMD_RCGR_DIRTY_D_BMSK                                                                             0x80
#define HWIO_LPASS_SW_NPL_CMD_RCGR_DIRTY_D_SHFT                                                                              0x7
#define HWIO_LPASS_SW_NPL_CMD_RCGR_DIRTY_N_BMSK                                                                             0x40
#define HWIO_LPASS_SW_NPL_CMD_RCGR_DIRTY_N_SHFT                                                                              0x6
#define HWIO_LPASS_SW_NPL_CMD_RCGR_DIRTY_M_BMSK                                                                             0x20
#define HWIO_LPASS_SW_NPL_CMD_RCGR_DIRTY_M_SHFT                                                                              0x5
#define HWIO_LPASS_SW_NPL_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                      0x10
#define HWIO_LPASS_SW_NPL_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                       0x4
#define HWIO_LPASS_SW_NPL_CMD_RCGR_ROOT_EN_BMSK                                                                              0x2
#define HWIO_LPASS_SW_NPL_CMD_RCGR_ROOT_EN_SHFT                                                                              0x1
#define HWIO_LPASS_SW_NPL_CMD_RCGR_UPDATE_BMSK                                                                               0x1
#define HWIO_LPASS_SW_NPL_CMD_RCGR_UPDATE_SHFT                                                                               0x0

#define HWIO_LPASS_SW_NPL_CFG_RCGR_ADDR                                                                               (LPASS_CC_REG_BASE      + 0x0004d004)
#define HWIO_LPASS_SW_NPL_CFG_RCGR_OFFS                                                                               (LPASS_CC_REG_BASE_OFFS + 0x0004d004)
#define HWIO_LPASS_SW_NPL_CFG_RCGR_RMSK                                                                                   0x771f
#define HWIO_LPASS_SW_NPL_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_SW_NPL_CFG_RCGR_ADDR, HWIO_LPASS_SW_NPL_CFG_RCGR_RMSK)
#define HWIO_LPASS_SW_NPL_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SW_NPL_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_SW_NPL_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_SW_NPL_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_SW_NPL_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SW_NPL_CFG_RCGR_ADDR,m,v,HWIO_LPASS_SW_NPL_CFG_RCGR_IN)
#define HWIO_LPASS_SW_NPL_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                       0x4000
#define HWIO_LPASS_SW_NPL_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                          0xe
#define HWIO_LPASS_SW_NPL_CFG_RCGR_MODE_BMSK                                                                              0x3000
#define HWIO_LPASS_SW_NPL_CFG_RCGR_MODE_SHFT                                                                                 0xc
#define HWIO_LPASS_SW_NPL_CFG_RCGR_SRC_SEL_BMSK                                                                            0x700
#define HWIO_LPASS_SW_NPL_CFG_RCGR_SRC_SEL_SHFT                                                                              0x8
#define HWIO_LPASS_SW_NPL_CFG_RCGR_SRC_DIV_BMSK                                                                             0x1f
#define HWIO_LPASS_SW_NPL_CFG_RCGR_SRC_DIV_SHFT                                                                              0x0

#define HWIO_LPASS_SW_NPL_M_ADDR                                                                                      (LPASS_CC_REG_BASE      + 0x0004d008)
#define HWIO_LPASS_SW_NPL_M_OFFS                                                                                      (LPASS_CC_REG_BASE_OFFS + 0x0004d008)
#define HWIO_LPASS_SW_NPL_M_RMSK                                                                                            0xff
#define HWIO_LPASS_SW_NPL_M_IN          \
        in_dword_masked(HWIO_LPASS_SW_NPL_M_ADDR, HWIO_LPASS_SW_NPL_M_RMSK)
#define HWIO_LPASS_SW_NPL_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_SW_NPL_M_ADDR, m)
#define HWIO_LPASS_SW_NPL_M_OUT(v)      \
        out_dword(HWIO_LPASS_SW_NPL_M_ADDR,v)
#define HWIO_LPASS_SW_NPL_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SW_NPL_M_ADDR,m,v,HWIO_LPASS_SW_NPL_M_IN)
#define HWIO_LPASS_SW_NPL_M_M_BMSK                                                                                          0xff
#define HWIO_LPASS_SW_NPL_M_M_SHFT                                                                                           0x0

#define HWIO_LPASS_SW_NPL_N_ADDR                                                                                      (LPASS_CC_REG_BASE      + 0x0004d00c)
#define HWIO_LPASS_SW_NPL_N_OFFS                                                                                      (LPASS_CC_REG_BASE_OFFS + 0x0004d00c)
#define HWIO_LPASS_SW_NPL_N_RMSK                                                                                            0xff
#define HWIO_LPASS_SW_NPL_N_IN          \
        in_dword_masked(HWIO_LPASS_SW_NPL_N_ADDR, HWIO_LPASS_SW_NPL_N_RMSK)
#define HWIO_LPASS_SW_NPL_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_SW_NPL_N_ADDR, m)
#define HWIO_LPASS_SW_NPL_N_OUT(v)      \
        out_dword(HWIO_LPASS_SW_NPL_N_ADDR,v)
#define HWIO_LPASS_SW_NPL_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SW_NPL_N_ADDR,m,v,HWIO_LPASS_SW_NPL_N_IN)
#define HWIO_LPASS_SW_NPL_N_NOT_N_MINUS_M_BMSK                                                                              0xff
#define HWIO_LPASS_SW_NPL_N_NOT_N_MINUS_M_SHFT                                                                               0x0

#define HWIO_LPASS_SW_NPL_D_ADDR                                                                                      (LPASS_CC_REG_BASE      + 0x0004d010)
#define HWIO_LPASS_SW_NPL_D_OFFS                                                                                      (LPASS_CC_REG_BASE_OFFS + 0x0004d010)
#define HWIO_LPASS_SW_NPL_D_RMSK                                                                                            0xff
#define HWIO_LPASS_SW_NPL_D_IN          \
        in_dword_masked(HWIO_LPASS_SW_NPL_D_ADDR, HWIO_LPASS_SW_NPL_D_RMSK)
#define HWIO_LPASS_SW_NPL_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_SW_NPL_D_ADDR, m)
#define HWIO_LPASS_SW_NPL_D_OUT(v)      \
        out_dword(HWIO_LPASS_SW_NPL_D_ADDR,v)
#define HWIO_LPASS_SW_NPL_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SW_NPL_D_ADDR,m,v,HWIO_LPASS_SW_NPL_D_IN)
#define HWIO_LPASS_SW_NPL_D_NOT_2D_BMSK                                                                                     0xff
#define HWIO_LPASS_SW_NPL_D_NOT_2D_SHFT                                                                                      0x0

#define HWIO_LPASS_AUDIO_WRAPPER_SW_NPL_CBCR_ADDR                                                                     (LPASS_CC_REG_BASE      + 0x0004d014)
#define HWIO_LPASS_AUDIO_WRAPPER_SW_NPL_CBCR_OFFS                                                                     (LPASS_CC_REG_BASE_OFFS + 0x0004d014)
#define HWIO_LPASS_AUDIO_WRAPPER_SW_NPL_CBCR_RMSK                                                                     0x80000003
#define HWIO_LPASS_AUDIO_WRAPPER_SW_NPL_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_SW_NPL_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_SW_NPL_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_SW_NPL_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_SW_NPL_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_SW_NPL_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_SW_NPL_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_SW_NPL_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_SW_NPL_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_SW_NPL_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_SW_NPL_CBCR_CLK_OFF_BMSK                                                             0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_SW_NPL_CBCR_CLK_OFF_SHFT                                                                   0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_SW_NPL_CBCR_HW_CTL_BMSK                                                                     0x2
#define HWIO_LPASS_AUDIO_WRAPPER_SW_NPL_CBCR_HW_CTL_SHFT                                                                     0x1
#define HWIO_LPASS_AUDIO_WRAPPER_SW_NPL_CBCR_CLK_ENABLE_BMSK                                                                 0x1
#define HWIO_LPASS_AUDIO_WRAPPER_SW_NPL_CBCR_CLK_ENABLE_SHFT                                                                 0x0

#define HWIO_LPASS_INT_I2S0_1_CMD_RCGR_ADDR                                                                           (LPASS_CC_REG_BASE      + 0x0004e000)
#define HWIO_LPASS_INT_I2S0_1_CMD_RCGR_OFFS                                                                           (LPASS_CC_REG_BASE_OFFS + 0x0004e000)
#define HWIO_LPASS_INT_I2S0_1_CMD_RCGR_RMSK                                                                           0x800000f3
#define HWIO_LPASS_INT_I2S0_1_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_INT_I2S0_1_CMD_RCGR_ADDR, HWIO_LPASS_INT_I2S0_1_CMD_RCGR_RMSK)
#define HWIO_LPASS_INT_I2S0_1_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_I2S0_1_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_INT_I2S0_1_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_INT_I2S0_1_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_INT_I2S0_1_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_I2S0_1_CMD_RCGR_ADDR,m,v,HWIO_LPASS_INT_I2S0_1_CMD_RCGR_IN)
#define HWIO_LPASS_INT_I2S0_1_CMD_RCGR_ROOT_OFF_BMSK                                                                  0x80000000
#define HWIO_LPASS_INT_I2S0_1_CMD_RCGR_ROOT_OFF_SHFT                                                                        0x1f
#define HWIO_LPASS_INT_I2S0_1_CMD_RCGR_DIRTY_D_BMSK                                                                         0x80
#define HWIO_LPASS_INT_I2S0_1_CMD_RCGR_DIRTY_D_SHFT                                                                          0x7
#define HWIO_LPASS_INT_I2S0_1_CMD_RCGR_DIRTY_N_BMSK                                                                         0x40
#define HWIO_LPASS_INT_I2S0_1_CMD_RCGR_DIRTY_N_SHFT                                                                          0x6
#define HWIO_LPASS_INT_I2S0_1_CMD_RCGR_DIRTY_M_BMSK                                                                         0x20
#define HWIO_LPASS_INT_I2S0_1_CMD_RCGR_DIRTY_M_SHFT                                                                          0x5
#define HWIO_LPASS_INT_I2S0_1_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                  0x10
#define HWIO_LPASS_INT_I2S0_1_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                   0x4
#define HWIO_LPASS_INT_I2S0_1_CMD_RCGR_ROOT_EN_BMSK                                                                          0x2
#define HWIO_LPASS_INT_I2S0_1_CMD_RCGR_ROOT_EN_SHFT                                                                          0x1
#define HWIO_LPASS_INT_I2S0_1_CMD_RCGR_UPDATE_BMSK                                                                           0x1
#define HWIO_LPASS_INT_I2S0_1_CMD_RCGR_UPDATE_SHFT                                                                           0x0

#define HWIO_LPASS_INT_I2S0_1_CFG_RCGR_ADDR                                                                           (LPASS_CC_REG_BASE      + 0x0004e004)
#define HWIO_LPASS_INT_I2S0_1_CFG_RCGR_OFFS                                                                           (LPASS_CC_REG_BASE_OFFS + 0x0004e004)
#define HWIO_LPASS_INT_I2S0_1_CFG_RCGR_RMSK                                                                               0x771f
#define HWIO_LPASS_INT_I2S0_1_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_INT_I2S0_1_CFG_RCGR_ADDR, HWIO_LPASS_INT_I2S0_1_CFG_RCGR_RMSK)
#define HWIO_LPASS_INT_I2S0_1_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_I2S0_1_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_INT_I2S0_1_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_INT_I2S0_1_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_INT_I2S0_1_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_I2S0_1_CFG_RCGR_ADDR,m,v,HWIO_LPASS_INT_I2S0_1_CFG_RCGR_IN)
#define HWIO_LPASS_INT_I2S0_1_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                   0x4000
#define HWIO_LPASS_INT_I2S0_1_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                      0xe
#define HWIO_LPASS_INT_I2S0_1_CFG_RCGR_MODE_BMSK                                                                          0x3000
#define HWIO_LPASS_INT_I2S0_1_CFG_RCGR_MODE_SHFT                                                                             0xc
#define HWIO_LPASS_INT_I2S0_1_CFG_RCGR_SRC_SEL_BMSK                                                                        0x700
#define HWIO_LPASS_INT_I2S0_1_CFG_RCGR_SRC_SEL_SHFT                                                                          0x8
#define HWIO_LPASS_INT_I2S0_1_CFG_RCGR_SRC_DIV_BMSK                                                                         0x1f
#define HWIO_LPASS_INT_I2S0_1_CFG_RCGR_SRC_DIV_SHFT                                                                          0x0

#define HWIO_LPASS_INT_I2S0_1_M_ADDR                                                                                  (LPASS_CC_REG_BASE      + 0x0004e008)
#define HWIO_LPASS_INT_I2S0_1_M_OFFS                                                                                  (LPASS_CC_REG_BASE_OFFS + 0x0004e008)
#define HWIO_LPASS_INT_I2S0_1_M_RMSK                                                                                        0xff
#define HWIO_LPASS_INT_I2S0_1_M_IN          \
        in_dword_masked(HWIO_LPASS_INT_I2S0_1_M_ADDR, HWIO_LPASS_INT_I2S0_1_M_RMSK)
#define HWIO_LPASS_INT_I2S0_1_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_I2S0_1_M_ADDR, m)
#define HWIO_LPASS_INT_I2S0_1_M_OUT(v)      \
        out_dword(HWIO_LPASS_INT_I2S0_1_M_ADDR,v)
#define HWIO_LPASS_INT_I2S0_1_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_I2S0_1_M_ADDR,m,v,HWIO_LPASS_INT_I2S0_1_M_IN)
#define HWIO_LPASS_INT_I2S0_1_M_M_BMSK                                                                                      0xff
#define HWIO_LPASS_INT_I2S0_1_M_M_SHFT                                                                                       0x0

#define HWIO_LPASS_INT_I2S0_1_N_ADDR                                                                                  (LPASS_CC_REG_BASE      + 0x0004e00c)
#define HWIO_LPASS_INT_I2S0_1_N_OFFS                                                                                  (LPASS_CC_REG_BASE_OFFS + 0x0004e00c)
#define HWIO_LPASS_INT_I2S0_1_N_RMSK                                                                                        0xff
#define HWIO_LPASS_INT_I2S0_1_N_IN          \
        in_dword_masked(HWIO_LPASS_INT_I2S0_1_N_ADDR, HWIO_LPASS_INT_I2S0_1_N_RMSK)
#define HWIO_LPASS_INT_I2S0_1_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_I2S0_1_N_ADDR, m)
#define HWIO_LPASS_INT_I2S0_1_N_OUT(v)      \
        out_dword(HWIO_LPASS_INT_I2S0_1_N_ADDR,v)
#define HWIO_LPASS_INT_I2S0_1_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_I2S0_1_N_ADDR,m,v,HWIO_LPASS_INT_I2S0_1_N_IN)
#define HWIO_LPASS_INT_I2S0_1_N_NOT_N_MINUS_M_BMSK                                                                          0xff
#define HWIO_LPASS_INT_I2S0_1_N_NOT_N_MINUS_M_SHFT                                                                           0x0

#define HWIO_LPASS_INT_I2S0_1_D_ADDR                                                                                  (LPASS_CC_REG_BASE      + 0x0004e010)
#define HWIO_LPASS_INT_I2S0_1_D_OFFS                                                                                  (LPASS_CC_REG_BASE_OFFS + 0x0004e010)
#define HWIO_LPASS_INT_I2S0_1_D_RMSK                                                                                        0xff
#define HWIO_LPASS_INT_I2S0_1_D_IN          \
        in_dword_masked(HWIO_LPASS_INT_I2S0_1_D_ADDR, HWIO_LPASS_INT_I2S0_1_D_RMSK)
#define HWIO_LPASS_INT_I2S0_1_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_I2S0_1_D_ADDR, m)
#define HWIO_LPASS_INT_I2S0_1_D_OUT(v)      \
        out_dword(HWIO_LPASS_INT_I2S0_1_D_ADDR,v)
#define HWIO_LPASS_INT_I2S0_1_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_I2S0_1_D_ADDR,m,v,HWIO_LPASS_INT_I2S0_1_D_IN)
#define HWIO_LPASS_INT_I2S0_1_D_NOT_2D_BMSK                                                                                 0xff
#define HWIO_LPASS_INT_I2S0_1_D_NOT_2D_SHFT                                                                                  0x0

#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_IBIT_CBCR_ADDR                                                               (LPASS_CC_REG_BASE      + 0x0004e014)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_IBIT_CBCR_OFFS                                                               (LPASS_CC_REG_BASE_OFFS + 0x0004e014)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_IBIT_CBCR_RMSK                                                               0x80000003
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_IBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_IBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_IBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_IBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_IBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_IBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_IBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_IBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_IBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_IBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_IBIT_CBCR_CLK_OFF_BMSK                                                       0x80000000
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_IBIT_CBCR_CLK_OFF_SHFT                                                             0x1f
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_IBIT_CBCR_HW_CTL_BMSK                                                               0x2
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_IBIT_CBCR_HW_CTL_SHFT                                                               0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_IBIT_CBCR_CLK_ENABLE_BMSK                                                           0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_IBIT_CBCR_CLK_ENABLE_SHFT                                                           0x0

#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EBIT_CBCR_ADDR                                                               (LPASS_CC_REG_BASE      + 0x0004e018)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EBIT_CBCR_OFFS                                                               (LPASS_CC_REG_BASE_OFFS + 0x0004e018)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EBIT_CBCR_RMSK                                                               0x80000003
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EBIT_CBCR_CLK_OFF_BMSK                                                       0x80000000
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EBIT_CBCR_CLK_OFF_SHFT                                                             0x1f
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EBIT_CBCR_HW_CTL_BMSK                                                               0x2
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EBIT_CBCR_HW_CTL_SHFT                                                               0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EBIT_CBCR_CLK_ENABLE_BMSK                                                           0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EBIT_CBCR_CLK_ENABLE_SHFT                                                           0x0

#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EXT_CLK_DETECT_ADDR                                                          (LPASS_CC_REG_BASE      + 0x0004e01c)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EXT_CLK_DETECT_OFFS                                                          (LPASS_CC_REG_BASE_OFFS + 0x0004e01c)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EXT_CLK_DETECT_RMSK                                                          0x80007f13
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EXT_CLK_DETECT_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EXT_CLK_DETECT_ADDR, HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EXT_CLK_DETECT_RMSK)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EXT_CLK_DETECT_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EXT_CLK_DETECT_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EXT_CLK_DETECT_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EXT_CLK_DETECT_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EXT_CLK_DETECT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EXT_CLK_DETECT_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EXT_CLK_DETECT_IN)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EXT_CLK_DETECT_CLK_INACTIVE_IRQ_BMSK                                         0x80000000
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EXT_CLK_DETECT_CLK_INACTIVE_IRQ_SHFT                                               0x1f
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EXT_CLK_DETECT_CLK_COUNTER_VALUE_BMSK                                            0x7f00
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EXT_CLK_DETECT_CLK_COUNTER_VALUE_SHFT                                               0x8
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EXT_CLK_DETECT_IRQ_CLEAR_BMSK                                                      0x10
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EXT_CLK_DETECT_IRQ_CLEAR_SHFT                                                       0x4
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EXT_CLK_DETECT_CLK_COUNTER_EN_BMSK                                                  0x2
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EXT_CLK_DETECT_CLK_COUNTER_EN_SHFT                                                  0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EXT_CLK_DETECT_IRQ_EN_BMSK                                                          0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EXT_CLK_DETECT_IRQ_EN_SHFT                                                          0x0

#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_TEST_ENABLE_ADDR                                                             (LPASS_CC_REG_BASE      + 0x0004e020)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_TEST_ENABLE_OFFS                                                             (LPASS_CC_REG_BASE_OFFS + 0x0004e020)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_TEST_ENABLE_RMSK                                                                    0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_TEST_ENABLE_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_TEST_ENABLE_ADDR, HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_TEST_ENABLE_RMSK)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_TEST_ENABLE_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_TEST_ENABLE_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_TEST_ENABLE_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_TEST_ENABLE_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_TEST_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_TEST_ENABLE_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_TEST_ENABLE_IN)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_TEST_ENABLE_TEST_CLK_ENABLE_BMSK                                                    0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_TEST_ENABLE_TEST_CLK_ENABLE_SHFT                                                    0x0

#define HWIO_LPASS_INT_I2S2_CMD_RCGR_ADDR                                                                             (LPASS_CC_REG_BASE      + 0x0004f000)
#define HWIO_LPASS_INT_I2S2_CMD_RCGR_OFFS                                                                             (LPASS_CC_REG_BASE_OFFS + 0x0004f000)
#define HWIO_LPASS_INT_I2S2_CMD_RCGR_RMSK                                                                             0x800000f3
#define HWIO_LPASS_INT_I2S2_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_INT_I2S2_CMD_RCGR_ADDR, HWIO_LPASS_INT_I2S2_CMD_RCGR_RMSK)
#define HWIO_LPASS_INT_I2S2_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_I2S2_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_INT_I2S2_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_INT_I2S2_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_INT_I2S2_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_I2S2_CMD_RCGR_ADDR,m,v,HWIO_LPASS_INT_I2S2_CMD_RCGR_IN)
#define HWIO_LPASS_INT_I2S2_CMD_RCGR_ROOT_OFF_BMSK                                                                    0x80000000
#define HWIO_LPASS_INT_I2S2_CMD_RCGR_ROOT_OFF_SHFT                                                                          0x1f
#define HWIO_LPASS_INT_I2S2_CMD_RCGR_DIRTY_D_BMSK                                                                           0x80
#define HWIO_LPASS_INT_I2S2_CMD_RCGR_DIRTY_D_SHFT                                                                            0x7
#define HWIO_LPASS_INT_I2S2_CMD_RCGR_DIRTY_N_BMSK                                                                           0x40
#define HWIO_LPASS_INT_I2S2_CMD_RCGR_DIRTY_N_SHFT                                                                            0x6
#define HWIO_LPASS_INT_I2S2_CMD_RCGR_DIRTY_M_BMSK                                                                           0x20
#define HWIO_LPASS_INT_I2S2_CMD_RCGR_DIRTY_M_SHFT                                                                            0x5
#define HWIO_LPASS_INT_I2S2_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                    0x10
#define HWIO_LPASS_INT_I2S2_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                     0x4
#define HWIO_LPASS_INT_I2S2_CMD_RCGR_ROOT_EN_BMSK                                                                            0x2
#define HWIO_LPASS_INT_I2S2_CMD_RCGR_ROOT_EN_SHFT                                                                            0x1
#define HWIO_LPASS_INT_I2S2_CMD_RCGR_UPDATE_BMSK                                                                             0x1
#define HWIO_LPASS_INT_I2S2_CMD_RCGR_UPDATE_SHFT                                                                             0x0

#define HWIO_LPASS_INT_I2S2_CFG_RCGR_ADDR                                                                             (LPASS_CC_REG_BASE      + 0x0004f004)
#define HWIO_LPASS_INT_I2S2_CFG_RCGR_OFFS                                                                             (LPASS_CC_REG_BASE_OFFS + 0x0004f004)
#define HWIO_LPASS_INT_I2S2_CFG_RCGR_RMSK                                                                                 0x771f
#define HWIO_LPASS_INT_I2S2_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_INT_I2S2_CFG_RCGR_ADDR, HWIO_LPASS_INT_I2S2_CFG_RCGR_RMSK)
#define HWIO_LPASS_INT_I2S2_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_I2S2_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_INT_I2S2_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_INT_I2S2_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_INT_I2S2_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_I2S2_CFG_RCGR_ADDR,m,v,HWIO_LPASS_INT_I2S2_CFG_RCGR_IN)
#define HWIO_LPASS_INT_I2S2_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                     0x4000
#define HWIO_LPASS_INT_I2S2_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                        0xe
#define HWIO_LPASS_INT_I2S2_CFG_RCGR_MODE_BMSK                                                                            0x3000
#define HWIO_LPASS_INT_I2S2_CFG_RCGR_MODE_SHFT                                                                               0xc
#define HWIO_LPASS_INT_I2S2_CFG_RCGR_SRC_SEL_BMSK                                                                          0x700
#define HWIO_LPASS_INT_I2S2_CFG_RCGR_SRC_SEL_SHFT                                                                            0x8
#define HWIO_LPASS_INT_I2S2_CFG_RCGR_SRC_DIV_BMSK                                                                           0x1f
#define HWIO_LPASS_INT_I2S2_CFG_RCGR_SRC_DIV_SHFT                                                                            0x0

#define HWIO_LPASS_INT_I2S2_M_ADDR                                                                                    (LPASS_CC_REG_BASE      + 0x0004f008)
#define HWIO_LPASS_INT_I2S2_M_OFFS                                                                                    (LPASS_CC_REG_BASE_OFFS + 0x0004f008)
#define HWIO_LPASS_INT_I2S2_M_RMSK                                                                                          0xff
#define HWIO_LPASS_INT_I2S2_M_IN          \
        in_dword_masked(HWIO_LPASS_INT_I2S2_M_ADDR, HWIO_LPASS_INT_I2S2_M_RMSK)
#define HWIO_LPASS_INT_I2S2_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_I2S2_M_ADDR, m)
#define HWIO_LPASS_INT_I2S2_M_OUT(v)      \
        out_dword(HWIO_LPASS_INT_I2S2_M_ADDR,v)
#define HWIO_LPASS_INT_I2S2_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_I2S2_M_ADDR,m,v,HWIO_LPASS_INT_I2S2_M_IN)
#define HWIO_LPASS_INT_I2S2_M_M_BMSK                                                                                        0xff
#define HWIO_LPASS_INT_I2S2_M_M_SHFT                                                                                         0x0

#define HWIO_LPASS_INT_I2S2_N_ADDR                                                                                    (LPASS_CC_REG_BASE      + 0x0004f00c)
#define HWIO_LPASS_INT_I2S2_N_OFFS                                                                                    (LPASS_CC_REG_BASE_OFFS + 0x0004f00c)
#define HWIO_LPASS_INT_I2S2_N_RMSK                                                                                          0xff
#define HWIO_LPASS_INT_I2S2_N_IN          \
        in_dword_masked(HWIO_LPASS_INT_I2S2_N_ADDR, HWIO_LPASS_INT_I2S2_N_RMSK)
#define HWIO_LPASS_INT_I2S2_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_I2S2_N_ADDR, m)
#define HWIO_LPASS_INT_I2S2_N_OUT(v)      \
        out_dword(HWIO_LPASS_INT_I2S2_N_ADDR,v)
#define HWIO_LPASS_INT_I2S2_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_I2S2_N_ADDR,m,v,HWIO_LPASS_INT_I2S2_N_IN)
#define HWIO_LPASS_INT_I2S2_N_NOT_N_MINUS_M_BMSK                                                                            0xff
#define HWIO_LPASS_INT_I2S2_N_NOT_N_MINUS_M_SHFT                                                                             0x0

#define HWIO_LPASS_INT_I2S2_D_ADDR                                                                                    (LPASS_CC_REG_BASE      + 0x0004f010)
#define HWIO_LPASS_INT_I2S2_D_OFFS                                                                                    (LPASS_CC_REG_BASE_OFFS + 0x0004f010)
#define HWIO_LPASS_INT_I2S2_D_RMSK                                                                                          0xff
#define HWIO_LPASS_INT_I2S2_D_IN          \
        in_dword_masked(HWIO_LPASS_INT_I2S2_D_ADDR, HWIO_LPASS_INT_I2S2_D_RMSK)
#define HWIO_LPASS_INT_I2S2_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_I2S2_D_ADDR, m)
#define HWIO_LPASS_INT_I2S2_D_OUT(v)      \
        out_dword(HWIO_LPASS_INT_I2S2_D_ADDR,v)
#define HWIO_LPASS_INT_I2S2_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_I2S2_D_ADDR,m,v,HWIO_LPASS_INT_I2S2_D_IN)
#define HWIO_LPASS_INT_I2S2_D_NOT_2D_BMSK                                                                                   0xff
#define HWIO_LPASS_INT_I2S2_D_NOT_2D_SHFT                                                                                    0x0

#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_IBIT_CBCR_ADDR                                                                 (LPASS_CC_REG_BASE      + 0x0004f014)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_IBIT_CBCR_OFFS                                                                 (LPASS_CC_REG_BASE_OFFS + 0x0004f014)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_IBIT_CBCR_RMSK                                                                 0x80000003
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_IBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S2_IBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_INT_I2S2_IBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_IBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S2_IBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_IBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_INT_I2S2_IBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_IBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_INT_I2S2_IBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_INT_I2S2_IBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_IBIT_CBCR_CLK_OFF_BMSK                                                         0x80000000
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_IBIT_CBCR_CLK_OFF_SHFT                                                               0x1f
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_IBIT_CBCR_HW_CTL_BMSK                                                                 0x2
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_IBIT_CBCR_HW_CTL_SHFT                                                                 0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_IBIT_CBCR_CLK_ENABLE_BMSK                                                             0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_IBIT_CBCR_CLK_ENABLE_SHFT                                                             0x0

#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_EBIT_CBCR_ADDR                                                                 (LPASS_CC_REG_BASE      + 0x0004f018)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_EBIT_CBCR_OFFS                                                                 (LPASS_CC_REG_BASE_OFFS + 0x0004f018)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_EBIT_CBCR_RMSK                                                                 0x80000003
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_EBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S2_EBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_INT_I2S2_EBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_EBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S2_EBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_EBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_INT_I2S2_EBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_EBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_INT_I2S2_EBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_INT_I2S2_EBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_EBIT_CBCR_CLK_OFF_BMSK                                                         0x80000000
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_EBIT_CBCR_CLK_OFF_SHFT                                                               0x1f
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_EBIT_CBCR_HW_CTL_BMSK                                                                 0x2
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_EBIT_CBCR_HW_CTL_SHFT                                                                 0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_EBIT_CBCR_CLK_ENABLE_BMSK                                                             0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_EBIT_CBCR_CLK_ENABLE_SHFT                                                             0x0

#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_EXT_CLK_DETECT_ADDR                                                            (LPASS_CC_REG_BASE      + 0x0004f01c)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_EXT_CLK_DETECT_OFFS                                                            (LPASS_CC_REG_BASE_OFFS + 0x0004f01c)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_EXT_CLK_DETECT_RMSK                                                            0x80007f13
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_EXT_CLK_DETECT_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S2_EXT_CLK_DETECT_ADDR, HWIO_LPASS_AUDIO_CORE_INT_I2S2_EXT_CLK_DETECT_RMSK)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_EXT_CLK_DETECT_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S2_EXT_CLK_DETECT_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_EXT_CLK_DETECT_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_INT_I2S2_EXT_CLK_DETECT_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_EXT_CLK_DETECT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_INT_I2S2_EXT_CLK_DETECT_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_INT_I2S2_EXT_CLK_DETECT_IN)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_EXT_CLK_DETECT_CLK_INACTIVE_IRQ_BMSK                                           0x80000000
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_EXT_CLK_DETECT_CLK_INACTIVE_IRQ_SHFT                                                 0x1f
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_EXT_CLK_DETECT_CLK_COUNTER_VALUE_BMSK                                              0x7f00
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_EXT_CLK_DETECT_CLK_COUNTER_VALUE_SHFT                                                 0x8
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_EXT_CLK_DETECT_IRQ_CLEAR_BMSK                                                        0x10
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_EXT_CLK_DETECT_IRQ_CLEAR_SHFT                                                         0x4
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_EXT_CLK_DETECT_CLK_COUNTER_EN_BMSK                                                    0x2
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_EXT_CLK_DETECT_CLK_COUNTER_EN_SHFT                                                    0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_EXT_CLK_DETECT_IRQ_EN_BMSK                                                            0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_EXT_CLK_DETECT_IRQ_EN_SHFT                                                            0x0

#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_TEST_ENABLE_ADDR                                                               (LPASS_CC_REG_BASE      + 0x0004f020)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_TEST_ENABLE_OFFS                                                               (LPASS_CC_REG_BASE_OFFS + 0x0004f020)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_TEST_ENABLE_RMSK                                                                      0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_TEST_ENABLE_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S2_TEST_ENABLE_ADDR, HWIO_LPASS_AUDIO_CORE_INT_I2S2_TEST_ENABLE_RMSK)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_TEST_ENABLE_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S2_TEST_ENABLE_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_TEST_ENABLE_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_INT_I2S2_TEST_ENABLE_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_TEST_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_INT_I2S2_TEST_ENABLE_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_INT_I2S2_TEST_ENABLE_IN)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_TEST_ENABLE_TEST_CLK_ENABLE_BMSK                                                      0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_TEST_ENABLE_TEST_CLK_ENABLE_SHFT                                                      0x0

#define HWIO_LPASS_INT_I2S3_CMD_RCGR_ADDR                                                                             (LPASS_CC_REG_BASE      + 0x00050000)
#define HWIO_LPASS_INT_I2S3_CMD_RCGR_OFFS                                                                             (LPASS_CC_REG_BASE_OFFS + 0x00050000)
#define HWIO_LPASS_INT_I2S3_CMD_RCGR_RMSK                                                                             0x800000f3
#define HWIO_LPASS_INT_I2S3_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_INT_I2S3_CMD_RCGR_ADDR, HWIO_LPASS_INT_I2S3_CMD_RCGR_RMSK)
#define HWIO_LPASS_INT_I2S3_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_I2S3_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_INT_I2S3_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_INT_I2S3_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_INT_I2S3_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_I2S3_CMD_RCGR_ADDR,m,v,HWIO_LPASS_INT_I2S3_CMD_RCGR_IN)
#define HWIO_LPASS_INT_I2S3_CMD_RCGR_ROOT_OFF_BMSK                                                                    0x80000000
#define HWIO_LPASS_INT_I2S3_CMD_RCGR_ROOT_OFF_SHFT                                                                          0x1f
#define HWIO_LPASS_INT_I2S3_CMD_RCGR_DIRTY_D_BMSK                                                                           0x80
#define HWIO_LPASS_INT_I2S3_CMD_RCGR_DIRTY_D_SHFT                                                                            0x7
#define HWIO_LPASS_INT_I2S3_CMD_RCGR_DIRTY_N_BMSK                                                                           0x40
#define HWIO_LPASS_INT_I2S3_CMD_RCGR_DIRTY_N_SHFT                                                                            0x6
#define HWIO_LPASS_INT_I2S3_CMD_RCGR_DIRTY_M_BMSK                                                                           0x20
#define HWIO_LPASS_INT_I2S3_CMD_RCGR_DIRTY_M_SHFT                                                                            0x5
#define HWIO_LPASS_INT_I2S3_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                    0x10
#define HWIO_LPASS_INT_I2S3_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                     0x4
#define HWIO_LPASS_INT_I2S3_CMD_RCGR_ROOT_EN_BMSK                                                                            0x2
#define HWIO_LPASS_INT_I2S3_CMD_RCGR_ROOT_EN_SHFT                                                                            0x1
#define HWIO_LPASS_INT_I2S3_CMD_RCGR_UPDATE_BMSK                                                                             0x1
#define HWIO_LPASS_INT_I2S3_CMD_RCGR_UPDATE_SHFT                                                                             0x0

#define HWIO_LPASS_INT_I2S3_CFG_RCGR_ADDR                                                                             (LPASS_CC_REG_BASE      + 0x00050004)
#define HWIO_LPASS_INT_I2S3_CFG_RCGR_OFFS                                                                             (LPASS_CC_REG_BASE_OFFS + 0x00050004)
#define HWIO_LPASS_INT_I2S3_CFG_RCGR_RMSK                                                                                 0x771f
#define HWIO_LPASS_INT_I2S3_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_INT_I2S3_CFG_RCGR_ADDR, HWIO_LPASS_INT_I2S3_CFG_RCGR_RMSK)
#define HWIO_LPASS_INT_I2S3_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_I2S3_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_INT_I2S3_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_INT_I2S3_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_INT_I2S3_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_I2S3_CFG_RCGR_ADDR,m,v,HWIO_LPASS_INT_I2S3_CFG_RCGR_IN)
#define HWIO_LPASS_INT_I2S3_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                     0x4000
#define HWIO_LPASS_INT_I2S3_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                        0xe
#define HWIO_LPASS_INT_I2S3_CFG_RCGR_MODE_BMSK                                                                            0x3000
#define HWIO_LPASS_INT_I2S3_CFG_RCGR_MODE_SHFT                                                                               0xc
#define HWIO_LPASS_INT_I2S3_CFG_RCGR_SRC_SEL_BMSK                                                                          0x700
#define HWIO_LPASS_INT_I2S3_CFG_RCGR_SRC_SEL_SHFT                                                                            0x8
#define HWIO_LPASS_INT_I2S3_CFG_RCGR_SRC_DIV_BMSK                                                                           0x1f
#define HWIO_LPASS_INT_I2S3_CFG_RCGR_SRC_DIV_SHFT                                                                            0x0

#define HWIO_LPASS_INT_I2S3_M_ADDR                                                                                    (LPASS_CC_REG_BASE      + 0x00050008)
#define HWIO_LPASS_INT_I2S3_M_OFFS                                                                                    (LPASS_CC_REG_BASE_OFFS + 0x00050008)
#define HWIO_LPASS_INT_I2S3_M_RMSK                                                                                          0xff
#define HWIO_LPASS_INT_I2S3_M_IN          \
        in_dword_masked(HWIO_LPASS_INT_I2S3_M_ADDR, HWIO_LPASS_INT_I2S3_M_RMSK)
#define HWIO_LPASS_INT_I2S3_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_I2S3_M_ADDR, m)
#define HWIO_LPASS_INT_I2S3_M_OUT(v)      \
        out_dword(HWIO_LPASS_INT_I2S3_M_ADDR,v)
#define HWIO_LPASS_INT_I2S3_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_I2S3_M_ADDR,m,v,HWIO_LPASS_INT_I2S3_M_IN)
#define HWIO_LPASS_INT_I2S3_M_M_BMSK                                                                                        0xff
#define HWIO_LPASS_INT_I2S3_M_M_SHFT                                                                                         0x0

#define HWIO_LPASS_INT_I2S3_N_ADDR                                                                                    (LPASS_CC_REG_BASE      + 0x0005000c)
#define HWIO_LPASS_INT_I2S3_N_OFFS                                                                                    (LPASS_CC_REG_BASE_OFFS + 0x0005000c)
#define HWIO_LPASS_INT_I2S3_N_RMSK                                                                                          0xff
#define HWIO_LPASS_INT_I2S3_N_IN          \
        in_dword_masked(HWIO_LPASS_INT_I2S3_N_ADDR, HWIO_LPASS_INT_I2S3_N_RMSK)
#define HWIO_LPASS_INT_I2S3_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_I2S3_N_ADDR, m)
#define HWIO_LPASS_INT_I2S3_N_OUT(v)      \
        out_dword(HWIO_LPASS_INT_I2S3_N_ADDR,v)
#define HWIO_LPASS_INT_I2S3_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_I2S3_N_ADDR,m,v,HWIO_LPASS_INT_I2S3_N_IN)
#define HWIO_LPASS_INT_I2S3_N_NOT_N_MINUS_M_BMSK                                                                            0xff
#define HWIO_LPASS_INT_I2S3_N_NOT_N_MINUS_M_SHFT                                                                             0x0

#define HWIO_LPASS_INT_I2S3_D_ADDR                                                                                    (LPASS_CC_REG_BASE      + 0x00050010)
#define HWIO_LPASS_INT_I2S3_D_OFFS                                                                                    (LPASS_CC_REG_BASE_OFFS + 0x00050010)
#define HWIO_LPASS_INT_I2S3_D_RMSK                                                                                          0xff
#define HWIO_LPASS_INT_I2S3_D_IN          \
        in_dword_masked(HWIO_LPASS_INT_I2S3_D_ADDR, HWIO_LPASS_INT_I2S3_D_RMSK)
#define HWIO_LPASS_INT_I2S3_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_I2S3_D_ADDR, m)
#define HWIO_LPASS_INT_I2S3_D_OUT(v)      \
        out_dword(HWIO_LPASS_INT_I2S3_D_ADDR,v)
#define HWIO_LPASS_INT_I2S3_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_I2S3_D_ADDR,m,v,HWIO_LPASS_INT_I2S3_D_IN)
#define HWIO_LPASS_INT_I2S3_D_NOT_2D_BMSK                                                                                   0xff
#define HWIO_LPASS_INT_I2S3_D_NOT_2D_SHFT                                                                                    0x0

#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_IBIT_CBCR_ADDR                                                                 (LPASS_CC_REG_BASE      + 0x00050014)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_IBIT_CBCR_OFFS                                                                 (LPASS_CC_REG_BASE_OFFS + 0x00050014)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_IBIT_CBCR_RMSK                                                                 0x80000003
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_IBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S3_IBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_INT_I2S3_IBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_IBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S3_IBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_IBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_INT_I2S3_IBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_IBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_INT_I2S3_IBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_INT_I2S3_IBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_IBIT_CBCR_CLK_OFF_BMSK                                                         0x80000000
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_IBIT_CBCR_CLK_OFF_SHFT                                                               0x1f
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_IBIT_CBCR_HW_CTL_BMSK                                                                 0x2
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_IBIT_CBCR_HW_CTL_SHFT                                                                 0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_IBIT_CBCR_CLK_ENABLE_BMSK                                                             0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_IBIT_CBCR_CLK_ENABLE_SHFT                                                             0x0

#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_EBIT_CBCR_ADDR                                                                 (LPASS_CC_REG_BASE      + 0x00050018)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_EBIT_CBCR_OFFS                                                                 (LPASS_CC_REG_BASE_OFFS + 0x00050018)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_EBIT_CBCR_RMSK                                                                 0x80000003
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_EBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S3_EBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_INT_I2S3_EBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_EBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S3_EBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_EBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_INT_I2S3_EBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_EBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_INT_I2S3_EBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_INT_I2S3_EBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_EBIT_CBCR_CLK_OFF_BMSK                                                         0x80000000
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_EBIT_CBCR_CLK_OFF_SHFT                                                               0x1f
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_EBIT_CBCR_HW_CTL_BMSK                                                                 0x2
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_EBIT_CBCR_HW_CTL_SHFT                                                                 0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_EBIT_CBCR_CLK_ENABLE_BMSK                                                             0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_EBIT_CBCR_CLK_ENABLE_SHFT                                                             0x0

#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_EXT_CLK_DETECT_ADDR                                                            (LPASS_CC_REG_BASE      + 0x0005001c)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_EXT_CLK_DETECT_OFFS                                                            (LPASS_CC_REG_BASE_OFFS + 0x0005001c)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_EXT_CLK_DETECT_RMSK                                                            0x80007f13
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_EXT_CLK_DETECT_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S3_EXT_CLK_DETECT_ADDR, HWIO_LPASS_AUDIO_CORE_INT_I2S3_EXT_CLK_DETECT_RMSK)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_EXT_CLK_DETECT_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S3_EXT_CLK_DETECT_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_EXT_CLK_DETECT_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_INT_I2S3_EXT_CLK_DETECT_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_EXT_CLK_DETECT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_INT_I2S3_EXT_CLK_DETECT_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_INT_I2S3_EXT_CLK_DETECT_IN)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_EXT_CLK_DETECT_CLK_INACTIVE_IRQ_BMSK                                           0x80000000
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_EXT_CLK_DETECT_CLK_INACTIVE_IRQ_SHFT                                                 0x1f
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_EXT_CLK_DETECT_CLK_COUNTER_VALUE_BMSK                                              0x7f00
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_EXT_CLK_DETECT_CLK_COUNTER_VALUE_SHFT                                                 0x8
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_EXT_CLK_DETECT_IRQ_CLEAR_BMSK                                                        0x10
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_EXT_CLK_DETECT_IRQ_CLEAR_SHFT                                                         0x4
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_EXT_CLK_DETECT_CLK_COUNTER_EN_BMSK                                                    0x2
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_EXT_CLK_DETECT_CLK_COUNTER_EN_SHFT                                                    0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_EXT_CLK_DETECT_IRQ_EN_BMSK                                                            0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_EXT_CLK_DETECT_IRQ_EN_SHFT                                                            0x0

#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_TEST_ENABLE_ADDR                                                               (LPASS_CC_REG_BASE      + 0x00050020)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_TEST_ENABLE_OFFS                                                               (LPASS_CC_REG_BASE_OFFS + 0x00050020)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_TEST_ENABLE_RMSK                                                                      0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_TEST_ENABLE_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S3_TEST_ENABLE_ADDR, HWIO_LPASS_AUDIO_CORE_INT_I2S3_TEST_ENABLE_RMSK)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_TEST_ENABLE_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S3_TEST_ENABLE_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_TEST_ENABLE_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_INT_I2S3_TEST_ENABLE_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_TEST_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_INT_I2S3_TEST_ENABLE_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_INT_I2S3_TEST_ENABLE_IN)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_TEST_ENABLE_TEST_CLK_ENABLE_BMSK                                                      0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_TEST_ENABLE_TEST_CLK_ENABLE_SHFT                                                      0x0

#define HWIO_LPASS_INT_I2S4_CMD_RCGR_ADDR                                                                             (LPASS_CC_REG_BASE      + 0x00051000)
#define HWIO_LPASS_INT_I2S4_CMD_RCGR_OFFS                                                                             (LPASS_CC_REG_BASE_OFFS + 0x00051000)
#define HWIO_LPASS_INT_I2S4_CMD_RCGR_RMSK                                                                             0x800000f3
#define HWIO_LPASS_INT_I2S4_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_INT_I2S4_CMD_RCGR_ADDR, HWIO_LPASS_INT_I2S4_CMD_RCGR_RMSK)
#define HWIO_LPASS_INT_I2S4_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_I2S4_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_INT_I2S4_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_INT_I2S4_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_INT_I2S4_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_I2S4_CMD_RCGR_ADDR,m,v,HWIO_LPASS_INT_I2S4_CMD_RCGR_IN)
#define HWIO_LPASS_INT_I2S4_CMD_RCGR_ROOT_OFF_BMSK                                                                    0x80000000
#define HWIO_LPASS_INT_I2S4_CMD_RCGR_ROOT_OFF_SHFT                                                                          0x1f
#define HWIO_LPASS_INT_I2S4_CMD_RCGR_DIRTY_D_BMSK                                                                           0x80
#define HWIO_LPASS_INT_I2S4_CMD_RCGR_DIRTY_D_SHFT                                                                            0x7
#define HWIO_LPASS_INT_I2S4_CMD_RCGR_DIRTY_N_BMSK                                                                           0x40
#define HWIO_LPASS_INT_I2S4_CMD_RCGR_DIRTY_N_SHFT                                                                            0x6
#define HWIO_LPASS_INT_I2S4_CMD_RCGR_DIRTY_M_BMSK                                                                           0x20
#define HWIO_LPASS_INT_I2S4_CMD_RCGR_DIRTY_M_SHFT                                                                            0x5
#define HWIO_LPASS_INT_I2S4_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                    0x10
#define HWIO_LPASS_INT_I2S4_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                     0x4
#define HWIO_LPASS_INT_I2S4_CMD_RCGR_ROOT_EN_BMSK                                                                            0x2
#define HWIO_LPASS_INT_I2S4_CMD_RCGR_ROOT_EN_SHFT                                                                            0x1
#define HWIO_LPASS_INT_I2S4_CMD_RCGR_UPDATE_BMSK                                                                             0x1
#define HWIO_LPASS_INT_I2S4_CMD_RCGR_UPDATE_SHFT                                                                             0x0

#define HWIO_LPASS_INT_I2S4_CFG_RCGR_ADDR                                                                             (LPASS_CC_REG_BASE      + 0x00051004)
#define HWIO_LPASS_INT_I2S4_CFG_RCGR_OFFS                                                                             (LPASS_CC_REG_BASE_OFFS + 0x00051004)
#define HWIO_LPASS_INT_I2S4_CFG_RCGR_RMSK                                                                                 0x771f
#define HWIO_LPASS_INT_I2S4_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_INT_I2S4_CFG_RCGR_ADDR, HWIO_LPASS_INT_I2S4_CFG_RCGR_RMSK)
#define HWIO_LPASS_INT_I2S4_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_I2S4_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_INT_I2S4_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_INT_I2S4_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_INT_I2S4_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_I2S4_CFG_RCGR_ADDR,m,v,HWIO_LPASS_INT_I2S4_CFG_RCGR_IN)
#define HWIO_LPASS_INT_I2S4_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                     0x4000
#define HWIO_LPASS_INT_I2S4_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                        0xe
#define HWIO_LPASS_INT_I2S4_CFG_RCGR_MODE_BMSK                                                                            0x3000
#define HWIO_LPASS_INT_I2S4_CFG_RCGR_MODE_SHFT                                                                               0xc
#define HWIO_LPASS_INT_I2S4_CFG_RCGR_SRC_SEL_BMSK                                                                          0x700
#define HWIO_LPASS_INT_I2S4_CFG_RCGR_SRC_SEL_SHFT                                                                            0x8
#define HWIO_LPASS_INT_I2S4_CFG_RCGR_SRC_DIV_BMSK                                                                           0x1f
#define HWIO_LPASS_INT_I2S4_CFG_RCGR_SRC_DIV_SHFT                                                                            0x0

#define HWIO_LPASS_INT_I2S4_M_ADDR                                                                                    (LPASS_CC_REG_BASE      + 0x00051008)
#define HWIO_LPASS_INT_I2S4_M_OFFS                                                                                    (LPASS_CC_REG_BASE_OFFS + 0x00051008)
#define HWIO_LPASS_INT_I2S4_M_RMSK                                                                                          0xff
#define HWIO_LPASS_INT_I2S4_M_IN          \
        in_dword_masked(HWIO_LPASS_INT_I2S4_M_ADDR, HWIO_LPASS_INT_I2S4_M_RMSK)
#define HWIO_LPASS_INT_I2S4_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_I2S4_M_ADDR, m)
#define HWIO_LPASS_INT_I2S4_M_OUT(v)      \
        out_dword(HWIO_LPASS_INT_I2S4_M_ADDR,v)
#define HWIO_LPASS_INT_I2S4_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_I2S4_M_ADDR,m,v,HWIO_LPASS_INT_I2S4_M_IN)
#define HWIO_LPASS_INT_I2S4_M_M_BMSK                                                                                        0xff
#define HWIO_LPASS_INT_I2S4_M_M_SHFT                                                                                         0x0

#define HWIO_LPASS_INT_I2S4_N_ADDR                                                                                    (LPASS_CC_REG_BASE      + 0x0005100c)
#define HWIO_LPASS_INT_I2S4_N_OFFS                                                                                    (LPASS_CC_REG_BASE_OFFS + 0x0005100c)
#define HWIO_LPASS_INT_I2S4_N_RMSK                                                                                          0xff
#define HWIO_LPASS_INT_I2S4_N_IN          \
        in_dword_masked(HWIO_LPASS_INT_I2S4_N_ADDR, HWIO_LPASS_INT_I2S4_N_RMSK)
#define HWIO_LPASS_INT_I2S4_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_I2S4_N_ADDR, m)
#define HWIO_LPASS_INT_I2S4_N_OUT(v)      \
        out_dword(HWIO_LPASS_INT_I2S4_N_ADDR,v)
#define HWIO_LPASS_INT_I2S4_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_I2S4_N_ADDR,m,v,HWIO_LPASS_INT_I2S4_N_IN)
#define HWIO_LPASS_INT_I2S4_N_NOT_N_MINUS_M_BMSK                                                                            0xff
#define HWIO_LPASS_INT_I2S4_N_NOT_N_MINUS_M_SHFT                                                                             0x0

#define HWIO_LPASS_INT_I2S4_D_ADDR                                                                                    (LPASS_CC_REG_BASE      + 0x00051010)
#define HWIO_LPASS_INT_I2S4_D_OFFS                                                                                    (LPASS_CC_REG_BASE_OFFS + 0x00051010)
#define HWIO_LPASS_INT_I2S4_D_RMSK                                                                                          0xff
#define HWIO_LPASS_INT_I2S4_D_IN          \
        in_dword_masked(HWIO_LPASS_INT_I2S4_D_ADDR, HWIO_LPASS_INT_I2S4_D_RMSK)
#define HWIO_LPASS_INT_I2S4_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_I2S4_D_ADDR, m)
#define HWIO_LPASS_INT_I2S4_D_OUT(v)      \
        out_dword(HWIO_LPASS_INT_I2S4_D_ADDR,v)
#define HWIO_LPASS_INT_I2S4_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_I2S4_D_ADDR,m,v,HWIO_LPASS_INT_I2S4_D_IN)
#define HWIO_LPASS_INT_I2S4_D_NOT_2D_BMSK                                                                                   0xff
#define HWIO_LPASS_INT_I2S4_D_NOT_2D_SHFT                                                                                    0x0

#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_IBIT_CBCR_ADDR                                                                 (LPASS_CC_REG_BASE      + 0x00051014)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_IBIT_CBCR_OFFS                                                                 (LPASS_CC_REG_BASE_OFFS + 0x00051014)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_IBIT_CBCR_RMSK                                                                 0x80000003
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_IBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S4_IBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_INT_I2S4_IBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_IBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S4_IBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_IBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_INT_I2S4_IBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_IBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_INT_I2S4_IBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_INT_I2S4_IBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_IBIT_CBCR_CLK_OFF_BMSK                                                         0x80000000
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_IBIT_CBCR_CLK_OFF_SHFT                                                               0x1f
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_IBIT_CBCR_HW_CTL_BMSK                                                                 0x2
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_IBIT_CBCR_HW_CTL_SHFT                                                                 0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_IBIT_CBCR_CLK_ENABLE_BMSK                                                             0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_IBIT_CBCR_CLK_ENABLE_SHFT                                                             0x0

#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_EBIT_CBCR_ADDR                                                                 (LPASS_CC_REG_BASE      + 0x00051018)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_EBIT_CBCR_OFFS                                                                 (LPASS_CC_REG_BASE_OFFS + 0x00051018)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_EBIT_CBCR_RMSK                                                                 0x80000003
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_EBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S4_EBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_INT_I2S4_EBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_EBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S4_EBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_EBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_INT_I2S4_EBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_EBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_INT_I2S4_EBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_INT_I2S4_EBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_EBIT_CBCR_CLK_OFF_BMSK                                                         0x80000000
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_EBIT_CBCR_CLK_OFF_SHFT                                                               0x1f
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_EBIT_CBCR_HW_CTL_BMSK                                                                 0x2
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_EBIT_CBCR_HW_CTL_SHFT                                                                 0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_EBIT_CBCR_CLK_ENABLE_BMSK                                                             0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_EBIT_CBCR_CLK_ENABLE_SHFT                                                             0x0

#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_EXT_CLK_DETECT_ADDR                                                            (LPASS_CC_REG_BASE      + 0x0005101c)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_EXT_CLK_DETECT_OFFS                                                            (LPASS_CC_REG_BASE_OFFS + 0x0005101c)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_EXT_CLK_DETECT_RMSK                                                            0x80007f13
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_EXT_CLK_DETECT_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S4_EXT_CLK_DETECT_ADDR, HWIO_LPASS_AUDIO_CORE_INT_I2S4_EXT_CLK_DETECT_RMSK)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_EXT_CLK_DETECT_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S4_EXT_CLK_DETECT_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_EXT_CLK_DETECT_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_INT_I2S4_EXT_CLK_DETECT_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_EXT_CLK_DETECT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_INT_I2S4_EXT_CLK_DETECT_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_INT_I2S4_EXT_CLK_DETECT_IN)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_EXT_CLK_DETECT_CLK_INACTIVE_IRQ_BMSK                                           0x80000000
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_EXT_CLK_DETECT_CLK_INACTIVE_IRQ_SHFT                                                 0x1f
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_EXT_CLK_DETECT_CLK_COUNTER_VALUE_BMSK                                              0x7f00
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_EXT_CLK_DETECT_CLK_COUNTER_VALUE_SHFT                                                 0x8
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_EXT_CLK_DETECT_IRQ_CLEAR_BMSK                                                        0x10
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_EXT_CLK_DETECT_IRQ_CLEAR_SHFT                                                         0x4
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_EXT_CLK_DETECT_CLK_COUNTER_EN_BMSK                                                    0x2
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_EXT_CLK_DETECT_CLK_COUNTER_EN_SHFT                                                    0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_EXT_CLK_DETECT_IRQ_EN_BMSK                                                            0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_EXT_CLK_DETECT_IRQ_EN_SHFT                                                            0x0

#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_TEST_ENABLE_ADDR                                                               (LPASS_CC_REG_BASE      + 0x00051020)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_TEST_ENABLE_OFFS                                                               (LPASS_CC_REG_BASE_OFFS + 0x00051020)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_TEST_ENABLE_RMSK                                                                      0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_TEST_ENABLE_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S4_TEST_ENABLE_ADDR, HWIO_LPASS_AUDIO_CORE_INT_I2S4_TEST_ENABLE_RMSK)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_TEST_ENABLE_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S4_TEST_ENABLE_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_TEST_ENABLE_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_INT_I2S4_TEST_ENABLE_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_TEST_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_INT_I2S4_TEST_ENABLE_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_INT_I2S4_TEST_ENABLE_IN)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_TEST_ENABLE_TEST_CLK_ENABLE_BMSK                                                      0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_TEST_ENABLE_TEST_CLK_ENABLE_SHFT                                                      0x0

#define HWIO_LPASS_INT_I2S5_6_CMD_RCGR_ADDR                                                                           (LPASS_CC_REG_BASE      + 0x00052000)
#define HWIO_LPASS_INT_I2S5_6_CMD_RCGR_OFFS                                                                           (LPASS_CC_REG_BASE_OFFS + 0x00052000)
#define HWIO_LPASS_INT_I2S5_6_CMD_RCGR_RMSK                                                                           0x800000f3
#define HWIO_LPASS_INT_I2S5_6_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_INT_I2S5_6_CMD_RCGR_ADDR, HWIO_LPASS_INT_I2S5_6_CMD_RCGR_RMSK)
#define HWIO_LPASS_INT_I2S5_6_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_I2S5_6_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_INT_I2S5_6_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_INT_I2S5_6_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_INT_I2S5_6_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_I2S5_6_CMD_RCGR_ADDR,m,v,HWIO_LPASS_INT_I2S5_6_CMD_RCGR_IN)
#define HWIO_LPASS_INT_I2S5_6_CMD_RCGR_ROOT_OFF_BMSK                                                                  0x80000000
#define HWIO_LPASS_INT_I2S5_6_CMD_RCGR_ROOT_OFF_SHFT                                                                        0x1f
#define HWIO_LPASS_INT_I2S5_6_CMD_RCGR_DIRTY_D_BMSK                                                                         0x80
#define HWIO_LPASS_INT_I2S5_6_CMD_RCGR_DIRTY_D_SHFT                                                                          0x7
#define HWIO_LPASS_INT_I2S5_6_CMD_RCGR_DIRTY_N_BMSK                                                                         0x40
#define HWIO_LPASS_INT_I2S5_6_CMD_RCGR_DIRTY_N_SHFT                                                                          0x6
#define HWIO_LPASS_INT_I2S5_6_CMD_RCGR_DIRTY_M_BMSK                                                                         0x20
#define HWIO_LPASS_INT_I2S5_6_CMD_RCGR_DIRTY_M_SHFT                                                                          0x5
#define HWIO_LPASS_INT_I2S5_6_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                  0x10
#define HWIO_LPASS_INT_I2S5_6_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                   0x4
#define HWIO_LPASS_INT_I2S5_6_CMD_RCGR_ROOT_EN_BMSK                                                                          0x2
#define HWIO_LPASS_INT_I2S5_6_CMD_RCGR_ROOT_EN_SHFT                                                                          0x1
#define HWIO_LPASS_INT_I2S5_6_CMD_RCGR_UPDATE_BMSK                                                                           0x1
#define HWIO_LPASS_INT_I2S5_6_CMD_RCGR_UPDATE_SHFT                                                                           0x0

#define HWIO_LPASS_INT_I2S5_6_CFG_RCGR_ADDR                                                                           (LPASS_CC_REG_BASE      + 0x00052004)
#define HWIO_LPASS_INT_I2S5_6_CFG_RCGR_OFFS                                                                           (LPASS_CC_REG_BASE_OFFS + 0x00052004)
#define HWIO_LPASS_INT_I2S5_6_CFG_RCGR_RMSK                                                                               0x771f
#define HWIO_LPASS_INT_I2S5_6_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_INT_I2S5_6_CFG_RCGR_ADDR, HWIO_LPASS_INT_I2S5_6_CFG_RCGR_RMSK)
#define HWIO_LPASS_INT_I2S5_6_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_I2S5_6_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_INT_I2S5_6_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_INT_I2S5_6_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_INT_I2S5_6_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_I2S5_6_CFG_RCGR_ADDR,m,v,HWIO_LPASS_INT_I2S5_6_CFG_RCGR_IN)
#define HWIO_LPASS_INT_I2S5_6_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                   0x4000
#define HWIO_LPASS_INT_I2S5_6_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                      0xe
#define HWIO_LPASS_INT_I2S5_6_CFG_RCGR_MODE_BMSK                                                                          0x3000
#define HWIO_LPASS_INT_I2S5_6_CFG_RCGR_MODE_SHFT                                                                             0xc
#define HWIO_LPASS_INT_I2S5_6_CFG_RCGR_SRC_SEL_BMSK                                                                        0x700
#define HWIO_LPASS_INT_I2S5_6_CFG_RCGR_SRC_SEL_SHFT                                                                          0x8
#define HWIO_LPASS_INT_I2S5_6_CFG_RCGR_SRC_DIV_BMSK                                                                         0x1f
#define HWIO_LPASS_INT_I2S5_6_CFG_RCGR_SRC_DIV_SHFT                                                                          0x0

#define HWIO_LPASS_INT_I2S5_6_M_ADDR                                                                                  (LPASS_CC_REG_BASE      + 0x00052008)
#define HWIO_LPASS_INT_I2S5_6_M_OFFS                                                                                  (LPASS_CC_REG_BASE_OFFS + 0x00052008)
#define HWIO_LPASS_INT_I2S5_6_M_RMSK                                                                                        0xff
#define HWIO_LPASS_INT_I2S5_6_M_IN          \
        in_dword_masked(HWIO_LPASS_INT_I2S5_6_M_ADDR, HWIO_LPASS_INT_I2S5_6_M_RMSK)
#define HWIO_LPASS_INT_I2S5_6_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_I2S5_6_M_ADDR, m)
#define HWIO_LPASS_INT_I2S5_6_M_OUT(v)      \
        out_dword(HWIO_LPASS_INT_I2S5_6_M_ADDR,v)
#define HWIO_LPASS_INT_I2S5_6_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_I2S5_6_M_ADDR,m,v,HWIO_LPASS_INT_I2S5_6_M_IN)
#define HWIO_LPASS_INT_I2S5_6_M_M_BMSK                                                                                      0xff
#define HWIO_LPASS_INT_I2S5_6_M_M_SHFT                                                                                       0x0

#define HWIO_LPASS_INT_I2S5_6_N_ADDR                                                                                  (LPASS_CC_REG_BASE      + 0x0005200c)
#define HWIO_LPASS_INT_I2S5_6_N_OFFS                                                                                  (LPASS_CC_REG_BASE_OFFS + 0x0005200c)
#define HWIO_LPASS_INT_I2S5_6_N_RMSK                                                                                        0xff
#define HWIO_LPASS_INT_I2S5_6_N_IN          \
        in_dword_masked(HWIO_LPASS_INT_I2S5_6_N_ADDR, HWIO_LPASS_INT_I2S5_6_N_RMSK)
#define HWIO_LPASS_INT_I2S5_6_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_I2S5_6_N_ADDR, m)
#define HWIO_LPASS_INT_I2S5_6_N_OUT(v)      \
        out_dword(HWIO_LPASS_INT_I2S5_6_N_ADDR,v)
#define HWIO_LPASS_INT_I2S5_6_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_I2S5_6_N_ADDR,m,v,HWIO_LPASS_INT_I2S5_6_N_IN)
#define HWIO_LPASS_INT_I2S5_6_N_NOT_N_MINUS_M_BMSK                                                                          0xff
#define HWIO_LPASS_INT_I2S5_6_N_NOT_N_MINUS_M_SHFT                                                                           0x0

#define HWIO_LPASS_INT_I2S5_6_D_ADDR                                                                                  (LPASS_CC_REG_BASE      + 0x00052010)
#define HWIO_LPASS_INT_I2S5_6_D_OFFS                                                                                  (LPASS_CC_REG_BASE_OFFS + 0x00052010)
#define HWIO_LPASS_INT_I2S5_6_D_RMSK                                                                                        0xff
#define HWIO_LPASS_INT_I2S5_6_D_IN          \
        in_dword_masked(HWIO_LPASS_INT_I2S5_6_D_ADDR, HWIO_LPASS_INT_I2S5_6_D_RMSK)
#define HWIO_LPASS_INT_I2S5_6_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_I2S5_6_D_ADDR, m)
#define HWIO_LPASS_INT_I2S5_6_D_OUT(v)      \
        out_dword(HWIO_LPASS_INT_I2S5_6_D_ADDR,v)
#define HWIO_LPASS_INT_I2S5_6_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_I2S5_6_D_ADDR,m,v,HWIO_LPASS_INT_I2S5_6_D_IN)
#define HWIO_LPASS_INT_I2S5_6_D_NOT_2D_BMSK                                                                                 0xff
#define HWIO_LPASS_INT_I2S5_6_D_NOT_2D_SHFT                                                                                  0x0

#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_IBIT_CBCR_ADDR                                                               (LPASS_CC_REG_BASE      + 0x00052014)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_IBIT_CBCR_OFFS                                                               (LPASS_CC_REG_BASE_OFFS + 0x00052014)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_IBIT_CBCR_RMSK                                                               0x80000003
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_IBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_IBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_IBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_IBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_IBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_IBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_IBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_IBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_IBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_IBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_IBIT_CBCR_CLK_OFF_BMSK                                                       0x80000000
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_IBIT_CBCR_CLK_OFF_SHFT                                                             0x1f
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_IBIT_CBCR_HW_CTL_BMSK                                                               0x2
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_IBIT_CBCR_HW_CTL_SHFT                                                               0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_IBIT_CBCR_CLK_ENABLE_BMSK                                                           0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_IBIT_CBCR_CLK_ENABLE_SHFT                                                           0x0

#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EBIT_CBCR_ADDR                                                               (LPASS_CC_REG_BASE      + 0x00052018)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EBIT_CBCR_OFFS                                                               (LPASS_CC_REG_BASE_OFFS + 0x00052018)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EBIT_CBCR_RMSK                                                               0x80000003
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EBIT_CBCR_CLK_OFF_BMSK                                                       0x80000000
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EBIT_CBCR_CLK_OFF_SHFT                                                             0x1f
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EBIT_CBCR_HW_CTL_BMSK                                                               0x2
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EBIT_CBCR_HW_CTL_SHFT                                                               0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EBIT_CBCR_CLK_ENABLE_BMSK                                                           0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EBIT_CBCR_CLK_ENABLE_SHFT                                                           0x0

#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EXT_CLK_DETECT_ADDR                                                          (LPASS_CC_REG_BASE      + 0x0005201c)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EXT_CLK_DETECT_OFFS                                                          (LPASS_CC_REG_BASE_OFFS + 0x0005201c)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EXT_CLK_DETECT_RMSK                                                          0x80007f13
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EXT_CLK_DETECT_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EXT_CLK_DETECT_ADDR, HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EXT_CLK_DETECT_RMSK)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EXT_CLK_DETECT_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EXT_CLK_DETECT_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EXT_CLK_DETECT_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EXT_CLK_DETECT_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EXT_CLK_DETECT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EXT_CLK_DETECT_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EXT_CLK_DETECT_IN)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EXT_CLK_DETECT_CLK_INACTIVE_IRQ_BMSK                                         0x80000000
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EXT_CLK_DETECT_CLK_INACTIVE_IRQ_SHFT                                               0x1f
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EXT_CLK_DETECT_CLK_COUNTER_VALUE_BMSK                                            0x7f00
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EXT_CLK_DETECT_CLK_COUNTER_VALUE_SHFT                                               0x8
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EXT_CLK_DETECT_IRQ_CLEAR_BMSK                                                      0x10
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EXT_CLK_DETECT_IRQ_CLEAR_SHFT                                                       0x4
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EXT_CLK_DETECT_CLK_COUNTER_EN_BMSK                                                  0x2
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EXT_CLK_DETECT_CLK_COUNTER_EN_SHFT                                                  0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EXT_CLK_DETECT_IRQ_EN_BMSK                                                          0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EXT_CLK_DETECT_IRQ_EN_SHFT                                                          0x0

#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_TEST_ENABLE_ADDR                                                             (LPASS_CC_REG_BASE      + 0x00052020)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_TEST_ENABLE_OFFS                                                             (LPASS_CC_REG_BASE_OFFS + 0x00052020)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_TEST_ENABLE_RMSK                                                                    0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_TEST_ENABLE_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_TEST_ENABLE_ADDR, HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_TEST_ENABLE_RMSK)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_TEST_ENABLE_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_TEST_ENABLE_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_TEST_ENABLE_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_TEST_ENABLE_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_TEST_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_TEST_ENABLE_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_TEST_ENABLE_IN)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_TEST_ENABLE_TEST_CLK_ENABLE_BMSK                                                    0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_TEST_ENABLE_TEST_CLK_ENABLE_SHFT                                                    0x0

#define HWIO_LPASS_INT_MCLK0_CMD_RCGR_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x00053000)
#define HWIO_LPASS_INT_MCLK0_CMD_RCGR_OFFS                                                                            (LPASS_CC_REG_BASE_OFFS + 0x00053000)
#define HWIO_LPASS_INT_MCLK0_CMD_RCGR_RMSK                                                                            0x800000f3
#define HWIO_LPASS_INT_MCLK0_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_INT_MCLK0_CMD_RCGR_ADDR, HWIO_LPASS_INT_MCLK0_CMD_RCGR_RMSK)
#define HWIO_LPASS_INT_MCLK0_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_MCLK0_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_INT_MCLK0_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_INT_MCLK0_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_INT_MCLK0_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_MCLK0_CMD_RCGR_ADDR,m,v,HWIO_LPASS_INT_MCLK0_CMD_RCGR_IN)
#define HWIO_LPASS_INT_MCLK0_CMD_RCGR_ROOT_OFF_BMSK                                                                   0x80000000
#define HWIO_LPASS_INT_MCLK0_CMD_RCGR_ROOT_OFF_SHFT                                                                         0x1f
#define HWIO_LPASS_INT_MCLK0_CMD_RCGR_DIRTY_D_BMSK                                                                          0x80
#define HWIO_LPASS_INT_MCLK0_CMD_RCGR_DIRTY_D_SHFT                                                                           0x7
#define HWIO_LPASS_INT_MCLK0_CMD_RCGR_DIRTY_N_BMSK                                                                          0x40
#define HWIO_LPASS_INT_MCLK0_CMD_RCGR_DIRTY_N_SHFT                                                                           0x6
#define HWIO_LPASS_INT_MCLK0_CMD_RCGR_DIRTY_M_BMSK                                                                          0x20
#define HWIO_LPASS_INT_MCLK0_CMD_RCGR_DIRTY_M_SHFT                                                                           0x5
#define HWIO_LPASS_INT_MCLK0_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                   0x10
#define HWIO_LPASS_INT_MCLK0_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                    0x4
#define HWIO_LPASS_INT_MCLK0_CMD_RCGR_ROOT_EN_BMSK                                                                           0x2
#define HWIO_LPASS_INT_MCLK0_CMD_RCGR_ROOT_EN_SHFT                                                                           0x1
#define HWIO_LPASS_INT_MCLK0_CMD_RCGR_UPDATE_BMSK                                                                            0x1
#define HWIO_LPASS_INT_MCLK0_CMD_RCGR_UPDATE_SHFT                                                                            0x0

#define HWIO_LPASS_INT_MCLK0_CFG_RCGR_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x00053004)
#define HWIO_LPASS_INT_MCLK0_CFG_RCGR_OFFS                                                                            (LPASS_CC_REG_BASE_OFFS + 0x00053004)
#define HWIO_LPASS_INT_MCLK0_CFG_RCGR_RMSK                                                                                0x771f
#define HWIO_LPASS_INT_MCLK0_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_INT_MCLK0_CFG_RCGR_ADDR, HWIO_LPASS_INT_MCLK0_CFG_RCGR_RMSK)
#define HWIO_LPASS_INT_MCLK0_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_MCLK0_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_INT_MCLK0_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_INT_MCLK0_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_INT_MCLK0_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_MCLK0_CFG_RCGR_ADDR,m,v,HWIO_LPASS_INT_MCLK0_CFG_RCGR_IN)
#define HWIO_LPASS_INT_MCLK0_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                    0x4000
#define HWIO_LPASS_INT_MCLK0_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                       0xe
#define HWIO_LPASS_INT_MCLK0_CFG_RCGR_MODE_BMSK                                                                           0x3000
#define HWIO_LPASS_INT_MCLK0_CFG_RCGR_MODE_SHFT                                                                              0xc
#define HWIO_LPASS_INT_MCLK0_CFG_RCGR_SRC_SEL_BMSK                                                                         0x700
#define HWIO_LPASS_INT_MCLK0_CFG_RCGR_SRC_SEL_SHFT                                                                           0x8
#define HWIO_LPASS_INT_MCLK0_CFG_RCGR_SRC_DIV_BMSK                                                                          0x1f
#define HWIO_LPASS_INT_MCLK0_CFG_RCGR_SRC_DIV_SHFT                                                                           0x0

#define HWIO_LPASS_INT_MCLK0_M_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x00053008)
#define HWIO_LPASS_INT_MCLK0_M_OFFS                                                                                   (LPASS_CC_REG_BASE_OFFS + 0x00053008)
#define HWIO_LPASS_INT_MCLK0_M_RMSK                                                                                         0xff
#define HWIO_LPASS_INT_MCLK0_M_IN          \
        in_dword_masked(HWIO_LPASS_INT_MCLK0_M_ADDR, HWIO_LPASS_INT_MCLK0_M_RMSK)
#define HWIO_LPASS_INT_MCLK0_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_MCLK0_M_ADDR, m)
#define HWIO_LPASS_INT_MCLK0_M_OUT(v)      \
        out_dword(HWIO_LPASS_INT_MCLK0_M_ADDR,v)
#define HWIO_LPASS_INT_MCLK0_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_MCLK0_M_ADDR,m,v,HWIO_LPASS_INT_MCLK0_M_IN)
#define HWIO_LPASS_INT_MCLK0_M_M_BMSK                                                                                       0xff
#define HWIO_LPASS_INT_MCLK0_M_M_SHFT                                                                                        0x0

#define HWIO_LPASS_INT_MCLK0_N_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x0005300c)
#define HWIO_LPASS_INT_MCLK0_N_OFFS                                                                                   (LPASS_CC_REG_BASE_OFFS + 0x0005300c)
#define HWIO_LPASS_INT_MCLK0_N_RMSK                                                                                         0xff
#define HWIO_LPASS_INT_MCLK0_N_IN          \
        in_dword_masked(HWIO_LPASS_INT_MCLK0_N_ADDR, HWIO_LPASS_INT_MCLK0_N_RMSK)
#define HWIO_LPASS_INT_MCLK0_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_MCLK0_N_ADDR, m)
#define HWIO_LPASS_INT_MCLK0_N_OUT(v)      \
        out_dword(HWIO_LPASS_INT_MCLK0_N_ADDR,v)
#define HWIO_LPASS_INT_MCLK0_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_MCLK0_N_ADDR,m,v,HWIO_LPASS_INT_MCLK0_N_IN)
#define HWIO_LPASS_INT_MCLK0_N_NOT_N_MINUS_M_BMSK                                                                           0xff
#define HWIO_LPASS_INT_MCLK0_N_NOT_N_MINUS_M_SHFT                                                                            0x0

#define HWIO_LPASS_INT_MCLK0_D_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x00053010)
#define HWIO_LPASS_INT_MCLK0_D_OFFS                                                                                   (LPASS_CC_REG_BASE_OFFS + 0x00053010)
#define HWIO_LPASS_INT_MCLK0_D_RMSK                                                                                         0xff
#define HWIO_LPASS_INT_MCLK0_D_IN          \
        in_dword_masked(HWIO_LPASS_INT_MCLK0_D_ADDR, HWIO_LPASS_INT_MCLK0_D_RMSK)
#define HWIO_LPASS_INT_MCLK0_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_MCLK0_D_ADDR, m)
#define HWIO_LPASS_INT_MCLK0_D_OUT(v)      \
        out_dword(HWIO_LPASS_INT_MCLK0_D_ADDR,v)
#define HWIO_LPASS_INT_MCLK0_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_MCLK0_D_ADDR,m,v,HWIO_LPASS_INT_MCLK0_D_IN)
#define HWIO_LPASS_INT_MCLK0_D_NOT_2D_BMSK                                                                                  0xff
#define HWIO_LPASS_INT_MCLK0_D_NOT_2D_SHFT                                                                                   0x0

#define HWIO_LPASS_AUDIO_CORE_INT_MCLK0_CBCR_ADDR                                                                     (LPASS_CC_REG_BASE      + 0x00053014)
#define HWIO_LPASS_AUDIO_CORE_INT_MCLK0_CBCR_OFFS                                                                     (LPASS_CC_REG_BASE_OFFS + 0x00053014)
#define HWIO_LPASS_AUDIO_CORE_INT_MCLK0_CBCR_RMSK                                                                     0x80000003
#define HWIO_LPASS_AUDIO_CORE_INT_MCLK0_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_MCLK0_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_INT_MCLK0_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_INT_MCLK0_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_MCLK0_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_INT_MCLK0_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_INT_MCLK0_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_INT_MCLK0_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_INT_MCLK0_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_INT_MCLK0_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_INT_MCLK0_CBCR_CLK_OFF_BMSK                                                             0x80000000
#define HWIO_LPASS_AUDIO_CORE_INT_MCLK0_CBCR_CLK_OFF_SHFT                                                                   0x1f
#define HWIO_LPASS_AUDIO_CORE_INT_MCLK0_CBCR_HW_CTL_BMSK                                                                     0x2
#define HWIO_LPASS_AUDIO_CORE_INT_MCLK0_CBCR_HW_CTL_SHFT                                                                     0x1
#define HWIO_LPASS_AUDIO_CORE_INT_MCLK0_CBCR_CLK_ENABLE_BMSK                                                                 0x1
#define HWIO_LPASS_AUDIO_CORE_INT_MCLK0_CBCR_CLK_ENABLE_SHFT                                                                 0x0

#define HWIO_LPASS_INT_MCLK1_CMD_RCGR_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x00054000)
#define HWIO_LPASS_INT_MCLK1_CMD_RCGR_OFFS                                                                            (LPASS_CC_REG_BASE_OFFS + 0x00054000)
#define HWIO_LPASS_INT_MCLK1_CMD_RCGR_RMSK                                                                            0x800000f3
#define HWIO_LPASS_INT_MCLK1_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_INT_MCLK1_CMD_RCGR_ADDR, HWIO_LPASS_INT_MCLK1_CMD_RCGR_RMSK)
#define HWIO_LPASS_INT_MCLK1_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_MCLK1_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_INT_MCLK1_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_INT_MCLK1_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_INT_MCLK1_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_MCLK1_CMD_RCGR_ADDR,m,v,HWIO_LPASS_INT_MCLK1_CMD_RCGR_IN)
#define HWIO_LPASS_INT_MCLK1_CMD_RCGR_ROOT_OFF_BMSK                                                                   0x80000000
#define HWIO_LPASS_INT_MCLK1_CMD_RCGR_ROOT_OFF_SHFT                                                                         0x1f
#define HWIO_LPASS_INT_MCLK1_CMD_RCGR_DIRTY_D_BMSK                                                                          0x80
#define HWIO_LPASS_INT_MCLK1_CMD_RCGR_DIRTY_D_SHFT                                                                           0x7
#define HWIO_LPASS_INT_MCLK1_CMD_RCGR_DIRTY_N_BMSK                                                                          0x40
#define HWIO_LPASS_INT_MCLK1_CMD_RCGR_DIRTY_N_SHFT                                                                           0x6
#define HWIO_LPASS_INT_MCLK1_CMD_RCGR_DIRTY_M_BMSK                                                                          0x20
#define HWIO_LPASS_INT_MCLK1_CMD_RCGR_DIRTY_M_SHFT                                                                           0x5
#define HWIO_LPASS_INT_MCLK1_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                   0x10
#define HWIO_LPASS_INT_MCLK1_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                    0x4
#define HWIO_LPASS_INT_MCLK1_CMD_RCGR_ROOT_EN_BMSK                                                                           0x2
#define HWIO_LPASS_INT_MCLK1_CMD_RCGR_ROOT_EN_SHFT                                                                           0x1
#define HWIO_LPASS_INT_MCLK1_CMD_RCGR_UPDATE_BMSK                                                                            0x1
#define HWIO_LPASS_INT_MCLK1_CMD_RCGR_UPDATE_SHFT                                                                            0x0

#define HWIO_LPASS_INT_MCLK1_CFG_RCGR_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x00054004)
#define HWIO_LPASS_INT_MCLK1_CFG_RCGR_OFFS                                                                            (LPASS_CC_REG_BASE_OFFS + 0x00054004)
#define HWIO_LPASS_INT_MCLK1_CFG_RCGR_RMSK                                                                                0x771f
#define HWIO_LPASS_INT_MCLK1_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_INT_MCLK1_CFG_RCGR_ADDR, HWIO_LPASS_INT_MCLK1_CFG_RCGR_RMSK)
#define HWIO_LPASS_INT_MCLK1_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_MCLK1_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_INT_MCLK1_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_INT_MCLK1_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_INT_MCLK1_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_MCLK1_CFG_RCGR_ADDR,m,v,HWIO_LPASS_INT_MCLK1_CFG_RCGR_IN)
#define HWIO_LPASS_INT_MCLK1_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                    0x4000
#define HWIO_LPASS_INT_MCLK1_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                       0xe
#define HWIO_LPASS_INT_MCLK1_CFG_RCGR_MODE_BMSK                                                                           0x3000
#define HWIO_LPASS_INT_MCLK1_CFG_RCGR_MODE_SHFT                                                                              0xc
#define HWIO_LPASS_INT_MCLK1_CFG_RCGR_SRC_SEL_BMSK                                                                         0x700
#define HWIO_LPASS_INT_MCLK1_CFG_RCGR_SRC_SEL_SHFT                                                                           0x8
#define HWIO_LPASS_INT_MCLK1_CFG_RCGR_SRC_DIV_BMSK                                                                          0x1f
#define HWIO_LPASS_INT_MCLK1_CFG_RCGR_SRC_DIV_SHFT                                                                           0x0

#define HWIO_LPASS_INT_MCLK1_M_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x00054008)
#define HWIO_LPASS_INT_MCLK1_M_OFFS                                                                                   (LPASS_CC_REG_BASE_OFFS + 0x00054008)
#define HWIO_LPASS_INT_MCLK1_M_RMSK                                                                                         0xff
#define HWIO_LPASS_INT_MCLK1_M_IN          \
        in_dword_masked(HWIO_LPASS_INT_MCLK1_M_ADDR, HWIO_LPASS_INT_MCLK1_M_RMSK)
#define HWIO_LPASS_INT_MCLK1_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_MCLK1_M_ADDR, m)
#define HWIO_LPASS_INT_MCLK1_M_OUT(v)      \
        out_dword(HWIO_LPASS_INT_MCLK1_M_ADDR,v)
#define HWIO_LPASS_INT_MCLK1_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_MCLK1_M_ADDR,m,v,HWIO_LPASS_INT_MCLK1_M_IN)
#define HWIO_LPASS_INT_MCLK1_M_M_BMSK                                                                                       0xff
#define HWIO_LPASS_INT_MCLK1_M_M_SHFT                                                                                        0x0

#define HWIO_LPASS_INT_MCLK1_N_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x0005400c)
#define HWIO_LPASS_INT_MCLK1_N_OFFS                                                                                   (LPASS_CC_REG_BASE_OFFS + 0x0005400c)
#define HWIO_LPASS_INT_MCLK1_N_RMSK                                                                                         0xff
#define HWIO_LPASS_INT_MCLK1_N_IN          \
        in_dword_masked(HWIO_LPASS_INT_MCLK1_N_ADDR, HWIO_LPASS_INT_MCLK1_N_RMSK)
#define HWIO_LPASS_INT_MCLK1_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_MCLK1_N_ADDR, m)
#define HWIO_LPASS_INT_MCLK1_N_OUT(v)      \
        out_dword(HWIO_LPASS_INT_MCLK1_N_ADDR,v)
#define HWIO_LPASS_INT_MCLK1_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_MCLK1_N_ADDR,m,v,HWIO_LPASS_INT_MCLK1_N_IN)
#define HWIO_LPASS_INT_MCLK1_N_NOT_N_MINUS_M_BMSK                                                                           0xff
#define HWIO_LPASS_INT_MCLK1_N_NOT_N_MINUS_M_SHFT                                                                            0x0

#define HWIO_LPASS_INT_MCLK1_D_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x00054010)
#define HWIO_LPASS_INT_MCLK1_D_OFFS                                                                                   (LPASS_CC_REG_BASE_OFFS + 0x00054010)
#define HWIO_LPASS_INT_MCLK1_D_RMSK                                                                                         0xff
#define HWIO_LPASS_INT_MCLK1_D_IN          \
        in_dword_masked(HWIO_LPASS_INT_MCLK1_D_ADDR, HWIO_LPASS_INT_MCLK1_D_RMSK)
#define HWIO_LPASS_INT_MCLK1_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_MCLK1_D_ADDR, m)
#define HWIO_LPASS_INT_MCLK1_D_OUT(v)      \
        out_dword(HWIO_LPASS_INT_MCLK1_D_ADDR,v)
#define HWIO_LPASS_INT_MCLK1_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_MCLK1_D_ADDR,m,v,HWIO_LPASS_INT_MCLK1_D_IN)
#define HWIO_LPASS_INT_MCLK1_D_NOT_2D_BMSK                                                                                  0xff
#define HWIO_LPASS_INT_MCLK1_D_NOT_2D_SHFT                                                                                   0x0

#define HWIO_LPASS_AUDIO_CORE_INT_MCLK1_CBCR_ADDR                                                                     (LPASS_CC_REG_BASE      + 0x00054014)
#define HWIO_LPASS_AUDIO_CORE_INT_MCLK1_CBCR_OFFS                                                                     (LPASS_CC_REG_BASE_OFFS + 0x00054014)
#define HWIO_LPASS_AUDIO_CORE_INT_MCLK1_CBCR_RMSK                                                                     0x80000003
#define HWIO_LPASS_AUDIO_CORE_INT_MCLK1_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_MCLK1_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_INT_MCLK1_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_INT_MCLK1_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_MCLK1_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_INT_MCLK1_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_INT_MCLK1_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_INT_MCLK1_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_INT_MCLK1_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_INT_MCLK1_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_INT_MCLK1_CBCR_CLK_OFF_BMSK                                                             0x80000000
#define HWIO_LPASS_AUDIO_CORE_INT_MCLK1_CBCR_CLK_OFF_SHFT                                                                   0x1f
#define HWIO_LPASS_AUDIO_CORE_INT_MCLK1_CBCR_HW_CTL_BMSK                                                                     0x2
#define HWIO_LPASS_AUDIO_CORE_INT_MCLK1_CBCR_HW_CTL_SHFT                                                                     0x1
#define HWIO_LPASS_AUDIO_CORE_INT_MCLK1_CBCR_CLK_ENABLE_BMSK                                                                 0x1
#define HWIO_LPASS_AUDIO_CORE_INT_MCLK1_CBCR_CLK_ENABLE_SHFT                                                                 0x0

#define HWIO_LPASS_ISLAND_SCC_UART4_BCR_ADDR                                                                          (LPASS_CC_REG_BASE      + 0x00055000)
#define HWIO_LPASS_ISLAND_SCC_UART4_BCR_OFFS                                                                          (LPASS_CC_REG_BASE_OFFS + 0x00055000)
#define HWIO_LPASS_ISLAND_SCC_UART4_BCR_RMSK                                                                                 0x1
#define HWIO_LPASS_ISLAND_SCC_UART4_BCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_UART4_BCR_ADDR, HWIO_LPASS_ISLAND_SCC_UART4_BCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_UART4_BCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_UART4_BCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_UART4_BCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_UART4_BCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_UART4_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_UART4_BCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_UART4_BCR_IN)
#define HWIO_LPASS_ISLAND_SCC_UART4_BCR_BLK_ARES_BMSK                                                                        0x1
#define HWIO_LPASS_ISLAND_SCC_UART4_BCR_BLK_ARES_SHFT                                                                        0x0

#define HWIO_LPASS_SCC_UART4_CMD_RCGR_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x00055004)
#define HWIO_LPASS_SCC_UART4_CMD_RCGR_OFFS                                                                            (LPASS_CC_REG_BASE_OFFS + 0x00055004)
#define HWIO_LPASS_SCC_UART4_CMD_RCGR_RMSK                                                                            0x800000f3
#define HWIO_LPASS_SCC_UART4_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_SCC_UART4_CMD_RCGR_ADDR, HWIO_LPASS_SCC_UART4_CMD_RCGR_RMSK)
#define HWIO_LPASS_SCC_UART4_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_UART4_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_SCC_UART4_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_UART4_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_SCC_UART4_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_UART4_CMD_RCGR_ADDR,m,v,HWIO_LPASS_SCC_UART4_CMD_RCGR_IN)
#define HWIO_LPASS_SCC_UART4_CMD_RCGR_ROOT_OFF_BMSK                                                                   0x80000000
#define HWIO_LPASS_SCC_UART4_CMD_RCGR_ROOT_OFF_SHFT                                                                         0x1f
#define HWIO_LPASS_SCC_UART4_CMD_RCGR_DIRTY_D_BMSK                                                                          0x80
#define HWIO_LPASS_SCC_UART4_CMD_RCGR_DIRTY_D_SHFT                                                                           0x7
#define HWIO_LPASS_SCC_UART4_CMD_RCGR_DIRTY_N_BMSK                                                                          0x40
#define HWIO_LPASS_SCC_UART4_CMD_RCGR_DIRTY_N_SHFT                                                                           0x6
#define HWIO_LPASS_SCC_UART4_CMD_RCGR_DIRTY_M_BMSK                                                                          0x20
#define HWIO_LPASS_SCC_UART4_CMD_RCGR_DIRTY_M_SHFT                                                                           0x5
#define HWIO_LPASS_SCC_UART4_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                   0x10
#define HWIO_LPASS_SCC_UART4_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                    0x4
#define HWIO_LPASS_SCC_UART4_CMD_RCGR_ROOT_EN_BMSK                                                                           0x2
#define HWIO_LPASS_SCC_UART4_CMD_RCGR_ROOT_EN_SHFT                                                                           0x1
#define HWIO_LPASS_SCC_UART4_CMD_RCGR_UPDATE_BMSK                                                                            0x1
#define HWIO_LPASS_SCC_UART4_CMD_RCGR_UPDATE_SHFT                                                                            0x0

#define HWIO_LPASS_SCC_UART4_CFG_RCGR_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x00055008)
#define HWIO_LPASS_SCC_UART4_CFG_RCGR_OFFS                                                                            (LPASS_CC_REG_BASE_OFFS + 0x00055008)
#define HWIO_LPASS_SCC_UART4_CFG_RCGR_RMSK                                                                                0x771f
#define HWIO_LPASS_SCC_UART4_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_SCC_UART4_CFG_RCGR_ADDR, HWIO_LPASS_SCC_UART4_CFG_RCGR_RMSK)
#define HWIO_LPASS_SCC_UART4_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_UART4_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_SCC_UART4_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_UART4_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_SCC_UART4_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_UART4_CFG_RCGR_ADDR,m,v,HWIO_LPASS_SCC_UART4_CFG_RCGR_IN)
#define HWIO_LPASS_SCC_UART4_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                    0x4000
#define HWIO_LPASS_SCC_UART4_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                       0xe
#define HWIO_LPASS_SCC_UART4_CFG_RCGR_MODE_BMSK                                                                           0x3000
#define HWIO_LPASS_SCC_UART4_CFG_RCGR_MODE_SHFT                                                                              0xc
#define HWIO_LPASS_SCC_UART4_CFG_RCGR_SRC_SEL_BMSK                                                                         0x700
#define HWIO_LPASS_SCC_UART4_CFG_RCGR_SRC_SEL_SHFT                                                                           0x8
#define HWIO_LPASS_SCC_UART4_CFG_RCGR_SRC_DIV_BMSK                                                                          0x1f
#define HWIO_LPASS_SCC_UART4_CFG_RCGR_SRC_DIV_SHFT                                                                           0x0

#define HWIO_LPASS_SCC_UART4_M_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x0005500c)
#define HWIO_LPASS_SCC_UART4_M_OFFS                                                                                   (LPASS_CC_REG_BASE_OFFS + 0x0005500c)
#define HWIO_LPASS_SCC_UART4_M_RMSK                                                                                       0xffff
#define HWIO_LPASS_SCC_UART4_M_IN          \
        in_dword_masked(HWIO_LPASS_SCC_UART4_M_ADDR, HWIO_LPASS_SCC_UART4_M_RMSK)
#define HWIO_LPASS_SCC_UART4_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_UART4_M_ADDR, m)
#define HWIO_LPASS_SCC_UART4_M_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_UART4_M_ADDR,v)
#define HWIO_LPASS_SCC_UART4_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_UART4_M_ADDR,m,v,HWIO_LPASS_SCC_UART4_M_IN)
#define HWIO_LPASS_SCC_UART4_M_M_BMSK                                                                                     0xffff
#define HWIO_LPASS_SCC_UART4_M_M_SHFT                                                                                        0x0

#define HWIO_LPASS_SCC_UART4_N_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x00055010)
#define HWIO_LPASS_SCC_UART4_N_OFFS                                                                                   (LPASS_CC_REG_BASE_OFFS + 0x00055010)
#define HWIO_LPASS_SCC_UART4_N_RMSK                                                                                       0xffff
#define HWIO_LPASS_SCC_UART4_N_IN          \
        in_dword_masked(HWIO_LPASS_SCC_UART4_N_ADDR, HWIO_LPASS_SCC_UART4_N_RMSK)
#define HWIO_LPASS_SCC_UART4_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_UART4_N_ADDR, m)
#define HWIO_LPASS_SCC_UART4_N_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_UART4_N_ADDR,v)
#define HWIO_LPASS_SCC_UART4_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_UART4_N_ADDR,m,v,HWIO_LPASS_SCC_UART4_N_IN)
#define HWIO_LPASS_SCC_UART4_N_NOT_N_MINUS_M_BMSK                                                                         0xffff
#define HWIO_LPASS_SCC_UART4_N_NOT_N_MINUS_M_SHFT                                                                            0x0

#define HWIO_LPASS_SCC_UART4_D_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x00055014)
#define HWIO_LPASS_SCC_UART4_D_OFFS                                                                                   (LPASS_CC_REG_BASE_OFFS + 0x00055014)
#define HWIO_LPASS_SCC_UART4_D_RMSK                                                                                       0xffff
#define HWIO_LPASS_SCC_UART4_D_IN          \
        in_dword_masked(HWIO_LPASS_SCC_UART4_D_ADDR, HWIO_LPASS_SCC_UART4_D_RMSK)
#define HWIO_LPASS_SCC_UART4_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_UART4_D_ADDR, m)
#define HWIO_LPASS_SCC_UART4_D_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_UART4_D_ADDR,v)
#define HWIO_LPASS_SCC_UART4_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_UART4_D_ADDR,m,v,HWIO_LPASS_SCC_UART4_D_IN)
#define HWIO_LPASS_SCC_UART4_D_NOT_2D_BMSK                                                                                0xffff
#define HWIO_LPASS_SCC_UART4_D_NOT_2D_SHFT                                                                                   0x0

#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART4_CBCR_ADDR                                                                 (LPASS_CC_REG_BASE      + 0x00055018)
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART4_CBCR_OFFS                                                                 (LPASS_CC_REG_BASE_OFFS + 0x00055018)
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART4_CBCR_RMSK                                                                 0x80000001
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART4_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_UART_DM_UART4_CBCR_ADDR, HWIO_LPASS_ISLAND_SCC_UART_DM_UART4_CBCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART4_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_UART_DM_UART4_CBCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART4_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_UART_DM_UART4_CBCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART4_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_UART_DM_UART4_CBCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_UART_DM_UART4_CBCR_IN)
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART4_CBCR_CLK_OFF_BMSK                                                         0x80000000
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART4_CBCR_CLK_OFF_SHFT                                                               0x1f
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART4_CBCR_CLK_ENABLE_BMSK                                                             0x1
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART4_CBCR_CLK_ENABLE_SHFT                                                             0x0

#define HWIO_LPASS_ISLAND_MODE_SMMU_CTRL_ADDR                                                                         (LPASS_CC_REG_BASE      + 0x00056000)
#define HWIO_LPASS_ISLAND_MODE_SMMU_CTRL_OFFS                                                                         (LPASS_CC_REG_BASE_OFFS + 0x00056000)
#define HWIO_LPASS_ISLAND_MODE_SMMU_CTRL_RMSK                                                                                0x1
#define HWIO_LPASS_ISLAND_MODE_SMMU_CTRL_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_MODE_SMMU_CTRL_ADDR, HWIO_LPASS_ISLAND_MODE_SMMU_CTRL_RMSK)
#define HWIO_LPASS_ISLAND_MODE_SMMU_CTRL_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_MODE_SMMU_CTRL_ADDR, m)
#define HWIO_LPASS_ISLAND_MODE_SMMU_CTRL_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_MODE_SMMU_CTRL_ADDR,v)
#define HWIO_LPASS_ISLAND_MODE_SMMU_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_MODE_SMMU_CTRL_ADDR,m,v,HWIO_LPASS_ISLAND_MODE_SMMU_CTRL_IN)
#define HWIO_LPASS_ISLAND_MODE_SMMU_CTRL_ISLAND_MODE_ENTRY_ENABLE_BMSK                                                       0x1
#define HWIO_LPASS_ISLAND_MODE_SMMU_CTRL_ISLAND_MODE_ENTRY_ENABLE_SHFT                                                       0x0

#define HWIO_LPASS_DBG_CLK_ADDR                                                                                       (LPASS_CC_REG_BASE      + 0x00057000)
#define HWIO_LPASS_DBG_CLK_OFFS                                                                                       (LPASS_CC_REG_BASE_OFFS + 0x00057000)
#define HWIO_LPASS_DBG_CLK_RMSK                                                                                       0xfff0ffff
#define HWIO_LPASS_DBG_CLK_IN          \
        in_dword_masked(HWIO_LPASS_DBG_CLK_ADDR, HWIO_LPASS_DBG_CLK_RMSK)
#define HWIO_LPASS_DBG_CLK_INM(m)      \
        in_dword_masked(HWIO_LPASS_DBG_CLK_ADDR, m)
#define HWIO_LPASS_DBG_CLK_OUT(v)      \
        out_dword(HWIO_LPASS_DBG_CLK_ADDR,v)
#define HWIO_LPASS_DBG_CLK_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DBG_CLK_ADDR,m,v,HWIO_LPASS_DBG_CLK_IN)
#define HWIO_LPASS_DBG_CLK_RESETN_MUX_SEL_BMSK                                                                        0xe0000000
#define HWIO_LPASS_DBG_CLK_RESETN_MUX_SEL_SHFT                                                                              0x1d
#define HWIO_LPASS_DBG_CLK_BYPASSNL_MUX_SEL_BMSK                                                                      0x1c000000
#define HWIO_LPASS_DBG_CLK_BYPASSNL_MUX_SEL_SHFT                                                                            0x1a
#define HWIO_LPASS_DBG_CLK_RESERVE_BITS25_21_BMSK                                                                      0x3e00000
#define HWIO_LPASS_DBG_CLK_RESERVE_BITS25_21_SHFT                                                                           0x15
#define HWIO_LPASS_DBG_CLK_DBG_CLK_ENABLE_BMSK                                                                          0x100000
#define HWIO_LPASS_DBG_CLK_DBG_CLK_ENABLE_SHFT                                                                              0x14
#define HWIO_LPASS_DBG_CLK_DBG_CLK_MUX_SEL_BMSK                                                                           0xffff
#define HWIO_LPASS_DBG_CLK_DBG_CLK_MUX_SEL_SHFT                                                                              0x0

#define HWIO_LPASS_TEST_BUS_SEL_ADDR                                                                                  (LPASS_CC_REG_BASE      + 0x00057004)
#define HWIO_LPASS_TEST_BUS_SEL_OFFS                                                                                  (LPASS_CC_REG_BASE_OFFS + 0x00057004)
#define HWIO_LPASS_TEST_BUS_SEL_RMSK                                                                                         0x7
#define HWIO_LPASS_TEST_BUS_SEL_IN          \
        in_dword_masked(HWIO_LPASS_TEST_BUS_SEL_ADDR, HWIO_LPASS_TEST_BUS_SEL_RMSK)
#define HWIO_LPASS_TEST_BUS_SEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_TEST_BUS_SEL_ADDR, m)
#define HWIO_LPASS_TEST_BUS_SEL_OUT(v)      \
        out_dword(HWIO_LPASS_TEST_BUS_SEL_ADDR,v)
#define HWIO_LPASS_TEST_BUS_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_TEST_BUS_SEL_ADDR,m,v,HWIO_LPASS_TEST_BUS_SEL_IN)
#define HWIO_LPASS_TEST_BUS_SEL_SEL_BMSK                                                                                     0x7
#define HWIO_LPASS_TEST_BUS_SEL_SEL_SHFT                                                                                     0x0

#define HWIO_LPASS_PLLOUT_LV_TEST_SEL_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x00057008)
#define HWIO_LPASS_PLLOUT_LV_TEST_SEL_OFFS                                                                            (LPASS_CC_REG_BASE_OFFS + 0x00057008)
#define HWIO_LPASS_PLLOUT_LV_TEST_SEL_RMSK                                                                                   0x3
#define HWIO_LPASS_PLLOUT_LV_TEST_SEL_IN          \
        in_dword_masked(HWIO_LPASS_PLLOUT_LV_TEST_SEL_ADDR, HWIO_LPASS_PLLOUT_LV_TEST_SEL_RMSK)
#define HWIO_LPASS_PLLOUT_LV_TEST_SEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_PLLOUT_LV_TEST_SEL_ADDR, m)
#define HWIO_LPASS_PLLOUT_LV_TEST_SEL_OUT(v)      \
        out_dword(HWIO_LPASS_PLLOUT_LV_TEST_SEL_ADDR,v)
#define HWIO_LPASS_PLLOUT_LV_TEST_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_PLLOUT_LV_TEST_SEL_ADDR,m,v,HWIO_LPASS_PLLOUT_LV_TEST_SEL_IN)
#define HWIO_LPASS_PLLOUT_LV_TEST_SEL_SEL_BMSK                                                                               0x3
#define HWIO_LPASS_PLLOUT_LV_TEST_SEL_SEL_SHFT                                                                               0x0

#define HWIO_LPASS_LPASS_CC_SPARE_REG_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x0005700c)
#define HWIO_LPASS_LPASS_CC_SPARE_REG_OFFS                                                                            (LPASS_CC_REG_BASE_OFFS + 0x0005700c)
#define HWIO_LPASS_LPASS_CC_SPARE_REG_RMSK                                                                            0xffffffff
#define HWIO_LPASS_LPASS_CC_SPARE_REG_IN          \
        in_dword_masked(HWIO_LPASS_LPASS_CC_SPARE_REG_ADDR, HWIO_LPASS_LPASS_CC_SPARE_REG_RMSK)
#define HWIO_LPASS_LPASS_CC_SPARE_REG_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPASS_CC_SPARE_REG_ADDR, m)
#define HWIO_LPASS_LPASS_CC_SPARE_REG_OUT(v)      \
        out_dword(HWIO_LPASS_LPASS_CC_SPARE_REG_ADDR,v)
#define HWIO_LPASS_LPASS_CC_SPARE_REG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPASS_CC_SPARE_REG_ADDR,m,v,HWIO_LPASS_LPASS_CC_SPARE_REG_IN)
#define HWIO_LPASS_LPASS_CC_SPARE_REG_SPARE_BMSK                                                                      0xffffffff
#define HWIO_LPASS_LPASS_CC_SPARE_REG_SPARE_SHFT                                                                             0x0

#define HWIO_LPASS_LPASS_CC_SPARE1_REG_ADDR                                                                           (LPASS_CC_REG_BASE      + 0x00057010)
#define HWIO_LPASS_LPASS_CC_SPARE1_REG_OFFS                                                                           (LPASS_CC_REG_BASE_OFFS + 0x00057010)
#define HWIO_LPASS_LPASS_CC_SPARE1_REG_RMSK                                                                           0xffffffff
#define HWIO_LPASS_LPASS_CC_SPARE1_REG_IN          \
        in_dword_masked(HWIO_LPASS_LPASS_CC_SPARE1_REG_ADDR, HWIO_LPASS_LPASS_CC_SPARE1_REG_RMSK)
#define HWIO_LPASS_LPASS_CC_SPARE1_REG_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPASS_CC_SPARE1_REG_ADDR, m)
#define HWIO_LPASS_LPASS_CC_SPARE1_REG_OUT(v)      \
        out_dword(HWIO_LPASS_LPASS_CC_SPARE1_REG_ADDR,v)
#define HWIO_LPASS_LPASS_CC_SPARE1_REG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPASS_CC_SPARE1_REG_ADDR,m,v,HWIO_LPASS_LPASS_CC_SPARE1_REG_IN)
#define HWIO_LPASS_LPASS_CC_SPARE1_REG_SPARE1_BMSK                                                                    0xffffffff
#define HWIO_LPASS_LPASS_CC_SPARE1_REG_SPARE1_SHFT                                                                           0x0


#endif /* __HWIO_H__ */

