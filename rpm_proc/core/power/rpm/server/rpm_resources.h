/*===========================================================================

  rpm_resources.h - data models for resources

  Copyright (c) 2012 Qualcomm Technologies Incorporated.  
  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ===========================================================================*/

#ifndef RPM_RESOURCES_H
#define RPM_RESOURCES_H

#include <stdint.h>

#include "rpmserver.h"
#include "rpm_estimator.h"
#include "rpm_config.h"

enum rpm_transition_type
{
    ACTIVE_TO_SLEEP,
    SLEEP_TO_ACTIVE,
};

void resource_init(ResourceData *r, unsigned class_idx, unsigned id);

bool resource_ee_request(ResourceData *r, unsigned ee, rpm_set_type set, kvp_t *data, uint64 &settling_time);

uint64 resource_ee_transition(ResourceData *r, unsigned ee, rpm_transition_type transition);
bool resource_ee_has_transition_work(ResourceData *r, unsigned ee, rpm_transition_type transition);
bool resource_ee_has_apply_work(const ResourceData *r, const void* req0, const void* req1);

unsigned resource_num_clients(const ResourceData *r);

void resource_get_request(const ResourceData *r, unsigned client, unsigned *client_type, const void **request);

unsigned resource_create_client(ResourceData *r, unsigned client_type);
uint64 resource_client_request(ResourceData *r, unsigned client, unsigned size, void *data, uint64 settling_time);

static unsigned resource_estimate(ResourceData *r, unsigned operating_point)
{
    unsigned estimate = r->estimates[operating_point];
    if(!estimate)
    {	    
        for(int i = 0; i < NUM_CLOCK_RATES; i++)
        {		
            //if another estimate exists, use an estimate based off that but adjusted for the current operating point
            if(r->estimates[i])
            {
                Estimator  &estimator = theEstimator();
                return (((estimator.getFreqFromOperatingPoint(i) >> 10) * r->estimates[i]) / 
                         (estimator.getFreqFromOperatingPoint(operating_point) >> 10));
            }		    
        }		

        return 0x4B00; // No estimate yet, approximate ~1 ms.
    }
    else
    {	    
        return estimate;
    }	  
}

static unsigned resource_settling_estimate(ResourceData *r)
{
    return (&(rpm->classes[r->class_idx]))->settling_estimate;
}

static void resource_observe(ResourceData *r, unsigned operating_point, Observation &obs, unsigned settling_time)
{
    if(obs.time > r->estimates[operating_point])
        r->estimates[operating_point] = obs.time;

    if(settling_time > (&(rpm->classes[r->class_idx]))->settling_estimate)
        (&(rpm->classes[r->class_idx]))->settling_estimate = settling_time;
}

void resource_class_add_client_type(ResourceClassData *rc, unsigned client_type, unsigned inrep_size);

uint64 resource_ee_settling_apply(ResourceData *r, unsigned ee, uint64 settling_time);

uint64 resource_ee_settling_query(ResourceData *r, unsigned ee);

void rpm_query_npa_settling(rpm_application_info *info);

#endif // RPM_RESOURCES_H

