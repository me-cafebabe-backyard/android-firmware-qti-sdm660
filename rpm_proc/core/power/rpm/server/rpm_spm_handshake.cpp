/*==============================================================================

FILE:      rpm_spm_handshake.cpp

DESCRIPTION: This file implements SPM Handshakes and state changes

PUBLIC CLASSES:  Not Applicable

INITIALIZATION AND SEQUENCING REQUIREMENTS:  N/A

      Copyright (c) 2010-2017 Qualcomm Technologies Incorporated.
               All Rights Reserved.
         QUALCOMM Proprietary and Confidential


$Header: //components/rel/rpm.bf/1.8/core/power/rpm/server/rpm_spm_handshake.cpp#8 $
$Date: 2018/03/06 $

==============================================================================*/

#define __STDC_LIMIT_MACROS

#include <stdlib.h>
#include <assert.h>
#include <limits.h>

extern "C"
{
    #include "DALSys.h"
    #include "cortex-m3.h"
}
#include "swevent.h"
#include "rpm.h"
#include "rpmserver.h"
#include "rpmserver_internal.h"
#include "CoreVerify.h"

#include "msmhwiobase.h"
#include "HALhwio.h"
#include "rpm_hwio.h"
#include "security_hwio.h"

#include "time_service.h"
#include "rpm_config.h"
#include "rpm_sched.h"
#include "rpm_spm_handshake.h"
#include "rpm_messageram.h"
#include "cortex-m3.h"

extern "C"
{
	#include "cpr.h"
}

typedef struct
{
  uint8_t ee;
  uint8_t core;
} rpm_spm_isr_context_t;

static void rpm_spm_shutdown_low_isr(void) __irq;
static void rpm_spm_shutdown_high_isr(void) __irq;

static rpm_spm_isr_context_t   *spm_isr_context;


#if DAL_CONFIG_TARGET_ID==0x8998
// CR 1041398 - NAZGUL V1: SW WAR for missing handshake to disable IO coherent redirect from BIMC
#include "Chipinfo.h"
extern "C"
{
    #include "cci_spm_sw_sequence_rpm.h"
}

static struct
{
    bool enabled;
    bool execute_entry;
    bool execute_exit;
    rpm_spm_isr_context_t *apps_spm_isr_ctxt;
} cci_spm_e3_workaround;
#endif /* DAL_CONFIG_TARGET_ID==0x8998 */


// Table of callbacks for SPM state changes.
// FIXME: in future revision, get the size of this table from target specific
//        code, since it's really target-dependent
#define NUM_SPM_CALLBACKS 6
typedef struct
{
    uint32_t   ees; // mask of masters to call for
    spm_cb_fcn cb;  // the function to call
} spm_cb_t;
static spm_cb_t spm_callbacks[NUM_SPM_CALLBACKS];

#define SPM_CHANGE_STATE(new_state) \
{ \
    changed_state = TRUE; \
    rpm->ees[ee].subsystem_status = new_state; \
    rpm_trigger_spm_callbacks(ee); \
}

void rpm_trigger_spm_callbacks(unsigned ee)
{
    int i;

    for(i = 0; i < NUM_SPM_CALLBACKS; i++)
    {
        if(spm_callbacks[i].cb && (spm_callbacks[i].ees & (1 << ee)))
        {
            spm_callbacks[i].cb(ee, rpm->ees[ee].subsystem_status);
        }
    }
}

inline void rpm_acknowledge_spm_handshakes(unsigned ee)
{
    unsigned pending_bringups = __rbit(rpm->ees[ee].pending_bringups);

    unsigned core;
    while((core = __clz(pending_bringups)) != 32)
    {
        SWEVENT(RPM_BRINGUP_ACK, ee, core, rpm->ees[ee].is_soft_transition);

        if (rpm->ees[ee].is_soft_transition)
        {
            //send bringup ACK message
            rpm->ees[ee].is_soft_transition = false;
            rpm->ees[ee].handler->writeResponse(SPM_BRINGUP_ACK, 0, RPM_MESSAGE_ERROR_NONE, RPM_COMMAND_SERVICE);
        }
        else
        {
            HWIO_OUT(RPM_GPO_WDSET, (1 << (rpm->ees[ee].spm.bringupAcks[core]))); // set bringup_ack
        }
        pending_bringups &= ~(0x80000000 >> core);
    }

    // Handled the known pending bringups.
    if (rpm->ees[ee].pending_bringups)
    {
      rpm->ees[ee].stats->bringup_ack = time_service_now ();
    }
    
    rpm->ees[ee].pending_bringups = 0;
    
}

