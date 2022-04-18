/*============================================================================
  @file sns_low_lat.c

  @brief
  API functions, data structures, and constants used by the Low Latency Stream
  Library

  @note
  File line length should generally be limited to <= 80 columns.

  Copyright (c) 2016-2017 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
  ===========================================================================*/

#include "sns_low_lat.h"
#include "sns_low_lat_buffer.h"
#include "sns_low_lat_priv.h"

#include <comdef.h>
// PEND: Consider using sns_osa instead of qurt_signal2 (for portability)
#include <qurt_signal2.h>
#include <DDIIPCInt.h>
#include <qmi_idl_lib.h>

#include "sns_debug_str.h"
#include "sns_usmr.h"
#include "sns_em.h"
#include "sns_smgr_api_v01.h"
#include "sns_smgr_common_v01.h"
#include "sns_profiling.h"
#include "sns_memmgr.h"
#include "fixed_point.h"
#include "sns_log_api_public.h"
#include "sns_log_types.h"
#include "tracer_event_ids.h"
#include "qurt_thread.h"

//#define SNS_LOW_LAT_DEBUG

#define SNS_LOW_LAT_US_PER_SEC               1000000

#define SNS_LOW_LAT_SMR_CLIENT_INIT_TIMEOUT  0
#define SNS_LOW_LAT_MAX_SAMPLE_RATE_HZ       1000
#define SNS_LOW_LAT_MIN_SAMPLE_PERIOD_US     SNS_LOW_LAT_US_PER_SEC / SNS_LOW_LAT_MAX_SAMPLE_RATE_HZ
#define SNS_LOW_LAT_MIN_SAMPLE_RATE_HZ       1
#define SNS_LOW_LAT_MAX_SAMPLE_PERIOD_US     SNS_LOW_LAT_US_PER_SEC / SNS_LOW_LAT_MIN_SAMPLE_RATE_HZ

#define SNS_LOW_LAT_SIGNAL_RESP              0x00000001
#define SNS_LOW_LAT_SIGNAL_IND               0x00000002
#define SNS_LOW_LAT_SIGNAL_RELEASE           0x00000004
#define SNS_LOW_LAT_SIGNAL_CANCEL_POLL       0x00000008

// The maximum amount of open low-lat streams
// 5 was arbitrarily chosen
#define SNS_LOW_LAT_MAX_STREAMS              5

// Defined in dsp_cache.S
void cache_clean(void* addr, int size);
//void cache_invalidate(void *addr, int size);


typedef struct sns_low_lat_stream
{
  // Pointer to the output buffer, must be a non-NULL value
  // If this value is NULL, then the entire stream state is invalid
  void*            output_buf;
  unsigned int     output_buf_size;
  // PEND: OS_EVENT         output_buf_mutex;
  unsigned int     flags;
  // Signal used to wait on responses and indications
  qurt_signal2_t   signal;
  smr_client_hndl  smr_handle;
  DalDeviceHandle* interrupt_handle;
} sns_low_lat_stream;


// PEND: For now we're using an pre-allocated list to manage the existing
//       streams. This was done to avoid any memory management. But ideally,
//       this library would allocate and deallocate memory, as needed.
// PEND: This should be mutex protected
STATIC sns_low_lat_stream sns_low_lat_stream_list[SNS_LOW_LAT_MAX_STREAMS];


/**
 * @brief
 * This utility function is used to find the first available slot in the list
 * of
 *
 * @param[i] transp_err Error code
 *
 * @return Index of a the first available slot
 *         -1, otherwise
 */
STATIC void sns_low_lat_init_circ_buf(sns_low_lat_stream* stream, uint32_t num_sensors)
{
  sns_low_lat_circ_buf* circ_buf = (sns_low_lat_circ_buf*) stream->output_buf;
  uint32_t max_num_samples = (stream->output_buf_size - sizeof(circ_buf->header)) / sizeof(circ_buf->samples[0]);

  // PEND: Verify that the size of the buffer can indeed fit the number of samples (e.g. max_samples should not be 0)
  // Limit the max_samples such that all concurrent sensor samples lie
  // contiguously within the buffer
  circ_buf->header.info.max_samples = (max_num_samples / num_sensors) * num_sensors;
  circ_buf->header.info.most_recent_index = circ_buf->header.info.max_samples;

  MSG_1(MSG_SSID_SNS,DBG_HIGH_PRIO,"sns_low_lat_init_circ_buf - max_samples %d", circ_buf->header.info.max_samples);
}

/**
 * @brief
 * This utility function is used to find the first available slot in the list
 * of
 *
 * @param[i] transp_err Error code
 *
 * @return Index of a the first available slot
 *         -1, otherwise
 */
