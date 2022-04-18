/** @file
*
*  Copyright (c) 2014 Qualcomm Technologies, Inc. All rights reserved.
*  Copyright (c) 2011-2012, ARM Limited. All rights reserved.
*  
*  This program and the accompanying materials                          
*  are licensed and made available under the terms and conditions of the BSD License         
*  which accompanies this distribution.  The full text of the license may be found at        
*  http://opensource.org/licenses/bsd-license.php                                            
*
*  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,                     
*  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.             
*
**/

#include "BdsInternal.h"
#include "BdsLinuxLoader.h"
#include "UpdateCmdLine.h"
#include "LocateDeviceTree.h"
#include "ram_partition.h"
#include <Library/CacheMaintenanceLib.h>
#include <Library/smem.h>
#include <Library/QcomLib.h>
#include <Library/QcomBaseLib.h>

#define ALIGN32_BELOW(addr)   ALIGN_POINTER(addr - 32,32)
#include "libfdt.h"
#define BOOT_MAGIC "ANDROID!"
#define BOOT_MAGIC_SIZE 8
#define BOOT_NAME_SIZE 16
#define BOOT_ARGS_SIZE 512
#define LOCAL_ROUND_TO_PAGE(x,y) (((x) + (y - 1)) & (~(y - 1))) 

typedef struct boot_img_hdr boot_img_hdr;
INTN 
dev_tree_add_mem_info(VOID*   fdt, 
                      UINT32  offset, 
                      UINT32  addr, 
                      UINT32  size);

INTN 
dev_tree_add_mem_infoV64(VOID*   fdt, 
                         UINT32  offset, 
                         UINT64  addr, 
                         UINT64  size);

extern VOID LocateAndCopyDeviceTree (UINT8*  DeviceTreeBuff, 
                              UINT32* DeviceTreeSize, 
                              UINT32* DeviceTreeLoadAddr);

/*Struct def for boot image header*/
struct boot_img_hdr
{
    UINT8 magic[BOOT_MAGIC_SIZE];

    UINT32 kernel_size;  /* size in bytes */
    UINT32 kernel_addr;  /* physical load addr */

    UINT32 ramdisk_size; /* size in bytes */
    UINT32 ramdisk_addr; /* physical load addr */

    UINT32 second_size;  /* size in bytes */
    UINT32 second_addr;  /* physical load addr */

    UINT32 tags_addr;    /* physical addr for kernel tags */
    UINT32 page_size;    /* flash page size we assume */
    UINT32 dt_size;      /* device_tree in bytes */
    UINT32 unused;    /* future expansion: should be 0 */

    UINT8 name[BOOT_NAME_SIZE]; /* asciiz product name */
    
    UINT8 cmdline[BOOT_ARGS_SIZE];

    UINT32 id[8]; /* timestamp / checksum / sha1 / etc */
};

EFI_STATUS
HandlePartitionVer0(
  IN  VOID   *pRamPartitionTable,
  OUT UINT32 *pMemoryBase,
  OUT UINT32 *DDRMemorySize
  )
{
  EFI_STATUS Status = EFI_SUCCESS;
  UINT32 i = 0;
  usable_ram_part_table_t_v0 pRamPartTablev0;
  pRamPartTablev0 = (usable_ram_part_table_t_v0) pRamPartitionTable;

  for( i = 0; i < pRamPartTablev0->num_partitions; i++ )
  {
    /* If this is the entry for the beginning of EBI, we already use some of it for */
    /* SEC and our FD volume and some pre-allocated buffers.  So account for that memory here. */
    if ((pRamPartTablev0->ram_part_entry_v0[i].partition_type == RAM_PARTITION_SYS_MEMORY) &&
        (pRamPartTablev0->ram_part_entry_v0[i].partition_category == RAM_PARTITION_SDRAM))
    {
      /* Make sure the memory is contiguous */
      if ((*DDRMemorySize == 0) ||
          (pRamPartTablev0->ram_part_entry_v0[i].start_address == (*pMemoryBase + *DDRMemorySize)))
      {
        *DDRMemorySize += pRamPartTablev0->ram_part_entry_v0[i].length;
      }

      /* Get the lowest DDR memory base */
      if ((*pMemoryBase == 0xFFFFFFFF) ||
          (*pMemoryBase > pRamPartTablev0->ram_part_entry_v0[i].start_address))
      {
        *pMemoryBase = pRamPartTablev0->ram_part_entry_v0[i].start_address;
      }
    }
  }

  return Status;
}

EFI_STATUS
GetRamPartitionVersion (VOID *pRamPartitionTable, UINT32 *Version)
{
  /* v0 and v1 have same header info */
  usable_ram_part_table_t pRamPartTable;
  pRamPartTable = (usable_ram_part_table_t) pRamPartitionTable;

  /* First, make sure the RAM partition table is valid */
  if( pRamPartTable->magic1 == RAM_PART_MAGIC1 &&
      pRamPartTable->magic2 == RAM_PART_MAGIC2 )
  {
     *Version = pRamPartTable->version;
     return EFI_SUCCESS;
  }
  else
  {
    return EFI_NOT_FOUND;
  }
}

