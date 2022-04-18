/******************** (C) COPYRIGHT 2015 STMicroelectronics ********************
 *
 * File Name         : sns_dd_lsm6dsm_uimg.c
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

sns_ddf_driver_if_s sns_dd_lsm6dsm_if;


stm_lsm6dsm_head_s lsm6dsm_dd_head = {
  NULL,
  {"STMICRO_LSM6DSM", 3}
};

/**
 * Accelerometer LSM6DSM_ACC sampling frequencies array for setting attribute
 */
stm_lsm6dsm_acc_odr lsm6dsm_acc_odr_reg_values[STM_LSM6DSM_ODR_NUM] = {
  STM_LSM6DSM_ACC_ODR13,
  STM_LSM6DSM_ACC_ODR26,
  STM_LSM6DSM_ACC_ODR52,
  STM_LSM6DSM_ACC_ODR104,
  STM_LSM6DSM_ACC_ODR208,
  STM_LSM6DSM_ACC_ODR416,
  STM_LSM6DSM_ACC_ODR833,
  STM_LSM6DSM_ACC_ODR1660,
  STM_LSM6DSM_ACC_ODR3330,
  STM_LSM6DSM_ACC_ODR6660
};

/**
 * LSM6DSM_GYR sampling frequencies array for setting attribute
 */
stm_lsm6dsm_gyr_odr lsm6dsm_gyr_odr_reg_values[STM_LSM6DSM_ODR_NUM] = {
  STM_LSM6DSM_GYR_ODR13,
  STM_LSM6DSM_GYR_ODR26,
  STM_LSM6DSM_GYR_ODR52,
  STM_LSM6DSM_GYR_ODR104,
  STM_LSM6DSM_GYR_ODR208,
  STM_LSM6DSM_GYR_ODR416,
  STM_LSM6DSM_GYR_ODR833,
  STM_LSM6DSM_GYR_ODR1660,
};

/**
 * LSM6DSM FIFO sampling frequencies array for setting attribute
 */
stm_lsm6dsm_fifo_odr lsm6dsm_fifo_odr_reg_values[STM_LSM6DSM_ODR_NUM] = {
  STM_LSM6DSM_FIFO_ODR13,
  STM_LSM6DSM_FIFO_ODR26,
  STM_LSM6DSM_FIFO_ODR52,
  STM_LSM6DSM_FIFO_ODR104,
  STM_LSM6DSM_FIFO_ODR208,
  STM_LSM6DSM_FIFO_ODR416,
  STM_LSM6DSM_FIFO_ODR833,
  STM_LSM6DSM_FIFO_ODR1660,
  STM_LSM6DSM_FIFO_ODR3330,
  STM_LSM6DSM_FIFO_ODR6660
};

/**
 * LSM6DSM sampling frequencies array for attribute(ODR)
 */
sns_ddf_odr_t lsm6dsm_s4s_odr[STM_LSM6DSM_ODR_NUM] = {
  /* Different ODRs for S4S */
  10,
  20,
  50,
  100,
  200,
  416,
  833,
  1660,
  3330,
  6660
};
sns_ddf_odr_t lsm6dsm_non_s4s_odr[STM_LSM6DSM_ODR_NUM] = {
  13,
  26,
  52,
  104,
  208,
  416,
  833,
  1660,
  3330,
  6660
};

sns_dd_lsm6dsm_state_t* sns_dd_lsm6dsm_get_state(sns_ddf_handle_t dd_handle)
{
  if(dd_handle == NULL)
    return NULL;
  return (sns_dd_lsm6dsm_state_t *)lsm6dsm_dd_head.next;
}

#if DUMP_REGISTER_DATA
void sns_dd_lsm6dsm_dump_register_single(sns_ddf_handle_t  dd_handle, uint8_t reg, uint8_t size)
{
  sns_dd_lsm6dsm_state_t* state = sns_dd_lsm6dsm_get_state(dd_handle);
  sns_ddf_status_e status;
  uint8_t rw_buffer[32] = {0};
  uint8_t rw_bytes = 0;
  uint8_t i = 0;

  status = sns_ddf_read_port(
      state->port_handle,
      reg,
      &rw_buffer[i],
      size,
      &rw_bytes);
  if(status != SNS_DDF_SUCCESS) {
    LSM6DSM_MSG_E_0(ERROR, "returned error");
    return;
  }
  if(rw_bytes != size) {
    LSM6DSM_MSG_E_0(ERROR, "bytes doesn't match");
    return;
  }
  for(i=0;i<size;i++)
    LSM6DSM_MSG_2(HIGH, "UPDATED - Reg 0x%x = 0x%x ", reg, rw_buffer[i]);
}
#endif

int8_t sns_dd_lsm6dsm_get_acc_rate(sns_ddf_handle_t dd_handle)
{
    sns_dd_lsm6dsm_state_t* state = sns_dd_lsm6dsm_get_state(dd_handle);
    int8_t acc_eff_rate_idx = state->acc_desired_rate_idx;
    int8_t hub_rate_idx = -1, esp_rate_idx = -1;
    if(LSM6DSM_IS_ESP_ACTIVE(state->esp_info))
      esp_rate_idx = LSM6DSM_ESP_RATE(state->esp_info);
    if(esp_rate_idx > acc_eff_rate_idx)
      acc_eff_rate_idx = esp_rate_idx;

    if((LSM6DSM_IS_HUB_SLV_ACTIVE(state->hub_info)) &&
        (state->hub_info.cur_rate)) {
      hub_rate_idx = state->hub_info.master_rate_idx;
    }
    if(hub_rate_idx >= acc_eff_rate_idx)
      acc_eff_rate_idx = hub_rate_idx;
    if(state->md_desired) {
      if(STM_LSM6DSM_ODR13 > acc_eff_rate_idx)
      acc_eff_rate_idx = STM_LSM6DSM_ODR13;
    }
    return acc_eff_rate_idx;
}

/**
 * @brief Performs a motion detection enable
 *
 * @param[in]  dd_handle      Handle to a driver instance.
 *
 * @return SNS_DDF_SUCCESS if this operation was done successfully. Otherwise
 *         SNS_DDF_EDEVICE, SNS_DDF_EBUS, SNS_DDF_EINVALID_PARAM, or SNS_DDF_EFAIL to
 *         indicate and error has occurred.
 */
sns_ddf_status_e sns_dd_lsm6dsm_enable_md(
    sns_ddf_handle_t dd_handle)
{
  sns_dd_lsm6dsm_state_t* state = sns_dd_lsm6dsm_get_state(dd_handle);
  sns_ddf_status_e status = SNS_DDF_EFAIL;
  uint8_t rw_buffer = 0;
  int8_t new_rate_index;
  sns_ddf_odr_t new_rate;
  uint8_t dur_set = 0;
  uint8_t thresh_set = 0;

  LSM6DSM_MSG_1(LOW, "enable_md dd_handle (%u)", dd_handle);
  //Register configuration for wake-up application
  //config ODR and bandwidth
  //only config ODR when double tap sensor is off. ODR when dbt is on is always 1250hz.

  state->md_desired = true;

  if(state->acc_cur_rate_idx < 0) {
    status =  sns_dd_lsm6dsm_match_odr(dd_handle,
        STM_LSM6DSM_MD_ODR,
        &new_rate,
        &new_rate_index);
    if(SNS_DDF_SUCCESS != status) {
      LSM6DSM_MSG_E_1(ERROR, "match_odr failed status (%d)", status);
      return status;
    }
    //update rate
    status = sns_dd_acc_lsm6dsm_set_datarate(dd_handle, new_rate_index);
    if(SNS_DDF_SUCCESS != status) {
      LSM6DSM_MSG_E_1(ERROR, "set_acc_datarate failed status (%d)", status);
      return status;
    }
  }
  if(!(state->esp_info.esp_enabled & STM_LSM6DSM_BM_DBT))
  {
    thresh_set = STM_LSM6DSM_MD_THRESH;
    dur_set =  STM_LSM6DSM_MD_DUR;
  }
  else
  {
    // default, double-tap enabled
    thresh_set = state->esp_info.esp_config.md_thresh;
    dur_set = state->esp_info.esp_config.md_dur;
  }

  LSM6DSM_MSG_3(HIGH, "esp_enabled (%d) md_thresh (%d) md_odr (%d)", state->esp_info.esp_enabled, thresh_set, dur_set);
  rw_buffer = thresh_set;
  status = sns_dd_lsm6dsm_write_reg(
      dd_handle,
      STM_LSM6DSM_REG_WAKE_THS,
      &rw_buffer,
      1,
      0x3F);
  if(status != SNS_DDF_SUCCESS) {
    LSM6DSM_MSG_E_1(ERROR, "write reg failed  status=%u", status);
    return status;
  }
  rw_buffer = dur_set;
  status = sns_dd_lsm6dsm_write_reg(
      dd_handle,
      STM_LSM6DSM_REG_WAKE_DUR,
      &rw_buffer,
      1,
      0x60);
  if(status != SNS_DDF_SUCCESS) {
    LSM6DSM_MSG_E_1(ERROR, "write reg failed  status=%u", status);
    return status;
  }

  lsm6dsm_enable_mdf(dd_handle, SLOPE_FILTER);
  if(is_lsm6dsm_mdf_settled(dd_handle, SLOPE_FILTER)) {
    if(is_lsm6dsm_mdf_settled(dd_handle, HP_FILTER))
      lsm6dsm_enable_mdf(dd_handle, HP_FILTER);
    rw_buffer = 0x20; //set wakeup int
    status = sns_dd_lsm6dsm_write_reg(
        dd_handle,
        STM_LSM6DSM_REG_MD1_CFG,
        &rw_buffer,
        1,
        0x20);
    if(status != SNS_DDF_SUCCESS) {
      LSM6DSM_MSG_E_1(ERROR, "write reg failed  status=%u", status);
      return status;
    }
    state->md_enabled = true;
  }
  LSM6DSM_MSG_1(HIGH, "enable md - Exit enable_md status %d", status );
  return status;
}

/**
 * @brief Performs a motion detection disable
 *
 * @param[in]  dd_handle      Handle to a driver instance.
 *
 * @return SNS_DDF_SUCCESS if this operation was done successfully. Otherwise
 *         SNS_DDF_EDEVICE, SNS_DDF_EBUS, SNS_DDF_EINVALID_PARAM, or SNS_DDF_EFAIL to
 *         indicate and error has occurred.
 */
