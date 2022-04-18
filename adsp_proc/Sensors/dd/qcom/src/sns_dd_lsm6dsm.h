/******************** (C) COPYRIGHT 2015 STMicroelectronics ********************
 *
 * File Name         : sns_dd_lsm6dsm.h
 * Authors           : Karimuddin Sayed
 * Version           : V 5.15.0
 * Date              : 2/20/2017
 * Description       : LSM6DSM driver header file
 *
 ********************************************************************************
 * Copyright (c) 2016, STMicroelectronics.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     1. Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *     2. Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     3. Neither the name of the STMicroelectronics nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *******************************************************************************/

#ifndef __LSM6DSM__
#define __LSM6DSM__

#include "math.h"
#include "fixed_point.h"
#include "sns_ddf_attrib.h"
#include "sns_ddf_common.h"
#include "sns_ddf_comm.h"
#include "sns_ddf_driver_if.h"
#include "sns_ddf_memhandler.h"
#include "sns_ddf_smgr_if.h"
#include "sns_ddf_util.h"
#include "sns_ddf_signal.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define DEVICE_NAME "LSM6DSM"
//compilation flags
//please define all here
#ifdef SENSORS_DD_DEV_FLAG
#define BUILD_DRAGON_BOARD         1
#else // SENSORS_DD_DEV_FLAG
#define BUILD_DRAGON_BOARD         0
#endif // SENSORS_DD_DEV_FLAG
#define DEBUG_LOGS_VERBOSE         0
#define STM_LSM6DSM_LOGDATA        1
#define DEBUG_DATA                 0
#define DUMP_REGISTER_DATA         0
#define UIMAGE_SUPPORT             1
#define ACC_LOWPOWER_MODE          0
#define LSM6DSM_ENABLE_ESP         0
#define LSM6DSM_ENABLE_HUB         0

#if BUILD_DRAGON_BOARD
#include "sns_log_api_public.h"
#include "sns_log_types_public.h"
#include "msg.h"
#define sns_dd_lsm6dsm_if sns_dd_vendor_if_2
#define SNS_LOG_CONVERTED_SENSOR_DATA    SNS_LOG_CONVERTED_SENSOR_DATA_PUBLIC
#define SNS_DDF_SENSOR_TILT_EVENT SNS_DDF_SENSOR_OEM_SENSOR_01
#define SNS_DDF_SENSOR_D6D_EVENT SNS_DDF_SENSOR_OEM_SENSOR_02
#define DBG_LOW_PRIO   MSG_LEGACY_LOW    /**< Low priority debug message. */
#define DBG_MED_PRIO   MSG_LEGACY_MED    /**< Medium priority debug message. */
#define DBG_HIGH_PRIO  MSG_LEGACY_HIGH   /**< High priority debug message. */
#define DBG_ERROR_PRIO MSG_LEGACY_ERROR  /**< Error priority debug message. */
#define DBG_FATAL_PRIO MSG_LEGACY_FATAL  /**< Fatal priority debug message. */
#define SMGR_SUPPORTED_MAX_ODR_IDX     (STM_LSM6DSM_ODR208) //specifiy only odr index
#define SMGR_SUPPORTED_MAX_S4S_ODR_IDX     (STM_LSM6DSM_ODR208) //specifiy only odr index

#else
#include "log_codes.h"
#include "sns_log_types.h"
#include "sns_log_api.h"
#define SNS_DDF_SENSOR_D6D_EVENT SNS_DDF_SENSOR_ORIENTATION_EVENT
#define SMGR_SUPPORTED_MAX_ODR_IDX     (STM_LSM6DSM_ODR6660) //specifiy only odr index
#define SMGR_SUPPORTED_MAX_S4S_ODR_IDX     (STM_LSM6DSM_ODR6660) //specifiy only odr index
#endif


#if !UIMAGE_SUPPORT
#define 	sns_dd_lsm6dsm_malloc(ptr, size, smgr)	          sns_ddf_malloc(ptr, size)
#define		sns_dd_lsm6dsm_mfree(ptr, smgr) 						      sns_ddf_mfree(ptr)
#define 	sns_dd_lsm6dsm_memhandler_malloc(ptr, size, smgr)	sns_ddf_memhandler_malloc(ptr, size)

#if (BUILD_DRAGON_BOARD) && (DEBUG_LOGS_VERBOSE)
#define LSM6DSM_MSG_0(level,msg)          MSG(MSG_SSID_QDSP6,DBG_##level##_PRIO, DEVICE_NAME" - "msg)
#define LSM6DSM_MSG_1(level,msg,p1)       MSG_1(MSG_SSID_QDSP6,DBG_##level##_PRIO, DEVICE_NAME" - "msg,p1)
#define LSM6DSM_MSG_2(level,msg,p1,p2)    MSG_2(MSG_SSID_QDSP6,DBG_##level##_PRIO, DEVICE_NAME" - "msg,p1,p2)
#define LSM6DSM_MSG_3(level,msg,p1,p2,p3) MSG_3(MSG_SSID_QDSP6,DBG_##level##_PRIO, DEVICE_NAME" - "msg,p1,p2,p3)
#define LSM6DSM_MSG_4(level,msg,p1,p2,p3,p4) MSG_4(MSG_SSID_QDSP6,DBG_##level##_PRIO, DEVICE_NAME" - "msg,p1,p2,p3,p4)

#elif (!BUILD_DRAGON_BOARD) && (DEBUG_LOGS_VERBOSE)

#define LSM6DSM_MSG_0(level,msg)          MSG(MSG_SSID_SNS,DBG_##level##_PRIO, DEVICE_NAME" - "msg)
#define LSM6DSM_MSG_1(level,msg,p1)       MSG_1(MSG_SSID_SNS,DBG_##level##_PRIO, DEVICE_NAME" - "msg,p1)
#define LSM6DSM_MSG_2(level,msg,p1,p2)    MSG_2(MSG_SSID_SNS,DBG_##level##_PRIO, DEVICE_NAME" - "msg,p1,p2)
#define LSM6DSM_MSG_3(level,msg,p1,p2,p3) MSG_3(MSG_SSID_SNS,DBG_##level##_PRIO, DEVICE_NAME" - "msg,p1,p2,p3)
#define LSM6DSM_MSG_4(level,msg,p1,p2,p3,p4) MSG_4(MSG_SSID_SNS,DBG_##level##_PRIO, DEVICE_NAME" - "msg,p1,p2,p3,p4)

#elif (!DEBUG_LOGS_VERBOSE)

#define LSM6DSM_MSG_0(level,msg)
#define LSM6DSM_MSG_1(level,msg,p1)
#define LSM6DSM_MSG_2(level,msg,p1,p2)
#define LSM6DSM_MSG_3(level,msg,p1,p2,p3)
#define LSM6DSM_MSG_4(level,msg,p1,p2,p3,p4)

#endif
//enable error logs only
#if (BUILD_DRAGON_BOARD)
#define LSM6DSM_MSG_E_0(level,msg)          MSG(MSG_SSID_QDSP6,DBG_##level##_PRIO, DEVICE_NAME" - "msg)
#define LSM6DSM_MSG_E_1(level,msg,p1)       MSG_1(MSG_SSID_QDSP6,DBG_##level##_PRIO, DEVICE_NAME" - "msg,p1)
#define LSM6DSM_MSG_E_2(level,msg,p1,p2)    MSG_2(MSG_SSID_QDSP6,DBG_##level##_PRIO, DEVICE_NAME" - "msg,p1,p2)
#define LSM6DSM_MSG_E_3(level,msg,p1,p2,p3) MSG_3(MSG_SSID_QDSP6,DBG_##level##_PRIO, DEVICE_NAME" - "msg,p1,p2,p3)
#define LSM6DSM_MSG_E_4(level,msg,p1,p2,p3,p4) MSG_4(MSG_SSID_QDSP6,DBG_##level##_PRIO, DEVICE_NAME" - "msg,p1,p2,p3,p4)

