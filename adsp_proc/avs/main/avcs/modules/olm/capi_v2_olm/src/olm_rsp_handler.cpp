/**
@file olm_rsp_handler.cpp

@brief This file contains the response handling functionality for Off-loading module

 */

/*========================================================================

Edit History

when          who            what, where, why
--------      ---            -------------------------------------------------------
11/27/2017    bvodapal       Initial version (moved the response handling code from olm_utils)

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
static void olm_process_open_response(capi_v2_olm_t* me_ptr, elite_apr_packet_t *resp_pkt_ptr);
static void olm_process_get_param_response(capi_v2_olm_t* me_ptr, elite_apr_packet_t *resp_pkt_ptr);
static void olm_process_ibasic_response(capi_v2_olm_t* me_ptr, elite_apr_packet_t *resp_pkt_ptr);

/**
 * This function is to process the Response Packet from the Dynamic Svc
 *
 * @param[in] me_ptr pointer to OLM module structure
 * @param[in] resp_pkt_ptr pointer to response apr packet
 *
 * @return none
 */
void olm_response_pkt_handler(capi_v2_olm_t *me_ptr, elite_apr_packet_t *resp_pkt_ptr)
{
  /* Gets called by dynamic service when an APR packet is received at the service response Q */
  uint32_t opcode   = elite_apr_if_get_opcode(resp_pkt_ptr);

  MSG_3(MSG_SSID_QDSP6, DBG_LOW_PRIO,"CAPIv2 OLM 0x%8lX: Received Rsp 0x%x from 0x%x",
                                        me_ptr->capi_v2_olm_identifier, opcode, elite_apr_if_get_src_addr(resp_pkt_ptr));

  void     *payload = elite_apr_if_get_payload_ptr(resp_pkt_ptr);
  if(NULL == payload)
  {
    MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Rsp for opcode 0x%x received NULL Payload",
                                       me_ptr->capi_v2_olm_identifier, opcode);
    elite_apr_if_free(me_ptr->apr_handle,resp_pkt_ptr);
    return;
  }

  switch(opcode)
  {
    case AP_CMDRSP_OPEN:
    {
      olm_process_open_response(me_ptr, resp_pkt_ptr);
      break;
    }

    case AP_CMDRSP_GET_PARAM_CONFIG_V2:
    case AP_CMDRSP_GET_PARAM_CONFIG_V1:
    {
      olm_process_get_param_response(me_ptr, resp_pkt_ptr);
      break;
    }

    case APRV2_IBASIC_RSP_RESULT:
    {
      olm_process_ibasic_response(me_ptr, resp_pkt_ptr);
      break;
    }

    case AP_CMD_EVENT:
    {
      /* Pass the payload to OLM event handler */
      olm_event_handler(me_ptr, resp_pkt_ptr);

      break;
    }
    default:
    {
      MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Invaild response command OPCODE = %d", me_ptr->capi_v2_olm_identifier, opcode);
      break;
    }
  }
  elite_apr_if_free(me_ptr->apr_handle,resp_pkt_ptr);
}

/**
 * This function is to process the Open Response from the Remote Static Svc
 *
 * @param[in] me_ptr pointer to OLM module structure
 * @param[in] resp_pkt_ptr pointer to response apr packet
 *
 * @return none
 */
