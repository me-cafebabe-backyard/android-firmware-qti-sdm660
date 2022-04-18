/*==============================================================================
  FILE:         uSleep_node.c

  OVERVIEW:     This file provides the /core/uSleep node setup

  DEPENDENCIES: None
  
                Copyright (c) 2014-2017 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/uSleep/src/transition/ddr/uSleep_node.c#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include <stdlib.h>
#include "uSleep.h"
#include "uSleepi.h"
#include "uSleep_util.h"
#include "CoreVerify.h"
#include "uSleep_node.h"
#include "npa.h"
#include "npa_resource.h"
#include "sleep_plugin_clients.h"
#include "sleep_lpr.h"
#include "client_os.h"
#include "uSleep_target.h"
#include "uSleep_core_npa.h"
#include "sleep_npa.h"

/*==============================================================================
                                  TYPEDEFS
 =============================================================================*/
/* Data structure for the internal LPR change event registration */
typedef struct lprEvents_s
{
  npa_client_handle client_handle;  /* Custom client handle to the main /uSleep node
                                     * (Initially NULL; will be created at init) */
  char              *node_name;     /* Unique name of the custom client */
  char              *LPR_node_name; /* LPR node name used to base client vote on */
  qurt_mutex_t      lock;           /* Lock to synchronize resource as it can be issued 
                                     * from multiple contexts */
}lprEvents;

/*==============================================================================
                             INTERNAL VARIABLES
 =============================================================================*/
/* Variables for the uSleep test nodes to enabled or disabled entry into uImage.
 * These variables must be set before system init; setting at runtime has no meaning.
 * Valid variable values:
 *  = -1: Do not create a client (default)
 *   = 0: Create a client and vote against entry
 *   > 0: Create a client and vote for entry
 */ 
#ifdef USLEEP_CREATE_TEST_NODE
static volatile uint32 g_uSleepTestNodeOption         = -1;  /* Client to the main node "/core/uSleep" */
static volatile uint32 g_uSleepInternalTestNodeOption = -1;  /* Client to the internal uSleep node */
#endif

/* LPR event change list to tie uSleep enablement to.
 * uSleep will be disabled if any of these LPR's are also disabled */
static lprEvents g_uSleepLprEvents[] =
{
  /*  Handle  Client Name to "/core/uSleep"   LPR node name to add a change event to */
  {   NULL,   "/uSleep/lprEvent/cpu_vdd",     SLEEP_CPUVDD_LPR_NODE_NAME},
  {   NULL,   "/uSleep/lprEvent/rpm",         SLEEP_RPM_LPR_NODE_NAME},
};

/*==============================================================================
                             FORWARD DECLARATIONS
 =============================================================================*/
static npa_resource_state uSleepNode_driver(npa_resource       *resource,
                                            npa_client         *client,
                                            npa_resource_state state);

static npa_resource_state uSleep_resourceUpdateFn(npa_resource      *resource,
                                                  npa_client_handle client);

static npa_resource_state uSleepNode_internalDriver(npa_resource        *resource,
                                                    npa_client          *client,
                                                    npa_resource_state  state);

static void uSleepNode_LPRResourceAvailCB(void         *context, 
                                          unsigned int eventType,
                                          void         *data, 
                                          unsigned int dataSize);

static void uSleepNode_setupInternalNPANodes(void);

/*==============================================================================
                         MAIN uSLEEP NODE DEFINITION
 =============================================================================*/
/* Main uSleep node which is custom AND plugin with internal/custom clients
 * that are considered only in presence of external/default clients.
 * 
 * Internal clients are used to control uSleep node based on other sleep
 * restrictions. */
static npa_resource_plugin g_uSleepResourcePlugin = 
{
  uSleep_resourceUpdateFn,          /* Update function */
  NPA_CLIENT_REQUIRED             | /* Supported clients */
  NPA_CLIENT_SUPPRESSIBLE         |
  USLEEP_CLIENT_NODE_CORE_DRIVERS,
  NULL,                           /* Client creation function */
  NULL                            /* Client destroy function */
};

/* Dependencies required for main usleep node */
static npa_node_dependency g_uSleepNodeDependency[1] =
{
  {
    SLEEP_LPR_NODE_NAME,
    NPA_CLIENT_REQUIRED,
  },
};

