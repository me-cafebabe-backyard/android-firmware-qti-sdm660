/*=============================================================================
  @file sns_rh_main_uimg.c

  This file implements portion of Request Handler task that executes in microImage.

*******************************************************************************
* Copyright (c) 2014-2017 Qualcomm Technologies, Inc.
* All Rights Reserved.
* Confidential and Proprietary - Qualcomm Technologies, Inc.
********************************************************************************/

/* $Header: //components/rel/ssc.slpi/2.2/smgr/src/sns_rh_main_uimg.c#3 $ */
/* $DateTime: 2017/09/05 01:58:40 $ */
/* $Author: pwbldsvc $ */

/*============================================================================
  EDIT HISTORY FOR FILE

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------
  2017-04-16  bd   When it is time to send reports, flush fifo for APP requests only
  2017-03-16  sd   send ind regardless of processor when report timer expires
  2017-03-06  sd   Added check for modem processor when report timer expires
  2016-12-09  bd   Replaced SNS_RH_RESCHED_REPORTS_SIG with SNS_RH_SENSOR_CONFIG_DONE_SIG
  2016-12-08  tc   Synchronize report items before marking the report as ready
  2016-11-15  bd   Send reports immediately when they are ready
  2016-10-13  bd   Added flusing report into ready queue when process flushed signal
  2016-09-30  sd   added field in sns_rh_uimg structure to read latest sample timestamps
  2016-09-20  bd   Add report into ready queue when flushing  
  2016-09-01  pc   SL Virtio bring up changes
                   - Fixed Linker error: Undefined reference to sns_pm_ap_wakeup_broadcast()
  2016-08-10  np   Added playback support.  
  2016-08-08  pn   Considers possibility of no samples when receiving FIFO_FLUSHED signal 
  2016-07-22  pn   - Using report timer to schedule batch reports
                   - Improved report synchronization to AP clients
  2016-07-19  bd   Wait for SMGR notification before processing other msg
  2016-07-13  np   Support for calibration algorithm
  2016-06-23  pn   Alerts PM when sending indications to AP clients
  2016-06-21  pn   Report for which indications are being generated is no longer
                   put back onto ready queue
  2016-05-18  pn   Periodic-like Buffering report are treated the same as Batching reports
  2016-03-02  pn   Processes WAKE_SIG in bigImage
  2016-02-11  pn   Cleans up WAKE_SIG/SLEEP_SIG processing
  2016-02-05  pn   Added SNS_RH_RESCHED_REPORTS_SIG
  2016-01-28  pn   Reports being flushed need not be added to ready queue
  2016-01-26  pn   Changed sns_rh_init_uimg() signature
  2015-12-08  pn   RH coordinates with SMGR when update sensor for FIFO Flushing
  2015-11-23  pn   Handles connection busy condition when batching samples
  2015-11-04  pn   Query reports readiness differs from other periodic-like reports
  2015-10-20  bd   Added reserved fifo support
  2015-10-19  pn   Report timer is used only for event-sensor batching
  2015-10-13  jtl  Only send error indications on failed heartbeats
  2015-09-30  pn   Added handler for SNS_RH_SENSOR_DECOMMISSIONED_SIG
  2015-09-24  pn   Added method to check for pending signals
  2015-09-18  pn   Report scheduling changes for Batching 
  2015-09-11  bd   - Send indication to sam when enough samples are saved
                   - Exit uimg when before calling bimage functions
  2015-09-11  pn   Refactored sns_rh_send_report_indications()
  2015-09-03  bd   Code cleanup
  2015-08-24  pn   Added support for concurrent selftest and streaming
  2015-08-21  bd   - Do not send sample_ready for buffering reports
                   - Code cleanup
  2015-08-18  bd   - Move batchbuff low signal to uimg
                   - Send indications when ap wake up
  2015-07-30  bd   Added batching feature
  2015-06-19  pn   Times each report one extra sampling interval longer
  2015-06-15  pn   Sends all ready reports when QMI connection resumes
  2015-06-15  pn   Always restarts report timers
  2015-05-27  pn   Takes filter delay into account when checking for ready reports
  2015-05-27  bd   Indication flow control in SMGR
  2015-05-21  pn   Signals SMGR after consuming FIFO data from Flush request
  2015-05-08  pn   Restarts report timer after report flushing is triggered by AP resume
  2015-04-21  pn   Changed report flushing to AP
  2015-04-09  pn   Replaced calls to sns_em_get_timestamp() with sns_ddf_get_timestamp()
  2015-03-20  pn   Fixed Buffering indication size in concurrent with Periodic
  2015-02-03  pn   Made sns_rh_get_latest_sample_timestamp() global
  2015-01-29  pn   Must not update queue while using SMGR_FOR_EACH_Q_ITEM()
  2015-01-23  hw   Added SNS_RH_MODEM_WAKE_SIG signal
  2015-01-23  pn   - Fixed problem of no response to report replacement request
                   - Periodic-like Buffering reports do not need to be flushed
  2015-01-22  BD   Changed the way of putting functions in uImage to use sections
  2015-01-19  hw   Added RH flushing accumulated samples support
  2015-01-16  vy   Moved uImage logging to debug module
  2015-01-13  pn   Correctly handles pending reports
  2014-12-12  sd   relaxed report ready check
  2014-12-03  pn   Moved sns_rh_delete_rpt_after_flush() to bigImage
  2014-11-24  pn   - Only flushes reports to AP when sending Buffering indications
                   - Added handler for SNS_RH_FIFO_SAMPLES_SIG
  2014-11-11  dk   Added support for handling SNS_RH_LOGPKT_DROP_SIG
  2014-11-04  pn   ts_last_sent of Periodic reports being setup does not get updated
  2014-10-28  jms  Rpt sending with effective_rate_hz=0 fix
  2014-10-28  pn   Periodic report scheduling improvements
  2014-10-22  pn   Buffering report scheduling improvements
  2014-10-10  pn   Only synchronizes reports to AP clients if waking up AP
  2014-10-02  pn   Added report synchronization
  2014-09-25  pn   Uses depot selected for report item
  2014-09-23  pn   Added QDSS logging
  2014-09-16  pn   Makes sure not to send indications to suspended AP
  2014-09-08  pn   Maintains external report rate
  2014-09-04  pn   Changed how the next indication is scheduled
  2014-09-03  jhh  Added client name on pm client
  2014-09-02  rt   Added signal for UPDATE_REPORT_TIMER
  2014-08-05  pn   Added handlers for ODR_CHANGED and FIFO_FLUSHED signals
  2014-07-31  pn   Removed POWER_INTERFACE featurization
  2014-07-27  vy   Added vote for NoClient mode
  2014-07-25  pn   Makes sure report is set up completely before adding it to ready list
  2014-07-21  pn   Added unsignal_me()
  2014-06-16  pn   Unshared sns_rh_uimg
  2014-06-05  vy   Further refactored to support uImage
  2014-05-02  aj   Replaced QMI with SMR
  2014-04-29  pn   Initial version
============================================================================*/
/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "sns_osa.h"
#include "sns_rh_main.h"
#include "sns_rh_main_uimg.h"
#include "sns_rh_sol.h"
#include "sns_rh_rpt_gen.h"
#include "sns_rh_util.h"
#include "sns_rh_batchbuff.h"
#include "sns_smgr_api_v01.h"
#include "sns_smgr_util.h"
#ifdef FAST_PLAYBACK
#include "sns_em.h"
#include "sns_smgr.h"
#include "playback.h"
#endif
/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/
#define __SNS_MODULE__ SNS_RH