static void olm_process_open_response(capi_v2_olm_t* me_ptr, elite_apr_packet_t *resp_pkt_ptr)
{
  uint32_t token        = elite_apr_if_get_client_token(resp_pkt_ptr);
  void     *payload_ptr = elite_apr_if_get_payload_ptr(resp_pkt_ptr);

  int8_t   *buffer      = (int8_t*)payload_ptr;

  uint32_t   shm_offset = 0;
  ADSPResult result     = ADSP_EOK;

  /* Extract header from the response message */
  ap_server_stat_cmn_header_t *header_ptr = reinterpret_cast<ap_server_stat_cmn_header_t*>(buffer);

  struct open_resp_t
  {
    capi_v2_olm_open_resp_t base_resp;
    olm_open_resp_t dynamic_resp;
  };

  open_resp_t open_rsp;

  if(NULL == payload_ptr)
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Received NULL payload for AP_CMDRSP_OPEN",
                                          me_ptr->capi_v2_olm_identifier);
    open_rsp.base_resp.result = ADSP_EFAILED;
    goto __send_open_rsp;
  }

  /* Supported response versions can be 1 to AP_PARAM_CREATE_CONTAINER_RSP_VERSION */
  if( AP_PARAM_ID_CREATE_CONTAINER_RSP == header_ptr->param_id &&
      sizeof(ap_create_container_rsp_v1_t) <= header_ptr->param_size &&
      AP_PARAM_CREATE_CONTAINER_RSP_VERSION >= header_ptr->param_version &&
      0 != header_ptr->param_version)
  {
    buffer += sizeof(ap_server_stat_cmn_header_t);

    /* Supported response version currently is 1 */
    ap_create_container_rsp_v1_t *ap_resp_ptr = reinterpret_cast<ap_create_container_rsp_v1_t*>(buffer);

    if(ADSP_FAILED(ap_resp_ptr->status))
    {
      MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Received failed status 0x%x for AP_CMDRSP_OPEN",
            me_ptr->capi_v2_olm_identifier, ap_resp_ptr->status);

      open_rsp.base_resp.result = ap_resp_ptr->status;
      goto __send_open_rsp;
    }


    /* Copy the response info into context pointer */
    memscpy((void *)&me_ptr->create_resp_info, sizeof(ap_create_container_rsp_v1_t),
            (void *)ap_resp_ptr, sizeof(ap_create_container_rsp_v1_t) );

    /* Copy the response from the response pkt */
    open_rsp.base_resp.version = 0;
    open_rsp.base_resp.result = ap_resp_ptr->status;
    //RR: TBD open_rsp.base_resp.payload_size = ?;

    me_ptr->remote_num_frames   = me_ptr->olm_num_frames; //RR: Review this once
    me_ptr->remote_container_id = ap_resp_ptr->container_id;

    if(NULL != me_ptr->outband_mem_info_ptr)
    {
      result =  qurt_elite_memorymap_cache_invalidate((uint32_t)me_ptr->outband_mem_info_ptr, me_ptr->outband_mem_info.data_payload_size);
      if(ADSP_EOK != result)
      {
        MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Invalidate Cache failed for "
              "Open response Shared Memory with result 0x%x",me_ptr->capi_v2_olm_identifier, result);
        open_rsp.base_resp.result = result;
        goto __send_open_rsp;
      }
      else
      {
        // copy the Interface & Framework extension details from Shared memory to local memory
        if(ADSP_EOK == ap_resp_ptr->topo_extension_info_t.status)
        {
          uint32_t payload_size = ap_resp_ptr->topo_extension_info_t.inf_extn_payload_size
                                  + ap_resp_ptr->topo_extension_info_t.fwk_extn_payload_size
                                  + sizeof(topo_extn_info_t);

          uint32_t *ptr = (uint32_t*)qurt_elite_memory_malloc(payload_size, QURT_ELITE_HEAP_DEFAULT);

          if(ptr==NULL)
          {
            MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Failed to allocate memory to store the fwk/inf extn",me_ptr->capi_v2_olm_identifier);

            me_ptr->fwk_inf_extn_info_ptr = NULL;
            open_rsp.base_resp.result = ADSP_ENOMEMORY;
            goto __send_open_rsp;
          }
          else
          {
            me_ptr->fwk_inf_extn_info_ptr = ptr;

            uint32_t offset = memscpy((uint8_t*)(me_ptr->fwk_inf_extn_info_ptr),
                                      payload_size,
                                      &ap_resp_ptr->topo_extension_info_t,
                                      sizeof(topo_extn_info_t));

            uint32_t extn_payload_size = ap_resp_ptr->topo_extension_info_t.inf_extn_payload_size
                                         + ap_resp_ptr->topo_extension_info_t.fwk_extn_payload_size;

            if((payload_size - offset) == extn_payload_size)
            {
              shm_offset = memscpy((((uint8_t*)me_ptr->fwk_inf_extn_info_ptr) + offset),
                                   extn_payload_size,
                                   me_ptr->outband_mem_info_ptr,
                                   extn_payload_size);
#ifdef CAPI_V2_OLM_DEBUG
              MSG_1(MSG_SSID_QDSP6, DBG_LOW_PRIO, "CAPIv2 OLM 0x%8lX: FWK/INF extn information cached ",
                    me_ptr->capi_v2_olm_identifier);
#endif
            }
            else
            {
              MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Mismatched sizes to store"
                    "extension information" , me_ptr->capi_v2_olm_identifier);

              open_rsp.base_resp.result = ADSP_EBADPARAM;
              goto __send_open_rsp;
            }
          }
        }
