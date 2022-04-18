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
  04/11/2017  SQ   Corrected the lux value when the lux value is negative value
  04/04/2017  RB   Fixed first indication always reported as FAR state in Proximity Polling mode. 
  09/21/2016  BD   Fix memory issue for ALS and Prox in polling mode
  09/16/2016  PB   Reject invalid als and CCT samples generated in polling mode
  08/30/2016  PB   DAF support from Vendor
  08/15/2016  PB   Fix Klocwork issues
============================================================================*/

#include "sns_dd_ams_tmg4903_qcom.h"


/*
Processing uImage file:
./ams_tmx490x_qcom_hd22/src/algorithm_als/src/ams_als_API_config.c
*/

/*
 * Device Algorithm ALS
 */

/*
 * @@AMS_REVISION_Id: cee780370eb22b17f687d78123b4575fb8205b88
 */

#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS

extern void als_update_statics(amsAlsContext_t * ctx);

int amsAlg_als_setConfig(amsAlsContext_t * ctx, amsAlsConf_t * inputData){
    int ret = 0;

    if (inputData != NULL) {
        ctx->gain = inputData->gain;
        ctx->time_us = inputData->time_us;
    }
    als_update_statics(ctx);
    return ret;
}

/*
 * getConfig: is used to quarry the algorithm's configuration
 */
int amsAlg_als_getConfig(amsAlsContext_t * ctx, amsAlsConf_t * outputData){
    int ret = 0;

    outputData->gain = ctx->gain;
    outputData->time_us = ctx->time_us;

    return ret;
}
#endif

/*
Processing uImage file:
./ams_tmx490x_qcom_hd22/src/algorithm_als/src/ams_als_API_process.c
*/

/*
 * Device Algorithm ALS
 */

/*
 * @@AMS_REVISION_Id: cee780370eb22b17f687d78123b4575fb8205b88
 */

#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS

int amsAlg_als_processData(amsAlsContext_t * ctx, amsAlsDataSet_t * inputData){
    int ret = 0;

    if (inputData->status & ALS_STATUS_RDY){
        ctx->previousLux = ctx->results.mLux;
        if (ctx->previousGain != ctx->gain){
            als_update_statics(ctx);
        } else {
            ctx->notStableMeasurement = false;
        }
#if defined(CONFIG_AMS_OPTICAL_SENSOR_ALS_RGB) || defined(CONFIG_AMS_OPTICAL_SENSOR_ALS_WIDEBAND)
        als_compute_data(ctx, inputData);
#endif
#if defined CONFIG_AMS_OPTICAL_SENSOR_ALS_CLEAR
        als_compute_data_clear(ctx, inputData);
#endif
        als_ave_LUX(ctx);
    }

    if (ctx->adaptive){
        if (inputData->status & ALS_STATUS_OVFL){
            ctx->results.adaptive = ADAPTIVE_ALS_GAIN_DEC_REQUEST;
        } else {
            ctx->results.adaptive = als_adaptive(ctx, inputData);
        }
    } else {
        ctx->results.adaptive = ADAPTIVE_ALS_NO_REQUEST;
    }

    if (ctx->notStableMeasurement) {
        ctx->results.mLux = ctx->previousLux;
    }
    return ret;
}
#endif

/*
Processing uImage file:
./ams_tmx490x_qcom_hd22/src/algorithm_als/src/ams_als_API_result.c
*/

/*
 * Device Algorithm ALS
 */

/*
 * @@AMS_REVISION_Id: cee780370eb22b17f687d78123b4575fb8205b88
 */

#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS

/*
 * getResult: will return the output generated by the algorithm
 */

int amsAlg_als_getResult(amsAlsContext_t * ctx, amsAlsResult_t * outData){
    int ret = 0;

    outData->rawClear  = ctx->results.rawClear;
    outData->rawRed  = ctx->results.rawRed;
    outData->rawGreen  = ctx->results.rawGreen;
    outData->rawBlue  = ctx->results.rawBlue;
    outData->irrBlue  = ctx->results.irrBlue;
    outData->irrClear = ctx->results.irrClear;
    outData->irrGreen = ctx->results.irrGreen;
    outData->irrRed   = ctx->results.irrRed;
    outData->irrWideband = ctx->results.irrWideband;
    outData->mLux_ave  = ctx->results.mLux_ave / AMS_LUX_AVERAGE_COUNT;
    outData->IR  = ctx->results.IR;
    outData->CCT = ctx->results.CCT;
    outData->adaptive = ctx->results.adaptive;
    if (ctx->notStableMeasurement) {
        ctx->notStableMeasurement = false;
    }
    outData->mLux = ctx->results.mLux;

    return ret;
}
#endif

/*
Processing uImage file:
./ams_tmx490x_qcom_hd22/src/algorithm_als/src/ams_als_core.c
*/

/*
 * Device Algorithm ALS
 */

/*
 * @@AMS_REVISION_Id: cee780370eb22b17f687d78123b4575fb8205b88
 */

/* see Application Note:
 * DN40-Rev 1.0 – Lux and CCT Calculations using ams Color Sensors
 */
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS

#define AMS_ROUND_SHFT_VAL                      4
#define AMS_ROUND_ADD_VAL                       (1 << (AMS_ROUND_SHFT_VAL - 1))

#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS_RGB
static void als_calc_LUX_CCT (amsAlsContext_t * ctx,
                                uint16_t redADC,
                                uint16_t greenADC,
                                uint16_t blueADC) {
    int32_t rp1;
    int32_t gp1;
    int32_t bp1;
    int32_t lux = 0;

    rp1 = redADC   - ctx->results.IR;
    gp1 = greenADC - ctx->results.IR;
    bp1 = blueADC  - ctx->results.IR;

    if (redADC > ctx->results.IR)
    {
        lux += (int32_t)(ctx->calibration.R_coef * rp1);
    }
    if (greenADC > ctx->results.IR)
    {
        lux += (int32_t)(ctx->calibration.G_coef * gp1);
    }
    if (blueADC > ctx->results.IR)
    {
        lux += (int32_t)((int32_t)ctx->calibration.B_coef * bp1);
    }	
	if (lux < 0) 
	{
	    lux = 0;
	} else {
        lux <<= AMS_ROUND_SHFT_VAL;
        if (lux < (LONG_MAX / ctx->calibration.calibrationFactor)) {
            lux = (lux * ctx->calibration.calibrationFactor) / ctx->cpl;
        } else {
            lux = (lux / ctx->cpl ) * ctx->calibration.calibrationFactor;
        }
        lux += AMS_ROUND_ADD_VAL;
        lux >>= AMS_ROUND_SHFT_VAL; 
    }
	ctx->results.mLux = lux;
	
    if (rp1 == 0 ) rp1 = 1;
    ctx->results.CCT = ((ctx->calibration.CT_coef * bp1) / rp1) + ctx->calibration.CT_offset;
}
#endif

void als_update_statics(amsAlsContext_t * ctx) {
    uint64_t tempCpl;
    uint64_t tempTime_us = ctx->time_us;
    uint64_t tempGain = ctx->gain;

    /* test for the potential of overflowing */
    uint32_t maxOverFlow = (uint64_t)ULLONG_MAX / ctx->time_us;
    if (maxOverFlow < ctx->gain) {
        /* TODO: need to find use-case to test */
        tempCpl = ((tempTime_us / 2) * (tempGain / 2)) / (AMS_ALS_GAIN_FACTOR/4) ;
    } else {
        tempCpl = (tempTime_us * tempGain) / AMS_ALS_GAIN_FACTOR;
    }
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS_CLEAR
    ctx->cpl = tempCpl / ctx->calibration.DGL_factor;
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS_RGB
    if (tempCpl > (((uint32_t)ULONG_MAX))){
        /* if we get here, we have an problem */
        while(1);
    }
    ctx->cpl = tempCpl / ctx->calibration.D_factor;
#endif

#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS_259x
    if (ctx->time_us > AMS_ALS_TIMEBASE) {
        ctx->saturation = (uint16_t)USHRT_MAX;
    } else {
        ctx->saturation = AMS_ALS_ADC_MAX_COUNT;
    }
#else
    {
        int32_t max_count = ((AMS_ALS_ADC_MAX_COUNT) * ctx->time_us) / ctx->calibration.Time_base;
        if(max_count > (((uint32_t)ULONG_MAX))) {
            ctx->saturation = (uint16_t)USHRT_MAX;
        } else {
            ctx->saturation = (uint16_t)max_count; /* TODO: need to validate more all devices */
        }
    }
#endif
    ctx->previousGain = ctx->gain;
    {
        /* just changed settings, lux readings could be jumpy */
        ctx->notStableMeasurement = true;
    }
}

#if defined(CONFIG_AMS_OPTICAL_SENSOR_ALS_RGB) || defined(CONFIG_AMS_OPTICAL_SENSOR_ALS_WIDEBAND)
void als_compute_data (amsAlsContext_t * ctx, amsAlsDataSet_t * inputData) {
    uint32_t tempIr;

#if defined(CONFIG_AMS_OPTICAL_SENSOR_ALS_WIDEBAND)
    uint16_t widebandADC = inputData->datasetArray->greenADC;

    AMS_PORT_log_3("als_compute_data: cpl=%u, Wbc factor=%u, greenWbADC=%u", ctx->cpl, ctx->calibration.Wbc, widebandADC);
    AMS_PORT_log_3("als_compute_data: WB CRB coefs = (%u, %u, %u)", ctx->calibration.Wideband_C_factor, ctx->calibration.Wideband_R_factor, ctx->calibration.Wideband_B_factor);
    ctx->results.irrWideband = (widebandADC * (ctx->calibration.Wbc / CPU_FRIENDLY_FACTOR_1024)) / ctx->cpl;

    ctx->results.IR = 0;
    if (widebandADC < (uint16_t)SHRT_MAX)){
        /* Substitute derived green reading for actual */
        inputData->datasetArray->greenADC = ( (inputData->datasetArray->clearADC * ctx->calibration.Wideband_C_factor)
                                              - (inputData->datasetArray->redADC * ctx->calibration.Wideband_R_factor)
                                              - (inputData->datasetArray->blueADC * ctx->calibration.Wideband_B_factor)
                                            ) / AMS_WIDEBAND_SCALE_FACTOR;
        AMS_PORT_log_3("als_compute_data: IR = %u - %u = %u", widebandADC, inputData->datasetArray->clearADC, ctx->results.IR);
        AMS_PORT_log_3("als_compute_data: R = %u, B = %u, G' = %u", inputData->datasetArray->redADC, inputData->datasetArray->blueADC, inputData->datasetArray->greenADC);
    }
#endif

    if (inputData->datasetArray->clearADC < (uint16_t)USHRT_MAX){
        /* Calculate IR */
        tempIr = inputData->datasetArray->redADC +
                            inputData->datasetArray->greenADC +
                            inputData->datasetArray->blueADC;
        if (tempIr > inputData->datasetArray->clearADC) {
            ctx->results.IR = (tempIr - inputData->datasetArray->clearADC) / 2;
        } else {
            ctx->results.IR = 0;
        }

        /* Compute irradiances in uW/cm^2 */
        ctx->results.rawClear = inputData->datasetArray->clearADC;
        ctx->results.rawRed = inputData->datasetArray->redADC;
        ctx->results.rawGreen = inputData->datasetArray->greenADC;
        ctx->results.rawBlue = inputData->datasetArray->blueADC;
        ctx->results.irrRed = (inputData->datasetArray->redADC * (ctx->calibration.Rc / CPU_FRIENDLY_FACTOR_1024)) / ctx->cpl;
        ctx->results.irrClear = (inputData->datasetArray->clearADC * (ctx->calibration.Cc / CPU_FRIENDLY_FACTOR_1024)) / ctx->cpl;
        ctx->results.irrBlue = (inputData->datasetArray->blueADC * (ctx->calibration.Bc / CPU_FRIENDLY_FACTOR_1024)) / ctx->cpl;
        ctx->results.irrGreen = (inputData->datasetArray->greenADC * (ctx->calibration.Gc / CPU_FRIENDLY_FACTOR_1024)) / ctx->cpl;
#if defined(CONFIG_AMS_OPTICAL_SENSOR_ALS_WIDEBAND)
        AMS_PORT_log_2("als_compute_data: irrClear = %u, irrWideband = %u"
                        , ctx->results.irrClear
                        , ctx->results.irrWideband
                        );
#else
        AMS_PORT_log_1("als_compute_data: irrClear = %u"
                        , ctx->results.irrClear
                        );
#endif
        AMS_PORT_log_3("als_compute_data: irrRed = %u, irrGreen = %u, irrBlue = %u"
                        , ctx->results.irrRed
                        , ctx->results.irrGreen
                        , ctx->results.irrBlue
                       );

        als_calc_LUX_CCT(ctx, inputData->datasetArray->redADC,
            inputData->datasetArray->greenADC,
            inputData->datasetArray->blueADC);
    } else {
        /* measurement is saturated */
        AMS_PORT_log("als_compute_data:  saturated");
    }
}
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS_CLEAR
void als_compute_data_clear (amsAlsContext_t * ctx, amsAlsDataSet_t * inputData) {
    uint64_t lux1 = 0;
    uint64_t lux2 = 0;

    if (inputData->datasetArray->ch0ADC < (uint16_t)USHRT_MAX){

        lux1 = ((inputData->datasetArray->ch0ADC * AMS_ALS_FACTOR) - (ctx->calibration.L1_factor * inputData->datasetArray->ch1ADC));
        lux2 = ((ctx->calibration.L2_factor * inputData->datasetArray->ch0ADC) - (ctx->calibration.L3_factor * inputData->datasetArray->ch1ADC));

        if (lux1 > lux2) {
            ctx->results.mLux = (lux1 * ctx->calibration.calibrationFactor) / ctx->cpl;
        } else {
            ctx->results.mLux = (lux2 * ctx->calibration.calibrationFactor) / ctx->cpl;
        }
    } else {
        ctx->results.mLux = 0;
    }
}
#endif

void als_ave_LUX (amsAlsContext_t * ctx) {

    /* if average queue isn't full (at startup), fill it */
    if(ctx->ave_lux[AMS_LUX_AVERAGE_COUNT - 1] == 0) {
        ctx->results.mLux_ave = 0;
        ctx->ave_lux_index = 0;
        do {
            ctx->ave_lux[ctx->ave_lux_index++] = ctx->results.mLux;
            ctx->results.mLux_ave += ctx->results.mLux;
        } while (ctx->ave_lux_index < AMS_LUX_AVERAGE_COUNT);
        ctx->ave_lux_index = 1;
    } else {
        /* replace the oldest LUX value with the new LUX value */
        ctx->results.mLux_ave -= ctx->ave_lux[ctx->ave_lux_index];
        ctx->ave_lux[ctx->ave_lux_index] = ctx->results.mLux;
        ctx->results.mLux_ave += ctx->ave_lux[ctx->ave_lux_index];
        ctx->ave_lux_index ++;
    }

    if (ctx->ave_lux_index == AMS_LUX_AVERAGE_COUNT) {
        ctx->ave_lux_index = 0;
    }
}

amsAlsAdaptive_t als_adaptive(amsAlsContext_t * ctx, amsAlsDataSet_t * inputData){
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS_RGB
    if (inputData->status & ALS_STATUS_OVFL) {
        ctx->results.adaptive = ADAPTIVE_ALS_TIME_DEC_REQUEST;
    } else {
        if (inputData->datasetArray->clearADC == (uint16_t)USHRT_MAX){
            if (ctx->gain != 0){
                return ADAPTIVE_ALS_GAIN_DEC_REQUEST;
            } else {
                return ADAPTIVE_ALS_TIME_DEC_REQUEST;
            }
        } else {
            if (ctx->gain != 0) {
                if (inputData->datasetArray->clearADC >= ctx->saturation){
                    return ADAPTIVE_ALS_GAIN_DEC_REQUEST;
                }
            } else {
                if (inputData->datasetArray->clearADC >= ctx->saturation){
                    return ADAPTIVE_ALS_TIME_DEC_REQUEST;
                }
            }
            if (inputData->datasetArray->clearADC <= 0xff){
                return ADAPTIVE_ALS_GAIN_INC_REQUEST;
            }
        }
    }
#else
    ctx++; inputData++; /* avoid compiler warning */
#endif
    return ADAPTIVE_ALS_NO_REQUEST;
}

void als_getDefaultCalibrationData(amsAlsCalibration_t * data)
{
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS_RGB
        data->R_coef = AMS_ALS_R_COEF;
        data->G_coef = AMS_ALS_G_COEF;
        data->B_coef = AMS_ALS_B_COEF;
        data->Rc = AMS_ALS_Rc;
        data->Gc = AMS_ALS_Gc;
        data->Bc = AMS_ALS_Bc;
        data->Cc = AMS_ALS_Cc;
        data->D_factor = AMS_ALS_D_FACTOR;
        data->CT_coef = AMS_ALS_CT_COEF;
        data->CT_offset = AMS_ALS_CT_OFFSET;
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS_CLEAR
        data->DGL_factor = AMS_ALS_DGL_FACTOR;
        data->L1_factor = AMS_ALS_L1_FACTOR;
        data->L2_factor = AMS_ALS_L2_FACTOR;
        data->L3_factor = AMS_ALS_L3_FACTOR;
#endif
        data->Time_base = AMS_ALS_TIMEBASE;
        data->thresholdLow = AMS_ALS_THRESHOLD_LOW;
        data->thresholdHigh = AMS_ALS_THRESHOLD_HIGH;
        data->calibrationFactor = AMS_CONFIG_ALS_CAL_FACTOR;
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS_WIDEBAND
        data->Wbc = AMS_ALS_Wbc;
        data->Wideband_C_factor = AMS_ALS_WB_C_FACTOR;
        data->Wideband_R_factor = AMS_ALS_WB_R_FACTOR;
        data->Wideband_B_factor = AMS_ALS_WB_B_FACTOR;
#endif
}
#endif

/*
Processing uImage file:
./ams_tmx490x_qcom_hd22/src/algorithm_gesture/src/ams_gesture_API_config.c
*/

/*
 * Device Algorithm Gesture (Basic)
 */

/*
 * @@AMS_REVISION_Id: 0943d97e723a716129efe0aad203025bdebfbecb
 */


/*
 * setConfig: is used to re-configure the algorithm during run-time
 */
int amsAlg_gesture_setConfig(amsGestContext_t * ctx, amsGestConf_t * inputData){
    int ret = 0;

    ctx->state = gesture_init;

    if (inputData != NULL) {
        ctx->mode = inputData->mode;
    }
    return ret;
}

/*
 * getConfig: is used to quarry the algorithm's configuration
 */
int amsAlg_gesture_getConfig(amsGestContext_t * ctx, amsGestConf_t * outputData){
    int ret = 0;

    /* remove compiler warning */
    ctx++;
    outputData++;

    return ret;
}

/*
Processing uImage file:
./ams_tmx490x_qcom_hd22/src/algorithm_gesture/src/ams_gesture_API_process.c
*/

/*
 * Device Algorithm Gesture (Basic)
 */

/*
 * @@AMS_REVISION_Id: 0943d97e723a716129efe0aad203025bdebfbecb
 */

extern void process_gesture_stateMachine_fourPoint(amsGestContext_t * ctx);
extern void process_gesture_stateMachine_pushRelease(amsGestContext_t * ctx);
extern void process_gesture_x_y(amsGestContext_t * ctx);

int amsAlg_gesture_processData(amsGestContext_t * ctx, amsGestDataSet_t * inputData){
    int ret = 0;

    ctx->gestRawData = inputData->datasetArray;

    if ((inputData->timeStamp - ctx->lastTimeStamp) > MILLISEC_500  ) {
        /* new set of data. be sure the state-machine start restart. */
        ctx->state = gesture_init;
    }
    ctx->lastTimeStamp = inputData->timeStamp;

    switch (ctx->mode)
    {
        case x_y:
            process_gesture_x_y(ctx);
            process_gesture_stateMachine_pushRelease(ctx);
            break;
#if 0
        case four_point_plus_push:
            process_gesture_stateMachine_fourPoint(ctx);
            process_gesture_stateMachine_pushRelease(ctx);
            break;
        case four_point:
            process_gesture_stateMachine_fourPoint(ctx);
            break;
#endif
        default:
            break;
    }

    return ret;
}

/*
Processing uImage file:
./ams_tmx490x_qcom_hd22/src/algorithm_gesture/src/ams_gesture_API_result.c
*/

/*
 * Device Algorithm Gesture (Basic)
 */

/*
 * @@AMS_REVISION_Id: 0943d97e723a716129efe0aad203025bdebfbecb
 */


extern enum gestureEvent getResultFourPoint(amsGestContext_t * ctx);

/*
 * getResult: will return the output generated by the algorithm
 */

int amsAlg_gesture_getResult(amsGestContext_t * ctx, amsGestResult_t * outData){
    int ret = 0;

    outData->event = unknown_gestureEvent;

    switch (ctx->mode)
    {
#if 0
        case four_point_plus_push:
        case four_point:
#endif
        case x_y:
            if (((ctx->entryPoint != unknown_gesturePoint) && (ctx->exitPoint != unknown_gesturePoint)) || ctx->entryPoint == center){
                outData->event = getResultFourPoint(ctx);
                        outData->strongEntryPoint = ctx->strongEntryPoint;
                        outData->strongExitPoint  = ctx->strongExitPoint;
            }
            break;
        default:
            break;
    }
    return ret;
}

/*
Processing uImage file:
./ams_tmx490x_qcom_hd22/src/algorithm_gesture/src/ams_gesture_core.c
*/

/*
 * Device Algorithm Gesture (Basic)
 */

/*
 * @@AMS_REVISION_Id: 0943d97e723a716129efe0aad203025bdebfbecb
 */


gestureEvent_t getResultFourPoint(amsGestContext_t * ctx);
gestureEvent_t getResultEightPoint(amsGestContext_t * ctx);
void process_gesture_stateMachine_pushRelease(amsGestContext_t * ctx);
void process_gesture_stateMachine_fourPoint(amsGestContext_t * ctx);

#if 0
static void gesture_resetVariables (amsGestContext_t * ctx){
    ctx->lastHighestDeltaAccumulator = 0;
    ctx->gestDeltaWeight.weightEastWest = 0;
    ctx->gestDeltaWeight.weightNorthSouth = 0;
    ctx->gestSum.north = 0;
    ctx->gestSum.south = 0;
    ctx->gestSum.east = 0;
    ctx->gestSum.west = 0;
}

static void gesture_setOffset(gestureAPIData_t *offset, gestureAPIData_t *data)
{
    offset->north = data->north / 8;
    offset->south = data->south / 8;
    offset->east = data->east / 8;
    offset->west = data->west / 8;
}

