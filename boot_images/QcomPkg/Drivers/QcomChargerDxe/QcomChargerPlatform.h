/*
This file is for LA vbatt based charging in UEFI, it initialize ChargerLib 
to use HW Jeita and implement the function to determine if the conditions to boot to HLOS are met.
*/
/** 
  @file  QcomChargerPlatform.h
  @brief Charger Vbatt based threshold charging UEFI Driver definitions.
         It initializes ChargerLibCommon, initializes HW Jeita 
         and implement the function to determine if the conditions to boot to HLOS are met.
*/
/*=============================================================================
  Copyright (c) 2016-2017 Qualcomm Technologies, Incorporated.
  All rights reserved.
  Qualcomm Technologies, Confidential and Proprietary.
=============================================================================*/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 01/17/17   va      Adding Rconn configuration for considering compensation
 01/10/17   cs      add config to enable/disable INOV
 11/10/16   va      Adding Config VBtEmpty threshold
 10/19/16   sm      Removed EnableHvdcp cfg param from QCOM_CHARGER_PLATFORM_SCHG_CFGDATA_TYPE struct
 10/06/16   cs      configure batt therm/aux therm bias wait 
 09/13/16   sm      Removed unused config parameters from QCOM_CHARGER_PLATFORM_SCHG_CFGDATA_TYPE
                    and QCOM_CHARGER_PLATFORM_CFGDATA_TYPE structs
 09/06/16   cs      wipower changes to remove 3.5 sec, not suspend DCIn
 08/05/16   va      Adding Charger led indication support
 07/26/16   va      Restarting FG Changes on warm boot 
 07/15/16   cs      Adding Wipower support
 06/23/16   va      Adding Action Info for taking Action
 06/23/16   sm      Added EnableHvdcp config parameter in QCOM_CHARGER_PLATFORM_SCHG_CFGDATA_TYPE
 06/23/16   va      Adding support for Charger Fg Peripheral dumps
 06/14/16   va      Adding File log support to Charger App
 06/09/16   sm      Added SupportHostMode in QCOM_CHARGER_PLATFORM_SCHG_CFGDATA_TYPE
 05/31/16   va      Adding Battery profile load feature
 05/10/16   sm      Added ChargerPlatform_GetConfigData()
 04/26/16   va      Adding parameters for Aux Coffes, SkinHot and Charger Hot settings
 04/21/16   sm      Added EnableChargerWdog in QCOM_CHARGER_PLATFORM_CFGDATA_TYPE struct
 04/12/16   sm      Editted elements in BATTID_CFGDATA_TYPE Struct
 03/28/16   va      Adding Jeita Compensation and Consolidating config data into one struct 
 03/21/16   va      Remove dummy configs and add battery missing config
 01/27/16   sm      Initial revision

=============================================================================*/

#ifndef __QCOMCHARGERPLATFORM_H__ 
#define __QCOMCHARGERPLATFORM_H__

#include <api/systemdrivers/charger/ChargerLibCommon.h>

/*===========================================================================
MACRO DEFINITIONS
===========================================================================*/

#define QCOM_CHG_WDOG_DISABLE               0
#define QCOM_CHG_WDOG_DISABLE_ON_EXIT       1
#define QCOM_CHG_WDOG_LEAVE_ENABLED_ON_EXIT 2

/*===========================================================================
TYPE DEFINITIONS
===========================================================================*/
typedef enum
{
  QCOM_CHARGER_PLATFORM_STATUS_GOOD_TO_BOOT = 0,
  /**< Device is good to boot to HLOS */
  QCOM_CHARGER_PLATFORM_STATUS_CHARGING,
  /**< Charging is on-going */
  QCOM_CHARGER_PLATFORM_STATUS_ERROR,
  /**< Error occurred */
  QCOM_CHARGER_PLATFORM_STATUS_PROFILE_LOAD,
  /**< Profile load is needed  */
  QCOM_CHARGER_PLATFORM_STATUS_DEBUG_BOARD_GOOD_TO_BOOT,
  /**< Boot to HLOS */
  QCOM_CHARGER_PLATFORM_STATUS_INVALID,
  /**< Error occurred */
}QCOM_CHARGER_PLATFORM_STATUS_TYPE;

