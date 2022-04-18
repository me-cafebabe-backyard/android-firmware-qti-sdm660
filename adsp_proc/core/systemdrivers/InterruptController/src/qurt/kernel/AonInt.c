/*
===========================================================================
*/
/**
  @file AonInt.c
  
  The file contains the resource definitions for retention voting on the
  Low Power Island subsystem.
*/
/*  
  ====================================================================

  Copyright (c) 2016 Qualcomm Technologies Incorporated.
  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ==================================================================== 
  $Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/InterruptController/src/qurt/kernel/AonInt.c#1 $
  $DateTime: 2020/02/10 01:57:30 $
  $Author: pwbldsvc $

  when       who     what, where, why
  --------   ---     -------------------------------------------------
  12/02/16   shm     Updated for core.qdsp6.1.0
  09/25/14   dcf     Created.

  ====================================================================
*/ 


/*=========================================================================
      Include Files
==========================================================================*/

/*
 * External header files.
 */
#include <sleep_lpr.h>
#include <npa.h>
#include <npa_resource.h>
#include <npa_remote.h>
#include <npa_remote_resource.h>
#include <uSleep.h>
#include <uSleep_core_npa.h>

#include "AonInt_Internal.h"
#include "HALaonint.h"

/*=========================================================================
      Type Definitions
==========================================================================*/

static npa_client_handle hNPARetentionHandle = NULL;
static npa_client_handle hNPAIslandModeHandle = NULL;


/*
 * AonIntRetentionType
 *
 * Structure containing the retention NPA node and resource data.
 *
 *  Node      - Retention node data
 *  Resource  - Retention resource data: /lpi/retention
 *  Dependency - 
 */ 
typedef struct
{
  npa_resource_definition   Resource;
  npa_node_definition       Node;
  npa_node_dependency       Dependency[1];
} AonIntRetentionType;


/*=========================================================================
      Prototypes
==========================================================================*/

static npa_resource_state AonIntRetentionDriver
(
  npa_resource *pResource,
  npa_client   *pClient,
  npa_resource_state nState
);

/*=========================================================================
      Variables
==========================================================================*/


/*
 * AonInterruptRetention
 *
 * Low power resource data.
 */
static AonIntRetentionType AonIntRetention =
{
  /*
   * Resource
   */
  {
    "/lpi/retention", 
    "on/off",
    AONINT_SOURCE_REQUIRED,        /* max state */
    &npa_max_plugin, 
    NPA_RESOURCE_DEFAULT,
    NULL
  },

  /*
   * Node
   */
  { 
    "/node/lpi/retention",                 /* name */
    AonIntRetentionDriver,                 /* driver_fcn */
    NPA_NODE_DEFAULT,                      /* attributes */
    NULL,                                  /* data */
    NPA_ARRAY(AonIntRetention.Dependency), /* dependency */
    1,                                     /* dependency count */
    &AonIntRetention.Resource              /* resource */
  },
  /*
   * Dependency
   */
  {
    {
      SLEEP_LPR_NODE_NAME,
      NPA_CLIENT_REQUIRED
    }
  }

};


/*=========================================================================
      Functions
==========================================================================*/


/* =========================================================================
**  Function : AonIntRetentionDriver
** =========================================================================*/
/**
  API to handle retention requests.
 
  This API manages retention votes and notifies sleep driver via LPR if 
  retention can be entered or not based on the aggregated votes.

  @param pResource [in] -- The NPA resource being requested.
  @param pClient [in]   -- Pointer to the client making the request.
  @param nState [in]    -- New state of the resource.

  @return
  New state of the resource.

  @dependencies
  None.
*/ 

static npa_resource_state AonIntRetentionDriver
(
  npa_resource      *pResource,
  npa_client        *pClient,
  npa_resource_state nState
)
{
  /*-----------------------------------------------------------------------*/
  /* Get the retention node's client handle to the sleep LPR node.         */
  /*-----------------------------------------------------------------------*/

  npa_client_handle hClientHandle = NPA_DEPENDENCY(pResource, 0);

  /*-----------------------------------------------------------------------*/
  /* At init time, register the LPR with the sleep LPR node, and request   */
  /* a bit mask to use for the retentionLPRMs from the sleep LPR node.     */
  /*-----------------------------------------------------------------------*/

  if (pClient->type == NPA_CLIENT_INITIALIZE)
  {
    sleepLPR_define("lpi", hClientHandle);
  }

  /*-----------------------------------------------------------------------*/
  /* Issue a request to the sleep node to enable or disable this node's    */
  /* LPRMs during sleep.                                                   */
  /*  0: retention is not required at all by any client.                   */
  /*  1: retention is required by one or more clients.                     */
  /*-----------------------------------------------------------------------*/

  if (nState == AONINT_SOURCE_REQUIRED)
  {
    // Make an NPA vote against island mode
    npa_complete_request( hClientHandle );

    npa_complete_request( hNPAIslandModeHandle );
  }
  else
  {
    // Make an NPA vote for island mode
    npa_issue_scalar_request( hClientHandle, 
                              SLEEP_LPRM_NUM(0) );

    npa_issue_required_request( hNPAIslandModeHandle, 
                                AONINT_VOTE_FOR_ISLAND_MODE );
  }

  return nState;

} /* END AonIntRetentionDriver */