static void gesture_sum(gestureData_t *total, gestureAPIData_t *data, gestureAPIData_t *offset)
{
    total->north += (data->north - offset->north);
    total->south += (data->south - offset->south);
    total->east += (data->east - offset->east);
    total->west += (data->west - offset->west);
}
#endif

gestureEvent_t getResultEightPoint(amsGestContext_t * ctx)
{
    enum gestureEvent eventResult = unknown_gestureEvent;

    /* remove compiler warning */
    ctx++;

    return eventResult;
}

gestureEvent_t getResultFourPoint(amsGestContext_t * ctx)
{
    enum gestureEvent eventResult = unknown_gestureEvent;

    switch (ctx->entryPoint)
    {
        case unknown_gesturePoint:
        {
            if (ctx->exitPoint == center) {
                eventResult = pushedAndReleased;
            }
            break;
        }
        case center:
        {
            if (ctx->state == gesture_ending) {
                eventResult = pushedAndReleased;
            } else {
                eventResult = pushedAndHold;
            }
            break;
        }
        case north:
        {
            switch (ctx->exitPoint)
            {
                case south:
                case south_east:
                case south_west:
                    eventResult = northToSouth;
                    break;
                case north:
                case east:
                case west:
                default:
                    break;
            }
            break;
        }
        case south:
        {
            switch (ctx->exitPoint)
            {
                case north:
                case north_east:
                case north_west:
                    eventResult = southToNorth;
                    break;
                case south:
                case east:
                case west:
                default:
                    break;
            }
            break;
        }
        case east:
        {
            switch (ctx->exitPoint)
            {
                case west:
                case north_west:
                case south_west:
                    eventResult = eastToWest;
                    break;
                case east:
                case north:
                case south:
                default:
                    break;

            }
            break;
        }
        case west:
        {
            switch (ctx->exitPoint)
            {
                case east:
                case north_east:
                case south_east:
                    eventResult = westToEast;
                    break;
                case north:
                case south:
                case west:
                default:
                    break;

            }
            break;
        }
        case north_east:
        case north_west:
        case south_east:
        case south_west:
            break;
        default:
            break;
    }
    return eventResult;
}

static void gestureXYave(amsGestureXY_t * gestXY, int32_t northSouth, int32_t eastWest){
    gestXY->northSouthAve -= gestXY->xyBuffer[gestXY->bufferIndex].northSouth;
    gestXY->eastWestAve -= gestXY->xyBuffer[gestXY->bufferIndex].eastWest;

    gestXY->northSouthAve += northSouth;
    gestXY->eastWestAve += eastWest;

    gestXY->xyBuffer[gestXY->bufferIndex].northSouth = northSouth;
    gestXY->xyBuffer[gestXY->bufferIndex].eastWest = eastWest;

    gestXY->bufferIndex++;
    if (gestXY->bufferIndex == gestXY->xyBufferSize) {
        gestXY->bufferIndex = 0;
    }
}

static enum gesturePoint gesturePointCalculation(amsGestContext_t * ctx){
    enum gesturePoint result = unknown_gesturePoint;

    if (ctx->gestureXY.northSouthAve > 0) {
        /* north */
        if (ctx->gestureXY.eastWestAve > 0) {
            /* east */
            if (abs(ctx->gestureXY.northSouthAve) > abs(ctx->gestureXY.eastWestAve)) {
                result = north;
            } else {
                result = east;
            }
        } else {
            if (abs(ctx->gestureXY.northSouthAve) > abs(ctx->gestureXY.eastWestAve)) {
                result = north;
            } else {
                result = west;
            }
        }
    } else {
        /* south */
        if (ctx->gestureXY.eastWestAve > 0) {
            /* east */
            if (abs(ctx->gestureXY.northSouthAve) > abs(ctx->gestureXY.eastWestAve)) {
                result = south;
            } else {
                result = east;
            }
        } else {
            if (abs(ctx->gestureXY.northSouthAve) > abs(ctx->gestureXY.eastWestAve)) {
                result = south;
            } else {
                result = west;
            }
        }
    }
    return result;
}

void process_gesture_x_y(amsGestContext_t * ctx);
void process_gesture_x_y(amsGestContext_t * ctx){
    int32_t northSouth;
    int32_t eastWest;

    northSouth = ctx->gestRawData->north - ctx->gestRawData->south;
    eastWest = ctx->gestRawData->east - ctx->gestRawData->west;

    switch (ctx->state)
    {
        case gesture_init:
            memset(&ctx->gestureXY, 0, sizeof(amsGestureXY_t));
            ctx->gestureXY.xyBufferSize = ctx->factorA;
            ctx->state = gesture_started;
        case gesture_started:
        case gesture_active:
        case gesture_buttonDown:
            gestureXYave(&ctx->gestureXY, northSouth, eastWest);
            if (ctx->state == gesture_started) {
                if((ctx->gestRawData->north > (ctx->targetOffset * 2) ) &&
                   (ctx->gestRawData->south > (ctx->targetOffset * 2) ) &&
                   (ctx->gestRawData->east  > (ctx->targetOffset * 2) ) &&
                   (ctx->gestRawData->west  > (ctx->targetOffset * 2) )){
                    ctx->state = gesture_active;
                    ctx->entryPoint = gesturePointCalculation(ctx);
#if 0
                    if (abs(ctx->gestureXY.northSouthAve) > abs(ctx->gestureXY.eastWestAve)){
                        ctx->strongEntryPoint = abs(ctx->gestureXY.northSouthAve);
                    } else {
                        ctx->strongEntryPoint = abs(ctx->gestureXY.eastWestAve);
                    }
#else
                    if (abs(ctx->gestureXY.northSouthAve) > abs(ctx->gestureXY.eastWestAve)){
                        ctx->strongEntryPoint = abs(ctx->gestureXY.northSouthAve) - abs(ctx->gestureXY.eastWestAve);
                    } else {
                        ctx->strongEntryPoint = abs(ctx->gestureXY.eastWestAve) - abs(ctx->gestureXY.northSouthAve);
                    }
#endif
                }
            } else {
                if((ctx->gestRawData->north < (ctx->targetOffset * 2) ) &&
                   (ctx->gestRawData->south < (ctx->targetOffset * 2) ) &&
                   (ctx->gestRawData->east  < (ctx->targetOffset * 2) ) &&
                   (ctx->gestRawData->west  < (ctx->targetOffset * 2) )){
                    ctx->state = gesture_ending;
                    ctx->exitPoint = gesturePointCalculation(ctx);
#if 0
                    if (abs(ctx->gestureXY.northSouthAve) > abs(ctx->gestureXY.eastWestAve)){
                        ctx->strongExitPoint = abs(ctx->gestureXY.northSouthAve);
                    } else {
                        ctx->strongExitPoint = abs(ctx->gestureXY.eastWestAve);
                    }
#else
                    if (abs(ctx->gestureXY.northSouthAve) > abs(ctx->gestureXY.eastWestAve)){
                        ctx->strongExitPoint = abs(ctx->gestureXY.northSouthAve) - abs(ctx->gestureXY.eastWestAve);
                    } else {
                        ctx->strongExitPoint = abs(ctx->gestureXY.eastWestAve) - abs(ctx->gestureXY.northSouthAve);
                    }
#endif
                }
            }
            break;
        case gesture_ending:
            gestureXYave(&ctx->gestureXY, northSouth, eastWest);
            break;
        default:
            break;
    }
}

void process_gesture_stateMachine_pushRelease(amsGestContext_t * ctx)
{
    switch (ctx->state)
    {
        case gesture_active:
            ctx->activeCounter ++;
            if (ctx->pushDetectTime < ctx->activeCounter) {
                    ctx->state = gesture_buttonDown;
                    ctx->entryPoint = center;
            }
            break;
        case gesture_ending:
        case gesture_started:
            ctx->activeCounter = 0;
            break;
        default:
            break;
    }
}

#if 0
void process_gesture_stateMachine_fourPoint(amsGestContext_t * ctx)
{
    int32_t deltaNorthSouth;
    int32_t deltaEastWest;

    switch (ctx->state)
    {
        case gesture_init:
        {
            gesture_resetVariables(ctx);
            gesture_setOffset(&ctx->gestOffset, ctx->gestRawData);
            gesture_sum(&ctx->gestSum, ctx->gestRawData, &ctx->gestOffset);

            ctx->state = gesture_started;
            ctx->entryPoint = unknown_gesturePoint;
            ctx->exitPoint = unknown_gesturePoint;
            ctx->eventResult = unknown_gestureEvent;
            ctx->activeCounter = 0;

            break;
        }
        case gesture_started:
        {
            /*
             * This state is active during the gesture's ramping up phase
             *
             * We calculate the delta sum between the sensors
             * When summing, the deltas will become bigger,
             * and easier to determine the gesture point.
             *
             */
            gesture_sum(&ctx->gestSum, ctx->gestRawData, &ctx->gestOffset);

            deltaNorthSouth = ctx->gestSum.north - ctx->gestSum.south;
            deltaEastWest = ctx->gestSum.east - ctx->gestSum.west;

            ctx->gestDeltaWeight.weightNorthSouth += deltaNorthSouth;
            ctx->gestDeltaWeight.weightEastWest += deltaEastWest;

            if (abs(ctx->gestDeltaWeight.weightNorthSouth) >= abs(ctx->gestDeltaWeight.weightEastWest)) {
                uint32_t temp = abs(deltaNorthSouth);
                if ( temp >= ctx->lastHighestDeltaAccumulator) {
                    ctx->lastHighestDeltaAccumulator = temp;
                } else {
                    ctx->state = gesture_active;
                    if (deltaNorthSouth > 0) {
                        ctx->entryPoint = north;
                        gesture_resetVariables(ctx);
                        gesture_sum(&ctx->gestSum, ctx->gestRawData, &ctx->gestOffset);
                    } else {
                        ctx->entryPoint = south;
                        gesture_resetVariables(ctx);
                        gesture_sum(&ctx->gestSum, ctx->gestRawData, &ctx->gestOffset);
                    }
                }
            } else {
                uint32_t temp = abs(deltaEastWest);
                if (temp >= ctx->lastHighestDeltaAccumulator) {
                    ctx->lastHighestDeltaAccumulator = temp;
                } else {
                    ctx->state = gesture_active;
                    if (deltaEastWest > 0) {
                        ctx->entryPoint = east;
                        gesture_resetVariables(ctx);
                        gesture_sum(&ctx->gestSum, ctx->gestRawData, &ctx->gestOffset);
                    } else {
                        ctx->entryPoint = west;
                        gesture_resetVariables(ctx);
                        gesture_sum(&ctx->gestSum, ctx->gestRawData, &ctx->gestOffset);
                    }
                }
            }
            break;
        }
        case gesture_active:
        {
            /* in this state, its waiting for the measurements to ramp down
             * This is often in PressAndHold gestures.
             */

            gesture_sum(&ctx->gestSum, ctx->gestRawData, &ctx->gestOffset);

            deltaNorthSouth = ctx->gestSum.north - ctx->gestSum.south;
            deltaEastWest = ctx->gestSum.east - ctx->gestSum.west;

            ctx->gestDeltaWeight.weightNorthSouth += deltaNorthSouth;
            ctx->gestDeltaWeight.weightEastWest += deltaEastWest;

            {
                int32_t temp = abs(deltaNorthSouth) - abs(deltaEastWest);
                if (temp / 8) {
                    ctx->state = gesture_ending;
                }
            }

            break;
        }
        case gesture_ending:
        {
            gesture_sum(&ctx->gestSum, ctx->gestRawData, &ctx->gestOffset);

            deltaNorthSouth = ctx->gestSum.north - ctx->gestSum.south;
            deltaEastWest = ctx->gestSum.east - ctx->gestSum.west;

            ctx->gestDeltaWeight.weightNorthSouth += deltaNorthSouth;
            ctx->gestDeltaWeight.weightEastWest += deltaEastWest;

            if (abs(ctx->gestDeltaWeight.weightNorthSouth) >= abs(ctx->gestDeltaWeight.weightEastWest)) {
                if (deltaNorthSouth > 0) {
                    ctx->exitPoint = north;
                } else {
                    ctx->exitPoint = south;
                }
            } else {
                if (deltaEastWest > 0) {
                    ctx->exitPoint = east;

                } else {
                    ctx->exitPoint = west;
                }
            }
            break;
        }
        case gesture_buttonDown:
        {
            uint32_t sum = ctx->gestRawData->north +
                    ctx->gestRawData->south +
                    ctx->gestRawData->east +
                    ctx->gestRawData->west;
            if (sum < 100) ctx->state = gesture_ending;
            break;
        }
        default:
            break;
    }
}
#endif

/*
Processing uImage file:
./ams_tmx490x_qcom_hd22/src/ccb_als/src/core_control_block_als.c
*/

/*
 * Core Control Block ALS
 */

/*
 * @@AMS_REVISION_Id: 20854d55e9fee8b0787b60f02b2fd249dd246aff
 */


void ccb_alsInit(void * dcbCtx, ams_ccb_als_init_t* initData){
    ams_deviceCtx_t * ctx = (ams_deviceCtx_t*)dcbCtx;
    ams_ccb_als_ctx_t * ccbCtx = &ctx->ccbAlsCtx;
    amsAlsInitData_t initAlsData;
    amsAlsAlgoInfo_t infoAls;

    if (initData){
        memcpy(&ccbCtx->initData, initData, sizeof(ams_ccb_als_init_t));
    } else {
        ccbCtx->initData.calibrate = false;
    }

    initAlsData.adaptive = false;
    initAlsData.irRejection = false;
    initAlsData.gain = ccbCtx->initData.configData.gain;
    /* quantize the integration time */
    alsTimeUsToReg(ccbCtx->initData.configData.uSecTime, &ccbCtx->initData.configData.uSecTime);
    initAlsData.time_us = ccbCtx->initData.configData.uSecTime;
    amsAlg_als_getAlgInfo (&infoAls);
    infoAls.calibrationData.calibrationFactor = ccbCtx->initData.calibrationData.calibrationFactor;
    amsAlg_als_initAlg(&ccbCtx->ctxAlgAls, &initAlsData, &infoAls.calibrationData);

    ams_setWord(ctx->portHndl, DEVREG_AILTHL, 0xffff);
    ams_setWord(ctx->portHndl, DEVREG_AIHTHL, 0x0000);

    if (ccbCtx->initData.calibrate){
        ccbCtx->state = AMS_CCB_ALS_CALIBRATION_INIT;
    } else {
        ccbCtx->state = AMS_CCB_ALS_INIT;
    }
}

void ccb_alsGetConfig(void * dcbCtx, ams_ccb_als_config_t * configData){
    ams_ccb_als_ctx_t * ccbCtx = &((ams_deviceCtx_t*)dcbCtx)->ccbAlsCtx;

    configData->threshold = ccbCtx->initData.configData.threshold;
}

void ccb_alsSetConfig(void * dcbCtx, ams_ccb_als_config_t * configData){
    ams_ccb_als_ctx_t * ccbCtx = &((ams_deviceCtx_t*)dcbCtx)->ccbAlsCtx;

    ccbCtx->initData.configData.threshold = configData->threshold;
}

bool ccb_alsHandle(void * dcbCtx, ams_ccb_als_dataSet_t * alsData){
    ams_deviceCtx_t * ctx = (ams_deviceCtx_t*)dcbCtx;
    ams_ccb_als_ctx_t * ccbCtx = &((ams_deviceCtx_t*)dcbCtx)->ccbAlsCtx;
    amsAlsDataSet_t inputDataAls;
    typedef struct _fifo{
        uint16_t AdcClear;
        uint16_t AdcRed;
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS_WIDEBAND
        uint16_t AdcGreenWb;
#else
        uint16_t AdcGreen;
#endif
        uint16_t AdcBlue;
    } adcDataSet_t;
    adcDataSet_t adcData = { 0 };

#if 0
    AMS_PORT_log_1("ccb_alsHandle: case = %u\n", ccbCtx->state);
    ams_getBuf(ctx->portHndl, DEVREG_CLR_CHANLO, (uint8_t *)&adcData, 8);
    AMS_PORT_log_4("ccb_alsHandle: C,R,G,B = %u, %u,%u,%u\n"
        , adcData.AdcClear
        , adcData.AdcRed
        , adcData.AdcGreen
        , adcData.AdcBlue
        );
#endif

    switch (ccbCtx->state){
    case AMS_CCB_ALS_INIT:
        AMS_PORT_log("ccb_alsHandle: AMS_CCB_ALS_INIT\n");
        /* stop ALS before changing its parameters */
        ams_tmg490x_setField(ctx->portHndl, DEVREG_ENABLE, LOW, (MASK_AEN | MASK_AIEN ));
        ams_setByte(ctx->portHndl, DEVREG_ATIME, alsTimeUsToReg(ccbCtx->initData.configData.uSecTime, &ccbCtx->initData.configData.uSecTime));
        ams_tmg490x_setField(ctx->portHndl, DEVREG_PERS, 0x01, MASK_APERS);
        ams_tmg490x_setField(ctx->portHndl, DEVREG_CFG1, HIGH, MASK_ASIEN);
        ams_tmg490x_setField(ctx->portHndl, DEVREG_CFG1, alsGainToReg(ctx->ccbAlsCtx.initData.configData.gain), MASK_AGAIN);
        ccbCtx->shadowAiltReg = 0xffff;
        ccbCtx->shadowAihtReg = 0;
        /* force interrupt */
        ams_setWord(ctx->portHndl, DEVREG_AILTHL, 0xffff);
        ams_setWord(ctx->portHndl, DEVREG_AIHTHL, 0x0000);
        ccbCtx->state = AMS_CCB_ALS_RGB;
        break;
    case AMS_CCB_ALS_RGB: /* state to measure RGB */
    if (alsData->statusReg & (AINT)){
        ams_getBuf(ctx->portHndl, DEVREG_CLR_CHANLO, (uint8_t *)&adcData, 8);
        inputDataAls.status = ALS_STATUS_RDY;
        inputDataAls.datasetArray = (alsData_t*)&adcData;
        if (ccbCtx->initData.configData.threshold){
            uint32_t tempThresh;

            tempThresh = (((uint32_t)adcData.AdcClear * (100 - (uint32_t)(ccbCtx->initData.configData.threshold))) + 50) / 100;
            ccbCtx->shadowAiltReg = (uint16_t)tempThresh;
            tempThresh = (((uint32_t)adcData.AdcClear * (100 + (uint32_t)(ccbCtx->initData.configData.threshold))) + 50) / 100;
            ccbCtx->shadowAihtReg = (uint16_t)tempThresh;
            ams_setWord(ctx->portHndl, DEVREG_AILTHL, ccbCtx->shadowAiltReg);
            ams_setWord(ctx->portHndl, DEVREG_AIHTHL, ccbCtx->shadowAihtReg);
        }
        amsAlg_als_processData(&ctx->ccbAlsCtx.ctxAlgAls, &inputDataAls);
        ctx->updateAvailable |= (1 << AMS_AMBIENT_SENSOR);
#if 1
        AMS_PORT_log_1("ccb_alsHandle: Clear    = %d\n", adcData.AdcClear);
        AMS_PORT_log_1("ccb_alsHandle: Red      = %d\n", adcData.AdcRed);
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS_WIDEBAND
        AMS_PORT_log_1("ccb_alsHandle: Green    = %d\n", adcData.AdcGreenWb);
#else
        AMS_PORT_log_1("ccb_alsHandle: Green    = %d\n", adcData.AdcGreen);
#endif
        AMS_PORT_log_1("ccb_alsHandle: Blue     = %d\n", adcData.AdcBlue);
        AMS_PORT_log_1("ccb_alsHandle: IR       = %d\n", ctx->ccbAlsCtx.ctxAlgAls.results.IR);
        AMS_PORT_log_1("ccb_alsHandle: aveLux   = %d\n", ctx->ccbAlsCtx.ctxAlgAls.results.mLux_ave / AMS_LUX_AVERAGE_COUNT );
        AMS_PORT_log_1("ccb_alsHandle: CT       = %d\n", ctx->ccbAlsCtx.ctxAlgAls.results.CCT);
        AMS_PORT_log_1("ccb_alsHandle: factor   = %d\n", ctx->ccbAlsCtx.ctxAlgAls.calibration.calibrationFactor);
        AMS_PORT_log_1("ccb_alsHandle: timeUs   = %d\n", ctx->ccbAlsCtx.ctxAlgAls.time_us);
        AMS_PORT_log_1("ccb_alsHandle: gain     = %d\n", ctx->ccbAlsCtx.ctxAlgAls.gain);
#endif
        ccbCtx->state = AMS_CCB_ALS_RGB;
        if (ccbCtx->initData.autoGain == false)
            break;
        /* else no break */
    } else {
        break;
    }
    case AMS_CCB_ALS_AUTOGAIN:
    {
        uint64_t temp;
        uint32_t recommendedGain;
        uint32_t adcObjective = ctx->ccbAlsCtx.ctxAlgAls.saturation * 128;
        adcObjective /= 160; /* about 80% (128 / 160) */

        temp = adcObjective * 2048; /* 2048 to avoid floating point operation later on */
        temp /= adcData.AdcClear;
        temp *= ctx->ccbAlsCtx.ctxAlgAls.gain;
        temp /= 2048;

        recommendedGain = temp & 0xffffffff;
#if 0
        AMS_PORT_log_4("ccb_alsHandle: AMS_CCB_ALS_AUTOGAIN: sat=%u, objctv=%u, cur=%u, rec=%u\n"
            , ctx->ccbAlsCtx.ctxAlgAls.saturation
            , adcObjective
            , ctx->ccbAlsCtx.ctxAlgAls.gain
            , recommendedGain
            );
#endif
        recommendedGain = alsGainToReg(recommendedGain);
        recommendedGain = alsGain_conversion[recommendedGain];
        if (recommendedGain != ctx->ccbAlsCtx.ctxAlgAls.gain){
            AMS_PORT_log_1("ccb_alsHandle: AMS_CCB_ALS_AUTOGAIN: change gain to: %u\n", recommendedGain);
            ctx->ccbAlsCtx.ctxAlgAls.gain = recommendedGain;
            /* stop ALS before changing its parameters */
            ams_tmg490x_setField(ctx->portHndl, DEVREG_ENABLE, LOW, (MASK_AEN | MASK_AIEN ));
            ams_tmg490x_setField(ctx->portHndl, DEVREG_CFG1, alsGainToReg(ctx->ccbAlsCtx.ctxAlgAls.gain), MASK_AGAIN);
        }
        else
          AMS_PORT_log_1("ccb_alsHandle: AMS_CCB_ALS_AUTOGAIN: no change, gain=%u\n", ctx->ccbAlsCtx.ctxAlgAls.gain);

    }
    break;
    case AMS_CCB_ALS_CALIBRATION_INIT:
    if (alsData->statusReg & (AINT)){
        ams_tmg490x_setField(ctx->portHndl, DEVREG_ENABLE, LOW, (MASK_AEN | MASK_AIEN ));
        ams_setByte(ctx->portHndl, DEVREG_ATIME, alsTimeUsToReg(ccbCtx->initData.configData.uSecTime, &ccbCtx->initData.configData.uSecTime));
        ams_tmg490x_setField(ctx->portHndl, DEVREG_PERS, 0x01, MASK_APERS);
        ams_tmg490x_setField(ctx->portHndl, DEVREG_CFG1, HIGH, MASK_ASIEN);
        ams_tmg490x_setField(ctx->portHndl, DEVREG_CFG1, alsGainToReg(ctx->ccbAlsCtx.initData.configData.gain), MASK_AGAIN);
        ccbCtx->shadowAiltReg = 0xffff;
        ccbCtx->shadowAihtReg = 0;
        ams_setWord(ctx->portHndl, DEVREG_AILTHL, ccbCtx->shadowAiltReg);
        ams_setWord(ctx->portHndl, DEVREG_AIHTHL, ccbCtx->shadowAihtReg);

        ccbCtx->state = AMS_CCB_ALS_CALIBRATION_COLLECT_DATA;
        ccbCtx->ctxAlgAls.ave_lux[AMS_LUX_AVERAGE_COUNT - 1] = 0;
    }
    break;
    case AMS_CCB_ALS_CALIBRATION_COLLECT_DATA:
    if (alsData->statusReg & (AINT)){
        ams_getBuf(ctx->portHndl, DEVREG_CLR_CHANLO, (uint8_t *)&adcData, 8);
        inputDataAls.status = ALS_STATUS_RDY;
        inputDataAls.datasetArray = (alsData_t*)&adcData;
        amsAlg_als_processData(&ctx->ccbAlsCtx.ctxAlgAls, &inputDataAls);
        ccbCtx->bufferCounter += 1;
        AMS_PORT_log_1("AMS_CCB_ALS_CALIBRATION_COLLECT_DATA = %d\n", ccbCtx->bufferCounter);
        if (ccbCtx->bufferCounter == (AMS_LUX_AVERAGE_COUNT - 1)){
            uint32_t avaLux = ctx->ccbAlsCtx.ctxAlgAls.results.mLux_ave / AMS_LUX_AVERAGE_COUNT;
            uint32_t factor = (ccbCtx->initData.calibrationData.luxTarget * ctx->ccbAlsCtx.ctxAlgAls.calibration.calibrationFactor) / (avaLux / 1000);
            ctx->ccbAlsCtx.ctxAlgAls.calibration.calibrationFactor = factor;

            AMS_PORT_log_1("ccb_alsHandle: target = %d\n", ccbCtx->initData.calibrationData.luxTarget);
            AMS_PORT_log_1("ccb_alsHandle: mLux   = %d\n", ctx->ccbAlsCtx.ctxAlgAls.results.mLux);
            AMS_PORT_log_1("ccb_alsHandle: aveLux = %d\n", avaLux);
            AMS_PORT_log_1("ccb_alsHandle: factor = %d\n", factor);

            ccbCtx->bufferCounter = 0;
            ccbCtx->ctxAlgAls.ave_lux[AMS_LUX_AVERAGE_COUNT - 1] = 0;
            ccbCtx->state = AMS_CCB_ALS_CALIBRATION_CHECK;
        }
    }
    break;
    case AMS_CCB_ALS_CALIBRATION_CHECK:
    if (alsData->statusReg & (AINT)){
        ams_getBuf(ctx->portHndl, DEVREG_CLR_CHANLO, (uint8_t *)&adcData, 8);
        inputDataAls.status = ALS_STATUS_RDY;
        inputDataAls.datasetArray = (alsData_t*)&adcData;
        amsAlg_als_processData(&ctx->ccbAlsCtx.ctxAlgAls, &inputDataAls);

        ccbCtx->bufferCounter += 1;
        if (ccbCtx->bufferCounter == (AMS_LUX_AVERAGE_COUNT - 1)){
            uint32_t avaLux = ctx->ccbAlsCtx.ctxAlgAls.results.mLux_ave / AMS_LUX_AVERAGE_COUNT;
            uint32_t error = 0;
            ccbCtx->bufferCounter = 0;
            AMS_PORT_log_1("ccb_alsHandle: target = %d\n", ccbCtx->initData.calibrationData.luxTarget);
            AMS_PORT_log_1("ccb_alsHandle: toler. = %d\n", ccbCtx->initData.calibrationData.luxTargetError);
            AMS_PORT_log_1("ccb_alsHandle: mLux   = %d\n", ctx->ccbAlsCtx.ctxAlgAls.results.mLux);
            AMS_PORT_log_1("ccb_alsHandle: aveLux = %d\n", ctx->ccbAlsCtx.ctxAlgAls.results.mLux_ave / AMS_LUX_AVERAGE_COUNT );
            AMS_PORT_log_1("ccb_alsHandle: factor = %d\n", ctx->ccbAlsCtx.ctxAlgAls.calibration.calibrationFactor);
                ccbCtx->state = AMS_CCB_ALS_INIT;
                ccbCtx->initData.calibrate = false;
            avaLux /= 1000; /* mLux to lux */
            if (avaLux > ccbCtx->initData.calibrationData.luxTarget){
                error = avaLux - ccbCtx->initData.calibrationData.luxTarget;
            } else {
                error = ccbCtx->initData.calibrationData.luxTarget - avaLux;
            }
            if (error < ccbCtx->initData.calibrationData.luxTargetError){
                AMS_PORT_log("AMS_CCB_ALS_CALIBRATION_CHECK pass\n");
                ctx->updateAvailable = AMS_CALIBRATION_DONE;
                ctx->systemCalibrationData->alsCalibrationFactor = ctx->ccbAlsCtx.ctxAlgAls.calibration.calibrationFactor;
            } else {
                AMS_PORT_log("AMS_CCB_ALS_CALIBRATION_CHECK fail\n");
                ctx->updateAvailable = AMS_CALIBRATION_DONE_BUT_FAILED;
                ctx->ccbAlsCtx.ctxAlgAls.calibration.calibrationFactor = ctx->systemCalibrationData->alsCalibrationFactor;
            }
        }
    }
    break;
    default:
        ccbCtx->state = AMS_CCB_ALS_RGB;
    break;
    }
    return false;
}

