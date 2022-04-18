/*==============================================================================
  FILE:         qtmr_lpr.c

  OVERVIEW:     This file provides the sleep QTMR LPR definition
                for the sleep low power modes for deferring timers

  DEPENDENCIES: None

                Copyright (c) 2015-2016 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/sleep2.0/src/lpr/qtmr_lpr.c#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include "comdef.h"
#include "synthLPRM.h"
#include "HALsleep_hwio.h"
#include "sleep_hwio.h"

/*==============================================================================
                              MACRO DEFINTIONS
 =============================================================================*/
/* WAKEUP_EN field bit value definition
 * 0:  The corresponding Qtmer cannot wakeup QDSP6
 *     However, it will still be serviced when QDSP6 is running
 * 
 * 1:  The corresponding Qtmer interrupt can wakeup QDSP6 */
#define WAKEUP_EN_RESERVED_0   ( 1 << 0 ) /* Reserved bit 0              */
#define WAKEUP_EN_RESERVED_1   ( 1 << 1 ) /* Reserved bit 1              */
#define WAKEUP_EN_QTMR_FRAME_0 ( 1 << 2 ) /* QTimer Frame 0 (Kernel)     */
#define WAKEUP_EN_QTMR_FRAME_1 ( 1 << 3 ) /* QTimer Frame 1 (User/Timer) */
#define WAKEUP_EN_QTMR_FRAME_2 ( 1 << 4 ) /* QTimer Frame 2 (Sleep)      */

/* Configuration for wakeup on sleep frame interrupt only */ 
#define DEFER_QTMR_FRAMES_CONFIG  (WAKEUP_EN_QTMR_FRAME_2)

/* Configuration for wakeup on any frame interrupt */
#define UNDEFER_QTMR_FRAMES_CONFIG (WAKEUP_EN_QTMR_FRAME_0 |  \
                                     WAKEUP_EN_QTMR_FRAME_1 | \
                                    WAKEUP_EN_QTMR_FRAME_2) 

/*===========================================================================
                              GLOBAL FUNCTIONS
 ==========================================================================*/
/** 
 * qtmrLPR_deferEnter 
 *  
 * @brief Configures timer frames to prevent interrupts prior to sleep enter
 */
void qtmrLPR_deferEnter(uint64 wakeupTick)
{
  boolean state = synthLPRM_isConfiguringModeFullyCacheable();

  /* If the mode is not fully cacheable, don't defer the timers wakeup interrupt */
  if(FALSE == state)
  {
    SLEEP_HWIO_OUT(L2VIC_WAKEUP_EN, DEFER_QTMR_FRAMES_CONFIG);
  }

  return;
}

/** 
 * qtmrLPR_deferExit
 *  
 * @brief Allows all timer frame interrupts during sleep
 */
void qtmrLPR_deferExit(uint64 wakeupTick)
{
  boolean state = synthLPRM_isConfiguringModeFullyCacheable();

  if(FALSE == state)
  {
    SLEEP_HWIO_OUT(L2VIC_WAKEUP_EN, UNDEFER_QTMR_FRAMES_CONFIG);
  }  

  return;
}

