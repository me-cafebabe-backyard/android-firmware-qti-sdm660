/******************** (C) COPYRIGHT 2014 STMicroelectronics ********************
 *
 * File Name         : sns_dd_lis3mdl.c
 * Authors           : Karimuddin Sayed
 *                     Wei Wang
 * Version           : V 0.9.8
 * Date              : 04/02/2015
 * Description       : Magnetometer driver for ST sensors with WHO_AM_I=0x3D.
 *
 ********************************************************************************
 * Copyright (c) 2014, STMicroelectronics.
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
 * 0.9.8   | 04/02/2015    | Add DRI mode.
 *                           Add code to support LSM303C_MAG
 * 0.9.7   | 04/01/2015    | Update code for uImage.
 * 0.9.6   | 12/17/2014    | Updated according to Maansy's suggestion.
 * 0.9.5   | 11/20/2014    | Change LowPass to ODR.
 * 0.9.4   | 11/19/2014    | Correct ranges and self-test.
 * 0.9.3   | 11/18/2014    | Support uImage.
 * 0.9.2   | 09/25/2014    | Changed delay time back to 5 ms during init.
 *                           Tested on HD22-NK291-3_2.1.00.
 *                           Change LSM303C(M) to LIS3MDL.
 * 0.9.1   | 05/20/2014    | Add self test, probe, data log.
 * 0.9.0   | 12/17/2012    | Created.
 *******************************************************************************/
#include "sns_dd_lis3mdl.h"

extern sns_ddf_driver_if_s sns_dd_lis3mdl_if;

/**
 * Magnetometer MAG_LIS3MDL sampling frequencies array for getting attribute
 * frequencies are rounded to interger, such as using 2Hz to replace 1.5Hz.
 */
/*
static const sns_ddf_lowpass_freq_t lis3mdl_freqs[LIS3MDL_ODR_NUM]=
{
    FX_FLTTOFIX_Q16(0.625/2),
    FX_FLTTOFIX_Q16(1.25/2),
    FX_FLTTOFIX_Q16(2.5/2),
    FX_FLTTOFIX_Q16(5.0/2),
    FX_FLTTOFIX_Q16(10.0/2),
    FX_FLTTOFIX_Q16(20.0/2),
    FX_FLTTOFIX_Q16(40.0/2),
    FX_FLTTOFIX_Q16(80.0/2)
};
*/

static sns_ddf_odr_t lis3mdl_odr_hz[LIS3MDL_ODR_NUM] =
{
    1,
    1,
    2,
    5,
    10,
    20,
    40,
    80
};

/**
 * Magnetometer MAG_LIS3MDL min and max of ranges, converted to q16.
 */
#if defined (LSM303C_MAG)
    #define LIS3MDL_RANGE_NUM           1
    #define LIS3MDL_DEFAULT_RANGE_IDX   0   //+/-16Gauss
    static sns_ddf_range_s lis3mdl_range[LIS3MDL_RANGE_NUM]=
    {
        { FX_FLTTOFIX_Q16(-16.0),   FX_FLTTOFIX_Q16(16.0)   }
    };
    static q16_t lis3mdl_sstvt[LIS3MDL_RANGE_NUM]=
    {
//        FX_CONV_Q16((int32_t)1711, 0)    // +/-16Gauss
        (q16_t) (1711<<16)
    };
    static uint8_t lis3mdl_fs_code[LIS3MDL_RANGE_NUM]={3};
#else
    #define LIS3MDL_RANGE_NUM           4
    #define LIS3MDL_DEFAULT_RANGE_IDX   0   //+/-16Gauss
    static sns_ddf_range_s lis3mdl_range[LIS3MDL_RANGE_NUM]=
    {
        { FX_FLTTOFIX_Q16(-4.0),    FX_FLTTOFIX_Q16(4.0)    },
        { FX_FLTTOFIX_Q16(-8.0),    FX_FLTTOFIX_Q16(8.0)    },
        { FX_FLTTOFIX_Q16(-12.0),   FX_FLTTOFIX_Q16(12.0)   },
        { FX_FLTTOFIX_Q16(-16.0),   FX_FLTTOFIX_Q16(16.0)   }
    };
    static q16_t lis3mdl_sstvt[LIS3MDL_RANGE_NUM]=
    {
        //FX_CONV_Q16((int32_t)6842, 0),   // +/-4Gauss
        //FX_CONV_Q16((int32_t)3421, 0),   // +/-8Gauss
        //FX_CONV_Q16((int32_t)2281, 0),   // +/-12Gauss
        //FX_CONV_Q16((int32_t)1711, 0)    // +/-16Gauss
        (q16_t) (6842<<16),
        (q16_t) (3421<<16),
        (q16_t) (2281<<16),
        (q16_t) (1711<<16)
    };
    static uint8_t lis3mdl_fs_code[LIS3MDL_RANGE_NUM]={0, 1, 2, 3};
