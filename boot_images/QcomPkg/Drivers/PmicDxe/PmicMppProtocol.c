/*! @file PmicMppProtocol.c 

 *  PMIC-MPP MODULE RELATED DECLARATION
 *  This file contains functions and variable declarations to support 
 *  the PMIC MPP module.
 *
 * Copyright (c) 2011-2014 Qualcomm Technologies, Inc.  All Rights Reserved. 
 * Qualcomm Technologies Proprietary and Confidential.
 */

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
06/09/14   al      Arch update
13/12/13   aa      PmicLib Dec Addition
04/23/13   al      Add ConfigDtestOut
01/29/13   al      Cleaning compiler warnings  
01/22/13   al      Add rt. interrupt  
10/25/12   al      File renamed 
07/27/12   al	     Commenting out not required for 8974 and compiling for 8960
02/24/12   sm      Added ConfigAnalogOutput, StatusGet and GetValue APIs
05/11/11   dy      New file.
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES FOR MODULE

===========================================================================*/

#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include "pm_mpp.h"
#include "pm_uefi.h"

#include <Protocol/EFIPmicMpp.h>
#include <Library/DebugLib.h>

/*===========================================================================
                  LOCAL VARIABLE DEFINITION
===========================================================================*/

/*===========================================================================
                  EXTERNAL FUNCTION DEFINITION
===========================================================================*/
/**
  EFI_PmicMppConfigDigitalInput ()

  @brief
  ConfigDigitalInput implementation of EFI_QCOM_PMIC_MPP_PROTOCOL
 */
EFI_STATUS
EFIAPI
EFI_PmicMppConfigDigitalInput
(
  IN UINT32 PMIC_DEVICE_INDEX,
  EFI_PM_MPP_WHICH_TYPE                Mpp,
  EFI_PM_MPP_DLOGIC_LVL_TYPE           Level,
  EFI_PM_MPP_DLOGIC_IN_DBUS_TYPE       DBus
)
{
  pm_err_flag_type errFlag = PM_ERR_FLAG__SUCCESS;
  errFlag = pm_mpp_config_digital_input( PMIC_DEVICE_INDEX, 
										(pm_mpp_perph_index) Mpp,
                                        (pm_mpp_dlogic_lvl_type) Level,
                                        (pm_mpp_dlogic_in_dbus_type) DBus );
  
  if (errFlag != PM_ERR_FLAG__SUCCESS)
  {
    return EFI_DEVICE_ERROR;
  }

  return EFI_SUCCESS;
}

/**
  EFI_PmicMppConfigDigitalOutput ()

  @brief
  ConfigDigitalOutput implementation of EFI_QCOM_PMIC_MPP_PROTOCOL
 */
EFI_STATUS
EFIAPI
EFI_PmicMppConfigDigitalOutput
(
  IN UINT32 PMIC_DEVICE_INDEX,  
  EFI_PM_MPP_WHICH_TYPE                Mpp,
  EFI_PM_MPP_DLOGIC_LVL_TYPE           Level,
  EFI_PM_MPP_DLOGIC_OUT_CTRL_TYPE      OutputCtrl
)
{
  pm_err_flag_type errFlag = PM_ERR_FLAG__SUCCESS;
  errFlag = pm_mpp_config_digital_output( PMIC_DEVICE_INDEX,
										 (pm_mpp_perph_index) Mpp,
                                         (pm_mpp_dlogic_lvl_type) Level,
                                         (pm_mpp_dlogic_out_ctrl_type) OutputCtrl );
  
  if (errFlag != PM_ERR_FLAG__SUCCESS)
  {
    return EFI_DEVICE_ERROR;
  }

  return EFI_SUCCESS;
}

/**
  EFI_PmicMppConfigDigitalInOut ()

  @brief
  ConfigDigitalInOut implementation of EFI_QCOM_PMIC_MPP_PROTOCOL
 */
EFI_STATUS
EFIAPI
EFI_PmicMppConfigDigitalInOut
(
  IN UINT32 PMIC_DEVICE_INDEX,
  EFI_PM_MPP_WHICH_TYPE                Mpp,
  EFI_PM_MPP_DLOGIC_LVL_TYPE           Level,
  EFI_PM_MPP_DLOGIC_INOUT_PUP_TYPE     PullUp
)
{
  pm_err_flag_type errFlag = PM_ERR_FLAG__SUCCESS;
  errFlag = pm_mpp_config_digital_inout( PMIC_DEVICE_INDEX,
										(pm_mpp_perph_index) Mpp,
                                        (pm_mpp_dlogic_lvl_type) Level,
                                        (pm_mpp_dlogic_inout_pup_type) PullUp );
  
  if (errFlag != PM_ERR_FLAG__SUCCESS)
  {
    return EFI_DEVICE_ERROR;
  }

  return EFI_SUCCESS;
}

