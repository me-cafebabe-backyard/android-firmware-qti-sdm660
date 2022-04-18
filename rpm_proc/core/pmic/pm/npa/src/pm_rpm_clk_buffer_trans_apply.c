/*! \file pm_rpm_clk_buffer_trans_apply.c
 *  \n
 *  \brief This file contains implementation for PMIC CLOCKS Translation
 *         and Apply (Aggregate) functions.
 *  \n
 *  \n &copy; Copyright 2012-2015 QUALCOMM Technologies Incorporated, All Rights Reserved
 */

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

$Header: //components/rel/rpm.bf/1.8/core/pmic/pm/npa/src/pm_rpm_clk_buffer_trans_apply.c#1 $  

when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
03/13/14   kt      Handle AlwaysOn flag for clocks (CR-574742) 
05/29/13   aks     Clk driver input check (do not disable critical clocks) 
05/17/13   hs      PMIC SWEVENT revise.
04/12/13   hs      Code refactoring.
02/27/13   hs      Code refactoring.
04/12/12   hs      Fixed the launching of StartTransaction.
                   Fixed the internal resource indexing.
04/09/12   hs      Added missing implementation.
01/26/12   wra     Created.
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "npa.h"
#include "npa_resource.h"
#include "rpmserver.h"

#include "pm_target_information.h"
#include "pm_rpm_clk_buffer_trans_apply.h"
#include "pm_npa_device_clk_buff.h"
#include "CoreVerify.h"
#include "device_info.h"
#include "pm_config.h"
#include "pm_debug.h"

/*===========================================================================

                        TYPE DEFINITIONS 

===========================================================================*/

pm_clk_settle_info_type pm_settle_clk_ok_err_info;

static pm_npa_clk_buffer_data_type *pm_rpm_clk_buffer_req_data[PM_MAX_NUM_PMICS];

void pm_rpm_clk_buffer_translation(rpm_translation_info *pm_rpm_clk_buffer_translation_info);
void pm_rpm_clk_buffer_apply(rpm_application_info *pm_rpm_clk_buffer_application_info);
void pm_rpm_clk_buffer_pre_dependency_analysis(rpm_application_info *info, pm_npa_clk_buffer_int_rep *previous_aggregation);
void pm_rpm_clk_buffer_post_dependency_analysis(rpm_application_info *info, pm_npa_clk_buffer_int_rep *previous_aggregation);
int pm_rpm_clk_buffer_aggregate(rpm_application_info *info);
void pm_rpm_clk_buffer_execute_driver(rpm_application_info *info, pm_npa_clk_buffer_int_rep *previous_aggregation);
pm_npa_clk_buffer_data_type* pm_rpm_clk_buffer_get_resource_data(uint8 pmic_index);
static void pm_rpm_clk_buffer_settle(rpm_application_info *info);

void pm_rpm_clk_buffer_translation(rpm_translation_info *info)
{ 
    unsigned type, length, *value;
    pm_npa_clk_buffer_data_type* clk_data = (pm_npa_clk_buffer_data_type*)info->cb_data;
    pm_clk_data_type *clk_ptr = NULL;
    
    CORE_VERIFY_PTR(clk_data);
    clk_ptr = clk_data->clkBuffDriverData;
    CORE_VERIFY_PTR(clk_ptr);

    // Return for invalid PMIC resource ids. PMIC resource id 0 is invalid.
    if((info->id == 0) || (info->id > clk_ptr->num_of_peripherals))
    {
        return;  
    }

    ((pm_npa_clk_buffer_int_rep *)(info->dest_buffer))->reserved = 0;

    while(kvp_get(info->new_kvps, &type, &length, (const char **)&value))
    {
        // Need size to match.
        if(sizeof(npa_resource_state) != length)
            continue;

        switch(type)
        {
        case PM_NPA_KEY_SOFTWARE_ENABLE:
            {
                ((pm_npa_clk_buffer_int_rep *)(info->dest_buffer))->sw_enable = (uint8)*value;

                break;
            }
        case PM_NPA_KEY_PIN_CTRL_CLK_BUFFER_ENABLE_KEY:
            {
                ((pm_npa_clk_buffer_int_rep *)(info->dest_buffer))->pc_enable = (uint8)*value;
                break;
            }
        default:
            {
                //should never go here
            }
        }
    }
}

