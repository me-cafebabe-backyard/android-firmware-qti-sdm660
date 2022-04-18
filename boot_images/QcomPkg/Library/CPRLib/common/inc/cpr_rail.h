/**
 * @file:  cpr_rail.h
 * @brief:
 *
 * Copyright (c) 2015-2016 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * QUALCOMM Proprietary and Confidential.
 *
 * $DateTime: 2016/08/19 05:58:45 $
 * $Header: //components/rel/boot.xf/1.4/QcomPkg/Library/CPRLib/common/inc/cpr_rail.h#2 $
 * $Change: 11185940 $
 */
#ifndef CPR_RAIL_H
#define	CPR_RAIL_H

#include "cpr_data.h"
#include "cpr_cfg.h"


void cpr_rail_init(cpr_rail* rail);
void cpr_rail_init_rail_hw(cpr_rail* rail, boolean configureHW);
boolean cpr_rail_process_results(cpr_rail* rail, cpr_results* rslts);
void cpr_rail_calculate_target_quotients(cpr_rail* rail, cpr_rail_state* state);
void cpr_rail_set_initial_voltages(cpr_rail* rail, boolean useGlobalCeiling, boolean useGlobalFloor);
void cpr_rail_disable_lower_modes(cpr_rail* rail, cpr_rail* fuse_rail, boolean updateOpenLoop, boolean updateClosedLoop, boolean forceDisable);
void cpr_rail_enable(cpr_rail* rail, cpr_mode_settings* modeState, cpr_submode_settings* submodeState, boolean changeOveride);
void cpr_rail_disable(cpr_rail* rail);
void cpr_rail_register_isr(cpr_rail* rail);
void cpr_rail_isr(void* ctx);

#endif