bool rpm_get_wakeup_deadline(unsigned ee, uint64_t &deadline)
{
  vmpm_data_t *vmpm = message_ram_vmpm((vmpm_masters)ee);
  deadline = vmpm->wakeup_time;

  return (deadline < UINT64_MAX);
}

static inline void rpm_spm_log_subsystem_states(void)
{
    unsigned master_states = 0;
    for(unsigned ee = 0; ee < rpm->num_ees; ee++)
    {
      if((rpm->ees[ee].subsystem_status == SPM_AWAKE) || (rpm->ees[ee].subsystem_status == SPM_GOING_TO_SLEEP))
      {
        master_states |= (1 << ee);
      }
    }
    SWEVENT(RPM_MASTER_STATES, master_states); 
}

void rpm_spm_state_machine(unsigned ee, rpm_spm_entry_reason reason)
{
    INTLOCK();

    bool        changed_state = false;
    EEData     *ee_state      = &(rpm->ees[ee]);
    SetChanger *changer       = ee_state->changer;

    do
    {
        switch(ee_state->subsystem_status)
        {
            case SPM_AWAKE:
                changed_state = FALSE;

                if(0 == ee_state->num_active_cores)
                {
                    SPM_CHANGE_STATE(SPM_GOING_TO_SLEEP);
                }
                else
                {
                    // We're awake, so make sure we keep up with any incoming bringup reqs.
                    rpm_acknowledge_spm_handshakes(ee);
                }
                break;

            case SPM_GOING_TO_SLEEP:
                if(changed_state)
                {
                    // check for scheduled wakeup
                    uint64_t deadline = 0;

                    if(! rpm_get_wakeup_deadline(ee, deadline))
                    {
                      deadline = 0;
                    }
                    changer->setWakeTime (deadline);
                    // enqueue immediate set transition to sleep
                    changer->enqueue(RPM_SLEEP_SET, 0);
                }
                changed_state = FALSE;

                // When we've finished selecting the sleep set, we're officially asleep.
                if((SPM_TRANSITION_COMPLETE == reason) && (RPM_SLEEP_SET == changer->currentSet()))
                {
                  SPM_CHANGE_STATE(SPM_SLEEPING);
                  rpm_spm_log_subsystem_states();
                }
                // However, we might get a wakeup request before we've made it all the way to sleep.
                if(SPM_BRINGUP_REQ == reason)
                {
                    // Set the preempt flag; this will force the set change to recycle if
                    // it's currently running.  It will notice the processor has woken up
                    // and stop performing its work.
                    theSchedule().preempt();
                }
                break;

            case SPM_SLEEPING:
                if(changed_state)
                {
                    // check for scheduled wakeup
                    uint64_t deadline = changer->getWakeTime ();
                    
                    // enqueue scheduled wakeup request
                    changer->enqueue(RPM_ACTIVE_SET, deadline);
                }
                changed_state = FALSE;

                if(ee_state->num_active_cores > 0)
                {
                    SPM_CHANGE_STATE(SPM_WAKING_UP);
                }
                break;

            case SPM_WAKING_UP:
                if(changed_state)
                {
                    // work our way back to the active set
                    if(RPM_SLEEP_SET == changer->currentSet() || changer->inTransition())
                    {
                        changer->enqueue(RPM_ACTIVE_SET, 0);
                    }
                }
                changed_state = FALSE;

                // check for completion
                if(RPM_ACTIVE_SET == changer->currentSet() && !changer->inTransition())
                {
                  SPM_CHANGE_STATE(SPM_AWAKE);
                  rpm_spm_log_subsystem_states();
                }
                break;
        }
    } while(changed_state);

    INTFREE();
}

