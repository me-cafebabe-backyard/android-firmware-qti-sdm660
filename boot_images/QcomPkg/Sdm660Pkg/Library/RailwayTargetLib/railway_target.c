#include "railway_config.h"
#include "CoreVerify.h"
#include "msmhwio.h"
#include "railway.h"
#include "cpr_fuses_hwio.h"

/* -----------------------------------------------------------------------
**                           FUNCTIONS
** ----------------------------------------------------------------------- */


extern int wlan_rail_id;

volatile uint32 wlan_fuse_value;

typedef uint32 (*custom_read_fuse_setting_cb_t)(void);

typedef struct
{
    const uint32 *retention_values;
    const custom_read_fuse_setting_cb_t custom_read_fuse_setting_cb;
} pvs_data_t;

static uint32 read_wlan_fuse_setting(void);

// WLAN uses the same table as the mx/lpi_mx rail
static const uint32 vddwlan_pvs_retention_data[8] =
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

static pvs_data_t vddwlan_pvs_data =
{
    /* .retention_values            */ vddwlan_pvs_retention_data,
    /* .custom_read_fuse_setting_cb */ read_wlan_fuse_setting
};

// WLAN uses the same fuse as the mx rail
static uint32 read_wlan_fuse_setting(void)
{
    /*	0x780148[17:19] */
    return (HWIO_INM(QFPROM_RAW_PTE_ROW3_LSB, (0x7 << 17)) >> 17);
}

static uint32 set_sleep_voltage(int rail_id, pvs_data_t *pvs_data_ptr)
{
  uint32 lookup_val;

  CORE_VERIFY_PTR(pvs_data_ptr->custom_read_fuse_setting_cb);
  lookup_val = pvs_data_ptr->custom_read_fuse_setting_cb();

  CORE_VERIFY(lookup_val < 8);

  railway_set_retention_voltage(rail_id, pvs_data_ptr->retention_values[lookup_val]);

  return lookup_val;
}


//Any early target-specific init should be done in this function.
void railway_target_init(void)
{

	wlan_rail_id = rail_id("vdda_wlan");
	CORE_VERIFY(RAIL_NOT_SUPPORTED_BY_RAILWAY!=wlan_rail_id);

	wlan_fuse_value = set_sleep_voltage(wlan_rail_id, &vddwlan_pvs_data);
}

