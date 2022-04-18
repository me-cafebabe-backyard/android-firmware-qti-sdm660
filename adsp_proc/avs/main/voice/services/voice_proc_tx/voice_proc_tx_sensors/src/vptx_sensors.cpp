/*============================================================================
  FILE:          vptx_sensors.cpp

  OVERVIEW:      This file has the function definitions for sensors interface for fpro v2 algorithm.

  DEPENDENCIES:  sensors code should be present

Copyright (c) 2014-2015 Qualcomm Technologies, Inc.  All Rights Reserved.
Confidential and Proprietary - Qualcomm Technologies, Inc.
============================================================================*/

/*============================================================================
  EDIT HISTORY FOR MODULE

  $Header: //components/rel/avs.adsp/2.8/voice/services/voice_proc_tx/voice_proc_tx_sensors/src/vptx_sensors.cpp#2 $

  when       who        what, where, why
  ---------- -------    ---------------------------------------------------------
  2014-07-14 rishabht   Initial revision.
============================================================================*/

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/

#include "vptx_sensors.h"


/*
 * This call back function gets invoked in the QMI thread context as a callback routine with
 * each indication from Sensors.
 * Arguements :
 * user_handle : unique user handle for a client
 * msg_id      : msg id corresponding to holding pattern change indication by sensors
 * ind_buf     : buffer containing response from sensors for the holding pattern change
 * ind_buf_len : length of buffer containing response from sensors
*/
static void vptx_sns_indication_cb
(
   elite_qmi_client_type          user_handle,
   unsigned int                   msg_id,
   void                           *ind_buf,
   unsigned int                   ind_buf_len,
   void                           *ind_cb_data
 );

/*
 * The below call back function gets invoked in QMI thread context as a response to the request
 * placed.
 * Arguements :
 * user_handle : unique user handle for a client
 * msg_id      : msg id corresponding to registration call back by sensors
 * ind_buf     : buffer containing response from sensors for the registration request
 * ind_buf_len : length of buffer containing response from sensors
 * err         : error flag to indicate if there are any qmi transport errors
*/
static void vptx_sns_registration_cb
(
   elite_qmi_client_type          user_handle,
   unsigned int                   msg_id,
   void                           *ind_buf,
   unsigned int                   ind_buf_len,
   void                           *ind_cb_data,
   elite_qmi_client_error_type    err
 );



/*
 * Vptx thread places an asynchronous request to Sensors to start receiving Indications
 * conveying changes in holding pattern. At the time this request is placed, a pointer to
 * Vptx instance is passed as Callback data.
 * The below function gets invoked in QMI thread context as a response to the request
 * placed. This function:
 *   1. Uses the Vptx instance structure to compare the user handle received now
 *      with what was set at the time the request was placed.
 *   2. Extract session number, for debug purposes - in a read-only operation.
 *   3. Set signal (write operation), so Vptx is notified of this response.
 *   4. Request response status or Error code (write operation).
 */
static void vptx_sns_registration_cb
(
 elite_qmi_client_type          user_handle,
 unsigned int                   msg_id,
 void                           *ind_buf,
 unsigned int                   ind_buf_len,
 void                           *ind_cb_data,
 elite_qmi_client_error_type    err
 )
{
   // Check for QMI Transport errors.
   if (ELITE_QMI_NO_ERR != err)
   {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"VCP: vptx_sns_registration_cb : QMI Transport error 0x%x.", err);
      return;
   }

   // Read Qmi_obj handle.
   // If execution has reached here, it means that Vptx state is still present.
   // Had Vptx issued a qmi_client_release or a qmi_client_delete_async_txn (basically
   // retracting its requests), then this function would have returned with a transport error.
   qmi_obj_t *pQmi_obj = (qmi_obj_t*)ind_cb_data;

   MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"VCP: Vptx session # (%lx): Received response to request for SNS Indications",
         pQmi_obj->session_num);

   // Check user handle against cached Vptx handle.
   if (user_handle != pQmi_obj->user_handle)
   {
      // No course of action available.
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"VCP: Vptx session # (%lx): Message to SNS for indications failed, Handle mismatch %lu.",
            pQmi_obj->session_num);
      return;
   }

   sns_sam_facing_enable_resp_msg_v01* resp_msg = ( sns_sam_facing_enable_resp_msg_v01 *)ind_buf;
   if (SNS_RESULT_SUCCESS_V01 != resp_msg->resp.sns_result_t)
   {
      MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"VCP: vptx_sns_registration_cb : Vptx session # (%lx): QMI Response for Sensors failed with code 0x%x",
            pQmi_obj->session_num,
            resp_msg->resp.sns_err_t);
      return;
   }

   // Notify Vptx thread about registration callback.
   qurt_elite_signal_send(pQmi_obj->reg_sig);
   MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"VCP: Vptx session # (%lx): Vptx notified of registration response from Sensors.",
         pQmi_obj->session_num);
}



