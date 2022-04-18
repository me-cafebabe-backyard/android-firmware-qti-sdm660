/*==============================================================================
  FILE:         uimage.c

  OVERVIEW:     This file provides uimage (software based) transition functions

  DEPENDENCIES: Functions are located in normal mode memory section
  
                Copyright (c) 2015-2017 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/uSleep/src/transition/island.c#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include "comdef.h"
#include "CoreVerify.h"
#include "uSleep_os.h"
#include "uSleep_trans.h"
#include "uSleep_transi.h"
#include "island_mgr.h"
#include "uSleep_HALhwio.h"
#include "uSleep_hwio.h"
#include "island_spm.h"
#include "uSleep_log.h"
#include "uSleep_target.h"
#include "uSleep_util.h"
#include "uInterruptController.h"

/*==============================================================================
                       INTERNAL FUNCTION DEFINITIONS
 =============================================================================*/
/**
 * island_waitForHardwareExit
 *
 * @brief Used to poll for the hardware exit status in error cases where the
 *        exit interrupt can not be used.
 */ 
void island_waitForHardwareExit(void)
{
  uint32 state;

  do
  {
    if(UINTERRUPT_ERROR == uInterruptController_IsInterruptPending(ISLAND_EXIT_IRQ, &state))
    {
      uSleepOS_haltOnError();
    }
  }while(state != 1);

  /* Complete exit path */
  uSleepTrans_notifyComplete(FALSE);

  return;
}

/**
 * island_triggerTransition
 *
 * @brief Triggers hardware to begin the island enter or exit process 
 *  
 * @param triggerType: Enter or exit option
 */ 
static void island_triggerTransition(island_spm_soft_trigger triggerType)
{
  uint32 status;
  uint32 timeoutCount = 0;

  uSleepLog_printf(USLEEP_LOG_LEVEL_TRANSITION, 1, 
                   "Begin bus transition (Mode: %s)",
                   ISLAND_SW_TRIGGER_ENTER == triggerType ? "Isolation" : "Deisolation");

  CORE_VERIFY(triggerType < ISLAND_SW_TRIGGER_LAST);

  if(ISLAND_SW_TRIGGER_ENTER == triggerType)
  {
    /* Ensure SW trigger status is not active. */
    CORE_VERIFY(0 == USLEEP_HWIO_IN(SPM_TRIG_STATUS));

    /* Completion interrupt should already be clear, but need to be sure */
    CORE_VERIFY(uInterruptController_IsInterruptPending(ISLAND_ENTRY_IRQ, &status) == UINTERRUPT_SUCCESS);

    if(status != 0)
    {
      /* Clear interrupt source */
      HWIO_OUTF(LPASS_SCSR_IEC_CTL, ENTER_ISLAND_MODE_IRQ_CLR, 0x1);
      do
      {
        /* ensure source interrupt is clear before starting the sequence */
        CORE_VERIFY(uInterruptController_IsInterruptPending(ISLAND_ENTRY_IRQ, &status) == UINTERRUPT_SUCCESS);
      }while(status != 0);
    }

    /* Trigger the sequence */
    USLEEP_HWIO_OUT(SPM_SW_TRIG, 0x01);
  
    /* Add an initial read of the status to ensure trigger setting is flushed (per HPG) */
    status = USLEEP_HWIO_IN(SPM_TRIG_STATUS);

    /* Wait for AXI isolation sequence to complete before returning on island entry */
    while(0 != USLEEP_HWIO_IN(SPM_TRIG_STATUS))
    {
      CORE_LOG_VERIFY((++timeoutCount < 1024),
                       uSleepLog_printf(USLEEP_LOG_LEVEL_TRANSITION, 0, 
                                        " ERROR: Isolation timeout"));
    }

    uSleepLog_printf(USLEEP_LOG_LEVEL_TRANSITION, 1, 
                     " Sequence trigger complete (count: %d)",
                     timeoutCount);
  }
  else
  {
    /* Set exit bit */
    HWIO_OUTF(LPASS_SCSR_IEC_CTL, EXIT_ISLAND_MODE_TRIG, 0x01);

    /* Add an initial read of the status to ensure trigger setting is flushed (per HPG) */
    status = USLEEP_HWIO_IN(SPM_TRIG_STATUS);

  }

  return;
}

/*==============================================================================
                       EXTERNAL FUNCTION DEFINITIONS
 =============================================================================*/
/*
 * island_exitHandler
 */
void island_exitHandler(uint32 param)
{
  /* Wait for SMMU GDS power to be ON. */
  uint32 status = 0;
  do 
  {
    status = HWIO_INF (LPASS_AUDIO_WRAPPER_Q6_VOTE_LPASS_Q6_SMMU_GDS, Q6_SMMU_PWR_ON);
  }while (status != 1);

  /* Enable XO clock during island exit */
  HWIO_OUTF(LPASS_LPAAUDIO_XO_CLK_CTL, XO_CLK_CGC_EN, 0x1);

  /* Interrupt handler for the bus de-isolation sequence
   * Call the notificaiton API */
  uSleepTrans_notifyComplete(FALSE);

  return;
}

/*
 * uSleep_completeEntry
 */
void uSleep_completeEntry(void)
{
  return;
}

/*
 * uSleep_ClearIslandEntryInterrupt
 *
 * @brief Clear pending island entry interrupt (# 156) at L2VIC.
 */
void uSleep_ClearIslandEntryInterrupt()
{
   HWIO_LPASS_QDSP6SS_L2VIC_INT_CLEARn_OUTI (4, (1 << 28));
}

/*
 * uSleep_continueEntry
 */
