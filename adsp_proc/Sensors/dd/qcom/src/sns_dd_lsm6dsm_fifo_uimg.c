/******************** (C) COPYRIGHT 2015 STMicroelectronics ********************
 *
 * File Name         : sns_ddf_lsm6dsm_fifo_uimg.c
 * Authors           : Karimuddin Sayed
 * Version           : V 5.15.0
 * Date              : 2/20/2017
 * Description       : LSM6DSM driver source file
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

#include "sns_dd_lsm6dsm.h"
#define S4S_DEBUG 1
#define ROUND(a,b) (((a)/(b)) + ((((a) % (b)) > ((b)/2)) ? 1 : 0))
#define ONE_PATTERN (STM_LSM6DSM_BYTES_PER_SAMPLE * state->fifo_info.active_sensors)
#define MAX_SENSORS_SUPPORTED_IN_FIFO (3)
#define MAX_FIFO_SAMPLES_PER_SENSOR (STM_LSM6DSM_MAX_FIFO_READ / (STM_LSM6DSM_BYTES_PER_SAMPLE *  MAX_SENSORS_SUPPORTED_IN_FIFO))

/* Gets the interval (in ticks) between "num_samples" samples, assuming the S4S
 * schedule is synced */
#define STM_GET_S4S_INTVL( state, num_samples ) ((num_samples)*(state->s4s_config.ideal_sync_interval) / (state->s4s_config.modified_t_ph) )

extern stm_lsm6dsm_fifo_odr lsm6dsm_fifo_odr_reg_values[STM_LSM6DSM_ODR_NUM];

void sns_dd_lsm6dsm_alloc_raw_buff( sns_ddf_handle_t dd_handle, int32_t num_bytes)
{
  sns_ddf_status_e status = SNS_DDF_SUCCESS;
  sns_dd_lsm6dsm_state_t* state = sns_dd_lsm6dsm_get_state(dd_handle);
#if UIMAGE_SUPPORT
  uint32_t sub_dev_idx = (dd_handle_align_t) dd_handle & (~DD_HANDLE_ALIGN_BITS);
#endif
  //malloc memory for state->fifo_raw_buffer
  if(NULL == state->fifo_info.raw_buffer) {
    //allocate for accel and gyro
    //if gyro is not enabled we will not use those samples
    status = sns_dd_lsm6dsm_malloc((void**)&(state->fifo_info.raw_buffer),
                                   num_bytes,
                                   state->sub_dev[sub_dev_idx].smgr_handle);
    if(status != SNS_DDF_SUCCESS) {
      LSM6DSM_MSG_E_1(ERROR, "lsm6dsm_enable_fifo: malloc raw_buffer failed. status=%u", status);
    }
  }
}

sns_ddf_status_e sns_dd_lsm6dsm_free_buff(
    sns_ddf_handle_t dd_handle,
    sns_ddf_sensor_e sensor)
{
  sns_dd_lsm6dsm_state_t* state = sns_dd_lsm6dsm_get_state(dd_handle);
  sns_ddf_status_e status = SNS_DDF_SUCCESS;
  uint32_t sub_dev_idx = 0;
  sns_ddf_sensor_sample_s** data_samples = NULL;

  status = lsm6dsm_search_subdev_by_sensortype(
      state,
      sensor,
      &sub_dev_idx);
  if(status != SNS_DDF_SUCCESS)
    return status;

  if((state->fifo_info.acc_data.samples) &&
      (sensor == SNS_DDF_SENSOR_ACCEL)) {
    data_samples = &state->fifo_info.acc_data.samples;
  } else if((state->fifo_info.temp_data.samples) &&
      (state->a_temp_rate == 0) &&
      (state->g_temp_rate == 0) &&
      (sensor == SNS_DDF_SENSOR_TEMP)) {
    data_samples = &state->fifo_info.temp_data.samples;
  } else if((state->fifo_info.gyr_data.samples) &&
      (sensor == SNS_DDF_SENSOR_GYRO)) {
    data_samples = &state->fifo_info.gyr_data.samples;
  } else if((state->hub_info.slv_data.samples) &&
      (sensor == LSM6DSM_SLAVE_SENSOR)) {
    data_samples = &state->hub_info.slv_data.samples;
  }

  if((data_samples) &&
    (*data_samples)) {
    LSM6DSM_DATA_MSG_3(HIGH, "Free_buff - sensor (%d) sub_dev_idx (%d) ptr=%u ", sensor, sub_dev_idx, *data_samples);
    sns_dd_lsm6dsm_mfree(*data_samples, state->sub_dev[sub_dev_idx].smgr_handle);
    *data_samples = NULL;
  } else {
    LSM6DSM_DATA_MSG_2(HIGH, "Free_buff - NULL ptr sensor (%d) sub_dev_idx (%d)  ", sensor, sub_dev_idx);
  }
  return status;
}

sns_ddf_status_e sns_dd_lsm6dsm_alloc_buff(
    sns_ddf_handle_t dd_handle,
    sns_ddf_sensor_e sensor,
    int32_t num_samples)
{
  sns_dd_lsm6dsm_state_t* state = sns_dd_lsm6dsm_get_state(dd_handle);
  sns_ddf_status_e status = SNS_DDF_SUCCESS;
  uint32_t sub_dev_idx = 0;
  sns_ddf_sensor_sample_s** data_samples = NULL;
  uint16_t size = 0;

  status = lsm6dsm_search_subdev_by_sensortype(
      state,
      sensor,
      &sub_dev_idx);
  if(status != SNS_DDF_SUCCESS)
    return status;

  if((!state->fifo_info.acc_data.samples) &&
      (sensor == SNS_DDF_SENSOR_ACCEL)) {
    data_samples = &state->fifo_info.acc_data.samples;
    size = num_samples * STM_LSM6DSM_AXES_PER_SENSOR * sizeof(sns_ddf_sensor_sample_s);
  } else if((!state->fifo_info.temp_data.samples) &&
      ((state->a_temp_rate > 0) ||
      (state->g_temp_rate > 0))   &&
      (sensor == SNS_DDF_SENSOR_TEMP)) {
    data_samples = &state->fifo_info.temp_data.samples;
    size = num_samples * sizeof(sns_ddf_sensor_sample_s);

  } else if((!state->fifo_info.gyr_data.samples) &&
      (sensor == SNS_DDF_SENSOR_GYRO)) {
    data_samples = &state->fifo_info.gyr_data.samples;
    size = num_samples * STM_LSM6DSM_AXES_PER_SENSOR * sizeof(sns_ddf_sensor_sample_s);
  } else if((!state->hub_info.slv_data.samples) &&
      (sensor == LSM6DSM_SLAVE_SENSOR)) {
    data_samples = &state->hub_info.slv_data.samples;
    size = num_samples * STM_LSM6DSM_AXES_PER_SENSOR * sizeof(sns_ddf_sensor_sample_s);
  }
  if((data_samples) &&
    (*data_samples == NULL)) {
    status = sns_dd_lsm6dsm_malloc((void**)(data_samples),
        size,
        state->sub_dev[sub_dev_idx].smgr_handle);
    if(status != SNS_DDF_SUCCESS) {
      LSM6DSM_MSG_E_1(ERROR, "malloc fifo_acc_data samples failed. status=%u", status);
      return status;
    }
    LSM6DSM_DATA_MSG_3(HIGH, "alloc_buff - sensor (%d) num_samples (%d) ptr=%u ", sensor, num_samples, *data_samples);
  } else
    LSM6DSM_DATA_MSG_2(HIGH, "alloc_buff - NULL pointer sensor (%d) num_samples (%d) ", sensor, num_samples);

  return status;
}

sns_ddf_status_e sns_dd_lsm6dsm_start_streaming(
    sns_ddf_handle_t  dd_handle)
{
  sns_dd_lsm6dsm_state_t* state = sns_dd_lsm6dsm_get_state(dd_handle);
  uint8_t rw_buffer = 0x00;
  int8_t new_acc_rate_idx = STM_LSM6DSM_ODR0, set_odr_idx = STM_LSM6DSM_ODR0;
  sns_ddf_status_e status = SNS_DDF_SUCCESS;

  new_acc_rate_idx = sns_dd_lsm6dsm_get_acc_rate(dd_handle);
  set_odr_idx = MAX(new_acc_rate_idx, state->gyr_desired_rate_idx);
  if(state->fifo_info.fifo_enabled) {
    if((state->fifo_info.fifo_rate_idx <= STM_LSM6DSM_ODR0) &&
        (set_odr_idx > STM_LSM6DSM_ODR0)) {
      rw_buffer = 0x06 | lsm6dsm_fifo_odr_reg_values[set_odr_idx];
      sns_dd_lsm6dsm_write_reg(
          dd_handle,
          STM_LSM6DSM_REG_FIFO_CTRL5,
          &rw_buffer,
          1,
          0xFF);
      state->fifo_info.fifo_rate_idx = set_odr_idx;
    }
  }

  //always set max odr of all sensors even in fifo or not
  if ((new_acc_rate_idx > STM_LSM6DSM_ODR0) ||
      (state->fifo_info.acc_fifo_alive == true)) {
    status = sns_dd_acc_lsm6dsm_set_datarate(dd_handle,
        set_odr_idx);
    if(SNS_DDF_SUCCESS != status) {
      LSM6DSM_MSG_E_2(ERROR, "Failed status (%u) odr_idx (%d)", status, set_odr_idx);
      return status;
    }
  }
  if(state->md_desired)
    sns_dd_lsm6dsm_enable_md(dd_handle);
  if (state->gyr_desired_rate_idx > STM_LSM6DSM_ODR0) {
    status = sns_dd_gyr_lsm6dsm_set_datarate(dd_handle,
        set_odr_idx, false);

    if(SNS_DDF_SUCCESS != status) {
      LSM6DSM_MSG_E_2(ERROR, "Failed status (%u) odr_idx (%d)", status, set_odr_idx);
      return status;
    }
  }

  if(LSM6DSM_IS_HUB_SLV_ACTIVE(state->hub_info)) {
    if(state->hub_info.sample_cnt)
      state->hub_info.sample_cnt = state->hub_info.sample_cnt / state->hub_info.dec;
    state->hub_info.dec = state->odr_list[set_odr_idx]/state->hub_info.cur_rate;
  }
  return SNS_DDF_SUCCESS;
}

