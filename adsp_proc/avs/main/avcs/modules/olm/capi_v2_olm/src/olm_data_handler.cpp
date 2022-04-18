/**
@file olm_data_handler.cpp

@brief This file contains the data handling functionality for Off-loading module

 */

/*========================================================================

Edit History

when          who            what, where, why
--------      ---            -------------------------------------------------------
11/27/2017    bvodapal       Initial version (moved the data handling code from olm_utils)

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

/**
 * This function is used to calculate the buffering delay for OLM
 *
 * @param[in] me_ptr, pointer to the CAPI lib
 * @param[in] cmd_type, type of command
 * @param[in] port_index, index of the port
 *
 * @return uint64_t, delay in us
 */
uint64_t get_buf_delay(capi_v2_olm_t *me_ptr, olm_data_cmd_type_t cmd_type, uint32_t port_index)
{

  uint64_t delay_in_us = 0;
  uint32_t buf_size, num_buffers;
  uint32_t delay_in_samples, bytes_per_sample;
  capi_v2_standard_data_format_v2_t *media_fmt_ptr = NULL;
  if(WRITE_CMD == cmd_type)
  {
    buf_size = me_ptr->write_buf_pool[port_index].buf_size;
    media_fmt_ptr = &me_ptr->in_media_fmt[port_index].f; //RR: Do we need check if media format was received?
    num_buffers = (me_ptr->write_buf_pool[port_index].num_bufs);
  }
  else //READ command
  {
    buf_size = me_ptr->read_buf_pool[port_index].buf_size;
    media_fmt_ptr = &me_ptr->out_media_fmt[port_index].f;
    num_buffers = (me_ptr->read_buf_pool[port_index].num_bufs - 1);
  }

  /* Calculation of delay per data buffer */
  bytes_per_sample = bits_per_sample_2_bytes_per_sample(media_fmt_ptr->bits_per_sample);
  delay_in_samples = buf_size/(media_fmt_ptr->num_channels * bytes_per_sample);
  delay_in_us = (delay_in_samples * 1000000)/media_fmt_ptr->sampling_rate;

  /* Total delay is number of buffers * delay per buffer */
  return (delay_in_us * num_buffers);
}

/**
 * This function is used identify if one of the buffers in OLM
 * needs to be deprecated
 *
 * @param[in] data_buf_ptr, pointer to the buffer
 * @param[in] cmd_type, type of command
 *
 * @return TRUE or FALSE,
 */
bool_t is_deprecated_buffer(void *data_buf_ptr, olm_data_cmd_type_t cmd_type)
{
  olm_write_buf_t *wr_buf_ptr = NULL;
  olm_read_buf_t *rd_buf_ptr = NULL;

  if(WRITE_CMD == cmd_type)
  {
    wr_buf_ptr = (olm_write_buf_t*) data_buf_ptr;
    return wr_buf_ptr->is_deprecated;
  }

  // Else it is read buffer
  rd_buf_ptr = (olm_read_buf_t*) data_buf_ptr;
  return rd_buf_ptr->is_deprecated;
}

/**
 * This function removes deprecated write buffer from the
 * buffer pool list and deallocates the memory
 *
 * @param[in] me_ptr pointer to OLM module structure
 * @param[in] dep_buf_ptr node pointer
 * @param[in] port_index index of the input port
 *
 * @return ADSPResult, error code
 */
ADSPResult olm_remove_deprecated_write_buffer(capi_v2_olm_t *me_ptr, olm_write_buf_t *dep_buf_ptr, uint32_t port_index)
{
  olm_write_buf_t *prev_buf_ptr = NULL;
  olm_write_buf_t *cur_buf_ptr = (olm_write_buf_t*)me_ptr->write_buf_pool[port_index].buf_list_head_ptr;

  /*Find the node is in the list*/
  while((dep_buf_ptr != cur_buf_ptr) && (cur_buf_ptr != NULL))
  {
    prev_buf_ptr = cur_buf_ptr;
    cur_buf_ptr = cur_buf_ptr->next;
  }

	if(cur_buf_ptr == NULL || prev_buf_ptr == NULL)
	{
		//todo : add message
		return ADSP_EFAILED;
	}

  /* Check if the deprecated buffer is the head of the list */
  if(cur_buf_ptr == me_ptr->write_buf_pool[port_index].buf_list_head_ptr)
  {
    //change the head to next node
    me_ptr->write_buf_pool[port_index].buf_list_head_ptr = cur_buf_ptr->next;
  }
  else
  {
    /* Remove current node from the list */
    prev_buf_ptr->next = cur_buf_ptr->next;
  }

  /*Remove node from the list*/
  cur_buf_ptr->next = NULL;
  me_ptr->write_buf_pool[port_index].buf_list_size--;

  //Deallocate the shared buffer memory
  if( NULL != cur_buf_ptr->data_buf_ptr)
  {
    elite_mem_mdf_mem_free(cur_buf_ptr->data_buf_ptr,
                           cur_buf_ptr->data_write_buf.mem_map_handle,
                           cur_buf_ptr->data_buf_size);
  }

  /* Deallocate the buffer node*/
  qurt_elite_memory_free(cur_buf_ptr);

  return ADSP_EOK;
}

/**
 * This function removes deprecated read buffer from the
 * buffer pool list and deallocates the memory
 *
 * @param[in] me_ptr pointer to OLM module structure
 * @param[in] dep_buf_ptr node pointer
 * @param[in] port_index index of the output port
 *
 * @return ADSPResult, error code
 */
ADSPResult olm_remove_deprecated_read_buffer(capi_v2_olm_t *me_ptr, olm_read_buf_t *dep_buf_ptr, uint32_t port_index)
{
  olm_read_buf_t *prev_buf_ptr = NULL;
  olm_read_buf_t *cur_buf_ptr = (olm_read_buf_t*)me_ptr->read_buf_pool[port_index].buf_list_head_ptr;

  /*Find the node is in the list*/
  while((dep_buf_ptr != cur_buf_ptr) && (cur_buf_ptr !=NULL))
  {
    prev_buf_ptr = cur_buf_ptr;
    cur_buf_ptr = cur_buf_ptr->next;
  }

  if(cur_buf_ptr == NULL || prev_buf_ptr == NULL)
	{
		//todo : add message
		return ADSP_EFAILED;
	}

  /* Check if the deprecated buffer is the head of the list */
  if(cur_buf_ptr == me_ptr->read_buf_pool[port_index].buf_list_head_ptr)
  {
    //change the head to next node
    me_ptr->read_buf_pool[port_index].buf_list_head_ptr = cur_buf_ptr->next;
  }
  else
  {
    /* Remove current node from the list */
    prev_buf_ptr->next = cur_buf_ptr->next;
  }

  /*Remove node from the list*/
  cur_buf_ptr->next = NULL;
  me_ptr->read_buf_pool[port_index].buf_list_size--;

  //Deallocate the shared buffer memory
  if( NULL != cur_buf_ptr->data_buf_ptr)
  {
    elite_mem_mdf_mem_free(cur_buf_ptr->data_buf_ptr,
                           cur_buf_ptr->data_read_buf.mem_map_handle,
                           cur_buf_ptr->data_buf_size);
  }

  /* Deallocate the buffer node*/
  qurt_elite_memory_free(cur_buf_ptr);

  return ADSP_EOK;
}

