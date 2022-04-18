/*
  @file 
	Copyright (c) 2016 Qualcomm Technologies, Inc.
	All Rights Reserved.
	Qualcomm Technologies Confidential and Proprietary.
  ============================================================================*/
  
  /*=============================================================================
								EDIT HISTORY
  
  
   when 	  who	  what, where, why
   --------   ---	  -----------------------------------------------------------
   09/30/16   ltg     Added full implementation for patching ACPI, updating UEFI variable, and protocol API's
   08/4/16	 vahidd   Intial Draft for Patching DSDT tables.
  =============================================================================*/


#include <PiDxe.h>
#include <Protocol/AcpiTable.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/HobLib.h>
#include <Protocol/AcpiSystemDescriptionTable.h>
#include <Library/UefiCfgLib.h>
#include <IndustryStandard/Acpi.h>

/**
WinDsdtUpdate PROTOCOL interfaces
*/
#include <Protocol/EfiWinDsdtUpdate.h>

/**
Device node information.
*/
#define EFI_DEVICE_FRONT_CAMERA "CAMF"
#define EFI_DEVICE_BACK_CAMERA "CAMS"
#define EFI_DEVICE_BT "BTH0"
#define EFI_DEVICE_AUDIO "ADSP"
#define EFI_DEVICE_MODEM "AMSS"
#define EFI_DEVICE_USB "URS0.USB0"
#define EFI_DEVICE_WLAN "WLEN"

char * DEVICE_LIST[EFI_FEATURE_MAX] = { 
	EFI_DEVICE_FRONT_CAMERA,
	EFI_DEVICE_BACK_CAMERA,
	EFI_DEVICE_BT,
	EFI_DEVICE_AUDIO,
	EFI_DEVICE_MODEM,
	EFI_DEVICE_USB,
	EFI_DEVICE_WLAN
};

/**
UEFI Variable information
*/
#define FEATURE_ENABLE_VAR_NAME L"FeatureEnableBitmask"

#define FEATURE_ENABLE_VAR_GUID \
  { \
    0x68f38861, 0x1414, 0x439b, { 0x94, 0xa0, 0xb2, 0x8, 0xfd, 0xe5, 0xe, 0x12 } \
  }

STATIC EFI_GUID   FeatureEnableVarGuid = FEATURE_ENABLE_VAR_GUID;

/**
Global variables
*/
static EFI_ACPI_SDT_PROTOCOL				*gAcpiSdt = NULL;
static UINT32								gfeatureBitmask = 0x0;

EFI_STATUS
GetFeatureVariable(
IN  EFI_WIN_DSDT_UPDATE_PROTOCOL	*This,
IN EFI_FEATURE_TYPE					Type,
OUT  BOOLEAN						*Enable
)
{
	EFI_STATUS Status = EFI_SUCCESS;
	UINTN  VarSize = sizeof(gfeatureBitmask);
	Status = gRT->GetVariable(FEATURE_ENABLE_VAR_NAME, &FeatureEnableVarGuid, NULL, &VarSize, &gfeatureBitmask);

	if (EFI_ERROR(Status)) {
		DEBUG((EFI_D_ERROR, "[WinDsdtUpdate] Error GetFeatureVariable, Status = (0x%x) \r\n", Status));
	}
	else {
		// check if feature's bit is set or not, and set Enable to T/F accordingly
		*Enable = (gfeatureBitmask & (0x1 << Type)) ? TRUE : FALSE;
	}

	return Status;
}

EFI_STATUS
SetFeatureVariable(
IN  EFI_WIN_DSDT_UPDATE_PROTOCOL	*This,
IN  EFI_FEATURE_TYPE				Type,
IN  BOOLEAN							Enable
)
{
	EFI_STATUS Status = EFI_SUCCESS;

	// update global variable
	if (Enable == TRUE)
	{
		gfeatureBitmask |= (UINT32)(0x1 << Type);
	}
	else
	{
		gfeatureBitmask &= (UINT32)(~(0x1 << Type));
	}

	return Status;
}

