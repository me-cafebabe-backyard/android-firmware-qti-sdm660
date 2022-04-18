/*
* Copyright (c) 2015 Qualcomm Technologies, Inc.
* All Rights Reserved.
* Confidential and Proprietary - Qualcomm Technologies, Inc.
*/

#include "config.h"

#define FIDOSUI_VERSION 1

/*lint -esym(506,g_config) */
qsapp_config_t  g_config = {
  {
    FIDOSUI_VERSION,
    10000, /**< timeout, ms */
    {
      "fidocrypto",
      {0},
      {0},
      {0}
    },
  },
};


