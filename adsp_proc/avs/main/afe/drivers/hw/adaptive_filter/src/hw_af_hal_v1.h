#ifndef __AFE_HW_AF_HAL_V1_H_
#define __AFE_HW_AF_HAL_V1_H_

/*==============================================================================
  @brief This file contains Hardware Adaptive filter HAL v1 APIs

  Copyright (c) 2017-2018 QUALCOMM Technologies, Inc.  All Rights Reserved.
  QUALCOMM Technologies, Inc Proprietary.  Export of this technology or
  software is regulated by the U.S. Government, Diversion contrary to U.S.
  law prohibited.
==============================================================================*/

/*==============================================================================
  Edit History

  $Header: //components/rel/avs.adsp/2.8/afe/drivers/hw/adaptive_filter/src/hw_af_hal_v1.h#2 $

  when       who     what, where, why
  --------   ---     -------------------------------------------------------
  02/15/18   eta      Fix for HW AF NOC register retain issue
  09/22/17   unni     Created file
==============================================================================*/

#include "mmdefs.h"
#include "hw_af_hal_common.h"

/* 
   Init HW_AF block 

   return: None
  */
void hw_af_hal_init_v1(
  uint32_t base_virt_addr, 
  hw_af_hal_func_def_t* hal_func_def_ptr);

/*
  Submit current job to hardware
  param[in/out] config_phys_addr: input/output filter configuration used 
  param[in/out] buffer_phys_addr: input/output buffers used for processing

  return: None
 */
void hw_af_hal_job_submit_v1(
  uint32_t config_phys_addr, 
  uint32_t buffer_phys_addr);

/*
  Kill current job 

  return: None
 */
void hw_af_hal_job_kill_v1(void);

/* 
  Enable interrupt 

  return: None
  */
void hw_af_hal_intr_enable_v1(void);

/* 
  Disable interrupt 

  return: None
  */
void hw_af_hal_intr_disable_v1(void);

/*
  Clear interrupt 
  
  return: None
 */
void hw_af_hal_intr_clear_v1(void);

/*
  Fixes register retain issue
  after power collapse
  
  return: None
*/
void hw_af_hal_noc_register_fix_v1(void);

#endif /* __AFE_HW_AF_HAL_V1_H_ */