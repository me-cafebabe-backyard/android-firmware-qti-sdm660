/*===========================================================================
  railway_adapter.c

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
#include <stdlib.h>

#include "rpmserver.h"
#include "../common/vect.h"

#include "railway.h"

#include "railway_internal.h"
#include "railway_adapter.h"
#include "railway_config.h"
#include "CoreVerify.h"
#include "pmapp_npa.h"

//---------------------------------------------------------------------------
// Constant / Define Declarations
//--------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Type Declarations
//---------------------------------------------------------------------------
typedef enum
{
    RAILWAY_VOTE_MODE_NONE    = 0,
    RAILWAY_VOTE_MODE_CORNER  = 1,
    RAILWAY_VOTE_MODE_LEVEL   = 2,

    RAILWAY_VOTE_MODE_COUNT
} railway_vote_mode;

typedef struct
{
#if 0 //sw_enable is not used
  uint32            sw_enable;
#endif
  railway_corner    corner;
  railway_corner    active_floor;
} railway_voter_irep;

typedef struct
{
  int rail_num;
  vect_t  *voter_handles;
} cb_data_t;


//---------------------------------------------------------------------------
// Global Constant Definitions
//---------------------------------------------------------------------------
bool ghost_vote;

//---------------------------------------------------------------------------
// Local Object Definitions
//---------------------------------------------------------------------------

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
  FUNCTION: set_ghost_vote

  DESCRIPTION:

  RETURN VALUE:
  ===========================================================================*/
void set_ghost_vote(bool do_ghost_vote)
{
  ghost_vote=do_ghost_vote;
}

//This translation is required because masters vote for levels 0-6, but we support more levels internally in the RPM.
//Masters don't vote for level RAILWAY_SVS_HIGH, RAILWAY_TURBO_HIGH, or RAILWAY_SUPER_TURBO_NO_CPR
const static railway_corner railway_master_corner_remap[] =
{
  RAILWAY_NO_REQUEST,
  RAILWAY_RETENTION,
  RAILWAY_SVS_LOW,
  RAILWAY_SVS,
  RAILWAY_NOMINAL,
  RAILWAY_TURBO,
  RAILWAY_SUPER_TURBO,
};

#define RAILWAY_CORNER_REMAP_TABLE_SIZE (sizeof(railway_master_corner_remap)/sizeof(railway_corner))

/*===========================================================================
  FUNCTION: railway_translate_master_corner

  DESCRIPTION:

  RETURN VALUE:
  ===========================================================================*/
railway_corner railway_translate_master_corner(uint32 master_corner)
{
    CORE_VERIFY(master_corner < RAILWAY_CORNER_REMAP_TABLE_SIZE);
    CORE_VERIFY((railway_corner)master_corner < RAILWAY_SUPER_TURBO_NO_CPR);

    return railway_master_corner_remap[master_corner];
}

/*===========================================================================
  FUNCTION: railway_xlate

  DESCRIPTION:

  RETURN VALUE:
  ===========================================================================*/