static void rpm_spm_bringup_isr(void) __irq
{
    INTLOCK();

    unsigned isrNum = interrupt_current_isr();
    unsigned ee     = spm_isr_context[isrNum].ee;
    unsigned core   = spm_isr_context[isrNum].core;

    EEData               *ee_state = &(rpm->ees[ee]);
    const SPMDescription *spm      = &(ee_state->spm);

    CORE_VERIFY(ee < 0xFF);
#if DAL_CONFIG_TARGET_ID==0x660	|| DAL_CONFIG_TARGET_ID==0x405
	if(ee == RPM_EE_LPASS)
	{
		//Disable lpi_cx CPR controller
		cpr_lpi_controller_config(false);
	}
#endif /* DAL_CONFIG_TARGET_ID==0x660	|| DAL_CONFIG_TARGET_ID==0x405*/

    SWEVENT(RPM_BRINGUP_REQ, ee, core, ee_state->is_soft_transition);

    // Record this core as being active now.
    ee_state->num_active_cores++;
    ee_state->stats->active_cores |= (1 << core);
    ee_state->stats->bringup_req = time_service_now ();
    
    // We can't actually acknowledge the bringup here, because we haven't brought
    // the master out of its sleep set.
    ee_state->pending_bringups |= (1 << core);

    // Disable bringup_req as an interrupt, as the signal will stay high.
    interrupt_disable(spm->bringupInts[core]);
    
	// Send wakeup indicator interrupt to Modem (Workaround for Modem SPM issue)
    if (strcmp(ee_state->remote_ss, "mpss") == 0)
    {
       HWIO_OUT(RPM_IPC, (1<<15));
       HWIO_OUT(RPM_IPC, (1<<13));
    }
	else if(strcmp(ee_state->remote_ss, "lpass") == 0) // Send wakeup indicator interrupt to LPASS (Workaround for LPASS SPM issue)
    {
       HWIO_OUT(RPM_IPC, (1<<11));
	   HWIO_OUT(RPM_IPC, (1<<9));
    }	
	
    // Kick off whatever other action needs to happen due to this event.
    rpm_spm_state_machine(ee, SPM_BRINGUP_REQ);

    INTFREE();
}

static void rpm_spm_shutdown_high_isr(void) __irq
{
    INTLOCK();

    unsigned isrNum = interrupt_current_isr();
    unsigned ee     = spm_isr_context[isrNum].ee;
    unsigned core   = spm_isr_context[isrNum].core;
    unsigned active_cores;
    
    EEData               *ee_state = &(rpm->ees[ee]);
    const SPMDescription *spm      = &(ee_state->spm);

    CORE_VERIFY(ee < 0xFF);

    // A core turned off, so record that.
    ee_state->num_active_cores--;
    active_cores = ee_state->stats->active_cores;
    active_cores &= ~(1 << core);
    ee_state->stats->active_cores = active_cores;
    if (ee_state->num_active_cores == 0)
    {
      ee_state->stats->num_shutdowns ++;
      ee_state->stats->shutdown_req = time_service_now ();
    }
#if DAL_CONFIG_TARGET_ID==0x660	|| DAL_CONFIG_TARGET_ID==0x405
	if(ee == RPM_EE_LPASS)
	{
		//enable lpi_cx CPR controller
		cpr_lpi_controller_config( true );
	}
#endif /* DAL_CONFIG_TARGET_ID==0x660	|| DAL_CONFIG_TARGET_ID==0x405 */
    SWEVENT(RPM_SHUTDOWN_REQ, ee, core, ee_state->is_soft_transition);

#if DAL_CONFIG_TARGET_ID==0x8998
    // CR 1041398 - NAZGUL V1: SW WAR for missing handshake to disable IO coherent redirect from BIMC
    if((ee == RPM_EE_APSS) && cci_spm_e3_workaround.enabled)
    {
        /*
         * Just schedule Set Transition, and don't send shutdown ack until CCI SPM E3 entry sequence is executed.
         * The CCI SPM E3 entry sequence is called from SPM resource Clock driver callback or
         * SetChanger if Set Transition is bypassed.
         */
        cci_spm_e3_workaround.apps_spm_isr_ctxt = &spm_isr_context[isrNum];
        cci_spm_e3_workaround.execute_entry = true;
        cci_spm_e3_workaround.execute_exit  = true;

        // Disable shutdown_req as an interrupt, as the signal will stay high.
        interrupt_disable(spm->shutdownInts[core]);

        // Kick off whatever other action needs to happen due to this event.
        rpm_spm_state_machine(ee, SPM_SHUTDOWN_REQ);

        INTFREE();
        return;
    }
#endif /* DAL_CONFIG_TARGET_ID==0x8998 */

    // Acknowledge the shutdown by clearing bringup ack and setting shutdown ack.
    if(!ee_state->is_soft_transition)
    {
        HWIO_OUT(RPM_GPO_WDCLR, (1 << (spm->bringupAcks[core])));  // clear bringup_ack
        HWIO_OUT(RPM_GPO_WDSET, (1 << (spm->shutdownAcks[core]))); // set shutdown_ack
    }
    else
    {
        //send soft ACK
        rpm->ees[ee].handler->writeResponse(SPM_SHUTDOWN_ACK, 0, RPM_MESSAGE_ERROR_NONE, RPM_COMMAND_SERVICE);
    }

    // Wait for the shutdown to go through.
    interrupt_set_isr(spm->shutdownInts[core], rpm_spm_shutdown_low_isr);
    interrupt_configure(spm->shutdownInts[core], LEVEL_LOW);
    
    INTFREE();
}

