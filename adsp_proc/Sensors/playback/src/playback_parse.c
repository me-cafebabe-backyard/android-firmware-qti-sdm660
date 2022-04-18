#include <stdio.h>
#include <stdbool.h>
#include "playback_parse.h"
#include "sns_usmr.h"
#include "sns_log_api_public.h"
#include "sns_osa.h"
#include "sns_em.h"

// Includes for IDL headers
#include "sns_common_v01.h"
#include "sns_sam_qmd_v01.h"
#include "sns_sam_amd_v01.h"
#include "sns_sam_rmd_v01.h"
#include "sns_sam_ped_v01.h"
#include "sns_sam_smd_v01.h"
#include "sns_sam_cmc_v02.h"
#include "sns_sam_tilt_detector_v01.h"
#include "sns_sam_fast_amd_v01.h"
#include "sns_sam_filtered_mag_v01.h"
#include "sns_sam_rotation_vector_v01.h"
#include "sns_sam_quaternion_v01.h"
#include "sns_sam_gravity_vector_v01.h"
#include "sns_sam_orientation_v01.h"
#include "sns_sam_game_rotation_vector_v01.h"
#include "sns_sam_dpc_v02.h"
#include "sns_sam_multishake_v01.h"
#include "sns_sam_basic_gestures_v01.h"
#include "sns_sam_dev_ori_v01.h"
#include "sns_sam_pmd_v01.h"
#include "sns_sam_qmag_cal_v01.h"
#include "sns_sam_gyro_cal_v01.h"
#include "sns_smgr_api_v01.h"
#include "playback.h"


/*============================================================================
  Global Data
  ===========================================================================*/
/* Flag that enables/disables Sensor1 logging */
STATIC bool log_sensor1_enabled = true;

/* Input Sensor1 Diag Request File (SRT format w/o send_data) */
/* Should be in byte-string (decimal) format with space delimiters */
FILE * diag_req_file = NULL;

/* SAM client's event signal */
OS_FLAG_GRP *fpb_client_sig_event;

STATIC qmi_idl_service_object_type service_obj;

smr_client_hndl client_handle = NULL;

/*
 * FUNCTION: Parse Diag Request
 */
sensor1_error_e fast_playback_parse_diag_req(
    uint8_t* raw_diag_req_ptr,
    unsigned int raw_diag_req_size,
    fast_playback_sensor1_diag_req** diag_req_ptr)
{
  unsigned int raw_diag_req_size_min;
  fast_playback_sensor1_diag_req* diag_req = NULL;
  *diag_req_ptr = NULL;

  /* Do some argument sanity checking */
  if (NULL == raw_diag_req_ptr || NULL == diag_req_ptr)
  {
    printf("ERROR: null diag_req!\n");
    return SENSOR1_EFAILED;
  }
  // Make sure the raw_diag_req is at least large enough for the sensor1
  // request header and session header
  raw_diag_req_size_min = sizeof(fast_playback_sensor1_req_hdr) + sizeof(fast_playback_session_hdr);
  if (raw_diag_req_size_min > raw_diag_req_size)
  {
    printf("ERROR: Sensor1 Diag Request is too small! raw_diag_req_size=%d expected=%d\n", raw_diag_req_size, raw_diag_req_size_min);
    return SENSOR1_EBAD_MSG_ID;
  }

  // Malloc the diag_req
  diag_req = malloc(raw_diag_req_size);
  if (NULL == diag_req)
  {
    printf("ERROR: Unable to malloc for diag_req!\n");
    return SENSOR1_ENOMEM;
  }
  *diag_req_ptr = diag_req;

  /* Parse and sanity check the sensor1_req_hdr */
  diag_req->req_hdr.byte0 = raw_diag_req_ptr[0];
  diag_req->req_hdr.byte1 = raw_diag_req_ptr[1];
  diag_req->req_hdr.byte2 = raw_diag_req_ptr[2]; // Note: This value does not need to be verified
  diag_req->req_hdr.byte3 = raw_diag_req_ptr[3];
  diag_req->req_hdr.byte4 = raw_diag_req_ptr[4];
  diag_req->req_hdr.req_type = raw_diag_req_ptr[5];

  if (128 != diag_req->req_hdr.byte0 ||
      64  != diag_req->req_hdr.byte1 ||
      0   != diag_req->req_hdr.byte3 ||
      2   != diag_req->req_hdr.byte4 ||
      (FPB_SENSOR1_OPEN > diag_req->req_hdr.req_type ||
       FPB_SENSOR1_CLOSE < diag_req->req_hdr.req_type) )
  {
    printf("ERROR: Invalid sensor1_req_hdr field(s) found!\n");
    free(diag_req);
    *diag_req_ptr = NULL;
    return SENSOR1_EFAILED;
  }

  /* Parse and sanity check the session_hdr */
  diag_req->session_hdr.cb_data = (raw_diag_req_ptr[6] & 0xFF) |
    ((raw_diag_req_ptr[7] & 0xFF) << 8 ) |
    ((raw_diag_req_ptr[8] & 0xFF) << 16) |
    ((raw_diag_req_ptr[9] & 0xFF) << 24);
  diag_req->session_hdr.srvc_num = raw_diag_req_ptr[10];
  diag_req->session_hdr.msg_id = (raw_diag_req_ptr[11] & 0xFF) |
      ((raw_diag_req_ptr[12] & 0xFF) << 8 );
  diag_req->session_hdr.msg_type = raw_diag_req_ptr[13];
  diag_req->session_hdr.txn_id = raw_diag_req_ptr[14];
  diag_req->session_hdr.qmi_msg_size = (raw_diag_req_ptr[15] & 0xFF) |
      ((raw_diag_req_ptr[16] & 0xFF) << 8 );

  if (diag_req->session_hdr.msg_type > FPB_QMI_IDL_INDICATION ||
      raw_diag_req_size != (raw_diag_req_size_min + diag_req->session_hdr.qmi_msg_size))
  {
    printf("ERROR: Invalid session_hdr field(s) found!\n");
    free(diag_req);
    *diag_req_ptr = NULL;
    return SENSOR1_EFAILED;
  }

  /* Copy the QMI message body */
  memcpy(diag_req->qmi_message_body, &raw_diag_req_ptr[17], diag_req->session_hdr.qmi_msg_size);

  return SENSOR1_SUCCESS;
}

