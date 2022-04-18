/*=============================================================================

                               rpm_target_init.c

GENERAL DESCRIPTION
  This file contains the target initialization for the RPM.

EXTERNALIZED FUNCTIONS

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None

Copyright (c) 2015 by Qualcomm Technologies, Inc.  All Rights Reserved.

  $Header:
  $Author:
  $DateTime:
=============================================================================*/

#include <assert.h>
#include "comdef.h"

#include "cortex-m3.h"
#include "npa_init.h"
#include "comdef.h"
#include "smem.h"
#include "rpmserver.h"
#include "mpm.h"
#include "vmpm.h"
#include "dog.h"
#include "time_service.h"
#include "QDSSLite.h"
#include "icb_rpm.h"
#include "swevent.h"
#include "railway.h"
#include "cpu.h"
#include "kvp.h"
#include "ddr_drivers.h"
#include "system_db_rpm.h"
#include "rpm_settling_timer.h"
#include "low_power_led.h"
#include "rpm_mpu.h"

#include "HALhwio.h"
#include "hw_version.h"
#include "coredump.h"
#include "Clock.h"
#include "PlatformInfo.h"
#include "version.h"
#include "timetick.h"
#include "version.h"
#include "image_layout.h"
#include "glink.h"
#include "CoreVerify.h"
#include "gcc_rpm_branch_ena_vote_hwio.h"
#include "sleep_v.h"
#include "cpr.h"


#define ARRAY_SIZE(a) (sizeof(a)/sizeof((a)[0]))

#define SHARED_IMEM_BASE 0x746BF000

#define RESERVED_IMEM_DEBUG_COOKIE  (SHARED_IMEM_BASE + 0x00000B18)
#define RPM_INIT_COOKIE             (SHARED_IMEM_BASE + 0x00000B1C)
#define DEBUG_COOKIE_VALUE          0x53444247

#ifdef PRE_SILICON_WORKAROUND
// RPM runs slower on Virtio/RUMI and wdog exipres after APPS set transition.
#define DOG_BARK_AFTER_BOOT 0xFFFFF
#define DOG_BITE_AFTER_BOOT 0xFFFFF
#else
#define DOG_BARK_AFTER_BOOT 0x400 // ~31.2 ms
#define DOG_BITE_AFTER_BOOT 0x800 // ~62.5 ms
#endif


typedef void (*init_fcn)(void);
enum
{
  RPM_SERVER_INIT_DONE,
  RPM_INIT_DONE,
};


//prng stack protection init
extern void __init_stack_chk_guard(void);

extern void time_service_init(void);
extern void sched_run(void);
extern uint64_t sched_get_next_start(void);
extern unsigned int npa_num_pending_events(void);
extern void npa_process_event(void);
extern void exceptions_init(void);
extern void exceptions_enable(void);
extern void pm_init(void);
extern void debug_init(void);
extern void swevent_init(void);
extern void swevent_qdss_init(void);
extern void prevent_further_heap_frees(void);
extern void busywait_init(void);
extern void rpm_settling_timer_init(void);
extern void message_ram_init(void);
extern void gpio_toggle_init(void);
extern void misc_init(void);
//Get rid of this once we're back to one railway.
extern void railway_init_v2(void);
extern void railway_init_early_proxy_votes(void);
extern void populate_image_header(void);
extern void DALSYS_PropsInit(void);
extern void zqcal_task_init(void);
extern void acc_init(void);
extern void railway_sw_mode_poke(void);
//extern void debug_cookie_init(void);
//extern void rpm_init_done(void);
//extern void rpm_server_init_done(void);
extern void glink_ssr_init( void );
extern void glink_init(void);
extern void xport_rpm_toc_init(void);
extern void xport_rpm_init(void);
#if (defined (VSENSE_FEATURE_ENABLED))
extern void vsense_init(void);
#endif

#if (defined(SDM660_STUBS))
#include "pmapp_npa.h"
/*
 * Vsense stub
 */
void vsense_init(void){}

#endif /* SDM660_STUBS */


/*
 * CR 998818 - HW Workaround
 * The bit 7 of 0x95e80 is stuck at 0 and cannot be writable.
 * Reserve the address so that SW cannot use the address.
 */
//volatile unsigned broken_memory __attribute__((at(0x95e80)));// = 0xDEAD0000;


__attribute__((section("proxy_cram_reclaim_pool")))
static void init_time_proxy_votes(void)
{


  kvp_t *kvp;
  uint32 req = 1;
  static unsigned ENABLED_KEY = 0x62616e45;

  extern void Clock_SetSPMStates( kvp_t *kvp );

  //init time request for CXO on behalf of apps
  kvp = kvp_create(0);
  kvp_clear(kvp);
  kvp_put(kvp, ENABLED_KEY, sizeof(req), &req);
  rpm_send_init_proxy_vote(RPM_CLOCK_0_REQ, /*CXO is CLK0*/ 0, /*Apps is master 0*/ 0, kvp);

  Clock_SetSPMStates(kvp);
  kvp_destroy(kvp);

}

