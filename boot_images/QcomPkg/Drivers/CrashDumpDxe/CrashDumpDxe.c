/** @file CrashDumpDxe.c
   
  Code for reset reason feature for retail devices

  Copyright (c) 2012-2016 Qualcomm Technologies, Inc. 
  All rights reserved.

**/

/*=============================================================================
                              EDIT HISTORY
  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.



  when        who       what, where, why
  --------    ---       ----------------------------------------------------------
  02/10/2016  na        check DbiDumpTable DDR Base from cfg file rather than FdRegion
  07/29/2015  ao        bring in crash Dump related code from Sec.c
  12/11/2014  ao        update with new SPMI API
  08/15/2014  sm        Switched to new SCM API
  07/09/2014  shireesh  Added pmic PON_PBL_STATUS register to reset data buffer
  06/06/2014  vk        Fix crash in 64 bit
  04/29/2014  shireesh  Added support for h/w button trigerd reset detection
  03/26/2014  shireesh  Initial version
  
=============================================================================*/

#include <Uefi.h>
#include <Library/DebugLib.h>
#include <Library/PcdLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UncachedMemoryAllocationLib.h>
#include <Library/UefiLib.h>
#include <Library/PrintLib.h>
#include <Library/BaseLib.h>
#include <Include/UefiInfoBlk.h>
#include <Library/QcomLib.h>
#include <Library/DBIDump.h>
#include <Library/OfflineCrashDump.h>
#include <Library/QcomBaseLib.h>
#include <Library/UefiCfgLib.h>
#include <Protocol/EFIScm.h>
#include <Include/scm_sip_interface.h>
#include <Protocol/EFIChipInfo.h>
#include <Protocol/EFIPmicPwrOn.h>
#include <Protocol/EFISPMI.h>
#include <Library/HobLib.h>
#include <Library/RamPartitionTableLib.h>
#include <Library/IoLib.h>

STATIC EFI_OFFLINE_CRASHDUMP_CONFIG_TABLE * OfflineCrashDumpConfigTable = NULL;

/**
  Function make syscall to TZ to provide buffer address to copy diag data

**/
STATIC
BOOLEAN
EFIAPI
TZResetDiagDataBufferAddressSysCall(VOID* address, UINTN size)
{ 
  EFI_STATUS        Status;
  BOOLEAN           SysCallStatus     = FALSE;
  QCOM_SCM_PROTOCOL *pQcomScmProtocol = NULL;
  UINT64            Parameters[SCM_MAX_NUM_PARAMETERS] = {0};
  UINT64            Results[SCM_MAX_NUM_RESULTS] = {0};
  tz_set_address_to_dump_tz_diag_for_uefi_req_t *SysCallReq = (tz_set_address_to_dump_tz_diag_for_uefi_req_t*)Parameters;
  tz_syscall_rsp_t *SysCallRsp = (tz_syscall_rsp_t*)Results;
  
  
  /* Initializing cmd structure for SCM sys call */
  SysCallReq->size        = size;
  SysCallReq->addr        = (UINTN)address;

  /* Locate QCOM_SCM_PROTOCOL */
  Status = gBS->LocateProtocol ( &gQcomScmProtocolGuid, NULL, (VOID **)&pQcomScmProtocol);
  if( EFI_ERROR(Status)) 
  {
    DEBUG(( EFI_D_ERROR, " Locate SCM Protocol failed, Status =  (0x%x)\r\n", Status));
    goto ErrorExit;
  }

  /* Make a SCM Sys call */
  Status = pQcomScmProtocol->ScmSipSysCall (pQcomScmProtocol,
                                            TZ_DUMP_SET_ADDRESS_TO_DUMP_TZ_DIAG_FOR_UEFI,
                                            TZ_DUMP_SET_ADDRESS_TO_DUMP_TZ_DIAG_FOR_UEFI_PARAM_ID,
                                            Parameters,
                                            Results
                                            );
  if (EFI_ERROR (Status)) 
  {
    DEBUG(( EFI_D_ERROR, "ScmSipSysCall() failed, Status = (0x%x)\r\n", Status));
    goto ErrorExit;
  }
  if (SysCallRsp->status != 1)
  {    
    DEBUG(( EFI_D_ERROR, "TZ_DUMP_SET_ADDRESS_TO_DUMP_TZ_DIAG_FOR_UEFI failed, Status = (0x%x)\r\n", SysCallRsp->status));
    goto ErrorExit;
  }

  SysCallStatus = TRUE;

ErrorExit:
  return SysCallStatus;
}

