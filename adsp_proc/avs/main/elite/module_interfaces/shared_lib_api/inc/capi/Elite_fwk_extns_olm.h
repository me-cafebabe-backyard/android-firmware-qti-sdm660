#ifndef ELITE_FWK_EXTNS_OLM_H
#define ELITE_FWK_EXTNS_OLM_H

/* ======================================================================== */
/**
@file Elite_fwk_extns_olm.h

@brief framework extensions header file for OLM (OffLoad Module)

  This file defines a framework extensions and corresponding private properties
  needed by the OLM.
 */
/*===========================================================================
NOTE: The @brief description above does not appear in the PDF. The description
      after the Edit History below is pulled in by the Elite_CAPIv2_mainpage.
      dox file and is displayed in the PDF. Contact Tech Pubs for assistance.
===========================================================================*/
/* =========================================================================
  Copyright (c) 2017 Qualcomm Technologies, Inc. (QTI) All rights reserved.
  Qualcomm Technologies Proprietary and Confidential.
  ========================================================================== */
/* =========================================================================
                             Edit History

   when          who        what, where, why
   --------       ---       ---------------------------------------------------
   11/6/2017    bvodapal    adding version details
   9/18/2017    sranumul    Create File
   ========================================================================= */

#include "Elite_CAPI_V2_types.h"
#include "qurt_elite.h"
#include "EliteCmnTopology_db_if.h"
#include "EliteAprIf.h"
#include "EliteMem_Util.h"


/** @cond OEM_only */

/** @addtogroup capiv2_ext_offload_module
@{ */

/** Unique identifier used to represent the Offload Module (OLM) framework
    extension.

    This extension support the following parameters:
     - #CAPI_V2_PARAM_ID_OLM_OPEN
     - #CAPI_V2_PARAM_ID_OLM_CLOSE
     - #CAPI_V2_PARAM_ID_OLM_RUN
     - #CAPI_V2_PARAM_ID_OLM_SETPARAM
     - #CAPI_V2_PARAM_ID_OLM_GETPARAM
     - #CAPI_V2_PARAM_ID_OLM_FLUSH
     - #CAPI_V2_PARAM_ID_OLM_SUSPEND
     - #CAPI_V2_PARAM_ID_OLM_RESP_PKT
     - #CAPI_V2_PARAM_ID_OLM_GET_FWK_INF_EXTN_INFO
     - #CAPI_V2_PARAM_ID_SET_OLM_FWK_EXTN_MODULE_CONFIG
     - #CAPI_V2_PARAM_ID_SET_OLM_INF_EXTN_MODULE_CONFIG
 */
#define FWK_EXTN_OLM 0x0001296F

/** Valid response IDs that are passed to the framework.
 */
enum capi_v2_olm_resp_id_t
{
  CAPI_V2_OLM_RESP_OPEN,     /**< Response to a #CAPI_V2_PARAM_ID_OLM_OPEN
                                  command. */
  CAPI_V2_OLM_RESP_CLOSE,    /**< Response to a #CAPI_V2_PARAM_ID_OLM_CLOSE
                                  command. */
  CAPI_V2_OLM_RESP_RUN,      /**< Response to a #CAPI_V2_PARAM_ID_OLM_RUN
                                  command. */
  CAPI_V2_OLM_RESP_FLUSH,    /**< Response to a #CAPI_V2_PARAM_ID_OLM_FLUSH
                                  command. */
  CAPI_V2_OLM_RESP_SUSPEND,  /**< Response to a #CAPI_V2_PARAM_ID_OLM_SUSPEND
                                  command. */
  CAPI_V2_OLM_RESP_SETPARAM, /**< Response to a #CAPI_V2_PARAM_ID_OLM_SETPARAM
                                  command. */
  CAPI_V2_OLM_RESP_GETPARAM, /**< Response to a #CAPI_V2_PARAM_ID_OLM_GETPARAM
                                  command. */
};

