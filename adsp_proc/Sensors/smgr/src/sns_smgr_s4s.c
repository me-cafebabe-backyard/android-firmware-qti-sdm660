/*=============================================================================
  @file sns_smgr_s4s.c

  This file contains the logic for managing the S4S scheduler

*******************************************************************************
* Copyright (c) 2014-2016 Qualcomm Technologies, Inc.
* All Rights Reserved.
* Confidential and Proprietary - Qualcomm Technologies, Inc.
********************************************************************************/

/* $Header: //components/rel/ssc.slpi/2.2/smgr/src/sns_smgr_s4s.c#1 $ */
/* $DateTime: 2017/04/17 22:20:39 $ */
/* $Author: pwbldsvc $ */

/*============================================================================
  EDIT HISTORY FOR FILE

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------
  2016-07-28  jtl  get_next_ts may generate new S4S schedule if it doesn't already exist 
  2016-06-28  pn   No longer generates signals not appropriate when turning off sensor
  2016-06-10  jtl  Fixing null pointer deference in config_s4s
  2016-06-08  jtl  Set ddf_sensor_ptr flag when first S4S synced sample is received
  2016-06-03  jtl  Keep track of first synced sample from the sensor
  2016-05-27  jtl  Support driver enabling/disabling S4S scheduling via S4S_CONFIG attrib
  2016-05-23  jtl  Use ANY_ALLOC method to allocated S4S structures
  2016-05-17  jtl  Don't send ST/DT in the case of t_ph=0.
  2016-04-21  jtl  Various S4S fixes. Limit missed DTs to 2, longer RR for non-uImage drivers
  2016-03-30  jtl  Modify S4S to separate out S4S sched from FIFO read sched
  2016-03-07  jtl  Updated S4S to read config back from driver after it has been set.
  2016-01-28  jtl  Updated update_fifo_read_interval to handle fifo changes better
                   Update S4S to have fixed interval. 16000 tick startup, 32000 tick runtime
                   Made multiple S4S schedule blocks -- one per sensor.
  2015-10-26  jtl  Ininital S4S implementation.

============================================================================*/

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "sns_em.h"
#include "sns_memmgr.h"
#include "sns_profiling.h"
#include "sns_rh_sol.h"
#include "sns_rh_util.h"
#include "sns_smgr_main.h"
#include "sns_smgr_depot.h"
#include "sns_smgr_ddf_if.h"
#include "sns_smgr_hw.h"
#include "sns_smgr_util.h"
#include "sns_smgr_pm_if.h"

#include <limits.h>
#include <stdlib.h>

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/

/* For fast sync startup, divides the nominal TPH period by this.
 * Should be chosen such that the PERIOD_TICKS / PERIOD_DIVISOR is
 * an integer.
 * Note: All suppored ODRs will be divisible by this number * 2. So,
 * for example, setting this to 4 means that 100Hz is not supported,
 * but S4S will force an ODR of 104.
 */
#define FAST_TPH_PERIOD_DIVISOR 2

/* S4S spec defined typical maximum sensor clock drift, after clocks are
 * synced. In units of 1/10th of a percent */
#define S4S_CLOCK_DRIFT_10THS_PCT 1

/* Maximum number of missed DTs to account for */
#define S4S_MAX_MISSED_DTS 2

/*----------------------------------------------------------------------------
 *  External functions
 * -------------------------------------------------------------------------*/

/*===========================================================================

  FUNCTION:   sns_smgr_s4s_init_new_sched_block

===========================================================================*/
/*!
  @brief Initializes a new S4S schedule block.

  @return
   A pointer to the scheduler block containing the S4S schedule
   or returns NULL when there is nothing
*/
/*=========================================================================*/
void sns_smgr_s4s_init_new_sched_block( sns_smgr_sensor_s* sensor_ptr )
{
  smgr_s4s_sched_block_s *s4s_sched_ptr;

  if( SMGR_SENSOR_IS_S4S(sensor_ptr) && sensor_ptr->curr_s4s_sched == NULL )
  {
    int i;
    sns_ddf_time_t max_isi = 0;
    
    s4s_sched_ptr = SMGR_ANY_ALLOC_STRUCT(smgr_s4s_sched_block_s);
    if( s4s_sched_ptr != NULL )
    {
      sns_q_link( s4s_sched_ptr, &(s4s_sched_ptr->sched_link) );
      s4s_sched_ptr->missed_dts = 1;
      s4s_sched_ptr->ideal_sync_offset = 0;
      s4s_sched_ptr->st_send_time = 0;
      s4s_sched_ptr->synced = false;
      /* Set initial clock drift to a percent of the initial ideal sync interval */
      s4s_sched_ptr->max_clock_drift =
        NOMINAL_TPH_PERIOD_TICKS / FAST_TPH_PERIOD_DIVISOR * S4S_CLOCK_DRIFT_10THS_PCT / 1000;
      
      for ( i = 0; i < ARR_SIZE(sensor_ptr->ddf_sensor_ptr); i++ )
      {
        if ( sensor_ptr->ddf_sensor_ptr[i] != NULL )
        {
          sensor_ptr->ddf_sensor_ptr[i]->first_synced_s4s_sample_received = false;
          max_isi =
            MAX(max_isi,
                sensor_ptr->ddf_sensor_ptr[i]->current_s4s.ideal_sync_interval);
        }
      }
      if( max_isi == 0 )
      {
        max_isi = NOMINAL_TPH_PERIOD_TICKS / FAST_TPH_PERIOD_DIVISOR;
      }
      s4s_sched_ptr->ideal_sync_interval = max_isi;
      SNS_SMGR_PRINTF1( HIGH, "initializing new s4s sched block. isi %u",
                        s4s_sched_ptr->ideal_sync_interval );
      sensor_ptr->curr_s4s_sched = s4s_sched_ptr;
    }
    else
    {
      SNS_SMGR_PRINTF1(
        ERROR, "s4s_init_new_sched_block: sensor id=%u no memory for new sched block",
        SMGR_SENSOR_ID(sensor_ptr));
    }
  }
}

