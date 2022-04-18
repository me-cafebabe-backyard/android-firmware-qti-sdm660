/*! \file
*  
*  \brief  coinchg_app.cpp ----File contains the implementation of the public APIs for MPP resource type.
*  \details Implementation file for MPP resourece type.
*  Each of the APIs checks for access and then if necessary directs
*  the call to Driver implementation or to RPC function for the master processor.
*  
*    PMIC code generation Version: 2.0.0.19
*    This file contains code for Target specific settings and modes.
*  
*  &copy; Copyright 2012 - 2015 QUALCOMM Technologies, Inc, All Rights Reserved
*/

/*===========================================================================

EDIT HISTORY FOR MODULE

This document is created by a code generator, therefore this section will
not contain comments describing changes made to the module.


when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
05/12/15   al      Updating for dbus/dtest
12/08/14   al      Updated for inverted dbus logic  
08/20/14   al      Updating comm lib 
08/29/14   al      KW fixes
05/20/14   al      Architecture update 
02/27/13   al      Adding IRQ related APIs  
01/24/13   al      Added get real time interrupt status
04/10/12   hs      Changed the type for internalResourceIndex from int to uint8.
03/02/12   hs	   Removed deprecated APIs.

===========================================================================*/

/*===========================================================================

INCLUDE FILES 

===========================================================================*/
#include "pm_mpp.h"
#include "pm_mpp_driver.h"

/*===========================================================================

                        FUNCTION PROTOTYPES

===========================================================================*/
static pm_err_flag_type pm_mpp_configure_type(uint32 pmic_chip, uint8  perph_index, pm_drv_mpp_config_type type);
static pm_err_flag_type pm_mpp_config_dvin(uint32 pmic_chip, uint8  perph_index, pm_mpp_dlogic_lvl_type  level);
static pm_err_flag_type pm_mpp_is_dbus_valid(uint32 pmic_chip, uint8  perph_index, pm_mpp_dlogic_in_dbus_type  dbus);
static pm_err_flag_type pm_mpp_abus_pulldown(uint32 pmic_chip, uint8  perph_index, uint8  which_ch, pm_drv_mpp_config_type  mpp_type);
/*===========================================================================

                        FUNCTION DEFINITIONS

===========================================================================*/
pm_err_flag_type pm_mpp_config_digital_input(uint32 pmic_chip, pm_mpp_perph_index mpp, pm_mpp_dlogic_lvl_type  level, pm_mpp_dlogic_in_dbus_type  dbus)
{
    /* Use this variable to keep track if the operation was successful or not */
    pm_err_flag_type         err_flag = PM_ERR_FLAG__SUCCESS;
    pm_register_address_type dig_in_ctl;
    pm_mpp_data_type *mpp_ptr = pm_mpp_get_data(pmic_chip);
    pm_register_address_type perph_index = (pm_register_address_type)mpp;


    if (mpp_ptr == NULL)
    {
        return PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
    }
    if ((uint8)perph_index >= mpp_ptr->num_of_peripherals)
    {
        return PM_ERR_FLAG__INVALID_MPP_INDEXED;
    }
    if (level >= PM_MPP__DLOGIC__LVL_INVALID)
    {
        return PM_ERR_FLAG__PAR1_OUT_OF_RANGE;
    }
    if (dbus >= PM_MPP__DLOGIC_IN__DBUS_INVALID)
    {
        return PM_ERR_FLAG__PAR2_OUT_OF_RANGE;
    }

    dig_in_ctl = mpp_ptr->mpp_reg_table->base_address + (mpp_ptr->mpp_reg_table->peripheral_offset * perph_index) + mpp_ptr->mpp_reg_table->dig_in_ctl;

    /* Make sure that the user made a valid dbus selection. */
    err_flag = pm_mpp_is_dbus_valid(pmic_chip, mpp, dbus );
    if (err_flag != PM_ERR_FLAG__SUCCESS) return err_flag;

    /* Check whether this config will enable or disable ABUS pull down */
    err_flag = pm_mpp_abus_pulldown(pmic_chip, (uint8)perph_index, (uint8)level, PM_MPP_DIG_IN);
    if (err_flag != PM_ERR_FLAG__SUCCESS) return err_flag;

    // Set MPP_TYPE to DIGITAL INPUT
    err_flag = pm_mpp_configure_type(pmic_chip, (uint8)perph_index, PM_MPP_DIG_IN);
    if (err_flag != PM_ERR_FLAG__SUCCESS) return err_flag;

    // Configure the VOLTAGE_SEL
    err_flag = pm_mpp_config_dvin(pmic_chip, (uint8)perph_index, level);
    if (err_flag != PM_ERR_FLAG__SUCCESS) return err_flag;

    // Enable Digital Input buffer
    //DTEST4	Route to DTEST4
    //DTEST3	Route to DTEST3
    //DTEST2	Route to DTEST2
    //DTEST1	Route to DTEST1
    // DTEST lines can be used in parallel
    err_flag = pm_comm_write_byte_mask(mpp_ptr->comm_ptr->slave_id, dig_in_ctl, (pm_register_mask_type)0x0F, (pm_register_data_type)(1 << dbus), 0);
    if (err_flag != PM_ERR_FLAG__SUCCESS) return err_flag;

    // Enable the MPP
    err_flag = pm_mpp_enable(pmic_chip, mpp, TRUE);
    if (err_flag != PM_ERR_FLAG__SUCCESS) return err_flag;

    return err_flag;
}