typedef struct capi_v2_olm_resp_info_t capi_v2_olm_resp_info_t;

/** Generic response container for the OLM to communicate with the framework.
 */
struct capi_v2_olm_resp_info_t
{
  uint32_t token;
  /**< Unique token associated with the command. */

  capi_v2_port_info_t port_info;
  /**< Port Information of the module. */

  capi_v2_buf_t  payload;
  /**< Payload data of the response.

       Possible payloads:
       - capi_v2_olm_open_resp_t
       - capi_v2_olm_open_resp_t
       - capi_v2_olm_close_resp_t
       - capi_v2_olm_setparam_resp_t
       - capi_v2_olm_getparam_resp_t
       - capi_v2_olm_flush_resp_t
       - capi_v2_olm_suspend_resp_t
       - capi_v2_olm_run_resp_t @tablebulletend */
};

/** Callback function handler that the OLM uses to communicate a command
    response to the framework.

    The framework shares the function handler information during the Open
    command.

    @param[in] cntx_ptr       Pointer to the client handle.
    @param[in] id             ID of the command.
    @param[in] resp_info_ptr  Pointer to the response payload.
    @param[in] olm_iid        Instance ID of the offloaded module instance.

    @returns
    None.

    @dependencies
    None.
 */
typedef  void (*olm_resp_callback_fn_ptr)(void *cntx_ptr, capi_v2_olm_resp_id_t id, capi_v2_olm_resp_info_t *resp_info_ptr, uint16_t olm_iid);

typedef struct olm_resp_callback_info_t olm_resp_callback_info_t;

/** Callback function handler for the OLM to communicate a command response to
    the frameworks. This function handler information is shared by a framework
    during the #CAPI_V2_PARAM_ID_OLM_OPEN command.
*/
struct olm_resp_callback_info_t
{
  olm_resp_callback_fn_ptr cb_fn_ptr;
  /**< Function handler defined and shared by the framework. */

  void *context_ptr;
  /**< Context pointer of the framework to be shared to OLM. The OLM caches the
       same pointer during the response callback. */
};


/** ID of the open configuration parameter used by offload modules to create
    both a remote service and a sub-graph on a remote processor.

    @msgpayload{capi_v2_olm_open_t}
    @table{weak__capi__v2__olm__open__t}

    @par Data payload (olm_open_config_t)
    @table{weak__olm__open__config__t}
 */
#define CAPI_V2_PARAM_ID_OLM_OPEN 0x00012970

typedef struct olm_open_config_t olm_open_config_t;
/** @weakgroup weak_olm_open_config_t
@{ */
/* Payload structure for CAPI_V2_PARAM_ID_OLM_OPEN parameter.
 */
struct olm_open_config_t
{
   uint16_t olm_iid;
   /**< Unique OLM instance ID that is assigned while registering a topology. */

   uint16_t client_id;
   /**< Unique identifier of the client. */

  uint32_t frame_size;
  /**< Operating frame size (in frames) of the framework. */

  uint32_t scale_factor;
  /**< Specifies the priority of offload processing.

       @values Currently, only 1 */

  uint32_t is_input_output_realtime;
  /**< Specifies whether the input and output are connected to a real-time
       source or sink.

       Bit 0 configures the input, and bit 1 configures the output.

       @values{for each bit}
       - 0 -- Non-real-time
       - 1 -- Real-time @tablebulletend */

  olm_resp_callback_info_t  olm_resp_cb_info;
  /**< Call back function handler information for the framework. */

  elite_cmn_olm_topo_db_entry_t *olm_topo_info_ptr;
  /**< Sub-graph information to be processed remotely by the OLM. */

  qurt_elite_queue_t *framework_respQ;
  /**< Command response queue of the framework where the OLM sends the
       response.*/

};
/** @} *//* end_weakgroup weak_olm_open_config_t */

