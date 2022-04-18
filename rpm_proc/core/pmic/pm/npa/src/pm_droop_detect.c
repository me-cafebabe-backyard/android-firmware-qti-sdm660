/*! \file pm_droop_detect.c
 *  \n
 *  \brief This file contains implementation for PMIC RPM droop detection functions.
 *  \n  
 *  \n &copy; Copyright 2014 - 2016 QUALCOMM Technologies Incorporated, All Rights Reserved
 */

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

$Header: //components/rel/rpm.bf/1.8/core/pmic/pm/npa/src/pm_droop_detect.c#1 $  

when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
05/22/14   kt      Created.
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "pm_droop_detect.h"
#include "pm_droop_detect_internal.h"
#include "pm_rpm_utilities.h"

/*===========================================================================

                        STATIC AND GLOBAL VARIABLES

===========================================================================*/

// Droop detection debug info: time stamp, slave_id and periph_id
pm_droop_detect_info_type pm_droop_detect_info[PM_DROOP_LOG_ARRAY_SIZE];

// Droop detection rail register dump status info
pm_rail_status_info_type pm_droop_rail_status[PM_DROOP_LOG_ARRAY_SIZE];

// Droop detect isr hit count
static uint32 pm_droop_detect_count = 0;

// static global flag enable/disable abort on droop detection
static boolean pm_droop_detect_abort_enable = TRUE;

// static global flag to indicate droop detection for post droop config
static boolean pm_droop_detect_isr_triggered = FALSE;

// Isr prototype 
static void* pm_droop_detect_isr (uint32 isr_ctx, uint32 irq_mask);

pm_debug_droop_info_type pm_debug_droop = {.pm_droop_detect_info = pm_droop_detect_info,
                                           .pm_droop_rail_status = pm_droop_rail_status,
                                           .pm_droop_detect_count = &pm_droop_detect_count,
                                           .pm_droop_detect_abort_enable = &pm_droop_detect_abort_enable,
                                           .pm_droop_detect_isr_triggered = &pm_droop_detect_isr_triggered };

/*===========================================================================

                     FUNCTION IMPLEMENTATION 

===========================================================================*/

pm_err_flag_type pm_droop_detect_irq_enable(pm_pwr_data_type *pwr_data, pm_comm_info_type *comm_ptr, 
                                            uint8 resource_index, boolean enable)
{
    pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;
    pm_pwr_irq_type irq_type = PM_PWR_IRQ_VREG_FAULT;

    /* Clear the VREG_FAULT interrupt */
    err_flag = pm_pwr_irq_clear_alg(pwr_data, comm_ptr, resource_index, irq_type);

    /* Enable/disable the VREG_FAULT interrupt */
    err_flag |= pm_pwr_irq_enable_alg(pwr_data, comm_ptr, resource_index, irq_type, enable); 
    
    return err_flag;
}


__attribute__((section("pm_dram_reclaim_pool")))
pm_err_flag_type pm_droop_detect_irq_config(pm_pwr_data_type *pwr_data, pm_comm_info_type *comm_ptr, 
                                            uint8 resource_index, uint32 isr_ctx)
{
    pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;
    pm_pwr_irq_type irq_type = PM_PWR_IRQ_VREG_FAULT;
    pm_irq_trigger_type trig_type = PM_IRQ_TRIGGER_RISING_EDGE;

    /* Clear the VREG_FAULT interrupt */
    err_flag = pm_pwr_irq_clear_alg(pwr_data, comm_ptr, resource_index, irq_type);

    /* Disable the VREG_FAULT interrupt */
    err_flag |= pm_pwr_irq_enable_alg(pwr_data, comm_ptr, resource_index, irq_type, FALSE); 

    /* Set the power rails's VREG_FAULT interrupt polarity to RISING_EDGE */
    err_flag |= pm_pwr_irq_set_trigger_alg(pwr_data, comm_ptr, resource_index, irq_type, trig_type);

    /* Register the ISR to the power rails's VREG_FAULT interrupt */
    err_flag |= pm_pwr_irq_register_isr_alg(pwr_data, comm_ptr, resource_index, irq_type, (void*)&pm_droop_detect_isr, isr_ctx); 
    
    return err_flag;
}

static void* pm_droop_detect_isr (uint32 isr_ctx, uint32 irq_mask)
{
   static uint8 pm_droop_detect_arr_index = 0;

   uint32 slave_id = 0;
   uint32 periph_id = 0;

   if(pm_droop_detect_arr_index >= PM_DROOP_LOG_ARRAY_SIZE)
   {
      // reset the droop detect array index
      pm_droop_detect_arr_index = 0;
   }

   // isr_ctx (periph_id <0:15> slave_id <16:31>)
   slave_id = ((isr_ctx>>16) & 0xFFFF);
   periph_id = (isr_ctx & 0xFFFF);

   // save the time_stamp, slave_id and periph_id
   pm_droop_detect_info[pm_droop_detect_arr_index].time_stamp = timetick_get64();
   pm_droop_detect_info[pm_droop_detect_arr_index].slave_id = slave_id;
   pm_droop_detect_info[pm_droop_detect_arr_index].base_address = (uint32)((periph_id<<8) & 0xFF00);
   pm_droop_detect_info[pm_droop_detect_arr_index].irq_mask = (uint8)(irq_mask & 0xFF);


   // increment the droop detect array index
   pm_droop_detect_arr_index++;

   // increment the isr hit count
   pm_droop_detect_count++;
   
   pm_droop_detect_isr_triggered = TRUE;

   return NULL;
}

pm_err_flag_type pm_droop_detect_rpm_callback (void)
{
   pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;
   uint16 addr = 0;
   uint8 data = 0;
   uint8 arr_index = 0;

   for(arr_index = 0; arr_index < PM_DROOP_LOG_ARRAY_SIZE; arr_index++)
   {
      if(pm_droop_detect_info[arr_index].irq_mask == 0)
      {
         continue;
      }

      err_flag |= pm_rpm_status_reg_dump(pm_droop_detect_info[arr_index].slave_id, 
                                         pm_droop_detect_info[arr_index].base_address, 
                                         &pm_droop_rail_status[arr_index]);

      // get the addr and data to clear the interrupt latched status   
      addr = (uint16)(pm_droop_detect_info[arr_index].base_address + PM_INT_LATCHED_CLR_REG_OFFSET);
      data = (uint8)(pm_droop_detect_info[arr_index].irq_mask & 0xFF);

      // clear the interrupt latched status
      err_flag |= pm_comm_write_byte(pm_droop_detect_info[arr_index].slave_id, addr, data, 0);

      pm_droop_detect_info[arr_index].irq_mask = 0;
   }

   if (pm_droop_detect_abort_enable == TRUE)
   {
      // abort
      CORE_VERIFY(0);
   }

   pm_droop_detect_isr_triggered = FALSE;

   return err_flag;
}

boolean pm_is_droop_detected (void)
{
   return pm_droop_detect_isr_triggered;
}

