/**
@file capi_v2_olm_utils.cpp

@brief This contains Utility  functions for CAPI V2 Off Loaded Module

 */

/*========================================================================
$Header: //components/rel/avs.adsp/2.8/avcs/modules/olm/capi_v2_olm/src/capi_v2_olm_utils.cpp#8 $

Edit History

when         who         what, where, why
--------     ---         -------------------------------------------------------
11/13/2017   bvodapal    Initial version (set/get property implementation from capi_v2_olm )
==========================================================================*/

/*-----------------------------------------------------------------------
Copyright (c) 2017-2018 Qualcomm Technologies, Inc.  All Rights Reserved.
Confidential and Proprietary - Qualcomm Technologies, Inc.
-----------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "capi_v2_olm.h"
#include "capi_v2_olm_internal.h"
#include "EliteAprIf.h"
#include "aprv2_api_inline.h"
#include "ap_server_api.h"
#include "olm_utils.h"
#include "EliteMsg.h"


capi_v2_err_t capi_v2_olm_set_input_media_format(capi_v2_olm_t *me_ptr, capi_v2_olm_media_fmt_t *media_payload_ptr,
                                                 uint32_t payload_size, uint32_t port_index);
/*----------------------------------------------------------------------------
 * Function Definitions
 * -------------------------------------------------------------------------*/

static bool_t capi_v2_olm_is_equal_media_format(const capi_v2_standard_data_format_v2_t *prev_mf,
		const capi_v2_standard_data_format_v2_t *new_mf)
{
    bool_t is_equal = TRUE;

    is_equal = is_equal && (prev_mf->bits_per_sample == new_mf->bits_per_sample);
    is_equal = is_equal && (prev_mf->bitstream_format == new_mf->bitstream_format);
    is_equal = is_equal && (prev_mf->data_interleaving == new_mf->data_interleaving);
    is_equal = is_equal && (prev_mf->data_is_signed == new_mf->data_is_signed);
    is_equal = is_equal && (prev_mf->num_channels == new_mf->num_channels);
    is_equal = is_equal && (prev_mf->q_factor == new_mf->q_factor);
    is_equal = is_equal && (prev_mf->sampling_rate == new_mf->sampling_rate);

    if (is_equal)
    {
        for (uint32_t i = 0; i < prev_mf->num_channels; i++)
        {
            is_equal = is_equal && (prev_mf->channel_type[i] == new_mf->channel_type[i]);
        }
    }

    return is_equal;
}


bool_t capi_v2_olm_is_supported_media_type(capi_v2_olm_t *me_ptr,
												  capi_v2_data_format_header_t    *data_format_header,
												  capi_v2_standard_data_format_v2_t *pStd)
{
    if (CAPI_V2_FIXED_POINT != data_format_header->data_format)
    {
        MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: unsupported data format %lu",
        		me_ptr->capi_v2_olm_identifier,(uint32_t)data_format_header->data_format);
        return FALSE;
    }

    if ( (16 != pStd->bits_per_sample) && (32 != pStd->bits_per_sample) )
    {
        MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: PP modules only supports 16 and 32 bit data. Received %lu.",
        		me_ptr->capi_v2_olm_identifier,pStd->bits_per_sample);
        return FALSE;
    }

    if (CAPI_V2_DEINTERLEAVED_UNPACKED != pStd->data_interleaving)
    {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Unsupported data interleaved format.",
        		me_ptr->capi_v2_olm_identifier);
        return FALSE;
    }

    if (!pStd->data_is_signed)
    {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Unsigned data not supported.",
        		me_ptr->capi_v2_olm_identifier);
        return FALSE;
    }

    if(!((pStd->num_channels >= 1) && (pStd->num_channels <= CAPI_V2_MAX_CHANNELS_V2)))
    {
    	MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Only upto %lu channels supported. Received %lu.",
    			me_ptr->capi_v2_olm_identifier,CAPI_V2_MAX_CHANNELS_V2, pStd->num_channels);
    	return FALSE;
    }

    if(!((pStd->sampling_rate >= 1) && (pStd->sampling_rate <= OLM_MAX_SAMPLE_RATE)))
    {
    	MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Invalid Sample Rate input. Received %lu.",
    			me_ptr->capi_v2_olm_identifier, pStd->sampling_rate);
    	return FALSE;
    }
    return TRUE;
}


/**
 * This function is used to set the input media format to the OLM CAPI
 *
 * @param[in] me_ptr, pointer to the CAPI lib
 * @param[in] media_payload_ptr, pointer to the media format information.
 * @param[in] payload_size, size of the payload
 * @param[in] port_index, input port index for which media format is recvd
 *
 * @return capi_v2_err_t, result code
 */