/**
 * This function sends the data command to the remote service
 *
 * @param[in] me_ptr pointer to OLM module structure
 * @param[in] data_buf_ptr pointer to OLM data buf pool node
 * @param[in] cmd_type type of the command
 *
 * @return ADSPResult, error code
 */
ADSPResult olm_send_data_cmd(capi_v2_olm_t *me_ptr, void *data_buf_ptr, olm_data_cmd_type_t cmd_type)
{
  ADSPResult result = ADSP_EOK;

  uint32_t payload_size = 0;
  uint32_t token;
  uint32_t param_size = 0;
  uint32_t port_index =0;

  olm_write_buf_t *wr_buf_ptr = NULL;
  olm_read_buf_t *rd_buf_ptr = NULL;

  payload_size = sizeof(ap_server_stat_cmn_header_t);

  if(WRITE_CMD == cmd_type)
  {
    wr_buf_ptr = (olm_write_buf_t *)data_buf_ptr;
#ifdef OLM_DATA_PATH_LATENCY_MEASUREMENT
    detect_random_sample_olm_write(me_ptr, wr_buf_ptr->data_buf_ptr,wr_buf_ptr->fill_size_per_ch );
#endif
    if(ADSP_EOK != (result = qurt_elite_memorymap_cache_flush((uint32_t)wr_buf_ptr->data_buf_ptr,
                                                              wr_buf_ptr->data_buf_size)))
    {
      MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Flush Cache failed"
                                            "with result 0x%x", me_ptr->capi_v2_olm_identifier,
                                            result);
      return result;
    }
    param_size = sizeof(ap_container_data_write_buffer_v1_t);
    token = wr_buf_ptr->token;
  }
  else
  {
    rd_buf_ptr = (olm_read_buf_t *)data_buf_ptr;

    /* reallocate the buffer if the size is changed */
    if(ADSP_EOK != (result = olm_realloc_read_data_buffer(me_ptr, rd_buf_ptr, port_index)))
    {
      MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Failed to reallocate "
                                           "read buffer for port index %d with result 0x%x ",
                                           me_ptr->capi_v2_olm_identifier, port_index, result);
      return result;
    }

    param_size = sizeof(ap_container_data_read_param_v1_t);
    token = rd_buf_ptr->token;
  }

  payload_size += param_size;

  /* Allocate APR set param packet*/
  elite_apr_packet_t *elite_pkt_ptr = NULL;

  /* Send the packet to the remote server */
  result = elite_apr_if_alloc_cmd(me_ptr->apr_handle,
                                  me_ptr->apr_addr,
                                  me_ptr->olm_cfg.dynamic_cfg->olm_iid,
                                  me_ptr->create_resp_info.container_apr_addr,
                                  DEFAULT_OLM_AP_SESSION_PORT,
                                  token,
                                  AP_CMD_DATA,
                                  payload_size,
                                  &elite_pkt_ptr);
  if(ADSP_FAILED(result))
  {
    MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Could not allocate apr packet with error 0x%x ",
                                          me_ptr->capi_v2_olm_identifier, result);
    return result;
  }

  /* Get remote command payload pointer in the packet*/
  uint8_t *payload_ptr = (uint8_t*)elite_apr_if_get_payload_ptr(elite_pkt_ptr);
  if(NULL == payload_ptr)
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Data Command had NULL payload in apr packet",
                                              me_ptr->capi_v2_olm_identifier);
    elite_apr_if_free(me_ptr->apr_handle, elite_pkt_ptr);
    return ADSP_EFAILED;
  }

  /* Update the packet header structure */
  ap_server_stat_cmn_header_t *header_ptr = (ap_server_stat_cmn_header_t*) payload_ptr;
  header_ptr->module_id         = me_ptr->remote_module_id;
  header_ptr->instance_id       = 1;
  header_ptr->param_id          = AP_PARAM_ID_DATA_WRITE;
  header_ptr->reserved          = 0;
  header_ptr->param_size        = param_size;
  header_ptr->param_version     = AP_PARAM_DATA_WRITE_VERSION;
  header_ptr->param_struct_size = sizeof(ap_container_data_write_buffer_v1_t);

  uint8_t *data_cmd_ptr = (uint8_t*)payload_ptr + sizeof(ap_server_stat_cmn_header_t);

  if(WRITE_CMD == cmd_type)
  {
    memscpy(data_cmd_ptr, sizeof(ap_container_data_write_buffer_v1_t), &wr_buf_ptr->data_write_buf,
            sizeof(ap_container_data_write_buffer_v1_t));

    port_index = wr_buf_ptr->data_write_buf.port_index;
    /* Set the write buffer in use */
    wr_buf_ptr->buf_in_use = TRUE;
  }
  else
  {
    header_ptr->param_id          = AP_PARAM_ID_DATA_READ;
    header_ptr->param_struct_size = sizeof(ap_container_data_read_param_v1_t);
    header_ptr->param_version     = AP_PARAM_DATA_READ_VERSION;

    ap_container_data_read_param_v1_t *read_param_ptr = (ap_container_data_read_param_v1_t*)data_cmd_ptr;

    read_param_ptr->port_index         = port_index;
    read_param_ptr->reserved           = 0;
    read_param_ptr->shm_virtual_offset = rd_buf_ptr->data_read_buf.shm_virtual_offset;
	  rd_buf_ptr->data_read_buf.buf_size = me_ptr->read_buf_pool[port_index].buf_size; // todo :
    read_param_ptr->buf_size           = rd_buf_ptr->data_read_buf.buf_size;
    read_param_ptr->mem_map_handle     = rd_buf_ptr->data_read_buf.mem_map_handle;
    read_param_ptr->seq_id             = rd_buf_ptr->data_read_buf.seq_id;

    /* Set the read buffer in use */
    rd_buf_ptr->buf_in_use = TRUE;
  }

  //olm_elite_hexdump((uint8_t*)payload_ptr, payload_size);

  /*
   * Send the packet to the remote server
   */
  result = elite_apr_if_cmd_fwd(me_ptr->apr_handle, elite_pkt_ptr);
  if(ADSP_FAILED(result))
  {
    MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Failed to send data cmd to remote service"
                                          "with result 0x%x", me_ptr->capi_v2_olm_identifier, result);
    return result;
  }

  if(WRITE_CMD == cmd_type)
  {
    me_ptr->process_info.wr_buf_sent[port_index]++;
  }
  else
  {
    me_ptr->process_info.rd_buf_sent[port_index]++;
  }

  return result;
}

/**
 * This function  is to allocate write data buffers.
 * For setup time media fmt, this function will allocate buffer pool
 * and write data buffers.
 *
 * For steady state media format update, it calculates the updated
 * write buffer size
 *
 * @param[in] me_ptr pointer to OLM module structure
 * @param[in] port_index index of the input port
 *
 * @return ADSPResult, error code
 */
