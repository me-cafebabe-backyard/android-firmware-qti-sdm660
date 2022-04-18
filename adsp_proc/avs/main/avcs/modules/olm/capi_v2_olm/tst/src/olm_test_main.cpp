/*==========================================================================
 * Copyright (c) 2014-2015 QUALCOMM Technologies Incorporated.
 * All rights reserved.
 * Qualcomm Technologies Proprietary and Confidential.
 *==========================================================================*/

/**
 * @file main.cpp
 *
 * Standalone Setup for CAPI_V2 modules. This can be used with any CAPI_V2
 * by defining 3 macros in makefile corresponding to capi_v2 header,
 * capi_v2 get static prop function and capi_v2 init function.
 */

/*==========================================================================
 * Edit History:
 * when         who         what, where, why
 * ----------   ---         ------------------------------------------------
 * 2014/07/02   kgodara     CAPI_V2 standslone setup
 *==========================================================================*/


//#ifndef CAPI_V2_STATIC_PROP_FUNCTION
//#error "Please specify the capi_v2 static property function in makefile"
//#endif
//
//#ifndef CAPI_V2_INIT_FUNCTION
//#error "Please specify the capi_v2 init function in makefile"
//#endif

#include "capi_v2_olm_test.h"
#include "capi_v2_olm.h"
#include "Elite_fwk_extns_olm.h"
#include "adsp_error_codes.h"
#include "EliteMsg.h"
#include "rx_codec_gain_ctrl_calib.h"
#include "adsp_asm_stream_commands.h"
#include "adsp_media_fmt.h"

#define OLM_TEST_MAX_RSP_Q_ELEMENTS 8

typedef struct olm_test_obj_t  olm_test_obj_t;

struct olm_test_obj_t
{
  capi_v2_olm_open_t open_cmd;
  elite_cmn_olm_topo_db_entry_t db_info;
  qurt_elite_channel_t channel;
  qurt_elite_queue_t *resp_q;
  QURT_ELITE_ALIGN(char rsp_qBuf[QURT_ELITE_QUEUE_GET_REQUIRED_BYTES(OLM_TEST_MAX_RSP_Q_ELEMENTS)],8);
};

capi_v2_t *me_ptr = NULL;

olm_test_obj_t olm_cur_test_obj;

capi_v2_olm_open_t olm_test_open_cmd;
elite_cmn_olm_topo_db_entry_t olm_test_db_info;

avcs_module_instance_proc_info_t olm_test_module_info = {0x00010C37,
    0,
    0};

capi_v2_err_t test_olm_capi_set_param()
{
  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO,
      "OLM_TEST: test_olm_capi_set_param");

  capi_v2_err_t result = CAPI_V2_EOK;

  int8_t *ptr = (int8_t*)qurt_elite_memory_malloc(sizeof(asm_stream_param_data_v3_t)+ sizeof(audproc_rx_codec_gain_t),
                                                  QURT_ELITE_HEAP_DEFAULT);

  asm_stream_param_data_v3_t *setp_payload = (asm_stream_param_data_v3_t *)ptr;

  setp_payload->module_id   = 0x00010C37;
  setp_payload->instance_id = 0;
  setp_payload->reserved    = 0;
  setp_payload->param_id    = AUDPROC_PARAM_ID_RX_CODEC_GAIN  ;
  setp_payload->param_size  = sizeof(audproc_rx_codec_gain_t);
  ptr += sizeof(asm_stream_param_data_v3_t);

  audproc_rx_codec_gain_t *gain_cfg = (audproc_rx_codec_gain_t* )ptr;
  gain_cfg->rx_codec_gain = 0xE;
  gain_cfg->reserved      = 0;

  capi_v2_olm_setparam_t olm_setp_cfg;
  olm_setp_cfg.token = 0x00001234;
  olm_setp_cfg.mode = 0;
  olm_setp_cfg.payload_size =  sizeof(asm_stream_param_data_v3_t)+ sizeof(audproc_rx_codec_gain_t);
  olm_setp_cfg.payload_ptr = (void *)setp_payload;

  capi_v2_buf_t buf;
  buf.data_ptr        = (int8_t*) &olm_setp_cfg;
  buf.actual_data_len = sizeof(capi_v2_olm_setparam_t);
  buf.max_data_len    = sizeof(capi_v2_olm_setparam_t);

  me_ptr->vtbl_ptr->set_param(me_ptr,
                              CAPI_V2_PARAM_ID_OLM_SETPARAM,
                              NULL,
                              &buf);
  return result;
}

