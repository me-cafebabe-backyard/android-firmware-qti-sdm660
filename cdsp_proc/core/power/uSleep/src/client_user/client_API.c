/*==============================================================================
  FILE:         uSleep_api.c

  OVERVIEW:     This file provides uSleep API functions for user PD that are
                located in the ISLAND section

  DEPENDENCIES: None
  
                Copyright (c) 2014-2015 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/uSleep/src/client_user/client_API.c#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include "comdef.h"
#include "uSleep.h"
#include "uSleepi.h"
#include "uSleep_util.h"
#include "uSleep_qdi.h"
#include "qurt.h"
/*==============================================================================
                           INTERNAL VARIABLES
 =============================================================================*/
/* QDI Client Handle to communicate with Guest OS layer. This variable needs to
 * be located in island section memory, but is initialized while in normal
 * operational mode */
int g_uSleepQDIClientHandle = -1;

/*==============================================================================
                          EXTERNAL API FUNCTIONS
 =============================================================================*/
/*
 * uSleep_exit
 */
uint32 uSleep_exit(void)
{
  return qurt_qdi_handle_invoke(g_uSleepQDIClientHandle, USLEEP_QDI_EXIT);
}

/*
 * uSleep_setLowPowerMode
 */
uint32 uSleep_setLowPowerMode(uSleep_power_mode mode)
{
  return qurt_qdi_handle_invoke(g_uSleepQDIClientHandle, 
                                USLEEP_QDI_SET_LOW_POWER_MODE, mode); 
}

/*
 * uSleep_getCriticalExitTime
 */
uint64 uSleep_getCriticalExitTime(void)
{
  uint64 exitTime;
  uint32 status;

  status = qurt_qdi_handle_invoke(g_uSleepQDIClientHandle,
                                  USLEEP_QDI_GET_CRITICAL_EXIT_TIME,
                                  &exitTime);
  return(exitTime);
}

/*
 * uSleep_isExitRequested
 */
boolean uSleep_isExitRequested(void)
{
  return (boolean)qurt_qdi_handle_invoke(g_uSleepQDIClientHandle,
                                         USLEEP_QDI_IS_EXIT_REQUESTED);
}

