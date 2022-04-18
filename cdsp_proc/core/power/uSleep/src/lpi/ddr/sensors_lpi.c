/*==============================================================================
  FILE:         sensors_lpi.c

  OVERVIEW:     This file provides the uSleep sensors LPI definition.

  DEPENDENCIES: None

                Copyright (c) 2015-2016 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/uSleep/src/lpi/ddr/sensors_lpi.c#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include "DALStdDef.h"
#include "CoreVerify.h"
#include "uSleep_os.h"
#include "uSleep_util.h"
#include "uSleep_transi.h"

/*===========================================================================
                              GLOBAL FUNCTIONS
 ==========================================================================*/
/** 
 * sensorsLPI_enter 
 *  
 * @brief Function that will be called while entering the sensor LPI
 */
void sensorsLPI_enter(uint64 unused)
{
  /* Set main entry pointer to begin transition */
  uSleepOS_setIdleFunctionPtr(uSleepOS_mainEntry);

  return;
}

/** 
 * sensorsLPI_exit 
 *  
 * @brief Function that will be called while exiting from the sensors LPI
 */
void sensorsLPI_exit(void)
{
  return;
}

/** 
 * sensorsLPI_initialize 
 *  
 * @brief Function that will be called at power island init time
 */
void sensorsLPI_initialize(void)
{
  /* Set initial uSleep transition times based on the original XML values. These will later be 
   * adjusted as transitions happen. */
  uSleepTrans_initLatency();

  return;
}
