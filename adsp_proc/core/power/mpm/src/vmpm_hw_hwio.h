#ifndef __VMPM_HW_HWIO_H__
#define __VMPM_HW_HWIO_H__
/*
===========================================================================
*/
/**
  @file vmpm_hw_hwio.h
  @brief Auto-generated HWIO interface include file.

  Reference chip release:
    MSM8998 (Nazgul) [nazgul_v1.0_p3q3r37]
 
  This file contains HWIO register definitions for the following modules:
    MPM2_SLP_CNTR

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

  $Header: //components/rel/core.qdsp6/1.0.c2/power/mpm/src/vmpm_hw_hwio.h#1 $
  $DateTime: 2020/02/10 01:57:30 $
  $Author: pwbldsvc $

  ===========================================================================
*/


#include "msmhwiobase.h"

/*----------------------------------------------------------------------------
 * MODULE: MPM2_SLP_CNTR
 *--------------------------------------------------------------------------*/

#define MPM2_SLP_CNTR_REG_BASE                                    (MPM2_MPM_BASE      + 0x00003000)

#define HWIO_MPM2_MPM_SLEEP_TIMETICK_COUNT_VAL_ADDR               (MPM2_SLP_CNTR_REG_BASE      + 0x00000000)
#define HWIO_MPM2_MPM_SLEEP_TIMETICK_COUNT_VAL_RMSK               0xffffffff
#define HWIO_MPM2_MPM_SLEEP_TIMETICK_COUNT_VAL_IN          \
        in_dword_masked(HWIO_MPM2_MPM_SLEEP_TIMETICK_COUNT_VAL_ADDR, HWIO_MPM2_MPM_SLEEP_TIMETICK_COUNT_VAL_RMSK)
#define HWIO_MPM2_MPM_SLEEP_TIMETICK_COUNT_VAL_INM(m)      \
        in_dword_masked(HWIO_MPM2_MPM_SLEEP_TIMETICK_COUNT_VAL_ADDR, m)
#define HWIO_MPM2_MPM_SLEEP_TIMETICK_COUNT_VAL_DATA_BMSK          0xffffffff
#define HWIO_MPM2_MPM_SLEEP_TIMETICK_COUNT_VAL_DATA_SHFT                 0x0


#endif /* __VMPM_HW_HWIO_H__ */
