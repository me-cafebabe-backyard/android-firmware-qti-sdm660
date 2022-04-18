/*========================================================================

*//** @file qurt_elite_globalstate.cpp
This file contains the global state structure for the qurt_elite environment.
This state includes system-wide information such as number of active
threads, malloc counters, etc..

Copyright (c) 2010,2018 QUALCOMM Technologies, Inc.  All Rights Reserved. 
QUALCOMM Technologies, Inc Proprietary. Export of this technology or software 
is regulated by the U.S. Government, Diversion contrary to U.S. law prohibited.

*//*====================================================================== */

/*========================================================================
Edit History

$Header: //components/rel/avs.adsp/2.8/elite/qurt_elite/src/qurt_elite_globalstate.cpp#5 $

when       who     what, where, why
--------   ---     -------------------------------------------------------
02/04/10   mwc     Created file.

========================================================================== */


/* =======================================================================
INCLUDE FILES FOR MODULE
========================================================================== */
#include "qurt_elite.h"
#include "DALSys.h"
#include "DALSysTypes.h"
#include "DALPropDef.h"
#include "DDIChipInfo.h"
#include "qurt_elite_adsppm_wrapper.h"

/*--------------------------------------------------------------*/
/* Macro definitions                                            */
/* -------------------------------------------------------------*/

/* -----------------------------------------------------------------------
** Constant / Define Declarations
** ----------------------------------------------------------------------- */

/* =======================================================================
**                          Function Definitions
** ======================================================================= */

//***************************************************************************
// Global state structure for resource monitoring & debugging
//***************************************************************************
qurt_elite_globalstate_t qurt_elite_globalstate;

void qurt_elite_globalstate_init(void)
{
   qurt_elite_memory_stats_init();

   // set all fields to 0.
   qurt_elite_globalstate.nSimulatedMallocFailCount = -1;
   qurt_elite_atomic_set(&qurt_elite_globalstate.nMsgQs, 0);
   qurt_elite_atomic_set(&qurt_elite_globalstate.nMemRegions, 0);
   qurt_elite_globalstate.pMemoryMapClientList = NULL;
   qurt_elite_mutex_init(&qurt_elite_globalstate.mutex);


   // by default, do not log queues.
   qurt_elite_globalstate.bEnableQLogging = 0;

   // Initialise the static svc cmd Q with NULL
   qurt_elite_globalstate.pAdmStatSvcCmdQ = NULL;
   qurt_elite_globalstate.pAfeStatSvcCmdQ = NULL;
   qurt_elite_globalstate.pVoiceTimerCmdQ = NULL;
   qurt_elite_globalstate.pAvcsCmdQ = NULL;
   qurt_elite_globalstate.pVPMSvcCmdQ = NULL;

   for (uint32_t i=0; i < ASM_NUM_QUEUES; i++)
   {
      qurt_elite_globalstate.pAsmSessionCmdQ[i] = NULL;
   }
   qurt_elite_globalstate.uSvcUpStatus = 0;
   qurt_elite_globalstate.uApStatSvcUpStatus = 0;

   //clear the thread context structures
   qurt_elite_thread_list_init();

   // initialize qurt_elite heap manager heap table entries
   qurt_elite_heap_table_init();

   (void)qurt_elite_adsppm_wrapper_create();
}

void qurt_elite_globalstate_deinit(void)
{
   // clean up all resources.
   (void)qurt_elite_adsppm_wrapper_destroy();

   qurt_elite_mutex_lock(&qurt_elite_globalstate.mutex);

   qurt_elite_memorymap_client_t *pClientNode = qurt_elite_globalstate.pMemoryMapClientList;
   qurt_elite_memorymap_node_t *pMemoryMapNode;

   //loop through all clients
   while (pClientNode) {
      qurt_elite_globalstate.pMemoryMapClientList = pClientNode->pNext;

      //loop through all memory regions of a client
      qurt_elite_mutex_lock(&(pClientNode->mClientMutex));
      pMemoryMapNode = pClientNode->pMemMapListNode;
      while (pMemoryMapNode) {
         pClientNode->pMemMapListNode = pMemoryMapNode->pNext;
         qurt_elite_memory_aligned_free(pMemoryMapNode);
         pMemoryMapNode = pClientNode->pMemMapListNode;
      }
      qurt_elite_mutex_unlock(&(pClientNode->mClientMutex));

      qurt_elite_memory_free(pClientNode);
      pClientNode = qurt_elite_globalstate.pMemoryMapClientList;
   }
   qurt_elite_atomic_set(&qurt_elite_globalstate.nMemRegions, 0);
   qurt_elite_mutex_unlock(&qurt_elite_globalstate.mutex);
   qurt_elite_mutex_destroy(&qurt_elite_globalstate.mutex);

   qurt_elite_memory_stats_deinit();


}



