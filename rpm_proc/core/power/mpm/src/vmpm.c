/*==============================================================================

FILE:      vmpm.c

DESCRIPTION: Function and data structure declarations

PUBLIC CLASSES:  Not Applicable

INITIALIZATION AND SEQUENCING REQUIREMENTS:  N/A

        Copyright © 2010-2011 Qualcomm Technologies Incorporated.
               All Rights Reserved.
            QUALCOMM Proprietary/GTDR

$Header: //components/rel/rpm.bf/1.8/core/power/mpm/src/vmpm.c#1 $
$Date: 2016/11/03 $

==============================================================================*/

#include <stdbool.h>
#include <DALSys.h>
#include <DALDeviceId.h>
#include <DDIInterruptController.h>
#include <err.h>

#include "vmpm.h"
#include <HALmpmint.h>
#include "HALhwio.h"
#include "tlmm_hwio.h"
#include "cortex-m3.h"
#include "../hal/source/common/HALmpmintInternal.h"
#include "HALmpm.h"
#include "vmpm_target.h"
#include "swevent.h"

#define MPM_IRQ    42
#define APPS_IRQ   9
#define LPASS_IRQ  21
#define MPSS_IRQ   5
#define SPS_IRQ 31
#define CDSP_IRQ 37


typedef struct
{
  uint32 vmpm_enable[3];
  uint32 vmpm_detect_ctl_lower[3];
  uint32 vmpm_detect_ctl_higher[3];
  uint32 vmpm_polarity[3];
} vmpm_master_cache_type;

static struct vmpm_masters_cache_s
{
  //0 = apps, 1 = modem, 2 = qdsp, 3 = riva/ssc
  vmpm_master_cache_type master[4];
} vmpm_masters_cache;

/* the purpose of this function is to make sure that a master's requested
 * interrupt configuration is in place at all times.
 *
 * if the interrupt corresponds to a GPIO, then we should only reconfigure it
 * if the requesting processor is the target of that GPIO.
 *
 * if it isn't a GPIO, we have no way to identify the 'owning' master, so we
 * only use the data in the BSP table and never reconfigure */
void vmpm_reconfigure(uint32 phys_int_num, uint32 master_isr, HAL_mpmint_TriggerType trigger)
{
  uint32 mpm_int_id, gpio_num;

  /* check to see if this physical interrupt number is supported */
  if(!HAL_mpmint_GetEnumNumber(phys_int_num, &mpm_int_id))
    return;

  /* before reconfiguring, check to see if this is a GPIO--if not we leave the
   * interrupt configured to whatever is in the BSP table (as the interrupt is
   * a fixed-function interrupt that should never change). */
  if(!HAL_mpmint_IsGpio(mpm_int_id, &gpio_num))
    return;

  /* in order to check the permissions of this master to change this interrupt,
   * we first need to see if this gpio is routed to a summary interrupt or a
   * direct connect interrupt */

  /* now go look at the appropriate configuration source to figure out which
   * trigger we should be using */

  if(!gpio_is_dir_conn_intr_enabled(gpio_num))
  {
    /* this is a summary interrupt, which means we can look up its destination
     * mapping quite easily */
    if(gpio_is_summary_intr(vmpm_masters_info[master_isr].target_id, gpio_num))
    {
      /* configure MPM with the correct information */
      HAL_mpmint_SetTrigger(mpm_int_id, trigger);
    }
  }
  else
  {
    /* for direct connect, we have to loop through the direct connect registers
     * and find the one that is connecting this GPIO */
    if(gpio_is_dir_conn_intr(vmpm_masters_info[master_isr].target_id, gpio_num))
    {
      /* configure MPM with the correct information */
      HAL_mpmint_SetTrigger(mpm_int_id, trigger);
    }
  }
}

void vmpm_enable_interrupt(uint32 phys_int_num)
{
  uint32 mpm_int_id;

  /* check to see if this physical interrupt number is supported */
  if(!HAL_mpmint_GetEnumNumber(phys_int_num, &mpm_int_id))
    return;

  /* enable the interrupt */
  HAL_mpmint_Enable(mpm_int_id);
}

void vmpm_disable_interrupt(uint32 phys_int_num)
{
  uint32 i, num_masks, mpm_int_id;
  bool   in_use = false;

  /* check to see if this physical interrupt number is supported */
  if(!HAL_mpmint_GetEnumNumber(phys_int_num, &mpm_int_id))
    return;

  /* before we can disable an interrupt, we need to loop through all the
   * masters and make sure nobody is requesting that interrupt be enabled */
  HAL_mpmint_GetNumberMasks(&num_masks);
  for(i = 0; i < VMPM_NUM_MASTERS; i++)
  {
    vmpm_data_t *vmpm = message_ram_vmpm((vmpm_masters)i);
    uint32 masterEnable = vmpm->vmpm_enable[phys_int_num / 32];
    if((1 << (phys_int_num % 32)) & masterEnable)
    {
      in_use = true;
      break;
    }
  }

  if(!in_use)
    HAL_mpmint_Disable(mpm_int_id);
}

