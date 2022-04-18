#ifndef PM_BOOST_DRIVER__H
#define PM_BOOST_DRIVER__H

/*! \file pm_boost_driver.h
 *  \n
 *  \brief This file contains BOOST peripheral driver related function prototypes,
 *         enums and driver data structure type.   
 *  \n  
 *  \n &copy; Copyright 2013-2014 QUALCOMM Technologies Incorporated, All Rights Reserved
 */
/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

  $Header: //components/rel/rpm.bf/1.8/core/pmic/pm/drivers/boost/src/pm_boost_driver.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
04/25/13   aks      Code Refactoring: Removing PMIC_SubRsc from pwr algs
04/12/13   hs       Code refactoring.
1/29/13    aks      Adding support for 5v boost as a separate driver
========================================================================== */

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "pm_err_flags.h"
#include "pm_pwr_alg.h"

/*===========================================================================

                     BOOST TYPES AND STRUCTURES 

===========================================================================*/

typedef struct
{
    pm_comm_info_type        *comm_ptr;
    pm_pwr_data_type  pm_pwr_data;
} pm_boost_data_type;

/*===========================================================================

                     FUNCTION DECLARATION 

===========================================================================*/
void pm_boost_driver_init(pm_comm_info_type *comm_ptr, peripheral_info_type *peripheral_info, uint8 pmic_index);

pm_boost_data_type* pm_boost_get_data(uint8 pmic_index);

uint8 pm_boost_get_num_peripherals(uint8 pmic_index);


#endif // PM_BOOST_DRIVER__H