sns_ddf_status_e sns_dd_lsm6dsm_stop_streaming(
    sns_ddf_handle_t  dd_handle,
    bool flush)
{
  //flags
  //0x1 acc restarted as gyro is starting first time
  //0x2 gyr restarted as acc is starting first time
  sns_dd_lsm6dsm_state_t* state = sns_dd_lsm6dsm_get_state(dd_handle);
  uint8_t rw_buffer = 0x00;

  if(flush == true)
    sns_dd_lsm6dsm_flush_fifo(dd_handle, 0, true);

  if(state->fifo_info.fifo_rate_idx > STM_LSM6DSM_ODR0) {
    sns_dd_lsm6dsm_write_reg(
        dd_handle,
        STM_LSM6DSM_REG_FIFO_CTRL5,
        &rw_buffer,
        1,
        0xFF);
    state->fifo_info.fifo_rate_idx = STM_LSM6DSM_ODR0;
  }

  if (state->acc_cur_rate_idx > STM_LSM6DSM_ODR0) {
    sns_dd_acc_lsm6dsm_set_datarate(dd_handle,
        STM_LSM6DSM_ODR0);
  }
  if(state->md_enabled)
    sns_dd_lsm6dsm_disable_md(dd_handle);

  if(state->gyr_cur_rate_idx > STM_LSM6DSM_ODR0) {
    sns_dd_gyr_lsm6dsm_set_datarate(dd_handle,
        STM_LSM6DSM_ODR0, true);
  }

  if(LSM6DSM_IS_HUB_SLV_ACTIVE(state->hub_info)) {
    //reset sample count as sample count depends on dec
    state->hub_info.sample_cnt = 0;
  }
  return SNS_DDF_SUCCESS;
}

static void sns_dd_backup_valid_sample(
    sns_ddf_handle_t  dd_handle,
    sns_ddf_sensor_e sensor)
{

  sns_dd_lsm6dsm_state_t* state = sns_dd_lsm6dsm_get_state(dd_handle);
  uint16_t idx = 0;
  if((sensor == SNS_DDF_SENSOR_ACCEL) &&
  (state->fifo_info.acc_data.status == SNS_DDF_SUCCESS)){
    //backup last sample
    if((state->fifo_info.acc_sample_cnt) &&
        (state->fifo_info.acc_sample_cnt < MAX_FIFO_SAMPLES_PER_SENSOR)) {
      state->data_intp.acc_last_sample_status = true;
      idx = state->fifo_info.acc_sample_cnt - 1;
      state->data_intp.acc_last_sample[0] = state->fifo_info.acc_data.samples[0 + idx*3].sample;
      state->data_intp.acc_last_sample[1] = state->fifo_info.acc_data.samples[1 + idx*3].sample;
      state->data_intp.acc_last_sample[2] = state->fifo_info.acc_data.samples[2 + idx*3].sample;
    }
  }  else if((sensor == SNS_DDF_SENSOR_GYRO) &&
  (state->fifo_info.gyr_data.status == SNS_DDF_SUCCESS)){
    if((state->fifo_info.gyr_sample_cnt) &&
        (state->fifo_info.gyr_sample_cnt < MAX_FIFO_SAMPLES_PER_SENSOR)) {
      state->data_intp.gyr_last_sample_status = true;
      idx = state->fifo_info.gyr_sample_cnt - 1;
      state->data_intp.gyr_last_sample[0] = state->fifo_info.gyr_data.samples[0 + idx*3].sample;
      state->data_intp.gyr_last_sample[1] = state->fifo_info.gyr_data.samples[1 + idx*3].sample;
      state->data_intp.gyr_last_sample[2] = state->fifo_info.gyr_data.samples[2 + idx*3].sample;
    }
  }

}
static sns_ddf_status_e sns_dd_lsm6dsm_intp(
    sns_ddf_handle_t dd_handle,
    sns_ddf_sensor_e sensor,
    sns_ddf_sensor_sample_s* data_ptr,
    uint16_t valid_samples,
    uint16_t invalid_samples)
{
  sns_dd_lsm6dsm_state_t* state = sns_dd_lsm6dsm_get_state(dd_handle);
  q16_t* last_sample = NULL;
  q16_t valid_first_sample[3] = {0};
  int i = 0;
  bool last_sample_status = false;

  if(sensor == SNS_DDF_SENSOR_ACCEL) {
    last_sample = state->data_intp.acc_last_sample;
    last_sample_status = state->data_intp.acc_last_sample_status;
  }
  else {
    last_sample = state->data_intp.gyr_last_sample;
    last_sample_status = state->data_intp.gyr_last_sample_status;
  }
  if(last_sample_status == false)
    return SNS_DDF_EINVALID_PARAM;

  if(valid_samples) {
    valid_first_sample[0] = (data_ptr+(invalid_samples*3 + 0))->sample;
    valid_first_sample[1] = (data_ptr+(invalid_samples*3 + 1))->sample;
    valid_first_sample[2] = (data_ptr+(invalid_samples*3 + 2))->sample;

    for(i=0; i<invalid_samples; i++) {
      (data_ptr+(0 + i*3))->sample = FX_DIV_Q16((valid_first_sample[0] - last_sample[0]), FX_CONV_Q16((int32_t)(invalid_samples+1), 0)) + last_sample[0];
      (data_ptr+(1 + i*3))->sample = FX_DIV_Q16((valid_first_sample[1] - last_sample[1]), FX_CONV_Q16((int32_t)(invalid_samples+1), 0)) + last_sample[1];
      (data_ptr+(2 + i*3))->sample = FX_DIV_Q16((valid_first_sample[2] - last_sample[2]), FX_CONV_Q16((int32_t)(invalid_samples+1), 0)) + last_sample[2];
    }
  } else {
    for(i=0;i<invalid_samples;i++) {
      (data_ptr+(0 + i*3))->sample = last_sample[0];
      (data_ptr+(1 + i*3))->sample = last_sample[1];
      (data_ptr+(2 + i*3))->sample = last_sample[2];
    }
  }
  return SNS_DDF_SUCCESS;
}

static sns_ddf_status_e sns_dd_lsm6dsm_send_data_smgr(
    sns_ddf_handle_t dd_handle,
    sns_ddf_sensor_e sensor,
    sns_ddf_sensor_data_s* data,
    uint32_t len)
{
  sns_dd_lsm6dsm_state_t* state = sns_dd_lsm6dsm_get_state(dd_handle);
  uint32_t sub_dev_inx = 0;
  sns_ddf_status_e status = SNS_DDF_SUCCESS;
  uint8_t t_fifo_status = 0, t_idx=0;
  sns_ddf_sensor_e p_sensor = 0;
  uint8_t i = 0, temp_enabled = 0;

  if(sensor == SNS_DDF_SENSOR_TEMP) {
    t_fifo_status = (state->fifo_info.fifo_enabled & (TEMP_A_FIFO_BM | TEMP_G_FIFO_BM)) >> 2; //moving bits to first
    if(state->a_temp_rate)
      temp_enabled |=  0x01;
    if(state->g_temp_rate)
      temp_enabled |=  0x10;
    while(t_fifo_status) {
      if(i == 0) {
        p_sensor = SNS_DDF_SENSOR_ACCEL;
        t_idx = 0x0F;
      } else {
        p_sensor = SNS_DDF_SENSOR_GYRO;
        t_idx = 0xF0;
      }
      LSM6DSM_DATA_MSG_3(HIGH, "sns_dd_temp_fifo_data:fifo_enabled (0x%x) temp_enabled (%d) p_sensor (%d)",
          state->fifo_info.fifo_enabled, temp_enabled, p_sensor);

      if(temp_enabled & t_idx) {
        status = lsm6dsm_search_subdev_by_sensortype(
            state,
            p_sensor,
            &sub_dev_inx);
        status = sns_ddf_smgr_notify_data(
            state->sub_dev[sub_dev_inx].smgr_handle,
            data,
            len);
        if(status != SNS_DDF_SUCCESS)
          return status;
#if STM_LSM6DSM_LOGDATA
        sns_dd_lsm6dsm_log_data(data, true);
#endif
      }
      t_fifo_status >>= 1;
      i++;
    }
  } else {
    status = lsm6dsm_search_subdev_by_sensortype(
        state,
        sensor,
        &sub_dev_inx);
    if(status != SNS_DDF_SUCCESS)
      return status;
    status = sns_ddf_smgr_notify_data(
        state->sub_dev[sub_dev_inx].smgr_handle,
        data,
        len);
    if(status != SNS_DDF_SUCCESS)
      return status;

#if STM_LSM6DSM_LOGDATA
    sns_dd_lsm6dsm_log_data(data, true);
#endif

  }
  return status;
}
/**
 * @brief To send FIFO data to SMGR, numbers of sample up to watermark level.
 *
 * @param[in]  dd_handle      Handle to a driver instance.
 * @param[in]  num_samples Num of data samples in FIFO to read.
 * @param[in]  timestamp      The end timestamp.
 *
 * @return SNS_DDF_SUCCESS if this operation was done successfully. Otherwise
 *         SNS_DDF_EDEVICE, SNS_DDF_EBUS, SNS_DDF_EINVALID_PARAM, or SNS_DDF_EFAIL to
 *         indicate and error has occurred.
 */
