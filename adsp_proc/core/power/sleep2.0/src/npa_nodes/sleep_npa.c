/*==============================================================================
  FILE:         sleep_npa.c
  
  OVERVIEW:     This file provides the NPA node definitions for latency and
                wakeup nodes.

  DEPENDENCIES: None

                Copyright (c) 2010-2016 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/sleep2.0/src/npa_nodes/sleep_npa.c#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include "sleep_npai.h"

/*==============================================================================
                            EXTERNAL FUNCTIONS
 =============================================================================*/
/*
 * sleepNPA_initialize
 */
void sleepNPA_initialize(void)
{
  /* Define the various sleep nodes */
  sleepWakeupNode_define();
  sleepMaxDurNode_define();
  sleepLatencyNode_define();

  return;
}

