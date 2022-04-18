/*
===========================================================================

FILE:         ddr_external_api.c

DESCRIPTION:  
  This is external APIs to support usage of SCALe sequences

  Copyright (c) 2014 QUALCOMM Technologies Incorporated.  All Rights Reserved.  
  QUALCOMM Proprietary and Confidential. 
===========================================================================
                                EDIT HISTORY

$Header: //components/rel/rpm.bf/1.8/core/boot/ddr/hw/sdm660/ddr_external_api.c#1 $
$DateTime: 2016/11/03 00:13:13 $
$Author: pwbldsvc $
================================================================================
when       who     what, where, why
--------   ---     -------------------------------------------------------------
04/05/14   sr      Initial version.
================================================================================
*/

/*==============================================================================
                                  INCLUDES
==============================================================================*/
#include "ddr_common.h"
#include "seq_hwio.h"
#include "mpm.h"
#include "Clock.h"
#include "busywait.h"

/*==============================================================================
                                  MACROS
==============================================================================*/

/*==============================================================================
                                  DATA
==============================================================================*/


/*==============================================================================
                                  ASSEMBLY
==============================================================================*/


/*==============================================================================
                                  FUNCTIONS
==============================================================================*/

/* ============================================================================
**  Function : ddr_external_set_clk_speed
** ============================================================================
*/
/*!
*   @brief
*   This function is called by external library to set the clock speed
*   
*   @details
*   This api will set the clock speed accordingly as specified in the parameter to this function
*   
*   @param 
*   @param clk_in_khz       -  [IN] clock speed in khz 
*   
*   @par Dependencies
*   
*   @par Side Effects
*   None
*   
*   @retval  boolean
*   
*   @sa None
*/

boolean ddr_external_set_clk_speed(uint32 clk_in_khz)
{
   //Clock_SetDirectBusSpeed(CLOCK_RESOURCE_BIMC, clk_in_khz);
   return TRUE;
}


/* ============================================================================
**  Function : ddr_mpm_config_ebi1_freeze_io
** ============================================================================
*/
/*!
*   @brief
*   This function is called by external library while entering/exiting Power Collapse
*   
*   @details
*   This api will be called by SNS library to enable/disable IO clamps during PC
*   
*   @param 
*   @param flag         -  [IN] boolean flag to enable/disable IO clamps
*   
*   @par Dependencies
*   
*   @par Side Effects
*   None
*   
*   @retval  None
*   
*   @sa None
*/

void ddr_mpm_config_ebi1_freeze_io( boolean flag ) 
{ 
  mpm_config_ebi1_freeze_io(flag);
}

void ddr_external_page_to_storage( void * buffer, uint32 size )
{
}

boolean ddr_external_set_ddrss_cfg_clk(boolean on_off)
{
  static ClockIdType dimClk = 0;
  DALResult   eRes;
	
  if (dimClk == 0)
  {
  	eRes = Clock_GetClockId( "gcc_ddr_dim_cfg_clk", &dimClk);
  	assert( eRes == DAL_SUCCESS);
  }

  if(on_off)
     Clock_EnableClock(dimClk);
  else
     Clock_DisableClock(dimClk);
  return TRUE;
}

void seq_wait(uint32 time_value, SEQ_TimeUnit time_unit)
  {

    if(time_unit == SEC)
    {
       busywait(time_value * 1000 * 1000);
    }
    else if(time_unit == MS)
    {
       busywait(time_value * 1000);
    }
    else if(time_unit == US)
    {
       busywait(time_value);
    }
    else
    {
       /* time_unit == NS */
       busywait(time_value / 1000);
    }

}

