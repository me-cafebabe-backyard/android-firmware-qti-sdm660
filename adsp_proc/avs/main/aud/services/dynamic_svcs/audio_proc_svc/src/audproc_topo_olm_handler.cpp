/*==========================================================================
@file audproc_topo_olm_handler.cpp

   Source file for the Off loaded Module Handling

Copyright (c) 2017 Qualcomm Technologies, Inc.  All Rights Reserved.
Confidential and Proprietary - Qualcomm Technologies, Inc.
*/

/*===========================================================================
Edit History

when       who       what, where, why
--------   ---       ---------------------------------------------------------
9/20/17    bvodapal    Created file.
=========================================================================== */

/*---------------------------------------------------------------------------
* Include Files
* -------------------------------------------------------------------------*/
#include "audproc_comdef.h"
#include "audproc_topo_olm_handler.h"

/*---------------------------------------------------------------------------
 * Function Declarations
 * -------------------------------------------------------------------------*/
ADSPResult topo_get_olm_token_rsph_index(olm_token_info_t *token_info, uint32_t token, uint32_t *rsph_index );
void topo_release_olm_response_token( topo_olm_response_handler_t *olm_response_handler, uint32_t token );
void topo_update_olm_response_handle_with_response(olm_response_handler_t *rsp_handler_ptr, uint32_t result, int32_t index);

/*---------------------------------------------------------------------------
 * Function Definition
 * -------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------
 * Function Name : topo_get_olm_token_rsph_index
 * Function to get the OLM response handler index given the command token
 * Input  : OLM token list Information , Token
 * Output : Response Handler index
 * Result : Error Code.
 ---------------------------------------------------------------------------*/
ADSPResult topo_get_olm_token_rsph_index(olm_token_info_t *token_info, uint32_t token, uint32_t *rsph_index )
{
	uint32_t index = (token >> 16) & (0x0000FFFF);

	if(index >= MAX_OLM_TOKEN)
	{
		MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "topo_get_olm_token_rsph_index : Failed to map to valid token list index,"
				"Invalid command token  %lu ", token);
		return ADSP_EFAILED;
	}

	/* token is also cached in the token list and should match with the incoming command token */
	if (token!=token_info->olm_active_token_list[index].token_state)
	{
		MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "topo_get_olm_token_rsph_index : Error Token Mismatch  "
				"token list index %lu i-token %lu c-token %lu ",index,
				token, token_info->olm_active_token_list[index].token_state);
		return ADSP_EUNEXPECTED;
	}

	*rsph_index = token_info->olm_active_token_list[index].response_handler_index;

#ifdef PP_OLM_DEBUG
	MSG_2(MSG_SSID_QDSP6, DBG_MED_PRIO, "topo_get_olm_token_rsph_index : token %lu "
			"Response handler Index %lu  ",	token, *rsph_index);
#endif

	return ADSP_EOK;
}

/*------------------------------------------------------------------------------------------
 * Function Name : topo_update_olm_token_with_rsph_index
 * Description : Function to update the OLM response handler with the response handler index
 * Input  : OLM token list Information , Token , Response Handler index
 * Output : OLM token list Information with the response handler index
 * Result : Error Code.
 -------------------------------------------------------------------------------------------*/
ADSPResult topo_update_olm_token_with_rsph_index(olm_token_info_t *token_info, uint32_t token, uint32_t rsph_index )
{
	uint32_t index = (token >> 16) & (0x0000FFFF);
	if(index >= MAX_OLM_TOKEN)
	{
		MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "topo_update_olm_token_with_rsph_index :  Failed to map "
				"to valid index in token list ,Invalid command token  %lu ", token);
		return ADSP_EFAILED;
	}

#ifdef PP_OLM_DEBUG
	MSG_2(MSG_SSID_QDSP6, DBG_MED_PRIO, "topo_update_olm_token_with_rsph_index : "
			"Update token %lu with response handler index %lu", token, rsph_index);
