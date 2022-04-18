/*=============================================================================

FILE:         TPDA.c

DESCRIPTION:  

================================================================================
            Copyright (c) 2014 Qualcomm Technologies, Inc.
                         All Rights Reserved.
          Qualcomm Technologies Proprietary and Confidential
==============================================================================*/

#include "TPDA.h"
#include "halqdss_tpda.c"  //lite_inline 
#include "qdss_tpda_config.h"


uint32 qdss_tpdas[] = QDSS_TPDA_BASE_ADDRS;

__inline void TPDASetTimestampFreq(uint32 ts_counter_freq)
{
   int num_tpdas = sizeof(qdss_tpdas) >> 2; 
   int i = 0;
   for (i=0; i < num_tpdas; i++) {
      HAL_qdss_tpda_HalConfigInit(qdss_tpdas[i]);
      HAL_qdss_tpda_AccessUnLock();
      HAL_qdss_tpda_SetTimeStampFreq(ts_counter_freq);
      HAL_qdss_tpda_AccessLock();
   }
}


__attribute__((section("qdss_cram_reclaim_pool")))
__inline void TPDAPreInit(uint32 ts_counter_freq)
{
      TPDASetTimestampFreq(ts_counter_freq);
}

