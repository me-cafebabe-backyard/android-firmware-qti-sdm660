/*
===========================================================================

FILE:         ddr_sns_drivers.c

DESCRIPTION:  
  This is the ddr drivers implementation for Qualcomm memory controller.

Copyright 2014 by Qualcomm Technologies, Inc.  All Rights Reserved.
===========================================================================

                             Edit History


when       who     what, where, why
--------   ---     --------------------------------------------------------
07/18/14   tw      added support for passing highest bank bit information to ram
                   partition table
05/28/14   tw      Renamed lp4_share_data to ddrsns_share_data for code clarity
03/12/14   sr      Initial version

===========================================================================
*/


/*==============================================================================
                                  INCLUDES
==============================================================================*/
#include "ddr_common.h"
#include "ddr_drivers.h"
#include "ddr_internal.h"
#include "ddr_sync.h"
#include "ddr_params.h"
#include "HAL_SNS_DDR.h"

/*==============================================================================
                                  DATA
==============================================================================*/
ddr_interface_state ddr_status;

/* internal variable to keep track of device specific bus width, 32bit vs 64 bit */
uint32 ddr_bus_width;

/*Indicates ddr initialization is done or not, FALSE by default*/
boolean ddr_init_done = FALSE;

/* Chip selects for selected ranks by ddr_enter/exit_self_refresh_all() */
static DDR_CHIPSELECT ddr_csel_ch0, ddr_csel_ch1;

ddr_info ddr_physical_size = {{0}};
ddr_size_info ddr_system_size = {0};

/*==============================================================================
                                  FUNCTIONS
==============================================================================*/
/* ============================================================================
**  Function : ddr_init
** ============================================================================
*/
/*!
*   @brief
*   Initialize ddr HAL with the correct ddr parameters
*   This must be done before calling any of the drivers functions
*   
*   @details
*   Initialize ddr HAL with the correct ddr parameters
*   This must be done before calling any of the drivers functions
*      
*   @par Dependencies
*   None
*   
*   @par Side Effects
*   None
*   
*   @retval  None
*   
*   @sa None
*/

void ddr_init(void)
{
  struct detected_ddr_device_params *ddr_detected_param_interface_0, *ddr_detected_param_interface_1;

  /* Initialize the ddr driver Mutex */
  DDR_SYNC_INIT();

  /* Get DDR parameters */
  ddr_detected_param_interface_0 = (ddr_get_detected_params(DDR_CH0));
  ddr_detected_param_interface_1 = (ddr_get_detected_params(DDR_CH1));

  /* First initialize all the ddr devices to be unavailable */
  ddr_status.sdram0_cs0 = DDR_UNAVAILABLE;
  ddr_status.sdram0_cs1 = DDR_UNAVAILABLE;
  ddr_status.sdram1_cs0 = DDR_UNAVAILABLE;
  ddr_status.sdram1_cs1 = DDR_UNAVAILABLE;

  /* based on ddr parameter selected, set the ddr status for active ddr */
  if(ddr_detected_param_interface_0->num_rows_cs0 != 0)
  {
    ddr_status.sdram0_cs0 = DDR_ACTIVE;
  }
  if(ddr_detected_param_interface_0->num_rows_cs1 != 0)
  {
    ddr_status.sdram0_cs1 = DDR_ACTIVE;
  }
  if(ddr_detected_param_interface_1->num_rows_cs0 != 0)
  {
    ddr_status.sdram1_cs0 = DDR_ACTIVE;
  }
  if(ddr_detected_param_interface_1->num_rows_cs1 != 0)
  {
    ddr_status.sdram1_cs1 = DDR_ACTIVE;
  }

  /* initialize target specific functions */
  ddr_target_init();

} /* ddr_init */

/* ============================================================================
**  Function : ddr_initialize_device
** ============================================================================
*/
/*!
*   @brief
*   This function will setup the ddr parameter in HAl and initialize the ddr
*   
*   @details
*   This function will first pass the currently used ddr device parameter
*   to the HAL. Then it will initialize the ddr as per specified speed
*   
*   @param clkspeed   -  [IN] clk speed to initialize for
*   
*   @par Dependencies
*   None
*   
*   @par Side Effects
*   None
*   
*   @retval  None
*   
*   @sa None
*/