void pm_rpm_clk_buffer_apply(rpm_application_info *info)
{
    int change_detected = 0;
    pm_npa_clk_buffer_int_rep previous_aggregation = *((pm_npa_clk_buffer_int_rep*)(info->current_aggregation));
    pm_npa_clk_buffer_data_type* clk_data = (pm_npa_clk_buffer_data_type*)info->cb_data;
    pm_clk_data_type *clk_ptr = NULL;
	uint64  current_time = 0;
    uint64  settle_start_time = 0;
    uint64  settle_end_time = 0;
    uint32  settling_time_remaining_us = 0;
    pm_on_off_type clk_ok = PM_OFF;
    uint8   pmic_index = 0;
    uint8   driver_resource_index = (uint8)(info->id);
    uint8   npa_resource_index = (uint8)(info->id - 1);
    pm_npa_clk_buffer_int_rep *curr_aggr = NULL;
    
    CORE_VERIFY_PTR(clk_data);
    clk_ptr = clk_data->clkBuffDriverData;
    CORE_VERIFY_PTR(clk_ptr);

    // Return for invalid PMIC resource ids. PMIC resource id 0 is invalid.
    if((info->id == 0) || (info->id > clk_ptr->num_of_peripherals))
    {
        return;  
    }

    pmic_index = GET_PMIC_INDEX_CLK(clk_data->resourceType);
    CORE_VERIFY(pmic_index < PM_MAX_NUM_PMICS);

    if(0 == info->settling_time) //  this is a new request
    {
        // Aggregate the results, but don't call driver
        change_detected = pm_rpm_clk_buffer_aggregate(info);

        if( change_detected != 0 )
        {
            // Check the dependencies
            pm_rpm_clk_buffer_pre_dependency_analysis(info, &previous_aggregation);

            // Execute the driver calls once all dependencies have been executed  
            pm_rpm_clk_buffer_execute_driver(info, &previous_aggregation);

            pm_rpm_clk_buffer_post_dependency_analysis(info, &previous_aggregation);
        }
    }
    else
    {
        // Check the current aggregation to see if the clk got disabled while settling parallely
        curr_aggr = (pm_npa_clk_buffer_int_rep*)info->current_aggregation;

        if(curr_aggr->sw_enable != 0)
        {
           settle_start_time = clk_data->settlingInfo[npa_resource_index].settle_start_time;
           settle_end_time = clk_data->settlingInfo[npa_resource_index].settle_end_time;

           // take the current system time in time tick
           current_time = time_service_now();

           // Check for CLK_OK status
           pm_clk_ok_status(pmic_index, clk_ptr->clk_common[driver_resource_index], &clk_ok);

           if(clk_ok != PM_ON)
           {
              // if the clk finished settling due to a different request and still 
              // CLK_OK is not high then give the clk some more time to settle internally
              if(settle_start_time == 0)
              {
                 // save the current time as settling start time
                 clk_data->settlingInfo[npa_resource_index].settle_start_time = current_time;

                 // calculate the settle end time using the settling time threshold
                 clk_data->settlingInfo[npa_resource_index].settle_end_time = 
                    current_time + pm_convert_time_to_timetick(PM_RPM_SETTTLING_TIME_THRESHOLD);

                 // poll for CLK_OK to continue settling
                 pm_rpm_clk_buffer_settle(info);
              }
              else if(current_time < settle_end_time) // still need more time to settle
              {
                 // calculate the remaining settling time in micro secs
                 settling_time_remaining_us = pm_convert_timetick_to_time(settle_end_time - current_time);

                 // if the remaining settling time is small enough, wait internally
                 if(settling_time_remaining_us < PM_RPM_SETTTLING_TIME_THRESHOLD)
                 {
                    // poll for CLK_OK to continue settling
                    pm_rpm_clk_buffer_settle(info);
                 }
              }
              else // estimated settling time elapsed, clk should have already settled
              {
                 // poll for CLK_OK to continue settling
                 pm_rpm_clk_buffer_settle(info);
              }
           }
           else // settling is done since CLK_OK status is ON
           {
              // reset the settling time values
              info->settling_time = 0;
              clk_data->settlingInfo[npa_resource_index].settle_end_time = 0;
              clk_data->settlingInfo[npa_resource_index].settle_start_time = 0;
           }
        }
        else // reset the settling time if the clk got disabled while settling parallely
        {
            // reset the settling time values
            info->settling_time = 0;
            clk_data->settlingInfo[npa_resource_index].settle_end_time = 0;
            clk_data->settlingInfo[npa_resource_index].settle_start_time = 0;
        }
    } //end if(0 == info->settling_time)
}