/*===========================================================================

  FUNCTION:   sns_smgr_s4s_dereg_from_sched

===========================================================================*/
/*!
  @brief Initializes a new S4S schedule block.

  @return
   A pointer to the scheduler block containing the S4S schedule
   or returns NULL when there is nothing
*/
/*=========================================================================*/
void sns_smgr_s4s_dereg_from_sched( sns_smgr_sensor_s* sensor_ptr )
{
  smgr_s4s_sched_block_s *s4s_sched_ptr = sensor_ptr->curr_s4s_sched;
  sensor_ptr->curr_s4s_sched = NULL;
  if( s4s_sched_ptr != NULL )
  {
    if( SMGR_QUE_HEADER_FROM_LINK(&s4s_sched_ptr->sched_link) )
    {
      sns_q_delete(&s4s_sched_ptr->sched_link);
    }
    SNS_OS_FREE(s4s_sched_ptr);
  }
}

/*===========================================================================

  FUNCTION:   sns_smgr_s4s_handle_first_synced_sample

===========================================================================*/
/*!
  @brief Handles receiving the first synced sample from the sensor
*/
/*=========================================================================*/
SMGR_STATIC void sns_smgr_s4s_handle_first_synced_sample( sns_smgr_ddf_sensor_s* ddf_sensor_ptr )
{
  sns_smgr_sensor_s *sensor_ptr = ddf_sensor_ptr->sensor_ptr;
  sns_ddf_sensor_e sensor_type = 
    SMGR_SENSOR_TYPE(sensor_ptr, ddf_sensor_ptr->data_type);

  SNS_SMGR_PRINTF1( MED, "smgr s4s: ddf_sensor=%d first synced s4s sample received",
                    sensor_type );

  ddf_sensor_ptr->first_synced_s4s_sample_received = true;

  /* Set the UPDATE_SAMPLING_NEEDED flag so that interpolation can get disabled */
  sns_os_mutex_pend(sensor_ptr->mutex_ptr, 0, NULL);
  SMGR_BIT_SET(sensor_ptr->flags, SMGR_SENSOR_FLAGS_UPDATE_SAMPLING_NEEDED_B);
  SMGR_BIT_SET(ddf_sensor_ptr->flags, SMGR_SENSOR_FLAGS_UPDATE_SAMPLING_NEEDED_B);
  SMGR_BIT_SET(ddf_sensor_ptr->flags, SMGR_SENSOR_FLAGS_FIRST_SYNCED_S4S_SAMPLE_B);
  sns_os_mutex_post(sensor_ptr->mutex_ptr);
  sns_smgr_signal_me(SNS_SMGR_SENSOR_STATE_SIG);
}

/*===========================================================================

  FUNCTION:   sns_smgr_s4s_check_first_synced_sample

===========================================================================*/
/*!
  @brief Handles receiving the first synced sample from the sensor
*/
/*=========================================================================*/
SNS_SMGR_UIMAGE_CODE void sns_smgr_s4s_check_first_synced_sample( sns_smgr_ddf_sensor_s* ddf_sensor_ptr )
{
  sns_pm_img_mode_e curr_mode = sns_smgr_get_curr_image_vote();
  sns_smgr_sensor_s* sensor_ptr = ddf_sensor_ptr->sensor_ptr;
  sns_ddf_sensor_e sensor_type = 
    SMGR_SENSOR_TYPE(sensor_ptr, ddf_sensor_ptr->data_type);

  if( !ddf_sensor_ptr->first_synced_s4s_sample_received &&
      ddf_sensor_ptr->current_s4s.t_ph != 0 && 
      sensor_ptr->curr_s4s_sched &&
      sensor_ptr->curr_s4s_sched->ideal_sync_interval != 0 && 
      sensor_ptr->curr_s4s_sched->synced )
  {
    sns_ddf_time_t time_offset = 
      ( sensor_ptr->curr_s4s_sched->ideal_sync_offset - 
        ( ddf_sensor_ptr->latest_sample_ts + ddf_sensor_ptr->current_filter_delay ) )
      % ( sensor_ptr->curr_s4s_sched->ideal_sync_interval / ddf_sensor_ptr->current_s4s.t_ph );
    if( time_offset == 0 )
    {
        sns_smgr_vote_image_mode( SNS_IMG_MODE_BIG );
        sns_smgr_s4s_handle_first_synced_sample(ddf_sensor_ptr);
        sns_smgr_vote_image_mode( curr_mode );
    }
    else
    {
      SNS_SMGR_PRINTF4( LOW, "smgr s4s: ddf_sensor=%d non-synced TS after s4s sync latest ts %u "
                        "filter delay %u iso %u",
                        sensor_type, ddf_sensor_ptr->latest_sample_ts,
                        ddf_sensor_ptr->current_filter_delay,
                        sensor_ptr->curr_s4s_sched->ideal_sync_offset );
      SNS_SMGR_PRINTF2( LOW, "smgr s4s: isi %u tph %u",
                        sensor_ptr->curr_s4s_sched->ideal_sync_interval, ddf_sensor_ptr->current_s4s.t_ph );
    }
  }
}

