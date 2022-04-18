/*
 * Copyright (c) 2016, ams AG
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/*
ams_tmx490x_qcom_hd22_Build_17  Mon May 16 16:53:46 CDT 2016
GitHash                                   FileName
7823d9348d179d4063fe78e9e1b8bba5abf9c005  ./ams_tmx490x_qcom_hd22/sensor_def_qcomdev.conf
24eac85329886ce82627a54da2d81614c076976a  ./ams_tmx490x_qcom_hd22/src/dd_ams_uimg.c
cee780370eb22b17f687d78123b4575fb8205b88  ./ams_tmx490x_qcom_hd22/src/algorithm_als/src/ams_als_API_process.c
cee780370eb22b17f687d78123b4575fb8205b88  ./ams_tmx490x_qcom_hd22/src/algorithm_als/src/ams_als_API_config.c
cee780370eb22b17f687d78123b4575fb8205b88  ./ams_tmx490x_qcom_hd22/src/algorithm_als/src/ams_als_API_init.c
cee780370eb22b17f687d78123b4575fb8205b88  ./ams_tmx490x_qcom_hd22/src/algorithm_als/src/ams_als_API_result.c
cee780370eb22b17f687d78123b4575fb8205b88  ./ams_tmx490x_qcom_hd22/src/algorithm_als/src/ams_als_API_info.c
cee780370eb22b17f687d78123b4575fb8205b88  ./ams_tmx490x_qcom_hd22/src/algorithm_als/src/ams_als_core.c
cee780370eb22b17f687d78123b4575fb8205b88  ./ams_tmx490x_qcom_hd22/src/algorithm_als/include/ams_als_core.h
cee780370eb22b17f687d78123b4575fb8205b88  ./ams_tmx490x_qcom_hd22/src/algorithm_als/include/ams_als_API.h
cee780370eb22b17f687d78123b4575fb8205b88  ./ams_tmx490x_qcom_hd22/src/algorithm_als/include/ams_als_callibration.h
24eac85329886ce82627a54da2d81614c076976a  ./ams_tmx490x_qcom_hd22/src/dd_ams_ext.c
0943d97e723a716129efe0aad203025bdebfbecb  ./ams_tmx490x_qcom_hd22/src/algorithm_gesture/src/ams_gesture_API_config.c
0943d97e723a716129efe0aad203025bdebfbecb  ./ams_tmx490x_qcom_hd22/src/algorithm_gesture/src/ams_gesture_API_init.c
0943d97e723a716129efe0aad203025bdebfbecb  ./ams_tmx490x_qcom_hd22/src/algorithm_gesture/src/ams_gesture_API_result.c
0943d97e723a716129efe0aad203025bdebfbecb  ./ams_tmx490x_qcom_hd22/src/algorithm_gesture/src/ams_gesture_API_process.c
0943d97e723a716129efe0aad203025bdebfbecb  ./ams_tmx490x_qcom_hd22/src/algorithm_gesture/src/ams_gesture_core.c
0943d97e723a716129efe0aad203025bdebfbecb  ./ams_tmx490x_qcom_hd22/src/algorithm_gesture/src/ams_gesture_API_info.c
0943d97e723a716129efe0aad203025bdebfbecb  ./ams_tmx490x_qcom_hd22/src/algorithm_gesture/include/ams_gesture_API.h
0943d97e723a716129efe0aad203025bdebfbecb  ./ams_tmx490x_qcom_hd22/src/algorithm_gesture/include/ams_gesture_calibration.h
0943d97e723a716129efe0aad203025bdebfbecb  ./ams_tmx490x_qcom_hd22/src/algorithm_gesture/include/ams_gesture_core.h
c8e79b435fc6473b258ed9f0962c7786a891c81f  ./ams_tmx490x_qcom_hd22/src/dev_com_iface/src/ams_device_com_interface.c
c8e79b435fc6473b258ed9f0962c7786a891c81f  ./ams_tmx490x_qcom_hd22/src/dev_com_iface/include/ams_device_com_interface.h
2dad92045ce32acf5055e46a82353ab0d6f888ee  ./ams_tmx490x_qcom_hd22/src/algorithm_flicker/src/ams_flicker_API_init.c
2dad92045ce32acf5055e46a82353ab0d6f888ee  ./ams_tmx490x_qcom_hd22/src/algorithm_flicker/src/ams_flicker_API_info.c
2dad92045ce32acf5055e46a82353ab0d6f888ee  ./ams_tmx490x_qcom_hd22/src/algorithm_flicker/src/ams_flicker_API_config.c
2dad92045ce32acf5055e46a82353ab0d6f888ee  ./ams_tmx490x_qcom_hd22/src/algorithm_flicker/src/ams_flicker_API_result.c
2dad92045ce32acf5055e46a82353ab0d6f888ee  ./ams_tmx490x_qcom_hd22/src/algorithm_flicker/src/ams_flicker_API_process.c
2dad92045ce32acf5055e46a82353ab0d6f888ee  ./ams_tmx490x_qcom_hd22/src/algorithm_flicker/src/ams_flicker_core.c
2dad92045ce32acf5055e46a82353ab0d6f888ee  ./ams_tmx490x_qcom_hd22/src/algorithm_flicker/include/ams_flicker_core.h
2dad92045ce32acf5055e46a82353ab0d6f888ee  ./ams_tmx490x_qcom_hd22/src/algorithm_flicker/include/ams_flicker_API.h
0fffc445130180dddfd05a90dabd053dbd82de38  ./ams_tmx490x_qcom_hd22/src/ccb_proximity_dynamic_b/src/core_control_block_dyn_prox_init.c
0fffc445130180dddfd05a90dabd053dbd82de38  ./ams_tmx490x_qcom_hd22/src/ccb_proximity_dynamic_b/src/core_control_block_dyn_prox.c
0fffc445130180dddfd05a90dabd053dbd82de38  ./ams_tmx490x_qcom_hd22/src/ccb_proximity_dynamic_b/include/core_control_block_dyn_prox.h
24eac85329886ce82627a54da2d81614c076976a  ./ams_tmx490x_qcom_hd22/src/ams_port_platform.h
24eac85329886ce82627a54da2d81614c076976a  ./ams_tmx490x_qcom_hd22/src/dd_ams.h
e77bb8690ffdb4d13f9a92c7fe149beace30b869  ./ams_tmx490x_qcom_hd22/src/tmx490x_dev_ctrl_block/src/ams_device_control_block_init.c
e77bb8690ffdb4d13f9a92c7fe149beace30b869  ./ams_tmx490x_qcom_hd22/src/tmx490x_dev_ctrl_block/src/ams_device_control_block.c
e77bb8690ffdb4d13f9a92c7fe149beace30b869  ./ams_tmx490x_qcom_hd22/src/tmx490x_dev_ctrl_block/include/ams_device_control_block.h
20854d55e9fee8b0787b60f02b2fd249dd246aff  ./ams_tmx490x_qcom_hd22/src/ccb_als/src/core_control_block_als_init.c
20854d55e9fee8b0787b60f02b2fd249dd246aff  ./ams_tmx490x_qcom_hd22/src/ccb_als/src/core_control_block_als.c
20854d55e9fee8b0787b60f02b2fd249dd246aff  ./ams_tmx490x_qcom_hd22/src/ccb_als/include/core_control_block_als.h
ebd0a567719248739d0a97343b53df481d4d1773  ./ams_tmx490x_qcom_hd22/src/ccb_proximity_dynamic_a/src/core_control_block_dyn_prox_init.c
ebd0a567719248739d0a97343b53df481d4d1773  ./ams_tmx490x_qcom_hd22/src/ccb_proximity_dynamic_a/src/core_control_block_dyn_prox.c
ebd0a567719248739d0a97343b53df481d4d1773  ./ams_tmx490x_qcom_hd22/src/ccb_proximity_dynamic_a/include/core_control_block_dyn_prox.h
7823d9348d179d4063fe78e9e1b8bba5abf9c005  ./ams_tmx490x_qcom_hd22/ReadMe.txt
7823d9348d179d4063fe78e9e1b8bba5abf9c005  ./ams_tmx490x_qcom_hd22/BSDheader.txt
7823d9348d179d4063fe78e9e1b8bba5abf9c005  ./ams_tmx490x_qcom_hd22/build/sensor_img/qdsp6/AAAAAAAA/DoNotRemove.txt
7823d9348d179d4063fe78e9e1b8bba5abf9c005  ./ams_tmx490x_qcom_hd22/build/dd_vendor.scons
*/

/****************************************************************************
  Copyright (c) 2016 -2017 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
 ****************************************************************************/
/*============================================================================
  EDIT HISTORY FOR FILE

  when              who  what, where, why
  ----------  ---  -----------------------------------------------------------
  03/14/2017  sq   add als tuning factors in nv_memory_calibrationData
  08/30/2016  PB   DAF support from Vendor
  08/29/2016  PB   Tune prox hreshold limits
  08/11/2016  PB   Revert lux calibration factor to fix light OEM self test
  08/03/2016  PB   Tune lux calibration factor and prox near threshold
============================================================================*/

#include "string.h"
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
#ifdef SENSORS_DD_DEV_FLAG
#include "qurt_elite_diag.h"
#endif
#include "driver_access_framework.h"
#include "stdlib.h"
#include <limits.h>


/*
Processing H file:
./ams_tmx490x_qcom_hd22/src/ams_port_platform.h
*/