/*Supporting function of UpdateDeviceTree( )
 *Function adds memory map entries to the device tree binary
 *dev_tree_add_mem_info( ) is called at every time when memory type matches conditions*/
STATIC
EFI_STATUS
AddMemMap(VOID *fdt,
          UINT32 memory_node_offset,
          VOID*  pRamPartitionTable)
{
  EFI_STATUS     Status = EFI_NOT_FOUND;
  UINT32         i;
  INTN           ret = 0;
  UINT32 PartTableVer = 0;

  Status  = GetRamPartitionVersion(pRamPartitionTable, &PartTableVer);
  if (Status != EFI_SUCCESS)  /* Invalid RAM Partition, return early */
    return Status;

  /* Version 0 is 32bit, move from 32 bit to 64 bit RAM partition table */
  if (PartTableVer == 0)
  {
    usable_ram_part_table_t_v0 pRamPartTablev0;
    pRamPartTablev0 = (usable_ram_part_table_t_v0) pRamPartitionTable;

    /* First, make sure the RAM partion table is valid */
    if( pRamPartTablev0->magic1 == RAM_PART_MAGIC1 &&
        pRamPartTablev0->magic2 == RAM_PART_MAGIC2 )
    {
      Status = EFI_SUCCESS;
      for( i = 0; i < pRamPartTablev0->num_partitions; i++ )
      {
        if ((pRamPartTablev0->ram_part_entry_v0[i].partition_type == RAM_PARTITION_SYS_MEMORY) &&
            (pRamPartTablev0->ram_part_entry_v0[i].partition_category == RAM_PARTITION_SDRAM))
        {
           /* Make sure the memory is contiguous */
           ret = dev_tree_add_mem_info(fdt,
                                       memory_node_offset,
                                       pRamPartTablev0->ram_part_entry_v0[i].start_address,
                                       pRamPartTablev0->ram_part_entry_v0[i].length);

           if (ret)
           {
             DEBUG ((EFI_D_ERROR, "Failed to add secondary banks memory addresses\n"));
           }
        }
      }
    }
  }
  else
  {
    usable_ram_part_table_t pRamPartTable;

    /* Version 1 onwards should be backward compatible */ 
    pRamPartTable = (usable_ram_part_table_t) pRamPartitionTable;

    /* First, make sure the RAM partion table is valid */
    if( pRamPartTable->magic1 == RAM_PART_MAGIC1 &&
        pRamPartTable->magic2 == RAM_PART_MAGIC2 )
    {
      Status = EFI_SUCCESS;
      for( i = 0; i < pRamPartTable->num_partitions; i++ )
      {
        if ((pRamPartTable->ram_part_entry[i].partition_type == RAM_PARTITION_SYS_MEMORY) &&
            (pRamPartTable->ram_part_entry[i].partition_category == RAM_PARTITION_SDRAM))
        {
           /* Make sure the memory is contiguous */
           ret = dev_tree_add_mem_infoV64(fdt,
                                          memory_node_offset,
                                          pRamPartTable->ram_part_entry[i].start_address,
                                          pRamPartTable->ram_part_entry[i].length);

           if (ret)
           {
             DEBUG ((EFI_D_ERROR, "Failed to add secondary banks memory addresses\n"));
           }
        }
      }
    }
  }

  return Status;
}


/*Supporting function of UpdateDeviceTree( )
 *Function first gets the RAM partition table, then passes the pointer to AddMemMap( )*/
INTN
target_dev_tree_mem(VOID*   fdt, 
                    UINT32  memory_node_offset)
{
  EFI_STATUS                Status;
  VOID*   pRamPartitionTable;
  UINT32 RamPartitionBuffSz = 0;
  
  smem_init ();
  /* Get the RAM partition table */

  pRamPartitionTable = smem_get_addr(SMEM_USABLE_RAM_PARTITION_TABLE, (uint32*)&RamPartitionBuffSz);
  if (pRamPartitionTable == NULL)
  {
    /*NOTE: We should be here only if SMEM is not initialized (virtio, SmemNullLib)*/
    DEBUG ((EFI_D_ERROR, "WARNING: Unable to read memory partition table from SMEM\n"));
    DEBUG ((EFI_D_ERROR, "WARNING: Using default values from PCD !\n"));
	}
  else 
  {
    /* Get Available memory from partition table */
    Status = AddMemMap(fdt, memory_node_offset, pRamPartitionTable);
    if (EFI_ERROR(Status))
    {
      DEBUG ((EFI_D_ERROR, "Invalid memory configuration, check memory partition table\n"));
      ASSERT (Status == EFI_SUCCESS);
      CpuDeadLoop();
      return 1; /* For KW */
    }
  }
  return 0;
}
  

