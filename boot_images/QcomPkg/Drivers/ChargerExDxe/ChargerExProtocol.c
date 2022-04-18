/*! @file ChargerExProtocol.c

*  CHARGER EXTENDED MODULE RELATED DECLARATION
*  This file contains functions and variable declarations to support
*  the Charger Extended module.
*
*  Copyright (c) 2016-2017 Qualcomm Technologies, Inc.  All Rights Reserved.
*  Qualcomm Technologies Inc Proprietary and Confidential.
*/

/*===========================================================================

EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     --------------------------------------------------------------------------
07/27/17   pbitra  Returning EFI_UNSUPPORTED for RCM platform
02/20/17   mr      Added changes to return EFI_UNSUPPORTED Status for CDP and RUMI Platforms
01/03/17   ks      Updating "EFI_ChargerExGetChargerPresence" to support micro usb
11/09/16   cs      modified charger present API also to detect DCIn.
09/09/16   sm      Added Status success check after locating protocol.
05/31/16   sm      New File
===========================================================================*/

/*===========================================================================

INCLUDE FILES FOR MODULE

===========================================================================*/

#include <Library/UefiLib.h>
/**
  PMIC Lib interfaces
 */
#include <Include/Protocol/EFIQcomCharger.h>
#include <Include/Protocol/EFIPmicUsb.h>
#include <Include/Protocol/EFIChargerEx.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Protocol/EFIPlatformInfo.h>
#include <Library/QcomLib.h>

extern EFI_GUID gQcomPmicUsbProtocolGuid;
EFI_CHARGER_EX_PROTOCOL ChargerExProtocolImplementation;

STATIC EFI_QCOM_CHARGER_PROTOCOL        *pQcomChargerProtocol  = NULL;

/*===========================================================================
EXTERNAL FUNCTION DECLARATIONS
===========================================================================*/
/**
EFI_ChargerExInit()

@brief
Initializes charger Extended module
*/
EFI_STATUS ChargerExInitialize( IN EFI_HANDLE         ImageHandle,
                                IN EFI_SYSTEM_TABLE   *SystemTable )
{
  EFI_STATUS Status = EFI_SUCCESS;

  Status  = gBS->InstallMultipleProtocolInterfaces(
                 &ImageHandle,
                 &gChargerExProtocolGuid,
                 &ChargerExProtocolImplementation,
                 NULL
                 );

  return Status;
}

/**
EFI_ChargerExGetChargerPresence()

@brief
 Returns charger presence status
 */
EFI_STATUS
EFIAPI
EFI_ChargerExGetChargerPresence
(
  OUT BOOLEAN  *pChargerPresent
)
{
  EFI_STATUS                           Status = EFI_SUCCESS;
  STATIC EFI_QCOM_PMIC_USB_PROTOCOL   *PmicUsbProtocol   = NULL;
  BOOLEAN                              DcInValid = FALSE;
  EFI_PLATFORMINFO_PLATFORM_TYPE       PlatformType;

  if (!pChargerPresent)
  {
    return EFI_INVALID_PARAMETER;
  }

  Status |= GetPlatformType(&PlatformType);
  if(EFI_SUCCESS != Status)
  {
    DEBUG((EFI_D_WARN, "ChargerExProtocol:: %a Error getting platform type  \r\n", __FUNCTION__));
    return EFI_DEVICE_ERROR;
  }

  if((EFI_PLATFORMINFO_TYPE_CDP == PlatformType) || (EFI_PLATFORMINFO_TYPE_RUMI == PlatformType) || (EFI_PLATFORMINFO_TYPE_RCM == PlatformType))
  {
    DEBUG(( EFI_D_WARN, "ChargerExProtocol:: %a CDP/RUMI (%d) Platform detected. No Battery information available. \r\n", __FUNCTION__, PlatformType));
    return EFI_UNSUPPORTED;
  }

  if (!PmicUsbProtocol)
  {
    Status = gBS->LocateProtocol( &gQcomPmicUsbProtocolGuid,
                                  NULL,
                                 (VOID **)&PmicUsbProtocol );

    if((EFI_SUCCESS != Status) || (NULL == PmicUsbProtocol))
    {
      return EFI_DEVICE_ERROR;
    }
  }

  Status = PmicUsbProtocol->GetChargerPresence(pChargerPresent);

  if (EFI_SUCCESS != Status)
  {
    return Status;
  }

  if (!pQcomChargerProtocol)
  {
    Status = gBS->LocateProtocol(&gQcomChargerProtocolGuid, NULL, (VOID **)&pQcomChargerProtocol);

    if ((EFI_SUCCESS != Status) || (NULL == pQcomChargerProtocol))
    {
      return EFI_DEVICE_ERROR;
    }
  }

  Status = pQcomChargerProtocol->IsDcInValid(&DcInValid);

  if (EFI_SUCCESS == Status)
  {
    (*pChargerPresent) |= DcInValid;
  }

  return Status;
}


