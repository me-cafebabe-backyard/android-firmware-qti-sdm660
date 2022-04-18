/**
@file capi_v2_olm_internal.h

@brief Header file for Offload module with internal declarations

 */

/*========================================================================
$Header: //components/rel/avs.adsp/2.8/avcs/modules/olm/capi_v2_olm/src/capi_v2_olm_internal.h#18 $

Edit History

when       who     what, where, why
--------   ---     -------------------------------------------------------
9/18/2017   RV       Created
==========================================================================*/

/*-----------------------------------------------------------------------
Copyright (c) 2017-2018 Qualcomm Technologies, Inc.  All Rights Reserved.
Confidential and Proprietary - Qualcomm Technologies, Inc.
-----------------------------------------------------------------------*/

#include "qurt_elite.h"
#include "Elite_fwk_extns_olm.h"
#include "ap_server_api.h"
#include "capi_v2.h"
#include "capi_v2_adsp_error_code_converter.h"

#ifndef _CAPI_V2_OLM_T_H_
#define _CAPI_V2_OLM_T_H_

/* Size of the Array used to store OLM Commands*/
#define CMD_HANDLES_MAX_ARRAY_SIZE   16

/* Invalid index to access the OLM Command Handles Array */
#define CMD_HANDLE_INVALID_INDEX     0xFFFF

/* Macro defined for maximum number of Input ports supported by OLM */
#define OLM_MAX_INPUT_PORTS    2

/* Macro defined for maximum number of Output ports supported by OLM */
#define OLM_MAX_OUTPUT_PORTS   1

/* Macro definition for the primary input port for OLM*/
#define OLM_PRIMARY_INPUT_PORT 0

/* Macro definition for the primary output port for OLM*/
#define OLM_PRIMARY_OUTPUT_PORT 0

#define OLM_MAX_SAMPLE_RATE 384000

/* Default APR session port*/
#define DEFAULT_OLM_AP_SESSION_PORT 0x1

/* Stack size needed for OLM module. */ //TODO: This need to be profiled and updated once dev is completed
#define STACK_SIZE 2048

/* Size of shared memory allocated by OLM when sending open command to Remote AP */
#define OLM_OPEN_SHM_SIZE 1024

#define OLM_KPPS_REQ 20000 //TODO: Needs to be profiled

#define OLM_BW_REQ   20 //TODO: Needs to be profiled

/* CAPI v2 OLM module debug flag. Uncomment to enable debug messages */
//#define CAPI_V2_OLM_DEBUG 1

/* CAPI v2 OLM latency measurement flag. Uncomment to enable debug messages */
//#define OLM_LATENCY_MEASUREMENT 1

//#define OLM_DATA_PATH_LATENCY_MEASUREMENT 1

//#define OLM_SIM_FILE_DUMP
#ifdef OLM_SIM_FILE_DUMP
#include "stdio.h"
#include "stdlib.h"
#endif

inline uint32_t  bits_per_sample_2_bytes_per_sample(uint32_t bits_per_sample)
{
  return ((16 == bits_per_sample) ? 2 : 4);
}

typedef struct olm_cmd_handle_t olm_cmd_handle_t;

/* Command Handle structure used to cache any info
 * pertaining to the commands received */
struct olm_cmd_handle_t
{
  bool_t        is_used;
  uint32_t      token;
  uint32_t      cmd;
  void          *payload;
};

/*
 * OLM command handle structure, the can be used to cache the Get Param command
 * handle, to be able to handle the response.
 */
typedef struct olm_getparam_cmd_handle_t olm_getparam_cmd_handle_t;

struct olm_getparam_cmd_handle_t
{
  capi_v2_olm_getparam_t cfg;
  uint32_t               mem_map_hdl;
  uint32_t               shm_alloc_size;
  void                   *shm_mem_ptr;
};

struct olm_setparam_cmd_handle_t
{
  uint32_t mem_map_hdl;
  uint32_t shm_alloc_size;
  void     *shm_mem_ptr;
};

/* Number of write buffer Q elements */
#define OLM_WRITE_BUF_Q_ELEMENTS_MAX 32