void uSleep_continueEntry(void)
{
  uint32  nState;
  int32   entryCount = 0x000fffff;

  /* Trigger AXI bus isolation and begin island entry */
  island_triggerTransition(ISLAND_SW_TRIGGER_ENTER);

  /* Disable XO clock branch coming into LPASS to prevent glitches propagating into the system */
  HWIO_OUTF(LPASS_LPAAUDIO_XO_CLK_CTL, XO_CLK_CGC_EN, 0x0);

  /* Wait for island entry complete interrupt. Give it a few tries before erroring */
  do
  {
    CORE_VERIFY(uInterruptController_IsInterruptPending(ISLAND_ENTRY_IRQ, &nState) == UINTERRUPT_SUCCESS);
  }while((--entryCount > 0) && (nState == 0));

  /* Should be fully transitioned to island mode at this point.  Main sleep function poniter
   * will also be correctly setup. */
  CORE_VERIFY(entryCount > 0);

  /* Clear interrupt source */
  HWIO_OUTF(LPASS_SCSR_IEC_CTL, ENTER_ISLAND_MODE_IRQ_CLR, 0x1);

  /* Clearing island entry interrupt at the source is not clearing the pending interrupt
   * at L2VIC. So, clear the interrupt at L2VIC too for now.  
  */
  uSleep_ClearIslandEntryInterrupt();

  /* Complete island entry by notifying it's complete */
  uSleepTrans_notifyComplete(TRUE);

  return;
}

/*
 * uSleep_prepareForExit
 */
void uSleep_prepareForExit(uSleep_transition_mode mode)
{
  /* Trigger AXI bus isolation and begin HW island exit */
  island_triggerTransition(ISLAND_SW_TRIGGER_EXIT);

  if(UIMAGE_EXIT == mode)
  {
    /* If this is a normal exit request, enable the exit mode low power mode to
     * be entered if the system goes idle while we are waiting for the bus
     * deisolation completion interrupt */
    uSleepTarget_configureIslandTransitionPowerMode(TRUE);
  }
  else
  {
    /* In error case, wait here for hardware exit to complete */
    island_waitForHardwareExit();
  }

  return;
}

/*
 * uSleep_fatalErrorHandler
 */
void uSleep_fatalErrorHandler(uSleep_internal_state state)
{
  uint32  count     = 0;
  uint32  intState  = 0;

  uSleepLog_printf(USLEEP_LOG_LEVEL_TRANSITION, 1, 
                   "USLEEP FATAL ERROR CALLED (state: %d)",
                   state);

  switch(state)
  {
    /* At beginning stage of entry -
     * Nothing to do as the normal exit request was made before (or while in) call
     * to kernel entry */ 
    case uSLEEP_INTERNAL_STATE_FULL_ENTRY:
    case uSLEEP_INTERNAL_STATE_STAGE1_ENTRY:
    {
      return;
    }

    /* Island entry transition is in progress -
     * This stage is after kernel entry, but before final transition is complete
     * In true island case, sleep will be waiting for hardware entry completion interrupt and
     * must wait for the completion interrupt before allowing exit.
     * In uImage case, sleep is waiting for the RPM DDR off notificaiton */ 
    case uSLEEP_INTERNAL_STATE_STAGE2_ENTRY:
    {
      do
      {
        /* Wait for entry completion interrupt - can not start exit sequence before entry is complete.
         * The count value used has no special significance and is simply a large enough value to 
         * give the interrupt a chance to fire before declaring (forced watchdog) a complete failure 
         * in the exit process. */
        if((UINTERRUPT_SUCCESS != uInterruptController_IsInterruptPending(ISLAND_ENTRY_IRQ, &intState)) ||
           (++count > 131072))
        {
          uSleepLog_QDSSPrintf(USLEEP_LOG_LEVEL_TRANSITION, 
                               USLEEP_CRIT_ERR_NUM_ARGS,
                               USLEEP_CRIT_ERR_STR, 
                               USLEEP_CRIT_ERR,
                               state, intState, count);

          /* Could not receive the entry completion interrupt. There is nothing to loose at this
           * point so just try to trigger the exit sequence */
          break;
        }
      } while(intState != 0);

      /* Initiate the exit */
      uSleepTrans_islandControl(UIMAGE_EXIT_FAST);
      break;
    }

    /* Standard exit request is in progress -
     * This stage is before kernel exit call
     * In true island case, sleep is waiting for hardware exit completion interrupt.
     * In uImage case, we will be in the middle of turning DDR on - need to ensure it's on
     * before proceeding */ 
    case uSLEEP_INTERNAL_STATE_STAGE1_EXIT:
    {
      /* Set the fatal exit state so when the transition notification is called it will perform
       * the correct behavior */
      uSleep_setStateInternal(uSLEEP_INTERNAL_STATE_FATAL_EXIT);

      /* Call the remaining critical error handler routines (path after exit sequence triggered) */
      island_waitForHardwareExit();
      break;
    }

    /* Island has completed the HW exit transition - 
     * Continue with the SW error exit handling */ 
    case uSLEEP_INTERNAL_STATE_STAGE2_EXIT:
    {
      uSleep_setStateInternal(uSLEEP_INTERNAL_STATE_FATAL_EXIT);
      uSleepTrans_notifyComplete(FALSE);
      break;
    }

    case uSLEEP_INTERNAL_STATE_ACTIVE:
    {
      /* In island operational mode, just call the island control API with the fatal flag */
      uSleepTrans_islandControl(UIMAGE_EXIT_FAST);
      break;
    }

    /* Invalid or recursive state - function should not have been called */
    default:
    {
      uSleepLog_QDSSPrintf(USLEEP_LOG_LEVEL_TRANSITION, 
                           USLEEP_CRIT_ERR_NUM_ARGS,
                           USLEEP_CRIT_ERR_STR, 
                           USLEEP_CRIT_ERR,
                           state, intState, count);

    }
  }

  return;
}