#ifndef AMS_PORT_PLATFORM_H
#define AMS_PORT_PLATFORM_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef ENDIAN_LITTLE
#define AMS_ENDIAN_1    0
#define AMS_ENDIAN_2    8
#else
#define AMS_ENDIAN_2    0
#define AMS_ENDIAN_1    8
#endif

#ifdef SENSORS_DD_DEV_FLAG
#endif

#define AMS_PORT_portHndl   sns_ddf_handle_t

#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS
#endif
#ifndef CONFIG_AMS_OPTICAL_SENSOR_PROX
#ifdef CONFIG_AMS_OPTICAL_SENSOR_PROX_CCB
#define CONFIG_AMS_OPTICAL_SENSOR_PROX
#endif
#endif

extern void AMS_PORT_get_timestamp_usec(uint64_t *timestamp);
extern void AMS_PORT_timer_callback(void * callBack, uint64_t timeout);
extern uint8_t AMS_PORT_getByte(AMS_PORT_portHndl * portHndl, uint8_t reg, uint8_t * data, uint8_t lenght);
extern uint8_t AMS_PORT_setByte(AMS_PORT_portHndl * portHndl, uint8_t reg, uint8_t * data, uint8_t lenght);
extern void AMS_PORT_suspend(uint32_t timeOut_us);

#if 0
#define AMS_PORT_log(x)                   UMSG(MSG_SSID_SNS, DBG_LOW_PRIO, "AMS: - <" x ">")
#define AMS_PORT_log_1(x, a)              UMSG_1(MSG_SSID_SNS, DBG_LOW_PRIO, "AMS: - <" x ">", a)
#define AMS_PORT_log_2(x, a, b)           UMSG_2(MSG_SSID_SNS, DBG_LOW_PRIO, "AMS: - <" x ">", a, b)
#define AMS_PORT_log_3(x, a, b, c)        UMSG_3(MSG_SSID_SNS, DBG_LOW_PRIO, "AMS: - <" x ">", a, b, c)
#define AMS_PORT_log_4(x, a, b, c, d)     UMSG_4(MSG_SSID_SNS, DBG_LOW_PRIO, "AMS: - <" x ">", a, b, c, d)
#else
#define AMS_PORT_log(x)              
#define AMS_PORT_log_1(x, a)         
#define AMS_PORT_log_2(x, a, b)      
#define AMS_PORT_log_3(x, a, b, c)   
#define AMS_PORT_log_4(x, a, b, c, d)
#endif

#ifdef __cplusplus
}
#endif

#endif /* AMS_PORT_PLATFORM_H */


/*
Processing H file:
./ams_tmx490x_qcom_hd22/src/algorithm_als/include/ams_als_API.h
*/

/*
 * Device Algorithm ALS
 */

/*
 * @@AMS_REVISION_Id: cee780370eb22b17f687d78123b4575fb8205b88
 */

#ifndef __AMS_DEVICE_ALG_ALS_API_H__
#define __AMS_DEVICE_ALG_ALS_API_H__

#ifdef __TESTBENCH__
#endif
#ifdef VXMICRO_ARCH_Intel
#endif
#ifdef __KERNEL__
#endif
#ifdef QDSP6
#endif


#define AMS_LUX_AVERAGE_COUNT    4

typedef enum _amsAlsAdaptive {
    ADAPTIVE_ALS_NO_REQUEST,
    ADAPTIVE_ALS_TIME_INC_REQUEST,
    ADAPTIVE_ALS_TIME_DEC_REQUEST,
    ADAPTIVE_ALS_GAIN_INC_REQUEST,
    ADAPTIVE_ALS_GAIN_DEC_REQUEST
}amsAlsAdaptive_t;

typedef enum _amsAlsStatus {
    ALS_STATUS_IRQ  = (1 << 0),
    ALS_STATUS_RDY  = (1 << 1),
    ALS_STATUS_OVFL = (1 << 2)
}amsAlsStatus_t;

#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS_RGB
typedef struct _alsData{
    uint16_t clearADC;
    uint16_t redADC;
    uint16_t greenADC;
    uint16_t blueADC;
} alsData_t;
#endif
#if defined CONFIG_AMS_OPTICAL_SENSOR_ALS_CLEAR
typedef struct _alsData{
    uint16_t ch0ADC;
    uint16_t ch1ADC;
} alsData_t;
#endif

typedef struct _amsAlsCalibration {
    uint32_t Time_base; /* in uSec */
    uint16_t calibrationFactor; /* default 1000 */
    uint8_t thresholdLow;
    uint8_t thresholdHigh;
#if defined CONFIG_AMS_OPTICAL_SENSOR_ALS_CLEAR
    uint32_t DGL_factor;
    uint32_t L1_factor;
    uint32_t L2_factor;
    uint32_t L3_factor;
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS_RGB
    uint32_t Cc;
    uint32_t Rc;
    uint32_t Gc;
    uint32_t Bc;
    uint32_t R_coef;
    uint32_t G_coef;
    uint32_t B_coef;
    uint32_t D_factor;
    uint32_t CT_coef;
    uint32_t CT_offset;
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS_WIDEBAND
    uint32_t Wbc;
    uint32_t Wideband_C_factor;
    uint32_t Wideband_R_factor;
    uint32_t Wideband_B_factor;
#endif
} amsAlsCalibration_t;

typedef struct _amsAlsInitData {
    bool adaptive;
    bool irRejection;
    uint32_t time_us;
    uint32_t gain;
} amsAlsInitData_t;

typedef struct _amsALSConf {
    uint32_t time_us;
    uint32_t gain;
    uint8_t thresholdLow;
    uint8_t thresholdHigh;
} amsAlsConf_t;

typedef struct _amsAlsDataSet {
    alsData_t *datasetArray;
    uint64_t timeStamp;
    uint8_t status;
} amsAlsDataSet_t;

typedef struct _amsAlsResult {
    uint32_t    irrClear;
    uint32_t    irrRed;
    uint32_t    irrGreen;
    uint32_t    irrBlue;
    uint32_t    IR;
    uint32_t    irrWideband;
    uint32_t    mLux;
    uint32_t    mLux_ave;
    uint32_t    CCT;
    amsAlsAdaptive_t adaptive;
    uint32_t    rawClear;
    uint32_t    rawRed;
    uint32_t    rawGreen;
    uint32_t    rawBlue;
}amsAlsResult_t;

typedef struct _amsAlsContext {
    uint64_t lastTimeStamp;
    uint32_t ave_lux[AMS_LUX_AVERAGE_COUNT];
    uint32_t ave_lux_index;
    uint32_t cpl;
    uint32_t time_us;
    amsAlsCalibration_t calibration;
    amsAlsResult_t results;
    bool adaptive;
    uint16_t saturation;
    uint32_t gain;
    uint32_t previousGain;
    uint32_t previousLux;
    bool notStableMeasurement;
} amsAlsContext_t;

typedef struct _amsAlsAlgInfo {
    char * algName;
    uint16_t contextMemSize;
    uint16_t scratchMemSize;
    amsAlsCalibration_t calibrationData;
    int (*initAlg) (amsAlsContext_t * ctx, amsAlsInitData_t * initData, amsAlsCalibration_t * calibrationData);
    int (*processData) (amsAlsContext_t * ctx, amsAlsDataSet_t * inputData);
    int (*getResult) (amsAlsContext_t * ctx, amsAlsResult_t * outData);
    int (*setConfig) (amsAlsContext_t * ctx, amsAlsConf_t * inputData);
    int (*getConfig) (amsAlsContext_t * ctx, amsAlsConf_t * outputData);
} amsAlsAlgoInfo_t;

extern int amsAlg_als_getAlgInfo (amsAlsAlgoInfo_t * info);
extern int amsAlg_als_initAlg (amsAlsContext_t * ctx, amsAlsInitData_t * initData, amsAlsCalibration_t * calibrationData);
extern int amsAlg_als_processData(amsAlsContext_t * ctx, amsAlsDataSet_t * inputData);
extern int amsAlg_als_getResult(amsAlsContext_t * ctx, amsAlsResult_t * outData);
extern int amsAlg_als_setConfig(amsAlsContext_t * ctx, amsAlsConf_t * inputData);
extern int amsAlg_als_getConfig(amsAlsContext_t * ctx, amsAlsConf_t * outputData);

#endif

/*
Processing H file:
./ams_tmx490x_qcom_hd22/src/algorithm_als/include/ams_als_callibration.h
*/

/*
 * Device Algorithm ALS
 */

/*
 * @@AMS_REVISION_Id: cee780370eb22b17f687d78123b4575fb8205b88
 */

#ifndef AMS_ALS_CALLIBRATION_H
#define AMS_ALS_CALLIBRATION_H

#if !defined(AMS_CONFIG_ALS_CAL_FACTOR)
#define AMS_CONFIG_ALS_CAL_FACTOR     1200
#endif

