/*
* Copyright (c) 2015 Qualcomm Technologies, Inc.  All Rights Reserved.
* Qualcomm Technologies Proprietary and Confidential.
*/

#pragma once

#include <stdbool.h>
#include <stdint.h>
#include "locale.h"

locale_data_t const * getLocaleData(uint32_t layoutId, char const * locale);
