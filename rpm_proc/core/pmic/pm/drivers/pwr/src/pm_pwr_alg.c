/*! \file pm_pwr_alg.c 
*  \n
*  \brief  
*  \n  
*  \n &copy; Copyright 2012-2016 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

$Header: //components/rel/rpm.bf/1.8/core/pmic/pm/drivers/pwr/src/pm_pwr_alg.c#2 $

when        who     what, where, why
--------    ---     ----------------------------------------------------------
07/22/14   aks     Adding API to round off voltage
12/06/12   hw      Rearchitecturing module driver to peripheral driver
========================================================================== */
/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "pm_pwr_alg.h"
#include "pm_comm.h"
#include "pm_debug.h"

#define SMART_BOOST_OFFSET         0xE6 //store this offset here instead of config since this bit is going to be erased in new HW
#define STEPPER_OK                 0x81
#define VREG_OK                    0x80
#define STATUS2_OFFSET             0x009
#define OCP_CTL2_OFFSET            0x04B

uint32 pm_ocp_rail_count;
#define PM_OCP_RAIL_STATUS_SIZE    3
pm_pwr_ocp_rail_status pm_ocp_rail_status[PM_OCP_RAIL_STATUS_SIZE] = { 0 }; 
/*===========================================================================

                     FUNCTION IMPLEMENTATION 

===========================================================================*/

pm_err_flag_type pm_pwr_pull_down_alg(pm_pwr_data_type *pwr_data, pm_comm_info_type *comm_ptr, uint8 peripheral_index, pm_on_off_type on_off)
{
    pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;
    uint8 periph_type = 0;
    
    if ((peripheral_index >= pwr_data->num_of_peripherals) || (pwr_data->pwr_specific_info[peripheral_index].periph_type == 0))
    {
        err_flag = PM_ERR_FLAG__INVALID_RESOURCE_ACCESS_ATTEMPTED;
    }
    else if (on_off >= PM_INVALID)
    {
        err_flag = PM_ERR_FLAG__MACRO_NOT_RECOGNIZED;
    }
    else
    {
        pm_register_address_type          reg = 0xFF;
        pm_register_data_type             data = 0xFF;

        periph_type = pwr_data->pwr_specific_info[peripheral_index].periph_type;
    
        reg = (pm_register_address_type)(pwr_data->pwr_specific_info[peripheral_index].periph_base_address + pwr_data->pwr_reg_table->PD_CTL);
    
        data = (PM_OFF == on_off) ? 0 : 0x80;

        err_flag = pm_comm_write_byte_mask(comm_ptr->slave_id, reg, 0x80, data, 0);
    }

    if (PM_ERR_FLAG__SUCCESS != err_flag)
    {
        PM_LOG_MSG_ERROR(PMIC_DRV_PWR_PULL_DOWN_ERROR, comm_ptr->pmic_index, periph_type, peripheral_index, err_flag);
    }

    return err_flag;
}

pm_err_flag_type pm_pwr_sw_mode_status_alg(pm_pwr_data_type *pwr_data, pm_comm_info_type *comm_ptr, uint8 peripheral_index, pm_sw_mode_type *sw_mode)
{
    pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;
    uint8 periph_type = 0;
                                                          
    if ((peripheral_index >= pwr_data->num_of_peripherals) || (pwr_data->pwr_specific_info[peripheral_index].periph_type == 0))
    {
        err_flag = PM_ERR_FLAG__INVALID_RESOURCE_ACCESS_ATTEMPTED;
    }
    else if (sw_mode == NULL)
    {
        err_flag = PM_ERR_FLAG__INVALID_POINTER;
    }
    else
    {
        pm_register_address_type           reg = 0x0;
        pm_register_data_type              data = 0xFF;

        periph_type = pwr_data->pwr_specific_info[peripheral_index].periph_type;
            
        reg = (pm_register_address_type)(pwr_data->pwr_specific_info[peripheral_index].periph_base_address + pwr_data->pwr_reg_table->MODE_CTL);

        err_flag = pm_comm_read_byte(comm_ptr->slave_id, reg, &data, 0);
        
        if (err_flag == PM_ERR_FLAG__SUCCESS)
        {
            if (pwr_data->pwr_specific_info[peripheral_index].is_periph_unified_reg == TRUE)
            {
                if (data == 7)
                {
                    *sw_mode = PM_SW_MODE_NPM;
                }
                else if ((data == 6) && (periph_type != PM_HW_MODULE_LDO))
                {
                    *sw_mode = PM_SW_MODE_AUTO;
                }
                else if (data == 5)
                {
                    *sw_mode = PM_SW_MODE_LPM;
                }
                else if (data == 4)
                {
                    *sw_mode = PM_SW_MODE_RETENTION;
                }
                else if ((data <= 3) && (data >= 1) && (periph_type == PM_HW_MODULE_LDO))
                {
                    // applicable for LDOs only
                    *sw_mode = PM_SW_MODE_BYPASS;
                }
                else
                {
                    *sw_mode = PM_SW_MODE_INVALID;
                }
            }
            else
            {
                /* BYPASS supercedes NPM & PFM */
                /* Only valid for LDO's */
                if (data & 0x20)
                {
                    *sw_mode = PM_SW_MODE_BYPASS;
                }
                /* NPM supercedes AUTO & PFM */
                else if (data & 0x80)
                {
                    *sw_mode = PM_SW_MODE_NPM;
                }
                /* AUTO supercedes PFM */
                /* only valid for SMPS */
                else if (data & 0x40)
                {
                    *sw_mode = PM_SW_MODE_AUTO;
                }
                else /* IT MIGHT BE PFM DEPENDING ON pc_mode bits */
                {
                    *sw_mode = PM_SW_MODE_LPM;
                }
            }
        }
        else
        {
            *sw_mode = PM_SW_MODE_INVALID;
        }
    }

    if (PM_ERR_FLAG__SUCCESS != err_flag)
    {
        PM_LOG_MSG_ERROR(PMIC_DRV_PWR_MODE_ERROR, comm_ptr->pmic_index, periph_type, peripheral_index, err_flag);
    }

    return err_flag;
}

