/*
===========================================================================

FILE:         railway_config.c

DESCRIPTION:
  Per target railway configurations

===========================================================================

                             Edit History

$Header: //components/rel/rpm.bf/1.8/core/power/railway_v2/src/660/railway_config.c#9 $
$Date: 2017/03/15 $

when       who     what, where, why
--------   ---     --------------------------------------------------------

===========================================================================
             Copyright (c) 2015 QUALCOMM Technologies Incorporated.
                    All Rights Reserved.
              QUALCOMM Proprietary and Confidential
===========================================================================
*/

/* -----------------------------------------------------------------------
**                           INCLUDES
** ----------------------------------------------------------------------- */

#include "CoreVerify.h"
#include "kvp.h"
#include "rpmserver.h"
#include "railway_config.h"
#include "railway_core_rails.h"
#include "railway_lpi_rails.h"
#include "time_service.h"
#include "Chipinfo.h"


#if 1 /* TODO: Delete this when no need to support 8997 RUMI */
#include "pm_npa_irep.h"

extern struct ResourceData *rpmserver_lookup_resource(rpm_resource_type resource, unsigned id);

void railway_dummy_pmic_xlate(rpm_translation_info *info) { }
void railway_dummy_pmic_apply(rpm_application_info *info) { }
#endif

/* -----------------------------------------------------------------------
**                           DATA
** ----------------------------------------------------------------------- */
#define RAIL_RESIDENCE_COUNT 2
const railway_rail_groups railway_8998_rail_groups =
{
    .group_fns = (const railway_rail_group_fns*[])
    {
        &railway_core_rail_fns,
        &railway_lpi_rail_fns
    },
    .num_groups = 2,
};

const railway_rail_groups * const RAILWAY_RAIL_GROUP_DATA = &railway_8998_rail_groups;


//
// BEGIN config data; should migrate to the system enumeration data method
//
static const railway_config_data_t temp_config_data =
{
    .rails     = (railway_rail_config_t[])
    {
        // Must init VDDMX first, as voting on the other rails will cause Mx changes to occur.
        {
            .vreg_name      = "vddmx",

            .resource_type  = RPM_RAILWAY_MX_REQ,

            .vreg_type      = RPM_SMPS_B_REQ,
            .vreg_num       = 5,

            .initial_corner = RAILWAY_NO_REQUEST, // set to NO_REQUEST to make sure rail transition won't be
                                                  // bypassed during railway_init_proxies_and_pins()

            .default_retention_uv = 488000,
        },

        // VDDCX
        {
            .vreg_name      = "vddcx",

            .resource_type  = RPM_RAILWAY_CX_REQ,

            .vreg_type      = RPM_SMPS_B_REQ,
            .vreg_num       = 3,

            .initial_corner = RAILWAY_NO_REQUEST, // set to NO_REQUEST to make sure rail transition won't be
                                                  // bypassed during railway_init_proxies_and_pins()

            .default_retention_uv = 348000,
        },

        // LPI_MX
        {
            .vreg_name      = "vdd_lpi_mx",

            .resource_type  = RPM_RAILWAY_LPI_MX_REQ,

            .vreg_type      = RPM_LDO_B_REQ,
            .vreg_num       = 10,

            .initial_corner = RAILWAY_NO_REQUEST,

            .default_retention_uv = 488000,
        },
        // LPI_CX
        {
            .vreg_name      = "vdd_lpi_cx",

            .resource_type  = RPM_RAILWAY_LPI_CX_REQ,

            .vreg_type      = RPM_LDO_B_REQ,
            .vreg_num       = 9,

            .initial_corner = RAILWAY_NO_REQUEST,

            .default_retention_uv = 352000,
        },
    },

    .num_rails = 4,
};
//
// END config data
//

const railway_config_data_t * const RAILWAY_CONFIG_DATA = &temp_config_data;

/* -----------------------------------------------------------------------
**                           FUNCTIONS
** ----------------------------------------------------------------------- */
__attribute__((section("railway_cram_reclaim_pool")))
void railway_init_early_proxy_votes(void)
{
    kvp_t  *kvp    = kvp_create(0);
    uint32  cx_req = (uint32)RAIL_VOLTAGE_LEVEL_NOMINAL;

    kvp_clear(kvp);

    // Init VDDCX at NOMINAL on behalf of APPS
    kvp_reset(kvp);
    kvp_put(kvp, RAILWAY_KEY_VOLTAGE_LEVEL, sizeof(uint32), (void *)&cx_req);
    rpm_send_init_proxy_vote(RPM_RAILWAY_CX_REQ, 0, (uint32)RPM_EE_APSS, kvp);
    kvp_destroy(kvp);
}

