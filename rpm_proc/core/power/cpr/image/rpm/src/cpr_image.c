/**
 * @file:  cpr_image.c
 *
 * Copyright (c) 2015-2016 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * QUALCOMM Proprietary and Confidential.
 *
 * $DateTime: 2018/03/06 23:35:37 $
 * $Header: //components/rel/rpm.bf/1.8/core/power/cpr/image/rpm/src/cpr_image.c#4 $
 * $Change: 15617431 $
 */
#include <stdlib.h>
#include "cpr_image.h"
#include "cpr_image_target.h"
#include "cpr_resource.h"
#include "cpr_cfg.h"
#include "cpr_data.h"
#include "cpr.h"
#include "cpr_utils.h"

#include "rpmserver.h"
#include "railway.h"
#include "CoreVerify.h"
#include "ClockDefs.h"
#include "Clock.h"
#include "cortex-m3.h"
#include "swevent.h"
#include "Chipinfo.h"
#include "coredump.h"

#include <stringl/stringl.h>

void RBCPRTaskISR(void* task);
void* RBCPRTaskInit(cpr_image_isr func, void* ctx, uint32_t client_interrupt_id);

//******************************************************************************
// Global Data
//******************************************************************************

typedef struct
{
    cpr_domain_id   cpr_rail_id;
    const char*     railway_name;
} rail_name_map;
#if DAL_CONFIG_TARGET_ID==0x8998
const static rail_name_map railway_name_map[] =
{
    { CPR_RAIL_MX,       "vddmx"      },
    { CPR_RAIL_CX,       "vddcx"      },
    { CPR_RAIL_GFX,      "vddgfx"     },
    { CPR_RAIL_VDDA,     "vdda_ebi"   },
    { CPR_RAIL_SSC_MX,   "vdd_ssc_mx" },
    { CPR_RAIL_SSC_CX,   "vdd_ssc_cx" },
};
#elif DAL_CONFIG_TARGET_ID==0x660 || DAL_CONFIG_TARGET_ID==0x405
const static rail_name_map railway_name_map[] =
{
    { CPR_RAIL_MX,       "vddmx"      },
    { CPR_RAIL_CX,       "vddcx"      },
    { CPR_RAIL_LPI_MX,   "vdd_lpi_mx" },
    { CPR_RAIL_LPI_CX,   "vdd_lpi_cx" },
};
#endif

typedef struct
{
    boolean         init;
    int32           railway_rail_id;
    railway_voter_t voter;
} railway_handle;

typedef struct
{
    uint32 interrupt;
    void* task;
} cpr_isr_data;

static cpr_isr_data *isr_data;
static railway_handle *handles;

//******************************************************************************
// Local Helper Functions
//******************************************************************************

static const char* cpr_rpm_railway_rail_name(cpr_domain_id rail_id)
{
    for(int i = 0; i < (sizeof(railway_name_map) / sizeof(rail_name_map)); i++) {
        if(rail_id == railway_name_map[i].cpr_rail_id) {
            return railway_name_map[i].railway_name;
        }
    }

    CPR_ASSERT( 0 );
    return NULL;
}

static railway_handle* get_railway_handle(cpr_domain_id railId)
{
    uint32 railIdx = cpr_utils_get_rail_idx( railId );

    if(!handles)
    {
        handles = cpr_image_malloc(sizeof(railway_handle) * cpr_utils_get_num_rails());
    }

    if(!handles[railIdx].init)
    {
        handles[railIdx].railway_rail_id = rail_id( cpr_rpm_railway_rail_name( railId ) );
        CPR_ASSERT( handles[railIdx].railway_rail_id != RAIL_NOT_SUPPORTED_BY_RAILWAY );

        handles[railIdx].init = true;
    }

    return &handles[railIdx];
}

static void cpr_image_pre_switch(const railway_settings *settings, void* ctx)
{
    cpr_domain_id railId = (cpr_domain_id)(uintptr_t)ctx;
    cpr_pre_state_switch( railId );
}

