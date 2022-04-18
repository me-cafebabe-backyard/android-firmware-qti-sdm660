
/*============================================================================
  FILE:         sleep_target_config.c

  OVERVIEW:     This file provides target-specific functionality for the RPM.

  DEPENDENCIES: None

                Copyright (c) 2015-2016 Qualcomm Technologies, Inc.
                All Rights Reserved.
                Qualcomm Confidential and Proprietary

  $Header: //components/rel/rpm.bf/1.8/core/power/sleep/src/660/sleep_target_config.c#3 $
  $DateTime: 2017/02/14 22:42:16 $
  $Author: pwbldsvc $
============================================================================*/

#include "qfprom_pte_lpass_hwio.h"
#include "msmhwiobase.h"
#include "msmhwio.h"
#include "railway.h"
#include "Chipinfo.h"
#include "CoreVerify.h"
#include "cpr.h"


extern int cx_id, mx_id;
extern volatile boolean mock_vdd_min_only;

volatile uint32 cx_fuse_value;
volatile uint32 mx_fuse_value;


/*
 * EARLY_INIT below
 */

typedef struct
{
    uint32 address;
    uint8 offset;
    uint8 mask;
} fuse_t;

typedef struct
{
    const uint32 *retention_table;
    const fuse_t  fuse;
} pvs_data_t;



// retention programmed in uV ( 600000uV = 0.6V )
__attribute__((section("sleep_cram_reclaim_pool")))
static const uint32 vddcx_retention_table[8] =
{
  /* 000 */ 600000,
  /* 001 */ 552000,
  /* 010 */ 500000,
  /* 011 */ 452000,
  /* 100 */ 400000,
  /* 101 */ 600000,
  /* 110 */ 600000,
  /* 111 */ 600000
};

__attribute__((section("sleep_cram_reclaim_pool")))
static const uint32 vddmx_retention_data[8] =
{
  /* 000 */ 700000,
  /* 001 */ 652000,
  /* 010 */ 580000,
  /* 011 */ 552000,
  /* 100 */ 492000,
  /* 101 */ 700000,
  /* 110 */ 700000,
  /* 111 */ 700000
};

__attribute__((section("sleep_cram_reclaim_pool")))
static const uint32 vdd_lpimx_retention_data[8] =
{
  /* 000 */ 704000,
  /* 001 */ 656000,
  /* 010 */ 584000,
  /* 011 */ 552000,
  /* 100 */ 496000,
  /* 101 */ 704000,
  /* 110 */ 704000,
  /* 111 */ 704000
};

__attribute__((section("sleep_cram_reclaim_pool")))
static const uint32 vdd_lpicx_retention_data[8] =
{
  /* 000 */ 600000,
  /* 001 */ 552000,
  /* 010 */ 504000,
  /* 011 */ 456000,
  /* 100 */ 400000,
  /* 101 */ 600000,
  /* 110 */ 600000,
  /* 111 */ 600000
};


__attribute__((section("sleep_cram_reclaim_pool")))
static const pvs_data_t vddcx_pvs_data =
{
    /* .retention_table */ vddcx_retention_table,
    /* .fuse            */ { HWIO_ADDR(QFPROM_RAW_PTE_ROW0_MSB), 29, 0x7 }
};

__attribute__((section("sleep_cram_reclaim_pool")))
static const pvs_data_t vddmx_pvs_data =
{
    /* .retention_table */ vddmx_retention_data,
    /* .fuse            */ { HWIO_ADDR(QFPROM_RAW_PTE_ROW3_LSB), 17, 0x7 }
};


/* lpi_mx,lpi_cx follows system mx,cx respectively. But its a 8mV stepper instead of 4mV
 * which could causes the floor to be different voltage levels, hence 
 * a seperate table is used */
__attribute__((section("sleep_cram_reclaim_pool")))
static const pvs_data_t vdd_lpimx_pvs_data =
{
    /* .retention_table */ vdd_lpimx_retention_data,
    /* .fuse            */ { HWIO_ADDR(QFPROM_RAW_PTE_ROW3_LSB), 17, 0x7 }
};

__attribute__((section("sleep_cram_reclaim_pool")))
static const pvs_data_t vdd_lpicx_pvs_data =
{
    /* .retention_table */ vdd_lpicx_retention_data,
    /* .fuse            */ { HWIO_ADDR(QFPROM_RAW_PTE_ROW0_MSB), 29, 0x7 }
};

__attribute__((section("sleep_cram_reclaim_pool")))
static uint32 read_fuse_value(const fuse_t *fuse)
{
    return ( __inpdw(fuse->address) >> fuse->offset ) & (uint32)fuse->mask;
}

__attribute__((section("sleep_cram_reclaim_pool")))
static uint32 set_sleep_voltage(int rail_id, const pvs_data_t *pvs_data_ptr)
{
  uint32 lookup_val = read_fuse_value( &pvs_data_ptr->fuse );

  railway_set_retention_voltage(rail_id, pvs_data_ptr->retention_table[lookup_val]);

  return lookup_val;
}


__attribute__((section("sleep_cram_reclaim_pool")))
void sleep_voltages_init(void)
{
    int lpi_cx_id = rail_id("vdd_lpi_cx");
    int lpi_mx_id = rail_id("vdd_lpi_mx");

    CORE_VERIFY(RAIL_NOT_SUPPORTED_BY_RAILWAY!=lpi_cx_id);
    CORE_VERIFY(RAIL_NOT_SUPPORTED_BY_RAILWAY!=lpi_mx_id);

    cx_fuse_value = set_sleep_voltage(cx_id, &vddcx_pvs_data);
    mx_fuse_value = set_sleep_voltage(mx_id, &vddmx_pvs_data);

    (void)set_sleep_voltage(lpi_cx_id, &vdd_lpicx_pvs_data);
    (void)set_sleep_voltage(lpi_mx_id, &vdd_lpimx_pvs_data);

    /*
     * CR1010811 - Enable mock vdd min to restrict MX sleep voltage
     * to the known voltage used to pre-calculate MPM RO divider.
     *  TODO: Need to check with PTE on this for Starlord
     */
    if(cpr_is_mx_chain_broken())
    {
        mock_vdd_min_only = TRUE;
    }

}

