#ifndef FAST_PLAYBACK_SMGR_H_
#define FAST_PLAYBACK_SMGR_H_

#include "playback.h"
#include "sns_common.h"
#include "sns_smgr_api_v01.h"
#include "sns_smgr_internal_api_v02.h"
#include "sns_smgr.h"
#include "sns_rh.h"
#include "sns_rh_sol.h"
#include "sns_smgr_main.h"
#include "sns_rh_mr.h"
#include "sns_rh_sample_proc_uimg.h"


#define SMGR_SENSOR_BUFFER_DEPTH 100

//#define FAST_PLAYBACK_SMGR_DEBUG

#if defined(FAST_PLAYBACK_SMGR_DEBUG)
  #define FPB_SMGR_PRINTF printf // Use this #define to ENABLE SMGR debug messages
#else /* defined(FAST_PLAYBACK_SMGR_DEBUG) */
  #define FPB_SMGR_PRINTF(...)   // Use this #define to DISABLE SMGR debug messages
#endif /* defined(FAST_PLAYBACK_SMGR_DEBUG) */

extern sns_smgr_sensor_s  accel_sensor_ptr;
extern sns_smgr_sensor_s  gyro_sensor_ptr;
extern sns_smgr_sensor_s  mag_sensor_ptr;
extern sns_smgr_sensor_s  pressure_sensor_ptr;
extern sns_smgr_sensor_s  ppg_sensor_ptr;
extern sns_smgr_sensor_s  prox_sensor_ptr;     // Proximity Sensors Pointer

extern sns_ddf_odr_t accel_input_rate;
extern sns_ddf_odr_t gyro_input_rate;
extern sns_ddf_odr_t mag_input_rate;
extern sns_ddf_odr_t pressure_input_rate;
extern sns_ddf_odr_t ppg_input_rate;
extern sns_ddf_odr_t prox_input_rate;          // Proximity Input Rate

/*=========================================================================
  fpb_smgr_register_all_services
  =========================================================================*/
/*!
  @brief Registers the external and internal SMGR APIs
*/
/*=======================================================================*/
sns_err_code_e fpb_smgr_register_all_services(void);

// Forward Declarations
void create_dummy_sensor_data(void);
void create_dummy_report(void);

#endif /* FAST_PLAYBACK_SMGR_H_ */