#ifdef CAPI_V2_OLM_DEBUG
        MSG_2(MSG_SSID_QDSP6, DBG_LOW_PRIO, "CAPIv2 OLM 0x%8lX: number of module in the active topology %lu "
                                            , me_ptr->capi_v2_olm_identifier,ap_resp_ptr->active_topo_def.num_active_modules);
#endif

        me_ptr->olm_topo_def.active_topo_def.num_active_modules = ap_resp_ptr->active_topo_def.num_active_modules;
        me_ptr->olm_topo_def.active_topo_def.payload_size       = ap_resp_ptr->active_topo_def.payload_size;
        me_ptr->olm_topo_def.active_module_def                  = NULL;

        if(me_ptr->olm_topo_def.active_topo_def.num_active_modules > 0)
        {
          uint32_t payload_size =  me_ptr->olm_topo_def.active_topo_def.num_active_modules * sizeof(avcs_module_instance_info_t);

          uint32_t *ptr = (uint32_t*)qurt_elite_memory_malloc(payload_size, QURT_ELITE_HEAP_DEFAULT);

          if(ptr==NULL)
          {
            MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Failed to allocate "
                  "memory to cache the active topology definition", me_ptr->capi_v2_olm_identifier);

            open_rsp.dynamic_resp.active_topo_def.num_active_modules = 0;
            open_rsp.dynamic_resp.active_topo_def.payload_size       = 0;
            open_rsp.dynamic_resp.active_topo_def.active_module_list = NULL;

            open_rsp.base_resp.result = ADSP_ENOMEMORY;
            goto __send_open_rsp;
          }
          else
          {
            uint32_t copysize = memscpy((uint8_t*)(ptr),
                                        payload_size,
                                        (uint8_t *)me_ptr->outband_mem_info_ptr + shm_offset,
                                        ap_resp_ptr->active_topo_def.payload_size);

            shm_offset += copysize;

            me_ptr->olm_topo_def.active_module_def = (avcs_module_instance_info_t *)ptr;

            open_rsp.dynamic_resp.active_topo_def.num_active_modules = me_ptr->olm_topo_def.active_topo_def.num_active_modules;
            open_rsp.dynamic_resp.active_topo_def.payload_size       = copysize;
            open_rsp.dynamic_resp.active_topo_def.active_module_list = me_ptr->olm_topo_def.active_module_def;
#ifdef CAPI_V2_OLM_DEBBUG
            MSG_1(MSG_SSID_QDSP6, DBG_LOW_PRIO, "CAPIv2 OLM 0x%8lX: active topology definition cached "
                                                ,me_ptr->capi_v2_olm_identifier);
#endif
          }
        } //If num modules in active topo > 0
      } // If cache invalidate was successful
    } //If outband mem info ptr was allocated

#ifdef CAPI_V2_OLM_DEBUG

    MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "CAPIv2 OLM 0x%8lX: Open Response successful with container_apr_addr = %lx  ",
          me_ptr->capi_v2_olm_identifier,ap_resp_ptr->container_apr_addr);
#endif

  }
  else
  {
    MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: param_id = 0x%x, version = 0x%x"
                                          "Received invaild Open command response payload. ",
                                          me_ptr->capi_v2_olm_identifier, header_ptr->param_id, header_ptr->param_version);

    open_rsp.base_resp.result = ADSP_EFAILED;
  }

  __send_open_rsp:

  if(me_ptr->outband_mem_info_ptr)
  {
    elite_mem_mdf_mem_free(me_ptr->outband_mem_info_ptr,
                           me_ptr->outband_mem_info.mem_map_handle,
                           me_ptr->outband_mem_info.data_payload_size);

    me_ptr->outband_mem_info_ptr = NULL;
  }

  olm_response_cb_fn_wrapper(me_ptr,
                            CAPI_V2_OLM_RESP_OPEN,
                            (int8_t*)&open_rsp,
                            sizeof(open_resp_t),
                            token);
}

/**
 * This function is to process the Get Param Response from the Remote Container
 *
 * @param[in] me_ptr pointer to OLM module structure
 * @param[in] resp_pkt_ptr pointer to response apr packet
 *
 * @return none
 */
