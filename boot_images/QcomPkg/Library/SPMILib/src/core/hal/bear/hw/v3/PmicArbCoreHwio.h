#ifndef __PMICARBCOREHWIO_H__
#define __PMICARBCOREHWIO_H__
/*
===========================================================================
*/
/**
  @file PmicArbCoreHwio.h
  @brief Auto-generated HWIO interface include file.

  Reference chip release:
    MSM8998 (Nazgul) [nazgul_v1.0_p1q1r17.1.0]
 
  This file contains HWIO register definitions for the following modules:
    PMIC_ARB_CORE
    PMIC_ARB_CORE_REGISTERS
    PMIC_ARB_CORE_REGISTERS_OBS
    PMIC_ARB_MPU1132_18_M25L12_AHB

  'Include' filters applied: 
  'Exclude' filters applied: RESERVED DUMMY 
*/
/*
  ===========================================================================

  Copyright (c) 2015 Qualcomm Technologies Incorporated.
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

  $Header: //components/rel/boot.xf/1.4/QcomPkg/Library/SPMILib/src/core/hal/bear/hw/v3/PmicArbCoreHwio.h#2 $
  $DateTime: 2016/08/19 05:58:45 $
  $Author: c_mvanim $

  ===========================================================================
*/

/*----------------------------------------------------------------------------
 * MODULE: PMIC_ARB_CORE
 *--------------------------------------------------------------------------*/

#define PMIC_ARB_CORE_REG_BASE                                        (PMIC_ARB_BASE      + 0x0000f000)
#define PMIC_ARB_CORE_REG_BASE_OFFS                                   0x0000f000

#define HWIO_PMIC_ARB_HW_VERSION_ADDR(x)                              ((x) + PMIC_ARB_CORE_REG_BASE_OFFS + 0x00000000)
#define HWIO_PMIC_ARB_HW_VERSION_OFFS                                 (0x00000000)
#define HWIO_PMIC_ARB_HW_VERSION_RMSK                                 0xffffffff
#define HWIO_PMIC_ARB_HW_VERSION_IN(x)      \
        in_dword_masked(HWIO_PMIC_ARB_HW_VERSION_ADDR(x), HWIO_PMIC_ARB_HW_VERSION_RMSK)
#define HWIO_PMIC_ARB_HW_VERSION_INM(x, m)      \
        in_dword_masked(HWIO_PMIC_ARB_HW_VERSION_ADDR(x), m)
#define HWIO_PMIC_ARB_HW_VERSION_MAJOR_BMSK                           0xf0000000
#define HWIO_PMIC_ARB_HW_VERSION_MAJOR_SHFT                                 0x1c
#define HWIO_PMIC_ARB_HW_VERSION_MINOR_BMSK                            0xfff0000
#define HWIO_PMIC_ARB_HW_VERSION_MINOR_SHFT                                 0x10
#define HWIO_PMIC_ARB_HW_VERSION_STEP_BMSK                                0xffff
#define HWIO_PMIC_ARB_HW_VERSION_STEP_SHFT                                   0x0

#define HWIO_PMIC_ARB_MISC_CONFIG_ADDR(x)                             ((x) + PMIC_ARB_CORE_REG_BASE_OFFS + 0x00000004)
#define HWIO_PMIC_ARB_MISC_CONFIG_OFFS                                (0x00000004)
#define HWIO_PMIC_ARB_MISC_CONFIG_RMSK                                       0x7
#define HWIO_PMIC_ARB_MISC_CONFIG_IN(x)      \
        in_dword_masked(HWIO_PMIC_ARB_MISC_CONFIG_ADDR(x), HWIO_PMIC_ARB_MISC_CONFIG_RMSK)
#define HWIO_PMIC_ARB_MISC_CONFIG_INM(x, m)      \
        in_dword_masked(HWIO_PMIC_ARB_MISC_CONFIG_ADDR(x), m)
#define HWIO_PMIC_ARB_MISC_CONFIG_OUT(x, v)      \
        out_dword(HWIO_PMIC_ARB_MISC_CONFIG_ADDR(x),v)
#define HWIO_PMIC_ARB_MISC_CONFIG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PMIC_ARB_MISC_CONFIG_ADDR(x),m,v,HWIO_PMIC_ARB_MISC_CONFIG_IN(x))
#define HWIO_PMIC_ARB_MISC_CONFIG_TEST_BUS_EN_BMSK                           0x4
#define HWIO_PMIC_ARB_MISC_CONFIG_TEST_BUS_EN_SHFT                           0x2
#define HWIO_PMIC_ARB_MISC_CONFIG_CLK_GATE_EN_BMSK                           0x2
#define HWIO_PMIC_ARB_MISC_CONFIG_CLK_GATE_EN_SHFT                           0x1
#define HWIO_PMIC_ARB_MISC_CONFIG_DONE_IRQ_EN_BMSK                           0x1
#define HWIO_PMIC_ARB_MISC_CONFIG_DONE_IRQ_EN_SHFT                           0x0