/*Supporting function of target_dev_tree_mem( )
 *Function to add the subsequent RAM partition info to the device tree*/
INTN 
dev_tree_add_mem_info(VOID*   fdt, 
                      UINT32  offset, 
                      UINT32  addr, 
                      UINT32  size)
{
  STATIC INTN   mem_info_cnt = 0;
  INTN          ret = 0;

  if (!mem_info_cnt)
  {
    /* Replace any other reg prop in the memory node. */
    ret = fdt_setprop_u32(fdt, offset, "reg", addr);
    mem_info_cnt = 1;
  }
  else
  {
    /* Append the mem info to the reg prop for subsequent nodes.  */
    ret = fdt_appendprop_u32(fdt, offset, "reg", addr);
  }

  if (ret)
  {
    DEBUG ((EFI_D_ERROR,"Failed to add the memory information addr: %d\n",ret));
  }


  ret = fdt_appendprop_u32(fdt, offset, "reg", size);

  if (ret)
  {
    DEBUG ((EFI_D_ERROR,"Failed to add the memory information size: %d\n",ret));
  }

  return ret;
}

INTN 
dev_tree_add_mem_infoV64(VOID*   fdt, 
                         UINT32  offset, 
                         UINT64  addr, 
                         UINT64  size)
{
  STATIC INTN   mem_info_cnt = 0;
  INTN          ret = 0;

  if (!mem_info_cnt)
  {
    /* Replace any other reg prop in the memory node. */
    ret = fdt_setprop_u64(fdt, offset, "reg", addr);
    mem_info_cnt = 1;
  }
  else
  {
    /* Append the mem info to the reg prop for subsequent nodes.  */
    ret = fdt_appendprop_u64(fdt, offset, "reg", addr);
  }

  if (ret)
  {
    DEBUG ((EFI_D_ERROR,"Failed to add the memory information addr: %d\n",ret));
  }


  ret = fdt_appendprop_u64(fdt, offset, "reg", size);

  if (ret)
  {
    DEBUG ((EFI_D_ERROR,"Failed to add the memory information size: %d\n",ret));
  }

  return ret;
}


/*Update Device Tree function, replicate functions in LK
 *Fdt functions taken off fdtlib from EDK*/
EFI_STATUS
UpdateDeviceTree(VOID*         fdt, 
                 CONST CHAR8*  cmdline, 
                 VOID*         ramdisk, 
                 UINT32        ramdisk_size)
{
  INTN        ret = 0;
  UINT32      offset;

  /* Check the device tree header */
  ret = fdt_check_header(fdt);
  if (ret)
  {
    DEBUG ((EFI_D_ERROR, "ERROR: Invalid device tree header ...\n"));
  	return ret;
  }

	/* Add padding to make space for new nodes and properties. */
  #define DTB_PAD_SIZE          1024

  ret = fdt_open_into(fdt, fdt, fdt_totalsize(fdt) + DTB_PAD_SIZE);
  if (ret!= 0)
  {
    DEBUG ((EFI_D_ERROR, "ERROR: Failed to move/resize dtb buffer ...\n"));
  	return ret;
  }

	/* Get offset of the memory node */
  ret = fdt_path_offset(fdt, "/memory");
  if (ret < 0)
  {
    DEBUG ((EFI_D_ERROR, "ERROR: Could not find memory node ...\n"));
  	return ret;
  }

  offset = ret;
  
  ret = target_dev_tree_mem(fdt, offset);
  if(ret)
  {
    DEBUG ((EFI_D_ERROR, "ERROR: Cannot update memory node\n"));
  	return ret;
  }

  /* Get offset of the chosen node */
  ret = fdt_path_offset(fdt, "/chosen");
  if (ret < 0)
  {
    DEBUG ((EFI_D_ERROR, "ERROR: Could not find chosen node ...\n"));
  	return ret;
  }

  offset = ret;
  /* Adding the cmdline to the chosen node */
  ret = fdt_setprop_string(fdt, offset, (CONST char*)"bootargs", (CONST VOID*)cmdline);
  if (ret)
  {
    DEBUG ((EFI_D_ERROR, "ERROR: Cannot update chosen node [bootargs] ...\n"));
  	return ret;
  }

  /* Adding the initrd-start to the chosen node */
  ret = fdt_setprop_u32(fdt, offset, "linux,initrd-start", (UINT32)ramdisk);
  if (ret)
  {
    DEBUG ((EFI_D_ERROR, "ERROR: Cannot update chosen node [linux,initrd-start] ...\n"));
  	return ret;
  }

	/* Adding the initrd-end to the chosen node */
  ret = fdt_setprop_u32(fdt, offset, "linux,initrd-end", ((UINT32)ramdisk + ramdisk_size));
  if (ret)
  {
    DEBUG ((EFI_D_ERROR, "ERROR: Cannot update chosen node [linux,initrd-end] ...\n"));
  	return ret;
  }

  fdt_pack(fdt);

  return ret;
}