static void rpm_spm_shutdown_low_isr(void) __irq
{
    INTLOCK();

    unsigned isrNum = interrupt_current_isr();
    unsigned ee     = spm_isr_context[isrNum].ee;
    unsigned core   = spm_isr_context[isrNum].core;

    EEData               *ee_state = &(rpm->ees[ee]);
    const SPMDescription *spm      = &(ee_state->spm);

    CORE_VERIFY(ee < 0xFF);

    SWEVENT(RPM_SHUTDOWN_ACK, ee, core, ee_state->is_soft_transition);

    // We're shutdown, switch over to sleep mode.
    if(!ee_state->is_soft_transition)
    {
        HWIO_OUT(RPM_GPO_WDCLR, (1 << (spm->shutdownAcks[core]))); // clear shutdown_ack
        interrupt_enable(spm->bringupInts[core]); // enable bringup_req ISR
    }

    // Reset shutdown_req monitoring for after the wakeup.
    interrupt_configure(spm->shutdownInts[core], LEVEL_HIGH);
    interrupt_set_isr(spm->shutdownInts[core], rpm_spm_shutdown_high_isr);

#if DAL_CONFIG_TARGET_ID==0x8998
    // CR 1041398 - NAZGUL V1: SW WAR for missing handshake to disable IO coherent redirect from BIMC
    if((ee == RPM_EE_APSS) && cci_spm_e3_workaround.enabled)
    {
        // rpm_spm_state_machine() is already called in shutdown_high_isr
        INTFREE();
        return;
    }
#endif

    // Kick off whatever other action needs to happen due to this event.
    rpm_spm_state_machine(ee, SPM_SHUTDOWN_REQ);

    INTFREE();
}

void rpm_spm_soft_transition( unsigned ee, rpm_spm_entry_reason reason)
{
  EEData *ee_state              = &(rpm->ees[ee]);
  const SPMDescription *spm     = &(ee_state->spm);
  
  //set flag, soft trigger interrupt
  ee_state->is_soft_transition = true;
  switch(reason)
  {
      case SPM_SHUTDOWN_REQ:
          interrupt_soft_trigger(spm->shutdownInts[0]);
          break;
      case SPM_BRINGUP_REQ:
          if((ee_state->subsystem_status != SPM_AWAKE) && (ee_state->subsystem_status != SPM_WAKING_UP))
          {		  
            interrupt_soft_trigger(spm->bringupInts[0]);
            interrupt_enable(spm->bringupInts[0]); // enable bringup_req ISR
          }	    
          break;

      default:
          abort();
  }    
}