pm_err_flag_type pm_mpp_config_digital_output(uint32 pmic_chip, pm_mpp_perph_index mpp, pm_mpp_dlogic_lvl_type  level, pm_mpp_dlogic_out_ctrl_type  output_ctrl)
{
    /* Use this variable to keep track if the operation was successful or not */
    pm_err_flag_type         err_flag = PM_ERR_FLAG__SUCCESS;
    pm_register_address_type mode_ctl;
    pm_mpp_data_type *mpp_ptr = pm_mpp_get_data(pmic_chip);
    pm_register_address_type perph_index = (pm_register_address_type)mpp;

    if (mpp_ptr == NULL)
    {
        return PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
    }
    if ((uint8)perph_index >= mpp_ptr->num_of_peripherals)
    {
        return PM_ERR_FLAG__INVALID_MPP_INDEXED;
    }
    if (level >= PM_MPP__DLOGIC__LVL_INVALID)
    {
        /* Parm 1 is out of range */
        return PM_ERR_FLAG__PAR1_OUT_OF_RANGE;
    }
    if (output_ctrl >= PM_MPP__DLOGIC_OUT__CTRL_INVALID)
    {
        /* Parm 2 is out of range */
        return PM_ERR_FLAG__PAR2_OUT_OF_RANGE;
    }

    mode_ctl = mpp_ptr->mpp_reg_table->base_address + (mpp_ptr->mpp_reg_table->peripheral_offset * perph_index) + mpp_ptr->mpp_reg_table->mode_ctl;

    /* Check whether this config will enable or disable ABUS pulldown */
    err_flag = pm_mpp_abus_pulldown(pmic_chip, (uint8)perph_index,(uint8)level, PM_MPP_DIG_OUT);
    if (err_flag != PM_ERR_FLAG__SUCCESS) return err_flag;

    // Set MPP_TYPE to DIGITAL OUTPUT
    err_flag = pm_mpp_configure_type(pmic_chip, (uint8)perph_index, PM_MPP_DIG_OUT);
    if (err_flag != PM_ERR_FLAG__SUCCESS) return err_flag;
    
    // Configure the VOLTAGE_SEL
    err_flag = pm_mpp_config_dvin(pmic_chip, (uint8)perph_index, level);
    if (err_flag != PM_ERR_FLAG__SUCCESS) return err_flag;

    // Configure output source
    //Source select:
    //When configured as a digital output Source select:
    //0000 = 0
    //0001 = 1
    //0010 = paired MPP
    //0011 = inverted paired MPP
    err_flag = pm_comm_write_byte_mask(mpp_ptr->comm_ptr->slave_id, mode_ctl, 0x03, (pm_register_data_type)output_ctrl, 0);
    if (err_flag != PM_ERR_FLAG__SUCCESS) return err_flag;

    // Enable the MPP
    err_flag = pm_mpp_enable(pmic_chip, mpp, TRUE);
    if (err_flag != PM_ERR_FLAG__SUCCESS) return err_flag;

    return err_flag;
}

pm_err_flag_type pm_mpp_config_digital_inout(uint32 pmic_chip, pm_mpp_perph_index mpp, pm_mpp_dlogic_lvl_type  level, pm_mpp_dlogic_inout_pup_type  pull_up)
{
    /* Use this variable to keep track if the operation was successful or not */
    pm_err_flag_type         err_flag = PM_ERR_FLAG__SUCCESS;
    pm_register_address_type dig_pull_ctl;
    pm_mpp_data_type *mpp_ptr = pm_mpp_get_data(pmic_chip);
    pm_register_address_type perph_index = (pm_register_address_type)mpp;

    if (mpp_ptr == NULL)
    {
        return PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
    }
    if ((uint8)perph_index >= mpp_ptr->num_of_peripherals)
    {
        return PM_ERR_FLAG__INVALID_MPP_INDEXED;
    }
    if (level >= PM_MPP__DLOGIC__LVL_INVALID)
    {
        /* Parm 1 is out of range */
        return PM_ERR_FLAG__PAR1_OUT_OF_RANGE;
    }
    if (pull_up >= PM_MPP__DLOGIC_INOUT__PUP_INVALID)
    {
        /* Parm 2 is out of range */
        return PM_ERR_FLAG__PAR2_OUT_OF_RANGE;
    }

    dig_pull_ctl = mpp_ptr->mpp_reg_table->base_address + (mpp_ptr->mpp_reg_table->peripheral_offset * perph_index) + mpp_ptr->mpp_reg_table->dig_pull_ctl;

    /* Check whether this config will enable or disable ABUS pulldown */
    err_flag = pm_mpp_abus_pulldown(pmic_chip, (uint8)perph_index, (uint8)level, PM_MPP_BI_DIR);
    if (err_flag != PM_ERR_FLAG__SUCCESS) return err_flag;

    // Set MPP_TYPE to PM_MPP_BI_DIR
    err_flag = pm_mpp_configure_type(pmic_chip, (uint8)perph_index, PM_MPP_BI_DIR);
    if (err_flag != PM_ERR_FLAG__SUCCESS) return err_flag;

    // Configure the VOLTAGE_SEL
    err_flag = pm_mpp_config_dvin(pmic_chip, (uint8)perph_index, level);
    if (err_flag != PM_ERR_FLAG__SUCCESS) return err_flag;

    // Config the Pullup Resistor Control
    err_flag = pm_comm_write_byte_mask(mpp_ptr->comm_ptr->slave_id, dig_pull_ctl, 0x07, (pm_register_data_type)pull_up, 0);
    if (err_flag != PM_ERR_FLAG__SUCCESS) return err_flag;

    // Enable the MPP
    err_flag = pm_mpp_enable(pmic_chip, mpp, TRUE);
    if (err_flag != PM_ERR_FLAG__SUCCESS) return err_flag;

    return err_flag;
}

pm_err_flag_type pm_mpp_config_analog_input(uint32 pmic_chip, pm_mpp_perph_index mpp, pm_mpp_ain_ch_type  ch_select)
{
    /* Use this variable to keep track if the operation was successful or not */
    pm_err_flag_type       err_flag = PM_ERR_FLAG__SUCCESS;
    pm_register_address_type ana_in_ctl;
    pm_register_address_type mode_ctl;
    pm_mpp_data_type *mpp_ptr = pm_mpp_get_data(pmic_chip);
    pm_register_address_type perph_index = (pm_register_address_type)mpp;

    if (mpp_ptr == NULL)
    {
        return PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
    }
    if ((uint8)perph_index >= mpp_ptr->num_of_peripherals)
    {
        return PM_ERR_FLAG__INVALID_MPP_INDEXED;
    }
    if (ch_select >= PM_MPP__AIN__CH_INVALID)
    {
        /* Parm 1 is out of range */
        return PM_ERR_FLAG__PAR1_OUT_OF_RANGE;
    }

    ana_in_ctl = mpp_ptr->mpp_reg_table->base_address + (mpp_ptr->mpp_reg_table->peripheral_offset * perph_index) + mpp_ptr->mpp_reg_table->ana_in_ctl;
    mode_ctl   = mpp_ptr->mpp_reg_table->base_address + (mpp_ptr->mpp_reg_table->peripheral_offset * perph_index) + mpp_ptr->mpp_reg_table->mode_ctl;

    /* Check whether this config will enable or disable ABUS pulldown */
    err_flag = pm_mpp_abus_pulldown(pmic_chip, (uint8)perph_index,(uint8)ch_select, PM_MPP_ANALOG_IN);
    if (err_flag != PM_ERR_FLAG__SUCCESS) return err_flag;

    // Set MPP_TYPE to PM_MPP_ANALOG_IN
    err_flag = pm_mpp_configure_type(pmic_chip, (uint8)perph_index, PM_MPP_ANALOG_IN);
    if (err_flag != PM_ERR_FLAG__SUCCESS) return err_flag;

    // Configure the channel control
    //AMUX Channel Control
    //0: Route to AMUX5
    //1: Route to AMUX6
    //2: Route to AMUX7
    //3: Route to AMUX8
    //4: Route to ATEST1 (aka ABUS1) (internal use only)
    //5: Route to ATEST2 (aka ABUS2) (internal use only)
    //6: Route to ATEST3 (aka ABUS3) (internal use only)
    //7: Route to ATEST4 (aka ABUS4) (internal use only)

    err_flag = pm_comm_write_byte_mask(mpp_ptr->comm_ptr->slave_id, ana_in_ctl, 0x07, (pm_register_data_type)ch_select, 0);
    if (err_flag != PM_ERR_FLAG__SUCCESS) return err_flag;

    // Note: When the MPP is configured as AIN, AOUT, or Current Sink, the LSB in mode_ctl needs to be set to keep the MPP enabled; otherwise, the MPP
    // will alwways be disabled.
    err_flag = pm_comm_write_byte_mask(mpp_ptr->comm_ptr->slave_id, mode_ctl, 0x01, 0x01, 0);

    // Enable the MPP
    err_flag = pm_mpp_enable(pmic_chip, mpp, TRUE);
    if (err_flag != PM_ERR_FLAG__SUCCESS) return err_flag;

    return err_flag;
}


