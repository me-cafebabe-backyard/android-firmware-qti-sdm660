#ifndef SLEEP_NPAI_H
#define SLEEP_NPAI_H
/*==============================================================================
  FILE:         sleep_npa.h
  
  OVERVIEW:     This file provides the private externs and definitions fpr
                accessing the various sleep nodes and functions.

  DEPENDENCIES: None

                Copyright (c) 2015-2016 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/sleep2.0/src/npa_nodes/sleep_npai.h#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include "comdef.h"

/*==============================================================================
                             TYPES & DEFINITIONS
 =============================================================================*/
/* Node name for the idle plugin */
#define SLEEP_IDLE_PLUGIN_NODE_NAME     "/sleep/idle/plugin"

/* Used to create the node names for LPR clients to main sleep/lpr node
 * This macro will create a unique, standard name based on the base node_name */
#define SLEEP_LPR_CLIENT_NODE(baseName) "/node" baseName

/*==============================================================================
                             EXTERNAL FUNCTIONS
 =============================================================================*/
/**
 * sleepLatencyNode_define
 *
 * @brief Constructs npa resources for latency node
 */
void sleepLatencyNode_define(void);

/**
 * sleepMaxDurNode_define
 *
 * @brief Constructs npa resources for the max duration node
 */
void sleepMaxDurNode_define(void);

/**
 * sleepWakeupNode_define
 *
 * @brief Constructs npa resources for the wakeup node
 */
void sleepWakeupNode_define(void);

#endif /* SLEEP_NPAI_H */

