/*! @file PmicWledProtocol.c 

 *  PMIC-WLED MODULE RELATED DECLARATION
 *  This file contains functions and variable declarations to support 
 *  the PMIC WLED module.
 *
 * Copyright (c) 2012 - 2016 Qualcomm Technologies Incorporated.  All Rights Reserved. 
 * Qualcomm Technologies Proprietary and Confidential.
 */

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
11/03/16   al      Adding newer sequence for enabling and disabling WLED to clear OVP bit 
10/19/16   al      Adding APIs for configuring SWIRE default value
28/05/14   al      Adding APIs for configuring various AMOLED param.
07/01/14   al      Adding get_status 
06/09/14   al      Arch update
05/19/14   al    Added initializers 
04/29/14   al    Added for AMOLED. PSM, PFM 
13/12/13   aa    PmicLib Dec Addition
09/17/13   al	   Added workaround for disabling WLED MODULE
03/15/13   al	   Updating api names
10/25/12   al    File renamed 
08/15/12   al	   Changed according to naming conventions
07/27/12   al	   Commented out not required for 8974 and compiling for 8960
03/05/12   sm    Changes parameters for EFI_PM_WLED_ENABLE_SYNC
02/08/12   sm    New file.
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES FOR MODULE

===========================================================================*/

#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>

#include "pm_uefi.h"
#include "pm_wled.h"
#include "pm_version.h"

#include <Protocol/EFIPmicWled.h>


/*===========================================================================
                  LOCAL STRUCTURE DEFINITIONS
===========================================================================*/

/*===========================================================================

                  LOCAL VARIABLE DEFINITIONS

===========================================================================*/


/*===========================================================================

                  STATIC FUNCTION DECLARATIONS

===========================================================================*/
#define TEN_MILLI_SEC 10000

/*===========================================================================

                  EXTERNAL FUNCTION DECLARATIONS

===========================================================================*/

/**
  EFI_PmEnableWled

  @brief
  Enables WLED module
 */
EFI_STATUS
EFIAPI
EFI_PmEnableWled
(
   IN UINT32 PmicDeviceIndex,
   IN UINT32 ResourceIndex,
   IN BOOLEAN  Enable
   )
{
  pm_err_flag_type               errFlag    = PM_ERR_FLAG__SUCCESS;
  /* while enabling WLED: disable OVP, enable WLED, wait 10miilisec and then enable OVP. While disabling WLED: disable WLED and keep OVP disabled.*/
  if (Enable)
  {
    errFlag |= pm_wled_irq_enable(PmicDeviceIndex, PM_WLED_IRQ_OVP_FAULT, FALSE);
    errFlag |= pm_wled_enable_module(PmicDeviceIndex, ResourceIndex, Enable);
    gBS->Stall(TEN_MILLI_SEC);
    errFlag |= pm_wled_irq_enable(PmicDeviceIndex, PM_WLED_IRQ_OVP_FAULT, TRUE);
  }
  else
  {
  errFlag = pm_wled_enable_module(PmicDeviceIndex, ResourceIndex, Enable);
    errFlag |= pm_wled_irq_enable(PmicDeviceIndex, PM_WLED_IRQ_OVP_FAULT, FALSE);
  }

  if (PM_ERR_FLAG__SUCCESS != errFlag)
  {
    return EFI_DEVICE_ERROR;
  }

  return EFI_SUCCESS;
}




/**
  EFI_PmWledEnableModulator

  @brief
  Enables digital modulator generator and modulator input
  for each current sink.
 */
EFI_STATUS
EFIAPI
EFI_PmWledEnableModulator
(
   IN UINT32                PmicDeviceIndex,
   IN EFI_PM_WLED_LED_TYPE  LedType,
   IN BOOLEAN               Enable
   )
{
  pm_err_flag_type  errFlag  = PM_ERR_FLAG__SUCCESS;

  errFlag = pm_wled_enable_modulator(PmicDeviceIndex, (pm_wled_led_type)LedType, Enable);

  if (errFlag != PM_ERR_FLAG__SUCCESS)
  {
    return EFI_DEVICE_ERROR;
  }

  return EFI_SUCCESS;
}

/**
  EFI_PmWledEnableCurrentSink

  @brief
  Enables control for LED current sink outputs
 */