#endif

	token_info->olm_active_token_list[index].response_handler_index = rsph_index;
	return ADSP_EOK;
}

/*--------------------------------------------------------------------------
 * Function Name : topo_olm_release_token
 * Description   : Function to release the token from the token list
 * Input  : OLM token list Information , Token
 * Output : OLM token list Information with token clear from the list
 * Result : Error Code.
 ---------------------------------------------------------------------------*/
ADSPResult topo_olm_release_token(olm_token_info_t *token_info, uint32_t token)
{
	uint32_t index = (token >> 16) & (0x0000FFFF);
	if(index >= MAX_OLM_TOKEN)
	{
		MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "topo_olm_release_token :Failed to map to valid token list index ,"
				" Invalid command token  %lu ", token);
		return ADSP_EFAILED;
	}
	token_info->olm_active_token_list[index].token_state = 0;   // Free the c-token
	token_info->olm_active_token_list[index].response_handler_index = 0;  // Free the response handler index

#ifdef PP_OLM_DEBUG
	MSG_1(MSG_SSID_QDSP6, DBG_MED_PRIO, "topo_olm_release_token : release token %lu ", token);
#endif

	return ADSP_EOK;
}

/*--------------------------------------------------------------------------
 * Function Name : topo_olm_generate_token
 * Description   : Function to generate the unique token for every command
 * Input  : OLM token list Information , Token
 * Output : Unique token
 * Result : Error Code.
 ---------------------------------------------------------------------------*/

ADSPResult topo_olm_generate_token(olm_token_info_t *token_info, uint32_t *ctoken)
{
	token_info->token_counter++;
	uint32_t index = 0;
	*ctoken = 0 ;

	for( index = 0;index < MAX_OLM_TOKEN; index++)
	{
		if(token_info->olm_active_token_list[index].token_state == 0)  // find the index of free token in the token list
		{
			break;
		}
	}

	if(index == MAX_OLM_TOKEN)
	{
		MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "topo_olm_generate_token : Token list is full, "
				"Failed to generate a token for the command  %lu ", index);
		return ADSP_EUNEXPECTED;
	}

	uint32_t token =  (index <<16) + token_info->token_counter;
	token_info->olm_active_token_list[index].token_state = token;
	token_info->current_token = token; // TD : CU
	*ctoken = token;
	MSG_3(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "topo_olm_get_token :  index  %lu token %lu active token state %lu ",
			index, token, token_info->olm_active_token_list[index].token_state);
	return ADSP_EOK;
}

/*--------------------------------------------------------------------------
 * Function Name : topo_olm_response_handler_send_command_ack
 * Description   : Function to send acknowledgment for the given command
 * Input  : OLM response handler
 * Output : none
 * Result : none
 ---------------------------------------------------------------------------*/

void topo_olm_response_handler_send_command_ack(olm_response_handler_t *rsp_handler_ptr)
{
	if(rsp_handler_ptr->response_msg.unOpCode!=0xFFFF)
	{
		elite_svc_send_ack(&rsp_handler_ptr->response_msg, rsp_handler_ptr->accu_result);
	}
	else
	{
		 MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"audproc_svc: No Valid Response Message to send the acknowledgment");
	}
}

/*----------------------------------------------------------------------------------------
 * Function Name : topo_olm_set_client_command_handling_done
 * Description   : Function to update the command response handler with the latest result
 * Input  : OLM response handler,token, command result
 * Output : Response handler updated with the result.
 * Result : error code
 -----------------------------------------------------------------------------------------*/
