/*=============================================================================
  @file sns_rh_mr_cal.c

  This file implements the Message Router module of Request Handler task.

*******************************************************************************
* Copyright (c) 016 Qualcomm Technologies, Inc.
* All Rights Reserved.
* Confidential and Proprietary - Qualcomm Technologies, Inc.
********************************************************************************/
/*============================================================================
  EDIT HISTORY FOR FILE

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------
  2016-11-01  np   Added memory leak fix on request handling .
  2016-10-12  np   Added playback sample loss fix for qmag cal .
  2016-08-10  np   Added playback support.  
  2016-07-05  np   SMR interface for calibration service.

============================================================================*/
/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "sns_sam_qmag_cal_v01.h"
#include "sns_sam_gyro_cal_v01.h"
#include "sns_rh_mr_cal.h"
#include "sns_memmgr.h"
#include "sns_rh.h"
#include "sns_rh_cal.h"
#include "sns_rh_util.h"
#include "qmi_err_codes.h"
#ifdef FAST_PLAYBACK
#include "playback.h"
#endif
/*----------------------------------------------------------------------------
 *  Variables
 * -------------------------------------------------------------------------*/
sns_rh_mr_c   sns_rh_mr_cal_client;


/*----------------------------------------------------------------------------
 * Macro
 * -------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
 * Function Declarations and Documentation
 * -------------------------------------------------------------------------*/

/*===========================================================================

  FUNCTION:   sns_rh_mr_cal_init

===========================================================================*/
/*!
  @brief    This function initializes OS structures for SAM message handling.


  @param[]  void

  @return   none
 */
/*=========================================================================*/
void sns_rh_mr_cal_init(void)
{
  smr_err err;
  sns_rh_mr_cal_client.mutex_ptr = sns_os_mutex_create(SNS_SMGR_QUE_MUTEX, &err);
  SNS_ASSERT (err == OS_ERR_NONE );
  sns_q_init( &sns_rh_mr_cal_client.sam_q );
}

 /*=============================================================================
   FUNCTION sns_rh_mr_cal_put_q_msg
 =============================================================================*/
 /*!
 @brief
   This puts the SAM/REG QMI messages into Queue and posts the signal

 @param[in]  client_hndl                    connection handle to
                                           differentiate the clients
 @param[in]  msg_id                        Message ID of the indication
 @param[in]  svc_id                        Service Id.
 @param[in]  buffer                        Buffer holding the data
 @param[in]  sns_rh_cal_msg_type           Message type(SAM/REG)
 @param[in]  transp_err                    QMI error .
 @param[in]  buf_len                       Length of buffer holding the data .
 @param[in]  decode_msg_len                Length of data to fetch.

 @return     None

 */
 /*=========================================================================*/