#define SNS_RH_FIFO_READY(ip) \
  (SMGR_SENSOR_FIFO_IS_ENABLE((ip)->ddf_sensor_ptr->sensor_ptr) && \
   (ip)->ddf_sensor_ptr->sensor_ptr->sensor_state == SENSOR_STATE_READY)

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/
typedef struct
{
  smgr_sensor_id_e               sensor_id;
  sns_ddf_time_t                 data_type_latest_sample_ts[SMGR_MAX_DATA_TYPES_PER_DEVICE];
} sns_rh_sensor_sample_ts_s;

typedef struct
{
  OS_STK                          task_stack[SNS_MODULE_STK_SIZE_DSPS_RH];

  OS_FLAG_GRP*                    sig_grp;
  OS_FLAGS                        sig_mask;

  sns_em_timer_obj_t              report_timer;

  sns_pm_handle_t                 pm_client_handle;
  sns_pm_img_mode_e               curr_img_vote;

  /* queue for reports built from report requests messages */
  sns_q_s                         report_queue;

  /* queue for reports suspended due to selftest */
  sns_q_s                         suspended_report_queue;

  /* linked list of reports ready to be sent */
  sns_rh_rpt_spec_s*              ready_report_ptr;
  sns_rh_report_indication_u      report_ind;

  bool                            app_is_awake;
  uint32_t                        app_state_toggle_count;
  sns_rh_sensor_sample_ts_s       sensor[SNS_SMGR_NUM_SENSORS_DEFINED];

} sns_rh_uimg_s;

/*----------------------------------------------------------------------------
 *  Variables
 * -------------------------------------------------------------------------*/
SNS_RH_UIMAGE_DATA sns_rh_uimg_s sns_rh_uimg;

/*----------------------------------------------------------------------------
 * Macro
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * External Function Declarations
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Function Declarations and Documentation
 * -------------------------------------------------------------------------*/
/*===========================================================================

  FUNCTION:   sns_smgr_flush_reports_to_same_processor

===========================================================================*/
/*!
  @brief Send all available samples to clients on the given processor.

  @detail
  @param[i] proc         - processor type
  @param[i] piggybacking - true if sending report opportunistically
  @return   none
 */
/*=========================================================================*/
SNS_RH_UIMAGE_CODE SMGR_STATIC void sns_rh_flush_reports_to_same_processor(
  sns_proc_type_e_v01 proc,
  bool                piggybacking )
{
  sns_rh_rpt_spec_s* rpt_ptr;
  /* -------------------------------------------------------------------- */

  SMGR_FOR_EACH_Q_ITEM( &sns_rh_uimg.report_queue, rpt_ptr, rpt_link )
  {
    if ( (rpt_ptr->proc_type == proc) &&
         (rpt_ptr->state == RH_RPT_STATE_ACTIVE) && (rpt_ptr->q16_rpt_rate != 0) )
    {
      if ( SNS_RH_REPORT_IS_BATCHING(rpt_ptr) ||
           (!piggybacking && SNS_RH_REPORT_IS_STREAMING(rpt_ptr)) )
      {
        if ( sns_rh_add_to_ready_list(rpt_ptr) )
        {
          rpt_ptr->state = RH_RPT_STATE_FLUSHING;
        }
      }
    }
  }
}

/*===========================================================================

  FUNCTION:   sns_rh_flush_reports_to_ap

===========================================================================*/
/*!
  @details If the given report belongs to a client on AP
           flushes Buffering reports belonging to other AP clients.

  @param  in_rpt_ptr - the report being sent
 
  @return none

*/
/*=========================================================================*/
SNS_RH_UIMAGE_CODE SMGR_STATIC 
void sns_rh_flush_reports_to_ap(sns_rh_rpt_spec_s* const in_rpt_ptr)
{
  if ( in_rpt_ptr->proc_type == SNS_PROC_APPS_V01 && SNS_RH_REPORT_IS_BATCHING(in_rpt_ptr) )
  {
    sns_rh_rpt_spec_s* rpt_ptr;
    SMGR_FOR_EACH_Q_ITEM( &sns_rh_uimg.report_queue, rpt_ptr, rpt_link )
    {
      if ( rpt_ptr != in_rpt_ptr && rpt_ptr->proc_type == SNS_PROC_APPS_V01 &&
           SNS_RH_REPORT_IS_BATCHING(rpt_ptr) && 
           (rpt_ptr->rpt_interval != in_rpt_ptr->rpt_interval) )
      {
        if ( rpt_ptr->state != RH_RPT_STATE_FIFO_FLUSH_PENDING &&
             rpt_ptr->state != RH_RPT_STATE_FIFO_FLUSH_READY &&
             sns_rh_add_to_ready_list(rpt_ptr) )
        {
          rpt_ptr->state = RH_RPT_STATE_FLUSHING;
          /* SNS_SMGR_PRINTF2(
            LOW, "flush_reports_to_ap - rpt_id=%u/0x%x",
            rpt_ptr->rpt_id, rpt_ptr->msg_header.connection_handle); */
        }
      }
    }
  }
}

/*===========================================================================

  FUNCTION:   sns_rh_send_report_indication

===========================================================================*/
/*!
  @details Sends indications for the given report
 
  @param  rpt_ptr - the report being sent
 
  @return true if any indication is sent

*/
/*=========================================================================*/
SNS_RH_UIMAGE_CODE bool sns_rh_send_report_indication(sns_rh_rpt_spec_s* rpt_ptr)
{
  bool sent = false;
  uint8_t last_ind_type = SNS_BATCH_LAST_IND_V01;

  if ( !sns_rh_mr_conn_busy(rpt_ptr->msg_header.connection_handle) )
  {
    /* Rather than leaving it up to SMR to switch in and out of uImage when sending
       back to back indications to external clients, vote for and stay in bigImage 
       when necessary. This eliminates the image toggle to save times waiting for 
       each transaction */
    if ( rpt_ptr->proc_type != SNS_PROC_SSC_V01 || /* external clients */
         rpt_ptr->ind_buffer != NULL ||            /* saved indication exists */
         rpt_ptr->q16_rpt_rate == 0 )              /* query indications */
    {
      sns_rh_leave_island();
    }

    if ( rpt_ptr->ind_buffer != NULL )
    {
      if ( SNS_RH_REPORT_IS_BUFFERING(rpt_ptr) )
      {
        last_ind_type = rpt_ptr->ind_buffer->buffering.IndType;
      }
      sns_rh_rpt_gen_send_saved_ind(rpt_ptr);
    }
    if ( rpt_ptr->ind_buffer == NULL )
    {
      if ( SNS_RH_REPORT_IS_PERIODIC(rpt_ptr) )
      {
        sent = sns_rh_rpt_gen_generate_periodic_report(rpt_ptr);
      }
      else if ( rpt_ptr->q16_rpt_rate != 0 )
      {
        sent = sns_rh_rpt_gen_send_buffering_indications(rpt_ptr, last_ind_type);
      }
      else
      {
        sent = sns_rh_rpt_gen_send_query_indication(rpt_ptr);
      }
    }
  }
  return sent;
}