sns_ddf_status_e sns_dd_lsm6dsm_disable_md(
    sns_ddf_handle_t dd_handle)
{
  sns_dd_lsm6dsm_state_t* state = sns_dd_lsm6dsm_get_state(dd_handle);
  sns_ddf_status_e status = SNS_DDF_EFAIL;
  uint8_t rw_buffer[1] = {0};

  LSM6DSM_MSG_0(LOW, "disable_md dd_handle ");
  if(state->md_desired == true) {
    if(state->md_enabled) {
      rw_buffer[0] = 0
        | (0<<7)            // INT1_INACT_STATE
        | (0<<6)            // INT1_SINGLE_TAP
        | (0<<5)            // INT1_WU
        | (0<<4)            // INT1_FF
        | (0<<3)            // INT1_DOUBLE_TAP
        | (0<<2)            // INT1_6D
        | (0<<1)            // INT1_TILT
        | 0;                // INT1_TIMER
      status = sns_dd_lsm6dsm_write_reg(
          dd_handle,
          STM_LSM6DSM_REG_MD1_CFG,
          rw_buffer,
          1,
          0x20);
      if(status != SNS_DDF_SUCCESS) {
        LSM6DSM_MSG_E_1(ERROR, "write reg failed  status=%u", status);
        return status;
      }
    }

    rw_buffer[0] = 0x3F;
    status = sns_dd_lsm6dsm_write_reg(
        dd_handle,
        STM_LSM6DSM_REG_WAKE_THS,
        rw_buffer,
        1,
        0x3F);
    if(status != SNS_DDF_SUCCESS) {
      LSM6DSM_MSG_E_1(ERROR, "write reg failed  status=%u", status);
      return status;
    }

    lsm6dsm_enable_mdf(dd_handle, SLOPE_FILTER);
    if((state->acc_desired_rate_idx < 0) &&
        (state->fifo_info.acc_fifo_alive == false) &&
        (!LSM6DSM_IS_ESP_ACTIVE(state->esp_info))) {
      status = sns_dd_acc_lsm6dsm_set_datarate(dd_handle, -1);
      if(status != SNS_DDF_SUCCESS)
        return status;
    }
    //TODO:: any timers active cancel
      //there must be some timer running
    if((state->md_timer.timer) &&
      ((state->md_timer.reason == SETTLING_HPF) ||
       (state->md_timer.reason == SETTLING_SLOPE)))
      sns_dd_lsm6dsm_destroy_timer(dd_handle, &state->md_timer);


    LSM6DSM_MSG_1(HIGH, "disable_md: status=%d", status);
    state->md_enabled = false;
  }
  return SNS_DDF_SUCCESS;

}
sns_ddf_status_e sns_dd_lsm6dsm_send_event_smgr(
    sns_ddf_handle_t dd_handle,
    sns_ddf_sensor_e sensor,
    sns_ddf_event_e event)
{
  sns_dd_lsm6dsm_state_t* state = sns_dd_lsm6dsm_get_state(dd_handle);
  uint32_t sub_dev_inx = 0;
  sns_ddf_status_e status = SNS_DDF_SUCCESS;
  status = lsm6dsm_search_subdev_by_sensortype(
      state,
      sensor,
      &sub_dev_inx);
  if(status != SNS_DDF_SUCCESS)
    return status;
  if(event == SNS_DDF_EVENT_ODR_CHANGED)
    LSM6DSM_MSG_2(HIGH, "ODR_CHANGED event sent to smgr - sub_dev (%d) sensor (%d)", sub_dev_inx, sensor);
  else if(event == SNS_DDF_EVENT_DT_ABORT)
    LSM6DSM_MSG_2(HIGH, "DT_ABORT event sent to smgr - sub_dev (%d) sensor (%d)", sub_dev_inx, sensor);
  return sns_ddf_smgr_notify_event(
      state->sub_dev[sub_dev_inx].smgr_handle,
      sensor,
      event);
}

void sns_dd_lsm6dsm_convert_raw_data(
    sns_ddf_handle_t dd_handle,
    sns_ddf_sensor_e sensor,
    uint8_t* raw,//8 bits for each sensor
    q16_t* data)
{
  sns_dd_lsm6dsm_state_t* state = sns_dd_lsm6dsm_get_state(dd_handle);
  int16_t hw_d[STM_LSM6DSM_AXES_PER_SENSOR] = {0};
  int i = 0;

  if(sensor == SNS_DDF_SENSOR_GYRO) {
    for(i=0; i<STM_LSM6DSM_AXES_PER_SENSOR; i++) {
      hw_d[i] = (int16_t) (((raw[i*2 + 1]) << 8) | raw[i*2 + 0]);
      data[i] = FX_MUL_Q16(FX_DIV_Q16(FX_CONV_Q16((int32_t)hw_d[i],0), FX_CONV_Q16((int32_t)1000,0)),
          state->gyr_sstvt_adj);
    }
    sns_ddf_map_axes(&state->axes_map, data);
  } else if(sensor == SNS_DDF_SENSOR_ACCEL) {
    for(i=0; i<STM_LSM6DSM_AXES_PER_SENSOR; i++) {
      hw_d[i] = (int16_t) (((raw[i*2 + 1]) << 8) | raw[i*2 + 0]);
      //adjust sensor data per current sensitivity, and convert to Q16
      data[i] = FX_FLTTOFIX_Q16(hw_d[i] * state->acc_sstvt_adj * G/1000000);

    }
    sns_ddf_map_axes(&state->axes_map, data);
  } else if(sensor == SNS_DDF_SENSOR_TEMP) {
    hw_d[0] = (int16_t) (((raw[1]) << 8) | raw[0]);
    data[0] = FX_DIV_Q16(FX_CONV_Q16((int16_t)hw_d[0],0), FX_CONV_Q16((int16_t)256,0)) +
      FX_CONV_Q16((int16_t)25,0);
  } else if(LSM6DSM_IS_HUB_SLV_SENSOR(sensor)) {
    for(i=0; i<LSM6DSM_SLAVE_1_AXES; i++) {
      hw_d[i] = (int16_t) (((raw[i*2 + 1]) << 8) | raw[i*2 + 0]);
      data[i] = FX_FLTTOFIX_Q16(hw_d[i] * state->hub_info.sstvt);
    }
#if DEBUG_MAG_DATA
    LSM6DSM_DATA_MSG_3(HIGH, "MAG_DATA raw (%d) (%d) %d)", raw[0], raw[1], raw[2]);
    LSM6DSM_DATA_MSG_3(HIGH, "MAG_DATA raw (%d) (%d) %d)", raw[3], raw[4], raw[5]);
    LSM6DSM_DATA_MSG_3(HIGH, "MAG_DATA adc (%d) (%d) %d)", hw_d[0], hw_d[1], hw_d[2]);
    LSM6DSM_DATA_MSG_3(HIGH, "MAG_DATA sae_d(%d) (%d) %d)", data[0], data[1], data[2]);
#endif
    sns_ddf_map_axes(&state->hub_info.axes_map, data);
  }
}
//pattern returns bit setting using FIFO_BM
uint16_t sns_dd_lsm6dsm_read_out_data(
    sns_ddf_handle_t dd_handle,
    sns_ddf_sensor_e sensors[],
    uint32_t num_sensors,
    q16_t* sae_d,
    uint8_t* sensors_pattern)
{
  uint8_t read_reg = 0x00;
  uint8_t num_bytes = 0;
  uint8_t raw_buffer[14] = { 0 };
  sns_ddf_status_e status;
  // sensor coordinate x,y,z axis raw hardware data
  uint8_t read_count = 0;
  uint8_t buf_idx = 0, s_pattern = 0;
  int i = 0;
  sns_dd_lsm6dsm_state_t* state = sns_dd_lsm6dsm_get_state(dd_handle);

  for(i = 0; i < num_sensors; i++) {
    if(sensors[i] == SNS_DDF_SENSOR_ACCEL)
      s_pattern |= ACCEL_FIFO_BM;
    else if(sensors[i] == SNS_DDF_SENSOR_GYRO)
      s_pattern |= GYRO_FIFO_BM;
    else if(sensors[i] == SNS_DDF_SENSOR_TEMP)
      s_pattern |= TEMP_A_FIFO_BM;
  }
  *sensors_pattern = s_pattern;
  //special case Temp and accel
  if((s_pattern & 0x07) == 0x05) {
    //read seperately
    read_reg = STM_LSM6DSM_REG_OUT_TEMP_L;
    status = sns_ddf_read_port(
        state->port_handle,
        read_reg,
        raw_buffer,
        2,
        &read_count);
    if(status != SNS_DDF_SUCCESS) {
      LSM6DSM_MSG_E_1(ERROR, "read_port failed- status (%d)",status);
      return buf_idx;
    }
    if(read_count != 2) {
      LSM6DSM_MSG_E_1(ERROR, "read_port failed-  read_count  does not match - read_count (%d)",read_count);
      return buf_idx;
    }
    buf_idx += 2;
    //clear temp in s_pattern
    s_pattern &= ~0x04;

  }

  if(s_pattern & TEMP_A_FIFO_BM) {
    read_reg = STM_LSM6DSM_REG_OUT_TEMP_L;
    num_bytes += 2;
  }
  if(s_pattern & GYRO_FIFO_BM) {
    if(!(s_pattern & 0x04))
      read_reg = STM_LSM6DSM_REG_OUT_X_L_G;
    num_bytes += STM_LSM6DSM_BYTES_PER_SAMPLE;
  }

  if(s_pattern & ACCEL_FIFO_BM) {
    if((!(s_pattern & 0x04)) &&
        (!(s_pattern & GYRO_FIFO_BM)))
    read_reg = STM_LSM6DSM_REG_OUT_X_L_XL;
    num_bytes += STM_LSM6DSM_BYTES_PER_SAMPLE;
  }

  status = sns_ddf_read_port(
      state->port_handle,
      read_reg,
      &raw_buffer[buf_idx],
      num_bytes,
      &read_count);
  if(status != SNS_DDF_SUCCESS) {
    LSM6DSM_MSG_E_1(ERROR, "read_port failed- status (%d)",status);
    return buf_idx;
  }
  if(read_count != num_bytes) {
    LSM6DSM_MSG_E_1(ERROR, "read_port failed-  read_count  does not match - read_count (%d)",read_count);
    return buf_idx;
  }

 //reset here for parsing
  buf_idx = 0;


  if(s_pattern & TEMP_A_FIFO_BM) {
    sns_dd_lsm6dsm_convert_raw_data(dd_handle, SNS_DDF_SENSOR_TEMP, &raw_buffer[buf_idx * 2], sae_d+buf_idx);
    buf_idx += 1;
  }
  if(s_pattern & GYRO_FIFO_BM) {
    sns_dd_lsm6dsm_convert_raw_data(dd_handle, SNS_DDF_SENSOR_GYRO, &raw_buffer[buf_idx * 2], sae_d+buf_idx);
    buf_idx += STM_LSM6DSM_AXES_PER_SENSOR;
  }

  if(s_pattern & ACCEL_FIFO_BM) {
    sns_dd_lsm6dsm_convert_raw_data(dd_handle, SNS_DDF_SENSOR_ACCEL, &raw_buffer[buf_idx * 2], sae_d+buf_idx);
    buf_idx += STM_LSM6DSM_AXES_PER_SENSOR;
  }

  return (buf_idx);
}