capi_v2_err_t capi_v2_olm_set_input_media_format(capi_v2_olm_t *me_ptr, capi_v2_olm_media_fmt_t *media_payload_ptr,
                                                 uint32_t payload_size, uint32_t port_index)
{
  ADSPResult result = ADSP_EOK;
  capi_v2_err_t capi_v2_result = CAPI_V2_EOK;

  /* push input media format command to remote proc */
  capi_v2_set_get_media_format_t    *pFmt;
  capi_v2_standard_data_format_v2_t *pStd;

  pFmt = (capi_v2_set_get_media_format_t *)media_payload_ptr;
  pStd = (capi_v2_standard_data_format_v2_t *) (( (uint8_t *) media_payload_ptr + sizeof(capi_v2_set_get_media_format_t)));

#ifdef OLM_LATENCY_MEASUREMENT
  MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: received input MF at time %lld", me_ptr->capi_v2_olm_identifier,qurt_elite_timer_get_time());
#endif

#ifdef CAPI_V2_OLM_DEBUG
  MSG_2(MSG_SSID_QDSP6, DBG_MED_PRIO, "CAPIv2 OLM 0x%8lX: Input MF = 0x%x, ",me_ptr->capi_v2_olm_identifier, me_ptr->is_input_mf_rcvd_mask);
#endif

  if(port_index == OLM_PRIMARY_INPUT_PORT)
  {
	  if(!capi_v2_olm_is_supported_media_type(me_ptr, &pFmt->format_header, pStd ))
		  return CAPI_V2_EFAILED;

	  if((capi_v2_olm_is_equal_media_format(&me_ptr->in_media_fmt[OLM_PRIMARY_INPUT_PORT].f , pStd))
			  &&(me_ptr->olm_event_cfg.enable))
		  return CAPI_V2_EOK;
  }

  /* For multi- input port case in OLM, check that the sampling rate
	   & bit width values match the primary port. This is derived keeping
	   EC implementation in mind */
  if(port_index != OLM_PRIMARY_INPUT_PORT)
  {
    capi_v2_olm_media_fmt_t *primary_fmt_ptr = &me_ptr->in_media_fmt[OLM_PRIMARY_INPUT_PORT];
    if((primary_fmt_ptr->f.sampling_rate != pStd->sampling_rate) ||
        (primary_fmt_ptr->f.bits_per_sample != pStd->bits_per_sample))
    {
      MSG_7(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Received mismatched values for media format for"
            "port_index = 0x%x compared with primary port_index = 0x%x "
            "Expected (primary) sampling_rate = %d, bit_width = %d "
            "Received (port_id) sampling_rate = %d, bit_width = %d",
            me_ptr->capi_v2_olm_identifier, port_index, OLM_PRIMARY_INPUT_PORT, primary_fmt_ptr->f.sampling_rate,
            primary_fmt_ptr->f.bits_per_sample, pStd->sampling_rate, pStd->bits_per_sample);
      return CAPI_V2_EFAILED;
    }
  }

  /* Send temporary write buffers to remote */
  if(NULL != me_ptr->tmp_wr_data_buf_ptr[port_index])
  {
    result = olm_send_temp_wr_buffer(me_ptr, port_index);
    if(ADSP_FAILED(result))
    {
      MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Failed to send temp "
                  "Write buffer for port_index %d with result 0x%x",me_ptr->capi_v2_olm_identifier, port_index, result);
    }
  }

  /* Send input media format to the remote processor */
  result = olm_send_media_fmt(me_ptr, pFmt, pStd, port_index );
  if(ADSP_FAILED(result))
  {
    MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Failed to send "
          "input media format for port_index %d with result = 0x%x",me_ptr->capi_v2_olm_identifier, port_index, result);
    CAPI_V2_SET_ERROR(capi_v2_result, CAPI_V2_EBADPARAM);
    return capi_v2_result;
  }

  /* cache the media format */
  memscpy(&me_ptr->in_media_fmt[port_index],
          sizeof(capi_v2_olm_media_fmt_t),
          media_payload_ptr,
          payload_size);

  if(FALSE == me_ptr->is_olm_instance_created)
  {
	  /* Allocate Write rsp data Q, read rsp Data Q */
	  for(uint32_t input_port_index =0; input_port_index < me_ptr->num_active_input_ports; input_port_index++)
	  {
		  if(ADSP_EOK != (result = olm_create_queues(me_ptr, WRITE_CMD, input_port_index)))
		  {
			  MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: create write "
					  "queue failed for port_index = %d with result 0x%x",
					  me_ptr->capi_v2_olm_identifier, input_port_index, result);
			  CAPI_V2_SET_ERROR(capi_v2_result, CAPI_V2_EFAILED);
			  return capi_v2_result;
		  }
	  }

	  /* Allocate Write rsp data Q, read rsp Data Q */
	  if(ADSP_EOK != (result = olm_create_queues(me_ptr, READ_CMD, 0)))
	  {
		  MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: create read "
				  "queue failed for port_index = %d with result 0x%x",
				  me_ptr->capi_v2_olm_identifier, port_index, result);
		  CAPI_V2_SET_ERROR(capi_v2_result, CAPI_V2_EFAILED);
		  return capi_v2_result;
	  }
  }

  /* Allocate write buffers for data communication with Remote proc */
  /* This is the place where the buffers are created for secondary port */
  if(me_ptr->is_olm_instance_created)
  {
	  if(ADSP_EOK != (result = olm_alloc_write_data_buffers(me_ptr, port_index)))
	  {
		  MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Failed to allocate "
				  "write buffers during input media fmt for port_index = %d with result 0x%x",
				  me_ptr->capi_v2_olm_identifier, port_index, result);
		  CAPI_V2_SET_ERROR(capi_v2_result, CAPI_V2_ENOMEMORY);
		  return capi_v2_result;
	  }
  }

  olm_set_reset_bitmask(&me_ptr->is_input_mf_rcvd_mask, port_index, TRUE);

  /* Wait for output media format if OLM is not in run state */
  if(FALSE == me_ptr->is_olm_instance_created)
  {
    /* Check if media format is set on the Primary Port */
    bool_t wait_for_out_media_fmt = TRUE;
   
    /* Check if the media format is set on the given port or not*/
    if(0 == me_ptr->in_media_fmt[OLM_PRIMARY_INPUT_PORT].f.num_channels)
    {
	  wait_for_out_media_fmt = FALSE;
    }
	
    if(TRUE == wait_for_out_media_fmt)
    {
      uint32_t output_port_index = 0;
      uint32_t ch_status = 0;
      ch_status = qurt_elite_channel_wait(me_ptr->rd_done_channel_ptr[output_port_index], RD_CHAN_BIT_MASK);

      /* get media format and allocate read buffers */
      elite_msg_any_t msg;

      /* pop from read data Q */
      result = qurt_elite_queue_pop_front(me_ptr->rd_rsp_q_ptr[output_port_index], (uint64_t*) &msg);
      if (ADSP_EOK != result)
      {
        //Error case. We should have atleast one read buffer at this point.
        QURT_ELITE_ASSERT(0); // crash during bring up
        CAPI_V2_SET_ERROR(capi_v2_result, CAPI_V2_EFAILED);
        olm_set_reset_bitmask(&me_ptr->is_input_mf_rcvd_mask, port_index, FALSE);
        return capi_v2_result;
      }
      elite_apr_packet_t *mf_apr_pkt_ptr = (elite_apr_packet_t *)msg.pPayload;

      uint32_t opcode     = elite_apr_if_get_opcode(mf_apr_pkt_ptr);

      /*  Checking if it is output media format event or not */
      if(AP_CMD_EVENT == opcode)
      {
        /*
         * Pass the packet Payload to the event handler.
         * This custom event is usually OUTPUT_MEDIA_FORMAT_CHANGE or NUM UNIT FRAMES change event only.
         */
    	  result = olm_event_handler(me_ptr, mf_apr_pkt_ptr);
        elite_apr_if_free(me_ptr->apr_handle, mf_apr_pkt_ptr);
        if(result!=ADSP_EOK)
        {
        	olm_handle_disable_sequence(me_ptr, TRUE);
        	CAPI_V2_SET_ERROR(capi_v2_result, CAPI_V2_EFAILED);
        	return capi_v2_result;
        }
      }
      else
      {
        MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: received non event command %ld", me_ptr->capi_v2_olm_identifier, opcode );
        elite_apr_if_free(me_ptr->apr_handle, mf_apr_pkt_ptr);
        CAPI_V2_SET_ERROR(capi_v2_result, CAPI_V2_EFAILED);
        olm_set_reset_bitmask(&me_ptr->is_input_mf_rcvd_mask, port_index, FALSE);
        return capi_v2_result;
      }
    }
  }