void railway_xlate(rpm_translation_info *info)
{
  uint32              type, length;
  uint32             *value;
  railway_voter_irep *req = info->dest_buffer;
  railway_vote_mode vote_mode = RAILWAY_VOTE_MODE_NONE;

  /* Read until we run out of KVPs. */
  while( !kvp_eof(info->new_kvps) )
  {
    kvp_get( info->new_kvps, &type, &length, (const char **)&value);

    if(length==0)
    {   /* Implies we need to invalidate any previous request the client 
           might have on this kvp type. */
      switch(type)
      {
#if 0
        case PM_NPA_KEY_SOFTWARE_ENABLE:
          req->sw_enable = 0;
          break;
#endif
        case PM_NPA_KEY_CORNER_LEVEL_KEY:
        case RAILWAY_KEY_INTERNAL_CORNER_LEVEL:
          // don't allow corner and level voting at the same time
          CORE_VERIFY(vote_mode != RAILWAY_VOTE_MODE_LEVEL);
          vote_mode   = RAILWAY_VOTE_MODE_CORNER;
          req->corner = RAILWAY_NO_REQUEST;
          break;
        case RAILWAY_KEY_ACTIVE_FLOOR:
          // don't allow corner and level voting at the same time
          CORE_VERIFY(vote_mode != RAILWAY_VOTE_MODE_LEVEL);
          vote_mode         = RAILWAY_VOTE_MODE_CORNER;
          req->active_floor = RAILWAY_NO_REQUEST;
          break;
        case RAILWAY_KEY_VOLTAGE_LEVEL:
          // don't allow corner and level voting at the same time
          CORE_VERIFY(vote_mode != RAILWAY_VOTE_MODE_CORNER);
          vote_mode   = RAILWAY_VOTE_MODE_LEVEL;
          req->corner = RAILWAY_NO_REQUEST;
          break;
        case RAILWAY_KEY_ACTIVE_FLOOR_LEVEL:
          // don't allow corner and level voting at the same time
          CORE_VERIFY(vote_mode != RAILWAY_VOTE_MODE_CORNER);
          vote_mode         = RAILWAY_VOTE_MODE_LEVEL;
          req->active_floor = RAILWAY_NO_REQUEST;
          break;
        default:
          break;
      }
    }
    else
    {
      switch(type)
      {
#if 0
        case PM_NPA_KEY_SOFTWARE_ENABLE:
          CORE_VERIFY(sizeof(npa_resource_state) == length);
          req->sw_enable = *value;
          break;
#endif
        case PM_NPA_KEY_CORNER_LEVEL_KEY:
          CORE_VERIFY(sizeof(npa_resource_state) == length);
          // don't allow corner and level voting at the same time
          CORE_VERIFY(vote_mode != RAILWAY_VOTE_MODE_LEVEL);
          vote_mode   = RAILWAY_VOTE_MODE_CORNER;
          req->corner = railway_translate_master_corner((railway_corner)*value);
          break;
        //We don't support explicit voltage votes on Railway-managed rails.
        //Only acceptable value to vote for is 0 which we can safely ignore.
        case PM_NPA_KEY_MICRO_VOLT: 
          CORE_VERIFY(sizeof(npa_resource_state) == length);
          CORE_VERIFY(*value==0);
          break;
        case RAILWAY_KEY_ACTIVE_FLOOR:
          CORE_VERIFY(sizeof(npa_resource_state) == length);
          // don't allow corner and level voting at the same time
          CORE_VERIFY(vote_mode != RAILWAY_VOTE_MODE_LEVEL);
          vote_mode         = RAILWAY_VOTE_MODE_CORNER;
          req->active_floor = railway_translate_master_corner(*value);
          break;
        case RAILWAY_KEY_INTERNAL_CORNER_LEVEL:
          CORE_VERIFY(sizeof(npa_resource_state) == length);
          // don't allow corner and level voting at the same time
          CORE_VERIFY(vote_mode != RAILWAY_VOTE_MODE_LEVEL);
          vote_mode   = RAILWAY_VOTE_MODE_CORNER;
          req->corner = (railway_corner)*value;
          break;
        case RAILWAY_KEY_ACTIVE_FLOOR_LEVEL:
          CORE_VERIFY(sizeof(npa_resource_state) == length);
          // don't allow corner and level voting at the same time
          CORE_VERIFY(vote_mode != RAILWAY_VOTE_MODE_CORNER);
          vote_mode         = RAILWAY_VOTE_MODE_LEVEL;
          req->active_floor = railway_level_to_corner((rail_voltage_level)*value);
          break;
        case RAILWAY_KEY_VOLTAGE_LEVEL:
          CORE_VERIFY(sizeof(npa_resource_state) == length);
          // don't allow corner and level voting at the same time
          CORE_VERIFY(vote_mode != RAILWAY_VOTE_MODE_CORNER);
          vote_mode   = RAILWAY_VOTE_MODE_LEVEL;
          req->corner = railway_level_to_corner((rail_voltage_level)*value);
          break;
        default:
          break;
      }
    }
  }
}

/*===========================================================================
  FUNCTION: railway_apply

  DESCRIPTION:

  RETURN VALUE:
  ===========================================================================*/
void railway_apply(rpm_application_info *info)
{
  cb_data_t   *rail_info = (cb_data_t *)info->cb_data;
  railway_voter_irep* new_irep;
  railway_voter_irep  invalidated_irep;

  //info->new_state can be NULL in the case that a request has been invalidated.
  //In that case, use a zeroed-out irep.
  if(info->new_state)
  {
    new_irep = (railway_voter_irep*)info->new_state;
  }
  else
  {
    memset(&invalidated_irep, 0, sizeof(railway_voter_irep));
    new_irep = &invalidated_irep;
  }

  uint32 voter = info->client;
  int rail_id    = rail_info->rail_num;
  CORE_VERIFY(rail_id!=-1);

  // Ensure we have enough room to store a voter handle for this voter.
  if(voter >= vect_size(rail_info->voter_handles))
    vect_resize(rail_info->voter_handles, voter+1);

  // Ensure we have an internal voter handle.
  railway_voter_t h = (railway_voter_t)vect_at(rail_info->voter_handles, voter);
  if(!h)
  {
    bool is_external = info->client < rpm_get_num_ees();
    h = railway_create_voter(rail_id, is_external ? false : true, voter);
    vect_set(rail_info->voter_handles, voter, h);
  }

  railway_corner_vote(h, new_irep->corner);
#if 0
  railway_sw_enable_vote(h, new_irep->sw_enable);
#endif
  railway_active_floor_vote(h, new_irep->active_floor);

  if(!ghost_vote)
  {
    railway_transition_rail(rail_id);
  }
}

/*===========================================================================
  FUNCTION: railway_adapter_init

  DESCRIPTION:

  RETURN VALUE:
  ===========================================================================*/
__attribute__((section("railway_dram_reclaim_pool")))
void railway_adapter_init(void)
{
    for(int i = 0; i < RAILWAY_CONFIG_DATA->num_rails; i++)
    {
        const railway_rail_config_t *rail = &RAILWAY_CONFIG_DATA->rails[i];

        cb_data_t *cb_data = malloc(sizeof(cb_data_t));
        CORE_VERIFY_PTR(cb_data);
        cb_data->rail_num = i;
        cb_data->voter_handles = vect_create();
        CORE_VERIFY(cb_data->voter_handles);

        /*
         * Master doesn't vote for EBI rail, and there is no resouce type defined for EBI rail
         */
        if(rail->resource_type)
        {
            rpm_register_resource(rail->resource_type, 1, sizeof(railway_voter_irep),
                                  railway_xlate, railway_apply, cb_data);
        }
    }
}