EFI_STATUS
CommitFeatureVariable(
IN  EFI_WIN_DSDT_UPDATE_PROTOCOL	*This
)
{
	EFI_STATUS Status = EFI_SUCCESS;
	UINTN VarSize = sizeof(gfeatureBitmask);
	UINT32 Attributes = (EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS);

	Status = gRT->SetVariable(FEATURE_ENABLE_VAR_NAME, &FeatureEnableVarGuid, Attributes, VarSize, &gfeatureBitmask);

	return Status;
}

/**
EFI_WIN_DSDT_UPDATE Protocol implementation
*/
EFI_WIN_DSDT_UPDATE_PROTOCOL gEfiWinDsdtUpdateProtocol =
{
	EFI_WIN_DSDT_UPDATE_PROTOCOL_REVISION,
	GetFeatureVariable,
	SetFeatureVariable,
	CommitFeatureVariable
};

static
EFI_ACPI_HANDLE
LocateHandle(
IN EFI_ACPI_HANDLE AcpiHandle,
IN UINT8 Operation,
IN CONST VOID *Name
)
{
	EFI_ACPI_HANDLE ChildAcpiHandle = NULL;
	EFI_ACPI_HANDLE PrevChildAcpiHandle = NULL;
	EFI_STATUS Status;
	EFI_ACPI_DATA_TYPE DataType;
	CONST UINT8 *Data;
	UINTN DataSize;

	// Find all children and loop through them until we find a match with the one we want
	Status = gAcpiSdt->GetChild(AcpiHandle, &PrevChildAcpiHandle);
	ChildAcpiHandle = PrevChildAcpiHandle;
	while (!EFI_ERROR(Status) &&
		(NULL != ChildAcpiHandle)) {
		Status = gAcpiSdt->GetOption(ChildAcpiHandle, 0, &DataType, (CONST VOID **) &Data, &DataSize);
		if (EFI_ERROR(Status)){
			goto Error;
		}
		if ((DataType == EFI_ACPI_DATA_TYPE_OPCODE) && (Data[0] == Operation)) {
			Status = gAcpiSdt->GetOption(ChildAcpiHandle, 1, &DataType, (CONST VOID **) &Data, &DataSize);
			if (EFI_ERROR(Status)){
				goto Error;
			}
			if (0 == CompareMem(Name, Data, DataSize)) {
				return ChildAcpiHandle;
			}
		}
		Status = gAcpiSdt->GetChild(AcpiHandle, &PrevChildAcpiHandle);
		gAcpiSdt->Close(ChildAcpiHandle);
		ChildAcpiHandle = PrevChildAcpiHandle;
	}

Error:
	if (ChildAcpiHandle){
		gAcpiSdt->Close(ChildAcpiHandle);
	}
	if (PrevChildAcpiHandle){
		gAcpiSdt->Close(PrevChildAcpiHandle);
	}

	return NULL;
}

static
VOID
UpdateACPIGlobal(
IN EFI_ACPI_HANDLE AcpiHandle,
IN BOOLEAN Enabled
)
{
	EFI_STATUS Status;
	EFI_ACPI_DATA_TYPE DataType;
	CONST UINT8 *Data;
	UINTN DataSize;
	UINT8 GlobalValue;
	UINTN i = 0;

	// first make sure this is a NAME opcode
	Status = gAcpiSdt->GetOption(AcpiHandle, i, &DataType, (CONST VOID **) &Data, &DataSize);
	if (EFI_ERROR(Status)) {
		DEBUG((EFI_D_ERROR, "[WinDsdtUpdate] Error finding data (opcode for name operation)\n"));
	}
	else {
		if ((DataType != EFI_ACPI_DATA_TYPE_OPCODE) || (Data[0] != AML_NAME_OP)) {
			DEBUG((EFI_D_ERROR, "[WinDsdtUpdate] Unexpected data found\n"));
			goto Error;
		}
	}

	// go through indices until we find the value of the global var
	while (DataType != EFI_ACPI_DATA_TYPE_CHILD){
		i++;
		Status = gAcpiSdt->GetOption(AcpiHandle, i, &DataType, (CONST VOID **) &Data, &DataSize);
		if (EFI_ERROR(Status)) {
			DEBUG((EFI_D_ERROR, "[WinDsdtUpdate] Error finding data\n"));
		}
	}

	if (Enabled) {
		GlobalValue = 0x1;
	}
	else {
		GlobalValue = 0x0;
	}

	if (Data[0] != GlobalValue) {
		Status = gAcpiSdt->SetOption(AcpiHandle, i, &GlobalValue, sizeof(GlobalValue));
		if ((EFI_ERROR(Status))) {
			DEBUG((EFI_D_ERROR, "[WinDsdtUpdate] Error setting global variable value\n"));
			goto Error;
		}
	}

Error:
	return;
}

