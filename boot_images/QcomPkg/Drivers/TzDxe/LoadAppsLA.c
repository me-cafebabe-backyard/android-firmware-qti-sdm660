/** @file LoadAppsLA.c
  Implementation of modules to load hlos specific applications 

  Copyright (c) 2011-2016, Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
   
**/

/*=============================================================================
                              EDIT HISTORY


 when       who      what, where, why
 --------   ---      ----------------------------------------------------------
 07/12/16   rj       Created the file. Moved function from TzeLoader.c
=============================================================================*/


/*=========================================================================
      Include Files
==========================================================================*/

#include <Library/QcomLib.h>
#include <Library/UefiLib.h>
#include <Library/UncachedMemoryAllocationLib.h>
#include <Library/TzRuntimeLib.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/EfiFileLib.h>
#include <Library/ArmLib.h>
#include <Library/PcdLib.h>
#include <Guid/FileSystemVolumeLabelInfo.h>
#include "QcomLib.h"
#include <Protocol/EFITzeLoader.h>
#include <Library/QcomBaseLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Protocol/EFIScm.h>
#include <Include/scm_sip_interface.h>
#include <Include/scm_qsee_interface.h>
#include <Library/UefiCfgLib.h>
#include <Library/BootConfig.h>
#include <TzeLoaderDxe.h>
#include <QseeComDxe.h>

#define TZ_FVER_QSEE                         10 /**< QSEE application layer. */

#define TZBSP_computed_VERSION(major, minor, patch) \
  (((major & 0x3FF) << 22) | ((minor & 0x3FF) << 12) | (patch & 0xFFF))

#define COMMON_LIB_LABEL                     L"cmnlib"
#define COMMON_LIB_64_LABEL                  L"cmnlib64"
#define KEYMASTER_MBN_LABEL                  L"keymaster"

//Fat16 partition; @TODO: move all this once tested
STATIC EFI_GUID KeyMasterPartitionGuid =
  { 0xA11D2A7C, 0xD82A, 0x4C2F, { 0x8A, 0x01, 0x18, 0x05, 0x24, 0x0E, 0x66, 0x26 } };
STATIC EFI_GUID CommonLibPartitionGuid =
  { 0x73471795, 0xAB54, 0x43F9, { 0xA8, 0x47, 0x4F, 0x72, 0xEA, 0x5C, 0xBE, 0xF5 } };
//8EA64893-1267-4A1B-947C-7C362ACAAD2C
STATIC EFI_GUID CommonLib64PartitionGuid =
  { 0x8EA64893, 0x1267, 0x4A1B, { 0x94, 0x7C, 0x7C, 0x36, 0x2A, 0xCA, 0xAD, 0x2C } };


BOOLEAN TZSecureAppLoadCalled;

  /**
  Loads all Secure Apps at bootup
  
  @param  Path            Directory containging ACPI table files
  @param  pPartitionGuid  GUID eg:  TzAppsPartitionType
  @param AppIdPtr         out  if success holds app id on return
   
  @return EFI_SUCCESS if successful
**/
 