static sns_ddf_status_e sns_dd_send_fifo_data(
    sns_ddf_handle_t dd_handle,
    sns_ddf_sensor_e sensor,
    sns_ddf_time_t    start_time,
    sns_ddf_time_t    end_time)
{
  sns_dd_lsm6dsm_state_t* state = sns_dd_lsm6dsm_get_state(dd_handle);
  stm_lsm6dsm_fifo_info_s* fifo_info = &state->fifo_info;
  sns_ddf_sensor_data_s fifo_data;
  uint16_t num_samples = 0, total_samples = 0;
  uint16_t num_invalid_samples;
  sns_ddf_status_e status = SNS_DDF_SUCCESS;
  sns_ddf_time_t    last_timestamp = 0, odr_settled_ts = 0;
  sns_ddf_sensor_data_s* sensor_data = NULL;
  int8_t cur_rate_idx = -1;
  bool* intp_status;

  LSM6DSM_DATA_MSG_3(HIGH,
      "send_fifo_data: sensor (%d) start_time (%u) end_time (%u)", sensor, start_time, end_time);

  fifo_data.sensor = sensor;
  fifo_data.status = SNS_DDF_SUCCESS;
  fifo_data.end_timestamp = end_time;
  fifo_data.timestamp = start_time;

  if(sensor == SNS_DDF_SENSOR_TEMP) {
    fifo_data.samples = fifo_info->temp_data.samples;
    fifo_data.num_samples = 1 * fifo_info->temp_sample_cnt;
    if(fifo_data.num_samples == 1)
      fifo_data.end_timestamp = fifo_data.timestamp;

    status = sns_dd_lsm6dsm_send_data_smgr(
        dd_handle,
        sensor,
        &fifo_data,
        1);
    return status;
  }

  if(sensor == SNS_DDF_SENSOR_ACCEL) {
    num_samples = total_samples = fifo_info->acc_sample_cnt;
    sensor_data = &fifo_info->acc_data;
    odr_settled_ts = state->acc_odr_settled_ts;
    intp_status = &state->data_intp.acc_intp_status;
    cur_rate_idx = state->acc_cur_rate_idx;
  } else if(sensor == SNS_DDF_SENSOR_GYRO) {
    num_samples = total_samples = fifo_info->gyr_sample_cnt;
    sensor_data = &fifo_info->gyr_data;
    odr_settled_ts = state->gyr_odr_settled_ts;
    intp_status = &state->data_intp.gyr_intp_status;
    cur_rate_idx = state->gyr_cur_rate_idx;
  } else if(LSM6DSM_IS_HUB_SLV_SENSOR(sensor)) {
    num_samples = total_samples = state->hub_info.sample_cnt / state->hub_info.dec;
    sensor_data = &state->hub_info.slv_data;
    intp_status = &state->hub_info.intp_status;
    odr_settled_ts = state->hub_info.odr_settled_ts;
    //flush use cur rate idx
    cur_rate_idx = state->hub_info.master_rate_idx;
    if(num_samples)
      state->hub_info.sample_cnt = 0;
      //state->hub_info.sample_cnt = state->hub_info.sample_cnt % state->hub_info.dec;
  }

  if(cur_rate_idx < 0) {
    LSM6DSM_MSG_E_1(ERROR, "sns_dd_send_fifo_data:invalid rate_idx (%d) ", cur_rate_idx);
    return SNS_DDF_EINVALID_PARAM;
  }

  fifo_data.samples = sensor_data->samples;

  LSM6DSM_DATA_MSG_3(HIGH, "send_fifo_data: start_timestamp=%u, end_timestamp=%u odr_settled_ts=%u",
      fifo_data.timestamp, fifo_data.end_timestamp, odr_settled_ts);

  if ( (int64_t)(odr_settled_ts - fifo_data.timestamp) <= 0 )
  {
    /* all samples in FIFO produced after ODR change settled */
    num_invalid_samples = 0;
  }
  else if ( (int64_t)(odr_settled_ts - fifo_data.end_timestamp) > 0 )
  {
    /* all samples in FIFO produced before ODR change settled */
    num_invalid_samples = num_samples;
  }
  else /* some samples in FIFO produced before ODR change settled */
  {
    //fifo_info.last_timestamp could be zero or not reliable. Use input parameters of this function.
    uint64_t time_interval = (end_time - start_time)/(num_samples-1);
    uint32_t st_odr = sns_ddf_convert_usec_to_tick ( 1000000 / state->odr_list[cur_rate_idx]);
    num_invalid_samples =
      ((state->acc_odr_settled_ts - fifo_data.timestamp) / st_odr) + 1;
    if(num_invalid_samples > num_samples)
      num_invalid_samples = num_samples;
    fifo_data.end_timestamp =
      start_time + (time_interval * (num_invalid_samples-1));
    //set temporary fifo_info.last_timestamp within this function.
    last_timestamp = fifo_data.end_timestamp;
  }

  if ( num_invalid_samples > 0 )
  {
    LSM6DSM_MSG_3(HIGH,
        "send_fifo_data: #T_samples=%d #invalid=%d intp_status %d", num_samples, num_invalid_samples, *intp_status);
    fifo_data.status      = SNS_DDF_EINVALID_DATA;
    fifo_data.num_samples = STM_LSM6DSM_AXES_PER_SENSOR * num_invalid_samples;
    if(*intp_status == true) {
        status = sns_dd_lsm6dsm_intp(dd_handle, sensor, sensor_data->samples, (num_samples-num_invalid_samples), num_invalid_samples);
        if(status == SNS_DDF_SUCCESS) {

          sns_ddf_time_t est_st_odr = (sns_ddf_convert_usec_to_tick(1000000 / state->odr_list[cur_rate_idx]));
          uint8_t i = 0;
          if((int64_t)(start_time - state->fifo_info.last_timestamp) > (1.8 * est_st_odr)) {
            fifo_data.timestamp -= est_st_odr;
            fifo_data.num_samples += STM_LSM6DSM_AXES_PER_SENSOR;
            for(i=0;i<STM_LSM6DSM_AXES_PER_SENSOR;i++)
              sensor_data->samples[i + num_samples * STM_LSM6DSM_AXES_PER_SENSOR] =
                sensor_data->samples[i + (num_samples -1) * STM_LSM6DSM_AXES_PER_SENSOR];
          }

          fifo_data.status  = SNS_DDF_SUCCESS;
          fifo_data.end_timestamp = end_time;
          if(num_samples - num_invalid_samples) {
            fifo_data.num_samples += STM_LSM6DSM_AXES_PER_SENSOR * (num_samples-num_invalid_samples);
          }
          num_samples = 0;
        } else {
          *intp_status = false;
          /* prepares to send remaining samples */
          num_samples -= num_invalid_samples;
        }
    } else {
        /* prepares to send remaining samples */
        num_samples -= num_invalid_samples;
    }
    status = sns_dd_lsm6dsm_send_data_smgr(
        dd_handle,
        sensor,
        &fifo_data,
        1);
    if(status != SNS_DDF_SUCCESS)
      return status;

    LSM6DSM_DATA_MSG_4(HIGH,
        "send_fifo_data: sensor=%d #invalid=%d ts=%u end_ts=%u",
        sensor, num_invalid_samples, fifo_data.timestamp, fifo_data.end_timestamp);

    if ( num_samples > 0 )
    {
      fifo_data.end_timestamp = end_time;
      fifo_data.timestamp     = last_timestamp +
        (end_time - last_timestamp)/num_samples;
      fifo_data.samples = &sensor_data->samples[num_invalid_samples * STM_LSM6DSM_AXES_PER_SENSOR];
      LSM6DSM_DATA_MSG_4(HIGH,
          "send_fifo_data: sensor = %d #valid=%d ts=%u end_ts=%u",
          sensor, num_samples, fifo_data.timestamp, fifo_data.end_timestamp);
    }
  }
  if ( num_samples > 0 )
  {
    *intp_status = false;
    fifo_data.status = SNS_DDF_SUCCESS;
    fifo_data.num_samples = STM_LSM6DSM_AXES_PER_SENSOR * num_samples;
    status = sns_dd_lsm6dsm_send_data_smgr(
        dd_handle,
        sensor,
        &fifo_data,
        1);
    if(status != SNS_DDF_SUCCESS)
      return status;
    LSM6DSM_DATA_MSG_4(HIGH,
        "send_fifo_data:sensor=%d #valid=%d ts=%u end_ts=%u",
        sensor, num_samples, fifo_data.timestamp, fifo_data.end_timestamp);
    sensor_data->status = fifo_data.status;
    sns_dd_backup_valid_sample(dd_handle, sensor);
  }
  return SNS_DDF_SUCCESS;
}

