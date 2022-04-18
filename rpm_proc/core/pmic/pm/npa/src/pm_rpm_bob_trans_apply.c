/*! \file pm_rpm_bob_trans_apply.c
 *  \n
 *  \brief This file contains implementation for PMIC BOB Translation
 *         and Apply (Aggregate) functions.
 *  \n  
 *  \n &copy; Copyright 2013 QUALCOMM Technologies Incorporated, All Rights Reserved
 */

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

$Header: //components/rel/rpm.bf/1.8/core/pmic/pm/npa/src/pm_rpm_bob_trans_apply.c#1 $

when        who     what, where, why
--------    ---     ----------------------------------------------------------
11/22/13    kt      Created.
========================================================================== */
/*===========================================================================

                        INCLUDE FILES

===========================================================================*/
#include "npa.h"
#include "rpmserver.h"
#include "pm_npa.h"

#include "pm_target_information.h"
#include "pm_rpm_bob_trans_apply.h"
#include "CoreVerify.h"
#include "pm_comm.h"
#include "device_info.h"


static pm_npa_bob_data_type *pm_rpm_bob_req_data[PM_MAX_NUM_PMICS];

// internal function prototypes
void pm_rpm_bob_translation(rpm_translation_info *info);
void pm_rpm_bob_apply(rpm_application_info *info);
int pm_rpm_bob_aggregate(rpm_application_info *info);
static uint32 pm_rpm_bob_voltage_boundry_value_adjust(pm_npa_bob_data_type *bob_data, rpm_application_info *info, uint32 uValue, boolean pin);
void pm_rpm_bob_execute_driver(rpm_application_info *info, pm_npa_bob_int_rep *previous_aggregation);
void pm_rpm_bob_settle(rpm_application_info *info);
pm_npa_bob_data_type* pm_rpm_bob_get_resource_data(uint8 pmic_index);
void pm_rpm_bob_dependency_execute(rpm_application_info *info, pm_npa_bob_int_rep *shadow_data);

void pm_rpm_bob_translation(rpm_translation_info *info)
{
    unsigned type, length, *value;
    pm_npa_bob_int_rep *cache;
    pm_npa_bob_data_type *bob_data = (pm_npa_bob_data_type *)info->cb_data;
    pm_bob_data_type     *bob_ptr = NULL;

    CORE_VERIFY_PTR(bob_data);
    bob_ptr = bob_data->bobDriverData;
    CORE_VERIFY_PTR(bob_ptr);

    // Return for invalid PMIC resource ids. PMIC resource id 0 is invalid.
    if((info->id == 0) || (info->id > bob_ptr->pm_pwr_data.num_of_peripherals))
    {
        return;
    }

    cache = (pm_npa_bob_int_rep *)(info->dest_buffer);

    while(kvp_get(info->new_kvps, &type, &length, (const char **)&value))
    {
        // Need size to match.
        if(sizeof(npa_resource_state) != length) continue;

        switch(type)
        {
        case PM_NPA_KEY_SOFTWARE_ENABLE:
            {
                cache->sw_en = *value;
                break;
            }
        case PM_NPA_KEY_BOB_MODE:
            {
                cache->mode = *value;
                break;
            }
        case PM_NPA_KEY_MICRO_VOLT:
            {
                cache->uvol = *value;
                break;
            }
        case PM_NPA_KEY_PIN_CTRL1_MICRO_VOLT:
            {
                cache->pin1_uvol = *value;
                break;
            }
        case PM_NPA_KEY_PIN_CTRL2_MICRO_VOLT:
            {
                cache->pin2_uvol = *value;
                break;
            }
        case PM_NPA_KEY_PIN_CTRL3_MICRO_VOLT:
            {
                cache->pin3_uvol = *value;
                break;
            }
        default:
            {
                //should never go here
            }
        }
    }
}