static void cpr_image_post_switch(const railway_settings *settings, void* ctx)
{
    cpr_domain_id railId = (cpr_domain_id)(uintptr_t)ctx;
    cpr_domain_info info = {CPR_DOMAIN_TYPE_MODE_BASED, {cpr_image_target_railway_corner_to_cpr_mode(settings->mode)}};
    cpr_post_state_switch( railId, &info, settings->microvolts );
}

static void cpr_isr() __irq
{
    uint32 interrupt = interrupt_current_isr();
    interrupt_clear( interrupt );

    for(int i = 0; i < cpr_utils_get_num_rails(); i++)
    {
        if(isr_data[i].interrupt == interrupt)
        {
            cpr_rail_state *rail = &cpr_info.railStates[i];
            cpr_image_target_custom_fn(rail);
            RBCPRTaskISR( isr_data[i].task );
            return;
        }
    }

    CPR_ASSERT( 0 );
}

//******************************************************************************
// Public API Functions
//******************************************************************************

__attribute__((section("cpr_dram_reclaim_pool")))
void cpr_image_init(void)
{
    rpm_core_dump.cpr_info = &cpr_info;

    cpr_image_target_init_mpm_ro_div_table();
}

void* cpr_image_malloc(uint32 size)
{
    void* buf = calloc( 1, size );
    CPR_ASSERT( buf );
    return buf;
}

__attribute__((section("cpr_dram_reclaim_pool")))
void cpr_image_free(void* buf)
{
    free( buf );
}

void cpr_image_memscpy(void* dst, void* src, uint32 size)
{
    memscpy(dst, size, src, size);
}

__attribute__((section("cpr_dram_reclaim_pool")))
void cpr_image_register_thermal_cb(cpr_therm_cb cb)
{
    rpm_register_resource( RPM_RBCPR_REQ, 1, sizeof(cpr_therm_notification), cpr_resource_xlate, cpr_resource_apply, cb );
}

void cpr_image_register_isr(cpr_domain_id railId, uint32 interrupt, cpr_image_isr isr, void* ctx)
{
    railway_handle* hdl = get_railway_handle( railId );
    uint32 railIdx = cpr_utils_get_rail_idx( railId );

    if(!isr_data)
    {
        isr_data = cpr_image_malloc(sizeof(cpr_isr_data) * cpr_utils_get_num_rails());
    }

    isr_data[railIdx].interrupt = interrupt;
    isr_data[railIdx].task = RBCPRTaskInit(isr, ctx, interrupt);

    interrupt_set_isr( interrupt, cpr_isr );
    interrupt_configure( interrupt, RISING_EDGE );
    interrupt_clear( interrupt );
    interrupt_enable( interrupt );

    railway_set_callback( hdl->railway_rail_id, RAILWAY_PRECHANGE_CB, cpr_image_pre_switch, (void*) railId );
    railway_set_callback( hdl->railway_rail_id, RAILWAY_POSTCHANGE_CB, cpr_image_post_switch, (void*) railId );
}

void cpr_image_enable_clock(const char* clkId)
{
    //Clock_EnableClock( clkId );
}

uint32 cpr_image_get_chip_version()
{
    return Chipinfo_GetVersion();
}

cpr_foundry_id cpr_image_get_foundry()
{
    return cpr_image_target_get_foundry();
}

boolean cpr_image_set_rail_mode(cpr_domain_id railId, cpr_domain_info* info)
{
    railway_handle* hdl = get_railway_handle( railId );

    if(!hdl->voter) {
        hdl->voter = railway_create_voter( hdl->railway_rail_id, true, RAILWAY_CPR_SETTLING_VOTER );
    }

    railway_corner_vote( hdl->voter, cpr_image_target_cpr_mode_to_railway_corner(info->u.mode) );
    railway_transition_rail( hdl->railway_rail_id );

    return true;
}

