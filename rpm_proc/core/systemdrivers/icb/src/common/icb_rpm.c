/**

@file   icb_rpm.c

@brief  Initialization and common code between icb rpm modules.
*/
/*
===========================================================================

                             Edit History

$Header: //components/rel/rpm.bf/1.8/core/systemdrivers/icb/src/common/icb_rpm.c#1 $

when         who     what, where, why
----------   ---     ------------------------------------------------------
2015/06/08   sds     Add SCHEME_1 support.
2014/08/04   sds     Add DSAT per perf level danger modulation.
2014/06/20   sds     Extend request types to add latency request in addition to BW.
2014/05/20   sds     Change the hardware base address to a uint8_t*.
2014/03/24   sds     Properly initialize save/restore HALs, if present.
2014/03/04   sds     Removed clock enable/disable for save and restore.
                     Clock team will ensure required clocks are managed properly
                     prior to save and restore function calls.
2013/02/22   sds     Add save/restore functionality
2011/11/08   sds     Created 

===========================================================================
                Copyright (c) 2011-2016 Qualcomm Technologies, Inc.
                       All Rights Reserved.
                       QUALCOMM Proprietary
===========================================================================
*/

/* -----------------------------------------------------------------------
** Includes
** ----------------------------------------------------------------------- */
#include "DALSys.h"
#include "CoreVerify.h"
#include "icb_rpmi.h"
#include "swevent.h"
#include "Clock.h"
#include "npa_resource.h"

/* -----------------------------------------------------------------------
** Types
** ----------------------------------------------------------------------- */

/* -----------------------------------------------------------------------
** Definitions
** ----------------------------------------------------------------------- */
#define CLK_DIV_KHZ(bps, width, ports) CEILING_DIV((bps), ((ports)!=0?(ports):1)*(width)*1000)
#define CLK_DIV_RAW(bps, width, ports) CEILING_DIV((bps), ((ports)!=0?(ports):1)*(width))

/* -----------------------------------------------------------------------
** Data
** ----------------------------------------------------------------------- */
static icb_system_info_type *sys_info = NULL;

/* -----------------------------------------------------------------------
** Functions - Clock management
** ----------------------------------------------------------------------- */
void icb_clock_init( icb_clock_type *clock )
{
  CORE_VERIFY_PTR( clock->handle = 
    npa_create_sync_client(clock->name, "ICB Driver", NPA_CLIENT_REQUIRED) );
}

void icb_clock_request( icb_clock_handle_type const *handle, uint32_t request )
{
  CORE_VERIFY_PTR( handle );
  const icb_clock_type *clock = handle->clock;
  CORE_VERIFY( handle->idx < clock->num_clients );

  /* Record updated request for this client. */
  clock->client_reqs[handle->idx] = request;

  /* Update our request to clock regime, if necessary. */
  uint32_t max = clock->client_reqs[0];
  for( uint32_t i = 1; i < clock->num_clients; i++ )
  {
    max = MAX( max, clock->client_reqs[i] );
  }
  npa_issue_required_request( clock->handle, max );
}

uint32_t icb_calc_clock_request
(
  uint64_t                request,
  const icb_bus_def_type *pBus,
  uint32_t                width,
  uint32_t                num_agg_ports )
{
  uint64_t scaled_request;
  uint32_t scalar = pBus->uP0;
  
  /* Adjust the request to reflect our aggregation scheme. */
  switch(pBus->aggType)
  {
    case ICB_AGG_SCHEME_1:
    {
      /* Search the table for the first level that matches.
       * If we don't find a match, we'll use the last entry. */
      uint32_t i;
      uint64_t req_mbps = CEILING_DIV(request, 1000000);
      for( i = 0; i < (pBus->uP0 - 1); i++ )
      {
        if( req_mbps <= pBus->levels[i].uBW )
        {
          break;
        }
      }
      scalar = pBus->levels[i].uP0;

      /* Intentional fall through. */
    }
    case ICB_AGG_SCHEME_0:
      scaled_request = CEILING_DIV(request * scalar, 100);
      break;
    case ICB_AGG_SCHEME_LEGACY:
    default:
      scaled_request = request;
      break;
  }

  /* Calculate the clock frequency required for this master */
  uint32_t clk_req;
  if( 0 != (ICB_WIDTH_TYPE_RAW & width) )
  {
    uint32_t raw_width = width & ~ICB_WIDTH_TYPE_MASK;
    clk_req = CLK_DIV_RAW( scaled_request,
                           raw_width,
                           num_agg_ports );
  }
  else
  {
    clk_req = CLK_DIV_KHZ( scaled_request,
                           width,
                           num_agg_ports );
  }

  return clk_req;
}

/* -----------------------------------------------------------------------
** Functions
** ----------------------------------------------------------------------- */
/**
@copydoc icb_get_target_resources()
*/
icb_system_info_type *icb_get_target_resources( void )
{
  static DALSYS_PROPERTY_HANDLE_DECLARE(hProp);

  /* Only get info once. */
  if( !sys_info )
  {
    DALSYSPropertyVar prop;

    /* Get our handle and sys_info property. */
    if( DAL_SUCCESS == 
        DALSYS_GetDALPropertyHandleStr( "/dev/icb/rpm", hProp ) &&
        DAL_SUCCESS ==
        DALSYS_GetPropertyValue( hProp, "system", 0, &prop) ) 
    {
      sys_info = (icb_system_info_type *)prop.Val.pStruct;
    }
  }

  return sys_info;
}