STATIC void sns_low_lat_insert_sample(sns_low_lat_stream* stream,
                                      sns_low_lat_sample* sample)
{
  sns_low_lat_circ_buf* circ_buf = (sns_low_lat_circ_buf*) stream->output_buf;
  uint32_t              new_sample_index;

  // Insert the sample after the most recent sample and check for rollovers
  new_sample_index = (circ_buf->header.info.most_recent_index + 1) % circ_buf->header.info.max_samples;

  // Log the QDSS event if it's a gyro sample
  if (sample->sensor_type == SNS_LOW_LAT_GYRO)
  {
    tracer_event_simple_vargs(SNS_LOWLATENCY_GYRO_IDX, 2, (uint32_t)qurt_thread_get_id(),new_sample_index);
  }

  SNS_OS_MEMSCPY(&circ_buf->samples[new_sample_index].data,
      sizeof(circ_buf->samples[new_sample_index].data),
      sample,
      sizeof(*sample));

  // Clean the cache
  // PEND: Consider doing the cache_clean at the end of the handle_ind function (better performance)
  cache_clean(&circ_buf->samples[new_sample_index],
      sizeof(circ_buf->samples[new_sample_index]));
//  cache_clean(&circ_buf->header,
//              sizeof(circ_buf->header));

  circ_buf->header.info.most_recent_index = new_sample_index;

}

/**
 * @brief
 * This utility function is used to find the first available slot in the list
 * of
 *
 * @return Index of a the first available slot
 *         -1, otherwise
 */
STATIC int sns_low_lat_find_open_slot(void)
{
  int i, ret = -1;

  for (i = 0; i < ARR_SIZE(sns_low_lat_stream_list); i++)
  {
    if (NULL == sns_low_lat_stream_list[i].output_buf)
    {
      ret = i;
      break;
    }
  }

  return ret;
};

/*===========================================================================

  FUNCTION:   sns_low_lat_notify_data_ready

  ===========================================================================*/
/**
   @brief This function will notify the target client that there is data ready
          to be read.
*/
STATIC void sns_low_lat_notify_data_ready(sns_low_lat_stream* stream)
{
  // Send data ready interrupt to ADSP
  DalIPCInt_Trigger(stream->interrupt_handle,
      DALIPCINT_PROC_ADSP,
      DALIPCINT_GP_1);
}


/**
 * @brief
 * This callback function is called by the SMR infrastructure when a connection
 * is fully released.
 *
 * @param[i] release_cb_data cookie provided in smr_client_release()
 */
STATIC void sns_low_lat_release_cb(void *release_cb_data)
{
  int stream_id = (int) release_cb_data;

  // Validate input
  if ( (-1 == stream_id) ||
       (stream_id >= ARR_SIZE(sns_low_lat_stream_list)) ||
       (NULL == sns_low_lat_stream_list[stream_id].output_buf) )
  {
    MSG_1(MSG_SSID_SNS,DBG_ERROR_PRIO,"sns_low_lat_release_cb - invalid stream_id %d", stream_id);
    return;
  }

  // Signal that the response has been received
  qurt_signal2_set(&sns_low_lat_stream_list[stream_id].signal,
      SNS_LOW_LAT_SIGNAL_RELEASE);
}

/**
 * @brief
 * This callback function is called by the SMR infrastructure when a response
 * is received after a request is sent using smr_client_send_req()
 *
 * @param[i] client_handle Handle used by the infrastructure to identify different clients.
 * @param[i] msg_id Message ID
 * @param[i] resp_c_struct Pointer to the response
 * @param[i] resp_c_struct_len Length of the response
 * @param[i] resp_cb_data User-data
 * @param[i] transp_err Error code
 */
STATIC void sns_low_lat_resp_cb(smr_client_hndl client_handle,
                                unsigned int msg_id,
                                void *resp_c_struct,
                                unsigned int resp_c_struct_len,
                                void *resp_cb_data,
                                smr_err transp_err)
{
  int stream_id = (int) resp_cb_data;

  // Validate input
  if ( (-1 == stream_id) ||
       (stream_id >= ARR_SIZE(sns_low_lat_stream_list)) ||
       (NULL == sns_low_lat_stream_list[stream_id].output_buf) )
  {
    MSG_1(MSG_SSID_SNS,DBG_ERROR_PRIO,"sns_low_lat_resp_cb - invalid stream_id %d", stream_id);
    return;
  }

  // Signal that the response has been received
  qurt_signal2_set(&sns_low_lat_stream_list[stream_id].signal,
                   SNS_LOW_LAT_SIGNAL_RESP);
}