void ccb_alsGetResult(void * dcbCtx, ams_ccb_als_result_t * exportData){
    ams_ccb_als_ctx_t * ccbCtx = &((ams_deviceCtx_t*)dcbCtx)->ccbAlsCtx;

    /* export data */
    if ((ccbCtx->ctxAlgAls.results.rawClear >= ccbCtx->ctxAlgAls.saturation) || (ccbCtx->ctxAlgAls.notStableMeasurement)){
        exportData->mLux = 0; /* indicate invalid reading */
    } else {
        if (ccbCtx->ctxAlgAls.results.mLux == 0)
            exportData->mLux = 1; /* if extremely low but valid */
        else
            exportData->mLux = ccbCtx->ctxAlgAls.results.mLux;
    }
    exportData->colorTemp = ccbCtx->ctxAlgAls.results.CCT;
    exportData->clear = ccbCtx->ctxAlgAls.results.irrClear;
    exportData->blue = ccbCtx->ctxAlgAls.results.irrBlue;
    exportData->green = ccbCtx->ctxAlgAls.results.irrGreen;
    exportData->red = ccbCtx->ctxAlgAls.results.irrRed;
    exportData->ir = ccbCtx->ctxAlgAls.results.IR;
    exportData->wideband = ccbCtx->ctxAlgAls.results.irrWideband;
    exportData->rawClear = ccbCtx->ctxAlgAls.results.rawClear;
    exportData->rawRed = ccbCtx->ctxAlgAls.results.rawRed;
    exportData->rawGreen = ccbCtx->ctxAlgAls.results.rawGreen;
    exportData->rawBlue = ccbCtx->ctxAlgAls.results.rawBlue;
}

/*
Processing uImage file:
./ams_tmx490x_qcom_hd22/src/ccb_proximity_dynamic_a/src/core_control_block_dyn_prox.c
*/

/*
 * Core Control Block Dynamic Proximity
 */

/*
 * @@AMS_REVISION_Id: ebd0a567719248739d0a97343b53df481d4d1773
 */


uint32_t AMS_NORMALISE_16(uint32_t data, uint32_t dataSize);
uint32_t AMS_NORMALISE_16(uint32_t data, uint32_t dataSize){
    uint32_t temp = (16 - dataSize);
    return (data << temp);
}

void ccb_proximityInit(void * dcbCtx, ams_ccb_proximity_init_t* initData){
    ams_deviceCtx_t * ctx = (ams_deviceCtx_t*)dcbCtx;
    ams_ccb_proximity_ctx_t * ccbCtx = &((ams_deviceCtx_t*)dcbCtx)->ccbProxCtx;

    ccbCtx->nearBy = false;
    ccbCtx->sensitivity = 3;
    if (initData){
        memcpy(&ccbCtx->initData, initData, sizeof(ams_ccb_proximity_init_t));
    } else {
        ccbCtx->initData.adcThreshold = AMS_PRX_DEFAULT_ADC_THRESHOLD;
        ccbCtx->initData.nearByHardThreshold = AMS_PRX_DEFAULT_NEARBY_HARD_THRESHOLD;
        ccbCtx->initData.nearByThresholdHysteresis = AMS_PRX_DEFAULT_THRESHOLD_HYSTERESIS;
        ccbCtx->initData.dynamicMode = true;
        AMS_PORT_log("ccb_proximityInit: please check numberAdcBits\n");
        ccbCtx->initData.numberAdcBits = 16;
        ccbCtx->initData.ptime_us = 30000;
    }

    ams_setByte(ctx->portHndl,  DEVREG_PTIME,  proxTimeToReg(ccbCtx->initData.ptime_us));
    ams_tmg490x_setField(ctx->portHndl, DEVREG_PERS,   AMS_PRX_PERS_TO_REG(2), MASK_PPERS);
    ams_tmg490x_setField(ctx->portHndl, DEVREG_PGCFG0, AMS_PRX_DEFAULT_PULSE_LENGTH << 6, MASK_PPLEN);
    ams_tmg490x_setField(ctx->portHndl, DEVREG_PGCFG0, AMS_PRX_DEFAULT_PULSE_COUNT, MASK_PPULSE);
    ams_tmg490x_setField(ctx->portHndl, DEVREG_PGCFG1, PGAIN_4, MASK_PGAIN);
    ams_tmg490x_setField(ctx->portHndl, DEVREG_PGCFG1, 6 << 1, MASK_PGLDRIVE);
    ams_setWord(ctx->portHndl,  DEVREG_PIHTL, (0x0000));
    ams_setWord(ctx->portHndl,  DEVREG_PILTL, (0xffff));
    if (ccbCtx->initData.dynamicMode == true) {
    ams_tmg490x_setField(ctx->portHndl, DEVREG_CAL_CFG1, HIGH, 0x40);
    }

    ccbCtx->state = PRX_STATE_BEGIN;

    /* ccbCtx->state = PRX_STATE_STATIC_DETECT; */
}

void ccb_proximitySetConfig(void * dcbCtx, ams_ccb_proximity_config_t * configData){
    ams_ccb_proximity_ctx_t * ccbCtx = &((ams_deviceCtx_t*)dcbCtx)->ccbProxCtx;

    if (configData->sensitivity > 0){
        ccbCtx->sensitivity = configData->sensitivity;
    }
}

bool ccb_proximityHandle(void * dcbCtx, ams_ccb_proximity_dataSet_t * proxData){
    ams_deviceCtx_t * ctx = (ams_deviceCtx_t*)dcbCtx;
    ams_ccb_proximity_ctx_t * ccbCtx = &((ams_deviceCtx_t*)dcbCtx)->ccbProxCtx;

    ccbCtx->pData = proxData->pData;
    ccbCtx->pDataNorm = AMS_NORMALISE_16(proxData->pData, ccbCtx->initData.numberAdcBits);

    switch (ccbCtx->state)
    {
    case PRX_STATE_FACTORY_CALIBRATION:
        ccbCtx->initData.calibrate = false;
        ccbCtx->nearBy = true;
        /* signal to DCB that calibration is completed */
        ctx->updateAvailable = AMS_CALIBRATION_DONE;
        AMS_PORT_log("PRX_STATE_FACTORY_CALIBRATION done\n");

        if (ccbCtx->initData.dynamicMode == true) {
            ccbCtx->initData.nearByHardThreshold = ccbCtx->pDataNorm;
            ccbCtx->initData.nearByThresholdHysteresis = ccbCtx->pDataNorm >> 2;
            ctx->systemCalibrationData->proxHardThreshold = ccbCtx->pDataNorm;
            ccbCtx->state = PRX_STATE_OPER;
        } else {
            ccbCtx->initData.nearByHardThreshold = ccbCtx->pData;
            ccbCtx->initData.nearByThresholdHysteresis = ccbCtx->pData >> 2;
            ctx->systemCalibrationData->proxHardThreshold = ccbCtx->pData;
            ccbCtx->state = PRX_STATE_STATIC_DETECT;
        }
        break;
    case PRX_STATE_STATIC_NO_DETECT:
        if (ccbCtx->pData > ccbCtx->initData.nearByHardThreshold) {
        ccbCtx->state = PRX_STATE_STATIC_DETECT;
        AMS_PORT_log("PRX_STATE nearBy\n");
        ams_setWord(ctx->portHndl,  DEVREG_PILTL, ccbCtx->initData.nearByHardThreshold - (ccbCtx->initData.nearByHardThreshold >> 2));
        ams_setWord(ctx->portHndl,  DEVREG_PIHTL, 0xffff);
        ccbCtx->nearBy = true;
        ctx->updateAvailable |= (1 << AMS_PROXIMITY_SENSOR);
        }
        break;
    case PRX_STATE_STATIC_DETECT:
        if (ccbCtx->pData < (ccbCtx->initData.nearByHardThreshold - (ccbCtx->initData.nearByHardThreshold >> 2))) {
        ccbCtx->state = PRX_STATE_STATIC_NO_DETECT;
        AMS_PORT_log("PRX_STATE farAway\n");
        ams_setWord(ctx->portHndl,  DEVREG_PILTL, 0x0000);
        ams_setWord(ctx->portHndl,  DEVREG_PIHTL, ccbCtx->initData.nearByHardThreshold);
        ccbCtx->nearBy = false;
        ctx->updateAvailable |= (1 << AMS_PROXIMITY_SENSOR);
        }
        break;
    default:
    case PRX_STATE_UNKNOWN:
    case PRX_STATE_BEGIN:
ccb_prox_recalibrate:
        AMS_PORT_log("PRX_STATE_BEGIN\n");

        ccbCtx->nearBy = false;
        ccbCtx->pDataAve = 0;
        ccbCtx->ave_index = 0;
        ccbCtx->pDataLow = -1;
        ccbCtx->pDataMax = 0;
        ccbCtx->pDataNormLast = 0xffff;
        ccbCtx->pDataNormTrigger = 0xffff;

        if (ccbCtx->initData.calibrate) {
            ccbCtx->state = PRX_STATE_FACTORY_CALIBRATION;
            ams_setByte(ctx->portHndl,  DEVREG_ENABLE, (ctx->shadowEnableReg & ~(PEN)));
            ams_setWord(ctx->portHndl,  DEVREG_PILTL, 0xffff);
            ams_setWord(ctx->portHndl,  DEVREG_PIHTL, 0X0000);
            ams_setByte(ctx->portHndl,  DEVREG_ENABLE, ctx->shadowEnableReg);
        }
        if (ccbCtx->initData.dynamicMode == true){
            /* setup registers for HW calibration */
            /* ams_setByte(ctx->portHndl,  DEVREG_ENABLE, 0); */
            ctx->shadowEnableReg &= ~(PEN);
            ams_setByte(ctx->portHndl,  DEVREG_ENABLE, ctx->shadowEnableReg);
            ams_tmg490x_setField(ctx->portHndl, DEVREG_CAL_CFG2, 2 << 4, MASK_BINSRCH);
            ams_tmg490x_setField(ctx->portHndl,  DEVREG_INT_ENBL, CINT, MASK_CINT);
            /* Trigger calibration sequence */
            ams_tmg490x_setField(ctx->portHndl, DEVREG_CALIB, HIGH, MASK_OFFSET_CALIB);

            ccbCtx->state = PRX_STATE_CAL;
        } else {
            if (ccbCtx->initData.calibrate == false){
                if (ccbCtx->pData > ccbCtx->initData.nearByHardThreshold) {
                ccbCtx->state = PRX_STATE_STATIC_NO_DETECT;
                } else {
                    ccbCtx->state = PRX_STATE_STATIC_DETECT;
                }
            }
        }
        break;
    case PRX_STATE_CAL:
        if (proxData->statusReg & MASK_CINT){
            AMS_PORT_log("PRX_STATE_CAL\n");
            {
                uint16_t offset;
                ams_getWord(ctx->portHndl,  DEVREG_OFFSET_NL, &offset);
                AMS_PORT_log_1("DEVREG_OFFSET_NL 0x%04x\n", offset);
                ams_getWord(ctx->portHndl,  DEVREG_OFFSET_SL, &offset);
                AMS_PORT_log_1("DEVREG_OFFSET_SL 0x%04x\n", offset);
                ams_getWord(ctx->portHndl,  DEVREG_OFFSET_EL, &offset);
                AMS_PORT_log_1("DEVREG_OFFSET_EL 0x%04x\n", offset);
                ams_getWord(ctx->portHndl,  DEVREG_OFFSET_WL, &offset);
                AMS_PORT_log_1("DEVREG_OFFSET_WL 0x%04x\n", offset);
            }
            ams_tmg490x_setField(ctx->portHndl, DEVREG_CALIB, LOW, MASK_OFFSET_CALIB);
            ams_tmg490x_setField(ctx->portHndl, DEVREG_INT_ENBL, HIGH, MASK_PINT);
            ams_tmg490x_setField(ctx->portHndl, DEVREG_INT_ENBL, LOW, MASK_CINT);
            ctx->shadowEnableReg |= (PEN | PON);
            ccbCtx->state = PRX_STATE_FILLUP;

            if (ccbCtx->initData.calibrate) {
                ccbCtx->state = PRX_STATE_FACTORY_CALIBRATION;
                ams_setByte(ctx->portHndl,  DEVREG_ENABLE, (ctx->shadowEnableReg & ~(PEN)));
                ams_setWord(ctx->portHndl,  DEVREG_PILTL, 0xffff);
                ams_setWord(ctx->portHndl,  DEVREG_PIHTL, 0X0000);
                ams_setByte(ctx->portHndl,  DEVREG_ENABLE, ctx->shadowEnableReg);
            } else {
                /* HW calibration completed */
                if (ccbCtx->initData.dynamicMode == false){
                    ccbCtx->state = PRX_STATE_STATIC_NO_DETECT;
                    ams_setByte(ctx->portHndl,  DEVREG_ENABLE, (ctx->shadowEnableReg & ~(PEN)));
                    ams_setWord(ctx->portHndl,  DEVREG_PILTL, 0x0000);
                    ams_setWord(ctx->portHndl,  DEVREG_PIHTL, ccbCtx->initData.nearByHardThreshold);
                    ams_setByte(ctx->portHndl,  DEVREG_ENABLE, ctx->shadowEnableReg);
                }
            }
        }
        ams_setByte(ctx->portHndl, DEVREG_INT_CLEAR, HIGH); /* clear ALL interrupt */
        break;
    case PRX_STATE_FILLUP:
    case PRX_STATE_OPER:
        /* check if we have a new prox cycle */
        if (proxData->statusReg & MASK_PINT){

            if (ccbCtx->pData == 0) {
                ccbCtx->state = PRX_STATE_BEGIN;
                goto ccb_prox_recalibrate;
            }

            if (ccbCtx->state == PRX_STATE_FILLUP){
                AMS_PORT_log("PRX_STATE_CAL Find noise level\n");
                /* determine min and max of pData */
                if (ccbCtx->ave_index != 0){
                    if (ccbCtx->pDataLow > ccbCtx->pData) ccbCtx->pDataLow = ccbCtx->pData;
                    if (ccbCtx->pDataMax < ccbCtx->pData) ccbCtx->pDataMax = ccbCtx->pData;
                }

                /* fill the average buffer */
                ccbCtx->ave[ccbCtx->ave_index++] = ccbCtx->pDataNorm;
                ccbCtx->pDataAve += ccbCtx->pDataNorm;

                if (ccbCtx->ave_index == AMS_PRX_AVERAGE_COUNT){
                    /* average buffer is full */
                    ccbCtx->ave_index = 1;
                    ccbCtx->state = PRX_STATE_OPER;
                    if (ccbCtx->initData.adcThreshold == 0 ){
                        AMS_PORT_log_2("pData High: %d   Low: %d\n", ccbCtx->pDataMax, ccbCtx->pDataLow);
                        /* use min and max to calculate the noise for threshold setup */
                        ccbCtx->initData.adcThreshold =  (ccbCtx->pDataMax - ccbCtx->pDataLow) << 2;
                    }
                    if (ccbCtx->initData.calibrate) {
                        ccbCtx->state = PRX_STATE_FACTORY_CALIBRATION;
                    }
                }
            } else {
                /* setup the threshold registers based on pData */
                ams_setWord(ctx->portHndl, DEVREG_PIHTL, MIN(0xffff, (ccbCtx->pData + ccbCtx->initData.adcThreshold)));
                ams_setWord(ctx->portHndl, DEVREG_PILTL, MAX(0, (ccbCtx->pData - ccbCtx->initData.adcThreshold)));

                if (ccbCtx->nearBy == false){
                    /* replace the oldest PROX value with the new PROX value
                     * but only if not nearBy
                     */
                    ccbCtx->pDataAve -= ccbCtx->ave[ccbCtx->ave_index];
                    ccbCtx->ave[ccbCtx->ave_index] = ccbCtx->pDataNorm;
                    ccbCtx->pDataAve += ccbCtx->ave[ccbCtx->ave_index];
                    ccbCtx->ave_index ++;
                    if (ccbCtx->ave_index == AMS_PRX_AVERAGE_COUNT) {
                        /* ring buffer for averaging */
                        ccbCtx->ave_index = 0;
                    }
                }
                if (ccbCtx->nearBy){
                    if (ccbCtx->pDataNorm < (uint16_t)(ccbCtx->pDataNormTrigger -
                            (AMS_NORMALISE_16(ccbCtx->initData.adcThreshold, ccbCtx->initData.numberAdcBits) << (ccbCtx->sensitivity + 2)))){
                        ccbCtx->nearBy = false;
                        ctx->updateAvailable |= (1 << AMS_PROXIMITY_SENSOR);
                    }
                }
                /* check if nearBy */
                if ((ccbCtx->pDataNorm > (ccbCtx->pDataNormLast +
                        (AMS_NORMALISE_16(ccbCtx->initData.adcThreshold, ccbCtx->initData.numberAdcBits) << (ccbCtx->sensitivity + 1)))) ||
                    (ccbCtx->pDataNorm > ccbCtx->initData.nearByHardThreshold)){
                    ccbCtx->nearBy = true;
                    ctx->updateAvailable |= (1 << AMS_PROXIMITY_SENSOR);
                    ccbCtx->pDataNormTrigger = ccbCtx->pDataNorm;
                } else {
                    ccbCtx->pDataNormLast = ccbCtx->pDataNorm;
                }
            }
            AMS_PORT_log_1("pData:       0x%04x\n", ccbCtx->pData);
            AMS_PORT_log_1("pDataNorm:     %d\n", ccbCtx->pDataNorm);
            AMS_PORT_log_1("threshold HW:  %d\n", ccbCtx->initData.adcThreshold);
            AMS_PORT_log_1("threshold SW:  %d\n", (ccbCtx->pDataNormLast + (AMS_NORMALISE_16(ccbCtx->initData.adcThreshold, ccbCtx->initData.numberAdcBits) << (ccbCtx->sensitivity + 1))));
            AMS_PORT_log_1("triggered @:   %d\n", ccbCtx->pDataNormTrigger);
            AMS_PORT_log_1("nearBy:        %d\n", ccbCtx->nearBy);
        }
        ams_tmg490x_setField(ctx->portHndl, DEVREG_INT_CLEAR, HIGH, (MASK_INTCLR_PINT | MASK_INTCLR_PGSAT | MASK_INTCLR_CINT)); /* clear interrupt */

        break;
    }
    if ((ccbCtx->state == PRX_STATE_STATIC_NO_DETECT) || (ccbCtx->state == PRX_STATE_STATIC_DETECT)){
        AMS_PORT_log_1("pData:       0x%04x\n", ccbCtx->pData);
        AMS_PORT_log_1("pDataNorm:     %d\n", ccbCtx->pDataNorm);
        AMS_PORT_log_1("nearBy:        %d\n", ccbCtx->nearBy);
    }
    return false;
}

