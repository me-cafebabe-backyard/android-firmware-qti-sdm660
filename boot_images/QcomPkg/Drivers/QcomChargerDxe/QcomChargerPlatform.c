/** @file ChargerPlatform.c

  Implements Qualcomm's battery voltage based threshold Charging solution

  Copyright (c) 2016-2017,  Qualcomm Technologies Inc. All rights reserved.

**/

/*=============================================================================

                              EDIT HISTORY

when        who     what, where, why
--------    ----    -----------------------------------------------------------
01/17/17    va      Adding Rconn configuration for considering compensation
01/10/17    cs      add config to enable/disable INOV
11/02/16    sv      Updated to support section based config for different platforms.
09/13/16    sm      removed unused parameters from ChargerPlatform_ReadCfgParams()
09/06/16    cs      wipower changes to remove 3.5 sec, not suspend DCIn
08/24/16    sm      Added changes for supporting different config parameters settings for
                      different platforms, MTP, QRD, etc.
08/12/16    sm      Merged Vbatt and SOC based Platform files.
08/05/16    va      Adding Charger led indication support
07/26/16    va      Restarting FG Changes on warm boot
07/15/16    cs      Adding Wipower support
06/28/16    va      Changes to share charger info to smem
06/24/16    sm      Added check for charging enabled in GetChargingAction()
06/23/16    sm      Added EnableHvdcp in ChargerPlatform_ReadCfgParams()
06/23/16    va      Adding support for Charger Fg Peripheral dumps
06/14/16    va      Adding Thermal Support
06/09/16    sm      Added SupportHostMode in ChargerPlatform_ReadCfgParams()
05/31/16    va      Adding Battery profile load feature
05/24/16    sm      Added changes to handle No_Charger_wait case in GetChargingAction()
05/10/16    sm      Added ChargerPlatform_GetConfigData()
04/26/16    va      Adding parameters for Aux Coffes, SkinHot and Charger Hot settings
04/21/16    sm      Added API call for Watchdog
                      Added EnableChargerWdog in ChargerPlatform_ReadCfgParams
04/12/16    sm      Edited variables in ChargerPlatform_ReadCfgParams()
04/07/16    sm      Added ChargerPlatform_GetUefiVariableValues()
03/31/16    sm      Completing API definitions
03/28/16    va      Add logging CHARGER_DEBUG
03/21/16    va      Remove dummy configs and add battery missing config
01/27/16    sm      Initial revision
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
#include <Library/FuseControlLib.h>
#include <Library/QcomBaseLib.h>

#include <Protocol/EFIVariableServices.h>
#include <Library/MemoryAllocationLib.h>

#include <Library/BaseMemoryLib.h>
#include <Library/BaseLib.h>

/**
  EFI interfaces
 */
#include <Protocol/GraphicsOutput.h>
#include <Protocol/EFIPlatformInfo.h>

#include "QcomChargerPlatform.h"
#include "QcomChargerPlatform_File.h"

#include <api/systemdrivers/pmic/pm_chg.h>

/**
Smem Interface 
*/
#include "smem.h"

/*===========================================================================*/
/*                  TYPEDEF AND MACRO DEFINITIONS                            */
/*===========================================================================*/
#define QCOM_CHARGER_IDLE_WAIT_DURATION            3000 /*3 sec in milliseconds*/
#define QCOM_CHARGER_MS_TO_S                       1000

/* UI would be displayed if VBAT read is less than 3700mV is 7% Soc. 
   Having a margin of extra 50mV to consider on the top of error margin */
#define QCOM_CHARGER_VBAT_ERROR_MARGIN 0 /*in Mv as of now keeping default as 0 error margin */
#define QCOM_CHARGER_LOW_THERSHOLD_VBAT 3700 /*in Mv*/
#define QCOM_CHARGER_INVALID_VALUE_MARKER  -1


STATIC UINT32 gThresholdVbatt = 0;
STATIC UINT32 gThresholdSoc   = 0;

QCOM_CHARGER_PLATFORM_CFGDATA_TYPE gChargerPlatformCfgData; 

extern BOOLEAN ExitChargingLoop;
BOOLEAN gChargingInitialized = FALSE;

pm_chg_info_type gChargerSharedInfo;

STATIC EFI_PLATFORMINFO_PLATFORM_TYPE PlatformType;

/*===========================================================================*/
/*                  FUNCTIONS PROTOTYPES                                     */
/*===========================================================================*/

EFI_STATUS ChargerPlatform_GetUefiVariableValues( void );
EFI_STATUS ChargerPlatform_SaveChargeInfoToSmem(pm_chg_info_type *ChargerActionInfo);
EFI_STATUS ChargerPlatform_ProfileLoadingInit(QCOM_CHARGER_PLATFORM_ACTION_TYPE *pActionType,
                                              QCOM_CHARGER_PLATFORM_ACTION_INFO *pChargerActionInfo);
EFI_STATUS ChargerPlatform_CheckIfOkToBoot(QCOM_CHARGER_PLATFORM_ACTION_TYPE *pActionType,
                                           QCOM_CHARGER_PLATFORM_ACTION_INFO ChargerActionInfo,
                                           QCOM_CHARGER_BATT_STATUS_INFO CurrentBatteryStatus);

/*===========================================================================*/
/*                  FUNCTIONS DEFINITIONS                                    */
/*===========================================================================*/
/*
ChargerPlatform_Init(): This function locates and initializes ADC Protocal, Charger Protocal and other Protocols that are 
needed for that specific platform. It also loads the cfg file and initialize charger and FG accordingly. 
*/
EFI_STATUS ChargerPlatform_Init( VOID )
{
  EFI_STATUS Status = EFI_SUCCESS;

  SetMem(&gChargerPlatformCfgData, sizeof(QCOM_CHARGER_PLATFORM_CFGDATA_TYPE), 0x00);
  SetMem(&gChargerSharedInfo, sizeof(pm_chg_info_type), 0xFF);

  Status |= GetPlatformType(&PlatformType);
  if(EFI_SUCCESS != Status)
  {
    DEBUG((EFI_D_WARN, "QcomChargerPlatform:: %a Error getting platform type  \r\n", __FUNCTION__));
    return EFI_DEVICE_ERROR;
  }

  /* Load CFG file */
  Status |= ChargerPlatformFile_ReadDefaultCfgData();
  if(EFI_SUCCESS == Status)
  {
    CHARGER_DEBUG(( EFI_D_WARN, "QcomChargerDxe:: %a Successfully read config file\n\r", __FUNCTION__));
  }

  /* Read debug var from pmic bds menu */
  Status  |= ChargerPlatform_GetUefiVariableValues();

  /* Init Charger lib configs */
  Status |= ChargerLibCommon_InitConfiguration((chargerlib_cfgdata_type*)&gChargerPlatformCfgData);

  if ((EFI_SUCCESS == Status) && (TRUE == gChargerPlatformCfgData.DbgCfgData.PrintChargerAppDbgMsgToFile))
  {
    Status = ChargerPlatformFile_FileLogInit(gChargerPlatformCfgData);
  }

  CHARGER_DEBUG(( EFI_D_WARN, "QcomChargerDxe:: %a chargerlib_cfgdata_type = %d QCOM_CHARGER_PLATFORM_CFGDATA_TYPE = %d \r\n", __FUNCTION__, sizeof(chargerlib_cfgdata_type), sizeof(QCOM_CHARGER_PLATFORM_CFGDATA_TYPE) ));

  /* Init Charger lib */
  Status |= ChargerLibCommon_Init();
  if(EFI_SUCCESS != Status)
  {
    CHARGER_DEBUG(( EFI_D_ERROR, "QcomChargerDxe:: %a Error when initializing ChargerLibCommon = %r \r\n", __FUNCTION__, Status));
    return Status;
  }
  else
  {
    CHARGER_DEBUG(( EFI_D_WARN, "QcomChargerDxe:: %a Successfully initialized ChargerLibCommon %r \r\n", __FUNCTION__, Status));
  }

  gThresholdVbatt = gChargerPlatformCfgData.BootToHLOSThresholdInMv;
  gThresholdSoc   = gChargerPlatformCfgData.BootToHLOSThresholdInSOC;

  /* Enable HW JEITA*/
  Status |= ChargerLib_EnableHWJeita(TRUE);

  /*Disable Charger wdog before applying config based wdog setting*/
  Status = ChargerLib_EnableWdog(FALSE);

  if((QCOM_CHG_WDOG_DISABLE_ON_EXIT == gChargerPlatformCfgData.EnableChargerWdog)|| (QCOM_CHG_WDOG_LEAVE_ENABLED_ON_EXIT == gChargerPlatformCfgData.EnableChargerWdog))
  {
    /* Enable Charger Watchdog*/
    Status = ChargerLib_EnableWdog(TRUE);
    if(EFI_SUCCESS == Status)
    {
      CHARGER_DEBUG(( EFI_D_ERROR, "QcomChargerDxe:: %a Enabled WDOG.\r\n", __FUNCTION__));
    }
    else if (EFI_UNSUPPORTED == Status)
    {
      /*Do not need to return status as unsupported. Debug statement will be printed from SCG protocol API*/
      Status = EFI_SUCCESS;
    }
  }

  return Status;
}

