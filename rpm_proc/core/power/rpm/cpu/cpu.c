/*===========================================================================
                              cpu.c

SERVICES:

DESCRIPTION:

INITIALIZATION AND SEQUENCING REQUIREMENTS:
  Description...

Copyright (c) 2013 Qualcomm Technologies, Inc.  All Rights Reserved.
QUALCOMM Proprietary.  Export of this technology or software is regulated
by the U.S. Government. Diversion contrary to U.S. law prohibited.
===========================================================================*/


//===========================================================================
//                     Includes and Variable Definitions
//===========================================================================

//---------------------------------------------------------------------------
// Include Files
//---------------------------------------------------------------------------
#include "npa.h"
#include "railway.h"
#include "rpm_sched.h"
#include "time_service.h"
#include "CoreVerify.h"
#include "railway.h"
#include "cpu.h"

#include "swevent.h"
#include "cpu.h"


//---------------------------------------------------------------------------
// Constant / Define Declarations
//--------------------------------------------------------------------------
#define ARRAY_SIZE(a) (sizeof(a)/sizeof((a)[0]))

// Reasons to choose your clock rate (for logging).
#define CPU_IDLE                0
#define CPU_SPEEDUP             1
#define CPU_NO_SPEEDUP          2
#define CPU_IMMINENT_PROCESSING 3
#define CPU_SCHEDULE_IS_FULL    4
#define CPU_EXTERNAL_VOTE       5

#define CPU_WORKLOAD_THRESHOLD  57600 /* 3ms */

//---------------------------------------------------------------------------
// Type Declarations
//---------------------------------------------------------------------------
typedef struct
{
  unsigned int   clock_freq_khz;
  railway_corner voltage_requirement;
} cpu_mode;

//---------------------------------------------------------------------------
// Global Constant Definitions
//---------------------------------------------------------------------------
//
//svs2->svs, svs2->nom, svs->nom. old mode + new mode - 1
unsigned int cpu_switch_time[CPU_NUM_MODES] = {0, 0, 0};
unsigned int cpu_max_switch_time = 0;

//---------------------------------------------------------------------------
// Local Object Definitions
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Static Variable Definitions
//---------------------------------------------------------------------------
static const char *cpu_resources[] = {"/clk/cpu"};
static npa_client_handle cpu_handle;
static railway_voter_t vddcx_handle;
static int vddcx_rail_id;

// Our current operating mode--initially as fast as possible.
static unsigned int cpu_inited             = 0;
static unsigned int cpu_railway_mode       = CPU_FAST;
static unsigned int cpu_railway_previous_mode       = CPU_FAST;
static unsigned int cpu_freq_request = 0;

static const cpu_mode cpu_modes[CPU_NUM_MODES] =
{
  { .clock_freq_khz = 300000, .voltage_requirement = RAILWAY_SVS_LOW }, // RPM "SVS2" mode
  { .clock_freq_khz = 400000, .voltage_requirement = RAILWAY_SVS     }, // standard RPM "slow" mode
  { .clock_freq_khz = 600000, .voltage_requirement = RAILWAY_NOMINAL }, // standard RPM "fast" mode
};

//---------------------------------------------------------------------------
// Forward Declarations
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// External References
//---------------------------------------------------------------------------


//===========================================================================
//                           Function Definitions
//===========================================================================

/*===========================================================================
FUNCTION: cpu_current_speed

DESCRIPTION:

RETURN VALUE:
===========================================================================*/
cpu_mode_id cpu_current_speed(void)
{
  return (cpu_mode_id)cpu_railway_mode;
}

/*===========================================================================
FUNCTION: cpu_current_freq

DESCRIPTION:

RETURN VALUE:
===========================================================================*/
unsigned int cpu_get_freq(cpu_mode_id mode)
{
  return cpu_modes[mode].clock_freq_khz;
}


