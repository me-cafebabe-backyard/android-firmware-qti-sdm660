#ifndef SLEEP_IDLE_PLUGIN_H
#define SLEEP_IDLE_PLUGIN_H
/*============================================================================
  FILE:         sleep_idle_plugin.h

  OVERVIEW:     This file provides the externs and declarations needed for the
                sleep idle plugin subsystem.
 
  DEPENDENCIES: None

                Copyright (c) 2011-2014 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
==============================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/sleep2.0/src/npa_nodes/sleep_idle_plugin.h#1 $
$DateTime: 2020/02/10 01:57:30 $
============================================================================*/
#include "sleep_plugin_clients.h"

/*==============================================================================
                           FUNCTION DECLARATIONS
 =============================================================================*/
/**
 * sleepIdlePlugin_initialize
 * 
 * @brief Initialize the sleep idle plugin subsystem.  This function registers 
 *        the idle plugin node. 
 */
void sleepIdlePlugin_initialize( void );

#endif /* SLEEP_IDLE_PLUGIN_H */

