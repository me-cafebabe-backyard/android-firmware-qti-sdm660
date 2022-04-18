/*
===========================================================================

FILE:         railway_config.c

DESCRIPTION:
  Per target railway configurations

===========================================================================

                             Edit History

$Date: 2017/01/11 $

when       who     what, where, why
--------   ---     --------------------------------------------------------

===========================================================================
             Copyright (c) 2013 Qualcomm Technologies Incorporated.
                    All Rights Reserved.
              QUALCOMM Proprietary and Confidential
===========================================================================
*/

/* -----------------------------------------------------------------------
**                           INCLUDES
** ----------------------------------------------------------------------- */

#include "railway_config.h"
#include "pm_ldo.h"
#include "pm_smps.h"
#include "pm_version.h" 

/* -----------------------------------------------------------------------
**                           DATA
** ----------------------------------------------------------------------- */

//
// BEGIN config data; should migrate to the system enumeration data method
//
static const railway_config_data_t temp_config_data =
{
    .rails     = (railway_rail_config_t[])
    {
        //Must init Mx first, as voting on the other rails will cause Mx changes to occur.
        {
            .vreg_name = "vddmx",

            // SMPS5B
            .pmic_rail_type = RAILWAY_SMPS_TYPE,
            .pmic_chip_id   = 1,
            .pmic_peripheral_index = PM_SMPS_5,


            .initial_corner = RAILWAY_NO_REQUEST,
            .default_retention_uv = 488000,
        },

        // VDDCX
        {
            .vreg_name = "vddcx",

            // SMPS3B
            .pmic_rail_type = RAILWAY_SMPS_TYPE,
            .pmic_chip_id   = 1,
            .pmic_peripheral_index = PM_SMPS_3,

            .initial_corner = RAILWAY_NO_REQUEST,
            .default_retention_uv = 400000,
        },
		
		// VDDWLAN
        {
            .vreg_name = "vdda_wlan",

            // LDO5
            .pmic_rail_type = RAILWAY_LDO_TYPE,
            .pmic_chip_id   = 0,
            .pmic_peripheral_index = PM_LDO_5,

            .initial_corner = RAILWAY_NOMINAL,
            .default_retention_uv = 700000,
        },
    },

    .num_rails = 3,
};
//
// END config data
//

const railway_config_data_t * const RAILWAY_CONFIG_DATA = &temp_config_data;

