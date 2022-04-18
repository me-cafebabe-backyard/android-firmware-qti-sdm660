/*==============================================================================
  FILE:         wakeup_node.c
  
  OVERVIEW:     This file provides the wakeup NPA node definitions

  DEPENDENCIES: None

                Copyright (c) 2015-2016 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/sleep2.0/src/npa_nodes/wakeup_node.c#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#ifndef FEATURE_SLEEP_NO_WAKEUP_NODE
#include <stdint.h>
#include <stdlib.h>
#include "comdef.h"
#include "CoreVerify.h"
#include "CoreTime.h"
#include "sleep_npa.h"
#include "sleep_log.h"
#include "npa_resource.h"
#include "sleep_utils.h"

/*==============================================================================
                             INTERNAL VARIABLES
 =============================================================================*/
/* Minimum absolute of the set of clients on wakeup node resource */
static uint64 g_wakeupResourceMin64;

/* Client handle whose request is the currently set minimum */
static npa_client *g_wakeupResourceMinClientHandle;

/*==============================================================================
                               INTERNAL TYPES
 =============================================================================*/
/* npa_user_data is defined as void* and wakeup node defines this struct to 
 * send as resource_data */
typedef struct wakeupResourceData_s
{
  uint64 data;
}wakeupUserData;

/*==============================================================================
                              INTERNAL FUNCTIONS
 =============================================================================*/
/**
 * sleepWakeupNode_aggregate
 *
 * @brief Aggregates minimum of all client requests
 *
 * @param resource: The NPA resource being requested (should be 
 *                  /core/cpu/wakeup).
 * @param client: The handle to the client registered to the 
 *                resource.
 *
 * @return Returns the new minimum of the resource 
 */
static void sleepWakeupNode_aggregate(npa_resource  *resource, 
                                      npa_client    *client )
{
  wakeupUserData    *dataPtr;
  npa_client_handle activeClient = resource->clients;

  /* First reset minimum and minimum client handle */
  g_wakeupResourceMin64           = UINT64_MAX;
  g_wakeupResourceMinClientHandle = NULL;

  /* Traverse through the list of clients to find the minimum */
  while(activeClient != NULL)
  {
    dataPtr = (wakeupUserData *)activeClient->resource_data;

    /* Get the minimum value from clients */
    if(dataPtr->data < g_wakeupResourceMin64)
    {
      g_wakeupResourceMin64           = dataPtr->data;
      g_wakeupResourceMinClientHandle = activeClient;
    }
    activeClient = activeClient->next;
  }

  if(g_wakeupResourceMin64 <= CoreTimetick_Get64())
  {
    /* Node clients are responsible to cancel requests placed on node
     * when use-case completes and cannot have requests that are in past */
    sleepLog_printf(SLEEP_LOG_LEVEL_INFO, 1, 
                    "Client (handle: 0x%08x) - request on "
                    "wakeup node is in the past",
                    g_wakeupResourceMinClientHandle);
  }

  return;
}

/**
 * sleepWakeupNode_update
 *
 * @brief This function is invoked by the /core/cpu/wakeup resource when a 
 *        client request is made.
 *
 * Its job is to compute the expected wakeup time based on input from clients
 * so that sleep can better estimate what modes it should enter. 
 *
 * @param resource: The NPA resource being requested (should be 
 *                  /core/cpu/wakeup).
 * @param client: The handle to the clients registered to the 
 *                resource.
 *
 * @return Returns the new state of the resource ('zero' until 64-bit NPA
 *         support becomes available).
 */
