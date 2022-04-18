/*============================================================================
  FILE:         sleep_perform.c

  OVERVIEW:     This file provides the sleep task and OS-specific
                functionality for the RPM processor.

  DEPENDENCIES: sleep_init() should be called before using any other function
                in the sleep subsystem.

                Copyright (c) 2010-2013 Qualcomm Technologies, Inc.
                All Rights Reserved.
                Qualcomm Confidential and Proprietary
============================================================================*/
/*=======================================================================


========================================================================*/

#include "cortex-m3.h"
#include "DALSysTypes.h"
#include "CoreConfig.h"
#include "CoreVerify.h"
#include "npa.h"
#include "rpm_definitions.h"
#include "time_service.h"
#include "pm_clk_sleep.h"
#include "pm_clk_xo.h"
#include "pm_pon.h"
#include "pm_version.h"
#include "mpm.h"

#include "railway.h"
//#include "dog.h"

/* ==================================================================
                        EXTERNAL VARIABLES
   ================================================================== */
extern bool use_pmic_wdog;

/* ==================================================================
                  EXTERNAL FUNCTION DECLARATIONS
   ================================================================== */
extern void rpm_halt_enter(void);
extern void cxo_shutdown_enter(void);
extern void vdd_min_enter(bool mock_vdd_min);
extern void rpm_halt_exit(void);
extern void cxo_shutdown_exit(void);
extern void vdd_min_exit(bool mock_vdd_min);
extern uint64_t sched_get_next_start(void);
extern void sleep_early_init(void);
extern void sleep_target_init(void);
extern void sleep_voltages_init(void);

void sleep_modes_init(void);

int    cx_id, mx_id;

// to support tcxo
pm_on_off_type tcxo_on;

static npa_query_handle sleep_cxo_query_handle;

typedef void (*lprm_func)(void);

/* ==================================================================
                        GLOBAL DEFINES
   ================================================================== */
#define START_TIME_HAIRY_THRESHOLD (2000)

#ifdef MSM_DISABLE_SLEEP
volatile boolean sleep_allow_low_power_modes = FALSE;
#else
volatile boolean sleep_allow_low_power_modes = TRUE;
#endif

#ifdef MSM_DISABLE_DEEP_SLEEP
volatile boolean deep_sleep_enabled = FALSE;
#else
volatile boolean deep_sleep_enabled = TRUE;
#endif

#ifdef MSM_MOCK_VDD_MIN_ONLY
volatile boolean mock_vdd_min_only = TRUE;
#else
volatile boolean mock_vdd_min_only = FALSE;
#endif


/* ==================================================================
                  INTERNAL FUNCTION DECLARATIONS
   ================================================================== */

__attribute__((section("sleep_cram_reclaim_pool")))
void sleep_init(void)
{
    cx_id = rail_id("vddcx");
    mx_id = rail_id("vddmx");

    assert(RAIL_NOT_SUPPORTED_BY_RAILWAY!=cx_id);
    assert(RAIL_NOT_SUPPORTED_BY_RAILWAY!=mx_id);

    sleep_voltages_init();

    sleep_modes_init();

    /* set tcxo status */
    pm_clk_sleep_src_status(0, PM_CLK_SLEEP, &tcxo_on);
    /* allow the mpm to set up cxo sleep times based on this*/
    mpm_init_xtal();

    CORE_VERIFY_PTR(sleep_cxo_query_handle = npa_create_query_handle( "/xo/cxo" ));
}

uint32 sleep_perform_lpm(void)
{
    npa_query_type   sleep_query_result;
    npa_query_status sleep_query_status;
    static volatile  uint64 next_work_start = 0;

    if(!sleep_allow_low_power_modes)
    {
        return 0;
    }

    INTLOCK();
    do
    {
        if(is_any_interrupt_pending())
        {
            break;
        }

        /* Calculate the duration until the backoff time */
        next_work_start = sched_get_next_start();
        if ((time_service_now () + START_TIME_HAIRY_THRESHOLD) >= next_work_start)
        {
          //there is imminent work, so we shouldn't go to sleep
          break;
        }

        //TODO: check latency?

        sleep_query_status = npa_query(sleep_cxo_query_handle, NPA_QUERY_CURRENT_STATE, &sleep_query_result);
        CORE_VERIFY(NPA_QUERY_SUCCESS == sleep_query_status);
        CORE_VERIFY(NPA_QUERY_TYPE_STATE == sleep_query_result.type);

        if(deep_sleep_enabled && (!(sleep_query_result.data.state)))
        {
            vdd_min_enter(mock_vdd_min_only);
            vdd_min_exit(mock_vdd_min_only);
        }
        else
        {
            rpm_halt_enter();
            rpm_halt_exit();
        }
    } while(0);
    INTFREE();

    return 0;
}

