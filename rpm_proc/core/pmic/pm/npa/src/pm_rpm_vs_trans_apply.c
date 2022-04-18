/*! \file pm_rpm_vs_trans_apply.c
 *  \n
 *  \brief This file contains implementation for PMIC VS Translation
 *         and Apply (Aggregate) functions.
 *  \n  
 *  \n &copy; Copyright 2012-2015 QUALCOMM Technologies Incorporated, All Rights Reserved
 */

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

$Header: //components/rel/rpm.bf/1.8/core/pmic/pm/npa/src/pm_rpm_vs_trans_apply.c#1 $  

when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
06/11/13   hs      Adding settling time for regulators.
05/17/13   hs      PMIC SWEVENT revise.
04/25/13   aks     Code Refactoring: Removing PMIC_SubRsc from pwr algs 
04/12/13   hs      Code refactoring.
02/27/13   hs      Code refactoring.
02/01/12   hs      Added support for input validation. 
07/20/12   hs      Added settling time.
04/12/12   hs      Fixed the launching of StartTransaction.
                   Fixed the internal resource indexing.
01/26/12   wra     Created.
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "npa.h"
#include "rpmserver.h"
#include "pm_npa.h"

#include "pm_target_information.h"
#include "pm_rpm_vs_trans_apply.h"
#include "pm_npa_device_vs.h"
#include "CoreVerify.h"
#include "device_info.h"
#include "pm_config.h"


static pm_npa_vs_data_type *pm_rpm_vs_req_data[PM_MAX_NUM_PMICS];


void pm_rpm_vs_translation(rpm_translation_info *info);
void pm_rpm_vs_apply(rpm_application_info *info);
void pm_rpm_vs_pre_dependency_analysis(rpm_application_info *info, pm_npa_vs_int_rep *previous_aggregation);
void pm_rpm_vs_post_dependency_analysis(rpm_application_info *info, pm_npa_vs_int_rep *previous_aggregation);
int pm_rpm_vs_aggregate(rpm_application_info *info);
void pm_rpm_vs_execute_driver(rpm_application_info *info, pm_npa_vs_int_rep *previous_aggregation);
pm_npa_vs_data_type* pm_rpm_vs_get_resource_data(uint8 pmic_index);
void pm_rpm_vs_settle(rpm_application_info *info);

void pm_rpm_vs_translation(rpm_translation_info *info)
{
    unsigned type, length, *value;
    pm_npa_vs_data_type *vs_data = (pm_npa_vs_data_type*)info->cb_data;
    pm_vs_data_type     *vs_ptr = NULL;
    
    CORE_VERIFY_PTR(vs_data);
    vs_ptr = vs_data->vsDriverData;
    CORE_VERIFY_PTR(vs_ptr);

    // Return for invalid PMIC resource ids. PMIC resource id 0 is invalid.
    if((info->id == 0) || (info->id > vs_ptr->pm_pwr_data.num_of_peripherals))
    {
        return;  
    }

    ((pm_npa_vs_int_rep *)(info->dest_buffer))->reserve1 = 0;

    while(kvp_get(info->new_kvps, &type, &length, (const char **)&value))
    {
        // Need size to match.
        if(sizeof(npa_resource_state) != length)
            continue;

        switch(type)
        {
        case PM_NPA_KEY_SOFTWARE_ENABLE:
            {
                ((pm_npa_vs_int_rep *)(info->dest_buffer))->sw_en = *value;

                break;
            }
        case PM_NPA_KEY_PIN_CTRL_ENABLE:
            {
                ((pm_npa_vs_int_rep *)(info->dest_buffer))->pc_en = *value;
                break;
            }
        case PM_NPA_KEY_CURRENT:
            {
                ((pm_npa_vs_int_rep *)(info->dest_buffer))->ip = *value;
                break;
            }
        default:
            {
                //should never go here
            }
        }
    }
}

