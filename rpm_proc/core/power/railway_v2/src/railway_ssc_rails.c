// railway_ssc_rails.c
//
// Copyright 2011 - 2014 by QUALCOMM Technologies, Inc.
// All Rights Reserved
// Confidental and Proprietary
//
// $ Header: $
// $ Author: $
// $ DateTime: $
//

#include "railway_ssc_rails.h"
#include "railway_internal.h"


static int ssc_vdd_cx_rail_id = RAIL_NOT_SUPPORTED_BY_RAILWAY;
static int ssc_vdd_mx_rail_id = RAIL_NOT_SUPPORTED_BY_RAILWAY;
static railway_rail_state_t* ssc_vdd_cx_rail_state = NULL;
static railway_rail_state_t* ssc_vdd_mx_rail_state = NULL;

static void railway_do_transition_ssc_rails(void)
{
    ssc_vdd_cx_rail_state->unconstrained_target = railway_aggregated_voltage_target(ssc_vdd_cx_rail_id, false);
    ssc_vdd_mx_rail_state->unconstrained_target = railway_aggregated_voltage_target(ssc_vdd_mx_rail_id, false);

    //Now update the constrained targets for the rails.
    railway_update_constrained_targets(ssc_vdd_cx_rail_id, ssc_vdd_cx_rail_state, RAILWAY_NO_REQUEST);
    railway_update_constrained_targets(ssc_vdd_mx_rail_id, ssc_vdd_mx_rail_state, ssc_vdd_cx_rail_state->constrained_target.mode);

    //Now do the transitions.
    //If SSC_Mx is going up, do that first.
    if((ssc_vdd_mx_rail_state->constrained_target.microvolts>ssc_vdd_mx_rail_state->current_active.microvolts) ||
        (ssc_vdd_mx_rail_state->constrained_target.mode>ssc_vdd_mx_rail_state->current_active.mode))
    {
        railway_transition_individual_rail(ssc_vdd_mx_rail_id);
    }

    //Now transition the logical rail
    if((ssc_vdd_cx_rail_state->constrained_target.microvolts!=ssc_vdd_cx_rail_state->current_active.microvolts) ||
        (ssc_vdd_cx_rail_state->constrained_target.mode!=ssc_vdd_cx_rail_state->current_active.mode))
    {
        railway_transition_individual_rail(ssc_vdd_cx_rail_id);
    }

    //Now transition SSC_Mx if it's going down.
    if((ssc_vdd_mx_rail_state->constrained_target.microvolts<ssc_vdd_mx_rail_state->current_active.microvolts) ||
        (ssc_vdd_mx_rail_state->constrained_target.mode<ssc_vdd_mx_rail_state->current_active.mode))
    {
        railway_transition_individual_rail(ssc_vdd_mx_rail_id);
    }

    //Assertion that current_active == constrained_target for all rails.
    for(int i=0; i<RAILWAY_CONFIG_DATA->num_rails; i++)
    {
        CORE_VERIFY(railway.rail_state[i].constrained_target.microvolts == railway.rail_state[i].current_active.microvolts);
        CORE_VERIFY(railway.rail_state[i].constrained_target.mode == railway.rail_state[i].current_active.mode);
    }

    //Assertion that SSC_MX-mode >= SSC_CX-mode
    CORE_VERIFY(ssc_vdd_mx_rail_state->current_active.mode>=ssc_vdd_cx_rail_state->current_active.mode);
}

__attribute__((section("railway_dram_reclaim_pool")))
static void railway_init_ssc_rail_group(void)
{
    //Code assumes that both SSC_CX and SSC_MX will exist if this rail group is supported.
    ssc_vdd_cx_rail_id = rail_id("vdd_ssc_cx");
    CORE_VERIFY(RAIL_NOT_SUPPORTED_BY_RAILWAY!=ssc_vdd_cx_rail_id);

    ssc_vdd_mx_rail_id = rail_id("vdd_ssc_mx");
    CORE_VERIFY(RAIL_NOT_SUPPORTED_BY_RAILWAY!=ssc_vdd_mx_rail_id);

    ssc_vdd_cx_rail_state = &railway.rail_state[ssc_vdd_cx_rail_id];
    ssc_vdd_mx_rail_state = &railway.rail_state[ssc_vdd_mx_rail_id];

    ssc_vdd_cx_rail_state->rail_group_fns = &railway_ssc_rail_fns;
    ssc_vdd_mx_rail_state->rail_group_fns = &railway_ssc_rail_fns;
}

const railway_rail_group_fns railway_ssc_rail_fns =
{
    .init_function       = railway_init_ssc_rail_group,
    .transition_function = railway_do_transition_ssc_rails,
};