#define CPU_FRIENDLY_FACTOR_1024        1
#define AMS_ALS_GAIN_FACTOR             1000
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS_259x
#define AMS_ALS_FACTOR                  1000
#define AMS_ALS_DGL_FACTOR              (923)
#define AMS_ALS_L1_FACTOR               (3.15  * AMS_ALS_FACTOR)
#define AMS_ALS_L2_FACTOR               (0.46 * AMS_ALS_FACTOR)
#define AMS_ALS_L3_FACTOR               (0.74 * AMS_ALS_FACTOR)
#else
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS_CLEAR
#define AMS_ALS_FACTOR                  1000
#define AMS_ALS_DGL_FACTOR              (101)
#define AMS_ALS_L1_FACTOR               (1.75 * AMS_ALS_FACTOR)
#define AMS_ALS_L2_FACTOR               (0.63 * AMS_ALS_FACTOR)
#define AMS_ALS_L3_FACTOR               (1 * AMS_ALS_FACTOR)
#endif
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS_RGB
#define AMS_ALS_Cc                      (118 * CPU_FRIENDLY_FACTOR_1024)
#define AMS_ALS_Rc                      (112 * CPU_FRIENDLY_FACTOR_1024)
#define AMS_ALS_Gc                      (172 * CPU_FRIENDLY_FACTOR_1024)
#define AMS_ALS_Bc                      (180 * CPU_FRIENDLY_FACTOR_1024)
#define AMS_ALS_R_COEF                  ((int32_t)(0.195 * AMS_CONFIG_ALS_CAL_FACTOR))
#define AMS_ALS_G_COEF                  ((int32_t)(1 * AMS_CONFIG_ALS_CAL_FACTOR))
#define AMS_ALS_B_COEF                  ((int32_t)(-0.293 * AMS_CONFIG_ALS_CAL_FACTOR))
#define AMS_ALS_D_FACTOR                ((int32_t)(0.436 * AMS_CONFIG_ALS_CAL_FACTOR))
#define AMS_ALS_CT_COEF                 (4417)
#define AMS_ALS_CT_OFFSET               (1053)
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS_WIDEBAND
#define AMS_WIDEBAND_SCALE_FACTOR       1000
#define AMS_ALS_Wbc                     (111 * CPU_FRIENDLY_FACTOR_1024) /* actual value is TBD */
#define AMS_ALS_WB_C_FACTOR             (0.79 * AMS_WIDEBAND_SCALE_FACTOR)
#define AMS_ALS_WB_R_FACTOR             (0.54 * AMS_WIDEBAND_SCALE_FACTOR)
#define AMS_ALS_WB_B_FACTOR             (0.39 * AMS_WIDEBAND_SCALE_FACTOR)
#endif

#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS_259x
#define AMS_ALS_TIMEBASE                (100000) /* in uSec, see data sheet */
#define AMS_ALS_ADC_MAX_COUNT           (37888) /* see data sheet */
#else
#define AMS_ALS_TIMEBASE                (2780) /* in uSec, see data sheet */
#define AMS_ALS_ADC_MAX_COUNT           (1024) /* see data sheet */
#endif
#define AMS_ALS_THRESHOLD_LOW           (5) /* in % */
#define AMS_ALS_THRESHOLD_HIGH          (5) /* in % */

#ifdef NOT_IMPLEMENTED
#define AMS_ALS_ADAPTIVE_PREF_ATIME_BEFORE_AGAIN   1
#endif

#endif /* AMS_ALS_CALLIBRATION_H */

/*
Processing H file:
./ams_tmx490x_qcom_hd22/src/algorithm_als/include/ams_als_core.h
*/

/*
 * Device Algorithm ALS
 */

/*
 * @@AMS_REVISION_Id: cee780370eb22b17f687d78123b4575fb8205b88
 */

#ifndef __AMS_DEVICE_ALG_ALS_CORE_H__
#define __AMS_DEVICE_ALG_ALS_CORE_H__



#if defined CONFIG_AMS_OPTICAL_SENSOR_ALS_CLEAR || defined CONFIG_AMS_OPTICAL_SENSOR_ALS_259x
extern void als_compute_data_clear (amsAlsContext_t * ctx, amsAlsDataSet_t * inputData);
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS_RGB
extern void als_compute_data (amsAlsContext_t * ctx, amsAlsDataSet_t * inputData);
#endif
extern void als_update_statics(amsAlsContext_t * ctx);
extern void als_ave_LUX (amsAlsContext_t * ctx);
extern amsAlsAdaptive_t als_adaptive(amsAlsContext_t * ctx, amsAlsDataSet_t * inputData);
extern void als_getDefaultCalibrationData(amsAlsCalibration_t * data);

#endif

/*
Processing H file:
./ams_tmx490x_qcom_hd22/src/algorithm_gesture/include/ams_gesture_core.h
*/

/*
 * Device Algorithm Gesture (Basic)
 */

/*
 * @@AMS_REVISION_Id: 0943d97e723a716129efe0aad203025bdebfbecb
 */


#ifndef __AMS_GESTURE_CORE_H__
#define __AMS_GESTURE_CORE_H__

typedef struct _gestureAPIData {
    uint16_t north; /* see datasheet */
    uint16_t south;
    uint16_t west;
    uint16_t east;
}__attribute__ ((packed)) gestureAPIData_t;

typedef struct _gestureData {
    int32_t north;
    int32_t south;
    int32_t west;
    int32_t east;
}gestureData_t;

typedef struct _gestureDataSum {
    int32_t weightNorthSouth;
    int32_t weightEastWest;
}gestureDeltaWeight_t;

enum gesture_state {
    gesture_init,
    gesture_started,
    gesture_active,
    gesture_ending,
    gesture_offset,
    gesture_buttonDown
};

enum gesturePoint {
    north,
    south,
    east,
    west,
    north_east,
    south_east,
    north_west,
    south_west,
    center,
    unknown_gesturePoint
};

typedef enum gesturePoint gestureEntryPoint_t;
typedef enum gesturePoint gestureExitPoint_t;

#endif

/*
Processing H file:
./ams_tmx490x_qcom_hd22/src/algorithm_gesture/include/ams_gesture_calibration.h
*/

/*
 * @@AMS_REVISION_Id: 0943d97e723a716129efe0aad203025bdebfbecb
 */

#ifndef AMS_GESTURE_CALIBRATION_H
#define AMS_GESTURE_CALIBRATION_H

#ifdef __cplusplus
extern "C" {
#endif

#define AMS_GESTURE_CALIBRATION_OFFSET_TARGET   80
#define AMS_GESTURE_CALIBRATION_MAX_AVE         4

#ifdef __cplusplus
}
#endif

#endif /* AMS_GESTURE_CALIBRATION_H */


/*
Processing H file:
./ams_tmx490x_qcom_hd22/src/algorithm_gesture/include/ams_gesture_API.h
*/

/*
 * Device Algorithm Gesture (Basic)
 */

/*
 * @@AMS_REVISION_Id: 0943d97e723a716129efe0aad203025bdebfbecb
 */

#ifndef __AMS_GESTURE_API_H__
#define __AMS_GESTURE_API_H__

#ifdef __TESTBENCH__
#endif
#ifdef VXMICRO_ARCH_Intel
#endif
#ifdef __KERNEL__
#endif
#ifdef QDSP6
#endif


#ifndef false
#define false 0
#endif
#ifndef true
#define true ~false
#endif

/* TODO: Adjust below define to match this magic number to reflect your platform's time-stamp scaling factor
 * The magic number below, must match approximately the number of ticks or time-units to match 500 mill seconds.
 * These units are used to determinate when a new gesture starts
 */
#define MILLISEC_500    500000

typedef enum gestureEvent {
    northToSouth,
    southToNorth,
    eastToWest,
    westToEast,
    northWestToSouthEast,
    northEastToSouthWest,
    southWestToNorthEast,
    southEastToNorthWest,
    pushedAndReleased,
    pushedAndHold,
    unknown_gestureEvent
}gestureEvent_t;

typedef enum gestureMode {
#if 0
    four_point,
    four_point_plus_push,
    eight_point,
    eight_point_plus_push,
#endif
    x_y
}gestureMode_t;

typedef struct _amsGestInitData {
    enum gestureMode mode;
    uint16_t targetOffset;
    uint8_t factorA;
} amsGestInitData_t;

typedef struct _amsGestConf {
    enum gestureMode mode;
    gestureData_t gesOffset;
} amsGestConf_t;

typedef struct _amsGestXYdata {
    int32_t northSouth;
    int32_t eastWest;
} amsGestXYdata_t;

typedef struct {
    amsGestXYdata_t xyBuffer[AMS_GESTURE_CALIBRATION_MAX_AVE];
    uint8_t bufferIndex;
    int32_t northSouthAve;
    int32_t eastWestAve;
    uint8_t xyBufferSize;
} amsGestureXY_t;

typedef struct _amsGestDataSet {
    gestureAPIData_t *datasetArray;
    uint16_t prox;
    uint64_t timeStamp;
} amsGestDataSet_t;

typedef struct _amsGestResult {
    enum gestureEvent event;
    uint32_t strongEntryPoint;
    uint32_t strongExitPoint;
}amsGestResult_t;

typedef struct _amsGestContext {
    uint64_t lastTimeStamp;
    uint32_t lastHighestDeltaAccumulator;
    enum gestureMode mode;
    enum gesture_state state;
    enum gestureEvent eventResult;
    gestureAPIData_t * gestRawData;
    gestureAPIData_t gestOffset;
    gestureData_t gestSum;
    gestureDeltaWeight_t gestDeltaWeight;
    gestureEntryPoint_t entryPoint;
    gestureExitPoint_t exitPoint;
    amsGestureXY_t gestureXY;
    uint16_t activeCounter;
    uint16_t targetOffset;
    uint8_t strongEntryPoint;
    uint8_t strongExitPoint;
    uint8_t factorA;
    uint8_t pushDetectTime;
} amsGestContext_t;

typedef struct _amsGestureAlgInfo {
    char * algName;
    uint16_t contextMemSize;
    uint16_t scratchMemSize;
    int (*initAlg) (amsGestContext_t * ctx, amsGestInitData_t * initData);
    int (*processData) (amsGestContext_t * ctx, amsGestDataSet_t * inputData);
    int (*getResult) (amsGestContext_t * ctx, amsGestResult_t * outData);
    int (*setConfig) (amsGestContext_t * ctx, amsGestConf_t * inputData);
    int (*getConfig) (amsGestContext_t * ctx, amsGestConf_t * outputData);
} amsGestureAlgoInfo_t;

