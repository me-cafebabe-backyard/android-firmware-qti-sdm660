#ifndef __AFE_HW_AF_H_
#define __AFE_HW_AF_H_

/*==============================================================================
  @brief This file contains Hardware Adaptive filter APIs

  Copyright (c) 2017 QUALCOMM Technologies, Inc.  All Rights Reserved.
  QUALCOMM Technologies, Inc Proprietary.  Export of this technology or
  software is regulated by the U.S. Government, Diversion contrary to U.S.
  law prohibited.
==============================================================================*/

/*==============================================================================
  Edit History

  $Header: //components/rel/avs.adsp/2.8/afe/drivers/hw/adaptive_filter/inc/hw_af.h#2 $

  when       who     what, where, why
  --------   ---     -------------------------------------------------------
  09/19/17   unni     Created file
==============================================================================*/

#include "mmdefs.h"
#include "adsp_error_codes.h"

/*==============================================================================
   Type Definitions
==============================================================================*/

/* Speaker/Echo Reference Config bit position in param 'hw_af_filter_t' */
#define HW_AF_ECHO_REF_BIT_POS (8)

/* Filter types supported */
typedef enum 
{
  /* Supported Filtering Modes */
  HW_FILTER_ADAPTIVE_FFT_SUBBAND = 1,     
  /* FFT based sub-band domain Adaptive Filter with 1 complex sample per 
     subband. 
     Inputs, Outputs & Coeffs must be in 64-bit Complex fixed-point 
     (HW_TYPE_COMPLEX_FIX_64_BIT). Supports Foreground (FG) & background (BG) 
     Filters, Adaptation is performed on BG. BG filter coefficients are 
     conditionally downloaded to FG outside HW_AF block. */

  HW_FILTER_ADAPTIVE_FFT_SUBBAND_FG = 2,    
  /* FFT based sub-band domain Adaptive Filter with 1 complex sample per 
     subband. 
     Inputs, Outputs & Coeffs must be in 64-bit Complex fixed-point 
     (HW_TYPE_COMPLEX_FIX_64_BIT). Supports Foreground (FG) Filter only, 
     Adaptation is performed on FG. */

  HW_FILTER_ADAPTIVE_TIME = 4,     
  /* Time-domain Adaptive Filter - FG & BG. 
     Inputs & Outputs must be in 32/16-bit and Coeffs in 32-bit real 
     fixed-point */

  HW_FILTER_ADAPTIVE_TIME_FG = 8,     
  /* Adaptive Filter - FG  
     Inputs & Outputs must be in 32/16-bit and Coeffs in 32-bit real 
     fixed-point */

  HW_FILTER_FIR = 16,
  /* FIR Filter
     Inputs & Outputs must be in 32/16-bit and Coeffs in 32-bit real 
     fixed-point */

  HW_FILTER_ADAPTIVE_GROUP = 
     (  HW_FILTER_ADAPTIVE_FFT_SUBBAND 
      | HW_FILTER_ADAPTIVE_FFT_SUBBAND_FG
      | HW_FILTER_ADAPTIVE_TIME
      | HW_FILTER_ADAPTIVE_TIME_FG ),

  HW_FILTER_ADAPTIVE_FG_BG_GROUP = 
     (  HW_FILTER_ADAPTIVE_FFT_SUBBAND | HW_FILTER_ADAPTIVE_TIME ),

  HW_FILTER_ADAPTIVE_FFT_SB_GROUP = 
     ( HW_FILTER_ADAPTIVE_FFT_SUBBAND | HW_FILTER_ADAPTIVE_FFT_SUBBAND_FG ),

  HW_FILTER_ADAPTIVE_TIME_GROUP = 
     ( HW_FILTER_ADAPTIVE_TIME | HW_FILTER_ADAPTIVE_TIME_FG ),

  HW_FILTER_FIR_GROUP = ( HW_FILTER_FIR ),

  /** Adaptive Filter Speaker/Echo Reference Config Modes, numEchoRefPerMic 
      is set based on this **/   
   HW_AF_SPKR_MONO = (1<<HW_AF_ECHO_REF_BIT_POS),     
   /* 1 SPKR reference common to all Mics */

   HW_AF_SPKR_STEREO = (2<<HW_AF_ECHO_REF_BIT_POS),     
   /* Stereo Adaptive Filter, 2 SPKR references per Mic & common to all Mics */

   HW_AF_SPKR_MULTI_CHAN_FF = (4<<HW_AF_ECHO_REF_BIT_POS),      
   /* 1 SPKR reference per Mic uniquely generated from 2 or more Playback 
      Channels using Fixed filtering. (#SPKR references = #Mics) */
}hw_af_filter_e;