static
VOID
UpdateSTA(
IN EFI_ACPI_HANDLE AcpiHandle,
IN BOOLEAN Enabled
)
{
	EFI_ACPI_HANDLE ReturnAcpiHandle = NULL;
	EFI_ACPI_HANDLE ValueAcpiHandle = NULL;
	EFI_ACPI_DATA_TYPE DataType;
	CONST UINT8 *Data;
	UINTN DataSize;
	UINT8 STAValue;
	EFI_STATUS Status;

	EFI_ACPI_HANDLE STAAcpiHandle = LocateHandle(AcpiHandle, AML_METHOD_OP, "_STA");
	if (NULL == STAAcpiHandle) {
		DEBUG((EFI_D_ERROR, "[WinDsdtUpdate] No STA Method found\n"));
		goto Error;
	}
	Status = gAcpiSdt->GetChild(STAAcpiHandle, &ReturnAcpiHandle);
	if (EFI_ERROR(Status) || (NULL == ReturnAcpiHandle)){
		DEBUG((EFI_D_ERROR, "[WinDsdtUpdate] No child found\n"));
		goto Error;
	}

	Status = gAcpiSdt->GetOption(ReturnAcpiHandle, 0, &DataType, (CONST VOID **) &Data, &DataSize);
	if ((EFI_ERROR(Status))){
		DEBUG((EFI_D_ERROR, "[WinDsdtUpdate] Error finding data (opcode for return statement)\n"));
		goto Error;
	}
	if ((DataType != EFI_ACPI_DATA_TYPE_OPCODE) || (Data[0] != AML_RETURN_OP)){
		DEBUG((EFI_D_ERROR, "[WinDsdtUpdate] Unexpected data found\n"));
		goto Error;
	}

	Status = gAcpiSdt->GetChild(ReturnAcpiHandle, &ValueAcpiHandle);
	if ((EFI_ERROR(Status)) || (NULL == ValueAcpiHandle)){
		DEBUG((EFI_D_ERROR, "[WinDsdtUpdate] No child found\n\n"));
		goto Error;
	}

	Status = gAcpiSdt->GetOption(ValueAcpiHandle, 0, &DataType, (CONST VOID **) &Data, &DataSize);
	if ((EFI_ERROR(Status))){
		DEBUG((EFI_D_ERROR, "[WinDsdtUpdate] Error finding data\n"));
		goto Error;
	}
	if ((DataType != EFI_ACPI_DATA_TYPE_OPCODE) || (Data[0] != AML_BYTE_PREFIX)){
		DEBUG((EFI_D_ERROR, "[WinDsdtUpdate] Unexpected data found\n"));
		goto Error;
	}

	// get the value of the return statement
	Status = gAcpiSdt->GetOption(ValueAcpiHandle, 1, &DataType, (CONST VOID **) &Data, &DataSize);
	if ((EFI_ERROR(Status))){
		DEBUG((EFI_D_ERROR, "[WinDsdtUpdate] Error finding data (STA return value)\n"));
		goto Error;
	}

	if ((DataType == EFI_ACPI_DATA_TYPE_UINT) && (DataSize == 1)) {
		if (Enabled) {
			STAValue = 0xF;
		}
		else {
			STAValue = 0x0;
		}
		if (Data[0] != STAValue) {
			Status = gAcpiSdt->SetOption(ValueAcpiHandle, 1, &STAValue, sizeof(STAValue));
			if ((EFI_ERROR(Status))){
				DEBUG((EFI_D_ERROR, "[WinDsdtUpdate] Error setting STA return value\n"));
				goto Error;
			}
		}
	}
	else {
		DEBUG((EFI_D_ERROR, "[WinDsdtUpdate] Unexpected data found (STA return value)\n"));
		goto Error;
	}

Error:
	if (ValueAcpiHandle){
		gAcpiSdt->Close(ValueAcpiHandle);
	}
	if (ReturnAcpiHandle){
		gAcpiSdt->Close(ReturnAcpiHandle);
	}
	if (STAAcpiHandle){
		gAcpiSdt->Close(STAAcpiHandle);
	}
}