extern int amsAlg_gesture_getAlgInfo (amsGestureAlgoInfo_t * info);
extern int amsAlg_gesture_initAlg (amsGestContext_t * ctx, amsGestInitData_t * initData);
extern int amsAlg_gesture_processData(amsGestContext_t * ctx, amsGestDataSet_t * inputData);
extern int amsAlg_gesture_getResult(amsGestContext_t * ctx, amsGestResult_t * outData);
extern int amsAlg_gesture_setConfig(amsGestContext_t * ctx, amsGestConf_t * inputData);
extern int amsAlg_gesture_getConfig(amsGestContext_t * ctx, amsGestConf_t * outputData);

#endif

/*
Processing H file:
./ams_tmx490x_qcom_hd22/src/ccb_als/include/core_control_block_als.h
*/

/*
 * Core Control Block Flicker
 */

/*
 * @@AMS_REVISION_Id: 20854d55e9fee8b0787b60f02b2fd249dd246aff
 */

#ifndef __AMS_CCB_CORE_CONROL_BLOCK_ALS_H__
#define __AMS_CCB_CORE_CONROL_BLOCK_ALS_H__

#ifdef __TESTBENCH__
#elif VXMICRO_ARCH_Intel
#endif
#ifdef QDSP6
#endif


#define HIGH    0xFF
#define LOW     0x00

#if !defined(AMS_CONFIG_ALS_CAL_FACTOR)
#define AMS_CONFIG_ALS_CAL_FACTOR     1200
#endif

#if !defined(AMS_CONFIG_ALS_CAL_TARGET)
#define AMS_CONFIG_ALS_CAL_TARGET      300 /* lux */
#endif

#if !defined(CONFIG_ALS_CAL_TARGET_TOLERANCE)
#define CONFIG_ALS_CAL_TARGET_TOLERANCE  2 /* lux */
#endif

typedef struct {
    uint32_t calibrationFactor;
    int32_t luxTarget;
    int8_t luxTargetError;
}ams_ccb_als_calibration_t;

typedef struct {
    uint32_t uSecTime;
    uint32_t gain;
    uint8_t  threshold;
}ams_ccb_als_config_t;

typedef struct {
    bool calibrate;
    bool autoGain;
    uint16_t  sampleRate;
    ams_ccb_als_config_t configData;
    ams_ccb_als_calibration_t calibrationData;
}ams_ccb_als_init_t;

typedef enum {
    AMS_CCB_ALS_INIT,
    AMS_CCB_ALS_RGB,
    AMS_CCB_ALS_AUTOGAIN,
    AMS_CCB_ALS_CALIBRATION_INIT,
    AMS_CCB_ALS_CALIBRATION_COLLECT_DATA,
    AMS_CCB_ALS_CALIBRATION_CHECK,
    AMS_CCB_ALS_LAST_STATE
}ams_ccb_als_state_t;

typedef struct {
    char * algName;
    uint16_t contextMemSize;
    uint16_t scratchMemSize;
    ams_ccb_als_calibration_t defaultCalibrationData;
}ams_ccb_als_info_t;

typedef struct {
    ams_ccb_als_state_t state;
    amsAlsContext_t ctxAlgAls;
    ams_ccb_als_init_t initData;
    uint16_t bufferCounter;
    uint16_t shadowAiltReg;
    uint16_t shadowAihtReg;
}ams_ccb_als_ctx_t;

typedef struct {
    uint8_t  statusReg;
}ams_ccb_als_dataSet_t;

typedef struct {
    uint32_t mLux;
    uint32_t colorTemp;
    uint32_t clear;
    uint32_t red;
    uint32_t green;
    uint32_t blue;
    uint32_t ir;
    uint32_t wideband;
    uint32_t rawClear;
    uint32_t rawRed;
    uint32_t rawGreen;
    uint32_t rawBlue;
}ams_ccb_als_result_t;

extern void ccb_alsInit(void * dcbCtx, ams_ccb_als_init_t * initData);
extern void ccb_alsInfo(ams_ccb_als_info_t* infoData);
extern void ccb_alsGetConfig(void * dcbCtx, ams_ccb_als_config_t * configData);
extern void ccb_alsSetConfig(void * dcbCtx, ams_ccb_als_config_t * configData);
extern bool ccb_alsHandle(void * dcbCtx, ams_ccb_als_dataSet_t * data);
extern void ccb_alsGetResult(void * dcbCtx, ams_ccb_als_result_t * result);

#endif

/*
Processing H file:
./ams_tmx490x_qcom_hd22/src/ccb_proximity_dynamic_a/include/core_control_block_dyn_prox.h
*/

/*
 * Core Control Block Dynamic Proximity
 */

/*
 * @@AMS_REVISION_Id: ebd0a567719248739d0a97343b53df481d4d1773
 */

#ifndef __AMS_CCB_CORE_CONROL_BLOCK_DYN_PROX_H__
#define __AMS_CCB_CORE_CONROL_BLOCK_DYN_PROX_H__

#ifdef __TESTBENCH__
#elif VXMICRO_ARCH_Intel
#endif
#ifdef QDSP6
#endif

#define AMS_PRX_TIMEBASE                            (2780) /* in uSec, see data sheet */
#define AMS_PRX_AVERAGE_COUNT                       8
#define AMS_PRX_DEFAULT_PULSE_COUNT                 16
#define AMS_PRX_DEFAULT_PULSE_LENGTH                2 /* 16 uSec */

#define AMS_PRX_DEFAULT_ADC_THRESHOLD               0
#define AMS_PRX_DEFAULT_ADAPTIVE_THRESHOLD_FACTOR   2
#define AMS_PRX_DEFAULT_NEARBY_HARD_THRESHOLD       0x1A00
#define AMS_PRX_DEFAULT_THRESHOLD_HYSTERESIS        0x2000

#define HIGH    0xFF
#define LOW     0x00

#ifndef MIN
#define MIN(a,b) (((a)<(b))?(a):(b))
#endif
#ifndef MAX
#define MAX(a,b) (((a)>(b))?(a):(b))
#endif

typedef enum{
    PRX_STATE_UNKNOWN,
    PRX_STATE_BEGIN,
    PRX_STATE_CAL,
    PRX_STATE_FILLUP,
    PRX_STATE_OPER,
    PRX_STATE_STATIC_NO_DETECT,
    PRX_STATE_STATIC_DETECT,
    PRX_STATE_FACTORY_CALIBRATION,
    PRX_STATE_LAST
}ams_prox_dyn_state_t;

typedef struct {
    bool     dynamicMode;
    bool     calibrate;
    uint32_t ptime_us;
    uint16_t nearByHardThreshold;
    uint16_t nearByThresholdHysteresis;
    uint8_t  adcThreshold;
    uint8_t  numberAdcBits;
}ams_ccb_proximity_init_t;

typedef struct {
    ams_ccb_proximity_init_t initData;
    ams_prox_dyn_state_t state;
    bool nearBy;
    uint32_t pDataNorm;
    uint32_t pDataNormLast;
    uint32_t pDataNormTrigger;
    uint32_t pDataAve;
    uint32_t pDataLow;
    uint32_t pDataMax;
    uint16_t ave[AMS_PRX_AVERAGE_COUNT];
    uint16_t pData;
    uint8_t sensitivity;
    uint8_t ave_index;
}ams_ccb_proximity_ctx_t;

typedef struct {
    uint8_t sensitivity;
}ams_ccb_proximity_config_t;

typedef struct {
    uint32_t alsData;
    uint16_t pData;
    uint8_t  statusReg;
}ams_ccb_proximity_dataSet_t;

typedef struct {
    bool nearBy;
    uint16_t proximity;
}ams_ccb_proximity_result_t;

typedef struct {
    uint32_t hardThreshold;
    uint16_t hardThresholdDistanceMM;
}ams_ccb_proximity_calibration_t;

typedef struct {
    char * algName;
    uint16_t contextMemSize;
    uint16_t scratchMemSize;
    ams_ccb_proximity_calibration_t defaultCalibrationData;
}ams_ccb_proximity_info_t;

extern void ccb_proximityInfo(ams_ccb_proximity_info_t* infoData);
extern void ccb_proximityInit(void * dcbCtx, ams_ccb_proximity_init_t * initData);
extern void ccb_proximitySetConfig(void * dcbCtx, ams_ccb_proximity_config_t * configData);
extern bool ccb_proximityHandle(void * dcbCtx, ams_ccb_proximity_dataSet_t * data);
extern void ccb_proximityGetResult(void * dcbCtx, ams_ccb_proximity_result_t * result);

#endif

/*
Processing H file:
./ams_tmx490x_qcom_hd22/src/ccb_proximity_dynamic_b/include/core_control_block_dyn_prox.h
*/

/*
 * Core Control Block Dynamic Proximity
 */

/*
 * @@AMS_REVISION_Id: 0fffc445130180dddfd05a90dabd053dbd82de38
 */

#ifndef __AMS_CCB_CORE_CONROL_BLOCK_DYN_PROX_H__
#define __AMS_CCB_CORE_CONROL_BLOCK_DYN_PROX_H__

#ifdef __TESTBENCH__
#elif VXMICRO_ARCH_Intel
#endif
#ifdef QDSP6
#endif

