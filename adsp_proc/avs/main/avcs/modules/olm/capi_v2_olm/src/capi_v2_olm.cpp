/**
@file capi_v2_olm.cpp

@brief This contains wrapper functions for CAPI V2 Off-Loaded Module
       implementation

 */

/*========================================================================
$Header: //components/rel/avs.adsp/2.8/avcs/modules/olm/capi_v2_olm/src/capi_v2_olm.cpp#18 $

Edit History

when          who     what, where, why
--------      ---     -------------------------------------------------------
18/9/2017      MK       Created
11/13/2107   bvodapal	Moved set/get properties core code to utils file

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

/*----------------------------------------------------------------------------
 * Defines
 * -------------------------------------------------------------------------*/

/*------------------------------------------------------------------------
 * Static declarations
 * -----------------------------------------------------------------------*/
static capi_v2_err_t capi_v2_olm_process(capi_v2_t* _pif, capi_v2_stream_data_t* input[], capi_v2_stream_data_t* output[]);
static capi_v2_err_t capi_v2_olm_end(capi_v2_t* _pif);
static capi_v2_err_t capi_v2_olm_set_param(capi_v2_t* _pif, uint32_t param_id,
                                           const capi_v2_port_info_t *port_info_ptr,
                                           capi_v2_buf_t *params_ptr);
static capi_v2_err_t capi_v2_olm_get_param(capi_v2_t* _pif,
                                           uint32_t param_id,
                                           const capi_v2_port_info_t *port_info_ptr,
                                           capi_v2_buf_t *params_ptr);
static capi_v2_err_t capi_v2_olm_set_properties(capi_v2_t* _pif, capi_v2_proplist_t *props_ptr);
static capi_v2_err_t capi_v2_olm_get_properties(capi_v2_t* _pif, capi_v2_proplist_t *props_ptr);


static capi_v2_vtbl_t vtbl =
{
    capi_v2_olm_process,
    capi_v2_olm_end,
    capi_v2_olm_set_param,
    capi_v2_olm_get_param,
    capi_v2_olm_set_properties,
    capi_v2_olm_get_properties,
};


/*----------------------------------------------------------------------------
 * Function Definitions
 * -------------------------------------------------------------------------*/

/**
 * This function is used to query the static properties to create the CAPI.
 *
 * @param[in] init_set_properties, pointer to the list of initialization properties
 * @param[in, out] static_properties, pointer to the get static property list
 * @return capi_v2_err_t, result code
 */
capi_v2_err_t capi_v2_olm_get_static_properties(capi_v2_proplist_t *init_set_properties,
                                                capi_v2_proplist_t *static_properties)
{

  capi_v2_err_t capi_v2_result = CAPI_V2_EOK;

  if (NULL != static_properties)
  {
    capi_v2_result = capi_v2_olm_process_get_properties((capi_v2_olm_t*)NULL, static_properties);
    if (CAPI_V2_FAILED(capi_v2_result))
    {
      MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"CAPI_V2 OLM: get static properties failed!");
      return capi_v2_result;
    }
  }
  else
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPI_V2 OLM: Get static properties received "
          "bad pointer, 0x%lx",(uint32_t)static_properties);
  }
  return CAPI_V2_EOK;
}

/**
 * This function is used init the CAPI lib.
 *
 * @param[in] _pif, pointer to the OLM CAPIv2 library instance.
 * @param[in] init_set_properties, pointer to the initialization property list.
 *
 * @return capi_v2_err_t, result code
 */
capi_v2_err_t capi_v2_olm_init(capi_v2_t* _pif,
                               capi_v2_proplist_t      *init_set_properties)
{
  capi_v2_err_t  capi_v2_result = CAPI_V2_EOK;
  if (NULL == _pif || NULL == init_set_properties )
  {
    MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM: Init received bad pointer"
          ", 0x%lx, 0x%lx", (uint32_t)_pif, (uint32_t)init_set_properties);
    return CAPI_V2_SET_ERROR(capi_v2_result, CAPI_V2_EBADPARAM);
  }

  capi_v2_olm_t *pMe = (capi_v2_olm_t *)_pif;

  /* Memset the structure first */
  memset(pMe, 0, sizeof(capi_v2_olm_t));

  /* Set the vtable to allow the processing */
  pMe->vtbl_ptr = &vtbl;

  /* Initialize number of input and output ports */
  pMe->num_active_input_ports  = 1;
  pMe->num_active_output_ports = 1;

  if (NULL != init_set_properties)
  {
    capi_v2_result = capi_v2_olm_process_set_properties(pMe, init_set_properties);
    capi_v2_result ^= (capi_v2_result & CAPI_V2_EUNSUPPORTED);
  }