/**
 * @brief
 * This callback function is called by the SMR infrastructure when an
 * indication is received. This callback is registered at initialization.
 *
 * @param[i] client_handle Handle used by the infrastructure to identify different clients.
 * @param[i] msg_id Message ID
 * @param[i] ind_buf Pointer to the raw/undecoded indication
 * @param[i] ind_buf_len Length of the indication
 * @param[i] resp_cb_data User-data
 */
STATIC void sns_low_lat_ind_cb(smr_client_hndl client_handle,
                               unsigned int msg_id,
                               void *ind_c_struct,
                               unsigned int ind_struct_len,
                               void *ind_cb_data)
{
  int stream_id = (int) ind_cb_data;
  int num_samples = 0;

#ifdef SNS_LOW_LAT_DEBUG
  static unsigned int num_inds_received;
  //MSG_1(MSG_SSID_SNS,DBG_ERROR_PRIO,"sns_low_lat_ind_cb - hooked=%d", g_sensor_hooked );
#endif /* SNS_LOW_LAT_DEBUG */

  // Validate input
  // PEND: Cross-check the client_handle to make sure it matches?
  if ( (-1 == stream_id) ||
       (stream_id >= ARR_SIZE(sns_low_lat_stream_list)) ||
       (NULL == sns_low_lat_stream_list[stream_id].output_buf) )
  {
    MSG_1(MSG_SSID_SNS,DBG_ERROR_PRIO,"sns_low_lat_ind_cb - invalid stream_id %d", stream_id);
    return;
  }

  if (SNS_SMGR_BUFFERING_IND_V01 == msg_id)
  {
    sns_low_lat_sample sample;
    sns_smgr_buffering_ind_msg_v01* ind = ind_c_struct;
    int i, j;
    uint8_t ind_sample_index;
    uint64_t ind_sample_ts;

    // Cross-check the ReportId to make sure it matches the stream_id
    if ( (ind_struct_len < sizeof(*ind)) || (ind->ReportId != stream_id) )
    {
      // Something funny is happening here...
      MSG_3(MSG_SSID_SNS,DBG_ERROR_PRIO,"sns_low_lat_ind_cb - unexpected report! ind_struct_len %d report_id %d stream_id %d",
          ind_struct_len, ind->ReportId, stream_id);
      return;
    }

    // Pull the data from the indication
    for (i = 0; (i < ind->Indices_len) && (i < SNS_SMGR_BUFFERING_REQUEST_MAX_ITEMS_V01); i++)
    {
      if ( (SNS_SMGR_ID_ACCEL_V01 == ind->Indices[i].SensorId) &&
           (SNS_SMGR_DATA_TYPE_PRIMARY_V01 == ind->Indices[i].DataType) )
      {
        sample.sensor_type = SNS_LOW_LAT_ACCEL;
      }
      else if ( (SNS_SMGR_ID_GYRO_V01 == ind->Indices[i].SensorId) &&
                (SNS_SMGR_DATA_TYPE_PRIMARY_V01 == ind->Indices[i].DataType) )
      {
        sample.sensor_type = SNS_LOW_LAT_GYRO;
      }
      else
      {
        // Skip the unrecognized sensor
        MSG_2(MSG_SSID_SNS,DBG_ERROR_PRIO,"sns_low_lat_ind_cb - unsupported sensor SensorId %d DataType %d",
            ind->Indices[i].SensorId, ind->Indices[i].DataType);
        continue;
      }

      ind_sample_index = ind->Indices[i].FirstSampleIdx;
      ind_sample_ts = (uint64_t) ind->Indices[i].FirstSampleTimestamp;
      for (j = 0; j < ind->Indices[i].SampleCount; j++, ind_sample_index++)
      {
        // PEND: Check against ind->Samples_len and SNS_SMGR_BUFFERING_REPORT_MAX_SAMPLES_V01
        ind_sample_ts += ind->Samples[ind_sample_index].TimeStampOffset;
        sample.timestamp = sns_em_convert_dspstick_to_qtimertick(ind_sample_ts);

        // Convert from SAE to Android coordinates and scale
        // x' = y; y' = x; z' = -z;
        sample.sample[0] = FX_FIXTOFLT_Q16_SP(ind->Samples[ind_sample_index].Data[1]);
        sample.sample[1] = FX_FIXTOFLT_Q16_SP(ind->Samples[ind_sample_index].Data[0]);
        sample.sample[2] = FX_FIXTOFLT_Q16_SP(-ind->Samples[ind_sample_index].Data[2]);

        // Write the data to the output buffer
        sns_low_lat_insert_sample(&sns_low_lat_stream_list[stream_id], &sample);

        num_samples++;

#ifdef SNS_LOW_LAT_DEBUG
  //MSG_1(MSG_SSID_SNS,DBG_HIGH_PRIO,"sns_low_lat_ind_cb - samp_ts %u", sample.timestamp);
#endif /* SNS_LOW_LAT_DEBUG */
      }
    }
  }

  if (num_samples > 0)
  {
    // Clean the cache
    sns_low_lat_circ_buf* circ_buf = (sns_low_lat_circ_buf*) sns_low_lat_stream_list[stream_id].output_buf;
    cache_clean(&circ_buf->header,
                sizeof(circ_buf->header));

    // Fire off the interrupt, if necessary
    if (sns_low_lat_stream_list[stream_id].flags & SNS_LOW_LAT_START_FLAG_INTERRUPT_EN)
    {
      sns_low_lat_notify_data_ready(&sns_low_lat_stream_list[stream_id]);
    }

    // Log a QDSS event for the sample
    sns_profiling_log_qdss(SNS_HDRLL_NOTIFY_DATA_READY, 1, 0);

    // Signal that the indication has been received and that there is a new sample
    // in the buffer. This signal is used by clients that actively poll the
    // low-lat library.
    qurt_signal2_set(&sns_low_lat_stream_list[stream_id].signal,
                     SNS_LOW_LAT_SIGNAL_IND);

    // Log the data
    // Note: We avoid the sns_logpkt_submit() function because it uses a highly
    //       inefficient linear search to see if the log packet is enabled
    sns_err_code_e log_err;
    sns_log_hdrll_data_v2* log_pkt;

    log_err = sns_logpkt_malloc((log_pkt_t)SNS_LOG_HDRLL_DATA, sizeof(*log_pkt), (void**) &log_pkt);

    if (SNS_SUCCESS == log_err)
    {
      int a;
      uint32_t prev_sample_idx;

      log_pkt->version = SNS_LOG_HDRLL_DATA_VERSION;
      if (SNS_LOW_LAT_ACCEL == circ_buf->samples[circ_buf->header.info.most_recent_index].data.sensor_type)
      {
        log_pkt->sensor_id_1 = 1;
      }
      else
      {
        log_pkt->sensor_id_1 = 3;
      }
      log_pkt->timestamp_1 = sns_em_convert_qtimertick_to_dspstick(circ_buf->samples[circ_buf->header.info.most_recent_index].data.timestamp);
      for (a = 0; a < SNS_LOG_HDRLL_DATA_NUM_AXES; a++)
      {
        log_pkt->data_1[a] = FX_FLTTOFIX_Q16(circ_buf->samples[circ_buf->header.info.most_recent_index].data.sample[a]);
      }
      if (num_samples > 1)
      {
        // Check for rollovers when trying to access the previous sample
        if (0 == circ_buf->header.info.most_recent_index)
        {
          prev_sample_idx = circ_buf->header.info.max_samples - 1;
        }
        else
        {
          prev_sample_idx = circ_buf->header.info.most_recent_index - 1;
        }

        if (SNS_LOW_LAT_ACCEL == circ_buf->samples[prev_sample_idx].data.sensor_type)
        {
          log_pkt->sensor_id_2 = 1;
        }
        else
        {
          log_pkt->sensor_id_2 = 3;
        }
        log_pkt->timestamp_2 = sns_em_convert_qtimertick_to_dspstick(circ_buf->samples[prev_sample_idx].data.timestamp);
        for (a = 0; a < SNS_LOG_HDRLL_DATA_NUM_AXES; a++)
        {
          log_pkt->data_2[a] = FX_FLTTOFIX_Q16(circ_buf->samples[prev_sample_idx].data.sample[a]);
        }
      }
      log_pkt->stream_id = stream_id;
      log_pkt->log_timestamp_type = SNS_TIMESTAMP_DSPS;
      log_pkt->log_timestamp = sns_em_get_system_time();

      sns_logpkt_commit((log_pkt_t)SNS_LOG_HDRLL_DATA, log_pkt);
    }
  }

#ifdef SNS_LOW_LAT_DEBUG
  ++num_inds_received;

  if ((num_inds_received % 100) == 0)
  {
    MSG_1(MSG_SSID_SNS,DBG_HIGH_PRIO,"low_lat - # ind received %d", num_inds_received);
  }
#endif /* SNS_LOW_LAT_DEBUG */
}