#define AMS_PRX_TIMEBASE                            (2780) /* in uSec, see data sheet */
#define AMS_PRX_AVERAGE_COUNT                       16
#define AMS_PRX_DEFAULT_PULSE_COUNT                 16
#define AMS_PRX_DEFAULT_PULSE_LENGTH                3 /* 32uSec */
#define AMS_PRX_DEFAULT_PGLDRIVE                    148 /* mA */

#define AMS_PRX_DEFAULT_ADC_THRESHOLD               0
#define AMS_PRX_DEFAULT_ADAPTIVE_THRESHOLD_FACTOR   2
#define AMS_PRX_DEFAULT_NEARBY_HARD_THRESHOLD       0x7FFF
#define AMS_PRX_DEFAULT_THRESHOLD_HYSTERESIS        0x1000
#define AMS_PRX_INDOOR_LUX_TRIGGER                  6000
#define AMS_PRX_OUTDOOR_LUX_TRIGGER                 10000

#define HIGH    0xFF
#define LOW     0x00

typedef enum{
    PROX_STATE_UNKNOWN,
    PROX_STATE_INIT,
    PROX_STATE_INIT_TWO,
    PROX_STATE_CAL,
    PROX_STATE_CAL_TWO,
    PROX_STATE_OPER,
    PROX_STATE_DETECT,
    PROX_STATE_DETECT_STILL
}ams_prox_dyn_state_t;

typedef struct {
    bool     calibrate;
    uint16_t nearByHardThreshold;
    uint16_t nearByThresholdHysteresis;
    uint8_t  adaptiveThresholdFactor;
    uint8_t  adcThreshold;
}ams_ccb_proximity_init_t;

typedef struct {
    ams_ccb_proximity_init_t initData;
    ams_prox_dyn_state_t state;
    bool nearBy;
    bool amsIndoorMode;
    uint32_t pDataNorm;
    uint16_t pData;
    uint16_t dcavg;
    uint16_t dcavg_max;
    uint16_t th_min;
    uint16_t th_max;
    uint8_t prox_drive;
}ams_ccb_proximity_ctx_t;

typedef struct {
    uint8_t temp;
}ams_ccb_proximity_config_t;

typedef struct {
    uint32_t alsData;
    uint16_t pData;
    uint8_t  statusReg;
}ams_ccb_proximity_dataSet_t;

typedef struct {
    bool nearBy;
    uint16_t proximity;
}ams_ccb_proximity_result_t;

extern void ccb_proximityInit(void * dcbCtx, ams_ccb_proximity_init_t * initData);
extern void ccb_proximitySetConfig(void * dcbCtx, ams_ccb_proximity_config_t * configData);
extern bool ccb_proximityHandle(void * dcbCtx, ams_ccb_proximity_dataSet_t * data);
extern void ccb_proximityGetResult(void * dcbCtx, ams_ccb_proximity_result_t * result);

#endif

/*
Processing H file:
./ams_tmx490x_qcom_hd22/src/tmx490x_dev_ctrl_block/include/ams_device_control_block.h
*/

/*
 * Device Control Block 490x
 */

/*
 * @@AMS_REVISION_Id: e77bb8690ffdb4d13f9a92c7fe149beace30b869
 */

#ifndef __AMS_DEVICE_CONTROL_BLOCK_H__
#define __AMS_DEVICE_CONTROL_BLOCK_H__

#if defined(CONFIG_AMS_OPTICAL_SENSOR_GESTURE) && defined(CONFIG_AMS_OPTICAL_SENSOR_FLICKER)
#error Please define only 1 of:  CONFIG_AMS_OPTICAL_SENSOR_GESTURE, _FLICKER
#endif

#ifdef __KERNEL__
#endif
#ifdef __TESTBENCH__
#endif

#ifdef CONFIG_AMS_OPTICAL_SENSOR_IRBEAM_CCB
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_GESTURE
#endif

#ifdef CONFIG_AMS_OPTICAL_SENSOR_PROX_CCB

typedef struct {
    bool     nearBy;
    uint16_t proximity;
} ams_apiPrx_t;
#endif

#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS_CCB

#ifdef CONFIG_AMS_OPTICAL_SENSOR_FLICKER
typedef struct {
    bool     freq100Hz;
    bool     freq120Hz;
    uint16_t mHz;
} ams_apiAlsFlicker_t;
#endif

typedef struct {
    uint32_t mLux;
    uint32_t colorTemp;
    uint32_t red;
    uint32_t green;
    uint32_t blue;
    uint32_t ir;
    uint32_t wideband;
    uint32_t rawClear;
    uint32_t rawRed;
    uint32_t rawGreen;
    uint32_t rawBlue;
} ams_apiAls_t;
#endif

