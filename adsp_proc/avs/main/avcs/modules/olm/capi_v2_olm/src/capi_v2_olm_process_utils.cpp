/**
@file capi_v2_olm_process_utils.cpp

@brief This contains wrapper functions for CAPI V2 Off-Loaded Module
       implementation

 */

/*========================================================================
$Header: //components/rel/avs.adsp/2.8/avcs/modules/olm/capi_v2_olm/src/capi_v2_olm_process_utils.cpp#5 $

Edit History

when          who        what, where, why
--------      ---        -------------------------------------------------------
18/2/2018    bvodapal    Created (moved process related utils to this file)

==========================================================================*/

/*-----------------------------------------------------------------------
Copyright (c) 2018 Qualcomm Technologies, Inc.  All Rights Reserved.
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


/*----------------------------------------------------------------------------
 * Function Definitions
 * -------------------------------------------------------------------------*/

/**
 * This function is used to prefill zeroes in the OLM input processing
 *
 * @param[in] pMe, pointer to the CAPI lib
 * @param[in] input[], pointer to CAPI input stream
 * @param[in] olm_input, pointer to OLM write buffer
 * @param[in] wr_olm_proc_size, size of input to be processed
 * @param[in] wr_olm_proc_done_size, pointer to size of input already processed
 * @param[in] input_port_index, port index to be processed
 *
 * @return none
 */
static void capi_v2_olm_write_prefill_data(capi_v2_olm_t *pMe,
                                   capi_v2_stream_data_t* input[],
                                   olm_write_buf_t *olm_input,
                                   uint32_t wr_olm_proc_size,
                                   uint32_t *wr_olm_proc_done_size,
                                   uint32_t input_port_index)
{
  uint32_t size_to_fill_per_ch = 0;

  size_to_fill_per_ch = (pMe->process_info.prefill_write_data_size_per_ch[input_port_index] - pMe->process_info.prefill_write_done_size_per_ch[input_port_index]) ;

  if(size_to_fill_per_ch > ((wr_olm_proc_size - *wr_olm_proc_done_size )/ input[input_port_index]->bufs_num))
  {
    size_to_fill_per_ch = (wr_olm_proc_size - *wr_olm_proc_done_size)/(input[input_port_index]->bufs_num) ;
  }

  if(size_to_fill_per_ch > (olm_input->buf_size_per_ch - olm_input->fill_size_per_ch) )
  {
    size_to_fill_per_ch = (olm_input->buf_size_per_ch - olm_input->fill_size_per_ch);
  }

  if(0 == size_to_fill_per_ch)
  {
    return;
  }

  for(uint32_t i = 0; i < input[input_port_index]->bufs_num; i++)
  {
    memset((olm_input->data_buf_ptr +
        ((i * olm_input->buf_size_per_ch) +  olm_input->fill_size_per_ch)), 0, size_to_fill_per_ch);

    *wr_olm_proc_done_size += size_to_fill_per_ch;
    olm_input->data_write_buf.buf_size += size_to_fill_per_ch;
  }

  olm_input->fill_size_per_ch += size_to_fill_per_ch;
  pMe->process_info.prefill_write_done_size_per_ch[input_port_index] += size_to_fill_per_ch;

}

/**
 * This function is used to prefill zeroes in the OLM output processing
 *
 * @param[in] pMe, pointer to the CAPI lib
 * @param[in] output[], pointer to CAPI input stream
 * @param[in] olm_output, pointer to OLM output buffer
 * @param[in] rd_olm_proc_size, size of output to be processed
 * @param[in] rd_olm_proc_done_size, pointer to size of output already processed
 * @param[in] output_port_index, port index to be processed
 *
 * @return none
 */
static void capi_v2_olm_read_prefill_data(capi_v2_olm_t *pMe,
                                   capi_v2_stream_data_t* output[],
                                   capi_v2_buf_t *olm_output[],
                                   uint32_t rd_olm_proc_size,
                                   uint32_t *rd_olm_proc_done_size,
                                   uint32_t output_port_index)
{
  uint32_t size_to_fill_per_ch = 0;

  size_to_fill_per_ch = (pMe->process_info.prefill_read_data_size_per_ch - pMe->process_info.prefill_read_done_size_per_ch) ;

  if(size_to_fill_per_ch > ((rd_olm_proc_size - *rd_olm_proc_done_size )/ output[output_port_index]->bufs_num))
  {
    size_to_fill_per_ch = (rd_olm_proc_size - *rd_olm_proc_done_size)/ output[output_port_index]->bufs_num;
  }

  if(size_to_fill_per_ch > (olm_output[output_port_index][0].max_data_len - olm_output[output_port_index][0].actual_data_len) )
  {
    size_to_fill_per_ch = (olm_output[output_port_index][0].max_data_len - olm_output[output_port_index][0].actual_data_len);
  }

  if(size_to_fill_per_ch==0)
    return;

  for(uint32_t i = 0; i < output[output_port_index]->bufs_num; i++)
  {
    memset((olm_output[output_port_index][i].data_ptr + olm_output[output_port_index][i].actual_data_len), 0, size_to_fill_per_ch);
    olm_output[output_port_index][i].actual_data_len += size_to_fill_per_ch;
    *rd_olm_proc_done_size += size_to_fill_per_ch;
  }
  pMe->process_info.prefill_read_done_size_per_ch += size_to_fill_per_ch;

}

