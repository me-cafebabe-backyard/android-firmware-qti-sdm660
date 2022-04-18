/** @file QcomChargerAppEventHandler.c

  Helper functions for charger lib for creating and handling events

  Copyright (c) 2016 -2017, Qualcomm Technologies Inc. All rights reserved.

**/

/*===========================================================================

                              EDIT HISTORY

when        who     what, where, why
--------    ----    --------------------------------------------------------
02/13/17    va      Charger Animation fix during jeita zone
11/22/16    va      Display and clear image before startng animation
11/11/16    va      Init AnimType for Initial Animation
10/19/16    sm      Added input parameter to QcomChargerAppEvent_KeyPressHandler() API
11/02/16    mr      Renamed QcomChargerAppEvent_KeyPressEventHandler to QcomChargerAppEvent_KeyPressHandler
                      and removed QcomChargerAppEvent_KeyPressControl()
08/18/16    va      Merge Display and Anim timer
07/06/16    sm      Enabled Clock and Display related changes
06/23/16    va      Adding support for Charger Fg Peripheral dumps
06/21/16    va      Changing debugs to CHARGERAPP_DEBUG
05/31/16    va      Adding Sign of early life suppot
05/25/16    sm      Commented out Clock and Display APIs to Enter/Exit LPM
03/28/16    va      Add logging CHARGER_DEBUG
01/27/16    sm      Initial revision
===========================================================================*/

/*===========================================================================
                    INCLUDE FILES FOR MODULE
===========================================================================*/
#include <Uefi.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/QcomLib.h>
#include "Library/SerialPortShLib.h"
#include <Library/QcomTargetLib.h>
#include <Library/FuseControlLib.h>
#include <api/systemdrivers/pmic/pm_uefi.h>

/**
  Protocol Dependencies
*/
#include <Protocol/EFIPlatformInfo.h>
#include <Protocol/EFIVariableServices.h>
#include <Protocol/EFIQcomCharger.h>

#include <Protocol/EFIDisplayPwr.h>
#include <Protocol/EFIDisplayPwrCtrl.h>
#include <Protocol/EFIClock.h>

#include <Library/UefiLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/ParserLib.h>
#include <Library/BaseMemoryLib.h>
#include <Guid/FileSystemInfo.h>
#include <Guid/FileInfo.h>
#include <api/systemdrivers/pmic/pm_uefi.h>

#include "DDIPlatformInfo.h"
#include <Protocol/SimpleFileSystem.h>

#include "QcomChargerAppEventHandler.h"

#include "QcomChargerApp.h"

/*===========================================================================
                    TYPEDEF AND MACRO DEFINITIONS
===========================================================================*/
/*
This file will implement the functions to setup timer and implment the timer callback, 
also it implement functions to register for key and LPM events and callback functions for key events and LPM events. 
It also implement functions to turn display on/off, and render charging/battery images.
*/

#define CHGAPP_BATTERY_SYMBOL_NOBATTERY            "fv1:\\battery_symbol_NoBattery.bmp"
#define CHGAPP_BATTERY_SYMBOL_NOCHARGER            "fv1:\\battery_symbol_Nocharger.bmp"
#define CHGAPP_BATTERY_SYMBOL_ABOVE_THRESHOLD      "fv1:\\battery_symbol_Soc10.bmp"
#define CHGAPP_BATTERY_SYMBOL_LOWBATTERYCHARGING   "fv1:\\battery_symbol_LowBatteryCharging.bmp"
#define CHGAPP_BATTERY_SYMBOL_LOWBATTERY           "fv1:\\battery_symbol_LowBattery.bmp"
#define CHARGER_TSENS_THERMAL_SYMBOL               "fv1:\\tsens_thermal_symbol.bmp"

#define CHGAPP_ANIM_TIMER_DURATION_IN_US           5000000 /*500 milli sec*/
#define CHGAPP_SEVEN_SEC_WAIT_IN_US                70000000 /*tick is 100ns; 100 * 70000000 = 7sec*/
#define CHGAPP_FLASH_IMAGE_COUNT                   (CHGAPP_SEVEN_SEC_WAIT_IN_US/CHGAPP_ANIM_TIMER_DURATION_IN_US) /* Flash Count which is 14 times */