typedef struct capi_v2_olm_open_t capi_v2_olm_open_t;
/** @weakgroup weak_capi_v2_olm_open_t
@{ */
struct capi_v2_olm_open_t
{
   uint16_t version;
   /**< Version details for the configuration parameter.

        @values 0 -- Maps to olm_open_config_t */

  uint16_t payload_size;
  /**< Size of the configuration payload. The size depends on the version
       details.

       Immediately following this structure is the data that corresponds to
       open command configuration. */

  uint32_t token;
   /**< Unique token associated with the command. */

};
/** @} *//* end_weakgroup weak_capi_v2_olm_open_t */


/** ID of the parameter used to send a Close command to offloaded modules.
    This command closes both the remote processing instances and the modules
    that are being processed remotely.

    @msgpayload{capi_v2_olm_close_t}
    @table{weak__capi__v2__olm__close__t}
 */
#define CAPI_V2_PARAM_ID_OLM_CLOSE 0x00012971

typedef struct capi_v2_olm_close_t capi_v2_olm_close_t;
/** @weakgroup weak_capi_v2_olm_close_t
@{ */
/* Payload structure for CAPI_V2_PARAM_ID_OLM_CLOSE parameter.
 */
struct capi_v2_olm_close_t
{
    uint16_t version;
    /**< Version details for the configuration parameter.

         @values 0 -- No specific payload extension (dynamic payload size
         is 0) */

    uint16_t payload_size;
    /**< Size of the configuration payload. The size depends on the version
         details.

         Immediately following this structure is the data that corresponds to
         close command configuration. */

    uint32_t token;
    /**< Unique token associated with the command. @newpagetable */
};
/** @} *//* end_weakgroup weak_capi_v2_olm_close_t */


/** ID of the parameter used to send a Run command to offloaded modules.

    @msgpayload{capi_v2_olm_run_t}
    @table{weak__capi__v2__olm__run__t}
*/
#define CAPI_V2_PARAM_ID_OLM_RUN 0x00012972

typedef struct capi_v2_olm_run_t capi_v2_olm_run_t;
/** @weakgroup weak_capi_v2_olm_run_t
@{ */
/* Payload structure for CAPI_V2_PARAM_ID_OLM_RUN parameter.
 */
struct capi_v2_olm_run_t
{
    uint16_t version;
    /**< Version details for the configuration parameter.

         @values 0 -- No specific payload extension (dynamic payload size
         is 0) */

    uint16_t payload_size;
    /**< Size of the configuration payload. The size depends on the version
         details.

         Immediately following this structure is the data that corresponds to
         run command configuration. */

    uint32_t token;
    /**< Unique token associated with the command. */
};
/** @} *//* end_weakgroup weak_capi_v2_olm_run_t */


/** ID of the parameter used to send module calibration to offloaded modules.

    @msgpayload{capi_v2_olm_setparam_t}
    @table{weak__capi__v2__olm__setparam__t} @newpage
 */
#define CAPI_V2_PARAM_ID_OLM_SETPARAM 0x00012973

typedef struct capi_v2_olm_setparam_t capi_v2_olm_setparam_t;
/** @weakgroup weak_capi_v2_olm_setparam_t
@{ */
/* Payload structure for CAPI_V2_PARAM_ID_OLM_SETPARAM parameter.
 */
struct capi_v2_olm_setparam_t
{
  uint32_t token;
  /**< Unique token associated with the command. */

  uint32_t mode;
  /**< Indicates the version of the payload, depending on whether the input
       payload is asm_stream_param_data_v3_t or asm_stream_param_data_v2_t.

       @values
       - 0 -- GIVEN_INSTANCE [asm_stream_param_data_v3_t]
       - 1 -- ZERO_INSTANCE  [asm_stream_param_data_v2_t]

       For more information on the input payloads, see
       @xrefcond{Q3,80-NF772-1,80-NA609-1}. */
  /* adsp_asm_stream_commands.h */

