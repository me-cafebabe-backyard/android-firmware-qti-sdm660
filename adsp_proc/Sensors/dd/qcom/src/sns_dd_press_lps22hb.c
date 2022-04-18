/******************** (C) COPYRIGHT 2016 STMicroelectronics ********************
*
* File Name         : sns_dd_lps22hb.c
* Authors           : Wei Wang
* Version           : V 1.3.0
* Date              : 04/07/2016
* Description       : LPS22HB pressure sensor driver source file
*
********************************************************************************
* Copyright (c) 2016, STMicroelectronics.
* All rights reserved.
* 
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*     1. Redistributions of source code must retain the above copyright
*      notice, this list of conditions and the following disclaimer.
*     2. Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimer in the
*       documentation and/or other materials provided with the distribution.
*     3. Neither the name of the STMicroelectronics nor the
*       names of its contributors may be used to endorse or promote products
*       derived from this software without specific prior written permission.
* 
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*******************************************************************************
* REVISON HISTORY
*
* VERSION | DATE          | DESCRIPTION
* 1.3.0   | 04/07/2016    | Fix bug of ODR=0 setting.
* 1.2.0   | 02/08/2016    | Update some parameters.
* 1.1.0   | 12/05/2015    | Update _probe(), _handle_timer().
* 1.0.0   | 11/16/2015    | Fix temperature reading and pressure LPF issue.
* 0.9.0   | 07/13/2015    | Created.
*******************************************************************************/

#include "sns_dd_press_lps22hb.h"

sns_ddf_driver_if_s sns_dd_press_lps22hb_if;

static sns_ddf_odr_t lps22hb_odr_hz[LPS22HB_ODR_NUM] = {1, 10, 25, 50, 75};
static uint8_t lps22hb_odr_code[LPS22HB_ODR_NUM] = {1, 2, 3, 4, 5};

/** 
 * @brief Resets the driver and device so they return to the state they were
 *        in after init() was called.
 *  
 * Refer to sns_ddf_driver_if.h for definition.
 */
sns_ddf_status_e sns_dd_lps22hb_reset(sns_ddf_handle_t dd_handle)
{
    sns_dd_lps22hb_state_t* state = (sns_dd_lps22hb_state_t*)dd_handle;
    sns_ddf_status_e status;
    uint8_t reg;
    uint8_t rw_bytes;

    DD_MSG_0(MED, "Reset():");

    // Init CTRL_REG1, put LPS22HB into power down.
    reg = 0
        | (0<<4)        // ODR[2:0]: 0-1S/1S;1-1/1Hz;2-10/10;3-25/25;4-50/50;5-75/75;
        | (1<<3)        // EN_LPFP: 0-low pass filter disabled; 1-enabled.
        | (1<<2)        // LPF_CFG: 0-ODR/9; 1-ODR/20.
        | (1<<1)        // BDU
        | 0;            // SIM: 0-4 wire SPI; 1-3wire SPI.
    status=sns_dd_lps22hb_write_regs(LPS22HB_CTRL_REG1, &reg, 1);
    if (status!=SNS_DDF_SUCCESS) return status;
    if (state->ctrl_reg1&0xF0) sns_ddf_delay(1000);    // Sensor was active, wait sensor to power down by delaying 1 ms.
    state->ctrl_reg1 = reg;
    state->dd_press_odr = state->dd_temp_odr = 0;
    state->sensor_odr_code = 0;

    // Init INTERRUPT_CFG
    reg = 0;
    status=sns_dd_lps22hb_write_regs(LPS22HB_INTERRUPT_CFG, &reg, 1);
    if (status!=SNS_DDF_SUCCESS) return status;

    // Init CTRL_REG2
    reg = 0
        | (0<<7)        // BOOT
        | (0<<6)        // FIFO_EN
        | (0<<5)        // STOP_ON_FIFO:
        | (1<<4)        // IF_ADD_INC:
        | (0<<3)        // I2C_DIS: 0-I2c enabled; 1-disable.
        | (0<<2)        // SWRESET: 0-Normal mode; 1-Software reset.
        | 0;            // OneShotEnable when ODR=0: 0-wait for start of conversion; 1-start for a new data set.
    status=sns_dd_lps22hb_write_regs(LPS22HB_CTRL_REG2, &reg, 1);
    if (status!=SNS_DDF_SUCCESS) return status;

    // Init CTRL_REG3
    reg = 0
        | (0<<7)        // INT_H_L: 0-interrupt active high; 1-active low.
        | (0<<6)        // PP_OD: 0-push pull; 1-open drain.
        | (0<<5)        // F_FSS5: 0-disable; 1-FIFO full on INT_DRDY pin.
        | (0<<4)        // F_FTH:
        | (0<<3)        // F_OVR:
        | (1<<2)        // DRDY:
        | 0;            // INT1_S[1:0]: 0-Data Signal; 1-P High; 2-P Low; 3-P_low or P_high;
    status=sns_dd_lps22hb_write_regs(LPS22HB_CTRL_REG3, &reg, 1);
    if (status!=SNS_DDF_SUCCESS) return status;

    // Init FIFO_CTRL
    reg=0
        | (0<<5)        // F_MODE[2:0]: 0-Bypass; 1-FIFO; 2-Stream; 3-Stream-to-FIFO; 4-Bypass-to-Stream; 5-Reserved; 6-Dynamic-Stream; 7-Bypass-to-FIFO
        | 0;            // WTM[4:0];
    status=sns_dd_lps22hb_write_regs(LPS22HB_FIFO_CTRL, &reg, 1);
    if (status!=SNS_DDF_SUCCESS) return status;

    // Init RES_CONF
    reg = 0
        | 0;            // LC_EN: 0-Normal mode; 1-Low Current Mode.
    status=sns_dd_lps22hb_write_regs(LPS22HB_RES_CONF, &reg, 1);
    if (status!=SNS_DDF_SUCCESS) return status;
    
    // reset LPF
    status=sns_dd_lps22hb_read_regs(0x33, &reg, 1);
    if (status!=SNS_DDF_SUCCESS) return status;

    state->timer_type = LPS22HB_TIMER_Idle;
    state->start_count = 0;

    return SNS_DDF_SUCCESS;
}

