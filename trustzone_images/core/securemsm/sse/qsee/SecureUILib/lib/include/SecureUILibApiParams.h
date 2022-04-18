/*
 * Copyright (c) 2013-2014 Qualcomm Technologies, Inc.  All Rights Reserved.
 * Qualcomm Technologies Proprietary and Confidential.
 */

#pragma once

#include <stdint.h>
#include "SecureUILibDefs.h"
#include "si.h"

/******************************************************************************/
/** (1) StartTouch */
/******************************************************************************/
/** StartTouch command */
typedef struct {
  uint32_t reserved;
} cmdStartTouch_t;
/** StartTouch response */
typedef struct {
  int32_t timeout; /**< in milliseconds, 0 for no timeout, negative for infinite */
  sec_touch_cmd_t cmd;
} rspStartTouch_t;

/******************************************************************************/
/** (2) ProcessTouch */
/******************************************************************************/
/** ProcessTouch command */
typedef struct {
  sec_touch_err_t err;
} cmdProcessTouch_t;
/** ProcessTouch response */
typedef struct {
  int32_t timeout; /**< in milliseconds, 0 for no timeout, negative for infinite */
  sec_touch_cmd_t cmd;
} rspProcessTouch_t;

/******************************************************************************/
/** (3) StopTouch */
/******************************************************************************/
/** StopTouch command */
typedef struct {
  sec_touch_err_t err;
} cmdStopTouch_t;
/** StopTouch response */
typedef struct {
  sec_touch_cmd_t cmd;
} rspStopTouch_t;

/******************************************************************************/
/** (4) PrepareRequest */
/******************************************************************************/
/** PrepareRequest response */
typedef struct {
  uint8 encapsulatedReq[MAX_ENCAPSULATED_REQ];
  uint32 encapsulatedReqLen;
} rspPrepareRequest_t;

/******************************************************************************/
/** (5) StoreIndicator */
/******************************************************************************/
/** StoreIndicator command */
typedef struct {
  uint8 encapsulatedIndicator[MAX_ENCAPSULATED_INDICATOR];
  uint32 encapsulatedIndicatorLen;
} cmdStoreIndicator_t;