EFI_STATUS
EFIAPI
EFI_PmWledEnableCurrentSink
(
   IN UINT32 PmicDeviceIndex,
   IN EFI_PM_WLED_LED_TYPE   LedType
   )
{
  pm_err_flag_type  errFlag  = PM_ERR_FLAG__SUCCESS;

  errFlag = pm_wled_enable_current_sink(PmicDeviceIndex, (pm_wled_led_type)LedType);

  if (errFlag != PM_ERR_FLAG__SUCCESS)
  {
    return EFI_DEVICE_ERROR;
  }

  return EFI_SUCCESS;
}

/**
  EFI_PmWledSetDelay

  @brief
  Sets delay for after the LED sync write
 */
EFI_STATUS
EFIAPI
EFI_PmWledSetDelay
(
   IN UINT32                 PmicDeviceIndex,
   IN EFI_PM_WLED_LED_TYPE   LedType,
   IN UINT32                 DelayUSec
   )
{
  pm_err_flag_type  errFlag  = PM_ERR_FLAG__SUCCESS;

  errFlag = pm_wled_set_sync_delay(PmicDeviceIndex, (pm_wled_led_type)LedType, (uint32)DelayUSec);

  if (errFlag != PM_ERR_FLAG__SUCCESS)
  {
    return EFI_DEVICE_ERROR;
  }

  return EFI_SUCCESS;
}

/**
  EFI_PmWledSetCurrentSink

  @brief
  Selects LED current sink number 
 */
EFI_STATUS
EFIAPI
EFI_PmWledSetCurrentSink
(
   IN UINT32                 PmicDeviceIndex,
   IN EFI_PM_WLED_LED_TYPE   LedType,
   IN UINT32                 CurrentMilliAmp
   )
{
  pm_err_flag_type  errFlag  = PM_ERR_FLAG__SUCCESS;

  errFlag = pm_wled_set_current_sink(PmicDeviceIndex, (pm_wled_led_type)LedType, (uint32)CurrentMilliAmp);

  if (errFlag != PM_ERR_FLAG__SUCCESS)
  {
    return EFI_DEVICE_ERROR;
  }

  return EFI_SUCCESS;
}

/**
  EFI_PmWledEnableExtPwm

  @brief
  Enables use of pwm_in_ext as pwm dimming control
 */
EFI_STATUS
EFIAPI
EFI_PmWledEnableExtPwm
(
   IN UINT32                PmicDeviceIndex,
   IN EFI_PM_WLED_LED_TYPE  LedType,
   IN BOOLEAN               Enable
   )
{
  pm_err_flag_type  errFlag  = PM_ERR_FLAG__SUCCESS;

  errFlag = pm_wled_en_ext_pwm(PmicDeviceIndex, (pm_wled_led_type)LedType, Enable);

  if (errFlag != PM_ERR_FLAG__SUCCESS)
  {
    return EFI_DEVICE_ERROR;
  }

  return EFI_SUCCESS;
}


/**
  EFI_PmWledSetLedDutyCycle

  @brief
  Sets 12b duty cycle control for indicated LED digital 
  modulator control.
 */
EFI_STATUS
EFIAPI
EFI_PmWledSetLedDutyCycle
(
   IN UINT32                 PmicDeviceIndex,
   IN EFI_PM_WLED_LED_TYPE   LedType,
   IN UINT16                 Data
   )
{
  pm_err_flag_type  errFlag  = PM_ERR_FLAG__SUCCESS;

  errFlag = pm_wled_set_led_duty_cycle(PmicDeviceIndex, (pm_wled_led_type)LedType, (uint16)Data);

  if (errFlag != PM_ERR_FLAG__SUCCESS)
  {
    return EFI_DEVICE_ERROR;
  }

  return EFI_SUCCESS;
}

/**
  EFI_PmWledSetSlopeComp

  @brief
  Sets slope compensation adjustment for inductor 
  component value.
 */
EFI_STATUS
EFIAPI
EFI_PmWledSetSlopeComp
(
   IN UINT32 PmicDeviceIndex,
   IN UINT32 ResourceIndex,
   IN UINT32 SlopeComp
   )
{
  pm_err_flag_type  errFlag  = PM_ERR_FLAG__SUCCESS;

  errFlag = pm_wled_set_slope_comp(PmicDeviceIndex, ResourceIndex, (uint32)SlopeComp);

  if (errFlag != PM_ERR_FLAG__SUCCESS)
  {
    return EFI_DEVICE_ERROR;
  }

  return EFI_SUCCESS;
}

/**
  EFI_PmWledEnableCabc

  @brief
  Enables content adaptive backlight control
 */