void ddr_initialize_device(uint32 clk_speed)
{
  struct detected_ddr_device_params *ddr_detected_param_interface_0, *ddr_detected_param_interface_1;


  if(!ddr_init_done)
  {    
    /* Pass the ddr parameters to HAL */
    ddr_init();

    /* Update the ddr clock speed variable to the initialization clock */
    ddr_status.clk_speed = clk_speed;
	
    ddrsns_share_data->ecdt_input = (uint32) ddr_get_extended_cdt_params();
    
    if((ddr_status.sdram0_cs0 != DDR_UNAVAILABLE) && 
       (ddr_status.sdram1_cs0 != DDR_UNAVAILABLE))
    {
      if((ddr_status.sdram0_cs1 != DDR_UNAVAILABLE) &&
      (ddr_status.sdram1_cs1 != DDR_UNAVAILABLE))
      {
        HAL_DDR_Init(ddrsns_share_data, DDR_CH_BOTH, DDR_CS_BOTH, clk_speed);
      }
      else
      {
        HAL_DDR_Init(ddrsns_share_data, DDR_CH_BOTH, DDR_CS0, clk_speed);
      }
    }
    else if((ddr_status.sdram0_cs0 != DDR_UNAVAILABLE)||
            (ddr_status.sdram1_cs0 != DDR_UNAVAILABLE))
    {
      if((ddr_status.sdram0_cs1 != DDR_UNAVAILABLE) ||
      (ddr_status.sdram1_cs1 != DDR_UNAVAILABLE))
      {
        if(ddr_status.sdram0_cs1 != DDR_UNAVAILABLE)
        {
          HAL_DDR_Init(ddrsns_share_data, DDR_CH0, DDR_CS_BOTH, clk_speed);
        }
        else if(ddr_status.sdram0_cs0 != DDR_UNAVAILABLE)
        {
          HAL_DDR_Init(ddrsns_share_data, DDR_CH0, DDR_CS0, clk_speed);
        } 
      }
	  else if(ddr_status.sdram0_cs0 != DDR_UNAVAILABLE)
      {
          HAL_DDR_Init(ddrsns_share_data, DDR_CH0, DDR_CS0, clk_speed);
      } 
    }  


    /* Get DDR device parameters after detection during initialization */
    ddr_detected_param_interface_0 = (ddr_get_detected_params(DDR_CH0));;
    ddr_detected_param_interface_1 = (ddr_get_detected_params(DDR_CH1));;

    /* Update DDR status */
    ddr_status.sdram0_cs0 = (ddr_detected_param_interface_0->num_rows_cs0 != 0) ?
                            DDR_ACTIVE : DDR_UNAVAILABLE;
    ddr_status.sdram0_cs1 = (ddr_detected_param_interface_0->num_rows_cs1 != 0) ?
                            DDR_ACTIVE : DDR_UNAVAILABLE;
    ddr_status.sdram1_cs0 = (ddr_detected_param_interface_1->num_rows_cs0 != 0) ?
                            DDR_ACTIVE : DDR_UNAVAILABLE;
    ddr_status.sdram1_cs1 = (ddr_detected_param_interface_1->num_rows_cs1 != 0) ?
                            DDR_ACTIVE : DDR_UNAVAILABLE;
    
    ddr_update_info();
    ddr_update_size();

    ddr_init_done = TRUE;
  }
  /* Else, already initialized ddr, do nothing */
} /* ddr_initialize_device */

