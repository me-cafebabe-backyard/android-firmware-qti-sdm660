/*==============================================================================
  FILE:         lpr_solver.c
 
  OVERVIEW:     This file provides the sleep LPR solver implementation.

  DEPENDENCIES: None

                Copyright (c) 2012-2016 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/sleep2.0/src/solver/lpr_solver.c#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include "comdef.h"
#include "CoreVerify.h"
#include "CoreTime.h"
#include "sleep_log.h"
#include "SleepLPR_synth_modes.h"
#include "lpr_solver.h"
#include "synthLPR.h"
#include "synthRegistry.h"

/*==============================================================================
                            INTERNAL FUNCTIONS
 =============================================================================*/
/**
 * sleepLPRSolver_findElement
 *
 * @brief This function finds the lookup table element that 
 *        contains a duration range that satisfies the sleep
 *        duration passed in, and returns a pointer to that
 *        element.  This function can be optimized/modified
 *        independently of the main solver function.
 *
 * @param modeDuration:    Normal mode sleep duration to find the lookup 
 *                         table element for.
 *  
 * @param freqLutIdx:      Frequency table index based on
 *                         current core frequency 
 * 
 * @param lutEntryIdx[out]:Index to the lookup table element which
 *                         was return. Valid only if lookup table
 *                         element was non null else -1.
 *  
 * @return Pointer to the lookup table element whose duration 
 *         range contains the sleep duration passed in.
 */
static sleep_mLUT_elem *sleepLPRSolver_findElement(uint64 modeDuration,
                                                   uint32 freqLutIdx,
                                                   int32  *lutElementIdx)
{
  /* Keep track of the most recently used duration.  This should help
   * with the case where the same duration range is hit over and over
   * again. */
  sleep_mLUT_elem   *mruMode, *lastMode, *compMruMode;
  sleep_mLUT        *modeLUT;
  int32             endIdx        = 0;
  static int32      mruModeIndex  = 0;
  static sleep_mLUT *mruLut       = NULL;

  CORE_VERIFY_PTR(lutElementIdx);

  /* Get correct LUT for the given frequency */
  modeLUT   = SleepLPR_power_lookup_table[freqLutIdx];
  mruMode   = &modeLUT->element[mruModeIndex];
  lastMode  = &modeLUT->element[modeLUT->num_elements - 1];

  /* Set comparison mode to one idx lower (higher duration) */
  if(mruModeIndex == 0)
  {
    compMruMode = mruMode;
  }
  else
  {
    compMruMode = &modeLUT->element[mruModeIndex - 1];
  }

  /* Check the last recently used entry for a match. */
  if(modeLUT == mruLut)
  {
    /* If given duration > most recently used duration and most recent duration
     * is max or given duration is <= next higher duration */
    if((modeDuration >= mruMode->duration_thresh) &&
       ((mruModeIndex == 0) || (modeDuration < compMruMode->duration_thresh)))
    {
      /* Found a match */
      *lutElementIdx = mruModeIndex;
      sleepStats_updateValue(&mruMode->element_stats, modeDuration);
      return mruMode;
    }
    /* Check for not enough time for any mode */
    else if(modeDuration < lastMode->duration_thresh)
    {
      return NULL;
    }
  }
  else
  {
    /* Running at different frequency from last cached value (different LUT ptr)
     *  - Need to update cache values */
    mruLut    = modeLUT;
    lastMode  = &modeLUT->element[modeLUT->num_elements - 1];
  }
  
  mruModeIndex  = modeLUT->num_elements / 2;
  mruMode       = &modeLUT->element[mruModeIndex];

  /* Check for not enough time for any mode in new frequency table */
  if(modeDuration < lastMode->duration_thresh)
  {
    return NULL;
  }

  /* Use the MRU info to determine which half of lookup table to traverse.
   * The search will start at index 0 or current index + 1 and increment until 
   * it finds the correct entry or errors. */
  if(modeDuration >= mruMode->duration_thresh )
  {
    endIdx       = mruModeIndex + 1;
    mruModeIndex = 0;
  }
  else
  {
    mruModeIndex++;
    endIdx = modeLUT->num_elements;
  }

  /* Traverse the rest of the table to find the duration that matches. */
  for(; mruModeIndex < endIdx; mruModeIndex++)
  {
    if(modeDuration >= modeLUT->element[mruModeIndex].duration_thresh)
    {
      /* Found it, return this element. */
      *lutElementIdx = mruModeIndex;
      sleepStats_updateValue(&modeLUT->element[mruModeIndex].element_stats, 
                             modeDuration);
      return(&modeLUT->element[mruModeIndex]);
    }
  }

  /* We should never make it this far. If we do, some logic failed above that 
   * should have caught the case were there is not enough time to do any modes. */
   sleepLog_printf(SLEEP_LOG_LEVEL_ATS, 2*1, 
                   "Invalid duration (Value: 0x%llx)", 
                   ULOG64_DATA(modeDuration));

  CORE_VERIFY(0);
  return NULL;
}

