/*! \file pm_rpm_boost_trans_apply.c
 *  \n
 *  \brief This file contains implementation for PMIC BOOST Translation
 *         and Apply (Aggregate) functions.
 *  \n  
 *  \n &copy; Copyright 2013-2015 QUALCOMM Technologies Incorporated, All Rights Reserved
 */

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.
 
$Header: //components/rel/rpm.bf/1.8/core/pmic/pm/npa/src/pm_rpm_boost_trans_apply.c#1 $

when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
06/11/13   hs      Adding settling time for regulators.
05/17/13   hs      PMIC SWEVENT revise.
04/25/13   aks     Code Refactoring: Removing PMIC_SubRsc from pwr algs   
04/12/13   hs       Code refactoring.
02/27/13   hs       Code refactoring.
01/29/13   aks     Adding support for 5v boost as a separate driver
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "npa.h"
#include "rpmserver.h"
#include "pm_npa.h"

#include "pm_target_information.h"
#include "pm_rpm_boost_trans_apply.h"
#include "pm_npa_device_boost.h"
#include "CoreVerify.h"
#include "device_info.h"
#include "pm_config.h"

static pm_npa_boost_data_type *pm_rpm_boost_req_data[PM_MAX_NUM_PMICS];


// internal function prototypes
void pm_rpm_boost_translation(rpm_translation_info *info);
void pm_rpm_boost_apply(rpm_application_info *info);
void pm_rpm_boost_pre_dependency_analysis(rpm_application_info *info, pm_npa_boost_int_rep* previous_aggregation);
void pm_rpm_boost_post_dependency_analysis(rpm_application_info *info, pm_npa_boost_int_rep* previous_aggregation);
int pm_rpm_boost_aggregate(rpm_application_info *info);
void pm_rpm_boost_execute_driver(rpm_application_info *info, pm_npa_boost_int_rep* previous_aggregation);
void pm_rpm_boost_settle(rpm_application_info *info);

void pm_rpm_boost_translation(rpm_translation_info *info)
{
    unsigned type, length, *value;
    pm_npa_boost_int_rep *cache;
    pm_npa_boost_data_type *boost_data = (pm_npa_boost_data_type *)info->cb_data;
    pm_boost_data_type     *boost_ptr = NULL;

    CORE_VERIFY_PTR(boost_data);
    boost_ptr = boost_data->boostDriverData;
    CORE_VERIFY_PTR(boost_ptr);

    // Return for invalid PMIC resource ids. PMIC resource id 0 is invalid.
    if((info->id == 0) || (info->id > boost_ptr->pm_pwr_data.num_of_peripherals))
    {
        return;  
    }

    // PMIC resource id 0 is invalid
    if(info->id == 0)
    {
        return;  
    }

    cache = (pm_npa_boost_int_rep *)(info->dest_buffer);
    
    while(kvp_get(info->new_kvps, &type, &length, (const char **)&value))
    {
        // Need size to match.
        if(sizeof(npa_resource_state) != length)
            continue;

        switch(type)
        {
            case PM_NPA_KEY_SOFTWARE_ENABLE:
            {
                cache->sw_en = *value;
                break;
            }
            case PM_NPA_KEY_PIN_CTRL_ENABLE:
            {
                cache->pc_en = *value;
                break;
            }
            default:
            {
                //should never go here
            }
        }
    }
}

