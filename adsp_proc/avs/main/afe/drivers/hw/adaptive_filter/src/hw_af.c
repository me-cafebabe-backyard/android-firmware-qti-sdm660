/*==============================================================================
  @brief This file contains hardware adaptive filter driver implementation

  Copyright (c) 2017-2018 QUALCOMM Technologies, Inc.  All Rights Reserved.
  QUALCOMM Technologies, Inc Proprietary.  Export of this technology or
  software is regulated by the U.S. Government, Diversion contrary to U.S.
  law prohibited.
==============================================================================*/

/*==============================================================================
  Edit History

  $Header: //components/rel/avs.adsp/2.8/afe/drivers/hw/adaptive_filter/src/hw_af.c#3 $

  when       who     what, where, why
  --------   ---     -------------------------------------------------------
  09/19/17   unni     Created file
==============================================================================*/

#include "hw_af.h"
#include "hw_af_hal_common.h"
#include "qurt_elite.h"
#include "hwd_devcfg.h"

/*==============================================================================
   Local Defines
==============================================================================*/
#define HW_AF_MAX_NUM_CLIENT 8
#define HW_AF_MAX_NUM_JOB 8
#define HW_AF_IST_STACK_SIZE_BYTES 1024
#define HW_AF_SYNC_JOB_WAIT_MASK 0x1
#define HW_AF_JOB_QUEUE_CH_ANY_MASK 0x0
#define HW_AF_ALLOC_ALIGN 128
#ifndef MAX
  /** Macro for getting the maximum of two numbers. */
   #define  MAX( x, y ) ( ((x) > (y)) ? (x) : (y) )
#endif
#ifndef MIN
  /** Macro for getting the maximum of two numbers. */
   #define  MIN( x, y ) ( ((x) < (y)) ? (x) : (y) )
#endif

typedef struct 
{
  hw_af_config_t* config_ptr;
  /* pointer to the configuration to be used */

  hw_af_buffer_t* buffer_ptr; 
  /* pointer to the buffer to be processed */

  hw_af_callback_func_t callback_func;
  /* callback function for async job completion */

  void* callback_arg_ptr;
  /* callback argument for async job completion */

  hw_af_t* client_ptr;
  /* client owning the job */  
}hw_af_job_t;

typedef struct 
{
  qurt_elite_mutex_t drv_mutex;
  /* Mutex protecting update of global variables */

  hw_af_t clients[HW_AF_MAX_NUM_CLIENT];
  /* Resources for clients */

  uint32_t num_clients_in_use;
  /* Number of clients in use */

  qurt_elite_queue_t* job_pending_queue_ptr;
  /* queue for pending async jobs */

  qurt_elite_queue_t* job_free_queue_ptr;
  /* queue for pending async jobs */

  qurt_elite_channel_t job_queue_channel;
  /* channel to statisfy qurt elite queue usage */

  hw_af_job_t jobs[HW_AF_MAX_NUM_JOB];
  /* static pool of async jobs */

  qurt_elite_mutex_t job_mutex;
  /* Mutex protecting job state */

  hw_af_job_t* job_running_ptr;
  /* Current job */

  qurt_elite_interrupt_ist_t ist;
  /* interrupt service thread */

  hw_adaptive_filter_prop_t property;
  /* Hardware property */

  qurt_mem_region_t  hw_reg_mem_region;
  /* Hardware register memory region */

  hw_af_client_type_t client_mode;
  /* Operation mode of driver and currently supported clients */

  uint32_t max_avail_clock_mhz;
  /* Maximum available clock (in Mhz) */

}hw_af_drv_state_t;

/* Global HW AF state */
hw_af_drv_state_t hw_af_drv;

/*==============================================================================
   Local Function definition
==============================================================================*/


/* 
   Submit job

   param[in] virt_config_ptr: Virtual address pointing to Configuration
   param[in] virt_buffer_ptr: Virtual address pointing to Buffer

   return: None
 */
static inline void hw_af_submit_job(
  hw_af_config_t* virt_config_ptr, 
  hw_af_buffer_t* virt_buffer_ptr)
{
  hw_af_hal_job_submit(
    (uint32_t)qurt_elite_memorymap_get_physical_addr(
      (uint32_t)virt_config_ptr),
    (uint32_t)qurt_elite_memorymap_get_physical_addr(
      (uint32_t)virt_buffer_ptr));
}



/*
   Interrupt service routine

   param[in] arg_ptr: Argument got during IST routine

   return: None
 */
static void hw_af_intr_handler(void *arg_ptr)
{
  ADSPResult result = ADSP_EOK;
  uint64_t queue_entry;
  hw_af_job_t* next_job_ptr = NULL;

  /* Clear current interrupt */
  hw_af_hal_intr_clear();

  /* Signal caller */
  if(NULL != hw_af_drv.job_running_ptr->callback_func)
  {
    hw_af_drv.job_running_ptr->callback_func(
      hw_af_drv.job_running_ptr->callback_arg_ptr);  
  }  

  /* Queue job to free list */
  queue_entry = (uint64_t)hw_af_drv.job_running_ptr;
  qurt_elite_queue_push_back(hw_af_drv.job_free_queue_ptr, 
    &queue_entry);
  
  /* Lock pending and current job */
  qurt_elite_mutex_lock(&hw_af_drv.job_mutex);
  result = qurt_elite_queue_pop_front(hw_af_drv.job_pending_queue_ptr, 
    &queue_entry);
  if(ADSP_EOK == result)
  {
    next_job_ptr = (hw_af_job_t*)queue_entry;
    hw_af_drv.job_running_ptr = next_job_ptr;
  }
  else
  {
    /* No pending job */
    hw_af_drv.job_running_ptr = NULL;
  }
  qurt_elite_mutex_unlock(&hw_af_drv.job_mutex);

  if(NULL != next_job_ptr)
  {
    /* Submit next Job*/
    hw_af_submit_job(next_job_ptr->config_ptr, next_job_ptr->buffer_ptr);
  }

  return;
}