__attribute__((section("rpmserver_cram_reclaim_pool")))
void rpm_spm_init(void)
{
    unsigned num_ees = rpm->num_ees;

    unsigned highestISR = 0;
   
    for(unsigned i = 0; i < num_ees; ++i)
    {
        EEData               *ee       = &(rpm->ees[i]);
        const SPMDescription *spm      = &(ee->spm);
        unsigned              numCores = spm->numCores;
        unsigned active_cores = 0;
        
        // All cores start "awake."
        ee->num_active_cores = numCores;
        ee->pending_bringups = 0;
        ee->subsystem_status = SPM_AWAKE;
        ee->is_soft_transition = false;
        
        for(unsigned core = 0; core < numCores; ++core)
        {
            unsigned bringupISR = spm->bringupInts[core];
            if(bringupISR > highestISR) highestISR = bringupISR;
            interrupt_configure(bringupISR, LEVEL_HIGH);
            interrupt_set_isr(bringupISR, rpm_spm_bringup_isr);

            unsigned shutdownISR = spm->shutdownInts[core];
            if(shutdownISR > highestISR) highestISR = shutdownISR;
            interrupt_configure(shutdownISR, LEVEL_HIGH);
            interrupt_set_isr(shutdownISR, rpm_spm_shutdown_high_isr);
            interrupt_enable(shutdownISR);

            active_cores |= (1 << core);
            ee->stats->active_cores = active_cores;
        }
    }

    // Allocate context blocks for each ISR.
    ++highestISR;
    spm_isr_context = new rpm_spm_isr_context_t[highestISR];
    memset(spm_isr_context, 0xFF, highestISR * sizeof(rpm_spm_isr_context_t));
    for(unsigned i = 0; i < num_ees; ++i)
    {
        EEData               *ee       = &(rpm->ees[i]);
        const SPMDescription *spm      = &(ee->spm);
        unsigned              numCores = spm->numCores;
        
        for(unsigned core = 0; core < numCores; ++core)
        {
            spm_isr_context[spm->shutdownInts[core]].ee = i;
            spm_isr_context[spm->shutdownInts[core]].core = core;

            spm_isr_context[spm->bringupInts[core]].ee = i;
            spm_isr_context[spm->bringupInts[core]].core = core;
        }
    }

#if DAL_CONFIG_TARGET_ID==0x8998
    // CR 1041398 - NAZGUL V1: SW WAR for missing handshake to disable IO coherent redirect from BIMC
    if((Chipinfo_GetFamily() == CHIPINFO_FAMILY_MSM8998) && (Chipinfo_GetVersion() < CHIPINFO_VERSION(2,0)))
    {
        cci_spm_e3_workaround.enabled = true;
    }
    else
    {
        cci_spm_e3_workaround.enabled = false;
    }
#endif /* DAL_CONFIG_TARGET_ID==0x8998 */
}

void rpm_spm_trigger_wakeup_int(unsigned ee)
{
    if(!rpm->ees[ee].is_soft_transition)
    {
        unsigned wakeupInt = rpm->ees[ee].wakeupInt;
        HWIO_OUT(RPM_IPC, wakeupInt);
		
        //CR930460. Due to delay between wakeup_int and bringup_req on power islands (sensors for now), 
		//  send the bringup ack early for scheduled wakeups so there is no possible delay 
		//  between bringup_req and bringup_ack
        if(ee == 3 | ee == 2) 
        {		
			rpm->ees[ee].stats->bringup_ack = time_service_now(); 
			// Read back MSG_RAM to guarantee flush 
			uint64 tmp = rpm->ees[ee].stats->bringup_ack; 
            HWIO_OUT(RPM_GPO_WDSET, (1 << (rpm->ees[ee].spm.bringupAcks[0]))); // set slpi bringup_ack
            SWEVENT(RPM_BRINGUP_ACK, ee, 0, rpm->ees[ee].is_soft_transition, (tmp >> 32));
        }	    
    }
    else
    {
        rpm_spm_soft_transition(ee, SPM_BRINGUP_REQ);
    }
}

void rpm_register_spm_callback(unsigned ee, spm_cb_fcn cb)
{
    int i, free = -1;

    CORE_VERIFY(cb);

    // Try first to find an existing registration of this callback, but also
    // record the location of a free entry, if any.
    for(i = 0; i < NUM_SPM_CALLBACKS; i++)
    {
        if(free < 0 && !spm_callbacks[i].cb)
            free = i;
        else if(spm_callbacks[i].cb == cb)
            break;
    }

    if(i < NUM_SPM_CALLBACKS)
    {
        // Found an existing entry for this callback, just add to the master mask.
        spm_callbacks[i].ees |= (1 << ee);
        return;
    }

    // Didn't find an existing entry, so make one if we can.
    if(free >= 0)
    {
        spm_callbacks[free].ees = (1 << ee);
        spm_callbacks[free].cb = cb;
        return;
    }

    // Out of space, time to fail.
    abort();
}