typedef enum
{
  QCOM_CHARGER_PLATFORM_ACTION_CONTINUE,
  /**< Continue charging */
  QCOM_CHARGER_PLATFORM_ACTION_START_CHARGING,
  /**< Start Charging */
  QCOM_CHARGER_PLATFORM_ACTION_STOP_CHARGING,
  /**<  Stop Charging */
  QCOM_CHARGER_PLATFORM_ACTION_GOOD_TO_BOOT,
  /**< Boot to HLOS */
  QCOM_CHARGER_PLATFORM_ACTION_CRITICAL,
  /**< Action for critical error */
  QCOM_CHARGER_PLATFORM_ACTION_SHUTDOWN,
  /**< Shutdown device */
  QCOM_CHARGER_PLATFORM_ACTION_NO_CHARGE_WAIT,
  /**< Stop charging and wait */
  QCOM_CHARGER_PLATFORM_ACTION_PROFILE_LOAD,
  /**< battery profile load  */
  QCOM_CHARGER_PLATFORM_ACTION_SHUTDOWN_USB_DC_PON_DISABLED,
  /**< Action required for shutdown error */
  QCOM_CHARGER_PLATFORM_ACTION_DEBUG_BOARD_GOOD_TO_BOOT,
  /**< Boot to HLOS */
  /**< Profile load Action */
  QCOM_CHARGER_PLATFORM_ACTION_INVALID,
  /**< Charger Action invalid */
}QCOM_CHARGER_PLATFORM_ACTION_TYPE;

typedef struct
{
  UINT32 BatteryIdTolerance;
  /**< Battery ID Tolerance Percentage */

  UINT32 DebugBoardBatteryIdMin;
  /**<  Debug board Battery ID Range Min */

  UINT32 DebugBoardBatteryIdMax;
  /**<  Debug board Battery ID Range Max */

  UINT32 RegularBatteryIdMin;
  /**< Regular Battery ID Range Min */

  UINT32 RegularBatteryIdMax;
  /**<  Regular Battery ID Range Max */

  UINT32 SmartBatteryIdMin;
  /**< Smart Battery ID Range Min */

  UINT32 SmartBatteryIdMax;
  /**<  Smart Battery ID Range Max */

}QCOM_CHARGER_PLATFORM_BATTID_CFGDATA_TYPE;


typedef struct 
{
  BOOLEAN  ProgramAuxThermCoeffs;
  /**<  Enables Aux therm coeffs to be programmed via configs instead of profiles */

  INT32   AuxThermC1;
  /**<  Battery Aux therm coeffs*/

  INT32   AuxThermC2;
  /**<  Battery Aux therm coeffs*/

  INT32   AuxThermC3;
  /**<  Battery Aux therm coeffs*/

  INT32   AuxThermHalfRangeInC;
  /**<  Battery Aux therm Range Ratio in C*/

}QCOM_CHARGER_PLATFORM_FG_CFGDATA_AUX_THERM_COEFFS;

typedef struct 
{
  BOOLEAN  ProgramBattThermCoeffs;
  /**<  Enables Batt therm coeffs to be programmed via configs instead of profiles */

  INT32   BattThermC1;
  /**<  Battery Batt therm coeffs*/

  INT32   BattThermC2;
  /**<  Battery Batt therm coeffs*/

  INT32   BattThermC3;
  /**<  Battery Batt therm coeffs*/

  INT32   BattThermHalfRangeInC;
  /**<  Batt therm Range Ratio in C*/ 

}QCOM_CHARGER_PLATFORM_FG_CFGDATABATT_THERM_COEFFS;

typedef struct 
{
  BOOLEAN  ProgramSkinAndChargerHotThreshold;
  /**<  Enables Pmic Skin and Charger Hot Threshols to be programmed via configs instead of profiles */
  INT32   DeviceSkinHotInC;
  /**<  Device Skin hot */
  INT32   DeviceSkinTooHotInC;
  /**<  Device Skin too hot */
  INT32   ChargerHotInC;
  /**<  Charger Hot Threshold*/
  INT32   ChargerTooHotInC;
  /**<  Charger too Hot Threshold*/

}QCOM_CHARGER_PLATFORM_FG_CFGDATA_SKIN_CHARGERHOT_THRESHOLD;

typedef struct 
{
  INT32    JeitaCriticalTempLowLimit;
  /**< Lower limit of Batery temperature value to perform AFP*/

  INT32    JeitaHardColdLimit; // put all variable for error in one struct..phase 2
  /**< Lower limit of Batery temperature value to stop charging*/

  INT32    JeitaSoftColdLimit;
  /**< Lower limit of Batery temperature value to lower charging parameters*/

  INT32    JeitaSoftHotLimit;
  /**< Upper limit of Batery temperature value to lower charging parameters*/

  INT32    JeitaHardHotLimit;
  /**< Upper limit of Batery temperature value to stop charging*/

  INT32    JeitaCriticalTempHighLimit;
  /**< Upper limit of Batery temperature value to perform AFP*/
}QCOM_CHARGER_PLATFORM_FG_CFGDATA_HW_JEITA_THRESHOLD;

