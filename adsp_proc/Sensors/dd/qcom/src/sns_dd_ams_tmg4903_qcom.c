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
  Copyright (c) 2016 - 2017 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
 ****************************************************************************/
/*============================================================================
  EDIT HISTORY FOR FILE

  when              who  what, where, why
  ----------  ---  -----------------------------------------------------------
  04/04/2017  pc   KW fix
  03/14/2017  sq   add als tuning factors in nv_memory_calibrationData
  03/10/2017  AN   change device Info alsSensor.rangeMax to 32767 to fit in q16_t
  02/02/2017  BD   Change resolution in sensorinfo to 1
  12/20/2016  PB   Validate calibration params from registry
  12/08/2016  jhh  Remove checksum validation
  08/30/2016  PB   DAF support from Vendor
  08/15/2016  PB   Fix Klocwork issues
  08/03/2016  PB   Tune lux calibration factor and prox near threshold
============================================================================*/

#include "sns_dd_ams_tmg4903_qcom.h"


/*
Processing bigImage file:
./ams_tmx490x_qcom_hd22/src/algorithm_als/src/ams_als_API_info.c
*/

/*
 * Device Algorithm ALS
 */

/*
 * @@AMS_REVISION_Id: cee780370eb22b17f687d78123b4575fb8205b88
 */

#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS

/*
 * getAlgInfo: Intended to be called by a wrapper, allowing the wrapper to
 * allocate memory for the algorithm.
 * It's not needed to call this API, but it could be useful in certain OS'es
 */
int amsAlg_als_getAlgInfo (amsAlsAlgoInfo_t * info) {
    int ret = 0;

    info->algName = "AMS_ALS";
    info->contextMemSize = sizeof(amsAlsContext_t);
    info->scratchMemSize = 0;

    info->initAlg = &amsAlg_als_initAlg;
    info->processData = &amsAlg_als_processData;
    info->getResult = &amsAlg_als_getResult;
    info->setConfig = &amsAlg_als_setConfig;
    info->getConfig = &amsAlg_als_getConfig;

    als_getDefaultCalibrationData(&info->calibrationData);
    return ret;
}
#endif

/*
Processing bigImage file:
./ams_tmx490x_qcom_hd22/src/algorithm_als/src/ams_als_API_init.c
*/

/*
 * Device Algorithm ALS
 */

/*
 * @@AMS_REVISION_Id: cee780370eb22b17f687d78123b4575fb8205b88
 */

#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS

extern void als_calc_cpl(amsAlsContext_t * ctx);

/*
 * initAlg: is used to initialize the algorithm.
 */
int amsAlg_als_initAlg (amsAlsContext_t * ctx, amsAlsInitData_t * initData, amsAlsCalibration_t * calibrationData){
    int ret = 0;

    if (calibrationData == NULL){
        als_getDefaultCalibrationData(&ctx->calibration);
    } else {
        ctx->calibration.Time_base = calibrationData->Time_base;
        ctx->calibration.thresholdLow = calibrationData->thresholdLow;
        ctx->calibration.thresholdHigh = calibrationData->thresholdHigh;
        ctx->calibration.calibrationFactor = calibrationData->calibrationFactor;
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS_RGB
	if( ctx->calibration.R_coef == 0 && ctx->calibration.G_coef == 0
	    && ctx->calibration.B_coef == 0 && ctx->calibration.D_factor == 0
	    && ctx->calibration.CT_coef ==0 && ctx->calibration.CT_offset == 0) {
        	ctx->calibration.R_coef = calibrationData->R_coef;
        	ctx->calibration.G_coef = calibrationData->G_coef;
        	ctx->calibration.B_coef = calibrationData->B_coef;
        	ctx->calibration.D_factor = calibrationData->D_factor;
        	ctx->calibration.CT_coef = calibrationData->CT_coef;
        	ctx->calibration.CT_offset = calibrationData->CT_offset;
	}
	   ctx->calibration.Rc = calibrationData->Rc;
       ctx->calibration.Gc = calibrationData->Gc;
       ctx->calibration.Bc = calibrationData->Bc;
       ctx->calibration.Cc = calibrationData->Cc;
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS_WIDEBAND
        ctx->calibration.Wbc = calibrationData->Wbc;
        ctx->calibration.Wideband_C_factor = calibrationData->Wideband_C_factor;
        ctx->calibration.Wideband_R_factor = calibrationData->Wideband_R_factor;
        ctx->calibration.Wideband_B_factor = calibrationData->Wideband_B_factor;
#endif
#if defined CONFIG_AMS_OPTICAL_SENSOR_ALS_CLEAR || CONFIG_AMS_OPTICAL_SENSOR_ALS_259x
        ctx->calibration.DGL_factor = calibrationData->DGL_factor;
        ctx->calibration.L1_factor = calibrationData->L1_factor;
        ctx->calibration.L2_factor = calibrationData->L2_factor;
        ctx->calibration.L3_factor = calibrationData->L3_factor;
#endif
    }

    if (initData != NULL) {
        ctx->gain = initData->gain;
        ctx->time_us = initData->time_us;
        ctx->adaptive = initData->adaptive;
    } else {
        ctx->time_us = 200000;
        ctx->gain = 16350;
        ctx->adaptive = true;
    }

    als_update_statics(ctx);
    return ret;
}
#endif

/*
Processing bigImage file:
./ams_tmx490x_qcom_hd22/src/algorithm_gesture/src/ams_gesture_API_info.c
*/

/*
 * Device Algorithm Gesture (Basic)
 */

/*
 * @@AMS_REVISION_Id: 0943d97e723a716129efe0aad203025bdebfbecb
 */


gestureEvent_t getResultEightPoint(amsGestContext_t * ctx);

/*
 * getAlgInfo: Intended to be called by a wrapper, allowing the wrapper to
 * allocate memory for the algorithm.
 * It's not needed to call this API, but it could be useful in certain OS'es
 */
int amsAlg_gesture_getAlgInfo (amsGestureAlgoInfo_t * info) {
    int ret = 0;

    info->algName = "AMS_Gesture";
    info->contextMemSize = sizeof(amsGestContext_t);
    info->scratchMemSize = 0;
    info->initAlg = &amsAlg_gesture_initAlg;
    info->processData = &amsAlg_gesture_processData;
    info->getResult = &amsAlg_gesture_getResult;
    info->setConfig = &amsAlg_gesture_setConfig;
    info->getConfig = NULL;

    return ret;
}

/*
Processing bigImage file:
./ams_tmx490x_qcom_hd22/src/algorithm_gesture/src/ams_gesture_API_init.c
*/

/*
 * Device Algorithm Gesture (Basic)
 */

/*
 * @@AMS_REVISION_Id: 0943d97e723a716129efe0aad203025bdebfbecb
 */


/*
 * initAlg: is used to initialize the algorithm.
 */
int amsAlg_gesture_initAlg (amsGestContext_t * ctx, amsGestInitData_t * initData){
    int ret = 0;

    memset(ctx, 0, sizeof(amsGestContext_t));
    ctx->mode = x_y;
    ctx->lastTimeStamp = 0;
    ctx->entryPoint = unknown_gesturePoint;
    ctx->exitPoint = unknown_gesturePoint;
    ctx->state = gesture_init;
    ctx->pushDetectTime = 50;
    ctx->factorA = AMS_GESTURE_CALIBRATION_MAX_AVE;

    if (initData != NULL) {
        ctx->mode = initData->mode;
        ctx->factorA = initData->factorA;
        ctx->targetOffset = initData->targetOffset;
    }
    if(ctx->factorA > AMS_GESTURE_CALIBRATION_MAX_AVE){
        ctx->factorA = AMS_GESTURE_CALIBRATION_MAX_AVE;
        ctx->targetOffset = AMS_GESTURE_CALIBRATION_OFFSET_TARGET;
    }
    return ret;
}

/*
Processing bigImage file:
./ams_tmx490x_qcom_hd22/src/ccb_als/src/core_control_block_als_init.c
*/

/*
 * Core Control Block ALS
 */

/*
 * @@AMS_REVISION_Id: 20854d55e9fee8b0787b60f02b2fd249dd246aff
 */


void ccb_alsInfo(ams_ccb_als_info_t* infoData){
    infoData->algName = "ALS";
    infoData->contextMemSize = sizeof(ams_ccb_als_ctx_t);
    infoData->scratchMemSize = 0;
    infoData->defaultCalibrationData.calibrationFactor = AMS_CONFIG_ALS_CAL_FACTOR;
    infoData->defaultCalibrationData.luxTarget = AMS_CONFIG_ALS_CAL_TARGET;
    infoData->defaultCalibrationData.luxTargetError = CONFIG_ALS_CAL_TARGET_TOLERANCE;
}

/*
Processing bigImage file:
./ams_tmx490x_qcom_hd22/src/ccb_proximity_dynamic_a/src/core_control_block_dyn_prox_init.c
*/

/*
 * Core Control Block Dynamic Proximity
 */

/*
 * @@AMS_REVISION_Id: ebd0a567719248739d0a97343b53df481d4d1773
 */


void ccb_proximityInfo(ams_ccb_proximity_info_t* infoData){

    infoData->algName = "PROX";
    infoData->contextMemSize = sizeof(ams_ccb_proximity_ctx_t);
    infoData->scratchMemSize = 0;
    infoData->defaultCalibrationData.hardThreshold = 0x3000;
    infoData->defaultCalibrationData.hardThresholdDistanceMM = 500; /* 500 millimeters */
}

/*
Processing bigImage file:
./ams_tmx490x_qcom_hd22/src/dd_ams_ext.c
*/

/*
 *
 */

/*
 * @@AMS_REVISION_Id: 24eac85329886ce82627a54da2d81614c076976a
 */


/*============================================================================
              STATIC VARIABLE DEFINITIONS
============================================================================*/
static sns_dd_head_s dd_head = { NULL, {"dd_name", 1} };

extern sns_ddf_status_e sns_dd_set_attrib
(
    sns_ddf_handle_t     dd_handle,
    sns_ddf_sensor_e     sensor,
    sns_ddf_attribute_e  attrib,
    void*                value
);