  elite_mem_shared_memory_map_t bufferMemNode;
  /**< Shared memory details for the out-of-band command. */

  uint32_t payload_size;
  /**< Size of the calibration data. */

  void *payload_ptr;
  /**<  Pointer to the calibration data. */

};
/** @} *//* end_weakgroup weak_capi_v2_olm_setparam_t */


/** ID of the parameter used to get calibration information for offloaded
    modules.

    @msgpayload{capi_v2_olm_getparam_t}
    @table{weak__capi__v2__olm__getparam__t}
*/
#define CAPI_V2_PARAM_ID_OLM_GETPARAM 0x00012974

typedef struct capi_v2_olm_getparam_t capi_v2_olm_getparam_t;
/** @weakgroup weak_capi_v2_olm_getparam_t
@{ */
/* Payload structure for CAPI_V2_PARAM_ID_OLM_GETPARAM parameter.
 */
struct capi_v2_olm_getparam_t
{
  uint32_t token;
  /**< Unique token associated with the command. */

  uint32_t mode;
  /**< Indicates the version of the payload, depending on whether the input
       payload is asm_stream_param_data_v3_t or asm_stream_param_data_v2_t.

       @values
       - 0 -- GIVEN_INSTANCE [asm_stream_param_data_v3_t]
       - 1 -- ZERO_INSTANCE  [asm_stream_param_data_v2_t]

       For more information on the input payloads, see
       @xrefcond{Q3,80-NF772-1,80-NA609-1}. *//* Audio API Spec*/

  uint32_t module_id;
  /**< Valid ID of the offloaded module. */

  uint16_t instance_id;
  /**< Valid ID of the offloaded module instance. */

  uint32_t param_id;
  /**< Valid ID of the parameter. */

  elite_mem_shared_memory_map_t bufferMemNode;
  /**< Shared memory information for the out-of-band command. */

  uint32_t max_data_size;
  /**< Maximum size of the parameter data (in bytes) based on the
       module_id/param_id combination. */

  uint32_t *param_size;
  /**< Pointer to the actual size of the parameter data based on the
       module_id/param_id combination. */

  void *payload;
  /**< Pointer to the virtual address of the data payload. */
};
/** @} *//* end_weakgroup weak_capi_v2_olm_getparam_t */


/** ID of the parameter used to send a Flush command to offloaded modules.

    @msgpayload{capi_v2_olm_flush_t}
    @table{weak__capi__v2__olm__flush__t} @newpage
*/
#define CAPI_V2_PARAM_ID_OLM_FLUSH 0x00012975

typedef struct capi_v2_olm_flush_t capi_v2_olm_flush_t;
/** @weakgroup weak_capi_v2_olm_flush_t
@{ */
/* Payload structure for CAPI_V2_PARAM_ID_OLM_FLUSH parameter.
 */
struct capi_v2_olm_flush_t
{
    uint16_t version;
    /**< Version details for the configuration parameter.

         @values 0 -- No specific payload extension (dynamic payload size
         is 0) */

    uint16_t payload_size;
    /**< Size of the configuration payload. The size depends on the version
         details.

         Immediately following this structure is the data that corresponds to
         flush command configuration. */

    uint32_t token;
    /**< Unique token associated with the command. */
};
/** @} *//* end_weakgroup weak_capi_v2_olm_flush_t */


/** ID of the parameter used to send a Suspend command to offloaded modules.

    @msgpayload{capi_v2_olm_suspend_t}
    @table{weak__capi__v2__olm__suspend__t}
*/
#define CAPI_V2_PARAM_ID_OLM_SUSPEND 0x00012976

typedef struct capi_v2_olm_suspend_t capi_v2_olm_suspend_t;
/** @weakgroup weak_capi_v2_olm_suspend_t
@{ */
/* Payload structure for CAPI_V2_PARAM_ID_OLM_SUSPEND parameter.
 */
