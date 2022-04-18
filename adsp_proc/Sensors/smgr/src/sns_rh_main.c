/*=============================================================================
  @file sns_rh_main.c

  This file implements Request Handler task.

*******************************************************************************
* Copyright (c) 2014-2016 Qualcomm Technologies, Inc.
* All Rights Reserved.
* Confidential and Proprietary - Qualcomm Technologies, Inc.
********************************************************************************/

/* $Header: //components/rel/ssc.slpi/2.2/smgr/src/sns_rh_main.c#3 $ */
/* $DateTime: 2017/07/26 22:19:12 $ */
/* $Author: pwbldsvc $ */

/*============================================================================
  EDIT HISTORY FOR FILE

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------
  2017-07-17  rb   Stability adsp crash issue fix
  2017-05-18  ak   Self test SMGR API enhancement to return more than true/false
  2016-12-07  bd   Replaced SNS_RH_RESCHED_REPORTS_SIG with SNS_RH_SENSOR_CONFIG_DONE_SIG
  2016-12-01  bd   Fixed possible mem leak
  2016-10-20  tc   Limit the max advertised sampling rate to 400 Hz
  2016-09-12  np   Re-added support for SMGR_CAL_REQ_MSG
  2016-08-25  np   Added playback support.
  2016-08-23  np   Legacy process cal request function removed.
  2016-07-22  pn   Some functions moved from uImage module
  2016-07-19  bd   Wait for SMGR notification before processing other msg
  2016-07-13  np   Support for calibration algorithm 
  2016-04-13  ks   Dynamic calibration reset api support
  2016-03-11  bd   Move reserved fifo size to uimage
  2016-03-14  gju  Use consolidated SNS_OS_FREE to free any memory block
  2016-03-02  pn   Processes WAKE_SIG in bigImage
  2015-12-03  jtl  Added initial S4S implementation
  2016-02-08  gju  Update sns_batchbuff header file name
  2016-02-05  pn   Added SNS_RH_RESCHED_REPORTS_SIG
  2016-01-29  sc   Added TITL_EVENT and ORIENTATION_EVENT to short_names[]
  2016-01-26  pn   RH is no longer a child thread of SMGR
  2015-12-09  BD   Added reserved fifo size into sensor info response
  2015-09-29  pn   Processes incoming messages before disconnection signal
  2015-09-08  BD   Change the advertised depot depth
  2015-08-24  pn   Added support for concurrent selftest and streaming
  2015-08-24  BD   Changed the advertise depot depth
  2015-08-18  BD   -Move batchbuff low request handling to uimg
                   -Remove batchbuff block before going to suspend mode
  2015-07-30  BD   Added SNS_RH_BATCHBUFF_LOW_SIG and batch memory utility
  2015-05-27  BD   Add SNS_RH_SMR_RESUME_SIG and smr resume function
  2015-04-09  pn   Replaced calls to sns_em_get_timestamp() with sns_ddf_get_timestamp()
  2015-04-03  AH   Added Object Temperature sensor type
  2015-03-12  AH   Added Heart Rate sensor type
  2015-03-03  pn   Flushes affected reports before ODR is changed as result of 
                   reports getting deleted when their connection is terminated
  2015-02-18  MW   Added UV sensor type
  2015-01-20  pn   Removed unnecessary calls to memhandler funtions
  2015-01-16  vy   Moved uImage logging to debug module  
  2014-12-07  pn   Handles requests orphaned by QMI disconnection
  2014-11-11  dk   Added support for handling SNS_RH_LOGPKT_DROP_SIG
  2014-11-06  dk   Added sns_rh_logpkt_lowmem_flush_cb
  2014-11-04  pn   Removed all references to SNS_RH_SENSOR_EVENT_ENABLE_SIG
  2014-09-25  pn   Uses depot selected for report item
  2014-09-14  vy   Used new uImage supported DDF api to free memhandler
  2014-07-21  pn   Updated sensor_event implementation to support updated API
  2014-06-16  pn   Avoided unnecessary task context switch
  2014-06-16  pn   Unshared sns_rh_uimg
  2014-06-11  vy   Further refactored to support uImage
  2014-05-23  pn   Sensor is deemed busy when its state is above IDLE
  2014-05-07  pn   Added support for MD deregistration
  2014-05-02  aj   Replaced QMI with SMR
  2014-04-29  pn   Refactored to support microImage
  2014-04-23  pn   Initial version
  ============================================================================*/
/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#ifndef FAST_PLAYBACK
#include <stringl.h>
#endif
#include "sensor1.h"
#include "sns_batchbuff.h"
#include "sns_init.h"
#include "sns_memmgr.h"
#include "sns_osa.h"
#include "sns_rh_batchbuff.h"
#include "sns_rh_internal_svc.h"
#include "sns_rh_main.h"
#include "sns_rh_main_uimg.h"
#include "sns_rh_restricted_svc.h"
#include "sns_rh_rpt_gen.h"
#include "sns_rh_sol.h"
#include "sns_rh_util.h"
#include "sns_smgr_main.h"
#include "sns_smgr_util.h"
#include "sns_rh_cal.h"
#ifdef FAST_PLAYBACK
#include "sns_debug_str.h"
#include "playback.h"
#include "sns_sam_qmag_cal_v01.h"
#include "sns_sam_gyro_cal_v01.h"
#endif
/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/
#define TICK_MOD_MASK                      0xFFFFFFFF
#define __SNS_MODULE__ SNS_RH

// PEND: Ideally the RH shouldn't have to limit the advertised sampling rates
//       but until we fix the congestion issues in the transport layer, we have
//       to settle with this limitation.
// NOTE: THIS DOES NOT PREVENT ANY CLIENT FOR ASKING FOR (AND RECEIVING) A
//       HIGHER SAMPLING RATE!
#define SNS_RH_MAX_ADVERTISED_SAMPLING_RATE_HZ  400

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/
typedef struct
{
  smgr_sensor_id_e sensor_id;
  char*            short_name_ptr;
} sns_rh_sensor_short_name_s;

/*----------------------------------------------------------------------------
 *  Variables
 * -------------------------------------------------------------------------*/
