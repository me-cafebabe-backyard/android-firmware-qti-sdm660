/*============================================================================

FILE:      dog.c

DESCRIPTION: RPM watchdog driver

PUBLIC CLASSES: 

INITIALIZATION AND SEQUENCING REQUIREMENTS:  N/A

      Copyright (c) 2010-2012 Qualcomm Technologies Incorporated.
               All Rights Reserved.
         QUALCOMM Proprietary and Confidential

$Header: //components/rel/rpm.bf/1.8/core/power/rpm/dog.c#4 $
$Date: 2017/03/15 $

============================================================================*/

#include <err.h>
#include <DALDeviceId.h>
#include <DALSys.h>
#include "HALhwio.h"
#include "dog.h"
#include "dog_hwio.h"
#include "time_service.h"
#include "CoreVerify.h"
#include "Chipinfo.h"

#ifdef DISABLE_RPM_WATCHDOG
volatile bool rpm_wdog_enabled = 0;
#else
volatile bool rpm_wdog_enabled = 1;
#endif

void busywait (uint32 pause_time_us);

#define WATCHDOG_BARK_TIME_SCLK 0x400 // ~31.25 ms
#define WATCHDOG_BITE_TIME_SCLK 0x800 // ~62.50 ms

static uint32         dog_frozen = 0;
static dog_stats_type dog_stats;
#if 0
static dog_stats_type pmic_dog_stats;
#endif

static void dog_update_stats(dog_stats_type* dog, dog_event_type dog_event, uint32* source)
{
  dog->entries[dog->index].dog_event = dog_event;
  dog->entries[dog->index].dog_event_source = source;
  dog->entries[dog->index].timestamp = time_service_now();
  dog->index = (dog->index + 1) % DOG_STATS_ENTRIES;
}

__asm void dog_bark_isr(void) __irq
{
#ifdef __clang__
    asm("b abort");
#else
    IMPORT abort
    b abort
#endif
}

void dog_set_bark_time(unsigned bark_time)
{
  INTLOCK();
    while(!HWIO_INF(RPM_WDOG_BARK_TIME, SYNC_STATUS));
    HWIO_OUTF(RPM_WDOG_BARK_TIME, WDOG_BARK_VAL, bark_time);
  INTFREE();
}

void dog_set_bite_time(unsigned bite_time)
{
  INTLOCK();
    while(!HWIO_INF(RPM_WDOG_BITE_TIME, SYNC_STATUS));
    HWIO_OUTF(RPM_WDOG_BITE_TIME, WDOG_BITE_VAL, bite_time);
  INTFREE();
}

void dog_enable(unsigned enabled)
{
    if(!rpm_wdog_enabled)
      return;

    enabled = enabled ? 3 : 0; // Identify appropriate settings.
    HWIO_OUT(RPM_WDOG_CTRL, enabled);
}

__attribute__((section("dog_dram_reclaim_pool")))
void dog_init(void)
{
  static boolean already_init = FALSE;

  if(already_init)
    return;

  already_init = TRUE;

#if DAL_CONFIG_TARGET_ID==0x8998
  /*
   * TODO: Delete this when no need to support 8997 RUMI
   */
  if(CHIPINFO_FAMILY_MSM8997 == Chipinfo_GetFamily())
  {
      rpm_wdog_enabled = 0;
  }
#endif

  /* Start the dog ticking. */
  HWIO_OUTF(RPM_TIMERS_CLK_OFF_CTL, WDOG_TIMER_CLK_OFF, 0x0);
  busywait(153);
  dog_set_bark_time(WATCHDOG_BARK_TIME_SCLK);
  dog_set_bite_time(WATCHDOG_BITE_TIME_SCLK);

  dog_enable(TRUE);
}

void dog_kick(void)
{
  if(!dog_frozen)
  {
    void *return_address = (void *)__return_address();	
    INTLOCK();
      while(!HWIO_INF(RPM_WDOG_RESET, SYNC_STATUS));
      HWIO_OUTF(RPM_WDOG_RESET, WDOG_RESET, 0x1);
      dog_update_stats(&dog_stats, DOG_KICK, return_address);
    INTFREE();
  }
}

#if 0
/* PMIC wdog functions */

static void pmic_wdog_cfg(void)
{
    static bool pmic_wdog_configured = 0;
    void *return_address = (void *)__return_address();
    pmic_rtc_init();
    if (pmic_wdog_enable && !pmic_wdog_configured)
    {
        dog_update_stats(&pmic_dog_stats, PMIC_DOG_CFG, return_address);
#ifdef LONG_PMIC_BITE
        pm_pon_wdog_cfg(0, 17, 7, PM_PON_RESET_CFG_WARM_RESET_THEN_D_VDD_BATT_REMOVE_HARD_RESET);
#else
        pm_pon_wdog_cfg(0, 17, 1, PM_PON_RESET_CFG_WARM_RESET_THEN_D_VDD_BATT_REMOVE_HARD_RESET);
#endif
        pm_pon_wdog_enable(0, PM_ON);
        pmic_wdog_configured = 1;
    }
    else if (!pmic_wdog_enable && pmic_wdog_configured)
    {
        dog_update_stats(&pmic_dog_stats, PMIC_DOG_DECFG, return_address);
        pm_pon_wdog_enable(0, PM_OFF);
        pmic_wdog_configured = 0;
    }
}
#endif

void pmic_wdog_pet(bool unconditional)
{
#if 0
    static uint64 last_kick_time = 0;
    void *return_address = (void *)__return_address();
    uint64 cur_time = time_service_now();
    pmic_wdog_cfg();
    if ( pmic_wdog_enable && ( unconditional || cur_time > (last_kick_time+PMIC_WDOG_MAX_SLEEP_TIME) ) )
    {
        dog_update_stats(&pmic_dog_stats, PMIC_DOG_KICK, return_address);
        last_kick_time = cur_time;
        CORE_VERIFY(pm_pon_wdog_pet(0) == PM_ERR_FLAG__SUCCESS);
    }
#endif
}

/* PMIC RTC Logging functions */

struct {
    uint32 pm_time;
    uint64 rpm_time;
} PMIC_timestamp;

void pmic_rtc_init(void)
{
#if 0
    static int init = 0;
    if (init == 0)
    {
        if (pm_rtc_get_time(0,&(PMIC_timestamp.pm_time)) == PM_ERR_FLAG__SUCCESS) {
            PMIC_timestamp.rpm_time = time_service_now();
        } else {
            PMIC_timestamp.pm_time = 0xBAD0FA11;
        }
        init = 1;
    }
#endif
}

