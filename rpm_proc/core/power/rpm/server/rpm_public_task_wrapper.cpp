/*
===========================================================================

FILE:         rpm_suppressible.cpp

DESCRIPTION:


===========================================================================

                             Edit History

$Header: //components/rel/rpm.bf/1.8/core/power/rpm/server/rpm_public_task_wrapper.cpp#1 $
$Date: 2016/11/03 $

when       who     what, where, why
--------   ---     --------------------------------------------------------

===========================================================================
             Copyright (c) 2013 Qualcomm Technologies, Inc.
                    All Rights Reserved.
              QUALCOMM Proprietary and Confidential
===========================================================================
*/

#include <stdlib.h>
#include "comdef.h"
#include "rpm_public_task.h"
#include "scheduled_task.h"

//Scheduled public APIs
void * scheduled_task( rpm_scheduled_task_priority priority, rpm_scheduled_task_id task_id, scheduled_cb cb,
		           void *ctxt, uint8_t suppressible, unsigned estimate_ticks)
{
    ScheduledTask *ST = new ScheduledTask((uint8_t)priority, task_id, cb, ctxt, suppressible, estimate_ticks);
    return (void *)ST;    
}

void scheduled_task_enqueue(void *scheduled_task_handle, uint64_t deadline)
{
   ((ScheduledTask*)scheduled_task_handle)->enqueue(deadline);
}

void scheduled_task_cancel(void *scheduled_task_handle)
{
   ((ScheduledTask*)scheduled_task_handle)->cancel();
}