SMGR_STATIC void sns_rh_mr_cal_put_q_msg(
  smr_client_hndl                         client_hndl,
  unsigned int                            msg_id,
  uint8_t                                 sensor_id,
  void                                    *buffer,
  sns_rh_msg_type_e                       sns_rh_cal_msg_type,
  qmi_client_error_type                   transp_err,
  int32                                   buf_len,
  int32                                   decode_msg_len)
{
  uint8_t               os_err = 0;
  sns_rh_cal_q_item_s   *rh_cal_q_ptr = NULL;
  void                  *decode_buf_ptr = NULL;
  void                  *rh_msg_buf_ptr = NULL;

  if ( buffer == NULL )
  {
    SNS_SMGR_PRINTF2(ERROR, "Null Buffer, sns_rh_cal_msg_type = %d, msg_id = %d",
        sns_rh_cal_msg_type, msg_id);

    return;
  }
  if ( transp_err != QMI_NO_ERR )
  {
    SNS_OS_FREE(buffer);

    SNS_SMGR_PRINTF3(ERROR,
        "Transportation Error = %d, sns_rh_cal_msg_type = %d, msg_id = %d",
        transp_err, sns_rh_cal_msg_type, msg_id);
    return;
  }


  switch ( sns_rh_cal_msg_type )
  {
    case RH_SAM_RESP_MSG:
      rh_msg_buf_ptr = buffer;
      break;

    case RH_SAM_IND_MSG:
      decode_buf_ptr = SNS_OS_MALLOC (SNS_DBG_MOD_DSPS_SMR, decode_msg_len);
      if( decode_buf_ptr !=NULL )
      {
        SNS_OS_MEMSCPY( decode_buf_ptr,decode_msg_len,buffer,decode_msg_len);
        rh_msg_buf_ptr = decode_buf_ptr;
      }
      else
        SNS_SMGR_PRINTF0(ERROR,"decode_buf_ptr error");
      break;
    default:
      SNS_SMGR_PRINTF1(ERROR, "Invalid sns_rh_cal_msg_type = %d", sns_rh_cal_msg_type);
      return;
  }
  if ( rh_msg_buf_ptr == NULL )
  {
    SNS_SMGR_PRINTF1(ERROR, "rh_msg_buf_ptr should not be NULL",
        sizeof(sns_rh_cal_q_item_s));

    return;
  }


  rh_cal_q_ptr = (sns_rh_cal_q_item_s *)
                                  SNS_OS_MALLOC (SNS_DBG_MOD_DSPS_SMR, sizeof(sns_rh_cal_q_item_s));
  if ( rh_cal_q_ptr == NULL )
  {
    SNS_OS_FREE(rh_msg_buf_ptr);

    SNS_SMGR_PRINTF1(ERROR, "Malloc Fail for requested size = %d",
        sizeof(sns_rh_cal_q_item_s));

    return;
  }

  rh_cal_q_ptr->msg_id = msg_id;
  rh_cal_q_ptr->body_ptr = rh_msg_buf_ptr;
  rh_cal_q_ptr->rh_msg_type = sns_rh_cal_msg_type;
  rh_cal_q_ptr->sensor_id = sensor_id;
  sns_q_link(rh_cal_q_ptr, &rh_cal_q_ptr->q_link);

  sns_os_mutex_pend(sns_rh_mr_cal_client.mutex_ptr, 0, &os_err);
  if ( os_err != OS_ERR_NONE )
  {
    SNS_OS_FREE(rh_cal_q_ptr->body_ptr);
    SNS_OS_FREE(rh_cal_q_ptr);

    SNS_SMGR_PRINTF1(ERROR, "Error acquiring mutex = %d", os_err);

    return ;
  }

  sns_q_put(&(sns_rh_mr_cal_client.sam_q), &rh_cal_q_ptr->q_link);

  os_err = sns_os_mutex_post(sns_rh_mr_cal_client.mutex_ptr);
  SNS_ASSERT( os_err == OS_ERR_NONE );

  sns_rh_signal_me(SNS_RH_SAM_MSG_SIG);
}

 /*=========================================================================
   FUNCTION:  sns_rh_mr_cal_resp_cb
   =========================================================================*/
 /*!
   @brief RH - SAM response callback

   @detail     Handles the responses from SAM to RH for enable/disable/update.

   @param[i]   user_handle         Handle used by the
                                   infrastructure to identify
                                   different clients.
   @param[i]   msg_id              Message ID
   @param[i]   resp_buf            Pointer to the response buffer
   @param[i]   resp_buf_len        Length of the response buffer
   @param[i]   user_cb_data        Pointer to the User-data
   @param[i]   transp_err          Error code

     @return None
 */
 /*=======================================================================*/
SMGR_STATIC void sns_rh_mr_cal_resp_cb (
  smr_client_hndl                        user_handle,
  unsigned int                           msg_id,
  void                                   *resp_buf,
  unsigned int                           resp_buf_len,
  void                                   *user_cb_data,
  smr_err                                transp_err)
{
  if( transp_err != SMR_NO_ERR )
  {
    SNS_SMGR_PRINTF0(ERROR,"sns_rh_mr_cal_resp_cb error");
  }
  uint8_t  * sensorId = (uint8_t *)user_cb_data;

  sns_rh_mr_cal_put_q_msg(user_handle,
                          msg_id,
                          *sensorId,
                          resp_buf,
                          RH_SAM_RESP_MSG,
                          QMI_NO_ERR, 0, 0);
#ifdef FAST_PLAYBACK
  uint8_t errOS;
  sns_os_sigs_post( playback_sig_event,
      FPB_CAL_ENABLE_SIG, OS_FLAG_SET, &errOS );
#endif
  SNS_OS_FREE( (void*)user_cb_data );

}

 /*=========================================================================
   FUNCTION:  sns_rh_mr_cal_rels_cb
   =========================================================================*/
 /*!
   @brief RH - SAM Release callback

   @detail     Handles the responses from SAM to RH for release.
               Makes the client handle NULL.

   @param[i]   user_cb_data        Call back data ( SMR client handle).
   @return     None
 */
 /*=======================================================================*/
SMGR_STATIC void sns_rh_mr_cal_rels_cb (void *user_cb_data)
{
  SNS_SMGR_PRINTF0(HIGH, "SCal release cb" );
  if( user_cb_data )
  {
     *((smr_client_hndl*)user_cb_data) = NULL;
     SNS_OS_FREE( (void*)user_cb_data );
  }
}

 /*===========================================================================

   FUNCTION:   sns_rh_mr_send_cal_enable_req

 ===========================================================================
   @brief This function fills response message header info then sends the message.
   @detail
   @param[i]  smr_hndl      Client handle.
   @param[i]  msg_id        Message to send.
   @param[i]  sensor_id     Sensor id .
   @return  sns_err_code_e
 =========================================================================*/