qmi_idl_service_object_type fpb_parse_get_service_obj( uint8_t service_num )
{
  qmi_idl_service_object_type ret_val;

  switch( service_num )
  {
    case SNS_SAM_AMD_SVC_ID_V01: // 4
      printf("AMD\n");
      ret_val = SNS_SAM_AMD_SVC_get_service_object_v01();
      break;

    case SNS_SAM_RMD_SVC_ID_V01: // 5
      printf("RMD\n");
      ret_val = SNS_SAM_RMD_SVC_get_service_object_v01();
      break;

    //case SNS_SAM_FNS_SVC_ID_V01: // 9
    //case SNS_SAM_BTE_SVC_ID_V01: // 10

    case SNS_SAM_FILTERED_MAG_SVC_ID_V01: // 17
      ret_val = SNS_SAM_FILTERED_MAG_SVC_get_service_object_v01();
      break;

    case SNS_SAM_ROTATION_VECTOR_SVC_ID_V01: // 18
      ret_val = SNS_SAM_ROTATION_VECTOR_SVC_get_service_object_v01();
      break;

    case SNS_SAM_QUATERNION_SVC_ID_V01: // 19
      ret_val = SNS_SAM_QUATERNION_SVC_get_service_object_v01();
      break;

    case SNS_SAM_GRAVITY_VECTOR_SVC_ID_V01: // 20
      ret_val = SNS_SAM_GRAVITY_VECTOR_SVC_get_service_object_v01();
      break;

    case SNS_SAM_ORIENTATION_SVC_ID_V01: // 23
      ret_val = SNS_SAM_ORIENTATION_SVC_get_service_object_v01();
      break;

    //case SNS_SAM_BASIC_GESTURES_SVC_ID_V01: // 25
    //case SNS_SAM_FACING_SVC_ID_V01: // 27

    case SNS_SAM_PED_SVC_ID_V01: // 37
      printf("Pedometer\n");
      ret_val = SNS_SAM_PED_SVC_get_service_object_v01();
      break;

    case SNS_SAM_SMD_SVC_ID_V01: // 40
      printf("SMD\n");
      ret_val = SNS_SAM_SMD_SVC_get_service_object_v01();
      break;

    case SNS_SAM_CMC_SVC_ID_V01: // 41
      printf("CMC\n");
      ret_val = SNS_SAM_CMC_SVC_get_service_object_v02();
      break;

    case SNS_SAM_GAME_ROTATION_VECTOR_SVC_ID_V01: // 43
      ret_val = SNS_SAM_GAME_ROTATION_VECTOR_SVC_get_service_object_v01();
      break;

    case SNS_SAM_TILT_DETECTOR_SVC_ID_V01: // 46
      ret_val = SNS_SAM_TILT_DETECTOR_SVC_get_service_object_v01();
      break;

    //TODO enable DPC
    case SNS_SAM_DPC2_SVC_ID_V01: // 58
        printf("DPC\n");
        ret_val = SNS_SAM_DPC_SVC_get_service_object_v02();
        break;

    case SNS_SAM_FAST_AMD_SVC_ID_V01:
      ret_val = SNS_SAM_FAST_AMD_SVC_get_service_object_v01();
      break;

    case SNS_SAM_BASIC_GESTURES_SVC_ID_V01:
        ret_val = SNS_SAM_BASIC_GESTURES_SVC_get_service_object_v01();
    break;

    case SNS_SAM_MULTISHAKE_SVC_ID_V01:
      ret_val = SNS_SAM_MULTISHAKE_SVC_get_service_object_v01();
      break;

    case SNS_SAM_DEV_ORI_SVC_ID_V01:
      ret_val = SNS_SAM_DEV_ORI_SVC_get_service_object_v01();
      break;

    case SNS_SAM_PMD_SVC_ID_V01:
      ret_val = SNS_SAM_PMD_SVC_get_service_object_v01();
      break;
    case SNS_SMGR_SVC_ID_V01:
      printf("\nSMGR SERVICE\n");
      ret_val = SNS_SMGR_SVC_get_service_object_v01();
      break;
    case SNS_SAM_GYRO_CAL_SVC_ID_V01:
      ret_val = SNS_SAM_GYRO_CAL_SVC_get_service_object_v01();
      printf("GYRO CAL SERVICE OBJECT\n"); //Nahush
      break;

    case SNS_SAM_QMAG_CAL_SVC_ID_V01:
      ret_val = SNS_SAM_QMAG_CAL_SVC_get_service_object_v01();
      printf("QMAG CAL SERVICE OBJECT\n"); //Nahush
      break;

    default:
      ret_val = NULL;
      break;
  }

  return ret_val;
}