/*===========================================================================
FUNCTION: cpu_set_mode

DESCRIPTION:

RETURN VALUE:
===========================================================================*/
static void cpu_set_mode(unsigned int mode, bool passive)
{
  unsigned int start, end;

  CORE_VERIFY(mode < CPU_NUM_MODES);

  start = time_service_now();

  if(mode != cpu_railway_mode || !cpu_inited)
  {
    unsigned int switch_time_index = (mode + cpu_railway_mode) - 1;
    cpu_inited = 1;
    cpu_railway_mode = mode;
    railway_corner_vote(vddcx_handle, cpu_modes[mode].voltage_requirement);
	
    // If passive is true, we just need to put our vote in and not actually transition the rail.
    // This will be the case if cpu_set_mode is being called from a railway callback.
    if(!passive)
    {
      railway_transition_rail(vddcx_rail_id);
    }

    // Record how long this took if it's longer than we've seen before.
    end = time_service_now();
    if((end - start) > cpu_switch_time[switch_time_index])
    {	    
      cpu_switch_time[switch_time_index] = end - start;
      if (cpu_switch_time[switch_time_index] > cpu_max_switch_time)
      {
          cpu_max_switch_time = cpu_switch_time[switch_time_index];
      }	      
    }      
  }
}

/*===========================================================================
FUNCTION: cpu_prechange_cb

DESCRIPTION:
// The VDDCX prechange callback lets us lower our clock vote when the voltage
// has aggregated to a lower status (we also have a vote on the voltage, which
// is how we forcibly raise the clock).

RETURN VALUE:
===========================================================================*/
static void cpu_prechange_cb(const railway_settings *settings, void* cookie)
{
  unsigned int clock_vote = 0;

  for(unsigned int i = 0; i < CPU_NUM_MODES; ++i)
  {
    if(cpu_modes[i].voltage_requirement <= settings->mode)
      clock_vote = cpu_modes[i].clock_freq_khz; // voltage is sufficient for this clock rate
  }

  if(clock_vote < cpu_freq_request)
  {
    // The acceptable clock rate is lower, so we need to lower our vote.
    npa_issue_suppressible_request(cpu_handle, clock_vote);
    cpu_freq_request = clock_vote;
    sched_cpu_speed_change(clock_vote);

    // compare railway vote with driver vote to make sure
    // actual voltage >= required voltage for our current frequency
    if(clock_vote < cpu_modes[cpu_railway_mode].clock_freq_khz)
      ERR_FATAL("RPM clock lowered below expected floor.", 0, 0, 0);
  }
}

/*===========================================================================
FUNCTION: 

DESCRIPTION:
The VDDCX postchange callback gives us the opportunity to ensure we're
running as fast as we can for the current voltage selection.

RETURN VALUE:
===========================================================================*/
static void cpu_postchange_cb(const railway_settings *settings, void* cookie)
{
  unsigned int clock_vote = 0;
  cpu_mode_id new_mode = CPU_FAST; 

  for(unsigned int i = 0; i < CPU_NUM_MODES; ++i)
  {
    if(cpu_modes[i].voltage_requirement <= settings->mode)
    {	    
      clock_vote = cpu_modes[i].clock_freq_khz; // voltage is sufficient for this clock rate
      new_mode = (cpu_mode_id)i;
    }      
  }

  if(clock_vote > cpu_freq_request)
  {
    // The acceptable clock rate is higher, so we can safely increase our clock vote.
    npa_issue_suppressible_request(cpu_handle, clock_vote);
    cpu_freq_request = clock_vote;
    sched_cpu_speed_change(clock_vote);

    // Put a handy log message noting that we raised the clock because we had the opportunity.
    SWEVENT(RPM_CPU_FAST_EXTERNAL_VOTE);

    // Lock in the new mode;
    cpu_set_mode(new_mode, true);
  }
}

/*===========================================================================
FUNCTION: cpu_resources_ready

DESCRIPTION:

RETURN VALUE:
===========================================================================*/
static void cpu_resources_ready(void *unused_context, unsigned int unused, const char **resources, unsigned int num_resources)
{
//  npa_client_handle sfpb_handle;

  // Create the requisite NPA clients.
  CORE_VERIFY_PTR(cpu_handle   = npa_create_sync_client("/clk/cpu",    "rpm cpu", NPA_CLIENT_SUPPRESSIBLE));
  
  vddcx_rail_id = rail_id("vddcx");
  CORE_VERIFY(vddcx_rail_id!=RAIL_NOT_SUPPORTED_BY_RAILWAY);
  
  vddcx_handle = railway_create_voter(vddcx_rail_id, true, RAILWAY_CPU_VOTER_ID);

  // Attach ourselves to the VDDCX callback system.
  
  railway_set_callback(vddcx_rail_id, RAILWAY_PRECHANGE_CB,  cpu_prechange_cb, NULL);
  railway_set_callback(vddcx_rail_id, RAILWAY_POSTCHANGE_CB, cpu_postchange_cb, NULL);

  cpu_set_mode(cpu_railway_mode, false);
  sched_cpu_speed_change(cpu_modes[cpu_railway_mode].clock_freq_khz);
}

