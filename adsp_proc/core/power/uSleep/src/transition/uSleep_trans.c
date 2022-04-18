/*==============================================================================
  FILE:         uSleep_trans.c

  OVERVIEW:     This file provides uSleep framework for island transition

  DEPENDENCIES: Object file generated from source is marked as island section
  
                Copyright (c) 2014-2017 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/uSleep/src/transition/uSleep_trans.c#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include "comdef.h"
#include "CoreVerify.h"
#include "uSleep.h"
#include "uSleepi.h"
#include "uSleep_transi.h"
#include "uSleep_timer.h"
#include "uSleep_target.h"
#include "uSleep_util.h"
#include "uSleep_lpr.h"
#include "uSleep_os.h"
#include "uSleep_log.h"
#include "island_mgr.h"
#include "adsppm.h"

/*==============================================================================
                              INTERNAL MACROS
 =============================================================================*/
/* Internal signal values used to coordinate transition routines */
#define USLEEP_CLIENT_EXIT_SIGNAL     0x01

/*==============================================================================
                         EXTERNAL FUNCTION REFERENCES
 =============================================================================*/
void uSleep_prepareForEntry(void);  /* Island entry preperation - Called in normal mode */ 
void uSleep_continueEntry(void);    /* Island entry continuation - Called after Kernel entry */
void uSleep_completeEntry(void);    /* Island entry completion - Called after full entry complete */

void uSleep_prepareForExit(uSleep_transition_mode mode);  /* Island exit preperation - Called in island mode*/
void uSleep_completeExit(uSleep_transition_mode mode);

/*==============================================================================
                             GLOBAL VARIABLES
 =============================================================================*/
/* Signal used to block caller when uSleep exit is requested */
qurt_signal_t g_uSleepExitSignal;

/* Signal used to block a call to exit while in the process of entering island */
qurt_signal_t g_uSleepEnterSignal;

/*==============================================================================
                       INTERNAL FUNCTION DEFINITIONS
 =============================================================================*/
/** 
 * uSleepTrans_internalSignalControl
 * 
 * @brief Controls the internal entry and exit signals to ensure the transition
 *        flow completes properly
 * 
 * @param control:  Enum type for the desired operation on the given signal
 * @param signal:   Initilized entry or exit signal
 */
static void uSleepTrans_internalSignalControl(uSleep_trans_signal_control control,
                                              qurt_signal_t               *signal)
{
  switch(control)
  {
    case USLEEP_TRANS_SIGNAL_CLEAR:
    {
      qurt_signal_clear(signal, USLEEP_CLIENT_EXIT_SIGNAL);
    }
    break;

    case USLEEP_TRANS_SIGNAL_SET:
    {
      qurt_signal_set(signal, USLEEP_CLIENT_EXIT_SIGNAL);
    }
    break;

    case USLEEP_TRANS_SIGNAL_WAIT:
    {
      qurt_signal_wait(signal, USLEEP_CLIENT_EXIT_SIGNAL, QURT_SIGNAL_ATTR_WAIT_ALL);
    }
    break;

    default:
    {
      CORE_LOG_VERIFY(0, uSleepLog_printf(USLEEP_LOG_LEVEL_TRANSITION, 1,
                                          "Invalid signal (%d)",
                                          (uint32)control));
    }
  }

  return;
}

/** 
 * uSleepTrans_performNormalModeTransition
 * 
 * @brief uSleep function that begins the kernel island exit requirements
 */
static uint32 uSleepTrans_performNormalModeTransition(void)
{
  /* Hardware should have exited island at this point, continue the software
   * exit process */
  CORE_VERIFY(uSleep_getStateInternal() == uSLEEP_INTERNAL_STATE_STAGE2_EXIT);
  
  uSleepLog_printf(USLEEP_LOG_LEVEL_TRANSITION, 0, "Starting kernel exit");

  /* Call the kernel transition function to continue the process of exiting island 
   * mode.
   * 
   * When this returns the kernel will allow DDR access, global interrupts will be
   * disabled (special STM mode) and the calling thread (sleep in this case) will be
   * set to the highest priority. */ 
  if(QURT_EOK != island_mgr_island_exit(QURT_ISLAND_EXIT_STAGE1))
  {
    /* Exit is broke, and we can't continue. */
    uSleepOS_haltOnError();
  }
  
  /* AHB-I needs to be restored back to previous after island exit*/
  ADSPPM_ExitSleep();

  /* Complete the target specific requirements to continue the exit process */
  uSleep_completeExit(UIMAGE_EXIT);

  /* Finish the transition now that DDR is fully accessible */
  uSleepTrans_completeTransitionToNormalMode();

  return 0; 
}

/*==============================================================================
                           EXTERNAL FUNCTION DEFINITIONS
 =============================================================================*/
/*
 * uSleepTrans_islandControl
 */