capi_v2_err_t test_olm_capi_get_param()
{
  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO,
      "OLM_TEST: test_olm_capi_set_param");

  capi_v2_err_t result = CAPI_V2_EOK;


  int8_t *ptr = (int8_t*)qurt_elite_memory_malloc(sizeof(audproc_rx_codec_gain_t),
                                                  QURT_ELITE_HEAP_DEFAULT);

  capi_v2_olm_getparam_t olm_getp_cfg;
  olm_getp_cfg.token = 0x00005555;
  olm_getp_cfg.mode = 0;
  olm_getp_cfg.module_id = 0x00010C37;
  olm_getp_cfg.instance_id = 0;
  olm_getp_cfg.param_id = AUDPROC_PARAM_ID_RX_CODEC_GAIN;
  olm_getp_cfg.max_data_size = sizeof(audproc_rx_codec_gain_t);
  olm_getp_cfg.payload = (void *)ptr;


  capi_v2_buf_t buf;
  buf.data_ptr        = (int8_t*) &olm_getp_cfg;
  buf.actual_data_len = sizeof(capi_v2_olm_getparam_t);
  buf.max_data_len    = sizeof(capi_v2_olm_getparam_t);

  me_ptr->vtbl_ptr->set_param(me_ptr,
                              CAPI_V2_PARAM_ID_OLM_GETPARAM,
                              NULL,
                              &buf);

  return result;
}

capi_v2_err_t test_olm_capi_set_media_fmt()
{
  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO,
    "OLM_TEST: test_olm_capi_set_media_fmt");

  capi_v2_err_t result = CAPI_V2_EOK;

   capi_v2_set_get_media_format_t *pFmt;
   capi_v2_standard_data_format_t *pStd;

  uint32_t payload_size = sizeof(capi_v2_set_get_media_format_t) + sizeof(capi_v2_standard_data_format_t);

  int8_t *ptr = (int8_t*) qurt_elite_memory_malloc(payload_size, QURT_ELITE_HEAP_DEFAULT);

  pFmt = (  capi_v2_set_get_media_format_t *) ptr;
  pFmt->format_header.data_format = CAPI_V2_RAW_COMPRESSED;

  pStd = (capi_v2_standard_data_format_t *)(ptr + sizeof(capi_v2_set_get_media_format_t));
  pStd->bitstream_format = ASM_MEDIA_FMT_MULTI_CHANNEL_PCM_V2;
  pStd->num_channels     = 1;
  pStd->bits_per_sample  = 16;
  pStd->q_factor         = 1;
  pStd->sampling_rate    = 48000;
  pStd->data_is_signed   = 0;
  pStd->data_interleaving= CAPI_V2_INTERLEAVED;
  pStd->channel_type[0]  = PCM_CHANNEL_C;

  capi_v2_prop_t media_prop;

  media_prop.id = CAPI_V2_INPUT_MEDIA_FORMAT;

  media_prop.payload.data_ptr        = ptr;
  media_prop.payload.actual_data_len = payload_size;
  media_prop.payload.max_data_len    = payload_size;

  media_prop.port_info.is_valid      = 1;
  media_prop.port_info.is_input_port = TRUE;
  media_prop.port_info.port_index    = 0;

  capi_v2_proplist_t plist;
  plist.props_num = 1;
  plist.prop_ptr  = &media_prop;

  me_ptr->vtbl_ptr->set_properties(me_ptr,
                                     &plist );


 MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO,
    "OLM_TEST: test_olm_capi_set_media_fmt successful");


  return result;
}

