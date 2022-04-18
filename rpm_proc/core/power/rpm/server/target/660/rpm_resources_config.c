/*
===========================================================================

FILE:         rpm_resources_config.c

DESCRIPTION:
  Per target resource configurations

===========================================================================

                             Edit History

$Header: //components/rel/rpm.bf/1.8/core/power/rpm/server/target/660/rpm_resources_config.c#2 $
$Date: 2017/02/08 $

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

#include <stddef.h>
#include "rpm_resources_config.h"

/* -----------------------------------------------------------------------
**                           DATA
** ----------------------------------------------------------------------- */

static const rpm_resource_config_t temp_config_data[] =
{
    { RPM_SMPS_B_REQ,       5 },  // VDDMX
    { RPM_SMPS_B_REQ,       3 },  // VDDCX
    { RPM_LDO_B_REQ,       10 },  // LPI_MX
    { RPM_LDO_B_REQ ,       9 },  // LPI_CX
    { (rpm_resource_type)0, 0 }
};

const rpm_resource_config_t * const RESOURCE_CONFIG_DATA = temp_config_data;


/*
 * Resources dependent on BIMC resource
 * - be pre-processed before BIMC active->sleep transition
 * - be post-processed after BIMC sleep->active transition
 */
__attribute__((section("rpmserver_cram_reclaim_pool")))
const rpm_bimc_resource_config_t temp_bimc_config_data[] =
{
    {.type = RPM_BUS_SLAVE_REQ         , .id =  0}, // EBI1 SLAVE
    {.type = RPM_BUS_SLAVE_REQ         , .id =  2}, // BIMC SNOC SLAVE
    {.type = RPM_BUS_MASTER_REQ        , .id =  3}, // SNOC BIMC MASTER
    {.type = RPM_BUS_SLAVE_REQ         , .id =160}, // HMSS_L3 SLAVE
    {.type = RPM_BUS_MASTER_LATENCY_REQ, .id =  1}, // BIMC MASTER LATENCY (MSS PROC)
    {.type = RPM_BUS_MASTER_LATENCY_REQ, .id = 25}, // BIMC MASTER LATENCY (LPASS PROC)
    {(rpm_resource_type)0      ,  0}
};

const rpm_bimc_resource_config_t * const BIMC_RESOURCE_CONFIG_DATA = temp_bimc_config_data;