#elif (!BUILD_DRAGON_BOARD)
#define LSM6DSM_MSG_E_0(level,msg)          MSG(MSG_SSID_SNS,DBG_##level##_PRIO, DEVICE_NAME" - "msg)
#define LSM6DSM_MSG_E_1(level,msg,p1)       MSG_1(MSG_SSID_SNS,DBG_##level##_PRIO, DEVICE_NAME" - "msg,p1)
#define LSM6DSM_MSG_E_2(level,msg,p1,p2)    MSG_2(MSG_SSID_SNS,DBG_##level##_PRIO, DEVICE_NAME" - "msg,p1,p2)
#define LSM6DSM_MSG_E_3(level,msg,p1,p2,p3) MSG_3(MSG_SSID_SNS,DBG_##level##_PRIO, DEVICE_NAME" - "msg,p1,p2,p3)
#define LSM6DSM_MSG_E_4(level,msg,p1,p2,p3,p4) MSG_4(MSG_SSID_SNS,DBG_##level##_PRIO, DEVICE_NAME" - "msg,p1,p2,p3,p4)

#endif

#if (BUILD_DRAGON_BOARD) && (DEBUG_DATA)
#define LSM6DSM_DATA_MSG_0(level,msg)          MSG(MSG_SSID_QDSP6,DBG_##level##_PRIO, DEVICE_NAME" - "msg)
#define LSM6DSM_DATA_MSG_1(level,msg,p1)       MSG_1(MSG_SSID_QDSP6,DBG_##level##_PRIO, DEVICE_NAME" - "msg,p1)
#define LSM6DSM_DATA_MSG_2(level,msg,p1,p2)    MSG_2(MSG_SSID_QDSP6,DBG_##level##_PRIO, DEVICE_NAME" - "msg,p1,p2)
#define LSM6DSM_DATA_MSG_3(level,msg,p1,p2,p3) MSG_3(MSG_SSID_QDSP6,DBG_##level##_PRIO, DEVICE_NAME" - "msg,p1,p2,p3)
#define LSM6DSM_DATA_MSG_4(level,msg,p1,p2,p3,p4) MSG_4(MSG_SSID_QDSP6,DBG_##level##_PRIO, DEVICE_NAME" - "msg,p1,p2,p3,p4)

#elif (!BUILD_DRAGON_BOARD) && (DEBUG_DATA)
#define LSM6DSM_DATA_MSG_0(level,msg)          MSG(MSG_SSID_SNS,DBG_##level##_PRIO, DEVICE_NAME" - "msg)
#define LSM6DSM_DATA_MSG_1(level,msg,p1)       MSG_1(MSG_SSID_SNS,DBG_##level##_PRIO, DEVICE_NAME" - "msg,p1)
#define LSM6DSM_DATA_MSG_2(level,msg,p1,p2)    MSG_2(MSG_SSID_SNS,DBG_##level##_PRIO, DEVICE_NAME" - "msg,p1,p2)
#define LSM6DSM_DATA_MSG_3(level,msg,p1,p2,p3) MSG_3(MSG_SSID_SNS,DBG_##level##_PRIO, DEVICE_NAME" - "msg,p1,p2,p3)
#define LSM6DSM_DATA_MSG_4(level,msg,p1,p2,p3,p4) MSG_4(MSG_SSID_SNS,DBG_##level##_PRIO, DEVICE_NAME" - "msg,p1,p2,p3,p4)
#else
#define LSM6DSM_DATA_MSG_0(level,msg)
#define LSM6DSM_DATA_MSG_1(level,msg,p1)
#define LSM6DSM_DATA_MSG_2(level,msg,p1,p2)
#define LSM6DSM_DATA_MSG_3(level,msg,p1,p2,p3)
#define LSM6DSM_DATA_MSG_4(level,msg,p1,p2,p3,p4)
#endif
#else
#define 	sns_dd_lsm6dsm_malloc(ptr, size, smgr)				      sns_ddf_malloc_ex(ptr, size, smgr)
#define		sns_dd_lsm6dsm_mfree(ptr, smgr)						          sns_ddf_mfree_ex(ptr, smgr)
#define 	sns_dd_lsm6dsm_memhandler_malloc(ptr, size, smgr) 	sns_ddf_memhandler_malloc_ex(ptr, size, smgr)

#if (BUILD_DRAGON_BOARD) && (DEBUG_LOGS_VERBOSE)
#define LSM6DSM_MSG_0(level,msg)          UMSG(MSG_SSID_QDSP6,DBG_##level##_PRIO, DEVICE_NAME" - "msg)
#define LSM6DSM_MSG_1(level,msg,p1)       UMSG_1(MSG_SSID_QDSP6,DBG_##level##_PRIO, DEVICE_NAME" - "msg,p1)
#define LSM6DSM_MSG_2(level,msg,p1,p2)    UMSG_2(MSG_SSID_QDSP6,DBG_##level##_PRIO, DEVICE_NAME" - "msg,p1,p2)
#define LSM6DSM_MSG_3(level,msg,p1,p2,p3) UMSG_3(MSG_SSID_QDSP6,DBG_##level##_PRIO, DEVICE_NAME" - "msg,p1,p2,p3)
#define LSM6DSM_MSG_4(level,msg,p1,p2,p3,p4) UMSG_4(MSG_SSID_QDSP6,DBG_##level##_PRIO, DEVICE_NAME" - "msg,p1,p2,p3,p4)

#elif (!BUILD_DRAGON_BOARD) && (DEBUG_LOGS_VERBOSE)

#define LSM6DSM_MSG_0(level,msg)          UMSG(MSG_SSID_SNS,DBG_##level##_PRIO, DEVICE_NAME" - "msg)
#define LSM6DSM_MSG_1(level,msg,p1)       UMSG_1(MSG_SSID_SNS,DBG_##level##_PRIO, DEVICE_NAME" - "msg,p1)
#define LSM6DSM_MSG_2(level,msg,p1,p2)    UMSG_2(MSG_SSID_SNS,DBG_##level##_PRIO, DEVICE_NAME" - "msg,p1,p2)
#define LSM6DSM_MSG_3(level,msg,p1,p2,p3) UMSG_3(MSG_SSID_SNS,DBG_##level##_PRIO, DEVICE_NAME" - "msg,p1,p2,p3)
#define LSM6DSM_MSG_4(level,msg,p1,p2,p3,p4) UMSG_4(MSG_SSID_SNS,DBG_##level##_PRIO, DEVICE_NAME" - "msg,p1,p2,p3,p4)

#elif (!DEBUG_LOGS_VERBOSE)

#define LSM6DSM_MSG_0(level,msg)
#define LSM6DSM_MSG_1(level,msg,p1)
#define LSM6DSM_MSG_2(level,msg,p1,p2)
#define LSM6DSM_MSG_3(level,msg,p1,p2,p3)
#define LSM6DSM_MSG_4(level,msg,p1,p2,p3,p4)

#endif
//enable error logs only
#if (BUILD_DRAGON_BOARD)
#define LSM6DSM_MSG_E_0(level,msg)          UMSG(MSG_SSID_QDSP6,DBG_##level##_PRIO, DEVICE_NAME" - "msg)
#define LSM6DSM_MSG_E_1(level,msg,p1)       UMSG_1(MSG_SSID_QDSP6,DBG_##level##_PRIO, DEVICE_NAME" - "msg,p1)
#define LSM6DSM_MSG_E_2(level,msg,p1,p2)    UMSG_2(MSG_SSID_QDSP6,DBG_##level##_PRIO, DEVICE_NAME" - "msg,p1,p2)
#define LSM6DSM_MSG_E_3(level,msg,p1,p2,p3) UMSG_3(MSG_SSID_QDSP6,DBG_##level##_PRIO, DEVICE_NAME" - "msg,p1,p2,p3)
#define LSM6DSM_MSG_E_4(level,msg,p1,p2,p3,p4) UMSG_4(MSG_SSID_QDSP6,DBG_##level##_PRIO, DEVICE_NAME" - "msg,p1,p2,p3,p4)

#elif (!BUILD_DRAGON_BOARD)
#define LSM6DSM_MSG_E_0(level,msg)          UMSG(MSG_SSID_SNS,DBG_##level##_PRIO, DEVICE_NAME" - "msg)
#define LSM6DSM_MSG_E_1(level,msg,p1)       UMSG_1(MSG_SSID_SNS,DBG_##level##_PRIO, DEVICE_NAME" - "msg,p1)
#define LSM6DSM_MSG_E_2(level,msg,p1,p2)    UMSG_2(MSG_SSID_SNS,DBG_##level##_PRIO, DEVICE_NAME" - "msg,p1,p2)
#define LSM6DSM_MSG_E_3(level,msg,p1,p2,p3) UMSG_3(MSG_SSID_SNS,DBG_##level##_PRIO, DEVICE_NAME" - "msg,p1,p2,p3)
#define LSM6DSM_MSG_E_4(level,msg,p1,p2,p3,p4) UMSG_4(MSG_SSID_SNS,DBG_##level##_PRIO, DEVICE_NAME" - "msg,p1,p2,p3,p4)