void pm_rpm_vs_apply(rpm_application_info *info)
{
    int                  change_detected = 0;
    pm_npa_vs_int_rep    previous_aggregation = *((pm_npa_vs_int_rep*)(info->current_aggregation));
	uint64               current_time = 0;
    uint64               settle_start_time = 0;
    uint64               settle_end_time = 0;
    uint32               min_settling_time_us = 0;
    uint32               settling_time_elapsed_us = 0;
    uint32               settling_time_remaining_us = 0;
    boolean              vreg_status = FALSE;
    uint8                internal_resource_index = 0;
    uint8                pmic_index = 0;
    pm_npa_vs_data_type *vs_data = (pm_npa_vs_data_type*)info->cb_data;
    pm_vs_data_type     *vs_ptr = NULL;
    pm_npa_vs_int_rep   *curr_aggr = NULL;
    uint32              actual_time_us = 0;
    uint32              estimated_time_us = 0;
    uint8               periph_type = 0;
    
    CORE_VERIFY_PTR(vs_data);

    vs_ptr = vs_data->vsDriverData;

    CORE_VERIFY_PTR(vs_ptr);

    // Return for invalid PMIC resource ids. PMIC resource id 0 is invalid.
    if((info->id == 0) || (info->id > vs_ptr->pm_pwr_data.num_of_peripherals))
    {
        return;  
    }

    internal_resource_index = (uint8)(info->id - 1);

    pmic_index = GET_PMIC_INDEX_VS(vs_data->resourceType);
    CORE_VERIFY(pmic_index < PM_MAX_NUM_PMICS);

    if(0 == info->settling_time) // this is a new request
    {
        // Aggregate the results, but don't call driver
        change_detected = pm_rpm_vs_aggregate(info);
    
        if( change_detected != 0 )
        {
            // Check the dependencies
            pm_rpm_vs_pre_dependency_analysis(info, &previous_aggregation);
    
            // Execute the driver calls once all dependencies have been executed  
            pm_rpm_vs_execute_driver(info, &previous_aggregation);
    
            // Check the dependencies
            pm_rpm_vs_post_dependency_analysis(info, &previous_aggregation);
        }
    }
    else // this is an old request to check if the rail has settled
    {
        // Check the current aggregation to see if the rail got disabled while settling parallely
        curr_aggr = (pm_npa_vs_int_rep*)info->current_aggregation;

        if(curr_aggr->sw_en != 0)
        {
            settle_start_time = vs_data->settlingInfo[internal_resource_index].settle_start_time;
            settle_end_time = vs_data->settlingInfo[internal_resource_index].settle_end_time;

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
               min_settling_time_us = vs_data->railInfo[pmic_index][internal_resource_index].MinSettlingTime;
            }

            // if minimum settling time has elapsed, only then check for VREG_OK ow call back to RPM server
            if (settling_time_elapsed_us >= min_settling_time_us)
            {
                // Check for VREG status
                pm_pwr_is_vreg_ready_alg(&vs_ptr->pm_pwr_data, vs_ptr->comm_ptr, internal_resource_index, &vreg_status);

                if(vreg_status == FALSE)
                {
                    // if the rail finished settling due to a different request and still 
                    // VREG_OK is not high then give the rail some more time to settle internally
                    if(settle_start_time == 0)
                    {
                       // save the current time as settling start time
                       vs_data->settlingInfo[internal_resource_index].settle_start_time = current_time;

                       // calculate the settle end time using the settling time threshold
                       vs_data->settlingInfo[internal_resource_index].settle_end_time = 
                                  current_time + pm_convert_time_to_timetick(PM_RPM_SETTTLING_TIME_THRESHOLD);

                       // poll for VREG_OK to continue settling
                       pm_rpm_vs_settle(info);
                    }
                    else if(current_time < settle_end_time) // still need more time to settle
                    {
                        // calculate the remaining settling time in micro secs
                        settling_time_remaining_us = pm_convert_timetick_to_time(settle_end_time - current_time);

                        // if the remaining settling time is small enough, wait internally
                        if(settling_time_remaining_us < PM_RPM_SETTTLING_TIME_THRESHOLD)
                        {
                            // poll for VREG_OK to continue settling
                            pm_rpm_vs_settle(info);
                        }
                    }
                    else // estimated settling time elapsed, rail should have already settled
                    {
                        // poll for VREG_OK to continue settling
                        pm_rpm_vs_settle(info);
                    }
                }
                else // settling is done since VREG_OK status is TRUE
                {
                    estimated_time_us = pm_convert_timetick_to_time(settle_end_time - settle_start_time);
                    actual_time_us = pm_convert_timetick_to_time(current_time - settle_start_time);
                    periph_type = (&vs_ptr->pm_pwr_data)->pwr_specific_info[internal_resource_index].periph_type;

                    PM_LOG_MSG_DEBUG(PMIC_RPM_SETTLING_TIME, 
                                     PM_LOG_FORMAT_PERIPH_INFO(pmic_index, periph_type, internal_resource_index), 
                                     estimated_time_us, actual_time_us);

                    // reset the settling time values
                    info->settling_time = 0;
                    vs_data->settlingInfo[internal_resource_index].settle_end_time = 0;
                    vs_data->settlingInfo[internal_resource_index].settle_start_time = 0;
                }
            }
        }
        else // reset the settling time if the rail got disabled while settling parallely
        {
            // reset the settling time values
            info->settling_time = 0;
            vs_data->settlingInfo[internal_resource_index].settle_end_time = 0;
            vs_data->settlingInfo[internal_resource_index].settle_start_time = 0;
        }
    } //end if(0 == info->settling_time)
}