#ifdef    __cplusplus
extern "C" {
#endif

#define AMS_USEC_PER_TICK               (2780)
#define ACTUAL_USEC(x)                  (((x + AMS_USEC_PER_TICK / 2) / AMS_USEC_PER_TICK) * AMS_USEC_PER_TICK)
#define AMS_ALS_USEC_TO_REG(x)          (256 - (x / AMS_USEC_PER_TICK))
#define AMS_DEFAULT_REPORTTIME_US       (1000000) /* Max 8 seconds */
#define AMS_PRX_PGLD_TO_REG(x)          ((x-4)/8)

#ifndef UINT_MAX_VALUE
#define UINT_MAX_VALUE      (-1)
#endif

#define AMS_CALIBRATION_DONE                (-1)
#define AMS_CALIBRATION_DONE_BUT_FAILED     (-2)

typedef enum _deviceIdentifier_e {
    AMS_UNKNOWN_DEVICE,
    AMS_TMG4903,
    AMS_TMG4904,
    AMS_LAST_DEVICE
} ams_deviceIdentifier_e;

#define AMS_DEVICE_ID       0xB8
#define AMS_DEVICE_ID_MASK  0xFD
#define AMS_REV_ID          0x02
#define AMS_REV_ID_MASK     0x07

#define AMS_PRX_PERS_TO_REG(x)         (x << 4)
#define AMS_PRX_REG_TO_PERS(x)         (x >> 4)
#define AMS_ALS_PERS_TO_REG(x)         (x << 0)
#define AMS_ALS_REG_TO_PERS(x)         (x >> 0)

typedef enum _deviceRegisters {
    DEVREG_ENABLE,      /* 0x80 */
    DEVREG_ATIME,
    DEVREG_PTIME,
    DEVREG_WTIME,
    DEVREG_AILTHL,
    DEVREG_AILTH,
    DEVREG_AIHTHL,
    DEVREG_AIHTH,
    DEVREG_PILTL,
    DEVREG_PILTH,
    DEVREG_PIHTL,
    DEVREG_PIHTH,
    DEVREG_PERS,
    DEVREG_CFG0,
    DEVREG_PGCFG0,
    DEVREG_PGCFG1,
    DEVREG_CFG1,
    DEVREG_REVID,
    DEVREG_ID,
    DEVREG_STATUS,      /* 0x93 */
    DEVREG_CLR_CHANLO,
    DEVREG_CLR_CHANHI,
    DEVREG_RED_CHANLO,
    DEVREG_RED_CHANHI,
    DEVREG_GRN_CHANLO,
    DEVREG_GRN_CHANHI,
    DEVREG_BLU_CHANLO,
    DEVREG_BLU_CHANHI,
    DEVREG_PDATA_LOW,
    DEVREG_PDATA_HI,
    DEVREG_STATUS2,
    DEVREG_CFG2,

    DEVREG_IRBEAM_0,    /* 0xA0 */
    DEVREG_IRBEAM_1,
    DEVREG_IRBEAM_2,
    DEVREG_IRBEAM_3,
    DEVREG_IRBEAM_4,
    DEVREG_IRBEAM_5,
    DEVREG_IRBEAM_6,
    DEVREG_IRBEAM_7,
    DEVREG_IRBEAM_8,
    DEVREG_IRBEAM_9,

    DEVREG_CFG3,        /* 0xAB */
    DEVREG_CFG4,
    DEVREG_CFG5,

    DEVREG_CFG7,        /* 0xAF */

#ifdef CONFIG_AMS_OPTICAL_SENSOR_GESTURE
    DEVREG_GESTURE_0,   /* 0xB0 */
    DEVREG_GESTURE_1,
    DEVREG_GESTURE_2,
    DEVREG_GESTURE_3,
    DEVREG_GESTURE_4,
    DEVREG_GESTURE_5,
    DEVREG_GESTURE_6,
    DEVREG_GESTURE_7,
    DEVREG_GESTURE_8,
    DEVREG_GESTURE_9,
    DEVREG_GESTURE_A,
    DEVREG_GESTURE_B,
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_FLICKER
    DEVREG_NOT_USED_0,   /* 0xB0 */
    DEVREG_NOT_USED_1,
    DEVREG_FLICKER_CFG,
    DEVREG_STATUS_3,     /* 0xB3 */
    DEVREG_NOT_USED_4,
    DEVREG_NOT_USED_5,
    DEVREG_NOT_USED_6,
    DEVREG_NOT_USED_7,
    DEVREG_NOT_USED_8,
    DEVREG_NOT_USED_9,
    DEVREG_FIFO_LVL,     /* 0xBA */
    DEVREG_NOT_USED_B,
#endif
    DEVREG_CONTROL,
    DEVREG_AUXID,

    DEVREG_OFFSET_NL,   /* 0xC0 */
    DEVREG_OFFSET_NH,
    DEVREG_OFFSET_SL,
    DEVREG_OFFSET_SH,
    DEVREG_OFFSET_WL,
    DEVREG_OFFSET_WH,
    DEVREG_OFFSET_EL,
    DEVREG_OFFSET_EH,

    DEVREG_PBSLN_MEASL, /* 0xD0 */
    DEVREG_PBSLN_MEASH,
    DEVREG_CALIB_DCAVG, /* 0xD2 */
    DEVREG_CALIB_DCAVG_H, /* 0xD3 */
    DEVREG_AZ_CONFIG,
    DEVREG_CALIB,
    DEVREG_CAL_CFG0,
    DEVREG_CAL_CFG1,
    DEVREG_CAL_CFG2,
    DEVREG_CAL_CFG3,
    DEVREG_CAL_CFGSTAT,

    DEVREG_INT_ENBL,
    DEVREG_INT_CLEAR,

#ifdef CONFIG_AMS_OPTICAL_SENSOR_GESTURE
    DEVREG_GFIFO_N_L,   /* 0xF8 */
    DEVREG_GFIFO_N_H,
    DEVREG_GFIFO_S_L,
    DEVREG_GFIFO_S_H,
    DEVREG_GFIFO_W_L,
    DEVREG_GFIFO_W_H,
    DEVREG_GFIFO_E_L,
    DEVREG_GFIFO_E_H,
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_FLICKER
    DEVREG_FIFO_0L,     /* 0xF8 */
    DEVREG_FIFO_0H,
    DEVREG_FIFO_1L,
    DEVREG_FIFO_1H,
    DEVREG_FIFO_2L,
    DEVREG_FIFO_2H,
    DEVREG_FIFO_3L,
    DEVREG_FIFO_3H,
#endif
    DEVREG_REG_MAX
}ams_deviceRegister_t;

typedef enum _490x_regOptions {

    PON             = 0x01,  /* register 0x80 */
    AEN             = 0x02,
    PEN             = 0x04,
    WEN             = 0x08,
    AIEN            = 0x10,
    PIEN            = 0x20,
    GEN             = 0x40,
    FIEN            = 0x40,
    IBEN            = 0x80,
#ifdef CONFIG_AMS_OPTICAL_SENSOR_FLICKER
    ALS_ENABLE_ALL  = (AEN+AIEN+FIEN),
#else
    ALS_ENABLE_ALL  = (AEN+AIEN),
#endif

    WLOG            = 0x04,
    LOWPWR_IDLE     = 0x20,

    PPLEN_4uS       = 0x00,  /* register 0x8E */
    PPLEN_8uS       = 0x40,
    PPLEN_16uS      = 0x80,
    PPLEN_32uS      = 0xC0,

    PGAIN_1         = 0x00,  /* register 0x8F */
    PGAIN_2         = 0x40,
    PGAIN_4         = 0x80,
    PGAIN_8         = 0xC0,

    AGAIN_1         = 0x00,  /* register 0x90 */
    AGAIN_4         = 0x01,
    AGAIN_16        = 0x02,
    AGAIN_64        = 0x03,
    PSIEN           = 0x80,
    ASIEN           = 0x40,
    DETCT_FLCKR_0   = 0x00,
    DETCT_FLCKR_1   = 0x04,
    DETCT_FLCKR_2   = 0x08,
    DETCT_FLCKR_3   = 0x0C,
    ENABLE_WB       = 0x10,

    CINT            = 0x02, /* register 0x93 */
#ifdef CONFIG_AMS_OPTICAL_SENSOR_GESTURE
    GINT            = 0x04,
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_FLICKER
    FINT            = 0x04,
#endif
    IINT            = 0x08,
    AINT            = 0x10,
    PINT            = 0x20,
    PGSAT           = 0x40,
    ASAT            = 0x80,
#ifdef CONFIG_AMS_OPTICAL_SENSOR_FLICKER
    ALS_INT_ALL     = (AINT+FINT),
#else
    ALS_INT_ALL     = AINT,
#endif

    PGSAT_AMB       = 0x01, /* register */
    PGSAT_REFL      = 0x02,
    PGSAT_ADC       = 0x04,
    ASAT_ANALOG     = 0x08,
    ASAT_DIGITAL    = 0x10,
    AVALID          = 0x40,
    PVALID          = 0x80,

    PMSK_E          = 0x80,
    PMSK_W          = 0x40,
    PMSK_S          = 0x20,
    PMSK_N          = 0x10,
    AMSK            = 0x08,

    AUTO_WB_DIODE   = 0x80, /* 0xAF */
    GST_EXMSK_ALL   = 0x00, /* 0xB0 */

    BINSRC_SKIPB    = 0x08, /* register 0xD8 */
    ELECT_CAL       = 0x10,
    DCAVG_AUTO_OFF_ADJ = 0x40,

    LAST_IN_ENUM_LIST
}ams_regOptions_t;

typedef enum _490x_regMasks {
    MASK_PON            = 0x01, /* register 0x80 */
    MASK_AEN            = 0x02,
    MASK_PEN            = 0x04,
    MASK_WEN            = 0x08,
    MASK_AIEN           = 0x10,
    MASK_PIEN           = 0x20,
#ifdef CONFIG_AMS_OPTICAL_SENSOR_GESTURE
    MASK_GEN            = 0x40,
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_FLICKER
    MASK_FIEN           = 0x40,
#endif
    MASK_PBEN           = 0x80,

    MASK_ATIME          = 0xFF, /* register 0x81 */

    MASK_PTIME          = 0xFF, /* register 0x82 */

    MASK_WTIME          = 0xFF, /* register 0x83 */

    MASK_AILT           = 0xFFFF, /* register 0x84 */
    MASK_AILH           = 0xFFFF, /* register 0x86 */

    MASK_PILT           = 0xFFFF, /* register 0x88 */
    MASK_PILH           = 0xFFFF, /* register 0x8A */

    MASK_APERS          = 0x0F, /* register 0x8C */
    MASK_PPERS          = 0xF0,

    MASK_WLONG          = 0x02, /* register 0x8D */
    MASK_LOWPWR_IDLE    = 0x40,

    MASK_PPULSE         = 0x3F, /* register 0x9=8e */
    MASK_PPLEN          = 0xC0,

    MASK_PGAIN          = 0xC0, /* register 0x8f */
    MASK_PGLDRIVE       = 0x1E,

    MASK_AGAIN          = 0x03, /* register 0x90 */
    MASK_ASIEN          = 0x40,
    MASK_PGSIEN         = 0x80,
    MASK_DETCT_FLCKR    = 0x0C,
    MASK_ENABLE_WB      = 0x10,

    MASK_REV_ID         = 0x07, /* register 0x91 */

    MASK_ID             = 0xFC, /* register 0x92 */

    MASK_CINT           = 0x02, /* register 0x93 */
#ifdef CONFIG_AMS_OPTICAL_SENSOR_GESTURE
    MASK_GINT           = 0x04,
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_FLICKER
    MASK_FINT           = 0x04,
#endif
    MASK_IINT           = 0x08,
    MASK_AINT           = 0x10,
    MASK_PINT           = 0x20,
    MASK_PGSAT          = 0x40,
    MASK_ASAT           = 0x80,
    MASK_AGDATA         = 0x01,
#ifdef CONFIG_AMS_OPTICAL_SENSOR_FLICKER
    MASK_ALS_INT_ALL    = (MASK_AINT+MASK_FINT),
#else
    MASK_ALS_INT_ALL    = MASK_AINT,
#endif

    MASK_CDATA          = 0xFFFF, /* register 0x94 */
    MASK_RDATA          = 0xFFFF, /* register 0x96 */
    MASK_GDATA          = 0xFFFF, /* register 0x98 */
    MASK_BDATA          = 0xFFFF, /* register 0x9A */
    MASK_PDATA          = 0xFFFF, /* register 0x9C */

    MASK_PGSAT_AMB      = 0x01, /* register */
    MASK_PGSAT_REFL     = 0x02,
    MASK_PGSAT_ADC      = 0x04,
    MASK_ASAT_ANALOG    = 0x08,
    MASK_ASAT_DIGITAL   = 0x10,
    MASK_AVALID         = 0x40,
    MASK_PVALID         = 0x80,

    MASK_PMSK_E         = 0x80,
    MASK_PMSK_W         = 0x40,
    MASK_PMSK_S         = 0x20,
    MASK_PMSK_N         = 0x10,
    MASK_AMSK           = 0x08,

    MASK_AUTO_WB_DIODE  = 0x80, /* 0xAF */

    MASK_GST_EXMSK      = 0x3c, /* register 0xB0 */
    MASK_GST_EXPERS     = 0x03,

    MASK_OFFSET_CALIB   = 0x01, /* register 0xD7 */

    MASK_DCAVG_ITR      = 0x07, /* register 0xD8 */
    MASK_BINSRC_SKIPB   = 0x08,
    MASK_ELECT_CAL      = 0x10,
    MASK_DCAVG_AUTO_OFF_ADJ = 0x40,

    MASK_BINSRCH        = 0x70, /* register 0xDA */
    MASK_AUTO_GTH       = 0x0f,
    MASK_AUTO_DCAVG_GTH = 0x80,

    MASK_INTCLR_CINT    = 0x02, /* Register 0xde */
#ifdef CONFIG_AMS_OPTICAL_SENSOR_GESTURE
    MASK_INTCLR_GINT    = 0x04,
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_FLICKER
    MASK_INTCLR_FINT    = 0x04,
#endif
    MASK_INTCLR_IINT    = 0x08,
    MASK_INTCLR_AINT    = 0x10,
    MASK_INTCLR_PINT    = 0x20,
    MASK_INTCLR_PGSAT   = 0x40,
    MASK_INTCLR_ASAT    = 0x80,
#ifdef CONFIG_AMS_OPTICAL_SENSOR_FLICKER
    MASK_ALS_INTCLR_ALL = (MASK_INTCLR_AINT+MASK_INTCLR_FINT+MASK_INTCLR_ASAT),
#else
    MASK_ALS_INTCLR_ALL = (MASK_INTCLR_AINT+MASK_INTCLR_ASAT),
#endif

    MASK_LAST_IN_ENUMLIST
}ams_regMask_t;

enum _tmx4905_calibcfg0 {
    TMX4905_DCAVG_ITERATIONS        = (0x7 << 0),
    TMX4905_BINSRCH_SKIP            = (0x1 << 3),
    TMX4905_ELECTRICAL_CALIBRATION  = (0x1 << 4),
    TMX4905_BINSRCH_NOSUPPRESS_APC  = (0x1 << 5),
    TMX4905_DCAVG_AUTO_OFFSET_ADJUST = (0x1 << 6),
    TMX4905_DCAVG_AUTO_BASELINE     = (0x1 << 7)
};

enum _tmx4905_calibcfg1 {
    TMX4905_PXDCAVG_BASELINE_WINDOW = (0x7 << 0),
    TMX4905_PXDCAVG_AUTO_BASELINE   = (0x1 << 3),
    TMX4905_PROX_AUTO_OFFSET_ADJUST = (0x1 << 6),
    TMX4905_PXDCAVG_AUTO_GTHR       = (0x1 << 7)
};

typedef struct _deviceRegisterTable {
    uint8_t address;
    uint8_t resetValue;
}deviceRegisterTable_t;

typedef enum _490x_config_options {
    AMS_CONFIG_ENABLE,
    AMS_CONFIG_THRESHOLD,
    AMS_CONFIG_OPTION_LAST
}deviceConfigOptions_t;

typedef enum _490x_mode {
    MODE_OFF            = (0),
    MODE_ALS_LUX        = (1 << 0),
    MODE_ALS_RGB        = (1 << 1),
    MODE_ALS_CT         = (1 << 2),
    MODE_ALS_WIDEBAND   = (1 << 3),
    MODE_PROX           = (1 << 4),
    MODE_GESTURE        = (1 << 5),
    MODE_ALS_RGB_ALT_REPORT = (1 << 6),
    MODE_PROX_ALT_REPORT    = (1 << 7),
    MODE_ALS_ALL        = (MODE_ALS_LUX | MODE_ALS_RGB | MODE_ALS_CT | MODE_ALS_WIDEBAND | MODE_ALS_RGB_ALT_REPORT),
    MODE_PROX_ALL       = (MODE_PROX | MODE_PROX_ALT_REPORT),
    MODE_UNKNOWN    /* must be in last position */
} ams_mode_t;

typedef enum _490x_configureFeature {
#ifdef CONFIG_AMS_OPTICAL_SENSOR_PROX_CCB
    AMS_CONFIG_PROX,
    AMS_CONFIG_PROX_ALT_REPORT,
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS_CCB
    AMS_CONFIG_ALS_LUX,
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS_RGB
    AMS_CONFIG_ALS_RGB,
    AMS_CONFIG_ALS_RGB_ALT_REPORT,
    AMS_CONFIG_ALS_CT,
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS_WIDEBAND
    AMS_CONFIG_ALS_WIDEBAND,
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_GESTURE
    AMS_CONFIG_GESTURE,
#endif
    AMS_CONFIG_FEATURE_LAST
}ams_configureFeature_t;

typedef struct _calibrationData {
    uint32_t    timeBase_us;
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS_CCB
    uint16_t    alsCalibrationLuxTarget;
    uint16_t    alsCalibrationLuxTargetError;
    uint16_t    alsCalibrationFactor;        /* multiplicative factor default 1000 */
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_PROX_CCB
    uint16_t    proxHardThreshold;
#endif
    uint32_t     alsItemsSum;
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS_RGB
    uint32_t     alsCalibrationCoefR;
    uint32_t     alsCalibrationCoefG;
    uint32_t     alsCalibrationCoefB;
    uint32_t     alsCalibrationFactorD;
    uint32_t     alsCalibrationCoefCT;
    uint32_t     alsCalibrationOffsetCT;   
#endif
} ams_calibrationData_t;

typedef struct _490xContext {
    ams_deviceIdentifier_e deviceId;
    uint64_t timeStamp;
    AMS_PORT_portHndl * portHndl;
    ams_mode_t mode;
#ifdef AMS_PHY_SUPPORT_SHADOW
    uint8_t shadow[DEVREG_REG_MAX];
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_GESTURE
    amsGestContext_t gestureCtx;
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_PROX_CCB
    ams_ccb_proximity_ctx_t ccbProxCtx;
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS_CCB
    ams_ccb_als_ctx_t ccbAlsCtx;
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_IRBEAM_CCB
    ams_ccb_irBeam_ctx_t ccbIrBeamCtx;
#endif

    ams_calibrationData_t * systemCalibrationData;
    uint32_t updateAvailable;
    uint8_t shadowEnableReg;
    uint8_t shadowStatus1Reg;
    uint8_t shadowStatus2Reg;
}ams_deviceCtx_t;

typedef enum _sensorType {
    AMS_NO_SENSOR_AVAILABLE,
    AMS_AMBIENT_SENSOR,
    AMS_PROXIMITY_SENSOR,
    AMS_GESTURE_SENSOR,
    AMS_WIDEBAND_ALS_SENSOR,
    AMS_LAST_SENSOR
}ams_sensorType_t;

typedef struct _sensorInfo {
    uint32_t    standbyCurrent_uA;
    uint32_t    activeCurrent_uA;
    uint32_t    rangeMin;
    uint32_t    rangeMax;
    char *      driverName;
    uint8_t     maxPolRate;
    uint8_t     adcBits;
} ams_SensorInfo_t;

typedef struct _deviceInfo {
    uint32_t    memorySize;
    ams_calibrationData_t defaultCalibrationData;
#ifdef CONFIG_AMS_OPTICAL_SENSOR_PROX_CCB
    ams_SensorInfo_t proxSensor;
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS_CCB
    ams_SensorInfo_t alsSensor;
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_GESTURE
    ams_SensorInfo_t gestureSensor;
#endif
    ams_sensorType_t tableSubSensors[10];
    uint8_t     numberOfSubSensors;
    char *      driverVersion;
    char *      deviceModel;
    char *      deviceName;
}ams_deviceInfo_t;

#if defined CONFIG_AMS_OPTICAL_SENSOR_ALS_CCB
extern uint32_t alsGain_conversion[];
extern uint8_t alsGainToReg(uint32_t x);
extern uint8_t alsTimeUsToReg(uint32_t nominalTimeUs, uint32_t *quantizedTimeUs);
#endif
#if defined CONFIG_AMS_OPTICAL_SENSOR_PROX_CCB
extern uint32_t proxGain_conversion[];
extern uint8_t proxGainToReg(uint32_t x);
extern uint8_t proxTimeToReg (uint32_t x);
extern uint32_t proxRegToTime (uint8_t x);
#endif

extern deviceRegisterTable_t deviceRegisterDefinition[DEVREG_REG_MAX];
extern ams_deviceIdentifier_e ams_validateDevice(AMS_PORT_portHndl * portHndl);
extern bool ams_getDeviceInfo(ams_deviceInfo_t * info);
extern bool ams_getMode(ams_deviceCtx_t * ctx, ams_mode_t * mode);
extern bool ams_deviceInit(ams_deviceCtx_t * ctx, AMS_PORT_portHndl * portHndl, ams_calibrationData_t * calibrationData);
extern bool ams_deviceEventHandler(ams_deviceCtx_t * ctx);
extern uint32_t ams_getResult(ams_deviceCtx_t * ctx);
extern bool ams_deviceSetConfig(ams_deviceCtx_t * ctx, ams_configureFeature_t feature, deviceConfigOptions_t option, uint32_t data);
extern bool ams_deviceGetConfig(ams_deviceCtx_t * ctx);
extern bool ams_deviceCalibrateLux(ams_deviceCtx_t * ctx, ams_calibrationData_t * calibrationData);
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS_CCB
extern bool ams_deviceGetAls(ams_deviceCtx_t * ctx, ams_apiAls_t * exportData);
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_PROX_CCB
extern bool ams_deviceGetPrx(ams_deviceCtx_t * ctx, ams_apiPrx_t * exportData);
extern bool ams_deviceCalibrateProx(ams_deviceCtx_t * ctx, ams_calibrationData_t * calibrationData);
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_GESTURE
extern bool ams_deviceGetGesture(ams_deviceCtx_t * ctx, amsGestResult_t * exportData);
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_FLICKER
extern bool ams_deviceGetFlicker(ams_deviceCtx_t * ctx, ams_apiAlsFlicker_t * exportData);
#endif

#ifdef __cplusplus
}
#endif

