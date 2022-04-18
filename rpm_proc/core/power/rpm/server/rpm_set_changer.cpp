/*===========================================================================
  rpm_set_changer.cpp

  SERVICES:

  DESCRIPTION:

  INITIALIZATION AND SEQUENCING REQUIREMENTS:
  Description...

  Copyright (c) 2012 Qualcomm Technologies, Incorporated.  All Rights Reserved.
  QUALCOMM Proprietary.  Export of this technology or software is regulated
  by the U.S. Government. Diversion contrary to U.S. law prohibited.
  ===========================================================================*/


//===========================================================================
//                     Includes and Variable Definitions
//===========================================================================

//---------------------------------------------------------------------------
// Include Files
//---------------------------------------------------------------------------
#include <assert.h>
#include <string.h>
#include <alloca.h>

#include "rpm_set_changer.h"
#include "rpmserver_internal.h"
#include "rpm_spm_handshake.h"
#include "rpm_estimator.h"
#include "rpm_hash.h"
#include "swevent.h"
#include "rpm_config.h"
#include "rpm_resources_config.h"
#include "rpm_settling_timer.h"
#include "gpio_debug.h"

extern "C"
{
    #include "low_power_led.h"
}

#include "time_service.h"
#include "err.h"
#include "CoreVerify.h"

#include "rpm_messageram.h"

//---------------------------------------------------------------------------
// Constant / Define Declarations
//--------------------------------------------------------------------------
#define ARRAY_SIZE(x) (sizeof(x)/sizeof((x)[0]))

#define MAX_WAKEUP_DEADLINE_EXCEEDANCE              76800 /* Ticks in 19.2 MHz, 76800 ~= 4.0ms */
#define NUM_SHUTDOWNS_BEFORE_SETTLING_ESTIMATES     100
#define DEFAULT_NO_WORK_ESTIMATE                    1920  /* 100 usec */

//---------------------------------------------------------------------------
// Type Declarations
//---------------------------------------------------------------------------
struct EstimateContext
{
  unsigned ee;
  rpm_transition_type transition;

  unsigned *approxWorkRemaining;
  unsigned *approxSettlingRemaining;
};

struct TransitionContext
{
  volatile bool &preempt;
  uint64_t      &stop_time;

  unsigned ee;
  rpm_transition_type transition;

  unsigned *approxWorkRemaining;
  unsigned *approxSettlingRemaining;

  TransitionContext(volatile bool &pre, uint64_t &stop, unsigned ee, rpm_transition_type trans, unsigned *approx, unsigned *settling)
      : preempt(pre), stop_time(stop), ee(ee), transition(trans), approxWorkRemaining(approx), approxSettlingRemaining(settling)
  {
  }
};

//---------------------------------------------------------------------------
// Global Constant Definitions
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Local Object Definitions
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Static Variable Definitions
//---------------------------------------------------------------------------

static uint32_t       preProcessResources[SETTLING_BMSK_SIZE];
static boolean        disable_settling = FALSE;
static uint32_t       noWorkEstimates[NUM_CLOCK_RATES];

//---------------------------------------------------------------------------
// Forward Declarations
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// External References
//---------------------------------------------------------------------------

//===========================================================================
//                             Macro Definitions
//===========================================================================

//===========================================================================
//                           Function Definitions
//===========================================================================

/*===========================================================================
FUNCTION: rpm_set_changer_common_init

DESCRIPTION:

RETURN VALUE:
===========================================================================*/
__attribute__((section("rpmserver_cram_reclaim_pool")))
void rpm_set_changer_common_init(void)
{
    const rpm_bimc_resource_config_t *ptr = BIMC_RESOURCE_CONFIG_DATA;

    while(ptr->type)
    {
        uint32_t index = rpmserver_lookup_resource(ptr->type, ptr->id) - rpm->resources;

        CORE_VERIFY(index < SETTLING_BMSK_SIZE * 32);

        preProcessResources[index/32] |= (1 << (index % 32));

        ptr++;
    }
}

/*===========================================================================
FUNCTION: estimate_no_work

DESCRIPTION:

RETURN VALUE:
===========================================================================*/
static unsigned estimate_no_work(void)
{
    unsigned operating_point = theEstimator().currentOperatingPoint();

    return (noWorkEstimates[operating_point] > 0) ? noWorkEstimates[operating_point] : DEFAULT_NO_WORK_ESTIMATE;
}

