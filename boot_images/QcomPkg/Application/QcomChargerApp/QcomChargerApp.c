/** @file QcomChargerApp.c

  Implements the Qualcomm's Charging application

  Copyright (c) 2016,  Qualcomm Technologies Inc. All rights reserved.

**/

/*=============================================================================

                        EDIT HISTORY

when        who     what, where, why
--------    ----    -----------------------------------------------------------
11/10/16    va      Adding crash dump watchdog support
11/07/16    va      Skip once detected as Debug Board
10/19/16    sm      Added input parameters to QcomChargerAppEvent_KeyPressHandler() API call
10/12/16    sv      Fixed Array 'FormatString' KW issue. CR:1063098
09/29/16    va      update to print function names %a and handle %r format specifier for file logging
11/02/16    mr      Removed QcomChargerAppEvent_KeyPressControl() API call and
                    Added keypress check after WaitForTimeout in MonitorCharging API
09/06/16    cs      wipower changes to remove 3.5 sec, not suspend DCIn
08/12/16    va      Adding Charger led indication support
08/10/16    sm      Added changes to skip ChargerApp for RUMI
07/26/16    va      Restarting FG Changes on warm boot
07/15/16    cs      added wipower support
07/07/16    va      DEBUG print to print time stamp in seconds
07/06/16    sm      Added changes to explicitly disable charging for CDP Platform
06/28/16    va      Changes to share charger info to smem
06/21/16    va      Adding Thermal and File log support
06/17/16    vk      Delete entry log message
05/31/16    va      Adding Sign of early life suppot
05/23/16    sm      Added changes to handling EFI_QCOM_CHARGER_ACTION_NO_CHARGE_WAIT action
04/22/16    sm      Added TakeAction() API call for more ChargingAction
04/13/16    sm      Added support for CDP platform
03/28/16    va      Add logging CHARGER_DEBUG
03/21/16    va      Adding Exit API for clean up
03/15/16    sm      Added changes for bring up to only enter and exit the app
                 without performing any checks.
01/27/16    sm      Initial draft for new architecture of Charger app module
=============================================================================*/

/*===========================================================================*/
/*                  INCLUDE FILES                                            */
/*===========================================================================*/
#include <Uefi.h>

/**
  EFI interfaces
 */
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/QcomLib.h>
#include <Library/QcomUtilsLib.h>
#include <api/systemdrivers/pmic/pm_uefi.h>
#include <Library/QcomTargetLib.h>
#include <Library/FuseControlLib.h>
#include <Library/QcomBaseLib.h>

#include <Protocol/EFIVariableServices.h>
#include <Library/MemoryAllocationLib.h>

#include <Library/BaseMemoryLib.h>
#include <PrintShLib.h>

/**
  EFI interfaces
 */

#include <Protocol/EFIQcomCharger.h>
#include <Protocol/EFIPlatformInfo.h>

/**
  EFI interfaces
 */
#include <Library/BaseLib.h>

#include "QcomChargerAppEventHandler.h"
#include "QcomChargerApp.h"


/**
File Logging Dependencies
*/
#include "ULogFront.h"
#include "ULogUEFI.h"

/*===========================================================================*/
/*                  TYPEDEF AND MACRO DEFINITIONS                            */
/*===========================================================================*/
#define QCOM_CHARGER_IDLE_WAIT_DURATION_IN_MS            3000 /*3 sec in milliseconds*/
#define QCOM_CHARGER_DCIN_PENDING_WAIT_DURATION_IN_MS    500  /*500 msec*/
#define QCOM_CHARGER_TOGGLE_LED_WAIT_DURATION_IN_MS      500  /*500 msec*/
#define QCOM_CHARGER_WAIT_TO_LOG_COUNT                   QCOM_CHARGER_IDLE_WAIT_DURATION_IN_MS/QCOM_CHARGER_TOGGLE_LED_WAIT_DURATION_IN_MS  /* 6 times*/

/* Options passed into WaitForTimeout function to break out of the timer loop with a key stroke.*/
#define QCOM_CHARGER_TIMEOUT_WAIT_FOR_KEY    0x01
#define QCOM_CHARGER_POLLING_WAIT_IN_US      3000000 /*3 sec*/
#define QCOM_CHARGER_MS_TO_S                 1000

#define QCOM_CHARGER_LOGFILE_IN_EFS "ChargerLog" /* logfile name is file system */
#define QCOM_CHARGER_LOGFILE_SIZE   8630272 // 7MB