capi_v2_err_t test_olm_capi_get_static_properties()
{
  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO,
      "OLM_TEST: test_olm_capi_get_static_properties");

  capi_v2_err_t result = CAPI_V2_EOK;

  /* Query for CAPI_V2 size */
  capi_v2_proplist_t static_properties;
  static_properties.props_num = 1;
  capi_v2_prop_t prop_ptr[static_properties.props_num];
  static_properties.prop_ptr = prop_ptr;

  /* Populate INIT_MEMORY_REQUIREMENT query */
  capi_v2_init_memory_requirement_t mem_req;
  prop_ptr[0].id = CAPI_V2_INIT_MEMORY_REQUIREMENT;
  prop_ptr[0].payload.max_data_len = sizeof(mem_req);
  prop_ptr[0].payload.data_ptr = (int8_t *)&mem_req;
  prop_ptr[0].port_info.is_valid = FALSE;

  result = CAPI_V2_STATIC_PROP_FUNCTION(
      NULL, &static_properties);
  if (CAPI_V2_EOK != result)
  {
    MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO,
        "OLM_TEST: Failed to query for module size");
    return CAPI_V2_EFAILED;
  }

  MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO,
        "OLM_TEST: %lu bytes required for module.",
        mem_req.size_in_bytes);

  /* STEP 2: Allocate memory */
  uint8_t *ptr = (uint8_t*)qurt_elite_memory_malloc(
      mem_req.size_in_bytes, QURT_ELITE_HEAP_DEFAULT);
  if (NULL == ptr)
  {
    MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO,
        "OLM_TEST: Memory allocation error");
    return CAPI_V2_ENOMEMORY;
  }
  me_ptr = (capi_v2_t *)ptr;
  MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO,
        "OLM_TESTModule allocated for %lu bytes of memory at location 0x%p.",
        mem_req.size_in_bytes,
        me_ptr);

  return result;
}

capi_v2_err_t test_olm_capi_init()
{
  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO,
      "OLM_TEST:  test_olm_capi_init");

  capi_v2_err_t result = CAPI_V2_EOK;

  /* STEP 3: Initialize module */
  capi_v2_prop_t hp_prop;


  capi_v2_heap_id_t mem;
  mem.heap_id = QURT_ELITE_HEAP_DEFAULT;


  hp_prop.id = CAPI_V2_HEAP_ID;
  hp_prop.payload.actual_data_len = sizeof(mem);
  hp_prop.payload.max_data_len = sizeof(mem);
  hp_prop.payload.data_ptr = reinterpret_cast<int8_t*>(&mem);

  capi_v2_proplist_t init_proplist;
  init_proplist.props_num = 1 ;
  init_proplist.prop_ptr = &hp_prop;

  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "OLM_TEST: capiv2 init");
  result = CAPI_V2_INIT_FUNCTION((capi_v2_t *)me_ptr, &init_proplist);

  return result;
}