/* Main usleep node used to control entry into uImage */
static npa_resource_definition g_uSleepNodeResource[] =
{
  {
    USLEEP_NODE_NAME,         /* Name */
    "Allow",                  /* Units */
    0x01,                     /* Max State - increase if multiple islands */
    &g_uSleepResourcePlugin,  /* Custom plugin */
    NPA_RESOURCE_INTERPROCESS_ACCESS_ALLOWED, /* Attributes */
    NULL,                     /* User Data */
    NULL                      /* Query Function */
  }
};

/* uSleep driver node to the /sleep/lpr node */
static npa_node_definition g_uSleepNode =
{
  "/node/core/uSleep",                /* Name */
  uSleepNode_driver,                  /* Driver_fcn */
  NPA_NODE_DEFAULT,                   /* Attributes */
  NULL,                               /* Data */
  NPA_ARRAY(g_uSleepNodeDependency),  /* Dependencies */
  NPA_ARRAY(g_uSleepNodeResource)     /* Resources */
};

/*==============================================================================
                         MAIN INTERNAL uSLEEP NODE DEFINITION
 =============================================================================*/
/* Dependencies for the internal uSleep node */
static npa_node_dependency g_uSleepInternalDependencies[1] =
{
  {
    USLEEP_NODE_NAME,
    USLEEP_CLIENT_NODE_CORE_DRIVERS,
  },
};

/* Definition of the internal uSleep node  */
static npa_resource_definition g_uSleepInternalDefinition[] = 
{ 
  {  
    USLEEP_CORE_DRIVER_NODE_NAME,             /* Name */
    "Allow",                                  /* Units */
    1,                                        /* Max State */
    &npa_binary_and_plugin,                   /* Plugin */
    NPA_RESOURCE_INTERPROCESS_ACCESS_ALLOWED, /* Attributes */
    NULL,                                     /* User Data */
    NULL,                                     /* Query Function */
    NULL                                      /* Query Link Function */
  }
};

/* Definition of the internal uSleep node */
static npa_node_definition g_uSleepInternalNode = 
{ 
  "/node/island/core/drivers",              /* name */
  uSleepNode_internalDriver,                /* driver_fcn */
  NPA_NODE_DEFAULT,                         /* attributes */
  NULL,                                     /* data */
  NPA_ARRAY(g_uSleepInternalDependencies),  /* dependencies */
  NPA_ARRAY(g_uSleepInternalDefinition)     /* resources */
};

/*==============================================================================
                        MAIN uSLEEP NODE FUNCTION DEFINITIONS
 =============================================================================*/
/**
 * uSleepNode_driver
 * 
 * @brief Driver function for the uSleep node
 *
 * @param resource: The NPA resource being requested.
 * @param client:   Pointer to the client making the request.
 * @param state:    New state of the resource.
 *
 * @return: New state of the resource
 */
static npa_resource_state uSleepNode_driver(npa_resource       *resource,
                                            npa_client         *client,
                                            npa_resource_state state)
{
  /* Get the dependency of the uSleep node. */
  npa_client_handle client_handle = NPA_DEPENDENCY(resource, 0);

  if(client->type == NPA_CLIENT_INITIALIZE)
  {
    /* Register the low power island resources */
    sleepLPI_define("power_island", client_handle);

    /* Setup guest OS client - Allows callbacks to be registered and requires
     * that the LPI be registered with the main sleep system */
    uSleep_guestClientInit();

    /* Register for a callback to perform any target specific transition requirements */
    CORE_VERIFY(0 != uSleep_registerNotificationCallback(10, 1000, 
                                                         uSleepTarget_transitionNotificationCB));
  }

  /* Enable or disable the LPI. */
  npa_issue_required_request(client_handle, state);

  return state;
}

/**
 * uSleep_resourceUpdateFn
 *
 * @brief Update function for the uSleep NPA resource.
 *
 * @param resouce: Pointer to uSleep npa resource.
 * @param client:  Client whose request is being processed.
 *
 * @return State of uSleep NPA resource after considering client's request.
 */