#ifdef CAPI_V2_OLM_DEBUG
  MSG_1(MSG_SSID_QDSP6, DBG_MED_PRIO, "CAPIv2 OLM 0x%8lX: Input MF end = 0x%x, ",me_ptr->capi_v2_olm_identifier, me_ptr->is_input_mf_rcvd_mask);
#endif
  return capi_v2_result;
}

/**
 * This function is used to raise the KPPS event for the OFF load module.
 *
 * @param[in] me_ptr, pointer to the CAPI lib.
 *
 * @return none
 */
void capi_v2_olm_update_raise_kpps_event(capi_v2_olm_t *me_ptr)
{
  uint32_t default_kpps = OLM_KPPS_REQ;

  if(default_kpps != me_ptr->olm_event_cfg.kpps)
  {
    capi_v2_err_t  capi_v2_result = CAPI_V2_EOK;
    capi_v2_event_KPPS_t event;
    capi_v2_event_info_t event_info;

    me_ptr->olm_event_cfg.kpps = default_kpps;

    event.KPPS                         = me_ptr->olm_event_cfg.kpps;
    event_info.port_info.is_valid      = false;
    event_info.payload.actual_data_len = sizeof(event);
    event_info.payload.max_data_len    = sizeof(event);
    event_info.payload.data_ptr        = reinterpret_cast<int8_t*>(&event);

    capi_v2_result = me_ptr->event_callback_info.event_cb(me_ptr->event_callback_info.event_context,
                                                          CAPI_V2_EVENT_KPPS, &event_info);

    if (CAPI_V2_FAILED(capi_v2_result))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Failed to send KPPS event.",
                                            me_ptr->capi_v2_olm_identifier);
    }
#ifdef CAPI_V2_OLM_DEBUG
    else
    {
      MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"CAPIv2 OLM 0x%8lX: Event raised. KPPS %lu",
                                            me_ptr->capi_v2_olm_identifier, me_ptr->olm_event_cfg.kpps);
    }
#endif
  }

}

/**
 * This function is used to raise the BW event for the OFF load module.
 *
 * @param[in] me_ptr, pointer to the CAPI lib.
 *
 * @return none
 */
void capi_v2_olm_update_raise_bw_event(capi_v2_olm_t *me_ptr)
{
  uint32_t default_bw = OLM_BW_REQ;

  if(default_bw != me_ptr->olm_event_cfg.bw)
  {
    capi_v2_err_t  capi_v2_result = CAPI_V2_EOK;
    capi_v2_event_bandwidth_t event;
    capi_v2_event_info_t event_info;

    me_ptr->olm_event_cfg.bw = default_bw;

    event.code_bandwidth               = 0;
    event.data_bandwidth               = me_ptr->olm_event_cfg.bw;
    event_info.port_info.is_valid      = false;
    event_info.payload.actual_data_len = sizeof(event);
    event_info.payload.max_data_len    = sizeof(event);
    event_info.payload.data_ptr        = reinterpret_cast<int8_t*>(&event);

    capi_v2_result = me_ptr->event_callback_info.event_cb(me_ptr->event_callback_info.event_context,
                                                          CAPI_V2_EVENT_BANDWIDTH, &event_info);

    if (CAPI_V2_FAILED(capi_v2_result))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Failed to send BW event.",
                                             me_ptr->capi_v2_olm_identifier);
    }
#ifdef CAPI_V2_OLM_DEBUG
    else
    {
      MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"CAPIv2 OLM 0x%8lX: Event raised. BW %lu",
                                           me_ptr->capi_v2_olm_identifier, me_ptr->olm_event_cfg.bw);
    }
#endif
  }

}

/**
 * This function is used to raise the process event for the OFF load module.
 *
 * @param[in] me_ptr, pointer to the CAPI lib.
 *
 * @return none
 */
void capi_v2_olm_update_raise_process_event(capi_v2_olm_t *me_ptr)
{

  capi_v2_err_t  capi_v2_result = CAPI_V2_EOK;
  capi_v2_event_process_state_t event;
  capi_v2_event_info_t          event_info;

  event.is_enabled                   = (0 == me_ptr->olm_event_cfg.enable)? 0 : 1;
  event_info.port_info.is_valid      = false;
  event_info.payload.actual_data_len = sizeof(event);
  event_info.payload.max_data_len    = sizeof(event);
  event_info.payload.data_ptr        = reinterpret_cast<int8_t*>(&event);

  capi_v2_result = me_ptr->event_callback_info.event_cb(me_ptr->event_callback_info.event_context,
                                                        CAPI_V2_EVENT_PROCESS_STATE, &event_info);

  if (CAPI_V2_FAILED(capi_v2_result))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Failed to send process state event.",
                                          me_ptr->capi_v2_olm_identifier);
  }
#ifdef CAPI_V2_OLM_DEBUG
  else
  {
    MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"CAPIv2 OLM 0x%8lX: Process state event raised. is_enabled %lu",
                                         me_ptr->capi_v2_olm_identifier, me_ptr->olm_event_cfg.enable);
  }
#endif


}

/**
 * This function is used to raise the delay event for the OFF load module.
 *
 * @param[in] me_ptr, pointer to the CAPI lib.
 *
 * @return none
 */