void ccb_proximityGetResult(void * dcbCtx, ams_ccb_proximity_result_t * result){
    ams_ccb_proximity_ctx_t * ccbCtx = &((ams_deviceCtx_t*)dcbCtx)->ccbProxCtx;

    /* export proximity data */
    result->nearBy = ccbCtx->nearBy;
    result->proximity = ccbCtx->pDataNorm;
}

/*
Processing uImage file:
./ams_tmx490x_qcom_hd22/src/dd_ams_uimg.c
*/

/*
 *
 */

/*
 * @@AMS_REVISION_Id: 24eac85329886ce82627a54da2d81614c076976a
 */


void AMS_PORT_suspend(uint32_t timeOut_us){
    sns_ddf_delay(timeOut_us);
}

void AMS_PORT_get_timestamp_usec(uint64_t *timestamp) {
    *timestamp = sns_ddf_get_timestamp();
}

uint8_t AMS_PORT_setByte(AMS_PORT_portHndl * portHndl, uint8_t reg, uint8_t * data, uint8_t lenght) {
    uint8_t write_count;
    sns_ddf_status_e status;

    status = sns_ddf_write_port(portHndl,
                    reg,
                    data,
                    lenght,
                    &write_count);

    if (status == SNS_DDF_SUCCESS) {
        return write_count;
    }
    return 0;
}

uint8_t AMS_PORT_getByte(AMS_PORT_portHndl * portHndl, uint8_t reg, uint8_t * data, uint8_t lenght){
    uint8_t read_count;
    sns_ddf_status_e status;

    status = sns_ddf_read_port(portHndl,
                    reg,
                    data,
                    lenght,
                    &read_count);

    if (status == SNS_DDF_SUCCESS) {
        return read_count;
    }
    return 0;
}

static sns_ddf_status_e ams_freeResponse
(
    sns_ddf_handle_t*  smgr_handle,
    sns_ddf_sensor_data_s* data
)
{
    sns_ddf_status_e status = SNS_DDF_SUCCESS;

    sns_ddf_mfree_ex(data->samples, smgr_handle);
    sns_ddf_mfree_ex(data, smgr_handle);

    return status;
}

static sns_ddf_sensor_data_s * ams_configureResponse(
    sns_ddf_memhandler_s*  memhandler,
    sns_ddf_handle_t *     smgr_handle,
    sns_ddf_sensor_data_s* in_sensor_data[],
    uint32_t               numSamples
)
{
    sns_ddf_status_e status = SNS_DDF_SUCCESS;
    sns_ddf_sensor_data_s*   sensor_data;

    if(memhandler == NULL){
        status = sns_ddf_malloc_ex((void **)&sensor_data, sizeof(sns_ddf_sensor_data_s), smgr_handle);
        if (status != SNS_DDF_SUCCESS ){
            DD_MSG_0(MED, "ams_configureResponse: sns_ddf_sensor_data_s failed");
            return NULL;
        }
        status = sns_ddf_malloc_ex((void **)&sensor_data->samples, (numSamples * sizeof(sns_ddf_sensor_sample_s)), smgr_handle);
        if (status != SNS_DDF_SUCCESS ){
            DD_MSG_0(MED, "ams_configureResponse: sns_ddf_sensor_sample_s failed");
            sns_ddf_mfree_ex(&sensor_data, smgr_handle);
            return NULL;
        }
    }else{
        if ( in_sensor_data == NULL )
        {
            sensor_data  = sns_ddf_memhandler_malloc_ex(memhandler, sizeof(sns_ddf_sensor_data_s), smgr_handle);
            if(sensor_data == NULL){
                DD_MSG_0(MED, "ams_configureResponse: sns_ddf_sensor_data_s failed");
                return NULL;
            }
        }else{
            sensor_data = *in_sensor_data;
        }
        sensor_data->samples  = sns_ddf_memhandler_malloc_ex(memhandler, (numSamples * sizeof(sns_ddf_sensor_sample_s)), smgr_handle);
        if (sensor_data->samples == NULL){
            DD_MSG_0(MED, "ams_configureResponse: sns_ddf_sensor_sample_s failed");
            // sensor_data will be freed by the memhandler
            return NULL;
        }
    }
    return sensor_data;
}

static sns_ddf_status_e ams_freeResponse2
(
    sns_ddf_handle_t*  smgr_handle,
    sns_ddf_sensor_data_s* data
)
{
    sns_ddf_status_e status = SNS_DDF_SUCCESS;

    DD_MSG_2(MED, "ams_freeResponse2: smgr_handle=%p, data=%p", smgr_handle, data);
    sns_ddf_mfree_ex(data[0].samples, smgr_handle);
    sns_ddf_mfree_ex(data[1].samples, smgr_handle);
    sns_ddf_mfree_ex(data, smgr_handle);

    return status;
}

static sns_ddf_sensor_data_s * ams_configureResponse2(
    sns_ddf_memhandler_s*  memhandler,
    sns_ddf_handle_t *     smgr_handle,
    sns_ddf_sensor_data_s* in_sensor_data[],
    uint32_t               numSamples1,
    uint32_t               numSamples2
)
{
    sns_ddf_status_e status = SNS_DDF_SUCCESS;
    sns_ddf_sensor_data_s*   sensor_data;

    if(memhandler == NULL){
        status = sns_ddf_malloc_ex((void **)&sensor_data, 2 * sizeof(sns_ddf_sensor_data_s), smgr_handle);
        if (status != SNS_DDF_SUCCESS ){
            DD_MSG_0(MED, "ams_configureResponse: sns_ddf_sensor_data_s failed");
            return NULL;
        }
        status = sns_ddf_malloc_ex((void **)&(sensor_data[0].samples), (numSamples1 * sizeof(sns_ddf_sensor_sample_s)), smgr_handle);
        if (status != SNS_DDF_SUCCESS ){
            DD_MSG_0(MED, "ams_configureResponse: sns_ddf_sensor_sample_s failed");
            sns_ddf_mfree_ex(&sensor_data, smgr_handle);
            return NULL;
        }
        status = sns_ddf_malloc_ex((void **)&(sensor_data[1].samples), (numSamples2 * sizeof(sns_ddf_sensor_sample_s)), smgr_handle);
        if (status != SNS_DDF_SUCCESS ){
            DD_MSG_0(MED, "ams_configureResponse: sns_ddf_sensor_sample_s failed");
            sns_ddf_mfree_ex(&sensor_data, smgr_handle);
            return NULL;
        }
    }else{
        if ( in_sensor_data == NULL )
        {
            sensor_data  = sns_ddf_memhandler_malloc_ex(memhandler, 2 * sizeof(sns_ddf_sensor_data_s), smgr_handle);
            if(sensor_data == NULL){
                DD_MSG_0(MED, "ams_configureResponse: sns_ddf_sensor_data_s failed");
                return NULL;
            }
        }else{
            sensor_data = *in_sensor_data;
        }
        sensor_data[0].samples  = sns_ddf_memhandler_malloc_ex(memhandler, (numSamples1 * sizeof(sns_ddf_sensor_sample_s)), smgr_handle);
        if (sensor_data[0].samples == NULL){
            DD_MSG_0(MED, "ams_configureResponse: sns_ddf_sensor_sample_s failed");
            // sensor_data will be freed by the memhandler
            return NULL;
        }
        sensor_data[1].samples  = sns_ddf_memhandler_malloc_ex(memhandler, (numSamples2 * sizeof(sns_ddf_sensor_sample_s)), smgr_handle);
        if (sensor_data[1].samples == NULL){
            DD_MSG_0(MED, "ams_configureResponse: sns_ddf_sensor_sample_s failed");
            // sensor_data will be freed by the memhandler
            return NULL;
        }
    }
    return sensor_data;
}

// sns_log_sensor_data_pkt_s per se includes only samples[1]; use this
// to extend it if necessary (but currently we don't use samples[] at all)
#define LOGPKT_NUM_EXTRA_SAMPLES    0
static void ams_generateLog(
    sns_ddf_sensor_e sensor_type,
    uint32_t         data1,
    uint32_t         data2,
    uint32_t         data3,
    uint32_t         data4,
    uint32_t         data5)
{
    sns_log_sensor_data_pkt_s* log_struct_ptr;
    sns_err_code_e err_code;

    DD_MSG_0(HIGH, "ams_generateLog: ENTER");

#ifdef SENSORS_DD_DEV_FLAG
    log_pkt_t log_pkt_type = SNS_LOG_CONVERTED_SENSOR_DATA_PUBLIC;
#else
    log_pkt_t log_pkt_type = SNS_LOG_CONVERTED_SENSOR_DATA;
#endif

    switch (sensor_type) {
        case SNS_DDF_SENSOR_AMBIENT:
        case SNS_DDF_SENSOR_PROXIMITY:
        case SNS_DDF_SENSOR_RGB:
        case SNS_DDF_SENSOR_CT_C:
        case SNS_DD_SENSOR_WIDEBAND:
        case SNS_DDF_SENSOR_IR_GESTURE:
            break;
        default:
            DD_MSG_1(ERROR,"ams_generateLog: unknown sensor_type %u", sensor_type);
            return;
    }

   /* Allocate log packet */
    err_code = sns_logpkt_malloc(log_pkt_type,
                (sizeof(sns_log_sensor_data_pkt_s) + LOGPKT_NUM_EXTRA_SAMPLES * sizeof(log_struct_ptr->samples[0])),
                (void **)&log_struct_ptr);

    if ((err_code != SNS_SUCCESS) || (log_struct_ptr == NULL)) {
            DD_MSG_1(ERROR,"ams_generateLog: malloc sns_log_sensor_data_pkt_s failed %d", err_code);
            return;
    }

    log_struct_ptr->version   = SNS_LOG_SENSOR_DATA_PKT_VERSION;
    log_struct_ptr->sensor_id = sensor_type;
    log_struct_ptr->vendor_id = SNS_DDF_VENDOR_AMS;

    /* Timestamp the log with sample time */
    log_struct_ptr->timestamp = log_struct_ptr->end_timestamp = sns_ddf_get_timestamp();

    /* Log the sensor data */
    if (SNS_DDF_SENSOR_AMBIENT == sensor_type)
    {
      log_struct_ptr->num_data_types = 3;
      log_struct_ptr->data[0] = data1;
      log_struct_ptr->data[1] = data2;
      log_struct_ptr->data[2] = data3;
     }
#ifdef CONFIG_AMS_OPTICAL_SENSOR_PROX
    else if (SNS_DDF_SENSOR_PROXIMITY == sensor_type)
    {
      log_struct_ptr->num_data_types = 5;
      log_struct_ptr->data[0] = data1;
      log_struct_ptr->data[1] = data2;
      log_struct_ptr->data[2] = data3;
      log_struct_ptr->data[3] = data4;
      log_struct_ptr->data[4] = data5;
    }
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS_RGB
    else if (SNS_DDF_SENSOR_RGB == sensor_type)
    {
      log_struct_ptr->num_data_types = 3;
      log_struct_ptr->data[0] = data1;
      log_struct_ptr->data[1] = data2;
      log_struct_ptr->data[2] = data3;
    }
    else if (SNS_DDF_SENSOR_CT_C == sensor_type)
    {
      log_struct_ptr->num_data_types = 2;
      log_struct_ptr->data[0] = data1;
      log_struct_ptr->data[1] = data2;
    }
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS_WIDEBAND
    else if (SNS_DD_SENSOR_WIDEBAND == sensor_type)
    {
      log_struct_ptr->num_data_types = 1;
      log_struct_ptr->data[0] = data1;
    }
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_GESTURE
    else if (SNS_DDF_SENSOR_IR_GESTURE == sensor_type)
    {
      log_struct_ptr->num_data_types = 1;
      log_struct_ptr->data[0] = data1;
    }
#endif
    /* Commit log (also frees up the log packet memory) */
    sns_logpkt_commit(log_pkt_type,
                                 log_struct_ptr);

   DD_MSG_0(HIGH, "ams_generateLog: EXIT");
}

#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS
static sns_ddf_status_e ams_generateAlsResponse(
    sns_dd_ams_t*  state,
    sns_ddf_memhandler_s*  memhandler,
    sns_ddf_sensor_data_s* data[],
    uint32_t               sub_dev_id,
    sns_ddf_time_t         timestamp
)
{
    sns_ddf_status_e status = SNS_DDF_SUCCESS;
    sns_ddf_sensor_data_s*   sensor_data;
    ams_apiAls_t outData;
    bool als_valid = false;

    sensor_data = ams_configureResponse(memhandler,
                        state->sub_dev[sub_dev_id].smgr_handle,
                        data,
                        SENSOR_AMBIENT_SAMPLES);

    if (sensor_data == NULL ) return SNS_DDF_EFAIL;

    als_valid = ams_deviceGetAls(&state->chip, &outData);

    sensor_data->sensor        = SNS_DDF_SENSOR_AMBIENT;
    sensor_data->status        = SNS_DDF_SUCCESS;
    sensor_data->timestamp     = timestamp;
    sensor_data->end_timestamp = timestamp;
    sensor_data->num_samples   = SENSOR_AMBIENT_SAMPLES;
    sensor_data->samples[0].sample = FX_FLTTOFIX_Q16(outData.mLux/1000);
    sensor_data->samples[0].status = SNS_DDF_SUCCESS;
    sensor_data->samples[1].sample = (uint32_t)outData.rawClear;
    sensor_data->samples[1].status = SNS_DDF_SUCCESS;

    DD_MSG_2(MED, "ams_generateAlsResponse: %d %d", sensor_data->sensor, sensor_data->num_samples);
    DD_MSG_1(MED, "ams_generateAlsResponse: %d", sensor_data->samples[0].sample);
    DD_MSG_1(MED, "ams_generateAlsResponse: %d", sensor_data->samples[1].sample);

    if(als_valid == false) {
      sensor_data->samples[0].status = SNS_DDF_EDATA_BOUND;
      sensor_data->samples[1].status = SNS_DDF_EDATA_BOUND;
      sensor_data->status        = SNS_DDF_EFAIL;
    } else {
      // log packet layout differs from the sample data report
      ams_generateLog(SNS_DDF_SENSOR_AMBIENT,
        (uint32_t)outData.mLux,
        sensor_data->samples[0].sample,
        sensor_data->samples[1].sample,
        0,
        0);
    }

    if(memhandler == NULL){
        status = sns_ddf_smgr_notify_data(state->sub_dev[sub_dev_id].smgr_handle, sensor_data, 1);
        status = ams_freeResponse(state->sub_dev[sub_dev_id].smgr_handle, sensor_data);
    } else {
        *data = sensor_data;
    }
    return status;
}
#endif

#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS_RGB
static sns_ddf_status_e ams_generateAlsRgbResponse(
    sns_dd_ams_t*  state,
    sns_ddf_memhandler_s*  memhandler,
    sns_ddf_sensor_data_s* data[],
    uint32_t               sub_dev_id,
    sns_ddf_time_t         timestamp
)
{
    sns_ddf_status_e status = SNS_DDF_SUCCESS;
    sns_ddf_sensor_data_s*   sensor_data;
    ams_apiAls_t outData;

    sensor_data = ams_configureResponse(memhandler,
                        state->sub_dev[sub_dev_id].smgr_handle,
                        data,
                        SENSOR_RGB_SAMPLES);

    if (sensor_data == NULL ) return SNS_DDF_EFAIL;

    ams_deviceGetAls(&state->chip, &outData);

    sensor_data->sensor        = SNS_DDF_SENSOR_RGB;
    sensor_data->status        = SNS_DDF_SUCCESS;
    sensor_data->timestamp     = timestamp;
    sensor_data->end_timestamp = timestamp;
    sensor_data->num_samples   = SENSOR_RGB_SAMPLES;
    sensor_data->samples[0].sample = (outData.red);
    sensor_data->samples[0].status = SNS_DDF_SUCCESS;
    sensor_data->samples[1].sample = (outData.green);
    sensor_data->samples[1].status = SNS_DDF_SUCCESS;
    sensor_data->samples[2].sample = (outData.blue);
    sensor_data->samples[2].status = SNS_DDF_SUCCESS;

    DD_MSG_2(MED, "ams_generateAlsRgbResponse: %d %d", sensor_data->sensor, sensor_data->num_samples);
    DD_MSG_1(MED, "ams_generateAlsRgbResponse: %d", outData.red);
    DD_MSG_1(MED, "ams_generateAlsRgbResponse: %d", outData.green);
    DD_MSG_1(MED, "ams_generateAlsRgbResponse: %d", outData.blue);

    ams_generateLog(SNS_DDF_SENSOR_RGB,
        outData.red,
        outData.green,
        outData.blue,
        0,
        0);

    if(memhandler == NULL){
        status = sns_ddf_smgr_notify_data(state->sub_dev[sub_dev_id].smgr_handle, sensor_data, 1);
        status = ams_freeResponse(state->sub_dev[sub_dev_id].smgr_handle, sensor_data);
    } else {
        *data = sensor_data;
    }
    return status;
}

static sns_ddf_status_e ams_generateAlsCtResponse(
    sns_dd_ams_t*  state,
    sns_ddf_memhandler_s*  memhandler,
    sns_ddf_sensor_data_s* data[],
    uint32_t               sub_dev_id,
    sns_ddf_time_t         timestamp
)
{
    sns_ddf_status_e status = SNS_DDF_SUCCESS;
    sns_ddf_sensor_data_s*   sensor_data;
    ams_apiAls_t outData;

    sensor_data = ams_configureResponse(memhandler,
                        state->sub_dev[sub_dev_id].smgr_handle,
                        data,
                        SENSOR_CT_SAMPLES);

    if (sensor_data == NULL ) return SNS_DDF_EFAIL;

    ams_deviceGetAls(&state->chip, &outData);

    sensor_data->sensor        = SNS_DDF_SENSOR_CT_C;
    sensor_data->status        = SNS_DDF_SUCCESS;
    sensor_data->timestamp     = timestamp;
    sensor_data->end_timestamp = timestamp;
    sensor_data->num_samples   = SENSOR_CT_SAMPLES;
    sensor_data->samples[0].sample = FX_FLTTOFIX_Q16(outData.colorTemp);
    sensor_data->samples[0].status = SNS_DDF_SUCCESS;
    sensor_data->samples[1].sample = outData.ir;
    sensor_data->samples[1].status = SNS_DDF_SUCCESS;

    DD_MSG_2(MED, "ams_generateAlsCtResponse: %d %d", sensor_data->sensor, sensor_data->num_samples);
    DD_MSG_1(MED, "ams_generateAlsCtResponse: %d", outData.colorTemp);
    DD_MSG_1(MED, "ams_generateAlsCtResponse: %d", outData.ir);

    if(sensor_data->samples[0].sample == 0) {
       sensor_data->samples[0].status = SNS_DDF_EDATA_BOUND;
       sensor_data->samples[1].status = SNS_DDF_EDATA_BOUND;
       sensor_data->status            = SNS_DDF_EFAIL;
    } else {
       ams_generateLog(SNS_DDF_SENSOR_CT_C,
        sensor_data->samples[0].sample,
        sensor_data->samples[1].sample,
        0,
        0,
        0);
    }

    if(memhandler == NULL){
        status = sns_ddf_smgr_notify_data(state->sub_dev[sub_dev_id].smgr_handle, sensor_data, 1);
        status = ams_freeResponse(state->sub_dev[sub_dev_id].smgr_handle, sensor_data);
    } else {
        *data = sensor_data;
    }
    return status;
}

