/*******************************************************************************
* Copyright (c) 2016, Capella Microsystems, Inc.
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*     1. Redistributions of source code must retain the above copyright
*      notice, this list of conditions and the following disclaimer.
*     2. Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimer in the
*       documentation and/or other materials provided with the distribution.
*     3. Neither the name of Capella Microsystems, Inc. nor the
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
  
/*==============================================================================

EDIT HISTORY FOR FILE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.

when         who     what, where, why
----------   ---     -----------------------------------------------------------
04/12/2016   JH      Porting from dd_vendor_1.h
==============================================================================*/

#ifndef _SNS_DD_CM3526_H
#define _SNS_DD_CM3526_H

#include "fixed_point.h"
#include "sns_ddf_util.h"
#include "sns_ddf_attrib.h"
#include "sns_ddf_common.h"
#include "sns_ddf_comm.h"
#include "sns_ddf_driver_if.h"
#include "sns_ddf_smgr_if.h"
#include "sns_ddf_memhandler.h"
#include "sns_ddf_signal.h"
#include "sns_log_api_public.h"
#include "sns_log_types_public.h"


/*=======================================================================

INTERNAL DEFINITIONS

========================================================================*/

/* Enable this flag to enable uImage operation */
//#define CM3526_ENABLE_UIMG

#ifndef CM3526_ENABLE_UIMG
/* Define extended DDF uImage functions if missing in HD22 package */
#define sns_ddf_malloc_ex(ptr, size, smgr_handle)                               sns_ddf_malloc(ptr, size)
#define sns_ddf_mfree_ex(ptr, smgr_handle)                                      sns_ddf_mfree(ptr)
#define sns_ddf_memhandler_malloc_ex(memhandler, size, smgr_handle)             sns_ddf_memhandler_malloc(memhandler, size)
#define sns_ddf_smgr_is_in_uimage()     false
#endif

/* Enable this flag when compiling on OpenSSC HD22 builds */
//#define CM3526_COMPILE_FOR_HD22

#ifdef CM3526_COMPILE_FOR_HD22
#define CM3526_LOG_PACKET SNS_LOG_CONVERTED_SENSOR_DATA_PUBLIC
sns_ddf_driver_if_s sns_dd_vendor_if_1;
#define CM3526_DD_IF sns_dd_vendor_if_1
#else
#define CM3526_LOG_PACKET SNS_LOG_CONVERTED_SENSOR_DATA
sns_ddf_driver_if_s sns_dd_cm3526_if;
#define CM3526_DD_IF sns_dd_cm3526_if
#endif


// Enable the following macro to see debug out 
//#define DD_CM3526_DEBUG