/*===========================================================================

  FUNCTION:   sns_smgr_s4s_config_s4s

===========================================================================*/
/*!
  @brief Calculates S4S configuration and sends to driver

  After setting S4S config:
    Gets new max clock drift
    Gets new ODR
    Updates depot_rate

  @param[i] ddf_sensor_ptr - sensor type representing a sensor/data type pair
  @param[i] restart_schedule - true to start a new schedule

*/
/*=========================================================================*/
void sns_smgr_s4s_config_s4s( sns_smgr_ddf_sensor_s* ddf_sensor_ptr, bool restart_schedule )
{
  sns_ddf_status_e s4s_config_err;
  sns_ddf_odr_t target_odr;
  sns_ddf_s4s_config_s s4s_config;
  sns_smgr_sensor_s *sensor_ptr = ddf_sensor_ptr->sensor_ptr;
  smgr_s4s_sched_block_s *s4s_sched_ptr = sensor_ptr->curr_s4s_sched;
  sns_ddf_sensor_e sensor_type = 
    SMGR_SENSOR_TYPE(sensor_ptr, ddf_sensor_ptr->data_type);

  if( !SMGR_SENSOR_IS_S4S(sensor_ptr) )
  {
    return;
  }
  target_odr = DDF_FIXTOODR_CEIL_Q16(ddf_sensor_ptr->client_stat.max_requested_freq_hz);

  if( target_odr < 4 )
  {
    target_odr = ddf_sensor_ptr->requested_odr;
  }
  
  if( target_odr & 1 )
  {
    target_odr ++;
  }
  
  SNS_SMGR_PRINTF4( MED, "smgr_config_s4s. ddf_sensor %u restart %u max freq 0x%x target ODR %u",
                    sensor_type,
                    restart_schedule,
                    ddf_sensor_ptr->client_stat.max_requested_freq_hz,
                    target_odr);

  if ( sensor_ptr->is_uimg_refac )
  {
    s4s_config.rr = 3;
  }
  else
  {
    /* Exiting uImage can take a while. Increase RR to account for extra delays */
    s4s_config.rr = 0;
  }
  s4s_config.fifo_int_en = false;

  if( target_odr < 4 )
  {
    /* Disable S4S at low data rates -- less than 4 Hz */
    s4s_config.t_ph = 0;
    s4s_config.ideal_sync_interval = 0;
  }
  else
  {
    if( s4s_sched_ptr != NULL && !restart_schedule )
    {
      s4s_config.ideal_sync_interval = s4s_sched_ptr->ideal_sync_interval;
      s4s_config.t_ph = ddf_sensor_ptr->current_s4s.t_ph;
      s4s_config.rr = ddf_sensor_ptr->current_s4s.rr;
      s4s_config.fifo_int_en = ddf_sensor_ptr->current_s4s.fifo_int_en;
    }
    else
    {
      s4s_config.ideal_sync_interval = NOMINAL_TPH_PERIOD_TICKS / FAST_TPH_PERIOD_DIVISOR;
      s4s_config.t_ph = (uint64_t)target_odr * NOMINAL_TPH_PERIOD_TICKS / NOMINAL_S4S_1SEC_TICKS / FAST_TPH_PERIOD_DIVISOR;
      if(s4s_config.t_ph < 2)
      {
        s4s_config.t_ph = 2;
      }
      else if( s4s_config.t_ph & 1 )
      {
        s4s_config.ideal_sync_interval -=
          (float)(s4s_config.ideal_sync_interval)
          / (float)(s4s_config.t_ph);
        s4s_config.t_ph --;
      }
    }
  }

  if( ddf_sensor_ptr->current_s4s.t_ph != 0 &&
      s4s_config.t_ph != 0 )
  {
    sns_ddf_dt_t  s4s_abort_dt = false;
    sns_ddf_time_t st_time;

    if( s4s_sched_ptr != NULL && !restart_schedule )
    {
      st_time = s4s_sched_ptr->ideal_sync_offset;
      SNS_SMGR_PRINTF2( MED, "modifying current sched. ddf_sensor = %u ST: %u",
                        sensor_type,
                        st_time );
    }
    else
    {
      st_time = sns_smgr.last_tick;
      SNS_SMGR_PRINTF2( MED, "aborting current sched. ddf_sensor = %u ST: %u",
                        sensor_type,
                        st_time );
    }
      
    sns_smgr_set_attr( sensor_ptr, sensor_type, SNS_DDF_ATTRIB_S4S_ST, &st_time );
    sns_smgr_set_attr( sensor_ptr, sensor_type, SNS_DDF_ATTRIB_S4S_DT, &s4s_abort_dt );
  }

  if ( !sns_smgr_s4s_same_config(&ddf_sensor_ptr->current_s4s, &s4s_config ) )
  {
    sns_ddf_s4s_config_s s4s_config_drv_copy;
    if ( s4s_sched_ptr != NULL && restart_schedule )
    {
      s4s_sched_ptr->missed_dts = 1;
      s4s_sched_ptr->synced = false;
      ddf_sensor_ptr->first_synced_s4s_sample_received = false;
      if ( ddf_sensor_ptr->current_odr != 0 )
      {
        sns_os_mutex_pend(sensor_ptr->mutex_ptr, 0, NULL);
        SMGR_BIT_SET(sensor_ptr->flags, SMGR_SENSOR_FLAGS_UPDATE_SAMPLING_NEEDED_B);
        SMGR_BIT_SET(ddf_sensor_ptr->flags, SMGR_SENSOR_FLAGS_UPDATE_SAMPLING_NEEDED_B);
        SMGR_BIT_SET(ddf_sensor_ptr->flags, SMGR_SENSOR_FLAGS_FIRST_SYNCED_S4S_SAMPLE_B);
        sns_os_mutex_post(sensor_ptr->mutex_ptr);
        sns_smgr_signal_me(SNS_SMGR_SENSOR_STATE_SIG);
      }
      if ( ddf_sensor_ptr->latest_sample_ts != 0 )
      {
        // Pick new ideal_sync_offset (isi) to be the previous isi + N*sample_interval (using
        // the new/updated sample interval)
        sns_ddf_time_t one_new_interval = ( s4s_config.ideal_sync_interval / s4s_config.t_ph );
        sns_ddf_time_t one_old_interval = ( s4s_sched_ptr->ideal_sync_interval / ddf_sensor_ptr->current_s4s.t_ph );
        sns_ddf_time_t one_interval = MAX( one_new_interval, one_old_interval );
        
        SNS_SMGR_PRINTF3(MED, "config_s4s old int %u new int %u old iso %u",
                         one_old_interval, one_new_interval, s4s_sched_ptr->ideal_sync_offset);

        s4s_sched_ptr->ideal_sync_offset =
          s4s_sched_ptr->ideal_sync_offset +
          ( ( llabs((int64_t)s4s_sched_ptr->ideal_sync_offset - (int64_t)sns_smgr.last_tick) / one_interval ) * one_interval )+
          ( one_interval * 2 );
            
        s4s_sched_ptr->st_send_time =
          s4s_sched_ptr->ideal_sync_offset + s4s_sched_ptr->max_clock_drift*2;
        sns_smgr.sched_tick = MIN( sns_smgr.sched_tick,
                                   s4s_sched_ptr->st_send_time );
        sns_smgr_signal_me(SNS_SMGR_SENSOR_READ_SIG);
      }
    }
    SNS_SMGR_PRINTF4( HIGH, "ddf_sensor=%u Setting t_ph %d isi %d iso now %u",
                      sensor_type,
                      s4s_config.t_ph,
                      s4s_config.ideal_sync_interval,
                      s4s_sched_ptr?s4s_sched_ptr->ideal_sync_offset:0 );
    SNS_OS_MEMSCPY((void*)&s4s_config_drv_copy, sizeof(s4s_config_drv_copy),
                   (void*)&s4s_config, sizeof(s4s_config) );
    s4s_config_err =
      sns_smgr_set_attr( sensor_ptr,
                         sensor_type,
                         SNS_DDF_ATTRIB_S4S_CONFIG,
                         &s4s_config_drv_copy );
    if( s4s_config_err == SNS_DDF_SUCCESS )
    {
      ddf_sensor_ptr->current_s4s = s4s_config;
      SNS_SMGR_PRINTF4( HIGH, "Saving driver s4s settings t_ph %u isi %u "
                        "rr %u fifo_int_en %u",
                        ddf_sensor_ptr->current_s4s.t_ph,
                        ddf_sensor_ptr->current_s4s.ideal_sync_interval,
                        ddf_sensor_ptr->current_s4s.rr,
                        ddf_sensor_ptr->current_s4s.fifo_int_en );

    } else {
      SNS_SMGR_PRINTF2( ERROR, "ddf_sensor=%u Driver error %u setting S4S config.",
                        sensor_type,
                        s4s_config_err );
    }
  }
}