static void debug_cookie_init(void)
{
   unsigned int cookie = 0;
   cookie =   (*((volatile unsigned int *) (RESERVED_IMEM_DEBUG_COOKIE)));

   if(cookie == DEBUG_COOKIE_VALUE)
   {
    __asm__("BKPT #0x0");
   }
}


static void rpm_init_done(void)
{
    unsigned *cookie = (unsigned *)(RPM_INIT_COOKIE);
    *cookie |= (1 << RPM_INIT_DONE);
}

static void rpm_server_init_done(void)
{
    unsigned *cookie = (unsigned *)(RPM_INIT_COOKIE);
    *cookie |= (1 << RPM_SERVER_INIT_DONE);
}


static void rpm_mpu_enable_data_ram_protection(void)
{
    rpm_mpu_enable_region(RPM_MPU_RGN_DATA_RAM, TRUE);
}

static void rpm_mpu_enable_code_ram_protection(void)
{
    rpm_mpu_enable_region(RPM_MPU_RGN_CODE_RAM_HEAP, TRUE);
    rpm_mpu_enable_region(RPM_MPU_RGN_CODE_RAM, TRUE);
}

__attribute__((section("proxy_cram_reclaim_pool")))
const init_fcn init_fcns[] =
{
  populate_image_header,
  npa_init,
  PlatformInfo_Init, /* Needs to be before pm_init since PMIC driver init PMIC based on platform type (RUMI/virtio/etc). */
  pm_init,
  smem_init,
  rpm_reclaim_smem_init_code_ram_pool,
  railway_init_v2,
  message_ram_init,
  acc_init,
  cpr_init,
  rpm_reclaim_data_ram_pool,
  rpm_mpu_enable_data_ram_protection, /* must be after rpm_reclaim_data_ram_pool() to make sure
                                         no instruction fetched from the data ram reclaim pool */
  (init_fcn)Clock_Init,
  railway_init_early_proxy_votes, /* must be after Clock_Init since it causes railway transition to happen 
                                    and there is no EBI vote before Clock_Init and EBI voltage dropped to retention */
  __init_stack_chk_guard,
  ddr_init,
  glink_init,
  xport_rpm_toc_init,
  xport_rpm_init,
  version_init,     /* Needs to be after glink_init */
  rpmserver_init,
  rpm_server_init_done,
  railway_init_proxies_and_pins,
  icb_init,
  cpu_init,
//  debug_init,
  vmpm_init,
  glink_ssr_init,
  sleep_init,
  QDSSInit,
  exceptions_enable,
  swevent_qdss_init,
  system_db_init,
  rpm_settling_timer_init,
  low_power_led_init,
  zqcal_task_init,
  gpio_toggle_init,
  misc_init,
  rpm_set_changer_common_init,
#if (defined (VSENSE_FEATURE_ENABLED))
  vsense_init,
#endif
};


__attribute__((section("proxy_cram_reclaim_pool")))
__attribute__((noinline))
static void rpm_do_target_init(void)
{
    unsigned i;

#ifdef INIT_PRNG_NO_TZ
    extern uint32 g_prng_config_enable;

    if (g_prng_config_enable == 0)
    {
        g_prng_config_enable = 1;
    }
#endif

    debug_cookie_init();
    DALSYS_PropsInit();
    exceptions_init();
    rpm_core_dump_init();
    rpm_mpu_init();
    busywait_init();
    timetick_init();
    dog_init();

    // We need to have the clock to message RAM turned on *before* we intiailize
    // the rpmserver driver.  This is *before* we initialize the clock driver,
    // so we have to just do it ourselves.
    // Sets the vote bit for msg_ram_hclk
    HWIO_OUTF(GCC_RPM_CLOCK_BRANCH_ENA_VOTE, MSG_RAM_AHB_CLK_ENA, 1);

    mpm_init();
    time_service_init();
    swevent_init();

    SWEVENT(RPM_BOOT_STARTED, get_free_heap_space());

    for(i = 0; i < ARRAY_SIZE(init_fcns); ++i)
    {
        dog_kick();
        SWEVENT(RPM_BOOT_INIT_FCN_STARTED, i, get_free_heap_space());
        init_fcns[i]();
        SWEVENT(RPM_BOOT_INIT_FCN_FINISHED, i, get_free_heap_space());
    }

    dog_set_bark_time(DOG_BARK_AFTER_BOOT);
    dog_set_bite_time(DOG_BITE_AFTER_BOOT);

    init_time_proxy_votes();
    prevent_further_heap_frees();

    rpm_init_done();

    SWEVENT(RPM_BOOT_FINISHED, get_free_heap_space());
}

void rpm_target_init(void)
{
    rpm_do_target_init();
    rpm_reclaim_code_ram_pool();
    rpm_mpu_enable_code_ram_protection(); /* must be after rpm_reclaim_code_ram_pool() to make sure 
                                             no instruction fetched from code ram reclaim pool */
}

