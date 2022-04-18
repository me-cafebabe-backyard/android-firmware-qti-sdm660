/*============================================================================
  @file sns_hdrll.c

  @brief
  API functions, data structures, and constants used by the High Data Rate,
  Low Latency (HDRLL) Library

  @note
  File line length should generally be limited to <= 80 columns.

  Copyright (c) 2016 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
  ===========================================================================*/

#include <qmi_client.h>
#include <qmi_idl_lib_internal.h>
#include <DDIIPCInt.h>

#include "sns_hdrll.h"
#include "sns_hdrll_daf.h"
#include "sns_debug_str.h"
#include "sns_smgr_restricted_api_v01.h"
#include "sns_reg_api_v02.h"
#include "sns_reg_common.h"
#include "sns_profiling.h"
#include "sns_memmgr.h"

/*============================================================================
  Preprocessor Definitions and Constants
  ===========================================================================*/

// Arbitrarily set timeout duration
#define SNS_HDRLL_QMI_TIMEOUT_MS       2000 // 2000 ms timeout


/*============================================================================
  Static variable definitions
  ===========================================================================*/

static DalDeviceHandle * sns_hdrll_int_handle;


/*============================================================================
  Type Declarations
  ===========================================================================*/


/*============================================================================
  Function Definitions
  ===========================================================================*/


/*===========================================================================

  FUNCTION:   sns_hdrll_enable_hdrll_mode

  ===========================================================================*/
