/*
* Copyright (c) 2014 Qualcomm Technologies, Inc.  All Rights Reserved.
* Qualcomm Technologies Proprietary and Confidential.
*/

#pragma once

#include "tci.h"
#include "fcApiParams.h"

/**
* @cond
* Command ID's for communication HLOS Client App -> TZ App.
*/

#define FC_CMD_INITIALIZE               1
#define FC_CMD_GET_INFO                 2
#define FC_CMD_REGISTER                 3
#define FC_CMD_SIGN                     4
#define FC_CMD_SET_CHALLENGE            5
#define FC_CMD_PROVISION               99

/*
* @endcond
*/

typedef union {
  cmdInitialize_t                 initialize;
  cmdGetInfo_t                    getInfo;
  cmdRegister_t                   reg;
  cmdSign_t                       sign;
  cmdSetChallenge_t               setChallenge;
  cmdProvision_t                  provision;
} fcCommandPayload_t;

typedef union {
  rspInitialize_t                 initialize;
  rspGetInfo_t                    getInfo;
  rspRegister_t                   reg;
  rspSign_t                       sign;
  rspSetChallenge_t               setChallenge;
  rspProvision_t                  provision;
} fcResponsePayload_t;

typedef struct __attribute__ ((aligned (0x40))) {
  tciCommandHeader_t           header;
  fcCommandPayload_t  payload;
} tciCommand_t;

typedef struct __attribute__ ((aligned (0x40))) {
  tciResponseHeader_t           header;
  fcResponsePayload_t  payload;
} tciResponse_t;

typedef struct {
  tciCommand_t command;
  tciResponse_t response;
} fctci_t;