/**
  Function to get offlinedump Config table

**/
EFIAPI
EFI_STATUS
GetCrashDumpConfigTable( VOID )
{
  EFI_STATUS Status = EFI_SUCCESS;

  Status = EfiGetSystemConfigurationTable(&gEfiOfflineCrashDumpConfigTableGuid, (VOID**)&OfflineCrashDumpConfigTable);
  if (Status != EFI_SUCCESS) 
  {
    DEBUG(( EFI_D_ERROR, "Offline Crash Dump Config Table does not exist in System Configuration Table\r\n"));
    return EFI_NOT_FOUND;
  }

  return EFI_SUCCESS;
}

/**
 This function intializes Offline Crash Dump Config table fields for reset reason

**/
STATIC
EFI_STATUS
EFIAPI
InitializeResetDataBuffers ( EFI_OFFLINE_CRASHDUMP_CONFIG_TABLE *mOfflineCrashDumpConfigTable )
{
  EFI_STATUS    Status;
  MemRegionInfo ResetDataRegionInfo;
  volatile UINT32 RegDump;
  
  CHAR8* UefiResetBufferAddress = NULL;
  VOID* tzBufferAddress = 0;
  RESET_DATA_HEADER *mResetReasonData = NULL;
  EFI_QCOM_SPMI_PROTOCOL *pSPMI = NULL;
  Spmi_Result result = SPMI_SUCCESS;
  EFI_CHIPINFO_PROTOCOL *pChipInf;
  UINT64 *GCCResetValueAddress = NULL;

  const CHAR8 GccStr[]               = "GCC_RESET_STATUS=";
  const CHAR8 PONReason1Str[]        = "PON_REASON1=";	
  const CHAR8 PONWarmReset1Str[]     = "PON_WARM_RESET_REASON1=";  
  const CHAR8 PONWarmReset2Str[]     = "PON_WARM_RESET_REASON2=";	
  const CHAR8 POFF1Str[]             = "POFF_REASON1=";	
  const CHAR8 POFF2Str[]             = "POFF_REASON2=";
  const CHAR8 PONPBL2Str[]           = "PON_PBL_STATUS=";

  /* UEFI total reset data size in bytes */
  UINT64 UefiResetDataSize = AsciiStrLen(GccStr)+AsciiStrLen(PONReason1Str)+AsciiStrLen(PONWarmReset1Str)+AsciiStrLen(PONWarmReset2Str)+AsciiStrLen(GccStr)+AsciiStrLen(POFF1Str)+AsciiStrLen(POFF2Str)+ 6* sizeof(UINT64);

  /* Get the Reset Data memory region. */
  Status = GetMemRegionInfoByName("Reset Data", &ResetDataRegionInfo);
  if (Status != EFI_SUCCESS)
  {
    DEBUG((EFI_D_ERROR, " Could not find the Reset Data region .\r\n"));
    return Status;
  }
  
  mResetReasonData = (RESET_DATA_HEADER*) ((UINTN)ResetDataRegionInfo.MemBase);

  /* Initialize reset reason data structure*/
  mResetReasonData->Version = RESET_DATA_HEADER_VERSION;
  
  Status = gBS->LocateProtocol (&gEfiChipInfoProtocolGuid, NULL, (VOID **) &pChipInf);
  if (EFI_SUCCESS != Status)
  { 
     return Status;
  }

  if (EFI_SUCCESS != pChipInf->GetChipIdString(pChipInf, mResetReasonData->PlatformID, PLATFORMID_MAX_LENGTH))
  {
    DEBUG ((EFI_D_WARN, "gEfiChipInfoProtocolGuid->GetChipIdString() Failed. \n"));
    Status = EFI_UNSUPPORTED;
    return Status;
  }
  
  mResetReasonData->Guid                        = gQcomResetReasonDataCaptureGuid;
  /* Size of datbuffer+header */
  mResetReasonData->ResetDataBufferSize         = sizeof(RESET_DATA_BUFFER);       
  mResetReasonData->ResetDataBuffer.Version     = RESET_DATA_BUFFER_VERSION;
  
  /* Offset from reset data header to tz data buffer */
  mResetReasonData->ResetDataBuffer.DataOffset1 = sizeof(RESET_DATA_HEADER) - QCDATA_1_SIZE - QCDATA_2_SIZE;
  mResetReasonData->ResetDataBuffer.DataSize1   = QCDATA_1_SIZE;

  /* Offset from reset data header to UEFI data buffer */
  mResetReasonData->ResetDataBuffer.DataOffset2 = mResetReasonData->ResetDataBuffer.DataOffset1 + QCDATA_1_SIZE;
  mResetReasonData->ResetDataBuffer.DataSize2   = QCDATA_2_SIZE;


  /* Setup buffer address for TZ to dump to within Reset Data region */
  tzBufferAddress = (UINT8*)mResetReasonData + (UINTN)mResetReasonData->ResetDataBuffer.DataOffset1;
  TZResetDiagDataBufferAddressSysCall(tzBufferAddress, QCDATA_1_SIZE);

  mOfflineCrashDumpConfigTable->ResetDataAddress = (UINT64)mResetReasonData;
  mOfflineCrashDumpConfigTable->ResetDataSize    = sizeof(RESET_DATA_HEADER);
  
  /* Return if there is not enough room for all data */
  if ( UefiResetDataSize > QCDATA_2_SIZE )
  { 
     return EFI_OUT_OF_RESOURCES;
  }
  
  /* Sets up UefiResetBufferAddress to point to just after TZ buffer */
  UefiResetBufferAddress = (CHAR8*)((UINTN)tzBufferAddress + QCDATA_1_SIZE);
    
  /* Fill in version as first field in UEFI buffer */
  *((UINT64*)UefiResetBufferAddress) = RESET_DATA2_VERSION;
    
  /* Copy GCC reset string to UEFI data buffer */
  UefiResetBufferAddress = UefiResetBufferAddress + sizeof(UINT64);
  AsciiStrCpy(UefiResetBufferAddress, GccStr);
  UefiResetBufferAddress = (CHAR8*)( (UINTN)UefiResetBufferAddress + AsciiStrLen(GccStr));
    
  /* Copy GCC reset from SMEM to UEFI data buffer */
  /* Get location of where GCC reset reason is backed up */
  Status = GetConfigValue("GCCResetValueAddress", (UINT32*)&GCCResetValueAddress);
  if (Status != EFI_SUCCESS)
  {
      DEBUG(( EFI_D_ERROR, "Could not get address from uefiplat.cfg to read GCC Reset Value, Status = (0x%x)\r\n", Status));
      return Status;
  }

  RegDump = *((UINT32*)GCCResetValueAddress) & 0x0FE;

  AsciiValueToString ((UefiResetBufferAddress), 0, (UINT64)RegDump, 8);
  UefiResetBufferAddress = UefiResetBufferAddress + sizeof(UINT64);

  /* Write PMIC registers to reset data buffer */

  /* Get SPMI Protocol */
  Status = gBS->LocateProtocol(&gQcomSPMIProtocolGuid, NULL, (VOID **) &pSPMI);
  if ( EFI_ERROR (Status) )
  {
      DEBUG(( EFI_D_ERROR, "MemMapDump: failed to locate SPMIProtocol, Status = (0x%x)\r\n", Status));
      return Status;
  }

  /* Read and write PON_REASON1 register to buffer */
  result = pSPMI->ReadLong(pSPMI, 0, SPMI_BUS_ACCESS_PRIORITY_LOW, PON_REASON1, (UINT8*)&RegDump, (UINT32)1,0);
  if ( result != SPMI_SUCCESS )
  {
      DEBUG(( EFI_D_ERROR, "Read to PON_REASON1 register failed, Status = (0x%x)\r\n", result));
  }
    
  AsciiStrCpy(UefiResetBufferAddress, PONReason1Str);    
  UefiResetBufferAddress = (CHAR8*)( (UINTN)UefiResetBufferAddress + AsciiStrLen(PONReason1Str));
  AsciiValueToString ((UefiResetBufferAddress), 0, (UINT64)RegDump, 8);
  UefiResetBufferAddress=UefiResetBufferAddress+sizeof(UINT64);
  
  /* Read and write PON_WARM_RESET_REASON1 register to buffer */
  result = pSPMI->ReadLong(pSPMI, 0, SPMI_BUS_ACCESS_PRIORITY_LOW, PON_WARM_RESET_REASON1, (UINT8*)&RegDump, (UINT32)1,0);
  if ( result != SPMI_SUCCESS )
  {
      DEBUG(( EFI_D_ERROR, "Read to PON_WARM_RESET_REASON1 register failed, Status = (0x%x)\r\n", result));
  }
  
  AsciiStrCpy(UefiResetBufferAddress, PONWarmReset1Str);    
  UefiResetBufferAddress = (CHAR8*)( (UINTN)UefiResetBufferAddress + AsciiStrLen(PONWarmReset1Str));
  AsciiValueToString ((UefiResetBufferAddress), 0, (UINT64)RegDump, 8);
  UefiResetBufferAddress=UefiResetBufferAddress+sizeof(UINT64);
    
  /* Read and write PON_WARM_RESET_REASON2 register to buffer */
  result = pSPMI->ReadLong(pSPMI, 0, SPMI_BUS_ACCESS_PRIORITY_LOW, PON_WARM_RESET_REASON2, (UINT8*)&RegDump, (UINT32)1,0);
  if ( result != SPMI_SUCCESS )
  {
    DEBUG(( EFI_D_ERROR, "Read to PON_WARM_RESET_REASON2 register failed, Status = (0x%x)\r\n", result));
    
  }

  AsciiStrCpy(UefiResetBufferAddress, PONWarmReset2Str);    
  UefiResetBufferAddress = (CHAR8*)( (UINTN)UefiResetBufferAddress + AsciiStrLen(PONWarmReset2Str));
  AsciiValueToString ((UefiResetBufferAddress), 0, (UINT64)RegDump, 8);
  UefiResetBufferAddress = UefiResetBufferAddress+sizeof(UINT64);
    
  /* Read and write POFF_REASON1 egister to buffer */
  result = pSPMI->ReadLong(pSPMI, 0, SPMI_BUS_ACCESS_PRIORITY_LOW, POFF_REASON1, (UINT8*)&RegDump, (UINT32)1,0);
  if ( result != SPMI_SUCCESS )
  {
      DEBUG(( EFI_D_ERROR, "Read to POFF_REASON1 register failed, Status = (0x%x)\r\n", result));

  }

  AsciiStrCpy(UefiResetBufferAddress, POFF1Str);   
  UefiResetBufferAddress = (CHAR8*)( (UINTN)UefiResetBufferAddress + AsciiStrLen(POFF1Str));
  AsciiValueToString ((UefiResetBufferAddress), 0, (UINT64)RegDump, 8);
  UefiResetBufferAddress = UefiResetBufferAddress+sizeof(UINT64);
            
  /* Read and write POFF_REASON2 egister to buffer */
  result = pSPMI->ReadLong(pSPMI, 0, SPMI_BUS_ACCESS_PRIORITY_LOW, POFF_REASON2, (UINT8*)&RegDump, (UINT32)1,0);
  if ( result != SPMI_SUCCESS )
  {
    DEBUG(( EFI_D_ERROR, "Read to POFF_REASON2 register failed, Status = (0x%x)\r\n", result));

  }

  AsciiStrCpy(UefiResetBufferAddress, POFF2Str);  
  UefiResetBufferAddress = (CHAR8*)( (UINTN)UefiResetBufferAddress + AsciiStrLen(POFF2Str));
  AsciiValueToString ((UefiResetBufferAddress), 0, (UINT64)RegDump, 8);
  UefiResetBufferAddress = UefiResetBufferAddress+sizeof(UINT64);
  
  /* Read and write PON_PBL_STATUS egister to buffer */
  result = pSPMI->ReadLong(pSPMI, 0, SPMI_BUS_ACCESS_PRIORITY_LOW, PON_PBL_STATUS, (UINT8*)&RegDump, (UINT32)1,0);
  if ( result != SPMI_SUCCESS )
  {
    DEBUG(( EFI_D_ERROR, "Read to PON_PBL_STATUS register failed, Status = (0x%x)\r\n", result));

  }

  AsciiStrCpy(UefiResetBufferAddress, PONPBL2Str);  
  UefiResetBufferAddress = (CHAR8*)( (UINTN)UefiResetBufferAddress + AsciiStrLen(PONPBL2Str));
  AsciiValueToString ((UefiResetBufferAddress), 0, (UINT64)RegDump, 8);
  UefiResetBufferAddress = UefiResetBufferAddress+sizeof(UINT64);

  return EFI_SUCCESS; 
}

