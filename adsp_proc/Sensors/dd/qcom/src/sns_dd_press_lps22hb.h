/******************** (C) COPYRIGHT 2016 STMicroelectronics ********************
*
* File Name         : sns_dd_lps22hb.h
* Authors           : Wei Wang
* Version           : V 1.3.0
* Description       : LPS22HB pressure sensor driver header file
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

#ifndef __LPS22HB__
#define __LPS22HB__

#include <stdio.h>
#include "sns_ddf_attrib.h"
#include "sns_ddf_comm.h"
#include "sns_ddf_common.h"
#include "sns_ddf_driver_if.h"
#include "sns_ddf_memhandler.h"
#include "sns_ddf_smgr_if.h"
#include "sns_ddf_util.h"
#include "sns_ddf_signal.h"

//#define BUILD_DRAGON_BOARD      // Enable this flag to build in HD22 build
#define BUILD_UIMAGE
//#define BUILD_DEBUG_LOG

#if defined(BUILD_DRAGON_BOARD)
#   include "sns_log_types_public.h"
#   include "sns_log_api_public.h"
#   define SNS_LOG_CONVERTED_SENSOR_DATA    SNS_LOG_CONVERTED_SENSOR_DATA_PUBLIC
#   include "qurt_elite_diag.h"
#   define sns_dd_press_lps22hb_if    sns_dd_vendor_if_1
#   if defined(BUILD_DEBUG_LOG) && !defined(BUILD_UIMAGE)
#       define DD_MSG_0(level,msg)             MSG(MSG_SSID_QDSP6,DBG_##level##_PRIO, "LPS22HB-"msg)
#       define DD_MSG_1(level,msg,p1)          MSG_1(MSG_SSID_QDSP6,DBG_##level##_PRIO, "LPS22HB-"msg,p1)
#       define DD_MSG_2(level,msg,p1,p2)       MSG_2(MSG_SSID_QDSP6,DBG_##level##_PRIO, "LPS22HB-"msg,p1,p2)
#       define DD_MSG_3(level,msg,p1,p2,p3)    MSG_3(MSG_SSID_QDSP6,DBG_##level##_PRIO, "LPS22HB-"msg,p1,p2,p3)
#       define DD_MSG_4(level,msg,p1,p2,p3,p4) MSG_4(MSG_SSID_QDSP6,DBG_##level##_PRIO, "LPS22HB-"msg,p1,p2,p3,p4)
#       define DD_MSG_5(level,msg,p1,p2,p3,p4,p5)       MSG_5(MSG_SSID_QDSP6,DBG_##level##_PRIO, "LPS22HB-"msg,p1,p2,p3,p4,p5)
#       define DD_MSG_6(level,msg,p1,p2,p3,p4,p5,p6)    MSG_6(MSG_SSID_QDSP6,DBG_##level##_PRIO, "LPS22HB-"msg,p1,p2,p3,p4,p5,p6)
#   elif defined(BUILD_DEBUG_LOG) && defined(BUILD_UIMAGE)
#       define DD_MSG_0(level,msg)             UMSG(MSG_SSID_QDSP6,DBG_##level##_PRIO, "LPS22HB-"msg)
#       define DD_MSG_1(level,msg,p1)          UMSG_1(MSG_SSID_QDSP6,DBG_##level##_PRIO, "LPS22HB-"msg,p1)
#       define DD_MSG_2(level,msg,p1,p2)       UMSG_2(MSG_SSID_QDSP6,DBG_##level##_PRIO, "LPS22HB-"msg,p1,p2)
#       define DD_MSG_3(level,msg,p1,p2,p3)    UMSG_3(MSG_SSID_QDSP6,DBG_##level##_PRIO, "LPS22HB-"msg,p1,p2,p3)
#       define DD_MSG_4(level,msg,p1,p2,p3,p4) UMSG_4(MSG_SSID_QDSP6,DBG_##level##_PRIO, "LPS22HB-"msg,p1,p2,p3,p4)
#       define DD_MSG_5(level,msg,p1,p2,p3,p4,p5)       UMSG_5(MSG_SSID_QDSP6,DBG_##level##_PRIO, "LPS22HB-"msg,p1,p2,p3,p4,p5)
#       define DD_MSG_6(level,msg,p1,p2,p3,p4,p5,p6)    UMSG_6(MSG_SSID_QDSP6,DBG_##level##_PRIO, "LPS22HB-"msg,p1,p2,p3,p4,p5,p6)
#   else
#       define DD_MSG_0(level,msg)
#       define DD_MSG_1(level,msg,p1)
#       define DD_MSG_2(level,msg,p1,p2)
#       define DD_MSG_3(level,msg,p1,p2,p3)
#       define DD_MSG_4(level,msg,p1,p2,p3,p4)
#       define DD_MSG_5(level,msg,p1,p2,p3,p4,p5)
#       define DD_MSG_6(level,msg,p1,p2,p3,p4,p5,p6)
#   endif
#else    // Regular Builds
#   include "log_codes.h"
#   include "sns_log_types.h"
#   include "sns_log_api.h"
#   if defined(BUILD_DEBUG_LOG) && !defined(BUILD_UIMAGE)
#       define DD_MSG_0(level,msg)             MSG(MSG_SSID_SNS,DBG_##level##_PRIO, "LPS22HB-"msg)
#       define DD_MSG_1(level,msg,p1)          MSG_1(MSG_SSID_SNS,DBG_##level##_PRIO, "LPS22HB-"msg,p1)
#       define DD_MSG_2(level,msg,p1,p2)       MSG_2(MSG_SSID_SNS,DBG_##level##_PRIO, "LPS22HB-"msg,p1,p2)
#       define DD_MSG_3(level,msg,p1,p2,p3)    MSG_3(MSG_SSID_SNS,DBG_##level##_PRIO, "LPS22HB-"msg,p1,p2,p3)
#       define DD_MSG_4(level,msg,p1,p2,p3,p4) MSG_4(MSG_SSID_SNS,DBG_##level##_PRIO, "LPS22HB-"msg,p1,p2,p3,p4)
#       define DD_MSG_5(level,msg,p1,p2,p3,p4,p5)       MSG_5(MSG_SSID_SNS,DBG_##level##_PRIO, "LPS22HB-"msg,p1,p2,p3,p4,p5)
#       define DD_MSG_6(level,msg,p1,p2,p3,p4,p5,p6)    MSG_6(MSG_SSID_SNS,DBG_##level##_PRIO, "LPS22HB-"msg,p1,p2,p3,p4,p5,p6)
#   elif defined(BUILD_DEBUG_LOG) && defined(BUILD_UIMAGE)
#       define DD_MSG_0(level,msg)             UMSG(MSG_SSID_SNS,DBG_##level##_PRIO, "LPS22HB-"msg)
#       define DD_MSG_1(level,msg,p1)          UMSG_1(MSG_SSID_SNS,DBG_##level##_PRIO, "LPS22HB-"msg,p1)
#       define DD_MSG_2(level,msg,p1,p2)       UMSG_2(MSG_SSID_SNS,DBG_##level##_PRIO, "LPS22HB-"msg,p1,p2)
#       define DD_MSG_3(level,msg,p1,p2,p3)    UMSG_3(MSG_SSID_SNS,DBG_##level##_PRIO, "LPS22HB-"msg,p1,p2,p3)
#       define DD_MSG_4(level,msg,p1,p2,p3,p4) UMSG_4(MSG_SSID_SNS,DBG_##level##_PRIO, "LPS22HB-"msg,p1,p2,p3,p4)
#       define DD_MSG_5(level,msg,p1,p2,p3,p4,p5)       UMSG_5(MSG_SSID_SNS,DBG_##level##_PRIO, "LPS22HB-"msg,p1,p2,p3,p4,p5)
#       define DD_MSG_6(level,msg,p1,p2,p3,p4,p5,p6)    UMSG_6(MSG_SSID_SNS,DBG_##level##_PRIO, "LPS22HB-"msg,p1,p2,p3,p4,p5,p6)
#   else
#       define DD_MSG_0(level,msg)
#       define DD_MSG_1(level,msg,p1)
#       define DD_MSG_2(level,msg,p1,p2)
#       define DD_MSG_3(level,msg,p1,p2,p3)
#       define DD_MSG_4(level,msg,p1,p2,p3,p4)
#       define DD_MSG_5(level,msg,p1,p2,p3,p4,p5)
#       define DD_MSG_6(level,msg,p1,p2,p3,p4,p5,p6)
#   endif
#endif

#define LPS22HB_PRESS_RANGE_MIN FX_CONV_Q16(260,0)
#define LPS22HB_PRESS_RANGE_MAX	FX_CONV_Q16(1260,0)
#define LPS22HB_TEMP_RANGE_MIN	FX_CONV_Q16(0,0)
#define LPS22HB_TEMP_RANGE_MAX	FX_CONV_Q16(65,0)

#define LPS22HB_MAX_RES_PRESS   FX_FLTTOFIX_Q16(0.0002)	// 4096lsb/hPa
#define LPS22HB_MAX_RES_TEMP    FX_FLTTOFIX_Q16(0.01)	// 100lsb/C

#define LPS22HB_ODR_NUM         5
#define LPS22HB_MAX_ODR_Hz      30

// Self Test Range. Assume test in normal room condition.
#define LPS22HB_PRESS_ST_MIN    FX_CONV_Q16(260,0)
#define LPS22HB_PRESS_ST_MAX    FX_CONV_Q16(1260,0)
#define LPS22HB_TEMP_ST_MIN     FX_CONV_Q16(0,0)
#define LPS22HB_TEMP_ST_MAX     FX_CONV_Q16(65,0)

#define LPS22HB_TIMER_Idle		0
#define LPS22HB_TIMER_SelfTest	1
#define LPS22HB_TIMER_Startup	2

/**
 * Pressure sensor LPS22HB I2C address
 */