/*
   Prepare Buffer : Flush and Physical address translation

   param[out] hw_buffer_ptr: Buffer to be submitted to Hardware
   param[in] virt_buffer_ptr: Buffer in virtual address space used by client

   return: None
 */
static inline void hw_af_prepare_buffers(
  hw_af_buffer_t* hw_buffer_ptr,
  hw_af_buffer_t* virt_buffer_ptr)
{
  /* Based on system team analysis - optimize cache operations
   - qurt_invalidate / flush has a barrier syncht in every call     
   - If clients are forced to use contiguous memory - then we can flush one 
     contiguous chunck using formula:
        sizeof(hw_af_buffer_t) + 
        FilterCoef_size*numMics*numEchoRef*numSubBands*2 + 
        Mic_sample_size*numMics*numSubBands*4 +
        sizeof(hw_af_adaptation_flag_t)*numSubBands*numMics*numSamples + 
        sizeof(hw_af_inst_second_moments_t)*numSubBands*numMics        
   - Else, write ASM code to flush individual chuncks and final syncht as two
     separate functions 
   - Another optimization is to flush enite cache if buffer size is more than
     70% of cache size as the there are special instructions to flush entire 
     complete cache efficiently */

  /* Make local copy of config for phys addr translation */
  memscpy(hw_buffer_ptr, sizeof(hw_af_buffer_t),
    virt_buffer_ptr,sizeof(hw_af_buffer_t));

  /* Flush */
  if(virt_buffer_ptr->pFilterIn_size)
  {
    /* Flush buffer */
    qurt_elite_memorymap_cache_flush(
      (uint32_t)virt_buffer_ptr->pFilterIn,
      virt_buffer_ptr->pFilterIn_size);
    
    /* Phys addr translation */
    hw_buffer_ptr->pFilterIn = (void*)qurt_elite_memorymap_get_physical_addr(
        (uint32_t)virt_buffer_ptr->pFilterIn);
  }
  if(virt_buffer_ptr->pFilterCoef_size)
  {
    qurt_elite_memorymap_cache_flush(
      (uint32_t)virt_buffer_ptr->pFilterCoef,
      virt_buffer_ptr->pFilterCoef_size);

    /* Phys addr translation */
    hw_buffer_ptr->pFilterCoef = (void*)qurt_elite_memorymap_get_physical_addr(
        (uint32_t)virt_buffer_ptr->pFilterCoef);
  }
  if(virt_buffer_ptr->pMicInErrOut_size)
  {
    qurt_elite_memorymap_cache_flush(
      (uint32_t)virt_buffer_ptr->pMicInErrOut,
      virt_buffer_ptr->pMicInErrOut_size);

    /* Phys addr translation */
    hw_buffer_ptr->pMicInErrOut = (void*)qurt_elite_memorymap_get_physical_addr(
        (uint32_t)virt_buffer_ptr->pMicInErrOut);
  }
  if(virt_buffer_ptr->pFilterCoefBG_size)
  {
    qurt_elite_memorymap_cache_flush(
      (uint32_t)virt_buffer_ptr->pFilterCoefBG,
      virt_buffer_ptr->pFilterCoefBG_size);

    /* Phys addr translation */
    hw_buffer_ptr->pFilterCoefBG = 
      (void*)qurt_elite_memorymap_get_physical_addr(
        (uint32_t)virt_buffer_ptr->pFilterCoefBG);
  }
  if(virt_buffer_ptr->pAdaptFlags_size)
  {
    qurt_elite_memorymap_cache_flush(
      (uint32_t)virt_buffer_ptr->pAdaptFlags,
      virt_buffer_ptr->pAdaptFlags_size);

    /* Phys addr translation */
    hw_buffer_ptr->pAdaptFlags = (void*)qurt_elite_memorymap_get_physical_addr(
        (uint32_t)virt_buffer_ptr->pAdaptFlags);
  }

  /* No flush - just phys addr translation */
  hw_buffer_ptr->pFilterOut = (void*)qurt_elite_memorymap_get_physical_addr(
        (uint32_t)virt_buffer_ptr->pFilterOut);
  hw_buffer_ptr->pErrorBG = (void*)qurt_elite_memorymap_get_physical_addr(
        (uint32_t)virt_buffer_ptr->pErrorBG);
  hw_buffer_ptr->pFilterOutBG = (void*)qurt_elite_memorymap_get_physical_addr(
      (uint32_t)virt_buffer_ptr->pFilterOutBG);
  hw_buffer_ptr->pISM = (void*)qurt_elite_memorymap_get_physical_addr(
        (uint32_t)virt_buffer_ptr->pISM);
  
  /* Flush main structure */  
  qurt_elite_memorymap_cache_flush((uint32_t)hw_buffer_ptr, 
    sizeof(hw_af_buffer_t));
}