pm_err_flag_type pm_pwr_sw_mode_status_raw_alg(pm_pwr_data_type *pwr_data, pm_comm_info_type *comm_ptr, uint8 peripheral_index, uint8 *mode_ctl)
{
    pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;
    uint8 periph_type = 0;
                                                          
    if ((peripheral_index >= pwr_data->num_of_peripherals) || (pwr_data->pwr_specific_info[peripheral_index].periph_type == 0))
    {
        err_flag = PM_ERR_FLAG__INVALID_RESOURCE_ACCESS_ATTEMPTED;
    }
    else if (mode_ctl == NULL)
    {
        err_flag = PM_ERR_FLAG__INVALID_POINTER;
    }
    else
    {
        pm_register_address_type           reg = 0x0;
        pm_register_data_type              data = 0xFF;

        periph_type = pwr_data->pwr_specific_info[peripheral_index].periph_type;
            
        reg = (pm_register_address_type)(pwr_data->pwr_specific_info[peripheral_index].periph_base_address + pwr_data->pwr_reg_table->MODE_CTL);

        err_flag = pm_comm_read_byte(comm_ptr->slave_id, reg, &data, 0);
        
        if (err_flag == PM_ERR_FLAG__SUCCESS)
        {
            *mode_ctl = data;
        }
    }

    if (PM_ERR_FLAG__SUCCESS != err_flag)
    {
        PM_LOG_MSG_ERROR(PMIC_DRV_PWR_MODE_ERROR, comm_ptr->pmic_index, periph_type, peripheral_index, err_flag);
    }

    return err_flag;
}

pm_err_flag_type pm_pwr_pin_ctrl_alg(pm_pwr_data_type *pwr_data, pm_comm_info_type *comm_ptr, uint8 peripheral_index, uint8 select_pin)
{
    pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;
    uint8 periph_type = 0;

    if ((peripheral_index < pwr_data->num_of_peripherals) && (pwr_data->pwr_specific_info[peripheral_index].periph_type != 0))
    {
        pm_register_address_type reg = 0x0;

        periph_type = pwr_data->pwr_specific_info[peripheral_index].periph_type;

        if (pwr_data->pwr_specific_info[peripheral_index].is_periph_unified_reg ==  TRUE)
        {
            reg = (pm_register_address_type)(pwr_data->pwr_specific_info[peripheral_index].periph_base_address + pwr_data->pwr_reg_table->FOLLOW_HWEN);
        }
        else
        {
            reg = (pm_register_address_type)(pwr_data->pwr_specific_info[peripheral_index].periph_base_address + pwr_data->pwr_reg_table->EN_CTL);
        }

        err_flag = pm_comm_write_byte_mask(comm_ptr->slave_id, reg, 0x0F, (pm_register_data_type)select_pin, 1); // bit<0:3>
    }
    else
    {
        err_flag = PM_ERR_FLAG__INVALID_RESOURCE_ACCESS_ATTEMPTED;
    }

    if (PM_ERR_FLAG__SUCCESS == err_flag)
    {
        PM_LOG_MSG_DEBUG(PMIC_DRV_PWR_PIN_CTRL, comm_ptr->pmic_index, periph_type, peripheral_index, select_pin);
    }
    else
    {
        PM_LOG_MSG_ERROR(PMIC_DRV_PWR_PIN_CTRL_ERROR, comm_ptr->pmic_index, periph_type, peripheral_index, err_flag);
    }

    return err_flag;
}

pm_err_flag_type pm_pwr_pin_ctrl_mode_alg(pm_pwr_data_type *pwr_data, pm_comm_info_type *comm_ptr, uint8 peripheral_index, uint8 select_pin)
{
    pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;
    uint8 periph_type = 0;
    uint8 mask = 0;

    if ((peripheral_index < pwr_data->num_of_peripherals) && (pwr_data->pwr_specific_info[peripheral_index].periph_type != 0))
    {
        pm_register_address_type reg = 0x0;

        periph_type = pwr_data->pwr_specific_info[peripheral_index].periph_type;

        if (pwr_data->pwr_specific_info[peripheral_index].is_periph_unified_reg ==  TRUE)
        {
            reg = (pm_register_address_type)(pwr_data->pwr_specific_info[peripheral_index].periph_base_address + pwr_data->pwr_reg_table->FOLLOW_HWEN);
            mask = 0xF0;
            select_pin = (select_pin<<4);
        }
        else
        {
            reg = (pm_register_address_type)(pwr_data->pwr_specific_info[peripheral_index].periph_base_address + pwr_data->pwr_reg_table->MODE_CTL);
            mask = 0x1F;
        }

        err_flag = pm_comm_write_byte_mask(comm_ptr->slave_id, reg, mask, (pm_register_data_type)select_pin, 0); // bit<0:4>
    }
    else
    {
        err_flag = PM_ERR_FLAG__INVALID_RESOURCE_ACCESS_ATTEMPTED;
    }

    if (PM_ERR_FLAG__SUCCESS == err_flag)
    {
        PM_LOG_MSG_DEBUG(PMIC_DRV_PWR_PIN_CTRL_MODE, comm_ptr->pmic_index, periph_type, peripheral_index, select_pin);
    }
    else
    {
        PM_LOG_MSG_ERROR(PMIC_DRV_PWR_PIN_CTRL_ERROR, comm_ptr->pmic_index, periph_type, peripheral_index, err_flag);
    }

    return err_flag;
}