static sns_ddf_status_e lps22hb_match_odr(sns_ddf_odr_t desired_odr, sns_ddf_odr_t* proposed_odr, int* odr_index)
{
    int i;
    for (i=0; i<LPS22HB_ODR_NUM; i++) if (desired_odr<=lps22hb_odr_hz[i]) break;
    if (i>=LPS22HB_ODR_NUM) i=LPS22HB_ODR_NUM-1;
    *proposed_odr=lps22hb_odr_hz[i];
    *odr_index=i;
    return SNS_DDF_SUCCESS;
}

/**
 * @brief Performs a set data sampling rate operation
 *        -- Must set power to low before doing this
 *
 * @param[in]  dd_handle      Handle to a driver instance.
 * @param[in]  odr_index       Data sampling rate settings for LPS22HB
 * 
 * @return SNS_DDF_SUCCESS if this operation was done successfully. Otherwise
 *         SNS_DDF_EDEVICE, SNS_DDF_EBUS, SNS_DDF_EINVALID_PARAM, or SNS_DDF_EFAIL to
 *         indicate and error has occurred.
 */
static sns_ddf_status_e lps22hb_set_odr(sns_dd_lps22hb_state_t* state, uint8 odr_code)
{
    sns_ddf_status_e status;
    uint8_t rw_bytes;
    state->ctrl_reg1=(state->ctrl_reg1&0x0F) | (odr_code<<4);
    status=sns_dd_lps22hb_write_regs(LPS22HB_CTRL_REG1, &state->ctrl_reg1, 1);
    return status;
}

/**
 * @brief Performs a set power state operation
 *
 * @param[in]  dd_handle      Handle to a driver instance.
 * @param[in]  power_state    Power state to be set.
 * 
 * @return SNS_DDF_SUCCESS if this operation was done successfully. Otherwise
 *         SNS_DDF_EDEVICE, SNS_DDF_EBUS, SNS_DDF_EINVALID_PARAM, or SNS_DDF_EFAIL to
 *         indicate and error has occurred.
 */
static sns_ddf_status_e lps22hb_set_power(sns_dd_lps22hb_state_t* state, sns_ddf_powerstate_e power_state)
{
    sns_ddf_status_e status = SNS_DDF_SUCCESS;
    uint8_t rw_bytes;
	if ((power_state==SNS_DDF_POWERSTATE_LOWPOWER)&&((state->ctrl_reg1&0x70)!=0))
	{
	    state->ctrl_reg1&=0x0F;
	    state->sensor_odr_code = 0;
	    status=sns_dd_lps22hb_write_regs(LPS22HB_CTRL_REG1, &state->ctrl_reg1, 1);
	}
    return status;
}

/** 
 * @brief Initializes the lps25h driver and sets up sensor. 
 *  
 * Refer to sns_ddf_driver_if.h for definition.
 */
