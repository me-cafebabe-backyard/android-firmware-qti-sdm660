#ifndef __PM_DROOP_DETECT_H__
#define __PM_DROOP_DETECT_H__

/*! \file pm_droop_detect.h
 *  \n
 *  \brief This file contains PMIC RPM droop detection related restricted APIs.
 *  
 *  \n &copy; Copyright 2016 QUALCOMM Technologies Incorporated, All Rights Reserved
 */

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

$Header: //components/rel/rpm.bf/1.8/core/pmic/pm/inc/pm_droop_detect.h#1 $ 

when       who     what, where, why
--------   ---     ----------------------------------------------------------
02/04/16   kt      Created.
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "com_dtypes.h"
#include "pm_err_flags.h"

/*===========================================================================

                     API DECLARATION 

===========================================================================*/
/**
 * @brief This function is used to indicate to RPM if a droop 
 *        has occured which in turn triggers RPM to call the
 *        pm_droop_detect_rpm_callback() function. The flag is
 *        cleared in the callback function and the flow repeats
 *        on the next droop.
 * @param None
 * 
 * @return TRUE if droop occured after the last time callback 
 *         was called else FALSE.
 */
boolean pm_is_droop_detected (void);

/**
 * @brief This function is used as a call back from RPM when RPM
 *        is indicated that a droop was detected. This function
 *        clears the interrupt latched status and collects the
 *        drooping rail status and could abort based on a flag
 *        set or not
 * @param None
 * 
 * @return err_flag pm_err_flag_type.
 */
pm_err_flag_type pm_droop_detect_rpm_callback (void);

#endif //__PM_DROOP_DETECT_H__