#define LPS22HB_I2C_ADDR        0x5D
#define LPS22HB_NUM_BYTES_PRESS 3
#define LPS22HB_NUM_BYTES_TEMP  2

/**
 * Pressure sensor LPS22HB WHO AM I register
 */
#define LPS22HB_WHOAMI_VALUE    0xB1

/**
 * Pressure sensor LPS22HB register addresses
 */
#define LPS22HB_INTERRUPT_CFG   0x0B
#define LPS22HB_THS_P_L         0x0C
#define LPS22HB_THS_P_H         0x0D
#define LPS22HB_WHO_AM_I        0x0F    //ro, =0xB1
#define LPS22HB_CTRL_REG1       0x10
#define LPS22HB_CTRL_REG2       0x11
#define LPS22HB_CTRL_REG3       0x12
#define LPS22HB_FIFO_CTRL       0x14
#define LPS22HB_REF_P_XL        0x15
#define LPS22HB_REF_P_L         0x16
#define LPS22HB_REF_P_H         0x17
#define LPS22HB_RPDS_L          0x18
#define LPS22HB_RPDS_H          0x19
#define LPS22HB_RES_CONF        0x1A
#define LPS22HB_INT_SOURCE      0x25
#define LPS22HB_FIFO_STATUS     0x26
#define LPS22HB_STATUS_REG      0x27
#define LPS22HB_PRESS_OUT_XL    0x28
#define LPS22HB_PRESS_OUT_L     0x29
#define LPS22HB_PRESS_OUT_H     0x2A
#define LPS22HB_TEMP_OUT_L      0x2B
#define LPS22HB_TEMP_OUT_H      0x2C