static sns_ddf_status_e ams_generateAlsRgbCtResponse(
    sns_dd_ams_t*  state,
    sns_ddf_memhandler_s*  memhandler,
    sns_ddf_sensor_data_s* data[],
    uint32_t               sub_dev_id,
    sns_ddf_time_t         timestamp,
    bool                   doRgbNow
)
{
    sns_ddf_status_e status = SNS_DDF_SUCCESS;
    sns_ddf_sensor_data_s*   sensor_data;
    ams_apiAls_t outData;
    uint32_t i;

    DD_MSG_1(MED, "ams_generateAlsRgbCtResponse: state=%p", state);
    if ( doRgbNow )
    {
        sensor_data = ams_configureResponse2(memhandler,
                        state->sub_dev[sub_dev_id].smgr_handle,
                        data,
                        SENSOR_RGB_SAMPLES, SENSOR_CT_SAMPLES);
    }
    else
    {
        
        sensor_data = ams_configureResponse2(memhandler,
                        state->sub_dev[sub_dev_id].smgr_handle,
                        data,
                        SENSOR_CT_SAMPLES, SENSOR_RGB_SAMPLES);
    }
    

    if (sensor_data == NULL ) return SNS_DDF_EFAIL;

    ams_deviceGetAls(&state->chip, &outData);

    for (i=0 ; i < 2; i++) {
        if (doRgbNow) {
            sensor_data[i].sensor        = SNS_DDF_SENSOR_RGB;
            sensor_data[i].status        = SNS_DDF_SUCCESS;
            sensor_data[i].timestamp     = timestamp;
            sensor_data[i].num_samples   = SENSOR_RGB_SAMPLES;
            sensor_data[i].samples[0].sample = (outData.red);
            sensor_data[i].samples[0].status = SNS_DDF_SUCCESS;
            sensor_data[i].samples[1].sample = (outData.green);
            sensor_data[i].samples[1].status = SNS_DDF_SUCCESS;
            sensor_data[i].samples[2].sample = (outData.blue);
            sensor_data[i].samples[2].status = SNS_DDF_SUCCESS;

            DD_MSG_2(MED, "ams_generateAlsRgbCtResponse: RGB: %d %d", sensor_data[i].sensor, sensor_data[i].num_samples);
            DD_MSG_1(MED, "ams_generateAlsRgbCtResponse: RGB: %d", outData.red);
            DD_MSG_1(MED, "ams_generateAlsRgbCtResponse: RGB: %d", outData.green);
            DD_MSG_1(MED, "ams_generateAlsRgbCtResponse: RGB: %d", outData.blue);

            ams_generateLog(SNS_DDF_SENSOR_RGB,
                sensor_data[i].samples[0].sample,
                sensor_data[i].samples[1].sample,
                sensor_data[i].samples[2].sample,
                0,
                0);

            doRgbNow = false;
        } else {
            sensor_data[i].sensor        = SNS_DDF_SENSOR_CT_C;
            sensor_data[i].status        = SNS_DDF_SUCCESS;
            sensor_data[i].timestamp     = timestamp;
            sensor_data[i].end_timestamp = timestamp;
            sensor_data[i].num_samples   = SENSOR_CT_SAMPLES;
            sensor_data[i].samples[0].sample = FX_FLTTOFIX_Q16(outData.colorTemp);
            sensor_data[i].samples[0].status = SNS_DDF_SUCCESS;
            sensor_data[i].samples[1].sample = outData.ir;
            sensor_data[i].samples[1].status = SNS_DDF_SUCCESS;

            DD_MSG_2(MED, "ams_generateAlsRgbCtResponse: CT: %d %d", sensor_data[i].sensor, sensor_data[i].num_samples);
            DD_MSG_1(MED, "ams_generateAlsRgbCtResponse: CT: %d", outData.colorTemp);
            DD_MSG_1(MED, "ams_generateAlsRgbCtResponse: CT: %d", outData.ir);

           if(sensor_data[i].samples[0].sample == 0) {
              sensor_data[i].samples[0].status = SNS_DDF_EDATA_BOUND;
              sensor_data[i].samples[1].status = SNS_DDF_EDATA_BOUND;
              sensor_data[i].status        = SNS_DDF_EFAIL;
           } else { 
              ams_generateLog(SNS_DDF_SENSOR_CT_C,
                sensor_data[i].samples[0].sample,
                sensor_data[i].samples[1].sample,
                0,
                0,
                0);
       }

            doRgbNow = true;
        }
    }

    if(memhandler == NULL){
        DD_MSG_2(MED, "ams_generateAlsRgbCtResponse: state=%p, sensor_data=%p", state, sensor_data);
        status = sns_ddf_smgr_notify_data(state->sub_dev[sub_dev_id].smgr_handle, sensor_data, 2);
        status = ams_freeResponse2(state->sub_dev[sub_dev_id].smgr_handle, sensor_data);
    } else {
        *data = sensor_data;
    }
    return status;
}
#endif

#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS_WIDEBAND
static sns_ddf_status_e ams_generateAlsWbResponse(
    sns_dd_ams_t*  state,
    sns_ddf_memhandler_s*  memhandler,
    sns_ddf_sensor_data_s* data[],
    uint32_t               sub_dev_id,
    sns_ddf_time_t         timestamp
)
{
    sns_ddf_status_e status = SNS_DDF_SUCCESS;
    sns_ddf_sensor_data_s*   sensor_data;
    ams_apiAls_t outData;

    sensor_data = ams_configureResponse(memhandler,
                        state->sub_dev[sub_dev_id].smgr_handle,
                        data,
                        SENSOR_WIDEBAND_SAMPLES);

    if (sensor_data == NULL ) return SNS_DDF_EFAIL;

    ams_deviceGetAls(&state->chip, &outData);

    sensor_data->sensor        = SNS_DD_SENSOR_WIDEBAND;
    sensor_data->status        = SNS_DDF_SUCCESS;
    sensor_data->timestamp     = timestamp;
    sensor_data->end_timestamp = timestamp;
    sensor_data->num_samples   = SENSOR_WIDEBAND_SAMPLES;
    sensor_data->samples[0].sample = FX_FLTTOFIX_Q16(outData.wideband);
    sensor_data->samples[0].status = SNS_DDF_SUCCESS;

    DD_MSG_2(MED, "ams_generateAlsWbResponse: %d %d", sensor_data->sensor, sensor_data->num_samples);
    DD_MSG_1(MED, "ams_generateAlsWbResponse: %d", outData.wideband);

    ams_generateLog(SNS_DD_SENSOR_WIDEBAND,
        sensor_data->samples[0].sample,
        0,
        0,
        0,
        0);

    if(memhandler == NULL){
        status = sns_ddf_smgr_notify_data(state->sub_dev[sub_dev_id].smgr_handle, sensor_data, 1);
        status = ams_freeResponse(state->sub_dev[sub_dev_id].smgr_handle, sensor_data);
    } else {
        *data = sensor_data;
    }
    return status;
}
#endif

#ifdef CONFIG_AMS_OPTICAL_SENSOR_PROX
static sns_ddf_status_e ams_generateProxResponse(
    sns_dd_ams_t* state,
    sns_ddf_memhandler_s*  memhandler,
    sns_ddf_sensor_data_s* data[],
    uint32_t               sub_dev_id,
    sns_ddf_time_t         timestamp
)
{
    sns_ddf_status_e status = SNS_DDF_SUCCESS;
    sns_ddf_sensor_data_s*   sensor_data;
    ams_apiPrx_t outData;

    sensor_data = ams_configureResponse(memhandler,
                        state->sub_dev[sub_dev_id].smgr_handle,
                        data,
                        SENSOR_PROXIMITY_SAMPLES);

    if (sensor_data == NULL ) return SNS_DDF_EFAIL;

    ams_deviceGetPrx(&state->chip, &outData);

    sensor_data->sensor        = SNS_DDF_SENSOR_PROXIMITY;
    sensor_data->status        = SNS_DDF_SUCCESS;
    sensor_data->timestamp     = timestamp;
    sensor_data->end_timestamp = timestamp;
    sensor_data->num_samples   = SENSOR_PROXIMITY_SAMPLES;
    sensor_data->samples[0].sample = FX_CONV_Q16(outData.nearBy, 0);
    sensor_data->samples[0].status = SNS_DDF_SUCCESS;
    sensor_data->samples[1].sample = outData.proximity;
    sensor_data->samples[1].status = SNS_DDF_SUCCESS;

    DD_MSG_2(MED, "ams_generateProxResponse %d %d", sensor_data->sensor, sensor_data->num_samples);
    DD_MSG_1(MED, "ams_generateProxResponse: %d", outData.nearBy);
    DD_MSG_1(MED, "ams_generateProxResponse: %d", outData.proximity);

    // log packet layout differs from the sample data report
    ams_generateLog(SNS_DDF_SENSOR_PROXIMITY,
        outData.nearBy,
        sensor_data->samples[0].sample,
        0,
        0,
        sensor_data->samples[1].sample);

    if(memhandler == NULL){
        status = sns_ddf_smgr_notify_data(state->sub_dev[sub_dev_id].smgr_handle, sensor_data, 1);
        status = ams_freeResponse(state->sub_dev[sub_dev_id].smgr_handle, sensor_data);
    } else {
        *data = sensor_data;
    }
    return status;
}
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_GESTURE
static sns_ddf_status_e ams_generateGestureResponse(
    sns_dd_ams_t* state,
    sns_ddf_memhandler_s*  memhandler,
    sns_ddf_sensor_data_s* data[],
    uint32_t               sub_dev_id,
    sns_ddf_time_t         timestamp
)
{
    sns_ddf_status_e status = SNS_DDF_SUCCESS;
    sns_ddf_sensor_data_s*   sensor_data;
    amsGestResult_t outData;
    sns_ddf_ir_gesture_e qcomGestureEvent;

    sensor_data = ams_configureResponse(memhandler,
                        state->sub_dev[sub_dev_id].smgr_handle,
                        data,
                        SENSOR_GESTURE_SAMPLES);

    if (sensor_data == NULL ) return SNS_DDF_EFAIL;

    ams_deviceGetGesture(&state->chip, &outData);
    switch (outData.event){
    case northToSouth:
        qcomGestureEvent = SNS_DDF_IR_GESTURE_UP;
        break;
    case southToNorth:
        qcomGestureEvent = SNS_DDF_IR_GESTURE_DOWN;
        break;
    case eastToWest:
        qcomGestureEvent = SNS_DDF_IR_GESTURE_LEFT;
        break;
    case westToEast:
        qcomGestureEvent = SNS_DDF_IR_GESTURE_RIGHT;
        break;
    case northWestToSouthEast:
    case northEastToSouthWest:
    case southWestToNorthEast:
    case southEastToNorthWest:
    case pushedAndReleased:
    case pushedAndHold:
    case unknown_gestureEvent:
    default:
        qcomGestureEvent = SNS_DDF_IR_GESTURE_NONE;
        break;
    }

    sensor_data->sensor        = SNS_DDF_SENSOR_IR_GESTURE;
    sensor_data->status        = SNS_DDF_SUCCESS;
    sensor_data->timestamp     = timestamp;
    sensor_data->end_timestamp = timestamp;
    sensor_data->num_samples   = SENSOR_GESTURE_SAMPLES;
    sensor_data->samples[0].sample = qcomGestureEvent;
    sensor_data->samples[0].status = SNS_DDF_SUCCESS;

    DD_MSG_2(MED, "ams_generateGestureResponse %d %d", sensor_data->sensor, sensor_data->num_samples);
    DD_MSG_1(MED, "ams_generateGestureResponse: %d", outData.event);

    ams_generateLog(SNS_DDF_SENSOR_IR_GESTURE,
        sensor_data->samples[0].sample,
        0,
        0,
        0,
        0);

    if(memhandler == NULL){
        status = sns_ddf_smgr_notify_data(state->sub_dev[sub_dev_id].smgr_handle, sensor_data, 1);
        status = ams_freeResponse(state->sub_dev[sub_dev_id].smgr_handle, sensor_data);
    } else {
        *data = sensor_data;
    }
    return status;
}
#endif

/*===========================================================================

  FUNCTION:   sns_dd_ams_getData

===========================================================================*/
/*!
  @brief Called by the SMGR to get data

  @detail
  Requests a single sample of sensor data from each of the specified
  sensors. Data is returned immediately after being read from the
  sensor, in which case data[] is populated in the same order it was
  requested

  This driver is a pure asynchronous one, so no data will be written to buffer.
  As a result, the return value will be always PENDING if the process does
  not fail.  This driver will notify the Sensors Manager via asynchronous
  notification when data is available.

  @param[in]  dd_handle    Handle to a driver instance.
  @param[in]  sensors      List of sensors for which data is requested.
  @param[in]  num_sensors  Length of @a sensors.
  @param[in]  memhandler   Memory handler used to dynamically allocate
               output parameters, if applicable.
  @param[out] data         Sampled sensor data. The number of elements must
               match @a num_sensors.

  @return SNS_DDF_SUCCESS if data was populated successfully. If any of the
      sensors queried are to be read asynchronously SNS_DDF_PENDING is
      returned and data is via @a sns_ddf_smgr_data_notify() when
      available. Otherwise a specific error code is returned.

*/
/*=========================================================================*/

static sns_ddf_status_e sns_dd_get_data
(
    sns_ddf_handle_t        dd_handle,
    sns_ddf_sensor_e        sensors[],
    uint32_t                num_sensors,
    sns_ddf_memhandler_s*   memhandler,
    sns_ddf_sensor_data_s*  data[]
)
{
    sns_ddf_status_e status = SNS_DDF_SUCCESS;
    sns_dd_ams_t*    state = (sns_dd_ams_t*)(((uint32_t)dd_handle) & (uint32_t)(~DD_HANDLE_ALIGN));
    uint32_t         sub_dev_id = (uint32_t)dd_handle & ((uint32_t)DD_HANDLE_ALIGN);
    sns_ddf_time_t   timeStamp = sns_ddf_get_timestamp();
    uint32_t         i = 0;
    int32_t updateAvailableFlags;

//    DD_MSG_1(HIGH, "sns_dd_get_data: ENTER %p", dd_handle);
    DD_MSG_2(MED,  "sns_dd_get_data: num of sensors: %d, sub_dev_id: %d", num_sensors, sub_dev_id);
    DD_MSG_1(MED,  "sns_dd_get_data: sensors[0]: %d", sensors[0]);
    if (num_sensors > 1)
        DD_MSG_1(MED,  "sns_dd_get_data: sensors[1]: %d", sensors[1]);

    if (num_sensors == 0)
    {
        DD_MSG_0(HIGH, "sns_dd_get_data: num_sensors == 0");
        DD_MSG_0(HIGH, "sns_dd_get_data: EXIT, EINVALID");

        return SNS_DDF_EINVALID_PARAM;
    }

    if ((state == NULL) || (sub_dev_id >= state->ams_max_supported_features)) {
        DD_MSG_1(HIGH, "sns_dd_get_data: state == NULL or sub_dev_id >= NUM_SUB_DEV (%d)", sub_dev_id);
        DD_MSG_0(HIGH, "sns_dd_get_data: EXIT 2");
        return SNS_DDF_EINVALID_PARAM;
    }
#ifdef CONFIG_AMS_USE_SCRATCH_MEMORY
    if (sns_ddf_malloc_ex((void **)&state->chip.scratch, sizeof(ams_scratch_t), state->sub_dev[sub_dev_id].smgr_handle) != SNS_DDF_SUCCESS) {
            DD_MSG_0(ERROR,"sns_dd_get_data: malloc ams_scratch_t failed");
            return SNS_DDF_EINVALID_PARAM;
    }
#endif
    DD_MSG_0(LOW, "sns_dd_get_data: => ams_deviceEventHandler");
    ams_deviceEventHandler(&state->chip);
    updateAvailableFlags = ams_getResult(&state->chip);

    *data = sns_ddf_memhandler_malloc_ex(memhandler, num_sensors * sizeof(sns_ddf_sensor_data_s), state->sub_dev[sub_dev_id].smgr_handle);
    if(*data == NULL)
    {
      DD_MSG_0(ERROR, "malloc error");
      return SNS_DDF_ENOMEM;
    }
    
    do{
        sns_ddf_sensor_data_s*  data_ptr = &((*data)[i]);
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS
        if (sensors[i] == SNS_DDF_SENSOR_AMBIENT){
            ams_deviceSetConfig(&state->chip, AMS_CONFIG_ALS_LUX, AMS_CONFIG_THRESHOLD, 0); /* needed to disable interrupts */
            ams_generateAlsResponse(state, memhandler, &data_ptr, sub_dev_id, timeStamp);
        }
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS_RGB
        do {
            bool doRgbFirst;
            if (sensors[i] == SNS_DDF_SENSOR_RGB){
                ams_deviceSetConfig(&state->chip, AMS_CONFIG_ALS_RGB, AMS_CONFIG_THRESHOLD, 0); /* needed to disable interrupts */
                if (((i+1) < num_sensors)  &&  (sensors[i+1] == SNS_DDF_SENSOR_CT_C))
                {
                    doRgbFirst = true;
                    ams_generateAlsRgbCtResponse(state, memhandler, &data_ptr, sub_dev_id, timeStamp, doRgbFirst);
                    i++;
                    break;
                }
                else
                {
                    ams_generateAlsRgbResponse(state, memhandler, &data_ptr, sub_dev_id, timeStamp);
                }
            }
            if (sensors[i] == SNS_DDF_SENSOR_CT_C){
                ams_deviceSetConfig(&state->chip, AMS_CONFIG_ALS_CT, AMS_CONFIG_THRESHOLD, 0); /* needed to disable interrupts */
                if (((i+1) < num_sensors)  &&  (sensors[i+1] == SNS_DDF_SENSOR_RGB))
                {
                    doRgbFirst = false;
                    ams_generateAlsRgbCtResponse(state, memhandler, &data_ptr, sub_dev_id, timeStamp, doRgbFirst);
                    i++;
                    break;
                }
                else
                {
                    ams_generateAlsCtResponse(state, memhandler, &data_ptr, sub_dev_id, timeStamp);
                }
            }
        } while (0);
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS_WIDEBAND
        if (sensors[i] == SNS_DD_SENSOR_WIDEBAND){
            ams_deviceSetConfig(&state->chip, AMS_CONFIG_ALS_WIDEBAND, AMS_CONFIG_THRESHOLD, 0); /* needed to disable interrupts */
            ams_generateAlsWbResponse(state, memhandler, &data_ptr, sub_dev_id, timeStamp);
        }
#endif
#endif //CONFIG_AMS_OPTICAL_SENSOR_ALS_RGB
#ifdef CONFIG_AMS_OPTICAL_SENSOR_PROX
        if (sensors[i] == SNS_DDF_SENSOR_PROXIMITY && (updateAvailableFlags & (1 << AMS_PROXIMITY_SENSOR))){
            ams_deviceSetConfig(&state->chip, AMS_CONFIG_PROX, AMS_CONFIG_THRESHOLD, 0); /* needed to disable interrupts */
            ams_generateProxResponse(state, memhandler, &data_ptr, sub_dev_id, timeStamp);
        }
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_GESTURE
        if (sensors[i] == SNS_DDF_SENSOR_IR_GESTURE){
            ams_deviceSetConfig(&state->chip, AMS_CONFIG_GESTURE, AMS_CONFIG_THRESHOLD, 0); /* needed to disable interrupts */
            ams_generateGestureResponse(state, memhandler, &data_ptr, sub_dev_id, timeStamp);
        }
#endif
      i++;
    } while (i < num_sensors);
#ifdef CONFIG_AMS_USE_SCRATCH_MEMORY
    sns_ddf_mfree_ex(state->chip.scratch, state->sub_dev[sub_dev_id].smgr_handle);
#endif
    DD_MSG_0(HIGH, "sns_dd_get_data: EXIT 99");
    return status;
}

/*===========================================================================

  FUNCTION:   sns_dd_ams_handleIrq

===========================================================================*/
/*!
  @brief AMS interrupt handler

  @detail
  This function will be called within the context of the Interrupt
  Service Task (IST), *not* the ISR.

  @param[in] dd_handle  Handle to a driver instance.
  @param[in] irq        The IRQ representing the interrupt that occured.

  @return None
*/
/*=========================================================================*/
static void sns_dd_handle_irq
(
    sns_ddf_handle_t  dd_handle,
    uint32_t          gpio_num,
    sns_ddf_time_t    timestamp
)
{
    int32_t updateAvailableFlags;
    sns_dd_ams_t* state = (sns_dd_ams_t*)(((uint32_t)dd_handle) & (uint32_t)(~DD_HANDLE_ALIGN));
    uint32_t      sub_dev_id = (uint32_t)dd_handle & ((uint32_t)DD_HANDLE_ALIGN);

    DD_MSG_1(HIGH, "sns_dd_handle_irq: ENTER %p", dd_handle);
    DD_MSG_0(MED, "HndlIrq: ENTER ***********************************************");

#ifdef CONFIG_AMS_USE_SCRATCH_MEMORY
    if (sns_ddf_malloc_ex((void **)&state->chip.scratch, sizeof(ams_scratch_t), state->sub_dev[sub_dev_id].smgr_handle) != SNS_DDF_SUCCESS) {
            DD_MSG_0(ERROR,"sns_dd_handle_irq: malloc ams_scratch_t failed");
            return;
    }
#endif

    DD_MSG_0(LOW, "sns_dd_handle_irq: => ams_deviceEventHandler");
    ams_deviceEventHandler(&state->chip);
    updateAvailableFlags = ams_getResult(&state->chip);
    if (updateAvailableFlags == AMS_CALIBRATION_DONE) {
        /* ALS calibration done */
        DD_MSG_0(MED, "sns_dd_handle_irq: update calibration data");
        sns_ddf_smgr_notify_event(state->sub_dev[sub_dev_id].smgr_handle,
                SNS_DDF_SENSOR__ALL,
                SNS_DDF_EVENT_UPDATE_REGISTRY_GROUP);
        if (state->report_mask & SENSOR_MASK_ALS) {
            DD_MSG_0(MED, "sns_dd_handle_irq: ALS AMS_CALIBRATION_DONE");
            state->report_mask &= ~SENSOR_MASK_ALS;
            sns_ddf_smgr_notify_test_complete(state->sub_dev[sub_dev_id].smgr_handle,
                    SNS_DDF_SENSOR_AMBIENT,
                    SNS_DDF_SUCCESS,
                    0);
        }
        if (state->report_mask & SENSOR_MASK_PROX) {
            DD_MSG_0(MED, "sns_dd_handle_irq: PROX AMS_CALIBRATION_DONE");
            state->report_mask &= ~SENSOR_MASK_PROX;
            sns_ddf_smgr_notify_test_complete(state->sub_dev[sub_dev_id].smgr_handle,
                    SNS_DDF_SENSOR_PROXIMITY,
                    SNS_DDF_SUCCESS,
                    0);
        }
    } else if (updateAvailableFlags == AMS_CALIBRATION_DONE_BUT_FAILED) {
        if (state->report_mask & SENSOR_MASK_ALS) {
            DD_MSG_0(MED, "sns_dd_handle_irq: ALS AMS_CALIBRATION_DONE_BUT_FAILED");
            state->report_mask &= ~SENSOR_MASK_ALS;
            sns_ddf_smgr_notify_test_complete(state->sub_dev[sub_dev_id].smgr_handle,
                    SNS_DDF_SENSOR_AMBIENT,
                    SNS_DDF_EFAIL,
                    0);
        }
        if (state->report_mask & SENSOR_MASK_PROX) {
            DD_MSG_0(MED, "sns_dd_handle_irq: PROX AMS_CALIBRATION_DONE_BUT_FAILED");
            state->report_mask &= ~SENSOR_MASK_PROX;
            sns_ddf_smgr_notify_test_complete(state->sub_dev[sub_dev_id].smgr_handle,
                    SNS_DDF_SENSOR_PROXIMITY,
                    SNS_DDF_EFAIL,
                    0);
        }
    } else {
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS
        if (updateAvailableFlags & (1 << AMS_AMBIENT_SENSOR)){
            DD_MSG_0(LOW, "updateAvailableFlags => AMS_AMBIENT_SENSOR");
            if (state->report_mask & SENSOR_MASK_ALS)
                ams_generateAlsResponse(state, NULL, NULL, state->als_sub_dev_idx, timestamp);
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS_RGB
            if ((state->report_mask & (SENSOR_MASK_RGB | SENSOR_MASK_CT)) == (SENSOR_MASK_RGB | SENSOR_MASK_CT))
                ams_generateAlsRgbCtResponse(state, NULL, NULL, state->rgb_sub_dev_idx, timestamp, true);
            else
            {
                if (state->report_mask & SENSOR_MASK_RGB)
                    ams_generateAlsRgbResponse(state, NULL, NULL, state->rgb_sub_dev_idx, timestamp);
                if (state->report_mask & SENSOR_MASK_CT)
                    ams_generateAlsCtResponse(state, NULL, NULL, state->cct_sub_dev_idx, timestamp);
            }
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS_WIDEBAND
            if (state->report_mask & SENSOR_MASK_WIDEBAND)
                    ams_generateAlsWbResponse(state, NULL, NULL, state->wideband_sub_dev_idx, timestamp);
#endif
        }
#endif //CONFIG_AMS_OPTICAL_SENSOR_ALS

#ifdef CONFIG_AMS_OPTICAL_SENSOR_PROX
        if (updateAvailableFlags & (1 << AMS_PROXIMITY_SENSOR)){
            DD_MSG_0(LOW, "updateAvailableFlags => AMS_PROXIMITY_SENSOR");
            if (state->report_mask & SENSOR_MASK_PROX)
                ams_generateProxResponse(state, NULL, NULL, state->prox_sub_dev_idx, timestamp);
        }
#endif

#ifdef CONFIG_AMS_OPTICAL_SENSOR_GESTURE
        if (updateAvailableFlags & (1 << AMS_GESTURE_SENSOR)){
            DD_MSG_0(LOW, "updateAvailableFlags => AMS_GESTURE_SENSOR");
            if (state->report_mask & SENSOR_MASK_GESTURE)
                ams_generateGestureResponse(state, NULL, NULL, state->gesture_sub_dev_idx, timestamp);
        }
#endif
    }
#ifdef CONFIG_AMS_USE_SCRATCH_MEMORY
    sns_ddf_mfree_ex(state->chip.scratch, state->sub_dev[sub_dev_id].smgr_handle);
#endif
    DD_MSG_0(MED, "HndlIrq: EXIT");
}