/* =============================================================================
**  Function : ddr_enter_self_refresh_all
** =============================================================================
*/
/**
*   @brief
*   Put DDR into self refresh mode for all active ranks.
*
*   @param[in]  clk_speed  Current clock speed (in KHz)
*
*   @retval  None
*
*   @dependencies
*   None
*
*   @sideeffects
*   None
*
*   @sa
*   None
*/
void ddr_enter_self_refresh_all(uint32 clk_speed)
{
  DDR_SYNC_LOCK();

  /* Set chip select and update DDR status */
  ddr_csel_ch0 = DDR_CS_NONE;
  if (ddr_status.sdram0_cs0 == DDR_ACTIVE)
  {
    ddr_status.sdram0_cs0 = DDR_SELF_REFRESH;
    ddr_csel_ch0 |= DDR_CS0;
  }
  if (ddr_status.sdram0_cs1 == DDR_ACTIVE)
  {
    ddr_status.sdram0_cs1 = DDR_SELF_REFRESH;
    ddr_csel_ch0 |= DDR_CS1;
  }
  /* Enter self refresh for selected ranks */
  if (ddr_csel_ch0 != DDR_CS_NONE)
  {
    HAL_DDR_Enter_Self_Refresh(ddrsns_share_data,DDR_CH0, ddr_csel_ch0);
  }

  /* Set chip select and update DDR status */
  ddr_csel_ch1 = DDR_CS_NONE;
  if (ddr_status.sdram1_cs0 == DDR_ACTIVE)
  {
    ddr_status.sdram1_cs0 = DDR_SELF_REFRESH;
    ddr_csel_ch1 |= DDR_CS0;
  }
  if (ddr_status.sdram1_cs1 == DDR_ACTIVE)
  {
    ddr_status.sdram1_cs1 = DDR_SELF_REFRESH;
    ddr_csel_ch1 |= DDR_CS1;
  }
  /* Enter self refresh for selected ranks */
  if (ddr_csel_ch1 != DDR_CS_NONE)
  {
    HAL_DDR_Enter_Self_Refresh(ddrsns_share_data,DDR_CH1, ddr_csel_ch1);
  }

  DDR_SYNC_UNLOCK();

} /* ddr_enter_self_refresh_all */

/* =============================================================================
**  Function : ddr_exit_self_refresh_all
** =============================================================================
*/
/**
*   @brief
*   Take DDR out of self refresh mode for ranks that are active before
*   ddr_enter_self_refresh_all() is called.
*
*   @param[in]  clk_speed  Current clock speed (in KHz)
*
*   @retval  None
*
*   @dependencies
*   None
*
*   @sideeffects
*   None
*
*   @sa
*   None
*/
void ddr_exit_self_refresh_all(uint32 clk_speed)
{
  DDR_SYNC_LOCK();

  /* Update DDR status */
  if (ddr_csel_ch0 & DDR_CS0)
  {
    ddr_status.sdram0_cs0 = DDR_ACTIVE;
  }
  if (ddr_csel_ch0 & DDR_CS1)
  {
    ddr_status.sdram0_cs1 = DDR_ACTIVE;
  }
  /* Exit self refresh for selected ranks */
  if (ddr_csel_ch0 != DDR_CS_NONE)
  {
    HAL_DDR_Exit_Self_Refresh(ddrsns_share_data,DDR_CH0, ddr_csel_ch0);
  }

  /* Update DDR status */
  if (ddr_csel_ch1 & DDR_CS0)
  {
    ddr_status.sdram1_cs0 = DDR_ACTIVE;
  }
  if (ddr_csel_ch1 & DDR_CS1)
  {
    ddr_status.sdram1_cs1 = DDR_ACTIVE;
  }
  /* Exit self refresh for selected ranks */
  if (ddr_csel_ch1 != DDR_CS_NONE)
  {
    HAL_DDR_Exit_Self_Refresh(ddrsns_share_data,DDR_CH1, ddr_csel_ch1);
  }

  DDR_SYNC_UNLOCK();

} /* ddr_exit_self_refresh_all */