/*===========================================================================
FUNCTION: cpu_init

DESCRIPTION:

RETURN VALUE:
===========================================================================*/
void cpu_init(void)
{
  npa_resources_available_cb(ARRAY_SIZE(cpu_resources), cpu_resources, (npa_callback)cpu_resources_ready, NULL);
}

/*===========================================================================
FUNCTION: cpu_get_switch_time

DESCRIPTION:

RETURN VALUE: duration for switching CPU speed
===========================================================================*/

unsigned cpu_get_switch_time(void)
{
  return cpu_max_switch_time;
}

static void cpu_get_durations(unsigned int current_mode, unsigned int new_mode, unsigned int* old_duration, unsigned int* new_duration)
{
    *old_duration = sched_get_next_duration(cpu_modes[current_mode].clock_freq_khz);
    unsigned int new_mhz = cpu_modes[new_mode].clock_freq_khz / 1000;
    unsigned int old_mhz = cpu_modes[current_mode].clock_freq_khz / 1000;
    *new_duration = (*old_duration + (((*old_duration) * old_mhz)/new_mhz))/2; 
}

static bool cpu_slow_fast_speedup(void)
{
    CORE_VERIFY(CPU_SLOW == cpu_railway_mode);	
    unsigned int new_duration, old_duration;	
    cpu_get_durations(CPU_SLOW, CPU_FAST, &old_duration, &new_duration);

    /*
     * CR 1088640:
     * The ratio, old_duration/new_duration, was always 1.2 due to the formula in cpu_get_durations(), and
     * RPM was choosing speed up almost always since CPU switch time is smaller than (1/6)*old_duration.
     * It caused early wakeups during Modem standbys, and RPM was just spinning and wasting power.
     * If RPM didn't speed up and stayed at SVS speed, the issue didn't occur.
     *
     * Tried sched_get_next_duration() for new_duration instead but durations were not reliable due to
     * the worst case time stored in each resource. Some resource had the worst time during FAST mode but
     * not during SLOW mode, and it gave FAST mode duration (new_duration) was much longer than SLOW mode duration (old_duration).
     * The overhead time was not that bad but couldn't use this approach since the durations are not reliable.
     *
     * The formula above was actually elimiating the uncertainty. Tried modifing the formula and
     * didn't observe speedup during modem standbys when the SW:HW ratio was set to 15%.
     * But the ratio approach had the following concerns:
     * - it could cause speedup for small workload.  For small workload, the benefit from faster speed would be negligible.
     * - it could miss speedup for large workload.  For large workload, there would be higher chance to get benefit from faster speed.
     * - Actual SW:HW ratio varies over resources and use cases.
     *
     * The workload approach was the most reasonable solution:
     * - it is simpler, less memory, deterministic, and more intuitive: more work, more speed
     * - the thing we have to avoid with optimization is that RPM never speed up and fails to catch up with processing tasks.
     *   The workload approach guarantees the case doesn't happen.
     *
     * The threshold values need to be adjusted properly. Otherwise it will cause 100% speedup.
     * Currently it's set to 3ms based on power team's help. About 2.4ms threshold they didn't observe speedup during modem standbys.
     * If cache miss happens, speed up would happen since the worst case estimate would be larger than 3ms.
     * As the worst case scenario we want to avoid is that RPM never speed up for huge workload, we could increase the threshold to 5ms or more.
     */
#if 0
    if ((new_duration + cpu_switch_time[(CPU_SLOW + CPU_FAST) - 1]) < old_duration)
#else
    if (old_duration >= CPU_WORKLOAD_THRESHOLD)
#endif
    {
        SWEVENT(RPM_CPU_FAST_SPEEDUP, old_duration, new_duration, cpu_switch_time[(CPU_SLOW + CPU_FAST) - 1]);
        cpu_set_mode(CPU_FAST, false);
        return true;
    }	    
    else
    {
      SWEVENT(RPM_CPU_SLOW_NO_SPEEDUP, old_duration, new_duration, cpu_switch_time[(CPU_SLOW + CPU_FAST) - 1]);
      return false;
    }
}

/*===========================================================================
FUNCTION: cpu_update_idle

DESCRIPTION:

RETURN VALUE: update speed floor around RPM halt
===========================================================================*/