static sns_ddf_status_e sns_dd_process_daf_req(
  sns_ddf_handle_t       dd_handle,
  uint32_t               req_id,
  const void*            req_msg,
  uint32_t               req_size,
  sns_ddf_memhandler_s*  memhandler,
  void**                 resp_msg,
  uint32_t*              resp_size,
  const uint8_t*         trans_id_ptr,
  void*                  conn_handle)
{
  sns_ddf_status_e   err_code = SNS_DDF_SUCCESS;

  uint32_t         sub_dev_id = (uint32_t)dd_handle & ((uint32_t)DD_HANDLE_ALIGN);
  sns_dd_ams_t*    state = (sns_dd_ams_t*)(((uint32_t)dd_handle) & (uint32_t)(~DD_HANDLE_ALIGN));
  int id = 0;
  ams_configureFeature_t feature = AMS_CONFIG_FEATURE_LAST; // init to invalid
  uint32_t thresh;

  if ((dd_handle == NULL) || (memhandler == NULL))
  {
    DD_MSG_0(ERROR, "process_daf_req handle is NULL");
    return SNS_DDF_EINVALID_PARAM;
  }

  if (dd_handle == NULL || sub_dev_id >= state->sub_dev_count)
  {
    return SNS_DDF_EINVALID_PARAM;
  }

  DD_MSG_1(HIGH,
    "sns_dd_ams_tmd490x_process_daf_req: req_id %d",
    req_id);
  switch (req_id)
  {
  case SNS_DAF_GENERAL_REVERB_START_V01: id = 0; break;
  case SNS_DAF_GENERAL_REVERB_STOP_V01: id = 0; break;
  case SNS_DAF_PROX_POLLING_START_V01: id = 1; break;
  case SNS_DAF_PROX_POLLING_STOP_V01: id = 1; break;
  case SNS_DAF_ALS_RGB_POLLING_START_V01: id = 2; break;
  case SNS_DAF_ALS_RGB_POLLING_STOP_V01: id = 2; break;
  }
  /* Set default values */
  *resp_size = 0;

  /* All of the DAF message processing happens in this switch statement */
  switch (req_id)
  {
  case SNS_DAF_GENERAL_WHO_AM_I_V01:
  {
    DD_MSG_0(HIGH, "SNS_DAF_GENERAL_WHO_AM_I_V01");

    sns_daf_general_who_am_i_resp_v01* resp_msg_ptr;

    /* conn_handle is not used for this message since this message does not make use of indications */
    (void)conn_handle;

    /* No need to validate the request message. The message should be empty. */

    /* Read the WHO AM I (ID) register and return the information in the response.
       Allocate the response message and fill it in */
    resp_msg_ptr = sns_ddf_memhandler_malloc_ex(memhandler, sizeof(sns_daf_general_who_am_i_resp_v01), state->sub_dev[sub_dev_id].smgr_handle);
    if (resp_msg_ptr == NULL)
    {
      err_code = SNS_DDF_ENOMEM;
      DD_MSG_1(ERROR, "daf error - memhandler %d", err_code);
      break;
    }

    resp_msg_ptr->hardware_id = (uint32_t)0x1111;
    resp_msg_ptr->firmware_id = (uint32_t)0x1000;

    DD_MSG_1(HIGH, "hardware ID %x ", resp_msg_ptr->hardware_id);
    DD_MSG_1(HIGH, "firmware ID %x ", resp_msg_ptr->firmware_id);

    *resp_msg = resp_msg_ptr;
    *resp_size = sizeof(sns_daf_general_who_am_i_resp_v01);

    err_code = sns_ddf_smgr_notify_event(
      state->sub_dev[sub_dev_id].smgr_handle,
      state->sub_dev[sub_dev_id].sensors[0],
      SNS_DDF_EVENT_DAF_INACTIVE);
    if (err_code != SNS_DDF_SUCCESS)
    {
      DD_MSG_1(ERROR, "daf error - smgr_notify_event %d", err_code);
      break;
    }
    err_code = SNS_DDF_SUCCESS;
    break;
  }
  case SNS_DAF_GENERAL_ECHO_V01:
  {
    DD_MSG_0(HIGH, "SNS_DAF_GENERAL_ECHO_V01");

    const sns_daf_general_echo_req_v01 *req_msg_ptr = req_msg;
    sns_daf_general_echo_resp_v01 *resp_msg_ptr;

    /* Allocate the response message and fill it in */
    resp_msg_ptr = sns_ddf_memhandler_malloc_ex(memhandler, sizeof(sns_daf_general_echo_resp_v01), state->sub_dev[sub_dev_id].smgr_handle);
    if (resp_msg_ptr == NULL)
    {
      err_code = SNS_DDF_ENOMEM;
      DD_MSG_1(ERROR, "daf error - memhandler %d", err_code);
      break;
    }

    resp_msg_ptr->echo = req_msg_ptr->echo;

    *resp_msg = resp_msg_ptr;
    *resp_size = sizeof(sns_daf_general_echo_resp_v01);

    err_code = SNS_DDF_SUCCESS;
    break;
  }
  case SNS_DAF_GENERAL_REVERB_START_V01:
  {
    DD_MSG_0(HIGH, "SNS_DAF_GENERAL_REVERB_START_V01");

    const sns_daf_general_reverb_start_req_v01 *req_msg_ptr = req_msg;
    sns_daf_general_reverb_start_resp_v01 *resp_msg_ptr;

    /* Save the DAF request ID */
    state->daf_reqs[id].daf_active_req = req_id;

    /* Save the conn_handle */
    state->daf_reqs[id].daf_conn_handle = conn_handle;

    /* Save if the trans_id, if it exists */
    if (NULL != trans_id_ptr)
    {
        state->daf_reqs[id].daf_trans_id_valid = TRUE;
        state->daf_reqs[id].daf_trans_id = *trans_id_ptr;
    }
    else
    {
        state->daf_reqs[id].daf_trans_id_valid = FALSE;
    }

    state->daf_reqs[id].daf_echo = req_msg_ptr->echo;

    DD_MSG_1(ERROR, "state->daf_echo : %d", state->daf_reqs[id].daf_echo);

    /* Start a periodic timer */
    err_code = sns_ddf_timer_start(state->daf_reqs[id].daf_timer, req_msg_ptr->reverb_period);
    if (err_code != SNS_DDF_SUCCESS)
    {
        DD_MSG_1(ERROR, "daf error - timer_start %d", err_code);
        break;
    }

    /* Notify the SMGR of a DAF Request becoming active */
    err_code = sns_ddf_smgr_notify_event(
        state->sub_dev[sub_dev_id].smgr_handle,
        state->sub_dev[sub_dev_id].sensors[0],
        SNS_DDF_EVENT_DAF_ACTIVE);
    if (err_code != SNS_DDF_SUCCESS)
    {
        DD_MSG_1(ERROR, "daf error - smgr_notify_event %d", err_code);
        break;
    }

    /* Allocate the response message and fill it in */
    resp_msg_ptr = sns_ddf_memhandler_malloc_ex(memhandler, sizeof(sns_daf_general_reverb_start_resp_v01), state->sub_dev[sub_dev_id].smgr_handle);
    if (resp_msg_ptr == NULL)
    {
      err_code = SNS_DDF_ENOMEM;
      DD_MSG_1(ERROR, "daf error - memhandler %d", err_code);
      break;
    }

    resp_msg_ptr->echo = req_msg_ptr->echo;

    DD_MSG_2(HIGH, "ALSPRX - echo %d reverb_period %d", req_msg_ptr->echo, req_msg_ptr->reverb_period);

    *resp_msg = resp_msg_ptr;
    *resp_size = sizeof(sns_daf_general_reverb_start_resp_v01);

    err_code = SNS_DDF_SUCCESS;
    break;
  }
  case SNS_DAF_GENERAL_REVERB_STOP_V01:
  {
    DD_MSG_0(HIGH, "SNS_DAF_GENERAL_REVERB_STOP_V01");

    /* Cancel the DAF request timer */
    err_code = sns_ddf_timer_cancel(state->daf_reqs[id].daf_timer);
    if (err_code != SNS_DDF_SUCCESS)
    {
      DD_MSG_1(ERROR, "daf error - timer cancel %d", err_code);
      break;
    }

    /* Notify the SMGR of a DAF Request becoming inactive */
    err_code = sns_ddf_smgr_notify_event(
      state->sub_dev[sub_dev_id].smgr_handle,
      state->sub_dev[sub_dev_id].sensors[0],
      SNS_DDF_EVENT_DAF_INACTIVE);
    if (err_code != SNS_DDF_SUCCESS)
    {
      DD_MSG_1(ERROR, "daf error - smgr_notify_event %d", err_code);
      break;
    }

    err_code = SNS_DDF_SUCCESS;
    break;
  }
  /* These two requests happen to have the same structure so this logic is common */
  case SNS_DAF_PROX_POLLING_START_V01:
  case SNS_DAF_ALS_RGB_POLLING_START_V01:
  {
    uint32_t sampling_period;
    const sns_daf_prox_polling_start_req_v01 *req_msg_ptr = req_msg;
    sns_daf_prox_polling_start_resp_v01 *resp_msg_ptr;

    /* Save the DAF request ID */
    state->daf_reqs[id].daf_active_req = req_id;

    /* Save the conn_handle */
    state->daf_reqs[id].daf_conn_handle = conn_handle;

    /* Save if the trans_id, if it exists */
    if (NULL != trans_id_ptr)
    {
      state->daf_reqs[id].daf_trans_id_valid = TRUE;
      state->daf_reqs[id].daf_trans_id = *trans_id_ptr;
    }
    else
    {
      state->daf_reqs[id].daf_trans_id_valid = FALSE;
    }

    /* Verify the sampling period and adjust it, if necessary */
    sampling_period = req_msg_ptr->sampling_period_us;
    /* Limit the sampling rate to 100 Hz or less */
    if (sampling_period < 10000)
    {
      sampling_period = 10000;
    }
    DD_MSG_1(HIGH, "<<SNS_DAF_{PROX,RGB}_POLLING_START_V01>>  period = %d", sampling_period);
    DD_MSG_1(HIGH, "<<SNS_DAF_{PROX,RGB}_POLLING_START_V01>>  timer* = %p", state->daf_reqs[id].daf_timer);

    /* Start a periodic timer */
    err_code = sns_ddf_timer_start(state->daf_reqs[id].daf_timer, sampling_period);
    if (err_code != SNS_DDF_SUCCESS)
    {
      DD_MSG_1(ERROR, "daf error - timer_start %d", err_code);
      break;
    }

    if (req_id == SNS_DAF_PROX_POLLING_START_V01){
        feature = AMS_CONFIG_PROX_ALT_REPORT;
        state->report_mask |= SENSOR_MASK_PROX_ALT_REPORT;
        thresh = 1;
    } else {
        feature = AMS_CONFIG_ALS_RGB_ALT_REPORT;
        state->report_mask |= SENSOR_MASK_PROX_ALT_REPORT;
        thresh = AMS_CONFIG_ALS_THRESHOLD_PERCENT;
    }
    ams_deviceSetConfig(&state->chip, feature, AMS_CONFIG_THRESHOLD, thresh); /* needed to generate interrupts */
    ams_deviceSetConfig(&state->chip, feature, AMS_CONFIG_ENABLE, 1);

    /* Notify the SMGR of a DAF Request becoming active */
    err_code = sns_ddf_smgr_notify_event(
      state->sub_dev[sub_dev_id].smgr_handle,
      state->sub_dev[sub_dev_id].sensors[0],
      SNS_DDF_EVENT_DAF_ACTIVE);
    if (err_code != SNS_DDF_SUCCESS)
    {
      DD_MSG_1(ERROR, "daf error - smgr_notify_event %d", err_code);
      break;
    }

    /* Allocate the response message and fill it in */
    resp_msg_ptr = sns_ddf_memhandler_malloc_ex(memhandler, sizeof(sns_daf_prox_polling_start_resp_v01), state->sub_dev[sub_dev_id].smgr_handle);
    if (resp_msg_ptr == NULL)
    {
      err_code = SNS_DDF_ENOMEM;
      DD_MSG_1(ERROR, "daf error - memhandler %d", err_code);
      break;
    }

    resp_msg_ptr->actual_sampling_period_us = sampling_period;

    *resp_msg = resp_msg_ptr;
    *resp_size = sizeof(sns_daf_prox_polling_start_resp_v01);

    err_code = SNS_DDF_SUCCESS;
    break;
  }
  /* Both of these DAF requests execute the same set of actions */
  case SNS_DAF_PROX_POLLING_STOP_V01:
  case SNS_DAF_ALS_RGB_POLLING_STOP_V01:
  {
    DD_MSG_0(HIGH, "SNS_DAF_{PROX,RGB}_POLLING_STOP_V01");

    /* Cancel the DAF request timer */
    err_code = sns_ddf_timer_cancel(state->daf_reqs[id].daf_timer);
    if (err_code != SNS_DDF_SUCCESS)
    {
      DD_MSG_1(ERROR, "daf error - timer cancel %d", err_code);
      break;
    }

    if (req_id == SNS_DAF_PROX_POLLING_STOP_V01){
        feature = AMS_CONFIG_PROX_ALT_REPORT;
        state->report_mask &= ~SENSOR_MASK_PROX_ALT_REPORT;
        thresh = 1;
    } else {
        feature = AMS_CONFIG_ALS_RGB_ALT_REPORT;
        state->report_mask &= ~SENSOR_MASK_RGB_ALT_REPORT;
        thresh = AMS_CONFIG_ALS_THRESHOLD_PERCENT;
    }
    ams_deviceSetConfig(&state->chip, feature, AMS_CONFIG_ENABLE, 0);

    /* Notify the SMGR of a DAF Request becoming inactive */
    err_code = sns_ddf_smgr_notify_event(
      state->sub_dev[sub_dev_id].smgr_handle,
      state->sub_dev[sub_dev_id].sensors[0],
      SNS_DDF_EVENT_DAF_INACTIVE);
    if (err_code != SNS_DDF_SUCCESS)
    {
      DD_MSG_1(ERROR, "daf error - smgr_notify_event %d", err_code);
      break;
    }

    err_code = SNS_DDF_SUCCESS;
    break;
  }
#ifdef CONFIG_AMS_OPTICAL_SENSOR_IRBEAM_CCB
  case SNS_DAF_MOBEAM_SEND_COUNT_V01:
  {
    const sns_daf_general_send_byte_array_v01* req_msg_ptr = req_msg;

    DD_MSG_1(HIGH, "SNS_DAF_MOBEAM_SEND_COUNT_V01 count:%d", req_msg_ptr->byte_array[0]);
    if (!ams_deviceSetIrBeamConfig(&state->chip, IRBEAM_COUNT, 1, &req_msg_ptr->byte_array[0]))
        err_code = SNS_DDF_EINVALID_DATA;

    break;
  }
  case SNS_DAF_MOBEAM_SEND_REG_V01:
  {
    const sns_daf_general_send_byte_array_v01* req_msg_ptr = req_msg;

    DD_MSG_1(HIGH, "SNS_DAF_MOBEAM_SEND_REG_V01 hop idx:%d", req_msg_ptr->byte_array[0]);
    if (!ams_deviceSetIrBeamConfig(&state->chip, IRBEAM_HOP, req_size, &req_msg_ptr->byte_array[0]))
        err_code = SNS_DDF_EINVALID_DATA;

    break;
  }
  case SNS_DAF_MOBEAM_SEND_DATA_V01:
  {
    const sns_daf_general_send_byte_array_v01* req_msg_ptr = req_msg;
    uint8_t size = strlen((const char*)req_msg_ptr->byte_array);

    DD_MSG_1(HIGH, "SNS_DAF_MOBEAM_SEND_DATA_V01 size:%d", size);
    if (!ams_deviceSetIrBeamConfig(&state->chip, IRBEAM_PATTERN, req_size, &req_msg_ptr->byte_array[0]))
        err_code = SNS_DDF_EINVALID_DATA;

    break;
  }
  case SNS_DAF_MOBEAM_START_V01:
  {
    sns_ddf_status_e status = SNS_DDF_SUCCESS;

    DD_MSG_0(HIGH, "SNS_DAF_MOBEAM_START_V01");

    ams_deviceSetConfig(&state->chip, AMS_CONFIG_MOBEAM, AMS_CONFIG_ENABLE, 1);

    status = sns_ddf_signal_register(state->sub_dev[sub_dev_id].interrupt_gpio,
                dd_handle,
                &sns_dd_vendor_if_1,
                SNS_DDF_SIGNAL_IRQ_FALLING);
    if (status != SNS_DDF_SUCCESS) {
        DD_MSG_1(MED, "SNS_DAF_MOBEAM_START_V01: EXIT %d", status);
    } else {
        state->chip.ccbIrBeamCtx.hop_index = 0;
        ccb_irBeam_xmit((ams_deviceCtx_t*)&state->chip);
    }
    break;
  }
  case SNS_DAF_MOBEAM_STOP_V01:
  {
    sns_ddf_status_e status = SNS_DDF_SUCCESS;

    DD_MSG_0(HIGH, "SNS_DAF_MOBEAM_STOP_V01");

    if (state->chip.mode == MODE_IRBEAM) {
        status = sns_ddf_signal_deregister(state->sub_dev[sub_dev_id].interrupt_gpio);
        if (status != SNS_DDF_SUCCESS)
            DD_MSG_1(MED, "SNS_DAF_MOBEAM_STOP_V01: EXIT %d", status);
    }
    ams_deviceSetConfig(&state->chip, AMS_CONFIG_MOBEAM, AMS_CONFIG_ENABLE, 0);
    break;
  }
#endif /*CONFIG_AMS_OPTICAL_SENSOR_IRBEAM_CCB*/
#if 0
  case SNS_DAF_PROX_THD_HI_V01:
  {
    sns_ddf_status_e status = SNS_DDF_SUCCESS;
    const sns_daf_general_send_byte_array_v01* req_msg_ptr = req_msg;
    int32_t val = req_msg_ptr->int_array[0];

    state->nv_db.proxDetect = val;
    state->nv_db.thresh_near = val;
    state->chip.setup.prox.detect = state->nv_db.proxDetect;
    DD_MSG_2(MED, "DAF request:%d thd:%d", req_id, val);
    status = sns_ddf_smgr_notify_event(state->sub_dev[sub_dev_id].smgr_handle, SNS_DDF_SENSOR_PROXIMITY, SNS_DDF_EVENT_UPDATE_REGISTRY_GROUP);
    if (status != SNS_DDF_SUCCESS)
    {
      DDF_MSG_0(HIGH, "DAF: Could not notify SMGR");
      return status;
    }
    DD_MSG_0(HIGH, "DAF: successful reg update notify");
    break;
  }
  case SNS_DAF_PROX_THD_LO_V01:
  {
    sns_ddf_status_e status = SNS_DDF_SUCCESS;
    const sns_daf_general_send_byte_array_v01* req_msg_ptr = req_msg;
    int32_t val = req_msg_ptr->int_array[0];

    DD_MSG_2(MED, "DAF request:%d thd:%d", req_id, val);
    state->nv_db.proxRelease = val;
    state->nv_db.thresh_far = val;
    state->chip.setup.prox.release = state->nv_db.proxRelease;
    status = sns_ddf_smgr_notify_event(state->sub_dev[sub_dev_id].smgr_handle, SNS_DDF_SENSOR_PROXIMITY, SNS_DDF_EVENT_UPDATE_REGISTRY_GROUP);
    if (status != SNS_DDF_SUCCESS)
    {
      DDF_MSG_0(HIGH, "DAF: Could not notify SMGR");
      return status;
    }
    DD_MSG_0(HIGH, "DAF: successful reg update notify");
    break;
  }
#endif
  default:
  {
    DD_MSG_1(ERROR, "Unsupported DAF request : %d", req_id);
    /* Unsupported DAF request */
    err_code = SNS_DDF_EINVALID_DAF_REQ;
    break;
  }
  }

  return err_code;
}

