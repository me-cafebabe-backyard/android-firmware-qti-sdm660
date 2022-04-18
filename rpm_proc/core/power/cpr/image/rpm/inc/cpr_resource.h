/**
 * @file:  cpr_resource.h
 * @brief:
 *
 * Copyright (c) 2015-2016 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * QUALCOMM Proprietary and Confidential.
 *
 * $DateTime: 2016/11/03 00:13:13 $
 * $Header: //components/rel/rpm.bf/1.8/core/power/cpr/image/rpm/inc/cpr_resource.h#1 $
 * $Change: 11690628 $
 */
#ifndef CPR_RESOURCE_H
#define	CPR_RESOURCE_H

#include "cpr_types.h"
#include "rpmserver.h"

#define CPR_RESOURCE_THERM_KEY 0x706d6574 // 'temp'

typedef enum
{
    thermal_no_info = 0,
    thermal_cold_critical = 1,
    thermal_cold = 2,
    thermal_cool = 3,
    thermal_normal = 4,
    thermal_warm = 5,
    thermal_hot = 6,
    thermal_hot_critical = 7,
} thermal_range;

typedef struct {
    uint32 temp;
} cpr_therm_notification;

void cpr_resource_xlate(rpm_translation_info *info);
void cpr_resource_apply(rpm_application_info *info);

#endif