/* ============================================================================
**  Function : ddr_enter_self_refresh
** ============================================================================
*/
/*!
*   @brief
*   This function will put the a particular ddr into self refresh mode, provided that it is currently active.
*   
*   @details
*   This function will first check to see if the ddr specified by the caller is available and active, then put it into self
*   refresh mode. If it is not active or not available, simply do nothing.
*   
*   @param interface_name   - [IN] The interface to put ddr into self refresh
*   @param chip_select      -     [IN] The chip select to put ddr into self refresh
*   @param clkspeed      -        [IN] The current clock speed

*
*   @par Dependencies
*   This code has to reside in IRAM
*   
*   @par Side Effects
*   None
*   
*   @retval  None
*   
*   @sa None
*/
void ddr_enter_self_refresh(SDRAM_INTERFACE interface_name, SDRAM_CHIPSELECT chip_select, uint32 clk_speed)
{
   ddrsns_enter_self_refresh((DDR_CHANNEL)interface_name,(DDR_CHIPSELECT)chip_select,clk_speed);
}

void ddrsns_enter_self_refresh(DDR_CHANNEL interface_name, DDR_CHIPSELECT chip_select, uint32 clk_speed)
{
  DDR_CHIPSELECT csel = DDR_CS_NONE;

  /*
    Issue a lock to prevent anyone else from updating ddr
    status while we are working here
  */
  DDR_SYNC_LOCK();

  /* Mark device as self refresh after entering self refresh */
  if (interface_name == DDR_CH0)
  {
    if ( (chip_select & DDR_CS0) && (ddr_status.sdram0_cs0 == DDR_ACTIVE) )
    {
      csel |= DDR_CS0;
      ddr_status.sdram0_cs0 = DDR_SELF_REFRESH;
    }
    if ( (chip_select & DDR_CS1) && (ddr_status.sdram0_cs1 == DDR_ACTIVE) )
    {
      csel |= DDR_CS1;
      ddr_status.sdram0_cs1 = DDR_SELF_REFRESH;
    }
  }
  else
  {
    if ( (chip_select & DDR_CS0) && (ddr_status.sdram1_cs0 == DDR_ACTIVE) )
    {
      csel |= DDR_CS0;
      ddr_status.sdram1_cs0 = DDR_SELF_REFRESH;
    }
    if ( (chip_select & DDR_CS1) && (ddr_status.sdram1_cs1 == DDR_ACTIVE) )
    {
      csel |= DDR_CS1;
      ddr_status.sdram1_cs1 = DDR_SELF_REFRESH;
    }
  }

  if (csel != DDR_CS_NONE)
  {
    HAL_DDR_Enter_Self_Refresh(ddrsns_share_data, interface_name, csel);
  }

  /* Unlock now that we are done */
  DDR_SYNC_UNLOCK();

} /* ddr_enter_self_refresh */

/* ============================================================================
**  Function : ddr_exit_self_refresh
** ============================================================================
*/
/*!
*   @brief
*   This function will put the particular ddr into active mode, provided that it is currently in self refresh.
*   
*   @details
*   This function will first check to see if the ddr specified by the caller is available and in self refresh, then put it into active
*   mode. If it is not in self refresh, simply do nothing.
*   
*   @param interface_name   -  [IN] The interface to put ddr into self refresh
*   @param chip_select      -  [IN] The chip select to put ddr into self refresh
*   @param clkspeed      -        [IN] The current clock speed
*
*   @par Dependencies
*   This code has to reside in IRAM
*   
*   @par Side Effects
*   None
*   
*   @retval  None
*   
*   @sa None
*/

void ddr_exit_self_refresh(SDRAM_INTERFACE interface_name, SDRAM_CHIPSELECT chip_select, uint32 clk_speed)
{
   ddrsns_exit_self_refresh((DDR_CHANNEL)interface_name,(DDR_CHIPSELECT)chip_select,clk_speed);
}

