/*
===========================================================================

FILE:         acc_config.c

DESCRIPTION:
  Per target ACC configurations

===========================================================================

                             Edit History

$Header: //components/rel/rpm.bf/1.8/core/power/acc/src/660/acc_config.c#2 $
$Date: 2016/11/23 $

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

#include "acc.h"
#include "tcsr_hwio_acc.h"

/* -----------------------------------------------------------------------
**                           DATA
** ----------------------------------------------------------------------- */

const unsigned acc_register_settings[ACC_REGISTER_NUM_SETTING] =
{
    0x1,    // SVS_REGISTER_SVS_SETTING
    0x0,    // SVS_REGISTER_NOM_SETTING
};

const acc_target_config acc_config =
{
   .config = (const acc_control_config[])
    {
        {
        .rail_name = "vddcx",
        .acc_register_setting = (const int[])
            {
                ACC_MODE_NOT_SUPPORTED,         // RAILWAY_NO_REQUEST
                ACC_REGISTER_SVS_SETTING,       // RAILWAY_RETENTION
                ACC_REGISTER_SVS_SETTING,       // RAILWAY_SVS_MIN
                ACC_REGISTER_SVS_SETTING,       // RAILWAY_SVS_LOW
                ACC_REGISTER_SVS_SETTING,       // RAILWAY_SVS
                ACC_REGISTER_NOM_SETTING,       // RAILWAY_SVS_HIGH
                ACC_REGISTER_NOM_SETTING,       // RAILWAY_NOMINAL
				ACC_REGISTER_NOM_SETTING,       // RAILWAY_NOMINAL_HIGH
                ACC_REGISTER_NOM_SETTING,       // RAILWAY_TURBO
                ACC_REGISTER_NOM_SETTING,       // RAILWAY_SUPER_TURBO
                ACC_MODE_NOT_SUPPORTED,         // RAILWAY_SUPER_TURBO_NO_CPR
            },
        .acc_register_address = (volatile unsigned*) HWIO_TCSR_MEM_SVS_SEL_VDDCX_ADDR,
        },
        {
        .rail_name = "vdd_lpi_cx",
        .acc_register_setting = (const int[])
            {
                ACC_REGISTER_SVS_SETTING,       // RAILWAY_NO_REQUEST
                ACC_REGISTER_SVS_SETTING,       // RAILWAY_RETENTION
                ACC_REGISTER_SVS_SETTING,       // RAILWAY_SVS_MIN
                ACC_REGISTER_SVS_SETTING,       // RAILWAY_SVS_LOW
                ACC_REGISTER_SVS_SETTING,       // RAILWAY_SVS
                ACC_REGISTER_NOM_SETTING,       // RAILWAY_SVS_HIGH
                ACC_REGISTER_NOM_SETTING,       // RAILWAY_NOMINAL
				ACC_REGISTER_NOM_SETTING,       // RAILWAY_NOMINAL_HIGH
                ACC_REGISTER_NOM_SETTING,       // RAILWAY_TURBO
                ACC_REGISTER_NOM_SETTING,       // RAILWAY_SUPER_TURBO
                ACC_MODE_NOT_SUPPORTED,         // RAILWAY_SUPER_TURBO_NO_CPR
            },
        .acc_register_address = (volatile unsigned*) HWIO_TCSR_MEM_SVS_SEL_VDDLPI_ADDR,
        },

    },
    .number_of_acc_controls = 2,
};


const acc_target_config* ACC_TARGET_CONFIG = &acc_config;