/** 
 * sleepLPRSolver_setThresholdDeadline 
 * 
 * @brief This function outputs threshold deadline when the mode selected by
 *        lookup table solver may no longer be optimal. 
 *
 * @param duration_thresh : Lookup table element duration threshold value
 * @param refDeadline     : Reference hard wakeup deadline
 *
 * @note This is meant to be an internal function and assumes valid input
 *       parameters. If that changes, we may need to verify them.
 */
static uint64 sleepLPRSolver_setThresholdDeadline(uint64 duration_thresh,
                                                  uint64 refDeadline)
{
  /* Setting the threshold deadline. */
  CORE_VERIFY(refDeadline > duration_thresh);
  return(refDeadline - duration_thresh);
}

/**
 * sleepLPRSolver_initialize
 *
 * @brief Init function for the lookup table solver.  This 
 *        function populates the mode_to_enter field in the
 *        lookup table, per the synthLPRM's registered.
 *
 * @return Returns non-zero on error.
 */
uint32 sleepLPRSolver_initialize(void)
{
  synthRegistry *registry;
  uint32        freqIdx, durIdx, modeIdx;
  uint32        mode_index;

  registry = synthRegistry_getRegistry();

  /* There will always be at least 1 table */
  for(freqIdx = 0; freqIdx < SLEEP_NUM_STATIC_FREQ; freqIdx++)
  {
    sleep_mLUT *pTable = SleepLPR_power_lookup_table[freqIdx]; 

    for(durIdx = 0; durIdx < pTable->num_elements; durIdx++)
    {
      pTable->element[durIdx].element_stats.min = UINT64_MAX;

      for( modeIdx = 0; modeIdx < SLEEP_LPR_NUM_SYNTHESIZED_MODES; modeIdx++)
      {
        if(-1 == pTable->element[durIdx].mode[modeIdx].mode_idx) 
        {
          pTable->element[durIdx].mode[modeIdx].mode_ptr = NULL; 
        }
        else
        {
          mode_index = pTable->element[durIdx].mode[modeIdx].mode_idx;
          pTable->element[durIdx].mode[modeIdx].mode_ptr = &registry->LPR->modes[mode_index];
        }
      }
    }
  }

  return 0;
}

/*
 * sleepLUTSolver_mainFunction
 */
