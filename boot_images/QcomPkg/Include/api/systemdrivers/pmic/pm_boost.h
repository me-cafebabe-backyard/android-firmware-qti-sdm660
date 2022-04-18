#ifndef PM_BOOST__H
#define PM_BOOST__H
/*! \file 
 *  \n
 *  \brief
 *  \n
 *  \n This header file contains enums and API definitions for PMIC voltage
 *  regulator driver.
 *  \n
 *  \n &copy; Copyright 2012 - 2014 QUALCOMM Technologies, Inc All Rights Reserved
 */
/* ======================================================================= */

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ----------------------------------------------------------
05/20/14   al      Architecture update 
12/06/12   hw      Rearchitecturing module driver to peripheral driver
=============================================================================*/
/*===========================================================================

                        HEADER FILES

===========================================================================*/

#include "pm_err_flags.h"
#include "pm_resources_and_types.h"
#include "com_dtypes.h"

/*===========================================================================

                        TYPE DEFINITIONS 

===========================================================================*/
/* BOOST peripheral index. This enum type contains all ldo regulators that you may need. */
enum
{
  PM_BOOST_1, 
  PM_BOOST_INVALID
};

/*===========================================================================

                        API PROTOTYPE

===========================================================================*/

/**
 * @name 
 *     pm_boost_volt_level_status
 *
 * @description
 *     obtain the voltage of a regulator. Note, differnt type (
 *     LDO, HFS etc ) may have different programmable voltage
 *     steps. Only support the correct programmable steps. Not
 *     rounding voltages if the voltage selected is not part of
 *     the programmable steps.
 * 
 * @param 
 *     volt_level - returns the voltage.
 * 
 * @return 
 *     error flag type - pm_err_flag_type
 */
pm_err_flag_type pm_boost_volt_level_status
(uint8 pmic_chip, uint8 boost_peripheral_index, pm_volt_level_type* volt_level);


/**
 * @name 
 *     pm_boost_sw_enable
 *
 * @description
 *     enable or disable a rboost.
 * 
 * @param 
 *     enableDisableCmd - turn on and off the regulator.
 * 
 * @return 
 *     error flag type - pm_err_flag_type
 */
pm_err_flag_type pm_boost_sw_enable
(uint8 pmic_chip, uint8 boost_peripheral_index, pm_on_off_type on_off);

/**
 * @name 
 *     pm_boost_sw_enable_status
 *
 * @description
 *     obtain the status of a mode ( HPM, LPM etc ) at an instance.
 *     Note, the mode of a regulator changes dyanmically.
 * 
 * @param 
 *     mode - Select the different mode of a regulator. Example, HPM, LPM
 * 
 * @return 
 *     error flag type - pm_err_flag_type
 */
pm_err_flag_type pm_boost_sw_enable_status
(uint8 pmic_chip, uint8 boost_peripheral_index, pm_on_off_type* on_off);

#endif /* PM_BOOST__H */

