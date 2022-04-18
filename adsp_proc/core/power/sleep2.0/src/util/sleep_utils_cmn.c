/*==============================================================================
  FILE:         sleep_utils_cmn.c
  
  OVERVIEW:     Provides sleep global general interest common functions
 
  DEPENDENCIES: None

                Copyright (c) 2015 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/sleep2.0/src/util/sleep_utils_cmn.c#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include <stdlib.h>
#include "sleep_utils.h"

/*==============================================================================
                        INTERNAL FUNCTION DEFINITIONS
 =============================================================================*/
/*
 * safe_unsigned_addition
 */
uint64 safe_unsigned_addition(uint64 a, uint64 b)
{
  if((UINT64_MAX - a) < b)
  {
    /* clip to maximum */
    return UINT64_MAX;
  }

  return (a + b);
}