#ifdef OLM_SIM_FILE_DUMP
  pMe->in_file = fopen("olm_in.raw","wb");
  if(!pMe->in_file)
  {
    MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"OLM SIM File Open for input failed");
  }

  pMe->out_file = fopen("olm_out.raw","wb");
  if(!pMe->out_file)
  {
    MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"OLM SIM File Open for output failed");
  }

#endif

  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "CAPIv2 OLM: Initialization completed !!");
  return capi_v2_result;
}

/**
 * This function is used to set the OLM configuration.
 * OLM configuration PID maps to the commands from
 * the Client framework..
 *
 * @param[in] _pif, pointer to the CAPI lib
 * @param[in] param_id, param id to be set.
 * @param[in] port_info_ptr, pointer to port info (optional)
 * @param[in] params_ptr, pointer to the param payload.
 *
 * @return capi_v2_err_t, result code
 */
static capi_v2_err_t capi_v2_olm_set_param(capi_v2_t* _pif,
                                           uint32_t param_id,
                                           const capi_v2_port_info_t *port_info_ptr,
                                           capi_v2_buf_t *params_ptr)
{
  capi_v2_olm_t *pMe     = (capi_v2_olm_t*)_pif;
  capi_v2_err_t result   = CAPI_V2_EOK;
  ADSPResult adsp_result = ADSP_EOK;

  uint32_t cfg_size = 0;

  if(NULL == _pif || NULL == params_ptr)
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM : Set Param received bad pointer for param_id  0x%lx", param_id);
    return CAPI_V2_EFAILED;
  }

#ifdef OLM_LATENCY_MEASUREMENT
  MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Set Param received for param_id  0x%lx at time %lld", pMe->capi_v2_olm_identifier, param_id, qurt_elite_timer_get_time());
