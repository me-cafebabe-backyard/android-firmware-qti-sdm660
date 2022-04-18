/*==============================================================================
$Header: //components/rel/avs.adsp/2.8/afe/drivers/afe/pcie/src/AFEPCIeDriver.cpp#1 $
$DateTime: 2018/06/19 06:00:11 $
$Author: pwbldsvc $
$Change: 16448086 $
$Revision: #1 $

FILE:     AFEpcieudioDriver.cpp

DESCRIPTION: Main Interface to the AFE PCIe driver

PUBLIC CLASSES:  Not Applicable

INITIALIZATION AND SEQUENCING REQUIREMENTS:  N/A

Copyright (c) 2018 QUALCOMM Technologies, Inc.  All Rights Reserved.
QUALCOMM Technologies, Inc Proprietary.  Export of this technology or software is regulated
by the U.S. Government, Diversion contrary to U.S. law prohibited.
==============================================================================*/
/*============================================================================
EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order. Please
use ISO format for dates.

$Header: //components/rel/avs.adsp/2.8/afe/drivers/afe/pcie/src/AFEPCIeDriver.cpp#1 $ $DateTime: 2018/06/19 06:00:11 $ $Author: pwbldsvc $

when        who  what, where, why
----------  ---  ----------------------------------------------------------
02-22-2016  mk  Initial Draft


============================================================================*/

/*=====================================================================
 Includes
 ======================================================================*/
#include "AFEPCIeDriver_i.h"
#include "qurt.h"
extern "C" 
{
  #include "ipa_vop.h"
}

/*=====================================================================
 Globals
 ======================================================================*/

// AFE PCIe Driver instance
static pcie_driver_state_t  g_pcie_driver_state;
static afe_dev_port_t  afe_pcie_ports_global[AFE_PORT_ID_PCIE_RANGE_SIZE] __attribute__((__section__(".bss.lpa_audio_static_svc_afe")));


/*=====================================================================
 Static Functions
 ======================================================================*/

/*=====================================================================
 Define Functions
 ======================================================================*/

/*=====================================================================
 Functions
 ======================================================================*/

void afe_pcie_data_callback(void *cbCtxt, uint32 addr_lsw, uint32 addr_msw, uint32 size, ipa_vop_resp_cb_err_code_e res)
{
  afe_dev_port_t *afe_port_ptr = (afe_dev_port_t *)cbCtxt;
  afe_pcie_dev_state_struct_t *p_dev_state = NULL; 
  uint32_t req_size = 0;
	
  p_dev_state = (afe_pcie_dev_state_struct_t *)afe_port_ptr->afe_drv;  
  p_dev_state->cb_counter++;
  
  (void) afe_driver_pcie_get_header_size( afe_port_ptr, &req_size);
  req_size += afe_port_ptr->int_samples_per_period * afe_port_ptr->channels * afe_port_ptr->bytes_per_channel;
  
  if ( (AFE_PORT_STATE_RUN != afe_port_ptr->port_state) || 
  		 ( size != req_size ) || 
  		 ( IPA_VOP_RESP_CB_COMPLETE != res ) )
  {
    // Error scenario
    MSG_5(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"afe_pcie_data_callback : direction %d, port_state %d, size %d, req_size %d, response %d",
    																			afe_port_ptr->dir, afe_port_ptr->port_state, size, req_size, res);
  }    
  if( ( IPA_VOP_RESP_CB_STALE_DATA == p_dev_state->resp ) && 
  		( IPA_VOP_RESP_CB_STALE_DATA == res ) &&
  		( TX_DIR == afe_port_ptr->dir ) )
  {
  	/* Received stale data even after repoll, so error out. */
  	p_dev_state->resp = IPA_VOP_RESP_CB_ERR_FAIL;  	
		MSG_4(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"afe_pcie_data_callback :Received stale data even after repoll"
																				 "port_state %d, size %d, req_size %d, response %d",
																					afe_port_ptr->port_state, size, req_size, res);
  }
  else
  {  
  	p_dev_state->resp = res;
  }
  if ( (AFE_PORT_STATE_RUN == afe_port_ptr->port_state) &&
    	 ( TX_DIR == afe_port_ptr->dir ) )  
  {    
    // signal to the port data thread about the finishing of the data transfer
    qurt_elite_signal_send(&afe_port_ptr->dma_signal);
  }
}

ADSPResult afe_pcie_send_sub_unsub_msg_to_voicetimer(qurt_elite_queue_t *respQ, qurt_elite_queue_t *destQ, uint32_t sec_opcode,
      uint32_t client_token, bool_t wait_for_ack, Vtm_SubUnsubMsg_t *data_ptr)
{
   ADSPResult result = ADSP_EOK;
   uint32_t size = 0;
   elite_msg_any_t msg;
   EliteMsg_CustomVtSubUnsubHeaderType *payload_ptr;

   size = sizeof(EliteMsg_CustomVtSubUnsubHeaderType);
   result = elite_msg_create_msg( &msg,
                                  &size,
                                  ELITE_CUSTOM_MSG,
                                  respQ,
                                  client_token,
                                  ADSP_EOK);
   if( ADSP_FAILED( result))
   {
      MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"AFE PCIe driver : FAILED to create EliteMsg!! Not Sending Msg!!\n");
      // added return code to avoid crash incase of buffer run-out
      return result;
   }
   payload_ptr = (EliteMsg_CustomVtSubUnsubHeaderType *) msg.pPayload;
   payload_ptr->unSecOpCode = sec_opcode;
   payload_ptr->vtm_sub_unsub_payload_ptr = data_ptr;

   result = qurt_elite_queue_push_back(destQ, (uint64*)&msg);
   if (ADSP_FAILED(result))
   {
      MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"AFE PCIe driver: FAILED to send voice sub_unsub msg to voice timer!!\n");
      elite_msg_return_payload_buffer( &msg);
      return result;
   }

   if (wait_for_ack)
   {
      result = elite_svc_wait_for_ack(&msg);
   }

//   elite_msg_return_payload_buffer( &msg);

   return result;
}

