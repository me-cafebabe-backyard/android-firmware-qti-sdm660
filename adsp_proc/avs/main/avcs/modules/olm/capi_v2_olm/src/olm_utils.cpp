/**
@file olm_utils.cpp

@brief This file contains the utility functionality for Off-loading module

 */

/*========================================================================

Edit History

when          who            what, where, why
--------      ---            -------------------------------------------------------
18/9/2017     MK             Initial version
11/27/2017    bvodapal       Updated to moved the cmd/response/data/ handling code to separate files
==========================================================================*/

/*-----------------------------------------------------------------------
Copyright (c) 2017-2018 Qualcomm Technologies, Inc.  All Rights Reserved.
Confidential and Proprietary - Qualcomm Technologies, Inc.
-----------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "qurt_elite.h"
#include "capi_v2_olm.h"
#include "capi_v2_olm_internal.h"
#include "qurt_elite_memory.h"
#include "Elite_fwk_extns_olm.h"
#include "EliteAprIf.h"
#include "ap_server_api.h"
#include "olm_utils.h"
#include "EliteMsg.h"
#include "EliteMem_Util.h"

/*----------------------------------------------------------------------------
 * Function Definitions
 * -------------------------------------------------------------------------*/

/* Proc ID to Remote Static Service name mapping */
//NOTE: The ADSP entry is only for Simulation Testing.
const char *proc_to_svc_name_map[] = {"qcom.ap.molm", //ADSP
                                      "qcom.ap.molm", //MDSP
                                      "qcom.ap.solm"  //SLPI
                                     };

/**
 * This function is to dump the contents of the incoming pointer
 *
 * @param[in] buffer pointer to the incoming buffer
 * @param[in] size   size of the buffer to be dumped.
 *
 * @return None
 */
void olm_elite_hexdump(const uint8_t* buffer, int32_t size)
{
  // output name and size
  MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "buffer addr: 0x%lx len: %ld", (uint32_t)buffer, size);

  // print 8 bytes per line
  for (int i =0; i + 4 <= size; i += 4 ) {
    MSG_4(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "%02hX %02hX %02hX %02hX",
          buffer[0], buffer[1], buffer[2], buffer[3]);
    buffer += 4;
  }
}

/**
 * This function is to check if the incoming sample rate is fractional
 *
 * @param[in] sample_rate incoming sample rate
 *
 * @return TRUE or FALSE
 */
bool_t is_sample_rate_fractional(uint32_t sample_rate)
{
  if(((sample_rate/1000)*1000) != sample_rate)
  {
    return TRUE;
  }
  return FALSE;
}

/**
 * This function is to generate an unique identifier for the OLM.
 * It is a combination of the dynamic service client ID and OLM instance ID.
 *------------------------------------------------------------------
 * Client ID (upper 16 bits) | OLM instance ID (lower 16 bits)
 *------------------------------------------------------------------
 * @param[in] me_ptr pointer to the OLM module structure
 *
 * @return TRUE or FALSE
 */
uint32_t get_capi_v2_olm_identifier(capi_v2_olm_t *me_ptr)
{
  uint32_t olm_id = 0xFFFFFFFF; // invalid ID
  if(me_ptr)
  {
    if(me_ptr->olm_cfg.dynamic_cfg)
    {
      olm_id = ((me_ptr->olm_cfg.dynamic_cfg->client_id << 16) | (me_ptr->olm_cfg.dynamic_cfg->olm_iid));
    }
  }
  return olm_id;
}

/**
 * This function is to update the mode of OLM
 *
 * @param[in] me_ptr pointer to the OLM module structure
 *
 * @return none
 */
void olm_check_update_sync_mode(capi_v2_olm_t *me_ptr)
{
  /* Once in ASYNC mode, OLM can never go back to SYNC Mode*/
  if(FALSE == me_ptr->sync_mode)
  {
    return;
  }

  bool_t orig_mode = me_ptr->sync_mode;

  /* If OLM is in sync mode, check for the state of OLM/Remote Config
   * to check if it can continue operating in SYNC mode */
  if(TRUE == me_ptr->sync_mode)
  {
    /** 1. Frame size check
           - Check if the Remote and OLM have the same number of operating frames
           - Ensure that the frame size is not lesser than 2 * IPC Latency
    */
    if(is_olm_mask_set(me_ptr->is_output_mf_rcvd_mask, OLM_PRIMARY_OUTPUT_PORT))
    {
      if(me_ptr->remote_num_frames == me_ptr->olm_num_frames)
      {
        /* Change to ASYNC mode is the IPC latency is greater than the threshold*/
        if( (2 * IPC_LATENCY_IN_NUM_FRAMES)  >  me_ptr->remote_num_frames)
        {
          me_ptr->sync_mode = FALSE;
        }
        /* If the frame sizes are the same, check whether the remote container has
         * raised an explicit port threshold request */
        if(me_ptr->remote_threshold)
        {
          me_ptr->sync_mode = FALSE;
        }
      }
      else
      {
        me_ptr->sync_mode = FALSE;
      }
    }

    /** 2. Unequal sample rates across primary input & outputs
            - If the sample rates of OLM input and Remote output
               media formats, do not match, move to async mode.
     */
    if((is_olm_mask_set(me_ptr->is_input_mf_rcvd_mask, OLM_PRIMARY_INPUT_PORT)) &&
        (is_olm_mask_set(me_ptr->is_output_mf_rcvd_mask,OLM_PRIMARY_OUTPUT_PORT)))
    {
      if(me_ptr->in_media_fmt[OLM_PRIMARY_INPUT_PORT].f.sampling_rate != me_ptr->out_media_fmt[OLM_PRIMARY_OUTPUT_PORT].f.sampling_rate)
      {
        me_ptr->sync_mode = FALSE;
      }
    }

    /* 3. If it is a multi input port use case, disable sync mode */
    if(me_ptr->num_active_input_ports > 1)
    {
      me_ptr->sync_mode = FALSE;
    }
  } //if sync_mode == TRUE

  if(orig_mode != me_ptr->sync_mode)
  {
//#ifdef CAPI_V2_OLM_DEBUG
  MSG_3(MSG_SSID_QDSP6, DBG_MED_PRIO, "CAPIv2 OLM 0x%8lX: Sync Mode change from %d to %d",
                                       me_ptr->capi_v2_olm_identifier, orig_mode, me_ptr->sync_mode);
///#endif
  }
}

/**
 * This function is to calculate the Q Factor
 *
 * @param[in] bit_width input
 *
 * @return uint32_t
 */
uint32_t olm_calc_q_factor(uint32_t bit_width)
{
  uint32_t q_factor = 0;
  if(16 == bit_width)
  {
    q_factor = 15;
  }
  else if(24 == bit_width)
  {
    q_factor = 27;
  }
  else if(32 == bit_width)
  {
    q_factor = 31;
  }

  return q_factor;
}

/**
 * This function is used to set/reset nth bit of an uint32_t variable.
 *
 * @param[in] mask_ptr, pointer to the mask variable of type (uint32_t)
 * @param[in] pos,      position of the bit to be modified
 * @param[in] is_set,   bool indicating whether the bit is to be set or reset
 *
 * @return none
 */
void olm_set_reset_bitmask(uint32_t *mask_ptr, uint32_t pos, bool_t is_set)
{
  if(pos > 31)
  {
    return;
  }

  uint32_t value = *mask_ptr;

  if(is_set)
  {
    value |= (1 << pos);
  }
  else
  {
    value &= ~(1 << pos);
  }

  *mask_ptr = value;

}

/**
 * This function is used to check if the nth bit of an uint32_t variable is set
 *
 * @param[in] mask,     mask variable of type (uint32_t)
 * @param[in] pos,      position of the bit to be modified
 *
 * @return TRUE or FALSE
 */
bool_t is_olm_mask_set(uint32_t mask, uint32_t pos)
{
  return (mask & (1 << pos));
}