static npa_resource_state uSleep_resourceUpdateFn(npa_resource      *resource,
                                                  npa_client_handle client)
{
  static npa_resource_state coreDriverClientsState  = 1;
  static npa_resource_state requiredClientsState    = 0;
  
  /* Initialize internal AND aggregations so that subsequent REQUIRED 
   * requests are aggregated correctly. */
  if(0 == resource->sequence)
  {
    resource->internal_state[NPA_REQUIRED_INDEX] = 0x1;
    resource->internal_state[NPA_SUPPRESSIBLE_INDEX] = 0x1;
  }

  switch(client->type)
  {
    case USLEEP_CLIENT_NODE_CORE_DRIVERS:
    {
      /* Take the aggritaged value of all the internal core driver clients */
      coreDriverClientsState = NPA_PENDING_REQUEST(client).state;
      break;
    }

    default:
    {
      /* All default clients are handled by npa plugin's update function */
      requiredClientsState = npa_binary_and_plugin.update_fcn(resource, client);
      break;
    }
  }

  /* All clients must be non-zero to allow entry. For now, force the return value to 1 or 0.
  * If multiple islands are supported, the return value will be the bit-wise AND value. */
  return((requiredClientsState && coreDriverClientsState) ? 0x01 : 0x00);
}

#ifdef USLEEP_CREATE_TEST_NODE
/**
 * uSleepNode_createTestClient
 * 
 * @brief Creates a test client to control uSleep entry for debug or 
 *        bringup purposes.
 *  
 * @note Variables must be initially set at cold boot time. 
 *       Changing after that, during run-time, will have no effect. 
 */
static void uSleepNode_createTestClient(void)
{
  npa_client_handle uSleepTestClient;
  npa_client_handle uSleepInternalTestClient;

  /* Check if test clients should be created */
  if(-1 != g_uSleepTestNodeOption)
  {
    uSleepTestClient = npa_create_sync_client(USLEEP_NODE_NAME,
                                              "uSleepTestClient",
                                              NPA_CLIENT_REQUIRED);
    
    if(NULL != uSleepTestClient)
    {
      /* Allow/disallow uImage entry from this client */
      npa_issue_required_request(uSleepTestClient, g_uSleepTestNodeOption);
    }
  }

  if(-1 != g_uSleepInternalTestNodeOption)
  {
    uSleepInternalTestClient = npa_create_sync_client(USLEEP_CORE_DRIVER_NODE_NAME,
                                                      "uSleepLPRTestClient",
                                                      NPA_CLIENT_REQUIRED);

    if(NULL != uSleepInternalTestClient)
    {
      npa_issue_required_request(uSleepInternalTestClient, g_uSleepInternalTestNodeOption);
    }
  }
  
  return;
}
#endif

/**
 * uSleepNode_registerCB
 * 
 * @brief Registers the main uSleep node
 * 
 * @param see npa_callback defintion for function parameters
 */
static void uSleepNode_registerCB(void         *context,
                                  unsigned int  eventType,
                                  void         *data,
                                  unsigned int  dataSize)
{
  npa_resource_state uSleepInitialState         = 0; /* Default is disabled */
  npa_resource_state uSleepInternalInitialState = 1; /* Default is enable */
  
  /* Creates the main /core/uSleep node */
  npa_define_node(&g_uSleepNode, &uSleepInitialState, NULL);

  /* Creates the internal uSleep node */
  npa_define_node(&g_uSleepInternalNode, &uSleepInternalInitialState, NULL);

  /* Setup any target specific lpr clients to the usleep core driver node */
  uSleepNode_setupInternalNPANodes();

#ifdef USLEEP_CREATE_TEST_NODE
  uSleepNode_createTestClient();
#endif

  return;
}

/*==============================================================================
                       INTERNAL uSLEEP NODE FUNCTIONS
 =============================================================================*/
/**
 * uSleepNode_setupInternalNPANodes
 * 
 * @brief Creates any target specific clients to the uSleepInternal node
 *        that will limit entry to uImage.  This will typically be a change
 *        event to the /cpu/vdd LPR so when power collapse is disabled, uImage
 *        entry is not allowed.
 */