#endif

  /*
   * Return response if container response is not received yet, and
   * if a Set Param is received for commands other than open or response pkt.
   */
  if( (0 == pMe->create_resp_info.container_apr_addr) &&
      (CAPI_V2_PARAM_ID_OLM_OPEN != param_id && CAPI_V2_PARAM_ID_OLM_RESP_PKT != param_id) )
  {
    MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Set param received before remote container creation"
                                          "Invalid sequence for param ID 0x%lx", pMe->capi_v2_olm_identifier, param_id);
    return CAPI_V2_EFAILED;
  }

  switch(param_id)
  {
    case CAPI_V2_PARAM_ID_OLM_OPEN:
    {
      if(params_ptr->actual_data_len < sizeof(capi_v2_olm_open_t))
      {
        cfg_size = sizeof(capi_v2_olm_open_t);
        MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM : Set Open Config Failed due to bad param size,"
                                              " param_id = 0x%lx, required size = %lu, given size = %lu",
                                              param_id,cfg_size, params_ptr->actual_data_len);
        return CAPI_V2_ENEEDMORE;
      }
      else
      {
        capi_v2_olm_open_t *data_ptr = (capi_v2_olm_open_t *) params_ptr->data_ptr;
        if(NULL == data_ptr)
        {
          MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM : Open command payload is NULL.",
                data_ptr);
          return CAPI_V2_EBADPARAM;
        }

        if(params_ptr->actual_data_len < (sizeof(capi_v2_olm_open_t) + data_ptr->payload_size))
        {
          cfg_size = sizeof(capi_v2_olm_open_t) + data_ptr->payload_size;
          MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM : Set Open Config Failed due to bad param size,"
                                                " param_id = 0x%lx, required size = %lu, given size = %lu",
                                                param_id,cfg_size, params_ptr->max_data_len);
          return CAPI_V2_ENEEDMORE;
        }

        if(CAPI_V2_FAILED(result = capi_v2_olm_process_open(pMe, data_ptr)))
        {
          return result;
        }
      }
      break;
    }

    case CAPI_V2_PARAM_ID_OLM_RUN:
    {
      cfg_size = sizeof(capi_v2_olm_run_t);
      if(cfg_size > params_ptr->max_data_len)
      {
        MSG_4(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Set RUN Config Failed due to bad param size,"
                                              " param_id = 0x%lx, required size = %lu, given size = %lu",
                                                pMe->capi_v2_olm_identifier, param_id, cfg_size, params_ptr->actual_data_len);
        return CAPI_V2_EBADPARAM;
      }

      capi_v2_olm_run_t *cfg_ptr = (capi_v2_olm_run_t*) params_ptr->data_ptr;

      adsp_result = olm_send_run_cmd(pMe,cfg_ptr);
      if(ADSP_FAILED(adsp_result))
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Failed to send RUN command",pMe->capi_v2_olm_identifier);
      }
      result = adsp_result_to_capi_v2_err(adsp_result);
      break;
    }

    case CAPI_V2_PARAM_ID_OLM_SETPARAM:
    {
      cfg_size = sizeof(capi_v2_olm_setparam_t);
      if(cfg_size > params_ptr->max_data_len)
      {
        MSG_4(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Set-param for module calibration "
                                              "failed due to bad param size, param_id = 0x%lx,"
                                              "required size = %lu, given size = %lu",
                                               pMe->capi_v2_olm_identifier, param_id, cfg_size, params_ptr->actual_data_len);
        return CAPI_V2_EBADPARAM;
      }

      capi_v2_olm_setparam_t *cfg_ptr = (capi_v2_olm_setparam_t*) params_ptr->data_ptr;

      /* Parse the payload to extract only those calibration payloads that are relevant to this OLM */
      adsp_result = olm_set_param(pMe,cfg_ptr);

      if(ADSP_FAILED(adsp_result))
      {
        MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Failed in Sending module calibration(set-param)"
                                              "param_id = %lu",pMe->capi_v2_olm_identifier, param_id );
      }
      result = adsp_result_to_capi_v2_err(adsp_result);
      break;
    }
    case CAPI_V2_PARAM_ID_OLM_GETPARAM:
    {
      cfg_size = sizeof(capi_v2_olm_getparam_t);
      if(cfg_size > params_ptr->max_data_len)
      {
        MSG_4(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Received Invalid payload for param_id = 0x%lx,"
                                            "required size = %lu, given size = %lu",
                                            pMe->capi_v2_olm_identifier, param_id, cfg_size,
                                             params_ptr->max_data_len);

        return CAPI_V2_EBADPARAM;
      }

      capi_v2_olm_getparam_t *cfg_ptr = (capi_v2_olm_getparam_t*) params_ptr->data_ptr;

      adsp_result = olm_get_param(pMe,cfg_ptr);
      if(ADSP_FAILED(adsp_result))
      {
        MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Failed for param_id = 0x%lx",
              pMe->capi_v2_olm_identifier, param_id);
      }
      result = adsp_result_to_capi_v2_err(adsp_result);
      break;
    }

    case CAPI_V2_PARAM_ID_OLM_FLUSH:
    {
      cfg_size = sizeof(capi_v2_olm_flush_t);
      if(cfg_size > params_ptr->max_data_len)
      {
        MSG_4(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Received Invalid payload for"
                                            " param_id = 0x%lx,required size = %lu, given size = %lu",
                                              pMe->capi_v2_olm_identifier, param_id,cfg_size, params_ptr->max_data_len);

        return CAPI_V2_EBADPARAM;
      }

      capi_v2_olm_flush_t *cfg_ptr = (capi_v2_olm_flush_t*) params_ptr->data_ptr;

      adsp_result = olm_send_flush_cmd(pMe,cfg_ptr);
      if(ADSP_FAILED(adsp_result))
      {
        MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Failed for param_id = 0x%lx",
                                               pMe->capi_v2_olm_identifier, param_id );
      }
      result = adsp_result_to_capi_v2_err(adsp_result);
      break;
    }

    case CAPI_V2_PARAM_ID_OLM_CLOSE:
    {
      cfg_size = sizeof(capi_v2_olm_close_t);
      if(cfg_size > params_ptr->max_data_len)
      {
        MSG_4(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Received Invalid payload for"
                                            " param_id = 0x%lx,required size = %lu, given size = %lu",
                                            pMe->capi_v2_olm_identifier, param_id,cfg_size, params_ptr->max_data_len);

        return CAPI_V2_EBADPARAM;
      }

      capi_v2_olm_close_t *cfg_ptr = (capi_v2_olm_close_t*) params_ptr->data_ptr;

      adsp_result = olm_send_close_cmd(pMe,cfg_ptr);
      if(ADSP_FAILED(adsp_result))
      {
        MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Failed for param_id = 0x%lx",
                                               pMe->capi_v2_olm_identifier, param_id );
      }
      result = adsp_result_to_capi_v2_err(adsp_result);
      break;
    }

    case CAPI_V2_PARAM_ID_OLM_RESP_PKT:
    {
      cfg_size = sizeof(capi_v2_olm_resp_pkt_t);
      if(cfg_size > params_ptr->max_data_len)
      {
        MSG_4(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Failed with bad param size "
                                              " for param_id = 0x%lx,"
                                              " required size = %lu, given size = %lu",
                                              pMe->capi_v2_olm_identifier, param_id,cfg_size,
                                              params_ptr->max_data_len);

        return CAPI_V2_EBADPARAM;
      }

#ifdef CAPI_V2_OLM_DEBUG
      MSG_1(MSG_SSID_QDSP6, DBG_LOW_PRIO, "CAPIv2 OLM 0x%8lX: Received CAPI_V2_PARAM_ID_OLM_RESP_PKT",
                                            pMe->capi_v2_olm_identifier);
#endif

#ifdef OLM_LATENCY_MEASUREMENT
      MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Received CAPI_V2_PARAM_ID_OLM_RESP_PKT command at time %lld", pMe->capi_v2_olm_identifier, qurt_elite_timer_get_time());
#endif

      capi_v2_olm_resp_pkt_t *cfg_ptr = (capi_v2_olm_resp_pkt_t*) params_ptr->data_ptr;

      /* Handle the response packet*/
      //RR: This needs to return a result?
      olm_response_pkt_handler(pMe,cfg_ptr->pkt_ptr);

      break;
    }

    case CAPI_V2_PARAM_ID_SET_OLM_INF_EXTN_MODULE_CONFIG:
    {
      cfg_size = sizeof(capi_v2_olm_set_inf_extn_module_config_t);

      if(params_ptr->actual_data_len > sizeof(capi_v2_olm_set_inf_extn_module_config_t))
      {
        MSG_4(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Failed in Set Param - Bad param size,"
                                              " param_id = 0x%lx, required size = %lu, given size = %lu",
                                              pMe->capi_v2_olm_identifier, param_id,cfg_size,
                                              params_ptr->actual_data_len);
        return CAPI_V2_ENEEDMORE; //RR: Badparam or needmore?
      }

      capi_v2_olm_set_inf_extn_module_config_t *inf_extn_info_ptr = (capi_v2_olm_set_inf_extn_module_config_t *)params_ptr->data_ptr;
      adsp_result = olm_send_set_intf_extn_config(pMe, inf_extn_info_ptr);
      result = adsp_result_to_capi_v2_err(adsp_result);

      break;
    }

    default:
    {
      MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Unsupported param_id 0x%lx",
                                            pMe->capi_v2_olm_identifier,param_id);
      result = CAPI_V2_EBADPARAM;
      break;
    }
  }

  MSG_3(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"CAPIv2 OLM 0x%8lX: Set param for 0x%lx done, result: %lu",
                                        pMe->capi_v2_olm_identifier, param_id, result);
  return result;
}