static const sns_rh_sensor_short_name_s sns_rh_sensor_short_names[] =
{
  { SNS_SMGR_ID_ACCEL_V01,                "ACCEL"                     },
  { SNS_SMGR_ID_ACCEL_2_V01,              "ACCEL2"                    },
  { SNS_SMGR_ID_ACCEL_3_V01,              "ACCEL3"                    },
  { SNS_SMGR_ID_ACCEL_4_V01,              "ACCEL4"                    },
  { SNS_SMGR_ID_ACCEL_5_V01,              "ACCEL5"                    },
  { SNS_SMGR_ID_GYRO_V01,                 "GYRO"                      },
  { SNS_SMGR_ID_MAG_V01,                  "MAG"                       },
  { SNS_SMGR_ID_PRESSURE_V01,             "PRESSURE"                  },
  { SNS_SMGR_ID_PROX_LIGHT_V01,           "PROX_LIGHT"                },
  { SNS_SMGR_ID_IR_GESTURE_V01,           "IR_GESTURE"                },
  { SNS_SMGR_ID_TAP_V01,                  "TAP"                       },
  { SNS_SMGR_ID_STEP_EVENT_V01,           "StepDetector"              },
  { SNS_SMGR_ID_STEP_COUNT_V01,           "StepCount"                 },
  { SNS_SMGR_ID_SMD_V01,                  "SignificantMotionDetector" },
  { SNS_SMGR_ID_GAME_ROTATION_VECTOR_V01, "GameRotationVector"        },
  { SNS_SMGR_ID_HUMIDITY_V01,             "HUMIDITY"                  },
  { SNS_SMGR_ID_RGB_V01,                  "RGB"                       },
  { SNS_SMGR_ID_RGB_2_V01,                "RGB2"                      },
  { SNS_SMGR_ID_SAR_V01,                  "SAR"                       },
  { SNS_SMGR_ID_SAR_2_V01,                "SAR2"                      },
  { SNS_SMGR_ID_HALL_EFFECT_V01,          "HALL_EFFECT"               },
  { SNS_SMGR_ID_ULTRA_VIOLET_V01,         "ULTRA_VIOLET"              },
  { SNS_SMGR_ID_HEART_RATE_V01,           "HEART_RATE"                },
  { SNS_SMGR_ID_OBJECT_TEMP_V01,          "OBJECT_TEMP"               },
  { SNS_SMGR_ID_TILT_EVENT_V01,           "TILT_EVENT"                },
  { SNS_SMGR_ID_ORIENTATION_EVENT_V01,    "ORIENTATION_EVENT"         },
  { SNS_SMGR_ID_OEM_SENSOR_01_V01,        "OEM1"                      },
  { SNS_SMGR_ID_OEM_SENSOR_02_V01,        "OEM2"                      },
  { SNS_SMGR_ID_OEM_SENSOR_03_V01,        "OEM3"                      },
  { SNS_SMGR_ID_OEM_SENSOR_04_V01,        "OEM4"                      },
  { SNS_SMGR_ID_OEM_SENSOR_05_V01,        "OEM5"                      },
  { SNS_SMGR_ID_OEM_SENSOR_06_V01,        "OEM6"                      },
  { SNS_SMGR_ID_OEM_SENSOR_07_V01,        "OEM7"                      },
  { SNS_SMGR_ID_OEM_SENSOR_08_V01,        "OEM8"                      },
  { SNS_SMGR_ID_OEM_SENSOR_09_V01,        "OEM9"                      },
  { SNS_SMGR_ID_OEM_SENSOR_10_V01,        "OEM10"                     },
};

sns_rh_s sns_rh;


/*----------------------------------------------------------------------------
 * Macro
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Function Declarations and Documentation
 * -------------------------------------------------------------------------*/
/*===========================================================================

  FUNCTION:   sns_smgr_proc_sensor_status_req_msg

===========================================================================*/
/*!
  @brief This function process a sensor status report request message, add or
         delete a client from power status report list

  @detail

  @param[i] Hdr_p request message header
  @param[i] Msg_p request message pointer
  @param[o] Response  response pointer
  @return  none
 */
/*=========================================================================*/
SMGR_STATIC sns_err_code_e sns_rh_process_sensor_status_request(
  sns_rh_mr_req_q_item_s* msg_ptr)
{
  sns_smgr_sensor_status_req_msg_v01* req_ptr =
    &msg_ptr->request.deprecated_sensor_status;
  sns_smgr_sensor_status_resp_msg_v01* resp_ptr;
  sns_rh_mr_header_s resp_msg_header = msg_ptr->header;
  /* -------------------------------------------------------------------- */

  SNS_SMGR_PRINTF2(MED, "sensor_status_req - action=%d sensor=%d",
                   req_ptr->Action, req_ptr->SensorID);

  resp_ptr = SMGR_ALLOC_STRUCT(sns_smgr_sensor_status_resp_msg_v01);
  if ( resp_ptr == NULL )
  {
    return SNS_ERR_NOMEM;
  }

  resp_ptr->Resp.sns_result_t = SNS_RESULT_FAILURE_V01;
  resp_ptr->Resp.sns_err_t    = SENSOR1_ENOTALLOWED;
  resp_ptr->SensorID          = req_ptr->SensorID;
  resp_msg_header.msg_id      = SNS_SMGR_SENSOR_STATUS_RESP_V01;
  resp_msg_header.body_len    = sizeof(sns_smgr_sensor_status_resp_msg_v01);

  sns_rh_mr_send_resp(&resp_msg_header, (void**)&resp_ptr);

  return SNS_SUCCESS;
}

/*===========================================================================

  FUNCTION:   sns_rh_sol_process_all_sensor_info_request

===========================================================================*/
/*!
  @brief Processes SNS_SMGR_ALL_SENSOR_INFO_REQ_V01.

  @detail Builds and sends a list of names of all the supported sensors.

  @param[i]  hdr_ptr    - message header

  @return SNS_SUCCESS or SNS_ERR_NOMEM
 */
/*=========================================================================*/
SMGR_STATIC sns_err_code_e sns_rh_process_all_sensor_info_request(
  sns_rh_mr_req_q_item_s*  msg_ptr)
{
  uint8_t i, j;
  sns_rh_mr_header_s resp_msg_header = msg_ptr->header;
  sns_smgr_all_sensor_info_resp_msg_v01* resp_ptr =
    SMGR_ALLOC_STRUCT(sns_smgr_all_sensor_info_resp_msg_v01);
  /* -------------------------------------------------------------------- */

  if ( resp_ptr == NULL )
  {
    return SNS_ERR_NOMEM;
  }

  SNS_OS_MEMZERO(resp_ptr, sizeof(sns_smgr_all_sensor_info_resp_msg_v01));
  for ( i=0; i<ARR_SIZE(sns_smgr.sensor); i++ )
  {
    sns_smgr_sensor_s* sensor_ptr = &sns_smgr.sensor[i];
#ifndef FAST_PLAYBACK
    if ( (sensor_ptr != NULL) && (SMGR_DRV_FN_PTR(sensor_ptr) != NULL) &&
         (sensor_ptr->dd_handle != NULL ) &&
         (sensor_ptr->sensor_state != SENSOR_STATE_FAILED) )
#else
    if ( (sensor_ptr != NULL))
#endif
    {
      sns_smgr_sensor_id_info_s_v01* sensor_info_ptr =
        &resp_ptr->SensorInfo[resp_ptr->SensorInfo_len++];
      for ( j=0; j<ARR_SIZE(sns_rh_sensor_short_names); j++ )
      {
        if ( sns_rh_sensor_short_names[j].sensor_id ==
             sensor_ptr->const_ptr->sensor_id )
        {
          strlcpy(sensor_info_ptr->SensorShortName,
                  sns_rh_sensor_short_names[j].short_name_ptr,
                  sizeof(sensor_info_ptr->SensorShortName));
          break;
        }
      }
      if ( j >= ARR_SIZE(sns_rh_sensor_short_names))
      {
        strlcpy(sensor_info_ptr->SensorShortName, "UNKNOWN",
                sizeof(sensor_info_ptr->SensorShortName));
      }
      sensor_info_ptr->SensorShortName_len = strlen(sensor_info_ptr->SensorShortName);
      sensor_info_ptr->SensorID = sensor_ptr->const_ptr->sensor_id;
    }
  }
  SNS_SMGR_PRINTF1(
    MED, "all_sensor_info - #sensor=%d", (unsigned)resp_ptr->SensorInfo_len);

  resp_ptr->Resp.sns_result_t = SNS_RESULT_SUCCESS_V01;
  resp_ptr->Resp.sns_err_t    = SENSOR1_SUCCESS;

  resp_msg_header.msg_id   = SNS_SMGR_ALL_SENSOR_INFO_RESP_V01;
  resp_msg_header.body_len = sizeof(sns_smgr_all_sensor_info_resp_msg_v01);
  sns_rh_mr_send_resp(&resp_msg_header, (void**)&resp_ptr);

  return SNS_SUCCESS;
}

