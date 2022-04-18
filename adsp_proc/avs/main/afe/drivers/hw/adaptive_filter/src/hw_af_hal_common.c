/*==============================================================================
  @brief This file contains hardware adaptive filter HAL common implementation

  Copyright (c) 2017-2018 QUALCOMM Technologies, Inc.  All Rights Reserved.
  QUALCOMM Technologies, Inc Proprietary.  Export of this technology or
  software is regulated by the U.S. Government, Diversion contrary to U.S.
  law prohibited.
==============================================================================*/

/*==============================================================================
  Edit History

  $Header: //components/rel/avs.adsp/2.8/afe/drivers/hw/adaptive_filter/src/hw_af_hal_common.c#3 $

  when       who     what, where, why
  --------   ---     -------------------------------------------------------
  02/15/18   eta      Fix for HW AF NOC register retain issue
  09/19/17   unni     Created file
==============================================================================*/

#include "hw_af_hal_common.h"
#include "hw_af_hal_v1.h"

#define ADAPTIVE_FILTER_HW_VERSION_1 0x10000001

/* Global HAL function table */
hw_af_hal_func_def_t hal_af_func_def_ptr_g;


/*
  Hal common Init

  param[in] base_virt_addr: Base address of LPASS
  param[in] hw_version: Version of hardware
  param[in/out] hal_func_def_ptr: hal func definitions table
 */
void hw_af_hal_init(
  uint32_t base_virt_addr, 
  uint32_t hw_version)
{
  switch(hw_version)
  {
    case ADAPTIVE_FILTER_HW_VERSION_1:
    default:
    {
      hw_af_hal_init_v1(base_virt_addr, &hal_af_func_def_ptr_g);
    }
    break;
  }

  return;
}


/*
  Submit current job to hardware
  param[in/out] config_phys_addr: input/output filter configuration used 
  param[in/out] buffer_phys_addr: input/output buffers used for processing

  return: None
 */
void hw_af_hal_job_submit(
  uint32_t config_phys_addr, 
  uint32_t buffer_phys_addr)
{
  hal_af_func_def_ptr_g.hw_af_hal_job_submit(
    config_phys_addr, 
    buffer_phys_addr);  
}

/*
  Kill current job 

  return: None
 */
void hw_af_hal_job_kill(void)
{
  hal_af_func_def_ptr_g.hw_af_hal_job_kill();
}

/* 
  Enable interrupt 

  return: None
  */
void hw_af_hal_intr_enable(void)
{
  hal_af_func_def_ptr_g.hw_af_hal_intr_enable();
}

/* 
  Disable interrupt 

  return: None
  */
void hw_af_hal_intr_disable(void)
{
  hal_af_func_def_ptr_g.hw_af_hal_intr_disable();
}

/*
  Clear interrupt 
  
  return: None
 */
void hw_af_hal_intr_clear(void)
{
  hal_af_func_def_ptr_g.hw_af_hal_intr_clear();
}

/*
  Fixes register retain issue
  after power collapse
  
  return: None
*/
void hw_af_hal_noc_register_fix(void)
{
  hal_af_func_def_ptr_g.hw_af_hal_noc_register_fix();
}