ADSPResult olm_alloc_write_data_buffers(capi_v2_olm_t *me_ptr,
                                        uint32_t port_index)
{
  ADSPResult result = ADSP_EOK;
  uint32_t wr_buf_size;
  uint32_t num_wr_buffers;

  uint32_t buf_cnt;
  int8_t *buf_ptr = NULL;

  capi_v2_standard_data_format_v2_t *media_fmt_ptr = NULL;
  olm_write_buf_t *cur_node_ptr = NULL;
  olm_write_buf_t *prev_node_ptr = NULL;
  uint32_t cur_num_buffers = 0;

  if(NULL == me_ptr)
  {
    MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM : Received invalid instance ptr");
    return ADSP_EFAILED;
  }
  if(port_index >=  me_ptr->num_active_input_ports)
  {
    MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Invalid port index 0x%x ",
                                          me_ptr->capi_v2_olm_identifier, port_index);
    return ADSP_EFAILED;
  }

  olm_update_num_buffers(me_ptr, WRITE_CMD,port_index );
  num_wr_buffers = me_ptr->write_buf_pool[port_index].num_bufs;

  /* Allocate the array of data buffers if not allocated already*/
  if(NULL ==  me_ptr->write_buf_pool[port_index].buf_list_head_ptr && num_wr_buffers > 0)
  {
    /* Create the head node pointer first*/
    cur_node_ptr = NULL;
    cur_node_ptr = (olm_write_buf_t*)qurt_elite_memory_malloc((sizeof(olm_write_buf_t)),
                                                              QURT_ELITE_HEAP_DEFAULT);
    if(NULL == cur_node_ptr)
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Failed to allocate in data buf ptr!",
                                            me_ptr->capi_v2_olm_identifier);
      return ADSP_ENOMEMORY;
    }
    memset(cur_node_ptr, 0, sizeof(olm_write_buf_t));

    me_ptr->write_buf_pool[port_index].buf_list_head_ptr = (void *) cur_node_ptr;
    me_ptr->write_buf_pool[port_index].buf_list_size++;

    /* Initialize the write buffers linked list */
    prev_node_ptr = cur_node_ptr;
    prev_node_ptr->next = NULL;

    for(buf_cnt =0; buf_cnt < num_wr_buffers-1; buf_cnt++)
    {
      cur_node_ptr = NULL;
      cur_node_ptr = (olm_write_buf_t*)qurt_elite_memory_malloc(
          (sizeof(olm_write_buf_t)), QURT_ELITE_HEAP_DEFAULT);
      if(NULL == cur_node_ptr)
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Failed to allocate in data buf ptr!",
                                              me_ptr->capi_v2_olm_identifier);
        return ADSP_ENOMEMORY;
      }
      memset(cur_node_ptr, 0, sizeof(olm_write_buf_t));

      prev_node_ptr->next = cur_node_ptr;
      prev_node_ptr = cur_node_ptr;

      me_ptr->write_buf_pool[port_index].buf_list_size++;
    }
    cur_num_buffers = num_wr_buffers;
  }
  else
  {
    cur_num_buffers =  me_ptr->write_buf_pool[port_index].buf_list_size;
  }

  /* Add new buffers at the beginning of the list */
  if(cur_num_buffers < num_wr_buffers)
  {
    uint32_t add_buf_cnt = num_wr_buffers - cur_num_buffers;

    /*add new buffers in the beginning of the list */
    for(buf_cnt =0; buf_cnt < add_buf_cnt; buf_cnt++)
    {
      cur_node_ptr = NULL;
      cur_node_ptr = (olm_write_buf_t*)qurt_elite_memory_malloc(
          (sizeof(olm_write_buf_t)), QURT_ELITE_HEAP_DEFAULT);

      if(NULL == cur_node_ptr)
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Failed to allocate write buffer node", me_ptr->capi_v2_olm_identifier);
        return ADSP_ENOMEMORY;
      }
      memset(cur_node_ptr, 0, sizeof(olm_write_buf_t));

      cur_node_ptr->next = (olm_write_buf_t *)me_ptr->write_buf_pool[port_index].buf_list_head_ptr;

      /* Update the new head pointer */
      me_ptr->write_buf_pool[port_index].buf_list_head_ptr = (void *)cur_node_ptr;

      /* Increment the buffer list size*/
      me_ptr->write_buf_pool[port_index].buf_list_size++;
    }
  }
  else if(cur_num_buffers > num_wr_buffers)
  {
    /* Need to remove buffers in this case */
    uint32_t rem_buf_cnt = cur_num_buffers - num_wr_buffers;

    /* Initialize the cur_node_ptr to the head of the list */
    cur_node_ptr = (olm_write_buf_t *)me_ptr->write_buf_pool[port_index].buf_list_head_ptr;

    /*
     * Deprecate the buffers starting from the head of the list
     */
    for(buf_cnt =0; buf_cnt < rem_buf_cnt; buf_cnt++)
    {
      cur_node_ptr->is_deprecated = TRUE;
      cur_node_ptr = cur_node_ptr->next;
    }
  }

  media_fmt_ptr = &me_ptr->in_media_fmt[port_index].f;

  /* Calculate write buffer size */
  uint32_t bytes_per_sample = bits_per_sample_2_bytes_per_sample(media_fmt_ptr->bits_per_sample);
  wr_buf_size = media_fmt_ptr->num_channels * (media_fmt_ptr->sampling_rate / 1000) *bytes_per_sample *
      (me_ptr->olm_num_frames);

  me_ptr->write_buf_pool[port_index].buf_size = wr_buf_size;


  /* Delay due to write data buffers */
  if(TRUE == me_ptr->sync_mode)
  {
    me_ptr->write_buf_delay_in_us = 0; //no delay in sync mode
  }
  else
  {
    me_ptr->write_buf_delay_in_us = get_buf_delay(me_ptr, WRITE_CMD, port_index);
  }

  /* Retreive the client proc ID info from the topo definition */
  uint32_t client_proc_id = me_ptr->remote_proc_id;

  /* Allocate write buffers */
  cur_node_ptr = (olm_write_buf_t*)me_ptr->write_buf_pool[port_index].buf_list_head_ptr;

  buf_cnt = 0;
  while(NULL != cur_node_ptr)
  {
    /* The data buf pointer is null if it is a newly added buffer in the list,
     * else it will have a Valid Non Null address.
     * Generally new buffers are added when there is change in remote frame size, during media format
     * handling.
     */
    if( NULL == cur_node_ptr->data_buf_ptr &&
        !is_deprecated_buffer(cur_node_ptr, WRITE_CMD) )
    {
      /* Allocate buffer from shared memory */
      buf_ptr = NULL;

      /* Allocate Buffers in the Shared memory*/
      buf_ptr = (int8_t*) elite_mem_mdf_malloc(wr_buf_size,
                                               client_proc_id,
                                               &cur_node_ptr->data_write_buf.mem_map_handle,
                                               &cur_node_ptr->data_write_buf.shm_virtual_offset);

      if(NULL == buf_ptr)
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Failed to allocate in buffers!", me_ptr->capi_v2_olm_identifier);
        return ADSP_ENOMEMORY;
      }

      MSG_3( MSG_SSID_QDSP6, DBG_MED_PRIO, "CAPIv2 OLM 0x%8lX: elite_mem_mdf_malloc write buf_virt_addr: 0x%08X,"
             " buf VirtOffset 0x%08X", me_ptr->capi_v2_olm_identifier, buf_ptr, cur_node_ptr->data_write_buf.shm_virtual_offset);

      //memset(buf_ptr, 0, wr_buf_size);

      cur_node_ptr->data_write_buf.port_index = port_index;
      cur_node_ptr->data_buf_ptr              = buf_ptr;
      cur_node_ptr->data_buf_size             = wr_buf_size;
      cur_node_ptr->buf_size_per_ch           = wr_buf_size / media_fmt_ptr->num_channels;
      cur_node_ptr->token                     = buf_cnt + 1;

      // TODO assign memmap related info

      // Push the buffers to write Q
      if(NULL != me_ptr->wr_rsp_q_ptr[port_index])
      {
        /* Allocate APR set param packet*/
        elite_apr_packet_t *elite_pkt_ptr;

        result = elite_apr_if_alloc_cmd(me_ptr->apr_handle,
                                        me_ptr->create_resp_info.container_apr_addr,
                                        DEFAULT_OLM_AP_SESSION_PORT,
                                        me_ptr->apr_addr,
                                        me_ptr->olm_cfg.dynamic_cfg->olm_iid,
                                        cur_node_ptr->token,
                                        AP_CMDRSP_DATA,
                                        sizeof(ap_server_stat_cmn_header_t) +
                                        sizeof(ap_container_data_write_buffer_done_v1_t),
                                        &elite_pkt_ptr);
        if(ADSP_FAILED(result))
        {
          MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Could not allocate apr packet for Write Command ",
                me_ptr->capi_v2_olm_identifier);
          return ADSP_EBADPARAM;
        }

        void   *payload  =  elite_apr_if_get_payload_ptr(elite_pkt_ptr);
        if(NULL == payload)
        {
          MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Data Rsp Command had NULL payload in apr packet",
                                                    me_ptr->capi_v2_olm_identifier);
          elite_apr_if_free(me_ptr->apr_handle, elite_pkt_ptr);
          return ADSP_EFAILED;
        }

        ap_server_stat_cmn_header_t *header_ptr = (ap_server_stat_cmn_header_t*)payload;
        header_ptr->param_version     = AP_PARAM_DATA_WRITE_DONE_VERSION;
        header_ptr->param_struct_size = sizeof(ap_container_data_write_buffer_done_v1_t);

        ap_container_data_write_buffer_done_v1_t *write_done_ptr = (ap_container_data_write_buffer_done_v1_t *)((int8_t*)payload + sizeof(ap_server_stat_cmn_header_t));

        write_done_ptr->port_index         = cur_node_ptr->data_write_buf.port_index;
        write_done_ptr->shm_virtual_offset = cur_node_ptr->data_write_buf.shm_virtual_offset;
        write_done_ptr->mem_map_handle     = cur_node_ptr->data_write_buf.mem_map_handle;
        write_done_ptr->status             = ADSP_EOK;