void* fpb_parse_malloc_msg(qmi_idl_service_object_type service_obj,
                     qmi_idl_type_of_message_type msg_type,
                     unsigned int msg_id,
                     uint32_t *msg_len)
{
  void* ret_val = NULL;
  uint32_t length = 0;
  *msg_len = 0;

  // Get the size of the message C-struct
  int32_t qmi_err = qmi_idl_get_message_c_struct_len (service_obj, msg_type,
      (uint16_t) msg_id, &length);
  if (QMI_NO_ERR != qmi_err)
  {
    printf("qmi_idl_get_message_c_struct_len %ld\n", qmi_err);
    return NULL;
  }

  ret_val = malloc(length);
  if (NULL != ret_val)
  {
    *msg_len = length;
  }
  else
  {
    printf("ERROR: No memory to malloc %lu bytes", length);
  }

  return ret_val;
}


void fpb_parse_client_ind_cb(smr_client_hndl client_handle,
                             unsigned int msg_id,
                             void *ind_c_struct,
                             unsigned int ind_struct_len,
                             void *ind_cb_data)
{
//  printf("fpb_parse_client_ind_cb msg_id %d\n", msg_id);
  unsigned int log_sensor1_ind_size;
  uint32_t qmi_ind_encoded_len_max = 0, qmi_ind_encoded_len = 0;
  int32_t qmi_err;
  fast_playback_sensor1_diag_req * diag_req = ind_cb_data;
  SNS_ASSERT( NULL != diag_req);

  // Get the maximum size of the message length
  qmi_err = qmi_idl_get_max_message_len(service_obj,
      QMI_IDL_INDICATION,
      msg_id,
      &qmi_ind_encoded_len_max);
  if( QMI_NO_ERR != qmi_err )
  {
    printf("ERROR: qmi_idl_get_max_message_len error %ld\n", qmi_err);
  }

  // Encode the indication in wire format
  uint8_t qmi_ind_encoded[qmi_ind_encoded_len_max];
  qmi_err = qmi_idl_message_encode (
      service_obj,
      QMI_IDL_INDICATION,
      msg_id,
      ind_c_struct,
      ind_struct_len,
      qmi_ind_encoded,
      qmi_ind_encoded_len_max,
      &qmi_ind_encoded_len );
  if( QMI_NO_ERR != qmi_err )
  {
    printf("ERROR: qmi_idl_message_encode error %ld\n", qmi_err);
  }

  if( log_sensor1_enabled )
  {
    // Log the Sensor1 Indication
    log_sensor1_ind_size = sizeof(sns_log_sensor1_resp_ind_s) + qmi_ind_encoded_len;
    sns_log_sensor1_resp_ind_s* log_sensor1_ind = malloc( log_sensor1_ind_size );
    if( NULL != log_sensor1_ind )
    {
      log_sensor1_ind->version = SNS_LOG_STRUCT_VERSION;
      log_sensor1_ind->logging_processor = 3; // TODO: FIX THIS?
      log_sensor1_ind->timestamp = sns_em_get_timestamp(); // TODO: FIX THIS?
//      sns_em_get_timestamp64(&log_sensor1_ind->timestamp);
      log_sensor1_ind->cb_data = diag_req->session_hdr.cb_data;
      log_sensor1_ind->context_handle = 0; // TODO: FIX THIS?
      log_sensor1_ind->ext_clnt_id = 0; // TODO: FIX THIS?
      log_sensor1_ind->svc_num = diag_req->session_hdr.srvc_num;
      log_sensor1_ind->msg_id = msg_id;
      log_sensor1_ind->msg_type = QMI_IDL_INDICATION;
      log_sensor1_ind->txn_id = diag_req->session_hdr.txn_id;
      log_sensor1_ind->resp_ind_size = qmi_ind_encoded_len;
      memcpy(log_sensor1_ind->resp_ind, qmi_ind_encoded, log_sensor1_ind->resp_ind_size);

      sns_logpkt_submit(LOG_SNS_SENSOR1_INDICATION_C, log_sensor1_ind_size, log_sensor1_ind);
      free(log_sensor1_ind);
    }
  }
}

void fpb_parse_client_error_cb (smr_client_hndl client_handle,
                                 smr_err error,
                                 void *err_cb_data)
{
  printf("[stub] fpb_parse_client_error_cb error %d\n", error);
}