/** Interrupt service routine for an incoming master interrupt.
 *
 * Masters send interrupts after they have written their 'clear' register, so
 * that we can be notified of the write and process it accordingly.  So--check
 * their clear register and do the operation now.
 */
void vmpm_isr(void) __irq
{
  //vmpm_master_info_type *master = (vmpm_master_info_type *)param;
  DALBOOL still_pending = FALSE;
  uint32 i, num_masks, master_isr;
  unsigned curr_isr = interrupt_current_isr();
  vmpm_data_t *vmpm = NULL;

  switch(curr_isr)
  {
    case APPS_IRQ:
      master_isr = 0;
      break;

    case MPSS_IRQ:
      master_isr = 1;
      break;

    case LPASS_IRQ:
      master_isr = 2;
      break;

    case SPS_IRQ:
      master_isr = 3;
      break;

    case CDSP_IRQ:
      master_isr = 3;
      break;

    default:
      // shouldn't reach here...
      abort();
  }

  vmpm = message_ram_vmpm((vmpm_masters)master_isr);

  /* the clear operation clears from status any bits written '1' to clear */
  HAL_mpmint_GetNumberMasks(&num_masks);
  for(i = 0; i < num_masks; i++)
  {
    uint32 masterEnable               = vmpm->vmpm_enable[i];
    uint32 masterEnableCache          = vmpm_masters_cache.master[master_isr].vmpm_enable[i];
    uint32 masterDetectCtlLower       = vmpm->vmpm_detect_lower[i];
    uint32 masterDetectCtlHigher      = vmpm->vmpm_detect_higher[i];
    uint32 masterDetectCtlLowerCache  = vmpm_masters_cache.master[master_isr].vmpm_detect_ctl_lower[i];
    uint32 masterDetectCtlHigherCache = vmpm_masters_cache.master[master_isr].vmpm_detect_ctl_higher[i];
    uint32 masterPolarity             = vmpm->vmpm_polarity[i];
    uint32 masterPolarityCache        = vmpm_masters_cache.master[master_isr].vmpm_polarity[i];
    uint32 masterStatus               = vmpm->vmpm_status[i];
    uint32 temp, int_num;

    /* check for any newly reconfigured interrupts, or any newly enabled
     * interrupts, and make sure the triggers are configured correctly */
    temp = masterDetectCtlLower ^ masterDetectCtlLowerCache;
    temp |= masterDetectCtlLower ^ masterDetectCtlHigherCache;
    temp |= masterPolarity ^ masterPolarityCache;
    temp |= masterEnable & ~masterEnableCache;
    while(temp)
    {
      uint32                 detect, detect3, polarity;
      HAL_mpmint_TriggerType trigger;

      int_num = (31 - __clz(temp)) + 32 * i;

      detect = masterDetectCtlLower & (1 << (int_num % 32));
      detect3 = masterDetectCtlHigher & (1 << (int_num % 32));
      polarity = masterPolarity & (1 << (int_num % 32));

      HAL_mpmint_GetIndex(detect, detect3, polarity, (1 << (int_num % 32)), &trigger);

      vmpm_reconfigure(int_num, master_isr, trigger);

      temp &= ~(1 << (int_num % 32));
    }
    vmpm_masters_cache.master[master_isr].vmpm_detect_ctl_lower[i] = masterDetectCtlLower;
    vmpm_masters_cache.master[master_isr].vmpm_detect_ctl_higher[i] = masterDetectCtlHigher;
    vmpm_masters_cache.master[master_isr].vmpm_polarity[i] = masterPolarity;

    /* check for any newly enabled interrupts */
    temp = masterEnable & ~masterEnableCache;
    while(temp)
    {
      int_num = (31 - __clz(temp)) + 32 * i;
      vmpm_enable_interrupt(int_num);
      temp &= ~(1 << (int_num % 32));
    }

    /* check for any newly disabled interrupts */
    temp = masterEnableCache & ~masterEnable;
    while(temp)
    {
      int_num = (31 - __clz(temp)) + 32 * i;
      vmpm_disable_interrupt(int_num);
      temp &= ~(1 << (int_num % 32));
    }
    vmpm_masters_cache.master[master_isr].vmpm_enable[i] = masterEnable;

    /* if any 'clear' bits are set, remove them from status */
    vmpm->vmpm_status[i] = masterStatus;

    /* check if there's still an int pending */
    if(masterStatus & masterEnable)
      still_pending = TRUE;
  }

  /* if there was still an interrupt pending, re-send the virtual mpm int */
  if(still_pending)
      vmpm_masters_info[master_isr].pfnSendInterrupt();
}