#ifdef DD_CM3526_DEBUG
#if defined QDSP6
#ifdef CM3526_COMPILE_FOR_HD22
#include "qurt_elite_diag.h"
#define DBG_MEDIUM_PRIO DBG_MED_PRIO
#define CM3526_DEBUG_MSG_0(level,msg)          UMSG(MSG_SSID_QDSP6,DBG_##level##_PRIO, "CM3526 - " msg)
#define CM3526_DEBUG_MSG_1(level,msg,p1)       UMSG_1(MSG_SSID_QDSP6,DBG_##level##_PRIO, "CM3526 - " msg,p1)
#define CM3526_DEBUG_MSG_2(level,msg,p1,p2)    UMSG_2(MSG_SSID_QDSP6,DBG_##level##_PRIO, "CM3526 - " msg,p1,p2)
#define CM3526_DEBUG_MSG_3(level,msg,p1,p2,p3) UMSG_3(MSG_SSID_QDSP6,DBG_##level##_PRIO, "CM3526 - " msg,p1,p2,p3)
#else
#define DBG_MEDIUM_PRIO DBG_MED_PRIO
#define CM3526_DEBUG_MSG_0(level,msg)          UMSG(MSG_SSID_SNS,DBG_##level##_PRIO, " " msg)
#define CM3526_DEBUG_MSG_1(level,msg,p1)       UMSG_1(MSG_SSID_SNS,DBG_##level##_PRIO, " " msg,p1)
#define CM3526_DEBUG_MSG_2(level,msg,p1,p2)    UMSG_2(MSG_SSID_SNS,DBG_##level##_PRIO, " " msg,p1,p2)
#define CM3526_DEBUG_MSG_3(level,msg,p1,p2,p3) UMSG_3(MSG_SSID_SNS,DBG_##level##_PRIO, " " msg,p1,p2,p3)
#endif /* End of CM3526_COMPILE_FOR_HD22*/
#else
#define MED MEDIUM
#include "sns_debug_str.h"
#define CM3526_DEBUG_MSG_0(level,msg)          SNS_PRINTF_STRING_ID_##level##_0(SNS_DBG_MOD_DSPS_SMGR,DBG_SMGR_GENERIC_STRING0)
#define CM3526_DEBUG_MSG_1(level,msg,p1)       SNS_PRINTF_STRING_ID_##level##_1(SNS_DBG_MOD_DSPS_SMGR,DBG_SMGR_GENERIC_STRING1,p1)
#define CM3526_DEBUG_MSG_2(level,msg,p1,p2)    SNS_PRINTF_STRING_ID_##level##_2(SNS_DBG_MOD_DSPS_SMGR,DBG_SMGR_GENERIC_STRING2,p1,p2)
#define CM3526_DEBUG_MSG_3(level,msg,p1,p2,p3) SNS_PRINTF_STRING_ID_##level##_3(SNS_DBG_MOD_DSPS_SMGR,DBG_SMGR_GENERIC_STRING3,p1,p2,p3)
#endif /* End of QDSP6 */
#else
#define CM3526_DEBUG_MSG_0(level,msg)
#define CM3526_DEBUG_MSG_1(level,msg,p1)
#define CM3526_DEBUG_MSG_2(level,msg,p1,p2)
#define CM3526_DEBUG_MSG_3(level,msg,p1,p2,p3)
#endif /* End of DD_CM3526_DEBUG */


/* Register Addresses define */
#define SNS_DD_CM3526_CONF_REG				0x00
#define SNS_DD_CM3526_UVA_DATA_REG			0x07
#define SNS_DD_CM3526_DUMMY_DATA_REG		0x08
#define	SNS_DD_CM3526_UVB_DATA_REG			0x09
#define	SNS_DD_CM3526_UVCOMP1_DATA_REG		0x0A
#define	SNS_DD_CM3526_UVCOMP2_DATA_REG		0x0B
#define	SNS_DD_CM3526_ID_REG				0x0C

/* Register Value define : CONF */
#define SNS_DD_CM3526_CONF_SD				0x01
#define SNS_DD_CM3526_CONF_UV_AF_AUTO		0x00
#define SNS_DD_CM3526_CONF_UV_AF_FORCE		0x02
#define SNS_DD_CM3526_CONF_UV_TRIG_NO		0x00
#define SNS_DD_CM3526_CONF_UV_TRIG_ONCE		0x04
#define SNS_DD_CM3526_CONF_HD				0x08
#define SNS_DD_CM3526_CONF_UV_IT_MASK		0x70
#define SNS_DD_CM3526_CONF_UV_IT_50MS		0x00
#define SNS_DD_CM3526_CONF_UV_IT_100MS		0x10
#define SNS_DD_CM3526_CONF_UV_IT_200MS		0x20
#define SNS_DD_CM3526_CONF_UV_IT_400MS		0x30
#define SNS_DD_CM3526_CONF_UV_IT_800MS		0x40
#define SNS_DD_CM3526_CONF_DEFAULT			(SNS_DD_CM3526_CONF_UV_AF_AUTO | SNS_DD_CM3526_CONF_UV_TRIG_NO | SNS_DD_CM3526_CONF_UV_IT_100MS)

/* CM3526 device ID */
#define CM3526_ID							0x26

/* Sensor SW configuration */ 
#define SNS_DD_CM3526_NUM_SENSOR_TYPES      1
#define SNS_DD_CM3526_NUM_REGS              1       /* number of config registers */