STATIC VOID
SetupDBIDump (UINT64 MemoryBase)
{
  EFI_STATUS Status = EFI_SUCCESS;
  UINTN WriteAddr;
  UINT32 WriteValue;
  UINT32 i;
  UINTN NumCores = 0;
  UINT32 SkipDBISetup = 0;
  UINT32 SharedIMEMBaseAddr = 0;

  DUMP_TABLE_TYPE *DbiDumpTable = (DUMP_TABLE_TYPE*)(MemoryBase + DBI_DUMP_TABLE_OFFSET);
  DUMP_TABLE_TYPE *AppDumpTable = (DUMP_TABLE_TYPE*)(MemoryBase + DBI_DUMP_TABLE_OFFSET + sizeof(DUMP_TABLE_TYPE));
  DUMP_DATA_TYPE_TABLE *DumpDataTypeTable = (DUMP_DATA_TYPE_TABLE*)(MemoryBase + DBI_DUMP_TABLE_OFFSET + 2*sizeof(DUMP_TABLE_TYPE));
  
  if (DbiDumpTable == NULL)
  {
    DEBUG ((EFI_D_ERROR, "ERROR: DBI Dump table not setup\r\n"));
    CpuDeadLoop();
    return;
  }

  Status = GetConfigValue("SkipDBISetup", (UINT32*)&SkipDBISetup);
  if ((Status == EFI_SUCCESS) && (SkipDBISetup == 1)) {
    return;
  }

  Status = GetConfigValue("NumCpus", (UINT32*)&NumCores);
  if (Status != EFI_SUCCESS)
  {
      DEBUG(( EFI_D_ERROR, "Could not NumCpus uefiplat.cfg Defaulting to 8 cores , Status = (0x%x)\r\n", Status));
      NumCores = 0x08;
  }
  /* Fill out the top level DbiDumpTable version and entries*/
  DbiDumpTable->Version    =    0x1;
  DbiDumpTable->NumEntries =    0x1;

  /* Fill out the second level APP dump table */
  AppDumpTable->Version     =    0x1;
  AppDumpTable->NumEntries  =   NumCores + 1;

  DbiDumpTable->Entries[0].id         = MSM_DUMP_CLIENT_APPS;
  DbiDumpTable->Entries[0].type       = MSM_DUMP_TYPE_TABLE;
  DbiDumpTable->Entries[0].start_addr = (UINT64)AppDumpTable; 
  
  DEBUG ((EFI_D_INFO, "NumCores : %d \n", NumCores));
  
  for (i=0; i < NumCores ; i++)
  {
    DumpDataTypeTable->DumpDataType[i].header.version        = 0x0;
    DumpDataTypeTable->DumpDataType[i].header.magic          = 0x0;
    DumpDataTypeTable->DumpDataType[i].start_addr     = MemoryBase + CPU_REG_DUMP_START_OFFSET + i * SDI_DUMP_CORE_AP_REG_SIZE;
    DumpDataTypeTable->DumpDataType[i].len            = SDI_DUMP_CORE_AP_REG_SIZE;
    AppDumpTable->Entries[i].id         = MSM_CPU_REGS_DUMP + i;
    AppDumpTable->Entries[i].type       = MSM_DUMP_TYPE_DATA;
    AppDumpTable->Entries[i].start_addr = (UINT64)(&DumpDataTypeTable->DumpDataType[i]); 
  }
   DumpDataTypeTable->DumpDataType[NumCores].header.version         = 0x0;
   DumpDataTypeTable->DumpDataType[NumCores].header.magic           = 0x0;
   DumpDataTypeTable->DumpDataType[NumCores].start_addr      = MemoryBase + CPU_REG_DUMP_END_OFFSET;
   DumpDataTypeTable->DumpDataType[NumCores].len             = SDI_DUMP_ETB_DUMP_SIZE;
   AppDumpTable->Entries[NumCores].id          = MSM_ETB_DUMP;
   AppDumpTable->Entries[NumCores].type        = MSM_DUMP_TYPE_DATA;
   AppDumpTable->Entries[NumCores].start_addr  = (UINT64)(&DumpDataTypeTable->DumpDataType[NumCores]);
   
   DumpDataTypeTable->DumpDataType[NumCores + 1].header.version         = 0x0;
   DumpDataTypeTable->DumpDataType[NumCores + 1].header.magic           = 0x0;
   DumpDataTypeTable->DumpDataType[NumCores + 1].start_addr      = MemoryBase + CPU_REG_DUMP_END_CHECK_OFFSET;
   DumpDataTypeTable->DumpDataType[NumCores + 1].len             = SDI_DUMP_CORE_AP_REG_SIZE;
   AppDumpTable->Entries[NumCores + 1].id          = CPU_REG_DUMP_END_CHECK;
   AppDumpTable->Entries[NumCores + 1].type        = 0x0;
   AppDumpTable->Entries[NumCores + 1].start_addr  = (UINT64)(&DumpDataTypeTable->DumpDataType[NumCores + 1]);

  /* Set the IMEM Cookie with the address to the DbiDumpTable */
  Status = GetConfigValue ("SharedIMEMBaseAddr", (UINT32 *)&SharedIMEMBaseAddr); 
  if ((Status != EFI_SUCCESS) || (SharedIMEMBaseAddr == 0))
  {
    return;
  }
  /* TODO: Fix this when Shared IMEM table is fixed to support 64-bit addressing */
  WriteAddr = (UINTN) SharedIMEMBaseAddr + DBI_SHARED_IMEM_COOKIE_OFFSET;
  //ASSERT((UINTN) DbiDumpTable < 0xFFFFFFFF);
  WriteValue = ((UINTN)DbiDumpTable & 0xFFFFFFFF);
  MmioWrite32(WriteAddr, WriteValue);
}

