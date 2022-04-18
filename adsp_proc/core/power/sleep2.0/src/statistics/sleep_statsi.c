/*==============================================================================
  FILE:         sleep_statsi.c
  
  OVERVIEW:     Contains internal variables and functions for the implementation 
                of sleep mode statistics and dynamic latency adjustments

  DEPENDENCIES: None

                Copyright (c) 2013-2016 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/sleep2.0/src/statistics/sleep_statsi.c#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include <stdint.h>
#include <stdlib.h>
#include "comdef.h"
#include "sleep.h"
#include "CoreMutex.h"
#include "synthLPRM.h"
#include "sleep_stats.h"
#include "sleep_statsi.h"
#include "sleep_stats_global.h"
#include "CoreVerify.h"
#include "sleep_log.h"
#include "sleep_target.h"
#include "synthRegistry.h"
#include "sleep_utils.h"
#include "sleep_qr.h"
#include "lpr_solver.h"
#include "rpm_messageram.h"

/*==============================================================================
                             GLOBAL VARIABLES
 =============================================================================*/
sleepStats_postedData   g_sleepStatsPostedData;

/* =============================================================================
                          GLOBAL EXTERNAL VARIABLES
   ===========================================================================*/
extern sleepStats_power_collapse_time g_sleepTotalPowerCollapseTime;
extern volatile rpm_master_stats_t *g_sleepStatsRPM;

/*==============================================================================
                      INTERNAL VARIABLE DECLARATIONS
 =============================================================================*/
/* Head pointer for sleep frequency lookup tables */
static sleep_fLUT_node  *g_sleepFLUT = NULL;

/* Used to controll access to the mail fLUT list */
static CoreMutexType    *g_sleepfLUTMutex = NULL;

/* Static FLUT array to use for adding elements first before using dynamic
 * memory in the heap */
#if defined(SLEEP_NUM_STATIC_FLUTS) && (SLEEP_NUM_STATIC_FLUTS > 0)
static sleep_fLUT_node  g_staticFlutArray[SLEEP_NUM_STATIC_FLUTS];
#endif

/*==============================================================================
                       INTERNAL FUNCTION DEFINITIONS
 =============================================================================*/
/*
 * sleepStats_init
 */
void sleepStats_init(void)
{
#if defined(SLEEP_NUM_STATIC_FLUTS) && (SLEEP_NUM_STATIC_FLUTS > 0)
  /* Clear static array memory */
  memset(g_staticFlutArray, 0, sizeof(g_staticFlutArray));
#endif

  /* Get RPM statistics memory area pointer */
  g_sleepStatsRPM = (volatile rpm_master_stats_t *)sleepTarget_getRPMStatisticsAddress();

  /* Setup the fLUT data lock */
  CORE_VERIFY_PTR(g_sleepfLUTMutex = Core_MutexCreate(CORE_MUTEXATTR_DEFAULT));

  return;
}

/*
 * sleepStats_initSynth
 */
static void sleepStats_initSynth(synth_dyn_data *synth)
{
#ifdef SLEEP_ENABLE_AUTO_SYNTH_BACKOFF_ADJUSTMENT
  uint32              nMode;
  synth_LPRM_dyn_data *synthData = synth->LPRM;

  for(nMode = 0; nMode < SLEEP_LPR_NUM_SYNTHESIZED_MODES; nMode++)
  {
    synthData[nMode].adjust_cnt       = SLEEPSTATS_INITIAL_CYCLE_COUNT;
    synthData[nMode].wakeup_stats.min = INT64_MAX;
    synthData[nMode].wakeup_stats.max = INT64_MIN;
  }
#endif

  /* Nothing to do for synth LPR */

  return;
}

/*
 * sleepStats_initDynamicData
 */
void sleepStats_initDynamicData(sleepStats_dynamic_data *data)
{
  /* New data has already been set to '0' so only non-zero values need to be
   * set */
  sleepStats_initSynth(&data->synth);

  sleepQR_initElement(data);

  return;
}

