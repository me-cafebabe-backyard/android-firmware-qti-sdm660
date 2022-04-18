/*==============================================================================
  FILE:         synthLPRM.c
  
  OVERVIEW:     Provides the synth lprm functions
 
  DEPENDENCIES: None

                Copyright (c) 2013-2016 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/sleep2.0/src/synthesizer/synthLPRM.c#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include <stdlib.h>
#include "comdef.h"
#include "sleepi.h"
#include "sleep_statsi.h"
#include "sleep_lpri.h"
#include "synthLPRM.h"
#include "synthLPR.h"
#include "CoreAtomicOps.h"
#include "lookup_table_types.h"
#include "sleep_qr.h"

#ifdef USLEEP_ISLAND_MODE_ENABLE
#include "synthLPI.h"
#endif

/*==============================================================================
                           INTERNAL VARIABLES
 =============================================================================*/
static sleep_synth_lprm *g_sleepCurrentlyConfiguringMode = NULL;

/*==============================================================================
                           FUNCTION DEFINITIONS
 =============================================================================*/

/*
 * Helper function for synthLPRM_setupComponentModeParents
 */
static void setupComponentModeParents( sleep_synth_lprm *synthLPRM,
                                       sleep_lprm_group *group )
{
  uint32      i;
  uint32      newParentIdx;
  sleep_lprm  *sleepLPRM;
  void        *tmpPtr;
  uint32      numMode;
  sleep_lprm  **component_modes;

  CORE_VERIFY_PTR(group);

  numMode         = group->num_component_modes;
  component_modes = group->component_modes;

  for( i = 0; i < numMode; i++ )
  {
    sleepLPRM     = component_modes[i];
    newParentIdx  = sleepLPRM->synth_LPRM_parent_count++;

    CORE_VERIFY_PTR(tmpPtr = realloc(sleepLPRM->synth_LPRM_parent_array,
                                     sizeof(void *) * sleepLPRM->synth_LPRM_parent_count));

    sleepLPRM->synth_LPRM_parent_array = tmpPtr;

    /* Set the component mode's parent to this synthmode */
    sleepLPRM->synth_LPRM_parent_array[newParentIdx] = synthLPRM;
  }

  return;
}

/*
 * synthLPRM_setupComponentModeParents
 */
void synthLPRM_setupComponentModeParents( sleep_synth_lprm *synthLPRM )
{
  CORE_VERIFY_PTR(synthLPRM);

  setupComponentModeParents( synthLPRM, &synthLPRM->cacheable );
  setupComponentModeParents( synthLPRM, &synthLPRM->uncacheable );

  return;
}

/*
 * synthLPRM_initSynth
 */
void synthLPRM_initSynth(sleep_synth_lprm *synthLPRM)
{
  CORE_LOG_VERIFY_PTR( synthLPRM, sleepLog_printf(SLEEP_LOG_LEVEL_ERROR, 0,
                       "ERROR (message: \"NULL Synthesized LPRM\")" ) );

  /* Default is synthmode disabled */
  synthLPRM->mode_status = SLEEP_DISABLED;
  synthLPRM_setupComponentModeParents(synthLPRM);

  return;
}

/*
 * synthLPRM_getLatency
 */
uint32 synthLPRM_getLatency(sleep_synth_lprm  *synthLPRM,
                            uint32            mLUTidx)
{
  CORE_VERIFY_PTR(synthLPRM);
  CORE_VERIFY(mLUTidx < SLEEP_NUM_STATIC_FREQ);

  /* Since enter & exit latencies are not dynamically adjusted,
   * always return the appropriate seed value */
  return synthLPRM->seed_latency->enter_exit[mLUTidx];
}

/*
 * synthLPRM_getEnterLatency
 */
uint32 synthLPRM_getEnterLatency(sleep_synth_lprm  *synthLPRM,
                                 uint32            mLUTidx)
{
  CORE_VERIFY_PTR(synthLPRM);
  CORE_VERIFY(mLUTidx < SLEEP_NUM_STATIC_FREQ);

  /* Since enter latency is not dynamically adjusted,
   * always return the appropriate seed value */
  return synthLPRM->seed_latency->enter[mLUTidx];
}

