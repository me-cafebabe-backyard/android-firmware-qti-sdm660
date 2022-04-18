/** @file PciBusLib.c

  PCIe Init Driver File.

  Copyright (c) 2014-2016, Qualcomm Technologies Inc. All rights reserved.

**/


/*=============================================================================
                              EDIT HISTORY


 when       who      what, where, why
 --------   ---      ----------------------------------------------------------
 02/08/16   tselvam  Added pcie xml config support
 01/11/16   tselvam  Register for PCIe ExitBootServices callback
 06/15/15   tselvam  Simplified PCIe_Read_Config function.
                     Calling setup L1ss after iATU setup.
 05/13/15   tselvam  Unified code for multi platforms
 03/18/15   tselvam  Fixed Copyrights header
 03/16/15   tselvam  Added warning messages and split PHY code
                     into common and port
 01/26/15   tselvam  Updated the code as per 8994 changes
 10/07/14   ahalabi  Changes for 8996
 06/16/14   hozefak  Add PcieInit protocol
 05/07/14   hozefak  Turn on PCie during exitbootservices
 04/18/14   hozefak  First checkin for 8994
=============================================================================*/

#include "PciLink.h"
#include "DDIChipInfo.h"
#include <Protocol/EFIPlatformInfo.h>
#include <Protocol/EFIChipInfo.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/EFIClock.h>
#include <Library/IoLib.h>
#include <Library/IoLib.h>
#include <Library/PcieConfigLib.h>
#include <Protocol/EFIPCIeInit.h>
#include <Library/DebugLib.h>

STATIC PRootPort_Config_Data FirstNode = NULL;

//
// PCI Bus Driver Global Variables
//

EFI_PLATFORMINFO_PLATFORM_INFO_TYPE   PlatformInfo;
EFIChipInfoIdType                chipVersion;

// Exit Boot Services guid
extern EFI_GUID gEfiEventExitBootServicesGuid;
EFI_EVENT EfiPCIeExitBootServicesEvent = (EFI_EVENT)NULL;

/**
 * Exit Boot services callback for PCIe library
 *@param  Event                 Event whose notification
 *                              function is being invoked.
 *
 *@param  Context               The pointer to the notification
 *                              function's context which is
 *                              implementation-dependent.
 */
VOID
EFIAPI
PCIeExitBSCallback (
  IN EFI_EVENT        Event,
  IN VOID             *Context
  )
{
  EFI_STATUS Status = EFI_SUCCESS;
  QCOM_PCIE_PROTOCOL *PcieInitProtocol = NULL;

  Status = gBS->LocateProtocol(&gQcomPcieInitProtocolGuid,
    NULL,
    (VOID**) &PcieInitProtocol);

  if (PcieInitProtocol == NULL)
  {
    DEBUG((EFI_D_WARN, "PCIeExitBSCallback: Could not locate PCIE Init protocol\n"));
  }

  if (PcieInitProtocol != NULL)
  {
    Status = PcieInitProtocol->PCIeInitHardware(PcieInitProtocol);
    if (EFI_ERROR(Status)) {
	  DEBUG((EFI_D_WARN, "PCIeExitBSCallback: Unable to init H/w Status = 0x%p\r\n", Status));
    }
  }
}

/**
  RegisterPCIeEBSCallback, registers for the Exit boot services callback
**/
EFI_STATUS
EFIAPI
PCIeLib_Register_EBS_Callback
(
  VOID
)
{
  EFI_STATUS Status = EFI_SUCCESS;

  //Register to Exit Boot Service Event
  Status = gBS->CreateEventEx ( EVT_NOTIFY_SIGNAL,
    TPL_CALLBACK,
    PCIeExitBSCallback,
    NULL,
    &gEfiEventExitBootServicesGuid,
    &EfiPCIeExitBootServicesEvent);

  if (EFI_ERROR(Status)) {
    DEBUG((EFI_D_WARN, "RegisterPCIeEBSCallback: register failed Status = 0x%p\r\n", Status));
  }

  return Status;
}
/**
  Read the config table and fill up the linked list.

 Read the number of root ports

  @retval EFI_SUCCESS       The entry point is executed successfully.
  @retval other             Some error occurred when executing this entry point.

**/
EFI_STATUS
EFIAPI
PCIe_Read_Config (VOID)
{
  EFI_STATUS Status;

  Status = PCIe_ReadConfigData (&FirstNode);
  if (EFI_ERROR(Status)) {
	  DEBUG((EFI_D_WARN, "PCIe_Read_Config: Unable to Read determine RP Mask Status = 0x%p\r\n", Status));
	  goto Exit;
  }

Exit:
  return Status;
}


