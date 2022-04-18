/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

                      ERR service crash simulator
                
GENERAL DESCRIPTION
  Command handler for injecting various types of crashes for testing

INITIALIZATION AND SEQUENCING REQUIREMENTS
  Diag must be initialized

Copyright (c) 2016 by QUALCOMM Technologies, Incorporated.  All Rights Reserved.
*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/


/*==========================================================================

                        EDIT HISTORY FOR MODULE
$Header: //components/rel/core.qdsp6/1.0.c2/debugtools/eic/src/err_inject_crash_root.c#1 $

when       who     what, where, why
--------   ---     ------------------------------------------------------------

===========================================================================*/

#ifndef ERR_INJECT_CRASH
  #error Required definition is missing, check configuration
#endif //ERR_INJECT_CRASH

/*===========================================================================

                     INCLUDE FILES FOR MODULE

===========================================================================*/

#include "tms_utils_msg.h"
#include "dog_hal.h"
#include "qurt.h"

static volatile int always_true = 1;
static volatile int  always_false = 0;

void err_dog_force_bite(void)
{
    TMS_MSG_ERROR("Calling HAL_dogForceBite from CORE ROOT PD");

   /*Entering to STM after force Dog bite is triggered to force stop all activities, 
    its to simulate closer behavior as practical scenario of WDog Bite 
    and avoid issues while APSS tries to do SSR since the proc may have activities going which may 
    interfere with APSS while APSS trying to reset the proc.*/
    qurt_exception_raise_fatal();
    HAL_dogForceBite();

    while(always_true)
    {
        if(always_false)
            break;
	}
}
