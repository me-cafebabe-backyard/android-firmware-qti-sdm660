#ifndef __PM_DEVICE_H__
#define __PM_DEVICE_H__

/*! \file pm_device.h
*  \n
*  \brief This header file contains enums and helper function declarations needed
*  \n during PMIC device initialization .
*  \n
*  \n &copy; Copyright 2016 QUALCOMM Technologies Incorporated, All Rights Reserved
*/
/* =======================================================================
Edit History
This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ----------------------------------------------------------
08/03/16   akm     Created
 
========================================================================== */
/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/

#include "pm_err_flags.h"
#include "pm_boot.h"
#include "pm_version.h"

/*===========================================================================

                        TYPE DEFINITIONS 

===========================================================================*/


/*===========================================================================

                        FUNCTION PROTOTYPES 

===========================================================================*/

/*! \brief This function executes the pmic device setup needed to communicate with PMICs
 *   \brief  It initilizes SPMI bus and detects PMIC on target
 *  \return Error flag.
 *
 */
pm_err_flag_type pm_device_setup(void);

#endif // __PM_DEVICE_H__
