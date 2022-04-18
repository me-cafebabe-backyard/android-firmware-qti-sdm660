/******************** (C) COPYRIGHT 2014 STMicroelectronics ********************
 *
 * File Name         : sns_dd_lis3mdl.c
 * Authors           : Karimuddin Sayed
 *                     Wei Wang
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
 *******************************************************************************/
#include "sns_dd_lis3mdl.h"

/**
 * @brief Log data packets
 *
 * @param[in]  sensor      Sensor ID
 * @param[in]  data        Data to log
 * @param[in]  timestamp   Timestamp of data
 */
static void sns_dd_lis3mdl_log_data(sns_ddf_sensor_e sensor, q16_t mag[], sns_ddf_time_t timestamp)
{
    sns_err_code_e status;
    sns_log_sensor_data_pkt_s* log;
    int i;

    status = sns_logpkt_malloc(
        SNS_LOG_CONVERTED_SENSOR_DATA,
        sizeof(sns_log_sensor_data_pkt_s)+sizeof(q16_t)*(LIS3MDL_NUM_AXES-1),
        (void**)&log);
    if ( (status==SNS_SUCCESS) && (log!=NULL) )
    {
        log->version = SNS_LOG_SENSOR_DATA_PKT_VERSION;
        log->sensor_id = sensor;
        log->vendor_id = SNS_DDF_VENDOR_STMICRO;
        log->timestamp = timestamp;
        log->num_data_types = LIS3MDL_NUM_AXES; // axis dimension
        log->num_samples = 1;                   // sample count
        for (i=0;i<LIS3MDL_NUM_AXES;i++) log->data[i]=mag[i];
        sns_logpkt_commit(SNS_LOG_CONVERTED_SENSOR_DATA, log);
    }
}

static sns_ddf_status_e lis3mdl_get_mag(sns_dd_lis3mdl_state_t* state, q16_t mag_Gauss[])
{
    sns_ddf_status_e status;
    uint8_t reg[6] = {0};
    uint8_t rw_bytes;
    int16_t adc[3];

    status=sns_dd_lis3mdl_read_regs(AUTO_INCREMENT|LIS3MDL_OUT_X_L, reg, 6);
    if (status==SNS_DDF_SUCCESS)
    {
        //convert the raw data in reg to X/Y/Z axis sensor data
        adc[0] = (int16_t) (((reg[1])<<8) | reg[0]);
        adc[1] = (int16_t) (((reg[3])<<8) | reg[2]);
        adc[2] = (int16_t) (((reg[5])<<8) | reg[4]);

        //adjust sensor data per current sensitivity, and convert to Q16
        mag_Gauss[0] = FX_DIV_Q16(FX_CONV_Q16((int32_t)adc[0],0), state->sstvt);
        mag_Gauss[1] = FX_DIV_Q16(FX_CONV_Q16((int32_t)adc[1],0), state->sstvt);
        mag_Gauss[2] = FX_DIV_Q16(FX_CONV_Q16((int32_t)adc[2],0), state->sstvt);
        //LIS3MDL_MSG_3(MED, "GetMag: %d, %d, %dmGauss", mag_Gauss[0]*1000/65536, mag_Gauss[1]*1000/65536, mag_Gauss[2]*1000/65536);
    }
    return status;
}

/**
 * @brief Retrieves a single set of magnetic sensor data from mag_lis3mdl.
 *
 * Refer to sns_ddf_driver_if.h for definition.
 */
sns_ddf_status_e sns_dd_lis3mdl_get_data(
    sns_ddf_handle_t dd_handle,
    sns_ddf_sensor_e sensors[],
    uint32_t num_sensors,
    sns_ddf_memhandler_s* memhandler,
    sns_ddf_sensor_data_s** data)
{
    sns_ddf_time_t timestamp;
    sns_ddf_status_e status;
    sns_ddf_sensor_data_s *data_ptr;
    sns_dd_lis3mdl_state_t *state;
    q16_t sae_d[LIS3MDL_NUM_AXES] = { 0 };  // SAE coordinate x,y,z axis data

    if ( (dd_handle==NULL) || (data==NULL) || (num_sensors!=1) )
    {
        LIS3MDL_MSG_0(ERROR, "GetData: dd_handle is NULL");
        return SNS_DDF_EINVALID_PARAM;
    }

    state=(sns_dd_lis3mdl_state_t*)dd_handle;
    //if current power mode is LOWPOWER , return error.
    if (SNS_DDF_POWERSTATE_LOWPOWER==state->power_state) return SNS_DDF_EDEVICE;

    // get current time stamp
    timestamp = sns_ddf_get_timestamp();
    status=lis3mdl_get_mag(state, sae_d);
    if (status!=SNS_DDF_SUCCESS) return status;

    sns_ddf_map_axes(&state->axes_map, sae_d);  //map the sensor data to the phone's coordinates
    LIS3MDL_MSG_3(MED, "mag[3]=%d, %d, %dmGauss", sae_d[0]*1000/65536, sae_d[1]*1000/65536, sae_d[2]*1000/65536);

    //allocate memory for sns_ddf_sensor_data_s data structure
    data_ptr = sns_dd_memhandler_malloc(memhandler, sizeof(sns_ddf_sensor_data_s), state->smgr_handle);
    if (NULL==data_ptr) return SNS_DDF_ENOMEM;
    *data = data_ptr;
    data_ptr->sensor = sensors[0];
    data_ptr->status = SNS_DDF_SUCCESS;
    data_ptr->timestamp = timestamp;
    //allocate memory for data samples.
    data_ptr->samples = sns_dd_memhandler_malloc(memhandler, LIS3MDL_NUM_AXES*sizeof(sns_ddf_sensor_sample_s), state->smgr_handle);
    if (NULL==data_ptr->samples)  return SNS_DDF_ENOMEM;

    //Fill out sensor output data and status.
    //Axis and polarity conversion are configured in the header file.
    data_ptr->samples[0].sample = sae_d[0];
    data_ptr->samples[0].status = SNS_DDF_SUCCESS;
    data_ptr->samples[1].sample = sae_d[1];
    data_ptr->samples[1].status = SNS_DDF_SUCCESS;
    data_ptr->samples[2].sample = sae_d[2];
    data_ptr->samples[2].status = SNS_DDF_SUCCESS;
    data_ptr->num_samples = LIS3MDL_NUM_AXES;
    sns_dd_lis3mdl_log_data(sensors[0], sae_d, timestamp);
    return SNS_DDF_SUCCESS;
}