/*===========================================================================*/
/*                  FUNCTIONS PROTOTYPES                                     */
/*===========================================================================*/
EFI_STATUS QcomChargerApp_PostProcessing( VOID );
EFI_STATUS QcomChargerApp_MonitorCharging( VOID );
EFI_STATUS QcomChargerApp_Initialize( EFI_QCOM_CHARGER_ACTION_TYPE ChargingAction );
EFI_STATUS QcomChargerApp_DeInitialize( VOID );
EFI_STATUS QcomChargerApp_DisplaySignOfLifeOnVBat(EFI_QCOM_CHARGER_ACTION_INFO *ChargerActionInfo);
EFI_STATUS QcomChargerApp_ChargerDebugDateTime (void);
EFI_STATUS QcomChargerApp_LogParam(  EFI_QCOM_CHARGER_ACTION_INFO *ChargerActionInfo);
EFI_STATUS QcomChargerApp_InitFileLog();

STATIC EFI_QCOM_CHARGER_PROTOCOL    *pQcomChargerProtocol  = NULL;
STATIC EFI_QCOM_CHARGER_LOG_INFO    FileLogInfo;

/*===========================================================================*/
/*                  FUNCTIONS DEFINITIONS                                    */
/*===========================================================================*/
/**
  QcomChargerApp_Entry ()

  @brief
  Initialize Charger App
 */