sns_ddf_status_e sns_dd_lps22hb_init(
    sns_ddf_handle_t* dd_handle_ptr,
    sns_ddf_handle_t smgr_handle,
    sns_ddf_nv_params_s* nv_params,
    sns_ddf_device_access_s device_info[],
    uint32_t num_devices,
    sns_ddf_memhandler_s* memhandler,
    sns_ddf_sensor_e* sensors[],
    uint32_t* num_sensors)
{
    sns_ddf_status_e status;
    sns_dd_lps22hb_state_t* state;
    static sns_ddf_sensor_e my_sensors[] = {SNS_DDF_SENSOR_PRESSURE, SNS_DDF_SENSOR_TEMP};
    uint8_t reg;
    uint8_t rw_bytes;
    
    DD_MSG_0(MED, "Init:");

#if defined(BUILD_UIMAGE)
	/* Update smgr sensor data for the driver to indicate uImage support */
	sns_ddf_smgr_set_uimg_refac(smgr_handle);
#endif

    // Allocate a driver instance.
    status = sns_dd_malloc((void**)&state, sizeof(sns_dd_lps22hb_state_t), smgr_handle);
    if(status != SNS_DDF_SUCCESS) return SNS_DDF_ENOMEM;
    memset(state, 0x0, sizeof(sns_dd_lps22hb_state_t));
    *dd_handle_ptr = state;
    state->smgr_handle = smgr_handle;
    state->gpio_num = device_info->first_gpio;
    state->last_irq_timestamp = 0;

     // Open communication port to the device.
    status = sns_ddf_open_port(&state->port_handle, &device_info->port_config);
    if(status != SNS_DDF_SUCCESS)
    {
        DD_MSG_0(ERROR, "Init: can't open i2c.");
    	sns_dd_mfree(state, smgr_handle);
        return status;
    }

    // Check WhoAmIRegister to make sure this is the correct driver
    status=sns_dd_lps22hb_read_regs(LPS22HB_WHO_AM_I, &reg, 1);
    if (status!=SNS_DDF_SUCCESS)
    {
        DD_MSG_0(ERROR, "Init: can't open device.");
        sns_ddf_close_port(state->port_handle);
        sns_dd_mfree(state, smgr_handle);
        return status;
    }
    if (reg!=LPS22HB_WHOAMI_VALUE)
    {
        DD_MSG_1(ERROR, "Init: wrong WhoAmI=%d.", reg);
        sns_ddf_close_port(state->port_handle);
        sns_dd_mfree(state, smgr_handle);
        return SNS_DDF_EFAIL;
    }

    // Resets the LPS22HB
    status = sns_dd_lps22hb_reset(state);
    if(status != SNS_DDF_SUCCESS)
    {
        DD_MSG_0(ERROR, "Init: reset error.");
        sns_ddf_close_port(state->port_handle);
        sns_dd_mfree(state, smgr_handle);
        return status;
    }

    status = sns_ddf_timer_init(&state->timer_obj,
                                state,
                                &sns_dd_press_lps22hb_if,
                                state, //always return dd_handle_ptr
                                false); // not periodic
    if(status != SNS_DDF_SUCCESS)
    {
        DD_MSG_0(ERROR, "Init: timer error.");
        sns_ddf_close_port(state->port_handle);
        sns_dd_mfree(state, smgr_handle);
        return status;
    }

    // Fill out output parameters.
    *num_sensors = 2;
    *sensors = my_sensors;
    DD_MSG_0(MED, "Init: succeeded.");
    return SNS_DDF_SUCCESS;
}

/** 
 * @brief Retrieves the value of an attribute for a lps25h sensor.
 *  
 * Refer to sns_ddf_driver_if.h for definition.
 */
