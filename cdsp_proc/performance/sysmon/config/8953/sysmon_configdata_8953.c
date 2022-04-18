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
        /* vRegLevel */             SYSMON_CLOCK_VREG_LEVEL_LOW_MINUS,
        },
        {
        /* freqkHz */               50000,
        /* vRegLevel */             SYSMON_CLOCK_VREG_LEVEL_LOW_MINUS,
        },
        {
        /* freqkHz */               100000,
        /* vRegLevel */             SYSMON_CLOCK_VREG_LEVEL_LOW,
        },
        {
        /* freqkHz */               133330,
        /* vRegLevel */             SYSMON_CLOCK_VREG_LEVEL_LOW_PLUS,
        },
        {
        /* freqkHz */               160000,
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
        /* vRegLevel */             SYSMON_CLOCK_VREG_LEVEL_LOW_MINUS,
        },
        {
        /* freqkHz */               115200,
        /* vRegLevel */             SYSMON_CLOCK_VREG_LEVEL_LOW_MINUS,
        },
        {
        /* freqkHz */               230400,
        /* vRegLevel */             SYSMON_CLOCK_VREG_LEVEL_LOW_MINUS,
        },
        {
        /* freqkHz */               326400,
        /* vRegLevel */             SYSMON_CLOCK_VREG_LEVEL_LOW_MINUS,
        },
        {
        /* freqkHz */               499200,
        /* vRegLevel */             SYSMON_CLOCK_VREG_LEVEL_LOW,
        },
        {
        /* freqkHz */               556800,
        /* vRegLevel */             SYSMON_CLOCK_VREG_LEVEL_LOW_PLUS,
        },
        {
        /* freqkHz */               691200,
        /* vRegLevel */             SYSMON_CLOCK_VREG_LEVEL_NOMINAL,
        },
        {
        /* freqkHz */               748800,
        /* vRegLevel */             SYSMON_CLOCK_VREG_LEVEL_NOMINAL_PLUS,
        },
        {
        /* freqkHz */               844800,
        /* vRegLevel */             SYSMON_CLOCK_VREG_LEVEL_HIGH,
        },
};

const sd_devcfg_core_clk_desc_t core_clk_descriptor =
{
        sizeof(core_clk_table)/sizeof(sd_devcfg_core_clk_table_t),
        (sd_devcfg_core_clk_table_t *)core_clk_table
};
