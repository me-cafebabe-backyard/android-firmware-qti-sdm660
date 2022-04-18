/*==============================================================================
  FILE:         uSleep_os.c

  OVERVIEW:     This file provides uSleep API and functions that reside in
                normal mode memory space

  DEPENDENCIES: None
  
                Copyright (c) 2014-2017 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/uSleep/src/os/qurt/ddr/uSleep_os.c#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include "DALStdDef.h"
#include "CoreVerify.h"
#include "uSleep.h"
#include "uSleepi.h"
#include "uSleep_util.h"
#include "uSleep_timer.h"
#include "uSleep_target.h"
#include "uSleep_transi.h"
#include "uSleep_lpr.h"
#include "uSleep_log.h"
#include "uSleep_ddr_log.h"
#include "uSleep_qdi.h"
#include "CoreTime.h"
#include "timer.h"
#include "sleep_os.h"
#include "uSleep_os.h"
#include "client_os.h"
#include "uSleep_node.h"
#include "uSleep_solver.h"
#include "simple_solver.h"
#include "sleep_solver.h"
#include "sleepActive.h"
#include "DDIClock.h"

 /* DAL clock handle for making clock requests */
DalDeviceHandle  *dalClkHandle = NULL;

ClockIdType      spm_clock_id  = 0;
ClockIdType      axi_clock_id  = 0;

/*==============================================================================
                           INTERNAL TRANSITION FUNCTIONS
 =============================================================================*/
/** 
 * uSleepOS_beginEntryTransition
 * 
 * @brief Entry function to uSleep called from STM context. 
 *        uSleep entry is now committed.
 *  
 * @note Assumes function is called from STM via main sleep function 
 */
static void uSleepOS_beginEntryTransition(uint64 startTime)
{
  uSleep_internal_state         state         = uSleep_getStateInternal();
  uSleep_transition_profiling   *profileData  = uSleep_getProfilingDataPtr();
  const sleep_solver_deadlines  *deadlines    = sleepActive_GetSolverHardDeadlines();

  CORE_VERIFY_PTR(profileData);

  uSleepDDRLog_QDSSPrintf(USLEEP_DDR_LOG_LEVEL_TRANSITION, 
                          USLEEP_ENTER_NUM_ARGS,
                          USLEEP_ENTER_STR, 
                          USLEEP_ENTER);

  /* Clear any ATS threshold timer, as when uImage is exited, it will trigger ATS directly */
  sleepActive_clearThreasholdTimer();

  /* Set timestamp of the start of the uSleep entry point */
  profileData->entry_start_time = startTime;

  /* Record number of island entries */
  profileData->total_entries++;

  /* Verify we are currently in normal mode before beginning transition
   * to island mode */
  CORE_VERIFY(uSLEEP_INTERNAL_STATE_IN_DDR == state);

  /* Only defer normal operational timers, island ones will be done as part of
   * low power mode entry in island. */
  timer_defer_match_interrupt_64();

  /* Set full entry state */
  uSleep_setStateInternal(uSLEEP_INTERNAL_STATE_FULL_ENTRY);
  
  /* Update the PMI handler function to the uImage version */
  uSleepTarget_setPMIHandler();

  /* Call LPR init functions */
  uSleepLPR_init();

  /* Transfer normal operational wakeup time to island system */
  uSleepTrans_setDDRWakeupTimeInternal(deadlines->normal_min);

  /* Call notification CB's while still in normal operational mode */
  uSleepTrans_transitionNotify(USLEEP_STATE_ENTER);

  /* Update the idle function pointer to the main transition function.
   * This is done because we must switch to an island function pointer. */
  uSleepOS_setIdleFunctionPtr(uSleepTrans_performIslandModeTransition);

  return;
}

/** 
 * uSleepOS_prepareForIslandEntry
 * 
 * @brief Prepares uSleep by ensuring various sleep options & 
 *        settings allow entry. If the function returns, it will have
 *        already placed the system in STM.         
 *    
 * @return Time of STM entry (in ticks) or 0 if unable to enter 
 *         any sleep (i.e. early exit cases)
 */
static uint64 uSleepOS_prepareForIslandEntry(void)
{
  /* Use the main sleep prepare function which performs all the
   * required actions by waiting for idle and verifying sleep modes */
  return(sleepOS_prepareForSleep(SLEEP_OS_IDLE_MODE_LPI));
}

/** 
 * uSleepOS_completeIslandExit
 * 
 * @brief Cleans up any actions on island exit that were done in the entry 
 *        preperation call 
 */
static void uSleepOS_completeIslandExit(void)
{
  /* Use the main sleep completion function which performs all the
   * required cleanup actions for normal sleep including STM exit */
  sleepOS_completeSleep(FALSE);
  return;
}