/* Filter coefs & input samples type */
typedef enum
{
   HW_TYPE_REAL_FIX_16_BIT = 1,    
   /* Inputs & Outputs in 16-bit real fixed-point */

   HW_TYPE_REAL_FIX_32_BIT = 2,    
   /* Inputs, Outputs in 32-bit real fixed-point */

   HW_TYPE_COMPLEX_FIX_64_BIT = 3     
   /* Inputs, Outputs in 64-bit Complex fixed-point, 
      Real part in lower 32-bits & imaginary part in upper 32-bits */

}hw_af_data_e;

/* Adaptive filter config specific to one mic & speaker pair (echo path) */
typedef struct
{
  uint16_t filterLen;           
  /* filter length for low bands */

  uint16_t filterLenHB;         
  /* filter length for high bands */

  int8_t filtOutDownShift;    
  /* Temporary Down shift applied on Mic & Echo during intermediate computations
     to avoid overflow. Must be same for stereo filters of a mic */

  int8_t filtWgtQfmt;         
  /* No. of fractional bits in filter coef 32-bit fixed-point representation 
     'Q(filtWgtQfmt)'. Must be same for low & high bands and stereo filters of 
     a mic */

  uint16_t echoRefBufOffset;    
  /* filter offset in echo reference buffer */

  uint16_t echoRefBufOffsetHB;  
  /* filter offset for HB in echo reference buffer */

  uint8_t refEnergyRshift;     
  /* Right shift for adaptation normalization factor, to avoid overflow. */

  uint8_t refEnergyRshiftHB;   
  /* Right shift for adaptation normalization factor, to avoid overflow. */

  int32_t nlmsNormDelta;       
  /* Small constant in the denominator of adaptation factor to avoid divide by 
     '0', this is in Q31 format. */

}hw_af_channel_config_t;

/* Adaptive filter configuration object.

   Struct size calculation formula:
       sizeof(hw_af_conf_t) + 
       (sizeof(hw_af_channel_config_t)*numMics*numEchoRef)
 */
typedef struct
{
  uint16_t filterType;             
  /* Type of filter & Echo Reference Config. 
     supported values from 'enum hw_af_filter_e' */

  uint16_t inputType;              
  /* Type & bitwidth for inputs, filter weights & outputs. 
     supported values from 'enum hw_af_data_e' */

  uint16_t numMics;                
  /* Number of Mics */

  uint16_t numSamples;             
  /* Number of sub-frames (input blocks) for FFT sub-band domain filter 
     (each sub-band contain one bin) (or) Block size for time-domain filter */

  uint16_t numSubBands;            
  /* Number of sub-bands */

  uint16_t primaryChanIdx;         
  /* Primary Mic channel identifier */

  uint16_t nSBandsNonPrimMic;      
  /* Number of sub-bands processed for non-primary Mics */

  uint16_t nSBandsLargeFLen;       
  /* Number of sub-bands processed with higher-order filters (low Bands) */

  int16_t inputQfmt;              
  /* Mic input & output fixed-point Q-format 'Q(inputQfmt)' */

  uint16_t echoRefSize;            
  /* Combined size (in samples) of 1 or more echo references for filtering 1 SB 
     of all Mics (low bands) */

  uint16_t echoRefSizeHB;          
  /* Combined size (in samples) of 1 or more echo references for filtering 1 SB 
     of all Mics (high bands) */

  hw_af_channel_config_t* pChanCfg;               
  /* Pointer to buffer of N filter configurations each defined by 
     'hw_af_channel_config_t' & N = numMics*numEchoRefPerMic.

     The following order will need to be maintained:
     hw_af_channel_config_t for {mic[0], Speaker[0]},
     ..
     hw_af_channel_config_t for {mic[0], Speaker[m]},
     hw_af_channel_config_t for {mic[1], Speaker[0]},
     ..
     hw_af_channel_config_t for {mic[n], Speaker[m]}.*/
 
  uint32_t pChanCfg_buf_size;      
  /* Size of pChanCfg buffer in bytes */

} hw_af_config_t;