/**
 * This function is used to get the params for the OLM CAPI.
 *
 * @param[in] _pif, pointer to the CAPI lib
 * @param[in] param_id, param id to get.
 * @param[in] port_info_ptr, pointer to port info (optional)
 * @param[in, out] params_ptr, pointer to the param payload to be written here.
 *
 * @return capi_v2_err_t, result code
 */
static capi_v2_err_t capi_v2_olm_get_param(capi_v2_t* _pif, uint32_t param_id, const capi_v2_port_info_t *port_info_ptr, capi_v2_buf_t *params_ptr)
{
  capi_v2_err_t result  = CAPI_V2_EOK;
  if(NULL == _pif || NULL == params_ptr || NULL == params_ptr->data_ptr)
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM: Received bad property pointer for param_id property, 0x%lx", param_id);
    return CAPI_V2_EFAILED;
  }

  capi_v2_olm_t *me_ptr = (capi_v2_olm_t*)_pif;

  switch(param_id)
  {
    case CAPI_V2_PARAM_ID_OLM_GET_FWK_INF_EXTN_INFO:
    {
      if (params_ptr->max_data_len >= sizeof(capi_v2_olm_get_fwk_inf_extn_info_t))
      {
        capi_v2_olm_get_fwk_inf_extn_info_t *fwk_inf_extn_ptr = (capi_v2_olm_get_fwk_inf_extn_info_t *)params_ptr->data_ptr;
        if(me_ptr->fwk_inf_extn_info_ptr!=NULL)
        {
          fwk_inf_extn_ptr->data_ptr = me_ptr->fwk_inf_extn_info_ptr;
          params_ptr->actual_data_len = sizeof(capi_v2_olm_get_fwk_inf_extn_info_t);
        }
        else
        {
          fwk_inf_extn_ptr->data_ptr = NULL;
          params_ptr->actual_data_len = 0;
        }
#ifdef CAPI_V2_OLM_DEBUG
        MSG_2(MSG_SSID_QDSP6, DBG_MED_PRIO,"CAPIv2 OLM 0x%8lX: Get param to get the fwk/inf extension payload,"
                                           " payload length %lu",
                                           me_ptr->capi_v2_olm_identifier, params_ptr->actual_data_len);
#endif
      }
      else
      {
        MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Bad payload size %ld for param_id %ld",
                                              me_ptr->capi_v2_olm_identifier, params_ptr->max_data_len, param_id);
        CAPI_V2_SET_ERROR(result,CAPI_V2_ENEEDMORE);
      }
      break;
    }

    default:
    {
      MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Get parameter Failed - received bad param_id 0x%lx",
                                             me_ptr->capi_v2_olm_identifier, param_id);
      return CAPI_V2_EBADPARAM;
    }
  }
  return result;
}