/**
 * @brief
 * This callback function is called by the SMR infrastructure when the service
 * terminates or deregisters
 *
 * @param[i] client_handle Handle used by the infrastructure to identify different clients.
 * @param[i] error Error code
 * @param[i] err_cb_data User-data
 */
STATIC void sns_low_lat_error_cb (smr_client_hndl client_handle,
                                  smr_err error,
                                  void *err_cb_data)
{
  int stream_id = (int) err_cb_data;

  MSG_1(MSG_SSID_SNS,DBG_ERROR_PRIO,"sns_low_lat_error_cb - error %d", error);

  // Validate input
  // PEND: Check the client_handle to make sure it matches?
  if ( (-1 == stream_id) ||
       (stream_id >= ARR_SIZE(sns_low_lat_stream_list)) ||
       (NULL == sns_low_lat_stream_list[stream_id].output_buf) )
  {
    MSG_1(MSG_SSID_SNS,DBG_ERROR_PRIO,"sns_low_lat_error_cb - invalid stream_id %d", stream_id);
    return;
  }

  // PEND: Reflect this error to the client by inserting a code into the output stream
}

int sns_low_lat_enable(void* output_buf,
                       unsigned int output_buf_size,
                       unsigned int output_buf_offset,
                       const uint64* sensor_suid,
                       int sensor_suidLen,
                       unsigned int sample_period_us,
                       unsigned int flags,
                       int* stream_id)
{
  qmi_idl_service_object_type     service_obj;
  sns_smgr_buffering_req_msg_v01  smgr_req_msg;
  sns_smgr_buffering_resp_msg_v01 smgr_resp_msg;
  uint64_t                        suid = 0;
  float                           sample_rate_hz = 0.0;
  int                             stream_slot;
  smr_err                         smr_error;
  smr_txn_handle                  smr_txn_handle;
  unsigned int                    signal;
  DALResult                       dal_err;
  int i;

  MSG(MSG_SSID_SNS,DBG_HIGH_PRIO,"sns_low_lat_enable");

  // Validate inputs
  if ( (NULL == output_buf) ||
       (output_buf_size <= 0) ||
       (NULL == sensor_suid) ||
       (sensor_suidLen <= 0) ||
       (sample_period_us < SNS_LOW_LAT_MIN_SAMPLE_PERIOD_US) ||
       (sample_period_us > SNS_LOW_LAT_MAX_SAMPLE_PERIOD_US) ||
       (NULL == stream_id) )
  {
    MSG_3(MSG_SSID_SNS,DBG_ERROR_PRIO,"low_lat - invalid inputs 0x%x %d 0x%0x",
          output_buf, output_buf_size, sensor_suid);
    MSG_2(MSG_SSID_SNS,DBG_ERROR_PRIO,"low_lat - invalid inputs %d 0x%x",
          sample_period_us, stream_id);
    return -1;
  }

  // Initialize the stream_id
  *stream_id = -1;

  // Find an open slot in the stream list
  stream_slot = sns_low_lat_find_open_slot();

  // If an open slot can't be found, then return an error code
  if (stream_slot < 0)
  {
    MSG_1(MSG_SSID_SNS,DBG_ERROR_PRIO,"low_lat - no open slot %d", stream_slot);
    return -2;
  }

  MSG_1(MSG_SSID_SNS,DBG_HIGH_PRIO,"sns_low_lat_enable - using stream slot %d", stream_slot);

  sns_low_lat_stream_list[stream_slot].output_buf = (void*) ((unsigned int)output_buf + output_buf_offset);
  sns_low_lat_stream_list[stream_slot].output_buf_size = output_buf_size;
  sns_low_lat_stream_list[stream_slot].flags = flags;
  sns_low_lat_stream_list[stream_slot].interrupt_handle = NULL;
  qurt_signal2_init(&sns_low_lat_stream_list[stream_slot].signal);
  sns_low_lat_init_circ_buf(&sns_low_lat_stream_list[stream_slot], sensor_suidLen);
  *stream_id = stream_slot;

  // If the client is asking for interrupts
  // Create Interrupt Handler
  if (flags & SNS_LOW_LAT_START_FLAG_INTERRUPT_EN)
  {
    dal_err = DAL_DeviceAttach( DALDEVICEID_IPCINT, &sns_low_lat_stream_list[stream_slot].interrupt_handle );
    if( DAL_SUCCESS != dal_err )
    {
      MSG_1(MSG_SSID_SNS,DBG_ERROR_PRIO,"low_lat - DAL_DeviceAttach err %d", dal_err);
      return -3;
    }
    dal_err = DalIPCInt_IsSupported( sns_low_lat_stream_list[stream_slot].interrupt_handle, DALIPCINT_PROC_ADSP, DALIPCINT_GP_1 );
    if( DAL_SUCCESS != dal_err )
    {
      MSG_1(MSG_SSID_SNS,DBG_ERROR_PRIO,"low_lat - DalIPCInt_IsSupported err %d", dal_err);
      return -4;
    }

    MSG(MSG_SSID_SNS,DBG_HIGH_PRIO,"sns_low_lat_enable - interrupt enabled");
  }

  // Generate the request message
  service_obj = SNS_SMGR_SVC_get_service_object_v01();
  // PEND: The report ID shouldn't matter in this case, because each client will only have 1 report, but we have it here for verification purposes
  smgr_req_msg.ReportId = stream_slot; //0;
  smgr_req_msg.Action = SNS_SMGR_BUFFERING_ACTION_ADD_V01;
  sample_rate_hz = (float) SNS_LOW_LAT_US_PER_SEC / (float) sample_period_us;
  smgr_req_msg.ReportRate = FX_FLTTOFIX_Q16(sample_rate_hz);
  smgr_req_msg.Item_len = 0;
  smgr_req_msg.notify_suspend_valid = TRUE;
  smgr_req_msg.notify_suspend.proc_type = SNS_PROC_SSC_V01;
  smgr_req_msg.notify_suspend.send_indications_during_suspend = TRUE;
  smgr_req_msg.SrcModule_valid = FALSE;

  for (i = 0; i < sensor_suidLen; i++)
  {
    suid = sensor_suid[i];
    switch (suid)
    {
      case SNS_SMGR_SUID_ACCEL_1_V01:
      {
        MSG(MSG_SSID_SNS,DBG_HIGH_PRIO,"low_lat - adding accel");
        smgr_req_msg.Item[smgr_req_msg.Item_len].SensorId = SNS_SMGR_ID_ACCEL_V01;
        smgr_req_msg.Item[smgr_req_msg.Item_len].DataType = SNS_SMGR_DATA_TYPE_PRIMARY_V01;
        smgr_req_msg.Item[smgr_req_msg.Item_len].Decimation = SNS_SMGR_DECIMATION_FILTER_V01;
        smgr_req_msg.Item[smgr_req_msg.Item_len].Calibration = SNS_SMGR_CAL_SEL_FACTORY_CAL_V01;
        smgr_req_msg.Item[smgr_req_msg.Item_len].SamplingRate = (uint16_t) sample_rate_hz;
        smgr_req_msg.Item[smgr_req_msg.Item_len].SampleQuality = SNS_SMGR_SAMPLE_QUALITY_ACCURATE_TIMESTAMP_V01;
        break;
      }
      case SNS_SMGR_SUID_GYRO_1_V01:
      {
        MSG(MSG_SSID_SNS,DBG_HIGH_PRIO,"low_lat - adding gyro");
        smgr_req_msg.Item[smgr_req_msg.Item_len].SensorId = SNS_SMGR_ID_GYRO_V01;
        smgr_req_msg.Item[smgr_req_msg.Item_len].DataType = SNS_SMGR_DATA_TYPE_PRIMARY_V01;
        smgr_req_msg.Item[smgr_req_msg.Item_len].Decimation = SNS_SMGR_DECIMATION_FILTER_V01;
        smgr_req_msg.Item[smgr_req_msg.Item_len].Calibration = SNS_SMGR_CAL_SEL_FACTORY_CAL_V01;
        smgr_req_msg.Item[smgr_req_msg.Item_len].SamplingRate = (uint16_t) sample_rate_hz;
        smgr_req_msg.Item[smgr_req_msg.Item_len].SampleQuality = SNS_SMGR_SAMPLE_QUALITY_ACCURATE_TIMESTAMP_V01;
        break;
      }
      default:
      {
        // Unsupported SUID
        MSG_1(MSG_SSID_SNS,DBG_ERROR_PRIO,"sns_low_lat_enable - unsupported SUID 0x%x", suid);
        return -5;
      }
    }
    smgr_req_msg.Item_len++;
  }

  // Initialize the SMR client
  smr_error = smr_client_init(service_obj,
      SMR_CLIENT_INSTANCE_ANY,
      sns_low_lat_ind_cb,
      (void *) stream_slot,
      SNS_LOW_LAT_SMR_CLIENT_INIT_TIMEOUT,
      sns_low_lat_error_cb,
      (void *) stream_slot,
      &sns_low_lat_stream_list[stream_slot].smr_handle,
      FALSE);
  if (SMR_NO_ERR != smr_error)
  {
    MSG_1(MSG_SSID_SNS,DBG_ERROR_PRIO,"low_lat - smr client init err %d", smr_error);
    return -6;
  }

  // Send in the request message
  smr_error = smr_client_send_req(sns_low_lat_stream_list[stream_slot].smr_handle,
      SNS_SMGR_BUFFERING_REQ_V01,
      &smgr_req_msg,
      sizeof(smgr_req_msg),
      &smgr_resp_msg,
      sizeof(smgr_resp_msg),
      sns_low_lat_resp_cb,
      (void *) stream_slot,
      &smr_txn_handle);
  if (SMR_NO_ERR != smr_error)
  {
    MSG_1(MSG_SSID_SNS,DBG_ERROR_PRIO,"low_lat - smr send req err %d", smr_error);
    return -7;
  }

  // Wait for the response message
  // PEND: Check the returned signal to verify that the right signal was hit
  signal = qurt_signal2_wait_any(&sns_low_lat_stream_list[stream_slot].signal,
      SNS_LOW_LAT_SIGNAL_RESP);
  qurt_signal2_clear(&sns_low_lat_stream_list[stream_slot].signal,
      SNS_LOW_LAT_SIGNAL_RESP);

  // Check the response message for any errors
  if ( (0 != smgr_resp_msg.Resp.sns_result_t) ||
       (SENSOR1_SUCCESS != smgr_resp_msg.Resp.sns_err_t) ||
       ( (smgr_resp_msg.AckNak_valid) &&
         (SNS_SMGR_RESPONSE_ACK_SUCCESS_V01 != smgr_resp_msg.AckNak) &&
         (SNS_SMGR_RESPONSE_ACK_MODIFIED_V01 != smgr_resp_msg.AckNak) ) )
  {
    // TODO: Clean up
    MSG_1(MSG_SSID_SNS,DBG_ERROR_PRIO,"low_lat - resp error %d", smgr_resp_msg.Resp.sns_err_t);
    return -8;
  }

  // Check the reason codes if request was modified
  if ( smgr_resp_msg.AckNak_valid &&
       (SNS_SMGR_RESPONSE_ACK_MODIFIED_V01 == smgr_resp_msg.AckNak) )
  {
    for (i = 0; i < smgr_resp_msg.ReasonPair_len; i++ )
    {
      MSG_3(MSG_SSID_SNS,DBG_HIGH_PRIO,"low_lat - resp reasons #%d item %u reason %u",
          i, smgr_resp_msg.ReasonPair[i].ItemNum, smgr_resp_msg.ReasonPair[i].Reason);
    }
  }

  return 0;
}