/* Number of read buffer Q elements */
#define OLM_READ_BUF_Q_ELEMENTS_MAX 32

/* Base Media format structure */
typedef struct capi_v2_olm_base_media_fmt_t
{
  capi_v2_data_format_header_t h;
  capi_v2_standard_data_format_v2_t f;
}capi_v2_olm_base_media_fmt_t;

/* Media format structure */
typedef struct capi_v2_olm_media_fmt_t
{
  capi_v2_data_format_header_t h;
  capi_v2_standard_data_format_v2_t f;
  uint16_t channel_type[32];
}capi_v2_olm_media_fmt_t;


#ifdef OLM_DATA_PATH_LATENCY_MEASUREMENT

#define SAMPLE_POINTS 100

typedef struct capi_v2_olm_data_latency_t
{
	uint32_t sample_value[SAMPLE_POINTS];

	uint64_t timer_value[SAMPLE_POINTS];

	uint32_t fill_sample_index;

	uint32_t find_sample_index;

	uint32_t find_sample_index_olm_write;

	uint32_t find_sample_index_olm_read;

	uint32_t max_latency_stats[3];
	uint32_t min_latency_stats[3];

	uint64_t sample_consumed;

	uint64_t samples_delivered;

	uint64_t max_samples_buffered;
}capi_v2_olm_data_latency_t;

#endif



/* OLM data command type */
typedef enum
{
  WRITE_CMD = 0, //Indicates write data command
  READ_CMD //Indicates read data command
}olm_data_cmd_type_t;

/* write data buffer structure */
typedef struct olm_write_buf_t
{
  int8_t *data_buf_ptr;
  /* buffer pointer */

  uint32_t data_buf_size;
  /* Total buffer size for all channel*/

  uint32_t fill_size_per_ch;
  /* buffer size*/

  uint32_t buf_size_per_ch;
  /* buffer size*/

  uint32_t token;
  /* token to communicate with remote service */

  ap_container_data_write_buffer_v1_t data_write_buf;
  /* write data buffer for remote service */

  bool_t buf_in_use;
  /* Flag set when buffer in use*/

  bool_t is_deprecated;
  /* flag set if buffer needs to be deprecated */

  olm_write_buf_t *next;
  /* Next node in the linked list*/
}olm_write_buf_t;

/* read data buffer structure */
typedef struct olm_read_buf_t
{
  int8_t *data_buf_ptr;
  /* buffer pointer */

  uint32_t data_buf_size;
  /* buffer size*/

  uint32_t token;
  /* token to communicate with remote service */

  uint32_t rd_offset;
  /* Read offset indicates how much data is read from this buffer */

  uint32_t rd_offset_per_ch;
  /* buffer size*/

  uint32_t buf_size_per_ch;
  /* buffer size*/

  ap_container_data_read_done_param_v1_t data_read_buf;
  /* read data buffer for remote service */

  bool_t buf_in_use;
  /* Flag set when buffer in use*/

  bool_t is_deprecated;
  /* flag set if buffer needs to be deprecated */

  olm_read_buf_t *next;
  /* Next node in the linked list*/
}olm_read_buf_t;

/* Data buffer pool */
typedef struct olm_buf_pool_t
{
  uint32_t buf_size;
  /* size of each buffer */

  uint32_t num_bufs;
  /* number of buffers */

  uint32_t prev_num_bufs;
  /* previous number of buffers*/

  void *buf_list_head_ptr;
  /* pointer to buffer array */

  uint32_t buf_list_size;
  /* Number of nodes in the linked list */

}olm_buf_pool_t;

typedef struct olm_active_topo_definition_t
{
  topo_active_module_list_t  active_topo_def;
  /* Active modules created on the remote */

  avcs_module_instance_info_t  *active_module_def;
  /* active remote module definition list */

}olm_active_topo_definition_t;

typedef struct olm_open_cfg_t
{
  capi_v2_olm_open_t olm_open_cfg;
  /* OLM static open configuration */

  olm_open_config_t *dynamic_cfg;
  /* OLM dynamic configuration based on version
   * version 0 : maps to olm_open_config_t */

}olm_open_cfg_t;