#ifdef SLEEP_ENABLE_AUTO_SYNTH_BACKOFF_ADJUSTMENT
/*
 * sleepStats_resetSynth
 */
void sleepStats_resetSynth(synth_LPRM_dyn_data *synth)
{
  synth->wakeup_stats.min    = INT64_MAX;
  synth->wakeup_stats.max    = INT64_MIN;
  synth->wakeup_stats.total  = 0;
  synth->wakeup_stats.count  = 0;

  sleepQR_reset(&synth->QR_data);
  return;
}

/*
 * sleepStats_verifyBackoffRange
 */
void sleepStats_verifyBackoffRange(uint32 currentBackoff,
                                   int32  newBackoff, 
                                   uint32 enterExitLatency)
{
  /* Minimum and maximum allowable backoff based on the current value */
  uint32 maxBackoff = currentBackoff * SLEEPSTATS_VALID_BACKOFF_MAX_FACTOR;
  uint32 minBackoff = currentBackoff / SLEEPSTATS_VALID_BACKOFF_MIN_FACTOR;

  /* Make sure new latency value is something reasonable:
   *  - Between min & max allowed (either error or print warning)
   *  - Less than than enter + exit latency */ 
  if(newBackoff < enterExitLatency)
  {
    if((newBackoff < minBackoff) || (newBackoff > maxBackoff))
    {
      sleepLog_printf(SLEEP_LOG_LEVEL_AUTO_LATENCY, 5,
                      " WARNING: New backoff out of range "
                      "(Current: %u) (New: %u) "
                      "(Min: %d) "
                      "(Enter+Exit: %u) "
                      "(Max %d)",
                      currentBackoff,
                      newBackoff,
                      minBackoff,
                      enterExitLatency, 
                      maxBackoff);

#if (0 != SLEEP_BACKOFF_ADJUST_CRASH_OUT_OF_RANGE)
      CORE_VERIFY(0);
#endif
    }
  }
  else
  {
    CORE_LOG_VERIFY(0, 
                    sleepLog_printf(SLEEP_LOG_LEVEL_AUTO_LATENCY, 5,
                                    " ERROR: New backoff exceeds enter + exit latency " 
                                    "(Current: %u) (New: %u) "
                                    "(Min: %d) "
                                    "(Enter+Exit: %u) "
                                    "(Max %d)",
                                    currentBackoff,
                                    newBackoff,
                                    minBackoff,
                                    enterExitLatency, 
                                    maxBackoff));
  }

  return;
}

/*
 * sleepStats_adjustSynthmode
 */