int pm_rpm_vs_aggregate(rpm_application_info *info)
{
    int change_detected = 0;
    // get the resource type from the info->cb_data
    pm_npa_vs_data_type* vs_data = (pm_npa_vs_data_type*)info->cb_data;
    pm_npa_vs_int_rep aggregatedIntRep = {0};
    unsigned numberOfClients,clientCount,clientType ;
    pm_npa_vs_int_rep* clientRequest;
    void* state = NULL;
    uint8 pmic_index = GET_PMIC_INDEX_VS(vs_data->resourceType);

    numberOfClients = rpm_get_num_clients(info->resource_handle);
    
    if(vs_data->railInfo[pmic_index][info->id -1].AccessAllowed)
    {
        for(clientCount = 0; clientCount < numberOfClients; clientCount++)
        {
            rpm_get_current_request(info->resource_handle, clientCount, &clientType, (const void **)&state);        
            
            // EE Client and Internal VS clients
            if ((clientType == 0) || (clientType == PM_RPM_NPA_CLIENT_VS_REQ))
            {
                clientRequest = (pm_npa_vs_int_rep*)state;            
                
                if(clientRequest != NULL)
                {
                    // Aggregate Software Enable
                    aggregatedIntRep.sw_en          = MAX(aggregatedIntRep.sw_en,       clientRequest->sw_en);

                    // Aggregate ORed values of Pin Control Enable
                    aggregatedIntRep.pc_en          = aggregatedIntRep.pc_en | clientRequest->pc_en;

                    // Aggregate Summation of Current
                    aggregatedIntRep.ip             = aggregatedIntRep.ip + clientRequest->ip;
                }
            }
        }

        // input checking
        if(vs_data->railInfo[pmic_index][info->id -1].AlwaysOn)
        {
            aggregatedIntRep.sw_en = 1;
        }

        change_detected = pm_rpm_int_copy( &aggregatedIntRep, (pm_npa_vs_int_rep *)info->current_aggregation, sizeof(pm_npa_vs_int_rep));
    }// end access_allowed

    return change_detected;
}