static void sns_dd_lsm6dsm_handle_temp_timeout(
    sns_ddf_handle_t dd_handle)
{
  sns_dd_lsm6dsm_state_t* state = sns_dd_lsm6dsm_get_state(dd_handle);
  q16_t sae_d[STM_LSM6DSM_AXES_PER_SENSOR];
  uint8_t read_bytes = 0, s_pattern = 0;
  sns_ddf_sensor_e sensors = SNS_DDF_SENSOR_TEMP;

  uint16_t idx = state->fifo_info.temp_sample_cnt;

  if((state->fifo_info.temp_data.samples == NULL) ||
    (idx > STM_LSM6DSM_MAX_TEMP_FIFO_DEPTH))
    return;
  if(state->fifo_info.fifo_enabled & (TEMP_A_FIFO_BM | TEMP_G_FIFO_BM)) {

  read_bytes = sns_dd_lsm6dsm_read_out_data(dd_handle, &sensors, 1, sae_d, &s_pattern);
  if(read_bytes == 0)
    return ;
    if(idx == 0)
      state->fifo_info.temp_data.timestamp = sns_ddf_get_timestamp();
    state->fifo_info.temp_data.samples[idx].sample = sae_d[0];
    state->fifo_info.temp_data.samples[idx].status = SNS_DDF_SUCCESS;
    state->fifo_info.temp_sample_cnt++;
  }
}
//create timer if the odr set time and timeout are not within 1 msec
sns_ddf_status_e sns_dd_lsm6dsm_create_timer(
    sns_ddf_handle_t dd_handle,
    stm_lsm6dsm_timer* timer_info,
    uint32_t timeout,
    timer_msg_t msg,
    bool repeat)
{
  if(timer_info->timer == NULL) {
    LSM6DSM_MSG_0(HIGH, "create timer - timer NULL initializing");
    sns_ddf_timer_init(&timer_info->timer, dd_handle, &sns_dd_lsm6dsm_if, timer_info, false);
  }
  timer_info->reason = msg;
  timer_info->repeat = repeat;
  sns_ddf_timer_start(timer_info->timer, timeout);
  LSM6DSM_MSG_2(HIGH, "create timer - timer started timeout(%d)usec ticks(%d)",
      timeout, sns_ddf_convert_usec_to_tick(timeout));
  LSM6DSM_MSG_1(HIGH, "create timer -  timer (%u)", timer_info);
  return SNS_DDF_SUCCESS;
}

void sns_dd_lsm6dsm_destroy_timer(sns_ddf_handle_t dd_handle, stm_lsm6dsm_timer* timer)
{
  LSM6DSM_MSG_2(HIGH, "destroy timer -  timer (%u) reason (%d)", timer, timer->reason);
  if(timer->timer) {
    sns_ddf_timer_cancel(timer->timer);
//    sns_ddf_timer_release(timer->timer);
//    timer->timer = NULL;
  }
}

bool is_lsm6dsm_mdf_settled(sns_ddf_handle_t dd_handle, filter_t filter)
{
  sns_dd_lsm6dsm_state_t* state = sns_dd_lsm6dsm_get_state(dd_handle);
  uint8_t samples_to_settle = 0;
  timer_msg_t timer_msg = SETTLING_SLOPE;
  sns_ddf_time_t cur_time, odr_time_elapsed, filter_settling_time;
  int64_t req_timeout;

  if(filter == SLOPE_FILTER) {
    samples_to_settle = SLOPE_SETTLING_SAMPLES;
    timer_msg = SETTLING_SLOPE;
  } else if(filter == HP_FILTER) {
    samples_to_settle = HPF_SETTLING_SAMPLES;
    timer_msg = SETTLING_HPF;
  }
  filter_settling_time = (samples_to_settle*1000000)/state->odr_list[state->acc_cur_rate_idx];
  cur_time = sns_ddf_get_timestamp();
  odr_time_elapsed = cur_time - state->acc_odr_ts;
  req_timeout = (int64_t) (sns_ddf_convert_usec_to_tick(filter_settling_time) - odr_time_elapsed);
  LSM6DSM_MSG_3(HIGH, "enable_md - cur_time(%u) acc_set_ts (%u) filter_set_time (%u)usec",
      cur_time, state->acc_odr_ts, filter_settling_time);

  if(req_timeout > 0) {
    sns_dd_lsm6dsm_create_timer(dd_handle, &state->md_timer, TICKS_TO_USEC(req_timeout), timer_msg, false);
    return false;
  } else
    return true;
}
void lsm6dsm_enable_mdf(sns_ddf_handle_t dd_handle, filter_t filter)
{
  sns_dd_lsm6dsm_state_t* state = sns_dd_lsm6dsm_get_state(dd_handle);
  uint8_t rw_buffer = 0;

  if(filter == HP_FILTER) {
    rw_buffer = 0x10;
  }
  sns_dd_lsm6dsm_write_reg(
      state,
      STM_LSM6DSM_REG_TAP_CFG,
      &rw_buffer,
      1,
      0x10);
}
#if 0
bool sns_dd_lsm6dsm_is_timer_valid(sns_ddf_handle_t dd_handle, stm_lsm6dsm_timer* timer_info)
{
  sns_dd_lsm6dsm_state_t* state = sns_dd_lsm6dsm_get_state(dd_handle);
  stm_lsm6dsm_timer* temp;
  for(temp=state->timer_list; temp && (temp != timer_info); temp=temp->next);
  return temp ? true : false;
}
#endif

/**
* @brief Called when the timer set by this driver has expired.This must be
*        the callback function submitted when initializing a timer.
*
*        Right now this timer handler is only used in selftest, where the timer
*        will be initialized
*
* Refer to sns_ddf_driver_if.h for definition.
*/

void sns_dd_lsm6dsm_handle_timer(
    sns_ddf_handle_t dd_handle,
    void* arg)
{
  uint8_t rw_buffer = 0;
  sns_ddf_status_e status = SNS_DDF_SUCCESS;
  sns_dd_lsm6dsm_state_t* state = sns_dd_lsm6dsm_get_state(dd_handle);
  stm_lsm6dsm_timer* timer_info = (stm_lsm6dsm_timer*) arg;

  if(arg == NULL)
    return sns_dd_lsm6dsm_handle_temp_timeout(dd_handle);

  LSM6DSM_MSG_3(HIGH, "Handle timer handle (%u) timer_info (%u) reason (%d)", dd_handle, timer_info, timer_info->reason);

  if(timer_info->reason == TEMP_DATA) {
    sns_dd_lsm6dsm_handle_temp_timeout(dd_handle);

    if(timer_info->repeat == false)
      sns_dd_lsm6dsm_destroy_timer(dd_handle, timer_info);

  } else if(timer_info->reason == SELFTEST_HW) {
    sns_dd_lsm6dsm_handle_selftest_timeout(dd_handle, arg);

    if(timer_info->repeat == false)
      sns_dd_lsm6dsm_destroy_timer(dd_handle, timer_info);
  } else if(timer_info->reason == SETTLING_SLOPE) {
      //cancle timer
      if(timer_info->repeat == false)
        sns_dd_lsm6dsm_destroy_timer(dd_handle, timer_info);

    if((state->md_desired == true) &&
        (state->md_enabled == false)) {

      //check hpf settling
      if(is_lsm6dsm_mdf_settled(dd_handle, HP_FILTER))
        lsm6dsm_enable_mdf(dd_handle, HP_FILTER);

      rw_buffer = 0x20; //setting wakeup
      status = sns_dd_lsm6dsm_write_reg(
          dd_handle,
          STM_LSM6DSM_REG_MD1_CFG,
          &rw_buffer,
          1,
          0x20);
      if(status != SNS_DDF_SUCCESS) {
        LSM6DSM_MSG_E_1(ERROR, "write reg failed  status=%u", status);
        return ;
      }
      state->md_enabled = true;
    }
  } else if(timer_info->reason == SETTLING_HPF) {
    //cancel timer
    if(timer_info->repeat == false)
      sns_dd_lsm6dsm_destroy_timer(dd_handle, timer_info);
    if((state->md_desired == true) &&
        (state->md_enabled == true)) {

      lsm6dsm_enable_mdf(dd_handle, HP_FILTER);
    }
  }
}

/**
 * @brief To search which sub device has a specific sensor.
 *
 * @param[in]  state               - Handle to a driver instance.
 * @param[in]  sensor            - the sensor type.
 * @param[out]  sub_dev_inx  - the index of sub_dev which contains this sensor.
 *
 * @return SNS_DDF_SUCCESS if this sensor is found. Otherwise return SNS_DDF_EFAIL.
 */
sns_ddf_status_e lsm6dsm_search_subdev_by_sensortype (
    sns_dd_lsm6dsm_state_t* state,
    sns_ddf_sensor_e sensor,
    uint32_t *sub_dev_inx)
{
  uint32_t i, j;
  stm_lsm6dsm_sub_dev_s *sub_dev_slot_ptr;

  for (i =0; i < LSM6DSM_MAX_SUB_DEV; i++)
  {
    sub_dev_slot_ptr = &state->sub_dev[i];
    for (j =0; j < sub_dev_slot_ptr->num_sensors; j++)
    {
      if(sensor == sub_dev_slot_ptr->sensors[j])
      {
        *sub_dev_inx = i;
        return SNS_DDF_SUCCESS;
      }
    }
  }

  return SNS_DDF_EFAIL;
}

/**
 * @brief write reg wrapper for write_port
 *
 * @param[in]  dd_handle   Handle to a driver instance.
 * @param[in]  reg_addr    The array of address
 * @param[in]  reg_value   The araay of values to update
 * @param[in]  bytes       The number of bytes in a array
 * @param[in]  mask        The mask of this register to specify which part to be updated
 *                         To be used only to update single register
 *
 * @return SNS_DDF_SUCCESS if this operation was done successfully. Otherwise
 *         SNS_DDF_EDEVICE, SNS_DDF_EBUS, SNS_DDF_EINVALID_PARAM, or SNS_DDF_EFAIL to
 *         indicate and error has occurred.
 */