/**
 * This function is used to find the index of the command handle array
 *   i.  Returns any existing index based on the incoming cmd & token params
 *   ii. Returns the next available index in the array
 *
 * @param[in] me_ptr,  pointer to OLM module structure
 * @param[in] cmd,     opcode of the command to search for
 * @param[in] token,   token of the command to search for
 * @param[in] is_find_free_index, indicates if the search is for the next available index
 *
 * @return uint32_t
 */
static uint32_t find_cmd_handle_index(capi_v2_olm_t *me_ptr, uint32_t cmd, uint32_t token, bool_t is_find_free_index)
{
  olm_cmd_handle_t *cmd_hndls = me_ptr->cmd_hndls;

  uint32_t index = CMD_HANDLE_INVALID_INDEX ;
  if(is_find_free_index)
  {
    for(uint32_t i = 0 ; i < CMD_HANDLES_MAX_ARRAY_SIZE ; i++ )
    {
      if(FALSE == cmd_hndls[i].is_used)
      {
        index = i;
        return index;
      }
    }
  }
  else
  {
    for(uint32_t i = 0 ; i < CMD_HANDLES_MAX_ARRAY_SIZE ; i++ )
    {
      if(TRUE == cmd_hndls[i].is_used && cmd == cmd_hndls[i].cmd && token == cmd_hndls[i].token )
      {
        index = i;
        return index;
      }
    }
  }
  return index;
}

/**
 * This function is used to free an entry of the command handle array
 *
 * @param[in] me_ptr,  pointer to OLM module structure
 * @param[in] cmd,     opcode of the command to be freed
 * @param[in] token,   token of the command to be freed
 *
 * @return none
 */
void free_cmd_handle(capi_v2_olm_t *me_ptr, uint32_t cmd, uint32_t token)
{
   uint32_t i = find_cmd_handle_index(me_ptr, cmd, token, FALSE);
   if(CMD_HANDLE_INVALID_INDEX == i || (i >= CMD_HANDLES_MAX_ARRAY_SIZE))
   {
     MSG_4(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM %lu: Unable to find "
                                    "command handle for cmd = 0x%x, token = 0x%x"
                                    "Translated to index = %d", me_ptr->capi_v2_olm_identifier,
                                    cmd, token, i);
     return;
   }

   olm_cmd_handle_t *cmd_hndls = me_ptr->cmd_hndls;

   cmd_hndls[i].is_used = FALSE;
   if(cmd_hndls[i].payload)
   {
     qurt_elite_memory_free(cmd_hndls[i].payload);
     cmd_hndls[i].payload = NULL;
   }

}

/**
 * This function is used to store an entry in the command handle array
 *
 * @param[in] me_ptr,  pointer to OLM module structure
 * @param[in] cmd,     opcode of the command to be stored
 * @param[in] token,   token of the command to be stored
 * @param[in] payload, pointer to the payload of the command to be stored
 *
 * @return ADSPResult, error code
 */
ADSPResult store_cmd_payload(capi_v2_olm_t *me_ptr, uint32_t cmd,  uint32_t token, void * payload)
{
  uint32_t i = find_cmd_handle_index(me_ptr, cmd, token, TRUE);

  if(CMD_HANDLE_INVALID_INDEX == i || (i >= CMD_HANDLES_MAX_ARRAY_SIZE))
  {
    MSG_4(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM %lu: Unable to find "
          "free command handle for cmd = 0x%x, token = 0x%x"
          "Translated to index = %d", me_ptr->capi_v2_olm_identifier,
          cmd, token, i);
    return ADSP_EFAILED;
  }

  olm_cmd_handle_t *cmd_hndls = me_ptr->cmd_hndls;

  cmd_hndls[i].is_used = TRUE;
  cmd_hndls[i].cmd     = cmd ;
  cmd_hndls[i].token   = token;
  cmd_hndls[i].payload = payload;
  return ADSP_EOK;

}

/**
 * This function is used to retrieve a payload pointer from the command handle array
 *
 * @param[in] me_ptr,  pointer to OLM module structure
 * @param[in] cmd,     opcode of the command to be stored
 * @param[in] token,   token of the command to be stored
 *
 * @return void*, payload pointer
 */
void *get_cmd_payload(capi_v2_olm_t *me_ptr, uint32_t cmd,  uint32_t token)
{
  uint32_t i = find_cmd_handle_index(me_ptr, cmd, token, FALSE);
  if(CMD_HANDLE_INVALID_INDEX == i || (i >= CMD_HANDLES_MAX_ARRAY_SIZE))
  {
    MSG_4(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM %lu: Unable to find "
          "command handle for cmd = 0x%x, token = 0x%x"
          "Translated to index = %d", me_ptr->capi_v2_olm_identifier,
          cmd, token, i);
    return NULL;
  }

  olm_cmd_handle_t *cmd_hndls = me_ptr->cmd_hndls;
  return cmd_hndls[i].payload;
}

/**
 * This function is the APR callback function registered by OLM. This is
 * invoked everytime a APR packet is received by this OLM.
 *
 * @param[in] apr_pkt,       pointer to the APR packet
 * @param[in] context_ptr,   pointer to the context variable (OLM structure)
 *
 * @return int32_t, error code
 */