sns_ddf_status_e sns_dd_lps22hb_get_attr(
    sns_ddf_handle_t dd_handle,
    sns_ddf_sensor_e sensor,
    sns_ddf_attribute_e attrib,
    sns_ddf_memhandler_s* memhandler,
    void** value,
    uint32_t* num_elems)
{
	sns_dd_lps22hb_state_t *state;

    DD_MSG_2(MED, "GetAttr(S%d, A%d)", sensor, attrib);
    if (dd_handle==NULL || value==NULL)
    {
        DD_MSG_0(ERROR, "GetAttr: dd_handle is NULL");
        return SNS_DDF_EINVALID_PARAM;
    }

    state = (sns_dd_lps22hb_state_t*)dd_handle;
    if (state->smgr_handle==NULL) return SNS_DDF_EINVALID_PARAM;

    switch(attrib)
    {
        case SNS_DDF_ATTRIB_POWER_INFO:
        {
            sns_ddf_power_info_s *power;
            power = sns_dd_memhandler_malloc(memhandler, sizeof(sns_ddf_power_info_s), state->smgr_handle);
            if(NULL == power) return SNS_DDF_ENOMEM;
            power->active_current = 275;     //current consumption, unit uA
            power->lowpower_current = 1;
            *value = power;
            *num_elems = 1;
            return SNS_DDF_SUCCESS;
        }

        case SNS_DDF_ATTRIB_RANGE:
        {
            sns_ddf_range_s *range;
            range = sns_dd_memhandler_malloc(memhandler, sizeof(sns_ddf_range_s), state->smgr_handle);
            if(NULL == range) return SNS_DDF_ENOMEM;
            if(sensor == SNS_DDF_SENSOR_PRESSURE)
            {
                range->min = LPS22HB_PRESS_RANGE_MIN;
                range->max = LPS22HB_PRESS_RANGE_MAX;
            }
            else
            {
                range->min = LPS22HB_TEMP_RANGE_MIN;
                range->max = LPS22HB_TEMP_RANGE_MAX;
            }
            *num_elems = 1;
            *value = range;
            return SNS_DDF_SUCCESS;
        }

        case SNS_DDF_ATTRIB_RESOLUTION:
        {
            sns_ddf_resolution_t *res;
            res = sns_dd_memhandler_malloc(memhandler, sizeof(sns_ddf_resolution_t), state->smgr_handle);
            if(NULL == res) return SNS_DDF_ENOMEM;
            if(sensor == SNS_DDF_SENSOR_PRESSURE)
                *res = LPS22HB_MAX_RES_PRESS;
            else
                *res = LPS22HB_MAX_RES_TEMP;
            *value = res;
            *num_elems = 1;
            return SNS_DDF_SUCCESS;
        }

        case SNS_DDF_ATTRIB_RESOLUTION_ADC:
        {
            sns_ddf_resolution_adc_s *res;
            res = sns_dd_memhandler_malloc(memhandler ,sizeof(sns_ddf_resolution_adc_s), state->smgr_handle);
            if(NULL == res) return SNS_DDF_ENOMEM;
            res->bit_len = (sensor==SNS_DDF_SENSOR_PRESSURE)?(LPS22HB_NUM_BYTES_PRESS*8):(LPS22HB_NUM_BYTES_TEMP*8);
            res->max_freq = LPS22HB_MAX_ODR_Hz;
            *value = res;
            *num_elems = 1;
            return SNS_DDF_SUCCESS;
        }

        case SNS_DDF_ATTRIB_ODR:
        {
            sns_ddf_odr_t *odr;
            odr = sns_dd_memhandler_malloc(memhandler ,sizeof(sns_ddf_odr_t), state->smgr_handle);
            if (odr==NULL) return SNS_DDF_ENOMEM;
            *odr = (sensor==SNS_DDF_SENSOR_PRESSURE)? state->dd_press_odr : state->dd_temp_odr;
            *value = odr;
            *num_elems = 1;
            DD_MSG_1(MED, "\tOdr=%d", *odr);
            return SNS_DDF_SUCCESS;
        }

        case SNS_DDF_ATTRIB_SUPPORTED_ODR_LIST:
        {
            *value = lps22hb_odr_hz;
            *num_elems = LPS22HB_ODR_NUM;
            return SNS_DDF_SUCCESS;
        }

        case SNS_DDF_ATTRIB_DELAYS:
        {
            sns_ddf_delays_s *lps22hb_delays;
            lps22hb_delays = sns_dd_memhandler_malloc(memhandler, sizeof(sns_ddf_delays_s), state->smgr_handle);
            if(NULL == lps22hb_delays) return SNS_DDF_ENOMEM;
            lps22hb_delays->time_to_active = 1;
            lps22hb_delays->time_to_data = 1;
            *value = lps22hb_delays;
            *num_elems = 1;
            return SNS_DDF_SUCCESS;
        }

        case SNS_DDF_ATTRIB_DRIVER_INFO:
        {
            sns_ddf_driver_info_s *info;
            info = sns_dd_memhandler_malloc(memhandler,sizeof(sns_ddf_driver_info_s), state->smgr_handle);
            if(NULL == info) return SNS_DDF_ENOMEM;
            info->name = "STM LPS22HB Driver";
            info->version = 10300;
            *value = info;
            *num_elems = 1;
            return SNS_DDF_SUCCESS;
        }

        case SNS_DDF_ATTRIB_DEVICE_INFO:
        {
            sns_ddf_device_info_s *info;
            info = sns_dd_memhandler_malloc(memhandler, sizeof(sns_ddf_device_info_s), state->smgr_handle);
            if(NULL == info) return SNS_DDF_ENOMEM;
            if (sensor==SNS_DDF_SENSOR_PRESSURE) info->name = "Barometer";
            else info->name = "Thermometer";
            info->vendor = "STMicroelectronics";
            info->model = "LPS22HB";
            info->version = 1;
            *value = info;
            *num_elems = 1;
            return SNS_DDF_SUCCESS;
        }
        
        default:
        {
            return SNS_DDF_EINVALID_ATTR;
        }
    }
}