#define STMERR_TEST_OK					0
#define STMERR_TEST_UNKNOWN				1
#define STMERR_TEST_BUS_ERROR			2
#define STMERR_TEST_SENSOR1_ST_FAIL		0x10
#define STMERR_TEST_SENSOR2_ST_FAIL		0x20

#define LPS22HB_DRVMODE_bPowerPress           0x01
#define LPS22HB_DRVMODE_bPowerTemp            0x02
#define LPS22HB_DRVMODE_bSchedulePress        0x04
#define LPS22HB_DRVMODE_bScheduleTemp         0x08
#define LPS22HB_DRVMODE_bPowerAll             0x03
#define LPS22HB_DRVMODE_bScheduleAll          0x0C

/**
 * Pressure sensor LPS22HB Driver State Information Structure
 */
typedef struct
{
    sns_ddf_handle_t smgr_handle;	// Handle used with sns_ddf_notify_data.
    sns_ddf_handle_t port_handle;	// Handle used to access the I2C bus.
    uint32_t gpio_num;				// GPIO number used for DRI.
    uint8_t ctrl_reg1;				// mirror register for LPS22HB CTRL_REG1
    uint8_t timer_type;				// Self-test status: 0 for disabled; 1 for enabled.
    uint8_t sensor_odr_code;
    uint8_t start_count;
    sns_ddf_odr_t dd_press_odr;     // Current driver data rate. 0Hz and physical sensor odr.
    sns_ddf_odr_t dd_temp_odr;
    sns_ddf_timer_s timer_obj;		// Timer object for self-test
    sns_ddf_time_t last_irq_timestamp;
    int32_t driver_mode;
} sns_dd_lps22hb_state_t;