/**
  EFI_PmicMppConfigAnalogInput ()

  @brief
  ConfigAnalogInput implementation of EFI_QCOM_PMIC_MPP_PROTOCOL
 */
EFI_STATUS
EFIAPI
EFI_PmicMppConfigAnalogInput
(
  IN UINT32 PMIC_DEVICE_INDEX,
  EFI_PM_MPP_WHICH_TYPE                Mpp,
  EFI_PM_MPP_AIN_CH_TYPE               ChSelect
)
{
  pm_err_flag_type errFlag = PM_ERR_FLAG__SUCCESS;
  errFlag = pm_mpp_config_analog_input( PMIC_DEVICE_INDEX,(pm_mpp_perph_index) Mpp,
                                             (pm_mpp_ain_ch_type) ChSelect );
  
  if (errFlag != PM_ERR_FLAG__SUCCESS)
  {
    return EFI_DEVICE_ERROR;
  }

  return EFI_SUCCESS;
}

/**
  EFI_PmicMppConfigISink ()

  @brief
  ConfigISick implementation of EFI_QCOM_PMIC_MPP_PROTOCOL
 */
EFI_STATUS
EFIAPI
EFI_PmicMppConfigISink
(
  IN UINT32 PMIC_DEVICE_INDEX,
  EFI_PM_MPP_WHICH_TYPE                Mpp,
  EFI_PM_MPP_I_SINK_LEVEL_TYPE         Level,
  EFI_PM_MPP_I_SINK_SWITCH_TYPE        OnOff
)
{
  pm_err_flag_type errFlag = PM_ERR_FLAG__SUCCESS;
  errFlag = pm_mpp_config_i_sink( PMIC_DEVICE_INDEX,(pm_mpp_perph_index) Mpp,
                                       (pm_mpp_i_sink_level_type) Level,
                                       (pm_mpp_i_sink_switch_type) OnOff );
  
  if (errFlag != PM_ERR_FLAG__SUCCESS)
  {
    return EFI_DEVICE_ERROR;
  }

  return EFI_SUCCESS;
}

/**
  EFI_PmicMppConfigAnalogOutput ()

  @brief
  ConfigAnalogOutput implementation of EFI_QCOM_PMIC_MPP_PROTOCOL
 */
EFI_STATUS
EFIAPI
EFI_PmicMppConfigAnalogOutput
(
	IN UINT32 PMIC_DEVICE_INDEX,
    EFI_PM_MPP_WHICH_TYPE        Mpp,
    EFI_PM_MPP_AOUT_LEVEL_TYPE   Level,
    EFI_PM_MPP_AOUT_SWITCH_TYPE  OnOff
)
{
    pm_err_flag_type errFlag = PM_ERR_FLAG__SUCCESS;
    errFlag = pm_mpp_config_analog_output( PMIC_DEVICE_INDEX, 
										  (pm_mpp_perph_index)       Mpp,
                                          (pm_mpp_aout_level_type)  Level,
                                          (pm_mpp_aout_switch_type) OnOff);

    if (errFlag != PM_ERR_FLAG__SUCCESS)
    {
        return EFI_DEVICE_ERROR;
    }

    return EFI_SUCCESS;
}

/**
  EFI_PmicMppStatusGet ()

  @brief
  StatusGet implementation of EFI_QCOM_PMIC_MPP_PROTOCOL
 */
EFI_STATUS
EFIAPI
EFI_PmicMppStatusGet
(
	IN UINT32 PMIC_DEVICE_INDEX,
    EFI_PM_MPP_WHICH_TYPE   Mpp,
    EFI_PM_MPP_STATUS_TYPE  *Status
)
{
    pm_err_flag_type errFlag = PM_ERR_FLAG__SUCCESS;
    errFlag = pm_mpp_status_get( PMIC_DEVICE_INDEX,(pm_mpp_perph_index)  Mpp,
                                     (pm_mpp_status_type *) Status);

    if (errFlag != PM_ERR_FLAG__SUCCESS)
    {
        return EFI_DEVICE_ERROR;
    }

    return EFI_SUCCESS;
}


/**
  EFI_PmicMppIrqEnable()

  @brief
  MppIrqEnable implementation of EFI_QCOM_PMIC_MPP_PROTOCOL
 */
EFI_STATUS
EFIAPI
EFI_PmicMppIrqEnable
(
 IN  UINT32                     PmicDeviceIndex,
 IN  EFI_PM_MPP_WHICH_TYPE      Mpp,
 IN  BOOLEAN                    Enable
)
{
  pm_err_flag_type errFlag = PM_ERR_FLAG__SUCCESS;

  errFlag = pm_mpp_irq_enable( PmicDeviceIndex,(pm_mpp_perph_index)Mpp,(boolean)Enable);
  if (errFlag != PM_ERR_FLAG__SUCCESS)
  {
    return EFI_DEVICE_ERROR;
  }
  return EFI_SUCCESS;
}