pm_err_flag_type pm_pwr_sw_en_pin_ctl_alg(pm_pwr_data_type *pwr_data, pm_comm_info_type *comm_ptr, uint8 peripheral_index, 
                                          pm_on_off_type on_off , uint8 select_pin)
{
    pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;
    uint8 periph_type = 0;
    uint8 perph_revision = 0;
    uint8 sw_en = 0;
    uint8 pc_en = 0;

    if (peripheral_index < pwr_data->num_of_peripherals && 
              pwr_data->pwr_specific_info[peripheral_index].periph_type != 0)
    {
        pm_register_address_type sec_reg = 0;
        pm_register_address_type smart_boost_reg = 0;   
        pm_register_address_type pin_ctl_reg = 0;   
        pm_register_address_type en_ctl_reg = (pm_register_address_type)(pwr_data->pwr_specific_info[peripheral_index].periph_base_address + pwr_data->pwr_reg_table->EN_CTL);
        periph_type = pwr_data->pwr_specific_info[peripheral_index].periph_type;


        if (pwr_data->pwr_specific_info[peripheral_index].is_periph_unified_reg ==  TRUE)
        {
            pin_ctl_reg = (pm_register_address_type)(pwr_data->pwr_specific_info[peripheral_index].periph_base_address + pwr_data->pwr_reg_table->FOLLOW_HWEN);

            if(on_off != 0)
            {
                sw_en = 0x80;
            }
            
            err_flag = pm_comm_write_byte(comm_ptr->slave_id, en_ctl_reg, sw_en, 1);

            err_flag |= pm_comm_write_byte_mask(comm_ptr->slave_id, pin_ctl_reg, 0x0F, (pm_register_data_type)select_pin, 1); // bit<0:3>
        }
        else if (periph_type == PM_HW_MODULE_BOOST)
        {
            smart_boost_reg = (pm_register_address_type)(pwr_data->pwr_specific_info[peripheral_index].periph_base_address + 0x1);

            err_flag = pm_comm_read_byte(comm_ptr->slave_id, smart_boost_reg, &perph_revision, 1);

            if(perph_revision <=2)
            {
                sec_reg = (pm_register_address_type)(pwr_data->pwr_specific_info[peripheral_index].periph_base_address + pwr_data->pwr_reg_table->SEC_ACCESS);
                smart_boost_reg = (pm_register_address_type)(pwr_data->pwr_specific_info[peripheral_index].periph_base_address + SMART_BOOST_OFFSET);

                //unlock the register
                err_flag = pm_comm_write_byte(comm_ptr->slave_id, sec_reg, 0xA5, 0);

                if(on_off != 0)
                {
                    sw_en = 0x80;
                }
                else if(select_pin != 0)
                {
                    sw_en = 0x80;
                    pc_en = 0x80;
                }
                err_flag = pm_comm_write_byte(comm_ptr->slave_id, smart_boost_reg, pc_en, 1); // bit<7>
                err_flag = pm_comm_write_byte(comm_ptr->slave_id, en_ctl_reg,  sw_en, 1); 
            } 
            else
            {
                if(on_off != 0)
                {
                    sw_en = 0x80;
                }

                err_flag = pm_comm_write_byte(comm_ptr->slave_id, en_ctl_reg,  ( sw_en | (0xF & select_pin)), 1); 
            }
        }   
        else
        {   
            if(on_off != 0)
            {
                sw_en = 0x80;
            }
            
            err_flag = pm_comm_write_byte(comm_ptr->slave_id, en_ctl_reg,  ( sw_en | (0xF & select_pin)), 1); 
        }
        
    }
    else
    {
        err_flag = PM_ERR_FLAG__INVALID_RESOURCE_ACCESS_ATTEMPTED;
    }
    
    if (PM_ERR_FLAG__SUCCESS == err_flag)
    {
        PM_LOG_MSG_DEBUG(PMIC_DRV_PWR_PIN_CTRL, comm_ptr->pmic_index, periph_type, peripheral_index, select_pin);
        PM_LOG_MSG_DEBUG(PMIC_DRV_PWR_SW_EN, comm_ptr->pmic_index, periph_type, peripheral_index, on_off);
    }
    else
    {
        PM_LOG_MSG_ERROR(PMIC_DRV_PWR_PIN_CTRL_ERROR, comm_ptr->pmic_index, periph_type, peripheral_index, err_flag);
        PM_LOG_MSG_ERROR(PMIC_DRV_PWR_SW_EN_ERROR, comm_ptr->pmic_index, periph_type, peripheral_index, err_flag);
    }
    
    return err_flag;

}


pm_err_flag_type pm_pwr_sw_enable_alg(pm_pwr_data_type *pwr_data, pm_comm_info_type *comm_ptr, uint8 peripheral_index, pm_on_off_type on_off)
{
    pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;
    uint8 periph_type = 0;

    if ((peripheral_index >= pwr_data->num_of_peripherals) || (pwr_data->pwr_specific_info[peripheral_index].periph_type == 0))
    {
        err_flag = PM_ERR_FLAG__INVALID_RESOURCE_ACCESS_ATTEMPTED;
    }
    else if (on_off >= PM_INVALID)
    {
        err_flag = PM_ERR_FLAG__MACRO_NOT_RECOGNIZED;
    }
    else
    {
        pm_register_address_type reg = 0x0;
        pm_register_data_type data = 0;

        periph_type = pwr_data->pwr_specific_info[peripheral_index].periph_type;
            
        reg = (pm_register_address_type)(pwr_data->pwr_specific_info[peripheral_index].periph_base_address + pwr_data->pwr_reg_table->EN_CTL);

        if (PM_OFF == on_off)
        {
            data = 0;
        }
        else
        {
            data = 0x80;
        }

        if (pwr_data->pwr_specific_info[peripheral_index].is_periph_unified_reg ==  TRUE)
        {
            err_flag = pm_comm_write_byte(comm_ptr->slave_id, reg, data, 0);
        }
        else
        {
            err_flag = pm_comm_write_byte_mask(comm_ptr->slave_id, reg, 0x80, data, 0);
        }
    }

    if (PM_ERR_FLAG__SUCCESS == err_flag)
    {
        PM_LOG_MSG_DEBUG(PMIC_DRV_PWR_SW_EN, comm_ptr->pmic_index, periph_type, peripheral_index, on_off);
    }
    else
    {
        PM_LOG_MSG_ERROR(PMIC_DRV_PWR_SW_EN_ERROR, comm_ptr->pmic_index, periph_type, peripheral_index, err_flag);
    }

    return err_flag;
}