ADSPResult afe_pcie_voice_set_rw_offsets(afe_dev_port_t* afe_port_ptr, elite_msg_any_t *pMsg)
{
  afe_pcie_dev_state_struct_t *p_dev_state = (afe_pcie_dev_state_struct_t *)afe_port_ptr->afe_drv;
  elite_msg_custom_afe_data_rw_offsets_t *vfr_data_rw_offset_ptr;
	uint64_t tx_data_path_delay = 0;
	
  if(NULL == p_dev_state)
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,
          "Failed to set pcie voice RW offsets for intf: 0x%x as driver handle is NULL", afe_port_ptr->intf);
    return ADSP_EFAILED;
  }
  vfr_data_rw_offset_ptr = (elite_msg_custom_afe_data_rw_offsets_t *)(pMsg->pPayload);
  

  afe_driver_pcie_get_data_path_delay(afe_port_ptr, &tx_data_path_delay);  
  afe_pcie_vfr_timing_t *vfr_timing_ptr = &(p_dev_state->afe_pcie_vfr_timing);
  vfr_timing_ptr->vfr_mode = vfr_data_rw_offset_ptr->vfr_mode;
  vfr_timing_ptr->is_new_offset_registered = TRUE;
  vfr_timing_ptr->vsid = vfr_data_rw_offset_ptr->vsid;
  vfr_timing_ptr->vfr_cycle_us = vfr_data_rw_offset_ptr->vfr_cycle_us;

	/* Account for IPA data path delay into the UL offsets. */
  if( vfr_data_rw_offset_ptr->ul_offset_1 >= tx_data_path_delay )
  {	    	  
  	vfr_timing_ptr->ul_offset_1 = vfr_data_rw_offset_ptr->ul_offset_1 - tx_data_path_delay;
  }
  else
  {
  	vfr_timing_ptr->ul_offset_1 = vfr_data_rw_offset_ptr->ul_offset_1 + vfr_data_rw_offset_ptr->vfr_cycle_us - tx_data_path_delay;
  }
  
  if( vfr_data_rw_offset_ptr->ul_offset_2 >= tx_data_path_delay)
  {
  	vfr_timing_ptr->ul_offset_2 = vfr_data_rw_offset_ptr->ul_offset_2 - tx_data_path_delay;
  }	
  else
  {
  	vfr_timing_ptr->ul_offset_2 = vfr_data_rw_offset_ptr->ul_offset_2 + vfr_data_rw_offset_ptr->vfr_cycle_us - tx_data_path_delay;
  }
  
  vfr_timing_ptr->dl_offset_1 = vfr_data_rw_offset_ptr->dl_offset_1;
  vfr_timing_ptr->dl_offset_2 = vfr_data_rw_offset_ptr->dl_offset_2;
  
  if ( AFE_PCIE_VFR_CYCLE_DURATION_40000_US == vfr_data_rw_offset_ptr->vfr_cycle_us )
  {
  	vfr_timing_ptr->dl_offset_2 = ( vfr_timing_ptr->dl_offset_1 + AFE_PCIE_VFR_CYCLE_DURATION_20000_US ) % AFE_PCIE_VFR_CYCLE_DURATION_40000_US;
  	vfr_timing_ptr->ul_offset_1 = ( vfr_timing_ptr->ul_offset_2 + AFE_PCIE_VFR_CYCLE_DURATION_20000_US ) % AFE_PCIE_VFR_CYCLE_DURATION_40000_US;  	
  }     
  vfr_timing_ptr->vtm_cmdq_ptr = qurt_elite_globalstate.pVoiceTimerCmdQ;
  if(TX_DIR == afe_port_ptr->dir)
  {
    vfr_timing_ptr->vtm_sub_1.client_id = AFE_TX_1;
    vfr_timing_ptr->vtm_sub_1.offset = vfr_timing_ptr->ul_offset_1;
    vfr_timing_ptr->vtm_sub_2.client_id = AFE_TX_2;
    vfr_timing_ptr->vtm_sub_2.offset = vfr_timing_ptr->ul_offset_2;
  }  
  else
  {
    vfr_timing_ptr->vtm_sub_1.client_id = AFE_RX_1;
    vfr_timing_ptr->vtm_sub_1.offset = vfr_timing_ptr->dl_offset_1;
    vfr_timing_ptr->vtm_sub_2.client_id = AFE_RX_2;
    vfr_timing_ptr->vtm_sub_2.offset = vfr_timing_ptr->dl_offset_2;      
  }  
  vfr_timing_ptr->vtm_sub_1.vfr_mode = vfr_timing_ptr->vfr_mode;
  vfr_timing_ptr->vtm_sub_1.vsid = vfr_timing_ptr->vsid;
  vfr_timing_ptr->vtm_sub_1.signal_enable = TRUE;
  vfr_timing_ptr->vtm_sub_1.timing_ver = 1;
  vfr_timing_ptr->vtm_sub_1.vfr_cycle = vfr_timing_ptr->vfr_cycle_us;

	/* vtm_sub_2 comes into the picture only for 40ms VFR cycle.  */
  vfr_timing_ptr->vtm_sub_2.vfr_mode = vfr_timing_ptr->vfr_mode;
  vfr_timing_ptr->vtm_sub_2.vsid = vfr_timing_ptr->vsid;
  vfr_timing_ptr->vtm_sub_2.signal_enable = TRUE;
  vfr_timing_ptr->vtm_sub_2.timing_ver = 1;
  vfr_timing_ptr->vtm_sub_2.vfr_cycle = vfr_timing_ptr->vfr_cycle_us;

  /* subscribe to voice timer only if VFR timer source is selected */
  if ( AFE_PCIE_AUDIO_TIMER_SOURCE_VFR == p_dev_state->afe_pcie_dev_cfg.timer_source )
  {
  	/* Unsubscribe before subcribing. */ 
  	afe_pcie_send_sub_unsub_msg_to_voicetimer(NULL, vfr_timing_ptr->vtm_cmdq_ptr, 
  																						VOICE_TIMER_UNSUBSCRIBE, NULL, FALSE, &(vfr_timing_ptr->vtm_sub_1));
    afe_pcie_send_sub_unsub_msg_to_voicetimer(NULL, vfr_timing_ptr->vtm_cmdq_ptr, 
  																							VOICE_TIMER_UNSUBSCRIBE, NULL, FALSE, &(vfr_timing_ptr->vtm_sub_2));	  																						
  	if( vfr_timing_ptr->vtm_sub_1.vfr_cycle )																					
  	{
  	  afe_pcie_send_sub_unsub_msg_to_voicetimer(NULL, vfr_timing_ptr->vtm_cmdq_ptr, 
  																						VOICE_TIMER_SUBSCRIBE, NULL, FALSE, &(vfr_timing_ptr->vtm_sub_1));
    }
	    																						
	if ( AFE_PCIE_VFR_CYCLE_DURATION_40000_US == vfr_timing_ptr->vfr_cycle_us )    																						
	{			
      if( vfr_timing_ptr->vtm_sub_2.vfr_cycle )																					
      {
			  afe_pcie_send_sub_unsub_msg_to_voicetimer(NULL, vfr_timing_ptr->vtm_cmdq_ptr, 
  																							VOICE_TIMER_SUBSCRIBE, NULL, FALSE, &(vfr_timing_ptr->vtm_sub_2));	
      }
	}    																						
  }			
  return ADSP_EOK;
}

