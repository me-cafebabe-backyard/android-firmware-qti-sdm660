/**
@file olm_cmd_handler.cpp

@brief This file contains the command handling functionality for off-loading module

 */

/*========================================================================

Edit History

when          who            what, where, why
--------      ---            -------------------------------------------------------
11/27/2017    bvodapal       Initial version (moved the command handling code from olm_utils)

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
 * This function is used to send the Open Command to the Remote AP Static Svc
 *
 * @param[in] me_ptr, pointer to the CAPI lib
 *
 * @return ADSPResult, result code
 */
ADSPResult olm_send_open_cmd(capi_v2_olm_t *me_ptr)
{
  ADSPResult result = ADSP_EOK;

  /* Get the modules information*/
  uint32_t num_modules = me_ptr->olm_cfg.dynamic_cfg->olm_topo_info_ptr->num_modules;
  if(0 == num_modules)
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Received zero number of modules in Open Command",
                                          me_ptr->capi_v2_olm_identifier);
    return ADSP_EBADPARAM;
  }

  uint32_t modules_info_size = num_modules * (sizeof(ap_module_instance_info_t));

  /* Allocate open command Payload */
  uint32 payload_size = modules_info_size;

  /* add size of the headers for  # AP_PARAM_ID_CREATE_CONTAINER,
   *                              # AP_PARAM_ID_CREATE_CONTAINER_PROP &
   *                              # AP_PARAM_ID_CREATE_CONTAINER_OUTBAND_INFO */
  payload_size += 3 * sizeof(ap_server_stat_cmn_header_t);

  /* add container property and outband info sizes */
  payload_size += sizeof(ap_create_container_prop_v1_t);
  payload_size += sizeof(ap_create_container_outband_info_v1_t);

  uint32_t rem_mem_map_hdl  = 0;
  uint32_t rem_virt_offset  = 0;
  void     *rem_shm_mem_ptr = NULL;

  uint32_t max_data_size    = OLM_OPEN_SHM_SIZE;

  rem_shm_mem_ptr = elite_mem_mdf_malloc( max_data_size,
                                          me_ptr->remote_proc_id,
                                          &rem_mem_map_hdl,
                                          &rem_virt_offset);
  if(NULL ==  rem_shm_mem_ptr)
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Failed to allocate "
    		                                  "shared memory for open command",
    		                                  me_ptr->capi_v2_olm_identifier);
    max_data_size = 0;
    me_ptr->outband_mem_info.shm_virtual_offset = 0;
    me_ptr->outband_mem_info.mem_map_handle     = 0;
    me_ptr->outband_mem_info.data_payload_size  = 0;
    return ADSP_ENOMEMORY;
  }
  else
  {
    me_ptr->outband_mem_info.shm_virtual_offset = rem_virt_offset;
    me_ptr->outband_mem_info.data_payload_size  = max_data_size;
    me_ptr->outband_mem_info.mem_map_handle     = rem_mem_map_hdl;

#ifdef CAPI_V2_OLM_DEBUG
	  MSG_4(MSG_SSID_QDSP6, DBG_LOW_PRIO,"CAPIv2 OLM_%lu: Open Command Remote outband Memory info"
			                                 "rem_mem_map_hdl: %u , rem_phy_addr_lsw %lu, max_data_size %lu ",
			                                  me_ptr->capi_v2_olm_identifier, rem_mem_map_hdl, rem_virt_offset, max_data_size);
#endif
    me_ptr->outband_mem_info_ptr = rem_shm_mem_ptr;
  }

#ifdef CAPI_V2_OLM_DEBUG
  MSG_2(MSG_SSID_QDSP6, DBG_LOW_PRIO,"CAPIv2 OLM 0x%8lX: Open Command Remote addr: %u ",
                                      me_ptr->capi_v2_olm_identifier, me_ptr->remote_svc_apr_addr);
#endif

  /* Allocate the open command packet */
    elite_apr_packet_t *elite_pkt_ptr = NULL;

  /* Send the packet to the remote server */
  result = elite_apr_if_alloc_cmd(me_ptr->apr_handle,
                                  me_ptr->apr_addr,
                                  me_ptr->olm_cfg.dynamic_cfg->olm_iid,
                                  me_ptr->remote_svc_apr_addr,
                                  DEFAULT_OLM_AP_SESSION_PORT, // change to zero
                                  me_ptr->olm_cfg.olm_open_cfg.token,
                                  AP_CMD_OPEN,
                                  payload_size,
                                  &elite_pkt_ptr);
  if(ADSP_FAILED(result))
  {
    MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Could not allocate apr packet for Open Command with result 0x%x",
                                          me_ptr->capi_v2_olm_identifier, result);
    return result;
  }

#ifdef CAPI_V2_OLM_DEBUG

  MSG_3(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "CAPIv2 OLM 0x%8lX: Open packet created successful. remote_server_addr = %lu olm_apr_addr: %lu ",
                                        me_ptr->capi_v2_olm_identifier, me_ptr->remote_svc_apr_addr, me_ptr->apr_addr );

#endif

  /* Get remote command payload pointer in the packet*/
  uint8_t *payload = (uint8_t*)elite_apr_if_get_payload_ptr(elite_pkt_ptr);
  if(NULL == payload)
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Open Cmd Packet payload is null. ",
                                          me_ptr->capi_v2_olm_identifier);
    return ADSP_EFAILED;
  }

  /* Initialize the AP_PARAM_ID_CREATE_CONTAINER header  */
  int8_t* buffer = (int8_t*)payload;

  ap_server_stat_cmn_header_t *header_ptr = reinterpret_cast<ap_server_stat_cmn_header_t*>(buffer);
  header_ptr->module_id         = me_ptr->remote_module_id;
  header_ptr->instance_id       = 1;
  header_ptr->param_id          = AP_PARAM_ID_CREATE_CONTAINER;
  header_ptr->reserved          = 0;
  header_ptr->param_size        = modules_info_size;
  header_ptr->param_version     = AP_PARAM_CREATE_CONTAINER_VERSION;
  header_ptr->param_struct_size = sizeof(ap_module_instance_info_t);

  buffer += sizeof(ap_server_stat_cmn_header_t);

  ap_module_instance_info_t* cur_moduleinfo_ptr     = (ap_module_instance_info_t*)  (buffer);
  avcs_module_instance_proc_info_t *olm_modules_ptr = me_ptr->olm_cfg.dynamic_cfg->olm_topo_info_ptr->module_info;

  for(uint16_t idx = 0; idx < num_modules  ; idx++)
  {
    /* Copy info from topology into the payload buffer*/
    cur_moduleinfo_ptr->module_id   = olm_modules_ptr->module_id;
    cur_moduleinfo_ptr->instance_id = olm_modules_ptr->instance_id;
    cur_moduleinfo_ptr->reserved    = 0;

    /* Udpate the module pointers */
    cur_moduleinfo_ptr++;
    olm_modules_ptr++;
  }
  buffer +=  modules_info_size;

  header_ptr = reinterpret_cast<ap_server_stat_cmn_header_t*>(buffer);
  header_ptr->module_id         = me_ptr->remote_module_id;
  header_ptr->instance_id       = 1;
  header_ptr->param_id          = AP_PARAM_ID_CREATE_CONTAINER_PROP;
  header_ptr->reserved          = 0;
  header_ptr->param_size        = sizeof(ap_create_container_prop_v1_t);
  header_ptr->param_version     = AP_PARAM_CREATE_CONTAINER_PROP_VERSION;
  header_ptr->param_struct_size = sizeof(ap_create_container_prop_v1_t);

  buffer += sizeof(ap_server_stat_cmn_header_t);
  ap_create_container_prop_v1_t *container_prop_ptr = reinterpret_cast<ap_create_container_prop_v1_t*>(buffer);

  /* Initialize the AP_PARAM_ID_CREATE_CONTAINER_PROP payload */
  container_prop_ptr->client_frame_size = me_ptr->olm_cfg.dynamic_cfg->frame_size;
  container_prop_ptr->scale_factor      = me_ptr->olm_cfg.dynamic_cfg->scale_factor;
  container_prop_ptr->usecase_type      = (me_ptr->olm_cfg.dynamic_cfg->is_input_output_realtime == 0) ? 0 : 1 ;

  buffer += sizeof(ap_create_container_prop_v1_t);

  header_ptr = reinterpret_cast<ap_server_stat_cmn_header_t*>(buffer);
  header_ptr->module_id         = me_ptr->remote_module_id;
  header_ptr->instance_id       = 1;
  header_ptr->param_id          = AP_PARAM_ID_CREATE_CONTAINER_OUTBAND_INFO;
  header_ptr->reserved          = 0;
  header_ptr->param_size        = sizeof(ap_create_container_outband_info_v1_t);
  header_ptr->param_version     = AP_PARAM_CREATE_CONTAINER_OUTBAND_INFO_VERSION;
  header_ptr->param_struct_size = sizeof(ap_create_container_outband_info_v1_t);

  buffer += sizeof(ap_server_stat_cmn_header_t);
  ap_create_container_outband_info_v1_t *extn_info =  reinterpret_cast<ap_create_container_outband_info_v1_t*>(buffer);
  extn_info->shm_virtual_offset = me_ptr->outband_mem_info.shm_virtual_offset;
  extn_info->data_payload_size  = me_ptr->outband_mem_info.data_payload_size;
  extn_info->mem_map_handle     = me_ptr->outband_mem_info.mem_map_handle;

#ifdef OLM_LATENCY_MEASUREMENT
  MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: sending open command at time %lld",me_ptr->capi_v2_olm_identifier, qurt_elite_timer_get_time());
#endif

  /* Send the packet to the remote AP Static Service */
  result = elite_apr_if_cmd_fwd(me_ptr->apr_handle, elite_pkt_ptr);
  if(ADSP_FAILED(result))
  {
    MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Failed to send open cmd to with result 0x%x", me_ptr->capi_v2_olm_identifier, result);
    return result;
  }