/**
 * This function is used to handle input data marker transitions in OLM
 * When the non-primary port input data starts flowing, the input buffer is
 * prefilled with primary port input buffer offset. This is needed to maintain
 * data sync between primary and other input ports.
 *
 * @param[in] pMe, pointer to the CAPI lib
 *
 * @return none
 */
void capi_v2_olm_process_data_marker(capi_v2_olm_t *pMe)
{
  if(pMe->process_info.prev_in_data_marker != pMe->process_info.in_data_marker)
  {
    uint32_t updated_mask = (pMe->process_info.prev_in_data_marker) ^ (pMe->process_info.in_data_marker);

    while(updated_mask)
    {
      uint32_t temp_port_id = Q6_R_ct0_R(updated_mask);
      updated_mask ^= (1<<temp_port_id);

      if(temp_port_id >= pMe->num_active_input_ports)
      {
        continue;
      }
      else if(temp_port_id == OLM_PRIMARY_INPUT_PORT) /* Do not check for primary port marker */
      {
        pMe->process_info.olm_input_marker[temp_port_id] = 1;
        continue;
      }
      else
      {
        pMe->process_info.olm_input_marker[temp_port_id] ^= 1; /* Toggle the marker */

        if(pMe->process_info.olm_input_marker[temp_port_id])
        {
          MSG_2(MSG_SSID_QDSP6, DBG_MED_PRIO, "CAPIv2 OLM 0x%8lX: Marker state changed to 1 for port id 0x%x",pMe->capi_v2_olm_identifier, temp_port_id);

          if(NULL != pMe->tmp_wr_data_buf_ptr[OLM_PRIMARY_INPUT_PORT])
          {
            pMe->process_info.prefill_write_data_size_per_ch[temp_port_id] = pMe->tmp_wr_data_buf_ptr[OLM_PRIMARY_INPUT_PORT]->fill_size_per_ch;
            pMe->process_info.prefill_write_done_size_per_ch[temp_port_id] = 0;
          }
          else
          {
            pMe->process_info.prefill_write_data_size_per_ch[temp_port_id] = 0;
            pMe->process_info.prefill_write_done_size_per_ch[temp_port_id] = 0;
          }
        }
        else
        {
          MSG_2(MSG_SSID_QDSP6, DBG_MED_PRIO, "CAPIv2 OLM 0x%8lX: Marker state changed to 0 for port id 0x%x",pMe->capi_v2_olm_identifier, temp_port_id);
          if(pMe->tmp_wr_data_buf_ptr[temp_port_id])
          {

              olm_write_buf_t *write_data_buf_ptr = pMe->tmp_wr_data_buf_ptr[temp_port_id];

              MSG_3(MSG_SSID_QDSP6, DBG_MED_PRIO, "CAPIv2 OLM 0x%8lX: Marker state changed to 0 for port id 0x%x with data per ch = %d",pMe->capi_v2_olm_identifier, temp_port_id, write_data_buf_ptr->fill_size_per_ch);

              ADSPResult result = olm_pack_send_temp_wr_buffer(pMe, temp_port_id); //RR: check result?
              MSG_3(MSG_SSID_QDSP6, DBG_MED_PRIO, "CAPIv2 OLM 0x%8lX: Sent packed buffer for port id %d with result 0x%x",pMe->capi_v2_olm_identifier, temp_port_id, result);
              pMe->tmp_wr_data_buf_ptr[temp_port_id] = NULL;
          }
        }

      }
    }//while(updated_mask)
  } //If marker state has changed.
}

/**
 * This function is used to validate the CAPI buffers received at OLM &
 * update the data marker for the input ports.
 *
 * @param[in] pMe, pointer to the CAPI lib
 * @param[in] input[], pointer to the CAPI inputs
 * @param[in] output[], pointer to the CAPI outputs
 *
 * @return capi_v2_err_t
 */
capi_v2_err_t capi_v2_olm_validate_io_buffers(capi_v2_olm_t *pMe, capi_v2_stream_data_t* input[], capi_v2_stream_data_t* output[])
{
  capi_v2_err_t result = CAPI_V2_EOK;

  pMe->process_info.remote_write_buf_mask = 0;
  pMe->process_info.prev_in_data_marker = pMe->process_info.in_data_marker;

  /* Check validity of input ports */
  for(int port_idx = 0; port_idx < pMe->num_active_input_ports; port_idx++)
  {
    if( NULL == input[port_idx]->buf_ptr )
    {
      olm_set_reset_bitmask(&pMe->process_info.in_data_marker, port_idx, FALSE);
      pMe->process_info.olm_input[port_idx] = NULL;
    }
    else
    {
      /* Set the data marker only if MF is received && the buffer has valid data */
      if((is_olm_mask_set(pMe->is_input_mf_rcvd_mask, port_idx) && input[port_idx]->buf_ptr->actual_data_len > 0))
      {
        QURT_ELITE_ASSERT(pMe->in_media_fmt[port_idx].f.num_channels == input[port_idx]->bufs_num);
        olm_set_reset_bitmask(&pMe->process_info.in_data_marker, port_idx, TRUE);
        pMe->process_info.olm_input[port_idx] = input[port_idx]->buf_ptr;
      }
      else
      {
        olm_set_reset_bitmask(&pMe->process_info.in_data_marker, port_idx, FALSE);
        pMe->process_info.olm_input[port_idx] = NULL;
      }
    }
  }

  capi_v2_olm_process_data_marker(pMe);

  /* Check validity of output ports */
  for(int idx = 0; idx < pMe->num_active_output_ports; idx++)
  {
    if( NULL == output[idx]->buf_ptr )
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: received bad output buffer pointer",
                                             pMe->capi_v2_olm_identifier);
      return(CAPI_V2_EFAILED);
    }
    else
    {
      QURT_ELITE_ASSERT(pMe->out_media_fmt[idx].f.num_channels == output[idx]->bufs_num);
      pMe->process_info.olm_output[idx] =  output[idx]->buf_ptr;
    }
  }