sns_ddf_status_e sns_dd_lsm6dsm_write_reg(
    sns_ddf_handle_t dd_handle,
    uint8_t reg_addr,
    uint8_t* reg_value,
    uint8_t size,
    uint8_t mask)
{
  sns_dd_lsm6dsm_state_t* state = sns_dd_lsm6dsm_get_state(dd_handle);
  sns_ddf_status_e status;
  uint8_t rw_buffer = 0;
  uint8_t rw_bytes = 0;

  if((size > 1) || (mask == 0xFF) || (mask == 0x00)) {
    status = sns_ddf_write_port(
        state->port_handle,
        reg_addr,
        reg_value,
        size,
        &rw_bytes);
    if(status != SNS_DDF_SUCCESS) {
      LSM6DSM_MSG_E_1(ERROR, "write_port failed- status (%d)",status);
      return status;
    }
    if(rw_bytes!= size) {
      LSM6DSM_MSG_E_2(ERROR, "write_port failed- write bytes not match - rw_byest (%d) size (%d)",rw_bytes, size);
      return SNS_DDF_EBUS;
    }
  } else {
    // read current value from this register
    status = sns_ddf_read_port(
        state->port_handle,
        reg_addr,
        &rw_buffer,
        1,
        &rw_bytes);
    if(status != SNS_DDF_SUCCESS) {
      LSM6DSM_MSG_E_1(ERROR, "read_port failed- status (%d)",status);
      return status;
    }
    if(rw_bytes != 1) {
      LSM6DSM_MSG_E_1(ERROR, "read_port failed-  read_count  does not match - read_count (%d)",rw_bytes);
      return SNS_DDF_EBUS;
    }

    // generate new value
    rw_buffer = (rw_buffer & (~mask)) | (*reg_value & mask);

    // write new value to this register
    status = sns_ddf_write_port(
        state->port_handle,
        reg_addr,
        &rw_buffer,
        1,
        &rw_bytes);
    if(status != SNS_DDF_SUCCESS) {
      LSM6DSM_MSG_E_1(ERROR, "write_port failed- status (%d)",status);
      return status;
    }
    if(rw_bytes != 1) {
      LSM6DSM_MSG_E_1(ERROR, "write_port failed- write bytes not match - rw_byest (%d)",rw_bytes);
      return SNS_DDF_EBUS;
    }
  }
#if  DUMP_REGISTER_DATA
      LSM6DSM_MSG_3(HIGH, "reg_addr (0x%x) reg_val (0x%x) mask (0x%x)", reg_addr, reg_value[0], mask);
      sns_dd_lsm6dsm_dump_register_single(dd_handle, reg_addr, size);
#endif
  return SNS_DDF_SUCCESS;
}

/**
 * @brief Performs a set accelerometer data sampling rate operation
 *
 * @param[in]  dd_handle      Handle to a driver instance.
 * @param[in]  data_rate       Data sampling rate settings for LSM6DSM
 *
 * @return SNS_DDF_SUCCESS if this operation was done successfully. Otherwise
 *         SNS_DDF_EDEVICE, SNS_DDF_EBUS, SNS_DDF_EINVALID_PARAM, or SNS_DDF_EFAIL to
 *         indicate and error has occurred.
 */
sns_ddf_status_e sns_dd_acc_lsm6dsm_set_datarate(
    sns_ddf_handle_t dd_handle,
    int8_t rate_idx)
{
  sns_ddf_status_e status;
  sns_dd_lsm6dsm_state_t* state = sns_dd_lsm6dsm_get_state(dd_handle);
  uint8_t write_buffer = 0;
  uint32_t delay = 0;
   sns_ddf_time_t cur_time = 0;
  //few changes, need these below parameters to tune if required
  //1. use datarates 10 and 50 in calculating delay even when gyr is enabled.
  //this will gives little more delay
  //2. discard extra 1 more sample
  struct {
    uint32_t        odr;                /* in Hz */
    sns_ddf_odr_t   odr_reg_val;        /* register value */
    uint8_t         bw_reg_val;         /* register value for corresponding BW */
    uint32_t        samples_to_discard; /* samples to be discarded before ODR settled */
  } sns_dd_acc_lsm6dsm_odr_config_table[] =
  {
    { 13,  STM_LSM6DSM_ACC_ODR13,   STM_LSM6DSM_ACC_BW50,  2 },
    { 26,  STM_LSM6DSM_ACC_ODR26,   STM_LSM6DSM_ACC_BW50,  2 },
    { 52,  STM_LSM6DSM_ACC_ODR52,   STM_LSM6DSM_ACC_BW50,  2 },
    { 104, STM_LSM6DSM_ACC_ODR104,  STM_LSM6DSM_ACC_BW50,  3 },
    { 208, STM_LSM6DSM_ACC_ODR208,  STM_LSM6DSM_ACC_BW100, 4 },
    { 416, STM_LSM6DSM_ACC_ODR416,  STM_LSM6DSM_ACC_BW200, 2 },
    { 833, STM_LSM6DSM_ACC_ODR833,  STM_LSM6DSM_ACC_BW400, 2 },
    { 1660, STM_LSM6DSM_ACC_ODR1660, STM_LSM6DSM_ACC_BW400, 2 },
    { 3330, STM_LSM6DSM_ACC_ODR3330,  0x00, 2 },
    { 6660, STM_LSM6DSM_ACC_ODR6660,  0x00, 2 },
  };

  cur_time = sns_ddf_get_timestamp();

  if(rate_idx < 0) {

    if(state->acc_cur_rate_idx == rate_idx)
      return SNS_DDF_SUCCESS;
    LSM6DSM_MSG_2(HIGH, "SET_ACC_DATARATE - resetting/powering down rate idx (%d) cur_time (%u)",rate_idx, cur_time);
    write_buffer = (uint8_t)STM_LSM6DSM_ACC_ODR_OFF;
    status = sns_dd_lsm6dsm_write_reg(
        dd_handle,
        STM_LSM6DSM_REG_CTRL1_A,
        &write_buffer,
        1,
        STM_LSM6DSM_ODR_XL_MASK);
    if(status != SNS_DDF_SUCCESS)
      return status;
    if((state->acc_lp_mode) &&
        (state->acc_desired_rate_idx < 0) &&
        (state->fifo_info.acc_fifo_alive == false)) {
      write_buffer = 0x10;
      status = sns_dd_lsm6dsm_write_reg(
          dd_handle,
          STM_LSM6DSM_REG_CTRL6_G,
          &write_buffer,
          1,
          0x10);
      if(status != SNS_DDF_SUCCESS) {
        LSM6DSM_MSG_1(HIGH,"set acc performance failed - status (%d)",status);
        return status;
      }
    }

  } else {
    if(rate_idx > (STM_LSM6DSM_ODR_NUM - 1)) {
      LSM6DSM_MSG_E_1(ERROR, "SET_DATARATE - invalid index (%d) ", rate_idx);
      return SNS_DDF_EINVALID_PARAM;
    }
    if(rate_idx < state->min_supported_odr_idx)
      rate_idx = state->min_supported_odr_idx;

    if(state->acc_cur_rate_idx == rate_idx)
      return SNS_DDF_SUCCESS;


    //discard two samples of accels, accel is turning on
    if((state->gyr_cur_rate_idx >= 0) &&
        (state->gyr_sleep == false)){
      //gyro is on but not sleep
      delay = 4 * (sns_ddf_convert_usec_to_tick ( 1000000 / state->odr_list[state->gyr_cur_rate_idx]));
      if(state->gyr_odr_settled_ts < (cur_time + delay)) {
        state->gyr_odr_settled_ts =
          cur_time + delay ; /* in microseconds */

        LSM6DSM_DATA_MSG_3(HIGH,
            "set_datarate - acc entering/changing HP: gyro -updated-delays cur_time (%u) delay_us=(%u) tick odr_settled_ts=%u",
            cur_time, delay, state->gyr_odr_settled_ts);
      }
    } else if(state->gyr_sleep == true) {
      //if gyro is sleeping, keep gyro odr is same as accel odr
      write_buffer = (uint8_t)lsm6dsm_gyr_odr_reg_values[rate_idx];
      status = sns_dd_lsm6dsm_write_reg(
          dd_handle,
          STM_LSM6DSM_REG_CTRL2_G,
          &write_buffer,
          1,
          STM_LSM6DSM_ODR_G_MASK);
    }

    LSM6DSM_DATA_MSG_3(LOW, "SET_ACC_DATARATE - rate_idx (%d) data_rate_reg_value (0x%x) rate (%d)",rate_idx, lsm6dsm_acc_odr_reg_values[rate_idx], state->odr_list[rate_idx]);

    if((state->acc_lp_mode) &&
        (state->acc_desired_rate_idx >= 0)) {
      write_buffer = 0x00;
      status = sns_dd_lsm6dsm_write_reg(
          dd_handle,
          STM_LSM6DSM_REG_CTRL6_G,
          &write_buffer,
          1,
          0x10);
      if(status != SNS_DDF_SUCCESS) {
        LSM6DSM_MSG_1(HIGH,"set acc performance failed - status (%d)",status);
        return status;
      }
    }

    // Configure ODR in CTRL_ODR register
    //write_buffer = ((uint8_t)lsm6dsm_acc_odr_reg_values[rate_idx]| sns_dd_acc_lsm6dsm_odr_config_table[rate_idx].bw_reg_val);
    write_buffer = (uint8_t)lsm6dsm_acc_odr_reg_values[rate_idx];

    // Configure Bandwidth along with ODR.
    status = sns_dd_lsm6dsm_write_reg(
        dd_handle,
        STM_LSM6DSM_REG_CTRL1_A,
        &write_buffer,
        1,
        STM_LSM6DSM_ODR_XL_MASK);
    if(status != SNS_DDF_SUCCESS)
      return status;

    delay = sns_dd_acc_lsm6dsm_odr_config_table[rate_idx].samples_to_discard *
      (sns_ddf_convert_usec_to_tick ( 1000000 / sns_dd_acc_lsm6dsm_odr_config_table[rate_idx].odr)); /* in microseconds */

    state->acc_odr_ts =
      cur_time;
    state->acc_odr_settled_ts =
      cur_time + delay;

    LSM6DSM_MSG_3(HIGH,
        "A - set_datarate: rate (%d) delay_us=(%u) tick odr_settled_ts=%u",
        state->odr_list[rate_idx], delay, state->acc_odr_settled_ts);
  }
  state->acc_cur_rate_idx = rate_idx;
  return SNS_DDF_SUCCESS;

}
/**
 * @brief Performs a set gyrnetometer data sampling rate operation
 *
 * @param[in]  dd_handle      Handle to a driver instance.
 * @param[in]  data_rate       Data sampling rate settings for LSM6DSM
 *
 * @return SNS_DDF_SUCCESS if this operation was done successfully. Otherwise
 *         SNS_DDF_EDEVICE, SNS_DDF_EBUS, SNS_DDF_EINVALID_PARAM, or SNS_DDF_EFAIL to
 *         indicate and error has occurred.
 */