#ifdef CAPI_V2_OLM_DEBUG
        MSG_3(MSG_SSID_QDSP6, DBG_MED_PRIO, "CAPIv2 OLM 0x%8lX: Virt Offset LSW 0x%x Handle 0x%x",me_ptr->capi_v2_olm_identifier, write_done_ptr->shm_virtual_offset, write_done_ptr->mem_map_handle);
#endif

        /* Allocate a message structure */
        elite_msg_any_t msg;

        msg.unOpCode = ELITE_APR_PACKET;
        msg.pPayload = elite_pkt_ptr;


        result = qurt_elite_queue_push_back(me_ptr->wr_rsp_q_ptr[port_index], (uint64_t*)&msg);

        if (ADSP_FAILED(result))
        {
          MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: failed to push buffer to write queue with result = 0x%x", me_ptr->capi_v2_olm_identifier, result);
          return result;
        }
      }
    }

    /* Move to the next write buffer node */
    cur_node_ptr = cur_node_ptr->next;
  }

  return ADSP_EOK;
}

/**
 * This function  is to reallocate write data buffers for steady state
 * media format update
 *
 * @param[in] me_ptr pointer to OLM module structure
 * @param[inout] wr_data_buf_ptr pointer to write data buffer
 * @param[in] port_index index of the input port
 *
 * @return ADSPResult, error code
 *
 */
ADSPResult olm_realloc_write_data_buffer(capi_v2_olm_t *me_ptr, olm_write_buf_t *wr_data_buf_ptr, uint32_t port_index)
{
  ADSPResult result = ADSP_EOK;
  int8_t *buf_ptr = NULL;

  if(NULL == me_ptr)
  {
    MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM : Received invalid instance ptr");
    return ADSP_EFAILED;
  }
  if(port_index >=  me_ptr->num_active_input_ports)
  {
    MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Invalid port index 0x%x ",
          me_ptr->capi_v2_olm_identifier, port_index);
    return ADSP_EFAILED;
  }

  /* Reallocate only if the buffer size is not the required size and if the buffer node is not deprecated */
  if( (me_ptr->write_buf_pool[port_index].buf_size != wr_data_buf_ptr->data_buf_size) &&
      !is_deprecated_buffer(wr_data_buf_ptr, WRITE_CMD) )
  {
    if(NULL != wr_data_buf_ptr->data_buf_ptr)
    {
      elite_mem_mdf_mem_free(wr_data_buf_ptr->data_buf_ptr,
                             wr_data_buf_ptr->data_write_buf.mem_map_handle,
                             wr_data_buf_ptr->data_buf_size);
    }
    wr_data_buf_ptr->data_buf_ptr = NULL;

    /* Retreive the client proc ID info from the topo definition */
    uint32_t client_proc_id = me_ptr->remote_proc_id;

    /* Allocate Buffers in the Shared memory*/
    buf_ptr = (int8_t*) elite_mem_mdf_malloc(me_ptr->write_buf_pool[port_index].buf_size,
                                             client_proc_id,
                                             &wr_data_buf_ptr->data_write_buf.mem_map_handle,
                                             &wr_data_buf_ptr->data_write_buf.shm_virtual_offset);
    if(NULL == buf_ptr)
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Failed to allocate in buffers!", me_ptr->capi_v2_olm_identifier);
      return ADSP_ENOMEMORY;
    }

   // memset(buf_ptr, 0, me_ptr->write_buf_pool[port_index].buf_size);

    wr_data_buf_ptr->data_buf_ptr  = buf_ptr;
    wr_data_buf_ptr->data_buf_size = me_ptr->write_buf_pool[port_index].buf_size;
    wr_data_buf_ptr->buf_size_per_ch     = me_ptr->write_buf_pool[port_index].buf_size / me_ptr->in_media_fmt[port_index].f.num_channels;
  }

  return result;
}

/**
 * This function  is to allocate read data buffers.
 * For setup time media fmt, this function will allocate buffer pool
 * and read data buffers.
 *
 * For steady state media format update, it calculates the updated
 * write buffer size
 *
 * @param[in] me_ptr pointer to OLM module structure
 * @param[in] port_index index of the output port
 *
 * @return ADSPResult, error code
 */