static void sns_dd_fill_fifo_data(
    sns_ddf_handle_t  dd_handle,
    sns_ddf_sensor_e sensor,
    uint8_t* raw_buf_ptr)
{

  uint16_t *idx = NULL;
  int8_t dec = 1;
  uint16_t i= 0;
  sns_dd_lsm6dsm_state_t* state = sns_dd_lsm6dsm_get_state(dd_handle);
  q16_t sae_d[STM_LSM6DSM_AXES_PER_SENSOR];
  sns_ddf_sensor_sample_s* data_samples = NULL;


  if(sensor == SNS_DDF_SENSOR_ACCEL) {
    data_samples = state->fifo_info.acc_data.samples;
    idx = &state->fifo_info.acc_sample_cnt;
  } else if(sensor == SNS_DDF_SENSOR_GYRO) {
    data_samples = state->fifo_info.gyr_data.samples;
    idx = &state->fifo_info.gyr_sample_cnt;
  } else if(sensor == SNS_DDF_SENSOR_TEMP) {
    data_samples = state->fifo_info.temp_data.samples;
    idx = &state->fifo_info.temp_sample_cnt;
  } else if(LSM6DSM_IS_HUB_SLV_SENSOR(sensor)) {
    data_samples = state->hub_info.slv_data.samples;
    idx = &state->hub_info.sample_cnt;
    dec = state->hub_info.dec;
  }
  if(data_samples != NULL) {

    sns_dd_lsm6dsm_convert_raw_data(dd_handle, sensor, raw_buf_ptr, sae_d);
    for(i=0; i<STM_LSM6DSM_AXES_PER_SENSOR; i++) {
      data_samples[i+(*idx/dec)*3].sample = sae_d[i];
    }
    *idx += 1;
  } else {
    LSM6DSM_MSG_E_1(ERROR, "memory not allocated for samples - sensor (%d)", sensor);
  }

}

static int32_t sns_dd_read_and_split(
    sns_ddf_handle_t  dd_handle,
    uint16_t* pattern_pos,
    uint16_t fifo_count)
{
  sns_dd_lsm6dsm_state_t* state = sns_dd_lsm6dsm_get_state(dd_handle);
  sns_ddf_status_e status = SNS_DDF_SUCCESS;
  uint16_t buffer_pos = 0;
  uint16_t p_pos = 0;
  uint32_t read_count = 0;
  uint8_t offset = 0;
  uint16_t bytes_to_read = fifo_count;
  uint16_t buf_idx = 0;
#if UIMAGE_SUPPORT
  uint32_t sub_dev_idx = (dd_handle_align_t) dd_handle & (~DD_HANDLE_ALIGN_BITS);
#endif

  LSM6DSM_DATA_MSG_2(HIGH, "fifo_count %d pattern_pos %d",fifo_count, *pattern_pos);

  if(fifo_count == 0)
    return 0;

  sns_dd_lsm6dsm_alloc_raw_buff( dd_handle, fifo_count);
  //read pattern pos before reading fifo data
  uint16_t pattern_sample = *pattern_pos / STM_LSM6DSM_AXES_PER_SENSOR; //converting word pos to sample pos

  //reset the parameters
  state->fifo_info.acc_sample_cnt = 0;
  state->fifo_info.gyr_sample_cnt = 0;
  //calculate offset
  switch (*pattern_pos % STM_LSM6DSM_AXES_PER_SENSOR) {

    //data not at sample boundary
    case 1:
    {
      if(state->fifo_info.active_sensors > 1) {
        offset = 4 + (1 - pattern_sample) * STM_LSM6DSM_BYTES_PER_SAMPLE;
      }
      else
        offset = 4 ;
    }
    break;
    case 2:
    if(state->fifo_info.active_sensors > 1)
      offset = 2 + (1 - pattern_sample) * STM_LSM6DSM_BYTES_PER_SAMPLE;
    else
      offset = 2 ;
    break;
    default:
    offset = 0;
    break;
  }

  if(offset > 0) {

    LSM6DSM_DATA_MSG_3(HIGH, "pattern_pos %d pattern_sample %d fifo_count %d",*pattern_pos, pattern_sample, fifo_count);
    bytes_to_read = ALIGN_UP((fifo_count - offset ), (STM_LSM6DSM_BYTES_PER_SAMPLE * state->fifo_info.active_sensors)) + offset;
    pattern_sample = 0;
    LSM6DSM_DATA_MSG_2(HIGH, "offset %d bytes_to_read %d", offset, bytes_to_read);
  }

  if((!(bytes_to_read / ONE_PATTERN)) && (offset > 0)) {
    LSM6DSM_MSG_E_0(HIGH, "ERROR*** not enough bytes in fifo to make a sample");
    sns_ddf_read_port_u32_count(
        state->port_handle,
        STM_LSM6DSM_REG_FIFO_DATA_OUT_L,
        state->fifo_info.raw_buffer,
        (offset),
        &read_count);
    *pattern_pos = pattern_sample * STM_LSM6DSM_AXES_PER_SENSOR;
    sns_dd_lsm6dsm_mfree( state->fifo_info.raw_buffer, state->sub_dev[sub_dev_idx].smgr_handle );
    state->fifo_info.raw_buffer = NULL;
    return offset;
  }

  bytes_to_read = ALIGN_UP((bytes_to_read + buf_idx), ONE_PATTERN) + offset;
  if(bytes_to_read == 0) {
    LSM6DSM_MSG_1(HIGH, "handle_irq: bytes_to_read (%d) not even one sample", bytes_to_read);
    sns_dd_lsm6dsm_mfree( state->fifo_info.raw_buffer, state->sub_dev[sub_dev_idx].smgr_handle );
    state->fifo_info.raw_buffer = NULL;
    return bytes_to_read;
  }

  if(bytes_to_read > STM_LSM6DSM_MAX_FIFO_READ)
    bytes_to_read = STM_LSM6DSM_MAX_FIFO_READ;

  bytes_to_read -= buf_idx;

  LSM6DSM_DATA_MSG_2(HIGH, "sns_dd_parse_and_split: buff_idx %d bytes_to_read %d",buf_idx, bytes_to_read);
  status = sns_ddf_read_port_u32_count(
      state->port_handle,
      STM_LSM6DSM_REG_FIFO_DATA_OUT_L,
      &state->fifo_info.raw_buffer[buf_idx],
      bytes_to_read,
      &read_count);

  if(status != SNS_DDF_SUCCESS) {
    LSM6DSM_MSG_E_1(ERROR, "read_port fails status 0x%x ",status);
    sns_dd_lsm6dsm_mfree( state->fifo_info.raw_buffer, state->sub_dev[sub_dev_idx].smgr_handle );
    state->fifo_info.raw_buffer = NULL;
    return -1;
  }
  if(read_count != bytes_to_read)
  {
    LSM6DSM_MSG_E_2(ERROR, "send_fifo_data: raw data reading fails, num_bytes_to_read=%u, actual_read_bytes=%u",
        bytes_to_read, read_count);
    sns_dd_lsm6dsm_mfree( state->fifo_info.raw_buffer, state->sub_dev[sub_dev_idx].smgr_handle );
    state->fifo_info.raw_buffer = NULL;
    return -1;
  }

  uint8_t* raw_buf_ptr = state->fifo_info.raw_buffer;

  LSM6DSM_DATA_MSG_3(HIGH, "sns_dd_parse_and_split read bytes %d pattern_pos %d active_sensors %d",read_count, *pattern_pos, state->fifo_info.active_sensors);

  if(state->fifo_info.fifo_enabled & ACCEL_FIFO_BM)
    sns_dd_lsm6dsm_alloc_buff(dd_handle, SNS_DDF_SENSOR_ACCEL, read_count/ONE_PATTERN+1);
  if(state->fifo_info.fifo_enabled & GYRO_FIFO_BM)
    sns_dd_lsm6dsm_alloc_buff(dd_handle, SNS_DDF_SENSOR_GYRO, read_count/ONE_PATTERN+1);
  if(state->fifo_info.fifo_enabled & SLAVE_FIFO_BM)
    sns_dd_lsm6dsm_alloc_buff(dd_handle, LSM6DSM_SLAVE_SENSOR, read_count/ONE_PATTERN+1);

  if(state->fifo_info.active_sensors > 1) {

    p_pos = pattern_sample;
    for(buffer_pos = 0; buffer_pos < ((read_count+buf_idx-offset)/STM_LSM6DSM_BYTES_PER_SAMPLE); buffer_pos++, p_pos++)
    {
      if(p_pos == state->fifo_info.pattern_samples_cnt)
        p_pos = 0;
#if PACKET_DBG
      LSM6DSM_DATA_MSG_2(HIGH, "sns_dd_parse_and_split: p_pos %d buffer_pos %d",p_pos, buffer_pos);
#endif
      //convert the raw data in read_buffer to X/Y/Z axis sensor data
      if((state->fifo_info.pattern_array[p_pos] == ACCEL_FIFO_BM) && (state->fifo_info.fifo_enabled & ACCEL_FIFO_BM)) {
        sns_dd_fill_fifo_data(dd_handle, SNS_DDF_SENSOR_ACCEL, &raw_buf_ptr[offset + buffer_pos*STM_LSM6DSM_BYTES_PER_SAMPLE]);
      } else if((state->fifo_info.pattern_array[p_pos] == GYRO_FIFO_BM) && (state->fifo_info.fifo_enabled & GYRO_FIFO_BM)) {
        sns_dd_fill_fifo_data(dd_handle, SNS_DDF_SENSOR_GYRO, &raw_buf_ptr[offset + buffer_pos*STM_LSM6DSM_BYTES_PER_SAMPLE]);
      } else if((state->fifo_info.pattern_array[p_pos] == SLAVE_FIFO_BM) && (state->fifo_info.fifo_enabled & SLAVE_FIFO_BM)) {
        sns_dd_fill_fifo_data(dd_handle, LSM6DSM_SLAVE_SENSOR, &raw_buf_ptr[offset + buffer_pos*STM_LSM6DSM_BYTES_PER_SAMPLE]);
      }
    }
  } else if(state->fifo_info.active_sensors == 1) {
    if(state->fifo_info.fifo_enabled & ACCEL_FIFO_BM) {
      for(buffer_pos = 0; buffer_pos < ((read_count+buf_idx-offset)/STM_LSM6DSM_BYTES_PER_SAMPLE); buffer_pos++ ) {
        sns_dd_fill_fifo_data(dd_handle, SNS_DDF_SENSOR_ACCEL, &raw_buf_ptr[offset + buffer_pos*STM_LSM6DSM_BYTES_PER_SAMPLE]);
      }
    } else if(state->fifo_info.fifo_enabled & GYRO_FIFO_BM) {
      for(buffer_pos = 0; buffer_pos < ((read_count+buf_idx-offset)/STM_LSM6DSM_BYTES_PER_SAMPLE); buffer_pos++ ) {
        sns_dd_fill_fifo_data(dd_handle, SNS_DDF_SENSOR_GYRO, &raw_buf_ptr[offset + buffer_pos*STM_LSM6DSM_BYTES_PER_SAMPLE]);
      }
    } else if(state->fifo_info.fifo_enabled & SLAVE_FIFO_BM) {
      for(buffer_pos = 0; buffer_pos < ((read_count+buf_idx-offset)/STM_LSM6DSM_BYTES_PER_SAMPLE); buffer_pos++ ) {
        sns_dd_fill_fifo_data(dd_handle, LSM6DSM_SLAVE_SENSOR, &raw_buf_ptr[offset + buffer_pos*STM_LSM6DSM_BYTES_PER_SAMPLE]);
      }
    }
  }
  sns_dd_lsm6dsm_mfree( state->fifo_info.raw_buffer, state->sub_dev[sub_dev_idx].smgr_handle );
  state->fifo_info.raw_buffer = NULL;
  *pattern_pos = 0;
  return (read_count);
}