#ifdef OLM_DATA_PATH_LATENCY_MEASUREMENT
  insert_random_sample_in_capiv2_input_buffer(pMe);
#endif

  return result;
}

/**
 * This function is used to update the OLM process info
 * based on the CAPI buffer sizes.
 *
 * @param[in] pMe, pointer to the CAPI lib
 * @param[in] input[], pointer to the CAPI inputs
 * @param[in] output[], pointer to the CAPI outputs
 *
 * @return none
 */
void capi_v2_olm_update_process_info(capi_v2_olm_t *pMe , capi_v2_stream_data_t* input[], capi_v2_stream_data_t* output[])
{
  uint32_t olm_input_frame_size  = pMe->olm_num_frames * (pMe->in_media_fmt[0].f.sampling_rate/1000) * (pMe->in_media_fmt[0].f.bits_per_sample >> 3);
  uint32_t olm_output_frame_size = pMe->olm_num_frames * (pMe->out_media_fmt[0].f.sampling_rate/1000) * (pMe->out_media_fmt[0].f.bits_per_sample >> 3);

  if( (!((pMe->num_active_input_ports > 0) && (pMe->num_active_input_ports <= OLM_MAX_INPUT_PORTS)))
      || (!((pMe->num_active_output_ports > 0) && (pMe->num_active_output_ports <= OLM_MAX_OUTPUT_PORTS))))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: process called with module initialized with invalid ports",
                                           pMe->capi_v2_olm_identifier);
    return;
  }

  uint32_t input_process_buf_size =  pMe->process_info.olm_input[0][0].actual_data_len  ;
  /* OLM processing size is min of input and output actual data len for the all input & output port */
  for(uint32_t port_index =0; port_index < pMe->num_active_input_ports; port_index++ )
  {
    if(NULL == pMe->process_info.olm_input[port_index])
    {
      continue;
    }

    if(pMe->process_info.olm_input[port_index][0].actual_data_len < input_process_buf_size)
    {
      input_process_buf_size =  pMe->process_info.olm_input[port_index][0].actual_data_len ;
    }

    for( uint32_t i = 0; i < input[port_index]->bufs_num; i++)
    {
      pMe->process_info.olm_input[port_index][i].actual_data_len = 0;
    }
  }

  uint32_t wr_olm_proc_size = (input_process_buf_size < olm_input_frame_size) ?  input_process_buf_size : olm_input_frame_size ;


  uint32_t output_process_buf_size = pMe->process_info.olm_output[0][0].max_data_len ;
  for(uint32_t port_index =0; port_index < pMe->num_active_output_ports; port_index++ )
  {
    if(pMe->process_info.olm_output[port_index][0].max_data_len < output_process_buf_size)
    {
      output_process_buf_size =  pMe->process_info.olm_output[port_index][0].max_data_len ;
    }
    for(uint32_t i = 0; i < output[port_index]->bufs_num; i++)
    {
      pMe->process_info.olm_output[port_index][i].actual_data_len = 0;
    }
  }
  uint32_t rd_olm_proc_size = (output_process_buf_size < olm_output_frame_size) ?  output_process_buf_size : olm_output_frame_size ;

  pMe->process_info.client_input_process_min_buf_size = input_process_buf_size;
  pMe->process_info.client_output_process_min_buf_size = output_process_buf_size;

  pMe->process_info.wr_olm_proc_size = wr_olm_proc_size;
  pMe->process_info.rd_olm_proc_size = rd_olm_proc_size;

  pMe->process_info.wr_olm_done_size[0] = 0;
  pMe->process_info.wr_olm_done_size[1] = 0;
  pMe->process_info.rd_olm_done_size[0] = 0;

  //pMe->process_info.prefill_read_data_size_per_ch = 0;
  //pMe->process_info.prefill_read_done_size_per_ch = 0;
}

/**
 * This function is used to determine the OLM read write
 * frame sizes for each process call
 *
 * @param[in] pMe, pointer to the CAPI lib
 * @param[in] input[], pointer to the CAPI inputs
 * @param[in] output[], pointer to the CAPI outputs
 *
 * @return none
 */