solver_status sleepLPRSolver_mainFunction(sleep_solver_input  *input,
                                          sleep_solver_output *output)
{
  int32             i;
  int32             lutEntryIdx;        /* Index of chosen entry in LUT */
  uint64            modeDuration;
  uint64            softDeadline;
  uint64            currentTime;
  uint64            minHardDuration;
  uint32            latencyBudget;
  uint32            modeEnterExitLat  = 0;
  sleep_synth_lprm  *modeChosen       = NULL;
  sleep_mLUT_elem   *lookupElement    = NULL;
  sleep_fLUT_node   *fLUT             = input->fLUT;
  
  if(SLEEP_ENABLED == synthRegistry_getStatus(REGISTRY_TYPE_LPR))
  {
    /* Use the smallest of the latency restrictions */
    latencyBudget = MIN(input->normal_latency_budget, input->island_latency_budget);

    /* Get current time to be used for determination of
     * soft deadline and hard duration */
    currentTime = CoreTimetick_Get64();

    /* Verify deadline hasn't already past */
    if(input->hard_deadlines.overall_min <= currentTime)
    {
      sleepLog_printf(SLEEP_LOG_LEVEL_INFO, 0 + (1 * 2), 
                      " LPR Solver bypass "
                      "(Hard Deadline in past: 0x%llx)",
                      ULOG64_DATA(input->hard_deadlines.overall_min));

      return SOLVER_DEADLINE_IN_PAST;
    }

    /* Compute the soft deadline from the duration */
    softDeadline = currentTime + input->soft_duration;  

    /* Calculate hard duration from first hard deadline */
    minHardDuration = input->hard_deadlines.overall_min - currentTime;

    /* Check if soft deadline expires before the hard deadline and use that if it does */
    if(input->hard_deadlines.overall_min < softDeadline)
    {
      output->ref_deadline  = input->hard_deadlines.overall_min;
      modeDuration          = minHardDuration;
    }
    else
    {
     /* Use the hard deadline as the reference because setting a threshold timer based on the
      * soft duration does not acomplish solving for any different mode */
      output->ref_deadline  = input->hard_deadlines.overall_min;
      modeDuration          = input->soft_duration;
    }
  
    sleepLog_printf(SLEEP_LOG_LEVEL_INFO, 1 + (1 * 2), 
                    " LPR Solver (Min Duration: 0x%llx) "
                    "(Min latency budget: 0x%x)",
                    ULOG64_DATA(minHardDuration),
                    latencyBudget);
    
    /* Find the lookup table entry for this duration. */
    lookupElement = sleepLPRSolver_findElement(modeDuration, fLUT->mLUT_idx, &lutEntryIdx);

    if(lookupElement != NULL)
    {
      sleepLog_printf( SLEEP_LOG_LEVEL_INFO, 3,
                       " LPR table (mLUT: %d) (Duration: %lld)",
                       fLUT->mLUT_idx,
                       ULOG64_DATA(lookupElement->duration_thresh));

      /* Set the threshold deadline which is based off the row element in the LUT */
      output->threshold_deadline = sleepLPRSolver_setThresholdDeadline(lookupElement->duration_thresh, 
                                                                       output->ref_deadline);

      /* Traverse the modes for the duration range found, and find the one
       * that fits the current criteria. */
      for( i = 0; i < SLEEP_LPR_NUM_SYNTHESIZED_MODES; i++ )
      {
        modeChosen = lookupElement->mode[i].mode_ptr;

        /* If we hit a NULL mode, then we've reached the end of the mode list,
         * and didn't find a mode to enter. */
        if( NULL == modeChosen )
        {
          break;
        }

        /* Skip if mode is disabled */
        if( SLEEP_DISABLED == modeChosen->mode_status ) 
        {
          continue;
        }

        modeEnterExitLat = synthLPRM_getLatency( modeChosen, fLUT->mLUT_idx);

        /* Verify the mode does not violate the latency budget */
        if(modeEnterExitLat > latencyBudget)
        {
          sleepLog_printf( SLEEP_LOG_LEVEL_INFO, 3,
                           " Mode skipped (name: \"%s\") "
                           "(reason: \"Insufficient Time\") "
                           "(Synth latency: 0x%x) "
                           "(Latency budget: 0x%08x)",
                           modeChosen->name, 
                           modeEnterExitLat,
                           latencyBudget);
          continue;
        }

        /* If we made it this far, then solver was able to select a mode */
        output->selected_synthLPRM = modeChosen;

        sleepLog_QDSSPrintf( SLEEP_LOG_LEVEL_ATS, 
                             SLEEP_SOLVER_MODE_CHOSEN_NUM_ARGS,
                             SLEEP_SOLVER_MODE_CHOSEN_STR, 
                             SLEEP_SOLVER_MODE_CHOSEN,
                             modeChosen->name,
                             ULOG64_DATA( output->ref_deadline),
                             ULOG64_DATA( output->threshold_deadline ) );

        /* Prepare the data to return. */
        output->backoff_ptr     = synthLPRM_getBackOffTime(modeChosen, fLUT);
        output->enter_exit_time = modeEnterExitLat;
        return SOLVER_SUCCESS;
      }
    }
  }
  else
  {
    sleepLog_printf(SLEEP_LOG_LEVEL_ATS, 0, 
                    " LPR Registry Disabled");
  }

  return SOLVER_NO_MODE_CHOSEN;
}