/*
   Prepare Configuration : Flush and Physical address translation

   param[out] hw_config_ptr: Configuration to be submitted to Hardware
   param[in] virt_config_ptr: Configuration in virtual address space used by 
                              client

   return: None
 */
static inline void hw_af_prepare_config(
  hw_af_config_t* hw_config_ptr,
  hw_af_config_t* virt_config_ptr)
{
  /* Make local copy of config for phys addr translation */
  memscpy(hw_config_ptr, sizeof(hw_af_config_t),
    virt_config_ptr,sizeof(hw_af_config_t));

  /* Flush linked buffer */
  qurt_elite_memorymap_cache_flush((uint32_t)virt_config_ptr->pChanCfg,
      sizeof(hw_af_channel_config_t)*hw_config_ptr->pChanCfg_buf_size);

  /* Phys addr translation */
  hw_config_ptr->pChanCfg = (hw_af_channel_config_t*)
    qurt_elite_memorymap_get_physical_addr(
      (uint32_t)hw_config_ptr->pChanCfg);

  /* Flush main structure */  
  qurt_elite_memorymap_cache_flush((uint32_t)hw_config_ptr,
      sizeof(hw_af_config_t));
}

/*
   Process a job async using hardware adaptive filter

   param[in] hw_af_ptr: instance of hardware adaptive filter
   param[in/out] hw_af_buffer_ptr: input/output buffers used for processing
   param[in] callback_func: Callback routine called once job is completed
   param[in] callback_arg_ptr: Argument for above call back routine

   return: ADSP_EOK(0) on success else failure error code
 */
static inline ADSPResult hw_af_process_async(
  hw_af_t* hw_af_ptr,
  hw_af_buffer_t* hw_af_buffer_ptr,
  hw_af_callback_func_t callback_func,
  void* callback_arg_ptr)
{
  bool_t hw_acquired = FALSE;
  hw_af_job_t* sync_job_ptr = NULL;
  uint64_t queue_entry;
  ADSPResult result = ADSP_EOK;

  result = qurt_elite_queue_pop_front(hw_af_drv.job_free_queue_ptr, 
    &queue_entry);
  if(ADSP_EOK != result)
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "No free job 0x%x", 
      result);
  }
  sync_job_ptr = (hw_af_job_t*)(queue_entry);

  sync_job_ptr->callback_func = callback_func;
  sync_job_ptr->callback_arg_ptr = callback_arg_ptr;
  sync_job_ptr->config_ptr = hw_af_ptr->config_ptr;
  hw_af_prepare_buffers(sync_job_ptr->buffer_ptr, hw_af_buffer_ptr);
  
  /* Lock pending and current job */
  qurt_elite_mutex_lock(&hw_af_drv.job_mutex);
  if(NULL == hw_af_drv.job_running_ptr)
  {
    hw_af_drv.job_running_ptr = sync_job_ptr;
    hw_acquired = TRUE;
  }
  else
  {
    /* Queue pending job  */
    qurt_elite_queue_push_back(hw_af_drv.job_pending_queue_ptr,
      &queue_entry);
  }
  qurt_elite_mutex_unlock(&hw_af_drv.job_mutex);

  if(TRUE == hw_acquired)
  {
    /* Submit job in client's context */
    hw_af_submit_job(sync_job_ptr->config_ptr, sync_job_ptr->buffer_ptr);
  }
  
  return ADSP_EOK;
}

/*
   Process a job sync using hardware adaptive filter

   param[in] hw_af_ptr: instance of hardware adaptive filter
   param[in/out] hw_af_buffer_ptr: input/output buffers used for processing

   return: ADSP_EOK(0) on success else failure error code
 */
static inline ADSPResult hw_af_process_sync(
  hw_af_t* hw_af_ptr,
  hw_af_buffer_t* hw_af_buffer_ptr)
{
  ADSPResult result = ADSP_EOK;
  qurt_elite_signal_t job_completed_sig;
  qurt_elite_channel_t job_completed_ch;

  /* Init local wait */
  qurt_elite_signal_init(&job_completed_sig);
  qurt_elite_channel_init(&job_completed_ch);
  qurt_elite_channel_add_signal(&job_completed_ch, &job_completed_sig, 
    HW_AF_SYNC_JOB_WAIT_MASK);

  /* Submit job */
  result = hw_af_process_async(hw_af_ptr,
    hw_af_buffer_ptr,
    (hw_af_callback_func_t)qurt_elite_signal_send,
    (void*)&job_completed_sig);

  if(ADSP_EOK == result)
  {
    /* Wait for job compleion */
    qurt_elite_channel_wait(&job_completed_ch, HW_AF_SYNC_JOB_WAIT_MASK);
    /* Flush output */
    hw_af_fetch(hw_af_ptr, hw_af_buffer_ptr);  
  }  

  /* Deinit local signal */
  qurt_elite_signal_deinit(&job_completed_sig);
  qurt_elite_channel_destroy(&job_completed_ch);

  return result;
}

/*
   Calculate clock and bandwidth

   param[in] config_ptr: filter configuration
   param[in] client_info_ptr: client info pointer
   param[out] hw_af_ptr: client instance pointer

   return: None
 */
