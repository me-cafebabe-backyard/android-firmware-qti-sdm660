/*=============================================================================
 * FILE:                 sysmon_configdata_8998.c
 *
 * DESCRIPTION:
 *    Sysmon device configuration data for 8998 ADSP
 *
 * Copyright (c) 2016 QUALCOMM Technologies, Incorporated.
 * All Rights Reserved.
 * QUALCOMM Proprietary.
  ===========================================================================*/

/*=============================================================================
 *
 *                       EDIT HISTORY FOR FILE
 *
 *   This section contains comments describing changes made to the
 *   module. Notice that changes are listed in reverse chronological
 *   order.
 *
 * when         who          what, where, why
 * ----------   ------     ------------------------------------------------
 ============================================================================*/

#include <stdlib.h>
#include "DALDeviceId.h"
#include "DDIChipInfo.h"
#include "sysmon_devcfg_int.h"

const sd_devcfg_bus_clk_table_t bus_clk_table[]=
{
        {
        /* freqkHz */               100000,
        /* vRegLevel */             SYSMON_CLOCK_VREG_LEVEL_LOW_MINUS,
        },
        {
        /* freqkHz */               200000,
        /* vRegLevel */             SYSMON_CLOCK_VREG_LEVEL_LOW_MINUS,
        },
        {
        /* freqkHz */               300000,
        /* vRegLevel */             SYSMON_CLOCK_VREG_LEVEL_LOW,
        },
        {
        /* freqkHz */               768000,
        /* vRegLevel */             SYSMON_CLOCK_VREG_LEVEL_LOW,
        },
        {
        /* freqkHz */               1017600,
        /* vRegLevel */             SYSMON_CLOCK_VREG_LEVEL_LOW_PLUS,
        },
        {
        /* freqkHz */               1296000,
        /* vRegLevel */             SYSMON_CLOCK_VREG_LEVEL_NOMINAL,
        },
        {
        /* freqkHz */               1555200,
        /* vRegLevel */             SYSMON_CLOCK_VREG_LEVEL_NOMINAL,
        },
        {
        /* freqkHz */               1804800,
        /* vRegLevel */             SYSMON_CLOCK_VREG_LEVEL_HIGH,
        },
};

const sd_devcfg_bus_clk_desc_t bus_clk_descriptor =
{
        sizeof(bus_clk_table)/sizeof(sd_devcfg_bus_clk_table_t),
        (sd_devcfg_bus_clk_table_t *)bus_clk_table
};

const sd_devcfg_core_clk_table_t core_clk_table[]=
{
        {
        /* freqkHz */               144000,
        /* vRegLevel */             SYSMON_CLOCK_VREG_LEVEL_LOW_MINUS,
        },
        {
        /* freqkHz */               297600,
        /* vRegLevel */             SYSMON_CLOCK_VREG_LEVEL_LOW_MINUS,
        },
        {
        /* freqkHz */               480000,
        /* vRegLevel */             SYSMON_CLOCK_VREG_LEVEL_LOW,
        },
        {
        /* freqkHz */               652800,
        /* vRegLevel */             SYSMON_CLOCK_VREG_LEVEL_NOMINAL,
        },
        {
        /* freqkHz */               787200,
        /* vRegLevel */             SYSMON_CLOCK_VREG_LEVEL_HIGH,
        },
};

const sd_devcfg_core_clk_desc_t core_clk_descriptor =
{
        sizeof(core_clk_table)/sizeof(sd_devcfg_core_clk_table_t),
        (sd_devcfg_core_clk_table_t *)core_clk_table
};

const sd_devcfg_dcvs_params_t dcvsBalancedParams =
{
    /* dcvsTransientDur      = */    200,
    /* dcvsTransientDurMax   = */    500,
    /* q6LoadSafe            = */    70,
    /* q6LoadDanger          = */    90,
    /* q6Load1TSafe          = */    10,
    /* lowerCoreQ6Load       = */    68,
    /* lowerCoreQ6LoadAdj    = */    0,
    /* lowerCoreQ6LoadMin    = */    68,
    /* lowerCoreWinDur       = */    100,
    /* lowerCoreWinHFW       = */    0,
    /* lowerCoreWinDurAdj    = */    100,
    /* lowerCoreWinDurMax    = */    400,
    /* lowerBusWinDur        = */    200,
    /* lowerBusWinHFW        = */    50,
    /* pCppDangerLevel       = */    10,
    /* pCppSafeLevel         = */    5,
    /* coreStallsDangerLevel = */    40,
	/* pCppSafe1TLevel       = */    30,
};