void fpb_parse_client_resp_cb (
    smr_client_hndl client_handle,
    unsigned int msg_id,
    void *resp_c_struct,
    unsigned int resp_c_struct_len,
    void *resp_cb_data,
    smr_err transp_err)
{
  printf("fpb_parse_client_resp_cb msg_id %d\n", msg_id);
  unsigned int log_sensor1_resp_size;
  uint32_t qmi_resp_encoded_len_max = 0, qmi_resp_encoded_len = 0;
  int32_t qmi_err;
  fast_playback_sensor1_diag_req * diag_req = resp_cb_data;
  SNS_ASSERT( NULL != diag_req);

  // Get the maximum size of the message length
  qmi_err = qmi_idl_get_max_message_len(service_obj,
      QMI_IDL_RESPONSE,
      msg_id,
      &qmi_resp_encoded_len_max);
  if( QMI_NO_ERR != qmi_err )
  {
    printf("ERROR: qmi_idl_get_max_message_len error %ld\n", qmi_err);
  }

  // Encode the response in wire format
  uint8_t qmi_resp_encoded[qmi_resp_encoded_len_max];
  qmi_err = qmi_idl_message_encode (
      service_obj,
      QMI_IDL_RESPONSE,
      msg_id,
      resp_c_struct,
      resp_c_struct_len,
      qmi_resp_encoded,
      qmi_resp_encoded_len_max,
      &qmi_resp_encoded_len );
  if( QMI_NO_ERR != qmi_err )
  {
    printf("ERROR: qmi_idl_message_encode error %ld\n", qmi_err);
  }

  if( log_sensor1_enabled )
  {
    // Log the Sensor1 Response
    log_sensor1_resp_size = sizeof(sns_log_sensor1_resp_ind_s) + qmi_resp_encoded_len;
    sns_log_sensor1_resp_ind_s* log_sensor1_resp = malloc( log_sensor1_resp_size );
    if( NULL != log_sensor1_resp )
    {
      log_sensor1_resp->version = SNS_LOG_STRUCT_VERSION;
      log_sensor1_resp->logging_processor = 3; // TODO: FIX THIS?
      log_sensor1_resp->timestamp = sns_em_get_timestamp(); // TODO: FIX THIS?
//      sns_em_get_timestamp64(&log_sensor1_resp->timestamp);
      log_sensor1_resp->cb_data = diag_req->session_hdr.cb_data;
      log_sensor1_resp->context_handle = 0; // TODO: FIX THIS?
      log_sensor1_resp->ext_clnt_id = 0; // TODO: FIX THIS?
      log_sensor1_resp->svc_num = diag_req->session_hdr.srvc_num;
      log_sensor1_resp->msg_id = msg_id;
      log_sensor1_resp->msg_type = QMI_IDL_RESPONSE;
      log_sensor1_resp->txn_id = diag_req->session_hdr.txn_id;
      log_sensor1_resp->resp_ind_size = qmi_resp_encoded_len;
      memcpy(log_sensor1_resp->resp_ind, qmi_resp_encoded, log_sensor1_resp->resp_ind_size);

      sns_logpkt_submit(LOG_SNS_SENSOR1_RESPONSE_C, log_sensor1_resp_size, log_sensor1_resp);
      free(log_sensor1_resp);
    }
  }
  uint8_t errOS;
  sns_os_sigs_post( playback_sig_event,
  FPB_CLIENT_CONNECT_DONE, OS_FLAG_SET, &errOS );

}

void fpb_disable_client_resp_cb (
    smr_client_hndl client_handle,
    unsigned int msg_id,
    void *resp_c_struct,
    unsigned int resp_c_struct_len,
    void *resp_cb_data,
    smr_err transp_err)
{
  if(SNS_SAM_ALGO_DISABLE_REQ_V01 == msg_id)
  {
    printf("fpb_disable_client_resp_cb msg_id %d\n", msg_id);
    uint8_t errOS;
    sns_os_sigs_post( playback_disable_sig_event,
        FPB_CLIENT_DISABLE_DONE, OS_FLAG_SET, &errOS );
  }
}

void fpb_parse_client_cb (qmi_idl_service_object_type serviceObj,
                          qmi_service_instance instanceID,
                          bool timeoutExpired,
                          void *param)
{
  uint8_t errOS;

  printf("fpb_parse_client_cb service obj %x\n", serviceObj);

  sns_os_sigs_post( fpb_client_sig_event,
          FPB_RESUME_CLIENT_INIT_SIG, OS_FLAG_SET, &errOS );
}