boolean cpr_image_rail_transition_voltage(cpr_domain_id railId)
{
    railway_handle* hdl = get_railway_handle( railId );
    railway_transition_rail( hdl->railway_rail_id );

    return true;
}

void cpr_image_enter_sleep(void)
{
    for(int i = 0; i < cpr_info.settings->railsCount; i++)
    {
        cpr_rail* rail = cpr_info.settings->rails[i];

        if(!cpr_utils_is_closed_loop_mode(rail->id))
        {
            continue;
        }

        /*
         * Disable rail.
         * Currnt activeMode is saved in previousMode.
         */
        cpr_pre_state_switch(rail->id);
    }
}

void cpr_image_exit_sleep(void)
{
    for(int i = 0; i < cpr_info.settings->railsCount; i++)
    {
        cpr_rail* rail = cpr_info.settings->rails[i];

        if(!cpr_utils_is_closed_loop_mode(rail->id))
        {
            continue;
        }

        cpr_mode_settings* prev_mode_setting = cpr_utils_get_previous_mode_setting(rail->id);

        if(prev_mode_setting)
        {
            cpr_domain_info info = {CPR_DOMAIN_TYPE_MODE_BASED, {prev_mode_setting->mode}};

            /*
             * Enable rail with previousMode.
             */
            cpr_post_state_switch(rail->id, &info, cpr_get_voltage( rail->id, &info ));
        }
    }
}

void cpr_image_open_remote_cfg(void** cfg, uint32* size)
{
    cpr_image_target_open_remote_cfg(cfg, size);
}

void cpr_image_close_remote_cfg()
{
    cpr_image_target_close_remote_cfg();
}

void cpr_image_wait(uint32 us)
{
    DALSYS_BusyWait( us );
}

void rbcpr_core_dump()
{

}

uint32 cpr_image_get_eldo_voltage(cpr_domain_id railId, cpr_domain_info* info)
{
    return 0;
}

boolean cpr_image_can_resume_control(cpr_domain_id railId)
{
    return true;
}

void cpr_image_enable_measurements(cpr_rail* rail, cpr_measurement_type type)
{
    cpr_image_target_enable_measurements(rail, type);
}

void cpr_image_disable_measurements(cpr_rail* rail, cpr_measurement_type type)
{
    cpr_image_target_disable_measurements(rail, type);
}

const cpr_settings* cpr_image_get_settings(void)
{
    return cpr_image_target_get_settings();
}

/*
 * Wrapper functions for Railway declared in cpr_image_api.h
 */
uint32 cpr_railway_get_voltage(int railwayRailId, railway_corner railwayCorner)
{
    cpr_domain_id domain = cpr_image_target_railway_rail_to_cpr_domain( railwayRailId );
    cpr_domain_info info = {CPR_DOMAIN_TYPE_MODE_BASED, {cpr_image_target_railway_corner_to_cpr_mode(railwayCorner)}};

    return cpr_get_voltage( domain, &info );
}

void cpr_railway_get_supported_corners(int railwayRailId, railway_corner *corners, uint32 *cornerCount )
{
    const cpr_voltage_mode* modes = NULL;

    cpr_get_supported_modes( cpr_image_target_railway_rail_to_cpr_domain(railwayRailId), &modes, cornerCount );

    for(uint32 i = 0; i < *cornerCount; i++)
    {
        corners[i] = cpr_image_target_cpr_mode_to_railway_corner( modes[i] );
    }
}

uint16 cpr_get_mpm_ro_div(uint32 mxSleepUV)
{
    return cpr_image_target_get_mpm_ro_div(mxSleepUV);
}

boolean cpr_is_mx_chain_broken(void)
{
    return cpr_image_target_is_mx_chain_broken();
}

boolean cpr_is_retention_failed(void)
{
    return cpr_image_target_is_retention_failed();
}

void cpr_lpi_controller_config(boolean config)
{
    cpr_image_target_lpi_controller_config(config);
    return;
}