void uSleepTrans_islandControl(uSleep_transition_mode mode)
{
  if(UIMAGE_ENTER == mode)
  {
    /* Reset the entry signal so we can block any possible exit call until uSleep
     * has fully entered */
    uSleepTrans_enterSignalControl(USLEEP_TRANS_SIGNAL_CLEAR);

    /* The entry is divided into seperate calls to allow the functions to be located in
     * different memory sections, as well as allow any target specific requirements to be handled
     * seperaratly.
     * 
     * The prepare function will perform any initial setup required to enter uImage mode
     * while still in normal operational mode. */
    uSleep_prepareForEntry();

    /* AHB-I needs to be running from PEEL PLL before island entry*/
    ADSPPM_EnterSleep();
	
    /* Set CLK_ENABLE bit of Q6 Axi clock before island entry (HW CR QCTDD03809491) */
    uSleepOS_Set_Q6AxiClockConfiguration( CLK_ENABLE );

    /* Invoke the kernel island mangager entry function
     * This will update TLBs and perform other OS specific island entry requirements */
    CORE_VERIFY(ISLAND_MGR_EOK == island_mgr_island_enter());

    /* Set kernel entry stage complete */
    uSleep_setStateInternal(uSLEEP_INTERNAL_STATE_STAGE2_ENTRY);

    /* Perform any further target specific requirements after kernel entry is complete */
    uSleep_continueEntry();
  }
  else
  {
    /* Set the initial exit state and perform any pre-exit requirements */
    if(UIMAGE_EXIT_FAST == mode)
    {
      uSleep_setStateInternal(uSLEEP_INTERNAL_STATE_FATAL_EXIT);
    }
    else
    {
      uSleep_setStateInternal(uSLEEP_INTERNAL_STATE_STAGE1_EXIT);
    }

    /* Prepare for exiting uImage */
    uSleep_prepareForExit(mode);   
  }
 
  return;
}

/* 
 * uSleepTrans_performIslandModeTransition
 */
uint32 uSleepTrans_performIslandModeTransition(void)
{
  /* Function should entered once, only from the island entry request stage */
  CORE_VERIFY(uSleep_getStateInternal() == uSLEEP_INTERNAL_STATE_FULL_ENTRY);

  /* Set initial entry state  */
  uSleep_setStateInternal(uSLEEP_INTERNAL_STATE_STAGE1_ENTRY);

  /* Start the island entry process */
  uSleepTrans_islandControl(UIMAGE_ENTER);

  return 0;
}

/*
 * uSleepTrans_notifyComplete
 */
void uSleepTrans_notifyComplete(uint8 entry)
{
  uSleep_transition_profiling *transProfileData;
  uSleep_internal_state       state = uSleep_getStateInternal();

  if(TRUE == entry)
  {
    transProfileData = uSleep_getProfilingDataPtr();

    /* Ensure we are in stage 2 entry, waiting for completion notification */
    CORE_VERIFY(uSLEEP_INTERNAL_STATE_STAGE2_ENTRY == state);

    /* Complete target specific requirments to enter uImage mode */
    uSleep_completeEntry();

    /* Island entry is complete, set task pointer to main uSleep function */
    uSleepOS_setIdleFunctionPtr(uSleepOS_performLPM);

    uSleepLog_printf(USLEEP_LOG_LEVEL_TRANSITION, 1,
                     "Entry done (LPM+: %s)",
                     USLEEP_LPM_PLUS_ENABLE == 
                     uSleep_getLowPowerModeInternal() ? "Enabled" : "Disabled");

    /* Record the uSleep entry transition time */
    sleepStats_updateValue(&transProfileData->entry_stats,
                           uTimetick_Get() - transProfileData->entry_start_time);

    /* Exit STM */
    qurt_power_exit();

    /* Let anyone waiting that entry is done */
    uSleep_setStateInternal(uSLEEP_INTERNAL_STATE_ACTIVE);
    uSleepTrans_enterSignalControl(USLEEP_TRANS_SIGNAL_SET);
  }
  else
  {
    if(uSLEEP_INTERNAL_STATE_FATAL_EXIT == state)
    {
      /* In cases of fatal error, exit island immediatly after island HW has
       * finished it's transition. */
      uSleepOS_setIdleFunctionPtr(uSleepOS_performError);

      /* Exit immediately */
      if(QURT_EOK != island_mgr_island_exit(QURT_ISLAND_EXIT_STAGE1) ||
         QURT_EOK != island_mgr_island_exit(QURT_ISLAND_EXIT_STAGE2))
      {
        /* Fatal error exit is broke, nothing more we can do here. */
        uSleepOS_haltOnError();
      }
    }
    else
    {
      CORE_VERIFY(uSLEEP_INTERNAL_STATE_STAGE1_EXIT == state);

      uSleepLog_printf(USLEEP_LOG_LEVEL_TRANSITION, 0, "Sleep exit stage 1 complete");

      uSleep_setStateInternal(uSLEEP_INTERNAL_STATE_STAGE2_EXIT);

      /* Island exit prep is done, finish the non-error exit process */
      uSleepOS_setIdleFunctionPtr(uSleepTrans_performNormalModeTransition);

      /* Force the sleep thread out of any call to the kernel wait for idle API so the exit can 
       * continue in the sleep context which will run the function set above. */
      qurt_power_cancel_wait_for_idle();
    }
  }

  return;
}

/*
 * uSleepTrans_exitSignalControl
 */
void uSleepTrans_exitSignalControl(uSleep_trans_signal_control control)
{
  uSleepTrans_internalSignalControl(control, &g_uSleepExitSignal);
  return;
}

/*
 * uSleepTrans_enterSignalControl
 */
void uSleepTrans_enterSignalControl(uSleep_trans_signal_control control)
{
  uSleepTrans_internalSignalControl(control, &g_uSleepEnterSignal);
  return;
}