EFI_STATUS QcomChargerApp_Entry
(
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
)
{
  EFI_STATUS Status = EFI_SUCCESS;
  EFI_QCOM_CHARGER_ACTION_INFO ChargerActionInfo = {0};
  EFI_QCOM_CHARGER_ACTION_TYPE   ChargingAction;
  EFI_PLATFORMINFO_PLATFORM_TYPE PlatformType;

  Status |= GetPlatformType(&PlatformType);
  if(EFI_SUCCESS != Status)
  {
    DEBUG((EFI_D_WARN, "QcomChargerApp:: %a Error getting platform type  \r\n", __FUNCTION__));
    return EFI_DEVICE_ERROR;
  }

  if((EFI_PLATFORMINFO_TYPE_CDP == PlatformType) || (EFI_PLATFORMINFO_TYPE_RUMI == PlatformType))
  {/*if platform is CDP/RUMI , don't need to run the app. */
    CHARGERAPP_FILE_UART_DEBUG(( EFI_D_WARN, "QcomChargerApp:: %a CDP/RUMI (%d) Platform detected. Exiting app. \r\n", __FUNCTION__, PlatformType));
    return EFI_SUCCESS;
  }

  SetMem(&ChargerActionInfo, sizeof(EFI_QCOM_CHARGER_ACTION_INFO), 0x00);
  SetMem(&FileLogInfo, sizeof(EFI_QCOM_CHARGER_LOG_INFO), 0x00);

  Status = gBS->LocateProtocol( &gQcomChargerProtocolGuid, NULL, (VOID **)&pQcomChargerProtocol );
  if(EFI_SUCCESS != Status || !pQcomChargerProtocol)
  {
    CHARGERAPP_FILE_UART_DEBUG(( EFI_D_ERROR, "QcomChargerApp:: %a Can not locate Charger Protocol = %r \r\n", __FUNCTION__, Status));
    return EFI_DEVICE_ERROR;
  }

  /*Get charging Action to be taken */
  Status = pQcomChargerProtocol->GetChargingAction(&ChargingAction, &ChargerActionInfo);
  /* In case of debug board to save boot time below can be ignored since debug board no Action for charger app */
  if(EFI_QCOM_CHARGER_ACTION_DEBUG_BOARD_GOOD_TO_BOOT != ChargingAction)
  {
  if (PRODMODE_DISABLED )
  {
    Status = pQcomChargerProtocol->GetLogInfo(&FileLogInfo);
    if(EFI_SUCCESS != Status )
    {
        CHARGERAPP_DEBUG(( EFI_D_WARN, "QcomChargerApp:: %a GetFileLogInfo Failed = %r \r\n", __FUNCTION__, Status));
      Status =  EFI_SUCCESS;/* should continue as not a critical error */
        FileLogInfo.gChargerLogHandle = NULL;
      }
      if(FileLogInfo.bPrintChargerAppDbgMsgToFile == TRUE)
      {
        Status = QcomChargerApp_InitFileLog();
      }
      else
      {  /* Make sure that file log handle is zero */
        FileLogInfo.gChargerLogHandle = NULL;
    }
      CHARGERAPP_DEBUG(( EFI_D_WARN, "QcomChargerApp:: %a FileHandle = %lld PrintDbgMsg = %d \r\n", __FUNCTION__, (UINT64)FileLogInfo.gChargerLogHandle, FileLogInfo.bPrintChargerAppDbgMsg));
  }

  if (!RETAIL)
  {
    Status = QcomChargerApp_ChargerDebugDateTime();
    if(EFI_SUCCESS != Status)
    {
        CHARGERAPP_DEBUG((EFI_D_WARN, "QcomChargerApp:: %a ChargerDebugDateTime Error = %r \r\n",__FUNCTION__, Status));
      /*override status */
      Status = EFI_SUCCESS;
    }
  }
  }
  /* Handle if FG battery profile needs to be loaded */
  if(EFI_QCOM_CHARGER_PLATFORM_ACTION_PROFILE_LOAD == ChargingAction)
  {
    if(ChargerActionInfo.ProfState == EFI_QCOM_CHARGER_PROFILE_LOAD)
    {
      Status |= QcomChargerApp_DisplaySignOfLifeOnVBat(&ChargerActionInfo);
    }
    /* Load Battery Profile */
    Status |= pQcomChargerProtocol->TakeAction(ChargingAction, &ChargerActionInfo);

    /*Get charging Action again to be taken to proceed further for charging if needed */
    Status = pQcomChargerProtocol->GetChargingAction(&ChargingAction, &ChargerActionInfo);
    if(EFI_SUCCESS != Status )
    {
      CHARGERAPP_DEBUG(( EFI_D_ERROR, "QcomChargerApp:: %a GetChargingAction Status = %r \r\n", __FUNCTION__, Status));
      return EFI_DEVICE_ERROR;
    }
  }

  /* Take Action First skip if debug board i.e. boot to HLOS */
  if(EFI_QCOM_CHARGER_ACTION_DEBUG_BOARD_GOOD_TO_BOOT != ChargingAction)
  {
  Status |= pQcomChargerProtocol->TakeAction(ChargingAction, &ChargerActionInfo);

  /* DO charger App Actions */
  switch(ChargingAction)
  {
    case EFI_QCOM_CHARGER_ACTION_START_CHARGING:
    case EFI_QCOM_CHARGER_ACTION_NO_CHARGE_WAIT:
    case EFI_QCOM_CHARGER_ACTION_CONTINUE:
      /*Initializes and displays the battery symbol*/
      Status |= QcomChargerApp_Initialize(ChargingAction);
      if(EFI_SUCCESS == Status)
      {
        /* if initialization success then start charging upto target SoC*/
        Status |= QcomChargerApp_MonitorCharging();
        Status |= QcomChargerApp_PostProcessing();
      }
      else
      {
        CHARGERAPP_DEBUG((EFI_D_WARN, "QcomChargerApp::%a Initialization error = %r \r\n",__FUNCTION__, Status));
        /* return Status */; /* Allowing deinit */
      }
    break;

    case EFI_QCOM_CHARGER_ACTION_GOOD_TO_BOOT:
      {
        CHARGERAPP_DEBUG((EFI_D_WARN, "QcomChargerApp:: QcomChargerApp_Start: Battery level is good to boot to HLOS. \r\n"));
      }
    break;

    default:
          CHARGERAPP_DEBUG(( EFI_D_ERROR, "QcomChargerApp:: %a ChargingAction = %d \r\n", __FUNCTION__, ChargingAction));
    break;
  }
  }
  else
  {
    CHARGERAPP_DEBUG(( EFI_D_ERROR, "QcomChargerApp:: %a Debug Board detected boot to hlos ChargingAction = %d \r\n", __FUNCTION__, ChargingAction));
  }
  /* After post processing call to exit module */
  Status |= QcomChargerApp_DeInitialize();

  CHARGERAPP_DEBUG((EFI_D_WARN, "QcomChargerApp:: %a Exiting \r\n", __FUNCTION__));

  return Status;
}

EFI_STATUS QcomChargerApp_Initialize( EFI_QCOM_CHARGER_ACTION_TYPE ChargingAction )
{
  EFI_STATUS Status = EFI_SUCCESS;

  if(!pQcomChargerProtocol)
  {
    Status = gBS->LocateProtocol( &gQcomChargerProtocolGuid, NULL, (VOID **)&pQcomChargerProtocol );
  }

  /*Start required timers */
  Status |= QcomChargerAppEvent_DisplayTimerEvent(TRUE, TRUE);
  CHARGERAPP_DEBUG((EFI_D_WARN, "QcomChargerApp:: %a Status = %r \r\n", __FUNCTION__, Status));

  return Status;
}

