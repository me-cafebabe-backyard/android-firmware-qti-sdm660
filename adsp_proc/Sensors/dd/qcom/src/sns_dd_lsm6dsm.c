/******************** (C) COPYRIGHT 2015 STMicroelectronics ********************
 *
 * File Name         : sns_dd_lsm6dsm.c
 * Authors           : Karimuddin Sayed
 * Version           : V 5.15.1
 * Date              : 2/28/2017
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
 *******************************************************************************
 * REVISON HISTORY
 *
 * VERSION | DATE          | DESCRIPTION
 *
 * 1.0.0   | 11/06/2015    | DDF device driver initial version
 * 2.0.0   | 2/05/2016     | updating driver for FIFO
 * 3.0.0   | 3/15/2016     | 13Hz support and Bug fixes for selftest
 * 3.1.0   | 3/24/2016     | wakeup detection, using timer
 * 5.0.0   | 4/7/2016      | S4S support, first version
 * 5.1.0   | 5/9/2016      | S4S support, for gyro
 * 5.2.0   | 5/12/2016     | set fifo odr to be 6.6.KHz to work with old samples
 * 5.3.0   | 6/28/2016     | fixed motion detecction misfire, default range to be 2000dps
 * 5.4.0   | 7/7/2016      | fix md sensitivity issue
 * 5.5.0   | 7/13/2016     | Update logic to handle new smgr power/reset sequence
 * 5.6.0   | 8/18/2016     | irq timestamp jitter fix for cts orientation 15Hz
 *                         | change logic to get state from handle
 *                         | temp sensor with 200Hz fix and selftest with streaming fixed
 * 5.7.0   | 9/1/2016      | Fixed reset function to avoid too many contigous invalid samples
 *                         | Fixed timestamp roll back
 * 5.8.0   | 9/22/2016     | gyro in sleep mode when accel is not streaming, powering down
 * 5.9.0   | 11/11/2016    | Adding sensor hub support - using AKM MAG sensor as slave 
 * 5.10.0  | 11/29/2016    | support for dynamic switch s4s(<=200Hz) <-> non-s4s (>200Hz)
 * 5.11.0  | 12/14/2016    | report slave supported odr as accel odrs to smgr
 * 5.12.0  | 1/16/2017     | update mag timestamps for CTS failure of 15Hz and 25Hz
 * 5.13.0  | 1/30/2017     | Axis mapping for accel data is missing in polling mode
 * 5.14.0  | 2/8/2017      | corrected temp resolution when getting attribute
 *                         | use max_odr_idx and min_odr_idx while setting sample rates
 *                         | check sensor fifo enabled or not while splitting data
 *                         | fix md spurious interrupts when gyro enabled/disabled
 * 5.15.0  | 2/20/2017     | fixed timestamp rollover issue in validate timstamp
 *                         | fixed temp sensor fifo information
 * 5.15.1  | 2/28/2017     | corrected shiting a negative value
 ********************************************************************************/

#include "sns_dd_lsm6dsm.h"

extern sns_ddf_driver_if_s sns_dd_lsm6dsm_if;

#if LSM6DSM_ENABLE_ESP
extern sns_ddf_driver_if_s sns_dd_lsm6dsm_esp_if;
#endif

#if LSM6DSM_ENABLE_HUB
extern sns_ddf_driver_if_s sns_dd_lsm6dsm_hub_if;
#endif

extern void sns_dd_lsm6dsm_handle_timer(
   sns_ddf_handle_t dd_handle,
    void* arg);
extern void sns_dd_lsm6dsm_config_md(
    sns_ddf_nv_params_s* nv_params,
    stm_lsm6dsm_esp_config *esp_config);

/**
 * Accelerometer LSM6DSM_ACC ranges array for setting attribute
 */
stm_lsm6dsm_acc_range lsm6dsm_acc_ranges[]={
  STM_LSM6DSM_ACC_RANGE_2G,
  STM_LSM6DSM_ACC_RANGE_4G,
  STM_LSM6DSM_ACC_RANGE_8G,
  STM_LSM6DSM_ACC_RANGE_16G
};

/**
 * Accelerometer LSM6DSM sampling frequencies array for getting attribute
 */
sns_ddf_lowpass_freq_t lsm6dsm_freqs[] = {
/*
  FX_CONV_Q16((int32_t)13,0),
  FX_CONV_Q16((int32_t)26,0),
  FX_CONV_Q16((int32_t)52,0),
  FX_CONV_Q16((int32_t)104,0),
  FX_CONV_Q16((int32_t)208,0)
  */
  (q16_t) (25<<16),
  (q16_t) (50<<16),
  (q16_t) (100<<16),
  (q16_t) (200<<16)
};

/**
 * Magnetometer LSM6DSM_GYR ranges array for setting attribute
 */
stm_lsm6dsm_gyr_range lsm6dsm_gyr_ranges[]={
  STM_LSM6DSM_GYR_RANGE_125DPS,
  STM_LSM6DSM_GYR_RANGE_245DPS,
  STM_LSM6DSM_GYR_RANGE_500DPS,
  STM_LSM6DSM_GYR_RANGE_1000DPS,
  STM_LSM6DSM_GYR_RANGE_2000DPS
};

extern sns_ddf_odr_t lsm6dsm_s4s_odr[STM_LSM6DSM_ODR_NUM] ;
extern sns_ddf_odr_t lsm6dsm_non_s4s_odr[STM_LSM6DSM_ODR_NUM] ;
extern stm_lsm6dsm_acc_odr lsm6dsm_acc_odr_reg_values[STM_LSM6DSM_ODR_NUM];
extern stm_lsm6dsm_gyr_odr lsm6dsm_gyr_odr_reg_values[STM_LSM6DSM_ODR_NUM];
extern stm_lsm6dsm_fifo_odr lsm6dsm_fifo_odr_reg_values[STM_LSM6DSM_ODR_NUM];

extern stm_lsm6dsm_head_s lsm6dsm_dd_head;
static uint8_t stm_lsm6dsm_axis_dflt[3] = {1, 2, 3};
/*===========================================================================

FUNCTION:   dd_find_free_sub_dev_slot

===========================================================================*/
/*!
  @brief Find a free slot for a sub-dd

  @detail

  @param[i] my_dev_ptr - the poiter to the my_dev instance

  @return
  The index for the first free slot of the sub-dd
  -1 : When there is no free slot for a sub-dd
  */
/*=========================================================================*/
static int32_t dd_find_free_sub_dev_slot (sns_dd_lsm6dsm_state_t *my_dev_ptr)
{
  uint32_t i;
  for (i =0; i < LSM6DSM_MAX_SUB_DEV; i++)
  {
    if ( 0 == my_dev_ptr->sub_dev[i].num_sensors )
    {
      return i;
    }
  }
  return -1;
}
/*===========================================================================

FUNCTION:   dd_fill_sub_dev_slot

===========================================================================*/
/*!
  @brief  Fill the sub-dd slot with the sensor types from the input parameters

  @detail

  @param[o] sub_dev_slot_ptr - the poiter to the my_dev instance
  @param[i] num_sensors - the number of sensor types
  @param[i] sensors - the list of sensor types

  @return the number of sensor types that the device suspport
  */
/*=========================================================================*/
static uint32_t dd_fill_sub_dev_slot (stm_lsm6dsm_sub_dev_s *sub_dev_slot_ptr, uint32_t num_sensors, sns_ddf_sensor_e sensors[])
{
  uint32_t my_num_sensors = 0, i;
  for (i =0; i < num_sensors; i++)
  {
    /*
     * Note: both ACCEL and GYR are Primary Data Types, by definition.
     */
    if(LSM6DSM_IS_ESP_SENSOR(sensors[i]))
      sub_dev_slot_ptr->sensors[my_num_sensors++] = sensors[i];
    else if(LSM6DSM_IS_HUB_SLV_SENSOR(sensors[i]))
      sub_dev_slot_ptr->sensors[my_num_sensors++] = sensors[i];
    else {
      LSM6DSM_MSG_2(HIGH, "fill_sub_dev i (%d) sensor %d",i, sensors[i]);
      switch(sensors[i]) {
        case SNS_DDF_SENSOR_ACCEL:
        case SNS_DDF_SENSOR_GYRO:
          sub_dev_slot_ptr->sensors[my_num_sensors++] = sensors[i];
          sub_dev_slot_ptr->sensors[my_num_sensors++] = SNS_DDF_SENSOR_TEMP;
          break;
        default:
          break;
      }
    }
  }

  sub_dev_slot_ptr->num_sensors = my_num_sensors;
  return my_num_sensors;
}

/*===========================================================================

FUNCTION:   dd_find_same_dev

===========================================================================*/
/*!
  @brief  Find the device instance which if corespond to the input port configuration

  @detail

  @param[i] port_config_ptr - the port configuration

  @return the my_dev instance
  */
/*=========================================================================*/
static sns_dd_lsm6dsm_state_t *dd_find_same_port_dev (sns_ddf_port_config_s *port_config_ptr)
{
  sns_dd_lsm6dsm_state_t *cur_dd_dev_ptr = (sns_dd_lsm6dsm_state_t *)lsm6dsm_dd_head.next;

  while (cur_dd_dev_ptr)
  {
    if (true == sns_ddf_is_same_port_id(port_config_ptr, &cur_dd_dev_ptr->port_id))
    {
      return cur_dd_dev_ptr;
    }
    else
    {
      cur_dd_dev_ptr = cur_dd_dev_ptr->next;
    }
  }
  return NULL;
}


/**
 * @brief To update odr of lsm6dsm based on cur accel and gyro rate
 *
 * @param[in]  state          - Handle to a driver instance.
 * @param[in]  new_rate_idx       - if new_rate_idx = -1 device is resetting
 *
 * @return SNS_DDF_SUCCESS if set appropriate rate otherwise return SNS_DDF_EINVALID_PARAM.
 */

sns_ddf_status_e sns_dd_lsm6dsm_update_rate(
    sns_ddf_handle_t dd_handle,
    sns_ddf_sensor_e sensor,
    int8_t new_rate_idx)
{
  sns_ddf_status_e status = SNS_DDF_SUCCESS;
  sns_dd_lsm6dsm_state_t* state;
  int8_t a_cur_odr_idx = -1;
  int8_t g_cur_odr_idx = -1;
  int8_t odr_idx = -1;
  int8_t update_rate_idx;
  int8_t cur_rate_idx;
  int8_t new_acc_rate_idx = -1, set_odr_idx = -1;

  //enters in this function only when fifo is enabled and new_rate_idx >= 0
  //doesn't enter when sensor is powering down
  state = sns_dd_lsm6dsm_get_state(dd_handle);

  cur_rate_idx = state->fifo_info.fifo_rate_idx;
  a_cur_odr_idx = state->acc_cur_rate_idx;
  g_cur_odr_idx = state->gyr_cur_rate_idx;

  if(((sensor != SNS_DDF_SENSOR_ACCEL) &&
        (sensor != SNS_DDF_SENSOR_GYRO)) ||
      (new_rate_idx < 0)) {
    LSM6DSM_MSG_E_2(ERROR, "sensor (%d) new_rate (%d) invalid parameters", sensor, new_rate_idx);
    return SNS_DDF_EINVALID_PARAM;
  }
  //TODO update needed if ESP rate is higher, this logic fails
  if(sensor == SNS_DDF_SENSOR_ACCEL) {
    update_rate_idx = MAX(new_rate_idx, state->gyr_desired_rate_idx);
    odr_idx = a_cur_odr_idx;
  }
  else {
    if(LSM6DSM_IS_ESP_ACTIVE(state->esp_info))
      update_rate_idx = MAX(a_cur_odr_idx, new_rate_idx);
    else
      update_rate_idx = MAX(state->acc_desired_rate_idx, new_rate_idx);
    odr_idx = g_cur_odr_idx;
  }

  LSM6DSM_MSG_3(LOW, "update_rate new_rate_idx (%d) update_rate_idx (%d) cur_fifo_rate_idx (%d)",new_rate_idx, update_rate_idx, cur_rate_idx);
  if(update_rate_idx < 0) {
    return SNS_DDF_SUCCESS;
  }

  if((update_rate_idx != cur_rate_idx) ||
      (odr_idx != cur_rate_idx)) {
    LSM6DSM_DATA_MSG_2(LOW, "update accel, gyro and fifo rate - update_rate_idx (%d) cur_rate_idx (%d)", update_rate_idx, cur_rate_idx);

    sns_dd_lsm6dsm_stop_streaming(dd_handle, true);
    if(state->device_select) {
      //s4s case only
      new_acc_rate_idx = sns_dd_lsm6dsm_get_acc_rate(dd_handle);
      set_odr_idx = MAX(new_acc_rate_idx, state->gyr_desired_rate_idx);
      if(set_odr_idx > STM_LSM6DSM_ODR208) {
        //comes here only in fifo case
        if(!state->fifo_info.fifo_int_enabled) {
          //setting wmk=1, fifo is already enabled here
          state->s4s_config.sensor_sbsp = SNS_DDF_SENSOR__NONE;
          sns_dd_lsm6dsm_set_fifo_wmk(
              dd_handle,
              1);
          state->s4s_config.synced = STM_LSM6DSM_S4S_NOT_SYNCED;
        }
        if(state->acc_desired_rate_idx > STM_LSM6DSM_ODR208)
          state->fifo_info.acc_wmk = 1;
        if(state->gyr_desired_rate_idx > STM_LSM6DSM_ODR208)
          state->fifo_info.gyr_wmk = 1;

        //set int for the sensor whose fifo is enabled
        if((state->acc_desired_rate_idx > STM_LSM6DSM_ODR208) 
            && (state->fifo_info.fifo_enabled & ACCEL_FIFO_BM))
          sns_dd_lsm6dsm_enable_fifo_int(dd_handle, SNS_DDF_SENSOR_ACCEL);
        if((state->gyr_desired_rate_idx > STM_LSM6DSM_ODR208)
            && (state->fifo_info.fifo_enabled & GYRO_FIFO_BM))
          sns_dd_lsm6dsm_enable_fifo_int(dd_handle, SNS_DDF_SENSOR_GYRO);
      } else if(cur_rate_idx > STM_LSM6DSM_ODR208) {
        if(state->fifo_info.fifo_int_enabled & ACCEL_FIFO_BM)
          sns_dd_lsm6dsm_disable_fifo_int(dd_handle, SNS_DDF_SENSOR_ACCEL);
        if(state->fifo_info.fifo_int_enabled & GYRO_FIFO_BM)
          sns_dd_lsm6dsm_disable_fifo_int(dd_handle, SNS_DDF_SENSOR_GYRO);
        sns_dd_lsm6dsm_set_fifo_wmk(
            dd_handle,
            STM_LSM6DSM_MAX_FIFO);
        if(state->fifo_info.fifo_enabled & ACCEL_FIFO_BM)
          state->fifo_info.acc_wmk = STM_LSM6DSM_MAX_FIFO;
        if(state->fifo_info.fifo_enabled & GYRO_FIFO_BM)
          state->fifo_info.gyr_wmk = STM_LSM6DSM_MAX_FIFO;
      }
    }
    sns_dd_lsm6dsm_start_streaming(dd_handle);

    state->fifo_info.avg_sample_time = 0;

    if(sensor == SNS_DDF_SENSOR_ACCEL) {
      //update desired rate before sending event
      if(state->gyr_desired_rate_idx >= 0)
        state->data_intp.gyr_intp_status = true;

      if(g_cur_odr_idx != state->gyr_cur_rate_idx) {
        sns_dd_lsm6dsm_send_event_smgr(dd_handle,
            SNS_DDF_SENSOR_GYRO,
            SNS_DDF_EVENT_ODR_CHANGED);
      }
    } else {
      if(state->acc_desired_rate_idx >= 0) {
        state->data_intp.acc_intp_status = true;
        if(a_cur_odr_idx != state->acc_cur_rate_idx) {
          sns_dd_lsm6dsm_send_event_smgr(dd_handle,
              SNS_DDF_SENSOR_ACCEL,
              SNS_DDF_EVENT_ODR_CHANGED);
        }
      }
    }
  }
  return status;
}


