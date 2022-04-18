/*==============================================================================
  FILE:         sleep_lpi.c
 
  OVERVIEW:     This file provides the implementation of the sleep LPI node.

  DEPENDENCIES: None

                Copyright (c) 2016 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/sleep2.0/src/npa_nodes/sleep_lpi.c#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include "comdef.h"
#include "npa.h"
#include "CoreVerify.h"
#include "sleep_lpr.h"
#include "sleep_lpri.h"
#include "sleep_log.h"
#include "SleepLPI_lookup_table.h"

/*==============================================================================
                              INTERNAL FUNCTIONS
 =============================================================================*/
/*
 * Internal function called by sleep framework to register LPI which are
 * defined by build time synthesis tool.
 *
 * @param resource: Pointer to Low Power Island Resource.
 * @param client_handle: NPA client handle which will be used to issue
 *                       request for above LPR.
 */
static void sleepLPI_defineInternal(sleep_lpr         *resource, 
                                    npa_client_handle clientHandle)
{
  /* This function foists the registration off to the resource itself, which 
   * does the work inside the resource lock */
  lpr_registration_info info;
  npa_query_type        q;

  info.lpr          = resource;
  info.client       = clientHandle;
  q.type            = NPA_QUERY_TYPE_REFERENCE;
  q.data.reference  = &info;

  /* Use the LPR framework for now */
  CORE_VERIFY(NPA_QUERY_SUCCESS == npa_query_by_client(clientHandle, 
                                                       SLEEP_LPR_REGISTER, 
                                                       &q));
  return;
}
/*==============================================================================
                              EXTERNAL FUNCTIONS
 =============================================================================*/
/*
 * sleepLPI_define
 */
int sleepLPI_define(const char *name, npa_client_handle clientHandle)
{
  int     result = SLEEP_LPR_FAILED;
  int     nCount = sizeof(SleepLPI_LookupTable) / sizeof(SleepLPI_LookupTable[0]);
  int     nLPI   = 0;

  if(NULL != name)
  {
    for(nLPI = 0; result == SLEEP_LPR_FAILED && nLPI < nCount; nLPI++)
    {
      if(strcmp(name, SleepLPI_LookupTable[nLPI]->resource_name) == 0)
      {
        sleepLPI_defineInternal(SleepLPI_LookupTable[nLPI], clientHandle);
        result = SLEEP_LPR_SUCCESS;
      }
    }
  }

  if(SLEEP_LPR_FAILED == result)
  {
     sleepLog_printf(SLEEP_LOG_LEVEL_WARNING, 1, 
                     "WARNING (message: \"Sleep LPI not found\") "
                     "(LPI Name: \"%s\")", name);
  }

  return result;
}