int32_t remote_response_apr_dispatch_fn( aprv2_packet_t *apr_pkt, void* context_ptr)
{
  capi_v2_olm_t *me_ptr = (capi_v2_olm_t *) context_ptr;

  /* Allocate a message structure */
  elite_msg_any_t msg;
  msg.unOpCode = ELITE_APR_PACKET;
  msg.pPayload = apr_pkt;

  elite_apr_packet_t *resp_pkt_ptr = (elite_apr_packet_t*)apr_pkt; // aprv2_packet_t and elite_apr_packet_t are same
  uint32_t           opcode        = elite_apr_if_get_opcode(resp_pkt_ptr);

#ifdef OLM_LATENCY_MEASUREMENT
  MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: received APR packet with opcode 0x%x at time %lld",me_ptr->capi_v2_olm_identifier, opcode, qurt_elite_timer_get_time());
#endif

  MSG_3(MSG_SSID_QDSP6, DBG_LOW_PRIO,"At <0x%x> CAPIv2 OLM 0x%8lX: received APR packet <0x%8lX>",
                              elite_apr_if_get_dst_addr(resp_pkt_ptr), me_ptr->capi_v2_olm_identifier ,opcode);

  /* Push the data command responses to corresponding Queues. All other responses to command response Queue */
  if(AP_CMDRSP_DATA == opcode )
  {
    uint8_t   *payload  =  (uint8_t *)elite_apr_if_get_payload_ptr(resp_pkt_ptr);
    ap_server_stat_cmn_header_t *header_ptr = reinterpret_cast<ap_server_stat_cmn_header_t*>(payload);

    /* Push to write data Queue*/
    if(AP_PARAM_ID_DATA_WRITE_DONE == header_ptr->param_id)
    {
      ap_container_data_write_buffer_done_v1_t *wr_done_ptr = (ap_container_data_write_buffer_done_v1_t* )(payload + sizeof(ap_server_stat_cmn_header_t));

      if(ADSP_EOK != qurt_elite_queue_push_back(me_ptr->wr_rsp_q_ptr[wr_done_ptr->port_index], (uint64_t *)&msg))
      {
        MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Unable to push message to write "
                                              "response queue of port_index = 0x%x", me_ptr->capi_v2_olm_identifier, wr_done_ptr->port_index);
        elite_apr_if_end_cmd(me_ptr->apr_handle, apr_pkt, ADSP_EFAILED);
      }
    }
    else /* Push to read data queue */
    {
      if(ADSP_EOK != qurt_elite_queue_push_back(me_ptr->rd_rsp_q_ptr[0], (uint64_t *)&msg))
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Unable to push message to read response queue.", me_ptr->capi_v2_olm_identifier);
        elite_apr_if_end_cmd(me_ptr->apr_handle, apr_pkt, ADSP_EFAILED);
      }
    }
  }
  else if(AP_CMD_EVENT == opcode)
  {
    void   *payload  =  elite_apr_if_get_payload_ptr(resp_pkt_ptr);
    ap_server_stat_cmn_header_t *header_ptr = reinterpret_cast<ap_server_stat_cmn_header_t*>(payload);

    if(AP_PARAM_ID_CUSTOM_EVENT == header_ptr->param_id)
    {
      ap_container_custom_event_v1_t* custom_event_ptr = (ap_container_custom_event_v1_t*)((uint8_t*)header_ptr + sizeof(ap_server_stat_cmn_header_t));

      /* Push to read data Queue, since it is Output media format event*/
      if( AP_EVENT_OUTPUT_MEDIA_FORMAT == custom_event_ptr->event_id ||
          AP_EVENT_NUM_UNIT_FRAMES == custom_event_ptr->event_id )
      {
        if(ADSP_EOK != qurt_elite_queue_push_back(me_ptr->rd_rsp_q_ptr[0], (uint64_t *)&msg))
        {
          MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Unable to push message to read response queue.",me_ptr->capi_v2_olm_identifier);
          elite_apr_if_end_cmd(me_ptr->apr_handle, apr_pkt, ADSP_EFAILED);
        }
      }

      else /* If it is a normal event, then push it  to command queue*/
      {
        if(ADSP_EOK != qurt_elite_queue_push_back(me_ptr->olm_cfg.dynamic_cfg->framework_respQ, (uint64_t*)&msg))
        {
          MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Unable to push message to Service response queue.", me_ptr->capi_v2_olm_identifier);
          elite_apr_if_end_cmd(me_ptr->apr_handle, apr_pkt, ADSP_EFAILED);
        }
      }

    } //Custom Event
    else
    {
      if(ADSP_EOK != qurt_elite_queue_push_back(me_ptr->olm_cfg.dynamic_cfg->framework_respQ, (uint64_t*)&msg))
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Unable to push message to Service response queue.", me_ptr->capi_v2_olm_identifier);
        elite_apr_if_end_cmd(me_ptr->apr_handle, apr_pkt, ADSP_EFAILED);
      }
    }
  }
  else
  {
    if(ADSP_EOK != qurt_elite_queue_push_back(me_ptr->olm_cfg.dynamic_cfg->framework_respQ, (uint64_t*)&msg))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Unable to push message to Service response queue.", me_ptr->capi_v2_olm_identifier);
      elite_apr_if_end_cmd(me_ptr->apr_handle, apr_pkt, ADSP_EFAILED);
    }
  }

  return APR_EOK;
}

/**
 * This function is to handle events from AP Service.
 * The caller of the function needs to free the APR packet being passed to this function
 *
 * @param[in] me_ptr,    pointer to the OLM structure
 * @param[in] pkt_ptr,   pointer to the APR packet
 *
 * @return capi_v2_err_t, error code
 */