/*===========================================================================
FUNCTION: observe_no_work

DESCRIPTION:

RETURN VALUE:
===========================================================================*/
static void observe_no_work(uint32_t elapsed_time)
{
    unsigned operating_point = theEstimator().currentOperatingPoint();

    if(noWorkEstimates[operating_point] < elapsed_time)
    {
        noWorkEstimates[operating_point] = elapsed_time;
    }
}

/*===========================================================================
  FUNCTION: SetChanger::SetChanger

  DESCRIPTION:

  RETURN VALUE:
  ===========================================================================*/
SetChanger::SetChanger(unsigned ee, Handler *handler, uint8_t priority)
    : Task(priority), state_(IDLE), ee_(ee), handler_(handler), currentSet_(RPM_ACTIVE_SET),
      destinationSet_(RPM_ACTIVE_SET), approxWorkRemaining_(0), approxSettlingRemaining_(0), actionHash_(0),
      started_(false), interrupted_(false), startState_(0), startTime_ (0), settlingTime_(0), tranBypassCount_ (0),
      wakeTime_(0), cacheHit_(0), bimcTransitionCount_(0)
{
  for(unsigned i = 0; i < SETTLING_BMSK_SIZE; i++)
    settlingBmsk_[i] = 0;
}

/*===========================================================================
  FUNCTION: SetChanger::get_length_given

  DESCRIPTION:

  RETURN VALUE:
  ===========================================================================*/
uint64_t SetChanger::get_length_given(uint32_t systemStateIn, uint32_t &systemStateOut)
{
  bool hit = false;
  uint32_t resultState, timeEstimate;

  // Check the appropriate queue for active->sleep (immediate) or sleep->active.
  if(destinationSet_ != RPM_ACTIVE_SET)
  {
    hit = theEstimateCacheImmediate().lookup(systemStateIn, actionHash_, &resultState, &timeEstimate);
  }
  else
  {
    hit = theEstimateCache().lookup(systemStateIn, actionHash_, &resultState, &timeEstimate);
  }

  if(hit) {
    systemStateOut = resultState;
    setCacheHit(1);
    return timeEstimate;
  }

  setCacheHit(0);
  systemStateOut = 0;
  return get_length();
}

EEClient* resource_lookup_and_alloc_client(ResourceData *r, unsigned ee);

/*===========================================================================
  FUNCTION: SetChanger::estimateResource

  DESCRIPTION:

  RETURN VALUE:
  ===========================================================================*/
bool SetChanger::estimateResource(ResourceData *r)
{
  bool has_work = false;
  rpm_transition_type transition = (destinationSet_ == RPM_ACTIVE_SET) ? SLEEP_TO_ACTIVE : ACTIVE_TO_SLEEP;

  if(resource_ee_has_transition_work(r, ee_, transition))
  {
    EEClient* ee = resource_lookup_and_alloc_client(r, ee_);

    if(resource_ee_has_apply_work(r, ee->request[0], ee->request[1]))
    {
        unsigned estimate = resource_estimate(r, theEstimator().currentOperatingPoint());
        approxWorkRemaining_ += estimate;
        has_work = true;

        ResourceClassData *rc = &rpm->classes[r->class_idx];
        unsigned inrep_size = rc->inrep_size;

        char *substate = (char *)alloca(2 * inrep_size);
        memcpy(substate,              ee->request[0], inrep_size);
        memcpy(substate + inrep_size, ee->request[1], inrep_size);
        unsigned rotation = r - rpm->resources;
        actionHash_ ^= __ror(rpm_hash(2 * inrep_size, substate), rotation);
    }
  }

  return has_work;
}

/*===========================================================================
  FUNCTION: SetChanger::requeue

  DESCRIPTION:

  RETURN VALUE:
  ===========================================================================*/