void cpu_update_idle(bool entering)
{
    if(entering)
    {
        cpu_railway_previous_mode = cpu_railway_mode;
        cpu_set_mode(CPU_SLOW2, false);
    }
    else
    {
        int have_imminent_work = ((time_service_now() + 3 * cpu_max_switch_time) >= sched_get_next_start());
        switch(cpu_railway_mode)
        {
            case CPU_SLOW2: 
            {		    
                //if we don't have any work to do shortly, just set the mode to SLOW		    
                if(!have_imminent_work)
                {
                   cpu_set_mode(CPU_SLOW, false);
                   break;
                }			
                //we have to switch to SVS or NOM. Figure out which one is faster.		    
                unsigned int previous_duration, new_duration;    
                unsigned int new_mode = (cpu_railway_previous_mode == CPU_FAST) ? CPU_SLOW : CPU_FAST; 		    
                cpu_get_durations(cpu_railway_previous_mode, new_mode, &previous_duration, &new_duration);
		if((new_duration + cpu_switch_time[(CPU_SLOW2 + new_mode) - 1]) > 
                   (previous_duration + cpu_switch_time[(CPU_SLOW2 + cpu_railway_previous_mode - 1)]))
                {
                   cpu_set_mode(cpu_railway_previous_mode, false);
                }			
		else
                {
                   cpu_set_mode(new_mode, false);
		}			
                break;		
            }		
            case CPU_SLOW: 
		//check if we should switch to NOM
                cpu_slow_fast_speedup();
                break;		
            case CPU_FAST: //if we are at fast on exiting halt, we won't lower
                return;    		    
        }		
    }
}

/*===========================================================================
FUNCTION: cpu_update_speed

DESCRIPTION:
This is "it" -- the meat, the business logic, the decider, the place we pick... fast or slow?

RETURN VALUE:
===========================================================================*/
bool cpu_update_speed(int change_speed)
{
  if(!cpu_handle)
    return false; // the system is not fully booted yet

  int have_imminent_work = ((time_service_now() + 3 * cpu_max_switch_time) >= sched_get_next_start());

  // There are 2 independent boolean states that affect the CPU decision making
  // which gives us 4 possible paths to take.  2 of those paths short circuit,
  // and 2 need to go on to make a "smarter" decision.
  
  // The first short-circuit path: we haev no immediate work to do, and either
  //   1) we're already running slow, so we have nothing to do, or
  //   2) XO shutdown is enabled
  //
  // In this case we're likely on our way to sleep.  The current theory is that
  // it isn't worth increasing VDDCX just so it can leak more during XO
  // shutdown.  On the flip side of that though, if we're imminently headed for
  // XO shutdown / Vdd Min then we want to get into that mode as quickly as
  // possible--that is, stay at whatever clock we're at, even if that's fast.
  if(!have_imminent_work && !change_speed)
    return false;

  if(!have_imminent_work && (cpu_railway_mode == CPU_SLOW))
    return false;
  
  // The second short-circuit path: we're running fast and we have work.  No
  // reason to slow down now--so just keep chugging away at high.  We have to
  // reissue the fast request though, to make sure that handling the request
  // doesn't cause us to drop lower than we want.
  if((cpu_freq_request == cpu_modes[CPU_FAST].clock_freq_khz) && have_imminent_work)
  {
    SWEVENT(RPM_CPU_FAST_IMMINENT_PROCESSING);
    cpu_set_mode(CPU_FAST, false);
    return false;
  }

  // Now the "smart" logic where we need to make a real decision.  First, if
  // we're requesting that we run fast and we have no work, ask the scheduler
  // if we can safely lower the clock rate while we're idle.
  // FIXME: probably should check whether vddcx would be held high anyway,
  //        before wasting time on checking to see if our schedule allows this
  //        (checking the schedule is expensive)
  if(CPU_FAST == cpu_railway_mode && !have_imminent_work)
  {
    if(!sched_cpu_speed_change_ok(cpu_modes[CPU_SLOW].clock_freq_khz)) // don't lower if it would make us late
    {
      SWEVENT(RPM_CPU_FAST_SCHEDULE_IS_FULL);
      return false;
    }

    SWEVENT(RPM_CPU_SLOW_IDLE);
    cpu_set_mode(CPU_SLOW, false);
    return true;
  }

  bool ret_val = false;

  // On the flip side, if we're asking for slow and we have enough work that it
  // makes sense to switch up to the next threshold, do it.
  if(CPU_FAST != cpu_railway_mode && have_imminent_work)
  {
    ret_val = cpu_slow_fast_speedup();
  }
  return ret_val;
}