#define HWIO_PMIC_ARB_PVC_INTF_CTL_ADDR(x)                            ((x) + PMIC_ARB_CORE_REG_BASE_OFFS + 0x00000008)
#define HWIO_PMIC_ARB_PVC_INTF_CTL_OFFS                               (0x00000008)
#define HWIO_PMIC_ARB_PVC_INTF_CTL_RMSK                                      0x1
#define HWIO_PMIC_ARB_PVC_INTF_CTL_IN(x)      \
        in_dword_masked(HWIO_PMIC_ARB_PVC_INTF_CTL_ADDR(x), HWIO_PMIC_ARB_PVC_INTF_CTL_RMSK)
#define HWIO_PMIC_ARB_PVC_INTF_CTL_INM(x, m)      \
        in_dword_masked(HWIO_PMIC_ARB_PVC_INTF_CTL_ADDR(x), m)
#define HWIO_PMIC_ARB_PVC_INTF_CTL_OUT(x, v)      \
        out_dword(HWIO_PMIC_ARB_PVC_INTF_CTL_ADDR(x),v)
#define HWIO_PMIC_ARB_PVC_INTF_CTL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PMIC_ARB_PVC_INTF_CTL_ADDR(x),m,v,HWIO_PMIC_ARB_PVC_INTF_CTL_IN(x))
#define HWIO_PMIC_ARB_PVC_INTF_CTL_PVC_INTF_EN_BMSK                          0x1
#define HWIO_PMIC_ARB_PVC_INTF_CTL_PVC_INTF_EN_SHFT                          0x0

#define HWIO_PMIC_ARB_PVC_INTF_STATUS_ADDR(x)                         ((x) + PMIC_ARB_CORE_REG_BASE_OFFS + 0x0000000c)
#define HWIO_PMIC_ARB_PVC_INTF_STATUS_OFFS                            (0x0000000c)
#define HWIO_PMIC_ARB_PVC_INTF_STATUS_RMSK                                   0x1
#define HWIO_PMIC_ARB_PVC_INTF_STATUS_IN(x)      \
        in_dword_masked(HWIO_PMIC_ARB_PVC_INTF_STATUS_ADDR(x), HWIO_PMIC_ARB_PVC_INTF_STATUS_RMSK)
#define HWIO_PMIC_ARB_PVC_INTF_STATUS_INM(x, m)      \
        in_dword_masked(HWIO_PMIC_ARB_PVC_INTF_STATUS_ADDR(x), m)
#define HWIO_PMIC_ARB_PVC_INTF_STATUS_PVC_INTF_BUSY_BMSK                     0x1
#define HWIO_PMIC_ARB_PVC_INTF_STATUS_PVC_INTF_BUSY_SHFT                     0x0

#define HWIO_PMIC_ARB_PRIORITIESn_ADDR(base,n)                        ((base) + PMIC_ARB_CORE_REG_BASE_OFFS + 0x00000100 + 0x4 * (n))
#define HWIO_PMIC_ARB_PRIORITIESn_OFFS(base,n)                        (0x00000100 + 0x4 * (n))
#define HWIO_PMIC_ARB_PRIORITIESn_RMSK                                       0x7
#define HWIO_PMIC_ARB_PRIORITIESn_INI(base,n)        \
        in_dword_masked(HWIO_PMIC_ARB_PRIORITIESn_ADDR(base,n), HWIO_PMIC_ARB_PRIORITIESn_RMSK)
#define HWIO_PMIC_ARB_PRIORITIESn_INMI(base,n,mask)    \
        in_dword_masked(HWIO_PMIC_ARB_PRIORITIESn_ADDR(base,n), mask)
#define HWIO_PMIC_ARB_PRIORITIESn_OUTI(base,n,val)    \
        out_dword(HWIO_PMIC_ARB_PRIORITIESn_ADDR(base,n),val)
#define HWIO_PMIC_ARB_PRIORITIESn_OUTMI(base,n,mask,val) \
        out_dword_masked_ns(HWIO_PMIC_ARB_PRIORITIESn_ADDR(base,n),mask,val,HWIO_PMIC_ARB_PRIORITIESn_INI(base,n))
#define HWIO_PMIC_ARB_PRIORITIESn_PORT_BMSK                                  0x7
#define HWIO_PMIC_ARB_PRIORITIESn_PORT_SHFT                                  0x0

#define HWIO_PMIC_ARB_PVC_PORTn_CTL_ADDR(base,n)                      ((base) + PMIC_ARB_CORE_REG_BASE_OFFS + 0x00000200 + 0x4 * (n))
#define HWIO_PMIC_ARB_PVC_PORTn_CTL_OFFS(base,n)                      (0x00000200 + 0x4 * (n))
#define HWIO_PMIC_ARB_PVC_PORTn_CTL_RMSK                                     0x3
#define HWIO_PMIC_ARB_PVC_PORTn_CTL_INI(base,n)        \
        in_dword_masked(HWIO_PMIC_ARB_PVC_PORTn_CTL_ADDR(base,n), HWIO_PMIC_ARB_PVC_PORTn_CTL_RMSK)
#define HWIO_PMIC_ARB_PVC_PORTn_CTL_INMI(base,n,mask)    \
        in_dword_masked(HWIO_PMIC_ARB_PVC_PORTn_CTL_ADDR(base,n), mask)