/*===========================================================================

  FUNCTION:   sns_rh_send_ready_reports

===========================================================================*/
/*!
  @brief Generates indications for all ready reports.

  @param  none

  @return true if indications were sent
*/
/*=========================================================================*/
SNS_RH_UIMAGE_CODE bool sns_rh_send_ready_reports(void)
{
  bool ind_sent = false;
  bool alert_pm = false;
  sns_rh_rpt_spec_s* rpt_ptr;
  sns_rh_rpt_spec_s* rpt_ptrs[SNS_SMGR_MAX_REPORT_CNT];
  uint8_t i, num_rpts = 0;
  /* -------------------------------------------------------------------- */

  while ( (rpt_ptr = sns_rh_uimg.ready_report_ptr) != NULL )
  {
    sns_rh_uimg.ready_report_ptr = rpt_ptr->next_ready_report_ptr;
    rpt_ptr->next_ready_report_ptr = NULL;

    if ( sns_rh_send_report_indication(rpt_ptr) )
    {
      ind_sent = true;
      if ((rpt_ptr->proc_type == SNS_PROC_APPS_V01) && !sns_rh_uimg.app_is_awake )
      {
        alert_pm = true;
      }
    }
    else if ( sns_rh_mr_conn_busy(rpt_ptr->msg_header.connection_handle) &&
              rpt_ptr->state == RH_RPT_STATE_FLUSHING )
    {
      rpt_ptr->state = RH_RPT_STATE_ACTIVE;
    }
  }
  
  /* Delete marked reports after flushing indications */
  SMGR_FOR_EACH_Q_ITEM( &sns_rh_uimg.report_queue, rpt_ptr, rpt_link )
  {
    if ( rpt_ptr->state          == RH_RPT_STATE_ACTIVE &&
         rpt_ptr->state_extended != RH_RPT_STATE_EXT_NONE )
    {
      rpt_ptrs[num_rpts++] = rpt_ptr;
    }
  }

  if ( num_rpts > 0 )
  {
    sns_rh_leave_island();
    for ( i=0; i<num_rpts; i++ )
    {
      sns_rh_sol_handle_pending_rpt(rpt_ptrs[i]);
    }
  }
  
  if ( alert_pm )
  {
#ifndef SNS_PM_EXCLUDE_POWER
    sns_pm_ap_wakeup_broadcast();
#endif
  }
  sns_rh_enter_island();
  return ind_sent;
}

/*===========================================================================

  FUNCTION:   sns_rh_link_lastest_sample_ts

===========================================================================*/
/*!
  @brief associate a item spec with the latest sample timestamp read for the ddf sensor

  @Detail 

  @param[i] ddf_sensor_ptr - Point to the ddf sensor pointer the item points to

  @return
    latest sample time stamp read for the ddf sensor
*/
/*=========================================================================*/
SNS_RH_UIMAGE_CODE sns_ddf_time_t *sns_rh_link_lastest_sample_ts(
   const sns_smgr_ddf_sensor_s*  ddf_sensor_ptr)
{
  uint8_t s, d;
  
  for ( s=0; s<ARR_SIZE(sns_smgr.sensor); s++ )
  {
    sns_smgr_sensor_s *sensor_ptr = &sns_smgr.sensor[s];
    if ( sensor_ptr != NULL )
    {
      for ( d=0; d<ARR_SIZE(sensor_ptr->ddf_sensor_ptr); d++ )
      {
        if ( ddf_sensor_ptr == sensor_ptr->ddf_sensor_ptr[d])
        {
          return &sns_rh_uimg.sensor[s].data_type_latest_sample_ts[d];
        }
      }
    }
  }
  return NULL;
}

/*===========================================================================

  FUNCTION:   sns_rh_get_latest_sample_timestamp

===========================================================================*/
/*!
  @brief Get timestamp of the latest available sample for the given report item

  @param [i] item_ptr - the report item of interest

  @return timestamp of latest sample

*/
/*=========================================================================*/
SNS_RH_UIMAGE_CODE sns_ddf_time_t sns_rh_get_latest_sample_timestamp(
  const sns_rh_rpt_item_s* item_ptr)
{
  return *item_ptr->latest_sample_timestamp_ptr ;
}

/*===========================================================================

  FUNCTION:   sns_rh_ok_to_send_to_sam

===========================================================================*/
/*!
  @brief Decide whether send samples to SAM based on number of samples available
  @param [i] rpt_ptr - the report of interest
  @param [i] num_bbb - number of bigImage batchbuffs held by the report
  @param [i] num_ubb - number of uImage batchbuffs held by the report
    
  @return
  true to send, false otherwise
*/
/*=========================================================================*/
SNS_RH_UIMAGE_CODE SMGR_STATIC bool sns_rh_ok_to_send_to_sam(
  const sns_rh_rpt_spec_s* rpt_ptr,
  uint16_t num_bbb, 
  uint16_t num_ubb)
{
  bool send = false;

  if ( rpt_ptr->proc_type == SNS_PROC_SSC_V01 &&
       rpt_ptr->msg_header.src_module == SNS_MODULE_DSPS_SAM &&
       rpt_ptr->q16_rpt_rate == 1 )
  {
    if ( num_bbb != 0 && 
         rpt_ptr->num_saved_samples >= SNS_SMGR_BUFFERING_REPORT_MAX_SAMPLES_V01 )
    {
      send = true;
    }
    else if ( num_ubb != 0 && rpt_ptr->num_saved_samples >= SNS_RH_BATCHBUFF_MAX_SAMPLE )
    {
      send = true;
    }
  }
  return send;
}

/*===========================================================================

  FUNCTION:   sns_rh_read_latest_sample_ts

===========================================================================*/
/*!
  @brief Read latest sample timestamp before calling sns_rh_buffer_samples
 
  @details this function is added to prevent the latest sample timestamp change
           during  buffering samples for several items in a report
 
  @return  none
*/
/*=========================================================================*/
SNS_RH_UIMAGE_CODE SMGR_STATIC void sns_rh_read_latest_sample_ts()
{
  uint8_t s, d;
  
  for ( s=0; s<ARR_SIZE(sns_smgr.sensor); s++ )
  {
    sns_smgr_sensor_s *sensor_ptr = &sns_smgr.sensor[s];
    if ( sensor_ptr != NULL )
    {
      sns_rh_uimg.sensor[s].sensor_id = SMGR_SENSOR_ID(sensor_ptr);
      for ( d=0; d<ARR_SIZE(sensor_ptr->ddf_sensor_ptr); d++ )
      {
        sns_smgr_ddf_sensor_s* ddf_sensor_ptr = sensor_ptr->ddf_sensor_ptr[d];
        if ( ddf_sensor_ptr != NULL  )
        {
          sns_rh_uimg.sensor[s].data_type_latest_sample_ts[d] = 0;
          if ( ddf_sensor_ptr->client_stat.num_rpt_items > 0 )
          {
            sns_os_mutex_pend(ddf_sensor_ptr->depot_mutex_ptr, 0, NULL);
            sns_rh_uimg.sensor[s].data_type_latest_sample_ts[d] = ddf_sensor_ptr->latest_sample_ts;
            sns_os_mutex_post(ddf_sensor_ptr->depot_mutex_ptr);
         }
        }
      }
    }
  }
}

// Check to see if there are other items in this report that we need to wait on
// before sending out the report indication
SNS_RH_UIMAGE_CODE SMGR_STATIC bool sns_rh_is_periodic_report_ready(
  sns_rh_rpt_spec_s* rpt_ptr)
{
  // Default to true
  bool result = true;
  int i = 0;

  if ( rpt_ptr->periodic_like )
  {
    // 1) Run through all of the report items and look for ones that should be in sync
    // 2) If an item doesn't have a sample to report yet, then return false so the RH knows to wait
    RH_FOR_EACH_REPORT_ITEM(rpt_ptr, i)
    {
      sns_rh_rpt_item_s* item_ptr = rpt_ptr->item_list[i];
      // If this item is expected to generate a sample at the same rate as the report
      if ( (item_ptr->sampling_rate_hz == rpt_ptr->q16_rpt_rate) &&
           // (item_ptr->samples_per_report > item_ptr->num_saved_samples) )
           (item_ptr->num_saved_samples < 1) )
      {
        return false; //kick out;
      }
    }
  }

  return result;
}