void railway_init_proxies_and_pins(void)
{
#if 0   //for Cx/Mx to peg at turbo
	const int cx_rail_id = rail_id("vddcx");
	assert(RAIL_NOT_SUPPORTED_BY_RAILWAY != cx_rail_id);
	railway_voter_t cx_pin = railway_create_voter(cx_rail_id, true, RAILWAY_RPM_INIT_VOTER);
	railway_corner_vote(cx_pin, RAILWAY_SUPER_TURBO);

#endif

#if 0	//for lpi_Cx/lpi_Mx to peg at turbo
	const int lpi_cx_rail_id = rail_id("vdd_lpi_cx");
	assert(RAIL_NOT_SUPPORTED_BY_RAILWAY != lpi_cx_rail_id);
	railway_voter_t lpi_cx_pin = railway_create_voter(lpi_cx_rail_id, true, RAILWAY_RPM_INIT_VOTER);
	railway_corner_vote(lpi_cx_pin, RAILWAY_SUPER_TURBO);
#endif	
}

typedef struct corner_stat
{
    uint64 time;
    uint32 corner;
    uint32 reserved;
} corner_stat;

typedef struct
{
    uint32 rail;
    uint32 num_corners;
    uint32 current_corner;
    uint32 last_entered;
} residence_info_type;

typedef struct
{
    uint32 num_rails;
    uint32 reserved;
    residence_info_type mx;
    corner_stat mx_residence[5];
    residence_info_type cx;
    corner_stat cx_residence[7];
	residence_info_type lpi_mx;
    corner_stat lpi_mx_residence[5];
    residence_info_type lpi_cx;
    corner_stat lpi_cx_residence[8];
} rail_residence_type;

__attribute__((section("rail_residencies")))
rail_residence_type rail_residence =
{
    .num_rails = 4,

    .mx = {
        .rail           = 0x0000786d, // "mx" in little endian
        .num_corners    = 5,
        .current_corner = RAILWAY_CORNERS_COUNT,
        .last_entered   = 0,
    },

    .mx_residence = {
        { .time = 0, .corner = 0x00746572 }, // "ret" in little endian
        { .time = 0, .corner = 0x32737673 }, // "svs2" in little endian
        { .time = 0, .corner = 0x006d6f6e }, // "nom" in little endian
		{ .time = 0, .corner = 0x326d6f6e }, // "nom2" in little endian
        { .time = 0, .corner = 0x62727574 }  // "turb" in little endian
    },

    .cx = {
        .rail           = 0x00007863, // "cx" in little endian
        .num_corners    = 7,
        .current_corner = RAILWAY_CORNERS_COUNT,
        .last_entered   = 0,
    },

    .cx_residence = {
        { .time = 0, .corner = 0x00746572 }, // "ret" in little endian
        { .time = 0, .corner = 0x6c737673 }, // "svsl" in little endian
		{ .time = 0, .corner = 0x00737673 }, // "svs" in little endian
        { .time = 0, .corner = 0x32737673 }, // "svs2" in little endian
        { .time = 0, .corner = 0x006d6f6e }, // "nom" in little endian
		{ .time = 0, .corner = 0x326d6f6e }, // "nom2" in little endian
        { .time = 0, .corner = 0x62727574 }  // "turb" in little endian
    },
	
	.lpi_mx = {
        .rail           = 0x786d706c, // "lpmx" in little endian
        .num_corners    = 5,
        .current_corner = RAILWAY_CORNERS_COUNT,
        .last_entered   = 0,
    },

    .lpi_mx_residence = {
        { .time = 0, .corner = 0x00746572 }, // "ret" in little endian
        { .time = 0, .corner = 0x32737673 }, // "svs2" in little endian
        { .time = 0, .corner = 0x006d6f6e }, // "nom" in little endian
		{ .time = 0, .corner = 0x326d6f6e }, // "nom2" in little endian
        { .time = 0, .corner = 0x62727574 }  // "turb" in little endian
    },
	
	.lpi_cx = {
        .rail           = 0x7863706c, // "lpcx" in little endian
        .num_corners    = 8,
        .current_corner = RAILWAY_CORNERS_COUNT,
        .last_entered   = 0,
    },

    .lpi_cx_residence = {
        { .time = 0, .corner = 0x00746572 }, // "ret" in little endian
		{ .time = 0, .corner = 0x6d737673 }, // "svsm" in little endian
        { .time = 0, .corner = 0x6c737673 }, // "svsl" in little endian
		{ .time = 0, .corner = 0x00737673 }, // "svs" in little endian
        { .time = 0, .corner = 0x32737673 }, // "svs2" in little endian
        { .time = 0, .corner = 0x006d6f6e }, // "nom" in little endian
		{ .time = 0, .corner = 0x326d6f6e }, // "nom2" in little endian
        { .time = 0, .corner = 0x62727574 }  // "turb" in little endian
    }
	
};