#ifdef CAPI_V2_OLM_DEBUG

  MSG_3(MSG_SSID_QDSP6, DBG_LOW_PRIO, "CAPIv2 OLM 0x%8lX: sent open cmd successfully. remote_server_addr = %lu olm_apr_addr: %lu ",
                                       me_ptr->capi_v2_olm_identifier, me_ptr->remote_svc_apr_addr, me_ptr->apr_addr );

#endif

  return result;

}

/**
 * This function is used to send the Run Command to the Remote AP Static Svc
 *
 * @param[in] me_ptr, pointer to the CAPI lib
 * @param[in] cfg_ptr, pointer to the command config
 *
 * @return ADSPResult, result code
 */
ADSPResult olm_send_run_cmd(capi_v2_olm_t *me_ptr, capi_v2_olm_run_t *cfg_ptr)
{
  ADSPResult result = ADSP_EOK;

  /* send the RUN command to AP contianer */
  result = olm_send_simple_ap_container_cmd(me_ptr,
                                            AP_CMD_RUN,
                                            AP_PARAM_ID_RUN,
                                            AP_PARAM_RUN_VERSION,
                                            0,
                                            cfg_ptr->token,
                                            me_ptr->create_resp_info.container_apr_addr,
                                            DEFAULT_OLM_AP_SESSION_PORT);

  return result;

}

/**
 * This function is used to copy the set param payload for the relevant modules
 * to be sent the Remote Container.
 *
 * @param[in] me_ptr, pointer to the CAPI lib
 * @param[in] cfg_ptr, pointer to the command config
 * @param[in] dest_calibdata_ptr, destination pointer
 * @param[in] dest_calibdata_size, size of destination pointer
 * @param[in] src_calibdata_ptr, source pointer
 * @param[in] src_calibdata_size, size of source pointer
 *
 * @return ADSPResult, result code
 */
ADSPResult olm_create_setparam_payload(capi_v2_olm_t *me_ptr,
                                       capi_v2_olm_setparam_t *cfg_ptr,
                                       int8_t *dest_calibdata_ptr,
                                       uint32_t dest_calibdata_size,
                                       int8_t *src_calibdata_ptr,
                                       uint32_t src_calibdata_size)
{
  ADSPResult result = ADSP_EOK;

  uint32_t mode = cfg_ptr->mode;
  uint32_t module_id,instance_id;
  uint32_t param_id =0;

  uint32_t param_size, ap_header_size;
  uint32_t stream_header_size =0;

  while (src_calibdata_size > 0 && dest_calibdata_size > 0)
  {
    uint32_t req_payload_size = (mode == GIVEN_INSTANCE)? sizeof(asm_stream_param_data_v3_t) : sizeof(asm_stream_param_data_v2_t);
    if (src_calibdata_size < req_payload_size)
    {
      MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Incorrect payload size,"
    		                                    " payload size=%lu, req payload size=%hu.",
			                                      me_ptr->capi_v2_olm_identifier, src_calibdata_size, req_payload_size);
     result = ADSP_EFAILED;
     break;
    }
    if(GIVEN_INSTANCE == mode)
    {
      asm_stream_param_data_v3_t *pDataPayload = (asm_stream_param_data_v3_t *)(src_calibdata_ptr);
      module_id   = pDataPayload->module_id;
      instance_id = (uint32_t)pDataPayload->instance_id;
      param_size  = pDataPayload->param_size;
      param_id    = pDataPayload->param_id;

      stream_header_size = sizeof(asm_stream_param_data_v3_t);
      ap_header_size     = sizeof(ap_container_set_mid_iid_param_info_v1_t);

      req_payload_size = stream_header_size + param_size;
    }
    else
    {
      asm_stream_param_data_v2_t *pDataPayload = (asm_stream_param_data_v2_t *)(src_calibdata_ptr);
      module_id   = pDataPayload->module_id;
      instance_id = 0;
      param_size  = pDataPayload->param_size;
      param_id    = pDataPayload->param_id;

      stream_header_size = sizeof(asm_stream_param_data_v2_t);
      ap_header_size     = sizeof(ap_container_set_mid_param_info_v1_t);

      req_payload_size = stream_header_size + param_size;
      if (mode != ZERO_INSTANCE && ADSP_FAILED(olm_get_instance_id(me_ptr->olm_cfg.dynamic_cfg->olm_topo_info_ptr,module_id,&instance_id)))
      {
        result = ADSP_EBADPARAM;
        return result;
      }
    }

    /* Check if module is present in the OLM topology */
    if(TRUE == olm_check_if_module_present(me_ptr->olm_cfg.dynamic_cfg->olm_topo_info_ptr, module_id, instance_id) &&
        dest_calibdata_size >= req_payload_size)
    {
      /* Copy the header info based on the version of the source header*/
      if( GIVEN_INSTANCE == mode)
      {
        /* Initalize the header data*/
        ap_container_set_mid_iid_param_info_v1_t *temp_ptr = (ap_container_set_mid_iid_param_info_v1_t *)dest_calibdata_ptr;
        temp_ptr->module_id    = module_id;
        temp_ptr->instance_id  = instance_id;
        temp_ptr->reserved     = 0;
        temp_ptr->param_id     = param_id;
        temp_ptr->param_size   = param_size;
      }
      else
      {
        /* Initialize the header data*/
        ap_container_set_mid_param_info_v1_t *temp_ptr = (ap_container_set_mid_param_info_v1_t *)dest_calibdata_ptr;
        temp_ptr->module_id    = module_id;
        temp_ptr->param_id     = param_id;
        temp_ptr->param_size   = param_size;
      }

      /* Advance the calib data ptr*/
      dest_calibdata_ptr +=  ap_header_size;

      /* get the source param addr */
      uint8_t *src_param_ptr =  (uint8_t *)( src_calibdata_ptr + stream_header_size );

      /* Copy the param payload into the new calibration memory blob*/
      memscpy((void *)dest_calibdata_ptr,
              param_size,
              (void *)src_param_ptr,
              param_size);

      /*Advance the calibration pointer by parameter calib size*/
      dest_calibdata_ptr = dest_calibdata_ptr + param_size;

      /* Update the left over memory in new calibration pointer*/
      dest_calibdata_size = dest_calibdata_size - (ap_header_size + param_size);
    }

    /* Advance the source calibration pointers*/
    src_calibdata_ptr       = src_calibdata_ptr + req_payload_size;
    src_calibdata_size      = src_calibdata_size - req_payload_size;
  }

  return result;
}

/**
 * This function is used to calculate the payload size for the relevant modules
 * to be sent the Remote Container.
 *
 * @param[in] me_ptr, pointer to the CAPI lib
 * @param[in] cfg_ptr, pointer to the command config
 * @param[in] new_size_ptr, pointer to the calculated payload size
 *
 * @return ADSPResult, result code
 */
static ADSPResult olm_get_valid_calib_size(capi_v2_olm_t *me_ptr,
                                         capi_v2_olm_setparam_t *cfg_ptr,
                                         uint32_t *new_size_ptr)
{
#ifdef CAPI_OLM_DEBUG
  MSG_1(MSG_SSID_QDSP6, DBG_LOW_PRIO, "CAPIv2 OLM 0x%8lX: Set param Begin.",me_ptr->capi_v2_olm_identifier);
#endif
  ADSPResult result = ADSP_EOK;

  uint32_t mode           = cfg_ptr->mode;
  uint32_t payload_size   = cfg_ptr->payload_size;
  uint8_t  *src_calib_ptr = (uint8_t * )cfg_ptr->payload_ptr;

  uint32_t module_id;
  uint32_t instance_id;
  uint32_t param_size;
  uint32_t ap_header_size;
  uint32_t param_id;

  /* Get the new payload size*/
  uint32_t new_payload_size =0;

  /* Check the source calib data payload size*/
  while(payload_size > 0)
  {
    uint32_t req_payload_size = (mode == GIVEN_INSTANCE)? sizeof(asm_stream_param_data_v3_t) : sizeof(asm_stream_param_data_v2_t);
    if (payload_size < req_payload_size)
    {
      MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Mismatched payload sizes received "
                                            "payload size=%lu, req payload size=%hu.",
                                            me_ptr->capi_v2_olm_identifier, payload_size, req_payload_size);
      return result;
    }
    if(GIVEN_INSTANCE == mode)
    {
      asm_stream_param_data_v3_t *pDataPayload = (asm_stream_param_data_v3_t *)(src_calib_ptr);
      module_id        = pDataPayload->module_id;
      instance_id      = (uint32_t)pDataPayload->instance_id;
      param_size       = pDataPayload->param_size;
      param_id         = pDataPayload->param_id;
      ap_header_size   = sizeof(ap_container_set_mid_iid_param_info_v1_t);
      req_payload_size = sizeof(asm_stream_param_data_v3_t) + param_size;
    }
    else
    {
      asm_stream_param_data_v2_t *pDataPayload = (asm_stream_param_data_v2_t *)(src_calib_ptr);
      module_id        = pDataPayload->module_id;
      instance_id      = 0;
      param_size       = pDataPayload->param_size;
      param_id         = pDataPayload->param_id;
      ap_header_size   = sizeof(ap_container_set_mid_param_info_v1_t);
      req_payload_size = sizeof(asm_stream_param_data_v2_t) + param_size;

      if (mode != ZERO_INSTANCE && ADSP_FAILED(olm_get_instance_id(me_ptr->olm_cfg.dynamic_cfg->olm_topo_info_ptr ,module_id,&instance_id)))
      {
        result = ADSP_EBADPARAM;
        return result;
      }

    }

    /* Check if the param_size is within the source calibration boundary */
    if (payload_size < req_payload_size)
    {
      MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Incorrect payload size, "
                                            "payload size=%lu, req payload size=%hu.",
                                            me_ptr->capi_v2_olm_identifier, payload_size, req_payload_size);
      result = ADSP_EFAILED;
      return result;
    }

    /* Check if module is present in the OLM topology */
    if(TRUE == olm_check_if_module_present(me_ptr->olm_cfg.dynamic_cfg->olm_topo_info_ptr, module_id, instance_id) )
    {
      new_payload_size += (ap_header_size + param_size);
    }

    src_calib_ptr += req_payload_size;
    payload_size -= req_payload_size;

    /* Check validity of the old calibration boundaries*/
    if (((param_size % 4) != 0) && (payload_size > 0))
    {
      MSG_5(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: set param size for"
                                            "Module-Instance with ID 0x%lx-0x%lx, Param ID 0x%lx "
                                            "is %lu which is not a multiple of 4. Aborting further processing.",
			                                       me_ptr->capi_v2_olm_identifier, module_id, instance_id, param_id, param_size);
      result = ADSP_EFAILED;
      return result;
    }
  }

  *new_size_ptr = new_payload_size;
  return result;
}

