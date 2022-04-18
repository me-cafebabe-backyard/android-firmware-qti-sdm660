/**
@file olm_utils.h

@brief This header file contains the utility functions for Off-loading module

 */

/*========================================================================

Edit History

when          who            what, where, why
--------      ---            -------------------------------------------------------
18/9/2017     RV             Initial version
==========================================================================*/

/*-----------------------------------------------------------------------
Copyright (c) 2017-2018 Qualcomm Technologies, Inc.  All Rights Reserved.
Confidential and Proprietary - Qualcomm Technologies, Inc.
-----------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/

#include "Elite_CAPI_V2.h"
#include "qurt_elite.h"
#include "capi_v2_olm.h"
#include "capi_v2_olm_internal.h"
#include "qurt_elite_memory.h"
#include "Elite_fwk_extns_olm.h"
#include "EliteAprIf.h"
#include "ap_server_api.h"
#include "adsp_asm_stream_commands.h"


#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

#define GIVEN_INSTANCE 3
#define ZERO_INSTANCE 1

#define IS_ALIGN_4_BYTE(a) (!(a & 0x3))

#define IPC_LATENCY_IN_NUM_FRAMES   1       //in number of frames

#define RD_CHAN_BIT_MASK 0x80000000
#define WR_CHAN_BIT_MASK 0x80000000


 /*----------------------------------------------------------------------------
 * Function Declarations
 * -------------------------------------------------------------------------*/

/** ---------------- OLM APR Command Utilities------------------------------------------------*/

int32_t remote_response_apr_dispatch_fn( aprv2_packet_t *apr_pkt,
                                         void* context_ptr);
ADSPResult olm_apr_get_remote_svc_addr(capi_v2_olm_t *me_ptr,
                                       uint16_t *server_address);
ADSPResult olm_apr_register(capi_v2_olm_t *pMe);
ADSPResult olm_send_open_cmd(capi_v2_olm_t *pMe);
ADSPResult olm_send_run_cmd(capi_v2_olm_t *me_ptr,
                            capi_v2_olm_run_t *cfg_ptr);
ADSPResult olm_set_param(capi_v2_olm_t *pMe,
                         capi_v2_olm_setparam_t *cfg_ptr);
ADSPResult olm_set_remote_config(capi_v2_olm_t *me_ptr,
                                   void *payload_ptr,
                                   uint32_t payload_size);
ADSPResult olm_get_param(capi_v2_olm_t * pMe,
                         capi_v2_olm_getparam_t *cfg);
ADSPResult olm_send_flush_cmd(capi_v2_olm_t *pMe,
                              capi_v2_olm_flush_t *cfg);
ADSPResult olm_send_close_cmd(capi_v2_olm_t *pMe,
                              capi_v2_olm_close_t *cfg);
ADSPResult olm_send_disable_event(capi_v2_olm_t *me_ptr);
ADSPResult olm_send_simple_ap_container_cmd(capi_v2_olm_t *me_ptr,
                                                uint32_t cmd_id,
                                                uint32_t param_id,
                                                uint16_t param_version,
                                                uint16_t param_struct_size,
                                                uint32_t token,
                                                uint16_t remote_apr_addr,
                                                uint16_t remote_port_no);
ADSPResult olm_send_set_intf_extn_config(capi_v2_olm_t *me_ptr,
                                             capi_v2_olm_set_inf_extn_module_config_t *inf_extn_info_ptr);
ADSPResult olm_send_data_cmd(capi_v2_olm_t *me_ptr,
                             void *data_buf_ptr,
                             olm_data_cmd_type_t cmd_type);

/**<------------- OLM APR Response Utilities------------------------------------------------*/

void olm_response_pkt_handler(capi_v2_olm_t *pMe, elite_apr_packet_t *respPkt);
capi_v2_err_t olm_event_handler(capi_v2_olm_t *me_ptr, elite_apr_packet_t* buffer);

/**<------------- OLM Command Handler Utilities---------------------------------------------*/

ADSPResult store_cmd_payload(capi_v2_olm_t *me_ptr,
                               uint32_t cmd,
                               uint32_t token,
                               void * payload);
void *get_cmd_payload(capi_v2_olm_t *me_ptr,
                        uint32_t cmd,
                        uint32_t token);
void free_cmd_handle(capi_v2_olm_t *me_ptr,
                     uint32_t cmd, uint32_t token);
void olm_check_free_cmd_handles(capi_v2_olm_t * me_ptr);

/**<------------- OLM Media Format Utilities------------------------------------------------*/

ADSPResult olm_send_media_fmt(capi_v2_olm_t *me_ptr,
                                capi_v2_set_get_media_format_t *pFmt,
                                capi_v2_standard_data_format_v2_t *pStd,
                                uint32_t port_index);