#endif

#if (BUILD_DRAGON_BOARD) && (DEBUG_DATA)
#define LSM6DSM_DATA_MSG_0(level,msg)          UMSG(MSG_SSID_QDSP6,DBG_##level##_PRIO, DEVICE_NAME" - "msg)
#define LSM6DSM_DATA_MSG_1(level,msg,p1)       UMSG_1(MSG_SSID_QDSP6,DBG_##level##_PRIO, DEVICE_NAME" - "msg,p1)
#define LSM6DSM_DATA_MSG_2(level,msg,p1,p2)    UMSG_2(MSG_SSID_QDSP6,DBG_##level##_PRIO, DEVICE_NAME" - "msg,p1,p2)
#define LSM6DSM_DATA_MSG_3(level,msg,p1,p2,p3) UMSG_3(MSG_SSID_QDSP6,DBG_##level##_PRIO, DEVICE_NAME" - "msg,p1,p2,p3)
#define LSM6DSM_DATA_MSG_4(level,msg,p1,p2,p3,p4) UMSG_4(MSG_SSID_QDSP6,DBG_##level##_PRIO, DEVICE_NAME" - "msg,p1,p2,p3,p4)

#elif (!BUILD_DRAGON_BOARD) && (DEBUG_DATA)
#define LSM6DSM_DATA_MSG_0(level,msg)          UMSG(MSG_SSID_SNS,DBG_##level##_PRIO, DEVICE_NAME" - "msg)
#define LSM6DSM_DATA_MSG_1(level,msg,p1)       UMSG_1(MSG_SSID_SNS,DBG_##level##_PRIO, DEVICE_NAME" - "msg,p1)
#define LSM6DSM_DATA_MSG_2(level,msg,p1,p2)    UMSG_2(MSG_SSID_SNS,DBG_##level##_PRIO, DEVICE_NAME" - "msg,p1,p2)
#define LSM6DSM_DATA_MSG_3(level,msg,p1,p2,p3) UMSG_3(MSG_SSID_SNS,DBG_##level##_PRIO, DEVICE_NAME" - "msg,p1,p2,p3)
#define LSM6DSM_DATA_MSG_4(level,msg,p1,p2,p3,p4) UMSG_4(MSG_SSID_SNS,DBG_##level##_PRIO, DEVICE_NAME" - "msg,p1,p2,p3,p4)
#else
#define LSM6DSM_DATA_MSG_0(level,msg)
#define LSM6DSM_DATA_MSG_1(level,msg,p1)
#define LSM6DSM_DATA_MSG_2(level,msg,p1,p2)
#define LSM6DSM_DATA_MSG_3(level,msg,p1,p2,p3)
#define LSM6DSM_DATA_MSG_4(level,msg,p1,p2,p3,p4)
#endif
#endif

typedef uint32_t dd_handle_align_t;
#define UDIV_UP(a, b) ((a) / (b))
#define ALIGN_UP(a, b) (UDIV_UP(a, b) * (b))

#define STM_LSM6DSM_AXES_PER_SENSOR  3
#define STM_LSM6DSM_BYTES_PER_SAMPLE 6
#define AUTO_INCREMENT             0x80 //to read multiple bytes MSB should be 1

#define TICKS_PER_SEC      32768
#define TICKS_TO_USEC(x) (x*(1000000/TICKS_PER_SEC))

#define LSM6DSM_ASSUMED_SMGR_S4S_TICKS_PER_SEC 32000
#define LSM6DSM_ASSUMED_SMGR_NOMINAL_S4S_TICKS (LSM6DSM_ASSUMED_SMGR_S4S_TICKS_PER_SEC * 1)

#define BIT(x) (0x01 << x)
typedef enum
{
  STM_LSM6DSM_ODR0 = -1,
  STM_LSM6DSM_ODR13 ,
  STM_LSM6DSM_ODR26 ,
  STM_LSM6DSM_ODR52 ,
  STM_LSM6DSM_ODR104,
  STM_LSM6DSM_ODR208,
  STM_LSM6DSM_ODR416,
  STM_LSM6DSM_ODR833,
  STM_LSM6DSM_ODR1660,
  STM_LSM6DSM_ODR3330,
  STM_LSM6DSM_ODR6660,
}stm_lsm6dsm_odr_idx;

typedef enum
{
  STM_LSM6DSM_BM__NONE = 0,
  STM_LSM6DSM_BM_ACCEL = BIT(0),
  STM_LSM6DSM_BM_GYRO  = BIT(1),
  STM_LSM6DSM_BM_SMD   = BIT(2),
  STM_LSM6DSM_BM_STC   = BIT(3),
  STM_LSM6DSM_BM_STE   = BIT(4),
  STM_LSM6DSM_BM_TILT  = BIT(5),
  STM_LSM6DSM_BM_D6D   = BIT(6),
  STM_LSM6DSM_BM_DBT   = BIT(7),
}stm_lsm6dsm_sensor_bm_e;

typedef enum {
  ACCEL_FIFO_BM  =  BIT(0),
  GYRO_FIFO_BM   =  BIT(1),
  TEMP_A_FIFO_BM =  BIT(2),
  TEMP_G_FIFO_BM =  BIT(3),
  SLAVE_FIFO_BM  =  BIT(4),
}stm_lsm6dsm_fifo_bm_e;

/**
 * LSM6DSM Full Scales in register setting for gyro
 */
typedef enum
{
  STM_LSM6DSM_GYR_RANGE_125DPS   = 0x02,
  STM_LSM6DSM_GYR_RANGE_245DPS   = 0x00,
  STM_LSM6DSM_GYR_RANGE_500DPS   = 0x04,
  STM_LSM6DSM_GYR_RANGE_1000DPS  = 0x08,
  STM_LSM6DSM_GYR_RANGE_2000DPS  = 0x0C,
} stm_lsm6dsm_gyr_range;

#define STM_LSM6DSM_GYR_MAX_RANGE STM_LSM6DSM_GYR_RANGE_2000G

/**
 * LSM6DSM min and max of ranges, converted to Q16 for gyro.
 */
#define STM_LSM6DSM_GYR_RANGE_125_MIN    FX_FLTTOFIX_Q16(-125 * PI /180)
#define STM_LSM6DSM_GYR_RANGE_125_MAX    FX_FLTTOFIX_Q16(125 * PI /180)
#define STM_LSM6DSM_GYR_RANGE_245_MIN    FX_FLTTOFIX_Q16(-245 * PI /180)
#define STM_LSM6DSM_GYR_RANGE_245_MAX    FX_FLTTOFIX_Q16(245 * PI /180)
#define STM_LSM6DSM_GYR_RANGE_500_MIN    FX_FLTTOFIX_Q16(-500 * PI /180)
#define STM_LSM6DSM_GYR_RANGE_500_MAX    FX_FLTTOFIX_Q16(500 * PI /180)
#define STM_LSM6DSM_GYR_RANGE_1000_MIN   FX_FLTTOFIX_Q16(-1000 * PI /180)
#define STM_LSM6DSM_GYR_RANGE_1000_MAX   FX_FLTTOFIX_Q16(1000 * PI /180)
#define STM_LSM6DSM_GYR_RANGE_2000_MIN   FX_FLTTOFIX_Q16(-2000 * PI /180)
#define STM_LSM6DSM_GYR_RANGE_2000_MAX   FX_FLTTOFIX_Q16(2000 * PI /180)

/**
 * LSM6DSM sensitivity for gyro
 */
