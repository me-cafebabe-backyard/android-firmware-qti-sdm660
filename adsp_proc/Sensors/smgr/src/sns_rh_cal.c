/*=============================================================================
  @file sns_rh_cal.c

  This file implements Request Handler task.

*******************************************************************************
* Copyright (c) 2016-2017 Qualcomm Technologies, Inc.
* All Rights Reserved.
* Confidential and Proprietary - Qualcomm Technologies, Inc.
********************************************************************************/
/*============================================================================
  EDIT HISTORY FOR FILE

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------
  2017-02-16  qm   fix mem leak
  2016-12-22  qm   remove accuracy latency for first mag client
  2016-12-08  qm   Fix magcal reset req missing resp issue
  2016-12-07  bd   Fixed possible NULL pointer dereference
  2016-12-01  bd   Fixed possible mem leak
  2016-11-18  qm   Fix reset cal param during mode switch
  2016-11-10  qm   Added playback only singal when disable qmagcal
  2016-10-03  np   Support for MAR reset added.
  2016-09-12  np   Added support for SMGR_CAL_REQ_MSG
  2016-08-15  bd   Fix code review issues
  2016-07-05  np   Support for calibration  .
  ============================================================================*/

#include "sns_rh_cal.h"
#include "sns_rh_mr_cal.h"
#include "sns_rh_sol.h"
#include "sns_rh_util.h"
#include "sns_smgr_priv.h"
#include "sns_smgr_common_v01.h"
#include "sns_ddf_common.h"
#include "sns_smgr_util.h"
#include "sns_smgr_main.h"
#include "sns_sam_qmag_cal_v01.h"
#include "sns_sam_gyro_cal_v01.h"
#include "sns_sam_amd_v01.h"
#include "sns_smgr_reg.h"
#ifdef FAST_PLAYBACK
#include "playback.h"
#endif
extern sns_reg_mag_cal_params_data_group_s mag_fac_cal_reg_data;
/*----------------------------------------------------------------------------
 *  Variables
 * -------------------------------------------------------------------------*/