struct capi_v2_olm_suspend_t
{
    uint16_t version;
    /**< Version details for the configuration parameter.

         @values 0 -- No specific payload extension (dynamic payload size
         is 0) */

    uint16_t payload_size;
    /**< Size of the configuration payload. The size depends on the version
         details.

         Immediately following this structure is the data that corresponds to
         suspend command configuration. */

    uint32_t token;
    /**< Unique token associated with the command. */
};
/** @} *//* end_weakgroup weak_capi_v2_olm_suspend_t */


/** ID of the parameter used to send a remote response to offloaded modules.

    @msgpayload{capi_v2_olm_resp_pkt_t}
    @table{weak__capi__v2__olm__resp__pkt__t}
*/
#define CAPI_V2_PARAM_ID_OLM_RESP_PKT 0x00012977

typedef struct capi_v2_olm_resp_pkt_t capi_v2_olm_resp_pkt_t;
/** @weakgroup weak_capi_v2_olm_resp_pkt_t
@{ */
/* Payload structure for CAPI_V2_PARAM_ID_OLM_RESP_PKT parameter.
 */
struct capi_v2_olm_resp_pkt_t
{
  elite_apr_packet_t *pkt_ptr;   /**< APR packet of the response. */
};
/** @} *//* end_weakgroup weak_capi_v2_olm_resp_pkt_t */


/** Information about an interface being queried.
 */
struct capiv2_fwk_extn_desc_t // to check : if we need to have this in CAPIV2 API
{
  uint32_t id;
  /**< Valid ID of the interface extension being queried. The client must
       provide this value. */

  uint32_t module_id;
   /**< Valid ID of the module that requested the framework extension. */

   uint32_t instance_id;
   /**< Valid ID of the module instance. */

  capi_v2_buf_t capabilities;
  /**< Buffer containing a structure that can be used to specify the
       module requirements from the framework.

       The structure is defined in the framework extension file. @newpagetable */
};

/** Contains framework or interface extension information.
 */
struct topo_olm_extn_info_t
{
    uint32_t status;
    /**< Status of the request to get framework or interface extension
         information.

         @values Non-zero indicates a failure to get the status */

    uint32_t num_inf_extn;
    /**< Number of interface extensions supported by the remote offloaded
         module. */

    uint32_t inf_extn_payload_size;
    /**< Size of the interface extension information payload. */

    uint32_t num_fwk_extn;
    /**< Number of framework extensions required by the remote offloaded module.

         Only the framework extension that cannot be supported by the remote
         container/processor is communicated to the offoad module. */

    uint32_t fwk_extn_payload_size;
    /**< Size of the framework extension information payload. */
};


/** ID of the parameter used to get the framwork interface extension
    information from the offloaded module.

    @msgpayload{capi_v2_olm_get_fwk_inf_extn_info_t}
    @table{weak__capi__v2__olm__get__fwk__inf__extn__info__t} @newpage
 */
#define CAPI_V2_PARAM_ID_OLM_GET_FWK_INF_EXTN_INFO 0x00012978

typedef struct capi_v2_olm_get_fwk_inf_extn_info_t capi_v2_olm_get_fwk_inf_extn_info_t;
/** @weakgroup weak_capi_v2_olm_get_fwk_inf_extn_info_t
@{ */
/* Payload structure for CAPI_V2_PARAM_ID_GET_FWK_INF_EXTN_INFO parameter.
 */
struct capi_v2_olm_get_fwk_inf_extn_info_t
{
  void *data_ptr;
  /**< Pointer to the framework or interface extension information stored by
       the offloaded module. */
};
/** @} *//* end_weakgroup weak_capi_v2_olm_get_fwk_inf_extn_info_t */


