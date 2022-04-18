/*============================================================================

  @file sns_pm_smp2p.c

  @brief
  This file contains the implementation of the Sensors usage of SMP2P to monitor
  the activity of other processors

  Copyright (c) 2014-2016 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.

============================================================================*/

/*============================================================================

                        EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/ssc.slpi/2.2/pm/src/sns_pm_smp2p.c#2 $


when         who     what, where, why
----------   ---     ---------------------------------------------------------
03-27-2017   sd      Include uSleep_mode_trans.h for 8998
11-03-2016   rt      Added exponential backoff to AP resume hysteresis timer
03-13-2015   hw      Initial Version for 8996

============================================================================*/

/*=====================================================================
                               INCLUDES
=======================================================================*/
#include <stdbool.h>
#include "sns_init.h"
#include "sns_common.h"
#include "sns_pm.h"
#include "sns_pm_priv.h"
#include "sns_debug_str.h"

#include "smem_type.h"
#include "smp2p.h"
#include "sns_log_types.h"
#include "sns_log_api.h"
#include "log.h"
#include "log_codes.h"

#include "uSleep.h"
#if defined(SLEEP_HEADER_8998)
#include "uSleep_mode_trans.h"
#endif
#include "sns_profiling.h"

/*======================================================================
                     INTERNAL DEFINITIONS AND TYPES
========================================================================*/

/*============================================================================
  Static Data
  ===========================================================================*/
/* SMP2P task stack */
static OS_STK sns_pm_smp2p_task_stk[SNS_MODULE_STK_SIZE_DSPS_SMP2P];

/*======================================================================
                            GLOBAL VARIABLES
========================================================================*/
extern sns_pm_internal_s sns_pm;
extern bool linux_kernel_suspend;
extern volatile bool timer_valid;
extern uint32_t current_resume_hysteresis_ticks;
/* SPARE variables */
/* Resume time hysteresis to prevent rapid suspend/resume due to high frequency data. */
#define  MAX_RESUME_CONFLICTS       3
#define  MAX_RESUME_HYSTERESIS_TICKS    (uint32_t)(50000000/30.51) /* 50 second limit */

uint64_t ap_suspend_time = 0;
uint64_t ap_wakeup_time = 0;
uint8_t resume_conflict_count = 0;
/*======================================================================
                               FUNCTIONS
========================================================================*/
/*===========================================================================

FUNCTION sns_pm_smp2p_cb

DESCRIPTION
  Callback registered with smp2p to be called when the SMP2P_PROC_AWAKE bit is set
  on the other processor. This signals when the processor is either suspended or awake

===========================================================================*/
void sns_pm_smp2p_cb( uint32_t currstate )
{
  uint8_t os_err;
  bool ap_woke_up = currstate & SMP2P_PROC_AWAKE;

  sns_os_mutex_pend(sns_pm.pm_suspend_resume_mutex_ptr, 0, &os_err );
  SNS_ASSERT ( os_err == OS_ERR_NONE );

  if( ap_woke_up )
  {
    // Get timestamp of last AP wakeup
    ap_wakeup_time = sns_em_get_system_time(); 
    
    if(linux_kernel_suspend)
    {
      if ( SNS_ERR_FAILED == sns_em_register_utimer(resume_tmr_obj, current_resume_hysteresis_ticks))
      {
        linux_kernel_suspend = false;
        sns_pm_notify_smp2p_client(linux_kernel_suspend);
      }
      else
      {
        timer_valid = true;
      }
    }
  }
  else /*ap just entered suspend*/
  {
    // Get timestamp of last AP suspend
    ap_suspend_time = sns_em_get_system_time(); 
    
    /* If AP wakeup to suspend duration is in the range of the current
       hysteresis timer, increment the conflict count */
    if ((ap_suspend_time - ap_wakeup_time) >= (current_resume_hysteresis_ticks*0.95) &&
        (ap_suspend_time - ap_wakeup_time) <= (current_resume_hysteresis_ticks + (current_resume_hysteresis_ticks*0.25)))
    {
      resume_conflict_count++;
      if (resume_conflict_count == MAX_RESUME_CONFLICTS)
      {
        /* Exponentially increase the resume backoff timer to give AP time to suspend */
        if (current_resume_hysteresis_ticks < MAX_RESUME_HYSTERESIS_TICKS)
        {
           current_resume_hysteresis_ticks *= 2;
        } 
        resume_conflict_count = 0;
      }
    }
    else
    {
      resume_conflict_count = 0;
    }
    //if ap enter suspend, update flag and let timer cb take care of it
    timer_valid = false;

    if(!linux_kernel_suspend)
    {
      linux_kernel_suspend = true;
      sns_pm_notify_smp2p_client(linux_kernel_suspend);
    }
  }

  os_err = sns_os_mutex_post(sns_pm.pm_suspend_resume_mutex_ptr );
  SNS_ASSERT ( os_err == OS_ERR_NONE );
}