STATIC
EFI_STATUS
PreparePlatformHardware (
  VOID
  )
{
  ArmDisableBranchPrediction();

  DisableInterrupts();

  // Clean, invalidate, disable data cache
  WriteBackInvalidateDataCache();
  InvalidateInstructionCache();

  ArmDisableDataCache ();
  ArmDisableInstructionCache ();
  ArmDisableMmu ();
  
  return EFI_SUCCESS;
}

/*Loading Linux Kernel directly from UEFI*/
STATIC
EFI_STATUS
StartLinux (volatile UINT8*  BootImgBuff,
            volatile UINT32  BootImageSize)
{
  EFI_STATUS            Status;
  LINUX_KERNEL          LinuxKernel;
  UINT8*                Final_CmdLine;
  STATIC UINT32         NumPages; 
  STATIC UINT32         DeviceTreeOffset;
  STATIC UINT32         RamdiskOffset;
  STATIC UINT32         KernelSizeActual;
  STATIC UINT32         RamdiskSizeActual;
  STATIC UINT32         SecondSizeActual; 

  STATIC EFI_PHYSICAL_ADDRESS  *Memory;

  /*Boot Image header information variables*/
  STATIC UINT32         KernelSize;
  STATIC UINT32*        KernelLoadAddr; 
  STATIC UINT32         RamdiskSize;
  STATIC UINT32*        RamdiskLoadAddr; 
  STATIC UINT32         SecondSize;
  //STATIC UINT32*        SecondLoadAddr;
  STATIC UINT32*        DeviceTreeLoadAddr = 0; 
  STATIC UINT32         PageSize = 0;
  STATIC UINT32         DeviceTreeSize = 0;
  STATIC UINT32*        CmdLine;
  
  UINT8* mBootImgBuff = (UINT8*)BootImgBuff;
  EFI_PHYSICAL_ADDRESS MemoryBuffer;
  
  /*Device tree, ramdisk, kernel loading addresses and sizes all reside in boot image header
   *SecondSize and SecondLoadAddr were not used, but kept in case of future use*/  
  KernelSize = ((boot_img_hdr*)(BootImgBuff))->kernel_size;
  KernelLoadAddr = (UINT32*)((boot_img_hdr*)(BootImgBuff))->kernel_addr;
  RamdiskSize = ((boot_img_hdr*)(BootImgBuff))->ramdisk_size;
  RamdiskLoadAddr = (UINT32*)((boot_img_hdr*)(BootImgBuff))->ramdisk_addr;
  SecondSize = ((boot_img_hdr*)(BootImgBuff))->second_size;
  //SecondLoadAddr = (UINT32*)((boot_img_hdr*)(BootImgBuff))->second_addr;
  DeviceTreeLoadAddr = (UINT32*)((boot_img_hdr*)(BootImgBuff))->tags_addr;
  PageSize = ((boot_img_hdr*)(BootImgBuff))->page_size;
  DeviceTreeSize = ((boot_img_hdr*)(BootImgBuff))->dt_size;
  CmdLine = (UINT32*)&(((boot_img_hdr*)(BootImgBuff))->cmdline[0]);

  /*Allocate Page for boot image at 0x8000 and copy image to it*/ 
  MemoryBuffer = (EFI_PHYSICAL_ADDRESS)(0x0 | (UINT32)KernelLoadAddr);
  Memory = &MemoryBuffer;
  NumPages = KernelSize /(4*1024);
  Status = gBS->AllocatePages (AllocateAddress, EfiRuntimeServicesCode, NumPages, Memory);
  if (EFI_ERROR(Status) || (Memory == NULL)) 
  {
    DEBUG((EFI_D_ERROR,"ERROR: Boot Image Allocation Failed Status=0x%X\n", Status));
    goto Exit;
  }  

  CopyMem (KernelLoadAddr, mBootImgBuff + PageSize, KernelSize);

  /*Finds out the location of device tree image and ramdisk image within the boot image
   *Kernel, Ramdisk and Second sizes all rounded to page
   *The offset and the LOCAL_ROUND_TO_PAGE function is written in a way that it is done the same in LK*/
  KernelSizeActual = LOCAL_ROUND_TO_PAGE (KernelSize, PageSize);
  RamdiskSizeActual = LOCAL_ROUND_TO_PAGE (RamdiskSize, PageSize);
  SecondSizeActual = LOCAL_ROUND_TO_PAGE (SecondSize, PageSize);
  
  /*Offsets are the location of the images within the boot image*/
  RamdiskOffset = PageSize + KernelSizeActual;
  DeviceTreeOffset = PageSize + KernelSizeActual + RamdiskSizeActual + SecondSizeActual;
 

#if 0
  /*Copy Ramdisk image to 0x2000000
   *AllocatePage is experiencing incompatible memory error, awaits fix*/
  Memory = RamdiskLoadAddr;
  NumPages = RamdiskSize/(4*1024);
  Status = gBS->AllocatePages (AllocateAddress, EfiRuntimeServicesCode, NumPages, Memory);
  if (EFI_ERROR(Status) || (Memory == NULL)) 
  {
    DEBUG((EFI_D_ERROR,"ERROR: Ramdisk Image Allocation Failed Status=0x%X\n", Status));
    goto Exit;
  }  
#endif
  CopyMem (RamdiskLoadAddr, mBootImgBuff + RamdiskOffset, RamdiskSize);

  /*Updates the command line from boot image, appends device serial no., baseband information, etc
   *Called before ShutdownUefiBootServices as it uses some boot service functions*/
  Final_CmdLine = update_cmdline ((CHAR8*)CmdLine);

  /*Function below is given the location of device tree within boot image
   *It finds where the device tree for the current platform is, and loads to memory*/
  LocateAndCopyDeviceTree (mBootImgBuff + DeviceTreeOffset, &DeviceTreeSize, DeviceTreeLoadAddr);
  UpdateDeviceTree((VOID*)DeviceTreeLoadAddr , (CHAR8*)Final_CmdLine, RamdiskLoadAddr, RamdiskSize);

  /*Shut down UEFI boot services*/
  Status = ShutdownUefiBootServices ();
  if(EFI_ERROR(Status)) {
    DEBUG((EFI_D_ERROR,"ERROR: Can not shutdown UEFI boot services. Status=0x%X\n", Status));
    goto Exit;
  }
 
  //
  // Start the Linux Kernel, loaded at 0x8000
  //
  LinuxKernel = (LINUX_KERNEL)(UINTN)KernelLoadAddr;
  DEBUG((EFI_D_ERROR, "\nStarting the kernel ...\n\n"));
  Status = PreparePlatformHardware ();
  ASSERT_EFI_ERROR(Status);
  LinuxKernel ((UINTN)0, 0xFFFFFFFF, (UINTN)DeviceTreeLoadAddr);

  // Kernel should never exit
  // After Life services are not provided
  ASSERT(FALSE);

Exit:
  // Only be here if we fail to start Linux
  Print (L"ERROR  : Can not start the kernel. Status=0x%X\n", Status);

  // Free Runtimee Memory (kernel and FDT)
  return Status;
}

