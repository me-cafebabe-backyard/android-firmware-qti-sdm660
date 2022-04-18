#ifndef TPDA_H
#define TPDA_H

/*=============================================================================

FILE:         TPDA.h

DESCRIPTION:  

================================================================================
            Copyright (c) 2014 Qualcomm Technologies, Inc.
                         All Rights Reserved.
          Qualcomm Technologies Proprietary and Confidential
==============================================================================*/

#include "HALcomdef.h"

void TPDAPreInit(uint32 ts_counter_freq);
void TPDASetTimestampFreq(uint32 ts_counter_freq);

#endif //TPDA_H