void test_olm_call_back_fn(void *ptr,capi_v2_olm_resp_id_t id, capi_v2_olm_resp_info_t *resp_info_ptr)
{
  MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO,
        "OLM_TEST:  test_olm_call_back_fn, recieved reponse with RESP_ID: %x ",id);
  
  void *temp_ptr    = resp_info_ptr->payload.data_ptr;
  uint32_t actual_data_len = resp_info_ptr->payload.actual_data_len;
  
  switch(id)
  {
    case CAPI_V2_OLM_RESP_OPEN:
    {
      if(actual_data_len < sizeof(capi_v2_olm_open_resp_t) )
      {
        MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO,
                    "OLM_TEST:  test_olm_call_back_fn, CAPI_V2_OLM_RESP_OPEN reponse has incorrect payload.");
        break;
      }
      
      capi_v2_olm_open_resp_t *data_ptr = ( capi_v2_olm_open_resp_t *) temp_ptr;

      if(ADSP_FAILED(data_ptr->result))
      {
        MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO,
              "OLM_TEST:  test_olm_call_back_fn, recieved CAPI_V2_OLM_RESP_OPEN Failed");
      }
      else
      {
        MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO,
              "OLM_TEST:  test_olm_call_back_fn, recieved CAPI_V2_OLM_RESP_OPEN Successfull");

      }
      break;
    }

    case CAPI_V2_OLM_RESP_SETPARAM:
    {
      if(actual_data_len < sizeof(capi_v2_olm_setparam_resp_t) )
      {
        MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO,
                    "OLM_TEST:  test_olm_call_back_fn, CAPI_V2_OLM_RESP_SETPARAM reponse has incorrect payload.");
        break;
      }

      capi_v2_olm_setparam_resp_t *data_ptr = ( capi_v2_olm_setparam_resp_t *) temp_ptr;

      if(ADSP_FAILED(data_ptr->result))
      {
        MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO,
              "OLM_TEST:  test_olm_call_back_fn, recieved CAPI_V2_OLM_RESP_SETPARAM Failed");
      }
      else
      {
        MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO,
              "OLM_TEST:  test_olm_call_back_fn, recieved CAPI_V2_OLM_RESP_SETPARAM Successfull");

      }
      break;
    }


    case CAPI_V2_OLM_RESP_GETPARAM:
    {
      if(actual_data_len < sizeof(capi_v2_olm_getparam_resp_t) )
      {
        MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO,
                    "OLM_TEST:  test_olm_call_back_fn, CAPI_V2_OLM_RESP_GETPARAM reponse has incorrect payload.");
        break;
      }

      capi_v2_olm_getparam_resp_t *data_ptr = ( capi_v2_olm_getparam_resp_t *) temp_ptr;

      if(ADSP_FAILED(data_ptr->result))
      {
        MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO,
              "OLM_TEST:  test_olm_call_back_fn, recieved CAPI_V2_OLM_RESP_GETPARAM Failed");
      }
      else
      {
        MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO,
              "OLM_TEST:  test_olm_call_back_fn, recieved CAPI_V2_OLM_RESP_GETPARAM Successfull");
      }
      break;
    }



    default:
      break;
  }

}

capi_v2_err_t test_olm_capi_open()
{

  capi_v2_err_t result = CAPI_V2_EOK;

  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO,
      "OLM_TEST:  test_olm_capi_open");

  /*
   *  Init command queue
   */
  /* Initalize the channel*/
  qurt_elite_channel_init(&(olm_cur_test_obj.channel));

  qurt_elite_queue_t *temp_ptr;
  char  rsp_q_name[]  =  "olm_test_resp_q";

  //Create the rspQ.
  temp_ptr =(qurt_elite_queue_t *)olm_cur_test_obj.rsp_qBuf;

  if (ADSP_FAILED(result = (qurt_elite_queue_init(rsp_q_name, OLM_TEST_MAX_RSP_Q_ELEMENTS,temp_ptr ))))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "test_olm_capi_open: responseQ creation failed, result: 0x%lx", result);
    return result;
  }

  if (ADSP_FAILED(result = qurt_elite_channel_addq(&(olm_cur_test_obj.channel), temp_ptr,0)))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "MDF: failed to add responseQ to channel, result: 0x%lx", result);
    return result;
  }

  ////////////////////////////

  olm_cur_test_obj.resp_q = temp_ptr;

  /*Create open command payload */
  olm_test_open_cmd.olm_iid =0;
  olm_test_open_cmd.frame_size_in_us = 5000;
  olm_test_open_cmd.scale_factor = 1;
  olm_test_open_cmd.token = 0xAAA00BBB;

  olm_test_db_info.olm_iid      = 0;
  olm_test_db_info.num_modules  = 1;
  olm_test_db_info.is_sync_mode = FALSE;
  olm_test_db_info.module_info = &olm_test_module_info;

  olm_test_open_cmd.olm_topo_info_ptr = &olm_test_db_info ;
  olm_test_open_cmd.cmd_respQ  = temp_ptr;

  olm_test_open_cmd.olm_resp_cb_info.cb_fn_ptr = test_olm_call_back_fn;
  olm_test_open_cmd.olm_resp_cb_info.context_ptr = NULL;

  /* Send the payload*/

  capi_v2_buf_t open_param_info;

  open_param_info.data_ptr          = (int8_t*) &olm_test_open_cmd;
  open_param_info.actual_data_len   = sizeof(olm_test_open_cmd);
  open_param_info.max_data_len   = sizeof(olm_test_open_cmd);

  me_ptr->vtbl_ptr->set_param(me_ptr,
                              CAPI_V2_PARAM_ID_OLM_OPEN,
                              NULL,
                              &open_param_info);

  return result;
}