__attribute__((section("mpm_cram_reclaim_pool")))
void vmpm_init(void)
{
  uint32 i, j, num_masks;
  char **ppszVersionInt = NULL;
  volatile unsigned isrNum = interrupt_current_isr();

  HAL_mpmint_Init( ppszVersionInt );

  /* walk the master list and initialize for each */
  HAL_mpmint_GetNumberMasks(&num_masks);
  for(i = 0; i < VMPM_NUM_MASTERS; i++)
  {
    vmpm_data_t *vmpm = message_ram_vmpm((vmpm_masters)i);

    for(j = 0; j < num_masks; j++)
    {
      vmpm->vmpm_enable[j]        = 0;
      vmpm->vmpm_detect_lower[j]  = 0;
      vmpm->vmpm_detect_higher[j] = 0;
      vmpm->vmpm_polarity[j]      = 0;
      vmpm->vmpm_status[j]        = 0;

      vmpm_masters_cache.master[i].vmpm_enable[j]            = 0;
      vmpm_masters_cache.master[i].vmpm_detect_ctl_lower[j]  = 0;
      vmpm_masters_cache.master[i].vmpm_detect_ctl_higher[j] = 0;
      vmpm_masters_cache.master[i].vmpm_polarity[j]          = 0;
    }
    interrupt_set_isr(vmpm_masters_info[i].vmpm_interrupt, vmpm_isr);
  }
}

void vmpm_prepare_for_sleep(void)
{
  uint32 i;	

  /* first clear any stale interrupts (from previous sleep / active period) */
  HAL_mpmint_All_Clear();

  /* no matter what interrupts are enabled by masters, we always need to
   * enable the timetick interrupt (for wakeup-on-timer) and the processor
   * wakeup interrupts (to allow actual wakeups) */
  HAL_mpmint_Enable(HAL_MPMINT_QTIMER_ISR);

  /* Enable this interrupt since RPM is the destination and owns the config */

  for(i = 0; i < (NUM_RPM_WAKEUP_INTS); i++)
  {
    HAL_mpmint_Enable(rpm_wakeup_ints[i].mpm_interrupt_index);
  }    

}

void vmpm_propogate_interrupts(void)
{
  uint32 i, num_masks, master;
  uint32 tempStatus[HAL_MPMINT_PHYS_INTS/32] = {0};

  /* disable the MPM interrupt in the RPM QGIC because this basically services
   * the interrupt before interrupts are ever unlocked */
  interrupt_disable(MPM_IRQ);

  /* iterate over the hardware's masks, collecting pending ints */
  HAL_mpmint_GetNumberMasks(&num_masks);
  for(i = 0; i < num_masks; i++)
  {
    uint32 newStatus;
    HAL_mpm_GetWakeupInts(i, &newStatus);

    /* install the new pending interrupts in each master */
    for(master = 0; master < VMPM_NUM_MASTERS; master++)
    {
      vmpm_data_t *vmpm = message_ram_vmpm((vmpm_masters)master);
      vmpm->vmpm_status[i] |= newStatus;
      tempStatus[i] |= newStatus;
    }
  }

  /* now send interrupts to masters if they have pending interrupts */
  for(master = 0; master < VMPM_NUM_MASTERS; master++)
  {
    vmpm_data_t *vmpm = message_ram_vmpm((vmpm_masters)master);

    for(i = 0; i < num_masks; i++)
    {
      uint32 enabled = vmpm->vmpm_enable[i];
      uint32 pending = vmpm->vmpm_status[i];

      if(enabled & pending)
      {
        /* this master does need an interrupt--send it and move on */
        /* Send both vmpm and the wakeup_ind, per agreement with the sleep team */
        vmpm_masters_info[master].pfnSendWakeup();
        vmpm_masters_info[master].pfnSendInterrupt ();
        break;
      }
    }
  }

  /* check for RPM registered wakeup interrupts and trigger if pending*/
      
  for(i = 0; i < (NUM_RPM_WAKEUP_INTS); i++)
  {
    uint32 mpm_int_num = (rpm_wakeup_ints[i].mpm_interrupt_index % 32);  
    uint32 mpm_int_index = (rpm_wakeup_ints[i].mpm_interrupt_index / 32);  

    uint32 pending = tempStatus[mpm_int_index];
    uint32 mpm_index = (1 << (mpm_int_num));
    if(pending & mpm_index)
    {
        SWEVENT(RPM_SOFT_TRIGGER_BRINGUP, pending, mpm_index);	    
        interrupt_soft_trigger(rpm_wakeup_ints[i].rpm_interrupt_index);	    
    }    
  }  
}