int pm_rpm_clk_buffer_aggregate(rpm_application_info *info)
{
    int change_detected = 0;
    // get the resource type from the info->cb_data
    pm_npa_clk_buffer_data_type* cb_data = (pm_npa_clk_buffer_data_type*)info->cb_data;
   
    unsigned numberOfClients = rpm_get_num_clients(info->resource_handle);
    unsigned clientCount = 0;
    // For each client aggregate the correct values.
    pm_npa_clk_buffer_int_rep aggregatedIntRep = {0};
    uint8 pmic_index = GET_PMIC_INDEX_CLK(cb_data->resourceType);

    //if access not allowed , just return
    if(cb_data->clkInfo[pmic_index][info->id - 1].AccessAllowed == 0)
    {
        return change_detected;
    }

    for(clientCount = 0; clientCount < numberOfClients; clientCount++)
    {
        unsigned clientType;
        pm_npa_clk_buffer_int_rep* clientRequest;     
        void* state = NULL;
        rpm_get_current_request(info->resource_handle, clientCount, &clientType, (const void **)&state);   

        // EE Client and Internal CLK clients
        if((clientType == 0) || (clientType == PM_RPM_NPA_CLIENT_CLK_BUFFER_REQ )) 
        {
            clientRequest = (pm_npa_clk_buffer_int_rep*)state;

            if(clientRequest != NULL)
            {
                
                // Aggregate Software Enable
                aggregatedIntRep.sw_enable = MAX(aggregatedIntRep.sw_enable, clientRequest->sw_enable);

                // Aggregate ORed values of Pin Control Enable
                aggregatedIntRep.pc_enable = aggregatedIntRep.pc_enable | clientRequest->pc_enable;
            }
        }
    }

    /* input checking after aggregation */
    if(cb_data->clkInfo[pmic_index][info->id - 1].AlwaysOn)
    {
        /* if the clock is required to be always ON, keep it ON */
        aggregatedIntRep.sw_enable = 1;
    }

    change_detected = pm_rpm_int_copy( &aggregatedIntRep, (pm_npa_clk_buffer_int_rep *)info->current_aggregation, sizeof(pm_npa_clk_buffer_int_rep));

    return change_detected;
}

