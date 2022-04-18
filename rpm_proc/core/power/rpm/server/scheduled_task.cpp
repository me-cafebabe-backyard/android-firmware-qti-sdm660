/*
===========================================================================

FILE:         rpm_suppressible.cpp

DESCRIPTION:


===========================================================================

                             Edit History

$Header: //components/rel/rpm.bf/1.8/core/power/rpm/server/scheduled_task.cpp#1 $
$Date: 2016/11/03 $

when       who     what, where, why
--------   ---     --------------------------------------------------------

===========================================================================
             Copyright (c) 2013 Qualcomm Technologies, Inc.
                    All Rights Reserved.
              QUALCOMM Proprietary and Confidential
===========================================================================
*/

/* -----------------------------------------------------------------------
**                           INCLUDES
** ----------------------------------------------------------------------- */

#include "comdef.h"
#include "CoreVerify.h"
#include "scheduled_task.h"
#include "time_service.h"
#include "swevent.h"

#ifdef __cplusplus
extern "C" {
#endif
void busywait (uint32 pause_time_us);
#ifdef __cplusplus
} // extern "C"
#endif

/* -----------------------------------------------------------------------
**                           DATA
** ----------------------------------------------------------------------- */

/* -----------------------------------------------------------------------
**                           FUNCTIONS
** ----------------------------------------------------------------------- */

ScheduledTask::ScheduledTask(uint8_t priority, rpm_scheduled_task_id task_id, scheduled_cb cb, 
		                         void *ctxt, uint8_t suppressible, unsigned estimate_ticks) :
    Task(priority, suppressible),
    state_(IDLE),
    taskId_(task_id),
    estimate_(estimate_ticks),
    callback_(cb)
{
    context_.client_data = ctxt;
    context_.requeue = false;
    context_.deadline = 0;
}

ScheduledTask::~ScheduledTask()
{
}

uint64_t ScheduledTask::get_length() const
{
    if(!estimate_)
      return 0x4B00; //default 1mS if task doesn't provide an initial estimate 
    else
      return estimate_;
}

uint64_t ScheduledTask::get_length_given(uint32_t systemStateIn, uint32_t &systemStateOut)
{
    //We don't necessarily know how system state will change for a given suppressible task.
    //Set to 0 for now so that no assumptions are made about system state after this task.
    //It may be possible to expand this using the estimate cache such that we aren't always
    //using worst case.
    //Assume that the suppressible task does not alter the system state.
    //Current suppressible task does not generally alter the system state and if it did, the
    //alteration adds very little to the total timeline, making the best option to assume no
    //system state change.
    systemStateOut = systemStateIn;
    return get_length();
}

void ScheduledTask::reestimate()
{
}

bool ScheduledTask::hasImmediateWork() const
{
    uint64_t deadline;

    if (get_deadline(deadline))
    {
        return ((time_service_now() + get_length()) > deadline);
    }

    return false;
}

void ScheduledTask::cancel(void)
{
    CORE_VERIFY(state_ != ACTIVE);
    state_ = IDLE;
    clear_deadline();
}

void ScheduledTask::execute_until(volatile bool &preempt, uint64_t stop_time)
{
    INTLOCK();
    uint64_t start = time_service_now();
    if (preempt || (stop_time < (start+estimate_)))
    {
        SWEVENT(RPM_PREEMPT_SCHEDULED_TASK, taskId_);	
        INTFREE();
        return;
    }

    if ((state_ == ACTIVE) || (state_ == SCHEDULED))
    {
        uint64_t end;
        state_ = ACTIVE;
        SWEVENT(RPM_EXECUTE_SCHEDULED_TASK, taskId_);	

        if (callback_)
            callback_(&context_);

        // Cleanup
        end = time_service_now();
        set_end(end);
        clear_deadline();
        // Update estimate
        estimate_ = end - start;

        SWEVENT(RPM_COMPLETE_SCHEDULED_TASK, taskId_);	
        state_ = IDLE;
        if(context_.requeue)
        {
            enqueue(context_.deadline);
        }	    
    }

    INTFREE();
}

void ScheduledTask::enqueue(uint64_t deadline)
{
    CORE_VERIFY(state_ != ACTIVE);
    state_ = SCHEDULED;
    set_deadline(deadline);
    schedule_me();
    SWEVENT(RPM_ENQUEUE_SCHEDULED_TASK, taskId_);	
}

