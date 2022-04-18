// railway_cbs.c
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

static const railway_internal_cb_type railway_callback_remap[RAILWAY_NUM_CB_TYPES] =
{
    RAILWAY_INTERNAL_PRECHANGE_CB,      //RAILWAY_PRECHANGE_CB
    RAILWAY_INTERNAL_POSTCHANGE_CB,     //RAILWAY_POSTCHANGE_CB
    RAILWAY_INTERNAL_PRECHANGE_CB,      //RAILWAY_LAST_PRECHANGE_CB
    RAILWAY_INTERNAL_POSTCHANGE_CB,     //RAILWAY_FIRST_POSTCHANGE_CB
};

void railway_walk_cbs(const railway_rail_state_t *rail_data, railway_cb_type type, const railway_settings *proposal)
{
    //Must be done from 0 upwards as we have some callbacks which must be called first which are in the 0th slot.
    for(int i=0; i<RAILWAY_MAX_CBS; i++)
    {
        if(rail_data->cbs[type][i].callback_fn)
        {
            rail_data->cbs[type][i].callback_fn(proposal, rail_data->cbs[type][i].callback_cookie);
        }
    }
}

static void railway_set_pre_callback(railway_rail_state_t *rail_state, railway_cb_type type, railway_cb cb, void* cookie)
{
    const railway_internal_cb_type cb_type = railway_callback_remap[type];

    //Deal with special callbacks first.
    if(type!=RAILWAY_PRECHANGE_CB)
    {
        //If we ever extend this, implement another lookup to map the enum railway_cb_type to the array index.
        //For now, support the last entry only.
        CORE_VERIFY(type==RAILWAY_LAST_PRECHANGE_CB);
        
        CORE_VERIFY(rail_state->cbs[cb_type][RAILWAY_MAX_CBS-1].callback_fn==NULL);
        rail_state->cbs[cb_type][RAILWAY_MAX_CBS-1].callback_fn = cb;
        rail_state->cbs[cb_type][RAILWAY_MAX_CBS-1].callback_cookie = cookie;
        return;
    }
    
    // If this check fails then we need to increase RAILWAY_MAX_CBS by 1.
    // The last CB is reserved for RAILWAY_LAST_PRECHANGE_CB, so check the "RAILWAY_MAX_CBS-2"-th entry
    CORE_VERIFY(!rail_state->cbs[cb_type][RAILWAY_MAX_CBS-2].callback_fn);
    
    // The last CB is reserved for RAILWAY_LAST_PRECHANGE_CB, so search up to the "RAILWAY_MAX_CBS-1"-th entry
    for(int i = 0; i < RAILWAY_MAX_CBS-2; ++i)
    {
        if(!rail_state->cbs[cb_type][i].callback_fn)
        {
            rail_state->cbs[cb_type][i].callback_fn = cb;
            rail_state->cbs[cb_type][i].callback_cookie = cookie;
            break;
        }
    }
}

static void railway_set_post_callback(railway_rail_state_t *rail_state, railway_cb_type type, railway_cb cb, void* cookie)
{
    const railway_internal_cb_type cb_type = railway_callback_remap[type];

    //Deal with special callbacks first.
    if(type!=RAILWAY_POSTCHANGE_CB)
    {
        //If we ever extend this, implement another lookup to map the enum railway_cb_type to the array index.
        //For now, support the 0th entry only.
        CORE_VERIFY(type==RAILWAY_FIRST_POSTCHANGE_CB);
        
        CORE_VERIFY(rail_state->cbs[cb_type][0].callback_fn==NULL);
        rail_state->cbs[cb_type][0].callback_fn = cb;
        rail_state->cbs[cb_type][0].callback_cookie = cookie;
        return;
    }

    // If this check fails then we need to increase RAILWAY_MAX_CBS by 1.
    CORE_VERIFY(!rail_state->cbs[cb_type][RAILWAY_MAX_CBS-1].callback_fn);
    
    //Skip the first entry as that's for RAILWAY_FIRST_POSTCHANGE_CB
    for(int i = 1; i < RAILWAY_MAX_CBS; ++i)
    {
        if(!rail_state->cbs[cb_type][i].callback_fn)
        {
            rail_state->cbs[cb_type][i].callback_fn = cb;
            rail_state->cbs[cb_type][i].callback_cookie = cookie;
            break;
        }
    }
}

void railway_set_callback(int rail, railway_cb_type type, railway_cb cb, void* cookie)
{
    CORE_VERIFY(type<RAILWAY_NUM_CB_TYPES);
    CORE_VERIFY(cb);
    CORE_VERIFY(rail<RAILWAY_CONFIG_DATA->num_rails);

    railway_rail_state_t *rail_state = &railway.rail_state[rail];
    const railway_internal_cb_type cb_type = railway_callback_remap[type];
    
    if(cb_type==RAILWAY_INTERNAL_PRECHANGE_CB)
    {
        railway_set_pre_callback(rail_state, type, cb, cookie);
    }
    else if(cb_type==RAILWAY_INTERNAL_POSTCHANGE_CB)
    {
        railway_set_post_callback(rail_state, type, cb, cookie);
    }
    else
    {
        CORE_VERIFY(0);
    }
}