typedef struct capi_v2_olm_event_cfg_t
{
  uint32_t enable;
  /* Enable value for the OLM */

  uint32_t kpps;
  /* Current KPPS req for the OLM */

  uint32_t bw;
  /* Current BW req for the OLM */

  uint32_t delay;
  /* Current delay reported by OLM */

}capi_v2_olm_event_cfg_t;

typedef struct capi_v2_olm_process_info_t
{
  uint32_t prefill_read_data_size_per_ch;
  /* Size of pre-filled zeroes to be inserted at the output */

  uint32_t prefill_read_done_size_per_ch;
  /* Size of pre-filled zeroes already inserted at the output */

  uint32 client_input_process_min_buf_size;
  /* Minimum size of input capiv2 buffer across all input ports */

  uint32 client_output_process_min_buf_size;
  /* Minimum size of output capiv2 buffer across all input ports */

  uint32_t wr_olm_proc_size;
  /* Size to be processed at the OLM input */

  uint32_t rd_olm_proc_size;
  /* Size to be processed at the OLM output */

  uint32_t wr_olm_done_size[OLM_MAX_INPUT_PORTS];
  /* Size already processed at the OLM input */

  uint32_t rd_olm_done_size[OLM_MAX_OUTPUT_PORTS];
  /* Size already processed at the OLM output */

  uint32_t in_data_marker;
  /* Mask for input data availability. Used across OLM_MAX_INPUT_PORTS */

  uint32_t prev_in_data_marker;
  /* Store previous state of data availability */

  uint32_t remote_write_buf_mask;
  /* Status of write buffers sent to AP Dynamic Service */

  uint32_t prefill_write_data_size_per_ch[OLM_MAX_INPUT_PORTS];
  /* Specifies the number of zeroes to be inserted per channel to synchronize
	   the primary and secondary data */

  uint32_t prefill_write_done_size_per_ch[OLM_MAX_INPUT_PORTS];
  /* Specifies the number of zeroes inserted per channel to synchronize
	     the primary and secondary data */

  uint32_t olm_input_marker[OLM_MAX_INPUT_PORTS];
  /* Marker used to track transition of the input port data markers */

  capi_v2_buf_t *olm_input[OLM_MAX_INPUT_PORTS];
  capi_v2_buf_t *olm_output[OLM_MAX_OUTPUT_PORTS];
  /* Pointers to the OLM input & output buffers */

  uint32_t  wr_buf_sent[OLM_MAX_INPUT_PORTS];
  /* Number of write buffers sent to Remote Container */

  uint32_t wr_buf_rcvd[OLM_MAX_INPUT_PORTS];
  /* Number of write buffers done received from Remote Container */

  uint32_t rd_buf_sent[OLM_MAX_OUTPUT_PORTS];
  /* Number of read buffers sent to Remote Container */

  uint32_t rd_buf_rcvd[OLM_MAX_OUTPUT_PORTS];
  /* Number of read buffers done received from Remote Container */

  uint32_t process_counter;

}capi_v2_olm_process_info_t;


typedef struct capi_v2_olm_t capi_v2_olm_t;

struct capi_v2_olm_t
{
  /**< The CAPI V2 params */
  capi_v2_vtbl_t  *vtbl_ptr;

  /**< Heap id to allocate memory from */
  QURT_ELITE_HEAP_ID heap_id;

  /**< Logging code */
  capi_v2_log_code_t log_code;

  /**< Mode of module [SYNC or ASYNC]*/
  bool_t sync_mode;

  /**< OLM module open configuration */
  olm_open_cfg_t olm_cfg;

  /**< OLM Process info */
  capi_v2_olm_process_info_t process_info;

  /**< OLM Identifier (combination of dynamic svc ID & OLM IID */
  uint32_t capi_v2_olm_identifier;

  /**< OLM's apr handle*/
  uint32_t apr_handle;

  /**< OLM's apr address*/
  uint16_t apr_addr;

  /**< Remote AP Static Svc APR address*/
  uint16_t remote_svc_apr_addr;

  /**< Remote Proc ID to which this OLM is talking to*/
  uint16_t remote_proc_id;