#define HWIO_PMIC_ARB_PVC_PORTn_CTL_OUTI(base,n,val)    \
        out_dword(HWIO_PMIC_ARB_PVC_PORTn_CTL_ADDR(base,n),val)
#define HWIO_PMIC_ARB_PVC_PORTn_CTL_OUTMI(base,n,mask,val) \
        out_dword_masked_ns(HWIO_PMIC_ARB_PVC_PORTn_CTL_ADDR(base,n),mask,val,HWIO_PMIC_ARB_PVC_PORTn_CTL_INI(base,n))
#define HWIO_PMIC_ARB_PVC_PORTn_CTL_SPMI_PRIORITY_BMSK                       0x2
#define HWIO_PMIC_ARB_PVC_PORTn_CTL_SPMI_PRIORITY_SHFT                       0x1
#define HWIO_PMIC_ARB_PVC_PORTn_CTL_PVC_PORT_EN_BMSK                         0x1
#define HWIO_PMIC_ARB_PVC_PORTn_CTL_PVC_PORT_EN_SHFT                         0x0

#define HWIO_PMIC_ARB_PVC_PORTn_STATUS_ADDR(base,n)                   ((base) + PMIC_ARB_CORE_REG_BASE_OFFS + 0x00000280 + 0x4 * (n))
#define HWIO_PMIC_ARB_PVC_PORTn_STATUS_OFFS(base,n)                   (0x00000280 + 0x4 * (n))
#define HWIO_PMIC_ARB_PVC_PORTn_STATUS_RMSK                                  0x3
#define HWIO_PMIC_ARB_PVC_PORTn_STATUS_INI(base,n)        \
        in_dword_masked(HWIO_PMIC_ARB_PVC_PORTn_STATUS_ADDR(base,n), HWIO_PMIC_ARB_PVC_PORTn_STATUS_RMSK)
#define HWIO_PMIC_ARB_PVC_PORTn_STATUS_INMI(base,n,mask)    \
        in_dword_masked(HWIO_PMIC_ARB_PVC_PORTn_STATUS_ADDR(base,n), mask)
#define HWIO_PMIC_ARB_PVC_PORTn_STATUS_PVC_PORT_FAILURE_BMSK                 0x2
#define HWIO_PMIC_ARB_PVC_PORTn_STATUS_PVC_PORT_FAILURE_SHFT                 0x1
#define HWIO_PMIC_ARB_PVC_PORTn_STATUS_PVC_PORT_BUSY_BMSK                    0x1
#define HWIO_PMIC_ARB_PVC_PORTn_STATUS_PVC_PORT_BUSY_SHFT                    0x0

#define HWIO_PMIC_ARB_PVCn_ADDRm_ADDR(base,n,m)                       ((base) + PMIC_ARB_CORE_REG_BASE_OFFS + 0x00000400 + 0x20 * (n) + 0x4 * (m))
#define HWIO_PMIC_ARB_PVCn_ADDRm_OFFS(base,n,m)                       (0x00000400 + 0x20 * (n) + 0x4 * (m))
#define HWIO_PMIC_ARB_PVCn_ADDRm_RMSK                                    0xfffff
#define HWIO_PMIC_ARB_PVCn_ADDRm_INI2(base,n,m)        \
        in_dword_masked(HWIO_PMIC_ARB_PVCn_ADDRm_ADDR(base,n,m), HWIO_PMIC_ARB_PVCn_ADDRm_RMSK)
#define HWIO_PMIC_ARB_PVCn_ADDRm_INMI2(base,n,m,mask)    \
        in_dword_masked(HWIO_PMIC_ARB_PVCn_ADDRm_ADDR(base,n,m), mask)
#define HWIO_PMIC_ARB_PVCn_ADDRm_OUTI2(base,n,m,val)    \
        out_dword(HWIO_PMIC_ARB_PVCn_ADDRm_ADDR(base,n,m),val)
#define HWIO_PMIC_ARB_PVCn_ADDRm_OUTMI2(base,n,m,mask,val) \
        out_dword_masked_ns(HWIO_PMIC_ARB_PVCn_ADDRm_ADDR(base,n,m),mask,val,HWIO_PMIC_ARB_PVCn_ADDRm_INI2(base,n,m))
#define HWIO_PMIC_ARB_PVCn_ADDRm_SID_BMSK                                0xf0000
#define HWIO_PMIC_ARB_PVCn_ADDRm_SID_SHFT                                   0x10
#define HWIO_PMIC_ARB_PVCn_ADDRm_ADDRESS_BMSK                             0xffff
#define HWIO_PMIC_ARB_PVCn_ADDRm_ADDRESS_SHFT                                0x0

#define HWIO_PMIC_ARB_REG_CHNLn_ADDR(base,n)                          ((base) + PMIC_ARB_CORE_REG_BASE_OFFS + 0x00000800 + 0x4 * (n))
#define HWIO_PMIC_ARB_REG_CHNLn_OFFS(base,n)                          (0x00000800 + 0x4 * (n))
#define HWIO_PMIC_ARB_REG_CHNLn_RMSK                                     0xfff00
#define HWIO_PMIC_ARB_REG_CHNLn_INI(base,n)        \
        in_dword_masked(HWIO_PMIC_ARB_REG_CHNLn_ADDR(base,n), HWIO_PMIC_ARB_REG_CHNLn_RMSK)