sns_err_code_e sns_rh_mr_cal_send_enable_req(
  smr_client_hndl                            smr_hndl,
  uint8_t                                    msg_id,
  uint8_t                                    sensor_id,
  uint8_t                                    cal_phone_mode)
{
  smr_txn_handle txn_handle;
  sns_sam_cal_enable_req_msg_v01  cal_enable_req;
  sns_sam_cal_enable_resp_msg_v01 *cal_enable_resp;
  uint8_t *cb_data = (uint8_t *) SNS_OS_MALLOC(SNS_DBG_MOD_DSPS_SMR, sizeof(uint8_t));
  SNS_ASSERT(cb_data != NULL);
  *cb_data = sensor_id;

  cal_enable_req.phone_mode_valid = true;
  cal_enable_req.phone_mode = cal_phone_mode;

  cal_enable_resp = (sns_sam_cal_enable_resp_msg_v01 *)
                  SNS_OS_MALLOC(SNS_DBG_MOD_DSPS_SMR, sizeof(sns_sam_cal_enable_resp_msg_v01));
  SNS_ASSERT(cal_enable_resp != NULL);

  SNS_SMGR_PRINTF1(MED, "enable cal algo with phone mode %d!", cal_enable_req.phone_mode );

  smr_err err = smr_client_send_req( smr_hndl,
                                     msg_id,
                                     &cal_enable_req,
                                     sizeof(sns_sam_cal_enable_req_msg_v01),
                                     cal_enable_resp,
                                     sizeof(sns_sam_cal_enable_resp_msg_v01),
                                     sns_rh_mr_cal_resp_cb,
                                     (void *)cb_data,
                                     &txn_handle );
  if( err != SMR_NO_ERR )
  {
    SNS_SMGR_PRINTF1(ERROR, "smr_client_init error %d", err );
    if( cal_enable_resp )
    {
      SNS_OS_FREE(cal_enable_resp);
      cal_enable_resp = NULL;
    }
    SNS_OS_FREE(cb_data);
    smr_client_release( smr_hndl,
        sns_rh_mr_cal_rels_cb, smr_hndl );

  }

  return (err == SMR_NO_ERR) ? SNS_SUCCESS : SNS_ERR_FAILED;
}
 /*===========================================================================

   FUNCTION:   sns_rh_mr_cal_send_update_req

 ===========================================================================
   @brief This function fills response message header info then sends the message.
   @detail
   @param[i]  smr_hndl      Client handle.
   @param[i]  msg_id        Message to send.
   @param[i]  inst_id       Instance id in the disable.
   @param[i]  sensor_id     Sensor id.
   @return    sns_err_code_e
 =========================================================================*/
sns_err_code_e sns_rh_mr_cal_send_update_req(
  smr_client_hndl                             smr_hndl,
  uint8_t                                     msg_id,
  int32_t                                     inst_id,
  uint8_t                                     sensor_id,
  sns_sam_cal_update_type_e_v01               update_type)
{
  smr_txn_handle txn_handle;
  sns_sam_cal_update_req_msg_v01  cal_update_req;
  sns_sam_cal_update_resp_msg_v01 *cal_update_resp;
  uint8_t *cb_data = (uint8_t *) SNS_OS_MALLOC(SNS_DBG_MOD_DSPS_SMR, sizeof(uint8_t));
  SNS_ASSERT(cb_data != NULL);
  *cb_data = sensor_id;


  cal_update_resp = (sns_sam_cal_update_resp_msg_v01 *)
                  SNS_OS_MALLOC(SNS_DBG_MOD_DSPS_SMR, sizeof(sns_sam_cal_update_resp_msg_v01));
  SNS_ASSERT( cal_update_resp != NULL );
  cal_update_req.instance_id = inst_id;
  cal_update_req.update_type=update_type;
  smr_err err = smr_client_send_req( smr_hndl,
                                     msg_id,
                                     &cal_update_req,
                                     sizeof(sns_sam_cal_update_req_msg_v01),
                                     cal_update_resp,
                                     sizeof(sns_sam_cal_update_resp_msg_v01),
                                     sns_rh_mr_cal_resp_cb,
                                     (void *)cb_data,
                                     &txn_handle );
  if( err != SMR_NO_ERR )
  {
    SNS_SMGR_PRINTF1(ERROR, "SSM: smr_client_init error %d", err );
    if( cal_update_resp )
    {
      SNS_OS_FREE(cal_update_resp);
      cal_update_resp = NULL;
    }
    SNS_OS_FREE( cb_data );
    smr_client_release( smr_hndl,
        sns_rh_mr_cal_rels_cb, smr_hndl );

  }

  return (err == SMR_NO_ERR) ? SNS_SUCCESS : SNS_ERR_FAILED;
}

 /*===========================================================================

   FUNCTION:   sns_rh_mr_cal_send_disable_req

 ===========================================================================*/
 /*!
   @brief     This function sends a disable request to the cal algo on SAM.

   @detail

   @param[i]  smr_hndl    Client handle.
   @param[i]  msg_id       Message to send.
   @param[i]  inst_id      Instance id in the disable.
   @param[i]  sensor_id    Sensor Id.

   @return  sns_err_code_e
  */
 /*=========================================================================*/