/**
 * This function is used to send the Set Param Command to the
 * Remote Container service,
 *
 * @param[in] me_ptr, pointer to the CAPI lib
 * @param[in] cfg_ptr, pointer to the command config
 *
 * @return ADSPResult, result code
 */
ADSPResult olm_set_param(capi_v2_olm_t *me_ptr,
                         capi_v2_olm_setparam_t *cfg_ptr)
{
  ADSPResult result = ADSP_EOK;

  uint32_t token              = cfg_ptr->token;
  uint32_t mode               = cfg_ptr->mode;
  uint32_t src_calibdata_size = cfg_ptr->payload_size;
  uint32_t cmd_op_code        = 0;
  uint32_t param_id           = 0;
  uint32_t setp_version = 0, setp_size = 0;

  uint32_t pkt_payload_sz = 0;
  uint8_t *src_calib_ptr = (uint8_t *)cfg_ptr->payload_ptr;

  uint32_t rem_mem_map_hdl  = 0;
  uint32_t rem_phy_addr_lsw = 0;
  uint32_t rem_phy_addr_msw = 0;
  uint32_t rem_virt_offset  = 0;

  bool_t is_inband = FALSE;

  elite_apr_packet_t        *elite_pkt_ptr = NULL;
  olm_setparam_cmd_handle_t *cmd_hdl       = NULL;

  if(!IS_ALIGN_4_BYTE((uint32_t)src_calib_ptr))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Set param pointer is not"
    		                                  " aligned to 4 bytes. Aborting.",
    		                                  me_ptr->capi_v2_olm_identifier);
    result =  ADSP_EFAILED;
    return result;
  }

  /* Send the packet to the remote server */
  switch(mode)
  {
    case GIVEN_INSTANCE:
    {
      cmd_op_code  = AP_CMD_SET_PARAM_CONFIG_V2;
      param_id     = AP_PARAM_ID_SET_CONTAINER_MID_IID_PARAM;
      setp_version = AP_PARAM_SET_MID_IID_PARAM_VERSION;
      setp_size    = sizeof(ap_container_set_mid_iid_param_info_v1_t);
      break;
    }
    case ZERO_INSTANCE:
    {
      cmd_op_code  = AP_CMD_SET_PARAM_CONFIG_V1;
      param_id     = AP_PARAM_ID_SET_CONTAINER_MID_PARAM;
      setp_version = AP_PARAM_SET_MID_PARAM_VERSION;
      setp_size    = sizeof(ap_container_set_mid_param_info_v1_t);
      break;
    }
    default:
    {
      MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Received Invalid mode %ul.",
    		                                    me_ptr->capi_v2_olm_identifier, mode);
      result = ADSP_EBADPARAM;
      return result;
    }
  }

  /* Identify the relevant payload to the offloaded module list and calculate the updated size */
  uint32_t in_band_calib_size  = 0;
  uint32_t out_band_calib_size = 0;

  /* Updated set param calib data size*/
  uint32_t new_calibdata_size = 0;
  uint8_t *payload_ptr = NULL;

  ap_server_stat_cmn_header_t *header_ptr = NULL;
  ap_container_set_param_config_info_v1_t *set_cfg_info_ptr = NULL;

  /* Get the new payload size, this function calculates the new
   * payload size by removing the unwanted module calib data
  */
  result = olm_get_valid_calib_size(me_ptr, cfg_ptr, &new_calibdata_size);
  if(ADSP_FAILED(result))
  {
    MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Failed to parse the set param payload with result 0x%x",
    		                                  me_ptr->capi_v2_olm_identifier, result);
    return result;
  }

  /* If the new payload size is zero, implies the set param payload is irrelevant to the OLM's sub graph
   * Since we are returning ADSP_EOK, the OLM is expected to raise a call back with the same status.
   * This ensures that the dynamic service command handler doesnt wait for a response from this OLM.
   */
  if(0 == new_calibdata_size)
  {
    MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"CAPIv2 OLM 0x%8lX: Returning. "
    		                                 "irrelevant calib data for this OLM.",me_ptr->capi_v2_olm_identifier);
    capi_v2_olm_setparam_resp_t setp_resp;
    setp_resp.result = ADSP_EOK;
    olm_response_cb_fn_wrapper(me_ptr,
                              CAPI_V2_OLM_RESP_SETPARAM,
                              (int8_t *)&setp_resp,
                              sizeof(capi_v2_olm_setparam_resp_t),
                              token);
    result =  ADSP_EOK;
    return result;
  }

  /* Check if the given payload is outband */
  if(0 != cfg_ptr->bufferMemNode.unMemMapHandle)
  {

    /* Get the mem handle from the set param configuration from Dynamic service*/
    uint32_t in_mem_map_hdl  = cfg_ptr->bufferMemNode.unMemMapHandle;
    uint32_t in_phy_addr_lsw = cfg_ptr->bufferMemNode.unPhysAddrLsw;
    uint32_t in_phy_addr_msw = cfg_ptr->bufferMemNode.unPhysAddrMsw;

    out_band_calib_size = cfg_ptr->bufferMemNode.unMemSize;

    /* Get the memory handle for the remote processor */
    /* CASE 1: Memory shared with me_ptr->proc_id, returns a valid mem handle*/
    result = olm_get_client_shm_mem_handle(me_ptr->remote_proc_id,
                                         in_mem_map_hdl,
                                         in_phy_addr_lsw,
                                         in_phy_addr_msw,
                                         &rem_mem_map_hdl,
                                         &rem_phy_addr_lsw,
                                         &rem_phy_addr_msw);


    if(ADSP_FAILED(result))
    {
      /* CASE 1: Memory is not shared with client_proc_id */
      out_band_calib_size = new_calibdata_size;

      /* Allocate shared memory for the given client processor ID */
      void* temp_ptr = elite_mem_mdf_malloc( out_band_calib_size,
                                             me_ptr->remote_proc_id,
                                             &rem_mem_map_hdl,
                                             &rem_virt_offset);

      if(NULL ==  temp_ptr)
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Couldn't allocate shared memory "
                                              "for Set param.",me_ptr->capi_v2_olm_identifier);
        result = ADSP_ENOMEMORY;
        return result;
      }

      /* Copy the payload to newly allocated shared memory*/
      result =  olm_create_setparam_payload(me_ptr, cfg_ptr,
                                            (int8_t*) temp_ptr,
                                            out_band_calib_size,
                                            (int8_t*) src_calib_ptr,
                                            src_calibdata_size);
      if(ADSP_FAILED(result))
      {
        MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Could not create the Out band "
        		                                  "set param payload with result 0x%x",
        		                                  me_ptr->capi_v2_olm_identifier, result);
        elite_mem_mdf_mem_free(temp_ptr, rem_mem_map_hdl, out_band_calib_size);
        return result;
      }

      /* Flush the cache for the set param payload  */
      if(ADSP_FAILED(result = qurt_elite_memorymap_cache_flush((uint32_t)temp_ptr, out_band_calib_size)))
      {
        MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Failed to flush "
                                              "set param payload with result 0x%x",
                                              me_ptr->capi_v2_olm_identifier, result);
        elite_mem_mdf_mem_free(temp_ptr, rem_mem_map_hdl, out_band_calib_size);
        return result;
      }

      /* Store the shared memory region info and free it
         when the response is received */

      cmd_hdl = (olm_setparam_cmd_handle_t *)qurt_elite_memory_malloc(sizeof(olm_setparam_cmd_handle_t),
                                                                                                 QURT_ELITE_HEAP_DEFAULT);
      if(NULL == cmd_hdl)
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Failed to allocate memory "
                                               "for command handle.", me_ptr->capi_v2_olm_identifier);
        elite_mem_mdf_mem_free(temp_ptr, rem_mem_map_hdl, out_band_calib_size);
        result = ADSP_ENOMEMORY;
        return result;
      }

      cmd_hdl->shm_mem_ptr = temp_ptr;
      cmd_hdl->mem_map_hdl = rem_mem_map_hdl;
      cmd_hdl->shm_alloc_size = out_band_calib_size;

      result = store_cmd_payload(me_ptr,
                        CAPI_V2_PARAM_ID_OLM_SETPARAM,
                        token,
                        cmd_hdl);

      if(ADSP_FAILED(result))
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Failed to cache command info "
                                                       " for set param", me_ptr->capi_v2_olm_identifier);
        elite_mem_mdf_mem_free(temp_ptr, rem_mem_map_hdl, out_band_calib_size);
        qurt_elite_memory_free(cmd_hdl);
        return result;
      }
    } /* If SHM is not accessible across all the processors */
  }
  else /* IN BAND case*/
  {
    in_band_calib_size = new_calibdata_size;
    is_inband = TRUE;
  }

  pkt_payload_sz = sizeof(ap_server_stat_cmn_header_t);
  pkt_payload_sz += sizeof(ap_container_set_param_config_info_v1_t);

  /* If out band, in_band_calib_size = 0 */
  pkt_payload_sz += in_band_calib_size;

  result = elite_apr_if_alloc_cmd(me_ptr->apr_handle,
                                  me_ptr->apr_addr,
                                  me_ptr->olm_cfg.dynamic_cfg->olm_iid,
                                  me_ptr->create_resp_info.container_apr_addr,
                                  DEFAULT_OLM_AP_SESSION_PORT,
                                  token,
                                  cmd_op_code,
                                  pkt_payload_sz,
                                  &elite_pkt_ptr);
  if(ADSP_FAILED(result))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Could not allocate apr packet for set param",
                                          me_ptr->capi_v2_olm_identifier);
    if(cmd_hdl)
    {
      elite_mem_mdf_mem_free(cmd_hdl->shm_mem_ptr,
                             cmd_hdl->mem_map_hdl,
                             cmd_hdl->shm_alloc_size);

      free_cmd_handle(me_ptr, CAPI_V2_PARAM_ID_OLM_SETPARAM, token);
    }
    return result;
  }

  payload_ptr = (uint8_t*)elite_apr_if_get_payload_ptr(elite_pkt_ptr);
  if(NULL == payload_ptr)
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX:Set Param Packet payload is null. ",
                                           me_ptr->capi_v2_olm_identifier);
    if(cmd_hdl)
    {
      elite_mem_mdf_mem_free(cmd_hdl->shm_mem_ptr,
                             cmd_hdl->mem_map_hdl,
                             cmd_hdl->shm_alloc_size);

      free_cmd_handle(me_ptr, CAPI_V2_PARAM_ID_OLM_SETPARAM, token);
    }
    elite_apr_if_free(me_ptr->apr_handle, elite_pkt_ptr);
    return ADSP_EFAILED;
  }

  /* Update the packet header structure */
  header_ptr = (ap_server_stat_cmn_header_t*) payload_ptr;
  header_ptr->module_id         = me_ptr->remote_module_id;
  header_ptr->instance_id       = 1;
  header_ptr->param_id          = param_id;
  header_ptr->reserved          = 0;
  header_ptr->param_size        = sizeof(ap_container_set_param_config_info_v1_t) + in_band_calib_size;
  header_ptr->param_version     = AP_PARAM_SET_CONTAINER_PARAM_COMMON_VERSION;
  header_ptr->param_struct_size = sizeof(ap_container_set_param_config_info_v1_t);

  payload_ptr = payload_ptr + sizeof(ap_server_stat_cmn_header_t);

  /* Supported version is 1, so typecast and access the memory directly */
  /* Update the container set configuration info structure */
  set_cfg_info_ptr = (ap_container_set_param_config_info_v1_t*) payload_ptr ;

  set_cfg_info_ptr->shm_virtual_offset  = rem_virt_offset;
  set_cfg_info_ptr->mem_map_handle      = rem_mem_map_hdl;
  set_cfg_info_ptr->data_payload_size   = out_band_calib_size;
  set_cfg_info_ptr->payload_version     = setp_version;
  set_cfg_info_ptr->payload_struct_size = setp_size;

  if(is_inband)
  {
    /* If in band case*/
    set_cfg_info_ptr->data_payload_size = in_band_calib_size;

    payload_ptr = payload_ptr + sizeof(ap_container_set_param_config_info_v1_t);
    uint8_t* dest_calibdata_ptr = payload_ptr;

    result =  olm_create_setparam_payload(me_ptr, cfg_ptr,
                                          (int8_t*) dest_calibdata_ptr,
                                          in_band_calib_size,
                                          (int8_t*) src_calib_ptr,
                                          src_calibdata_size);
    if(ADSP_FAILED(result))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Could not create the In band set param payload.",
                                            me_ptr->capi_v2_olm_identifier);
      elite_apr_if_free(me_ptr->apr_handle, elite_pkt_ptr);
      //Since it is inband, no command information is cached. Simply return error

      return result;
    }
  }