#if 0
STATIC
EFI_STATUS
StartLinux (
  IN  EFI_PHYSICAL_ADDRESS  LinuxImage,
  IN  UINTN                 LinuxImageSize,
  IN  EFI_PHYSICAL_ADDRESS  KernelParamsAddress,
  IN  UINTN                 KernelParamsSize,
  IN  UINT32                MachineType
  )
{
  EFI_STATUS            Status;
  LINUX_KERNEL          LinuxKernel;

  // Shut down UEFI boot services. ExitBootServices() will notify every driver that created an event on
  // ExitBootServices event. Example the Interrupt DXE driver will disable the interrupts on this event.
  Status = ShutdownUefiBootServices ();
  if(EFI_ERROR(Status)) {
    DEBUG((EFI_D_ERROR,"ERROR: Can not shutdown UEFI boot services. Status=0x%X\n", Status));
    goto Exit;
  }

  // Move the kernel parameters to any address inside the first 1MB.
  // This is necessary because the ARM Linux kernel requires
  // the FTD / ATAG List to reside entirely inside the first 1MB of
  // physical memory.
  //Note: There is no requirement on the alignment
  if (MachineType != ARM_FDT_MACHINE_TYPE) {
    if (((UINTN)KernelParamsAddress > LINUX_ATAG_MAX_OFFSET) && (KernelParamsSize < PcdGet32(PcdArmLinuxAtagMaxOffset))) {
      KernelParamsAddress = (EFI_PHYSICAL_ADDRESS)(UINTN)CopyMem (ALIGN32_BELOW(LINUX_ATAG_MAX_OFFSET - KernelParamsSize), (VOID*)(UINTN)KernelParamsAddress, KernelParamsSize);
    }
  } else {
    if (((UINTN)KernelParamsAddress > LINUX_FDT_MAX_OFFSET) && (KernelParamsSize < PcdGet32(PcdArmLinuxFdtMaxOffset))) {
      KernelParamsAddress = (EFI_PHYSICAL_ADDRESS)(UINTN)CopyMem (ALIGN32_BELOW(LINUX_FDT_MAX_OFFSET - KernelParamsSize), (VOID*)(UINTN)KernelParamsAddress, KernelParamsSize);
    }
  }

  if ((UINTN)LinuxImage > LINUX_KERNEL_MAX_OFFSET) {
    //Note: There is no requirement on the alignment
    LinuxKernel = (LINUX_KERNEL)CopyMem (ALIGN32_BELOW(LINUX_KERNEL_MAX_OFFSET - LinuxImageSize), (VOID*)(UINTN)LinuxImage, LinuxImageSize);
  } else {
    LinuxKernel = (LINUX_KERNEL)(UINTN)LinuxImage;
  }

  // Check if the Linux Image is a uImage
  if (*(UINT32*)LinuxKernel == LINUX_UIMAGE_SIGNATURE) {
    // Assume the Image Entry Point is just after the uImage header (64-byte size)
    LinuxKernel = (LINUX_KERNEL)((UINTN)LinuxKernel + 64);
    LinuxImageSize -= 64;
  }

  //TODO: Check there is no overlapping between kernel and Atag

  //
  // Switch off interrupts, caches, mmu, etc
  //
  Status = PreparePlatformHardware ();
  ASSERT_EFI_ERROR(Status);

  // Register and print out performance information
  PERF_END (NULL, "BDS", NULL, 0);
  if (PerformanceMeasurementEnabled ()) {
    PrintPerformance ();
  }

  //
  // Start the Linux Kernel
  //

  // Outside BootServices, so can't use Print();
  DEBUG((EFI_D_ERROR, "\nStarting the kernel:\n\n"));

  // Jump to kernel with register set
  LinuxKernel ((UINTN)0, MachineType, (UINTN)KernelParamsAddress);

  // Kernel should never exit
  // After Life services are not provided
  ASSERT(FALSE);

Exit:
  // Only be here if we fail to start Linux
  Print (L"ERROR  : Can not start the kernel. Status=0x%X\n", Status);

  // Free Runtimee Memory (kernel and FDT)
  return Status;
}