/*
 * This function gets invoked in the QMI thread context as a callback routine with
 * each indication from Sensors.
 */
static void vptx_sns_indication_cb
(
 elite_qmi_client_type          user_handle,
 unsigned int                   msg_id,
 void                           *ind_buf,
 unsigned int                   ind_buf_len,
 void                           *ind_cb_data
 )
{
   // Read qmi_obj handle.
   // If execution has reached here, it means that Vptx state is still present.
   // Had Vptx issued a qmi_client_release or a qmi_client_delete_async_txn (basically
   // retracting its requests), then QMI retracts all pending transactions before releasing.
   qmi_obj_t *pQmi_obj = (qmi_obj_t*)ind_cb_data;

   MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"VCP: Vptx session # (%lx): Received SNS Indications, message ID %d, forwarding to Vptx",
         pQmi_obj->session_num,
         msg_id);

   // Check user handle against cached Vptx handle.
   if (user_handle != pQmi_obj->user_handle)
   {
      // No course of action available.
      MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"VCP: vptx_sns_indication_cb : Vptx session # (%lx): SNS indications sent to wrong handle %lu, %lu.",
            pQmi_obj->session_num,
            user_handle,
            pQmi_obj->user_handle);
      return;
   }

   sns_sam_facing_report_ind_msg_v01 ind_msg;
   elite_qmi_client_error_type err;
   err = elite_qmi_client_message_decode(user_handle, ELITE_QMI_IDL_INDICATION, msg_id, ind_buf,
         ind_buf_len, &ind_msg, sizeof(ind_msg));

   // Check for QMI Decode errors.
   if (ELITE_QMI_NO_ERR != err)
   {
      MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"VCP: vptx_sns_indication_cb : Vptx session # (%lx): QMI Decode error 0x%x",
            pQmi_obj->session_num,
            err);
      return;
   }

   // Cross check instance IDs, to ensure Sensors has sent indications to the right client.
   // instance_id_valid flag is to validate whether its the right instance of service we have registered with
   if (pQmi_obj->data_resp->instance_id_valid)
   {
      if (ind_msg.instance_id != pQmi_obj->data_resp->instance_id)
      {
         // No course of action available.
         MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"VCP: vptx_sns_indication_cb : Vptx session # (%lx): SNS indications sent to wrong instance %lu, %lu.",
               pQmi_obj->session_num,
               ind_msg.instance_id,
               pQmi_obj->data_resp->instance_id);

         return;
      }
   }
/***************************************************************************************************************************/
   // Copy over the decoded message contents (basically the holding pattern).
   // this state(holding pattern) can take following values
   //typedef enum FPv2_HoldingPattern_Enum_Type
   //{
      //SNS_SAM_FACING_EVENT_E_MIN_ENUM_VAL_V01 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
      //FACING_UP_V01 = 1, /**<  Phone has just moved to a facing-up phone posture, which is defined as screen up  */
      //FACING_DOWN_V01 = 2, /**<  Phone has just moved to a facing-down phone posture, which is defined as screen down  */
      //FACING_NEUTRAL_V01 = 3, /**<  Phone has just left either the facing-up or the facing-down phone posture  */
      //SNS_SAM_FACING_EVENT_E_MAX_ENUM_VAL_V01 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
   //}FPv2_HoldingPattern_Enum_Type;
/***************************************************************************************************************************/

   pQmi_obj->holding_pattern = ind_msg.state;

   // Notify Vptx thread about indication callback.
   qurt_elite_signal_send(pQmi_obj->ind_sig);
   MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"VCP: Vptx session # (%lx): Received SNS Indications, signalled Vptx",
         pQmi_obj->session_num);
}