/*
 * synthLPRM_getBackOffTime
 */
const uint32* synthLPRM_getBackOffTime(sleep_synth_lprm  *synthLPRM,
                                       sleep_fLUT_node   *fLUT)
{
  const uint32* backoffPtr = NULL;

#ifdef SLEEP_ENABLE_AUTO_SYNTH_BACKOFF_ADJUSTMENT
  uint32  dynIndex;

  CORE_VERIFY_PTR(synthLPRM);

  dynIndex = synthLPRM->dynamic_num;

  /* If the backoff adjustment feature is enabled, then get the backoff value
   * from the frequency dependant list */
  backoffPtr = &(fLUT->dynamic_data.synth.LPRM[dynIndex].backoff);

#else

  CORE_VERIFY_PTR(synthLPRM);
  /* If the backoff feature is disabled, then get the value from the initial
   * seed value(s) given */
  backoffPtr = &(synthLPRM->seed_latency->backoff[fLUT->mLUT_idx]);

#endif

  return backoffPtr;
}

/*
 * synthLPRM_isAttributeSet
 */
boolean synthLPRM_isAttributeSet(sleep_synth_lprm *synthLPRM, 
                                 uint32           attributes,
                                 boolean          requireAllSet)
{
  boolean rtnValue;
  
  if(TRUE == requireAllSet)
  {
    /* Check if all attributes are set */
    rtnValue = (attributes != (synthLPRM->attr & attributes)) ? FALSE : TRUE;
  }
  else
  {
    /* Check if any attribute is set */
    rtnValue = (0 == (synthLPRM->attr & attributes)) ? FALSE : TRUE;
  }

  return(rtnValue);
}

/*
 * synthLPRM_cachedModeEnter
 */
void synthLPRM_cachedModeEnter(sleep_synth_lprm *synthLPRM,
                               uint64            wakeupTick,
                               boolean           reenter)
{
  sleep_lprm  *component;
  uint32      nMode;
  uint32      numMode;
  uint32      isReentrant;
  sleep_lprm  **component_modes;
  
  CORE_VERIFY_PTR(synthLPRM);
  CORE_VERIFY(TRUE != sleepOS_isProcessorInSTM());

  synthLPRM->wakeup_tick = wakeupTick;

  /* Set the current mode being entered */
  g_sleepCurrentlyConfiguringMode = synthLPRM;

  /* Iterating through each component mode */
  numMode         = synthLPRM->cacheable.num_component_modes;
  component_modes = synthLPRM->cacheable.component_modes;

  for(nMode = 0; nMode < numMode; nMode++)
  {
    /* Calling the actual enter functions of the component modes */
    component   = component_modes[nMode];
    isReentrant = component->attributes & SLEEP_MODE_ATTR_MULTIPLE_ENTRY;

    /* If reentrant is false, call every component mode's enter function.
     * Otherwise, only call component mode's enter function if its REENTRANT
     * attribute is set.  */
    if((NULL != component->enter_func) && 
       ((FALSE == reenter) || (0 != isReentrant)))
    {
      sleepLog_QDSSPrintf(SLEEP_LOG_LEVEL_PROFILING, 
                          SLEEP_ATS_ENTER_MODE_NUM_ARGS,
                          SLEEP_ATS_ENTER_MODE_STR, 
                          SLEEP_ATS_ENTER_MODE,
                          (FALSE != reenter) ? "True" : "False",
                          component->parent_LPR->resource_name,
                          component->mode_name);
      
      component->enter_func(wakeupTick);
    }
  }

  return;
}

/*
 * synthLPRM_enter
 */
