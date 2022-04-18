/*! \file pm_clk_xo.c
*  \n
*  \brief Implementation file for CLK XO public APIs.
*  \n  
*  &copy; Copyright 2013-2016 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

$Header: //components/rel/rpm.bf/1.8/core/pmic/pm/drivers/clk/src/pm_clk_xo.c#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
05/20/13   aks      Created as a part of code re-architecture
========================================================================== */
/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "pm_clk_xo.h"
#include "pm_clk_driver.h"
#include "pm_comm.h"


/*===========================================================================

                     STRUCTURE TYPE AND ENUM

===========================================================================*/

/* Max XO Warm up timer value in sleep (32KHz) clock cycles. */
#define PM_XO_MAX_WARMUP_TIME_SLP_CLK_CYCLES            0x7FF
#define PM_XO_38P4MHZ_MAX_WARMUP_TIME_SLP_CLK_CYCLES    0x1FE

/*===========================================================================

                     API IMPLEMENTATION 

===========================================================================*/
__attribute__((section("pm_cram_reclaim_pool")))
pm_err_flag_type pm_clk_xo_set_warmup_time(uint8 pmic_chip, pm_clk_type periph, uint32 num_sleep_clk_cycles)
{
    pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;
    pm_clk_data_type *clk_ptr = pm_clk_get_data(pmic_chip);
    pm_register_address_type reg = 0;
    pm_register_data_type data = 0;
    pm_register_data_type data_arr[2] = {0};
    uint32 periph_index = 0;

    if ((clk_ptr == NULL) || (clk_ptr->comm_ptr == NULL))
    {
        return PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
    }

    if ((periph != PM_CLK_XO) && (periph != PM_CLK_BB_1) && (periph != PM_CLK_LN_BB))
    {
        return PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
    }

    periph_index = clk_ptr->clk_perph_index[periph];

    if((periph_index == PM_CLK_INVALID_DATA) || (periph_index >= PM_MAX_NUM_CLKS) || (periph_index >= clk_ptr->num_of_peripherals))
    {
        return PM_ERR_FLAG__INVALID_CLK_INDEXED;
    }

    reg = clk_ptr->clk_reg_table->base_address + (pm_register_address_type)(clk_ptr->clk_reg_table->peripheral_offset*periph_index) + 
          clk_ptr->clk_xo_reg_table->TIMER1;

    if (clk_ptr->periph_subtype[periph_index] == PM_HW_MODULE_CLOCK_XO_CORE)
    {
        /* If the user entered XO Warm up delay timer value is greater
           than max allowed, set the max value and return error */
        if (num_sleep_clk_cycles > PM_XO_MAX_WARMUP_TIME_SLP_CLK_CYCLES)
        {
            num_sleep_clk_cycles = (uint32)PM_XO_MAX_WARMUP_TIME_SLP_CLK_CYCLES;
            err_flag = PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
        }

        data_arr[0] = (pm_register_data_type)(num_sleep_clk_cycles & 0xFF);
        data_arr[1] = (pm_register_data_type)((num_sleep_clk_cycles>>8) & 0x07);

        err_flag |= pm_comm_write_byte_array(clk_ptr->comm_ptr->slave_id, reg, 2, data_arr, 0);
    }
    else if ((clk_ptr->periph_subtype[periph_index] == PM_HW_MODULE_CLOCK_XO_CORE_38P4MHZ) ||
             (clk_ptr->periph_subtype[periph_index] == PM_HW_MODULE_CLOCK_BB_CLK))
    {
        /* If the user entered XO Warm up delay timer value is greater
           than max allowed, set the max value and return error */
        if (num_sleep_clk_cycles > PM_XO_38P4MHZ_MAX_WARMUP_TIME_SLP_CLK_CYCLES)
        {
            num_sleep_clk_cycles = (uint32)PM_XO_38P4MHZ_MAX_WARMUP_TIME_SLP_CLK_CYCLES;
            err_flag = PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
        }

        /* Delay time configured is twice the number of sleep (32kHz) clock cycles */
        data = (pm_register_data_type)((num_sleep_clk_cycles + 1)/2);

        err_flag |= pm_comm_write_byte(clk_ptr->comm_ptr->slave_id, reg, data, 0);
    }
    else
    {
        err_flag |= PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
    }

    return err_flag;
}

pm_err_flag_type pm_clk_xo_get_warmup_time(uint8 pmic_chip, pm_clk_type periph, uint32 *num_sleep_clk_cycles)
{
    pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;
    pm_clk_data_type *clk_ptr = pm_clk_get_data(pmic_chip);
    pm_register_address_type reg = 0;
    pm_register_data_type data = 0;
    uint32 periph_index = 0;

    if ((clk_ptr == NULL) || (clk_ptr->comm_ptr == NULL))
    {
        return PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
    }

    if (num_sleep_clk_cycles == NULL)
    {
        return PM_ERR_FLAG__INVALID_POINTER;
    }

    if ((periph != PM_CLK_XO) && (periph != PM_CLK_BB_1) && (periph != PM_CLK_LN_BB))
    {
        return PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
    }

    periph_index = clk_ptr->clk_perph_index[periph];

    if((periph_index == PM_CLK_INVALID_DATA) || (periph_index >= PM_MAX_NUM_CLKS) || (periph_index >= clk_ptr->num_of_peripherals))
    {
        return PM_ERR_FLAG__INVALID_CLK_INDEXED;
    }

    reg = clk_ptr->clk_reg_table->base_address + (pm_register_address_type)(clk_ptr->clk_reg_table->peripheral_offset*periph_index) + 
          clk_ptr->clk_xo_reg_table->TIMER1;

    if (clk_ptr->periph_subtype[periph_index] == PM_HW_MODULE_CLOCK_XO_CORE)
    {

        err_flag = pm_comm_read_byte_array(clk_ptr->comm_ptr->slave_id, reg, 2, (uint8*)num_sleep_clk_cycles, 0);

    }
    else if ((clk_ptr->periph_subtype[periph_index] == PM_HW_MODULE_CLOCK_XO_CORE_38P4MHZ) ||
             (clk_ptr->periph_subtype[periph_index] == PM_HW_MODULE_CLOCK_BB_CLK))
    {
        err_flag = pm_comm_read_byte(clk_ptr->comm_ptr->slave_id, reg, &data, 0);

        /* Delay time configured is twice the number of sleep (32kHz) clock cycles */
        *num_sleep_clk_cycles = (uint32)(data * 2);
    }
    else
    {
        err_flag = PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
    }

    return err_flag;
}