void capi_v2_olm_determine_operating_rw_frame_size(capi_v2_olm_t *pMe , capi_v2_stream_data_t* input[], capi_v2_stream_data_t* output[])
{
  uint32_t olm_input_frame_size  = pMe->olm_num_frames * (pMe->in_media_fmt[0].f.sampling_rate/1000) * (pMe->in_media_fmt[0].f.bits_per_sample >> 3);
  uint32_t olm_output_frame_size = pMe->olm_num_frames * (pMe->out_media_fmt[0].f.sampling_rate/1000) * (pMe->out_media_fmt[0].f.bits_per_sample >> 3);

  uint32_t input_process_buf_avail_size =  pMe->process_info.client_input_process_min_buf_size - pMe->process_info.olm_input[0][0].actual_data_len  ;
  /* OLM processing size is min of input and output actual data len for the all input & output port */
  for(uint32_t port_index =0; ((port_index < pMe->num_active_input_ports) && (port_index < OLM_MAX_INPUT_PORTS)); port_index++ )
  {
    if(NULL == pMe->process_info.olm_input[port_index])
    {
      continue;
    }
    if((pMe->process_info.client_input_process_min_buf_size - pMe->process_info.olm_input[port_index][0].actual_data_len) < input_process_buf_avail_size)
    {
      input_process_buf_avail_size =  (pMe->process_info.client_input_process_min_buf_size - pMe->process_info.olm_input[port_index][0].actual_data_len);
    }
  }

  uint32_t wr_olm_proc_size = (input_process_buf_avail_size < olm_input_frame_size) ?  input_process_buf_avail_size : olm_input_frame_size ;


  uint32_t output_process_buf_avail_size = pMe->process_info.client_output_process_min_buf_size  - pMe->process_info.olm_output[0][0].actual_data_len;
  for(uint32_t port_index =0; ((port_index < pMe->num_active_output_ports) && (port_index < OLM_MAX_OUTPUT_PORTS)); port_index++ )
  {
    if((pMe->process_info.client_output_process_min_buf_size  - pMe->process_info.olm_output[port_index][0].actual_data_len) < output_process_buf_avail_size)
    {
      output_process_buf_avail_size =  pMe->process_info.client_output_process_min_buf_size  - pMe->process_info.olm_output[port_index][0].actual_data_len;
    }
  }
  uint32_t rd_olm_proc_size = (output_process_buf_avail_size < olm_output_frame_size) ?  output_process_buf_avail_size : olm_output_frame_size ;

  uint32_t input_media_factor = (pMe->in_media_fmt[0].f.sampling_rate/1000) * (pMe->in_media_fmt[0].f.bits_per_sample >> 3) ;
  uint32_t output_media_factor = (pMe->out_media_fmt[0].f.sampling_rate/1000) * (pMe->out_media_fmt[0].f.bits_per_sample >> 3);

  /*TODO: Change this to uint64_t to accomodate the left shift */
  uint32_t wr_olm_proc_num_units = (wr_olm_proc_size << 10)/input_media_factor;
  uint32_t rd_olm_proc_num_units = (rd_olm_proc_size << 10)/output_media_factor;


  if(wr_olm_proc_num_units!=rd_olm_proc_num_units)
  {
	if(wr_olm_proc_num_units < rd_olm_proc_num_units )
	{
		pMe->process_info.wr_olm_proc_size = wr_olm_proc_size;
		uint32_t temp_rd_samples  = wr_olm_proc_size/(pMe->in_media_fmt[0].f.bits_per_sample >> 3);
		temp_rd_samples =  (uint32_t) ((((float)temp_rd_samples *  (pMe->out_media_fmt[0].f.sampling_rate))/(pMe->in_media_fmt[0].f.sampling_rate)) + 0.5);
		uint32_t temp_rd_size = temp_rd_samples * (pMe->out_media_fmt[0].f.bits_per_sample >> 3);
		temp_rd_size = (temp_rd_size < rd_olm_proc_size) ? temp_rd_size : rd_olm_proc_size;
		pMe->process_info.rd_olm_proc_size = temp_rd_size;
	}
	else
	{
		pMe->process_info.rd_olm_proc_size = rd_olm_proc_size;
		uint32_t temp_wr_samples  = rd_olm_proc_size/(pMe->out_media_fmt[0].f.bits_per_sample >> 3);
		temp_wr_samples =  (uint32_t) ((((float)temp_wr_samples *  (pMe->in_media_fmt[0].f.sampling_rate))/(pMe->out_media_fmt[0].f.sampling_rate)) + 0.5);
		uint32_t temp_wr_size = temp_wr_samples * (pMe->in_media_fmt[0].f.bits_per_sample >> 3);
		temp_wr_size = (temp_wr_size < wr_olm_proc_size) ? temp_wr_size : wr_olm_proc_size;
		pMe->process_info.wr_olm_proc_size = temp_wr_size;
	}

  }
  else
  {
    pMe->process_info.wr_olm_proc_size = wr_olm_proc_size;
    pMe->process_info.rd_olm_proc_size = rd_olm_proc_size;
  }
}

/**
 * This function is used to determine the whether the OLM
 * process loop can continue
 *
 * @param[in] pMe, pointer to the CAPI lib
 * @param[in] wr_olm_proc_size_inst, size of OLM input processing
 * @param[in] rd_olm_proc_size_inst, size of OLM output processing
 *
 * @return TRUE or FALSE
 */