pm_err_flag_type pm_mpp_config_analog_output(uint32 pmic_chip, pm_mpp_perph_index mpp, pm_mpp_aout_level_type  level, pm_mpp_aout_switch_type  OnOff)
{
    /* Use this variable to keep track if the operation was successful or not */
    pm_err_flag_type       err_flag = PM_ERR_FLAG__SUCCESS;
    pm_register_address_type mode_ctl = 0;
    pm_register_address_type ana_out_ctl;
    pm_mpp_data_type *mpp_ptr = pm_mpp_get_data(pmic_chip);
    pm_register_address_type perph_index = (pm_register_address_type)mpp;

    if (mpp_ptr == NULL)
    {
        return PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
    }
    if ((uint8)perph_index >= mpp_ptr->num_of_peripherals)
    {
        return PM_ERR_FLAG__INVALID_MPP_INDEXED;
    }
    if (level >= PM_MPP__AOUT__LEVEL_INVALID)
    {
        /* Parm 1 is out of range */
        return PM_ERR_FLAG__PAR1_OUT_OF_RANGE;
    }
    if (OnOff >= PM_MPP__AOUT__SWITCH_INVALID)
    {
        /* Parm 2 is out of range */
        return PM_ERR_FLAG__PAR2_OUT_OF_RANGE;
    }

    mode_ctl    = mpp_ptr->mpp_reg_table->base_address + (mpp_ptr->mpp_reg_table->peripheral_offset * perph_index) + mpp_ptr->mpp_reg_table->mode_ctl;
    ana_out_ctl = mpp_ptr->mpp_reg_table->base_address + (mpp_ptr->mpp_reg_table->peripheral_offset * perph_index) + mpp_ptr->mpp_reg_table->ana_out_ctl;

    /* Check whether this config will enable or disable ABUS pulldown */
    err_flag = pm_mpp_abus_pulldown(pmic_chip, (uint8)perph_index,(uint8)level, PM_MPP_ANALOG_OUT);
    if (err_flag != PM_ERR_FLAG__SUCCESS) return err_flag;

    // Set MPP_TYPE to PM_MPP_ANALOG_OUT
    err_flag = pm_mpp_configure_type(pmic_chip, (uint8)perph_index, PM_MPP_ANALOG_OUT);
    if (err_flag != PM_ERR_FLAG__SUCCESS) return err_flag;

    // Config Analog Output Control
    //Analog Output Control
    //0: Output = vref_1V25 = REF_BYP pin, typically 1.25 Volts
    //1: Output = vref_V625 = 0.625 Volts (internal use only)
    //2: Output = vref_V3125 = 0.3125 Volts (internal use only)
    //3: Output = paired MPP input (internal use only)
    //4: Output = buffered ATEST1 (aka ABUS1) (internal use only)
    //5: Output = buffered ATEST2 (aka ABUS2) (internal use only)
    //6: Output = buffered ATEST3 (aka ABUS3) (internal use only)
    //7: Output = buffered ATEST4 (aka ABUS4) (internal use only)
    err_flag = pm_comm_write_byte_mask(mpp_ptr->comm_ptr->slave_id, ana_out_ctl, 0x07, (pm_register_data_type)level, 0);
    if (err_flag != PM_ERR_FLAG__SUCCESS) return err_flag;

    // Config analog output
    //Enable control when configured as Bidirectional, AIN, AOUT, or Current Sink.  MPP is enable whenever the selected condition is true.
    //0000 = 0 (mpp is always disabled)
    //0001 = 1 (mpp is always Enabled)
    //0010 = paired MPP
    //0011 = inverted paired MPP
    err_flag = pm_comm_write_byte_mask(mpp_ptr->comm_ptr->slave_id, mode_ctl, 0x03, (pm_register_data_type)OnOff, 0);
    if (err_flag != PM_ERR_FLAG__SUCCESS) return err_flag;

    // Enable the MPP
    err_flag = pm_mpp_enable(pmic_chip, mpp, TRUE);

    return err_flag;
}

