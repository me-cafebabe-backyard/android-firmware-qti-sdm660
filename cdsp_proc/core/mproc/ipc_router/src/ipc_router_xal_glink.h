#ifndef _IPC_ROUTER_XAL_GLINK_H_
#define _IPC_ROUTER_XAL_GLINK_H_
/*===========================================================================

                      I P C    R O U T E R    X A L
                                G L I N K

  ---------------------------------------------------------------------------
  Copyright (c) 2014 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
  ---------------------------------------------------------------------------
===========================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

$Header: //components/rel/core.qdsp6/1.0.c2/mproc/ipc_router/src/ipc_router_xal_glink.h#1 $ 
$DateTime: 2020/02/10 01:57:30 $ $Author: pwbldsvc $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
11/06/14   aep     Initial creation
===========================================================================*/

/*===========================================================================
                          INCLUDE FILES
===========================================================================*/
#include "ipc_router_os.h"
#include "ipc_router_xal.h"
#include "glink.h"

/*===========================================================================
                  CONSTANT / MACRO DACLARATIONS
===========================================================================*/

/** Max number of intent categories */
#define IPC_ROUTER_XAL_GLINK_MAX_INTENT_TYPES 4

/** Paramters provided to the transport */
typedef struct {
  /* Transport to use, NULL, if we would prefer GLink to pick one */
  const char   *transport;
  /* Remote subsystem */
  const char   *remote_ss;
  /* Name of the channel */
  const char   *name;
  /* Channel options */
  unsigned int options;
  /* (OS Specific) Priority of the worker thread if present */
  uint8_t      priority;
  /* (OS Specific) Size of the stack of the worker thread. 0 may
   * be used to indicate that the XAL will operate in a threadless 
   * manner */
  size_t       stack_size;

  /* The intent spread/pattern */
  struct {
    /* Size of the intent */
    size_t     size;
    /* Number of intents of the size specified above queued */
    size_t     count;
  } intents[IPC_ROUTER_XAL_GLINK_MAX_INTENT_TYPES];

} ipc_router_xal_glink_param_type;

/** The operation table of the XAL */
extern ipc_router_xal_ops_type ipc_router_xal_glink;

#endif