/* value of sensitivity at 240dps, converted to (rad/s)*1000 */
#define STM_LSM6DSM_GYR_SSTVT_125DPS  FX_FLTTOFIX_Q16(4.38*PI/180)
/* value of sensitivity at 240dps, converted to (rad/s)*1000 */
#define STM_LSM6DSM_GYR_SSTVT_245DPS  FX_FLTTOFIX_Q16(8.75*PI/180)
/* value of sensitivity at 500dps, converted to rad/s */
#define STM_LSM6DSM_GYR_SSTVT_500DPS  FX_FLTTOFIX_Q16(17.50*PI/180)
/* value of sensitivity at 1000dps, converted to rad/s */
#define STM_LSM6DSM_GYR_SSTVT_1000DPS  FX_FLTTOFIX_Q16(35.00*PI/180)
/* value of sensitivity at 2000dps, converted to rad/s */
#define STM_LSM6DSM_GYR_SSTVT_2000DPS  FX_FLTTOFIX_Q16(70.00*PI/180)

/**
 * LSM6DSM output data rate for gyro, Disabling LPF2,
 * so BW setting is not required
 */
typedef enum
{
  STM_LSM6DSM_GYR_ODR_OFF =        0x00,       /* power down output data rate */
  STM_LSM6DSM_GYR_ODR13   =        0x10,       /* 13 Hz output data rate */
  STM_LSM6DSM_GYR_ODR26   =        0x20,       /* 26 Hz output data rate */
  STM_LSM6DSM_GYR_ODR52   =        0x30,       /* 52 Hz output data rate */
  STM_LSM6DSM_GYR_ODR104  =        0x40,       /* 104 Hz output data rate */
  STM_LSM6DSM_GYR_ODR208  =        0x50,       /* 208 Hz output data rate */
  STM_LSM6DSM_GYR_ODR416  =        0x60,       /* 416 Hz output data rate */
  STM_LSM6DSM_GYR_ODR833  =        0x70,       /* 833 Hz output data rate */
  STM_LSM6DSM_GYR_ODR1660 =        0x80,       /* 1.66 kHz output data rate */

} stm_lsm6dsm_gyr_odr;

/**
 * Accelerometer LSM6DSM_ACC Full Scales in register setting.
 */
typedef enum
{
  STM_LSM6DSM_ACC_RANGE_2G   = 0x00,  /*corresponding value in register setting*/
  STM_LSM6DSM_ACC_RANGE_4G   = 0x08,
  STM_LSM6DSM_ACC_RANGE_8G   = 0x0C,
  STM_LSM6DSM_ACC_RANGE_16G   = 0x04,
} stm_lsm6dsm_acc_range;

#define STM_LSM6DSM_ACC_MAX_RANGE  STM_LSM6DSM_ACC_RANGE_16G

/**
 * Accelerometer LSM6DSM_ACC ranges, converted to Q16.
 */
#define STM_LSM6DSM_ACC_RANGE_2G_MIN    FX_FLTTOFIX_Q16(-2*G)
#define STM_LSM6DSM_ACC_RANGE_2G_MAX    FX_FLTTOFIX_Q16(2*G)
#define STM_LSM6DSM_ACC_RANGE_4G_MIN    FX_FLTTOFIX_Q16(-4*G)
#define STM_LSM6DSM_ACC_RANGE_4G_MAX    FX_FLTTOFIX_Q16(4*G)
#define STM_LSM6DSM_ACC_RANGE_8G_MIN    FX_FLTTOFIX_Q16(-8*G)
#define STM_LSM6DSM_ACC_RANGE_8G_MAX    FX_FLTTOFIX_Q16(8*G)
#define STM_LSM6DSM_ACC_RANGE_16G_MIN    FX_FLTTOFIX_Q16(-16*G)
#define STM_LSM6DSM_ACC_RANGE_16G_MAX    FX_FLTTOFIX_Q16(16*G)

/**
 * Accelerometer LSM6DSM_ACC sensitivity for each range.
 */
typedef enum
{
  STM_LSM6DSM_ACC_SSTVT_2G  = 61,   /* in the unit of micro-g/digit */
  STM_LSM6DSM_ACC_SSTVT_4G  = 122,
  STM_LSM6DSM_ACC_SSTVT_8G  = 244,
  STM_LSM6DSM_ACC_SSTVT_16G = 488,
}stm_lsm6dsm_acc_sstvt;

/**
 * Accelerometer LSM6DSM_ACC output data rate in register setting
 */
typedef enum
{
  STM_LSM6DSM_ACC_ODR_OFF   = 0x00,
  STM_LSM6DSM_ACC_ODR13     = 0x10,  /* 13 Hz output data rate */
  STM_LSM6DSM_ACC_ODR26     = 0x20,  /* 26 Hz output data rate */
  STM_LSM6DSM_ACC_ODR52     = 0x30,  /* 52 Hz output data rate */
  STM_LSM6DSM_ACC_ODR104    = 0x40,  /* 104 Hz output data rate */
  STM_LSM6DSM_ACC_ODR208    = 0x50,  /* 208 Hz output data rate */
  STM_LSM6DSM_ACC_ODR416    = 0x60,  /* 416 Hz output data rate */
  STM_LSM6DSM_ACC_ODR833    = 0x70,  /* 833 Hz output data rate */
  STM_LSM6DSM_ACC_ODR1660   = 0x80,  /* 1.66 kHz output data rate */
  STM_LSM6DSM_ACC_ODR3330   = 0x90,  /* 3.33 kHz output data rate */
  STM_LSM6DSM_ACC_ODR6660   = 0xA0,  /* 6.66 kHz output data rate */
} stm_lsm6dsm_acc_odr;

/**
 * Accelerometer LSM6DSM ACC filter bandwidth in register setting
 */
typedef enum
{
  STM_LSM6DSM_ACC_BW50      = 0x03,  /* 50 Hz bandwidth */
  STM_LSM6DSM_ACC_BW100     = 0x02,  /* 100 Hz bandwidth */
  STM_LSM6DSM_ACC_BW200     = 0x01,  /* 200 Hz bandwidth */
  STM_LSM6DSM_ACC_BW400     = 0x00   /* 400 Hz bandwidth */
} stm_lsm6dsm_acc_bw;

#define STM_LSM6DSM_ODR_NUM         (STM_LSM6DSM_ODR6660+1)
//#define STM_LSM6DSM_MAX_ODR_416     416
//#define STM_LSM6DSM_MAX_ODR_208     200

#define STM_LSM6DSM_MAX_ODR_IDX     (SMGR_SUPPORTED_MAX_ODR_IDX) //specifiy only odr index
#define STM_LSM6DSM_MIN_ODR_IDX     (STM_LSM6DSM_ODR13) //specifiy only odr index
#define STM_LSM6DSM_MAX_S4S_ODR_IDX (SMGR_SUPPORTED_MAX_S4S_ODR_IDX) //specifiy only odr index
#define STM_LSM6DSM_MIN_S4S_ODR_IDX (STM_LSM6DSM_ODR52) //specifiy only odr index

/* fifo paramters */
#define STM_LSM6DSM_MAX_FIFO_BYTES 4096 // Max fifo samples 4K bytes to samples
#define STM_LSM6DSM_MAX_FIFO       (STM_LSM6DSM_MAX_FIFO_BYTES / STM_LSM6DSM_BYTES_PER_SAMPLE) // Max fifo samples 4K bytes to samples
#define STM_LSM6DSM_MAX_FIFO_READ STM_LSM6DSM_MAX_FIFO_BYTES // max fifo samples to read at once 240 bytes (20 samples per sensor)
#define STM_LSM6DSM_MAX_PATTERN_SAMPLES 4
#define STM_LSM6DSM_MAX_TEMP_FIFO_DEPTH 20
#define STM_LSM6DSM_MAX_SHARED_FIFO_SENSORS 4 //maximum sensors that can be shared
/**
 * LSM6DSM output data rate for gyro, Disabling LPF2,
 * so BW setting is not required
 */
typedef enum
{
  STM_LSM6DSM_FIFO_ODR_OFF =        0x00,       /* power down output data rate */
  STM_LSM6DSM_FIFO_ODR13   =        0x08,       /* 13 Hz data rate */
  STM_LSM6DSM_FIFO_ODR26   =        0x10,       /* 26 Hz data rate */
  STM_LSM6DSM_FIFO_ODR52   =        0x18,       /* 52 Hz data rate */
  STM_LSM6DSM_FIFO_ODR104  =        0x20,       /* 104 Hz data rate */
  STM_LSM6DSM_FIFO_ODR208  =        0x28,       /* 208 Hz data rate */
  STM_LSM6DSM_FIFO_ODR416  =        0x30,       /* 416 Hz data rate */
  STM_LSM6DSM_FIFO_ODR833  =        0x38,       /* 833 Hz data rate */
  STM_LSM6DSM_FIFO_ODR1660 =        0x40,       /* 1660 Hz data rate */
  STM_LSM6DSM_FIFO_ODR3330 =        0x48,       /* 3330 Hz data rate */
  STM_LSM6DSM_FIFO_ODR6660 =        0x50,       /* 6660 Hz data rate */
} stm_lsm6dsm_fifo_odr;