/*===========================================================================

  FUNCTION:   sns_rh_buffer_samples

===========================================================================*/
/*!
  @brief Buffers any new samples for the given report
 
  @details Called when new sample(s) are available or when report timer expires; 
           If new samples are saved for the given report puts report on ready list
           if it's time or it waiting for next sample(s) would delay report
 
  @param [i] rpt_ptr - the Buffering report for whom to process new samples
  @param [i] send_now - true if report should be added to ready list now

  @return true if report is put on ready list
*/
/*=========================================================================*/
SNS_RH_UIMAGE_CODE SMGR_STATIC bool sns_rh_buffer_samples(
  sns_rh_rpt_spec_s* rpt_ptr,
  bool               send_now)
{
  bool ready = false;
  bool new_samples_saved = false;
  bool fifo_flush_pending = false;
  sns_ddf_time_t time_now = sns_ddf_get_timestamp();
  sns_ddf_time_t ts_last_saved = 0;
  uint16_t num_bbb = 0;
  uint16_t num_ubb = 0;
  uint8_t i;

  RH_FOR_EACH_REPORT_ITEM(rpt_ptr, i)
  {
    sns_rh_rpt_item_s* item_ptr = rpt_ptr->item_list[i];
    if ( sns_rh_batchbuff_save_samples(item_ptr) )
    {
      new_samples_saved = true;
    }
    if ( send_now )
    {
      ts_last_saved = MAX(ts_last_saved, item_ptr->ts_last_saved);
      num_bbb += sns_q_cnt(&item_ptr->bbatch_buffer_queue);
      num_ubb += sns_q_cnt(&item_ptr->ubatch_buffer_queue);
    }
  }

  if ( new_samples_saved && sns_rh_mr_conn_busy(rpt_ptr->msg_header.connection_handle) )
  {
    sns_rh_batchbuff_handle_conn_busy(rpt_ptr);
  }

  if ( send_now && sns_rh_ok_to_send_report(rpt_ptr) )
  {
    if ( rpt_ptr->event_sensors_only )
    {
      if ( rpt_ptr->num_saved_samples > 0  )
      {
        if ( time_now >= rpt_ptr->rpt_tick || rpt_ptr->ind_count == 0 )
        {
          sns_rh_add_to_ready_list(rpt_ptr);
          ready = true;
        }
      }
    }
    else if ( new_samples_saved )
    {
      // If there's a report item that's not ready to report yet, then don't
      // add the report to the ready list.
      if ( rpt_ptr->periodic_like )
      {
        if (sns_rh_is_periodic_report_ready(rpt_ptr))
        {
          sns_rh_add_to_ready_list(rpt_ptr);
          ready = true;
        }
      }
      else if ( rpt_ptr->state == RH_RPT_STATE_FIFO_FLUSH_READY ||
                ts_last_saved >= rpt_ptr->rpt_tick - rpt_ptr->min_sampling_interval ||
                sns_rh_ok_to_send_to_sam(rpt_ptr, num_bbb, num_ubb) )
      {

        if ( rpt_ptr->state != RH_RPT_STATE_FIFO_FLUSH_PENDING )
        {
          sns_rh_add_to_ready_list(rpt_ptr);
          ready = true;
        }
      }
    }
    else /* no new samples but maybe it's time for report */
    {
      if ( !rpt_ptr->periodic_like && 
           (time_now >= rpt_ptr->rpt_tick || rpt_ptr->state == RH_RPT_STATE_FIFO_FLUSH_READY ) )
      {
        if ( rpt_ptr->proc_type != SNS_PROC_SSC_V01 )
        {
          sns_rh_leave_island();
          sns_rh_prepare_report_for_flushing(rpt_ptr);
        }
        SNS_SMGR_PRINTF5(
          LOW, "buffer_sample - rpt_id=%u/0x%x state=%u last_saved=%u sched=%u timer expired",
          rpt_ptr->rpt_id, rpt_ptr->msg_header.connection_handle, rpt_ptr->state, 
          ts_last_saved, rpt_ptr->rpt_tick);
        if ( rpt_ptr->state == RH_RPT_STATE_FIFO_FLUSH_PENDING )
        {
          fifo_flush_pending = true;
        }
        else
        {
          sns_rh_add_to_ready_list(rpt_ptr);
          ready = true;
        }
      }
    }
  }
  if ( fifo_flush_pending )
  {
    sns_smgr_signal_me(SNS_SMGR_SENSOR_STATE_SIG);
  }
  if ( ready )
  {
    sns_rh_flush_reports_to_ap(rpt_ptr);
  }
  return ready;
}

/*===========================================================================

  FUNCTION:   sns_rh_process_ready_sample_sig

===========================================================================*/
/*!
  @brief Processes SNS_RH_SAMPLE_READY_SIG 

  @param[i] in_rpt_ptr - if not NULL, the report not to be added to ready list

  @return none
*/
/*=========================================================================*/
SNS_RH_UIMAGE_CODE 
void sns_rh_process_ready_sample_sig(const sns_rh_rpt_spec_s* in_rpt_ptr)
{
  sns_rh_rpt_spec_s* rpt_ptr;
  bool update_timer = false;
  /* -------------------------------------------------------------------- */

  sns_rh_read_latest_sample_ts();
  SMGR_FOR_EACH_Q_ITEM( &sns_rh_uimg.report_queue, rpt_ptr, rpt_link )
  {
    bool send_now = (in_rpt_ptr == NULL || rpt_ptr != in_rpt_ptr);
    if ( SNS_RH_REPORT_IS_PERIODIC(rpt_ptr) || rpt_ptr->q16_rpt_rate == 0 )
    {
      if ( send_now && sns_rh_ok_to_send_report(rpt_ptr) )
      {
        uint32_t i;
        RH_FOR_EACH_REPORT_ITEM(rpt_ptr, i)
        {
          sns_rh_rpt_item_s* item_ptr = rpt_ptr->item_list[i];
          if ( item_ptr->state != RH_RPT_ITEM_STATE_LINKING )
          {
            sns_ddf_time_t latest_sample_ts = sns_rh_get_latest_sample_timestamp(item_ptr);
            if ( SNS_RH_REPORT_IS_PERIODIC(rpt_ptr) )
            {
              if ( TICK1_GTR_TICK2(latest_sample_ts, item_ptr->ts_last_sent) &&
                   ((item_ptr->quality == SNS_SMGR_ITEM_QUALITY_CURRENT_SAMPLE_V01) ||
                    (item_ptr->quality == SNS_SMGR_ITEM_QUALITY_FILTERED_V01) ||
                    TICK1_GTR_TICK2(latest_sample_ts,
                                    item_ptr->interpolator_obj.desired_timestamp)) )
              {
                sns_rh_add_to_ready_list(rpt_ptr);
                break;
              }
            }
            else if ( item_ptr->query_ptr != NULL &&
                      TICK1_GEQ_TICK2(latest_sample_ts, item_ptr->query_ptr->T1) )
            {
              sns_rh_add_to_ready_list(rpt_ptr);
              break;
            }
          }
        }
      }
    }
    else if ( rpt_ptr->state == RH_RPT_STATE_FIFO_FLUSH_READY )
    {
      /* this report has a pending response which would not be sent
         unless and until FIFO_FLUSHED signal is processed */
      sns_rh_signal_me(SNS_RH_FIFO_FLUSHED_SIG);
    }
    else if ( rpt_ptr->state != RH_RPT_STATE_FIFO_FLUSH_PENDING &&
              (rpt_ptr->periodic_like || rpt_ptr->rpt_tick != 0) )
    {
      if ( sns_rh_buffer_samples(rpt_ptr, send_now) )
      {
        update_timer = true;
      }
    }
  }

  if ( in_rpt_ptr == NULL )
  {
    sns_rh_send_ready_reports();
  }
  if ( update_timer )
  {
   sns_rh_update_report_timer();
  }
}

