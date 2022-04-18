/*=============================================================================
  @file sns_rh_mr.c

  This file implements the Message Router module of Request Handler task.

*******************************************************************************
* Copyright (c) 2014-2017 Qualcomm Technologies, Inc.
* All Rights Reserved.
* Confidential and Proprietary - Qualcomm Technologies, Inc.
********************************************************************************/

/* $Header: //components/rel/ssc.slpi/2.2/smgr/src/sns_rh_mr.c#1 $ */
/* $DateTime: 2017/04/17 22:20:39 $ */
/* $Author: pwbldsvc $ */

/*============================================================================
  EDIT HISTORY FOR FILE

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------
  2017-03-14  bd   Send FAKE APP wake up signal when receiving requests from APP  
  2016-12-01  bd   Fixed possible mem leak
  2016-10-17  np   Moved the FAKE APP wake up signal to update connection.
  2016-08-10  np   Added playback support.  
  2016-07-13  np   Support for calibration algorithm
  2016-06-21  pn   Cleans up connection entry when disconnected
                   Updated sns_rh_mr_conn_busy()
  2016-05-16  pn   Replaced connection array with connection queue
  2016-04-01  jtl  Fix disconnect callback to fully clean up internal services
  2016-03-14  gju  Include string1.h for memscpy
  2016-02-11  pn   RH fakes WAKE_SIG when it receives messages from AP
  2015-11-23  pn   Locks connection when updating its busy flag
  2015-05-27  bd   Indication flow control in SMGR
  2015-04-09  pn   Replaced calls to sns_em_get_timestamp() with sns_ddf_get_timestamp()
  2014-12-30  pn   Fixed memory access after free in sns_rh_mr_send_resp()
  2014-12-16  pn   Fixed potential memory corruption in sns_rh_mr_put_msg()
  2014-12-07  pn   Drops requests orphaned by QMI disconnection
  2014-09-16  pn   Consolidated all process_req callbacks into one
  2014-08-13  sc   Fixed compilaton warning (corrected function prototyping)
  2014-05-02  aj   Replaced QMI with SMR
  2014-04-29  pn   Refactored to support microImage
  2014-04-23  pn   Initial version

============================================================================*/
/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "sns_em.h"
#include "sns_memmgr.h"
#include "sns_rh_main.h"
#include "sns_rh_mr.h"
#include "sns_rh_internal_svc.h"
#include "sns_rh_restricted_svc.h"
#include "sns_rh_util.h"
#include "sns_rh_mr_cal.h"
/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/
#define SNS_RH_MR_MSG_HISTORY_MAX_COUNT           16
#define SNS_RH_MR_MSG_HISTORY_BYTES2SAVE          32

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/
typedef struct
{
  sns_rh_mr_header_s  msg_header;
  uint8_t             body[SNS_RH_MR_MSG_HISTORY_BYTES2SAVE - sizeof(sns_rh_mr_header_s)];
} sns_rh_mr_msg_content_s;

typedef struct
{
  uint32_t                num_rcvd_msgs;
  sns_rh_mr_msg_content_s msg_contents[SNS_RH_MR_MSG_HISTORY_MAX_COUNT];
} sns_rh_mr_msg_history_s;

typedef struct
{
  sns_q_link_s            conn_q_link;
  smr_qmi_client_handle   client_handle;
  uint32_t                service_cookie;
  sns_proc_type_e_v01     proc_type;
  bool                    proc_type_is_valid;
  bool                    is_busy;  /* set to false in resume_cb()*/
  sns_ddf_time_t          timestamp;
  sns_rh_mr_header_s      last_msg_header; /* header of last msg received on this conn */
} sns_rh_mr_connection_s;

typedef struct  
{
  /* SMR server interface */
  smr_service_hndl            service_handle_ext;
  uint32_t                    service_cookie_ext;

  smr_service_hndl            service_handle_int;
  uint32_t                    service_cookie_int;

  smr_service_hndl            service_handle_restricted;
  uint32_t                    service_cookie_restricted;

  sns_q_s                     connection_q;
  sns_q_s                     disconnection_q;

  sns_q_s                     req_queue;
  OS_EVENT*                   mutex_ptr;

  sns_rh_mr_msg_history_s     msg_history;
  uint16_t                    max_connections;

} sns_rh_mr_s;