/*===========================================================================

  FUNCTION:   sns_rh_fill_odr_list

===========================================================================*/
SMGR_STATIC void sns_rh_fill_odr_list(
  const sns_smgr_ddf_sensor_s*              ddf_sensor_ptr,
  sns_smgr_single_sensor_info_resp_msg_v01* resp_ptr)
{
  uint8_t j;
  const sns_smgr_ddf_sensor_info_s* dsi_ptr = ddf_sensor_ptr->ddf_sensor_info;
  sns_smgr_odr_list_s_v01* odr_list =
    &resp_ptr->supported_odr_list[resp_ptr->supported_odr_list_len++];
  /* -------------------------------------------------------------------- */

  for ( j=0; j<ARR_SIZE(dsi_ptr->odr_list) && j<dsi_ptr->num_supported_odrs &&
             j<ARR_SIZE(odr_list->odrs); j++ )
  {
    odr_list->odrs[j] = dsi_ptr->odr_list[j];
    SNS_SMGR_PRINTF2(LOW, "fill_odr_list - odr[%u]=%u", j, odr_list->odrs[j]);
  }
  odr_list->odrs_len = j;
  resp_ptr->supported_odr_list_valid = true;
}

/*===========================================================================

  FUNCTION:   sns_rh_process_single_sensor_info_request

===========================================================================*/
/*!
  @brief Processes SNS_SMGR_SINGLE_SENSOR_INFO_REQ_V01.

  @detail Builds and sends response message with detail information on
          the requested sensor.

  @param[i]  msg_ptr - the request message

  @return  SNS_ERR_NOMEM or SNS_SUCCESS
 */
/*=========================================================================*/
SMGR_STATIC sns_err_code_e sns_rh_process_single_sensor_info_request(
  const sns_rh_mr_req_q_item_s* msg_ptr)
{
  sns_rh_mr_header_s resp_msg_header = msg_ptr->header;
  const sns_smgr_single_sensor_info_req_msg_v01* req_ptr =
    &msg_ptr->request.single_sensor_info;
  sns_smgr_sensor_s* sensor_ptr = sns_smgr_find_sensor(req_ptr->SensorID);
  sns_smgr_single_sensor_info_resp_msg_v01* resp_ptr =
    SMGR_ALLOC_STRUCT(sns_smgr_single_sensor_info_resp_msg_v01);
  /* -------------------------------------------------------------------- */

  if ( resp_ptr == NULL )
  {
    return SNS_ERR_NOMEM;
  }

  SNS_SMGR_PRINTF1(MED, "single_sensor_info - sensor=%d", req_ptr->SensorID);

  sensor_ptr = sns_smgr_find_sensor(req_ptr->SensorID);
#ifndef FAST_PLAYBACK
  if ( (sensor_ptr != NULL) && (SMGR_DRV_FN_PTR(sensor_ptr) != NULL) &&
       (sensor_ptr->dd_handle != NULL ) &&
       (sensor_ptr->sensor_state != SENSOR_STATE_FAILED) )
#else
   if( sensor_ptr != NULL )
#endif
  {
    uint8_t i;
#ifndef FAST_PLAYBACK

    for ( i=0; i<ARR_SIZE(sensor_ptr->const_ptr->data_types); i++ )
    {

      sns_smgr_ddf_sensor_s* ddf_sensor_ptr =
        sns_smgr_find_ddf_sensor(req_ptr->SensorID, i);
      if ( ddf_sensor_ptr != NULL )
      {

        sns_smgr_sensor_datatype_info_s_v01* info_ptr =
          &resp_ptr->SensorInfo.data_type_info[resp_ptr->SensorInfo.data_type_info_len];
        sns_smgr_ddf_sensor_info_s* dsi_ptr = ddf_sensor_ptr->ddf_sensor_info;

        info_ptr->SensorID = req_ptr->SensorID;
        info_ptr->DataType = i;
        // PEND: Fix the transport layer congestion problems so we don't have
        //       to limit the advertised max rate.
        // Limit the advertised max sampling rate to avoid potential congestion
        // issues in the transport layer.
        if (dsi_ptr->max_sampling_rate > SNS_RH_MAX_ADVERTISED_SAMPLING_RATE_HZ)
        {
          info_ptr->MaxSampleRate = SNS_RH_MAX_ADVERTISED_SAMPLING_RATE_HZ;
        }
        else
        {
          info_ptr->MaxSampleRate = dsi_ptr->max_sampling_rate;
        }
        strlcpy(info_ptr->SensorName, dsi_ptr->name, sizeof(info_ptr->SensorName));
        info_ptr->SensorName_len = strlen(info_ptr->SensorName);
        strlcpy(info_ptr->VendorName, dsi_ptr->vendor, sizeof(info_ptr->VendorName));
        info_ptr->VendorName_len = strlen(info_ptr->VendorName);
        info_ptr->Version = dsi_ptr->version;
        info_ptr->IdlePower = dsi_ptr->idle_power;
        info_ptr->MaxPower  = dsi_ptr->active_power;
        info_ptr->MaxRange  = dsi_ptr->max_range;
        info_ptr->Resolution = dsi_ptr->resolution;

        resp_ptr->num_buffered_reports[resp_ptr->SensorInfo.data_type_info_len] =
          (SNS_BATCHBUFF_BLK_MAX_BIMG*SNS_RH_BATCHBUFF_MAX_SAMPLE);

        resp_ptr->num_reserved_buffered_reports[resp_ptr->SensorInfo.data_type_info_len] =
          ddf_sensor_ptr->reserved_sample_cnt_nonwakeup;

        if ( dsi_ptr->suid != 0 )
        {
          resp_ptr->suid_valid = true;
          resp_ptr->suid[resp_ptr->suid_len++] = dsi_ptr->suid;
        }
        if ( (sensor_ptr->num_lpf > 0) || sensor_ptr->odr_attr_supported )
        {
          sns_rh_fill_odr_list(ddf_sensor_ptr, resp_ptr);
        }
        SNS_SMGR_PRINTF4(
           LOW, "single_sensor_info - max_freq=%u num_buf=%u suid=0x%08x%08x",
           dsi_ptr->max_sampling_rate,
           resp_ptr->num_buffered_reports[resp_ptr->SensorInfo.data_type_info_len],
           dsi_ptr->suid >> 32, dsi_ptr->suid);
        resp_ptr->SensorInfo.data_type_info_len++;
      }
    }

    resp_ptr->num_buffered_reports_valid = true;
    resp_ptr->num_buffered_reports_len   = resp_ptr->SensorInfo.data_type_info_len;

    resp_ptr->num_reserved_buffered_reports_valid = true;
    resp_ptr->num_reserved_buffered_reports_len   = resp_ptr->SensorInfo.data_type_info_len;

    resp_ptr->op_mode_valid     = true;
    resp_ptr->op_mode =
      SMGR_SENSOR_IS_S4S(sensor_ptr) ? SNS_SMGR_OP_MODE_S4S_V01 :
      SMGR_SENSOR_FIFO_IS_ENABLE(sensor_ptr) ? SNS_SMGR_OP_MODE_FIFO_V01 :
      (SMGR_SENSOR_IS_SELF_SCHED(sensor_ptr) ? SNS_SMGR_OP_MODE_DRI_V01 :
       SNS_SMGR_OP_MODE_POLLING_V01);

    resp_ptr->Resp.sns_result_t = SNS_RESULT_SUCCESS_V01;
    resp_ptr->Resp.sns_err_t    = SENSOR1_SUCCESS;
  }
#else
    sns_smgr_sensor_datatype_info_s_v01* info_ptr =
      &resp_ptr->SensorInfo.data_type_info[0];

    resp_ptr->Resp.sns_result_t = SNS_SUCCESS;
    resp_ptr->Resp.sns_err_t = SNS_SUCCESS;
    resp_ptr->SensorInfo.data_type_info_len = 1;
    info_ptr->SensorID = SNS_SMGR_ID_ACCEL_V01;
    info_ptr->DataType = 0;
    info_ptr->SensorName_len = 0; // Ignore the SensorName
    info_ptr->VendorName_len = 0; // Ignore the VendorName
    info_ptr->Version = 1;
    info_ptr->MaxSampleRate = 200;
    info_ptr->IdlePower = 5;
    info_ptr->MaxPower = 5;
    info_ptr->MaxRange = 0xA0000;
    info_ptr->Resolution = 0x10000;
    resp_ptr->suid_valid = 1;
    resp_ptr->suid_len = 1;
    resp_ptr->suid[0] = SNS_SMGR_SUID_ACCEL_1_V01;
    resp_ptr->op_mode_valid = 0;
    resp_ptr->supported_odr_list_valid = 0;

    switch (req_ptr->SensorID)
    {
      case SNS_SMGR_ID_ACCEL_V01:
    	info_ptr->SensorID = SNS_SMGR_ID_ACCEL_V01;
    	resp_ptr->suid[0] = SNS_SMGR_SUID_ACCEL_1_V01;
        break;
      case SNS_SMGR_ID_GYRO_V01:
    	info_ptr->SensorID = SNS_SMGR_ID_GYRO_V01;
        resp_ptr->suid[0] = SNS_SMGR_SUID_GYRO_1_V01;
        break;
      case SNS_SMGR_ID_MAG_V01:
    	info_ptr->SensorID= SNS_SMGR_ID_MAG_V01;
    	resp_ptr->suid[0] = SNS_SMGR_SUID_MAG_1_V01;
        break;
      case SNS_SMGR_ID_PRESSURE_V01:
    	info_ptr->SensorID= SNS_SMGR_ID_PRESSURE_V01;
    	resp_ptr->suid[0] = SNS_SMGR_SUID_PRESSURE_1_V01;
        break;
      case SNS_SMGR_ID_HEART_RATE_V01:
    	info_ptr->SensorID= SNS_SMGR_ID_HEART_RATE_V01;
    	resp_ptr->suid[0] = SNS_SMGR_SUID_HEART_RATE_1_V01;
        break;
      case SNS_SMGR_ID_PROX_LIGHT_V01: // Proximity
    	info_ptr->SensorID = SNS_SMGR_ID_PROX_LIGHT_V01;
        resp_ptr->suid[0] = SNS_SMGR_SUID_PROX_1_V01;
        break;
      default:
        printf("ERROR: Unsupported SSI sensor ID %d\n", req_ptr->SensorID);
        break;
    }
  }