void capi_v2_olm_update_raise_delay_event(capi_v2_olm_t *me_ptr)
{

  uint32_t cur_delay_in_us = (me_ptr->remote_delay_in_us) + (me_ptr->read_buf_delay_in_us) + (me_ptr->write_buf_delay_in_us);

  /* Raise algorithmic delay event to Dynamic service */
  if(cur_delay_in_us != me_ptr->olm_event_cfg.delay)
  {
    capi_v2_err_t  capi_v2_result = CAPI_V2_EOK;

    capi_v2_event_info_t              event_info;
    capi_v2_event_algorithmic_delay_t algo_delay_info;

    algo_delay_info.delay_in_us = cur_delay_in_us;
    me_ptr->olm_event_cfg.delay = cur_delay_in_us;

    event_info.port_info.is_valid      = TRUE;
    event_info.port_info.is_input_port = FALSE;
    event_info.port_info.port_index    = 0;
    event_info.payload.actual_data_len = event_info.payload.max_data_len = sizeof(algo_delay_info);
    event_info.payload.data_ptr        = reinterpret_cast<int8_t*>(&algo_delay_info);

    capi_v2_result = me_ptr->event_callback_info.event_cb(me_ptr->event_callback_info.event_context,
                                                          CAPI_V2_EVENT_ALGORITHMIC_DELAY, &event_info );

    if (CAPI_V2_FAILED(capi_v2_result))
    {
      MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Failed to send delay event with result 0x5x", me_ptr->capi_v2_olm_identifier, capi_v2_result);
    }
#ifdef CAPI_V2_OLM_DEBUG
    else
    {
      MSG_3(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"CAPIv2 OLM 0x%8lX: Delay event raised with Remote Delay %lu OLM Read Buffer Delay %lu"
            " OLM Write Buffer Delay %lu ", me_ptr->capi_v2_olm_identifier, me_ptr->remote_delay_in_us,me_ptr->read_buf_delay_in_us,
            me_ptr->write_buf_delay_in_us) );
    }
#endif
  }

}

/**
 * This function is used set properties of the CAPI for the OFF load module.
 *
 * @param[in] me_ptr, pointer to the CAPI lib.
 * @param[in] props_ptr, pointer to the prop list that needs to be set.
 *
 * @return capi_v2_err_t, result code
 */