/*===========================================================================

  FUNCTION:   sns_smgr_s4s_update_s4s

===========================================================================*/
/*!
  @brief Reads current S4S config from driver and updates internal data

    Gets new max clock drift
    Gets new ODR
    Updates depot_rate
    Updates s4s_sched ideal sync interval

  @param[i] ddf_sensor_ptr - sensor type representing a sensor/data type pair

  @return
   true Successfully registerd into a scheduler
   false Failed to register into a scheduler because of:
   - Memory allocation failed for the new scheduler
   - etc
*/
/*=========================================================================*/
void sns_smgr_s4s_update_s4s( sns_smgr_ddf_sensor_s* ddf_sensor_ptr )
{
  sns_ddf_status_e s4s_config_err;
  sns_ddf_time_t clock_drift = 33;
  uint32_t len;
  sns_ddf_s4s_config_s *s4s_config_driver;
  sns_smgr_sensor_s *sensor_ptr = ddf_sensor_ptr->sensor_ptr;
  sns_ddf_sensor_e sensor_type = 
    SMGR_SENSOR_TYPE(sensor_ptr, ddf_sensor_ptr->data_type);

  if( !SMGR_SENSOR_IS_S4S(sensor_ptr) )
  {
    return;
  }

  s4s_config_err =
    sns_smgr_get_attr( sensor_ptr,
                       SMGR_SENSOR_TYPE(sensor_ptr, ddf_sensor_ptr->data_type),
                       SNS_DDF_ATTRIB_S4S_CONFIG,
                       (void**)&s4s_config_driver,
                       &len);
  if( s4s_config_err == SNS_DDF_SUCCESS )
  {
    smgr_s4s_sched_block_s *s4s_sched_ptr = sensor_ptr->curr_s4s_sched;
    if( sns_smgr_s4s_same_config( &ddf_sensor_ptr->current_s4s, s4s_config_driver ) != true )
    {
      /* Driver adjusted settings */
      SNS_SMGR_PRINTF4( HIGH, "driver adjusted: t_ph %u-->%u isi %u-->%u",
                        ddf_sensor_ptr->current_s4s.t_ph,
                        s4s_config_driver->t_ph,
                        ddf_sensor_ptr->current_s4s.ideal_sync_interval,
                        s4s_config_driver->ideal_sync_interval );
      SNS_SMGR_PRINTF4( HIGH, "driver adjusted: rr %u-->%u fifo_int_en %u-->%u",
                        ddf_sensor_ptr->current_s4s.rr,
                        s4s_config_driver->rr,
                        ddf_sensor_ptr->current_s4s.fifo_int_en,
                        s4s_config_driver->fifo_int_en );
      ddf_sensor_ptr->current_s4s = *s4s_config_driver;

      if( s4s_sched_ptr != NULL )
      {
        sns_os_mutex_pend(sensor_ptr->mutex_ptr, 0, NULL);
        SMGR_BIT_SET(sensor_ptr->flags, SMGR_SENSOR_FLAGS_UPDATE_SAMPLING_NEEDED_B);
        SMGR_BIT_SET(ddf_sensor_ptr->flags, SMGR_SENSOR_FLAGS_UPDATE_SAMPLING_NEEDED_B);
        sns_os_mutex_post(sensor_ptr->mutex_ptr);
      }
    }
    if( s4s_sched_ptr != NULL )
    {
      s4s_sched_ptr->ideal_sync_interval = s4s_config_driver->ideal_sync_interval;
      if( s4s_sched_ptr->ideal_sync_interval == 0 )
      {
        sns_smgr_s4s_dereg_from_sched( sensor_ptr );
        s4s_sched_ptr = NULL;
      }
    }
    else if( s4s_config_driver->ideal_sync_interval != 0 )
    {
      sns_smgr_s4s_reg_into_sched( sensor_ptr );
      s4s_sched_ptr = sensor_ptr->curr_s4s_sched;
    }
    sns_ddf_memhandler_free_ex( &sensor_ptr->memhandler, sensor_ptr );

    s4s_config_err =
      sns_smgr_get_attr( sensor_ptr, sensor_type, SNS_DDF_ATTRIB_S4S_MAX_CLOCK_DRIFT,
                         (void**)&clock_drift, &len );
    
    if( s4s_sched_ptr != NULL &&
        s4s_config_err == SNS_DDF_SUCCESS &&
        s4s_sched_ptr->max_clock_drift != clock_drift
        && clock_drift != 0 )
    {
      int32_t clock_diff = clock_drift - s4s_sched_ptr->max_clock_drift;
      SNS_SMGR_PRINTF2( HIGH, "driver adjusted: clock drift %u-->%u",
                        s4s_sched_ptr->max_clock_drift,
                        clock_drift );
      s4s_sched_ptr->max_clock_drift = clock_drift;
      if ( s4s_sched_ptr->st_send_time != 0 )
      {
        s4s_sched_ptr->st_send_time += clock_diff * s4s_sched_ptr->missed_dts;
        sns_smgr.sched_tick = MIN( sns_smgr.sched_tick, s4s_sched_ptr->st_send_time );
        sns_smgr_signal_me(SNS_SMGR_SENSOR_READ_SIG);
      }
    }
    
    ddf_sensor_ptr->depot_data_rate = sns_smgr_compute_depot_data_rate( ddf_sensor_ptr );
  }
}