#define HWIO_PMIC_ARB_REG_CHNLn_INMI(base,n,mask)    \
        in_dword_masked(HWIO_PMIC_ARB_REG_CHNLn_ADDR(base,n), mask)
#define HWIO_PMIC_ARB_REG_CHNLn_OUTI(base,n,val)    \
        out_dword(HWIO_PMIC_ARB_REG_CHNLn_ADDR(base,n),val)
#define HWIO_PMIC_ARB_REG_CHNLn_OUTMI(base,n,mask,val) \
        out_dword_masked_ns(HWIO_PMIC_ARB_REG_CHNLn_ADDR(base,n),mask,val,HWIO_PMIC_ARB_REG_CHNLn_INI(base,n))
#define HWIO_PMIC_ARB_REG_CHNLn_SID_BMSK                                 0xf0000
#define HWIO_PMIC_ARB_REG_CHNLn_SID_SHFT                                    0x10
#define HWIO_PMIC_ARB_REG_CHNLn_ADDRESS_BMSK                              0xff00
#define HWIO_PMIC_ARB_REG_CHNLn_ADDRESS_SHFT                                 0x8

/*----------------------------------------------------------------------------
 * MODULE: PMIC_ARB_CORE_REGISTERS
 *--------------------------------------------------------------------------*/

#define PMIC_ARB_CORE_REGISTERS_REG_BASE                  (PMIC_ARB_BASE      + 0x00400000)
#define PMIC_ARB_CORE_REGISTERS_REG_BASE_OFFS             0x00400000

#define HWIO_PMIC_ARBq_CHNLn_CMD_ADDR(base,q,n)           ((base) + PMIC_ARB_CORE_REGISTERS_REG_BASE_OFFS + 0x00000000 + 0x1000 * (q) + 0x8000 * (n))
#define HWIO_PMIC_ARBq_CHNLn_CMD_OFFS(base,q,n)           (0x00000000 + 0x1000 * (q) + 0x8000 * (n))
#define HWIO_PMIC_ARBq_CHNLn_CMD_RMSK                     0xfc000ff7
#define HWIO_PMIC_ARBq_CHNLn_CMD_INI2(base,q,n)        \
        in_dword_masked(HWIO_PMIC_ARBq_CHNLn_CMD_ADDR(base,q,n), HWIO_PMIC_ARBq_CHNLn_CMD_RMSK)
#define HWIO_PMIC_ARBq_CHNLn_CMD_INMI2(base,q,n,mask)    \
        in_dword_masked(HWIO_PMIC_ARBq_CHNLn_CMD_ADDR(base,q,n), mask)
#define HWIO_PMIC_ARBq_CHNLn_CMD_OUTI2(base,q,n,val)    \
        out_dword(HWIO_PMIC_ARBq_CHNLn_CMD_ADDR(base,q,n),val)
#define HWIO_PMIC_ARBq_CHNLn_CMD_OUTMI2(base,q,n,mask,val) \
        out_dword_masked_ns(HWIO_PMIC_ARBq_CHNLn_CMD_ADDR(base,q,n),mask,val,HWIO_PMIC_ARBq_CHNLn_CMD_INI2(base,q,n))
#define HWIO_PMIC_ARBq_CHNLn_CMD_OPCODE_BMSK              0xf8000000
#define HWIO_PMIC_ARBq_CHNLn_CMD_OPCODE_SHFT                    0x1b
#define HWIO_PMIC_ARBq_CHNLn_CMD_PRIORITY_BMSK             0x4000000
#define HWIO_PMIC_ARBq_CHNLn_CMD_PRIORITY_SHFT                  0x1a
#define HWIO_PMIC_ARBq_CHNLn_CMD_ADDRESS_BMSK                  0xff0
#define HWIO_PMIC_ARBq_CHNLn_CMD_ADDRESS_SHFT                    0x4
#define HWIO_PMIC_ARBq_CHNLn_CMD_BYTE_CNT_BMSK                   0x7
#define HWIO_PMIC_ARBq_CHNLn_CMD_BYTE_CNT_SHFT                   0x0

#define HWIO_PMIC_ARBq_CHNLn_CONFIG_ADDR(base,q,n)        ((base) + PMIC_ARB_CORE_REGISTERS_REG_BASE_OFFS + 0x00000004 + 0x1000 * (q) + 0x8000 * (n))
#define HWIO_PMIC_ARBq_CHNLn_CONFIG_OFFS(base,q,n)        (0x00000004 + 0x1000 * (q) + 0x8000 * (n))
#define HWIO_PMIC_ARBq_CHNLn_CONFIG_RMSK                         0x1
#define HWIO_PMIC_ARBq_CHNLn_CONFIG_INI2(base,q,n)        \
        in_dword_masked(HWIO_PMIC_ARBq_CHNLn_CONFIG_ADDR(base,q,n), HWIO_PMIC_ARBq_CHNLn_CONFIG_RMSK)
#define HWIO_PMIC_ARBq_CHNLn_CONFIG_INMI2(base,q,n,mask)    \
        in_dword_masked(HWIO_PMIC_ARBq_CHNLn_CONFIG_ADDR(base,q,n), mask)
