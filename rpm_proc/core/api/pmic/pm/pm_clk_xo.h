#ifndef PM_CLK_XO__H
#define PM_CLK_XO__H

/*! \file pm_clk_xo.h
*  \n
*  \brief This header file contains functions and variable declarations 
*         to support PMIC XO Clock peripheral.
*  
*  \n &copy; Copyright 2013-2016 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/* =======================================================================
                                Edit History
This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/rpm.bf/1.8/core/api/pmic/pm/pm_clk_xo.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
04/29/13   kt      Initial version. 
========================================================================== */
#include "com_dtypes.h"
#include "pm_err_flags.h"
#include "pm_resources_and_types.h"
#include "pm_clk.h"

/*===========================================================================

                 API PROTOTYPES

===========================================================================*/
/** @addtogroup pm_clk_xo
@{ */

/** Configures XO warmup delay time. The delay time is the number of
    sleep (32 kHz) clock cycles to wait for the XO clock to warm up.

    @param[in] pmic_chip   Selects the device in which the buffers being
                           controlled are located. The device index starts
                           with zero.

    @param[in] clk_type    Selects the clock type. For details, see #pm_clk_type.

    @param[in] num_sleep_clk_cycles Number of sleep (32 kHz) clock cycles to wait. 
                                    The value cannot be greater than 2047.
  
    @return
    Success or Error -- See #pm_err_flag_type.

    <b>Example</b> 
    @code
    pm_clk_xo_set_warmup_time(0, PM_CLK_XO, 1000);  @endcode
 */
pm_err_flag_type pm_clk_xo_set_warmup_time(uint8 pmic_chip, pm_clk_type clk_type, uint32 num_sleep_clk_cycles);

/** Configures XO warmup delay time. The delay time is the number of
    sleep (32 kHz) clock cycles to wait for the XO clock to warm up.

    @param[in] pmic_chip   Selects the device in which the buffers being
                           controlled are located. The device index starts
                           with zero.

    @param[in] clk_type    Selects the clock type. For details, see #pm_clk_type.

    @param[out] num_sleep_clk_cycles Pointer to return the
                            number of sleep (32 kHz) clock
                            cycles to wait.
  
    @return
    Success or Error -- See #pm_err_flag_type.
 */
pm_err_flag_type pm_clk_xo_get_warmup_time(uint8 pmic_chip, pm_clk_type clk_type, uint32 *num_sleep_clk_cycles);

/** @} */ /* end_addtogroup pm_clk_xo */
#endif /* PM_CLK_XO__H */
