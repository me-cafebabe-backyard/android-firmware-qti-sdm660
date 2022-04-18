// Copyright (c) 2016 Qualcomm Technologies, Inc.  All Rights Reserved.
// Qualcomm Technologies Proprietary and Confidential.

#include <stringl.h>
#include "object.h"
#include "qsee_heap.h"
#include "ITest1.h"
#include "ITest1_invoke.h"
#include "CTest1_open.h"
#include "CTest1_priv.h"
#include "qsee_log.h"

//----------------------------------------------------------------
// Implementation of the ITest1 interface
//----------------------------------------------------------------

static int32_t TestObj_retain(TestObj *me)
{
  /* Don't set this becuase invoke over SMC always retains/releases
     for the duration of the call and that overwrites the actual
     command. */
  /* me->lastInvoked = Object_OP_retain; */
  qsee_log(QSEE_LOG_MSG_DEBUG, "%s: me=%p refs=%d",__FUNCTION__, me, me->refs);
  ++me->refs;
  return Object_OK;
}

static int32_t TestObj_release(TestObj *me)
{
  /* Don't set this becuase invoke over SMC always retains/releases
     for the duration of the call and that overwrites the actual
     command.  Can set it for the last release, though. */
  /* me->lastInvoked = Object_OP_release; */
  qsee_log(QSEE_LOG_MSG_DEBUG, "%s: me=%p refs=%d",__FUNCTION__, me, me->refs);
  if (--me->refs == 0) {
    qsee_free(me);
  }
  return Object_OK;
}

static int32_t TestObj_noop(TestObj *me)
{
  qsee_log(QSEE_LOG_MSG_DEBUG, "%s: me=%p refs=%d",__FUNCTION__, me, me->refs);
  me->lastInvoked = NoOp_OP_noop;
  return Object_OK;
}

static inline int32_t
TestObj_num(TestObj *me, int32_t ia, int32_t *oa)
{
  qsee_log(QSEE_LOG_MSG_DEBUG, "%s: me=%p refs=%d",__FUNCTION__, me, me->refs);
  me->lastInvoked = Test1_OP_num;
  *oa = ia;
  return Object_OK;
}

static inline int32_t
TestObj_bundled(TestObj *me, int32_t ia, const Struct2 *is, int32_t *oa, Struct2 *os)
{
  qsee_log(QSEE_LOG_MSG_DEBUG, "%s: me=%p refs=%d",__FUNCTION__, me, me->refs);
  me->lastInvoked = Test1_OP_bundled;
  *oa = ia;
  *os = *is;
  return Object_OK;
}

static inline int32_t
TestObj_array(TestObj *me, const uint8_t *a, size_t a_len, uint8_t *b, size_t b_len, size_t *b_lenout)
{
  qsee_log(QSEE_LOG_MSG_DEBUG, "%s: me=%p refs=%d",__FUNCTION__, me, me->refs);
  me->lastInvoked = Test1_OP_array;
  *b_lenout = memscpy(b, b_len, a, a_len);
  return Object_OK;
}

static inline int32_t
TestObj_setObj(TestObj *me, Object o_val)
{
  qsee_log(QSEE_LOG_MSG_DEBUG, "%s: me=%p refs=%d",__FUNCTION__, me, me->refs);
  me->lastInvoked = Test1_OP_setObj;
  Object_ASSIGN(me->o, o_val);
  return Object_OK;
}

static inline int32_t
TestObj_getObj(TestObj *me, Object *o_ptr)
{
  qsee_log(QSEE_LOG_MSG_DEBUG, "%s: me=%p refs=%d",__FUNCTION__, me, me->refs);
  me->lastInvoked = Test1_OP_getObj;
  if (!Object_isNull(me->o)) {
    *o_ptr = me->o;
    Object_retain(me->o);
    return Object_OK;
  }
  return Object_ERROR;
}

static Test1_DEFINE_INVOKE(TestObj_Test1_invoke, TestObj_, TestObj *)

/**
 *  return an object implementing Test1
 */
static Object TestObj_asTest1(TestObj *me)
{
  return (Object) { TestObj_Test1_invoke, me };
}

/**
 * Externally visible function: return a test object
 */
int32_t CTestObj_open(Object* obj)
{
  TestObj *me = (TestObj*)qsee_realloc(NULL, sizeof(TestObj));
  if (!me) {
    return Object_ERROR_KMEM;
  }
  me->refs = 1;
  me->lastInvoked = Test1_NO_METHOD;
  me->o = Object_NULL;
  *obj = TestObj_asTest1(me);
  return Object_OK;
}