void sleepStats_adjustSynthmode(sleepStats_input *statInput,
                                int64            wakeupDelta,
                                int64            wakeupAdjust)
{
  synth_LPRM_dyn_data       *dynamicLPRM;
  uint32                    *adjustCnt;
  sleepStats_generic_signed *synthLPRMStats;
  uint32                    *currentBackoff;
  sleep_fLUT_node           *fLUT   = statInput->fLUT;
  uint32                    dynNum  = statInput->mode->dynamic_num;
  
  dynamicLPRM     = &fLUT->dynamic_data.synth.LPRM[dynNum];
  adjustCnt       = &dynamicLPRM->adjust_cnt;
  synthLPRMStats  = &dynamicLPRM->wakeup_stats;
  currentBackoff  = &dynamicLPRM->backoff;

  /* Remove any wakeup latency errors so only the masters local latency is
   * adjusted */
  wakeupDelta -= wakeupAdjust;

  /* Ensure a single delta adjustment would not create a negative backoff.
   * If it would, log a message and force a crash here to catch this situation. */
  CORE_LOG_VERIFY((((int64)(*currentBackoff) + wakeupDelta) > 0),
                  sleepLog_printf(SLEEP_LOG_LEVEL_AUTO_LATENCY, 1 + (2 * 2),
                                  " ERROR: Bad wakeup delta "
                                  "(Wakeup Delta: %lld) "
                                  "(Wakeup Error: %lld) "
                                  "(Current Backoff: %d) ",
                                  ULOG64_DATA(wakeupDelta),
                                  ULOG64_DATA(wakeupAdjust),
                                  *currentBackoff));
  
  /* Record wakeup statistics */
  sleepStats_updateSignedValue(synthLPRMStats, wakeupDelta);

  /* Checks if the last sleep cycle requires a Quick Response */
  sleepQR_perform(statInput->mode, fLUT, (int32)wakeupDelta);

  /* Adjust synth mode latency if it's time to do so */
  if(synthLPRMStats->count >= *adjustCnt)
  {
    int64   actualAvg;
    int64   adjustedTotal   = synthLPRMStats->total;
    int64   avgCount        = (int64)(synthLPRMStats->count);
    
    if(avgCount > 2)
    {
      /* Remove worst to cases from average*/
      adjustedTotal = adjustedTotal - synthLPRMStats->min - synthLPRMStats->max;
      avgCount -= 2;
    }

    /* Compute average synth mode exit time */
    actualAvg = adjustedTotal / avgCount;

    sleepLog_QDSSPrintf(SLEEP_LOG_LEVEL_AUTO_LATENCY, 
                        SLEEP_BKOFF_STATS_NUM_ARGS,
                        SLEEP_BKOFF_STATS_STR, 
                        SLEEP_BKOFF_STATS,
                        statInput->mode->name,
                        fLUT->frequency,
                        safe_signed_truncate(synthLPRMStats->min),
                        safe_signed_truncate(synthLPRMStats->max),
                        ULOG64_DATA(synthLPRMStats->total),
                        synthLPRMStats->count,
                        safe_signed_truncate(actualAvg));

    /* Sanity checking */
    if((actualAvg > INT32_MIN) && (actualAvg < INT32_MAX))
    {
      /* Want to keep synth mode slightly early to provide a little buffer */ 
      if((actualAvg < -250) || (actualAvg > -50)) 
      {
        int32   adjustment;
        int32   newBackoff;
        uint32  seedEnterExitLatency;

#ifdef SLEEP_ENABLE_FREQUENCY_SCALING
        seedEnterExitLatency = statInput->mode->seed_latency->enter_exit[statInput->fLUT->mLUT_idx];
#else
        seedEnterExitLatency = statInput->mode->seed_latency->enter_exit[0];
#endif

        adjustment = (int32)(actualAvg + 150);
        newBackoff = (int32)(*currentBackoff) + adjustment;
        
        /* Validate the new backoff and take the appropriate action */
        sleepStats_verifyBackoffRange(*currentBackoff, (uint32)newBackoff, 
                                      seedEnterExitLatency);

        sleepLog_printf(SLEEP_LOG_LEVEL_AUTO_LATENCY, 3 + (1 * 2),
                        " Adjusting (Wakeup Error: %lld) "
                        "(Current Backoff: %d) (Adjustment: %d) "
                        "(New Backoff: %d)",
                        ULOG64_DATA(wakeupAdjust),
                        *currentBackoff,
                        adjustment,
                        newBackoff);

        /* Set new backoff value */
        *currentBackoff = (uint32)newBackoff;
      }
      else
      {
        sleepLog_printf(SLEEP_LOG_LEVEL_AUTO_LATENCY, 2,
                        " No adjustment needed (Current: %d) (avg: %d)",
                        *currentBackoff,
                        safe_signed_truncate(actualAvg));
      }

      /* Increase next adjust time but limit to maximum number of cycles  */
      if(*adjustCnt < SLEEPSTATS_FINAL_CYCLE_COUNT)
      {
        /* Shift the adjustment counter for the next group average */
        *adjustCnt = ((*adjustCnt) << 1);

        /* Reset & determine component backoff after a certain number of
         * auto-backoff adjustments */
        if((*adjustCnt == (SLEEPSTATS_INITIAL_CYCLE_COUNT << 1)) ||
           (*adjustCnt == (SLEEPSTATS_INITIAL_CYCLE_COUNT << 4)) ||
           (*adjustCnt >= SLEEPSTATS_FINAL_CYCLE_COUNT)
          )
        {
          sleepQR_resetComponents(statInput->mode, fLUT);

          /* If the synthmode has finished it's adjustment cycles, the 
           * system has settled enough and we don't need to monitor component QR 
           * data anymore. */ 
          if(*adjustCnt >= SLEEPSTATS_FINAL_CYCLE_COUNT)
          {
            sleepQR_clearComponentMonitoring(statInput->mode, &fLUT->dynamic_data);
          }
        }
      }
    }
    else
    {
      sleepLog_printf( SLEEP_LOG_LEVEL_AUTO_LATENCY, 0,
                       " Adjustment failed sanity check");
    }

    /* reset min/max stats for next run */
    sleepStats_resetSynth(dynamicLPRM);
  }

  return;
}
#endif /* SLEEP_ENABLE_AUTO_SYNTH_BACKOFF_ADJUSTMENT */