pm_err_flag_type pm_pwr_sw_enable_status_alg(pm_pwr_data_type *pwr_data, pm_comm_info_type *comm_ptr, uint8 peripheral_index, pm_on_off_type *on_off)
{
    pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;
    uint8 periph_type = 0;

    if ((peripheral_index >= pwr_data->num_of_peripherals) || (pwr_data->pwr_specific_info[peripheral_index].periph_type == 0))
    {
        err_flag = PM_ERR_FLAG__INVALID_RESOURCE_ACCESS_ATTEMPTED;
    }
    else if (on_off == NULL)
    {
        err_flag = PM_ERR_FLAG__INVALID_POINTER;
    }
    else
    {
        pm_register_address_type           reg = 0x0;
        pm_register_data_type              data = 0;

        periph_type = pwr_data->pwr_specific_info[peripheral_index].periph_type;

        reg = (pm_register_address_type)(pwr_data->pwr_specific_info[peripheral_index].periph_base_address + pwr_data->pwr_reg_table->EN_CTL);

        err_flag = pm_comm_read_byte(comm_ptr->slave_id, reg, &data, 0);
        if (err_flag != PM_ERR_FLAG__SUCCESS)
        {
            *on_off = PM_INVALID;
            return err_flag;
        }

        if (data & 0x80)
        {
            *on_off = PM_ON;
        }
        else
        {
            *on_off = PM_OFF;
        }
    }

    if (PM_ERR_FLAG__SUCCESS != err_flag)
    {
        PM_LOG_MSG_ERROR(PMIC_DRV_PWR_SW_EN_ERROR, comm_ptr->pmic_index, periph_type, peripheral_index, err_flag);
    }

    return err_flag;
}

pm_err_flag_type pm_pwr_is_vreg_ready_alg(pm_pwr_data_type *pwr_data, pm_comm_info_type *comm_ptr, 
                                                 uint8 peripheral_index, boolean *vreg_ready)
{
    pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;
    uint8 vreg_mask = 0;
    uint8 periph_type = 0;

    if (peripheral_index >= pwr_data->num_of_peripherals || 
             pwr_data->pwr_specific_info[peripheral_index].periph_type == 0)
    {
        err_flag = PM_ERR_FLAG__INVALID_RESOURCE_ACCESS_ATTEMPTED;
    }
    else if (vreg_ready == NULL)
    {
        err_flag = PM_ERR_FLAG__INVALID_POINTER;
    }
    else
    {
        pm_register_address_type reg = 0x0;
        pm_register_data_type data = 0;
        periph_type = pwr_data->pwr_specific_info[peripheral_index].periph_type;

        reg = (pm_register_address_type)(pwr_data->pwr_specific_info[peripheral_index].periph_base_address + pwr_data->pwr_reg_table->STATUS);

        err_flag = pm_comm_read_byte(comm_ptr->slave_id, reg, &data, 0);
        if (err_flag != PM_ERR_FLAG__SUCCESS)
        {
            err_flag = pm_comm_read_byte(comm_ptr->slave_id, reg, &data, 0);
            if (err_flag != PM_ERR_FLAG__SUCCESS)
            {
                *vreg_ready = FALSE;
                return err_flag;
            }
        }

        if (pwr_data->pwr_specific_info[peripheral_index].is_periph_unified_reg == TRUE)
        {
            // In the new peripherals, VREG_READY bit is used which indicates both VREG_OK and STEPPER_OK
            vreg_mask = VREG_OK; 
        }
        else if (pwr_data->pwr_specific_info[peripheral_index].is_periph_stepper == TRUE)
        {
            vreg_mask = STEPPER_OK; 
        }
        else
        {
            vreg_mask = VREG_OK;
        }

        if ((data & vreg_mask) == vreg_mask)
        {
            *vreg_ready = TRUE;
        }
        else
        {
            *vreg_ready = FALSE;
        }
    }

    if (PM_ERR_FLAG__SUCCESS != err_flag)
    {
        PM_LOG_MSG_ERROR(PMIC_DRV_PWR_SW_EN_ERROR, comm_ptr->pmic_index, periph_type, peripheral_index, err_flag);
    }

    return err_flag;
}

pm_err_flag_type pm_pwr_volt_level_alg(pm_pwr_data_type *pwr_data, pm_comm_info_type *comm_ptr, uint8 peripheral_index, pm_volt_level_type  volt_level)
{
    pm_err_flag_type                  err_flag = PM_ERR_FLAG__SUCCESS;
    uint32                            vmin = 0;  // microvolt
    uint32                            vStep = 0; // microvolt
    uint32                            range = 0; // 0 to 4
    uint32                            calculated_vset = 0;
    pm_register_data_type             vset_ht[2] = {0};
    pm_register_data_type             vset = 0;
    pm_register_data_type             mask = 0;
    pm_register_address_type          reg = 0;
    uint8                             periph_type = 0;

    if (peripheral_index >= (pwr_data->num_of_peripherals) || 
            pwr_data->pwr_specific_info[peripheral_index].periph_type == 0)
    {
        err_flag = PM_ERR_FLAG__INVALID_RESOURCE_ACCESS_ATTEMPTED ;
    }
    else
    {
        periph_type = pwr_data->pwr_specific_info[peripheral_index].periph_type;

        range = pwr_data->pwr_specific_info[peripheral_index].pwr_range;
        if ((volt_level <= pwr_data->pwr_specific_info[peripheral_index].pwr_vset[range].RangeMax) && 
            (volt_level >= pwr_data->pwr_specific_info[peripheral_index].pwr_vset[range].RangeMin) )
        {
            vmin = pwr_data->pwr_specific_info[peripheral_index].pwr_vset[range].RangeMin;
            vStep = pwr_data->pwr_specific_info[peripheral_index].pwr_vset[range].VStep;
        }
       
        if (vStep > 0)
        {
            calculated_vset = (volt_level - vmin)/vStep;

            if (pwr_data->pwr_specific_info[peripheral_index].is_periph_unified_reg ==  TRUE)
            {
                vset_ht[0] = ((calculated_vset) & 0xFF);
                vset_ht[1] = ((calculated_vset>>8) & 0xFF);

                reg =  (pm_register_address_type)(pwr_data->pwr_specific_info[peripheral_index].periph_base_address + pwr_data->pwr_reg_table->VOLTAGE_CTRL1);

                // Set vset
                err_flag = pm_comm_write_byte_array(comm_ptr->slave_id, reg, 2, vset_ht, 0);
            }
            else
            {
                //calculate VSET
                vset = (pm_register_data_type)(calculated_vset);

                // Set VSET
                reg =  (pm_register_address_type)(pwr_data->pwr_specific_info[peripheral_index].periph_base_address + pwr_data->pwr_reg_table->VOLTAGE_CTRL2);

                if ((PM_HW_MODULE_ULT_BUCK == periph_type) && (1 == range))
                {
                    // since bit<5> and bit<6> are used for range
                    mask = 0x1F; 

                    // Set the vset then
                    err_flag = pm_comm_write_byte_mask(comm_ptr->slave_id, reg, mask, vset , 0);
                }
                else
                {
                    // Set vset
                    err_flag = pm_comm_write_byte(comm_ptr->slave_id, reg, vset , 0);
                }
            }
        }
        else
        {
            err_flag = PM_ERR_FLAG__VLEVEL_OUT_OF_RANGE;
        }
    }

    if (PM_ERR_FLAG__SUCCESS == err_flag)
    {
        PM_LOG_MSG_DEBUG(PMIC_DRV_PWR_VOLT_LVL, comm_ptr->pmic_index, periph_type, peripheral_index, volt_level);
    }
    else
    {
        PM_LOG_MSG_ERROR(PMIC_DRV_PWR_VOLT_LVL_ERROR, comm_ptr->pmic_index, periph_type, peripheral_index, err_flag);
    }

    return err_flag;
}

