/**
 * @file:  cpr_image_logs.c
 *
 * Copyright (c) 2015-2016 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * QUALCOMM Proprietary and Confidential.
 *
 * $DateTime: 2017/02/15 22:06:11 $
 * $Header: //components/rel/rpm.bf/1.8/core/power/cpr/image/rpm/src/cpr_image_logs.c#2 $
 * $Change: 12459999 $
 */

#include "cpr_image_defs.h"
#include "cpr_image_logs.h"
#include "time_service.h"

#ifndef CPR_IMAGE_LOG_NUM_CLOSED_LOOP_RAILS
#define CPR_IMAGE_LOG_NUM_CLOSED_LOOP_RAILS 2
#endif

#ifndef CPR_IMAGE_LOG_SIZE
#define CPR_IMAGE_LOG_SIZE 8
#endif


typedef struct
{
    uint32         timestamp[2]; /* use two 32-bit instead of 64-bit to avoid 64-bit alignment */
    cpr_isr_data_t data;
} cpr_isr_log_t;

typedef struct
{
    cpr_domain_id id;
    uint8         idx;
    cpr_isr_log_t logs[CPR_IMAGE_LOG_SIZE];
} cpr_stats_t;


/*
 * Define the log data in the CPR_STATS region defined in rpm.scl file.
 */
__attribute__((section("cpr_stats")))
static cpr_stats_t cpr_stats[CPR_IMAGE_LOG_NUM_CLOSED_LOOP_RAILS] =
{
    { .id = CPR_RAIL_CX },
 	{ .id = CPR_RAIL_LPI_CX },
};


cpr_isr_data_t* cpr_image_log_get_entry(cpr_rail *rail)
{
    for(int i = 0; i < CPR_IMAGE_LOG_NUM_CLOSED_LOOP_RAILS; i++)
    {
        cpr_stats_t *stats = &cpr_stats[i];

        if(stats->id == rail->id)
        {
            cpr_isr_log_t *log;

            stats->idx++;

            if(stats->idx >= CPR_IMAGE_LOG_SIZE)
            {
                stats->idx = 0;
            }

            log = &stats->logs[stats->idx];

            *(uint64*)&log->timestamp = time_service_now();
            *(uint32*)&log->data      = 0;

            return &log->data;
        }
    }

    /*
     * Requested rail is not supported.
     */
    CPR_ASSERT(0);
    return NULL;
}

