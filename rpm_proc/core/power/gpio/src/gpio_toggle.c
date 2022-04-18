/*===========================================================================

  gpio_toggle.c - resource to allow masters to toggle GPIO pins

  Copyright (c) 2013 Qualcomm Technologies, Inc.  
  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ===========================================================================*/

#include "gpio_toggle.h"
#include "comdef.h"
#include <stdlib.h>
#include "time_service.h"
#include "rpmserver.h"
#include "CoreVerify.h"

#include "gpio.h"


void gpio_toggle_xlate(rpm_translation_info *info)
{
    unsigned               type, length, value;
    const char             *value_ptr;
    gpio_toggle_inrep *req = info->dest_buffer;

    // Read until we run out of KVPs
    while( !kvp_eof(info->new_kvps) )
    {
        if(!kvp_get( info->new_kvps, &type, &length, &value_ptr ))
        {
            abort();
        }

        CORE_VERIFY_PTR(value_ptr);
        value = *(unsigned*)value_ptr;

        switch(type)
        {
            case REQ_GPIO_NUM:
                if (sizeof(uint32) != length)
                  abort();
                req->pin = (uint8)value;
                break;
            case REQ_GPIO_STATE:
                if (sizeof(uint32) != length)
                  abort();
                req->state = (value?1:0);
/*            case REQ_GPIO_ENABLE:
                if (sizeof(uint32) != length)
                  abort();
                req->state = (value?1:0);
*/
            default:
            {
                //unknown key
            }
        }
    }
}

static void gpio_toggle_apply(rpm_application_info *info)
{
    uint32 gpio_num = 0;
    uint32 state = 0;

    //update state
    gpio_toggle_inrep *new_req = (gpio_toggle_inrep *)info->new_state;

    gpio_num = new_req->pin;
    state = new_req->state;

    //configure GPIO for output
    gpio_configure_gpio(gpio_num, 0x303);

    //set GPIO state on listed GPIO
    gpio_write_gpio_out(gpio_num, state);
}

void gpio_toggle_init()
{
    rpm_register_resource(RPM_GPIO_TOGGLE_REQ, 3, sizeof(gpio_toggle_inrep), gpio_toggle_xlate, gpio_toggle_apply, 0);
}

