#ifndef USLEEPI_H
#define USLEEPI_H
/*==============================================================================
  FILE:         uSleepi.h

  OVERVIEW:     Internal interface functions and types for uSleep

  DEPENDENCIES: None
  
                Copyright (c) 2014-2016 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/uSleep/src/uSleepi.h#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include "DALStdDef.h"
#include "uTimetick.h"
#include "uSleep.h"
#include "utimer.h"
#include "qurt.h"
#include "npa.h"

/*==============================================================================
                              DEFINES & TYPES
 =============================================================================*/
/**
 * uSleep_internal_state
 * 
 * @brief Internal states for uSleep mode used to control tranistions and other
 *        behavior
 */
typedef enum uSleep_internal_state
{
  /* Steady mode state */
  uSLEEP_INTERNAL_STATE_IN_DDR            = 0x0001, 
  uSLEEP_INTERNAL_STATE_ACTIVE            = 0x0002,

  /* Entry transitions */
  uSLEEP_INTERNAL_STATE_FULL_ENTRY        = 0x0010, /* Initial entry request stage */
  uSLEEP_INTERNAL_STATE_STAGE1_ENTRY      = 0x0020, /* Waiting for HW/Kernel to complete
                                                     * entry */
  uSLEEP_INTERNAL_STATE_STAGE2_ENTRY      = 0x0040, /* HW/Kernel completed entry,
                                                     * SW finishing entry */

  /* Exit transitions */
  uSLEEP_INTERNAL_STATE_STAGE1_EXIT       = 0x0100, /* Initial exit stage, where exit preperation
                                                     * is done */
  uSLEEP_INTERNAL_STATE_STAGE2_EXIT       = 0x0200, /* Exit prep is done, continuing with 
                                                     * first kernel stage exit */ 
  uSLEEP_INTERNAL_STATE_FATAL_EXIT        = 0x0400, /* Fatal error exit stage */

  /* Exited states */
  uSLEEP_INTERNAL_STATE_FAST_EXIT         = 0x1000,
  uSLEEP_INTERNAL_STATE_FULL_EXIT         = 0x2000,

  uSLEEP_INTERNAL_STATE_MAX
}uSleep_internal_state;

/**
 * uSleep_signals
 * 
 * @brief Signals to use to indicate callback function execution state between 
 *        different PD's
 */
typedef struct uSleep_signals_s
{
  qurt_anysignal_t start; /* Signal to start executing callbacks -user wait */ 
  qurt_signal_t    done;  /* Signal to indicate callbacks are done -guest wait*/
}uSleep_signals;

/**
 * uSleep_callback_list
 * 
 * @brief Main callback strucutre for guest PD
 */
typedef struct uSleep_callback_list_s
{
  uSleep_notification_cb_type   callback;
  struct uSleep_callback_list_s *next;
}uSleep_callback_list;

/**
 * uSleep_user_signal_cb_type
 * 
 * @brief User callback function prototype
 */
typedef uint32 (*uSleep_user_signal_cb_type)(uSleep_state_notification  state, 
                                             uSleep_signals             *signals);

/**
 * uSleep_user_callback_list
 * 
 * @brief Main callback strucutre for user PD which includes signals that guest
 *        PD will wait on when calling the user callbacks
 */
typedef struct uSleep_user_callback_list_s
{
  uSleep_user_signal_cb_type          callback;
  uSleep_signals                      *signals;
  struct uSleep_user_callback_list_s  *next;
}uSleep_user_callback_list;

/**
 * uSleep_callback_data
 * 
 * @brief Main callback structure that contains the two callback function lists
 *        as well as the total entry/exit latencies for the registered callbacks
 */
typedef struct uSleep_callback_data_s
{
  uint32                    enterLat;
  uint32                    exitLat;
  uSleep_callback_list      *callback_list;
  uSleep_user_callback_list *user_callback_list;
}uSleep_callback_data;

/* Signal values to trigger the execution of user callbacks */
#define USLEEP_SIGNAL_START_ENTER     0x01
#define USLEEP_SIGNAL_START_EXIT      0x02 /* exit callbacks not currently called */

/* Signal value for guest PD to wait on for user callbacks to finished exeuction */ 
#define USLEEP_SIGNAL_DONE_FINISHED   0x01

#endif /* USLEEPI_H */