ADSPResult topo_olm_set_client_command_handling_done(topo_olm_response_handler_t *olm_response_handler, uint32_t token, int32_t result)
{
	uint32_t rsph_index=0;
	ADSPResult error_code = ADSP_EOK;
	ADSPResult temp_result = ADSP_EOK;
	temp_result = topo_get_olm_token_rsph_index(&olm_response_handler->token_info,  token, &rsph_index );

	if(temp_result == ADSP_EOK)
	{
		olm_response_handler_t *rsp_handler_ptr = olm_response_handler->olm_rh_list[rsph_index];
		if(rsp_handler_ptr)
		{
			rsp_handler_ptr->wait_for_client_to_process_command=FALSE;
			rsp_handler_ptr->accu_result |= result;
			if((rsp_handler_ptr->responses_rx==rsp_handler_ptr->total_responses) && (rsp_handler_ptr->total_responses> 0))
			{
				error_code = rsp_handler_ptr->accu_result;
				olm_response_handler->wait_for_remote_response = FALSE;
				//topo_olm_response_handler_send_command_ack(rsp_handler_ptr);
				topo_release_olm_response_token(olm_response_handler, token );
			}
		}
	}
	else
	{
		MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "topo_olm_set_client_command_handling_done : Failed to"
				" get valid response handler for the given command token %lu ", token);
		error_code = temp_result;
	}
	return error_code;
}

/*----------------------------------------------------------------------------------------
 * Function Name : topo_update_olm_response_handler
 * Description   : Function to initialize the the OLM response handler
 * Input  : OLM response handler,token, total number of response, accumulated result.
 * Output : Response handler updated with the result.
 * Result : error code
 -----------------------------------------------------------------------------------------*/
void topo_update_olm_response_handler(
		topo_olm_response_handler_t *topo_olm_response_handler,
		uint32_t token,
		uint32_t total_num_responses,
		int32_t  accu_result,
		elite_msg_any_t* pMsg,
		bool_t client_cmd_handling_done)
{

	uint32_t rsph_index=0;
	ADSPResult temp_result = ADSP_EOK;
	temp_result = 	topo_get_olm_token_rsph_index(&topo_olm_response_handler->token_info, token, &rsph_index );

	if(temp_result == ADSP_EOK)
	{
		olm_response_handler_t *rsp_handler_ptr = topo_olm_response_handler->olm_rh_list[rsph_index];

		if(rsp_handler_ptr)
		{
			topo_olm_response_handler->wait_for_remote_response = FALSE;
			if(total_num_responses > 0)
			{
				rsp_handler_ptr->accu_result = accu_result;
				rsp_handler_ptr->total_responses = total_num_responses;
				if(accu_result==ADSP_EOK)
				{
					if(pMsg!=NULL)
					{
						rsp_handler_ptr->response_msg = *pMsg;
					}
					topo_olm_response_handler->wait_for_remote_response = TRUE;
				}
				else
				{
					rsp_handler_ptr->response_msg.unOpCode = 0xFFFF;
					// Inline Failure indicates the response will be sent inline. No need to wait & acknowledge later based on remote response
				}
				if(client_cmd_handling_done)
				{
					rsp_handler_ptr->wait_for_client_to_process_command=FALSE;
				}
			}
			else
			{
				topo_release_olm_response_token(topo_olm_response_handler, token );
			}

            // if the response for commands to Offload modules is already received, We can free the packet.
			if((rsp_handler_ptr->responses_rx==rsp_handler_ptr->total_responses)
					&& (rsp_handler_ptr->wait_for_client_to_process_command==FALSE)
					&& (total_num_responses > 0))
			{
				//topo_olm_response_handler_send_command_ack(rsp_handler_ptr);
				topo_olm_response_handler->wait_for_remote_response = FALSE;
				topo_release_olm_response_token(topo_olm_response_handler, token );
			}
		}
	}
	else
	{
		MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "topo_update_olm_response_handler : Failed to "
				"get valid response handler for the given command token");
	}
}

/*----------------------------------------------------------------------------------------
 * Function Name : topo_update_olm_response_handler_module_info
 * Description   : Function to update the the OLM response handler module info
 * Input  : OLM response handler,token, index,  OLM IID
 * Output : Response handler updated with the module info.
 * Result : error code
 -----------------------------------------------------------------------------------------*/