pm_err_flag_type pm_mpp_config_i_sink(uint32 pmic_chip, pm_mpp_perph_index mpp, pm_mpp_i_sink_level_type  level, pm_mpp_i_sink_switch_type  OnOff)
{
    /* Use this variable to keep track if the operation was successful or not */
    pm_err_flag_type       err_flag = PM_ERR_FLAG__SUCCESS;
    pm_register_address_type sink_ctl;
    pm_register_address_type mode_ctl;
    pm_mpp_data_type *mpp_ptr = pm_mpp_get_data(pmic_chip);
    pm_register_address_type perph_index = (pm_register_address_type)mpp;

    if (mpp_ptr == NULL)
    {
        return PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
    }
    if ((uint8)perph_index >= mpp_ptr->num_of_peripherals)
    {
        return PM_ERR_FLAG__INVALID_MPP_INDEXED;
    }
    if (level >= PM_MPP__I_SINK__LEVEL_INVALID)
    {
        /* Parm 1 is out of range */
        return PM_ERR_FLAG__PAR1_OUT_OF_RANGE;
    }
    if (OnOff >= PM_MPP__I_SINK__SWITCH_INVALID)
    {
        /* Parm 2 is out of range */
        return PM_ERR_FLAG__PAR2_OUT_OF_RANGE;
    }

    sink_ctl = mpp_ptr->mpp_reg_table->base_address + (mpp_ptr->mpp_reg_table->peripheral_offset * (uint8)perph_index) + mpp_ptr->mpp_reg_table->sink_ctl;
    mode_ctl = mpp_ptr->mpp_reg_table->base_address + (mpp_ptr->mpp_reg_table->peripheral_offset * (uint8)perph_index) + mpp_ptr->mpp_reg_table->mode_ctl;

    /* Check whether this config will enable or disable ABUS pulldown */
    err_flag = pm_mpp_abus_pulldown(pmic_chip, (uint8)perph_index,(uint8)level, PM_MPP_I_SINK);
    if (err_flag != PM_ERR_FLAG__SUCCESS) return err_flag;

    // Set MPP_TYPE to PM_MPP_I_SINK
    err_flag = pm_mpp_configure_type(pmic_chip, (uint8)perph_index, PM_MPP_I_SINK);
    if (err_flag != PM_ERR_FLAG__SUCCESS) return err_flag;

    // Config Current Sink Output Control
    //Current Sink Output Control
    //0: Output = 5 mA
    //1: Output = 10 mA
    //2: Output = 15 mA
    //3: Output = 20 mA
    //4: Output = 25 mA
    //5: Output = 30 mA
    //6: Output = 35 mA
    //7: Output = 40 mA
    err_flag = pm_comm_write_byte_mask(mpp_ptr->comm_ptr->slave_id, sink_ctl, 0x07, (pm_register_data_type)level, 0);
    if (err_flag != PM_ERR_FLAG__SUCCESS) return err_flag;

    // Config I_SINK output
    //Enable control when configured as Bidirectional, AIN, AOUT, or Current Sink.  MPP is enable whenever the selected condition is true.
    //0000 = 0 (mpp is always disabled)
    //0001 = 1 (mpp is always Enabled)
    //0010 = paired MPP
    //0011 = inverted paired MPP
    err_flag = pm_comm_write_byte_mask(mpp_ptr->comm_ptr->slave_id, mode_ctl, 0x03, (pm_register_data_type)OnOff, 0);
    if (err_flag != PM_ERR_FLAG__SUCCESS) return err_flag;

    // Enable the MPP
    err_flag = pm_mpp_enable(pmic_chip, mpp, TRUE);

    return err_flag;
}


pm_err_flag_type pm_mpp_config_atest(uint32 pmic_chip, pm_mpp_perph_index mpp, pm_mpp_ch_atest_type  atest_select)
{
    /* Use this variable to keep track if the operation was successful or not */
    pm_err_flag_type    err_flag = PM_ERR_FLAG__SUCCESS;
    pm_register_address_type ana_in_ctl;
    pm_register_address_type mode_ctl;
    pm_mpp_data_type *mpp_ptr = pm_mpp_get_data(pmic_chip);
    pm_register_address_type perph_index = (pm_register_address_type)mpp;

    if (mpp_ptr == NULL)
    {
        return PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
    }
    if ((uint8)perph_index >= mpp_ptr->num_of_peripherals)
    {
        return PM_ERR_FLAG__INVALID_MPP_INDEXED;
    }
    if (atest_select >= PM_MPP__CH_ATEST_INVALID)
    {
        /* Parm 1 is out of range */
        return PM_ERR_FLAG__PAR1_OUT_OF_RANGE;
    }

    ana_in_ctl = mpp_ptr->mpp_reg_table->base_address + (mpp_ptr->mpp_reg_table->peripheral_offset * perph_index) + mpp_ptr->mpp_reg_table->ana_in_ctl;
    mode_ctl   = mpp_ptr->mpp_reg_table->base_address + (mpp_ptr->mpp_reg_table->peripheral_offset * perph_index) + mpp_ptr->mpp_reg_table->mode_ctl;

    // Set MPP_TYPE to PM_MPP_ANALOG_IN
    err_flag = pm_mpp_configure_type(pmic_chip, (uint8)perph_index, PM_MPP_ANALOG_IN);
    if (err_flag != PM_ERR_FLAG__SUCCESS) return err_flag;

    // Configure teh channel control
    //AMUX Channel Control
    //4: Route to ATEST1 (aka ABUS1) (internal use only)
    //5: Route to ATEST2 (aka ABUS2) (internal use only)
    //6: Route to ATEST3 (aka ABUS3) (internal use only)
    //7: Route to ATEST4 (aka ABUS4) (internal use only)
    err_flag = pm_comm_write_byte_mask(mpp_ptr->comm_ptr->slave_id, ana_in_ctl, 0x07, (pm_register_data_type)(atest_select + 4), 0);
    if (err_flag != PM_ERR_FLAG__SUCCESS) return err_flag;

    // Note: When the MPP is configured as AIN, AOUT, or Current Sink, the LSB in mode_ctl needs to be set to keep the MPP enabled; otherwise, the MPP
    // will alwways be disabled.
    err_flag = pm_comm_write_byte_mask(mpp_ptr->comm_ptr->slave_id, mode_ctl, 0x01, 0x01, 0);

    // Enable the MPP
    err_flag = pm_mpp_enable(pmic_chip, mpp, TRUE);
    if (err_flag != PM_ERR_FLAG__SUCCESS) return err_flag;

    return err_flag;
}


pm_err_flag_type pm_mpp_config_dtest_output(uint32 pmic_chip, pm_mpp_perph_index mpp, pm_mpp_dlogic_lvl_type  level, pm_mpp_dlogic_out_dbus_type  dbus)
{
    pm_err_flag_type    err_flag = PM_ERR_FLAG__SUCCESS;
    pm_register_data_type data;
    pm_mpp_data_type *mpp_ptr = pm_mpp_get_data(pmic_chip);
    pm_register_address_type perph_index = (pm_register_address_type)mpp;

    if (mpp_ptr == NULL)
    {
        return PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
    }
    if ((uint8)perph_index >= mpp_ptr->num_of_peripherals)
    {
        return PM_ERR_FLAG__INVALID_MPP_INDEXED;
    }

    pm_register_address_type mode_ctl = mpp_ptr->mpp_reg_table->base_address + (mpp_ptr->mpp_reg_table->peripheral_offset * perph_index) + mpp_ptr->mpp_reg_table->mode_ctl;

    switch (dbus)
    {
    case PM_MPP__DLOGIC_OUT__DISABLED            : data = 0;     break;
    case PM_MPP__DLOGIC_OUT__ENABLED             : data = 1;     break;
    case PM_MPP__DLOGIC_OUT__PAIRED_MPP          : data = 2;     break;
    case PM_MPP__DLOGIC_OUT__INVERTED_PAIRED_MPP : data = 3;     break;
    case PM_MPP__DLOGIC_OUT__DBUS1               : data =  8;    break;
    case PM_MPP__DLOGIC_OUT__DBUS1_INVERTED      : data =  9;    break;
    case PM_MPP__DLOGIC_OUT__DBUS2               : data =  10;   break;
    case PM_MPP__DLOGIC_OUT__DBUS2_INVERTED      : data =  11;   break;
    case PM_MPP__DLOGIC_OUT__DBUS3               : data =  12;   break;
    case PM_MPP__DLOGIC_OUT__DBUS3_INVERTED      : data =  13;   break;
    case PM_MPP__DLOGIC_OUT__DBUS4               : data =  14;   break;
    case PM_MPP__DLOGIC_OUT__DBUS4_INVERTED      : data =  15;   break;
    default:
        return PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
    }
    // Configure the VOLTAGE_SEL
    err_flag = pm_mpp_config_dvin(pmic_chip, (uint8)perph_index, level);
    if (err_flag != PM_ERR_FLAG__SUCCESS) return err_flag;

    err_flag = pm_comm_write_byte_mask(mpp_ptr->comm_ptr->slave_id, mode_ctl, 0x0F, data, 0);

    return err_flag;
}