/* Filter Adaptation Flags */
typedef struct
{
  uint8_t mode;
  /* Filter weight adaptation mode for each sub-band, Mic & sub-frame.
     Supported modes: 
      0 - Adaptation off (Echo Ref VAD = 0), 
      1 - Adapt FG filter, 
      2 - Adapt BG filter (enum HW_FilterAdaptationMode)
     mode word packs the adaptation mode for stereo echo references of a mic 
     channel in 2 bits each: |Mode_e_ref_1||Mode_e_ref_0| */

  int8_t scaling;
  /* Adaptation scaling in amount of shift. Includes NLMS Step size in shift &
     shifts (filtWgtQfmt-inputQfmt-31) to convert to filter adaptation term 
     (Q(31+inputQfmt)) to filter coef. Q-format (Q(filtWgtQfmt)). 
     For stereo echo references, scaling is same for both. */
} hw_af_adaptation_flag_t;

/* Instantaneous second moments data structure */
typedef struct
{
   int32_t lRefEn;    
   /* far-end reference signal energy for the current subframe */

   int32_t lEccEnBG;    
   /* echo cleaned signal energy for the current subframe BG */

   int32_t lMecCov;   
   /* covariance of microphone signal and echo cleaned signal for the current 
      subframe */

   int32_t lEccEn;    
   /* echo cleaned signal energy for the current subframe */

   int32_t lMicEn;    
   /* microphone signal energy for the current subframe */

} hw_af_inst_second_moments_t;

/* Adaptive filter shared data buffer structure

   All the buffer starting addresses must be aligned to 128-byte memory 
   boundary.

   FilterIn buffer shall contain speaker references for all channels & 
   sub-bands in a contiguous buffer:
   {speaker_ref[SUB_BANDS][CHANNELS][NUM_TAPS-1+NUM_SAMPLES]}

   FilterCoef & FilterCoefBG buffers shall maintain the following format & 
   order:
     - [coefs(0, 0, 0), coefs(0, 0, 1) ....
        coefs(0, 1, 0), coefs(0, 1, 1) .... 
        coefs(numSubBands, numMics, numEchoRef)]
     - coefs = [coef(tap-1), coef(tap-2) ..... coef(0)]

   Mic & output error buffers shall maintain the following format & order:
     - [mic(0, 0, 0), mic(0, 0, 1) ....
        mic(0, 1, 0), mic(0, 1, 1) .... 
        mic(numSubBands, numMics, numSamples)]

   FilterOut & FilterOutBG buffers shall maintain the following format & order:
     - [echo(0, 0, 0), echo(0, 0, 1) ....
        echo(0, 1, 0), echo(0, 1, 1) .... 
        echo(numSubBands, numMics, numSamples)]

   AdaptFlags buffer shall maintain the following format & order:
     - [hw_af_adaptation_flag_t(0, 0, 0), hw_af_adaptation_flag_t(0, 0, 1) ....
        hw_af_adaptation_flag_t(0, 1, 0), hw_af_adaptation_flag_t(0, 1, 1) .... 
        hw_af_adaptation_flag_t(numSubBands, numMics, numSamples)]

   ISM buffer shall maintain the following format & order:
     - [hw_af_inst_second_moments_t(0, 0), 
        hw_af_inst_second_moments_t(0, 1) .... 
        hw_af_inst_second_moments_t(numSubBands, numMics)]

   Struct size calculation formula:
       sizeof(hw_af_buffer_t) + 
       FilterCoef_size*numMics*numEchoRef*numSubBands*2 + 
       Mic_sample_size*numMics*numSubBands*4 +
       sizeof(hw_af_adaptation_flag_t)*numSubBands*numMics*numSamples + 
       sizeof(hw_af_inst_second_moments_t)*numSubBands*numMics
 */