EFI_STATUS ChargerPlatform_GetChargingAction(QCOM_CHARGER_PLATFORM_ACTION_TYPE *pActionType, QCOM_CHARGER_PLATFORM_ACTION_INFO *pChargerActionInfo)
{
  EFI_STATUS Status                = EFI_SUCCESS;
  BOOLEAN    bChargerReinserted    = FALSE;
  QCOM_CHARGER_BATT_STATUS_INFO             CurrentBatteryStatus = {0};
  CHARGERLIB_CHARGING_ERROR_TYPES           ErrorType  = CHARGERLIB_CHARGING_ERROR_NONE;
  STATIC QCOM_CHARGER_PLATFORM_ACTION_TYPE  PrevChargerAction = QCOM_CHARGER_PLATFORM_ACTION_INVALID;
  BOOLEAN                                   ChargingEnabled    = FALSE;

  if (!pChargerActionInfo || !pActionType)
    return EFI_INVALID_PARAMETER;

  /* Get Error like debug board or battery not detected first */
  Status |= ChargerLib_GetErrors(&ErrorType);
  if(EFI_SUCCESS != Status)
  {
    CHARGER_DEBUG(( EFI_D_ERROR, "QcomChargerDxe:: %a Error Getting Battery Error = %r.\r\n", __FUNCTION__, Status));
    *pActionType = QCOM_CHARGER_PLATFORM_ACTION_SHUTDOWN ;
    PrevChargerAction = *pActionType;
    return Status;
  }

  if((CHARGERLIB_CHARGING_ERROR_BATTERY_NOT_DETECTED == ErrorType ) || (CHARGERLIB_CHARGING_ERROR_DEBUG_BOARD == ErrorType ) ||
    (CHARGERLIB_DEVICE_ERROR == ErrorType ) || (CHARGERLIB_CHARGING_ERROR_UNKNOWN_BATTERY == ErrorType ))
  {
    Status = ChargerLib_GetErrorAction(ErrorType, (((CHARGERLIB_ERROR_ACTION_TYPE*)pActionType)));
    PrevChargerAction = *pActionType;

    /*If there is a battery error, return */
    return Status;
  }

  /* Assign Led config to toggle led */
  pChargerActionInfo->LedConfigType = (QCOM_CHARGER_PLATFORM_CHARGING_LED_CONFIG_TYPE)gChargerPlatformCfgData.ChargerLedConfig;

  if(PrevChargerAction == QCOM_CHARGER_PLATFORM_ACTION_INVALID )
  {
    /* Load profile if SocBasedboot is true or profile load is enabled */
    if((gChargerPlatformCfgData.SocBasedBoot == TRUE ) || (gChargerPlatformCfgData.FgCfgData.LoadBatteryProfile == TRUE ))
    {
      Status = ChargerPlatform_ProfileLoadingInit(pActionType, pChargerActionInfo);
      PrevChargerAction = *pActionType;

      /* Return since action is decided for this Invalid charging action case */
      return Status;
    }
    else
    {
      CHARGER_DEBUG(( EFI_D_WARN, "QcomChargerDxe:: %a Battery Profile Loading Not Required \r\n", __FUNCTION__));
    }
  }

  Status |= ChargerLib_GetErrors(&ErrorType);
  if(EFI_SUCCESS != Status)
  {
    CHARGER_DEBUG(( EFI_D_ERROR, "QcomChargerDxe:: %a Error Getting Battery Error = %r.\r\n", __FUNCTION__, Status));
    *pActionType = QCOM_CHARGER_PLATFORM_ACTION_SHUTDOWN ;
    PrevChargerAction = *pActionType;
    return Status;
  }

  if(CHARGERLIB_CHARGING_ERROR_NONE != ErrorType)
  {
    Status = ChargerLib_GetErrorAction(ErrorType, (((CHARGERLIB_ERROR_ACTION_TYPE*)pActionType)));
    PrevChargerAction = *pActionType;

    /*If there is a battery error, return */
    return Status;
  }

  Status |= ChargerLib_GetBatteryStatus((chargerlib_batt_status_info*)&CurrentBatteryStatus);
  if(EFI_SUCCESS != Status )
  {
    CHARGER_DEBUG(( EFI_D_WARN, "QcomChargerDxe:: %a Error Getting Battery Status = %r.\r\n", __FUNCTION__, Status));
    *pActionType = QCOM_CHARGER_PLATFORM_ACTION_STOP_CHARGING;
    PrevChargerAction = *pActionType;

    /*If there is an error, return since action is decided */
    return Status;
  }

  Status = ChargerLib_GetChargingPath(&pChargerActionInfo->ChargerAttached);
  if (EFI_SUCCESS != Status)
  {
    CHARGER_DEBUG((EFI_D_WARN, "QcomChargerDxe:: %a Error Getting Power Path = %r.\r\n", __FUNCTION__, Status));
    *pActionType = QCOM_CHARGER_PLATFORM_ACTION_STOP_CHARGING;
    PrevChargerAction = *pActionType;
    return Status;
  }

  /* Assign status info for caller */
  pChargerActionInfo->BattStsInfo = CurrentBatteryStatus;

  if ((QCOM_CHARGER_PLATFORM_CHARGER_ATTACHED_USB  == pChargerActionInfo->ChargerAttached) &&
     ((QCOM_CHARGER_PLATFORM_ACTION_INVALID        == PrevChargerAction ) || 
      (QCOM_CHARGER_PLATFORM_ACTION_PROFILE_LOAD   == PrevChargerAction ) || 
      (QCOM_CHARGER_PLATFORM_ACTION_NO_CHARGE_WAIT == PrevChargerAction )))
  {
    *pActionType = QCOM_CHARGER_PLATFORM_ACTION_START_CHARGING; 
  }
  else
  {
    Status = ChargerLib_GetChargingStatus(&ChargingEnabled);
    if(EFI_SUCCESS != Status)
    {
      CHARGER_DEBUG((EFI_D_WARN, "ChargerLib::%a Error Getting Charging Status = %r \r\n", __FUNCTION__, Status));
      return Status;
    }

    if(FALSE == ChargingEnabled)
    {
      /*Charger register dump in case need to determine why charging is disabled*/
      Status |= ChargerLib_DumpChargerPeripheral();
      if (gChargerPlatformCfgData.WiPowerCfgData.WipowerEnabled && 
         (QCOM_CHARGER_PLATFORM_CHARGER_ATTACHED_DCIN == pChargerActionInfo->ChargerAttached))
      {
        *pActionType = QCOM_CHARGER_PLATFORM_ACTION_NO_CHARGE_WAIT;
        }
      else
      {
        *pActionType = QCOM_CHARGER_PLATFORM_ACTION_START_CHARGING;
      }
    }
    else
    {
        /* Charging already started, go to continue. */
        *pActionType = QCOM_CHARGER_PLATFORM_ACTION_CONTINUE;
        /* Assign Led config to toggle led */
        /* pChargerActionInfo->LedConfigType = (QCOM_CHARGER_PLATFORM_CHARGING_LED_CONFIG_TYPE)gChargerPlatformCfgData.ChargerLedConfig;*/
      }

    if (QCOM_CHARGER_PLATFORM_CHARGER_ATTACHED_USB == pChargerActionInfo->ChargerAttached)
    {
      /* Check if charger was swapped/re-inserted */
      Status = ChargerLib_WasChargerReinserted(&bChargerReinserted);
      if(EFI_SUCCESS != Status )
      {
        CHARGER_DEBUG((EFI_D_WARN, "ChargerLib::%a Error = %d Error Checking Charger Re-insertion. \r\n", __FUNCTION__, Status));
        return Status;
      }

      if(bChargerReinserted)
      {
        //Status = ChargerLib_CheckAPSDResults();
        Status = ChargerLib_ReRunAicl();
      }
    }
  }

  Status |= ChargerPlatform_CheckIfOkToBoot(pActionType, *pChargerActionInfo, CurrentBatteryStatus);

  CHARGER_DEBUG(( EFI_D_WARN, "QcomChargerDxe:: %a Action Returned = %d \r\n", __FUNCTION__,*pActionType));

  PrevChargerAction = *pActionType;

  return Status;
}