static
VOID
UpdateACPI(
IN EFI_ACPI_HANDLE AcpiHandle,
IN BOOLEAN Enabled
)
{
	/*
	Check if there is an STA method for this feature:
	If there is one, then use UpdateSTA to patch ACPI
	If there isn't one, then use UpdateACPIGlobal to patch ACPI
	*/
	EFI_ACPI_HANDLE STAAcpiHandle = LocateHandle(AcpiHandle, AML_METHOD_OP, "_STA");
	if (NULL == STAAcpiHandle) {
		UpdateACPIGlobal(AcpiHandle, Enabled);
	}
	else{
		UpdateSTA(AcpiHandle, Enabled);
	}
}

static
EFI_STATUS
GetCurrentStatus(
IN EFI_ACPI_HANDLE AcpiHandle,
OUT BOOLEAN *Enabled
)
{
	EFI_ACPI_HANDLE ReturnAcpiHandle = NULL;
	EFI_ACPI_HANDLE ValueAcpiHandle = NULL;
	EFI_ACPI_DATA_TYPE DataType;
	CONST UINT8 *Data;
	UINTN DataSize;
	EFI_STATUS Status = EFI_SUCCESS;
	UINTN i = 0;

	EFI_ACPI_HANDLE STAAcpiHandle = LocateHandle(AcpiHandle, AML_METHOD_OP, "_STA");
	if (NULL == STAAcpiHandle) {
		DEBUG((EFI_D_ERROR, "[WinDsdtUpdate] No STA Method found. Checking if this is set using a global variable...\n"));
		Status = gAcpiSdt->GetOption(AcpiHandle, 0, &DataType, (CONST VOID **) &Data, &DataSize);
		if (EFI_ERROR(Status)){
			DEBUG((EFI_D_ERROR, "[WinDsdtUpdate] Error finding data. Exiting.\n"));
			goto Error;
		}
		if ((DataType != EFI_ACPI_DATA_TYPE_OPCODE) || (Data[0] != AML_NAME_OP)) {
			DEBUG((EFI_D_ERROR, "[WinDsdtUpdate] No global variable found. Exiting.\n"));
			goto Error;
		}

		// search for the value of this global variable
		while (DataType != EFI_ACPI_DATA_TYPE_CHILD){
			i++;
			Status = gAcpiSdt->GetOption(AcpiHandle, i, &DataType, (CONST VOID **) &Data, &DataSize);
			if (EFI_ERROR(Status)) {
				DEBUG((EFI_D_ERROR, "[WinDsdtUpdate] Error finding data\n"));
			}
		}
		*Enabled = (Data[0] != 0x0);
		goto Error;
	}

	Status = gAcpiSdt->GetChild(STAAcpiHandle, &ReturnAcpiHandle);
	if (EFI_ERROR(Status)) {
		DEBUG((EFI_D_ERROR, "[WinDsdtUpdate] No child found\n"));
		goto Error;
	}

	Status = gAcpiSdt->GetOption(ReturnAcpiHandle, 0, &DataType, (CONST VOID **) &Data, &DataSize);
	if (EFI_ERROR(Status)) {
		DEBUG((EFI_D_ERROR, "[WinDsdtUpdate] Error finding data (opcode for return statement)\n"));
		goto Error;
	}
	if ((DataType != EFI_ACPI_DATA_TYPE_OPCODE) || (Data[0] != AML_RETURN_OP)){
		DEBUG((EFI_D_ERROR, "[WinDsdtUpdate] Error finding data (opcode for return statement) - Unexpected data found\n"));
		goto Error;
	}

	Status = gAcpiSdt->GetChild(ReturnAcpiHandle, &ValueAcpiHandle);
	if ((EFI_ERROR(Status)) || (NULL == ValueAcpiHandle)){
		DEBUG((EFI_D_ERROR, "[WinDsdtUpdate] No child found\n\n"));
		goto Error;
	}

	Status = gAcpiSdt->GetOption(ValueAcpiHandle, 0, &DataType, (CONST VOID **) &Data, &DataSize);
	if (EFI_ERROR(Status)){
		DEBUG((EFI_D_ERROR, "[WinDsdtUpdate] Error finding data (prefix for return value)\n"));
		goto Error;
	}
	if ((DataType != EFI_ACPI_DATA_TYPE_OPCODE) || (Data[0] != AML_BYTE_PREFIX)){
		DEBUG((EFI_D_ERROR, "[WinDsdtUpdate] Error finding data (prefix for return value) - Unexpected data found\n"));
		goto Error;
	}

	// get the value of the return statement
	Status = gAcpiSdt->GetOption(ValueAcpiHandle, 1, &DataType, (CONST VOID **) &Data, &DataSize);
	if (EFI_ERROR(Status)){
		DEBUG((EFI_D_ERROR, "[WinDsdtUpdate] Error finding data (STA return value)\n"));
		goto Error;
	}
	if ((DataType == EFI_ACPI_DATA_TYPE_UINT) && (DataSize == 1)) {
		*Enabled = (Data[0] != 0x0);
	}
	else {
		DEBUG((EFI_D_ERROR, "[WinDsdtUpdate] Error finding data (STA return value) - Unexpected data found\n"));
		goto Error;
	}

Error:
	if (ValueAcpiHandle){
		gAcpiSdt->Close(ValueAcpiHandle);
	}
	if (ReturnAcpiHandle){
		gAcpiSdt->Close(ReturnAcpiHandle);
	}
	if (STAAcpiHandle){
		gAcpiSdt->Close(STAAcpiHandle);
	}
	return Status;
}