/** 
 * @brief Sets a lps25h sensor attribute to a specific value.
 *  
 * Refer to sns_ddf_driver_if.h for definition.
 */
sns_ddf_status_e sns_dd_lps22hb_set_attr(
    sns_ddf_handle_t dd_handle,
    sns_ddf_sensor_e sensor,
    sns_ddf_attribute_e attrib,
    void* value)
{
    sns_ddf_status_e status=SNS_DDF_SUCCESS;
    sns_dd_lps22hb_state_t* state;

    if (dd_handle==NULL || value==NULL)
    {
        DD_MSG_2(ERROR, "SetAttr(S%d, A%d): dd_handle is NULL", sensor, attrib);
        return SNS_DDF_EINVALID_PARAM;
    }

    state = (sns_dd_lps22hb_state_t*)dd_handle;

    switch(attrib)
    {
        case SNS_DDF_ATTRIB_POWER_STATE:
        {
            sns_ddf_powerstate_e* req_power_state = value;
            int mode_bit, new_mode;
            DD_MSG_3(MED, "SetAttr(S%d, A%d): PowerState=%d", sensor, attrib, *req_power_state);
            if (sensor==SNS_DDF_SENSOR_PRESSURE) mode_bit=LPS22HB_DRVMODE_bPowerPress;
            else if (sensor==SNS_DDF_SENSOR_TEMP) mode_bit=LPS22HB_DRVMODE_bPowerTemp;
            else mode_bit=LPS22HB_DRVMODE_bPowerAll;
            if (*req_power_state==SNS_DDF_POWERSTATE_ACTIVE) new_mode=state->driver_mode|mode_bit;
            else new_mode=state->driver_mode&~mode_bit;
            if ( ((new_mode&LPS22HB_DRVMODE_bPowerAll)==0) != ((state->driver_mode&LPS22HB_DRVMODE_bPowerAll)==0))
                status=lps22hb_set_power(state, *req_power_state);
            state->driver_mode=new_mode;
            return status;
        }

        case SNS_DDF_ATTRIB_RANGE:
        {
            uint8_t range_idx = *(uint8_t*)value;
			if (range_idx!=0) status=SNS_DDF_EINVALID_PARAM;
            DD_MSG_3(MED, "SetAttr(S%d, A%d): RangeIndex=%d", sensor, attrib, range_idx);
            return SNS_DDF_SUCCESS;
        }

        case SNS_DDF_ATTRIB_ODR:
        {
            sns_ddf_odr_t* odr = (sns_ddf_odr_t*)value;
            sns_ddf_odr_t desired_odr, proposed_odr;
            int odr_index;

            desired_odr=*odr;
            if (desired_odr==0)
            {
                if (sensor==SNS_DDF_SENSOR__ALL) state->dd_press_odr = state->dd_temp_odr = 0;
                else if (sensor==SNS_DDF_SENSOR_PRESSURE) state->dd_press_odr = 0;
                else if (sensor==SNS_DDF_SENSOR_TEMP) state->dd_temp_odr = 0;
                if ((state->dd_press_odr==0)&&(state->dd_temp_odr==0))
                {
                	status = lps22hb_set_odr(state, 0);
                	state->sensor_odr_code = 0;
                }
            }
            else
            {
                lps22hb_match_odr(desired_odr, &proposed_odr, &odr_index);
                if (sensor==SNS_DDF_SENSOR__ALL)
                {
                    if (lps22hb_odr_code[odr_index]!=state->sensor_odr_code)
                    {
                        status = lps22hb_set_odr(state, lps22hb_odr_code[odr_index]);
                        state->sensor_odr_code = lps22hb_odr_code[odr_index];
                    }
                    *odr = state->dd_press_odr = state->dd_temp_odr = proposed_odr;
                }
                else if (sensor==SNS_DDF_SENSOR_PRESSURE)
                {
                    if (lps22hb_odr_code[odr_index]!=state->sensor_odr_code)
                    {
                        status = lps22hb_set_odr(state, lps22hb_odr_code[odr_index]);
                        state->sensor_odr_code = lps22hb_odr_code[odr_index];
                        if (state->dd_temp_odr!=0)
                        {
                            state->dd_temp_odr=proposed_odr;
                            //sns_ddf_smgr_notify_event(state->smgr_handle, SNS_DDF_SENSOR_TEMP, SNS_DDF_EVENT_ODR_CHANGED); // SMGR will call get_attr(odr).
                        }
                    }
                    *odr=state->dd_press_odr=proposed_odr;
                }
                else //(sensor==SNS_DDF_SENSOR_TEMP)
                {
                    if (state->dd_press_odr!=0) // not allow TEMP change odr.
                    {
                        *odr=state->dd_temp_odr=state->dd_press_odr;
                    }
                    else    // state->dd_press_odr==0: allows TEMP change odr.
                    {
                        if (lps22hb_odr_code[odr_index]!=state->sensor_odr_code)
                        {
                            status = lps22hb_set_odr(state, lps22hb_odr_code[odr_index]);
                            state->sensor_odr_code = lps22hb_odr_code[odr_index];
                        }
                        *odr=state->dd_temp_odr=proposed_odr;
                    }
                }
            } //*odr!=0;
            DD_MSG_4(MED, "SetAttr(S%d, A%d), DesiredOdr=%d, SetOdr=%d", sensor, attrib, desired_odr, *odr);
            return status;
        }

        default:
        {
            DD_MSG_2(MED, "SetAttr(S%d, A%d). unsupported attribute.", sensor, attrib);
            return SNS_DDF_EINVALID_ATTR;
        }
    }
}