/**
 * This function is used set properties of the OLM CAPI.
 *
 * @param[in] _pif, pointer to the CAPI lib.
 * @param[in] input, pointer to the input stream data.
 * @param[in, out] output, pointer to the output stream data.
 *
 * @return capi_v2_err_t, result code
 */
static capi_v2_err_t capi_v2_olm_process(capi_v2_t* _pif, capi_v2_stream_data_t* input[], capi_v2_stream_data_t* output[])
{
  if((NULL == _pif) || (NULL == input) || (NULL == output))
  {
    MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM: Received bad property pointer in process");
    return(CAPI_V2_EFAILED);
  }

  capi_v2_olm_t *pMe = (capi_v2_olm_t*)_pif;

  capi_v2_err_t result = CAPI_V2_EOK;
  uint32_t output_port_index =0;
  uint32_t wr_olm_proc_size_inst = 0;
  uint32_t rd_olm_proc_size_inst = 0;
  bool_t can_process_continue = FALSE;

  if( (!((pMe->num_active_input_ports > 0) && (pMe->num_active_input_ports <= OLM_MAX_INPUT_PORTS)))
      || (!((pMe->num_active_output_ports > 0) && (pMe->num_active_output_ports <= OLM_MAX_OUTPUT_PORTS))))
  {
    MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Process called with "
                                        "invalid ports initialized num_inputs = %d"
                                        "num_outputs", pMe->capi_v2_olm_identifier, pMe->num_active_input_ports,
                                        pMe->num_active_output_ports);
    olm_handle_disable_sequence(pMe, TRUE);
    return CAPI_V2_EFAILED;
  }

  result = capi_v2_olm_validate_io_buffers(pMe, input, output);
  if(CAPI_V2_FAILED(result))
  {
    MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Failed to validate io buffers "
                                            "with result 0x%x ", pMe->capi_v2_olm_identifier, result);
    olm_handle_disable_sequence(pMe, TRUE);
    return result;
  }