sns_ddf_status_e sns_dd_handleCalibrationData
(
    sns_dd_ams_t*         state,
    uint32_t              sub_dev_id,
    sns_ddf_nv_params_s*  reg_params
)
{
    sns_ddf_status_e status = SNS_DDF_SUCCESS;
    bool haveValidCalibrationData = false;

    if (reg_params){
        sns_ddf_nv_calibration_data_t *nv_memory_calibrationData = (sns_ddf_nv_calibration_data_t *) reg_params->data;
        ams_calibrationData_t * ams_calibrationData = &nv_memory_calibrationData->ams_data;

        if (reg_params->status == SNS_DDF_SUCCESS){
            if (reg_params->data_len >= sizeof(sns_ddf_nv_calibration_data_t)){
                uint32_t checkSum = 0;
                uint8_t i;
                for(i=0; i<sizeof(sns_ddf_nv_calibration_data_t); i++ ){
                    checkSum += reg_params->data[i];
                    checkSum ++;
                    checkSum &= 0xFF;
                }
                if (nv_memory_calibrationData->als_factor && nv_memory_calibrationData->near_threshold) {
                    haveValidCalibrationData = true;
                    memcpy(&state->calibrationData, ams_calibrationData, sizeof(ams_calibrationData_t));
                    state->calibrationData.alsCalibrationFactor = (nv_memory_calibrationData->als_factor * 10);
                    state->calibrationData.proxHardThreshold = nv_memory_calibrationData->near_threshold;
                    DD_MSG_0(LOW, "sns_dd_handleCalibrationData: found calibration data");
                    AMS_PORT_log_1("nv_memory_calibrationData->als_factor     = %d\n", nv_memory_calibrationData->als_factor);
                    AMS_PORT_log_1("nv_memory_calibrationData->near_threshold = %d\n", nv_memory_calibrationData->near_threshold);
                } else {
                    DD_MSG_2(LOW, "sns_dd_handleCalibrationData: checkSum= %d, data %x", checkSum, ams_calibrationData);
                }
            }
        }
    }

    if (haveValidCalibrationData == false) {
        ams_deviceInfo_t info;
        ams_getDeviceInfo(&info);
        memcpy(&state->calibrationData, &info.defaultCalibrationData, sizeof(ams_calibrationData_t));
        status = sns_ddf_smgr_notify_event(state->sub_dev[sub_dev_id].smgr_handle,
                            SNS_DDF_SENSOR__ALL,
                            SNS_DDF_EVENT_UPDATE_REGISTRY_GROUP);
        DD_MSG_1(LOW, "sns_dd_handleCalibrationData: defaultData %d", status);
    }
    return status;
}

/*===========================================================================*/
/*
 * @brief sns_dd_find_same_port_dev: check if a device with the input
 *                         port config has already been initialized.
 *
 * @param[in] port_config_ptr - I2C port config.
 *
 * @return NULL if a similar port device was not initialized
 *         device state pointer if already initialized
 */
 /*===========================================================================*/
static sns_dd_ams_t *sns_dd_find_same_port_dev(sns_ddf_port_config_s *port_config_ptr)
{
  sns_dd_ams_t *cur_dd_dev_ptr = (sns_dd_ams_t*)dd_head.next;

  while (cur_dd_dev_ptr)
  {
    if (true == sns_ddf_is_same_port_id(port_config_ptr, &cur_dd_dev_ptr->port_id))
    {
      DD_MSG_1(MED, "find_same_port_dev - cur_dev_ptr: %p", cur_dd_dev_ptr);
      return cur_dd_dev_ptr;
    }
    else
    {
      cur_dd_dev_ptr = cur_dd_dev_ptr->next;
    }
  }
  return NULL;
}


/*===========================================================================*/
/*
 * @brief sns_dd_ams_490x_init_timer: initialize timer for the sub device.
 *
 * @param[in] state - DD state handle.
 * @param[in] sub_dev_id
 * @param[in] sensor
 *
 * @return SNS_DDF_SUCCESS if timer init is successful else error code
 */
/*===========================================================================*/
sns_ddf_status_e sns_dd_ams_490x_init_timer
(
    sns_dd_ams_t*      state,
    uint32_t           sub_dev_id,
    sns_ddf_sensor_e*  sensor
)
{
    int i;
    sns_ddf_status_e ret = SNS_DDF_SUCCESS;

    state->sub_dev[sub_dev_id].timer_arg[0] = (void*)TIMER_EVENT_UNKNOWN;

    ret = sns_ddf_timer_init(&state->sub_dev[sub_dev_id].timer_obj[0],
                             (sns_ddf_handle_t)((uint32_t)state | sub_dev_id),
                             &TMG490x_DD_if,
                             &state->sub_dev[sub_dev_id].timer_arg[0],
                             FALSE);

    /* timers for DAF Requests */
    for (i = 0; i < DD_MAX_DAF_REQS; i++)
    {
      ret = sns_ddf_timer_init(&state->daf_reqs[i].daf_timer,
        (sns_ddf_handle_t)((uint32_t)state | sub_dev_id),
        &TMG490x_DD_if,
        &state->daf_reqs[i].daf_timer,
        TRUE);
    }

    return ret;
}

/*===========================================================================*/
/*
 * @brief sns_dd_fill_sub_dev_slot: fill all info for a sub device.
 *
 * @param[in] sub_dev_slot - sub device slot to fill
 * @param[in] smgr_handle - SMGR handle for this sub device
 * @param[in] gpio - GPIO num for this sub device
 * @param[in] num_sensors - number of sensors supported by this sub device
 * @param[in] sensors - sensor list supported by this sub device
 * @param[in] maxSupportedSensors - maximum supported sensors by this sub device
 *
 * @return number of sensors
 */
/*===========================================================================*/
static uint32_t sns_dd_fill_sub_dev_slot
(
    sns_dd_ams_t      *state,
    sns_dd_sub_dev_t* sub_dev_slot,
    sns_ddf_handle_t  smgr_handle,
    uint16_t          gpio,
    uint32_t          num_sensors,
    sns_ddf_sensor_e  sensors[],
    uint16_t          maxSupportedSensors
)
{
    int i;
    uint32_t num_sensors_filled = 0;

    // Check for null-pointers
    if (NULL == sub_dev_slot)
    {
        DD_MSG_1(ERROR, "sns_dd_fill_sub_dev_slot: sub_dev_slot: %d", sub_dev_slot);
        return 0;
    }

    // Check bounds
    if (num_sensors > maxSupportedSensors)
    {
        DD_MSG_1(ERROR, "sns_dd_fill_sub_dev_slot: num_sensors: %d", num_sensors);
        return 0;
    }

    for( i = 0 ; i < num_sensors ; i++ )
    {
        DD_MSG_2(MED, "sns_dd_fill_sub_dev_slot: %d %d", num_sensors_filled, sensors[i]);
        sub_dev_slot->powerstate[i]  = SNS_DDF_POWERSTATE_LOWPOWER;
        sub_dev_slot->current_odr[i] = 0;
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS
        if (sensors[i] == SNS_DDF_SENSOR_AMBIENT){
            sub_dev_slot->sensors[num_sensors_filled++] = SNS_DDF_SENSOR_AMBIENT;
            state->als_sub_dev_idx = state->sub_dev_count;
        }
#else
        if (sensors[i] == SNS_DDF_SENSOR_AMBIENT) DD_MSG_0(HIGH, "no CONFIG_AMS_OPTICAL_SENSOR_ALS");
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS_RGB
        if (sensors[i] == SNS_DDF_SENSOR_RGB){
            sub_dev_slot->sensors[num_sensors_filled++] = SNS_DDF_SENSOR_RGB;
            state->rgb_sub_dev_idx = state->sub_dev_count;
        }
        if (sensors[i] == SNS_DDF_SENSOR_CT_C){
            sub_dev_slot->sensors[num_sensors_filled++] = SNS_DDF_SENSOR_CT_C;
            state->cct_sub_dev_idx = state->sub_dev_count;
        }
#else
        if (sensors[i] == SNS_DDF_SENSOR_RGB)  DD_MSG_0(HIGH, "no CONFIG_AMS_OPTICAL_SENSOR_ALS_RGB");
        if (sensors[i] == SNS_DDF_SENSOR_CT_C) DD_MSG_0(HIGH, "no CONFIG_AMS_OPTICAL_SENSOR_ALS_RGB");
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS_WIDEBAND
        if (sensors[i] == SNS_DD_SENSOR_WIDEBAND){
            sub_dev_slot->sensors[num_sensors_filled++] = SNS_DD_SENSOR_WIDEBAND;
            state->wideband_sub_dev_idx = state->sub_dev_count;
        }
#else
        if (sensors[i] == SNS_DD_SENSOR_WIDEBAND) DD_MSG_0(HIGH, "no CONFIG_AMS_OPTICAL_SENSOR_ALS_WIDEBAND");
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_PROX
        if (sensors[i] == SNS_DDF_SENSOR_PROXIMITY){
            sub_dev_slot->sensors[num_sensors_filled++] = SNS_DDF_SENSOR_PROXIMITY;
            state->prox_sub_dev_idx = state->sub_dev_count;
        }
#else
        if (sensors[i] == SNS_DDF_SENSOR_PROXIMITY) DD_MSG_0(HIGH, "no CONFIG_AMS_OPTICAL_SENSOR_PROX");
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_GESTURE
        if (sensors[i] == SNS_DDF_SENSOR_IR_GESTURE){
            sub_dev_slot->sensors[num_sensors_filled++] = SNS_DDF_SENSOR_IR_GESTURE;
            state->gesture_sub_dev_idx = state->sub_dev_count;
        }
#else
        if (sensors[i] == SNS_DDF_SENSOR_IR_GESTURE) DD_MSG_0(HIGH, "no CONFIG_AMS_OPTICAL_SENSOR_GESTURE");
#endif
    }

    sub_dev_slot->smgr_handle    = smgr_handle;
    sub_dev_slot->num_sensors    = num_sensors_filled;
    sub_dev_slot->interrupt_gpio = gpio;
    sub_dev_slot->dri_enable     = false;

    if(sub_dev_slot->interrupt_gpio != 0xFFFF)
    {
        sub_dev_slot->dri_enable     = true;
        DD_MSG_0(MED, "sns_dd_fill_sub_dev_slot: DRI");
    }
    return sub_dev_slot->num_sensors;
}