#define HWIO_PMIC_ARBq_CHNLn_CONFIG_OUTI2(base,q,n,val)    \
        out_dword(HWIO_PMIC_ARBq_CHNLn_CONFIG_ADDR(base,q,n),val)
#define HWIO_PMIC_ARBq_CHNLn_CONFIG_OUTMI2(base,q,n,mask,val) \
        out_dword_masked_ns(HWIO_PMIC_ARBq_CHNLn_CONFIG_ADDR(base,q,n),mask,val,HWIO_PMIC_ARBq_CHNLn_CONFIG_INI2(base,q,n))
#define HWIO_PMIC_ARBq_CHNLn_CONFIG_IRQ_EN_BMSK                  0x1
#define HWIO_PMIC_ARBq_CHNLn_CONFIG_IRQ_EN_SHFT                  0x0

#define HWIO_PMIC_ARBq_CHNLn_STATUS_ADDR(base,q,n)        ((base) + PMIC_ARB_CORE_REGISTERS_REG_BASE_OFFS + 0x00000008 + 0x1000 * (q) + 0x8000 * (n))
#define HWIO_PMIC_ARBq_CHNLn_STATUS_OFFS(base,q,n)        (0x00000008 + 0x1000 * (q) + 0x8000 * (n))
#define HWIO_PMIC_ARBq_CHNLn_STATUS_RMSK                         0xf
#define HWIO_PMIC_ARBq_CHNLn_STATUS_INI2(base,q,n)        \
        in_dword_masked(HWIO_PMIC_ARBq_CHNLn_STATUS_ADDR(base,q,n), HWIO_PMIC_ARBq_CHNLn_STATUS_RMSK)
#define HWIO_PMIC_ARBq_CHNLn_STATUS_INMI2(base,q,n,mask)    \
        in_dword_masked(HWIO_PMIC_ARBq_CHNLn_STATUS_ADDR(base,q,n), mask)
#define HWIO_PMIC_ARBq_CHNLn_STATUS_DROPPED_BMSK                 0x8
#define HWIO_PMIC_ARBq_CHNLn_STATUS_DROPPED_SHFT                 0x3
#define HWIO_PMIC_ARBq_CHNLn_STATUS_DENIED_BMSK                  0x4
#define HWIO_PMIC_ARBq_CHNLn_STATUS_DENIED_SHFT                  0x2
#define HWIO_PMIC_ARBq_CHNLn_STATUS_FAILURE_BMSK                 0x2
#define HWIO_PMIC_ARBq_CHNLn_STATUS_FAILURE_SHFT                 0x1
#define HWIO_PMIC_ARBq_CHNLn_STATUS_DONE_BMSK                    0x1
#define HWIO_PMIC_ARBq_CHNLn_STATUS_DONE_SHFT                    0x0

#define HWIO_PMIC_ARBq_CHNLn_WDATA0_ADDR(base,q,n)        ((base) + PMIC_ARB_CORE_REGISTERS_REG_BASE_OFFS + 0x00000010 + 0x1000 * (q) + 0x8000 * (n))
#define HWIO_PMIC_ARBq_CHNLn_WDATA0_OFFS(base,q,n)        (0x00000010 + 0x1000 * (q) + 0x8000 * (n))
#define HWIO_PMIC_ARBq_CHNLn_WDATA0_RMSK                  0xffffffff
#define HWIO_PMIC_ARBq_CHNLn_WDATA0_INI2(base,q,n)        \
        in_dword_masked(HWIO_PMIC_ARBq_CHNLn_WDATA0_ADDR(base,q,n), HWIO_PMIC_ARBq_CHNLn_WDATA0_RMSK)
#define HWIO_PMIC_ARBq_CHNLn_WDATA0_INMI2(base,q,n,mask)    \
        in_dword_masked(HWIO_PMIC_ARBq_CHNLn_WDATA0_ADDR(base,q,n), mask)
#define HWIO_PMIC_ARBq_CHNLn_WDATA0_OUTI2(base,q,n,val)    \
        out_dword(HWIO_PMIC_ARBq_CHNLn_WDATA0_ADDR(base,q,n),val)
#define HWIO_PMIC_ARBq_CHNLn_WDATA0_OUTMI2(base,q,n,mask,val) \
        out_dword_masked_ns(HWIO_PMIC_ARBq_CHNLn_WDATA0_ADDR(base,q,n),mask,val,HWIO_PMIC_ARBq_CHNLn_WDATA0_INI2(base,q,n))
#define HWIO_PMIC_ARBq_CHNLn_WDATA0_DATA_BMSK             0xffffffff
#define HWIO_PMIC_ARBq_CHNLn_WDATA0_DATA_SHFT                    0x0

#define HWIO_PMIC_ARBq_CHNLn_WDATA1_ADDR(base,q,n)        ((base) + PMIC_ARB_CORE_REGISTERS_REG_BASE_OFFS + 0x00000014 + 0x1000 * (q) + 0x8000 * (n))
#define HWIO_PMIC_ARBq_CHNLn_WDATA1_OFFS(base,q,n)        (0x00000014 + 0x1000 * (q) + 0x8000 * (n))
#define HWIO_PMIC_ARBq_CHNLn_WDATA1_RMSK                  0xffffffff
#define HWIO_PMIC_ARBq_CHNLn_WDATA1_INI2(base,q,n)        \
        in_dword_masked(HWIO_PMIC_ARBq_CHNLn_WDATA1_ADDR(base,q,n), HWIO_PMIC_ARBq_CHNLn_WDATA1_RMSK)