/*===========================================================================

  FUNCTION:   sns_smgr_s4s_same_config

===========================================================================*/
/*!
  @brief Returns true if the S4S configurations are the same

  @Detail

  @param[i] config1
  @param[i] config2

  @return
    true if configs are the same
*/
/*=========================================================================*/
bool sns_smgr_s4s_same_config(
  const sns_ddf_s4s_config_s * restrict config1,
  const sns_ddf_s4s_config_s * restrict config2 )
{
  bool rv;

  rv = config1->t_ph == config2->t_ph &&
    config1->rr == config2->rr &&
    config1->ideal_sync_interval == config2->ideal_sync_interval &&
    config1->fifo_int_en == config2->fifo_int_en;

  return rv;
}


/*===========================================================================

  FUNCTION:   smgr_s4s_resync_sched

===========================================================================*/
/*!
  @brief Abort this schedule & sync to another one.

  @Detail

  @param[i] sched_blk_ptr - the S4S schedling block pointer

  @return
     None
*/
/*=========================================================================*/
SMGR_STATIC void smgr_s4s_resync_sched( sns_smgr_ddf_sensor_s  *ddf_sensor_ptr )
{
  smgr_s4s_sched_block_s *sched_itter;
  uint32_t est_num_samples;
  smgr_s4s_sched_block_s *s4s_sched_ptr = ddf_sensor_ptr->sensor_ptr->curr_s4s_sched;

  SNS_SMGR_PRINTF1( HIGH, "s4s resync ddf_sensor=%u",
                    SMGR_SENSOR_TYPE(ddf_sensor_ptr->sensor_ptr,
                                     ddf_sensor_ptr->data_type) );

  if( !SMGR_SENSOR_IS_S4S(ddf_sensor_ptr->sensor_ptr) )
  {
    return;
  }

  /* Read the data */
  sns_smgr_get_estimated_read_time(ddf_sensor_ptr,
                                   &est_num_samples);
  if( est_num_samples != 0 )
  {
    smgr_get_data(ddf_sensor_ptr);
  }
          
  ddf_sensor_ptr->current_s4s.t_ph =
    ddf_sensor_ptr->current_s4s.t_ph * NOMINAL_TPH_PERIOD_TICKS / s4s_sched_ptr->ideal_sync_interval;
  s4s_sched_ptr->ideal_sync_interval = NOMINAL_TPH_PERIOD_TICKS;
  SMGR_FOR_EACH_Q_ITEM(&sns_smgr.s4s_que, sched_itter, sched_link)
  {
    if( sched_itter != s4s_sched_ptr &&
        sched_itter->ideal_sync_offset &&
        sched_itter->synced == true  &&
        sched_itter->ideal_sync_offset != s4s_sched_ptr->ideal_sync_offset )
    {
      SNS_SMGR_PRINTF1( LOW, "found synced sched. iso: %d", sched_itter->ideal_sync_offset);
      s4s_sched_ptr->ideal_sync_offset = sched_itter->ideal_sync_offset;
      // TODO: update send time to account for different clock drifts
      s4s_sched_ptr->st_send_time = sched_itter->st_send_time;
      if( s4s_sched_ptr->st_send_time > sns_smgr.last_tick )
      {
        s4s_sched_ptr->st_send_time -= s4s_sched_ptr->ideal_sync_interval;
        s4s_sched_ptr->ideal_sync_offset -= s4s_sched_ptr->ideal_sync_interval;
      }
      break;
    }
  }
  sns_smgr_s4s_config_s4s( ddf_sensor_ptr, false );
  sns_os_mutex_pend(ddf_sensor_ptr->sensor_ptr->mutex_ptr, 0, NULL);
  SMGR_BIT_SET(ddf_sensor_ptr->sensor_ptr->flags, SMGR_SENSOR_FLAGS_ODR_CHANGED_B);
  SMGR_BIT_SET(ddf_sensor_ptr->flags, SMGR_SENSOR_FLAGS_ODR_CHANGED_B);
  sns_os_mutex_post(ddf_sensor_ptr->sensor_ptr->mutex_ptr);
  sns_smgr_signal_me(SNS_SMGR_SENSOR_STATE_SIG);
}