pm_err_flag_type pm_mpp_set_list_mpp_with_shunt_cap(uint32 pmic_chip, pm_mpp_perph_index mpp)
{
    pm_mpp_data_type *mpp_ptr = pm_mpp_get_data(pmic_chip);

    pm_register_address_type perph_index = (pm_register_address_type)mpp;

    if (mpp_ptr == NULL)
    {
        return PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
    }
    if ((uint8)perph_index >= mpp_ptr->num_of_peripherals)
    {
        return PM_ERR_FLAG__INVALID_MPP_INDEXED;
    }

    (mpp_ptr)->m_mpp_with_shunt_cap_list_status |= (1L << (uint8)perph_index);

    return PM_ERR_FLAG__SUCCESS;
}



pm_err_flag_type pm_mpp_get_mpp_with_shunt_cap_list_status_for_device(uint32 pmic_chip, pm_mpp_perph_index mpp, uint32  *shuntList)
{
    pm_mpp_data_type *mpp_ptr = pm_mpp_get_data(pmic_chip);
    pm_register_address_type perph_index = (pm_register_address_type)mpp;

    if (mpp_ptr == NULL)
    {
        return PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
    }
    if ((uint8)perph_index >= mpp_ptr->num_of_peripherals)
    {
        return PM_ERR_FLAG__INVALID_MPP_INDEXED;
    }
    if (NULL == shuntList)
    {
        /* Param is out of range */
        return PM_ERR_FLAG__INVALID_POINTER;
    }

    *shuntList = (mpp_ptr)->m_mpp_with_shunt_cap_list_status;
    return PM_ERR_FLAG__SUCCESS;
}



pm_err_flag_type pm_mpp_status_get(uint32 pmic_chip, pm_mpp_perph_index mpp, pm_mpp_status_type  *mpp_status)
{
    pm_register_data_type	 data		  = 0;
    pm_err_flag_type		 err_flag	  = PM_ERR_FLAG__SUCCESS;
    uint8					 index		  = 0;

    pm_register_address_type base_address;
    pm_register_address_type mode_ctl;
    pm_register_address_type dig_pull_ctl;
    pm_register_address_type dig_in_ctl;
    pm_register_address_type dig_vin_ctl;
    pm_register_address_type sink_ctl;
    pm_register_address_type ana_in_ctl;
    pm_register_address_type ana_out_ctl;

    pm_mpp_data_type *mpp_ptr = pm_mpp_get_data(pmic_chip);
    pm_register_address_type perph_index = (pm_register_address_type)mpp;

    if (mpp_ptr == NULL)
    {
        return PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
    }
    if (NULL == mpp_status)
    {
        return PM_ERR_FLAG__INVALID_POINTER;
    }
    if ((uint8)perph_index >= mpp_ptr->num_of_peripherals)
    {
        return PM_ERR_FLAG__INVALID_MPP_INDEXED;
    }

    base_address = mpp_ptr->mpp_reg_table->base_address + (mpp_ptr->mpp_reg_table->peripheral_offset * perph_index);
    mode_ctl	  =	base_address + mpp_ptr->mpp_reg_table->mode_ctl;
    dig_pull_ctl =	base_address + mpp_ptr->mpp_reg_table->dig_pull_ctl;
    dig_in_ctl	  =	base_address + mpp_ptr->mpp_reg_table->dig_in_ctl;
    dig_vin_ctl  =	base_address + mpp_ptr->mpp_reg_table->dig_vin_ctl;
    sink_ctl     =	base_address + mpp_ptr->mpp_reg_table->sink_ctl;
    ana_in_ctl   =	base_address + mpp_ptr->mpp_reg_table->ana_in_ctl;
    ana_out_ctl  =	base_address + mpp_ptr->mpp_reg_table->ana_out_ctl;

    //Determine configuration of MPP
    err_flag = pm_comm_read_byte_mask(mpp_ptr->comm_ptr->slave_id, mode_ctl, 0x70, &data, 0);

    if (PM_ERR_FLAG__SUCCESS == err_flag)
    {
        mpp_status->mpp_config = (pm_mpp_config_type)(data >> 4);

        //Based on configuration fill out appropriate struct
        switch (mpp_status->mpp_config)
        {
        case PM_MPP_DIG_IN:

            err_flag = pm_comm_read_byte_mask(mpp_ptr->comm_ptr->slave_id, dig_vin_ctl, 0x07, &data, 0);
            if (PM_ERR_FLAG__SUCCESS == err_flag) mpp_status->mpp_config_settings.mpp_digital_input_status.mpp_dlogic_lvl = (pm_mpp_dlogic_lvl_type)data;

            err_flag = pm_comm_read_byte_mask(mpp_ptr->comm_ptr->slave_id, dig_in_ctl, 0xF, &data, 0);
            if (PM_ERR_FLAG__SUCCESS == err_flag)
            {

                //Check which bit is set to determine DBUS index, break if index goes beyond number of DBUS lines
                while (data >>= 1)
                {
                    if (index >= (mpp_ptr)->mpp_specific->num_of_dbus) break;
                    index++;
                }

                mpp_status->mpp_config_settings.mpp_digital_input_status.mpp_dlogic_in_dbus = (pm_mpp_dlogic_in_dbus_type)index;
            }
            break;
        case PM_MPP_DIG_OUT:

            err_flag = pm_comm_read_byte_mask(mpp_ptr->comm_ptr->slave_id, dig_vin_ctl, 0x07, &data, 0);
            if (PM_ERR_FLAG__SUCCESS == err_flag) mpp_status->mpp_config_settings.mpp_digital_output_status.mpp_dlogic_lvl = (pm_mpp_dlogic_lvl_type)data;

            err_flag = pm_comm_read_byte_mask(mpp_ptr->comm_ptr->slave_id, mode_ctl, 0x03, &data, 0);
            if (PM_ERR_FLAG__SUCCESS == err_flag) mpp_status->mpp_config_settings.mpp_digital_output_status.mpp_dlogic_out_ctrl = (pm_mpp_dlogic_out_ctrl_type)data;

            break;
        case PM_MPP_BI_DIR:

            err_flag = pm_comm_read_byte_mask(mpp_ptr->comm_ptr->slave_id, dig_pull_ctl, 0x07, &data, 0);
            if (PM_ERR_FLAG__SUCCESS == err_flag) mpp_status->mpp_config_settings.mpp_bidirectional_status.mpp_dlogic_inout_pup = (pm_mpp_dlogic_inout_pup_type)data;

            err_flag = pm_comm_read_byte_mask(mpp_ptr->comm_ptr->slave_id, dig_vin_ctl, 0x07, &data, 0);
            if (PM_ERR_FLAG__SUCCESS == err_flag) mpp_status->mpp_config_settings.mpp_bidirectional_status.mpp_dlogic_lvl = (pm_mpp_dlogic_lvl_type)data;

            break;
        case PM_MPP_ANALOG_IN:

            err_flag = pm_comm_read_byte_mask(mpp_ptr->comm_ptr->slave_id, ana_in_ctl, 0x07, &data, 0);
            if (PM_ERR_FLAG__SUCCESS == err_flag) mpp_status->mpp_config_settings.mpp_analog_input_status.mpp_ain_ch = (pm_mpp_ain_ch_type)data;

            break;
        case PM_MPP_ANALOG_OUT:

            err_flag = pm_comm_read_byte_mask(mpp_ptr->comm_ptr->slave_id, ana_out_ctl, 0x07, &data, 0);
            if (PM_ERR_FLAG__SUCCESS == err_flag) mpp_status->mpp_config_settings.mpp_analog_output_status.mpp_aout_level = (pm_mpp_aout_level_type)data;

            err_flag = pm_comm_read_byte_mask(mpp_ptr->comm_ptr->slave_id, mode_ctl, 0x03, &data, 0);
            if (PM_ERR_FLAG__SUCCESS == err_flag) mpp_status->mpp_config_settings.mpp_analog_output_status.mpp_aout_switch = (pm_mpp_aout_switch_type)data;

            break;
        case PM_MPP_I_SINK:

            err_flag = pm_comm_read_byte_mask(mpp_ptr->comm_ptr->slave_id, sink_ctl, 0x07, &data, 0);
            if (PM_ERR_FLAG__SUCCESS == err_flag) mpp_status->mpp_config_settings.mpp_current_sink_status.mpp_i_sink_level = (pm_mpp_i_sink_level_type)data;

            err_flag = pm_comm_read_byte_mask(mpp_ptr->comm_ptr->slave_id, mode_ctl, 0x03, &data, 0);
            if (PM_ERR_FLAG__SUCCESS == err_flag) mpp_status->mpp_config_settings.mpp_current_sink_status.mpp_i_sink_switch = (pm_mpp_i_sink_switch_type)data;

            break;
        case PM_MPP_TYPE_INVALID:
            err_flag = PM_ERR_FLAG__INVALID;
            break;
        default:
            err_flag = PM_ERR_FLAG__INVALID;
            break;
        }
    }

    return err_flag;
}