void pm_rpm_boost_apply(rpm_application_info *info)
{
    int                    change_detected = 0;
    pm_npa_boost_int_rep   previous_aggregation = *((pm_npa_boost_int_rep*)(info->current_aggregation));
	uint64                 current_time = 0;
    uint64                 settle_start_time = 0;
    uint64                 settle_end_time = 0;
    uint32                 min_settling_time_us = 0;
    uint32                 settling_time_elapsed_us = 0;
    uint32                 settling_time_remaining_us = 0;
    boolean                vreg_status = FALSE;
    uint8                  internal_resource_index = 0;
    uint8                  pmic_index = 0;
    pm_npa_boost_data_type *boost_data = (pm_npa_boost_data_type *)info->cb_data;
    pm_boost_data_type     *boost_ptr = NULL;
    pm_npa_boost_int_rep   *curr_aggr = NULL;
    uint32                 actual_time_us = 0;
    uint32                 estimated_time_us = 0;
    uint8                  periph_type = 0;

    CORE_VERIFY_PTR(boost_data);

    boost_ptr = boost_data->boostDriverData;

    CORE_VERIFY_PTR(boost_ptr);

    // Return for invalid PMIC resource ids. PMIC resource id 0 is invalid.
    if((info->id == 0) || (info->id > boost_ptr->pm_pwr_data.num_of_peripherals))
    {
        return;  
    }

    internal_resource_index = (uint8)(info->id - 1);

    pmic_index = GET_PMIC_INDEX_BOOST(boost_data->resourceType);
    CORE_VERIFY(pmic_index < PM_MAX_NUM_PMICS);

    if(0 == info->settling_time) // this is a new request
    {
        // Aggregate the results, but don't call driver
        change_detected = pm_rpm_boost_aggregate(info);
    
        if(change_detected != 0 )
        {
            pm_rpm_boost_dependency_execute(info, &previous_aggregation);
        }
    }
    else // this is an old request to check if the rail has settled
    {
        // Check the current aggregation to see if the rail got disabled while settling parallely
        curr_aggr = (pm_npa_boost_int_rep*)info->current_aggregation;

        if(curr_aggr->sw_en != 0)
        {
            settle_start_time = boost_data->settlingInfo[internal_resource_index].settle_start_time;
            settle_end_time = boost_data->settlingInfo[internal_resource_index].settle_end_time;

            // take the current system time in time tick
            current_time = time_service_now();

            // make sure the rail didn't finish settling due to a different request
            // only then update the settling time elapsed and check min settling time
            if(settle_start_time != 0)
            {
               // calculate the settling time elapsed in micro seconds
               if(current_time > settle_start_time)
               {
                  settling_time_elapsed_us = pm_convert_timetick_to_time(current_time - settle_start_time);
               }
 
               // get the minimum settling time info for the rail from config data
               min_settling_time_us = boost_data->railInfo[pmic_index][internal_resource_index].MinSettlingTime;
            }

            // if minimum settling time has elapsed, only then check for VREG_OK ow call back to RPM server
            if (settling_time_elapsed_us >= min_settling_time_us)
            {
                // Check for VREG_OK status
                pm_pwr_is_vreg_ready_alg(&boost_ptr->pm_pwr_data, boost_ptr->comm_ptr, internal_resource_index, &vreg_status);

                if(vreg_status == FALSE)
                {
                    // if the rail finished settling due to a different request and still 
                    // VREG_OK is not high then give the rail some more time to settle internally
                    if(settle_start_time == 0)
                    {
                       // save the current time as settling start time
                       boost_data->settlingInfo[internal_resource_index].settle_start_time = current_time;

                       // calculate the settle end time using the settling time threshold
                       boost_data->settlingInfo[internal_resource_index].settle_end_time = 
                                  current_time + pm_convert_time_to_timetick(PM_RPM_SETTTLING_TIME_THRESHOLD);

                       // poll for VREG_OK to continue settling
                       pm_rpm_boost_settle(info);
                    }
                    else if(current_time < settle_end_time) // still need more time to settle
                    {
                        // calculate the remaining settling time in micro secs
                        settling_time_remaining_us = pm_convert_timetick_to_time(settle_end_time - current_time);

                        // if the remaining settling time is small enough, wait internally
                        if(settling_time_remaining_us < PM_RPM_SETTTLING_TIME_THRESHOLD)
                        {
                            // poll for VREG_OK to continue settling
                            pm_rpm_boost_settle(info);
                        }
                    }
                    else // estimated settling time elapsed, rail should have already settled
                    {
                        // poll for VREG_OK to continue settling
                        pm_rpm_boost_settle(info);
                    }
                }
                else // settling is done since VREG_OK status is TRUE
                {
                    estimated_time_us = pm_convert_timetick_to_time(settle_end_time - settle_start_time);
                    actual_time_us = pm_convert_timetick_to_time(current_time - settle_start_time);
                    periph_type = (&boost_ptr->pm_pwr_data)->pwr_specific_info[internal_resource_index].periph_type;

                    PM_LOG_MSG_DEBUG(PMIC_RPM_SETTLING_TIME, 
                                     PM_LOG_FORMAT_PERIPH_INFO(pmic_index, periph_type, internal_resource_index), 
                                     estimated_time_us, actual_time_us);

                    // reset the settling time values
                    info->settling_time = 0;
                    boost_data->settlingInfo[internal_resource_index].settle_end_time = 0;
                    boost_data->settlingInfo[internal_resource_index].settle_start_time = 0;
                }
            }
        }
        else // reset the settling time if the rail got disabled while settling parallely
        {
            // reset the settling time values
            info->settling_time = 0;
            boost_data->settlingInfo[internal_resource_index].settle_end_time = 0;
            boost_data->settlingInfo[internal_resource_index].settle_start_time = 0;
        }
    } //end if(0 == info->settling_time)
}

