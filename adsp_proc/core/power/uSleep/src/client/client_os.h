#ifndef CLIENT_OS_H
#define CLIENT_OS_H
/*==============================================================================
  FILE:         client_os.h

  OVERVIEW:     uSleep guest client types

  DEPENDENCIES: None
  
                Copyright (c) 2014-2015 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/uSleep/src/client/client_os.h#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include "DALStdDef.h"

/*==============================================================================
                            FUNCTION DECLARATIONS
 =============================================================================*/
/**
 * uSleep_registerUserNotificationCallback
 * 
 * @brief Function that is called once during user PD callback registration
 *        that will add a guest callback to signal the user callbacks to
 *        execute
 * 
 * @param signals: Handshake signals used to coordinate the guest-user callback
 *                 system. These signals are specific to each seperate user PD.
 * 
 * @return USLEEP_SUCCESS or USLEEP_FAILURE 
 */
uint32 uSleep_registerUserNotificationCallback(uSleep_signals *signals);

/**
 * uSleep_addUserCallbackLatency 
 *  
 * @brief Helper function that adds the enter/exit latencies for a callback 
 *        function
 *  
 * @note  This function should not be called directly, it will be called 
 *        appropriately via the registration API
 * 
 * @param enterLat: Enter latency (in ticks) of the callback being registered 
 * @param exitLat:  Exit latency (in ticks) of the callback being registered 
 *  
 * @return USLEEP_SUCCESS or USLEEP_FAILURE 
 */
uint32 uSleep_addUserCallbackLatency(uint32 enterLat, uint32 exitLat);

/** 
 * uSleep_guestClientInit
 * 
 * @brief Initializes the guest PD client data
 */
void uSleep_guestClientInit(void);

#endif /* CLIENT_OS_H */

