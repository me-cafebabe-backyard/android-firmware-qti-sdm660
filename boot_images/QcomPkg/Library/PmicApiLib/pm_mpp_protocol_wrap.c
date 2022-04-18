/*! \file
*  
*  \brief  pm_mpp_protocol_wrap.c ----File contains the implementation of the public APIs for MPP resource type.
*  \details Implementation file for MPP resourece type.
*  Each of the APIs checks for access and then if necessary directs
*  the call to Driver implementation or to RPC function for the master processor.
*  
*    PMIC code generation Version: 2.0.0.19
*    This file contains code for Target specific settings and modes.
*  
*  &copy; Copyright 2014 QUALCOMM Technologies, Inc, All Rights Reserved
*/

/*===========================================================================

EDIT HISTORY FOR MODULE

This document is created by a code generator, therefore this section will
not contain comments describing changes made to the module.


when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
12/15/14   al      New file 
===========================================================================*/

/*===========================================================================

INCLUDE FILES 

===========================================================================*/
#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>


#include <api/systemdrivers/pmic/pm_mpp.h>
#include <Protocol/EFIPmicMpp.h>
/*===========================================================================

                        FUNCTION PROTOTYPES

===========================================================================*/

/*===========================================================================

                        FUNCTION DEFINITIONS

===========================================================================*/

STATIC EFI_QCOM_PMIC_MPP_PROTOCOL            *PmicMppProtocol  = NULL;

pm_err_flag_type pm_mpp_protocol_init(void)
{
  EFI_STATUS  Status = EFI_SUCCESS;
  pm_err_flag_type         err_flag = PM_ERR_FLAG__SUCCESS;

  if (NULL == PmicMppProtocol)
  {
    Status = gBS->LocateProtocol(&gQcomPmicMppProtocolGuid, NULL, (VOID **)&PmicMppProtocol);
    err_flag = (Status == EFI_SUCCESS) ? PM_ERR_FLAG__SUCCESS : PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
  }

  return err_flag;
}

pm_err_flag_type pm_mpp_config_digital_input(uint32 pmic_chip, pm_mpp_perph_index mpp, pm_mpp_dlogic_lvl_type  level, pm_mpp_dlogic_in_dbus_type  dbus)
{
  pm_err_flag_type       err_flag = PM_ERR_FLAG__SUCCESS;
  EFI_STATUS  Status = EFI_SUCCESS;

  if (PM_ERR_FLAG__SUCCESS == pm_mpp_protocol_init())
  {
    Status = PmicMppProtocol->ConfigDigitalInput(pmic_chip, (EFI_PM_MPP_WHICH_TYPE)mpp, (EFI_PM_MPP_DLOGIC_LVL_TYPE)level, (EFI_PM_MPP_DLOGIC_IN_DBUS_TYPE)dbus);
    err_flag = (Status == EFI_SUCCESS) ? PM_ERR_FLAG__SUCCESS : PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
  }
  else
  {
    err_flag = PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
  }

  return err_flag;
}


pm_err_flag_type pm_mpp_config_digital_output(uint32 pmic_chip, pm_mpp_perph_index mpp, pm_mpp_dlogic_lvl_type  level, pm_mpp_dlogic_out_ctrl_type  output_ctrl)
{
  pm_err_flag_type       err_flag = PM_ERR_FLAG__SUCCESS;
  EFI_STATUS  Status = EFI_SUCCESS;

  if (PM_ERR_FLAG__SUCCESS == pm_mpp_protocol_init())
  {
    Status = PmicMppProtocol->ConfigDigitalOutput(pmic_chip, (EFI_PM_MPP_WHICH_TYPE)mpp, (EFI_PM_MPP_DLOGIC_LVL_TYPE)level, (EFI_PM_MPP_DLOGIC_OUT_CTRL_TYPE)output_ctrl);
    err_flag = (Status == EFI_SUCCESS) ? PM_ERR_FLAG__SUCCESS : PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
  }
  else
  {
    err_flag = PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
  }

  return err_flag;
}

pm_err_flag_type pm_mpp_config_digital_inout(uint32 pmic_chip, pm_mpp_perph_index mpp, pm_mpp_dlogic_lvl_type  level, pm_mpp_dlogic_inout_pup_type  pull_up)
{
  pm_err_flag_type       err_flag = PM_ERR_FLAG__SUCCESS;
  EFI_STATUS  Status = EFI_SUCCESS;

  if (PM_ERR_FLAG__SUCCESS == pm_mpp_protocol_init())
  {
    Status = PmicMppProtocol->ConfigDigitalInOut(pmic_chip, (EFI_PM_MPP_WHICH_TYPE)mpp, (EFI_PM_MPP_DLOGIC_LVL_TYPE)level, (EFI_PM_MPP_DLOGIC_INOUT_PUP_TYPE)pull_up);
    err_flag = (Status == EFI_SUCCESS) ? PM_ERR_FLAG__SUCCESS : PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
  }
  else
  {
    err_flag = PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
  }

  return err_flag;
}

pm_err_flag_type pm_mpp_config_analog_input(uint32  pmic_chip,  pm_mpp_perph_index mpp, pm_mpp_ain_ch_type  ch_select)
{
/* Use this variable to keep track if the operation was successful or not */
  pm_err_flag_type       err_flag = PM_ERR_FLAG__SUCCESS;
  EFI_STATUS  Status = EFI_SUCCESS;

  if (PM_ERR_FLAG__SUCCESS == pm_mpp_protocol_init())
  {
    Status = PmicMppProtocol->ConfigAnalogInput(pmic_chip, (EFI_PM_MPP_WHICH_TYPE)mpp, (EFI_PM_MPP_AIN_CH_TYPE)ch_select);
    err_flag = (Status == EFI_SUCCESS) ? PM_ERR_FLAG__SUCCESS : PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
  }
  else
  {
    err_flag = PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
  }

  return err_flag;
}


pm_err_flag_type pm_mpp_config_analog_output(uint32 pmic_chip, pm_mpp_perph_index mpp, pm_mpp_aout_level_type  level, pm_mpp_aout_switch_type  OnOff)
{
  pm_err_flag_type       err_flag = PM_ERR_FLAG__SUCCESS;
  EFI_STATUS  Status = EFI_SUCCESS;

  if (PM_ERR_FLAG__SUCCESS == pm_mpp_protocol_init())
  {
    Status = PmicMppProtocol->ConfigAnalogOutput(pmic_chip, (EFI_PM_MPP_WHICH_TYPE)mpp, (EFI_PM_MPP_AOUT_LEVEL_TYPE)level, (EFI_PM_MPP_AOUT_SWITCH_TYPE)OnOff);
    err_flag = (Status == EFI_SUCCESS) ? PM_ERR_FLAG__SUCCESS : PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
  }
  else
  {
    err_flag = PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
  }

  return err_flag;
}