#endif
  else
  {
    resp_ptr->Resp.sns_result_t = SNS_RESULT_FAILURE_V01;
    resp_ptr->Resp.sns_err_t    = SENSOR1_EBAD_PARAM;
    SNS_SMGR_PRINTF0(ERROR, "single_sensor_info - bad param");
  }

  resp_msg_header.msg_id   = SNS_SMGR_SINGLE_SENSOR_INFO_RESP_V01;
  resp_msg_header.body_len = sizeof(sns_smgr_single_sensor_info_resp_msg_v01);
  sns_rh_mr_send_resp(&resp_msg_header, (void**)&resp_ptr);

  return SNS_SUCCESS;
}

/*===========================================================================

  FUNCTION:   sns_smgr_proc_cancel_service_req_msg

===========================================================================*/
/*!
  @brief Processes SNS_SMGR_CANCEL_REQ.

  @detail Deletes all reports started by clients on the given connection.

  @param[i]  msg_ptr - the request message

  @return  SNS_SUCCESS or SNS_ERR_NOMEM
 */
/*=========================================================================*/
SMGR_STATIC sns_err_code_e sns_rh_process_cancel_service_request(
  const sns_rh_mr_req_q_item_s* msg_ptr)
{
  sns_rh_mr_header_s resp_msg_header;
  sns_common_cancel_resp_msg_v01* resp_ptr =
    SMGR_ALLOC_STRUCT(sns_common_cancel_resp_msg_v01);
  /* -------------------------------------------------------------------- */

  if ( resp_ptr == NULL )
  {
    return SNS_ERR_NOMEM;
  }

  SNS_SMGR_PRINTF1(
    MED, "cancel_service_req - conn=0x%x",
    (unsigned)msg_ptr->header.connection_handle);

  sns_rh_cancel_service(msg_ptr->header.connection_handle);
  resp_ptr->resp.sns_result_t = SNS_RESULT_SUCCESS_V01;
  resp_ptr->resp.sns_err_t    = SENSOR1_SUCCESS;

  resp_msg_header          = msg_ptr->header;
  resp_msg_header.msg_id   = SNS_SMGR_CANCEL_RESP_V01;
  resp_msg_header.body_len = sizeof(sns_common_cancel_resp_msg_v01);
  sns_rh_mr_send_resp(&resp_msg_header, (void**)&resp_ptr);

  return SNS_SUCCESS;
}

/*===========================================================================

  FUNCTION:   sns_rh_process_version_request

===========================================================================*/
/*!
  @brief Handles SNS_SMGR_VERSION_REQ.

  @detail Builds and sends response message with version of the
          SMGR interface in use.

  @param[i]  msg_ptr - the request message

  @return  SNS_SUCCESS or SNS_ERR_NOMEM
 */
/*=========================================================================*/
SMGR_STATIC sns_err_code_e sns_rh_process_version_request(
  const sns_rh_mr_req_q_item_s* msg_ptr)
{
  sns_err_code_e err_code = SNS_ERR_NOMEM;
  sns_common_version_resp_msg_v01* resp_ptr =
    SMGR_ALLOC_STRUCT(sns_common_version_resp_msg_v01);
  /* -------------------------------------------------------------------- */

  if ( resp_ptr != NULL )
  {
    sns_rh_mr_header_s resp_msg_header = msg_ptr->header;

    resp_ptr->max_message_id = SNS_SMGR_SVC_V01_MAX_MESSAGE_ID;
    resp_ptr->interface_version_number = SNS_SMGR_SVC_V01_IDL_MINOR_VERS;
    resp_msg_header.msg_id   = SNS_SMGR_VERSION_RESP_V01;
    resp_msg_header.body_len = sizeof(sns_common_version_resp_msg_v01);
    resp_ptr->resp.sns_result_t = SNS_RESULT_SUCCESS_V01;
    resp_ptr->resp.sns_err_t    = SENSOR1_SUCCESS;
    sns_rh_mr_send_resp(&resp_msg_header, (void**)&resp_ptr);
    err_code = SNS_SUCCESS;
  }
  return err_code;
}
/*===========================================================================

  FUNCTION:   sns_rh_validate_scale_factor

===========================================================================*/
SMGR_STATIC bool sns_rh_validate_scale_factor(
  const sns_smgr_sensor_cal_req_msg_v01* req_ptr)
{
  bool valid = false;
  /* -------------------------------------------------------------------- */

  if ( req_ptr->ScaleFactor_len <= SNS_SMGR_SENSOR_DIMENSION_V01 )
  {
    uint8_t i;
    valid = true;
    for ( i=0; i<req_ptr->ScaleFactor_len; i++ )
    {
      if ( req_ptr->ScaleFactor[i] == 0 )
      {
        SNS_SMGR_PRINTF1(HIGH, "calibration - scale factor[%d] is 0", i);
        valid = false;
        break;
      }
    }
  }
  return valid;
}


/*===========================================================================

  FUNCTION:   sns_rh_process_user_calibration_request

===========================================================================*/
/*!
  @brief Handles SNS_SMGR_CAL_REQ_V01.

  @detail Sets up calibration data to be applied to new samples.

  @param[i]  msg_ptr - the request message

  @return  SNS_ERR_NOMEM or SNS_SUCCESS
 */