/**
  Start a Linux kernel from a Device Path

  @param  LinuxKernel           Device Path to the Linux Kernel
  @param  Parameters            Linux kernel arguments
  @param  Fdt                   Device Path to the Flat Device Tree

  @retval EFI_SUCCESS           All drivers have been connected
  @retval EFI_NOT_FOUND         The Linux kernel Device Path has not been found
  @retval EFI_OUT_OF_RESOURCES  There is not enough resource memory to store the matching results.

**/
EFI_STATUS
BdsBootLinuxAtag (
  IN  EFI_DEVICE_PATH_PROTOCOL* LinuxKernelDevicePath,
  IN  EFI_DEVICE_PATH_PROTOCOL* InitrdDevicePath,
  IN  CONST CHAR8*              CommandLineArguments
  )
{
  EFI_STATUS            Status;
  UINT32                LinuxImageSize;
  UINT32                InitrdImageBaseSize = 0;
  UINT32                InitrdImageSize = 0;
  UINT32                AtagSize;
  EFI_PHYSICAL_ADDRESS  AtagBase;
  EFI_PHYSICAL_ADDRESS  LinuxImage;
  EFI_PHYSICAL_ADDRESS  InitrdImageBase = 0;
  EFI_PHYSICAL_ADDRESS  InitrdImage = 0;

  PERF_START (NULL, "BDS", NULL, 0);

  // Load the Linux kernel from a device path
  LinuxImage = LINUX_KERNEL_MAX_OFFSET;
  Status = BdsLoadImage (LinuxKernelDevicePath, AllocateMaxAddress, &LinuxImage, &LinuxImageSize);
  if (EFI_ERROR(Status)) {
    Print (L"ERROR: Did not find Linux kernel.\n");
    return Status;
  }

  if (InitrdDevicePath) {
    // Load the initrd near to the Linux kernel
    InitrdImageBase = LINUX_KERNEL_MAX_OFFSET;
    Status = BdsLoadImage (InitrdDevicePath, AllocateMaxAddress, &InitrdImageBase, &InitrdImageBaseSize);
    if (Status == EFI_OUT_OF_RESOURCES) {
      Status = BdsLoadImage (InitrdDevicePath, AllocateAnyPages, &InitrdImageBase, &InitrdImageBaseSize);
    }
    if (EFI_ERROR(Status)) {
      Print (L"ERROR: Did not find initrd image.\n");
      goto EXIT_FREE_LINUX;
    }
    
    // Check if the initrd is a uInitrd
    if (*(UINT32*)((UINTN)InitrdImageBase) == LINUX_UIMAGE_SIGNATURE) {
      // Skip the 64-byte image header
      InitrdImage = (EFI_PHYSICAL_ADDRESS)((UINTN)InitrdImageBase + 64);
      InitrdImageSize = InitrdImageBaseSize - 64;
    } else {
      InitrdImage = InitrdImageBase;
      InitrdImageSize = InitrdImageBaseSize;
    }
  }

  //
  // Setup the Linux Kernel Parameters
  //
 
  // By setting address=0 we leave the memory allocation to the function
  Status = PrepareAtagList (CommandLineArguments, InitrdImage, InitrdImageSize, &AtagBase, &AtagSize);
  if (EFI_ERROR(Status)) {
    Print(L"ERROR: Can not prepare ATAG list. Status=0x%X\n", Status);
    goto EXIT_FREE_INITRD;
  }

  return StartLinux (LinuxImage, LinuxImageSize, AtagBase, AtagSize, PcdGet32(PcdArmMachineType));

EXIT_FREE_INITRD:
  if (InitrdDevicePath) {
    gBS->FreePages (InitrdImageBase, EFI_SIZE_TO_PAGES (InitrdImageBaseSize));
  }

EXIT_FREE_LINUX:
  gBS->FreePages (LinuxImage, EFI_SIZE_TO_PAGES (LinuxImageSize));

  return Status;
}