/*
 * The below function gets invoked in vptx init to allocate memory and  initialize :
 *   1. Registration signal pointer in vptx qmi structure(signal which will be set when call back is recieved
 *      from sensors after successful registration)
 *   2. Indication signal pointer in vptx qmi structure (signal which will be set when call back is recieved
 *      from sensors after holding pattern change)
*/
ADSPResult vptx_sns_qmi_init(void *pQmi_object, qurt_elite_channel_t  *pChannel, uint32_t qmi_reg_mask, uint32_t qmi_ind_mask, uint32_t session_num)
{
   ADSPResult nResult = ADSP_EOK;
   if(NULL == pQmi_object)
   {
      MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"VCP: vptx_sns_qmi_init : NULL qmi object pointer !!");
      return ADSP_ENOMEMORY;
   }
   qmi_obj_t *pQmi_obj = (qmi_obj_t *)pQmi_object;
   // First default init for sensors structure
   pQmi_obj->user_handle = NULL;
   pQmi_obj->data_req = NULL;
   pQmi_obj->data_resp = NULL;
   pQmi_obj->holding_pattern = FACING_UP_V01;              // initialize holding pattern with face up position
   pQmi_obj->instance_id = 0;
   pQmi_obj->session_num = session_num;


   pQmi_obj->reg_sig = (qurt_elite_signal_t*) qurt_elite_memory_malloc(sizeof(qurt_elite_signal_t), QURT_ELITE_HEAP_DEFAULT);
   pQmi_obj->ind_sig = (qurt_elite_signal_t*) qurt_elite_memory_malloc(sizeof(qurt_elite_signal_t), QURT_ELITE_HEAP_DEFAULT);

   if (NULL == pQmi_obj->reg_sig
         || NULL == pQmi_obj->ind_sig)
   {
      MSG_1(MSG_SSID_QDSP6, DBG_FATAL_PRIO,"VCP: vptx_sns_qmi_init : Failed to allocate memory for VpTx sensors Queues/Signals session(%#lx)",pQmi_obj->session_num);
      vptx_sns_qmi_destroy(pQmi_obj);
      return ADSP_ENOMEMORY;
   }

   if( ADSP_FAILED(nResult = qurt_elite_signal_init(pQmi_obj->reg_sig))
         || ADSP_FAILED(nResult = qurt_elite_signal_init(pQmi_obj->ind_sig))
         || ADSP_FAILED(nResult = qurt_elite_channel_add_signal(pChannel, (pQmi_obj->reg_sig), qmi_reg_mask))
         || ADSP_FAILED(nResult = qurt_elite_channel_add_signal(pChannel, (pQmi_obj->ind_sig), qmi_ind_mask))

     )
   {
      MSG_1(MSG_SSID_QDSP6, DBG_FATAL_PRIO,"VCP: vptx_sns_qmi_init : Failed create Vptx sensors MsgQs !! session(%lx)",pQmi_obj->session_num);
      vptx_sns_qmi_destroy(pQmi_obj);
      return nResult;
   }

   MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"VCP: vptx QMI signals memalloc/Initialization Done !!");

   return nResult;
}



