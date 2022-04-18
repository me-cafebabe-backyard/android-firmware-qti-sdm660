/*
===========================================================================

FILE:         rpm_public_task.h

DESCRIPTION:


===========================================================================

                             Edit History

$Header: //components/rel/rpm.bf/1.8/core/api/power/rpm_public_task.h#1 $
$Date: 2016/11/03 $

when       who     what, where, why
--------   ---     --------------------------------------------------------

===========================================================================
             Copyright (c) 2013 Qualcomm Technologies, Inc.
                    All Rights Reserved.
              QUALCOMM Proprietary and Confidential
===========================================================================
*/

#ifndef RPM_PUBLIC_TASK_H
#define RPM_PUBLIC_TASK_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "comdef.h"
#include "rpm.h"

typedef struct
{
    //client defined callback data	
    void    *client_data;

    //should this task be requeued on completion
    bool     requeue;

    //if it is to be requeued, what is the deadline for completion
    uint64_t deadline;
} scheduled_context;

typedef void (*scheduled_cb)(scheduled_context*);

/* Scheduled task APIs */

/* Create a new scheduled task
 *
 * @params
 *   priority       - the task priority relative to other tasks in the system (defined in rpm.h)
 *   task_id        - a unique id to identify this public task (defined in rpm.h)
 *   cb             - client cb function to be called when task is run
 *   ctxt           - a client defined context for the callback (NULL if not needed0
 *   suppressible   - whether or not this task should cause a wakeup from chip sleep
 *   estimate_ticks - rough estimate of how long this task will take. 0 if unknown
 *
 * @return opaque handle to the client which needs to be passed for future API calls
*/ 
void *scheduled_task( rpm_scheduled_task_priority priority, rpm_scheduled_task_id task_id, scheduled_cb cb, 
                      void *ctxt, uint8_t suppressible, unsigned estimate_ticks);

/* Queue a scheduled task
 *
 * @params
 *   scheduled_task_handle  - opaque handle returned by scheduled_task()
 *   deadline               - QTMR value for the completion of this task
*/ 
void scheduled_task_enqueue(void *scheduled_task_handle, uint64_t deadline);

/* Cancel a currently scheduled task
 *
 * @params
 *   scheduled_task_handle  - opaque handle returned by scheduled_task()
 *   deadline               - QTMR value for the completion of this task
*/ 
void scheduled_task_cancel(void *scheduled_task_handle);

#ifdef __cplusplus
};
#endif // __cplusplus

#endif // RPM_PERIODIC_TASK_H