#define ENTER_LPM                     TRUE
#define EXIT_LPM                      FALSE

typedef enum _CHGAPP_DISP_ANIM_IMG{
  CHGAPP_DISP_ANIM_IMG_LOW_BATTERY,
  CHGAPP_DISP_ANIM_IMG_LOW_BATT_CHARGING,
  CHGAPP_DISP_ANIM_IMG_NUM_MAX = 0x7fffffff
} CHGAPP_DISP_ANIM_IMG_NUM;

static BOOLEAN SystemInLPM = FALSE;
QCOMCHARGERAPP_EVENT_ANIMATION_TYPE gAnimationType = QCOMCHARGERAPP_EVENT_ANIMATION__CHARGING_ANIM;
/******************************************************************************
            LOCAL FUNCTIONS
******************************************************************************/

static EFI_CLOCK_PROTOCOL *ClockProtocol = NULL;
static EFI_QCOM_DISPLAY_PWR_CTRL_PROTOCOL *DisplayPwrCtrlProtocol = NULL;
static EFI_QCOM_CHARGER_PROTOCOL          *pQcomChargerProtocol   = NULL;
STATIC UINT32                              DisplayOffCount        = 0;

extern EFI_STATUS
LoadFromFV(IN   CHAR8 *Name,
           OUT  UINT8 **FileBuffer,
           OUT  UINTN *FileSize);

EFI_EVENT EventAnimImg = (EFI_EVENT)NULL;

/*===========================================================================
                    FUNCTIONS DEFINITIONS
===========================================================================*/

EFI_STATUS
QcomChargerAppEvent_KeyPressHandler( QCOMCHARGERAPP_EVENT_ANIMATION_TYPE AnimationType )
{
  if(!pQcomChargerProtocol)
  {
    gBS->LocateProtocol( &gQcomChargerProtocolGuid, NULL, (VOID **)&pQcomChargerProtocol );
  }

  gAnimationType = AnimationType;

  /*Render Image before exiting LPM to have updated image only for firt time key press ignore subsequent key press as it produced flicker*/
  if(NULL == EventAnimImg)
  {
    if(QCOMCHARGERAPP_EVENT_ANIMATION__LOW_BATTERY_NO_ANIM == AnimationType)
    {
      CHARGERAPP_DEBUG((EFI_D_WARN, "QcomChargerApp:: %a CHGAPP_DISP_LOW_BATTERY with clearnscreen\r\n", __FUNCTION__));
      pQcomChargerProtocol->DisplayImage(EFI_QCOM_CHARGER_DISP_IMAGE_LOWBATTERY, TRUE);
    }
    else
    {
      CHARGERAPP_DEBUG((EFI_D_WARN, "QcomChargerApp:: %a CHGAPP_DISP_LOW_BATTERY_CHARGING with clearnscreen\r\n", __FUNCTION__));
      pQcomChargerProtocol->DisplayImage(EFI_QCOM_CHARGER_DISP_IMAGE_LOWBATTERYCHARGING, TRUE);
    }

    if(PRODMODE_DISABLED || JTAGDebugDisableFusesBlown())
    {
      pQcomChargerProtocol->DumpPeripheral();
    }
  }
  else
  {
    CHARGERAPP_DEBUG((EFI_D_ERROR, "QcomChargerApp: %a follow anim timer Ignore key for display\r\n", __FUNCTION__));
  }

  CHARGERAPP_DEBUG((EFI_D_ERROR, "QcomChargerApp:: %a Turning off display in = %d seconds \r\n", __FUNCTION__, CHGAPP_FLASH_IMAGE_COUNT/2));

  /*Create Timer Event*/
  QcomChargerAppEvent_DisplayTimerEvent(TRUE, TRUE);

  QcomChargerAppEvent_ExitLPM();

  return EFI_SUCCESS;
}
 