/*
 * sleepStats_logWakeup
 */
void sleepStats_logWakeup(sleepStats_input *statInput)
{
  int64                       wakeupDelta;
  int64                       wakeupAdjust;
  const char                  *wakeupReason;
  volatile rpm_master_stats_t *rpmStats;
  boolean                     isRPMAssisted   = FALSE;
  uint64                      sleepResumeTime = sleepStats_getLprTimeData(SLEEP_STATS_TIME_MSTR_RETURN_TYPE);

  CORE_VERIFY_PTR(rpmStats = sleepStats_getRpmDataPtr());

  switch(statInput->master_wakeup_reason)
  {
    case SLEEP_STATS_WAKEUP_RPM_SCHEDULED:
    {
      isRPMAssisted = TRUE;
    }

    case SLEEP_STATS_WAKEUP_SA_SCHEDULED:
    {
      wakeupReason = "Timer";
      break;
    }

    case SLEEP_STATS_WAKEUP_RPM_UNSCHEDULED:
    {
      isRPMAssisted = TRUE;
    }

    case SLEEP_STATS_WAKEUP_SA_UNSCHEDULED:
    {
      wakeupReason = "Rude";
      break;
    }

    case SLEEP_STATS_WAKEUP_RPM_UNKNOWN:
    {
      isRPMAssisted = TRUE;
    }

    default:
    {
      wakeupReason = "Unknown";
    }
  }

  /* Get inaccuracy in the master wakeup so only the local latency
   * is adjusted later */
  if( statInput->actual_wakeup_time >= statInput->backoff_deadline )
  {
    /* RPM or idle timer woke up the master late */
    wakeupAdjust = (int64)(statInput->actual_wakeup_time - 
                           statInput->backoff_deadline); 
  }
  else
  {
    /* RPM or idle timer woke up the master early */
    wakeupAdjust = -((int64)(statInput->backoff_deadline - 
                             statInput->actual_wakeup_time));
  }
  
  if(statInput->os_overhead.count > 0)
  {
    /* Log OS bringup times */
    sleepLog_printf(SLEEP_LOG_LEVEL_PROFILING, 2 + (3*2),
                    "Warmboot stats (Count: %d) "
                    "(Power collapse: 0x%llx) (Core resume: 0x%llx) "
                    "(Sleep resume: 0x%llx) "
                    "(WB time: %duS)" ,
                    statInput->os_overhead.count,
                    ULOG64_DATA(statInput->os_overhead.sleep_time),
                    ULOG64_DATA(statInput->os_overhead.awake_time),
                    ULOG64_DATA(sleepResumeTime),
                    TICKS_TO_US(sleepResumeTime - statInput->os_overhead.awake_time));
  }

  if(isRPMAssisted == TRUE)
  {
    /* Log RPM bringup info */
    sleepLog_printf( SLEEP_LOG_LEVEL_PROFILING, 2 + (3*2),
                     "RPM stats (wakeup_ind: 0x%llx) (bringup_req: 0x%llx) "
                     "(bringup_ack: 0x%llx) (sleep trans time: %d) "
                     "(wake trans time: %d)",
                     ULOG64_DATA(rpmStats->wakeup_ind),
                     ULOG64_DATA(rpmStats->bringup_req),
                     ULOG64_DATA(rpmStats->bringup_ack),
                     rpmStats->last_sleep_transition_duration,
                     rpmStats->last_wake_transition_duration );
  }
  
  /* Log master wakeup */
  sleepLog_QDSSPrintf( SLEEP_LOG_LEVEL_INFO, SLEEP_WAKEUP_NUM_ARGS,
                       SLEEP_WAKEUP_STR, SLEEP_WAKEUP, 
                       wakeupReason, 
                       statInput->master_interrupt,
                       ULOG64_DATA(statInput->actual_wakeup_time),
                       ULOG64_DATA(statInput->backoff_deadline),
                       ULOG64_DATA(wakeupAdjust) ); 

  /* Log late sleep exits */
  if( statInput->sleep_exit_stm > statInput->hard_deadline )
  {
    /* Get difference of sleep exit time to expected exit */
    wakeupDelta = statInput->sleep_exit_stm - statInput->hard_deadline;
    
    sleepLog_printf( SLEEP_LOG_LEVEL_WARNING, 4*2,
                     "WARNING (message: \"Late sleep exit\") "
                     "(Actual: 0x%llx) (Expected: 0x%llx) "
                     "(diff ticks: %lld) (diff us: %lld)",
                     ULOG64_DATA(statInput->sleep_exit_stm), 
                     ULOG64_DATA(statInput->hard_deadline),
                     ULOG64_DATA(wakeupDelta),
                     ULOG64_DATA(TICKS_TO_US(wakeupDelta)));
  }
#ifdef SLEEP_ENABLE_AUTO_SYNTH_BACKOFF_ADJUSTMENT
  else
  {
    /* Early wake ups are negative values */
    wakeupDelta = -(statInput->hard_deadline - statInput->sleep_exit_stm);
  }

  /* Record stats and make any adjustments only for scheduled PC modes.
   * Since we don't have an accurate wakeup time for
   * unscheduled modes, we're unable to adjust latencies for those modes */
  if(SLEEP_STATS_WAKEUP_RPM_SCHEDULED == statInput->master_wakeup_reason ||
     SLEEP_STATS_WAKEUP_SA_SCHEDULED  == statInput->master_wakeup_reason)
  {
    sleepStats_adjustSynthmode(statInput, wakeupDelta, wakeupAdjust);
  }

#endif /* SLEEP_ENABLE_AUTO_SYNTH_BACKOFF_ADJUSTMENT */

  return;
}