void ddrsns_exit_self_refresh(DDR_CHANNEL interface_name, DDR_CHIPSELECT chip_select, uint32 clk_speed)
{
  DDR_CHIPSELECT csel = DDR_CS_NONE;

  /*
    Issue a lock to prevent anyone else from updating ddr
    status while we are working here
  */
  DDR_SYNC_LOCK();

  /* Mark device as active after exiting from self refresh */
  if (interface_name == DDR_CH0)
  {
    if ( (chip_select & DDR_CS0) && (ddr_status.sdram0_cs0 == DDR_SELF_REFRESH) )
    {
      csel |= DDR_CS0;
      ddr_status.sdram0_cs0 = DDR_ACTIVE;
    }
    if ( (chip_select & DDR_CS1) && (ddr_status.sdram0_cs1 == DDR_SELF_REFRESH) )
    {
      csel |= DDR_CS1;
      ddr_status.sdram0_cs1 = DDR_ACTIVE;
    }
  }
  else
  {
    if ( (chip_select & DDR_CS0) && (ddr_status.sdram1_cs0 == DDR_SELF_REFRESH) )
    {
      csel |= DDR_CS0;
      ddr_status.sdram1_cs0 = DDR_ACTIVE;
    }
    if ( (chip_select & DDR_CS1) && (ddr_status.sdram1_cs1 == DDR_SELF_REFRESH) )
    {
      csel |= DDR_CS1;
      ddr_status.sdram1_cs1 = DDR_ACTIVE;
    }
  }

  if (csel != DDR_CS_NONE)
  {
    HAL_DDR_Exit_Self_Refresh(ddrsns_share_data,interface_name, csel);
  }

  /* Unlock now that we are done */
  DDR_SYNC_UNLOCK();
} /* ddr_exit_self_refresh */

/* ============================================================================
**  Function : ddr_enter_deep_power_down
** ============================================================================
*/
/*!
*   @brief
*   This function will put ddr into deep power down mode.
*   
*   @details
*   This function will put ddr into deep power down mode.
*   
*   @param interface_name   -  [IN] The interface to put ddr into DPD
*   @param chip_select      -  [IN] The chip select to put ddr into DPD
*   
*   @par Dependencies
*   None
*   
*   @par Side Effects
*   After a device has entered Deep Power Down, it will be unavailable for use.
*   When it is necessary to bring device out of DPD, a full HW initialization must be
*   executed.
*   
*   @retval  None
*   
*   @sa None
*/
void ddr_enter_deep_power_down(SDRAM_INTERFACE interface_name, SDRAM_CHIPSELECT chip_select)
{
   ddrsns_enter_deep_power_down((DDR_CHANNEL)interface_name, (DDR_CHIPSELECT)chip_select);
}

void ddrsns_enter_deep_power_down(DDR_CHANNEL interface_name, DDR_CHIPSELECT chip_select)
{
  DDR_CHIPSELECT csel = DDR_CS_NONE;

  /*
    Issue a lock to prevent anyone else from updating ddr
    status while we are working here
  */
  DDR_SYNC_LOCK();

  /* Mark device as DPD after entering from deep power down */
  if (interface_name == DDR_CH0)
  {
    if ( (chip_select & DDR_CS0) && (ddr_status.sdram0_cs0 == DDR_ACTIVE) )
    {
      csel |= DDR_CS0;
      ddr_status.sdram0_cs0 = DDR_DPD;
    }
    if ( (chip_select & DDR_CS1) && (ddr_status.sdram0_cs1 == DDR_ACTIVE) )
    {
      csel |= DDR_CS1;
      ddr_status.sdram0_cs1 = DDR_DPD;
    }
  }
  else
  {
    if ( (chip_select & DDR_CS0) && (ddr_status.sdram1_cs0 == DDR_ACTIVE) )
    {
      csel |= DDR_CS0;
      ddr_status.sdram1_cs0 = DDR_DPD;
    }
    if ( (chip_select & DDR_CS1) && (ddr_status.sdram1_cs1 == DDR_ACTIVE) )
    {
      csel |= DDR_CS1;
      ddr_status.sdram1_cs1 = DDR_DPD;
    }
  }

  if (csel != DDR_CS_NONE)
  {
    HAL_DDR_Enter_Deep_Power_Down(ddrsns_share_data,interface_name, csel);
  }

  /* Unlock now that we are done */
  DDR_SYNC_UNLOCK();

} /* ddr_enter_deep_power_down */