void sns_dd_lis3mdl_handle_irq(
    sns_ddf_handle_t  handle,
    uint32_t          gpio_num,
    sns_ddf_time_t    timestamp)
{
    sns_dd_lis3mdl_state_t* state;
    sns_ddf_status_e status;
    sns_ddf_sensor_data_s ddf_data[1];
    sns_ddf_sensor_sample_s ddf_sample[LIS3MDL_NUM_AXES];
    sns_ddf_time_t isr_timestamp;
    q16_t mag_Gauss[3];
    sns_ddf_odr_t current_dd_odr;

    //LIS3MDL_MSG_1(MED, "HandleIrq @%d", timestamp);
    if (handle==NULL)
    {
        LIS3MDL_MSG_0(MED, "HandleIrq: Received Null Pointer.");
        return;
    }
    state = (sns_dd_lis3mdl_state_t*)handle;
    if (!state->enable_sched_data||(gpio_num!=state->gpio_num)) return;

    current_dd_odr=state->dd_mag_odr;
    if (current_dd_odr==0) return;
    isr_timestamp=sns_ddf_get_timestamp();
    if ((timestamp-state->last_irq_timestamp)<(TIMESTAMP_TICK_FREQ/2/current_dd_odr))
    // If IRQ interval is less than 1/2 ODR, treat this IRQ as false IRQ.
    {
        LIS3MDL_MSG_2(MED, "DRI: IrqTime=%u, IsrTime=%u. False IRQ.", timestamp, isr_timestamp);
        return;
    }

    state->last_irq_timestamp=timestamp;

    // Get sensor data.
    status=lis3mdl_get_mag(state, mag_Gauss);
    if (status!=SNS_DDF_SUCCESS) return;
    sns_ddf_map_axes(&state->axes_map, mag_Gauss);  //map the sensor data to the phone's coordinates

    // Create notification for primary sensor.
    ddf_sample[0].status=status;
    ddf_sample[0].sample=mag_Gauss[0];
    ddf_sample[1].status=status;
    ddf_sample[1].sample=mag_Gauss[1];
    ddf_sample[2].status=status;
    ddf_sample[2].sample=mag_Gauss[2];
    ddf_data[0].sensor=SNS_DDF_SENSOR_MAG;
    ddf_data[0].status=status;
    ddf_data[0].timestamp=timestamp;
    ddf_data[0].num_samples=LIS3MDL_NUM_AXES*1;
    ddf_data[0].samples=ddf_sample;
    sns_dd_lis3mdl_log_data(SNS_DDF_SENSOR_MAG, mag_Gauss, timestamp);
    LIS3MDL_MSG_5(MED, "DRI: IrqTime=%u, IsrTime=%u, Mag[3]=%d, %d, %dmGauss", timestamp, isr_timestamp,
            mag_Gauss[0]*1000/65536, mag_Gauss[1]*1000/65536, mag_Gauss[2]*1000/65536);

    // 3. Notify SMGR.
    status = sns_ddf_smgr_notify_data(state->smgr_handle, ddf_data, 1);
    if (SNS_DDF_SUCCESS!=status) LIS3MDL_MSG_0(ERROR, "DRI: notice error.");
}

/**
 * MAG_LIS3MDL Magnetometer device driver interface.
 */
sns_ddf_driver_if_s sns_dd_lis3mdl_if =
{
    .init         = &sns_dd_lis3mdl_init,
    .get_data     = &sns_dd_lis3mdl_get_data,
    .set_attrib   = &sns_dd_lis3mdl_set_attr,
    .get_attrib   = &sns_dd_lis3mdl_get_attr,
    .handle_timer = &sns_dd_lis3mdl_handle_timer,
    .handle_irq   = sns_dd_lis3mdl_handle_irq,
    .reset        = &sns_dd_lis3mdl_reset,
    .run_test     = &sns_dd_lis3mdl_run_test,
    .enable_sched_data = &sns_dd_lis3mdl_enable_sched_data,
    .probe        = &sns_dd_lis3mdl_probe
};