/**
 * Perform PCIe port initialization 
 *
 * @param[in] afe_svc_ptr pointer for AFE static service 
 *  
 * @return  ADSP_EOK on success, an error code on error
 *  
 * @dependencies
 * None.
 *
 */
ADSPResult afe_pcie_port_init(aud_stat_afe_svc_t* afe_svc_ptr)
{
  ADSPResult                  result;
  uint16_t                    port_id;
  afe_dev_port                *afe_port_ptr = NULL;

  // Global initialization
  memset((char *) &afe_pcie_ports_global[0],0, sizeof(afe_pcie_ports_global));

  // initialize PCIe related ports
  for (port_id = AFE_PORT_ID_PCIE_RANGE_START; port_id <= AFE_PORT_ID_PCIE_RANGE_END; port_id++)
  {
    afe_port_ptr = &afe_pcie_ports_global[GET_PCIE_PORT_INDEX(port_id)];
    afe_svc_ptr->ports_pcie_ptr[GET_PCIE_PORT_INDEX(port_id)] = afe_port_ptr;

    if (ADSP_FAILED(result = afe_svc_init_port(afe_port_ptr, port_id, (port_id & AFE_PORT_DIR_MASK))))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Fail to init port: %d, aborting\n", port_id);
      return result;
    }

    if (IS_IT_TX_PORT_AFE_ID(afe_port_ptr->intf))
    {
      afe_port_ptr->afe_dev_process = (afe_dev_port_proc_func)afe_pcie_read;
    }
    else
    {
      afe_port_ptr->afe_dev_process = (afe_dev_port_proc_func)afe_pcie_write;
    }
  }

  return ADSP_EOK;
}

/**
  @brief Perform PCIe port de-initialization

  @param[in] afe_svc_ptr pointer for AFE static service

  @return  ADSP_EOK on success, an error code on error

 */
ADSPResult afe_pcie_port_deinit(aud_stat_afe_svc_t* afe_svc_ptr)
{
  uint16_t        port_id;

  // de-initialize PCIe related ports
  for (port_id = AFE_PORT_ID_PCIE_RANGE_START; port_id <= AFE_PORT_ID_PCIE_RANGE_END; port_id++)
  {
    afe_svc_deinit_port(afe_svc_ptr->ports_pcie_ptr[GET_PCIE_PORT_INDEX(port_id)]);
  }

  return ADSP_EOK;
}


/**
 * Perform one time initialization of the AFE PCIe driver
 *
 * @return  ADSP_EOK on success, an error code on faliure
 *
 * @dependencies
 * None.
 *
 */
ADSPResult afe_pcie_driver_init(void)
{

  g_pcie_driver_state.is_initialized = TRUE;

  return ADSP_EOK;
}

/**
 * Perform de-initialization of the AFE PCIe driver
 *
 * @return  ADSP_EOK on success, an error code on error
 *
 * @dependencies
 * None.
 *
 */
ADSPResult afe_pcie_driver_deinit(void)
{
  ADSPResult result = ADSP_EOK;
  g_pcie_driver_state.is_initialized = FALSE;

  return result;
}


/**
  @brief Perform configuration of PCIe device for the given
         configuration

  @param[in] afe_port_ptr pointer to AFE device port structure
  @param[in] p_cfg pointer to AFE port PCIe device config
        strcutre
  @param[in] cfg_payload_size config struct payload size
  @param[in] cfg_ver -> config version

  @return  ADSP_EOK on success, an error code on error

 */