EFI_STATUS ChargerPlatform_LoadProfile(CONST QCOM_CHARGER_PLATFORM_ACTION_INFO *pChargerActionInfo)
{
  QCOM_CHARGER_PLATFORM_BATT_PROFILE_DATA BattProfileInfo = {0};
  EFI_STATUS Status = EFI_SUCCESS;

  if(!pChargerActionInfo)
    return EFI_INVALID_PARAMETER;

  if (gChargerPlatformCfgData.FgCfgData.LoadBatteryProfile == TRUE)
  {
    CHARGER_DEBUG(( EFI_D_WARN, "QcomChargerDxe:: %a Battery Profile Loading is enabled \r\n", __FUNCTION__ ));
    switch(pChargerActionInfo->ProfState.eProfileState)
    {
      case QCOM_CHARGER_PLATFORM_PROFILE_LOAD:
        Status |= ChargerPlatformFile_ReadBatteryProfile(&BattProfileInfo);
        if(Status == EFI_SUCCESS)
        {
          CHARGER_DEBUG(( EFI_D_WARN, "QcomChargerDxe:: %a Battery Profile File Read Success DataSize = %d \r\n", __FUNCTION__, BattProfileInfo.DataSize));
          Status |= ChargerLib_LoadProfile((chargerlib_batt_profile_data *)&BattProfileInfo);
        }
        else
        {
          CHARGER_DEBUG(( EFI_D_WARN, "QcomChargerDxe:: %a Battery Profile File read Failed = %r \r\n", __FUNCTION__, Status));
        }
        /* Free allocated file buffer */
        if(NULL != BattProfileInfo.pFileBuffer)
          gBS->FreePool(BattProfileInfo.pFileBuffer);
      break;
      case QCOM_CHARGER_PLATFORM_PROFILE_RESTART:
        /* Restart FG Condition */
        Status |= ChargerPlatformFile_ReadBatteryProfile(&BattProfileInfo);
        if(Status == EFI_SUCCESS)
        {
          CHARGER_DEBUG(( EFI_D_WARN, "QcomChargerDxe:: %a Battery Profile File Read Success DataSize = %d \r\n", __FUNCTION__, BattProfileInfo.DataSize));
          Status |= ChargerLib_LoadProfile((chargerlib_batt_profile_data *)&BattProfileInfo);
        }
        else
        {
          CHARGER_DEBUG(( EFI_D_WARN, "QcomChargerDxe:: %a Battery Profile Restart = %r \r\n", __FUNCTION__, Status));
        }
        /* Free allocated file buffer */
        if(NULL != BattProfileInfo.pFileBuffer)
          gBS->FreePool(BattProfileInfo.pFileBuffer);
      break;

      default:
      break;
    }
  }

  return Status;
}


EFI_STATUS ChargerPlatform_TakeAction(QCOM_CHARGER_PLATFORM_ACTION_TYPE ChargingAction, CONST QCOM_CHARGER_PLATFORM_ACTION_INFO *pChargerActionInfo)
{
  QCOM_CHARGER_BATT_STATUS_INFO CurrentBatteryStatus = {0};
  STATIC BOOLEAN bToggleLed = TRUE;

  if(!pChargerActionInfo)
  {
    CHARGER_DEBUG(( EFI_D_WARN, "QcomChargerDxe:: %a Invalid parameter \r\n", __FUNCTION__));
    return EFI_INVALID_PARAMETER;
  }

  CurrentBatteryStatus = (QCOM_CHARGER_BATT_STATUS_INFO)pChargerActionInfo->BattStsInfo;

  switch (ChargingAction)
  {
    case QCOM_CHARGER_PLATFORM_ACTION_CRITICAL:
         //print out and flush critical error messages 
         //Perform AFP
         CHARGER_FILE_UART_DEBUG((EFI_D_WARN, "QcomChargerDxe::%a Critical Error occurred. Shutting down \r\n", __FUNCTION__));
         ChargerLib_ForceSysShutdown(CHGAPP_RESET_AFP);
         break;

    case QCOM_CHARGER_PLATFORM_ACTION_SHUTDOWN:
         //print error message and trigger system shutdown
         //These errors will only be checked and handled when battery voltage is not high enough to boot and uefi charging is needed.
         CHARGER_FILE_UART_DEBUG((EFI_D_WARN, "QcomChargerDxe::%a Waiting for %d s \r\n", __FUNCTION__, QCOM_CHARGER_IDLE_WAIT_DURATION/QCOM_CHARGER_MS_TO_S));
         WaitForTimeout (QCOM_CHARGER_IDLE_WAIT_DURATION, TIMEOUT_WAIT_FOR_KEY, NULL);
         ChargerLib_ForceSysShutdown(CHGAPP_RESET_SHUTDOWN);
         break;

    case QCOM_CHARGER_PLATFORM_ACTION_START_CHARGING:
          /* Assign entry voltage on warm boot and soc after profile is loaded or not loaded as in warm/cold boot */
          if(gChargerSharedInfo.uefi_entry_mV == QCOM_CHARGER_INVALID_VALUE_MARKER)
          {
            gChargerSharedInfo.uefi_entry_mV    = CurrentBatteryStatus.BatteryVoltage;
          }
          if (gChargerPlatformCfgData.FgCfgData.LoadBatteryProfile == TRUE)
          {
            gChargerSharedInfo.uefi_entry_soc = CurrentBatteryStatus.StateOfCharge;
          }
          else
          {
            gChargerSharedInfo.uefi_entry_soc   = QCOM_CHARGER_INVALID_VALUE_MARKER;
          }
          CHARGER_DEBUG(( EFI_D_WARN, "QcomChargerDxe:: %a Saving Entry VBatt  = %d SOC = %d \r\n", __FUNCTION__,
                          CurrentBatteryStatus.BatteryVoltage, CurrentBatteryStatus.StateOfCharge));
          if (QCOM_CHARGER_PLATFORM_CHARGER_ATTACHED_USB == pChargerActionInfo->ChargerAttached)
          {
            ChargerLib_InitializeCharging();
          }
         break;

    case QCOM_CHARGER_PLATFORM_ACTION_STOP_CHARGING:
         if(TRUE == gChargingInitialized)
         {
           ChargerLib_ChargerEnable(FALSE);
           gChargingInitialized = FALSE;
         }
         if(gChargerPlatformCfgData.ChargerLedConfig)
         {
           /* Turn Off Charging */
           bToggleLed = FALSE;
           ChargerLib_LedOn(bToggleLed);
         }
         break;

    case QCOM_CHARGER_PLATFORM_ACTION_NO_CHARGE_WAIT:
         if (gChargerPlatformCfgData.WiPowerCfgData.WipowerEnabled 
            && (QCOM_CHARGER_PLATFORM_CHARGER_ATTACHED_DCIN == pChargerActionInfo->ChargerAttached))
         {
           //do nothing if wipower is enabled and dcin is attached
           break;
         }  
         else
         {
           //only need to disable charging or shutdown if not wipower enabled.
         ChargerLib_HandleNoChargeAndWait();
         }

         if(gChargerPlatformCfgData.EnableChargerWdog)
         {
           /* Pet the watchdog if feature is enabled */
           ChargerLib_PetChgWdog();
         }
         break;
    
    case QCOM_CHARGER_PLATFORM_ACTION_CONTINUE:
         if(gChargerPlatformCfgData.EnableChargerWdog)
         {
           /* Pet the watchdog if feature is enabled */
           ChargerLib_PetChgWdog();
         }
         if(gChargerPlatformCfgData.ChargerLedConfig)
         {
            /*  DEBUG ONLY */
           /* CHARGER_DEBUG((EFI_D_WARN, "QcomChargerDxe::%a SWLedToggleConfig = %d \r\n", __FUNCTION__, gChargerPlatformCfgData.ChargerLedConfig)); */
           switch(gChargerPlatformCfgData.ChargerLedConfig)
           {
             case QCOM_CHARGER_PLATFORM_CHARGING_LED_ON:
               bToggleLed = TRUE; /* Make sure to turn on flag as control can come back from wait state */
               ChargerLib_LedOn(bToggleLed);
               break;
             case QCOM_CHARGER_PLATFORM_CHARGING_LED_TOGGLE:
               ChargerLib_LedOn(bToggleLed);
               bToggleLed = (bToggleLed == TRUE)? FALSE: TRUE;
              break;
             case QCOM_CHARGER_PLATFORM_CHARGING_LED_OFF:
              /* will not reache here */
             default:
              break;
            }
         }
         else
         {
           /*  DEBUG ONLY */
           /* CHARGER_DEBUG(( EFI_D_WARN, "QcomChargerDxe:: %a Charging Led Indication is off = %d \r\n", __FUNCTION__, gChargerPlatformCfgData.ChargerLedConfig)); */
         }
         /* Debug FG SRAM */
         ChargerLib_DumpSram(FALSE);
         break;

    case QCOM_CHARGER_PLATFORM_ACTION_GOOD_TO_BOOT:
        /* Assign Exit voltage and soc */
        gChargerSharedInfo.uefi_exit_mV    = CurrentBatteryStatus.BatteryVoltage;
        if (gChargerPlatformCfgData.FgCfgData.LoadBatteryProfile == TRUE)
        {
          gChargerSharedInfo.uefi_exit_soc = CurrentBatteryStatus.StateOfCharge;
        }
        else
        {
          gChargerSharedInfo.uefi_exit_soc   = QCOM_CHARGER_INVALID_VALUE_MARKER;
        }
        CHARGER_DEBUG(( EFI_D_WARN, "QcomChargerDxe:: %a Saving Exit VBat = %d Soc = %d \r\n", __FUNCTION__,
                         CurrentBatteryStatus.BatteryVoltage, CurrentBatteryStatus.StateOfCharge));
        /* Save Smem Info ignoring return status as XBL loader changes are not ready yet*/
        ChargerPlatform_SaveChargeInfoToSmem(&gChargerSharedInfo);
        if (gChargerPlatformCfgData.WiPowerCfgData.WipowerEnabled)
        {
          if (gChargerPlatformCfgData.WiPowerCfgData.DCINDisableOnExit)
        {
          //suspend DCIn when wipower flags are set.
          (void)ChargerLib_DcinSuspend(TRUE);
        }
          if (QCOM_CHARGER_PLATFORM_CHARGER_ATTACHED_DCIN == pChargerActionInfo->ChargerAttached)
          {
            (void)ChargerLib_ToggleWipowerShutDownLatch();
          }
        }

        /* Turn Off Charging */
        bToggleLed = FALSE;
        ChargerLib_LedOn(bToggleLed);
        break;

    case QCOM_CHARGER_PLATFORM_ACTION_PROFILE_LOAD:
        /* Assign only entry voltage for smem before profile load, soc will be update after profile is loaded in next action which is start charging action*/
        gChargerSharedInfo.uefi_entry_mV    = CurrentBatteryStatus.BatteryVoltage;
        ChargerPlatform_LoadProfile(pChargerActionInfo);
        break;

    case QCOM_CHARGER_PLATFORM_ACTION_SHUTDOWN_USB_DC_PON_DISABLED:
      //print error message and trigger system shutdown
      //These errors will only be checked and handled when battery voltage is not high enough to boot and uefi charging is needed.
      CHARGER_FILE_UART_DEBUG((EFI_D_WARN, "QcomChargerDxe::%a Waiting for %d s \r\n", __FUNCTION__, QCOM_CHARGER_IDLE_WAIT_DURATION/QCOM_CHARGER_MS_TO_S));
      WaitForTimeout (QCOM_CHARGER_IDLE_WAIT_DURATION, TIMEOUT_WAIT_FOR_KEY, NULL);
      ChargerLib_ForceSysShutdown(CHGAPP_RESET_SHUTDOWN_USB_DC_PON_DISABLED);
      break;

        break;
    default:
        CHARGER_DEBUG(( EFI_D_WARN, "QcomChargerDxe:: %a Action Passed = %d \r\n", __FUNCTION__,ChargingAction));
      break;
  }
  
  return EFI_SUCCESS;
}


