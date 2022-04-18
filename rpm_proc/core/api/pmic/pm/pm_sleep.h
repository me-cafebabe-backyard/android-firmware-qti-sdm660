#ifndef PM_SLEEP__H
#define PM_SLEEP__H

/*! \file pm_sleep.h
*  \n
*  \brief This header file contains functions and variable declarations
*         to support RPM sleep.
*  \n
*  \n &copy; Copyright 2014 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

$Header: //components/rel/rpm.bf/1.8/core/api/pmic/pm/pm_sleep.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
5/20/14   vtw      Created.
========================================================================== */
/*===========================================================================

                        HEADER FILES

===========================================================================*/
#include "com_dtypes.h"
#include "pm_err_flags.h"
#include "pm_resources_and_types.h"

/*===========================================================================

                        TYPE DEFINE AND ENUMS

===========================================================================*/

 /*! \enum pm_sleep_mode_type
 *  \brief Type definition for support sleep mode.
 */
typedef enum
{
  PM_SLEEP_MODE_XO_SHUTDOWN,
  PM_SLEEP_MODE_VDD_MIN,
  PM_SLEEP_MODE_INVALID
} pm_sleep_mode_type;

/*===========================================================================

                        API

===========================================================================*/

/**
 * @name pm_rpm_enter_sleep
 *
 * @brief This function calls the driver layer PMIC calls to set
 *        the Rails to the state prior to entering sleep.
 *
 * @param  sleep_mode: can be vdd_min/XO shutdown
 *
 * @return PMIC error code.
 *
 * @sideeffects Will over-write any client configuration
 *              requests. Any additions to the below function
 *              should be cautiously be added.
 *
 */
pm_err_flag_type
pm_rpm_enter_sleep (pm_sleep_mode_type sleep_mode);

/**
 * @name pm_rpm_exit_sleep
 *
 * @brief This function calls the driver layer PMIC calls to set
 *        the Rails back to the prior state of entering sleep.
 *
 * @param sleep_mode: can be vdd_min/XO shutdown
 *
 * @return PMIC error code.
 *
 * @sideeffects Will restore any client configuration requests.
 *              Any additions to the below function should be
 *              cautiously be added.
 *
 */
pm_err_flag_type
pm_rpm_exit_sleep (pm_sleep_mode_type sleep_mode);

#endif /* PM_SLEEP__H */