static void sns_dd_cancel_daf_trans(
  sns_ddf_handle_t       dd_handle,
  void*                  conn_handle)
{
  sns_ddf_status_e   err_code = SNS_DDF_SUCCESS;
  sns_dd_ams_t*    state = (sns_dd_ams_t*)(((uint32_t)dd_handle) & (uint32_t)(~DD_HANDLE_ALIGN));
  uint32_t         sub_dev_id = (uint32_t)dd_handle & ((uint32_t)DD_HANDLE_ALIGN);
  int i, id = -1;

  if (dd_handle == NULL)
  {
    DD_MSG_0(ERROR, "cancel_daf_trans handle is NULL");
    return;
  }


  if (dd_handle == NULL || sub_dev_id >= state->sub_dev_count)
  {
    return;
  }

  DD_MSG_1(HIGH,
    "sns_dd_ams_tmd490x_cancel_daf_trans: conn_handle %d",
    conn_handle);

  for (i = 0; i < DD_MAX_DAF_REQS; i++)
  {
    if (state->daf_reqs[i].daf_conn_handle == conn_handle)
    {
      id = i;
    }
  }

  /* If there is a DAF request that is active for the given conn_handle */
  if (id >= 0 && state->daf_reqs[id].daf_active_req != SNS_DAF_NO_MSG)
  {
    /* Cancel the DAF request timer */
    err_code = sns_ddf_timer_cancel(state->daf_reqs[id].daf_timer);
    if (err_code != SNS_DDF_SUCCESS)
    {
      DD_MSG_1(ERROR,
        "sns_dd_tmd490x_cancel_daf_trans: error canceling timer %d",
        err_code);
    }

    /* Notify the SMGR of a DAF Request becoming inactive */
    err_code = sns_ddf_smgr_notify_event(
      state->sub_dev[sub_dev_id].smgr_handle,
      state->sub_dev[sub_dev_id].sensors[0],
      SNS_DDF_EVENT_DAF_INACTIVE);
    if (err_code != SNS_DDF_SUCCESS)
    {
      DD_MSG_1(ERROR,
        "sns_dd_tmd490x_cancel_daf_trans: error notifying SMGR %d",
        err_code);
    }

    /* DAF Request has been successfully deactivated */
    state->daf_reqs[id].daf_active_req = SNS_DAF_NO_MSG;
  }
}


static void ams_handle_daf_req_timer
(
  sns_dd_ams_t* state,
  sns_ddf_timer_s* timer
  )
{
  sns_ddf_status_e err_code;
  sns_dd_daf_s* daf_req = NULL;
  int i;
  // Use the timer pointer to find the accompanying DAF request
  for (i = 0; i < DD_MAX_DAF_REQS; i++)
  {
    if (timer == &state->daf_reqs[i].daf_timer)
    {
      daf_req = &state->daf_reqs[i];
      DD_MSG_1(MED, "ams_handle_daf_req_timer:  points to daf_reqs[%d]", i);
#if 0 /*JIMR_D*/
      DD_MSG_1(MED, "                           daf_active_req:      %u"  , state->daf_reqs[i].daf_active_req);
      DD_MSG_1(MED, "                           daf_conn_handle:     %p"  , state->daf_reqs[i].daf_conn_handle);
      DD_MSG_1(MED, "                           daf_trans_id_valid:  %u"  , state->daf_reqs[i].daf_trans_id_valid);
      DD_MSG_1(MED, "                           daf_trans_id:        %u"  , state->daf_reqs[i].daf_trans_id);
      DD_MSG_1(MED, "                           daf_timer:           %p  ", state->daf_reqs[i].daf_timer);
      DD_MSG_1(MED, "                           daf_timer_arg:       %u  ", state->daf_reqs[i].daf_timer_arg);
      DD_MSG_1(MED, "                           daf_echo:            %08x", state->daf_reqs[i].daf_echo);
      return;
#endif
      break;
    }
  }

  // Accompanying DAF request was not found for this timer, exit out
  if (NULL == daf_req)
  {
    DD_MSG_1(ERROR, "handle_daf_req_timer: unable to service timer 0x%x", timer);
    return;
  }

  switch (daf_req->daf_active_req)
  {
  case SNS_DAF_GENERAL_REVERB_START_V01:
  {
    sns_daf_general_reverb_ind_v01 ind_msg;

    uint8_t *trans_id_ptr = NULL;
    if (daf_req->daf_trans_id_valid)
      trans_id_ptr = &daf_req->daf_trans_id;

    // Create the DAF indication
    ind_msg.echo = daf_req->daf_echo;

    // Send the DAF indication through the SMGR
    err_code = sns_ddf_smgr_notify_daf_ind(
      SNS_DAF_GENERAL_REVERB_IND_V01,
      &ind_msg,
      sizeof(ind_msg),
      trans_id_ptr,
      daf_req->daf_conn_handle);
    if (err_code != SNS_DDF_SUCCESS)
      DD_MSG_1(ERROR, "Error sending DAF ind %d", err_code);
    break;
  }

  case SNS_DAF_PROX_POLLING_START_V01:
  {
    sns_daf_prox_polling_report_v01 ind_msg;

    uint8_t *trans_id_ptr = NULL;

    if (daf_req->daf_trans_id_valid)
      trans_id_ptr = &daf_req->daf_trans_id;

    ams_deviceEventHandler(&state->chip);

    // Create the DAF indication
    ind_msg.prox_adc = state->chip.ccbProxCtx.pData;
    // Send the DAF indication through the SMGR
    err_code = sns_ddf_smgr_notify_daf_ind(
      SNS_DAF_PROX_POLLING_REPORT_V01,
      &ind_msg,
      sizeof(ind_msg),
      trans_id_ptr,
      daf_req->daf_conn_handle);
    if (err_code != SNS_DDF_SUCCESS)
      DD_MSG_1(ERROR, "Error sending DAF ind %d", err_code);
    break;
  }

  case SNS_DAF_ALS_RGB_POLLING_START_V01:
  {
    sns_daf_als_rgb_polling_report_v01 ind_msg;

    uint8_t *trans_id_ptr = NULL;
    if (daf_req->daf_trans_id_valid)
      trans_id_ptr = &daf_req->daf_trans_id;

    ams_deviceEventHandler(&state->chip);

    // Create the DAF indication
    ind_msg.als_data = state->chip.ccbAlsCtx.ctxAlgAls.results.rawClear;
    ind_msg.r_data = state->chip.ccbAlsCtx.ctxAlgAls.results.rawRed;
    ind_msg.g_data = state->chip.ccbAlsCtx.ctxAlgAls.results.rawGreen;
    ind_msg.b_data = state->chip.ccbAlsCtx.ctxAlgAls.results.rawBlue;

    // Send the DAF indication through the SMGR
    err_code = sns_ddf_smgr_notify_daf_ind(
      SNS_DAF_ALS_RGB_POLLING_REPORT_V01,
      &ind_msg,
      sizeof(ind_msg),
      trans_id_ptr,
      daf_req->daf_conn_handle);
    if (err_code != SNS_DDF_SUCCESS)
      DD_MSG_1(ERROR, "Error sending DAF ind %d", err_code);
    break;
  }
  
  default:
  {
    // Unknown DAF request
    DD_MSG_1(ERROR, "handle_daf_req_timer - unknown DAF:%d", daf_req->daf_active_req);
    break;
  }
  }
}

bool ams_is_daf_active(sns_dd_ams_t* state)
{
  bool is_daf_active = FALSE;
  int i;

  for (i = 0; i < DD_MAX_DAF_REQS; i++)
  {
    if (SNS_DAF_NO_MSG != state->daf_reqs[i].daf_active_req)
    {
      is_daf_active = TRUE;
    }
  }

  return is_daf_active;
}


/*===========================================================================*/
/*
* @brief sns_dd_ams_490x_handle_timer: handle timer expiration
*
* @param[in] state - DD state handle.
* @param[in] arg - a ptr to a ptr to the specific timer object
*
* @return None
*/
/*===========================================================================*/
static void sns_dd_handle_timer
(
    sns_ddf_handle_t dd_handle,
    void*            arg
)
{
  sns_dd_ams_t*    state = (sns_dd_ams_t*)(((uint32_t)dd_handle) & (uint32_t)(~DD_HANDLE_ALIGN));

#ifdef ENABLE_DEBUG
    DD_MSG_1(MED, "HndlTimer: ENTER  arg=%p", arg);
#endif

    if (ams_is_daf_active(state))
        ams_handle_daf_req_timer(state, (sns_ddf_timer_s*)arg);
    else
        DD_MSG_1(ERROR, "handle_timer - Unexpected DAF timer event!! Timer=%p", arg);

#ifdef ENABLE_DEBUG
    DD_MSG_0(MED, "HndlTimer: EXIT");
#endif

}

#ifdef SENSORS_DD_DEV_FLAG
sns_ddf_driver_if_s sns_dd_vendor_if_1 =
#else
sns_ddf_driver_if_s sns_dd_tmg490x_if =
#endif
{
    .init = &sns_dd_init,
    .reset = &sns_dd_reset,
    .set_attrib = &sns_dd_set_attrib,
    .get_attrib = &sns_dd_get_attrib,
    .handle_irq = &sns_dd_handle_irq,
    .get_data = &sns_dd_get_data,
    .handle_timer = &sns_dd_handle_timer,
    .run_test = &sns_dd_run_test,
    .enable_sched_data = &sns_dd_enable_sched_data,
    .probe = &sns_dd_probe,
    .trigger_fifo_data = NULL,
    .process_daf_req = sns_dd_process_daf_req,
    .cancel_daf_trans = sns_dd_cancel_daf_trans
};

#ifdef SENSORS_DD_DEV_FLAG
sns_ddf_driver_if_s sns_dd_vendor_if_2 =
{
    .init = NULL,
    .reset = NULL,
    .set_attrib = NULL,
    .get_attrib = NULL,
    .handle_irq = NULL,
    .get_data = NULL,
    .handle_timer = NULL,
    .run_test = NULL,
    .enable_sched_data = NULL,
    .probe = NULL,
};
#endif

/*
Processing uImage file:
./ams_tmx490x_qcom_hd22/src/dev_com_iface/src/ams_device_com_interface.c
*/

/*
 * Device Communication Interface
 */

/*
 * @@AMS_REVISION_Id: c8e79b435fc6473b258ed9f0962c7786a891c81f
 */


uint8_t ams_getByte(AMS_PORT_portHndl * portHndl, ams_deviceRegister_t reg, uint8_t * readData)
{
    uint8_t read_count = 0;
    uint8_t length = 1;

    /* Sanity check input param */
    if(reg > DEVREG_REG_MAX)
    {
        return 0;
    }

    read_count = AMS_PORT_getByte(portHndl,
                                deviceRegisterDefinition[reg].address,
                                readData,
                                length);

    return read_count;
}

uint8_t ams_setByte(AMS_PORT_portHndl * portHndl, ams_deviceRegister_t reg, uint8_t data)
{
    uint8_t write_count = 0;
    uint8_t length = 1;

    /* Sanity check input param */
    if(reg > DEVREG_REG_MAX)
    {
        return 0;
    }

    write_count = AMS_PORT_setByte(portHndl,
                                deviceRegisterDefinition[reg].address,
                                &data,
                                length);

    return write_count;
}

uint8_t ams_getBuf(AMS_PORT_portHndl * portHndl, ams_deviceRegister_t reg, uint8_t * readData, uint8_t length)
{
    uint8_t read_count = 0;

    /* Sanity check input param */
    if(reg > DEVREG_REG_MAX)
    {
        return 0;
    }

    read_count = AMS_PORT_getByte(portHndl,
                                deviceRegisterDefinition[reg].address,
                                readData,
                                length);

    return read_count;
}

uint8_t ams_setBuf(AMS_PORT_portHndl * portHndl, ams_deviceRegister_t reg, uint8_t * data, uint8_t length)
{
    uint8_t write_count = 0;

    /* Sanity check input param */
    if(reg > DEVREG_REG_MAX)
    {
        return 0;
    }

    write_count = AMS_PORT_setByte(portHndl,
                                deviceRegisterDefinition[reg].address,
                                data,
                                length);

    return write_count;
}

uint8_t ams_getWord(AMS_PORT_portHndl * portHndl, ams_deviceRegister_t reg, uint16_t * readData)
{
    uint8_t read_count = 0;
    uint8_t length = sizeof(uint16_t);
    uint8_t buffer[sizeof(uint16_t)];

    /* Sanity check input param */
    if(reg > DEVREG_REG_MAX)
    {
        return 0;
    }

    read_count = AMS_PORT_getByte(portHndl,
                                deviceRegisterDefinition[reg].address,
                                buffer,
                                length);

    *readData = ((buffer[0] << AMS_ENDIAN_1) + (buffer[1] << AMS_ENDIAN_2));

    return read_count;
}

uint8_t ams_setWord(AMS_PORT_portHndl * portHndl, ams_deviceRegister_t reg, uint16_t data)
{
    uint8_t write_count = 0;
    uint8_t length = sizeof(uint16_t);
    uint8_t buffer[sizeof(uint16_t)];

    /* Sanity check input param */
    if(reg > DEVREG_REG_MAX)
    {
        return 0;
    }

    buffer[0] = ((data >> AMS_ENDIAN_1) & 0xff);
    buffer[1] = ((data >> AMS_ENDIAN_2) & 0xff);

    write_count = AMS_PORT_setByte(portHndl,
                                deviceRegisterDefinition[reg].address,
                                &buffer[0],
                                length);
    return write_count;
}

uint8_t ams_tmg490x_getField(AMS_PORT_portHndl * portHndl, ams_deviceRegister_t reg, uint8_t * data, ams_regMask_t mask)
{
    uint8_t read_count = 0;
    uint8_t length = 1;

    /* Sanity check input param */
    if(reg > DEVREG_REG_MAX)
    {
        return 0;
    }

    read_count = AMS_PORT_getByte(portHndl,
                                deviceRegisterDefinition[reg].address,
                                data,
                                length);

    *data &= mask;

    return read_count;
}

uint8_t ams_tmg490x_setField(AMS_PORT_portHndl * portHndl, ams_deviceRegister_t reg, uint8_t data, ams_regMask_t mask)
{
    uint8_t write_count = 1;
    uint8_t length = 1;
    uint8_t original_data;
    uint8_t new_data;

    AMS_PORT_getByte(portHndl,
                        deviceRegisterDefinition[reg].address,
                        &original_data,
                        length);

    new_data = original_data & ~mask;
    new_data |= (data & mask);

    if (new_data != original_data){
        write_count = AMS_PORT_setByte(portHndl,
                        deviceRegisterDefinition[reg].address,
                        &new_data,
                        length);
    }

    return write_count;
}

/*
Processing uImage file:
./ams_tmx490x_qcom_hd22/src/tmx490x_dev_ctrl_block/src/ams_device_control_block.c
*/

/*
 * @@AMS_COPYRIGHT_HEADER:
 */

/*
 * Device Control Block 399x
 */

/*
 * @@AMS_REVISION_Id: e77bb8690ffdb4d13f9a92c7fe149beace30b869
 */

#ifdef CONFIG_AMS_OPTICAL_SENSOR_PROX_CCB
#endif

#define HIGH    0xFF
#define LOW     0x00

deviceRegisterTable_t deviceRegisterDefinition[DEVREG_REG_MAX] = {
    { 0x80, 0x00 },
    { 0x81, 0xFF },
    { 0x82, 0x00 },
    { 0x83, 0xFF },
    { 0x84, 0x00 },
    { 0x85, 0x00 },
    { 0x86, 0x00 },
    { 0x87, 0x00 },
    { 0x88, 0x00 },
    { 0x89, 0x00 },
    { 0x8A, 0x00 },
    { 0x8B, 0x00 },
    { 0x8C, 0x00 },
    { 0x8D, 0xA0 },
    { 0x8E, 0x4f },
    { 0x8F, 0x00 },
    { 0x90, 0x00 },
    { 0x91, AMS_REV_ID },
    { 0x92, AMS_DEVICE_ID },
    { 0x93, 0x00 },
    { 0x94, 0x00 },
    { 0x95, 0x00 },
    { 0x96, 0x00 },
    { 0x97, 0x00 },
    { 0x98, 0x00 },
    { 0x99, 0x00 },
    { 0x9A, 0x00 },
    { 0x9B, 0x00 },
    { 0x9C, 0x00 },
    { 0x9D, 0x00 },
    { 0x9E, 0x00 },
    { 0x9F, 0x04 },

    { 0xA0, 0x00 },
    { 0xA1, 0x00 },
    { 0xA2, 0x00 },
    { 0xA3, 0x00 },
    { 0xA4, 0x00 },
    { 0xA5, 0x00 },
    { 0xA6, 0x40 },
    { 0xA7, 0x00 },
    { 0xA8, 0x00 },
    { 0xA9, 0x00 },
    { 0xAB, 0x00 },
    { 0xAC, 0x07 },
    { 0xAD, 0x08 },
    { 0xAF, 0x16 },

#if defined CONFIG_AMS_OPTICAL_SENSOR_GESTURE || defined CONFIG_AMS_OPTICAL_SENSOR_FLICKER
    { 0xB0, 0x00 },
    { 0xB1, 0x8F },
    { 0xB2, 0x80 },
    { 0xB3, 0x00 },
    { 0xB4, 0x0A },
    { 0xB5, 0x00 },
    { 0xB6, 0x40 },
    { 0xB7, 0x00 },
    { 0xB8, 0x00 },
    { 0xB9, 0x00 },
    { 0xBA, 0x00 },
    { 0xBB, 0x00 },
#endif
    { 0xBC, 0x00 },
    { 0xBD, 0x00 },

    { 0xC0, 0x00 },
    { 0xC1, 0x00 },
    { 0xC2, 0x00 },
    { 0xC3, 0x00 },
    { 0xC4, 0x00 },
    { 0xC5, 0x00 },
    { 0xC6, 0x40 },
    { 0xC7, 0x00 },

    { 0xD0, 0x00 },
    { 0xD1, 0x00 },
    { 0xD2, 0x00 },
    { 0xD3, 0x00 },
    { 0xD6, 0xFF },
    { 0xD7, 0x00 },
    { 0xD8, 0x44 },
    { 0xD9, 0x0C },
    { 0xDA, 0x20 },
    { 0xDB, 0x10 },
    { 0xDC, 0x07 },
    { 0xDD, 0x08 },
    { 0xDE, 0x08 }
#if defined CONFIG_AMS_OPTICAL_SENSOR_GESTURE || defined CONFIG_AMS_OPTICAL_SENSOR_FLICKER
  , { 0xF8, 0x00 },
    { 0xF9, 0x00 },
    { 0xFA, 0x00 },
    { 0xFB, 0x00 },
    { 0xFC, 0x00 },
    { 0xFD, 0x00 },
    { 0xFE, 0x00 },
    { 0xFF, 0x00 }
#endif
};

#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS_CCB
uint32_t alsGain_conversion[] = { 1 * 1000, 4 * 1000, 16 * 1000, 64 * 1000};
uint8_t alsGainToReg(uint32_t x);
uint8_t alsGainToReg(uint32_t x){
    int i;

    for (i = sizeof(alsGain_conversion)/sizeof(uint32_t)-1; i != 0; i--) {
        if (x >= alsGain_conversion[i]) break;
    }
    return (i << 0);
}
uint8_t alsTimeUsToReg(uint32_t nominalTimeUs, uint32_t *quantizedTimeUs){
    uint8_t count;
    uint32_t t;
    
    if (nominalTimeUs == 0){
        count = 0;
        t = AMS_ALS_TIMEBASE;
    } else {
        count = (nominalTimeUs / AMS_ALS_TIMEBASE);
        t = count * AMS_ALS_TIMEBASE;
        if (t == nominalTimeUs)
            count--;
        else if (t < nominalTimeUs)
            t += AMS_ALS_TIMEBASE;
    }

    if (quantizedTimeUs)
        *quantizedTimeUs = t;

    return (0xff - count);
}
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_PROX_CCB
uint32_t proxGain_conversion[] = { 1000, 2000, 4000, 8000};
uint8_t proxGainToReg(uint32_t x);
uint8_t proxGainToReg(uint32_t x){
    int i;

    for (i = sizeof(proxGain_conversion)/sizeof(uint32_t)-1; i != 0; i--) {
        if (x >= proxGain_conversion[i]) break;
    }
    return (i << 6);
}
uint8_t proxTimeToReg (uint32_t x);
uint8_t proxTimeToReg (uint32_t x){
    uint8_t regValue;
    regValue = (x / AMS_PRX_TIMEBASE) - 1;
    return regValue;
}
uint32_t proxRegToTime (uint8_t x);
uint32_t proxRegToTime (uint8_t x){
    uint32_t time;
    time = (x + 1) * AMS_PRX_TIMEBASE;
    return time;
}
#endif

#ifdef CONFIG_AMS_OPTICAL_SENSOR_PROX_CCB
bool _490x_proxInit(ams_deviceCtx_t * ctx, ams_calibrationData_t * calibrationData);

static bool _490x_proxSetThreshold(ams_deviceCtx_t * ctx, int32_t threshold){
    ams_ccb_proximity_config_t configData;
    configData.sensitivity = (threshold & 0xff);
    ccb_proximitySetConfig(&ctx->ccbProxCtx, &configData);
    return false;
}

static void _490x_handleProxEvent(ams_deviceCtx_t * ctx){
    ams_ccb_proximity_dataSet_t proxData;
    uint16_t pData;
    proxData.statusReg = ctx->shadowStatus1Reg;
    ams_getWord(ctx->portHndl, DEVREG_PDATA_LOW, &pData);
    /* proxData.pData = AMS_NORMALISE_16(pData, 14); */
    proxData.pData = pData;
    ccb_proximityHandle(ctx, &proxData);
}

bool ams_deviceGetPrx(ams_deviceCtx_t * ctx, ams_apiPrx_t * exportData){
    ams_ccb_proximity_result_t outData;
    ccb_proximityGetResult(ctx, &outData);
    exportData->nearBy = outData.nearBy;
    exportData->proximity = outData.proximity;

    return false;
}
#endif

#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS_CCB
static bool _490x_alsSetThreshold(ams_deviceCtx_t * ctx, int32_t threshold){
    ams_ccb_als_config_t configData;
    configData.threshold = threshold;
    ccb_alsSetConfig(ctx, &configData);
    return false;
}

bool _490x_alsInit(ams_deviceCtx_t * ctx, ams_calibrationData_t * calibrationData);

bool ams_deviceGetAls(ams_deviceCtx_t * ctx, ams_apiAls_t * exportData){
    ams_ccb_als_result_t result;
    ccb_alsGetResult(ctx, &result);
    exportData->mLux        = result.mLux;
    exportData->colorTemp   = result.colorTemp;

    exportData->red         = result.red;
    exportData->green       = result.green;
    exportData->blue        = result.blue;
    exportData->ir          = result.ir;
    exportData->wideband    = result.wideband;
    exportData->rawClear    = result.rawClear;
    exportData->rawRed      = result.rawRed;
    exportData->rawGreen    = result.rawGreen;
    exportData->rawBlue     = result.rawBlue;

    return ((exportData->mLux == 0)? false: true);
}