#ifdef CAPI_V2_OLM_DEBUG
  MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Set params End.", me_ptr->capi_v2_olm_identifier);
#endif

#ifdef OLM_LATENCY_MEASUREMENT
MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: olm_set_param: Sent cmd to remote service at time %lld.", me_ptr->capi_v2_olm_identifier, qurt_elite_timer_get_time());
#endif

  /* Send the packet to the remote server */
  result = elite_apr_if_cmd_fwd(me_ptr->apr_handle, elite_pkt_ptr);
  if(ADSP_FAILED(result))
  {
    MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Fail to send Set Param with result 0x%x",
                                           me_ptr->capi_v2_olm_identifier, result);
    if(cmd_hdl)
    {
      elite_mem_mdf_mem_free(cmd_hdl->shm_mem_ptr,
                             cmd_hdl->mem_map_hdl,
                             cmd_hdl->shm_alloc_size);

      free_cmd_handle(me_ptr, CAPI_V2_PARAM_ID_OLM_SETPARAM, token); //Free the handle
    }

    return result;
  }
  return result;
}

/**
 * This function is used to send the Get Param Command to the
 * Remote Container service,
 *
 * @param[in] me_ptr, pointer to the CAPI lib
 * @param[in] cfg_ptr, pointer to the command config
 *
 * @return ADSPResult, result code
 */
ADSPResult olm_get_param(capi_v2_olm_t *me_ptr, capi_v2_olm_getparam_t *cfg_ptr)
{
  ADSPResult result = ADSP_EOK;

  /* Get the parameters */
  uint32_t token               = cfg_ptr->token;
  uint32_t mode                = cfg_ptr->mode;
  uint32_t cmd_op_code         = 0;
  uint32_t param_id            = 0;
  uint32_t ap_header_size      = 0;
  uint32_t payload_size        = 0;
  uint32_t payload_version     = 0;
  uint32_t payload_struct_size = 0;

  uint32_t payload_data_size = 0;
  uint32_t rem_mem_map_hdl   = 0;
  uint32_t rem_phy_addr_lsw  = 0;
  uint32_t rem_phy_addr_msw  = 0;
  uint32_t rem_virt_offset   = 0;
  void     *rem_shm_mem_ptr  = NULL;

#ifdef CAPI_OLM_DEBUG
  MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "CAPIv2 OLM 0x%8lX: Get param Begin.",
                                        me_ptr->capi_v2_olm_identifier);
#endif

  switch(mode)
  {
    case GIVEN_INSTANCE:
    {
      cmd_op_code         = AP_CMD_GET_PARAM_CONFIG_V2;
      param_id            = AP_PARAM_ID_GET_CONTAINER_MID_IID_PARAM;
      ap_header_size      = sizeof(ap_container_get_mid_iid_param_info_v1_t);
      payload_version     = AP_PARAM_GET_MID_IID_PARAM_VERSION;
      payload_struct_size = sizeof(ap_container_get_mid_iid_param_info_v1_t);
      break;
    }
    case ZERO_INSTANCE:
    {
      cmd_op_code         = AP_CMD_GET_PARAM_CONFIG_V1;
      param_id            = AP_PARAM_ID_GET_CONTAINER_MID_PARAM;
      ap_header_size      = sizeof(ap_container_get_mid_param_info_v1_t);
      payload_version     = AP_PARAM_GET_MID_PARAM_VERSION;
      payload_struct_size = sizeof(ap_container_get_mid_param_info_v1_t);
      break;
    }
    default:
      MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Get Param Invalid mode %ul.",
    		                                    me_ptr->capi_v2_olm_identifier,  mode);
      return ADSP_EBADPARAM;
      break;
  }

  /* Extract the shared memory information from the payload*/
  if(0 != cfg_ptr->bufferMemNode.unMemMapHandle)
  {
    /* OUT band case*/
    uint32_t in_mem_map_hdl  = cfg_ptr->bufferMemNode.unMemMapHandle;
    uint32_t in_phy_addr_lsw = cfg_ptr->bufferMemNode.unPhysAddrLsw;
    uint32_t in_phy_addr_msw = cfg_ptr->bufferMemNode.unPhysAddrMsw;

    payload_data_size = cfg_ptr->bufferMemNode.unMemSize;

    /* CASE 1: Memory shared with APPS - ADSP - Remote Processor */
    result = olm_get_client_shm_mem_handle(me_ptr->remote_proc_id,
                                         in_mem_map_hdl,
                                         in_phy_addr_lsw,
                                         in_phy_addr_msw,
                                         &rem_mem_map_hdl,
                                         &rem_phy_addr_lsw,
                                         &rem_phy_addr_msw);


    if(ADSP_FAILED(result))
    {
      /* CASE 2: Memory not shared with Remote Processors */
      rem_shm_mem_ptr = elite_mem_mdf_malloc( payload_data_size,
                                              me_ptr->remote_proc_id,
                                              &rem_mem_map_hdl,
                                              &rem_virt_offset);
      if(NULL ==  rem_shm_mem_ptr)
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Couldn't allocate "
                                             "shared memory for Get param.",
				                                      me_ptr->capi_v2_olm_identifier);
        return ADSP_ENOMEMORY;
      }
      memset(rem_shm_mem_ptr, 0, payload_data_size);
      (void)qurt_elite_memorymap_cache_flush((uint32_t)rem_shm_mem_ptr, payload_data_size);
    }
  }

  /* Allocate APR set param packet*/
  elite_apr_packet_t *elite_pkt_ptr = NULL;

  payload_size = sizeof(ap_server_stat_cmn_header_t);
  payload_size = payload_size + sizeof(ap_container_get_param_config_info_v1_t);
  payload_size = payload_size + ap_header_size;

  /* Send the packet to the remote server */
  result = elite_apr_if_alloc_cmd(me_ptr->apr_handle,
                                  me_ptr->apr_addr,
                                  me_ptr->olm_cfg.dynamic_cfg->olm_iid,
                                  me_ptr->create_resp_info.container_apr_addr,
                                  DEFAULT_OLM_AP_SESSION_PORT,
                                  token,
                                  cmd_op_code,
                                  payload_size,
                                  &elite_pkt_ptr);
  if(ADSP_FAILED(result))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Could not allocate apr packet for get param",
    		                                  me_ptr->capi_v2_olm_identifier);
    elite_mem_mdf_mem_free(rem_shm_mem_ptr, rem_mem_map_hdl, payload_data_size);
    return result;
  }

  /* Get remote command payload pointer in the packet*/
  uint8_t *payload_ptr = (uint8_t*)elite_apr_if_get_payload_ptr(elite_pkt_ptr);
  if(NULL == payload_ptr)
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX:Get Param Packet payload is null. ",
                                           me_ptr->capi_v2_olm_identifier);

    elite_mem_mdf_mem_free(rem_shm_mem_ptr, rem_mem_map_hdl, payload_data_size);
    elite_apr_if_free(me_ptr->apr_handle, elite_pkt_ptr);
    return ADSP_EFAILED;
  }

  /* Update the packet header structure */
  ap_server_stat_cmn_header_t *header_ptr = (ap_server_stat_cmn_header_t*) payload_ptr;
  header_ptr->module_id         = me_ptr->remote_module_id;
  header_ptr->instance_id       = 1;
  header_ptr->param_id          = param_id;
  header_ptr->reserved          = 0;
  header_ptr->param_size        = sizeof(ap_container_get_param_config_info_v1_t) + ap_header_size;
  header_ptr->param_version     = AP_PARAM_GET_CONTAINER_PARAM_COMMON_VERSION;
  header_ptr->param_struct_size = sizeof(ap_container_get_param_config_info_v1_t);

  payload_ptr = payload_ptr + sizeof(ap_server_stat_cmn_header_t);

  /* Update the container set config info structure */
  ap_container_get_param_config_info_v1_t *get_cfg_info_ptr = (ap_container_get_param_config_info_v1_t*) payload_ptr ;

  get_cfg_info_ptr->shm_virtual_offset  = rem_virt_offset;
  get_cfg_info_ptr->mem_map_handle      = rem_mem_map_hdl;
  get_cfg_info_ptr->data_payload_size   = payload_data_size;
  get_cfg_info_ptr->payload_version     = payload_version;
  get_cfg_info_ptr->payload_struct_size = payload_struct_size;

  payload_ptr = payload_ptr + sizeof(ap_container_get_param_config_info_v1_t);

  if(GIVEN_INSTANCE == mode)
  {
    /* Update the container get config info structure */
    ap_container_get_mid_iid_param_info_v1_t *get_param_info_ptr = (ap_container_get_mid_iid_param_info_v1_t*) ( payload_ptr);
    get_param_info_ptr->module_id       = cfg_ptr->module_id;
    get_param_info_ptr->instance_id     = cfg_ptr->instance_id;
    get_param_info_ptr->reserved        =  0;
    get_param_info_ptr->param_id        = cfg_ptr->param_id;
    get_param_info_ptr->max_param_size  = cfg_ptr->max_data_size;
  }
  else
  {
    /* Update the container set config info structure */
    ap_container_get_mid_param_info_v1_t *get_param_info_ptr = (ap_container_get_mid_param_info_v1_t*) ( payload_ptr);
    get_param_info_ptr->module_id      = cfg_ptr->module_id;
    get_param_info_ptr->param_id       = cfg_ptr->param_id;
    get_param_info_ptr->max_param_size = cfg_ptr->max_data_size;
  }