static void uSleepNode_setupInternalNPANodes(void)
{
  uint32 idx        = 0;
  uint32 numEntries = sizeof(g_uSleepLprEvents) / sizeof(g_uSleepLprEvents[0]);

  /* Registering NPA callback to init the client with the LPR node is available */
  while(idx < numEntries)
  {
    npa_resource_available_cb(g_uSleepLprEvents[idx].LPR_node_name, 
                              uSleepNode_LPRResourceAvailCB, (void *)&g_uSleepLprEvents[idx]);
    idx++;
  }

  return;
}

/**
 * uSleepNode_internalDriver
 *
 * @brief 
 *
 * @param resource: Pointer to the resource (unused).
 * @param client: Client of this resource (unused).
 * @param state: New(?) state for the resource (unused).
 *
 * @return The state of the resource if set else NPA_MAX_STATE
 */
static npa_resource_state uSleepNode_internalDriver(npa_resource        *resource,
                                                    npa_client          *client,
                                                    npa_resource_state  state)
{
  npa_client_handle client_handle = NPA_DEPENDENCY(resource, 0);

  /* Forward request to the corresponding base uSleep resource */
  npa_issue_required_request(client_handle, state);

  return state;
}

/*==============================================================================
                     INTERNAL uSLEEP LPR NODE FUNCTIONS
 =============================================================================*/
/**
 * @brief This Callback is triggered when the registered LPR is enabled 
 *        or disabled  
 *
 * @param See npa_callback type
 */
static void uSleepNode_ProcessLPRChangeEvent(void         *context,
                                             unsigned int event,
                                             void         *event_data,
                                             unsigned int event_data_size)
{
  lprEvents *localEvent = (lprEvents *)context;

  CORE_VERIFY_PTR(localEvent);

  qurt_mutex_lock(&localEvent->lock);

  if(event == NPA_EVENT_CHANGE)
  {
    /* State will be non-zero when the LPR is disabled.
     * Note that this currently a bit of an assumption that a non-zero LPR state
     * means disable.  It should be pretty safe though since a complete request sets a 0 state
     * on nodes */ 
    if(((npa_event_data *)event_data)->state)
    {
      /* LPR is disabled and should prevent uSleep */
      npa_issue_required_request(localEvent->client_handle, USLEEP_CLIENT_RESTRICT_ISLAND);
    }
    else
    {
      /* Ok to vote for uSleep */
      npa_issue_required_request(localEvent->client_handle, USLEEP_CLIENT_ALLOW_ISLAND);
    } 
  }

  qurt_mutex_unlock(&localEvent->lock);

  return;
}

/**
 * uSleepNode_LPRResourceAvailCB
 * 
 * @brief Callback function run when the LPR node dependencies are avaialble
 * 
 * @param see npa_callback defintion for function parameters
 */
static void uSleepNode_LPRResourceAvailCB(void         *context, 
                                          unsigned int eventType,
                                          void         *data, 
                                          unsigned int dataSize)
{
  npa_event_handle  eventHandle;
  lprEvents         *localEvent = (lprEvents *)context;
 
  CORE_VERIFY_PTR(localEvent);

  qurt_mutex_init(&localEvent->lock);

  /* Create a cpu/vdd client to the internal core node.
   * This is used to disable island mode if the cpu/vdd LPRM's are disabled */
  CORE_VERIFY_PTR(localEvent->client_handle = 
                  npa_create_sync_client(USLEEP_CORE_DRIVER_NODE_NAME,
                                         localEvent->node_name,
                                         NPA_CLIENT_REQUIRED));

  CORE_VERIFY_PTR(eventHandle =
                  npa_create_event_cb(localEvent->LPR_node_name,
                                      "uSleep LPR Event",
                                      NPA_TRIGGER_CHANGE_EVENT,
                                      uSleepNode_ProcessLPRChangeEvent,
                                      (void *)localEvent));

  /* Default is allow entry */
  npa_issue_required_request(localEvent->client_handle, 1);

  return;  
}

/*==============================================================================
                         EXTERNAL FUNCTION DEFINITIONS
 =============================================================================*/
/*
 * uSleepNode_initialize
 */
void uSleepNode_initialize(void)
{
  /* Register a callback for when the necessary dependencies are available,
   * in order to register the nodes and other requirements that uSleep owns. */
  npa_resource_available_cb(SLEEP_LPR_NODE_NAME,
                            uSleepNode_registerCB, NULL);

  return;
}