VOID QcomChargerAppEvent_HandleLPMClock(BOOLEAN EnterLPM)
{
  EFI_STATUS Status = EFI_SUCCESS;
  if(!ClockProtocol)
  {
    Status = gBS->LocateProtocol(&gEfiClockProtocolGuid, NULL, (VOID **)&ClockProtocol);
  }

  if (ClockProtocol && (EFI_SUCCESS == Status))
  {
    if(EnterLPM)
    {
      Status = ClockProtocol->EnterLowPowerMode(ClockProtocol);
    }
    else
    {
      Status = ClockProtocol->ExitLowPowerMode(ClockProtocol);
    }
    
    if(EFI_SUCCESS != Status)
    {
      CHARGERAPP_DEBUG((EFI_D_ERROR, "QcomChargerApp:: %a ClockProtocol returned error = %d. \r\n", __FUNCTION__, Status));
    }
  }
  else
  {
    CHARGERAPP_DEBUG((EFI_D_ERROR, "QcomChargerApp:: %a Error returned while locating ClockProtocol = %d. \r\n",__FUNCTION__, Status));
  }
}

VOID QcomChargerAppEvent_HandleLPMDisplay(BOOLEAN EnterLPM)
{
  EFI_STATUS Status = EFI_SUCCESS;
  EFI_DISPLAY_TYPE               eDisplayType = EFI_DISPLAY_TYPE_ALL;
  EFI_DISPLAY_POWER_CTRL_STATE   ePowerState  = EFI_DISPLAY_POWER_STATE_OFF;

  if(!DisplayPwrCtrlProtocol)
  {
    Status = gBS->LocateProtocol(&gQcomDisplayPwrCtrlProtocolGuid, NULL, (VOID **)&DisplayPwrCtrlProtocol);
  }

  if (DisplayPwrCtrlProtocol && (EFI_SUCCESS == Status))
  {
    if(EnterLPM)
    {//Turn off display
      ePowerState = EFI_DISPLAY_POWER_STATE_OFF; 
    }
    else
    {//Turn on display
      ePowerState = EFI_DISPLAY_POWER_STATE_ON;
    }

    Status = DisplayPwrCtrlProtocol->DisplayPanelPowerControl(eDisplayType, ePowerState);
   
    if(EFI_SUCCESS != Status)
    {
      CHARGERAPP_DEBUG((EFI_D_ERROR, "QcomChargerApp:: %a DisplayPwrCtrlProtocol returned error = %d. \r\n",__FUNCTION__, Status));
    }
  }
  else
  {
    CHARGERAPP_DEBUG((EFI_D_ERROR, "QcomChargerApp:: %a Error returned while locating DisplayPwrCtrlProtocol = %d. \r\n",__FUNCTION__, Status));
  }

}

//This function gets called when display is turned off.
VOID QcomChargerAppEvent_EnterLPM(VOID)
{
  if(FALSE == SystemInLPM)
  {
    /* During threshold charging, only turn off display and set few clocks to lower frequency, exceptions include Memcore and NPA nodes related clocks. */
    CHARGERAPP_DEBUG((EFI_D_ERROR, "QcomChargerApp:: %a Turning off Display\n\r", __FUNCTION__));

    /* Turn off the display */
    QcomChargerAppEvent_HandleLPMDisplay(ENTER_LPM);

    QcomChargerAppEvent_HandleLPMClock(ENTER_LPM);

    SystemInLPM = TRUE;
  }
}


//This function gets called when display is turned on by key press.
VOID QcomChargerAppEvent_ExitLPM(VOID)
{
  if(TRUE == SystemInLPM)
  {
    QcomChargerAppEvent_HandleLPMClock(EXIT_LPM);

    CHARGERAPP_DEBUG((EFI_D_ERROR, "QcomChargerApp:: %a turning ON display \r\n", __FUNCTION__));

    /* Turn on the display */
    QcomChargerAppEvent_HandleLPMDisplay(EXIT_LPM);

    SystemInLPM = FALSE;
  }
}


/***************************************
    Functions to Display battery symbol on screen
***************************************/

/* Turn off display off */
EFI_STATUS QcomChargerAppEvent_DisplayOff(VOID)
{
  /*periodic timer for key press wait for 7 seconds decrement count.. have 1 second timer
   no key pressed signal Display
   */
  CHARGERAPP_DEBUG((EFI_D_ERROR, "QcomChargerApp:: %a Called = %d s ellapsed Turning off display now \r\n", __FUNCTION__, CHGAPP_FLASH_IMAGE_COUNT/2));
  /*close timer event - display off and animImg*/
  QcomChargerAppEvent_DisplayTimerEvent(FALSE, FALSE);

  QcomChargerAppEvent_EnterLPM();

  return EFI_SUCCESS;
}