ADSPResult olm_update_media_fmt(capi_v2_olm_t *me_ptr,
                                  int8_t* payload,
                                  uint16_t param_size,
								  uint32_t *payload_size);
ADSPResult olm_raise_output_media_fmt_event(capi_v2_olm_t *me_ptr);

/**<------------- OLM Buffer Management Utilities---------------------------------------------*/

void olm_update_num_buffers(capi_v2_olm_t *me_ptr,
                                olm_data_cmd_type_t cmd_type,
                                uint32_t port_index );
ADSPResult olm_create_queues(capi_v2_olm_t *me_ptr,
                               olm_data_cmd_type_t cmd_type,
                               uint32_t port_index);
void olm_destroy_queues(capi_v2_olm_t *me_ptr,
                        olm_data_cmd_type_t cmd_type,
                        uint32 port_index);
ADSPResult olm_alloc_write_data_buffers(capi_v2_olm_t *me_ptr,
                                        uint32_t port_index);
ADSPResult olm_realloc_write_data_buffer(capi_v2_olm_t *me_ptr,
                                         olm_write_buf_t *wr_data_buf_ptr,
                                         uint32_t port_index);
ADSPResult olm_alloc_read_data_buffers(capi_v2_olm_t *me_ptr, uint32_t port_index);
ADSPResult olm_realloc_read_data_buffer(capi_v2_olm_t *me_ptr,
                                        olm_read_buf_t *rd_data_buf_ptr,
                                        uint32_t port_index);
ADSPResult olm_remove_deprecated_read_buffer(capi_v2_olm_t *me_ptr,
                                             olm_read_buf_t *dep_buf_ptr,
                                             uint32_t port_index);
ADSPResult olm_remove_deprecated_write_buffer(capi_v2_olm_t *me_ptr,
                                              olm_write_buf_t *dep_buf_ptr,
                                              uint32_t port_index);
bool_t is_deprecated_buffer(void *data_buf_ptr, olm_data_cmd_type_t cmd_type);
void olm_dealloc_write_data_buffers(capi_v2_olm_t *me_ptr, uint32_t port_index);
void olm_dealloc_read_data_buffers(capi_v2_olm_t *me_ptr, uint32_t port_index);
ADSPResult get_wr_data_buf_ptr(capi_v2_olm_t *me_ptr,
                               elite_apr_packet_t *data_apr_pkt_ptr,
                               uint32_t port_index,
                               olm_write_buf_t **wr_data_buf_ptr_ptr);
ADSPResult get_rd_data_buf_ptr(capi_v2_olm_t *me_ptr,
                               elite_apr_packet_t *data_apr_pkt_ptr,
                               uint32_t port_index,
                               olm_read_buf_t **rd_data_buf_ptr_ptr);
ADSPResult olm_send_temp_wr_buffer(capi_v2_olm_t *me_ptr, uint32_t port_index);
ADSPResult olm_pack_send_temp_wr_buffer(capi_v2_olm_t *me_ptr, uint32_t port_index);

/**<------------- OLM General Utilities-------------------------------------------------------*/

bool_t olm_check_if_module_present(elite_cmn_olm_topo_db_entry_t *olm_topo_ptr,
                                   uint32_t module_id,
                                   uint32_t instance_id);
ADSPResult olm_get_client_shm_mem_handle(uint32_t client_proc_id,
                                         uint32_t  in_mem_map_handle,
                                         uint32_t  in_addr_lsw,
                                         uint32_t  in_addr_msw,
                                         uint32_t  *out_mem_map_handle,
                                         uint32_t  *out_addr_lsw,
                                         uint32_t  *out_addr_msw );
ADSPResult olm_get_instance_id(elite_cmn_olm_topo_db_entry_t *olm_topo_ptr,
                                 uint32_t module_id,
                                 uint32_t *instance_id);
void olm_response_callback_wrapper(capi_v2_olm_t *me_ptr,
                                    uint32_t resp_id,
                                    int8_t *resp_ptr,
                                    uint32_t token );
void olm_response_cb_fn_wrapper(capi_v2_olm_t *me_ptr,
                                 capi_v2_olm_resp_id_t resp_id,
                                 int8_t *resp_ptr,
                                 uint32_t actual_data_len,
                                 uint32_t token );
void olm_elite_hexdump(const uint8_t* buffer, int32_t size);
void olm_set_reset_bitmask(uint32_t *mask_ptr, uint32_t pos, bool_t is_set);
bool_t is_olm_mask_set(uint32_t mask, uint32_t pos);
void olm_handle_disable_sequence(capi_v2_olm_t *me_ptr, bool_t is_olm_triggered);

#ifdef __cplusplus
}
#endif //__cplusplus