/**
ChargerPlatform_GetUefiVariableValues()

@brief
Reads UEFI Variables changed via BDS Menu
*/
EFI_STATUS ChargerPlatform_GetUefiVariableValues( VOID)
{
  UINT8          Flag          = 0;
  UINTN          VarSize       = sizeof(Flag);
  STATIC BOOLEAN VariablesRead = FALSE;
  EFI_STATUS     Status = EFI_SUCCESS;

  if (FALSE == VariablesRead)
  {
    VariablesRead = TRUE;
    /*We are supposed to read only once. if the variable doesn't exist, make assumption on the value to treat
      variable not being there as expected condition and cache the expectation instead. We are memsetting the
      structure variable and so by default it is disabled
    */
    Status = gRT->GetVariable(L"PrintChargerAppDbgMsg", &gQcomTokenSpaceGuid, NULL, &VarSize, &Flag);
    if (EFI_SUCCESS == Status )
    {
      gChargerPlatformCfgData.DbgCfgData.PrintChargerAppDbgMsg = (Flag) ? TRUE : FALSE;
      /* DO NOT CHK IN DEBUG */
      /*DEBUG(( EFI_D_WARN, "QcomChargerDxe:: %a GetVariable Success = %r Flag = %d \r\n", __FUNCTION__,Status, Flag)); */
    }
    else
    {
      /* DO NOT CHK IN DEBUG */
      /* DEBUG(( EFI_D_WARN, "QcomChargerDxe:: %a GetVariable Failed = %r \r\n", __FUNCTION__,Status)); */
    }
  }

  return EFI_SUCCESS;
}

/**
ChargerPlatform_GetConfigData()

@brief
Returns config data
*/
EFI_STATUS ChargerPlatform_GetConfigData
(
  QCOM_CHARGER_PLATFORM_CFGDATA_TYPE *pChargerPlatformCfgData
)
{

  if(!pChargerPlatformCfgData)
    return EFI_INVALID_PARAMETER;

  CopyMemS(pChargerPlatformCfgData, sizeof(QCOM_CHARGER_PLATFORM_CFGDATA_TYPE), &gChargerPlatformCfgData, sizeof(QCOM_CHARGER_PLATFORM_CFGDATA_TYPE));

  return EFI_SUCCESS;
}


