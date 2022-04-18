#ifndef SNS_HDRLL_DAF_H_
#define SNS_HDRLL_DAF_H_

/*============================================================================
  @file sns_hdrll_daf.h

  @brief
  Driver Access Framework (DAF) message structures for the High Data Rate, Low
  Latency (HDRLL) set of commands.
    - SNS_DAF_HDRLL_ENABLE_V01 = 70
    - SNS_DAF_HDRLL_DISABLE_V01 = 71
    - SNS_DAF_HDRLL_GET_SENSOR_RATE_INFO_V01 = 72

  Copyright (c) 2016 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
  ===========================================================================*/

/*============================================================================
  Includes
  ===========================================================================*/

#include "sns_hdrll.h"
#include "driver_access_framework.h"


/*============================================================================
  Preprocessor Definitions and Constants
  ===========================================================================*/

#define SNS_DAF_HDRLL_ENABLE_V01                 SNS_DAF_RESERVED_70
  /**< Enable High Data-Rate, Low Latency Mode. */

#define SNS_DAF_HDRLL_DISABLE_V01                SNS_DAF_RESERVED_71
  /**< Disable VR Mode. */

#define SNS_DAF_HDRLL_GET_SENSOR_RATE_INFO_V01   SNS_DAF_RESERVED_72
  /**< Retrieve the a table of the sensor's ODR and Filter Delay pairings. */

// TODO: REMOVE THIS TEMPORARY DEFINITION
#define SNS_HDRLL_MAX_TBL_SIZE                   12

/*============================================================================
  DAF Message Structure Declarations
  ===========================================================================*/

/**
 * HDRLL Enable Request v01
 *
 * Defines the request structure for the SNS_DAF_HDRLL_ENABLE_V01 message
 *
 * Note: This is an "all-or-nothing" type message. All fields MUST CONTAIN A
 *       VALUE! Furthermore, if there is a failure in one field, the ENTIRE
 *       message fails.
 */
typedef PACK(struct) sns_daf_hdrll_enable_req_v01
{
  sns_hdrll_send_data_cb               send_data_cb;
  sns_hdrll_handle_error_cb            handle_error_cb;
  void*                                hdrll_cb_context;
  unsigned int                         num_sensor_requests;
  sns_hdrll_sensor_request             sensor_requests[SNS_HDRLL_MAX_TBL_SIZE];
} sns_daf_hdrll_enable_req_v01;

/**
 * HDRLL Enable Response v01
 *
 * Defines the response structure for the SNS_DAF_HDRLL_ENABLE_V01 message
 */
typedef PACK(struct) sns_daf_hdrll_enable_resp_v01
{
  uint32_t                             error;
} sns_daf_hdrll_enable_resp_v01;

/**
 * HDRLL Disable Request v01
 *
 * Defines the request structure for the SNS_DAF_HDRLL_DISABLE_V01 message
 *
 * Note: This is an "all-or-nothing" type message. All fields MUST CONTAIN A
 *       VALUE! Furthermore, if there is a failure in one field, the ENTIRE
 *       message fails.
 */
typedef PACK(struct) sns_daf_hdrll_disable_req_v01
{
  // Empty Message
} sns_daf_hdrll_disable_req_v01;

/**
 * HDRLL Disable Response v01
 *
 * Defines the response structure for the SNS_DAF_HDRLL_DISABLE_V01 message
 */
typedef PACK(struct) sns_daf_hdrll_disable_resp_v01
{
  uint32_t                             error;
} sns_daf_hdrll_disable_resp_v01;

/**
 * HDRLL Get Sensor Rate Info Request v01
 *
 * Defines the request structure for the SNS_DAF_HDRLL_GET_SENSOR_RATE_INFO_V01
 * message
 */
typedef PACK(struct) sns_daf_hdrll_get_sensor_rate_info_req_v01
{
  sns_hdrll_sensor_type_e              sensor_type;
  /**< Sensor Type
   *   @see sns_hdrll
   */
} sns_daf_hdrll_get_sensor_rate_info_req_v01;

/**
 * HDRLL Get Sensor Rate Info Response v01
 *
 * Defines the response structure for the SNS_DAF_HDRLL_GET_SENSOR_RATE_INFO_V01
 * message
 */
typedef PACK(struct) sns_daf_hdrll_get_sensor_rate_info_resp_v01
{
  uint32_t                             fifo_depth;
  /**< Maximum number of samples the FIFO can buffer
   */

  uint32_t                             num_entries;
  /**< Number of valid entries
   */

  sns_hdrll_sensor_rate_delay_pair     table[SNS_HDRLL_MAX_TBL_SIZE];
  /**< Table of ODR and Filter Delay pairs in descending order
   */
} sns_daf_hdrll_get_sensor_rate_info_resp_v01;

#endif /* SNS_HDRLL_DAF_H_ */