/*===========================================================================

FUNCTION:   sns_dd_reset

===========================================================================*/
/**
* @brief Resets the driver and device so they return to the state they were
*        in after init() was called.
*
* @param[in] dd_handle  Handle to a driver instance.
*
* @return Success if the driver was able to reset its state and the device.
*         Otherwise a specific error code is returned.
*/
/*=========================================================================*/
sns_ddf_status_e sns_dd_reset
(
    sns_ddf_handle_t dd_handle
)
{
    sns_dd_ams_t *state = (sns_dd_ams_t *)(((uint32_t)dd_handle) & (uint32_t)(~DD_HANDLE_ALIGN));
    uint32_t     sub_dev_id = (uint32_t)dd_handle & ((uint32_t)DD_HANDLE_ALIGN);

    if (sub_dev_id == 0)
        state->report_mask &= ~(SENSOR_MASK_ALS | SENSOR_MASK_PROX);
    else if (sub_dev_id == 1)
        state->report_mask &= ~(SENSOR_MASK_RGB | SENSOR_MASK_CT);
#ifdef DCONFIG_AMS_OPTICAL_SENSOR_ALS_WIDEBAND
    else if (sub_dev_id == 2)
        state->report_mask &= ~(SENSOR_MASK_WIDEBAND);
#endif

    if (state->report_mask == 0){
        DD_MSG_1(MED, "sns_dd_reset(%p): no reporters => ams_deviceInit", dd_handle);
        ams_deviceInit(&state->chip, state->port_handle, &state->calibrationData);
    }
    else {
        DD_MSG_2(MED, "sns_dd_reset(%p): reporters=0x%02x => no init", dd_handle, state->report_mask);
    }
    return SNS_DDF_SUCCESS;
}

/*===========================================================================

FUNCTION:   sns_dd_init

===========================================================================*/
/**
* @brief Initializes the driver and sets up devices.
*
* @param[out] dd_handle_ptr  Pointer that this function must malloc and
*                            populate. This is a handle to the driver
*                            instance that will be passed in to all other
*                            functions. NB: Do not use @a memhandler to
*                            allocate this memory.
* @param[in]  smgr_handle    Handle used to identify this driver when it
*                            calls into Sensors Manager functions.
* @param[in]  nv_params      NV parameters retrieved for the driver.
* @param[in]  device_info    Access info for physical devices controlled by
*                            this driver. Used to configure the bus
*                            and talk to the devices.
* @param[in]  num_devices    Number of elements in @a device_info.
* @param[in]  memhandler     Memory handler used to dynamically allocate
*                            output parameters, if applicable. NB: Do not
*                            use memhandler to allocate memory for
*                            @a dd_handle_ptr.
* @param[in/out] sensors     List of supported sensors, allocated,
*                            populated, and returned by this function.
* @param[in/out] num_sensors Number of elements in @a sensors.
*
* @return Success if @a dd_handle_ptr was allocated and the driver was
*         configured properly. Otherwise a specific error code is returned.
*/
/*=========================================================================*/
sns_ddf_status_e sns_dd_init
(
    sns_ddf_handle_t*       dd_ptr,
    sns_ddf_handle_t        smgr_handle,
    sns_ddf_nv_params_s*    nv_params,
    sns_ddf_device_access_s device_info[],
    uint32_t                num_devices,
    sns_ddf_memhandler_s*   memhandler,
    sns_ddf_sensor_e*       sensors[],
    uint32_t*               num_sensors
)
{
    sns_dd_ams_t            *state;
    sns_ddf_status_e        ret = SNS_DDF_SUCCESS;
    uint32_t                dd_num_sensors = 0;

#ifdef ENABLE_UIMG
    /* Update smgr sensor data for the driver to indicate uImage support */
    sns_ddf_smgr_set_uimg_refac(smgr_handle);
    DD_MSG_0(HIGH, "sns_dd_init: ENABLE_UIMG");
#else
    DD_MSG_0(HIGH, "sns_dd_init:");
#endif

    /* basic sanity check */
    if (dd_ptr == NULL || sensors == NULL || num_sensors == NULL) {
        return SNS_DDF_EINVALID_PARAM;
    }

    DD_MSG_1(MED, "sns_dd_init - sensors[0] = %d", (*sensors)[0]);
    DD_MSG_1(MED, "sns_dd_init - sensors[1] = %d", (*sensors)[1]);

    // If the device instance does not exist, then initialize it
    state = sns_dd_find_same_port_dev(&device_info->port_config);
    if ( NULL == state ) {
        DD_MSG_0(ERROR,"sns_dd_init: first time");
        /* allocate state memory */
        if (sns_ddf_malloc_ex((void **)&state, sizeof(sns_dd_ams_t), smgr_handle) != SNS_DDF_SUCCESS) {
            DD_MSG_0(ERROR,"sns_dd_init: malloc sns_dd_ams_t failed");
            return SNS_DDF_ENOMEM;
        }
        memset(state, 0, sizeof(sns_dd_ams_t));
        //init subdev idx's to invalid
        state->als_sub_dev_idx = -1;
        state->rgb_sub_dev_idx = -1;
        state->cct_sub_dev_idx = -1;
        state->wideband_sub_dev_idx = -1;
        state->prox_sub_dev_idx = -1;
        state->gesture_sub_dev_idx = -1;

        {
            sns_ddf_handle_t dd_handle;
            // Assign the dd_handle_ptr
            dd_handle = (sns_ddf_handle_t)((uint32_t)state | state->sub_dev_count);
            *dd_ptr = dd_handle;
        }

        // Put this device instance at the front of the list (all inserts into
        // the list are placed at the front)
        state->next = NULL;
        dd_head.next = state;
        state->sub_dev_count = 0;

        // skip this function if API not available
        sns_ddf_get_port_id(&device_info->port_config, &state->port_id);

        /* open I2C port */
        ret = sns_ddf_open_port(&state->port_handle, &device_info->port_config);
        if (ret != SNS_DDF_SUCCESS) {
            DD_MSG_0(ERROR,"sns_dd_init: I2C open failed");
            sns_ddf_mfree_ex(state, smgr_handle);
            dd_head.next = NULL;
            return ret;
        }

        DD_MSG_0(LOW, "sns_dd_init: => ams_validateDevice");
        if (ams_validateDevice(state->port_handle) == false){
            DD_MSG_0(ERROR, "sns_dd_init: ams_validateDevice failed");
            sns_ddf_close_port(state->port_handle);
            sns_ddf_mfree_ex(state, smgr_handle);
            dd_head.next = NULL;
            return SNS_DDF_EFAIL;
        }

        {
            DD_MSG_0(LOW, "sns_dd_init: => ams_getDeviceInfo");
            ams_deviceInfo_t info;
            ams_getDeviceInfo(&info);
            state->ams_max_supported_features = info.numberOfSubSensors;
            DD_MSG_1(LOW, "ams_getDeviceInfo: contextMemsize= %d", info.memorySize);
#ifdef CONFIG_AMS_USE_SCRATCH_MEMORY
            DD_MSG_1(LOW, "ams_getDeviceInfo: scratchMemeorySize= %d", info.scratchMemeorySize);
#endif

            if (sns_ddf_malloc_ex((void **)&state->sub_dev, (sizeof(sns_dd_sub_dev_t) * info.numberOfSubSensors), smgr_handle) != SNS_DDF_SUCCESS) {
                DD_MSG_0(ERROR,"sns_dd_init: malloc sns_dd_sub_dev_t failed");
                sns_ddf_close_port(state->port_handle);
                sns_ddf_mfree_ex(state, smgr_handle);
                dd_head.next = NULL;
                return SNS_DDF_ENOMEM;
            }
        }

        /* Fill out the first sub-device slot */
        dd_num_sensors = sns_dd_fill_sub_dev_slot( state,
                    &state->sub_dev[state->sub_dev_count],
                    smgr_handle,
                    device_info->first_gpio,
                    *num_sensors,
                    *sensors,
                    state->ams_max_supported_features);
        if (dd_num_sensors == 0)
        {
            DD_MSG_0(ERROR, "sns_dd_init: Unable to initialize any sensors.");
            sns_ddf_close_port(state->port_handle);
            sns_ddf_mfree_ex(state->sub_dev, smgr_handle);
            sns_ddf_mfree_ex(state, smgr_handle);
            dd_head.next = NULL;
            return SNS_DDF_EINVALID_DATA;
        }

        // init timers
        ret = sns_dd_ams_490x_init_timer(state, state->sub_dev_count, (sns_ddf_sensor_e *)*sensors);
        if (ret != SNS_DDF_SUCCESS)
        {
            DD_MSG_0(ERROR, "sns_dd_init:  failed init timer");
            sns_ddf_close_port(state->port_handle);
            sns_ddf_mfree_ex(state->sub_dev, smgr_handle);
            sns_ddf_mfree_ex(state, smgr_handle);
            dd_head.next = NULL;
            return SNS_DDF_EFAIL;
        }

        /* get calibration data */
        ret = sns_dd_handleCalibrationData(state, state->sub_dev_count, nv_params);
        if (SNS_DDF_SUCCESS != ret)
        {
          DD_MSG_0(ERROR, "sns_dd_init: Failed to handle calibration data");
          sns_ddf_close_port(state->port_handle);
          sns_ddf_mfree_ex(state, smgr_handle);
          dd_head.next = NULL;
          return SNS_DDF_EFAIL;
        }

        DD_MSG_0(LOW, "sns_dd_init: => ams_deviceInit");
        if (ams_deviceInit(&state->chip, state->port_handle, &state->calibrationData) == true) {
            DD_MSG_0(ERROR, "sns_dd_init: ams_deviceInit failed");
            sns_ddf_close_port(&state->port_handle);
            sns_ddf_mfree_ex(state, smgr_handle);
            dd_head.next = NULL;
            return SNS_DDF_EFAIL;
        }

        // Set the output and return
        *num_sensors = dd_num_sensors;
        *sensors = (sns_ddf_sensor_e *)state->sub_dev[state->sub_dev_count].sensors;

        state->sub_dev_count++;

        DD_MSG_0(ERROR,"sns_dd_init: exit :-) ");
        return SNS_DDF_SUCCESS;

    } else {
        DD_MSG_0(ERROR,"sns_dd_init: next sub-device");
        // If there is an empty slot
        if (state->sub_dev_count < state->ams_max_supported_features)
        {
            // Fill out the next sub-device slot
            dd_num_sensors = sns_dd_fill_sub_dev_slot(state,
                                    &state->sub_dev[state->sub_dev_count],
                                    smgr_handle,
                                    device_info->first_gpio,
                                    *num_sensors,
                                    *sensors,
                                    state->ams_max_supported_features);

            if (dd_num_sensors == 0)
            {
                DD_MSG_0(ERROR, "sns_dd_init: Unable to initialize any sensors.");
                return SNS_DDF_EFAIL;
            }

            {
            sns_ddf_handle_t dd_handle;
            // Assign the dd_handle_ptr
            dd_handle = (sns_ddf_handle_t)((uint32_t)state | state->sub_dev_count);
            *dd_ptr = dd_handle;
            }

            *num_sensors = dd_num_sensors;
            *sensors = (sns_ddf_sensor_e *)state->sub_dev[state->sub_dev_count].sensors;
            state->sub_dev_count++;

            DD_MSG_0(ERROR,"sns_dd_init: exit :-) ");
            return SNS_DDF_SUCCESS;
        }
        else
        {
            DD_MSG_0(ERROR, "sns_dd_init: Out of sub-device slots.");
            return SNS_DDF_ENOMEM;
        }
    }
  return SNS_DDF_SUCCESS;
}

