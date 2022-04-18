/******************** (C) COPYRIGHT 2015 STMicroelectronics ********************
 *
 * File Name         : sns_ddf_lsm6dsm_fifo.c
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
extern sns_ddf_driver_if_s sns_dd_lsm6dsm_if;

extern stm_lsm6dsm_fifo_odr lsm6dsm_fifo_odr_reg_values[STM_LSM6DSM_ODR_NUM];
extern stm_lsm6dsm_acc_odr lsm6dsm_acc_odr_reg_values[STM_LSM6DSM_ODR_NUM];
extern stm_lsm6dsm_gyr_odr lsm6dsm_gyr_odr_reg_values[STM_LSM6DSM_ODR_NUM];
extern stm_lsm6dsm_fifo_odr lsm6dsm_fifo_odr_reg_values[STM_LSM6DSM_ODR_NUM];

/**
 * @brief To select appropriate wmk when both sensors are active
 *
 * @param[in]  dd_handle      Handle to a driver instance.
 * @param[out] wmk      calculated wmk
 *
 * @return SNS_DDF_SUCCESS if this operation was done successfully. Otherwise
 *         SNS_DDF_EDEVICE, SNS_DDF_EBUS, SNS_DDF_EINVALID_PARAM, or SNS_DDF_EFAIL to
 *         indicate and error has occurred.
 */
static uint16_t sns_dd_lsm6dsm_calculate_wmk(
    sns_ddf_handle_t dd_handle)
{
  sns_dd_lsm6dsm_state_t* state = sns_dd_lsm6dsm_get_state(dd_handle);
  int16_t min_odr_idx = -1, max_odr_idx = -1, acc_rate_idx = -1;
  int16_t odr1_idx = -1, odr2_idx = -1;
  uint16_t wmk1 = 0, wmk2 = 0;
  uint16_t min_odr = 0, max_odr = 0;
  uint16_t min_odr_wmk = 0, max_odr_wmk = 0, cal_wmk = 0;

  cal_wmk = MIN_NZERO(state->fifo_info.acc_wmk, state->fifo_info.gyr_wmk);
  if((LSM6DSM_IS_HUB_SLV_ACTIVE(state->hub_info)) && (state->fifo_info.fifo_enabled & SLAVE_FIFO_BM)) {
    if(!cal_wmk)
      return state->hub_info.wmk;
    wmk1 = cal_wmk;
    wmk2 = state->hub_info.wmk;
    //check with esp rate also
    acc_rate_idx = MAX(state->acc_desired_rate_idx, (LSM6DSM_IS_ESP_ACTIVE(state->esp_info)) ? LSM6DSM_ESP_RATE(state->esp_info) : -1);
    odr1_idx = MAX(acc_rate_idx , state->gyr_desired_rate_idx);
    odr2_idx = (state->hub_info.cur_rate) ? state->hub_info.master_rate_idx : -1;
    if(odr1_idx == odr2_idx)
      cal_wmk = MIN_NZERO(wmk1, wmk2);
    else {
      min_odr_idx = MIN(odr1_idx, odr2_idx);
      max_odr_idx = MAX(odr1_idx, odr2_idx);
      if(min_odr_idx == odr1_idx) {
        min_odr_wmk = wmk1;
        max_odr_wmk = wmk2;
      }
      else {
        min_odr_wmk = wmk2;
        max_odr_wmk = wmk1;
      }
      LSM6DSM_DATA_MSG_2(HIGH, "cal_wmk min_odr_idx %d max_odr_idx %d ", min_odr_idx, max_odr_idx);
      LSM6DSM_DATA_MSG_2(HIGH, "cal_wmk min_odr_wmk %d max_odr_wmk %d ", min_odr_wmk, max_odr_wmk);
      min_odr = (min_odr_idx >= 0) ? state->odr_list[min_odr_idx] : 0;
      max_odr = (max_odr_idx >= 0) ? state->odr_list[max_odr_idx] : 0;
      if((min_odr) && (min_odr_wmk))
        cal_wmk = ((max_odr*min_odr_wmk) / min_odr);
      else
        cal_wmk = max_odr_wmk;

      if(cal_wmk > max_odr_wmk)
        cal_wmk = max_odr_wmk;
    }
  }
  return cal_wmk;
}

/**
 * @brief To set LSM6DSM FIFO wmk
 *
 * @param[in]  dd_handle      Handle to a driver instance.
 * @param[in] watermark      Watermark level.
 *
 * @return SNS_DDF_SUCCESS if this operation was done successfully. Otherwise
 *         SNS_DDF_EDEVICE, SNS_DDF_EBUS, SNS_DDF_EINVALID_PARAM, or SNS_DDF_EFAIL to
 *         indicate and error has occurred.
 */