typedef struct
{
  /************************ FG filter buffers *********************************/
  void* pFilterIn;            
  /* [in] Pointer to echo references for each sub-band (including history 
     samples with oldest sample first). */

  uint32_t pFilterIn_size;        
  /* Size of pFilterIn buffer in bytes */

  void* pFilterCoef;        
  /* [in/out] Pointer to FG Filter Coefficients for all mics & sub-bands */

  uint32_t pFilterCoef_size;      
  /* Size of pFilterCoef buffer in bytes (valid data) */

  void* pMicInErrOut;       
  /* [in/out] Pointer to mic input / FG error output for all mics & subbands. */

  uint32_t pMicInErrOut_size;      
  /* Size of pMicInErrOut buffer in bytes */

  void* pFilterOut;        
  /* [out] Pointer to FG Echo Estimate for all mics & sub-bands */

  uint32_t pFilterOut_size;      
  /* Size of pFilterOut buffer in bytes */


  /************************ BG filter buffers *********************************/
  void* pFilterCoefBG;    
  /* [in/out] Pointer to BG Filter Coefficients for all mics & sub-bands */

  uint32_t pFilterCoefBG_size;      
  /* Size of pFilterCoefBG buffer in bytes */

  void* pErrorBG;           
  /* [out] Pointer to BG error for all mics & sub-bands */

  uint32_t pErrorBG_size;        
  /* Size of pErrorBG buffer in bytes */

  void* pFilterOutBG;        
  /* [out] Pointer to BG Echo Estimate for all mics & sub-bands */

  uint32_t pFilterOutBG_size;      
  /* Size of pFilterOutBG buffer in bytes */


  /*************************** Common buffers *********************************/  
  hw_af_adaptation_flag_t* pAdaptFlags; 
  /* [in] Filter Adaptation Flags. */

  uint32_t pAdaptFlags_size;      
  /* Size of pAdaptFlags buffer in bytes (valid data) */

  hw_af_inst_second_moments_t* pISM;      
  /* [out] Pointer to Signal Instantaneous Energy buffer for all mics & 
     sub-bands */

  uint32_t pISM_size;          
  /* Size of pISM buffer in bytes (valid data) */

} hw_af_buffer_t;

typedef enum
{
  NO_PREFERENCE_CLIENT = 0,
  LOW_LATENCY_CLIENT,
  HIGH_LATENCY_CLIENT  
} hw_af_client_type_t;

/* Client info structure */
typedef struct 
{
  hw_af_client_type_t client_type;
  /* Type of client */

  uint32_t bw_scaling_factor_q10;
  /* Extra bandwidth to be added to the calculated bandwidth (in q10 format). 
     Effective bandwidth = calculated bandwidth * (1 + bw_scaling_factor_q10) */
  
  uint32_t block_size_in_us;
  /* Time alloted for a HW AF process routine in micro-second  */
  
} hw_af_client_info_t;

/*
  Callback function signature
*/
typedef void (*hw_af_callback_func_t)(void* arg_ptr);

/* Hardware adaptive filter instance */
typedef struct {

  bool_t in_use;
  /* whether instance is in use or not */

  uint32_t clk_req_mhz;
  /* clock required in mhz for this instance */

  uint32_t data_bandwidth;
  /* Bandwidth used by this instance */

  hw_af_config_t* config_ptr;
  /* pointer to the configuration to be used */

  hw_af_client_info_t client_info;
  /* client info */  
  
}hw_af_t;

/*==============================================================================
   Function declarations
==============================================================================*/

#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus*/

/* 
   Initialize hardware adaptive filter driver

   return: ADSP_EOK(0) on success else failure error code
 */
ADSPResult hw_af_init(void);

/* 
   Initialize hardware adaptive filter driver

   return: ADSP_EOK(0) on success else failure error code
 */
ADSPResult hw_af_deinit(void);

/* 
   Open an instance of hardware adaptive filter

   param[in] config_ptr: Filter configuration
   param[in] client_info_ptr: Information about the client

   return: instance of hardware adaptive filter
 */
hw_af_t* hw_af_open(
  hw_af_config_t* config_ptr, 
  hw_af_client_info_t* client_info_ptr);

/* 
   Close the instance of hardwar adaptive filter

   param[in] hw_af_ptr: instance of hardware adaptive filter

   return: nothing
 */
void hw_af_close(
  hw_af_t* hw_af_ptr);

/*
   Process a job using hardware adaptive filter

   param[in] hw_af_ptr: instance of hardware adaptive filter
   param[in/out] hw_af_buffer_ptr: input/output buffers used for processing
   param[in] callback_func: Callback routine in case of async processing, else 
             use NULL for sync processing
   param[in] callback_arg_ptr: Argument for above call back routine

   return: ADSP_EOK(0) on success else failure error code
 */
ADSPResult hw_af_process(
  hw_af_t* hw_af_ptr,
  hw_af_buffer_t* hw_af_buffer_ptr,
  hw_af_callback_func_t callback_func,
  void* callback_arg_ptr);

/*
   Fetch output buffer (required while using async process).
   After client is notifed that a async process has completed, client ought to
   call this function before accessing the output data.

   param[in] hw_af_ptr: instance of hardware adaptive filter
   param[in/out] hw_af_buffer_ptr: input/output buffers used for processing
   
   return: ADSP_EOK(0) on success else failure error code
 */
ADSPResult hw_af_fetch(
  hw_af_t* hw_af_ptr,
  hw_af_buffer_t* hw_af_buffer_ptr);

#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /* __AFE_HW_AF_H_ */