ADSPResult afe_set_pcie_cfg (afe_dev_port_t* afe_port_ptr, int8_t *p_cfg, uint16_t cfg_payload_size, uint32_t param_id)
{
  ADSPResult result = ADSP_EOK;

  /* If this is the first set cfg for the interface, allocate the driver state */
  if(NULL == afe_port_ptr->afe_drv)
  {
    afe_pcie_dev_state_struct_t *dev_state_ptr = NULL;

    if(NULL == (dev_state_ptr = (afe_pcie_dev_state_struct_t *)qurt_elite_memory_malloc(
            sizeof(afe_pcie_dev_state_struct_t), QURT_ELITE_HEAP_DEFAULT)))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Failed, cannot allocate driver state memory for port: 0x%lx!", afe_port_ptr->intf);
      result = ADSP_ENOMEMORY;
      return result;
    }
    else
    {
      MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "PCIe driver alloc successfully at 0x%lx for port: 0x%lx!",
            dev_state_ptr, afe_port_ptr->intf);
    }

    // do the mem clean of the dev-state struct
    memset((char *) dev_state_ptr, 0, sizeof(afe_pcie_dev_state_struct_t));
    afe_port_ptr->afe_drv = (void *)dev_state_ptr;
  }

  afe_pcie_dev_state_struct_t *p_dev_state = (afe_pcie_dev_state_struct_t *)afe_port_ptr->afe_drv;
  afe_pcie_dev_cfg_info_t *cfg_ptr = &p_dev_state->afe_pcie_dev_cfg;

  switch(param_id)
  {
    case AFE_PARAM_ID_PCIE_AUDIO_CONFIG:
    {
      // choose the appropriate config version
      uint32_t cfg_ver = (uint32_t) * (p_cfg);
      if(cfg_ver > AFE_API_VERSION_PCIE_AUDIO_CONFIG)
      {
        cfg_ver = AFE_API_VERSION_PCIE_AUDIO_CONFIG;
      }

      cfg_ptr->cfg_version = cfg_ver;
      switch(cfg_ver)
      {
        case AFE_API_VERSION_PCIE_AUDIO_CONFIG:
        {
          afe_param_id_pcie_audio_cfg_v1_t *p_pcie_cfg = (afe_param_id_pcie_audio_cfg_v1_t *)p_cfg;
          if(cfg_payload_size < sizeof(afe_param_id_pcie_audio_cfg_v1_t))
          {
            MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "PCIe Config Fails, Bad Param");
            return ADSP_EBADPARAM;
          }

          MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "AFE PCIe port configuration for port 0x%x "
                "data_format %d", afe_port_ptr->intf, p_pcie_cfg->data_format);

          MSG_3(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "sample_rate %ld bit_width %d num_channels %d",
                p_pcie_cfg->sample_rate, p_pcie_cfg->bit_width, p_pcie_cfg->num_channels);

          if((AFE_BITS_PER_SAMPLE_16 != p_pcie_cfg->bit_width) &&
              (AFE_BITS_PER_SAMPLE_24 != p_pcie_cfg->bit_width) &&
              (AFE_BITS_PER_SAMPLE_32 != p_pcie_cfg->bit_width))
          {
            MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Un-supported bit_width: %d for port 0x%x", p_pcie_cfg->bit_width, afe_port_ptr->intf);
            return ADSP_EUNSUPPORTED;
          }

          if((p_pcie_cfg->num_channels < 1) || (p_pcie_cfg->num_channels > AFE_PORT_MAX_AUDIO_CHAN_CNT))
          {
            MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Un-supported num_channels: %d for port 0x%x", p_pcie_cfg->num_channels, afe_port_ptr->intf);
            return ADSP_EUNSUPPORTED;
          }

          if((AFE_PORT_SAMPLE_RATE_8K != p_pcie_cfg->sample_rate) &&
              (AFE_PORT_SAMPLE_RATE_16K != p_pcie_cfg->sample_rate) &&
              (AFE_PORT_SAMPLE_RATE_32K != p_pcie_cfg->sample_rate) &&
              (AFE_PORT_SAMPLE_RATE_48K != p_pcie_cfg->sample_rate) )
          {
            MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Un-supported sampling rate: %lu, for port: 0x%x", p_pcie_cfg->sample_rate, afe_port_ptr->intf);
            return ADSP_EUNSUPPORTED;
          }

          if((AFE_PCIE_AUDIO_DATA_FORMAT_LINEAR_PCM != p_pcie_cfg->data_format) &&
             (AFE_PCIE_AUDIO_DATA_FORMAT_COMPRESSED_UL_SCHEDULE_IN_DL != p_pcie_cfg->data_format))
          {
            MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Un-supported data_format: %lu, for port: 0x%x", p_pcie_cfg->data_format, afe_port_ptr->intf);
            return ADSP_EUNSUPPORTED;
          }

          /* Determining the qformat shift factor based on bit width. This shift factor is being used for 24bit and 32bit only*/
          if(AFE_BITS_PER_SAMPLE_24 == p_pcie_cfg->bit_width)
          {
            afe_port_ptr->q_format_shift_factor = QFORMAT_SHIFT_FACTOR;
          }
          else
          {
            afe_port_ptr->q_format_shift_factor = 0;
          }

          if( AFE_PCIE_AUDIO_TIMER_SOURCE_VFR != p_pcie_cfg->timer_source )
          {
            MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Un-supported frame_size: %lu, for port: 0x%x", p_pcie_cfg->frame_size, afe_port_ptr->intf);
            return ADSP_EUNSUPPORTED;
          }
					MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "frame_size: %lu, for port: 0x%x", p_pcie_cfg->frame_size, afe_port_ptr->intf);

          cfg_ptr->bit_width = p_pcie_cfg->bit_width;
          cfg_ptr->num_channels = p_pcie_cfg->num_channels;
          cfg_ptr->data_format = p_pcie_cfg->data_format;
          cfg_ptr->sample_rate = p_pcie_cfg->sample_rate;
          cfg_ptr->frame_size = p_pcie_cfg->frame_size;
          cfg_ptr->timer_source = p_pcie_cfg->timer_source;
        }
        break;

        default:
          MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "PCIe device Config Fails, Bad Param");
          return ADSP_EUNSUPPORTED;
      }

      cfg_ptr->bytes_per_channel = (cfg_ptr->bit_width > AFE_BITS_PER_SAMPLE_16) ? AFE_BYTES_PER_SAMPLE_FOUR : AFE_BYTES_PER_SAMPLE_TWO;
      p_dev_state->afe_port_ptr = afe_port_ptr;
      p_dev_state->resp = IPA_VOP_RESP_CB_ERR_CODE_MAX;

      // store the device state information in port structure for future needs
      afe_port_ptr->dev_data_type = AFE_UNCOMPRESSED_DATA_PORT;
      afe_port_ptr->dev_bit_width = cfg_ptr->bit_width;
      afe_port_ptr->dev_channels = cfg_ptr->num_channels;
      afe_port_ptr->dev_bytes_per_channel = cfg_ptr->bytes_per_channel;
      afe_port_ptr->dev_sample_rate = cfg_ptr->sample_rate;
      afe_port_ptr->int_samples_per_period = ((cfg_ptr->frame_size)/1000 * (cfg_ptr->sample_rate)/1000);
      afe_port_ptr->latency_mode = AFE_PORT_HIGH_LATENCY_MODE_20MS;

      //if applicable, overwrite the port media type with the device media type.
      //this is applicable for all the use cases where the port media type is not explicitly set by the HLOS client.
      afe_port_copy_media_type_dev_to_port(afe_port_ptr);

      afe_port_ptr->is_interleaved = TRUE;

      if (AFE_PCIE_AUDIO_TIMER_SOURCE_VFR == cfg_ptr->timer_source)
      {                 
	       p_dev_state->afe_pcie_vfr_timing.vtm_sub_1.signal_ptr = &(afe_port_ptr->dma_signal);
	       p_dev_state->afe_pcie_vfr_timing.vtm_sub_2.signal_ptr = &(afe_port_ptr->dma_signal);
	       if ( TRUE == p_dev_state->afe_pcie_vfr_timing.vtm_sub_1.signal_enable )
	       {
	       	 afe_pcie_send_sub_unsub_msg_to_voicetimer(NULL, p_dev_state->afe_pcie_vfr_timing.vtm_cmdq_ptr, 
	  																									VOICE_TIMER_UNSUBSCRIBE, NULL, FALSE, &(p_dev_state->afe_pcie_vfr_timing.vtm_sub_1));
	  			 afe_pcie_send_sub_unsub_msg_to_voicetimer(NULL, p_dev_state->afe_pcie_vfr_timing.vtm_cmdq_ptr, 
	  																									VOICE_TIMER_SUBSCRIBE, NULL, FALSE, &(p_dev_state->afe_pcie_vfr_timing.vtm_sub_1));
				 }  
	     	 if ( ( TRUE == p_dev_state->afe_pcie_vfr_timing.vtm_sub_2.signal_enable ) &&
	     	 			( AFE_PCIE_VFR_CYCLE_DURATION_40000_US == p_dev_state->afe_pcie_vfr_timing.vtm_sub_2.vfr_cycle ) )
	     	 {
	     	   afe_pcie_send_sub_unsub_msg_to_voicetimer(NULL, p_dev_state->afe_pcie_vfr_timing.vtm_cmdq_ptr, 
	  																									VOICE_TIMER_UNSUBSCRIBE, NULL, FALSE, &(p_dev_state->afe_pcie_vfr_timing.vtm_sub_2));
	     	 	 afe_pcie_send_sub_unsub_msg_to_voicetimer(NULL, p_dev_state->afe_pcie_vfr_timing.vtm_cmdq_ptr, 
	  																									VOICE_TIMER_SUBSCRIBE, NULL, FALSE, &(p_dev_state->afe_pcie_vfr_timing.vtm_sub_2));
	     	 }                
      }
    }
    break;
    default:
      MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "PCIE set device Config Fails, Bad Param");
      return ADSP_EUNSUPPORTED;
  }

  return ADSP_EOK;
}