typedef struct 
{
  BOOLEAN  DumpSram;
  /**< Dump SRAM contents */
  UINT32   DumpSramStartAddr;
  /**< #SRAM Block    SRAM Address
    #dump SRAM Start and End Address in Hex Format*/
  UINT32   DumpSramEndAddr;
  /**<  End Address */
  UINT32   DumpSramDuration;
  /**<  dump SRAM contents timer Duration in s */
}QCOM_CHARGER_PLATFORM_FG_SRAM_DEBUG_CFGS;

typedef struct
{
  UINT32 BiasWait;
  BOOLEAN GroundSel;
}QCOM_CHARGER_PLATFORM_FG_THERM_CONFIG;

/*EFI_CHARGER_FG_CFGDATA_TYPE*/
typedef struct
{

  UINT32   ChargingTermCurrent;
  /**<  Charging termination current*/

  UINT32   BattMissingCfg;
  /**<  Battery Missing Config Param*/

  BOOLEAN  FgCondRestart;
  /**<  FG Conditional Restart on reset */

  UINT32   VBattEstDiffThreshold;
  /**<  FG Fuel Gauge Voltage Battery Threshold difference to decide FG Restart condition at FG Algo start */

  UINT32   RestartFgInactiveHrs;
  /**<Force FG to restart after device being inactive for RestartFgInactiveHrs hours */

  BOOLEAN  LoadBatteryProfile;
  /**<  Load Fuel Gauge Battery Profile profile for SOC estimation and accuracy */

  UINT32   VBtEmpty;
  /**<  VBat Empty threshold for empty interrupt */

  QCOM_CHARGER_PLATFORM_FG_CFGDATA_AUX_THERM_COEFFS          AuxThermCoeffs;
  /**<  Battery Aux Therm Coffes*/

  QCOM_CHARGER_PLATFORM_FG_CFGDATA_HW_JEITA_THRESHOLD        HwJeitaThreshold;
  /**<  HW Jeita Thresholds used when HW Jeita is enabled */

  QCOM_CHARGER_PLATFORM_FG_CFGDATA_SKIN_CHARGERHOT_THRESHOLD SkinAndChargerHotThreshold;
  /**<  Battery Pmic Skin and Charger Hot Threshols */

  QCOM_CHARGER_PLATFORM_FG_SRAM_DEBUG_CFGS                   FgSramDbgCfgs;
  /**<  FG SRAM Debug Cfgs */

  QCOM_CHARGER_PLATFORM_FG_THERM_CONFIG            FgBattThermCfg;
  /**<  batt therm configs */

  QCOM_CHARGER_PLATFORM_FG_THERM_CONFIG            FgAuxThermCfg;
  /**<  aux therm configs */

  QCOM_CHARGER_PLATFORM_FG_CFGDATABATT_THERM_COEFFS           FgBattThermCoffs;
    /**<  Battery Batt Therm Coffes*/

  INT32 RconnComp;
  /**<  Rconn compensation */
}QCOM_CHARGER_PLATFORM_FG_CFGDATA_TYPE;

typedef struct
{
  UINT32 ChargingTermCurrent;
  /**<  Charging termination current*/

  UINT32   ChgFccMax; 
  /**< Value of FCC_MAX in mA */

  UINT32   JeitaCcCompCfg;
  /**< JEITA Charge Current Compensation when in battery temperature soft-limit in mA */
 
  UINT32   JeitaFvCompCfg;
  /**< JEITA Float Voltage Compensation when in battery temperature soft-limit in mA */
  
  UINT32  ChgFvMax;
  /**< Maximum Float Voltage */

  BOOLEAN JeitaSoftColdFvCompEnable;
  /**<Enable/Disable Float Voltage compensation during soft cold*/

  BOOLEAN JeitaSoftHotFvCompEnable;
  /**<Enable/Disable Float Voltage compensation during soft hot*/

  BOOLEAN JeitaSoftColdCcCompEnable;
  /**<Enable/Disable Charge Current compensation during soft cold*/

  BOOLEAN JeitaSoftHotCcCompEnable;
  /**<Enable/Disable Charge Current compensation during soft cold*/

  BOOLEAN EnableSkinTempINov;
  /**<Enable/Disable using skin temp for charging thermal imitiageion*/

  BOOLEAN EnableDieTempINov;
  /**<Enable/Disable using die temp for thermal mitigation*/

  BOOLEAN EnableDieTempCompINov;
  /**<Enable/Disable using die temp comparator for thermal mitigation*/

}QCOM_CHARGER_PLATFORM_SCHG_CFGDATA_TYPE;


