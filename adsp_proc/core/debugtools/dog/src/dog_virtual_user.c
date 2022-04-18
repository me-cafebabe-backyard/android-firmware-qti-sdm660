/*
#============================================================================
#  Name:
#    dog_virtual_user.c 
#
#  Description:
#    Virtual watchdog component in USER-PD
#
# Copyright (c) 2015-2016 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
#============================================================================
*/

#include "stdarg.h"
#include "stdlib.h"
#include <stringl/stringl.h>
#include "comdef.h"
#include "err.h"
#include "qurt.h"
#include "tms_utils_msg.h"
#include "tms_utils.h"
#include "tms_dll_api.h"
#include "timer.h"
#include "rcecb.h"
#include "rcinit.h"
#include "servreg_locator.h"

#include "dog_virtual.h"
#include "dog_hal.h"

/* sec period for dog_virtual_StartupGraceFailureCb */
#define DOG_STARTUP_GRACE_TIMER_PERIOD_SEC  40
#define DOG_VIRTUAL_TASK_NAME               "dog_vir_rtask"

static struct
{
   qurt_thread_t tid;
} dog_virtual_user_task_internal;

/* If this flag is set to TRUE, 40sec startup gracetimer for user_pd will not be initialized.
*  This flag should be set to TRUE only for DEBUG purposes eg TRACE32 Instrument to Disable hw wdog At Runtime
*/
static volatile boolean dog_disable_user_startup_timer = FALSE;

int32_t dog_qdi_client_handle = -1 ;

/* One time Timer coupled tightly to RCINIT_RCECB_INITGROUPS.
 * A fail safe mechanism to detect RCINIT groups initialization has failed.
 * Its a non deferrable timer. */
static timer_type dog_startup_grace_timer;

/* Static functions in this file */
static void dog_virtual_report(void);
static void dog_virtual_StartupSuccessCb(void);
static void dog_virtual_StartupGraceFailureCb(timer_cb_data_type);

/** =====================================================================
 * Function:
 *     dog_qdi_invoke_pong
 *
 * Description:
 *     Invoke the qdi method to report back to the virtual dog
 *
 * Parameters:
 *
 * Returns:
 *    Refer to the enum DOG_VIRTUAL_RESULT for list of possible results
 * =====================================================================  */
DOG_VIRTUAL_RESULT dog_qdi_invoke_hb_register(void)
{
   int ret = -1;

   ret = qurt_qdi_handle_invoke(dog_qdi_client_handle, DOG_QDI_HB_REGISTER);

   if(-1 != ret)
   {
      return DOG_VIRTUAL_SUCCESS;
   }
   else
   {
      return DOG_VIRTUAL_FAILURE;
   }
}

/** =====================================================================
 * Function:
 *     dog_qdi_invoke_worker_wait
 *
 * Description:
 *     Invoke the qdi method to wait for the dog hb root signal
 *
 * Parameters:
 *
 * Returns:
 *    Refer to the enum DOG_VIRTUAL_RESULT for list of possible results
 * =====================================================================  */
DOG_VIRTUAL_RESULT dog_qdi_invoke_worker_wait(uint32_t * remote_mask)
{
   int ret = -1;

   ret = qurt_qdi_handle_invoke(dog_qdi_client_handle, DOG_QDI_WAIT, remote_mask);

   if(-1 != ret)
   {
      return DOG_VIRTUAL_SUCCESS;
   }
   else
   {
      return DOG_VIRTUAL_FAILURE;
   }
}

/** =====================================================================
 * Function:
 *     dog_qdi_invoke_pong
 *
 * Description:
 *     Invoke the qdi method to report back to the virtual dog
 *
 * Parameters:
 *
 * Returns:
 *    Refer to the enum DOG_VIRTUAL_RESULT for list of possible results
 * =====================================================================  */
DOG_VIRTUAL_RESULT dog_qdi_invoke_pong(void)
{
   int ret = -1;

   ret = qurt_qdi_handle_invoke(dog_qdi_client_handle, DOG_QDI_PONG);

   if(-1 != ret)
   {
      return DOG_VIRTUAL_SUCCESS;
   }
   else
   {
      return DOG_VIRTUAL_FAILURE;
   }
}

/** =====================================================================
 * Function:
 *     dog_qdi_invoke_close
 *
 * Description:
 *     Closes the specified driver, releasing any resources associated with the open driver
 *
 * Parameters:
 *     handle : handle to be released
 *
 * Returns:
 *     Refer to the enum DOG_VIRTUAL_RESULT for list of possible results
 * =====================================================================  */
DOG_VIRTUAL_RESULT dog_qdi_invoke_close(void)
{
   int ret = -1;

   ret = qurt_qdi_close(dog_qdi_client_handle);

   if(-1 != ret)
   {
      return DOG_VIRTUAL_SUCCESS;
   }
   else
   {
      return DOG_VIRTUAL_FAILURE;
   }
}

/** =====================================================================
* Function:
*     dog_virtual_report
*
* Description:
*       hb driven function for virtual dog
*
* Parameters:
*     none
*
* Returns:
*     none
* =====================================================================  */
static void dog_virtual_report(void)
{
   if(DOG_VIRTUAL_FAILURE == dog_qdi_invoke_pong())
   {
      ERR_FATAL( "DOG_VIRTUAL: User-pd dog report failed", 0, 0, 0);
   }
   return;
}