ADSPResult olm_alloc_read_data_buffers(capi_v2_olm_t *me_ptr, uint32_t port_index)
{
  uint32_t rd_buf_size;
  uint32_t num_rd_buffers = 0;
  uint32_t cur_num_buffers = 0;

  if(NULL == me_ptr)
  {
    MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM : Received invalid instance ptr");
    return ADSP_EFAILED;
  }
  if(port_index >=  me_ptr->num_active_output_ports)
  {
    MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Invalid port index 0x%x ",
          me_ptr->capi_v2_olm_identifier, port_index);
    return ADSP_EFAILED;
  }

  uint32_t buf_cnt = 0;
  int8_t *buf_ptr = NULL;
  olm_read_buf_t *cur_node_ptr = NULL;
  olm_read_buf_t *prev_node_ptr = NULL;

  capi_v2_standard_data_format_v2_t *media_fmt_ptr = NULL;

  olm_update_num_buffers(me_ptr, READ_CMD,port_index );

  num_rd_buffers = me_ptr->read_buf_pool[port_index].num_bufs;

  /* Allocate the array of data buffers if not allocated already*/
  if(NULL ==  me_ptr->read_buf_pool[port_index].buf_list_head_ptr && num_rd_buffers > 0)
  {
    /* Create the head node pointer first*/
    cur_node_ptr = NULL;
    cur_node_ptr = (olm_read_buf_t*)qurt_elite_memory_malloc(
        (sizeof(olm_read_buf_t)), QURT_ELITE_HEAP_DEFAULT);

    if(NULL == cur_node_ptr)
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Failed to allocate read buffer node", me_ptr->capi_v2_olm_identifier);
      return ADSP_ENOMEMORY;
    }
    memset(cur_node_ptr, 0, sizeof(olm_read_buf_t));

    me_ptr->read_buf_pool[port_index].buf_list_head_ptr = (void *) cur_node_ptr;
    me_ptr->read_buf_pool[port_index].buf_list_size++;

    /* Initialize the write buffers linked list */
    prev_node_ptr = cur_node_ptr;
    prev_node_ptr->next = NULL;

    for(buf_cnt =0; buf_cnt < num_rd_buffers-1; buf_cnt++)
    {
      cur_node_ptr = NULL;
      cur_node_ptr = (olm_read_buf_t*)qurt_elite_memory_malloc( sizeof(olm_read_buf_t),
                                                               QURT_ELITE_HEAP_DEFAULT);
      if(NULL == cur_node_ptr)
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Failed to allocate read buffer node", me_ptr->capi_v2_olm_identifier);
        return ADSP_ENOMEMORY;
      }
      memset(cur_node_ptr, 0, sizeof(olm_read_buf_t));

      prev_node_ptr->next = cur_node_ptr;
      prev_node_ptr = cur_node_ptr;

      me_ptr->read_buf_pool[port_index].buf_list_size++;
    }
    cur_num_buffers = num_rd_buffers;
  }
  else
  {
    /* get the count of existing buffers in the list */
    cur_num_buffers = me_ptr->read_buf_pool[port_index].buf_list_size;
  }

  /* Add new buffers at beginning of the list*/
  if(cur_num_buffers < num_rd_buffers)
  {
    uint32_t add_buf_cnt = num_rd_buffers -cur_num_buffers;

    /*add new buffers in the beginning of the list */
    for(buf_cnt =0; buf_cnt < add_buf_cnt; buf_cnt++)
    {
      cur_node_ptr = NULL;
      cur_node_ptr = (olm_read_buf_t*)qurt_elite_memory_malloc(
          (sizeof(olm_read_buf_t)), QURT_ELITE_HEAP_DEFAULT);

      if(NULL == cur_node_ptr)
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Failed to allocate read buffer node", me_ptr->capi_v2_olm_identifier);
        return ADSP_ENOMEMORY;
      }
      memset(cur_node_ptr, 0, sizeof(olm_read_buf_t));

      cur_node_ptr->next = (olm_read_buf_t *)me_ptr->read_buf_pool[port_index].buf_list_head_ptr;

      /* Update the new head pointer */
      me_ptr->read_buf_pool[port_index].buf_list_head_ptr = (void *)cur_node_ptr;

      /* Increment the buffer list size*/
      me_ptr->read_buf_pool[port_index].buf_list_size++;
    }
  }
  else if(cur_num_buffers > num_rd_buffers)
  {
    /* Need to remove buffers in this case */
    uint32_t rem_buf_cnt = cur_num_buffers - num_rd_buffers;

    /* Initialize the cur_node_ptr to the head of the list */
    cur_node_ptr = (olm_read_buf_t *)me_ptr->read_buf_pool[port_index].buf_list_head_ptr;

    /* Delete the nodes from the beginning of the list and update the head pointer */
    for(buf_cnt =0; buf_cnt < rem_buf_cnt; buf_cnt++)
    {
      /* save the current head pointer*/
      cur_node_ptr->is_deprecated = TRUE;
      cur_node_ptr = cur_node_ptr->next;
    }
  }

  media_fmt_ptr = &me_ptr->out_media_fmt[port_index].f;

  /* Calculate input buffer size */
  uint32_t bytes_per_sample = bits_per_sample_2_bytes_per_sample(media_fmt_ptr->bits_per_sample);
  rd_buf_size = media_fmt_ptr->num_channels * (media_fmt_ptr->sampling_rate / 1000) *
      bytes_per_sample * (me_ptr->olm_num_frames);

  me_ptr->read_buf_pool[port_index].buf_size = rd_buf_size;

  if(me_ptr->remote_num_frames > me_ptr->olm_num_frames)
  {
	  me_ptr->process_info.prefill_read_done_size_per_ch = 0;
	  me_ptr->process_info.prefill_read_data_size_per_ch = 2 * (media_fmt_ptr->sampling_rate / 1000) * bytes_per_sample * (me_ptr->remote_num_frames);
  }

  /* delay due to read buffers */
  if(TRUE == me_ptr->sync_mode)
  {
    me_ptr->read_buf_delay_in_us = 0; //no delay in sync mode
  }
  else
  {
    me_ptr->read_buf_delay_in_us = get_buf_delay(me_ptr, READ_CMD, port_index);;
  }

  /* Retrieve the client proc ID info from the topo definition */
  uint32_t client_proc_id = me_ptr->remote_proc_id;

  /* Allocate read buffers */
  cur_node_ptr = (olm_read_buf_t*)me_ptr->read_buf_pool[port_index].buf_list_head_ptr;

  while(NULL != cur_node_ptr)
  {
    /* The data buf pointer is null if it is a newly added buffer in the buffer list,
     * else it will have a Valid Non Null address.
     *
     * Generally buffers are added/removed when there is change in remote frame size, during media format
     * handling.
     */
    if( NULL == cur_node_ptr->data_buf_ptr &&
        !is_deprecated_buffer(cur_node_ptr, READ_CMD) )
    {
      /* Allocate buffer from shared memory */
      buf_ptr = NULL;

      /* Allocate buffer from shared memory */
      buf_ptr = (int8_t*) elite_mem_mdf_malloc(rd_buf_size,
                                               client_proc_id,
                                               &cur_node_ptr->data_read_buf.mem_map_handle,
                                               &cur_node_ptr->data_read_buf.shm_virtual_offset);
      if(NULL == buf_ptr)
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Failed to allocate rd buffers!", me_ptr->capi_v2_olm_identifier);
        return ADSP_ENOMEMORY;
      }

      MSG_3( MSG_SSID_QDSP6, DBG_MED_PRIO, "CAPIv2 OLM 0x%8lX: elite_mem_mdf_malloc Read buf_virt_addr: 0x%08X,"
             " buf Virt Offset 0x%08X,  MSW 0x%08X", me_ptr->capi_v2_olm_identifier, buf_ptr, cur_node_ptr->data_read_buf.shm_virtual_offset);

      memset(buf_ptr, 0, rd_buf_size);
      cur_node_ptr->data_buf_ptr = buf_ptr;
      cur_node_ptr->data_buf_size = rd_buf_size;
      cur_node_ptr->buf_size_per_ch = rd_buf_size / media_fmt_ptr->num_channels;

      cur_node_ptr->token = buf_cnt + 1;
      cur_node_ptr->data_read_buf.buf_size = 0; // size is updated in the send data cmd
      cur_node_ptr->data_read_buf.status = ADSP_EOK;
      cur_node_ptr->data_read_buf.port_index = port_index;

      ADSPResult adsp_result = ADSP_EOK;
      if(ADSP_EOK != (adsp_result = olm_send_data_cmd(me_ptr,(void *)cur_node_ptr, READ_CMD)))
      {
    	  MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Send read command failed", me_ptr->capi_v2_olm_identifier);
    	  return adsp_result;
      }

    }

    /* Move to the next read buffer node*/
    cur_node_ptr = cur_node_ptr->next;
  }

  return ADSP_EOK;
}

