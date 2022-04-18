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
04/12/2016   JH      Porting from dd_vendor_1.c
==============================================================================*/

/*============================================================================
INCLUDE FILES
============================================================================*/

#include "sns_dd_cm3526.h"

/*============================================================================
STATIC VARIABLE DEFINITIONS
============================================================================*/

static sns_ddf_sensor_e dd_cm3526_sensors[SNS_DD_CM3526_NUM_SENSOR_TYPES] =
{
	SNS_DDF_SENSOR_ULTRA_VIOLET
};

/*============================================================================
STATIC FUNCTION PROTOTYPES
============================================================================*/


/*===========================================================================

FUNCTION:   sns_dd_cm3526_init

===========================================================================*/
/** 
* @brief Initializes the driver and sets up devices.
*  
* @param[out] dd_handle_ptr  Pointer that this function must malloc and 
*                            populate. This is a handle to the driver
*                            instance that will be passed in to all other
*                            functions. NB: Do not use @a memhandler to
*                            allocate this memory.
* @param[in]  smgr_handle    Handle used to identify this driver when it 
*                            calls into Sensors Manager functions.
* @param[in]  nv_params      NV parameters retrieved for the driver.
* @param[in]  device_info    Access info for physical devices controlled by 
*                            this driver. Used to configure the bus
*                            and talk to the devices.
* @param[in]  num_devices    Number of elements in @a device_info. 
* @param[in]  memhandler     Memory handler used to dynamically allocate 
*                            output parameters, if applicable. NB: Do not
*                            use memhandler to allocate memory for
*                            @a dd_handle_ptr.
* @param[in/out] sensors     List of supported sensors, allocated, 
*                            populated, and returned by this function.
* @param[in/out] num_sensors Number of elements in @a sensors.
*
* @return Success if @a dd_handle_ptr was allocated and the driver was 
*         configured properly. Otherwise a specific error code is returned.
*/
/*=========================================================================*/                                             
sns_ddf_status_e sns_dd_cm3526_init
(
	sns_ddf_handle_t*        dd_ptr,
	sns_ddf_handle_t         smgr_handle,
	sns_ddf_nv_params_s*     nv_params,
	sns_ddf_device_access_s  device_info[],
	uint32_t                 num_devices,
	sns_ddf_memhandler_s*    memhandler,
	sns_ddf_sensor_e*        sensors[],
	uint32_t*                num_sensors
)
{
	sns_dd_cm3526_t *state;
	sns_ddf_status_e status;

	CM3526_DEBUG_MSG_0(HIGH, "sns_dd_cm3526_init: Enter");

#ifdef CM3526_ENABLE_UIMG
	/* Update smgr sensor data for the driver to indicate uImage support */
	sns_ddf_smgr_set_uimg_refac(smgr_handle);
#endif

	/* Input sanity check */
	if (num_sensors == NULL)
	{
		return SNS_DDF_EINVALID_PARAM;
	}

	if ((sns_ddf_malloc_ex(
			(void **)&state,
			sizeof(sns_dd_cm3526_t), smgr_handle)) != SNS_DDF_SUCCESS)
	{
		return SNS_DDF_ENOMEM;
	}

	memset(state, 0, sizeof(sns_dd_cm3526_t));

	*dd_ptr = state;

	if ((status = sns_ddf_open_port(
			&(state->port_handle),
			&(device_info->port_config))) != SNS_DDF_SUCCESS)
	{
		sns_ddf_mfree_ex((void *)state, smgr_handle);
		return SNS_DDF_EBUS;
	}

	state->smgr_handle    = smgr_handle;

	/* Fill out supported sensor info */
	*sensors        = dd_cm3526_sensors;
	*num_sensors    = SNS_DD_CM3526_NUM_SENSOR_TYPES;

	/* Read sensor ID register to confirm presence. */

	/* Perform reset */
	sns_dd_cm3526_reset(state);

	CM3526_DEBUG_MSG_0(HIGH, "sns_dd_cm3526_init: Exit");

	return SNS_DDF_SUCCESS;
}