/* ============================================================================
**  Function : ddr_exit_deep_power_down
** ============================================================================
*/
/*!
*   @brief
*   This function will take the ddr out of deep power down mode.
*   
*   @details
*   This function will take the ddr out of deep power down mode.
*   
*   @param interface_name  -  [IN] The interface to take ddr out of DPD
*   @param chip_select         -  [IN] The chip select to take ddr out of DPD
*   @param clk_speed          -  [IN] The ddr speed to reinitialize for
*
*   @par Dependencies
*   ddr clock must be returned to an applicable initialization frequency
*   LPDDR1 - no restrictions
*   LPDDR2 - < 50Mhz
*   
*   @par Side Effects
*   None
*   
*   @retval  None
*   
*   @sa None
*/
void ddr_exit_deep_power_down(SDRAM_INTERFACE interface_name, SDRAM_CHIPSELECT chip_select, uint32 clk_speed)
{
   ddrsns_exit_deep_power_down((DDR_CHANNEL)interface_name,(DDR_CHIPSELECT)chip_select,clk_speed);
}

void ddrsns_exit_deep_power_down(DDR_CHANNEL interface_name, DDR_CHIPSELECT chip_select, uint32 clk_speed)
{
  DDR_CHIPSELECT csel = DDR_CS_NONE;

  /*
    Issue a lock to prevent anyone else from updating ddr
    status while we are working here
  */
  DDR_SYNC_LOCK();

  /* Mark device as active after exiting from deep power down */
  if (interface_name == DDR_CH0)
  {
    if ( (chip_select & DDR_CS0) && (ddr_status.sdram0_cs0 == DDR_DPD) )
    {
      csel |= DDR_CS0;
      ddr_status.sdram0_cs0 = DDR_ACTIVE;
    }
    if ( (chip_select & DDR_CS1) && (ddr_status.sdram0_cs1 == DDR_DPD) )
    {
      csel |= DDR_CS1;
      ddr_status.sdram0_cs1 = DDR_ACTIVE;
    }
  }
  else
  {
    if ( (chip_select & DDR_CS0) && (ddr_status.sdram1_cs0 == DDR_DPD) )
    {
      csel |= DDR_CS0;
      ddr_status.sdram1_cs0 = DDR_ACTIVE;
    }
    if ( (chip_select & DDR_CS1) && (ddr_status.sdram1_cs1 == DDR_DPD) )
    {
      csel |= DDR_CS1;
      ddr_status.sdram1_cs1 = DDR_ACTIVE;
    }
  }

  if (csel != DDR_CS_NONE)
  {
    HAL_DDR_Exit_Deep_Power_Down(ddrsns_share_data,interface_name, csel, clk_speed);
  }

  /* Unlock now that we are done */
  DDR_SYNC_UNLOCK();

} /* ddr_exit_deep_power_down */

/* ============================================================================
**  Function : ddr_get_status
** ============================================================================
*/
/*!
*   @brief
*   Returns the status of DDR.
*   
*   @details
*   Returns the ddr_status internal structure so that caller of this API can
*   see which devices are available and what state they are in.
*   
*  @param  None
*   
*   @par Dependencies
*   None
*   
*   @par Side Effects
*   None
*   
*   @retval returns the status of the devices on all available interface
*   and chip select
*   
*   @sa None
*/

ddr_interface_state ddr_get_status(void)
{
  return ddr_status;
} /* ddr_get_status */

/* ============================================================================
**  Function : ddr_update_info
** ============================================================================
*/
/*!
*   @brief
*   update the internal ddr info variable with the latest detected settings
*
*   @details
*   update the internal ddr info variable with the latest detected settings
*
*   @param  None.
*
*   @par Dependencies
*   None
*
*   @par Side Effects
*   None
*
*   @retval
*   None
*
*   @sa None
*/
#define QFPROM_RAW_CALIB_ROW5_MSB                     (0x780214)
#define MSM_VERSION_MASK 							  (3<<25)