#ifdef CAPI_OLM_DEBUG
  MSG_1(MSG_SSID_QDSP6, DBG_LOW_PRIO, "CAPIv2 OLM 0x%8lX: Get param End.",
		                                    me_ptr->capi_v2_olm_identifier);
#endif

  /* Cache the get param payload ptr, to be able to copy the get param response
   * from remote service.
   */
  olm_getparam_cmd_handle_t *cmd_hdl_ptr = (olm_getparam_cmd_handle_t *)qurt_elite_memory_malloc(sizeof(olm_getparam_cmd_handle_t),
                                                                                                 QURT_ELITE_HEAP_DEFAULT);
  if(NULL == cmd_hdl_ptr)
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Could not allocate "
                                          "memory to cache command info in the cmd handle",
    		                                  me_ptr->capi_v2_olm_identifier);
    elite_mem_mdf_mem_free(rem_shm_mem_ptr, rem_mem_map_hdl, payload_data_size);
    return ADSP_ENOMEMORY;
  }

  /* Copy the get param configuration payload to a new pointer */
  memscpy((void *)&cmd_hdl_ptr->cfg,
          sizeof(capi_v2_olm_getparam_t),
          cfg_ptr,
          sizeof(capi_v2_olm_getparam_t));

  /*
   * Store the virtual address of allocated shared memory region,
   * if non NULL it will be de allocated when response is received
   */
  cmd_hdl_ptr->shm_mem_ptr    = rem_shm_mem_ptr;
  cmd_hdl_ptr->mem_map_hdl    = rem_mem_map_hdl;
  cmd_hdl_ptr->shm_alloc_size = payload_data_size;

  /* Store the command handle pointer, to be able handle get param response*/
  result = store_cmd_payload(me_ptr, CAPI_V2_PARAM_ID_OLM_GETPARAM, token, (void *)cmd_hdl_ptr);
  if(ADSP_FAILED(result))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Could not cache command info in the "
    		                                 "get param cmd handle",
    		                                  me_ptr->capi_v2_olm_identifier);
    elite_mem_mdf_mem_free(rem_shm_mem_ptr, rem_mem_map_hdl, payload_data_size);
    qurt_elite_memory_free(cmd_hdl_ptr);
    return result;
  }

  /*
   * Send the packet to the remote server
   */
#ifdef OLM_LATENCY_MEASUREMENT
  MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX olm_get_param: sent cmd to remote service at time %lld", me_ptr->capi_v2_olm_identifier, qurt_elite_timer_get_time());
#endif

  result = elite_apr_if_cmd_fwd(me_ptr->apr_handle, elite_pkt_ptr);
  if(ADSP_FAILED(result))
  {
    MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Fail to send Get Param "
                                          "cmd to remote service. 0x%x",
                                          me_ptr->capi_v2_olm_identifier, result);

    elite_mem_mdf_mem_free(rem_shm_mem_ptr, rem_mem_map_hdl, payload_data_size);
    free_cmd_handle(me_ptr, CAPI_V2_PARAM_ID_OLM_GETPARAM, token); //free up the command handle
    return result;
  }

  return result;
}

/**
 * This function is used to send the Flush Command to the
 * Remote Container service,
 *
 * @param[in] me_ptr, pointer to the CAPI lib
 * @param[in] cfg_ptr, pointer to the command config
 *
 * @return ADSPResult, result code
 */
ADSPResult olm_send_flush_cmd(capi_v2_olm_t *me_ptr, capi_v2_olm_flush_t* cfg_ptr)
{
  ADSPResult result = ADSP_EOK;

  /*send the Flush command to AP contianer*/
  result = olm_send_simple_ap_container_cmd(me_ptr,
                                            AP_CMD_FLUSH,
                                            AP_PARAM_ID_FLUSH,
                                            AP_PARAM_FLUSH_VERSION,
                                            0,
                                            cfg_ptr->token,
                                            me_ptr->create_resp_info.container_apr_addr,
                                            DEFAULT_OLM_AP_SESSION_PORT);

  return result;

}

/**
 * This function is used to send the Close Command to the
 * Remote Container service,
 *
 * @param[in] me_ptr, pointer to the CAPI lib
 * @param[in] cfg_ptr, pointer to the command config
 *
 * @return ADSPResult, result code
 */
ADSPResult olm_send_close_cmd(capi_v2_olm_t *me_ptr, capi_v2_olm_close_t* cfg_ptr)
{
  ADSPResult result = ADSP_EOK;
  uint32_t pkt_size = sizeof(ap_server_stat_cmn_header_t) + sizeof(ap_destroy_container_v1_t);

  /* Allocate APR set param packet*/
  elite_apr_packet_t *elite_pkt_ptr;

  /* Send the packet to the remote server */
  result = elite_apr_if_alloc_cmd(me_ptr->apr_handle,
                                  me_ptr->apr_addr,
                                  me_ptr->olm_cfg.dynamic_cfg->olm_iid,
                                  me_ptr->remote_svc_apr_addr,
                                  DEFAULT_OLM_AP_SESSION_PORT,
                                  cfg_ptr->token,
                                  AP_CMD_CLOSE,
                                  pkt_size,
                                  &elite_pkt_ptr);
  if(ADSP_FAILED(result))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Could not allocate apr packet for Close",
                                          me_ptr->capi_v2_olm_identifier);
    return result;
  }

  /* Get remote command payload pointer in the packet*/
  uint8_t *payload_ptr = (uint8_t*)elite_apr_if_get_payload_ptr(elite_pkt_ptr);
  if(NULL == payload_ptr)
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX:Close command Packet payload is null. ",
          me_ptr->capi_v2_olm_identifier);
    elite_apr_if_free(me_ptr->apr_handle, elite_pkt_ptr);
    return ADSP_EFAILED;
  }

  /* Update the packet header strcutre */
  ap_server_stat_cmn_header_t *header_ptr = (ap_server_stat_cmn_header_t*) payload_ptr;
  header_ptr->module_id         = me_ptr->remote_module_id;
  header_ptr->instance_id       = 1;
  header_ptr->param_id          = AP_PARAM_ID_DESTROY_CONTAINER;
  header_ptr->reserved          = 0;
  header_ptr->param_version     = AP_PARAM_DESTROY_CONTAINER_VERSION;
  header_ptr->param_size        = sizeof(ap_destroy_container_v1_t);
  header_ptr->param_struct_size = sizeof(ap_destroy_container_v1_t);

  ap_destroy_container_v1_t *info = (ap_destroy_container_v1_t*)((uint8_t*)header_ptr + sizeof(ap_server_stat_cmn_header_t));
  info->container_id = me_ptr->remote_container_id;

  /*
   * Send the packet to the remote server
   */
#ifdef OLM_LATENCY_MEASUREMENT
  MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: olm_send_close_cmd: to remote service at time %lld", me_ptr->capi_v2_olm_identifier,qurt_elite_timer_get_time());
#endif

  result = elite_apr_if_cmd_fwd(me_ptr->apr_handle, elite_pkt_ptr);
  if(ADSP_FAILED(result))
  {
    MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Fail to close cmd to remote service"
                                          " with result 0x%x", me_ptr->capi_v2_olm_identifier, result);
  }

  return result;
}

/**
 * This function is used to send the Suspend Command to the
 * Remote Container service,
 *
 * @param[in] me_ptr, pointer to the CAPI lib
 * @param[in] cfg_ptr, pointer to the command config
 *
 * @return ADSPResult, result code
 */