/*
 * sleepStats_getLastLprLatency
 */
uint32 sleepStats_getLastLprLatency(sleepStats_latency_type type)
{
  uint32 tempVal;

  CORE_VERIFY(type < SLEEP_STATS_NUM_LATENCY_TYPE);

  tempVal = g_sleepStatsPostedData.latency[type];

  /* Verify an LPR put a valid value */
  CORE_VERIFY(tempVal != 0);
  g_sleepStatsPostedData.latency[type] = 0;

  return(tempVal);
}

/*
 * sleepStats_getLprTimeData
 */
uint64 sleepStats_getLprTimeData(sleepStats_timedata_type type)
{
  uint64 tempVal;

  CORE_VERIFY(type < SLEEP_STATS_NUM_TIMEDATA_TYPE);

  tempVal = g_sleepStatsPostedData.time[type];
  
  return(tempVal);
}

/*
 * sleepStats_getMiscData
 */
uint32 sleepStats_getMiscData(sleepStats_misc_type type)
{
  CORE_VERIFY(type < SLEEP_STATS_NUM_MISC_TYPE);
  return(g_sleepStatsPostedData.misc_32bit[type]);
}

/*
 * sleepStats_getTableEntry
 */
boolean sleepStats_getTableEntry(uint32           freq,
                                 sleep_fLUT_node  **fLUT)
{
  static sleep_fLUT_node *cachedEntry = NULL;
  
  sleep_fLUT_node *freqTable;
  sleep_fLUT_node *workingCachePtr;
  sleep_fLUT_node *closest;
  boolean         rtnCode   = TRUE;
  
  freqTable       = g_sleepFLUT;
  workingCachePtr = cachedEntry;
  closest         = freqTable;

  /* Set initial returned LUT to cached LUT */
  *fLUT = workingCachePtr;

  /* Only scan tables if given frequency is different from cached value */
  if(workingCachePtr == 0 || (freq != workingCachePtr->frequency))
  {
    while(freqTable != NULL)
    {
      /* Check if we already have a frequency entry in the table */
      if(freq == freqTable->frequency)
      {
        /* update cache pointer */
        *fLUT       = freqTable;
        cachedEntry = freqTable;
        return (TRUE);
      }

      /* Remember closest (but less than) entry */
      if(freqTable->frequency < freq)
      {
        closest = freqTable;
      }

      /* Check next entry */
      freqTable = freqTable->next;
    };

    /* At this point, a new entry needs to be added
     * Set the frequency LUT to the closest entry and return that new elements
     * need to be added.
     */
    *fLUT   = closest;
    rtnCode = FALSE;
  }

  return(rtnCode);
}