pm_err_flag_type pm_pwr_volt_level_status_alg(pm_pwr_data_type *pwr_data, pm_comm_info_type *comm_ptr, uint8  peripheral_index, pm_volt_level_type *volt_level)
{
    pm_err_flag_type                 err_flag = PM_ERR_FLAG__SUCCESS;
    uint32                           vmin = 0; // microvolt
    uint32                           vStep = 0; //microvolt
    uint32                           range = 0; // 0 to 4
    uint16                           vset_ht = 0;
    pm_register_data_type            vset = 0;
    pm_register_address_type         reg = 0;
    pm_register_data_type            reg_data[2] = {0};
    boolean                          vreg_ready = FALSE;
    uint8                            periph_type = 0;

    if (peripheral_index >= (pwr_data->num_of_peripherals) || 
            pwr_data->pwr_specific_info[peripheral_index].periph_type == 0)
    {
        err_flag = PM_ERR_FLAG__INVALID_RESOURCE_ACCESS_ATTEMPTED;
    }
    else if (volt_level == NULL)
    {
        err_flag = PM_ERR_FLAG__INVALID_POINTER;
    }
    else
    {
        periph_type = pwr_data->pwr_specific_info[peripheral_index].periph_type;

        err_flag |= pm_pwr_is_vreg_ready_alg(pwr_data, comm_ptr, peripheral_index, &vreg_ready);

        if ((pwr_data->pwr_specific_info[peripheral_index].is_periph_unified_reg ==  TRUE) && 
            (vreg_ready ==  TRUE))
        {
            reg =  (pm_register_address_type)(pwr_data->pwr_specific_info[peripheral_index].periph_base_address + pwr_data->pwr_reg_table->VSET_VALID_LB);
        }
        else
        {
            // get the voltage level LUT
            reg =  (pm_register_address_type)(pwr_data->pwr_specific_info[peripheral_index].periph_base_address + pwr_data->pwr_reg_table->VOLTAGE_CTRL1);
        }

        err_flag |= pm_comm_read_byte_array(comm_ptr->slave_id, reg, 2, reg_data, 0);

        if ( err_flag == PM_ERR_FLAG__SUCCESS )
        {
            range = pwr_data->pwr_specific_info[peripheral_index].pwr_range;
            vmin = pwr_data->pwr_specific_info[peripheral_index].pwr_vset[range].RangeMin; // microvolt
            vStep = pwr_data->pwr_specific_info[peripheral_index].pwr_vset[range].VStep; //microvolt

            if (pwr_data->pwr_specific_info[peripheral_index].is_periph_unified_reg == TRUE)
            {
                vset_ht = (reg_data[1]<<8) | (reg_data[0]);

                *volt_level = vmin + vset_ht * vStep;
            }
            else
            {
                vset = reg_data[1];
                if ((1 == range) && (PM_HW_MODULE_ULT_BUCK == periph_type))
                {
                    vset &= 0x1F;
                }

                *volt_level = vmin + vset * vStep;
            }
        }
    }

    if (PM_ERR_FLAG__SUCCESS != err_flag)
    {
        PM_LOG_MSG_ERROR(PMIC_DRV_PWR_VOLT_LVL_ERROR, comm_ptr->pmic_index, periph_type, peripheral_index, err_flag);
    }

    return err_flag;
}

pm_err_flag_type pm_pwr_volt_calculate_vset_celing_uv(pm_pwr_data_type *pwr_data, pm_comm_info_type *comm_ptr, 
                                                      uint8 peripheral_index, pm_volt_level_type req_volt_level, 
                                                      uint32 *calculated_vset, pm_volt_level_type *ceiling_uv )
{
    pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;
    uint32           vmin = 0; // microvolt
    uint32           vStep = 0; //microvolt
    uint32           range = 0; //microvolt
    uint8            periph_type = 0;
    uint32           vset =  0;

    if (peripheral_index >= (pwr_data->num_of_peripherals) || 
            pwr_data->pwr_specific_info[peripheral_index].periph_type == 0)
    {
        err_flag = PM_ERR_FLAG__INVALID_RESOURCE_ACCESS_ATTEMPTED;
    }
    else if (calculated_vset == NULL || ceiling_uv == NULL)
    {
        err_flag = PM_ERR_FLAG__INVALID_POINTER;
    }
    else
    {
        periph_type = pwr_data->pwr_specific_info[peripheral_index].periph_type;

        if ((req_volt_level <= pwr_data->pwr_specific_info[peripheral_index].pwr_vset[range].RangeMax) && 
            (req_volt_level >= pwr_data->pwr_specific_info[peripheral_index].pwr_vset[range].RangeMin))
        {
            vmin = pwr_data->pwr_specific_info[peripheral_index].pwr_vset[range].RangeMin;
            vStep = pwr_data->pwr_specific_info[peripheral_index].pwr_vset[range].VStep;
        }

        if (vStep > 0)
        {
            // calculate VSET
            vset = ((req_volt_level - vmin)/vStep);

            if ((1 == range) && (PM_HW_MODULE_ULT_BUCK == periph_type))
            {
                vset |= 0x60;
            }

            /* check if rounding off vset is required - if the voltage request
               cannot be met with the vstep , then it ends up being set to one
               vstep lower. So move it to next higher vstep boundary */
             if( ((vset*vStep) + vmin)  <  req_volt_level )
             {
                // increment the voltage by a step count if the voltage is less than the expected 
                vset++; 
                *ceiling_uv =  (vset*vStep) + vmin; 
             }
             *calculated_vset = vset;
        }
        else
        {
            err_flag = PM_ERR_FLAG__VLEVEL_OUT_OF_RANGE;
        }
    }

    if (PM_ERR_FLAG__SUCCESS != err_flag)
    {
        PM_LOG_MSG_ERROR(PMIC_DRV_PWR_VOLT_LVL_ERROR, comm_ptr->pmic_index, periph_type, peripheral_index, err_flag);
    }

    return err_flag;
}