/** =====================================================================
* Function:
*     dog_virtual_StartupSuccessCb
*
* Description:
*   This function is called after rc group initialization is done.  
*   It clears the timer and de-registers with RCvent for any future events.
*
* Parameters:
*     none
*
* Returns:
*     none
* =====================================================================  */
static void dog_virtual_StartupSuccessCb(void)
{
   time_timetick_type remaining_time= 0;

   /* Clear the timer */
   timer_stop(&dog_startup_grace_timer, T_NONE, &remaining_time);

   /* Undefine the timer */
   timer_undef(&dog_startup_grace_timer);

   /* Unregister with RC events once RCECB supports un-registering in the cb handler */
   //rcecb_unregister_name(RCINIT_RCECB_INITGROUPS, dog_virtual_StartupSuccessCb);
}

/** =====================================================================
* Function:
*     dog_virtual_StartupGraceFailureCb
*
* Description:
*   This function is called when the dog start up grace timer expires.  
*   It results in Error fatal.
*
* Parameters:
*     none
*
* Returns:
*     none
* =====================================================================  */
static void dog_virtual_StartupGraceFailureCb(timer_cb_data_type unused)
{
   time_timetick_type remaining_time= 0;

   /* Clear the timer */
   timer_stop(&dog_startup_grace_timer, T_NONE, &remaining_time);

   /* Undefine the timer */
   timer_undef(&dog_startup_grace_timer);

   ERR_FATAL("USER-PD DOG detects stalled initialization, triage with IMAGE OWNER", 0, 0, 0);
}

/** =====================================================================
 * Task:
 *
 * Description:
 *
 * Parameters:
 *     None
 * 
 * Returns:
 *     None
 * =====================================================================  */
static void dog_virtual_user_task(void *argv __attribute__((unused)))
{
   uint32_t mask = 0;

   dog_qdi_invoke_hb_register();

   /* Task forever loop */
   for (;;)
   {
      dog_qdi_invoke_worker_wait(&mask);

      if(mask & DOG_VIR_SIGNAL_MASK)
      {
         dog_virtual_report();
         if(rcevt_signal_name(DOG_HB_EVENT)){;}
         TMS_MSG_LOW( "DOG_QDI: reported back to root and signaled user dog_hb \n");
      }
   }
}

/** =====================================================================
 * Function:
 *     dog_qdi_init
 *
 * Description:
 *     Initialization function in user pd.
 *     Function to obtain a QDI handle given the qdi device name.
 *
 * Parameters:
 *     None
 *
 * Returns:
 *     None
 * =====================================================================  */
DLL_API_GLOBAL void dog_qdi_init(void)
{
   char* domain = NULL;
   int len = 0;
   qurt_thread_attr_t attr;
   static unsigned long stack[DOG_VIRTUAL_TASK_STACK/sizeof(unsigned long)];

   domain = servreg_get_local_domain();

   if (NULL != domain)
   {
      len = strlen(domain) + 1;
      dog_qdi_client_handle = qurt_qdi_open(DOG_QDI_DEVICE, domain, len);
   }

   if (0 <= dog_qdi_client_handle)
   {
      TMS_MSG_HIGH_1("DOG_QDI: user-pd dog_qdi_init() PASS , handle = %d\n", dog_qdi_client_handle);
   }
   else
   {
      ERR_FATAL( "DOG_QDI: user-pd dog_qdi_init failed", 0, 0, 0);
   }

   qurt_thread_attr_init(&attr);
   qurt_thread_attr_set_name(&attr, DOG_VIRTUAL_TASK_NAME);
   qurt_thread_attr_set_stack_addr(&attr, stack);
   qurt_thread_attr_set_stack_size(&attr, sizeof(stack));
   qurt_thread_attr_set_priority(&attr, qurt_thread_get_priority(qurt_thread_get_id()) - 1);
   qurt_thread_attr_set_affinity(&attr, QURT_THREAD_ATTR_AFFINITY_DEFAULT);

   qurt_thread_create(&dog_virtual_user_task_internal.tid, &attr, dog_virtual_user_task, NULL);

   if(dog_disable_user_startup_timer != TRUE)
   {
      /* Event indicates startup completes */
      rcecb_register_name(RCINIT_RCECB_INITGROUPS, dog_virtual_StartupSuccessCb); 

      /* Define watchdog timer */
      if(TE_SUCCESS != timer_def_osal(&dog_startup_grace_timer, 
                                     &timer_non_defer_group, 
                                     TIMER_FUNC1_CB_TYPE, 
                                     dog_virtual_StartupGraceFailureCb, NULL ))
      {
       ERR_FATAL("Dog startup grace Timer def failed", 0, 0, 0);
      }

      /* Set watchdog timer */
      if(TE_SUCCESS != timer_set_64(&dog_startup_grace_timer, 
                                   DOG_STARTUP_GRACE_TIMER_PERIOD_SEC, 
                                   0, T_SEC ))
      {
       ERR_FATAL("Dog startup grace Timer set failed", 0, 0, 0);
      }
   }
}


