#ifndef SNS_RH_CAL_H_
#define SNS_RH_CAL_H_

/*============================================================================

  @file sns_rh_cal.h

  @brief
  This file contains definition for calibration functionality

  Copyright (c) 2016 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.

=============================================================================*/
/*============================================================================
  EDIT HISTORY FOR FILE

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------
  2016-09-12  np   Added support for SMGR_CAL_REQ_MSG
  2016-07-05  np   Support for calibration  .
 ============================================================================*/
#include "sns_smgr.h"
#include "sns_rh_mr_cal.h"
#include "sns_rh.h"
/*============================================================================

                   DEFINITIONS AND TYPES

=============================================================================*/
#define SNS_RH_MAX_CAL_REG 5
#define SNS_RH_INVALID_ID       0xFF
#define SNS_RH_ZERO_BIAS_LEN 3

/*===========================================================================

                   STRUCTURE DEFINITIONS

===========================================================================*/
typedef enum
{
  SNS_RH_CAL_MODE_UNKNOWN,
  SNS_RH_CAL_ALGO_NORMAL,
  SNS_RH_CAL_ALGO_RESETTING,
  SNS_RH_CAL_ALGO_REG_WRITING,
  SNS_RH_CAL_ALGO_MODE_SWITCHING,
} sns_rh_cal_algo_mode_e;

typedef struct libsensor_svc_accessor
{
  qmi_idl_service_object_type (*get_svc)(int32_t, int32_t, int32_t);
  int32_t maj_ver;
  int32_t min_ver;
  int32_t tool_ver;
} sam_svc_accessor;

typedef struct
{
  sns_rh_cal_algo_mode_e                 algo_mode;
  /* Sensor id on SMGR */
  smgr_sensor_id_e                       sensor_id;

  /*Whether the corresponding service is active */
  sns_rh_cal_algo_status_e               algo_status;

  /* Service object  */
  sam_svc_accessor                       sam_svc;
  /*Enable request and response  message id*/
  uint8_t                                enable_req_id;
  uint8_t                                enable_resp_id;

  /*Disable request and response message id */
  uint8_t                                disable_req_id;
  uint8_t                                disable_resp_id;

  /*Update request and response message id */
  uint8_t                                update_req_id;
  uint8_t                                update_resp_id;
  /*Current instance of calibration algorithm on SAM*/
  int32_t                                inst_id;
} sns_rh_cal_sam_map_s;

/*===========================================================================

                          FUNCTIONS

===========================================================================*/

extern sns_err_code_e    sns_rh_cal_scheduler(
  uint8_t                              sensor_id,
  bool                                 cal_flag );

extern void              sns_rh_cal_get_sensor_id (
  qmi_idl_service_object_type                  svc_obj,
  smgr_sensor_id_e                             *sensor_id,
  uint8_t                                      *index );


extern void              sns_rh_cal_check_clients(void);

extern void              sns_rh_cal_process_handle_sam_msg(void);

extern sns_err_code_e    sns_rh_cal_process_reset_request(
  sns_rh_mr_req_q_item_s**                      msg_ptr_ptr);

extern sns_ddf_status_e sns_rh_cal_process_user_calibration_req(
  sns_smgr_sensor_cal_req_msg_v01* req_ptr,
  sns_smgr_ddf_sensor_s*           ddf_sensor_ptr);
extern sns_err_code_e sns_rh_cal_scheduler(
  uint8_t                            sensor_id,
  bool                               cal_flag);

extern sns_err_code_e sns_rh_cal_process_mar_request(
  smgr_sensor_id_e const             sensor_id);

extern sns_err_code_e sns_rh_cal_process_mode_switch_request(
    sns_rh_mr_req_q_item_s**                      msg_ptr_ptr);

extern sns_ddf_status_e sns_rh_cal_process_calibration_ind(
  sns_sam_cal_report_ind_msg_v01*                                ind_msg,
  uint8_t                                                        usage,
  smgr_sensor_id_e                                               sensor_id,
  uint8_t                                                        data_type);
#endif /* SMGR_SRC_SNS_RH_CAL_H_ */