void topo_update_olm_response_handler_module_info(
		topo_olm_response_handler_t *olm_response_handler,
		uint32_t token,
		uint32_t index,
		uint16_t olm_iid)
{
	uint32_t rsph_index=0;
	ADSPResult temp_result = ADSP_EOK;
	temp_result = topo_get_olm_token_rsph_index(&olm_response_handler->token_info, token, &rsph_index );
	if(temp_result == ADSP_EOK)
	{
		olm_response_handler_t *rsp_handler_ptr = olm_response_handler->olm_rh_list[rsph_index];
		rsp_handler_ptr->rm_rsp_info[index].olm_iid = olm_iid;
		rsp_handler_ptr->rm_rsp_info[index].wait_for_response = 1;
	}
	else
	{
		MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "topo_update_olm_response_handler_module_info : Failed to "
				"get valid response handler for the given command token");
	}
}

/*----------------------------------------------------------------------------------------
 * Function Name : topo_create_command_olm_response_handler
 * Description   : Function to create the the OLM response handler
 * Input  : OLM response handler
 * Output : Response handler updated with the module info.
 * Result : error code
 -----------------------------------------------------------------------------------------*/
ADSPResult topo_create_command_olm_response_handler( topo_olm_response_handler_t *topo_olm_response_handler , uint32_t *token )
{
	uint32_t curr_index = topo_olm_response_handler->next_index;
	ADSPResult result = ADSP_EOK;

	olm_response_handler_t *cmd_response_handler = (olm_response_handler_t *)qurt_elite_memory_malloc(sizeof(olm_response_handler_t),QURT_ELITE_HEAP_DEFAULT);
	if(cmd_response_handler)
	{
		memset(cmd_response_handler, 0, sizeof(olm_response_handler_t));

		uint32_t temp_token = 0;
		result = topo_olm_generate_token(&topo_olm_response_handler->token_info, &temp_token);
		if(result!=ADSP_EOK)
		{
			MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "topo_create_command_olm_response_handler : Failed to generate token ");
			qurt_elite_memory_free(cmd_response_handler);
			return result;
		}

		topo_olm_response_handler->olm_rh_list[curr_index] = cmd_response_handler;
		cmd_response_handler->response_msg.unOpCode = 0xFFFF;
		cmd_response_handler->responses_rx = 0;
		cmd_response_handler->accu_result = ADSP_EOK;
		cmd_response_handler->token = temp_token;
		cmd_response_handler->total_responses = 0;
		cmd_response_handler->wait_for_client_to_process_command = TRUE;

		topo_update_olm_token_with_rsph_index(&topo_olm_response_handler->token_info,temp_token,curr_index );
		*token = temp_token;
		for (uint32_t i = curr_index + 1 ; i < MAX_OLM_TOKEN; i++)
		{
			if(topo_olm_response_handler->olm_rh_list[i] == NULL )
			{
				topo_olm_response_handler->next_index = i;
				break;
			}
		}
	}
	else
	{
		result = ADSP_ENOMEMORY;
		MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "topo_create_command_olm_response_handler: "
				"failed to allocate OLM command Handler Memory");
	}
	return result;
}

/*----------------------------------------------------------------------------------------
 * Function Name : topo_release_olm_response_token
 * Description   : Function to create the the OLM response handler
 * Input  : OLM response handler,token
 * Output : Response handler updated to free the token & corresponding response handler
 * Result : none
 -----------------------------------------------------------------------------------------*/