void pm_rpm_clk_buffer_pre_dependency_analysis(rpm_application_info *info, pm_npa_clk_buffer_int_rep *previous_aggregation)
{
    pm_pwr_resource_dependency_info *depInfo = NULL;
    pm_npa_clk_buffer_int_rep *cur_data = (pm_npa_clk_buffer_int_rep*)info->current_aggregation;
    pm_npa_clk_buffer_data_type *cb_data = (pm_npa_clk_buffer_data_type*)info->cb_data;
    uint8 pmic_index = GET_PMIC_INDEX_CLK(cb_data->resourceType);

    CORE_VERIFY(cb_data != NULL);
    
    if(cb_data->depInfo[pmic_index] != NULL)
    {
        depInfo = &cb_data->depInfo[pmic_index][info->id];
    }

    if ((depInfo != NULL) && (depInfo->parent_source_dependency != NULL))
    {
        // Detect if this is a pre-operation change on the parent
        // These conditions are
        // If the CLK_BUFF goes from a disabled to an enabled state
        // If the CLK_BUFF Pin Control goes from disabled to an enabled state
        if((cur_data->sw_enable > previous_aggregation->sw_enable) || 
            (cur_data->pc_enable > previous_aggregation->pc_enable))
        {
            rpm_issue_request(depInfo->parent_source_dependency->resource_type, 
                depInfo->parent_source_dependency->internal_resource_index, 
                depInfo->parent_source_dependency_client_handle,
                sizeof(pm_npa_clk_buffer_int_rep), info->current_aggregation);
        }   
    }
}

void pm_rpm_clk_buffer_post_dependency_analysis(rpm_application_info *info, pm_npa_clk_buffer_int_rep *previous_aggregation)
{
    pm_pwr_resource_dependency_info *depInfo = NULL;
    pm_npa_clk_buffer_int_rep *cur_data = (pm_npa_clk_buffer_int_rep*)info->current_aggregation;
    pm_npa_clk_buffer_data_type *cb_data = (pm_npa_clk_buffer_data_type*)info->cb_data;
    unsigned change_detected = 0;
    uint8 pmic_index = GET_PMIC_INDEX_CLK(cb_data->resourceType);

    CORE_VERIFY(cb_data != NULL);
    
    if(cb_data->depInfo[pmic_index] != NULL)
    {
        depInfo = &cb_data->depInfo[pmic_index][info->id];
    }

    if ((depInfo != NULL) && (depInfo->parent_source_dependency != NULL))
    {
        // Detect if this is a post-operation change on the parent
        // These conditions are
        // If the CLK_BUFF goes from a enabled to an disabled state
        // If the CLK_BUFF Pin Control goes from enabled to an disabled state
        if((cur_data->sw_enable < previous_aggregation->sw_enable) || 
            (cur_data->pc_enable < previous_aggregation->pc_enable))
        {
            change_detected = 1;
        }

        if(1 == change_detected)
        {
            rpm_issue_request(depInfo->parent_source_dependency->resource_type, 
                depInfo->parent_source_dependency->internal_resource_index, 
                depInfo->parent_source_dependency_client_handle,
                sizeof(pm_npa_clk_buffer_int_rep), info->current_aggregation);
        }  
    }
}