/**
ChargerPlatform_ReadCfgParams()

@brief
Battery Parameter Default Configurations file read Call Back
*/
VOID
ChargerPlatform_ReadCfgParams
(
  UINT8* Section,
  UINT8* Key,
  UINT8* Value
)
{

  //CHARGER_DEBUG(( EFI_D_INFO, "Section = \"%s\", Key = \"%s\", Value = \"%s\"\n", Section, Key, Value));

  if (AsciiStriCmp ((CHAR8*)Section, "PlatformCommon") == 0) //Common
  {
  if (AsciiStriCmp ((CHAR8*)Key, "CfgVersion") == 0)
  {
    gChargerPlatformCfgData.CfgVersion = ChargerPlatformFile_AsciiToInt((char *)Value);
    return;
  }

      if (AsciiStriCmp((CHAR8 *)Key, "BattVoltLimHighDelta") == 0)
  {
        gChargerPlatformCfgData.BattVoltLimHighDelta = ChargerPlatformFile_AsciiToInt((char *)Value);
    return;
  }

      if (AsciiStriCmp ((CHAR8*)Key, "SWThermalMitigationEnable") == 0)
  {
        gChargerPlatformCfgData.SWThermalMitigationEnable = ( AsciiStriCmp ((CHAR8*)Value, "TRUE") == 0 );
    return;
  }

  if (AsciiStriCmp ((CHAR8*)Key, "PrintChargerAppDbgMsg") == 0)
  {
    gChargerPlatformCfgData.DbgCfgData.PrintChargerAppDbgMsg = ( AsciiStriCmp ((CHAR8*)Value, "TRUE") == 0 );
    return;
  }

  if (AsciiStriCmp ((CHAR8*)Key, "PrintChargerAppDbgMsgToFile") == 0)
  {
    gChargerPlatformCfgData.DbgCfgData.PrintChargerAppDbgMsgToFile= ( AsciiStriCmp ((CHAR8*)Value, "TRUE") == 0 );
    return;
  }

  if (AsciiStriCmp((CHAR8 *)Key, "ChargingTermCurrent") == 0)
  {
    gChargerPlatformCfgData.FgCfgData.ChargingTermCurrent = ChargerPlatformFile_AsciiToInt((char *)Value);
    gChargerPlatformCfgData.SchgCfgData.ChargingTermCurrent = gChargerPlatformCfgData.FgCfgData.ChargingTermCurrent;
    return;
  }

  if (AsciiStriCmp ((CHAR8*)Key, "BatteryIdTolerance") == 0)
  {
    gChargerPlatformCfgData.BattIdCfgData.BatteryIdTolerance = ChargerPlatformFile_AsciiToInt((char *)Value);
    return;
  }

  if (AsciiStriCmp ((CHAR8*)Key, "DebugBoardBatteryIdMin") == 0)
  {
    gChargerPlatformCfgData.BattIdCfgData.DebugBoardBatteryIdMin = ChargerPlatformFile_AsciiToInt((char *)Value);;
    return;
  }

  if (AsciiStriCmp ((CHAR8*)Key, "DebugBoardBatteryIdMax") == 0)
  {
    gChargerPlatformCfgData.BattIdCfgData.DebugBoardBatteryIdMax = ChargerPlatformFile_AsciiToInt((char *)Value);
    return;
  }

  if (AsciiStriCmp ((CHAR8*)Key, "RegularBatteryIdMin") == 0)
  {
    gChargerPlatformCfgData.BattIdCfgData.RegularBatteryIdMin = ChargerPlatformFile_AsciiToInt((char *)Value);
    return;
  }

  if (AsciiStriCmp ((CHAR8*)Key, "RegularBatteryIdMax") == 0)
  {
    gChargerPlatformCfgData.BattIdCfgData.RegularBatteryIdMax = ChargerPlatformFile_AsciiToInt((char *)Value);
    return;
  }

  if (AsciiStriCmp ((CHAR8*)Key, "SmartBatteryIdMin") == 0)
  {
    gChargerPlatformCfgData.BattIdCfgData.SmartBatteryIdMin = ChargerPlatformFile_AsciiToInt((char *)Value);
    return;
  }

  if (AsciiStriCmp ((CHAR8*)Key, "SmartBatteryIdMax") == 0)
  {
    gChargerPlatformCfgData.BattIdCfgData.SmartBatteryIdMax = ChargerPlatformFile_AsciiToInt((char *)Value);
    return;
  }

  if (AsciiStriCmp ((CHAR8*)Key, "ConservChgFvDelta") == 0)
  {
    gChargerPlatformCfgData.ConservChgFvDelta = ChargerPlatformFile_AsciiToInt((char *)Value);
    return;
  }

  if (AsciiStriCmp ((CHAR8*)Key, "UnknownBatteryBehavior") == 0)
  {
    gChargerPlatformCfgData.UnknownBatteryBehavior = ChargerPlatformFile_AsciiToInt((char *)Value);
    return;
  }

      if (AsciiStriCmp ((CHAR8*)Key, "DebugBoardBehavior") == 0)
      {
        gChargerPlatformCfgData.DebugBoardBehavior= ChargerPlatformFile_AsciiToInt((char *)Value);
        return;
      }

  if (AsciiStriCmp ((CHAR8*)Key, "BootToHLOSThresholdInMv") == 0)
  {
    gChargerPlatformCfgData.BootToHLOSThresholdInMv = ChargerPlatformFile_AsciiToInt((char *)Value);
    return;
  }

  if (AsciiStriCmp ((CHAR8*)Key, "OsStandardBootSocThreshold") == 0)
  {
    gChargerPlatformCfgData.BootToHLOSThresholdInSOC= ChargerPlatformFile_AsciiToInt((char *)Value);
    return;
  }

  if (AsciiStriCmp ((CHAR8*)Key, "NoChargeAndWait") == 0)
  {
    gChargerPlatformCfgData.NoChargeAndWait = ( AsciiStriCmp ((CHAR8*)Value, "TRUE") == 0 );
    return;
  }

  if (AsciiStriCmp ((CHAR8*)Key, "EmergencyShutdownVbatt") == 0)
  {
    gChargerPlatformCfgData.EmergencyShutdownVbatt = ChargerPlatformFile_AsciiToInt((char *)Value);
    return;
  }

  if (AsciiStriCmp ((CHAR8*)Key, "BattMissingCfg") == 0)
  {
    gChargerPlatformCfgData.FgCfgData.BattMissingCfg= ChargerPlatformFile_AsciiToInt((char *)Value);
    return;
  }

  if (AsciiStriCmp ((CHAR8*)Key, "EnableChargerWdog") == 0)
  {
    gChargerPlatformCfgData.EnableChargerWdog= ChargerPlatformFile_AsciiToInt((char *)Value);
    return;
  }

  if (AsciiStriCmp ((CHAR8*)Key, "ProgramAuxThermCoeffs") == 0)
  {
    gChargerPlatformCfgData.FgCfgData.AuxThermCoeffs.ProgramAuxThermCoeffs = ( AsciiStriCmp ((CHAR8*)Value, "TRUE") == 0 );
    return;
  }

  if (AsciiStriCmp ((CHAR8*)Key, "AuxThermC1") == 0)
  {
    gChargerPlatformCfgData.FgCfgData.AuxThermCoeffs.AuxThermC1= ChargerPlatformFile_AsciiStrToHex((CHAR8 *)Value, AsciiStrLen((CHAR8 *)Value));
        /* CHARGER_DEBUG(( EFI_D_WARN, "QcomChargerDxe:: %a AuxThermC1 = 0x%x Length = %d.\n\r", __FUNCTION__, gChargerPlatformCfgData.FgCfgData.AuxThermCoeffs.AuxThermC1, AsciiStrLen((CHAR8 *)Value)));*/
    return;
  }

  if (AsciiStriCmp ((CHAR8*)Key, "AuxThermC2") == 0)
  {
    gChargerPlatformCfgData.FgCfgData.AuxThermCoeffs.AuxThermC2= ChargerPlatformFile_AsciiStrToHex((CHAR8 *)Value, AsciiStrLen((CHAR8 *)Value));
    return;
  }

  if (AsciiStriCmp ((CHAR8*)Key, "AuxThermC3") == 0)
  {
    gChargerPlatformCfgData.FgCfgData.AuxThermCoeffs.AuxThermC3= ChargerPlatformFile_AsciiStrToHex((CHAR8 *)Value, AsciiStrLen((CHAR8 *)Value));
    return;
  }

  if (AsciiStriCmp ((CHAR8*)Key, "AuxThermHalfRangeInC") == 0)
  {
    gChargerPlatformCfgData.FgCfgData.AuxThermCoeffs.AuxThermHalfRangeInC = ChargerPlatformFile_AsciiToInt((char *)Value);
    return;
  }

  if (AsciiStriCmp ((CHAR8*)Key, "ProgramBattThermCoeffs") == 0)
  {
    gChargerPlatformCfgData.FgCfgData.FgBattThermCoffs.ProgramBattThermCoeffs = ( AsciiStriCmp ((CHAR8*)Value, "TRUE") == 0 );
    return;
  }

  if (AsciiStriCmp ((CHAR8*)Key, "BattThermC1") == 0)
  {
    gChargerPlatformCfgData.FgCfgData.FgBattThermCoffs.BattThermC1= ChargerPlatformFile_AsciiStrToHex((CHAR8 *)Value, AsciiStrLen((CHAR8 *)Value));
    /* CHARGER_DEBUG(( EFI_D_WARN, "QcomChargerDxe:: %a AuxThermC1 = 0x%x Length = %d.\r\n", __FUNCTION__, gChargerPlatformCfgData.FgCfgData.AuxThermCoeffs.AuxThermC1, AsciiStrLen((CHAR8 *)Value)));*/
    return;
  }

  if (AsciiStriCmp ((CHAR8*)Key, "BattThermC2") == 0)
  {
    gChargerPlatformCfgData.FgCfgData.FgBattThermCoffs.BattThermC2= ChargerPlatformFile_AsciiStrToHex((CHAR8 *)Value, AsciiStrLen((CHAR8 *)Value));
    return;
  }

  if (AsciiStriCmp ((CHAR8*)Key, "BattThermC3") == 0)
  {
    gChargerPlatformCfgData.FgCfgData.FgBattThermCoffs.BattThermC3= ChargerPlatformFile_AsciiStrToHex((CHAR8 *)Value, AsciiStrLen((CHAR8 *)Value));
    return;
  }

  if (AsciiStriCmp ((CHAR8*)Key, "BattThermHalfRangeInC") == 0)
  {
    gChargerPlatformCfgData.FgCfgData.FgBattThermCoffs.BattThermHalfRangeInC = ChargerPlatformFile_AsciiToInt((char *)Value);
    return;
  }

  if (AsciiStriCmp ((CHAR8*)Key, "ProgramSkinAndChargerHotThreshold") == 0)
  {
    gChargerPlatformCfgData.FgCfgData.SkinAndChargerHotThreshold.ProgramSkinAndChargerHotThreshold = ( AsciiStriCmp ((CHAR8*)Value, "TRUE") == 0 );
    return;
  }

  if (AsciiStriCmp ((CHAR8*)Key, "DeviceSkinHotInC") == 0)
  {
    gChargerPlatformCfgData.FgCfgData.SkinAndChargerHotThreshold.DeviceSkinHotInC = ChargerPlatformFile_AsciiToInt((char *)Value);
    return;
  }

  if (AsciiStriCmp ((CHAR8*)Key, "DeviceSkinTooHotInC") == 0)
  {
    gChargerPlatformCfgData.FgCfgData.SkinAndChargerHotThreshold.DeviceSkinTooHotInC = ChargerPlatformFile_AsciiToInt((char *)Value);
    return;
  }

      if (AsciiStriCmp ((CHAR8*)Key, "ChargerHotInC") == 0)
      {
        gChargerPlatformCfgData.FgCfgData.SkinAndChargerHotThreshold.ChargerHotInC = ChargerPlatformFile_AsciiToInt((char *)Value);
        return;
      }

  if (AsciiStriCmp ((CHAR8*)Key, "ChargerTooHotInC") == 0)
  {
    gChargerPlatformCfgData.FgCfgData.SkinAndChargerHotThreshold.ChargerTooHotInC= ChargerPlatformFile_AsciiToInt((char *)Value);
    return;
  }

      if (AsciiStriCmp ((CHAR8*)Key, "SocBasedBoot") == 0)
      {
        gChargerPlatformCfgData.SocBasedBoot = ( AsciiStriCmp ((CHAR8*)Value, "TRUE") == 0 );
        return;
      }

      if (AsciiStriCmp ((CHAR8*)Key, "LoadBatteryProfile") == 0)
      {
        gChargerPlatformCfgData.FgCfgData.LoadBatteryProfile = ( AsciiStriCmp ((CHAR8*)Value, "TRUE") == 0 );
        return;
      }

      if (AsciiStriCmp ((CHAR8*)Key, "DispSignOfLifeMaxThresholdMv") == 0)
  {
        gChargerPlatformCfgData.DispSignOfLifeMaxThresholdMv = ChargerPlatformFile_AsciiToInt((char *)Value);
    return;
  }

  if (AsciiStriCmp((CHAR8*)Key, "SkinTempSrc") == 0)
  {
    gChargerPlatformCfgData.SchgCfgData.EnableSkinTempINov = (AsciiStriCmp((CHAR8*)Value, "TRUE") == 0);
    return;
  }

  if (AsciiStriCmp((CHAR8*)Key, "DieTempSrc") == 0)
  {
    gChargerPlatformCfgData.SchgCfgData.EnableDieTempINov = (AsciiStriCmp((CHAR8*)Value, "TRUE") == 0);
    return;
  }

  if (AsciiStriCmp((CHAR8*)Key, "DieTempCompSrc") == 0)
  {
    gChargerPlatformCfgData.SchgCfgData.EnableDieTempCompINov = (AsciiStriCmp((CHAR8*)Value, "TRUE") == 0);
    return;
  }

  if (AsciiStriCmp ((CHAR8*)Key, "DumpSram") == 0)
  {
    gChargerPlatformCfgData.FgCfgData.FgSramDbgCfgs.DumpSram = ( AsciiStriCmp ((CHAR8*)Value, "TRUE") == 0 );
    return;
  }

  if (AsciiStriCmp ((CHAR8*)Key, "DumpSramStartAddr") == 0)
  {
    gChargerPlatformCfgData.FgCfgData.FgSramDbgCfgs.DumpSramStartAddr = ChargerPlatformFile_AsciiToInt((char *)Value);
    return;
  }

  if (AsciiStriCmp ((CHAR8*)Key, "DumpSramEndAddr") == 0)
  {
    gChargerPlatformCfgData.FgCfgData.FgSramDbgCfgs.DumpSramEndAddr = ChargerPlatformFile_AsciiToInt((char *)Value);
    return;
  }

  if (AsciiStriCmp ((CHAR8*)Key, "DumpSramDuration") == 0)
  {
    gChargerPlatformCfgData.FgCfgData.FgSramDbgCfgs.DumpSramDuration = ChargerPlatformFile_AsciiToInt((char *)Value);
    return;
  }

  if (AsciiStriCmp((CHAR8*)Key, "BattThermBiasWait") == 0)
  {
    gChargerPlatformCfgData.FgCfgData.FgBattThermCfg.BiasWait = ChargerPlatformFile_AsciiToInt((char *)Value);
    return;
  }

  if (AsciiStriCmp((CHAR8*)Key, "BattThermGndSel") == 0)
  {
    gChargerPlatformCfgData.FgCfgData.FgBattThermCfg.GroundSel = (AsciiStriCmp((CHAR8*)Value, "TRUE") == 0);
    return;
  }

  if (AsciiStriCmp((CHAR8*)Key, "AuxThermBiasWait") == 0)
  {
    gChargerPlatformCfgData.FgCfgData.FgAuxThermCfg.BiasWait = ChargerPlatformFile_AsciiToInt((char *)Value);
    return;
  }
  if (AsciiStriCmp((CHAR8*)Key, "AuxThermGndSel") == 0)
  {
    gChargerPlatformCfgData.FgCfgData.FgAuxThermCfg.GroundSel = (AsciiStriCmp((CHAR8*)Value, "TRUE") == 0);
    return;
  }

  if (AsciiStriCmp((CHAR8*)Key, "RconnComp") == 0)
  {
    gChargerPlatformCfgData.FgCfgData.RconnComp = ChargerPlatformFile_AsciiToInt((char *)Value);
    return;
  }

      if (AsciiStriCmp ((CHAR8*)Key, "TsensHighTemp") == 0)
  {
        gChargerPlatformCfgData.ThermalCfgData.TsensHighTemp = ChargerPlatformFile_AsciiToInt((char *)Value);
    return;
  }

      if (AsciiStriCmp ((CHAR8*)Key, "TsensExtremeTemp") == 0)
  {
        gChargerPlatformCfgData.ThermalCfgData.TsensExtremeTemp = ChargerPlatformFile_AsciiToInt((char *)Value);
    return;
  }

  if (AsciiStriCmp ((CHAR8*)Key, "TsensLowTemp") == 0)
  {
    gChargerPlatformCfgData.ThermalCfgData.TsensLowTemp = ChargerPlatformFile_AsciiToInt((char *)Value);
    return;
  }

  if (AsciiStriCmp ((CHAR8*)Key, "TsensTimeoutMins") == 0)
  {
    gChargerPlatformCfgData.ThermalCfgData.TsensTimeoutMins = ChargerPlatformFile_AsciiToInt((char *)Value);
    return;
  }

  if (AsciiStriCmp ((CHAR8*)Key, "EnableChargerFgDump") == 0)
  {
    gChargerPlatformCfgData.DbgCfgData.EnableChargerFgDump = ( AsciiStriCmp ((CHAR8*)Value, "TRUE") == 0 );
    return;
  }

  if (AsciiStriCmp((CHAR8*)Key, "WiPowerSupported") == 0)
  {
    gChargerPlatformCfgData.WiPowerCfgData.WipowerEnabled = (AsciiStriCmp((CHAR8*)Value, "TRUE") == 0);
    return;
  }

  if (AsciiStriCmp((CHAR8*)Key, "DCInBootToHLOSThresholdInMv") == 0)
  {
    gChargerPlatformCfgData.WiPowerCfgData.WipowerBootThreshold = ChargerPlatformFile_AsciiToInt((char *)Value);
    return;
  }

  if (AsciiStriCmp((CHAR8*)Key, "SuspendDCIn") == 0)
  {
    gChargerPlatformCfgData.WiPowerCfgData.DCINDisableOnExit = (AsciiStriCmp((CHAR8*)Value, "TRUE") == 0);
    return;
  }

  if (AsciiStriCmp ((CHAR8*)Key, "FgCondRestart") == 0)
  {
      gChargerPlatformCfgData.FgCfgData.FgCondRestart = ( AsciiStriCmp ((CHAR8*)Value, "TRUE") == 0 );
      return;
  }

  if (AsciiStriCmp((CHAR8*)Key, "VBattEstDiffThreshold") == 0)
  {
    gChargerPlatformCfgData.FgCfgData.VBattEstDiffThreshold = ChargerPlatformFile_AsciiToInt((char *)Value);
    return;
  }

  if (AsciiStriCmp((CHAR8*)Key, "ChargerLedConfig") == 0)
  {
    gChargerPlatformCfgData.ChargerLedConfig = ChargerPlatformFile_AsciiToInt((CHAR8*)Value);
    return;
  }



    }
  else if ( ((EFI_PLATFORMINFO_TYPE_MTP == PlatformType) && (AsciiStriCmp ((CHAR8*)Section, "PlatformMTP") == 0)) ||
       ((EFI_PLATFORMINFO_TYPE_QRD == PlatformType) && (AsciiStriCmp ((CHAR8*)Section, "PlatformQRD") == 0))  )
  {
      if (AsciiStriCmp ((CHAR8*)Key, "ChgFvMax") == 0)
    {
        gChargerPlatformCfgData.SchgCfgData.ChgFvMax = ChargerPlatformFile_AsciiToInt((char *)Value);;
    return;
  }

      if (AsciiStriCmp ((CHAR8*)Key, "ChgFccMax") == 0)
    {
      gChargerPlatformCfgData.SchgCfgData.ChgFccMax = ChargerPlatformFile_AsciiToInt((char *)Value);
    return;
  }

      if (AsciiStriCmp ((CHAR8*)Key, "JeitaCriticalTempLowLimit") == 0)
  {

      gChargerPlatformCfgData.FgCfgData.HwJeitaThreshold.JeitaCriticalTempLowLimit = ChargerPlatformFile_AsciiToInt((char *)Value);
    return;
  }

      if (AsciiStriCmp ((CHAR8*)Key, "JeitaHardColdLimit") == 0)
  {
      gChargerPlatformCfgData.FgCfgData.HwJeitaThreshold.JeitaHardColdLimit = ChargerPlatformFile_AsciiToInt((char *)Value);
    return;
  }

      if (AsciiStriCmp ((CHAR8*)Key, "JeitaSoftColdLimit") == 0)
    {
      gChargerPlatformCfgData.FgCfgData.HwJeitaThreshold.JeitaSoftColdLimit = ChargerPlatformFile_AsciiToInt((char *)Value);
    return;
  }

      if (AsciiStriCmp ((CHAR8*)Key, "JeitaSoftHotLimit") == 0)
  {
      gChargerPlatformCfgData.FgCfgData.HwJeitaThreshold.JeitaSoftHotLimit = ChargerPlatformFile_AsciiToInt((char *)Value);
    return;
  }

      if (AsciiStriCmp ((CHAR8*)Key, "JeitaHardHotLimit") == 0)
    {
      gChargerPlatformCfgData.FgCfgData.HwJeitaThreshold.JeitaHardHotLimit = ChargerPlatformFile_AsciiToInt((char *)Value);
        return;
  }

      if (AsciiStriCmp ((CHAR8*)Key, "JeitaCriticalTempHighLimit") == 0)
    {
      gChargerPlatformCfgData.FgCfgData.HwJeitaThreshold.JeitaCriticalTempHighLimit = ChargerPlatformFile_AsciiToInt((char *)Value);
    return;
  }

      if (AsciiStriCmp ((CHAR8*)Key, "JeitaCcCompCfg") == 0)
  {
        gChargerPlatformCfgData.SchgCfgData.JeitaCcCompCfg= ChargerPlatformFile_AsciiToInt((char *)Value);
    return;
  }

      if (AsciiStriCmp ((CHAR8*)Key, "JeitaFvCompCfg") == 0)
  {
      gChargerPlatformCfgData.SchgCfgData.JeitaFvCompCfg= ChargerPlatformFile_AsciiToInt((char *)Value);
    return;
  }

      if (AsciiStriCmp ((CHAR8*)Key, "JeitaSoftColdFvCompEnable") == 0)
    {
      gChargerPlatformCfgData.SchgCfgData.JeitaSoftColdFvCompEnable = ( AsciiStriCmp ((CHAR8*)Value, "TRUE") == 0 );
    return;
  }

      if (AsciiStriCmp ((CHAR8*)Key, "JeitaSoftHotFvCompEnable") == 0)
  {
      gChargerPlatformCfgData.SchgCfgData.JeitaSoftHotFvCompEnable = ( AsciiStriCmp ((CHAR8*)Value, "TRUE") == 0 );
    return;
  }

      if (AsciiStriCmp ((CHAR8*)Key, "JeitaSoftColdCcCompEnable") == 0)
    {
      gChargerPlatformCfgData.SchgCfgData.JeitaSoftColdCcCompEnable = ( AsciiStriCmp ((CHAR8*)Value, "TRUE") == 0 );
    return;
  }

      if (AsciiStriCmp ((CHAR8*)Key, "JeitaSoftHotCcCompEnable") == 0)
  {
      gChargerPlatformCfgData.SchgCfgData.JeitaSoftHotCcCompEnable = ( AsciiStriCmp ((CHAR8*)Value, "TRUE") == 0 );
    return;
  }
      if (AsciiStriCmp ((CHAR8*)Key, "VBtEmpty") == 0)
    {
      gChargerPlatformCfgData.FgCfgData.VBtEmpty= ChargerPlatformFile_AsciiToInt((char *)Value);
        return;
    }
  }

  return;
}