/*----------------------------------------------------------------------------
 *  Variables
 * -------------------------------------------------------------------------*/
sns_rh_mr_s   sns_rh_mr;

/*----------------------------------------------------------------------------
 * Macro
 * -------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
 * Function Declarations and Documentation
 * -------------------------------------------------------------------------*/
  /*===========================================================================
  
    FUNCTION:   sns_rh_mr_get_src_module
  
  ===========================================================================*/

SMGR_STATIC uint8_t sns_rh_mr_get_src_module(sns_rh_mr_req_q_item_s* msg_ptr)
{
  uint8_t src_module = (uint8_t)-1;
  switch ( msg_ptr->header.msg_id)
  {
  case SNS_SMGR_REPORT_REQ_V01:
    if ( msg_ptr->request.periodic_report.SrcModule_valid )
    {
      src_module = msg_ptr->request.periodic_report.SrcModule;
    }
    break;
  case SNS_SMGR_BUFFERING_REQ_V01:
    if ( msg_ptr->request.buffering_report.SrcModule_valid )
    {
      src_module = msg_ptr->request.buffering_report.SrcModule;
    }
    break;
  case SNS_SMGR_BUFFERING_QUERY_REQ_V01:
    if ( msg_ptr->request.query_report.SrcModule_valid )
    {
      src_module = msg_ptr->request.query_report.SrcModule;
    }
    break;
  default:
    break;
  }
  return src_module;
}
/*===========================================================================

  FUNCTION:   sns_rh_mr_track_msg_history

===========================================================================*/
SMGR_STATIC void sns_rh_mr_track_msg_history(sns_rh_mr_req_q_item_s* msg_ptr)
{
  uint32_t idx = sns_rh_mr.msg_history.num_rcvd_msgs %
    ARR_SIZE(sns_rh_mr.msg_history.msg_contents);
  sns_rh_mr.msg_history.msg_contents[idx].msg_header = msg_ptr->header;
  SNS_OS_MEMSCPY(sns_rh_mr.msg_history.msg_contents[idx].body,
          sizeof(sns_rh_mr.msg_history.msg_contents[idx].body),
          &msg_ptr->request, sizeof(sns_rh_mr.msg_history.msg_contents[idx].body));
  sns_rh_mr.msg_history.num_rcvd_msgs++;
}

