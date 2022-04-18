/** @file MemTest.c
   
  Tests for Allocate/Free pages/pool and uncached pages/pool.

  Copyright (c) 2012-2013, Qualcomm Technologies Inc. All rights reserved.
  
**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 01/17/13   vk      Fix warning
 06/27/12   jz      Cleanups
 04/04/12   jz      Initial revision

=============================================================================*/

#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/TestInterface.h>
#include <Library/PrintLib.h>
#include <Library/UncachedMemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/PcdLib.h>
#include <Library/QcomBaseLib.h>

#define MAX_NUM_LOOP   100

STATIC
EFI_STATUS
TestAllocatePages (
  EFI_ALLOCATE_TYPE AllocateType,
  EFI_MEMORY_TYPE   MemoryType
  )
{
  EFI_STATUS           Status = EFI_SUCCESS;
  UINTN                Index;
  EFI_PHYSICAL_ADDRESS MemAddress = MAX_ADDRESS;

  for (Index=1; Index<=MAX_NUM_LOOP; Index++)
  {
    Status = gBS->AllocatePages(AllocateType, MemoryType, Index, &MemAddress);
    if (EFI_ERROR(Status))
    {
      AsciiPrint("*** Failed to allocate %d pages, Status: 0x%x\n",
                 Index, Status);
      break;
    }

    gBS->SetMem((VOID *)(UINTN)MemAddress, EFI_PAGES_TO_SIZE(Index), 1 << (Index & 0x7));
    Status = gBS->FreePages(MemAddress, Index);
    if (EFI_ERROR(Status))
    {
      AsciiPrint("*** Failed to free %d pages, Status: 0x%x\n",
                 Index, Status);
      break;
    }
  }

  return Status;
}

STATIC
EFI_STATUS
TestAllocatePool (
  EFI_MEMORY_TYPE   MemoryType
  )
{
  EFI_STATUS           Status = EFI_SUCCESS;
  UINTN                Index;
  VOID                 *pMemBuffer = NULL;

  for (Index=1; Index<=MAX_NUM_LOOP; Index++)
  {
    Status = gBS->AllocatePool(MemoryType, EFI_PAGES_TO_SIZE(Index), &pMemBuffer);
    if (EFI_ERROR(Status))
    {
      AsciiPrint("*** Failed to allocate pool, size %d, Status: 0x%x\n",
                 EFI_PAGES_TO_SIZE(Index), Status);
      break;
    }

    SetMem(pMemBuffer, EFI_PAGES_TO_SIZE(Index), 1 << (Index & 0x7));
    Status = gBS->FreePool(pMemBuffer);
    if (EFI_ERROR(Status))
    {
      AsciiPrint("*** Failed to free pool, size %d, Status: 0x%x\n",
                 EFI_PAGES_TO_SIZE(Index), Status);
      break;
    }
  }

  return Status;
}

STATIC
EFI_STATUS
TestUncachedAllocatePages (
  VOID
  )
{
  EFI_STATUS           Status = EFI_SUCCESS;
  VOID                 *pMemBuffer = NULL;
  UINTN                Index;

  for (Index=1; Index<=MAX_NUM_LOOP; Index++)
  {
    pMemBuffer = UncachedAllocatePages(Index);
    if (pMemBuffer == NULL)
    {
      Status = EFI_OUT_OF_RESOURCES;
      AsciiPrint("*** Failed to allocate %d uncached pages, Status = 0x%x\n",
                 Index, Status);
      break;
    }

    SetMem(pMemBuffer, EFI_PAGES_TO_SIZE(Index), 1 << (Index & 0x7));
    UncachedFreePages(pMemBuffer, Index);
  }

  return Status;
}

STATIC
EFI_STATUS
TestUncachedAllocatePool (
  VOID
  )
{
  EFI_STATUS           Status = EFI_SUCCESS;
  VOID                 *pMemBuffer = NULL;
  UINTN                Index;

  for (Index=1; Index<=MAX_NUM_LOOP; Index++)
  {
    pMemBuffer = UncachedAllocatePool(EFI_PAGES_TO_SIZE(Index));
    if (pMemBuffer == NULL)
    {
      Status = EFI_OUT_OF_RESOURCES;
      AsciiPrint("*** Failed to allocate uncached pool, size %d, Status = 0x%x\n",
                 EFI_PAGES_TO_SIZE(Index), Status);
      break;
    }

    SetMem(pMemBuffer, EFI_PAGES_TO_SIZE(Index), 1 << (Index & 0x7));
    UncachedFreePool(pMemBuffer);
  }

  return Status;
}

/**
  Entry point for the application

  @param[in] ImageHandle    Image handle 
  @param[in] SystemTable    Pointer to the System Table
  
  @retval EFI_SUCCESS       Execution successful
  @retval other             Error occurred

**/
EFI_STATUS
EFIAPI
MemTestMain (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS Status;
  
  TEST_START("MemTest");

  AsciiPrint("\nMemory Allocation Tests: 1..%d\n", MAX_NUM_LOOP);

  AsciiPrint("\n   Allocate/Free Pages\n");
  Status = TestAllocatePages(AllocateAnyPages, EfiBootServicesData);
  AsciiPrint("===> AllocateAnyPages, EfiBootServicesData, Status: 0x%x\n", Status);
  Status = TestAllocatePages(AllocateMaxAddress, EfiBootServicesData);
  AsciiPrint("===> AllocateMaxAddress, EfiBootServicesData, Status: 0x%x\n", Status);
  Status = TestAllocatePages(AllocateAnyPages, EfiRuntimeServicesData);
  AsciiPrint("===> AllocateAnyPages, EfiRuntimeServicesData, Status: 0x%x\n", Status);
  Status = TestAllocatePages(AllocateMaxAddress, EfiRuntimeServicesData);
  AsciiPrint("===> AllocateMaxAddress, EfiRuntimeServicesData, Status: 0x%x\n", Status);

  AsciiPrint("\n\n   Allocate/Free Pool\n");
  Status = TestAllocatePool(EfiBootServicesData);
  AsciiPrint("===> EfiBootServicesData, Status: 0x%x\n", Status);
  Status = TestAllocatePool(EfiRuntimeServicesData);
  AsciiPrint("===> EfiRuntimeServicesData, Status: 0x%x\n", Status);

  AsciiPrint("\n\nUncached Memory Allocation Tests 1..%d\n\n", MAX_NUM_LOOP);
  
  Status = TestUncachedAllocatePages();  
  AsciiPrint("===> Allocate/Free Uncached Pages, Status: 0x%x\n", Status);
  Status = TestUncachedAllocatePool();  
  AsciiPrint("===> Allocate/Free Uncached Pool, Status: 0x%x\n", Status);

  TestStatus("MemTest", Status);
  TEST_STOP("MemTest");
  return Status;
}