/*=========================================================================*/
SMGR_STATIC sns_err_code_e sns_rh_process_user_calibration_request(
  sns_rh_mr_req_q_item_s** msg_ptr_ptr)
{
  sns_rh_mr_req_q_item_s* msg_ptr = *msg_ptr_ptr;
  sns_smgr_sensor_cal_req_msg_v01* req_ptr = &msg_ptr->request.calibration;
  sns_smgr_sensor_cal_resp_msg_v01* resp_ptr =
    SMGR_ALLOC_STRUCT(sns_smgr_sensor_cal_resp_msg_v01);
  sns_smgr_ddf_sensor_s* ddf_sensor_ptr =
    sns_smgr_find_ddf_sensor(req_ptr->SensorId, req_ptr->DataType);
  sns_rh_mr_header_s resp_msg_header = msg_ptr->header;

  if ( resp_ptr == NULL )
  {
    return SNS_ERR_NOMEM;
  }

  SNS_SMGR_PRINTF3(
    MED, "proc_cal - sensor=%d dtype=%d usage=%d",
    req_ptr->SensorId, req_ptr->DataType, req_ptr->usage);

  if ( (ddf_sensor_ptr == NULL) || (ddf_sensor_ptr->all_cal_ptr == NULL) ||
       (req_ptr->ZeroBias_len > SNS_SMGR_SENSOR_DIMENSION_V01) ||
       !sns_rh_validate_scale_factor(req_ptr) )
  {
    resp_ptr->Resp.sns_result_t = SNS_RESULT_FAILURE_V01;
    resp_ptr->Resp.sns_err_t    = SENSOR1_EBAD_PARAM;
    SNS_SMGR_PRINTF3(
      ERROR, "proc_cal - 0x%x / 0x%x / %u ", ddf_sensor_ptr,
      ddf_sensor_ptr ? ddf_sensor_ptr->all_cal_ptr : 0, req_ptr->ZeroBias_len );
  }
  else if( sns_rh_cal_process_user_calibration_req(req_ptr,ddf_sensor_ptr)
           == SNS_DDF_SUCCESS)
  {
    /* needed when processing response from SMGR later */
    resp_ptr->Resp.sns_result_t        = SNS_RESULT_SUCCESS_V01;
    resp_ptr->Resp.sns_err_t           = SENSOR1_SUCCESS;
  }
  else
  {
    //This should never happen
    resp_ptr->Resp.sns_result_t = SNS_RESULT_FAILURE_V01;
    resp_ptr->Resp.sns_err_t    = SENSOR1_EBAD_PARAM;
  }

  resp_msg_header.msg_id = SNS_SMGR_CAL_RESP_V01;
  resp_msg_header.body_len = sizeof(sns_smgr_sensor_cal_resp_msg_v01);
  sns_rh_mr_send_resp(&resp_msg_header, (void**)&resp_ptr);

  return SNS_SUCCESS;
}


/*===========================================================================

  FUNCTION:   sns_rh_generate_self_test_indication

===========================================================================*/
SMGR_STATIC void sns_rh_generate_self_test_indication(
  sns_rh_mr_req_q_item_s*       msg_ptr,
  sns_smgr_self_test_result_s*  result_ptr)
{
  sns_smgr_single_sensor_test_req_msg_v01* req_ptr =
    &msg_ptr->request.single_sensor_test;
  sns_smgr_single_sensor_test_ind_msg_v01* ind_ptr =
    &sns_rh.infrequent_ind.self_test;
  /* -------------------------------------------------------------------- */

  SNS_OS_MEMSET((void*)&sns_rh.infrequent_ind.self_test, 0, 
                                 sizeof(sns_rh.infrequent_ind.self_test)); 

  ind_ptr->SensorID = req_ptr->SensorID;
  ind_ptr->DataType = req_ptr->DataType;
  ind_ptr->TestType = req_ptr->TestType;
  if ( result_ptr == NULL )
  {
    ind_ptr->TestResult = SNS_SMGR_TEST_RESULT_FAIL_V01;
  }
  else
  {
    ind_ptr->TestResult = result_ptr->result;
    if ( result_ptr->test_specific_error != 0 )
    {
      ind_ptr->ErrorCode_valid = true;
      ind_ptr->ErrorCode = (uint8_t)result_ptr->test_specific_error;
    }
	
	if ( result_ptr->additional_info_valid == true )
  	{
	    ind_ptr->AdditionalInfo_valid = true;
	    ind_ptr->AdditionalInfo_len   = ADDITIONAL_INFOLENGTH_V01;
	    SNS_OS_MEMSCPY(&ind_ptr->AdditionalInfo, sizeof(ind_ptr->AdditionalInfo), 
	      result_ptr->additional_info, sizeof(result_ptr->additional_info));
	    SNS_SMGR_PRINTF5( HIGH, " AdditionalInfo_len=%d AdditionalInfo_valid=%d AdditionalInfo - %d/ %d / %d ",
	      ind_ptr->AdditionalInfo_len, ind_ptr->AdditionalInfo_valid,
	      ind_ptr->AdditionalInfo[0], ind_ptr->AdditionalInfo[1],
	      ind_ptr->AdditionalInfo[ADDITIONAL_INFOLENGTH_V01-1] );
  	}
  }

  SNS_SMGR_PRINTF5(
    HIGH, "self_test_ind - sensor=%u test=%u result=%u, errorCode=%u EValid=%u",
    ind_ptr->SensorID, ind_ptr->TestType, ind_ptr->TestResult, 
    ind_ptr->ErrorCode, ind_ptr->ErrorCode_valid);

  sns_rh_mr_send_indication(msg_ptr->header.connection_handle,
                            ind_ptr,
                            SNS_SMGR_SINGLE_SENSOR_TEST_IND_V01,
                            sizeof(*ind_ptr),
                            false); /* do not free ind msg */
}

/*===========================================================================

  FUNCTION:   sns_rh_process_self_test_request

===========================================================================*/
/*!
  @brief Handles SNS_SMGR_SINGLE_SENSOR_TEST_REQ_V01.

  @detail Validates and forwards self-test request to SMGR.  Test result
          will be made available by SMGR at a later time.

  @param[i/o] msg_ptr_ptr - reference to the request message

  @return  SNS_ERR_NOMEM or SNS_SUCCESS
 */
