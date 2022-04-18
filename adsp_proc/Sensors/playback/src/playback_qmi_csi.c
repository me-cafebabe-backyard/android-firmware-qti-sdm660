#include "qmi_csi.h"
#include "sns_usmr_priv.h"

/*=============================================================================
  Override QMI CSI Macros
=============================================================================*/
#ifdef QMI_CSI_OPTIONS_INIT
  #undef QMI_CSI_OPTIONS_INIT
#endif
#define QMI_CSI_OPTIONS_INIT(opt)

#ifdef QMI_CSI_OPTIONS_SET_INSTANCE_ID
  #undef QMI_CSI_OPTIONS_SET_INSTANCE_ID
#endif
#define QMI_CSI_OPTIONS_SET_INSTANCE_ID(opt, inst)

#ifdef QMI_CSI_OPTIONS_SET_MAX_OUTSTANDING_INDS
  #undef QMI_CSI_OPTIONS_SET_MAX_OUTSTANDING_INDS
#endif
#define QMI_CSI_OPTIONS_SET_MAX_OUTSTANDING_INDS(opt, _max_outstanding_inds)

#ifdef QMI_CSI_OPTIONS_SET_SCOPE
  #undef QMI_CSI_OPTIONS_SET_SCOPE
#endif
#define QMI_CSI_OPTIONS_SET_SCOPE(opt, _scope)

#ifdef QMI_CSI_OPTIONS_SET_RAW_REQUEST_CB
  #undef QMI_CSI_OPTIONS_SET_RAW_REQUEST_CB
#endif
#define QMI_CSI_OPTIONS_SET_RAW_REQUEST_CB(opt, _raw_req)

#ifdef QMI_CSI_OPTIONS_SET_PRE_REQUEST_CB
  #undef QMI_CSI_OPTIONS_SET_PRE_REQUEST_CB
#endif
#define QMI_CSI_OPTIONS_SET_PRE_REQUEST_CB(opt, _pre_req)

#ifdef QMI_CSI_OPTIONS_SET_RESUME_IND_CB
  #undef QMI_CSI_OPTIONS_SET_RESUME_IND_CB
#endif
#define QMI_CSI_OPTIONS_SET_RESUME_IND_CB(opt, _resume_cb_)

/* Queue holding service_check_cb_data. Since Offline Playback does not have
 * access to QMI, it needs to mimic the behavior of the QMI client notifier
 * call flow. */
STATIC sns_smr_protected_q_s smr_client_check_cb_data_q;

/*=============================================================================
  FUNCTION  qmi_csi_register
=============================================================================*/
/*!
@brief
  Register a service with the QCSI infrastructure.

@param[in]  service_obj         Object containing meta information to
                                encode/decode the messages.
@param[in]  service_connect     Callback to register each client with the
                                service.
@param[in]  service_disconnect  Callback to unregister each client from
                                service.
@param[in]  service_process_req Callback that handles the incoming requests.
@param[in]  service_cookie      User data.
@param[out] service_provider    Handle that infra provides to represent this
                                service connection.
@retval    QMI_CSI_NO_ERR       Success
@retval    QMI_CSI_.....        Look into the enumeration qmi_csi_error for
                                the error values.
*/
/*=========================================================================*/

qmi_csi_error
qmi_csi_register
(
 qmi_idl_service_object_type               service_obj,
 qmi_csi_connect                           service_connect,
 qmi_csi_disconnect                        service_disconnect,
 qmi_csi_process_req                       service_process_req,
 void                                      *service_cookie,
 qmi_csi_os_params                         *os_params,
 qmi_csi_service_handle                    *service_provider
 )
{
  // Offline Playback Stub
  return QMI_CSI_INTERNAL_ERR;
}

/*=============================================================================
  FUNCTION  qmi_csi_register_with_options
=============================================================================*/
/*!
@brief
  Register a service with the QCSI infrastructure.

@param[in]  service_obj         Object containing meta information to
                                encode/decode the messages.
@param[in]  service_connect     Callback to register each client with the
                                service.
@param[in]  service_disconnect  Callback to unregister each client from
                                service.
@param[in]  service_process_req Callback that handles the incoming requests.
@param[in]  service_cookie      User data.
@param[in]  options             Options as defined by qmi_csi_options
@param[out] service_provider    Handle that infra provides to represent this
                                service connection.
@retval    QMI_CSI_NO_ERR       Success
@retval    QMI_CSI_.....        Look into the enumeration qmi_csi_error for
                                the error values.
*/
/*=========================================================================*/

qmi_csi_error
qmi_csi_register_with_options
(
 qmi_idl_service_object_type               service_obj,
 qmi_csi_connect                           service_connect,
 qmi_csi_disconnect                        service_disconnect,
 qmi_csi_process_req                       service_process_req,
 void                                      *service_cookie,
 qmi_csi_os_params                         *os_params,
 qmi_csi_options                           *options,
 qmi_csi_service_handle                    *service_provider
 )
{
  qmi_csi_error qmi_err = QMI_CSI_NO_ERR;

  // Go through the client-check callbacks to see if a client can be serviced
  sns_smr_service_check_cb_data* cb_data;
  uint8_t os_err;

  cb_data = (sns_smr_service_check_cb_data*)
      sns_q_check(&smr_client_check_cb_data_q.protected_q);

  // Search for the clients waiting on this service and call their client_init_cbs
  while( NULL != cb_data )
  {
    if (cb_data->serviceObj == service_obj)
    {
      // Get the matching client check callback from the queue and call it
      sns_os_mutex_pend(smr_client_check_cb_data_q.mutex_ptr, 0, &os_err );
      sns_q_delete(&cb_data->q_link);
      sns_os_mutex_post(smr_client_check_cb_data_q.mutex_ptr);
      SNS_ASSERT(NULL != cb_data);
      cb_data->init_cb(cb_data->serviceObj, cb_data->instanceID, false, NULL);
      SNS_OS_FREE(cb_data);
    }
    cb_data = (sns_smr_service_check_cb_data*)
        sns_q_next(&smr_client_check_cb_data_q.protected_q, &cb_data->q_link);
  }

  return qmi_err;
}