void SetChanger::requeue_settling(uint64_t deadline)
{
  unsigned is_settling = 0;
  //its possible we got an explicit transition before the timer fired. In this case we
  //will have already processed the settling resource, so check to see if there is anything still settling
  for (unsigned i = 0; i < SETTLING_BMSK_SIZE; i++)
  {
    is_settling |= settlingBmsk_[i];
  }

  if(is_settling)
  {
    if(!deadline)
    {
      SWEVENT(RPM_SETTLING_TRANSITION_REQUEUED, ee_, false);
      schedule_me(IGNORE_DEADLINE);
    }
    else
    {
      SWEVENT(RPM_SETTLING_TRANSITION_REQUEUED, ee_, true, (uint32)deadline, (uint32)(deadline >> 32));
      set_deadline(deadline);
      schedule_me();
    }
    state_ = SETTLING;
  }
}

/*===========================================================================
  FUNCTION: SetChanger::enqueue

  DESCRIPTION:

  RETURN VALUE:
  ===========================================================================*/
void SetChanger::enqueue(rpm_set_type destination_set, uint64_t deadline)
{
  if(state_ == IDLE)
  {
    rpm_transition_type  transition = (destination_set == RPM_ACTIVE_SET) ? SLEEP_TO_ACTIVE : ACTIVE_TO_SLEEP;
    destinationSet_ = destination_set;
    state_ = CHANGE_SETS;

    // Compute what work we'll need to do (how long it will take).
    approxWorkRemaining_ = 0;
    actionHash_ = 0xb7ee364b;
    for(unsigned i = 0; i < rpm->supported_resources; ++i)
    {
      ResourceData *r = &(rpm->resources[i]);

      if(!(r && r->current_state && resource_ee_has_transition_work(r, ee_, transition)))
      {
        continue; // not an initialized resource or no work to do
      }

      if(estimateResource(r))
      {
          approxSettlingRemaining_ = MAX(approxSettlingRemaining_, resource_settling_estimate(r));
      }
    }

    approxWorkRemaining_ += approxSettlingRemaining_;

    if (approxWorkRemaining_ == 0)
    {
      hasWork_ = false;
      approxWorkRemaining_ = estimate_no_work();
    }
    else
    {
      hasWork_ = true;
    }

    started_ = false;
    interrupted_ = false;
  }
  else
  {
    CORE_VERIFY(destinationSet_ == destination_set);
  }

  if(!deadline)
  {
    SWEVENT(RPM_TRANSITION_QUEUED, ee_, false);
    schedule_me(IGNORE_DEADLINE);
  }
  else
  {
    SWEVENT(RPM_TRANSITION_QUEUED, ee_, true, (uint32)deadline, (uint32)(deadline >> 32));
    set_deadline(deadline);
    schedule_me();
  }
}

/*===========================================================================
  FUNCTION: SetChanger::hasImmediateWork

  DESCRIPTION:

  RETURN VALUE:
  ===========================================================================*/
bool SetChanger::hasImmediateWork() const
{
  const EEData *ee = &(rpm->ees[ee_]);

  bool rudely_awoken = (ee->subsystem_status == SPM_WAKING_UP)      && (state_ != IDLE);
  bool going_to_bed  = (ee->subsystem_status == SPM_GOING_TO_SLEEP) && (state_ != IDLE);

  return rudely_awoken || going_to_bed;
}

/*===========================================================================
  FUNCTION: SetChanger::transitionResource

  DESCRIPTION:

  RETURN VALUE:
  ===========================================================================*/
static bool transitionResource(ResourceData *r, void *context, uint64 *settling_time)
{
  TransitionContext *ctxt = (TransitionContext *)context;

  Estimator &estimator = theEstimator();
  unsigned   runtime   = resource_estimate(r, estimator.currentOperatingPoint());
  uint64     observed_settling = 0;

  *settling_time = 0;

  if(ctxt->preempt || ((time_service_now() + runtime) > ctxt->stop_time))
    return false;

  Observation obs = estimator.startObservation();

  *settling_time = resource_ee_transition(r, ctxt->ee, ctxt->transition);
  if(*(ctxt->approxWorkRemaining) > runtime)
    *(ctxt->approxWorkRemaining) -= runtime;
  else
    *(ctxt->approxWorkRemaining) = 0;

  estimator.completeObservation(obs);

  if(*settling_time)
  {
    uint64 now = time_service_now();
    if (disable_settling)
    {
      while(*settling_time)
        *settling_time = resource_ee_settling_apply(r, ctxt->ee, *settling_time);
    }
    else if(*settling_time <= now)
    {
      *settling_time = resource_ee_settling_apply(r, ctxt->ee, *settling_time);
    }
    else
    {
      observed_settling = (*settling_time) - now;
    }
  }

  resource_observe(r, estimator.currentOperatingPoint(), obs, observed_settling);

  return true;
}

