/*
* Copyright (c) 2015 Qualcomm Technologies, Inc.  All Rights Reserved.
* Qualcomm Technologies Proprietary and Confidential.
*/

#pragma once

#include "tci.h"
#include "fidosuiApiParams.h"

/**
* @cond
* Command ID's for communication HLOS Client App -> TZ App.
*/

#define FS_CMD_SUI_FLAG              0x08000000
#define FS_CMD_SUI_PROGRESS_FLAG     0x04000000
#define FS_CMD_SUI_FINAL_FLAG        0x02000000
#define FS_CMD_SUI_MASK              0x0FF00000

#define FS_CMD_INITIALIZE               1
#define FS_CMD_SHOW_MESSAGE_SUI         8 /**< message coming through binder */
#define FS_CMD_SHOW_MESSAGE_SUI_START   (FS_CMD_SUI_FLAG | 81)
#define FS_CMD_SHOW_MESSAGE_SUI_FINISH  (FS_CMD_SUI_FLAG | FS_CMD_SUI_FINAL_FLAG | 82)


/*
* @endcond
*/

typedef union {
  cmdInitialize_t                 initialize;
  cmdShowMessageSuiStart_t        showMessageSui;
  cmdShowMessageSuiStart_t        showMessageSuiStart;
  cmdShowMessageSuiFinish_t       showMessageSuiFinish;
} fsCommandPayload_t;

typedef union {
  rspInitialize_t                 initialize;
  rspShowMessageSuiFinish_t       showMessageSui;
  rspShowMessageSuiStart_t        showMessageSuiStart;
  rspShowMessageSuiFinish_t       showMessageSuiFinish;
} fsResponsePayload_t;

typedef struct __attribute__ ((aligned (0x40))) {
  tciCommandHeader_t           header;
  fsCommandPayload_t  payload;
} tciCommand_t;

typedef struct __attribute__ ((aligned (0x40))) {
  tciResponseHeader_t           header;
  fsResponsePayload_t  payload;
} tciResponse_t;

typedef struct {
  tciCommand_t command;
  tciResponse_t response;
} fstci_t;