/**
  Start a Linux kernel from a Device Path

  @param  LinuxKernel           Device Path to the Linux Kernel
  @param  Parameters            Linux kernel arguments
  @param  Fdt                   Device Path to the Flat Device Tree

  @retval EFI_SUCCESS           All drivers have been connected
  @retval EFI_NOT_FOUND         The Linux kernel Device Path has not been found
  @retval EFI_OUT_OF_RESOURCES  There is not enough resource memory to store the matching results.

**/
EFI_STATUS
BdsBootLinuxFdt (
  IN  EFI_DEVICE_PATH_PROTOCOL* LinuxKernelDevicePath,
  IN  EFI_DEVICE_PATH_PROTOCOL* InitrdDevicePath,
  IN  CONST CHAR8*              CommandLineArguments,
  IN  EFI_DEVICE_PATH_PROTOCOL* FdtDevicePath
  )
{
  EFI_STATUS            Status;
  UINT32                LinuxImageSize;
  UINT32                InitrdImageBaseSize = 0;
  UINT32                InitrdImageSize = 0;
  UINT32                FdtBlobSize;
  EFI_PHYSICAL_ADDRESS  FdtBlobBase;
  EFI_PHYSICAL_ADDRESS  LinuxImage;
  EFI_PHYSICAL_ADDRESS  InitrdImageBase = 0;
  EFI_PHYSICAL_ADDRESS  InitrdImage = 0;

  PERF_START (NULL, "BDS", NULL, 0);

  // Load the Linux kernel from a device path
  LinuxImage = LINUX_KERNEL_MAX_OFFSET;
  Status = BdsLoadImage (LinuxKernelDevicePath, AllocateMaxAddress, &LinuxImage, &LinuxImageSize);
  if (EFI_ERROR(Status)) {
    Print (L"ERROR: Did not find Linux kernel.\n");
    return Status;
  }

  if (InitrdDevicePath) {
    InitrdImageBase = LINUX_KERNEL_MAX_OFFSET;
    Status = BdsLoadImage (InitrdDevicePath, AllocateMaxAddress, &InitrdImageBase, &InitrdImageBaseSize);
    if (Status == EFI_OUT_OF_RESOURCES) {
      Status = BdsLoadImage (InitrdDevicePath, AllocateAnyPages, &InitrdImageBase, &InitrdImageBaseSize);
    }
    if (EFI_ERROR(Status)) {
      Print (L"ERROR: Did not find initrd image.\n");
      goto EXIT_FREE_LINUX;
    }

    // Check if the initrd is a uInitrd
    if (*(UINT32*)((UINTN)InitrdImageBase) == LINUX_UIMAGE_SIGNATURE) {
      // Skip the 64-byte image header
      InitrdImage = (EFI_PHYSICAL_ADDRESS)((UINTN)InitrdImageBase + 64);
      InitrdImageSize = InitrdImageBaseSize - 64;
    } else {
      InitrdImage = InitrdImageBase;
      InitrdImageSize = InitrdImageBaseSize;
    }
  }

  // Load the FDT binary from a device path. The FDT will be reloaded later to a more appropriate location for the Linux kernel.
  FdtBlobBase = 0;
  Status = BdsLoadImage (FdtDevicePath, AllocateAnyPages, &FdtBlobBase, &FdtBlobSize);
  if (EFI_ERROR(Status)) {
    Print (L"ERROR: Did not find Device Tree blob.\n");
    goto EXIT_FREE_INITRD;
  }

  // Update the Fdt with the Initrd information. The FDT will increase in size.
  // By setting address=0 we leave the memory allocation to the function
  Status = PrepareFdt (CommandLineArguments, InitrdImage, InitrdImageSize, &FdtBlobBase, &FdtBlobSize);
  if (EFI_ERROR(Status)) {
    Print(L"ERROR: Can not load kernel with FDT. Status=%r\n", Status);
    goto EXIT_FREE_FDT;
  }

  return StartLinux (LinuxImage, LinuxImageSize, FdtBlobBase, FdtBlobSize, ARM_FDT_MACHINE_TYPE);

EXIT_FREE_FDT:
  gBS->FreePages (FdtBlobBase, EFI_SIZE_TO_PAGES (FdtBlobSize));

EXIT_FREE_INITRD:
  if (InitrdDevicePath) {
    gBS->FreePages (InitrdImageBase, EFI_SIZE_TO_PAGES (InitrdImageBaseSize));
  }

EXIT_FREE_LINUX:
  gBS->FreePages (LinuxImage, EFI_SIZE_TO_PAGES (LinuxImageSize));

  return Status;
}
#endif