inline bool SetChanger::execute_specific_resource(TransitionContext *context, ResourceData *r)
{
  uint64 settling_time = 0;

  if(!resource_ee_has_transition_work(r, ee_, context->transition))
  {
    return true;
  }

  if(!transitionResource(r, context, &settling_time))
  {
    return false;
  }

  if(settling_time)
  {
    unsigned r_index = r - rpm->resources;
    assert((r_index/32) < SETTLING_BMSK_SIZE);
    settlingBmsk_[r_index/32] |= 1 << (r_index%32);
    SWEVENT(RPM_RESOURCE_SETTLING, ee_, (rpm->classes[r->class_idx]).type, r->id, 0);
    SWEVENT(RPM_RESOURCE_SETTLING_TIME, (uint32_t)settling_time, (uint32_t)(settling_time >> 32));
  }
  settlingTime_ = MAX(settling_time, settlingTime_);
  return true;
}

inline bool SetChanger::execute_resource_list(TransitionContext *context, uint32_t *resources_bmsk)
{
  for(unsigned i = 0; i < SETTLING_BMSK_SIZE; ++i)
  {
    uint32_t index_bmsk = resources_bmsk[i];
    while(index_bmsk)
    {
      uint32_t index = 31 - __clz(index_bmsk);
      ResourceData *r = &(rpm->resources[index + (32 * i)] );

      index_bmsk &= (~(1 << index));

      if (!execute_specific_resource(context, r))
      {
        return false;
      }
    }
  }
  return true;
}

/*===========================================================================
  FUNCTION: SetChanger::execute_until

  DESCRIPTION:

  RETURN VALUE:
  ===========================================================================*/
