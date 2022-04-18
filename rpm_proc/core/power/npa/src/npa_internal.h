#ifndef NPA_INTERNAL_H
#define NPA_INTERNAL_H

#include "npa_resource.h"

#include "CorePool.h"
#include "CoreWorkContainer.h"

#include "ULogFront.h"
#include "DALSys.h"


typedef struct npa_continuation
{
  npa_callback_event callback;

  union
  {
    struct npa_alias_continuation
    {
      const char        *resource_name;
      const char        *alias_name;
    } alias;

    struct npa_node_continuation
    {
      npa_node_definition *definition;
      unsigned int         dependency;
    } node;

    struct npa_resources_available_continuation
    {
      const char  **resources;
      unsigned int  num_resources;
      unsigned int  index;
    } resources;

    struct npa_client_request_continuation
    {
      DALSYSEventHandle    enqueue_event; /* DAL Event Handle for enquing
                                           * async requests */
      npa_resource_state  *vector;
    } client;

  } data;
} npa_continuation;

typedef struct npa_link
{
  struct npa_link *next;
  const char      *name;
  npa_resource    *resource;
} npa_link;

typedef struct npa_struct
{
  /* memory pools */
  CorePoolType resource_pool;
  CorePoolType client_pool;
  CorePoolType event_pool;
  CorePoolType link_pool;

/* Global list of registered resources
 * 
 * TODO: Perhaps this should be a hash table indexed on resource name?
 * Depends on the number of resources and lookups that happen... */
  npa_link     *resources;
  npa_link     *placeholders;

  DALSYSSyncHandle graph_lock;
  DALSYSSyncHandle event_lock;

  ULogHandle     log;

  /* Workloop for async requests */
  DALSYSWorkLoopHandle async_request_handle;

  /* Workloop for npa event processing */
  CoreContainerWorkLoopHandle event_handle;

  /* Queue for async npa event processing */
  CoreWorkContainerHandle event_queue_handle;
  
} npa_struct;

/* NPA data structure */
extern npa_struct npa;

#endif /* NPA_INTERNAL_H */