void synthLPRM_enter(sleep_synth_lprm  *synthLPRM, 
                     uint64            wakeupTick, 
                     sleep_fLUT_node   *fLUT)
{
  sleep_lprm  *component;
  uint32      i;
  uint64      LPRMTime   = CoreTimetick_Get64();
  uint32      numMode;
  sleep_lprm  **component_modes;
  
  CORE_VERIFY_PTR(synthLPRM);

  /* setup initial value */
  synthLPRM->wakeup_tick = wakeupTick;

  /* Set the current mode being entered */
  g_sleepCurrentlyConfiguringMode = synthLPRM;

  /* Iterating through each component mode */
  numMode         = synthLPRM->uncacheable.num_component_modes;
  component_modes = synthLPRM->uncacheable.component_modes;
  for(i = 0; i < numMode; i++)
  {
    /* Calling the actual enter functions of the component modes */
    component   = component_modes[i];

    /* Sleep statistics */
    component->parent_LPR->run_count++;                   /* Update LPR cycles*/
    component->mode_statistics.mode_run_cycles++;         /* Update LPRM cycles */
    component->mode_statistics.last_mode_time = LPRMTime; /* Recored LPRM enter time */

    /* Logging mode entry message */
    sleepLog_QDSSPrintf( SLEEP_LOG_LEVEL_PROFILING, 
                         SLEEP_ENTER_MODE_NUM_ARGS,
                         SLEEP_ENTER_MODE_STR, SLEEP_ENTER_MODE, 
                         component->parent_LPR->resource_name,
                         component->mode_name,
                         ULOG64_DATA(LPRMTime));

    /* Call the enter function with the latest sleep duration value */
    if(NULL != component->enter_func)
    {
      component->enter_func(synthLPRM->wakeup_tick);
    }

    /* Get the end of the current LPRM exit, and also use this as the
     * beginning of the next LPRM exit so that multiple calls to timetick
     * are avoided. */
    LPRMTime = CoreTimetick_Get64();
  }

  return;
}

/*
 * synthLPRM_cachedModeExit
 */
void synthLPRM_cachedModeExit(sleep_synth_lprm *synthLPRM)
{
  int         nMode;
  sleep_lprm  *component;
  uint32      numMode;
  sleep_lprm  **component_modes;
  
  CORE_VERIFY_PTR(synthLPRM);
  CORE_VERIFY(TRUE != sleepOS_isProcessorInSTM());

  /* Set the current mode being exited */
  g_sleepCurrentlyConfiguringMode = synthLPRM;

  numMode         = synthLPRM->cacheable.num_component_modes;
  component_modes = synthLPRM->cacheable.component_modes;
  for(nMode = numMode - 1; nMode >= 0; nMode--)
  {
    /* Calling the exit functions of the component modes */
    component = component_modes[nMode];
    
    /* Call LRPM exit function */
    if(NULL != component->exit_func)
    {
      sleepLog_QDSSPrintf(SLEEP_LOG_LEVEL_PROFILING, 
                          SLEEP_ATS_EXIT_MODE_NUM_ARGS,
                          SLEEP_ATS_EXIT_MODE_STR, 
                          SLEEP_ATS_EXIT_MODE, 
                          component->parent_LPR->resource_name,
                          component->mode_name);

      component->exit_func();
    }
  }

  return;
}

/*
 * synthLPRM_exit
 */