/**
   @brief This function enables HDRLL mode in the SSC for the given sensors at
          their specified rates.

   @note HDRLL mode entails bypassing the standard SSC frameworks in favor of
         faster channels. This is all done to reduce the latency between the
         receiving of the samples and the sending of those samples.

   @param[out] client                An opaque handle used to identify this client
   @param[in]  send_data_cb          This callback function will be used by the
                                     driver to write data to a location determined
                                     by the client
   @param[in]  handle_error_cb       This callback function will be used by the
                                     driver to notify the HDRLL client of any
                                     unexpected errors
   @param[in]  cb_context            User-defined context that will be supplied
                                     back to the user when any of the callback
                                     functions are called
   @param[in]  sensor_requests       Table of the sensors the client is
                                     requesting to be enabled along with their
                                     specified rates

   @return
     - 0: client successfully registered
     - -1: otherwise
     - all other values are reserved
*/
int
sns_hdrll_enable_hdrll_mode
(
  sns_hdrll_client_handle*                  client,
  sns_hdrll_send_data_cb                    send_data_cb,
  sns_hdrll_handle_error_cb                 handle_error_cb,
  const sns_hdrll_context_handle            cb_context,
  const sns_hdrll_sensor_request_table*     sensor_requests
)
{
  qmi_client_error_type                qmi_err;
  qmi_client_type                      smgr_res_qmi_client_handle;
//  qmi_client_type                      reg_qmi_client_handle;
  sns_daf_hdrll_enable_req_v01         hdrll_en_req_msg;
  sns_daf_hdrll_enable_resp_v01*       hdrll_en_resp_msg;
  sns_smgr_driver_access_req_msg_v01   daf_req_msg;
  sns_smgr_driver_access_resp_msg_v01  daf_resp_msg;
  int                                  i;
  DALResult                            dal_err;

  uint8_t                              bmi160_uuid[16] = SNS_REG_UUID_BMI160;

  MSG(MSG_SSID_SNS,DBG_HIGH_PRIO,"HDRLL - enable_hdrll_mode");

  // Validate inputs
  // Note: the handle_error_cb and the cb_context are optional
  if ( (NULL == client) || (NULL == send_data_cb) || (NULL == sensor_requests) )
  {
    return -1;
  }
  // PEND: Determine a reasonable max number of entries
//  if ( sensor_requests->num_entries > 2 )
//  {
//    return -1;
//  }
  // PEND: enforce the sensor_requests to be only accel and gyro at matching
  // rates.

  // Initialize QMI client with the Registry service (to lookup the UUID)
//  qmi_err = qmi_client_init_instance(
//      SNS_REG2_SVC_get_service_object_v02(),
//      QMI_CLIENT_INSTANCE_ANY,
//      NULL, // ind_cb
//      NULL,
//      NULL,
//      SNS_HDRLL_QMI_TIMEOUT_MS,
//      &reg_qmi_client_handle);
//  if (QMI_NO_ERR != qmi_err)
//  {
//     return -1;
//  }

  //
//  SNS_REG_GROUP_SSI_SMGR_CFG_V02
//  SNS_REG_ITEM_SSI_SMGR_CFG0_UUID_HIGH_V02
//  SNS_REG_ITEM_SSI_SMGR_CFG0_UUID_LOW_V02
//  SNS_REG_ITEM_SSI_SMGR_CFG1_UUID_HIGH_V02
//  SNS_REG_ITEM_SSI_SMGR_CFG1_UUID_LOW_V02

  // TODO: Retrieve the first SMGR SSI group to get the accel and gyro's UUID
//  qmi_err = qmi_client_send_msg_sync(
//      reg_qmi_client_handle,
//   unsigned int       msg_id,
//   void               *req_c_struct,
//   unsigned int       req_c_struct_len,
//   void               *resp_c_struct,
//   unsigned int       resp_c_struct_len,
//   unsigned int       timeout_msecs
//  );
//  if (QMI_NO_ERR != qmi_err)
//  {
//     return -1;
//  }

  // Initialize QMI client with the SMGR Restricted service (for DAF functionality)
  qmi_err = qmi_client_init_instance(
      SNS_SMGR_RESTRICTED_SVC_get_service_object_v01(),
      QMI_CLIENT_INSTANCE_ANY,
      NULL, // ind_cb
      NULL,
      NULL,
      SNS_HDRLL_QMI_TIMEOUT_MS,
      &smgr_res_qmi_client_handle);
  if (QMI_NO_ERR != qmi_err)
  {
    MSG_1(MSG_SSID_SNS,DBG_ERROR_PRIO,"HDRLL - qmi_client_init err %d", qmi_err);
    return -2;
  }

  // Assign the client handle
  *client = smgr_res_qmi_client_handle;

  // Prepare the DAF HDRLL Enable request message
  hdrll_en_req_msg.send_data_cb = send_data_cb;
  hdrll_en_req_msg.handle_error_cb = handle_error_cb;
  hdrll_en_req_msg.hdrll_cb_context = cb_context;
  hdrll_en_req_msg.num_sensor_requests = sensor_requests->num_entries;
  SNS_OS_MEMZERO(hdrll_en_req_msg.sensor_requests, sizeof(hdrll_en_req_msg.sensor_requests));
  for (i = 0; i < hdrll_en_req_msg.num_sensor_requests; i++)
  {
    MSG_3(MSG_SSID_SNS,DBG_HIGH_PRIO,"HDRLL - type %u, odr %u, div %u",
        sensor_requests->table[i].sensor_type,
        sensor_requests->table[i].sensor_odr,
        sensor_requests->table[i].odr_divider);
    hdrll_en_req_msg.sensor_requests[i].sensor_type = sensor_requests->table[i].sensor_type;
    hdrll_en_req_msg.sensor_requests[i].sensor_odr = sensor_requests->table[i].sensor_odr;
    hdrll_en_req_msg.sensor_requests[i].odr_divider = sensor_requests->table[i].odr_divider;
  }

  // Prepare the SMGR Restricted request
  SNS_OS_MEMSCPY( daf_req_msg.Uuid, SNS_SMGR_UUID_LENGTH_V01,
                  bmi160_uuid, 16 );
  daf_req_msg.RequestId = SNS_DAF_HDRLL_ENABLE_V01;
  daf_req_msg.RequestMsg_valid = true;
  daf_req_msg.RequestMsg_len = sizeof(hdrll_en_req_msg);
  SNS_OS_MEMSCPY( (void*)daf_req_msg.RequestMsg, SNS_SMGR_MAX_DAF_MESSAGE_SIZE_V01,
                  (void*)&hdrll_en_req_msg, sizeof(hdrll_en_req_msg) );
  daf_req_msg.TransactionId_valid = false;

  // Send DAF message to QMI client and wait for a response
  qmi_err = qmi_client_send_msg_sync(
      smgr_res_qmi_client_handle,
      SNS_SMGR_DRIVER_ACCESS_REQ_V01,
      (void*)&daf_req_msg,
      sizeof(daf_req_msg),
      (void*)&daf_resp_msg,
      sizeof(daf_resp_msg),
      SNS_HDRLL_QMI_TIMEOUT_MS);
  if (QMI_NO_ERR != qmi_err)
  {
    MSG_1(MSG_SSID_SNS,DBG_ERROR_PRIO,"HDRLL - qmi_client_send_msg err %d", qmi_err);
    return -3;
  }

  // Check the response for any errors
  // TODO: CHECK daf_resp_msg.Resp
  hdrll_en_resp_msg = (sns_daf_hdrll_enable_resp_v01*)daf_resp_msg.ResponseMsg;
  if ( daf_resp_msg.ResponseStatus_valid &&
       (daf_resp_msg.ResponseStatus == SNS_SMGR_DRIVER_ACCESS_STATUS_SUCCESS_V01) &&
       daf_resp_msg.ResponseMsg_valid &&
       (daf_resp_msg.ResponseMsg_len == sizeof(*hdrll_en_resp_msg)) &&
       (hdrll_en_resp_msg->error == 0) )
  {
    // TODO: USE DEMORGANS LAW AND INVERT THE CONDITIONAL ABOVE
  }
  else
  {
    MSG_1(MSG_SSID_SNS,DBG_ERROR_PRIO,"HDRLL - qmi_client_init err %d", qmi_err);
    return -4;
  }

  // Create Interrupt Handler
  if( sns_hdrll_int_handle )
  {
    DAL_DeviceDetach(sns_hdrll_int_handle);
    sns_hdrll_int_handle = 0;
  }
  dal_err = DAL_DeviceAttach( DALDEVICEID_IPCINT, &sns_hdrll_int_handle );
  if( DAL_SUCCESS != dal_err )
  {
    MSG_1(MSG_SSID_SNS,DBG_ERROR_PRIO,"HDRLL - DAL_DeviceAttach err %d", dal_err);
    return -5;
  }
  dal_err = DalIPCInt_IsSupported( sns_hdrll_int_handle, DALIPCINT_PROC_ADSP, DALIPCINT_GP_1 );
  if( DAL_SUCCESS != dal_err )
  {
    MSG_1(MSG_SSID_SNS,DBG_ERROR_PRIO,"HDRLL - DalIPCInt_IsSupported err %d", dal_err);
    return -6;
  }

  return 0;
}


