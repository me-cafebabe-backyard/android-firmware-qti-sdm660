/**
 * @file:  cpr_image_target.c
 *
 * Copyright (c) 2015-2016 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * QUALCOMM Proprietary and Confidential.
 *
 * $DateTime: 2017/03/06 22:14:55 $
 * $Header: //components/rel/rpm.bf/1.8/core/power/cpr/image/rpm/target/660/cpr_image_target.c#7 $
 * $Change: 12599917 $
 */

#include "cpr_image_target.h"
#include "cpr_logs.h"
#include "cpr_utils.h"
#include "time_service.h"
#include "rpmserver.h"
#include "cpr_hal.h"
#include "smem.h"
#include "page_select.h"
#include "Chipinfo.h"

#define CPR_MPM_RO_DIV_MIN_UV       450000
#define CPR_MPM_RO_DIV_MAX_UV       1100000
#define CPR_MPM_RO_DIV_STEP_UV      50000
#define CPR_MPM_RO_DIV_COUNT        8
#define CPR_MPM_RO_DIV_TABLE_COUNT  31 // fuse value range [-15, +15]

typedef struct cpr_lpass_debug
{
  uint32   cpr_interrupt_ignored_count;
  uint64_t interrupt_ignored_time_stamp;
} cpr_lpass_debug;

static boolean cpr_lpass_collapsed;
static cpr_lpass_debug cpr_lpass_debug_info;

/*
 * Default RO divider value used for CPR Rev0 part
 * CPR Rev0 part only enables Nominal and Turbo voltages.
 */
static uint16 cpr_mpm_ro_div_table[CPR_MPM_RO_DIV_COUNT];
//static uint32 cpr_xo_shutdown_disable_fuse;

/*
 * From Nominal to Turbo (800mV - 1100mV), RO frequency is 696MHz - 2004MHz.
 * And for active voltages, SPMI frequency can be between 1MHz - 19.2MHz.
 * 150 (0x96) can be used for RO divider for all Nominal-Turbo voltages.
 */