/*=============================================================================
  FUNCTION sns_rh_mr_put_msg
=============================================================================*/
/*!
@brief
  This puts the SMGR QMI messages into Queue and posts the signal

@param[in]  connection_handle  connection handle to differntiate the clients

@param[in]  req_handle         handle used for each requests

@param[in]  msg_id             Message ID of the indication

@param[in]  buff_ptr           Buffer holding the data

@param[in]  buff_len           Number of bytes in buffer

@param[in]  svc_num            Service number

@return  Returns QMI_CSI_CB_NO_ERR or QMI_CSI_CB_INTERNAL_ERR or QMI_CSI_CB_NO_MEM

*/
/*=========================================================================*/
SMGR_STATIC smr_cb_err sns_rh_mr_put_msg(
  void*           connection_handle,
  smr_req_handle  req_handle,
  unsigned int    msg_id,
  void*           buff_ptr,
  unsigned int    buff_len,
  uint8_t         svc_num)
{
  sns_rh_mr_req_q_item_s* msg_ptr = NULL;
  sns_rh_mr_connection_s* conn_ptr = (sns_rh_mr_connection_s*)connection_handle;

  SNS_SMGR_PRINTF5(
    HIGH, "put_msg - conn=0x%x cli=0x%x req_hndl=0x%x type=%u/=0x%02x",
    conn_ptr, conn_ptr ? conn_ptr->client_handle : 0, req_handle, svc_num, msg_id);

  if ( !sns_rh_mr_validate_connection(connection_handle) )
  {
    SNS_SMGR_PRINTF0(ERROR, "put_msg - invalid connection, dropping request");
    return SMR_CB_CONN_REFUSED;
  }

  msg_ptr = SMGR_ALLOC_STRUCT(sns_rh_mr_req_q_item_s);
  if ( msg_ptr == NULL )
  {
    SNS_SMGR_PRINTF1(ERROR, "put_msg - fail alloc size=%b", buff_len);
    return SMR_CB_NO_MEM;
  }
  msg_ptr->header.timestamp         = sns_ddf_get_timestamp();
  msg_ptr->header.svc_num           = svc_num;
  msg_ptr->header.msg_id            = msg_id;
  msg_ptr->header.body_len          = buff_len;
  msg_ptr->header.connection_handle = connection_handle;
  msg_ptr->header.req_handle        = req_handle;
  SNS_OS_MEMSCPY(&msg_ptr->request, sizeof(msg_ptr->request), buff_ptr, buff_len);
  sns_q_link(msg_ptr, &msg_ptr->q_link);

  sns_rh_mr_track_msg_history(msg_ptr);
  conn_ptr->last_msg_header = msg_ptr->header;

  sns_os_mutex_pend(sns_rh_mr.mutex_ptr, 0, NULL);
  sns_q_put(&sns_rh_mr.req_queue, &msg_ptr->q_link);
  sns_os_mutex_post(sns_rh_mr.mutex_ptr);
  if ( sns_rh_mr_get_src_module(msg_ptr) < SNS_MODULE_DSPS ||
       (conn_ptr->proc_type_is_valid && conn_ptr->proc_type == SNS_PROC_APPS_V01))
  {
    sns_rh_signal_me(SNS_RH_APP_WAKE_SIG);
  }
  sns_rh_signal_me(SNS_RH_SMR_MSG_SIG);

  return SMR_CB_NO_ERR;
}


/*=========================================================================
  FUNCTION:  sns_rh_mr_get_msg
  =========================================================================*/
sns_rh_mr_req_q_item_s* sns_rh_mr_get_msg(void)
{
  sns_rh_mr_req_q_item_s* msg_ptr = NULL;

  sns_os_mutex_pend(sns_rh_mr.mutex_ptr, 0, NULL);
  msg_ptr = (sns_rh_mr_req_q_item_s*) sns_q_get(&sns_rh_mr.req_queue);
  sns_os_mutex_post(sns_rh_mr.mutex_ptr);

  return msg_ptr;
}

/*=========================================================================
  CALLBACK FUNCTION:  sns_rh_mr_smr_connect_cb
  =========================================================================*/
/*!
  @brief Callback registered with SMR to receive connect requests
*/
/*=======================================================================*/
SMGR_STATIC smr_cb_err sns_rh_mr_smr_connect_cb(
  smr_qmi_client_handle client_handle,
  void*                 service_cookie,
  void**                connection_handle)
{
  smr_cb_err smr_err = SMR_CB_NO_ERR;
  sns_rh_mr_connection_s* new_conn_ptr = NULL;

  if ( service_cookie == NULL || connection_handle == NULL )
  {
    smr_err = SMR_CB_CONN_REFUSED;
  }
  else if ( (new_conn_ptr = SMGR_ANY_ALLOC_STRUCT(sns_rh_mr_connection_s)) == NULL )
  {
    smr_err = SMR_CB_NO_MEM;
  }

  if ( new_conn_ptr != NULL )
  {
    uint16_t num_connections;

    sns_q_link(new_conn_ptr, &new_conn_ptr->conn_q_link);
    new_conn_ptr->is_busy        = false;
    new_conn_ptr->client_handle  = client_handle;
    new_conn_ptr->service_cookie = *(uint32_t*)service_cookie;
    new_conn_ptr->timestamp      = sns_ddf_get_timestamp();
    *connection_handle = (void*)new_conn_ptr;

    sns_os_mutex_pend(sns_rh_mr.mutex_ptr, 0, NULL);
    sns_q_put(&sns_rh_mr.connection_q, &new_conn_ptr->conn_q_link);
    num_connections = sns_q_cnt(&sns_rh_mr.connection_q);
    sns_os_mutex_post(sns_rh_mr.mutex_ptr);
    if ( sns_rh_mr.max_connections < num_connections )
    {
      sns_rh_mr.max_connections = num_connections;
    }
    SNS_SMGR_PRINTF5(
      HIGH, "connect_cb -     conn=0x%x cli=0x%x cookie=%u #conns(curr/max)=%u/%u",
      new_conn_ptr, new_conn_ptr->client_handle, new_conn_ptr->service_cookie,
      num_connections, sns_rh_mr.max_connections);
  }
  else
  {
    SNS_SMGR_PRINTF2(
      ERROR, "connect_cb - cli_hndl 0x%x refused with err code %u", 
      client_handle, smr_err);
  }
  return smr_err;
}