void test_olm_wait_for_response()
{
  //  struct olm_test_obj_t
  //  {
  //    capi_v2_olm_open_t open_cmd;
  //    elite_cmn_olm_topo_db_entry_t db_info;
  //    qurt_elite_channel_t channel;
  //    qurt_elite_queue_t *resp_q;
  //  };

  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO,
      "OLM_TEST:  test_olm_wait_for_response function.");

  uint32_t channel_bit_field;
  channel_bit_field = qurt_elite_queue_get_channel_bit(olm_cur_test_obj.resp_q);

  elite_msg_any_t rsp_msg;

  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO,
      "OLM_TEST:  test_olm_wait_for_response: Waiting for OPEN response...");

  qurt_elite_channel_wait(&(olm_cur_test_obj.channel),channel_bit_field);

  /* pop the response from reponse queue*/
  for (;; )
  {
    int32_t res = qurt_elite_queue_pop_front(olm_cur_test_obj.resp_q, (uint64*)(&rsp_msg));
    /* break out of loop if there are no more messages */
    if (res == ADSP_ENEEDMORE) break;

    elite_apr_packet_t *pkt_ptr = (elite_apr_packet_t*) rsp_msg.pPayload;
    MSG_2( MSG_SSID_QDSP6, DBG_MED_PRIO, "OLM test: response received token: %lx Op CODE: %lx \n",
           elite_apr_if_get_client_token(pkt_ptr), rsp_msg.unOpCode );

    if(OLM_REMOTE_RSP_MSG == rsp_msg.unOpCode)
    {
      /* Send the packet to the OLM for response handling*/
      capi_v2_olm_resp_pkt_t olm_resp;
      olm_resp.pkt_ptr = pkt_ptr;

      capi_v2_buf_t buf;
      buf.data_ptr        = (int8_t*) &olm_resp;
      buf.actual_data_len = sizeof(capi_v2_olm_resp_pkt_t);
      buf.max_data_len    = sizeof(capi_v2_olm_resp_pkt_t);

      me_ptr->vtbl_ptr->set_param(me_ptr,
                                  CAPI_V2_PARAM_ID_OLM_RESP_PKT,
                                  NULL,
                                  &buf);
    }

  } // for (;;);

    MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO,
        "OLM_TEST:  test_olm_wait_for_response: Received OPEN response!!! ");

  /* Once the setparam command is successful, we can do get param*/

  test_olm_capi_set_param();

  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO,
      "OLM_TEST:  test_olm_wait_for_response: Waiting for SET PARAM response...");

  qurt_elite_channel_wait(&(olm_cur_test_obj.channel),channel_bit_field);


    /* pop the response from reponse queue*/
  for (;; )
  {
    int32_t res = qurt_elite_queue_pop_front(olm_cur_test_obj.resp_q, (uint64*)(&rsp_msg));
    /* break out of loop if there are no more messages */
    if (res == ADSP_ENEEDMORE) break;

    elite_apr_packet_t *pkt_ptr = (elite_apr_packet_t*) rsp_msg.pPayload;
    MSG_2( MSG_SSID_QDSP6, DBG_MED_PRIO, "OLM test: response received token: %lx Op CODE: %lx \n",
           elite_apr_if_get_client_token(pkt_ptr), rsp_msg.unOpCode );

    if(OLM_REMOTE_RSP_MSG == rsp_msg.unOpCode)
    {
      /* Send the packet to the OLM for response handling*/
      capi_v2_olm_resp_pkt_t olm_resp;
      olm_resp.pkt_ptr = pkt_ptr;

      capi_v2_buf_t buf;
      buf.data_ptr        = (int8_t*) &olm_resp;
      buf.actual_data_len = sizeof(capi_v2_olm_resp_pkt_t);
      buf.max_data_len    = sizeof(capi_v2_olm_resp_pkt_t);

      me_ptr->vtbl_ptr->set_param(me_ptr,
                                  CAPI_V2_PARAM_ID_OLM_RESP_PKT,
                                  NULL,
                                  &buf);
    }

  } // for (;;);

  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO,
        "OLM_TEST:  test_olm_wait_for_response: Received a SET PARAM response!!! ");

    test_olm_capi_set_media_fmt();

  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO,
        "OLM_TEST:  test_olm_wait_for_response: Received a  Media format set prop response!!! ");


  /* Once the setparam command is successful, we can do get param*/
  test_olm_capi_get_param();


  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO,
      "OLM_TEST:  test_olm_wait_for_response: Waiting for GET PARAM response...");

  qurt_elite_channel_wait(&(olm_cur_test_obj.channel),channel_bit_field);

    /* pop the response from reponse queue*/
  for (;; )
  {
    int32_t res = qurt_elite_queue_pop_front(olm_cur_test_obj.resp_q, (uint64*)(&rsp_msg));
    /* break out of loop if there are no more messages */
    if (res == ADSP_ENEEDMORE) break;

    elite_apr_packet_t *pkt_ptr = (elite_apr_packet_t*) rsp_msg.pPayload;
    MSG_2( MSG_SSID_QDSP6, DBG_MED_PRIO, "OLM test: response received token: %lx Op CODE: %lx \n",
           elite_apr_if_get_client_token(pkt_ptr), rsp_msg.unOpCode );

    if(OLM_REMOTE_RSP_MSG == rsp_msg.unOpCode)
    {
      /* Send the packet to the OLM for response handling*/
      capi_v2_olm_resp_pkt_t olm_resp;
      olm_resp.pkt_ptr = pkt_ptr;

      capi_v2_buf_t buf;
      buf.data_ptr        = (int8_t*) &olm_resp;
      buf.actual_data_len = sizeof(capi_v2_olm_resp_pkt_t);
      buf.max_data_len    = sizeof(capi_v2_olm_resp_pkt_t);

      me_ptr->vtbl_ptr->set_param(me_ptr,
                                  CAPI_V2_PARAM_ID_OLM_RESP_PKT,
                                  NULL,
                                  &buf);
    }

  } // for (;;);

  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO,
        "OLM_TEST:  test_olm_wait_for_response: Received a GET PARAM response!!! ");
  
}


int capi_v2_olm_test_main()
{
  capi_v2_err_t result = CAPI_V2_EOK;

  /* STEP 1: Get size requirements of CAPI_V2 */
  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"MAIN: -----------------");
  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"MAIN: Initialize OLM module");
  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"MAIN: -----------------");

  result = test_olm_capi_get_static_properties();
  if(CAPI_V2_EOK != result)
  {
    MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "MAIN: test_olm_capi_init() error");
    return result;
  }


  result = test_olm_capi_init();
  if (CAPI_V2_EOK != result)
  {
    MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "MAIN: test_olm_capi_init error");
    qurt_elite_memory_free(me_ptr);
    return result;
  }

  /* Send open command*/
  result = test_olm_capi_open();
  if(CAPI_V2_EOK != result)
  {
    MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "MAIN: test_olm_capi_open() error");
    return result;
  }

  test_olm_wait_for_response();

  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"MAIN: Done");
  return result;
}