__attribute__((section("cpr_dram_reclaim_pool")))
static uint16 cpr_mpm_ro_div_tables[CPR_MPM_RO_DIV_TABLE_COUNT][CPR_MPM_RO_DIV_COUNT] =
{   //      MX Sleep Voltage (mV)
    //From: 450   500   550   600   650   700   750   800  (mV)
    //To  : 500   550   600   650   700   750   800   1100 (mV)
    [ 0] = {0xAB, 0xAB, 0xAB, 0x1AD, 0x1AD, 0x1AD, 0x1AD, 0x1AD }, // CPRx_TARG_VOLT_TUR = -15 = 0x1F (31)
    [ 1] = {0xAB, 0xAB, 0xAB, 0x1AD, 0x1AD, 0x1AD, 0x1AD, 0x1AD }, // CPRx_TARG_VOLT_TUR = -14 = 0x1E (30)
    [ 2] = {0xAB, 0xAB, 0xAB, 0x1AD, 0x1AD, 0x1AD, 0x1AD, 0x1AD }, // CPRx_TARG_VOLT_TUR = -13 = 0x1D (29)
    [ 3] = {0xAB, 0xAB, 0xAB, 0x1AD, 0x1AD, 0x1AD, 0x1AD, 0x1AD }, // CPRx_TARG_VOLT_TUR = -12 = 0x1C (28)
    [ 4] = {0xAB, 0xAB, 0xAB, 0x1AD, 0x1AD, 0x1AD, 0x1AD, 0x1AD }, // CPRx_TARG_VOLT_TUR = -11 = 0x1B (27)
    [ 5] = {0xAB, 0xAB, 0xAB, 0x1AD, 0x1AD, 0x1AD, 0x1AD, 0x1AD }, // CPRx_TARG_VOLT_TUR = -10 = 0x1A (26)
    [ 6] = {0xAB, 0xAB, 0xAB, 0x1AD, 0x1AD, 0x1AD, 0x1AD, 0x1AD }, // CPRx_TARG_VOLT_TUR =  -9 = 0x19 (25)
    [ 7] = {0xAB, 0xAB, 0xAB, 0x1AD, 0x1AD, 0x1AD, 0x1AD, 0x1AD }, // CPRx_TARG_VOLT_TUR =  -8 = 0x18 (24)
    [ 8] = {0xAB, 0xAB, 0xAB, 0x1AD, 0x1AD, 0x1AD, 0x1AD, 0x1AD }, // CPRx_TARG_VOLT_TUR =  -7 = 0x17 (23)
    [ 9] = {0xAB, 0xAB, 0xAB, 0x1AD, 0x1AD, 0x1AD, 0x1AD, 0x1AD }, // CPRx_TARG_VOLT_TUR =  -6 = 0x16 (22)
    [10] = {0xAB, 0xAB, 0xAB, 0x1AD, 0x1AD, 0x1AD, 0x1AD, 0x1AD }, // CPRx_TARG_VOLT_TUR =  -5 = 0x15 (21)
    [11] = {0xAB, 0xAB, 0xAB, 0x1AD, 0x1AD, 0x1AD, 0x1AD, 0x1AD }, // CPRx_TARG_VOLT_TUR =  -4 = 0x14 (20)
    [12] = {0xAB, 0xAB, 0xAB, 0x1AD, 0x1AD, 0x1AD, 0x1AD, 0x1AD }, // CPRx_TARG_VOLT_TUR =  -3 = 0x13 (19)
    [13] = {0xAB, 0xAB, 0xAB, 0x1AD, 0x1AD, 0x1AD, 0x1AD, 0x1AD }, // CPRx_TARG_VOLT_TUR =  -2 = 0x12 (18)
    [14] = {0xAB, 0xAB, 0xAB, 0x1AD, 0x1AD, 0x1AD, 0x1AD, 0x1AD }, // CPRx_TARG_VOLT_TUR =  -1 = 0x11 (17)
    [15] = {0xAB, 0xAB, 0xAB, 0x1AD, 0x1AD, 0x1AD, 0x1AD, 0x1AD }, // CPRx_TARG_VOLT_TUR =   0 = 0x10, 0x00 (16, 0)
    [16] = {0xAB, 0xAB, 0xAB, 0x1AD, 0x1AD, 0x1AD, 0x1AD, 0x1AD }, // CPRx_TARG_VOLT_TUR =  +1 = 0x01 ( 1)
    [17] = {0xAB, 0xAB, 0xAB, 0x1AD, 0x1AD, 0x1AD, 0x1AD, 0x1AD }, // CPRx_TARG_VOLT_TUR =  +2 = 0x02 ( 2)
    [18] = {0xAB, 0xAB, 0xAB, 0x1AD, 0x1AD, 0x1AD, 0x1AD, 0x1AD }, // CPRx_TARG_VOLT_TUR =  +3 = 0x03 ( 3)
    [19] = {0xAB, 0xAB, 0xAB, 0x1AD, 0x1AD, 0x1AD, 0x1AD, 0x1AD }, // CPRx_TARG_VOLT_TUR =  +4 = 0x04 ( 4)
    [20] = {0xAB, 0xAB, 0xAB, 0x1AD, 0x1AD, 0x1AD, 0x1AD, 0x1AD }, // CPRx_TARG_VOLT_TUR =  +5 = 0x05 ( 5)
    [21] = {0xAB, 0xAB, 0xAB, 0x1AD, 0x1AD, 0x1AD, 0x1AD, 0x1AD }, // CPRx_TARG_VOLT_TUR =  +6 = 0x06 ( 6)
    [22] = {0xAB, 0xAB, 0xAB, 0x1AD, 0x1AD, 0x1AD, 0x1AD, 0x1AD }, // CPRx_TARG_VOLT_TUR =  +7 = 0x07 ( 7)
    [23] = {0xAB, 0xAB, 0xAB, 0x1AD, 0x1AD, 0x1AD, 0x1AD, 0x1AD }, // CPRx_TARG_VOLT_TUR =  +8 = 0x08 ( 8)
    [24] = {0xAB, 0xAB, 0xAB, 0x1AD, 0x1AD, 0x1AD, 0x1AD, 0x1AD }, // CPRx_TARG_VOLT_TUR =  +9 = 0x09 ( 9)
    [25] = {0xAB, 0xAB, 0xAB, 0x1AD, 0x1AD, 0x1AD, 0x1AD, 0x1AD }, // CPRx_TARG_VOLT_TUR = +10 = 0x0A (10)
    [26] = {0xAB, 0xAB, 0xAB, 0x1AD, 0x1AD, 0x1AD, 0x1AD, 0x1AD }, // CPRx_TARG_VOLT_TUR = +11 = 0x0B (11)
    [27] = {0xAB, 0xAB, 0xAB, 0x1AD, 0x1AD, 0x1AD, 0x1AD, 0x1AD }, // CPRx_TARG_VOLT_TUR = +12 = 0x0C (12)
    [28] = {0xAB, 0xAB, 0xAB, 0x1AD, 0x1AD, 0x1AD, 0x1AD, 0x1AD }, // CPRx_TARG_VOLT_TUR = +13 = 0x0D (13)
    [29] = {0xAB, 0xAB, 0xAB, 0x1AD, 0x1AD, 0x1AD, 0x1AD, 0x1AD }, // CPRx_TARG_VOLT_TUR = +14 = 0x0E (14)
    [30] = {0xAB, 0xAB, 0xAB, 0x1AD, 0x1AD, 0x1AD, 0x1AD, 0x1AD }  // CPRx_TARG_VOLT_TUR = +15 = 0x0F (15)
};