capi_v2_err_t olm_event_handler(capi_v2_olm_t *me_ptr, elite_apr_packet_t *pkt_ptr)
{
  capi_v2_err_t result = CAPI_V2_EOK;
  ap_server_stat_cmn_header_t *header_ptr;

  int8_t *buffer = (int8_t *)elite_apr_if_get_payload_ptr(pkt_ptr);

  uint32_t payload_size = elite_apr_if_get_payload_size(pkt_ptr);

  /* Iterate while the payload size is greater than zero */
  while(payload_size > 0)
  {
    header_ptr = reinterpret_cast<ap_server_stat_cmn_header_t*>(buffer);

    // Read the Param ID to fin
    if(AP_PARAM_ID_CUSTOM_EVENT == header_ptr->param_id)
    {
      buffer = buffer  + sizeof(ap_server_stat_cmn_header_t);

      if(header_ptr->param_version > AP_PARAM_CUSTOM_EVENT_VERSION || (0 == header_ptr->param_version))
      {
        MSG_4(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: param_id = 0x%x received version 0x%x, expected version range 0x1 to 0x%x",
                                        me_ptr->capi_v2_olm_identifier, header_ptr->param_id, header_ptr->param_version, AP_PARAM_CUSTOM_EVENT_VERSION);

        payload_size = payload_size - header_ptr->param_size - sizeof(ap_server_stat_cmn_header_t);
        buffer += header_ptr->param_size;
        CAPI_V2_SET_ERROR(result, CAPI_V2_EBADPARAM);
        continue; //RR: Keep the result

      }
      else
      {
        payload_size = payload_size - sizeof(ap_server_stat_cmn_header_t);

        ap_container_custom_event_v1_t* custom_event_ptr = (ap_container_custom_event_v1_t*)(buffer);

        buffer = buffer + header_ptr->param_struct_size;
        payload_size = payload_size - header_ptr->param_struct_size;

        switch(custom_event_ptr->event_id)
        {
          case AP_EVENT_DELAY:
          {
            if(custom_event_ptr->event_version > AP_PARAM_DELAY_VERSION || (0 == custom_event_ptr->event_version))
            {
              MSG_4(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: event_id = 0x%x Received version 0x%x, Expected version 0x1 to 0x%x",
                                      me_ptr->capi_v2_olm_identifier, custom_event_ptr->event_id, custom_event_ptr->event_version, AP_PARAM_DELAY_VERSION );
              buffer = buffer + custom_event_ptr->event_struct_size;
              payload_size = payload_size - custom_event_ptr->event_struct_size;
              CAPI_V2_SET_ERROR(result, CAPI_V2_EBADPARAM);
              continue;

            }

            if(ADSP_FAILED(custom_event_ptr->event_status))
            {
              MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: event_id = 0x%x Received with failure status 0x%x",
                                                    me_ptr->capi_v2_olm_identifier, custom_event_ptr->event_id, custom_event_ptr->event_status );
              buffer = buffer + custom_event_ptr->event_struct_size;
              payload_size = payload_size - custom_event_ptr->event_struct_size;
              CAPI_V2_SET_ERROR(result, adsp_result_to_capi_v2_err(custom_event_ptr->event_status));
              continue;

            }

            ap_container_event_delay_v1_t *resp_delay_ptr = (ap_container_event_delay_v1_t *)buffer;
            me_ptr->remote_delay_in_us = resp_delay_ptr->delay;

            capi_v2_olm_update_raise_delay_event(me_ptr);

            buffer = buffer + custom_event_ptr->event_struct_size;
            payload_size = payload_size - custom_event_ptr->event_struct_size;

            break;
          }
          case AP_EVENT_NUM_UNIT_FRAMES:
          {
            if(custom_event_ptr->event_version > AP_PARAM_NUM_UNIT_FRAMES_VERSION || (0 == custom_event_ptr->event_version))
            {
              MSG_4(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: event_id = 0x%x Received version 0x%x Expected Version 0x1 to 0x%x",
                           me_ptr->capi_v2_olm_identifier, custom_event_ptr->event_id, custom_event_ptr->event_version, AP_PARAM_NUM_UNIT_FRAMES_VERSION );
              buffer = buffer + custom_event_ptr->event_struct_size;
              payload_size = payload_size - custom_event_ptr->event_struct_size;
              CAPI_V2_SET_ERROR(result, CAPI_V2_EBADPARAM);
              continue;

            }

            /* If NUM_UNIT_FRAMES has failed status, it will be followed by DISABLE_EVENT as well. So simply continue*/
            if(ADSP_FAILED(custom_event_ptr->event_status))
            {
              MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: event_id = 0x%x Received with failure status 0x%x",
                    me_ptr->capi_v2_olm_identifier, custom_event_ptr->event_id, custom_event_ptr->event_status );
              buffer = buffer + custom_event_ptr->event_struct_size;
              payload_size = payload_size - custom_event_ptr->event_struct_size;
              CAPI_V2_SET_ERROR(result, adsp_result_to_capi_v2_err(custom_event_ptr->event_status));
              continue;

            }

            ap_container_event_num_frames_v1_t *resp_delay_ptr = (ap_container_event_num_frames_v1_t *)buffer;

            /* Raise algorithmic delay event to Dynamic service */
            uint32_t remote_num_frms = resp_delay_ptr->num_frames;
            me_ptr->remote_threshold = resp_delay_ptr->port_threshold;

            /* Check if there is any change in the remote frame size */
            if(remote_num_frms != me_ptr->remote_num_frames)
            {
              /* Update the remote num_frames*/
              me_ptr->remote_num_frames = remote_num_frms;

            }

            buffer = buffer + custom_event_ptr->event_struct_size;
            payload_size = payload_size - custom_event_ptr->event_struct_size;

            break;
          }
          case AP_EVENT_OUTPUT_MEDIA_FORMAT:
          {
            if(custom_event_ptr->event_version > AP_PARAM_OUTPUT_MEDIA_FORMAT_VERSION || (0 == custom_event_ptr->event_version))
            {
              MSG_4(MSG_SSID_QDSP6, DBG_MED_PRIO, "CAPIv2 OLM 0x%8lX: event_id = 0x%x Received version 0x%x Expected Version 0x1 to 0x%x",
                    me_ptr->capi_v2_olm_identifier, custom_event_ptr->event_id, custom_event_ptr->event_version, AP_PARAM_OUTPUT_MEDIA_FORMAT_VERSION );
              buffer = buffer + custom_event_ptr->event_struct_size;
              payload_size = payload_size - custom_event_ptr->event_struct_size;
              CAPI_V2_SET_ERROR(result, CAPI_V2_EBADPARAM);
              continue;
            }

            /* If OUTPUT MEDIA FORMAT has failed status, it will be followed by DISABLE_EVENT as well. So simply continue*/
            if(ADSP_FAILED(custom_event_ptr->event_status))
            {
              MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: event_id = 0x%x Received with failure status 0x%x",
                    me_ptr->capi_v2_olm_identifier, custom_event_ptr->event_id, custom_event_ptr->event_status );
              buffer = buffer + custom_event_ptr->event_struct_size;
              payload_size = payload_size - custom_event_ptr->event_struct_size;
              CAPI_V2_SET_ERROR(result, adsp_result_to_capi_v2_err(custom_event_ptr->event_status));
              continue;
            }

            uint32_t media_format_payload_size = 0;
            if(ADSP_EOK != (result = olm_update_media_fmt(me_ptr, buffer, custom_event_ptr->event_struct_size, &media_format_payload_size)))
            {
              MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Failed to update output media format", me_ptr->capi_v2_olm_identifier);
              buffer = buffer + media_format_payload_size;
              payload_size = payload_size - media_format_payload_size;
              olm_handle_disable_sequence(me_ptr, TRUE);
              return CAPI_V2_EFAILED;
            }

            buffer = buffer + media_format_payload_size;
            payload_size = payload_size - media_format_payload_size;

            if(!capi_v2_olm_is_supported_media_type(me_ptr, &me_ptr->out_media_fmt[0].h , &me_ptr->out_media_fmt[0].f))
            {
            	MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: "
            			"Failed to update output media format with valid values", me_ptr->capi_v2_olm_identifier);
            	olm_handle_disable_sequence(me_ptr, TRUE);
            	return CAPI_V2_EFAILED;
            }

            olm_check_update_sync_mode(me_ptr);

            /* Reallocate Input port data handling resources */
            for(uint32_t port_index =0; port_index < me_ptr->num_active_input_ports; port_index++)
            {
            	/*
            	 *  Allocate number of buffer based on the new frame size
            	 *  Allocate write buffers for data communication with Remote proc
            	 *   */
            	if(ADSP_EOK != (result = olm_alloc_write_data_buffers(me_ptr, port_index)))
            	{
            		MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: event_id = 0x%x OLM Failed to allocate write buffers.",
            				me_ptr->capi_v2_olm_identifier, custom_event_ptr->event_id );
            		olm_handle_disable_sequence(me_ptr, TRUE);
            		return CAPI_V2_ENOMEMORY;
            	}
            }

            uint32_t out_port_idx =0;
            if(ADSP_EOK != (result = olm_alloc_read_data_buffers(me_ptr, out_port_idx)))
            {
              MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Failed to allocate read data buffers", me_ptr->capi_v2_olm_identifier);
              olm_handle_disable_sequence(me_ptr, TRUE);
              return CAPI_V2_ENOMEMORY;
            }

            /*Raise ouput media format event to the Dynamic service*/
            result = olm_raise_output_media_fmt_event(me_ptr);
            if(ADSP_EOK != result)
            {
              MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: failed to raise output media format event ", me_ptr->capi_v2_olm_identifier);
              olm_handle_disable_sequence(me_ptr, TRUE);
              return CAPI_V2_EFAILED;
            }

            /* If all is successful, mark OLM as enabled */
            me_ptr->olm_event_cfg.enable = 1;

            capi_v2_olm_update_raise_kpps_event(me_ptr);
            capi_v2_olm_update_raise_bw_event(me_ptr);
            capi_v2_olm_update_raise_delay_event(me_ptr);
            capi_v2_olm_update_raise_process_event(me_ptr);


            break;
          }
          case AP_EVENT_DISABLE:
          {
            MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Received DISABLE event from Remote", me_ptr->capi_v2_olm_identifier);

            olm_handle_disable_sequence(me_ptr, FALSE);

            buffer = buffer + custom_event_ptr->event_struct_size;
            payload_size = payload_size - custom_event_ptr->event_struct_size;
            break;
          }
          default:
          {
            MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Invaild Custom Event ID - 0x%x.",
                     me_ptr->capi_v2_olm_identifier, custom_event_ptr->event_id);
            buffer = buffer + custom_event_ptr->event_struct_size;
            payload_size = payload_size - custom_event_ptr->event_struct_size;
            break;
          }
        }//switch(event_id)
      }//if param_version is valid
    } //param_id == AP_PARAM_ID_CUSTOM_EVENT
    else if(AP_PARAM_ID_REGISTER_EVENT_RSP == header_ptr->param_id)
    {
      MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Invaild Custom Event ID - 0x%x.",
                        me_ptr->capi_v2_olm_identifier, header_ptr->param_id);
      buffer = buffer + sizeof(ap_server_stat_cmn_header_t);
      buffer = buffer + header_ptr->param_size;
      payload_size = payload_size - (sizeof(ap_server_stat_cmn_header_t)) - header_ptr->param_size;
    }
    else
    {
      /* Unknown event param ID*/
      MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Invaild Event Param ID - 0x%x.",
            me_ptr->capi_v2_olm_identifier, header_ptr->param_id);
      buffer = buffer + sizeof(ap_server_stat_cmn_header_t);
      buffer = buffer + header_ptr->param_size;
      payload_size = payload_size - (sizeof(ap_server_stat_cmn_header_t)) - header_ptr->param_size;
    }

  } //while payload_size > 0

  return result;
}

/**
 * This function is to raise call back events to the Dynamic Service.
 * Based on the opcode of the response, the Dynamic Service would acknowledge
 * the client commands
 *
 * @param[in] me_ptr,          pointer to the OLM structure
 * @param[in] resp_id,         opcode of the response
 * @param[in] resp_ptr,        pointer to the response payload
 * @param[in] actual_data_len, length of the response
 * @param[in] token,           token provided by the Dynamic Service
 *
 * @return none
 */