/*
ChgAppMonitorCharging(): This is the charging loop that will keep the chargerApp running, it will also call ChargerPlatform_Periodic function to get the error status,
get charging/gauging status, control charging and determine when to exit charging loop.
*/
EFI_STATUS QcomChargerApp_MonitorCharging( VOID )
{
  EFI_STATUS Status = EFI_SUCCESS;
  EFI_QCOM_CHARGER_ACTION_TYPE ChargingAction;
  EFI_QCOM_CHARGER_ACTION_INFO ChargerActionInfo = {0};
  BOOLEAN ExitChargingLoop = FALSE;
  UINT32  Timeoutms = QCOM_CHARGER_IDLE_WAIT_DURATION_IN_MS; /* default wait duration */
  EFI_INPUT_KEY UserKey;
  CHARGERAPP_DEBUG((EFI_D_WARN, "QcomChargerApp:: %a \r\n", __FUNCTION__));

  if(!pQcomChargerProtocol)
  {
    Status = gBS->LocateProtocol( &gQcomChargerProtocolGuid, NULL, (VOID **)&pQcomChargerProtocol );
    if(EFI_SUCCESS != Status)
      return Status;
  }

  /* Disable crash dump watchdog only when charger app starts charging */
  gBS->SetWatchdogTimer(0, 0, 0, NULL);

  /* Query charging action */
  Status = pQcomChargerProtocol->GetChargingAction(&ChargingAction, &ChargerActionInfo);
  CHARGERAPP_DEBUG((EFI_D_WARN, "QcomChargerApp:: %a ChargingAction = %d Status = %r LedConfigType = %d \r\n", __FUNCTION__, ChargingAction, Status, ChargerActionInfo.LedConfigType));
  if(EFI_SUCCESS != Status)
  {
    return Status;
  }

  CHARGERAPP_FILE_DEBUG((EFI_D_WARN, "RebootCount,TimeStamp,StateOfCharge,Voltage,ChargeCurrent,Temp \r\n"));
  DEBUG((EFI_D_WARN, "QcomChargerApp::%a TimeStamp,StateOfCharge,Voltage,ChargeCurrent,Temp \r\n",__FUNCTION__));

  /* Calculate Time to know if IDLE wait have reached to print logs and get next action */
  if(ChargerActionInfo.LedConfigType == EFI_QCOM_CHARGER_CHARGING_LED_TOGGLE)
  {
    /* wait for IDLE duration to get status and print status info */
    Timeoutms = QCOM_CHARGER_TOGGLE_LED_WAIT_DURATION_IN_MS;
  }
  else
  {
    /* Normal wait for 3s*/
    Timeoutms      = QCOM_CHARGER_IDLE_WAIT_DURATION_IN_MS;
  }

  do
  {
    /* Get charging action to be taken */
    Status = pQcomChargerProtocol->GetChargingAction(&ChargingAction, &ChargerActionInfo);
    CHARGERAPP_DEBUG((EFI_D_WARN, "QcomChargerApp:: %a ChargingAction = %d Status = %r LedConfigType = %d \r\n", __FUNCTION__, ChargingAction, Status, ChargerActionInfo.LedConfigType));
    if(EFI_SUCCESS != Status)
    {
      return Status;
    }

    switch(ChargingAction)
    {
      case EFI_QCOM_CHARGER_ACTION_GOOD_TO_BOOT:
      /*TBD Handle Charging actions with Switch statement */
      {
        Status = pQcomChargerProtocol->TakeAction(ChargingAction, &ChargerActionInfo);
        QcomChargerAppEvent_ExitLPM();
        QcomChargerAppEvent_DisplayTimerEvent(FALSE, FALSE);
        ExitChargingLoop = TRUE;
      }
      break;

      case EFI_QCOM_CHARGER_ACTION_SHUTDOWN:
        {
          /*Exit LPM and Display image before shutting down*/
          QcomChargerAppEvent_ExitLPM();
          QcomChargerAppEvent_DisplayTimerEvent(FALSE, FALSE);
        }
        Status = pQcomChargerProtocol->TakeAction(ChargingAction, &ChargerActionInfo);
        /* Control does not return here as in case to shutdown action */
        ExitChargingLoop = TRUE;
      break;

      case EFI_QCOM_CHARGER_ACTION_NO_CHARGE_WAIT:
        {
          /* Take Action to make sure charging is disabled */
          Status = pQcomChargerProtocol->TakeAction(ChargingAction, &ChargerActionInfo);
          CHARGERAPP_FILE_UART_DEBUG((EFI_D_WARN, "QcomChargerApp:: %a No Charge Wait ChrgAct = %d wait %d ms \r\n", __FUNCTION__, ChargingAction, QCOM_CHARGER_IDLE_WAIT_DURATION_IN_MS));
          WaitForTimeout (QCOM_CHARGER_IDLE_WAIT_DURATION_IN_MS, QCOM_CHARGER_TIMEOUT_WAIT_FOR_KEY, &UserKey);
          /*Check if WaitForTimeout returned due to key press */
          if((UserKey.UnicodeChar != 0x00) || (UserKey.ScanCode != 0x00))
          {
            DEBUG((EFI_D_WARN, "QcomChargerApp:: %a Keypress detected \r\n", __FUNCTION__));
            QcomChargerAppEvent_KeyPressHandler(QCOMCHARGERAPP_EVENT_ANIMATION__LOW_BATTERY_NO_ANIM);
          }
        }
      break;
      case EFI_QCOM_CHARGER_ACTION_CRITICAL:
        {
          /*Exit LPM and Display image before shutting down*/
          QcomChargerAppEvent_ExitLPM();
          Status = pQcomChargerProtocol->TakeAction(ChargingAction, &ChargerActionInfo);
          /* Control does not return here as in case to shutdown action */
          ExitChargingLoop = TRUE;
          }
      break;
      case EFI_QCOM_CHARGER_ACTION_SHUTDOWN_USB_DC_PON_DISABLED:
          {
            /*Exit LPM and Display image before shutting down*/
            QcomChargerAppEvent_ExitLPM();
            CHARGERAPP_FILE_UART_DEBUG((EFI_D_WARN, "QcomChargerApp:: %a Shutdown with PON disabled \r\n", __FUNCTION__));
            Status = pQcomChargerProtocol->TakeAction(ChargingAction, &ChargerActionInfo);
            /* Control does not return here as in case to shutdown action */
            ExitChargingLoop = TRUE;
        }
      break;
      case EFI_QCOM_CHARGER_ACTION_CONTINUE:
      default:
        /* Take Action */
        Status |= pQcomChargerProtocol->TakeAction(ChargingAction, &ChargerActionInfo);
        QcomChargerApp_LogParam(&ChargerActionInfo);
        CHARGERAPP_FILE_UART_DEBUG((EFI_D_WARN, "QcomChargerApp:: %a Waiting for %d ms \r\n", __FUNCTION__, Timeoutms));
        /* Now wait for set Timeout */
        WaitForTimeout (Timeoutms, QCOM_CHARGER_TIMEOUT_WAIT_FOR_KEY, &UserKey);
        /*Check if WaitForTimeout returned due to key press */
        if((UserKey.UnicodeChar != 0x00) || (UserKey.ScanCode != 0x00))
        {
          DEBUG((EFI_D_WARN, "QcomChargerApp:: %a Keypress detected \r\n", __FUNCTION__));
          QcomChargerAppEvent_KeyPressHandler(QCOMCHARGERAPP_EVENT_ANIMATION__CHARGING_ANIM);
        }
      break;
    }
  }while (FALSE == ExitChargingLoop);

  /* Start 10min watchdog timer */
  gBS->SetWatchdogTimer(10 * 60, 0, 0, NULL);

  CHARGERAPP_DEBUG((EFI_D_WARN, "QcomChargerApp:: %a Exiting ChargingAction = %d \r\n", __FUNCTION__, ChargingAction));

  return Status;
}