void pm_rpm_boost_dependency_execute(rpm_application_info *info, pm_npa_boost_int_rep* previous_aggregation)
{
    // Check the pre-operational dependencies
    pm_rpm_boost_pre_dependency_analysis(info, previous_aggregation);

    // Execute the driver calls once all dependencies have been executed    
    pm_rpm_boost_execute_driver(info, previous_aggregation);

    // Check the post operational dependencies
    pm_rpm_boost_post_dependency_analysis(info, previous_aggregation);
}

int pm_rpm_boost_aggregate(rpm_application_info *info)
{
    int change_detected = 0;
    pm_npa_boost_data_type* boost_data = (pm_npa_boost_data_type*)info->cb_data;
    unsigned clientType, numberOfClients;
    pm_npa_boost_int_rep* boostClientRequest;
    pm_npa_vs_int_rep* vsClientRequest;
    void* state = NULL;
    unsigned clientCount = 0;
    pm_npa_boost_int_rep aggregatedIntRep = {0};
    uint8 pmic_index = GET_PMIC_INDEX_BOOST(boost_data->resourceType);
    
    numberOfClients  = rpm_get_num_clients(info->resource_handle);
    
    /* if access not allowed, just return */
    if(boost_data->railInfo[pmic_index][info->id -1].AccessAllowed == 0)
    {
        return change_detected;
    }
    
    for(clientCount = 0; clientCount < numberOfClients; clientCount++)
    {
        rpm_get_current_request(info->resource_handle, clientCount, &clientType, (const void **)&state);        

         // EE Client and Internal BOOST clients
        if((clientType == 0) || (clientType == PM_RPM_NPA_CLIENT_BOOST_REQ))
        {
            if(boost_data->railInfo[pmic_index][info->id -1].AccessAllowed)
            {
                boostClientRequest = (pm_npa_boost_int_rep*)state;
                
                if(boostClientRequest != NULL)
                {
                    // Aggregate Software Enable
                    aggregatedIntRep.sw_en = MAX(aggregatedIntRep.sw_en, boostClientRequest->sw_en);
                    // Pin Ctrl Enable
                    aggregatedIntRep.pc_en = aggregatedIntRep.pc_en | boostClientRequest->pc_en ;
                }
            }
        }           
        else if(clientType == PM_RPM_NPA_INT_CLIENT_VS_DEPENDENT)
        {
            vsClientRequest = (pm_npa_vs_int_rep*)state;

            if( NULL != vsClientRequest)
            {
                // Aggregate Software Enable - Child needs power
                aggregatedIntRep.sw_en = MAX(aggregatedIntRep.sw_en, vsClientRequest->sw_en);

            }
        }
    }
    
    // input checking
    if(boost_data->railInfo[pmic_index][info->id -1].AlwaysOn)
    {
        aggregatedIntRep.sw_en = 1;
    }
    
    change_detected = pm_rpm_int_copy(&aggregatedIntRep, (pm_npa_boost_int_rep *)info->current_aggregation, sizeof(pm_npa_boost_int_rep));

    return change_detected;
}

void pm_rpm_boost_pre_dependency_analysis(rpm_application_info *info, pm_npa_boost_int_rep* previous_aggregation)
{
    pm_pwr_resource_dependency_info *depInfo = NULL;
    pm_npa_boost_int_rep *cur_data = (pm_npa_boost_int_rep*)info->current_aggregation;
    pm_npa_boost_data_type *cb_data = (pm_npa_boost_data_type*)info->cb_data;
    uint8 pmic_index = GET_PMIC_INDEX_BOOST(cb_data->resourceType);
    
    if(cb_data->depInfo[pmic_index] != NULL)
    {
        depInfo = &cb_data->depInfo[pmic_index][info->id];
    }

    if ((depInfo != NULL) && (depInfo->parent_source_dependency != NULL))
    {
        // Detect if this is a pre-operation change on the parent
        // These conditions are
        // If the BOOST goes from a disabled to an enabled state
    
        if( cur_data->sw_en > previous_aggregation->sw_en )
        {
            rpm_issue_request(depInfo->parent_source_dependency->resource_type, 
                depInfo->parent_source_dependency->internal_resource_index, 
                depInfo->parent_source_dependency_client_handle,
                sizeof(pm_npa_boost_int_rep), info->current_aggregation);
        } 
     }
}