void olm_response_cb_fn_wrapper(capi_v2_olm_t *me_ptr,
                               capi_v2_olm_resp_id_t resp_id,
                               int8_t *resp_ptr,
                               uint32_t actual_data_len,
                               uint32_t token )
{
  /* Create a common OLM response header */
  capi_v2_olm_resp_info_t cmn_resp_hdr;

  cmn_resp_hdr.token              = token;
  cmn_resp_hdr.payload.data_ptr   = resp_ptr;
  cmn_resp_hdr.payload.actual_data_len = actual_data_len;
  cmn_resp_hdr.payload.max_data_len    = actual_data_len;

  olm_resp_callback_fn_ptr cb_fn_ptr = me_ptr->olm_cfg.dynamic_cfg->olm_resp_cb_info.cb_fn_ptr;
  void *context_ptr                  = me_ptr->olm_cfg.dynamic_cfg->olm_resp_cb_info.context_ptr;
  uint16_t  olm_iid                  = me_ptr->olm_cfg.dynamic_cfg->olm_iid;

  // Call the dynamic service's OLM response call back handler function
  cb_fn_ptr(context_ptr,
            resp_id,
            &cmn_resp_hdr,
            olm_iid);

#ifdef CAPI_V2_OLM_DEBUG
  MSG_4(MSG_SSID_QDSP6, DBG_MED_PRIO,"CAPIv2 OLM 0x%8lX: Raised Response to Dynamic Service for token = %d,"
                                      "olm_iid = %d and size = %d", me_ptr->capi_v2_olm_identifier, token,
                                      olm_iid,actual_data_len);
#endif

}

/**
 * This function is used to fetch the instance ID of a module in the OLM
 * sub graph.
 *
 * @param[in] olm_topo_ptr,    pointer to the OLM sub graph
 * @param[in] module_id,       module ID of the given module
 * @param[in/out] instance_id, pointer to the instance ID of the given module
 *
 * @return ADSPResult, error code
 */
ADSPResult olm_get_instance_id(elite_cmn_olm_topo_db_entry_t *olm_topo_ptr,
                               uint32_t module_id,
                               uint32_t *instance_id)
{
  uint32_t num_modules = olm_topo_ptr->num_modules;

  avcs_module_instance_proc_info_t *modules_list_ptr = olm_topo_ptr->module_info;

  for(uint16_t idx =0; idx < num_modules; idx++)
  {
    if( module_id  == modules_list_ptr->module_id  )
    {
      // IF the modules is present in the topology then return ADSP_EOK.
      *instance_id = modules_list_ptr->instance_id;
      return ADSP_EOK;
    }
    modules_list_ptr++;
  }

  return ADSP_EBADPARAM;
}

/**
 * This function is used to verify if a given module-instance ID pair
 * is present in the OLM sub graph
 *
 * @param[in] olm_topo_ptr,    pointer to the OLM sub graph
 * @param[in] module_id,       module ID of the given module
 * @param[in] instance_id,     instance ID of the given module
 *
 * @return TRUE or FALSE
 */
bool_t olm_check_if_module_present(elite_cmn_olm_topo_db_entry_t *olm_topo_ptr,
                                   uint32_t module_id,
                                   uint32_t instance_id)
{

  uint32_t num_modules = olm_topo_ptr->num_modules;

  avcs_module_instance_proc_info_t *modules_list_ptr = olm_topo_ptr->module_info;

  for(uint16_t idx =0; idx < num_modules; idx++)
  {
    if( module_id  == modules_list_ptr->module_id &&
        instance_id   == modules_list_ptr->instance_id )
    {
      // IF the modules is present in the topology then return true.
      return TRUE;
    }
    modules_list_ptr++;
  }

  return FALSE;
}

/* This function needs to be updated where there is common shared
 * memory between APPS - ADSP - Remote Processors */
ADSPResult olm_get_client_shm_mem_handle(uint32_t client_proc_id,
                                       uint32_t  in_mem_map_handle,
                                       uint32_t  in_addr_lsw,
                                       uint32_t  in_addr_msw,
                                       uint32_t  *out_mem_map_handle,
                                       uint32_t  *out_addr_lsw,
                                       uint32_t  *out_addr_msw )
{
  return ADSP_EFAILED;
}

/**
 * This function is used to fetch the remote AP Static Service address for the
 * OLM instance
 *
 * @param[in] me_ptr,              pointer to the OLM structure
 * @param[in/out] server_address,  pointer to Remote AP Static Service APR Address
 *
 * @return ADSPResult, error code
 */
ADSPResult olm_apr_get_remote_svc_addr(capi_v2_olm_t *me_ptr, uint16_t *server_address)
{
  ADSPResult result = ADSP_EOK;
  char ap_svc_name[100];
  uint32_t remote_proc_id = me_ptr->remote_proc_id;
  uint32_t svc_name_size  = strlen(proc_to_svc_name_map[remote_proc_id-1]);

  strlcpy(ap_svc_name, proc_to_svc_name_map[remote_proc_id-1], svc_name_size +1);

#ifdef CAPI_V2_OLM_DEBUG
  MSG_5(MSG_SSID_QDSP6, DBG_LOW_PRIO, "CAPIv2 OLM 0x%8lX: Remote Processor ID: %lu'proc_to_svc_name_map %s,"
                                       " ap_svc_name %s, ap_svc_name_size %lu ",
                                       me_ptr->olm_id, remote_proc_id,
                                       proc_to_svc_name_map[remote_proc_id-1],
                                       ap_svc_name , svc_name_size);
#endif

  if (ADSP_FAILED( result = elite_apr_if_lookup_addr_by_name(ap_svc_name, svc_name_size, (elite_apr_addr_t *)server_address)) )
  {
    MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Failed to look up remote static service address for %s with result =0x%x",
    		                                   me_ptr->capi_v2_olm_identifier , ap_svc_name, result);
    return result;
  }

  return result;
}

/**
 * This function is used to dynamically register the OLM instance with APR
 *
 * @param[in] me_ptr,              pointer to the OLM structure
 *
 * @return ADSPResult, error code
 */
ADSPResult olm_apr_register(capi_v2_olm_t *me_ptr)
{
  ADSPResult result           = ADSP_EOK;
  uint16_t   remote_serv_addr = 0;

  /* register OLM with APR and pass the return handle and return Address pointers */
  /* Set input name pointer to NULL for dynamic registration */
  if (ADSP_FAILED( result = elite_apr_if_register_by_name( &me_ptr->apr_handle,
                                                           &me_ptr->apr_addr,
                                                           NULL, 0,
                                                           &remote_response_apr_dispatch_fn,
                                                           me_ptr)) )
  {
    MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Failed to register with APR with result 0x%8x",
                                           me_ptr->capi_v2_olm_identifier, result);
    return result;
  }

  /* Fetch the address of the remote static service */
  result = olm_apr_get_remote_svc_addr(me_ptr, &remote_serv_addr);
  if(ADSP_FAILED(result))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Failed to get remote static service address with result = 0x%8x", result);
    return result;
  }
  me_ptr->remote_svc_apr_addr = remote_serv_addr;

#ifdef CAPI_V2_OLM_DEBUG
  MSG_3(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "CAPIv2 OLM 0x%8lX: APR Registration successful remote_server_addr = %lu olm_apr_addr: %lu",
                                        me_ptr->olm_id,me_ptr->remote_svc_apr_addr,me_ptr->apr_addr);
#endif

  return result;
}

/**
 * This function is used to update the output media format in the OLM structures
 *
 * @param[in] me_ptr,            pointer to the OLM structure
 * @param[in] payload,           pointer to the payload with the media format info
 * @param[in] param_struct_size, size of the payload
 *
 * @return ADSPResult, error code
 */