/*After Charging is completed, handle cases for threshold charging and full battery charging*/
EFI_STATUS QcomChargerApp_PostProcessing( VOID )
{
  EFI_STATUS Status = EFI_SUCCESS;

  if(!pQcomChargerProtocol)
  {
    Status = gBS->LocateProtocol( &gQcomChargerProtocolGuid, NULL, (VOID **)&pQcomChargerProtocol );
  }

  Status = pQcomChargerProtocol->DisplayImage(EFI_QCOM_CHARGER_DISP_IMAGE_ABOVE_THRESHOLD, TRUE);

  QcomChargerAppEvent_ExitLPM();

  /*close timer events*/
  QcomChargerAppEvent_DisplayTimerEvent(FALSE, FALSE);

  //Ensuring charging is enabled when booting from UEFI to HLOS
  Status |= pQcomChargerProtocol->EnableCharging(TRUE);

  return Status;
}

EFI_STATUS QcomChargerApp_DeInitialize( VOID)
{
  EFI_STATUS Status = EFI_SUCCESS;

  if(pQcomChargerProtocol)
  {
    Status = pQcomChargerProtocol->ChargerDeInit(EFI_QCOM_CHARGER_ACTION_EXIT);
  }

  /* CHARGERAPP_DEBUG((EFI_D_WARN, "QcomChargerApp:: %a SUCCESS \r\n", __FUNCTION__));*/
  return Status;
}