sns_ddf_status_e sns_dd_gyr_lsm6dsm_set_datarate(
    sns_ddf_handle_t dd_handle,
    int8_t rate_idx,
    bool sleep_mode)
{
  sns_dd_lsm6dsm_state_t* state = sns_dd_lsm6dsm_get_state(dd_handle);
  sns_ddf_status_e status;
  uint8_t write_buffer = 0;
  uint8_t rw_bytes = 0;
  sns_ddf_time_t cur_time = 0;

  uint32_t delay;
  cur_time = sns_ddf_get_timestamp();
  sns_ddf_time_t acc_st = 0;

  if(state->acc_cur_rate_idx >= 0)
    acc_st = sns_ddf_convert_usec_to_tick (1000000 / state->odr_list[state->acc_cur_rate_idx]);
  //setting sleep
  if(sleep_mode) {

    status = sns_ddf_read_port(
        state->port_handle,
        STM_LSM6DSM_REG_CTRL2_G,
        &write_buffer,
        1,
        &rw_bytes);
    if((status != SNS_DDF_SUCCESS) ||
        (rw_bytes != 1))
      return SNS_DDF_EBUS;
    if(!(write_buffer & STM_LSM6DSM_ODR_G_MASK)) {
      // Configure ODR in CTRL_ODR register
      write_buffer = (uint8_t)lsm6dsm_gyr_odr_reg_values[STM_LSM6DSM_ODR13];

      status = sns_dd_lsm6dsm_write_reg(
          dd_handle,
          STM_LSM6DSM_REG_CTRL2_G,
          &write_buffer,
          1,
          STM_LSM6DSM_ODR_G_MASK);
      if(status != SNS_DDF_SUCCESS)
        return status;
      //80ms
      delay =  sns_ddf_convert_usec_to_tick(80000) ;
      state->gyr_odr_settled_ts =
        cur_time + delay;

      LSM6DSM_DATA_MSG_2(HIGH,
          "set_datarate: gyro PD --- > sleep  using 80ms (%u) ticks turn on time gyr_odr_settled_ts (%u)", delay, state->gyr_odr_settled_ts);
    }
    write_buffer = 0x40;
    status = sns_dd_lsm6dsm_write_reg(
        dd_handle,
        STM_LSM6DSM_REG_CTRL4,
        &write_buffer,
        1,
        0x40);
    if(status != SNS_DDF_SUCCESS)
      return status;
    state->gyr_sleep = true;
    state->gyr_cur_rate_idx = -1;
    if(state->acc_cur_rate_idx >= 0) {
      delay =  2 * acc_st + sns_ddf_convert_usec_to_tick (20000);
      state->acc_odr_settled_ts =
        cur_time + delay;
      LSM6DSM_DATA_MSG_3(HIGH,
          "set_datarate - gyro PD ---> sleep: acc-updated-delays cur_time (%u) delay_us=(%u) tick odr_settled_ts=%u",
          cur_time, delay, state->acc_odr_settled_ts);
    }

  } else {

    if(rate_idx < 0) {

      write_buffer = 0x0;
      status = sns_dd_lsm6dsm_write_reg(
          dd_handle,
          STM_LSM6DSM_REG_CTRL4,
          &write_buffer,
          1,
          0x40);
      if(status != SNS_DDF_SUCCESS)
        return status;

      // Configure ODR in CTRL_ODR register
      write_buffer = STM_LSM6DSM_GYR_ODR_OFF;

      status = sns_dd_lsm6dsm_write_reg(
          dd_handle,
          STM_LSM6DSM_REG_CTRL2_G,
          &write_buffer,
          1,
          STM_LSM6DSM_ODR_G_MASK);
      if(status != SNS_DDF_SUCCESS)
        return status;
      // no impact on delays
      // sleep --> powerdown
      // on --> powerdown
      state->gyr_sleep = false;

    } else if (rate_idx >= 0) {

    if(rate_idx < state->min_supported_odr_idx)
      rate_idx = state->min_supported_odr_idx;

      if(state->gyr_cur_rate_idx == rate_idx)
        return SNS_DDF_SUCCESS;

      if(rate_idx > (STM_LSM6DSM_ODR_NUM - 1)) {
        LSM6DSM_MSG_E_1(ERROR, "SET_DATARATE - invalid index (%d) ", rate_idx);
        return SNS_DDF_EINVALID_PARAM;
      }

      LSM6DSM_DATA_MSG_2(LOW, "SET_GYR_DATARATE - data_rate_reg_value (%d) rate (%d)",lsm6dsm_gyr_odr_reg_values[rate_idx], state->odr_list[rate_idx]);

      //discard two samples of accels
      if(state->acc_cur_rate_idx >= 0) {
        if((state->gyr_sleep == true) ||
            (state->gyr_cur_rate_idx > 0)) {
          delay = 3 * acc_st;
          if(state->acc_odr_settled_ts < (cur_time + delay)) {
            state->acc_odr_settled_ts =
              cur_time + delay; /* in microseconds */
            LSM6DSM_DATA_MSG_3(HIGH,
                "set_datarate - gyro entering/changing HP: acc-updated-delays cur_time (%u) delay_us=(%u) tick odr_settled_ts=%u",
                cur_time, delay, state->acc_odr_settled_ts);
          }
        } else  if(state->gyr_cur_rate_idx < 0) {
          delay = 2 * acc_st + sns_ddf_convert_usec_to_tick (20000);

          if(state->acc_odr_settled_ts < (cur_time + delay)) {
            state->acc_odr_settled_ts =
              cur_time + delay; /* in microseconds */
            LSM6DSM_DATA_MSG_3(HIGH,
                "set_datarate - gyro entering/changing HP: acc-updated-delays cur_time (%u) delay_us=(%u) tick odr_settled_ts=%u",
                cur_time, delay, state->acc_odr_settled_ts);
          }
        }
      }
      // Configure ODR in CTRL_ODR register
      write_buffer = (uint8_t)lsm6dsm_gyr_odr_reg_values[rate_idx];

      status = sns_dd_lsm6dsm_write_reg(
          dd_handle,
          STM_LSM6DSM_REG_CTRL2_G,
          &write_buffer,
          1,
          STM_LSM6DSM_ODR_G_MASK);
      if(status != SNS_DDF_SUCCESS)
        return status;

      /* turn-on time is 80ms */
      if((state->gyr_sleep == false) &&
          (state->gyr_cur_rate_idx < 0)) {
        //70ms + 3 samples
        delay =  sns_ddf_convert_usec_to_tick(70000) +
          3 * sns_ddf_convert_usec_to_tick (1000000 / state->odr_list[rate_idx]);
        state->gyr_odr_settled_ts =
          cur_time + delay;
        LSM6DSM_DATA_MSG_2(HIGH,
            "set_datarate: gyro sleep false using 80ms (%u) ticks turn on time gyr_odr_settled_ts (%u)", delay, state->gyr_odr_settled_ts);
      } else {
        //gyr is in sleep mode
        //or gyr is changing odr
        write_buffer = 0x0;
        status = sns_dd_lsm6dsm_write_reg(
            dd_handle,
            STM_LSM6DSM_REG_CTRL4,
            &write_buffer,
            1,
            0x40);
        if(status != SNS_DDF_SUCCESS)
          return status;

        //if previous settled time is not past, still wait 80ms
        delay = 3 * sns_ddf_convert_usec_to_tick ( 1000000 / state->odr_list[rate_idx]); /* in microseconds */
        if((state->gyr_odr_settled_ts > cur_time) &&
            (state->gyr_odr_settled_ts > (cur_time + delay))) {
          LSM6DSM_DATA_MSG_2(HIGH,
              "set_datarate: using old settle time cur_time (%u) odr_settled_ts=%u",cur_time, state->gyr_odr_settled_ts);
        }
        else {
          LSM6DSM_DATA_MSG_0(HIGH,
              "set_datarate: using 3 samples turn on time");
          state->gyr_odr_settled_ts =
            cur_time + delay;

        }
      }
      state->gyr_sleep = false;
      LSM6DSM_MSG_3(HIGH,
          "G - set_datarate: rate (%d) delay (%u) tick odr_settled_ts=%u",
          state->odr_list[rate_idx], delay, state->gyr_odr_settled_ts);
    }
    state->gyr_cur_rate_idx = rate_idx;
  }

  return SNS_DDF_SUCCESS;
}