EFI_STATUS
LoadSecureApps(
   IN  EFI_TZE_LOADER_PROTOCOL        *This,
   IN EFI_HANDLE ImageHandle,
   IN EFI_SYSTEM_TABLE *SystemTable,
   OUT UINT32                         *AppIdPtr
)
{
  UINT64                  MemBase = 0;
  UINT64                  MemSize = 0;
  EFI_STATUS              Status = EFI_SUCCESS;
  UINT32                  AppId = 0;
  UINT32                  version = 0;
  UINT32                  computed_version = 0;
  UINT32                  CommonMbnLoadFlag = 0;
  UINT32                  LoadKeymasterFlag = 0;

  if (TZSecureAppLoadCalled == TRUE)
  {
    Status = EFI_LOAD_ERROR;
    goto ErrorExit;
  }

  // init QSEECOM protocol
  Status = QseeComProtocolInit(ImageHandle, SystemTable);
  if (Status != EFI_SUCCESS)
  {
    return Status;
  }

  Status = TzGetFeatureVersion(TZ_FVER_QSEE, &version);
  if(EFI_ERROR(Status))
  {
    goto ErrorExit;
  }

  computed_version = TZBSP_computed_VERSION (1,2,0);
  if (version >= computed_version)
  {
    Status = GetConfigValue64 ("TzAppsRegnAddr", &MemBase);
    if (Status != EFI_SUCCESS)
    {
        DEBUG ((EFI_D_INFO, "LoadSecureApps: Unable to find TZApps region addr in config file\n"));
        ASSERT (Status == EFI_SUCCESS);
    }
	
    Status = GetConfigValue64 ("TzAppsRegnSize", &MemSize);
    if (Status != EFI_SUCCESS)
    {
        DEBUG ((EFI_D_INFO, "LoadSecureApps: Unable to find TZApps region size in config file\n"));
        ASSERT (Status == EFI_SUCCESS);
    }

    Status = QseeAppsRegionNotificationSyscall(MemBase, MemSize);
    ASSERT_EFI_ERROR(Status);
  }
  
  TZSecureAppLoadCalled = TRUE;

  computed_version = TZBSP_computed_VERSION (1,1,0);
  if (version >= computed_version)
  {
    Status = GetConfigValue ("SecurityFlag", &CommonMbnLoadFlag);        // Get this flag from uefiplat.cfg. Depending on the flag, process call to this function
    if ((Status != EFI_SUCCESS) || ((CommonMbnLoadFlag & 0x4) != 0x4))
    {
      DEBUG ((EFI_D_INFO, "CommonMbnLoadFlag not found in uefiplat.cfg. Defaulting to 0.\r\n"));
      // Default to 0. Does not matter what the flag is
      CommonMbnLoadFlag = 0;
      Status = EFI_SUCCESS;   // Continue for Hawker
    }
    else
    {
      Status = LoadSecureImageFromFileSystem (This,
                                       &CommonLibPartitionGuid,
                                       NULL,
                                       TRUE,
                                       &AppId);
      if (Status != EFI_SUCCESS)
      {
          DEBUG ((EFI_D_WARN, "Unable to load cmnlib Status:%d\r\n", Status));
          Status = LoadImageFromPartitionLabel (This,
                                                COMMON_LIB_LABEL,
                                                &AppId);
          if(Status != EFI_SUCCESS)
          {
            DEBUG ((EFI_D_WARN, "Unable to load cmnlib using label Status:%d\r\n", Status));
            ASSERT_EFI_ERROR(Status);
          }
          //gRT->ResetSystem(EfiResetCold, EFI_SUCCESS, 0, NULL);
      }


      Status = LoadSecureImageFromFileSystem (This,
                                       &CommonLib64PartitionGuid,
                                       NULL,
                                       TRUE,
                                       &AppId);
      if (Status != EFI_SUCCESS)
      {
        DEBUG ((EFI_D_WARN, "Unable to load cmnlib64 Status:%d\r\n", Status));
        Status = LoadImageFromPartitionLabel (This,
                                              COMMON_LIB_64_LABEL,
                                              &AppId);
        if(Status != EFI_SUCCESS)
        {
          DEBUG ((EFI_D_WARN, "Unable to load cmnlib using label Status:%d\r\n", Status));
          ASSERT_EFI_ERROR(Status);
        }
        //gRT->ResetSystem(EfiResetCold, EFI_SUCCESS, 0, NULL);
      }
    }
  }

  Status = GetConfigValue ("SecurityFlag", &LoadKeymasterFlag);        // Get this flag from uefiplat.cfg. Depending on the flag, process call to this function
  if ((Status != EFI_SUCCESS) || ((LoadKeymasterFlag & 0x80) != 0x80))
  {
    DEBUG ((EFI_D_INFO, "KeymasterFlag not found in uefiplat.cfg. Defaulting to 0.\r\n"));
    LoadKeymasterFlag = 0;
    Status = EFI_SUCCESS;
  }
  else
  {
    Status = LoadSecureImageFromFileSystem (This,
                                     &KeyMasterPartitionGuid,
                                     NULL,
                                     FALSE,
                                     &AppId);
    if(EFI_ERROR(Status))
    {
      DEBUG((EFI_D_ERROR, "Keymaster failed to load! Status = 0x%x\r\n", Status));
      Status = LoadImageFromPartition (This,
                                       &KeyMasterPartitionGuid,
                                       KEYMASTER_MBN_LABEL,
                                       &AppId);
      if(Status != EFI_SUCCESS)
      {
        DEBUG ((EFI_D_WARN, "Unable to load Keymaster using label Status:%d\r\n", Status));
        ASSERT_EFI_ERROR(Status);
      }
      //gRT->ResetSystem(EfiResetCold, EFI_SUCCESS, 0, NULL);
    }
    DEBUG ((EFI_D_ERROR, "LoadSecureApps: Load app from partition(%s): Status = 0x%p, AppId = %d\r\n",
                                               KEYMASTER_MBN_LABEL, Status, AppId));
    if (AppIdPtr)
      *AppIdPtr = AppId;
  }

  Status = EFI_SUCCESS;

ErrorExit:
  return Status;
}