void pm_rpm_bob_apply(rpm_application_info *info)
{
    int                    change_detected = 0;
    pm_npa_bob_int_rep     previous_aggregation = *((pm_npa_bob_int_rep *)(info->current_aggregation));
    uint8                  pmic_index = 0;
    pm_npa_bob_data_type  *bob_data = (pm_npa_bob_data_type *)info->cb_data;
    pm_bob_data_type      *bob_ptr = NULL;

    CORE_VERIFY_PTR(bob_data);
    bob_ptr = bob_data->bobDriverData;
    CORE_VERIFY_PTR(bob_ptr);

    // Return for invalid PMIC resource ids. PMIC resource id 0 is invalid.
    if((info->id == 0) || (info->id > bob_ptr->pm_pwr_data.num_of_peripherals))
    {
        return;
    }

    pmic_index = GET_PMIC_INDEX_BOB(bob_data->resourceType);
    CORE_VERIFY(pmic_index < PM_MAX_NUM_PMICS);

    // Aggregate the results, but don't call driver
    change_detected = pm_rpm_bob_aggregate(info);

    if(change_detected != 0)
    {
        pm_rpm_bob_dependency_execute(info, &previous_aggregation);
    }
}



void pm_rpm_bob_dependency_execute(rpm_application_info *info, pm_npa_bob_int_rep *previous_aggregation)
{
    // Execute the driver calls once all dependencies have been executed
    pm_rpm_bob_execute_driver(info, previous_aggregation);
}