sns_ddf_status_e sns_dd_lsm6dsm_set_fifo_wmk(
    sns_ddf_handle_t dd_handle,
    uint16_t watermark)
{
  sns_dd_lsm6dsm_state_t* state = sns_dd_lsm6dsm_get_state(dd_handle);
  sns_ddf_status_e status;
  uint16_t wmk_words = 0;
  uint8_t wmkL = 0;
  uint8_t wmkH = 0;

  //convert samples to words
  if((state->acc_desired_rate_idx >= 0) && (state->fifo_info.fifo_enabled & ACCEL_FIFO_BM))
    wmk_words = watermark * 3;
  else if(state->fifo_info.acc_fifo_alive == true)
    wmk_words = watermark * 3;
  if((state->gyr_desired_rate_idx >= 0) && (state->fifo_info.fifo_enabled & GYRO_FIFO_BM))
    wmk_words += (watermark * 3);
  if((LSM6DSM_IS_HUB_SLV_ACTIVE(state->hub_info)) && (state->fifo_info.fifo_enabled & SLAVE_FIFO_BM))
    wmk_words += (watermark * 3);

  //wmk_words -= 1; //starts from 0
  // Configure FIFO control registers to enable streaming mode
  wmkL = wmk_words & 0xFF;
  status = sns_dd_lsm6dsm_write_reg(
      dd_handle,
      STM_LSM6DSM_REG_FIFO_CTRL1,
      &wmkL,
      1,
      0x00);
  if(status != SNS_DDF_SUCCESS) {
    LSM6DSM_MSG_E_1(ERROR, "write_reg failed status=%u", status);
    return SNS_DDF_EBUS;
  }

  wmkH = (wmk_words >> 8) & STM_LSM6DSM_FIFO_WTM_CTRL2_MASK;

  status = sns_dd_lsm6dsm_write_reg(
      dd_handle,
      STM_LSM6DSM_REG_FIFO_CTRL2,
      &wmkH,
      1,
      STM_LSM6DSM_FIFO_WTM_CTRL2_MASK);
  if(status != SNS_DDF_SUCCESS) {
    LSM6DSM_MSG_E_1(ERROR, "write reg failed  status=%u", status);
    return status;
  }
  state->fifo_info.cur_wmk = watermark;
  LSM6DSM_DATA_MSG_3(HIGH, "lsm6dsm_set_fifo_wmk: enabling fifo - setting ctrl register - wmk (%d) wmkL (%x) wmkH (%x)", wmk_words, wmkL, wmkH);

  return status;
}
//enable=true - set decimation
//enable=false - clear decimation
static sns_ddf_status_e sns_dd_lsm6dsm_fifo_decimation(
    sns_ddf_handle_t dd_handle,
    sns_ddf_sensor_e sensor,
    bool enable)
{
  sns_dd_lsm6dsm_state_t* state = sns_dd_lsm6dsm_get_state(dd_handle);
  sns_ddf_status_e status = SNS_DDF_SUCCESS;
  uint8_t r_buf[2] = {0};
  uint8_t w_buf[2] = {0};
  uint8_t read_count = 0, reg = 0 , val = 0;

  status = sns_ddf_read_port(
      state->port_handle,
      STM_LSM6DSM_REG_FIFO_CTRL3,
      r_buf,
      2,
      &read_count);
  if(status != SNS_DDF_SUCCESS) {
    LSM6DSM_MSG_E_1(ERROR, "read_port failed- status (%d)",status);
    return status;
  }
  if(read_count != 2) {
    LSM6DSM_MSG_E_1(ERROR, "read_port failed-  read_count  does not match - read_count (%d)",read_count);
    return SNS_DDF_EBUS;
  }

  LSM6DSM_MSG_3(HIGH, "lsm6dsm_fifo_decimation: sensor (%d) active_sensors %d reg (0x%x)", sensor, state->fifo_info.active_sensors, (uint16_t)(((uint16_t)(r_buf[1]) << 8) |(uint16_t) r_buf[0]));
  w_buf[0] = r_buf[0];
  w_buf[1] = r_buf[1];
  //update decimation register
  if(sensor == SNS_DDF_SENSOR_ACCEL) {
    if(enable) {
      w_buf[0] |= 0x01;
    } else {
      w_buf[0] &= ~STM_LSM6DSM_ACC_DEC_MASK; //accel not in FIFO
    }
  } else if(sensor == SNS_DDF_SENSOR_GYRO) {
    if(enable) {
      w_buf[0] |= 0x08;
    } else {
      w_buf[0] &= ~STM_LSM6DSM_GYR_DEC_MASK; //gyro not in FIFO
      if(state->fifo_info.acc_fifo_alive == true) {
        w_buf[0] &= ~STM_LSM6DSM_ACC_DEC_MASK; //accel not in FIFO
        state->fifo_info.acc_fifo_alive = false;
      }
    }
  } else if(LSM6DSM_IS_HUB_SLV_SENSOR(sensor)) {
    if(enable) {
      w_buf[1] |= 0x01;
    } else {
      w_buf[1] &= ~STM_LSM6DSM_SLV1_DEC_MASK;
    }
  }

  if(r_buf[0] != w_buf[0]) {
    reg = STM_LSM6DSM_REG_FIFO_CTRL3;
    val = w_buf[0];
  } else if(r_buf[1] != w_buf[1]) {
    reg = STM_LSM6DSM_REG_FIFO_CTRL4;
    val = w_buf[1];
  }
  if(reg) {
    status = sns_dd_lsm6dsm_write_reg(
        dd_handle,
        reg,
        &val,
        1,
        0xFF);
    if(status != SNS_DDF_SUCCESS) {
      LSM6DSM_MSG_E_1(ERROR, "write reg failed . status=%u", status);
      return status;
    }
    state->fifo_info.active_sensors = 0;
    state->fifo_info.pattern_samples_cnt = 0;
    state->fifo_info.pattern_array[0] = 0 ;
    state->fifo_info.pattern_array[1] = 0 ;
    state->fifo_info.pattern_array[2] = 0 ;
    if(w_buf[0] & STM_LSM6DSM_GYR_DEC_MASK) {
      state->fifo_info.pattern_array[state->fifo_info.active_sensors] = GYRO_FIFO_BM;
      ++state->fifo_info.active_sensors;
    }
    if(w_buf[0] & STM_LSM6DSM_ACC_DEC_MASK) {
      state->fifo_info.pattern_array[state->fifo_info.active_sensors] = ACCEL_FIFO_BM;
      ++state->fifo_info.active_sensors;
    }
    if(w_buf[1] & STM_LSM6DSM_SLV1_DEC_MASK) {
      state->fifo_info.pattern_array[state->fifo_info.active_sensors] = SLAVE_FIFO_BM;
      ++state->fifo_info.active_sensors;
    }
    //all sensors are having equal no of samples
    state->fifo_info.pattern_samples_cnt = state->fifo_info.active_sensors;
  }

  LSM6DSM_MSG_2(HIGH, "lsm6dsm_fifo_decimation:p_sample_cnt = 0x%x p_array = 0x%x)", state->fifo_info.pattern_samples_cnt, (uint32_t)(((uint16_t)(state->fifo_info.pattern_array[1]) << 16) | ((uint16_t)(state->fifo_info.pattern_array[1]) << 8) | (uint16_t)state->fifo_info.pattern_array[0]));
  LSM6DSM_MSG_3(HIGH, "lsm6dsm_fifo_decimation: sensor (%d) active_sensors %d reg (0x%x)", sensor, state->fifo_info.active_sensors, (uint16_t)(((uint16_t)(w_buf[1]) << 8) | (uint16_t) w_buf[0]));
  return status;
}