ADSPResult afe_get_pcie_cfg (afe_dev_port_t *afe_port_ptr, int8_t *param_buf_ptr, uint32_t payload_size,
                             uint16_t *params_buffer_len_req_ptr, uint32_t param_id)
{
  /* If get is called without a set cfg, return error */
  if(NULL == afe_port_ptr->afe_drv)
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Failed PCIe device cfg not yet set for port: 0x%x", afe_port_ptr->intf);
    return ADSP_EFAILED;
  }

  afe_pcie_dev_state_struct_t *p_dev_state = (afe_pcie_dev_state_struct_t *)afe_port_ptr->afe_drv;

  switch(param_id)
  {
    case AFE_PARAM_ID_PCIE_AUDIO_CONFIG:
    {
      uint32_t cfg_ver = p_dev_state->afe_pcie_dev_cfg.cfg_version;
      switch(cfg_ver)
      {
        case AFE_API_VERSION_PCIE_AUDIO_CONFIG:
        {
          *params_buffer_len_req_ptr = sizeof(afe_param_id_pcie_audio_cfg_v1_t);
          if(*params_buffer_len_req_ptr > payload_size)
          {
            MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Invalid payload size: pcie device cfg required size = %d, given size = %lu",
                  *params_buffer_len_req_ptr, payload_size);
            return ADSP_ENOMEMORY;
          }
          afe_param_id_pcie_audio_cfg_v1_t *p_pcie_cfg = (afe_param_id_pcie_audio_cfg_v1_t *)param_buf_ptr;

          p_pcie_cfg->minor_version = p_dev_state->afe_pcie_dev_cfg.cfg_version;
          p_pcie_cfg->bit_width = p_dev_state->afe_pcie_dev_cfg.bit_width;
          p_pcie_cfg->data_format = p_dev_state->afe_pcie_dev_cfg.data_format;
          p_pcie_cfg->num_channels = p_dev_state->afe_pcie_dev_cfg.num_channels;
          p_pcie_cfg->sample_rate = p_dev_state->afe_pcie_dev_cfg.sample_rate;
          p_pcie_cfg->minor_version = p_dev_state->afe_pcie_dev_cfg.cfg_version;
          p_pcie_cfg->timer_source = p_dev_state->afe_pcie_dev_cfg.timer_source;
        }
        break;

        default:
        {
          MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "PCIe cfg Get Cmd Cfg fail: InCompatible cfg version: %ld, port_id: %d",
                cfg_ver, afe_port_ptr->intf);
          return ADSP_EBADPARAM;
        }
        break;
      }
    }
    break;
    default:
    {
      MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "PCIe cfg Get Cmd fail: unsupported param id: 0x%lX, port_id: %d",
            param_id, afe_port_ptr->intf);
      return ADSP_EBADPARAM;
    }
  }

  return ADSP_EOK;
}

/**
  @brief Open the configured PCIe device for data transfers

  @param[in] afe_port_ptr pointer to AFE device port structure

  @return  ADSP_EOK on success, an error code on error

 */
ADSPResult afe_pcie_open (afe_dev_port_t* afe_port_ptr)
{
  afe_pcie_dev_state_struct_t *p_dev_state = (afe_pcie_dev_state_struct_t *)afe_port_ptr->afe_drv;
	ipa_vop_data_resp_cb_func_type data_cb = afe_pcie_data_callback;
	ipa_vop_client_type_e client_type;
  if(NULL == p_dev_state)
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,
          "Failed to open pcie device for intf: 0x%x as driver handle is NULL", afe_port_ptr->intf);
    return ADSP_EFAILED;
  }
  if( TX_DIR == afe_port_ptr->dir )
  {
  	client_type = IPA_VOP_CLIENT_UL;
  }
  else
  {
  	client_type = IPA_VOP_CLIENT_DL;
  }
  /* Open the pcie driver and get the handle */
  if( IPA_VOP_RET_SUCCESS != ipa_vop_register( &p_dev_state->pcie_drv.pcie_driver_hdl, client_type,
  																							afe_port_ptr, data_cb ) )
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Failed to open pcie driver. direction %d", afe_port_ptr->dir);
    return ADSP_EFAILED;
  }

  /* Get avtimer and qtimer offset */
  /* IPA driver gives qtimer timestamp for data buffers. Qtimer timestamp need to be converted to AVtimer
   * Offset for AVtimer and Qtimer to convert Qtimer timestamp to AVtimer timestamp.
   */
  uint64_t avtimer_timestamp = 0, qtimer_timestamp = 0;

  if(ADSP_EOK != avtimer_drv_latch_avtimer_qtimer(afe_port_ptr->avt_drv, &avtimer_timestamp, &qtimer_timestamp))
  {
    MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Failed to latch avtimer and qtimer together");
    return ADSP_EFAILED;
  }
  MSG_5(MSG_SSID_QDSP6, DBG_ERROR_PRIO, " avtimer_timestamp 0x%lx%lx qtimer_timestamp 0x%lx%lx for port 0x%x",
        (uint32_t)(avtimer_timestamp >> 32), (uint32_t)avtimer_timestamp, (uint32_t)(qtimer_timestamp >> 32),
        (uint32_t)qtimer_timestamp, afe_port_ptr->intf);

  p_dev_state->pcie_drv.avtimer_qtimer_offset = avtimer_timestamp - qtimer_timestamp;

  afe_port_ptr->is_first_interrupt = TRUE;
  afe_port_ptr->is_interleaved = TRUE;

  return ADSP_EOK;
}

/**
 * Close the configured PCIe device. 
 *
 * @param[in] afe_port_ptr pointer to AFE device port structure
 *  
 * @return
 * ADSP_EOK on success, an error code on error 
 *  
 * @dependencies
 * None.
 *
 */
