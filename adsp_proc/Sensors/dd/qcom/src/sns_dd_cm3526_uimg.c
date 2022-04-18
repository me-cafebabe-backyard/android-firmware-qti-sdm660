/*******************************************************************************
* Copyright (c) 2016, Capella Microsystems, Inc.
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*     1. Redistributions of source code must retain the above copyright
*      notice, this list of conditions and the following disclaimer.
*     2. Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimer in the
*       documentation and/or other materials provided with the distribution.
*     3. Neither the name of Capella Microsystems, Inc. nor the
*       names of its contributors may be used to endorse or promote products
*       derived from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*******************************************************************************/

/*==============================================================================    

EDIT HISTORY FOR FILE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.

when         who     what, where, why
----------   ---     -----------------------------------------------------------
04/29/2016   JH      Fix memory leakage issue in get_data callback
04/12/2016   JH      Porting from dd_vendor_1_uimg.c
==============================================================================*/

/*============================================================================
INCLUDE FILES
============================================================================*/

#include "sns_dd_cm3526.h"

/*============================================================================
STATIC VARIABLE DEFINITIONS
============================================================================*/

/*============================================================================
STATIC FUNCTION PROTOTYPES
============================================================================*/
sns_ddf_driver_if_s CM3526_DD_IF =
{
	.init = &sns_dd_cm3526_init,
	.get_data = &sns_dd_cm3526_get_data,
	.set_attrib = &sns_dd_cm3526_set_attrib, 
	.get_attrib = &sns_dd_cm3526_get_attrib,
	.handle_timer = &sns_dd_cm3526_handle_timer,
	.handle_irq = &sns_dd_cm3526_handle_irq,
	.reset = &sns_dd_cm3526_reset,
	.run_test = &sns_dd_cm3526_run_test,
	.enable_sched_data = &sns_dd_cm3526_enable_sched_data,
	.probe = &sns_dd_cm3526_probe,
	.trigger_fifo_data = NULL
};

/*============================================================================
LOCAL FUNCTION PROTOTYPES
============================================================================*/


void sns_dd_cm3526_log_sensor_data(sns_ddf_sensor_e sensor, uint64_t timestamp, int32_t data0, int32_t data1, int32_t data2)
{
	sns_log_sensor_data_pkt_s *log_struct_ptr;
	sns_err_code_e err_code;

	CM3526_DEBUG_MSG_0(HIGH, "sns_dd_cm3526_log_sensor_data: Enter");

	/* Allocate log packet */
	if ((err_code = sns_logpkt_malloc(
			CM3526_LOG_PACKET,
			sizeof(sns_log_sensor_data_pkt_s),
			(void**)&log_struct_ptr)) != SNS_SUCCESS)
	{
		// Do nothing
		CM3526_DEBUG_MSG_1(ERROR, "sns_dd_cm3526_log_sensor_data: sns_logpkt_malloc failed with error code: %d", err_code);
	}
	else
	{
		log_struct_ptr->version   = SNS_LOG_SENSOR_DATA_PKT_VERSION;
		log_struct_ptr->sensor_id = sensor;
		log_struct_ptr->vendor_id = SNS_DDF_VENDOR_CAPELLA;

		log_struct_ptr->timestamp = timestamp;

		log_struct_ptr->num_data_types = 3;
		log_struct_ptr->data[0]   = data0;
		log_struct_ptr->data[1]   = data1;
		log_struct_ptr->data[2]   = data2;		

		/* Commit log (also frees up the log packet memory) */
		sns_logpkt_commit(CM3526_LOG_PACKET, log_struct_ptr);
	}

	CM3526_DEBUG_MSG_0(HIGH, "sns_dd_cm3526_log_sensor_data: Exit");
}