/**
 * @brief To enable LSM6DSM FIFO.
 *
 * @param[in]  dd_handle      Handle to a driver instance.
 * @param[in] watermark      Watermark level.
 *
 * @return SNS_DDF_SUCCESS if this operation was done successfully. Otherwise
 *         SNS_DDF_EDEVICE, SNS_DDF_EBUS, SNS_DDF_EINVALID_PARAM, or SNS_DDF_EFAIL to
 *         indicate and error has occurred.
 */
sns_ddf_status_e sns_dd_lsm6dsm_enable_fifo(
    sns_ddf_handle_t dd_handle,
    uint16_t watermark,
    sns_ddf_sensor_e sensor)
{
  sns_dd_lsm6dsm_state_t* state = sns_dd_lsm6dsm_get_state(dd_handle);
  sns_ddf_status_e status = SNS_DDF_SUCCESS;
  uint16_t new_wmk = 0;
  uint8_t cur_fifo_status = 0;
  bool power_down  = false;
  int8_t cur_acc_rate_idx = state->acc_cur_rate_idx;
  int8_t cur_gyr_rate_idx = state->gyr_cur_rate_idx;
  int8_t set_odr_idx = -1;
  bool non_s4s_mode = false;
  sns_ddf_odr_t temp_rate = 0;

  LSM6DSM_MSG_3(HIGH, "lsm6dsm_enable_fifo: get called. sensor (%d) watermark=%u fifo_info.fifo_enabled (0x%x)",
      sensor, watermark, state->fifo_info.fifo_enabled);
  LSM6DSM_MSG_3(HIGH, "lsm6dsm_enable_fifo ENTER: NOW time (%u) acc_cur_rate_idx (%d) cur_gyr_rate_idx (%d) ",
      sns_ddf_get_timestamp(), cur_acc_rate_idx, cur_gyr_rate_idx);
  cur_fifo_status = state->fifo_info.fifo_enabled;


  if(cur_fifo_status) {
    //Do not move this code, fifo enabled is setting below
    sns_dd_lsm6dsm_flush_fifo(dd_handle, 0, true);
  }
  if(state->device_select) {
    set_odr_idx = MAX(cur_acc_rate_idx, cur_gyr_rate_idx);
    if(set_odr_idx > STM_LSM6DSM_ODR208) {
      watermark = 1;
      non_s4s_mode = true;
    }
  }

  if(sensor == SNS_DDF_SENSOR_ACCEL) {
    state->fifo_info.fifo_enabled |= ACCEL_FIFO_BM;
    state->fifo_info.acc_wmk = watermark;
    temp_rate = state->a_temp_rate;
  } else if(sensor == SNS_DDF_SENSOR_GYRO) {
    state->fifo_info.fifo_enabled |= GYRO_FIFO_BM;
    state->fifo_info.gyr_wmk = watermark;
    temp_rate = state->g_temp_rate;
  } else if(LSM6DSM_IS_HUB_SLV_SENSOR(sensor)) {
    state->fifo_info.fifo_enabled |= SLAVE_FIFO_BM;
    state->hub_info.wmk = watermark;
  }
  //update_fifo_status =  state->fifo_info.fifo_enabled | (sensor == SNS_DDF_SENSOR_ACCEL) ? 0x01 : 0x02;
  // call set rate only after setting fifo_enabled
  if(temp_rate)
    sns_dd_lsm6dsm_temp_set_rate(dd_handle, 1);

  //acc and gyro would have same odr, wmk would be MIN of both
  new_wmk = sns_dd_lsm6dsm_calculate_wmk(dd_handle);

  LSM6DSM_DATA_MSG_2(HIGH, "lsm6dsm_enable_fifo: cur_fifo_enabled 0x%x update_fifo_enabled 0x%x", cur_fifo_status, state->fifo_info.fifo_enabled);
  LSM6DSM_DATA_MSG_2(HIGH, "lsm6dsm_enable_fifo: cur_wmk %d new_wmk %d", state->fifo_info.cur_wmk, new_wmk);
  //adding new sensor, changing wmk and odr are not allowed
  if((sensor == SNS_DDF_SENSOR_ACCEL) &&
      (state->fifo_info.acc_fifo_alive == true)) {
    state->fifo_info.acc_fifo_alive = false;
    if(state->fifo_info.cur_wmk != new_wmk) {
      //lets try to set wmk without closing
      status = sns_dd_lsm6dsm_set_fifo_wmk(
          dd_handle,
          new_wmk);
      if(state->device_select && non_s4s_mode) {

        if((state->acc_desired_rate_idx > STM_LSM6DSM_ODR208) 
            && (state->fifo_info.fifo_enabled & ACCEL_FIFO_BM))
          sns_dd_lsm6dsm_enable_fifo_int(dd_handle, SNS_DDF_SENSOR_ACCEL);
        if((state->gyr_desired_rate_idx > STM_LSM6DSM_ODR208)
            && (state->fifo_info.fifo_enabled & GYRO_FIFO_BM))
          sns_dd_lsm6dsm_enable_fifo_int(dd_handle, SNS_DDF_SENSOR_GYRO);
        state->s4s_config.synced = STM_LSM6DSM_S4S_NOT_SYNCED;
      }
      return status;
    }
  } else if((cur_fifo_status == state->fifo_info.fifo_enabled) &&
      (state->fifo_info.cur_wmk != new_wmk)) {
    //fifo status same but wmk is changed
    status = sns_dd_lsm6dsm_set_fifo_wmk(
        dd_handle,
        new_wmk);
    if(state->device_select && non_s4s_mode) {
      if((state->acc_desired_rate_idx > STM_LSM6DSM_ODR208) 
          && (state->fifo_info.fifo_enabled & ACCEL_FIFO_BM))
        sns_dd_lsm6dsm_enable_fifo_int(dd_handle, SNS_DDF_SENSOR_ACCEL);
      if((state->gyr_desired_rate_idx > STM_LSM6DSM_ODR208)
          && (state->fifo_info.fifo_enabled & GYRO_FIFO_BM))
        sns_dd_lsm6dsm_enable_fifo_int(dd_handle, SNS_DDF_SENSOR_GYRO);
      state->s4s_config.synced = STM_LSM6DSM_S4S_NOT_SYNCED;
    }

    return status;
  } else if(cur_fifo_status != state->fifo_info.fifo_enabled) {
    power_down = true;
  }

  if(power_down == false) {
    LSM6DSM_DATA_MSG_0(HIGH, "lsm6dsm_enable_fifo: FIFO config is not changing .. returning");
    LSM6DSM_DATA_MSG_3(HIGH, "lsm6dsm_enable_fifo: sensor (%d) watermark=%u fifo_info.fifo_enabled (0x%x)",
        sensor, watermark, state->fifo_info.fifo_enabled);
    if(state->device_select && non_s4s_mode) {
      if((state->acc_desired_rate_idx > STM_LSM6DSM_ODR208) 
          && (state->fifo_info.fifo_enabled & ACCEL_FIFO_BM))
        sns_dd_lsm6dsm_enable_fifo_int(dd_handle, SNS_DDF_SENSOR_ACCEL);
      if((state->gyr_desired_rate_idx > STM_LSM6DSM_ODR208)
          && (state->fifo_info.fifo_enabled & GYRO_FIFO_BM))
        sns_dd_lsm6dsm_enable_fifo_int(dd_handle, SNS_DDF_SENSOR_GYRO);
      state->s4s_config.synced = STM_LSM6DSM_S4S_NOT_SYNCED;
    }
    return status;
  }

  sns_dd_lsm6dsm_stop_streaming(dd_handle, false);
  if(cur_acc_rate_idx > STM_LSM6DSM_ODR0)
    state->data_intp.acc_intp_status = true;
  if(cur_gyr_rate_idx > STM_LSM6DSM_ODR0)
    state->data_intp.gyr_intp_status = true;

  sns_dd_lsm6dsm_fifo_decimation(dd_handle, sensor, true);
  status = sns_dd_lsm6dsm_set_fifo_wmk(
      dd_handle,
      new_wmk);
  LSM6DSM_DATA_MSG_2(HIGH, "lsm6dsm_enable_fifo: acc_desired_rate_idx %d gyr_desired_rate_idx (%d)", state->acc_desired_rate_idx, state->gyr_desired_rate_idx);

  sns_dd_lsm6dsm_start_streaming(dd_handle);
  if(!cur_fifo_status && state->fifo_info.fifo_enabled)
    state->fifo_info.last_timestamp = sns_ddf_get_timestamp();

  if(state->device_select && non_s4s_mode) {

    if((state->acc_desired_rate_idx > STM_LSM6DSM_ODR208) 
        && (state->fifo_info.fifo_enabled & ACCEL_FIFO_BM))
      sns_dd_lsm6dsm_enable_fifo_int(dd_handle, SNS_DDF_SENSOR_ACCEL);
    if((state->gyr_desired_rate_idx > STM_LSM6DSM_ODR208)
        && (state->fifo_info.fifo_enabled & GYRO_FIFO_BM))
      sns_dd_lsm6dsm_enable_fifo_int(dd_handle, SNS_DDF_SENSOR_GYRO);
    state->s4s_config.synced = STM_LSM6DSM_S4S_NOT_SYNCED;
  }

  if((state->acc_desired_rate_idx >= 0) &&
      (cur_acc_rate_idx >= 0) &&
      (cur_acc_rate_idx != state->acc_cur_rate_idx))
    sns_dd_lsm6dsm_send_event_smgr(dd_handle,
        SNS_DDF_SENSOR_ACCEL,
        SNS_DDF_EVENT_ODR_CHANGED);

  if ((state->gyr_desired_rate_idx >= 0) &&
      (cur_gyr_rate_idx >= 0) &&
      (cur_gyr_rate_idx != state->gyr_cur_rate_idx))
    sns_dd_lsm6dsm_send_event_smgr(dd_handle,
        SNS_DDF_SENSOR_GYRO,
        SNS_DDF_EVENT_ODR_CHANGED);

  LSM6DSM_MSG_3(HIGH, "lsm6dsm_enable_fifo EXIT: watermark=%u fifo_info.fifo_enabled (0x%x) NOW_time (%u)",
      watermark, state->fifo_info.fifo_enabled, sns_ddf_get_timestamp());
  return SNS_DDF_SUCCESS;
}