/*===========================================================================

FUNCTION:   sns_dd_cm3526_reset

===========================================================================*/
/**
* @brief Resets the driver and device so they return to the state they were 
*        in after init() was called.
*
* @param[in] dd_handle  Handle to a driver instance.
* 
* @return Success if the driver was able to reset its state and the device.
*         Otherwise a specific error code is returned. 
*/
/*=========================================================================*/
sns_ddf_status_e sns_dd_cm3526_reset
(
	sns_ddf_handle_t dd_handle
)
{
	sns_dd_cm3526_t* state = (sns_dd_cm3526_t *)dd_handle;
	sns_ddf_status_e status = SNS_DDF_SUCCESS;
	
	CM3526_DEBUG_MSG_0(HIGH, "sns_dd_cm3526_reset: Enter");

	/* Reset state variables. */
	state->uvs_odr = 0;

	/* Perform software reset on sensor if supported. */
	state->regs[SNS_DD_CM3526_CONF_REG]  = SNS_DD_CM3526_CONF_DEFAULT;

	/* Put sensor in low power state. */
	state->regs[SNS_DD_CM3526_CONF_REG] |= SNS_DD_CM3526_CONF_SD;
	status = sns_dd_cm3526_reg_write(state->port_handle, SNS_DD_CM3526_CONF_REG, state->regs[SNS_DD_CM3526_CONF_REG]);
	if (status != SNS_DDF_SUCCESS)
	{
		CM3526_DEBUG_MSG_0(ERROR, "sns_dd_cm3526_reset: failed to write CONF_REG");
	}
	
	CM3526_DEBUG_MSG_0(HIGH, "sns_dd_cm3526_reset: Exit");

	return SNS_DDF_SUCCESS;
}

/*===========================================================================

FUNCTION:   sns_dd_cm3526_set_attrib

===========================================================================*/
/**
* @brief Sets a sensor attribute to a specific value.
*
* @param[in] dd_handle  Handle to a driver instance.
* @param[in] sensor     Sensor for which this attribute is to be set. When 
*                       addressing an attribute that refers to the driver
*                       this value is set to SNS_DDF_SENSOR__ALL.
* @param[in] attrib     Attribute to be set.
* @param[in] value      Value to set this attribute.
*
* @return Success if the value of the attribute was set properly. Otherwise 
*         a specific error code is returned.
*/
/*=========================================================================*/
sns_ddf_status_e sns_dd_cm3526_set_attrib
(
	sns_ddf_handle_t     dd_handle,
	sns_ddf_sensor_e     sensor,
	sns_ddf_attribute_e  attrib,
	void*                value
)
{  
	sns_ddf_status_e status = SNS_DDF_SUCCESS;
	sns_dd_cm3526_t* state = (sns_dd_cm3526_t *)dd_handle;

	CM3526_DEBUG_MSG_0(HIGH, "sns_dd_cm3526_set_attrib: Enter");

	/* Input sanity check */
	if (state == NULL)
	{
		return SNS_DDF_EINVALID_PARAM;
	}

	CM3526_DEBUG_MSG_2(HIGH, "sns_dd_cm3526_set_attrib: sensor = %d, attrib = %d", sensor, attrib);		
	
	if ((sensor != SNS_DDF_SENSOR_ULTRA_VIOLET) && (sensor != SNS_DDF_SENSOR__ALL))
	{
		return SNS_DDF_EINVALID_PARAM;
	}

	switch (attrib)
	{
		case SNS_DDF_ATTRIB_POWER_STATE:
			/* Set power mode */
			// Power mode is controlled by ODR setting so that RGB and CTC can be enabled/disabled separately
			break;
		case SNS_DDF_ATTRIB_ODR:
			/* Set ODR */
			{
				sns_ddf_odr_t desired_odr = *(sns_ddf_odr_t *)value;

				if (sensor == SNS_DDF_SENSOR_ULTRA_VIOLET)
				{
					CM3526_DEBUG_MSG_1(HIGH, "sns_dd_cm3526_set_attrib: UVS desired_odr = %d", (int)desired_odr);

					if ((state->uvs_odr == 0) && (desired_odr != 0))
					{
						// Activate UVS
						CM3526_DEBUG_MSG_0(HIGH, "sns_dd_cm3526_set_attrib: activate UVS");						
						state->regs[SNS_DD_CM3526_CONF_REG] = SNS_DD_CM3526_CONF_DEFAULT;
						status = sns_dd_cm3526_reg_write(state->port_handle, SNS_DD_CM3526_CONF_REG,  state->regs[SNS_DD_CM3526_CONF_REG]);
						if (status != SNS_DDF_SUCCESS)
						{
							CM3526_DEBUG_MSG_0(ERROR, "sns_dd_cm3526_set_attrib: failed to write CONF_REG");
							return status;
						}			
					}					
					else if ((state->uvs_odr != 0) && (desired_odr == 0))
					{					
						// Shut down UVS
						CM3526_DEBUG_MSG_0(HIGH, "sns_dd_cm3526_set_attrib: shut down UVS");						
						state->regs[SNS_DD_CM3526_CONF_REG] |= SNS_DD_CM3526_CONF_SD;
						status = sns_dd_cm3526_reg_write(state->port_handle, SNS_DD_CM3526_CONF_REG,  state->regs[SNS_DD_CM3526_CONF_REG]);
						if (status != SNS_DDF_SUCCESS)
						{
							CM3526_DEBUG_MSG_0(ERROR, "sns_dd_cm3526_set_attrib: failed to write CONF_REG");
							return status;
						}
					}					
					
					state->uvs_odr = desired_odr;
				}
			}
			break;
		case SNS_DDF_ATTRIB_RANGE:
			/* Set range (typically used only for accel and gyro sensors) */
			{
				state->range = *(uint16_t *)value;
			}
			break;
		default:
			CM3526_DEBUG_MSG_0(ERROR, "sns_dd_cm3526_set_attrib: unsupported attribute");		
			return SNS_DDF_EINVALID_ATTR;
	}

	CM3526_DEBUG_MSG_0(HIGH, "sns_dd_cm3526_set_attrib: Exit");

	return status;
}

