
/**
@file audproc_topo_olm_handler.h

   Header file for the Offloaded Module Handling API & functions
*/

/*========================================================================

Copyright (c) 2017 Qualcomm Technologies, Inc.  All Rights Reserved.
Confidential and Proprietary - Qualcomm Technologies, Inc.
*/

/*========================================================================
Edit History

when       who          what, where, why
--------   ---          -------------------------------------------------------
9/20/17   bvodapal      Created file.
========================================================================== */

#ifndef AUDPROC_TOPO_OLM_HANDLER_H
#define AUDPROC_TOPO_OLM_HANDLER_H

/*---------------------------------------------------------------------------
* Include Files
* -------------------------------------------------------------------------*/
#include "audproc_topohandler.h"
#ifndef TST_TOPO_LAYER
#ifdef AUDPPSVC_TEST
#include "hexagon_sim_timer.h"
#endif // AUDPPSVC_TEST
#include "adsp_amdb_static.h"
#include "AudDynaPPSvc.h"
#include "Elite_fwk_extns_olm.h"
#include "EliteCmnTopology_db_if.h"
#include "EliteCmnTopology_db.h"
#else
#include "tst_topo_layer.h"
#endif

/*---------------------------------------------------------------------------
 * Definitions and Constants
 * -------------------------------------------------------------------------*/
struct topo_struct;
#define MAX_OLM_MODULES 16
#define MAX_OLM_TOKEN   32

struct olm_info_t
{
	/* OLM modules instance ID*/
	uint16_t olm_iid;

	/* Client ID - unique identifier */
	uint16_t client_id;

	/* Frame size in num frames (us)*/
	uint32_t frame_size;

	/* Scale factor */
	uint32_t scale_factor;

	uint32_t module_index;

	uint32_t is_input_output_realtime;		/**< This variable is set by ASM/ADM to indicate if data
	   	   	   	   	   	   	   	   	   	   	   feeding in and out of  PP service is real-time.
	   	   	   	   	   	   	   	   	   	   	   0 - Either Input or Output is Real-time
	   	   	   	   	   	   	   	   	   	   	   1 - Both Input & Output are Real-time
	   	   	   	   	   	   	   	   	   	   	   2 - Both Input & Output are not Real-time
	   	   	   	   	   	   	   	   	   	   	   In existing use cases, 1 is set in ASM loopback only
	   	   	   	   	   	   	   	   	   	   	   and 2 is set only for NT mode*/

	/* Dynamic service call back pointer */
	olm_resp_callback_info_t  olm_resp_cb_info;

	uint32_t num_fwk_extns;

	capi_v2_framework_extension_id_t *fwk_extn_ptr;
											   
	uint32_t num_active_topology_modules;

	avcs_module_instance_info_t  *active_topo_def;

	/* Contains OLM topology information. */
	elite_cmn_olm_topo_db_entry_t *olm_topo_info_ptr;

	/* Command response queue for commands to offloaded modules */
	qurt_elite_queue_t *cmd_respQ;

};

/*
 * Unit structure of the active token
 * Store the Token and the corresponding response handler
 */
typedef struct olm_active_token_list
{
	uint32_t token_state;    // 0 --> inactive ; non-zero --> active ;
	                         // higher word stores the response handler index
	uint32_t response_handler_index;  // index of the response handle
}olm_active_token_list_t;

/* Structure to store the token information
 * Each token corresponds to a command from the client/dynamic service.
 */
typedef struct olm_token_info
{
	olm_active_token_list olm_active_token_list[MAX_OLM_TOKEN];  // static list of command tokens.
	uint32_t token_counter;          // number of active tokens
	uint32_t current_token;          // points to the current active token
}olm_token_info_t;

/* Structure to store the response results for each OLM module
 * These details are more useful for debugging purpose and is
 * created part of the response handler for each command
 */
typedef struct module_response_info
{
	int32_t response_result;            // remote response
	uint16_t olm_iid;                   // OLM IID
	uint16_t wait_for_response;         // indicate if a response is expected or not
	uint16_t received_response;         // indicate if the response is received or not
	uint16_t reserved;
}module_response_info_t;


/* Structure for the command response handler.
 * This created for each command and a unique token is associated with the same
 */
typedef struct olm_response_handler
{
	elite_msg_any_t response_msg;       // cached command message
	uint32_t token;                     // unique token associated with the command
	uint32_t total_responses;           // indicates the total number of remote responses required for the command
	uint32_t responses_rx;              // indicates the actual responses received.
	int32_t accu_result;                // indicates the accumulated result
	bool_t wait_for_client_to_process_command; // indicates if the client is yet to process the command for local modules
	module_response_info_t rm_rsp_info[MAX_OLM_MODULES];  // module response information
}olm_response_handler_t;

typedef struct topo_olm_response_handler
{
	uint32_t next_index;
	uint32_t num_olm_modules;
	uint32_t wait_for_remote_response;
	uint32_t wait_for_open_response;
	uint32_t wait_for_close_response;
	capi_v2_err_t open_command_response_result;
	olm_token_info_t  token_info;
	olm_response_handler_t *olm_rh_list[MAX_OLM_TOKEN];
}topo_olm_response_handler_t;

// Event handle structure and its methods
typedef struct olm_response_handle
{
   topo_struct *topo_struct_ptr;
   uint32_t module_index;
}olm_response_handle_t;

/*---------------------------------------------------------------------------
 * Function Declarations
 * -------------------------------------------------------------------------*/
ADSPResult topo_olm_release_token(olm_token_info_t *token_info, uint32_t token);
ADSPResult topo_update_olm_token_with_rsph_index(olm_token_info_t *token_info, uint32_t token, uint32_t rsph_index );
bool_t topo_check_if_olm_module(uint16_t pp_obj_id,adsp_amdb_module_handle_info_t *handle_info_ptr);
void topo_olm_response_callback(void *context_ptr, capi_v2_olm_resp_id_t id, capi_v2_olm_resp_info_t *resp_info_ptr, uint16_t olm_iid);
uint32_t topo_olm_generate_token(olm_token_info_t *token_info);
ADSPResult topo_create_command_olm_response_handler( topo_olm_response_handler_t *olm_response_handler , uint32_t *token );
void topo_update_olm_response_handler_module_info(
		topo_olm_response_handler_t *olm_response_handler,
		uint32_t token,
		uint32_t index,
		uint16_t olm_iid);
void topo_update_olm_response_handler(
		topo_olm_response_handler_t *olm_response_handler,
		uint32_t token,
		uint32_t total_num_responses,
		int32_t  accu_result,
		elite_msg_any_t* pMsg,
		bool_t cmd_processing_done);

ADSPResult topo_olm_set_client_command_handling_done(topo_olm_response_handler_t *olm_response_handler, uint32_t token, int32_t result);
void topo_handle_olm_fwk_inf_extension(void *topo_ptr );
#endif //AUDPROC_TOPO_OLM_HANDLER_H
