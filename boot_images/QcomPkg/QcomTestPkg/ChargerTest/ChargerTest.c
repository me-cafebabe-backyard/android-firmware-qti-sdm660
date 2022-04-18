/** @file ChargerTest.c
   
  Tests for Charger

  Copyright (c) 2010-2013, 2015 Qualcomm Technologies, Inc. All rights reserved.
  
**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 07/13/15   al      Changing TPL_NOTIFY to TPL_CALLBACK
 04/29/13   yg      Add back Stall
 04/04/13   yg      Some cleanup
 07/03/12   aus     Replaced DEBUG with AsciiPrint
 02/02/12   sm      Replaced DEBUG messages with AsciiPrint
 06/06/11   dy      New File

=============================================================================*/

#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Library/UefiLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>

#include <Protocol/EFICharger.h>
#include "Library/QcomLib.h"

EFI_EVENT  ChargerEvent;
EFI_BATTERY_CHARGING_COMPLETION_TOKEN ChargerCompletionToken;
BOOLEAN    ChargingEventOccurred = FALSE;

VOID EFIAPI ChargerEventHandler(IN EFI_EVENT Event, IN VOID *Context);

/* Sleep without burning CPU cycles */
EFI_STATUS
WaitForEventTimeout (IN UINT32   Timeoutms)
{
  UINTN           Index;
  EFI_STATUS      Status = EFI_NOT_READY;
  EFI_EVENT       TimerEvent;
  EFI_EVENT       WaitList[3];
  UINT64          TimeoutVal;
  EFI_INPUT_KEY   KeyVal;

  if (Timeoutms == 0)
    return EFI_INVALID_PARAMETER;

  /* Create a Timer event  */
  Status = gBS->CreateEvent (EVT_TIMER, 0, NULL, NULL, &TimerEvent);

  if (Status != EFI_SUCCESS)
    return Status;

  /* Convert to 100ns units */
  TimeoutVal = Timeoutms * 10000;

  /* Set Timer event */
  gBS->SetTimer (TimerEvent, TimerRelative, TimeoutVal);

  /* Wait for some event or the timer */
  WaitList[0] = TimerEvent;
  WaitList[1] = gST->ConIn->WaitForKey;
  Status = gBS->WaitForEvent (2, WaitList, &Index);
  if (Index == 1)
    gST->ConIn->ReadKeyStroke (gST->ConIn, &KeyVal);
  gBS->CloseEvent (TimerEvent);

  return Status;
}

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
ChargerTestMain (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS  Status = EFI_SUCCESS;
  EFI_BATTERY_CHARGING_PROTOCOL  *ChargerProtocol = NULL;
  
  /* Parameters to get current status of battery */
  UINT32 CurrentSOC = 0;
  UINT32 RatedCapacity = 0;
  INT32  ChargeCurrent = 0;
  
  /* Parameters to charge battery */
  UINT32 TargetSOC;
  UINT32 MaxCurrent = 500;
  
  /* Locate Charger Protocol */
  Status = gBS->LocateProtocol(
                  &gBatteryChargerProtocolGuid,
                  NULL,
                  (VOID**) &ChargerProtocol );
  
  if (Status != EFI_SUCCESS) 
  {
    AsciiPrint("ERROR: ChargerTest - Failed to locate Charger Protocol! Error Code: 0x%08X\r\n", Status);
    return Status;
  }
  AsciiPrint("ChargerTest - Charger Protocol located!\n");
  
  /* Create Charger Event Token */
  Status = gBS->CreateEvent ( EVT_NOTIFY_SIGNAL,
                              TPL_CALLBACK,
                              ChargerEventHandler,
                              NULL,
                              &ChargerEvent);
  
  if (Status != EFI_SUCCESS)
  {
    AsciiPrint("ERROR: ChargerTest - Failed to create completion event token! Error Code: 0x%08X\r\n", Status);
    return Status;
  }
  
  ChargerCompletionToken.Event = ChargerEvent;
  
  /* GetBatteryStatus - Get current SOC */
  Status = ChargerProtocol->GetBatteryStatus( ChargerProtocol,
                                              &CurrentSOC,
                                              &RatedCapacity,
                                              &ChargeCurrent );

  if (Status != EFI_SUCCESS) 
  {
    AsciiPrint("ERROR: ChargerTest - Failed to get battery status! Error Code: 0x%08X\r\n", Status);
    return Status;
  }
  AsciiPrint("ChargerTest - Successfully got battery status!\n");
  
  AsciiPrint("StateOfCharge: %d\n", CurrentSOC);
  AsciiPrint("RatedCapacity: %d\n", RatedCapacity);
  AsciiPrint("ChargeCurrent: %d\n", ChargeCurrent);
  
  /* Charge halfway to 100% from current SOC */
  TargetSOC = CurrentSOC + ((100 - CurrentSOC) / 2);
  AsciiPrint("\nCharge to: %d\n", TargetSOC);
  
  ChargingEventOccurred = FALSE;
  
  /* Start battery charging */
  Status = ChargerProtocol->ChargeBattery( ChargerProtocol,
                                           MaxCurrent,
                                           TargetSOC,
                                           &ChargerCompletionToken );
  
  if (Status != EFI_SUCCESS) 
  {
    AsciiPrint("ERROR: ChargerTest - Failed to start charging! Error Code: 0x%08X\r\n", Status);
    return Status;
  }
  AsciiPrint("ChargerTest - Successfully started charging!\n");
  
  while ( FALSE == ChargingEventOccurred )
  {
    AsciiPrint("Sleep for 5 seconds\r\n");
    // Wait for event doesn't work for Registered Key Notifications
    //WaitForEventTimeout (5000);
    gBS->Stall (5000000);      
    Status = ChargerProtocol->GetBatteryStatus( ChargerProtocol,
                                                &CurrentSOC,
                                                &RatedCapacity,
                                                &ChargeCurrent );
                                                
    AsciiPrint("StateOfCharge: %d\n", CurrentSOC);
    AsciiPrint("ChargeCurrent: %d\n", ChargeCurrent);
  }
  
  AsciiPrint("Done Charging! Press any key to exit\r\n");

  ReadAnyKey (NULL, 0);
  
  return EFI_SUCCESS;
}

/**
  ChargerEventHandler()
  
  @brief
  Charger event handler for when the charger state has changed
**/
VOID EFIAPI ChargerEventHandler(IN EFI_EVENT Event, IN VOID *Context)
{
  if ((ChargerCompletionToken.Status != EfiBatteryChargingStatusSuccess) &&
      (ChargerCompletionToken.Status != EfiBatteryChargingStatusNone))
  {
    AsciiPrint("ERROR: ChargerTest - Charger Error Detected!\r\n");
    Print(L"!!!Charger Error Detected!!!\r\n");
  }
  
  AsciiPrint("+++++Pmic Charger Test app Signal, ChgSt(%d)\r\n",ChargerCompletionToken.Status);
  Print(L"\r\n>>>>>>Pmic Charger Signal, ChgSt(%d)\r\n",ChargerCompletionToken.Status);
  
  /* Indicate that charging event has occurred */
  ChargingEventOccurred = TRUE;
}