EFI_STATUS QcomChargerApp_DisplaySignOfLifeOnVBat(EFI_QCOM_CHARGER_ACTION_INFO *ChargerActionInfo)
{
  EFI_STATUS Status   = EFI_SUCCESS;

  if(!ChargerActionInfo)
    return EFI_INVALID_PARAMETER;

  CHARGERAPP_DEBUG((EFI_D_WARN, "QcomChargerApp::%a CurrSoc = %d, BatteryVolt = %d mV, VbatThresholdForDisp = %d mV, Status = %r \r\n",__FUNCTION__,
                ChargerActionInfo->BatteryStatusInfo.StateOfCharge , ChargerActionInfo->BatteryStatusInfo.BatteryVoltage, ChargerActionInfo->DispSignOfLifeMaxThresholdMv, Status));/*DEBUG */
  if(ChargerActionInfo->BatteryStatusInfo.BatteryVoltage <= (ChargerActionInfo->DispSignOfLifeMaxThresholdMv ))
  {
    if(TRUE == ChargerActionInfo->bChargerSrcPresent)
    {
      Status |= QcomChargerAppEvent_DispBattSymbol(EFI_QCOM_CHARGER_DISP_IMAGE_LOWBATTERYCHARGING);
    }
    else
    {
      Status |= QcomChargerAppEvent_DispBattSymbol(EFI_QCOM_CHARGER_DISP_IMAGE_LOWBATTERY);
    }
  }
  else
  {
    /*DEBUG */
    CHARGERAPP_DEBUG((EFI_D_WARN, "QcomChargerApp:: %a Skipping Init Display On CurrSoc = %d, BatteryVolt = %d mV, ", __FUNCTION__, 
                      ChargerActionInfo->BatteryStatusInfo.StateOfCharge , ChargerActionInfo->BatteryStatusInfo.BatteryVoltage));
	CHARGERAPP_DEBUG((EFI_D_WARN, "DispSignOfLifeMaxThresholdMv = %d mV Status = %r \r\n",
                      ChargerActionInfo->DispSignOfLifeMaxThresholdMv, Status));
  }

  return Status;

}


/**
QcomChargerApp_PrintDebugMsg()

@brief
Returns QcomChargerApp_PrintDebugMsg Flag Status
*/
inline BOOLEAN
EFIAPI
QcomChargerApp_PrintDebugMsg(void)
{
  return ((BOOLEAN)FileLogInfo.bPrintChargerAppDbgMsg);
}

/**
QcomChargerApp_PrintDebugMsgToFile()

@brief
Returns QcomChargerApp_PrintDebugMsgToFile Flag Status
*/
inline BOOLEAN
EFIAPI
QcomChargerApp_PrintDebugMsgToFile(void)
{
  if (NULL != FileLogInfo.gChargerLogHandle) return (TRUE);
  return FALSE;
}


UINT64 QcomChargerApp_TimeGet64(void)
{
  UINT64 Result = 0 ;
  Result = GetPerformanceCounter();
  return(Result);
}