/**
 * @brief Implement enable_sched_data() DDF API.
 *
 * Refer to sns_ddf_driver_if.h for definition.
 */
sns_ddf_status_e sns_dd_lps22hb_enable_sched_data(
    sns_ddf_handle_t  dd_handle,
    sns_ddf_sensor_e  sensor,
    bool              enable)
{
    sns_ddf_status_e status = SNS_DDF_SUCCESS;
    sns_dd_lps22hb_state_t *state;
    uint32_t drdy;
    uint8_t reg[LPS22HB_NUM_BYTES_PRESS+LPS22HB_NUM_BYTES_TEMP];
    uint8_t rw_bytes;
    int driver_mode_old;

    DD_MSG_2(MED, "EnSchedData(S%d, E%d)", sensor, enable);
    if (dd_handle==NULL)
    {
        DD_MSG_0(ERROR, "\tdd_handle is NULL");
        return SNS_DDF_EINVALID_PARAM;
    }

    state=(sns_dd_lps22hb_state_t*)dd_handle;
    driver_mode_old = state->driver_mode;
    if (sensor==SNS_DDF_SENSOR__ALL)
    {
        if (enable) state->driver_mode|=LPS22HB_DRVMODE_bScheduleAll;
        else state->driver_mode&=~LPS22HB_DRVMODE_bScheduleAll;
    }
    else if (sensor==SNS_DDF_SENSOR_PRESSURE)
    {
        if (enable) state->driver_mode|=LPS22HB_DRVMODE_bSchedulePress;
        else state->driver_mode&=~LPS22HB_DRVMODE_bSchedulePress;
    }
    else //if (sensor==SNS_DDF_SENSOR_TEMP)
    {
        if (enable) state->driver_mode|=LPS22HB_DRVMODE_bScheduleTemp;
        else state->driver_mode&=~LPS22HB_DRVMODE_bScheduleTemp;
    }
    //status=LPS22HB_set_dri(state, (state->driver_mode&LPS22HB_DRVMODE_bScheduleAll));
    //if (status==SNS_DDF_SUCCESS)
    {
        DD_MSG_2(MED, "\tOldMode=%02Xh, NewMode=%02Xh", driver_mode_old, state->driver_mode);
        if (!(driver_mode_old&LPS22HB_DRVMODE_bScheduleAll) && (state->driver_mode&LPS22HB_DRVMODE_bScheduleAll))
        {
            status = sns_ddf_signal_gpio_read(state->gpio_num, &drdy);
            if (drdy) status=sns_dd_lps22hb_read_regs(LPS22HB_PRESS_OUT_XL, reg, LPS22HB_NUM_BYTES_PRESS+LPS22HB_NUM_BYTES_TEMP); // clear existing output buffer.
        	status = sns_ddf_signal_register(state->gpio_num, state, &sns_dd_press_lps22hb_if, SNS_DDF_SIGNAL_IRQ_RISING);
            if (status!=SNS_DDF_SUCCESS) return status;
            state->start_count = 0;
        }
        else if ((driver_mode_old&LPS22HB_DRVMODE_bScheduleAll) && !(state->driver_mode&LPS22HB_DRVMODE_bScheduleAll))
        {
            status = sns_ddf_signal_deregister(state->gpio_num);
        }
    }
    return status;
}