ADSPResult afe_pcie_close(afe_dev_port_t* afe_port_ptr)
{
  ADSPResult  result = ADSP_EOK;
  afe_pcie_dev_state_struct_t *p_dev_state = (afe_pcie_dev_state_struct_t *)afe_port_ptr->afe_drv;

  if(NULL == p_dev_state)
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,
          "Failed to close pcie device session for intf: 0x%x as driver handle is NULL", afe_port_ptr->intf);
    return ADSP_EFAILED;
  }

  if (NULL == p_dev_state->pcie_drv.pcie_driver_hdl)
  {
    MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "Invalid pcie driver handle, port_id: 0x%x", afe_port_ptr->intf);
    return ADSP_EOK;
  }
  /* unsubscribe from VTM */
  if (AFE_PCIE_AUDIO_TIMER_SOURCE_VFR == p_dev_state->afe_pcie_dev_cfg.timer_source)
  {
    p_dev_state->afe_pcie_vfr_timing.vtm_sub_1.signal_enable = FALSE;
    p_dev_state->afe_pcie_vfr_timing.vtm_sub_2.signal_enable = FALSE;
    afe_pcie_send_sub_unsub_msg_to_voicetimer(NULL, p_dev_state->afe_pcie_vfr_timing.vtm_cmdq_ptr, VOICE_TIMER_UNSUBSCRIBE, NULL, FALSE, &(p_dev_state->afe_pcie_vfr_timing.vtm_sub_1));
    if( AFE_PCIE_VFR_CYCLE_DURATION_40000_US == p_dev_state->afe_pcie_vfr_timing.vtm_sub_2.vfr_cycle )
    {
    	afe_pcie_send_sub_unsub_msg_to_voicetimer(NULL, p_dev_state->afe_pcie_vfr_timing.vtm_cmdq_ptr, VOICE_TIMER_UNSUBSCRIBE, NULL, FALSE, &(p_dev_state->afe_pcie_vfr_timing.vtm_sub_2));        
		}    	
  }
  /* close pcie device */
  if(IPA_VOP_RET_SUCCESS != ipa_vop_deregister(p_dev_state->pcie_drv.pcie_driver_hdl))
  {
    MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Failed to deregister with IPA");
    result |= ADSP_EFAILED;
  }
  p_dev_state->pcie_drv.pcie_driver_hdl = NULL;
  /* deallocate device handle */
  qurt_elite_memory_free(afe_port_ptr->afe_drv);
  afe_port_ptr->afe_drv = NULL;
  return result;
}

/**
 * Data is fetched from PCIe IPA Q6 driver to local 
 * buffer in case of Mic path (Tx path) 
 *
 * @param[in] afe_port_ptr pointer to AFE device port structure
 *  
 * @param[in] pBuffer - buffer to store the fetched data 
 *  
 * @param[in] numSamples - number of samples to be fetched
 *  
 * @return  ADSP_EOK on success, an error code on error 
 *  
 * @dependencies
 * None.
 *
 */
ADSPResult afe_pcie_read(afe_dev_port_t *afe_port_ptr, int16_t *pBuffer, uint32_t numSamples)
{
  ADSPResult result = ADSP_EOK;
  afe_pcie_dev_state_struct_t *p_dev_state = (afe_pcie_dev_state_struct_t *)afe_port_ptr->afe_drv;
  uint32_t num_bytes_to_read;
	uint64_t phy_addr = 0;
  ipa_vop_ret_code_e ipa_result = IPA_VOP_RET_SUCCESS;
  ipa_vop_repoll_param_e poll_param = IPA_VOP_PARAM_NO_REPOLL;
  num_bytes_to_read = numSamples * afe_port_ptr->bytes_per_channel * afe_port_ptr->channels;

#ifndef SIM
	phy_addr = qurt_lookup_physaddr_64((qurt_addr_t)pBuffer);
#else
	phy_addr = (qurt_addr_t)pBuffer;
#endif	
	if ( ( NULL == p_dev_state ) || (0 == phy_addr ) )
	{
		MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "afe_pcie_read: bad params: p_dev_state %d, phy_addr %d",
		    																			p_dev_state, phy_addr);
		return ADSP_EBADPARAM;
	}
	switch( p_dev_state->resp )
	{			
		case IPA_VOP_RESP_CB_STALE_DATA:
			/* Earlier fetch returned stale data, try repolling. */			
			poll_param = IPA_VOP_PARAM_REPOLL;
		/* Fall through. */	
		case IPA_VOP_RESP_CB_ERR_CODE_MAX:
		{
			p_dev_state->dma_counter++;
			if (IPA_VOP_RET_SUCCESS != (ipa_result = ipa_vop_ul_fetch(p_dev_state->pcie_drv.pcie_driver_hdl, (uint32_t)(phy_addr),
	                                                       				(uint32_t)(phy_addr>>32), num_bytes_to_read, poll_param ) ) )
		  {
		    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "afe_pcie_read:Failed to read data from pcie driver, ipa_vop_ul_fetch result %d",
		    																			ipa_result);
		    p_dev_state->resp = IPA_VOP_RESP_CB_ERR_CODE_MAX;		    
		  }	
		  /* Baling out after placing the fetch request. 
		   * Processing will start once the asynchronous data callback is received. */	
		  return ADSP_EFAILED;
		}
		break;
		case IPA_VOP_RESP_CB_COMPLETE:
		{			
			/* Received valid Tx data from IPA. Go ahead and process it. */	
			p_dev_state->resp = IPA_VOP_RESP_CB_ERR_CODE_MAX;
		}
		break;
 		case IPA_VOP_RESP_CB_NO_NEW_DATA:
		case IPA_VOP_RESP_CB_PCIE_LINK_IN_LPM:
		case IPA_VOP_RESP_CB_ERR_FAIL:
		default:
		{
			/* Error out. */
			MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "afe_pcie_read:Failed to read data from pcie driver, ipa response %d", p_dev_state->resp);
			p_dev_state->resp = IPA_VOP_RESP_CB_ERR_CODE_MAX;
			return ADSP_EFAILED;
		}
		break;		
	}	 

  /* Converting to Q27 for 24bit case */
  if(AFE_BITS_PER_SAMPLE_24 == p_dev_state->afe_pcie_dev_cfg.bit_width)
  {
    uint32_t samp, total_num_samp;
    int32_t *src_ptr_32, *dst_ptr_32;
    int64_t *src_ptr_64, *dst_ptr_64;


#ifdef __qdsp6__

    /* Calculate number of 32-bit samples */
    total_num_samp = (num_bytes_to_read >> 2);

    /* For Odd number of samples, copy one sample at a time */
    if(total_num_samp & 0x1)
    {
      src_ptr_32 = (int32_t *)pBuffer;
      dst_ptr_32 = (int32_t *)pBuffer;

      for(samp = total_num_samp; samp > 0; samp--)
      {
        (*dst_ptr_32++) = (*src_ptr_32++) >> QFORMAT_SHIFT_FACTOR;
      }
    }
    else
    {
      src_ptr_64 = (int64_t *)pBuffer; /* pBuffer points to 8 bytes aligned buffer  */
      dst_ptr_64 = (int64_t *)pBuffer; /* pBuffer points to 8 bytes aligned buffer  */

      /* Q31 to Q28 conversion
       */
      for(samp = total_num_samp; samp >= 2; samp -= 2)
      {
        (*dst_ptr_64++) = Q6_P_vasrw_PI(*src_ptr_64++, QFORMAT_SHIFT_FACTOR);
      }
    }

#else           /*------------ Non Q6 Version --------------------*/

    src_ptr_32 = (int32_t *)pBuffer;
    dst_ptr_32 = (int32_t *)pBuffer;

    for(samp = 0; samp < total_num_samp; samp++)
    {
      (*dst_ptr_32++) = (*src_ptr_32++) >> QFORMAT_SHIFT_FACTOR;
    }
#endif
  }

