/*===========================================================================
                              railway_aggregator.c

SERVICES:

DESCRIPTION:

INITIALIZATION AND SEQUENCING REQUIREMENTS:
  Description...

Copyright (c) 2013 Qualcomm Technologies, Inc.  All Rights Reserved.
QUALCOMM Proprietary.  Export of this technology or software is regulated
by the U.S. Government. Diversion contrary to U.S. law prohibited.
===========================================================================*/


//===========================================================================
//                     Includes and Variable Definitions
//===========================================================================

//---------------------------------------------------------------------------
// Include Files
//---------------------------------------------------------------------------
#include "railway.h"
#include "railway_internal.h"
#include "CoreVerify.h"
#include "railway_config.h"
#include "rpmserver.h"
#include "pm_npa_irep.h"

//---------------------------------------------------------------------------
// Type Declarations
//---------------------------------------------------------------------------
struct railway_sw_mode_state;

typedef struct railway_sw_mode_voter_s {
    unsigned server_handle;
    pm_npa_smps_int_rep server_vote;
    int rail_id;
} railway_sw_mode_voter_s;

//We don't actually care about the rail ID since we treat the automode as coupled for
//vddcx and vddmx
railway_sw_mode_voter_t railway_create_sw_mode_voter(int rail, int id)
{
  //Rail ID goes from 0 to (num_rails-1)
  CORE_VERIFY(rail<RAILWAY_CONFIG_DATA->num_rails);
  const railway_rail_config_t *rail_config = &RAILWAY_CONFIG_DATA->rails[rail];

  //We only support this for SMPS rails.
  CORE_VERIFY((rail_config->vreg_type & VREG_TYPE_MASK)==VREG_TYPE_SMPS);
  
  railway_sw_mode_voter_t voter = (railway_sw_mode_voter_t)malloc(sizeof(railway_sw_mode_voter_s));
  CORE_VERIFY_PTR(voter);
  
  voter->server_handle = rpm_create_client(rail_config->vreg_type, rail_config->vreg_num, 0);
  CORE_VERIFY(0xFFFFFFFF!=voter->server_handle);    //Validate the handle
  
  memset(&voter->server_vote, 0, sizeof(pm_npa_smps_int_rep));
  voter->rail_id = rail;
  return voter;
}

// Update this voter's sw mode vote. The default value is PM_NPA_SW_MODE_SMPS__AUTO
// Changing a vote will result in all voters being agregated, and if the agregation changes
// then the sw mode request will be forwarded to the PMIC driver straight away.
void railway_sw_mode_vote(railway_sw_mode_voter_t voter, pm_npa_sw_mode_smps_type sw_mode)
{
    CORE_VERIFY(voter);
    const railway_rail_config_t *rail_config = &RAILWAY_CONFIG_DATA->rails[voter->rail_id];

    voter->server_vote.smps_sw_mode = sw_mode;
    
    rpm_issue_request(rail_config->vreg_type, rail_config->vreg_num, voter->server_handle, sizeof(pm_npa_smps_int_rep), &voter->server_vote);       
}