static void uSleepOS_ClockInitialize()
{
  /* Attach Dal handle to clock driver for clock requests */
  CORE_DAL_VERIFY( DAL_DeviceAttach( DALDEVICEID_CLOCK, (DalDeviceHandle **)&dalClkHandle) );

  /* Get clock id for SPM clock*/
  CORE_DAL_VERIFY( DalClock_GetClockId( dalClkHandle,  (const char*)LPASS_Q6_SPM_CLOCKS,   &spm_clock_id) );

  /* Get clock id for AXI clock*/
  CORE_DAL_VERIFY( DalClock_GetClockId( dalClkHandle,  (const char*)GCC_LPASS_Q6_AXI_CBCR, &axi_clock_id) );
	
}

/*==============================================================================
                             EXTERNAL TRANSITION FUNCTIONS
 =============================================================================*/
/*
 * uSleepOS_mainEntry
 */ 
uint32 uSleepOS_mainEntry(void)
{
  uint64                      sleepStart;
  uSleep_idle_entry_ptr_type  uSleepFcnPtr;
  
  /* Update transition times if necessary */
  uSleepTrans_updateTimes();

  /* Allow island debug if option is enabled */
  uSleepTarget_enableIslandDebug(TRUE);

  /* Execute common sleep entry checks */
  sleepStart    = uSleepOS_prepareForIslandEntry();
  uSleepFcnPtr  = uSleepOS_getIdleFunctionPtr();

  if((0 == sleepStart) || (uSleepFcnPtr != uSleepOS_mainEntry))
  {
    uSleepDDRLog_printf(USLEEP_DDR_LOG_LEVEL_TRANSITION, 1,
                        "uSleep early exit (ptr: 0x%x)",
                        (uint32)uSleepFcnPtr);
    qurt_power_exit();

    /* Disallow island debug if option is enabled */
    uSleepTarget_enableIslandDebug(FALSE);

    return 0;
  }

  /***** Begin transition to uImage *****/
  uSleepOS_beginEntryTransition(sleepStart);

  return 0;
}

/*==============================================================================
                               EXTERNAL FUNCTIONS
 =============================================================================*/

/*
 * uSleepOS_SetSPMClockConfiguration
 */
void uSleepOS_SetSPMClockConfiguration()
{
  uint32  pnResultFreq;

  CORE_DAL_VERIFY( DalClock_SetClockFrequency( dalClkHandle, spm_clock_id, 19200000, CLOCK_FREQUENCY_HZ_CLOSEST, &pnResultFreq ) );

  CORE_DAL_VERIFY( DalClock_EnableClock(dalClkHandle, spm_clock_id) );
 
}

/*
 * uSleepOS_Set_Q6AxiClockConfiguration
 */
void uSleepOS_Set_Q6AxiClockConfiguration(clock_enablement_type enable)
{
  if(enable)
  {
     CORE_DAL_VERIFY( DalClock_EnableClock(dalClkHandle, axi_clock_id) );
  }
  else
  {
     CORE_DAL_VERIFY( DalClock_DisableClock(dalClkHandle, axi_clock_id) );
  }
}
/*
 * uSleepOS_cleanupIslandExit
 */
void uSleepOS_cleanupIslandExit(void)
{
  /* Complete and actions there were done at island entry by the perform call */
  uSleepOS_completeIslandExit();

  /* Undefer normal operational timers that were deferred on the way into
   * uSleep after we have exited STM. */
  timer_undefer_match_interrupt();

  /* Disable island debug */
  uSleepTarget_enableIslandDebug(FALSE);

  return;
}


/*
 * uSleepOS_initialize
 */
void uSleepOS_initialize(void)
{
  /* Setup uSleep logging system */
  uSleepLog_initialize();

  /* Setup default uSleep entry point */
  uSleepOS_setIdleFunctionPtr(uSleepOS_mainEntry);

  /* Setup uSleep Node */
  uSleepNode_initialize();

  /* Transition initialization */
  uSleepTrans_initialize();

  /* Setup guest OS client */
  uSleep_guestClientInit();

  /* Set uSleep initial internal state */
  uSleep_setStateInternal(uSLEEP_INTERNAL_STATE_IN_DDR);

  /* Set the solver function */
  uSleepSolver_setSolverFunction(simpleSolver_solve);

  /* Target specific initialization */
  uSleepTarget_initialize();

  /* Setup the handler for the DDR timer while in uImage */
  uSleepTimer_init();

  /* Setup uSleep QDI interface */
  uSleep_QDIInit();

  uSleepOS_ClockInitialize();

  /*SPM clock configuration needs to be explicitly set*/
  uSleepOS_SetSPMClockConfiguration();

  return;
}