//Timer event for 500ms timer to animate Image during charging while display is ON
VOID EFIAPI QcomChargerAppEvent_AnimImgTimer
(
 IN EFI_EVENT        Event,
 IN VOID             *Context
 )
{
  STATIC CHGAPP_DISP_ANIM_IMG_NUM AnimImgNum = CHGAPP_DISP_ANIM_IMG_LOW_BATTERY;
  /*periodic timer for image display every 500ms */
  if(!pQcomChargerProtocol)
  {
    gBS->LocateProtocol( &gQcomChargerProtocolGuid, NULL, (VOID **)&pQcomChargerProtocol );
  }

  if(QCOMCHARGERAPP_EVENT_ANIMATION__CHARGING_ANIM == gAnimationType)
  {
    switch(AnimImgNum)
    {
      case CHGAPP_DISP_ANIM_IMG_LOW_BATTERY:
           pQcomChargerProtocol->DisplayImage(EFI_QCOM_CHARGER_DISP_IMAGE_LOWBATTERYCHARGING, FALSE);
           AnimImgNum = CHGAPP_DISP_ANIM_IMG_LOW_BATT_CHARGING;
           break;
      case CHGAPP_DISP_ANIM_IMG_LOW_BATT_CHARGING:
           pQcomChargerProtocol->DisplayImage(EFI_QCOM_CHARGER_DISP_IMAGE_LOWBATTERY, FALSE);
           AnimImgNum = CHGAPP_DISP_ANIM_IMG_LOW_BATTERY;
           break;
      default:
           break;
    }
  }

  if(++DisplayOffCount >= CHGAPP_FLASH_IMAGE_COUNT)
  {
    DisplayOffCount = 0;
    QcomChargerAppEvent_DisplayOff();
  }
}

EFI_STATUS QcomChargerAppEvent_DisplayTimerEvent(BOOLEAN bDispOffTimer, BOOLEAN AnimTimer)
{
  EFI_STATUS Status = EFI_SUCCESS;

  switch (bDispOffTimer)
  {
    case TRUE:
      /* Create Animation timer */
      if(NULL == EventAnimImg )
      {
        /* To Clear screen from snapdragon logo */
        if(NULL == pQcomChargerProtocol)
        {
          Status = gBS->LocateProtocol( &gQcomChargerProtocolGuid, NULL, (VOID **)&pQcomChargerProtocol );
        }
        if((Status == EFI_SUCCESS) && (NULL != pQcomChargerProtocol))
        {
          pQcomChargerProtocol->DisplayImage(EFI_QCOM_CHARGER_DISP_IMAGE_LOWBATTERYCHARGING, TRUE);
        }
        else
        {
          CHARGERAPP_DEBUG((EFI_D_ERROR, "QcomChargerApp:: %a locate protocol error = %r \r\n", __FUNCTION__, Status));
        }
        Status |= gBS->CreateEvent(EVT_TIMER | EVT_NOTIFY_SIGNAL, TPL_CALLBACK, QcomChargerAppEvent_AnimImgTimer, NULL, /*GUID Display guys provide*/ &EventAnimImg);

      }
      if (TRUE == AnimTimer)
      {
        Status |= gBS->SetTimer(EventAnimImg, TimerPeriodic, CHGAPP_ANIM_TIMER_DURATION_IN_US);
        DisplayOffCount = 0; /* Reset DisplyOff Count */
      }
      break;
    case FALSE:
      if (NULL != EventAnimImg)
      {
        Status |= gBS->CloseEvent (EventAnimImg);
        EventAnimImg = (EFI_EVENT)NULL;
      }
      break;
    default:
      break;
  }

  return Status;
}


EFI_STATUS QcomChargerAppEvent_DispBattSymbol(EFI_QCOM_CHARGER_DISP_IMAGE_TYPE DispImageType)
{

  EFI_STATUS Status = EFI_SUCCESS;

  if(!pQcomChargerProtocol)
  {
    gBS->LocateProtocol( &gQcomChargerProtocolGuid, NULL, (VOID **)&pQcomChargerProtocol );
  }

  if(NULL != pQcomChargerProtocol)
    Status = pQcomChargerProtocol->DisplayImage(DispImageType, TRUE);

  return Status;
}