void SetChanger::execute_until(volatile bool &preempt, uint64_t stop_time)
{
  SWEVENT(RPM_MASTER_SET_TRANSITION, ee_, currentSet_, destinationSet_, getCacheHit());

  /*GPIO LOW*/
  gpio_test_low((gpio_debug_application)ee_, (gpio_debug_transition)destinationSet_);

  if(!started_)
  {
    started_ = true;
    interrupted_ = false;
    startState_ = rpm_system_hash;
    startTime_ = time_service_now();
    SWEVENT(RPM_MASTER_SET_TRANSITION_CACHE_STATUS, startState_, actionHash_);
  }

  // Note: this switch statement "resumes" from a previous pre-emption,
  // allowing a mechansim that is sometime referred to as "green threads" or
  // "protothreads." The fall-through (in every case block) is intentional
  // and vital to correct functionality.
  switch(state_)
  {
    case CHANGE_SETS:
      {
        currentSet_ = destinationSet_;

        // If we're going to sleep and at least one processor has woken up
        // already, skip directly to post dispatch without completing the
        // transition--we're just going to wake right up again.
        bool completed = true;
        // Visit all resources and place them in the destination set.
        rpm_transition_type  transition = (destinationSet_ == RPM_ACTIVE_SET) ? SLEEP_TO_ACTIVE : ACTIVE_TO_SLEEP;
        TransitionContext context(preempt, stop_time, ee_, transition, &approxWorkRemaining_, &approxSettlingRemaining_);

        if(!isWaking () && !isWakeupNear (&context))
        {
          // Visit all resources and place them in the destination set.
          if(destinationSet_ == RPM_SLEEP_SET)
          {
            //if we are going to sleep, process bimc dependencies first
            completed = execute_resource_list(&context, preProcessResources);
            if(!completed)
            {
              interrupted_ = true;
              break;
            }
          }

          ResourceData *bimc = rpmserver_lookup_resource(RPM_CLOCK_2_REQ, 0);

          if(bimc && bimc->current_state)
          {
            //process BIMC
            completed = execute_specific_resource(&context, bimc);
            if(!completed)
            {
              interrupted_ = true;
              break;
            }
          }

          //process everything else
          for(unsigned i = 0; i < rpm->supported_resources; ++i)
          {
            ResourceData *r = &(rpm->resources[i]);

            if(!(r && r->current_state))
            {
              continue; // not an initialized resource, doesn't have transition work, or was one of the preProcessed resources
            }

            completed = execute_specific_resource(&context, r);

            if(!completed)
            {
              interrupted_ = true;
              break;
            }
          }
          if(bimc && bimc->current_state)
          {
            uint64_t settling_time = resource_ee_settling_query(bimc, ee_);
            if(settling_time)
            {
              unsigned index = bimc - rpm->resources;
              assert((index/32) < SETTLING_BMSK_SIZE);
              settlingBmsk_[index/32] |= 1 << (index%32);
              SWEVENT(RPM_RESOURCE_SETTLING, ee_, (rpm->classes[bimc->class_idx]).type, bimc->id, 0);
              SWEVENT(RPM_RESOURCE_SETTLING_TIME, (uint32)settling_time, (uint32)(settling_time >> 32));
            }
            settlingTime_ = MAX(settling_time, settlingTime_);
          }

#if DAL_CONFIG_TARGET_ID==0x8998
          // CR 1041398 - NAZGUL V1: SW WAR for missing handshake to disable IO coherent redirect from BIMC
          // Handle the case where there is no work and SPM resource wasn't processed.
          if(ee_ == RPM_EE_APSS && !hasWork_)
          {
            rpm_cci_spm_e3_workaround();
          }
#endif /* DAL_CONFIG_TARGET_ID==0x8998 */

        } // if(!isWaking () && !isWakeupNear (&context))
        else
        {

#if DAL_CONFIG_TARGET_ID==0x8998
          // CR 1041398 - NAZGUL V1: SW WAR for missing handshake to disable IO coherent redirect from BIMC
          // Handle the case where set transition is bypassed and SPM resource wasn't processed.
          if(ee_ == RPM_EE_APSS)
          {
            rpm_cci_spm_e3_workaround();
          }
#endif /* DAL_CONFIG_TARGET_ID==0x8998 */

          completed = true;
          interrupted_ = true;
          tranBypassCount_ ++;
          SWEVENT (RPM_MASTER_SET_TRANSITION_BYPASS, (ee_ << 16 | rpm->ees[ee_].pending_bringups),
                   (uint32_t)(wakeTime_ >> 32), (uint32_t)wakeTime_, approxWorkRemaining_);
        }

        if(completed)
        {
          state_ = NAS_WORK;
        }
        else
        {
          break;
        }
      }

    case NAS_WORK:
      {
        if((RPM_SLEEP_SET != destinationSet_) || (handler_->processNAS(preempt, stop_time)))
        {
          if(!settlingTime_)
          {
            approxSettlingRemaining_ = 0;
            state_ = CLEANUP;
          }
          else
          {
            state_ = SETTLING;
          }
        }
        else
        {
            break;
        }
      }

    case SETTLING:
      {
        if(state_ == SETTLING)
        {
          uint64 new_time = 0;
          for(unsigned i = 0; i <= (rpm->supported_resources / 32); ++i)
          {
            while (settlingBmsk_[i])
            {
              uint32 index = 31 - __clz(settlingBmsk_[i]);
              ResourceData *r = &(rpm->resources[(i*32) + index]);
              new_time = resource_ee_settling_apply(r, ee_, settlingTime_);

              if(!new_time)
              {
                settlingBmsk_[i] &= (~(1 << index));
                SWEVENT(RPM_RESOURCE_SETTLING_COMPLETE, ee_, (rpm->classes[r->class_idx]).type, r->id);
              }
            }
          }
          approxSettlingRemaining_ = 0;
          settlingTime_ = 0;
          state_ = CLEANUP;
        }
      }

    case CLEANUP:
      {
        uint64_t now = time_service_now();

        // We're all done, so reset our internal state.
        set_end(now);
        uint64_t old_deadline = 0;
        bool deadline_valid = get_deadline (old_deadline);
        clear_deadline();
        state_ = IDLE;
        settlingTime_ = 0;
        approxSettlingRemaining_ = 0;

        SWEVENT(RPM_MASTER_SET_TRANSITION_COMPLETE, ee_, (uint32)(old_deadline>>32), (uint32)(old_deadline), (old_deadline && (now > old_deadline)));

        /*GPIO HIGH*/
        gpio_test_high((gpio_debug_application)ee_,(gpio_debug_transition)destinationSet_);

        uint64_t elapsed = now - startTime_;

        if (! interrupted_)
        {
          if (RPM_ACTIVE_SET == destinationSet_)
          {
            rpm->ees[ee_].stats->last_wake_transition_duration = (uint32_t)elapsed;
            theEstimateCache().observe(startState_, actionHash_, rpm_system_hash, elapsed, true);
          }
          else
          {
            rpm->ees[ee_].stats->last_sleep_transition_duration = (uint32_t)elapsed;
            theEstimateCacheImmediate().observe(startState_, actionHash_, rpm_system_hash, elapsed, true);
          }

          if(!hasWork_)
          {
              observe_no_work((uint32_t)elapsed);
          }
        }

        bool from_sleep = (RPM_SLEEP_SET != destinationSet_);

        if(from_sleep)
        {
          wakeTime_ = 0;
          // Also, send an interrupt ensure the other side wakes up in
          // the "timed wakeup" case.
          if(SPM_SLEEPING == rpm->ees[ee_].subsystem_status)
          {
            // coming from sleep with a scheduled wake up so set wakeup reason to 1 or SCHD_WAKEUP
            (message_ram_master_stats(ee_))->wakeup_reason = 1;
            rpm->ees[ee_].stats->wakeup_ind = now;
            rpm_spm_trigger_wakeup_int(ee_);

            if(deadline_valid && old_deadline && (now > old_deadline) && ((now - old_deadline) > MAX_WAKEUP_DEADLINE_EXCEEDANCE))
            {
                if((ee_ == RPM_EE_MPSS) && (rpm->ees[ee_].stats->num_shutdowns >= NUM_SHUTDOWNS_BEFORE_SETTLING_ESTIMATES))
                {
                    CORE_VERIFY(0);
                }
              //ERR_FATAL("Deadline latency exceeded", (uint32_t)this, 0, 0);
            }
          }
        }
        else
        {
          // going to sleep so set wakeup reason to be 0, or RUDE_WAKEUP
          (message_ram_master_stats(ee_))->wakeup_reason = 0;
        }

        // We just changed set, so the SPM state machine may need to advance.
        rpm_spm_state_machine(ee_, SPM_TRANSITION_COMPLETE);

        // Change Low Power LED if necessary
        rpm_low_power_led_toggle_led();
      }

    default:
      break;
  }

  if(state_ != IDLE)
  {
    interrupted_ = true;

    /*GPIO HIGH*/
    gpio_test_high((gpio_debug_application)ee_,(gpio_debug_transition)destinationSet_);
  }
}