capi_v2_err_t capi_v2_olm_process_set_properties(capi_v2_olm_t *me_ptr, capi_v2_proplist_t *props_ptr)
{
  ADSPResult result = ADSP_EOK;
  capi_v2_err_t capi_v2_result = CAPI_V2_EOK;
  capi_v2_prop_t *prop_ptr = props_ptr->prop_ptr;

  if(!prop_ptr)
  {
    MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM: Set properties received bad pointer in prop_list");
    return CAPI_V2_EFAILED;
  }

  for(uint32_t i = 0; i < props_ptr->props_num; i++)
  {
    capi_v2_buf_t *payload = &prop_ptr[i].payload;
#ifdef OLM_LATENCY_MEASUREMENT
    MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: received property 0x%x at time %lld", me_ptr->capi_v2_olm_identifier,prop_ptr[i].id, qurt_elite_timer_get_time());
#endif

    switch((uint32_t) prop_ptr[i].id)
    {
      case CAPI_V2_ALGORITHMIC_RESET:
      {
        /*
         * Clear the local buffers in OLM.         */

        capi_v2_err_t local_result = CAPI_V2_EOK;
        MSG_1(MSG_SSID_QDSP6, DBG_MED_PRIO,"CAPIv2 OLM 0x%8lX: Received algo reset",
              me_ptr->capi_v2_olm_identifier);

        local_result = capiv2_olm_reset(me_ptr);
        if(CAPI_V2_FAILED(local_result))
        {
          MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: failed in algo reset with error 0x%x ",
                me_ptr->capi_v2_olm_identifier, local_result);
          CAPI_V2_SET_ERROR(capi_v2_result, local_result);
        }

        break;
      }

      case CAPI_V2_EVENT_CALLBACK_INFO:
      {
        if(payload->actual_data_len >= sizeof(capi_v2_event_callback_info_t))
        {
          capi_v2_event_callback_info_t *data_ptr = (capi_v2_event_callback_info_t *)payload->data_ptr;
          if(NULL == data_ptr)
          {
            MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "CAPIv2 OLM 0x%8lX: NULL event callback ptr (%p)", me_ptr->capi_v2_olm_identifier, data_ptr);
            CAPI_V2_SET_ERROR(capi_v2_result, CAPI_V2_EBADPARAM);
            break;
          }

          (void)memscpy(&me_ptr->event_callback_info,
                        sizeof(capi_v2_event_callback_info_t),
                        data_ptr,
                        payload->actual_data_len);

          MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "CAPIv2 OLM 0x%8lX: Set Property id "
              "CAPI_V2_EVENT_CALLBACK_INFO is done", me_ptr->capi_v2_olm_identifier);
        }
        else
        {
          MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO,
                "CAPIv2 OLM 0x%8lX: Failed in Set Property id 0x%lx (CAPI_V2_EVENT_CALLBACK_INFO) "
                "Bad param size %lu", me_ptr->capi_v2_olm_identifier, (uint32_t)prop_ptr[i].id, payload->actual_data_len);
          CAPI_V2_SET_ERROR(capi_v2_result, CAPI_V2_ENEEDMORE);
        }
        break;
      }

      case CAPI_V2_PORT_NUM_INFO :
      {
        if(payload->actual_data_len >= sizeof(capi_v2_port_num_info_t))
        {
          capi_v2_port_num_info_t *num_port_info = (capi_v2_port_num_info_t *)payload->data_ptr;

          if((num_port_info->num_input_ports > OLM_MAX_INPUT_PORTS) ||
              (num_port_info->num_output_ports > OLM_MAX_OUTPUT_PORTS))
          {
            MSG_3(MSG_SSID_QDSP6,DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Failed to Set Property id "
                  " (CAPI_V2_PORT_NUM_INFO), received unsupported "
                  "port configuration - input ports (%lu) or output ports (%lu)",
                  me_ptr->capi_v2_olm_identifier, num_port_info->num_input_ports,num_port_info->num_output_ports);
            CAPI_V2_SET_ERROR(result,CAPI_V2_EBADPARAM);
            break;
          }
          me_ptr->num_active_input_ports = num_port_info->num_input_ports;
          me_ptr->num_active_output_ports = num_port_info->num_output_ports;

          MSG_1(MSG_SSID_QDSP6, DBG_MED_PRIO, "CAPIv2 OLM 0x%8lX: received valid port info ",me_ptr->capi_v2_olm_identifier);
        }
        else
        {
          MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Failed in Set Property "
                "id 0x%lx (CAPI_V2_PORT_NUM_INFO) Bad param size %lu",
                me_ptr->capi_v2_olm_identifier, (uint32_t)prop_ptr[i].id, payload->actual_data_len);
          CAPI_V2_SET_ERROR(capi_v2_result, CAPI_V2_ENEEDMORE);
          break;
        }
        break;
      }

      case CAPI_V2_HEAP_ID:
      {
        if(payload->actual_data_len >= sizeof(capi_v2_heap_id_t))
        {
          capi_v2_heap_id_t *data_ptr = (capi_v2_heap_id_t *)payload->data_ptr;
          if(NULL == data_ptr)
          {
            MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Failed in Set Property "
                  "id CAPI_V2_HEAP_ID - NULL data ptr (%p)",me_ptr->capi_v2_olm_identifier, data_ptr);
            CAPI_V2_SET_ERROR(capi_v2_result, CAPI_V2_EBADPARAM);
            break;
          }

          /*copy the head id from the input property value*/
          me_ptr->heap_id = (QURT_ELITE_HEAP_ID)data_ptr->heap_id;
          MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "CAPIv2 OLM 0x%8lX: received property id CAPI_V2_HEAP_ID ",
                                                me_ptr->capi_v2_olm_identifier);

        }
        else
        {
          MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Failed in Set Property "
                "id 0x%lx (CAPI_V2_HEAP_ID) Bad param size %lu",
                me_ptr->capi_v2_olm_identifier, (uint32_t)prop_ptr[i].id, payload->actual_data_len);
          CAPI_V2_SET_ERROR(capi_v2_result, CAPI_V2_ENEEDMORE);
          break;
        }
        break;
      }

      case CAPI_V2_INPUT_MEDIA_FORMAT_V2:
      {
        capi_v2_port_info_t *port_info_ptr =  &(prop_ptr[i].port_info);

        /* Get the port index for the given property */
        uint32_t port_index = port_info_ptr->port_index;

        if(!( port_info_ptr->is_valid &&
            port_index < me_ptr->num_active_input_ports &&
            TRUE == port_info_ptr->is_input_port ) )
        {
          MSG_2(MSG_SSID_QDSP6, DBG_MED_PRIO, "CAPIv2 OLM 0x%8lX: Input Media Format set with "
                "invalid port information - port_index = 0x%lx",me_ptr->capi_v2_olm_identifier, port_index);
          CAPI_V2_SET_ERROR(capi_v2_result, CAPI_V2_EBADPARAM);
          break;
        }

        if (payload->actual_data_len >= sizeof(capi_v2_olm_base_media_fmt_t))
        {
          capi_v2_olm_media_fmt_t *input_media_fmt_payload = (capi_v2_olm_media_fmt_t *)payload->data_ptr;
          uint32_t num_channel = input_media_fmt_payload->f.num_channels;
          uint32_t required_mediaformat_payload_size = sizeof(capi_v2_olm_base_media_fmt_t) + num_channel * sizeof(capi_v2_channel_type_t);

          if(payload->actual_data_len >= required_mediaformat_payload_size)
          {
            capi_v2_result = capi_v2_olm_set_input_media_format(me_ptr, input_media_fmt_payload, payload->actual_data_len,  port_index);
            if(CAPI_V2_FAILED(capi_v2_result))
            {
              MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Failed to Set "
                    "Input Media format for port_index = %d", me_ptr->capi_v2_olm_identifier, port_index);
              CAPI_V2_SET_ERROR(capi_v2_result, CAPI_V2_ENEEDMORE);
              break;
            }
            else
            {
              MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "CAPIv2 OLM 0x%8lX: Set Input Media format "
                    "sucessful for port_index = %d", me_ptr->capi_v2_olm_identifier, port_index);
            }
          }
          else
          {
            MSG_4(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Failed in Set Property "
                  "id 0x%lx (CAPI_V2_INPUT_MEDIA_FORMAT_V2) Bad param size %lu for port_index = 0x%lx",
                  me_ptr->capi_v2_olm_identifier, (uint32_t)prop_ptr[i].id, payload->actual_data_len, port_index);
            CAPI_V2_SET_ERROR(capi_v2_result, CAPI_V2_ENEEDMORE);
            break;
          }
        }
        else
        {
          MSG_4(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Failed in Set Property "
                "id 0x%lx (CAPI_V2_INPUT_MEDIA_FORMAT_V2) Bad param size %lu for port_index = 0x%lx",
                me_ptr->capi_v2_olm_identifier, (uint32_t)prop_ptr[i].id, payload->actual_data_len, port_index);
          CAPI_V2_SET_ERROR(capi_v2_result, CAPI_V2_ENEEDMORE);
          break;
        }
        break;
      }

      case CAPI_V2_OUTPUT_MEDIA_FORMAT:
      {
        /* push output media format command to remote proc */


        /* Send output media format command to the remote service*/
        break;
      }
      case CAPI_V2_LOG_CODE:
      {
        if(payload->actual_data_len >= sizeof(capi_v2_log_code_t))
        {
          capi_v2_log_code_t *data_ptr = (capi_v2_log_code_t *)payload->data_ptr;
          if(NULL == data_ptr)
          {
            MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Failed in Set Property "
                  "id CAPI_V2_LOG_CODE - NULL log code ptr (%p)", me_ptr->capi_v2_olm_identifier, data_ptr);
            return CAPI_V2_EBADPARAM;
          }

          (void)memscpy(&me_ptr->log_code,
                        sizeof(me_ptr->log_code),
                        data_ptr,
                        payload->actual_data_len);

          /* push the log code to remote proc */
        }
        else
        {
          MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Failed in Set Property "
                "id 0x%lx (CAPI_V2_LOG_CODE) Bad param size %lu",
                me_ptr->capi_v2_olm_identifier, (uint32_t)prop_ptr[i].id, payload->actual_data_len);
          CAPI_V2_SET_ERROR(capi_v2_result, CAPI_V2_ENEEDMORE);
          break;
        }

        MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "CAPIv2 OLM 0x%8lX: Set Property successful for CAPI_V2_LOG_CODE",
                                              me_ptr->capi_v2_olm_identifier);
        break;
      }

      default:
      {
        MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Failed in Set Property, "
              "Unsupported prop_id 0x%lx", me_ptr->capi_v2_olm_identifier, (uint32_t)prop_ptr[i].id);
        CAPI_V2_SET_ERROR(capi_v2_result, CAPI_V2_EUNSUPPORTED);
        break;
      }
    }
  }
  return capi_v2_result;
}

