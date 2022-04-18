// railway.c - railway top-level implementation
//
// Copyright 2011 - 2012 by QUALCOMM Technologies, Inc.
// All Rights Reserved
// Confidental and Proprietary
//
// $ Header: $
// $ Author: $
// $ DateTime: $
//

#include <stringl/stringl.h>
#include "CoreVerify.h"
#include "DALSys.h"

#include "railway.h"

#include "railway_internal.h"
#include "railway_config.h"
#include "rpmserver.h"
#include "swevent.h"
#include "alloca.h"
#include "pm_npa_irep.h"
#include "time_service.h"

typedef struct
{
  uint64_t       current_time;
  railway_corner cx_corner;
  uint32         cx_voltage;
} cx_switch_t;

typedef struct
{
  uint64_t        current_time;
  railway_corner  mx_corner;
  uint32          mx_voltage;
} mx_switch_t;

#define RAILWAY_SWITCH_LOG_COUNT 10

cx_switch_t cx_switch_done[RAILWAY_SWITCH_LOG_COUNT];
mx_switch_t mx_switch_done[RAILWAY_SWITCH_LOG_COUNT];

/*
 * Unsupported voltage level is rounded up to the nearest supported corner.
 * Unsupported voltage level higher than RAIL_VOLTAGE_LEVEL_TURBO is bounded to
 * the max supported corner (RAILWAY_SUPER_TURBO_NO_CPR)
 *
 * For example,
 * RAIL_VOLTAGE_LEVEL_RETENTION_HIGH rounded to RAILWAY_SVS_MIN
 * RAIL_VOLTAGE_LEVEL_NOMINAL_HIGH   rounded to RAILWAY_TURBO
 * 0x200                             bounded to RAILWAY_SUPER_TURBO_NO_CPR
 */
static const rail_voltage_level supported_voltage_levels[RAILWAY_CORNERS_COUNT] = {
    [RAILWAY_NO_REQUEST        ] = RAIL_VOLTAGE_LEVEL_OFF      ,
    [RAILWAY_RETENTION         ] = RAIL_VOLTAGE_LEVEL_RETENTION,
    [RAILWAY_SVS_MIN           ] = RAIL_VOLTAGE_LEVEL_SVS_MIN  ,
    [RAILWAY_SVS_LOW           ] = RAIL_VOLTAGE_LEVEL_SVS_LOW  ,
    [RAILWAY_SVS               ] = RAIL_VOLTAGE_LEVEL_SVS      ,
    [RAILWAY_SVS_HIGH          ] = RAIL_VOLTAGE_LEVEL_SVS_HIGH ,
    [RAILWAY_NOMINAL           ] = RAIL_VOLTAGE_LEVEL_NOMINAL  ,
	[RAILWAY_NOMINAL_HIGH      ] = RAIL_VOLTAGE_LEVEL_NOMINAL_HIGH,
    [RAILWAY_TURBO             ] = RAIL_VOLTAGE_LEVEL_TURBO    ,
    [RAILWAY_SUPER_TURBO       ] = RAIL_VOLTAGE_LEVEL_TURBO    ,
    [RAILWAY_SUPER_TURBO_NO_CPR] = RAIL_VOLTAGE_LEVEL_TURBO    ,
};


__attribute__((section("railway_dram_reclaim_pool")))
static void initialize_rail(uint32 rail_num)
{
    const railway_rail_config_t *rail_config = &RAILWAY_CONFIG_DATA->rails[rail_num];

    railway_rail_state_t* rail_state = &railway.rail_state[rail_num];

    // Compute what our initial request should be.
    // Update our initial state.
    rail_state->current_active.mode       = rail_config->initial_corner;
    rail_state->current_active.microvolts = railway_get_corner_voltage(rail_num, rail_config->initial_corner);
    rail_state->retention_voltage_uv      = rail_config->default_retention_uv;

    rail_state->rail_server_handle = rpm_create_client(rail_config->vreg_type, rail_config->vreg_num, 0);

    switch(rail_config->vreg_type & VREG_TYPE_MASK)
    {
        case VREG_TYPE_SMPS:
        {
            rail_state->rail_pmic_server_vote = malloc(sizeof(pm_npa_smps_int_rep));
            CORE_VERIFY_PTR(rail_state->rail_pmic_server_vote);
            memset(rail_state->rail_pmic_server_vote, 0, sizeof(pm_npa_smps_int_rep));
        }
        break;
        case VREG_TYPE_LDO:
        {
            rail_state->rail_pmic_server_vote = malloc(sizeof(pm_npa_ldo_int_rep));
            CORE_VERIFY_PTR(rail_state->rail_pmic_server_vote);
            memset(rail_state->rail_pmic_server_vote, 0, sizeof(pm_npa_ldo_int_rep));
        }
        break;
        default:
            CORE_VERIFY(0); //Bad rail type
    }
}

