#ifndef SLEEP_PLUGIN_CLIENTS_H
#define SLEEP_PLUGIN_CLIENTS_H
/*============================================================================
  FILE:         sleep_plugin_clients.h

  OVERVIEW:     This file provides the declarations needed for the sleep idle
                plugin subsystem.
 
  DEPENDENCIES: None

                Copyright (c) 2014-2015 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
==============================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/sleep2.0/inc/sleep_plugin_clients.h#1 $
$DateTime: 2020/02/10 01:57:30 $
============================================================================*/
#include "npa.h"

/*==============================================================================
                            GLOBAL DEFINITIONS
 =============================================================================*/
/**
 * SLEEP_IDLE_PLUGIN_CLIENT_LPM_HOLD_OFF
 *
 * @brief NPA client type that can hold off Sleep from executing any
 *        low power modes.
 */
#define SLEEP_IDLE_PLUGIN_CLIENT_LPM_HOLD_OFF         NPA_CLIENT_CUSTOM1

#endif /* SLEEP_PLUGIN_CLIENTS_H */