/**
ULogPrint ()

@brief Helper API to print multiple arguments
Returns
*/
inline void EFIAPI
ULogPrint(
  IN  UINTN        ErrorLevel,
  IN  CONST CHAR8  *Format,
  ...
  )
{
  va_list vlist;
  UINT32  dataCount = 0;
  UINTN   i         = 0;
  BOOLEAN  boEsc = FALSE;
  STATIC EFI_STATUS lastLogResult = EFI_SUCCESS;
  EFI_STATUS CurrentLogResult     = EFI_SUCCESS;
  CHAR8 CurrentFormat[512];
  UINTN CurrentFormatIndex = 0;
  UINT32 size = sizeof(CurrentFormat);
  BOOLEAN appendFlag = FALSE;
  CHAR8 *FnName = NULL;

  SetMem(CurrentFormat, sizeof(CurrentFormat), 0x00);

  /* If volume corrupted do not attempt to log */
  if (EFI_VOLUME_CORRUPTED == lastLogResult)
    return;

  for (i = 0, dataCount = 0; (NULL != (Format + i)) && (Format[i] != '\0'); i++, CurrentFormatIndex++)
  {
   CurrentFormat[CurrentFormatIndex] = Format[i];
   if (Format[i] == '%' && !boEsc)
   {
     if(Format[i + 1] == 'a')
     {
       appendFlag = TRUE;
       VA_START(vlist, Format);
       FnName = (CHAR8* ) va_arg(vlist, CHAR8*);
       AsciiVSPrint((CurrentFormat + CurrentFormatIndex), size, FnName, vlist);
       CurrentFormatIndex = CurrentFormatIndex + AsciiStrLen(FnName);
       CurrentFormat[CurrentFormatIndex] = ' ';
       i += 2;
     }else if (Format[i + 1] == 'r')
     {
       CurrentFormat[++CurrentFormatIndex] = 'd';
       i++;
       dataCount++;
     }
     else
     {
       dataCount++;
     }
   }
   else if (Format[i] == '\\' && !boEsc)
   {
     boEsc = TRUE;
   }
   else if (boEsc)
  {
     boEsc = FALSE;
   }
  }
  /* if(appendFlag)
  {
    va_end(vlist);
  } */
  /* Append end of the string */
  CurrentFormat[CurrentFormatIndex] = '\0';
  if(appendFlag == FALSE)
  {
    VA_START(vlist, Format);
  }

  //CHARGERAPP_UART_DEBUG((EFI_D_WARN, "ChargerApp:: %a dataCount = %d \r\n",__FUNCTION__, dataCount));

  //CHARGERAPP_UART_DEBUG((EFI_D_WARN, "ChargerApp:: %a formatstring = %a \r\n",__FUNCTION__, Format));
  //CHARGERAPP_UART_DEBUG((EFI_D_WARN, "ChargerApp:: %a Current Fn Name = %a size = %d \r\n",__FUNCTION__, CurrentFormat, size));
  if(appendFlag)
  {
    CurrentLogResult = (EFI_STATUS ) ULogFront_RealTimeVprintf(FileLogInfo.gChargerLogHandle,  dataCount, CurrentFormat, vlist);
  }
  else
  {
  CurrentLogResult = (EFI_STATUS ) ULogFront_RealTimeVprintf(FileLogInfo.gChargerLogHandle,  dataCount, Format, vlist);
  }
  if(CurrentLogResult == EFI_VOLUME_CORRUPTED)
  {
    CHARGERAPP_UART_DEBUG((EFI_D_WARN, "ChargerApp:: %a File Log Print Volume Error = %r \r\n",__FUNCTION__, CurrentLogResult));
    lastLogResult = CurrentLogResult;
  }else if (CurrentLogResult != EFI_SUCCESS)
  {
    CHARGERAPP_UART_DEBUG((EFI_D_WARN, "ChargerApp:: %a File Log Print Error = %r \r\n",__FUNCTION__, CurrentLogResult));
  }else { /* SUCCESS use case */}

   VA_END(vlist);
  }


/**
  QcomChargerApp_ChargerDebugDateTime ()

  @brief
  Debug Date & time
 */