/**
 * This function is to reallocate read data buffers.
 * when media format is updated in steady state.
 *
 * @param[in] me_ptr pointer to OLM module structure
 * @param[inout] rd_data_buf_ptr pointer to read data buffer
 * @param[in] port_index index of the output port
 *
 * @return ADSPResult, error code
 */
ADSPResult olm_realloc_read_data_buffer(capi_v2_olm_t *me_ptr, olm_read_buf_t *rd_data_buf_ptr, uint32_t port_index)
{
  ADSPResult result = ADSP_EOK;
  int8_t *buf_ptr = NULL;

  if(NULL == me_ptr)
  {
    MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM : Received invalid instance ptr");
    return ADSP_EFAILED;
  }
  if(port_index >=  me_ptr->num_active_output_ports)
  {
    MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Invalid port index 0x%x ",
          me_ptr->capi_v2_olm_identifier, port_index);
    return ADSP_EFAILED;
  }

  /* Reallocate only if the buffer size is not the required size */
  if(me_ptr->read_buf_pool[port_index].buf_size != rd_data_buf_ptr->data_buf_size &&
      !is_deprecated_buffer(rd_data_buf_ptr, READ_CMD))
  {
    if(NULL != rd_data_buf_ptr->data_buf_ptr)
    {
      elite_mem_mdf_mem_free(rd_data_buf_ptr->data_buf_ptr,
                             rd_data_buf_ptr->data_read_buf.mem_map_handle,
                             rd_data_buf_ptr->data_buf_size);
    }
    rd_data_buf_ptr->data_buf_ptr = NULL;

    /* Retreive the client proc ID info from the topo definition */
    uint32_t client_proc_id = me_ptr->remote_proc_id;

    /* Allocate Buffers in the Shared memory*/
    buf_ptr = (int8_t*) elite_mem_mdf_malloc(me_ptr->read_buf_pool[port_index].buf_size,
                                             client_proc_id,
                                             &rd_data_buf_ptr->data_read_buf.mem_map_handle,
                                             &rd_data_buf_ptr->data_read_buf.shm_virtual_offset);
    if(NULL == buf_ptr)
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Failed to allocate read buffers!",
                                            me_ptr->capi_v2_olm_identifier);
      return ADSP_ENOMEMORY;
    }
    //memset(buf_ptr, 0, me_ptr->read_buf_pool[port_index].buf_size);

    rd_data_buf_ptr->data_buf_ptr = buf_ptr;
    rd_data_buf_ptr->data_buf_size = me_ptr->read_buf_pool[port_index].buf_size;
    rd_data_buf_ptr->data_read_buf.buf_size = 0;
    rd_data_buf_ptr->buf_size_per_ch = me_ptr->read_buf_pool[port_index].buf_size / me_ptr->out_media_fmt[port_index].f.num_channels;
  }

  return result;
}

/**
 * This function is to deallocate write data buffers.
 *
 * @param[in] me_ptr pointer to OLM module structure
 * @param[in] port_index index of the input port
 *
 * @return none
 */
void olm_dealloc_write_data_buffers(capi_v2_olm_t *me_ptr, uint32_t port_index)
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

  if(NULL != me_ptr->write_buf_pool[port_index].buf_list_head_ptr)
  {
    olm_write_buf_t *cur_wr_buf_ptr = (olm_write_buf_t *)me_ptr->write_buf_pool[port_index].buf_list_head_ptr;
    olm_write_buf_t *prev_node_ptr = NULL;

    while(NULL != cur_wr_buf_ptr)
    {
      if(NULL != cur_wr_buf_ptr)
      {
        if( NULL != cur_wr_buf_ptr->data_buf_ptr)
        {
          elite_mem_mdf_mem_free(cur_wr_buf_ptr->data_buf_ptr,
                                 cur_wr_buf_ptr->data_write_buf.mem_map_handle,
                                 cur_wr_buf_ptr->data_buf_size);
        }
        cur_wr_buf_ptr->data_buf_ptr = NULL;

        /*move to the next buffer node*/
        prev_node_ptr = cur_wr_buf_ptr;
        cur_wr_buf_ptr = cur_wr_buf_ptr->next;

        /*Deallocate the buffer node memory*/
        qurt_elite_memory_free(prev_node_ptr);
      }
      else
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Buffer pointer is NULL", me_ptr->capi_v2_olm_identifier);
        break; //RR: is this an error? wouldn't the while break anyway?
      }
    }
    me_ptr->write_buf_pool[port_index].buf_list_head_ptr = NULL;
    me_ptr->write_buf_pool[port_index].buf_list_size = 0;
  }

  memset(&me_ptr->write_buf_pool[port_index], 0, sizeof(me_ptr->write_buf_pool[port_index]));

  olm_destroy_queues(me_ptr, WRITE_CMD, port_index);

}

/**
 * This function is to deallocate read data buffers.
 *
 * @param[in] me_ptr pointer to OLM module structure
 * @param[in] port_index index of the output port
 *
 * @return none
 */