const sd_devcfg_dcvs_params_t dcvsPerformanceParams =
{
    /* dcvsTransientDur      = */    200,
    /* dcvsTransientDurMax   = */    500,
    /* q6LoadSafe            = */    70,
    /* q6LoadDanger          = */    90,
    /* q6Load1TSafe          = */    10,
    /* lowerCoreQ6Load       = */    68,
    /* lowerCoreQ6LoadAdj    = */    10,
    /* lowerCoreQ6LoadMin    = */    48,
    /* lowerCoreWinDur       = */    200,
    /* lowerCoreWinHFW       = */    0,
    /* lowerCoreWinDurAdj    = */    100,
    /* lowerCoreWinDurMax    = */    600,
    /* lowerBusWinDur        = */    200,
    /* lowerBusWinHFW        = */    50,
    /* pCppDangerLevel       = */    10,
    /* pCppSafeLevel         = */    5,
    /* coreStallsDangerLevel = */    40,
	/* pCppSafe1TLevel       = */    30,
};

const sd_devcfg_dcvs_params_t dcvsPowerSaverParams =
{
    /* dcvsTransientDur      = */    200,
    /* dcvsTransientDurMax   = */    500,
    /* q6LoadSafe            = */    90,
    /* q6LoadDanger          = */    98,
    /* q6Load1TSafe          = */    10,
    /* lowerCoreQ6Load       = */    88,
    /* lowerCoreQ6LoadAdj    = */    10,
    /* lowerCoreQ6LoadMin    = */    68,
    /* lowerCoreWinDur       = */    100,
    /* lowerCoreWinHFW       = */    0,
    /* lowerCoreWinDurAdj    = */    100,
    /* lowerCoreWinDurMax    = */    300,
    /* lowerBusWinDur        = */    200,
    /* lowerBusWinHFW        = */    50,
    /* pCppDangerLevel       = */    10,
    /* pCppSafeLevel         = */    5,
    /* coreStallsDangerLevel = */    40,
	/* pCppSafe1TLevel       = */    30,
};

const sd_devcfg_dcvs_params_t dcvsPowerSaverAggressiveParams =
{
    /* dcvsTransientDur      = */    100,
    /* dcvsTransientDurMax   = */    500,
    /* q6LoadSafe            = */    90,
    /* q6LoadDanger          = */    98,
    /* q6Load1TSafe          = */    10,
    /* lowerCoreQ6Load       = */    88,
    /* lowerCoreQ6LoadAdj    = */    10,
    /* lowerCoreQ6LoadMin    = */    78,
    /* lowerCoreWinDur       = */    50,
    /* lowerCoreWinHFW       = */    0,
    /* lowerCoreWinDurAdj    = */    100,
    /* lowerCoreWinDurMax    = */    250,
    /* lowerBusWinDur        = */    100,
    /* lowerBusWinHFW        = */    50,
    /* pCppDangerLevel       = */    10,
    /* pCppSafeLevel         = */    5,
    /* coreStallsDangerLevel = */    40,
	/* pCppSafe1TLevel       = */    30,
};

const sd_vreg_type_t dcvsClientCornerVoteCoreConv[] = {
        SYSMON_CLOCK_VREG_LEVEL_OFF,
        SYSMON_CLOCK_VREG_LEVEL_LOW_MINUS,
        SYSMON_CLOCK_VREG_LEVEL_LOW,
        SYSMON_CLOCK_VREG_LEVEL_LOW_PLUS,
        SYSMON_CLOCK_VREG_LEVEL_NOMINAL,
        SYSMON_CLOCK_VREG_LEVEL_NOMINAL,
        SYSMON_CLOCK_VREG_LEVEL_HIGH,
};

const sd_vreg_type_t dcvsClientCornerVoteBusConv[] = {
        SYSMON_CLOCK_VREG_LEVEL_OFF,
        SYSMON_CLOCK_VREG_LEVEL_LOW_MINUS,
        SYSMON_CLOCK_VREG_LEVEL_LOW,
        SYSMON_CLOCK_VREG_LEVEL_LOW,
        SYSMON_CLOCK_VREG_LEVEL_NOMINAL,
        SYSMON_CLOCK_VREG_LEVEL_NOMINAL,
        SYSMON_CLOCK_VREG_LEVEL_HIGH,
};

const sd_hvx_rm_descriptor_t hvxRMDesc = {
        /* resThresPerc (<100)   = */ 50,   //Threshold in percentage to be used in HVX reserve calls. Max 100.
        /* tryLockTimeout        = */ 200,  //Default timeout in milli-seconds for try_lock call
        /* lockTimeout           = */ 200,  //Default timeout in milli-seconds for lock call
        /* obsWinDur             = */ 200,  //Observation window for tracking resource activity
};