EFI_STATUS QcomChargerApp_ChargerDebugDateTime (void)
{
  EFI_STATUS Status = EFI_SUCCESS;
  EFI_TIME   Time = {0};
  UINTN      CpuFrequency = 0;
  UINT64     Seconds = 0;
  UINT64     TotalTicks = 0;

  /* Debug Print CPU Frequncey */
  CpuFrequency = GetPerformanceCounterProperties(NULL, NULL);
  TotalTicks   = QcomChargerApp_TimeGet64();
  Seconds      = QcomChargerApp_CalculateTime();
  CHARGERAPP_DEBUG((EFI_D_WARN, "QcomChargerApp:: %a CpuFrequency = %lld Hz Seconds = %lld TotalTicks = %lld \r\n",__FUNCTION__, CpuFrequency, Seconds, TotalTicks));

  /* Print Date time once */
  Status = gRT->GetTime(&Time, NULL);
  if (Status == EFI_SUCCESS)
  {
    CHARGERAPP_DEBUG((EFI_D_WARN, "QcomChargerApp:: Date(year/month/Day):Time(Hour/Minute/sec/nano/timezone/daylight) "));
	CHARGERAPP_DEBUG((EFI_D_WARN, "-> %d/%d/%d:%d/%d/%d/%d/%d/%d \r\n",
                Time.Year, Time.Month, Time.Day, Time.Hour, Time.Minute, Time.Second, Time.Nanosecond, Time.TimeZone, Time.Daylight));
  }
  else
  {
    CHARGERAPP_DEBUG((EFI_D_WARN, "QcomChargerApp:: %a Error in Getting systems Date and Time: 0x%08X\r\n", Status));
    Status = EFI_SUCCESS;
  }

  return Status;
}



UINT64 QcomChargerApp_CalculateTime ()
{
  UINTN  CpuFrequency = 0;
  UINT64 TotalTicks = 0;
  UINT64 Seconds =0;

  /* Debug Print CPU Frequncey */
  TotalTicks   = QcomChargerApp_TimeGet64();
  /* Debug Print CPU Frequncey */
  CpuFrequency = GetPerformanceCounterProperties(NULL, NULL);
  Seconds = MultU64x32(TotalTicks, 1000000);
  Seconds = DivU64x32(Seconds, CpuFrequency);
  Seconds /= 1000000;

  return Seconds;
}


EFI_STATUS QcomChargerApp_LogParam(EFI_QCOM_CHARGER_ACTION_INFO *ChargerActionInfo)
{
  CHARGERAPP_DEBUG(( EFI_D_WARN, "QcomChargerApp:: %a StateOfCharge = %d, VBat = %d mV Current = %d mA Temperature = %d C \r\n",
                           __FUNCTION__, ChargerActionInfo->BatteryStatusInfo.StateOfCharge, ChargerActionInfo->BatteryStatusInfo.BatteryVoltage,
                           ChargerActionInfo->BatteryStatusInfo.ChargeCurrent, ChargerActionInfo->BatteryStatusInfo.BatteryTemperature));

  /* DEBUG when charging is progress and charger logs are disabled */
  CHARGERAPP_FILE_UART_DEBUG((EFI_D_WARN, "QcomChargerApp:: Battery Status %d,%d,%d,%d \r\n", ChargerActionInfo->BatteryStatusInfo.StateOfCharge,
                              ChargerActionInfo->BatteryStatusInfo.BatteryVoltage, ChargerActionInfo->BatteryStatusInfo.ChargeCurrent,
                              ChargerActionInfo->BatteryStatusInfo.BatteryTemperature));

  return EFI_SUCCESS;
}


/**
QcomChargerApp_InitFileLog( )

@brief  Returns File long handle if alreayd initilized
Returns Status
*/
EFI_STATUS QcomChargerApp_InitFileLog(VOID )
{
  ULogResult       result     = 0;
  ULOG_CONFIG_TYPE configType = {0};

  if(NULL != FileLogInfo.gChargerLogHandle)
  {
    result = ULogFile_Open(&(FileLogInfo.gChargerLogHandle), QCOM_CHARGER_LOGFILE_IN_EFS, QCOM_CHARGER_LOGFILE_SIZE);
    if (0 == result)
    {
      /* Set ULog configuration */
      ULogFile_GetConfig(&(FileLogInfo.gChargerLogHandle), &configType);
      configType.separator = ',';
      configType.PrintTimestamp = TRUE;
      configType.TrimNewline = TRUE;
      ULogFile_SetConfig(&FileLogInfo.gChargerLogHandle, &configType);
      ULOG_RT_PRINTF_1(FileLogInfo.gChargerLogHandle, "QcomChargerApp::InitFileLog SUCCESS gULogHandle = %lld", FileLogInfo.gChargerLogHandle);
      CHARGERAPP_UART_DEBUG((EFI_D_WARN, "QcomChargerApp:: %a InitFileLog SUCCESS \r\n",  __FUNCTION__));
    }
    else
    {
      CHARGERAPP_UART_DEBUG((EFI_D_WARN, "QcomChargerApp:: %a InitFileLog FAILED \r\n",  __FUNCTION__));
      FileLogInfo.gChargerLogHandle = NULL;
    }
  }

   return EFI_SUCCESS;
}