int sns_low_lat_disable(int stream_id)
{
  qmi_idl_service_object_type     service_obj;
  sns_smgr_buffering_req_msg_v01  smgr_req_msg;
  sns_smgr_buffering_resp_msg_v01 smgr_resp_msg;
  smr_err                         smr_error;
  smr_txn_handle                  smr_txn_handle;
  unsigned int                    signal;

  MSG_1(MSG_SSID_SNS,DBG_HIGH_PRIO,"sns_low_lat_disable - stream_id %d", stream_id);

  // Validate input
  if ( (-1 == stream_id) || (stream_id >= ARR_SIZE(sns_low_lat_stream_list)) )
  {
    MSG_1(MSG_SSID_SNS,DBG_ERROR_PRIO,"sns_low_lat_disable - invalid input, stream_id %d", stream_id);
    return -1;
  }

  // Signal that will cancel any pending polling call
  // The reason we cancel pending polling calls is because QURT forbids
  // multiple threads from waiting on the same signal. If there's a pending
  // call to sns_low_lat_poll, then this stream's signal will be in use. This
  // will prevent us from waiting on response messages
  qurt_signal2_set(&sns_low_lat_stream_list[stream_id].signal,
      SNS_LOW_LAT_SIGNAL_CANCEL_POLL);

  // Generate the disable request message
  service_obj = SNS_SMGR_SVC_get_service_object_v01();
  // PEND: The report ID shouldn't matter in this case, because each client will only have 1 report, but we have it here for verification purposes
  smgr_req_msg.ReportId = stream_id; //0;
  smgr_req_msg.Action = SNS_SMGR_BUFFERING_ACTION_DELETE_V01;
  smgr_req_msg.Item_len = 0;
  smgr_req_msg.notify_suspend_valid = FALSE;
  smgr_req_msg.SrcModule_valid = FALSE;

  // Send in the request message
  smr_error = smr_client_send_req(sns_low_lat_stream_list[stream_id].smr_handle,
      SNS_SMGR_BUFFERING_REQ_V01,
      &smgr_req_msg,
      sizeof(smgr_req_msg),
      &smgr_resp_msg,
      sizeof(smgr_resp_msg),
      sns_low_lat_resp_cb,
      (void *) stream_id,
      &smr_txn_handle);
  if (SMR_NO_ERR != smr_error)
  {
    MSG_1(MSG_SSID_SNS,DBG_ERROR_PRIO,"sns_low_lat_disable - smr send req err %d", smr_error);
  }

  // Wait for the response message
  // PEND: Check the returned signal to verify that the right signal was hit
  signal = qurt_signal2_wait_any(&sns_low_lat_stream_list[stream_id].signal,
      SNS_LOW_LAT_SIGNAL_RESP);
  qurt_signal2_clear(&sns_low_lat_stream_list[stream_id].signal,
      SNS_LOW_LAT_SIGNAL_RESP);

  // Release the SMR client
  smr_error = smr_client_release(sns_low_lat_stream_list[stream_id].smr_handle,
      sns_low_lat_release_cb,
      (void*) stream_id);
  if (SMR_NO_ERR != smr_error)
  {
    // Just print a warning message to the user and continue with the disabling
    MSG_1(MSG_SSID_SNS,DBG_ERROR_PRIO,"sns_low_lat_disable - smr client release error %d", smr_error);
  }

  // Wait for the client release to complete
  signal = qurt_signal2_wait_any(&sns_low_lat_stream_list[stream_id].signal,
      SNS_LOW_LAT_SIGNAL_RELEASE);
  qurt_signal2_clear(&sns_low_lat_stream_list[stream_id].signal,
      SNS_LOW_LAT_SIGNAL_RELEASE);

  // Detach from the interrupt
  if( sns_low_lat_stream_list[stream_id].interrupt_handle )
  {
    DAL_DeviceDetach(sns_low_lat_stream_list[stream_id].interrupt_handle);
  }

  // Reset the stream slot
  sns_low_lat_stream_list[stream_id].output_buf = NULL;
  sns_low_lat_stream_list[stream_id].output_buf_size = 0;
  sns_low_lat_stream_list[stream_id].smr_handle = NULL;
  sns_low_lat_stream_list[stream_id].interrupt_handle = 0;
  qurt_signal2_destroy(&sns_low_lat_stream_list[stream_id].signal);

  MSG_1(MSG_SSID_SNS,DBG_LOW_PRIO,"returning from sns_low_lat_disable - stream_id %d", stream_id);
  return 0;
}