//  p_dev_state->pcie_drv.acc_avt_drift_us = read_data.acc_drift_us;
  return result;
}


/**
 * Device data will be writen to IPA Q6 PCIe driver from
 * local buffer in case of Speaker path (Rx path) 
 *
 * @param[in] afe_port_ptr pointer to AFE device port structure
 *  
 * @param[in] pBuffer - data buffer to be pushed into DMA buffer
 *  
 * @param[in] numSamples - number of samples to be copied
 *  
 * @return
 * ADSP_EOK in case of success, otherwise corresponding error 
 * code 
 *  
 * @dependencies
 * None.
 *
 */
ADSPResult afe_pcie_write(afe_dev_port_t *afe_port_ptr,  int16_t *pBuffer, uint32_t numSamples)
{
  ADSPResult result = ADSP_EOK;
  afe_pcie_dev_state_struct_t *p_dev_state = (afe_pcie_dev_state_struct_t *)afe_port_ptr->afe_drv;
  uint32_t num_bytes_to_write;
  ipa_vop_ret_code_e ipa_result = IPA_VOP_RET_SUCCESS;
  uint64_t phy_addr = 0;
	uint64_t last_vfr_ts = 0;
	int32_t drift_value_us = 0;
	uint8_t* temp_buffer = NULL;
	
  num_bytes_to_write = (numSamples * afe_port_ptr->channels * afe_port_ptr->bytes_per_channel);

	if ( NULL == p_dev_state )
	{
		return ADSP_EFAILED;
	}

  /* Converting from Q27 */
#if 0  
  if(AFE_BITS_PER_SAMPLE_24 == p_dev_state->afe_pcie_dev_cfg.bit_width)
  {
    uint32_t samp = 0, total_num_samp = (num_bytes_to_write >> 2);
    int32_t *src_ptr_32 = (int32_t *)pBuffer;
    int32_t *dst_ptr_32 = (int32_t *)pBuffer;

    for(samp = 0; samp < total_num_samp; samp++)
    {
      *dst_ptr_32++ = s32_shl_s32_sat(*src_ptr_32++, QFORMAT_SHIFT_FACTOR);
    }
  }
#endif

  if( AFE_PCIE_AUDIO_DATA_FORMAT_COMPRESSED_UL_SCHEDULE_IN_DL == p_dev_state->afe_pcie_dev_cfg.data_format )
  {  
	  // Update UL TS info.
		p_dev_state->ul_offset_info.sample_number++;
		p_dev_state->ul_offset_info.time_stamp = qurt_elite_fwk_get_time(afe_port_ptr->avt_drv);
		
		if( ( 0 == p_dev_state->ul_offset_info.ul_schedule_ts ) || 
				( 1 == p_dev_state->afe_pcie_vfr_timing.is_new_offset_registered ) )
		{
			last_vfr_ts = p_dev_state->afe_pcie_vfr_timing.vtm_sub_1.avtimer_timestamp_us;
			
			if( p_dev_state->afe_pcie_vfr_timing.ul_offset_1 > p_dev_state->afe_pcie_vfr_timing.dl_offset_1 )
			{
				p_dev_state->ul_offset_info.ul_schedule_ts = last_vfr_ts + p_dev_state->afe_pcie_vfr_timing.ul_offset_1;
			}
			else
			{
				p_dev_state->ul_offset_info.ul_schedule_ts = last_vfr_ts + p_dev_state->afe_pcie_vfr_timing.vfr_cycle_us 
																											+ p_dev_state->afe_pcie_vfr_timing.ul_offset_1;
			}
			p_dev_state->afe_pcie_vfr_timing.is_new_offset_registered = 0;
		}
		temp_buffer = (uint8_t*)pBuffer;
		temp_buffer -= sizeof(afe_pcie_dl_buf_with_ul_offset_header_t);  			
		
	  memscpy(temp_buffer ,sizeof(afe_pcie_dl_buf_with_ul_offset_header_t),
						&p_dev_state->ul_offset_info, sizeof(afe_pcie_dl_buf_with_ul_offset_header_t));
		pBuffer = (int16_t*)temp_buffer;				
		num_bytes_to_write += sizeof(afe_pcie_dl_buf_with_ul_offset_header_t);  						
	}

#ifndef SIM
	phy_addr = qurt_lookup_physaddr_64((qurt_addr_t)pBuffer);
#else
	phy_addr = (qurt_addr_t)pBuffer;
#endif
	
	if ( 0 == phy_addr )
	{
		MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "afe_pcie_write: bad params:  phy_addr %d", phy_addr);
		return ADSP_EBADPARAM;
	}

  if(IPA_VOP_RET_SUCCESS != (ipa_result = ipa_vop_dl_submit(p_dev_state->pcie_drv.pcie_driver_hdl, (uint32_t)(phy_addr),
                                                       (uint32_t)(phy_addr>>32),num_bytes_to_write )))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "afe_pcie_write: Failed to write data from pcie driver, ipa result %ld", ipa_result);
    result = ADSP_EFAILED;
  }
  MSG_3(MSG_SSID_QDSP6, DBG_MED_PRIO, "afe_pcie_write: sample num:%d, DL_TS:0x%16x, UL_TS:0x%16x ", 
	  p_dev_state->ul_offset_info.sample_number, p_dev_state->ul_offset_info.time_stamp, p_dev_state->ul_offset_info.ul_schedule_ts );
	p_dev_state->dma_counter++;

	/* Update drift info to IPA once it crosses the threshold. */
	drift_value_us = (int32_t) ( afe_port_ptr->drift_info[AVT_DRIFT_INFO_IDX].vfr_drift_info >> 32 );

	if( abs(drift_value_us) >= AFE_PCIE_VFR_DRIFT_THRESHOLD_US )
	{
		ipa_result = ipa_vop_time_sync( p_dev_state->pcie_drv.pcie_driver_hdl, drift_value_us );
		if( IPA_VOP_RET_SUCCESS != ipa_result )
		{
			MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "afe_pcie_write: ipa_vop_time_sync failed, ipa result %ld", ipa_result);
		}		
	}
  return result;
}