ADSPResult olm_update_media_fmt(capi_v2_olm_t *me_ptr, int8_t* payload, uint16_t param_struct_size, uint32_t *payload_size)
{
  uint32_t out_port_index =0;

  ap_container_event_output_media_format_v1_t *fmt_type_ptr = (ap_container_event_output_media_format_v1_t*)payload;
  payload += param_struct_size;
  *payload_size += param_struct_size;

  capi_v2_olm_media_fmt_t *out_mf_payload = &me_ptr->out_media_fmt[out_port_index];

  out_mf_payload->f.minor_version = me_ptr->in_media_fmt[0].f.minor_version;

  if( AP_PARAM_ID_COMPRESSED_MEDIA_FORMAT == fmt_type_ptr->event_param_id &&
      AP_PARAM_COMPRESSED_MEDIA_FORMAT_VERSION <= fmt_type_ptr->payload_version &&
      0 != fmt_type_ptr->payload_version)
  {
    ap_container_compr_fmt_blk_v1_t *compr_fmt_ptr = (ap_container_compr_fmt_blk_v1_t *) payload;

    /* Init header*/
    out_mf_payload->h.data_format =  CAPI_V2_IEC61937_PACKETIZED;

    /* Init format data*/
    out_mf_payload->f.bitstream_format = compr_fmt_ptr->media_format;
    out_mf_payload->f.sampling_rate    = compr_fmt_ptr->sample_rate;
    out_mf_payload->f.bits_per_sample  = compr_fmt_ptr->bits_per_sample;
    out_mf_payload->f.num_channels     = compr_fmt_ptr->num_channels;

#ifdef CAPI_V2_OLM_DEBUG
    MSG_5(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "CAPIv2 OLM 0x%8lX: update OUTPUT_MEDIA_FORMAT event. num_channels= 0x%lu, sample_rate = %lu, bits_per_sample = %lu, media_format = 0x%x",
           me_ptr->capi_v2_olm_identifier, compr_fmt_ptr->num_channels, compr_fmt_ptr->sample_rate, compr_fmt_ptr->bits_per_sample, compr_fmt_ptr->media_format);
#endif

    olm_set_reset_bitmask(&me_ptr->is_output_mf_rcvd_mask, compr_fmt_ptr->port_index, TRUE);
    *payload_size += fmt_type_ptr->payload_struct_size;

  }
  else if(AP_PARAM_ID_MCH_PCM_MEDIA_FORMAT == fmt_type_ptr->event_param_id &&
          AP_PARAM_MCH_PCM_MEDIA_FORMAT_VERSION <= fmt_type_ptr->payload_version &&
            0 != fmt_type_ptr->payload_version)
  {
    ap_container_mch_pcm_fmt_blk_v1_t *pcm_fmt_ptr = (ap_container_mch_pcm_fmt_blk_v1_t *) payload;

    /* Init header*/
    out_mf_payload->h.data_format =  CAPI_V2_FIXED_POINT;

    /* Init format data*/
    out_mf_payload->f.bitstream_format = pcm_fmt_ptr->media_format;
    out_mf_payload->f.num_channels     = pcm_fmt_ptr->num_channels;
    out_mf_payload->f.bits_per_sample  = (16 == pcm_fmt_ptr->bits_per_sample) ? 16: 32;
    out_mf_payload->f.sampling_rate    = pcm_fmt_ptr->sample_rate;
    out_mf_payload->f.data_is_signed   = pcm_fmt_ptr->is_signed;
    out_mf_payload->f.data_interleaving= pcm_fmt_ptr->is_interleaved ? CAPI_V2_INTERLEAVED: CAPI_V2_DEINTERLEAVED_UNPACKED;
    out_mf_payload->f.q_factor 		     = pcm_fmt_ptr->q_format;

#ifdef CAPI_V2_OLM_DEBUG
    MSG_8(MSG_SSID_QDSP6, DBG_HIGH_PRIO, CAPIv2 OLM 0x%8lX: Received OUTPUT_MEDIA_FORMAT event. num_channels= 0x%lu, sample_rate = %lu, bits_per_sample = %lu, media_format = 0x%x, is_signed = %lu, is_interleaved = %lu, qformat = %lu",
          me_ptr->capi_v2_olm_identifier, pcm_fmt_ptr->num_channels, pcm_fmt_ptr->sample_rate,
          pcm_fmt_ptr->bits_per_sample, pcm_fmt_ptr->media_format,
          pcm_fmt_ptr->is_signed,pcm_fmt_ptr->is_interleaved, pcm_fmt_ptr->q_format );
#endif

    for(int i =0; i <out_mf_payload->f.num_channels ; i++ )
    {
      out_mf_payload->f.channel_type[i] = pcm_fmt_ptr->channel_mapping[i];
    }
    olm_set_reset_bitmask(&me_ptr->is_output_mf_rcvd_mask, pcm_fmt_ptr->port_index, TRUE);
    *payload_size += fmt_type_ptr->payload_struct_size;
  }
  else
  {
	  *payload_size += fmt_type_ptr->payload_struct_size;
	  MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Received invalid event param ID 0x%x or unsupported payload version 0x%x",
                                          me_ptr->capi_v2_olm_identifier, fmt_type_ptr->event_param_id, fmt_type_ptr->payload_version);
    return ADSP_EBADPARAM;
  }

  return ADSP_EOK;

}

/**
 * This function is used to raise the output media format from OLM to the
 * Dynamic Service
 *
 * @param[in] me_ptr,            pointer to the OLM structure
 * @param[in] payload,           double pointer to the payload with the media format info
 * @param[in] payload_size,      size of the payload
 * @param[in] param_struct_size, size of the param structure
 *
 * @return ADSPResult, error code
 */
ADSPResult olm_raise_output_media_fmt_event(capi_v2_olm_t *me_ptr)
{
  ADSPResult result = ADSP_EOK;

  if(NULL == me_ptr->event_callback_info.event_cb)
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Event callback is not set. Unable to raise events!", me_ptr->capi_v2_olm_identifier);
    return ADSP_EFAILED;
  }


  capi_v2_olm_media_fmt_t out_mf_payload;

  memscpy(&out_mf_payload, sizeof(capi_v2_olm_media_fmt_t),&me_ptr->out_media_fmt[0],sizeof(capi_v2_olm_media_fmt_t) );

  capi_v2_event_info_t event_info;
  event_info.port_info.is_valid      = TRUE;
  event_info.port_info.is_input_port = FALSE;
  event_info.port_info.port_index    = 0;
  event_info.payload.actual_data_len = event_info.payload.max_data_len = sizeof(out_mf_payload);
  event_info.payload.data_ptr        = reinterpret_cast<int8_t*>(&out_mf_payload);

  result = me_ptr->event_callback_info.event_cb( me_ptr->event_callback_info.event_context,
                                                 CAPI_V2_EVENT_OUTPUT_MEDIA_FORMAT_UPDATED_V2,
                                                 &event_info );
  if (CAPI_V2_FAILED(result))
  {
    MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO,
          "CAPIv2 OLM 0x%8lX: Failed to send output media format event"
        "with result %lu", me_ptr->capi_v2_olm_identifier, result);
  }
#ifdef CAPI_V2_OLM_DEBUG
  MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO,
            "CAPIv2 OLM 0x%8lX: Raised output media format event successully",me_ptr->capi_v2_olm_identifier);
#endif

  return result;
}

/**
 * This function is used to calculate the number of shared memory buffers
 * between OLM & Remote Container
 *
 * @param[in] me_ptr,     pointer to the OLM structure
 * @param[in] cmd_type,   type of data command (READ/WRITE)
 * @param[in] port_index, index of the input/output
 *
 * @return none
 */