#ifdef OLM_SIM_FILE_DUMP
  if(pMe->in_file)
  {
    //fwrite(input[0]->buf_ptr[0].data_ptr, sizeof(int8_t), input[0]->buf_ptr[0].actual_data_len,pMe->in_file);
  }
#endif

  /* This module expects the data length in all channels to have same length */
  pMe->is_olm_instance_created = TRUE;

#ifdef CAPI_V2_OLM_DEBUG
  MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Started Processing data", pMe->capi_v2_olm_identifier);
#endif // #ifdef CAPI_V2_OLM_DEBUG

  capi_v2_olm_update_process_info(pMe,input,output);

  do
  {
    capi_v2_olm_determine_operating_rw_frame_size(pMe,input,output);

    for(uint32_t port_index =0; ((port_index < pMe->num_active_input_ports) && (port_index < OLM_MAX_INPUT_PORTS)); port_index++ )
    {
      if(NULL == pMe->process_info.olm_input[port_index])
      {
        continue;
      }

      wr_olm_proc_size_inst = pMe->process_info.wr_olm_proc_size * input[port_index]->bufs_num;
      uint32_t *wr_olm_done_size = &pMe->process_info.wr_olm_done_size[port_index];

      /* resetting the input lengths to zero for the input buffers of the port */
      result = capi_v2_olm_write_process(pMe, input, pMe->process_info.olm_input, wr_olm_proc_size_inst, wr_olm_done_size, port_index,output_port_index); //todo
      if(CAPI_V2_FAILED(result))
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Failed in Write processing data ",pMe->capi_v2_olm_identifier);
        olm_handle_disable_sequence(pMe, TRUE);
        return result;
      }
    }
#ifdef CAPI_V2_OLM_DEBUG
    MSG_3(MSG_SSID_QDSP6, DBG_LOW_PRIO, "CAPIv2 OLM 0x%8lX: in_data_marker is 0x%x remote_write_buf_mask is 0x%x",
                                        pMe->capi_v2_olm_identifier, pMe->process_info.in_data_marker,
                                        pMe->process_info.remote_write_buf_mask);
#endif

    /* Process write buffers for all the input ports */
    for(uint32_t out_port_index = 0; out_port_index < pMe->num_active_output_ports; out_port_index++ )
    {
      rd_olm_proc_size_inst = pMe->process_info.rd_olm_proc_size * output[out_port_index]->bufs_num;
      uint32_t *rd_olm_done_size = &pMe->process_info.rd_olm_done_size[out_port_index];

      result =  capi_v2_olm_read_process(pMe, output, pMe->process_info.olm_output, rd_olm_proc_size_inst, rd_olm_done_size, output_port_index);

      if(CAPI_V2_FAILED(result))
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Failed in Read processing data",pMe->capi_v2_olm_identifier);
        olm_handle_disable_sequence(pMe, TRUE);
        return result;
      }
    }
    wr_olm_proc_size_inst = pMe->process_info.wr_olm_proc_size * input[0]->bufs_num;
    can_process_continue = capi_v2_olm_determine_can_process_continue(pMe, wr_olm_proc_size_inst , rd_olm_proc_size_inst);

  } while (can_process_continue);

#ifdef OLM_DATA_PATH_LATENCY_MEASUREMENT
  detect_random_sample_in_capiv2_output_buffer(pMe);
#endif

  return CAPI_V2_EOK;
}

/**
 * This function is end of the OLM CAPI.
 *
 * @param[in] _pif, pointer to the CAPI lib.
 *
 */
