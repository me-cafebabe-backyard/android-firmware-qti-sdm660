/*==============================================================================
  FILE:         cpu_vdd_lpr.c

  OVERVIEW:     This file provides the sleep LPR definition for the
                QDSP6 ALL WAIT low-power modes.

  DEPENDENCIES: None

                Copyright (c) 2010-2017 Qualcomm Technologies Incorporated.
                All Rights Reserved.
                Qualcomm Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/sleep2.0/src/lpr/cpu_vdd_lpr.c#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include "comdef.h"
#include "CoreTime.h"
#include "CoreVerify.h"
#include "sleepActivei.h"
#include "sleep_lpr.h"
#include "sleepi.h"
#include "sleep_log.h"
#include "sleep_target.h"
#include "sleep_statsi.h"
#include "qurt.h"
#include "adsppm.h"
#include "q6_lpm_config.h"
#include "synthLPRM.h"
#include "rpm_messageram.h"
#include "DDIClock.h"

/*==============================================================================
                              EXTERNAL VARIABLES
 =============================================================================*/
extern uint64 g_expectedWakeupTick;

/*==============================================================================
                INTERNAL FUNCTIONS FOR POWER CONFIG LPR'S MODES
 =============================================================================*/
/** 
 * powerConfigLPR_Q6LPMEnter
 *  
 * @brief Parameterized call to prepare core for different low power modes.
 * 
 * @param coreMode: Mode to which SPM HW will be programmed to 
 *                  execute appropriate command sequence.
 * @param wakeupTick: Absolute count of wakeup @19.2MHz
 */
static void powerConfigLPR_Q6LPMEnter(spm_low_power_mode_type coreMode,
                                      uint64                  wakeupTick)
{
  boolean synthHasUncacheableComponents;

  /* If the mode is fully cacheable, don't set a wakeup timer or enable the PMI
   * wakeup interrupt */
  synthHasUncacheableComponents = (synthLPRM_isConfiguringModeFullyCacheable() == TRUE) ? FALSE : TRUE;

  /* q6LPMConfig_setupModeConfig will only configure PMI if APCR is present and
   * the synth mode has uncacheable components */
  q6LPMConfig_setupModeConfig(coreMode, synthHasUncacheableComponents);

  return;
}

/*==============================================================================
                INTERNAL FUNCTIONS FOR CPU VDD LPR'S MODES
 =============================================================================*/
/** 
 * cpuVddLPR_powerCollapseEnter 
 *  
 * @brief Performs the appropriate power collapse depending on the presence of
 *        APCR.
 * 
 * @param coreMode: Mode to which SPM HW will be programmed to 
 *                  execute appropriate command sequence.
 */
static void cpuVddLPR_powerCollapseEnter(spm_low_power_mode_type coreMode)
{
  uint64  tempTimeTick;

  if (sleepOS_isProcessorInSTM() == FALSE)
  {
    return;
  }

  /* Store the time of the last point in sleep code before the power collapse */
  tempTimeTick = CoreTimetick_Get64();
  sleepStats_putLprTimeData(tempTimeTick, SLEEP_STATS_TIME_MSTR_SHUTDOWN_TYPE);

  /* Calling ADSPPM API to ramp down resources (e.g. AHB clock). This
   * request may or may not take effect depending on actual aggregation from 
   * ADSPPM clients */
  ADSPPM_EnterSleep();

  /* Calling clock API to set the SPM CTL PLL override bits appropriately
   * based on the PLL source set.
   */
  Clock_SetOverride();

  /* Call the correct kernel API based on the given shutdown type */
  if((SPM_MODE_APCR_PLL_LPM == coreMode) || 
     (SPM_MODE_APCR_PLL_ON == coreMode))
  {
    /* Perform APCR power collapse */
    CORE_VERIFY(QURT_EOK == qurt_power_apcr_enter());
  }
  else if((SPM_MODE_PWRC     == coreMode) ||
          (SPM_MODE_PWRC_BHS == coreMode))
  {
    /* Currently only non-retention full power collapse mode is supported */
    CORE_VERIFY(QURT_EOK == qurt_power_shutdown_enter(QURT_POWER_SHUTDOWN_TYPE_L2NORET));
  }
  else
  {
    CORE_LOG_VERIFY(0, sleepLog_printf(SLEEP_LOG_LEVEL_WARNING, 1,
                                       "Unsupported coreMode: 0x%x",
                                       coreMode));
  }

  return;
}

/** 
 * cpuVddLPR_powerCollapseExit 
 *  
 * @brief Performs the appropriate exit from power collapse depending on the
 *        presence of APCR.
 */