void olm_dealloc_read_data_buffers(capi_v2_olm_t *me_ptr, uint32_t port_index)
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

  if(NULL != me_ptr->read_buf_pool[port_index].buf_list_head_ptr )
  {
    olm_read_buf_t *cur_rd_buf_ptr = (olm_read_buf_t *)me_ptr->read_buf_pool[port_index].buf_list_head_ptr;
    olm_read_buf_t *prev_node_ptr = NULL;

    while(NULL != cur_rd_buf_ptr)
    {
      if(NULL != cur_rd_buf_ptr)
      {
        if(NULL != cur_rd_buf_ptr->data_buf_ptr)
        {
          elite_mem_mdf_mem_free(cur_rd_buf_ptr->data_buf_ptr,
                                 cur_rd_buf_ptr->data_read_buf.mem_map_handle,
                                 cur_rd_buf_ptr->data_buf_size);
        }
        cur_rd_buf_ptr->data_buf_ptr = NULL;

        /*move to the next buffer node*/
        prev_node_ptr = cur_rd_buf_ptr;
        cur_rd_buf_ptr = cur_rd_buf_ptr->next;

        /*Deallocate the buffer node*/
        qurt_elite_memory_free(prev_node_ptr);
      }
      else
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Buffer pointer is NULL",me_ptr->capi_v2_olm_identifier);
        break; //RR: is this an error? wouldn't the while break anyway?
      }
    }
    me_ptr->read_buf_pool[port_index].buf_list_head_ptr = NULL;
    me_ptr->read_buf_pool[port_index].buf_list_size = 0;
  }

  memset(&me_ptr->read_buf_pool[port_index], 0, sizeof(me_ptr->read_buf_pool[port_index]));

  /* Destroy Read buffer queues */
  olm_destroy_queues(me_ptr, READ_CMD, port_index);

}

/**
 * This function is to get write data buffer for the given write response buffer
 *
 * @param[in] me_ptr pointer to OLM module structure
 * @param[in] data_apr_pkt_ptr pointer to write response apr packet
 * @param[in] port_index input port index
 * @param[out] wr_data_buf_ptr_ptr pointer to write data buffer
 *
 * @return ADSPResult
 */
ADSPResult get_wr_data_buf_ptr(capi_v2_olm_t *me_ptr,
                                  elite_apr_packet_t *data_apr_pkt_ptr,
                                  uint32_t port_index,
                                  olm_write_buf_t **wr_data_buf_ptr_ptr)
{
  uint32_t token = elite_apr_if_get_client_token(data_apr_pkt_ptr);
  *wr_data_buf_ptr_ptr = NULL;

  ADSPResult result = ADSP_EOK;

  if(NULL == me_ptr)
  {
    MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM : Received invalid instance ptr");
    return ADSP_EFAILED;
  }
  if(port_index >=  me_ptr->num_active_input_ports)
  {
    MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Invalid port index 0x%x ",
          me_ptr->capi_v2_olm_identifier, port_index);
    return ADSP_EFAILED;
  }

  void   *payload  =  elite_apr_if_get_payload_ptr(data_apr_pkt_ptr);

  ap_server_stat_cmn_header_t *header_ptr = reinterpret_cast<ap_server_stat_cmn_header_t*>(payload);
  ap_container_data_write_buffer_done_v1_t *write_done_ptr = (ap_container_data_write_buffer_done_v1_t *) ((int8_t*)payload +
      sizeof(ap_server_stat_cmn_header_t));

  if(header_ptr->param_version > AP_PARAM_DATA_WRITE_DONE_VERSION || (0 == header_ptr->param_version))
  {
    MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: write buffer done with version 0x%lx Expected Version 0x1 to 0x%x ",
          me_ptr->capi_v2_olm_identifier, header_ptr->param_version, AP_PARAM_DATA_WRITE_DONE_VERSION);
    return ADSP_EUNSUPPORTED;

  }

  if(ADSP_EOK != write_done_ptr->status)
  {
    MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: write buffer failed with status %ld ",
          me_ptr->capi_v2_olm_identifier, write_done_ptr->status);
    return ADSP_EFAILED;
  }

  olm_write_buf_t *cur_wr_buf_ptr = (olm_write_buf_t*) me_ptr->write_buf_pool[port_index].buf_list_head_ptr;
  ap_container_data_write_buffer_v1_t *data_write_buf_ptr;

  while(NULL != cur_wr_buf_ptr)
  {
    data_write_buf_ptr = &cur_wr_buf_ptr->data_write_buf;
    if((token == cur_wr_buf_ptr->token) &&(write_done_ptr->shm_virtual_offset == data_write_buf_ptr->shm_virtual_offset))
    {
      *wr_data_buf_ptr_ptr = cur_wr_buf_ptr;

      /* reallocate the buffer if the size is changed */
      if(ADSP_EOK != (result = olm_realloc_write_data_buffer(me_ptr, cur_wr_buf_ptr, port_index)))
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Failed to reallocate write buffer ",me_ptr->capi_v2_olm_identifier);
        return result;
      }

      return ADSP_EOK;
    }

    /* move to the next node*/
    cur_wr_buf_ptr = cur_wr_buf_ptr->next;
  }

  return ADSP_EFAILED;
}

/**
 * This function is to get read data buffer for the given read response buffer
 *
 * @param[in] me_ptr pointer to OLM module structure
 * @param[in] data_apr_pkt_ptr pointer to read response apr packet
 * @param[in] port_index output port index
 * @param[out] rd_data_buf_ptr_ptr pointer to read data buffer
 *
 * @return ADSPResult
 */
ADSPResult get_rd_data_buf_ptr(capi_v2_olm_t *me_ptr,
                                  elite_apr_packet_t *data_apr_pkt_ptr,
                                  uint32_t port_index,
                                  olm_read_buf_t **rd_data_buf_ptr_ptr)
{
  ADSPResult result = ADSP_EOK;
  uint32_t token = elite_apr_if_get_client_token(data_apr_pkt_ptr);
  *rd_data_buf_ptr_ptr = NULL;

  if(NULL == me_ptr)
  {
    MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM : Received invalid instance ptr");
    return ADSP_EFAILED;
  }
  if(port_index >=  me_ptr->num_active_output_ports)
  {
    MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Invalid port index 0x%x ",
          me_ptr->capi_v2_olm_identifier, port_index);
    return ADSP_EFAILED;
  }

  void   *payload  =  elite_apr_if_get_payload_ptr(data_apr_pkt_ptr);
  ap_server_stat_cmn_header_t *header_ptr = reinterpret_cast<ap_server_stat_cmn_header_t*>(payload);

  ap_container_data_read_done_param_v1_t *read_done_ptr = (ap_container_data_read_done_param_v1_t *)((int8_t*)payload +
      sizeof(ap_server_stat_cmn_header_t));

  if(header_ptr->param_version > AP_PARAM_DATA_READ_DONE_VERSION || (0 == header_ptr->param_version))
  {
    MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: read response with version 0x%lx Expected Version 0x1 to 0x%x ",
          me_ptr->capi_v2_olm_identifier, header_ptr->param_version, AP_PARAM_DATA_READ_DONE_VERSION);
    return ADSP_EBADPARAM;
  }

  if(ADSP_EOK != read_done_ptr->status)
  {
    MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: read response with failure status %ld ",
          me_ptr->capi_v2_olm_identifier, read_done_ptr->status);

    return ADSP_EFAILED;
  }

  olm_read_buf_t *cur_rd_buf_ptr = (olm_read_buf_t*) me_ptr->read_buf_pool[port_index].buf_list_head_ptr;
  ap_container_data_read_done_param_v1_t *data_read_buf_ptr;

  while(NULL != cur_rd_buf_ptr)
  {
    data_read_buf_ptr = &cur_rd_buf_ptr->data_read_buf;
    if((token == cur_rd_buf_ptr->token) && (read_done_ptr->shm_virtual_offset == data_read_buf_ptr->shm_virtual_offset))
    {
      /* Copying the data from read response */
      memscpy(&cur_rd_buf_ptr->data_read_buf, sizeof(cur_rd_buf_ptr->data_read_buf), read_done_ptr,
              sizeof(ap_container_data_read_done_param_v1_t));

      *rd_data_buf_ptr_ptr = cur_rd_buf_ptr;

      if(ADSP_EOK != (result = qurt_elite_memorymap_cache_invalidate((uint32_t)(*rd_data_buf_ptr_ptr)->data_buf_ptr,
                                                                     (*rd_data_buf_ptr_ptr)->data_buf_size)))
      {
        MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "CAPIv2 OLM 0x%8lX: Invalidate Cache failed with result 0x%x", me_ptr->capi_v2_olm_identifier, result);
        return result;
      }

      return ADSP_EOK;
    }

    /* Move to the next read buffer node*/
    cur_rd_buf_ptr = cur_rd_buf_ptr->next;
  }

  return ADSP_EFAILED;
}

