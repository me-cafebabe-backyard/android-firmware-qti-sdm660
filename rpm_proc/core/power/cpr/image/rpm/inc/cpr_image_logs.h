/**
 * @file:  cpr_image_logs.h
 * @brief:
 *
 * Copyright (c) 2015-2016 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * QUALCOMM Proprietary and Confidential.
 *
 * $DateTime: 2016/11/03 00:13:13 $
 * $Header: //components/rel/rpm.bf/1.8/core/power/cpr/image/rpm/inc/cpr_image_logs.h#1 $
 * $Change: 11690628 $
 */
#ifndef CPR_IMAGE_LOGS_H
#define CPR_IMAGE_LOGS_H

#include <stdbool.h>
#include "ULogFront.h"
#include "CoreVerify.h"
#include "swevent.h"
#include "cpr_data.h"

#define CPR_IMAGE_LOG_INIT()
#define CPR_IMAGE_LOG_FATAL(msg, args...)
#define CPR_IMAGE_LOG_ERROR(msg, args...)
#define CPR_IMAGE_LOG_WARNING(msg, args...)
#define CPR_IMAGE_LOG_INFO(msg, args...)
#define CPR_IMAGE_LOG_VERBOSE(msg, args...)
#define CPR_IMAGE_LOG_TRACE(msg, args...)
#define CPR_IMAGE_LOG_TRACE_RAW(msg, args...)

typedef struct
{
    unsigned mode           :  4;
    unsigned up             :  1;
    unsigned down           :  1;
    unsigned recommendation : 21;
    unsigned hit_ceiling    :  1;
    unsigned hit_floor      :  1;
    unsigned ignored        :  1;
    unsigned changed        :  1;
    unsigned ackResult      :  1;
} cpr_isr_data_t;

cpr_isr_data_t* cpr_image_log_get_entry(cpr_rail *rail);

#endif