sns_err_code_e fast_playback_parse_client_init( const fast_playback_sensor1_diag_req * diag_req )
{
  smr_err smr_error;
//  qmi_idl_service_object_type service_obj;
  //smr_client_hndl client_handle;
  smr_txn_handle txn_handle;
  int32_t qmi_err;
  void *qmi_req_msg_c_struct, *qmi_resp_msg_c_struct;
  uint32_t qmi_req_msg_c_struct_size, qmi_resp_msg_c_struct_size;
  uint8_t errOS;
  OS_FLAGS sigFlags;

  if( NULL == diag_req )
  {
    printf("ERROR: Invalid diag_req\n");
    return SNS_ERR_FAILED;
  }

  // Verify that the diag request is a Sensor1-write and a QMI-request
  if( diag_req->req_hdr.req_type != FPB_SENSOR1_WRITE ||
      diag_req->session_hdr.msg_type != FPB_QMI_IDL_REQUEST )
  {
    printf("ERROR: Only Sensor1-writes and QMI-requests are allowed.\n");
    return SNS_ERR_NOTALLOWED;
  }

  service_obj = fpb_parse_get_service_obj( diag_req->session_hdr.srvc_num );
  if( NULL == service_obj)
  {
    printf("ERROR: Unable to find the service object for service %d\n", diag_req->session_hdr.srvc_num);
    exit(0);
    return SNS_ERR_FAILED;
  }

  // TODO: ADD MORE SIGNAL BITS TO SUPPORT MULTIPLE CONCURRENT SERVICE REQUESTS
  fpb_client_sig_event = sns_os_sigs_create(
      (OS_FLAGS)FPB_RESUME_CLIENT_INIT_SIG, &errOS );
  SNS_ASSERT( NULL != fpb_client_sig_event );

  // Check to see if the desired service is available
  smr_error = smr_client_check(service_obj, SMR_CLIENT_INSTANCE_ANY, 0,
      fpb_parse_client_cb);

  // Wait for the desired service to come up
  printf("Waiting on service %x to come up...\n", service_obj);
  fflush(stdout);
  sigFlags = sns_os_sigs_pend( fpb_client_sig_event, FPB_RESUME_CLIENT_INIT_SIG,
      OS_FLAG_WAIT_SET_ANY + OS_FLAG_CONSUME, 0, &errOS );
  SNS_ASSERT( OS_ERR_NONE == errOS );

  printf("Service %x is up.\n", service_obj);

  // Initialize the SMR client for the desired service
  smr_error = smr_client_init( service_obj,
      SMR_CLIENT_INSTANCE_ANY,
      fpb_parse_client_ind_cb,
      (void*) diag_req,
      0,
      fpb_parse_client_error_cb,
      (void*) diag_req,
      &client_handle,
      false);
  if( SMR_NO_ERR != smr_error )
  {
    printf("ERROR: smr_client_init error %d\n", smr_error);
    return SNS_ERR_FAILED;
  }

  // Malloc the request and response message C-structs
  qmi_req_msg_c_struct = fpb_parse_malloc_msg(
      service_obj,
      QMI_IDL_REQUEST,
      diag_req->session_hdr.msg_id,
      &qmi_req_msg_c_struct_size);
  qmi_resp_msg_c_struct = fpb_parse_malloc_msg(
      service_obj,
      QMI_IDL_RESPONSE,
      diag_req->session_hdr.msg_id,
      &qmi_resp_msg_c_struct_size);

  if( NULL == qmi_req_msg_c_struct || NULL == qmi_resp_msg_c_struct )
  {
    printf("ERROR: No memory to allocate\n");
    return SNS_ERR_NOMEM;
  }

  // Decode the QMI message body into the C-struct format
  qmi_err = qmi_idl_message_decode(
      service_obj,
      (qmi_idl_type_of_message_type) diag_req->session_hdr.msg_type,
      diag_req->session_hdr.msg_id,
      diag_req->qmi_message_body,
      diag_req->session_hdr.qmi_msg_size,
      qmi_req_msg_c_struct,
      qmi_req_msg_c_struct_size);
  if( QMI_NO_ERR != qmi_err )
  {
    printf("ERROR: qmi_idl_message_decode error %ld\n", qmi_err);
    return SNS_ERR_FAILED;
  }


  // Send the QMI request
  smr_error = smr_client_send_req(client_handle,
      diag_req->session_hdr.msg_id,
      qmi_req_msg_c_struct,
      qmi_req_msg_c_struct_size,
      qmi_resp_msg_c_struct,
      qmi_resp_msg_c_struct_size,
      fpb_parse_client_resp_cb,
      (void*) diag_req,
      &txn_handle);
  if( SMR_NO_ERR != smr_error )
  {
    printf("ERROR: smr_client_init error %d\n", smr_error);
    return SNS_ERR_FAILED;
  }

  return SNS_SUCCESS;
}

/*============================================================================
  Public Function Definitions
  ===========================================================================*/