/**
 * @brief To disable LSM6DSM FIFO.
 *
 * @param[in]  dd_handle      Handle to a driver instance.
 *
 * @return SNS_DDF_SUCCESS if this operation was done successfully. Otherwise
 *         SNS_DDF_EDEVICE, SNS_DDF_EBUS, SNS_DDF_EINVALID_PARAM, or SNS_DDF_EFAIL to
 *         indicate and error has occurred.
 */
sns_ddf_status_e sns_dd_lsm6dsm_disable_fifo(
    sns_ddf_handle_t dd_handle,
    sns_ddf_sensor_e sensor)
{
  sns_dd_lsm6dsm_state_t* state = sns_dd_lsm6dsm_get_state(dd_handle);
  sns_ddf_status_e status;
  uint16_t new_wmk = 0;
  int8_t cur_acc_rate_idx = state->acc_cur_rate_idx;
  int8_t cur_gyr_rate_idx = state->gyr_cur_rate_idx;
  uint8_t cur_fifo_status = 0;

  LSM6DSM_MSG_2(HIGH, "lsm6dsm_disable_fifo ENTER: NOW time (%u) fifo_rate_idx (%d)",sns_ddf_get_timestamp(), state->fifo_info.fifo_rate_idx);
  LSM6DSM_MSG_3(HIGH, "lsm6dsm_disable_fifo: sensor (%d) fifo_info.fifo_enabled (%d) cur_wmk (%d)",
      sensor, state->fifo_info.fifo_enabled, state->fifo_info.cur_wmk);

  if(((sensor == SNS_DDF_SENSOR_ACCEL) && (!(state->fifo_info.fifo_enabled & ACCEL_FIFO_BM))) ||
      ((sensor == LSM6DSM_SLAVE_SENSOR) && (!(state->fifo_info.fifo_enabled & SLAVE_FIFO_BM))) ||
      ((sensor == SNS_DDF_SENSOR_GYRO) && (!(state->fifo_info.fifo_enabled & GYRO_FIFO_BM)))) {
    //if requested sensor is not enabled, return from here
    LSM6DSM_DATA_MSG_2(HIGH, "lsm6dsm_disable_fifo: sensor (%d) fifo not enabled (%d)", sensor, state->fifo_info.fifo_enabled);
    return SNS_DDF_SUCCESS;
  }

  cur_fifo_status = state->fifo_info.fifo_enabled;

  if(sensor == SNS_DDF_SENSOR_ACCEL) {
    if(state->fifo_info.fifo_enabled & GYRO_FIFO_BM) {
      //gyro alive
      state->fifo_info.acc_fifo_alive = true;
      state->fifo_info.fifo_enabled &= (~ACCEL_FIFO_BM);
      state->fifo_info.acc_wmk = 0;
      sns_dd_lsm6dsm_temp_set_rate(dd_handle, 0);
      return SNS_DDF_SUCCESS;
    }
  }

  sns_dd_lsm6dsm_stop_streaming(dd_handle, true);

  if(sensor == SNS_DDF_SENSOR_ACCEL) {
    state->fifo_info.fifo_enabled &= ~ACCEL_FIFO_BM;
    state->fifo_info.acc_wmk = 0;
  } else if(sensor == SNS_DDF_SENSOR_GYRO) {
    state->fifo_info.fifo_enabled &= ~GYRO_FIFO_BM;
    state->fifo_info.gyr_wmk = 0;
  } else if(LSM6DSM_IS_HUB_SLV_SENSOR(sensor)) {
    state->fifo_info.fifo_enabled &= ~SLAVE_FIFO_BM;
    state->hub_info.wmk = 0;
  }

  sns_dd_lsm6dsm_temp_set_rate(dd_handle, 0);


  sns_dd_lsm6dsm_fifo_decimation(dd_handle, sensor, false);

  if(state->fifo_info.fifo_enabled ) {
    LSM6DSM_DATA_MSG_0(HIGH, "lsm6dsm_disable_fifo: Another sensor fifo active");

    new_wmk = sns_dd_lsm6dsm_calculate_wmk(dd_handle);
    status = sns_dd_lsm6dsm_set_fifo_wmk(
        dd_handle,
        new_wmk);

    LSM6DSM_DATA_MSG_2(HIGH, "lsm6dsm_disable_fifo: new_wmk (%d) cur_wmk=%d",new_wmk, state->fifo_info.cur_wmk);
  } else {
    //clear wmk
    new_wmk = 0x00;
    status = sns_dd_lsm6dsm_write_reg(
        dd_handle,
        STM_LSM6DSM_REG_FIFO_CTRL1,
        (uint8_t *)&new_wmk,
        1,
        0x00);

    status = sns_dd_lsm6dsm_write_reg(
        dd_handle,
        STM_LSM6DSM_REG_FIFO_CTRL2,
        (uint8_t *)&new_wmk,
        1,
        STM_LSM6DSM_FIFO_WTM_CTRL2_MASK);
    //only reset fifo_info.last_timestamp after reset or after fifo disabled
    state->fifo_info.last_timestamp = 0;
    state->fifo_info.cur_wmk = 0;
    state->fifo_info.avg_sample_time = 0;
  }

  sns_dd_lsm6dsm_start_streaming(dd_handle);
  if(cur_acc_rate_idx > STM_LSM6DSM_ODR0)
    state->data_intp.acc_intp_status = true;
  if(cur_gyr_rate_idx > STM_LSM6DSM_ODR0)
    state->data_intp.gyr_intp_status = true;
  state->fifo_info.avg_sample_time = 0;

  if(state->fifo_info.fifo_enabled) {
    if((state->fifo_info.fifo_enabled & ACCEL_FIFO_BM) &&
        (state->acc_desired_rate_idx >= 0) &&
        (cur_acc_rate_idx != state->acc_cur_rate_idx))
      sns_dd_lsm6dsm_send_event_smgr(dd_handle,
          SNS_DDF_SENSOR_ACCEL,
          SNS_DDF_EVENT_ODR_CHANGED);

    if((state->fifo_info.fifo_enabled & GYRO_FIFO_BM) &&
        (state->gyr_desired_rate_idx >= 0) &&
        (cur_gyr_rate_idx != state->gyr_cur_rate_idx))
      sns_dd_lsm6dsm_send_event_smgr(dd_handle,
          SNS_DDF_SENSOR_GYRO,
          SNS_DDF_EVENT_ODR_CHANGED);
  }

  LSM6DSM_MSG_3(HIGH, "lsm6dsm_disable_fifo EXIT:  fifo_info.fifo_enabled (%d) cur_wmk (%d) Now_time (%u)",
      state->fifo_info.fifo_enabled, state->fifo_info.cur_wmk, sns_ddf_get_timestamp());

  return SNS_DDF_SUCCESS;
}