pm_err_flag_type pm_pwr_volt_get_vstep(pm_pwr_data_type *pwr_data, pm_comm_info_type *comm_ptr, uint8 peripheral_index, uint8 *vstep_ptr)
{
    pm_err_flag_type                 err_flag = PM_ERR_FLAG__SUCCESS;
    pm_register_address_type         reg = 0;
    uint8                            periph_type = 0;

    if (peripheral_index >= (pwr_data->num_of_peripherals) || 
            pwr_data->pwr_specific_info[peripheral_index].periph_type == 0)
    {
        err_flag = PM_ERR_FLAG__INVALID_RESOURCE_ACCESS_ATTEMPTED;
    }
    else if (vstep_ptr == NULL)
    {
        err_flag = PM_ERR_FLAG__INVALID_POINTER;
    }
    else if (pwr_data->pwr_specific_info[peripheral_index].is_periph_stepper == FALSE)
    {
        err_flag = PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
    }
    else
    {
        periph_type = pwr_data->pwr_specific_info[peripheral_index].periph_type;
        reg =  (pm_register_address_type)(pwr_data->pwr_specific_info[peripheral_index].periph_base_address + pwr_data->pwr_reg_table->VOLTAGE_STEP_CTL);
        
        err_flag = pm_comm_read_byte(comm_ptr->slave_id, reg, vstep_ptr, 0);
    }

    if (PM_ERR_FLAG__SUCCESS != err_flag)
    {
        PM_LOG_MSG_ERROR(PMIC_DRV_PWR_VOLT_LVL_ERROR, comm_ptr->pmic_index, periph_type, peripheral_index, err_flag);
    }

    return err_flag;
}

pm_err_flag_type pm_pwr_irq_enable_alg(pm_pwr_data_type *pwr_data, pm_comm_info_type *comm_ptr, uint8 peripheral_index, pm_pwr_irq_type irq, boolean enable)
{
    pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;
    uint8            periph_type = 0;

    if ((peripheral_index >= pwr_data->num_of_peripherals) || (pwr_data->pwr_specific_info[peripheral_index].periph_type == 0))
    {
        err_flag = PM_ERR_FLAG__INVALID_RESOURCE_ACCESS_ATTEMPTED;
    }
    else if (irq >= PM_PWR_IRQ_INVALID)
    {
        err_flag = PM_ERR_FLAG__MACRO_NOT_RECOGNIZED;
    }
    else if (pwr_data->pwr_specific_info[peripheral_index].is_periph_unified_reg == FALSE)
    {
        err_flag = PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
    }
    else
    {
        pm_register_address_type reg = 0;
        uint8 irq_mask = 0;

        periph_type = pwr_data->pwr_specific_info[peripheral_index].periph_type;

        switch (irq)
        {
        case PM_PWR_IRQ_VREG_FAULT:
          irq_mask = 0x01;
          break;
        case PM_PWR_IRQ_VREG_READY:
          irq_mask = 0x02;
          break;
        default:
          // This check is already done so exec cannot reach here
          err_flag = PM_ERR_FLAG__MACRO_NOT_RECOGNIZED;
          break;
        }
         
        if (enable == TRUE)
        {
            reg = (pm_register_address_type)(pwr_data->pwr_specific_info[peripheral_index].periph_base_address + pwr_data->pwr_reg_table->INT_EN_SET);
        }
        else
        {
            reg = (pm_register_address_type)(pwr_data->pwr_specific_info[peripheral_index].periph_base_address + pwr_data->pwr_reg_table->INT_EN_CLR);
        }

        if (PM_ERR_FLAG__SUCCESS == err_flag)
        {
            err_flag = pm_comm_write_byte(comm_ptr->slave_id, reg, irq_mask, 0);
        }
    }

    if (PM_ERR_FLAG__SUCCESS != err_flag)
    {
        PM_LOG_MSG_ERROR(PMIC_DRV_PWR_IRQ_ERROR, comm_ptr->pmic_index, periph_type, peripheral_index, err_flag);
    }

    return err_flag;
}