/*  CR#1112278
    Log last 10 voltage switch history of CX and MX rails for debug purpose
*/
static void railway_log_rail_switch(int rail_num, unsigned microvolts)
{
	static int cx_count = 0;
	static int mx_count = 0;
	
	if(rail_id("vddcx") == rail_num)
	{
		if(cx_count < RAILWAY_SWITCH_LOG_COUNT) 
		{
			cx_switch_done[cx_count].current_time =   time_service_now();
			cx_switch_done[cx_count].cx_voltage   =   microvolts;
			cx_switch_done[cx_count].cx_corner    =   railway.rail_state[rail_num].constrained_target.mode;
			cx_count++;
			if(cx_count == RAILWAY_SWITCH_LOG_COUNT)
				cx_count = 0;
		}
	}
	else if(rail_id("vddmx") == rail_num)
	{
		if(mx_count < RAILWAY_SWITCH_LOG_COUNT) 
		{
			mx_switch_done[mx_count].current_time  =   time_service_now();
			mx_switch_done[mx_count].mx_voltage    =   microvolts;
			mx_switch_done[mx_count].mx_corner     =   railway.rail_state[rail_num].constrained_target.mode;
			mx_count++;
			if(mx_count == RAILWAY_SWITCH_LOG_COUNT)
				mx_count = 0;
		}
	}

	return;
}	
void railway_set_pmic_voltage(int rail_num, unsigned microvolts)
{
    const railway_rail_config_t *rail_config = &RAILWAY_CONFIG_DATA->rails[rail_num];
    const railway_rail_state_t *rail_data = &railway.rail_state[rail_num];

    switch(rail_config->vreg_type & VREG_TYPE_MASK)
    {
        case VREG_TYPE_SMPS:
        {
            pm_npa_smps_int_rep* request = (pm_npa_smps_int_rep*)rail_data->rail_pmic_server_vote;

            if(microvolts)
                request->sw_en = TRUE;
            else
                request->sw_en = FALSE;
            request->uvol = microvolts;

            rpm_issue_request(rail_config->vreg_type, rail_config->vreg_num, rail_data->rail_server_handle, sizeof(pm_npa_smps_int_rep), request);
            railway_log_rail_switch(rail_num, microvolts);
        }
        break;
        case VREG_TYPE_LDO:
        {
            pm_npa_ldo_int_rep* request = (pm_npa_ldo_int_rep*)rail_data->rail_pmic_server_vote;

            if(microvolts)
                request->sw_en = TRUE;
            else
                request->sw_en = FALSE;
            request->output_uvol = microvolts;

            rpm_issue_request(rail_config->vreg_type, rail_config->vreg_num, rail_data->rail_server_handle, sizeof(pm_npa_ldo_int_rep), request);
        }
        break;
        default:
            CORE_VERIFY(0); //Bad rail type
    }
}

void railway_transition_individual_rail(int rail_num)
{
    railway_rail_state_t *rail_data = &railway.rail_state[rail_num];
    const railway_settings* target = &rail_data->constrained_target;
    unsigned target_voltage = target->microvolts;

    railway_walk_cbs(rail_data, RAILWAY_PRECHANGE_CB, target);

    SWEVENT(RAILWAY_CHANGE_VOLTAGE, rail_num, target->microvolts, rail_data->current_active.microvolts, ((target->mode << 16) | (rail_data->current_active.mode)));

    // Only set the actual voltage if it's changing. It could be that we're just changing modes.
    // E.g. if CPR has taken the voltage down in one mode to the point that it is the same voltage as another mode.
    if(target_voltage!=railway.rail_state[rail_num].current_active.microvolts)
    {
        railway_track_rail_residence(rail_num, target->mode, railway.rail_state[rail_num].current_active.mode);
        railway_set_pmic_voltage(rail_num, target_voltage);
    }

    memscpy(&rail_data->current_active, sizeof(railway_settings), target, sizeof(railway_settings));
    railway_walk_cbs(rail_data, RAILWAY_POSTCHANGE_CB, target);
}