/*===========================================================================

  FUNCTION:   sns_smgr_s4s_reg_into_sched

===========================================================================*/
/*!
  @brief Adds a sensor to the S4S schedule.

  @Detail

  @param[i] sensor_ptr - sensor to add

*/
/*=========================================================================*/
void sns_smgr_s4s_reg_into_sched( sns_smgr_sensor_s *sensor_ptr )
{
  smgr_s4s_sched_block_s *s4s_sched_ptr = sensor_ptr->curr_s4s_sched;
  smgr_s4s_sched_block_s *sched_itter;

  if( !SMGR_SENSOR_IS_S4S(sensor_ptr) )
  {
    return;
  }
  SNS_SMGR_PRINTF1(HIGH, "S4S registering new schedule. Sensor ID = %u",
                   SMGR_SENSOR_ID(sensor_ptr) );

  if( s4s_sched_ptr == NULL )
  {
    SNS_SMGR_PRINTF0(ERROR, "curr_s4s_sched is NULL!");
    sns_smgr_s4s_init_new_sched_block( sensor_ptr );
    s4s_sched_ptr = sensor_ptr->curr_s4s_sched;
  }

  sns_os_mutex_pend(sensor_ptr->mutex_ptr, 0, NULL);

  if( s4s_sched_ptr->ideal_sync_offset == 0 )
  {
    sched_itter = sns_q_check(&sns_smgr.s4s_que);
    uint32_t sched_intvl = INT_MAX;
    int i;
    for ( i = 0; i < ARR_SIZE(sensor_ptr->ddf_sensor_ptr); i++ )
    {
      if ( sensor_ptr->ddf_sensor_ptr[i] != NULL )
      {
        q16_t synced_depot_data_rate;
        synced_depot_data_rate =
          FX_FLTTOFIX_Q16((float)sensor_ptr->ddf_sensor_ptr[i]->current_s4s.t_ph
                          * (float)DSPS_SLEEP_CLK
                          / (float)sensor_ptr->curr_s4s_sched->ideal_sync_interval);
        
        sched_intvl =
          MIN( sched_intvl,
               sns_smgr_get_sched_intval(synced_depot_data_rate) );
      }
    }

    if( sched_itter != NULL )
    {
      int num_fifo_intvls;

      s4s_sched_ptr->ideal_sync_offset = sched_itter->ideal_sync_offset;
      if( s4s_sched_ptr->ideal_sync_offset < sns_smgr.last_tick )
      {
        s4s_sched_ptr->ideal_sync_offset += sched_itter->ideal_sync_interval;
      }
      num_fifo_intvls = (s4s_sched_ptr->ideal_sync_offset-sns_smgr.last_tick) / sched_intvl;
      s4s_sched_ptr->ideal_sync_offset -= num_fifo_intvls * sched_intvl;
    }
    else
    {
      s4s_sched_ptr->ideal_sync_offset = 
        sns_smgr.sched_tick + sched_intvl - SMGR_PRIMARY_SENSOR(sensor_ptr)->current_filter_delay;
    }
    s4s_sched_ptr->st_send_time = s4s_sched_ptr->ideal_sync_offset + (s4s_sched_ptr->max_clock_drift << 1);
  }

  // TODO: pointer to primary sensor?
  s4s_sched_ptr->ddf_sensor_ptr = SMGR_PRIMARY_SENSOR(sensor_ptr);
  SNS_SMGR_PRINTF4( MED, "s4s: creating new schedule now: %u sync_offset: %u drift: %u interval: %u",
                    sns_smgr.last_tick,
                    s4s_sched_ptr->ideal_sync_offset,
                    s4s_sched_ptr->max_clock_drift,
                    s4s_sched_ptr->ideal_sync_interval );
  if( Q_ALREADY_QUEUED( &s4s_sched_ptr->sched_link ) ) {
    SNS_SMGR_PRINTF1(HIGH, "Sensor already registered in scheduler ID = %u",
                     SMGR_SENSOR_ID(sensor_ptr) );
  }
  else
  {
    sns_q_put( &sns_smgr.s4s_que, &s4s_sched_ptr->sched_link );
  }
  sns_smgr.sched_tick = MIN(sns_smgr.sched_tick,
                            s4s_sched_ptr->st_send_time );

  SMGR_BIT_SET(sensor_ptr->flags, SMGR_SENSOR_FLAGS_UPDATE_SAMPLING_NEEDED_B);
  SMGR_BIT_SET(SMGR_PRIMARY_SENSOR(sensor_ptr)->flags, SMGR_SENSOR_FLAGS_UPDATE_SAMPLING_NEEDED_B);
  sns_os_mutex_post(sensor_ptr->mutex_ptr);
  sns_smgr_signal_me(SNS_SMGR_SENSOR_STATE_SIG);
}
   