  /**< Remote Container Module ID */
  uint32_t remote_module_id;

  /**< OLM operating frame size in units */
  uint32_t olm_num_frames;

  /**< Remote container operating frame size in units */
  uint32_t remote_num_frames;

  /**< Remote container identifier */
  uint32_t remote_container_id;

  /**< Remote container port threshold event */
  uint32_t remote_threshold;

  /**< OLM event call back info*/
  capi_v2_event_callback_info_t event_callback_info;

  /**< Create Response from Remote Container */
  ap_create_container_rsp_v1_t create_resp_info;

  /**< Active Remote topology definition */
  olm_active_topo_definition_t  olm_topo_def;

  /**< OLM outband memory information */
  ap_create_container_outband_info_v1_t  outband_mem_info;

  /**< OLM outband memory info pointer */
  void*  outband_mem_info_ptr;

  /**< OLM framework extension info pointer */
  uint32_t * fwk_inf_extn_info_ptr;

  /**< OLM Command handles */
  olm_cmd_handle_t cmd_hndls[CMD_HANDLES_MAX_ARRAY_SIZE];

  /**< Write response queue buffer */
  QURT_ELITE_ALIGN(char wr_rsp_q_buf[OLM_MAX_INPUT_PORTS][QURT_ELITE_QUEUE_GET_REQUIRED_BYTES(OLM_WRITE_BUF_Q_ELEMENTS_MAX)], 8);

  /**< Write response queue pointer */
  qurt_elite_queue_t *wr_rsp_q_ptr[OLM_MAX_INPUT_PORTS];

  /**< Channel for write response queue */
  qurt_elite_channel_t *wr_done_channel_ptr[OLM_MAX_INPUT_PORTS];

  /**< Read response queue buffer */
  QURT_ELITE_ALIGN(char rd_rsp_q_buf[OLM_MAX_OUTPUT_PORTS][QURT_ELITE_QUEUE_GET_REQUIRED_BYTES(OLM_READ_BUF_Q_ELEMENTS_MAX)], 8);

  /**< Read response queue pointer */
  qurt_elite_queue_t *rd_rsp_q_ptr[OLM_MAX_OUTPUT_PORTS];

  /**< Channel for read response queue */
  qurt_elite_channel_t *rd_done_channel_ptr[OLM_MAX_OUTPUT_PORTS];

  /**< Mask indicating if media format was received per input port*/
  uint32_t is_input_mf_rcvd_mask;

  /**< Mask indicating if output media format was received per output port from Remote */
  uint32_t is_output_mf_rcvd_mask;

  /**< OLM Input media format */
  capi_v2_olm_media_fmt_t in_media_fmt[OLM_MAX_INPUT_PORTS];

  /**< OLM Output media format */
  capi_v2_olm_media_fmt_t out_media_fmt[OLM_MAX_OUTPUT_PORTS];

  /**< Buffer pool for write data */
  olm_buf_pool_t write_buf_pool[OLM_MAX_INPUT_PORTS];

  /**< Buffer pool for read data */
  olm_buf_pool_t read_buf_pool[OLM_MAX_OUTPUT_PORTS];

  /**< Pointer to the write buffer being currently used */
  olm_write_buf_t *tmp_wr_data_buf_ptr[OLM_MAX_INPUT_PORTS];

  /**< Pointer to the read buffer being currently used */
  olm_read_buf_t *tmp_rd_data_buf_ptr[OLM_MAX_OUTPUT_PORTS];

  /**< Indicates whether OLM is ready is process (analogous to library instance) */
  bool_t is_olm_instance_created;

  /**< Read buffer delay  */
  uint32_t read_buf_delay_in_us;

  /**< Write buffer delay */
  uint32_t write_buf_delay_in_us;

  /**< Remote Container Delay */
  uint32_t remote_delay_in_us;

  /**< Number of active ports */
  uint32_t num_active_input_ports;

  /**< Number of active output ports */
  uint32_t num_active_output_ports;

  /**< Local token counter for OLM */
  uint32_t olm_local_token;