#endif


/**
 * @brief Resets the driver and device so they return to the state they were
 *        in after init() was called.
 *
 * Refer to sns_ddf_driver_if.h for definition.
 */
sns_ddf_status_e sns_dd_lis3mdl_reset(sns_ddf_handle_t dd_handle)
{
    sns_dd_lis3mdl_state_t* state=(sns_dd_lis3mdl_state_t*)dd_handle;
    sns_ddf_status_e status;
    uint8_t reg[5];
    uint8_t rw_bytes;

    reg[0]=0x0		// CTRL_REG1
        | (0<<7)		// TEMP_EN: must be 0.
        | (3<<5)        // OM[1:0]: 0-X/Y low power; 1-medium power; 2-high performance; 3-ultra high performance.
        | (LIS3MDL_DEFAULT_ODR_IDX<<2)	// DO[2:1]: 0-0.625Hz; 1-1.25; 2-2.5; 3-5; 4-10; 5-20; 6-40; 7-80.
        | 0;            // ST: 0-self-test disabled; 1-enabled.

    reg[1]=0x0		// CTRL_REG2
        | (lis3mdl_fs_code[LIS3MDL_DEFAULT_RANGE_IDX]<<5)	// FS[1:0]: 0-4Gauss; 1-8; 2-12; 3-16
        | (0<<3)		// REBOOT:
        | (0<<2);       // SOFT_RST:

    reg[2]=0x0		// CTRL_REG3
        | (0<<5)        // LP bit low power mode
        | (0<<2)		// SIM
        | 3;            // MD[1:0]: 0-Continuous; 1-Single; 2,3-Power Down.

    reg[3]=0x0		// CTRL_REG4
        | (3<<2)        // OMZ[1:0]: 0-Z low power; 1-medium power; 2-high performance; 3-ultra high performance.
        | (0<<1);		// BLE: 0-little endian; 1-big endian.

    reg[4]=0x0		// CTRL_REG5
        | (1<<6);       // BDU

    status=sns_dd_lis3mdl_write_regs(AUTO_INCREMENT|LIS3MDL_REG_CNTRL1, reg, 5);
    if (status!=SNS_DDF_SUCCESS) return status;

    sns_ddf_delay(1000);	// Let configuration values settle in by waiting 1 ms.

    state->ctrl_reg1=reg[0];
    state->dd_mag_odr=0;
    state->current_range_idx=LIS3MDL_DEFAULT_RANGE_IDX;
    state->power_state=SNS_DDF_POWERSTATE_LOWPOWER;
    state->sstvt=lis3mdl_sstvt[LIS3MDL_DEFAULT_RANGE_IDX];
    state->self_test_enable=false;
    return SNS_DDF_SUCCESS;
}

/**
 * @brief Performs a set data sampling rate operation
 *
 * @param[in]  dd_handle      Handle to a driver instance.
 * @param[in]  data_rate       Data sampling rate settings for MAG_LIS3MDL
 *
 * @return SNS_DDF_SUCCESS if this operation was done successfully. Otherwise
 *         SNS_DDF_EDEVICE, SNS_DDF_EBUS, SNS_DDF_EINVALID_PARAM, or SNS_DDF_EFAIL to
 *         indicate and error has occurred.
 */