static inline void hw_af_calc_clk_bw(
  hw_af_config_t* config_ptr,
  hw_af_client_info_t* client_info_ptr,
  hw_af_t* hw_af_ptr)
{
  uint64_t clk_req_mhz = 0;
  uint64_t bandwidth = 0;
  uint32_t iter = 0;
  uint32_t num_channel_cfgs = 0;
  uint32_t filter_len_low_bands = 0;
  uint32_t filter_len_high_bands = 0;
  uint32_t num_sub_frames = 0;
  uint32_t num_sub_bands = 0;
  uint32_t num_low_bands = 0;
  uint32_t num_high_bands = 0;
  uint32_t bytes_per_sample = 0;
  uint32_t num_mics = 0;
  uint32_t num_speaker_refs = 0;
  hw_af_channel_config_t* ch_config_ptr = NULL;


  switch(config_ptr->inputType)
  {
    case HW_TYPE_REAL_FIX_16_BIT:
      /* Real only 16bits */
      bytes_per_sample = 2;
      break;
    case HW_TYPE_REAL_FIX_32_BIT:
      /* Real only 32bits */
      bytes_per_sample = 4;
      break;
    case HW_TYPE_COMPLEX_FIX_64_BIT:
    default:
      /* Complex : 32bit real and 32bit imaginary */
      bytes_per_sample = 8;
      break;
  }

  if(config_ptr->filterType | HW_FILTER_ADAPTIVE_TIME_GROUP)
  {
    if(config_ptr->filterType | HW_AF_SPKR_MONO)
    {
      num_speaker_refs = 1;
    }
    else /*if(config_ptr->filterType | HW_AF_SPKR_STEREO)*/
    {
      num_speaker_refs = 2;
    }
  }
  else /* Sub band domain */
  {
    if(config_ptr->filterType | HW_AF_SPKR_MONO)
    {
      num_speaker_refs = 1;
    }
    else if(config_ptr->filterType | HW_AF_SPKR_STEREO)
    {
      num_speaker_refs = 2;
    }
    else /* if(config_ptr->filterType | HW_AF_SPKR_MULTI_CHAN_FF) */
    {
      num_speaker_refs = config_ptr->numMics;
    }
  }

  num_channel_cfgs = config_ptr->pChanCfg_buf_size / 
    sizeof(hw_af_channel_config_t);
  num_sub_bands = config_ptr->numSubBands;
  num_low_bands = config_ptr->nSBandsLargeFLen;
  num_high_bands = num_sub_bands - num_low_bands;
  num_mics = config_ptr->numMics;
  num_sub_frames = config_ptr->numSamples;
  
  /* Iterate thru all channels and find max filter length */
  for( iter = 0; iter < num_channel_cfgs; iter++)
  {
    ch_config_ptr = &config_ptr->pChanCfg[iter];
    filter_len_low_bands = MAX(filter_len_low_bands, ch_config_ptr->filterLen);
    filter_len_high_bands = MAX(filter_len_high_bands, 
                                ch_config_ptr->filterLenHB);
  }

  /*--------------------------------------------------------------------------*
   |                       Clock Calculator                                   |
   *--------------------------------------------------------------------------*/
  /* Low band contribution */
  clk_req_mhz = num_low_bands * ( 26 + 3 * filter_len_low_bands +
                num_sub_frames * MAX(57, (3 + filter_len_low_bands)));
  /* High band contribution */
  clk_req_mhz += num_high_bands * ( 26 + 3 * filter_len_high_bands +
                 num_sub_frames * MAX(57, (3 + filter_len_high_bands)));
  /* Clock per frame */
  clk_req_mhz *= num_mics;
  /* Clock in Mhz */
  clk_req_mhz = clk_req_mhz/client_info_ptr->block_size_in_us;
  /* Store */
  hw_af_ptr->clk_req_mhz = (uint32_t)clk_req_mhz;

  MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, 
    "Low Band:Filter length = %ld, num low bands=%ld",
    filter_len_low_bands, num_low_bands);
  MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, 
    "high Band:Filter length = %ld, num high bands=%ld",
    filter_len_high_bands, num_high_bands);
  MSG_3(MSG_SSID_QDSP6, DBG_HIGH_PRIO, 
    "Num mics = %ld, Block size (us) =%ld, Num sub frames = %ld",
    num_mics, client_info_ptr->block_size_in_us, num_sub_frames);
  MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, 
    "Required clock (Mhz) = %ld",
    hw_af_ptr->clk_req_mhz);

  /*--------------------------------------------------------------------------*
   |                       Bandwidth calculator                               |
   *--------------------------------------------------------------------------*/
  /* Mics */
  bandwidth = num_mics * num_sub_bands * 
              num_sub_frames * bytes_per_sample;
  /* FG filter weights */
  if((config_ptr->filterType|HW_FILTER_ADAPTIVE_TIME_FG) ||
     (config_ptr->filterType|HW_FILTER_ADAPTIVE_FFT_SUBBAND_FG)  )
  {
    bandwidth =  bandwidth * 3 /* Input, Output and Error */+ 
                 (num_low_bands * filter_len_low_bands + 
                  num_high_bands * filter_len_high_bands) * 
                 num_mics * bytes_per_sample;
  }
  else  
  {
    /* FG & BG filter weights */
    bandwidth =  bandwidth * 5 /* Input, Output(FG,BG) and Error(FG,BG ) */ + 
                 (num_low_bands * filter_len_low_bands + 
                  num_high_bands * filter_len_high_bands) * 
                 num_mics * bytes_per_sample * 3 /* FG, BG in and BG out */;
  }
  
  /* Speaker Ref */
  bandwidth += (num_low_bands*(filter_len_low_bands + num_sub_frames - 1) +
                num_high_bands*(filter_len_high_bands + num_sub_frames - 1) ) *
               num_speaker_refs * bytes_per_sample;
  
  /* Adapt flags */
  bandwidth += num_sub_bands * num_mics * num_sub_frames * 
               num_speaker_refs * sizeof(hw_af_adaptation_flag_t);
  
  /* Inst. Energies */
  bandwidth += num_mics * num_sub_bands * 20;
  
  /* Bytes Per second */
  bandwidth = bandwidth/client_info_ptr->block_size_in_us;
  
  /* Apply bandwidth factor and ceiling */
  bandwidth += (bandwidth * client_info_ptr->bw_scaling_factor_q10 + 0x3FF)>>10;
  
  /* Store bandwidth */  
  hw_af_ptr->data_bandwidth = bandwidth;

  MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, 
    "Required bandwidth (bytes per second) = %ld",
    hw_af_ptr->data_bandwidth);

}

