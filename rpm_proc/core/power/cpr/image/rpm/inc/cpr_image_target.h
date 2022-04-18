/**
 * @file:  cpr_image_target.h
 *
 * Copyright (c) 2015-2016 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * QUALCOMM Proprietary and Confidential.
 *
 * $DateTime: 2017/03/06 22:14:55 $
 * $Header: //components/rel/rpm.bf/1.8/core/power/cpr/image/rpm/inc/cpr_image_target.h#2 $
 * $Change: 12599917 $
 */

#ifndef CPR_IMAGE_TARGET_H
#define CPR_IMAGE_TARGET_H

#include "cpr_data.h"
#include "cpr_defs.h"
#include "railway.h"


const cpr_settings* cpr_image_target_get_settings(void);

void cpr_image_target_init_mpm_ro_div_table(void);
uint16 cpr_image_target_get_mpm_ro_div(uint32 mxSleepUV);
boolean cpr_image_target_is_mx_chain_broken(void);
boolean cpr_image_target_is_retention_failed(void);
boolean cpr_image_target_is_turbo_mode_only(void);

void cpr_image_target_open_remote_cfg(void** cfg, uint32* size);
void cpr_image_target_close_remote_cfg(void);
cpr_foundry_id cpr_image_target_get_foundry(void);

cpr_domain_id cpr_image_target_railway_rail_to_cpr_domain(int railway_rail);
cpr_voltage_mode cpr_image_target_railway_corner_to_cpr_mode(railway_corner corner);
railway_corner cpr_image_target_cpr_mode_to_railway_corner(cpr_voltage_mode mode);

void cpr_image_target_enable_measurements(cpr_rail* rail, cpr_measurement_type type);
void cpr_image_target_disable_measurements(cpr_rail* rail, cpr_measurement_type type);
void cpr_image_target_custom_fn(cpr_rail_state *rail);
void cpr_image_target_lpi_controller_config(bool config);

#endif /*CPR_IMAGE_TARGET_H*/