#define HWIO_PMIC_ARBq_CHNLn_WDATA1_INMI2(base,q,n,mask)    \
        in_dword_masked(HWIO_PMIC_ARBq_CHNLn_WDATA1_ADDR(base,q,n), mask)
#define HWIO_PMIC_ARBq_CHNLn_WDATA1_OUTI2(base,q,n,val)    \
        out_dword(HWIO_PMIC_ARBq_CHNLn_WDATA1_ADDR(base,q,n),val)
#define HWIO_PMIC_ARBq_CHNLn_WDATA1_OUTMI2(base,q,n,mask,val) \
        out_dword_masked_ns(HWIO_PMIC_ARBq_CHNLn_WDATA1_ADDR(base,q,n),mask,val,HWIO_PMIC_ARBq_CHNLn_WDATA1_INI2(base,q,n))
#define HWIO_PMIC_ARBq_CHNLn_WDATA1_DATA_BMSK             0xffffffff
#define HWIO_PMIC_ARBq_CHNLn_WDATA1_DATA_SHFT                    0x0

#define HWIO_PMIC_ARBq_CHNLn_RDATA0_ADDR(base,q,n)        ((base) + PMIC_ARB_CORE_REGISTERS_REG_BASE_OFFS + 0x00000018 + 0x1000 * (q) + 0x8000 * (n))
#define HWIO_PMIC_ARBq_CHNLn_RDATA0_OFFS(base,q,n)        (0x00000018 + 0x1000 * (q) + 0x8000 * (n))
#define HWIO_PMIC_ARBq_CHNLn_RDATA0_RMSK                  0xffffffff
#define HWIO_PMIC_ARBq_CHNLn_RDATA0_INI2(base,q,n)        \
        in_dword_masked(HWIO_PMIC_ARBq_CHNLn_RDATA0_ADDR(base,q,n), HWIO_PMIC_ARBq_CHNLn_RDATA0_RMSK)
#define HWIO_PMIC_ARBq_CHNLn_RDATA0_INMI2(base,q,n,mask)    \
        in_dword_masked(HWIO_PMIC_ARBq_CHNLn_RDATA0_ADDR(base,q,n), mask)
#define HWIO_PMIC_ARBq_CHNLn_RDATA0_DATA_BMSK             0xffffffff
#define HWIO_PMIC_ARBq_CHNLn_RDATA0_DATA_SHFT                    0x0

#define HWIO_PMIC_ARBq_CHNLn_RDATA1_ADDR(base,q,n)        ((base) + PMIC_ARB_CORE_REGISTERS_REG_BASE_OFFS + 0x0000001c + 0x1000 * (q) + 0x8000 * (n))
#define HWIO_PMIC_ARBq_CHNLn_RDATA1_OFFS(base,q,n)        (0x0000001c + 0x1000 * (q) + 0x8000 * (n))
#define HWIO_PMIC_ARBq_CHNLn_RDATA1_RMSK                  0xffffffff
#define HWIO_PMIC_ARBq_CHNLn_RDATA1_INI2(base,q,n)        \
        in_dword_masked(HWIO_PMIC_ARBq_CHNLn_RDATA1_ADDR(base,q,n), HWIO_PMIC_ARBq_CHNLn_RDATA1_RMSK)
#define HWIO_PMIC_ARBq_CHNLn_RDATA1_INMI2(base,q,n,mask)    \
        in_dword_masked(HWIO_PMIC_ARBq_CHNLn_RDATA1_ADDR(base,q,n), mask)
#define HWIO_PMIC_ARBq_CHNLn_RDATA1_DATA_BMSK             0xffffffff
#define HWIO_PMIC_ARBq_CHNLn_RDATA1_DATA_SHFT                    0x0

#define HWIO_PMIC_ARBq_CHNLn_RDATA2_ADDR(base,q,n)        ((base) + PMIC_ARB_CORE_REGISTERS_REG_BASE_OFFS + 0x00000020 + 0x1000 * (q) + 0x8000 * (n))
#define HWIO_PMIC_ARBq_CHNLn_RDATA2_OFFS(base,q,n)        (0x00000020 + 0x1000 * (q) + 0x8000 * (n))
#define HWIO_PMIC_ARBq_CHNLn_RDATA2_RMSK                      0xffff
#define HWIO_PMIC_ARBq_CHNLn_RDATA2_INI2(base,q,n)        \
        in_dword_masked(HWIO_PMIC_ARBq_CHNLn_RDATA2_ADDR(base,q,n), HWIO_PMIC_ARBq_CHNLn_RDATA2_RMSK)
#define HWIO_PMIC_ARBq_CHNLn_RDATA2_INMI2(base,q,n,mask)    \
        in_dword_masked(HWIO_PMIC_ARBq_CHNLn_RDATA2_ADDR(base,q,n), mask)
