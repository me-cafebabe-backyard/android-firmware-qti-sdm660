/*==============================================================================
  FILE:         uSleep_target.c

  OVERVIEW:     This file provides uSleep target specfic functions while in
                island mode

  DEPENDENCIES: Object file generated from source is marked as island section
  
                Copyright (c) 2014-2018 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/uSleep/src/target/uSleep_target.c#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include "DALStdDef.h"
#include "CoreVerify.h"
#include "uSleep_target.h"
#include "qurt.h"
#include "uSleep_hwio.h"
#include "uSleep_HALhwio.h"
#include "uSleep_log.h"
#include "uSleep_util.h"
#include "uTimetick.h"

/*==============================================================================
                       EXTERNAL FUNCTION DEFINITIONS
 =============================================================================*/
/* 
 * uSleepTarget_enterIdle 
 */
void uSleepTarget_enterIdle(void)
{
  /* Wait for wakeup interrupt */ 
  qurt_power_wait_for_active();
  return;
}

/* 
 * uSleepTarget_configPowerMode
 */
void uSleepTarget_configPowerMode(target_power_mode mode, boolean enablePMI)
{
  uint32 wakeupIn;
  uint32 clkGatingMode; 
  uint32 wakeIRQ;
  uint32 saveRestore;

  if(TARGET_POWER_MODE_CLOCKGATE == mode)
  {
    wakeupIn      = 0;
    clkGatingMode = 1;
    wakeIRQ       = 0;
    saveRestore   = 0;
  }
  else
  {   
    wakeupIn      = 1;
    clkGatingMode = 0;
    wakeIRQ       = (TRUE == enablePMI) ? 1 : 0;
    saveRestore   = 1;
  }

  USLEEP_HWIO_OUT(SLPC_CFG, 
                  USLEEP_HWIO_FVAL( SLPC_CFG, EXTHW_WAKE_EN,       0x1           ) |
                  USLEEP_HWIO_FVAL( SLPC_CFG, MEM_PU_PERI_STAGGER, 0x1           ) |
                  USLEEP_HWIO_FVAL( SLPC_CFG, MEM_PD_PERI_STAGGER, 0x0           ) |
                  USLEEP_HWIO_FVAL( SLPC_CFG, MEM_PU_ARRY_STAGGER, 0x1           ) |
                  USLEEP_HWIO_FVAL( SLPC_CFG, MEM_PD_ARRY_STAGGER, 0x0           ) |
                  USLEEP_HWIO_FVAL( SLPC_CFG, WAKEUP_IN_EN,        wakeupIn      ) |
                  USLEEP_HWIO_FVAL( SLPC_CFG, CLK_GATING_MODE,     clkGatingMode ) |
                  USLEEP_HWIO_FVAL( SLPC_CFG, SAW_DBG,             0x0           ));

  USLEEP_HWIO_OUT(SPMCTL_EN_STATERET,
                  USLEEP_HWIO_FVAL( SPMCTL_EN_STATERET, WAKE_IRQ, wakeIRQ     ) |
                  USLEEP_HWIO_FVAL( SPMCTL_EN_STATERET, RESTORE,  saveRestore ) |
                  USLEEP_HWIO_FVAL( SPMCTL_EN_STATERET, SAVE,     saveRestore ) );
     
  /* Override wait for SMMU powerup as SMMU will be turned off during island entry*/
  USLEEP_HWIO_OUTF( SPM_EVENT_CTL, SMMU_STATUS_OVRRD,  0x1 );

  /* Override wait for Q6 PLL lock */
  USLEEP_HWIO_OUTF(SPM_EVENT_CTL, PLL_OVRRD, 0x1);

  return;
}

/* 
 * uSleepTarget_programWakeupTimer 
 */
void uSleepTarget_programWakeupTimer(uint64 wakeupTime)
{
  uSleep_setLastSleepWakeupInternal(wakeupTime);

  /* Program the wakeup time */
  uTimetick_SetWakeUpTimerInterrupt(wakeupTime);
  uTimetick_EnableWakeUpTimerInterrupt(TRUE);

  uSleepLog_printf(USLEEP_LOG_LEVEL_PROFILING, (1*2),
                   " Set wakeup (match: 0x%llx)",
                   MICRO_ULOG64_DATA(wakeupTime));

  /* Verify wakeup time is valid as late as possible */
  CORE_VERIFY(uTimetick_Get() < wakeupTime);

  return;
}

/* 
 * uSleepTarget_disableWakeupTimer 
 */
void uSleepTarget_disableWakeupTimer(void)
{
  uSleepLog_printf(USLEEP_LOG_LEVEL_PROFILING, 0,
                   "Disable wakeup timer");

  /* To stop the AON wakeup timer interrupt, since this function is 
   * shared with uSleep, we must use the uTimetick API. */ 
  uTimetick_EnableWakeUpTimerInterrupt(FALSE);
  return;
}

/* 
 * uSleepTarget_enterLowPowerMode 
 */
void uSleepTarget_enterLowPowerMode(uSleep_LPR *mode, uint64 wakeupTime)
{
  uSleepLog_printf(USLEEP_LOG_LEVEL_PROFILING, 0,
                   "Entering LPM",
                   mode->name);

  CORE_VERIFY(NULL != mode->enter_func);
  mode->enter_func(wakeupTime);

  return;
}

/* 
 * uSleepTarget_exitLowPowerMode 
 */
void uSleepTarget_exitLowPowerMode(uSleep_LPR *mode)
{
  uSleepLog_printf(USLEEP_LOG_LEVEL_PROFILING, 0, 
                   "Exiting LPM");

  CORE_VERIFY(NULL != mode->exit_func);
  mode->exit_func();

  return;
}

/* 
 * uSleepTarget_configureIslandTransitionPowerMode
 */ 
void uSleepTarget_configureIslandTransitionPowerMode(boolean transition)
{
  uSleep_power_mode mode;
  
  if(TRUE == transition)
  {
    uSleepLog_printf(USLEEP_LOG_LEVEL_TRANSITION, 0,
                     "Config transition LPM");

    /* In the transition period, enter cached clock gating mode */
    uSleepTarget_configPowerMode(TARGET_POWER_MODE_CLOCKGATE, FALSE);
    qurt_power_override_wait_for_idle(1);
  }
  else
  {
    mode = uSleep_getLowPowerModeInternal();

    uSleepLog_printf(USLEEP_LOG_LEVEL_TRANSITION, 0,
                     "Unconfig transition LPM");

    if(USLEEP_LPM_PLUS_ENABLE == mode)
    {
      uSleepTarget_configPowerMode(TARGET_POWER_MODE_APCR, TRUE);
      qurt_power_override_wait_for_idle(0);
    }
    else
    {
      uSleepTarget_configPowerMode(TARGET_POWER_MODE_APCR, FALSE);
      qurt_power_override_wait_for_idle(1);
    }
  }

  return;
}