STATIC EFI_GUID BootImgPartitionType = 
  { 0x20117f86, 0xe985, 0x4357, { 0xb9, 0xee, 0x37, 0x4b, 0xc1, 0xd8, 0x48, 0x7d } };
  
/*Loads Boot image from partition to buffer, and calls StartLinux function*/
EFI_STATUS
BdsBootLinuxFromPartition (VOID)
{
  EFI_STATUS                   Status;
  EFI_BLOCK_IO_PROTOCOL       *BlkIo;
//  EFI_GUID                    *PartitionType; 
//  EFI_GUID                    *RootDeviceType; 
  PartiSelectFilter            HandleFilter;
  HandleInfo                   HandleInfoList[1];
  STATIC UINT32                MaxHandles;
  STATIC UINT32               *BootImageBuffer;
  STATIC UINT32                BootImageSize;
  STATIC UINT32                BlkIOAttrib = 0;
  
  BlkIOAttrib = BLK_IO_SEL_PARTITIONED_MBR;
  BlkIOAttrib |= BLK_IO_SEL_PARTITIONED_GPT;
  BlkIOAttrib |= BLK_IO_SEL_MEDIA_TYPE_NON_REMOVABLE;
  BlkIOAttrib |= BLK_IO_SEL_MATCH_PARTITION_TYPE_GUID;
  
  HandleFilter.RootDeviceType = NULL;
  HandleFilter.PartitionType = &BootImgPartitionType;
  HandleFilter.VolumeName = 0;

  DEBUG ((DEBUG_ERROR, "Loading BootImage: %d\n",
                      GetTimerCountms ()));

  MaxHandles = sizeof(HandleInfoList)/sizeof(*HandleInfoList);

  /*Get BlockIO handle for "boot" partition*/
  Status = GetBlkIOHandles (BlkIOAttrib, &HandleFilter, HandleInfoList, &MaxHandles);

  if(Status == EFI_SUCCESS) {
    if(MaxHandles == 0)
      return EFI_NO_MEDIA;

    if(MaxHandles != 1) {
      //Unable to deterministically load from single partition
      DEBUG(( EFI_D_INFO, "ExecImgFromVolume(): multiple partitions found.\r\n"));
      return EFI_LOAD_ERROR;
    }
  } 

  #define   BLOCK_SIZE     512
  BlkIo = HandleInfoList[0].BlkIo;
  BootImageSize = (UINT32)(BlkIo->Media->LastBlock + 1) * BLOCK_SIZE;
  BootImageBuffer = AllocatePool (BootImageSize);

  Status = BlkIo->ReadBlocks (BlkIo, 
                              BlkIo->Media->MediaId, 
                              0, 
                              BootImageSize, 
                              BootImageBuffer);
  DEBUG ((DEBUG_ERROR, "Done Loading BootImage: %d\n",
                      GetTimerCountms ()));
                      
  return StartLinux((UINT8*)BootImageBuffer, BootImageSize);
  
}

extern EFI_GUID gEfiSdRemovableGuid;
EFI_STATUS
BdsBootLinuxFromFile (VOID)
{
  CHAR16 BootImgFileName[64];

  UINT32           BlkIOAttrib = 0, FileSize = 0;
  EFI_STATUS       Status;
  UINT8*           FileBuffer;

  // Set attributes for fetching Block IO handle
  BlkIOAttrib = BLK_IO_SEL_PARTITIONED_MBR;
  BlkIOAttrib |= BLK_IO_SEL_PARTITIONED_GPT;
  BlkIOAttrib |= BLK_IO_SEL_MEDIA_TYPE_REMOVABLE;
  BlkIOAttrib |= BLK_IO_SEL_SELECT_MOUNTED_FILESYSTEM;

  AsciiStrToUnicodeStr ("boot.img", BootImgFileName);

  DEBUG ((DEBUG_ERROR, "Loading BootImage: %d\n",
                      GetTimerCountms ()));

    // Load Menu config file into buffer
  // Attempt to load from removable card if one is existing
  Status = LoadFileFromPartition(BlkIOAttrib,
                                 BootImgFileName,
                                 &gEfiSdRemovableGuid,
                                 NULL,
                                 &FileBuffer, &FileSize);

  DEBUG ((DEBUG_ERROR, "Done Loading BootImage: %d\n",
                      GetTimerCountms ()));
  if (Status != EFI_SUCCESS)
  {
    DEBUG((EFI_D_ERROR, "Could not open boot.img\r\n"));
    return EFI_LOAD_ERROR;
  }

  return StartLinux(FileBuffer, FileSize);
}

