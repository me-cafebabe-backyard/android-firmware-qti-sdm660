#ifndef __HALHWIOTSENSFUSES_H__
#define __HALHWIOTSENSFUSES_H__
/*
===========================================================================
*/
/**
  @file HALhwioTsensFuses.h
  @brief Auto-generated HWIO interface include file.

  Reference chip release:
    SDM660 (Starlord) [starlord_v1.0_p3q2r79]

  This file contains HWIO register definitions for the following modules:
    SECURITY_CONTROL_CORE

  'Include' filters applied: QFPROM_CORR*[SECURITY_CONTROL_CORE]
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

  $Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/TsensTargetLib/HALhwioTsensFuses.h#2 $
  $DateTime: 2016/10/12 01:06:13 $
  $Author: pwbldsvc $

  ===========================================================================
*/

/*----------------------------------------------------------------------------
 * MODULE: SECURITY_CONTROL_CORE
 *--------------------------------------------------------------------------*/

#define SECURITY_CONTROL_CORE_REG_BASE                                                           (SECURITY_CONTROL_BASE      + 0x00000000)
#define SECURITY_CONTROL_CORE_REG_BASE_OFFS                                                      0x00000000

#define HWIO_QFPROM_CORR_CALIB_ROW11_MSB_ADDR                                                    (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004244)
#define HWIO_QFPROM_CORR_CALIB_ROW11_MSB_OFFS                                                    (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004244)
#define HWIO_QFPROM_CORR_CALIB_ROW11_MSB_RMSK                                                    0xffffffff
#define HWIO_QFPROM_CORR_CALIB_ROW11_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW11_MSB_ADDR, HWIO_QFPROM_CORR_CALIB_ROW11_MSB_RMSK)
#define HWIO_QFPROM_CORR_CALIB_ROW11_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW11_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIB_ROW11_MSB_TSENS2_OFFSET_BMSK                                      0xf0000000
#define HWIO_QFPROM_CORR_CALIB_ROW11_MSB_TSENS2_OFFSET_SHFT                                            0x1c
#define HWIO_QFPROM_CORR_CALIB_ROW11_MSB_TSENS1_OFFSET_BMSK                                       0xf000000
#define HWIO_QFPROM_CORR_CALIB_ROW11_MSB_TSENS1_OFFSET_SHFT                                            0x18
#define HWIO_QFPROM_CORR_CALIB_ROW11_MSB_TSENS0_OFFSET_BMSK                                        0xf00000
#define HWIO_QFPROM_CORR_CALIB_ROW11_MSB_TSENS0_OFFSET_SHFT                                            0x14
#define HWIO_QFPROM_CORR_CALIB_ROW11_MSB_TSENS0_BASE1_BMSK                                          0xffc00
#define HWIO_QFPROM_CORR_CALIB_ROW11_MSB_TSENS0_BASE1_SHFT                                              0xa
#define HWIO_QFPROM_CORR_CALIB_ROW11_MSB_TSENS0_BASE0_BMSK                                            0x3ff
#define HWIO_QFPROM_CORR_CALIB_ROW11_MSB_TSENS0_BASE0_SHFT                                              0x0

#define HWIO_QFPROM_CORR_CALIB_ROW12_LSB_ADDR                                                    (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004248)
#define HWIO_QFPROM_CORR_CALIB_ROW12_LSB_OFFS                                                    (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004248)
#define HWIO_QFPROM_CORR_CALIB_ROW12_LSB_RMSK                                                    0xffffffff
#define HWIO_QFPROM_CORR_CALIB_ROW12_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW12_LSB_ADDR, HWIO_QFPROM_CORR_CALIB_ROW12_LSB_RMSK)
#define HWIO_QFPROM_CORR_CALIB_ROW12_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW12_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIB_ROW12_LSB_TSENS10_OFFSET_BMSK                                     0xf0000000
#define HWIO_QFPROM_CORR_CALIB_ROW12_LSB_TSENS10_OFFSET_SHFT                                           0x1c
#define HWIO_QFPROM_CORR_CALIB_ROW12_LSB_TSENS9_OFFSET_BMSK                                       0xf000000
#define HWIO_QFPROM_CORR_CALIB_ROW12_LSB_TSENS9_OFFSET_SHFT                                            0x18
#define HWIO_QFPROM_CORR_CALIB_ROW12_LSB_TSENS8_OFFSET_BMSK                                        0xf00000
#define HWIO_QFPROM_CORR_CALIB_ROW12_LSB_TSENS8_OFFSET_SHFT                                            0x14
#define HWIO_QFPROM_CORR_CALIB_ROW12_LSB_TSENS7_OFFSET_BMSK                                         0xf0000
#define HWIO_QFPROM_CORR_CALIB_ROW12_LSB_TSENS7_OFFSET_SHFT                                            0x10
#define HWIO_QFPROM_CORR_CALIB_ROW12_LSB_TSENS6_OFFSET_BMSK                                          0xf000
#define HWIO_QFPROM_CORR_CALIB_ROW12_LSB_TSENS6_OFFSET_SHFT                                             0xc
#define HWIO_QFPROM_CORR_CALIB_ROW12_LSB_TSENS5_OFFSET_BMSK                                           0xf00
#define HWIO_QFPROM_CORR_CALIB_ROW12_LSB_TSENS5_OFFSET_SHFT                                             0x8
#define HWIO_QFPROM_CORR_CALIB_ROW12_LSB_TSENS4_OFFSET_BMSK                                            0xf0
#define HWIO_QFPROM_CORR_CALIB_ROW12_LSB_TSENS4_OFFSET_SHFT                                             0x4
#define HWIO_QFPROM_CORR_CALIB_ROW12_LSB_TSENS3_OFFSET_BMSK                                             0xf
#define HWIO_QFPROM_CORR_CALIB_ROW12_LSB_TSENS3_OFFSET_SHFT                                             0x0

#define HWIO_QFPROM_CORR_CALIB_ROW12_MSB_ADDR                                                    (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000424c)
#define HWIO_QFPROM_CORR_CALIB_ROW12_MSB_OFFS                                                    (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000424c)
#define HWIO_QFPROM_CORR_CALIB_ROW12_MSB_RMSK                                                        0x7fff
#define HWIO_QFPROM_CORR_CALIB_ROW12_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW12_MSB_ADDR, HWIO_QFPROM_CORR_CALIB_ROW12_MSB_RMSK)
#define HWIO_QFPROM_CORR_CALIB_ROW12_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW12_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIB_ROW12_MSB_TSENS_CAL_SEL_BMSK                                          0x7000
#define HWIO_QFPROM_CORR_CALIB_ROW12_MSB_TSENS_CAL_SEL_SHFT                                             0xc
#define HWIO_QFPROM_CORR_CALIB_ROW12_MSB_TSENS13_OFFSET_BMSK                                          0xf00
#define HWIO_QFPROM_CORR_CALIB_ROW12_MSB_TSENS13_OFFSET_SHFT                                            0x8
#define HWIO_QFPROM_CORR_CALIB_ROW12_MSB_TSENS12_OFFSET_BMSK                                           0xf0
#define HWIO_QFPROM_CORR_CALIB_ROW12_MSB_TSENS12_OFFSET_SHFT                                            0x4
#define HWIO_QFPROM_CORR_CALIB_ROW12_MSB_TSENS11_OFFSET_BMSK                                            0xf
#define HWIO_QFPROM_CORR_CALIB_ROW12_MSB_TSENS11_OFFSET_SHFT                                            0x0


#endif /* __HALHWIOTSENSFUSES_H__ */