static npa_resource_state sleepWakeupNode_update(npa_resource       *resource,
                                                 npa_client_handle  client)
{
  wakeupUserData      *clientReq;
  npa_resource_state  newReq;
  uint64              now = CoreTimetick_Get64();

  CORE_VERIFY_PTR(resource);
  CORE_VERIFY_PTR(client);

  /* Get the relative requested duration */
  newReq = NPA_PENDING_REQUEST(client).state;

  /* get the address where 64-bit address is/should be placed */
  clientReq = (wakeupUserData *)client->resource_data;

  /* Check if this is a cancel request or destroy client request
   * - in both of those cases, the requested value is sent as zero */
  if(0 == newReq)
  {
    /* Set MAX for the current client's data */
    clientReq->data = UINT64_MAX;
  }
  else
  {
    /* add current time and store into data field.
     * Since newReq is a offset from the client, use the time from the beginning
     * of this call rather than the current time at this point */
    clientReq->data = (uint64)(newReq + now);
  }

  if(clientReq->data < g_wakeupResourceMin64)
  {
    /* Find minimum duration at which wakeup needs to occur. If
     * first client or client's request is less than current minimum,
     * set client as new minimum */
    g_wakeupResourceMin64           = clientReq->data;
    g_wakeupResourceMinClientHandle = client;
  }
  else if(g_wakeupResourceMinClientHandle == client)
  {
    /* Re-aggregate the new minimum */
    sleepWakeupNode_aggregate(resource, client);
  }

  return 0;
}

/**
 * sleepWakeupNode_createClientFcn
 *
 * @brief In order to store values into the resource-data field, that will
 *        need to be assigned necessary memory
 *
 * Allocating memory to store address to 64-bit absolute time
 *
 * @param client: The handle to the client registered to the 
 *                resource.
 *
 * @return None
 */
static void sleepWakeupNode_createClientFcn(npa_client *client)
{
  wakeupUserData *clientReq;

  /* Allocate storage space because NPA discards the data otherwise */
  client->resource_data = (wakeupUserData *)malloc(sizeof(wakeupUserData));
  
  CORE_VERIFY_PTR(client->resource_data);

  /* get the address where 64-bit address is/should be placed & set to max */
  clientReq       = (wakeupUserData *)client->resource_data;
  clientReq->data = UINT64_MAX;

  return;
}

/**
 * sleepWakeupNode_destroyClientFcn
 *
 * @brief Free memory allocated to resource-data if client requests
 *        itself to be destroyed via npa_destroy_client
 *
 * Calling into npa_destroy_client would make NPA FW to call into the
 * plugin's destroy client fcn
 *
 * @param client: The handle to the client registered to the 
 *                resource.
 *
 * @return None
 */
static void sleepWakeupNode_destroyClientFcn(npa_client *client)
{
  /* Free the memory allocated for the client's data */
  free(client->resource_data);
  return;
}

/**
 * sleepWakeupNode_driver
 *
 * @brief Driver function for the /core/cpu/wakeup resource that updates its
 *        state.
 *
 * @param resource: Pointer to the /core/cpu/wakeup resource
 * @param client: Client of the resource
 * @param state: state of the resource.
 *
 * @return state of the resource.
 */
static npa_resource_state sleepWakeupNode_driver(npa_resource       *resource,
                                                 npa_client         *client,
                                                 npa_resource_state state)
{
  CORE_VERIFY_PTR(resource);
  CORE_VERIFY_PTR(client);

  if(NPA_CLIENT_INITIALIZE == client->type)
  {
    resource->internal_state[0]     = (npa_resource_state)NULL;
    g_wakeupResourceMin64           = UINT64_MAX;
    g_wakeupResourceMinClientHandle = NULL;
    return 0;
  }

  return state;
}

/**
 * sleepWakeupNode_query
 *
 * @brief Query function for the /core/cpu/wakeup resource that returns
 *        soft wakeup time based on the query id
 *
 * @param resource:     Resource to which we are making request (wakeup node here).
 * @param queryID:      ID for the query being made.
 * @param queryResult:  Stores to the result of the query
 *
 * @return Returns the status for the query (i.e. successfully handled or 
 *         unsupported).
 */
