/******************** (C) COPYRIGHT 2016 STMicroelectronics ********************
*
* File Name         : sns_dd_lps22hb_uimg.c
* Authors           : Wei Wang
* Version           : V 1.3.0
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
*******************************************************************************/

#include "sns_dd_press_lps22hb.h"

/**
 * @brief Log data packets
 *
 * @param[in]  sensor      Sensor ID
 * @param[in]  data        Data to log
 * @param[in]  timestamp   Timestamp of data
 */
void lps22hb_log_data(sns_ddf_sensor_e sensor, q16_t data, sns_ddf_time_t timestamp)
{
    sns_err_code_e status;
    sns_log_sensor_data_pkt_s* log;

    status = sns_logpkt_malloc(
        SNS_LOG_CONVERTED_SENSOR_DATA,
        sizeof(sns_log_sensor_data_pkt_s),
        (void**)&log);
    if ( (status==SNS_SUCCESS) && (log!=NULL) )
    {
        log->version = SNS_LOG_SENSOR_DATA_PKT_VERSION;
        log->sensor_id = sensor;
        log->vendor_id = SNS_DDF_VENDOR_STMICRO;
        log->timestamp = timestamp;
        log->end_timestamp = timestamp;
        log->num_data_types = 1;
        log->data[0] = data;
        sns_logpkt_commit(SNS_LOG_CONVERTED_SENSOR_DATA, log);
    }
}

sns_ddf_status_e lps22hb_get_pt(sns_dd_lps22hb_state_t* state, q16_t* press, q16_t* tmpt)
{
    sns_ddf_status_e status;
    uint8_t reg[LPS22HB_NUM_BYTES_PRESS+LPS22HB_NUM_BYTES_TEMP];
    uint8_t rw_bytes;
    status=sns_dd_lps22hb_read_regs(LPS22HB_PRESS_OUT_XL, reg, LPS22HB_NUM_BYTES_PRESS+LPS22HB_NUM_BYTES_TEMP);
    if (status!=SNS_DDF_SUCCESS) return status;
    *press=((reg[2]<<16)|(reg[1]<<8)|reg[0])<<4;
    *tmpt=FX_DIV_Q16(FX_CONV_Q16(((reg[4]<<8)|reg[3]),0), FX_CONV_Q16((int32_t)100,0));
    return status;
}

/** 
 * @brief Retrieves a single set of pressure and/or temperature data from lps25h
 *  
 * Refer to sns_ddf_driver_if.h for definition.
 */
sns_ddf_status_e sns_dd_lps22hb_get_data(
    sns_ddf_handle_t dd_handle,
    sns_ddf_sensor_e sensors[],
    uint32_t num_sensors,
    sns_ddf_memhandler_s* memhandler,
    sns_ddf_sensor_data_s** data)
{
    uint8_t i;
    q16_t press, tmpt;
    sns_ddf_time_t timestamp;
    sns_ddf_status_e status;
    sns_ddf_sensor_data_s *data_ptr;
    sns_dd_lps22hb_state_t *state;

    if (dd_handle==NULL || data==NULL)
    {
        DD_MSG_0(ERROR, "GetData: dd_handle is NULL");
        return SNS_DDF_EINVALID_PARAM;
    }

    state = (sns_dd_lps22hb_state_t*)dd_handle;

    //if current power mode is LOWPOWER , return error.
//    if(!(state->driver_mode&LPS22HB_DRVMODE_bPowerAll) || (num_sensors>2) )
//        return SNS_DDF_EDEVICE;
    
    //allocate memory for sns_ddf_sensor_data_s data structure
    data_ptr = sns_dd_memhandler_malloc(memhandler, num_sensors*sizeof(sns_ddf_sensor_data_s), state->smgr_handle);
    if (NULL==data_ptr) return SNS_DDF_ENOMEM;
    *data = data_ptr;
    timestamp = sns_ddf_get_timestamp();    // get current time stamp
    status=lps22hb_get_pt(state, &press, &tmpt);  // This is a synchronous driver, so try to read data now.
    if (status!=SNS_DDF_SUCCESS) return status;
    for (i=0; i<num_sensors; i++)
    {
        data_ptr[i].sensor = sensors[i];
        data_ptr[i].status = SNS_DDF_SUCCESS;
        data_ptr[i].timestamp = timestamp;
    
        //allocate memory for data samples.
        data_ptr[i].samples = sns_dd_memhandler_malloc(memhandler, sizeof(sns_ddf_sensor_sample_s), state->smgr_handle);
        if (NULL==data_ptr[i].samples) return SNS_DDF_ENOMEM;

        if (sensors[i]==SNS_DDF_SENSOR_PRESSURE)
        {
            data_ptr[i].samples->sample = press;
            DD_MSG_2(MED, "GetData: P=%d.%dhPa", Q16INT(press), Q16DEC3(press));
        }
        else
        {
            data_ptr[i].samples->sample = tmpt;
            DD_MSG_2(MED, "GetData: T=%d.%dC", Q16INT(tmpt), Q16DEC3(tmpt));
        }
        data_ptr[i].samples->status = SNS_DDF_SUCCESS;
        data_ptr[i].num_samples = 1;

        // Log sensor data
        lps22hb_log_data(data_ptr[i].sensor, data_ptr[i].samples->sample, data_ptr[i].timestamp);
    }
    
    return SNS_DDF_SUCCESS;
}