__attribute__((section("icb_cram_reclaim_pool")))
void icb_init_cb
(
  void         *context,
  unsigned int  event_type, 
  void         *data,       
  unsigned int  data_size
)
{
  /* Unused parameters. */
  (void)context;
  (void)event_type;
  (void)data; 
  (void)data_size;

  /* NPA resources available, initialize clocks. */
  for( uint32_t i = 0; i < sys_info->num_npa_deps; i++ )
  {
    icb_clock_init( sys_info->clocks[i] );
  }

  /* Clock resources for save/restore. */
  for( uint32_t i = 0; i < sys_info->num_ret_clks; i++ )
  {
    CORE_DAL_VERIFY( Clock_GetClockId( sys_info->ret_clks[i],
                                       &sys_info->ret_clk_ids[i] ) );
  }

  /* Initialize modules. */
  icb_masters_init();
  icb_slaves_init();
  icb_spdm_req_init();
  icb_master_latency_init();
  icb_dsat_init();

  SWEVENT(BUS_EVENT_INIT_DONE);
}

/**
@copydoc icb_init()
*/
__attribute__((section("icb_cram_reclaim_pool")))
void icb_init( void )
{
  /* Get a pointer to the system resources. */
  CORE_VERIFY_PTR( sys_info = icb_get_target_resources() );

  /* Initialize HALs. */
  for( uint32_t i = 0; i < sys_info->num_bus_defs; i++ )
  {
    switch( sys_info->bus_defs[i]->busType )
    {
      case ICB_BUS_BIMC:
      {
        HAL_bimc_InfoType *info = (HAL_bimc_InfoType *)sys_info->bus_defs[i]->pInfo;
        info->pBaseAddr = sys_info->bus_defs[i]->pBaseAddr;
        HAL_bimc_Init( info );
        break;
      }
      case ICB_BUS_NOC:
      {
        HAL_noc_InfoType *info = (HAL_noc_InfoType *)sys_info->bus_defs[i]->pInfo;
        info->pBaseAddr = sys_info->bus_defs[i]->pBaseAddr;
        HAL_noc_Init( info );
        break;
      }
      case ICB_BUS_VIRT:
        /* nothing to do for virtual bus. */
        break;
      default:
        /* Problem with the data file. */
        CORE_VERIFY( 0 );
        break;
    }
  }

  for( uint32_t i = 0; i < sys_info->num_ret_defs; i++ )
  {
    switch( sys_info->ret_defs[i]->busType )
    {
      case ICB_BUS_BIMC:
      {
        HAL_bimc_InfoType *info = (HAL_bimc_InfoType *)sys_info->ret_defs[i]->pInfo;
        info->pBaseAddr = sys_info->ret_defs[i]->pBaseAddr;
        HAL_bimc_Init( info );
        break;
      }
      case ICB_BUS_NOC:
      {
        HAL_noc_InfoType *info = (HAL_noc_InfoType *)sys_info->ret_defs[i]->pInfo;
        info->pBaseAddr = sys_info->ret_defs[i]->pBaseAddr;
        HAL_noc_Init( info );
        break;
      }
      case ICB_BUS_VIRT:
        /* nothing to do for virtual bus. */
        break;
      default:
        /* Problem with the data file. */
        CORE_VERIFY( 0 );
        break;
    }
  }

  /* Wait for the clock resources to be available. */
  npa_resources_available_cb( 
    sys_info->num_npa_deps, sys_info->npa_deps, icb_init_cb, NULL );
}

/**
@copydoc icb_hw_save()
*/
void icb_hw_save( void )
{
  /* Only do this if we have a valid sys_info pointer. */
  if( sys_info )
  {
    /* As per clock team, ALL required clocks will be on.
     * This function is in the power collapse/restore path, so it was desired
     * to optimize this for speed as much as possible. */
    for( uint32_t i = 0; i < sys_info->num_ret_defs; i++ )
    {
      switch( sys_info->ret_defs[i]->busType )
      {
        case ICB_BUS_BIMC:
        {
          HAL_bimc_InfoType *info = (HAL_bimc_InfoType *)sys_info->ret_defs[i]->pInfo;
          HAL_bimc_Save( info );
          break;
        }
        case ICB_BUS_NOC:
        {
          HAL_noc_InfoType *info = (HAL_noc_InfoType *)sys_info->ret_defs[i]->pInfo;
          HAL_noc_Save( info );
          break;
        }
        case ICB_BUS_VIRT:
          /* nothing to do for virtual bus. */
          break;
        default:
          /* Problem with the data file. */
          CORE_VERIFY( 0 );
          break;
      }
    }
    /* Clock disable handled externally by clock team. */
  }
}

/**
@copydoc icb_hw_restore()
*/
void icb_hw_restore( void )
{
  /* Only do this if we have a valid sys_info pointer. */
  if( sys_info )
  {
    /* As per clock team, ALL required clocks will be on.
     * This function is in the power collapse/restore path, so it was desired
     * to optimize this for speed as much as possible. */
    for( uint32_t i = 0; i < sys_info->num_ret_defs; i++ )
    {
      switch( sys_info->ret_defs[i]->busType )
      {
        case ICB_BUS_BIMC:
        {
          HAL_bimc_InfoType *info = (HAL_bimc_InfoType *)sys_info->ret_defs[i]->pInfo;
          HAL_bimc_Restore( info );
          break;
        }
        case ICB_BUS_NOC:
        {
          HAL_noc_InfoType *info = (HAL_noc_InfoType *)sys_info->ret_defs[i]->pInfo;
          HAL_noc_Restore( info );
          break;
        }
        case ICB_BUS_VIRT:
          /* nothing to do for virtual bus. */
          break;
        default:
          /* Problem with the data file. */
          CORE_VERIFY( 0 );
          break;
      }
    }
    /* Clock disable handled externally by clock team. */
  }
}