/*
   Aggregate all clients requirement and vote.
   In High Latency mode - check whether all clients aggregated clock requirement
   is available in HW AF core.

   return: Error status
 */

static inline ADSPResult hw_af_aggregate_vote(void)
{
  ADSPResult result = ADSP_EOK;
  int32_t iter;
  uint64_t total_clock = 0; 
  uint64_t total_bandwidth = 0;
  uint32_t min_block_size = ~0;
  
  if(0 == hw_af_drv.num_clients_in_use)
  {
    /* TODO: MMPM Devote everything 
       (Aggregated HW AF hardware clk/bandwidth - Onetime QDSP clk/bandwidth)*/
    return result;
  }

  /* Find min block size */
  for( iter=0; iter<HW_AF_MAX_NUM_CLIENT; iter++ )
  {
    if(TRUE == hw_af_drv.clients[iter].in_use)
    {
      min_block_size = MIN(hw_af_drv.clients[iter].client_info.block_size_in_us, 
                           min_block_size);
    }
  }

  if(min_block_size == 0)
  {
    MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "client block size cannot be 0ms");
    return ADSP_EUNEXPECTED;
  }

  /* Aggregate across all clients */
  for( iter=0; iter<HW_AF_MAX_NUM_CLIENT; iter++ )
  {
    if(TRUE == hw_af_drv.clients[iter].in_use)
    {
      total_clock += (hw_af_drv.clients[iter].clk_req_mhz*min_block_size)/
                     hw_af_drv.clients[iter].client_info.block_size_in_us;
      total_bandwidth += (hw_af_drv.clients[iter].data_bandwidth*
                          min_block_size)/
                          hw_af_drv.clients[iter].client_info.block_size_in_us;
    }    
  }

  if(0 == hw_af_drv.max_avail_clock_mhz)
  {
    /* TODO: One time query and set Max available clock        
        MMPM_GetInfo(MmpmInfoDataType *pInfoData) */
    hw_af_drv.max_avail_clock_mhz = 600;
  }  
  if(hw_af_drv.max_avail_clock_mhz < total_clock)
  {
    MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, 
      "Unable to support aggregated clock "
      "required=%ld, availabe=%ld",
      total_clock, hw_af_drv.max_avail_clock_mhz);
    return ADSP_ENORESOURCE;
  }
  
  /* TODO: MMPM Vote - aggregated HW AF clock and bandwidth */

  return result;
}

/*
  Kill client jobs
  Typically, client jobs should be completed before closing. In abrupt client 
  closure, driver ought to kill/remove clients jobs

  param[out] hw_af_ptr: client instance pointer

  return: None
 */
static inline void hw_af_kill_client_jobs(hw_af_t* hw_af_ptr)
{
  ADSPResult result = ADSP_EOK;
  uint64_t queue_entry;
  hw_af_job_t* last_job_ptr = NULL;
  hw_af_job_t* curr_job_ptr = NULL;

  /* Lock pending and current job */
  qurt_elite_mutex_lock(&hw_af_drv.job_mutex);  
  result = qurt_elite_queue_pop_back(hw_af_drv.job_pending_queue_ptr, 
      &queue_entry);
  if(ADSP_EOK == result)
  {
    /* Keep track of end of queue */
    last_job_ptr = (hw_af_job_t*)queue_entry;
    /* Push last job back to end of queue */
    qurt_elite_queue_push_back(hw_af_drv.job_pending_queue_ptr,
        &queue_entry);     

    /* Iterate and remove client's jobs */
    while(ADSP_EOK == 
      qurt_elite_queue_pop_front(hw_af_drv.job_pending_queue_ptr, 
        &queue_entry))
    {
      curr_job_ptr = (hw_af_job_t*)queue_entry;
      if(curr_job_ptr->client_ptr == hw_af_ptr)
      {
        /* Set job as free */
        qurt_elite_queue_push_back(hw_af_drv.job_free_queue_ptr,
          &queue_entry);       
      }
      else
      {
        /* Store non-client job back to pending queue */
        qurt_elite_queue_push_back(hw_af_drv.job_pending_queue_ptr,
            &queue_entry);  
      }      

      if(last_job_ptr == curr_job_ptr)
      {
        /* Reached end of queue - checked entire list */
        break;
      }
    }
  }  
  qurt_elite_mutex_unlock(&hw_af_drv.job_mutex);

  /* Kill pending jobs by client */
  if(NULL != hw_af_drv.job_running_ptr && 
     hw_af_ptr == hw_af_drv.job_running_ptr->client_ptr)
  {
    /* Disable interrupt */
    hw_af_hal_intr_disable();  
    
    /* Double check if job is still running */
    if(NULL != hw_af_drv.job_running_ptr && 
       hw_af_ptr == hw_af_drv.job_running_ptr->client_ptr)
    {
      /* Next job is still current client' job. Interrupt is now disabled. 
         Hence, no need to lock to change job callback */
      hw_af_drv.job_running_ptr->callback_func = NULL;
      hw_af_drv.job_running_ptr->callback_arg_ptr = NULL;

      /* Sent Kill signal */
      hw_af_hal_job_kill();
    }

    /* Enable Interrupt */
    hw_af_hal_intr_enable();  
  }
}