/*===========================================================================

  FUNCTION:   sns_rh_process_odr_changed_sig

===========================================================================*/
SNS_RH_UIMAGE_CODE SMGR_STATIC void sns_rh_process_odr_changed_sig(void)
{
  sns_rh_rpt_spec_s* rpt_ptr;
  /* -------------------------------------------------------------------- */

  SMGR_FOR_EACH_Q_ITEM( &sns_rh_uimg.report_queue, rpt_ptr, rpt_link )
  {
    uint32_t i;
    for ( i=0; i<rpt_ptr->num_items; i++ )
    {
      sns_rh_rpt_item_s* item_ptr = rpt_ptr->item_list[i];
      if ( SMGR_BIT_TEST(item_ptr->ddf_sensor_ptr->flags,
                         SMGR_SENSOR_FLAGS_ODR_CHANGED_B) &&
           sns_rh_ok_to_send_report(rpt_ptr) )
      {
        SNS_SMGR_PRINTF1(HIGH, "odr_changed_sig - rpt_id=%u", rpt_ptr->rpt_id);
        rpt_ptr->state = RH_RPT_STATE_FLUSHING;
        sns_rh_add_to_ready_list(rpt_ptr);
        break;
      }
    }
  }
  sns_rh_send_ready_reports();
  sns_smgr_signal_me(SNS_SMGR_SENSOR_STATE_SIG);
}

/*===========================================================================

  FUNCTION:   sns_rh_process_fifo_flushed_sig

===========================================================================*/
SNS_RH_UIMAGE_CODE SMGR_STATIC void sns_rh_process_fifo_flushed_sig(void)
{
  sns_rh_rpt_spec_s* rpt_ptr;
  /* -------------------------------------------------------------------- */

  sns_rh_read_latest_sample_ts();
  SMGR_FOR_EACH_Q_ITEM( &sns_rh_uimg.report_queue, rpt_ptr, rpt_link )
  {
    if ( rpt_ptr->state == RH_RPT_STATE_FIFO_FLUSH_READY )
    {
      SNS_SMGR_PRINTF2(HIGH, "fifo_flushed_sig - rpt_id=%u/0x%x",
                       rpt_ptr->rpt_id, rpt_ptr->msg_header.connection_handle);
      sns_rh_buffer_samples(rpt_ptr, true);
      if ( rpt_ptr->num_saved_samples > 0 )
      {
        sns_rh_add_to_ready_list(rpt_ptr);
      }
      else
      {
        rpt_ptr->state = RH_RPT_STATE_ACTIVE;
      }
    }
  }
  sns_rh_send_ready_reports();
  sns_rh_update_report_timer();
  sns_smgr_signal_me(SNS_SMGR_SENSOR_STATE_SIG);
}

/*===========================================================================

  FUNCTION:   sns_rh_report_timer_cb

===========================================================================*/
/*!
  @brief Time to send report(s).

  @detail

  @param[i]  cb_arg  callback argument
  @return   none
 */
/*=========================================================================*/
SNS_RH_UIMAGE_CODE SMGR_STATIC void sns_rh_report_timer_cb(void *cb_arg)
{
  uint8_t os_err;
  sns_os_sigs_post(
    (OS_FLAG_GRP*)cb_arg, SNS_RH_REPORT_TIMER_SIG, OS_FLAG_SET, &os_err);
}

/*===========================================================================

  FUNCTION:   sns_rh_process_report_timer_sig

===========================================================================*/
/*!
  @brief Processes SNS_RH_REPORT_TIMER_SIG

  @details Finds in report queue all Buffering report due to be sent
           and adds them to ready list.

           This function is called by report timer expiring.

  @param  none

  @return none
*/
/*=========================================================================*/
SNS_RH_UIMAGE_CODE SMGR_STATIC void sns_rh_process_report_timer_sig(void)
{
  sns_rh_rpt_spec_s* rpt_ptr;
  sns_ddf_time_t time_now = sns_ddf_get_timestamp();
  /* -------------------------------------------------------------------- */

  SNS_SMGR_PRINTF1(
    HIGH, "sns_rh_process_report_timer_sig time_now(%u)",time_now);
    
  sns_rh_read_latest_sample_ts();
  SMGR_FOR_EACH_Q_ITEM( &sns_rh_uimg.report_queue, rpt_ptr, rpt_link )
  {
    if ( rpt_ptr->state == RH_RPT_STATE_ACTIVE &&
         SNS_RH_REPORT_IS_BATCHING(rpt_ptr) && time_now >= rpt_ptr->rpt_tick )
    {
      sns_rh_buffer_samples(rpt_ptr, true);
    }
  }
  sns_rh_send_ready_reports();
  sns_rh_update_report_timer();
}

/*===========================================================================

  FUNCTION:   sns_rh_handle_app_wake_sig

===========================================================================*/
/*!
  @brief Handles APP_WAKE signal

  @detail
  @param  none
  @return none
 */
/*=========================================================================*/
void sns_rh_handle_app_wake_sig(void)
{
  SNS_SMGR_PRINTF2(
    HIGH, "WAKE_SIG curr state(%u) change count(%u)",
    sns_rh_uimg.app_is_awake, sns_rh_uimg.app_state_toggle_count);

  if ( !sns_rh_uimg.app_is_awake )
  {
    sns_rh_uimg.app_is_awake = true;
    sns_rh_uimg.app_state_toggle_count++;
  
    sns_rh_flush_reports_to_same_processor(SNS_PROC_APPS_V01, false);
    sns_rh_flush_reports();
  }
}

/*===========================================================================

  FUNCTION:   sns_rh_handle_app_sleep_sig

===========================================================================*/
/*!
  @brief Handles APP_SLEEP signal

  @detail
  @param  none
  @return none
 */
/*=========================================================================*/
void sns_rh_handle_app_sleep_sig(void)
{
  SNS_SMGR_PRINTF2(
    HIGH, "SLEEP_SIG curr state(%u), change count(%u)",
    sns_rh_uimg.app_is_awake, sns_rh_uimg.app_state_toggle_count);

  if ( sns_rh_uimg.app_is_awake )
  {
    sns_rh_uimg.app_is_awake = false;
    sns_rh_uimg.app_state_toggle_count++;
  }
}

/*===========================================================================

  FUNCTION:   sns_rh_uimg_modem_sync_event

===========================================================================*/
/*!
  @brief Called by modem sync proxy to indicate modem is awake

  @detail

  @return   none
 */
/*=========================================================================*/
SNS_RH_UIMAGE_CODE void sns_rh_uimg_modem_sync_event(void)
{
  uint8_t  err;
  sns_os_sigs_post(sns_rh_uimg.sig_grp, SNS_RH_MODEM_WAKE_SIG, OS_FLAG_SET, &err);
}