/**
 * @brief To check if the other sub device is in active state
 *
 * @param[in]  sub_dev_inx    - the sub device index
 * @param[in]  state               - Handle to a driver instance.
 *
 * @return true - one of the other sub device is in active state.
 */
bool sns_dd_acc_lsm6dsm_is_active_other_sub_dev (
    sns_dd_lsm6dsm_state_t* state,
    uint32_t sub_dev_inx)
{
  uint32_t i, j;
  bool     return_val = false;
  stm_lsm6dsm_sub_dev_s *sub_dev_slot_ptr = &state->sub_dev[0];

  for (i =0; i < LSM6DSM_MAX_SUB_DEV; i++)
  {
    if (i == sub_dev_inx) continue;
    for (j =0; (i < LSM6DSM_MAX_SUB_DEV) &&
        (j < sub_dev_slot_ptr[i].num_sensors) &&
        (j < ARR_SIZE(sub_dev_slot_ptr[i].sensors)); j++)
    {

      if(LSM6DSM_IS_ESP_SENSOR(sub_dev_slot_ptr[i].sensors[j]))
        return_val = LSM6DSM_IS_ESP_ACTIVE(state->esp_info);
      if(LSM6DSM_IS_HUB_SLV_SENSOR(sub_dev_slot_ptr[i].sensors[j]))
        return_val = LSM6DSM_IS_HUB_SLV_ACTIVE(state->hub_info);
      else if(sub_dev_slot_ptr[i].sensors[j] == SNS_DDF_SENSOR_ACCEL) {
        if (state->acc_desired_rate_idx >= 0)
          return_val = true;
      }
      if(return_val == true) {
        LSM6DSM_MSG_3(LOW, "Active  subdev_idx (%d) s_dev_idx(%d) sensor (%d)",i, j, sub_dev_slot_ptr[i].sensors[j]);
        i = LSM6DSM_MAX_SUB_DEV;
      }
    }
  }
  return return_val;
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
static sns_ddf_status_e sns_dd_acc_lsm6dsm_attrib_set_datarate(
    sns_ddf_handle_t dd_handle,
    uint32_t sub_dev_idx,
    sns_ddf_odr_t data_rate)
{
  sns_dd_lsm6dsm_state_t* state = sns_dd_lsm6dsm_get_state(dd_handle);;
  sns_ddf_status_e status = SNS_DDF_SUCCESS;
  int8_t new_rate_idx = -1;
  sns_ddf_odr_t new_rate = 0;
  LSM6DSM_MSG_2(LOW, "acc_attrib_setrate data_rate (%d) fifo_enabled (%d) ", data_rate, state->fifo_info.fifo_enabled);

  //set different data rate
  if (data_rate > 0)
  {
    status =  sns_dd_lsm6dsm_match_odr(dd_handle,
        data_rate,
        &new_rate,
        &new_rate_idx);

    if(SNS_DDF_SUCCESS != status)
      return SNS_DDF_EINVALID_PARAM;

    state->acc_desired_rate = data_rate;

    LSM6DSM_DATA_MSG_3(LOW, "acc_attrib_setrate new_rate_idx (%d) acc_desired_rate_idx (%d) gyr_desired_rate_idx (%d) ",
        new_rate_idx, state->acc_desired_rate_idx, state->gyr_desired_rate_idx);

    //do not update with max rate, useful when gyro is disabled
    state->acc_desired_rate_idx = new_rate_idx;
    new_rate_idx =  sns_dd_lsm6dsm_get_acc_rate(dd_handle);

    if(state->fifo_info.fifo_enabled) {
      status =  sns_dd_lsm6dsm_update_rate(dd_handle, SNS_DDF_SENSOR_ACCEL, new_rate_idx);
      if(SNS_DDF_SUCCESS != status) {
        return status;
      }
      if(state->gyr_cur_rate_idx >= 0)
        state->data_intp.gyr_intp_status = true;
    } else if(!(state->fifo_info.fifo_enabled)) {
      status = sns_dd_acc_lsm6dsm_set_datarate(dd_handle,
          new_rate_idx);
      if(SNS_DDF_SUCCESS != status)
        return status;
    }

    return status;
  } else {
    state->acc_desired_rate_idx = -1;

    //data rate is less than zero
    //turn off accel
    if(!(state->fifo_info.fifo_enabled & ACCEL_FIFO_BM) &&
        (state->fifo_info.acc_fifo_alive == false)) {
      new_rate_idx =  sns_dd_lsm6dsm_get_acc_rate(dd_handle);
      if(new_rate_idx >= 0) {
        LSM6DSM_DATA_MSG_2(HIGH, "new_rate(%d) new_rate_idx (%d)",
            state->odr_list[new_rate_idx], new_rate_idx);
        //update rate
        status = sns_dd_acc_lsm6dsm_set_datarate(dd_handle, new_rate_idx);

        if(SNS_DDF_SUCCESS != status) {
          LSM6DSM_MSG_E_1(ERROR, "set_acc_datarate failed status (%d)", status);
          return status;
        }
      }
    }
  }
  return status;
}

/**
 * @brief Find the matched internal ODR for desired ODR.

 *
 * @param[in]  desired_rate      New desired ODR.
 * @param[out] new_rate          Matched internal ODR.
 * @param[out] new_index         The index of matched internal ODR in lsm6dsm_odr.
 *
 * @return SNS_DDF_SUCCESS if this operation was done successfully. Otherwise
 *         SNS_DDF_EDEVICE, SNS_DDF_EBUS, SNS_DDF_EINVALID_PARAM, or SNS_DDF_EFAIL to
 *         indicate and error has occurred.
 */
sns_ddf_status_e  sns_dd_lsm6dsm_match_odr(
    sns_ddf_handle_t dd_handle,
    sns_ddf_odr_t desired_rate,
    sns_ddf_odr_t *new_rate,
    int8_t *new_index)
{
  uint8_t idx;
  *new_index = -1;

  sns_dd_lsm6dsm_state_t* state = sns_dd_lsm6dsm_get_state(dd_handle);
  if( 0 == desired_rate ) {
    LSM6DSM_MSG_E_3(ERROR, "ODR MATCH failed desired_rate (%d) max_odr_idx (%d) max_odr (%d)",
        desired_rate, state->max_supported_odr_idx, state->odr_list[state->max_supported_odr_idx]);
    return SNS_DDF_EINVALID_PARAM;
  }

  for(idx = state->min_supported_odr_idx; idx<STM_LSM6DSM_ODR_NUM; idx++)
  {
    if( state->device_select ) {
      if(desired_rate <= state->odr_list[idx] * TICKS_PER_SEC / LSM6DSM_ASSUMED_SMGR_S4S_TICKS_PER_SEC)
        break;
    } else {
      if(desired_rate <= state->odr_list[idx])
        break;
    }
  }

  if (idx >= STM_LSM6DSM_ODR_NUM)
    return SNS_DDF_EINVALID_PARAM;

  *new_rate = state->odr_list[idx];
  *new_index = idx;

  return SNS_DDF_SUCCESS;
}
/**
 * @brief Performs a set gyroscope data sampling rate operation
 *
 * @param[in]  dd_handle      Handle to a driver instance.
 * @param[in]  data_rate       Data sampling rate settings for LSM6DSM
 *
 * @return SNS_DDF_SUCCESS if this operation was done successfully. Otherwise
 *         SNS_DDF_EDEVICE, SNS_DDF_EBUS, SNS_DDF_EINVALID_PARAM, or SNS_DDF_EFAIL to
 *         indicate and error has occurred.
 */
static sns_ddf_status_e sns_dd_gyr_lsm6dsm_attrib_set_datarate(
    sns_ddf_handle_t dd_handle,
    uint32_t sub_dev_idx,
    sns_ddf_odr_t data_rate)
{

  sns_dd_lsm6dsm_state_t* state = sns_dd_lsm6dsm_get_state(dd_handle);
  sns_ddf_status_e status = SNS_DDF_SUCCESS;

  sns_ddf_odr_t new_gyr_rate;
  int8_t new_gyr_rate_index;

  LSM6DSM_MSG_2(LOW, "gyr_attrib_setrate data_rate (%d) fifo_enabled (%d)",data_rate, state->fifo_info.fifo_enabled);
  if (data_rate > 0)
  {
    status =  sns_dd_lsm6dsm_match_odr(dd_handle,
        data_rate,
        &new_gyr_rate,
        &new_gyr_rate_index);
    if(SNS_DDF_SUCCESS != status)
      return SNS_DDF_EINVALID_PARAM;

    state->gyr_desired_rate = data_rate;

    LSM6DSM_DATA_MSG_3(LOW, "gyr_attrib_setrate new_gyr_rate_index (%d) acc_desired_rate_idx (%d) gyr_desired_rate_idx (%d) ",
        new_gyr_rate_index, state->acc_desired_rate_idx, state->gyr_desired_rate_idx);

    state->gyr_desired_rate_idx = new_gyr_rate_index;
    if(state->fifo_info.fifo_enabled) {
      status =  sns_dd_lsm6dsm_update_rate(dd_handle, SNS_DDF_SENSOR_GYRO, new_gyr_rate_index);
      if(SNS_DDF_SUCCESS != status) {
        return status;
      }
      if(state->acc_cur_rate_idx >= 0)
        state->data_intp.acc_intp_status = true;
    } else {
      status = sns_dd_gyr_lsm6dsm_set_datarate(dd_handle,
          new_gyr_rate_index, false);
    }

    state->gyr_desired_rate_idx = new_gyr_rate_index;
    return status;
  } else {
    state->gyr_desired_rate_idx = -1;
    //data rate is less than zero
    //turn off gyro
    LSM6DSM_DATA_MSG_2(LOW, "gyr_attrib_setrate data_rate (%d) fifo_enabled (%d) ",data_rate, state->fifo_info.fifo_enabled);
    if(state->fifo_info.fifo_enabled) {
      if(!(state->fifo_info.fifo_enabled & GYRO_FIFO_BM)) {
        sns_dd_gyr_lsm6dsm_set_datarate(dd_handle,
            -1, true);

      }
      state->gyr_desired_rate_idx = -1;
      return status;
    } else {
      sns_dd_gyr_lsm6dsm_set_datarate(dd_handle,
          -1, true);

      state->gyr_desired_rate_idx = -1;
      return status;
    }
  }
  return status;
}

sns_ddf_status_e sns_dd_lsm6dsm_temp_set_rate(sns_ddf_handle_t dd_handle, uint8_t value)
{
  sns_dd_lsm6dsm_state_t* state = sns_dd_lsm6dsm_get_state(dd_handle);;
  uint32_t sub_dev_idx = (dd_handle_align_t)dd_handle & (~DD_HANDLE_ALIGN_BITS);
  sns_ddf_sensor_e p_sensor= state->sub_dev[sub_dev_idx].sensors[0];
  uint8_t idx = 0, t_idx = 0, temp_enabled = 0;
  //initialize temp_enabled
  if(state->a_temp_rate)
    temp_enabled |= 0x01;
  if(state->g_temp_rate)
    temp_enabled |= 0x10;
  if(p_sensor == SNS_DDF_SENSOR_ACCEL) {
    idx = ACCEL_FIFO_BM;
    t_idx = 0x0F;
  } else if(p_sensor == SNS_DDF_SENSOR_GYRO) {
    idx = GYRO_FIFO_BM;
    t_idx = 0xF0;
  }

  if(value) {
    //set_odr
    //check fifo is enabled for p_sensor and temp odr is set for p_sensor
    if((temp_enabled & t_idx) &&
        (state->fifo_info.fifo_enabled & idx)) {
      if(state->temp_timer == NULL) {
        if((NULL == state->fifo_info.temp_data.samples))
          sns_dd_lsm6dsm_alloc_buff(dd_handle, SNS_DDF_SENSOR_TEMP, STM_LSM6DSM_MAX_TEMP_FIFO_DEPTH);
        sns_ddf_timer_init(&state->temp_timer, dd_handle, &sns_dd_lsm6dsm_if, NULL, true);
        sns_ddf_timer_start(state->temp_timer, 1000000u);
        LSM6DSM_MSG_3(HIGH, "Temp timer started: a_temp_rate (%d) g_temp_rate (%d) fifo_enabled (0x%x)", state->a_temp_rate, state->g_temp_rate, state->fifo_info.fifo_enabled);
      }
      if(((p_sensor == SNS_DDF_SENSOR_ACCEL) &&
            (state->acc_desired_rate_idx >= 0)) ||
          ((p_sensor == SNS_DDF_SENSOR_GYRO) &&
           (state->gyr_desired_rate_idx >= 0)))

        state->fifo_info.fifo_enabled |= (idx << 2);
    }
  } else {
    if(!temp_enabled) {
      if(state->temp_timer != NULL) {
        LSM6DSM_MSG_3(HIGH, "Temp timer cancelled: a_temp_rate (%d) g_temp_rate (%d) fifo_enabled (0x%x)", state->a_temp_rate, state->g_temp_rate, state->fifo_info.fifo_enabled);
        sns_ddf_timer_cancel(state->temp_timer);
        sns_ddf_timer_release(state->temp_timer);
        state->temp_timer = NULL;
        state->fifo_info.fifo_enabled &= (~0x0C);
        if((NULL != state->fifo_info.temp_data.samples))
          sns_dd_lsm6dsm_free_buff(dd_handle, SNS_DDF_SENSOR_TEMP);
      }
    }
    if(state->temp_timer != NULL) {
      //fifo mode
      state->fifo_info.fifo_enabled &= ~(idx << 2);

    }
  }

  return SNS_DDF_SUCCESS;
}


/**
 * @brief Resets the driver and device so they return to the state they were
 *        in after init() was called.
 *
 * Refer to sns_ddf_driver_if.h for definition.
 */
sns_ddf_status_e sns_dd_lsm6dsm_reset(sns_ddf_handle_t dd_handle)
{
  sns_dd_lsm6dsm_state_t* state = (sns_dd_lsm6dsm_state_t*)
    ((dd_handle_align_t)dd_handle & DD_HANDLE_ALIGN_BITS);
  uint32_t sub_dev_idx;
  stm_lsm6dsm_sub_dev_s *sub_dev_slot_ptr;
  uint32_t i = 0;
  uint8_t rw_buffer[5] = {0};
  sns_ddf_status_e status = SNS_DDF_SUCCESS;
  bool reset = true;

  sub_dev_idx = (dd_handle_align_t)dd_handle & (~DD_HANDLE_ALIGN_BITS);
  if ( sub_dev_idx < ARR_SIZE(state->sub_dev) )
  {
    sub_dev_slot_ptr = &state->sub_dev[sub_dev_idx];
  }
  else
  {
    return SNS_DDF_EFAIL;
  }

  LSM6DSM_MSG_2(LOW, "Reset - called for subdev_idx (%d) sensor (%d)", sub_dev_idx, sub_dev_slot_ptr->sensors[0]);

  if((LSM6DSM_IS_ESP_SENSOR(sub_dev_slot_ptr->sensors[0])) &&
      (state->esp_info.esp_if == NULL))
    return status;

  if((LSM6DSM_IS_HUB_SLV_SENSOR(sub_dev_slot_ptr->sensors[0])) &&
      (state->hub_info.hub_if == NULL))
    return status;
  switch (sub_dev_slot_ptr->sensors[0])
  {
    case SNS_DDF_SENSOR_ACCEL:
      if(sub_dev_slot_ptr->powerstate != SNS_DDF_POWERSTATE_LOWPOWER)
        sns_dd_acc_lsm6dsm_set_power(dd_handle, SNS_DDF_POWERSTATE_LOWPOWER);
      break;
    case SNS_DDF_SENSOR_GYRO:
      if(sub_dev_slot_ptr->powerstate != SNS_DDF_POWERSTATE_LOWPOWER)
        sns_dd_gyr_lsm6dsm_set_power(dd_handle, SNS_DDF_POWERSTATE_LOWPOWER);
      break;
    default:
      break;
  }

  for (i =0; i < LSM6DSM_MAX_SUB_DEV; i++)
  {
    if((state->sub_dev[i].powerstate != SNS_DDF_POWERSTATE_LOWPOWER) &&
        (state->sub_dev[i].num_sensors)) {
      LSM6DSM_MSG_3(LOW, "Reset - sensor (%d) sub_dev (%d) power_state (%d)", state->sub_dev[i].sensors[0], i, state->sub_dev[i].powerstate);
      reset = false;
      break;
    }
  }

  if(reset != true) {
    /*TODO check if the resetting sensor is active
     * if active reset the variables */
    if(LSM6DSM_IS_ESP_SENSOR(sub_dev_slot_ptr->sensors[0])) {
      if(state->esp_info.esp_if)
        state->esp_info.esp_if->reset(dd_handle);
    }
    if(LSM6DSM_IS_HUB_SLV_SENSOR(sub_dev_slot_ptr->sensors[0])) {
      if(state->hub_info.hub_if)
        state->hub_info.hub_if->reset(dd_handle);
    }
    return SNS_DDF_SUCCESS;
  }

  //async read
  if(state->bus_id == SNS_DDF_BUS_SPI) {
    //disable I2C in case other SPI device affect LSM6DSM.
    rw_buffer[0] = 0x04;
    status = sns_dd_lsm6dsm_write_reg(dd_handle, STM_LSM6DSM_REG_CTRL4, rw_buffer, 1, 0xFF);
    if(status != SNS_DDF_SUCCESS) {
      LSM6DSM_MSG_E_1(ERROR, "write_reg failed- status (%d)",status);
      return status;
    }

    rw_buffer[0] = 0x30;
    status = sns_dd_lsm6dsm_write_reg(
        state,
        STM_LSM6DSM_REG_FIFO_CTRL2,
        rw_buffer,
        1,
        0x30);
    if(status != SNS_DDF_SUCCESS) {
      LSM6DSM_MSG_E_1(ERROR, "write reg failed  status=%u", status);
      return status;
    }
  }
  //set FIFO CTRL to defaults
  rw_buffer[0] = 0x0;
  rw_buffer[1] = 0x0;
  rw_buffer[2] = 0x0;
  rw_buffer[3] = 0x0;
  rw_buffer[4] = 0x0;

  status = sns_dd_lsm6dsm_write_reg(
      dd_handle,
      STM_LSM6DSM_REG_FIFO_CTRL1,
      rw_buffer,
      5,
      0xFF);
  if(status != SNS_DDF_SUCCESS) {
    LSM6DSM_MSG_E_1(ERROR, "write_reg failed- status (%d)",status);
    return status;
  }

  rw_buffer[0] = 0x0;
  rw_buffer[1] = 0x0;

  status = sns_dd_lsm6dsm_write_reg(
      dd_handle,
      STM_LSM6DSM_REG_INT1_CTRL,
      rw_buffer,
      2,
      0xFF);
  if(status != SNS_DDF_SUCCESS) {
    LSM6DSM_MSG_E_1(ERROR, "write_reg failed- status (%d)",status);
    return status;
  }

  // Configure control register 3
  rw_buffer[0] = 0x0
    | (0<<7)           // BOOT bit
    | (1<<6)           // BDU bit
    | (0<<5)           // H_LACTIVE bit
    | (0<<4)           // PP_OD bit
    | (0<<3)           // SIM bit
    | (1<<2)           // IF_INC
    | (0<<1)           // BLE
    | 0;               // SW_RESET
  status = sns_dd_lsm6dsm_write_reg(
      dd_handle,
      STM_LSM6DSM_REG_CTRL3,
      rw_buffer,
      1,
      0xFF);
  if(status != SNS_DDF_SUCCESS) {
    LSM6DSM_MSG_E_1(ERROR, "write_reg failed- status (%d)",status);
    return status;
  }

  state->acc_cur_rate_idx = -1;

  if(state->acc_range_idx < 0) {
    status = sns_dd_acc_lsm6dsm_set_range(dd_handle, 2);
    if(status != SNS_DDF_SUCCESS) {
      LSM6DSM_MSG_E_1(ERROR, "set range failed - status (%d)",status);
      return status;
    }
  }

  if(state->acc_lp_mode) {
    rw_buffer[0] = 0x10;
    status = sns_dd_lsm6dsm_write_reg(
        dd_handle,
        STM_LSM6DSM_REG_CTRL6_G,
        rw_buffer,
        1,
        0x10);
    if(status != SNS_DDF_SUCCESS) {
      LSM6DSM_MSG_1(HIGH,"set acc performance failed - status (%d)",status);
      return status;
    }
  }
  //workaround enable HPF for XL here
  //initialize with high threshold
  rw_buffer[0] = 0x3F;
  status = sns_dd_lsm6dsm_write_reg(
      state,
      STM_LSM6DSM_REG_WAKE_THS,
      rw_buffer,
      1,
      0x3F);
  if(status != SNS_DDF_SUCCESS) {
    LSM6DSM_MSG_E_1(ERROR, "write reg failed  status=%u", status);
    return status;
  }
  rw_buffer[0] = 0
    | (1<<7)            // ENable Hardcoded interrupts??
    | (0<<6)            // 0
    | (0<<5)            // 0
    | (1<<4)            // SLOPE_FDS: refer to figure 5.
    | (0<<3)            // TAP_X_EN:
    | (0<<2)            // TAP_Y_EN:
    | (0<<1)            // TAP_Z_EN:
    | 0;                   // LIR: 0-interrupt not latched; 1-latched.
  status = sns_dd_lsm6dsm_write_reg(
      state,
      STM_LSM6DSM_REG_TAP_CFG,
      rw_buffer,
      1,
      0x80);
  if(status != SNS_DDF_SUCCESS) {
    LSM6DSM_MSG_E_1(ERROR, "write reg failed  status=%u", status);
    return status;
  }

  status = sns_dd_acc_lsm6dsm_set_datarate(dd_handle, -1);
  if(SNS_DDF_SUCCESS != status)
    return status;

  status = sns_dd_gyr_lsm6dsm_set_datarate(dd_handle, -1, false);
  if(status != SNS_DDF_SUCCESS) {
    LSM6DSM_MSG_E_1(ERROR, "write_reg failed- status (%d)",status);
    return status;
  }

  status = sns_dd_gyr_lsm6dsm_set_range(dd_handle, 4);
  if(status != SNS_DDF_SUCCESS) {
    LSM6DSM_MSG_E_1(ERROR, "set range failed - status (%d)",status);
    return status;
  }

  state->md_desired = false;
  state->acc_desired_rate_idx = -1;

  state->fifo_info.acc_sample_cnt = 0;
  state->data_intp.acc_intp_status = false;
  state->fifo_info.acc_fifo_alive = false;
  state->data_intp.acc_last_sample_status = false;

  state->gyr_desired_rate_idx = -1;
  state->fifo_info.gyr_sample_cnt = 0;
  state->data_intp.gyr_intp_status = false;
  state->data_intp.gyr_last_sample_status = false;

  state->a_temp_rate = 0;
  state->g_temp_rate = 0;

  //update fifo parameters
  state->fifo_info.fifo_enabled = 0;
  state->fifo_info.fifo_int_enabled = 0;
  state->fifo_info.active_sensors = 0;
  state->fifo_info.acc_wmk = 0;
  state->fifo_info.gyr_wmk = 0;
  //only reset last_timestamp after reset or after fifo disabled.
  state->fifo_info.last_timestamp = 0;
  state->fifo_info.avg_sample_time = 0;
  state->gyr_sleep = false;

  //reset s4s parameters
  state->s4s_config.fifo_int_en = true;
  state->s4s_config.synced = STM_LSM6DSM_S4S_NOT_SYNCED;
  state->s4s_config.stdt_sensor = SNS_DDF_SENSOR__NONE;
  LSM6DSM_MSG_E_1(HIGH,"Setting stdt_sensor %d", state->s4s_config.stdt_sensor);
  state->s4s_config.sensor_sbsp = STM_LSM6DSM_BM__NONE;
  state->s4s_config.config_changed = false;

  if(state->esp_info.esp_if)
    state->esp_info.esp_if->reset(dd_handle);

  return SNS_DDF_SUCCESS;
}

sns_ddf_status_e sns_dd_lsm6dsm_sharedFifo_info(sns_ddf_handle_t dd_handle,
    sns_ddf_sensor_e sensor,
    sns_ddf_fifo_share_sensor_s* shared_sensors_info,
    uint8_t* shared_cnt)
{

  uint8_t i = 0;
  sns_dd_lsm6dsm_state_t* state = (sns_dd_lsm6dsm_state_t*)
    ((dd_handle_align_t)dd_handle & DD_HANDLE_ALIGN_BITS);
  sns_ddf_sensor_e shared_sensors[] = {SNS_DDF_SENSOR_ACCEL, SNS_DDF_SENSOR_GYRO, LSM6DSM_SLAVE_SENSOR};
  uint32_t s_dev_idx;
  sns_ddf_status_e status = SNS_DDF_SUCCESS;

  *shared_cnt = 0;
  for(i = 0; i < ARR_SIZE(shared_sensors); i++) {
    if(sensor != shared_sensors[i]) {
      status = lsm6dsm_search_subdev_by_sensortype(
          state,
          shared_sensors[i],
          &s_dev_idx);
      if(status == SNS_DDF_SUCCESS) {
        shared_sensors_info[*shared_cnt].sensor =  shared_sensors[i];
        shared_sensors_info[*shared_cnt].dd_handle = (sns_ddf_handle_t)((dd_handle_align_t)state |
            (dd_handle_align_t)s_dev_idx);
        *shared_cnt =  *shared_cnt + 1;
      }
    }
  }
  return SNS_DDF_SUCCESS;
}

/**
 * @brief Initializes the lsm6dsm driver and sets up sensor.
 *
 * Refer to sns_ddf_driver_if.h for definition.
 */
sns_ddf_status_e sns_dd_lsm6dsm_init(
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
  sns_dd_lsm6dsm_state_t* state;
  uint8_t rw_buffer = 0;
  uint8_t rw_bytes = 0;
  uint32_t my_num_sensors = 0;
  int32_t sub_dev_idx = 0;
  sns_ddf_time_t cur_time = 0;

#if UIMAGE_SUPPORT
  /* Update smgr sensor data for the driver to indicate uImage support */
  sns_ddf_smgr_set_uimg_refac(smgr_handle);

#endif

  /* check if this init() is a call for an existing device */
  state = dd_find_same_port_dev(&device_info->port_config);

  LSM6DSM_MSG_2(HIGH, "INIT num_sensors (%d) sensor %d",*num_sensors, *sensors[0]);
  if ( NULL == state)
  {
    LSM6DSM_MSG_0(HIGH, "INIT state NULL");
    /* Allocate a device instance and initialize it */
    status = sns_dd_lsm6dsm_malloc((void**)&state, sizeof(sns_dd_lsm6dsm_state_t), smgr_handle);
    if(status != SNS_DDF_SUCCESS)
      return SNS_DDF_ENOMEM;
    memset(state, 0, sizeof(sns_dd_lsm6dsm_state_t));

    *dd_handle_ptr = state;
    state->next = lsm6dsm_dd_head.next;
    lsm6dsm_dd_head.next = state;
    sns_ddf_get_port_id(&device_info->port_config,
      &state->port_id);

    sub_dev_idx = (dd_handle_align_t)state & (~DD_HANDLE_ALIGN_BITS);

    /* this init() call is for first sub_dev */
    my_num_sensors = dd_fill_sub_dev_slot(&state->sub_dev[sub_dev_idx],
        *num_sensors,
        *sensors);
    *num_sensors = my_num_sensors;
    *sensors = state->sub_dev[sub_dev_idx].sensors;
    LSM6DSM_MSG_2(HIGH, "INIT num_sensors (%d) sensor %d",*num_sensors, *sensors[0]);
    if ( 0 == my_num_sensors ) {
      sns_dd_lsm6dsm_mfree(state, smgr_handle);
      lsm6dsm_dd_head.next = NULL;
      return SNS_DDF_EINVALID_DATA;
    }

    // Open communication port to the device.
    status = sns_ddf_open_port(&state->port_handle,
        &device_info->port_config);
    if(status != SNS_DDF_SUCCESS)
    {
      sns_dd_lsm6dsm_mfree(state, smgr_handle);
      lsm6dsm_dd_head.next = NULL;
      return status;
    }

    // confirm WHO_AM_I register
    status = sns_ddf_read_port(
        state->port_handle,
        STM_LSM6DSM_REG_WHO_AM_I,
        &rw_buffer,
        1,
        &rw_bytes);
    if(status != SNS_DDF_SUCCESS) {
      LSM6DSM_MSG_E_1(ERROR, "read_port failed- status (%d)",status);
      sns_ddf_close_port(state->port_handle);
      sns_dd_lsm6dsm_mfree(state, smgr_handle);
      lsm6dsm_dd_head.next = NULL;
      return status;
    }
    if((rw_bytes!=1) ||
        (rw_buffer != STM_LSM6DSM_WHOAMI_VALUE)) {
      LSM6DSM_MSG_E_3(ERROR, "read_port failed (bytes count or WHOAMI failed)-\
          rw_bytes (%d) rw_buffer (0x%x) WHOAMI (0x%x)",rw_bytes, rw_buffer, STM_LSM6DSM_WHOAMI_VALUE);
      sns_ddf_close_port(state->port_handle);
      sns_dd_lsm6dsm_mfree(state, smgr_handle);
      lsm6dsm_dd_head.next = NULL;
      return SNS_DDF_EFAIL;
    }

    state->axes_mapped = false;
    if((*sensors[0] == SNS_DDF_SENSOR_ACCEL) ||
        (*sensors[0] == SNS_DDF_SENSOR_GYRO)) {
      //copy axis config from NV_PARAMS
      sns_ddf_axes_map_init(&state->axes_map,
          ((nv_params != NULL) ? nv_params->data : stm_lsm6dsm_axis_dflt));
      state->axes_mapped = true;
      // device_select = 0, Non-s4s
      // decice_select non-zero S4S
      state->device_select = device_info->device_select;
      if(state->device_select) {
        state->odr_list = lsm6dsm_s4s_odr;
        state->max_supported_odr_idx = STM_LSM6DSM_MAX_S4S_ODR_IDX;
        state->min_supported_odr_idx = STM_LSM6DSM_MIN_S4S_ODR_IDX;
      } else {
        state->odr_list = lsm6dsm_non_s4s_odr;
        state->max_supported_odr_idx = STM_LSM6DSM_MAX_ODR_IDX;
        state->min_supported_odr_idx = STM_LSM6DSM_MIN_ODR_IDX;
      }
    }

    // Fill out output and driver parameters.
    state->bus_id = device_info->port_config.bus;

    state->sub_dev[sub_dev_idx].smgr_handle = smgr_handle;
    state->sub_dev[sub_dev_idx].powerstate = SNS_DDF_POWERSTATE_LOWPOWER;
    state->gpio_num = device_info->first_gpio;
    state->acc_desired_rate_idx = -1;
    state->gyr_desired_rate_idx = -1;
    state->g_timer.timer = NULL;
    state->md_timer.timer = NULL;
    state->temp_timer = NULL;
    state->int_registered = false;
    state->fifo_info.acc_data.samples = NULL;
    state->fifo_info.temp_data.samples = NULL;
    state->fifo_info.gyr_data.samples = NULL;
    state->fifo_info.raw_buffer = NULL;
    state->fifo_info.fifo_enabled = 0;
    state->fifo_info.fifo_int_enabled = 0;
    state->fifo_info.temp_sample_cnt = 0;
    state->fifo_info.acc_wmk = 0;
    state->fifo_info.gyr_wmk = 0;
    //initializing fifo pattern array, acc and gyr odr are same
    //TODO need to change if acc and gyr odr are different
    state->fifo_info.pattern_samples_cnt = 0;//only acc and gyr
    //gyr is 2 and acc is 1
    state->fifo_info.pattern_array[0] = 2;
    state->fifo_info.pattern_array[1] = 1;
    state->fifo_info.active_sensors = 0;
    state->fifo_info.fifo_rate_idx = -1;
    state->acc_range_idx = -1;
    state->gyr_range_idx = -1;
    state->acc_cur_rate_idx = -1;
    state->gyr_cur_rate_idx = -1;
    state->a_temp_rate = 0;
    state->g_temp_rate = 0;
    state->gyr_sleep = false;
    state->esp_info.esp_enabled = 0;
#if ACC_LOWPOWER_MODE
    state->acc_lp_mode = true;
#else
    state->acc_lp_mode = false;
#endif
#if LSM6DSM_ENABLE_ESP
    state->esp_info.esp_if = &sns_dd_lsm6dsm_esp_if;
#else
    state->esp_info.esp_if = NULL;
#endif

#if LSM6DSM_ENABLE_HUB
    state->hub_info.hub_if = &sns_dd_lsm6dsm_hub_if;
#else
    state->hub_info.hub_if = NULL;
#endif

    if(LSM6DSM_IS_ESP_SENSOR(*sensors[0])) {
      if(state->esp_info.esp_if == NULL) {
        sns_ddf_close_port(state->port_handle);
        sns_dd_lsm6dsm_mfree(state, smgr_handle);
        status = SNS_DDF_EINVALID_PARAM;
        LSM6DSM_MSG_E_2(ERROR, "ESP not enabled - Init failed sensor (%d) status (%d)",*sensors[0], status);
        lsm6dsm_dd_head.next = NULL;
        return status;
      }
    }
    if(LSM6DSM_IS_HUB_SLV_SENSOR(*sensors[0])) {
      if(state->hub_info.hub_if == NULL) {
        sns_ddf_close_port(state->port_handle);
        sns_dd_lsm6dsm_mfree(state, smgr_handle);
        status = SNS_DDF_EINVALID_PARAM;
        LSM6DSM_MSG_E_2(ERROR, "HUB not enabled - Init failed sensor (%d) status (%d)",*sensors[0], status);
        lsm6dsm_dd_head.next = NULL;
        return status;
      }
    }
    // Default S4S params
    state->s4s_config.fifo_int_en = true;
    state->s4s_config.synced = STM_LSM6DSM_S4S_NOT_SYNCED;
    state->s4s_config.stdt_sensor = SNS_DDF_SENSOR__NONE;
    LSM6DSM_MSG_E_1(HIGH,"Setting stdt_sensor %d", state->s4s_config.stdt_sensor);
    state->s4s_config.sensor_sbsp = STM_LSM6DSM_BM__NONE;
    state->s4s_config.config_changed = false;

    //sw reset
    rw_buffer = 0x01; //set SW_RESET
    status = sns_dd_lsm6dsm_write_reg(
        state,
        STM_LSM6DSM_REG_CTRL3,
        &rw_buffer,
        1,
        0x01);
    if(status != SNS_DDF_SUCCESS) {
      LSM6DSM_MSG_E_1(ERROR, "write_reg failed- status (%d)",status);
      sns_ddf_close_port(state->port_handle);
      sns_dd_lsm6dsm_mfree(state, smgr_handle);
      lsm6dsm_dd_head.next = NULL;
      return status;
    }
    cur_time = sns_ddf_get_timestamp();
    do {
      if(sns_ddf_get_timestamp() > (cur_time + sns_ddf_convert_usec_to_tick(10000))) {
        LSM6DSM_MSG_E_3(ERROR, "cur_time (%u) now (%u) delay (%u) ",
            cur_time, sns_ddf_get_timestamp(), sns_ddf_convert_usec_to_tick(10000));
        status = SNS_DDF_EFAIL;
      } else {
        //1ms wait
        sns_ddf_delay(1000);
        status = sns_ddf_read_port(
            state->port_handle,
            STM_LSM6DSM_REG_CTRL3,
            &rw_buffer,
            1,
            &rw_bytes);
        if(status != SNS_DDF_SUCCESS) {
          LSM6DSM_MSG_E_1(ERROR, "read_port failed- status (%d)",status);
        }
        if(rw_bytes != 1) {
          LSM6DSM_MSG_E_1(ERROR, "read_port failed-  read_count  does not match - read_count (%d)",rw_bytes);
          status = SNS_DDF_EBUS;
        }
      }
      if(status != SNS_DDF_SUCCESS) {
        sns_ddf_close_port(state->port_handle);
        sns_dd_lsm6dsm_mfree(state, smgr_handle);
        lsm6dsm_dd_head.next = NULL;
        return status;
      }
    } while((rw_buffer & 0x01));

    status = sns_dd_lsm6dsm_reset(state);
    if(status != SNS_DDF_SUCCESS)
    {
      LSM6DSM_MSG_E_1(ERROR, "reset failed  status=%u", status);
      sns_ddf_close_port(state->port_handle);
      sns_dd_lsm6dsm_mfree(state, smgr_handle);
      lsm6dsm_dd_head.next = NULL;
      return status;
    }
    if(state->esp_info.esp_if)
      state->esp_info.esp_if->init(dd_handle_ptr,
          smgr_handle,
          nv_params,
          device_info,
          num_devices,
          memhandler,
          sensors,
          num_sensors);
    if(LSM6DSM_IS_HUB_SLV_SENSOR(*sensors[0]) &&
        (state->hub_info.hub_if)) {
      status = state->hub_info.hub_if->init(dd_handle_ptr,
          smgr_handle,
          nv_params,
          device_info,
          num_devices,
          memhandler,
          sensors,
          num_sensors);
      if(status != SNS_DDF_SUCCESS) {
        sns_ddf_close_port(state->port_handle);
        sns_dd_lsm6dsm_mfree(state, smgr_handle);
        lsm6dsm_dd_head.next = NULL;
        return status;
      }
    }

    //only reset last_timestamp after reset or after fifo disabled.
    state->fifo_info.last_timestamp = 0;
    state->fifo_info.avg_sample_time = 0;

    status =  sns_ddf_signal_register(
       state->gpio_num,
       state,
       &sns_dd_lsm6dsm_if,
       SNS_DDF_SIGNAL_IRQ_RISING);

    if(status != SNS_DDF_SUCCESS) {
      sns_ddf_close_port(state->port_handle);
      sns_dd_lsm6dsm_mfree(state, smgr_handle);
      lsm6dsm_dd_head.next = NULL;
      return status;
    }

    LSM6DSM_MSG_2(HIGH, "INIT Success sub_dev_idx (%d) sensor %d",sub_dev_idx, *sensors[0]);

  }
  else /* case the device instance is already there */
  {
    sns_ddf_handle_t dd_handle;
    LSM6DSM_MSG_0(HIGH, "INIT state not NULL");

    sub_dev_idx = dd_find_free_sub_dev_slot(state);
    if ( -1 == sub_dev_idx )
    {
      LSM6DSM_MSG_0(ERROR, "no free sub dev slot");
      return SNS_DDF_ENOMEM;
    }
    else
    {
      my_num_sensors = dd_fill_sub_dev_slot(&state->sub_dev[sub_dev_idx],
          *num_sensors,
          *sensors);

      // Fill out output parameters.
      *num_sensors = my_num_sensors;
      *sensors = state->sub_dev[sub_dev_idx].sensors;
      if ( 0 == my_num_sensors )
        return SNS_DDF_EINVALID_DATA;

      if(LSM6DSM_IS_ESP_SENSOR(*sensors[0])) {
        if(state->esp_info.esp_if == NULL) {
          status = SNS_DDF_EINVALID_PARAM;
          LSM6DSM_MSG_E_2(ERROR, "ESP not enabled - Init failed sensor (%d) status (%d)",*sensors[0], status);
          return status;
        }
      }
      if(LSM6DSM_IS_HUB_SLV_SENSOR(*sensors[0])) {
        if(state->hub_info.hub_if == NULL) {
          status = SNS_DDF_EINVALID_PARAM;
          LSM6DSM_MSG_E_2(ERROR, "ESP not enabled - Init failed sensor (%d) status (%d)",*sensors[0], status);
          return status;
        }

      }
      // dd_handle = (sns_ddf_handle_t)((dd_handle_align_t)state & sub_dev_idx);
      dd_handle = (sns_ddf_handle_t)(((dd_handle_align_t)state & DD_HANDLE_ALIGN_BITS) | (dd_handle_align_t)sub_dev_idx);
      *dd_handle_ptr = dd_handle;
      state->sub_dev[sub_dev_idx].smgr_handle = smgr_handle;
      state->sub_dev[sub_dev_idx].powerstate = SNS_DDF_POWERSTATE_LOWPOWER;
      if(LSM6DSM_IS_HUB_SLV_SENSOR(*sensors[0]) &&
          (state->hub_info.hub_if)) {
        status = state->hub_info.hub_if->init(dd_handle_ptr,
            smgr_handle,
            nv_params,
            device_info,
            num_devices,
            memhandler,
            sensors,
            num_sensors);
        if(status != SNS_DDF_SUCCESS) {
          state->sub_dev[sub_dev_idx].num_sensors = 0;
          return status;
        }
      }
      if (state->axes_mapped != true) {
        if((*sensors[0] == SNS_DDF_SENSOR_ACCEL) ||
            (*sensors[0] == SNS_DDF_SENSOR_GYRO)) {
          //copy axis config from NV_PARAMS
          sns_ddf_axes_map_init(&state->axes_map,
              ((nv_params != NULL) ? nv_params->data : stm_lsm6dsm_axis_dflt));
          state->axes_mapped = true;
          // device_select = 0, Non-s4s
          // decice_select non-zero S4S
          state->device_select = device_info->device_select;
          if(state->device_select) {
            state->odr_list = lsm6dsm_s4s_odr;
            state->max_supported_odr_idx = STM_LSM6DSM_MAX_S4S_ODR_IDX;
            state->min_supported_odr_idx = STM_LSM6DSM_MIN_S4S_ODR_IDX;
          } else {
            state->odr_list = lsm6dsm_non_s4s_odr;
            state->max_supported_odr_idx = STM_LSM6DSM_MAX_ODR_IDX;
            state->min_supported_odr_idx = STM_LSM6DSM_MIN_ODR_IDX;
          }
        }
      }
    }
    LSM6DSM_MSG_2(HIGH, "INIT Success sub_dev_idx (%d) sensor %d",sub_dev_idx, *sensors[0]);
  }

  LSM6DSM_MSG_3(HIGH, "INIT state (%p) dd_handle_ptr (%p) sub_dev_idx %d ",state, *dd_handle_ptr, sub_dev_idx);
  return SNS_DDF_SUCCESS;
}

/**
 * @brief Retrieves the value of an attribute for a lsm6dsm sensor.
 *
 * Refer to sns_ddf_driver_if.h for definition.
 */
sns_ddf_status_e sns_dd_lsm6dsm_get_attr(
    sns_ddf_handle_t dd_handle,
    sns_ddf_sensor_e sensor,
    sns_ddf_attribute_e attrib,
    sns_ddf_memhandler_s* memhandler,
    void** value,
    uint32_t* num_elems)
{
  sns_dd_lsm6dsm_state_t *state;
  uint32_t sub_dev_idx;
  sns_ddf_sensor_e ddf_sensor_type;

  if (dd_handle == NULL || value == NULL) {
    LSM6DSM_MSG_E_0(ERROR, "dd_handle is NULL");
    return SNS_DDF_EINVALID_PARAM;
  }

  state = sns_dd_lsm6dsm_get_state(dd_handle);
  sub_dev_idx = (dd_handle_align_t)dd_handle & (~DD_HANDLE_ALIGN_BITS);
  ddf_sensor_type = state->sub_dev[sub_dev_idx].sensors[0]; // '0' --> Primary
  LSM6DSM_MSG_3(LOW, "GET_ATTRIB attrib (%d) sensor (%d) p_sensor (%d)",attrib, sensor, ddf_sensor_type);

  if((attrib != SNS_DDF_ATTRIB_IO_REGISTER) &&
      (attrib != SNS_DDF_ATTRIB_DRIVER_INFO)) {
    if(LSM6DSM_IS_ESP_SENSOR(ddf_sensor_type)) {
      if(state->esp_info.esp_if)
        return state->esp_info.esp_if->get_attrib(dd_handle, sensor, attrib, memhandler, value, num_elems);
      else
        return SNS_DDF_EINVALID_PARAM;
    }
    if(LSM6DSM_IS_HUB_SLV_SENSOR(ddf_sensor_type)) {
      if(state->hub_info.hub_if)
        return state->hub_info.hub_if->get_attrib(dd_handle, sensor, attrib, memhandler, value, num_elems);
      else
        return SNS_DDF_EINVALID_PARAM;
    }
  }

  switch(attrib)
  {
    case SNS_DDF_ATTRIB_POWER_INFO:
      {
        sns_ddf_power_info_s* power = sns_dd_lsm6dsm_memhandler_malloc(
            memhandler, sizeof(sns_ddf_power_info_s), state->sub_dev[sub_dev_idx].smgr_handle);
        if(NULL == power)
          return SNS_DDF_ENOMEM;
        //current consumption, unit uA
        if(ddf_sensor_type == SNS_DDF_SENSOR_ACCEL) {
          power->active_current = 150;
          power->lowpower_current = 3;
        }
        else if(ddf_sensor_type == SNS_DDF_SENSOR_GYRO){
          power->active_current = 450;
          power->lowpower_current = 3;
        }
        else {
          return SNS_DDF_EINVALID_PARAM;
        }
        *value = power;
        *num_elems = 1;
        return SNS_DDF_SUCCESS;
      }

    case SNS_DDF_ATTRIB_RANGE:
      {
        sns_ddf_range_s* ranges = NULL;
        if(sensor == SNS_DDF_SENSOR_ACCEL)
        {
          ranges = sns_dd_lsm6dsm_memhandler_malloc(
              memhandler, ARR_SIZE(lsm6dsm_acc_ranges) * sizeof(sns_ddf_range_s), state->sub_dev[sub_dev_idx].smgr_handle);
          if(NULL == ranges)
            return SNS_DDF_ENOMEM;
          ranges[0].min = STM_LSM6DSM_ACC_RANGE_2G_MIN;
          ranges[0].max = STM_LSM6DSM_ACC_RANGE_2G_MAX;
          ranges[1].min = STM_LSM6DSM_ACC_RANGE_4G_MIN;
          ranges[1].max = STM_LSM6DSM_ACC_RANGE_4G_MAX;
          ranges[2].min = STM_LSM6DSM_ACC_RANGE_8G_MIN;
          ranges[2].max = STM_LSM6DSM_ACC_RANGE_8G_MAX;
          ranges[3].min = STM_LSM6DSM_ACC_RANGE_16G_MIN;
          ranges[3].max = STM_LSM6DSM_ACC_RANGE_16G_MAX;
          *num_elems = ARR_SIZE(lsm6dsm_acc_ranges);
        }
        else if(sensor == SNS_DDF_SENSOR_GYRO)
        {
          ranges = sns_dd_lsm6dsm_memhandler_malloc(
              memhandler, ARR_SIZE(lsm6dsm_gyr_ranges) * sizeof(sns_ddf_range_s), state->sub_dev[sub_dev_idx].smgr_handle);
          if(NULL == ranges)
            return SNS_DDF_ENOMEM;

          ranges[0].min = STM_LSM6DSM_GYR_RANGE_125_MIN;
          ranges[0].max = STM_LSM6DSM_GYR_RANGE_125_MAX;
          ranges[1].min = STM_LSM6DSM_GYR_RANGE_245_MIN;
          ranges[1].max = STM_LSM6DSM_GYR_RANGE_245_MAX;
          ranges[2].min = STM_LSM6DSM_GYR_RANGE_500_MIN;
          ranges[2].max = STM_LSM6DSM_GYR_RANGE_500_MAX;
          ranges[3].min = STM_LSM6DSM_GYR_RANGE_1000_MIN;
          ranges[3].max = STM_LSM6DSM_GYR_RANGE_1000_MAX;
          ranges[4].min = STM_LSM6DSM_GYR_RANGE_2000_MIN;
          ranges[4].max = STM_LSM6DSM_GYR_RANGE_2000_MAX;
          *num_elems = ARR_SIZE(lsm6dsm_gyr_ranges);
        }
        else if(sensor == SNS_DDF_SENSOR_TEMP)
        {
          ranges = sns_dd_lsm6dsm_memhandler_malloc(
              memhandler, sizeof(sns_ddf_range_s), state->sub_dev[sub_dev_idx].smgr_handle);
          if(NULL == ranges)
            return SNS_DDF_ENOMEM;
          ranges->min = FX_CONV_Q16((uint32_t)-40,0);
          ranges->max = FX_CONV_Q16((int32_t)85,0);
          *num_elems = 1;
        }
        else
        {
          return SNS_DDF_EINVALID_PARAM;
        }
        *value = ranges;
        return SNS_DDF_SUCCESS;
      }

    case SNS_DDF_ATTRIB_RESOLUTION:
      {
        sns_ddf_resolution_t *res = sns_dd_lsm6dsm_memhandler_malloc(
            memhandler, sizeof(sns_ddf_resolution_t), state->sub_dev[sub_dev_idx].smgr_handle);
        if(NULL == res)
          return SNS_DDF_ENOMEM;

        if(sensor == SNS_DDF_SENSOR_ACCEL)
          *res = FX_FLTTOFIX_Q16(state->acc_sstvt_adj * G / 1000000);
        else if(sensor == SNS_DDF_SENSOR_GYRO)
          *res = FX_DIV_Q16(state->gyr_sstvt_adj,FX_CONV_Q16((int32_t)1000,0));
        else if(sensor == SNS_DDF_SENSOR_TEMP)
          *res = FX_DIV_Q16(FX_CONV_Q16((int32_t)1,0), FX_CONV_Q16((int32_t)256,0));
        else
          return SNS_DDF_EINVALID_PARAM;

        *value = res;
        *num_elems = 1;

        return SNS_DDF_SUCCESS;
      }

    case SNS_DDF_ATTRIB_RESOLUTION_ADC:
      {
        sns_ddf_resolution_adc_s *res = sns_dd_lsm6dsm_memhandler_malloc(
            memhandler ,sizeof(sns_ddf_resolution_adc_s), state->sub_dev[sub_dev_idx].smgr_handle);
        if(NULL == res)
          return SNS_DDF_ENOMEM;

        if((sensor == SNS_DDF_SENSOR_ACCEL) ||
            (sensor == SNS_DDF_SENSOR_GYRO))
        {
          res->bit_len = 16;
          res->max_freq = state->odr_list[state->max_supported_odr_idx];
        }
        else if(sensor == SNS_DDF_SENSOR_TEMP)
        {
          res->bit_len = 16;
          res->max_freq = 1;
        }
        else
          return SNS_DDF_EINVALID_PARAM;
        *value = res;
        *num_elems = 1;

        return SNS_DDF_SUCCESS;
      }

    case SNS_DDF_ATTRIB_LOWPASS:
      {
        if((sensor == SNS_DDF_SENSOR_ACCEL) ||
        (sensor == SNS_DDF_SENSOR_GYRO))
        {
          *value = lsm6dsm_freqs;
          *num_elems = ARR_SIZE(lsm6dsm_freqs);
        }
         else
            return SNS_DDF_EINVALID_ATTR;


        return SNS_DDF_SUCCESS;
      }
    case SNS_DDF_ATTRIB_SUPPORTED_ODR_LIST:
      {
        if((sensor == SNS_DDF_SENSOR_ACCEL) ||
            (sensor == SNS_DDF_SENSOR_GYRO)) {

          *value = state->odr_list+state->min_supported_odr_idx;
          *num_elems = state->max_supported_odr_idx + 1 - state->min_supported_odr_idx;
        } else
          return SNS_DDF_EINVALID_ATTR;

        return SNS_DDF_SUCCESS;
      }

    case SNS_DDF_ATTRIB_ODR:
      {
        //int8_t lsm6dsm_rate_index = -1;
        sns_ddf_odr_t *res = sns_dd_lsm6dsm_memhandler_malloc(
            memhandler ,sizeof(sns_ddf_odr_t), state->sub_dev[sub_dev_idx].smgr_handle);
        if(NULL == res)
          return SNS_DDF_ENOMEM;

        if(sensor == SNS_DDF_SENSOR_ACCEL) {
          if(state->acc_desired_rate_idx >= 0) {
            *res = state->odr_list[state->acc_cur_rate_idx];
          } else
            *res = 0;
        } else if(sensor == SNS_DDF_SENSOR_GYRO) {
          if(state->gyr_desired_rate_idx >= 0) {
            *res = state->odr_list[state->gyr_cur_rate_idx];
          } else
            *res = 0;
        }
        else if(sensor == SNS_DDF_SENSOR_TEMP)
        {
          if(ddf_sensor_type == SNS_DDF_SENSOR_ACCEL)
            *res = (state->a_temp_rate) ? 1 : 0;
          else if(ddf_sensor_type == SNS_DDF_SENSOR_GYRO)
            *res = (state->g_temp_rate) ? 1 : 0;
        }
        else
          return SNS_DDF_EINVALID_PARAM;

        if( state->s4s_config.synced != STM_LSM6DSM_S4S_NOT_SYNCED ) {
          // Assume SMGR is using LSM6DSM_ASSUMED_SMGR_NOMINAL_S4S_TICKS ticks/s for S4S
          *res = *res * 32768 / LSM6DSM_ASSUMED_SMGR_NOMINAL_S4S_TICKS;
        }

        LSM6DSM_MSG_2(LOW, "Get_ATTRIB_ODR sensor(%d) odr (%d)",sensor, *res);

        *value = res;
        *num_elems = 1;

        return SNS_DDF_SUCCESS;
      }
    case SNS_DDF_ATTRIB_DELAYS:
      {
        sns_ddf_delays_s *lsm6dsm_delays = sns_dd_lsm6dsm_memhandler_malloc(
            memhandler, sizeof(sns_ddf_delays_s), state->sub_dev[sub_dev_idx].smgr_handle);
        if(NULL == lsm6dsm_delays)
          return SNS_DDF_ENOMEM;

        if(sensor == SNS_DDF_SENSOR_ACCEL)
        {
          lsm6dsm_delays->time_to_active = 1;
          lsm6dsm_delays->time_to_data = 1;
        }
        else
        {
          lsm6dsm_delays->time_to_active = 1;
          lsm6dsm_delays->time_to_data = 1;
        }
        *value = lsm6dsm_delays;
        *num_elems = 1;

        return SNS_DDF_SUCCESS;
      }
   case SNS_DDF_ATTRIB_BIAS:
      {
        if(sensor == SNS_DDF_SENSOR_ACCEL)
        {
          // for accel
          *value = state->xl_biases;
          *num_elems = ARR_SIZE(state->xl_biases);

          return SNS_DDF_SUCCESS;
        }
        else if(sensor == SNS_DDF_SENSOR_GYRO)
        {
          // for accel
          *value = state->g_biases;
          *num_elems = ARR_SIZE(state->g_biases);

          return SNS_DDF_SUCCESS;
        }
        else
        {
          LSM6DSM_MSG_E_1(ERROR, " Invalid sensor (%d) for getting bias ", sensor);
          return SNS_DDF_EINVALID_ATTR;
        }
      }
     case SNS_DDF_ATTRIB_FIFO:
      {
        sns_ddf_status_e status = SNS_DDF_SUCCESS;
        sns_ddf_fifo_share_sensor_s shared_sensors_fifo[STM_LSM6DSM_MAX_SHARED_FIFO_SENSORS];
        uint8_t size = STM_LSM6DSM_MAX_SHARED_FIFO_SENSORS;
        sns_ddf_fifo_share_sensor_s* dd_shared_sensors = NULL;
        uint8_t i = 0;
        sns_ddf_fifo_attrib_get_s *res = sns_dd_lsm6dsm_memhandler_malloc(
            memhandler ,sizeof(sns_ddf_fifo_attrib_get_s), state->sub_dev[sub_dev_idx].smgr_handle);
        if(NULL == res)
          return SNS_DDF_ENOMEM;

        if((sensor == SNS_DDF_SENSOR_ACCEL) ||
            (sensor == SNS_DDF_SENSOR_GYRO)) {
          res->is_supported = true;
          res->is_sw_watermark = false;
          res->max_watermark = STM_LSM6DSM_MAX_FIFO;
          status = sns_dd_lsm6dsm_sharedFifo_info(dd_handle, sensor, shared_sensors_fifo, &size);
          if(status == SNS_DDF_SUCCESS) {
            dd_shared_sensors = sns_dd_lsm6dsm_memhandler_malloc(
                memhandler , size * sizeof(sns_ddf_fifo_share_sensor_s), state->sub_dev[sub_dev_idx].smgr_handle);
            if(NULL == dd_shared_sensors)
              return SNS_DDF_ENOMEM;
            for(i = 0; i < size; i++) {
              dd_shared_sensors[i].sensor = shared_sensors_fifo[i].sensor;
              dd_shared_sensors[i].dd_handle = shared_sensors_fifo[i].dd_handle;
            }
            res->share_sensors[0] = dd_shared_sensors;
          }

        } else if(sensor == SNS_DDF_SENSOR_TEMP) {
          res->is_supported = true;
          res->is_sw_watermark = false;
          res->max_watermark = STM_LSM6DSM_MAX_TEMP_FIFO_DEPTH;
          res->share_sensor_cnt = 0;
          res->share_sensors[0] = NULL;
        } else {
          LSM6DSM_MSG_E_1(ERROR, " Invalid sensor (%d) ", sensor);
          return SNS_DDF_EINVALID_ATTR;
        }

        *value = res;
        *num_elems = 1;

        return status;
      }
    case SNS_DDF_ATTRIB_ODR_TOLERANCE:
      {
        q16_t *res = sns_dd_lsm6dsm_memhandler_malloc(
            memhandler ,sizeof(q16_t), state->sub_dev[sub_dev_idx].smgr_handle);
        if(NULL == res)
          return SNS_DDF_ENOMEM;
        if(sensor == SNS_DDF_SENSOR_ACCEL)
        {
          *res = FX_FLTTOFIX_Q16(0.05);
        }
        else if(sensor == SNS_DDF_SENSOR_GYRO)
        {
          *res = FX_FLTTOFIX_Q16(0.05);
        }
        else
        {
          LSM6DSM_MSG_E_1(ERROR, " Invalid sensor (%d) ", sensor);
          return SNS_DDF_EINVALID_ATTR;
        }
        *value = res;
        *num_elems = 1;

        return SNS_DDF_SUCCESS;
      }
    case SNS_DDF_ATTRIB_S4S_CONFIG:
      {
        sns_ddf_s4s_config_s *s4s_config =
          sns_dd_lsm6dsm_memhandler_malloc(memhandler,
                                           sizeof(sns_ddf_s4s_config_s),
                                           state->sub_dev[sub_dev_idx].smgr_handle);
        if(NULL == s4s_config)
          return SNS_DDF_ENOMEM;
        s4s_config->t_ph = state->s4s_config.modified_t_ph;
        s4s_config->rr = state->s4s_config.rr;
        s4s_config->ideal_sync_interval = state->s4s_config.ideal_sync_interval;
        s4s_config->fifo_int_en = state->s4s_config.fifo_int_en;

        if( ddf_sensor_type != state->s4s_config.stdt_sensor )
        {
          // TODO: if the non-STDT sensor isn't sycned with the STDT sensor yet, reply
          // with a short ideal_sync_interval
        }
        if( (ddf_sensor_type == SNS_DDF_SENSOR_ACCEL &&
             !(state->s4s_config.sensor_sbsp & STM_LSM6DSM_BM_ACCEL)) ||
            (ddf_sensor_type == SNS_DDF_SENSOR_GYRO &&
             !(state->s4s_config.sensor_sbsp & STM_LSM6DSM_BM_GYRO)) )
        {
          // Asking for S4S config, but this sensor isn't configured
          s4s_config->t_ph = 0;
          s4s_config->rr = 0;
          s4s_config->ideal_sync_interval = 0;
          s4s_config->fifo_int_en = false;
        } else if( MAX(state->acc_cur_rate_idx, state->gyr_cur_rate_idx) > STM_LSM6DSM_ODR208 ) {
          s4s_config->t_ph = 0;
          s4s_config->rr = 0;
          s4s_config->ideal_sync_interval = 0;
          s4s_config->fifo_int_en = true;
        }
        LSM6DSM_MSG_3(HIGH, "GET_S4S_CONFIG: t_ph %d rr %d sync_interval %u",
            s4s_config->t_ph, s4s_config->rr,
            s4s_config->ideal_sync_interval );
        *value = s4s_config;
        *num_elems = 1;
        return SNS_DDF_SUCCESS;
      }

    case SNS_DDF_ATTRIB_S4S_MAX_CLOCK_DRIFT:
      {
        /* What is the actual clock drift on the part after things have
         * been synced? Assume 0.1 % */
        sns_ddf_time_t *drift = (sns_ddf_time_t*)value;
        *drift = state->s4s_config.ideal_sync_interval / 1000;
        *num_elems = 1;

        return SNS_DDF_SUCCESS;
      }
      case SNS_DDF_ATTRIB_IO_REGISTER:
      {
        sns_ddf_io_register_s* io_reg_in = (sns_ddf_io_register_s *) (*value);
        uint8_t bytes_read;
        sns_ddf_status_e status;

        if ((uint32_t)(io_reg_in->address_ptr) > 0xFFFF)
        {
          LSM6DSM_MSG_E_1(ERROR, " Invalid address_ptr (0x%x)", io_reg_in->address_ptr);
          return SNS_DDF_EINVALID_PARAM;
        }
        if (io_reg_in->length > 0xFF)
        {
          LSM6DSM_MSG_E_1(ERROR, " Invalid length (%d)", io_reg_in->length);
          return SNS_DDF_EINVALID_PARAM;
        }

        // Allocate memory for the output data structure and for the data to be read from the register(s)
        sns_ddf_io_register_s* io_reg_out = sns_dd_lsm6dsm_memhandler_malloc(
            memhandler, sizeof(sns_ddf_io_register_s) + (sizeof(uint8_t) * (io_reg_in->length - 1)),
          state->sub_dev[sub_dev_idx].smgr_handle);
        if (io_reg_out == NULL) {
          LSM6DSM_MSG_E_1(ERROR, " Malloc failed ", 0);
          return SNS_DDF_ENOMEM;
        }

        status = sns_ddf_read_port(
            state->port_handle,
            (uint16_t) ((uint32_t)io_reg_in->address_ptr),
            &(io_reg_out->data[0]),
            (uint8_t) io_reg_in->length,
            &bytes_read);
      if(status != SNS_DDF_SUCCESS) {
          LSM6DSM_MSG_E_1(ERROR, "read_port failed status (%d) ", status);
          return status;
        }
        if(bytes_read != (uint8_t) io_reg_in->length) {
          LSM6DSM_MSG_E_2(ERROR, "read_port failed bytes_read (%d) doesn't match \
              length (%d) ", bytes_read, (uint8_t) io_reg_in->length);
          return SNS_DDF_EBUS;
        }

        // Fill out the information in the output io_register data structure
        io_reg_out->address_ptr = io_reg_in->address_ptr;
        io_reg_out->addr_fixed = io_reg_in->addr_fixed;
        io_reg_out->data_width = io_reg_in->data_width;
        io_reg_out->length = (uint32_t) bytes_read;
        // Return the io_register data structure by reference
        *value = io_reg_out;
        *num_elems = 1;

        return SNS_DDF_SUCCESS;
      }
    case SNS_DDF_ATTRIB_DRIVER_INFO:
      {
        sns_ddf_driver_info_s *info = sns_dd_lsm6dsm_memhandler_malloc(
            memhandler, sizeof(sns_ddf_driver_info_s), state->sub_dev[sub_dev_idx].smgr_handle);
        if(NULL == info)
          return SNS_DDF_ENOMEM;

        info->name = "STMicroelectronics LSM6DSM Driver";
        info->version = 50150; //05.015.0
        *value = info;
        *num_elems = 1;

        return SNS_DDF_SUCCESS;
      }

    case SNS_DDF_ATTRIB_DEVICE_INFO:
      {
        sns_ddf_device_info_s *info = sns_dd_lsm6dsm_memhandler_malloc(
            memhandler, sizeof(sns_ddf_device_info_s), state->sub_dev[sub_dev_idx].smgr_handle);
        if(NULL == info)
          return SNS_DDF_ENOMEM;

        if(ddf_sensor_type == SNS_DDF_SENSOR_ACCEL)
          info->name = "Accelerometer";
        else if(ddf_sensor_type == SNS_DDF_SENSOR_GYRO)
          info->name = "Gyroscope";
        else if(ddf_sensor_type == SNS_DDF_SENSOR_TEMP)
          info->name = "Thermometer";
        else
          return SNS_DDF_EINVALID_PARAM;

        info->vendor = "STMicroelectronics";
        info->model = "LSM6DSM";
        info->version = 1;
        *value = info;
        *num_elems = 1;

        return SNS_DDF_SUCCESS;
      }
    default:
      return SNS_DDF_EINVALID_ATTR;
  }
}


/**
 * @brief Performs a set accelerometer power state operation
 *
 * @param[in]  dd_handle      Handle to a driver instance.
 * @param[in]  power_state    Power state to be set.
 *
 * @return SNS_DDF_SUCCESS if this operation was done successfully. Otherwise
 *         SNS_DDF_EDEVICE, SNS_DDF_EBUS, SNS_DDF_EINVALID_PARAM, or SNS_DDF_EFAIL to
 *         indicate and error has occurred.
 */
sns_ddf_status_e sns_dd_acc_lsm6dsm_set_power(
    sns_ddf_handle_t dd_handle,
    sns_ddf_powerstate_e power_state)
{
  sns_dd_lsm6dsm_state_t* state = sns_dd_lsm6dsm_get_state(dd_handle);;
  sns_ddf_status_e status = SNS_DDF_SUCCESS;
  uint32_t sub_dev_idx;

  lsm6dsm_search_subdev_by_sensortype(state, SNS_DDF_SENSOR_ACCEL, &sub_dev_idx);

  if(SNS_DDF_POWERSTATE_LOWPOWER == power_state)
  {
    LSM6DSM_MSG_0(LOW, "SET_ACC_POWER - power_state to LOWPOWER");
    // This can call at any stage, make sure to handle well
    if(state->md_enabled) {
      sns_dd_lsm6dsm_disable_md(dd_handle);
      state->md_desired = true;
    }
    state->a_temp_rate = 0;
    if(state->fifo_info.fifo_enabled & TEMP_A_FIFO_BM)
      sns_dd_lsm6dsm_temp_set_rate(dd_handle, 0);
    if(state->acc_desired_rate_idx >= 0)
      sns_dd_acc_lsm6dsm_attrib_set_datarate(dd_handle, sub_dev_idx, 0);
    if(state->fifo_info.fifo_int_enabled & ACCEL_FIFO_BM)
      sns_dd_lsm6dsm_disable_fifo_int(dd_handle, SNS_DDF_SENSOR_ACCEL);
    if(state->fifo_info.fifo_enabled & ACCEL_FIFO_BM)
      sns_dd_lsm6dsm_disable_fifo(dd_handle, SNS_DDF_SENSOR_ACCEL);

    state->acc_desired_rate_idx = -1;
    //if gyro is enabled do not set fifo acc params
    //will be set when gyro disables
    if(!(state->fifo_info.fifo_enabled & GYRO_FIFO_BM)) {
      state->fifo_info.acc_sample_cnt = 0;
      state->data_intp.acc_intp_status = false;
      state->fifo_info.acc_fifo_alive = false;
      state->data_intp.acc_last_sample_status = false;
    }
    state->sub_dev[sub_dev_idx].powerstate = SNS_DDF_POWERSTATE_LOWPOWER;
    //check gyro power status
    status = lsm6dsm_search_subdev_by_sensortype(state, SNS_DDF_SENSOR_GYRO, &sub_dev_idx);
    if(status == SNS_DDF_SUCCESS) {
      if((state->sub_dev[sub_dev_idx].powerstate == SNS_DDF_POWERSTATE_LOWPOWER) &&
          (state->gyr_sleep))
        sns_dd_gyr_lsm6dsm_set_datarate(dd_handle, -1, false);
    }
  }
  else if(SNS_DDF_POWERSTATE_ACTIVE == power_state)
  {
    LSM6DSM_MSG_0(LOW, "SET_ACC_POWER - power_state to ACTIVE");
    sns_dd_lsm6dsm_reset(dd_handle);
    state->acc_desired_rate_idx = -1;
    state->sub_dev[sub_dev_idx].powerstate = SNS_DDF_POWERSTATE_ACTIVE;
    //make sure gyro is not turned on
    //put gyro in sleep mode, useful incase of S4S
    if((state->gyr_sleep == false) &&
      (state->gyr_cur_rate_idx < 0))
      sns_dd_gyr_lsm6dsm_set_datarate(dd_handle, -1, true);

  }
  return SNS_DDF_SUCCESS;
}

/**
 * @brief Performs a set gyrocope power state operation
 *
 * @param[in]  dd_handle      Handle to a driver instance.
 * @param[in]  power_state    Power state to be set.
 *
 * @return SNS_DDF_SUCCESS if this operation was done successfully. Otherwise
 *         SNS_DDF_EDEVICE, SNS_DDF_EBUS, SNS_DDF_EINVALID_PARAM, or SNS_DDF_EFAIL to
 *         indicate and error has occurred.
 */
sns_ddf_status_e sns_dd_gyr_lsm6dsm_set_power(
    sns_ddf_handle_t dd_handle,
    sns_ddf_powerstate_e power_state)
{
  sns_dd_lsm6dsm_state_t* state = sns_dd_lsm6dsm_get_state(dd_handle);
  uint32_t sub_dev_idx;
  sns_ddf_status_e status = SNS_DDF_SUCCESS;

  lsm6dsm_search_subdev_by_sensortype(state, SNS_DDF_SENSOR_GYRO, &sub_dev_idx);

  if(SNS_DDF_POWERSTATE_LOWPOWER == power_state)
  {
    LSM6DSM_MSG_0(LOW, "SET_GYR_POWER - power_state to LOWPOWER");
    //gyro sleep mode to Power down -- acc streaming no effect

    state->g_temp_rate = 0;
    if(state->fifo_info.fifo_enabled & TEMP_G_FIFO_BM)
      sns_dd_lsm6dsm_temp_set_rate(dd_handle, 0);
    if(state->gyr_desired_rate_idx >= 0)
      sns_dd_gyr_lsm6dsm_attrib_set_datarate(dd_handle, sub_dev_idx, 0);
    if(state->fifo_info.fifo_int_enabled & GYRO_FIFO_BM)
      sns_dd_lsm6dsm_disable_fifo_int(dd_handle, SNS_DDF_SENSOR_GYRO);
    if(state->fifo_info.fifo_enabled & GYRO_FIFO_BM)
      sns_dd_lsm6dsm_disable_fifo(dd_handle, SNS_DDF_SENSOR_GYRO);

    state->gyr_odr_settled_ts = 0;
    state->gyr_desired_rate_idx = -1;
    state->sub_dev[sub_dev_idx].powerstate = SNS_DDF_POWERSTATE_LOWPOWER;
    //check if acc is powered on, if powered on keep the device in sleep mode
    //accel will power down
    status = lsm6dsm_search_subdev_by_sensortype(state, SNS_DDF_SENSOR_ACCEL, &sub_dev_idx);
    if(status == SNS_DDF_SUCCESS) {
      if((state->sub_dev[sub_dev_idx].powerstate == SNS_DDF_POWERSTATE_LOWPOWER) &&
          (state->gyr_sleep))
        sns_dd_gyr_lsm6dsm_set_datarate(dd_handle, -1, false);
    }
  }
  else if(SNS_DDF_POWERSTATE_ACTIVE == power_state)
  {
    LSM6DSM_MSG_0(LOW, "SET_GYR_POWER - power_state to ACTIVE");
    sns_dd_lsm6dsm_reset(dd_handle);
    state->gyr_desired_rate_idx = -1;
    state->sub_dev[sub_dev_idx].powerstate = SNS_DDF_POWERSTATE_ACTIVE;

    //keeping device in sleep mode
    if(state->gyr_sleep == false)
      sns_dd_gyr_lsm6dsm_set_datarate(dd_handle, -1, true);
  }

  return SNS_DDF_SUCCESS;
}

/**
 * @brief Performs a set dynamic range operation for accelerometer
 *
 * @param[in]  dd_handle      Handle to a driver instance.
 * @param[in]  range          Dynamic range settings for LSM6DSM
 *
 * @return SNS_DDF_SUCCESS if this operation was done successfully. Otherwise
 *         SNS_DDF_EDEVICE, SNS_DDF_EBUS, SNS_DDF_EINVALID_PARAM, or SNS_DDF_EFAIL to
 *         indicate and error has occurred.
 */
sns_ddf_status_e sns_dd_acc_lsm6dsm_set_range(
    sns_ddf_handle_t dd_handle,
    int8_t range_idx)
{
  sns_dd_lsm6dsm_state_t* state = sns_dd_lsm6dsm_get_state(dd_handle);
  sns_ddf_status_e status;
  uint8_t write_buffer = 0;
  uint8_t read_count = 0;
  stm_lsm6dsm_acc_sstvt sstvt;

  if((range_idx < 0) ||
    (range_idx > (ARR_SIZE(lsm6dsm_acc_ranges)-1))) {
    LSM6DSM_MSG_E_1(ERROR, "SET_GYR_RANGE - invalid range_idx - (%d)",range_idx);
    return SNS_DDF_EINVALID_PARAM;
  }
  if(state->acc_range_idx >= 0) {
    status = sns_ddf_read_port(
        state->port_handle,
        STM_LSM6DSM_REG_CTRL1_A,
        &write_buffer,
        1,
        &read_count);
    if(status != SNS_DDF_SUCCESS) {
      LSM6DSM_MSG_E_1(ERROR, "read_port failed- status (%d)",status);
      return status;
    }
    if(read_count != 1) {
      LSM6DSM_MSG_E_1(ERROR, "read_port failed-  read_count  does not match - read_count (%d)",read_count);
      return SNS_DDF_EBUS;
    }
    LSM6DSM_MSG_2(LOW, "SET_ACC_RANGE - set range_idx - (%d) ctrl1_a 0x%x",range_idx, write_buffer);
    if(lsm6dsm_acc_ranges[range_idx]  == (write_buffer & STM_LSM6DSM_FS_XL_MASK))
      return SNS_DDF_SUCCESS;
  }
  LSM6DSM_MSG_2(LOW, "SET_ACC_RANGE - set range_idx - (%d) reg_value (%x)",range_idx, lsm6dsm_acc_ranges[range_idx]);
  //set sensor sensitivity for data conversion
  switch (lsm6dsm_acc_ranges[range_idx]) {
    case STM_LSM6DSM_ACC_RANGE_2G:
      sstvt = STM_LSM6DSM_ACC_SSTVT_2G;
      break;
    case STM_LSM6DSM_ACC_RANGE_4G:
      sstvt = STM_LSM6DSM_ACC_SSTVT_4G;
      break;
    case STM_LSM6DSM_ACC_RANGE_8G:
      sstvt = STM_LSM6DSM_ACC_SSTVT_8G;
      break;
    case STM_LSM6DSM_ACC_RANGE_16G:
      sstvt = STM_LSM6DSM_ACC_SSTVT_16G;
      break;
    default:
      return SNS_DDF_EINVALID_PARAM;
  }

  // Configure CTRL_FS register
  write_buffer = ((uint8_t)lsm6dsm_acc_ranges[range_idx]);
  status = sns_dd_lsm6dsm_write_reg(
      dd_handle,
      STM_LSM6DSM_REG_CTRL1_A,
      &write_buffer,
      1,
      STM_LSM6DSM_FS_XL_MASK);
  if(status != SNS_DDF_SUCCESS)
    return status;

  state->acc_range_idx = range_idx;
  state->acc_sstvt_adj = sstvt;

  return SNS_DDF_SUCCESS;
}

/**
 * @brief Performs a set dynamic range operation for gyroscope.
 *
 * @param[in]  dd_handle      Handle to a driver instance.
 * @param[in]  range          Dynamic range settings for LSM6DSM
 *
 * @return SNS_DDF_SUCCESS if this operation was done successfully. Otherwise
 *         SNS_DDF_EDEVICE, SNS_DDF_EBUS, SNS_DDF_EINVALID_PARAM, or SNS_DDF_EFAIL to
 *         indicate and error has occurred.
 */
sns_ddf_status_e sns_dd_gyr_lsm6dsm_set_range(
    sns_ddf_handle_t dd_handle,
    int8_t range_idx)
{
  sns_dd_lsm6dsm_state_t* state = sns_dd_lsm6dsm_get_state(dd_handle);
  sns_ddf_status_e status;
  uint8_t write_buffer = 0;
  q16_t sstvt;

  if((range_idx < 0) ||
    (range_idx > (ARR_SIZE(lsm6dsm_gyr_ranges)-1))) {
    LSM6DSM_MSG_E_1(ERROR, "SET_GYR_RANGE - invalid range_idx - (%d)",range_idx);
    return SNS_DDF_EINVALID_PARAM;
  }

  LSM6DSM_MSG_2(LOW, "SET_GYR_RANGE - set range_idx - (%d) reg_value (%x)",range_idx, lsm6dsm_gyr_ranges[range_idx]);
  //set sensor sensitivity for data conversion
  switch (lsm6dsm_gyr_ranges[range_idx]) {
    case STM_LSM6DSM_GYR_RANGE_125DPS:
      sstvt = STM_LSM6DSM_GYR_SSTVT_125DPS;
      break;
    case STM_LSM6DSM_GYR_RANGE_245DPS:
      sstvt = STM_LSM6DSM_GYR_SSTVT_245DPS;
      break;
    case STM_LSM6DSM_GYR_RANGE_500DPS:
      sstvt = STM_LSM6DSM_GYR_SSTVT_500DPS;
      break;
    case STM_LSM6DSM_GYR_RANGE_1000DPS:
      sstvt = STM_LSM6DSM_GYR_SSTVT_1000DPS;
      break;
    case STM_LSM6DSM_GYR_RANGE_2000DPS:
      sstvt = STM_LSM6DSM_GYR_SSTVT_2000DPS;
      break;
    default:
      return SNS_DDF_EINVALID_PARAM;
  }

  // Configure CTRL_FS register
  write_buffer = ((uint8_t)lsm6dsm_gyr_ranges[range_idx]);
  status = sns_dd_lsm6dsm_write_reg(
      dd_handle,
      STM_LSM6DSM_REG_CTRL2_G,
      &write_buffer,
      1,
      STM_LSM6DSM_FS_G_MASK);
  if(status != SNS_DDF_SUCCESS)
    return status;

  state->gyr_range_idx = range_idx;
  state->gyr_sstvt_adj = sstvt;


  return SNS_DDF_SUCCESS;
}

static uint32_t calc_best_s4s_fit( sns_ddf_handle_t handle,
                                   sns_ddf_sensor_e sensor,
                                   const sns_ddf_s4s_config_s *s4s_config )
{
  float resultant_tph_ms;
  sns_ddf_odr_t desired_odr, actual_odr = 200;
  sns_dd_lsm6dsm_state_t *state;
  sns_ddf_status_e status;
  uint8_t w_buffer[2];
  sns_ddf_rw_port_s s4s_cfg_txn[2];
  uint8_t orig_t_ph_reg_value;
  uint8_t orig_rr;
  int8_t  idx;


  state = (sns_dd_lsm6dsm_state_t*)((dd_handle_align_t)handle & DD_HANDLE_ALIGN_BITS);
  orig_t_ph_reg_value = state->s4s_config.t_ph_reg_value;
  orig_rr = state->s4s_config.rr;

  desired_odr = s4s_config->t_ph * 32768 / s4s_config->ideal_sync_interval;

  sns_dd_lsm6dsm_match_odr( handle, desired_odr, &actual_odr, &idx );

  // Assume SMGR is using LSM6DSM_ASSUMED_SMGR_S4S_TICKS_PER_SEC ticks/sec
  resultant_tph_ms = ((float)s4s_config->ideal_sync_interval * 1000.0 / (float)LSM6DSM_ASSUMED_SMGR_S4S_TICKS_PER_SEC);

  // LSM6DSM programs tph in 500ms increments:
  state->s4s_config.t_ph_reg_value = resultant_tph_ms / 500;
  state->s4s_config.modified_t_ph = actual_odr * s4s_config->ideal_sync_interval / LSM6DSM_ASSUMED_SMGR_S4S_TICKS_PER_SEC;

  LSM6DSM_MSG_E_1(HIGH, "modifying t_ph to %d", state->s4s_config.modified_t_ph);

  // Program calculated best-fit TPH
  if( state->s4s_config.stdt_sensor == SNS_DDF_SENSOR__NONE )
  {
    w_buffer[0] = state->s4s_config.t_ph_reg_value;
    w_buffer[1] = state->s4s_config.rr;

    s4s_cfg_txn[0].is_write = true;
    s4s_cfg_txn[0].reg_addr = STM_LSM6DSM_REG_T_PH;
    s4s_cfg_txn[0].buffer   = &(w_buffer[0]);
    s4s_cfg_txn[0].bytes    = 1;

    s4s_cfg_txn[1].is_write = true;
    s4s_cfg_txn[1].reg_addr = STM_LSM6DSM_REG_RR;
    s4s_cfg_txn[1].buffer   = &(w_buffer[1]);
    s4s_cfg_txn[1].bytes    = 1;

    status = sns_ddf_rw_port_v( state->port_handle,
                                s4s_cfg_txn, 2,
                                NULL, NULL );
    if(status != SNS_DDF_SUCCESS) {
      LSM6DSM_MSG_E_2(ERROR, "write_reg failed addr 0x%x- status (%d)",
                      STM_LSM6DSM_REG_T_PH, status);
    } else {
      LSM6DSM_MSG_E_2(HIGH,"wrote tph %u rr %u",
                      w_buffer[0], w_buffer[1]);
    }
    state->s4s_config.config_changed = false;
  }
  else
  {
    if( orig_t_ph_reg_value != state->s4s_config.t_ph_reg_value ||
        orig_rr != state->s4s_config.rr ) {
      LSM6DSM_MSG_4(HIGH,"scheduling TPH change %d-->%d rr %d-->%d",
                    orig_t_ph_reg_value, state->s4s_config.t_ph_reg_value,
                    orig_rr, state->s4s_config.rr);
      state->s4s_config.config_changed = true;
    }
  }

  return actual_odr;
}

/**
 * @brief Sets a lsm6dsm sensor attribute to a specific value.
 *
 * Refer to sns_ddf_driver_if.h for definition.
 */
sns_ddf_status_e sns_dd_lsm6dsm_set_attr(
    sns_ddf_handle_t dd_handle,
    sns_ddf_sensor_e sensor,
    sns_ddf_attribute_e attrib,
    void* value)
{
  uint32_t sub_dev_idx;
  sns_ddf_status_e  status = SNS_DDF_SUCCESS;
  sns_ddf_sensor_e ddf_sensor_type;

  if (dd_handle == NULL || value == NULL) {
    LSM6DSM_MSG_E_0(ERROR, "dd_handle is NULL");
    return SNS_DDF_EINVALID_PARAM;
  }

  sns_dd_lsm6dsm_state_t* state = sns_dd_lsm6dsm_get_state(dd_handle);
  sub_dev_idx = (dd_handle_align_t)dd_handle & (~DD_HANDLE_ALIGN_BITS);
  ddf_sensor_type = state->sub_dev[sub_dev_idx].sensors[0]; // '0' --> Primary

  LSM6DSM_MSG_3(LOW, "SET_ATTRIB attrib (%d) sensor (%d) p_sensor (%d)",attrib, sensor, ddf_sensor_type);
  if(attrib != SNS_DDF_ATTRIB_IO_REGISTER) {
    if(LSM6DSM_IS_ESP_SENSOR(ddf_sensor_type)) {
      if(state->esp_info.esp_if)
        return state->esp_info.esp_if->set_attrib(dd_handle, sensor, attrib, value);
      else
        return SNS_DDF_EINVALID_PARAM;
    }
    if(LSM6DSM_IS_HUB_SLV_SENSOR(ddf_sensor_type)) {
      if(state->hub_info.hub_if)
        return state->hub_info.hub_if->set_attrib(dd_handle, sensor, attrib, value);
      else
        return SNS_DDF_EINVALID_PARAM;
    }
  }

  switch(attrib)
  {
    case SNS_DDF_ATTRIB_POWER_STATE:
      {
        sns_ddf_powerstate_e* power_state = value;

        if(ddf_sensor_type == SNS_DDF_SENSOR_ACCEL) {
          LSM6DSM_MSG_0(LOW, "SET_POWER - sensor type accel");
          switch(sensor) {
            case SNS_DDF_SENSOR__ALL:
              // TODO: need to include secondary (above) under this
              /* falling through... */
            case SNS_DDF_SENSOR_ACCEL: // primary
              status = sns_dd_acc_lsm6dsm_set_power(dd_handle, *power_state);
              break;
            default:
              status =  SNS_DDF_EINVALID_PARAM;
              break;
          }
        } else if(ddf_sensor_type == SNS_DDF_SENSOR_GYRO) {
          LSM6DSM_MSG_0(LOW, "SET_POWER - sensor type gyro");
          switch(sensor) {
            case SNS_DDF_SENSOR__ALL:
              // TODO: need to include secondary (above) under this
              /* falling through... */
            case SNS_DDF_SENSOR_GYRO: // primary
              status = sns_dd_gyr_lsm6dsm_set_power(dd_handle, *power_state);
              break;
            default:
              status = SNS_DDF_EINVALID_PARAM;
              break;
          }
        }  else {
          /* should never be here... */
          status = SNS_DDF_EINVALID_PARAM;
        }
        if(status == SNS_DDF_SUCCESS)
          state->sub_dev[sub_dev_idx].powerstate = *power_state;
        break;
      }
    case SNS_DDF_ATTRIB_RANGE:
      {
        uint32_t* range_idx = value;

         if(sensor == SNS_DDF_SENSOR_ACCEL)
         status = sns_dd_acc_lsm6dsm_set_range(dd_handle, *range_idx);
         else if(sensor == SNS_DDF_SENSOR_GYRO)
          status = sns_dd_gyr_lsm6dsm_set_range(dd_handle, *range_idx);
         else
          status = SNS_DDF_EINVALID_PARAM;
        break;
      }
    case SNS_DDF_ATTRIB_ODR:
      {
        sns_ddf_odr_t* rate = value;
        LSM6DSM_MSG_3(LOW, "set_odr attrib (%d) sensor (%d) value (%d) ",attrib, sensor, *rate);

        if(sensor == SNS_DDF_SENSOR_ACCEL)
          status = sns_dd_acc_lsm6dsm_attrib_set_datarate(dd_handle, sub_dev_idx, *rate);
        else if(sensor == SNS_DDF_SENSOR_GYRO)
          status =sns_dd_gyr_lsm6dsm_attrib_set_datarate(dd_handle, sub_dev_idx, *rate);
        else if(sensor == SNS_DDF_SENSOR_TEMP)
        {
            if(ddf_sensor_type == SNS_DDF_SENSOR_ACCEL)
              state->a_temp_rate = *rate;
            else if(ddf_sensor_type == SNS_DDF_SENSOR_GYRO)
              state->g_temp_rate = *rate;

            sns_dd_lsm6dsm_temp_set_rate(dd_handle, *rate);
        }
        else
          status = SNS_DDF_EINVALID_PARAM;

        break;
      }
    case SNS_DDF_ATTRIB_MOTION_DETECT:
      {
        if(sensor == SNS_DDF_SENSOR_ACCEL) {
          sns_ddf_motion_detect_enable_t* flag = value;
          if(*flag)
          {
            //enable motion detection
            LSM6DSM_MSG_0(HIGH, "+++ enable MD +++ ");
            state->md_desired = true;
            status = sns_dd_lsm6dsm_enable_md(dd_handle);
          }else{
            //disable motion detection
            LSM6DSM_MSG_0(HIGH, "--- disable MD --- ");
            status = sns_dd_lsm6dsm_disable_md(dd_handle);
            state->md_desired = false;
          }
        }else
          status = SNS_DDF_EINVALID_PARAM;
        break;
      }
    case SNS_DDF_ATTRIB_FIFO:
      {
        sns_ddf_fifo_set_s* fifo = value;

        if(0 == fifo->watermark) {
          status = sns_dd_lsm6dsm_disable_fifo(dd_handle, sensor);
        }else if(fifo->watermark <= STM_LSM6DSM_MAX_FIFO) {
          //atleast acc should be up and running
          //if (state->acc_desired_rate_idx < 0)
          //  return SNS_DDF_EFAIL;

          status = sns_dd_lsm6dsm_enable_fifo(dd_handle, fifo->watermark, sensor);
        } else {
          status = SNS_DDF_EINVALID_ATTR;
        }

        break;
      }

    case SNS_DDF_ATTRIB_IO_REGISTER:
      {
        sns_ddf_io_register_s* io_reg_in = (sns_ddf_io_register_s *) value;

        if ((uint32_t)(io_reg_in->address_ptr) > 0xFFFF) {
          status =  SNS_DDF_EINVALID_PARAM;
        } else if (io_reg_in->length > 0xFF) {
          status = SNS_DDF_EINVALID_PARAM;
        } else {

          //sns_ddf_status_e status;
          status = sns_dd_lsm6dsm_write_reg(
              dd_handle,
              (uint16_t) ((uint32_t)io_reg_in->address_ptr),
              (uint8_t*) io_reg_in->data,
              (uint8_t) io_reg_in->length,
              0x00);
        }
        break;
      }
    case SNS_DDF_ATTRIB_S4S_CONFIG:
      /* TODO: Handle for both accel/gyro
       * When both are enabled/streaming, both accel & gyro handles
       * will get S4S information. The ST/DT timing will eventually be the same for both,
       * but SMGR may ask for different ODRs, and the timiming may be different while
       * SMGR tries to initially sync the clock. It's up to the driver to only
       * provide the fastest ODR to SMGR and program the hardware appropriately.
      */
      if ((ddf_sensor_type == SNS_DDF_SENSOR_ACCEL) ||
          (ddf_sensor_type == SNS_DDF_SENSOR_GYRO))
      {
        uint8_t w_buffer[4];
        sns_ddf_s4s_config_s * s4s_config = value;
        sns_ddf_rw_port_s s4s_cfg_txn[4];
        int i;
        float sample_interval;
        bool  adjusted_tph = false;
        LSM6DSM_MSG_E_3(HIGH,"got S4S config. t_ph %d. rr %d. ideal_sync_interval %d.",
            s4s_config->t_ph, s4s_config->rr, s4s_config->ideal_sync_interval );

        if (s4s_config->t_ph == 0 ) {
          state->s4s_config.sensor_sbsp &= (ddf_sensor_type == SNS_DDF_SENSOR_ACCEL) ?
            ~STM_LSM6DSM_BM_ACCEL : ~STM_LSM6DSM_BM_GYRO;
        } else {
          state->s4s_config.sensor_sbsp |= (ddf_sensor_type == SNS_DDF_SENSOR_ACCEL) ?
            STM_LSM6DSM_BM_ACCEL : STM_LSM6DSM_BM_GYRO;
        }
        if(MAX(state->acc_cur_rate_idx, state->gyr_cur_rate_idx) > STM_LSM6DSM_ODR208) {
          //remove from sbsp list
          state->s4s_config.sensor_sbsp = SNS_DDF_SENSOR__NONE;

          if (s4s_config->t_ph == 0 ) {
            //disabling s4s do not update odr
            //wait till set_odr called
            return status;
          }

          //ignore s4s parameters if the max odrs are greater than 200Hz
          if((!state->fifo_info.fifo_int_enabled) && (state->fifo_info.fifo_enabled)) {
            sns_dd_lsm6dsm_stop_streaming(dd_handle, true);
            //setting wmk=1, fifo is already enabled here
            sns_dd_lsm6dsm_set_fifo_wmk(
                dd_handle,
                1);
            if(state->acc_desired_rate_idx > STM_LSM6DSM_ODR208)
              state->fifo_info.acc_wmk = 1;
            if(state->gyr_desired_rate_idx > STM_LSM6DSM_ODR208)
              state->fifo_info.gyr_wmk = 1;
            state->s4s_config.synced = STM_LSM6DSM_S4S_NOT_SYNCED;
            if((state->acc_desired_rate_idx > STM_LSM6DSM_ODR208) 
                && (state->fifo_info.fifo_enabled & ACCEL_FIFO_BM))
              sns_dd_lsm6dsm_enable_fifo_int(dd_handle, SNS_DDF_SENSOR_ACCEL);
            if((state->gyr_desired_rate_idx > STM_LSM6DSM_ODR208)
                && (state->fifo_info.fifo_enabled & GYRO_FIFO_BM))
              sns_dd_lsm6dsm_enable_fifo_int(dd_handle, SNS_DDF_SENSOR_GYRO);
            sns_dd_lsm6dsm_start_streaming(dd_handle);
          }
          return status;
        }


        if((state->s4s_config.stdt_sensor == SNS_DDF_SENSOR__NONE) ||
           (state->s4s_config.stdt_sensor == ddf_sensor_type)) {
          if(s4s_config->fifo_int_en == false )
          {
            LSM6DSM_MSG_E_0(HIGH,"Disbaling future FIFO interrupts" );
          }
          else
          {
            // TODO: check to see if enable_sched_data(true) has been called..
          }

          sample_interval = (float)(s4s_config->ideal_sync_interval) / (float)(s4s_config->t_ph);

          /* TODO: This assumes SMGR is using LSM6DSM_ASSUMED_SMGR_NOMINAL_S4S_TICKS ticks for a typical 1-second interval */
          while( s4s_config->t_ph != 0 && s4s_config->ideal_sync_interval + sample_interval <= LSM6DSM_ASSUMED_SMGR_S4S_TICKS_PER_SEC/2)
          {
            s4s_config->ideal_sync_interval += sample_interval;
            s4s_config->t_ph++;
            adjusted_tph = true;
          }

          if( adjusted_tph == true )
          {
            s4s_config->ideal_sync_interval = LSM6DSM_ASSUMED_SMGR_S4S_TICKS_PER_SEC/2;
            LSM6DSM_MSG_E_2(HIGH,"adjusted incoming S4S config. t_ph %d. ideal_sync_interval %d.",
                s4s_config->t_ph, s4s_config->ideal_sync_interval );
          }

          if( state->s4s_config.sensor_sbsp == 0 )
          {
            /* No sensors left using S4S. Disable S4S */
            w_buffer[0] = 0;
            w_buffer[1] = s4s_config->rr;
            w_buffer[2] = 0xCC; /* STMicro spec for ST */
            w_buffer[3] = 0x80; /* DT abort */

            s4s_cfg_txn[0].is_write = true;
            s4s_cfg_txn[0].reg_addr = STM_LSM6DSM_REG_T_PH;
            s4s_cfg_txn[0].buffer   = &(w_buffer[0]);
            s4s_cfg_txn[0].bytes    = 1;

            s4s_cfg_txn[1].is_write = true;
            s4s_cfg_txn[1].reg_addr = STM_LSM6DSM_REG_RR;
            s4s_cfg_txn[1].buffer   = &(w_buffer[1]);
            s4s_cfg_txn[1].bytes    = 1;

            s4s_cfg_txn[2].is_write = true;
            s4s_cfg_txn[2].reg_addr = STM_LSM6DSM_REG_ST;
            s4s_cfg_txn[2].buffer   = &(w_buffer[2]);
            s4s_cfg_txn[2].bytes    = 1;

            s4s_cfg_txn[3].is_write = true;
            s4s_cfg_txn[3].reg_addr = STM_LSM6DSM_REG_DT;
            s4s_cfg_txn[3].buffer   = &(w_buffer[3]);
            s4s_cfg_txn[3].bytes    = 1;


            status = sns_ddf_rw_port_v( state->port_handle,
                                        s4s_cfg_txn, 4,
                                        NULL, NULL );
            if(status != SNS_DDF_SUCCESS) {
              LSM6DSM_MSG_E_1(ERROR, "S4S write_reg failed status (%d)",
                              status);
            }
            else
            {
              LSM6DSM_MSG_E_2(HIGH, "S4S wrote tph %d rr %d, DT abort",
                              w_buffer[0], w_buffer[1]);
            }
          }

          if (s4s_config->t_ph == 0 ) {
            state->s4s_config.t_ph[(ddf_sensor_type == SNS_DDF_SENSOR_ACCEL)?0:1]
              = 0;

            if(state->s4s_config.sensor_sbsp == STM_LSM6DSM_BM__NONE) {
              state->s4s_config.stdt_sensor = SNS_DDF_SENSOR__NONE;
              state->s4s_config.synced = STM_LSM6DSM_S4S_NOT_SYNCED;
            } else if(state->s4s_config.sensor_sbsp == STM_LSM6DSM_BM_ACCEL) {
              /* if accel is still enabled, switch to using accel schedule */
              state->s4s_config.stdt_sensor = SNS_DDF_SENSOR_ACCEL;
              state->s4s_config.modified_t_ph = state->s4s_config.t_ph[0];
            } else {
              /* if gyro is still enabled, switch to using gyro schedule */
              state->s4s_config.stdt_sensor = SNS_DDF_SENSOR_GYRO;
              state->s4s_config.modified_t_ph = state->s4s_config.t_ph[1];
            }
            LSM6DSM_MSG_E_1(HIGH,"Setting stdt_sensor %d", state->s4s_config.stdt_sensor);
          } else {
            calc_best_s4s_fit( dd_handle, sensor, s4s_config );
            state->s4s_config.rr = s4s_config->rr;
            if( state->s4s_config.ideal_sync_interval != s4s_config->ideal_sync_interval &&
                state->s4s_config.ideal_sync_interval != 0 )
            {
              state->s4s_config.t_ph[0] =
                state->s4s_config.t_ph[0] * s4s_config->ideal_sync_interval /
                state->s4s_config.ideal_sync_interval;
              state->s4s_config.t_ph[1] =
                state->s4s_config.t_ph[1] * s4s_config->ideal_sync_interval /
                state->s4s_config.ideal_sync_interval;
            }
            state->s4s_config.ideal_sync_interval = s4s_config->ideal_sync_interval;
            state->s4s_config.fifo_int_en = s4s_config->fifo_int_en;
            state->s4s_config.ticks_per_rr = state->s4s_config.ideal_sync_interval;
            state->s4s_config.t_ph[(ddf_sensor_type == SNS_DDF_SENSOR_ACCEL)?0:1]
              = state->s4s_config.modified_t_ph;
            for( i = 0; i<state->s4s_config.rr+11; i++ )
            {
              state->s4s_config.ticks_per_rr /= 2;
            }

            LSM6DSM_MSG_E_2(HIGH,"SSC ticks per RR: %d.%06d",
                            (int)state->s4s_config.ticks_per_rr,
                            ((int)(state->s4s_config.ticks_per_rr * 1000000) % 1000000));
          }

          //ret_val = SNS_DDF_SUCCESS;
        } else {
          LSM6DSM_MSG_E_2(HIGH,"Set S4S config. Another sensor synced/syncing --ignoring stdt_sensor %d sensor_sbsp %d",
              state->s4s_config.stdt_sensor, state->s4s_config.sensor_sbsp );

          if( s4s_config->t_ph != 0 ) {
            s4s_config->t_ph = s4s_config->t_ph * state->s4s_config.ideal_sync_interval /
              s4s_config->ideal_sync_interval;

            s4s_config->ideal_sync_interval = state->s4s_config.ideal_sync_interval;
            calc_best_s4s_fit( dd_handle, sensor, s4s_config );
          } else {
            state->s4s_config.modified_t_ph = 0;
          }
          state->s4s_config.t_ph[(ddf_sensor_type == SNS_DDF_SENSOR_ACCEL)?0:1]
            = state->s4s_config.modified_t_ph;
          state->s4s_config.modified_t_ph =
            MAX( state->s4s_config.t_ph[0], state->s4s_config.t_ph[1] );

          LSM6DSM_MSG_E_3(HIGH,"set s4s config: t_ph now: %u,%u-->%u",
                          state->s4s_config.t_ph[0],
                          state->s4s_config.t_ph[1],
                          state->s4s_config.modified_t_ph );
        }
      }
      else
      {
        status = SNS_DDF_EINVALID_PARAM;
      }
      break;
    default:
      status = SNS_DDF_EINVALID_ATTR;
  }

  return status;
}

/**
 * @brief Implement enable_sched_data() DDF API.
 *
 * Refer to sns_ddf_driver_if.h for definition.
 */
sns_ddf_status_e sns_dd_lsm6dsm_sched_data(
    sns_ddf_handle_t  dd_handle,
    sns_ddf_sensor_e  sensor,
    bool              enable)
{
  sns_ddf_status_e status = SNS_DDF_SUCCESS;
  sns_dd_lsm6dsm_state_t* state = sns_dd_lsm6dsm_get_state(dd_handle);

  LSM6DSM_MSG_2(HIGH, "enable_sched_data: sensor=%u, enable=%u", sensor, enable);

  //each called function will handle concurrencies when to enable/disable FIFO int.

  if(LSM6DSM_IS_ESP_SENSOR(sensor)) {
      if(state->esp_info.esp_if)
        state->esp_info.esp_if->enable_sched_data(dd_handle, sensor, enable);
  } else {
    //each called function will handle concurrencies when to enable/disable FIFO int.
    if( state->s4s_config.fifo_int_en == false ) {
      LSM6DSM_MSG_0(HIGH, "enable_sched_data: forcing enable=false");
      enable = false;
    }

    if((sensor == SNS_DDF_SENSOR_GYRO) ||
        (sensor == SNS_DDF_SENSOR_ACCEL) ||
        (LSM6DSM_IS_HUB_SLV_SENSOR(sensor)) ||
        (sensor == SNS_DDF_SENSOR_TEMP)) {
      status = (enable) ?
        sns_dd_lsm6dsm_enable_fifo_int(dd_handle, sensor) :
        sns_dd_lsm6dsm_disable_fifo_int(dd_handle, sensor);
    }
  }
  return status;
}

/**
* @brief Probes for an LSM6DSM part.
*
* Refer to sns_ddf_driver_if.h for definition.
*/
sns_ddf_status_e sns_dd_lsm6dsm_probe(
    sns_ddf_device_access_s* device_info,
    sns_ddf_memhandler_s*    memhandler,
    uint32_t*                num_sensors,
    sns_ddf_sensor_e**       sensors )
{
  sns_ddf_status_e status;
  sns_ddf_handle_t port_handle;
  uint8_t i2c_buff;
  uint8_t bytes_read;
  *num_sensors = 0;
  *sensors = NULL;

  status = sns_ddf_open_port(&port_handle, &(device_info->port_config));
  if(status != SNS_DDF_SUCCESS)
  {
    return status;
  }

  // Check WhoAmIRegister to make sure this is the correct driver
  status = sns_ddf_read_port(
      port_handle,
      STM_LSM6DSM_REG_WHO_AM_I,
      &i2c_buff,
      1,
      &bytes_read);
  if(status != SNS_DDF_SUCCESS || bytes_read != 1)
  {
    sns_ddf_close_port( port_handle );
    return status;
  }
  if(i2c_buff != STM_LSM6DSM_WHOAMI_VALUE)
  {
    /* Incorrect value. Return now with nothing detected */
    sns_ddf_close_port( port_handle );
    return SNS_DDF_SUCCESS;
  }

  // WHO_AM_I register is correct. This is probably an LSM6DSM
  *num_sensors = 2;
  *sensors = sns_ddf_memhandler_malloc( memhandler,
                    sizeof(sns_ddf_sensor_e) * *num_sensors );
  if( *sensors != NULL )
  {
    (*sensors)[0] = SNS_DDF_SENSOR_ACCEL;
    (*sensors)[1] = SNS_DDF_SENSOR_GYRO;
    status = SNS_DDF_SUCCESS;
  } else {
    status = SNS_DDF_ENOMEM;
  }

  sns_ddf_close_port( port_handle );
  return status;
}