/*===========================================================================

  FUNCTION:   smgr_s4s_process_missed_dt_changed

===========================================================================*/
/*!
  @brief Handles the event when the missed_dt value for a sensor has changed

  May update the S4S schedule, and cause the FIFO read schedule to be updated.

  @param[i] s4s_blk_ptr -- pointer to S4S schedule block for the sensor.
  @param[i] dt_status   -- Status from the driver for sending the S4S DT message

*/
/*=========================================================================*/
SMGR_STATIC void smgr_s4s_process_missed_dt_changed( smgr_s4s_sched_block_s *s4s_blk_ptr,
                                                     sns_ddf_status_e        dt_status )
{
  sns_smgr_ddf_sensor_s *ddf_sensor_ptr = s4s_blk_ptr->ddf_sensor_ptr;
  sns_smgr_sensor_s     *sensor_ptr = ddf_sensor_ptr->sensor_ptr;
  
  if( dt_status == SNS_DDF_SUCCESS )
  {
    if( s4s_blk_ptr->missed_dts == 0 && s4s_blk_ptr->synced == false )
    {
      s4s_blk_ptr->synced = true;
      smgr_s4s_resync_sched( ddf_sensor_ptr );
    }
    s4s_blk_ptr->missed_dts = 0;
  }
  else
  {
    if( s4s_blk_ptr->missed_dts < S4S_MAX_MISSED_DTS )
    {
      s4s_blk_ptr->missed_dts++;
      s4s_blk_ptr->st_send_time += s4s_blk_ptr->max_clock_drift;
    }
  }  
  if( s4s_blk_ptr->synced == true )
  {
    s4s_blk_ptr->st_send_time -= s4s_blk_ptr->max_clock_drift * s4s_blk_ptr->missed_dts;
    sns_os_mutex_pend(sensor_ptr->mutex_ptr, 0, NULL);
    SMGR_BIT_SET(sensor_ptr->flags, SMGR_SENSOR_FLAGS_UPDATE_SAMPLING_NEEDED_B);
    SMGR_BIT_SET(ddf_sensor_ptr->flags, SMGR_SENSOR_FLAGS_UPDATE_SAMPLING_NEEDED_B);
    sns_os_mutex_post(sensor_ptr->mutex_ptr);
    sns_smgr_signal_me(SNS_SMGR_SENSOR_STATE_SIG);
  }
}

/*----------------------------------------------------------------------------
 *  External uImage functions
 * -------------------------------------------------------------------------*/

/*===========================================================================

  FUNCTION:   smgr_s4s_proc_s4s_schedule

===========================================================================*/
/*!
  @brief Processes the S4S blocks

  @Detail

  @return
    next tick offset for the next schedule
*/
/*=========================================================================*/
SNS_SMGR_UIMAGE_CODE int32_t sns_smgr_s4s_proc_s4s_schedule( void )
{
  smgr_s4s_sched_block_s *s4s_blk_ptr = NULL;
  sns_smgr_ddf_sensor_s  *ddf_sensor_ptr;
  sns_smgr_sensor_s      *sensor_ptr;
  sns_ddf_status_e        dt_status;
  int32_t                 next_tick_offset = SMGR_MAX_TICKS;
  sns_ddf_dt_t            s4s_true_dt = true;
  sns_ddf_time_t          proc_time = sns_smgr.sched_tick;


  SMGR_FOR_EACH_Q_ITEM(&sns_smgr.s4s_que, s4s_blk_ptr, sched_link)
  {
    ddf_sensor_ptr = s4s_blk_ptr->ddf_sensor_ptr;
    sensor_ptr = ddf_sensor_ptr->sensor_ptr;
    if( s4s_blk_ptr->st_send_time <= proc_time )
    {
      sns_hw_set_qup_clk(true);
      SNS_SMGR_PRINTF4( HIGH, "s4s proc. ddf_sensor=%u Setting ST:%u sched_tick: %u now: %u",
                        SMGR_SENSOR_TYPE(sensor_ptr,
                                         ddf_sensor_ptr->data_type),
                        s4s_blk_ptr->ideal_sync_offset,
                        proc_time,
                        sns_ddf_get_timestamp());
      sns_smgr_set_attr( sensor_ptr,
                         SMGR_SENSOR_TYPE(sensor_ptr, ddf_sensor_ptr->data_type),
                         SNS_DDF_ATTRIB_S4S_ST,
                         &s4s_blk_ptr->ideal_sync_offset );
    }
  }
  SMGR_FOR_EACH_Q_ITEM(&sns_smgr.s4s_que, s4s_blk_ptr, sched_link)
  {
    ddf_sensor_ptr = s4s_blk_ptr->ddf_sensor_ptr;
    sensor_ptr = ddf_sensor_ptr->sensor_ptr;

    if( s4s_blk_ptr->st_send_time <= proc_time )
    {
      sns_pm_img_mode_e curr_mode = sns_smgr_get_curr_image_vote();
      dt_status = sns_smgr_set_attr( sensor_ptr,
                                     SMGR_SENSOR_TYPE(sensor_ptr, ddf_sensor_ptr->data_type),
                                     SNS_DDF_ATTRIB_S4S_DT,
                                     &(s4s_true_dt) );
      
      if( dt_status!=SNS_DDF_SUCCESS || s4s_blk_ptr->missed_dts!=0 || !s4s_blk_ptr->synced )
      {
        sns_smgr_vote_image_mode( SNS_IMG_MODE_BIG );
        smgr_s4s_process_missed_dt_changed( s4s_blk_ptr, dt_status );
        sns_smgr_vote_image_mode( curr_mode );
      }
      s4s_blk_ptr->ideal_sync_offset += s4s_blk_ptr->ideal_sync_interval;
      s4s_blk_ptr->st_send_time += s4s_blk_ptr->ideal_sync_interval;
    }
    next_tick_offset = MIN( next_tick_offset,
                            s4s_blk_ptr->st_send_time - (int64_t)sns_smgr.sched_tick);
    if( next_tick_offset < 0 ) {
      next_tick_offset = 0;
    }
    SNS_SMGR_PRINTF3(LOW,"s4s proc. ddf_sensor=%u next ST send: %u next_tick now %d",
                     SMGR_SENSOR_TYPE(sensor_ptr,
                                      ddf_sensor_ptr->data_type),
                     s4s_blk_ptr->st_send_time, next_tick_offset );
  }
  
  sns_hw_set_qup_clk(false);
  return next_tick_offset;
}