void olm_update_num_buffers(capi_v2_olm_t *me_ptr,
                            olm_data_cmd_type_t cmd_type,
                            uint32_t port_index )
{
  /* Get the frame size in num frames  */
  uint32_t rmt_svc_frm_size = me_ptr->remote_num_frames;
  uint32_t olm_frm_size = me_ptr->olm_num_frames;
  uint32_t new_num_bufs = 0;

  if(WRITE_CMD == cmd_type)
  {
    /* For sync mode, one buffer is enough */
    if(TRUE == me_ptr->sync_mode)
    {
      new_num_bufs = 1;
    }
    else
    {
      /* ceil(Remote frame size/OLM Frame size) + 1 * is_le(OLM frame size, 2*IPC latency) +
       * 1 (for jitter if frame sizes are different)
       */
      new_num_bufs = ((rmt_svc_frm_size + (olm_frm_size - 1) ) / olm_frm_size) +
          1 * (olm_frm_size <= 2 * IPC_LATENCY_IN_NUM_FRAMES) +
          1 * (rmt_svc_frm_size != olm_frm_size);
    }

    me_ptr->write_buf_pool[port_index].num_bufs = new_num_bufs;
  }
  else
  {
    /* For sync mode, one buffer is enough */
    if(TRUE == me_ptr->sync_mode)
    {
      new_num_bufs = 1;
    }
    else
    {
      /*  Ceil (Remote frame size/ OLM frame size) + 1 * is_le(OLM frame size, 2*IPC latency) + 1 */
      new_num_bufs =  ((rmt_svc_frm_size + (2 * olm_frm_size - 1) ) / olm_frm_size) +
          1 * (olm_frm_size <= 2 * IPC_LATENCY_IN_NUM_FRAMES) +
          1 * (rmt_svc_frm_size != olm_frm_size);;
    }

    me_ptr->read_buf_pool[port_index].num_bufs = new_num_bufs;
  }

  /* During the first media format we adjust the OLM frame-size to ensure the num_buf < OLM_WRITE_BUF_Q_ELEMENTS_MAX*/
  if((new_num_bufs > (OLM_WRITE_BUF_Q_ELEMENTS_MAX-1)) && (me_ptr->is_olm_instance_created==FALSE)&&(WRITE_CMD == cmd_type))
  {
	  do
	  {
		  olm_frm_size = olm_frm_size * 2;
		  new_num_bufs = ((rmt_svc_frm_size + (olm_frm_size - 1) ) / olm_frm_size) +
				  	  	  1 * (olm_frm_size <= 2 * IPC_LATENCY_IN_NUM_FRAMES) +
						  1 * (rmt_svc_frm_size != olm_frm_size);

	  }while(new_num_bufs < (OLM_WRITE_BUF_Q_ELEMENTS_MAX-1));

	  me_ptr->olm_num_frames = olm_frm_size;
	  me_ptr->write_buf_pool[port_index].num_bufs = new_num_bufs;
  }

}

/**
 * This function is to create read or write data response queues
 *
 * @param[in] me_ptr,      pointer to OLM module structure
 * @param[in] cmd_type,    command type (WRITE_CMD or READ_CMD)
 * @param[in] port_index,  index of the input/output port
 *
 * @return ADSPResult, error code
 */
ADSPResult olm_create_queues(capi_v2_olm_t *me_ptr,
		olm_data_cmd_type_t cmd_type,
		uint32_t port_index)
{
	ADSPResult           result = ADSP_EOK;
	char                 data_q_name[16];
	char                 *olm_iid_ptr = (char*)&me_ptr->olm_cfg.dynamic_cfg->olm_iid;
	qurt_elite_queue_t   *q_temp_ptr = NULL;

	if(WRITE_CMD == cmd_type && port_index >=  me_ptr->num_active_input_ports)
	{
		MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Invalid port index 0x%x ",me_ptr->capi_v2_olm_identifier, port_index);
		return ADSP_EFAILED;
	}

	if(READ_CMD == cmd_type && port_index >=  me_ptr->num_active_output_ports)
	{
		MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Invalid port index 0x%x ",me_ptr->capi_v2_olm_identifier, port_index);
		return ADSP_EFAILED;
	}

	if(WRITE_CMD == cmd_type)
	{
		q_temp_ptr = (qurt_elite_queue_t *)(&me_ptr->wr_rsp_q_buf[port_index][0]);
		qurt_elite_strl_cpy(data_q_name,"olm_00_wrdq_p00", sizeof(data_q_name));
	}
	else
	{
		q_temp_ptr = (qurt_elite_queue_t *)(&me_ptr->rd_rsp_q_buf[port_index][0]);
		qurt_elite_strl_cpy(data_q_name,"olm_00_rdq_p00", sizeof(data_q_name));
	}

	data_q_name[4] = olm_iid_ptr[1];
	data_q_name[5] = olm_iid_ptr[0];
	data_q_name[13] =  '0' + port_index;

	//todo :: check for num_q_elements

	/* Create a new queue only if the new Queue size is greater than the old queue size */
	if( (WRITE_CMD == cmd_type && NULL == me_ptr->wr_rsp_q_ptr[port_index]) ||
			(READ_CMD  == cmd_type && NULL == me_ptr->rd_rsp_q_ptr[port_index]) )
	{

		result = qurt_elite_queue_init(data_q_name,
									   OLM_WRITE_BUF_Q_ELEMENTS_MAX,
									   q_temp_ptr);
		if (ADSP_EOK != result)
		{
			MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: data Q Creation Failed for port index %d", me_ptr->capi_v2_olm_identifier, port_index);
			return result;
		}

		if(WRITE_CMD == cmd_type )
		{
			me_ptr->wr_rsp_q_ptr[port_index] = q_temp_ptr;

			/*Allocate memory for the write done Channel*/
			me_ptr->wr_done_channel_ptr[port_index] =
					(qurt_elite_channel_t *) qurt_elite_memory_malloc(sizeof(qurt_elite_channel_t),QURT_ELITE_HEAP_DEFAULT);

			if(NULL == me_ptr->wr_done_channel_ptr[port_index])
			{
				MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: write channel Creation Failed"
						" for port index %d",me_ptr->capi_v2_olm_identifier, port_index);
				return ADSP_ENOMEMORY;
			}

			/* Intialize the channel*/
			qurt_elite_channel_init(me_ptr->wr_done_channel_ptr[port_index]);

			result = qurt_elite_channel_addq(me_ptr->wr_done_channel_ptr[port_index], me_ptr->wr_rsp_q_ptr[port_index], WR_CHAN_BIT_MASK);
			if(ADSP_EOK != result)
			{
				MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Failed to attach write Q "
						"to Channel for port index %d", me_ptr->capi_v2_olm_identifier, port_index);
				return result;
			}
		}
		else
		{
			me_ptr->rd_rsp_q_ptr[port_index] = q_temp_ptr;

			/*Allocate memory for the read done Channel*/
			me_ptr->rd_done_channel_ptr[port_index] =
					(qurt_elite_channel_t *) qurt_elite_memory_malloc(sizeof(qurt_elite_channel_t),	QURT_ELITE_HEAP_DEFAULT);

			if(NULL == me_ptr->rd_done_channel_ptr[port_index])
			{
				MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: read channel creation Failed for port index %d",
						me_ptr->capi_v2_olm_identifier, port_index);
				return ADSP_ENOMEMORY;
			}

			/* Intialize the channel*/
			qurt_elite_channel_init(me_ptr->rd_done_channel_ptr[port_index]);

			result = qurt_elite_channel_addq(me_ptr->rd_done_channel_ptr[port_index], me_ptr->rd_rsp_q_ptr[port_index], RD_CHAN_BIT_MASK);
			if(ADSP_EOK != result)
			{
				MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Failed to attach read Q to"
						" Channel for port index %d", me_ptr->capi_v2_olm_identifier, port_index);
			}
		}

	}
	return result;
}

/**
 * This function is to destroy read or write data response queues
 *
 * @param[in] me_ptr,      pointer to OLM module structure
 * @param[in] cmd_type,    command type (WRITE_CMD or READ_CMD)
 * @param[in] port_index,  index of the input/output port
 *
 * @return none
 */
