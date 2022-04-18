/*! \file pm_app_clk.c
 *  \n
 *  \brief Implementation file for CLOCK application level APIs. 
 *  \n  
 *  \n &copy; Copyright 2015-2016 QUALCOMM Technologies Incorporated, All Rights Reserved
 */

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

$Header: //components/rel/rpm.bf/1.8/core/pmic/pm/app/clk/src/pm_app_clk.c#1 $
 
when        who     what, where, why
--------    ---     ----------------------------------------------------------
07/23/15    kt       Created
========================================================================== */
/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "pm_app_clk.h"
#include "pm_clk_xo.h"
#include "pm_clk_driver.h"
#include "pm_comm.h"

/*===========================================================================

                     API IMPLEMENTATION 

===========================================================================*/

pm_err_flag_type pm_app_clk_get_xo_warmup_time(uint32 *warmup_time_usec)
{
    pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;
    uint32 num_sleep_clk_cycles = 0;

    if (warmup_time_usec == NULL)
    {
        return PM_ERR_FLAG__INVALID_POINTER;
    }

    /* Get the number of sleep (32 kHz) clock cycles to wait based on primary PMIC PM_CLK_BB_1 timer */
    err_flag = pm_clk_xo_get_warmup_time(0, PM_CLK_BB_1, &num_sleep_clk_cycles);

    if (err_flag == PM_ERR_FLAG__SUCCESS)
    {
       /* Calculate the warm-up time in micro seconds: N is the number of sleep (32 KHz) clock cycles,
          we need to add at most 3 clock cycles of synchronization time.
        
          warmup_time (micro secs) = ((N + 3) * 1000)/32
       */
       *warmup_time_usec = ((num_sleep_clk_cycles + 3) * 1000)/32;
    }
    
    return err_flag;
}