EFI_STATUS
EFIAPI
CrashDumpDxeInitialize(
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
   EFI_STATUS Status = EFI_SUCCESS;
   UINT64 UefiFdBase = PcdGet64(PcdEmbeddedFdBaseAddress);
   MemRegionInfo FdRegion;
   UINT64 DBIDumpDDRBase;
   
   /* Get Available memory from partition table */  
   InitRamPartitionTableLib();
 
   Status = GetPartitionEntryByAddr (UefiFdBase, &FdRegion);
   if (Status != EFI_SUCCESS)
   {
      DEBUG ((EFI_D_ERROR, "ERROR: Unable to Get Available memory from partition table!!!\r\n"));
	  DEBUG ((EFI_D_ERROR, "ERROR: CrashDump setup failed!!!\r\n"));
      return Status;
   }
   
   /* Find the address of the DbiDumpTable base */
   Status = GetConfigValue64 ("DBIDumpDDRBase", &DBIDumpDDRBase); 
   if (Status != EFI_SUCCESS ) 
   {
      DEBUG((EFI_D_ERROR, "ERROR: Failed to get valid DBIDumpDDRBase from cfg file\r\n"));
      return Status;
   }
   
   SetupDBIDump(DBIDumpDDRBase);
   HandleCrashDump();
   UpdateOfflineCrashDumpConfigTable();
   GetCrashDumpConfigTable();
   InitializeResetDataBuffers(OfflineCrashDumpConfigTable);
   
   return Status;
}

