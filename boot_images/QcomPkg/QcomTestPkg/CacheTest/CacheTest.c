/** @file CacheTest.c
   
  Profile Cache

  Copyright (c) 2016 Qualcomm Technologies Inc. All rights reserved.
**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 12/20/10   niting  Added timer based Hello World.

=============================================================================*/

#include <Uefi.h>
#include <Library/PcdLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/TestInterface.h>
#include <Library/QcomLib.h>
#include <Library/QcomBaseLib.h>
#include <Library/ArmLib.h>
#include <Library/CacheMaintenanceLib.h>

/**
  The user Entry Point for Application. The user code starts with this function
  as the real entry point for the application.

  @param[in] ImageHandle    The firmware allocated handle for the EFI image.  
  @param[in] SystemTable    A pointer to the EFI System Table.
  
  @retval EFI_SUCCESS       The entry point is executed successfully.
  @retval other             Some error occurs when executing this entry point.

**/
EFI_STATUS
EFIAPI
UefiMain (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  #define WRITE_SIZE 350

  EFI_STATUS  Status = EFI_SUCCESS;
  VOID* TestBuffer = NULL;
  UINT32 i = 0;

  TestBuffer = AllocatePages(SIZE_16MB/EFI_PAGE_SIZE);
  if (TestBuffer == NULL)
    return EFI_OUT_OF_RESOURCES;

#if 0  
  ArmCleanInvadlidateDataCache();
  ArmCleanInvadlidateInstructionCache();

  SetMem (TestBuffer, SIZE_1MB, 0);
#endif

  LogMsg("Start Invalidate");
  for (i = 0; i < 100; i++)
  {
    SetMem (TestBuffer, WRITE_SIZE, i);     	  
    WriteBackInvalidateDataCacheRange (TestBuffer, WRITE_SIZE);
  }

  LogMsg("End   Invalidate");

  LogMsg("Start Invalidate");
  for (i = 0; i < 1000; i++)
  {
    SetMem ( (VOID*)((UINTN)TestBuffer+SIZE_8MB), WRITE_SIZE, i);     	  
    WriteBackInvalidateDataCacheRange ( (VOID*)((UINTN)TestBuffer+SIZE_8MB), WRITE_SIZE);
  }

  LogMsg("End   Invalidate");

  return Status;
}