static unsigned get_residence_id(railway_corner corner, railway_corners_t* rail_corners)
{
    // 1 to skip NO_REQUEST corner
    for(unsigned i = 1; i < rail_corners->corners_count; i++)
    {
        if(rail_corners->corners[i] == corner)
        {
            return i - 1; /* -1 to remove NO_REQUEST corner */
        }
    }
    abort(); //something is out of wack. We are trying to save residencies for an unsupported corner
}

void railway_track_rail_residence(int rail_num, railway_corner new_corner, railway_corner old_corner)
{
    uint64 now = time_service_now();
    railway_corners_t* rail_corners = railway_get_supported_corners(rail_num);

    switch(rail_num)
    {
        case 0: //index in temp_config_data for mx
             if(old_corner!=RAILWAY_NO_REQUEST)
             {
               if(rail_residence.mx.current_corner == RAILWAY_CORNERS_COUNT)
                 rail_residence.mx_residence[get_residence_id(old_corner, rail_corners)].time = now;
               else
                 rail_residence.mx_residence[rail_residence.mx.current_corner].time += (now - rail_residence.mx.last_entered);
             }
             rail_residence.mx.current_corner = get_residence_id(new_corner, rail_corners);
             rail_residence.mx.last_entered = now;
             break;
        case 1: //index in temp_config_data for cx
             if(old_corner!=RAILWAY_NO_REQUEST)
             {
               if(rail_residence.cx.current_corner == RAILWAY_CORNERS_COUNT)
                 rail_residence.cx_residence[get_residence_id(old_corner, rail_corners)].time = now;
               else
                 rail_residence.cx_residence[rail_residence.cx.current_corner].time += (now - rail_residence.cx.last_entered);
             }
             rail_residence.cx.current_corner = get_residence_id(new_corner, rail_corners);
             rail_residence.cx.last_entered = now;
             break;
		case 2: //index in temp_config_data for cx
             if(old_corner!=RAILWAY_NO_REQUEST)
             {
               if(rail_residence.lpi_mx.current_corner == RAILWAY_CORNERS_COUNT)
                 rail_residence.lpi_mx_residence[get_residence_id(old_corner, rail_corners)].time = now;
               else
                 rail_residence.lpi_mx_residence[rail_residence.lpi_mx.current_corner].time += (now - rail_residence.lpi_mx.last_entered);
             }
             rail_residence.lpi_mx.current_corner = get_residence_id(new_corner, rail_corners);
             rail_residence.lpi_mx.last_entered = now;
             break;
        case 3: //index in temp_config_data for cx
             if(old_corner!=RAILWAY_NO_REQUEST)
             {
               if(rail_residence.lpi_cx.current_corner == RAILWAY_CORNERS_COUNT)
                 rail_residence.lpi_cx_residence[get_residence_id(old_corner, rail_corners)].time = now;
               else
                 rail_residence.lpi_cx_residence[rail_residence.lpi_cx.current_corner].time += (now - rail_residence.lpi_cx.last_entered);
             }
             rail_residence.lpi_cx.current_corner = get_residence_id(new_corner, rail_corners);
             rail_residence.lpi_cx.last_entered = now;
             break;
        default:
              break;
    }
}

__attribute__((section("railway_dram_reclaim_pool")))
static void railway_residence_init()
{
}

__attribute__((section("railway_dram_reclaim_pool")))
void railway_target_init(void)
{
    railway_residence_init();
}