void olm_destroy_queues(capi_v2_olm_t *me_ptr, olm_data_cmd_type_t cmd_type, uint32_t port_index)
{
  if(WRITE_CMD == cmd_type)
  {
    if(NULL == me_ptr)
    {
      MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM : Received invalid instance ptr");
      return;
    }
    if(port_index >=  me_ptr->num_active_input_ports)
    {
      MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Invalid port index 0x%x ",
            me_ptr->capi_v2_olm_identifier, port_index);
      return;
    }

    if(NULL != me_ptr->wr_rsp_q_ptr[port_index])
    {
      while(1)
      {
        elite_msg_any_t msg;
        ADSPResult result = qurt_elite_queue_pop_front(me_ptr->wr_rsp_q_ptr[port_index],(uint64_t*)&msg);
        if(result == ADSP_ENEEDMORE)
        {
          break;
        }

        if(result == ADSP_EOK)
        {
          if(ELITE_APR_PACKET == msg.unOpCode)
          {
            elite_apr_if_free(me_ptr->apr_handle, (elite_apr_packet_t*)(msg.pPayload));
          }
          else //No other msg type supported
          {

          }
        }
      } //while(1)
      qurt_elite_queue_deinit(me_ptr->wr_rsp_q_ptr[port_index]);
    }
    if(NULL != me_ptr->wr_done_channel_ptr[port_index])
    {
    	qurt_elite_channel_destroy(me_ptr->wr_done_channel_ptr[port_index]);
    	qurt_elite_memory_free(me_ptr->wr_done_channel_ptr[port_index]);
    }

  } //if WRITE_CMD
  else
  {
    if(NULL == me_ptr)
    {
      MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM : Received invalid instance ptr");
      return;
    }
    if(port_index >=  me_ptr->num_active_output_ports)
    {
      MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Invalid port index 0x%x ",
            me_ptr->capi_v2_olm_identifier, port_index);
      return;
    }

    if(NULL != me_ptr->rd_rsp_q_ptr[port_index])
    {
      while(1)
      {
        elite_msg_any_t msg;
        ADSPResult      result = qurt_elite_queue_pop_front(me_ptr->rd_rsp_q_ptr[port_index],(uint64_t*)&msg);
        if(result == ADSP_ENEEDMORE)
        {
          break;
        }

        if(result == ADSP_EOK)
        {
          if(ELITE_APR_PACKET == msg.unOpCode)
          {
            elite_apr_if_free(me_ptr->apr_handle, (elite_apr_packet_t*)(msg.pPayload));
          }
          else  //No other msg type supported
          {

          }
        }
      } //while(1)
      qurt_elite_queue_deinit(me_ptr->rd_rsp_q_ptr[port_index]);
    }
    if(NULL != me_ptr->rd_done_channel_ptr[port_index])
    {
      qurt_elite_channel_destroy(me_ptr->rd_done_channel_ptr[port_index]);
      qurt_elite_memory_free(me_ptr->rd_done_channel_ptr[port_index]);
    }
  }//if READ_CMD
}

/**
 * This function is to handle disable of the OLM module in case of irrecoverable failures
 *
 * @param[in] me_ptr,         pointer to OLM module structure
 * @param[in] is_olm_trigger, indicates if the disable was initiated by OLM/Remote Service
 *
 * @return none
 */
void olm_handle_disable_sequence(capi_v2_olm_t *me_ptr, bool_t is_olm_triggered)
{

  MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "CAPIv2 OLM 0x%8lX: Processing disable sequence", get_capi_v2_olm_identifier(me_ptr));

  /* Do a Algo Reset of OLM to clean up buffer states */
  (void)capiv2_olm_reset(me_ptr);

  //RR: Check the state of is_olm_instance_created here once media format handling is refactored.

  /* If disable is initiated by OLM, send the event to Remote */
  if(is_olm_triggered)
  {
    olm_send_disable_event(me_ptr);
  }

  me_ptr->olm_event_cfg.enable = 0;

  capi_v2_olm_update_raise_process_event(me_ptr);
}

/**
 * This function is to free any used command handles during OLM End
 *
 * @param[in] me_ptr,         pointer to OLM module structure
 *
 * @return none
 */
void olm_check_free_cmd_handles(capi_v2_olm_t * me_ptr)
{
  olm_cmd_handle_t *cmd_hndls = me_ptr->cmd_hndls;

  for(uint32_t i = 0 ; i < CMD_HANDLES_MAX_ARRAY_SIZE ; i++ )
  {
    if(TRUE == cmd_hndls[i].is_used)
    {
      switch(cmd_hndls[i].cmd)
      {
        case CAPI_V2_PARAM_ID_OLM_SETPARAM:
        {
          if(cmd_hndls[i].payload)
          {
            olm_setparam_cmd_handle_t *set_param_hdl = (olm_setparam_cmd_handle_t*)cmd_hndls[i].payload;

            /* Return the set param command response to dynamic service*/
            capi_v2_olm_setparam_resp_t setp_resp;

            /* Copy the result from remote response message*/
            setp_resp.result = ADSP_EFAILED;

            olm_response_cb_fn_wrapper(me_ptr,
                                      CAPI_V2_OLM_RESP_SETPARAM,
                                      (int8_t *)&setp_resp,
                                      sizeof(capi_v2_olm_setparam_resp_t),
                                      cmd_hndls[i].token);

            if(set_param_hdl->shm_mem_ptr)
            {
              elite_mem_mdf_mem_free(set_param_hdl->shm_mem_ptr,
                                     set_param_hdl->mem_map_hdl,
                                     set_param_hdl->shm_alloc_size);
            }

            qurt_elite_memory_free(set_param_hdl);
            cmd_hndls[i].is_used = FALSE;
          }
          break;
        }
        case CAPI_V2_PARAM_ID_SET_OLM_INF_EXTN_MODULE_CONFIG:
        {
          if(cmd_hndls[i].payload)
          {
            olm_setparam_cmd_handle_t *set_param_hdl = (olm_setparam_cmd_handle_t*)cmd_hndls[i].payload;

            if(set_param_hdl->shm_mem_ptr)
            {
              elite_mem_mdf_mem_free(set_param_hdl->shm_mem_ptr,
                                     set_param_hdl->mem_map_hdl,
                                     set_param_hdl->shm_alloc_size);
            }

            qurt_elite_memory_free(set_param_hdl);
            cmd_hndls[i].is_used = FALSE;
          }
          break;
        }
        case CAPI_V2_PARAM_ID_OLM_GETPARAM:
        {
          if(cmd_hndls[i].payload)
          {
            olm_getparam_cmd_handle_t *get_param_hdl = (olm_getparam_cmd_handle_t*)cmd_hndls[i].payload;

            /* Send the get param response to the dynamic service thread */
            capi_v2_olm_getparam_resp_t getp_rsp_info;

            /* Update the fields based on the response packet */
            getp_rsp_info.result    = ADSP_EFAILED;
            getp_rsp_info.data_size = 0;
            getp_rsp_info.version   = 0;
            getp_rsp_info.data_ptr  = NULL;

            olm_response_cb_fn_wrapper(me_ptr,
                                      CAPI_V2_OLM_RESP_GETPARAM,
                                      (int8_t*)&getp_rsp_info,
                                      sizeof(capi_v2_olm_getparam_resp_t),
                                      cmd_hndls[i].token);

            if(get_param_hdl->shm_mem_ptr)
            {
              elite_mem_mdf_mem_free(get_param_hdl->shm_mem_ptr,
                                     get_param_hdl->mem_map_hdl,
                                     get_param_hdl->shm_alloc_size);
            }

            qurt_elite_memory_free(get_param_hdl);
            cmd_hndls[i].is_used = FALSE;
          }
          break;
        }
        default:
        {
          MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Unexpected command opcode 0x%x.",me_ptr->capi_v2_olm_identifier, cmd_hndls[i].cmd);
          break;
        }
      } // switch (cmd_opcode)
    } // if cmd hdl in use
  } // for loop over array
}
