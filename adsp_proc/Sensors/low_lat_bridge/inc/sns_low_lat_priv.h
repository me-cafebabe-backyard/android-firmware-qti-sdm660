#ifndef SNS_LOW_LAT_PRIV_H_
#define SNS_LOW_LAT_PRIV_H_

/*============================================================================
  @file sns_hdrll_priv.h

  @brief
  Private API functions, data structures, and constants used by the  Library

  @note
  File line length should generally be limited to <= 80 columns.

  Copyright (c) 2016 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
  ===========================================================================*/

//#include "sns_low_lat.h"
#include "sns_log_api_public.h"
#include "fixed_point.h"

/*============================================================================
  Preprocessor Definitions and Constants
  ===========================================================================*/

/*============================================================================
  Type Declarations
  ===========================================================================*/

/*============================================================================
  Log Packet Definitions
  ===========================================================================*/
#ifndef LOG_SNS_HDRLL_DATA_C
#define LOG_SNS_HDRLL_DATA_C           (log_pkt_t) 0x1964
#endif /* LOG_SNS_HDRLL_DATA_C */

// Version 2 is for the SNS Low Latency Bridge
#define SNS_LOG_HDRLL_DATA_VERSION     2
#define SNS_LOG_HDRLL_DATA_NUM_AXES    3
typedef PACK(struct) {
   log_hdr_type log_type;       /**< Type, as defined in log_codes.h         */
   uint32_t     version;        /**< Version of the log packet               */
   uint32_t     sensor_id_1;    /**< The sensor ID for the first set of data */
   uint64_t     timestamp_1;    /**< Timestamp for the first set of data (in SSC ticks) */
   q16_t        data_1[SNS_LOG_HDRLL_DATA_NUM_AXES]; /**< First set of data in Q16 */
   uint32_t     sensor_id_2;    /**< The sensor ID for the second set of data */
   uint64_t     timestamp_2;    /**< Timestamp for the second set of data (in SSC ticks) */
   q16_t        data_2[SNS_LOG_HDRLL_DATA_NUM_AXES]; /**< second set of data in Q16 */
   uint8_t      stream_id;      /**< Stream that this data belongs to */
   uint8_t      log_timestamp_type; /**< Source of the timestamp */
   uint64_t     log_timestamp;  /**< Timestamp that this log packet was generated */
} sns_log_hdrll_data_v2;

#endif /* SNS_LOW_LAT_PRIV_H_ */