/*=========================================================================
  CALLBACK FUNCTION:  sns_rh_mr_smr_disconnect_cb
  =========================================================================*/
/*!
  @brief Callback registered with SMR to receive disconnect requests
*/
/*=======================================================================*/
SMGR_STATIC void sns_rh_mr_smr_disconnect_cb(
  void* connection_handle,
  void* service_cookie)
{
  sns_rh_mr_connection_s* conn_ptr = (sns_rh_mr_connection_s*)connection_handle;

  if ( sns_rh_mr_validate_connection(connection_handle) && service_cookie != NULL &&
       *(uint32_t*)service_cookie == conn_ptr->service_cookie )
  {
    sns_os_mutex_pend(sns_rh_mr.mutex_ptr, 0, NULL);
    sns_q_delete(&conn_ptr->conn_q_link);
    sns_q_put(&sns_rh_mr.disconnection_q, &conn_ptr->conn_q_link);
    sns_os_mutex_post(sns_rh_mr.mutex_ptr);
    sns_rh_signal_me(SNS_RH_SMR_DISC_SIG);

    SNS_SMGR_PRINTF3(
      HIGH, "disconnect_cb -  conn=0x%x cli=0x%x #conns=%u",
      conn_ptr, conn_ptr->client_handle, sns_q_cnt(&sns_rh_mr.connection_q));
  }
  else
  {
    SNS_SMGR_PRINTF3(
      ERROR, "disconnect_cb - invalid params conn=0x%x cookie=0x%x/%d",
      connection_handle, service_cookie, service_cookie ? *(uint32_t*)service_cookie : -1);
  }
}

/*===========================================================================

  FUNCTION:   sns_rh_mr_update_connection_state

===========================================================================*/
/*!
  @brief Updates the busy state of the given connection

  @param [io] conn_ptr - the connection to update
  @param [i]  busy     - true if the connection became busy

  @return None
 */
/*=========================================================================*/
SMGR_STATIC void sns_rh_mr_update_connection_state(
  sns_rh_mr_connection_s* conn_ptr, 
  bool busy
)
{
  sns_os_mutex_pend(sns_rh_mr.mutex_ptr, 0, NULL);
  conn_ptr->is_busy = busy;
  sns_os_mutex_post(sns_rh_mr.mutex_ptr);
}

/*=========================================================================
  CALLBACK FUNCTION:  sns_rh_mr_smr_resume_cb
  =========================================================================*/
/*!
  @brief Callback registered with SMR to receive resume requests
*/
/*=======================================================================*/
SMGR_STATIC void sns_rh_mr_smr_resume_cb(
  void* connection_handle,
  void* service_cookie)
{
  sns_rh_mr_connection_s* conn_ptr = (sns_rh_mr_connection_s*)connection_handle;

  if ( sns_rh_mr_validate_connection(connection_handle) && service_cookie != NULL &&
       *(uint32_t*)service_cookie == conn_ptr->service_cookie )
  {
    SNS_SMGR_PRINTF2(HIGH, "resume_cb - conn=0x%x cli=0x%x q_ptr=0x%x", 
                     conn_ptr, conn_ptr->client_handle);

    sns_rh_mr_update_connection_state(conn_ptr, false);
    sns_rh_signal_me(SNS_RH_SMR_RESUME_SIG);
  }
  else
  {
    SNS_SMGR_PRINTF3(
      ERROR, "resume_cb - invalid params conn=0x%x cookie=0x%x/%d",
      connection_handle, service_cookie, service_cookie ? *(uint32_t*)service_cookie : -1);
  }
}