void sns_dd_lsm6dsm_handle_md_int(
    sns_ddf_handle_t  handle,
    sns_ddf_time_t    timestamp,
    bool* md_event)
{
  sns_dd_lsm6dsm_state_t* state;
  sns_ddf_status_e status;
  uint8_t rw_buffer = 0;
  uint8_t rw_bytes = 0;
  state = sns_dd_lsm6dsm_get_state(handle);

  if(false == state->md_enabled) {
    LSM6DSM_DATA_MSG_0(HIGH, "MD is not enabled - not initalizing");
    return;
  }

  status = sns_ddf_read_port(
        state->port_handle,
        STM_LSM6DSM_REG_WAKE_SRC,
        &rw_buffer,
        1,
        &rw_bytes);
    if(status != SNS_DDF_SUCCESS)
      return;
    if(rw_bytes != 1)
      return;
    if(rw_buffer & 0x08) {
      LSM6DSM_MSG_2(HIGH, "handle_md_int: time=%u wake_src (%x)", timestamp, rw_buffer);
      // verify motion detection interrupt by reading INT1_SRC.
      *md_event = true;
      }
}
static sns_ddf_status_e sns_dd_lsm6dsm_handle_esp_int(
    sns_ddf_handle_t dd_handle,
    sns_ddf_time_t    timestamp)
{
  sns_ddf_status_e status =  SNS_DDF_SUCCESS;
#if LSM6DSM_ENABLE_ESP
  sns_dd_lsm6dsm_state_t* state = sns_dd_lsm6dsm_get_state(dd_handle);
  uint32_t sub_dev_inx = 0;
  uint8_t rw_buffer[2];
  uint8_t rw_bytes = 0;
  uint8_t tap_data = 0;
  sns_ddf_sensor_data_s esp_data[LSM6DSM_MAX_ESP_SENSORS];
  sns_ddf_sensor_data_s* esp_data_ptr = &esp_data[0];
  sns_ddf_sensor_data_s* tmp_ptr = &esp_data[0];

  q16_t sample_d[STM_LSM6DSM_AXES_PER_SENSOR] = {0};

  if(state->esp_info.esp_enabled &
      (STM_LSM6DSM_BM_STC | STM_LSM6DSM_BM_STE |
       STM_LSM6DSM_BM_SMD | STM_LSM6DSM_BM_TILT)) {

    status = sns_ddf_read_port(
        state->port_handle,
        STM_LSM6DSM_REG_FUNC_SRC,
        rw_buffer,
        1,
        &rw_bytes);
    if((status != SNS_DDF_SUCCESS) ||
        (rw_bytes != 1))
      return SNS_DDF_EFAIL;

    if(rw_buffer[0] & 0x10) {
      if(state->esp_info.esp_enabled & STM_LSM6DSM_BM_STC) {
        esp_data_ptr++->sensor = SNS_DDF_SENSOR_STEP_COUNT;
      }
      if(state->esp_info.esp_enabled & STM_LSM6DSM_BM_STE) {
        esp_data_ptr++->sensor = SNS_DDF_SENSOR_STEP_EVENT;
      }
      if(state->esp_info.esp_enabled & STM_LSM6DSM_BM_SMD) {
        esp_data_ptr++->sensor = SNS_DDF_SENSOR_SMD;
      }
    }
    if(state->esp_info.esp_enabled & STM_LSM6DSM_BM_TILT) {
      if(rw_buffer[0] & 0x20) {
        esp_data_ptr++->sensor = SNS_DDF_SENSOR_TILT_EVENT;
      }
    }
  }

  if(state->esp_info.esp_enabled & STM_LSM6DSM_BM_D6D) {
    status = sns_ddf_read_port(
        state->port_handle,
        STM_LSM6DSM_REG_D6D_SRC,
        rw_buffer,
        1,
        &rw_bytes);
    if((status != SNS_DDF_SUCCESS) ||
        (rw_bytes != 1))
      return SNS_DDF_EFAIL;

    if((rw_buffer[0] & 0x40) &&
        (rw_buffer[0] & 0x3F)) {
      esp_data_ptr++->sensor = SNS_DDF_SENSOR_D6D_EVENT;
    }
  }

  if(state->esp_info.esp_enabled & STM_LSM6DSM_BM_DBT) {
    status = sns_ddf_read_port(
        state->port_handle,
        STM_LSM6DSM_REG_TAP_SRC,
        rw_buffer,
        1,
        &rw_bytes);
    if((status != SNS_DDF_SUCCESS) ||
        (rw_bytes != 1))
      return SNS_DDF_EFAIL;

    if((rw_buffer[0] & 0x40) &&
        (rw_buffer[0] & 0x10)) {
      esp_data_ptr++->sensor = SNS_DDF_SENSOR_DOUBLETAP;
      tap_data = rw_buffer[0];
    }
  }
  for(; tmp_ptr < esp_data_ptr; tmp_ptr++) {
    status = lsm6dsm_search_subdev_by_sensortype(
        state,
        tmp_ptr->sensor,
        &sub_dev_inx);
    if(status != SNS_DDF_SUCCESS)
      return status;

    LSM6DSM_MSG_2(LOW, "handle_esp_int sensor %d sub_dev_idx %d", tmp_ptr->sensor, sub_dev_inx);

    status = sns_dd_lsm6dsm_malloc((void**)&(tmp_ptr->samples),
        4 * sizeof(sns_ddf_sensor_sample_s), state->sub_dev[sub_dev_inx].smgr_handle);
    if(status != SNS_DDF_SUCCESS) {
      return SNS_DDF_ENOMEM;
    }
    memset(tmp_ptr->samples, 0, 4 * sizeof(sns_ddf_sensor_sample_s));

    tmp_ptr->status = SNS_DDF_SUCCESS;
    tmp_ptr->timestamp = timestamp;

    //Fill out sensor output data and status
    if((tmp_ptr->sensor == SNS_DDF_SENSOR_SMD) ||
        (tmp_ptr->sensor == SNS_DDF_SENSOR_TILT_EVENT) ||
        (tmp_ptr->sensor == SNS_DDF_SENSOR_D6D_EVENT) ||
        (tmp_ptr->sensor == SNS_DDF_SENSOR_STEP_EVENT)) {
      tmp_ptr->samples[0].sample = 1;
      tmp_ptr->samples[0].status = SNS_DDF_SUCCESS;
      tmp_ptr->num_samples = 1;
    } else if(tmp_ptr->sensor == SNS_DDF_SENSOR_STEP_COUNT) {

      status = sns_ddf_read_port(
          state->port_handle,
          STM_LSM6DSM_REG_STEP_COUNTER_L,
          rw_buffer,
          2,
          &rw_bytes);
      if(status != SNS_DDF_SUCCESS) {
        LSM6DSM_MSG_E_0(ERROR, "returned error");
        return status;
      }
      if(rw_bytes != 2) {
        LSM6DSM_MSG_E_0(ERROR, "returned error");
        return SNS_DDF_EBUS;
      }

      LSM6DSM_MSG_3(HIGH, "handle_esp_int - step count L (%d) H(%d) step_count(%d) ", rw_buffer[0], rw_buffer[1], ((rw_buffer[1] << 8) | rw_buffer[0]));
      tmp_ptr->samples[0].sample = FX_CONV_Q16((int16_t)(rw_buffer[1] << 8 | rw_buffer[0]), 0);
      tmp_ptr->samples[0].status = SNS_DDF_SUCCESS;
      tmp_ptr->num_samples = 1;


    } else if(tmp_ptr->sensor == SNS_DDF_SENSOR_DOUBLETAP) {

      if(tap_data & 0x04)
        sample_d[0] = SNS_DDF_TAP_DIR_X;
      else if(tap_data & 0x02)
        sample_d[0] = SNS_DDF_TAP_DIR_Y;
      else if(tap_data & 0x01)
        sample_d[0] = SNS_DDF_TAP_DIR_Z;

      LSM6DSM_MSG_2(LOW, "handle_esp_int - Double Tap data (0x%x) s_0 (0x%x) ", tap_data, sample_d[0]);
      //sns_ddf_map_axes(&state->axes_map, sample_d);
      tmp_ptr->samples[0].sample = sample_d[0];
      tmp_ptr->samples[0].status = SNS_DDF_SUCCESS;
      tmp_ptr->num_samples = 1;
    }

    status = sns_ddf_smgr_notify_data(
        state->sub_dev[sub_dev_inx].smgr_handle,
        tmp_ptr,
        1);
#if STM_LSM6DSM_LOGDATA
    sns_dd_lsm6dsm_log_data(tmp_ptr, true);
#endif

    sns_dd_lsm6dsm_mfree(tmp_ptr->samples,
        state->sub_dev[sub_dev_inx].smgr_handle);
  }
#endif
  return status;
}

/**
 * @brief Called in response to an motion detection interrupt for this driver.
 *
 * @param[in]  dd_handle    Handle to a driver instance.
 * @param[in]  gpio_num     GPIO number that generated the interrupt.
 * @param[in]  timestamp    Time at which ISR is called
 *
 * @return none
 * */

void sns_dd_lsm6dsm_handle_irq(
    sns_ddf_handle_t  dd_handle,
    uint32_t          gpio_num,
    sns_ddf_time_t    timestamp)
{
  sns_dd_lsm6dsm_state_t* state = sns_dd_lsm6dsm_get_state(dd_handle);
  //flag for the while loop to read out any new data samples during previous INT handling.
  bool run_again = true;
  bool md_event = false;
  //how many times fifo_read happens
  if(dd_handle==NULL)
  {
    LSM6DSM_MSG_E_0(ERROR, "handle_irq: Received Null Pointer.");
    return;
  }
  LSM6DSM_DATA_MSG_3(HIGH, "handle_irq: CPU IRQ time=%u cur_time (%u) gpio (%d)",
      timestamp, sns_ddf_get_timestamp(), gpio_num);

  if (gpio_num != state->gpio_num)
    return;
  state->fifo_info.first_pass = true;
  while(run_again)
  {
    run_again = false;

    //motion detection interrupt handling.
    if(state->fifo_info.first_pass == true) {
      sns_dd_lsm6dsm_handle_md_int(dd_handle, timestamp, &md_event);
      if(LSM6DSM_IS_ESP_ACTIVE(state->esp_info))
        sns_dd_lsm6dsm_handle_esp_int(dd_handle, timestamp);
    }
    sns_dd_lsm6dsm_handle_fifo_int(dd_handle, timestamp, &run_again);
  }
  //send md event at the end of handle irq
  //smgr might disable md and can close at the same context
  //which might take few msec
  if(md_event) {
    // motion detected, send an event to SMGR
    sns_dd_lsm6dsm_send_event_smgr(dd_handle,
        SNS_DDF_SENSOR_ACCEL,
        SNS_DDF_EVENT_MOTION);
  }

  LSM6DSM_DATA_MSG_2(HIGH, "handle_irq EXIT: DD ISR cur_time %u last_timestamp=%u", sns_ddf_get_timestamp(), state->fifo_info.last_timestamp);
}


/*===========================================================================
FUNCTION:   sns_dd_lsm6dsm_log_data
===========================================================================*/
/*!
  @brief log sensor data

  @detail
  - Logs latest set of sensor data sampled from the sensor.

  @param[in] data_ptr: ptr to the driver data
  */