int pm_rpm_bob_aggregate(rpm_application_info *info)
{
    int change_detected = 0;
    pm_npa_bob_data_type *bob_data = (pm_npa_bob_data_type *)info->cb_data;
    unsigned clientType = 0;
    pm_npa_bob_int_rep *clientRequest = NULL;
    pm_npa_ldo_int_rep *ldoClientRequest = NULL;
    void *state = NULL;
    unsigned clientCount = 0;
    uint8 i = 0;
    uint8 mask = 0x0F;
    uint8 pin_map = 0;

    unsigned numberOfClients = rpm_get_num_clients(info->resource_handle);

    // For each client aggregate the correct values.
    pm_npa_bob_int_rep aggregatedIntRep = { 0 };
    uint8 pmic_index = GET_PMIC_INDEX_BOB(bob_data->resourceType);
    CORE_VERIFY(pmic_index < PM_MAX_NUM_PMICS);

    /* if access not allowed, just return */
    if(((info->client_type == 0) || (info->client_type == PM_RPM_NPA_CLIENT_BOB_REQ)) &&
       (bob_data->railInfo[pmic_index][info->id - 1].AccessAllowed == 0))
    {
        return change_detected;
    }

    for(clientCount = 0; clientCount < numberOfClients; clientCount++)
    {
        rpm_get_current_request(info->resource_handle, clientCount, &clientType, (const void **)&state);

        // EE Client and Internal BOB BYPASS clients
        if((clientType == 0) || (clientType == PM_RPM_NPA_CLIENT_BOB_REQ))
        {
            clientRequest = (pm_npa_bob_int_rep *)state;

            if(clientRequest != NULL)
            {
                // Aggregate Software Enable
                aggregatedIntRep.sw_en = MAX(aggregatedIntRep.sw_en, clientRequest->sw_en);

                // Aggregate Software mode
                aggregatedIntRep.mode = MAX(aggregatedIntRep.mode, clientRequest->mode);

                // Aggregate Maximum Output Voltage
                aggregatedIntRep.uvol = MAX(aggregatedIntRep.uvol, clientRequest->uvol);

                // Aggregate Maximum Pin1 Output Voltage
                aggregatedIntRep.pin1_uvol = MAX(aggregatedIntRep.pin1_uvol, clientRequest->pin1_uvol);

                // Aggregate Maximum Pin2 Output Voltage
                aggregatedIntRep.pin2_uvol = MAX(aggregatedIntRep.pin2_uvol, clientRequest->pin2_uvol);

                // Aggregate Maximum Pin3 Output Voltage
                aggregatedIntRep.pin3_uvol = MAX(aggregatedIntRep.pin3_uvol, clientRequest->pin3_uvol);
            }
        }
        else if(clientType == PM_RPM_NPA_INT_CLIENT_LDO_DEPENDENT)
        {
            ldoClientRequest = (pm_npa_ldo_int_rep *)state;

            // A valid internal LDO client should have resource_id greater than zero
            if(ldoClientRequest->resource_id > 0)
            {
                // Aggregate Software Enable - Child needs power
                aggregatedIntRep.sw_en = MAX(aggregatedIntRep.sw_en, ldoClientRequest->sw_en);

                // Keep the BoB Always enabled if the child LDO is in pin control
                if(ldoClientRequest->pc_en > 0)
                {
                    mask = 0x0F;

                    aggregatedIntRep.sw_en = 1;

                    aggregatedIntRep.mode = MAX(aggregatedIntRep.mode, PM_SW_MODE_AUTO);
                   /*checking for LDO and BOB pin mapping. If LDO pin is mapped then vote will apply to BOB pin otherwise vote will apply to BOB voltage directly*/
                    if(bob_data->bobPinMappingInfo != NULL)
                    {
                        for(i = 1; i < PM_BOB_EXT_PIN_MAX; i++)
                        {
                            pin_map = bob_data->bobPinMappingInfo[i];
                            if((pin_map & ldoClientRequest->pc_en) != 0)
                            {
                                mask = (mask & ~pin_map);

                                switch(i)
                                {
                                case PM_BOB_EXT_PIN_CTRL1 :
                                  aggregatedIntRep.pin1_uvol = MAX(aggregatedIntRep.pin1_uvol, ldoClientRequest->input_uvol);
                                  break;
                                case PM_BOB_EXT_PIN_CTRL2 :
                                  aggregatedIntRep.pin2_uvol = MAX(aggregatedIntRep.pin2_uvol, ldoClientRequest->input_uvol);
                                  break;
                                case PM_BOB_EXT_PIN_CTRL3 :
                                  aggregatedIntRep.pin3_uvol = MAX(aggregatedIntRep.pin3_uvol, ldoClientRequest->input_uvol);
                                  break;
                                default:
                                  //should never come here
                                  aggregatedIntRep.uvol = MAX(aggregatedIntRep.uvol, ldoClientRequest->input_uvol);
                                  break;
                                }
                            }
                        }
                    }
                    else
                    {
                        aggregatedIntRep.uvol = MAX(aggregatedIntRep.uvol, ldoClientRequest->input_uvol);
                    }

                    if((ldoClientRequest->pc_en & mask) != 0)
                    {
                        aggregatedIntRep.uvol = MAX(aggregatedIntRep.uvol, ldoClientRequest->input_uvol);
                    }
                }

                if(ldoClientRequest->sw_en > 0)
                {
                    aggregatedIntRep.mode = MAX(aggregatedIntRep.mode, PM_SW_MODE_AUTO);
                    aggregatedIntRep.uvol = MAX(aggregatedIntRep.uvol, ldoClientRequest->input_uvol);
                }

            } //resource_id>0
        }
    }

    // input checking
    if(bob_data->railInfo[pmic_index][info->id - 1].AlwaysOn)
    {
        aggregatedIntRep.sw_en = 1;
    }

    if(aggregatedIntRep.mode < bob_data->railInfo[pmic_index][info->id - 1].MinPwrMode)
    {
        aggregatedIntRep.mode = bob_data->railInfo[pmic_index][info->id - 1].MinPwrMode;
    }

    aggregatedIntRep.uvol      = pm_rpm_bob_voltage_boundry_value_adjust(bob_data, info, aggregatedIntRep.uvol, FALSE/*not PIN*/);
    aggregatedIntRep.pin1_uvol = pm_rpm_bob_voltage_boundry_value_adjust(bob_data, info, aggregatedIntRep.pin1_uvol, TRUE/*PIN*/);
    aggregatedIntRep.pin2_uvol = pm_rpm_bob_voltage_boundry_value_adjust(bob_data, info, aggregatedIntRep.pin2_uvol, TRUE/*PIN*/);
    aggregatedIntRep.pin3_uvol = pm_rpm_bob_voltage_boundry_value_adjust(bob_data, info, aggregatedIntRep.pin3_uvol, TRUE/*PIN*/);

    change_detected = pm_rpm_int_copy(&aggregatedIntRep,(pm_npa_bob_int_rep *)info->current_aggregation, sizeof(pm_npa_bob_int_rep));

    return change_detected;
}