/*===========================================================================
  FUNCTION: bool SetChanger::isWaking () const

  DESCRIPTION:

  RETURN VALUE:
  ===========================================================================*/
inline bool SetChanger::isWaking () const
{
  return ((RPM_SLEEP_SET == destinationSet_) && (rpm->ees[ee_].pending_bringups));
}

/*===========================================================================
  FUNCTION: bool SetChanger::isWakeupNear () const

  DESCRIPTION:

  RETURN VALUE:
  ===========================================================================*/
bool SetChanger::isWakeupNear (const TransitionContext *context) const
{
  bool ret = false;

  if ((context->transition == ACTIVE_TO_SLEEP) && (wakeTime_ > 0))
  {
    uint64_t now = time_service_now ();
    uint32_t timeEstimate = (*context->approxWorkRemaining);

    // Check if there's sufficient time to process the work. We use 2 times work estimate for
    // A->S and S->W.

    // If there's a cache hit, use the cache estimate. Else use the worst case (approxWorkRemaining).
    if (cacheHit_)
    {
      uint32_t resultState, timeEstimate = (*context->approxWorkRemaining);
      if(destinationSet_ != RPM_ACTIVE_SET)
      {
        theEstimateCacheImmediate().lookup(startState_, actionHash_, &resultState, &timeEstimate);
      }
      else
      {
        theEstimateCache().lookup(startState_, actionHash_, &resultState, &timeEstimate);
      }
    }
    ret = (now >= wakeTime_) || ((wakeTime_ - now) < (timeEstimate << 1));
  }

  return ret;
}