/**
 * Update drift for PCIe port.
 *
 * @param[in] pDevPort Pointer to the instance of the port.
 * @return
 * void pointer to the handle.
 *
 * @dependencies
 * None.
 */
ADSPResult afe_update_avt_drift_for_pcie_port(afe_dev_port_t *afe_port_ptr)
{
  ADSPResult result = ADSP_EOK;
  afe_pcie_dev_state_struct_t *p_dev_state = (afe_pcie_dev_state_struct_t *)afe_port_ptr->afe_drv;

  if ( AFE_PCIE_AUDIO_TIMER_SOURCE_VFR != p_dev_state->afe_pcie_dev_cfg.timer_source )      
  {
    afe_port_ptr->running_int_counter++;
    return result;
  }

  if(afe_port_ptr->is_first_dma)
  {
    /* If first DMA reset the AVT vs device drift */
    afe_drv_update_avt_drift_info_element(&(afe_port_ptr->drift_info[AVT_DRIFT_INFO_IDX].avt_drift_info), p_dev_state->pcie_drv.acc_avt_drift_us, TRUE);
  }
  else /* For subsequent DMA interrupts */
  {
    afe_drv_update_avt_drift_info_element(&(afe_port_ptr->drift_info[AVT_DRIFT_INFO_IDX].avt_drift_info), p_dev_state->pcie_drv.acc_avt_drift_us, FALSE);
  }

  return result;
}

/**
 * For providing the delay introduced in PCIe driver data
 * path delay
 *
 * @param[in] port_id port id of the PCIe device
 *@param[out] data_path_delay_us is the delay introduced due 
 *    to internal buffering of PCIe driver

 * @return  ADSP_EOK on success, an error code on error
 *
 * @dependencies
 * None.
 *
 */
ADSPResult afe_driver_pcie_get_data_path_delay(afe_dev_port_t *afe_port_ptr, uint64_t* data_path_delay_us)
{
  afe_pcie_dev_state_struct_t *p_dev_state = (afe_pcie_dev_state_struct_t *)afe_port_ptr->afe_drv;

  if(NULL != p_dev_state)
  {
    *data_path_delay_us = AFE_PCIE_DATA_PATH_DELAY_US;
  }
  else
  {
    *data_path_delay_us = 0;
  }
  return ADSP_EOK;
}

/**
 * For providing the header size required specific 
 * to the given port.
 *
 * @param[in] port_id  of the PCIe device
 * @param[out] Header size required for the port.

 * @return  ADSP_EOK on success, an error code on error
 *
 * @dependencies
 * None.
 *
 */
ADSPResult afe_driver_pcie_get_header_size(afe_dev_port_t *afe_port_ptr, uint32_t* header_size)
{
  afe_pcie_dev_state_struct_t *p_dev_state = (afe_pcie_dev_state_struct_t *)afe_port_ptr->afe_drv;

  if( (NULL != p_dev_state ) && 
		  (RX_DIR != afe_port_ptr->dir ) && 
  		( AFE_PCIE_AUDIO_DATA_FORMAT_COMPRESSED_UL_SCHEDULE_IN_DL == p_dev_state->afe_pcie_dev_cfg.data_format ) )
  {
    *header_size = sizeof(afe_pcie_dl_buf_with_ul_offset_header_t);
  }
  else
  {
    *header_size = 0;
  }
  return ADSP_EOK;
}

/**
 * For getting the timestamp for pcie audio device
 * @param[in] port_id port id of the PCIe device

 * @return  ADSP_EOK on success, an error code on error
 *
 * @dependencies
 * None.
 *
 */
ADSPResult afe_pcie_get_timestamp(afe_dev_port_t *afe_port_ptr)
{
  afe_pcie_dev_state_struct_t *p_dev_state = (afe_pcie_dev_state_struct_t *)afe_port_ptr->afe_drv;
	uint64_t qtimer_timestamp = 0;

	qtimer_timestamp = qurt_elite_fwk_get_time(afe_port_ptr->avt_drv);
  afe_port_ptr->port_av_timestamp = qtimer_timestamp + p_dev_state->pcie_drv.avtimer_qtimer_offset ;

  return ADSP_EOK;
}

/**
 * For restoring PCIe device configuration
 * @param[in] port_id port id of the PCIe device

 * @return  ADSP_EOK on success, an error code on error
 *
 * @dependencies
 * None.
 *
 */
ADSPResult afe_restore_pcie_cfg(afe_dev_port_t *afe_port_ptr)
{
  ADSPResult                    result = ADSP_EFAILED;
  afe_pcie_dev_state_struct_t    *p_dev_state = (afe_pcie_dev_state_struct_t *)afe_port_ptr->afe_drv;
  afe_param_id_pcie_audio_cfg_v1_t    pcie_cfg_info;

  if (NULL != p_dev_state)
  {
    pcie_cfg_info.minor_version = p_dev_state->afe_pcie_dev_cfg.cfg_version;
    pcie_cfg_info.bit_width = p_dev_state->afe_pcie_dev_cfg.bit_width;
    pcie_cfg_info.num_channels = p_dev_state->afe_pcie_dev_cfg.num_channels;
    pcie_cfg_info.sample_rate = p_dev_state->afe_pcie_dev_cfg.sample_rate;
    pcie_cfg_info.data_format = p_dev_state->afe_pcie_dev_cfg.data_format;
    pcie_cfg_info.frame_size = 0;
    pcie_cfg_info.timer_source = 0;

    if(ADSP_EOK != (result = afe_set_pcie_cfg(afe_port_ptr,
                                              (int8_t *)&pcie_cfg_info,
                                              sizeof(pcie_cfg_info),
                                              AFE_PARAM_ID_PCIE_AUDIO_CONFIG)))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Failed to restore pcie config, port_id: 0x%lx", afe_port_ptr->intf);

      result = ADSP_EFAILED;
    }
  }

  return result;
}