/*=============================================================================
  FUNCTION  qmi_csi_handle_event
=============================================================================*/
/*!
@brief
  Handle event after the server thread receives an event notification.
  Callbacks from qmi_csi_register may be invoked in the server's context.

@param[in] service_provider    Opaque handle that defines the service.
@param[in] os_params           OS-defined parameters such as file handle.

@retval    QMI_CSI_NO_ERR       Success
@retval    Other error codes    Failure
*/
/*=========================================================================*/

qmi_csi_error
qmi_csi_handle_event
(
 qmi_csi_service_handle                    service_provider,
 qmi_csi_os_params                         *os_params
 )
{
  // Offline Playback Stub
  return QMI_CSI_INTERNAL_ERR;
}

/*=============================================================================
  FUNCTION  qmi_csi_send_resp
=============================================================================*/
/*!
@brief
  Sends a response to the client.

@param[in]  req_handle            Handle used by QCSI infrastructure to
                                  identify the transaction and the destination
                                  client.
@param[in]  msg_id                Message ID for this particular message.
@param[in]  resp_c_struct         C data structure for this response.
@param[in]  resp_c_struct_len     Size of the response c struct.

@retval  QMI_CSI_NO_ERR           Success.
@retval  QMI_CSI_.....            Look into the enumeration qmi_csi_error for
                                  the error values.
*/
/*=========================================================================*/
qmi_csi_error
qmi_csi_send_resp
(
 qmi_req_handle     req_handle,
 unsigned int       msg_id,
 void               *resp_c_struct,
 unsigned int       resp_c_struct_len
 )
{
  // Offline Playback Stub
  return QMI_CSI_INTERNAL_ERR;
}

/*=============================================================================
  FUNCTION  qmi_csi_send_ind
=============================================================================*/
/*!
@brief
  Sends an indication to the client.

@param[in]  client_handle            Handle used by QCSI infrastructure
                                     to identify the destination client.
@param[in]  msg_id                   Message ID for this particular message.
@param[in]  ind_c_struct             C data strcuture for this indication.
@param[in]  ind_c_struct_len         Size of the indication c struct

@retval    QMI_CSI_NO_ERR            Success.
@retval    QMI_CSI_.....             Look into the enumeration qmi_csi_error for
                                     the error values.
*/
/*=========================================================================*/
qmi_csi_error
qmi_csi_send_ind
(
 qmi_client_handle  client_handle,
 unsigned int       msg_id,
 void               *ind_c_struct,
 unsigned int       ind_c_struct_len
 )
{
  // Offline Playback Stub
  return QMI_CSI_INTERNAL_ERR;
}

/*=============================================================================
  FUNCTION  qmi_csi_send_broadcast_ind
=============================================================================*/
/*!
@brief
  Sends a broadcast indication to all registered clients.

@param[in]  service_provider         Handle used by QCSI infrastructure
                                     to identify the service that intends to
                                     send a broadcast message.
@param[in]  msg_id                   Message ID for this particular message.
@param[in]  ind_c_struct             C data structure for this broadcast
                                     indication.
@param[in]  ind_c_struct_len         Size of the broadcast indication

@retval    QMI_CSI_NO_ERR            Success
@retval    QMI_CSI_.....             Look into the enumeration qmi_csi_error for
                                     the error values.
*/
/*=========================================================================*/

qmi_csi_error
qmi_csi_send_broadcast_ind
(
 qmi_csi_service_handle   service_provider,
 unsigned int             msg_id,
 void                     *ind_c_struct,
 unsigned int             ind_c_struct_len
 )
{
  // Offline Playback Stub
  return QMI_CSI_INTERNAL_ERR;
}

/*=============================================================================
  FUNCTION  qmi_csi_unregister
=============================================================================*/
/*!
@brief
  Unregisters a server.

@param[in]  service_provider         Handle given in the qmi_csi_register by
                                     the service.
@retval     QMI_CSI_NO_ERR           Success
@retval     QMI_CSI_.....            Look into the enumeration qmi_csi_error for
                                     the error values.
*/
/*=========================================================================*/
qmi_csi_error
qmi_csi_unregister
(
 qmi_csi_service_handle service_provider
 )
{
  // Offline Playback Stub
  return QMI_CSI_INTERNAL_ERR;
}

void
fpb_qmi_csi_init_q( void )
{
  uint8_t err;

  sns_q_init(&smr_client_check_cb_data_q.protected_q);
  smr_client_check_cb_data_q.mutex_ptr = sns_os_mutex_create(SNS_SMR_QUE_MUTEX, &err);
  SNS_ASSERT(err == OS_ERR_NONE);
}