/*=========================================================================
  CALLBACK FUNCTION:  sns_rh_mr_smr_process_req_cb
  =========================================================================*/
/*!
  @brief Callback registered with SMR to receive service requests
*/
/*=======================================================================*/
SMGR_STATIC smr_cb_err sns_rh_mr_smr_process_req_cb(
  void*          connection_handle,
  smr_req_handle req_handle,
  unsigned int   msg_id,
  void*          req_c_struct,
  unsigned int   req_c_struct_len,
  void*          service_cookie)
{
  if ( service_cookie != NULL )
  {
    return sns_rh_mr_put_msg(connection_handle,
                             req_handle,
                             msg_id,
                             req_c_struct,
                             req_c_struct_len,
                             *(uint32_t*)service_cookie);
  }
  else
  {
    return SMR_CB_INTERNAL_ERR;
  }
}

/*===========================================================================

  FUNCTION:   sns_rh_mr_smr_external_service_register

===========================================================================*/
SMGR_STATIC void sns_rh_mr_smr_external_service_register(void)
{
  smr_err smr_err;

  sns_rh_mr.service_cookie_ext = SNS_SMGR_SVC_ID_V01;
  smr_err = smr_service_register(SNS_SMGR_SVC_get_service_object_v01(),
                                 SNS_SMR_SVC_PRI_MED,
                                 sns_rh_mr_smr_connect_cb,
                                 sns_rh_mr_smr_disconnect_cb,
                                 sns_rh_mr_smr_resume_cb,
                                 sns_rh_mr_smr_process_req_cb,
                                 &sns_rh_mr.service_cookie_ext,
                                 &sns_rh_mr.service_handle_ext);
  SNS_SMGR_PRINTF1(HIGH, "ext_svc_reg - result=%u", smr_err);
}

/*===========================================================================

  FUNCTION:   sns_rh_mr_smr_internal_service_register

===========================================================================*/
SMGR_STATIC void sns_rh_mr_smr_internal_service_register(void)
{
  smr_err err;

  sns_rh_mr.service_cookie_int = SNS_SMGR_INTERNAL_SVC_ID_V01;
  err = smr_service_register(SNS_SMGR_INTERNAL_SVC_get_service_object_v02(),
                             SNS_SMR_SVC_PRI_MED,
                             sns_rh_mr_smr_connect_cb,
                             sns_rh_mr_smr_disconnect_cb,
                             sns_rh_mr_smr_resume_cb,
                             sns_rh_mr_smr_process_req_cb,
                             &sns_rh_mr.service_cookie_int,
                             &sns_rh_mr.service_handle_int);
  SNS_SMGR_PRINTF1(HIGH, "int_svc_reg - result=%u", err);
}

/*===========================================================================

  FUNCTION:   sns_rh_mr_smr_restricted_service_register

===========================================================================*/
SMGR_STATIC void sns_rh_mr_smr_restricted_service_register(void)
{
  smr_err err;

  sns_rh_mr.service_cookie_restricted = SNS_SMGR_RESTRICTED_SVC_ID_V01;
  err = smr_service_register(SNS_SMGR_RESTRICTED_SVC_get_service_object_v01(),
                             SNS_SMR_SVC_PRI_MED,
                             sns_rh_mr_smr_connect_cb,
                             sns_rh_mr_smr_disconnect_cb,
                             sns_rh_mr_smr_resume_cb,
                             sns_rh_mr_smr_process_req_cb,
                             &sns_rh_mr.service_cookie_restricted,
                             &sns_rh_mr.service_handle_restricted);
  SNS_SMGR_PRINTF1(HIGH, "restricted_svc_reg - result=%u", err);
}