bool_t capi_v2_olm_determine_can_process_continue(capi_v2_olm_t *pMe , uint32_t wr_olm_proc_size_inst , uint32_t rd_olm_proc_size_inst)
{
  uint32_t input_port_index = 0;
  uint32_t output_port_index = 0;
  bool_t is_input_data_available = FALSE;
  bool_t is_output_buffer_space_available = FALSE;
  //static uint32_t process_counter = 0;

  if((pMe->process_info.wr_olm_done_size[0]!=0) || (pMe->process_info.rd_olm_done_size[0]!=0))
  {
	  pMe->process_info.process_counter++;
#ifdef CAPI_V2_OLM_DEBUG
	  MSG_6(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "CAPIv2 OLM 0x%8lX: process stats : "
			  "process counter %lu input process frame size %lu, input data consumed %lu, "
			  "out_buffer_size %lu , Output buffer_fill_size %lu ",
			  pMe->capi_v2_olm_identifier, pMe->process_info.process_counter, wr_olm_proc_size_inst,
			  pMe->process_info.wr_olm_done_size[0], rd_olm_proc_size_inst,
			  pMe->process_info.rd_olm_done_size[0]);
#endif
  }

  if((wr_olm_proc_size_inst==0) && (rd_olm_proc_size_inst==0))
  {
    return FALSE;
  }

  if(pMe->process_info.wr_olm_done_size[input_port_index] < wr_olm_proc_size_inst)
  {
    is_input_data_available = TRUE;
  }
  else if(pMe->process_info.wr_olm_done_size[input_port_index] == wr_olm_proc_size_inst)
  {
    pMe->process_info.wr_olm_done_size[0] = 0;
    pMe->process_info.wr_olm_done_size[1] = 0;
    if(pMe->process_info.olm_input[input_port_index][0].actual_data_len < pMe->process_info.client_input_process_min_buf_size)
    {
      is_input_data_available = TRUE;
    }
  }

  if(pMe->process_info.rd_olm_done_size[output_port_index] < rd_olm_proc_size_inst)
  {
    is_output_buffer_space_available = TRUE;
  }
  else if(pMe->process_info.rd_olm_done_size[output_port_index] == rd_olm_proc_size_inst)
  {
    pMe->process_info.rd_olm_done_size[0] = 0;
    if(pMe->process_info.olm_output[output_port_index][0].actual_data_len < pMe->process_info.client_output_process_min_buf_size)
    {
      is_output_buffer_space_available = TRUE;
    }
  }

  return (is_input_data_available && is_output_buffer_space_available);
}

/**
 * This function is used that handles the write/input processing at
 * the OLM. The appropriate error codes need to be returned to the caller.
 * Any error here, will lead to the module being disabled.
 *
 * @param[in] pMe, pointer to the CAPI lib
 * @param[in] input[], pointer to CAPI input stream
 * @param[in] olm_input[], pointer to OLM write buffer
 * @param[in] wr_olm_proc_size, size of input to be processed
 * @param[in] wr_olm_proc_done_size, pointer to size of input already processed
 * @param[in] input_port_index, port index on input to be processed
 * @param[in] output_port_index, port index on output to be processed
 *
 * @return capi_v2_err_t
 */