EFI_STATUS
InitFeatureVariable(
IN EFI_ACPI_HANDLE					AcpiHandle
)
{
	EFI_STATUS Status = EFI_SUCCESS;
	EFI_ACPI_HANDLE OutHandle = NULL;
	UINTN  VarSize = sizeof(gfeatureBitmask);
	UINT32 Attributes = (EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS);
	BOOLEAN enabled = FALSE;

	DEBUG((EFI_D_ERROR, "[WinDsdtUpdate] Creating UEFI variable... \r\n"));

	// loop through all features, check in ACPI if it is enabled/disabled by default, and construct global variable
	for (int i = 0; i < EFI_FEATURE_MAX; i++)
	{
		Status = gAcpiSdt->FindPath(AcpiHandle, (UINT8*)DEVICE_LIST[i], &OutHandle);
		if (EFI_ERROR(Status))
		{
			DEBUG((EFI_D_ERROR, "[WinDsdtUpdate] Error gAcpiSdt->FindPath, Status = (0x%x) \r\n", Status));
			goto Error;
		}

		// check ACPI for STA method's return value (enabled/disabled)
		Status = GetCurrentStatus(OutHandle, &enabled);
		if (EFI_ERROR(Status)) {
			DEBUG((EFI_D_ERROR, "[WinDsdtUpdate] Error getting current feature config, GetCurrentStatus Status = (0x%x) \r\n", Status));
			goto Error;
		}

		// update global variable
		if (enabled == TRUE)
		{
			gfeatureBitmask |= (UINT32)(0x1 << i);
		}
		else
		{
			gfeatureBitmask &= (UINT32)(~(0x1 << i));
		}
	}

	// create the uefi variable
	Status = gRT->SetVariable(FEATURE_ENABLE_VAR_NAME, &FeatureEnableVarGuid, Attributes, VarSize, &gfeatureBitmask);

	if (EFI_ERROR(Status)) {
		DEBUG((EFI_D_ERROR, "[WinDsdtUpdate] Error gRT->SetVariable, Status = (0x%x) \r\n", Status));
	}

Error:
	if (OutHandle){
		gAcpiSdt->Close(OutHandle);
	}
	return Status;
}