void sns_dd_cm3526_uvs_report_data(sns_dd_cm3526_t *state, sns_ddf_sensor_data_s *sensor_data, sns_ddf_memhandler_s *memhandler)
{
	sns_ddf_status_e          status;
	sns_ddf_sensor_sample_s*  sensor_sample;
	uint16_t                  uva_data;
	uint16_t                  dummy_data;
	uint16_t                  uvb_data;
	uint16_t                  uvcomp1_data;
	uint16_t                  uvcomp2_data;
	int64_t                   UVAComp;
	int64_t                   UVBComp;
	q16_t                     UVA;
	q16_t                     UVB;
	q16_t                     UVI;	

	CM3526_DEBUG_MSG_0(HIGH, "sns_dd_cm3526_uvs_report_data: Enter");

	/* allocate memory for sensor sub-samples */
	sensor_sample = sns_ddf_memhandler_malloc_ex(
			memhandler,
			3 * sizeof(sns_ddf_sensor_sample_s),
			state->smgr_handle);
	if (sensor_sample == NULL)
	{
		CM3526_DEBUG_MSG_0(ERROR, "sns_dd_cm3526_uvs_report_data: failed to allocate sensor_sample");
		return;
	} 

	/* read UVA data */
	status = sns_dd_cm3526_reg_read(state->port_handle, SNS_DD_CM3526_UVA_DATA_REG, &uva_data);
	if (status != SNS_DDF_SUCCESS)
	{
		CM3526_DEBUG_MSG_0(ERROR, "sns_dd_cm3526_uvs_report_data: failed to read UVA_DATA_REG");
		return;
	}
	CM3526_DEBUG_MSG_1(HIGH,"sns_dd_cm3526_uvs_report_data: UVA data = %d", uva_data);

	/* read Dummy data */
	status = sns_dd_cm3526_reg_read(state->port_handle, SNS_DD_CM3526_DUMMY_DATA_REG, &dummy_data);
	if (status != SNS_DDF_SUCCESS)
	{
		CM3526_DEBUG_MSG_0(ERROR, "sns_dd_cm3526_uvs_report_data: failed to read DUMMY_DATA_REG");
		return;
	}
	CM3526_DEBUG_MSG_1(HIGH,"sns_dd_cm3526_uvs_report_data: Dummy data = %d", dummy_data);	
	
	// Read UVB data
	status = sns_dd_cm3526_reg_read(state->port_handle, SNS_DD_CM3526_UVB_DATA_REG, &uvb_data);
	if (status != SNS_DDF_SUCCESS)
	{
		CM3526_DEBUG_MSG_0(ERROR, "sns_dd_cm3526_uvs_report_data: failed to read UVB_DATA_REG");
		return;
	}
	CM3526_DEBUG_MSG_1(HIGH,"sns_dd_cm3526_uvs_report_data: UVB data = %d", uvb_data);
	
	// Read UVCOMP1 data
	status = sns_dd_cm3526_reg_read(state->port_handle, SNS_DD_CM3526_UVCOMP1_DATA_REG, &uvcomp1_data);
	if (status != SNS_DDF_SUCCESS)
	{
		CM3526_DEBUG_MSG_0(ERROR, "sns_dd_cm3526_uvs_report_data: failed to read UVCOMP1_DATA_REG");
		return;
	}		
	CM3526_DEBUG_MSG_1(HIGH,"sns_dd_cm3526_uvs_report_data: UVCOMP1 data = %d", uvcomp1_data);

	// Read UVCOMP2 data
	status = sns_dd_cm3526_reg_read(state->port_handle, SNS_DD_CM3526_UVCOMP2_DATA_REG, &uvcomp2_data);
	if (status != SNS_DDF_SUCCESS)
	{
		CM3526_DEBUG_MSG_0(ERROR, "sns_dd_cm3526_uvs_report_data: failed to read UVCOMP2_DATA_REG");
		return;
	}		
	CM3526_DEBUG_MSG_1(HIGH,"sns_dd_cm3526_uvs_report_data: UVCOMP2 data = %d", uvcomp2_data);	

	// Calculate UVA, UVB and UVI
	UVAComp = 100 * (uva_data - dummy_data) - 250 * (uvcomp1_data - dummy_data) - 250 * (uvcomp2_data - dummy_data);
	if (UVAComp < 0)
	{
		UVAComp = 0;
	}
	UVBComp = 100 * (uvb_data - dummy_data) - 275 * (uvcomp1_data - dummy_data) - 275 * (uvcomp2_data - dummy_data);
	if (UVBComp < 0)
	{
		UVBComp = 0;
	}	
	UVA = FX_FLTTOFIX_Q16(UVAComp * 186 / 10000000.0);
	UVB = FX_FLTTOFIX_Q16(UVBComp * 420 / 10000000.0);
	UVI = FX_CONV_Q16((UVAComp * 110 + UVBComp * 125 + 10000000) / 20000000, 0);
	
	/* create a report */
	sensor_data->samples     = sensor_sample;
	sensor_data->num_samples = 3;

	sensor_data->samples[0].sample = UVA;
	sensor_data->samples[0].status = SNS_DDF_SUCCESS;
	sensor_data->samples[1].sample = UVB;
	sensor_data->samples[1].status = SNS_DDF_SUCCESS;
	sensor_data->samples[2].sample = UVI;
	sensor_data->samples[2].status = SNS_DDF_SUCCESS;	
	
	sns_dd_cm3526_log_sensor_data(SNS_DDF_SENSOR_ULTRA_VIOLET, sensor_data->timestamp, UVA, UVB, UVI);

	CM3526_DEBUG_MSG_0(HIGH, "sns_dd_cm3526_uvs_report_data: Exit");
}