/**
 * @brief Called in response to an data ready interrupt for this driver.
 *
 * @param[in]  dd_handle    Handle to a driver instance.
 * @param[in]  gpio_num     GPIO number that generated the interrupt.
 * @param[in]  timestamp    Time at which ISR is called
 *
 * @return none
 * */
void sns_dd_lps22hb_handle_irq(
    sns_ddf_handle_t  handle,
    uint32_t          gpio_num,
    sns_ddf_time_t    timestamp)
{
    sns_dd_lps22hb_state_t* state=(sns_dd_lps22hb_state_t*)handle;
    sns_ddf_status_e status;
    sns_ddf_sensor_data_s ddf_data[2];
    sns_ddf_sensor_sample_s ddf_sample[2];
    sns_ddf_time_t isr_timestamp;
    q16_t press, tmpt;
    uint32 data_num;

    if ((handle==NULL)||(gpio_num!=state->gpio_num)||!(state->driver_mode&LPS22HB_DRVMODE_bScheduleAll) )
    {
        DD_MSG_0(ERROR, "HandleIrq: Received Null Pointer.");
        return;
    }

    isr_timestamp=sns_ddf_get_timestamp();
    if (isr_timestamp==0) return; // use isr_timestamp once to prevent compile warning.
    if ((timestamp-state->last_irq_timestamp)<(TIMESTAMP_TICK_FREQ/2/LPS22HB_MAX_ODR_Hz))
    // If IRQ interval is less than 1/2 Maximum ODR, treat this IRQ as false IRQ.
    {
        DD_MSG_2(MED, "DRI: IrqTime=%u, IsrTime=%u. False IRQ.", timestamp, isr_timestamp);
        return;
    }
    state->last_irq_timestamp=timestamp;
    DD_MSG_2(MED, "DRI: IrqTime=%u, IsrTime=%u", timestamp, isr_timestamp);
    status=lps22hb_get_pt(state, &press, &tmpt);
    if (SNS_DDF_SUCCESS!=status)
    {
        DD_MSG_0(MED, "DRI: notice error.");
        return;
    }

    data_num=0;

    if (state->dd_press_odr!=0)
    {
        // Create notification for pressure sensor.
        ddf_sample[data_num].status=SNS_DDF_SUCCESS;
        ddf_sample[data_num].sample=press;
        ddf_data[data_num].sensor=SNS_DDF_SENSOR_PRESSURE;
        ddf_data[data_num].status=SNS_DDF_SUCCESS;
        ddf_data[data_num].timestamp=timestamp;
        ddf_data[data_num].end_timestamp=timestamp;
        ddf_data[data_num].num_samples=1;
        ddf_data[data_num].samples=&ddf_sample[data_num];
        lps22hb_log_data(ddf_data[data_num].sensor, ddf_data[data_num].samples->sample, ddf_data[data_num].timestamp);
        DD_MSG_2(MED, "\tP=%d.%dhPa, %d", Q16INT(press), Q16DEC2(press));
        data_num++;
    }

    if (state->dd_temp_odr!=0)
    {
        // Create notification for temperature sensor.
        ddf_sample[data_num].status=SNS_DDF_SUCCESS;
        ddf_sample[data_num].sample=tmpt;
        ddf_data[data_num].sensor=SNS_DDF_SENSOR_TEMP;
        ddf_data[data_num].status=SNS_DDF_SUCCESS;
        ddf_data[data_num].timestamp=timestamp;
        ddf_data[data_num].end_timestamp=timestamp;
        ddf_data[data_num].num_samples=1;
        ddf_data[data_num].samples=&ddf_sample[data_num];
        DD_MSG_0(MED, "dd_temp_odr");   // uncomment this line cause missing 14c1 log.
        lps22hb_log_data(ddf_data[data_num].sensor, ddf_data[data_num].samples->sample, ddf_data[data_num].timestamp);
        DD_MSG_2(MED, "\tT=%d.%dC", Q16INT(tmpt), Q16DEC2(tmpt));
        data_num++;
    }

    // 4. Notify SMGR.
    status = sns_ddf_smgr_notify_data(state->smgr_handle, ddf_data, data_num);
    if (SNS_DDF_SUCCESS!=status) DD_MSG_0(MED, "DRI: notice error.");
}

/**
 * sensor device driver interface.
 */
sns_ddf_driver_if_s sns_dd_press_lps22hb_if=
{
    .init       = &sns_dd_lps22hb_init,
    .get_data   = &sns_dd_lps22hb_get_data,
    .set_attrib = &sns_dd_lps22hb_set_attr,
    .get_attrib = &sns_dd_lps22hb_get_attr,
    .handle_timer = &sns_dd_lps22hb_handle_timer,
    .handle_irq = sns_dd_lps22hb_handle_irq,
    .reset      = &sns_dd_lps22hb_reset,
    .run_test   = &sns_dd_lps22hb_run_test,
    .enable_sched_data = &sns_dd_lps22hb_enable_sched_data,
    .probe      = &sns_dd_lps22hb_probe
};