static capi_v2_err_t capi_v2_olm_end(capi_v2_t* _pif)
{
  ADSPResult result = ADSP_EOK;
  if(NULL == _pif)
  {
    MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM: FAILED received invalid instance pointer during END");
    return CAPI_V2_EFAILED;
  }

  capi_v2_olm_t *me_ptr = (capi_v2_olm_t*)_pif;

  uint32_t olm_iid = me_ptr->capi_v2_olm_identifier;
  MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Process END", olm_iid);

#ifdef OLM_DATA_PATH_LATENCY_MEASUREMENT
  olm_print_data_latency_statistics(me_ptr);
#endif


  uint32_t port_idx = 0;

  for( port_idx = 0; port_idx < me_ptr->num_active_input_ports; port_idx++)
  {
    olm_dealloc_write_data_buffers(me_ptr, port_idx);
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Write Buffers cleaned up", olm_iid);
  }

  for( port_idx = 0; port_idx < me_ptr->num_active_output_ports; port_idx++)
  {
    olm_dealloc_read_data_buffers(me_ptr, port_idx);
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Read Buffers cleaned up", olm_iid);
  }

  if(me_ptr->fwk_inf_extn_info_ptr!=NULL)
  {
    qurt_elite_memory_free(me_ptr->fwk_inf_extn_info_ptr);
  }

  if(me_ptr->olm_topo_def.active_module_def!=NULL)
  {
    qurt_elite_memory_free(me_ptr->olm_topo_def.active_module_def);
  }

  if(me_ptr->olm_cfg.dynamic_cfg!=NULL)
  {
    qurt_elite_memory_free(me_ptr->olm_cfg.dynamic_cfg);
  }

  olm_check_free_cmd_handles(me_ptr);

#ifdef OLM_SIM_FILE_DUMP
  fclose(me_ptr->in_file);
  fclose(me_ptr->out_file);

  me_ptr->in_file = NULL;
  me_ptr->out_file = NULL;

#endif

  if(ADSP_FAILED(result = elite_apr_if_deregister(me_ptr->apr_handle)))
  {
    MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM %lu : Failed to deregister APR with result = 0x%x",olm_iid, result);
  }

  me_ptr->vtbl_ptr = NULL;

  return CAPI_V2_EOK;
}

/**
 * This function is used set properties of the OLM CAPI.
 *
 * @param[in] _pif, pointer to the CAPI lib.
 * @param[in] props_ptr, pointer to the prop list that needs to be set.
 *
 * @return capi_v2_err_t, result code
 */
static capi_v2_err_t capi_v2_olm_set_properties(capi_v2_t* _pif, capi_v2_proplist_t *props_ptr)
{

  capi_v2_err_t  capi_v2_result = CAPI_V2_EOK;
  if (NULL == _pif)
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM: Set properties received bad pointer, 0x%lx",(uint32_t)_pif);
    return CAPI_V2_SET_ERROR(capi_v2_result, CAPI_V2_EBADPARAM);
  }
  capi_v2_olm_t *me_ptr = (capi_v2_olm_t *)_pif;
  capi_v2_result |= capi_v2_olm_process_set_properties(me_ptr, props_ptr);
  return capi_v2_result;
}

/**
 * This function is used get properties of the OLM CAPI.
 *
 * @param[in] _pif, pointer to the CAPI lib.
 * @param[in] props_ptr, pointer to the prop list that needs to be set.
 *
 * @return capi_v2_err_t, result code
 */
static capi_v2_err_t capi_v2_olm_get_properties(capi_v2_t* _pif, capi_v2_proplist_t *props_ptr)
{
  capi_v2_err_t  capi_v2_result = CAPI_V2_EOK;
  if (NULL == _pif)
  {
    MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM: Get properties received "
          "bad instance/proplist pointer -instance 0x%lx proplist 0x%lx"
          ,(uint32_t)_pif, (uint32_t) props_ptr);
    return CAPI_V2_SET_ERROR(capi_v2_result, CAPI_V2_EBADPARAM);
  }
  capi_v2_olm_t *me_ptr = (capi_v2_olm_t *)_pif;
  capi_v2_result |= capi_v2_olm_process_get_properties(me_ptr, props_ptr);
  return capi_v2_result;
}
