/*===========================================================================
                              railway_aggregator.c

SERVICES:

DESCRIPTION:

INITIALIZATION AND SEQUENCING REQUIREMENTS:
  Description...

Copyright (c) 2013-2016 Qualcomm Technologies, Inc.  All Rights Reserved.
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
#include <stdlib.h>
#include <stdbool.h>
#include <stringl/stringl.h>
#include "railway_config.h"
#include "cpr.h"

//---------------------------------------------------------------------------
// Constant / Define Declarations
//--------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Type Declarations
//---------------------------------------------------------------------------
typedef struct railway_voter_s
{
    railway_corner         voltage_corner;
    railway_corner         active_floor;
    bool                   suppressible;
    int                    id;
    int                    rail;
#if 0 // sw_enable is not used
    bool                   sw_enable;
#endif
    railway_voter_t        voter_link; //Need a better plan for the linked list.
} railway_voter_s;

//---------------------------------------------------------------------------
// Global Constant Definitions
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Local Object Definitions
//---------------------------------------------------------------------------
static railway_corners_t supported_corners;


//---------------------------------------------------------------------------
// Static Variable Definitions
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Forward Declarations
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// External References
//---------------------------------------------------------------------------


//===========================================================================
//                             Macro Definitions
//===========================================================================

//===========================================================================
//                           Function Definitions
//===========================================================================

/*===========================================================================
FUNCTION: railway_create_voter

DESCRIPTION:

RETURN VALUE:
===========================================================================*/
railway_voter_t railway_create_voter(int rail, bool suppressible, int id)
{
  //Rail ID goes from 0 to (num_rails-1)
  CORE_VERIFY(rail<RAILWAY_CONFIG_DATA->num_rails);
  //Store all the voters in a linked list. To do, make this nicer.
  railway_voter_t voter = (railway_voter_t)malloc(sizeof(railway_voter_s));
  CORE_VERIFY_PTR(voter);
  voter->voltage_corner = RAILWAY_NO_REQUEST;
  voter->active_floor = RAILWAY_NO_REQUEST;
  voter->suppressible = suppressible;
  voter->id = id;
  voter->rail = rail;
#if 0
  voter->sw_enable = true;
#endif
  voter->voter_link = railway.rail_state[rail].voter_list_head;   //Will set the first voter's link to NULL, after that it just pushes out the list.
  railway.rail_state[rail].voter_list_head = voter;
  return voter;
}

#if 0
/*===========================================================================
FUNCTION: railway_sw_enable_vote

DESCRIPTION:

RETURN VALUE:
===========================================================================*/
void railway_sw_enable_vote(railway_voter_t voter, bool sw_enable)
{
  CORE_VERIFY(voter);
  voter->sw_enable = sw_enable;
}
#endif

/*===========================================================================
FUNCTION: railway_corner_vote

DESCRIPTION:

RETURN VALUE:
===========================================================================*/
void railway_corner_vote(railway_voter_t voter, railway_corner corner)
{
  CORE_VERIFY(voter);
  CORE_VERIFY(corner<RAILWAY_CORNERS_COUNT);
  voter->voltage_corner = corner;
}

/*===========================================================================
FUNCTION: railway_level_vote

DESCRIPTION: Vote for Volateg level

RETURN VALUE:
===========================================================================*/
void railway_level_vote(railway_voter_t voter, rail_voltage_level vol_level)
{
    CORE_VERIFY(voter);
    CORE_VERIFY(vol_level <RAIL_VOLTAGE_LEVEL_MAX);
    voter->voltage_corner = railway_level_to_corner(vol_level);
}

/*===========================================================================
FUNCTION: railway_active_floor_vote

DESCRIPTION:

RETURN VALUE:
===========================================================================*/
void railway_active_floor_vote(railway_voter_t voter, railway_corner corner)
{
    CORE_VERIFY(voter);
    CORE_VERIFY(corner<RAILWAY_CORNERS_COUNT);
    voter->active_floor = corner;
}

/*===========================================================================
FUNCTION: railway_active_floor_voltage_level_vote

DESCRIPTION: Vote for Volateg level

RETURN VALUE:
===========================================================================*/
void railway_active_floor_voltage_level_vote(railway_voter_t voter, rail_voltage_level vol_level)
{
    CORE_VERIFY(voter);
    CORE_VERIFY(vol_level <RAIL_VOLTAGE_LEVEL_MAX);
    voter->active_floor = railway_level_to_corner(vol_level);
}