typedef struct {

  BOOLEAN  PrintChargerAppDbgMsgToFile;
  /**< Flag to Enable/Disable Charger debug messages to File.  */

  BOOLEAN  PrintChargerAppDbgMsg;
  /**< Flag to Enable/Disable Charger debug messages.  */

  BOOLEAN   EnableChargerFgDump;
  /**< Flag to Enable/Disable Charger FG periperal debugs*/

  /* add other debug config here*/

}QCOM_CHARGER_PLATFORM_DEBUG_CFGDATA_TYPE;

/**
  Thermal Config Data.
*/
typedef struct 
{
  INT32 TsensHighTemp;
  /**< High Temperature */

  INT32 TsensExtremeTemp;
  /**< High Temperature for AFP */

  INT32 TsensLowTemp;
  /**< Low Temperature for thermal wait */

  INT32 TsensTimeoutMins;
  /**< Give up time in thermal wait for AFP */
}QCOM_CHARGER_PLATFORM_THERMAL_CFGDATA_TYPE;


typedef struct
{
    BOOLEAN WipowerEnabled;
    /**< if wipower is enabled or not */

    UINT32  WipowerBootThreshold;
    /**< boot up threshold for wipower charging */

    BOOLEAN DCINDisableOnExit;
    /**< suspend dcin or not */

}QCOM_CHARGER_PLATFORM_WIPOWER_CFGDATA_TYPE;

typedef struct {
  UINT32   CfgVersion;
  /**< Version number for CFG file*/

  BOOLEAN  FullBattChargingEnabled;
  /**<  Enable full battery charging  */

  UINT32   BootToHLOSThresholdInMv;
  /**<Battery voltage at which device will boot to HLOS if debug board or unknown battery detected */

  UINT32   BootToHLOSThresholdInSOC;
  /**<Battery SOC at which device will boot to HLOS */

  BOOLEAN  SocBasedBoot;
  /**< Use Battery SOC or voltage threshold as charging criteria */

  BOOLEAN  NoChargeAndWait;
  /**< Disable charging and wait if temp outside charging range.*/

  UINT32   BattVoltLimHighDelta;
  /**< Max Value for battery voltage in mV for WP Platform*/ 

  UINT32   EmergencyShutdownVbatt;
  /**< Lowest Voltage at which device should shutdown gracefully */

  UINT32   UnknownBatteryBehavior;
  /**<Shutdown device upon unknown battery detection */
  /**< 0: Shuts down device, 1: Boot to HLOS if battery more than threshold else shutdown
       2: Conservative Charging 3: Regular charging */

  UINT32   DebugBoardBehavior;
  /**< 0: Show low battery icon, disable PON1/USBIN trigger to prevent reboot and shutdown
       1: Show low battery icon and stay on until device is turned off by user. */

  UINT32  EnableChargerWdog;
  /**< TRUE: Enable watchdog when charging is enabled
       FALSE: Keep watchdog disabled when charging is enabled */

  UINT32   DispSignOfLifeMaxThresholdMv;
  /**< battery Threshold to display */

  BOOLEAN  SWThermalMitigationEnable;
  /**<  Enable SW thermal mitigation while charging  */

  UINT32   ChargerLedConfig;
  /**<  Led Toggle Config for charging status indication
  0 = Disable 1 = solid red during charging 2 = led blink during charging */

  UINT32 ConservChgFvDelta;
  /**< Voltage (in mV) to be reduced from FV_MAX during conservative charging */

  QCOM_CHARGER_PLATFORM_SCHG_CFGDATA_TYPE   SchgCfgData;

  QCOM_CHARGER_PLATFORM_FG_CFGDATA_TYPE     FgCfgData;

  QCOM_CHARGER_PLATFORM_DEBUG_CFGDATA_TYPE  DbgCfgData;

  QCOM_CHARGER_PLATFORM_BATTID_CFGDATA_TYPE BattIdCfgData;

  QCOM_CHARGER_PLATFORM_THERMAL_CFGDATA_TYPE     ThermalCfgData;

  QCOM_CHARGER_PLATFORM_WIPOWER_CFGDATA_TYPE     WiPowerCfgData;

} QCOM_CHARGER_PLATFORM_CFGDATA_TYPE;


typedef struct 
{
  UINT8 *pFileBuffer;
  UINTN  DataSize;
}QCOM_CHARGER_PLATFORM_BATT_PROFILE_DATA;