ADSPResult olm_send_suspend_cmd(capi_v2_olm_t *me_ptr, capi_v2_olm_suspend_t* cfg_ptr)
{
  ADSPResult result = ADSP_EOK;

  /*send the Suspend command to AP contianer*/
  result = olm_send_simple_ap_container_cmd(me_ptr,
                                            AP_CMD_SUSPEND,
                                            AP_PARAM_ID_SUSPEND,
                                            AP_PARAM_SUSPEND_VERSION,
                                            0,
                                            cfg_ptr->token,
                                            me_ptr->create_resp_info.container_apr_addr,
                                            DEFAULT_OLM_AP_SESSION_PORT);

  return result;
}

/**
 * This function is used to send the Disable Event to the
 * Remote Container service,
 *
 * @param[in] me_ptr, pointer to the CAPI lib
 *
 * @return ADSPResult, result code
 */
ADSPResult olm_send_disable_event(capi_v2_olm_t *me_ptr)
{
  ADSPResult result = ADSP_EOK;

  uint32_t pkt_size = sizeof(ap_server_stat_cmn_header_t) + sizeof(ap_container_custom_event_v1_t);

  //RR: Check this
  uint32_t token = me_ptr->olm_local_token;
  me_ptr->olm_local_token +=1;

  /* Allocate APR set param packet*/
  elite_apr_packet_t *elite_pkt_ptr = NULL;

  /* Send the packet to the remote server */
  result = elite_apr_if_alloc_cmd(me_ptr->apr_handle,
                                  me_ptr->apr_addr,
                                  me_ptr->olm_cfg.dynamic_cfg->olm_iid,
                                  me_ptr->create_resp_info.container_apr_addr,
                                  DEFAULT_OLM_AP_SESSION_PORT,
                                  token,
                                  AP_CMD_EVENT,
                                  pkt_size,
                                  &elite_pkt_ptr);
  if(ADSP_FAILED(result))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Could not allocate apr packet ", me_ptr->capi_v2_olm_identifier);
    return ADSP_EBADPARAM;
  }

  /* Get remote command payload pointer in the packet*/
  uint8_t *payload_ptr = (uint8_t*)elite_apr_if_get_payload_ptr(elite_pkt_ptr);
  if(NULL == payload_ptr)
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX:Disable Event payload is null. ",
          me_ptr->capi_v2_olm_identifier);

    elite_apr_if_free(me_ptr->apr_handle, elite_pkt_ptr);
    return ADSP_EFAILED;
  }

  /* Update the packet header strcutre */
  ap_server_stat_cmn_header_t *header_ptr = (ap_server_stat_cmn_header_t*) payload_ptr;
  header_ptr->module_id         = me_ptr->remote_module_id;
  header_ptr->instance_id       = 1;
  header_ptr->param_id          = AP_PARAM_ID_CUSTOM_EVENT;
  header_ptr->reserved          = 0;
  header_ptr->param_version     = AP_PARAM_CUSTOM_EVENT_VERSION;
  header_ptr->param_size        = sizeof(ap_container_custom_event_v1_t);
  header_ptr->param_struct_size = sizeof(ap_container_custom_event_v1_t);

  ap_container_custom_event_v1_t *info = (ap_container_custom_event_v1_t*)((uint8_t*)header_ptr + sizeof(ap_server_stat_cmn_header_t));

  info->container.module_id   = me_ptr->remote_module_id;
  info->container.instance_id = 1;
  info->container.reserved    = 0;
  info->event_id              = AP_EVENT_DISABLE;
  info->event_status          = ADSP_EOK;
  info->event_version         = AP_PARAM_EVENT_DISABLE_VERSION;
  info->event_struct_size     = 0;

  /*
   * Send the packet to the remote server
   */
  result = elite_apr_if_cmd_fwd(me_ptr->apr_handle, elite_pkt_ptr);
  if(APR_EOK != result)
  {
    MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Fail to disable event to remote service. 0x%x", me_ptr->capi_v2_olm_identifier, result);

  }

  return result;

}

/**
 * This function is used to send the Set Prop command for
 * Interface Extension to the Remote Container service
 *
 * @param[in] me_ptr, pointer to the CAPI lib
 * @param[in] inf_extn_info_ptr, pointer to interface extension
 *
 * @return ADSPResult, result code
 */
ADSPResult olm_send_set_intf_extn_config(capi_v2_olm_t *me_ptr, capi_v2_olm_set_inf_extn_module_config_t *inf_extn_info_ptr)
{
  uint32_t payload_size = inf_extn_info_ptr->payload_size +  sizeof(ap_container_prop_info_v1_t) + sizeof(ap_container_prop_payload_v1_t);
  int8_t *inf_payload_ptr = (int8_t *) qurt_elite_memory_malloc(payload_size, QURT_ELITE_HEAP_DEFAULT);

  ADSPResult result = ADSP_EOK;

  if(NULL == inf_payload_ptr)
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Failed to allocate memory "
                                          "to copy the interface extension payload!",
                                          me_ptr->capi_v2_olm_identifier);
    return ADSP_ENOMEMORY;
  }

  int8_t * payload_ptr = inf_payload_ptr;

  ap_container_prop_info_v1_t *cont_prop_info = (ap_container_prop_info_v1_t*)payload_ptr;
  cont_prop_info->num_prop         = 1;
  cont_prop_info->prop_version     = AP_PARAM_CONTAINER_PROP_PAYLOAD_VERSION;
  cont_prop_info->prop_struct_size = sizeof(ap_container_prop_payload_v1_t);

  payload_ptr = payload_ptr + sizeof(ap_container_prop_info_v1_t);

  ap_container_prop_payload_v1_t *inf_prop_payload_ptr = (ap_container_prop_payload_v1_t*)payload_ptr;

  inf_prop_payload_ptr->prop_id           = inf_extn_info_ptr->inf_extn_id;
  inf_prop_payload_ptr->prop_payload_size = inf_extn_info_ptr->payload_size;
  payload_ptr = payload_ptr + sizeof(ap_container_prop_payload_v1_t);

  memscpy(payload_ptr, inf_extn_info_ptr->payload_size, inf_extn_info_ptr->payload_ptr, inf_extn_info_ptr->payload_size);

  result = olm_set_remote_config(me_ptr, inf_payload_ptr, payload_size);
  qurt_elite_memory_free(inf_payload_ptr);

  return result;

}

/**
 * This function is used to send the Register Event Command
 * to the Remote Container service
 *
 * @param[in] me_ptr,      pointer to the OLM structure
 * @param[in] token,       token for the command
 * @param[in] event_id,    event ID for the registration
 * @param[in] module_id,   module ID for the registration
 * @param[in] instance_id, instance ID of the module
 * @param[in] config_mask, config mask for the event
 *
 * @return ADSPResult, result code
 */
ADSPResult olm_send_register_event_cmd(capi_v2_olm_t *me_ptr,
                                       uint32_t token,
                                       uint32_t event_id,
                                       uint32_t module_id,
                                       uint32_t instance_id,
                                       uint32_t config_mask)
{
  ADSPResult result = ADSP_EOK;
  uint32_t payload_size = 0;

  payload_size =  sizeof(ap_server_stat_cmn_header_t);
  payload_size += sizeof(ap_container_register_event_v1_t);
  payload_size += sizeof(ap_container_register_event_info_v1_t);

  /* Allocate APR set param packet*/
  elite_apr_packet_t *elite_pkt_ptr = NULL;

  /* Send the packet to the remote server */

  result = elite_apr_if_alloc_cmd(me_ptr->apr_handle,
                                  me_ptr->apr_addr,
                                  me_ptr->olm_cfg.dynamic_cfg->olm_iid,
                                  me_ptr->create_resp_info.container_apr_addr,
                                  DEFAULT_OLM_AP_SESSION_PORT,
                                  token,
                                  AP_CMD_EVENT,
                                  payload_size,
                                  &elite_pkt_ptr);
  if(ADSP_FAILED(result))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Could not allocate apr packet ", me_ptr->capi_v2_olm_identifier);
    return ADSP_EBADPARAM;
  }

  /* Get remote command payload pointer in the packet*/
  uint8_t *payload_ptr = (uint8_t*)elite_apr_if_get_payload_ptr(elite_pkt_ptr);
  if(NULL == payload_ptr)
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX:Register Event payload is null. ",
          me_ptr->capi_v2_olm_identifier);

    elite_apr_if_free(me_ptr->apr_handle, elite_pkt_ptr);
    return ADSP_EFAILED;
  }

  /* Update the packet header structure */
  ap_server_stat_cmn_header_t *header_ptr = (ap_server_stat_cmn_header_t*) payload_ptr;
  header_ptr->module_id         = me_ptr->remote_module_id;
  header_ptr->instance_id       = 1;
  header_ptr->param_id          = AP_PARAM_ID_REGISTER_EVENT;
  header_ptr->reserved          = 0;
  header_ptr->param_size        = sizeof(ap_container_register_event_v1_t) + sizeof(ap_container_register_event_info_v1_t);
  header_ptr->param_version     = AP_PARAM_REGISTER_EVENT_VERSION;
  header_ptr->param_struct_size = sizeof(ap_container_register_event_v1_t);

  payload_ptr += sizeof(ap_server_stat_cmn_header_t);

  /* Update number of events*/
  ap_container_register_event_v1_t *reg_event_ptr = (ap_container_register_event_v1_t *) payload_ptr;
  reg_event_ptr->payload_version     = AP_PARAM_REGISTER_EVENT_PAYLOAD_VERSION;
  reg_event_ptr->payload_struct_size = sizeof(ap_container_register_event_info_v1_t);
  reg_event_ptr->num_events          = 1;

  payload_ptr += sizeof(ap_container_register_event_v1_t);

  /* Fill event info pointer*/
  ap_container_register_event_info_v1_t *event_info_ptr = (ap_container_register_event_info_v1_t *)payload_ptr;
  event_info_ptr->event_id    = event_id;
  event_info_ptr->module_id   = module_id;
  event_info_ptr->instance_id = instance_id;
  event_info_ptr->reserved    = 0;
  event_info_ptr->config_mask = config_mask;

  /*
   * Send the packet to the remote server
   */
  result = elite_apr_if_cmd_fwd(me_ptr->apr_handle, elite_pkt_ptr);
  if(ADSP_FAILED(result))
  {
    MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Failed to send cmd to remote service with result 0x%x",
                                           me_ptr->capi_v2_olm_identifier, result);
    return result;
  }

  return result;
}

