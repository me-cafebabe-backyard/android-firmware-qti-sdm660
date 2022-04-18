/**
 * @file:  cpr_image_init.c
 *
 * Copyright (c) 2015-2016 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * QUALCOMM Proprietary and Confidential.
 *
 * $DateTime: 2017/03/09 00:39:37 $
 * $Header: //components/rel/rpm.bf/1.8/core/power/cpr/image/rpm/target/660/cpr_image_target_init.c#4 $
 * $Change: 12622387 $
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

__attribute__((section("cpr_dram_reclaim_pool")))
static cpr_cfg_funcs* init_open_loop(cpr_rail* rail)
{
	bool UseGlobalCeiling = false;
    CPR_LOG_TRACE( "Initializing open loop on %s", rail->name );

	if(cpr_utils_is_closed_loop_mode(rail->id))
	{
		UseGlobalCeiling = true;
	}
    cpr_rail_set_initial_voltages( rail, UseGlobalCeiling, false );

    return NULL;
}

__attribute__((section("cpr_dram_reclaim_pool")))
static cpr_cfg_funcs* init_closed_loop(cpr_rail* rail)
{
    cpr_rail_init_rail_hw( rail, true );

    init_open_loop(rail);

    CPR_LOG_TRACE( "Configuring closed loop on %s", rail->name );
    cpr_rail_calculate_target_quotients( rail, &cpr_info.railStates[rail->railIdx] );

    return NULL;
}

__attribute__((section("cpr_dram_reclaim_pool")))
static cpr_cfg_funcs* enable_closed_loop(cpr_rail* rail)
{
    CPR_LOG_TRACE( "Enabling closed loop on %s", rail->name );

    cpr_rail_register_isr( rail );

    return NULL;
}

__attribute__((section("cpr_dram_reclaim_pool")))
static cpr_cfg_funcs* init_smem(cpr_rail* rail)
{
    cpr_smem_deserialize_config( rail, &cpr_info.railStates[rail->railIdx] );

    if(cpr_utils_is_closed_loop_mode(rail->id))
    {
        /*
         * Don't modify one time HW configuration as it's done by XBL.
         */
        cpr_rail_init_rail_hw( rail, false );
    }

    return NULL;
}

__attribute__((section("cpr_dram_reclaim_pool")))
static cpr_cfg_funcs* enable_smem(cpr_rail* rail)
{
    if(cpr_utils_is_closed_loop_mode(rail->id))
    {
        enable_closed_loop( rail );
    }

    return NULL;
}


//******************************************************************************
// Default Enablement Structures
//******************************************************************************

__attribute__((section("cpr_dram_reclaim_pool")))
static cpr_cfg_funcs init_funcs[CPR_INIT_FUNCS_COUNT] =
{
[CPR_INIT_NONE]           = {.cMode = CPR_CONTROL_NONE,           .init = NULL,             .enable = NULL},
[CPR_INIT_SMEM]           = {.cMode = CPR_CONTROL_NONE,           .init = init_smem,        .enable = enable_smem},
[CPR_INIT_OPEN_LOOP]      = {.cMode = CPR_CONTROL_OPEN_LOOP,      .init = init_open_loop,   .enable = NULL},
[CPR_INIT_SW_CLOSED_LOOP] = {.cMode = CPR_CONTROL_SW_CLOSED_LOOP, .init = init_closed_loop, .enable = enable_closed_loop},
};

__attribute__((section("cpr_dram_reclaim_pool")))
cpr_cfg_funcs* cpr_image_target_get_init_func(cpr_init_funcs_id func_id)
{
    CPR_ASSERT(func_id < CPR_INIT_FUNCS_COUNT);

    return &init_funcs[func_id];
}

