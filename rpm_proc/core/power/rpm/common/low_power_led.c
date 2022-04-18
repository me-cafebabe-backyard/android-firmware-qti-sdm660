/*
===========================================================================

FILE:         low_power_led.c

DESCRIPTION:
  Control the LED upon a master's request.

===========================================================================

                             Edit History

$Header: //components/rel/rpm.bf/1.8/core/power/rpm/common/low_power_led.c#1 $
$Date: 2016/11/03 $

when       who     what, where, why
--------   ---     --------------------------------------------------------
2013-03-05 rc      Draft 1

===========================================================================
             Copyright (c) 2013 Qualcomm Technologies, Inc.
                    All Rights Reserved.
              QUALCOMM Proprietary and Confidential
===========================================================================
*/



#include "low_power_led.h"
#include "comdef.h"
#include "rpmserver.h"
#include "rpm_config.h"
#include "pm_app_led.h"
#include "pm_err_flags.h"
#include "railway.h"
#include <string.h>

static uint8 low_power_led_color_map[LOW_POWER_LED_POSSIBLE_STATES] = { 0 }; // array of colors corresponding to master states
static uint32 low_power_led_enabled = 0; // funtionality on or off?
static uint32 low_power_led_current_state = 0; // bitmask indicating awake/sleep state of masters

void rpm_low_power_led_pmic_wrapper(pm_led_rgb led_rgb, boolean enable)
{
#ifdef PM_RPM_LOW_POWER_LED
    if( PM_ERR_FLAG__SUCCESS != pm_rpm_enable_led_with_dim_ctrl(
                                  led_rgb,                 // Input color
                                  enable,                  // Enable/Disable 
                                  PM_LED_SRC__VPH_PWR,     // From battery
                                  PM_LED_DIM_LEVEL_HIGH ) ) // dim level low is "bright for the eyes"
    {
      abort();
    }
#endif // #ifdef PM_RPM_LOW_POWER_LED
}

void rpm_low_power_led_update_colors()
{
  // Call PMIC LED API to toggle all requested LED colors
  uint8 selected_colors = low_power_led_color_map[low_power_led_current_state];
  for( int i = 0; i < 3; i++ ) //3 LED colors
    rpm_low_power_led_pmic_wrapper((pm_led_rgb)i, ((selected_colors >> i) & 0x1));
}

uint32 rpm_low_power_led_enabled()
{
  return low_power_led_enabled;
}

void rpm_low_power_led_toggle_led()
{
  if( !rpm_low_power_led_enabled() )
    return;

  // Check status of masters ignoring TZ
  uint32 master_states = 0;
  uint32 rpm_num_ees = rpm_get_num_ees();
  for( int i = 0; i < rpm_num_ees && i < 4; i++)
  {
    switch(rpm->ees[i].subsystem_status)
    {
      case SPM_AWAKE:
      case SPM_GOING_TO_SLEEP:
        //if spm state is awake, then subsystem is on and LED should be on
        master_states |= (1 << i);
        break;
      case SPM_SLEEPING:
      case SPM_WAKING_UP:
        //if spm state is sleeping but master has vote preventing vdd_min, then subsystem is on and LED should be on
        if( railway_voter_preventing_vdd_min(i) )
        {
          master_states |= (1 << i);
        }
        break;
    }
  }
  if( master_states >= LOW_POWER_LED_POSSIBLE_STATES )
    abort();

  // Check if new LED color is the same as old LED color
  if( low_power_led_current_state == master_states )
    return; // No LED change necessary
  low_power_led_current_state = master_states;

  rpm_low_power_led_update_colors();
}

void rpm_low_power_led_xlate(rpm_translation_info *info)
{
    unsigned               type, length;
    const char             *value_ptr;
    low_power_led_inrep *req = info->dest_buffer;

    // Read until we run out of KVPs
    while( !kvp_eof(info->new_kvps) )
    {
        if(!kvp_get( info->new_kvps, &type, &length, &value_ptr ))
        {
            abort();
        }

        if( length == 0 )
        {
          switch(type)
          {
              case LOW_POWER_LED_REQ_ENAB:
                  req->enabled = 0;
                  break;
              case LOW_POWER_LED_REQ_COLOR_MAP:
                  memset(req->color_map, 0, LOW_POWER_LED_POSSIBLE_STATES * sizeof(uint8)); 
                  break;
              default:
                  break;
          }
        }
        else
        {
          switch(type)
          {
              case LOW_POWER_LED_REQ_ENAB:
                  if (sizeof(uint32) != length)
                    abort();
                  req->enabled = *(uint32 *)value_ptr;
                  break;
              case LOW_POWER_LED_REQ_COLOR_MAP:
                  if ( (LOW_POWER_LED_POSSIBLE_STATES * sizeof(uint8)) != length)
                    abort();
                  memcpy( req->color_map, (uint8 *)value_ptr, (LOW_POWER_LED_POSSIBLE_STATES * sizeof(uint8) ) );
                  break;
              default:
                  break;
          }
        }
    }
}

static void rpm_low_power_led_apply(rpm_application_info *info)
{
    //for now, assume only one master so no need to query
    low_power_led_inrep *new_req = (low_power_led_inrep *)info->new_state;
    low_power_led_enabled = new_req->enabled;
    memcpy((void*)low_power_led_color_map, new_req->color_map, (LOW_POWER_LED_POSSIBLE_STATES * sizeof(uint8)) );

    rpm_low_power_led_toggle_led(); // init the colors
}

void low_power_led_init(void)
{
    rpm_register_resource(RPM_LOW_POWER_LED_REQ, 1, sizeof(low_power_led_inrep), rpm_low_power_led_xlate, rpm_low_power_led_apply, 0);

    // Disable all LED's until further notified
    rpm_low_power_led_toggle_led();
}