/**
 * @brief To enable LSM6DSM FIFO interrupt.
 *
 * @param[in]  dd_handle      Handle to a driver instance.
 *
 * @return SNS_DDF_SUCCESS if this operation was done successfully. Otherwise
 *         SNS_DDF_EDEVICE, SNS_DDF_EBUS, SNS_DDF_EINVALID_PARAM, or SNS_DDF_EFAIL to
 *         indicate and error has occurred.
 */
sns_ddf_status_e sns_dd_lsm6dsm_enable_fifo_int(
    sns_ddf_handle_t dd_handle,
    sns_ddf_sensor_e sensor)
{
  sns_dd_lsm6dsm_state_t* state = sns_dd_lsm6dsm_get_state(dd_handle);
  sns_ddf_status_e status = SNS_DDF_SUCCESS;
  uint8_t fifo_int_status = state->fifo_info.fifo_int_enabled;
  uint8_t rw_buffer = 0;

  LSM6DSM_MSG_3(HIGH, "sns_dd_lsm6dsm_enable_fifo_int: sensor (%d) fifo_info.fifo_enabled (%d) int_enabled (%d)",
      sensor, state->fifo_info.fifo_enabled ,state->fifo_info.fifo_int_enabled);

  LSM6DSM_MSG_2(HIGH, "lsm6dsm_enable_fifo_int ENTER: NOW time (%u) cur_wmk (%d)",sns_ddf_get_timestamp(), state->fifo_info.cur_wmk);
  if(!state->fifo_info.fifo_enabled) {
    LSM6DSM_DATA_MSG_0(HIGH, "sns_dd_lsm6dsm_enable_fifo_int: FIFO not enabled - returing wihtout enabling interrupt");
    return SNS_DDF_SUCCESS;
  }
  if(state->fifo_info.cur_wmk) {
    if((sensor == SNS_DDF_SENSOR_ACCEL) && (state->fifo_info.fifo_enabled & ACCEL_FIFO_BM))
      state->fifo_info.fifo_int_enabled |= ACCEL_FIFO_BM;
    else if((sensor == SNS_DDF_SENSOR_GYRO) && (state->fifo_info.fifo_enabled & GYRO_FIFO_BM))
      state->fifo_info.fifo_int_enabled |= GYRO_FIFO_BM;
    else if((LSM6DSM_IS_HUB_SLV_SENSOR(sensor)) && (state->fifo_info.fifo_enabled & SLAVE_FIFO_BM))
      state->fifo_info.fifo_int_enabled |= SLAVE_FIFO_BM;

    if((!fifo_int_status) && (state->fifo_info.fifo_int_enabled)) {
      LSM6DSM_MSG_2(HIGH, "setting int:: prev_int_status 0x%x update_int_status 0x%x", fifo_int_status, state->fifo_info.fifo_int_enabled);
      rw_buffer = STM_LSM6DSM_FIFO_INT_MASK;
      status = sns_dd_lsm6dsm_write_reg(
          dd_handle,
          STM_LSM6DSM_REG_INT1_CTRL,
          &rw_buffer,
          1,
          STM_LSM6DSM_FIFO_INT_MASK);
      if(status != SNS_DDF_SUCCESS) {
        LSM6DSM_MSG_E_1(ERROR, "write reg failed . status=%u", status);
        return status;
      }
    }
  }
  LSM6DSM_MSG_3(HIGH, "lsm6dsm_enable_fifo_int EXIT: NOW time (%u) cur_wmk (%d) int_enabled (%d)",
      sns_ddf_get_timestamp(), state->fifo_info.cur_wmk, state->fifo_info.fifo_int_enabled);

  return SNS_DDF_SUCCESS;
}