//***** Private Functions *********************************************************
#define sns_dd_lps22hb_read_regs(reg_addr, reg_buf, count)    \
    ( (status=sns_ddf_read_port(state->port_handle, reg_addr, reg_buf, count, &rw_bytes)) \
    !=SNS_DDF_SUCCESS? status : (rw_bytes!=count)?SNS_DDF_EBUS:SNS_DDF_SUCCESS )

#define sns_dd_lps22hb_write_regs(reg_addr, reg_buf, count) \
    ( (status=sns_ddf_write_port(state->port_handle, reg_addr, reg_buf, count, &rw_bytes)) \
    !=SNS_DDF_SUCCESS? status : (rw_bytes!=count)?SNS_DDF_EBUS:SNS_DDF_SUCCESS )

#if !defined(BUILD_UIMAGE)
#   define 	sns_dd_malloc(ptr, size, smgr)		sns_ddf_malloc(ptr, size)
#   define	sns_dd_mfree(ptr, smgr) 			sns_ddf_mfree(ptr)
#   define 	sns_dd_memhandler_malloc(ptr, size, smgr) sns_ddf_memhandler_malloc(ptr, size)
#else
#   define 	sns_dd_malloc(ptr, size, smgr)		sns_ddf_malloc_ex(ptr, size, smgr)
#   define	sns_dd_mfree(ptr, smgr)			    sns_ddf_mfree_ex(ptr, smgr)
#   define 	sns_dd_memhandler_malloc(ptr, size, smgr) sns_ddf_memhandler_malloc_ex(ptr, size, smgr)
#endif

sns_ddf_status_e lps22hb_get_press(sns_dd_lps22hb_state_t* state, q16_t* press);
sns_ddf_status_e lps22hb_get_pt(sns_dd_lps22hb_state_t* state, q16_t* press, q16_t* tmpt);


//Extract integer and fractional part of q16_t variable.
#define Q16INT(a)       ((a)>>16)
#define Q16DEC2(a)      ((((a)>=0?(a):-(a))&0x0000FFFF)*100/65536)
#define Q16DEC3(a)      ((((a)>=0?(a):-(a))&0x0000FFFF)*1000/65536)

#define TIMESTAMP_TICK_FREQ     32768


//***** Interface Functions ****************************************************************
sns_ddf_status_e sns_dd_lps22hb_reset(
    sns_ddf_handle_t dd_handle);

sns_ddf_status_e sns_dd_lps22hb_init(
    sns_ddf_handle_t* dd_handle_ptr,
    sns_ddf_handle_t smgr_handle,
    sns_ddf_nv_params_s* nv_params,
    sns_ddf_device_access_s device_info[],
    uint32_t num_devices,
    sns_ddf_memhandler_s* memhandler,
    sns_ddf_sensor_e* sensors[],
    uint32_t* num_sensors);

sns_ddf_status_e sns_dd_lps22hb_get_attr(
    sns_ddf_handle_t dd_handle,
    sns_ddf_sensor_e sensor,
    sns_ddf_attribute_e attrib,
    sns_ddf_memhandler_s* memhandler,
    void** value,
    uint32_t* num_elems);

sns_ddf_status_e sns_dd_lps22hb_set_attr(
    sns_ddf_handle_t dd_handle,
    sns_ddf_sensor_e sensor,
    sns_ddf_attribute_e attrib,
    void* value);

void sns_dd_lps22hb_handle_timer(
    sns_ddf_handle_t dd_handle,
    void* arg);

void sns_dd_lps22hb_handle_irq(
    sns_ddf_handle_t  handle,
    uint32_t          gpio_num,
    sns_ddf_time_t    timestamp);

sns_ddf_status_e sns_dd_lps22hb_enable_sched_data(
    sns_ddf_handle_t  dd_handle,
    sns_ddf_sensor_e  sensor,
    bool              enable);

sns_ddf_status_e sns_dd_lps22hb_run_test(
    sns_ddf_handle_t    dd_handle,
    sns_ddf_sensor_e    sensor_type,
    sns_ddf_test_e      test,
    uint32_t*           err);

sns_ddf_status_e sns_dd_lps22hb_probe(
    sns_ddf_device_access_s* device_info,
    sns_ddf_memhandler_s*    memhandler,
    uint32_t*                num_sensors,
    sns_ddf_sensor_e**       sensors);

#endif  /* __LPS22HB__ */
