/*==============================================================================
  FILE:         sleep_target_cmn.c

  OVERVIEW:     This file provides common target-specific functionality for the
                modem Subsystem.

  DEPENDENCIES: None

                Copyright (c) 2015-2016 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/sleep2.0/src/target/sleep_target_cmn.c#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include "comdef.h"

/*==============================================================================
                             FUNCTION DECLARATIONS
 =============================================================================*/
/** 
 * sleepTarget_wakeupHandler
 * 
 * @brief Null handler for the registered idle timer interrupts
 */
void sleepTarget_wakeupHandler(uint32 param)
{
  return;
}

/**
 * sleepTarget_RPMWakeupHandler
 *
 * @brief Null handler for the RPM wakeup (timed trigger) interrupt.
 */
void sleepTarget_RPMWakeupHandler(uint32 param)
{
  return;
}