/*===========================================================================

  FUNCTION:   sns_rh_process_sensor_heartbeat_sig

===========================================================================*/
/*!
  @brief   Processes SNS_RH_SENSOR_HEARTBEAT_SIG
  @param   none
  @return  none
 */
/*=========================================================================*/
SNS_SMGR_UIMAGE_CODE SMGR_STATIC 
void sns_rh_process_sensor_heartbeat_sig(void)
{
  sns_rh_rpt_spec_s* rpt_ptr;
  sns_smgr_report_error_ind_msg_v01 error_ind;

  SMGR_FOR_EACH_Q_ITEM( &sns_rh_uimg.report_queue, rpt_ptr, rpt_link )
  {
    uint8_t i;
    RH_FOR_EACH_REPORT_ITEM(rpt_ptr, i)
    {
      sns_rh_rpt_item_s* item_ptr = rpt_ptr->item_list[i];
      bool sensor_is_ok = sns_smgr_sensor_is_ok( item_ptr->ddf_sensor_ptr );
      if ( !sensor_is_ok )
      {
        error_ind.ReportId  = rpt_ptr->rpt_id;
        error_ind.SensorId  = SMGR_SENSOR_ID(item_ptr->ddf_sensor_ptr->sensor_ptr);
        error_ind.DataType  = item_ptr->ddf_sensor_ptr->data_type;
        error_ind.ErrorCode = SNS_SMGR_REPORT_ERROR_DEVICE_V01;
        
        SNS_SMGR_PRINTF2(ERROR, "heartbeat_sig - error ind for report %u/0x%x",
                         rpt_ptr->rpt_id, rpt_ptr->msg_header.connection_handle);
        sns_rh_mr_send_indication(rpt_ptr->msg_header.connection_handle,
                                  &error_ind,
                                  SNS_SMGR_REPORT_ERROR_IND_V01,
                                  sizeof(error_ind),
                                  false); /* do not free ind msg */
      }
    }
  }
}

/*===========================================================================

  FUNCTION:   sns_rh_app_state_change

===========================================================================*/
/*!
  @brief Called by Power module when AP state changes

  @detail
  @param[i] app_is_asleep - true if AP entered sleep state, false wake state
  @return   none
 */
/*=========================================================================*/
SNS_RH_UIMAGE_CODE SMGR_STATIC void sns_rh_app_state_change(bool app_is_asleep)
{
  uint8_t  err;
  uint32_t set_bit = app_is_asleep ? SNS_RH_APP_SLEEP_SIG : SNS_RH_APP_WAKE_SIG;
  uint32_t clr_bit = app_is_asleep ? SNS_RH_APP_WAKE_SIG  : SNS_RH_APP_SLEEP_SIG;
  sns_os_sigs_post(sns_rh_uimg.sig_grp, clr_bit, OS_FLAG_CLR, &err);
  sns_os_sigs_post(sns_rh_uimg.sig_grp, set_bit, OS_FLAG_SET, &err);
}

/*===========================================================================
  FUNCTION:   sns_rh_pm_client_init
===========================================================================*/
SNS_RH_UIMAGE_CODE SMGR_STATIC void sns_rh_pm_client_init(void)
{
  sns_pm_err_code_e pm_err =
    sns_pm_client_init(&sns_rh_uimg.pm_client_handle, sns_rh_app_state_change, 
                       "SMGR_RH", SNS_PM_CLIENT_ID_RH);
  SNS_ASSERT(pm_err == SNS_PM_SUCCESS);
}

/*===========================================================================

  FUNCTION:   sns_rh_sol_update_report_timer

===========================================================================*/
/*!
  @brief Resets report timer as the schedule may have changed
  @param none
  @return none
*/
/*=========================================================================*/
SNS_RH_UIMAGE_CODE void sns_rh_update_report_timer(void)
{
  sns_ddf_time_t time_now = sns_ddf_get_timestamp();
  sns_ddf_time_t earliest_report_time = time_now + SMGR_MAX_TICKS;
  sns_rh_rpt_spec_s* rpt_ptr;
  /* -------------------------------------------------------------------- */

  if ( sns_q_cnt(&sns_rh_uimg.report_queue) > 0 )
  {
    uint32_t num_buffering_reports = 0;
    SMGR_FOR_EACH_Q_ITEM( &sns_rh_uimg.report_queue, rpt_ptr, rpt_link )
    {
      if ( SNS_RH_REPORT_IS_BATCHING(rpt_ptr) && sns_rh_ok_to_send_report(rpt_ptr) )
      {
        sns_ddf_time_t rt = rpt_ptr->rpt_tick + rpt_ptr->min_sampling_interval;
        if ( rt > time_now )
        {
          earliest_report_time = MIN(earliest_report_time, rt);
          num_buffering_reports++;
        }
      }
    }

    if ( num_buffering_reports > 0 )
    {
      if ( earliest_report_time > time_now )
      {
        int32_t offset = earliest_report_time - time_now;
        if ( sns_em_register_utimer(sns_rh_uimg.report_timer, offset) == SNS_SUCCESS )
        {
          sns_rh_unsignal_me(SNS_RH_REPORT_TIMER_SIG);
          /* SNS_SMGR_PRINTF4(
            MED, "report_timer - #rpts=%u now=%u offset=%d expire=%u", 
            num_buffering_reports, time_now, offset, earliest_report_time); */
        }
        else
        {
          SNS_SMGR_PRINTF2(ERROR, "report_timer - now=%u offset=%d", time_now, offset);
        }
        sns_profiling_log_qdss(SNS_RH_RPT_TIMER_SET, 2, earliest_report_time, offset);
      }
      else
      {
        SNS_SMGR_PRINTF2(ERROR, "report_timer - #reports=%u now=%u",
                         num_buffering_reports, time_now);
      }
    }
  }
  else
  {
    sns_em_cancel_utimer(sns_rh_uimg.report_timer);
    SNS_SMGR_PRINTF0(HIGH, "report_timer - no more reports - timer cancelled");
  }
}

/*===========================================================================

  FUNCTION:   sns_rh_rpt_gen_add_to_ready_list

===========================================================================*/
/*!
  @brief Adds the given report to the list of reports ready to be sent.

  @param[i] report_ptr - the report to add

  @return true if report is added, false if already on the list
*/
/*=========================================================================*/
SNS_RH_UIMAGE_CODE bool sns_rh_add_to_ready_list(sns_rh_rpt_spec_s* report_ptr)
{
  bool added = false;
  sns_rh_rpt_spec_s** rpp = &sns_rh_uimg.ready_report_ptr;
  /* -------------------------------------------------------------------- */

  while ( *rpp != NULL )
  {
    if ( *rpp == report_ptr )
    {
      /* already on ready list */
      break;
    }
    rpp = &(*rpp)->next_ready_report_ptr;
  }
  if (*rpp == NULL)
  {
    /* not already on ready list */
    *rpp = report_ptr;
    added = true;
  }
  return added;
}

