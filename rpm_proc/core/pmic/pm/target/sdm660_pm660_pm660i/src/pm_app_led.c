/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

             P M   RPM  LED 

GENERAL DESCRIPTION
  This file contains PMIC configuration functions on RPM for NPA Device layer
  to toggle the LED functions.
  
EXTERNALIZED FUNCTIONS
  None.

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None.

Copyright (c) 2014           by Qualcomm Technologies, Inc.  All Rights Reserved.
*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ----------------------------------------------------------
03/11/13   aks     Created.
===========================================================================*/
/*===========================================================================

                     INCLUDE FILES FOR MODULE

===========================================================================*/
#include "pm_app_led.h"
#include "pm_rgb_regs.h"
#include "pm_lpg_chan_regs.h"
#include "pm_pmio_spmi_lite.h"
#include "pm_base_addr_regs.h"

/*===========================================================================

                FUNCTION DEFINITIONS

===========================================================================*/
static pm_err_flag_type pm_rpm_program_lpg(uint8 channel_num , pm_led_dim_level dim_level);

pm_err_flag_type pm_rpm_enable_led_with_dim_ctrl(pm_led_rgb led_rgb, boolean enable, pm_led_volt_source led_volt_src, pm_led_dim_level dim_level)

{
  
  if(led_volt_src > PM_LED_SRC__INTERNAL)
  {
    return PM_ERR_FLAG__PAR1_OUT_OF_RANGE;
  }
  if(enable == TRUE)
  {
    /********************************* Select the LED source ******************************/
    //- 00 = ground (no power)
    //- 01 = VPH_PWR / Boost BYP
    //- 10 : Reserved
    //- 11 : min(VCHG, 5V), internally clamped by charger module

    //Boost and VPH are mapped to the same bit on PMI8994
    if (led_volt_src == PM_LED_SRC__BOOST) 
    {
      led_volt_src = PM_LED_SRC__VPH_PWR;
    }
    /* Set the new data in LED_SRC_SEL bit 1:0 */ 
    if ( PMIO_OUTFX(NULL, 3, PM_LED_RGB_BASE_ADDR, TRI_LED_LED_SRC_SEL , LED_SRC_SEL, (uint8)led_volt_src) != PM_ERR_FLAG__SUCCESS )
    { 
      return PM_ERR_FLAG__SPMI_OPT_ERR ; 
    }

    switch(led_rgb)
    {
      case PM_LED_RED:
      {
        /* Set the new data in RED_EN bit 7 */
        if ( PMIO_OUTFX(NULL, 3, PM_LED_RGB_BASE_ADDR, TRI_LED_EN_CTL, RED_EN, 1)  == PM_ERR_FLAG__SUCCESS )
        { 
		    return pm_rpm_program_lpg(PM_LED_RED_LED_CHANNEL_NUM ,dim_level);
        }
		else
		{           
		  return PM_ERR_FLAG__SPMI_OPT_ERR ; 
        }
      }
      case PM_LED_GREEN:
      {  
        /* Set the new data in GREEN_EN bit 6 */
        if ( PMIO_OUTFX(NULL, 3, PM_LED_RGB_BASE_ADDR, TRI_LED_EN_CTL, GREEN_EN, 1)	== PM_ERR_FLAG__SUCCESS )
        { 
		  return  pm_rpm_program_lpg(PM_LED_GREEN_LED_CHANNEL_NUM ,dim_level);
        }  
		else
		{ 					
          return PM_ERR_FLAG__SPMI_OPT_ERR ; 
        }
      }
      case PM_LED_BLUE:
      {  
        /* Set the new data in BLUE_EN bit 5 */
		if ( PMIO_OUTFX(NULL, 3, PM_LED_RGB_BASE_ADDR, TRI_LED_EN_CTL, BLUE_EN, 1) == PM_ERR_FLAG__SUCCESS )
        { 
          return  pm_rpm_program_lpg(PM_LED_BLUE_LED_CHANNEL_NUM ,dim_level);
        }	
        else
        {					
          return PM_ERR_FLAG__SPMI_OPT_ERR ; 
        }
      }
      default:
        return PM_ERR_FLAG__SPMI_OPT_ERR;
    }//switch 
  }//if
  else
  {
    switch( led_rgb )
    {
      case PM_LED_RED: //Disable RED LED
      {
        /* Set the new data in RED_EN bit 7 */
        if ( PMIO_OUTFX(NULL, 3, PM_LED_RGB_BASE_ADDR, TRI_LED_EN_CTL, RED_EN, 0) != PM_ERR_FLAG__SUCCESS )
        { 
          return PM_ERR_FLAG__SPMI_OPT_ERR ; 
        }
      }
      break;
      case PM_LED_GREEN: //Disable GREEN LED
      {
        /* Set the new data in GREEN_EN bit 6 */
        if ( PMIO_OUTFX(NULL, 3, PM_LED_RGB_BASE_ADDR, TRI_LED_EN_CTL, GREEN_EN, 0) != PM_ERR_FLAG__SUCCESS )
        { 
          return PM_ERR_FLAG__SPMI_OPT_ERR ; 
        }
      }
      break;
      case PM_LED_BLUE: //Disable BLUE LED
      {
        /* Set the new data in BLUE_EN bit 5 */
        if ( PMIO_OUTFX(NULL, 3, PM_LED_RGB_BASE_ADDR, TRI_LED_EN_CTL, BLUE_EN, 0) != PM_ERR_FLAG__SUCCESS )
        { 
          return PM_ERR_FLAG__SPMI_OPT_ERR ; 
        }
      }
      break;
      default:
        return PM_ERR_FLAG__SPMI_OPT_ERR;
    }//switch
  }//else enable false

  return PM_ERR_FLAG__SUCCESS;
}