/**
  EFI_PmicMppIrqClear()

  @brief
  MppIrqClear implementation of EFI_QCOM_PMIC_MPP_PROTOCOL
 */
EFI_STATUS
EFIAPI
EFI_PmicMppIrqClear
(
 IN  UINT32                    PmicDeviceIndex,
 IN  EFI_PM_MPP_WHICH_TYPE     Mpp
)
{
  pm_err_flag_type errFlag = PM_ERR_FLAG__SUCCESS;

  errFlag = pm_mpp_irq_clear( PmicDeviceIndex,(pm_mpp_perph_index)Mpp);
  if (errFlag != PM_ERR_FLAG__SUCCESS)
  {
    return EFI_DEVICE_ERROR;
  }
  return EFI_SUCCESS;
}



/**
  EFI_PmicMppIrqSetTrigger()

  @brief
  MppIrqSetTrigger implementation of EFI_QCOM_PMIC_MPP_PROTOCOL
 */
EFI_STATUS
EFIAPI
EFI_PmicMppIrqSetTrigger
(
 IN  UINT32                     PmicDeviceIndex,
 IN  EFI_PM_MPP_WHICH_TYPE      Mpp,
 IN  EFI_PM_IRQ_TRIGGER_TYPE    Trigger
)
{
  pm_err_flag_type errFlag = PM_ERR_FLAG__SUCCESS;

  errFlag = pm_mpp_irq_set_trigger( PmicDeviceIndex,(pm_mpp_perph_index)Mpp,(pm_irq_trigger_type)Trigger);
  if (errFlag != PM_ERR_FLAG__SUCCESS)
  {
    return EFI_DEVICE_ERROR;
  }
  return EFI_SUCCESS;
}


/**
  EFI_PmicMppIrqStatus()

  @brief
  PmMppIrqStatus implementation of EFI_QCOM_PMIC_MPP_PROTOCOL
 */
EFI_STATUS
EFIAPI
EFI_PmicMppIrqStatus
(
 IN  UINT32                     PmicDeviceIndex,
 IN  EFI_PM_MPP_WHICH_TYPE      Mpp,
 IN  EFI_PM_IRQ_STATUS_TYPE     Type,
 OUT BOOLEAN                    *Status
)
{
  pm_err_flag_type errFlag = PM_ERR_FLAG__SUCCESS;

  errFlag = pm_mpp_irq_status( PmicDeviceIndex,(pm_mpp_perph_index)Mpp,(pm_irq_status_type) Type,(boolean *)Status);
  if (errFlag != PM_ERR_FLAG__SUCCESS)
  {
    return EFI_DEVICE_ERROR;
  }
  return EFI_SUCCESS;
}


/**
  EFI_PmicMppConfigDtestOut()

  @brief
  ConfigDetstOut implementation of EFI_QCOM_PMIC_MPP_PROTOCOL
 */
EFI_STATUS
EFIAPI
EFI_PmicMppConfigDtestOut
(
 IN  UINT32                           PmicDeviceIndex,
 IN  EFI_PM_MPP_WHICH_TYPE            Mpp,
 IN  EFI_PM_MPP_DLOGIC_LVL_TYPE       Lvl,
 IN  EFI_PM_MPP_DLOGIC_OUT_DBUS_TYPE  Dbus
)
{
  pm_err_flag_type errFlag = PM_ERR_FLAG__SUCCESS;

  errFlag = pm_mpp_config_dtest_output( PmicDeviceIndex,(pm_mpp_perph_index)Mpp,(pm_mpp_dlogic_lvl_type) Lvl,(pm_mpp_dlogic_out_dbus_type)Dbus);
  if (errFlag != PM_ERR_FLAG__SUCCESS)
  {
    return EFI_DEVICE_ERROR;
  }
  return EFI_SUCCESS;

}

/**
  PMIC MPP UEFI Protocol implementation
 */
EFI_QCOM_PMIC_MPP_PROTOCOL PmicMppProtocolImplementation = 
{
    PMIC_MPP_REVISION,
    EFI_PmicMppConfigDigitalInput,
    EFI_PmicMppConfigDigitalOutput,
    EFI_PmicMppConfigDigitalInOut,
    EFI_PmicMppConfigAnalogInput,
    EFI_PmicMppConfigISink,
    EFI_PmicMppConfigAnalogOutput,
    EFI_PmicMppStatusGet,
    EFI_PmicMppIrqEnable,
    EFI_PmicMppIrqClear,
    EFI_PmicMppIrqSetTrigger,
    EFI_PmicMppIrqStatus,
    EFI_PmicMppConfigDtestOut
};