typedef enum
{
  STM_LSM6DSM_S4S_NOT_SYNCED,
  STM_LSM6DSM_S4S_SYNCING,
  STM_LSM6DSM_S4S_1ST_SYNCED,
  STM_LSM6DSM_S4S_SYNCED,
} stm_lsm6dsm_s4s_sync_state;




/* Address registers */

#define STM_LSM6DSM_FUNC_CFG_ACCESS_ADDR  (0x01)
#define STM_LSM6DSM_FORWARD_ADDR          (0x02)
#define STM_LSM6DSM_FORWARD_VALUE         (0x03)
#define STM_LSM6DSM_REG_T_PH              (0x04)
#define STM_LSM6DSM_REG_RR                (0x05)
#define STM_LSM6DSM_REG_FIFO_CTRL1        (0x06)
#define STM_LSM6DSM_REG_FIFO_CTRL2        (0x07)
#define STM_LSM6DSM_REG_FIFO_CTRL3        (0x08)
#define STM_LSM6DSM_REG_FIFO_CTRL4        (0x09)
#define STM_LSM6DSM_REG_FIFO_CTRL5        (0x0A)
#define STM_LSM6DSM_REG_INT1_CTRL         (0x0D)
#define STM_LSM6DSM_REG_INT2_CTRL         (0x0E)
#define STM_LSM6DSM_REG_WHO_AM_I          (0x0F)
#define STM_LSM6DSM_REG_CTRL1_A           (0x10)
#define STM_LSM6DSM_REG_CTRL2_G           (0x11)
#define STM_LSM6DSM_REG_CTRL3             (0x12)
#define STM_LSM6DSM_REG_CTRL4             (0x13)
#define STM_LSM6DSM_REG_CTRL5             (0x14)
#define STM_LSM6DSM_REG_CTRL6_G           (0x15)
#define STM_LSM6DSM_REG_CTRL7_G           (0x16)
#define STM_LSM6DSM_REG_CTRL8_XL          (0x17)
#define STM_LSM6DSM_REG_CTRL9_A           (0x18)
#define STM_LSM6DSM_REG_CTRL10_C          (0x19)
#define STM_LSM6DSM_REG_WAKE_SRC          (0x1B)
#define STM_LSM6DSM_REG_TAP_SRC           (0x1C)
#define STM_LSM6DSM_REG_D6D_SRC           (0x1D)
#define STM_LSM6DSM_REG_STATUS            (0x1E)

#define STM_LSM6DSM_REG_OUT_TEMP_L        (0x20)
#define STM_LSM6DSM_REG_OUT_TEMP_H        (0x21)
#define STM_LSM6DSM_REG_OUT_X_L_G         (0x22)
#define STM_LSM6DSM_REG_OUT_X_H_G         (0x23)
#define STM_LSM6DSM_REG_OUT_Y_L_G         (0x24)
#define STM_LSM6DSM_REG_OUT_Y_H_G         (0x25)
#define STM_LSM6DSM_REG_OUT_Z_L_G         (0x26)
#define STM_LSM6DSM_REG_OUT_Z_H_G         (0x27)
#define STM_LSM6DSM_REG_OUT_X_L_XL        (0x28)
#define STM_LSM6DSM_REG_OUT_X_H_XL        (0x29)
#define STM_LSM6DSM_REG_OUT_Y_L_XL        (0x2A)
#define STM_LSM6DSM_REG_OUT_Y_H_XL        (0x2B)
#define STM_LSM6DSM_REG_OUT_Z_L_XL        (0x2C)
#define STM_LSM6DSM_REG_OUT_Z_H_XL        (0x2D)
#define STM_LSM6DSM_REG_SENSOR_HUB1       (0x2E)
#define STM_LSM6DSM_REG_SENSOR_HUB10      (0x37)
#define STM_LSM6DSM_REG_FIFO_STATUS1      (0x3A)
#define STM_LSM6DSM_REG_FIFO_STATUS2      (0x3B)
#define STM_LSM6DSM_REG_FIFO_STATUS3      (0x3C)
#define STM_LSM6DSM_REG_FIFO_STATUS4      (0x3D)
#define STM_LSM6DSM_REG_FIFO_DATA_OUT_L   (0x3E)
#define STM_LSM6DSM_REG_FIFO_DATA_OUT_H   (0x3F)
#define STM_LSM6DSM_REG_TIMESTAMP0_REG    (0x40)
#define STM_LSM6DSM_REG_TIMESTAMP1_REG    (0x41)
#define STM_LSM6DSM_REG_TIMESTAMP2_REG    (0x42)
#define STM_LSM6DSM_REG_STEP_COUNTER_L    (0x4B)
#define STM_LSM6DSM_REG_STEP_COUNTER_H    (0x4C)
#define STM_LSM6DSM_REG_FUNC_SRC          (0x53)
#define STM_LSM6DSM_REG_TAP_CFG           (0x58)
#define STM_LSM6DSM_REG_TAP_THS_6D        (0x59)
#define STM_LSM6DSM_REG_TAP_DUR           (0x5A)
#define STM_LSM6DSM_REG_WAKE_THS          (0x5B)
#define STM_LSM6DSM_REG_WAKE_DUR          (0x5C)
#define STM_LSM6DSM_REG_MD1_CFG           (0x5E)
#define STM_LSM6DSM_REG_MD2_CFG           (0x5F)
#define STM_LSM6DSM_REG_ST                (0x60)
#define STM_LSM6DSM_REG_DT                (0x61)


#define  	STM_LSM6DSM_FIFO_WTM_STATUS_MASK  (0x80)
#define  	STM_LSM6DSM_FIFO_OVR_STATUS_MASK  (0x40)
#define  	STM_LSM6DSM_FIFO_FULL_STATUS_MASK  (0x20)
#define  	STM_LSM6DSM_FIFO_EMPTY_STATUS_MASK  (0x10)
#define  	STM_LSM6DSM_FIFO_PATTERN_STATUS3  (0xFF)
#define  	STM_LSM6DSM_FIFO_PATTERN_STATUS4  (0x03)
#define  	STM_LSM6DSM_FIFO_WTM_CTRL1_MASK  	(0xFF)
#define  	STM_LSM6DSM_FIFO_WTM_CTRL2_MASK  	(0x07)
#define  	STM_LSM6DSM_FIFO_DEC_XL_MASK  	  (0x07)
#define  	STM_LSM6DSM_FIFO_DEC_G_MASK  	    (0x38)
#define  	STM_LSM6DSM_FIFO_MODE_MASK  	    (0x07)
#define  	STM_LSM6DSM_FIFO_ODR_MASK  	      (0x78)
#define  	STM_LSM6DSM_INT1_FTH_MASK  	      (0x08)
#define  	STM_LSM6DSM_INT1_OVR_MASK  	      (0x10)
#define  	STM_LSM6DSM_FIFO_INT_MASK         (0x38)
#define  	STM_LSM6DSM_FS_XL_MASK  	        (0x0C)
#define  	STM_LSM6DSM_ODR_XL_MASK  	        (0xF0)
#define  	STM_LSM6DSM_ODR_BW_XL_MASK  	    (0xF3)
#define  	STM_LSM6DSM_FS_G_MASK  	          (0x0E)
#define  	STM_LSM6DSM_ODR_G_MASK  	        (0xF0)
#define  	STM_LSM6DSM_ACC_DEC_MASK  	      (0x07)
#define  	STM_LSM6DSM_GYR_DEC_MASK  	      (0x38)
#define  	STM_LSM6DSM_SLV1_DEC_MASK  	      (0x07)


#define   STM_LSM6DSM_ENABLE_FUNC_CFG_ACCESS (0x80)
#define   STM_LSM6DSM_FUNC_CFG_ACCESS_BASE  (0x00)


/* Default values loaded in probe function */
#define STM_LSM6DSM_WHOAMI_VALUE              (0x6A)  /** Who Am I default value */

/**
 * LSM6DSM data bit length for gyro
 */