#else

#endif /* __AMS_DEVICE_CONTROL_BLOCK_H__ */


/*
Processing H file:
./ams_tmx490x_qcom_hd22/src/dev_com_iface/include/ams_device_com_interface.h
*/

/*
 * Device Communication Interface
 */

/*
 * @@AMS_REVISION_Id: c8e79b435fc6473b258ed9f0962c7786a891c81f
 */

#ifndef __AMS_DEVICE_COMM_INTERFACE_H__
#define __AMS_DEVICE_COMM_INTERFACE_H__

#ifdef __cplusplus
extern "C" {
#endif

extern uint8_t ams_getByte(AMS_PORT_portHndl * portHndl, ams_deviceRegister_t reg, uint8_t * readData);
extern uint8_t ams_getWord(AMS_PORT_portHndl * portHndl, ams_deviceRegister_t reg, uint16_t * readData);
extern uint8_t ams_getBuf(AMS_PORT_portHndl * portHndl, ams_deviceRegister_t reg, uint8_t * readData, uint8_t length);
extern uint8_t ams_tmg490x_getField(AMS_PORT_portHndl * portHndl, ams_deviceRegister_t reg, uint8_t * data, ams_regMask_t mask);
extern uint8_t ams_setByte(AMS_PORT_portHndl * portHndl, ams_deviceRegister_t reg, uint8_t data);
extern uint8_t ams_setWord(AMS_PORT_portHndl * portHndl, ams_deviceRegister_t reg, uint16_t data);
extern uint8_t ams_setBuf(AMS_PORT_portHndl * portHndl, ams_deviceRegister_t reg, uint8_t * data, uint8_t length);
extern uint8_t ams_tmg490x_setField(AMS_PORT_portHndl * portHndl, ams_deviceRegister_t reg, uint8_t data, ams_regMask_t mask);

#ifdef __cplusplus
}
#endif