void pm_rpm_vs_pre_dependency_analysis(rpm_application_info *info, pm_npa_vs_int_rep *previous_aggregation)
{
    pm_pwr_resource_dependency_info *depInfo = NULL;
    pm_npa_vs_int_rep *cur_data = (pm_npa_vs_int_rep*)info->current_aggregation;
    pm_npa_vs_data_type *cb_data = (pm_npa_vs_data_type*)info->cb_data;
    uint8 pmic_index = GET_PMIC_INDEX_VS(cb_data->resourceType);
    
    if(cb_data->depInfo[pmic_index] != NULL)
    {
        depInfo = &cb_data->depInfo[pmic_index][info->id];
    }

    if ((depInfo != NULL) && (depInfo->parent_source_dependency != NULL))
    {
        // Detect if this is a pre-operation change on the parent
        // These conditions are
        // If the VS goes from a disabled to an enabled state
        // If the VS Pin Control goes from disabled to an enabled state
        if( (cur_data->sw_en > previous_aggregation->sw_en) ||
            (cur_data->pc_en > previous_aggregation->pc_en) )
        {
            rpm_issue_request(depInfo->parent_source_dependency->resource_type, 
                depInfo->parent_source_dependency->internal_resource_index, 
                depInfo->parent_source_dependency_client_handle,
                sizeof(pm_npa_vs_int_rep), info->current_aggregation);
        }   
    }
}

void pm_rpm_vs_post_dependency_analysis(rpm_application_info *info, pm_npa_vs_int_rep *previous_aggregation)
{
    pm_pwr_resource_dependency_info *depInfo = NULL;
    pm_npa_vs_int_rep *cur_data = (pm_npa_vs_int_rep*)info->current_aggregation;
    pm_npa_vs_data_type *cb_data = (pm_npa_vs_data_type*)info->cb_data;
    uint8 change_detected = 0;
    uint8 pmic_index = GET_PMIC_INDEX_VS(cb_data->resourceType);
    
    if(cb_data->depInfo[pmic_index] != NULL)
    {
        depInfo = &cb_data->depInfo[pmic_index][info->id];
    }

    if ((depInfo != NULL) && (depInfo->parent_source_dependency != NULL))
    {
        // Detect if this is a post-operation change on the parent
        // These conditions are
        // If the VS goes from a enabled to an disabled state
        // If the VS Pin Control goes from enabled to an disabled state
        if((cur_data->sw_en < previous_aggregation->sw_en) ||
           (cur_data->pc_en < previous_aggregation->pc_en))
        {
            change_detected = 1;
        }

        if( 1 == change_detected)
        {
            rpm_issue_request(depInfo->parent_source_dependency->resource_type, 
                depInfo->parent_source_dependency->internal_resource_index, 
                depInfo->parent_source_dependency_client_handle,
                sizeof(pm_npa_vs_int_rep), info->current_aggregation);
        }  
    }
}