/* Sensor HW configuration */ 
/* attributes for light data type */
/* The res and accuracy for ALS are not static values. They're calculated from the previous data */ 
#define SNS_DD_CM3526_RES                  FX_FLTTOFIX_Q16(0.1)
#define SNS_DD_CM3526_PWR                  480                     /* unit of uA */
#define SNS_DD_CM3526_LO_PWR               1                       /* unit of uA */
#define SNS_DD_CM3526_BITS                 16
#define SNS_DD_CM3526_FREQ                 5
#define SNS_DD_CM3526_UVS_ODR              5

/*=======================================================================

TYPE DEFINITIONS

========================================================================*/
/* State struct for driver */
typedef struct
{
	sns_ddf_handle_t         smgr_handle;                            /* SMGR handle */               
	sns_ddf_handle_t         port_handle;                            /* Port handle for bus access */
	sns_ddf_odr_t            uvs_odr;                                /* Sensor ODR setting */	
	uint16_t                 range;                                  /* range index */
	uint16_t                 regs[SNS_DD_CM3526_NUM_REGS];	
} sns_dd_cm3526_t;

/*=======================================================================

FUNCTION DEFINITIONS

========================================================================*/
sns_ddf_status_e sns_dd_cm3526_init
(
	sns_ddf_handle_t*        dd_handle_ptr,
	sns_ddf_handle_t         smgr_handle,
	sns_ddf_nv_params_s*     nv_params,
	sns_ddf_device_access_s  device_info[],
	uint32_t                 num_devices,
	sns_ddf_memhandler_s*    memhandler,
	sns_ddf_sensor_e*        sensors[],
	uint32_t*                num_sensors
);

sns_ddf_status_e sns_dd_cm3526_get_data
(
	sns_ddf_handle_t        dd_handle,
	sns_ddf_sensor_e        sensors[],
	uint32_t                num_sensors,
	sns_ddf_memhandler_s*   memhandler,
	sns_ddf_sensor_data_s*  data[]
);

sns_ddf_status_e sns_dd_cm3526_set_attrib
(
	sns_ddf_handle_t     dd_handle,
	sns_ddf_sensor_e     sensor,
	sns_ddf_attribute_e  attrib,
	void*                value
);

sns_ddf_status_e sns_dd_cm3526_get_attrib
(
	sns_ddf_handle_t     dd_handle,
	sns_ddf_sensor_e     sensor,
	sns_ddf_attribute_e  attrib,
	sns_ddf_memhandler_s* memhandler,
	void**               value,
	uint32_t*            num_elems
);

void sns_dd_cm3526_handle_timer 
(
	sns_ddf_handle_t dd_handle, 
	void* arg
);

void sns_dd_cm3526_handle_irq
(
	sns_ddf_handle_t dd_handle, 
	uint32_t          gpio_num,
	sns_ddf_time_t    timestamp
);

sns_ddf_status_e sns_dd_cm3526_reset
(
	sns_ddf_handle_t dd_handle
);

sns_ddf_status_e sns_dd_cm3526_enable_sched_data
(
	sns_ddf_handle_t  handle,
	sns_ddf_sensor_e  sensor,
	bool              enable
);

sns_ddf_status_e sns_dd_cm3526_run_test
(
	sns_ddf_handle_t  dd_handle,
	sns_ddf_sensor_e  sensor,
	sns_ddf_test_e    test,
	uint32_t*         err
);

sns_ddf_status_e sns_dd_cm3526_probe
(
	sns_ddf_device_access_s* device_info,
	sns_ddf_memhandler_s*    memhandler,
	uint32_t*                num_sensors,
	sns_ddf_sensor_e**       sensors
);

sns_ddf_status_e sns_dd_cm3526_reg_write
(
	sns_ddf_handle_t         port_handle,
	uint8_t                  reg,
	uint16_t                 value
);

sns_ddf_status_e sns_dd_cm3526_reg_read
(
	sns_ddf_handle_t         port_handle,
	uint8_t                  reg,
	uint16_t*                pvalue
);

#endif /* End include guard  _SNS_DD_CM3526_H */