/*=========================================================================*/
#if STM_LSM6DSM_LOGDATA
void sns_dd_lsm6dsm_log_data(sns_ddf_sensor_data_s *data_ptr, bool fifo_mode)
{
  sns_err_code_e err_code;
  sns_log_sensor_data_pkt_s* log_struct_ptr = NULL;
  uint16 idx =0 ;
  // do not change
  uint32_t num_samples = 1;
  if((!data_ptr) ||
      (data_ptr->status != SNS_DDF_SUCCESS)) {
    LSM6DSM_DATA_MSG_2(HIGH, "Not logging - sensor (%d) status (%u) ", data_ptr->sensor, data_ptr->status);
    return;
  }
  if(fifo_mode)
    num_samples = data_ptr->num_samples;
  //Allocate log packet
  err_code = sns_logpkt_malloc(SNS_LOG_CONVERTED_SENSOR_DATA,
      sizeof(sns_log_sensor_data_pkt_s) + (num_samples -1)*sizeof(int32_t),
      (void**)&log_struct_ptr);

  if ((err_code == SNS_SUCCESS) && (log_struct_ptr != NULL))
  {
    log_struct_ptr->version = SNS_LOG_SENSOR_DATA_PKT_VERSION;
    log_struct_ptr->sensor_id = data_ptr->sensor;
    log_struct_ptr->vendor_id = SNS_DDF_VENDOR_STMICRO;

    //Timestamp the log with sample time
    log_struct_ptr->timestamp = data_ptr->timestamp;
    log_struct_ptr->end_timestamp = data_ptr->timestamp;
    if(fifo_mode)
      log_struct_ptr->end_timestamp = data_ptr->end_timestamp;

    //Log the sensor data
    log_struct_ptr->num_data_types = (data_ptr->num_samples > 1) ?
                                     STM_LSM6DSM_AXES_PER_SENSOR : 1;
    //non-fifo mode, num_samples should be 0
    if(!fifo_mode)
      log_struct_ptr->num_samples = 0;
    else if(data_ptr->sensor != SNS_DDF_SENSOR_TEMP) //assuming all sensor data has 3-axis except temp
        log_struct_ptr->num_samples = num_samples / STM_LSM6DSM_AXES_PER_SENSOR;
    else
        log_struct_ptr->num_samples = num_samples;
    log_struct_ptr->data[0]  = data_ptr->samples[0].sample;
    log_struct_ptr->data[1]  = data_ptr->samples[1].sample;
    log_struct_ptr->data[2]  = data_ptr->samples[2].sample;
    if(fifo_mode) {
      for(idx=0; idx<data_ptr->num_samples; idx++)
      {
        log_struct_ptr->samples[idx]  = data_ptr->samples[idx].sample;
      }
    }
    //Commit log (also frees up the log packet memory)
    (void) sns_logpkt_commit(SNS_LOG_CONVERTED_SENSOR_DATA,
        log_struct_ptr);
  } else
    LSM6DSM_DATA_MSG_2(HIGH, "Not logging - sensor (%d) status (%u) ", data_ptr->sensor, data_ptr->status);
}
#endif
#if LSM6DSM_ENABLE_HUB
static sns_ddf_status_e sns_dd_lsm6dsm_hub_get_data(
    sns_ddf_handle_t dd_handle,
    sns_ddf_sensor_e sensors[],
    uint32_t num_sensors,
    sns_ddf_memhandler_s* memhandler,
    sns_ddf_sensor_data_s** data)
{
  sns_ddf_time_t timestamp;
  sns_ddf_status_e status;
  sns_ddf_sensor_data_s *data_ptr;
  sns_dd_lsm6dsm_state_t *state = sns_dd_lsm6dsm_get_state(dd_handle);
  // SAE coordinate x,y,z axis data
  int16_t adc[LSM6DSM_SLAVE_1_AXES] = { 0 };
  uint8_t raw_data[LSM6DSM_SLAVE_1_OUTDATA_LEN] = {0};
  q16_t sae_d[LSM6DSM_SLAVE_1_AXES];
  sns_ddf_time_t odr_settled_ts = state->hub_info.odr_settled_ts;
  uint32_t sub_dev_idx;
  uint8_t i = 0;
  uint16_t num_samples = 0;
  uint8_t read_count = 0;

  status = lsm6dsm_search_subdev_by_sensortype(
      state,
      sensors[0],
      &sub_dev_idx);
  if(status != SNS_DDF_SUCCESS)
    return status;

  LSM6DSM_DATA_MSG_2(HIGH, "get_data p_sensors (%d) num_sensors %d",  sensors[0], num_sensors);
  //LSM6DSM_MSG_1(LOW, "GET_DATA - num_sensors (%d)",num_sensors);
  //allocate memory for sns_ddf_sensor_data_s data structure
  data_ptr = sns_dd_lsm6dsm_memhandler_malloc(memhandler, num_sensors * sizeof(sns_ddf_sensor_data_s), state->sub_dev[sub_dev_idx].smgr_handle);
  if(NULL == data_ptr)
  {
    LSM6DSM_MSG_E_0(ERROR, "Malloc failed ");
    return SNS_DDF_ENOMEM;
  }
  *data = data_ptr;

  // get current time stamp
  timestamp = sns_ddf_get_timestamp();
  num_samples = LSM6DSM_SLAVE_1_AXES; //num samples = no of sensor axes

  status = sns_ddf_read_port(
        state->port_handle,
        STM_LSM6DSM_REG_SENSOR_HUB1,
        raw_data,
        LSM6DSM_SLAVE_1_OUTDATA_LEN,
        &read_count);
    if(status != SNS_DDF_SUCCESS) {
      LSM6DSM_MSG_E_1(ERROR, "read_port failed- status (%d)",status);
      return status;
    }
    if(read_count != LSM6DSM_SLAVE_1_OUTDATA_LEN) {
      LSM6DSM_MSG_E_1(ERROR, "read_port failed-  read_count  does not match - read_count (%d)",read_count);
      return status;
    }
     data_ptr->samples = sns_dd_lsm6dsm_memhandler_malloc(memhandler, LSM6DSM_SLAVE_1_AXES * sizeof(sns_ddf_sensor_sample_s), state->sub_dev[sub_dev_idx].smgr_handle);
      if(NULL == data_ptr->samples)
      {
        LSM6DSM_DATA_MSG_3(HIGH, "get_data: sensor (%d) num_samples (%d) odr_settled_ts (%u)", data_ptr->sensor, num_samples, odr_settled_ts);
        LSM6DSM_MSG_E_0(ERROR, "Malloc failed ");
        return SNS_DDF_ENOMEM;
      }
      data_ptr->sensor = LSM6DSM_SLAVE_SENSOR;
      data_ptr->timestamp = timestamp;
      data_ptr->status = SNS_DDF_SUCCESS;
      if((int64_t)(odr_settled_ts - data_ptr->timestamp) > 0) {
        LSM6DSM_DATA_MSG_1(HIGH, "Invalidating sample at time: %u", data_ptr->timestamp);
        data_ptr->status = SNS_DDF_EINVALID_DATA;
      }
      for(i=0; i<num_samples; i++) {
        adc[i] = (int16_t) (((uint16_t)(raw_data[i*2 + 1]) << 8) | ((uint16_t)raw_data[i*2 + 0]));
        sae_d[i] = FX_FLTTOFIX_Q16(adc[i] * state->hub_info.sstvt);
      }

      LSM6DSM_DATA_MSG_3(HIGH, "MAG_DATA raw (%d) (%d) %d)", raw_data[0], raw_data[1], raw_data[2]);
      LSM6DSM_DATA_MSG_3(HIGH, "MAG_DATA raw (%d) (%d) %d)", raw_data[3], raw_data[4], raw_data[5]);
      LSM6DSM_DATA_MSG_3(HIGH, "MAG_DATA adc (%d) (%d) %d)", adc[0], adc[1], adc[2]);
      LSM6DSM_DATA_MSG_3(HIGH, "MAG_DATA sae_d(%d) (%d) %d)", sae_d[0], sae_d[1], sae_d[2]);

      sns_ddf_map_axes(&state->hub_info.axes_map, sae_d);
      for(i=0; i<num_samples; i++) {
        data_ptr->samples[i].sample = sae_d[i];
        data_ptr->samples[i].status = data_ptr->status;
      }
      data_ptr->num_samples = num_samples;
#if STM_LSM6DSM_LOGDATA
    sns_dd_lsm6dsm_log_data(data_ptr, false);
#endif
    return status;
}
#endif
/**
 * @brief Retrieves a single set of sensor data from lsm6dsm.
 *
 * Refer to sns_ddf_driver_if.h for definition.
 */
static sns_ddf_status_e sns_dd_lsm6dsm_get_data(
    sns_ddf_handle_t dd_handle,
    sns_ddf_sensor_e sensors[],
    uint32_t num_sensors,
    sns_ddf_memhandler_s* memhandler,
    sns_ddf_sensor_data_s** data)
{
  sns_ddf_time_t timestamp;
  sns_ddf_status_e status;
  sns_ddf_sensor_data_s *data_ptr;
  sns_dd_lsm6dsm_state_t *state;
  // SAE coordinate x,y,z axis data
  q16_t sae_d[7] = { 0 };
  sns_ddf_time_t odr_settled_ts = 0;
  uint32_t sub_dev_idx;
  uint8_t s_pattern = 0x0, buf_idx = 0, num_samples = 0, p_idx=0;
  uint8_t i = 0, j = 0;
  uint16_t read_bytes = 0;

  state = sns_dd_lsm6dsm_get_state(dd_handle);

#if LSM6DSM_ENABLE_HUB
  //consider there is only on slave sensors
  if(LSM6DSM_IS_HUB_SLV_SENSOR(sensors[0])) {
    return sns_dd_lsm6dsm_hub_get_data(dd_handle, sensors, num_sensors, memhandler, data);
  }
#endif
  status = lsm6dsm_search_subdev_by_sensortype(
      state,
      sensors[0],
      &sub_dev_idx);
  if(status != SNS_DDF_SUCCESS)
    return status;

  LSM6DSM_DATA_MSG_2(HIGH, "get_data p_sensors (%d) num_sensors %d",  sensors[0], num_sensors);
  //LSM6DSM_MSG_1(LOW, "GET_DATA - num_sensors (%d)",num_sensors);
  //allocate memory for sns_ddf_sensor_data_s data structure
  data_ptr = sns_dd_lsm6dsm_memhandler_malloc(memhandler, num_sensors * sizeof(sns_ddf_sensor_data_s), state->sub_dev[sub_dev_idx].smgr_handle);
  if(NULL == data_ptr)
  {
    LSM6DSM_MSG_E_0(ERROR, "Malloc failed ");
    return SNS_DDF_ENOMEM;
  }
  *data = data_ptr;

  // get current time stamp
  timestamp = sns_ddf_get_timestamp();

  read_bytes = sns_dd_lsm6dsm_read_out_data(dd_handle, sensors, num_sensors, sae_d, &s_pattern);
  if(read_bytes == 0) {
    LSM6DSM_MSG_E_3(ERROR, "get_data read bytes (%d) p_sensors (%d) num_sensors %d", read_bytes, sensors[0], num_sensors);
    return SNS_DDF_EINVALID_DATA;
  }

  LSM6DSM_DATA_MSG_2(HIGH, "get_data read_bytes (%d) s_pattern (%d)",  read_bytes, s_pattern);
  for(i = 0; i < 3; i++) {
    p_idx = (TEMP_A_FIFO_BM >> i);
    if(s_pattern & p_idx) {
      if(p_idx == TEMP_A_FIFO_BM) {
        data_ptr->sensor = SNS_DDF_SENSOR_TEMP;
        num_samples = 1;
        odr_settled_ts = timestamp;
      } else if(p_idx == GYRO_FIFO_BM) {
        data_ptr->sensor = SNS_DDF_SENSOR_GYRO;
        num_samples = STM_LSM6DSM_AXES_PER_SENSOR;
        odr_settled_ts = state->gyr_odr_settled_ts;
      } else {
        data_ptr->sensor = SNS_DDF_SENSOR_ACCEL;
        num_samples = STM_LSM6DSM_AXES_PER_SENSOR;
        odr_settled_ts = state->acc_odr_settled_ts;
      }

      data_ptr->samples = sns_dd_lsm6dsm_memhandler_malloc(memhandler, num_samples* sizeof(sns_ddf_sensor_sample_s), state->sub_dev[sub_dev_idx].smgr_handle);
      if(NULL == data_ptr->samples)
      {
        LSM6DSM_DATA_MSG_3(HIGH, "get_data: sensor (%d) num_samples (%d) odr_settled_ts (%u)", data_ptr->sensor, num_samples, odr_settled_ts);
        LSM6DSM_MSG_E_0(ERROR, "Malloc failed ");
        return SNS_DDF_ENOMEM;
      }
      data_ptr->timestamp = timestamp;
      data_ptr->status = SNS_DDF_SUCCESS;
      if((int64_t)(odr_settled_ts - data_ptr->timestamp) > 0) {
        LSM6DSM_DATA_MSG_1(HIGH, "Invalidating sample at time: %u", data_ptr->timestamp);
        data_ptr->status = SNS_DDF_EINVALID_DATA;
      }

      for(j=0;j<num_samples;j++) {
        if( buf_idx< 7 ) {
          data_ptr->samples[j].sample = sae_d[buf_idx++];
          data_ptr->samples[j].status = data_ptr->status;
        }
      }
      data_ptr->num_samples = num_samples;

#if STM_LSM6DSM_LOGDATA
    sns_dd_lsm6dsm_log_data(data_ptr, false);
#endif
      data_ptr++;
    }
  }

  return SNS_DDF_SUCCESS;
}