static npa_query_status sleepWakeupNode_query(struct npa_resource  *resource,
                                              unsigned int         queryID, 
                                              npa_query_type       *queryResult)
{
  npa_query_status status = NPA_QUERY_SUCCESS;

  CORE_VERIFY_PTR(resource);
  CORE_VERIFY_PTR(queryResult);

  switch(queryID)
  {
    case SLEEP_WAKEUP_QUERY_TYPE:
    {
      uint64 now = CoreTimetick_Get64();

      /* return 32-bit value as soft-duration */
      queryResult->type = NPA_QUERY_TYPE_VALUE;

      if(g_wakeupResourceMin64 == UINT64_MAX)
      {
        /* return query result as UINT32_MAX */
        queryResult->data.value = UINT32_MAX;
      }
      else if(g_wakeupResourceMin64 <= now)
      {
        /* Node clients are responsible to cancel requests placed on node
         * when use-case completes, and cannot have requests in past. */
        sleepLog_printf(SLEEP_LOG_LEVEL_INFO, 1, 
                        "Client (handle: 0x%08x) "
                        "- request on wakeup node is in the past",
                        g_wakeupResourceMinClientHandle);

        /* return zero as soft-duration */
        queryResult->data.value = 0;
      }
      else
      {
        queryResult->data.value = safe_unsigned_truncate(g_wakeupResourceMin64 - now); 
      }
      break;
    }

    case SLEEP_WAKEUP_QUERY_TYPE_ABS:
    {
      /* Return 64-bit value as soft-duration */
      queryResult->type = NPA_QUERY_TYPE_VALUE64;

      /* Set return value to minimum wakeup time */
      queryResult->data.value64 = g_wakeupResourceMin64;

      /* Verify that the minimum is in the future */
      if (g_wakeupResourceMin64 <= CoreTimetick_Get64())
      {
        /* Node clients are responsible to cancel requests placed on node
         * when use-case completes, and cannot have requests in past. */
        sleepLog_printf(SLEEP_LOG_LEVEL_INFO, 1, 
                        "Client (handle: 0x%08x) " 
                        "- request on ABS wakeup node is in the past",
                         g_wakeupResourceMinClientHandle);
      }
      break;
    }

    default:
    {
      status = NPA_QUERY_UNSUPPORTED_QUERY_ID;
      break;
    }
  }

  return status;
}

/*==============================================================================
                              WAKEUP NODE DEFINITION
 =============================================================================*/
/* The plugin for the /core/cpu/wakeup resource. */
const npa_resource_plugin g_sleepWakeupPlugin = 
{
  sleepWakeupNode_update,           /* Update function */
  NPA_CLIENT_REQUIRED,              /* Supported client types */
  sleepWakeupNode_createClientFcn,  /* Create client function */
  sleepWakeupNode_destroyClientFcn  /* Destroy client function */
};

/* Expected wakeup pseudo-resource. */
static npa_resource_definition g_sleepWakeupResource[] = 
{ 
  {  
    SLEEP_WAKEUP_NODE_NAME,                    /* Name */
    "ticks",                                   /* Units */
    NPA_MAX_STATE,                             /* Max State */
    &g_sleepWakeupPlugin,                      /* Plugin */
    NPA_RESOURCE_INTERPROCESS_ACCESS_ALLOWED,  /* Attributes */
    NULL,                                      /* User Data */
    sleepWakeupNode_query                      /* Query Function */
  }
};

/**
 * @brief g_sleepWakeupNode
 *
 * Definition of the expected wakeup node. 
 */
static npa_node_definition g_sleepWakeupNode = 
{ 
  "/node/core/cpu/wakeup",      /* name */
  sleepWakeupNode_driver,       /* driver_fcn */
  NPA_NODE_DEFAULT,             /* attributes */
  NULL,                         /* data */
  NPA_EMPTY_ARRAY,
  NPA_ARRAY(g_sleepWakeupResource)
};

#endif /* !FEATURE_SLEEP_NO_WAKEUP_NODE */

/*==============================================================================
                              EXTERNAL FUNCTIONS
 =============================================================================*/
void sleepWakeupNode_define(void)
{
#ifndef FEATURE_SLEEP_NO_WAKEUP_NODE
  npa_resource_state initial_state[] = {NPA_MAX_STATE};

  npa_define_node(&g_sleepWakeupNode, initial_state, NULL);
#endif

  return;
}