/*===========================================================================

  FUNCTION:   sns_rh_mr_send_resp

===========================================================================*/
/*!
  @brief This function fills response message header info then sends the message.

  @detail

  @param[i]  msg_header - response message header
  @param[i]  resp_ptr   - response message body

  @return  sns_err_code_e
 */
/*=========================================================================*/
sns_err_code_e sns_rh_mr_send_resp(
  const sns_rh_mr_header_s* msg_header,
  void**                     resp_ptr)
{
  smr_req_handle req_handle = msg_header->req_handle;
  smr_err err =
    smr_service_send_resp(msg_header->req_handle,
                          msg_header->msg_id,
                          *resp_ptr,
                          msg_header->body_len);
  SNS_SMGR_PRINTF4(
    HIGH, "send_resp - type=%u/0x%02x req_hndl=0x%x err=%d",
    msg_header->svc_num, msg_header->msg_id, req_handle, err);
  SNS_OS_FREE(*resp_ptr);
  *resp_ptr = NULL;
  return (err == SMR_NO_ERR) ? SNS_SUCCESS : SNS_ERR_FAILED;
}

/*===========================================================================

  FUNCTION:   sns_smgr_send_resp_w_err

===========================================================================*/
/*!
  @brief This function sends error response due to unavailable memory resource.

  @detail

  @param[i]   msg_ptr - the message
  @return  none
 */
/*=========================================================================*/
void sns_rh_mr_send_resp_w_err(sns_rh_mr_req_q_item_s* item_ptr)
{
  SNS_SMGR_PRINTF1(
    ERROR, "send_resp_w_err - dropping msg_id=0x%x", item_ptr->header.msg_id);
  SNS_OS_FREE(item_ptr);
}

/*===========================================================================

  FUNCTION:   sns_rh_mr_init

===========================================================================*/
/*!
  @brief Message Router init

  @param    none
  @return   none
 */
/*=========================================================================*/
void sns_rh_mr_init(void)
{
  uint8_t err;

  sns_rh_mr.mutex_ptr = sns_os_mutex_create(SNS_SMGR_QUE_MUTEX, &err);
  SNS_ASSERT (err == OS_ERR_NONE );

  sns_q_init(&sns_rh_mr.connection_q);
  sns_q_init(&sns_rh_mr.disconnection_q);
  sns_q_init(&sns_rh_mr.req_queue);

  sns_rh_mr_cal_init();
  sns_rh_mr_smr_external_service_register();
  sns_rh_mr_smr_internal_service_register();
  sns_rh_mr_smr_restricted_service_register();
}

/*===========================================================================

  FUNCTION:   sns_rh_mr_handle_disconnect_sig

===========================================================================*/
/*!
  @brief Handles SNS_RH_QMI_DISC_SIG signal

  @detail
  @param  none
  @return none
 */
/*=========================================================================*/
void sns_rh_mr_handle_disconnect_sig(void)
{
  while ( sns_q_cnt(&sns_rh_mr.disconnection_q) != 0 )
  {
    sns_rh_mr_connection_s* conn_ptr;

    sns_os_mutex_pend(sns_rh_mr.mutex_ptr, 0, NULL);
    conn_ptr = sns_q_get(&sns_rh_mr.disconnection_q);
    sns_os_mutex_post(sns_rh_mr.mutex_ptr);

    if ( conn_ptr != NULL )
    {
      SNS_SMGR_PRINTF3(
        MED, "disconnect_sig - conn=0x%x cli=0x%x #reqs=%u", 
        conn_ptr, conn_ptr->client_handle, sns_q_cnt(&sns_rh_mr.req_queue));

      if ( conn_ptr->service_cookie == sns_rh_mr.service_cookie_ext)
      {
        sns_rh_cancel_service(conn_ptr);
      }
      else if (conn_ptr->service_cookie == sns_rh_mr.service_cookie_int)
      {
        sns_rh_cancel_internal_service(conn_ptr);
        sns_rh_cancel_service(conn_ptr);
      }
      else if ( conn_ptr->service_cookie == sns_rh_mr.service_cookie_restricted )
      {
        sns_rh_cancel_restricted_service(conn_ptr);
      }
      else
      {
        SNS_SMGR_PRINTF1(ERROR, "disconnect_sig - unrecognized service %u", 
                         conn_ptr->service_cookie);
      }

      SNS_OS_FREE(conn_ptr);
    }
  }
}