static sns_ddf_status_e lis3mdl_set_odr(sns_dd_lis3mdl_state_t* state, uint8_t odr_idx)
{
    sns_ddf_status_e status;
    uint8_t reg, rw_bytes;
    if (odr_idx>7) return SNS_DDF_EINVALID_PARAM;
    reg=(state->ctrl_reg1&0xE3)|(odr_idx<<2);   // Configure ODR bits in CNTRL1.
    status=sns_dd_lis3mdl_write_regs(LIS3MDL_REG_CNTRL1, &reg, 1);
    if (status!=SNS_DDF_SUCCESS) return status;
    state->ctrl_reg1=reg;
    sns_ddf_delay(5000);	// Let ODR value settle in by waiting 5 ms.
    return SNS_DDF_SUCCESS;
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
static sns_ddf_status_e lis3mdl_set_power(
    sns_dd_lis3mdl_state_t* state,
    sns_ddf_powerstate_e power_state)
{
    sns_ddf_status_e status;
    uint8_t reg;
    uint8_t rw_bytes;

    if ((SNS_DDF_POWERSTATE_LOWPOWER==power_state)
      &&(SNS_DDF_POWERSTATE_ACTIVE==state->power_state))
    {
        reg=0x0             // CTRL_REG3
            | (0<<5)        // LP bit low power mode
            | (0<<2)        // SIM
            | 3;            // MD[1:0]: 0-Continuous; 1-Single; 2,3-Power Down.
        status=sns_dd_lis3mdl_write_regs(LIS3MDL_REG_CNTRL3, &reg, 1);
        if (status!=SNS_DDF_SUCCESS) return status;
        state->power_state=SNS_DDF_POWERSTATE_LOWPOWER;
    }
    else if ((SNS_DDF_POWERSTATE_ACTIVE==power_state)
           &&(SNS_DDF_POWERSTATE_LOWPOWER==state->power_state))
    {
        reg=0x0             // CTRL_REG3
            | (0<<5)        // LP bit low power mode
            | (0<<2)        // SIM
            | 0;            // MD[1:0]: 0-Continuous; 1-Single; 2,3-Power Down.
        status=sns_dd_lis3mdl_write_regs(LIS3MDL_REG_CNTRL3, &reg, 1);
        if (status!=SNS_DDF_SUCCESS) return status;
        sns_ddf_delay(5000);    // Let register value settle in by waiting 5 ms.
        state->power_state=SNS_DDF_POWERSTATE_ACTIVE;
    }
    return SNS_DDF_SUCCESS;
}

/**
 * @brief Performs a set dynamic range operation
 *
 * @param[in]  dd_handle      Handle to a driver instance.
 * @param[in]  range          Dynamic range settings for MAG_LIS3MDL
 *
 * @return SNS_DDF_SUCCESS if this operation was done successfully. Otherwise
 *         SNS_DDF_EDEVICE, SNS_DDF_EBUS, SNS_DDF_EINVALID_PARAM, or SNS_DDF_EFAIL to
 *         indicate and error has occurred.
 */
static sns_ddf_status_e lis3mdl_set_range(sns_dd_lis3mdl_state_t* state, uint8_t range_idx)
{
    sns_ddf_status_e status;
    uint8_t reg;
    uint8_t rw_bytes;
    if (range_idx>=LIS3MDL_RANGE_NUM) return SNS_DDF_EINVALID_PARAM;
    reg=lis3mdl_fs_code[range_idx]<<5;
    status=sns_dd_lis3mdl_write_regs(LIS3MDL_REG_CNTRL2, &reg, 1);
    state->sstvt=lis3mdl_sstvt[range_idx];
    sns_ddf_delay(5000); // Let dynamic range value settle in by waiting 5 ms.
    return status;
}

/**
 * @brief Initializes the mag_lis3mdl driver and sets up sensor.
 *
 * Refer to sns_ddf_driver_if.h for definition.
 */
sns_ddf_status_e sns_dd_lis3mdl_init(
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
    sns_dd_lis3mdl_state_t* state;
    uint8_t reg = 0;
    uint8_t rw_bytes;
    static sns_ddf_sensor_e my_sensors[] = {SNS_DDF_SENSOR_MAG};

    LIS3MDL_MSG_0(MED, "Init:");

#if defined(BUILD_UIMAGE)
    /* Update smgr sensor data for the driver to indicate uImage support */
    sns_ddf_smgr_set_uimg_refac(smgr_handle);
#endif

    // Allocate a driver instance.
    status = sns_dd_malloc((void**)&state, sizeof(sns_dd_lis3mdl_state_t), smgr_handle);
    if (status!=SNS_DDF_SUCCESS) return SNS_DDF_ENOMEM;
    memset(state, 0x0, sizeof(sns_dd_lis3mdl_state_t));
    *dd_handle_ptr = state;
    state->smgr_handle = smgr_handle;
    state->gpio_num = device_info->first_gpio;
    state->last_irq_timestamp = 0;
    state->enable_sched_data = 0;

    // Open communication port to the device.
    status = sns_ddf_open_port(&state->port_handle, &device_info->port_config);
    if (status!=SNS_DDF_SUCCESS)
    {
        LIS3MDL_MSG_0(ERROR, "Init: can't open i2c.");
        sns_dd_mfree(state, smgr_handle);
        return status;
    }

    // wait sensor powering up to be ready by delaying 5 ms.
    //sns_ddf_delay(5000);
    status = sns_dd_lis3mdl_read_regs(LIS3MDL_REG_WHOAMI, &reg, 1);
    if (status!=SNS_DDF_SUCCESS)
    {
        LIS3MDL_MSG_0(MED, "Init: can't open device.");
        sns_ddf_close_port(state->port_handle);
        sns_dd_mfree(state, smgr_handle);
        return status;
    }

    if (reg!=LIS3MDL_WHO_AM_I)
    {
        LIS3MDL_MSG_1(ERROR, "Init: WhoAmI=%d",reg);
        sns_ddf_close_port(state->port_handle);
        sns_dd_mfree(state, smgr_handle);
        return SNS_DDF_EFAIL;
    }

    reg=0x04;   // SOFT_RST
    status = sns_dd_lis3mdl_write_regs(LIS3MDL_REG_CNTRL2, &reg, 1);
    if (status!=SNS_DDF_SUCCESS) return status;
    sns_ddf_delay(1000);

    // Resets the mag_lis3mdl
    status = sns_dd_lis3mdl_reset(state);
    if (status!=SNS_DDF_SUCCESS)
    {
        LIS3MDL_MSG_0(ERROR, "Init: can't reset device.");
        sns_ddf_close_port(state->port_handle);
        sns_dd_mfree(state, smgr_handle);
        return status;
    }

    sns_ddf_axes_map_init(&state->axes_map, ((nv_params!=NULL)?nv_params->data:NULL));

    // Set timer for run_test()
    status = sns_ddf_timer_init(&state->timer_obj,
                              state,
                              &sns_dd_lis3mdl_if,
                              state, //always return dd_handle_ptr
                              false); // not periodic
    if (status!=SNS_DDF_SUCCESS)
    {
        LIS3MDL_MSG_0(ERROR, "Init: timer error.");
        sns_ddf_close_port(state->port_handle);
        sns_dd_mfree(state, smgr_handle);
        return status;
    }

    // Fill out output parameters.
    *num_sensors = 1;
    *sensors = my_sensors;
    LIS3MDL_MSG_0(MED, "Init: succeed.");
    return SNS_DDF_SUCCESS;
}

/**
 * @brief Retrieves the value of an attribute for a mag_lis3mdl sensor.
 *
 * Refer to sns_ddf_driver_if.h for definition.
 */
sns_ddf_status_e sns_dd_lis3mdl_get_attr(
    sns_ddf_handle_t dd_handle,
    sns_ddf_sensor_e sensor,
    sns_ddf_attribute_e attrib,
    sns_ddf_memhandler_s* memhandler,
    void** value,
    uint32_t* num_elems)
{
    sns_dd_lis3mdl_state_t* state;
    LIS3MDL_MSG_2(HIGH, "GetAttr(S%d, A%d):", sensor, attrib);
    if (dd_handle==NULL || value==NULL)
    {
        LIS3MDL_MSG_0(ERROR, "GetAttr: dd_handle is NULL");
        return SNS_DDF_EINVALID_PARAM;
    }

    state=(sns_dd_lis3mdl_state_t*)dd_handle;
    if (state->smgr_handle==NULL) return SNS_DDF_EINVALID_PARAM;
    if ((sensor!=SNS_DDF_SENSOR_MAG)&&(sensor!=SNS_DDF_SENSOR__ALL)) return SNS_DDF_EINVALID_PARAM;
    switch(attrib)
    {
        case SNS_DDF_ATTRIB_POWER_INFO:
        {
            sns_ddf_power_info_s *power;
            power = sns_dd_memhandler_malloc(memhandler, sizeof(sns_ddf_power_info_s), state->smgr_handle);
            if (NULL==power) return SNS_DDF_ENOMEM;
            //current consumption, unit uA
            power->active_current = 270;
            power->lowpower_current = 6;
            *value = power;
            *num_elems = 1;
            return SNS_DDF_SUCCESS;
          }

        case SNS_DDF_ATTRIB_RANGE:
        {
            //sns_ddf_range_s *ranges;
            //int i;
            //ranges = sns_dd_memhandler_malloc(memhandler, LIS3MDL_RANGE_NUM*sizeof(sns_ddf_range_s), state->smgr_handle);
            //if (NULL==ranges) return SNS_DDF_ENOMEM;
            //for (i=0; i<LIS3MDL_RANGE_NUM; i++) ranges[i]=lis3mdl_range[i];
            *num_elems = LIS3MDL_RANGE_NUM;
            *value = lis3mdl_range;
            return SNS_DDF_SUCCESS;
        }

        case SNS_DDF_ATTRIB_RESOLUTION:
        {
            sns_ddf_resolution_t *res;
            res = sns_dd_memhandler_malloc(memhandler ,sizeof(sns_ddf_resolution_t), state->smgr_handle);
            if (NULL==res) return SNS_DDF_ENOMEM;
            *res = FX_DIV_Q16(FX_CONV_Q16((int32_t)1,0), FX_CONV_Q16((int32_t)(state->sstvt),0));
            *value = res;
            *num_elems = 1;
            return SNS_DDF_SUCCESS;
        }

        case SNS_DDF_ATTRIB_RESOLUTION_ADC:
        {
            sns_ddf_resolution_adc_s *device_res;
            device_res=sns_dd_memhandler_malloc(memhandler, sizeof(sns_ddf_resolution_adc_s), state->smgr_handle);
            if (NULL==device_res)  return SNS_DDF_ENOMEM;
            device_res->bit_len = LIS3MDL_SENSOR_BIT_LEN;
            device_res->max_freq = LIS3MDL_MAX_ODR_Hz;
            *value = device_res;
            *num_elems = 1;
            return SNS_DDF_SUCCESS;
        }
/*
        case SNS_DDF_ATTRIB_LOWPASS:
        {
            *value = lis3mdl_freqs;
            *num_elems = LIS3MDL_ODR_NUM;
            return SNS_DDF_SUCCESS;
        }
*/
        case SNS_DDF_ATTRIB_ODR:
        {
            *(sns_ddf_odr_t**)value = &state->dd_mag_odr;
            *num_elems = 1;
            LIS3MDL_MSG_1(MED, "CurrentOdr=%d.", state->dd_mag_odr);
            return SNS_DDF_SUCCESS;
        }

        case SNS_DDF_ATTRIB_SUPPORTED_ODR_LIST:
        {
            *value = lis3mdl_odr_hz;
            *num_elems = LIS3MDL_ODR_NUM;
            return SNS_DDF_SUCCESS;
        }

        case SNS_DDF_ATTRIB_DELAYS:
        {
            sns_ddf_delays_s *mag_lis3mdl_delays;
            mag_lis3mdl_delays = sns_dd_memhandler_malloc(memhandler, sizeof(sns_ddf_delays_s), state->smgr_handle);
            if (NULL==mag_lis3mdl_delays) return SNS_DDF_ENOMEM;
            mag_lis3mdl_delays->time_to_active = 5;
            mag_lis3mdl_delays->time_to_data = 1;
            *value = mag_lis3mdl_delays;
            *num_elems = 1;
            return SNS_DDF_SUCCESS;
        }

        case SNS_DDF_ATTRIB_DRIVER_INFO:
        {
            sns_ddf_driver_info_s *info;
            info = sns_dd_memhandler_malloc(memhandler,sizeof(sns_ddf_driver_info_s), state->smgr_handle);
            if (NULL==info) return SNS_DDF_ENOMEM;
            info->name = "STM LIS3MDL Magnetometer Driver";
            info->version = 1;
            *value = info;
            *num_elems = 1;
            return SNS_DDF_SUCCESS;
        }

        case SNS_DDF_ATTRIB_DEVICE_INFO:
        {
            sns_ddf_device_info_s *info;
            info = sns_dd_memhandler_malloc(memhandler, sizeof(sns_ddf_device_info_s), state->smgr_handle);
            if (NULL==info) return SNS_DDF_ENOMEM;
            info->name = "Magnetometer";
            info->vendor = "STMicroelectronics";
            info->model = DEVICE_NAME;
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
 * @brief Sets a mag_lis3mdl sensor attribute to a specific value.
 *
 * Refer to sns_ddf_driver_if.h for definition.
 */
sns_ddf_status_e sns_dd_lis3mdl_set_attr(
    sns_ddf_handle_t dd_handle,
    sns_ddf_sensor_e sensor,
    sns_ddf_attribute_e attrib,
    void* value)
{
    sns_dd_lis3mdl_state_t* state;
    if (dd_handle==NULL || value==NULL)
    {
        LIS3MDL_MSG_0(ERROR, "SetAttr: dd_handle is NULL");
        return SNS_DDF_EINVALID_PARAM;
    }

    state=(sns_dd_lis3mdl_state_t*)dd_handle;
    if ((sensor!=SNS_DDF_SENSOR_MAG)&&(sensor!=SNS_DDF_SENSOR__ALL)) return SNS_DDF_EINVALID_PARAM;
    switch(attrib)
    {
        case SNS_DDF_ATTRIB_POWER_STATE:
        {
            sns_ddf_powerstate_e* power_state = value;
            LIS3MDL_MSG_2(MED, "SetAttr(%d): PowerState=%d.", attrib, *power_state);
            return lis3mdl_set_power(state, *power_state);
        }
        case SNS_DDF_ATTRIB_RANGE:
        {
            uint8_t range_idx = *(uint8_t*)value;
            sns_ddf_status_e status=SNS_DDF_SUCCESS;
            if (range_idx!=state->current_range_idx) status=lis3mdl_set_range(state, range_idx);
            LIS3MDL_MSG_2(MED, "SetAttr(%d): RangeIdx=%d.", attrib, range_idx);
            return status;
        }
        case SNS_DDF_ATTRIB_ODR:
        {
            int i;
            sns_ddf_status_e status;
            sns_ddf_odr_t desired_odr=*(sns_ddf_odr_t*)value;
            if (desired_odr==state->dd_mag_odr)
            {
                status=SNS_DDF_SUCCESS;
            }
            else if (desired_odr==0)
            {
                state->dd_mag_odr=0;
                status=SNS_DDF_SUCCESS;
            }
            else
            {
                for (i=0; i<LIS3MDL_ODR_NUM; i++)
                    if (desired_odr<=lis3mdl_odr_hz[i]) break;
                if (i>=LIS3MDL_ODR_NUM) i=LIS3MDL_ODR_NUM-1;
                state->dd_mag_odr=lis3mdl_odr_hz[i];
                status=lis3mdl_set_odr(state, i);
            }
            LIS3MDL_MSG_3(MED, "SetAttr(%d): DesiredOdr=%d, SetOdr=%d.", attrib, desired_odr, state->dd_mag_odr);
            return status;
        }
        default:
        {
            LIS3MDL_MSG_1(MED, "SetAttr(%d).", attrib);
            return SNS_DDF_EINVALID_ATTR;
        }
    }
}


/**
 * @brief Implement enable_sched_data() DDF API.
 *
 * Refer to sns_ddf_driver_if.h for definition.
 */
sns_ddf_status_e sns_dd_lis3mdl_enable_sched_data(
    sns_ddf_handle_t  dd_handle,
    sns_ddf_sensor_e  sensor,
    bool              enable)
{
    sns_ddf_status_e status;
    sns_dd_lis3mdl_state_t *state;
    uint32_t drdy;
    uint8_t reg[6];
    uint8_t rw_bytes;

    LIS3MDL_MSG_2(MED, "EnableSchedData(S%d): enable=%d", sensor, enable);
    if ((dd_handle==NULL)||((sensor!=SNS_DDF_SENSOR_MAG)&&(sensor!=SNS_DDF_SENSOR__ALL)))
    {
        LIS3MDL_MSG_0(ERROR, "dd_handle is NULL");
        return SNS_DDF_EINVALID_PARAM;
    }
    state=(sns_dd_lis3mdl_state_t*)dd_handle;
    state->enable_sched_data = enable;
    if (enable)
    {
        status = sns_ddf_signal_register(state->gpio_num, state, &sns_dd_lis3mdl_if, SNS_DDF_SIGNAL_IRQ_RISING);
        if (status!=SNS_DDF_SUCCESS) return status;
        status = sns_ddf_signal_gpio_read(state->gpio_num, &drdy);
        if (drdy) status=sns_dd_lis3mdl_read_regs(LIS3MDL_OUT_X_L, reg, 6); // clear existing output buffer.
    }
    else
    {
        status = sns_ddf_signal_deregister(state->gpio_num);
    }
    return status;
}

/**
 * @brief Runs a factory test case.
 *
 * Refer to sns_ddf_driver_if.h for definition.
 */
sns_ddf_status_e sns_dd_lis3mdl_run_test
(
    sns_ddf_handle_t    dd_handle,
    sns_ddf_sensor_e    sensor_type,
    sns_ddf_test_e      test,
    uint32_t*           err
)
{
    sns_dd_lis3mdl_state_t* state;
    sns_ddf_status_e status;
    uint8_t reg = 0;
    uint8_t rw_bytes;

    LIS3MDL_MSG_2(MED, "RunTest(S%d, T%d):", sensor_type, test);
    if (dd_handle==NULL)
    {
        LIS3MDL_MSG_0(ERROR, "RunTest: dd_handle is NULL");
        return SNS_DDF_EINVALID_PARAM;
    }
    state = (sns_dd_lis3mdl_state_t*)dd_handle;
    if (state->power_state==SNS_DDF_POWERSTATE_ACTIVE) return SNS_DDF_EDEVICE_BUSY;

    if ((sensor_type!=SNS_DDF_SENSOR_MAG) && (sensor_type!=SNS_DDF_SENSOR__ALL)) return SNS_DDF_EINVALID_PARAM;
    if (SNS_DDF_POWERSTATE_ACTIVE==state->power_state) return SNS_DDF_EDEVICE_BUSY;
    if (test==SNS_DDF_TEST_SELF)
    {
        status = sns_dd_lis3mdl_read_regs(LIS3MDL_REG_WHOAMI, &reg, 1);
        if (status!=SNS_DDF_SUCCESS) return status;
        if (reg!=LIS3MDL_WHO_AM_I) return SNS_DDF_EFAIL;
        return SNS_DDF_SUCCESS;
    }
    else if (test==SNS_DDF_TEST_SELF_HW)
    {
        state->self_test_enable = true;
        status = sns_ddf_timer_start(state->timer_obj, 10000);  // Start a timer for few ms here
        if (status!=SNS_DDF_SUCCESS) return status;
        return SNS_DDF_PENDING;
    }
    else
    {
        return SNS_DDF_EINVALID_TEST;
    }
}

/**
 * @brief Probe MAG_LIS3MDL.
 *
 * Refer to sns_ddf_driver_if.h for definition.
 */
sns_ddf_status_e sns_dd_lis3mdl_probe(
    sns_ddf_device_access_s* device_info,
    sns_ddf_memhandler_s*    memhandler,
    uint32_t*                num_sensors,
    sns_ddf_sensor_e**       sensors )
{
    sns_ddf_status_e status;
    sns_ddf_handle_t port_handle;
    uint8_t i2c_buff = 0;
    uint8_t bytes_read;

    *num_sensors = 0;
    *sensors = NULL;

    status = sns_ddf_open_port(&port_handle, &(device_info->port_config));
    if (status!=SNS_DDF_SUCCESS) return status;

    /* Read & Verify Device ID */
    status = sns_ddf_read_port( port_handle,
                              LIS3MDL_REG_WHOAMI,
                              &i2c_buff,
                              1,
                              &bytes_read );

    if (status!=SNS_DDF_SUCCESS || bytes_read!=1)
    {
        sns_ddf_close_port( port_handle );
        return status;
    }

    if (i2c_buff!=LIS3MDL_WHO_AM_I)
    {
        /* Incorrect value. Return now with nothing detected */
        sns_ddf_close_port( port_handle );
        return SNS_DDF_SUCCESS;
    }

    /* Registers are correct. This is probably a MAG_LIS3MDL */
    *num_sensors = 1;
    *sensors = sns_ddf_memhandler_malloc( memhandler, sizeof(sns_ddf_sensor_e) * *num_sensors);
    if (*sensors!=NULL )
    {
        (*sensors)[0] = SNS_DDF_SENSOR_MAG;
        status = SNS_DDF_SUCCESS;
    }
    else
    {
        status = SNS_DDF_ENOMEM;
    }
    sns_ddf_close_port( port_handle );
    return status;
}

void sns_dd_lis3mdl_handle_timer(sns_ddf_handle_t dd_handle, void* arg)
{
    sns_dd_lis3mdl_state_t* state=(sns_dd_lis3mdl_state_t*)dd_handle;
    sns_ddf_status_e status = SNS_DDF_ELAST;
    uint8_t ctrlregs[5];
    uint8_t regs[6] = {0};
    uint8_t rw_bytes;
    int32_t mag_mG[3], mag_sum[3];
    uint32_t err;
    int i;

    if (dd_handle==NULL)
    {
        LIS3MDL_MSG_0(ERROR, "HandleTimer: dd_handle is NULL");
        return;
    }

    if (!state->self_test_enable) return;

    while (state->self_test_enable)
    {
        state->self_test_enable=false;
        err=STMERR_TEST_UNKNOWN;

        // 1.Backup control registers.
        status=sns_dd_lis3mdl_read_regs(AUTO_INCREMENT|LIS3MDL_REG_CNTRL1, ctrlregs, 5);
        if (status!=SNS_DDF_SUCCESS) break;

        // 2.Set control registers for self test.
        regs[0]=0x1D;
        status=sns_dd_lis3mdl_write_regs(LIS3MDL_REG_CNTRL1, regs, 1);
        if (status!=SNS_DDF_SUCCESS) break;

        regs[0]=0x40;
        status=sns_dd_lis3mdl_write_regs(LIS3MDL_REG_CNTRL2, regs, 1);
        if (status!=SNS_DDF_SUCCESS) break;

        regs[0]=0x00;
        status=sns_dd_lis3mdl_write_regs(LIS3MDL_REG_CNTRL4, regs, 1);
        if (status!=SNS_DDF_SUCCESS) break;

        sns_ddf_delay(20000);       //20ms

        regs[0]=0x00;
        status=sns_dd_lis3mdl_write_regs(LIS3MDL_REG_CNTRL3, regs, 1);
        if (status!=SNS_DDF_SUCCESS) break;

        // 3.Wait 20ms, read data, and abandon first reading.
        sns_ddf_delay(20000);       //20ms
        status=sns_dd_lis3mdl_read_regs(AUTO_INCREMENT|LIS3MDL_OUT_X_L, regs, 6);
        if (status!=SNS_DDF_SUCCESS) break;

        // 4.Collect 5 sample, average them.
        mag_sum[0]=mag_sum[1]=mag_sum[2]=0;
        for (i=0; i<5; i++)
        {
            sns_ddf_delay(20000);       //20ms
            status=sns_dd_lis3mdl_read_regs(AUTO_INCREMENT|LIS3MDL_OUT_X_L, regs, 6);
            if (status!=SNS_DDF_SUCCESS) break;
            mag_mG[0]=(int32_t)((int16_t)((regs[1]<<8)|regs[0]))*1000/2281;
            mag_mG[1]=(int32_t)((int16_t)((regs[3]<<8)|regs[2]))*1000/2281;
            mag_mG[2]=(int32_t)((int16_t)((regs[5]<<8)|regs[4]))*1000/2281;
            LIS3MDL_MSG_3(MED, "RunTest: %d, %d, %dmGauss.", mag_mG[0], mag_mG[1], mag_mG[2]);
            mag_sum[0]+=mag_mG[0];
            mag_sum[1]+=mag_mG[1];
            mag_sum[2]+=mag_mG[2];
        }
        if (status!=SNS_DDF_SUCCESS) break;
        for (i=0;i<3;i++) mag_mG[i]=mag_sum[i]/5;
        LIS3MDL_MSG_3(MED, "RunTest: %d, %d, %dmGauss.", mag_mG[0], mag_mG[1], mag_mG[2]);

        // 5.Check if data is within range.
        for (i=0;i<3;i++) if (mag_mG[i]<0) mag_mG[i]=-mag_mG[i];
        if ((1000<=mag_mG[0])&&(mag_mG[0]<=3000)&&
            (1000<=mag_mG[1])&&(mag_mG[1]<=3000)&&
            (100<=mag_mG[2])&&(mag_mG[2]<=1000))
          err=STMERR_TEST_OK;
        else
          err=STMERR_TEST_SENSOR1_ST_FAIL;

        // 6.Restore control registers.
        status=sns_dd_lis3mdl_write_regs(AUTO_INCREMENT|LIS3MDL_REG_CNTRL1, ctrlregs, 5);
        break;
    }
    if (status!=SNS_DDF_SUCCESS) err=STMERR_TEST_BUS_ERROR;
    else if (err!=STMERR_TEST_OK) status=SNS_DDF_EFAIL;
    sns_ddf_smgr_notify_test_complete(state->smgr_handle, SNS_DDF_SENSOR_MAG, status, err);
    return;
}



