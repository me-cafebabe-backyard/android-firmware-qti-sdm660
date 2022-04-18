// railway_lpi_rails.c
//
// Copyright 2011 - 2014 by QUALCOMM Technologies, Inc.
// All Rights Reserved
// Confidental and Proprietary
//
// $ Header: $
// $ Author: $
// $ DateTime: $
//

#include "railway_lpi_rails.h"
#include "railway_internal.h"


static int lpi_vdd_cx_rail_id = RAIL_NOT_SUPPORTED_BY_RAILWAY;
static int lpi_vdd_mx_rail_id = RAIL_NOT_SUPPORTED_BY_RAILWAY;
static railway_rail_state_t* lpi_vdd_cx_rail_state = NULL;
static railway_rail_state_t* lpi_vdd_mx_rail_state = NULL;

static void railway_do_transition_lpi_rails(void)
{
    lpi_vdd_cx_rail_state->unconstrained_target = railway_aggregated_voltage_target(lpi_vdd_cx_rail_id, false);
    lpi_vdd_mx_rail_state->unconstrained_target = railway_aggregated_voltage_target(lpi_vdd_mx_rail_id, false);

    //Now update the constrained targets for the rails.
    railway_update_constrained_targets(lpi_vdd_cx_rail_id, lpi_vdd_cx_rail_state, RAILWAY_NO_REQUEST);
    railway_update_constrained_targets(lpi_vdd_mx_rail_id, lpi_vdd_mx_rail_state, lpi_vdd_cx_rail_state->constrained_target.mode);

    //Now do the transitions.
    //If lpi_Mx is going up, do that first.
    if((lpi_vdd_mx_rail_state->constrained_target.microvolts>lpi_vdd_mx_rail_state->current_active.microvolts) ||
        (lpi_vdd_mx_rail_state->constrained_target.mode>lpi_vdd_mx_rail_state->current_active.mode))
    {
        railway_transition_individual_rail(lpi_vdd_mx_rail_id);
    }

    //Now transition the logical rail
    if((lpi_vdd_cx_rail_state->constrained_target.microvolts!=lpi_vdd_cx_rail_state->current_active.microvolts) ||
        (lpi_vdd_cx_rail_state->constrained_target.mode!=lpi_vdd_cx_rail_state->current_active.mode))
    {
        railway_transition_individual_rail(lpi_vdd_cx_rail_id);
    }

    //Now transition lpi_Mx if it's going down.
    if((lpi_vdd_mx_rail_state->constrained_target.microvolts<lpi_vdd_mx_rail_state->current_active.microvolts) ||
        (lpi_vdd_mx_rail_state->constrained_target.mode<lpi_vdd_mx_rail_state->current_active.mode))
    {
        railway_transition_individual_rail(lpi_vdd_mx_rail_id);
    }

    //Assertion that current_active == constrained_target for all rails.
    for(int i=0; i<RAILWAY_CONFIG_DATA->num_rails; i++)
    {
        CORE_VERIFY(railway.rail_state[i].constrained_target.microvolts == railway.rail_state[i].current_active.microvolts);
        CORE_VERIFY(railway.rail_state[i].constrained_target.mode == railway.rail_state[i].current_active.mode);
    }

    //Assertion that lpi_MX-mode >= lpi_CX-mode
    CORE_VERIFY(lpi_vdd_mx_rail_state->current_active.mode>=lpi_vdd_cx_rail_state->current_active.mode);
}

__attribute__((section("railway_dram_reclaim_pool")))
static void railway_init_lpi_rail_group(void)
{
    //Code assumes that both lpi_CX and lpi_MX will exist if this rail group is supported.
    lpi_vdd_cx_rail_id = rail_id("vdd_lpi_cx");
    CORE_VERIFY(RAIL_NOT_SUPPORTED_BY_RAILWAY!=lpi_vdd_cx_rail_id);

    lpi_vdd_mx_rail_id = rail_id("vdd_lpi_mx");
    CORE_VERIFY(RAIL_NOT_SUPPORTED_BY_RAILWAY!=lpi_vdd_mx_rail_id);

    lpi_vdd_cx_rail_state = &railway.rail_state[lpi_vdd_cx_rail_id];
    lpi_vdd_mx_rail_state = &railway.rail_state[lpi_vdd_mx_rail_id];

    lpi_vdd_cx_rail_state->rail_group_fns = &railway_lpi_rail_fns;
    lpi_vdd_mx_rail_state->rail_group_fns = &railway_lpi_rail_fns;
}

const railway_rail_group_fns railway_lpi_rail_fns =
{
    .init_function       = railway_init_lpi_rail_group,
    .transition_function = railway_do_transition_lpi_rails,
};