void pm_rpm_vs_execute_driver(rpm_application_info *info, pm_npa_vs_int_rep *previous_aggregation)
{
    pm_npa_vs_int_rep *vs_int_rep =(pm_npa_vs_int_rep *)info->current_aggregation;
    pm_npa_vs_data_type *vs_data = (pm_npa_vs_data_type *)info->cb_data;
    pm_vs_data_type* vs_ptr = NULL;
    uint64 curr_settle_start_time = 0;
    uint64 prev_settle_start_time = 0;
    uint64 curr_settle_end_time = 0;
    uint64 prev_settle_end_time = 0;
    uint32 estimated_settling_time_us = 0;
    uint32 min_settling_time_us = 0;
    uint8 internal_resource_index = (uint8)(info->id - 1);
    uint8 pmic_index = GET_PMIC_INDEX_VS(vs_data->resourceType);

    //Get the vs_ptr from the call back data.
    vs_ptr = vs_data->vsDriverData;
    
    if(vs_ptr != NULL)
    {
        /* Set PIN Control Enable */
        if(vs_int_rep->pc_en != previous_aggregation->pc_en)
        {
           pm_pwr_pin_ctrl_alg(&vs_ptr->pm_pwr_data, vs_ptr->comm_ptr, internal_resource_index, vs_int_rep->pc_en);    
        }

        /* State set */
        if(vs_int_rep->sw_en != previous_aggregation->sw_en)
        {
            pm_pwr_sw_enable_alg(&vs_ptr->pm_pwr_data, vs_ptr->comm_ptr, internal_resource_index, (pm_on_off_type)vs_int_rep->sw_en);

            if(vs_int_rep->sw_en > previous_aggregation->sw_en)
            {
                // get the minimum settling time from config if rail is enabling
                min_settling_time_us = vs_data->railInfo[pmic_index][internal_resource_index].MinSettlingTime;

                // calculate the estimated settling time
                estimated_settling_time_us = MAX(vs_data->settlingInfo[internal_resource_index].vreg_ok_us, min_settling_time_us);
            }
        }

        // -------------- Settling time ------------------

        // Get the previous settle start time to check if rail is already settling
        prev_settle_start_time = vs_data->settlingInfo[internal_resource_index].settle_start_time;

        // Check if rail has to settle or not
        if(((estimated_settling_time_us != 0) || (prev_settle_start_time != 0)) && 
           (vs_int_rep->sw_en != 0) &&
           (vs_data->railInfo[pmic_index][internal_resource_index].SettlingEnabled == PM_SETTLING_EN))
        {
           // get the current settle start time
           curr_settle_start_time = time_service_now();

           // if the rail is not already settling
           if(prev_settle_start_time == 0)
           {
              // Update the current settling start time
              vs_data->settlingInfo[internal_resource_index].settle_start_time = curr_settle_start_time;

              // calculate the current settle end time
              curr_settle_end_time = curr_settle_start_time + pm_convert_time_to_timetick(estimated_settling_time_us);
           }
           else // rail is already settling
           {
              // Get the previous settle end time
              prev_settle_end_time = vs_data->settlingInfo[internal_resource_index].settle_end_time;

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
           vs_data->settlingInfo[internal_resource_index].settle_end_time = curr_settle_end_time;
           info->settling_time = curr_settle_end_time;

           // if the estimated settling time is less than threshold or client is internal, settle internally
           if((estimated_settling_time_us < PM_RPM_SETTTLING_TIME_THRESHOLD) || 
              (info->client_type == PM_RPM_NPA_CLIENT_VS_REQ))
           {
              // busywait for minimum settling time if any, updated only for enabling rails
              if(min_settling_time_us != 0)
              {
                 DALSYS_BusyWait(min_settling_time_us);
              }

              // internal settling
              pm_rpm_vs_settle(info);
           }
        }

        // -------------- Settling time ------------------
    }
}

__attribute__((section("pm_dram_reclaim_pool")))
void pm_rpm_vs_register_resources(rpm_resource_type resourceType, uint32 num_npa_resources, uint8 pmic_index)
{
    pm_npa_vs_data_type *vs_data = NULL;
    pm_vs_data_type     *vs_ptr  = NULL;
    uint32 *vreg_ok_time = NULL;   
    uint32 vs_index = 0;
    
    if(num_npa_resources > 0)
    {
        vs_ptr = pm_vs_get_data(pmic_index);
        //return if driver is not initialized 
        if(vs_ptr == NULL)
        	   return;
        vs_data = pm_rpm_vs_get_resource_data(pmic_index);
        if(vs_data == NULL)
        {
            pm_malloc( sizeof(pm_npa_vs_data_type), (void**)&vs_data);
            vs_data->vsDriverData = vs_ptr;
                                
            vs_data->resourceType = resourceType;
            vs_data->depInfo = (pm_pwr_resource_dependency_info**)pm_target_information_get_specific_info(PM_PROP_VS_DEP);
            CORE_VERIFY_PTR(vs_data->depInfo);
            vs_data->railInfo = (pm_rpm_vs_rail_info_type**)pm_target_information_get_specific_info(PM_PROP_VS_RAIL);
            CORE_VERIFY_PTR(vs_data->railInfo);

            vreg_ok_time = (uint32*)pm_target_information_get_common_info(PM_PROP_VS_VREG_OK_TIME);
            CORE_VERIFY_PTR(vreg_ok_time);

            pm_malloc(sizeof(pm_pwr_settling_info_type)*num_npa_resources, (void**)&(vs_data->settlingInfo));

            for( vs_index = 0; vs_index < num_npa_resources ; vs_index++)
            {
                 //skip over invalid peripherals
                 if(vs_ptr->pm_pwr_data.pwr_specific_info[vs_index].periph_type == 0)
                 {
                     continue;
                 }

                 vs_data->settlingInfo[vs_index].vreg_ok_us = vreg_ok_time[0];
            }

            rpm_register_resource(resourceType, num_npa_resources + 1, sizeof(pm_npa_vs_int_rep), pm_rpm_vs_translation, pm_rpm_vs_apply, (void *)vs_data);        
            pm_rpm_vs_req_data[pmic_index] = vs_data;
        }
    }  
}

__attribute__((section("pm_dram_reclaim_pool")))
void pm_rpm_vs_register_resource_dependencies(rpm_resource_type resourceType, uint32 num_npa_resources, uint8 pmic_index)
{
    uint8 count = 0;
    pm_pwr_resource *dependency = NULL;
    pm_npa_vs_int_rep *current_agg = NULL;
    pm_pwr_resource_dependency_info *depInfo = NULL;
    pm_npa_vs_data_type *vs_data = NULL;
            
    if(num_npa_resources > 0)
    {
        //return if driver is not initialized
        if(pm_rpm_vs_req_data[pmic_index] == NULL)
        	   return;

        vs_data = pm_rpm_vs_req_data[pmic_index];
        if(vs_data->depInfo != NULL)
        {
            depInfo = vs_data->depInfo[pmic_index];
        }

        for(count = 1; count < num_npa_resources + 1; count++)
        {
            rpm_get_aggregated_request_buffer(resourceType, count, (const void**)&current_agg);
            if(current_agg != NULL)
            {
                DALSYS_memset(current_agg, 0, sizeof(pm_npa_vs_int_rep));
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
                    rpm_register_internal_client_type(dependency->resource_type, dependency->internal_resource_index, PM_RPM_NPA_INT_CLIENT_VS_DEPENDENT, sizeof(pm_npa_vs_int_rep));
                    
                    depInfo[count].parent_source_dependency_client_handle = 
                                 rpm_create_client(dependency->resource_type, dependency->internal_resource_index, PM_RPM_NPA_INT_CLIENT_VS_DEPENDENT);                   
                }

                //pm_rpm_register_operational_dependency_int_client(&depInfo[count]);
            }
        }
    }  
}