capi_v2_err_t capi_v2_olm_write_process(capi_v2_olm_t *pMe,
                                        capi_v2_stream_data_t* input[],
                                        capi_v2_buf_t *olm_input[],
                                        uint32_t wr_olm_proc_size,
                                        uint32_t *wr_olm_done_size,
                                        uint32_t input_port_index,
                                        uint32_t output_port_index)
{
  capi_v2_err_t result = CAPI_V2_EOK;
  ADSPResult      adsp_result    = ADSP_EOK;
  elite_msg_any_t msg;
  olm_write_buf_t *write_data_buf_ptr;

  /*Initialize the write done size to zero*/
  uint32_t wr_size = 0;
  uint32_t wr_done_size = *wr_olm_done_size;
  uint32_t wr_size_per_ch = 0;
  uint32_t buf_avail_size = 0;

  elite_apr_packet_t *data_apr_pkt_ptr = NULL;

  /* write processing */
  while(wr_done_size < wr_olm_proc_size)
  {
    /* if no temporary data buffer, get it from write data queue */
    if(NULL == pMe->tmp_wr_data_buf_ptr[input_port_index])
    {
      /* pop from write data Q */
      while(NULL == pMe->tmp_wr_data_buf_ptr[input_port_index])
      {
        adsp_result = qurt_elite_queue_pop_front(pMe->wr_rsp_q_ptr[input_port_index], (uint64_t*) &msg);
        if (ADSP_EOK != adsp_result)
        {
          MSG_2(MSG_SSID_QDSP6, DBG_LOW_PRIO,"CAPIv2 OLM 0x%8lX: Empty Write Buf Q for index %d",
                                              pMe->capi_v2_olm_identifier, input_port_index);
          return CAPI_V2_EOK;
          /* This is not a fatal error. Simply come back for the next process */
        }

        pMe->process_info.wr_buf_rcvd[input_port_index]++;
        data_apr_pkt_ptr = (elite_apr_packet_t *)msg.pPayload;

        adsp_result = get_wr_data_buf_ptr(pMe, data_apr_pkt_ptr, input_port_index, &pMe->tmp_wr_data_buf_ptr[input_port_index]);
        if(ADSP_FAILED(adsp_result))
        {
          //Error case. We should have proper buffer.
          MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Get "
                                                "Write Buffer ptr failed "
                                                "for index with result 0x%x",
                                                pMe->capi_v2_olm_identifier, input_port_index, adsp_result);
          elite_apr_if_free(pMe->apr_handle, data_apr_pkt_ptr);
          return adsp_result_to_capi_v2_err(adsp_result);
        }

        elite_apr_if_free(pMe->apr_handle, data_apr_pkt_ptr);
        data_apr_pkt_ptr = NULL;

        if(is_deprecated_buffer(pMe->tmp_wr_data_buf_ptr[input_port_index], WRITE_CMD))
        {
          // Delete the buffer
          olm_remove_deprecated_write_buffer(pMe, pMe->tmp_wr_data_buf_ptr[input_port_index], input_port_index);

          // Set temp buffer to NULL
          pMe->tmp_wr_data_buf_ptr[input_port_index] = NULL;
        }
      }

      ap_container_data_write_buffer_v1_t *write_buf_ptr = &pMe->tmp_wr_data_buf_ptr[input_port_index]->data_write_buf;
      write_buf_ptr->buf_size = 0; // resetting fill size to 0
      pMe->tmp_wr_data_buf_ptr[input_port_index]->fill_size_per_ch = 0;

      /* update time stamp */

      //RR: Update TS based on offset = 0 instead of first pop
      memscpy(&write_buf_ptr->flags, sizeof(ap_container_data_flags_t),&input[input_port_index]->flags, sizeof(capi_v2_stream_flags_t));

      if(input[input_port_index]->flags.is_timestamp_valid)
      {
        uint32_t bytes_per_sample = bits_per_sample_2_bytes_per_sample(pMe->in_media_fmt[input_port_index].f.bits_per_sample);
        uint32_t bytes_to_samples_factor = pMe->in_media_fmt[input_port_index].f.num_channels * bytes_per_sample;
        uint64_t timestamp_offset = ((wr_done_size/bytes_to_samples_factor) * 1000000);
        timestamp_offset = timestamp_offset / (pMe->in_media_fmt[input_port_index].f.sampling_rate);

        write_buf_ptr->timestamp = input[input_port_index]->timestamp + timestamp_offset;
#ifdef OLM_DATA_PATH_LATENCY_MEASUREMENT
        //if(olm_input[input_port_index][0].actual_data_len==0)
        {
        	MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Filling Write Buffer with TS %lld at  %lld",
        			pMe->capi_v2_olm_identifier, write_buf_ptr->timestamp, qurt_elite_timer_get_time());
        }
#endif
      }
    }

    /* Copy the input data to write data buffer  */
    if(NULL != pMe->tmp_wr_data_buf_ptr[input_port_index])
    {
      write_data_buf_ptr = pMe->tmp_wr_data_buf_ptr[input_port_index];

      capi_v2_olm_write_prefill_data(pMe,input,write_data_buf_ptr,wr_olm_proc_size, &wr_done_size, input_port_index);

      ap_container_data_write_buffer_v1_t *write_buf_ptr = &write_data_buf_ptr->data_write_buf;

      write_buf_ptr->data_avail = pMe->process_info.in_data_marker; /* This is parsed only for PRIMARY INPUT PORT */

      buf_avail_size = write_data_buf_ptr->data_buf_size - write_buf_ptr->buf_size;
      wr_size = wr_olm_proc_size - wr_done_size;
      wr_size = (wr_size < buf_avail_size) ? wr_size : buf_avail_size;

      wr_size_per_ch = wr_size / pMe->in_media_fmt[input_port_index].f.num_channels;


      for(uint32_t i = 0; i < input[input_port_index]->bufs_num; i++)
      {
        memscpy((write_data_buf_ptr->data_buf_ptr +
            ((i * write_data_buf_ptr->buf_size_per_ch) +  write_data_buf_ptr->fill_size_per_ch)),
                (buf_avail_size / pMe->in_media_fmt[input_port_index].f.num_channels),
                (olm_input[input_port_index][i].data_ptr + olm_input[input_port_index][i].actual_data_len), wr_size_per_ch);

#ifdef OLM_SIM_FILE_DUMP
        if((NULL != pMe->in_file) && (0 == i))
        {
          fwrite((olm_input[port_index][i].data_ptr + olm_input[port_index][i].actual_data_len),sizeof(int8_t), wr_size_per_ch,pMe->in_file);
        }
#endif

        write_buf_ptr->buf_size += wr_size_per_ch;
        olm_input[input_port_index][i].actual_data_len += wr_size_per_ch;
      }

      write_data_buf_ptr->fill_size_per_ch += wr_size_per_ch;

      /* send to remote svc if data buffer is full */
      if(write_data_buf_ptr->data_buf_size == write_buf_ptr->buf_size)
      {
#ifdef OLM_SIM_FILE_DUMP
        if(pMe->in_file)
        {
          //  fwrite(write_data_buf_ptr->data_buf_ptr, sizeof(int8_t), write_data_buf_ptr->data_buf_size,pMe->in_file);
        }
#endif

        //Send the write buffer to Remote Container
        if(ADSP_EOK != (adsp_result = olm_send_data_cmd(pMe, (void *)write_data_buf_ptr, WRITE_CMD)))
        {
          MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Failed to send Write Command for index %d with result 0x%x",
                                                pMe->capi_v2_olm_identifier, input_port_index, adsp_result);
          return adsp_result_to_capi_v2_err(adsp_result);
        }

        pMe->tmp_wr_data_buf_ptr[input_port_index] = NULL;
        olm_set_reset_bitmask(&pMe->process_info.remote_write_buf_mask, input_port_index, TRUE);

        /* If sync mode enabled, wait on read response here */
        if(TRUE == pMe->sync_mode &&
            (pMe->process_info.in_data_marker == pMe->process_info.remote_write_buf_mask))
        {
          uint32_t ch_status = 0;
#ifdef CAPI_V2_OLM_DEBUG
          MSG_1(MSG_SSID_QDSP6, DBG_LOW_PRIO, "CAPIv2 OLM 0x%8lX: In Sync Mode waiting for Read buffer",
                                                pMe->capi_v2_olm_identifier);
#endif
          ch_status = qurt_elite_channel_wait(pMe->rd_done_channel_ptr[output_port_index], RD_CHAN_BIT_MASK);

        }
      }
    }
    wr_done_size =  wr_done_size + wr_size;
  }
  *wr_olm_done_size = wr_done_size;

  return result;
}