/*===========================================================================

FUNCTION:   sns_dd_set_attrib

===========================================================================*/
/**
* @brief Sets a sensor attribute to a specific value.
*
* @param[in] dd_handle  Handle to a driver instance.
* @param[in] sensor     Sensor for which this attribute is to be set. When
*                       addressing an attribute that refers to the driver
*                       this value is set to SNS_DDF_SENSOR__ALL.
* @param[in] attrib     Attribute to be set.
* @param[in] value      Value to set this attribute.
*
* @return Success if the value of the attribute was set properly. Otherwise
*         a specific error code is returned.
*/
/*=========================================================================*/
sns_ddf_status_e sns_dd_set_attrib
(
    sns_ddf_handle_t     dd_handle,
    sns_ddf_sensor_e     sensor,
    sns_ddf_attribute_e  attrib,
    void*                value
)
{
    sns_ddf_status_e status = SNS_DDF_SUCCESS;
    sns_dd_ams_t *state = (sns_dd_ams_t *)(((uint32_t)dd_handle) & (uint32_t)(~DD_HANDLE_ALIGN));
    uint32_t      sub_dev_id = (uint32_t)dd_handle & ((uint32_t)DD_HANDLE_ALIGN);
    sns_ddf_powerstate_e power_state;
    ams_configureFeature_t feature = AMS_CONFIG_FEATURE_LAST; // init to invalid

    DD_MSG_1(HIGH, "sns_dd_set_attrib: ENTER %p", dd_handle);

    /* Input sanity check */
    if (state == NULL)
    {
        return SNS_DDF_EINVALID_PARAM;
    }

    DD_MSG_3(MED, "sns_dd_set_attrib: sensor=%d attrib=%d sub_dev=%d", sensor, attrib, sub_dev_id);

    switch(sensor)
    {
    case SNS_DDF_SENSOR__ALL:
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS
    case SNS_DDF_SENSOR_AMBIENT:
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS_RGB
    case SNS_DDF_SENSOR_RGB:
    case SNS_DDF_SENSOR_CT_C:
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS_WIDEBAND
    case SNS_DD_SENSOR_WIDEBAND:
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_PROX
    case SNS_DDF_SENSOR_PROXIMITY:
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_GESTURE
    case SNS_DDF_SENSOR_IR_GESTURE:
#endif
        break;
    default:
        DD_MSG_1(MED, "%s: Be sure to add the appropriate sensor in your build script to match the config file", __func__);
        return SNS_DDF_EINVALID_PARAM;
    }

    switch(attrib)
    {
    case SNS_DDF_ATTRIB_ODR:
    {
        uint32_t thresh = 1;
        uint32_t odr = *(uint32_t*)value;
        uint32_t mode;
        if (odr > 0){
            mode = 1;
        } else {
            mode = 0;
        }

        if (state->sub_dev[sub_dev_id].sensors[0] == sensor){
            state->sub_dev[sub_dev_id].current_odr[0] = odr;
            DD_MSG_2(MED, "sns_dd_set_attrib: SNS_DDF_ATTRIB_ODR: sensor[0]=%u, odr = %u", sensor, odr);
        } else {
            if (state->sub_dev[sub_dev_id].sensors[1] == sensor){
                state->sub_dev[sub_dev_id].current_odr[1] = odr;
                DD_MSG_2(MED, "sns_dd_set_attrib: SNS_DDF_ATTRIB_ODR: sensor [1]=%u, odr = %u", sensor, odr);
            }
        }
        switch ( sensor )
        {
        case SNS_DDF_SENSOR__ALL:
            break;
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS
        case SNS_DDF_SENSOR_AMBIENT:
            feature = AMS_CONFIG_ALS_LUX;
            if (mode){
                state->report_mask |= SENSOR_MASK_ALS;
                thresh = AMS_CONFIG_ALS_THRESHOLD_PERCENT;
            }
            else
                state->report_mask &= ~(SENSOR_MASK_ALS);
            break;
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS_RGB
        case SNS_DDF_SENSOR_RGB:
            feature = AMS_CONFIG_ALS_RGB;
            if (mode){
                state->report_mask |= SENSOR_MASK_RGB;
                thresh = AMS_CONFIG_ALS_THRESHOLD_PERCENT;
            }
            else
                state->report_mask &= ~(SENSOR_MASK_RGB);
            break;
        case SNS_DDF_SENSOR_CT_C:
            feature = AMS_CONFIG_ALS_CT;
            if (mode){
                state->report_mask |= SENSOR_MASK_CT;
                thresh = AMS_CONFIG_ALS_THRESHOLD_PERCENT;
            }
            else
                state->report_mask &= ~(SENSOR_MASK_CT);
            break;
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS_WIDEBAND
        case SNS_DD_SENSOR_WIDEBAND:
            feature = AMS_CONFIG_ALS_WIDEBAND;
            if (mode){
                state->report_mask |= SENSOR_MASK_WIDEBAND;
                thresh = AMS_CONFIG_ALS_THRESHOLD_PERCENT;
            }
            else
                state->report_mask &= ~(SENSOR_MASK_WIDEBAND);
            break;
#endif
#endif //CONFIG_AMS_OPTICAL_SENSOR_ALS

#ifdef CONFIG_AMS_OPTICAL_SENSOR_PROX
        case SNS_DDF_SENSOR_PROXIMITY:
            feature = AMS_CONFIG_PROX;
            if (mode){
                state->report_mask |= SENSOR_MASK_PROX;
                thresh = 1;
            }
            else
                state->report_mask &= ~(SENSOR_MASK_PROX);
            break;
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_GESTURE
        case SNS_DDF_SENSOR_IR_GESTURE:
            feature = AMS_CONFIG_GESTURE;
            if (mode){
                state->report_mask |= SENSOR_MASK_GESTURE;
                thresh = 1;
            }
            else
                state->report_mask &= ~(SENSOR_MASK_GESTURE);
            break;
#endif
        default:
            return SNS_DDF_EINVALID_ATTR;
            break;
        }
        DD_MSG_2(LOW, "sns_dd_set_attrib: sensor %d => ams_deviceSetConfig THRESHOLD and ENABLE, report_mask=0x%02x",  sensor, state->report_mask);
        ams_deviceSetConfig(&state->chip, feature, AMS_CONFIG_THRESHOLD, thresh); /* needed to generate interrupts */
        ams_deviceSetConfig(&state->chip, feature, AMS_CONFIG_ENABLE, mode);
        return SNS_DDF_SUCCESS;
        break;
    }
    case SNS_DDF_ATTRIB_POWER_STATE:
        /* Set power mode */
        {
            uint32_t mode;
            power_state = *(sns_ddf_powerstate_e *)value;
            DD_MSG_1(MED, "sns_dd_set_attrib: POWER_STATE --> %u", power_state);
            if(power_state == SNS_DDF_POWERSTATE_ACTIVE)
            {
                mode = 1;
            }
            else
            {
                /* Switch sensor OFF */
                mode = 0;
            }
            if (state->sub_dev[sub_dev_id].sensors[0] == sensor){
                state->sub_dev[sub_dev_id].powerstate[0] = mode;
            } else {
                if (state->sub_dev[sub_dev_id].sensors[1] == sensor){
                    state->sub_dev[sub_dev_id].powerstate[1] = mode;
                }
            }
            switch ( sensor )
            {
            case SNS_DDF_SENSOR__ALL:
                return status;
                break;
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS
            case SNS_DDF_SENSOR_AMBIENT:
                feature = AMS_CONFIG_ALS_LUX;
                break;
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS_RGB
            case SNS_DDF_SENSOR_RGB:
                feature = AMS_CONFIG_ALS_RGB;
                break;
            case SNS_DDF_SENSOR_CT_C:
                feature = AMS_CONFIG_ALS_CT;
                break;
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS_WIDEBAND
            case SNS_DD_SENSOR_WIDEBAND:
                feature = AMS_CONFIG_ALS_WIDEBAND;
                break;
#endif
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_PROX
            case SNS_DDF_SENSOR_PROXIMITY:
                feature = AMS_CONFIG_PROX;
                break;
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_GESTURE
            case SNS_DDF_SENSOR_IR_GESTURE:
                feature = AMS_CONFIG_GESTURE;
                break;
#endif
            default:
                return SNS_DDF_EINVALID_ATTR;
                break;
            }
            ams_deviceSetConfig(&state->chip, feature, AMS_CONFIG_ENABLE, mode);
        }
        break;
    default:
            DD_MSG_1(LOW, "Invalid Attribute: %d", attrib);
            return SNS_DDF_EINVALID_ATTR;
    }

  return status;
}