static 
EFI_STATUS
UpdateDsdtTable(
  IN EFI_ACPI_SDT_HEADER *Table,  
  IN EFI_ACPI_TABLE_VERSION Version,  
  IN UINTN TableKey )
{
	EFI_STATUS Status = EFI_SUCCESS;
	EFI_ACPI_HANDLE AcpiHandle = NULL;
	EFI_ACPI_HANDLE OutHandle = NULL;
	UINTN  VarSize = sizeof(gfeatureBitmask);

	// open handle with top node of dsdt table
	Status = gAcpiSdt->Open((VOID*)(UINTN)Table+sizeof(EFI_ACPI_SDT_HEADER),&AcpiHandle);
	if (EFI_ERROR (Status))
	{
		DEBUG((EFI_D_ERROR, "[WinDsdtUpdate] Error opening the handle for dsdt tables \r\n"));
		goto Error;
	}

	// get uefi variable for bitmask of features
	Status = gRT->GetVariable(FEATURE_ENABLE_VAR_NAME, &FeatureEnableVarGuid, NULL, &VarSize, &gfeatureBitmask);
	if (EFI_ERROR(Status)) {
		DEBUG((EFI_D_ERROR, "[WinDsdtUpdate] Error gRT->GetVariable, Status = (0x%x) \r\n", Status));

		// if this failed because the variable doesn't exist, we should create it here
		if (Status == EFI_NOT_FOUND){
			Status = InitFeatureVariable(AcpiHandle);
			if (EFI_ERROR(Status)){
				DEBUG((EFI_D_ERROR, "[WinDsdtUpdate] Error InitFeatureVariable, Status = (0x%x) \r\n", Status));
				goto Error;
			}
			DEBUG((EFI_D_ERROR, "[WinDsdtUpdate] InitFeatureVariable: Created uefi variable with value (0x%x) \r\n", gfeatureBitmask));
		}

		// if this failed for some other reason, just exit
		goto Error;
	}
	DEBUG((EFI_D_ERROR, "[WinDsdtUpdate] gRT->GetVariable: Got uefi variable with value (0x%x) \r\n", gfeatureBitmask));

	// loop through features and apply config based on gfeatureBitmask value
	for (int i = 0; i < EFI_FEATURE_MAX; i++)
	{
		Status = gAcpiSdt->FindPath(AcpiHandle,(UINT8*)DEVICE_LIST[i],&OutHandle);
		if(EFI_ERROR(Status))
		{
			DEBUG((EFI_D_ERROR, "[WinDsdtUpdate] Error gAcpiSdt->FindPath, Status = (0x%x) \r\n", Status));
		}
		UpdateACPI(OutHandle, ((gfeatureBitmask >> i) & 0x1));
	}

Error:
	if (AcpiHandle){
		gAcpiSdt->Close(AcpiHandle);
	}
	if (OutHandle){
		gAcpiSdt->Close(OutHandle);
	}
	return Status;
}

static 
EFI_STATUS
EFIAPI
AcpiNotification (  
	IN EFI_ACPI_SDT_HEADER *Table,  
	IN EFI_ACPI_TABLE_VERSION Version,  
	IN UINTN TableKey)
{
	EFI_STATUS Status = EFI_SUCCESS;

	if (Table->Signature == EFI_ACPI_6_1_DIFFERENTIATED_SYSTEM_DESCRIPTION_TABLE_SIGNATURE){
		Status = UpdateDsdtTable(Table,Version,TableKey);
	}
	
	return Status;
}



EFI_STATUS
EFIAPI
UpdateACPIEntry (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
)
{
   EFI_STATUS Status = EFI_SUCCESS;    
   
   Status = gBS->LocateProtocol (&gEfiAcpiSdtProtocolGuid, NULL, (VOID**) &gAcpiSdt);
   if (EFI_ERROR (Status)) {
	DEBUG((EFI_D_ERROR, "[WinDsdtUpdate] Failed to Locate SDT protocol \r\n"));
	goto Error;
   }

   Status = gBS->InstallMultipleProtocolInterfaces(&ImageHandle,
	   &gEfiWinDsdtUpdateProtocolGuid,
	   (void *)&gEfiWinDsdtUpdateProtocol,
	   NULL);

   if (EFI_ERROR(Status)) {
	   DEBUG((EFI_D_ERROR, "[WinDsdtUpdate] Failed to Install EfiWinDsdtUpdate protocol \r\n"));
	   goto Error;
   }

   // Register callback for when an ACPI table is loaded
  	gAcpiSdt->RegisterNotify(TRUE,AcpiNotification);

Error:
  	return Status;
  
}