EFI_STATUS
EFIAPI
EFI_PmWledEnableCabc
(
   IN UINT32 PmicDeviceIndex,
   IN EFI_PM_WLED_LED_TYPE    LedType
   )
{
  pm_err_flag_type  errFlag  = PM_ERR_FLAG__SUCCESS;

  errFlag = pm_wled_en_cabc(PmicDeviceIndex, (pm_wled_led_type)LedType);

  if (errFlag != PM_ERR_FLAG__SUCCESS)
  {
    return EFI_DEVICE_ERROR;
  }

  return EFI_SUCCESS;
}

/**
  EFI_PmWledEnableSync

  @brief
  Enables LED sync
 */
EFI_STATUS
EFIAPI
EFI_PmWledEnableSync
(
   IN UINT32 PmicDeviceIndex,
   IN EFI_PM_WLED_LED_TYPE    LedType,
   IN BOOLEAN                  Enable
   )
{
  pm_err_flag_type  errFlag  = PM_ERR_FLAG__SUCCESS;

  errFlag = pm_wled_en_sync(PmicDeviceIndex, (pm_wled_led_type)LedType, Enable);

  if (errFlag != PM_ERR_FLAG__SUCCESS)
  {
    return EFI_DEVICE_ERROR;
  }

  return EFI_SUCCESS;
}

/**
  EFI_PmWledSelectPwmMode

  @brief
  Selects internal digital modulator type
 */
EFI_STATUS
EFIAPI
EFI_PmWledSelectPwmMode
(
   IN UINT32 PmicDeviceIndex,
   IN UINT32 ResourceIndex,
   IN EFI_PM_WLED_PWM_MODE_TYPE PwmModeType
   )
{
  pm_err_flag_type  errFlag  = PM_ERR_FLAG__SUCCESS;

  //errFlag = pm_wled_sel_pwm_mode(PmicDeviceIndex, ResourceIndex, (pm_wled_pwm_mode_type)PwmModeType);

  if (errFlag != PM_ERR_FLAG__SUCCESS)
  {
    return EFI_DEVICE_ERROR;
  }

  return EFI_SUCCESS;
}

/**
  EFI_PmWledSetBoostMaxDuty

  @brief
  Selects maximum duty cycle control for boost.
 */
EFI_STATUS
EFIAPI
EFI_PmWledSetBoostMaxDuty
(
   IN UINT32 PmicDeviceIndex,
   IN UINT32 ResourceIndex,
   IN EFI_PM_WLED_BST_MAX_DUTY_TYPE    BstMaxDutyType
   )
{
  pm_err_flag_type  errFlag  = PM_ERR_FLAG__SUCCESS;

  errFlag = pm_wled_set_bst_max_duty(PmicDeviceIndex, ResourceIndex, (pm_wled_bst_max_duty_type)BstMaxDutyType);

  if (errFlag != PM_ERR_FLAG__SUCCESS)
  {
    return EFI_DEVICE_ERROR;
  }

  return EFI_SUCCESS;
}

/**
  EFI_PmWledSetFswCtrl

  @brief
  Selects boost switching frequency control
 */
EFI_STATUS
EFIAPI
EFI_PmWledSetFswCtrl
(
   IN UINT32 PmicDeviceIndex,
   IN UINT32 ResourceIndex,
   IN UINT32 FswKhz
   )
{
  pm_err_flag_type  errFlag  = PM_ERR_FLAG__SUCCESS;

  errFlag = pm_wled_set_fsw_ctrl(PmicDeviceIndex, ResourceIndex, (uint32)FswKhz);

  if (errFlag != PM_ERR_FLAG__SUCCESS)
  {
    return EFI_DEVICE_ERROR;
  }

  return EFI_SUCCESS;
}

/**
  EFI_PmWledSetModClkCtrl

  @brief
  Selects digital modulator input clock frequency control
 */
EFI_STATUS
EFIAPI
EFI_PmWledSetModClkCtrl
(
   IN UINT32                    PmicDeviceIndex,
   IN UINT32                    ResourceIndex,
   IN EFI_PM_WLED_MOD_CLK_TYPE  ModClkType
   )
{
  pm_err_flag_type  errFlag  = PM_ERR_FLAG__SUCCESS;

  //errFlag = pm_wled_set_mod_clk_ctrl(PmicDeviceIndex, ResourceIndex,(pm_wled_mode_clk_type)ModClkType);

  if (errFlag != PM_ERR_FLAG__SUCCESS)
  {
    return EFI_DEVICE_ERROR;
  }

  return EFI_SUCCESS;
}