static void sns_dd_lsm6dsm_validate_timestamps(
    sns_ddf_time_t cur_time,
    sns_ddf_time_t last_timestamp,
    int32_t        num_samples,
    uint32_t       est_interval,
    sns_ddf_time_t *restrict start_time,
    sns_ddf_time_t *restrict end_time )
{
  sns_ddf_time_t orig_start_time = *start_time;
  sns_ddf_time_t orig_end_time = *end_time;

  cur_time = sns_ddf_get_timestamp();

  if( *start_time > last_timestamp + est_interval * 3/2 ){
      *start_time = last_timestamp + est_interval * 3/2;
  }

  if( last_timestamp + est_interval/2 > *start_time ) {
      *start_time = last_timestamp + est_interval/2;
  }

  if( *start_time <= last_timestamp ) {
    *start_time += est_interval;
    *end_time += est_interval;
  }

  if( *start_time > cur_time) {
    *start_time = cur_time;
  }
  //start_time should be correct here
  //lets validate end_time
  if(*end_time < *start_time) {
    //using est_interval as the accurate interval
    *end_time = *start_time + (num_samples -1) * est_interval;
  }

  if( *end_time > cur_time) {
    *end_time = cur_time;
  }

  if(orig_start_time == orig_end_time) {
    //correct the end_time, as start_time is already corrected
    *end_time = *start_time;
  }

  if(( *start_time == *end_time && num_samples > 1 ) ||
      ( *start_time != *end_time && num_samples == 1 ))
  {
    LSM6DSM_MSG_0(ERROR, "Validate timestamp error");
  }
  if( *start_time != orig_start_time ||
      *end_time != orig_end_time )
  {
    LSM6DSM_MSG_E_4(HIGH, "Adjusted timestamps start %u-->%u end %u-->%u",
                  orig_start_time, *start_time,
                  orig_end_time, *end_time );
  }
}


static void sns_dd_lsm6dsm_timestamp_synthesis(
    sns_ddf_handle_t dd_handle,
    uint32_t total_sps,
    sns_ddf_time_t*  c_sample_time,
    sns_ddf_time_t use_time,
    bool flush)

{
  sns_dd_lsm6dsm_state_t* state = sns_dd_lsm6dsm_get_state(dd_handle);
  sns_ddf_time_t cal_end=0, cal_st = 0;

  sns_ddf_time_t est_st_odr = (sns_ddf_convert_usec_to_tick(1000000 / state->odr_list[state->fifo_info.fifo_rate_idx])) ;
  sns_ddf_time_t est_st_s = ROUND((use_time - state->fifo_info.last_timestamp), total_sps);
  int64_t drift_time = 0;

  LSM6DSM_DATA_MSG_4(HIGH, "flush = %d use_time = %u last_ts = %u total_sps = %d", flush, use_time, state->fifo_info.last_timestamp, total_sps);
  //if((state->fifo_info.first_pass == true) &&
  if((flush == true) ||
       (total_sps > state->fifo_info.cur_wmk))
  {
    if(state->fifo_info.avg_sample_time == 0) {
      if( state->s4s_config.modified_t_ph != 0 ) {
        cal_st = STM_GET_S4S_INTVL( state, 1 );
      } else {
        cal_st = est_st_odr;
      }
      //cal_st = MIN(est_st_s, est_st_odr);
    } else {
      cal_st = state->fifo_info.avg_sample_time;
    }
    cal_end = state->fifo_info.last_timestamp + cal_st * total_sps;
    LSM6DSM_DATA_MSG_2(HIGH, "time_synthesis: c_st = %d cal_end = %u",cal_st, cal_end);
    if(cal_end > use_time)
      cal_st = est_st_s;
    else {
      drift_time = (int64_t) (use_time - cal_end);
        //drift time is more than 1
      if (drift_time > cal_st) {
        cal_st += ALIGN_UP(drift_time, cal_st);
      } /*
      else if(drift_time > (0.9 * cal_st)) {
        // if drift time more than 70%
        //still consider avg_st is accurate, so add 50% of diff
        cal_st += ROUND((uint64_t) (drift_time - (cal_st * 0.9)), total_sps);
      }
      */
    }

  } else if((flush != true) &&
      (total_sps <= state->fifo_info.cur_wmk)) {

    if((use_time > state->fifo_info.last_timestamp)&&
        (0 != state->fifo_info.last_timestamp))
    {
      //use state->fifo_info.last_timestamp as reliable source
      cal_st = est_st_s;
      LSM6DSM_DATA_MSG_2(HIGH, "est_st_odr (%u) cal_st (%u)", est_st_odr, cal_st);
    }
    else
    {
      //applies if timestamp < fifo_info.last_timestamp or last_timestmap is zero
      //use timestamp as reliable source.
      cal_st = est_st_odr;
      LSM6DSM_DATA_MSG_2(HIGH, "est_st_odr (%u) cal_st (%u)", est_st_odr, cal_st);
    }
  }
  *c_sample_time = cal_st;
  LSM6DSM_DATA_MSG_4(HIGH, "time_synthesis: c_st = %d e_st_s = %d est_st_odr = %d avg_st = %d",cal_st, est_st_s, est_st_odr, state->fifo_info.avg_sample_time);
}

