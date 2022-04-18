/*
* Copyright (c) 2015 Qualcomm Technologies, Inc.
* All Rights Reserved.
* Confidential and Proprietary - Qualcomm Technologies, Inc.
*/

#include <stddef.h>
#include <string.h>
#include "locale.h"
#include "layout.h"


#ifndef LENGTH
#define LENGTH(X) (sizeof(X)/sizeof((X)[0]))
#endif

layout_data_t const layout_data[] = {
  {LAYOUT_ID_SAMPLE_REG, 1, "en", {"Registering to ", ".", "Description: ", NULL, "OK", "Cancel" } },
  {LAYOUT_ID_SAMPLE_AUTH, 1, "en", { "Authenticating to ", ".", "Description: ", NULL, "OK", "Cancel" } },
  {LAYOUT_ID_SAMPLE_TX, 1, "en", { "Transaction @ ", ".", "Transaction details: ", NULL, "OK", "Cancel" } },
  {LAYOUT_ID_SAMPLE_TX_PNG, 1, "en", { "Transaction @ ", ".", "Transaction details: ", NULL, "OK", "Cancel" } },
  {LAYOUT_ID_FP_REG, 1, "en", { "Transaction @ ", ".", "Transaction details: ", NULL, NULL, "Cancel" } },
  {LAYOUT_ID_FP_AUTH, 1, "en", { "Authenticating to ", ".", "Transaction details: ", NULL, NULL, "Cancel" } },
  {LAYOUT_ID_FP_TX, 1, "en", { "Transaction @ ", ".", "Transaction details: ", NULL, NULL, "Cancel" } },
  {LAYOUT_ID_FP_TX_PNG, 1, "en", { "Transaction @ ", ".", "Transaction details: ", NULL, NULL, "Cancel" } },
};

size_t const layout_data_len = LENGTH(layout_data);