void synthLPRM_exit( sleep_synth_lprm *synthLPRM,
                     sleep_fLUT_node  *fLUT)
{
  int         nMode;
  sleep_lprm  *component;
  uint32      noAutoLat;
  uint64      currentTime;
  uint64      LPRMTime = CoreTimetick_Get64();
  uint32      numMode;
  sleep_lprm  **component_modes;
  
  CORE_VERIFY_PTR(synthLPRM);

  /* Set the current mode being exited */
  g_sleepCurrentlyConfiguringMode = synthLPRM;

  numMode         = synthLPRM->uncacheable.num_component_modes;
  component_modes = synthLPRM->uncacheable.component_modes;
  for(nMode = numMode - 1; nMode >= 0; nMode--)
  {
    /* Calling the exit functions of the component modes */
    component   = component_modes[nMode];
    noAutoLat   = component->attributes & SLEEP_MODE_ATTR_NO_AUTO_LATENCY_TRACK;
    currentTime = 0;

    sleepLog_QDSSPrintf( SLEEP_LOG_LEVEL_PROFILING, 
                         SLEEP_EXIT_MODE_NUM_ARGS,
                         SLEEP_EXIT_MODE_STR, SLEEP_EXIT_MODE, 
                         component->parent_LPR->resource_name,
                         component->mode_name,
                         ULOG64_DATA(LPRMTime));

    /* Call LRPM exit function */
    if(NULL != component->exit_func)
    {
      component->exit_func();
    }

    /* Get the end of the current LPRM exit, and also use this as the
     * beginning of the next LPRM exit so that multiple calls to timetick
     * are avoided. */
    currentTime = CoreTimetick_Get64();

    /* Do statistic calculations */
    if((0 != noAutoLat) && (NULL != component->exit_func))
    {
      LPRMTime = sleepStats_getLastLprLatency(SLEEP_STATS_BACKOFF_LATENCY_TYPE);
    }
    else
    {
      LPRMTime = currentTime - LPRMTime;
    }

    /* On low timer resolution targets, ensure there is a minimal exit latency */
    if(0 == LPRMTime)
    {
      LPRMTime = 1;
    }

    /* Record the backoff time for QR handling */
    sleepQR_setComponentCycleBackoff(component, LPRMTime, &fLUT->dynamic_data);

    /* calculate last time in mode stats */
    component->mode_statistics.last_mode_time = currentTime - 
      component->mode_statistics.last_mode_time;

    /* Keep running total of mode time */
    component->mode_statistics.in_mode_time += 
      component->mode_statistics.last_mode_time;

    /* To avoid multiple calls to get the current time use the point after
     * the exit function returns, which is close enough to the start of the
     * next LRPM exit for statistical purposes. */
    LPRMTime = currentTime;
  }

  return;
}

/* 
 * synthLPRM_isConfiguringModeFullyCacheable 
 */
boolean synthLPRM_isConfiguringModeFullyCacheable(void)
{
  if (NULL != g_sleepCurrentlyConfiguringMode)
  {
    return (0 == g_sleepCurrentlyConfiguringMode->uncacheable.num_component_modes) ? TRUE : FALSE;
  }
  
  return FALSE;
}

/*
 * synthLPRM_update
 */
void synthLPRM_update( sleep_synth_lprm *synthLPRM,
                       sleep_lprm       *changedSleepLPRM )
{
  uint32       nComponentModes;
  sleep_status oldStatus;
  
  CORE_VERIFY_PTR(synthLPRM);
  CORE_VERIFY_PTR(changedSleepLPRM);

  oldStatus = synthLPRM->mode_status;

  /* Update the number of enabled modes */
  if( TRUE == changedSleepLPRM->mode_enabled )
    synthLPRM->num_enabled_component_modes++;
  else
    synthLPRM->num_enabled_component_modes--;

  /* Make sure the number of enabled component modes is not out of range. */
  nComponentModes = synthLPRM->cacheable.num_component_modes +
                    synthLPRM->uncacheable.num_component_modes;
  CORE_VERIFY( synthLPRM->num_enabled_component_modes >= 0 &&
               synthLPRM->num_enabled_component_modes <= nComponentModes );
  
  if(synthLPRM->num_enabled_component_modes == nComponentModes)
  {
    synthLPRM->mode_status = SLEEP_ENABLED;
  }
  else
  {
    synthLPRM->mode_status = SLEEP_DISABLED;
  }

  /* If we changed state, check for a parent and update it if we have one */
  if(synthLPRM->mode_status != oldStatus)
  {
#ifdef USLEEP_ISLAND_MODE_ENABLE
    if(0 != (synthLPRM->attr & SYNTH_MODE_ATTR_LPI))
    {
      synthLPI_modeUpdated(synthLPRM);
    }
    else
#endif
    {
      synthLPR_modeUpdated(synthLPRM);
    }
  }

  return;
}