/*=========================================================================*/
SMGR_STATIC sns_err_code_e sns_rh_process_self_test_request (
  sns_rh_mr_req_q_item_s** msg_ptr_ptr)
{
  sns_rh_mr_req_q_item_s* msg_ptr = *msg_ptr_ptr;
  sns_rh_mr_header_s resp_msg_header = msg_ptr->header;
  sns_smgr_single_sensor_test_req_msg_v01* req_ptr =
    &msg_ptr->request.single_sensor_test;
  sns_smgr_single_sensor_test_resp_msg_v01* resp_ptr =
    SMGR_ALLOC_STRUCT(sns_smgr_single_sensor_test_resp_msg_v01);
  sns_smgr_ddf_sensor_s* ddf_sensor_ptr =
    sns_smgr_find_ddf_sensor(req_ptr->SensorID, req_ptr->DataType);
  sns_smgr_request_response_s* smgr_req_ptr = NULL;
  /* -------------------------------------------------------------------- */

  if ( resp_ptr == NULL )
  {
    return SNS_ERR_NOMEM;
  }

  SNS_SMGR_PRINTF4(MED, "single_sensor_test - sensor=%d dtype=%d test=%d state=%d",
                   req_ptr->SensorID, req_ptr->DataType, req_ptr->TestType,
                   ddf_sensor_ptr?ddf_sensor_ptr->sensor_ptr->sensor_state:-1);

  resp_ptr->SensorID = req_ptr->SensorID;
  resp_ptr->DataType = req_ptr->DataType;
  resp_ptr->TestType = req_ptr->TestType;

  if ( ddf_sensor_ptr == NULL )
  {
    resp_ptr->TestStatus        = SNS_SMGR_TEST_STATUS_INVALID_PARAM_V01;
    resp_ptr->Resp.sns_result_t = SNS_RESULT_FAILURE_V01;
    resp_ptr->Resp.sns_err_t    = SENSOR1_EBAD_PARAM;
  }
  else if ( (SMGR_DRV_FN_PTR(ddf_sensor_ptr->sensor_ptr) == NULL) ||
            (SMGR_DRV_FN_PTR(ddf_sensor_ptr->sensor_ptr)->run_test == NULL) )
  {
    resp_ptr->TestStatus        = SNS_SMGR_TEST_STATUS_FAIL_V01; // ???
    resp_ptr->Resp.sns_result_t = SNS_RESULT_FAILURE_V01;
    resp_ptr->Resp.sns_err_t    = SENSOR1_ENOTALLOWED;
  }
  else if ( sns_rh.self_test.req_ptr != NULL )
  {
    resp_ptr->TestStatus        = SNS_SMGR_TEST_STATUS_BUSY_TESTING_V01;
    resp_ptr->Resp.sns_result_t = SNS_RESULT_SUCCESS_V01;
    resp_ptr->Resp.sns_err_t    = SENSOR1_SUCCESS;
  }
  else if ( (smgr_req_ptr = SMGR_ALLOC_STRUCT(sns_smgr_request_response_s)) == NULL )
  {
    resp_ptr->TestStatus        = SNS_SMGR_TEST_STATUS_FAIL_V01;
    resp_ptr->Resp.sns_result_t = SNS_RESULT_FAILURE_V01;
    resp_ptr->Resp.sns_err_t    = SENSOR1_ENOMEM;
  }
  else
  {
    sns_rh_sol_suspend_sensor_clients(ddf_sensor_ptr);

    resp_ptr->TestStatus = SNS_SMGR_TEST_STATUS_PENDING_V01;
    resp_ptr->Resp.sns_result_t = SNS_RESULT_SUCCESS_V01;
    resp_ptr->Resp.sns_err_t = SENSOR1_SUCCESS;

    sns_rh.self_test.ddf_sensor_ptr = ddf_sensor_ptr;
    sns_rh.self_test.req_ptr        = msg_ptr;
    *msg_ptr_ptr = NULL;

    smgr_req_ptr->ddf_sensor_ptr    = ddf_sensor_ptr;
    smgr_req_ptr->msg_id            = msg_ptr->header.msg_id;
    smgr_req_ptr->svc_num           = msg_ptr->header.svc_num;
    smgr_req_ptr->req.self_test_ptr = &msg_ptr->request.single_sensor_test;
    sns_smgr_put_next_request(ddf_sensor_ptr->sensor_ptr, smgr_req_ptr);
  }

  resp_msg_header.msg_id = SNS_SMGR_SINGLE_SENSOR_TEST_RESP_V01;
  resp_msg_header.body_len = sizeof(sns_smgr_single_sensor_test_resp_msg_v01);
  sns_rh_mr_send_resp(&resp_msg_header, (void**)&resp_ptr);

  if ( *msg_ptr_ptr != NULL )
  {
    sns_rh_generate_self_test_indication(msg_ptr, NULL);
  }

  return SNS_SUCCESS;
}

/*===========================================================================

  FUNCTION:   sns_rh_process_external_smgr_request

===========================================================================*/
/*!
  @brief Processes incoming messages for public SMGR service

  @param[i/o] msg_ptr_ptr - reference to the request message
  @param[i] time_now - timestamp when request is delivered to SMGR

  @return  SNS_SUCCESS or SNS_ERR_NOMEM
 */
/*=========================================================================*/
SMGR_STATIC sns_err_code_e sns_rh_process_external_smgr_request(
  sns_rh_mr_req_q_item_s** msg_ptr_ptr)
{
  sns_err_code_e  err_code = SNS_ERR_NOTSUPPORTED;
  switch ( (*msg_ptr_ptr)->header.msg_id )
  {
  case SNS_SMGR_REPORT_REQ_V01:
    err_code = sns_rh_sol_process_periodic_request(*msg_ptr_ptr);
    break;
  case SNS_SMGR_BUFFERING_REQ_V01:
    err_code = sns_rh_sol_process_buffering_request(*msg_ptr_ptr);
    break;
  case SNS_SMGR_BUFFERING_QUERY_REQ_V01:
    err_code = sns_rh_sol_process_buffering_query_request(*msg_ptr_ptr);
    break;
  case SNS_SMGR_SENSOR_STATUS_REQ_V01:
    err_code = sns_rh_process_sensor_status_request(*msg_ptr_ptr);
    break;
  case SNS_SMGR_ALL_SENSOR_INFO_REQ_V01:
    err_code = sns_rh_process_all_sensor_info_request(*msg_ptr_ptr);
    break;
  case SNS_SMGR_SINGLE_SENSOR_INFO_REQ_V01:
    err_code = sns_rh_process_single_sensor_info_request(*msg_ptr_ptr);
    break;
  case SNS_SMGR_CANCEL_REQ_V01:
    err_code = sns_rh_process_cancel_service_request(*msg_ptr_ptr);
    break;
  case SNS_SMGR_VERSION_REQ_V01:
    err_code = sns_rh_process_version_request(*msg_ptr_ptr);
    break;
  case SNS_SMGR_CAL_REQ_V01:
    err_code = sns_rh_process_user_calibration_request(msg_ptr_ptr);
    break;
  case SNS_SMGR_SINGLE_SENSOR_TEST_REQ_V01:
    err_code = sns_rh_process_self_test_request(msg_ptr_ptr);
    break;
  case SNS_SMGR_CAL_RESET_REQ_V01:
    err_code = sns_rh_cal_process_reset_request(msg_ptr_ptr);
    break;
  case SNS_SMGR_PHONE_MODE_SWITCH_REQ_V01:
    err_code = sns_rh_cal_process_mode_switch_request(msg_ptr_ptr);
    break;
  default:
    break;
  }
  return err_code;
}

/*===========================================================================

  FUNCTION:   sns_rh_process_smgr_response

===========================================================================*/
/*!
  @brief This function processes outgoing responses from SMGR

  @param[i]  resp_ptr  - the response from SMGR

  @return  none
 */
/*=========================================================================*/
SMGR_STATIC void sns_rh_process_smgr_response(void)
{
  sns_smgr_request_response_s* resp_ptr;

  while ( (resp_ptr = sns_rh_get_next_response()) != NULL )
  {
    sns_rh_mr_header_s* hdr_ptr = (sns_rh_mr_header_s*)resp_ptr->req_handle;
    switch ( hdr_ptr->svc_num )
    {
    case SNS_SMGR_SVC_ID_V01:
      if ( hdr_ptr->msg_id == SNS_SMGR_CAL_RESP_V01 )
      {
        sns_rh_mr_send_resp(hdr_ptr, (void**)&resp_ptr->resp.calibration_ptr);
      }
      else
      if ( hdr_ptr->msg_id == SNS_SMGR_CAL_RESET_RESP_V01 )
      {
        sns_rh_mr_send_resp(hdr_ptr, (void**)&resp_ptr->resp.cal_reset_ptr);
      }
      SNS_OS_FREE(hdr_ptr);
      SNS_OS_FREE(resp_ptr);
      break;
    case SNS_SMGR_RESTRICTED_SVC_ID_V01:
      sns_rh_process_restricted_smgr_response(resp_ptr);
      break;
    default:
      SNS_SMGR_PRINTF2(
        HIGH, "process_smgr_response - unexpected svc(%u) msg(0x%x)",
        ((sns_rh_mr_header_s*)resp_ptr->conn_handle)->svc_num,
        ((sns_rh_mr_header_s*)resp_ptr->conn_handle)->msg_id);
      break;
    }
  }
}

