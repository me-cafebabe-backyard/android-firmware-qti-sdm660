/******************** (C) COPYRIGHT 2014 STMicroelectronics ********************
 *
 * File Name         : sns_dd_lis3mdl.h
 * Authors           : Karimuddin sayed
 *		               Wei Wang
 * Description       : Magnetometer driver for ST sensors with WHO_AM_I=0x3D.
 *
 ********************************************************************************
 * Copyright (c) 2014, STMicroelectronics.
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

#ifndef __MAG_LIS3MDL__
#define __MAG_LIS3MDL__

#include <stdio.h>
#include "sns_ddf_attrib.h"
#include "sns_ddf_comm.h"
#include "sns_ddf_common.h"
#include "sns_ddf_driver_if.h"
#include "sns_ddf_memhandler.h"
#include "sns_ddf_smgr_if.h"
#include "sns_ddf_util.h"
#include "sns_ddf_signal.h"


// driver configuration switches.
#ifdef SENSORS_DD_DEV_FLAG
#define BUILD_DRAGON_BOARD      // defined: build in HD22 build; undefined: build in customer build.
#endif // SENSORS_DD_DEV_FLAG
#define BUILD_UIMAGE            // defined: run driver in uImage mode; undefined: in big image mode.
//#define BUILD_DEBUG_LOG         // defined: enable debug message; undefined: disable debug message.
#define LSM303C_MAG             // defined: for LSM303C.Mag; undefined: for LIS3MDL.


#define DEVICE_NAME "LIS3MDL"

#if defined(BUILD_DRAGON_BOARD)
#   include "sns_log_types_public.h"
#   include "sns_log_api_public.h"
#   define SNS_LOG_CONVERTED_SENSOR_DATA    SNS_LOG_CONVERTED_SENSOR_DATA_PUBLIC
// Commenting out the line below to allow integration of this driver in HD22 builds
//#   define sns_dd_lis3mdl_if    sns_dd_vendor_if_1
#else    // Regular Builds
#   include "log_codes.h"
#   include "sns_log_types.h"
#   include "sns_log_api.h"
#endif

#if defined(BUILD_DEBUG_LOG) && !defined(BUILD_UIMAGE)
#   define LIS3MDL_MSG_0(level,msg)             MSG(MSG_SSID_QDSP6,DBG_##level##_PRIO, DEVICE_NAME"-"msg)
#   define LIS3MDL_MSG_1(level,msg,p1)          MSG_1(MSG_SSID_QDSP6,DBG_##level##_PRIO, DEVICE_NAME"-"msg,p1)
#   define LIS3MDL_MSG_2(level,msg,p1,p2)       MSG_2(MSG_SSID_QDSP6,DBG_##level##_PRIO, DEVICE_NAME"-"msg,p1,p2)
#   define LIS3MDL_MSG_3(level,msg,p1,p2,p3)    MSG_3(MSG_SSID_QDSP6,DBG_##level##_PRIO, DEVICE_NAME"-"msg,p1,p2,p3)
#   define LIS3MDL_MSG_4(level,msg,p1,p2,p3,p4) MSG_4(MSG_SSID_QDSP6,DBG_##level##_PRIO, DEVICE_NAME"-"msg,p1,p2,p3,p4)
#   define LIS3MDL_MSG_5(level,msg,p1,p2,p3,p4,p5)       MSG_5(MSG_SSID_QDSP6,DBG_##level##_PRIO, DEVICE_NAME"-"msg,p1,p2,p3,p4,p5)
#   define LIS3MDL_MSG_6(level,msg,p1,p2,p3,p4,p5,p6)    MSG_6(MSG_SSID_QDSP6,DBG_##level##_PRIO, DEVICE_NAME"-"msg,p1,p2,p3,p4,p5,p6)
#elif defined(BUILD_DEBUG_LOG) && defined(BUILD_UIMAGE)
#   define LIS3MDL_MSG_0(level,msg)             UMSG(MSG_SSID_QDSP6,DBG_##level##_PRIO, DEVICE_NAME"-"msg)
#   define LIS3MDL_MSG_1(level,msg,p1)          UMSG_1(MSG_SSID_QDSP6,DBG_##level##_PRIO, DEVICE_NAME"-"msg,p1)
#   define LIS3MDL_MSG_2(level,msg,p1,p2)       UMSG_2(MSG_SSID_QDSP6,DBG_##level##_PRIO, DEVICE_NAME"-"msg,p1,p2)
#   define LIS3MDL_MSG_3(level,msg,p1,p2,p3)    UMSG_3(MSG_SSID_QDSP6,DBG_##level##_PRIO, DEVICE_NAME"-"msg,p1,p2,p3)
#   define LIS3MDL_MSG_4(level,msg,p1,p2,p3,p4) UMSG_4(MSG_SSID_QDSP6,DBG_##level##_PRIO, DEVICE_NAME"-"msg,p1,p2,p3,p4)
#   define LIS3MDL_MSG_5(level,msg,p1,p2,p3,p4,p5)       UMSG_5(MSG_SSID_QDSP6,DBG_##level##_PRIO, DEVICE_NAME"-"msg,p1,p2,p3,p4,p5)
#   define LIS3MDL_MSG_6(level,msg,p1,p2,p3,p4,p5,p6)    UMSG_6(MSG_SSID_QDSP6,DBG_##level##_PRIO, DEVICE_NAME"-"msg,p1,p2,p3,p4,p5,p6)
#else
#   define LIS3MDL_MSG_0(level,msg)
#   define LIS3MDL_MSG_1(level,msg,p1)
#   define LIS3MDL_MSG_2(level,msg,p1,p2)
#   define LIS3MDL_MSG_3(level,msg,p1,p2,p3)
#   define LIS3MDL_MSG_4(level,msg,p1,p2,p3,p4)
#   define LIS3MDL_MSG_5(level,msg,p1,p2,p3,p4,p5)
#   define LIS3MDL_MSG_6(level,msg,p1,p2,p3,p4,p5,p6)
#endif

#define LIS3MDL_NUM_AXES        3
#define LIS3MDL_NUM_READ_BYTES  6
#define AUTO_INCREMENT          0x80

/* Address registers */
#define LIS3MDL_REG_WHOAMI      (0x0F)	/** Who am i address register */
#define LIS3MDL_REG_CNTRL1      (0x20)	/** CNTRL1 address register */
#define LIS3MDL_REG_CNTRL2      (0x21)	/** CNTRL2 address register */
#define LIS3MDL_REG_CNTRL3      (0x22)	/** CNTRL3 address register */
#define LIS3MDL_REG_CNTRL4      (0x23)	/** CNTRL4 address register */
#define LIS3MDL_REG_CNTRL5      (0x24)	/** CNTRL5 address register */
#define LIS3MDL_OUT_X_L	        (0x28)	/** data low address register */

