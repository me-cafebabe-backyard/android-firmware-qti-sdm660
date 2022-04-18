#ifndef VMPM_UTILS_H
#define VMPM_UTILS_H
/*==============================================================================
  FILE:         vmpm_utils.h
  
  OVERVIEW:     This file contains vMPM utility functions
 
  DEPENDENCIES: None

                Copyright (c) 2012-2014,2016 QUALCOMM Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Confidential and Proprietary

===============================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/mpm/inc/vmpm_utils.h#1 $
$DateTime: 2020/02/10 01:57:30 $
=============================================================================*/ 

/*=============================================================================
                     INCLUDE FILES FOR MODULE
=============================================================================*/
#include "vmpm.h"
#include "HALcomdef.h"

/*===========================================================================
 *                            FUNCTION PROTOTYPES
 *===========================================================================*/
/**
 * Returns the time in sclk unit from MPM counter. MPM counter is expected to
 * be running reliably even in low power modes.
 *
 * @Note:
 * This API is just for legacy code. From B family onwards clients should use
 * QTimer base time which is also expected to work in low power modes.
 *
 * @return Time in sclk at MPM hardware.
 */
uint32 vmpm_GetTimetick( void );

/**
 * Writes a wake up tick for this master in to memory region reserved for it
 * in the shared message ram during rpm assisted low power modes. RPM 
 * processor uses it to determine wakeup time for that master. It must be
 * noted that during each rpm assited Sleep cycle, master needs to upate 
 * this value.
 *
 * @param wakeupTick: Time (in ticks) when this master wants rpm
 *                    to wake it up.
 * @return nothing.
 */
void vmpm_SetWakeupTimetick(uint64 wakeupTick);

#endif /* VMPM_UTILS_H */