/**
  EFI_PmWledSetModDimMode

  @brief
  Selects modulator dimming mode control
 */
EFI_STATUS
EFIAPI
EFI_PmWledSetModDimMode
(
   IN UINT32 PmicDeviceIndex,
   IN UINT32 ResourceIndex,
   IN EFI_PM_WLED_MOD_DIM_MODE_TYPE    ModDimModeType
   )
{
  pm_err_flag_type  errFlag  = PM_ERR_FLAG__SUCCESS;

  //errFlag = pm_wled_set_mod_dim_mode(PmicDeviceIndex, ResourceIndex,(pm_wled_mode_dim_mode_type)ModDimModeType);

  if (errFlag != PM_ERR_FLAG__SUCCESS)
  {
    return EFI_DEVICE_ERROR;
  }

  return EFI_SUCCESS;
}

/**
  EFI_PmWledSetWarmupDelay

  @brief
  Controls WLED bias generator warm-up time.
 */
EFI_STATUS
EFIAPI
EFI_PmWledSetWarmupDelay
(
   IN UINT32 PmicDeviceIndex,
   IN UINT32 ResourceIndex,
   IN EFI_PM_WLED_WARMUP_DLY_TYPE WarmupDlyType
   )
{
  pm_err_flag_type  errFlag  = PM_ERR_FLAG__SUCCESS;

  errFlag = pm_wled_sel_warmup_dly(PmicDeviceIndex, ResourceIndex, (pm_wled_warmup_dly_type)WarmupDlyType);

  if (errFlag != PM_ERR_FLAG__SUCCESS)
  {
    return EFI_DEVICE_ERROR;
  }

  return EFI_SUCCESS;
}

/**
  EFI_PmWledSetOvpThreshold

  @brief
  Selects OVP threshold
 */
EFI_STATUS
EFIAPI
EFI_PmWledSetOvpThreshold
(
   IN UINT32 PmicDeviceIndex,
   IN UINT32 ResourceIndex,
   IN EFI_PM_WLED_OVP_THRESHOLD_TYPE    OvpThrType
   )
{
  pm_err_flag_type  errFlag  = PM_ERR_FLAG__SUCCESS;

  errFlag = pm_wled_sel_ovp_thr(PmicDeviceIndex, ResourceIndex, (pm_wled_ovp_threshold_type)OvpThrType);

  if (errFlag != PM_ERR_FLAG__SUCCESS)
  {
    return EFI_DEVICE_ERROR;
  }

  return EFI_SUCCESS;
}

/**
  EFI_PmWledSetRampTime

  @brief
  Sets time to ramp Ilim from 0 to 100% of Ilim threshold
  during soft start

 */
EFI_STATUS
EFIAPI
EFI_PmWledSetRampTime
(
   IN UINT32 PmicDeviceIndex,
   IN UINT32 ResourceIndex,
   IN UINT32 TimeMicroSec
   )
{
  pm_err_flag_type  errFlag  = PM_ERR_FLAG__SUCCESS;

  errFlag = pm_wled_set_ramp_time(PmicDeviceIndex, ResourceIndex, (uint32)TimeMicroSec);

  if (errFlag != PM_ERR_FLAG__SUCCESS)
  {
    return EFI_DEVICE_ERROR;
  }

  return EFI_SUCCESS;
}

/**
  EFI_PmWledEnableSoftStart

  @brief
  Enable/disable soft start Ilim ramp after WLED module 
  enable

 */
EFI_STATUS
EFIAPI
EFI_PmWledEnableSoftStart
(
   IN UINT32 PmicDeviceIndex,
   IN UINT32 ResourceIndex,
   IN BOOLEAN Enable
   )
{
  pm_err_flag_type  errFlag  = PM_ERR_FLAG__SUCCESS;

  errFlag = pm_wled_en_soft_start(PmicDeviceIndex, ResourceIndex, Enable);

  if (errFlag != PM_ERR_FLAG__SUCCESS)
  {
    return EFI_DEVICE_ERROR;
  }

  return EFI_SUCCESS;
}

/**
  EFI_PmWledSetBoostIlimit

  @brief
  Selects boost current limit
 */
