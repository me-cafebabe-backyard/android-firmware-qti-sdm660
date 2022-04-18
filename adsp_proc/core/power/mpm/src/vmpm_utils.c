/*==============================================================================
  FILE:         vmpm_utils.c

  OVERVIEW:     This file provides target-specific functionality for the 
                Modem Subsystem.

  DEPENDENCIES: None

                Copyright (c) 2011-2013,2016 QUALCOMM Technologies Inc (QTI).
                All Rights Reserved.
                Qualcomm Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/mpm/src/vmpm_utils.c#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include "vmpm_utils.h"
#include "vmpm_hw_hwio.h"
#include "vmpm_internal.h"
#include "vmpm_HAL_Internal.h"

/*===========================================================================
 *                        GLOBAL FUNCTION DEFINITIONS
 *=========================================================================*/
/**
 * Reads time in sclk read from mpm registers.
 *
 * @Note:
 * This API is more for legacy code support. On B family targets, clients 
 * should use QTimer base time instead of sclk based.
 */
uint32 vmpm_GetTimetick( void )
{
  uint32 currTick;
  uint32 lastTick;
  static int mpmHwRegMapped = 0;
  static uint32 mpmTimetickRegAddr = 0;

  if(!mpmHwRegMapped)
  {
    /* Map physical address of actual MPM hw register base to some 
     * virtual address so we can access mpm hardware registers. */
    vmpm_MapHwRegBase();
    mpmTimetickRegAddr = HWIO_MPM2_MPM_SLEEP_TIMETICK_COUNT_VAL_ADDR;
    mpmHwRegMapped = 1;
  }

  /* Reading the counter value once may not return an accurate value if the
   * counter is in the processing of counting to the next value, and several
   * bits are changing.  Instead, the counter is repeatedly read until a
   * consistant value is read. */
  currTick = inpdw(mpmTimetickRegAddr);
  do 
  {
    lastTick = currTick;
    currTick = inpdw(mpmTimetickRegAddr);
  } while( currTick != lastTick );

  return currTick;

}

