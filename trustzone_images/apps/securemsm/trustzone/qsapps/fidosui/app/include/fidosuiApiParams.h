/*
* Copyright (c) 2015 Qualcomm Technologies, Inc.  All Rights Reserved.
* Qualcomm Technologies Proprietary and Confidential.
*/

#pragma once

#include <stdint.h>
#include <auth.h>
#include <fidot.h>

#define TOKEN_LEN              1024 // max 256 content and 256 of margin for QSEE message headers
#define LOCALE_LEN              16 // locale string

#ifdef __RVCT__
#pragma anon_unions
#endif

/******************************************************************************/
/** (1) Initialize */
/******************************************************************************/
typedef struct {
  uint32_t version;
} cmdInitialize_t;
typedef struct {
  uint32_t version;
} rspInitialize_t;
/******************************************************************************/
/** (81) ShowMessageSuiStart */
/******************************************************************************/
typedef struct {
  char secAppName[QC_SEC_APP_NAME_LEN];
  char appId[UAFV1_APPID_MAX_LEN];
  char locale[LOCALE_LEN];
  uint8_t nonce[QC_AUTH_NONCE];
  uint32_t layoutId; /**< This also carries the information if SDAT or SDTT or both are being generated */
  uint32_t content;
  uint64_t content64;
  uint32_t contentLen;
} cmdShowMessageSuiStart_t;
/** ShowMessageSuiStart Response */
typedef struct {
  uint32_t reserved;
} rspShowMessageSuiStart_t;
/******************************************************************************/
/** (82) ShowMessageSuiFinish */
/******************************************************************************/
typedef struct {
  uint32_t reserved;
} cmdShowMessageSuiFinish_t;
/** ShowMessageSuiFinish Response */
typedef struct {
  uint32_t code;
} rspShowMessageSuiFinish_t;