/*===========================================================================

  FUNCTION:   sns_rh_rpt_gen_remove_from_ready_list

===========================================================================*/
/*!
  @brief Removes the given report from the list of reports ready to be sent.

  @param[i] report_ptr - the report to remove from ready list

  @return none
*/
/*=========================================================================*/
SNS_RH_UIMAGE_CODE void sns_rh_rpt_gen_remove_from_ready_list(sns_rh_rpt_spec_s* rpt_ptr)
{
  sns_rh_rpt_spec_s** rpp = &sns_rh_uimg.ready_report_ptr;
  /* -------------------------------------------------------------------- */

  while ( *rpp != NULL )
  {
    if ( *rpp == rpt_ptr )
    {
      /* remove this report from ready list */
      *rpp = rpt_ptr->next_ready_report_ptr;
      rpt_ptr->next_ready_report_ptr = NULL;
      SNS_SMGR_PRINTF2(
        MED, "remove_from_ready_list - rpt_id=%u/0x%x",
        rpt_ptr->rpt_id, rpt_ptr->msg_header.connection_handle);
      break;
    }
    rpp = &(*rpp)->next_ready_report_ptr;
  }
}

/*===========================================================================
  FUNCTION:   sns_rh_init_uimg
===========================================================================*/
SNS_RH_UIMAGE_CODE void sns_rh_init_uimg(void)
{
  uint8_t  err;

  sns_rh_uimg.sig_grp = sns_os_sigs_create(0, &err);
  SNS_ASSERT(sns_rh_uimg.sig_grp != NULL);

  sns_rh_uimg.app_is_awake = true;

  sns_q_init(&sns_rh_uimg.report_queue);
  sns_q_init(&sns_rh_uimg.suspended_report_queue);

  sns_em_create_utimer_obj(&sns_rh_report_timer_cb, sns_rh_uimg.sig_grp,
                           SNS_EM_TIMER_TYPE_ONESHOT, &sns_rh_uimg.report_timer);

  sns_rh_pm_client_init();

  sns_rh_uimg.sig_mask =
    SNS_RH_SELF_TEST_DONE_SIG         |
    SNS_RH_SENSOR_CONFIG_DONE_SIG     |
    SNS_RH_SAMPLE_READY_SIG           |
    SNS_RH_REPORT_TIMER_SIG           |
    SNS_RH_MD_INT_ENABLED_SIG         |
    SNS_RH_MD_INT_DISABLED_SIG        |
    SNS_RH_MD_INT_SIG                 |
    SNS_RH_ODR_CHANGED_SIG            |
    SNS_RH_FIFO_FLUSHED_SIG           |
    SNS_RH_RESP_Q_SIG                 |
    SNS_RH_IND_Q_SIG                  |
    SNS_RH_SMR_MSG_SIG                |
    SNS_RH_SMR_DISC_SIG               |
    SNS_RH_SMR_RESUME_SIG             |
    SNS_RH_BATCHBUFF_LOW_SIG          |
    SNS_RH_SENSOR_HEARTBEAT_SIG       |
    SNS_RH_APP_WAKE_SIG               |
    SNS_RH_APP_SLEEP_SIG              |
    SNS_RH_UPDATE_REPORT_TIMER_SIG    |
    SNS_RH_SAM_MSG_SIG                |  
    SNS_RH_MODEM_WAKE_SIG;
}
/*===========================================================================

  FUNCTION:   sns_rh_task_loop

===========================================================================*/
/*!
  @brief Request Handler task

  @detail

  @param[i]  sig_grp
  @param[i]  sig_mask

  @return   none
 */
/*=========================================================================*/
SNS_RH_UIMAGE_CODE void sns_rh_task_loop(void)
{
  OS_FLAGS  sig_flags;
  OS_FLAGS  big_image_sig_mask =
    SNS_RH_SMR_DISC_SIG             |
    SNS_RH_SMR_RESUME_SIG           |
    SNS_RH_SELF_TEST_DONE_SIG       |
    SNS_RH_SENSOR_CONFIG_DONE_SIG   |
    SNS_RH_MD_INT_ENABLED_SIG       |
    SNS_RH_MD_INT_DISABLED_SIG      |
    SNS_RH_MD_INT_SIG               |
    SNS_RH_RESP_Q_SIG               |
    SNS_RH_IND_Q_SIG                |
    SNS_RH_MODEM_WAKE_SIG           |
    SNS_RH_APP_WAKE_SIG             |
    SNS_RH_APP_SLEEP_SIG            |
    SNS_RH_SAM_MSG_SIG              |
    SNS_RH_SMR_MSG_SIG;
  /* -------------------------------------------------------------------- */

  sns_os_sigs_add(sns_rh_uimg.sig_grp, sns_rh_uimg.sig_mask);

  while ( 1 )
  {
    uint8_t  err;
    sns_ddf_time_t time_now;

    sns_profiling_log_qdss(SNS_RH_EXIT, 0);

    /* OS_FLAG_CONSUME will make the SMR clear the flag after the call */
    sig_flags = sns_os_sigs_pend(sns_rh_uimg.sig_grp, sns_rh_uimg.sig_mask,
                                 OS_FLAG_WAIT_SET_ANY + OS_FLAG_CONSUME, 0, &err);

    time_now = sns_ddf_get_timestamp();

    sns_profiling_log_qdss(SNS_RH_ENTER, 2, sig_flags, time_now);

    //SNS_SMGR_PRINTF2(HIGH, "***rh_task - sigs=0x%08x at %u", sig_flags, time_now);

    if ( sig_flags & SNS_RH_SAMPLE_READY_SIG )
    {
#ifdef FAST_PLAYBACK
      sns_os_mutex_pend( fpb_rh_mutex, 0, &err );
      sns_rh_process_ready_sample_sig(NULL);
      sns_os_mutex_post(fpb_rh_mutex);
      sns_os_sigs_post( playback_cal_sig_event, (OS_FLAGS) FPB_CAL_CONNECT_SIG,
                      OS_FLAG_SET, &err );
#else
      sns_rh_process_ready_sample_sig(NULL);
#endif
    }
#ifdef FAST_PLAYBACK
    sns_os_mutex_pend( fpb_rh_mutex, 0, &err );
#endif
    if ( sig_flags & SNS_RH_REPORT_TIMER_SIG )
    {
      sns_rh_process_report_timer_sig();
    }
    if ( sig_flags & SNS_RH_BATCHBUFF_LOW_SIG )
    {
      sns_rh_process_batchbuff_low_request();
    }
    if ( sig_flags & SNS_RH_SENSOR_HEARTBEAT_SIG )
    {
      sns_rh_process_sensor_heartbeat_sig();
    }
    if ( sig_flags & SNS_RH_ODR_CHANGED_SIG )
    {
      sns_rh_process_odr_changed_sig();
    }
    if ( sig_flags & SNS_RH_FIFO_FLUSHED_SIG )
    {
      sns_rh_process_fifo_flushed_sig();
    }
    if ( sig_flags & SNS_RH_UPDATE_REPORT_TIMER_SIG )
    {
      sns_rh_update_report_timer();
    }
    if ( sig_flags & big_image_sig_mask )
    {
      sns_rh_leave_island();
      sns_rh_process_big_image_signals(sig_flags);
      sns_rh_enter_island();
      if ( sig_flags & SNS_RH_SMR_RESUME_SIG )
      {
        sns_rh_process_ready_sample_sig(NULL);
      }
    }
    sig_flags &= ~sns_rh_uimg.sig_mask;
    if ( sig_flags )
    {
      SNS_SMGR_PRINTF1(ERROR, "rh_task - unknown sigs(0x%08x)", sig_flags);
    }
#ifdef FAST_PLAYBACK
    sns_os_mutex_post(fpb_rh_mutex);
#endif
  } /* while */
}

/*===========================================================================

  FUNCTION:   sns_rh_new_samples_available

===========================================================================*/
/*!
  @brief   Checks whether SMGR has reported new samples
  @param   none
  @return  true if new samples are available
 */