pm_err_flag_type pm_mpp_enable(uint32 pmic_chip, pm_mpp_perph_index mpp, boolean enable)
{
    pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;
    pm_register_data_type data = 0;
    pm_register_address_type en_ctl;
    pm_mpp_data_type *mpp_ptr = pm_mpp_get_data(pmic_chip);
    pm_register_address_type perph_index = (pm_register_address_type)mpp;


    if (mpp_ptr == NULL)
    {
        return PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
    }

    en_ctl = mpp_ptr->mpp_reg_table->base_address + (mpp_ptr->mpp_reg_table->peripheral_offset * perph_index) + mpp_ptr->mpp_reg_table->en_ctl;

    // MPP_EN	0	"MPP enable
    //              0 = puts MPP_PAD at high Z and disables the block
    //              1 = MPP is enabled"
    if (TRUE == enable)
    {
        data = 0x80;
    }
    err_flag = pm_comm_write_byte_mask(mpp_ptr->comm_ptr->slave_id, en_ctl, 0x80, data, 0);

    return err_flag;
}


/*===========================================================================

                     INTERNAL FUNCTION DEFINITIONS

===========================================================================*/

pm_err_flag_type pm_mpp_is_dbus_valid(uint32 pmic_chip, uint8  perph_index, pm_mpp_dlogic_in_dbus_type  dbus)
{
    pm_err_flag_type    err_flag   = PM_ERR_FLAG__SUCCESS;
    uint8               index     = 0;
    pm_mpp_data_type *mpp_ptr = pm_mpp_get_data(pmic_chip);

    if (mpp_ptr == NULL)
    {
        return PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
    }
    if (perph_index >= mpp_ptr->num_of_peripherals)
    {
        return PM_ERR_FLAG__INVALID_MPP_INDEXED;
    }

    switch (dbus)
    {
        //case PM_MPP__DLOGIC_IN__DBUS_NONE:
        //    /* Only the MPP that reserved the DBUS/DTEST can release it.*/
        //    for (index = 0; index < mpp_ptr->mpp_specific->num_of_dbus; index++)
        //    {
        //        if (mpp_ptr->m_dbus_busy[index] == perph_index)
        //        {
        //            mpp_ptr->m_dbus_busy[index] = mpp_ptr->num_of_peripherals;
        //        }
        //    }
        //    break;

    case PM_MPP__DLOGIC_IN__DBUS1:
    case PM_MPP__DLOGIC_IN__DBUS2:
    case PM_MPP__DLOGIC_IN__DBUS3:
    case PM_MPP__DLOGIC_IN__DBUS4:
        /* Is the DBUS/DTEST already in use by another MPP?*/
        if ((mpp_ptr->m_dbus_busy[dbus] == mpp_ptr->num_of_peripherals) ||
            (mpp_ptr->m_dbus_busy[dbus] == perph_index))
        {
            /* Before we reserve the DBUS/DTEST, check if the MPP 
            has another DBUS/DTEST reserved.*/
            for (index = 0; index < mpp_ptr->mpp_specific->num_of_dbus; index++)
            {
                if (mpp_ptr->m_dbus_busy[index] == perph_index)
                {
                    /* the MPP has a DBUS/DTEST already reserved */
                    break;
                }
            }

            /* Assign the bus to the MPP. */
            mpp_ptr->m_dbus_busy[dbus] = perph_index;

            /* If the MPP has another DBUS/DTEST reserved then free it */
            if ((index != mpp_ptr->mpp_specific->num_of_dbus) && (index != dbus))
            {
                mpp_ptr->m_dbus_busy[index] = mpp_ptr->num_of_peripherals;
            }
        }
        else
        {
            /* The DBUS/DTEST is busy, return an ERROR. */
            err_flag = PM_ERR_FLAG__DBUS_IS_BUSY_MODE;
        }

        break;
    default:

        /* The user passed an invalid data bus selection. */
        err_flag = PM_ERR_FLAG__PAR1_OUT_OF_RANGE;
    }

    return err_flag;
}

