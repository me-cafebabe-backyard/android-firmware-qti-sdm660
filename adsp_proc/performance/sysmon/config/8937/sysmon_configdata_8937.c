/*=============================================================================
 * FILE:                 sysmon_configdata_8994.c
 *
 * DESCRIPTION:
 *    Sysmon device configuration data for 8994 ADSP
 *
 * Copyright (c) 2014 QUALCOMM Technologies, Incorporated.
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
        /* freqkHz */               19200,
        /* vRegLevel */             SYSMON_CLOCK_VREG_LEVEL_LOW,
        },
        {
        /* freqkHz */               50000,
        /* vRegLevel */             SYSMON_CLOCK_VREG_LEVEL_LOW,
        },
        {
        /* freqkHz */               100000,
        /* vRegLevel */             SYSMON_CLOCK_VREG_LEVEL_LOW,
        },
        {
        /* freqkHz */               145450,
        /* vRegLevel */             SYSMON_CLOCK_VREG_LEVEL_LOW_PLUS,
        },
        {
        /* freqkHz */               200000,
        /* vRegLevel */             SYSMON_CLOCK_VREG_LEVEL_NOMINAL,
        },
        {
        /* freqkHz */               228570,
        /* vRegLevel */             SYSMON_CLOCK_VREG_LEVEL_NOMINAL_PLUS,
        },
        {
        /* freqkHz */               266670,
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
        /* freqkHz */               19200,
        /* vRegLevel */             SYSMON_CLOCK_VREG_LEVEL_LOW,
        },
        {
        /* freqkHz */               115200,
        /* vRegLevel */             SYSMON_CLOCK_VREG_LEVEL_LOW,
        },
        {
        /* freqkHz */               144000,
        /* vRegLevel */             SYSMON_CLOCK_VREG_LEVEL_LOW,
        },
        {
        /* freqkHz */               230400,
        /* vRegLevel */             SYSMON_CLOCK_VREG_LEVEL_LOW,
        },
        {
        /* freqkHz */               288000,
        /* vRegLevel */             SYSMON_CLOCK_VREG_LEVEL_LOW,
        },
        {
        /* freqkHz */               384000,
        /* vRegLevel */             SYSMON_CLOCK_VREG_LEVEL_LOW,
        },
        {
        /* freqkHz */               480000,
        /* vRegLevel */             SYSMON_CLOCK_VREG_LEVEL_LOW_PLUS,
        },
        {
        /* freqkHz */               576000,
        /* vRegLevel */             SYSMON_CLOCK_VREG_LEVEL_NOMINAL,
        },
        {
        /* freqkHz */               614400,
        /* vRegLevel */             SYSMON_CLOCK_VREG_LEVEL_NOMINAL_PLUS,
        },
        {
        /* freqkHz */               691200,
        /* vRegLevel */             SYSMON_CLOCK_VREG_LEVEL_HIGH,
        },
};

const sd_devcfg_core_clk_desc_t core_clk_descriptor =
{
        sizeof(core_clk_table)/sizeof(sd_devcfg_core_clk_table_t),
        (sd_devcfg_core_clk_table_t *)core_clk_table
};