const cpr_settings* cpr_image_target_get_settings(void)
{
    extern const cpr_settings cpr_settings_660;
	extern const cpr_settings cpr_settings_630;

    return (CHIPINFO_FAMILY_SDM630 == Chipinfo_GetFamily()) ? &cpr_settings_630 : &cpr_settings_660;
    
}

void cpr_image_target_open_remote_cfg(void** cfg, uint32* size)
{
    *cfg = smem_get_addr( SMEM_CPR_CONFIG, size );

    CPR_ASSERT(*cfg);

    /* update page select bit for DDR access */
    set_page_select( 2 );
}

void cpr_image_target_close_remote_cfg(void)
{
    set_page_select( 0 );
}

cpr_foundry_id cpr_image_target_get_foundry(void)
{
    cpr_foundry_id cpr_foundry;
    uint32 chipInfo_foundry = Chipinfo_GetFoundryId();

    switch(chipInfo_foundry)
    {
        case(CHIPINFO_FOUNDRYID_TSMC):
            cpr_foundry = CPR_FOUNDRY_TSMC;
            break;
        case(CHIPINFO_FOUNDRYID_GF):
            cpr_foundry = CPR_FOUNDRY_GF;
            break;
        case(CHIPINFO_FOUNDRYID_SS):
            cpr_foundry = CPR_FOUNDRY_SS;
            break;
        case(CHIPINFO_FOUNDRYID_IBM):
            cpr_foundry = CPR_FOUNDRY_IBM;
            break;
        case(CHIPINFO_FOUNDRYID_UMC):
            cpr_foundry = CPR_FOUNDRY_UMC;
            break;
        default:
            CPR_ASSERT( 0 ); // Chip foundry is not valid
    }

    return cpr_foundry;
}

cpr_domain_id cpr_image_target_railway_rail_to_cpr_domain(int railway_rail)
{
    switch(railway_rail)
    {
        case 0: return CPR_RAIL_MX;
        case 1: return CPR_RAIL_CX;
        case 2: return CPR_RAIL_LPI_MX;
        case 3: return CPR_RAIL_LPI_CX;
        default:
            CPR_LOG_FATAL("Unsupported rail %u", railway_rail);
            break;
    }

    CPR_ASSERT( 0 );

    return (cpr_domain_id)0;
}

cpr_voltage_mode cpr_image_target_railway_corner_to_cpr_mode(railway_corner corner)
{
    cpr_voltage_mode map[RAILWAY_CORNERS_COUNT] =
    {
        [RAILWAY_NO_REQUEST        ] = CPR_VOLTAGE_MODE_OFF,
        [RAILWAY_RETENTION         ] = CPR_VOLTAGE_MODE_RETENTION,
        [RAILWAY_SVS_MIN           ] = CPR_VOLTAGE_MODE_MIN_SVS,
        [RAILWAY_SVS_LOW           ] = CPR_VOLTAGE_MODE_LOW_SVS,
        [RAILWAY_SVS               ] = CPR_VOLTAGE_MODE_SVS,
        [RAILWAY_SVS_HIGH          ] = CPR_VOLTAGE_MODE_SVS_L1,
        [RAILWAY_NOMINAL           ] = CPR_VOLTAGE_MODE_NOMINAL,
		[RAILWAY_NOMINAL_HIGH      ] = CPR_VOLTAGE_MODE_NOMINAL_L1,
        [RAILWAY_TURBO             ] = CPR_VOLTAGE_MODE_TURBO,
        [RAILWAY_SUPER_TURBO       ] = CPR_VOLTAGE_MODE_SUPER_TURBO,
        [RAILWAY_SUPER_TURBO_NO_CPR] = CPR_VOLTAGE_MODE_SUPER_TURBO_NO_CPR,
    };

    return (corner >= RAILWAY_CORNERS_COUNT) ? CPR_VOLTAGE_MODE_SUPER_TURBO_NO_CPR : map[corner];
}

