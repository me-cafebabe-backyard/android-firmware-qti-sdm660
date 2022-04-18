/*==============================================================================
  FILE:         island.c

  OVERVIEW:     This file provides island (hardware based) transition functions

  DEPENDENCIES: Functions are located in normal mode memory section
  
                Copyright (c) 2016-2017 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/uSleep/src/transition/ddr/island.c#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include "comdef.h"
#include "rpmclient.h"
#include "uSleep_transi.h"
#include "island_spm.h"

/*==============================================================================
                             INTERNAL VARIABLES
 =============================================================================*/
/* Results from the RPM call to force the sync of the various sets before
 * entering island mode */
static uint32 g_rpmSleepSetSync;
static uint32 g_rpmNextActiveSetResult;

/*==============================================================================
                       EXTERNAL FUNCTION DEFINITIONS
 =============================================================================*/
/*
 * uSleep_transitionInitialize
 */
void uSleep_transitionInitialize(void)
{
  /* Setup required hardware transition data */
  islandSPM_setupSequenceTransition();

  return;
}

/*
 * uSleep_prepareForEntry
 */
void uSleep_prepareForEntry(void)
{
  /* Disable the RPM interrupt so the sync calls do not cause us to
   * exit uImage with the ACK interrupt */
  rpm_mask_interrupt(true);

  /* Flush the sleep/next active sets */
  g_rpmSleepSetSync         = rpm_force_sync(RPM_SLEEP_SET);
  g_rpmNextActiveSetResult  = rpm_force_sync(RPM_NEXT_ACTIVE_SET); 

  return;
}

/*
 * uSleep_completeExit
 */
void uSleep_completeExit(uSleep_transition_mode mode)
{
  /* Use NAS result if valid, else SS */
  rpm_churn_queue(0 != g_rpmNextActiveSetResult ? g_rpmNextActiveSetResult : g_rpmSleepSetSync);

  /* Reenable RPM interrupt that was disabled from the set sync on island entry */
  rpm_mask_interrupt(false);

  return;
}