static void cpuVddLPR_powerCollapseExit(void)
{
  boolean       isRPMAssistedMode;
  uint64        startTime;
  uint32        lprmTime;

  /* If LPR Exit is called as part of Cached Synth mode then 
     no additional stats related profiling is required */
  if(sleepOS_isProcessorInSTM() == FALSE)
  {
    return;
  }

  ADSPPM_ExitSleep();

  /* Check if we are in an RPM assisted mode */
  isRPMAssistedMode = sleepTarget_getRPMAssistedMode();

  if (FALSE == isRPMAssistedMode)
  {
    sleepStats_wakeup_reason  reason;
    uint64                    master_wakeup_tick;

    /* Obtain time when control return to Sleep exit path */
    master_wakeup_tick = 
      sleepStats_getLprTimeData(SLEEP_STATS_TIME_MSTR_RETURN_TYPE);

    /* For standalone PC, wakeup time is scheduled QTimer value or earliest
     * possible point of return to Sleep module */
    if( master_wakeup_tick > g_expectedWakeupTick )
    {
      reason = SLEEP_STATS_WAKEUP_SA_SCHEDULED;

      /* use set Qtimer value as wakeup time */
      master_wakeup_tick = g_expectedWakeupTick;
    }
    else
    {
      reason = SLEEP_STATS_WAKEUP_SA_UNSCHEDULED;
    }

    /* Set stand alone PC wakeup reason and wakeup time in Stats */
    sleepStats_putMiscData(reason, SLEEP_STATS_MISC_WAKEUP_REASON_TYPE);

    startTime = master_wakeup_tick;
  }
  else
  {
    uint64                      wakeupTime;
    sleepStats_wakeup_reason    wakeReason;
    volatile rpm_master_stats_t *rpmStats     = sleepStats_getRpmDataPtr();
    static uint64               lastRPMWakeup = 0;

    CORE_VERIFY_PTR(rpmStats);

    wakeReason = rpmStats->wakeup_reason;

    if(SLEEP_STATS_WAKEUP_RPM_SCHEDULED == wakeReason)
    {
      /* If this is a timer based wakeup, use the wakeup ind as the wakeup time which will
       * account for any possible delay between the bringup req/ack handshake.  
       * Note that this value is only valid for scheduled wakeups */
      wakeupTime = rpmStats->wakeup_ind;
    }
    else
    {
      /* If unscheduled wakeup, use the bringup ack which will always be valid */
      wakeupTime = rpmStats->bringup_ack;

      /* Account for any untraceable, known latency.
       * For SSC, it's the AON/PLL time between receiving the wakeup interrupt
       * and the bringup request to RPM */
#ifdef SLEEP_FIXED_WAKEUP_OFFSET
      wakeupTime += SLEEP_FIXED_WAKEUP_OFFSET;
#endif
    }

    /* Catch errors where RPM didn't update its statistics */
    CORE_VERIFY(wakeupTime > lastRPMWakeup);
    lastRPMWakeup = wakeupTime;

    /* In RPM assisted modes, the wakeup time will come from RPM. Get that here 
     * so it can be used to calculate proper cpu_vdd backoff latency. */
    startTime = wakeupTime;

    /* Set wakeup reason as given from RPM */
    sleepStats_putMiscData(wakeReason, SLEEP_STATS_MISC_WAKEUP_REASON_TYPE);
  }

  /* Set master wakeup time */
  sleepStats_putLprTimeData(startTime, SLEEP_STATS_TIME_WAKEUP_TYPE);

  lprmTime = (uint32)(CoreTimetick_Get64() - startTime);

  /* Catch bad latency values */
  if((0 == lprmTime) || (lprmTime > 0x0f000000))
  {
    sleepLog_printf(SLEEP_LOG_LEVEL_INFO, 1,
                     "CPU_VDD exit (Ticks: 0x%x)",
                     lprmTime);

    CORE_VERIFY(0);
  }

  sleepStats_putLprLatency(lprmTime, SLEEP_STATS_BACKOFF_LATENCY_TYPE);

  return;
}

/*==============================================================================
                 INTERNAL FUNCTIONS FOR POWER CONFIG LPR'S MODES
 =============================================================================*/
/** 
 * powerConfigLPR_initialize
 *  
 * @brief Initialize cpu vdd LPR
 */
void powerConfigLPR_initialize(void)
{
  /* Common Q6SS register setup for all low power modes defined for
   * cpuVdd LPR. */
  q6LPMConfig_setupBase();

  return;
}

/**
 * powerConfigLPR_fullPCEnter
 *
 * @brief This function will be called while entering into the power collapse 
 *        mode with l2 non retention (flushed).
 *
 * @param wakeupTick: Time at which master is expected to wake up.
 */
void powerConfigLPR_fullPCEnter(uint64 wakeupTick)
{
  powerConfigLPR_Q6LPMEnter(SPM_MODE_PWRC_BHS, wakeupTick);
  return;
}

/**
 * powerConfigLPR_apcrPllLpmEnter
 *  
 * @brief Enter function for APCR with rail in low power mode.
 */
void powerConfigLPR_apcrPllLpmEnter(uint64 wakeupTick)
{
  powerConfigLPR_Q6LPMEnter(SPM_MODE_APCR_PLL_LPM, wakeupTick);
  return;
}

/** 
 * powerConfigLPR_apcrEnter 
 *  
 * @brief Enter function for APCR mode (Short Sequence in Q6HPG)
 */
void powerConfigLPR_apcrEnter(uint64 wakeupTick)
{
  powerConfigLPR_Q6LPMEnter(SPM_MODE_APCR_PLL_ON, wakeupTick);
  return;
}

/*==============================================================================
                             CPU VDD Functions
 =============================================================================*/
/**
 * cpuVddLPR_fullPCEnter
 *
 * @brief Enter function for power collapse with no retention
 */
void cpuVddLPR_fullPCEnter(uint64 wakeupTick)
{
  cpuVddLPR_powerCollapseEnter(SPM_MODE_PWRC_BHS);
  return;
}

/** 
 * cpuVddLPR_exit 
 *  
 * @brief Exit function for power collapse with no retention
 */
void cpuVddLPR_exit(void)
{
  cpuVddLPR_powerCollapseExit();
  return;
}

/**
 * cpuVddLPR_apcrEnter
 *
 * @brief Enter function for power collapse with APCR
 */
void cpuVddLPR_apcrEnter(uint64 wakeupTick)
{
  /* Specific APCR mode doesn't matter based on synth mode configuration */
  cpuVddLPR_powerCollapseEnter(SPM_MODE_APCR_PLL_LPM);
  return;
}