/*===========================================================================

FUNCTION:   sns_dd_cm3526_handle_irq

===========================================================================*/
/** 
* @brief Called in response to an interrupt for this driver.
*  
* @note This function will be called within the context of the SMGR task, 
*       *not* the ISR. 
*
* @param[in] dd_handle  Handle to a driver instance. 
* @param[in] gpio_num   GPIO number that triggered this interrupt.
* @param[in] timestamp  Time at which interrupt happened.
*/
/*=========================================================================*/
void sns_dd_cm3526_handle_irq
(
	sns_ddf_handle_t  dd_handle,
	uint32_t          gpio_num,
	sns_ddf_time_t    timestamp
)
{

}

/*===========================================================================

FUNCTION:   sns_dd_cm3526_handle_timer

===========================================================================*/
/**
* @brief Called when the timer set by this driver has expired. This must be 
*        the callback function submitted when initializing a timer.
*  
* @note This will be called within the context of the Sensors Manager task.
* 
* @param[in] dd_handle  Handle to a driver instance.
* @param[in] arg        The argument submitted when the timer was set. 
* 
*/
/*=========================================================================*/
void sns_dd_cm3526_handle_timer 
(
	sns_ddf_handle_t dd_handle, 
	void* arg
)
{

}

/*===========================================================================

FUNCTION:   sns_dd_cm3526_get_data

===========================================================================*/
/** 
* @brief Retrieves a single set of sensor data.
*  
* @param[in]  dd_handle    Handle to a driver instance.
* @param[in]  sensors      List of sensors for which data is requested.
* @param[in]  num_sensors  Number of elements in @a sensors.
* @param[in]  memhandler   Memory handler used to dynamically allocate 
*                          output parameters, if applicable.
* @param[out] data         Sampled sensor data. The number of elements must 
*                          match @a num_sensors.
*
* @return SNS_DDF_SUCCESS if data was populated successfully. If any of the 
*         sensors queried are to be read asynchronously SNS_DDF_PENDING is
*         returned and data is via @a sns_ddf_smgr_data_notify() when
*         available. Otherwise a specific error code is returned.
*/
/*=========================================================================*/
sns_ddf_status_e sns_dd_cm3526_get_data
(
	sns_ddf_handle_t        dd_handle,
	sns_ddf_sensor_e        sensors[],
	uint32_t                num_sensors,
	sns_ddf_memhandler_s*   memhandler,
	sns_ddf_sensor_data_s*  data[]
)
{
	sns_dd_cm3526_t* state = (sns_dd_cm3526_t *)dd_handle;
	sns_ddf_sensor_data_s* sensor_data;
	uint32_t i;

	CM3526_DEBUG_MSG_0(HIGH, "sns_dd_cm3526_get_data: Enter");	
	
	if ((state == NULL) || (memhandler == NULL))
	{
		return SNS_DDF_EINVALID_PARAM;
	}

	CM3526_DEBUG_MSG_1(HIGH, "sns_dd_cm3526_get_data: num_sensors = %d", num_sensors);	
	
	/* allocate memory for sensor data */
	sensor_data = sns_ddf_memhandler_malloc_ex(
			memhandler,
			num_sensors * sizeof(sns_ddf_sensor_data_s),
			state->smgr_handle);
	if (sensor_data == NULL)
	{
		CM3526_DEBUG_MSG_0(ERROR, "sns_dd_cm3526_get_data: failed to allocate sensor_data");
		return SNS_DDF_ENOMEM;
	}

	*data = sensor_data;
	
	for (i = 0; i < num_sensors; i++)
	{	
		sensor_data[i].sensor    = sensors[i];
		sensor_data[i].status    = SNS_DDF_SUCCESS;
		sensor_data[i].timestamp = sns_ddf_get_timestamp();
		
		switch (sensors[i])
		{
			case SNS_DDF_SENSOR_ULTRA_VIOLET:
				sns_dd_cm3526_uvs_report_data(state, &sensor_data[i], memhandler);
				break;		
			default:
				CM3526_DEBUG_MSG_1(HIGH, "sns_dd_cm3526_get_data: unknown sensor = %d", sensors[i]);
				break;
		}
	}
	
	CM3526_DEBUG_MSG_0(HIGH, "sns_dd_cm3526_get_data: Exit");

	return SNS_DDF_SUCCESS;
}