/*==============================================================================
   Public Function definition
==============================================================================*/
/* 
   Initialize hardware adaptive filter driver

   return: ADSP_EOK(0) on success else failure error code
 */
ADSPResult hw_af_init(void)
{
  ADSPResult result = ADSP_EOK;
  uint32_t iter = 0;
  uint64_t queue_entry;
  uint32_t base_virt_addr = 0;

  /* Read hardware config */
  result = HwdDevCfg_ReadModuleConfigData(HWD_MODULE_TYPE_ADAPTIVE_FILTER,
    (void*)&(hw_af_drv.property));
  if(ADSP_EOK != result)
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "HW dev cfg read failed 0x%x", 
      result);
    return result;
  }

  /* Check if hardware supported */
  if(hw_af_drv.property.reg_size == 0)
  { 
    MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, 
      "HW AF not supported in this LPASS version\n");
    return ADSP_EOK; 
  } 
  
  /* Get Virtual Address */
  result = HwdDevCfg_GetVirtAddress(
    &(hw_af_drv.hw_reg_mem_region), 
    hw_af_drv.property.base_reg_phy_addr, 
    hw_af_drv.property.reg_size,
    &base_virt_addr);
  if(ADSP_EOK != result)
  {
    MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, 
      "HW dev cfg failed obtaining virtual addr \n");
    return result;
  }

  /* HAL Init */
  hw_af_hal_init(base_virt_addr, hw_af_drv.property.hw_revision);

  MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "HW AF Interrupt no 0x%x", 
      (uint16_t)hw_af_drv.property.int_irq_no);

  /* Register with IST */
  result = qurt_elite_interrupt_register( &hw_af_drv.ist,
    (uint16_t)hw_af_drv.property.int_irq_no,
    hw_af_intr_handler,
    NULL,
    "hw_af_ist", 
    HW_AF_IST_STACK_SIZE_BYTES);
  if(ADSP_EOK != result)
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Unable to register IST 0x%x", 
      result);
    return result;
  }

  /* One time state variable initializations */
  qurt_elite_mutex_init(&hw_af_drv.drv_mutex);
  qurt_elite_mutex_init(&hw_af_drv.job_mutex);
  qurt_elite_channel_init(&hw_af_drv.job_queue_channel);
  result = qurt_elite_queue_create("hw af free job", HW_AF_MAX_NUM_JOB, 
    &hw_af_drv.job_free_queue_ptr);
  result |= qurt_elite_queue_create("hw af running job", HW_AF_MAX_NUM_JOB, 
    &hw_af_drv.job_pending_queue_ptr);    
  if(ADSP_EOK == result)
  {
    result |= qurt_elite_channel_addq(&hw_af_drv.job_queue_channel,
      hw_af_drv.job_free_queue_ptr, HW_AF_JOB_QUEUE_CH_ANY_MASK);  
    result |= qurt_elite_channel_addq(&hw_af_drv.job_queue_channel,
      hw_af_drv.job_pending_queue_ptr, HW_AF_JOB_QUEUE_CH_ANY_MASK);  
  }
  
  if(ADSP_EOK == result)
  {
    /* Attach free jobs */
    for(iter = 0; iter < HW_AF_MAX_NUM_JOB; iter++)
    {
      hw_af_drv.jobs[iter].buffer_ptr = (hw_af_buffer_t*)
        qurt_elite_memory_aligned_malloc(
          sizeof(hw_af_buffer_t),
          HW_AF_ALLOC_ALIGN,
          QURT_ELITE_HEAP_DEFAULT);
      if(NULL == hw_af_drv.jobs[iter].buffer_ptr)
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, 
          "Unable to allocate buffer size = %ld", 
          sizeof(hw_af_buffer_t));
        result = ADSP_EFAILED;
        break;
      }
      queue_entry = (uint64_t)&hw_af_drv.jobs[iter];
      result |= qurt_elite_queue_push_back(hw_af_drv.job_free_queue_ptr, 
        &queue_entry);
    }
  }

  if(ADSP_EOK != result)
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "HW AF init failed 0x%x", result);
    hw_af_deinit();
  }

  return result;
}

/* 
   Initialize hardware adaptive filter driver

   return: ADSP_EOK(0) on success else failure error code
 */