/**
 * This function is used that handles the read/output processing at
 * the OLM. The appropriate error codes need to be returned to the caller.
 * Any error here, will lead to the module being disabled.
 *
 * @param[in] pMe, pointer to the CAPI lib
 * @param[in] output[], pointer to CAPI output stream
 * @param[in] olm_output[], pointer to OLM read buffer
 * @param[in] rd_olm_proc_size, size of output to be processed
 * @param[in] rd_olm_proc_done_size, pointer to size of output already processed
 * @param[in] output_port_index, port index on output to be processed
 *
 * @return capi_v2_err_t
 */
capi_v2_err_t capi_v2_olm_read_process(capi_v2_olm_t *pMe,
                                       capi_v2_stream_data_t* output[],
                                       capi_v2_buf_t *olm_output[],
                                       uint32_t rd_olm_proc_size,
                                       uint32_t *rd_olm_proc_done_size,
                                       uint32_t output_port_index)
{

  capi_v2_err_t result = CAPI_V2_EOK;
  ADSPResult      adsp_result         = ADSP_EOK;
  elite_msg_any_t msg;
  olm_read_buf_t *read_data_buf_ptr;
  uint32_t rd_offset = 0;
  uint32_t rd_offset_per_ch;
  uint32_t buf_avail_size = 0;
  bool_t is_out_ts_updated = FALSE;
  uint32_t data_copy_size = 0;
  uint32_t rd_olm_done_size = *rd_olm_proc_done_size;

  if(pMe->process_info.prefill_read_data_size_per_ch > pMe->process_info.prefill_read_done_size_per_ch)
  {
    capi_v2_olm_read_prefill_data(pMe, output, olm_output, rd_olm_proc_size, rd_olm_proc_done_size, output_port_index  );
  }
  rd_olm_done_size = *rd_olm_proc_done_size;

  /* read processing */
  elite_apr_packet_t *data_apr_pkt_ptr = NULL;

  while(rd_olm_done_size < rd_olm_proc_size)
  {
    /* receive the buffer from remote proc */
    /* if no temporary data buffer buffer, get it from read data queue */

    while(NULL == pMe->tmp_rd_data_buf_ptr[output_port_index])
    {
      /* pop from read data Q */
      result = qurt_elite_queue_pop_front(pMe->rd_rsp_q_ptr[output_port_index], (uint64_t*) &msg);
      if (ADSP_EOK != result)
      {
        MSG_2(MSG_SSID_QDSP6, DBG_LOW_PRIO,"CAPIv2 OLM 0x%8lX: Empty Read Buf Q for index %d",
                                            pMe->capi_v2_olm_identifier, output_port_index);
        return CAPI_V2_EOK;
        /* This is not a fatal error. Simply come back for the next process */
        // todo : check if sync mode, retrun error RR: is this valid?
      }
      data_apr_pkt_ptr = (elite_apr_packet_t *)msg.pPayload;

      uint32_t opcode     = elite_apr_if_get_opcode(data_apr_pkt_ptr);
      if(AP_CMDRSP_DATA == opcode)
      {
        pMe->process_info.rd_buf_rcvd[output_port_index]++;
        adsp_result = get_rd_data_buf_ptr(pMe, data_apr_pkt_ptr, output_port_index, &pMe->tmp_rd_data_buf_ptr[output_port_index]);
        if(ADSP_FAILED(adsp_result))
        {
          MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Get "
                                               "Read Buffer ptr failed for index %d with result 0x%x",
                                               pMe->capi_v2_olm_identifier, output_port_index, adsp_result);
          elite_apr_if_free(pMe->apr_handle, data_apr_pkt_ptr);
          return adsp_result_to_capi_v2_err(adsp_result);
        }

        elite_apr_if_free(pMe->apr_handle, data_apr_pkt_ptr);
        data_apr_pkt_ptr = NULL;

        if (pMe->tmp_rd_data_buf_ptr[output_port_index]->data_read_buf.buf_size == 0) // and not depcreated
        {
          /* and send the buffer to remote proc */
          if(ADSP_EOK != (adsp_result = olm_send_data_cmd(pMe,
                                                          (void *)pMe->tmp_rd_data_buf_ptr[output_port_index],
                                                          READ_CMD)))
          {
            MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Failed to send Read Command with result 0x%x",
                                                pMe->capi_v2_olm_identifier, adsp_result);
            return adsp_result_to_capi_v2_err(adsp_result);
          }
          pMe->tmp_rd_data_buf_ptr[output_port_index] = NULL;
        }
        else
        {
          /* resetting read size to 0 */
          pMe->tmp_rd_data_buf_ptr[output_port_index]->rd_offset = 0;
          pMe->tmp_rd_data_buf_ptr[output_port_index]->rd_offset_per_ch = 0;
        }
      }
      else if(AP_CMD_EVENT == opcode)/*  Checking if it is output media format event or not */
      {
        /*
         * Pass the packet Payload to the event handler.
         * This custom event is usually OUTPUT_MEDIA_FORMAT_CHANGE or NUM UNIT FRAMES change event only.
         */
        olm_event_handler(pMe, data_apr_pkt_ptr);
        elite_apr_if_free(pMe->apr_handle, data_apr_pkt_ptr);
        continue;
      }
      else
      {
        MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "CAPIv2 OLM 0x%8lX: Received unexpected command 0x%lx for output index %d",
                                              pMe->capi_v2_olm_identifier, opcode, output_port_index );
        elite_apr_if_free(pMe->apr_handle, data_apr_pkt_ptr);
        return CAPI_V2_EFAILED; //RR: Do we need return error here?
      }
    }

    /* Copy the output data to read data buffer  */
    if(NULL != pMe->tmp_rd_data_buf_ptr[output_port_index])
    {
      uint32_t data_copy_size_per_ch = 0;
      data_copy_size = 0;
      rd_offset = rd_olm_proc_size - rd_olm_done_size;
      /* update output timestamp based if it is not done already */
      if ((FALSE == is_out_ts_updated) && (output[output_port_index]->buf_ptr[0].actual_data_len == 0))
      {
    	  memscpy(&output[output_port_index]->flags,
    			  sizeof(capi_v2_stream_flags_t),
				  &(pMe->tmp_rd_data_buf_ptr[output_port_index]->data_read_buf.flags),
				  sizeof(ap_container_data_flags_t));

    	  if(output[output_port_index]->flags.is_timestamp_valid)
    	  {
    		  uint32_t bytes_per_sample = bits_per_sample_2_bytes_per_sample(pMe->out_media_fmt[output_port_index].f.bits_per_sample);
    		  uint32_t bytes_to_samples_factor = pMe->out_media_fmt[output_port_index].f.num_channels * bytes_per_sample;
    		  uint64_t timestamp_offset = ((rd_offset/bytes_to_samples_factor) * 1000000);
    		  timestamp_offset = timestamp_offset / (pMe->out_media_fmt[output_port_index].f.sampling_rate);

    		  /* Subtract buffer delay in OLM to adjust the timestamp*/
    		  output[output_port_index]->timestamp = (pMe->tmp_rd_data_buf_ptr[output_port_index]->data_read_buf.timestamp + timestamp_offset) -
    				  (pMe->write_buf_delay_in_us + pMe->read_buf_delay_in_us);
    	  }
#ifdef OLM_DATA_PATH_LATENCY_MEASUREMENT
    	  MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Filling Read Buffer with TS %lld at  %lld",
    			  pMe->capi_v2_olm_identifier, output[output_port_index]->timestamp, qurt_elite_timer_get_time());
#endif
    	  is_out_ts_updated = TRUE;
      }

      read_data_buf_ptr = pMe->tmp_rd_data_buf_ptr[output_port_index];
      buf_avail_size = read_data_buf_ptr->data_read_buf.buf_size - read_data_buf_ptr->rd_offset;
      rd_offset = (rd_offset < buf_avail_size) ? rd_offset : buf_avail_size;
      rd_offset_per_ch = rd_offset / pMe->out_media_fmt[output_port_index].f.num_channels;