#endif /* __AMS_DEVICE_COMM_INTERFACE_H__ */


/*
Processing H file:
./ams_tmx490x_qcom_hd22/src/dd_ams.h
*/

/*
 *
 */

/*
 * @@AMS_REVISION_Id: 24eac85329886ce82627a54da2d81614c076976a
 */


#ifndef __DD_AMS_H__
#define __DD_AMS_H__

//#define ENABLE_DEBUG
/* define this flag to enable uImage operation */
#define ENABLE_UIMG

#ifndef ENABLE_UIMG
/* Define extended DDF uImage functions if missing in HD22 package */
#define sns_ddf_malloc_ex(ptr, size, smgr_handle)                               sns_ddf_malloc(ptr, size)
#define sns_ddf_mfree_ex(ptr, smgr_handle)                                      sns_ddf_mfree(ptr)
#define sns_ddf_memhandler_malloc_ex(memhandler, size, smgr_handle)             sns_ddf_memhandler_malloc(memhandler, size)
#define sns_ddf_smgr_is_in_uimage()                                             false
#endif
#ifdef ENABLE_DEBUG
#define DBG_MEDIUM_PRIO DBG_MED_PRIO
#define DD_MSG_0(level,msg)          UMSG(MSG_SSID_SNS,   DBG_##level##_PRIO, "AMS: - <" msg ">")
#define DD_MSG_1(level,msg,p1)       UMSG_1(MSG_SSID_SNS, DBG_##level##_PRIO, "AMS: - <" msg ">",p1)
#define DD_MSG_2(level,msg,p1,p2)    UMSG_2(MSG_SSID_SNS, DBG_##level##_PRIO, "AMS: - <" msg ">",p1,p2)
#define DD_MSG_3(level,msg,p1,p2,p3) UMSG_3(MSG_SSID_SNS, DBG_##level##_PRIO, "AMS: - <" msg ">",p1,p2,p3)
#else
#define DD_MSG_0(level,msg)
#define DD_MSG_1(level,msg,p1)
#define DD_MSG_2(level,msg,p1,p2)
#define DD_MSG_3(level,msg,p1,p2,p3)
#endif

#define DD_HANDLE_ALIGN     3
#define DD_MAX_DAF_REQS     3 // Prox-Polling, ALS-Polling, and Reverb

#define SENSOR_AMBIENT_SAMPLES      2
#define SENSOR_RGB_SAMPLES          3
#define SENSOR_CT_SAMPLES           2
#define SENSOR_WIDEBAND_SAMPLES     1
#define SENSOR_PROXIMITY_SAMPLES    2
#define SENSOR_GESTURE_SAMPLES      1

#define SNS_DD_SENSOR_WIDEBAND      (SNS_DDF_SENSOR_OEM_SENSOR_01)

#define SENSOR_MASK_ALS             0x01
#define SENSOR_MASK_RGB             0x02
#define SENSOR_MASK_CT              0x04
#define SENSOR_MASK_WIDEBAND        0x08
#define SENSOR_MASK_ALS_ALL         (SENSOR_MASK_ALS | SENSOR_MASK_RGB | SENSOR_MASK_CT | SENSOR_MASK_WIDEBAND | SENSOR_MASK_RGB_ALT_REPORT)
#define SENSOR_MASK_PROX            0x10
#define SENSOR_MASK_GESTURE         0x20
#define SENSOR_MASK_RGB_ALT_REPORT  0x40
#define SENSOR_MASK_PROX_ALT_REPORT 0x80

#if !defined(AMS_CONFIG_ALS_THRESHOLD_PERCENT)
#define AMS_CONFIG_ALS_THRESHOLD_PERCENT  5 /* percent */
#endif



typedef enum {
    TIMER_EVENT_ALS_CALIBRATION,
    TIMER_EVENT_UNKNOWN,
}ams_timerEvents_t;

typedef struct {
    bool                           dri_enable;
    uint16_t                       interrupt_gpio;
    sns_ddf_handle_t               smgr_handle;  /* notify_data handle */
    uint32_t                       current_odr[2];
    sns_ddf_powerstate_e           powerstate[2];
    sns_ddf_timer_s                timer_obj[2];
    uint32_t                       num_sensors;
    sns_ddf_sensor_e               sensors[2];
    void *                         timer_arg[2];
} sns_dd_sub_dev_t;

typedef struct
{
    sns_ddf_dev_list_t             next;     /* the next device instance */
    sns_ddf_driver_info_s          dd_info;  /* the driver info */
} sns_dd_head_s;

typedef struct
{
    uint32_t         daf_active_req;
    void*            daf_conn_handle;
    bool             daf_trans_id_valid;
    uint8_t          daf_trans_id;
    sns_ddf_timer_s  daf_timer;
    sns_ddf_sensor_e daf_timer_arg;
    uint32_t         daf_echo;
} sns_dd_daf_s;

/* State struct for driver */
typedef struct
{
    sns_ddf_port_id_s         port_id;
    sns_ddf_handle_t          port_handle;                            /* Port handle for bus access */
    sns_ddf_timer_s           sns_dd_tmr_obj;                         /* timer obj */
    sns_ddf_dev_list_t        next;
    sns_dd_sub_dev_t*         sub_dev;
    uint16_t                  sub_dev_count;
    uint16_t                  ams_max_supported_features;
    uint32_t                  gpio1;
    ams_deviceCtx_t           chip;
    ams_calibrationData_t     calibrationData;
    uint32_t                  report_mask;
    int16_t                   als_sub_dev_idx; // should always be 0, unless....?
    int16_t                   rgb_sub_dev_idx; // it's not clear if these 2 can be on
    int16_t                   cct_sub_dev_idx; //   separate subdevs, but assume so
    int16_t                   wideband_sub_dev_idx;
    int16_t                   prox_sub_dev_idx; // should always be same as als, unless....?
    int16_t                   gesture_sub_dev_idx;
    sns_dd_daf_s              daf_reqs[DD_MAX_DAF_REQS];
} sns_dd_ams_t;

extern sns_ddf_status_e sns_dd_init
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
extern sns_ddf_status_e sns_dd_reset
(
    sns_ddf_handle_t dd_handle
);
extern sns_ddf_status_e sns_dd_set_attrib
(
    sns_ddf_handle_t     dd_handle,
    sns_ddf_sensor_e     sensor,
    sns_ddf_attribute_e  attrib,
    void*                value
);
extern sns_ddf_status_e sns_dd_get_attrib
(
    sns_ddf_handle_t        dd_handle,
    sns_ddf_sensor_e        sensor,
    sns_ddf_attribute_e     attrib,
    sns_ddf_memhandler_s*   memhandler,
    void**                  value,
    uint32_t*               num_elems
);
extern sns_ddf_status_e sns_dd_run_test
(
    sns_ddf_handle_t    dd_handle,
    sns_ddf_sensor_e    sensor_type,
    sns_ddf_test_e      test,
    uint32_t*           err
);
extern sns_ddf_status_e sns_dd_probe
(
    sns_ddf_device_access_s* device_info,
    sns_ddf_memhandler_s*    memhandler,
    uint32_t*                num_sensors,
    sns_ddf_sensor_e**       sensors
);
extern sns_ddf_status_e sns_dd_enable_sched_data
(
    sns_ddf_handle_t state,
    sns_ddf_sensor_e sensor,
    bool             enable
);

typedef struct{
    uint8_t  visible_light_trans_ratio;
    uint8_t  ir_light_trans_ratio;
    uint16_t dc_offset;
    uint16_t near_threshold;
    uint16_t far_threshold;
    uint16_t prx_factor;
    uint16_t als_factor;
    ams_calibrationData_t ams_data;
}sns_ddf_nv_calibration_data_t;

#ifdef SENSORS_DD_DEV_FLAG
extern sns_ddf_driver_if_s sns_dd_vendor_if_1;
#define TMG490x_DD_if sns_dd_vendor_if_1
#else // SENSORS_DD_DEV_FLAG
extern sns_ddf_driver_if_s sns_dd_tmg490x_if;
#define TMG490x_DD_if sns_dd_tmg490x_if
#endif // SENSORS_DD_DEV_FLAG

#endif /* __DD_AMS_H__ */