sns_err_code_e sns_rh_mr_cal_send_disable_req(
  smr_client_hndl                              smr_hndl,
  uint8_t                                      msg_id,
  int32_t                                      inst_id,
  uint8_t                                      sensor_id)
{
  sns_sam_cal_disable_req_msg_v01  cal_disable_req;
  sns_sam_cal_disable_resp_msg_v01 *cal_disable_resp;
  smr_txn_handle txn_handle;
  uint8_t *cb_data = (uint8_t *) SNS_OS_MALLOC(SNS_DBG_MOD_DSPS_SMR, sizeof(uint8_t));
  SNS_ASSERT(cb_data != NULL);
  *cb_data = sensor_id;

  cal_disable_resp = (sns_sam_cal_disable_resp_msg_v01 *)
                  SNS_OS_MALLOC(SNS_DBG_MOD_DSPS_SMR, sizeof(sns_sam_cal_disable_resp_msg_v01));
  SNS_ASSERT(cal_disable_resp != NULL);


  cal_disable_req.instance_id = inst_id;
  smr_err err = smr_client_send_req( smr_hndl,
                                     msg_id,
                                     &cal_disable_req,
                                     sizeof(sns_sam_cal_disable_req_msg_v01),
                                     cal_disable_resp,
                                     sizeof(sns_sam_cal_disable_resp_msg_v01),
                                     sns_rh_mr_cal_resp_cb,
                                     cb_data,
                                     &txn_handle );
  if( err != SMR_NO_ERR )
  {
    SNS_SMGR_PRINTF1(ERROR, "RH: smr_client_init error %d", err );
    if( cal_disable_resp )
    {
      SNS_OS_FREE(cal_disable_resp);
      cal_disable_resp=NULL;
    }

    SNS_OS_FREE(cb_data);
    smr_client_release( smr_hndl,
        sns_rh_mr_cal_rels_cb, smr_hndl );

  }

  return (err == SMR_NO_ERR) ? SNS_SUCCESS : SNS_ERR_FAILED;
}


/*===========================================================================

 FUNCTION:   sns_rh_mr_cal_client_ind_cb

=============================================================================
 @brief      SAM cal services indication callback.

 @param[i]   client_hndl  Service handle.
 @param[i]   msg_id       The message type.
 @param[i]   ind_buf      The data buffer.
 @param[i]   ind_buf_len   Data buffer length.
 @param[i]   ind_cb_data   The call back data requested from SMR.

 @return   none
=========================================================================*/

SMGR_STATIC void sns_rh_mr_cal_client_ind_cb(
  smr_client_hndl                             client_hndl,
  unsigned int                                msg_id,
  void                                        *ind_buf,
  unsigned int                                ind_buf_len,
  void                                        *ind_cb_data )
{
  uint8_t  * sensor_id =NULL;
  sensor_id= ind_cb_data;
  int32  decode_msg_len = sizeof(sns_sam_cal_report_ind_msg_v01);

  sns_rh_mr_cal_put_q_msg(client_hndl,
                          msg_id,*sensor_id,
                          ind_buf, RH_SAM_IND_MSG,
                          QMI_NO_ERR, ind_buf_len,
                          decode_msg_len);
}

/*===========================================================================

  FUNCTION:   sns_rh_mr_cal_client_error_cb

=============================================================================
  @brief      Error callback for registry and SAM from SMR.

  @param[i]   client_hndl  Service handle.
  @param[i]   error       The SMR error.
  @param[i]   err_cb_data   The call back data requested from SMR.

  @return   none
=========================================================================*/