/*===========================================================================

  FUNCTION:   sns_hdrll_disable_hdrll_mode

  ===========================================================================*/
/**
   @brief This function disables HDRLL mode in the SSC.

   @param[in]   client    An opaque handle used to identify this client

   @return
     - 0: client successfully deregistered
     - -1: otherwise
     - all other values are reserved
*/
int
sns_hdrll_disable_hdrll_mode
(
  const sns_hdrll_client_handle      client
)
{
  qmi_client_error_type                qmi_err;
  sns_daf_hdrll_disable_resp_v01*      hdrll_dis_resp_msg;
  sns_smgr_driver_access_req_msg_v01   daf_req_msg;
  sns_smgr_driver_access_resp_msg_v01  daf_resp_msg;
  const uint8_t                        bmi160_uuid[16] = SNS_REG_UUID_BMI160;

  MSG(MSG_SSID_SNS,DBG_HIGH_PRIO,"HDRLL - disable_hdrll_mode");

  // Validate input
  if (NULL == client)
  {
    MSG_1(MSG_SSID_SNS,DBG_ERROR_PRIO,"HDRLL - invalid client 0x%x", client);
    return -1;
  }

  // Prepare the SMGR Restricted request
  // Note: the DAF HDRLL Disable request message is purposefully empty
  SNS_OS_MEMSCPY( daf_req_msg.Uuid, SNS_SMGR_UUID_LENGTH_V01,
                  bmi160_uuid, 16 );
  daf_req_msg.RequestId = SNS_DAF_HDRLL_DISABLE_V01;
  daf_req_msg.RequestMsg_valid = false;
  daf_req_msg.TransactionId_valid = false;

  // Send DAF message to QMI client and wait for a response
  qmi_err = qmi_client_send_msg_sync(
      client,
      SNS_SMGR_DRIVER_ACCESS_REQ_V01,
      (void*)&daf_req_msg,
      sizeof(daf_req_msg),
      (void*)&daf_resp_msg,
      sizeof(daf_resp_msg),
      SNS_HDRLL_QMI_TIMEOUT_MS);
  if (QMI_NO_ERR != qmi_err)
  {
     return -1;
  }

  // Check the response for any errors
  // TODO: CHECK daf_resp_msg.Resp
  hdrll_dis_resp_msg = (sns_daf_hdrll_disable_resp_v01*)daf_resp_msg.ResponseMsg;
  if ( daf_resp_msg.ResponseStatus_valid &&
       (daf_resp_msg.ResponseStatus == SNS_SMGR_DRIVER_ACCESS_STATUS_SUCCESS_V01) &&
       daf_resp_msg.ResponseMsg_valid &&
       (daf_resp_msg.ResponseMsg_len == sizeof(*hdrll_dis_resp_msg)) &&
       (hdrll_dis_resp_msg->error == 0) )
  {
    // TODO: USE DEMORGANS LAW AND INVERT THE CONDITIONAL ABOVE
  }
  else
  {
    return -1;
  }

  // Release the QMI client
  qmi_err = qmi_client_release(client);
  if (QMI_NO_ERR != qmi_err)
  {
     return -1;
  }

  // Note: no need to detach from the interrupt controller, the pin is dedicated

  return 0;
}


