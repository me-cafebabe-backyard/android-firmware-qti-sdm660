/*===========================================================================

  railway_internal.h - bits of state for railway, in a convenient global
                       wrapper for debug

  Copyright (c) 2012 Qualcomm Technologies Incorporated.
  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ===========================================================================*/

#ifndef RAILWAY_INTERNAL_H
#define RAILWAY_INTERNAL_H

#include "railway.h"
#include "CoreVerify.h"
#include "npa_resource.h"
#include "railway_config.h"
#define RAILWAY_MAX_CBS 7

#define RAILWAY_KEY_INTERNAL_CORNER_LEVEL   0x6c637772 // rwcl
#define RAILWAY_KEY_VOLTAGE_LEVEL           0x6C766C76 // vlvl - Rail voltag level
#define RAILWAY_KEY_ACTIVE_FLOOR            0x636676   // vfc - active voltage floor corner.
#define RAILWAY_KEY_ACTIVE_FLOOR_LEVEL      0x6c6676   // vfl - active voltage floor level

#define VREG_TYPE_MASK 0x00FFFFFF
#define VREG_TYPE_SMPS 0x00706D73   //'smp' in little endian
#define VREG_TYPE_LDO  0x006F646C   //'ldo' in little endian

typedef struct
{
    uint8          corners_count;
    railway_corner corners[RAILWAY_CORNERS_COUNT];
} railway_corners_t;

//typedef struct railway_rail_group_fns railway_rail_group_fns;

typedef enum
{
    RAILWAY_INTERNAL_PRECHANGE_CB = 0,
    RAILWAY_INTERNAL_POSTCHANGE_CB,
    RAILWAY_INTERNAL_NUM_CB_TYPES,
} railway_internal_cb_type;

typedef struct
{
    railway_cb      callback_fn;
    void*           callback_cookie;
} railway_cb_data;

//typedef void (*railway_aggregation_workaround_fn)(int rail_id);

typedef struct
{
    railway_settings  current_active;

    railway_corner    unconstrained_target;
    railway_settings  constrained_target;    //Re-calculated each time we transition rails.

    uint32            retention_voltage_uv;

    // Storage for callbacks.
    railway_cb_data   cbs[RAILWAY_INTERNAL_NUM_CB_TYPES][RAILWAY_MAX_CBS];

    railway_voter_t   voter_list_head;

    unsigned          rail_server_handle;
    void*             rail_pmic_server_vote;

    const struct railway_rail_group_fns *rail_group_fns;
} railway_rail_state_t;

typedef struct
{
    railway_rail_state_t *rail_state;
} railway_internals_t;

extern railway_internals_t railway;

//Returns the target voltage and corner for the named rail.
//rail is not currently used - all votes are for VddCx.
//If for_sleep is true then this will ignore any suppressible votes - this option would
//only be used for sleep to know if vdd_min is possible.
railway_corner railway_aggregated_voltage_target(int rail, bool for_sleep);

void railway_transitioner_init(void);

//Any early target-specific init should be done in this function.
void railway_target_init(void);

void railway_walk_cbs(const railway_rail_state_t *rail_data, railway_cb_type type, const railway_settings *proposal);

void railway_transition_individual_rail(int rail_num);
void railway_quantize_constrained_target(int rail);
void railway_update_constrained_targets(int rail, railway_rail_state_t* rail_state, railway_corner floor);

railway_corner railway_get_lowest_active(int rail);

//Map voltage level to corner
railway_corner railway_level_to_corner(rail_voltage_level voltage_level);

//Get supported corners from CPR in addition to RETENTION and NO_REQUEST corners.
railway_corners_t* railway_get_supported_corners(int rail);

#endif // RAILWAY_INTERNAL_H