/**
 * This function is used to send a simple AP command (only the header)
 * to the Remote Container
 *
 * @param[in] me_ptr,            pointer to the OLM structure
 * @param[in] cmd_id,            opcode for the command
 * @param[in] param_id,          param ID for the command
 * @param[in] param_version,     version of the param ID
 * @param[in] param_struct_size, unit size of the parameter structure
 * @param[in] token,             token of the command
 * @param[in] remote_apr_addr,   APR address of the remote service
 * @param[in] remote_port_no,    APR port of the remote service
 *
 * @return ADSPResult, result code
 */
ADSPResult olm_send_simple_ap_container_cmd(capi_v2_olm_t *me_ptr,
                                            uint32_t cmd_id,
                                            uint32_t param_id,
                                            uint16_t param_version,
                                            uint16_t param_struct_size,
                                            uint32_t token,
                                            uint16_t remote_apr_addr,
                                            uint16_t remote_port_no)
{
  ADSPResult result = ADSP_EOK;
  uint32_t payload_size = 0;

  payload_size = sizeof(ap_server_stat_cmn_header_t);

  /* Allocate APR set param packet*/
  elite_apr_packet_t *elite_pkt_ptr = NULL;

  /* Send the packet to the remote server */

  result = elite_apr_if_alloc_cmd(me_ptr->apr_handle,
                                  me_ptr->apr_addr,
                                  me_ptr->olm_cfg.dynamic_cfg->olm_iid,
                                  remote_apr_addr,
                                  remote_port_no,
                                  token,
                                  cmd_id,
                                  payload_size,
                                  &elite_pkt_ptr);
  if(ADSP_FAILED(result))
  {
    MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Could not allocate apr packet for opcode 0x%x with result 0x%x",
                                          me_ptr->capi_v2_olm_identifier, cmd_id, result );
    return result;
  }

  /* Get remote command payload pointer in the packet*/
  uint8_t *payload_ptr = (uint8_t*)elite_apr_if_get_payload_ptr(elite_pkt_ptr);

  if(NULL == payload_ptr)
  {
    MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: NULL payload in apr packet for opcode 0x%x",
                                              me_ptr->capi_v2_olm_identifier, cmd_id);
    elite_apr_if_free(me_ptr->apr_handle, elite_pkt_ptr);
    return ADSP_EFAILED;
  }

  /* Update the packet header structure */
  ap_server_stat_cmn_header_t *header_ptr = (ap_server_stat_cmn_header_t*) payload_ptr;
  header_ptr->module_id         = me_ptr->remote_module_id;
  header_ptr->instance_id       = 1;
  header_ptr->param_id          = param_id;
  header_ptr->reserved          = 0;
  header_ptr->param_size        = 0;
  header_ptr->param_struct_size = param_struct_size;
  header_ptr->param_version     = param_version;

#ifdef OLM_LATENCY_MEASUREMENT
  MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: olm_send_simple_ap_container_cmd: cmd_id = 0x%x sent at time %lld",
        me_ptr->capi_v2_olm_identifier, cmd_id, qurt_elite_timer_get_time());
#endif

  /* Send the packet to the Remote Service */
  result = elite_apr_if_cmd_fwd(me_ptr->apr_handle, elite_pkt_ptr);
  if(ADSP_FAILED(result))
  {
    MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Failed to send cmd 0x%x to Remote Service with result 0x%x",
                                          me_ptr->capi_v2_olm_identifier, cmd_id, result);
    return result;
  }

#ifdef CAPI_V2_OLM_DEBUG
  MSG_2(MSG_SSID_QDSP6, DBG_LOW_PRIO, "CAPIv2 OLM 0x%8lX: Sent cmd 0x%x to Remote Service successfully",
                                            me_ptr->capi_v2_olm_identifier, cmd_id);
#endif

  return result;
}

/**
 * This function is used to send a simple AP command (only the header)
 * to the Remote Container
 *
 * @param[in] me_ptr,       pointer to the OLM structure
 * @param[in] payload_ptr,  pointer to the payload
 * @param[in] payload_size, size of the payload
 *
 * @return ADSPResult, result code
 */
ADSPResult olm_set_remote_config(capi_v2_olm_t *me_ptr,void *payload_ptr, uint32_t payload_size)
{
  ADSPResult result = ADSP_EOK;

  uint32_t src_calibdata_size = payload_size;
  uint8_t  *src_calib_ptr     = (uint8_t *)payload_ptr;
  uint32_t token              = me_ptr->olm_local_token;
  uint32_t cmd_op_code        = 0;
  uint32_t param_id           = 0;

  uint32_t pkt_payload_sz       = 0;
  int8_t   *pkt_payload_ptr     = NULL;
  uint32_t rem_mem_map_hdl      = 0;
  uint32_t rem_virt_addr_offset = 0;

  elite_apr_packet_t        *elite_pkt_ptr = NULL;
  olm_setparam_cmd_handle_t *cmd_hdl       = NULL;

  if(!IS_ALIGN_4_BYTE((uint32_t)src_calib_ptr))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Set Prop payload param"
                                          " pointer is not aligned to 4 bytes. Aborting.",
                                          me_ptr->capi_v2_olm_identifier);
    result =  ADSP_EFAILED;
    return result;
  }

  cmd_op_code = AP_CMD_SET_PROP_CONFIG;
  param_id    = AP_PARAM_ID_SET_CONTAINER_PROP;

  /* Update the packet header structure */
  ap_server_stat_cmn_header_t *header_ptr = NULL;
  ap_container_set_param_config_info_v1_t *set_cfg_info_ptr = NULL;

  /* Allocate shared memory for the given client processor ID */
  void* temp_ptr = elite_mem_mdf_malloc( src_calibdata_size,
                                         me_ptr->remote_proc_id,
                                         &rem_mem_map_hdl,
                                         &rem_virt_addr_offset );

  if(NULL ==  temp_ptr)
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Couldn't allocate shared"
                                         " memory for Set Prop ",
                                         me_ptr->capi_v2_olm_identifier);
    result = ADSP_EFAILED;
    goto _bailout;
  }

  /* Store the shared memory region, and free it
       when the reponse is received */
  cmd_hdl = (olm_setparam_cmd_handle_t *)qurt_elite_memory_malloc(sizeof(olm_setparam_cmd_handle_t), QURT_ELITE_HEAP_DEFAULT);
  if(NULL == cmd_hdl)
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Failed to allocate memory"
                                          " for Set Prop command handle", me_ptr->capi_v2_olm_identifier);
    result = ADSP_ENOMEMORY;
    goto _bailout;
  }

  cmd_hdl->shm_mem_ptr    = temp_ptr;
  cmd_hdl->mem_map_hdl    = rem_mem_map_hdl;
  cmd_hdl->shm_alloc_size = src_calibdata_size;

  result = store_cmd_payload(me_ptr,
                            CAPI_V2_PARAM_ID_SET_OLM_INF_EXTN_MODULE_CONFIG,
                            token,
                            cmd_hdl);

  if(ADSP_FAILED(result))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Could not store command handle for Set Prop",
          me_ptr->capi_v2_olm_identifier);
    goto _bailout;
  }

  memscpy(temp_ptr, src_calibdata_size, src_calib_ptr, payload_size);
  if(ADSP_FAILED(result = qurt_elite_memorymap_cache_flush((uint32_t)temp_ptr, src_calibdata_size)))
  {
    MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Failed to flush cache for "
                                         "Set Prop with result", me_ptr->capi_v2_olm_identifier,
                                         result);
    goto _bailout;
  }

  pkt_payload_sz = sizeof(ap_server_stat_cmn_header_t);
  pkt_payload_sz += sizeof(ap_container_set_param_config_info_v1_t);

  result = elite_apr_if_alloc_cmd(me_ptr->apr_handle,
                                  me_ptr->apr_addr,
                                  me_ptr->olm_cfg.dynamic_cfg->olm_iid,
                                  me_ptr->create_resp_info.container_apr_addr,
                                  DEFAULT_OLM_AP_SESSION_PORT,
                                  token,
                                  cmd_op_code,
                                  pkt_payload_sz,
                                  &elite_pkt_ptr);
  if(ADSP_FAILED(result))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Could not allocate apr packet for Set Prop",
                                          me_ptr->capi_v2_olm_identifier);
    result = ADSP_EBADPARAM;
    goto _bailout;
  }

  pkt_payload_ptr = (int8_t*)elite_apr_if_get_payload_ptr(elite_pkt_ptr);
  if(NULL == pkt_payload_ptr)
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Set Prop Command had NULL payload in apr packet",
                                              me_ptr->capi_v2_olm_identifier);
    elite_apr_if_free(me_ptr->apr_handle, elite_pkt_ptr);
    return ADSP_EFAILED;
  }

  /* Update the packet header structure */
  header_ptr = (ap_server_stat_cmn_header_t*) pkt_payload_ptr;
  header_ptr->module_id         = me_ptr->remote_module_id;
  header_ptr->instance_id       = 1;
  header_ptr->param_id          = param_id;
  header_ptr->reserved          = 0;
  header_ptr->param_size        = sizeof(ap_container_set_param_config_info_v1_t);
  header_ptr->param_version     = AP_PARAM_SET_CONTAINER_PARAM_COMMON_VERSION;
  header_ptr->param_struct_size = sizeof(ap_container_set_param_config_info_v1_t);

  pkt_payload_ptr = pkt_payload_ptr + sizeof(ap_server_stat_cmn_header_t);

  /* Update the container set configuration info structure */
  set_cfg_info_ptr = (ap_container_set_param_config_info_v1_t*) pkt_payload_ptr ;

  set_cfg_info_ptr->shm_virtual_offset       = rem_virt_addr_offset;
  set_cfg_info_ptr->mem_map_handle           = rem_mem_map_hdl;
  set_cfg_info_ptr->data_payload_size        = src_calibdata_size;
  set_cfg_info_ptr->payload_version          = AP_PARAM_CONTAINER_PROP_VERSION;
  set_cfg_info_ptr->payload_struct_size      = sizeof(ap_container_prop_info_v1_t);

  /* Send the packet to the remote server */
  result = elite_apr_if_cmd_fwd(me_ptr->apr_handle, elite_pkt_ptr);
  if(ADSP_FAILED(result))
  {
    MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Fail to send cmd to "
                                          "remote service with result 0x%x",
                                          me_ptr->capi_v2_olm_identifier, result);
    goto _bailout;
  }
  me_ptr->olm_local_token+=1;

