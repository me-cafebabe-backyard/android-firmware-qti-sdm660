/**
 * @file:  cpr_thermal.c
 *
 * Copyright (c) 2015 by Qualcomm Technologies Incorporated. All Rights Reserved.
 *
 * $DateTime: 2016/11/03 00:13:13 $
 * $Header: //components/rel/rpm.bf/1.8/core/power/cpr/image/rpm/src/cpr_resource.c#1 $
 * $Change: 11690628 $
 */
#include "cpr_resource.h"
#include "cpr_logs.h"
#include "cpr_image.h"

//******************************************************************************
// Local Helper Functions
//******************************************************************************

void cpr_resource_xlate(rpm_translation_info *info)
{
    uint32               type, length;
    uint32               *value;
    cpr_therm_notification *req = info->dest_buffer;

    while( !kvp_eof(info->new_kvps) )
    {
        kvp_get( info->new_kvps, &type, &length, (const char **)&value);
        CPR_ASSERT(length == sizeof(req->temp));
        CPR_ASSERT(type == CPR_RESOURCE_THERM_KEY);
        req->temp = *value;
    }
}

void cpr_resource_apply(rpm_application_info *info)
{
    cpr_therm_notification* msg = (cpr_therm_notification*)info->new_state;
    cpr_therm_cb cb = (cpr_therm_cb) info->cb_data;
    cb( msg->temp <= thermal_cool ? CPR_THERMAL_REGION_COLD : CPR_THERMAL_REGION_NORMAL );
}