/*===========================================================================

  FUNCTION:   sns_smgr_s4s_get_next_sched_time

===========================================================================*/
/*!
  @brief Returns the time of the next S4S schedule

  @Detail

  @return
    next tick offset for the next schedule.
    ULLONG_MAX if there is no schedule
*/
/*=========================================================================*/
SNS_SMGR_UIMAGE_CODE sns_ddf_time_t sns_smgr_s4s_get_next_sched_time( void )
{
  smgr_s4s_sched_block_s *s4s_blk_ptr;
  sns_ddf_time_t          next_tick = ULLONG_MAX;

  SMGR_FOR_EACH_Q_ITEM(&sns_smgr.s4s_que, s4s_blk_ptr, sched_link)
  {
    next_tick = MIN( next_tick,
                     s4s_blk_ptr->st_send_time );
  }
  return next_tick;
}

/*===========================================================================

  FUNCTION:   sns_smgr_s4s_get_next_sample_ts

===========================================================================*/
/*!
  @brief Returns the projected S4S-aligned timestamp after the provided time

  @param ddf_sensor_ptr[i] S4S sensor to get the next timestamp

  @param timestamp[i]      Returned timestamp will be the timestamp greater
                           than this time

  @return
    0 if S4S is not initialized
*/
/*=========================================================================*/
SNS_SMGR_UIMAGE_CODE
sns_ddf_time_t sns_smgr_s4s_get_next_sample_ts( sns_smgr_ddf_sensor_s const* ddf_sensor_ptr,
                                                sns_ddf_time_t timestamp )
{
  smgr_s4s_sched_block_s *s4s_sched_ptr;
  sns_ddf_time_t next_ts = 0;
#ifndef FAST_PLAYBACK

  s4s_sched_ptr = ddf_sensor_ptr->sensor_ptr->curr_s4s_sched;
  if( s4s_sched_ptr != NULL && ddf_sensor_ptr->current_s4s.t_ph != 0
      && s4s_sched_ptr->ideal_sync_interval != 0)
  {
    sns_ddf_time_t one_interval;
    sns_ddf_time_t iso;

    if( s4s_sched_ptr->ideal_sync_offset == 0 )
    {
      /* Sensor not yet registered into the S4S schedule. Register it now */
      sns_pm_img_mode_e curr_mode = sns_smgr_get_curr_image_vote();
      sns_smgr_vote_image_mode( SNS_IMG_MODE_BIG );
      sns_smgr_s4s_reg_into_sched( ddf_sensor_ptr->sensor_ptr );
      sns_smgr_vote_image_mode( curr_mode );
    }

    iso = s4s_sched_ptr->ideal_sync_offset;
    while( (timestamp + ddf_sensor_ptr->current_filter_delay) >= iso )
    {
      iso += s4s_sched_ptr->ideal_sync_interval;
    }
    one_interval = ( s4s_sched_ptr->ideal_sync_interval / ddf_sensor_ptr->current_s4s.t_ph );
    next_ts = iso - ( (iso - timestamp) / one_interval * one_interval );
    next_ts -= ddf_sensor_ptr->current_filter_delay;
    SNS_SMGR_PRINTF5(
      MED, "get_next_sample_ts - t_ph=%u isi=%u delay=%u given=%u next=%u", 
      ddf_sensor_ptr->current_s4s.t_ph, s4s_sched_ptr->ideal_sync_interval, 
      ddf_sensor_ptr->current_filter_delay, timestamp, next_ts);
  }
  else
  {
    SNS_SMGR_PRINTF3(ERROR, "get_next_sample_ts - invalid state. sched_ptr=%u t_ph=%u isi=%u",
                     s4s_sched_ptr,
                     s4s_sched_ptr?ddf_sensor_ptr->current_s4s.t_ph:0,
                     s4s_sched_ptr?s4s_sched_ptr->ideal_sync_interval:0 );
                     
  }
#endif
  return next_ts;
}