void topo_release_olm_response_token( topo_olm_response_handler_t *olm_response_handler, uint32_t token )
{
	uint32_t rsph_index=0;
	ADSPResult temp_result = ADSP_EOK;
	temp_result = topo_get_olm_token_rsph_index(&olm_response_handler->token_info, token, &rsph_index );
	if(temp_result == ADSP_EOK)
	{
		olm_response_handler_t *rsp_handler_ptr = olm_response_handler->olm_rh_list[rsph_index];
		if(rsp_handler_ptr!=NULL)
		{
			olm_response_handler->next_index = rsph_index;
			qurt_elite_memory_free(rsp_handler_ptr);
			olm_response_handler->olm_rh_list[rsph_index] = NULL;
		}
		(void)topo_olm_release_token(&olm_response_handler->token_info, token);
	}
	else
	{
		MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "topo_release_olm_response_token : Failed to "
						"get valid response handler for the given command token");
	}
}

/*----------------------------------------------------------------------------------------
 * Function Name : topo_update_olm_response_handle_with_response
 * Description   :  Function to update the OLM response handler with the result
 * Input  : command response handler,result, index
 * Output : update the response handler with result & response received
 * Result : none
 *-----------------------------------------------------------------------------------------*/

void topo_update_olm_response_handle_with_response(olm_response_handler_t *rsp_handler_ptr, uint32_t result, int32_t index)
{
	CAPI_V2_SET_ERROR(rsp_handler_ptr->accu_result,result );
	rsp_handler_ptr->rm_rsp_info[index].response_result = result;
	rsp_handler_ptr->rm_rsp_info[index].received_response = 1;
	rsp_handler_ptr->responses_rx++;
}

/*----------------------------------------------------------------------------------------
 * Function Name : find_olm_index_in_resp_handler
 * Description   :  Function to find the responder index for the given OLM IID
 * Input  : command response handler,OLM IID
 * Output : index
 * Result : none
 *-----------------------------------------------------------------------------------------*/
int32_t find_olm_index_in_resp_handler(olm_response_handler_t *rsp_handler_ptr, uint16_t olm_iid)
{
	for(int32_t i=0; i < MAX_OLM_MODULES; i++)
	{
		if(rsp_handler_ptr->rm_rsp_info[i].olm_iid == olm_iid)
		{
			return i;
		}
	}
	return -1;
}

/*----------------------------------------------------------------------------------------
 * Function Name : topo_olm_response_callback
 * Description   : callback function handler set to the OLM module.Handles the response
 *                 for the all command sent to the remote service
 * Input  : context, command response ID , response pay-load, OLM IID
 * Output : none
 * Result : none
 *-----------------------------------------------------------------------------------------*/
