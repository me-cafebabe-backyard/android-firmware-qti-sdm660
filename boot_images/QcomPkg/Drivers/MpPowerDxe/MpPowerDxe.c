/** @file
  Implements the multi-processor power support

  Copyright (c) 2015-16, Qualcomm Technologies,Inc. All rights reserved.
   
**/

/*=============================================================================
                              EDIT HISTORY

  $Header: //components/rel/boot.xf/1.4/QcomPkg/Drivers/MpPowerDxe/MpPowerDxe.c#2 $
  $DateTime: 2016/08/19 05:58:45 $
  $Author: c_mvanim $

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 03/10/15   rli     Initial version.

=============================================================================*/

#include <Uefi.h>
#include <Guid/EventGroup.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiCfgLib.h>
#include <Library/DebugLib.h>

#include <Library/MpPowerLib.h>


/** Globals **/
UINT32    NumCpus =  0;
BOOLEAN   PsciCompliant = FALSE;


/** Locals **/
STATIC EFI_EVENT EfiExitBootServicesEvent = (EFI_EVENT)NULL;

/* This callback is to notify that boot services is about to exit */
VOID
EFIAPI
MpPowerExitBootServicesCallBack (
  IN EFI_EVENT        Event,
  IN VOID             *Context
  )
{
    /* Multicluster enablement */
  if (MpPower(NumCpus) != EFI_SUCCESS)
  {
    DEBUG(( EFI_D_ERROR, "Chipset-specific Exit BS initialization failed.\r\n"));
  }
}


EFI_STATUS
MpPowerInitialize (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTablef
  )
{
  EFI_STATUS  Status = GetConfigValue ("NumActiveCores", &NumCpus);

  if ((Status != EFI_SUCCESS) || (NumCpus == 0))
  {
    Status = GetConfigValue ("NumCpus", &NumCpus);
    if ((Status != EFI_SUCCESS) || (NumCpus == 0))
    {
      DEBUG ((EFI_D_WARN, "NumCpus not found in uefiplat.cfg. Defaulting to 1.\r\n"));
      // Default to 1
      NumCpus = 1;
    }
  }

  if (MpPowerInit() != EFI_SUCCESS)
  {
    DEBUG(( EFI_D_ERROR, "Chipset-specific initialization failed.\r\n"));
  }

  return gBS->CreateEventEx ( EVT_NOTIFY_SIGNAL,
                              TPL_CALLBACK,
                              MpPowerExitBootServicesCallBack,
                              NULL,
                              &gEfiEventExitBootServicesGuid,
                              &EfiExitBootServicesEvent);
}