/* **************************************************************************
 @ brief : set the brightness level for the selected led 
 @input param : channel_num : channel num of the register 
 @input param : dim_level : Brightness level desired

 return value : PM_ERR_FLAG__SPMI_OPT_ERR or PM_ERR_FLAG__SUCCESS
********************************************************************************/
static pm_err_flag_type pm_rpm_program_lpg(uint8 channel_num , pm_led_dim_level dim_level)
{
  /* substract 1 from the channel num since our first lpg slice register starts at 0xB100
	and the math is base_addr + 0x100 * channel_num  where address is the address of the first
	lpg slice register , LUT lpg is at 0xB000   */
  uint16 base_addr = PM_LED_LPG_SLICE_REG_BASE_ADDR + 
	                     ( PM_LED_LPG_FIRST_CHANNEL_OFFSET * (channel_num - 1 ) );
  uint8 val = 0;
  //Don't care about the read failures for now
  //No pattern is being set here
  if ( PMIO_OUTX( NULL, 3, base_addr, LPG_CHAN_LPG_PATTERN_CONFIG,0) != PM_ERR_FLAG__SUCCESS ) 
  { 
    return PM_ERR_FLAG__SPMI_OPT_ERR ; 
  }

  //7 bit mode, 19.2 MHz clock
  PMIO_INX( NULL, 3, base_addr, LPG_CHAN_LPG_PWM_SIZE_CLK,&val);
  val &= ~PMIO_FMSK(LPG_CHAN_LPG_PWM_SIZE_CLK, PWM_FREQ_CLK_SELECT);
  val |= PMIO_FVAL(LPG_CHAN_LPG_PWM_SIZE_CLK, PWM_FREQ_CLK_SELECT, 0x3);
  val &= ~PMIO_FMSK(LPG_CHAN_LPG_PWM_SIZE_CLK, PWM_SIZE);
  val |= PMIO_FVAL(LPG_CHAN_LPG_PWM_SIZE_CLK, PWM_SIZE, 0x1);
  if ( PMIO_OUTX( NULL, 3, base_addr, LPG_CHAN_LPG_PWM_SIZE_CLK,val) != PM_ERR_FLAG__SUCCESS  ) 
  { 
    return PM_ERR_FLAG__SPMI_OPT_ERR ; 
  }

  //Pre divide = 1, Exponent = 1 , This gives a 18.75 KHz PWM frequency
  PMIO_INX( NULL, 3, base_addr, LPG_CHAN_LPG_PWM_FREQ_PREDIV_CLK,&val);
  val &= ~PMIO_FMSK(LPG_CHAN_LPG_PWM_FREQ_PREDIV_CLK, PWM_FREQ_PRE_DIVIDE);
  val |= PMIO_FVAL(LPG_CHAN_LPG_PWM_FREQ_PREDIV_CLK, PWM_FREQ_PRE_DIVIDE, 0x0);
  val &= ~PMIO_FMSK(LPG_CHAN_LPG_PWM_FREQ_PREDIV_CLK, PWM_FREQ_EXPONENT);
  val |= PMIO_FVAL(LPG_CHAN_LPG_PWM_FREQ_PREDIV_CLK, PWM_FREQ_EXPONENT, 0x1);
  if ( PMIO_OUTX( NULL, 3, base_addr, LPG_CHAN_LPG_PWM_FREQ_PREDIV_CLK,val) != PM_ERR_FLAG__SUCCESS  )
  { 
    return PM_ERR_FLAG__SPMI_OPT_ERR ; 
  }

  if ( PMIO_OUTX( NULL, 3, base_addr, LPG_CHAN_LPG_PWM_TYPE_CONFIG,0) != PM_ERR_FLAG__SUCCESS  ) 
  { 
    return PM_ERR_FLAG__SPMI_OPT_ERR ; 
  }

  //Read the dim level register value 
  PMIO_INX( NULL, 3, base_addr, LPG_CHAN_PWM_VALUE_LSB, &val);
  val &= ~PMIO_FMSK(LPG_CHAN_PWM_VALUE_LSB, PWM_VALUE_LSB);
  //Configure DIM level
  switch ( dim_level )
  {
    case PM_LED_DIM_LEVEL_LOW: 
	  val |= PMIO_FVAL(LPG_CHAN_PWM_VALUE_LSB, PWM_VALUE_LSB, 0x2A);
	  break;
    case PM_LED_DIM_LEVEL_MID: 
	  val |= PMIO_FVAL(LPG_CHAN_PWM_VALUE_LSB, PWM_VALUE_LSB, 0x54);
    case PM_LED_DIM_LEVEL_HIGH:
	  //fixed 4mA
	  val |= PMIO_FVAL(LPG_CHAN_PWM_VALUE_LSB, PWM_VALUE_LSB, 0x80);
      break;
    default :
      return PM_ERR_FLAG__SPMI_OPT_ERR ;
  }//switch 
  //Set the dim level value 
  if ( PMIO_OUTX( NULL, 3, base_addr, LPG_CHAN_PWM_VALUE_LSB,val) != PM_ERR_FLAG__SUCCESS  )
  { 
    return PM_ERR_FLAG__SPMI_OPT_ERR ; 
  }

  //Dim Level MSB value is not used 
  if ( PMIO_OUTX( NULL, 3, base_addr, LPG_CHAN_PWM_VALUE_MSB,1) != PM_ERR_FLAG__SUCCESS  ) 
  { 
    return PM_ERR_FLAG__SPMI_OPT_ERR ; 
  }

  //Enable the PWM channel control
  PMIO_INX( NULL, 3, base_addr, LPG_CHAN_ENABLE_CONTROL, &val);
  
  val |= PMIO_FVAL(LPG_CHAN_ENABLE_CONTROL, EN_SLICE, 0x1);
  val |= PMIO_FVAL(LPG_CHAN_ENABLE_CONTROL, EN_RAMP_GEN, 0x01);
  val |= PMIO_FVAL(LPG_CHAN_ENABLE_CONTROL, EN_PWM_OUTPUT, 0x1);
  val |= PMIO_FVAL(LPG_CHAN_ENABLE_CONTROL, PWM_SRC_SELECT, 0x1);
  if ( PMIO_OUTX( NULL, 3, base_addr, LPG_CHAN_ENABLE_CONTROL,val) != PM_ERR_FLAG__SUCCESS  ) 
  { 
    return PM_ERR_FLAG__SPMI_OPT_ERR ; 
  }
  
  //SYNC
  if ( PMIO_OUTX( NULL, 3, base_addr, LPG_CHAN_PWM_SYNC,1) != PM_ERR_FLAG__SUCCESS  ) 
  { 
    return PM_ERR_FLAG__SPMI_OPT_ERR ; 
  }

  return PM_ERR_FLAG__SUCCESS;
}

