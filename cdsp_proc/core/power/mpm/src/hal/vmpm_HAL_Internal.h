#ifndef VMPM_HAL_INTERNAL_H
#define VMPM_HAL_INTERNAL_H
/*=========================================================================

FILE:         vmpm_HAL_Internal.h

DESCRIPTION:  This is the hardware abstraction layer internal interface for 
              the MPM interrupt controller block.

DEPENDENCIES: None

              Copyright (c) 2008-2013,2016 QUALCOMM Technologies, Inc. (QTI).
              All Rights Reserved.
              Qualcomm Confidential and Proprietary

===============================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/mpm/src/hal/vmpm_HAL_Internal.h#1 $
$DateTime: 2020/02/10 01:57:30 $
=============================================================================*/ 

/* -----------------------------------------------------------------------
**                        FUNCTION DECLARATIONS
** ----------------------------------------------------------------------- */
/**
 * Prepares mpm driver to perform IPC with RPM afterwards. This is just
 * a setup function and it does not perform any actual IPC. 
 *
 * @Note
 * This OS dependent function. For example,
 *  - in case where we use DAL IPC, it would be attaching to DAL IPC device.
 *  - On some target this function will map the addresses of IPC registers 
 *    for the process they are running in.
 */
void vmpm_HAL_SetupIPC( void );

/**
 * Sends an IPC interrupt to RPM whenver vMPM configuration for this
 * master has been changed. This happens when any interrupt/gpio 
 * configuration (MPM2 supported trigger type) is changed in DAL
 * which changes configuration in HAL (detection, polarity).
 *
 * @Note:
 * This function may have different implementation on different OSes.
 * - The default implementation is using DAL IPC interrupt interface.
 * - Alternative one would be to write directly to IPC registers.
 */
void vmpm_send_interrupt( void );

#endif /* VMPM_HAL_INTERNAL_H */