pm_npa_vs_data_type* pm_rpm_vs_get_resource_data(uint8 pmic_index)
{
    if(pmic_index < PM_MAX_NUM_PMICS) 
    {
        return  pm_rpm_vs_req_data[pmic_index];
    }

    return NULL;
}

void pm_rpm_vs_settle(rpm_application_info *info)
{
    pm_npa_vs_data_type *vs_data = (pm_npa_vs_data_type *)info->cb_data;
    uint8  internal_resource_index = (uint8)(info->id - 1);
    uint64 settle_start_time = vs_data->settlingInfo[internal_resource_index].settle_start_time;
    uint64 settle_end_time = vs_data->settlingInfo[internal_resource_index].settle_end_time;
    uint32 estimated_settling_time_us = 0;
    pm_vs_data_type* vs_ptr = NULL;
    uint8 pmic_index = GET_PMIC_INDEX_VS(vs_data->resourceType);

    if(settle_start_time != 0)
    {
        // calculate the estimated settling time in micro secs
        estimated_settling_time_us = pm_convert_timetick_to_time(settle_end_time - settle_start_time);

        // Get the driver data from the info call back data
        vs_ptr = vs_data->vsDriverData;

        CORE_VERIFY_PTR(vs_ptr);

        // poll VREG_OK
        pm_rpm_check_vreg_settle_status(settle_start_time, estimated_settling_time_us, &vs_ptr->pm_pwr_data, 
                                        vs_ptr->comm_ptr, internal_resource_index, 
                                        vs_data->railInfo[pmic_index][info->id -1].SettlingErrorEnabled);

        // reset the settling time values
        info->settling_time = 0;
        vs_data->settlingInfo[internal_resource_index].settle_end_time = 0;
        vs_data->settlingInfo[internal_resource_index].settle_start_time = 0;
    }
}