void railway_quantize_constrained_target(int rail)
{
    railway_corners_t* rail_corners = railway_get_supported_corners(rail);
    const railway_corner highest_supported_corner = rail_corners->corners[rail_corners->corners_count-1];
    railway_corner quantized_corner = highest_supported_corner;

    /*
     * If the requested corner is higher than the highest supported corner, just use the highest supported corner
     * instead of abort.
     * CPR driver uses TURBO instead of SUPER_TURBO since Voltage Plan uses Turbo, and
     * SUPER_TURBO enum value is higher than TURBO enum value * even though they are same.
     * We should just cap the requested corner to the highest supported corner.
     */
    if (railway.rail_state[rail].constrained_target.mode < highest_supported_corner)
    {
        for(int i = rail_corners->corners_count-1; i>=0; i--)
        {
            //Check that we're not going lower than the constrained target's mode.
            if(rail_corners->corners[i] < railway.rail_state[rail].constrained_target.mode)
            {
                break;
            }

            quantized_corner = rail_corners->corners[i];
        }
    }

    railway.rail_state[rail].constrained_target.mode       = quantized_corner;
    railway.rail_state[rail].constrained_target.microvolts = railway_get_corner_voltage(rail, quantized_corner);
}

void railway_update_constrained_targets(int rail, railway_rail_state_t* rail_state, railway_corner floor)
{
    //Start from the unconstrained target.
    rail_state->constrained_target.mode       = MAX(rail_state->unconstrained_target, floor);
    rail_state->constrained_target.microvolts = 0;

    railway_quantize_constrained_target(rail);
}


bool railway_transition_in_progress = false;

//Top level fn for transitioning a rail. Actually transitions all rails, not just rail_num.
void railway_transition_rail(int rail_num)
{
    CORE_VERIFY(!railway_transition_in_progress);    //We don't support this fn becoming re-entrant for now. Guard against it.
    railway_transition_in_progress = true;

    CORE_VERIFY_PTR(railway.rail_state[rail_num].rail_group_fns);

    railway.rail_state[rail_num].rail_group_fns->transition_function();

    railway_transition_in_progress = false;
}

__attribute__((section("railway_dram_reclaim_pool")))
void railway_transitioner_init(void)
{
    for(uint32 i = 0; i < RAILWAY_CONFIG_DATA->num_rails; i++)
    {
        initialize_rail(i);
    }
}

void railway_get_sleep_modes(int cx_id, int mx_id, railway_corner *cx_mode, railway_corner *mx_mode)
{
    railway_corners_t* rail_corners = NULL;

    CORE_VERIFY(cx_id < RAILWAY_CONFIG_DATA->num_rails);
    CORE_VERIFY(mx_id < RAILWAY_CONFIG_DATA->num_rails);

    *cx_mode = railway_aggregated_voltage_target(cx_id, true);
    *mx_mode = railway_aggregated_voltage_target(mx_id, true);

    rail_corners = railway_get_supported_corners(cx_id);

    /* start from 1 to skip NO_REQUEST corner on CX */
    for(unsigned i = 1; i < rail_corners->corners_count; i++)
    {

      if((*cx_mode) <= rail_corners->corners[i])
      {
          *cx_mode = rail_corners->corners[i];
          break;
      }
    }

    rail_corners = railway_get_supported_corners(mx_id);

    /* start from 1 to skip NO_REQUEST corner on MX */
    for(unsigned i = 1; i < rail_corners->corners_count; i++)
    {

      if((*mx_mode) <= rail_corners->corners[i])
      {
          *mx_mode = rail_corners->corners[i];
          break;
      }
    }
}

railway_corner railway_get_lowest_active(int rail)
{
    int index = 0;
    CORE_VERIFY(rail<RAILWAY_CONFIG_DATA->num_rails);
    railway_corners_t* rail_corners = railway_get_supported_corners(rail);
    railway_corner next_corner = rail_corners->corners[index];

    while((next_corner == RAILWAY_RETENTION) || (next_corner == RAILWAY_NO_REQUEST))
    {
        index++;
        CORE_VERIFY(index < rail_corners->corners_count);
        next_corner = rail_corners->corners[index];
    }
    CORE_VERIFY(next_corner < RAILWAY_CORNERS_COUNT);
    return next_corner;
}

/*
 * Unsupported voltage level is rounded up to the nearest supported corner.
 * Unsupported voltage level higher than RAIL_VOLTAGE_LEVEL_TURBO is bounded to
 * the max supported corner (RAILWAY_SUPER_TURBO_NO_CPR)
 *
 * For example,
 * RAIL_VOLTAGE_LEVEL_RETENTION_HIGH rounded to RAILWAY_SVS_MIN
 * RAIL_VOLTAGE_LEVEL_NOMINAL_HIGH   rounded to RAILWAY_TURBO
 * 0x200                             bounded to RAILWAY_SUPER_TURBO_NO_CPR
 */
railway_corner railway_level_to_corner(rail_voltage_level voltage_level)
{
    railway_corner corner_val = (railway_corner)(RAILWAY_CORNERS_COUNT - 1);

    for(int i = 0; i < RAILWAY_CORNERS_COUNT; i++)
    {
        if(voltage_level <= supported_voltage_levels[i])
        {
            corner_val = (railway_corner)i;
            break;
        }
    }

    return corner_val;
}

