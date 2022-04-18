// Copyright (c) 2016 Qualcomm Technologies, Inc.  All Rights Reserved.
// Qualcomm Technologies Proprietary and Confidential.

#ifndef __CTEST1_PRIV_H
#define __CTEST1_PRIV_H

#include <stdint.h>
#include "object.h"

/**
 * Internal context for CTestObj objects.
 * Shared so that it can be inspected in CObserver dumps for testing purposes,
 * i.e. to check reference counting, last called operation, etc.
 */
typedef struct TestObj {
   int refs;
   int lastInvoked;
   Object o;
} TestObj;


#endif // __CTEST1_PRIV_H
