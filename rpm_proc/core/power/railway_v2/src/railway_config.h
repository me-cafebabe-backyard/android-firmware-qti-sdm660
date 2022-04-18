/*===========================================================================

  railway_config.h - data related to platform-specific customization

  Copyright (c) 2012 Qualcomm Technologies Incorporated.
  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ===========================================================================*/

#ifndef RAILWAY_CONFIG_H
#define RAILWAY_CONFIG_H

#include "railway.h"
#include "rpm.h"
#include "railway_internal.h"
#include "pmapp_npa.h"

typedef void (*railway_static_cb_type)(uint32);
typedef void (*railway_ipeak_evaluator_fn)(uint32);
typedef void (*railway_rail_group_init_function)(void);
typedef void (*railway_rail_group_transition_function)(void);


typedef struct railway_rail_group_fns
{
    railway_rail_group_init_function        init_function;
    railway_rail_group_transition_function  transition_function;
} railway_rail_group_fns;

typedef struct
{
    const railway_rail_group_fns**    group_fns;
    int                               num_groups;
} railway_rail_groups;

typedef struct
{
    const char        *vreg_name;

    uint32            vreg_num;

    railway_corner    initial_corner; // Which corner to vote for out of the box (no votes received yet).

    rpm_resource_type vreg_type;
    rpm_resource_type resource_type;

    uint32            default_retention_uv; // default retention voltage in microvolt
} railway_rail_config_t;

typedef struct
{
    int                    num_rails;
    railway_rail_config_t *rails;
} railway_config_data_t;


extern const railway_config_data_t * const RAILWAY_CONFIG_DATA;
extern const railway_rail_groups * const RAILWAY_RAIL_GROUP_DATA;

#endif // RPM_CONFIG_H