#if DAL_CONFIG_TARGET_ID==0x8998
// CR 1041398 - NAZGUL V1: SW WAR for missing handshake to disable IO coherent redirect from BIMC
// This function is called in Clock driver callback for SPM resource
void rpm_cci_spm_e3_workaround(void)
{
    SetChanger *changer;

    if(!cci_spm_e3_workaround.enabled)
    {
        return;
    }

    changer = rpm->ees[RPM_EE_APSS].changer;

    /*
     * Make sure this is called during set transition since this is called from Clock SPM resource callback as well.
     */
    if(!changer->inTransition())
    {
        return;
    }

    if(RPM_SLEEP_SET == changer->currentSet() && cci_spm_e3_workaround.execute_entry)
    {
        unsigned              core;
        const SPMDescription *spm;

        cci_spm_e3_workaround.execute_entry = false;

        SWEVENT(RPM_CCI_SPM_E3_ENTRY_WORKAROUND_STARTED);

        /*
         * workaround for cci spm E3 entry
         */
        cci_spm_e3_entry_rpm();

        CORE_VERIFY(cci_spm_e3_workaround.apps_spm_isr_ctxt);

        core = cci_spm_e3_workaround.apps_spm_isr_ctxt->core;
        spm  = &(rpm->ees[cci_spm_e3_workaround.apps_spm_isr_ctxt->ee].spm);

        // Acknowledge the shutdown by clearing bringup ack and setting shutdown ack.
        HWIO_OUT(RPM_GPO_WDCLR, (1 << (spm->bringupAcks[core])));  // clear bringup_ack
        HWIO_OUT(RPM_GPO_WDSET, (1 << (spm->shutdownAcks[core]))); // set shutdown_ack

        // Wait for the shutdown to go through.
        interrupt_set_isr(spm->shutdownInts[core], rpm_spm_shutdown_low_isr);
        interrupt_configure(spm->shutdownInts[core], LEVEL_LOW);

        // enable shutdown_req ISR
        interrupt_enable(spm->shutdownInts[core]);
    }
    else if(RPM_ACTIVE_SET == changer->currentSet() && cci_spm_e3_workaround.execute_exit)
    {
        SWEVENT(RPM_CCI_SPM_E3_EXIT_WORKAROUND_STARTED);

        cci_spm_e3_workaround.execute_exit = false;

        /*
         * workaround for cci spm E3 exit
         */
        cci_spm_e3_exit_rpm();
    }
    else
    {
        return;
    }

    SWEVENT(RPM_CCI_SPM_E3_WORKAROUND_FINISHED);
}
#endif /* DAL_CONFIG_TARGET_ID==0x8998 */

#if DAL_CONFIG_TARGET_ID==0x660	|| DAL_CONFIG_TARGET_ID==0x405

void rpm_spm_enable_lpass_shtdwn_interrupt(void)
{
	EEData               *ee       = &(rpm->ees[RPM_EE_LPASS]);
	const SPMDescription *spm      = &(ee->spm);
	unsigned              numCores = spm->numCores;
	
	for(unsigned core = 0; core < numCores; ++core)
	{
		interrupt_enable(spm->shutdownInts[core]); //Enable Shutdown interrupts for all cores for LPASS subsystem
	}
}

void rpm_spm_disable_lpass_shtdwn_interrupt(void)
{
	EEData               *ee       = &(rpm->ees[RPM_EE_LPASS]);
	const SPMDescription *spm      = &(ee->spm);
	unsigned              numCores = spm->numCores;
	
	for(unsigned core = 0; core < numCores; ++core)
	{
		interrupt_disable(spm->shutdownInts[core]); //Disable Shutdown interrupts for all cores for LPASS subsystem
	}
}

#endif /* DAL_CONFIG_TARGET_ID==0x660	|| DAL_CONFIG_TARGET_ID==0x405*/