void topo_olm_response_callback(void *context_ptr, capi_v2_olm_resp_id_t id, capi_v2_olm_resp_info_t *resp_info_ptr, uint16_t olm_iid)
{
	capi_v2_err_t result = CAPI_V2_EOK;
	ADSPResult adsp_result = ADSP_EOK;
	topo_olm_response_handler_t *topo_olm_response_handler = (topo_olm_response_handler_t *) topo_olm_response_get_struct_ptr(context_ptr);
	uint32_t required_payload_size = 0;
	uint32_t rsph_index = 0;
	ADSPResult temp_result = ADSP_EOK;

	temp_result = topo_get_olm_token_rsph_index(&topo_olm_response_handler->token_info, resp_info_ptr->token, &rsph_index );
	if(temp_result != ADSP_EOK)
	{
		MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "topo_olm_response_callback : Failed to "
				"get valid response handler for the given command token");
		return;
	}
	else
	{
		MSG_3(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "topo_olm_response_callback : OLM IID %lu Command ID %lu, "
				"Command token %lu",olm_iid,id,resp_info_ptr->token);
	}

	olm_response_handler_t *rsp_handler_ptr = topo_olm_response_handler->olm_rh_list[rsph_index]; // check for NULL
	if(rsp_handler_ptr==NULL)
	{
		return;
	}

	int32_t index = find_olm_index_in_resp_handler(rsp_handler_ptr,olm_iid);

	if(index < 0)
	{
		return;
		// message for failure/fatal
	}

	switch(id)
	{
	case CAPI_V2_OLM_RESP_OPEN:
	{
		uint32_t open_result = 0;
		required_payload_size = sizeof(capi_v2_olm_open_resp_t);
		if (resp_info_ptr->payload.actual_data_len < required_payload_size){
			CAPI_V2_SET_ERROR(result,CAPI_V2_ENEEDMORE);
			// todo : discuss how to handle this case
			break;
		}
		capi_v2_olm_open_resp_t *open_rsp_ptr = (capi_v2_olm_open_resp_t *)resp_info_ptr->payload.data_ptr;
		olm_open_resp_t *open_dyna_rsp_ptr = (olm_open_resp_t *) (open_rsp_ptr + 1);
		open_result = open_rsp_ptr->result;
		adsp_result = topo_update_olm_active_topo_definition(context_ptr, &open_dyna_rsp_ptr->active_topo_def, olm_iid);
		/*if(adsp_result!=ADSP_EOK)
		{
			open_result = 1;
		}*/
		topo_update_olm_response_handle_with_response(rsp_handler_ptr, open_result, index);

		if((rsp_handler_ptr->responses_rx==rsp_handler_ptr->total_responses) && (rsp_handler_ptr->wait_for_client_to_process_command==FALSE))
		{
			topo_olm_response_handler->wait_for_open_response = 0;
			topo_olm_response_handler->open_command_response_result = rsp_handler_ptr->accu_result;
			topo_release_olm_response_token(topo_olm_response_handler, resp_info_ptr->token );
			topo_handle_olm_fwk_inf_extension(context_ptr);
		}
	}
	break;

	case CAPI_V2_OLM_RESP_CLOSE:
	{
		required_payload_size = sizeof(capi_v2_olm_close_resp_t);
		if (resp_info_ptr->payload.actual_data_len < required_payload_size){
			CAPI_V2_SET_ERROR(result,CAPI_V2_ENEEDMORE);
			// todo : discuss how to handle this case
			break;
		}
		capi_v2_olm_close_resp_t *close_rsp_ptr = (capi_v2_olm_close_resp_t *)resp_info_ptr->payload.data_ptr;

		topo_update_olm_response_handle_with_response(rsp_handler_ptr, close_rsp_ptr->result, index);
		if((rsp_handler_ptr->responses_rx==rsp_handler_ptr->total_responses) && (rsp_handler_ptr->wait_for_client_to_process_command==FALSE))
		{
			topo_olm_response_handler->wait_for_close_response = 0;
			topo_olm_response_handler_send_command_ack(rsp_handler_ptr);
			topo_release_olm_response_token(topo_olm_response_handler, resp_info_ptr->token );
		}
	}
	break;

	case CAPI_V2_OLM_RESP_RUN:
	{
		required_payload_size = sizeof(capi_v2_olm_run_resp_t);
		if (resp_info_ptr->payload.actual_data_len < required_payload_size){
			CAPI_V2_SET_ERROR(result,CAPI_V2_ENEEDMORE);
			// todo : discuss how to handle this case
			break;
		}
		capi_v2_olm_run_resp_t *run_rsp_ptr = (capi_v2_olm_run_resp_t *)resp_info_ptr->payload.data_ptr;

		topo_update_olm_response_handle_with_response(rsp_handler_ptr, run_rsp_ptr->result, index);
		if((rsp_handler_ptr->responses_rx==rsp_handler_ptr->total_responses) && (rsp_handler_ptr->wait_for_client_to_process_command==FALSE))
		{
			topo_update_run_state(context_ptr , rsp_handler_ptr->accu_result);
			topo_olm_response_handler_send_command_ack(rsp_handler_ptr);
			topo_release_olm_response_token(topo_olm_response_handler, resp_info_ptr->token );
		}
	}
	break;

	case CAPI_V2_OLM_RESP_SUSPEND:
	{
		required_payload_size = sizeof(capi_v2_olm_suspend_resp_t);
		if (resp_info_ptr->payload.actual_data_len < required_payload_size){
			CAPI_V2_SET_ERROR(result,CAPI_V2_ENEEDMORE);
			// todo : discuss how to handle this case
			break;
		}
		capi_v2_olm_suspend_resp_t *suspend_rsp_ptr = (capi_v2_olm_suspend_resp_t *)resp_info_ptr->payload.data_ptr;

		topo_update_olm_response_handle_with_response(rsp_handler_ptr, suspend_rsp_ptr->result, index);
		if((rsp_handler_ptr->responses_rx==rsp_handler_ptr->total_responses) && (rsp_handler_ptr->wait_for_client_to_process_command==FALSE))
		{
			topo_olm_response_handler_send_command_ack(rsp_handler_ptr);
			topo_release_olm_response_token(topo_olm_response_handler, resp_info_ptr->token );
		}
	}
	break;

	case CAPI_V2_OLM_RESP_FLUSH:
	{
		required_payload_size = sizeof(capi_v2_olm_flush_resp_t);
		if (resp_info_ptr->payload.actual_data_len < required_payload_size){
			CAPI_V2_SET_ERROR(result,CAPI_V2_ENEEDMORE);
			// todo : discuss how to handle this case
			break;
		}
		capi_v2_olm_flush_resp_t *flush_rsp_ptr = (capi_v2_olm_flush_resp_t *)resp_info_ptr->payload.data_ptr;

		topo_update_olm_response_handle_with_response(rsp_handler_ptr, flush_rsp_ptr->result, index);
		if((rsp_handler_ptr->responses_rx==rsp_handler_ptr->total_responses) && (rsp_handler_ptr->wait_for_client_to_process_command==FALSE))
		{
			topo_olm_response_handler_send_command_ack(rsp_handler_ptr);
			topo_release_olm_response_token(topo_olm_response_handler, resp_info_ptr->token );
		}
	}

	break;

	case CAPI_V2_OLM_RESP_SETPARAM:
	{
		required_payload_size = sizeof(capi_v2_olm_setparam_resp_t);
		if (resp_info_ptr->payload.actual_data_len < required_payload_size){
			CAPI_V2_SET_ERROR(result,CAPI_V2_ENEEDMORE);
			// todo : discuss how to handle this case
			break;
		}
		capi_v2_olm_setparam_resp_t *setparam_rsp_ptr = (capi_v2_olm_setparam_resp_t *)resp_info_ptr->payload.data_ptr;

		topo_update_olm_response_handle_with_response(rsp_handler_ptr, setparam_rsp_ptr->result, index);
		if((rsp_handler_ptr->responses_rx==rsp_handler_ptr->total_responses) && (rsp_handler_ptr->wait_for_client_to_process_command==FALSE))
		{
			topo_olm_response_handler_send_command_ack(rsp_handler_ptr);
			topo_release_olm_response_token(topo_olm_response_handler, resp_info_ptr->token );
		}
	}
	break;

	case CAPI_V2_OLM_RESP_GETPARAM:
	{
		required_payload_size = sizeof(capi_v2_olm_getparam_resp_t);
		if (resp_info_ptr->payload.actual_data_len < required_payload_size){
			CAPI_V2_SET_ERROR(result,CAPI_V2_ENEEDMORE);
			// todo : discuss how to handle this case
			break;
		}
		capi_v2_olm_getparam_resp_t *getparam_rsp_ptr = (capi_v2_olm_getparam_resp_t *)resp_info_ptr->payload.data_ptr;

		topo_update_olm_response_handle_with_response(rsp_handler_ptr, getparam_rsp_ptr->result, index);
		if((rsp_handler_ptr->responses_rx==rsp_handler_ptr->total_responses) && (rsp_handler_ptr->wait_for_client_to_process_command==FALSE))
		{
			topo_olm_response_handler_send_command_ack(rsp_handler_ptr);
			topo_release_olm_response_token(topo_olm_response_handler, resp_info_ptr->token );
		}
	}
	break;
	
	default :
	break;
	}

	return;
}


