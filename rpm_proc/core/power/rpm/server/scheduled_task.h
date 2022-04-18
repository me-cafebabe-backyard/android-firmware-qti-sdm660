#ifndef SCHEDULED_TASK_H
#define SCHEDULED_TASK_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/*
===========================================================================

FILE:         scheduled_task.h

DESCRIPTION:


===========================================================================

                             Edit History

$Header: //components/rel/rpm.bf/1.8/core/power/rpm/server/scheduled_task.h#1 $
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

#include "rpm_task.h"
#include "rpm_public_task.h"
#include "rpm.h"

/* -----------------------------------------------------------------------
**                           TYPES
** ----------------------------------------------------------------------- */

typedef enum
{
    IDLE,
    SCHEDULED,
    ACTIVE,
}state_t;

class ScheduledTask : public Task
{
public:
    virtual uint64_t get_length() const;
    virtual uint64_t get_length_given(uint32_t systemStateIn, uint32_t &systemStateOut);
    virtual void reestimate();
    virtual bool hasImmediateWork() const;
    virtual void enqueue(uint64_t deadline = 0);
    void cancel(void);

    inline void set_cb(scheduled_cb, void*);
    inline void remove_cb(void);

    ScheduledTask(uint8_t priority, rpm_scheduled_task_id task_id, scheduled_cb cb, void *ctxt = NULL, 
		        uint8_t suppressible = 1, unsigned estimate_ticks = 0);
    virtual ~ScheduledTask ();

    state_t                   state_;
    rpm_scheduled_task_id  taskId_;
    uint64_t                  estimate_;
    scheduled_cb              callback_;
    scheduled_context         context_;

private:
    virtual void execute_until(volatile bool &preempt, uint64_t stop_time);
};

inline void ScheduledTask::set_cb(scheduled_cb cb, void *ctxt = NULL)
{
    callback_ = cb;
    context_.client_data = ctxt;
    context_.requeue = false;
    context_.deadline = 0;
}

inline void ScheduledTask::remove_cb(void)
{
    callback_ = NULL;
    context_.client_data = NULL;
    context_.requeue = false;
    context_.deadline = 0;
}

#ifdef __cplusplus
};
#endif // __cplusplus

#endif /* SCHEDULED_TASK_H */