railway_corner cpr_image_target_cpr_mode_to_railway_corner(cpr_voltage_mode mode)
{
    railway_corner map[CPR_VOLTAGE_MODE_COUNT] =
    {
        [CPR_VOLTAGE_MODE_OFF                ] = RAILWAY_NO_REQUEST,
        [CPR_VOLTAGE_MODE_RETENTION          ] = RAILWAY_RETENTION,
        [CPR_VOLTAGE_MODE_MIN_SVS            ] = RAILWAY_SVS_MIN,
        [CPR_VOLTAGE_MODE_LOW_SVS            ] = RAILWAY_SVS_LOW,
        [CPR_VOLTAGE_MODE_SVS                ] = RAILWAY_SVS,
        [CPR_VOLTAGE_MODE_SVS_L1             ] = RAILWAY_SVS_HIGH,
        [CPR_VOLTAGE_MODE_NOMINAL            ] = RAILWAY_NOMINAL,
        [CPR_VOLTAGE_MODE_NOMINAL_L1         ] = RAILWAY_NOMINAL_HIGH,
        [CPR_VOLTAGE_MODE_TURBO              ] = RAILWAY_TURBO,
        [CPR_VOLTAGE_MODE_SUPER_TURBO        ] = RAILWAY_SUPER_TURBO,
        [CPR_VOLTAGE_MODE_SUPER_TURBO_NO_CPR ] = RAILWAY_SUPER_TURBO_NO_CPR,
    };

    return (mode >= CPR_VOLTAGE_MODE_COUNT) ? RAILWAY_SUPER_TURBO_NO_CPR : map[mode];
}

void cpr_image_target_enable_measurements(cpr_rail* rail, cpr_measurement_type type)
{
    /* measurements are done in XBL */
}

void cpr_image_target_disable_measurements(cpr_rail* rail, cpr_measurement_type type)
{
    /* measurements are done in XBL */
}

__attribute__((section("cpr_dram_reclaim_pool")))
void cpr_image_target_init_mpm_ro_div_table(void)
{
    cpr_mode_settings* mode;
    cpr_domain_info    info = {CPR_DOMAIN_TYPE_MODE_BASED, {CPR_VOLTAGE_MODE_TURBO}};
    int32              table_idx;

    cpr_utils_get_mode_settings(CPR_RAIL_MX, &info, &mode, NULL);

    // convert the fuse steps to the table index
    table_idx = mode->decodedFuseSteps + CPR_MPM_RO_DIV_TABLE_COUNT/2;

    CPR_ASSERT((table_idx >= 0) && (table_idx < CPR_MPM_RO_DIV_TABLE_COUNT));

    cpr_image_memscpy(cpr_mpm_ro_div_table, cpr_mpm_ro_div_tables[table_idx], sizeof(cpr_mpm_ro_div_table));
}

uint16 cpr_image_target_get_mpm_ro_div(uint32 mxSleepUV)
{
    int idx = (mxSleepUV - CPR_MPM_RO_DIV_MIN_UV) / CPR_MPM_RO_DIV_STEP_UV;

    if(idx < 0)
    {
        idx = 0;
    }
    else if(idx >= CPR_MPM_RO_DIV_COUNT)
    {
        idx = CPR_MPM_RO_DIV_COUNT - 1;
    }

    return cpr_mpm_ro_div_table[idx];
}

boolean cpr_image_target_is_mx_chain_broken(void)
{
//TODO: Update Register bit, if we have parts to disable XO_shutdown, for now return "false"
    /*
     * From PTE folks:
     *
     * As for the fuse bit to identify the parts that cannot be calibrated for Mx CPR due to chain enumeration failures,
     * we will define a fuse bit "XO_shutdown_disable".
     * It will be left at default value of 0 for parts that have Mx CPR functional.
     * It will be blown as 1 for parts where it fails starting with CPR REV1 next week.
     *
     * QC Spare 16; Address: 0x780324, Bit #16
     */
#if 0
    cpr_xo_shutdown_disable_fuse = CPR_HWIO_IN(0x60780324);

    return ((cpr_xo_shutdown_disable_fuse & (1 << 16)) != 0);
#endif
    return false;
}

boolean cpr_image_target_is_retention_failed(void)
{
    return false;
}

void cpr_image_target_custom_fn(cpr_rail_state *rail)
{
  
	if((rail->id == CPR_RAIL_LPI_CX) && cpr_lpass_collapsed)
	{
		cpr_lpass_debug_info.cpr_interrupt_ignored_count++;
		cpr_lpass_debug_info.interrupt_ignored_time_stamp = time_service_now();
		return;
	}
	else if(rail->id == CPR_RAIL_LPI_CX)
	{
		rpm_spm_disable_lpass_shtdwn_interrupt();
	}

	return;
}

void cpr_image_target_lpi_controller_config(bool config)
{
	cpr_domain_id railId = CPR_RAIL_LPI_CX;
	cpr_rail* rail = cpr_utils_get_rail( railId );
	cpr_hal_handle* hdl = &rail->hal;
	
    // Disable/Enable LPI_CX CPR only when it is configured as Closed Loop
	if(!cpr_utils_is_closed_loop_mode(rail->id))
	{
		return;
	}
		
	if(config == true)
	{
		//disable LPI_CX cpr controller
		cpr_hal_enable_controller( hdl, false);
		cpr_lpass_collapsed = true;
	}
	else
	{
		//enable LPI_CX cpr controller
		cpr_hal_enable_controller( hdl, true );
		cpr_lpass_collapsed = false;
	}
	
	return;
}