SMGR_STATIC void sns_rh_mr_cal_client_error_cb(
  smr_client_hndl                               client_hndl,
  smr_err                                       error,
  void                                          *err_cb_data )
{
  SNS_SMGR_PRINTF1(ERROR, "RH: sns_rh_mr_client_error_cb error %d", error );
  if( err_cb_data )
    SNS_OS_FREE(err_cb_data);
}


/*===========================================================================

  FUNCTION:   sns_rh_mr_cal_client_init

=============================================================================
  @brief      Initializes SAM cal algo handles.

  @param[i]   service_obj  Service object.
  @param[i]   index        Index to the cal algo in local map.
  @param[i]   sensor_id    SMGR sensor ID.

  @return   none
=========================================================================*/

SMGR_STATIC void sns_rh_mr_cal_client_init(
  qmi_idl_service_object_type       service_obj,
  uint8_t                           index,
  uint8_t                           sensor_id)
{
  SNS_SMGR_PRINTF0(LOW, "sns_rh_mr_client_init");
  smr_err err;
  uint8_t *cb_data = (uint8_t *) SNS_OS_MALLOC(SNS_DBG_MOD_DSPS_SMR, sizeof(uint8_t));
  SNS_ASSERT(cb_data != NULL);
  *cb_data = sensor_id;

  if( sns_rh_mr_cal_client.client_hndl[index] == NULL )
  {
    err = smr_client_init( service_obj,
                           SMR_CLIENT_INSTANCE_ANY,
                           sns_rh_mr_cal_client_ind_cb,
                           (void *)cb_data,
                           SNS_RH_MR_INIT_CLIENT_TIMEOUT_US,
                           sns_rh_mr_cal_client_error_cb,
                           (void *)cb_data,
                            &sns_rh_mr_cal_client.client_hndl[index],
                            true );
    if( SMR_NO_ERR != err )
    {
      SNS_SMGR_PRINTF1(ERROR, "RH: sns_rh_mr_client_init error %d", err );

      smr_client_release( sns_rh_mr_cal_client.client_hndl[index],
                          sns_rh_mr_cal_rels_cb,
                          &sns_rh_mr_cal_client.client_hndl[index] );

    }
  }
}
/*=========================================================================
 FUNCTION:  sns_rh_mr_cal_sam_client_check_cb
 =========================================================================*/
/**
* @brief
* This callback function is called by the SMR infrastructure when a service
* becomes available, or if the client-specified timeout passes.
*
* @param[i] service_obj QMI service object
* @param[i] instance_id Instance ID of the service found
* @param[i] timeout_exp Whether the timeout expired
*/
/*=======================================================================*/

SMGR_STATIC void sns_rh_mr_cal_sam_client_check_cb(
  qmi_idl_service_object_type                       service_obj,
  qmi_service_instance                              instance_id,
  bool                                              timeout_exp )
{
  int32_t errQMI = QMI_IDL_LIB_NO_ERR;
  uint32_t service_id = 0;
  smgr_sensor_id_e sensorId;
  uint8_t index;
  errQMI = qmi_idl_get_service_id( service_obj, &service_id );
  if( QMI_IDL_LIB_NO_ERR != errQMI )
  {
    SNS_SMGR_PRINTF1( ERROR, "Service ID check failed %i",
        service_id );
  }
  if( timeout_exp )
  {
    SNS_SMGR_PRINTF1( ERROR, "sns_rh_mr_client_check_cb time out svc_id %d", service_id );
    return;
  }

  sns_rh_cal_get_sensor_id(service_obj,&sensorId,&index);
  sns_rh_mr_cal_client_init(service_obj,index,sensorId);
#ifdef FAST_PLAYBACK
  uint8_t errOS;
   sns_os_sigs_post( playback_cal_sig_event, (OS_FLAGS) FPB_CAL_CONNECT_SIG,
       OS_FLAG_SET, &errOS );
#endif
}

/*=========================================================================
 FUNCTION:  sns_rh_mr_cal_smr_client_check
 =========================================================================*/
/*!
 * @brief
 * This callback function is called by the SMR infrastructure when a service
 * becomes available, or if the client-specified timeout passes.

 @param[i] service_obj  QMI service object
 @param[i] timeout      Time out


 @return Sensors error code
*/
/*=======================================================================*/
smr_err sns_rh_mr_cal_smr_client_check(
  qmi_idl_service_object_type            service_obj,
  uint32_t                               timeout)

{
  UNREFERENCED_PARAMETER(service_obj);
  UNREFERENCED_PARAMETER(timeout);

  smr_err err;
  err = smr_client_check( service_obj,
                          SMR_CLIENT_INSTANCE_ANY,
                          timeout,
                          sns_rh_mr_cal_sam_client_check_cb );
  return err;
}