static void _490x_handleAlsEvent(ams_deviceCtx_t * ctx){
    ams_ccb_als_dataSet_t ccbAlsData;
    ccbAlsData.statusReg = ctx->shadowStatus1Reg;
    ccb_alsHandle(ctx, &ccbAlsData);
}

#ifdef CONFIG_AMS_OPTICAL_SENSOR_FLICKER
bool ams_deviceGetFlicker(ams_deviceCtx_t * ctx, ams_apiAlsFlicker_t * exportData){
    ams_ccb_als_result_t result;
    ccb_alsGetResult(ctx, &result);
    exportData->freq100Hz = result.freq100Hz;
    exportData->freq120Hz = result.freq120Hz;
    exportData->mHz = result.mHz;

    return false;
}
#endif
#endif

#ifdef CONFIG_AMS_OPTICAL_SENSOR_GESTURE
#ifndef CONFIG_AMS_OPTICAL_SENSOR_PROX_CCB
/* #error "In order for gesture to work, prox is also needed" */
#endif
bool _490x_gestureRegUpdate(ams_deviceCtx_t * ctx);
bool _490x_gestureRegUpdate(ams_deviceCtx_t * ctx){
#if 0
    if ((ctx->mode & MODE_PROX) == 0){
        /* prox is disabled, setup threshold so it doesn't generate an interrupt */
        ams_setWord(ctx->portHndl,  DEVREG_PIHTL, (0xffff));
        ams_setWord(ctx->portHndl,  DEVREG_PILTL, (0x0000));
    }
#endif

    ams_setByte(ctx->portHndl,  DEVREG_GESTURE_4, 62 ); /* GTIME */
    ams_tmg490x_setField(ctx->portHndl, DEVREG_GESTURE_1, 15, 0x3f); /* pulse */

    ams_setWord(ctx->portHndl, DEVREG_GESTURE_6, AMS_GESTURE_CALIBRATION_OFFSET_TARGET); /* Threshold */
    ams_setWord(ctx->portHndl, DEVREG_GESTURE_8, AMS_GESTURE_CALIBRATION_OFFSET_TARGET); /* Threshold */

    ams_tmg490x_setField(ctx->portHndl, DEVREG_GESTURE_0, GST_EXMSK_ALL, MASK_GST_EXMSK);
    ams_tmg490x_setField(ctx->portHndl, DEVREG_GESTURE_0, 0x03,  MASK_GST_EXPERS);
    ams_tmg490x_setField(ctx->portHndl, DEVREG_GESTURE_1, 0x00,  0xC0);

    ams_tmg490x_setField(ctx->portHndl, DEVREG_GESTURE_2, LOW, 0x30);

    ams_setByte(ctx->portHndl,  DEVREG_GESTURE_5, 0x02); /* GIEN */

    return false;
}

bool _490x_gestureInit(ams_deviceCtx_t * ctx, ams_calibrationData_t * calibrationData);

static void _490x_handleGestureEvent(ams_deviceCtx_t * ctx)
{
    uint8_t numofdset = 1;
    amsGestDataSet_t inputData;
    amsGestResult_t outputData;
    gestureAPIData_t rawData;
    uint8_t gestureCompleted;

    inputData.prox = ctx->ccbProxCtx.pData;
    inputData.timeStamp = ctx->timeStamp;
    inputData.datasetArray = &rawData;

    do {
        /* get dataSet */
        ams_getBuf(ctx->portHndl, DEVREG_GFIFO_N_L,
                (uint8_t *)&rawData.north, 8);

        AMS_PORT_log_4("NSWE = %d, %d, %d, %d,\r\n",
            rawData.north,
            rawData.south,
            rawData.west,
            rawData.east);

        /* process dataSet */
        amsAlg_gesture_processData(&ctx->gestureCtx, &inputData);

        /* poll to see how many dataSets we have left */
        ams_getByte(ctx->portHndl, DEVREG_GESTURE_A, &numofdset);
    } while (numofdset > 0);

#if 0
    ams_setByte(ctx->portHndl, DEVREG_GESTURE_0, (ctx->prxCtx.results.prx_ave >> 7)); /* set to two times the Prox measurement */
    ams_setByte(ctx->portHndl, DEVREG_GESTURE_1, (ctx->prxCtx.results.prx_ave >> 7));
#endif

    ams_getByte(ctx->portHndl, DEVREG_GESTURE_B, &gestureCompleted);
    gestureCompleted &= 0x01;

    if(gestureCompleted == 0){
        amsAlg_gesture_getResult(&ctx->gestureCtx, &outputData);
        ctx->gestureCtx.state = gesture_init;
        switch (outputData.event){
        case northToSouth:
            AMS_PORT_log(">>>>>>>>>>>>>>>>  Gesture Event: northToSouth\r\n");
            break;
        case southToNorth:
            AMS_PORT_log(">>>>>>>>>>>>>>>>  Gesture Event: southToNorth\r\n");
            break;
        case eastToWest:
            AMS_PORT_log(">>>>>>>>>>>>>>>>  Gesture Event: eastToWest\r\n");
            break;
        case westToEast:
            AMS_PORT_log(">>>>>>>>>>>>>>>>  Gesture Event: westToEast\r\n");
            break;
        case northWestToSouthEast:
            AMS_PORT_log(">>>>>>>>>>>>>>>>  Gesture Event: northWestToSouthEast\r\n");
            break;
        case northEastToSouthWest:
            AMS_PORT_log(">>>>>>>>>>>>>>>>  Gesture Event: northEastToSouthWest\r\n");
            break;
        case southWestToNorthEast:
            AMS_PORT_log(">>>>>>>>>>>>>>>>  Gesture Event: southWestToNorthEast\r\n");
            break;
        case southEastToNorthWest:
            AMS_PORT_log(">>>>>>>>>>>>>>>>  Gesture Event: southEastToNorthWest\r\n");
            break;
        case pushedAndReleased:
            AMS_PORT_log(">>>>>>>>>>>>>>>>  Gesture Event: pushedAndReleased\r\n");
            break;
        case pushedAndHold:
            AMS_PORT_log(">>>>>>>>>>>>>>>>  Gesture Event: pushedAndHold\r\n");
            break;
        case unknown_gestureEvent:
            break;
        }
    }
}
bool ams_deviceGetGesture(ams_deviceCtx_t * ctx, amsGestResult_t * outData){
    amsAlg_gesture_getResult(&ctx->gestureCtx, outData);
    return false;
}
#endif

bool ams_deviceSetConfig(ams_deviceCtx_t * ctx, ams_configureFeature_t feature, deviceConfigOptions_t option, uint32_t data){
    int ret = 0;
    ams_mode_t opmode = MODE_OFF;

#ifdef CONFIG_AMS_OPTICAL_SENSOR_PROX_CCB
    if (feature == AMS_CONFIG_PROX)
        opmode = MODE_PROX;
    else if (feature == AMS_CONFIG_PROX_ALT_REPORT)
        opmode = MODE_PROX_ALT_REPORT;
    if ((feature == AMS_CONFIG_PROX) || (feature == AMS_CONFIG_PROX_ALT_REPORT)){
        AMS_PORT_log_1("ams_configureFeature_t  AMS_CONFIG_PROX (0x%x)\n", feature);
        switch (option)
        {
            case AMS_CONFIG_ENABLE: /* power on */
                AMS_PORT_log_1("deviceConfigOptions_t   AMS_CONFIG_ENABLE(%u)\n", data);
                AMS_PORT_log_1("current mode            %d\n", ctx->mode);
                if (data == 0) {
                    if (ctx->mode == opmode){
                        /* if no other active features, turn off device */
                        ctx->shadowEnableReg = 0;
                        ctx->mode = MODE_OFF;
                        ccb_proximityInit(ctx, &ctx->ccbProxCtx.initData);
                    } else {
                        ctx->mode &= ~opmode;
                        if ((ctx->mode & MODE_PROX_ALL) == 0){
                            if (ctx->mode & MODE_GESTURE){
                                /* gesture is still enabled. So, only disable Prox Interrupt*/
                                ctx->shadowEnableReg &= (~(PIEN));
                            } else {
                                ctx->shadowEnableReg &= (~(PEN | PIEN));
                            }
                        }
                    }
                } else {
                    if ((ctx->mode & (MODE_PROX_ALL | MODE_GESTURE)) == 0){
                        ccb_proximityInit(ctx, &ctx->ccbProxCtx.initData);
                    }
                    ctx->shadowEnableReg |= (PEN | PIEN | PON);
                    ctx->mode |= opmode;
                }
                break;
            case AMS_CONFIG_THRESHOLD: /* set threshold */
                AMS_PORT_log(  "deviceConfigOptions_t   AMS_CONFIG_THRESHOLD\n");
                ret |= _490x_proxSetThreshold(ctx, data);
                break;
            default:
                break;
        }
    }
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS_CCB
    if (feature == AMS_CONFIG_ALS_LUX){
        AMS_PORT_log("ams_configureFeature_t  AMS_CONFIG_ALS_LUX\n");
        switch (option)
        {
            case AMS_CONFIG_ENABLE: /* ON / OFF */
                AMS_PORT_log_1("deviceConfigOptions_t   AMS_CONFIG_ENABLE(%u)\n", data);
                AMS_PORT_log_1("current mode            %d\n", ctx->mode);
                if (data == 0) {
                    if (ctx->mode == MODE_ALS_LUX) {
                        /* if no other active features, turn off device */
                        ctx->shadowEnableReg = 0;
                        ctx->mode = MODE_OFF;
                    } else {
                        if ((ctx->mode & MODE_ALS_ALL) == MODE_ALS_LUX) {
                            ctx->shadowEnableReg &= (~ALS_ENABLE_ALL);
                        }
                        ctx->mode &= ~(MODE_ALS_LUX);
                    }
                } else {
                    if ((ctx->mode & MODE_ALS_ALL) == 0) {
                        ccb_alsInit(ctx, &ctx->ccbAlsCtx.initData);
                        ctx->shadowEnableReg |= (ALS_ENABLE_ALL | PON);
                    } else {
                        /* force interrupt */
                        ams_setWord(ctx->portHndl, DEVREG_AIHTHL, 0x00);
                    }
                    ctx->mode |= MODE_ALS_LUX;
                }
                break;
            case AMS_CONFIG_THRESHOLD: /* set threshold */
                AMS_PORT_log(  "deviceConfigOptions_t   AMS_CONFIG_THRESHOLD\n");
                AMS_PORT_log_1("data                    %d\n", data);
                ret |= _490x_alsSetThreshold(ctx, data);
                break;
            default:
                break;
        }
    }
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS_RGB
    if (feature == AMS_CONFIG_ALS_RGB)
        opmode = MODE_ALS_RGB;
    else if (feature == AMS_CONFIG_ALS_RGB_ALT_REPORT)
        opmode = MODE_ALS_RGB_ALT_REPORT;
    if ((feature == AMS_CONFIG_ALS_RGB) || (feature == AMS_CONFIG_ALS_RGB_ALT_REPORT)){
        AMS_PORT_log_1("ams_configureFeature_t  AMS_CONFIG_ALS_RGB (0x%x)\n", feature);
        switch (option)
        {
            case AMS_CONFIG_ENABLE: /* ON / OFF */
                AMS_PORT_log_1("deviceConfigOptions_t   AMS_CONFIG_ENABLE(%u)\n", data);
                AMS_PORT_log_1("current mode            %d\n", ctx->mode);
                if (data == 0) {
                    if (ctx->mode == opmode){
                        /* if no other active features, turn off device */
                        ctx->shadowEnableReg = 0;
                        ctx->mode = MODE_OFF;
                    } else {
                        ctx->mode &= ~opmode;
                        if ((ctx->mode & MODE_ALS_ALL) == 0) {
                            ctx->shadowEnableReg &= (~ALS_ENABLE_ALL);
                        }
                    }
                } else {
                    if ((ctx->mode & MODE_ALS_ALL) == 0) {
                        ccb_alsInit(ctx, &ctx->ccbAlsCtx.initData);
                        ctx->shadowEnableReg |= (ALS_ENABLE_ALL | PON);
                    } else {
                        /* force interrupt */
                        ams_setWord(ctx->portHndl, DEVREG_AIHTHL, 0x00);
                    }
                    ctx->mode |= opmode;
                }
                break;
            case AMS_CONFIG_THRESHOLD: /* set threshold */
                AMS_PORT_log(  "deviceConfigOptions_t   AMS_CONFIG_THRESHOLD\n");
                AMS_PORT_log_1("data                    %d\n", data);
                ret |= _490x_alsSetThreshold(ctx, data);
                break;
            default:
                break;
        }
    }
    if (feature == AMS_CONFIG_ALS_CT){
        AMS_PORT_log("ams_configureFeature_t  AMS_CONFIG_ALS_CT\n");
        switch (option)
        {
            case AMS_CONFIG_ENABLE: /* ON / OFF */
                AMS_PORT_log_1("deviceConfigOptions_t   AMS_CONFIG_ENABLE(%u)\n", data);
                AMS_PORT_log_1("current mode            %d\n", ctx->mode);
                if (data == 0) {
                    if (ctx->mode == MODE_ALS_CT) {
                        /* if no other active features, turn off device */
                        ctx->shadowEnableReg = 0;
                        ctx->mode = MODE_OFF;
                    } else {
                        if ((ctx->mode & MODE_ALS_ALL) == MODE_ALS_CT) {
                            ctx->shadowEnableReg &= (~ALS_ENABLE_ALL);
                        }
                        ctx->mode &= ~(MODE_ALS_CT);
                    }
                } else {
                    if ((ctx->mode & MODE_ALS_ALL) == 0) {
                        ccb_alsInit(ctx, &ctx->ccbAlsCtx.initData);
                        ctx->shadowEnableReg |= (ALS_ENABLE_ALL | PON);
                    } else {
                        /* force interrupt */
                        ams_setWord(ctx->portHndl, DEVREG_AIHTHL, 0x00);
                    }
                    ctx->mode |= MODE_ALS_CT;
                }
                break;
            case AMS_CONFIG_THRESHOLD: /* set threshold */
                AMS_PORT_log(  "deviceConfigOptions_t   AMS_CONFIG_THRESHOLD\n");
                AMS_PORT_log_1("data                    %d\n", data);
                ret |= _490x_alsSetThreshold(ctx, data);
                break;
            default:
                break;
        }
    }
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS_WIDEBAND
    if (feature == AMS_CONFIG_ALS_WIDEBAND){
        AMS_PORT_log("ams_configureFeature_t  AMS_CONFIG_ALS_WIDEBAND\n");
        switch (option)
        {
            case AMS_CONFIG_ENABLE: /* ON / OFF */
                AMS_PORT_log_1("deviceConfigOptions_t   AMS_CONFIG_ENABLE(%u)\n", data);
                AMS_PORT_log_1("current mode            %d\n", ctx->mode);
                if (data == 0) {
                    if (ctx->mode == MODE_ALS_WIDEBAND) {
                        /* if no other active features, turn off device */
                        ctx->shadowEnableReg = 0;
                        ctx->mode = MODE_OFF;
                    } else {
                        if ((ctx->mode & MODE_ALS_ALL) == MODE_ALS_WIDEBAND) {
                            ctx->shadowEnableReg &= (~ALS_ENABLE_ALL);
                        }
                        ctx->mode &= ~(MODE_ALS_WIDEBAND);
                    }
                } else {
                    if ((ctx->mode & MODE_ALS_ALL) == 0) {
                        ccb_alsInit(ctx, &ctx->ccbAlsCtx.initData);
                        ctx->shadowEnableReg |= (ALS_ENABLE_ALL | PON);
                    }
                    ctx->mode |= MODE_ALS_WIDEBAND;
                }
                break;
            case AMS_CONFIG_THRESHOLD: /* set threshold */
                AMS_PORT_log(  "deviceConfigOptions_t   AMS_CONFIG_THRESHOLD\n");
                AMS_PORT_log_1("data                    %d\n", data);
                ret |= _490x_alsSetThreshold(ctx, data);
                break;
            default:
                break;
        }
    }
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_GESTURE
    if (feature == AMS_CONFIG_GESTURE){
        AMS_PORT_log("ams_configureFeature_t  AMS_CONFIG_GESTURE\n");
        switch (option)
        {
            case AMS_CONFIG_ENABLE: /* ON / OFF */
                AMS_PORT_log_1("deviceConfigOptions_t   AMS_CONFIG_ENABLE(%u)\n", data);
                AMS_PORT_log_1("current mode            %d\n", ctx->mode);
                if (data == 0) {
                    ams_setByte(ctx->portHndl, DEVREG_GESTURE_5, 0);
                    if (ctx->mode == MODE_GESTURE) {
                        /* if no other active features, turn off device */
                        ctx->shadowEnableReg = 0;
                        ctx->mode = MODE_OFF;
                    } else {
                        ctx->mode &= ~MODE_GESTURE;
                        if (ctx->mode & MODE_PROX){
                            /* Prox is still active, only deactivate gesture*/
                            ctx->shadowEnableReg &= (~(GEN));
                        } else {
                            ctx->shadowEnableReg &= (~(GEN | PEN | PIEN));
                        }
                    }
                } else {
                    ret |= _490x_gestureRegUpdate(ctx);
                    ctx->shadowEnableReg |= (GEN | PEN | PON);
                    ctx->mode |= MODE_GESTURE;
                }
                break;
            case AMS_CONFIG_THRESHOLD: /* set threshold */
                AMS_PORT_log(  "deviceConfigOptions_t   AMS_CONFIG_THRESHOLD\n");
                break;
            default:
                break;
        }
    }
#endif
    ams_setByte(ctx->portHndl, DEVREG_ENABLE, ctx->shadowEnableReg);

    return 0;
}

bool ams_deviceEventHandler(ams_deviceCtx_t * ctx){
    int ret = 0;

    ams_getByte(ctx->portHndl, DEVREG_STATUS, &ctx->shadowStatus1Reg);
loop:
    AMS_PORT_get_timestamp_usec(&ctx->timeStamp);
    ams_getByte(ctx->portHndl, DEVREG_STATUS2, &ctx->shadowStatus2Reg);

    AMS_PORT_log_2("ams_deviceEventHandler loop:  DCB mode=0x%02x, STATUS=0x%02x", ctx->mode, ctx->shadowStatus1Reg);

#ifdef CONFIG_AMS_OPTICAL_SENSOR_GESTURE
    if (ctx->shadowStatus1Reg & MASK_GINT){
        if (ctx->mode & MODE_GESTURE){
            AMS_PORT_log_1("gesture mode=%u; call _490x_handleGestureEvent\n", ctx->gestureCtx.mode);
            _490x_handleGestureEvent(ctx);
            ctx->updateAvailable |= (1 << AMS_GESTURE_SENSOR);
        }
        ams_tmg490x_setField(ctx->portHndl, DEVREG_INT_CLEAR, HIGH, (MASK_INTCLR_GINT));
    }
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_PROX_CCB
    if (ctx->shadowStatus1Reg & (PGSAT | PINT | CINT)){
        if (ctx->mode & MODE_PROX_ALL){
            AMS_PORT_log("_490x_handleProxEvent\n");
            _490x_handleProxEvent(ctx);
        }
        ams_tmg490x_setField(ctx->portHndl, DEVREG_INT_CLEAR, HIGH, (MASK_INTCLR_PINT | MASK_INTCLR_PGSAT | MASK_INTCLR_CINT));
    }
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS_CCB
    if (ctx->shadowStatus1Reg & (ALS_INT_ALL)){
        if (ctx->mode & MODE_ALS_ALL){
            AMS_PORT_log("_490x_handleAlsEvent\n");
            _490x_handleAlsEvent(ctx);
            if (ctx->ccbAlsCtx.initData.calibrate == false){

            }
        }
        ams_tmg490x_setField(ctx->portHndl, DEVREG_INT_CLEAR, HIGH, (MASK_ALS_INTCLR_ALL));
    }
#endif
    ams_getByte(ctx->portHndl, DEVREG_STATUS, &ctx->shadowStatus1Reg);
    if ((ctx->shadowStatus1Reg & ~MASK_AGDATA)!= 0)
        goto loop;

    ams_setByte(ctx->portHndl, DEVREG_ENABLE, ctx->shadowEnableReg);

    return ret;
}

#ifdef CONFIG_AMS_OPTICAL_SENSOR_ALS_CCB
bool ams_deviceCalibrateLux(ams_deviceCtx_t * ctx, ams_calibrationData_t * calibrationData){
    ams_ccb_als_info_t infoData;

    if (calibrationData){
        ctx->ccbAlsCtx.initData.calibrationData.calibrationFactor = calibrationData->alsCalibrationFactor;
    } else {
        ccb_alsInfo(&infoData);
        ctx->ccbAlsCtx.initData.calibrationData.calibrationFactor = infoData.defaultCalibrationData.calibrationFactor;
    }
    ctx->ccbAlsCtx.initData.configData.gain = 64000;
    ctx->ccbAlsCtx.initData.configData.uSecTime = 100000;
    ctx->ccbAlsCtx.initData.calibrate = true;
    ccb_alsInit(ctx, &ctx->ccbAlsCtx.initData);

    ctx->shadowEnableReg |= (ALS_ENABLE_ALL | PON);
    ctx->mode |= MODE_ALS_LUX;
    ams_setByte(ctx->portHndl, DEVREG_ENABLE, ctx->shadowEnableReg);

    return true;
}
#endif
#ifdef CONFIG_AMS_OPTICAL_SENSOR_PROX_CCB
bool ams_deviceCalibrateProx(ams_deviceCtx_t * ctx, ams_calibrationData_t * calibrationData){
    ams_ccb_proximity_info_t infoData;

    if (calibrationData){
        ctx->ccbProxCtx.initData.nearByHardThreshold = calibrationData->proxHardThreshold;
    } else {
        ccb_proximityInfo(&infoData);
        ctx->ccbProxCtx.initData.nearByHardThreshold = infoData.defaultCalibrationData.hardThreshold;
    }
    ctx->ccbProxCtx.initData.calibrate = true;
    ccb_proximityInit(ctx, &ctx->ccbProxCtx.initData);

    ctx->shadowEnableReg |= (PEN | PIEN | PON);
    ctx->mode |= MODE_PROX;
    ams_setByte(ctx->portHndl, DEVREG_ENABLE, ctx->shadowEnableReg);

    return true;
}
#endif

bool ams_getMode(ams_deviceCtx_t * ctx, ams_mode_t * mode) {
    *mode = ctx->mode;
    return false;
}

uint32_t ams_getResult(ams_deviceCtx_t * ctx) {
    uint32_t returnValue = ctx->updateAvailable;
    ctx->updateAvailable = 0;
    return returnValue;
}