/**
 * sleepStats_initializeBackoffValues
 *
 * @brief Initializes a new synth backoff value using the given seed values or 
 *        the value of the closest frequency 
 *
 * @param newTable:    Pointer to newly created fLUT 
 * @param closestFlut: Pointer to closes fLUT, can be NULL if none exist
 */
static void sleepStats_initializeBackoffValues
(
    sleep_fLUT_node *newTable,
    sleep_fLUT_node *closestFlut
)
{
  uint32              nMode;
  synth_LPRM_dyn_data *newDynSynth;
  synthRegistry       *synthRegistry = synthRegistry_getRegistry();

  CORE_VERIFY_PTR(synthRegistry);

  newDynSynth = newTable->dynamic_data.synth.LPRM;

  for(nMode = 0; nMode < SLEEP_LPR_NUM_SYNTHESIZED_MODES; nMode++)
  {
    /* If backoff feature is enabled, then use the closest frequency
     *  - If the closest fLUT is NULL, this is the first entry, so use
     *    initial (only) seed value generated from SleepSynth
     *  - If the closest fLUT is value, use it's data 
     */
#ifdef SLEEP_ENABLE_AUTO_SYNTH_BACKOFF_ADJUSTMENT
    if(NULL == closestFlut)
    {
      newDynSynth[nMode].backoff = 
        synthRegistry->LPR->modes[nMode].seed_latency->backoff[0];
    }
    else
    {
      newDynSynth[nMode].backoff = 
        closestFlut->dynamic_data.synth.LPRM[nMode].backoff;
    }
#else
    /* If backoff feature is disabled, use seed values:
     *  - If scaling feature is enabled, use closest seed value    
     *  - If scaling feature is diabled, use only available seed value
     */
 #ifdef SLEEP_ENABLE_FREQUENCY_SCALING
    newDynSynth[nMode].backoff =
      synthRegistry->LPR->modes[nMode].seed_latency->backoff[newTable->mLUT_idx]; 
 #else
    newDynSynth[nMode].backoff = 
      synthRegistry->LPR->modes[nMode].seed_latency->backoff[0]; 
 #endif

#endif /*SLEEP_ENABLE_AUTO_SYNTH_BACKOFF_ADJUSTMENT*/
  }
  return;
}

/*
 * sleepStats_addFrequencyTable
 */