/*===========================================================================

FUNCTION:   sns_dd_cm3526_get_attrib

===========================================================================*/
/**
* @brief Retrieves the value of an attribute for a sensor.
* 
* @param[in]  dd_handle   Handle to a driver instance.
* @param[in]  sensor      Sensor whose attribute is to be retrieved. When 
*                         addressing an attribute that refers to the driver
*                         this value is set to SNS_DDF_SENSOR__ALL.
* @param[in]  attrib      Attribute to be retrieved.
* @param[in]  memhandler  Memory handler used to dynamically allocate 
*                         output parameters, if applicable.
* @param[out] value       Pointer that this function will allocate or set 
*                         to the attribute's value.
* @param[out] num_elems   Number of elements in @a value.
*  
* @return Success if the attribute was retrieved and the buffer was 
*         populated. Otherwise a specific error code is returned.
*/
/*=========================================================================*/
sns_ddf_status_e sns_dd_cm3526_get_attrib
(
	sns_ddf_handle_t     dd_handle,
	sns_ddf_sensor_e     sensor,
	sns_ddf_attribute_e  attrib,
	sns_ddf_memhandler_s* memhandler,
	void**                value,
	uint32_t*             num_elems
)
{
	sns_dd_cm3526_t *state = (sns_dd_cm3526_t *)dd_handle;

	CM3526_DEBUG_MSG_0(HIGH, "sns_dd_cm3526_get_attrib: Enter");

	/* Input sanity check */
	if (state == NULL)
	{	
		return SNS_DDF_EINVALID_PARAM;
	}

	CM3526_DEBUG_MSG_2(HIGH, "sns_dd_cm3526_get_attrib: sensor = %d, attrib = %d", sensor, attrib);	
	
	if (sensor != SNS_DDF_SENSOR_ULTRA_VIOLET)
	{
		return SNS_DDF_EINVALID_PARAM;
	}

	switch (attrib)
	{
		case SNS_DDF_ATTRIB_POWER_INFO:
			{
				sns_ddf_power_info_s* power_attrib;
				
				if ((*value = sns_ddf_memhandler_malloc_ex(
						memhandler,
						sizeof(sns_ddf_power_info_s), state->smgr_handle)) == NULL)
				{
					return SNS_DDF_ENOMEM;
				}
				power_attrib = (sns_ddf_power_info_s *)(*value);
				*num_elems   = 1;

				/* Value is unit of uA */
				power_attrib->active_current = SNS_DD_CM3526_PWR;
				power_attrib->lowpower_current = SNS_DD_CM3526_LO_PWR;
			}
			break;
		case SNS_DDF_ATTRIB_RANGE:
			{
				sns_ddf_range_s *device_ranges;
				
				if ((*value = sns_ddf_memhandler_malloc_ex(
						memhandler,
						sizeof(sns_ddf_range_s), state->smgr_handle)) == NULL)
				{
					return SNS_DDF_ENOMEM;
				}

				device_ranges = (sns_ddf_range_s *)(*value);
				*num_elems    = 1;

				/* Value is unit of sensor in Q16 format */
				device_ranges->min  = FX_FLTTOFIX_Q16(0.0);
				device_ranges->max  = FX_FLTTOFIX_Q16(6553.0);				
			}
			break;
		case SNS_DDF_ATTRIB_RESOLUTION_ADC:
			{
				sns_ddf_resolution_adc_s *device_res_adc;
				
				if ((*value = sns_ddf_memhandler_malloc_ex(
						memhandler,
						sizeof(sns_ddf_resolution_adc_s), state->smgr_handle)) == NULL)
				{
					return SNS_DDF_ENOMEM;
				}

				device_res_adc = (sns_ddf_resolution_adc_s *)(*value);
				*num_elems     = 1;

				/* Value is integer */
				device_res_adc->bit_len  = SNS_DD_CM3526_BITS;  // bits
				device_res_adc->max_freq = SNS_DD_CM3526_FREQ;  // Hz  
			}
			break;
		case SNS_DDF_ATTRIB_RESOLUTION:
			{
				sns_ddf_resolution_t *device_res;
				
				if ((*value = sns_ddf_memhandler_malloc_ex(
						memhandler,
						sizeof(sns_ddf_resolution_t), state->smgr_handle)) == NULL)
				{
					return SNS_DDF_ENOMEM;
				}
				
				/* Value is in Q16 in sensor unit */
				device_res  = (sns_ddf_resolution_t *)(*value);
				*num_elems  = 1;
				*device_res = SNS_DD_CM3526_RES;
			}
			break;
		case SNS_DDF_ATTRIB_DELAYS:
			{
				sns_ddf_delays_s *device_delay;
				
				if ((*value = sns_ddf_memhandler_malloc_ex(
						memhandler,
						sizeof(sns_ddf_delays_s), state->smgr_handle)) == NULL)
				{
					return SNS_DDF_ENOMEM;
				}

				device_delay = (sns_ddf_delays_s *)(*value);
				*num_elems   = 1;
				/* Value is in int in usec */
				device_delay->time_to_active  = 10;
				device_delay->time_to_data    = 100;
			}
			break;
		case SNS_DDF_ATTRIB_DRIVER_INFO:
			{
				sns_ddf_driver_info_s *driver_info;
				
				if ((*value = sns_ddf_memhandler_malloc_ex(
						memhandler,
						sizeof(sns_ddf_driver_info_s), state->smgr_handle)) == NULL)
				{
					return SNS_DDF_ENOMEM;
				}

				driver_info = (sns_ddf_driver_info_s *)(*value);
				*num_elems  = 1;
				driver_info->name = "CM3526";
				driver_info->version = 1;
			}
			break;
		case SNS_DDF_ATTRIB_DEVICE_INFO:
			{
				sns_ddf_device_info_s *device_info;

				if ((*value = sns_ddf_memhandler_malloc_ex(
						memhandler,
						sizeof(sns_ddf_device_info_s), state->smgr_handle)) == NULL)
				{
					return SNS_DDF_ENOMEM;
				}

				device_info = (sns_ddf_device_info_s *)(*value);
				*num_elems  = 1;
				device_info->model = "CM3526";
				device_info->vendor = "Capella";
				device_info->name = "UVS";
				device_info->version = 1;
			}
			break;
		case SNS_DDF_ATTRIB_ODR:
			{
				sns_ddf_odr_t *curr_odr;
				
				if ((curr_odr = sns_ddf_memhandler_malloc_ex(
						memhandler,
						sizeof(sns_ddf_odr_t), state->smgr_handle)) == NULL)
				{
					return SNS_DDF_ENOMEM;
				}
				
				*curr_odr = state->uvs_odr;
				*value = curr_odr;
			}
			break;
		case SNS_DDF_ATTRIB_SUPPORTED_ODR_LIST:
			{
				uint32_t *odr_list;

				if ((odr_list = (uint32_t *)sns_ddf_memhandler_malloc_ex(
						memhandler,
						1 * sizeof(uint32_t), state->smgr_handle)) == NULL)
				{
					return SNS_DDF_ENOMEM;
				}	
				
				odr_list[0] = SNS_DD_CM3526_UVS_ODR;		
				*value = (uint32_t *)odr_list;
				*num_elems = 1;				
			}
			break;
		default:
			CM3526_DEBUG_MSG_0(ERROR, "sns_dd_cm3526_get_attrib: unsupported attribute");
			return SNS_DDF_EINVALID_ATTR;
	}

	CM3526_DEBUG_MSG_0(HIGH, "sns_dd_cm3526_get_attrib: Exit");

	return SNS_DDF_SUCCESS;
}