sns_err_code_e fast_playback_parse_send_diag_req( const char* sns_diag_filename,
    fast_playback_sensor1_diag_req** diag_req_ptr)
{
//  sns_err_code_e  err = SNS_SUCCESS;
//  sns_fsa_stat_s  stat;
  diag_req_file = NULL;
  char diag_string[FPB_MAX_DIAG_STRING_SIZE];
  char * byte;
  uint8_t byte_string[FPB_MAX_BYTE_STRING_SIZE];
  unsigned int byte_string_size = 0;
  fast_playback_sensor1_diag_req * diag_req;
  int diag_cnt = 0;
  uint8_t errOS;
  OS_FLAGS sigFlags;

  // TODO: sns_fsa_stat(sns_diag_filename, &stat);
  if (NULL == sns_diag_filename)
  {
    printf("ERROR: No DIAG filename provided!\n");
    return SNS_ERR_FAILED;
  }

  // TODO: sns_fsa_open(sns_diag_filename, "r");
  diag_req_file = fopen(sns_diag_filename, "r");
  if( NULL == diag_req_file )
  {
    printf("ERROR: Error opening diag request file\n");
    return( SNS_ERR_FAILED );
  }

  /* Read out the diag byte string.
   * Keep reading lines until a byte string can be processed or until there are
   * no more lines to be read.
   */
  while( (NULL != fgets(diag_string, sizeof(diag_string), diag_req_file)))
  {
    /* FORMAT: <byte in decimal> <byte in decimal> <byte in decimal> ... */

    // Tokenize the byte
    byte = strtok_r(diag_string, FPB_DIAG_STRING_DELIMS, &line_save);
    while( byte != NULL)
    {
      if( FPB_DIAG_STRING_COMMENT_CHAR == byte[0] )
      {
        // Stop processing upon hitting the comment character
        break;
      }
      byte_string[byte_string_size] = (uint8_t) atoi(byte);

      byte_string_size++;
      byte = strtok_r(NULL, FPB_DIAG_STRING_DELIMS, &line_save);
    }

    if(0 == byte_string_size)
    {
      continue; //skip comment line
    }

    diag_cnt++;

    if(diag_cnt > 2)
    {
      printf("ERROR: Unable to send more than 2 Sensor1 diag request!\n");
      return SNS_ERR_NOTALLOWED;
    }

    // Parse the diag byte string
    fast_playback_parse_diag_req(byte_string, byte_string_size, &diag_req);
    if( NULL == diag_req )
    {
      printf("ERROR: Unable to parse the Sensor1 diag request!\n");
      return SNS_ERR_FAILED;
    }

    if( log_sensor1_enabled )
    {
      // Log the Sensor1 Request
      unsigned int log_sensor1_req_size = sizeof(sns_log_sensor1_request_s) + diag_req->session_hdr.qmi_msg_size;
      sns_log_sensor1_request_s* log_sensor1_req = malloc( log_sensor1_req_size );
      if( NULL != log_sensor1_req )
      {
        log_sensor1_req->version = SNS_LOG_STRUCT_VERSION;
        log_sensor1_req->logging_processor = 3; // TODO: FIX THIS?
        log_sensor1_req->timestamp = sns_em_get_timestamp(); // TODO: FIX THIS?
  //      sns_em_get_timestamp64(&log_sensor1_req->timestamp);
        log_sensor1_req->sensor1_fn = SNS_LOG_SENSOR1_API_WRITE;
        log_sensor1_req->sensor1_rv = SENSOR1_SUCCESS; // TODO: FIX THIS?
        log_sensor1_req->ext_clnt_id = 0; // TODO: FIX THIS?
        log_sensor1_req->cb_data = diag_req->session_hdr.cb_data;
        log_sensor1_req->context_handle = 0; // TODO: FIX THIS?
        log_sensor1_req->svc_num = diag_req->session_hdr.srvc_num;
        log_sensor1_req->msg_id = diag_req->session_hdr.msg_id;
        log_sensor1_req->msg_type = diag_req->session_hdr.msg_type;
        log_sensor1_req->txn_id = diag_req->session_hdr.txn_id;
        log_sensor1_req->request_size = diag_req->session_hdr.qmi_msg_size;
        memcpy(log_sensor1_req->request, diag_req->qmi_message_body, diag_req->session_hdr.qmi_msg_size);

        sns_logpkt_submit(LOG_SNS_SENSOR1_REQUEST_C, log_sensor1_req_size, log_sensor1_req);
        free(log_sensor1_req);
      }
    }

    printf("Request type %d\n", diag_req->req_hdr.req_type);
    printf("Service number %d\n", diag_req->session_hdr.srvc_num);
    printf("Message ID %d\n", diag_req->session_hdr.msg_id);
    printf("Message type %d\n", diag_req->session_hdr.msg_type);
    printf("Message size %d\n", diag_req->session_hdr.qmi_msg_size);


    // Initialize client for target algorithm
    fast_playback_parse_client_init(diag_req);

    //------------- WAIT UNTIL THE SAM REQUESTS FOR SMGR DATA ----------------//
    printf("Waiting for the client connect to be ready to "
            "accept sensor inputs...\n");
    fflush(stdout);
    sigFlags = sns_os_sigs_pend( playback_sig_event,
        (OS_FLAGS) FPB_CLIENT_CONNECT_DONE,
        OS_FLAG_WAIT_SET_ANY + OS_FLAG_CONSUME, 0, &errOS );

    printf("Client connected \n");


    if( diag_req->session_hdr.srvc_num == SNS_SMGR_SVC_ID_V01
         && diag_req->session_hdr.msg_id != SNS_SMGR_PHONE_MODE_SWITCH_REQ_V01)
    {
      printf("\nSMGR service being requested, wait for enabling of CAL Algo\n");
      sigFlags = sns_os_sigs_pend( playback_sig_event,
                                   (OS_FLAGS) FPB_CAL_ENABLE_SIG,
                                   OS_FLAG_WAIT_SET_ANY + OS_FLAG_CONSUME,
                                   0, &errOS );
      printf("\nCAL algo enabled by SMGR\n");
    }

    memset(byte_string, 0, byte_string_size);
    byte_string_size = 0;
  } //while( (NULL != fgets(diag_string, sizeof(diag_string), diag_req_file)))

  // TODO: Unify all usage of sns_err_code_e and sensor1_error_e
  *diag_req_ptr = diag_req;
  return SNS_SUCCESS;
}


