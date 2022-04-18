/*
 * Copyright (c) 2013-2015 Qualcomm Technologies, Inc.  All Rights Reserved.
 * Qualcomm Technologies Proprietary and Confidential.
 */

#pragma once

#include "tci.h"
#include "SecureUILibApiParams.h"

/**
 * @cond
 * Command ID's for communication TA Client -> TA.
 */

#define SECUREUILIB_OFFSET            0x01000000

#define SECUREUILIB_CMD_STARTTOUCH            ( 1 | SECUREUILIB_OFFSET)
#define SECUREUILIB_CMD_PROCESSTOUCH          ( 2 | SECUREUILIB_OFFSET)
#define SECUREUILIB_CMD_STOPTOUCH             ( 3 | SECUREUILIB_OFFSET)
#define SECUREUILIB_CMD_PREPARESECUREREQ      ( 4 | SECUREUILIB_OFFSET)
#define SECUREUILIB_CMD_STORESECUREINDICATOR  ( 5 | SECUREUILIB_OFFSET)

#define IS_OK(x) (x == SSE_OK)


/*
 * @endcond
 */

typedef union {
  cmdStartTouch_t              startTouch;
  cmdProcessTouch_t            processTouch;
  cmdStopTouch_t               stopTouch;
  cmdStoreIndicator_t          storeIndicator;
} SecureUILibCommandPayload_t;

typedef union {
  rspStartTouch_t              startTouch;
  rspProcessTouch_t            processTouch;
  rspStopTouch_t               stopTouch;
  rspPrepareRequest_t          prepareRequest;
} SecureUILibResponsePayload_t;

typedef struct __attribute__ ((aligned (0x40))) {
  tciCommandHeader_t           header;
  SecureUILibCommandPayload_t  payload;
} tciLibCommand_t;

typedef struct __attribute__ ((aligned (0x40))) {
  tciResponseHeader_t           header;
  SecureUILibResponsePayload_t  payload;
} tciLibResponse_t;