/** ID of the parameter used to send framework extension relevant configuration
    to an offloaded module.

    The OLM sends the same configuration to the module that is being processed
    on a remote module. No response is expected for this configuration.

    @msgpayload{capi_v2_olm_set_fwk_extn_module_config_t}
    @table{weak__capi__v2__olm__set__fwk__extn__module__config__t}
 */
#define CAPI_V2_PARAM_ID_SET_OLM_FWK_EXTN_MODULE_CONFIG 0x00012979

typedef struct capi_v2_olm_set_fwk_extn_module_config_t capi_v2_olm_set_fwk_extn_module_config_t;
/** @weakgroup weak_capi_v2_olm_set_fwk_extn_module_config_t
@{ */
/* Payload structure for CAPI_V2_PARAM_ID_SET_FWK_EXTN_MODULE_CONFIG parameter.
 */
struct capi_v2_olm_set_fwk_extn_module_config_t
{
    uint32_t fwk_extn_id;
    /**< ID of the framework extension. */

    uint32_t payload_size;
    /**< Size of the configuration data. */

    void *payload_ptr;
    /**<  Pointer to the data. */
};
/** @} *//* end_weakgroup weak_capi_v2_olm_set_fwk_extn_module_config_t */


/** ID of the parameter used to send interface extension configuration
    information to an offloaded module.

    The OLM sends the same configuration to the module that is being processed
    on a remote module. No response is expected for this configuration.

    @msgpayload{capi_v2_olm_set_inf_extn_module_config_t}
    @table{weak__capi__v2__olm__set__inf__extn__module__config__t} @newpage
 */
#define CAPI_V2_PARAM_ID_SET_OLM_INF_EXTN_MODULE_CONFIG 0x0001297A

typedef struct capi_v2_olm_set_inf_extn_module_config_t capi_v2_olm_set_inf_extn_module_config_t;
/** @weakgroup weak_capi_v2_olm_set_inf_extn_module_config_t
@{ */
/* Payload structure for CAPI_V2_PARAM_ID_SET_FWK_EXTN_MODULE_CONFIG parameter.
 */
struct capi_v2_olm_set_inf_extn_module_config_t
{
    uint32_t inf_extn_id;
    /**< ID of the interface extension. */

    uint32_t payload_size;
      /**< Size of the configuration data. */

      void *payload_ptr;
      /**<  Pointer to the data. */
};
/** @} *//* end_weakgroup weak_capi_v2_olm_set_inf_extn_module_config_t */

/** Contains definitions for an active module.
 */
struct capi_v2_olm_active_topo_definition_t
{
    uint32_t num_active_modules;
    /**< Number of modules loaded successfully in the topology.*/

    uint32_t payload_size;
    /**< Size of the payload that corresponds to the module list. */

    avcs_module_instance_info_t *active_module_list;
    /**< Pointer to the active module list. */
};

typedef struct olm_open_resp_t olm_open_resp_t;

/** Contains the topology definition in the response to a
    #CAPI_V2_PARAM_ID_OLM_OPEN command.
 */
struct olm_open_resp_t
{
  capi_v2_olm_active_topo_definition_t  active_topo_def;
  /**< Active topology definition for the offloaded module. @newpagetable */
};

typedef struct capi_v2_olm_open_resp_t capi_v2_olm_open_resp_t;

/** Response payload for a #CAPI_V2_PARAM_ID_OLM_OPEN command.
 */
struct capi_v2_olm_open_resp_t
{
    uint16_t version;
    /**< Version details for the configuration parameter.

         @values 0 -- Maps to olm_open_resp_t */

    uint16_t payload_size;
    /**< Size of the configuration payload. The size depends on the version
         details.

         Immediately following this structure is the data that corresponds to
         the response. */

    uint32_t result;
    /**< Status of the command. */
};

typedef struct capi_v2_olm_close_resp_t capi_v2_olm_close_resp_t;

/** Response payload for a #CAPI_V2_PARAM_ID_OLM_CLOSE command.
 */