/** 
 * @brief Runs a factory test case.
 *
 * Refer to sns_ddf_driver_if.h for definition.
 */
sns_ddf_status_e sns_dd_lps22hb_run_test(
    sns_ddf_handle_t    dd_handle,
    sns_ddf_sensor_e    sensor_type,
    sns_ddf_test_e      test,
    uint32_t*           err)
{
    sns_dd_lps22hb_state_t* state;
    sns_ddf_status_e status;

    if (dd_handle==NULL)
    {
        DD_MSG_0(ERROR, "RunTest: dd_handle is NULL.");
        return SNS_DDF_EINVALID_PARAM;
    }

    DD_MSG_1(MED, "RunTest: %d.", test);
    state = (sns_dd_lps22hb_state_t*)dd_handle;
    if ((sensor_type!=SNS_DDF_SENSOR_PRESSURE) && (sensor_type!=SNS_DDF_SENSOR__ALL)) return SNS_DDF_EINVALID_PARAM;
    if (state->driver_mode&LPS22HB_DRVMODE_bPowerAll) return SNS_DDF_EDEVICE_BUSY;
    if (test==SNS_DDF_TEST_SELF)
    {
        uint8_t i2c_buff = 0;
        uint8_t rw_bytes;
        status=sns_dd_lps22hb_read_regs(LPS22HB_WHO_AM_I, &i2c_buff, 1);
        if(status != SNS_DDF_SUCCESS) return status;
        if(i2c_buff != LPS22HB_WHOAMI_VALUE) return SNS_DDF_EFAIL;
        return SNS_DDF_SUCCESS;
    }
    else if (test==SNS_DDF_TEST_SELF_SW)
    {
    	state->timer_type = LPS22HB_TIMER_SelfTest;
        // Start a timer for few ms here
        status = sns_ddf_timer_start(state->timer_obj, 10000);
        if(status != SNS_DDF_SUCCESS) return status;
        // Return pending
        return SNS_DDF_PENDING;
    }
    else
    {
        return SNS_DDF_EINVALID_TEST;
    }
}