/**
 * This function is used get properties from the CAPI.
 *
 * @param[in] me_ptr, pointer to the CAPI lib.
 * @param[in] props_ptr, pointer to the prop list that is needed.
 *
 * @return capi_v2_err_t, result code
 */
capi_v2_err_t capi_v2_olm_process_get_properties(capi_v2_olm_t *me_ptr, capi_v2_proplist_t *props_ptr)
{
  capi_v2_err_t capi_v2_result = CAPI_V2_EOK;
  capi_v2_prop_t *prop_ptr = props_ptr->prop_ptr;

  uint32_t olm_iid = 0;
  if(me_ptr)
  {
    olm_iid = me_ptr->capi_v2_olm_identifier;
  }

  if(!prop_ptr)
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Get properties received bad pointer in prop_list",
                                          olm_iid);
    return CAPI_V2_EFAILED;
  }

  for(uint32_t i = 0; i < props_ptr->props_num; i++)
  {
    capi_v2_buf_t *payload = &prop_ptr[i].payload;

    switch((uint32_t)prop_ptr[i].id)
    {
      case CAPI_V2_INIT_MEMORY_REQUIREMENT:
      {
        if(payload->max_data_len >= sizeof(capi_v2_init_memory_requirement_t))
        {
          capi_v2_init_memory_requirement_t *data_ptr = (capi_v2_init_memory_requirement_t*)payload->data_ptr;
          data_ptr->size_in_bytes = sizeof(capi_v2_olm_t);
          payload->actual_data_len = sizeof(capi_v2_init_memory_requirement_t);
        }
        else
        {
          MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO,
                "CAPIv2 OLM 0x%8lX: Failed in Get Property id 0x%lx (CAPI_V2_INIT_MEMORY_REQUIREMENT) "
                "Bad param size %lu", olm_iid, (uint32_t)prop_ptr[i].id, payload->max_data_len);
          CAPI_V2_SET_ERROR(capi_v2_result, CAPI_V2_ENEEDMORE);
          break;
        }
        break;
      }

      case CAPI_V2_IS_INPLACE:
      {
        if(payload->max_data_len >= sizeof(capi_v2_is_inplace_t))
        {
          capi_v2_is_inplace_t *data_ptr = (capi_v2_is_inplace_t*)payload->data_ptr;
          data_ptr->is_inplace = FALSE;
          payload->actual_data_len = sizeof(capi_v2_is_inplace_t);
        }
        else
        {
          MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO,
                "CAPIv2 OLM 0x%8lX: Failed in Get Property id 0x%lx (CAPI_V2_IS_INPLACE) "
                "Bad param size %lu", olm_iid, (uint32_t)prop_ptr[i].id, payload->max_data_len);
          CAPI_V2_SET_ERROR(capi_v2_result, CAPI_V2_ENEEDMORE);
          break;
        }
        break;
      }

      case CAPI_V2_REQUIRES_DATA_BUFFERING:
      {
        if(payload->max_data_len >= sizeof(capi_v2_requires_data_buffering_t))
        {
          capi_v2_requires_data_buffering_t *data_ptr = (capi_v2_requires_data_buffering_t*)payload->data_ptr;
          // Need to update based on sync or async mode
          data_ptr->requires_data_buffering = TRUE;
          payload->actual_data_len = sizeof(capi_v2_requires_data_buffering_t);
        }
        else
        {
          MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO,
                "CAPIv2 OLM 0x%8lX: Failed in Get Property id 0x%lx (CAPI_V2_REQUIRES_DATA_BUFFERING) "
                "Bad param size %lu", olm_iid, (uint32_t)prop_ptr[i].id, payload->max_data_len);
          CAPI_V2_SET_ERROR(capi_v2_result, CAPI_V2_ENEEDMORE);
          break;
        }
        break;
      }

      case CAPI_V2_STACK_SIZE:
      {
        if(payload->max_data_len >= sizeof(capi_v2_stack_size_t))
        {
          capi_v2_stack_size_t *data_ptr = (capi_v2_stack_size_t*)payload->data_ptr;
          data_ptr->size_in_bytes = STACK_SIZE;
          payload->actual_data_len = sizeof(capi_v2_stack_size_t);
        }
        else
        {
          MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO,
                "CAPIv2 OLM 0x%8lX: Failed in Get Property id 0x%lx (CAPI_V2_STACK_SIZE) "
                "Bad param size %lu", olm_iid, (uint32_t)prop_ptr[i].id, payload->max_data_len);
          CAPI_V2_SET_ERROR(capi_v2_result, CAPI_V2_ENEEDMORE);
        }

        break;
      }

      case CAPI_V2_NUM_NEEDED_FRAMEWORK_EXTENSIONS:
      {
        if(payload->max_data_len >= sizeof(capi_v2_num_needed_framework_extensions_t))
        {
          capi_v2_num_needed_framework_extensions_t *data_ptr = (capi_v2_num_needed_framework_extensions_t *)payload->data_ptr;
          data_ptr->num_extensions = 1;
          payload->actual_data_len = sizeof(capi_v2_num_needed_framework_extensions_t);
        }
        else
        {
          MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO,
                "CAPIv2 OLM 0x%8lX: Failed in Get Property id 0x%lx (CAPI_V2_NUM_NEEDED_FRAMEWORK_EXTENSIONS) "
                "Bad param size %lu",olm_iid, (uint32_t)prop_ptr[i].id, payload->max_data_len);
          CAPI_V2_SET_ERROR(capi_v2_result, CAPI_V2_ENEEDMORE);
        }
        break;
      }

      case CAPI_V2_NEEDED_FRAMEWORK_EXTENSIONS:
      {
        if(payload->max_data_len >= sizeof(capi_v2_framework_extension_id_t))
        {
          capi_v2_framework_extension_id_t *data_ptr = (capi_v2_framework_extension_id_t *)payload->data_ptr;
          data_ptr[0].id             = FWK_EXTN_OLM;
          payload->actual_data_len   = sizeof(capi_v2_framework_extension_id_t);
        }
        else
        {
          MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO,
                "CAPIv2 OLM 0x%8lX: Failed in Get Property id 0x%lx (CAPI_V2_NEEDED_FRAMEWORK_EXTENSIONS) "
                "Bad param size %lu", olm_iid, (uint32_t)prop_ptr[i].id, payload->max_data_len);
          CAPI_V2_SET_ERROR(capi_v2_result, CAPI_V2_ENEEDMORE);
        }
        break;
      }


      case CAPI_V2_PORT_NUM_INFO:
      {
        if((payload->max_data_len >= sizeof(capi_v2_port_num_info_t)) && (me_ptr!=NULL))
        {
          capi_v2_port_num_info_t *data_ptr = (capi_v2_port_num_info_t*)payload->data_ptr;

          /* Return active number of input and output ports */
          data_ptr->num_input_ports   = me_ptr->num_active_input_ports;
          data_ptr->num_output_ports  = me_ptr->num_active_output_ports;
          payload->actual_data_len = sizeof(capi_v2_port_num_info_t);
        }
        else
        {
          MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO,
                "CAPIv2 OLM 0x%8lX: Failed in Get Property id 0x%lx (CAPI_V2_PORT_NUM_INFO )"
                "Bad param size %lu",olm_iid, (uint32_t)prop_ptr[i].id, payload->max_data_len);
          CAPI_V2_SET_ERROR(capi_v2_result, CAPI_V2_ENEEDMORE);
        }
        break;
      }

      case CAPI_V2_PORT_DATA_THRESHOLD:
      {
        if (payload->max_data_len >= sizeof(capi_v2_port_data_threshold_t))
        {
          capi_v2_port_data_threshold_t *data_ptr = (capi_v2_port_data_threshold_t*)payload->data_ptr;
          if (!prop_ptr[i].port_info.is_valid)
          {
            MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: get property id not valid", olm_iid);
            capi_v2_result = CAPI_V2_EBADPARAM;
          }
          if (prop_ptr[i].port_info.is_input_port)
          {
            if (0 != prop_ptr[i].port_info.port_index)
            {
              MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: get property id 0x%lx Max Input Port: "
                    "2. Requesting for index %lu", olm_iid, (uint32_t)prop_ptr[i].id, prop_ptr[i].port_info.port_index);
              capi_v2_result = CAPI_V2_EBADPARAM;
            }
            data_ptr->threshold_in_bytes = 1;
          }
          else
          {
            if (0 != prop_ptr[i].port_info.port_index)
            {
              MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: get property id 0x%lx Max Output Port: 1. "
                    "Requesting for index %lu", olm_iid,(uint32_t)prop_ptr[i].id, prop_ptr[i].port_info.port_index);
              CAPI_V2_SET_ERROR(capi_v2_result,CAPI_V2_EBADPARAM);
            }
            data_ptr->threshold_in_bytes = 1;
          }
          payload->actual_data_len = sizeof(capi_v2_port_data_threshold_t);
        }
        else
        {
          MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: get property id 0x%lx Bad param size %lu",
                olm_iid, (uint32_t)prop_ptr[i].id, payload->max_data_len);
          CAPI_V2_SET_ERROR(capi_v2_result, CAPI_V2_ENEEDMORE);
        }
        break;
      }
      default:
      {
        MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Get Property for"
              " Unsupported prop_id 0x%lx", olm_iid, (uint32_t)prop_ptr[i].id);
        CAPI_V2_SET_ERROR(capi_v2_result, CAPI_V2_EUNSUPPORTED);
        break;
      }
    }
  }
  return capi_v2_result;
}