ADSPResult hw_af_deinit(void)
{
  ADSPResult result = ADSP_EOK;
  uint32_t iter = 0;

  if(hw_af_drv.property.reg_size == 0)
  { 
    /* Nothing to deinit */
    return ADSP_EOK; 
  } 

  /* Close unclosed clients */
  for( iter=0; iter<HW_AF_MAX_NUM_CLIENT; iter++ )
  {
    if(hw_af_drv.clients[iter].in_use)
    {
      hw_af_close(&hw_af_drv.clients[iter]);
    }
  }

  /* Free up singleton resources de-initialization */  
  result = qurt_elite_interrupt_unregister(&hw_af_drv.ist);  
  qurt_elite_mutex_destroy(&hw_af_drv.drv_mutex);
  qurt_elite_mutex_destroy(&hw_af_drv.job_mutex);
  qurt_elite_channel_destroy(&hw_af_drv.job_queue_channel);
  qurt_elite_queue_destroy(hw_af_drv.job_free_queue_ptr);
  qurt_elite_queue_destroy(hw_af_drv.job_pending_queue_ptr);
  result |= HwdDevCfg_DestoryVirtAddress(hw_af_drv.hw_reg_mem_region);
  hw_af_drv.hw_reg_mem_region = NULL;

  for(iter = 0; iter < HW_AF_MAX_NUM_JOB; iter++)
  {
    if(NULL != hw_af_drv.jobs[iter].buffer_ptr)
    {
      qurt_elite_memory_aligned_free(hw_af_drv.jobs[iter].buffer_ptr);
      hw_af_drv.jobs[iter].buffer_ptr = NULL;
    }
  }
  
  /* Set all state value back to boot state */
  memset(&hw_af_drv, 0, sizeof(hw_af_drv));

  return result;
}

/* 
   Open an instance of hardware adaptive filter

   param[in] config_ptr: Filter configuration
   param[in] client_info_ptr: Information about the client

   return: instance of hardware adaptive filter
 */
hw_af_t* hw_af_open(
  hw_af_config_t* config_ptr, 
  hw_af_client_info_t* client_info_ptr)
{
  uint32_t i = 0;
  hw_af_t* hw_af_ptr = NULL;
  bool_t first_client = FALSE;
  ADSPResult result = ADSP_EOK;

  /* Check if hardware supported */
  if(hw_af_drv.property.reg_size == 0)
  { 
    MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, 
      "HW AF not supported in this LPASS version\n");
    return NULL; 
  } 

  /* Lock critical section */
  qurt_elite_mutex_lock(&hw_af_drv.drv_mutex);

  if(hw_af_drv.client_mode != NO_PREFERENCE_CLIENT && 
     hw_af_drv.client_mode != client_info_ptr->client_type)
  {
    MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, 
      "Error: hw drv mode is [%d] while client type was [%d]",
      hw_af_drv.client_mode, client_info_ptr->client_type);
    goto __bail;
  }

  if(hw_af_drv.num_clients_in_use < HW_AF_MAX_NUM_CLIENT)
  {
    /* Scan for free client */
    for( i=0; i<HW_AF_MAX_NUM_CLIENT; i++ )
    {
      if(FALSE == hw_af_drv.clients[i].in_use)
      {
        hw_af_ptr = &(hw_af_drv.clients[i]);    
        hw_af_ptr->in_use = TRUE;
        if(0 == hw_af_drv.num_clients_in_use)
        {
          first_client = TRUE;
        }
        hw_af_drv.num_clients_in_use++;        
        break;
      }
    }
  }

  if(NULL == hw_af_ptr)
  {
    MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, 
      "Couldn't find a un-used entry to open a new client ");
    goto __bail;
  }

  /* Set driver client_mode */
  hw_af_drv.client_mode = client_info_ptr->client_type;
  /* Save client info */
  hw_af_ptr->client_info = *client_info_ptr;

  /* calculate and update kpps and bandwidth */
  hw_af_calc_clk_bw(config_ptr, client_info_ptr, hw_af_ptr);

  /* Vote for aggregated KPPS and and bandwidth */
  result = hw_af_aggregate_vote();
  if(ADSP_EOK != result)
  {
    MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, 
      "Couldn't aggregate new client's clk[%ld],bw[%ld]",
      hw_af_ptr->clk_req_mhz, hw_af_ptr->data_bandwidth);
    goto __bail;
  }

  /* Fixes register retain issue */
  hw_af_hal_noc_register_fix();

  /* Allocate space to store configuration */
  hw_af_ptr->config_ptr = qurt_elite_memory_aligned_malloc(
    sizeof(hw_af_config_t),
    HW_AF_ALLOC_ALIGN,
    QURT_ELITE_HEAP_DEFAULT);
  if(NULL == hw_af_ptr->config_ptr)
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, 
      "Couldn't allocate hw_af_config_t(%ld) for client ",
      sizeof(hw_af_config_t));
    goto __bail;
  }

  /* Flush configuration*/
  hw_af_prepare_config(hw_af_ptr->config_ptr, config_ptr);

  if(TRUE == first_client)
  {
    /* TODO: MMPM Vote - First client 
       - Vote for QDSP6 driver routines (Flush/Invalidate operations ~5MIPS) */

    /* Enable interrupt */
    hw_af_hal_intr_enable();
  }

__bail:
  if(ADSP_EOK != result)
  {
    /* Unable to initilaize one time */
    hw_af_close(hw_af_ptr);
    hw_af_ptr = NULL;
    goto __bail;
  }

  /* Un-Lock critical section */
  qurt_elite_mutex_unlock(&hw_af_drv.drv_mutex);

  return hw_af_ptr;
}

/* 
   Close the instance of hardwar adaptive filter

   param[in] hw_af_ptr: instance of hardware adaptive filter

   return: nothing
 */