sns_err_code_e fast_playback_disable_client( const fast_playback_sensor1_diag_req * diag_req )
{
  sns_smgr_buffering_req_msg_v01 *smgr_bf_req_ptr;
  smr_err smr_error;
  smr_txn_handle txn_handle;
  int32_t qmi_err;
  void *qmi_req_msg_c_struct, *qmi_resp_msg_c_struct;
  uint32_t qmi_req_msg_c_struct_size, qmi_resp_msg_c_struct_size;
  uint8_t errOS;
  uint16_t disable_msg_id;

  if( NULL == diag_req )
  {
    printf("ERROR: Invalid diag_req\n");
    return SNS_ERR_FAILED;
  }

  // Verify that the diag request is a Sensor1-write and a QMI-request
  if( diag_req->req_hdr.req_type != FPB_SENSOR1_WRITE ||
      diag_req->session_hdr.msg_type != FPB_QMI_IDL_REQUEST )
  {
    printf("ERROR: Only Sensor1-writes and QMI-requests are allowed.\n");
    return SNS_ERR_NOTALLOWED;
  }

  service_obj = fpb_parse_get_service_obj( diag_req->session_hdr.srvc_num );
  if( NULL == service_obj)
  {
    printf("ERROR: Unable to find the service object for service %d\n", diag_req->session_hdr.srvc_num);
    exit(0);
    return SNS_ERR_FAILED;
  }


  if(SNS_SMGR_SVC_ID_V01 == diag_req->session_hdr.srvc_num)
  {
    disable_msg_id = diag_req->session_hdr.msg_id;
  }
  else
  {
    disable_msg_id = SNS_SAM_ALGO_DISABLE_REQ_V01;
  }


  // Malloc the request and response message C-structs
  qmi_req_msg_c_struct = fpb_parse_malloc_msg(
      service_obj,
      QMI_IDL_REQUEST,
      disable_msg_id,
      &qmi_req_msg_c_struct_size);
  qmi_resp_msg_c_struct = fpb_parse_malloc_msg(
      service_obj,
      QMI_IDL_RESPONSE,
      disable_msg_id,
      &qmi_resp_msg_c_struct_size);

  if( NULL == qmi_req_msg_c_struct || NULL == qmi_resp_msg_c_struct )
  {
    printf("ERROR: No memory to allocate\n");
    return SNS_ERR_NOMEM;
  }

  if(SNS_SMGR_SVC_ID_V01 == diag_req->session_hdr.srvc_num)
  {
    //Decode the QMI message body into the C-struct format
    qmi_err = qmi_idl_message_decode(
        service_obj,
        (qmi_idl_type_of_message_type) diag_req->session_hdr.msg_type,
        disable_msg_id,
        diag_req->qmi_message_body,
        diag_req->session_hdr.qmi_msg_size,
        qmi_req_msg_c_struct,
        qmi_req_msg_c_struct_size);
    if( QMI_NO_ERR != qmi_err )
    {
      printf("ERROR: qmi_idl_message_decode error %ld\n", qmi_err);
      return SNS_ERR_FAILED;
    }

    smgr_bf_req_ptr = (sns_smgr_buffering_req_msg_v01 *)qmi_req_msg_c_struct;
    smgr_bf_req_ptr->Action = SNS_SMGR_BUFFERING_ACTION_DELETE_V01;
  }

  // Send the QMI request to DELETE the stream
  smr_error = smr_client_send_req(client_handle,
      disable_msg_id,
      qmi_req_msg_c_struct,
      qmi_req_msg_c_struct_size,
      qmi_resp_msg_c_struct,
      qmi_resp_msg_c_struct_size,
      fpb_disable_client_resp_cb,
      (void*) diag_req,
      &txn_handle);
  if( SMR_NO_ERR != smr_error )
  {
    printf("ERROR: smr_client_disable error %d\n", smr_error);
    return SNS_ERR_FAILED;
  }

  return SNS_SUCCESS;
}

sns_err_code_e fast_playback_send_diag_helper(smgr_sensor_id_e sensor_id, char * raw_diag_string)
{
  smr_err smr_error;
  smr_txn_handle txn_handle;
  int32_t qmi_err;
  void *qmi_req_msg_c_struct, *qmi_resp_msg_c_struct;
  uint32_t qmi_req_msg_c_struct_size, qmi_resp_msg_c_struct_size;
  uint8_t errOS;
  OS_FLAGS sigFlags;

  fast_playback_sensor1_diag_req * diag_req;

  fast_playback_parse_diag_req(raw_diag_string, raw_diag_string[15]+17, &diag_req); //raw_diag_req_size = raw_diag_req_size_min + diag_req->session_hdr.qmi_msg_size

  if( NULL == diag_req )
  {
    printf("ERROR: Unable to parse the Sensor1 diag request!\n");
    return SNS_ERR_FAILED;
  }

  if( log_sensor1_enabled )
  {
    // Log the Sensor1 Request
    unsigned int log_sensor1_req_size = sizeof(sns_log_sensor1_request_s) + diag_req->session_hdr.qmi_msg_size;
    sns_log_sensor1_request_s* log_sensor1_req = malloc( log_sensor1_req_size );
    if( NULL != log_sensor1_req )
    {
      log_sensor1_req->version = SNS_LOG_STRUCT_VERSION;
      log_sensor1_req->logging_processor = 3; // TODO: FIX THIS?
      log_sensor1_req->timestamp = sns_em_get_timestamp(); // TODO: FIX THIS?
      log_sensor1_req->sensor1_fn = SNS_LOG_SENSOR1_API_WRITE;
      log_sensor1_req->sensor1_rv = SENSOR1_SUCCESS; // TODO: FIX THIS?
      log_sensor1_req->ext_clnt_id = 0; // TODO: FIX THIS?
      log_sensor1_req->cb_data = diag_req->session_hdr.cb_data;
      log_sensor1_req->context_handle = 0; // TODO: FIX THIS?
      log_sensor1_req->svc_num = diag_req->session_hdr.srvc_num;
      log_sensor1_req->msg_id = diag_req->session_hdr.msg_id;
      log_sensor1_req->msg_type = diag_req->session_hdr.msg_type;
      log_sensor1_req->txn_id = diag_req->session_hdr.txn_id;
      log_sensor1_req->request_size = diag_req->session_hdr.qmi_msg_size;
      memcpy(log_sensor1_req->request, diag_req->qmi_message_body, diag_req->session_hdr.qmi_msg_size);

      sns_logpkt_submit(LOG_SNS_SENSOR1_REQUEST_C, log_sensor1_req_size, log_sensor1_req);
      free(log_sensor1_req);
    }
  }

  printf("Request type %d\n", diag_req->req_hdr.req_type);
  printf("Service number %d\n", diag_req->session_hdr.srvc_num);
  printf("Message ID %d\n", diag_req->session_hdr.msg_id);
  printf("Message type %d\n", diag_req->session_hdr.msg_type);
  printf("Message size %d\n", diag_req->session_hdr.qmi_msg_size);


  service_obj = fpb_parse_get_service_obj( diag_req->session_hdr.srvc_num );
  if( NULL == service_obj)
  {
    printf("ERROR: Unable to find the service object for service %d\n", diag_req->session_hdr.srvc_num);
    exit(0);
    return SNS_ERR_FAILED;
  }

  // Malloc the request and response message C-structs
  qmi_req_msg_c_struct = fpb_parse_malloc_msg(
      service_obj,
      QMI_IDL_REQUEST,
      diag_req->session_hdr.msg_id,
      &qmi_req_msg_c_struct_size);
  qmi_resp_msg_c_struct = fpb_parse_malloc_msg(
      service_obj,
      QMI_IDL_RESPONSE,
      diag_req->session_hdr.msg_id,
      &qmi_resp_msg_c_struct_size);

  if( NULL == qmi_req_msg_c_struct || NULL == qmi_resp_msg_c_struct )
  {
    printf("ERROR: No memory to allocate\n");
    return SNS_ERR_NOMEM;
  }

  // Decode the QMI message body into the C-struct format
  qmi_err = qmi_idl_message_decode(
      service_obj,
      (qmi_idl_type_of_message_type) diag_req->session_hdr.msg_type,
      diag_req->session_hdr.msg_id,
      diag_req->qmi_message_body,
      diag_req->session_hdr.qmi_msg_size,
      qmi_req_msg_c_struct,
      qmi_req_msg_c_struct_size);
  if( QMI_NO_ERR != qmi_err )
  {
    printf("ERROR: qmi_idl_message_decode error %ld\n", qmi_err);
    return SNS_ERR_FAILED;
  }


  // Send the QMI request
  smr_error = smr_client_send_req(client_handle,
      diag_req->session_hdr.msg_id,
      qmi_req_msg_c_struct,
      qmi_req_msg_c_struct_size,
      qmi_resp_msg_c_struct,
      qmi_resp_msg_c_struct_size,
      fpb_parse_client_resp_cb,
      (void*) diag_req,
      &txn_handle);
  if( SMR_NO_ERR != smr_error )
  {
    printf("ERROR: smr_client_init error %d\n", smr_error);
    return SNS_ERR_FAILED;
  }

  return SNS_SUCCESS;
}

