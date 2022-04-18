/*! \file
*
*  \brief  pm_app_rgb_led.c
*  \details Implementation file for rgb led resourece type.
*
*  &copy; Copyright 2013-2017 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/*===========================================================================

EDIT HISTORY FOR MODULE

This document is created by a code generator, therefore this section will
not contain comments describing changes made to the module.


when       who     what, where, why
--------   ---     ----------------------------------------------------------
02/10/17   mr      Retrieve LPG Channel Num corresponding to RGB Segment
05/17/15   aab     Updated LPG Channel assignment to support 8998 target
03/31/15   aab     Added a call to select PWM source: pm_lpg_pwm_src_select()
06/24/14   aab     Cleaned up and added support for PMI8994
03/13/13   aab     Creation
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES

===========================================================================*/
#include "pm_err_flags.h"
#include "pm_target_information.h"
#include "pm_app_rgb.h"

#include "pm_rgb.h"
#include "pm_lpg.h"


/*===========================================================================

                     RGB APP API DEFINITIONS

===========================================================================*/
pm_err_flag_type pm_rgb_led_config
(
   unsigned                   device_index,
   pm_rgb_which_type          rgb_peripheral,
   uint32                     rgb_mask,
   pm_rgb_voltage_source_type source_type,
   uint32                     dim_level,
   boolean                    enable_rgb)
{
   pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;
   pm_lpg_chan_type lpg_channel = PM_LPG_CHAN_NONE;
   pm_rgb_lpg_chan_map_type *rgb_lpg_chan_map = NULL;

   if (rgb_peripheral >= PM_RGB_INVALID) {
      return PM_ERR_FLAG__PAR2_OUT_OF_RANGE;
   }

   if (!((rgb_mask & PM_RGB_SEGMENT_R) || (rgb_mask & PM_RGB_SEGMENT_G) || (rgb_mask & PM_RGB_SEGMENT_B))) {
      return PM_ERR_FLAG__PAR3_OUT_OF_RANGE;
   }

   if (source_type >= PM_RGB_VOLTAGE_SOURCE_INVALID) {
      return PM_ERR_FLAG__PAR4_OUT_OF_RANGE;
   }

   if (dim_level > PM_RGB_DIM_LEVEL_MAX) {
      return PM_ERR_FLAG__PAR5_OUT_OF_RANGE;
   }

   rgb_lpg_chan_map = (pm_rgb_lpg_chan_map_type *)pm_target_information_get_specific_info(PM_PROP_RGB_LPG_CHAN_MAP);
   if(NULL == rgb_lpg_chan_map)
   {
      return PM_ERR_FLAG__INVALID;
   }

   //RGB-LPG Channel Mapping
   switch(rgb_mask)
   {
      case PM_RGB_SEGMENT_R:  lpg_channel = rgb_lpg_chan_map->led_r_lpg_chan; break;
      case PM_RGB_SEGMENT_G:  lpg_channel = rgb_lpg_chan_map->led_g_lpg_chan; break;
      case PM_RGB_SEGMENT_B:  lpg_channel = rgb_lpg_chan_map->led_b_lpg_chan; break;
      default:                return PM_ERR_FLAG__INVALID;
   }

   err_flag = pm_rgb_set_voltage_source(device_index, rgb_peripheral, source_type); //Select RGB voltage source
   if (err_flag != PM_ERR_FLAG__SUCCESS) {
      return err_flag;
   }

   if (enable_rgb == TRUE)
   {
      err_flag = pm_lpg_pattern_config(device_index, lpg_channel, FALSE, FALSE, FALSE, FALSE, FALSE); //Configure for no pattern
      if (err_flag != PM_ERR_FLAG__SUCCESS) {return err_flag;}

      err_flag = pm_lpg_pwm_clock_sel(device_index, lpg_channel, PM_LPG_PWM_19_2_MHZ);  //Select 19.2 MHz clock
      if (err_flag != PM_ERR_FLAG__SUCCESS) {return err_flag;}

      err_flag = pm_lpg_pwm_set_pre_divide(device_index, lpg_channel, PM_LPG_PWM_PRE_DIV_5, PM_LPG_PWM_FREQ_EXPO_7); //Configure 390 Hz PWM frequency
      if (err_flag != PM_ERR_FLAG__SUCCESS) {return err_flag;}

      err_flag = pm_lpg_config_pwm_type(device_index, lpg_channel, FALSE);
      if (err_flag != PM_ERR_FLAG__SUCCESS) {return err_flag;}

      err_flag = pm_lpg_pwm_set_pwm_value(device_index, lpg_channel, dim_level);  //Configure DIM level
      if (err_flag != PM_ERR_FLAG__SUCCESS) {return err_flag;}

      err_flag = pm_lpg_set_pwm_bit_size(device_index, lpg_channel, PM_LPG_PWM_7BIT);    //Configure 7 bit mode
      if (err_flag != PM_ERR_FLAG__SUCCESS) {return err_flag;}

      err_flag = pm_lpg_pwm_src_select (device_index, lpg_channel,PM_LPG_PWM_SRC_PWM_REGISTER);
      if (err_flag != PM_ERR_FLAG__SUCCESS) {return err_flag;}

      err_flag = pm_lpg_pwm_enable(device_index, lpg_channel, TRUE); //enable LPG
      if (err_flag != PM_ERR_FLAG__SUCCESS) {return err_flag;}
   }
   else
   {
      err_flag = pm_lpg_pwm_enable(device_index, lpg_channel, FALSE); //Disable LPG
      if (err_flag != PM_ERR_FLAG__SUCCESS) {return err_flag;}
   }

   //Turn ON/OFF RGB LED
   err_flag = pm_rgb_enable(device_index, rgb_peripheral, rgb_mask, enable_rgb, FALSE);

   return err_flag;
}