static uint32 pm_rpm_bob_voltage_boundry_value_adjust(pm_npa_bob_data_type *bob_data, rpm_application_info *info, uint32 uValue, boolean pin)
{
    pm_volt_level_type ceiling_voltage = 0;
    uint32 uMaxValue =0;
    uint32 uMinValue = 0;
    uint32             dummy_vset = 0;
    uint8 pmic_index = GET_PMIC_INDEX_BOB(bob_data->resourceType);

    if(pin) 
    { 
    uMinValue = 1000 * (bob_data->railInfo[pmic_index][info->id - 1].MinPinVoltage); 
    uMaxValue = 1000 * (bob_data->railInfo[pmic_index][info->id - 1].MaxPinVoltage); 
    } 
    else 
    { 
    uMinValue = 1000 * (bob_data->railInfo[pmic_index][info->id - 1].MinVoltage); 
    uMaxValue = 1000 * (bob_data->railInfo[pmic_index][info->id - 1].MaxVoltage); 
    } 

    if(uValue != 0)
    {
        uValue = (uValue < uMinValue)? uMinValue : uValue;
        uValue = (uValue > uMaxValue)? uMaxValue : uValue ;
    }
     
    if(uValue != 0)
    {
        //check if rounding off vset is needed
        pm_pwr_volt_calculate_vset_celing_uv(&(bob_data->bobDriverData->pm_pwr_data), bob_data->bobDriverData->comm_ptr,
                                             info->id - 1, (pm_volt_level_type)uValue, &dummy_vset, &ceiling_voltage);
    } 

    if(ceiling_voltage != 0)
    {
        uValue =  ceiling_voltage;
    }

    return uValue;
}


