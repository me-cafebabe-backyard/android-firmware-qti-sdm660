#ifndef SNS_HDRLL_H_
#define SNS_HDRLL_H_

/*============================================================================
  @file sns_hdrll.h

  @brief
  API functions, data structures, and constants used by the High Data Rate,
  Low Latency (HDRLL) Library

  @note
  File line length should generally be limited to <= 80 columns.

  Copyright (c) 2016 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
  ===========================================================================*/

#include <stdint.h>

/*============================================================================
  Preprocessor Definitions and Constants
  ===========================================================================*/

#define SNS_HDRLL_NUM_AXES             3


/*============================================================================
  Type Declarations
  ===========================================================================*/

/**
 * Client handle type
 */
typedef void* sns_hdrll_client_handle;

/**
 * Context handle type
 */
typedef void* sns_hdrll_context_handle;

/**
 * Defines the sensors available for HDRLL mode.
 */
typedef enum sns_hdrll_sensor_type_e
{
  SNS_HDRLL_ACCEL = 0,
  SNS_HDRLL_GYRO,

  SNS_HDRLL_NUM_SENSOR_TYPES, // NOTE: This must always be the last entry in the
                              //       sensor_type enum!

  SNS_HDRLL_MAX_SENSOR_TYPE = 0xFFFFFFFF // Force sensor_type to a 32-bit int
} sns_hdrll_sensor_type_e;


/**
 * Defines the types of errors that may be encountered while in HDRLL mode.
 */
typedef enum sns_hdrll_error_e
{
  SNS_HDRLL_UNKNOWN_ERROR
} sns_hdrll_error_e;


/**
 * Contains an ODR and Filter Delay pair
 */
typedef struct sns_hdrll_sensor_rate_delay_pair
{
  unsigned int      odr;            // The Output Data Rate, natively
                                    // supported by the sensor (in Hz)
  unsigned int      filter_delay;   // The associated delay due to the
                                    // sensor's internal filter (in ns)
} sns_hdrll_sensor_rate_delay_pair;


/**
 * Table of ODR and Filter Delay pairs
 */
typedef struct sns_hdrll_sensor_rate_delay_table
{
  unsigned int                          max_entries;
  /**< Maximum number of entries that can be written to table. */
  unsigned int*                         num_entries;
  /**< Number of valid entries in the table. */
  sns_hdrll_sensor_rate_delay_pair*     table;
  /**< Table of ODR and Filter Delay pairings (in ascending order). */
} sns_hdrll_sensor_rate_delay_table;


/**
 * Contains a single sensor sample
 */
typedef struct sns_hdrll_sensor_sample
{
  sns_hdrll_sensor_type_e       sensor_type;
  /**< The sensor that this data is representing. */
  uint64_t                      timestamp;
  /**< The accurate timestamp of the sample. This is adjusted for the device's
     internal filter delay. (in QTimer ticks, 19.2 MHz clock) */
  float                         sample[SNS_HDRLL_NUM_AXES];
  /**< Three-element vector representing the sensor data. These samples must
     follow the Android Specification:
         Accel  - m/s/s
         Gyro   - rad/s
     */
} sns_hdrll_sensor_sample;


/**
 * Contains an individual request to enable a sensor
 */
typedef struct sns_hdrll_sensor_request
{
  sns_hdrll_sensor_type_e       sensor_type;
  /**< Sensor to be enabled. */
  unsigned int                  sensor_odr;
  /**< Desired output data rate (in Hz). */
  unsigned int                  odr_divider;
   /**< This value will cause sensor to report at a rate equivalent to the
      sensor_odr / odr_divider.
      Note: This requires the sensor to support a hardware FIFO
     */
} sns_hdrll_sensor_request;


/**
 * Table of sensor requests
 */
typedef struct sns_hdrll_sensor_request_table
{
  unsigned int                     num_entries;
  /**< The number of valid entries in the table. */
  sns_hdrll_sensor_request*        table;
  /**< Table of sensor requests (in ascending order). */
} sns_hdrll_sensor_request_table;


/*===========================================================================

  CALLBACK FUNCTION:   sns_hdrll_send_data_cb

  ===========================================================================*/
/**
   @brief This type defines a function pointer. A function of this type shall be
   implemented by the client to handle received data.

   A typical implementation will copy the received data into a location in
   shared memory where the client can access it.

   @see sns_hdrll_enable_hdrll_mode

   @param[in]  cb_context      The user-supplied context
   @param[in]  sensor_sample   Pointer to the sensor sample

   @return
     - 0: data was sent successfully
     - -1: otherwise
     - all other values are reserved
*/
typedef int (*sns_hdrll_send_data_cb)
(
  sns_hdrll_context_handle            cb_context,
  const sns_hdrll_sensor_sample*      sensor_sample
);


/*===========================================================================

  CALLBACK FUNCTION:   sns_hdrll_handle_error_cb

  ===========================================================================*/
/**
   @brief This type defines a function pointer. A function of this type shall be
   implemented by the client to handle unanticipated errors.

   @see sns_hdrll_enable_hdrll_mode

   @param[in]  cb_context        The user-supplied context
   @param[in]  error_code        The specific error encountered
*/
typedef void (*sns_hdrll_handle_error_cb)
(
  sns_hdrll_context_handle    cb_context,
  sns_hdrll_error_e           error_code
);


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
extern int
sns_hdrll_enable_hdrll_mode
(
  sns_hdrll_client_handle*                  client,
  sns_hdrll_send_data_cb                    send_data_cb,
  sns_hdrll_handle_error_cb                 handle_error_cb,
  const sns_hdrll_context_handle            cb_context,
  const sns_hdrll_sensor_request_table*     sensor_requests
);


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
extern int
sns_hdrll_disable_hdrll_mode
(
  const sns_hdrll_client_handle      client
);


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
extern int
sns_hdrll_notify_data_ready
( void );


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
extern int
sns_hdrll_get_sensor_rate_info
(
  sns_hdrll_sensor_type_e              sensor_type,
  sns_hdrll_sensor_rate_delay_table*   rate_table,
  unsigned int*                        fifo_depth
);


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
);

#endif /* SNS_HDRLL_H_ */