/**
 * @brief To disable LSM6DSM FIFO interrupt.
 *
 * @param[in]  dd_handle      Handle to a driver instance.
 *
 * @return SNS_DDF_SUCCESS if this operation was done successfully. Otherwise
 *         SNS_DDF_EDEVICE, SNS_DDF_EBUS, SNS_DDF_EINVALID_PARAM, or SNS_DDF_EFAIL to
 *         indicate and error has occurred.
 */
sns_ddf_status_e sns_dd_lsm6dsm_disable_fifo_int(
    sns_ddf_handle_t dd_handle,
    sns_ddf_sensor_e sensor)
{
  sns_dd_lsm6dsm_state_t* state = sns_dd_lsm6dsm_get_state(dd_handle);
  uint8_t fifo_int_status = state->fifo_info.fifo_int_enabled;
  sns_ddf_status_e status;
  uint8_t rw_buffer = 0;

  LSM6DSM_MSG_3(HIGH, "sns_dd_lsm6dsm_disable_fifo_int: sensor (%d) fifo_info.fifo_enabled (0x%x) fifo_info.fifo_int_enabled (0x%x) \
      ", sensor, state->fifo_info.fifo_enabled, state->fifo_info.fifo_int_enabled);
  LSM6DSM_MSG_2(HIGH, "lsm6dsm_disable_fifo_int ENTER: NOW time (%u) cur_wmk (%d)",sns_ddf_get_timestamp(), state->fifo_info.cur_wmk);

  if(sensor == SNS_DDF_SENSOR_ACCEL)
    state->fifo_info.fifo_int_enabled &= ~ACCEL_FIFO_BM;
  else if(sensor == SNS_DDF_SENSOR_GYRO)
    state->fifo_info.fifo_int_enabled &= ~GYRO_FIFO_BM;
  else if(LSM6DSM_IS_HUB_SLV_SENSOR(sensor))
    state->fifo_info.fifo_int_enabled &= ~SLAVE_FIFO_BM;

  if((fifo_int_status) && (!state->fifo_info.fifo_int_enabled)) {
    rw_buffer = 0;
    status = sns_dd_lsm6dsm_write_reg(
        dd_handle,
        STM_LSM6DSM_REG_INT1_CTRL,
        &rw_buffer,
        1,
        STM_LSM6DSM_FIFO_INT_MASK);

    if(status != SNS_DDF_SUCCESS)
      return status;
  }
  LSM6DSM_MSG_3(HIGH, "lsm6dsm_disable_fifo_int EXIT: NOW time (%u) sensor (%d) int_status (0x%x)",sns_ddf_get_timestamp(), sensor, state->fifo_info.fifo_int_enabled);
  return SNS_DDF_SUCCESS;
}

