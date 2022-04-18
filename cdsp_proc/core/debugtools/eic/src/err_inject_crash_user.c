/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

                      ERR service crash simulator
                
GENERAL DESCRIPTION
  Command handler for injecting various types of crashes for testing

INITIALIZATION AND SEQUENCING REQUIREMENTS
  Diag must be initialized

Copyright (c) 2013 -2014 by QUALCOMM Technologies, Incorporated.  All Rights Reserved.
*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/


/*==========================================================================

                        EDIT HISTORY FOR MODULE
$Header: //components/rel/core.qdsp6/1.0.c2/debugtools/eic/src/err_inject_crash_user.c#1 $

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

void err_dog_force_bite(void)
{
    TMS_MSG_ERROR("Cannot force a wdog bite from USER PD");
}

typedef void (*err_dynamic_msg_cb)(char* const, const uint16, const uint32);
void err_Fatal_internal_dynamic_1 (const msg_const_type* const_blk, err_dynamic_msg_cb callback, const uint32 cb_param)
{
    TMS_MSG_ERROR("err_Fatal_internal_dynamic currently is not supported in USER PD");
}