static void olm_process_get_param_response(capi_v2_olm_t* me_ptr, elite_apr_packet_t *resp_pkt_ptr)
{
  uint32_t rsp_header_size = 0;
  uint32_t param_size      = 0;
  uint32_t olm_rsp_status  = 0;
  int8_t * src_ptr = NULL;

  int8_t * pkt_buffer = (int8_t*)elite_apr_if_get_payload_ptr(resp_pkt_ptr);
  uint32_t token      = elite_apr_if_get_client_token(resp_pkt_ptr);

  uint32_t getp_rsp_version = 0;
  ADSPResult result = ADSP_EOK;
  uint32_t shm_mem_size = 0;

  olm_getparam_cmd_handle_t *cmd_hdl_ptr = NULL;
  ap_server_stat_cmn_header_t *header_ptr = NULL;
  ap_container_get_param_rsp_v1_t *status_ptr = NULL;

  /* Get the cached command info from the OLM handle list */
  cmd_hdl_ptr = (olm_getparam_cmd_handle_t *)get_cmd_payload(me_ptr,
                                                             CAPI_V2_PARAM_ID_OLM_GETPARAM,
                                                             token);
  if(NULL == cmd_hdl_ptr)
  {
    MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Failed to get command handler for token %d",
          me_ptr->capi_v2_olm_identifier, token);
    olm_rsp_status = ADSP_EFAILED;
    goto __send_get_param_rsp;
  }

  if(NULL == pkt_buffer)
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Received NULL payload for get param response",
          me_ptr->capi_v2_olm_identifier);
    olm_rsp_status = ADSP_EFAILED;
    goto __send_get_param_rsp;
  }

  /* Extract header from the response message. */
  header_ptr = reinterpret_cast<ap_server_stat_cmn_header_t*>(pkt_buffer);

  /* Handle get param response */
  if( ( AP_PARAM_ID_GET_CONTAINER_MID_PARAM_RSP == header_ptr->param_id ||
      AP_PARAM_ID_GET_CONTAINER_MID_IID_PARAM_RSP == header_ptr->param_id ) &&
      sizeof(ap_container_get_param_rsp_v1_t) <= header_ptr->param_size &&
      AP_PARAM_GET_CONTAINER_PARAM_RSP_COMMON_VERSION >= header_ptr->param_version &&
      0 != header_ptr->param_version)
  {
    pkt_buffer += sizeof(ap_server_stat_cmn_header_t);

    status_ptr = reinterpret_cast<ap_container_get_param_rsp_v1_t*>(pkt_buffer);

    if(AP_PARAM_ID_GET_CONTAINER_MID_PARAM_RSP == header_ptr->param_id)
    {
      getp_rsp_version = AP_PARAM_GET_MID_PARAM_RSP_VERSION;
    }
    else if(AP_PARAM_ID_GET_CONTAINER_MID_IID_PARAM_RSP == header_ptr->param_id)
    {
      getp_rsp_version = AP_PARAM_GET_MID_IID_PARAM_RSP_VERSION;
    }

    if(status_ptr->payload_version > getp_rsp_version)
    {
      MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Received unsupported version [0x%x] for get param rsp"
                                            "Expected version [0x%x]",
                                            me_ptr->capi_v2_olm_identifier, status_ptr->payload_version, getp_rsp_version);
      olm_rsp_status = ADSP_EUNSUPPORTED;
      goto __send_get_param_rsp;
    }

    pkt_buffer += sizeof(ap_container_get_param_rsp_v1_t);

    /* If OutBand Case */
    if(0 != cmd_hdl_ptr->cfg.bufferMemNode.unMemMapHandle)
    {

      if(NULL != cmd_hdl_ptr->shm_mem_ptr)
      {
        // OUT band case 2: Memory is not shared between the three processors (APPS - ADSP - Remote processor).
        src_ptr =  (int8_t*)cmd_hdl_ptr->shm_mem_ptr;
        shm_mem_size = cmd_hdl_ptr->cfg.max_data_size;
      }
      else
      {
        // OUT band case 1: memory shared with all the three processors (APPS - ADSP - Remote processor)
        src_ptr = (int8_t*)cmd_hdl_ptr->cfg.bufferMemNode.unVirtAddr;
        shm_mem_size = cmd_hdl_ptr->cfg.bufferMemNode.unMemSize;
      }
      if(ADSP_FAILED(result = qurt_elite_memorymap_cache_invalidate((uint32_t)src_ptr, shm_mem_size)))
      {
        MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Invalidate Cache failed"
                                            "for get param response with status 0x%x",
                                             me_ptr->capi_v2_olm_identifier,result);
        olm_rsp_status = result;
        goto __send_get_param_rsp;
      }
    }
    else /* In Band case*/
    {
      src_ptr = pkt_buffer;
    }

    if(AP_PARAM_ID_GET_CONTAINER_MID_IID_PARAM_RSP == header_ptr->param_id)
    {
      ap_container_get_mid_iid_param_rsp_v1_t *rsp_ptr = (ap_container_get_mid_iid_param_rsp_v1_t *)src_ptr;
      param_size = rsp_ptr->param_size;

      rsp_header_size = sizeof(ap_container_get_mid_iid_param_rsp_v1_t);
    }
    else
    {
      ap_container_get_mid_param_rsp_v1_t *rsp_ptr = (ap_container_get_mid_param_rsp_v1_t *)src_ptr;
      param_size = rsp_ptr->param_size;

      rsp_header_size = sizeof(ap_container_get_mid_param_rsp_v1_t);
    }

    /* Outband */
    if(0 != cmd_hdl_ptr->cfg.bufferMemNode.unMemMapHandle )
    {
      if(NULL != cmd_hdl_ptr->shm_mem_ptr)
      {
        /* Copy the data from shared memory*/
        memscpy((void *)cmd_hdl_ptr->cfg.bufferMemNode.unVirtAddr,
                cmd_hdl_ptr->cfg.bufferMemNode.unMemSize,
                (void *)src_ptr,
                (rsp_header_size + param_size) );

        elite_mem_mdf_mem_free(cmd_hdl_ptr->shm_mem_ptr,
                               cmd_hdl_ptr->mem_map_hdl,
                               cmd_hdl_ptr->shm_alloc_size);
      } //RR: Review this once
    }
    else
    {
      /* Copy the data from pkt to response */
      memscpy(cmd_hdl_ptr->cfg.payload,
              cmd_hdl_ptr->cfg.max_data_size,
              (void *)(src_ptr + rsp_header_size),
              param_size);
    }

    /* Update the param_size pointer */
    *(cmd_hdl_ptr->cfg.param_size) = param_size;

  } //If all the param ID & versions are correct
  else
  {
    MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Received invalid Get Param "
                                           "response payload.param_id = 0x%x, version = 0x%x  ",
                                           me_ptr->capi_v2_olm_identifier,header_ptr->param_id, header_ptr->param_version);

    olm_rsp_status = ADSP_EBADPARAM;
  }