pm_err_flag_type pm_pwr_irq_clear_alg(pm_pwr_data_type *pwr_data, pm_comm_info_type *comm_ptr, uint8 peripheral_index, pm_pwr_irq_type irq)
{
    pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;
    uint8            periph_type = 0;

    if ((peripheral_index >= pwr_data->num_of_peripherals) || (pwr_data->pwr_specific_info[peripheral_index].periph_type == 0))
    {
        err_flag = PM_ERR_FLAG__INVALID_RESOURCE_ACCESS_ATTEMPTED;
    }
    else if (irq >= PM_PWR_IRQ_INVALID)
    {
        err_flag = PM_ERR_FLAG__MACRO_NOT_RECOGNIZED;
    }
    else if (pwr_data->pwr_specific_info[peripheral_index].is_periph_unified_reg == FALSE)
    {
        err_flag = PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
    }
    else
    {
        pm_register_address_type reg = 0;
        uint8 irq_mask = 0;

        periph_type = pwr_data->pwr_specific_info[peripheral_index].periph_type;

        switch (irq)
        {
        case PM_PWR_IRQ_VREG_FAULT:
          irq_mask = 0x01;
          break;
        case PM_PWR_IRQ_VREG_READY:
          irq_mask = 0x02;
          break;
        default:
          // This check is already done so exec cannot reach here
          err_flag = PM_ERR_FLAG__MACRO_NOT_RECOGNIZED;
          break;
        }

        reg = (pm_register_address_type)(pwr_data->pwr_specific_info[peripheral_index].periph_base_address + pwr_data->pwr_reg_table->INT_LATCHED_CLR);

        if (PM_ERR_FLAG__SUCCESS == err_flag)
        {
            err_flag = pm_comm_write_byte(comm_ptr->slave_id, reg, irq_mask, 0);
        }
    }

    if (PM_ERR_FLAG__SUCCESS != err_flag)
    {
        PM_LOG_MSG_ERROR(PMIC_DRV_PWR_IRQ_ERROR, comm_ptr->pmic_index, periph_type, peripheral_index, err_flag);
    }

    return err_flag;
}

pm_err_flag_type pm_pwr_irq_set_trigger_alg(pm_pwr_data_type *pwr_data, pm_comm_info_type *comm_ptr, uint8 peripheral_index, pm_pwr_irq_type irq, pm_irq_trigger_type trigger)
{
    pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;
    uint8            periph_type = 0;

    if ((peripheral_index >= pwr_data->num_of_peripherals) || (pwr_data->pwr_specific_info[peripheral_index].periph_type == 0))
    {
        err_flag = PM_ERR_FLAG__INVALID_RESOURCE_ACCESS_ATTEMPTED;
    }
    else if ((irq >= PM_PWR_IRQ_INVALID) || (trigger >= PM_IRQ_TRIGGER_INVALID))
    {
        err_flag = PM_ERR_FLAG__MACRO_NOT_RECOGNIZED;
    }
    else if (pwr_data->pwr_specific_info[peripheral_index].is_periph_unified_reg == FALSE)
    {
        err_flag = PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
    }
    else
    {
        pm_register_address_type INT_SET_TYPE = (pm_register_address_type)(pwr_data->pwr_specific_info[peripheral_index].periph_base_address + pwr_data->pwr_reg_table->INT_SET_TYPE);
        pm_register_address_type INT_POLARITY_HIGH = (pm_register_address_type)(pwr_data->pwr_specific_info[peripheral_index].periph_base_address + pwr_data->pwr_reg_table->INT_POLARITY_HIGH);
        pm_register_address_type INT_POLARITY_LOW = (pm_register_address_type)(pwr_data->pwr_specific_info[peripheral_index].periph_base_address + pwr_data->pwr_reg_table->INT_POLARITY_LOW);
        uint8 irq_mask = 0;
        uint8 set_type = 0;
        uint8 polarity_high = 0;
        uint8 polarity_low = 0;

        periph_type = pwr_data->pwr_specific_info[peripheral_index].periph_type;

        switch (irq)
        {
        case PM_PWR_IRQ_VREG_FAULT:
          irq_mask = 0x01;
          break;
        case PM_PWR_IRQ_VREG_READY:
          irq_mask = 0x02;
          break;
        default:
          // This check is already done so exec cannot reach here
          err_flag = PM_ERR_FLAG__MACRO_NOT_RECOGNIZED;
          break;
        }

        switch (trigger)
        {
        case PM_IRQ_TRIGGER_ACTIVE_LOW:
          set_type = 0x00;
          polarity_high = 0x00;
          polarity_low = 0xFF;
          break;
        case PM_IRQ_TRIGGER_ACTIVE_HIGH:
          set_type = 0x00;
          polarity_high = 0xFF;
          polarity_low = 0x00;
          break;
        case PM_IRQ_TRIGGER_RISING_EDGE:
          set_type = 0xFF;
          polarity_high = 0xFF;
          polarity_low = 0x00;
          break;
        case PM_IRQ_TRIGGER_FALLING_EDGE:
          set_type = 0xFF;
          polarity_high = 0x00;
          polarity_low = 0xFF;
          break;
        case PM_IRQ_TRIGGER_DUAL_EDGE:
          set_type = 0xFF;
          polarity_high = 0xFF;
          polarity_low = 0xFF;
          break;
        default:
          // This check is already done so exec cannot reach here
          err_flag = PM_ERR_FLAG__MACRO_NOT_RECOGNIZED;
          break;
        }

        if (PM_ERR_FLAG__SUCCESS == err_flag)
        {
            err_flag = pm_comm_write_byte_mask(comm_ptr->slave_id, INT_SET_TYPE, irq_mask, set_type, 0);
            err_flag |= pm_comm_write_byte_mask(comm_ptr->slave_id, INT_POLARITY_HIGH, irq_mask, polarity_high, 0);
            err_flag |= pm_comm_write_byte_mask(comm_ptr->slave_id, INT_POLARITY_LOW, irq_mask, polarity_low, 0);
        }
    }

    if (PM_ERR_FLAG__SUCCESS != err_flag)
    {
        PM_LOG_MSG_ERROR(PMIC_DRV_PWR_IRQ_ERROR, comm_ptr->pmic_index, periph_type, peripheral_index, err_flag);
    }

    return err_flag;
}