EFI_STATUS ChargerPlatform_SaveChargeInfoToSmem(pm_chg_info_type *ChargerActionInfo)
{
  EFI_STATUS Status = EFI_SUCCESS;
  UINT32     buf_size = sizeof(pm_chg_info_type);
  UINT32     buf_size_ret = 0;
  pm_chg_info_type *pSmemChargerInfo = NULL, *pSmemChargerInfoRet = NULL;

  pSmemChargerInfo = (pm_chg_info_type *) smem_get_addr(SMEM_CHARGER_BATTERY_INFO, &buf_size_ret);
  if(!pSmemChargerInfo)
  {
    CHARGER_DEBUG((EFI_D_WARN, "QcomChargerDxe:: %a Retrieve Error.. XBL Core allocating SMEM now \r\n",__FUNCTION__));
      /* Assume Smem is already initilized in XBL Loader - No need to alloc as XBL loader will alloc for Core keeping this as debug code */
    pSmemChargerInfo = (pm_chg_info_type *)smem_alloc(SMEM_CHARGER_BATTERY_INFO, buf_size);
    if(!pSmemChargerInfo)
    {
      CHARGER_DEBUG((EFI_D_WARN, "QcomChargerDxe:: %a smem_alloc Error \r\n",__FUNCTION__));
      return EFI_DEVICE_ERROR;
    }
    else
    {
      CHARGER_DEBUG((EFI_D_WARN, "QcomChargerDxe:: %a SMEM Allocated \r\n",__FUNCTION__));
      /* Initialized to -1 since SBL did not allocate smem yet */
      pSmemChargerInfo->version       = 1;
      pSmemChargerInfo->sbl_entry_mV  = QCOM_CHARGER_INVALID_VALUE_MARKER;
      pSmemChargerInfo->sbl_entry_soc = QCOM_CHARGER_INVALID_VALUE_MARKER;
    }
  }

  /* Assign required values to smem memory */
  pSmemChargerInfo->uefi_entry_mV  = ChargerActionInfo->uefi_entry_mV;
  pSmemChargerInfo->uefi_exit_mV   = ChargerActionInfo->uefi_exit_mV;
  pSmemChargerInfo->uefi_entry_soc = ChargerActionInfo->uefi_entry_soc;
  pSmemChargerInfo->uefi_exit_soc  = ChargerActionInfo->uefi_exit_soc;

  buf_size_ret = 0;

  pSmemChargerInfoRet = (pm_chg_info_type *) smem_get_addr(SMEM_CHARGER_BATTERY_INFO, &buf_size_ret);
  if(!pSmemChargerInfoRet){
    CHARGER_DEBUG((EFI_D_WARN, "QcomChargerDxe:: %a Retrieve Error 2 \r\n",__FUNCTION__));
    return EFI_DEVICE_ERROR;
  }

  CHARGER_DEBUG((EFI_D_WARN, "QcomChargerDxe:: buf_size_ret = %d uefi_entry_mV = %d uefi_exit_mV = %d uefi_entry_soc = %d \r\n", buf_size_ret, pSmemChargerInfoRet->uefi_entry_mV, pSmemChargerInfoRet->uefi_exit_mV, pSmemChargerInfoRet->uefi_entry_soc));
  CHARGER_DEBUG((EFI_D_WARN, "QcomChargerDxe:: sbl_entry_mV = %d sbl_entry_soc = %d ueft_exit_soc = %d \r\n", pSmemChargerInfoRet->sbl_entry_mV, pSmemChargerInfoRet->sbl_entry_soc, pSmemChargerInfoRet->uefi_exit_soc));

  pSmemChargerInfoRet = NULL;
  pSmemChargerInfo    = NULL;

  return Status;

}