void pm_rpm_bob_execute_driver(rpm_application_info *info, pm_npa_bob_int_rep *previous_aggregation)
{
    pm_npa_bob_int_rep *bob_int_rep = (pm_npa_bob_int_rep *)info->current_aggregation;
    pm_npa_bob_data_type *bob_data = (pm_npa_bob_data_type *)info->cb_data;
    pm_bob_data_type *bob_ptr = NULL;
    uint64 curr_settle_end_time = 0;
    uint32 estimated_settling_time_us = 0;
    uint32 estimated_pin_settling_time_us = 0;

    uint8  internal_resource_index = (uint8)(info->id - 1);
    uint8 pmic_index = GET_PMIC_INDEX_BOB(bob_data->resourceType);

    /* Get the bob driver data from the call back data */
    bob_ptr = bob_data->bobDriverData;

    if(bob_ptr != NULL)
    {
        /* Set Power Mode */
        if(bob_int_rep->mode != previous_aggregation->mode)
        {
            pm_bob_sw_mode(pmic_index, internal_resource_index, (pm_bob_mode_type)bob_int_rep->mode);
        }

        /* Set the Output Voltage */
        if((bob_int_rep->uvol != previous_aggregation->uvol) && (bob_int_rep->uvol != 0))
        {
            pm_pwr_volt_level_alg(&(bob_ptr->pm_pwr_data), bob_ptr->comm_ptr, internal_resource_index, (pm_volt_level_type)bob_int_rep->uvol);

            // voltage changed, adding settling time.
            if(bob_int_rep->uvol > previous_aggregation->uvol)
            {
                //calculate the estimated settling time
                estimated_settling_time_us = ((bob_int_rep->uvol - previous_aggregation->uvol) / (bob_data->settlingInfo[internal_resource_index].stepper_rate));
            }
            else
            {
                //calculate the estimated settling time
                estimated_settling_time_us = ((previous_aggregation->uvol - bob_int_rep->uvol) / (bob_data->settlingInfo[internal_resource_index].stepper_rate));
            }
        }

        /* Set the Pin Output Voltage */
        if((bob_int_rep->pin1_uvol != previous_aggregation->pin1_uvol) && (bob_int_rep->pin1_uvol != 0))
        {
            pm_bob_pin_volt_level(pmic_index, internal_resource_index, PM_BOB_EXT_PIN_CTRL1, (pm_volt_level_type)bob_int_rep->pin1_uvol);
        }

        if((bob_int_rep->pin2_uvol != previous_aggregation->pin2_uvol) && (bob_int_rep->pin2_uvol != 0))
        {
            pm_bob_pin_volt_level(pmic_index, internal_resource_index, PM_BOB_EXT_PIN_CTRL2, (pm_volt_level_type)bob_int_rep->pin2_uvol);
        }

        if((bob_int_rep->pin3_uvol != previous_aggregation->pin3_uvol) && (bob_int_rep->pin3_uvol != 0))
        {
            pm_bob_pin_volt_level(pmic_index, internal_resource_index, PM_BOB_EXT_PIN_CTRL3, (pm_volt_level_type)bob_int_rep->pin3_uvol);
        }

        /* Set the enable state */
        if(bob_int_rep->sw_en != previous_aggregation->sw_en)
        {
            pm_pwr_sw_enable_alg(&(bob_ptr->pm_pwr_data), bob_ptr->comm_ptr, internal_resource_index, (pm_on_off_type)bob_int_rep->sw_en);

            estimated_settling_time_us = MAX(estimated_pin_settling_time_us, bob_data->settlingInfo[internal_resource_index].vreg_ok_us);
        }

        // -------------- Settling time ------------------

        // Check if rail has to settle or not
        if((estimated_settling_time_us != 0) && (bob_int_rep->sw_en != 0))
        {

            // Update the current settling start time
            bob_data->settlingInfo[internal_resource_index].settle_start_time = time_service_now();

            // calculate the current settle end time
            curr_settle_end_time = bob_data->settlingInfo[internal_resource_index].settle_start_time + pm_convert_time_to_timetick(estimated_settling_time_us);

            // save the timestamp at which rail is estimated to be settled in RPM info struct and internal struct
            bob_data->settlingInfo[internal_resource_index].settle_end_time = curr_settle_end_time;
            info->settling_time = curr_settle_end_time;

            // internal settling
            pm_rpm_bob_settle(info);
        }
    }
}

void pm_rpm_bob_settle(rpm_application_info *info)
{
    pm_npa_bob_data_type *bob_data = (pm_npa_bob_data_type *)info->cb_data;
    uint8  internal_resource_index = (uint8)(info->id - 1);
    uint64 settle_start_time = bob_data->settlingInfo[internal_resource_index].settle_start_time;
    uint64 settle_end_time = bob_data->settlingInfo[internal_resource_index].settle_end_time;
    uint32 estimated_settling_time_us = 0;
    pm_bob_data_type *bob_ptr = NULL;
    uint8 pmic_index = GET_PMIC_INDEX_BOB(bob_data->resourceType);

    if(settle_start_time != 0)
    {
        // calculate the estimated settling time in micro secs
        estimated_settling_time_us = pm_convert_timetick_to_time(settle_end_time - settle_start_time);

        // Get the driver data from the info call back data
        bob_ptr = bob_data->bobDriverData;

        CORE_VERIFY_PTR(bob_ptr);

        // poll VREG
        pm_rpm_check_vreg_settle_status(settle_start_time, estimated_settling_time_us, &bob_ptr->pm_pwr_data,
                                        bob_ptr->comm_ptr, internal_resource_index,
                                        bob_data->railInfo[pmic_index][info->id - 1].SettlingErrorEnabled);


        // reset the settling time values
        info->settling_time = 0;
        bob_data->settlingInfo[internal_resource_index].settle_end_time = 0;
        bob_data->settlingInfo[internal_resource_index].settle_start_time = 0;
    }
}