/*===========================================================================
FUNCTION: railway_aggregated_voltage_target_uv

DESCRIPTION:

RETURN VALUE:
===========================================================================*/
railway_corner railway_aggregated_voltage_target(int rail, bool for_sleep)
{
  //Rail ID goes from 0 to (num_rails-1)
  CORE_VERIFY(rail<RAILWAY_CONFIG_DATA->num_rails);

  railway_corner target_setting = RAILWAY_NO_REQUEST;
    
  railway_voter_t voter = railway.rail_state[rail].voter_list_head;
#if 0
  bool sw_enable = false;
#endif

  //First, find highest corner vote.
  while (voter)
  {
    if(!(for_sleep && voter->suppressible)) //Ignore suppressible votes if we're asking for sleep.
    {
      if(voter->voltage_corner > target_setting)
      {
        target_setting = voter->voltage_corner;
      }

#if 0
      if(voter->voltage_corner!=RAILWAY_NO_REQUEST)
      {
        sw_enable = sw_enable || voter->sw_enable;
      }
#endif
    }
    if(!for_sleep)  //Factor in active floor requests.
    {
      if(voter->active_floor > target_setting)
      {
        target_setting = voter->active_floor;
      }
    }
    voter = (railway_voter_t)voter->voter_link;
  }

  return target_setting;
}

void railway_set_retention_voltage(int rail, uint32 microvolts)
{
    CORE_VERIFY(rail<RAILWAY_CONFIG_DATA->num_rails);

    railway.rail_state[rail].retention_voltage_uv = microvolts;
}

uint32 railway_get_corner_voltage(int rail, railway_corner corner)
{
    uint32 uv = 0;

    CORE_VERIFY(rail<RAILWAY_CONFIG_DATA->num_rails);
    CORE_VERIFY(corner<RAILWAY_CORNERS_COUNT);

    if (corner == RAILWAY_RETENTION)
    {
        uv = railway.rail_state[rail].retention_voltage_uv;
    }
    else if (corner > RAILWAY_RETENTION)
    {
        uv = cpr_railway_get_voltage(rail, corner);
    }

    return uv;
}

railway_corners_t* railway_get_supported_corners(int rail)
{
    uint32 corner_count = 0;

    supported_corners.corners[0] = RAILWAY_NO_REQUEST;
    supported_corners.corners[1] = RAILWAY_RETENTION;

    cpr_railway_get_supported_corners(rail, &(supported_corners.corners[2]), &corner_count);

    supported_corners.corners_count = corner_count + 2;

    return &supported_corners;
}

bool railway_voter_preventing_vdd_min(int id)
{
    //RailID 1 is Cx. Should probably add a #define.
    railway_voter_t voter = railway.rail_state[1].voter_list_head;
    while (voter)
    {
        if(voter->id==id)
        {
            if((!voter->suppressible) &&
                (voter->voltage_corner>RAILWAY_RETENTION))
                return true;
            else
                return false;
        }
        voter = voter->voter_link;
    }
    return false;
}

extern bool railway_transition_in_progress;

/*===========================================================================
FUNCTION: railway_get_current_settings

DESCRIPTION:

RETURN VALUE:
===========================================================================*/
void railway_get_current_settings(int rail, railway_settings* settings)
{
  CORE_VERIFY(rail < RAILWAY_CONFIG_DATA->num_rails);
  CORE_VERIFY_PTR(settings);
  CORE_VERIFY(!railway_transition_in_progress);
  
  memscpy(settings, sizeof(railway_settings), &railway.rail_state[rail].current_active, sizeof(railway_settings));
}

/*===========================================================================
FUNCTION: rail_id

DESCRIPTION:

RETURN VALUE:
===========================================================================*/
int rail_id(const char* rail)
{
  const railway_rail_config_t *rail_data = NULL;
    
  for(int i = 0; i < RAILWAY_CONFIG_DATA->num_rails; ++i)
  {
    rail_data = &RAILWAY_CONFIG_DATA->rails[i];
    if(!strcmp(rail, rail_data->vreg_name))
      return i;
  }
    
  return RAIL_NOT_SUPPORTED_BY_RAILWAY;
}