EFI_STATUS ChargerPlatform_ProfileLoadingInit(QCOM_CHARGER_PLATFORM_ACTION_TYPE *pActionType, QCOM_CHARGER_PLATFORM_ACTION_INFO *pChargerActionInfo)
{
  EFI_STATUS Status = EFI_SUCCESS;
  QCOM_CHARGER_PLATFORM_BATT_PROFILE_STATUS BattProfileStatus    = {0};
  QCOM_CHARGER_BATT_STATUS_INFO             CurrentBatteryStatus = {0};
  CHARGERLIB_CHARGING_ERROR_TYPES           ErrorType  = CHARGERLIB_CHARGING_ERROR_NONE;

  Status = ChargerLib_GetBatteryProfileStatus((chargerlib_batt_profile_status *)&BattProfileStatus);
  Status |= ChargerLib_GetErrors(&ErrorType);
  if( EFI_SUCCESS == Status)
  {
    /* Attempt to load profile or restart FG will be called if below errors turns not TRUE */
    if((ErrorType != CHARGERLIB_CHARGING_ERROR_BATTERY_NOT_DETECTED ) && 
       (ErrorType != CHARGERLIB_CHARGING_ERROR_DEBUG_BOARD ) &&
       (ErrorType != CHARGERLIB_CHARGING_ERROR_BATT_TEMP_OUTSIDE_OPERATIONAL_RANGE) && 
       (ErrorType != CHARGERLIB_CHARGING_ERROR_TSENSE_CRITICAL) &&
       (ErrorType != CHARGERLIB_DEVICE_ERROR) && 
       (ErrorType != CHARGERLIB_CHARGING_ERROR_FG_ERROR ) && 
       (ErrorType != CHARGERLIB_CHARGING_ERROR_ADC_ERROR))
    {
      /* Assign Profile State info for action */
      pChargerActionInfo->ProfState.eProfileState = (QCOM_CHARGER_PLATFORM_BATT_PROFILE_STATE) BattProfileStatus.eProfileState;
      Status |= ChargerLib_GetBatteryStatus((chargerlib_batt_status_info*)&CurrentBatteryStatus);
      if(EFI_SUCCESS != Status )
      {
        CHARGER_DEBUG(( EFI_D_WARN, "QcomChargerDxe:: %a Get Battery Status Error = %r.\r\n", __FUNCTION__, Status));
        return Status;
      }
      pChargerActionInfo->BattStsInfo = CurrentBatteryStatus;
      /* Return same action for both profile state as FG would internally handle profile load or restart */
      *pActionType = QCOM_CHARGER_PLATFORM_ACTION_PROFILE_LOAD;
      switch(BattProfileStatus.eProfileState)
      {
        case PM_FG_BATT_PROFILE_LOAD:
          if(gChargerPlatformCfgData.DispSignOfLifeMaxThresholdMv == 0)
          {
            gChargerPlatformCfgData.DispSignOfLifeMaxThresholdMv  = QCOM_CHARGER_LOW_THERSHOLD_VBAT;
          }
          pChargerActionInfo->DispSignOfLifeMaxThresholdMv = gChargerPlatformCfgData.DispSignOfLifeMaxThresholdMv + QCOM_CHARGER_VBAT_ERROR_MARGIN;
          if(ErrorType == CHARGERLIB_CHARGING_ERROR_CHARGING_SOURCE_NOT_DETECTED)
            pChargerActionInfo->bChargerSrcPresent = FALSE;
          else
            pChargerActionInfo->bChargerSrcPresent = TRUE;
          /*Disable Charging to get accurate VBAT reading */
          Status |= ChargerLib_ChargerEnable(FALSE);

          /* Not enabling charging since charger app does not know if charging needs to enabled or not at this stage */
          /* Status |= ChargerLib_ChargerEnable(TRUE); */
          break;
          case PM_FG_BATT_PROFILE_RESTART:
            /* Restart FG if needed */
            /* PrevChargerAction = *pActionType = QCOM_CHARGER_PLATFORM_ACTION_PROFILE_LOAD; */
          break;
          default:
          break;
      }
    }
    else
    {
      CHARGER_DEBUG(( EFI_D_WARN, "QcomChargerDxe:: %a eProfileState = %d.Charger Lib Error = %d \r\n", __FUNCTION__, BattProfileStatus.eProfileState, ErrorType));
    }
  }
  else
  {
    CHARGER_DEBUG(( EFI_D_WARN, "QcomChargerDxe:: %a _GetBatteryProfileStatus/ChargerLib_GetErrors Error = %r.\r\n", __FUNCTION__, Status));
    Status = EFI_SUCCESS; /* Not an error to stop boot */
  }
  
  return Status;
}