pm_err_flag_type pm_pwr_irq_register_isr_alg(pm_pwr_data_type *pwr_data, pm_comm_info_type *comm_ptr, uint8 peripheral_index, 
                                             pm_pwr_irq_type irq, void *isr_ptr, uint32 isr_ctx)
{
    pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;
    uint8            periph_type = 0;

    if (peripheral_index >= (pwr_data->num_of_peripherals) || 
        pwr_data->pwr_specific_info[peripheral_index].periph_type == 0)
    {
        err_flag = PM_ERR_FLAG__INVALID_RESOURCE_ACCESS_ATTEMPTED;
    }
    else if (irq >= PM_PWR_IRQ_INVALID)
    {
        err_flag = PM_ERR_FLAG__MACRO_NOT_RECOGNIZED;
    }
    else if (isr_ptr == NULL)
    {
        err_flag = PM_ERR_FLAG__INVALID_POINTER;
    }
    else if (pwr_data->pwr_specific_info[peripheral_index].is_periph_unified_reg == FALSE)
    {
        err_flag = PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
    }
    else
    {
        pm_register_address_type base_addr = pwr_data->pwr_specific_info[peripheral_index].periph_base_address;
        uint8 irq_mask = 0;

        periph_type = pwr_data->pwr_specific_info[peripheral_index].periph_type;

        switch (irq)
        {
        case PM_PWR_IRQ_VREG_FAULT:
          irq_mask = 0x01;
          break;
        case PM_PWR_IRQ_VREG_READY:
          irq_mask = 0x02;
          break;
        default:
          // This check is already done so exec cannot reach here
          err_flag = PM_ERR_FLAG__MACRO_NOT_RECOGNIZED;
          break;
        }

        if (PM_ERR_FLAG__SUCCESS == err_flag)
        {
            err_flag = pm_comm_register_isr(comm_ptr->slave_id, base_addr, irq_mask, isr_ptr, isr_ctx);
        }
    }

    if (PM_ERR_FLAG__SUCCESS != err_flag)
    {
        PM_LOG_MSG_ERROR(PMIC_DRV_PWR_IRQ_ERROR, comm_ptr->pmic_index, periph_type, peripheral_index, err_flag);
    }

    return err_flag;
}

pm_err_flag_type pm_pwr_ocp_latched_status_clear_alg(pm_pwr_data_type *pwr_data, pm_comm_info_type *comm_ptr, uint8 peripheral_index, boolean *ocp_occured)
{
    pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;
    uint8 periph_type = 0;
    pm_register_address_type ocp_status_reg = 0x0;
    pm_register_address_type ocp_reg = 0x0;
    pm_register_address_type sec_reg = 0x0;
    pm_register_data_type status_data = 0;
    pm_register_data_type ocp_clear_data = 0;
    pm_register_data_type status_mask = 0;
    pm_register_data_type ocp_clear_mask = 0;
    static int ocp_status_counter = 0;
    
    pm_debug_info_type *pmic_debug = pm_get_debug_info();
    CORE_VERIFY_PTR(pmic_debug);
    pmic_debug->ocp_rail_status = pm_ocp_rail_status;
    pmic_debug->pm_ocp_rail_count = &pm_ocp_rail_count;

    if ((peripheral_index >= pwr_data->num_of_peripherals) || (pwr_data->pwr_specific_info[peripheral_index].periph_type == 0))
    {
        err_flag = PM_ERR_FLAG__INVALID_RESOURCE_ACCESS_ATTEMPTED;
    }
    else if(NULL == ocp_occured)
    {
        err_flag = PM_ERR_FLAG__INVALID_POINTER;
    }
    else
    {
        periph_type = pwr_data->pwr_specific_info[peripheral_index].periph_type;

        if (pwr_data->pwr_specific_info[peripheral_index].is_periph_unified_reg == TRUE)
        {
            ocp_status_reg = (pm_register_address_type)(pwr_data->pwr_specific_info[peripheral_index].periph_base_address + pwr_data->pwr_reg_table->STATUS);
            status_mask = 0x1 << 5;
            ocp_reg = (pm_register_address_type)(pwr_data->pwr_specific_info[peripheral_index].periph_base_address + pwr_data->pwr_reg_table->OCP);
            ocp_clear_mask = 0x1 << 1;
            ocp_clear_data = 0x1 << 1;
        }
        else if (periph_type == PM_HW_MODULE_ULT_LDO)
        {
            /*Only PMOS LDO have OCP but for other LDO either these registers are missing or the bit field is missing 
              and so status will never reported to be high  */
            ocp_status_reg = (pm_register_address_type)(pwr_data->pwr_specific_info[peripheral_index].periph_base_address + STATUS2_OFFSET);
            status_mask = 0x1 << 6;
            ocp_reg = (pm_register_address_type)(pwr_data->pwr_specific_info[peripheral_index].periph_base_address + OCP_CTL2_OFFSET);
            ocp_clear_mask = 0x1 << 6;
            ocp_clear_data = 0x1 << 6;
        }
        else
        {
            return PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
        }

        err_flag = pm_comm_read_byte(comm_ptr->slave_id, ocp_status_reg, &status_data, 0);

        if (err_flag != PM_ERR_FLAG__SUCCESS)
        {
            err_flag = pm_comm_read_byte(comm_ptr->slave_id, ocp_status_reg, &status_data, 0);
        }

        *ocp_occured = (status_data & status_mask) ? TRUE : FALSE ;

        if (*ocp_occured == TRUE)
        {
            if (ocp_status_counter >= PM_OCP_RAIL_STATUS_SIZE)
            {
                ocp_status_counter = 0;
            }
            pm_ocp_rail_status[ocp_status_counter].timestamp = time_service_now();
            pm_ocp_rail_status[ocp_status_counter].periph_type = pwr_data->pwr_specific_info[peripheral_index].periph_type;
            pm_ocp_rail_status[ocp_status_counter].periph_index = peripheral_index;
            pm_ocp_rail_count +=1; 
            ocp_status_counter += 1;
            sec_reg = (pm_register_address_type)(pwr_data->pwr_specific_info[peripheral_index].periph_base_address + pwr_data->pwr_reg_table->SEC_ACCESS);
            /*write 1 and then 0 to clear OCP*/
            err_flag |= pm_comm_write_byte(comm_ptr->slave_id, sec_reg, 0xA5, 0);
            err_flag |= pm_comm_write_byte_mask(comm_ptr->slave_id, ocp_reg, ocp_clear_mask, ocp_clear_data, 0);
            err_flag |= pm_comm_write_byte(comm_ptr->slave_id, sec_reg, 0xA5, 0);
            err_flag |= pm_comm_write_byte_mask(comm_ptr->slave_id, ocp_reg, ocp_clear_mask, 0, 0);
        }
    }

    return err_flag;
}