/*===========================================================================

FUNCTION:   sns_dd_get_attrib

===========================================================================*/
/**
* @brief Retrieves the value of an attribute for a sensor.
*
* @param[in]  dd_handle   Handle to a driver instance.
* @param[in]  sensor      Sensor whose attribute is to be retrieved. When
*                         addressing an attribute that refers to the driver
*                         this value is set to SNS_DDF_SENSOR__ALL.
* @param[in]  attrib      Attribute to be retrieved.
* @param[in]  memhandler  Memory handler used to dynamically allocate
*                         output parameters, if applicable.
* @param[out] value       Pointer that this function will allocate or set
*                         to the attribute's value.
* @param[out] num_elems   Number of elements in @a value.
*
* @return Success if the attribute was retrieved and the buffer was
*         populated. Otherwise a specific error code is returned.
*/
/*=========================================================================*/
sns_ddf_status_e sns_dd_get_attrib
(
    sns_ddf_handle_t        dd_handle,
    sns_ddf_sensor_e        sensor,
    sns_ddf_attribute_e     attrib,
    sns_ddf_memhandler_s*   memhandler,
    void**                  value,
    uint32_t*               num_elems
)
{
    sns_dd_ams_t* state = (sns_dd_ams_t*)(((uint32_t)dd_handle) & (uint32_t)(~DD_HANDLE_ALIGN));
    uint32_t      sub_dev_id = (uint32_t)dd_handle & ((uint32_t)DD_HANDLE_ALIGN);

    DD_MSG_1(ERROR,"sns_dd_get_attrib: Sensor %d", sensor);

    /* Input sanity check */
    if (state == NULL)
    {
        return SNS_DDF_EINVALID_PARAM;
    }

    switch(sensor)
    {
    case SNS_DDF_SENSOR__ALL:
    case SNS_DDF_SENSOR__NONE:
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS
    case SNS_DDF_SENSOR_AMBIENT:
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS_RGB
    case SNS_DDF_SENSOR_RGB:
    case SNS_DDF_SENSOR_CT_C:
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS_WIDEBAND
    case SNS_DD_SENSOR_WIDEBAND:
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_PROX
    case SNS_DDF_SENSOR_PROXIMITY:
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_GESTURE
    case SNS_DDF_SENSOR_IR_GESTURE:
#endif
        break;
    default:
        DD_MSG_1(MED, "Be sure to add the appropriate sensor in your build script to match the config file %d", sensor);
        return SNS_DDF_EINVALID_PARAM;
    }

    //DD_MSG_0(LOW, "sns_dd_get_attrib: => ams_getDeviceInfo");
    ams_deviceInfo_t info;
    ams_getDeviceInfo(&info);

    switch(attrib)
    {
    case SNS_DDF_ATTRIB_REGISTRY_GROUP:
    {
        sns_ddf_registry_group_s *  reg_group;
        sns_ddf_nv_calibration_data_t * nv_memory_calibrationData;

        DD_MSG_0(LOW, "SNS_DDF_ATTRIB_REGISTRY_GROUP");

        if ((reg_group = sns_ddf_memhandler_malloc_ex(memhandler, sizeof(sns_ddf_registry_group_s), state->sub_dev[sub_dev_id].smgr_handle)) == NULL )
        {
            return SNS_DDF_ENOMEM;
        }

        if ((nv_memory_calibrationData = sns_ddf_memhandler_malloc_ex(memhandler, 128, state->sub_dev[sub_dev_id].smgr_handle)) == NULL )
        {
            return SNS_DDF_ENOMEM;
        }
        reg_group->group_data = (uint8_t*) nv_memory_calibrationData;
        reg_group->size = 128; /* must be 128; if lesser, data will not be written to NV */

        {
            uint32_t checkSum = 0;
            uint8_t i;
            memcpy(&nv_memory_calibrationData->ams_data, &state->calibrationData, sizeof(ams_calibrationData_t));
            nv_memory_calibrationData->als_factor = (nv_memory_calibrationData->ams_data.alsCalibrationFactor / 10);
            nv_memory_calibrationData->near_threshold = nv_memory_calibrationData->ams_data.proxHardThreshold;
            for(i=0; i<sizeof(sns_ddf_nv_calibration_data_t); i++ ){
                checkSum += reg_group->group_data[i];
                checkSum ++;
                checkSum &= 0xFF;
            }
            reg_group->group_data[sizeof(sns_ddf_nv_calibration_data_t)] = checkSum;
        }
        AMS_PORT_log_1("nv_memory_calibrationData->als_factor     = %d\n", nv_memory_calibrationData->als_factor);
        AMS_PORT_log_1("nv_memory_calibrationData->near_threshold = %d\n", nv_memory_calibrationData->near_threshold);
        *(sns_ddf_registry_group_s**)value = reg_group;
        *num_elems = 1;
        return SNS_DDF_SUCCESS;
    }
    case SNS_DDF_ATTRIB_POWER_INFO:
    {
        sns_ddf_power_info_s* power_attrib;
        if ((*value = sns_ddf_memhandler_malloc_ex(
                        memhandler,
                        sizeof(sns_ddf_power_info_s) , state->sub_dev[sub_dev_id].smgr_handle)) == NULL)
        {
            return SNS_DDF_ENOMEM;
        }
        power_attrib  = (sns_ddf_power_info_s *)(*value);
        *num_elems    = 1;

        {
            switch ( sensor )
            {
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS
                case SNS_DDF_SENSOR_AMBIENT:
                case SNS_DDF_SENSOR_RGB:
                case SNS_DDF_SENSOR_CT_C:
                case SNS_DD_SENSOR_WIDEBAND:
                /* Value is unit of uA */
                power_attrib->active_current = info.alsSensor.activeCurrent_uA;
                power_attrib->lowpower_current = info.alsSensor.standbyCurrent_uA;
                DD_MSG_0(LOW, "SNS_DDF_ATTRIB_POWER_INFO SNS_DDF_SENSOR_AMBIENT");
                break;
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_PROX
                case SNS_DDF_SENSOR_PROXIMITY:
                /* Value is unit of uA */
                power_attrib->active_current = info.proxSensor.activeCurrent_uA;
                power_attrib->lowpower_current = info.proxSensor.standbyCurrent_uA;
                DD_MSG_0(LOW, "SNS_DDF_ATTRIB_POWER_INFO SNS_DDF_SENSOR_PROXIMITY");
                break;
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_GESTURE
                case SNS_DDF_SENSOR_IR_GESTURE:
                /* Value is unit of uA */
                power_attrib->active_current = info.gestureSensor.activeCurrent_uA;
                power_attrib->lowpower_current = info.gestureSensor.standbyCurrent_uA;
                DD_MSG_0(LOW, "SNS_DDF_ATTRIB_POWER_INFO SNS_DDF_SENSOR_IR_GESTURE");
                break;
#endif
                default:
                return SNS_DDF_EINVALID_ATTR;
                break;
            }
        }
    }
      break;

    case SNS_DDF_ATTRIB_RANGE:
      {
        sns_ddf_range_s *device_ranges;
        if ((*value = sns_ddf_memhandler_malloc_ex(
                memhandler,
                sizeof(sns_ddf_range_s) , state->sub_dev[sub_dev_id].smgr_handle)) == NULL)
        {
            return SNS_DDF_ENOMEM;
        }

        device_ranges  = (sns_ddf_range_s *)(*value);
        *num_elems     = 1;

        {
            switch ( sensor )
            {
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS
                case SNS_DDF_SENSOR_AMBIENT:
                case SNS_DDF_SENSOR_RGB:
                case SNS_DDF_SENSOR_CT_C:
                case SNS_DD_SENSOR_WIDEBAND:
                /* Value is unit of sensor in Q16 format */
                device_ranges->min = FX_FLTTOFIX_Q16(info.alsSensor.rangeMin);
                device_ranges->max = FX_FLTTOFIX_Q16(info.alsSensor.rangeMax);
                DD_MSG_0(LOW, "SNS_DDF_ATTRIB_RANGE SNS_DDF_SENSOR_PROXIMITY");
                break;
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_PROX
                case SNS_DDF_SENSOR_PROXIMITY:
                /* Value is unit of sensor in Q16 format */
                device_ranges->min = FX_FLTTOFIX_Q16(info.proxSensor.rangeMin);
                device_ranges->max = FX_FLTTOFIX_Q16(0.05);
                DD_MSG_0(LOW, "SNS_DDF_ATTRIB_RANGE SNS_DDF_SENSOR_PROXIMITY");
                break;
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_GESTURE
                case SNS_DDF_SENSOR_IR_GESTURE:
                /* Value is unit of sensor in Q16 format */
                device_ranges->min = FX_FLTTOFIX_Q16(0.01);
                device_ranges->max = FX_FLTTOFIX_Q16(10000);
                DD_MSG_0(LOW, "SNS_DDF_ATTRIB_RANGE SNS_DDF_SENSOR_GESTURE");
                break;
#endif
                default:
                return SNS_DDF_EINVALID_ATTR;
                break;
            }
        }
      }
      break;
    case SNS_DDF_ATTRIB_RESOLUTION_ADC:
      {
        sns_ddf_resolution_adc_s *device_res_adc;
        if ((*value = sns_ddf_memhandler_malloc_ex(
                memhandler,
                sizeof(sns_ddf_resolution_adc_s), state->sub_dev[sub_dev_id].smgr_handle)) == NULL)
        {
          return SNS_DDF_ENOMEM;
        }

        device_res_adc  = (sns_ddf_resolution_adc_s *)(*value);
        *num_elems      = 1;

        {
            switch ( sensor )
            {
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS
                case SNS_DDF_SENSOR_AMBIENT:
                case SNS_DDF_SENSOR_RGB:
                case SNS_DDF_SENSOR_CT_C:
                case SNS_DD_SENSOR_WIDEBAND:
                /* Value is unit of sensor in Q16 format */
                device_res_adc->bit_len = info.alsSensor.adcBits;
                device_res_adc->max_freq = 20;
                DD_MSG_0(LOW, "SNS_DDF_ATTRIB_RESOLUTION_ADC SNS_DDF_SENSOR_AMBIENT");
                break;
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_PROX
                case SNS_DDF_SENSOR_PROXIMITY:
                /* Value is unit of sensor in Q16 format */
                device_res_adc->bit_len = info.proxSensor.adcBits;
                device_res_adc->max_freq = 20;
                DD_MSG_0(LOW, "SNS_DDF_ATTRIB_RESOLUTION_ADC SNS_DDF_SENSOR_PROXIMITY");
                break;
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_GESTURE
                case SNS_DDF_SENSOR_IR_GESTURE:
                /* Value is unit of sensor in Q16 format */
                device_res_adc->bit_len = info.proxSensor.adcBits;
                device_res_adc->max_freq = 20;
                DD_MSG_0(LOW, "SNS_DDF_ATTRIB_RESOLUTION_ADC SNS_DDF_SENSOR_IR_GESTURE");
                break;
#endif
                default:
                return SNS_DDF_EINVALID_ATTR;
                break;
            }
        }
      }
      break;
    case SNS_DDF_ATTRIB_RESOLUTION:
      {
        sns_ddf_resolution_t *device_res;
        if ((*value = sns_ddf_memhandler_malloc_ex(
                memhandler,
                sizeof(sns_ddf_resolution_t), state->sub_dev[sub_dev_id].smgr_handle)) == NULL)
        {
            return SNS_DDF_ENOMEM;
        }
        DD_MSG_0(LOW, "SNS_DDF_ATTRIB_RESOLUTION");
        /* Value is in Q16 in sensor unit */
        device_res  = (sns_ddf_resolution_t *)(*value);
        *num_elems  = 1;
        *device_res = FX_FLTTOFIX_Q16(1);
      }
      break;
#if 0
    case SNS_DDF_ATTRIB_DRIVER_INFO:
      {
        sns_ddf_driver_info_s *driver_info;
        if ((*value = sns_ddf_memhandler_malloc_ex(
                memhandler,
                sizeof(sns_ddf_driver_info_s), state->sub_dev[sub_dev_id].smgr_handle)) == NULL)
        {
          return SNS_DDF_ENOMEM;
        }

        driver_info  = (sns_ddf_driver_info_s *)(*value);
        *num_elems   = 1;

        {
            switch ( sensor )
            {
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS
                case SNS_DDF_SENSOR_AMBIENT:
                case SNS_DDF_SENSOR_RGB:
                case SNS_DDF_SENSOR_CT_C:
                /* Value is unit of sensor in Q16 format */
                if (sensor == SNS_DDF_SENSOR_AMBIENT) driver_info->name = "AMS ALS";
                if (sensor == SNS_DDF_SENSOR_RGB)     driver_info->name = "AMS RGB";
                if (sensor == SNS_DDF_SENSOR_CT_C)    driver_info->name = "AMS CT";
                driver_info->version = 1;
                /* driver_info->version = info.driverVersion; */
                DD_MSG_0(LOW, "SNS_DDF_ATTRIB_DRIVER_INFO CONFIG_AMS_OPTICAL_SENSOR_ALS");
                break;
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_PROX
                case SNS_DDF_SENSOR_PROXIMITY:
                /* Value is unit of sensor in Q16 format */
                driver_info->name = "AMS PROX";
                driver_info->version = 1;
                /* driver_info->version = info.driverVersion; */
                DD_MSG_0(LOW, "SNS_DDF_ATTRIB_DRIVER_INFO SNS_DDF_SENSOR_PROXIMITY");
                break;
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_GESTURE
                case SNS_DDF_SENSOR_IR_GESTURE:
                /* Value is unit of sensor in Q16 format */
                driver_info->name = "AMS GESTURE";
                driver_info->version = 1;
                /* driver_info->version = info.driverVersion; */
                DD_MSG_0(LOW, "SNS_DDF_ATTRIB_DRIVER_INFO SNS_DDF_SENSOR_IR_GESTURE");
                break;
#endif
                default:
                return SNS_DDF_EINVALID_ATTR;
                break;
            }
        }
      }
      break;
#endif
    case SNS_DDF_ATTRIB_DEVICE_INFO:
      {
        sns_ddf_device_info_s *device_info;
        if ((*value = sns_ddf_memhandler_malloc_ex(
                memhandler,
                sizeof(sns_ddf_device_info_s), state->sub_dev[sub_dev_id].smgr_handle)) == NULL)
        {
          return SNS_DDF_ENOMEM;
        }

        device_info  = (sns_ddf_device_info_s *)(*value);
        *num_elems   = 1;
        {
            device_info->model = info.deviceModel;
            device_info->vendor = "AMS TAOS";
            device_info->version = 1;
            DD_MSG_0(LOW, "SNS_DDF_ATTRIB_DEVICE_INFO");

            switch ( sensor )
            {
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS
                case SNS_DDF_SENSOR_AMBIENT:
                device_info->name = "ALS";
                break;
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS_RGB
                case SNS_DDF_SENSOR_RGB:
                device_info->name = "RGB";
                break;
                case SNS_DDF_SENSOR_CT_C:
                device_info->name = "CT";
                break;
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS_WIDEBAND
                case SNS_DD_SENSOR_WIDEBAND:
                device_info->name = "Wide ALS";
                break;
#endif
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_PROX
                case SNS_DDF_SENSOR_PROXIMITY:
                device_info->name = "PROX";
                break;
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_GESTURE
                case SNS_DDF_SENSOR_IR_GESTURE:
                device_info->name = "GESTURE";
                break;
#endif
                default:
                return SNS_DDF_EINVALID_ATTR;
                break;
            }
        }
      }
      break;
    case SNS_DDF_ATTRIB_ODR:
    {
        sns_ddf_odr_t *curr_odr;
        if((*value = sns_ddf_memhandler_malloc_ex(
                memhandler,
                sizeof(sns_ddf_odr_t), state->sub_dev[sub_dev_id].smgr_handle)) == NULL)
        {
            return SNS_DDF_ENOMEM;
        }

        curr_odr = (sns_ddf_odr_t*)(*value);
        *num_elems = 1;

        if (state->sub_dev[sub_dev_id].sensors[0] == sensor){
            *curr_odr = state->sub_dev[sub_dev_id].current_odr[0];
            DD_MSG_2(MED, "sns_dd_get_attrib: SNS_DDF_ATTRIB_ODR: sensor[0]=%u, odr = %u", sensor, *curr_odr);
        } else {
            if (state->sub_dev[sub_dev_id].sensors[1] == sensor){
                *curr_odr = state->sub_dev[sub_dev_id].current_odr[1];
                DD_MSG_2(MED, "sns_dd_get_attrib: SNS_DDF_ATTRIB_ODR: sensor[1]=%u, odr = %u", sensor, *curr_odr);
            }
        }
#if 0
        switch ( sensor )
        {
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS
        case SNS_DDF_SENSOR_AMBIENT:
        case SNS_DDF_SENSOR_RGB:
        case SNS_DDF_SENSOR_CT_C:
            *curr_odr = state->sub_dev[sub_dev_id].current_odr[0];
            DD_MSG_0(LOW, "SNS_DDF_ATTRIB_ODR SNS_DDF_SENSOR_AMBIENT");
            break;
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_PROX
        case SNS_DDF_SENSOR_PROXIMITY:
            /* TODO */
            *curr_odr = state->sub_dev[sub_dev_id].current_odr[1];
            DD_MSG_0(LOW, "SNS_DDF_ATTRIB_ODR SNS_DDF_SENSOR_PROXIMITY");
            break;
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_GESTURE
        case SNS_DDF_SENSOR_IR_GESTURE:
            /* TODO */
            *curr_odr = state->sub_dev[sub_dev_id].current_odr[0];
            DD_MSG_0(LOW, "SNS_DDF_ATTRIB_ODR SNS_DDF_SENSOR_IR_GESTURE");
            break;
#endif
        default:
            return SNS_DDF_EINVALID_ATTR;
            break;
        }
#endif
      break;
      }
    case SNS_DDF_ATTRIB_SUPPORTED_ODR_LIST:
      {
        uint32_t *odr_list;

        if((odr_list = (uint32_t *)sns_ddf_memhandler_malloc_ex(
                memhandler,
                20 * sizeof(uint32_t), state->sub_dev[sub_dev_id].smgr_handle)) == NULL)
        {
          return SNS_DDF_ENOMEM;
        }

        DD_MSG_0(LOW, "SNS_DDF_ATTRIB_SUPPORTED_ODR_LIST");
        odr_list[0] = 1;
        odr_list[1] = 5;
        odr_list[2] = 10;
        odr_list[3] = 15;
        odr_list[4] = 20;
#if 0
        odr_list[5] = 25;
        odr_list[6] = 30;
        odr_list[7] = 35;
        odr_list[8] = 40;
        odr_list[9] = 45;
        odr_list[10] = 50;
        odr_list[11] = 55;
        odr_list[12] = 60;
        odr_list[13] = 65;
        odr_list[14] = 70;
        odr_list[15] = 75;
        odr_list[16] = 80;
        odr_list[17] = 85;
        odr_list[18] = 90;
        odr_list[19] = 95;
#endif
        *value = (uint32_t *)odr_list;
        *num_elems = 5;
      }
      break;
    default:
        DD_MSG_1(LOW, "Invalid Attribute: %d", attrib);
        return SNS_DDF_EINVALID_PARAM;
    }

    DD_MSG_0(ERROR,"sns_dd_get_attrib: exit :-) ");
    return SNS_DDF_SUCCESS;
}