/*===========================================================================

  FUNCTION:   sns_rh_process_smgr_indication

===========================================================================*/
/*!
  @brief This function processes outgoing indications from SMGR

  @param[i]  resp_ptr  - the indication generated by SMGR

  @return  none
 */
/*=========================================================================*/
SMGR_STATIC void sns_rh_process_smgr_indication(void)
{
  sns_smgr_indication_s* ind_ptr;
  while ( (ind_ptr = sns_rh_get_next_indication()) != NULL )
  {
    sns_rh_mr_send_indication(ind_ptr->conn_handle, &ind_ptr->ind,
                              ind_ptr->msg_id, ind_ptr->ind_len, false);
    SNS_OS_FREE(ind_ptr);
  }
}

/*===========================================================================

  FUNCTION:   sns_rh_process_msg

===========================================================================*/
/*!
  @brief This function processes incoming messages for SMGR

  @detail

  @param[i]  item_ptr  - message item
  @return  none
 */
/*=========================================================================*/
SMGR_STATIC void sns_rh_process_msg(void)
{
  sns_rh_mr_req_q_item_s* item_ptr;
  while ( (item_ptr = sns_rh_mr_get_msg()) != NULL )
  {
    sns_err_code_e  err_code = SNS_ERR_FAILED;
    sns_ddf_time_t  time_now = sns_ddf_get_timestamp();
    #ifdef CONFIG_DRI_UNIT_TEST
    static int      run_test = 10;
    #endif

    if ( !sns_rh_mr_validate_connection(item_ptr->header.connection_handle) )
    {
      SNS_SMGR_PRINTF3(
        ERROR, "process_msg - dropping msg conn=%u type=%u/0x%02x", 
        item_ptr->header.connection_handle, item_ptr->header.svc_num,
        item_ptr->header.msg_id);
      SNS_OS_FREE(item_ptr);
      continue;
    }

    SNS_SMGR_PRINTF2(
      MED, "process_msg - now=%u/0x%x", time_now, time_now);
    SNS_SMGR_PRINTF3(
      MED, "process_msg - conn=0x%x svc=%u msg=0x%x",
      item_ptr->header.connection_handle, item_ptr->header.svc_num,
      item_ptr->header.msg_id);

    switch ( item_ptr->header.svc_num )
    {
    case SNS_SMGR_SVC_ID_V01:
      err_code = sns_rh_process_external_smgr_request(&item_ptr);
      break;
    case SNS_SMGR_INTERNAL_SVC_ID_V01:
      err_code = sns_rh_process_internal_smgr_request(&item_ptr);
      break;
    case SNS_SMGR_RESTRICTED_SVC_ID_V01:
      err_code = sns_rh_process_restricted_smgr_request(&item_ptr);
      break;
    default:
      break;
    }
    if ( err_code != SNS_SUCCESS )
    {
      sns_rh_mr_send_resp_w_err(item_ptr);
    }
    else if ( item_ptr != NULL )
    {
      SNS_OS_FREE(item_ptr);
    }
    /* else, request was saved and will be released when no longer needed */
  }
}

/*===========================================================================

  FUNCTION:   sns_rh_process_self_test_result

===========================================================================*/
/*!
  @brief Processes SNS_RH_SELF_TEST_DONE_SIG
  @param   none
  @return  none
 */
/*=========================================================================*/
SMGR_STATIC void sns_rh_process_self_test_result(void)
{
  sns_smgr_self_test_result_s test_result;
  if ( sns_rh.self_test.req_ptr == NULL )
  {
    SNS_SMGR_PRINTF0(ERROR, "self_test_result - unexpected!");
    return;
  }

  sns_smgr_get_self_test_result(&test_result);
  sns_rh_generate_self_test_indication(sns_rh.self_test.req_ptr, &test_result);

  sns_rh_sol_resume_sensor_clients(sns_rh.self_test.ddf_sensor_ptr);

  SNS_OS_FREE(sns_rh.self_test.req_ptr);
  sns_rh.self_test.req_ptr = NULL;
  sns_rh.self_test.ddf_sensor_ptr = NULL;
}

/*===========================================================================

  FUNCTION:   sns_rh_handle_modem_wake_sig

===========================================================================*/
/*!
  @brief Handles MODEM_WAKE signal

  @detail
  @param  none
  @return none
 */
/*=========================================================================*/
SNS_RH_UIMAGE_CODE SMGR_STATIC void sns_rh_handle_modem_wake_sig(void)
{
  sns_rh_rpt_spec_s* rpt_ptr;
  sns_q_s*           rpt_queue_ptr = sns_rh_get_report_queue();
  /* -------------------------------------------------------------------- */

  SMGR_FOR_EACH_Q_ITEM( rpt_queue_ptr, rpt_ptr, rpt_link )
  {
    if ( rpt_ptr->proc_type == SNS_PROC_SSC_V01 )
    {
      sns_rh_prepare_report_for_flushing(rpt_ptr);
    }
  }
  sns_smgr_signal_me(SNS_SMGR_SENSOR_STATE_SIG);
}

/*===========================================================================
  FUNCTION:   sns_rh_init_bimg
===========================================================================*/
SMGR_STATIC void sns_rh_init_bimg(void)
{
  uint8_t  err;

  SNS_OS_MEMZERO(&sns_rh, sizeof(sns_rh_s));

  sns_q_init(&sns_rh.resp_queue.protected_q);
  sns_rh.resp_queue.mutex_ptr = sns_os_mutex_create(SNS_SMGR_QUE_MUTEX, &err);
  SNS_ASSERT (err == OS_ERR_NONE );

  sns_q_init(&sns_rh.ind_queue.protected_q);
  sns_rh.ind_queue.mutex_ptr = sns_os_mutex_create(SNS_SMGR_QUE_MUTEX, &err);
  SNS_ASSERT (err == OS_ERR_NONE );

}

/*===========================================================================

  FUNCTION:   sns_rh_task

===========================================================================*/
/*!
  @brief Request Hanlder task

  @param[i]  p_arg - unused
 
  @return   none
 */
/*=========================================================================*/
void sns_rh_task(void* p_arg)
{
  sns_rh_init_bimg();
  sns_rh_init_uimg();
  sns_rh_batchbuff_init();
#if defined(VIRTIO_BRINGUP) || defined(FAST_PLAYBACK)
  sns_rh_mr_init();
  sns_rh_cal_check_clients();
  sns_rh_internal_svc_init();
  sns_init_done();
#else
  sns_init_done();
  sns_rh_wait_for_smgr();
  sns_rh_mr_init();
  sns_rh_cal_check_clients();
  sns_rh_internal_svc_init();
#endif
  sns_rh_task_loop(); /* in uImage */
}

/*===========================================================================

  FUNCTION:   sns_rh_cancel_service

===========================================================================*/
/*!
  @details Cancels all requests to SMGR service by the client associated
           with given connection

  @param[i]  connection_handle - QCCI handle

  @return  none
 */