sns_err_code_e fast_playback_send_cal_reset(smgr_sensor_id_e sensor_id)
{
  char raw_diag_string[FPB_MAX_DIAG_STRING_SIZE];
  //Create the request header for reset
  raw_diag_string[0]=128;
  raw_diag_string[1]=64;
  raw_diag_string[2]=3;
  raw_diag_string[3]=0;
  raw_diag_string[4]=2;
  raw_diag_string[5]=2;
  raw_diag_string[6]=1;
  raw_diag_string[7]=0;
  raw_diag_string[8]=0;
  raw_diag_string[9]=0;
  raw_diag_string[10]=0;
  raw_diag_string[11]=38;
  raw_diag_string[12]=0;
  raw_diag_string[13]=0;
  raw_diag_string[14]=0;
  raw_diag_string[15]=12;
  raw_diag_string[16]=0;
  raw_diag_string[17]=1;
  raw_diag_string[18]=1;
  raw_diag_string[19]=0;
  raw_diag_string[20]=0;
  raw_diag_string[21]=2;
  raw_diag_string[22]=1;
  raw_diag_string[23]=0;
  //Sensor ID
  raw_diag_string[24]=sensor_id;
  raw_diag_string[25]=3;
  raw_diag_string[26]=1;
  raw_diag_string[27]=0;
  raw_diag_string[28]=0;

  return fast_playback_send_diag_helper(sensor_id,raw_diag_string );

}

sns_err_code_e fast_playback_send_cal_mode_switch(smgr_sensor_id_e sensor_id, q16_t phone_mode )
{
  char raw_diag_string[FPB_MAX_DIAG_STRING_SIZE];
  /*
  $> sns_smgr_mode_switch( 1, 0)
  sns_smgr_mode_switch( 1, 0)
  + --> send_data 128 64 2 0 2 2 1 0 0 0 0 39 0 0 0 7 0 1 4 0 0 0 0 0
  $> sns_smgr_mode_switch( 1, 1)
  sns_smgr_mode_switch( 1, 1)
  + --> send_data 128 64 2 0 2 2 1 0 0 0 0 39 0 0 0 7 0 1 4 0 1 0 0 0
  */

  //Create the request header for mode switch
  raw_diag_string[0]=128;
  raw_diag_string[1]=64;
  raw_diag_string[2]=2;
  raw_diag_string[3]=0;
  raw_diag_string[4]=2;
  raw_diag_string[5]=2;
  raw_diag_string[6]=1;
  raw_diag_string[7]=0;
  raw_diag_string[8]=0;
  raw_diag_string[9]=0;
  raw_diag_string[10]=0;
  raw_diag_string[11]=39;
  raw_diag_string[12]=0;
  raw_diag_string[13]=0;
  raw_diag_string[14]=0;
  raw_diag_string[15]=7;
  raw_diag_string[16]=0;
  raw_diag_string[17]=1;
  raw_diag_string[18]=4;
  raw_diag_string[19]=0;
  raw_diag_string[20]= phone_mode;
  raw_diag_string[21]=0;
  raw_diag_string[22]=0;
  raw_diag_string[23]=0;
  //raw_diag_string[24]=0;
  //raw_diag_string[25]=3;
  //raw_diag_string[26]=1;
  //raw_diag_string[27]=0;
  //raw_diag_string[28]=0;

  return fast_playback_send_diag_helper(sensor_id,raw_diag_string );

}
