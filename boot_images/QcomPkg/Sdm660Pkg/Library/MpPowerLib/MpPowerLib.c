/** @file MpPowerLib.c

  This file implements specialized chip specific code for Multicore
  protocol

  Copyright (c) 2015-17, Qualcomm Technologies, Inc. All rights reserved.

**/

/*=============================================================================
                              EDIT HISTORY

  $Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/MpPowerLib/MpPowerLib.c#4 $
  $DateTime: 2017/02/07 21:40:01 $
  $Author: pwbldsvc $

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 12/21/15   rli     Remove APC voltage adjustment
 09/22/15   rli     Initial revision
=============================================================================*/


/*=========================================================================
      Include Files
==========================================================================*/
#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/EFIPmicVreg.h>
#include <Library/IoLib.h>

#include <Library/MpPowerLib.h>
#include <Protocol/EFIChipInfo.h>
#include <Protocol/EFIPlatformInfo.h>

EFI_CHIPINFO_PROTOCOL  *ChipInfoProtocol = NULL;
EFIChipInfoFamilyType  ChipFamily        = EFICHIPINFO_FAMILY_UNKNOWN;

/**
  Chipset-specific initialization.
  @return - EFI_SUCCESS on success, otherwise error status
*/
EFI_STATUS MpPowerInit (VOID)
{
  return EFI_SUCCESS;
}

/**
  Chipset-specific multicore enablement

  @param[in]  CoreNum - number of cores
  @return - EFI_SUCCESS on success, otherwise error status
*/
EFI_STATUS MpPower (UINTN  CoreNum)
{
  EFI_QCOM_PMIC_VREG_PROTOCOL  *PmicVRegProtocol = NULL;
  EFI_STATUS Status = EFI_SUCCESS;
  EFI_PM_VREG_STATUS_TYPE VregStatus;
  EFI_PM_VREG_ID_TYPE pmicVregID = EFI_PM_SMPS_3;
  INT32 RetryCnt = 200; /* Only give PMIC 2ms to adjust otherwise HW error */

  /* Get Protocol handles */
  Status = gBS->LocateProtocol (&gEfiChipInfoProtocolGuid, NULL,
                               (VOID **) &ChipInfoProtocol);
  
  if (Status == EFI_SUCCESS)  
  {
     ChipInfoProtocol->GetChipFamily(ChipInfoProtocol, &ChipFamily);
     if (EFICHIPINFO_FAMILY_SDM630 == ChipFamily)
     {
        /* For Starhawk, Gold cluster is on S1 rail. */
        pmicVregID = EFI_PM_SMPS_1;
     }
  }

  /* Acquire PMIC Vreg EFI Protocol handle */
  Status = gBS->LocateProtocol( &gQcomPmicVregProtocolGuid,
                                NULL, (VOID **)&PmicVRegProtocol );
  if (EFI_ERROR(Status))
  {
    return EFI_NOT_FOUND;
  }

  /* Set Gold Cluster Rail to Nominal */
  Status = PmicVRegProtocol->VregSetLevel(0, pmicVregID, 868);
  if (EFI_ERROR(Status))
  {
    return Status;
  }

  /* Enable Gold Cluster Rail */
  Status = PmicVRegProtocol->VregControl(0, pmicVregID, TRUE);
  if (EFI_ERROR(Status))
  {
    return Status;
  }

  /* Wait for rail to come up */
  do
  {
    if (RetryCnt-- <= 0)
    {
      ASSERT(0);
    }

    gBS->Stall(10);
    Status = PmicVRegProtocol->VregGetStatus(0, pmicVregID,  &VregStatus);
    if (EFI_ERROR(Status))
    {
      return Status;
    }
  } while (!(VregStatus.VregOk));

  return EFI_SUCCESS;
}