/*===========================================================================

FUNCTION:   sns_dd_run_test

===========================================================================*/
/**
* @brief Runs a factory test case.
*
* @param[in]  dd_handle  Handle to a driver instance.
* @param[in]  sensor     Sensor on which to run the test.
* @param[in]  test       Test case to run.
* @param[out] err        Optional driver-specific error code.
*
* @return One of the following error codes:
*     SNS_DDF_SUCCESS        - Test passed.
*     SNS_DDF_PENDING        - Test result will be sent as an event.
*     SNS_DDF_EDEVICE_BUSY   - Device is busy streaming, cannot run test.
*     SNS_DDF_EINVALID_TEST  - Test is not defined for this sensor.
*     SNS_DDF_EINVALID_PARAM - One of the parameters is invalid.
*     SNS_DDF_EFAIL          - Unknown error occurred.
*/
/*=========================================================================*/
sns_ddf_status_e sns_dd_run_test
(
    sns_ddf_handle_t    dd_handle,
    sns_ddf_sensor_e    sensor_type,
    sns_ddf_test_e      test,
    uint32_t*           err
)
{
    sns_dd_ams_t* state = (sns_dd_ams_t*)(((uint32_t)dd_handle) & (uint32_t)(~DD_HANDLE_ALIGN));
#if 0
    uint32_t      sub_dev_id = (uint32_t)dd_handle & ((uint32_t)DD_HANDLE_ALIGN);
#endif
    DD_MSG_3(MED,"sns_dd_run_test: handle=%p, sensor=%d, test=%d", dd_handle, sensor_type, test);

    /* Sanity check input */
    if (state == NULL)
    {
       return SNS_DDF_EINVALID_PARAM;
    }

    switch(sensor_type)
    {
    case SNS_DDF_SENSOR__ALL:
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS
    case SNS_DDF_SENSOR_AMBIENT:
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS_RGB
    case SNS_DDF_SENSOR_RGB:
    case SNS_DDF_SENSOR_CT_C:
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_PROX
    case SNS_DDF_SENSOR_PROXIMITY:
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_GESTURE
    case SNS_DDF_SENSOR_IR_GESTURE:
#endif
        break;
    default:
        DD_MSG_1(MED, "%s: Be sure to add the appropriate sensor in your build script to match the config file", __func__);
        return SNS_DDF_EINVALID_PARAM;
    }

    if (ams_validateDevice(state->port_handle) == false){
        return SNS_DDF_EFAIL;
    }

    switch (test)
    {
        case SNS_DDF_TEST_CONNECTIVITY:
        case SNS_DDF_TEST_SELF:
            DD_MSG_1(MED, "SNS_DDF_TEST_SELF: sensor: %d", sensor_type);
            DD_MSG_0(LOW, "sns_dd_run_test: => ams_validateDevice");
              break;
        case SNS_DDF_TEST_OEM:
            DD_MSG_1(MED, "SNS_DDF_TEST_OEM: sensor: %d", sensor_type);
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS
            if (sensor_type == SNS_DDF_SENSOR_AMBIENT){
                uint32_t odr = 45;
                uint32_t powerState = 1;
                ams_deviceInfo_t info;
                ams_getDeviceInfo(&info);
                state->calibrationData.alsCalibrationFactor  = info.defaultCalibrationData.alsCalibrationFactor;

                sns_dd_enable_sched_data(dd_handle, sensor_type, true);
                sns_dd_set_attrib(dd_handle, sensor_type, SNS_DDF_ATTRIB_POWER_STATE, &powerState);
                sns_dd_set_attrib(dd_handle, sensor_type, SNS_DDF_ATTRIB_ODR, &odr);

                DD_MSG_0(LOW, "sns_dd_run_test: => ams_deviceCalibrateLux");
                ams_deviceCalibrateLux(&state->chip, &state->calibrationData);
                state->report_mask |= SENSOR_MASK_ALS;
                return SNS_DDF_PENDING;
            }
            if (sensor_type == SNS_DDF_SENSOR_PROXIMITY){
                uint32_t odr = 45;
                uint32_t powerState = 1;

                sns_dd_enable_sched_data(dd_handle, sensor_type, true);
                sns_dd_set_attrib(dd_handle, sensor_type, SNS_DDF_ATTRIB_POWER_STATE, &powerState);
                sns_dd_set_attrib(dd_handle, sensor_type, SNS_DDF_ATTRIB_ODR, &odr);

                DD_MSG_0(LOW, "sns_dd_run_test: => ams_deviceCalibrateProx");
                ams_deviceCalibrateProx(&state->chip, &state->calibrationData);
                state->report_mask |= SENSOR_MASK_PROX;
                return SNS_DDF_PENDING;
            }
#endif
            break;
        default:
            return SNS_DDF_EINVALID_PARAM;
    }

    DD_MSG_0(ERROR,"sns_dd_run_test: exit :-) ");
    return SNS_DDF_SUCCESS;
}