/*=========================================================================*/
SNS_RH_UIMAGE_CODE bool sns_rh_new_samples_available(void)
{
  uint8_t err;
  uint8_t sig_mask = SNS_RH_SAMPLE_READY_SIG;
  OS_FLAGS sig_flags = sns_os_sigs_accept(sns_rh_uimg.sig_grp, sig_mask, 
                                          OS_FLAG_WAIT_SET_ANY, &err);
  return ((sig_flags & SNS_RH_SAMPLE_READY_SIG) != 0);
}

/*===========================================================================

  FUNCTION:   sns_rh_signal_me

===========================================================================*/
/*!
  @brief Posts a signal to RH task

  @detail
  @param[i] sig - the signal to post
  @return   none
 */
/*=========================================================================*/
SNS_RH_UIMAGE_CODE void sns_rh_signal_me(uint32_t sig)
{
  uint8_t os_err;
  sns_os_sigs_post(sns_rh_uimg.sig_grp, sig, OS_FLAG_SET, &os_err);
}

/*===========================================================================

  FUNCTION:   sns_rh_unsignal_me

===========================================================================*/
/*!
  @brief Clears the given signal that might have been sent to RH task

  @detail
  @param[i] sig - the signal to post
  @return   none
 */
/*=========================================================================*/
SNS_RH_UIMAGE_CODE void sns_rh_unsignal_me(uint32_t sig)
{
  sns_os_sigs_post(sns_rh_uimg.sig_grp, sig, OS_FLAG_CLR, NULL);
}

/*===========================================================================
  FUNCTION:   sns_rh_leave_island
===========================================================================*/
SNS_RH_UIMAGE_CODE void sns_rh_leave_island(void)
{
  if ( sns_rh_uimg.curr_img_vote != SNS_IMG_MODE_BIG )
  {
    sns_rh_uimg.curr_img_vote = SNS_IMG_MODE_BIG;
    sns_pm_vote_img_mode(sns_rh_uimg.pm_client_handle, sns_rh_uimg.curr_img_vote);
  }
}

/*===========================================================================
  FUNCTION:   sns_rh_enter_island
===========================================================================*/
SNS_RH_UIMAGE_CODE void sns_rh_enter_island(void)
{
  if ( sns_rh_uimg.curr_img_vote != SNS_IMG_MODE_MICRO )
  {
    if ( sns_rh_get_report_count() == 0 )
    {
      sns_rh_uimg.curr_img_vote = SNS_IMG_MODE_NOCLIENT;
    }
    else
    {
      sns_rh_uimg.curr_img_vote = SNS_IMG_MODE_MICRO;
    }
    sns_pm_vote_img_mode(sns_rh_uimg.pm_client_handle, sns_rh_uimg.curr_img_vote);
  }
}

/*===========================================================================
  FUNCTION:   sns_rh_get_report_queue
===========================================================================*/
SNS_RH_UIMAGE_CODE sns_q_s* sns_rh_get_report_queue(void)
{
  return &sns_rh_uimg.report_queue;
}

/*===========================================================================
  FUNCTION:   sns_rh_get_suspended_report_queue
===========================================================================*/
SNS_RH_UIMAGE_CODE sns_q_s* sns_rh_get_suspended_report_queue(void)
{
  return &sns_rh_uimg.suspended_report_queue;
}

/*=========================================================================
  FUNCTION:  sns_rh_get_report_count
  =========================================================================*/
SNS_RH_UIMAGE_CODE int sns_rh_get_report_count(void)
{
  return sns_q_cnt(&sns_rh_uimg.report_queue);
}

/*=========================================================================
  FUNCTION:  sns_rh_ok_to_send_report
  =========================================================================*/
SNS_RH_UIMAGE_CODE bool sns_rh_ok_to_send_report(const sns_rh_rpt_spec_s* rpt_ptr)
{
  return ( !sns_rh_mr_conn_busy(rpt_ptr->msg_header.connection_handle) &&
           ((rpt_ptr->proc_type != SNS_PROC_APPS_V01) ||
           sns_rh_uimg.app_is_awake || rpt_ptr->send_ind_during_suspend));
}
/*=========================================================================
  FUNCTION:  sns_rh_ok_to_trim_nonwakeup_buffer
  =========================================================================*/
SNS_RH_UIMAGE_CODE bool 
sns_rh_ok_to_trim_nonwakeup_buffer(const sns_rh_rpt_spec_s* rpt_ptr)
{
  return (rpt_ptr->proc_type == SNS_PROC_APPS_V01) &&
         !sns_rh_uimg.app_is_awake && !rpt_ptr->send_ind_during_suspend;
}


/*=========================================================================
  FUNCTION:  sns_rh_get_periodic_ind_buf
  =========================================================================*/
SNS_RH_UIMAGE_CODE sns_smgr_periodic_report_ind_msg_v01* sns_rh_get_periodic_ind_buf(void)
{
  return &sns_rh_uimg.report_ind.periodic;
}

/*=========================================================================
  FUNCTION:  sns_rh_get_buffering_ind_buf
  =========================================================================*/
SNS_RH_UIMAGE_CODE sns_smgr_buffering_ind_msg_v01* sns_rh_get_buffering_ind_buf(void)
{
  return &sns_rh_uimg.report_ind.buffering;
}

/*=========================================================================
  FUNCTION:  sns_rh_get_query_ind_buf
  =========================================================================*/
SNS_RH_UIMAGE_CODE sns_smgr_buffering_query_ind_msg_v01* sns_rh_get_query_ind_buf(void)
{
  return &sns_rh_uimg.report_ind.query;
}

/*===========================================================================

  FUNCTION:   sns_rh_init

===========================================================================*/
/*!
  @brief Starts Request Handler task.
  @param   none
  @return  SNS_SUCCESS
 */
/*=========================================================================*/
SNS_RH_UIMAGE_CODE sns_err_code_e sns_rh_init(void)
{
  uint32_t stack_size = ARR_SIZE(sns_rh_uimg.task_stack);
  sns_os_task_create_ext(sns_rh_task, NULL,
                         &sns_rh_uimg.task_stack[stack_size - 1],
                         SNS_MODULE_PRI_DSPS_RH,
                         SNS_MODULE_PRI_DSPS_RH,
                         sns_rh_uimg.task_stack,
                         stack_size,
                         (void *)0,
                         OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR |
                         OS_TASK_OPT_ISLAND,
                         (uint8_t *)"SNS_RH");
  return SNS_SUCCESS;
}


/*===========================================================================

  FUNCTION:   sns_rh_get_pm_client_handle

===========================================================================*/
/*!
  @brief Returns RH's handle for PM

  @detail

  @param   none
  @return  return RH PM handle
 */
/*=========================================================================*/
SNS_RH_UIMAGE_CODE sns_pm_handle_t sns_rh_get_pm_client_handle(void)
{
  return sns_rh_uimg.pm_client_handle;
}

/*===========================================================================

  FUNCTION:   sns_rh_wait_for_smgr

===========================================================================*/
/*!
  @brief Pend until SMGR is initialized completely

  @detail

  @param   none
  @return  
 */
/*=========================================================================*/

void sns_rh_wait_for_smgr(void)
{
  uint8_t  err;

  sns_os_sigs_add( sns_rh_uimg.sig_grp,SNS_RH_SMGR_INIT_DONE_SIG ); 
  sns_os_sigs_pend( sns_rh_uimg.sig_grp,
                    SNS_RH_SMGR_INIT_DONE_SIG,
                    OS_FLAG_WAIT_SET_ANY + OS_FLAG_CONSUME,
                    0,
                    &err );
}


