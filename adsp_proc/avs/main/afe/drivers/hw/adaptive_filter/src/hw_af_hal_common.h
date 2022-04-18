#ifndef __AFE_HW_AF_HAL_COMMON_H_
#define __AFE_HW_AF_HAL_COMMON_H_

/*==============================================================================
  @brief This file contains Hardware Adaptive filter HAL common APIs

  Copyright (c) 2017-2018 QUALCOMM Technologies, Inc.  All Rights Reserved.
  QUALCOMM Technologies, Inc Proprietary.  Export of this technology or
  software is regulated by the U.S. Government, Diversion contrary to U.S.
  law prohibited.
==============================================================================*/

/*==============================================================================
  Edit History

  $Header: //components/rel/avs.adsp/2.8/afe/drivers/hw/adaptive_filter/src/hw_af_hal_common.h#2 $

  when       who     what, where, why
  --------   ---     -------------------------------------------------------
  02/15/18   eta      Fix for HW AF NOC register retain issue
  09/22/17   unni     Created file
==============================================================================*/

#include "mmdefs.h"
#include "hw_af.h"

typedef void (*hal_hw_no_arg_func)(void);
typedef void (*hal_hw_submit_job)(uint32_t, uint32_t);

typedef struct
{
  hal_hw_submit_job hw_af_hal_job_submit;
  hal_hw_no_arg_func hw_af_hal_job_kill;
  hal_hw_no_arg_func hw_af_hal_intr_enable;
  hal_hw_no_arg_func hw_af_hal_intr_disable;
  hal_hw_no_arg_func hw_af_hal_intr_clear;
  hal_hw_no_arg_func hw_af_hal_noc_register_fix;
} hw_af_hal_func_def_t;

/*
  Hal common Init

  param[in] base_virt_addr: Base address of LPASS
  param[in] hw_version: Version of hardware
  param[in/out] hal_func_def_ptr: hal func definitions table
 */
void hw_af_hal_init(
  uint32_t base_virt_addr, 
  uint32_t hw_version);

/*
  Submit current job to hardware
  param[in/out] config_phys_addr: input/output filter configuration used 
  param[in/out] buffer_phys_addr: input/output buffers used for processing

  return: None
 */
void hw_af_hal_job_submit(
  uint32_t config_phys_addr, 
  uint32_t buffer_phys_addr);

/*
  Kill current job 

  return: None
 */
void hw_af_hal_job_kill(void);

/* 
  Enable interrupt 

  return: None
  */
void hw_af_hal_intr_enable(void);

/* 
  Enable interrupt 

  return: None
  */
void hw_af_hal_intr_disable(void);

/*
  Clear interrupt 
  
  return: None
 */
void hw_af_hal_intr_clear(void);

/*
  Fixes register retain issue
  after power collapse
  
  return: None
*/
void hw_af_hal_noc_register_fix(void);

#endif /* __AFE_HW_AF_HAL_COMMON_H_ */