/*===========================================================================

  FUNCTION:   sns_rh_mr_validate_connection

===========================================================================*/
/*!
  @brief Checks if the connection associated with given handle is still valid

  @param [i] conn_handle - the connection to validate

  @return true if connection is valid
 */
/*=========================================================================*/
SNS_RH_UIMAGE_CODE bool sns_rh_mr_validate_connection(const void* conn_handle)
{
  bool is_valid = false;
  if ( conn_handle != NULL )
  {
    if ( &sns_rh_mr.connection_q == 
         SMGR_QUE_HEADER_FROM_LINK(&((sns_rh_mr_connection_s*)conn_handle)->conn_q_link) )
    {
      is_valid = true;
    }
  }
  return is_valid;
}

/*===========================================================================

  FUNCTION:   sns_rh_mr_update_connection

===========================================================================*/
/*!
  @brief Updates the processor type of the connection

  @param [io] conn_handle - connection to update
  @param [i]  proc_type   - the processor in which the connection's owner resides 

  @return none
 */
/*=========================================================================*/
void sns_rh_mr_update_connection(void* conn_handle, sns_proc_type_e_v01 proc_type)
{
  sns_rh_mr_connection_s* conn_ptr = (sns_rh_mr_connection_s*)conn_handle;
  if ( conn_ptr != NULL && 
      (!conn_ptr->proc_type_is_valid  || ( proc_type != conn_ptr->proc_type )) )
  {
    SNS_SMGR_PRINTF4(
      HIGH, "update_connection - conn=0x%x cli=0x%x proc_type(was/now)=%u/%u",
      conn_ptr, conn_ptr->client_handle, conn_ptr->proc_type, proc_type);
    conn_ptr->proc_type = proc_type;
    conn_ptr->proc_type_is_valid = true;
  }
}

/*===========================================================================

  FUNCTION:   sns_rh_mr_send_indication

===========================================================================*/
/*!
  @brief This function populates message header and sends the given indication
   over the given connection

  @param[io] conn_handle - connection over which to send indication
  @param[i]  ind_msg_ptr - the indication message to send
  @param[i]  msg_id      - indication ID
  @param[i]  len         - length of the indication body
  @param[i]  free_me     - whether to free the indication memory
 
  @return   true if indication was sent or will be sent
 */
/*=========================================================================*/
SNS_RH_UIMAGE_CODE bool sns_rh_mr_send_indication(
   void*        conn_handle,
   void*        ind_msg_ptr,
   uint16_t     msg_id, 
   uint16_t     len,
   bool         free_me)
{
  smr_err err = SMR_XPORT_ERR;

  if ( sns_rh_mr_validate_connection(conn_handle) )
  {
    sns_rh_mr_connection_s* conn_ptr = (sns_rh_mr_connection_s*)conn_handle;
    err = smr_service_send_ind(conn_ptr->client_handle, 
                               msg_id, (void *)ind_msg_ptr, len);
    if ( err == SMR_CONN_BUSY_ERR )
    {
      sns_rh_mr_update_connection_state(conn_ptr, true);
    }
  }

  if ( free_me && err == SMR_NO_ERR )
  {
    SNS_OS_FREE(ind_msg_ptr);
  }
  return (err == SMR_NO_ERR) ? true : false;
}

/*===========================================================================

  FUNCTION:   sns_rh_mr_conn_busy

===========================================================================*/
/*!
  @brief This function returns the connection status

  @param[i]  conn_handle - connection over which to send indication
 
  @return   true if busy or otherwise not open
 */
/*=========================================================================*/
SNS_RH_UIMAGE_CODE bool sns_rh_mr_conn_busy(const void* conn_handle)
{
  bool busy = true;
  if ( conn_handle != NULL )
  {
    busy = ((sns_rh_mr_connection_s*)conn_handle)->is_busy;
  }
  return busy;
}