EFI_STATUS ChargerPlatform_CheckIfOkToBoot
(
  QCOM_CHARGER_PLATFORM_ACTION_TYPE *pActionType, 
  QCOM_CHARGER_PLATFORM_ACTION_INFO  ChargerActionInfo, 
  QCOM_CHARGER_BATT_STATUS_INFO      CurrentBatteryStatus
)
{
  switch(gChargerPlatformCfgData.SocBasedBoot)
  {
    case FALSE:
      if (gChargerPlatformCfgData.WiPowerCfgData.WipowerEnabled && 
         (QCOM_CHARGER_PLATFORM_CHARGER_ATTACHED_DCIN == ChargerActionInfo.ChargerAttached))
      {
        if (CurrentBatteryStatus.BatteryVoltage >= gChargerPlatformCfgData.WiPowerCfgData.WipowerBootThreshold)
        {
          *pActionType = QCOM_CHARGER_PLATFORM_ACTION_GOOD_TO_BOOT;
          CHARGER_DEBUG((EFI_D_WARN, "QcomChargerDxe:: %a Good To Boot To HLOS BatteryVoltage= %d wipower threshold = %d \r\n",
            __FUNCTION__, CurrentBatteryStatus.BatteryVoltage, gChargerPlatformCfgData.WiPowerCfgData.WipowerBootThreshold));
        }
      }
      else if (CurrentBatteryStatus.BatteryVoltage >= gThresholdVbatt)
      {
        *pActionType = QCOM_CHARGER_PLATFORM_ACTION_GOOD_TO_BOOT;
         CHARGER_DEBUG(( EFI_D_WARN, "QcomChargerDxe:: %a Good To Boot To HLOS BatteryVoltage= %d gThresholdVbatt = %d \r\n",
                        __FUNCTION__, CurrentBatteryStatus.BatteryVoltage, gThresholdVbatt));
      }
      else
      { /* TBD comment out */
        CHARGER_DEBUG(( EFI_D_WARN, "QcomChargerDxe:: %a NOT Enough BatteryVoltage To Boot = %d gThresholdVbatt = %d \r\n",
                        __FUNCTION__, CurrentBatteryStatus.BatteryVoltage, gThresholdVbatt));
      }
      break;

    case TRUE:
      if(CurrentBatteryStatus.StateOfCharge >= gThresholdSoc)
      {
        *pActionType = QCOM_CHARGER_PLATFORM_ACTION_GOOD_TO_BOOT;
        CHARGER_DEBUG(( EFI_D_WARN, "QcomChargerDxe:: %a Good To Boot To HLOS StateOfCharge= %d gThresholdSoc = %d \r\n",
                       __FUNCTION__, CurrentBatteryStatus.StateOfCharge, gThresholdSoc));
      }
      else
      { /* TBD comment out */
        CHARGER_DEBUG(( EFI_D_WARN, "QcomChargerDxe:: %a Not Enough StateOfCharge= %d To Boot gThresholdSoc = %d \r\n",
                       __FUNCTION__, CurrentBatteryStatus.StateOfCharge, gThresholdSoc));
      }
    break;
    default:
    break;
  }
  
  return EFI_SUCCESS;
}