static void sns_dd_lsm6dsm_fifo_reset(sns_ddf_handle_t  dd_handle)
{
  sns_dd_lsm6dsm_state_t* state = sns_dd_lsm6dsm_get_state(dd_handle);
  sns_dd_lsm6dsm_stop_streaming(dd_handle, false);
  sns_dd_lsm6dsm_start_streaming(dd_handle);
  state->fifo_info.last_timestamp = sns_ddf_get_timestamp();
  if(state->acc_cur_rate_idx >= 0)
    state->data_intp.acc_intp_status = true;
  if(state->gyr_cur_rate_idx >= 0)
    state->data_intp.gyr_intp_status = true;
}



//MAX delay between interrupt generated to interrupt handler called
#define ADSP_MAX_INTERRUPT_DELAY (sns_ddf_convert_usec_to_tick(1000))
static sns_ddf_status_e sns_dd_lsm6dsm_handle_fifo_data(
    sns_ddf_handle_t  dd_handle,
    uint8_t* read_buf,
    sns_ddf_time_t timestamp,
    sns_ddf_time_t cur_time,
    bool flush)
{
  sns_dd_lsm6dsm_state_t* state = sns_dd_lsm6dsm_get_state(dd_handle);
  uint16_t read_bytes_remain = 0, bytes_to_read = 0, total_sps = 0, total_in_fifo = 0;
  int64_t drift_time = 0, adsp_int_latency = 0, st_jitter = 0;
  uint16_t read_bytes = 0;
  uint32_t read_samples = 0, hub_samples = 0;
  //flag for the while loop to guarantee no MD/DBT interrupt get dropped during fifo interrupt.
  sns_ddf_time_t end_time=0, start_time=0, cal_st = 0, est_st = 0, use_time = 0, hub_cal_st = 0;
  uint8_t countH, countL;
  //initialize end time, helps if any errors
  end_time = state->fifo_info.last_timestamp;

  LSM6DSM_DATA_MSG_3(HIGH, "handle_fifo_data: ENTRY last_timestamp %u irq_time %u cur_time %u ", state->fifo_info.last_timestamp, timestamp, cur_time);
  if(read_buf[1] & STM_LSM6DSM_FIFO_FULL_STATUS_MASK) {
    total_in_fifo = STM_LSM6DSM_MAX_FIFO_BYTES;
  } else {
    countH = read_buf[1] & STM_LSM6DSM_FIFO_WTM_CTRL2_MASK;
    countL = read_buf[0] & STM_LSM6DSM_FIFO_WTM_CTRL1_MASK;

    total_in_fifo = (((countH << 8) & 0xFF00) | countL) * 2; //converting to bytes
    LSM6DSM_DATA_MSG_3(HIGH, "countL=(%x) countH=(%x) fifo_count = (%d) bytes", countL, countH, total_in_fifo);

  }

  uint16_t pattern_pos = ((((read_buf[3] & STM_LSM6DSM_FIFO_PATTERN_STATUS4) << 8 ) & 0xFF00) |
      (read_buf[2] & STM_LSM6DSM_FIFO_PATTERN_STATUS3));

  LSM6DSM_DATA_MSG_3(HIGH, "pattern_pos (%d) fifo_enabled (%d) total_in_fifo (%d)", pattern_pos, state->fifo_info.fifo_enabled, total_in_fifo);

  total_sps =  total_in_fifo / ONE_PATTERN;
  if(!total_sps) {
    LSM6DSM_DATA_MSG_3(HIGH, "handle_fifo_data: total_in_fifo %d total_sps %d a_sensors %d",
        total_in_fifo, total_sps, state->fifo_info.active_sensors);
    return SNS_DDF_EFAIL;
  }

  // send a FIFO Watermark event to SMGR
  if(flush == true) {
    LSM6DSM_MSG_3(HIGH, "cur_time (%u) last_timestamp (%u) total_in_fifo (%d) bytes", cur_time, state->fifo_info.last_timestamp, total_in_fifo);
    state->fifo_info.first_pass = true;
    if(total_in_fifo % STM_LSM6DSM_BYTES_PER_SAMPLE) {
      //reset the fifo
      LSM6DSM_MSG_E_2(HIGH, "Resetting - FIFO bytes (%d) not multiple of 6 - pattern (%d)", total_in_fifo, pattern_pos);
      sns_dd_lsm6dsm_fifo_reset(dd_handle);
      return SNS_DDF_EFAIL;
    }
  } else if(state->fifo_info.first_pass == true) {
    if(total_sps > 1)
      state->fifo_info.avg_sample_time = 0;//reset here, recalculate
  }


  //initialize read_count_bytes
  read_bytes_remain = total_in_fifo; //total fifo bytes

  LSM6DSM_DATA_MSG_3(HIGH, "handle_fifo_data: total_in_fifo=%u bytes active sensors %d total_samples %d per sensor",
      total_in_fifo, state->fifo_info.active_sensors, total_sps);

  adsp_int_latency = (int64_t) (cur_time - timestamp);
  est_st = sns_ddf_convert_usec_to_tick(1000000 / state->odr_list[state->fifo_info.fifo_rate_idx]);

  if((flush == true) ||
      (state->fifo_info.first_pass != true) ||
      ((total_sps > state->fifo_info.cur_wmk) &&
       (state->fifo_info.cur_wmk == 1)))
    use_time = cur_time;
  else if((total_sps > state->fifo_info.cur_wmk) &&
      (state->fifo_info.cur_wmk > 1)) {
    //read only wmk samples if cur_wmk > 1
    read_bytes_remain =  state->fifo_info.cur_wmk * (STM_LSM6DSM_BYTES_PER_SAMPLE * state->fifo_info.active_sensors);
    use_time = timestamp;
  } else
    use_time = timestamp;

  do {
    //LIMIT - the max no of bytes to read at once is limited to 120 words (40 samples)
    //convert total samples (6 bytest) to bytes
    if(read_bytes_remain  > (ONE_PATTERN * MAX_FIFO_SAMPLES_PER_SENSOR)) {
      //limit total_in (in samples)
      bytes_to_read = ONE_PATTERN * MAX_FIFO_SAMPLES_PER_SENSOR;
    } else
      bytes_to_read = read_bytes_remain;

    LSM6DSM_DATA_MSG_3(HIGH, "handle_fifo_data: read_bytes_remain %d active sensors %d bytes_to_read (%d)",
        read_bytes_remain, state->fifo_info.active_sensors, bytes_to_read);
    bytes_to_read = ALIGN_UP(bytes_to_read, ONE_PATTERN);
    if(bytes_to_read == 0) {
      LSM6DSM_DATA_MSG_2(HIGH, "handle_fifo_data: a_sensors (%d) bytes_to_read (%d) not even one sample", state->fifo_info.active_sensors, bytes_to_read);
      break;
    }
    read_bytes = sns_dd_read_and_split(dd_handle, &pattern_pos, bytes_to_read);
    LSM6DSM_DATA_MSG_4(HIGH, "handle_fifo_data: active sensors %d acc_sample_cnt (%d) gyr_sample_cnt (%d) slave_sample_cnt (%d)",
        state->fifo_info.active_sensors, state->fifo_info.acc_sample_cnt, state->fifo_info.gyr_sample_cnt, state->hub_info.sample_cnt) ;

    if(read_bytes >= ONE_PATTERN) {

      total_sps = read_bytes_remain / ONE_PATTERN;
      if( flush == true &&
          ( state->s4s_config.synced == STM_LSM6DSM_S4S_1ST_SYNCED ||
            state->s4s_config.synced == STM_LSM6DSM_S4S_SYNCED ) ) {
        /* Calculate the number of samples before & after the current sync time */
        uint32_t num_after;
        uint32_t num_before;
        uint32_t num_samples = total_sps;
        est_st = STM_GET_S4S_INTVL(state, 1);

        num_after = (cur_time - state->s4s_config.curr_sync_time) * state->s4s_config.modified_t_ph / state->s4s_config.ideal_sync_interval;
#ifdef S4S_DEBUG
        LSM6DSM_MSG_3(HIGH, "calc ts: curr_sync_time %u mod t_ph %d sync_interval %u",
            state->s4s_config.curr_sync_time, state->s4s_config.modified_t_ph,
            state->s4s_config.ideal_sync_interval );
        LSM6DSM_MSG_3(HIGH, "calc ts:sync_status %d total_sps %d num_after %d ",
            state->s4s_config.synced, total_sps, num_after );
        LSM6DSM_MSG_1(HIGH, "calc ts: last_ts %u ",  state->fifo_info.last_timestamp );
#endif /* S4S_DEBUG */

        if( num_samples <= num_after ) {
          /* All samples are after the latest sync */
          end_time = state->s4s_config.curr_sync_time + STM_GET_S4S_INTVL( state, num_after );
          if(end_time > cur_time)
            end_time = cur_time;
          start_time = end_time - STM_GET_S4S_INTVL( state, num_samples - 1 );
#ifdef S4S_DEBUG
          LSM6DSM_MSG_2(HIGH, "all samples after latest sync: start_ts %u end_ts %u ",
              start_time, end_time);
          LSM6DSM_MSG_2(HIGH, "all samples after latest sync: num_after_int %d num_samp-1_int %d ",
              STM_GET_S4S_INTVL( state, num_after), STM_GET_S4S_INTVL( state, num_samples - 1 ));
#endif /* S4S_DEBUG */

        } else {
          /* TODO: in the case of 1ST_SYNCED, need to use a locally adjusted value
           * for curr_sync_time, since the part won't actually be using the S4S tick
           * for the sample at the 2nd ST (since it just got synced) */

          /* Some samples are before the sync time */
          num_before = num_samples - num_after;
          if( num_before > 0 && num_after > 0 ) {
            /* There are samples both before & after the current sync time */
            /* TODO: This should really send out the before samples in one report, and the after samples in another */
            start_time = state->fifo_info.last_timestamp + STM_GET_S4S_INTVL( state, 1 );
            end_time = state->s4s_config.curr_sync_time + STM_GET_S4S_INTVL( state, num_after );
#ifdef S4S_DEBUG
            if( start_time == end_time ) {
              LSM6DSM_MSG_0(ERROR, "Adjusting start time");
              start_time -= STM_GET_S4S_INTVL( state, 1 )/2;
            }

            LSM6DSM_MSG_2(HIGH, "some samples before some after current sync:: start_ts %u end_ts %u ",
                start_time, end_time);
            LSM6DSM_MSG_2(HIGH, "some samples before some after current sync:: num_after_int %d est_st %d ",
                STM_GET_S4S_INTVL( state, num_after), est_st);
#endif /* S4S_DEBUG */

          } else {
            /* Only samples before the current sync time */
            if( state->s4s_config.synced == STM_LSM6DSM_S4S_1ST_SYNCED ) {
              start_time = state->fifo_info.last_timestamp + est_st;
              end_time = start_time + STM_GET_S4S_INTVL(state, num_before);
            } else {
              start_time = state->fifo_info.last_timestamp + est_st;
              end_time = state->fifo_info.last_timestamp + STM_GET_S4S_INTVL(state, num_before);
#ifdef S4S_DEBUG
              LSM6DSM_MSG_3(HIGH, "all samples before current sync:: start_ts %u end_ts %u est_st %d",
                  start_time, end_time, est_st);
#endif
              if( (end_time - state->s4s_config.curr_sync_time) < est_st ||
                  (state->s4s_config.curr_sync_time - end_time) < est_st   ) {
                /* S4S is synced, and the end time is less than one interval away from the
                 * ideal sync interval. This means that the end sample time should really
                 * be equal to the ideal sync interval */
                end_time = state->s4s_config.curr_sync_time;
              }
            }
            if( end_time > state->s4s_config.curr_sync_time )
            {
#ifdef S4S_DEBUG
              LSM6DSM_MSG_0(HIGH, "Adjusting end time to be curr sync time");
#endif
              end_time = state->s4s_config.curr_sync_time;
              if( start_time > end_time ) {
                start_time = end_time;
              }
            }
            else if( end_time == state->s4s_config.curr_sync_time )
            {
            }
#ifdef S4S_DEBUG
            LSM6DSM_MSG_2(HIGH, "all samples before current sync:: start_ts %u end_ts %u ",
                start_time, end_time);
            LSM6DSM_MSG_2(HIGH, "all samples before current sync:: num_after_int %d est_st %d ",
                STM_GET_S4S_INTVL( state, num_before), est_st);
#endif /* S4S_DEBUG */

          }
          if(end_time > cur_time)
            end_time = cur_time;
        }

      } else {
        sns_dd_lsm6dsm_timestamp_synthesis(dd_handle, total_sps, &cal_st, use_time, flush);

        if((total_sps <= state->fifo_info.cur_wmk) &&
            (flush != true)) {
          if(total_sps == 1) {
            if((cal_st < 1.25 * est_st) && (cal_st > 0.75 * est_st)) {
              if(!state->fifo_info.avg_sample_time)
                state->fifo_info.avg_sample_time = est_st;
              st_jitter = cal_st - state->fifo_info.avg_sample_time;
              cal_st = state->fifo_info.avg_sample_time + st_jitter/2;
              state->fifo_info.avg_sample_time = (state->fifo_info.avg_sample_time + cal_st)/2;
              if(st_jitter)
                use_time = cur_time;
            }
          } else {
            state->fifo_info.avg_sample_time += (cal_st * total_sps) ;
          }
          read_samples += total_sps;
        }
        //assuming equal no of samples in acc & gyro

        if((state->fifo_info.fifo_enabled & SLAVE_FIFO_BM) &&
            (state->hub_info.sample_cnt)) {
          hub_cal_st = cal_st * state->hub_info.dec;
          hub_samples = state->hub_info.sample_cnt / state->hub_info.dec;
          if(hub_samples) {
            if(state->fifo_info.last_timestamp)
              start_time = state->fifo_info.last_timestamp + cal_st;
            else
              start_time = use_time - hub_cal_st * (hub_samples - 1);

            end_time = start_time + hub_cal_st * (hub_samples - 1);
            LSM6DSM_DATA_MSG_3(HIGH, "cal_st %u hub_sample_cnt %d hub_dec %d", cal_st, state->hub_info.sample_cnt, state->hub_info.dec);
            if(end_time > use_time)
              end_time = use_time;

            if(total_sps == 1) {
              if((flush == false) &&
                  (state->fifo_info.first_pass == true)) {

                //adjust timestamp - sometimes ADSP delaying calling interrupt handler
                //check if irq timestamp is way off cur time
                if(adsp_int_latency > ADSP_MAX_INTERRUPT_DELAY) {
                  cal_st = est_st;
                }
                else {
                  //end_time = timestamp;
                }
              } else
                end_time = state->fifo_info.last_timestamp + cal_st;
              start_time = end_time;
            }

            sns_dd_lsm6dsm_validate_timestamps(
                cur_time,
                state->fifo_info.last_timestamp,
                hub_samples,
                est_st*state->hub_info.dec,
                &start_time,
                &end_time );

            sns_dd_send_fifo_data(dd_handle,
                LSM6DSM_SLAVE_SENSOR,
                start_time,
                end_time);
          }
        }
        if(state->fifo_info.acc_sample_cnt || state->fifo_info.gyr_sample_cnt) {
          if(state->fifo_info.last_timestamp)
            start_time = state->fifo_info.last_timestamp + cal_st;
          else
            start_time = use_time - cal_st * ((state->fifo_info.acc_sample_cnt) ?
                (state->fifo_info.acc_sample_cnt- 1) :
                (state->fifo_info.gyr_sample_cnt- 1)) ;

          end_time = start_time + cal_st * ((state->fifo_info.acc_sample_cnt) ?
              (state->fifo_info.acc_sample_cnt- 1) :
              (state->fifo_info.gyr_sample_cnt- 1)) ;

          LSM6DSM_DATA_MSG_4(HIGH, "last_ts %u cur_ts %u ts %u end_ts %u",state->fifo_info.last_timestamp, cur_time, start_time, end_time);
          if(end_time > use_time)
            end_time = use_time;

          if(total_sps == 1) {
            if((flush == false) &&
                (state->fifo_info.first_pass == true)) {

              //adjust timestamp - sometimes ADSP delaying calling interrupt handler
              //check if irq timestamp is way off cur time
              if(adsp_int_latency > ADSP_MAX_INTERRUPT_DELAY) {
                cal_st = est_st;
              }
              else {
                //end_time = timestamp;
              }
            } else
              end_time = state->fifo_info.last_timestamp + cal_st;
            start_time = end_time;
          }
        }
      }
      if(state->fifo_info.acc_sample_cnt || state->fifo_info.gyr_sample_cnt) {
        LSM6DSM_DATA_MSG_4(HIGH, "use_ts %u ts %u end_ts %u drift_cts %d",use_time, start_time, end_time, (use_time - start_time));
        sns_dd_lsm6dsm_validate_timestamps(
            cur_time,
            state->fifo_info.last_timestamp,
            MAX(state->fifo_info.acc_sample_cnt, state->fifo_info.gyr_sample_cnt),
            est_st,
            &start_time,
            &end_time );

        if((state->fifo_info.fifo_enabled & ACCEL_FIFO_BM) &&
            (state->fifo_info.acc_sample_cnt)) {
          sns_dd_send_fifo_data(dd_handle,
              SNS_DDF_SENSOR_ACCEL,
              start_time,
              end_time);
        }
        if((state->fifo_info.fifo_enabled & GYRO_FIFO_BM) &&
            (state->fifo_info.gyr_sample_cnt)) {
          sns_dd_send_fifo_data(dd_handle,
              SNS_DDF_SENSOR_GYRO,
              start_time,
              end_time);
        }
      }
      state->fifo_info.first_pass = false;

      //update last timestamp
      state->fifo_info.last_timestamp = end_time;
      //free memory here, if allocated
      sns_dd_lsm6dsm_free_buff(dd_handle, SNS_DDF_SENSOR_ACCEL);
      sns_dd_lsm6dsm_free_buff(dd_handle, SNS_DDF_SENSOR_GYRO);
      sns_dd_lsm6dsm_free_buff(dd_handle, LSM6DSM_SLAVE_SENSOR);
    }
    read_bytes_remain -= read_bytes;
    LSM6DSM_DATA_MSG_3(HIGH, "handle_fifo_data: read_bytes_remain=%d read_bytes %d last_timestamp %u",
        read_bytes_remain, read_bytes, state->fifo_info.last_timestamp);


  } while(read_bytes_remain > 0);

  if((flush != true) && (read_samples))
    state->fifo_info.avg_sample_time /= read_samples;
  if((state->fifo_info.fifo_enabled & (TEMP_A_FIFO_BM | TEMP_G_FIFO_BM)) &&
      (state->fifo_info.temp_sample_cnt)) {
    sns_dd_send_fifo_data(dd_handle,
        SNS_DDF_SENSOR_TEMP,
        state->fifo_info.temp_data.timestamp,
        end_time);
    state->fifo_info.temp_sample_cnt = 0;
  }
  if(total_in_fifo >= ONE_PATTERN) {
    //resetting end_time based on cur_time
    drift_time = use_time - end_time;
    if ((drift_time > 0) && (drift_time > cal_st)) {
      end_time += ALIGN_UP(drift_time, cal_st);
      LSM6DSM_MSG_3(HIGH, "handle_fifo_data: adjusting drift_time %d cur_time %u cal_sample_time %d",drift_time, use_time, cal_st);
    }
  }
  state->fifo_info.last_timestamp = end_time;

  LSM6DSM_DATA_MSG_3(HIGH, "handle_fifo_data: EXIT irq_time = %u last_timestamp = %u cur_time = %u  ", timestamp, state->fifo_info.last_timestamp, sns_ddf_get_timestamp());
  return SNS_DDF_SUCCESS;
}

