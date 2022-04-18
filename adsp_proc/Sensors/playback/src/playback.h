/*
 * playback.h
 *
 *  Created on: Sep 12, 2014
 *      Author: tomcheng
 */

#ifndef FAST_PLAYBACK_PHASE1_H_
#define FAST_PLAYBACK_PHASE1_H_

#include <stdio.h>
//#include <cstdbool>

#include "sns_common.h"
#include "sns_reg_api_v02.h"
#include "com_dtypes.h"
#include "stdbool.h"
#include "fixed_point.h"
#include "sns_debug_api.h"
#include "sns_osa.h"

#include "sns_smgr.h"

#ifndef FAST_PLAYBACK
  #define FAST_PLAYBACK
#endif

#define restrict

// Current version 0.6 (SAM "2.1" framework (dated July 1st, 2015))
/* Version History
 * 0.5 Phase 2 + PPG & Pressure
 * 0.6 SAM "2.1" framework (dated July 1st, 2015)
 */
#define FAST_PLAYBACK_MAJOR_VERSION 0
#define FAST_PLAYBACK_MINOR_VERSION 6

#ifndef SNS_PLAYBACK_SENSOR_INPUT_CONFIG_V01
  #define SNS_PLAYBACK_SENSOR_INPUT_CONFIG_V01 0x3f39c7bfb4161880
#endif /* SNS_PLAYBACK_SENSOR_INPUT_CONFIG_V01 */

#define SNS_PLAYBACK_SENSOR_CALIBRATION_EVENT_V01 0xd2fb09de8d2715fd
#define SNS_PLAYBACK_SENSOR_RESET_EVENT_V01       0xd2fb09de8d2715fe
#define SNS_SMGR_ID_CAL_RESET_V01 255
#define SNS_SMGR_ID_CAL_MODE_SWITCH_V01 254

#define MAX_SENSOR_INPUT_SAMPLES 5

#define SNS_SAM_ALGO_DISABLE_REQ_V01 0x0003

/* Each signal should use a unique bit */
#define FPB_INIT_DONE                    0x01 //playback_sig_event
#define FPB_CLIENT_CONNECT_DONE          0x02 //playback_sig_event
#define FPB_SENSOR_DATA_RESUME           0x03 //playback_resume_sig_event
#define FPB_CAL_ENABLE_SIG               0x04 //playback_sig_event
#define FPB_CAL_CONNECT_SIG              0x05
#define FPB_REG_SIG                      0x06 //
#define FPB_CLIENT_DISABLE_DONE          0x07 //playback_disable_sig_event
#define FPB_REG_DEINIT_DONE                  0x08 //playback_sig_event
extern OS_FLAG_GRP *playback_sig_event;
extern OS_FLAG_GRP *playback_resume_sig_event;
extern OS_FLAG_GRP * playback_cal_sig_event;
extern OS_FLAG_GRP * playback_disable_sig_event;
extern OS_FLAG_GRP * playback_reg_sig_event;
extern OS_EVENT *fpb_rh_mutex;
//*********************** BEGIN PACK() Definition ***************************/
#if defined __GNUC__
  #define PACK(x)       x __attribute__((__packed__))
#elif defined __arm
  #define PACK(x)       __packed x
#elif defined _WIN32
  #define PACK(x)       x /* Microsoft uses #pragma pack() prologue/epilogue */
#else
  #error No PACK() macro defined for this compiler
#endif


//*********************** BEGIN Playback-Specific Definitions ******************/

/**
 * A collection of sensor data samples.
 */
typedef struct
{
    sns_ddf_sensor_e          sensor;      /**< Sensor providing this data. */
    uint64_t                  timestamp;   /**< Time the sample received. */
    // todo: make the number of axes (3) configurable (currently hardcoded to
    //       3 to prevent constantly malloc'ing for the samples array, this makes
    //       the simulation run faster)
    q16_t                     samples[3];  /**< Collection of sensor data. */
} sns_playback_sensor_data_s;

#endif /* FAST_PLAYBACK_PHASE1_H_ */
