/*===========================================================================

  Copyright (c) 2012 Qualcomm Technologies Incorporated.
  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ===========================================================================*/

#include <stdlib.h>
#include <string.h>

#include "railway.h"

#include "railway_internal.h"
#include "railway_config.h"

#include "railway_adapter.h"
#include "kvp.h"
#include "rpmserver.h"
#include "coredump.h"
#include "pmapp_npa.h"

railway_internals_t railway;

__attribute__((section("railway_dram_reclaim_pool")))
void railway_init_v2(void)
{
    uint32 num_rails = RAILWAY_CONFIG_DATA->num_rails;

    uint32 rail_state_size = num_rails * sizeof(railway_rail_state_t);
    railway.rail_state = malloc(rail_state_size);
    CORE_VERIFY(railway.rail_state);
    memset(railway.rail_state, 0, rail_state_size);

    //Init rail groups.
    for(int i=0; i<RAILWAY_RAIL_GROUP_DATA->num_groups; i++)
    {
        RAILWAY_RAIL_GROUP_DATA->group_fns[i]->init_function();
    }

    railway_target_init();
    railway_adapter_init();
#ifndef QCS405_IMAGE_LAYOUT   
    railway_transitioner_init();
#endif 
    rpm_core_dump.railway_state  = &railway;
    rpm_core_dump.railway_config = RAILWAY_CONFIG_DATA;
}