int sns_low_lat_poll(int stream_id)
{
  unsigned int                    signal;
  int                             sig_wait_error;

#ifdef SNS_LOW_LAT_DEBUG
  MSG_1(MSG_SSID_SNS,DBG_LOW_PRIO,"sns_low_lat_poll - stream_id %d", stream_id);
#endif /* SNS_LOW_LAT_DEBUG */

  // Validate input
  if ( (-1 == stream_id) || (stream_id >= ARR_SIZE(sns_low_lat_stream_list)) )
  {
    MSG_1(MSG_SSID_SNS,DBG_ERROR_PRIO,"sns_low_lat_poll - invalid input, stream_id %d", stream_id);
    return -1;
  }

  // Use the cancellable version of the wait so that the polling thread isn't held up by this call
  sig_wait_error = qurt_signal2_wait_cancellable(&sns_low_lat_stream_list[stream_id].signal,
      SNS_LOW_LAT_SIGNAL_IND | SNS_LOW_LAT_SIGNAL_CANCEL_POLL,
      QURT_SIGNAL_ATTR_WAIT_ANY,
      &signal);
  if (QURT_EOK != sig_wait_error)
  {
    MSG_2(MSG_SSID_SNS,DBG_ERROR_PRIO,"sns_low_lat_poll - error waiting for SIGNAL_IND, error %d, stream_id %d", sig_wait_error, stream_id);
    return -2;
  }

  // Clear any lingering signals
  qurt_signal2_clear(&sns_low_lat_stream_list[stream_id].signal,
      SNS_LOW_LAT_SIGNAL_IND | SNS_LOW_LAT_SIGNAL_CANCEL_POLL);

  // Return an error if this polling call needs to be canceled
  if (signal & SNS_LOW_LAT_SIGNAL_CANCEL_POLL)
  {
    MSG_1(MSG_SSID_SNS,DBG_ERROR_PRIO,"sns_low_lat_poll - canceled polling call, stream_id %d", stream_id);
    return -3;
  }

  // Unblock the caller once a new sample is ready to be read
  return 0;
}