sns_ddf_status_e sns_dd_lsm6dsm_set_attr_uimg(
    sns_ddf_handle_t dd_handle,
    sns_ddf_sensor_e sensor,
    sns_ddf_attribute_e attrib,
    void* value)
{
  uint32_t sub_dev_idx;
  sns_ddf_status_e  status = SNS_DDF_SUCCESS;
  sns_ddf_sensor_e ddf_sensor_type;

  LSM6DSM_MSG_2(LOW, "SET_ATTRIB attrib (%d) sensor (%d)",attrib, sensor);
  if (dd_handle == NULL || value == NULL) {
    LSM6DSM_MSG_E_0(ERROR, "dd_handle is NULL");
    return SNS_DDF_EINVALID_PARAM;
  }

  sns_dd_lsm6dsm_state_t* state = sns_dd_lsm6dsm_get_state(dd_handle);
  sub_dev_idx = (dd_handle_align_t)dd_handle & (~DD_HANDLE_ALIGN_BITS);
  ddf_sensor_type = state->sub_dev[sub_dev_idx].sensors[0]; // '0' --> Primary

  switch(attrib)
  {
    case SNS_DDF_ATTRIB_S4S_ST:
      // TODO: Handle both accel & gyro
      if(MAX(state->acc_cur_rate_idx, state->gyr_cur_rate_idx) > STM_LSM6DSM_ODR208)
        return status;
      //if ST already sent for one sensor ignore for other sensor
      if ((ddf_sensor_type == SNS_DDF_SENSOR_ACCEL) ||
          (ddf_sensor_type == SNS_DDF_SENSOR_GYRO)) {

        LSM6DSM_DATA_MSG_3(HIGH," Got ST - sbsp_sensor %d stdt_sensor %d sensor %d",
            state->s4s_config.sensor_sbsp, state->s4s_config.stdt_sensor, ddf_sensor_type );
        if( state->s4s_config.stdt_sensor == SNS_DDF_SENSOR__NONE )
        {
          state->s4s_config.stdt_sensor = ddf_sensor_type;
          LSM6DSM_MSG_E_1(HIGH,"Setting stdt_sensor %d", state->s4s_config.stdt_sensor);
        }
        if(ddf_sensor_type == state->s4s_config.stdt_sensor) {

          // The LSM6DSM doesn't support sending a stand-alone ST.
          // Only save the ideal sync time here
          // Otherwise, would send the ST and calculate DT value here.
          if( state->s4s_config.curr_sync_time != *((sns_ddf_st_t*)value) )
          {
            state->s4s_config.pending_sync_time = *((sns_ddf_st_t*)value);
            state->s4s_config.skip_dt = false;
            LSM6DSM_MSG_E_1(HIGH,"Setting pending sync time %u", state->s4s_config.pending_sync_time );
          }
          else
          {
            state->s4s_config.skip_dt = true;
          }
        }
      }
      break;
    case SNS_DDF_ATTRIB_S4S_DT:
      if( state->s4s_config.stdt_sensor == SNS_DDF_SENSOR__NONE )
      {
        status = SNS_DDF_EINVALID_PARAM;
      }
      if(MAX(state->acc_cur_rate_idx, state->gyr_cur_rate_idx) > STM_LSM6DSM_ODR208)
        return status;
      if ((ddf_sensor_type == SNS_DDF_SENSOR_ACCEL) ||
          (ddf_sensor_type == SNS_DDF_SENSOR_GYRO))
      {
        sns_ddf_dt_t s4s_dt_abort = !(*(sns_ddf_dt_t*)value);
        uint8_t dt_w_buffer;
        uint8_t dt_w_abort_buffer = 0x80;
        static uint8_t st_w_buffer = 0xCC;
        sns_ddf_time_t now = 0, start_time;
        sns_ddf_rw_port_s stdt_txn[6];
        int32_t write_count;
        int index = 0;
        uint8_t tph = state->s4s_config.t_ph_reg_value;
        uint8_t rr = state->s4s_config.rr;

        LSM6DSM_DATA_MSG_4(HIGH," Got DT - sbsp_sensor %d stdt_sensor %d sensor %d abort %d",
                           state->s4s_config.sensor_sbsp, state->s4s_config.stdt_sensor,
                           ddf_sensor_type, s4s_dt_abort );
        //skip DT if other sensor is syncing, asuming sync sensor is already set in
        //ST attrib
        if(state->s4s_config.stdt_sensor != ddf_sensor_type) {
          LSM6DSM_MSG_E_2(HIGH,"Skipping DT command stdt_sensor %d sensor %d",
            state->s4s_config.stdt_sensor, ddf_sensor_type );
          status = SNS_DDF_SUCCESS;
          break;
        }

        if( state->s4s_config.skip_dt == true /*|| s4s_dt_abort == true*/)
        {
          LSM6DSM_MSG_E_2(HIGH,"Skipping DT command skip:%d abort:%d",
              state->s4s_config.skip_dt,s4s_dt_abort);

          status = SNS_DDF_EDT_NOT_SENT;
          break;
        }

        if( (state->s4s_config.curr_sync_time+state->s4s_config.ideal_sync_interval !=
              state->s4s_config.pending_sync_time ) &&
            state->s4s_config.synced != STM_LSM6DSM_S4S_NOT_SYNCED )
        {
          LSM6DSM_MSG_E_2(HIGH,"Aborting sched current time %u pending %u.",
              state->s4s_config.curr_sync_time,
              state->s4s_config.pending_sync_time );
          stdt_txn[index].is_write = true;
          stdt_txn[index].reg_addr = STM_LSM6DSM_REG_ST;
          stdt_txn[index].buffer   = &st_w_buffer;
          stdt_txn[index].bytes    = 1;
          index++;
          stdt_txn[index].is_write = true;
          stdt_txn[index].reg_addr = STM_LSM6DSM_REG_DT;
          stdt_txn[index].buffer   = &dt_w_abort_buffer;
          stdt_txn[index].bytes    = 1;
          status = sns_ddf_rw_port_v( state->port_handle,
              stdt_txn, index+1,
              &write_count, NULL );
          index = 0;
          //state->s4s_config.synced = STM_LSM6DSM_S4S_NOT_SYNCED;
        }
        stdt_txn[index].is_write = true;
        stdt_txn[index].reg_addr = STM_LSM6DSM_REG_ST;
        stdt_txn[index].buffer   = &st_w_buffer;
        stdt_txn[index].bytes    = 1;

        if( state->s4s_config.config_changed == true )
        {
          index++;
          stdt_txn[index].is_write = true;
          stdt_txn[index].reg_addr = STM_LSM6DSM_REG_T_PH;
          stdt_txn[index].buffer   = &tph;
          stdt_txn[index].bytes    = 1;
          index++;
          stdt_txn[index].is_write = true;
          stdt_txn[index].reg_addr = STM_LSM6DSM_REG_RR;
          stdt_txn[index].buffer   = &rr;
          stdt_txn[index].bytes    = 1;

          state->s4s_config.config_changed = false;
          LSM6DSM_MSG_E_2(HIGH,"wrote tph %d rr %d",
                          tph, rr);
        }

        index++;
        stdt_txn[index].is_write = true;
        stdt_txn[index].reg_addr = STM_LSM6DSM_REG_DT;
        stdt_txn[index].buffer   = &dt_w_buffer;
        stdt_txn[index].bytes    = 1;
        /*
          index++;
          stdt_txn[index].is_write = false;
          stdt_txn[index].reg_addr = STM_LSM6DSM_REG_ST;
          stdt_txn[index].buffer   = &st_r_buffer;
          stdt_txn[index].bytes    = 1;
        */
        if( st_w_buffer == 0xCD ) {
          st_w_buffer = 0xCC; // Spec says 0xCC and 0xCD are OK values
        } else {
          st_w_buffer = 0xCD;
        }
        // Calculate DT value
        if( s4s_dt_abort == false ) {
          start_time = sns_ddf_get_timestamp();
          do {
            // To get a bit better accuracy, start exactly on the next tick edge
            now = sns_ddf_get_timestamp();
          } while ( now == start_time );
          // Assume it'll take 3 ticks to do the below calculations and start
          // sending the ST command on the bus
          now+=3;
          state->s4s_config.dt_value = (uint32_t)((float)(now-state->s4s_config.pending_sync_time)
                                                  / state->s4s_config.ticks_per_rr );
        }
        if( state->s4s_config.dt_value > 0xFF || s4s_dt_abort == true ) {
          // If the DT value is enormous, set the high bit to indicate an
          // abort.
          state->s4s_config.dt_value = 0x80;
        }

        dt_w_buffer = (uint8_t)state->s4s_config.dt_value;
        // This part requires the ST & DT happen in one transaction.
        status = sns_ddf_rw_port_v( state->port_handle,
                                    stdt_txn, index+1,
                                    &write_count, NULL );
        if(status != SNS_DDF_SUCCESS || write_count != (index+1)*2) {
          LSM6DSM_MSG_E_3(ERROR, "write_reg failed addr 0x%x- status %d count %d",
                          STM_LSM6DSM_REG_DT, status, write_count);
        } else {
          LSM6DSM_MSG_E_1(HIGH,"Sent DT with value %d",
                          state->s4s_config.dt_value);
        }
        /*
          LSM6DSM_MSG_E_1(HIGH,"st read value %d",
          st_r_buffer);
        */
        if( state->s4s_config.dt_value > 127 ) {
          LSM6DSM_MSG_E_0(HIGH,"Notifying SMGR of DT Abort");

          sns_dd_lsm6dsm_send_event_smgr(dd_handle,
                                         ddf_sensor_type,
                                         SNS_DDF_EVENT_DT_ABORT );

          status = SNS_DDF_EDT_ABORT;
        } else if( state->s4s_config.synced == STM_LSM6DSM_S4S_NOT_SYNCED ) {
          state->s4s_config.curr_sync_time = state->s4s_config.pending_sync_time;
          state->s4s_config.synced = STM_LSM6DSM_S4S_SYNCING;
        } else if( state->s4s_config.synced == STM_LSM6DSM_S4S_SYNCING ) {
          state->s4s_config.curr_sync_time = state->s4s_config.pending_sync_time;
          state->s4s_config.synced = STM_LSM6DSM_S4S_1ST_SYNCED;
          // TODO: Should check to see if the ODR actually changed...
          sns_dd_lsm6dsm_send_event_smgr(dd_handle,
                                         ddf_sensor_type,
                                         SNS_DDF_EVENT_ODR_CHANGED );
        } else {
          state->s4s_config.curr_sync_time = state->s4s_config.pending_sync_time;
          state->s4s_config.synced = STM_LSM6DSM_S4S_SYNCED;
        }

        if( state->s4s_config.curr_sync_time <= state->fifo_info.last_timestamp &&
            state->s4s_config.dt_value < 0x80) {
          LSM6DSM_MSG_E_2(ERROR,"Future timestamps? curr_sync_time: %u last_ts: %u",
              state->s4s_config.curr_sync_time,
              state->fifo_info.last_timestamp);
        }
        state->s4s_config.dt_value = 0;
      }
      else
      {
        status= SNS_DDF_EINVALID_PARAM;
      }
      break;
    default:
      return sns_dd_lsm6dsm_set_attr(dd_handle, sensor, attrib, value);
  }
  return status;
}

/**
 * LSM6DSMLHC device driver interface.
 */
sns_ddf_driver_if_s sns_dd_lsm6dsm_if =
{
  &sns_dd_lsm6dsm_init,
  &sns_dd_lsm6dsm_get_data,
  &sns_dd_lsm6dsm_set_attr_uimg,
  &sns_dd_lsm6dsm_get_attr,
  &sns_dd_lsm6dsm_handle_timer,
  &sns_dd_lsm6dsm_handle_irq,
  &sns_dd_lsm6dsm_reset,
  &sns_dd_lsm6dsm_run_test,
  &sns_dd_lsm6dsm_sched_data,
  &sns_dd_lsm6dsm_probe,
  &sns_dd_lsm6dsm_trigger_fifo
};
