/**
@file capi_v2_olm_process_utils.cpp

@brief This contains wrapper functions for CAPI V2 Off-Loaded Module
       implementation

 */

/*========================================================================
$Header: //components/rel/avs.adsp/2.8/avcs/modules/olm/capi_v2_olm/src/capi_v2_olm_profile.cpp#1 $

Edit History

when          who        what, where, why
--------      ---        -------------------------------------------------------
22/3/2018    bvodapal    Created

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
#include "olm_utils.h"

/*----------------------------------------------------------------------------
 * Defines
 * -------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
 * Function Definitions
 * -------------------------------------------------------------------------*/
#ifdef OLM_DATA_PATH_LATENCY_MEASUREMENT

void olm_print_data_latency_statistics(capi_v2_olm_t *pMe)
{

	MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: data_latency_marker_based, "
			"Capiv2 Input to OLM Write send : Max Latency %ld Min Latency  %lld ",
			pMe->capi_v2_olm_identifier,
			pMe->profile_data_latency.max_latency_stats[0],
			pMe->profile_data_latency.min_latency_stats[0]);

	MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: data_latency_marker_based, "
				"Capiv2 Input to OLM Read  : Max Latency %ld Min Latency  %lld ",
				pMe->capi_v2_olm_identifier,
				pMe->profile_data_latency.max_latency_stats[1],
				pMe->profile_data_latency.min_latency_stats[1]);

	MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: data_latency_marker_based, "
				"Capiv2 Input to Capiv2 Output send : Max Latency %ld Min Latency  %lld ",
				pMe->capi_v2_olm_identifier,
				pMe->profile_data_latency.max_latency_stats[2],
				pMe->profile_data_latency.min_latency_stats[2]);

	uint32_t framesize_in_samples = pMe->olm_num_frames * (pMe->in_media_fmt[0].f.sampling_rate/1000);

	MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: data_latency_buffer_based, "
					"framesize input %ld , Max data buffered  %lld ", pMe->capi_v2_olm_identifier,
					framesize_in_samples, pMe->profile_data_latency.max_samples_buffered);

}


void detect_random_sample_olm_read(capi_v2_olm_t *pMe, int8_t *read_data_ptr, uint32_t buffer_size_per_channel)
{
	uint32_t index =(pMe->profile_data_latency.find_sample_index_olm_read %100);
	uint32_t sample_value = pMe->profile_data_latency.sample_value[index];
	uint32_t sample_index = 0;
	uint32_t sample_found = 0;
	uint64_t timer_val = 0;
	uint64_t inst_latency =0;
	uint16_t *data_ptr = (uint16_t*)read_data_ptr;
	if ((data_ptr==NULL)||(sample_value ==0))
		return ;

	uint32_t num_out_sample = buffer_size_per_channel/(pMe->out_media_fmt[0].f.bits_per_sample/8);
	do
	{
		sample_found = 0;
		while(sample_index < num_out_sample)
		{
			if(data_ptr[sample_index] == sample_value)
			{
				sample_found = 1;
				sample_index++;
				timer_val = qurt_elite_timer_get_time();
				inst_latency = timer_val - pMe->profile_data_latency.timer_value[index];
				MSG_4(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: data_latency_marker_based, "
						"Finding sample in OLM Read Buffer with sample value %ld at  %lld : time_diff_CI_OR  %lld",
						pMe->capi_v2_olm_identifier, sample_value, timer_val,inst_latency);

				if(inst_latency > pMe->profile_data_latency.max_latency_stats[1])
					pMe->profile_data_latency.max_latency_stats[1] = inst_latency;
				else if (inst_latency > pMe->profile_data_latency.min_latency_stats[1])
					pMe->profile_data_latency.min_latency_stats[1] = inst_latency;
				break;
			}
			else
			{
				sample_index++;
			}
		}
		if(sample_found)
		{
			pMe->profile_data_latency.find_sample_index_olm_read++;
			index = (pMe->profile_data_latency.find_sample_index_olm_read %100);
			sample_value = pMe->profile_data_latency.sample_value[index];
			if (sample_value ==0)
				sample_found = 0;
		}
	}
	while(sample_found);
}




void detect_random_sample_olm_write(capi_v2_olm_t *pMe, int8_t *write_data_ptr, uint32_t buffer_size_per_channel)
{
	uint32_t index = (pMe->profile_data_latency.find_sample_index_olm_write %100);
	uint32_t sample_value = pMe->profile_data_latency.sample_value[index];
	uint32_t sample_index = 0;
	uint32_t sample_found = 0;
	uint64_t timer_val = 0;
	uint64_t inst_latency =0;
	uint16_t *data_ptr = (uint16_t*)write_data_ptr;

	if ((data_ptr==NULL) ||(sample_value ==0))
		return ;

	uint32_t num_out_sample = buffer_size_per_channel/(pMe->in_media_fmt[0].f.bits_per_sample/8);
	do
	{
		sample_found = 0;
		while(sample_index < num_out_sample)
		{
			if(data_ptr[sample_index] == sample_value)
			{
				sample_found = 1;
				sample_index++;
				timer_val = qurt_elite_timer_get_time();
				inst_latency = timer_val - pMe->profile_data_latency.timer_value[index];
				MSG_4(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: data_latency_marker_based, "
						"Finding sample in OLM Write Buffer with sample value %ld at  %lld : time_diff_CI_OW  %lld",
						pMe->capi_v2_olm_identifier, sample_value, timer_val,inst_latency);

				if(inst_latency > pMe->profile_data_latency.max_latency_stats[0])
					pMe->profile_data_latency.max_latency_stats[0] = inst_latency;
				else if (inst_latency > pMe->profile_data_latency.min_latency_stats[0])
					pMe->profile_data_latency.min_latency_stats[0] = inst_latency;
				break;
			}
			else
			{
				sample_index++;
			}
		}
		if(sample_found)
		{
			pMe->profile_data_latency.find_sample_index_olm_write++;
			index = (pMe->profile_data_latency.find_sample_index_olm_write %100);
			sample_value = pMe->profile_data_latency.sample_value[index];
			if (sample_value ==0)
				sample_found = 0;
		}
	}
	while(sample_found);

}