sns_ddf_status_e sns_dd_lsm6dsm_flush_fifo(
    sns_ddf_handle_t dd_handle,
    uint32_t num_samples,
    bool fifo_resetting)
{
  sns_dd_lsm6dsm_state_t *state = sns_dd_lsm6dsm_get_state(dd_handle);
  sns_ddf_status_e status = SNS_DDF_SUCCESS;
  uint8_t rw_buffer[10] = {0};
  uint8_t rw_bytes = 0;
  sns_ddf_time_t cur_time = 0;
  LSM6DSM_MSG_2(HIGH, "Flush_fifo: fifo_resetting %d fifo_enabled 0x%x", fifo_resetting, state->fifo_info.fifo_enabled);
  do {
    status = sns_ddf_read_port(
        state->port_handle,
        STM_LSM6DSM_REG_FIFO_STATUS1,
        rw_buffer,
        4,
        &rw_bytes);
    if(status != SNS_DDF_SUCCESS)
      return status ;
    if(rw_bytes != 4)
      return SNS_DDF_EBUS;

    cur_time = sns_ddf_get_timestamp();
    LSM6DSM_DATA_MSG_2(HIGH, "Flush_fifo: fifo_resetting %d cur_time %u", fifo_resetting, cur_time);
    status = sns_dd_lsm6dsm_handle_fifo_data(dd_handle, &rw_buffer[0], cur_time, cur_time, true);
  } while((fifo_resetting == true) && (status == SNS_DDF_SUCCESS));
  LSM6DSM_DATA_MSG_0(HIGH, "Flush_fifo: EXIT");
  return SNS_DDF_SUCCESS;
}

