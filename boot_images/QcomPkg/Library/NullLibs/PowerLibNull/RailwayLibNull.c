/** @file RailwayLibNull.c
  
  Stub functions for RailwayLib

  Copyright (c) 2014-2015, Qualcomm Technologies, Inc. All rights reserved.
**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 06/04/15   vk      Fix linux build
 05/14/15   plc     Update with newer api's post 8996
 09/24/14   ck      Initial revision

=============================================================================*/


/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include "../../../Library/RailwayLib/railway_config.h"
#include "pm_smps.h"
#include "pm_ldo.h"

/*===========================================================================
                             LOCAL DEFINITIONS
===========================================================================*/

//
// BEGIN config data; should migrate to the system enumeration data method
//
static const railway_config_data_t temp_config_data =
{
    .rails     = (railway_rail_config_t[])
    {
        //Must init Mx first, as voting on the other rails will cause Mx changes to occur.
        {
            .rail_type = RAILWAY_RAIL_TYPE_MX,
            .vreg_name = "vddmx",

            // SMPS2A
            .pmic_rail_type = RAILWAY_SMPS_TYPE,
            .pmic_chip_id   = 0,
            .pmic_peripheral_index = PM_SMPS_2,

            .pmic_step_size = 5000,

            .initial_corner = RAILWAY_NO_REQUEST,

            .default_uvs = (const uint32[])
            {
                0,                      // RAILWAY_NO_REQUEST
                590000,                 // RAILWAY_RETENTION          - rounded 587500
                850000,                 // RAILWAY_SVS_KRAIT
                850000,                 // RAILWAY_SVS_SOC
                850000,                 // RAILWAY_SVS_HIGH
                915000,                 // RAILWAY_NOMINAL            - rounded 912500
                990000,                 // RAILWAY_TURBO              - rounded 987500
                990000,                 // RAILWAY_TURBO_HIGH         - rounded 987500
                990000,                 // RAILWAY_SUPER_TURBO        - rounded 987500
                990000,                 // RAILWAY_SUPER_TURBO_NO_CPR - rounded 987500
            },

            .supported_corners = (railway_corner[])
            {
                RAILWAY_RETENTION,
                RAILWAY_SVS_SOC,
                RAILWAY_NOMINAL,
                RAILWAY_SUPER_TURBO,
            },
            .supported_corners_count = 4,
        },

        // VDDCX
        {
            .rail_type = RAILWAY_RAIL_TYPE_LOGIC,
            .vreg_name = "vddcx",

            // SMPS1A
            .pmic_rail_type = RAILWAY_SMPS_TYPE,
            .pmic_chip_id   = 0,
            .pmic_peripheral_index = PM_SMPS_1,

            .pmic_step_size = 5000,

            .initial_corner = RAILWAY_NOMINAL,

            .default_uvs = (const uint32[])
            {
                0,                      // RAILWAY_NO_REQUEST
                400000,                 // RAILWAY_RETENTION
                640000,                 // RAILWAY_SVS_KRAIT          - rounded 637500
                715000,                 // RAILWAY_SVS_SOC            - rounded 712500
                715000,                 // RAILWAY_SVS_HIGH           - rounded 712500
                865000,                 // RAILWAY_NOMINAL            - rounded 862500
                990000,                 // RAILWAY_TURBO              - rounded 987500
                990000,                 // RAILWAY_TURBO_HIGH         - rounded 987500
                990000,                 // RAILWAY_SUPER_TURBO        - rounded 987500
                990000,                 // RAILWAY_SUPER_TURBO_NO_CPR - rounded 987500
            },

            .supported_corners = (railway_corner[])
            {
                RAILWAY_RETENTION,
                RAILWAY_SVS_KRAIT,      // aka RAILWAY_SVS_LOW or SVS2
                RAILWAY_SVS_SOC,
                RAILWAY_NOMINAL,
                RAILWAY_SUPER_TURBO,
            },
            .supported_corners_count = 5,
        },

        // VDDA_EBI
        {
            .rail_type = RAILWAY_RAIL_TYPE_EBI,
            .vreg_name = "vdda_ebi",

            // LDO26A
            .pmic_rail_type = RAILWAY_LDO_TYPE,
            .pmic_chip_id   = 0,
            .pmic_peripheral_index = PM_LDO_3,

            .pmic_step_size = 12500,

            .initial_corner = RAILWAY_RETENTION,

            .default_uvs = (const uint32[])
            {
                0,                      // RAILWAY_NO_REQUEST
                587500,                 // RAILWAY_RETENTION
                850000,                 // RAILWAY_SVS_KRAIT
                850000,                 // RAILWAY_SVS_SOC
                850000,                 // RAILWAY_SVS_HIGH
                912500,                 // RAILWAY_NOMINAL
                987500,                 // RAILWAY_TURBO
                987500,                 // RAILWAY_TURBO_HIGH
                987500,                 // RAILWAY_SUPER_TURBO
                987500,                 // RAILWAY_SUPER_TURBO_NO_CPR
            },

            .supported_corners = (railway_corner[])
            {
                  RAILWAY_RETENTION,
                  RAILWAY_SVS_SOC,
                  RAILWAY_NOMINAL,
                  RAILWAY_SUPER_TURBO,
            },
            .supported_corners_count = 4,
        },
    },

    .num_rails = 3,
};
//
// END config data
//

const railway_config_data_t * const RAILWAY_CONFIG_DATA = &temp_config_data;

/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/ 

void railway_target_init(void)
{
  return;
}