void detect_random_sample_in_capiv2_output_buffer(capi_v2_olm_t *pMe)
{
	uint32_t index = (pMe->profile_data_latency.find_sample_index % 100);
	uint32_t sample_value = pMe->profile_data_latency.sample_value[index];
	uint32_t sample_index = 0;
	uint32_t sample_found = 0;
	uint64_t timer_val = 0;
	uint32_t port_idx = 0;
	uint64_t inst_latency =0;

	uint16_t *data_ptr = (uint16_t*)pMe->process_info.olm_output[port_idx][0].data_ptr;

	if ((sample_value ==0) || (data_ptr ==NULL))
		return ;

	uint32_t num_out_sample = pMe->process_info.olm_output[port_idx][0].actual_data_len/(pMe->out_media_fmt[0].f.bits_per_sample/8);
	do
	{
		sample_found = 0;
		while(sample_index < num_out_sample)
		{
			if(data_ptr[sample_index] == sample_value)
			{
				sample_found = 1;
				sample_index++;
				timer_val = qurt_elite_timer_get_time();
				inst_latency = timer_val - pMe->profile_data_latency.timer_value[index];

				MSG_4(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: data_latency_marker_based, "
						"Finding sample in Read Buffer with sample %ld at  %lld : time_diff_CI_CO  %lld",
						pMe->capi_v2_olm_identifier, sample_value, timer_val,
						inst_latency);

				if(inst_latency > pMe->profile_data_latency.max_latency_stats[2])
					pMe->profile_data_latency.max_latency_stats[2] = inst_latency;
				else if (inst_latency > pMe->profile_data_latency.min_latency_stats[2])
					pMe->profile_data_latency.min_latency_stats[2] = inst_latency;

				break;
			}
			else
			{
				sample_index++;
			}
		}
		if(sample_found)
		{
			pMe->profile_data_latency.find_sample_index++;
			index = (pMe->profile_data_latency.find_sample_index % 100);
			sample_value = pMe->profile_data_latency.sample_value[index];
			if (sample_value ==0)
				sample_found = 0;
		}
	}
	while(sample_found);

	uint32_t input_samples_consumed = pMe->process_info.olm_input[0][0].actual_data_len/(pMe->in_media_fmt[0].f.bits_per_sample/8);
	uint32_t output_samples_delivered = pMe->process_info.olm_output[0][0].actual_data_len/(pMe->out_media_fmt[0].f.bits_per_sample/8);

	pMe->profile_data_latency.sample_consumed += input_samples_consumed;
	pMe->profile_data_latency.samples_delivered += output_samples_delivered;

	uint64_t max_buffer_samples =  (uint32_t)(pMe->profile_data_latency.sample_consumed - pMe->profile_data_latency.samples_delivered );
	if(max_buffer_samples > pMe->profile_data_latency.max_samples_buffered)
	{
		pMe->profile_data_latency.max_samples_buffered = max_buffer_samples;
	}

	MSG_4(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: data_latency_sample_buffer_based, "
							"Sample consumed %ld Samples Delivered  %lld Samples Buffered : %lld",
							pMe->capi_v2_olm_identifier, pMe->profile_data_latency.sample_consumed,
							pMe->profile_data_latency.samples_delivered, max_buffer_samples);

}

void insert_random_sample_in_capiv2_input_buffer(capi_v2_olm_t *pMe)
{
	uint32_t index = (pMe->profile_data_latency.fill_sample_index % 100);;
	uint32_t sample_value = 0;
	uint16_t *data_ptr = (uint16_t*)pMe->process_info.olm_input[0][0].data_ptr;

	memset(data_ptr, 0, pMe->process_info.olm_input[0][0].actual_data_len);

	if((data_ptr!=NULL))
	{
		if(data_ptr[0]==0)
		{
			if(index == 0)
			{
				sample_value = pMe->profile_data_latency.sample_value[99] + 10;
			}
			else
			{
				sample_value = pMe->profile_data_latency.sample_value[index-1] + 10;
			}
			pMe->profile_data_latency.sample_value[index] = sample_value;
			pMe->profile_data_latency.timer_value[index] = qurt_elite_timer_get_time();
			data_ptr[0] = (uint16_t)sample_value;
			pMe->profile_data_latency.fill_sample_index++;
			MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: data_latency_marker_based,"
					"Filling Write Buffer with sample %ld at  %lld",
					pMe->capi_v2_olm_identifier, sample_value, pMe->profile_data_latency.timer_value[index]);

		}
		else
		{
			index = (pMe->profile_data_latency.fill_sample_index - 1) %100;
			if(pMe->profile_data_latency.sample_value[index] == data_ptr[0])
			{
				pMe->profile_data_latency.timer_value[index] = qurt_elite_timer_get_time();
				MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"CAPIv2 OLM 0x%8lX: data_latency_marker_based,"
						"Filling Re-Write Buffer with sample %ld at  %lld",
						pMe->capi_v2_olm_identifier, sample_value, pMe->profile_data_latency.timer_value[index]);
			}
		}
	}
}
#endif