/* =========================================================================
**  Function : AonInt_RetentionCreateClientCB
** =========================================================================*/
/**
  Callback when the retention node is created.
 
  This function is called by the NPA framework when the given retention node is
  created.  The creation is delayed until all dependencies are also
  created.
 
  @param *pContext [in] -- Context passed in npa_define_node_cb
  @param nEventType [in] -- Zero.
  @param *pNodeName [in] -- Name of the node being created.
  @param nNodeNameSize [in] -- Length of the name.

  @return
  None.

  @dependencies
  None.
*/ 

static void AonInt_RetentionCreateClientCB
(
  void        *pContext,
  unsigned int nEventType,
  void        *pNodeName,
  unsigned int nNodeNameSize
)
{
  npa_node_definition *pNode = (npa_node_definition *)pContext;
  uint32 nState;

  /*-----------------------------------------------------------------------*/
  /* Create the appropriate NPA client.                                    */
  /*-----------------------------------------------------------------------*/

  if (pNode == &AonIntRetention.Node)
  {
    hNPARetentionHandle = 
      npa_create_sync_client(
        AonIntRetention.Resource.name, "/lpi/retention", NPA_CLIENT_REQUIRED);
  }

  /*-----------------------------------------------------------------------*/
  /* Send current state info to retention NPA driver function.             */
  /*-----------------------------------------------------------------------*/

  nState = AONINT_SOURCE_NOT_REQUIRED;

  npa_issue_scalar_request(hNPARetentionHandle, nState);

} /* END AonInt_RetentionCreateClientCB */


/* =========================================================================
**  Function : AonInt_RetentionInit
** =========================================================================*/
/*
  See AonInt.h
*/

DALResult AonInt_RetentionInit
(
  void
)
{
  npa_resource_state nInitialState;

  /*-----------------------------------------------------------------------*/
  /* Init retention node.                                                  */
  /*-----------------------------------------------------------------------*/

  nInitialState = AONINT_SOURCE_NOT_REQUIRED;

  npa_define_node_cb(
    &AonIntRetention.Node, &nInitialState, AonInt_RetentionCreateClientCB,
    &AonIntRetention.Node);

  /*-----------------------------------------------------------------------*/
  /* Publish the node to the sensors PD.                                   */
  /*-----------------------------------------------------------------------*/
   
  npa_remote_publish_resources(SENSOR_PD,
                               1,
                               &AonIntRetention.Resource.name);

  /*-----------------------------------------------------------------------*/
  /* Good to go.                                                           */
  /*-----------------------------------------------------------------------*/

  return DAL_SUCCESS;

} /* END AonInt_RetentionInit */


/* =========================================================================
**  Function : AonInt_RetentionGetIslandHandleCB
** =========================================================================*/
/**
  Callback when the Island Mode resource is available.
 
  This function is called by the NPA framework when the uSleep resource
  is available to make requests to.
 
  @param *pContext [in] -- Context passed in npa_define_node_cb
  @param nEventType [in] -- Zero.
  @param *pUnusedPointer [in] -- Unused pointer parameter.
  @param nUnusedInt [in] -- Unused Size Parameter.

  @return
  None.

  @dependencies
  None.
*/ 

static void AonInt_RetentionGetIslandHandleCB
(
  void        *pContext,
  unsigned int nEventType,
  void        *pUnusedPointer,
  unsigned int nUnusedInt
)
{

  /*-----------------------------------------------------------------------*/
  /* Create a sync client for voting for and against Island Mode.          */
  /*-----------------------------------------------------------------------*/

  if ( hNPAIslandModeHandle == NULL )
  {
    hNPAIslandModeHandle = 
      npa_create_sync_client(USLEEP_CORE_DRIVER_NODE_NAME,
                             "/aonint/uSleepClient",
                             NPA_CLIENT_REQUIRED);

    AonInt_RetentionInit();
  }
}


/* =========================================================================
**  Function : AonInt_Init
** =========================================================================*/
/*
  See AonInt.h
*/

DALResult AonInt_Init
(
  void
)
{
  /*-----------------------------------------------------------------------*/
  /* Register a callback for when the NPA resource becomes available.      */
  /* Ideally we want to do this before registering the node                */
  /*-----------------------------------------------------------------------*/

  npa_resource_available_cb( USLEEP_CORE_DRIVER_NODE_NAME,
                             AonInt_RetentionGetIslandHandleCB,
                             NULL );

  return DAL_SUCCESS;

} /* END AonInt_Init */