void ddr_update_info(void)
{
  ddr_info ddr_physical_memory_size = {{0}};
  IOCTL_ARG data = {0};
  ddr_size_info *ddr_size = &(ddr_physical_memory_size.ddr_size);
#if 1 
  uint32 qfprom_row5;
  
  
   qfprom_row5 = ((*(volatile unsigned int *)QFPROM_RAW_CALIB_ROW5_MSB) & MSM_VERSION_MASK);
    if (qfprom_row5 != 0)
	{

  ddr_size->sdram0_cs0 =  ddrsns_share_data->ddr_size_info.ddr0_cs0_mb;
  ddr_size->sdram0_cs1 =  ddrsns_share_data->ddr_size_info.ddr0_cs1_mb;
	  ddr_size->sdram0_cs0_addr = ddrsns_share_data->ddr_size_info.ddr0_cs0_addr;
	  ddr_size->sdram0_cs1_addr = ddrsns_share_data->ddr_size_info.ddr0_cs1_addr;
	}
	else
	{
#endif
	  ddr_size->sdram0_cs0 =  0;
	  ddr_size->sdram0_cs1 =  0;
	  ddr_size->sdram0_cs0_addr = 0;
	  ddr_size->sdram0_cs1_addr = 0;
#if 1
	}
#endif
  
  ddr_size->sdram1_cs0 =  ddrsns_share_data->ddr_size_info.ddr1_cs0_mb;
  ddr_size->sdram1_cs1 =  ddrsns_share_data->ddr_size_info.ddr1_cs1_mb;
    
  ddr_size->sdram1_cs0_addr = ddrsns_share_data->ddr_size_info.ddr1_cs0_addr;
  ddr_size->sdram1_cs1_addr = ddrsns_share_data->ddr_size_info.ddr1_cs1_addr;

#if 0 // 64bit addressing in 8996 and above, below code is legacy 
  /* is it a 4GB device, if so restrict it to 3.9 GB , as the memory starting from 0xF8000000 to 100000000 is reserved*/
  if(ddr_size->sdram0_cs0 +
     ddr_size->sdram0_cs1 +
     ddr_size->sdram1_cs0 +
     ddr_size->sdram1_cs1 == 0x1000) {

	  /* Do we have only one rank or two ranks */
	  if((ddr_size->sdram0_cs1 != 0) && (ddr_size->sdram1_cs1 != 0)){
		  /* 2 ranks identified */
      	                ddr_size->sdram0_cs1 = 0x3C0;
      	                ddr_size->sdram1_cs1 = 0x3C0;

			/* store the info back in global DDR_STRUCT */
                        ddrsns_share_data->ddr_size_info.ddr0_cs1_mb = 0x3C0;
		        ddrsns_share_data->ddr_size_info.ddr1_cs1_mb = 0x3C0;	
	  }
	  else{
		  /* only 1 rank identified , lets split the 3.9 GB between the two channels and one rank  */
		      ddr_size->sdram0_cs0 = 0x780;
                      ddr_size->sdram1_cs0 = 0x780;

		        /* store the info back in global DDR_STRUCT */
                        ddrsns_share_data->ddr_size_info.ddr0_cs0_mb = 0x780;
                        ddrsns_share_data->ddr_size_info.ddr1_cs0_mb = 0x780;
	  }
  }
#endif
  /* Check to see if interleave is turned on */
  ddr_physical_memory_size.interleaved_memory = ddr_param_interleaved();

  /*
    Parse for ddr type from ddr parameters
    it is assumed that interface 0 and interface 1 has to have
    the same ddr type
  */
  ddr_physical_memory_size.ddr_type = (DDR_TYPE)(ddrsns_share_data->detected_ddr_device[0].device_type);

  /* update for highest banked bit */
  /* populate highest bank bit field */
  HAL_DDR_IOCTL(ddrsns_share_data, IOCTL_CMD_GET_HIGHEST_BANK_BIT, &data);
  ddr_size->highest_bank_bit = data.results;
    
  ddr_physical_size = ddr_physical_memory_size;
}/* ddr_update_info */

/* ============================================================================
**  Function : ddr_get_info
** ============================================================================
*/
/*!
*   @brief
*   Returns the physical configuration of ddr on target
*
*   @details
*   This function will return the physical configuration of the ddr on target
*
*   @param  None.
*
*   @par Dependencies
*   None
*
*   @par Side Effects
*   None
*
*   @retval ddr_size_infor contains the ddr size and base address
*
*   @sa None
*/