void pm_rpm_boost_post_dependency_analysis(rpm_application_info *info, pm_npa_boost_int_rep* previous_aggregation)
{
    pm_pwr_resource_dependency_info *depInfo = NULL;
    pm_npa_boost_int_rep *cur_data = (pm_npa_boost_int_rep*)info->current_aggregation;
    pm_npa_boost_data_type *cb_data = (pm_npa_boost_data_type*)info->cb_data;
    uint8 change_detected = 0;
    uint8 pmic_index = GET_PMIC_INDEX_BOOST(cb_data->resourceType);
    
    if(cb_data->depInfo[pmic_index] != NULL)
    {
        depInfo = &cb_data->depInfo[pmic_index][info->id];
    }

    if ((depInfo != NULL) && (depInfo->parent_source_dependency != NULL))
    {
        // Detect if this is a post-operation change on the parent
        // These conditions are
        // If the BOOST goes from a enabled to an disabled state
        if( cur_data->sw_en < previous_aggregation->sw_en )
        {
            change_detected = 1;
        }

        if(1== change_detected )
        {
            rpm_issue_request(depInfo->parent_source_dependency->resource_type, 
                depInfo->parent_source_dependency->internal_resource_index, 
                depInfo->parent_source_dependency_client_handle,
                sizeof(pm_npa_boost_int_rep), info->current_aggregation);
        }  
    }
}

void pm_rpm_boost_execute_driver(rpm_application_info *info, pm_npa_boost_int_rep* previous_aggregation)
{
    pm_npa_boost_int_rep *boost_int_rep =(pm_npa_boost_int_rep *)info->current_aggregation;
    pm_npa_boost_data_type *boost_data = (pm_npa_boost_data_type *)info->cb_data;
    pm_boost_data_type* boost_ptr = NULL;
    uint64 curr_settle_start_time = 0;
    uint64 prev_settle_start_time = 0;
    uint64 curr_settle_end_time = 0;
    uint64 prev_settle_end_time = 0;
    uint32 estimated_settling_time_us = 0;
    uint32 min_settling_time_us = 0;
    uint8 internal_resource_index = (uint8)(info->id - 1);
    uint8 pmic_index = GET_PMIC_INDEX_BOOST(boost_data->resourceType);
    
    boost_ptr = boost_data->boostDriverData;

    if(boost_ptr != NULL)
    {            
        /* State set */
        
        pm_pwr_sw_en_pin_ctl_alg(&boost_ptr->pm_pwr_data, boost_ptr->comm_ptr, internal_resource_index,
                                             (pm_on_off_type) boost_int_rep->sw_en,  boost_int_rep->pc_en); 
               
        if(boost_int_rep->sw_en > previous_aggregation->sw_en ||  
        	         boost_int_rep->pc_en != 0 )
        {
           // get the minimum settling time from config if rail is enabling
           min_settling_time_us = boost_data->railInfo[pmic_index][internal_resource_index].MinSettlingTime;

           // calculate the estimated settling time
           estimated_settling_time_us = MAX(boost_data->settlingInfo[internal_resource_index].vreg_ok_us, min_settling_time_us);
        }
        // -------------- Settling time ------------------

        // Get the previous settle start time to check if rail is already settling
        prev_settle_start_time = boost_data->settlingInfo[internal_resource_index].settle_start_time;

        // Check if rail has to settle or not
        if(((estimated_settling_time_us != 0) || (prev_settle_start_time != 0)) && 
           (boost_int_rep->sw_en != 0) &&
           (boost_data->railInfo[pmic_index][internal_resource_index].SettlingEnabled == PM_SETTLING_EN))
        {
           // get the current settle start time
           curr_settle_start_time = time_service_now();

           // if the rail is not already settling
           if(prev_settle_start_time == 0)
           {
              // Update the current settling start time
              boost_data->settlingInfo[internal_resource_index].settle_start_time = curr_settle_start_time;

              // calculate the current settle end time
              curr_settle_end_time = curr_settle_start_time + pm_convert_time_to_timetick(estimated_settling_time_us);
           }
           else // rail is already settling
           {
              // Get the previous settle end time
              prev_settle_end_time = boost_data->settlingInfo[internal_resource_index].settle_end_time;

              // check if current request needs any settling
              if(estimated_settling_time_us != 0)
              {
                 // calculate the current settle end time
                 curr_settle_end_time = curr_settle_start_time + pm_convert_time_to_timetick(estimated_settling_time_us);

                 // Use the MAX of current and previous settle end times as current
                 curr_settle_end_time = MAX(curr_settle_end_time, prev_settle_end_time);

                 // Calculate the new estimated settling time
                 estimated_settling_time_us = pm_convert_timetick_to_time(curr_settle_end_time - prev_settle_start_time);
              }
              else // current request needs no settling
              {
                 // Use the prev settle end time as current
                 curr_settle_end_time = prev_settle_end_time;

                 // Use the previous estimated settling time
                 estimated_settling_time_us = pm_convert_timetick_to_time(prev_settle_end_time - prev_settle_start_time);
              }
           }

           // save the timestamp at which rail is estimated to be settled in RPM info struct and internal struct
           boost_data->settlingInfo[internal_resource_index].settle_end_time = curr_settle_end_time;
           info->settling_time = curr_settle_end_time;

           // if the estimated settling time is less than threshold or client is internal, settle internally
           if((estimated_settling_time_us < PM_RPM_SETTTLING_TIME_THRESHOLD) || 
              (info->client_type == PM_RPM_NPA_CLIENT_BOOST_REQ) || 
              (info->client_type == PM_RPM_NPA_INT_CLIENT_VS_DEPENDENT))
           {
              // busywait for minimum settling time if any, updated only for enabling rails
              if(min_settling_time_us != 0)
              {
                 DALSYS_BusyWait(min_settling_time_us);
              }

              // internal settling
              pm_rpm_boost_settle(info);
           }
        }

        // -------------- Settling time ------------------
    }
}