/**
 * This function is to send partially filled write buffer to remote service
 *
 * @param[in] me_ptr pointer to OLM module structure
 * @param[in] port_index input port index
 *
 * @return ADSPResult
 */
ADSPResult olm_send_temp_wr_buffer(capi_v2_olm_t *me_ptr, uint32_t port_index)
{
  ADSPResult adsp_result = ADSP_EOK;
  uint32_t buf_size_per_ch = 0, ch_idx;
  uint32_t data_buf_size = 0;

  if(NULL == me_ptr)
  {
    MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM : Received invalid instance ptr");
    return ADSP_EFAILED;
  }
  if(port_index >=  me_ptr->num_active_input_ports)
  {
    MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Invalid port index 0x%x ",
          me_ptr->capi_v2_olm_identifier, port_index);
    return ADSP_EFAILED;
  }

  if(0 == me_ptr->tmp_wr_data_buf_ptr[port_index]->fill_size_per_ch)
  {
    /* No data in temporary write data buffer */
    return ADSP_EOK;
  }

  int8_t *dst_ptr = NULL, *src_ptr = NULL;

  data_buf_size = me_ptr->tmp_wr_data_buf_ptr[port_index]->data_buf_size;

  buf_size_per_ch = me_ptr->tmp_wr_data_buf_ptr[port_index]->buf_size_per_ch;

  /* Move till end of first channel */
  dst_ptr = me_ptr->tmp_wr_data_buf_ptr[port_index]->data_buf_ptr + me_ptr->tmp_wr_data_buf_ptr[port_index]->fill_size_per_ch;

  /* Adjust the channels in write buffer */
  if(1 < me_ptr->in_media_fmt[port_index].f.num_channels)
  {
    src_ptr = me_ptr->tmp_wr_data_buf_ptr[port_index]->data_buf_ptr +  buf_size_per_ch;
    for(ch_idx = 1; ch_idx < me_ptr->in_media_fmt[port_index].f.num_channels; ch_idx++)
    {
      memsmove(dst_ptr, (data_buf_size - me_ptr->tmp_wr_data_buf_ptr[port_index]->data_write_buf.buf_size),
               src_ptr, me_ptr->tmp_wr_data_buf_ptr[port_index]->fill_size_per_ch);

      dst_ptr = dst_ptr + me_ptr->tmp_wr_data_buf_ptr[port_index]->fill_size_per_ch;
      src_ptr = src_ptr + buf_size_per_ch;
    }
  }

  /* Send temporary write buffer to remote svc */
  if(ADSP_EOK != (adsp_result = olm_send_data_cmd(me_ptr, (void *)me_ptr->tmp_wr_data_buf_ptr[port_index], WRITE_CMD)))
  {
    MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Failed to send write buffer with result 0x%x",
                                          me_ptr->capi_v2_olm_identifier, adsp_result);
  }
  me_ptr->tmp_wr_data_buf_ptr[port_index] = NULL;

  return adsp_result;
}

/**
 * This function is to send partially filled write buffer to remote service
 *
 * @param[in] me_ptr pointer to OLM module structure
 * @param[in] port_index input port index
 *
 * @return ADSPResult
 */
ADSPResult olm_pack_send_temp_wr_buffer(capi_v2_olm_t *me_ptr, uint32_t port_index)
{
  ADSPResult adsp_result = ADSP_EOK;
  uint32_t buf_size_per_ch = 0, ch_idx;
  uint32_t data_buf_size = 0, fill_size_per_ch = 0, num_bytes = 0, bytes_per_sample = 0;

  if(NULL == me_ptr)
  {
    MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM : Received invalid instance ptr");
    return ADSP_EFAILED;
  }
  if(port_index >=  me_ptr->num_active_input_ports)
  {
    MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Invalid port index 0x%x ",
          me_ptr->capi_v2_olm_identifier, port_index);
    return ADSP_EFAILED;
  }

  if(NULL == me_ptr->tmp_wr_data_buf_ptr[port_index])
  {
    return ADSP_EOK;
  }

  if(0 == me_ptr->tmp_wr_data_buf_ptr[port_index]->fill_size_per_ch)
  {
    /* No data in temporary write data buffer */
    return ADSP_EOK;
  }

  olm_write_buf_t *olm_wr_buf = me_ptr->tmp_wr_data_buf_ptr[port_index];

  data_buf_size = olm_wr_buf->data_buf_size;
  buf_size_per_ch = olm_wr_buf->buf_size_per_ch;
  fill_size_per_ch = olm_wr_buf->fill_size_per_ch;

  bytes_per_sample = bits_per_sample_2_bytes_per_sample(me_ptr->in_media_fmt[port_index].f.bits_per_sample);

  num_bytes = (buf_size_per_ch - fill_size_per_ch);

  if(0 == num_bytes)
  {
    return ADSP_EOK;
  }

  MSG_3(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "CAPIv2 OLM 0x%8lX: Filling port index 0x%x write buffer with %d zeroes per ch ",
            me_ptr->capi_v2_olm_identifier, port_index, buf_size_per_ch - fill_size_per_ch);

  for(ch_idx = 0; ch_idx < me_ptr->in_media_fmt[port_index].f.num_channels; ch_idx++)
  {
    memset((olm_wr_buf->data_buf_ptr +
              ((ch_idx * olm_wr_buf->buf_size_per_ch) +  olm_wr_buf->fill_size_per_ch)), 0, num_bytes);

   olm_wr_buf->data_write_buf.buf_size += num_bytes;
  }

  olm_wr_buf->fill_size_per_ch += num_bytes;

  MSG_4(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "CAPIv2 OLM 0x%8lX: port index 0x%x filled write buffer size = %d alloc size = %d",
            me_ptr->capi_v2_olm_identifier, port_index, olm_wr_buf->data_write_buf.buf_size, data_buf_size);

  /* Send temporary write buffer to remote svc */
  if(ADSP_EOK != (adsp_result = olm_send_data_cmd(me_ptr, (void *)me_ptr->tmp_wr_data_buf_ptr[port_index], WRITE_CMD)))
  {
    MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Failed to send write buffer with result 0x%x",
                                          me_ptr->capi_v2_olm_identifier, adsp_result);
  }
  me_ptr->tmp_wr_data_buf_ptr[port_index] = NULL;

  return adsp_result;
}