/*==============================================================================

FUNCTION      sns_dd_cm3526_reg_write

DESCRIPTION   Write to sensor register

DEPENDENCIES  None

RETURN VALUE  Attribute value pointer on success, NULL otherwise

SIDE EFFECT   None 

==============================================================================*/
sns_ddf_status_e sns_dd_cm3526_reg_write
(
	sns_ddf_handle_t        port_handle,
	uint8_t                 reg,
	uint16_t                value
)
{
	sns_ddf_status_e status = SNS_DDF_PENDING;
	uint8_t i2c_data[2];
	uint8_t bytes_w;

	i2c_data[0] = (uint8_t)(value & 0xFF);
	i2c_data[1] = (uint8_t)((value >> 8) & 0xFF);
	status = sns_ddf_write_port(
		port_handle,
		reg,
		i2c_data, 
		2, 
		&bytes_w);
		
	return status;
}

/*==============================================================================

FUNCTION      sns_dd_cm3526_reg_read

DESCRIPTION   Read sensor register

DEPENDENCIES  None

RETURN VALUE  Attribute value pointer on success, NULL otherwise

SIDE EFFECT   None 

==============================================================================*/
sns_ddf_status_e sns_dd_cm3526_reg_read
(
	sns_ddf_handle_t		port_handle,
	uint8_t					reg,
	uint16_t*				pvalue
)
{
	sns_ddf_status_e status = SNS_DDF_PENDING;
	uint8_t i2c_data[2];
	uint8_t bytes_w;

	status = sns_ddf_read_port(
		port_handle,
		reg,
		i2c_data,
		2, 
		&bytes_w);
	if (status == SNS_DDF_SUCCESS)
	{
		*pvalue = (uint16_t)i2c_data[1] << 8 | i2c_data[0];
	}

	return status;
}
