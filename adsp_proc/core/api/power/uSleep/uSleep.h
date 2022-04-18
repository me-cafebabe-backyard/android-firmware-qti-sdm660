#ifndef USLEEP_H
#define USLEEP_H
/*==============================================================================
  FILE:         uSleep.h

  OVERVIEW:     Provides the public API interface functions and types for uSleep

  DEPENDENCIES: The build option for uSleep / island must be enabled
  
                Copyright (c) 2014-2016 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/api/power/uSleep/uSleep.h#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include "comdef.h"
#include "uSleep_mode_trans.h"

 /*==============================================================================
                           USLEEP USER CLIENT NODE
 =============================================================================*/
/* User client NPA node name used to support normal <-> island transitions. */
#define USLEEP_NODE_NAME                   "/core/uSleep"

/* Valid required requests for the user client node */
#define USLEEP_CLIENT_RESTRICT_ISLAND      0
#define USLEEP_CLIENT_ALLOW_ISLAND         1

/*==============================================================================
                              DEFINES & TYPES
 =============================================================================*/
/* uSleep API function error codes */
#define USLEEP_SUCCESS  0
#define USLEEP_FAILURE  1

/* Enumeration for the sleep modes available in uSleep mode.
 * LPM+ is target specific and is typically APCR/power collapse with
 * RPM handshake. */
typedef enum uSleep_power_mode
{
  USLEEP_LPM_PLUS_ENABLE  = 0,  /* Enable the LPR+ mode */
  USLEEP_LPM_PLUS_DISABLE = 1,  /* Disable the LPR+ mode */

  USLEEP_LPM_MAX_MODE           /* Maximum LPM option */
}uSleep_power_mode;

/* Legacy definitions for power mode selection */
#define USLEEP_CXO_SHUTDOWN_ENABLE    USLEEP_LPM_PLUS_ENABLE
#define USLEEP_CXO_SHUTDOWN_DISABLE   USLEEP_LPM_PLUS_DISABLE
#define USLEEP_RETENTION_ENABLE       USLEEP_LPM_PLUS_ENABLE
#define USLEEP_RETENTION_DISABLE      USLEEP_LPM_PLUS_DISABLE
  
/*==============================================================================
                      MAIN uSLEEP FUNCTION DECLARATIONS
 =============================================================================*/
/** 
 * uSleep_setLowPowerMode
 * 
 * @brief Indicates if a particular power mode is allowed to enter based on 
 *        the use case.  This is a direct enable/disable and the mode will be
 *        set from the last call to this function (no aggrigation).
 *  
 * @note This function is only intended for island mode. 
 *       It has no meaning in normal operational mode. 
 * 
 * @param mode: ENUM to enabled/disabled the power mode
 *  
 * @return USLEEP_SUCCESS or USLEEP_FAILURE
 */
uint32 uSleep_setLowPowerMode(uSleep_power_mode mode);

#endif /* USLEEP_H */

