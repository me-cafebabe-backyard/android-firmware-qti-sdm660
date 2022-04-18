/** vi: tw=128 ts=3 sw=3 et :
@file rcinit_rex_task.c
@brief This file contains the API for the Run Control Framework, API 2.1
*/
/*=============================================================================
NOTE: The @brief description above does not appear in the PDF.
The tms_mainpage.dox file contains the group/module descriptions that
are displayed in the output PDF generated using Doxygen and LaTeX. To
edit or update any of the group/module text in the PDF, edit the
tms_mainpage.dox file or contact Tech Pubs.
===============================================================================*/
/*=============================================================================
Copyright (c) 2015 Qualcomm Technologies, Inc.
All Rights Reserved.
Confidential and Proprietary - Qualcomm Technologies, Inc.
===============================================================================*/
/*=============================================================================
Edit History
$Header: //components/rel/core.qdsp6/1.0.c2/debugtools/rcinit/src/rcinit_rex_task.c#1 $
$DateTime: 2020/02/10 01:57:30 $
$Change: 22511909 $
$Author: pwbldsvc $
===============================================================================*/

#if !defined(RCINIT_EXCLUDE_TRACER_SWEVT)
#include "tracer.h"
#include "rcinit_tracer_swe.h"
#endif

#if !defined(RCINIT_EXCLUDE_MSG_SWEVT)
#include "msg.h"
#endif

#include "rcinit_dal.h"
#include "rcinit_rex.h"
#include "rcinit_internal.h"
#include "sys_m_internal.h"

//static DALSYSEventHandle hEventCoreStarted;

/*===========================================================================

 FUNCTION rcinit_task

 DESCRIPTION
 hlos task thread to process sequnece groups

 DEPENDENCIES
 none

 RETURN VALUE
 none

 SIDE EFFECTS
 none

 ===========================================================================*/

void rcinit_task(unsigned long arg_p)                                            // REX API
{
   RCEVT_SIGEX_SIGDAL sig;
   DALSYSEventHandle hEventShutdownTask;

   rcinit_internal.process_state = rcinit_process_init;

   DALSYS_InitMod(NULL);                                                         // prerequsite dependency

   if (DAL_SUCCESS != DALSYS_EventCreate(DALSYS_EVENT_ATTR_NORMAL, &hEventShutdownTask, NULL))
   {
      ERR_FATAL("create event shutdown", 0, 0, 0);
   }

   // rcinit init
   rcinit_init();

   // register as client to system monitor
   sig.signal = hEventShutdownTask;
   if (rcevt_register_sigex_name(SYS_M_SHUTDOWN, RCEVT_SIGEX_TYPE_SIGDAL, &sig)) {;}

   // DAL DEPENDS ON REX
   //if (DAL_SUCCESS != DALSYS_EventCtrl(hEventCoreStarted, DALSYS_EVENT_CTRL_TRIGGER))
   //{
   //ERR_FATAL("fail corestarted trigger", 0, 0, 0);
   //}

#if defined(RCINIT_TRACER_SWEVT)
   tracer_event_simple(RCINIT_SWE_INITGROUPS);
#endif
#if !defined(RCINIT_EXCLUDE_MSG_SWEVT)
   MSG(MSG_SSID_TMS, MSG_LEGACY_HIGH, "group initializations end");
#endif

   // signal for observers
   if (rcecb_signal_name(RCINIT_RCECB_INITGROUPS)) {;}
   if (rcevt_signal_name(RCINIT_RCEVT_INITGROUPS)) {;}

   rcinit_internal.process_state = rcinit_process_blocking;

   // block for system monitor notification
   if (NULL == hEventShutdownTask || DAL_SUCCESS != DALSYS_EventWait(hEventShutdownTask))
   {
      ERR_FATAL("task wait event shutdown", 0, 0, 0);
   }

   rcinit_internal.process_state = rcinit_process_running;

   // unregister further system monitor notifications
   if (rcevt_unregister_sigex_name(SYS_M_SHUTDOWN, RCEVT_SIGEX_TYPE_SIGDAL, &sig)) {;}

   if (NULL == hEventShutdownTask || DAL_SUCCESS != DALSYS_EventCtrl(hEventShutdownTask, DALSYS_EVENT_CTRL_RESET))
   {
      ERR_FATAL("task wait event shutdown", 0, 0, 0);
   }

   if (NULL == hEventShutdownTask || DAL_SUCCESS != DALSYS_DestroyObject(hEventShutdownTask))
   {
      ERR_FATAL("create event shutdown", 0, 0, 0);
   }

#if defined(RCINIT_TRACER_SWEVT)
   tracer_event_simple(RCINIT_SWE_TERMGROUPS);
#endif
#if !defined(RCINIT_EXCLUDE_MSG_SWEVT)
   MSG(MSG_SSID_TMS, MSG_LEGACY_HIGH, "group terminations begin");
#endif

   // signal for observers
   if (rcevt_signal_name(RCINIT_RCEVT_TERMGROUPS)) {;}
   if (rcecb_signal_name(RCINIT_RCECB_TERMGROUPS)) {;}

   // rcinit termination
   rcinit_term();

   // client ack to system monitor
   if (rcevt_signal_name(SYS_M_SHUTDOWN_ACK)) {;}

   // termination
   rcinit_internal.process_state = rcinit_process_term;

   if (arg_p) {;}
}

void rcinit_fail(void)
{
   static unsigned long unused = 0;

   for (;;)                                                                      // punt, no exception handler
   {
   }

   /* NOTREACHED */

   if (unused) {;}
}

#define dwMaxNumEvents        1
#define wlPriority            rcinit_lookup_prio("rcinit")
#define wlStackSize           rcinit_lookup_stksz("rcinit")

void bootstrap_rcinit_task(void)
{
   static rex_tcb_type tcb;                                                      // static allocation for boot strapping
   static rex_stack_word_type stack[6144 / sizeof(rex_stack_word_type)];         // static allocation for boot strapping

   // Initialize NHLOS Layers Needed

   // Must initialize the kernel REX API Layer; its not done by kernel
   // even on PL where the interface is available, and we are already
   // multi-tasking at this point by the NHLOS.

#if defined(FEATURE_QURT)

   rex_init(REX_ANY_CPU_AFFINITY_MASK, NULL, 0, &tcb,
            stack, sizeof(stack) / sizeof(rex_stack_word_type), wlPriority,
            rcinit_task, 0);

#else // defined(FEATURE_L4) || defined(FEATURE_REX)

   rex_init(NULL, 0, &tcb,
            stack, sizeof(stack) / sizeof(rex_stack_word_type), wlPriority,
            rcinit_task, 0);

#endif

   // Block for RCINIT Framework Startup to Complete

   //if ((DAL_SUCCESS != DALSYS_EventCreate(DALSYS_EVENT_ATTR_NORMAL, &hEventCoreStarted, NULL)) ||
   //(DAL_SUCCESS != DALSYS_EventWait(hEventCoreStarted)))
   //{
   //ERR_FATAL("task wait event shutdown", 0, 0, 0);
   //}
}
