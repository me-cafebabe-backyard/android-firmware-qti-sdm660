/** vi: tw=128 ts=3 sw=3 et
@file coremain.c
@brief This file contains the API details for the COREMAIN/MAIN
*/
/*=============================================================================
NOTE: The @brief description above does not appear in the PDF.
The tms_mainpage.dox file contains the group/module descriptions that
are displayed in the output PDF generated using Doxygen and LaTeX. To
edit or update any of the group/module text in the PDF, edit the
tms_mainpage.dox file or contact Tech Pubs.
===============================================================================*/
/*=============================================================================
Copyright (c) 2015-16 Qualcomm Technologies Incorporated.
All rights reserved.
Qualcomm Confidential and Proprietary
=============================================================================*/
/*=============================================================================
Edit History
$Header: //components/rel/core.qdsp6/1.0.c2/debugtools/task/src/coremain.c#1 $
$DateTime: 2020/02/10 01:57:30 $
$Change: 22511909 $
$Author: pwbldsvc $
===============================================================================*/

#include "rcinit_dal.h"
#include "qurt.h"
#include "err.h"

void bootstrap_exception_handler(void); // forward reference
void bootstrap_rcinit_task(void); // forward reference

#ifdef FEATURE_TIMESTAMP
#include "../../engg_timestamp.h"
#include "../../qcom_timestamp.h"
#define DBG_MED_PRIO   MSG_LEGACY_MED    /**< Medium priority debug message. */
#endif

/**
API, coremain_main
@return None.
*/
void coremain_main(void)
{
   DALSYS_InitMod(NULL);               // no error return

   bootstrap_exception_handler();      // creates context for error processing

   bootstrap_rcinit_task();            // creates context for rcinit processing
}

#if !defined(TASK_EXCLUDE_MAIN)
/**
API, main
@return None.
*/
int main(void)
{
   DALSYSEventHandle hEvent;

   coremain_main(); // when main is not delivered here, this is the entry to start cbsp

#ifdef FEATURE_TIMESTAMP
   qurt_printf("\n**********************************\n* DSP Image Creation Date: %s\n*******************************************************\n",engg_timestampstring);
   MSG_1(MSG_SSID_QDSP6, DBG_MED_PRIO, "Engineering Image Creation Date: %s\n", engg_timestampstring);
   MSG_1(MSG_SSID_QDSP6, DBG_MED_PRIO, "Qcom Image Creation Date: %s\n", qcom_timestampstring);
#endif

   // Block Forever

   if (DAL_SUCCESS != DALSYS_EventCreate(DALSYS_EVENT_ATTR_NORMAL, &hEvent, NULL))
   {
      ERR_FATAL("DALSYS_EventCreate in main() has unexpectedly failed.", 0, 0, 0);
   }

   if (DAL_SUCCESS != DALSYS_EventWait(hEvent))
   {
      ERR_FATAL("DALSYS_EventWait in main() has unexpectedly failed.", 0, 0, 0);
   }

   ERR_FATAL("DALSYS_EventWait in main() has unexpectedly returned.", 0, 0, 0);

   /* NOTREACHED */

   return (0);
}
#endif