/**
EFI_ChargerExGetBatteryPresence ()

@brief
Get battery presence status SCHG
*/
EFI_STATUS
EFIAPI
EFI_ChargerExGetBatteryPresence
(
  OUT BOOLEAN  *pBatteryPresent
)
{
  EFI_STATUS                      Status = EFI_SUCCESS;
  EFI_PLATFORMINFO_PLATFORM_TYPE  PlatformType;

  if (!pBatteryPresent)
  {
    return EFI_INVALID_PARAMETER;
  }

  Status |= GetPlatformType(&PlatformType);
  if(EFI_SUCCESS != Status)
  {
    DEBUG((EFI_D_WARN, "ChargerExProtocol:: %a Error getting platform type  \r\n", __FUNCTION__));
    return EFI_DEVICE_ERROR;
  }

  if((EFI_PLATFORMINFO_TYPE_CDP == PlatformType) || (EFI_PLATFORMINFO_TYPE_RUMI == PlatformType) || (EFI_PLATFORMINFO_TYPE_RCM == PlatformType))
  {
    DEBUG(( EFI_D_WARN, "ChargerExProtocol:: %a CDP/RUMI (%d) Platform detected. No Battery information available. \r\n", __FUNCTION__, PlatformType));
    return EFI_UNSUPPORTED;
  }

  if(!pQcomChargerProtocol)
  {
    Status = gBS->LocateProtocol( &gQcomChargerProtocolGuid, NULL, (VOID **)&pQcomChargerProtocol );

    if((EFI_SUCCESS != Status) || (NULL == pQcomChargerProtocol))
    {
      return EFI_DEVICE_ERROR;
    }
  }

  Status = pQcomChargerProtocol->GetBatteryPresence(pBatteryPresent);

  return Status;
}

/**
EFI_ChargerExGetBatteryVoltage ()

@brief
Returns battery voltage
*/
EFI_STATUS
EFIAPI
EFI_ChargerExGetBatteryVoltage
(
  OUT UINT32  *pBatteryVoltage
)
{
  EFI_STATUS                      Status = EFI_SUCCESS;
  EFI_PLATFORMINFO_PLATFORM_TYPE  PlatformType;

  if (!pBatteryVoltage)
  {
    return EFI_INVALID_PARAMETER;
  }

  Status |= GetPlatformType(&PlatformType);
  if(EFI_SUCCESS != Status)
  {
    DEBUG((EFI_D_WARN, "ChargerExProtocol:: %a Error getting platform type  \r\n", __FUNCTION__));
    return EFI_DEVICE_ERROR;
  }

  if((EFI_PLATFORMINFO_TYPE_CDP == PlatformType) || (EFI_PLATFORMINFO_TYPE_RUMI == PlatformType) || (EFI_PLATFORMINFO_TYPE_RCM == PlatformType))
  {
    DEBUG(( EFI_D_WARN, "ChargerExProtocol:: %a CDP/RUMI (%d) Platform detected. No Battery information available. \r\n", __FUNCTION__, PlatformType));
    return EFI_UNSUPPORTED;
  }

  if(!pQcomChargerProtocol)
  {
    Status = gBS->LocateProtocol( &gQcomChargerProtocolGuid, NULL, (VOID **)&pQcomChargerProtocol );

    if(EFI_SUCCESS != Status || NULL == pQcomChargerProtocol)
    {
      return EFI_DEVICE_ERROR;
    }
  }

  Status = pQcomChargerProtocol->GetBatteryVoltage(pBatteryVoltage);

  return Status;
}

/**
Charger External UEFI Protocol implementation
*/
EFI_CHARGER_EX_PROTOCOL ChargerExProtocolImplementation =
{
    CHARGER_EX_REVISION,
    EFI_ChargerExGetChargerPresence,
    EFI_ChargerExGetBatteryPresence,
    EFI_ChargerExGetBatteryVoltage,
};