ddr_info ddr_get_info(void)
{
  struct detected_ddr_device_params *ddr_detected_param_interface_0 = (ddr_get_detected_params(DDR_CH0));
  /* to workaround drivers calling ddr_get_info prior to ddr init, always update
   * with correct ddr type from ddr params. 
   */
  ddr_physical_size.ddr_type = (DDR_TYPE)(ddr_detected_param_interface_0->device_type);     
  
  return ddr_physical_size;
}/* ddr_get_info */

/* ============================================================================
**  Function : ddr_update_size
** ============================================================================
*/
/*!
*   @brief
*   Returns the ddr size and base address
*   
*   @details
*
*   
*  @param  None
*   
*   @par Dependencies
*   None
*   
*   @par Side Effects
*   None
*   
*   @retval ddr_size_infor contains the ddr size and base address
*   
*   @sa None
*/

void ddr_update_size(void)
{
  ddr_info ddr_physical_info = ddr_get_info();

  /* Check to see if interleave is turned on for CS0 */
  if(ddr_physical_info.interleaved_memory & DDR_CS0)
  {
    /* Interleave mode is on for CS0 , double the size of CS0, and do not populate interface 1 */
    ddr_physical_info.ddr_size.sdram0_cs0 *= 2;
    ddr_physical_info.ddr_size.sdram1_cs0 = 0;
  }

  if(ddr_physical_info.interleaved_memory & DDR_CS1)
  {
    /* Interleave mode is on for CS1 , double the size of CS1, and do not populate interface 1 */
    ddr_physical_info.ddr_size.sdram0_cs1 *= 2;
    ddr_physical_info.ddr_size.sdram1_cs1 = 0;
  }
 
  ddr_system_size = ddr_physical_info.ddr_size;  
} /* ddr_update_size */

/* ============================================================================
**  Function : ddr_get_size
** ============================================================================
*/
/*!
*   @brief
*   Returns the ddr size and base address
*   
*   @details
*
*   
*  @param  None
*   
*   @par Dependencies
*   None
*   
*   @par Side Effects
*   None
*   
*   @retval ddr_size_infor contains the ddr size and base address
*   
*   @sa None
*/

ddr_size_info ddr_get_size(void)
{
  return ddr_system_size;
} /* ddr_get_size */

/* ============================================================================
**  Function : ddr_get_partition
** ============================================================================
*/
/*!
*   @brief
*   Returns the ddr partitions and base address
*   
*   @details
*	This API will return the number of partitions on each interface along with the 
*	base address
*   
*  @param  None
*   
*   @par Dependencies
*   None
*   
*   @par Side Effects
*   None
*   
*   @retval ddr_size_partition contains the ddr partitions and base address
*   
*   @sa None
*/

ddr_size_partition ddr_get_partition(void)
{
  ddr_size_partition ddr_partitions = {{0}};
  
  /* 
    because we only support segment masking due to bank interleaving,
    we always have 8 partitions per device
  */  
  if(ddr_system_size.sdram0_cs0)
  {
    ddr_partitions.sdram0_cs0.sdram_addr = ddr_system_size.sdram0_cs0_addr;
    ddr_partitions.sdram0_cs0.num_partitions = 8;
  }
  if(ddr_system_size.sdram0_cs1)
  {
    ddr_partitions.sdram0_cs1.sdram_addr = ddr_system_size.sdram0_cs1_addr;
    ddr_partitions.sdram0_cs1.num_partitions = 8;
  }
  if(ddr_system_size.sdram1_cs0)
  {
    ddr_partitions.sdram1_cs0.sdram_addr = ddr_system_size.sdram1_cs0_addr;
    ddr_partitions.sdram1_cs0.num_partitions = 8;
  }
  if(ddr_system_size.sdram1_cs1)
  {
    ddr_partitions.sdram1_cs1.sdram_addr = ddr_system_size.sdram1_cs1_addr;
    ddr_partitions.sdram1_cs1.num_partitions = 8;
  }
 
  return ddr_partitions;
}