#define STM_GYR_SENSOR_BIT_LEN          16

#define LSM6DSM_MAX_SENSOR_TYPES  2
#define LSM6DSM_MAX_SUB_DEV       8
//modify align bits  to increase sub_dev count
//#define DD_HANDLE_ALIGN_32BITS    0xFFFFFFFFFFFFFFFC
#define DD_HANDLE_ALIGN_32BITS    -8
#define DD_HANDLE_ALIGN_BITS      DD_HANDLE_ALIGN_32BITS
#define DD_HANDLE_ALIGN_64        DD_HANDLE_ALIGN_BITS
#define MIN_NZERO(a,b) ((a > b) ? ((b > 0) ? b : a) : ((a > 0) ? a : b))
#define LSM6DSM_MAX_ESP_SENSORS 6
#define LSM6DSM_IS_ESP_SENSOR(s) ((s == SNS_DDF_SENSOR_SMD) || \
              (s == SNS_DDF_SENSOR_STEP_EVENT) || \
              (s == SNS_DDF_SENSOR_STEP_COUNT) || \
              (s == SNS_DDF_SENSOR_TILT_EVENT) || \
              (s == SNS_DDF_SENSOR_D6D_EVENT)  || \
              (s == SNS_DDF_SENSOR_DOUBLETAP)) ? (true) : (false)
#define LSM6DSM_IS_ESP_ACTIVE(s) ((s.esp_enabled) ? true : false)
#define LSM6DSM_IS_HUB_SLV_SENSOR(s) (s == LSM6DSM_SLAVE_SENSOR) ? (true) : (false)
#define LSM6DSM_IS_HUB_SLV_ACTIVE(s) (s.cur_rate) ? (true) : (false)
#define LSM6DSM_ESP_RATE(s) (s.esp_enabled & STM_LSM6DSM_BM_DBT) ? (STM_LSM6DSM_MIN_DBT_ODR) : (STM_LSM6DSM_MIN_ESP_ODR)
#define STM_LSM6DSM_MIN_ESP_ODR STM_LSM6DSM_ODR26 //index
#define STM_LSM6DSM_MIN_DBT_ODR STM_LSM6DSM_ODR416 //index
#if LSM6DSM_ENABLE_HUB
#define LSM6DSM_SLAVE_AK09916   1
#define AK09916_OUTDATA_LEN    (0x06)
#define AK09916_AXES           (0x03)
#if LSM6DSM_SLAVE_AK09916
#define LSM6DSM_SLAVE_1_OUTDATA_LEN     AK09916_OUTDATA_LEN
#define LSM6DSM_SLAVE_1_AXES            AK09916_AXES
#define LSM6DSM_SLAVE_SENSOR SNS_DDF_SENSOR_MAG
#endif
#else
#define LSM6DSM_SLAVE_SENSOR SNS_DDF_SENSOR__NONE
#define LSM6DSM_SLAVE_1_AXES STM_LSM6DSM_AXES_PER_SENSOR
#endif

/**
 * Accelerometer LSM6DSM Driver, device instance chain Structure
 */
typedef struct
{
  sns_ddf_dev_list_t next;       /* the next device instance */
  sns_ddf_driver_info_s dd_info; /* the driver info */
}stm_lsm6dsm_head_s;

/**
 * Accelerometer LSM6DSM Driver, sub device Structure
 */
typedef struct
{
  uint32_t num_sensors;

  sns_ddf_sensor_e sensors[LSM6DSM_MAX_SENSOR_TYPES];

  /**< sensor power state. */
  sns_ddf_powerstate_e powerstate;


  /**< Handle used with sns_ddf_notify_data. */
  sns_ddf_handle_t smgr_handle;
}stm_lsm6dsm_sub_dev_s;

/**
 * LSM6DSM Driver, NV_PARAMS Structure
 */
#define STM_LSM6DSM_NVPARAMS_DATALEN     136
#define STM_LSM6DSM_NVPARAMS_OFFSET      64
#define STM_LSM6DSM_MAG_NUM1             0x01
#define STM_LSM6DSM_MAG_NUM2             0xDB
#define STM_LSM6DSM_MAG_NUM3             0xBA
#define STM_LSM6DSM_MAG_NUM4             0xAB

/**
 * Accelerometer LSM6DSM Driver, esp config
 */
//Default setting when DBT is off.
#define STM_LSM6DSM_MD_THRESH          0x1    //1LSB = FS/2^6 FS = 4 1LSB=62.5mg
#define STM_LSM6DSM_MD_DUR             0x0    // 1 sample
#define STM_LSM6DSM_MD_ODR             13     //10 Hz
//Default setting when DBT is on.
//The new setting through registry will overwrite this one.
#define STM_LSM6DSM_MD_THRESH_2        0x5    //156 mg.
#define STM_LSM6DSM_MD_DUR_2           0x8    // 8 samples=5.6ms
#define STM_LSM6DSM_MD_ODR_2           416  //12500 Hz

#define STM_LSM6DSM_DBT_THRESH         (0x06)   //0.75mg for 4G fullscale th*FS/2^5
#define STM_LSM6DSM_DBT_MAX_TIME_GAP   (7)   //7*32*ODR_time = 7*32/416 = 538.5 ms
#define STM_LSM6DSM_DBT_QUIET_TIME     (3)   //3*4*ODR_time = 3*4/416 = 28.8ms
#define STM_LSM6DSM_DBT_SHOCK_TIME     (3)   //3*8*ODR_time = 3*8/416 = 57.7ms


#define HPF_SETTLING_SAMPLES 50
#define SLOPE_SETTLING_SAMPLES 3

typedef enum {
  SELFTEST_HW,
  SELFTEST_SW,
  SELFTEST_OEM,
  SETTLING_SLOPE,
  SETTLING_HPF,
  TEMP_DATA
}timer_msg_t;

typedef enum {
  SLOPE_FILTER,
  HP_FILTER,
}filter_t;

typedef PACK(struct)
{
  /**< Magic number string for LSM6DSM */
  uint8_t  magic_num[4];
  /**< motion detection threshold. 0x0: 31.25 mg,  0x1: 62.5 mg*/
  uint8_t  md_thresh;
  /**< Num_of_samples to check */
  uint8_t  md_dur;
  /**< motion detection ODR. 50 for 50Hz. */
  uint16_t md_ODR;
  /**< MD reserved. */
  uint32_t md_rsvd[6];
  /**< double tap threshold @4G*/
  uint8_t  dbt_thresh;
  /**< double tap max time btn two successive taps*/
  uint16_t dbt_max_time_gap;
  /**< double tap quiet time after first tap*/
  uint16_t dbt_quiet_time;
  /**< double tap max duration of overthereshold event*/
  uint8_t  dbt_shock_time;
  /**< double tap reserved. */
  uint32_t dbt_rsvd[5];
}stm_lsm6dsm_nv_params;

/**
 * Accelerometer LSM6DSM Driver, SM1 and SM2 configuration Structure
 */
typedef struct
{
  /**< motion detection threshold.  0x0: 31.25 mg,  0x1: 62.5 mg*/
  uint8_t  md_thresh;
  /**< Num_of_samples to check */
  uint8_t  md_dur;
  /**< motion detection ODR. 50 for 50Hz. */
  uint16_t md_ODR;
  /**< double tap threshold @2G*/
  uint8_t  dbt_thresh;
  /**< double tap max time btn two successive taps*/
  uint16_t dbt_max_time_gap;
  /**< double tap quiet time after first tap*/
  uint16_t dbt_quiet_time;
  /**< double tap max duration of overthereshold event*/
  uint8_t  dbt_shock_time;
}stm_lsm6dsm_esp_config;

typedef struct stm_lsm6dsm_timer_s{
  /**< Timer structure. */
  sns_ddf_timer_s timer;
  timer_msg_t reason;
  bool repeat; // for selftest, ture first stage, false second stage
}stm_lsm6dsm_timer;

typedef struct {
  bool acc_intp_status;

  bool gyr_intp_status;

  bool acc_last_sample_status;
  bool gyr_last_sample_status;
  /** acc last sample backup**/
  q16_t acc_last_sample[3];
  /** acc last sample backup**/
  q16_t gyr_last_sample[3];

}stm_lsm6dsm_data_intp_t;