/**
 * The SMP2P client thread.
 *
 * @param[i] argPtr Not used
 */
static void
sns_pm_smp2p_task( void *argPtr )
{
  UNREFERENCED_PARAMETER(argPtr);
  int32_t retCode;
  smp2p_context_type    *conTxt = NULL;
  smem_host_type        sourceId;
  char                  *entryName = "sleepstate";
  uint32                currState, recvData = 0;


  sns_em_create_utimer_obj( &sns_pm_resume_timer_cb, NULL, SNS_EM_TIMER_TYPE_ONESHOT, &resume_tmr_obj );

  sourceId = SMEM_APPS;

  //register for smp2p
  retCode = smp2p_register(&conTxt, sourceId, entryName);

  if(SMP2P_STATUS_SUCCESS != retCode && SMP2P_STATUS_NOT_FOUND != retCode)
  {
    PM_MSG_1(ERROR, "Error: Finding Entry Failed:%d", retCode);
  }

  /* Set the initial resume hysteresis timer to the default value */
  current_resume_hysteresis_ticks = DEFAULT_RESUME_HYSTERESIS_TICKS;
  for(;;)
  {
    /*Wait for Entry Init signal*/
    PM_MSG_0( LOW, "sns_pm_smp2p_task: Waiting for Entry Event" );
    retCode = smp2p_wait(conTxt);
    if(SMP2P_STATUS_SUCCESS == retCode){
      PM_MSG_0( LOW, "sns_pm_smp2p_task: Got Entry Event" );
    }
    else{
      PM_MSG_1(ERROR, "Error: Wait for Entry Failed:%d", retCode);
    }

    /*Entry Found. Now Read Data */
    retCode = smp2p_read(conTxt, &recvData);

    if(SMP2P_STATUS_SUCCESS == retCode){
       PM_MSG_1( HIGH, "sns_pm_smp2p_task: Data Read: %d", recvData );
       currState = recvData;
       sns_pm_smp2p_cb(currState);
    }
    else{
      PM_MSG_1( ERROR, "Error: Data Read Failed:%d", retCode );
    }
  }
}

/*===========================================================================

FUNCTION sns_pm_smp2p_init

DESCRIPTION
  This function initializes SMP2P internal thread on sensors side which is
  needed for listening to external processor's activity. This is called in
  boot up init seqeunce.

===========================================================================*/
sns_err_code_e sns_pm_smp2p_init(void)
{
  uint8_t errOS;

  PM_MSG_0( LOW, "sns_pm_smp2p_init" );

  errOS = sns_os_task_create_ext( sns_pm_smp2p_task, NULL,
      &sns_pm_smp2p_task_stk[ SNS_MODULE_STK_SIZE_DSPS_SMP2P - 1 ], SNS_MODULE_PRI_DSPS_SMP2P,
      SNS_MODULE_PRI_DSPS_SMP2P, &sns_pm_smp2p_task_stk[0], SNS_MODULE_STK_SIZE_DSPS_SMP2P,
      (void *)0, OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR,
      (uint8_t*)("SNS_SMP2P") );

  SNS_ASSERT( OS_ERR_NONE == errOS );
  return SNS_SUCCESS;
}
