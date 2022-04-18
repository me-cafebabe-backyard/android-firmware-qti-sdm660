// railway_core_rails.c
//
// Copyright 2011 - 2014 by QUALCOMM Technologies, Inc.
// All Rights Reserved
// Confidental and Proprietary
//
// $ Header: $
// $ Author: $
// $ DateTime: $
//

#include "CoreVerify.h"

#include "railway.h"

#include "railway_internal.h"
#include "railway_config.h"
#include "swevent.h"
#include "DALSys.h"
#include "railway_core_rails.h"

#define MAX_LOGICAL_RAILS 2

static int mx_rail_id = RAIL_NOT_SUPPORTED_BY_RAILWAY;
static int ebi_rail_id = RAIL_NOT_SUPPORTED_BY_RAILWAY;
static int cx_rail_id = RAIL_NOT_SUPPORTED_BY_RAILWAY;

static railway_rail_state_t* mx_rail = NULL;
static railway_rail_state_t* cx_rail = NULL;
static railway_rail_state_t* ebi_rail = NULL;


static void railway_do_transition_core_rails(void)
{
    //First thing to do is to calculate the unconstrained target for each of the core rails.
    mx_rail->unconstrained_target = railway_aggregated_voltage_target(mx_rail_id, false);
    cx_rail->unconstrained_target = railway_aggregated_voltage_target(cx_rail_id, false);
    
    if(ebi_rail)
    {    
        ebi_rail->unconstrained_target = railway_aggregated_voltage_target(ebi_rail_id, false);
    }

    //Now update the constrained targets for the rails.
    railway_update_constrained_targets(cx_rail_id, cx_rail, RAILWAY_RETENTION);
    railway_update_constrained_targets(mx_rail_id, mx_rail, cx_rail->constrained_target.mode);
    if(ebi_rail)
        railway_update_constrained_targets(ebi_rail_id, ebi_rail, RAILWAY_RETENTION);


    //Now do the transitions.
    //If MX is going up, do that first.
    if((mx_rail->constrained_target.microvolts>mx_rail->current_active.microvolts) ||
        (mx_rail->constrained_target.mode>mx_rail->current_active.mode))
    {
        railway_transition_individual_rail(mx_rail_id);
    }

    //Now transition EBI if supported.
    if(ebi_rail)
    {
        //Transition EBI if it's going up.
        if((ebi_rail->constrained_target.microvolts > ebi_rail->current_active.microvolts) ||
           (ebi_rail->constrained_target.mode > ebi_rail->current_active.mode))
        {
            railway_transition_individual_rail(ebi_rail_id);
        }
    }

    //Now transition the logical rails (Cx)
    if((cx_rail->constrained_target.microvolts!=cx_rail->current_active.microvolts) ||
        (cx_rail->constrained_target.mode!=cx_rail->current_active.mode))
    {
        railway_transition_individual_rail(cx_rail_id);
    }

    //Now transition EBI if supported.
    if(ebi_rail)
    {
        //Transition EBI if it's going down.
        if((ebi_rail->constrained_target.microvolts < ebi_rail->current_active.microvolts) ||
           (ebi_rail->constrained_target.mode < ebi_rail->current_active.mode))
        {
            railway_transition_individual_rail(ebi_rail_id);
        }
    }

    //Now transition Mx if it's going down.
    if((mx_rail->constrained_target.microvolts<mx_rail->current_active.microvolts) ||
        (mx_rail->constrained_target.mode<mx_rail->current_active.mode))
    {
        railway_transition_individual_rail(mx_rail_id);
    }

    //Assertion that current_active == constrained_target for all rails.
    for(int i=0; i<RAILWAY_CONFIG_DATA->num_rails; i++)
    {
        CORE_VERIFY(railway.rail_state[i].constrained_target.microvolts == railway.rail_state[i].current_active.microvolts);
        CORE_VERIFY(railway.rail_state[i].constrained_target.mode == railway.rail_state[i].current_active.mode);
    }

    //Assertion that Mx-mode >= Cx-mode
    CORE_VERIFY(mx_rail->current_active.mode>=cx_rail->current_active.mode);
}

__attribute__((section("railway_dram_reclaim_pool")))
static void railway_init_voter(int rail_id, bool suppressible, railway_voter_id voter_id, railway_corner corner)
{
    railway_voter_t voter = railway_create_voter(rail_id, suppressible, voter_id);
    railway_corner_vote(voter, corner);
}

__attribute__((section("railway_dram_reclaim_pool")))
static void railway_init_core_rail_group(void)
{
    mx_rail_id = rail_id("vddmx");
    CORE_VERIFY(RAIL_NOT_SUPPORTED_BY_RAILWAY!=mx_rail_id);
    railway.rail_state[mx_rail_id].rail_group_fns = &railway_core_rail_fns;
    mx_rail = &railway.rail_state[mx_rail_id];

    cx_rail_id = rail_id("vddcx");
    CORE_VERIFY(RAIL_NOT_SUPPORTED_BY_RAILWAY!=cx_rail_id);
    railway.rail_state[cx_rail_id].rail_group_fns = &railway_core_rail_fns;
    cx_rail = &railway.rail_state[cx_rail_id];

    ebi_rail_id = rail_id("vdda_ebi");

    if(RAIL_NOT_SUPPORTED_BY_RAILWAY!=ebi_rail_id)
    {
        railway.rail_state[ebi_rail_id].rail_group_fns = &railway_core_rail_fns;
        ebi_rail = &railway.rail_state[ebi_rail_id];
    }

    //init time request for lowest active level on CX internal
#ifdef QCS405_IMAGE_LAYOUT
    railway_init_voter(cx_rail_id, true, RAILWAY_RPM_CX_VOTER_ID, RAILWAY_TURBO);
#else 
    railway_init_voter(cx_rail_id, true, RAILWAY_RPM_CX_VOTER_ID, railway_get_lowest_active(cx_rail_id));
#endif

    //init time request for sleep settings on CX internal
    railway_init_voter(cx_rail_id, false, RAILWAY_RPM_CX_SLEEP_VOTER_ID, RAILWAY_RETENTION);

    //init time request for lowest active level on MX internal
#ifdef QCS405_IMAGE_LAYOUT
	railway_init_voter(mx_rail_id, true, RAILWAY_RPM_MX_VOTER_ID, RAILWAY_TURBO);
#else
    railway_init_voter(mx_rail_id, true, RAILWAY_RPM_MX_VOTER_ID, railway_get_lowest_active(mx_rail_id));
#endif

    //init time request for sleep settings on MX internal
    railway_init_voter(mx_rail_id, false, RAILWAY_RPM_MX_SLEEP_VOTER_ID, RAILWAY_RETENTION);

    if(ebi_rail_id != RAIL_NOT_SUPPORTED_BY_RAILWAY)
    {
        //init time request for lowest active level on EBI internal
        railway_init_voter(ebi_rail_id, true, RAILWAY_RPM_EBI_VOTER_ID, RAILWAY_RETENTION);

        //init time request for sleep settings on EBI internal
        railway_init_voter(ebi_rail_id, false, RAILWAY_RPM_EBI_SLEEP_VOTER_ID, RAILWAY_RETENTION);
    }
}

const railway_rail_group_fns railway_core_rail_fns =
{
    .init_function       = railway_init_core_rail_group,
    .transition_function = railway_do_transition_core_rails,
};