typedef struct {

  /** LSM6DSM fifo raw data buffer */
  uint8_t *raw_buffer;

  sns_ddf_sensor_data_s acc_data;

  sns_ddf_sensor_data_s gyr_data;

  sns_ddf_sensor_data_s temp_data;

  /** FIFO enabled or not for accel and gyro
   * first bit is accel and second bit gyro*/
  uint8_t fifo_enabled;

  /** FIFO and INT enabled or not*/
  /** bit 0 accel  bit 1 gyro */
  uint8_t fifo_int_enabled;

  /** number of sensors enabled in fifo mode*/
  uint8_t active_sensors;

  /** fifo cur rate index */
  int8_t fifo_rate_idx;

  /** FIFO watermark levels for accel and gyro*/
  uint16_t acc_wmk;
  uint16_t gyr_wmk;
  uint16_t cur_wmk;

  /** accel fifo status*/
  bool acc_fifo_alive;

  /** accel and gyro samples during fifo read*/
  uint16_t acc_sample_cnt;
  uint16_t gyr_sample_cnt;
  uint16_t temp_sample_cnt;

  /** fifo pattern array **/
  uint8_t pattern_array[STM_LSM6DSM_MAX_PATTERN_SAMPLES];
  /** number of pattern samples **/
  uint8_t pattern_samples_cnt;

  /** last FIFO watermark interrupt timestamp*/
  sns_ddf_time_t last_timestamp;

  /** calculated sample time **/
  sns_ddf_time_t avg_sample_time;

  /** reading fifo data first time or repeating */
  bool first_pass;

}stm_lsm6dsm_fifo_info_s;

typedef struct {

  sns_ddf_driver_if_s* esp_if;

  /** esp enabled or not */
  uint16_t esp_enabled;
  /** LSM6DSM state machines 1 and 2 config data */
  stm_lsm6dsm_esp_config esp_config;
}stm_lsm6dsm_esp_info_s;

typedef struct {
  sns_ddf_driver_if_s* hub_if;
  sns_ddf_odr_t cur_rate;
  int8_t master_rate_idx;
  uint16_t sample_cnt;
  float sstvt;
  bool intp_status;
  sns_ddf_sensor_data_s slv_data;
  sns_ddf_time_t odr_settled_ts;
  uint8_t dec;
  uint16_t wmk;
  /**< Device-to-phone axis mapping. */
  sns_ddf_axes_map_s axes_map;
}stm_lsm6dsm_hub_info_s;

typedef struct {
  /* S4S data */
  int16_t  t_ph[LSM6DSM_MAX_SENSOR_TYPES];
  int8_t   rr;
  uint32_t ideal_sync_interval;
  bool     fifo_int_en;
  uint32_t dt_value;
  sns_ddf_st_t curr_sync_time;
  sns_ddf_st_t pending_sync_time;
  float    ticks_per_rr;
  stm_lsm6dsm_s4s_sync_state synced;
  uint16_t modified_t_ph;
  uint8_t  t_ph_reg_value;
  bool     skip_dt;
  bool     config_changed;
  sns_ddf_sensor_e stdt_sensor;
  //sensors who are subscribed for s4s
  uint16_t sensor_sbsp;
}stm_lsm6dsm_s4s_config_s;


/**
 * LSM6DSM Driver State Information Structure
 */
typedef struct {
  /**< pointer to next device int the device chain. */
  sns_ddf_dev_list_t next;

  /**< the identifier of this port. */
  sns_ddf_port_id_s port_id;

  /**< the identifier of this port. */
  sns_ddf_bus_e bus_id;

  /**< the identifier of this port. */
  sns_ddf_odr_t* odr_list;
  uint32_t       max_supported_odr_idx;
  uint32_t       min_supported_odr_idx;

  /**< Handle used to access the I2C bus. */
  sns_ddf_handle_t port_handle;

  /**< sub device count.*/
  uint32_t sub_dev_cnt;

  /**< supported sub device array.*/
  stm_lsm6dsm_sub_dev_s sub_dev[LSM6DSM_MAX_SUB_DEV];

  /**< acc desired rate req by smgr*/
  int32_t acc_desired_rate_idx;
  sns_ddf_odr_t acc_desired_rate;

  /**< acc cur rate set*/
  int8_t acc_cur_rate_idx;

  /**< gyr desired rate req by smgr*/
  int32_t gyr_desired_rate_idx;
  sns_ddf_odr_t gyr_desired_rate;

  /**< gyr cur rate set*/
  int8_t gyr_cur_rate_idx;

  /**< temp sensor desired sampling frequency with acc primary */
  sns_ddf_odr_t a_temp_rate;

  /**< temp sensor desired sampling frequency with gyr primary */
  sns_ddf_odr_t g_temp_rate;

  /**< Current range selection.*/
  int8_t acc_range_idx;

  /**< Current range selection.*/
  int8_t gyr_range_idx;

  /**< Current acc sensitivity. */
  stm_lsm6dsm_acc_sstvt acc_sstvt_adj;

  /**< Current gyro sensitivity. */
  q16_t  gyr_sstvt_adj;

  /**< the time when ODR > 0 is set */
  sns_ddf_time_t   acc_odr_ts;

  /**< the time when new ODR is settled */
  sns_ddf_time_t   acc_odr_settled_ts;

  /**< the time when new ODR is settled */
  sns_ddf_time_t   gyr_odr_settled_ts;

  /**< Device-to-phone axis mapping. */
  sns_ddf_axes_map_s axes_map;

  bool axes_mapped;

  /**< gyro sleep mode */
  bool gyr_sleep;

  /**< Timer structure. */
  stm_lsm6dsm_timer md_timer;

  /**< Timer structure. */
  stm_lsm6dsm_timer g_timer;

  /**< Timer structure. */
  sns_ddf_timer_s temp_timer;
  /** GPIO number used for interrupts */
  uint32_t gpio_num;

  /** INT registered or not*/
  bool int_registered;

  /** LSM6DSM  zero-xl biases after inertial SW self test and calibration */
  q16_t xl_biases[STM_LSM6DSM_AXES_PER_SENSOR];

  /** LSM6DSM  zero-g biases after inertial SW self test and calibration */
  q16_t g_biases[STM_LSM6DSM_AXES_PER_SENSOR];


  /** Motion detection enabled or not*/
  bool md_enabled;

  /** Motion detection desired*/
  bool md_desired;


  /** fifo details*/
  stm_lsm6dsm_fifo_info_s fifo_info;

  /** LSM6DSM data intp*/
  stm_lsm6dsm_data_intp_t data_intp;

  /** LSM6DSM esp info */
  stm_lsm6dsm_esp_info_s esp_info;

  /** LSM6DSM hub info */
  stm_lsm6dsm_hub_info_s hub_info;

  /** Enable/Disable high performance mode */
  bool acc_lp_mode;
  bool acc_st_active;

  /** LSM6DSM s4s config*/
  stm_lsm6dsm_s4s_config_s s4s_config;

  /** Device select field */
  uint8_t device_select;
} sns_dd_lsm6dsm_state_t;

/**
 * Accelerometer LSM6DSM SW inertial self test settings
 */
#define STM_LSM6DSM_SWST_TPL_BIAS   40      //Unit: mg

#define STM_LSM6DSM_ACC_SWST_MAX_BIAS1  180     //Unit: mg
#define STM_LSM6DSM_ACC_SWST_MAX_BIAS2  210     //Unit: mg


/**
 * Accelerometer LSM6DSM hardware self test settings
 */
#define STM_LSM6DSM_ST_2G_MIN       90      //Unit: mg
#define STM_LSM6DSM_ST_2G_MAX       1700    //Unit: mg

/**
 * LSM6DSM GYR SW inertial self test settings
 */
#define STM_LSM6DSM_GYR_SWST_MAX_BIAS   40     //Unit: dps

/**
 * Gyroscope LSM6DSM self test settings
 */
#define STM_LSM6DSM_2000DPS_ST_MIN      150*1000  //unit milli-dps.
#define STM_LSM6DSM_2000DPS_ST_MAX      700*1000




/**
 * Gyroscope LSM6DSM fifo self test
 */
#define STM_LSM6DS_G_ST_FIFO_DEPTH 128

/**
 * Functions used across the driver
 */