void pm_rpm_clk_buffer_execute_driver(rpm_application_info *info, pm_npa_clk_buffer_int_rep *previous_aggregation)
{
    pm_npa_clk_buffer_int_rep *clk_buffer_int_rep =(pm_npa_clk_buffer_int_rep *)info->current_aggregation;
    pm_npa_clk_buffer_data_type *clk_buffer_data = (pm_npa_clk_buffer_data_type *)info->cb_data;
    pm_clk_data_type *clk_ptr = NULL;
    uint8 pmic_index = GET_PMIC_INDEX_CLK(clk_buffer_data->resourceType);
    uint8 driver_resource_index = (uint8)(info->id);
    uint8 npa_resource_index = (uint8)(info->id - 1);
    uint64 curr_settle_start_time = 0;
    uint64 prev_settle_start_time = 0;
    uint64 curr_settle_end_time = 0;
    uint64 prev_settle_end_time = 0;
    uint64 current_time = 0;
    uint64 prev_off_time = 0;
    uint32 min_time_gap_us = 0;
    uint32 time_gap_elapsed_us = 0;
    uint32 estimated_settling_time_us = 0;
    pm_on_off_type clk_ok = PM_OFF;
        

    clk_ptr = clk_buffer_data->clkBuffDriverData;
    
    if(clk_ptr != NULL)
    {
        /* State set */
        if(clk_buffer_int_rep->sw_enable != previous_aggregation->sw_enable)
        {
            //Check if minimum time gap needs to be maintained between CLK OFF and ON
            min_time_gap_us = clk_buffer_data->clkInfo[pmic_index][npa_resource_index].MinTimeGapOffOn;

            if(min_time_gap_us != 0)
            {
               if(clk_buffer_int_rep->sw_enable > previous_aggregation->sw_enable)
               {
                  prev_off_time = clk_buffer_data->settlingInfo[npa_resource_index].prev_off_time;

                  if(prev_off_time != 0)
                  {
                     current_time = time_service_now();

                     // Calculate the time gap elapsed from previous CLK OFF
                     time_gap_elapsed_us = pm_convert_timetick_to_time(current_time - prev_off_time);

                     // If the minimum time gap between OFF and ON is greater 
                     // than elapsed time gap then wait for remaining time
                     if(min_time_gap_us > time_gap_elapsed_us)
                     {
                        // Wait for remaining time
                        DALSYS_BusyWait(min_time_gap_us - time_gap_elapsed_us);
                     }

                     clk_buffer_data->settlingInfo[npa_resource_index].prev_off_time = 0;
                  }
               }
               else
               {
                  // save the clock disable timestamp
                  clk_buffer_data->settlingInfo[npa_resource_index].prev_off_time = time_service_now();
               }
            }

            pm_clk_sw_enable(pmic_index, clk_ptr->clk_common[driver_resource_index], (pm_on_off_type)(clk_buffer_int_rep->sw_enable));
            
            if(clk_buffer_int_rep->sw_enable > previous_aggregation->sw_enable)
            {
               // Check twice if CLK_OK is already HIGH before starting to settling
               pm_clk_ok_status(pmic_index, clk_ptr->clk_common[driver_resource_index], &clk_ok);

               if (clk_ok != PM_ON)
               {
                  // Wait for 10 micro secs and check CLK_OK again
                  DALSYS_BusyWait(10);

                  pm_clk_ok_status(pmic_index, clk_ptr->clk_common[driver_resource_index], &clk_ok);
               }

               if (clk_ok != PM_ON)
               {
                  // calculate the estimated settling time
                  estimated_settling_time_us = clk_buffer_data->settlingInfo[npa_resource_index].clk_ok_us;
               }
            }
        }

        /* Set PIN Control */
        if(clk_buffer_int_rep->pc_enable != previous_aggregation->pc_enable)
        {
            pm_clk_pin_ctrled(pmic_index, clk_ptr->clk_common[driver_resource_index], (pm_on_off_type)(clk_buffer_int_rep->pc_enable));
        }

        // -------------- Settling time ------------------

        // Get the previous settle start time to check if clk is already settling
        prev_settle_start_time = clk_buffer_data->settlingInfo[npa_resource_index].settle_start_time;

        // Check if clk has to settle or not
        if(((estimated_settling_time_us != 0) || (prev_settle_start_time != 0)) && 
           (clk_buffer_int_rep->sw_enable != 0) && 
           (clk_buffer_data->clkInfo[pmic_index][npa_resource_index].SettlingEnabled == PM_SETTLING_EN))
        {
           // get the current settle start time
           curr_settle_start_time = time_service_now();

           // if the clk is not already settling
           if(prev_settle_start_time == 0)
           {
              // Update the current settling start time
              clk_buffer_data->settlingInfo[npa_resource_index].settle_start_time = curr_settle_start_time;

              // calculate the current settle end time
              curr_settle_end_time = curr_settle_start_time + pm_convert_time_to_timetick(estimated_settling_time_us);
           }
           else // clock is already settling
           {
              // Get the previous settle end time
              prev_settle_end_time = clk_buffer_data->settlingInfo[npa_resource_index].settle_end_time;

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

           // save the timestamp at which clk is estimated to be settled in RPM info struct and internal struct
           clk_buffer_data->settlingInfo[npa_resource_index].settle_end_time = curr_settle_end_time;
           info->settling_time = curr_settle_end_time;

           // if the estimated settling time is less than threshold or client is internal, settle internally
           if((estimated_settling_time_us < PM_RPM_SETTTLING_TIME_THRESHOLD) || 
              (info->client_type == PM_RPM_NPA_CLIENT_CLK_BUFFER_REQ))
           {
              // internal settling
              pm_rpm_clk_buffer_settle(info);
           }
        }

        // -------------- Settling time ------------------
    }
}

__attribute__((section("pm_dram_reclaim_pool")))
void pm_rpm_clk_buffer_register_resources(rpm_resource_type resourceType, uint32 num_npa_resources, uint8 pmic_index)
{
    pm_npa_clk_buffer_data_type *clk_buffer_data = NULL;
    pm_clk_data_type            *clk_ptr = NULL;        
    uint32                      *clk_ok_time = NULL;
    uint32                      clk_index = 0;
    
    if(num_npa_resources > 0)
    {
        clk_ptr = pm_clk_get_data(pmic_index);
        //return if the clk driver is not initialized 
        if(clk_ptr == NULL)
        	return;

        
        clk_buffer_data = pm_rpm_clk_buffer_get_resource_data(pmic_index);
        if(clk_buffer_data == NULL)
        {   
            pm_malloc( sizeof(pm_npa_clk_buffer_data_type), (void**)&clk_buffer_data);
            
            clk_buffer_data->clkBuffDriverData = clk_ptr;
            clk_buffer_data->resourceType = resourceType;
            clk_buffer_data->depInfo = (pm_pwr_resource_dependency_info**)pm_target_information_get_specific_info(PM_PROP_CLK_DEP);
            CORE_VERIFY_PTR(clk_buffer_data->depInfo);
            clk_buffer_data->clkInfo = (pm_rpm_clk_info_type**)pm_target_information_get_specific_info(PM_PROP_CLK_INFO);
            CORE_VERIFY_PTR(clk_buffer_data->clkInfo);
            clk_ok_time = (uint32*)pm_target_information_get_common_info(PM_PROP_CLK_OK_TIME);
            CORE_VERIFY_PTR(clk_ok_time);

            pm_malloc(sizeof(pm_clk_settling_time_info_type)*num_npa_resources, (void**)&(clk_buffer_data->settlingInfo));

            for(clk_index = 0; clk_index < num_npa_resources; clk_index++)
            {
                 clk_buffer_data->settlingInfo[clk_index].clk_ok_us = clk_ok_time[0];
            }

            rpm_register_resource(resourceType, num_npa_resources + 1, sizeof(pm_npa_clk_buffer_int_rep), 
                                  pm_rpm_clk_buffer_translation, pm_rpm_clk_buffer_apply, (void *)clk_buffer_data);
            pm_rpm_clk_buffer_req_data[pmic_index] = clk_buffer_data;
        }
    }
}

__attribute__((section("pm_dram_reclaim_pool")))
void pm_rpm_clk_buffer_register_resource_dependencies(rpm_resource_type resourceType, uint32 num_npa_resources, uint8 pmic_index)
{
    uint8 count = 0;
    pm_pwr_resource *dependency = NULL;
    pm_pwr_resource_dependency_info *depInfo = NULL;
    pm_npa_clk_buffer_int_rep *current_agg = NULL;
    pm_npa_clk_buffer_data_type *clk_buffer_data = NULL;
        
    if(num_npa_resources > 0)
    {
         //return if there was no driver initialized for this pmic  
        if(pm_rpm_clk_buffer_req_data[pmic_index] == NULL)
        	return;

        clk_buffer_data = pm_rpm_clk_buffer_req_data[pmic_index];
        
        if(clk_buffer_data->depInfo != NULL)
        {
            depInfo = clk_buffer_data->depInfo[pmic_index];
        }

        for(count = 1; count < num_npa_resources+1; count++)
        {
            rpm_get_aggregated_request_buffer(resourceType, count, (const void**)&current_agg);
            if(current_agg != NULL)
            {
                DALSYS_memset(current_agg, 0, sizeof(pm_npa_clk_buffer_int_rep));
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
                    rpm_register_internal_client_type(dependency->resource_type, dependency->internal_resource_index, PM_RPM_NPA_INT_CLIENT_CLK_DEPENDENT, sizeof(pm_npa_clk_buffer_int_rep));
                    
                    depInfo[count].parent_source_dependency_client_handle = 
                                 rpm_create_client(dependency->resource_type, dependency->internal_resource_index, PM_RPM_NPA_INT_CLIENT_CLK_DEPENDENT);                   
                }

                //pm_rpm_register_operational_dependency_int_client(&depInfo[count]);
            }
        }
    } 
}