#ifdef CAPI_V2_OLM_DEBUG
  MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "CAPIv2 OLM 0x%8lX: Set Prop, "
      "sent payload", me_ptr->capi_v2_olm_identifier;
#endif

  return result;

  /* Bail out routine */
  _bailout:
  if(result!=ADSP_EOK)
  {
    if(temp_ptr)
    {
      elite_mem_mdf_mem_free(temp_ptr, rem_mem_map_hdl, src_calibdata_size);
    }
    if(cmd_hdl)
    {
      free_cmd_handle(me_ptr, CAPI_V2_PARAM_ID_SET_OLM_INF_EXTN_MODULE_CONFIG, token); //Free up handle if stored
      cmd_hdl = NULL;
    }
  }

  return result;
}

/**
 * This function is used to send the media format to the Remote Container
 *
 * @param[in] me_ptr,     pointer to the OLM structure
 * @param[in] pFmt,       pointer to the CAPI format header
 * @param[in] pStd,       pointer to the Media Format structure
 * @param[in] port_index, port index of the OLM input
 *
 * @return ADSPResult, result code
 */
ADSPResult olm_send_media_fmt(capi_v2_olm_t *me_ptr, capi_v2_set_get_media_format_t *pFmt, capi_v2_standard_data_format_v2_t *pStd, uint32_t port_index)
{
  ADSPResult result = ADSP_EOK;

  if( NULL == pFmt || NULL == pStd )
  {
    MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "CAPIv2 OLM 0x%8lX: Invalid media format recieved on port_index = 0x%x ",me_ptr->capi_v2_olm_identifier, port_index);
    return ADSP_EFAILED;
  }

  if(port_index >=  me_ptr->num_active_input_ports)
  {
    MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "CAPIv2 OLM 0x%8lX: Invalid port index 0x%x ",me_ptr->capi_v2_olm_identifier, port_index);
    return ADSP_EFAILED;
  }

  uint32_t payload_size = 0;
  uint32_t num_ports =1;

  payload_size += sizeof(ap_server_stat_cmn_header_t);

  if( CAPI_V2_RAW_COMPRESSED == pFmt->format_header.data_format )
  {
    payload_size += num_ports*sizeof(ap_container_compr_fmt_blk_v1_t);
  }
  else
  {
    payload_size += num_ports*sizeof(ap_container_mch_pcm_fmt_blk_v1_t);
  }


  /* Allocate APR set param packet*/
  elite_apr_packet_t *elite_pkt_ptr = NULL;

  /* Send the packet to the remote server */
  result = elite_apr_if_alloc_cmd(me_ptr->apr_handle,
                                  me_ptr->apr_addr,
                                  me_ptr->olm_cfg.dynamic_cfg->olm_iid,
                                  me_ptr->create_resp_info.container_apr_addr,
                                  DEFAULT_OLM_AP_SESSION_PORT,
                                  me_ptr->olm_cfg.olm_open_cfg.token,
                                  AP_CMD_DATA_MEDIA_FMT_UPDATE,
                                  payload_size,
                                  &elite_pkt_ptr);
  if(ADSP_FAILED(result))
  {
    MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Could not allocate apr packet with result 0x%x", me_ptr->capi_v2_olm_identifier, result);
    return result;
  }

  /* Get remote command payload pointer in the packet*/
  uint8_t *payload = (uint8_t*)elite_apr_if_get_payload_ptr(elite_pkt_ptr);
  if(NULL == payload)
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Input Media Format had NULL payload in apr packet",
                                              me_ptr->capi_v2_olm_identifier);
    elite_apr_if_free(me_ptr->apr_handle, elite_pkt_ptr);
    return ADSP_EFAILED;
  }

  /* Initalize the media format header  */
  int8_t* buffer = (int8_t*)payload;

  if( CAPI_V2_RAW_COMPRESSED == pFmt->format_header.data_format )
  {
    ap_server_stat_cmn_header_t *header_ptr = reinterpret_cast<ap_server_stat_cmn_header_t*>(buffer);
    header_ptr->module_id         = me_ptr->remote_module_id;
    header_ptr->instance_id       = 1;
    header_ptr->reserved          = 0;
    header_ptr->param_id          = AP_PARAM_ID_COMPRESSED_MEDIA_FORMAT;
    header_ptr->param_version     = AP_PARAM_COMPRESSED_MEDIA_FORMAT_VERSION;
    header_ptr->param_struct_size = sizeof(ap_container_compr_fmt_blk_v1_t);
    header_ptr->param_size        = (num_ports)* sizeof(ap_container_compr_fmt_blk_v1_t);

    buffer += sizeof(ap_server_stat_cmn_header_t);

    ap_container_compr_fmt_blk_v1_t *cur_media_fmt_blk_ptr = (ap_container_compr_fmt_blk_v1_t *)buffer;
    for(int i =0; i < num_ports ; i++)
    {
      /* Copy the media format from input pointer */
      cur_media_fmt_blk_ptr->port_index      = port_index;
      cur_media_fmt_blk_ptr->reserved        = 0;
      cur_media_fmt_blk_ptr->num_channels    = pStd->num_channels;
      cur_media_fmt_blk_ptr->sample_rate     = pStd->sampling_rate;
      cur_media_fmt_blk_ptr->bits_per_sample = pStd->bits_per_sample;
      cur_media_fmt_blk_ptr->media_format    = pStd->bitstream_format;

#ifdef CAPI_V2_OLM_DEBUG
      MSG_6(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "CAPIv2 OLM 0x%8lX: Send INPUT media format. port_index= 0x%x,"
          " num_channels= 0x%lu, sample_rate = %lu, bits_per_sample = %lu, media_format = 0x%x",
            me_ptr->capi_v2_olm_identifier, port_index, pStd->num_channels, pStd->sampling_rate, pStd->bits_per_sample, pStd->bitstream_format);
#endif

      cur_media_fmt_blk_ptr++;
    }

  }
  else
  {
    ap_server_stat_cmn_header_t *header_ptr = reinterpret_cast<ap_server_stat_cmn_header_t*>(buffer);
    header_ptr->module_id         = me_ptr->remote_module_id;
    header_ptr->instance_id       = 1;
    header_ptr->reserved          = 0;
    header_ptr->param_id          = AP_PARAM_ID_MCH_PCM_MEDIA_FORMAT;
    header_ptr->param_version     = AP_PARAM_MCH_PCM_MEDIA_FORMAT_VERSION;
    header_ptr->param_struct_size = sizeof(ap_container_mch_pcm_fmt_blk_v1_t);
    header_ptr->param_size        = (num_ports)* sizeof(ap_container_mch_pcm_fmt_blk_v1_t);

    buffer += sizeof(ap_server_stat_cmn_header_t);

    ap_container_mch_pcm_fmt_blk_v1_t *cur_media_fmt_blk_ptr = (ap_container_mch_pcm_fmt_blk_v1_t *)buffer;
    for(int i =0; i < num_ports ; i++)
    {
      /* Copy the media format from input pointer */
      cur_media_fmt_blk_ptr->port_index      = port_index;
      cur_media_fmt_blk_ptr->num_channels    = pStd->num_channels;
      cur_media_fmt_blk_ptr->sample_rate     = pStd->sampling_rate;
      cur_media_fmt_blk_ptr->bits_per_sample = pStd->bits_per_sample;
      cur_media_fmt_blk_ptr->is_signed       = pStd->data_is_signed;
      cur_media_fmt_blk_ptr->is_interleaved  = (CAPI_V2_INTERLEAVED == pStd->data_interleaving) ? 1: 0;
      cur_media_fmt_blk_ptr->media_format    = pStd->bitstream_format;
      cur_media_fmt_blk_ptr->q_format        = pStd->q_factor;

      uint16_t *pchannel_type = (uint16_t*)(pStd +1);

      for(int j = 0; j<pStd->num_channels; j++)
      {
        cur_media_fmt_blk_ptr->channel_mapping[j] = pchannel_type[j];
      }

#ifdef CAPI_V2_OLM_DEBUG
      MSG_6(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "CAPIv2 OLM 0x%8lX: Send INPUT media format. port_index= 0x%x, "
          "num_channels= 0x%lu, sample_rate = %lu, bits_per_sample = %lu, media_format = 0x%x",
            me_ptr->capi_v2_olm_identifier, port_index, pStd->num_channels, pStd->sampling_rate, pStd->bits_per_sample, pStd->bitstream_format);
#endif
      cur_media_fmt_blk_ptr++;

    }
  }

  /* Send the media format packet to the remote server */
  result = elite_apr_if_cmd_fwd(me_ptr->apr_handle, elite_pkt_ptr);
  if(ADSP_FAILED(result))
  {
    MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "CAPIv2 OLM 0x%8lX: Fail to send media fmt to remote service. 0x%x", me_ptr->capi_v2_olm_identifier, result);
    return result;
  }

#ifdef CAPI_V2_OLM_DEBUG
  MSG_3(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "CAPIv2 OLM 0x%8lX: sent mf msg succesfully. remote_server_addr = %lu olm_apr_addr: %lu ",
        me_ptr->capi_v2_olm_identifier, me_ptr->remote_svc_apr_addr, me_ptr->apr_addr );
#endif

  return result;
}
