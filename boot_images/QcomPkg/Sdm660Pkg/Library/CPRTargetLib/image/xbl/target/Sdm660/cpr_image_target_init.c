/**
 * @file:  cpr_init.c
 *
 * Copyright (c) 2015 by Qualcomm Technologies Incorporated. All Rights Reserved.
 *
 * $DateTime: 2017/03/02 23:37:54 $
 * $Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/CPRTargetLib/image/xbl/target/Sdm660/cpr_image_target_init.c#6 $
 * $Change: 12578103 $
 */
#include <string.h>
#include "cpr_logs.h"
#include "cpr_data.h"
#include "cpr_rail.h"
#include "cpr_smem.h"
#include "cpr_image.h"
#include "cpr_measurements.h"
#include "cpr_cfg.h"
#include "cpr_hal.h"
#include "cpr_utils.h"
#include "cpr_image_target_init.h"

//******************************************************************************
// Local Helper Functions
//******************************************************************************


static cpr_cfg_funcs* init_open_loop(cpr_rail* rail)
{
	bool UseGlobalCelling = false;
	
    CPR_LOG_TRACE( "Initializing open loop on %s", rail->name );

	if(cpr_utils_is_closed_loop_mode(rail->id))
	{
		UseGlobalCelling = true;
	}
    cpr_rail_set_initial_voltages( rail, UseGlobalCelling, false );

	return NULL;
}

static cpr_cfg_funcs* init_settle(cpr_rail* rail)
{
    CPR_LOG_TRACE( "Settling on %s", rail->name );

    for(int i = 0; i < rail->settleModesCount; i++) {
        cpr_measurements_settle( rail, rail->settleModes[i] );
    }

    return NULL;
}

static cpr_cfg_funcs* init_closed_loop(cpr_rail* rail)
{
    cpr_rail_init_rail_hw( rail, true );

    cpr_measurements_aging( rail );

    init_open_loop(rail);

    CPR_LOG_TRACE( "Configuring closed loop on %s", rail->name );
    cpr_rail_calculate_target_quotients( rail, &cpr_info.railStates[rail->railIdx] );

    init_settle( rail );

    return NULL;
}

/*
 * CPR config functions
 */
static cpr_cfg_funcs init_funcs[CPR_INIT_FUNCS_COUNT] =
{
    [CPR_INIT_NONE          ] = {.cMode = CPR_CONTROL_NONE,           .init = NULL,             .enable = NULL},
    [CPR_INIT_OPEN_LOOP     ] = {.cMode = CPR_CONTROL_OPEN_LOOP,      .init = init_open_loop,   .enable = NULL},
    [CPR_INIT_SW_CLOSED_LOOP] = {.cMode = CPR_CONTROL_SW_CLOSED_LOOP, .init = init_closed_loop, .enable = NULL},
};

//******************************************************************************
// Default Enablement Structures
//******************************************************************************

cpr_cfg_funcs* cpr_image_target_get_init_func(cpr_init_funcs_id func_id)
{
    CPR_ASSERT(func_id < CPR_INIT_FUNCS_COUNT);

    return &init_funcs[func_id];
}