/*=========================================================================*/
void sns_rh_cancel_service(void* connection_handle)
{
  sns_rh_rpt_spec_s* delete_rpt_ptr[SNS_SMGR_MAX_REPORT_CNT];
  uint8_t i = 0, num_reports = 0;
  sns_rh_rpt_spec_s* rpt_ptr;
  sns_q_s*           rpt_queue_ptr = sns_rh_get_report_queue();
  /* ---------------------------------------------------------------------- */

  SMGR_FOR_EACH_Q_ITEM( rpt_queue_ptr, rpt_ptr, rpt_link )
  {
    if ( connection_handle == rpt_ptr->msg_header.connection_handle )
    {
      SNS_SMGR_PRINTF4(
        LOW, "cancel_service - found rpt_id=%u/0x%x type=%u/0x%x", 
        rpt_ptr->rpt_id, rpt_ptr->msg_header.connection_handle,
        rpt_ptr->msg_header.svc_num, rpt_ptr->msg_header.msg_id);
      delete_rpt_ptr[num_reports++] = rpt_ptr;
    }
  }/* for each report in queue */

  if (num_reports > 0)
  {
    while ( i < num_reports )
    {
      sns_rh_sol_delete_report(delete_rpt_ptr[i++]);
    }
    sns_rh_flush_reports();
    sns_smgr_signal_me(SNS_SMGR_SENSOR_STATE_SIG);
  }
  else
  {
    SNS_SMGR_PRINTF1(
      LOW, "cancel_service - no reports associated with conn_hndl 0x%x",
      connection_handle);
  }
}

/*===========================================================================

  FUNCTION:   sns_rh_prepare_report_for_flushing

===========================================================================*/
/*!
  @brief Flushes accumulated samples

  @param[i] rpt_ptr - the report to flush

  @return   none
*/
/*=========================================================================*/
SNS_RH_UIMAGE_CODE void sns_rh_prepare_report_for_flushing(sns_rh_rpt_spec_s* rpt_ptr)
{
  if ( SNS_RH_REPORT_IS_BATCHING(rpt_ptr) && rpt_ptr->q16_rpt_rate != 0 &&
       rpt_ptr->state == RH_RPT_STATE_ACTIVE )
  {
    uint8_t i;
    bool fifo_flush_pending = false;

    RH_FOR_EACH_REPORT_ITEM( rpt_ptr, i )
    {
      sns_smgr_ddf_sensor_s* ddf_sensor_ptr = rpt_ptr->item_list[i]->ddf_sensor_ptr;
      if ( SMGR_SENSOR_FIFO_IS_ENABLE(ddf_sensor_ptr->sensor_ptr) &&
           ddf_sensor_ptr->latest_sample_ts != 0 )
      {
        sns_os_mutex_pend(ddf_sensor_ptr->sensor_ptr->mutex_ptr, 0, NULL);
        if ( SMGR_BIT_CLEAR_TEST(ddf_sensor_ptr->sensor_ptr->flags, 
                                 SMGR_SENSOR_FLAGS_FLUSH_FIFO_B) )
        {
          SMGR_BIT_SET(ddf_sensor_ptr->flags, SMGR_SENSOR_FLAGS_FLUSH_FIFO_B);
          SMGR_BIT_SET(ddf_sensor_ptr->sensor_ptr->flags, SMGR_SENSOR_FLAGS_FLUSH_FIFO_B);
        }
        rpt_ptr->state = RH_RPT_STATE_FIFO_FLUSH_PENDING;
        fifo_flush_pending = true;
        sns_os_mutex_post(ddf_sensor_ptr->sensor_ptr->mutex_ptr);
      }
    }
    if ( !fifo_flush_pending )
    {
      rpt_ptr->state = RH_RPT_STATE_FLUSHING;
    }
    SNS_SMGR_PRINTF4(
      MED, "prepare_4_flushing - rpt_id=%u/0x%x state=%u/%u",
      rpt_ptr->rpt_id, rpt_ptr->msg_header.connection_handle, 
      rpt_ptr->state, rpt_ptr->state_extended);
  }
}

/*===========================================================================

  FUNCTION:   sns_rh_process_sensor_config_done_sig

===========================================================================*/
/*!
  @details Processes SNS_RH_SENSOR_CONFIG_DONE_SIG
  @param   none
  @return  none
 */
/*=========================================================================*/
SMGR_STATIC void sns_rh_process_sensor_config_done_sig(void)
{
  uint8_t s, d;

  for ( s=0; s<ARR_SIZE(sns_smgr.sensor); s++ )
  {
    sns_smgr_sensor_s* sensor_ptr = &sns_smgr.sensor[s];
    if ( sensor_ptr->mutex_ptr != NULL )
    {
      sns_os_mutex_pend(sensor_ptr->mutex_ptr, 0, NULL);
      if ( sensor_ptr->sensor_state == SENSOR_STATE_READY && 
           SMGR_BIT_CLEAR_TEST(sensor_ptr->flags, SMGR_SENSOR_FLAGS_ITEM_ADD_B) &&
           SMGR_BIT_CLEAR_TEST(sensor_ptr->flags, SMGR_SENSOR_FLAGS_ITEM_DEL_B) )
      {
        for ( d=0; d<ARR_SIZE(sensor_ptr->const_ptr->data_types); d++ )
        {
          if ( sensor_ptr->ddf_sensor_ptr[d] != NULL )
          {
            sns_rh_sol_update_assoc_reports(sensor_ptr->ddf_sensor_ptr[d]);
          }
        }
      }
      sns_os_mutex_post(sensor_ptr->mutex_ptr);
    }
  }
}

/*===========================================================================

  FUNCTION:   sns_rh_process_big_image_signals

===========================================================================*/
/*!
  @details Processes signals that are only supposed to be handled in big image mode.

  @param[i]  sig_flags - signals to be processed

  @return  none
 */
/*=========================================================================*/
void sns_rh_process_big_image_signals(OS_FLAGS sig_flags)
{
  if ( sig_flags & SNS_RH_MODEM_WAKE_SIG )
  {
    sns_rh_handle_modem_wake_sig();
  }
  if ( sig_flags & SNS_RH_APP_WAKE_SIG )
  {
    sns_rh_handle_app_wake_sig();
  }
  if ( sig_flags & SNS_RH_SMR_MSG_SIG )
  {
    sns_rh_process_msg();
  }
  if(sig_flags & SNS_RH_SAM_MSG_SIG )
  {
    sns_rh_cal_process_handle_sam_msg();
  }
  if ( sig_flags & SNS_RH_SMR_DISC_SIG )
  {
    sns_rh_mr_handle_disconnect_sig();
  }
  if ( sig_flags & SNS_RH_SENSOR_CONFIG_DONE_SIG )
  {
    sns_rh_process_sensor_config_done_sig();
  }
  if ( sig_flags & SNS_RH_SELF_TEST_DONE_SIG )
  {
    sns_rh_process_self_test_result();
  }
  if ( sig_flags & SNS_RH_MD_INT_ENABLED_SIG )
  {
    sns_rh_process_md_int_enabled_sig();
  }
  if ( sig_flags & SNS_RH_MD_INT_DISABLED_SIG )
  {
    sns_rh_process_md_int_disabled_sig();
  }
  if ( sig_flags & SNS_RH_MD_INT_SIG )
  {
    sns_rh_process_md_int_sig();
  }
  if ( sig_flags & SNS_RH_RESP_Q_SIG )
  {
    sns_rh_process_smgr_response();
  }
  if ( sig_flags & SNS_RH_IND_Q_SIG )
  {
    sns_rh_process_smgr_indication();
  }
  if ( sig_flags & SNS_RH_SMR_RESUME_SIG )
  {
    sns_rh_process_conn_resume();
  }
  if ( sig_flags & SNS_RH_APP_SLEEP_SIG )
  {
    sns_rh_handle_app_sleep_sig();
  }
}