#define SNS_GET_SVC_OBJ( svc_name, version )                            \
  {   SNS_##svc_name##_SVC_get_service_object_internal_v##version,      \
      SNS_##svc_name##_SVC_V##version##_IDL_MAJOR_VERS,                 \
      SNS_##svc_name##_SVC_V##version##_IDL_MINOR_VERS,                 \
      SNS_##svc_name##_SVC_V##version##_IDL_TOOL_VERS }

static  sns_rh_cal_sam_map_s sns_rh_cal_map[] =
{
  { SNS_RH_CAL_ALGO_NORMAL,
    SNS_SMGR_ID_MAG_V01,
    SNS_RH_CAL_ALGO_DISABLED,
    SNS_GET_SVC_OBJ( SAM_QMAG_CAL, 01),
    SNS_SAM_QMAG_CAL_ENABLE_REQ_V01,
    SNS_SAM_QMAG_CAL_ENABLE_RESP_V01,
    SNS_SAM_QMAG_CAL_DISABLE_REQ_V01,
    SNS_SAM_QMAG_CAL_DISABLE_RESP_V01,
    SNS_SAM_QMAG_CAL_UPDATE_REQ_V01,
    SNS_SAM_QMAG_CAL_UPDATE_RESP_V01,
    SNS_RH_INVALID_ID},

  { SNS_RH_CAL_ALGO_NORMAL,
    SNS_SMGR_ID_GYRO_V01,
    SNS_RH_CAL_ALGO_DISABLED,
    SNS_GET_SVC_OBJ( SAM_GYRO_CAL, 01),
    SNS_SAM_GYRO_CAL_ENABLE_REQ_V01,
    SNS_SAM_GYRO_CAL_ENABLE_RESP_V01,
    SNS_SAM_GYRO_CAL_DISABLE_REQ_V01,
    SNS_SAM_GYRO_CAL_DISABLE_RESP_V01,
    SNS_SAM_GYRO_CAL_UPDATE_REQ_V01,
    SNS_SAM_GYRO_CAL_UPDATE_RESP_V01,
    SNS_RH_INVALID_ID}
};
extern sns_rh_mr_c   sns_rh_mr_cal_client;

/*----------------------------------------------------------------------------
 * Function Declarations and Documentation
 * -------------------------------------------------------------------------*/

/*===========================================================================

  FUNCTION:   sns_rh_cal_check_clients

===========================================================================*/
/*!
  @brief   Registers with SMR to check for SAM cal service connect.
  @param   none
  @return  none
 */
/*=========================================================================*/

void sns_rh_cal_check_clients(void)
{
  uint8_t j;
  smr_err err = SMR_NO_ERR;

  qmi_idl_service_object_type svc_obj;

  //Check SAM connectivity
  for( j=0; j<ARR_SIZE(sns_rh_cal_map) ; j++ )
  {
    if( sns_rh_cal_map[j].sam_svc.get_svc != NULL )
    {
      svc_obj = sns_rh_cal_map[j].sam_svc.get_svc(
                sns_rh_cal_map[j].sam_svc.maj_ver,
                sns_rh_cal_map[j].sam_svc.min_ver,
                sns_rh_cal_map[j].sam_svc.tool_ver );

      err = sns_rh_mr_cal_smr_client_check(svc_obj,
                                           SNS_RH_MR_INIT_CLIENT_TIMEOUT_US);
      if( err != SMR_NO_ERR )
      {
        SNS_SMGR_PRINTF1(ERROR,"SMR Client check failed for sensor id %d",
            sns_rh_cal_map[j].sensor_id);
      }
    }
    else
    {
      SNS_SMGR_PRINTF1(ERROR,"Service object is NULL for sensor Id %i",
          sns_rh_cal_map[j].sensor_id);
    }
  }
}
/*===========================================================================

  FUNCTION:   sns_rh_cal_get_svcid_index

===========================================================================*/
/*!
  @brief Returns the calibration algorithm index in the map.

  @detail
  @param[i]  svc_obj      QMI service object
  @param[o]  sensor_id    Sensor Id
  @param[o]  index        Index to be returned.

  @return    none
 */
/*=========================================================================*/
void sns_rh_cal_get_sensor_id (
  qmi_idl_service_object_type   svc_obj,
  smgr_sensor_id_e              *sensor_id,
  uint8_t                       *index )
{
  uint8_t j=0;
  qmi_idl_service_object_type   svc_obj_inst;
  for( j=0 ; j<ARR_SIZE(sns_rh_cal_map) ; j++ )
  {
    svc_obj_inst = sns_rh_cal_map[j].sam_svc.get_svc(
                   sns_rh_cal_map[j].sam_svc.maj_ver,
                   sns_rh_cal_map[j].sam_svc.min_ver,
                   sns_rh_cal_map[j].sam_svc.tool_ver );

    if( svc_obj_inst == svc_obj )
    {
      *sensor_id=sns_rh_cal_map[j].sensor_id;
      *index=j;
      break;
    }
  }
}
/*===========================================================================

  FUNCTION:   sns_rh_cal_get_sensor_index

===========================================================================*/
/*!
  @brief Returns the calibration algorithm index in the map.

  @detail
  @param[i]  Sensor Id
  @return    index
 */
/*=========================================================================*/
SMGR_STATIC uint8_t sns_rh_cal_get_sensor_index(
  smgr_sensor_id_e                              sensor_id)
{
  uint8_t j=0;
  for( j=0; j<ARR_SIZE(sns_rh_cal_map) ; j++ )
  {
    if( sns_rh_cal_map[j].sensor_id == sensor_id )
    {
      break;
    }
  }
  return j;
}

/*===========================================================================

  FUNCTION:   sns_rh_cal_sam_schedule

===========================================================================*/
/*!
  @brief   This function enables/disables calibration algorithms.

  @detail

  @param[i] calibrate_flag - Flag to enable/disable calibration.
  @param[i] cal_map - The calibration map object.
  @param[i] clnt_hndl  - SMR client handle for the algo.

  @return   sns_err_code_e
 */
/*=========================================================================*/
SMGR_STATIC sns_err_code_e sns_rh_cal_sam_schedule(
  bool                                            calibrate_flag,
  sns_rh_cal_sam_map_s *                          cal_map,
  smr_client_hndl                                 clnt_hndl)
{
  sns_err_code_e err = SNS_SUCCESS;
  SNS_SMGR_PRINTF2(LOW, "sns_rh_sam_cal_schedule Calibrate flag %d stored flag %d",calibrate_flag,cal_map->algo_status);
  if( calibrate_flag )
  {
    if( cal_map->algo_status == SNS_RH_CAL_ALGO_DISABLED )
    {
      err = sns_rh_mr_cal_send_enable_req(clnt_hndl,
                                          cal_map->enable_req_id,
                                          cal_map->sensor_id,
                                          sns_smgr.cal_phone_mode);
      if( err == SNS_SUCCESS )
      {
        cal_map->algo_status=SNS_RH_CAL_ALGO_ENABLING;
      }
    }
  }
  else
  {
    if( cal_map->algo_status == SNS_RH_CAL_ALGO_ENABLED )
    {
      sns_rh_mr_cal_send_update_req(clnt_hndl,
                                    cal_map->update_req_id,
                                    cal_map->inst_id,
                                    cal_map->sensor_id,
                                    CAL_UPDATE_REGISTRY_WRITE_V01);
      cal_map->algo_status=SNS_RH_CAL_ALGO_REG_WRITE;
      cal_map->algo_mode = SNS_RH_CAL_ALGO_REG_WRITING;

    }
  }
  return err;
}
/*===========================================================================

  FUNCTION:   sns_rh_cal_scheduler

===========================================================================*/
/*!
  @brief This function decides whether to enable/disable calibration for
         a sensor.
  @detail

  @param[i] sensor_id   Sensor Id for which calibration needs to be done.
  @param[i] cal_flag    Whether to enable or disable calibration.

  @return   sns_err_code_e
 */
/*=========================================================================*/

sns_err_code_e sns_rh_cal_scheduler(
  uint8_t                            sensor_id,
  bool                               cal_flag)
{
  uint8_t j;
  bool req_cal=false;
  sns_smgr_ddf_sensor_s* ddf_sensor_ptr = NULL;
  sns_err_code_e err=SNS_ERR_FAILED;

  for ( j=0; j<ARR_SIZE(sns_rh_cal_map); j++ )
  {
    if( !cal_flag && ( sns_rh_cal_map[j].sensor_id == sensor_id ))
    {
      ddf_sensor_ptr = sns_smgr_find_ddf_sensor(sensor_id,SNS_SMGR_DATA_TYPE_PRIMARY_V01);
      if( ddf_sensor_ptr == NULL )
      {
        SNS_SMGR_PRINTF0(ERROR,"DDF Sensor pointer NULL");
        break;
      }
      sns_rh_rpt_item_s* item_ptr = ddf_sensor_ptr->client_stat.rpt_item_ptr;

      while ( item_ptr != NULL )
      {
        sns_rh_rpt_item_s* cur_item_ptr = item_ptr;
        item_ptr = item_ptr->next_item_ptr;

        if( ( cur_item_ptr->cal_sel == SNS_SMGR_CAL_SEL_FULL_CAL_V01 ) &&
            ( cur_item_ptr->state   != RH_RPT_ITEM_STATE_UNLINKING   ) )
        {
          req_cal = true;
          break;
        }
      }
      err = sns_rh_cal_sam_schedule(req_cal,
                                    &sns_rh_cal_map[j],
                                    sns_rh_mr_cal_client.client_hndl[j]);
      break;
    }
    else if( cal_flag &&  ( sns_rh_cal_map[j].sensor_id == sensor_id ))
    {
      err = sns_rh_cal_sam_schedule(true,
                                    &sns_rh_cal_map[j],
                                    sns_rh_mr_cal_client.client_hndl[j]);
      break;
    }
  }
  return err;
}

 /*===========================================================================
   FUNCTION:   sns_rh_cal_apply_reset_req
 ===========================================================================*/
SMGR_STATIC sns_ddf_status_e sns_rh_cal_apply_reset_req(
  sns_smgr_request_response_s*                          smgr_req_resp_ptr)

{
  sns_smgr_ddf_sensor_s* ddf_sensor_ptr = smgr_req_resp_ptr->ddf_sensor_ptr;
  sns_smgr_all_cal_s* all_cal_ptr = ddf_sensor_ptr->all_cal_ptr;
  const sns_smgr_sensor_cal_reset_req_msg_v01* req_ptr =
      smgr_req_resp_ptr->req.cal_reset_ptr;
  sns_smgr_cal_s* cal_db_ptr;

  SNS_SMGR_PRINTF3(HIGH, "proc_cal_reset - usage=%u sensor=%u datatype=%u",
      req_ptr->usage,
      req_ptr->SensorId,
      req_ptr->DataType);

  if ( all_cal_ptr == NULL )
  {
    SNS_SMGR_PRINTF0(
        MED, "unsupported calibration reset request");
    SNS_OS_FREE(smgr_req_resp_ptr);
    return SNS_DDF_SUCCESS;
  }

  // reset auto_cal
  cal_db_ptr = &all_cal_ptr->auto_cal;
  cal_db_ptr->used = false;
  cal_db_ptr->need_to_log = false;
  cal_db_ptr->calibration_accuracy = 0;
  sns_smgr_load_default_cal(cal_db_ptr);

  // reset full_cal
  cal_db_ptr = &all_cal_ptr->full_cal;
  cal_db_ptr->used = false;
  cal_db_ptr->need_to_log = false;
  cal_db_ptr->calibration_accuracy = 0;
  sns_smgr_load_default_cal(cal_db_ptr);

  SNS_OS_FREE(smgr_req_resp_ptr);
  return SNS_DDF_SUCCESS;
}


 /*===========================================================================

   FUNCTION:   sns_rh_cal_update_fac_cal_mode

 ===========================================================================*/
 /*!
   @brief Update Application of calibration onto DDF.

   @detail switch fac cal param to be applied to new samples.

   @param[i]  msg_ptr - the request message

   @return  SNS_ERR_NOMEM or SNS_SUCCESS
  */
 /*=========================================================================*/
sns_err_code_e sns_rh_cal_update_fac_cal_mode(void)
{
  sns_smgr_ddf_sensor_s* ddf_sensor_ptr;
  sns_smgr_all_cal_s* all_cal_ptr;
  sns_smgr_cal_s* cal_db_ptr;
  uint32_t                  i;

  //we only update PRIMARY MAG here
  ddf_sensor_ptr = sns_smgr_find_ddf_sensor(SNS_SMGR_ID_MAG_V01, SNS_SMGR_DATA_TYPE_PRIMARY_V01);
  if ( ddf_sensor_ptr == NULL || ddf_sensor_ptr->all_cal_ptr == NULL)
  {
      SNS_SMGR_PRINTF0(ERROR, "fail to find mag sensor!!");
      return SNS_ERR_NOTSUPPORTED;
  }

  all_cal_ptr = ddf_sensor_ptr->all_cal_ptr;

  if ( all_cal_ptr == NULL )
  {
    SNS_SMGR_PRINTF0(
        MED, "unsupported calibration mode switch request");
    return SNS_ERR_NOTSUPPORTED;
  }

  // switch fac cal mode
  cal_db_ptr = &all_cal_ptr->factory_cal;
  cal_db_ptr->used = true;
  cal_db_ptr->need_to_log = false;
  cal_db_ptr->calibration_accuracy = 0;
  sns_smgr_load_default_cal(cal_db_ptr);

  if( mag_fac_cal_reg_data.mode[sns_smgr.cal_phone_mode].cal_mat_valid )
  {
    cal_db_ptr->compensation_matrix_valid = true;

    cal_db_ptr->compensation_matrix[0] = mag_fac_cal_reg_data.mode[sns_smgr.cal_phone_mode].compensation_matrix[0][0];
    cal_db_ptr->compensation_matrix[1] = mag_fac_cal_reg_data.mode[sns_smgr.cal_phone_mode].compensation_matrix[0][1];
    cal_db_ptr->compensation_matrix[2] = mag_fac_cal_reg_data.mode[sns_smgr.cal_phone_mode].compensation_matrix[0][2];
    cal_db_ptr->compensation_matrix[3] = mag_fac_cal_reg_data.mode[sns_smgr.cal_phone_mode].compensation_matrix[1][0];
    cal_db_ptr->compensation_matrix[4] = mag_fac_cal_reg_data.mode[sns_smgr.cal_phone_mode].compensation_matrix[1][1];
    cal_db_ptr->compensation_matrix[5] = mag_fac_cal_reg_data.mode[sns_smgr.cal_phone_mode].compensation_matrix[1][2];
    cal_db_ptr->compensation_matrix[6] = mag_fac_cal_reg_data.mode[sns_smgr.cal_phone_mode].compensation_matrix[2][0];
    cal_db_ptr->compensation_matrix[7] = mag_fac_cal_reg_data.mode[sns_smgr.cal_phone_mode].compensation_matrix[2][1];
    cal_db_ptr->compensation_matrix[8] = mag_fac_cal_reg_data.mode[sns_smgr.cal_phone_mode].compensation_matrix[2][2];

    SNS_SMGR_PRINTF1(
      LOW, "mag fac cal mode[%d]",sns_smgr.cal_phone_mode);
    SNS_SMGR_PRINTF3(
      LOW, "mag fac cal compensation_matrix: [0]:%u, [1]:%u, [2]:%u",
      (unsigned)cal_db_ptr->compensation_matrix[0],
      (unsigned)cal_db_ptr->compensation_matrix[1],
      (unsigned)cal_db_ptr->compensation_matrix[2]);
    SNS_SMGR_PRINTF3(
      LOW, "mag fac cal compensation_matrix: [0]:%u, [1]:%u, [2]:%u",
      (unsigned)cal_db_ptr->compensation_matrix[3],
      (unsigned)cal_db_ptr->compensation_matrix[4],
      (unsigned)cal_db_ptr->compensation_matrix[5]);
    SNS_SMGR_PRINTF3(
      LOW, "mag fac cal compensation_matrix: [0]:%u, [1]:%u, [2]:%u",
      (unsigned)cal_db_ptr->compensation_matrix[6],
      (unsigned)cal_db_ptr->compensation_matrix[7],
      (unsigned)cal_db_ptr->compensation_matrix[8]);
  }

  // reset full cal
  cal_db_ptr = &all_cal_ptr->full_cal;
  cal_db_ptr->used = true;
  cal_db_ptr->need_to_log = false;
  cal_db_ptr->calibration_accuracy = 0;
  sns_smgr_load_default_cal(cal_db_ptr);

  // reset auto_cal
  cal_db_ptr = &all_cal_ptr->auto_cal;
  cal_db_ptr->used = true;
  cal_db_ptr->need_to_log = false;
  cal_db_ptr->calibration_accuracy = 0;
  sns_smgr_load_default_cal(cal_db_ptr);

  //update active mode and write back to reg
  for(i = 0; i < PHONE_MODE_NUM; i++)
  {
    mag_fac_cal_reg_data.mode[i].active = false;
  }
  mag_fac_cal_reg_data.mode[sns_smgr.cal_phone_mode].active = true;

  SNS_SMGR_PRINTF1(
      MED, "update active phone mode to %d, write back to reg group", sns_smgr.cal_phone_mode);

#ifndef FAST_PLAYBACK
  sns_smgr_update_reg_data(SNS_REG_SCM_GROUP_MAG_FAC_CAL_PARAMS_V02,
                                      SNS_SMGR_REG_ITEM_TYPE_GROUP,
                                      sizeof(sns_reg_mag_cal_params_data_group_s),
                                      (uint8_t*)&mag_fac_cal_reg_data);
#endif
  return SNS_SUCCESS;
}


/*===========================================================================

  FUNCTION:   sns_rh_cal_process_mode_switch_request

===========================================================================*/
/*!
  @brief Handles Application of mode switch.

  @detail switch cal reg group and update cal algo config

  @param[i]  msg_ptr - the request message

  @return  SNS_ERR_NOMEM or SNS_SUCCESS
 */
/*=========================================================================*/
sns_err_code_e sns_rh_cal_process_mode_switch_request(
 sns_rh_mr_req_q_item_s**                      msg_ptr_ptr)
{
  uint8_t index;
  sns_rh_mr_req_q_item_s* msg_ptr = *msg_ptr_ptr;
  const sns_smgr_phone_mode_switch_req_msg_v01* req_ptr = &msg_ptr->request.mode_switch;
  sns_rh_mr_header_s resp_msg_header = msg_ptr->header;
  sns_smgr_phone_mode_switch_resp_msg_v01* resp_ptr =
     SMGR_ALLOC_STRUCT(sns_smgr_phone_mode_switch_resp_msg_v01);
  if ( resp_ptr == NULL )
  {
    return SNS_ERR_NOMEM;
  }

  SNS_SMGR_PRINTF2(
        MED, "mode_switch req received! - new phoneMode: %d, current phoneMode: %d", req_ptr->PhoneMode, sns_smgr.cal_phone_mode);

  //update phone mode and signal SMGR to reload the QMAG_FAC_CAL reg group
  if(req_ptr->PhoneMode != sns_smgr.cal_phone_mode){
    sns_smgr.cal_phone_mode = req_ptr->PhoneMode;

    //update fac cal
    sns_rh_cal_update_fac_cal_mode();

    //update auto cal
    sns_sam_cal_report_ind_msg_v01 mag_cal_ind_msg;
    mag_cal_ind_msg.accuracy = mag_dyn_cal_reg_data.mode[sns_smgr.cal_phone_mode].accuracy;
    mag_cal_ind_msg.bias[0] = -FX_FIXTOFLT_Q16(mag_dyn_cal_reg_data.mode[sns_smgr.cal_phone_mode].bias[0]);
    mag_cal_ind_msg.bias[1] = -FX_FIXTOFLT_Q16(mag_dyn_cal_reg_data.mode[sns_smgr.cal_phone_mode].bias[1]);
    mag_cal_ind_msg.bias[2] = -FX_FIXTOFLT_Q16(mag_dyn_cal_reg_data.mode[sns_smgr.cal_phone_mode].bias[2]);
    SNS_SMGR_PRINTF4(HIGH,
                "proc_reg_data - mag_dyn_cal_reg_data.mode(%d).bias: %d, %d, %d",
                sns_smgr.cal_phone_mode,
                mag_dyn_cal_reg_data.mode[sns_smgr.cal_phone_mode].bias[0],
                mag_dyn_cal_reg_data.mode[sns_smgr.cal_phone_mode].bias[1],
                mag_dyn_cal_reg_data.mode[sns_smgr.cal_phone_mode].bias[2]);

    sns_rh_cal_process_calibration_ind(&mag_cal_ind_msg, SNS_SMGR_CAL_DYNAMIC_V01,
                                       SNS_SMGR_ID_MAG_V01, SNS_SMGR_DATA_TYPE_PRIMARY_V01);

    //Update QMagCal algo with new mode
    index=sns_rh_cal_get_sensor_index(SNS_SMGR_ID_MAG_V01);
    if( index >= ARR_SIZE(sns_rh_cal_map) )
    {
      resp_ptr->Resp.sns_result_t        = SNS_RESULT_FAILURE_V01;
      resp_ptr->Resp.sns_err_t           = SENSOR1_EBAD_SVC_ID;

    }
    else if( ( sns_rh_cal_map[index].algo_mode   == SNS_RH_CAL_ALGO_NORMAL   ) &&
              ( sns_rh_cal_map[index].algo_status == SNS_RH_CAL_ALGO_DISABLED ))
    {
      SNS_SMGR_PRINTF1(
            MED, "no cal aglo enabled yet, only update smgr.cal_phone_mode to %d!", sns_smgr.cal_phone_mode);
    }
    else if( ( sns_rh_cal_map[index].algo_mode == SNS_RH_CAL_ALGO_NORMAL    ) &&
        ( sns_rh_cal_map[index].algo_status == SNS_RH_CAL_ALGO_ENABLED ))
    {
      //if already enabled, disable and re-enable with latest mode
    	sns_rh_cal_map[index].algo_mode = SNS_RH_CAL_ALGO_MODE_SWITCHING;
      sns_rh_mr_cal_send_disable_req(sns_rh_mr_cal_client.client_hndl[index],
                                            sns_rh_cal_map[index].disable_req_id,
                                            sns_rh_cal_map[index].inst_id,
                                            sns_rh_cal_map[index].sensor_id);
      SNS_SMGR_PRINTF1(
            MED, "cal aglo enabled, disable and restart with new phone mode %d!", sns_smgr.cal_phone_mode);
    }
    else
    {
      //when there is no cal algo running, return failure
      resp_ptr->Resp.sns_result_t        = SNS_RESULT_FAILURE_V01;
      resp_ptr->Resp.sns_err_t           = SENSOR1_ENOTALLOWED;
    }
  }

  if ( *msg_ptr_ptr != NULL )
  {
    resp_msg_header.msg_id = SNS_SMGR_PHONE_MODE_SWITCH_RESP_V01;
    resp_msg_header.body_len = sizeof(sns_smgr_phone_mode_switch_resp_msg_v01);
    sns_rh_mr_send_resp(&resp_msg_header, (void**)&resp_ptr);
  }

  return SNS_SUCCESS;
}

 /*===========================================================================

   FUNCTION:   sns_rh_cal_process_reset_request

 ===========================================================================*/
 /*!
   @brief Handles Application of calibration onto DDF.

   @detail Resets calibration data to be applied to new samples.

   @param[i]  msg_ptr - the request message

   @return  SNS_ERR_NOMEM or SNS_SUCCESS
  */
 /*=========================================================================*/
sns_err_code_e sns_rh_cal_process_reset_request(
  sns_rh_mr_req_q_item_s**                      msg_ptr_ptr)
{
  sns_rh_mr_req_q_item_s* msg_ptr = *msg_ptr_ptr;
  sns_smgr_sensor_cal_reset_req_msg_v01* req_ptr = &msg_ptr->request.cal_reset;
  sns_smgr_sensor_cal_reset_resp_msg_v01* resp_ptr =
      SMGR_ALLOC_STRUCT(sns_smgr_sensor_cal_reset_resp_msg_v01);
  sns_smgr_ddf_sensor_s* ddf_sensor_ptr =
      sns_smgr_find_ddf_sensor(req_ptr->SensorId, req_ptr->DataType);
  sns_rh_mr_header_s resp_msg_header = msg_ptr->header;
  sns_smgr_request_response_s* req_resp_ptr = NULL;
  uint8_t index;

  if ( resp_ptr == NULL )
  {
    return SNS_ERR_NOMEM;
  }

  SNS_SMGR_PRINTF3(
      MED, "proc_cal_reset - sensor=%d dtype=%d usage=%d",
      req_ptr->SensorId, req_ptr->DataType, req_ptr->usage);

  if ( ddf_sensor_ptr == NULL || ddf_sensor_ptr->all_cal_ptr == NULL ||
      req_ptr->usage != 0 )
  {
    resp_ptr->Resp.sns_result_t = SNS_RESULT_FAILURE_V01;
    resp_ptr->Resp.sns_err_t    = SENSOR1_EBAD_PARAM;
    SNS_SMGR_PRINTF3(ERROR, "proc_cal_reset - ddf_sensor_ptr 0x%x all_cal_ptr 0x%x usage %d",
                     ddf_sensor_ptr, ddf_sensor_ptr ?
                     ddf_sensor_ptr->all_cal_ptr : 0, req_ptr->usage);
  }
  else if ( (req_resp_ptr =
      SMGR_ALLOC_STRUCT(sns_smgr_request_response_s)) == NULL )
  {
    resp_ptr->Resp.sns_result_t = SNS_RESULT_FAILURE_V01;
    resp_ptr->Resp.sns_err_t    = SENSOR1_ENOMEM;
  }
  else
  {
    req_resp_ptr->ddf_sensor_ptr      = ddf_sensor_ptr;
    req_resp_ptr->msg_id              = msg_ptr->header.msg_id;
    req_resp_ptr->svc_num             = msg_ptr->header.svc_num;
    req_resp_ptr->req.cal_reset_ptr   = req_ptr;

    /* needed when processing response from SMGR later */
    msg_ptr->header.msg_id             = SNS_SMGR_CAL_RESET_RESP_V01;
    msg_ptr->header.body_len           = sizeof(sns_smgr_sensor_cal_reset_resp_msg_v01);
    req_resp_ptr->conn_handle          = msg_ptr->header.connection_handle;
    req_resp_ptr->req_handle           = &msg_ptr->header;
    req_resp_ptr->resp.cal_reset_ptr = resp_ptr;

    sns_rh_cal_apply_reset_req( req_resp_ptr);
    index=sns_rh_cal_get_sensor_index(req_ptr->SensorId);

    if( index >= ARR_SIZE(sns_rh_cal_map) )
    {
      resp_ptr->Resp.sns_result_t        = SNS_RESULT_FAILURE_V01;
      resp_ptr->Resp.sns_err_t           = SENSOR1_EBAD_SVC_ID;
      
    }
    else
    {
      resp_ptr->Resp.sns_result_t        = SNS_RESULT_SUCCESS_V01;
      resp_ptr->Resp.sns_err_t           = SENSOR1_SUCCESS;
      if( ( sns_rh_cal_map[index].algo_mode   == SNS_RH_CAL_ALGO_NORMAL   ) &&
          ( sns_rh_cal_map[index].algo_status == SNS_RH_CAL_ALGO_DISABLED ))
      {
        sns_rh_cal_map[index].algo_mode = SNS_RH_CAL_ALGO_RESETTING;
        sns_rh_mr_cal_send_enable_req(sns_rh_mr_cal_client.client_hndl[index],
                                      sns_rh_cal_map[index].enable_req_id,
                                      sns_rh_cal_map[index].sensor_id,
                                      sns_smgr.cal_phone_mode);
      }

      else if( ( sns_rh_cal_map[index].algo_mode == SNS_RH_CAL_ALGO_NORMAL    ) &&
               ( sns_rh_cal_map[index].algo_status == SNS_RH_CAL_ALGO_ENABLED ))
      {
        sns_rh_mr_cal_send_update_req(sns_rh_mr_cal_client.client_hndl[index],
                                      sns_rh_cal_map[index].update_req_id,
                                      sns_rh_cal_map[index].inst_id,
                                      sns_rh_cal_map[index].sensor_id,
                                      CAL_UPDATE_RESET_V01);
      }
    }
  }


  resp_msg_header.msg_id = SNS_SMGR_CAL_RESET_RESP_V01;
  resp_msg_header.body_len = sizeof(sns_smgr_sensor_cal_reset_resp_msg_v01);
  sns_rh_mr_send_resp(&resp_msg_header, (void**)&resp_ptr);


  return SNS_SUCCESS;
}
/*===========================================================================

   FUNCTION:   sns_rh_cal_process_mar_request

 ===========================================================================*/
 /*!
   @brief    Handles Application of MAR detection to reset HI biases.

   @detail   Resets calibration data to be applied to new samples.

   @param[i]  void

   @return  SNS_ERR_NOMEM or SNS_SUCCESS
  */
 /*=========================================================================*/
sns_err_code_e sns_rh_cal_process_mar_request(smgr_sensor_id_e const sensor_id)
{
  uint8_t index;

  SNS_SMGR_PRINTF1(MED, "process_mar_reset for sensor %d",sensor_id);

  index=sns_rh_cal_get_sensor_index(sensor_id);

  if( index >= ARR_SIZE(sns_rh_cal_map) )
  {
     return SNS_ERR_BAD_PARM;
  }
  else
  {
     if( ( sns_rh_cal_map[index].algo_mode   == SNS_RH_CAL_ALGO_NORMAL   ) &&
         ( sns_rh_cal_map[index].algo_status == SNS_RH_CAL_ALGO_DISABLED ))
      {
        sns_rh_cal_map[index].algo_mode = SNS_RH_CAL_ALGO_RESETTING;
        sns_rh_mr_cal_send_enable_req(sns_rh_mr_cal_client.client_hndl[index],
                                      sns_rh_cal_map[index].enable_req_id,
                                      sns_rh_cal_map[index].sensor_id,
                                      sns_smgr.cal_phone_mode);
      }
      else if( ( sns_rh_cal_map[index].algo_mode == SNS_RH_CAL_ALGO_NORMAL    ) &&
               ( sns_rh_cal_map[index].algo_status == SNS_RH_CAL_ALGO_ENABLED ))
      {
        sns_rh_mr_cal_send_update_req(sns_rh_mr_cal_client.client_hndl[index],
                                      sns_rh_cal_map[index].update_req_id,
                                      sns_rh_cal_map[index].inst_id,
                                      sns_rh_cal_map[index].sensor_id,
                                      CAL_UPDATE_RESET_V01);
      }
  }

  return SNS_SUCCESS;
}

 /*===========================================================================
   FUNCTION:   sns_rh_cal_process_calibration_ind
 ===========================================================================*/
 /*!
   @details Processes the calibration request and applies to DDF.

   @param[i]  indMsg - sns_sam_cal_report_ind_msg_v01 containing biases.

   @return  sns_ddf_status_e
  */
 /*=========================================================================*/

sns_ddf_status_e sns_rh_cal_process_calibration_ind(
  sns_sam_cal_report_ind_msg_v01*                                ind_msg,
  uint8_t                                                        usage,
  smgr_sensor_id_e                                               sensor_id,
  uint8_t                                                        data_type)
{
  if ( SNS_SMGR_CAL_DYNAMIC_V01 != usage )
    return SNS_DDF_EINVALID_ATTR;

  sns_sam_cal_report_ind_msg_v01 * calReq =( sns_sam_cal_report_ind_msg_v01 * )ind_msg;
  sns_smgr_ddf_sensor_s* ddf_sensor_ptr =
      sns_smgr_find_ddf_sensor(sensor_id,data_type);

  sns_smgr_all_cal_s* all_cal_ptr = NULL;
  uint8_t i;
  /* -------------------------------------------------------------------- */

  SNS_SMGR_PRINTF1(
      HIGH, "proc_cal - sensor=%u ",sensor_id);
  SNS_SMGR_PRINTF3(
      HIGH, "proc_cal - bias = 0x%08x 0x%08x 0x%08x",
      FX_FLTTOFIX_Q16(calReq->bias[0]),
      FX_FLTTOFIX_Q16(calReq->bias[1]),
      FX_FLTTOFIX_Q16(calReq->bias[2]));

  if ( ddf_sensor_ptr == NULL )
  {
    SNS_SMGR_PRINTF1(
      ERROR, "proc_cal - sensor=%u - Sensor not found",
      sensor_id);
    return SNS_DDF_EINVALID_PARAM;
  }
  all_cal_ptr = ddf_sensor_ptr->all_cal_ptr;

  if ( all_cal_ptr == NULL )
  {
    SNS_SMGR_PRINTF1(
        LOW, "proc_cal - sensor=%u - No cal needed", sensor_id);
    return SNS_DDF_SUCCESS;
  }

  if ( calReq->accuracy == 0 )
  {
    all_cal_ptr->full_cal.calibration_accuracy = 0;
    all_cal_ptr->auto_cal.calibration_accuracy = 0;
    SNS_SMGR_PRINTF1(
        LOW, "proc_cal - sensor=%u - unreliable accuracy", sensor_id);
    return SNS_DDF_SUCCESS;
  }
  else
  {
    all_cal_ptr->auto_cal.used           = true;
    all_cal_ptr->auto_cal.need_to_log    = false;
    all_cal_ptr->auto_cal.calibration_accuracy = calReq->accuracy;
    all_cal_ptr->full_cal.used             = true;
    all_cal_ptr->full_cal.need_to_log      = false;
    all_cal_ptr->full_cal.calibration_accuracy = calReq->accuracy;
  }

  SNS_SMGR_PRINTF1(
      HIGH, "proc_cal - accuracy(%u)", (unsigned)all_cal_ptr->full_cal.calibration_accuracy);

  for ( i=0; i<SNS_RH_ZERO_BIAS_LEN; i++ )
  {
    //All dynamic biases will be +ve when published from algorithm
    all_cal_ptr->auto_cal.zero_bias[i] = -FX_FLTTOFIX_Q16( calReq->bias[i] );
    all_cal_ptr->full_cal.zero_bias[i] =
      all_cal_ptr->factory_cal.zero_bias[i] +
      all_cal_ptr->auto_cal.zero_bias[i];
  }
  return SNS_DDF_SUCCESS;
}
 /*=========================================================================
   FUNCTION:  sns_rh_cal_process_sam_resp
   =========================================================================*/
 /*!
   @brief Processes the response received from SAM calibration algorithms.

   @param[i] smgrRespPtr: Pointer to SAM response message
   @param[i] msgId: Message ID
   @param[i] svcId: The service ID as msgId can be same.

   @return Sensors error code
 */
 /*=======================================================================*/
SMGR_STATIC sns_err_code_e sns_rh_cal_process_sam_resp(
  const void                                            *sam_resp_ptr,
  int32_t                                               msg_id,
  uint8_t                                               sensor_id)
{
  uint8_t j=0;

  for(j=0; j<ARR_SIZE(sns_rh_cal_map) ; j++)
  {
    if((  sns_rh_cal_map[j].enable_resp_id == msg_id ) &&
        ( sns_rh_cal_map[j].sensor_id == sensor_id   ))
    {
      sns_sam_cal_enable_resp_msg_v01* respPtr =
          (sns_sam_cal_enable_resp_msg_v01*)sam_resp_ptr;
      if ( respPtr->resp.sns_result_t != SNS_SUCCESS )
      {
        SNS_SMGR_PRINTF2(ERROR, "Error in CAL Algo Enable ins_id %d",
                         respPtr->instance_id,
                         respPtr->resp.sns_result_t);
        sns_rh_cal_map[j].algo_status= SNS_RH_CAL_ALGO_DISABLED;
        sns_rh_cal_map[j].inst_id = -1;
        return((sns_err_code_e)(respPtr->resp.sns_err_t));

      }

      sns_rh_cal_map[j].inst_id = respPtr->instance_id;
      sns_rh_cal_map[j].algo_status=SNS_RH_CAL_ALGO_ENABLED;

      if( sns_rh_cal_map[j].algo_mode == SNS_RH_CAL_ALGO_RESETTING )
      {
        sns_rh_mr_cal_send_update_req(sns_rh_mr_cal_client.client_hndl[j],
                                      sns_rh_cal_map[j].update_req_id,
                                      sns_rh_cal_map[j].inst_id,
                                      sns_rh_cal_map[j].sensor_id,
                                      CAL_UPDATE_RESET_V01);
      }
      else
      {
        sns_rh_cal_map[j].algo_mode = SNS_RH_CAL_ALGO_NORMAL;
      }
      break;
    }



    else if( ( sns_rh_cal_map[j].disable_resp_id == msg_id ) &&
             ( sns_rh_cal_map[j].sensor_id == sensor_id    ))
    {
      sns_sam_cal_disable_resp_msg_v01* respPtr =
          (sns_sam_cal_disable_resp_msg_v01*)sam_resp_ptr;

      if (respPtr->resp.sns_result_t != SNS_SUCCESS)
      {
        SNS_SMGR_PRINTF0(ERROR, "RH : error in SNS_SAM_CAL_DISABLE_RESP_V01");
        sns_rh_cal_map[j].algo_status=SNS_RH_CAL_ALGO_DISABLED;
        sns_rh_cal_map[j].inst_id =-1;

        return((sns_err_code_e)(respPtr->resp.sns_err_t));
      }
      if(SNS_RH_CAL_ALGO_MODE_SWITCHING == sns_rh_cal_map[j].algo_mode)
      {
        SNS_SMGR_PRINTF1(MED, "RH : switch on cal algo with new phone mode %d", sns_smgr.cal_phone_mode);
        sns_rh_mr_cal_send_enable_req(sns_rh_mr_cal_client.client_hndl[j],
                                      sns_rh_cal_map[j].enable_req_id,
                                      sns_rh_cal_map[j].sensor_id,
                                      sns_smgr.cal_phone_mode);
      }
      else
      {
      sns_rh_cal_map[j].algo_mode = SNS_RH_CAL_ALGO_NORMAL;
      sns_rh_cal_map[j].algo_status = SNS_RH_CAL_ALGO_DISABLED;
      sns_rh_cal_map[j].inst_id = -1;
#ifdef FAST_PLAYBACK
      uint8_t errOS;
      sns_os_sigs_post( playback_disable_sig_event,
      FPB_CLIENT_DISABLE_DONE, OS_FLAG_SET, &errOS );
#endif
      }
      break;
    }

    else if( ( sns_rh_cal_map[j].update_resp_id == msg_id ) &&
             ( sns_rh_cal_map[j].sensor_id == sensor_id   ))
    {
      sns_sam_cal_update_resp_msg_v01* respPtr =
          (sns_sam_cal_update_resp_msg_v01*)sam_resp_ptr;

      if ( respPtr->resp.sns_result_t != SNS_SUCCESS )
      {
        SNS_SMGR_PRINTF0(ERROR, "RH : error in SNS_SAM_CAL_UPDATE_RESP_V01");
        return((sns_err_code_e)(respPtr->resp.sns_err_t));
      }
      else if( sns_rh_cal_map[j].algo_mode == SNS_RH_CAL_ALGO_RESETTING
          || sns_rh_cal_map[j].algo_mode == SNS_RH_CAL_ALGO_REG_WRITING )
      {
        sns_rh_cal_map[j].algo_mode =SNS_RH_CAL_ALGO_NORMAL;
        sns_rh_cal_map[j].algo_status = SNS_RH_CAL_ALGO_ENABLED ;
        sns_rh_mr_cal_send_disable_req(sns_rh_mr_cal_client.client_hndl[j],
                                       sns_rh_cal_map[j].disable_req_id,
                                       sns_rh_cal_map[j].inst_id,
                                       sns_rh_cal_map[j].sensor_id);
      }
      break;
    }

  }

  return SNS_SUCCESS;
}
 /*===========================================================================

   FUNCTION:   sns_rh_cal_process_handle_sam_msg

 ===========================================================================*/
 /*!
   @brief Handles SNS_RH_SAM_MSG_SIG signal

   @detail
   @param  none
   @return none
  */
 /*=========================================================================*/
void sns_rh_cal_process_handle_sam_msg(void)
{
  sns_rh_cal_q_item_s *msg_ptr;
  uint8_t index;
  sns_rh_cal_algo_status_e status;
  smgr_sensor_id_e sensor_id;
  while ( sns_q_cnt(&sns_rh_mr_cal_client.sam_q) != 0 )
  {
    sns_os_mutex_pend(sns_rh_mr_cal_client.mutex_ptr, 0, NULL);
    msg_ptr = sns_q_get(&sns_rh_mr_cal_client.sam_q);
    sns_os_mutex_post(sns_rh_mr_cal_client.mutex_ptr);

    index = sns_rh_cal_get_sensor_index(msg_ptr->sensor_id);
    
    if( msg_ptr->rh_msg_type == RH_SAM_IND_MSG &&
        index < ARR_SIZE(sns_rh_cal_map) )
    {
      status = sns_rh_cal_map[index].algo_status;
      sensor_id = sns_rh_cal_map[index].sensor_id;
      switch(sensor_id)
      {
        case  SNS_SMGR_ID_MAG_V01:
        case  SNS_SMGR_ID_GYRO_V01:
        {
          sns_sam_cal_report_ind_msg_v01 * indMsg= (sns_sam_cal_report_ind_msg_v01 *)msg_ptr->body_ptr;
          if( ( status == SNS_RH_CAL_ALGO_ENABLED  )||
              (( status == SNS_RH_CAL_ALGO_ENABLING )))

            sns_rh_cal_process_calibration_ind(indMsg,
                                               SNS_SMGR_CAL_DYNAMIC_V01,
                                               sensor_id,
                                               SNS_SMGR_DATA_TYPE_PRIMARY_V01);
           //save mag HI locally, so when mode switch we can apply right away
          if(SNS_SMGR_ID_MAG_V01 == sensor_id)
          {
            mag_dyn_cal_reg_data.mode[sns_smgr.cal_phone_mode].accuracy  = indMsg->accuracy;
            mag_dyn_cal_reg_data.mode[sns_smgr.cal_phone_mode].bias[0] = -FX_FLTTOFIX_Q16(indMsg->bias[0]);
            mag_dyn_cal_reg_data.mode[sns_smgr.cal_phone_mode].bias[1] = -FX_FLTTOFIX_Q16(indMsg->bias[1]);
            mag_dyn_cal_reg_data.mode[sns_smgr.cal_phone_mode].bias[2] = -FX_FLTTOFIX_Q16(indMsg->bias[2]);
          }
        }
        break;
        default:
        {
          SNS_SMGR_PRINTF0(ERROR, "Invalid Service Id");
        }
        break;
      }
    }
    else if( msg_ptr->rh_msg_type == RH_SAM_RESP_MSG )
    {
      sns_rh_cal_process_sam_resp(msg_ptr->body_ptr,
                                  msg_ptr->msg_id,
                                  msg_ptr->sensor_id);
    }
    SNS_OS_FREE((void*)msg_ptr->body_ptr);
    SNS_OS_FREE((void *)msg_ptr);
    msg_ptr = NULL;
  }
}

/*===========================================================================

   FUNCTION:   sns_rh_cal_process_user_calibration_req

 ===========================================================================*/
 /*!
   @brief Handles SMGR USER CAL REQ message

   @detail
   @param  req_ptr          SMGR calibration request pointer
           ddf_sensor_ptr   Sensor ddf pointer
   @return sns_ddf_status_e
  */
 /*=========================================================================*/
sns_ddf_status_e sns_rh_cal_process_user_calibration_req(
  sns_smgr_sensor_cal_req_msg_v01* req_ptr,
  sns_smgr_ddf_sensor_s*           ddf_sensor_ptr)
{
  uint8_t i;
  sns_smgr_all_cal_s* all_cal_ptr = ddf_sensor_ptr->all_cal_ptr;
  sns_smgr_cal_s* cal_db_ptr;
  /* -------------------------------------------------------------------- */

  SNS_SMGR_PRINTF3(
    HIGH, "proc_cal - sensor=%u dynamic=%u matrix=%u",
    req_ptr->SensorId, (req_ptr->usage == SNS_SMGR_CAL_DYNAMIC_V01),
    req_ptr->CompensationMatrix_valid);
  SNS_SMGR_PRINTF3(
    HIGH, "proc_cal - bias = 0x%08x 0x%08x 0x%08x",
    req_ptr->ZeroBias[0], req_ptr->ZeroBias[1], req_ptr->ZeroBias[2]);

  if ( all_cal_ptr == NULL )
  {
    SNS_SMGR_PRINTF1(
      MED, "proc_cal - sensor=%u - No cal needed", req_ptr->SensorId);
    return SNS_DDF_SUCCESS;
  }

  if ( (req_ptr->CalibrationAccuracy_valid) &&
       (req_ptr->CalibrationAccuracy == 0) )
  {
    all_cal_ptr->full_cal.calibration_accuracy = 0;
    cal_db_ptr = (SNS_SMGR_CAL_FACTORY_V01 == req_ptr->usage) ?
        &all_cal_ptr->factory_cal : &all_cal_ptr->auto_cal;
    cal_db_ptr->calibration_accuracy = 0;
    SNS_SMGR_PRINTF1(
      MED, "proc_cal - sensor=%u - unreliable accuracy", req_ptr->SensorId);
    return SNS_DDF_SUCCESS;
  }

  if ( SNS_SMGR_CAL_FACTORY_V01 == req_ptr->usage )
  {
    /* Nullify all autocal data */
    //TODO - Reset calibration algorithm on SAM if required in future.
    all_cal_ptr->auto_cal.used           = false;
    sns_smgr_load_default_cal(&all_cal_ptr->auto_cal);

    /* set logging flag to be logged */
    all_cal_ptr->factory_cal.used        = true;
    all_cal_ptr->factory_cal.need_to_log = true;
    cal_db_ptr = &all_cal_ptr->factory_cal;
  }
  else  /* SNS_SMGR_CAL_DYNAMIC_V01 */
  {
    all_cal_ptr->auto_cal.used           = true;
    all_cal_ptr->auto_cal.need_to_log    = true;
    cal_db_ptr = &all_cal_ptr->auto_cal;
  }

  all_cal_ptr->full_cal.used             = true;
  all_cal_ptr->full_cal.need_to_log      = true;
  all_cal_ptr->full_cal.calibration_accuracy =
    cal_db_ptr->calibration_accuracy         =
    req_ptr->CalibrationAccuracy_valid ? req_ptr->CalibrationAccuracy : 0;

  SNS_SMGR_PRINTF1(
    HIGH, "proc_cal - accuracy(%u)", (unsigned)cal_db_ptr->calibration_accuracy);

  for ( i=0; i<req_ptr->ZeroBias_len; i++ )
  {
    cal_db_ptr->zero_bias[i] = req_ptr->ZeroBias[i];
    all_cal_ptr->full_cal.zero_bias[i] =
      all_cal_ptr->factory_cal.zero_bias[i] +
      all_cal_ptr->auto_cal.zero_bias[i];
  }
  for ( i=0; i<req_ptr->ScaleFactor_len; i++ )
  {
    cal_db_ptr->scale_factor[i] = req_ptr->ScaleFactor[i];
    all_cal_ptr->full_cal.scale_factor[i] = req_ptr->ScaleFactor[i];
  }
  if ( req_ptr->CompensationMatrix_valid )
  {
    cal_db_ptr->compensation_matrix_valid = true;
    for ( i=0; i<ARR_SIZE(cal_db_ptr->compensation_matrix); i++)
    {
      cal_db_ptr->compensation_matrix[i] = req_ptr->CompensationMatrix[i];
      SNS_SMGR_PRINTF2(
        ERROR, "proc_cal - Matrix[%d] = %d",
        i, (int)cal_db_ptr->compensation_matrix[i]);
    }
  }
  return SNS_DDF_SUCCESS;
}