#define LIS3MDL_WHO_AM_I        0x3d    // Who Am I default value
#define LIS3MDL_ODR_NUM         8
#define LIS3MDL_DEFAULT_ODR_IDX 5	// 20Hz
#define LIS3MDL_MAX_ODR_Hz		80

/**
 * Magnetometer MAG_LIS3MDL data bit length
 */
#define LIS3MDL_SENSOR_BIT_LEN  16

/**
 * Magnetometer MAG_LIS3MDL Driver State Information Structure
 */
typedef struct
{
    sns_ddf_handle_t smgr_handle;   // Handle used with sns_ddf_notify_data.
    sns_ddf_handle_t port_handle;   // Handle used to access the I2C bus.
    uint32_t gpio_num;              // GPIO number used for DRI.
    q16_t sstvt;                    // current sensitivity.
    uint8_t ctrl_reg1;              // mirror register for LIS3MDL.CtrlReg1
    sns_ddf_odr_t dd_mag_odr;       // in addition to physical ODR, current_dd_odr can be 0Hz.
    uint8_t current_range_idx;
    int enable_sched_data;
    sns_ddf_powerstate_e power_state;   // Current power state: ACTIVE or LOWPOWER.
    sns_ddf_axes_map_s axes_map;    // Device-to-phone axis mapping.
    bool self_test_enable;          // Self-test status: 0 for disabled; 1 for enabled.
    sns_ddf_timer_s timer_obj;      // Timer object for self-test.
    sns_ddf_time_t last_irq_timestamp;
} sns_dd_lis3mdl_state_t;

