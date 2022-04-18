/*==============================================================================
  @brief This file contains hardware adaptive filter HAL v1 implementation

  Copyright (c) 2017-2018 QUALCOMM Technologies, Inc.  All Rights Reserved.
  QUALCOMM Technologies, Inc Proprietary.  Export of this technology or
  software is regulated by the U.S. Government, Diversion contrary to U.S.
  law prohibited.
==============================================================================*/

/*==============================================================================
  Edit History

  $Header: //components/rel/avs.adsp/2.8/afe/drivers/hw/adaptive_filter/src/hw_af_hal_v1.c#2 $

  when       who     what, where, why
  --------   ---     -------------------------------------------------------
  02/15/18   eta      Fix for HW AF NOC register retain issue
  09/19/17   unni     Created file
==============================================================================*/

#include "hw_af_hal_v1.h"
#include "common.h"
#include "ureg_sw_lpass_hw_af_core.h"
#include "ureg_sw_lpass_hw_af_noc.h"
#include "qurt_memory.h"

/*
 PriorityInBand       12:12 NUM DEF=0x0 RW RETENTION;
 ReadThreshold        23:16 NUM DEF=0x0 RW RETENTION;
 ReadHigh             26:24 NUM DEF=0x0 RW RETENTION;
*/
#define HW_AF_NOC_QOS_REG_RETAIN_FIX_V 0xF800EFFF

static int32 hw_af_base_virt_addr = 0;

/*
  Submit current job to hardware
  param[in/out] config_phys_addr: input/output filter configuration used 
  param[in/out] buffer_phys_addr: input/output buffers used for processing

  return: None
 */
void hw_af_hal_job_submit_v1(
  uint32_t config_phys_addr, 
  uint32_t buffer_phys_addr)
{
  /* Set config */
  reg_wr(hw_af_base_virt_addr + A_HW_AF_CFG_TYPE, config_phys_addr);
  /* Set buffer */
  reg_wr(hw_af_base_virt_addr + A_HW_AF_BUF_TYPE, buffer_phys_addr);
  /* Start job */
  reg_wr(hw_af_base_virt_addr + A_HW_AF_CTRL, (1 << HW_AF_CTRL__GO___S));
  return;
}

/*
  Kill current job 

  return: None
 */
void hw_af_hal_job_kill_v1(void)
{
  /* Stop job */
  reg_wr(hw_af_base_virt_addr + A_HW_AF_CTRL, (1 << HW_AF_CTRL__STOP___S));
  return;
}

/* 
   Enable interrupt 

   return: None
  */
void hw_af_hal_intr_enable_v1(void)
{
  /* Enable interrupt */
  reg_wr(hw_af_base_virt_addr + A_HW_AF_INTERRUPT_EN,  
    (HW_AF_INTERRUPT_EN__FILTER_DONE___M << 
     HW_AF_INTERRUPT_EN__FILTER_DONE___S   ));
}

/* 
   Disable interrupt 

   return: None
  */
void hw_af_hal_intr_disable_v1(void)
{
  uint32_t reg_value;  
  reg_rd(hw_af_base_virt_addr + A_HW_AF_INTERRUPT_EN,  
    &reg_value);
  reg_value &= ~((HW_AF_INTERRUPT_EN__FILTER_DONE___M << 
     HW_AF_INTERRUPT_EN__FILTER_DONE___S   ));

  /* Disable interrupt */  
  reg_wr(hw_af_base_virt_addr + A_HW_AF_INTERRUPT_EN, reg_value);
}
/* 
  Clear interrupt 
  return: None
 */
void hw_af_hal_intr_clear_v1(void)
{
  /* Clear interrupt */
  reg_wr(hw_af_base_virt_addr + A_HW_AF_INTERRUPT_CLR, 
    (HW_AF_INTERRUPT_CLR__FILTER_DONE_ACK___M << 
     HW_AF_INTERRUPT_CLR__FILTER_DONE_ACK___S   ));
}

/*
  Fixes register retain issue
  after power collapse
  
  return: None
*/
void hw_af_hal_noc_register_fix_v1(void)
{
	uint32_t reg_value;
	reg_rd(hw_af_base_virt_addr + A_AMM_LEC_CLIENTS_MAIN_SPECIFICTONTTPTR_URGENCY_LOW, &reg_value);
	reg_value = reg_value &  HW_AF_NOC_QOS_REG_RETAIN_FIX_V;
	reg_wr(hw_af_base_virt_addr + A_AMM_LEC_CLIENTS_MAIN_SPECIFICTONTTPTR_URGENCY_LOW, reg_value);
}

/* 
   Init HW_AF block 

   return: None
  */
void hw_af_hal_init_v1(
  uint32_t base_virt_addr, 
  hw_af_hal_func_def_t* hal_func_def_ptr)
{
  hal_func_def_ptr->hw_af_hal_job_submit = hw_af_hal_job_submit_v1;
  hal_func_def_ptr->hw_af_hal_job_kill = hw_af_hal_job_kill_v1;
  hal_func_def_ptr->hw_af_hal_intr_enable = hw_af_hal_intr_enable_v1;
  hal_func_def_ptr->hw_af_hal_intr_disable = hw_af_hal_intr_disable_v1;
  hal_func_def_ptr->hw_af_hal_intr_clear = hw_af_hal_intr_clear_v1;
  hal_func_def_ptr->hw_af_hal_noc_register_fix = hw_af_hal_noc_register_fix_v1;
  hw_af_base_virt_addr =  base_virt_addr;
}