/*===========================================================================

FUNCTION:   sns_dd_cm3526_run_test

===========================================================================*/
/**
* @brief Runs a factory test case.
*  
* @param[in]  dd_handle  Handle to a driver instance. 
* @param[in]  sensor     Sensor on which to run the test. 
* @param[in]  test       Test case to run. 
* @param[out] err        Optional driver-specific error code.
*  
* @return One of the following error codes:
*     SNS_DDF_SUCCESS        - Test passed.
*     SNS_DDF_PENDING        - Test result will be sent as an event.
*     SNS_DDF_EDEVICE_BUSY   - Device is busy streaming, cannot run test.
*     SNS_DDF_EINVALID_TEST  - Test is not defined for this sensor.
*     SNS_DDF_EINVALID_PARAM - One of the parameters is invalid.
*     SNS_DDF_EFAIL          - Unknown error occurred.
*/
/*=========================================================================*/
sns_ddf_status_e sns_dd_cm3526_run_test
(
	sns_ddf_handle_t    dd_handle,
	sns_ddf_sensor_e    sensor_type,
	sns_ddf_test_e      test,
	uint32_t*           err
)
{
    sns_dd_cm3526_t    *state = (sns_dd_cm3526_t *)dd_handle;
    sns_ddf_status_e    status = SNS_DDF_SUCCESS;
    uint16_t            reg_read;  

	CM3526_DEBUG_MSG_0(HIGH, "sns_dd_cm3526_run_test: Enter");
  
	/* Sanity check input */
	if (state == NULL)
	{
		return SNS_DDF_EINVALID_PARAM;
	}

	if (sensor_type == SNS_DDF_SENSOR_ULTRA_VIOLET)
    {
        if (test == SNS_DDF_TEST_SELF)
        {
			CM3526_DEBUG_MSG_0(HIGH, "sns_dd_cm3526_run_test: UV sensor in self test");
			
            /* Read and verify device ID */
            status = sns_dd_cm3526_reg_read(state->port_handle, SNS_DD_CM3526_ID_REG, &reg_read);
            if (status != SNS_DDF_SUCCESS)
            {
                CM3526_DEBUG_MSG_0(ERROR, "sns_dd_cm3526_run_test: failed to read ID_REG");				
                return status;
            }
			if ((reg_read & 0xFF) != CM3526_ID)
            {
                CM3526_DEBUG_MSG_1(ERROR, "sns_dd_cm3526_run_test: wrong device id = %d", reg_read);
                return SNS_DDF_EDEVICE;
            }			
		
            status = sns_dd_cm3526_reg_read(state->port_handle, SNS_DD_CM3526_CONF_REG, &reg_read);
            if (status != SNS_DDF_SUCCESS) return status;
            status = sns_dd_cm3526_reg_read(state->port_handle, SNS_DD_CM3526_UVA_DATA_REG, &reg_read);
            if (status != SNS_DDF_SUCCESS) return status;
            status = sns_dd_cm3526_reg_read(state->port_handle, SNS_DD_CM3526_UVB_DATA_REG, &reg_read);
            if (status != SNS_DDF_SUCCESS) return status;
            status = sns_dd_cm3526_reg_read(state->port_handle, SNS_DD_CM3526_UVCOMP1_DATA_REG, &reg_read);
            if (status != SNS_DDF_SUCCESS) return status;
            status = sns_dd_cm3526_reg_read(state->port_handle, SNS_DD_CM3526_UVCOMP2_DATA_REG, &reg_read);
            if (status != SNS_DDF_SUCCESS) return status;			
        }
        else
        {
			CM3526_DEBUG_MSG_0(ERROR, "sns_dd_cm3526_run_test: not self test");
			return SNS_DDF_EINVALID_TEST;
        }
    }
    else 
    {
		CM3526_DEBUG_MSG_0(ERROR, "sns_dd_cm3526_run_test: not correct sensor");		
        return SNS_DDF_EINVALID_TEST;
    }

	CM3526_DEBUG_MSG_0(HIGH, "sns_dd_cm3526_run_test: Exit");
	
    return SNS_DDF_SUCCESS;
}