sns_ddf_status_e sns_dd_lsm6dsm_init(
    sns_ddf_handle_t* dd_handle_ptr,
    sns_ddf_handle_t smgr_handle,
    sns_ddf_nv_params_s* nv_params,
    sns_ddf_device_access_s device_info[],
    uint32_t num_devices,
    sns_ddf_memhandler_s* memhandler,
    sns_ddf_sensor_e* sensors[],
    uint32_t* num_sensors);

sns_ddf_status_e sns_dd_lsm6dsm_set_attr(
    sns_ddf_handle_t dd_handle,
    sns_ddf_sensor_e sensor,
    sns_ddf_attribute_e attrib,
    void* value);

sns_ddf_status_e sns_dd_lsm6dsm_get_attr(
    sns_ddf_handle_t dd_handle,
    sns_ddf_sensor_e sensor,
    sns_ddf_attribute_e attrib,
    sns_ddf_memhandler_s* memhandler,
    void** value,
    uint32_t* num_elems);

sns_ddf_status_e sns_dd_lsm6dsm_reset(sns_ddf_handle_t dd_handle);

sns_ddf_status_e sns_dd_lsm6dsm_run_test(
    sns_ddf_handle_t  dd_handle,
    sns_ddf_sensor_e  sensor,
    sns_ddf_test_e    test,
    uint32_t*         err);

sns_ddf_status_e sns_dd_lsm6dsm_probe(
    sns_ddf_device_access_s* device_info,
    sns_ddf_memhandler_s*    memhandler,
    uint32_t*                num_sensors,
    sns_ddf_sensor_e**       sensors );

sns_ddf_status_e sns_dd_lsm6dsm_trigger_fifo(
    sns_ddf_handle_t dd_handle,
    sns_ddf_sensor_e sensor,
    uint16_t num_samples,
    bool trigger_now);

sns_ddf_status_e sns_dd_lsm6dsm_write_reg(
    sns_ddf_handle_t dd_handle,
    uint8_t reg_addr,
    uint8_t* reg_value,
    uint8_t size,
    uint8_t mask);

sns_ddf_status_e  sns_dd_lsm6dsm_match_odr(
    sns_ddf_handle_t dd_handle,
    sns_ddf_odr_t desired_rate,
    sns_ddf_odr_t *new_rate,
    int8_t *new_index);

sns_ddf_status_e sns_dd_acc_lsm6dsm_set_datarate(
    sns_ddf_handle_t dd_handle,
    int8_t rate_idx);

sns_ddf_status_e sns_dd_gyr_lsm6dsm_set_datarate(
    sns_ddf_handle_t dd_handle,
    int8_t rate_idx,
    bool sleep_mode);

sns_ddf_status_e sns_dd_fifo_lsm6dsm_set_datarate(
    sns_ddf_handle_t dd_handle,
    int8_t rate_idx);

sns_ddf_status_e lsm6dsm_search_subdev_by_sensortype (
    sns_dd_lsm6dsm_state_t* state,
    sns_ddf_sensor_e sensor,
    uint32_t *sub_dev_inx);

sns_ddf_status_e sns_dd_gyr_lsm6dsm_set_power(
    sns_ddf_handle_t dd_handle,
    sns_ddf_powerstate_e power_state);
sns_ddf_status_e sns_dd_gyr_lsm6dsm_set_range(
    sns_ddf_handle_t dd_handle,
    int8_t range_idx);
sns_ddf_status_e sns_dd_acc_lsm6dsm_set_power(
    sns_ddf_handle_t dd_handle,
    sns_ddf_powerstate_e power_state);
sns_ddf_status_e sns_dd_acc_lsm6dsm_set_range(
    sns_ddf_handle_t dd_handle,
    int8_t range_idx);
sns_ddf_status_e sns_dd_lsm6dsm_update_rate(
    sns_ddf_handle_t dd_handle,
    sns_ddf_sensor_e sensor,
    int8_t new_rate_idx);
sns_ddf_status_e sns_dd_lsm6dsm_sched_data(
    sns_ddf_handle_t  dd_handle,
    sns_ddf_sensor_e  sensor,
    bool              enable);

sns_ddf_status_e sns_dd_lsm6dsm_enable_fifo_int(
    sns_ddf_handle_t dd_handle,
    sns_ddf_sensor_e sensor);
sns_ddf_status_e sns_dd_lsm6dsm_disable_fifo_int(
    sns_ddf_handle_t dd_handle,
    sns_ddf_sensor_e sensor);
sns_ddf_status_e sns_dd_lsm6dsm_disable_fifo(
    sns_ddf_handle_t dd_handle,
    sns_ddf_sensor_e sensor);
sns_ddf_status_e sns_dd_lsm6dsm_enable_fifo(
    sns_ddf_handle_t dd_handle,
    uint16_t watermark,
    sns_ddf_sensor_e sensor);

void sns_dd_lsm6dsm_handle_fifo_int(
    sns_ddf_handle_t  dd_handle,
    sns_ddf_time_t    timestamp,
    bool* run_again);

sns_ddf_status_e sns_dd_lsm6dsm_flush_fifo(
    sns_ddf_handle_t  dd_handle,
    uint32_t num_samples,
    bool fifo_reset);

sns_ddf_status_e sns_dd_lsm6dsm_temp_set_rate(sns_ddf_handle_t dd_handle,
    uint8_t value);
sns_ddf_status_e sns_dd_lsm6dsm_send_event_smgr(
    sns_ddf_handle_t dd_handle,
    sns_ddf_sensor_e sensor,
    sns_ddf_event_e event);

void sns_dd_lsm6dsm_handle_selftest_timeout(
    sns_ddf_handle_t dd_handle,
    void* arg);

bool sns_dd_acc_lsm6dsm_is_active_other_sub_dev (
    sns_dd_lsm6dsm_state_t* state,
    uint32_t sub_dev_inx);

void sns_dd_lsm6dsm_convert_raw_data(
    sns_ddf_handle_t dd_handle,
    sns_ddf_sensor_e sensor,
    uint8_t* raw,
    q16_t* data);

sns_ddf_status_e sns_dd_lsm6dsm_start_streaming(
    sns_ddf_handle_t  dd_handle);

sns_ddf_status_e sns_dd_lsm6dsm_stop_streaming(
    sns_ddf_handle_t  dd_handle,
    bool flush);

sns_ddf_status_e sns_dd_lsm6dsm_alloc_buff(
    sns_ddf_handle_t dd_handle,
    sns_ddf_sensor_e sensor,
    int32_t size);

sns_ddf_status_e sns_dd_lsm6dsm_free_buff(
    sns_ddf_handle_t dd_handle,
    sns_ddf_sensor_e sensor);

sns_ddf_status_e sns_dd_lsm6dsm_create_timer(sns_ddf_handle_t, stm_lsm6dsm_timer* , uint32_t, timer_msg_t, bool);
void sns_dd_lsm6dsm_destroy_timer(sns_ddf_handle_t, stm_lsm6dsm_timer*);
bool sns_dd_lsm6dsm_is_timer_valid(sns_ddf_handle_t, stm_lsm6dsm_timer*);

bool is_lsm6dsm_mdf_settled(sns_ddf_handle_t dd_handle, filter_t filter);
void lsm6dsm_enable_mdf(sns_ddf_handle_t dd_handle, filter_t filter);

sns_ddf_status_e sns_dd_lsm6dsm_enable_md(
    sns_ddf_handle_t dd_handle);

sns_ddf_status_e sns_dd_lsm6dsm_disable_md(
    sns_ddf_handle_t dd_handle);
sns_dd_lsm6dsm_state_t* sns_dd_lsm6dsm_get_state(sns_ddf_handle_t dd_handle);

int8_t sns_dd_lsm6dsm_get_acc_rate(sns_ddf_handle_t dd_handle);
sns_ddf_status_e sns_dd_lsm6dsm_sharedFifo_info(sns_ddf_handle_t dd_handle, sns_ddf_sensor_e sensor,
    sns_ddf_fifo_share_sensor_s* shared_sensors_info,
    uint8_t* s_shared_cnt);
sns_ddf_status_e sns_dd_lsm6dsm_set_fifo_wmk(
    sns_ddf_handle_t dd_handle,
    uint16_t watermark);
#if STM_LSM6DSM_LOGDATA
void sns_dd_lsm6dsm_log_data(sns_ddf_sensor_data_s *data_ptr, bool fifo_mode);
#endif

#endif  /* __LSM6DSM__ */