EFI_STATUS
EFIAPI
EFI_PmWledSetBoostIlimit
(
   IN UINT32 PmicDeviceIndex,
   IN UINT32 ResourceIndex,
   IN EFI_PM_WLED_BST_ILIMIT_TYPE    BstIlimitType
   )
{
  pm_err_flag_type  errFlag  = PM_ERR_FLAG__SUCCESS;

  errFlag = pm_wled_sel_bst_ilimit(PmicDeviceIndex, ResourceIndex, (pm_wled_bst_ilimit_type)BstIlimitType);

  if (errFlag != PM_ERR_FLAG__SUCCESS)
  {
    return EFI_DEVICE_ERROR;
  }

  return EFI_SUCCESS;
}

/**
  EFI_PmWledForceVmin

  @brief
  Forces selection of a LED output as feedback node for 
  the boost

 */
EFI_STATUS
EFIAPI
EFI_PmWledForceVmin
(
   IN UINT32 PmicDeviceIndex,
   IN EFI_PM_WLED_LED_TYPE    LedType
   )
{
  pm_err_flag_type  errFlag  = PM_ERR_FLAG__SUCCESS;

  errFlag = pm_wled_force_vmin(PmicDeviceIndex, (pm_wled_led_type)LedType);

  if (errFlag != PM_ERR_FLAG__SUCCESS)
  {
    return EFI_DEVICE_ERROR;
  }

  return EFI_SUCCESS;
}

/**
  EFI_PmWledSelectSlewRate

  @brief
  Selects slew rate
 */
EFI_STATUS
EFIAPI
EFI_PmWledSelectSlewRate
(
   IN UINT32 PmicDeviceIndex,
   IN UINT32 ResourceIndex,
   IN EFI_PM_WLED_SLEW_RATE_TYPE    SlewRateType
   )
{
  pm_err_flag_type  errFlag  = PM_ERR_FLAG__SUCCESS;

  errFlag = pm_wled_sel_slew_rate(PmicDeviceIndex, (pm_wled_slew_rate_type)SlewRateType);

  if (errFlag != PM_ERR_FLAG__SUCCESS)
  {
    return EFI_DEVICE_ERROR;
  }

  return EFI_SUCCESS;
}

/**
  EFI_PmWledSetAmoledVout

  @brief
  Selects AMOLED VOUT
 */
EFI_STATUS
EFIAPI
EFI_PmWledSetAmoledVout
(
   IN UINT32                       PmicDeviceIndex,
   IN EFI_PM_WLED_AMOLED_CTRL_TYPE VoutCtrl,
   IN UINT32                       AvddMilliVolt
   )
{
  pm_err_flag_type  err_flag  = PM_ERR_FLAG__SUCCESS;

  err_flag =  pm_wled_set_amoled_vout(PmicDeviceIndex, (pm_wled_amoled_ctrl_type)VoutCtrl, AvddMilliVolt);

  if (err_flag != PM_ERR_FLAG__SUCCESS)
  {
    return EFI_DEVICE_ERROR;
  }

  return EFI_SUCCESS;
}

/**
  EFI_PmWledSelectRz

  @brief
  Selects compensation resistor
 */
EFI_STATUS
EFIAPI
EFI_PmWledSelectRz
(
   IN UINT32 PmicDeviceIndex,
   IN UINT32 RzKOhm
   )
{
  pm_err_flag_type  errFlag  = PM_ERR_FLAG__SUCCESS;

  errFlag = pm_wled_sel_rz(PmicDeviceIndex, (uint32)RzKOhm);

  if (errFlag != PM_ERR_FLAG__SUCCESS)
  {
    return EFI_DEVICE_ERROR;
  }

  return EFI_SUCCESS;
}

/**
  EFI_PmWledSelectGm

  @brief
  Selects gm for the gm stage
 */
EFI_STATUS
EFIAPI
EFI_PmWledSelectGm
(
   IN UINT32 PmicDeviceIndex,
   IN UINT32 GmSel
   )
{
  pm_err_flag_type  errFlag  = PM_ERR_FLAG__SUCCESS;

  errFlag = pm_wled_sel_gm(PmicDeviceIndex, (uint32)GmSel);

  if (errFlag != PM_ERR_FLAG__SUCCESS)
  {
    return EFI_DEVICE_ERROR;
  }

  return EFI_SUCCESS;
}

/**
  EFI_PmWledEnableSleepb

  @brief
  Enables sleep
 */