__send_get_param_rsp:

    /* Send the get param response to the dynamic service thread */
    capi_v2_olm_getparam_resp_t getp_rsp_info;

    /* Update the fields based on the response packet */
    getp_rsp_info.result    = olm_rsp_status;
    getp_rsp_info.data_size = param_size;
    getp_rsp_info.version   = 0;
    //RR: TBD getp_rsp_info.payload_size = ?;

    if(cmd_hdl_ptr)
    {
      getp_rsp_info.data_ptr = cmd_hdl_ptr->cfg.payload;
    }
    else
    {
      getp_rsp_info.data_ptr = NULL;
    }

    /* Free the get param command handle payload*/
    if(cmd_hdl_ptr)
    {
      free_cmd_handle(me_ptr,
                      CAPI_V2_PARAM_ID_OLM_GETPARAM,
                      token);
      cmd_hdl_ptr = NULL;
    }

    olm_response_cb_fn_wrapper(me_ptr,
                              CAPI_V2_OLM_RESP_GETPARAM,
                              (int8_t*)&getp_rsp_info,
                              sizeof(capi_v2_olm_getparam_resp_t),
                              token);
}

/**
 * This function is to process the APR IBASIC Response from the Remote Container/Static Service
 *
 * @param[in] me_ptr pointer to OLM module structure
 * @param[in] resp_pkt_ptr pointer to response apr packet
 *
 * @return none
 */
