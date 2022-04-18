#ifndef __PM_APP_RGB_H__
#define __PM_APP_RGB_H__

/*! \file
*
*  \brief  pm_app_rgb.h
*  \details Implementation file for rgb led app interface implementation.
*
*  &copy; Copyright 2017 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/*===========================================================================

                        EDIT HISTORY

This document is created by a code generator, therefore this section will
not contain comments describing changes made to the module.


when        who    what, where, why
--------    ---    ----------------------------------------------------------
02/14/17    mr     Initial Revision
===========================================================================*/

/*===========================================================================

                        INCLUDE FILES

===========================================================================*/
#include "com_dtypes.h"


/*===========================================================================

                        TYPEDEF AND MACRO DEFINITIONS

===========================================================================*/

typedef struct
{
    uint8 led_r_lpg_chan;
    uint8 led_g_lpg_chan;
    uint8 led_b_lpg_chan;
} pm_rgb_lpg_chan_map_type;


#endif    /* __PM_APP_RGB_H__ */