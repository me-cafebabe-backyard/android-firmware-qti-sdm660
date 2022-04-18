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
#include "DALSys.h"
#include "CoreVerify.h"

void acc_init(void);

railway_internals_t railway;
int mx_rail_id = RAIL_NOT_SUPPORTED_BY_RAILWAY;
int cx_rail_id = RAIL_NOT_SUPPORTED_BY_RAILWAY;
int ebi_rail_id = RAIL_NOT_SUPPORTED_BY_RAILWAY;
int wlan_rail_id = RAIL_NOT_SUPPORTED_BY_RAILWAY;


static void railway_init_voter(int rail_id, railway_voter_id voter_id, railway_corner corner)
{
    railway_voter_t voter = railway_create_voter(rail_id, voter_id);
    railway_corner_vote(voter, corner);
}

void railway_init(void)
{
    uint32 num_rails = RAILWAY_CONFIG_DATA->num_rails;

    uint32 rail_state_size = num_rails * sizeof(railway_rail_state_t);

    DALResult dalResult = DALSYS_Malloc(rail_state_size, (void**)&railway.rail_state);
    CORE_VERIFY_PTR(railway.rail_state);
    CORE_VERIFY(dalResult==DAL_SUCCESS);

    memset(railway.rail_state, 0, rail_state_size);

    railway_transitioner_init(); // initialize all rails
    railway_target_init(); /* should be called after railway_transitioner_init
                            * since railway.rail_state[] are initialized with default values.
                            */

    cx_rail_id = rail_id("vddcx");
    CORE_VERIFY(RAIL_NOT_SUPPORTED_BY_RAILWAY!=cx_rail_id);

    //init time request for lowest active level on CX internal
    railway_init_voter(cx_rail_id, RAILWAY_RPM_CX_VOTER_ID, RAILWAY_NOMINAL);

    mx_rail_id = rail_id("vddmx");
    CORE_VERIFY(RAIL_NOT_SUPPORTED_BY_RAILWAY!=mx_rail_id);

    //init time request for lowest active level on MX internal
    railway_init_voter(mx_rail_id, RAILWAY_RPM_MX_VOTER_ID, RAILWAY_NOMINAL);

#if 0
    ebi_rail_id = rail_id("vdda_ebi");
    CORE_VERIFY(RAIL_NOT_SUPPORTED_BY_RAILWAY!=ebi_rail_id);

    //init time request for lowest active level on EBI internal
    railway_init_voter(ebi_rail_id, RAILWAY_RPM_EBI_VOTER_ID, RAILWAY_NOMINAL);
#endif
    wlan_rail_id = rail_id("vdda_wlan");
    CORE_VERIFY(RAIL_NOT_SUPPORTED_BY_RAILWAY!=wlan_rail_id);

    //init time request for lowest active level on WLAN internal
    railway_init_voter(wlan_rail_id, RAILWAY_RPM_WLAN_VOTER_ID, RAILWAY_NOMINAL);

//    acc_init();
}