/*===========================================================================

FUNCTION:   sns_dd_cm3526_probe

===========================================================================*/
/**
* @brief Probes for the device with a given configuration.

* @param[in]  dev_info    Access info for physical devices controlled by 
*                         this driver. Used to determine if the device is
*                         physically present.
* @param[in]  memhandler  Memory handler used to dynamically allocate 
*                         output parameters, if applicable.
* @param[out] num_sensors Number of sensors supported. 0 if none.
* @param[out] sensor_type Array of sensor types supported, with num_sensor
*                         elements. Allocated by this function.
*
* @return SNS_DDF_SUCCESS if the part was probed function completed, even
*         if no device was found (in which case num_sensors will be set to
*         0).
*/
/*=========================================================================*/
sns_ddf_status_e sns_dd_cm3526_probe
(
	sns_ddf_device_access_s* device_info,
	sns_ddf_memhandler_s*    memhandler,
	uint32_t*                num_sensors,
	sns_ddf_sensor_e**       sensors
)
{
	sns_ddf_status_e status;
	sns_ddf_handle_t port_handle;
    uint16_t         reg_read; 	

	CM3526_DEBUG_MSG_0(HIGH, "sns_dd_cm3526_probe: Enter");

	*num_sensors = 0;
	*sensors = NULL;

	if ((status = sns_ddf_open_port(
			&port_handle,
			&(device_info->port_config))) != SNS_DDF_SUCCESS)
	{
		return status;
	}

	/* Read ID register */
	/* Verify ID register value */
	/* If incorrect ID, close port and return */
	status = sns_dd_cm3526_reg_read(port_handle, SNS_DD_CM3526_ID_REG, &reg_read);
	if (status != SNS_DDF_SUCCESS)
	{
		CM3526_DEBUG_MSG_0(ERROR, "sns_dd_cm3526_probe: failed to read ID_REG");
		sns_ddf_close_port(port_handle);		
		return status;		
	}
	if ((reg_read & 0xFF) != CM3526_ID)
	{
		CM3526_DEBUG_MSG_1(ERROR, "sns_dd_cm3526_probe: wrong device id = %d", reg_read);
		sns_ddf_close_port(port_handle);			
		return SNS_DDF_EDEVICE;
	}

	/* Found sensor */
	*sensors = sns_ddf_memhandler_malloc(
		memhandler,
		sizeof(sns_ddf_sensor_e) * SNS_DD_CM3526_NUM_SENSOR_TYPES);

	if (*sensors == NULL)
	{
		status = SNS_DDF_ENOMEM;
		sns_ddf_close_port(port_handle);
		return status; 
	}

	/* set return value */
	(*sensors)[0] = SNS_DDF_SENSOR_ULTRA_VIOLET;	
	*num_sensors  = SNS_DD_CM3526_NUM_SENSOR_TYPES;

	status = SNS_DDF_SUCCESS;

	CM3526_DEBUG_MSG_0(HIGH, "sns_dd_cm3526_probe: Exit");

	return status;
}

/*===========================================================================

FUNCTION:   sns_dd_cm3526_enable_sched_data

===========================================================================*/
/**
* @brief Begins device-scheduled sampling and enables notification via Data 
*        Ready Interrupts (DRI).
*  
* @param[in] handle  Handle to the driver's instance.
* @param[in] sensor  Sensor to be sampled.
* @param[in] enable  True to enable or false to disable data stream.
* 
* @return SNS_DDF_SUCCESS if sensor was successfully configured and 
*         internal sampling has commenced or ceased. Otherwise an
*         appropriate error code.
*/
/*=========================================================================*/
sns_ddf_status_e sns_dd_cm3526_enable_sched_data
(
	sns_ddf_handle_t  handle,
	sns_ddf_sensor_e  sensor,
	bool              enable
)
{
	return SNS_DDF_SUCCESS;
}

