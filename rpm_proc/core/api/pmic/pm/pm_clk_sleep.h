#ifndef PM_CLK_SLEEP__H
#define PM_CLK_SLEEP__H

/*! \file pm_clk_sleep.h
*  \n
*  \brief This header file contains functions and variable declarations 
*         to support PMIC Sleep Clock peripheral.
*  
*  \n &copy; Copyright 2013 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/* =======================================================================
                                Edit History
This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/rpm.bf/1.8/core/api/pmic/pm/pm_clk_sleep.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
03/13/13   hw      Rearchitecting clk module driver to peripheral driver
========================================================================== */
/*===========================================================================

                        HEADER FILES

===========================================================================*/
#include "com_dtypes.h"
#include "pm_err_flags.h"
#include "pm_resources_and_types.h"
#include "pm_clk.h"

/*===========================================================================

                 API PROTOTYPES

===========================================================================*/

/**
* 
* @brief Returns on/off (enable/disable) status of the sleep 
*        clock (32K XTAL Oscillator).
* @param pmic_chip: Selects the device in which the buffers 
*                   being controlled are located. Device index
*                   starts with zero
* @param clk_type: Selects which clock type to use. Refer to 
 *                  pm_clk.h for further info on this enum
* @param on_off: Returns on/off status of the sleep clock 
*                Returns PM_ON: if clock is ON
*                Returns PM_OFF: if clock is OFF
 *
 * @note Usage Example:
 *            pm_clk_sleep_source_status(0, PM_CLK_SLEEP, *on_off);
* 
* @return pm_err_flag_type PM_ERR_FLAG__SUCCESS if successful
*/
pm_err_flag_type pm_clk_sleep_src_status(uint8 pmic_chip, pm_clk_type clk_type, pm_on_off_type* on_off);

#endif /* PM_CLK_SLEEP__H */