EFI_STATUS
EFIAPI
EFI_PmWledEnableSleepb
(
   IN UINT32 PmicDeviceIndex,
   IN UINT32 ResourceIndex,
   IN BOOLEAN  Enable
   )
{
  pm_err_flag_type  errFlag  = PM_ERR_FLAG__SUCCESS;

  errFlag = pm_wled_en_sleepb(PmicDeviceIndex, ResourceIndex, Enable);

  if (errFlag != PM_ERR_FLAG__SUCCESS)
  {
    return EFI_DEVICE_ERROR;
  }

  return EFI_SUCCESS;
}

/**
  EFI_PmWledSelectVrefCtrl

  @brief
  Selects reference voltage for boost feedback
 */
EFI_STATUS
EFIAPI
EFI_PmWledSelectVrefCtrl
(
   IN UINT32 PmicDeviceIndex,
   IN UINT32 ResourceIndex,
   IN UINT32 MicroVolt
   )
{
  pm_err_flag_type  errFlag  = PM_ERR_FLAG__SUCCESS;

  errFlag = pm_wled_sel_vref_ctrl(PmicDeviceIndex, ResourceIndex, (uint32)MicroVolt);

  if (errFlag != PM_ERR_FLAG__SUCCESS)
  {
    return EFI_DEVICE_ERROR;
  }

  return EFI_SUCCESS;
}


/**
  EFI_PmWledSelectHighPoleCap

  @brief
  Sets high pole capacaitance
 */
EFI_STATUS
EFIAPI
EFI_PmWledSelectHighPoleCap
(
   IN UINT32 PmicDeviceIndex,
   IN UINT32 CpPicoFarad
   )
{
  pm_err_flag_type  errFlag  = PM_ERR_FLAG__SUCCESS;

  errFlag = pm_wled_sel_high_pole_cap(PmicDeviceIndex, (uint32)CpPicoFarad);

  if (errFlag != PM_ERR_FLAG__SUCCESS)
  {
    return EFI_DEVICE_ERROR;
  }

  return EFI_SUCCESS;
}



/**
  EFI_PmWledEnAmoled 
  @brief
  This enables/disables AMOLED
 */
EFI_STATUS
EFIAPI
EFI_PmWledEnAmoled
(
   IN UINT32  PmicDeviceIndex,
   IN BOOLEAN Enable
   )
{
  pm_err_flag_type  errFlag  = PM_ERR_FLAG__SUCCESS;

  errFlag  = pm_wled_en_amoled((uint32)PmicDeviceIndex, (boolean)Enable);

  if (errFlag != PM_ERR_FLAG__SUCCESS)
  {
    return EFI_DEVICE_ERROR;
  }
  return EFI_SUCCESS;
}


/**
  EFI_PmWledConfigPsm 
  @brief
  This configures pulse skipping mode
 */
EFI_STATUS
EFIAPI
EFI_PmWledConfigPsm
(
   IN UINT32  PmicDeviceIndex,
   IN BOOLEAN IsHystLvlHigh,
   IN UINT32  RefVoltageMv,
   IN BOOLEAN PsmEn
   )
{
  pm_err_flag_type  errFlag  = PM_ERR_FLAG__SUCCESS;

  errFlag = pm_wled_config_psm((uint32)PmicDeviceIndex, (boolean)IsHystLvlHigh, (uint32)RefVoltageMv, (boolean)PsmEn);

  if (errFlag != PM_ERR_FLAG__SUCCESS)
  {
    return EFI_DEVICE_ERROR;
  }
  return EFI_SUCCESS;
}



/**
  EFI_PmWledConfigPfm
  @brief
  This configures pulse frequency mode
 */
EFI_STATUS
EFIAPI
EFI_PmWledConfigPfm
(
   IN UINT32  PmicDeviceIndex,
   IN BOOLEAN IsHystLvlHigh,
   IN UINT32  NfetOffTimeNs,
   IN UINT32  ILimitMa,
   IN BOOLEAN PfmEn
   )
{
  pm_err_flag_type  errFlag  = PM_ERR_FLAG__SUCCESS;

  errFlag =  pm_wled_config_pfm((uint32)PmicDeviceIndex, (boolean)IsHystLvlHigh, (uint32)NfetOffTimeNs, (uint32)ILimitMa, (boolean)PfmEn);

  if (errFlag != PM_ERR_FLAG__SUCCESS)
  {
    return EFI_DEVICE_ERROR;
  }
  return EFI_SUCCESS;
}


