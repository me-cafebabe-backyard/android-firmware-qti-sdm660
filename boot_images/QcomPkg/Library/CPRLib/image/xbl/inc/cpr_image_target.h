/**
 * @file:  cpr_image_target.h
 * @brief:
 *
 * Copyright (c) 2015-2016 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * QUALCOMM Proprietary and Confidential.
 *
 * $DateTime: 2016/08/19 05:58:45 $
 * $Header: //components/rel/boot.xf/1.4/QcomPkg/Library/CPRLib/image/xbl/inc/cpr_image_target.h#2 $
 * $Change: 11185940 $
 */
#ifndef CPR_IMAGE_TARGET_H
#define CPR_IMAGE_TARGET_H

#include "cpr_data.h"
#include "cpr_defs.h"
#include "railway.h"


const cpr_settings* cpr_image_target_get_settings(void);
cpr_domain_id cpr_image_target_railway_rail_to_cpr_domain(int railway_rail);
railway_corner cpr_image_target_cpr_mode_to_railway_corner(cpr_voltage_mode mode);
cpr_voltage_mode cpr_image_target_railway_corner_to_cpr_mode(railway_corner corner);

void cpr_image_target_enable_measurements(cpr_rail* rail, cpr_measurement_type type);
void cpr_image_target_disable_measurements(cpr_rail* rail, cpr_measurement_type type);

#endif /*CPR_IMAGE_TARGET_H*/