void hw_af_close(
  hw_af_t* hw_af_ptr)
{
  uint32_t i = 0;
  bool_t last_client = FALSE;
  bool_t client_disabled = FALSE;

  if(NULL == hw_af_ptr)
  {
    MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, 
      "Null arg as session pointer ");
    return;
  }
  
  /* Lock critical section */
  qurt_elite_mutex_lock(&hw_af_drv.drv_mutex);

  /* Scan for free client */
  for( i=0; i<HW_AF_MAX_NUM_CLIENT; i++ )
  {
    if(hw_af_ptr == &(hw_af_drv.clients[i]))
    {
      if(TRUE == hw_af_ptr->in_use)
      {
        /* Kill any pending jobs */
        hw_af_kill_client_jobs(hw_af_ptr);

        /* Clean up resources used for client */ 
        if(NULL != hw_af_ptr->config_ptr)
        {
          qurt_elite_memory_aligned_free(hw_af_ptr->config_ptr);  
          hw_af_ptr->config_ptr = NULL;
        }       
        
        memset(hw_af_ptr,0, sizeof(hw_af_t));
        hw_af_ptr->in_use = FALSE;
        hw_af_drv.num_clients_in_use--;
        if(0 == hw_af_drv.num_clients_in_use)
        {
          last_client = TRUE;
        }
        client_disabled = TRUE;
      }
      break;
    }
  }

  if(i == HW_AF_MAX_NUM_CLIENT)
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, 
      "Invalid client 0x%x, unable to close", hw_af_ptr);    
    goto __bail;
  }
  
  if(TRUE == client_disabled)
  {
    /* Vote for aggregated KPPS and and bandwidth */
    hw_af_aggregate_vote();
  }

  if(TRUE == last_client)
  {    
    /* Reset driver client_mode */
    hw_af_drv.client_mode = NO_PREFERENCE_CLIENT;

    /* Disable further interrupt */
    hw_af_hal_intr_disable();

    /* TODO: MMPM Vote - Last client 
       - De Vote for QDSP6 driver routines - done onetime in first open */
  }


__bail:
  /* Un-Lock critical section */
  qurt_elite_mutex_unlock(&hw_af_drv.drv_mutex);

  return;
}

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
  void* callback_arg_ptr)
{
  ADSPResult result = ADSP_EOK;

  if(NULL == hw_af_ptr || NULL == hw_af_buffer_ptr)
  {
    MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, 
      "Null arg hw_af_ptr=%p, hw_af_buffer_ptr=%p",
      hw_af_ptr, hw_af_buffer_ptr);
    return ADSP_EBADPARAM;
  }

  /* Schedule job */
  if(NULL != callback_func)
  {
    /* Call async */
    result = hw_af_process_async(hw_af_ptr, hw_af_buffer_ptr, 
      callback_func, callback_arg_ptr);
  }
  else
  {
    /* Call sync */
    result = hw_af_process_sync(hw_af_ptr, hw_af_buffer_ptr);
  }


  return result;
}

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
  hw_af_buffer_t* hw_af_buffer_ptr)
{
  if(NULL == hw_af_ptr || NULL == hw_af_buffer_ptr)
  {
    MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, 
      "Null arg hw_af_ptr=%p, hw_af_buffer_ptr=%p",
      hw_af_ptr, hw_af_buffer_ptr);
    return ADSP_EBADPARAM;
  }

  /* Invalidate output buffers */
  if(hw_af_buffer_ptr->pMicInErrOut_size)
  {
    qurt_elite_memorymap_cache_invalidate(
      (uint32_t)hw_af_buffer_ptr->pMicInErrOut,
      hw_af_buffer_ptr->pMicInErrOut_size);
  }
  if(hw_af_buffer_ptr->pErrorBG_size)
  {
    qurt_elite_memorymap_cache_invalidate(
      (uint32_t)hw_af_buffer_ptr->pErrorBG,
      hw_af_buffer_ptr->pErrorBG_size);
  }
  if(hw_af_buffer_ptr->pFilterOut_size)
  {
    qurt_elite_memorymap_cache_invalidate(
      (uint32_t)hw_af_buffer_ptr->pFilterOut,
      hw_af_buffer_ptr->pFilterOut_size);
  }
  if(hw_af_buffer_ptr->pFilterOutBG_size)
  {
    qurt_elite_memorymap_cache_invalidate(
      (uint32_t)hw_af_buffer_ptr->pFilterOutBG,
      hw_af_buffer_ptr->pFilterOutBG_size);
  }  
  if(hw_af_buffer_ptr->pISM_size)
  {
    qurt_elite_memorymap_cache_flush(
      (uint32_t)hw_af_buffer_ptr->pISM,
      hw_af_buffer_ptr->pISM_size);
  }

  /* Based on BG/FG usage, invalidate coefficients */
  if( hw_af_ptr->config_ptr->filterType & HW_FILTER_ADAPTIVE_FG_BG_GROUP )
  {
    /* When BG is used, only invalidate BG */
    if(hw_af_buffer_ptr->pFilterCoefBG_size)
    {
      qurt_elite_memorymap_cache_invalidate(
        (uint32_t)hw_af_buffer_ptr->pFilterCoefBG,
        hw_af_buffer_ptr->pFilterCoefBG_size);
    }
  }
  else
  {
    /* no BG used, only invalidate FG */
    if(hw_af_buffer_ptr->pFilterCoef_size) 
    {
      qurt_elite_memorymap_cache_invalidate(
        (uint32_t)hw_af_buffer_ptr->pFilterCoef,
        hw_af_buffer_ptr->pFilterCoef_size);
    }
  }

  return ADSP_EOK;
}