void sns_dd_lps22hb_handle_timer(
    sns_ddf_handle_t dd_handle,
    void* arg)
{
    sns_dd_lps22hb_state_t* state=(sns_dd_lps22hb_state_t*)dd_handle;
    sns_ddf_status_e status;
    uint8_t i2c_buffer[LPS22HB_NUM_BYTES_PRESS];
    uint8_t rw_bytes;
    q16_t press[10], tmpt[10];
    int i, dup_count_p, dup_count_t;
    uint32_t err;

    DD_MSG_1(MED, "HandleTimer(): TimerType=%d", state->timer_type);
    if (state->timer_type == LPS22HB_TIMER_SelfTest)
    {
        err=STMERR_TEST_OK;

        // 1. Set LPS22HB to active mode, 75Hz ODR
        DD_MSG_0(MED, "1. Set sensor active.");
        i2c_buffer[0] = 0
                | (5<<4)        // ODR[2:0]: 0-1S/1S;1-1/1Hz;2-10/10;3-25/25;4-50/50;5-75/75;
                | (0<<3)        // EN_LPFP: 0-low pass filter disabled; 1-enabled.
                | (1<<2)        // LPF_CFG: 0-ODR/9; 1-ODR/20.
                | (1<<1)        // BDU
                | 0,            // SIM: 0-4 wire SPI; 1-3wire SPI.
        status=sns_dd_lps22hb_write_regs(LPS22HB_CTRL_REG1, i2c_buffer, 1);
        if (status!=SNS_DDF_SUCCESS)
        {
            err=STMERR_TEST_BUS_ERROR;
            sns_ddf_smgr_notify_test_complete(state->smgr_handle, SNS_DDF_SENSOR_PRESSURE, status, err);
            return;
        }

        // 2. Collect 10 samples for both pressure and temperature
        DD_MSG_0(MED, "2. Collect 10 samples.");
        for (i=0; i<10; i++)
        {
            sns_ddf_delay(15000);    // Wait 15ms for one sample ready.
            status=lps22hb_get_pt(dd_handle, &press[i], &tmpt[i]);
            if (status!=SNS_DDF_SUCCESS)
            {
                err=STMERR_TEST_BUS_ERROR;
                sns_ddf_smgr_notify_test_complete(state->smgr_handle, SNS_DDF_SENSOR_PRESSURE, status, err);
                return;
            }
            DD_MSG_4(MED, "P=%d.%dhPa, T=%d.%dC", Q16INT(press[i]), Q16DEC2(press[i]), Q16INT(tmpt[i]), Q16DEC2(tmpt[i]));
        }

        // 3. Analyze data.
        DD_MSG_0(MED, "3. Analyze data.");
        dup_count_p=dup_count_t=0;
        DD_MSG_2(MED, "P: ST MIN=%d, MAX=%d",Q16INT(LPS22HB_PRESS_ST_MIN), Q16INT(LPS22HB_PRESS_ST_MAX));
        DD_MSG_2(MED, "T: ST MIN=%d, MAX=%d",Q16INT(LPS22HB_TEMP_ST_MIN), Q16INT(LPS22HB_TEMP_ST_MAX));
        for (i=0;i<10;i++)
        {
            if ((press[i]<LPS22HB_PRESS_ST_MIN)||(press[i]>LPS22HB_PRESS_ST_MAX))
                err|=STMERR_TEST_SENSOR1_ST_FAIL;
            if ( (i>0) && (press[i]==press[i-1]) ) dup_count_p++;
            if ((tmpt[i]<LPS22HB_TEMP_ST_MIN)||(tmpt[i]>LPS22HB_TEMP_ST_MAX))
                err|=STMERR_TEST_SENSOR2_ST_FAIL;
            if ( (i>0) && (tmpt[i]==tmpt[i-1]) ) dup_count_t++;
        }
        if (dup_count_p>5) err|=STMERR_TEST_SENSOR1_ST_FAIL;
        if (dup_count_t>5) err|=STMERR_TEST_SENSOR2_ST_FAIL;

        // 4. restore CTRL_REG1 and put sensor power down.
        DD_MSG_0(MED, "4. Set sensor power down.");
        status=sns_dd_lps22hb_write_regs(LPS22HB_CTRL_REG1, &state->ctrl_reg1, 1);
        if (status!=SNS_DDF_SUCCESS)
        {
            err=STMERR_TEST_BUS_ERROR;
            sns_ddf_smgr_notify_test_complete(state->smgr_handle, SNS_DDF_SENSOR_PRESSURE, status, err);
            return;
        }
        if (err!=STMERR_TEST_OK) status = SNS_DDF_EFAIL;
        sns_ddf_smgr_notify_test_complete(state->smgr_handle, SNS_DDF_SENSOR_PRESSURE, status, err);
    }
    else
    {
    	DD_MSG_0(MED, "error timer type.");
    	return;
    }
    state->timer_type = LPS22HB_TIMER_Idle;
    return;
}

/** 
 * @brief Probe sensor.
 *
 * Refer to sns_ddf_driver_if.h for definition.
 */
sns_ddf_status_e sns_dd_lps22hb_probe(
    sns_ddf_device_access_s* device_info,
    sns_ddf_memhandler_s*    memhandler,
    uint32_t*                num_sensors,
    sns_ddf_sensor_e**       sensors )
{
    sns_ddf_status_e status;
    sns_ddf_handle_t port_handle;
    uint8_t reg;
    uint8_t rw_bytes;

    *num_sensors = 0;
    *sensors = NULL;

    status = sns_ddf_open_port(&port_handle, &(device_info->port_config));
    if (status!=SNS_DDF_SUCCESS)
    {
        return status;
    }

    /* Read & Verify Device ID */
    status = sns_ddf_read_port(port_handle, LPS22HB_WHO_AM_I, &reg, 1, &rw_bytes );

    if ((status!=SNS_DDF_SUCCESS) || (rw_bytes!=1))
    {
        sns_ddf_close_port(port_handle);
        return status;
    }
    if (reg!=LPS22HB_WHOAMI_VALUE)
    {
        /* Incorrect value. Return now with nothing detected */
        sns_ddf_close_port(port_handle);
        return SNS_DDF_EDEVICE;
    }

    /* Registers are correct. This is probably a LPS22HB */
    *num_sensors = 2;
    *sensors = sns_ddf_memhandler_malloc(memhandler, sizeof(sns_ddf_sensor_e) * *num_sensors);
    if (*sensors!=NULL)
    {
        (*sensors)[0] = SNS_DDF_SENSOR_PRESSURE;
        (*sensors)[1] = SNS_DDF_SENSOR_TEMP;
        status = SNS_DDF_SUCCESS;
    }
    else
    {
        status = SNS_DDF_ENOMEM;
    }
    sns_ddf_close_port(port_handle);
    return status;
}
