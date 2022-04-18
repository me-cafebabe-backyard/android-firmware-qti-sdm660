// Copyright (c) 2016 Qualcomm Technologies, Inc.  All Rights Reserved.
// Qualcomm Technologies Proprietary and Confidential.

#include <stringl.h>
#include "object.h"
#include "qsee_heap.h"
#include "IObserver.h"
#include "IObserver_invoke.h"
#include "qsee_log.h"

/*******************************************************************************
 * Local data types
 * ****************************************************************************/

typedef struct Observer {
  int32_t refs;
  Object target;
  size_t contextSize;
} Observer;

/*******************************************************************************
 * Observer: peek into the context of an observed object
 * ****************************************************************************/

static int32_t CObserver_retain(Observer *me)
{
  ++me->refs;
  return Object_OK;
}

static int32_t CObserver_release(Observer *me)
{
  if (--me->refs == 0) {
    qsee_log(QSEE_LOG_MSG_DEBUG, "%s: Releasing target",__FUNCTION__);
    Object_ASSIGN_NULL(me->target);
    qsee_free(me);
  }
  return Object_OK;
}

static int32_t CObserver_observe(Observer *me, Object o, uint32_t contextSize)
{
  Object_ASSIGN(me->target, o);
  if (me->target.context) {
    me->contextSize = contextSize;
  } else {
    me->contextSize = 0;
  }
  return Object_OK;
}

static inline int32_t CObserver_dump(Observer *me, void *context_ptr, size_t context_len, size_t *context_lenout)
{
  *context_lenout = memscpy(context_ptr, context_len, me->target.context, me->contextSize);
  return Object_OK;
}

static IObserver_DEFINE_INVOKE(CObserver_invoke, CObserver_, Observer *)

/**
 * Externally visible function: return an observer object
 */
int32_t CObserver_open(Object* obj)
{
  Observer *me = (Observer*)qsee_realloc(NULL, sizeof(Observer));
  if (!me) {
     return Object_ERROR_KMEM;
  }
  me->refs = 1;
  *obj = (Object) { CObserver_invoke, me };
  return Object_OK;
}
