/** vi: tw=128 ts=3 sw=3 et
@file gen_cb_ctxt.c
@brief This file contains the API details for the Protection Domain Monitor, API 2.0
*/
/*=============================================================================
NOTE: The @brief description above does not appear in the PDF.
The tms_mainpage.dox file contains the group/module descriptions that
are displayed in the output PDF generated using Doxygen and LaTeX. To
edit or update any of the group/module text in the PDF, edit the
tms_mainpage.dox file or contact Tech Pubs.
===============================================================================*/
/*=============================================================================
Copyright (c) 2017 by Qualcomm Technologies, Inc.  All Rights Reserved.
Qualcomm Confidential and Proprietary
===============================================================================*/
/*=============================================================================
Edit History
$Header: //components/rel/core.qdsp6/1.0.c2/debugtools/gen_cb_ctxt/src/gen_cb_ctxt.c#1 $
$DateTime: 2020/02/10 01:57:30 $
$Change: 22511909 $
$Author: pwbldsvc $
===============================================================================*/

#include "com_dtypes.h"
#include "qurt.h"
#include "queue.h"
#include "gen_cb_ctxt.h"
#include "rcinit.h"
#include "dll_api.h"
#include <stdlib.h>

#define GEN_CB_CTXT_INVOKE_CBS 0x1

typedef struct 
{
  qurt_anysignal_t sig;
  q_type           queue;
  boolean          init;
}gen_cb_ctxt_internal_s;

static gen_cb_ctxt_internal_s gen_cb_ctxt_internal;

typedef struct
{
  /* q_link_type - Must be the first element */
  q_link_type        node;
  gen_cb_ctxt_cb_t   cb;
  void *             arg;
}gen_cb_ctxt_q_data_s;

/**
Function corresponding gen_cb_ctxt task. It is used to invoke the callbacks
@return
None
*/

DLL_API_GLOBAL void gen_cb_ctxt(void)
{
  unsigned int    sigs;
  gen_cb_ctxt_q_data_s * data;
  
  /* Handshake with rcinit */
  rcinit_handshake_startup();

  for(;;)
  {
    /* Wait for some task signal */
    sigs = qurt_anysignal_wait( &gen_cb_ctxt_internal.sig,
		                          GEN_CB_CTXT_INVOKE_CBS );
    
    if ( sigs & GEN_CB_CTXT_INVOKE_CBS )
    {
      qurt_anysignal_clear( &gen_cb_ctxt_internal.sig, GEN_CB_CTXT_INVOKE_CBS );

      /* Process the callback */
      /* Get from the queue */
      data = q_get(&(gen_cb_ctxt_internal.queue) );

      while ( data != NULL )
      {
        data->cb( data->arg);
        free(data);
        data = q_get(&(gen_cb_ctxt_internal.queue) );
      }
    }
  }
}

/**
Initializes the various data strcutures related to gen_cb_ctxt module 
@return
None
*/


DLL_API_GLOBAL void gen_cb_ctxt_init(void)
{
  if ( gen_cb_ctxt_internal.init != TRUE )
  {
    gen_cb_ctxt_internal.init = TRUE;
    q_init(&gen_cb_ctxt_internal.queue);
    qurt_anysignal_init(&gen_cb_ctxt_internal.sig);
  }
}


/**
Invokes the callback and the argument as specified by the argument 

@return
None
*/


DLL_API_GLOBAL void gen_cb_ctxt_invoke_cb( gen_cb_ctxt_cb_t cb, void * arg )
{
  gen_cb_ctxt_q_data_s * data = malloc(sizeof(gen_cb_ctxt_q_data_s));

  if ( data == NULL )
  {
    return;
  }
  
  data->cb = cb;
  data->arg = arg;
    
  /* Insert in the queue */
  (void) q_link( data , &(data->node) );
  q_put(&(gen_cb_ctxt_internal.queue), 
        &(data->node) );

  (void)qurt_anysignal_set(&gen_cb_ctxt_internal.sig, GEN_CB_CTXT_INVOKE_CBS);
}