#define HWIO_PMIC_ARBq_CHNLn_RDATA2_DATA_BMSK                 0xffff
#define HWIO_PMIC_ARBq_CHNLn_RDATA2_DATA_SHFT                    0x0

/*----------------------------------------------------------------------------
 * MODULE: PMIC_ARB_CORE_REGISTERS_OBS
 *--------------------------------------------------------------------------*/

#define PMIC_ARB_CORE_REGISTERS_OBS_REG_BASE                  (PMIC_ARB_BASE      + 0x01400000)
#define PMIC_ARB_CORE_REGISTERS_OBS_REG_BASE_OFFS             0x01400000

#define HWIO_PMIC_ARB_OBSq_CHNLn_CMD_ADDR(base,q,n)           ((base) + PMIC_ARB_CORE_REGISTERS_OBS_REG_BASE_OFFS + 0x00000000 + 0x1000 * (q) + 0x8000 * (n))
#define HWIO_PMIC_ARB_OBSq_CHNLn_CMD_OFFS(base,q,n)           (0x00000000 + 0x1000 * (q) + 0x8000 * (n))
#define HWIO_PMIC_ARB_OBSq_CHNLn_CMD_RMSK                     0xfc000ff7
#define HWIO_PMIC_ARB_OBSq_CHNLn_CMD_INI2(base,q,n)        \
        in_dword_masked(HWIO_PMIC_ARB_OBSq_CHNLn_CMD_ADDR(base,q,n), HWIO_PMIC_ARB_OBSq_CHNLn_CMD_RMSK)
#define HWIO_PMIC_ARB_OBSq_CHNLn_CMD_INMI2(base,q,n,mask)    \
        in_dword_masked(HWIO_PMIC_ARB_OBSq_CHNLn_CMD_ADDR(base,q,n), mask)
#define HWIO_PMIC_ARB_OBSq_CHNLn_CMD_OUTI2(base,q,n,val)    \
        out_dword(HWIO_PMIC_ARB_OBSq_CHNLn_CMD_ADDR(base,q,n),val)
#define HWIO_PMIC_ARB_OBSq_CHNLn_CMD_OUTMI2(base,q,n,mask,val) \
        out_dword_masked_ns(HWIO_PMIC_ARB_OBSq_CHNLn_CMD_ADDR(base,q,n),mask,val,HWIO_PMIC_ARB_OBSq_CHNLn_CMD_INI2(base,q,n))
#define HWIO_PMIC_ARB_OBSq_CHNLn_CMD_OPCODE_BMSK              0xf8000000
#define HWIO_PMIC_ARB_OBSq_CHNLn_CMD_OPCODE_SHFT                    0x1b
#define HWIO_PMIC_ARB_OBSq_CHNLn_CMD_PRIORITY_BMSK             0x4000000
#define HWIO_PMIC_ARB_OBSq_CHNLn_CMD_PRIORITY_SHFT                  0x1a
#define HWIO_PMIC_ARB_OBSq_CHNLn_CMD_ADDRESS_BMSK                  0xff0
#define HWIO_PMIC_ARB_OBSq_CHNLn_CMD_ADDRESS_SHFT                    0x4
#define HWIO_PMIC_ARB_OBSq_CHNLn_CMD_BYTE_CNT_BMSK                   0x7
#define HWIO_PMIC_ARB_OBSq_CHNLn_CMD_BYTE_CNT_SHFT                   0x0

#define HWIO_PMIC_ARB_OBSq_CHNLn_CONFIG_ADDR(base,q,n)        ((base) + PMIC_ARB_CORE_REGISTERS_OBS_REG_BASE_OFFS + 0x00000004 + 0x1000 * (q) + 0x8000 * (n))
#define HWIO_PMIC_ARB_OBSq_CHNLn_CONFIG_OFFS(base,q,n)        (0x00000004 + 0x1000 * (q) + 0x8000 * (n))
#define HWIO_PMIC_ARB_OBSq_CHNLn_CONFIG_RMSK                         0x1
#define HWIO_PMIC_ARB_OBSq_CHNLn_CONFIG_INI2(base,q,n)        \
        in_dword_masked(HWIO_PMIC_ARB_OBSq_CHNLn_CONFIG_ADDR(base,q,n), HWIO_PMIC_ARB_OBSq_CHNLn_CONFIG_RMSK)
#define HWIO_PMIC_ARB_OBSq_CHNLn_CONFIG_INMI2(base,q,n,mask)    \
        in_dword_masked(HWIO_PMIC_ARB_OBSq_CHNLn_CONFIG_ADDR(base,q,n), mask)
#define HWIO_PMIC_ARB_OBSq_CHNLn_CONFIG_OUTI2(base,q,n,val)    \
        out_dword(HWIO_PMIC_ARB_OBSq_CHNLn_CONFIG_ADDR(base,q,n),val)
#define HWIO_PMIC_ARB_OBSq_CHNLn_CONFIG_OUTMI2(base,q,n,mask,val) \
        out_dword_masked_ns(HWIO_PMIC_ARB_OBSq_CHNLn_CONFIG_ADDR(base,q,n),mask,val,HWIO_PMIC_ARB_OBSq_CHNLn_CONFIG_INI2(base,q,n))