#define sns_dd_lis3mdl_read_regs(reg_addr, reg_buf, count) \
    ( (status=sns_ddf_read_port(state->port_handle, reg_addr, reg_buf, count, &rw_bytes)) \
    !=SNS_DDF_SUCCESS? status : (rw_bytes!=count)?SNS_DDF_EBUS:SNS_DDF_SUCCESS )

#define sns_dd_lis3mdl_write_regs(reg_addr, reg_buf, count) \
    ( (status=sns_ddf_write_port(state->port_handle, reg_addr, reg_buf, count, &rw_bytes)) \
    !=SNS_DDF_SUCCESS? status : (rw_bytes!=count)?SNS_DDF_EBUS:SNS_DDF_SUCCESS )

#define TIMESTAMP_TICK_FREQ     32768

#ifndef BUILD_UIMAGE
#define 	sns_dd_malloc(ptr, size, smgr)				sns_ddf_malloc(ptr, size)
#define		sns_dd_mfree(ptr, smgr) 					sns_ddf_mfree(ptr)
#define 	sns_dd_memhandler_malloc(ptr, size, smgr)	sns_ddf_memhandler_malloc(ptr, size)
#else
#define 	sns_dd_malloc(ptr, size, smgr)				sns_ddf_malloc_ex(ptr, size, smgr)
#define		sns_dd_mfree(ptr, smgr)						sns_ddf_mfree_ex(ptr, smgr)
#define 	sns_dd_memhandler_malloc(ptr, size, smgr) 	sns_ddf_memhandler_malloc_ex(ptr, size, smgr)
#endif

#define STMERR_TEST_OK                          0
#define STMERR_TEST_UNKNOWN                     1
#define STMERR_TEST_BUS_ERROR                   2
#define STMERR_TEST_SENSOR1_ST_FAIL             0x10
#define STMERR_TEST_SENSOR2_ST_FAIL             0x20

//***** Interface Functions ****************************************************************
sns_ddf_status_e sns_dd_lis3mdl_reset(
    sns_ddf_handle_t dd_handle);

sns_ddf_status_e sns_dd_lis3mdl_init(
    sns_ddf_handle_t* dd_handle_ptr,
    sns_ddf_handle_t smgr_handle,
    sns_ddf_nv_params_s* nv_params,
    sns_ddf_device_access_s device_info[],
    uint32_t num_devices,
    sns_ddf_memhandler_s* memhandler,
    sns_ddf_sensor_e* sensors[],
    uint32_t* num_sensors);

sns_ddf_status_e sns_dd_lis3mdl_get_attr(
    sns_ddf_handle_t dd_handle,
    sns_ddf_sensor_e sensor,
    sns_ddf_attribute_e attrib,
    sns_ddf_memhandler_s* memhandler,
    void** value,
    uint32_t* num_elems);

sns_ddf_status_e sns_dd_lis3mdl_set_attr(
    sns_ddf_handle_t dd_handle,
    sns_ddf_sensor_e sensor,
    sns_ddf_attribute_e attrib,
    void* value);

sns_ddf_status_e sns_dd_lis3mdl_enable_sched_data(
    sns_ddf_handle_t  dd_handle,
    sns_ddf_sensor_e  sensor,
    bool              enable);

sns_ddf_status_e sns_dd_lis3mdl_run_test(
    sns_ddf_handle_t    dd_handle,
    sns_ddf_sensor_e    sensor_type,
    sns_ddf_test_e      test,
    uint32_t*           err);

void sns_dd_lis3mdl_handle_timer(
    sns_ddf_handle_t dd_handle,
    void* arg);

sns_ddf_status_e sns_dd_lis3mdl_probe(
    sns_ddf_device_access_s* device_info,
    sns_ddf_memhandler_s*    memhandler,
    uint32_t*                num_sensors,
    sns_ddf_sensor_e**       sensors);


#endif  /* __MAG_LIS3MDL__ */