  /**< OLM event configuration information */
  capi_v2_olm_event_cfg_t olm_event_cfg;

#ifdef OLM_SIM_FILE_DUMP
  FILE *in_file;
  int8_t *p_in;
  FILE *out_file;
  int8_t *p_out;
#endif

#ifdef OLM_DATA_PATH_LATENCY_MEASUREMENT
  capi_v2_olm_data_latency_t profile_data_latency;
#endif
};

/* CAPIv2 OLM Utilities */
capi_v2_err_t capi_v2_olm_process_set_properties(capi_v2_olm_t *me_ptr, capi_v2_proplist_t *props_ptr);
capi_v2_err_t capi_v2_olm_process_get_properties(capi_v2_olm_t *me_ptr, capi_v2_proplist_t *props_ptr);
capi_v2_err_t capi_v2_olm_process_open(capi_v2_olm_t *pMe, capi_v2_olm_open_t *data_ptr);

/* OLM Event Handler Utilities */
void capi_v2_olm_update_raise_kpps_event(capi_v2_olm_t *me_ptr);
void capi_v2_olm_update_raise_bw_event(capi_v2_olm_t *me_ptr);
void capi_v2_olm_update_raise_process_event(capi_v2_olm_t *me_ptr);
void capi_v2_olm_update_raise_delay_event(capi_v2_olm_t *me_ptr);

/* OLM Utilities */
uint32_t get_capi_v2_olm_identifier(capi_v2_olm_t *me_ptr);
capi_v2_err_t capiv2_olm_reset(capi_v2_olm_t *me_ptr);

/* OLM Data Process Utilities */
capi_v2_err_t capi_v2_olm_validate_io_buffers(capi_v2_olm_t *pMe, capi_v2_stream_data_t* input[], capi_v2_stream_data_t* output[]);
void capi_v2_olm_update_process_info(capi_v2_olm_t *pMe , capi_v2_stream_data_t* input[], capi_v2_stream_data_t* output[]);
void capi_v2_olm_determine_operating_rw_frame_size(capi_v2_olm_t *pMe , capi_v2_stream_data_t* input[], capi_v2_stream_data_t* output[]);
bool_t capi_v2_olm_determine_can_process_continue(capi_v2_olm_t *pMe , uint32_t wr_olm_proc_size_inst , uint32_t rd_olm_proc_size_inst);
capi_v2_err_t capi_v2_olm_write_process(capi_v2_olm_t *pMe,
                                        capi_v2_stream_data_t* input[],
                                        capi_v2_buf_t *olm_input[],
                                        uint32_t wr_olm_proc_size,
                                        uint32_t *wr_olm_done_size,
                                        uint32_t input_port_index,
                                        uint32_t output_port_index);
capi_v2_err_t capi_v2_olm_read_process(capi_v2_olm_t *pMe,
                                       capi_v2_stream_data_t* output[],
                                       capi_v2_buf_t *olm_output[],
                                       uint32_t rd_olm_proc_size,
                                       uint32_t *rd_olm_proc_done_size,
                                       uint32_t output_port_index);

bool_t capi_v2_olm_is_supported_media_type(capi_v2_olm_t *me_ptr,
										   capi_v2_data_format_header_t    *data_format_header,
										   capi_v2_standard_data_format_v2_t *pStd);

#ifdef OLM_DATA_PATH_LATENCY_MEASUREMENT
void olm_print_data_latency_statistics(capi_v2_olm_t *pMe);
void insert_random_sample_in_capiv2_input_buffer(capi_v2_olm_t *pMe);
void detect_random_sample_in_capiv2_output_buffer(capi_v2_olm_t *pMe);
void detect_random_sample_olm_read(capi_v2_olm_t *pMe, int8_t *read_data_ptr, uint32_t buffer_size_per_channel);
void detect_random_sample_olm_write(capi_v2_olm_t *pMe, int8_t *write_data_ptr, uint32_t buffer_size_per_channel);
#endif
#ifdef __cplusplus
extern "C" {
#endif //__cplusplus


#ifdef __cplusplus
}
#endif //__cplusplus

#endif // _CAPI_V2_OLM_T_H_