#define HWIO_PMIC_ARB_OBSq_CHNLn_CONFIG_IRQ_EN_BMSK                  0x1
#define HWIO_PMIC_ARB_OBSq_CHNLn_CONFIG_IRQ_EN_SHFT                  0x0

#define HWIO_PMIC_ARB_OBSq_CHNLn_STATUS_ADDR(base,q,n)        ((base) + PMIC_ARB_CORE_REGISTERS_OBS_REG_BASE_OFFS + 0x00000008 + 0x1000 * (q) + 0x8000 * (n))
#define HWIO_PMIC_ARB_OBSq_CHNLn_STATUS_OFFS(base,q,n)        (0x00000008 + 0x1000 * (q) + 0x8000 * (n))
#define HWIO_PMIC_ARB_OBSq_CHNLn_STATUS_RMSK                         0xf
#define HWIO_PMIC_ARB_OBSq_CHNLn_STATUS_INI2(base,q,n)        \
        in_dword_masked(HWIO_PMIC_ARB_OBSq_CHNLn_STATUS_ADDR(base,q,n), HWIO_PMIC_ARB_OBSq_CHNLn_STATUS_RMSK)
#define HWIO_PMIC_ARB_OBSq_CHNLn_STATUS_INMI2(base,q,n,mask)    \
        in_dword_masked(HWIO_PMIC_ARB_OBSq_CHNLn_STATUS_ADDR(base,q,n), mask)
#define HWIO_PMIC_ARB_OBSq_CHNLn_STATUS_DROPPED_BMSK                 0x8
#define HWIO_PMIC_ARB_OBSq_CHNLn_STATUS_DROPPED_SHFT                 0x3
#define HWIO_PMIC_ARB_OBSq_CHNLn_STATUS_DENIED_BMSK                  0x4
#define HWIO_PMIC_ARB_OBSq_CHNLn_STATUS_DENIED_SHFT                  0x2
#define HWIO_PMIC_ARB_OBSq_CHNLn_STATUS_FAILURE_BMSK                 0x2
#define HWIO_PMIC_ARB_OBSq_CHNLn_STATUS_FAILURE_SHFT                 0x1
#define HWIO_PMIC_ARB_OBSq_CHNLn_STATUS_DONE_BMSK                    0x1
#define HWIO_PMIC_ARB_OBSq_CHNLn_STATUS_DONE_SHFT                    0x0

#define HWIO_PMIC_ARB_OBSq_CHNLn_RDATA0_ADDR(base,q,n)        ((base) + PMIC_ARB_CORE_REGISTERS_OBS_REG_BASE_OFFS + 0x00000018 + 0x1000 * (q) + 0x8000 * (n))
#define HWIO_PMIC_ARB_OBSq_CHNLn_RDATA0_OFFS(base,q,n)        (0x00000018 + 0x1000 * (q) + 0x8000 * (n))
#define HWIO_PMIC_ARB_OBSq_CHNLn_RDATA0_RMSK                  0xffffffff
#define HWIO_PMIC_ARB_OBSq_CHNLn_RDATA0_INI2(base,q,n)        \
        in_dword_masked(HWIO_PMIC_ARB_OBSq_CHNLn_RDATA0_ADDR(base,q,n), HWIO_PMIC_ARB_OBSq_CHNLn_RDATA0_RMSK)
#define HWIO_PMIC_ARB_OBSq_CHNLn_RDATA0_INMI2(base,q,n,mask)    \
        in_dword_masked(HWIO_PMIC_ARB_OBSq_CHNLn_RDATA0_ADDR(base,q,n), mask)
#define HWIO_PMIC_ARB_OBSq_CHNLn_RDATA0_DATA_BMSK             0xffffffff
#define HWIO_PMIC_ARB_OBSq_CHNLn_RDATA0_DATA_SHFT                    0x0

#define HWIO_PMIC_ARB_OBSq_CHNLn_RDATA1_ADDR(base,q,n)        ((base) + PMIC_ARB_CORE_REGISTERS_OBS_REG_BASE_OFFS + 0x0000001c + 0x1000 * (q) + 0x8000 * (n))
#define HWIO_PMIC_ARB_OBSq_CHNLn_RDATA1_OFFS(base,q,n)        (0x0000001c + 0x1000 * (q) + 0x8000 * (n))
#define HWIO_PMIC_ARB_OBSq_CHNLn_RDATA1_RMSK                  0xffffffff
#define HWIO_PMIC_ARB_OBSq_CHNLn_RDATA1_INI2(base,q,n)        \
        in_dword_masked(HWIO_PMIC_ARB_OBSq_CHNLn_RDATA1_ADDR(base,q,n), HWIO_PMIC_ARB_OBSq_CHNLn_RDATA1_RMSK)
#define HWIO_PMIC_ARB_OBSq_CHNLn_RDATA1_INMI2(base,q,n,mask)    \
        in_dword_masked(HWIO_PMIC_ARB_OBSq_CHNLn_RDATA1_ADDR(base,q,n), mask)
#define HWIO_PMIC_ARB_OBSq_CHNLn_RDATA1_DATA_BMSK             0xffffffff
#define HWIO_PMIC_ARB_OBSq_CHNLn_RDATA1_DATA_SHFT                    0x0


#endif /* __PMICARBCOREHWIO_H__ */