/*----------------------------------------------------------------------------------------
 * Function Name : topo_check_if_olm_module
 * Description   : Function to check if a module is OLM
 * Input  : amdb module handle
 * Output : status to indicate if the module is OLM or not OLM
 * Result : none
 *-----------------------------------------------------------------------------------------*/

bool_t  topo_check_if_olm_module(uint16_t  obj_id, adsp_amdb_module_handle_info_t *handle_info_ptr)
{
	adsp_amdb_module_handle_info_t *handle_info_temp = handle_info_ptr;
	bool_t is_olm_module =  FALSE;
	if(CAPI_V2 == handle_info_temp->interface_type && (TRUE == is_amdb_module_handle_valid(handle_info_temp)))
	{
		// Query for the optional properties now.
		capi_v2_num_needed_framework_extensions_t num_extensions = { 0 };
		capi_v2_prop_t optional_props[] = {
				{ CAPI_V2_NUM_NEEDED_FRAMEWORK_EXTENSIONS,  { reinterpret_cast<int8_t*>(&num_extensions), 0, sizeof(num_extensions)   }, { FALSE, FALSE, 0} }
		};
		capi_v2_proplist_t optional_proplist = { SIZE_OF_ARRAY(optional_props), optional_props };
		capi_v2_err_t err_code = adsp_amdb_capi_v2_get_static_properties_f(handle_info_temp->h.capi_v2_handle, NULL, &optional_proplist);
		MSG_3(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "P%hX Module with ID 0x%lX needs %d framework extensions", obj_id, handle_info_temp->id1, num_extensions.num_extensions);
		if(CAPI_V2_FAILED(err_code))
		{
			MSG_3(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "P%hX Module with ID 0x%lX failed in getting some optional static properties with %d. Using default values.", obj_id, handle_info_temp->id1, static_cast<int>(err_code));
		}
		if(num_extensions.num_extensions > 0)
		{
			// allocate memory for extention id's based on the num of extentions.
			capi_v2_framework_extension_id_t fwk_extn_ptr[num_extensions.num_extensions];
			// query extension id's from the module
			capi_v2_prop_t static_props_extn[] = {
					{ CAPI_V2_NEEDED_FRAMEWORK_EXTENSIONS, { reinterpret_cast<int8_t *>(fwk_extn_ptr), 0, sizeof(capi_v2_framework_extension_id_t) * num_extensions.num_extensions }, { FALSE, FALSE, 0} },
			};
			//optional_proplist = { SIZE_OF_ARRAY(static_props_extn), static_props_extn };
			optional_proplist.props_num = SIZE_OF_ARRAY(static_props_extn);
			optional_proplist.prop_ptr  = static_props_extn;

			err_code = adsp_amdb_capi_v2_get_static_properties_f(handle_info_temp->h.capi_v2_handle, NULL, &optional_proplist);
			if(CAPI_V2_EOK != err_code)
			{
				MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO," get_static_prop: failed for module_id(0x%lx), prop_id: CAPI_V2_NEEDED_FRAMEWORK_EXTENSIONS, result(%ld)", handle_info_temp->id1, err_code);
			}
			else
			{
				for(uint32_t i = 0; i < num_extensions.num_extensions; i++)
				{
					if(FWK_EXTN_OLM == fwk_extn_ptr[i].id)
					{
						MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO," get_static_prop: module_id(0x%lx) would need extension_id(0x%lx)", handle_info_temp->id1, fwk_extn_ptr[i].id);
						is_olm_module = TRUE;
						return is_olm_module;
					}
				}
			}
		}
	}

	return is_olm_module;
}