void sns_dd_lsm6dsm_handle_fifo_int(
    sns_ddf_handle_t  dd_handle,
    sns_ddf_time_t    timestamp,
    bool* fifo_retry)
{
  sns_ddf_status_e status;
  sns_dd_lsm6dsm_state_t* state = sns_dd_lsm6dsm_get_state(dd_handle);
  sns_ddf_time_t    cur_time;
  uint8_t rw_buffer[4] = {0};
  uint8_t rw_bytes = 0;

  // verify source of interrupts by reading FIFO_SRC.
  status = sns_ddf_read_port(
      state->port_handle,
      STM_LSM6DSM_REG_FIFO_STATUS1,
      rw_buffer,
      4,
      &rw_bytes);
  if(status != SNS_DDF_SUCCESS)
    return;
  if(rw_bytes != 4)
    return;

  cur_time = sns_ddf_get_timestamp();

  //FIFO overflow interrupt handling.
  if((rw_buffer[1] & STM_LSM6DSM_FIFO_OVR_STATUS_MASK) &&
      (state->fifo_info.first_pass == true))
  {
    LSM6DSM_DATA_MSG_2(HIGH, "handle_fifo_int: to send overflow event, watermark=%u, timestamp=%u",
        state->fifo_info.cur_wmk, timestamp);
    LSM6DSM_MSG_2(HIGH, "handle_fifo_int: to send overflow event fifo_status2=0x%x fifo_enabled %d",
        rw_buffer, state->fifo_info.fifo_enabled);

    // send a FIFO overflow event to SMGR

    if((state->acc_desired_rate_idx >=0) &&
        (state->fifo_info.fifo_enabled & ACCEL_FIFO_BM)){
      status =sns_dd_lsm6dsm_send_event_smgr(dd_handle,
          SNS_DDF_SENSOR_ACCEL,
          SNS_DDF_EVENT_FIFO_OVERFLOW);
      if(status != SNS_DDF_SUCCESS)
        return;

    }
    if((state->gyr_desired_rate_idx >=0) &&
        (state->fifo_info.fifo_enabled & GYRO_FIFO_BM)){
      status =sns_dd_lsm6dsm_send_event_smgr(dd_handle,
          SNS_DDF_SENSOR_GYRO,
          SNS_DDF_EVENT_FIFO_OVERFLOW);
      if(status != SNS_DDF_SUCCESS)
        return;

    }
    state->fifo_info.first_pass = false;
    *fifo_retry = true;
  }

  //FIFO watermark interrupt(without overflow flag) handling
  if((0x0 == (rw_buffer[1] & STM_LSM6DSM_FIFO_OVR_STATUS_MASK)) &&
      (rw_buffer[1] & STM_LSM6DSM_FIFO_WTM_STATUS_MASK))
  {

    if(rw_buffer[1] & STM_LSM6DSM_FIFO_EMPTY_STATUS_MASK) {
      LSM6DSM_DATA_MSG_0(LOW, "fifo empty flag set");
      *fifo_retry = false;
    } else {
      if((state->acc_desired_rate_idx >=0) &&
          (state->fifo_info.fifo_enabled & ACCEL_FIFO_BM)){
        status =sns_dd_lsm6dsm_send_event_smgr(dd_handle,
            SNS_DDF_SENSOR_ACCEL,
            SNS_DDF_EVENT_FIFO_WM_INT);
        if(status != SNS_DDF_SUCCESS)
          return ;
      }
      if((state->gyr_desired_rate_idx >=0) &&
          (state->fifo_info.fifo_enabled & GYRO_FIFO_BM)){
        status =sns_dd_lsm6dsm_send_event_smgr(dd_handle,
            SNS_DDF_SENSOR_GYRO,
            SNS_DDF_EVENT_FIFO_WM_INT);
        if(status != SNS_DDF_SUCCESS)
          return ;
      }
      status = sns_dd_lsm6dsm_handle_fifo_data(dd_handle, rw_buffer, timestamp, cur_time, false);
        if(status == SNS_DDF_SUCCESS)
          *fifo_retry = true;
        else
          *fifo_retry = false;
    }
  }

}

/**
 * @brief Implement trigger_fifo_data API.
 *
 * Refer to sns_ddf_driver_if.h for definition.
 */
sns_ddf_status_e sns_dd_lsm6dsm_trigger_fifo(
    sns_ddf_handle_t dd_handle,
    sns_ddf_sensor_e sensor,
    uint16_t num_samples,
    bool trigger_now)
{
  sns_dd_lsm6dsm_state_t *state = sns_dd_lsm6dsm_get_state(dd_handle);
  sns_ddf_status_e status = SNS_DDF_SUCCESS;

  LSM6DSM_MSG_3(HIGH, "trigger_fifo: get called, sensor (%d) num_samples=%u, cur_time=%u",
      sensor, num_samples, sns_ddf_get_timestamp());

  if(!((SNS_DDF_SENSOR_ACCEL == sensor) ||
        (SNS_DDF_SENSOR_GYRO == sensor) ||
        (num_samples < STM_LSM6DSM_MAX_FIFO)))
  {
    LSM6DSM_MSG_E_2(HIGH, "trigger_fifo: SNS_DDF_EINVALID_PARAM , sensor=%u num_samples %d", sensor, num_samples);
    return SNS_DDF_EINVALID_PARAM;
  }

  if(!trigger_now || !state->fifo_info.fifo_enabled)
  {
    LSM6DSM_MSG_E_2(HIGH, "trigger_fifo: returning .. trigger_now (%d) fifo_info.fifo_enabled (%d)", trigger_now, state->fifo_info.fifo_enabled);
    return SNS_DDF_SUCCESS;
  }

  status = sns_dd_lsm6dsm_flush_fifo(dd_handle, num_samples, false);
  //reset the intp variables ... flushing
  //state->data_intp.acc_intp_status = false;
  //state->data_intp.gyr_intp_status = false;
  LSM6DSM_DATA_MSG_1(HIGH, "trigger_fifo: EXIT timestamp %u", sns_ddf_get_timestamp());
  return status;
}