/*
 * The below function gets invoked in vptx run cmnd to place request to QMI for registration
 * this function will:
 *   1. Get the service object to communicate with sensors code
 *   2. Check if qmi service is up, and get the list of services
 *   3. qmi client initialization
 *   4. place asynchronous message to request for indications from Facing Service
*/
ADSPResult vptx_sns_qmi_register(void *pQmi_object, int32_t facing_angle_threshold)
{

#if defined(__qdsp6__) && !defined(SIM)

   if(NULL == pQmi_object)
   {
      MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"VCP: vptx_sns_qmi_register : NULL qmi object pointer !!");
      return ADSP_ENOMEMORY;
   }
   qmi_obj_t *pQmi_obj = (qmi_obj_t *)pQmi_object;
   /*------------------------------------------------------------*/
   /* QMI interfacing */
   /*------------------------------------------------------------*/
   elite_qmi_client_error_type   retval;
   elite_qmi_service_info        info;
   elite_qmi_service_info        svc_under_use_info;
   unsigned int                  num_services = 0;
   unsigned int                  num_entries = 1;  // Accepting only 1 service.

   /*-----------------------------------------------------------------------
   Get Sensor service object
    -----------------------------------------------------------------------*/
   elite_qmi_idl_service_object_type sensor_svc_obj = SNS_SAM_FACING_SVC_get_service_object_v01();
   if(!sensor_svc_obj)
   {
      MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"VCP: Vptx session # (%lx): Unable to get Sensor service object", pQmi_obj->session_num);
      vptx_sns_qmi_deregister(pQmi_obj);
      return ADSP_EFAILED;
   }


   MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"VCP: Vptx session # (%lx): Found Sensor service object", pQmi_obj->session_num);

   /*------------------------------------------------------------------
   Check if the Sensor  service is up, if not return. Else,
   Get addressing information for accessing wds service
   Currently getting entire service list, but this can be replaced to
   just talk to the first responder (quickest sensor service to respond).
   ------------------------------------------------------------------*/
   retval = elite_qmi_client_get_service_list (sensor_svc_obj,
               &info,
               &num_entries,
               &num_services);

   if(ELITE_QMI_NO_ERR != retval || 1 != num_services)             // TODO : check if this is valid or it should be > 0
   {
      MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"VCP: vptx_sns_qmi_register : Vptx session # (%lx): Get Sensor service list error %d, num_services =%u", pQmi_obj->session_num, retval, num_entries);
      vptx_sns_qmi_deregister(pQmi_obj);
      return ADSP_EFAILED;
   }

   MSG_3(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"VCP: Vptx session # (%lx): Sensor service UP num_entries = %u, num_services = %u", pQmi_obj->session_num, num_entries, num_services);

   svc_under_use_info = info;

   retval = elite_qmi_client_init (&svc_under_use_info,
               sensor_svc_obj,
               &vptx_sns_indication_cb,
               (void *)pQmi_obj,
               NULL,
               &pQmi_obj->user_handle);
   if(ELITE_QMI_NO_ERR != retval)
   {
      MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"VCP: vptx_sns_qmi_register : Vptx session # (%lx): Sensor client init failed with error %d", pQmi_obj->session_num, retval);
      vptx_sns_qmi_deregister(pQmi_obj);
      return ADSP_EFAILED;
   }

   MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"VCP: Vptx session # (%lx): Sensor client init succeeded...", pQmi_obj->session_num);

   /* Prepare and send the request */
   pQmi_obj->data_req = (sns_sam_facing_enable_req_msg_v01*)
   qurt_elite_memory_malloc(sizeof(sns_sam_facing_enable_req_msg_v01), QURT_ELITE_HEAP_DEFAULT);
   pQmi_obj->data_resp = (sns_sam_facing_enable_resp_msg_v01*)
   qurt_elite_memory_malloc(sizeof(sns_sam_facing_enable_resp_msg_v01), QURT_ELITE_HEAP_DEFAULT);

   if ((NULL == pQmi_obj->data_req) || (NULL == pQmi_obj->data_resp))
   {
      MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"VCP: vptx_sns_qmi_register : Vptx session # (%lx): Sensor messaging allocation failed...", pQmi_obj->session_num);
      vptx_sns_qmi_deregister(pQmi_obj);
      return ADSP_ENOMEMORY;
   }

   memset( pQmi_obj->data_req, 0, sizeof(sns_sam_facing_enable_req_msg_v01) );
   memset( pQmi_obj->data_resp, 0, sizeof(sns_sam_facing_enable_resp_msg_v01) );

   /* Configure conditions upon which callback routine will be invoked */
   pQmi_obj->data_req->report_period = 0;
   pQmi_obj->data_req->report_neutral_valid = TRUE;
   pQmi_obj->data_req->report_neutral = TRUE;
   pQmi_obj->data_req->facing_angle_threshold_valid = TRUE;
   pQmi_obj->data_req->facing_angle_threshold = facing_angle_threshold;


   MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"VCP: Vptx session # (%lx): Placing async request for sensors indications with threshold angle (%d)", pQmi_obj->session_num,(int32_t)pQmi_obj->data_req->facing_angle_threshold);

   // Send asynchronous message to request for indications from Facing Service.
   // Use Vptx instance structure pointer as callback data.
   retval = elite_qmi_client_send_msg_async (pQmi_obj->user_handle,
               SNS_SAM_FACING_ENABLE_REQ_V01,
               pQmi_obj->data_req,
               sizeof(sns_sam_facing_enable_req_msg_v01),
               pQmi_obj->data_resp,
               sizeof(sns_sam_facing_enable_resp_msg_v01),
               vptx_sns_registration_cb,
               (void *)pQmi_obj,
               NULL);
   if(ELITE_QMI_NO_ERR != retval)
   {
      MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"VCP: vptx_sns_qmi_register : Vptx session # (%lx): Async messaging to Sensors failed with error %d", pQmi_obj->session_num, retval);
      vptx_sns_qmi_deregister(pQmi_obj);
      return ADSP_EFAILED;
   }

   MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"VCP: vptx QMI sensors registration request Done !!");