/**
  The Entry Point for PCI Bus module. The user code starts with this function.

 This function sets up the PCIe core depending on the number of RPs in the platfile. Will also setup clocks\ATUs for the endpoint

  @retval EFI_SUCCESS       The entry point is executed successfully.
  @retval other             Some error occurred when executing this entry point.

**/
EFI_STATUS
EFIAPI
PCIe_Enable (VOID)
{
  EFI_STATUS  Status;
  EFI_PLATFORMINFO_PROTOCOL  *hPlatformInfoProtocol;

  // Read the platform ID and then figure out what Phy to initialize
  Status = gBS->LocateProtocol (
             &gEfiPlatformInfoProtocolGuid,
             NULL,
             (VOID **) &hPlatformInfoProtocol
           );
  if EFI_ERROR (Status)
  {
    DEBUG(( EFI_D_WARN, "PCIe_Enable: Failed LocateProtocol\r\n"));
    return Status ;
  }

  Status = hPlatformInfoProtocol->GetPlatformInfo (hPlatformInfoProtocol, &PlatformInfo);
  if EFI_ERROR (Status)
  {
    DEBUG(( EFI_D_WARN, "PCIe_Enable: Failed PCIe_EnableClocks\r\n"));
    return Status ;
  }

  Status = PCIe_EnableClocks(&FirstNode);
  if EFI_ERROR (Status)
  {
    DEBUG(( EFI_D_WARN, "PCIe_Enable: Failed GetPlatformInfo\r\n"));
    return Status ;
  }

  /*
   * Initializes Link and Clocks
   */
  if (PlatformInfo.platform == EFI_PLATFORMINFO_TYPE_VIRTIO || PlatformInfo.platform == EFI_PLATFORMINFO_TYPE_UNKNOWN) 
  {
    Status = PCIe_InitialzeLink (&FirstNode);
    if EFI_ERROR (Status) 
    {
      DEBUG(( EFI_D_WARN, "PCIe_Enable: Failed PCIe_InitialzeLink\r\n"));
      return Status ;
    }
  } 
  else
  {
    Status = PCIe_InitialzeLDO();
    if EFI_ERROR (Status)
	{
	  DEBUG(( EFI_D_WARN, "PCIe_Enable: Failed PCIe_InitialzeLDO\r\n"));
	  return Status ;
	}

    Status = PCIe_InitAdditionalGPIO (&FirstNode);
	if EFI_ERROR (Status)
	{
	  DEBUG(( EFI_D_WARN, "PCIe_Enable: Failed PCIe_InitAdditionalGPIO\r\n"));
	  return Status ;
	}

	Status = PCIe_InitializePHY ();
	if EFI_ERROR (Status)
	{
	  DEBUG(( EFI_D_ERROR, "PCIe_Enable: Failed PCIe_InitializePHY\r\n"));
	  return Status ;
	}

    Status = PCIe_InitializePortPHY (&FirstNode);
    if EFI_ERROR (Status)
    {
    	DEBUG(( EFI_D_ERROR, "PCIe_Enable: Failed PCIe_InitializePortPHY\r\n"));
    	return Status ;
    }

    Status = PCIe_ChangeClockSource(&FirstNode);
    if EFI_ERROR (Status)
    {
      DEBUG(( EFI_D_ERROR, "PCIe_Enable: Failed PCIe_ChangeClockSource\r\n"));
      return Status ;
    }

    Status = PCIe_InitialzeLink (&FirstNode);
    if EFI_ERROR (Status) 
    {
      DEBUG(( EFI_D_WARN, "PCIe_Enable: Failed PCIe_InitialzeLink\r\n"));
      return Status ;
    }
  }

  Status = PCIe_InitializeConfigSpace (&FirstNode);
  if EFI_ERROR (Status) 
  {
    DEBUG(( EFI_D_WARN, "PCIe_Enable: Failed PCIe_InitializeConfigSpace\r\n"));
    return Status ;
  }

  Status = PCIe_GetBarMemoryRequirement (&FirstNode);
  if EFI_ERROR (Status)
  {
    DEBUG(( EFI_D_WARN, "PCIe_Enable: Failed PCIe_GetBarMemoryRequirement\r\n"));
    return Status ;
  }

  Status = PCIe_Setup_L1ss (&FirstNode);
  if EFI_ERROR (Status)
  {
    DEBUG(( EFI_D_WARN, "PCIe_Enable: Failed PCIe_Setup_L1ss\r\n"));
    return Status ;
  }

  return Status;
}

/**
  Read the config space of PCIe rootnode.

  @param[in] rpIndex    	root port index starting from 0 to n...
  @param[in] offset    		offset in the config space to read from.

  @retval 0xFFFFFFFF       Invalid rootnode index rpIndex passed .
  @retval other            32-bit value present in the configuration space register.

**/
UINT32
EFIAPI
PCIeLib_Config_Read_32 (
		IN PCIe_RP_IDX rpIndex,
		IN UINT32 offset)
{
	PRootPort_Config_Data rootNode = FirstNode;

	if(rootNode == NULL)
		return 0xFFFFFFFF;

	do
	{
		if(rpIndex == rootNode->rootPortIdx)
			break;

		rootNode = rootNode->Next;
	}while(rootNode);

	if(rootNode == NULL)
		return 0xFFFFFFFF;

	return MmioRead32((rootNode->ConfigBaseAddress + offset));
}