#ifdef OLM_SIM_FILE_DUMP
      if(pMe->out_file)
      {
        // fwrite(read_data_buf_ptr->data_buf_ptr + read_data_buf_ptr->rd_offset,sizeof(int8_t),rd_offset,pMe->out_file);
      }
#endif
#ifdef OLM_DATA_PATH_LATENCY_MEASUREMENT
      if(read_data_buf_ptr->rd_offset_per_ch==0)
      {
    	  detect_random_sample_olm_read(pMe, read_data_buf_ptr->data_buf_ptr, read_data_buf_ptr->buf_size_per_ch);
      }
#endif

      for(uint32_t i = 0; i < output[output_port_index]->bufs_num; i++)
      {
        data_copy_size_per_ch = memscpy((olm_output[output_port_index][i].data_ptr + olm_output[output_port_index][i].actual_data_len),
                                        (olm_output[output_port_index][i].max_data_len - olm_output[output_port_index][i].actual_data_len),
                                        (read_data_buf_ptr->data_buf_ptr + ((i * read_data_buf_ptr->buf_size_per_ch) +  read_data_buf_ptr->rd_offset_per_ch)),
                                        rd_offset_per_ch);

#ifdef OLM_SIM_FILE_DUMP
        if((NULL != pMe->out_file) && (0 == i))
        {
          fwrite((read_data_buf_ptr->data_buf_ptr + read_data_buf_ptr->rd_offset),sizeof(int8_t),rd_offset_per_ch,pMe->out_file);
        }
#endif
        data_copy_size +=data_copy_size_per_ch;
        read_data_buf_ptr->rd_offset += data_copy_size_per_ch;
        olm_output[output_port_index][i].actual_data_len += data_copy_size_per_ch;
      }
      read_data_buf_ptr->rd_offset_per_ch += data_copy_size_per_ch;

        /* send to remote svc if data buffer is emptied */
        if(read_data_buf_ptr->data_read_buf.buf_size == read_data_buf_ptr->rd_offset)
        {
          if(is_deprecated_buffer(read_data_buf_ptr, READ_CMD))
          {
            // Remove the buffer from buffer list
            olm_remove_deprecated_read_buffer(pMe, read_data_buf_ptr, output_port_index);

            // Set temp buffer to NULL
            pMe->tmp_rd_data_buf_ptr[output_port_index] = NULL;
          }
        else
        {
          if(ADSP_EOK != (adsp_result = olm_send_data_cmd(pMe, (void *)read_data_buf_ptr, READ_CMD)))
          {
            MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: Failed to send Read Command for index %d with result 0x%x",
                  pMe->capi_v2_olm_identifier, output_port_index, adsp_result);
            return adsp_result_to_capi_v2_err(adsp_result);

          }
          pMe->tmp_rd_data_buf_ptr[output_port_index] = NULL;
        }
      }
    }
    rd_olm_done_size = rd_olm_done_size + data_copy_size;
  }
  *rd_olm_proc_done_size = rd_olm_done_size;

  return result;
}