#endif
   return ADSP_EOK;

}


/*
 * The below function gets invoked in vptx end to free memory allocated for :
 *   1. Registration signal pointer in vptx qmi structure(signal set when call back is recieved
 *      from sensors after successful registration)
 *   2. Indication signal pointer in vptx qmi structure (signal set when call back is recieved
 *      from sensors after holding pattern change)
*/
void vptx_sns_qmi_destroy(void *pQmi_object)
{
   if(NULL == pQmi_object)
   {
      MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"VCP: vptx_sns_qmi_destroy : NULL qmi object pointer !!");
      return;
   }
   qmi_obj_t *pQmi_obj = (qmi_obj_t *)pQmi_object;


   // It can now be assumed that there are no more QMI callback
   // activities pending that will write to Vptx memory. We can
   // clean up all associated memory.
   // call utility function to deinitialize and destroy all signals
   if (NULL != pQmi_obj->reg_sig)
   {
      qurt_elite_signal_deinit(pQmi_obj->reg_sig);
      qurt_elite_memory_free(pQmi_obj->reg_sig);
      pQmi_obj->reg_sig = NULL;
   }
   if (NULL != pQmi_obj->ind_sig)
   {
      qurt_elite_signal_deinit(pQmi_obj->ind_sig);
      qurt_elite_memory_free(pQmi_obj->ind_sig);
      pQmi_obj->ind_sig = NULL;
   }

   return;
}


/*
 * The below function gets invoked in vptx stop cmnd to deregister from  QMI
 * this function will:
 *   1. set registration flag to FALSE
 *   2. release the client (deregister from qmi)
 *   3. free memory allocated for response and request queues
*/
void vptx_sns_qmi_deregister(void *pQmi_object)
{
#if defined(__qdsp6__) && !defined(SIM)

      if(NULL == pQmi_object)
      {
         MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"VCP: vptx_sns_qmi_deregister : NULL qmi object pointer !!");
         return;
      }
      qmi_obj_t *pQmi_obj = (qmi_obj_t *)pQmi_object;

      // First place Blocking call that will delete all the currently
      // placed requests from Vptx client.

      MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"VCP: vptx deregistering from QMI : user handle (%lu) !!",(uint32_t)pQmi_obj->user_handle);
      if(NULL != pQmi_obj->user_handle)
      {
         elite_qmi_client_release(pQmi_obj->user_handle);
         pQmi_obj->user_handle = NULL;
      }
      MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"VCP: vptx deregistration done from QMI !!");
      //  clean req and resp buffers as well as they are allocated during register
      if (NULL != pQmi_obj->data_req)
      {
         qurt_elite_memory_free(pQmi_obj->data_req);
         pQmi_obj->data_req = NULL;
      }
      if (NULL != pQmi_obj->data_resp)
      {
         qurt_elite_memory_free(pQmi_obj->data_resp);
         pQmi_obj->data_resp = NULL;
      }

#endif
      return;
}

/*
 * The below function gets invoked in vptx init  to get the size of
 * qmi structure
*/
uint32_t vptx_sns_qmi_get_mem_req(void)
{
   return sizeof(qmi_obj_t);
}


/*
 * The below function gets invoked whenever holding pattern
 * information is required by framework.
 * It will return the current holding pattern value.
*/
int32_t  vptx_sns_get_holding_pattern(void *pQmi_object)
{
   if(NULL == pQmi_object)
   {
      MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"VCP: vptx_sns_get_holding_pattern : NULL qmi object pointer !!");
      return 1;
   }
   qmi_obj_t *pQmi_obj = (qmi_obj_t *)pQmi_object;

   return (int32_t)pQmi_obj->holding_pattern;
}


/*
 * The below function will clear the registration and indication signals
*/
void vptx_sns_clear_qmi_signal(void *pQmi_object, reg_ind_signal_t sig_flag)
{
   if(NULL == pQmi_object)
   {
      MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"VCP: vptx_sns_clear_qmi_signal : NULL qmi object pointer !!");
      return;
   }
   qmi_obj_t *pQmi_obj = (qmi_obj_t *)pQmi_object;

   if(REG_SIG == sig_flag)
   {
      qurt_elite_signal_clear(pQmi_obj->reg_sig);
   }
   else
   {
      qurt_elite_signal_clear(pQmi_obj->ind_sig);
   }
   return;
}