/**
  EFI_PmWledGetStatus
  @brief
  This reads WLED status
 */
EFI_STATUS
EFIAPI
EFI_PmWledGetStatus
(
   IN UINT32                PmicDeviceIndex,
   EFI_PM_WLED_STATUS_TYPE *WledStatus
   )
{
  pm_err_flag_type  errFlag  = PM_ERR_FLAG__SUCCESS;
  pm_wled_status_type wled_status;

  if (NULL == WledStatus)
  {
    return EFI_DEVICE_ERROR;
  }

  errFlag =  pm_wled_get_status((uint32)PmicDeviceIndex, &wled_status);
  if (errFlag != PM_ERR_FLAG__SUCCESS)
  {
    return EFI_DEVICE_ERROR;
  }
  else
  {
    WledStatus->Led1ModulatorEn          = (BOOLEAN)(wled_status.led1_modulator_enable);
    WledStatus->Led2ModulatorEn          = (BOOLEAN)(wled_status.led2_modulator_enable);
    WledStatus->Led3ModulatorEn          = (BOOLEAN)(wled_status.led3_modulator_enable);
    WledStatus->Led4ModulatorEn          = (BOOLEAN)(wled_status.led4_modulator_enable);

    WledStatus->Led1CurrentSinkEn        = (BOOLEAN)(wled_status.led1_current_sink_enable);
    WledStatus->Led2CurrentSinkEn        = (BOOLEAN)(wled_status.led2_current_sink_enable);
    WledStatus->Led3CurrentSinkEn        = (BOOLEAN)(wled_status.led3_current_sink_enable);
    WledStatus->led4CurrentSinkEn        = (BOOLEAN)(wled_status.led4_current_sink_enable);

    WledStatus->SlopeTrim                = (UINT32)(wled_status.slope_trim);

    WledStatus->ModeClk                  = (EFI_PM_WLED_MOD_CLK_TYPE)(wled_status.mode_clk);
    WledStatus->EnPhaseStagger           = (BOOLEAN)(wled_status.en_phase_stagger);
    WledStatus->AccumClk                 = (EFI_PM_WLED_MOD_CLK_TYPE)(wled_status.accum_clk);
    WledStatus->EnHybridDim              = (BOOLEAN)(wled_status.en_hybrid_dim);
    WledStatus->PwmMode                  = (EFI_PM_WLED_PWM_MODE_TYPE)(wled_status.pwm_mode);
    WledStatus->DimMode                  = (EFI_PM_WLED_MOD_DIM_MODE_TYPE)(wled_status.dim_mode);
    WledStatus->BstMaxDuty               = (EFI_PM_WLED_BST_MAX_DUTY_TYPE)(wled_status.bst_max_duty);
    WledStatus->SetFswCtrl               = (UINT32)(wled_status.set_fsw_ctrl);
    WledStatus->RampTime                 = (UINT32)(wled_status.ramp_time);
    WledStatus->BstIlimit                = (EFI_PM_WLED_BST_ILIMIT_TYPE)(wled_status.bst_ilimit);
    WledStatus->SlewRate                 = (EFI_PM_WLED_SLEW_RATE_TYPE)(wled_status.slew_rate);
    WledStatus->VrefCtrl                 = (UINT32)(wled_status.vref_ctrl);
    WledStatus->WarmupDly                = (EFI_PM_WLED_WARMUP_DLY_TYPE)(wled_status.warmup_dly);
    WledStatus->OvpThr                   = (EFI_PM_WLED_OVP_THRESHOLD_TYPE)(wled_status.ovp_thr);
    WledStatus->Led1FullScaleCurrent     = (UINT32)(wled_status.led1_full_scale_current);
    WledStatus->Led2FullScaleCurrent     = (UINT32)(wled_status.led2_full_scale_current);
    WledStatus->Led3FullScaleCurrent     = (UINT32)(wled_status.led3_full_scale_current);
    WledStatus->Led4FullScaleCurrent     = (UINT32)(wled_status.led4_full_scale_current);
    WledStatus->Led1Brightness           = (UINT32)(wled_status.led1_brightness);
    WledStatus->Led2Brightness           = (UINT32)(wled_status.led2_brightness);
    WledStatus->Led3Brightness           = (UINT32)(wled_status.led3_brightness);
    WledStatus->Led4Brightness           = (UINT32)(wled_status.led4_brightness);
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
EFI_PmWledConfigShortCktProtect
(
  IN UINT32                            PmicDeviceIndex, 
  IN EFI_PM_WLED_SHORT_CKT_CONFIG_TYPE *ShortCktConfig
  )
{
  pm_err_flag_type  err_flag  = PM_ERR_FLAG__SUCCESS;

  if (NULL == ShortCktConfig)
  {
    return EFI_DEVICE_ERROR;
  }
  else
  {
    err_flag = pm_wled_config_short_ckt_protect(PmicDeviceIndex, (pm_wled_short_ckt_config_type*)ShortCktConfig);
  }

  if (err_flag != PM_ERR_FLAG__SUCCESS)
  {
    return EFI_DEVICE_ERROR;
  }
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
EFI_PmWledConfigShSoftStart
(
   IN UINT32                     PmicDeviceIndex, 
   IN EFI_PM_WLED_SH_CONFIG_TYPE ShType, 
   IN BOOLEAN                    Enable
   )
{
  pm_err_flag_type  err_flag  = PM_ERR_FLAG__SUCCESS;

  err_flag = pm_wled_config_sh_soft_start(PmicDeviceIndex, (pm_wled_sh_config_type)ShType, Enable);

  if (err_flag != PM_ERR_FLAG__SUCCESS)
  {
    return EFI_DEVICE_ERROR;
  }
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
EFI_PmWledSetWledDtest
(
    IN UINT32 PmicDeviceIndex, 
    IN UINT32 DtestSetting
    )
{
  pm_err_flag_type  err_flag  = PM_ERR_FLAG__SUCCESS;

  err_flag = pm_wled_set_wled_dtest(PmicDeviceIndex, DtestSetting);

  if (err_flag != PM_ERR_FLAG__SUCCESS)
  {
    return EFI_DEVICE_ERROR;
  }
  return EFI_SUCCESS;
}


/**
  EFI_PmWledSetDormantSwireAvddVolt

  @brief
  Selects AMOLED VOUT
 */
EFI_STATUS
EFIAPI
EFI_PmWledSetDormantSwireAvddVolt
(
   IN UINT32                       PmicDeviceIndex,
   IN UINT32                       AvddMilliVolt
   )
{
  pm_err_flag_type  err_flag  = PM_ERR_FLAG__SUCCESS;
  
  err_flag =  pm_wled_set_dormant_swire_avdd_volt(PmicDeviceIndex, AvddMilliVolt);

  if (err_flag != PM_ERR_FLAG__SUCCESS)
  {
    return EFI_DEVICE_ERROR;
  }

  return EFI_SUCCESS;
}


/**
  PMIC Keypad UEFI Protocol implementation
 */
EFI_QCOM_PMIC_WLED_PROTOCOL PmicWledProtocolImplementation =
{
  PMIC_WLED_REVISION,
  EFI_PmEnableWled,
  EFI_PmWledEnableModulator,
  EFI_PmWledEnableCurrentSink,
  EFI_PmWledSetDelay,
  EFI_PmWledSetCurrentSink,
  EFI_PmWledEnableExtPwm,
  EFI_PmWledSetLedDutyCycle,
  EFI_PmWledSetSlopeComp,
  EFI_PmWledEnableCabc,
  EFI_PmWledEnableSync,
  EFI_PmWledSelectPwmMode,
  EFI_PmWledSetBoostMaxDuty,
  EFI_PmWledSetFswCtrl,
  EFI_PmWledSetModClkCtrl,
  EFI_PmWledSetModDimMode,
  EFI_PmWledSetWarmupDelay,
  EFI_PmWledSetOvpThreshold,
  EFI_PmWledSetRampTime,
  EFI_PmWledEnableSoftStart,
  EFI_PmWledSetBoostIlimit,
  EFI_PmWledForceVmin,
  EFI_PmWledSelectSlewRate,
  EFI_PmWledSetAmoledVout,
  EFI_PmWledSelectRz,
  EFI_PmWledSelectGm,
  EFI_PmWledEnableSleepb,
  EFI_PmWledSelectVrefCtrl,
  EFI_PmWledSelectHighPoleCap,
  EFI_PmWledEnAmoled,
  EFI_PmWledConfigPsm,
  EFI_PmWledConfigPfm,
  EFI_PmWledGetStatus,
  EFI_PmWledConfigShortCktProtect,
  EFI_PmWledConfigShSoftStart,
  EFI_PmWledSetWledDtest,
  EFI_PmWledSetDormantSwireAvddVolt,
}; 