pm_npa_clk_buffer_data_type* pm_rpm_clk_buffer_get_resource_data(uint8 pmic_index)
{
    if(pmic_index < PM_MAX_NUM_PMICS) 
    {
        return  pm_rpm_clk_buffer_req_data[pmic_index];
    }

    return NULL;
}

void pm_rpm_clk_buffer_settle(rpm_application_info *info)
{
    pm_npa_clk_buffer_data_type *clk_buffer_data = (pm_npa_clk_buffer_data_type *)info->cb_data;
    pm_clk_data_type *clk_ptr = NULL;
    uint8 pmic_index = GET_PMIC_INDEX_CLK(clk_buffer_data->resourceType);
    uint8 driver_resource_index = (uint8)(info->id);
    uint8 npa_resource_index = (uint8)(info->id - 1);
    uint64 settle_start_time = clk_buffer_data->settlingInfo[npa_resource_index].settle_start_time;
    uint64 settle_end_time = clk_buffer_data->settlingInfo[npa_resource_index].settle_end_time;
    uint64 current_time = 0;
    uint32 estimated_settling_time_us = 0;
    uint32 actual_time_us = 0;
    pm_on_off_type clk_ok = PM_OFF;
    
    if(settle_start_time != 0)
    {
        // calculate the estimated settling time in micro secs
        estimated_settling_time_us = pm_convert_timetick_to_time(settle_end_time - settle_start_time);

        clk_ptr = clk_buffer_data->clkBuffDriverData;

        CORE_VERIFY_PTR(clk_ptr);

        pm_clk_ok_status(pmic_index, clk_ptr->clk_common[driver_resource_index], &clk_ok);

        while(clk_ok != PM_ON)
        {
            // Log and abort if the clk has not finished settling after
            // maximum allowed settle time
            if(current_time > settle_end_time)
            {
                actual_time_us = pm_convert_timetick_to_time(current_time - settle_start_time);

                // saving the settling info for the error case 
                pm_settle_clk_ok_err_info.settle_start_time = settle_start_time;
                pm_settle_clk_ok_err_info.actual_time_us = actual_time_us;
                pm_settle_clk_ok_err_info.estimated_time_us = estimated_settling_time_us;
                pm_settle_clk_ok_err_info.periph_subtype = clk_ptr->periph_subtype[driver_resource_index];
                pm_settle_clk_ok_err_info.periph_index = driver_resource_index;  
                pm_settle_clk_ok_err_info.pmic_index = pmic_index;

                if(clk_buffer_data->clkInfo[pmic_index][npa_resource_index].SettlingErrorEnabled == TRUE)
                {
                    CORE_VERIFY(0); // abort 
                }
                break;
            }

            // Get the current time and check if the maximum 
            // allowed settle time has elapsed
            current_time = time_service_now();

            pm_clk_ok_status(pmic_index, clk_ptr->clk_common[driver_resource_index], &clk_ok);
        }
        

        // reset the settling time values
        info->settling_time = 0;
        clk_buffer_data->settlingInfo[npa_resource_index].settle_end_time = 0;
        clk_buffer_data->settlingInfo[npa_resource_index].settle_start_time = 0;
    }
}