/*===========================================================================

FUNCTION:   sns_dd_probe

===========================================================================*/
/**
* @brief Probes for the device with a given configuration.

* @param[in]  dev_info    Access info for physical devices controlled by
*                         this driver. Used to determine if the device is
*                         physically present.
* @param[in]  memhandler  Memory handler used to dynamically allocate
*                         output parameters, if applicable.
* @param[out] num_sensors Number of sensors supported. 0 if none.
* @param[out] sensor_type Array of sensor types supported, with num_sensor
*                         elements. Allocated by this function.
*
* @return SNS_DDF_SUCCESS if the part was probed function completed, even
*         if no device was found (in which case num_sensors will be set to
*         0).
*/
/*=========================================================================*/
sns_ddf_status_e sns_dd_probe
(
    sns_ddf_device_access_s* device_info,
    sns_ddf_memhandler_s*    memhandler,
    uint32_t*                num_sensors,
    sns_ddf_sensor_e**       sensors
)
{
  sns_ddf_status_e status;
  sns_ddf_handle_t port_handle;
  ams_deviceInfo_t info;

  *num_sensors = 0;
  *sensors = NULL;

    if ((status = sns_ddf_open_port(
            &port_handle,
            &(device_info->port_config))) != SNS_DDF_SUCCESS) {
      return status;
    }

    DD_MSG_0(LOW, "sns_dd_probe: => ams_validateDevice");
    if (ams_validateDevice(port_handle) == false){
        DD_MSG_0(ERROR, "probe: ams_validateDevice failed");
        sns_ddf_close_port(port_handle);
        return SNS_DDF_SUCCESS;
    }
    sns_ddf_close_port(port_handle);

    // Found device
    DD_MSG_0(LOW, "sns_dd_probe: => ams_getDeviceInfo");
    ams_getDeviceInfo(&info);
    *num_sensors = info.numberOfSubSensors;
    *sensors = sns_ddf_memhandler_malloc( memhandler,
                                          sizeof(sns_ddf_sensor_e) * info.numberOfSubSensors);
    if( *sensors != NULL )
    {
#ifdef CONFIG_AMS_OPTICAL_SENSOR_PROX
        (*sensors)[--info.numberOfSubSensors] = SNS_DDF_SENSOR_PROXIMITY;
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS
        (*sensors)[--info.numberOfSubSensors] = SNS_DDF_SENSOR_AMBIENT;
#endif
        status = SNS_DDF_SUCCESS;
    }
    else
    {
        return SNS_DDF_ENOMEM;
    }

  return status;
}

/*===========================================================================

FUNCTION:   sns_dd_enable_sched_data

===========================================================================*/
/**
* @brief Begins device-scheduled sampling and enables notification via Data
*        Ready Interrupts (DRI).
*
* @param[in] handle  Handle to the driver's instance.
* @param[in] sensor  Sensor to be sampled.
* @param[in] enable  True to enable or false to disable data stream.
*
* @return SNS_DDF_SUCCESS if sensor was successfully configured and
*         internal sampling has commenced or ceased. Otherwise an
*         appropriate error code.
*/
/*=========================================================================*/
sns_ddf_status_e sns_dd_enable_sched_data
(
    sns_ddf_handle_t dd_handle,
    sns_ddf_sensor_e sensor,
    bool             enable
)
{
    sns_dd_ams_t* state = (sns_dd_ams_t*)(((uint32_t)dd_handle) & (uint32_t)(~DD_HANDLE_ALIGN));
    uint32_t sub_dev_id = (uint32_t)dd_handle & ((uint32_t)DD_HANDLE_ALIGN);
    sns_ddf_status_e status = SNS_DDF_SUCCESS;

    if ( (state == NULL) || (sub_dev_id >= state->ams_max_supported_features) ) {
        DD_MSG_0(MED, "sns_dd_enable_sched_data: EXIT");
        return SNS_DDF_EINVALID_PARAM;
    }

    DD_MSG_0(MED, "sns_dd_enable_sched_data: ENTER");
    DD_MSG_1(MED, "sns_dd_enable_sched_data: sensor: %d", sensor);
    DD_MSG_1(MED, "sns_dd_enable_sched_data: enable: %d", enable);

    // set up for run.
    //

    if(enable)
    {
        if(state->sub_dev[sub_dev_id].dri_enable)
        {
            DD_MSG_0(MED, "sns_dd_enable_sched_data: dri enabled");

            DD_MSG_0(MED, "sns_dd_enable_sched_data: Enable interrupt");

            // IRQ's are enabled, register the irq
            status = sns_ddf_signal_register(state->sub_dev[sub_dev_id].interrupt_gpio,
                                             dd_handle,
                                             &TMG490x_DD_if,
                                             SNS_DDF_SIGNAL_IRQ_FALLING);
            if( status != SNS_DDF_SUCCESS )
            {
                DD_MSG_0(MED, "sns_ddf_signal_register: failed");
                return status;
            }
        }
        else
        {
            status =  SNS_DDF_EFAIL;
        }
    }
    else  // disable
    {
        ams_mode_t mode;
        ams_getMode(&state->chip, &mode);
        if (mode == MODE_OFF){
            // If NO sensors are active then deregister irq
            DD_MSG_0(MED, "enSchedData: Deregister interrupt");
            sns_ddf_signal_deregister(state->sub_dev[sub_dev_id].interrupt_gpio);
        }
    }
    DD_MSG_0(MED, "sns_dd_enable_sched_data: EXIT :-) ");
    return status;
}

/*
Processing bigImage file:
./ams_tmx490x_qcom_hd22/src/tmx490x_dev_ctrl_block/src/ams_device_control_block_init.c
*/

/*
 * Device Control Block 490x
 */

/*
 * @@AMS_REVISION_Id: e77bb8690ffdb4d13f9a92c7fe149beace30b869
 */

#if defined CONFIG_AMS_OPTICAL_SENSOR_ALS
#endif

#define HIGH    0xFF
#define LOW     0x00

typedef struct{
    uint8_t                 deviceId;
    uint8_t                 deviceIdMask;
    uint8_t                 deviceRef;
    uint8_t                 deviceRefMask;
    ams_deviceIdentifier_e  device;
}ams_deviceIdentifier_t;

static ams_deviceIdentifier_t deviceIdentifier[]={
    {0xd0,          0xff,    0x20,       0xff,        AMS_TMG4904},
    {AMS_DEVICE_ID, MASK_ID, AMS_REV_ID, MASK_REV_ID, AMS_TMG4903},
    {0, 0, 0, 0, AMS_LAST_DEVICE}
};

static void _490x_resetAllRegisters(AMS_PORT_portHndl * portHndl);
extern void _490x_update_reportTime(ams_deviceCtx_t * ctx);

static void _490x_resetAllRegisters(AMS_PORT_portHndl * portHndl){
    ams_deviceRegister_t i;

    for (i = DEVREG_ENABLE; i <= DEVREG_CFG1; i++) {
        ams_setByte(portHndl, i, deviceRegisterDefinition[i].resetValue);
    }
    for (i = DEVREG_STATUS; i < DEVREG_REG_MAX; i++) {
        ams_setByte(portHndl, i, deviceRegisterDefinition[i].resetValue);
    }
}

