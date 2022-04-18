/*=============================================================================
  @file sns_rh_main.c

  This file implements Request Handler task.


/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/

#include "sns_rh_internal_svc.h"
#include "sns_rh_main.h"
#include "sns_rh_main_uimg.h"
#include "sns_rh_restricted_svc.h"
#include "sns_rh_rpt_gen.h"
#include "sns_rh_sol.h"
#include "sns_rh_util.h"
#include "sns_smgr_main.h"
#include "sns_smgr_util.h"
#include "sns_smgr_api_v01.h"

#include "sns_rh_rpt_gen.h"

#include "playback_smgr.h"
#include "sns_debug_str.h"
#include "sns_em.h"
/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 *  Variables
 * -------------------------------------------------------------------------*/
sns_ddf_odr_t accel_input_rate = 0;
sns_ddf_odr_t gyro_input_rate = 0;
sns_ddf_odr_t mag_input_rate = 0;
sns_ddf_odr_t pressure_input_rate = 0;
sns_ddf_odr_t ppg_input_rate = 0;
sns_ddf_odr_t prox_input_rate = 0;

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/
#define TICK_MOD_MASK                      0xFFFFFFFF
#define __SNS_MODULE__ SNS_RH

/*----------------------------------------------------------------------------
 *  Variables
 * -------------------------------------------------------------------------*/

void create_dummy_sensor_data(void)
{
  sns_smgr_init_single_sensor(SNS_SMGR_ID_PROX_LIGHT_V01,prox_input_rate);
  sns_smgr_init_single_sensor(SNS_SMGR_ID_ACCEL_V01,accel_input_rate);
  sns_smgr_init_single_sensor(SNS_SMGR_ID_GYRO_V01,gyro_input_rate);
  sns_smgr_init_single_sensor(SNS_SMGR_ID_MAG_V01,mag_input_rate);
  sns_smgr_init_single_sensor(SNS_SMGR_ID_PRESSURE_V01,pressure_input_rate);
  sns_smgr_init_single_sensor(SNS_SMGR_ID_HEART_RATE_V01,ppg_input_rate);
}