struct capi_v2_olm_close_resp_t
{
    uint16_t version;
    /**< Version details for the configuration parameter.

         @values 0 -- No specific dynamic response (extended payload size
         is 0). */

    uint16_t payload_size;
    /**< Size of the configuration payload. The size depends on the version
         details.

         Immediately following this structure is the data that corresponds to
         the response. */

    int32_t result;
    /**< Status of the command. */
};

typedef struct capi_v2_olm_setparam_resp_t capi_v2_olm_setparam_resp_t;

/** Response payload for a #CAPI_V2_PARAM_ID_OLM_SETPARAM command.
 */
struct capi_v2_olm_setparam_resp_t
{
    uint16_t version;
    /**< Version details for the configuration parameter.

         @values 0 -- No specific dynamic response (extended payload size
         is 0). */

    uint16_t payload_size;
    /**< Size of the configuration payload. The size depends on the version
         details.

         Immediately following this structure is the data that corresponds to
         the response. */

    int32_t result;
    /**< Status of the command. @newpagetable */
};

typedef struct capi_v2_olm_getparam_resp_t capi_v2_olm_getparam_resp_t;

/** Response payload for a #CAPI_V2_PARAM_ID_OLM_GETPARAM command.
 */
struct capi_v2_olm_getparam_resp_t
{
    uint16_t version;
    /**< Version details for the configuration parameter.

         @values 0 -- No specific dynamic response (extended payload size
         is 0). */

    uint16_t payload_size;
    /**< Size of the configuration payload. The size depends on the version
         details.

         Immediately following this structure is the data that corresponds to
         the response. */

    int32_t result;
    /**< Status of the command. */

    uint32_t data_size;
  /**< Maximum size of the parameter data (in bytes) based on the
       module_id/param_id combination. */

    void *data_ptr;
  /**< Pointer to the framework or interface extension information stored by
       the offloaded module. */
};

typedef struct capi_v2_olm_flush_resp_t capi_v2_olm_flush_resp_t;

/** Response payload for a #CAPI_V2_PARAM_ID_OLM_FLUSH command.
 */
struct capi_v2_olm_flush_resp_t
{
    uint16_t version;
    /**< Version details for the configuration parameter.

         @values 0 -- No specific dynamic response (extended payload size
         is 0). */

    uint16_t payload_size;
    /**< Size of the configuration payload. The size depends on the version
         details.

         Immediately following this structure is the data that corresponds to
         the response. */

    int32_t result;
    /**< Status of the command. */
};

typedef struct capi_v2_olm_suspend_resp_t capi_v2_olm_suspend_resp_t;

/** Response payload for a #CAPI_V2_PARAM_ID_OLM_SUSPEND command.
 */
struct capi_v2_olm_suspend_resp_t
{
    uint16_t version;
    /**< Version details for the configuration parameter.

         @values 0 -- No specific dynamic response (extended payload size
         is 0). */

    uint16_t payload_size;
    /**< Size of the configuration payload. The size depends on the version
         details.

         Immediately following this structure is the data that corresponds to
         the response. */

    int32_t result;
    /**< Status of the command. @newpagetable */
};

typedef struct capi_v2_olm_run_resp_t capi_v2_olm_run_resp_t;

/** Response to a #CAPI_V2_PARAM_ID_OLM_RUN command.
 */
struct capi_v2_olm_run_resp_t
{
    uint16_t version;
    /**< Version details for the configuration parameter.

         @values 0 -- No specific dynamic response (extended payload size
         is 0). */

    uint16_t payload_size;
    /**< Size of the configuration payload. The size depends on the version
         details.

         Immediately following this structure is the data that corresponds to
         the response. */

    int32_t result;
    /**< Status of the command. @newpagetable */
};

/** @} *//* end_addtogroup capiv2_ext_offload_module */

/** @endcond *//* OEM_only */

#endif /* #ifndef ELITE_FWK_EXTNS_OLM_H */