/*===========================================================================

  FUNCTION:   sns_hdrll_notify_data_ready

  ===========================================================================*/
/**
   @brief This function will notify the target client that there is data ready
          to be read.

   @return
     - 0: target client was successfully notified
     - -1: otherwise
     - all other values are reserved
*/
int
sns_hdrll_notify_data_ready
( void )
{
  // Send data ready interrupt to ADSP
  DalIPCInt_Trigger(sns_hdrll_int_handle,
                    DALIPCINT_PROC_ADSP,
                    DALIPCINT_GP_1);
  
  sns_profiling_log_qdss(SNS_HDRLL_NOTIFY_DATA_READY, 1, 0);

  return 0;
}


/*===========================================================================

  FUNCTION:   sns_hdrll_get_sensor_rate_info

  ===========================================================================*/
/**
   @brief This function will retrieve the following sensor information
          - supported ODRs
          - corresponding filter delays
          - supported FIFO depth

   @param[in]   sensor_type  The target sensor
   @param[out]  rate_table   Table with the device's ODR and filter delay pairs
   @param[out]  fifo_depth   This will be set to maximum size of the device's
                             hardware FIFO. If the device does not support a
                             hardware FIFO, this will be set to 0.

   @return
     - 0: Sensor rate information was successfully retrieved
     - -1: otherwise
     - all other values are reserved
*/
int
sns_hdrll_get_sensor_rate_info
(
  sns_hdrll_sensor_type_e              sensor_type,
  sns_hdrll_sensor_rate_delay_table*   rate_table,
  unsigned int*                        fifo_depth
)
{
  qmi_client_error_type                qmi_err;
  qmi_client_type                      smgr_res_qmi_client_handle;
  sns_daf_hdrll_get_sensor_rate_info_req_v01   hdrll_sensor_info_req_msg;
  sns_daf_hdrll_get_sensor_rate_info_resp_v01* hdrll_sensor_info_resp_msg_ptr;
  sns_smgr_driver_access_req_msg_v01   daf_req_msg;
  sns_smgr_driver_access_resp_msg_v01  daf_resp_msg;
  // PEND: This assumes that the caller
  const uint8_t                        bmi160_uuid[16] = SNS_REG_UUID_BMI160;

  MSG(MSG_SSID_SNS,DBG_HIGH_PRIO,"HDRLL - get_sensor_rate_info");

  // Validate input
  if ( (NULL == rate_table) || (NULL == fifo_depth) )
  {
    return -1;
  }

  // Initialize QMI client with the SMGR Restricted service (for DAF functionality)
  qmi_err = qmi_client_init_instance(
      SNS_SMGR_RESTRICTED_SVC_get_service_object_v01(),
      QMI_CLIENT_INSTANCE_ANY,
      NULL, // ind_cb
      NULL,
      NULL,
      SNS_HDRLL_QMI_TIMEOUT_MS,
      &smgr_res_qmi_client_handle);
  if (QMI_NO_ERR != qmi_err)
  {
     return -1;
  }

  // Prepare the DAF HDRLL Sensor Rate Info request message
  hdrll_sensor_info_req_msg.sensor_type = sensor_type;

  // Prepare the SMGR Restricted request
  SNS_OS_MEMSCPY( daf_req_msg.Uuid, SNS_SMGR_UUID_LENGTH_V01,
                  bmi160_uuid, 16 );
  daf_req_msg.RequestId = SNS_DAF_HDRLL_GET_SENSOR_RATE_INFO_V01;
  daf_req_msg.RequestMsg_valid = true;
  daf_req_msg.RequestMsg_len = sizeof(hdrll_sensor_info_req_msg);
  SNS_OS_MEMSCPY( (void*)daf_req_msg.RequestMsg, SNS_SMGR_MAX_DAF_MESSAGE_SIZE_V01,
                  (void*)&hdrll_sensor_info_req_msg, sizeof(hdrll_sensor_info_req_msg) );
  daf_req_msg.TransactionId_valid = false;

  // Send DAF message to QMI client and wait for a response
  qmi_err = qmi_client_send_msg_sync(
      smgr_res_qmi_client_handle,
      SNS_SMGR_DRIVER_ACCESS_REQ_V01,
      (void*)&daf_req_msg,
      sizeof(daf_req_msg),
      (void*)&daf_resp_msg,
      sizeof(daf_resp_msg),
      SNS_HDRLL_QMI_TIMEOUT_MS);
  if (QMI_NO_ERR != qmi_err)
  {
     return -1;
  }

  // Check the response for any errors
  // TODO: CHECK daf_resp_msg.Resp
  hdrll_sensor_info_resp_msg_ptr = (sns_daf_hdrll_get_sensor_rate_info_resp_v01*)daf_resp_msg.ResponseMsg;
  if ( daf_resp_msg.ResponseStatus_valid &&
       (daf_resp_msg.ResponseStatus == SNS_SMGR_DRIVER_ACCESS_STATUS_SUCCESS_V01) &&
       daf_resp_msg.ResponseMsg_valid &&
       (daf_resp_msg.ResponseMsg_len == sizeof(*hdrll_sensor_info_resp_msg_ptr)) )
  {
    // TODO: USE DEMORGANS LAW AND INVERT THE CONDITIONAL ABOVE
    // If the response is successfully received, fill the output params
    int i = 0;
    *fifo_depth = hdrll_sensor_info_resp_msg_ptr->fifo_depth;

    for (i = 0; (i < rate_table->max_entries) &&
                (i < hdrll_sensor_info_resp_msg_ptr->num_entries) &&
                (i < SNS_HDRLL_MAX_TBL_SIZE); i++)
    {
      rate_table->table[i] = hdrll_sensor_info_resp_msg_ptr->table[i];
    }
    *(rate_table->num_entries) = i;
  }
  else
  {
    return -1;
  }

  // Release the QMI client
  qmi_err = qmi_client_release(smgr_res_qmi_client_handle);
  if (QMI_NO_ERR != qmi_err)
  {
     return -1;
  }

  return 0;
}


/*===========================================================================

  FUNCTION:   sns_hdrll_ssc_to_qtimer_ticks

  ===========================================================================*/
/**
   @brief This function converts a value in SSC-ticks (32 KHz clock) into an
          equivalent value in QTimer-ticks (based on the 19.2 MHz global counter)

   @return Value in QTimer-ticks
*/
uint64_t sns_hdrll_ssc_to_qtimer_ticks
(
  uint64_t ssc_ticks
)
{
  return sns_em_convert_dspstick_to_qtimertick(ssc_ticks);
}
