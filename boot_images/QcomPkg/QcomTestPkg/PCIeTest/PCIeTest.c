/** @file PCIeTest.c
   
  Tests for PCIe root port

  Copyright (c) 2014-2015, Qualcomm Technologies Inc. All rights reserved.
  
**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 06/13/16   tselvam Fixed KW bug for not checking pcieRP for NULL
 06/08/16   tselvam Included support to dump config space for all RPs.
 03/18/15   tselvam Fixed Copyrights header.
 03/16/15   tselvam Fixed how exit will happen incase of failure.
 01/26/15   tselvam Initial version for 8996.
 12/03/14   tselvam Added support for De-initialization
 09/05/14   tselvam Initial version.

=============================================================================*/

#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Library/UefiLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Protocol/EFIPCIeInit.h>
#include <Library/TestInterface.h>

#define NUM_OF_RP_MASK                                   (0x00FF)
#define RP_ENABLE_MASK                                   (0xFF00)
#define RP_MASK_LENGTH                                   (8)

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
PCIeTestMain(
	IN EFI_HANDLE        ImageHandle,
	IN EFI_SYSTEM_TABLE  *SystemTable
	)
{
	EFI_STATUS status = EFI_SUCCESS;
	QCOM_PCIE_PROTOCOL *pcieRP = NULL;
	UINT32 regOffset = 0;
	UINT32 rpMask = 0;
	UINT32 rootPortIdx = 0;
	UINT32 enabled_rps = 0;
	UINT32 total_rps = 0;


	TEST_START("PCIeTest");
	status = gBS->LocateProtocol(&gQcomPcieInitProtocolGuid,
								NULL,
								(VOID**)&pcieRP);
	if((status != EFI_SUCCESS) || (pcieRP == NULL))
	{
		AsciiPrint("ERROR: PCIeTestMain: pcieRP protocol load failed\n");
		return status;
	}
  
	AsciiPrint("PCIeTestMain: pcieRP protocol loaded\n");

	status = pcieRP->PCIeInitHardware(pcieRP);
	if(status != EFI_SUCCESS)
	{
		AsciiPrint("ERROR: PCIeTestMain: PCIeInitHardware failed\n");
		goto Exit_Test;
	}

	AsciiPrint("PCIeTestMain: PCIeInitHardware completed\n");

	rpMask = pcieRP->PCIeReadRPMaskVal(pcieRP);
	if(rpMask == 0)
	{
		AsciiPrint("ERROR: PCIeTestMain: There are no configured root ports available\n");
		status = EFI_LOAD_ERROR;
		goto Exit_Test;
	}

	total_rps = rpMask & NUM_OF_RP_MASK;
	enabled_rps = (rpMask & RP_ENABLE_MASK) >> RP_MASK_LENGTH;

	while (total_rps)
	{
		rootPortIdx = __builtin_ctz(enabled_rps);

		AsciiPrint("\n######################################################################\n");
		AsciiPrint("PCIeTestMain: Config Space Read of Root Port %d Start\n", rootPortIdx);
		for(regOffset = 0; regOffset < 0xFF; regOffset += 4)
		{
			AsciiPrint("PCIeTestMain: RP%d Config Space offset: %02x read value %08x\n",
					rootPortIdx, regOffset, pcieRP->PCIe_Config_Read_32(rootPortIdx, regOffset));
		}
		AsciiPrint("PCIeTestMain: Config Space Read of Root Port %d End\n", rootPortIdx);

		AsciiPrint("PCIeTestMain: Config Space Read of EP%d Start\n", rootPortIdx);
		for(regOffset = 0x100000; regOffset < 0x1000FF; regOffset += 4)
		{
			AsciiPrint("PCIeTestMain: EP%d Config Space offset: %02x read value %08x\n",
					rootPortIdx, regOffset, pcieRP->PCIe_Config_Read_32(rootPortIdx, regOffset));
		}
		AsciiPrint("PCIeTestMain: Config Space Read of EP%d End\n", rootPortIdx);
		AsciiPrint("\n######################################################################\n");

		/* Masking out the identified root port index */
		enabled_rps &= (~ (((UINT32)0x01) << rootPortIdx) );
		total_rps--;
	}

Exit_Test:
	AsciiPrint("PCIeTestMain: PCIeDeInitHardware Start\n");
	if(pcieRP != NULL)
	{
		pcieRP->PCIeDeInitHardware();
	}
	AsciiPrint("PCIeTestMain: PCIeDeInitHardware End\n");
	TestStatus("PCIeTest", status);
	TEST_STOP("PCIeTest");
	
	return status;
}