pm_err_flag_type pm_mpp_abus_pulldown(uint32 pmic_chip, uint8  perph_index, uint8  which_ch, pm_drv_mpp_config_type  mpp_type)
{
    pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;
    pm_mpp_data_type *mpp_ptr = pm_mpp_get_data(pmic_chip);

    if (mpp_ptr == NULL)
    {
        return PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
    }
    if ((uint8)perph_index >= mpp_ptr->num_of_peripherals)
    {
        return PM_ERR_FLAG__INVALID_MPP_INDEXED;
    }

    /* If the config type is Analog Input and the MPP is routed to one of
    * the ABUS lines, then check further to see if it can really use it 
    */

    if (PM_MPP_ANALOG_IN == mpp_type)
    {
        if (which_ch >= (uint8)PM_MPP__AIN__CH_ABUS1 &&
            which_ch <= (uint8)PM_MPP__AIN__CH_ABUS4)
        {
            /* if m_abus_in_use indicates the ABUS line in question is being
            * used but this MPP is not using it, then someone else is using
            * it. The MPP can't have it since it's considered to be busy
            */
            if ((mpp_ptr->m_abus_in_use & (1 << which_ch)) &&
                mpp_ptr->m_mpp_using_abus[perph_index] != which_ch)
            {
                err_flag = PM_ERR_FLAG__ABUS_IS_BUSY_MODE;
            }
            else
            {
                /* Before setting any bit in m_abus_in_use, check whether any of
                * the ABUS lines are already in use. If true, don't need to 
                * set bit 7 of register 0x7F since it should have been set already
                */
                // in MISC module
                if (!mpp_ptr->m_abus_in_use) (void)pm_comm_write_byte_mask(mpp_ptr->comm_ptr->slave_id, mpp_ptr->mpp_specific->pm_drv_test_acc_rw, 0x80, 0x80, 0);
                /* If this MPP is already using an ABUS line which might be
                * different from the one being configured now, clear it.
                * That means the MPP will be re-routed to a different ABUS line
                */
                if (mpp_ptr->m_mpp_using_abus[perph_index])
                {
                    mpp_ptr->m_abus_in_use &= ~(uint32)(1 << mpp_ptr->m_mpp_using_abus[perph_index]);
                }
                /* Set the global flags to indicate the ABUS line is now 
                * being used by this MPP
                */
                mpp_ptr->m_mpp_using_abus[perph_index] = which_ch;
                mpp_ptr->m_abus_in_use |= (1 << which_ch);
            }
        }
    }
    else
    {
        /* The MPP is being configured to a type that won't use the ABUS
        * line. Check if the MPP has been using any ABUS line. If so,
        * clear it.
        */
        if (mpp_ptr->m_mpp_using_abus[perph_index])
        {
            mpp_ptr->m_abus_in_use &= ~(uint32)(1 << mpp_ptr->m_mpp_using_abus[perph_index]);
            mpp_ptr->m_mpp_using_abus[perph_index] = 0;
            /* Clear bit 7 of register 0x7F if none of the ABUS lines are
            * being used
            */
            //in MISC module
            if (!mpp_ptr->m_abus_in_use) (void)pm_comm_write_byte_mask(mpp_ptr->comm_ptr->slave_id, mpp_ptr->mpp_specific->pm_drv_test_acc_rw, 0x80, 0x00, 0);
        }
    }

    return err_flag;
}

pm_err_flag_type pm_mpp_configure_type(uint32 pmic_chip,uint8  perph_index, pm_drv_mpp_config_type type)
{
    pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;
    pm_mpp_data_type *mpp_ptr = pm_mpp_get_data(pmic_chip);
    pm_register_address_type mode_ctl;

    if (mpp_ptr == NULL)
    {
        return PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
    }
    if ((uint8)perph_index >= mpp_ptr->num_of_peripherals)
    {
        return PM_ERR_FLAG__INVALID_MPP_INDEXED;
    }

    mode_ctl = mpp_ptr->mpp_reg_table->base_address + (pm_register_address_type)(mpp_ptr->mpp_reg_table->peripheral_offset * perph_index) + mpp_ptr->mpp_reg_table->mode_ctl;

    // Set MPP_TYPE to DIGITAL INPUT
    //MPP Type:
    //0: Digital Input
    //1: Digital Output
    //2: Digital Input and Digital Output
    //3: Bidirectional Logic
    //4: Analog Input
    //5: Analog Output
    //6: Current Sink
    //7: Reserved
    err_flag = pm_comm_write_byte_mask(mpp_ptr->comm_ptr->slave_id, mode_ctl, 0x70, (pm_register_data_type)(type << 4), 0);

    return err_flag;
}





pm_err_flag_type pm_mpp_config_dvin(uint32 pmic_chip, uint8  perph_index, pm_mpp_dlogic_lvl_type  level)
{
    pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;
    pm_mpp_data_type *mpp_ptr = pm_mpp_get_data(pmic_chip);
    pm_register_address_type dig_vin_ctl;

    if (mpp_ptr == NULL)
    {
        return PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
    }
    if ((uint8)perph_index >= mpp_ptr->num_of_peripherals)
    {
        return PM_ERR_FLAG__INVALID_MPP_INDEXED;
    }

    dig_vin_ctl = mpp_ptr->mpp_reg_table->base_address + (pm_register_address_type)(mpp_ptr->mpp_reg_table->peripheral_offset * perph_index) + mpp_ptr->mpp_reg_table->dig_vin_ctl;

    // Configure the VOLTAGE_SEL
    // "Select Voltage source:
    //   000 = VIN0 (refer to the objective spec.)
    //   001 = VIN1 (refer to the objective spec.)
    //   010 = VIN2 (refer to the objective spec.)*
    //   011 = VIN3 (refer to the objective spec.)
    //   100 = VIN4 (refer to the objective spec.)*
    //   101 = VIN5 (refer to the objective spec.)
    //   110 = VIN6 (refer to the objective spec.)
    //   111 = VIN7 (refer to the objective spec.)

    err_flag = pm_comm_write_byte_mask(mpp_ptr->comm_ptr->slave_id, dig_vin_ctl, 0x07, (pm_register_data_type)level, 0);

    return err_flag;
}