typedef enum
{
  QCOM_CHARGER_PLATFORM_PROFILE_LOAD,
  QCOM_CHARGER_PLATFORM_PROFILE_RESTART,
  QCOM_CHARGER_PLATFORM_PROFILE_INVALID
}QCOM_CHARGER_PLATFORM_BATT_PROFILE_STATE;

typedef struct 
{
  /* Enum for profile load/restart state */
  QCOM_CHARGER_PLATFORM_BATT_PROFILE_STATE eProfileState;
}QCOM_CHARGER_PLATFORM_BATT_PROFILE_STATUS;

typedef struct
{
  UINT32 StateOfCharge;
  INT32  ChargeCurrent;
  INT32  BatteryVoltage;
  INT32  BatteryTemperature;
}QCOM_CHARGER_BATT_STATUS_INFO;

typedef enum
{
  QCOM_CHARGER_PLATFORM_CHARGING_LED_OFF,
  QCOM_CHARGER_PLATFORM_CHARGING_LED_ON,
  QCOM_CHARGER_PLATFORM_CHARGING_LED_TOGGLE,
  QCOM_CHARGER_PLATFORM_CHARGING_LED_INVALID
}QCOM_CHARGER_PLATFORM_CHARGING_LED_CONFIG_TYPE;

typedef enum 
{
   QCOM_CHARGER_PLATFORM_CHARGER_ATTACHED_NONE,    /**< No charger. */
   QCOM_CHARGER_PLATFORM_CHARGER_ATTACHED_BATT,    /**< Battery. */
   QCOM_CHARGER_PLATFORM_CHARGER_ATTACHED_USB,     /**< USB path. */
   QCOM_CHARGER_PLATFORM_CHARGER_ATTACHED_DCIN,    /**< DCIN path. */
}QCOM_CHARGER_PLATFORM_CHARGER_ATTACHED_TYPE;

typedef struct 
{
  BOOLEAN bChargerSrcPresent;
  UINT32  DispSignOfLifeMaxThresholdMv;
  QCOM_CHARGER_BATT_STATUS_INFO BattStsInfo;
  CHARGERLIB_ATTACHED_CHGR_TYPE ChargerAttached;
  QCOM_CHARGER_PLATFORM_BATT_PROFILE_STATUS ProfState;
  QCOM_CHARGER_PLATFORM_CHARGING_LED_CONFIG_TYPE LedConfigType;
}QCOM_CHARGER_PLATFORM_ACTION_INFO;

typedef struct
{
  /*Charger Log File Handled */
  VOID      *gChargerLogHandle;
  BOOLEAN    bPrintChargerAppDbgMsg;
  BOOLEAN    bPrintChargerAppDbgMsgToFile;
}QCOM_CHARGER_PLATFORM_LOG_INFO;

typedef enum
{
  QCOM_CHARGER_PLATFORM_CHG_WDOG_DISABLE,
  QCOM_CHARGER_PLATFORM_CHG_WDOG_DISABLE_ON_EXIT,
  QCOM_CHARGER_PLATFORM_CHG_WDOG_LEAVE_ENABLED_ON_EXIT,
  QCOM_CHARGER_PLATFORM_CHG_WDOG_INVALID
}QCOM_CHARGER_PLATFORM_CHG_WDOG_CONFIG_TYPE;

/** @} */ /* end_addtogroup efi_qcom_platform_cfg_data_types */

/*===========================================================================
  FUNCTION DEFINITIONS
===========================================================================*/
EFI_STATUS ChargerPlatform_Init( VOID );

EFI_STATUS ChargerPlatform_GetChargingAction(QCOM_CHARGER_PLATFORM_ACTION_TYPE *pActionType, QCOM_CHARGER_PLATFORM_ACTION_INFO *pChargerActionInfo);

EFI_STATUS ChargerPlatform_TakeAction(QCOM_CHARGER_PLATFORM_ACTION_TYPE ChargingAction, CONST QCOM_CHARGER_PLATFORM_ACTION_INFO *pChargerActionInfo);

VOID ChargerPlatform_ReadCfgParams( UINT8* Section, UINT8* Key, UINT8* Value);

EFI_STATUS ChargerPlatform_GetConfigData(QCOM_CHARGER_PLATFORM_CFGDATA_TYPE *pChargerPlatformCfgData);

EFI_STATUS ChargerPlatformFile_GetLogInfo(QCOM_CHARGER_PLATFORM_LOG_INFO *pFileLogInfo);

#endif  /* __CHARGERPLATFORM_H__ */