__attribute__((section("pm_dram_reclaim_pool")))
void pm_rpm_boost_register_resources(rpm_resource_type resourceType, uint32 num_npa_resources, uint8 pmic_index)
{
    pm_npa_boost_data_type *boost_data = NULL;
    pm_boost_data_type *boost_ptr = NULL;
    uint32 *vreg_ok_time = NULL;   
    uint32 boost_index = 0;
        
    if(num_npa_resources > 0 )
    {
         //return if there was no driver initialized for this pmic 
         boost_ptr = pm_boost_get_data(pmic_index);
         if(boost_ptr == NULL)
         {
            return; 
         }
     
         boost_data = pm_rpm_boost_get_resource_data(pmic_index);
         if(boost_data == NULL)
         {
            pm_malloc( sizeof(pm_npa_boost_data_type), (void**)&boost_data);
         
            boost_data->boostDriverData = boost_ptr;
            boost_data->resourceType = resourceType;
            boost_data->depInfo = (pm_pwr_resource_dependency_info**)pm_target_information_get_specific_info(PM_PROP_BOOST_DEP);
            CORE_VERIFY_PTR(boost_data->depInfo);
            boost_data->railInfo = (pm_rpm_boost_rail_info_type**)pm_target_information_get_specific_info(PM_PROP_BOOST_RAIL);
            CORE_VERIFY_PTR(boost_data->railInfo);

            vreg_ok_time = (uint32*)pm_target_information_get_common_info(PM_PROP_BOOST_VREG_OK_TIME);
            CORE_VERIFY_PTR(vreg_ok_time);

            pm_malloc(sizeof(pm_pwr_settling_info_type)*num_npa_resources, (void**)&(boost_data->settlingInfo));

            for( boost_index = 0; boost_index < num_npa_resources ; boost_index++)
            {
                 //skip over invalid peripherals
                 if(boost_ptr->pm_pwr_data.pwr_specific_info[boost_index].periph_type == 0)
                 {
                     continue;
                 }

                 boost_data->settlingInfo[boost_index].vreg_ok_us = vreg_ok_time[0];
            }

            rpm_register_resource(resourceType, num_npa_resources + 1 , sizeof(pm_npa_boost_int_rep), pm_rpm_boost_translation, pm_rpm_boost_apply, (void *)boost_data);
            pm_rpm_boost_req_data[pmic_index] = boost_data;
        }
    }
}