/**
 * This function is used process Open Set Param for the CAPI.
 *
 * @param[in] me_ptr, pointer to the CAPI lib.
 * @param[in] data_ptr, pointer to the open configuratio data.
 *
 * @return capi_v2_err_t, result code
 */
capi_v2_err_t capi_v2_olm_process_open(capi_v2_olm_t *me_ptr, capi_v2_olm_open_t *data_ptr)
{
  ADSPResult result = ADSP_EOK;

  /* Note : Once the supported version numbers increase, the code below needs to be
   *        updated accordingly.
   */
  if(data_ptr->version > 0)
  {
    MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM: Received invalid version for Open Command");
    return CAPI_V2_EBADPARAM;
  }

  /* Copy the olm configuration parameters */
  memscpy(&me_ptr->olm_cfg.olm_open_cfg,
          sizeof(capi_v2_olm_open_t),
          data_ptr,
          sizeof(capi_v2_olm_open_t));

  olm_open_config_t *module_config_ptr  = (olm_open_config_t *)(data_ptr + 1);

  /* Check Sanity of open config params*/
  if( module_config_ptr->frame_size <=0 ||
      NULL == module_config_ptr->olm_resp_cb_info.cb_fn_ptr ||
      NULL == module_config_ptr->olm_resp_cb_info.context_ptr ||
      NULL == module_config_ptr->olm_topo_info_ptr ||
      module_config_ptr->scale_factor <= 0)
  {
    MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM %lu PlX -"
          " Open command payload is invalid",module_config_ptr->olm_iid, module_config_ptr->client_id);
    return CAPI_V2_EBADPARAM;
  }

#ifdef CAPI_V2_OLM_DEBUG
  MSG_4(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "CAPIv2 OLM %lu Client ID P%lX, Received Capi V2 OLM_OPEN"
        " with command params - frame_size  = %lu, scale_factor = %lu ",
        module_config_ptr->olm_iid, module_config_ptr->client_id,
        module_config_ptr->frame_size, module_config_ptr->scale_factor);