#ifdef CONFIG_AMS_OPTICAL_SENSOR_PROX_CCB
bool _490x_proxInit(ams_deviceCtx_t * ctx, ams_calibrationData_t * calibrationData);
bool _490x_proxInit(ams_deviceCtx_t * ctx, ams_calibrationData_t * calibrationData){

    ams_ccb_proximity_init_t proxInitData;

    proxInitData.calibrate = false;
#ifdef CONFIG_AMS_PROX_STATIC_MODE
    proxInitData.dynamicMode = false;
#else
    proxInitData.dynamicMode = true;
#endif
    proxInitData.numberAdcBits = 14;
    proxInitData.ptime_us = 50000;
    proxInitData.adcThreshold = AMS_PRX_DEFAULT_ADC_THRESHOLD;
    proxInitData.nearByHardThreshold = AMS_PRX_DEFAULT_NEARBY_HARD_THRESHOLD;
    proxInitData.nearByThresholdHysteresis = AMS_PRX_DEFAULT_THRESHOLD_HYSTERESIS;

    if (calibrationData){
        proxInitData.nearByHardThreshold = calibrationData->proxHardThreshold;
    }

    ccb_proximityInit(ctx, &proxInitData);
    return false;
}
#endif

#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS_CCB
bool _490x_alsInit(ams_deviceCtx_t * ctx, ams_calibrationData_t * calibrationData);
bool _490x_alsInit(ams_deviceCtx_t * ctx, ams_calibrationData_t * calibrationData){

    if (calibrationData == NULL) {
        ams_ccb_als_info_t infoData;
        ccb_alsInfo(&infoData);
        ctx->ccbAlsCtx.initData.calibrationData.calibrationFactor = infoData.defaultCalibrationData.calibrationFactor;
        ctx->ccbAlsCtx.initData.calibrationData.luxTarget = infoData.defaultCalibrationData.luxTarget;
        ctx->ccbAlsCtx.initData.calibrationData.luxTargetError = infoData.defaultCalibrationData.luxTargetError;
    } else {
        ctx->ccbAlsCtx.initData.calibrationData.calibrationFactor = calibrationData->alsCalibrationFactor;
        ctx->ccbAlsCtx.initData.calibrationData.luxTarget = calibrationData->alsCalibrationLuxTarget;
        ctx->ccbAlsCtx.initData.calibrationData.luxTargetError = calibrationData->alsCalibrationLuxTargetError;
    }
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS_RGB
	 if(calibrationData != NULL &&
	    calibrationData->alsCalibrationCoefR && calibrationData->alsCalibrationCoefG
	    && calibrationData->alsCalibrationCoefB && calibrationData->alsCalibrationFactorD
	    && calibrationData->alsCalibrationCoefCT && calibrationData->alsCalibrationOffsetCT) {
	 	ctx->ccbAlsCtx.ctxAlgAls.calibration.R_coef = calibrationData->alsCalibrationCoefR;
	 	ctx->ccbAlsCtx.ctxAlgAls.calibration.G_coef = calibrationData->alsCalibrationCoefG;
	 	ctx->ccbAlsCtx.ctxAlgAls.calibration.B_coef = calibrationData->alsCalibrationCoefB;
	 	ctx->ccbAlsCtx.ctxAlgAls.calibration.D_factor = calibrationData->alsCalibrationFactorD;
	 	ctx->ccbAlsCtx.ctxAlgAls.calibration.CT_coef = calibrationData->alsCalibrationCoefCT;
	 	ctx->ccbAlsCtx.ctxAlgAls.calibration.CT_offset = calibrationData->alsCalibrationOffsetCT;
	 }
#endif
    ctx->ccbAlsCtx.initData.calibrate = false;
    ctx->ccbAlsCtx.initData.configData.gain = 64000;
    ctx->ccbAlsCtx.initData.configData.uSecTime = 100000;
#ifdef CONFIG_AMS_OPTICAL_SENSOR_FLICKER
    ctx->ccbAlsCtx.initData.sampleRate = AMS_FLICKER_SAMPLERATE;
#else
    ctx->ccbAlsCtx.initData.autoGain = true;
#endif

    ccb_alsInit(ctx, &ctx->ccbAlsCtx.initData);
    return false;
}
#endif

#ifdef CONFIG_AMS_OPTICAL_SENSOR_GESTURE
#ifndef CONFIG_AMS_OPTICAL_SENSOR_PROX_CCB
#error "In order for gesture to work, prox is also needed"
#endif
extern bool _490x_gestureRegUpdate(ams_deviceCtx_t * ctx);

static bool _490x_gestureInit(ams_deviceCtx_t * ctx, ams_calibrationData_t * calibrationData){
    amsGestInitData_t algInit;
    if (calibrationData == NULL) {
        /* TODO */
    }
    algInit.mode = x_y;
    algInit.factorA = 8;
    amsAlg_gesture_initAlg(&ctx->gestureCtx, &algInit);

    return _490x_gestureRegUpdate(ctx);
}
#endif

bool ams_deviceInit(ams_deviceCtx_t * ctx, AMS_PORT_portHndl * portHndl, ams_calibrationData_t * calibrationData){

    int ret = 0;

    ctx->portHndl = portHndl;
    ctx->mode = MODE_OFF;
    ctx->systemCalibrationData = calibrationData;
    ctx->deviceId = ams_validateDevice(ctx->portHndl);
    ctx->shadowEnableReg = deviceRegisterDefinition[DEVREG_ENABLE].resetValue;
    _490x_resetAllRegisters(ctx->portHndl);
    AMS_PORT_get_timestamp_usec(&ctx->timeStamp);

#ifdef CONFIG_AMS_OPTICAL_SENSOR_PROX_CCB
    ret |= _490x_proxInit(ctx, calibrationData);
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS_CCB
    ret |= _490x_alsInit(ctx, calibrationData);
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_GESTURE
    /* be aware that prox must be initialized before gesture */
    ret |= _490x_gestureInit(ctx, calibrationData);
#endif
    ams_setByte(ctx->portHndl, DEVREG_ENABLE, ctx->shadowEnableReg);
    return ret;
}

ams_deviceIdentifier_e ams_validateDevice(AMS_PORT_portHndl * portHndl){
    uint8_t chipId;
    uint8_t revId;
    uint8_t i = 0;

    ams_getByte(portHndl, DEVREG_ID, &chipId);
    ams_getByte(portHndl, DEVREG_REVID, &revId);

    do{
        if (((chipId & deviceIdentifier[i].deviceIdMask) ==
            (deviceIdentifier[i].deviceId & deviceIdentifier[i].deviceIdMask)) &&
            ((revId & deviceIdentifier[i].deviceRefMask) ==
             (deviceIdentifier[i].deviceRef & deviceIdentifier[i].deviceRefMask))){
#ifdef CONFIG_AMS_OPTICAL_SENSOR_FLICKER
            if (deviceIdentifier[i].device != AMS_TMG4904) {
                AMS_PORT_log("FLICKER not supported in this device\n");
                return AMS_UNKNOWN_DEVICE;
            }
#endif
                return deviceIdentifier[i].device;
        }
        i++;
    }while (deviceIdentifier[i].device != AMS_LAST_DEVICE);

    AMS_PORT_log_2("ams_validateDevice: 0x%02x 0x%02x\n", chipId, revId);
    return AMS_UNKNOWN_DEVICE;
}

bool ams_getDeviceInfo(ams_deviceInfo_t * info){
    memset(info, 0, sizeof(ams_deviceInfo_t));

    info->defaultCalibrationData.timeBase_us = AMS_USEC_PER_TICK;
    info->numberOfSubSensors = 0;
    info->memorySize =  sizeof(ams_deviceCtx_t);
    info->deviceModel = "TMx490x";
    info->deviceName  = "ALS/PRX/GST";
    info->driverVersion = "Alpha";
#ifdef CONFIG_AMS_OPTICAL_SENSOR_PROX_CCB
    {
        info->defaultCalibrationData.proxHardThreshold = AMS_PRX_DEFAULT_NEARBY_HARD_THRESHOLD;
        info->proxSensor.driverName = "PROX";

        info->tableSubSensors[info->numberOfSubSensors]= AMS_PROXIMITY_SENSOR;
        info->numberOfSubSensors++;
        info->proxSensor.adcBits = 8;
        info->proxSensor.maxPolRate = 50;
        info->proxSensor.activeCurrent_uA = 100;
        info->proxSensor.standbyCurrent_uA = 5;
        info->proxSensor.rangeMax = 1;
        info->proxSensor.rangeMin = 0;
    }
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS_CCB
    {
        /* TODO */
        ams_ccb_als_info_t infoData;
        ccb_alsInfo(&infoData);
        info->tableSubSensors[info->numberOfSubSensors]= AMS_AMBIENT_SENSOR;
        info->numberOfSubSensors++;

        info->alsSensor.driverName = infoData.algName;
        info->alsSensor.adcBits = 8;
        info->alsSensor.maxPolRate = 50;
        info->alsSensor.activeCurrent_uA = 100;
        info->alsSensor.standbyCurrent_uA = 5;
        info->alsSensor.rangeMax = 32767;
        info->alsSensor.rangeMin = 0;

        info->defaultCalibrationData.alsCalibrationFactor = infoData.defaultCalibrationData.calibrationFactor;
        info->defaultCalibrationData.alsCalibrationLuxTarget = infoData.defaultCalibrationData.luxTarget;
        info->defaultCalibrationData.alsCalibrationLuxTargetError = infoData.defaultCalibrationData.luxTargetError;
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS_WIDEBAND
        info->tableSubSensors[info->numberOfSubSensors]= AMS_WIDEBAND_ALS_SENSOR;
        info->numberOfSubSensors++;
#endif
    }
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_GESTURE
    {
        amsGestureAlgoInfo_t infoGest;
        amsAlg_gesture_getAlgInfo(&infoGest);

        info->tableSubSensors[info->numberOfSubSensors]= AMS_GESTURE_SENSOR;
        info->numberOfSubSensors++;
        info->proxSensor.adcBits = 16;
        info->proxSensor.maxPolRate = 50;
        info->proxSensor.activeCurrent_uA = 100;
        info->proxSensor.standbyCurrent_uA = 5;
        info->proxSensor.driverName = infoGest.algName;
        info->proxSensor.rangeMax = 1;
        info->proxSensor.rangeMin = 0;
    }
#endif
    return false;
}