__attribute__((section("pm_dram_reclaim_pool")))
void pm_rpm_bob_register_resources(rpm_resource_type resourceType, uint32 num_npa_resources, uint8 pmic_index)
{
    pm_npa_bob_data_type *bob_data = NULL;
    uint32 bob_index = 0;
    pm_bob_data_type *bob_ptr = NULL;
    uint8 range = 0;
    uint32 *vreg_ok_time = NULL;
    uint32 *stepper_rate = NULL;

    if(num_npa_resources > 0)
    {
        //return if there was no driver initialized for this pmic
        bob_ptr = pm_bob_get_data(pmic_index);
        if(bob_ptr == NULL) return;

        bob_data = pm_rpm_bob_get_resource_data(pmic_index);
        if(bob_data == NULL)
        {
            pm_malloc(sizeof(pm_npa_bob_data_type), (void **)&bob_data);

            bob_data->bobDriverData = bob_ptr;
            bob_data->resourceType = resourceType;
            bob_data->depInfo = (pm_pwr_resource_dependency_info **)pm_target_information_get_specific_info(PM_PROP_BOB_DEP);
            CORE_VERIFY_PTR(bob_data->depInfo);
            bob_data->railInfo = (pm_rpm_bob_rail_info_type **)pm_target_information_get_specific_info(PM_PROP_BOB_RAIL);
            CORE_VERIFY_PTR(bob_data->railInfo);

            vreg_ok_time = (uint32 *)pm_target_information_get_common_info(PM_PROP_BOB_VREG_OK_TIME);
            CORE_VERIFY_PTR(vreg_ok_time);
            stepper_rate = (uint32 *)pm_target_information_get_common_info(PM_PROP_BOB_STEPPER_RATE);
            CORE_VERIFY_PTR(stepper_rate);

            pm_malloc(sizeof(pm_pwr_settling_info_type)*num_npa_resources, (void**)&(bob_data->settlingInfo));

            bob_data->bobPinMappingInfo  = (pm_npa_pin_control_enable_type*)pm_target_information_get_specific_info(PM_PROP_BOB_PIN_MAPPING);
            /*NO Coreverify for BOB pin mapping since we do expect it can be NULL*/

            //verify if the range can meet the Bob bypass min, max voltage limits
            for(bob_index = 0; bob_index < num_npa_resources; bob_index++)
            {
                //skip over invalid peripherals
                if(bob_ptr->pm_pwr_data.pwr_specific_info[bob_index].periph_type == 0)
                {
                    continue;
                }
                range = bob_ptr->pm_pwr_data.pwr_specific_info[bob_index].pwr_range;

                /* Check if Min/Max voltage is within the range */
                CORE_VERIFY(((bob_data->railInfo[pmic_index][bob_index].MinVoltage) * 1000 >= bob_ptr->pm_pwr_data.pwr_specific_info[bob_index].pwr_vset[range].RangeMin) &&
                            ((bob_data->railInfo[pmic_index][bob_index].MaxVoltage) * 1000 <= bob_ptr->pm_pwr_data.pwr_specific_info[bob_index].pwr_vset[range].RangeMax));

                /* Check if Min/Max Pin1, Pin2, Pin3 voltage is within the range */
                CORE_VERIFY(((bob_data->railInfo[pmic_index][bob_index].MinPinVoltage) * 1000 >= bob_ptr->pm_pwr_data.pwr_specific_info[bob_index].pwr_vset[range].RangeMin) &&
                            ((bob_data->railInfo[pmic_index][bob_index].MaxPinVoltage) * 1000 <= bob_ptr->pm_pwr_data.pwr_specific_info[bob_index].pwr_vset[range].RangeMax));

                bob_data->settlingInfo[bob_index].vreg_ok_us = vreg_ok_time[0];
                bob_data->settlingInfo[bob_index].stepper_rate = stepper_rate[0];
            }

            rpm_register_resource(resourceType, num_npa_resources + 1, sizeof(pm_npa_bob_int_rep), pm_rpm_bob_translation, pm_rpm_bob_apply, (void *)bob_data);

            pm_rpm_bob_req_data[pmic_index] = bob_data;
        }
    }
}