#endif

  int8_t *ptr = (int8_t *) qurt_elite_memory_malloc(data_ptr->payload_size, QURT_ELITE_HEAP_DEFAULT);
  if(ptr == NULL)
  {
    MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX:%lu Failed to allocate memory to"
                                        " store open comand payload",module_config_ptr->olm_iid, module_config_ptr->client_id);
    return CAPI_V2_ENOMEMORY;
  }
  else
  {
    /* Copy the olm configuration parameters */
    memscpy(ptr,data_ptr->payload_size,
            module_config_ptr, data_ptr->payload_size);
    me_ptr->olm_cfg.dynamic_cfg = (olm_open_config_t*)ptr;
  }

  me_ptr->capi_v2_olm_identifier = get_capi_v2_olm_identifier(me_ptr);
  me_ptr->remote_proc_id         = me_ptr->olm_cfg.dynamic_cfg->olm_topo_info_ptr->module_info[0].client_proc_id;
  me_ptr->remote_module_id       = AP_MODULE_AUDPROC_ID_DEFAULT; //TODO: This needs to come from Dynamic Service

  /* Store the necessary information sent by the framework */
  me_ptr->olm_num_frames = module_config_ptr->frame_size;
  me_ptr->sync_mode      = module_config_ptr->olm_topo_info_ptr->is_sync_mode;

  /* Use cached response Q and OLM instance IID to register OLM with APR service */
  result = olm_apr_register(me_ptr);
  if(ADSP_EOK != result )
  {
    MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Unable to register with APR with result 0x%x",me_ptr->capi_v2_olm_identifier, result);
    return adsp_result_to_capi_v2_err(result);
  }

  /* Send open command with the init params to Remote AP */
  result = olm_send_open_cmd(me_ptr);
  if(ADSP_EOK != result )
  {
    MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Failed in sending the open command with result",me_ptr->capi_v2_olm_identifier, result);
    return adsp_result_to_capi_v2_err(result);
  }

  return CAPI_V2_EOK;

}

/**
 * This function is used reset the OLM CAPI
 *
 * @param[in] me_ptr, pointer to the CAPI lib.
 *
 * @return capi_v2_err_t, result code
 */

capi_v2_err_t capiv2_olm_reset(capi_v2_olm_t *me_ptr)
{
  capi_v2_err_t capi_v2_result = CAPI_V2_EOK;
  capi_v2_err_t capi_v2_temp_result = CAPI_V2_EOK;
  ADSPResult result = ADSP_EOK;

  uint32_t olm_iid =  me_ptr->capi_v2_olm_identifier;
  /*
   * Flush the current working write data buffer by re-setting the size fields
   */
  for(uint32_t in_port_idx =0; ((in_port_idx < me_ptr->num_active_input_ports) && (me_ptr->num_active_input_ports < OLM_MAX_INPUT_PORTS)); in_port_idx++)
  {
    if(NULL != me_ptr->tmp_wr_data_buf_ptr[in_port_idx])
    {
      olm_write_buf_t *write_data_buf_ptr = me_ptr->tmp_wr_data_buf_ptr[in_port_idx];
      ap_container_data_write_buffer_v1_t *write_buf_ptr = &write_data_buf_ptr->data_write_buf;
      write_buf_ptr->buf_size = 0;
      write_data_buf_ptr->fill_size_per_ch = 0;
    }
  }

  /*
   * Flush the Read response buffers from the Queue and return them to remote.
   */
  for(uint32_t out_port_idx = 0; ((out_port_idx <  me_ptr->num_active_output_ports)&& (me_ptr->num_active_input_ports < OLM_MAX_OUTPUT_PORTS)); out_port_idx++)
  {
    olm_read_buf_t *temp_rd_buf_ptr;
    capi_v2_result |= capi_v2_temp_result;
    capi_v2_temp_result = CAPI_V2_EOK;

    if(me_ptr->rd_rsp_q_ptr[out_port_idx]) // Need this check, in case if FLUSH command is received before Media format
    {
      while(1)
      {
        elite_msg_any_t rd_msg;

        /* Initialize the temporary pointer to NULL*/
        temp_rd_buf_ptr = NULL;

        /* pop all the buffers from read data Q */
        result = qurt_elite_queue_pop_front(me_ptr->rd_rsp_q_ptr[out_port_idx], (uint64_t*) &rd_msg);
        if(ADSP_FAILED(result))
        {
          MSG_1(MSG_SSID_QDSP6, DBG_LOW_PRIO, "CAPIv2 OLM 0x%8lX: OLM reset found empty Read response queue. ", olm_iid);
          break;
        }

        elite_apr_packet_t *data_apr_pkt_ptr = (elite_apr_packet_t *)rd_msg.pPayload;

        /*Get the opcode of the read response packet */
        uint32_t opcode = elite_apr_if_get_opcode(data_apr_pkt_ptr);
        if(AP_CMDRSP_DATA == opcode)
        {
          /* Get the read buffer pointer and reset the offsets*/
          if(ADSP_EOK != get_rd_data_buf_ptr(me_ptr, data_apr_pkt_ptr,out_port_idx, &temp_rd_buf_ptr))
          {
            MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: OLM reset Failed to get the read buf ptr.", olm_iid);
            CAPI_V2_SET_ERROR(capi_v2_temp_result, CAPI_V2_EFAILED);
            elite_apr_if_free(me_ptr->apr_handle, data_apr_pkt_ptr);
            continue;
          }

          elite_apr_if_free(me_ptr->apr_handle, data_apr_pkt_ptr);

          if(ADSP_EOK != olm_send_data_cmd(me_ptr, (void *)temp_rd_buf_ptr, READ_CMD) )
          {
            MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: OLM reset  Failed to return"
                "Read buf ptr to remote container. ", olm_iid);
            CAPI_V2_SET_ERROR(capi_v2_temp_result, CAPI_V2_EFAILED);
          }
        }
        else
        {
          // todo :Need to check if its is an event and ensure to handle/cache the event.
          elite_apr_if_free(me_ptr->apr_handle, data_apr_pkt_ptr);
        }
      }
    }

    if(NULL != me_ptr->tmp_rd_data_buf_ptr[out_port_idx])
    {
      olm_read_buf_t *read_data_buf_ptr = me_ptr->tmp_rd_data_buf_ptr[out_port_idx];
      uint32_t samples_dropped_per_ch = read_data_buf_ptr->buf_size_per_ch;
      if(ADSP_EOK != olm_send_data_cmd(me_ptr, (void *)me_ptr->tmp_rd_data_buf_ptr[out_port_idx], READ_CMD) )
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: OLM reset: Failed to return Read buf"
            " ptr to remote container." , olm_iid );
        CAPI_V2_SET_ERROR(capi_v2_temp_result, CAPI_V2_EFAILED);
      }
      else
      {
        MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "CAPIv2 OLM 0x%8lX: OLM reset: Dropped samples per channel"
            " from read buffer %lu", olm_iid, samples_dropped_per_ch);
        me_ptr->tmp_rd_data_buf_ptr[out_port_idx] = NULL;
      }
    }
  }
  return capi_v2_result;
}