sleep_fLUT_node* sleepStats_addFrequencyTable(sleep_fLUT_node *closestFlut,
                                              uint32          curFreq)
{
  sleep_fLUT_node *newTable = NULL;

#if defined(SLEEP_NUM_STATIC_FLUTS) && (SLEEP_NUM_STATIC_FLUTS > 0)
  static uint32   lastStaticIdx = 0;
#endif

  /* Find or create a free element to add the new frequency to */
#if defined(SLEEP_NUM_STATIC_FLUTS) && (SLEEP_NUM_STATIC_FLUTS > 0)
  if(lastStaticIdx < SLEEP_NUM_STATIC_FLUTS)
  {
    /* Still room in the static array, point to the next free element */
    newTable = &g_staticFlutArray[lastStaticIdx];
    lastStaticIdx++;
  }
  else
#endif
  {
    /* Allocate new fLUT element */
    CORE_VERIFY_PTR(newTable = calloc(1, sizeof(sleep_fLUT_node)));
  }

  CORE_VERIFY(curFreq > 0);
  newTable->frequency = curFreq;

#ifdef SLEEP_ENABLE_FREQUENCY_SCALING
  /* Find closest mLUT
   * If scaling feature is disabled, there is only on 1 mLUT so no need to search
   * Note that SLEEP_NUM_STATIC_FREQ will always be at least 1 */
  for(newTable->mLUT_idx = 1; 
       newTable->mLUT_idx < SLEEP_NUM_STATIC_FREQ; 
       newTable->mLUT_idx++)
  {
    if(curFreq < SleepLPR_static_freq_list[newTable->mLUT_idx])
    {
      break;
    }
  }

  /* Subtract one due to logic of finding closest, but less than frequency */
  newTable->mLUT_idx--;
#endif

  /* Initialize data & cache arrays for new frequency entry before adding to 
   * master list. */
  sleepStats_initDynamicData(&newTable->dynamic_data);
  sleepStats_initializeBackoffValues(newTable, closestFlut);

  sleepLog_printf(SLEEP_LOG_LEVEL_DEBUG, 2,
                  "Inserting new fLUT "
                  "(freq: %d) (mode_LUT_idx: %d)",
                  curFreq, newTable->mLUT_idx);

  /* Lock the master list while the new element is added */
  sleepStats_lockfLUTAccess();

  /* Verify that a closest frequency found, if not, initialize the head
   * fLUT pointer */
  if(closestFlut != NULL)
  {
    /* The closest frequency will be less than the current in all but one case
     * where it is the only (head) element.  In this case, the new element will
     * become the head. 
     */
    if(closestFlut->frequency > curFreq)
    {
      newTable->next  = closestFlut;
      g_sleepFLUT     = newTable;
    }
    else
    {
      /* Insert new element in frequency order which is after closest */
      newTable->next    = closestFlut->next;
      closestFlut->next = newTable;
    }
  }
  else
  {
    /* Set very first fLUT element */
    g_sleepFLUT = newTable;
  }

  /* New element was added, unlock access */
  sleepStats_unlockfLUTAccess();

  return newTable;
}

/*
 * sleepStats_lockfLUTAccess
 */
void sleepStats_lockfLUTAccess(void)
{
  Core_MutexLock(g_sleepfLUTMutex);
  return;
}

/*
 * sleepStats_unlockfLUTAccess
 */
void sleepStats_unlockfLUTAccess(void)
{
  Core_MutexUnlock(g_sleepfLUTMutex);
  return;
}

/*
 * sleepStats_updatePCTime
 */
void sleepStats_updatePCTime(void)
{
  uint64 sleepTime;
  uint64 wakeupTime;

  if(TRUE == g_sleepTotalPowerCollapseTime.tracking_enabled)
  {
    sleepTime   = sleepStats_getLprTimeData(SLEEP_STATS_TIME_MSTR_SHUTDOWN_TYPE);
    wakeupTime  = sleepStats_getLprTimeData(SLEEP_STATS_TIME_MSTR_RETURN_TYPE);

    /* Update stats */
    g_sleepTotalPowerCollapseTime.stats.last_mode_time = wakeupTime - sleepTime;

    g_sleepTotalPowerCollapseTime.stats.in_mode_time += 
      g_sleepTotalPowerCollapseTime.stats.last_mode_time;

    g_sleepTotalPowerCollapseTime.stats.mode_run_cycles++;
  }

  return;
}
