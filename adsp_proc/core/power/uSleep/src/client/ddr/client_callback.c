/*==============================================================================
  FILE:         client_callback.c

  OVERVIEW:     This file provides uSleep client callback functions

  DEPENDENCIES: None
  
                Copyright (c) 2014-2016 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/uSleep/src/client/ddr/client_callback.c#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include <stdlib.h>
#include "DALStdDef.h"
#include "CoreVerify.h"
#include "uSleep.h"
#include "uSleepi.h"
#include "uSleep_util.h"
#include "uSleep_ddr_log.h"
#include "qurt.h"
#include "uSleep_trans.h"

/*==============================================================================
                           TYPE & MACRO DEFINITIONS
 =============================================================================*/
/* Macros for locking/unlocking the mutex around uSleep callback data access */
#define USLEEP_CB_LOCK()  qurt_mutex_lock(&g_uSleepCallbackMutex);
#define USLEEP_CB_FREE()  qurt_mutex_unlock(&g_uSleepCallbackMutex);

/*==============================================================================
                             GLOBAL VARIABLES
 =============================================================================*/
/* Master callback structure that contains the user & guest callback data.
 * This structure will be populated as clients register their callbacks */
uSleep_callback_data g_uSleepCallbacks = {0, 0, NULL, NULL};

/* Lock for callback registration */
static qurt_mutex_t g_uSleepCallbackMutex;

/*==============================================================================
                             EXTERNAL VARIABLES
 =============================================================================*/
extern qurt_mutex_t g_uSleepMutex;

/*==============================================================================
                        INTERNAL DDR SECTION FUNCTIONS
 =============================================================================*/
/**
 * uSleep_userSignalCallback
 * 
 * @brief Callback function that is added to the guest PD callback list that
 *        simply triggers and waits for the user PD callbacks to execute
 * 
 * @param state:    enum to indicate if uImage is entering or exiting
 * @param signals:  signal structure that was given to the registration
 *                  function.  These are the handshake signals used to
 *                  coordinate the guest-user PD callback system
 * 
 * @return USLEEP_SUCCESS or USLEEP_FAILURE
 */
static uint32 uSleep_userSignalCallback(uSleep_state_notification  state, 
                                        uSleep_signals             *signals)
{
  /* Callback to simply signal user task to execute its callbacks and wait */
  if(USLEEP_STATE_ENTER == state)
  {
    qurt_anysignal_set(&signals->start, USLEEP_SIGNAL_START_ENTER);
  }
  else
  {
    qurt_anysignal_set(&signals->start, USLEEP_SIGNAL_START_EXIT);
  }

  qurt_signal_wait(&signals->done,
                   USLEEP_SIGNAL_DONE_FINISHED,
                   QURT_SIGNAL_ATTR_WAIT_ALL);

  qurt_signal_clear(&signals->done, USLEEP_SIGNAL_DONE_FINISHED);

  return USLEEP_SUCCESS;
}

/*==============================================================================
                    EXTERNAL DDR SECTION API FUNCTIONS
 =============================================================================*/
/*
 * uSleep_guestClientInit
 */
void uSleep_guestClientInit(void)
{
  qurt_mutex_init(&g_uSleepMutex);
  qurt_mutex_init(&g_uSleepCallbackMutex);
  return;
}

/*
 * uSleep_registerNotificationCallback
 */
uSleep_notification_cb_handle uSleep_registerNotificationCallback(
                                uint32                      enterLat,
                                uint32                      exitLat,
                                uSleep_notification_cb_type callback)
{
  uSleep_callback_list **workingList;

  /* If caller didn't provide a callback, there is nothing to do. */
  if((NULL == callback) || (enterLat > INT32_MAX) || (exitLat > INT32_MAX))
  {
    return 0;
  }

  /* Lock data access */
  USLEEP_CB_LOCK();

  uSleepDDRLog_printf(USLEEP_DDR_LOG_LEVEL_TRANSITION, 1,
                      "Registering guest notification callback "
                      "(callback 0x%x)",
                      (uint32)callback);

  workingList = &g_uSleepCallbacks.callback_list;

  if(NULL != *workingList)
  {
    /* Move to last one in the list */
    do
    {
      /* Verify callback is not already registered */
      CORE_VERIFY((*workingList)->callback != callback);
      workingList = &((*workingList)->next);
    }while(NULL != *workingList);
  }

  CORE_VERIFY_PTR(*workingList = calloc(1, sizeof(uSleep_callback_list)));
  
  (*workingList)->callback = callback;

  /* Add latency here since we already have the mutex */
  g_uSleepCallbacks.enterLat  += enterLat;
  g_uSleepCallbacks.exitLat   += exitLat;
  
  /* Add the callback latency to the transition time */
  uSleepTrans_adjustLatency((int32)enterLat, (int32)exitLat);

  USLEEP_CB_FREE();
  
  return (uSleep_notification_cb_handle)(*workingList);
}

/*
 * uSleep_addUserCallbackLatency
 */
uint32 uSleep_addUserCallbackLatency(uint32 enterLat, uint32 exitLat)
{
  /* Limit callback latencies to something reasonable */
  CORE_VERIFY((enterLat < INT32_MAX) && (exitLat < INT32_MAX));

  USLEEP_CB_LOCK();
  g_uSleepCallbacks.enterLat  += enterLat;
  g_uSleepCallbacks.exitLat   += exitLat;

  /* Add the callback latency to the transition time */
  uSleepTrans_adjustLatency((int32)enterLat, (int32)exitLat);
  USLEEP_CB_FREE();

  return USLEEP_SUCCESS;
}

/*
 * uSleep_registerUserNotificationCallback
 */
uint32 uSleep_registerUserNotificationCallback(uSleep_signals *signals)
{
  /* The user signaling callback will be added to the function list */
  uSleep_user_callback_list **workingList;

  /* Lock data access */
  USLEEP_CB_LOCK();

  workingList = &g_uSleepCallbacks.user_callback_list;

  if(NULL != *workingList)
  {
    /* Move to last one in the list */
    do
    {
      /* Verify callback is not already registered */
      CORE_VERIFY((*workingList)->signals != signals);
      workingList = &((*workingList)->next);
    }while(NULL != *workingList);
  }
  
  uSleepDDRLog_printf(USLEEP_DDR_LOG_LEVEL_TRANSITION, 0,
                      "Registering user notification callback");

  /* Add initial callback element */
  CORE_VERIFY_PTR(*workingList = calloc(1, sizeof(uSleep_user_callback_list)));
  
  (*workingList)->signals   = signals;
  (*workingList)->callback  = uSleep_userSignalCallback;

  USLEEP_CB_FREE();

  return USLEEP_SUCCESS;
}


