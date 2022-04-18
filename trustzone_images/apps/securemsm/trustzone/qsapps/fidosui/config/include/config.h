/*
* Copyright (c) 2014 Qualcomm Technologies, Inc.  All Rights Reserved.
* Qualcomm Technologies Proprietary and Confidential.
*/

#pragma once

#include <stdint.h>
#include "config.h"

#define QSAPP_OPTIONAL_PARTNERS_MAX 4

typedef struct {
  uint32_t version;
  int32_t timeout;
  char partners_app_name[QSAPP_OPTIONAL_PARTNERS_MAX][32];  /* zero terminated */
} config_arg_t;

typedef struct {
  config_arg_t arg;
} qsapp_config_t;
