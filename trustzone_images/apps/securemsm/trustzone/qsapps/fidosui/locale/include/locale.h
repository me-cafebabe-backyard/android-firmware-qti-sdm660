/*
* Copyright (c) 2014 Qualcomm Technologies, Inc.  All Rights Reserved.
* Qualcomm Technologies Proprietary and Confidential.
*/

#pragma once

#include <stdint.h>
#include "config.h"

typedef struct {
  char *title_pre;
  char *title_post;
  char *desc_pre;
  char *desc_post;
  char *ok;
  char *cancel;
} locale_data_t;

typedef struct {
  uint32_t layoutId;
  uint32_t is_default;
  char *locale;
  locale_data_t data;
} layout_data_t;