__attribute__((section("pm_dram_reclaim_pool")))
void pm_rpm_bob_register_resource_dependencies(rpm_resource_type resourceType, uint32 num_npa_resources, uint8 pmic_index)
{
    uint8 count = 0;
    pm_pwr_resource *dependency = NULL;
    pm_pwr_resource_dependency_info *depInfo = NULL;
    pm_npa_bob_int_rep *current_agg = NULL;
    pm_bob_data_type *bob_ptr = NULL;
    pm_volt_level_type vol = 0;
    pm_volt_level_type pin_vol = 0;
    pm_on_off_type en_status = PM_OFF;
    pm_npa_bob_data_type *bob_data = NULL;

    if(num_npa_resources > 0)
    {
        //return if there was no driver initialized for this pmic
        if(pm_rpm_bob_req_data[pmic_index] == NULL) return;

        bob_data = pm_rpm_bob_req_data[pmic_index];

        if(bob_data->depInfo != NULL)
        {
            depInfo = bob_data->depInfo[pmic_index];
        }

        for(count = 1; count < num_npa_resources + 1; count++)
        {
            rpm_get_aggregated_request_buffer(resourceType, count, (const void **)&current_agg);

            if(current_agg != NULL)
            {
                bob_ptr = bob_data->bobDriverData;
                CORE_VERIFY_PTR(bob_ptr);
                DALSYS_memset(current_agg, 0, sizeof(pm_npa_bob_int_rep));
                //skip over invalid peripherals
                if(bob_ptr->pm_pwr_data.pwr_specific_info[count - 1].periph_type == 0)
                {
                    continue;
                }
                pm_pwr_volt_level_status_alg(&(bob_ptr->pm_pwr_data), bob_ptr->comm_ptr, count - 1, &vol);
                current_agg->uvol = vol;
                pm_pwr_sw_enable_status_alg(&(bob_ptr->pm_pwr_data), bob_ptr->comm_ptr, count - 1, &en_status);
                current_agg->sw_en = en_status;
                pm_bob_pin_volt_level_status(pmic_index, count - 1, PM_BOB_EXT_PIN_CTRL1, &pin_vol);
                current_agg->pin1_uvol = pin_vol;
                pm_bob_pin_volt_level_status(pmic_index, count - 1, PM_BOB_EXT_PIN_CTRL2, &pin_vol);
                current_agg->pin2_uvol = pin_vol;
                pm_bob_pin_volt_level_status(pmic_index, count - 1, PM_BOB_EXT_PIN_CTRL3, &pin_vol);
                current_agg->pin3_uvol = pin_vol;
                current_agg->mode = PM_BOB_MODE_INVALID;
            }
        }

        if(depInfo)
        {
            for(count = 1; count < num_npa_resources + 1; count++)
            {
                if(depInfo[count].parent_source_dependency != NULL)
                {
                    dependency = depInfo[count].parent_source_dependency;

                    // create the internal client
                    rpm_register_internal_client_type(dependency->resource_type, dependency->internal_resource_index, PM_RPM_NPA_INT_CLIENT_BOB_DEPENDENT, sizeof(pm_npa_bob_int_rep));

                    depInfo[count].parent_source_dependency_client_handle =
                      rpm_create_client(dependency->resource_type, dependency->internal_resource_index, PM_RPM_NPA_INT_CLIENT_BOB_DEPENDENT);
                }
            }
        }
    }
}


pm_npa_bob_data_type* pm_rpm_bob_get_resource_data(uint8 pmic_index)
{
    if(pmic_index < PM_MAX_NUM_PMICS)
    {
        return  pm_rpm_bob_req_data[pmic_index];
    }

    return NULL;
}

