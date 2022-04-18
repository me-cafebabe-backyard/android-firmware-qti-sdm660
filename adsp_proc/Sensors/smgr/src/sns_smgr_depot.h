#ifndef SNS_SMGR_DEPOT_H
#define SNS_SMGR_DEPOT_H
/*=============================================================================
  @file sns_smgr_depot.h

  This header file contains the definitions for internal depot in which sensor
  samples are stored by Sensor Manager (SMGR)

******************************************************************************
* Copyright (c) 2014-2016 Qualcomm Technologies, Inc.  All Rights Reserved.
* Qualcomm Technologies Proprietary and Confidential.
******************************************************************************/

/* $Header: //components/rel/ssc.slpi/2.2/smgr/src/sns_smgr_depot.h#1 $ */
/* $DateTime: 2017/04/17 22:20:39 $ */
/* $Author: pwbldsvc $ */

/*============================================================================
  EDIT HISTORY FOR FILE

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------
  2016-08-10  np   Added playback support.  
  2015-08-24  bd   Depot size reduction
  2015-04-21  pn   Fixed deficient depot copy method
  2015-04-09  pn   Added support for 56-bit timestamp
  2014-10-26  pn   Updated sns_smgr_depot_dump()
  2014-09-25  pn   Added sns_smgr_depot_dump()
  2014-04-23  pn   Initial revision

============================================================================*/

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "sns_smgr.h"
#include "sns_smgr_priv.h"

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/
//#define SNS_SMGR_DEPOT_DEBUG
#ifdef SNS_SMGR_DEPOT_DEBUG
#define SNS_SMGR_DEPOT_DBG0 SNS_SMGR_PRINTF0
#define SNS_SMGR_DEPOT_DBG1 SNS_SMGR_PRINTF1
#define SNS_SMGR_DEPOT_DBG2 SNS_SMGR_PRINTF2
#define SNS_SMGR_DEPOT_DBG3 SNS_SMGR_PRINTF3
#define SNS_SMGR_DEPOT_DBG4 SNS_SMGR_PRINTF4
#else
#define SNS_SMGR_DEPOT_DBG0(level,msg)
#define SNS_SMGR_DEPOT_DBG1(level,msg,p1)
#define SNS_SMGR_DEPOT_DBG2(level,msg,p1,p2)
#define SNS_SMGR_DEPOT_DBG3(level,msg,p1,p2,p3)
#define SNS_SMGR_DEPOT_DBG4(level,msg,p1,p2,p3,p4)
#endif

/* within the status_n_ts_hi field of sample structure
   the upper most byte is the status and
   the lower three bytes are the upper part of the 56-bit timestamp */
#define SMGR_SAMPLE_TIMESTAMP(sp)         \
  ( (sns_ddf_time_t) (((sns_ddf_time_t)((sp)->status_n_ts_hi & 0xFFFFFF) << 32) | (sp)->ts_lo) )

#define SMGR_SAMPLE_TIMESTAMP_SET(sp,ts)  \
  ( (sp)->ts_lo = (uint32_t)(ts), \
    (sp)->status_n_ts_hi = ((ts >> 32) & 0xFFFFFF) | ((sp)->status_n_ts_hi & 0xFF000000) )

#define SMGR_SAMPLE_STATUS(sp)            \
  ( (sns_ddf_status_e)((sp)->status_n_ts_hi >> 24) )

#define SMGR_SAMPLE_STATUS_SET(sp,st)     \
  ( (sp)->status_n_ts_hi = (((uint32_t)(st) << 24) & 0xFF000000) | \
                           ((sp)->status_n_ts_hi & 0xFFFFFF) )

/*----------------------------------------------------------------------------
 * Structures
 * -------------------------------------------------------------------------*/
typedef struct 
{
  q16_t              data[SNS_SMGR_SENSOR_DIMENSION_V01];
  uint32_t           status_n_ts_hi; /* most significant byte is status */
  uint32_t           ts_lo;          /* the lower 32-bit of timestamp */
} sns_smgr_sample_s;

typedef struct 
{
  uint16_t           max_bufs;
  uint16_t           used_bufs;
  uint16_t           first_idx;  /* index to oldest sample */
  uint16_t           last_idx;   /* index to latest sample */
  uint8_t            num_axes;   /* depending on sensor type */
  sns_smgr_sample_s  samples[1]; /* many to be saved */
} sns_smgr_sample_depot_s;

typedef struct
{
  const sns_smgr_sample_depot_s* depot_ptr;
  uint16_t                   idx;
} sns_smgr_sample_depot_iter_s;

/*----------------------------------------------------------------------------
 * Function Declarations and Documentation
 * -------------------------------------------------------------------------*/
void sns_smgr_depot_clear(
   sns_smgr_sample_depot_s* depot_ptr, 
   uint16_t                 num_save);

uint16_t sns_smgr_depot_get_depth(
   const sns_smgr_sample_depot_s*);

uint16_t sns_smgr_depot_get_sample_count(
   const sns_smgr_sample_depot_s*);

const sns_smgr_sample_s* sns_smgr_depot_get_latest_sample(
   const sns_smgr_sample_depot_s*);

const sns_smgr_sample_s* sns_smgr_depot_get_oldest_sample(
   const sns_smgr_sample_depot_s*);

const sns_smgr_sample_s* sns_smgr_depot_init_iter(
   const sns_smgr_sample_depot_s*, 
   sns_ddf_time_t, 
   sns_smgr_sample_depot_iter_s*);

const sns_smgr_sample_s* sns_smgr_depot_get_sample(
   sns_smgr_sample_depot_iter_s*, 
   int8_t);

const sns_smgr_sample_s* sns_smgr_depot_put_sample(
   sns_smgr_sample_depot_s*     depot_ptr, 
   const sns_ddf_sensor_data_s* src_ptr);
#ifdef FAST_PLAYBACK
void sns_smgr_handle_new_sample(
   sns_smgr_ddf_sensor_s*       ddf_sensor_ptr,
   const sns_ddf_sensor_data_s* data_ptr);
#endif
#endif /* #ifndef SNS_SMGR_DEPOT_H */