pm_err_flag_type pm_mpp_irq_enable(uint32 pmic_chip, pm_mpp_perph_index  perph_index, boolean enable)
{
    pm_err_flag_type    err_flag    = PM_ERR_FLAG__SUCCESS;
    pm_register_address_type irq_reg;

    pm_mpp_data_type *mpp_ptr = pm_mpp_get_data(pmic_chip);

    if (mpp_ptr == NULL)
    {
        return PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
    }
    if ((uint8)perph_index >= mpp_ptr->num_of_peripherals)
    {
        return PM_ERR_FLAG__INVALID_MPP_INDEXED;
    }

    if (enable)
    {
        irq_reg = mpp_ptr->mpp_reg_table->base_address + (pm_register_address_type)(mpp_ptr->mpp_reg_table->peripheral_offset * perph_index) + mpp_ptr->mpp_reg_table->int_en_set;
    }
    else
    {
        irq_reg = mpp_ptr->mpp_reg_table->base_address + (pm_register_address_type)(mpp_ptr->mpp_reg_table->peripheral_offset * perph_index) + mpp_ptr->mpp_reg_table->int_en_clr;
    }

    err_flag = pm_comm_write_byte_mask(mpp_ptr->comm_ptr->slave_id, irq_reg, 0x01, 0xFF, 0);
    return err_flag;
}

pm_err_flag_type pm_mpp_irq_clear(uint32 pmic_chip, pm_mpp_perph_index perph_index)
{
    pm_err_flag_type    err_flag    = PM_ERR_FLAG__SUCCESS;
    pm_mpp_data_type *mpp_ptr = pm_mpp_get_data(pmic_chip);
    pm_register_address_type int_latched_clr;

    if (mpp_ptr == NULL)
    {
        return PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
    }
    if ((uint8)perph_index >= mpp_ptr->num_of_peripherals)
    {
        return PM_ERR_FLAG__INVALID_MPP_INDEXED;
    }

    int_latched_clr = mpp_ptr->mpp_reg_table->base_address + (pm_register_address_type)(mpp_ptr->mpp_reg_table->peripheral_offset * perph_index) + mpp_ptr->mpp_reg_table->int_latched_clr;
    err_flag = pm_comm_write_byte_mask(mpp_ptr->comm_ptr->slave_id, int_latched_clr, 0x01, 0xFF, 0);
    return err_flag;
}


pm_err_flag_type pm_mpp_irq_set_trigger(uint32 pmic_chip, pm_mpp_perph_index perph_index, pm_irq_trigger_type trigger)
{
    pm_err_flag_type    err_flag    = PM_ERR_FLAG__SUCCESS;
    pm_register_data_type set_type, polarity_high, polarity_low;

    pm_mpp_data_type *mpp_ptr = pm_mpp_get_data(pmic_chip);

    if (mpp_ptr == NULL)
    {
        return PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
    }
    if ((uint8)perph_index >= mpp_ptr->num_of_peripherals)
    {
        return PM_ERR_FLAG__INVALID_MPP_INDEXED;
    }

    pm_register_address_type int_set_type = mpp_ptr->mpp_reg_table->base_address + (pm_register_address_type)(mpp_ptr->mpp_reg_table->peripheral_offset * perph_index) + mpp_ptr->mpp_reg_table->int_set_type;
    pm_register_address_type int_polarity_high = mpp_ptr->mpp_reg_table->base_address + (pm_register_address_type)(mpp_ptr->mpp_reg_table->peripheral_offset * perph_index) + mpp_ptr->mpp_reg_table->int_polarity_high;
    pm_register_address_type int_polarity_low = mpp_ptr->mpp_reg_table->base_address + (pm_register_address_type)(mpp_ptr->mpp_reg_table->peripheral_offset * perph_index) + mpp_ptr->mpp_reg_table->int_polarity_low;

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
        return PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
    }
    err_flag = pm_comm_write_byte_mask(mpp_ptr->comm_ptr->slave_id, int_set_type, 0x01, set_type, 0);
    err_flag |= pm_comm_write_byte_mask(mpp_ptr->comm_ptr->slave_id, int_polarity_high, 0x01, polarity_high, 0);
    err_flag |= pm_comm_write_byte_mask(mpp_ptr->comm_ptr->slave_id, int_polarity_low, 0x01, polarity_low, 0);

    return err_flag;
}

pm_err_flag_type pm_mpp_irq_status(uint32 pmic_chip,  pm_mpp_perph_index perph_index, pm_irq_status_type type, boolean *status)
{
    pm_err_flag_type    err_flag    = PM_ERR_FLAG__SUCCESS;
    pm_register_data_type data;
    pm_register_address_type int_sts;

    pm_mpp_data_type *mpp_ptr = pm_mpp_get_data(pmic_chip);

    if (mpp_ptr == NULL)
    {
        return PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
    }
    if ((uint8)perph_index >= mpp_ptr->num_of_peripherals)
    {
        return PM_ERR_FLAG__INVALID_MPP_INDEXED;
    }

    switch (type)
    {
    case PM_IRQ_STATUS_RT:
        int_sts = mpp_ptr->mpp_reg_table->base_address + (pm_register_address_type)(mpp_ptr->mpp_reg_table->peripheral_offset * perph_index) + mpp_ptr->mpp_reg_table->int_rt_sts;
        break;
    case PM_IRQ_STATUS_LATCHED:
        int_sts = mpp_ptr->mpp_reg_table->base_address + (pm_register_address_type)(mpp_ptr->mpp_reg_table->peripheral_offset * perph_index) + mpp_ptr->mpp_reg_table->int_latched_sts;
        break;
    case PM_IRQ_STATUS_PENDING:
        int_sts = mpp_ptr->mpp_reg_table->base_address + (pm_register_address_type)(mpp_ptr->mpp_reg_table->peripheral_offset * perph_index) + mpp_ptr->mpp_reg_table->int_pending_sts;
        break;
    default:
        return PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
    }

    err_flag = pm_comm_read_byte_mask(mpp_ptr->comm_ptr->slave_id, int_sts, 0x01, &data, 0);
    *status = data ? TRUE : FALSE;

    return err_flag;
}