__attribute__((section("pm_dram_reclaim_pool")))
void pm_rpm_boost_register_resource_dependencies(rpm_resource_type resourceType, uint32 num_npa_resources, uint8 pmic_index)
{
    uint8 count = 0;
    pm_pwr_resource *dependency = NULL;
    pm_pwr_resource_dependency_info *depInfo = NULL;
    pm_npa_boost_int_rep *current_agg = NULL;
    pm_boost_data_type* boost_ptr = NULL;
    pm_on_off_type en_status = PM_OFF;
    pm_npa_boost_data_type *boost_data = NULL;
      
    if(num_npa_resources > 0)
    {
         //return if there was no driver initialized for this pmic  
        if(pm_rpm_boost_req_data[pmic_index] == NULL)
        	return;

        boost_data = pm_rpm_boost_req_data[pmic_index];
        
        if(boost_data->depInfo != NULL)
        {
            depInfo = boost_data->depInfo[pmic_index];
        }
       
        for(count = 1; count < num_npa_resources + 1; count++)
        {
            rpm_get_aggregated_request_buffer(resourceType, count, (const void**)&current_agg);
            if(current_agg != NULL)
            {
                boost_ptr = boost_data->boostDriverData;
                CORE_VERIFY_PTR(boost_ptr);
                DALSYS_memset(current_agg, 0, sizeof(pm_npa_boost_int_rep));
                //skip over invalid peripherals
                if(boost_ptr->pm_pwr_data.pwr_specific_info[count-1].periph_type == 0)
                {
                    continue;
                }
                pm_pwr_sw_enable_status_alg(&boost_ptr->pm_pwr_data, boost_ptr->comm_ptr, count-1, &en_status);
                current_agg->sw_en = en_status;
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
                    rpm_register_internal_client_type(dependency->resource_type, dependency->internal_resource_index, PM_RPM_NPA_INT_CLIENT_BOOST_DEPENDENT, sizeof(pm_npa_boost_int_rep));
                    
                    depInfo[count].parent_source_dependency_client_handle = 
                        rpm_create_client(dependency->resource_type, dependency->internal_resource_index, PM_RPM_NPA_INT_CLIENT_BOOST_DEPENDENT);                   
                }

                //pm_rpm_register_operational_dependency_int_client(&depInfo[count]);
            }
        }
    }  
}


pm_npa_boost_data_type* pm_rpm_boost_get_resource_data(uint8 pmic_index)
{
		  if(pmic_index < PM_MAX_NUM_PMICS) 
		  {
		    return  pm_rpm_boost_req_data[pmic_index];
		  }

		  return NULL;
}

void pm_rpm_boost_settle(rpm_application_info *info)
{
    pm_npa_boost_data_type *boost_data = (pm_npa_boost_data_type *)info->cb_data;
    uint8  internal_resource_index = (uint8)(info->id - 1);
    uint64 settle_start_time = boost_data->settlingInfo[internal_resource_index].settle_start_time;
    uint64 settle_end_time = boost_data->settlingInfo[internal_resource_index].settle_end_time;
    uint32 estimated_settling_time_us = 0;
    pm_boost_data_type* boost_ptr = NULL;
    uint8 pmic_index = GET_PMIC_INDEX_BOOST(boost_data->resourceType);

    if(settle_start_time != 0)
    {
        // calculate the estimated settling time in micro secs
        estimated_settling_time_us = pm_convert_timetick_to_time(settle_end_time - settle_start_time);

        // Get the driver data from the info call back data
        boost_ptr = boost_data->boostDriverData;

        CORE_VERIFY_PTR(boost_ptr);

        // poll VREG_OK
        pm_rpm_check_vreg_settle_status(settle_start_time, estimated_settling_time_us, &boost_ptr->pm_pwr_data, 
                                        boost_ptr->comm_ptr, internal_resource_index, 
                                        boost_data->railInfo[pmic_index][info->id -1].SettlingErrorEnabled);

        // reset the settling time values
        info->settling_time = 0;
        boost_data->settlingInfo[internal_resource_index].settle_end_time = 0;
        boost_data->settlingInfo[internal_resource_index].settle_start_time = 0;
    }
}




