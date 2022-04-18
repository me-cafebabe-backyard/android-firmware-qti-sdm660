/**
  @file  QcomChargerAppEventHandler.h
  @brief QCOM Charger App event handler API definitions.
*/
/*===========================================================================
  Copyright (c) 2016 QUALCOMM Technologies Incorporated.
  All rights reserved.
  Qualcomm Confidential and Proprietary.
===========================================================================*/

/*===========================================================================

                        EDIT HISTORY

when        who     what, where, why
--------    ----    ---------------------------------------------------------
10/19/16    sm      Added enum QCOMCHARGERAPP_EVENT_ANIMATION_TYPE and input parameter 
                    to QcomChargerAppEvent_KeyPressHandler() API
11/02/16    mr      Renamed QcomChargerAppEvent_KeyPressEventHandler to QcomChargerAppEvent_KeyPressHandler
                    and removed QcomChargerAppEvent_KeyPressControl()
05/31/16    va      Adding Sign of early life suppot
03/14/16    sm      Initial draft
===========================================================================*/
#ifndef __QCOMCHARGERAPPEVENTHANDLER_H__
#define __QCOMCHARGERAPPEVENTHANDLER_H__

/*===========================================================================
                    INCLUDE FILES FOR MODULE
===========================================================================*/
/**
UEFI DEBUG Dependencies
*/
#include <Library/DebugLib.h>
#include <Library/QcomBaseLib.h>
#include <Library/TimerLib.h>

/*===========================================================================
                    MACRO DEFINATIONS
===========================================================================*/
/**  Attached charger type. **/
typedef enum 
{
   QCOMCHARGERAPP_EVENT_ANIMATION__LOW_BATTERY_NO_ANIM,    /**< No charger. */
   QCOMCHARGERAPP_EVENT_ANIMATION__CHARGING_ANIM,    /**< Battery.    */
   QCOMCHARGERAPP_EVENT_ANIMATION__INVALID,    /**< DCIN path.  */
} QCOMCHARGERAPP_EVENT_ANIMATION_TYPE;

/*===========================================================================
                    TYPE DECLARATIONS
===========================================================================*/

/*===========================================================================
                    FUNCTION DEFINITIONS
===========================================================================*/
EFI_STATUS QcomChargerAppEvent_KeyPressHandler( QCOMCHARGERAPP_EVENT_ANIMATION_TYPE AnimationType );

VOID QcomChargerAppEvent_ExitLPM(VOID);

EFI_STATUS QcomChargerAppEvent_DisplayTimerEvent(BOOLEAN bDispOffTimer, BOOLEAN AnimTimer);
EFI_STATUS QcomChargerAppEvent_DispBattSymbol(EFI_QCOM_CHARGER_DISP_IMAGE_TYPE DispImageType);

#endif  /* __QCOMCHARGERAPPEVENTHANDLER_H__ */

