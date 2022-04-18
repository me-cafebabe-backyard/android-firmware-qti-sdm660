#ifndef SNS_RH_MR_H
#define SNS_RH_MR_H
/*=============================================================================
  @file sns_rh_mr.h

  This header file contains the data definitions used within the
  Message Router module of Request Handler task.

******************************************************************************
* Copyright (c) 2014-2016 Qualcomm Technologies, Inc. 
* All Rights Reserved.
* Confidential and Proprietary - Qualcomm Technologies, Inc.
******************************************************************************/

/* $Header: //components/rel/ssc.slpi/2.2/smgr/src/sns_rh_mr.h#1 $ */
/* $DateTime: 2017/04/17 22:20:39 $ */
/* $Author: pwbldsvc $ */

/*============================================================================
  EDIT HISTORY FOR FILE

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------
  2016-12-01  bd   Fixed possible mem leak
  2016-04-13  ks   Dynamic calibration reset api support
  2016-03-11  tc   Add the service cookie to the connection list
  2016-02-11  pn   Tracks processor type over connection
  2015-11-23  pn   Locks connection when updating its busy flag
  2015-09-29  pn   Rearranged sns_rh_mr_header_s for ease of debugging
  2015-05-27  bd   Indication flow control in SMGR
  2015-04-09  pn   Updated timestamps from uint32_t to sns_ddf_time_t
  2014-12-07  pn   Added sns_rh_mr_validate_connection()
  2014-07-21  pn   Added support for event_gated_buffering
  2014-05-02  aj   Replaced QMI with SMR
  2014-04-29  pn   Refactored to support microImage
  2014-04-23  pn   Initial version

============================================================================*/

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/

#include "sns_osa.h"
#include "sns_queue.h"
#include "sns_rh.h"
#include "sns_smgr_api_v01.h"
#include "sns_smgr_internal_api_v02.h"
#include "sns_smgr_restricted_api_v01.h"
#include "sns_usmr.h"

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Structure Definitions
 * -------------------------------------------------------------------------*/
typedef union
{
  /* external services */
  sns_smgr_sensor_cal_req_msg_v01             calibration;
  sns_smgr_all_sensor_info_req_msg_v01        all_sensor_info;
  sns_smgr_single_sensor_info_req_msg_v01     single_sensor_info;
  sns_smgr_single_sensor_test_req_msg_v01     single_sensor_test;
  sns_smgr_periodic_report_req_msg_v01        periodic_report;
  sns_smgr_buffering_req_msg_v01              buffering_report;
  sns_smgr_buffering_query_req_msg_v01        query_report;
  sns_smgr_sensor_cal_reset_req_msg_v01       cal_reset;
  sns_smgr_phone_mode_switch_req_msg_v01      mode_switch;

  /* deprecated services */
  sns_smgr_sensor_status_req_msg_v01          deprecated_sensor_status;

  /* internal service */
  sns_smgr_sensor_events_query_req_msg_v02    sensor_events_query;
  sns_smgr_sensor_event_req_msg_v02           sensor_event;
  sns_smgr_sensor_status_monitor_req_msg_v02  sensor_status_monitor;
  sns_smgr_event_gated_buffering_req_msg_v02  event_gated_buffering_report;
  sns_smgr_sensor_cal_status_monitor_req_msg_v02   sensor_cal_status_monitor;

  /* restricted service */
  sns_smgr_driver_access_req_msg_v01          driver_access;

} sns_rh_request_type_u;

typedef union
{
  /* external service */
  sns_smgr_sensor_cal_resp_msg_v01            calibration;
  sns_smgr_all_sensor_info_resp_msg_v01       all_sensor_info;
  sns_smgr_single_sensor_info_resp_msg_v01    single_sensor_info;
  sns_smgr_single_sensor_test_resp_msg_v01    single_sensor_test;
  sns_smgr_periodic_report_resp_msg_v01       periodic_report;
  sns_smgr_buffering_resp_msg_v01             buffering_report;
  sns_smgr_buffering_query_resp_msg_v01       query_report;
  sns_smgr_sensor_cal_reset_resp_msg_v01      cal_reset;

  /* internal service */
  sns_smgr_sensor_events_query_resp_msg_v02   sensor_events_query;
  sns_smgr_sensor_event_resp_msg_v02          sensor_event;
  sns_smgr_sensor_status_monitor_resp_msg_v02 sensor_status_monitor;
  sns_smgr_event_gated_buffering_resp_msg_v02 event_gated_buffering_report;
  sns_smgr_sensor_cal_status_monitor_resp_msg_v02  sensor_cal_status_monitor;

} sns_rh_response_type_u;

typedef struct
{
  sns_ddf_time_t      timestamp;
  uint8_t             src_module;  /* Source module ID within the Sensors framework */
  uint8_t             svc_num;     /* SNS_xxxx_SVC_ID_V01 in sns_common_v01.h */
  uint16_t            msg_id;      /* depending on the service */
  uint16_t            body_len;
  void*               connection_handle;
  smr_req_handle      req_handle;
} sns_rh_mr_header_s;

struct sns_rh_mr_req_q_item_s
{
  sns_rh_mr_header_s    header;
  sns_rh_request_type_u request;
  sns_q_link_s          q_link;
};

/*----------------------------------------------------------------------------
 * Function Declarations and Documentation
 * -------------------------------------------------------------------------*/
extern void sns_rh_mr_init(void);

extern void sns_rh_mr_handle_disconnect_sig(void);

extern void sns_rh_mr_handle_external_event(void);

extern void sns_rh_mr_handle_internal_event(void);

extern void sns_rh_mr_handle_restricted_event(void);

extern sns_rh_mr_req_q_item_s* sns_rh_mr_get_msg(void);

extern sns_err_code_e sns_rh_mr_send_resp(
  const sns_rh_mr_header_s* msg_header_ptr, 
  void**                    resp_ptr);

extern void sns_rh_mr_send_resp_w_err(
  sns_rh_mr_req_q_item_s*   item_ptr);

extern bool sns_rh_mr_send_indication(
  void*                     conn_handle,
  void*                     ind_msg_ptr, 
  uint16_t                  msg_id, 
  uint16_t                  len, 
  bool                      free_me);

extern bool sns_rh_mr_conn_busy(
  const void*               conn_handle);

extern bool sns_rh_mr_validate_connection(
  const void*               conn_handle);

extern void sns_rh_mr_update_connection(
  void*                     conn_handle,
  sns_proc_type_e_v01       proc_type);

#endif /* #ifndef SNS_RH_MR_H */