static void olm_process_ibasic_response(capi_v2_olm_t* me_ptr, elite_apr_packet_t *resp_pkt_ptr)
{
  int8_t * buffer = (int8_t*)elite_apr_if_get_payload_ptr(resp_pkt_ptr);
  uint32_t token      = elite_apr_if_get_client_token(resp_pkt_ptr);

  aprv2_ibasic_rsp_result_t *header_ptr = reinterpret_cast<aprv2_ibasic_rsp_result_t*>(buffer);

  /* Extract response info from the basic response from the container*/
  uint32_t cmd_opcode = header_ptr->opcode;
  int      status     = header_ptr->status;

  switch(cmd_opcode)
  {
    case AP_CMD_FLUSH:
    {
      /* Return the Flush command response to dynamic service*/
      capi_v2_olm_flush_resp_t flush_resp;

      /* Copy the result from remote response message*/
      flush_resp.result = status;
      olm_response_cb_fn_wrapper(me_ptr,
                                CAPI_V2_OLM_RESP_FLUSH,
                                (int8_t *)&flush_resp,
                                sizeof(capi_v2_olm_flush_resp_t),
                                token );
      break;
    }

    case AP_CMD_SUSPEND:
    {
      /* Return the suspend command response to dynamic service*/
      capi_v2_olm_suspend_resp_t susp_resp;

      /* Copy the result from remote response message*/
      susp_resp.result = status;

      olm_response_cb_fn_wrapper(me_ptr,
                                CAPI_V2_OLM_RESP_SUSPEND,
                                (int8_t *)&susp_resp,
                                sizeof(capi_v2_olm_suspend_resp_t),
                                token );
      break;
    }

    case AP_CMD_OPEN:
    {
      /* Return the open command response to dynamic service*/
      capi_v2_olm_open_resp_t open_resp;

      /* Copy the result from remote response message*/
      open_resp.result = status;

      olm_response_cb_fn_wrapper(me_ptr,
                                CAPI_V2_OLM_RESP_OPEN,
                                (int8_t *)&open_resp,
                                sizeof(capi_v2_olm_open_resp_t),
                                token);
      break;
    }
    case AP_CMD_CLOSE:
    {
      /* Return the close command response to dynamic service*/
      capi_v2_olm_close_resp_t close_resp;

      /* Copy the result from remote response message*/
      close_resp.result = status;

      olm_response_cb_fn_wrapper(me_ptr,
                                CAPI_V2_OLM_RESP_CLOSE,
                                (int8_t *)&close_resp,
                                sizeof(capi_v2_olm_close_resp_t),
                                token);
      break;
    }
    case AP_CMD_RUN:
    {
      /* Return the close command response to dynamic service*/
      capi_v2_olm_run_resp_t run_resp;

      /* Copy the result from remote response message*/
      run_resp.result = status;


      olm_response_cb_fn_wrapper(me_ptr,
                                CAPI_V2_OLM_RESP_RUN,
                                (int8_t *)&run_resp,
                                sizeof(capi_v2_olm_run_resp_t),
                                token);
      break;
    }
    case AP_CMD_SET_PARAM_CONFIG_V2:
    case AP_CMD_SET_PARAM_CONFIG_V1:
    {
      /* Return the set param command response to dynamic service*/
      capi_v2_olm_setparam_resp_t setp_resp;

      /* Copy the result from remote response message*/
      setp_resp.result = status;

      /*
       * Free the shared memory payload if it was allocated by OLM.
       */
      olm_setparam_cmd_handle_t *cmd_hdl = (olm_setparam_cmd_handle_t *)get_cmd_payload(me_ptr, CAPI_V2_PARAM_ID_OLM_SETPARAM, token);
      if(NULL != cmd_hdl)
      {
        if(NULL != cmd_hdl->shm_mem_ptr)
        {
          elite_mem_mdf_mem_free(cmd_hdl->shm_mem_ptr,
                                 cmd_hdl->mem_map_hdl,
                                 cmd_hdl->shm_alloc_size);
        }

        /*Deallocate the set param command handle*/
        free_cmd_handle(me_ptr, CAPI_V2_PARAM_ID_OLM_SETPARAM, token);
      }

      olm_response_cb_fn_wrapper(me_ptr,
                                CAPI_V2_OLM_RESP_SETPARAM,
                                (int8_t *)&setp_resp,
                                sizeof(capi_v2_olm_setparam_resp_t),
                                token);

      break;
    }

    case AP_CMD_SET_PROP_CONFIG:
    {
      olm_setparam_cmd_handle_t *cmd_hdl = (olm_setparam_cmd_handle_t *)get_cmd_payload(me_ptr, CAPI_V2_PARAM_ID_SET_OLM_INF_EXTN_MODULE_CONFIG, token);
      if(NULL != cmd_hdl)
      {
        if(NULL != cmd_hdl->shm_mem_ptr)
        {
          elite_mem_mdf_mem_free(cmd_hdl->shm_mem_ptr,
                                 cmd_hdl->mem_map_hdl,
                                 cmd_hdl->shm_alloc_size);
        }

        /*Deallocate the set inf extn command handle*/
        free_cmd_handle(me_ptr, CAPI_V2_PARAM_ID_SET_OLM_INF_EXTN_MODULE_CONFIG, token);
      }

      break;
    }

    default:
    {
      MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Invaild response Opcode = 0x%x in basic response.",
                                             me_ptr->capi_v2_olm_identifier, cmd_opcode);
      break;
    }
  }

}
