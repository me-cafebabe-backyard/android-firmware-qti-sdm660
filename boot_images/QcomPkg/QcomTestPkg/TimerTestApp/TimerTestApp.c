/** @file TimerTestApp.c
   
  Tests for Timer and Stall

  Copyright (c) 2010-2011, Qualcomm Technologies Inc. All rights reserved.
  
**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 07/13/15   al      Changing TPL_NOTIFY to TPL_CALLBACK
 06/27/12   pbi     Updated for timetick changes
 07/30/11   sy      Adding TestInterface Library
 03/10/11   EBR     Created test for Timer and Stall

=============================================================================*/

#include <Uefi.h>
#include <Library/PcdLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/TestInterface.h>

#include "TimetickUEFI.h"

static Timetick_timer_Type Timer;

/**
Used to handle the 1 second event test
*/
EFI_EVENT TimerEvent;

/**
  Converts the timeticks passed into useconds. 
   
  @param[in] tick_start Starting Tick 
  @param[in] tick_end   Ending Tick 
   
  @return Time passed between the two ticks in useconds 
**/
UINT64
EFIAPI microseconds_passed (UINT64 tick_start, UINT64 tick_end)
{
  UINT32 TimetickFreq;
  UINT64 uSeconds;
  Timetick_GetFreq(Timer, &TimetickFreq);
  uSeconds = tick_end - tick_start;
  uSeconds = MultU64x32(uSeconds, 1000000);
  uSeconds = DivU64x32(uSeconds, TimetickFreq);
  return uSeconds;
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
TimerTestMain (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  UINTN EventIndex;
  EFI_STATUS  Status;
  UINT64 starting_tick;
  UINT64 ending_tick;
  UINT64 microseconds_taken;
  UINT64 deviation;
  
  //
  // Create the timer event to implement a timer
  //
  TEST_START("TimerTest");
  Status = gBS->CreateEvent (
                  EVT_TIMER,
                  TPL_CALLBACK,
                  NULL,
                  NULL,
                  &TimerEvent
                  );
  if(EFI_ERROR (Status)) {
	TestStatus("TimerTest",Status);
    TEST_STOP("TimerTest");
    return Status;
  }

  if(PcdGet32(PcdQTimerEnabled))
  {
    Timer = TIMETICK_QTIMER;
  }
  else
  {
    Timer = TIMETICK_TIMER_ADGT;
  }

  // Set timer for 1 second
  Timetick_Init();
  AsciiPrint("Registering Timer Event: 100 ms relative timer\n");
  gBS->SetTimer(TimerEvent, TimerRelative, 1000000);
  Timetick_GetCount(Timer,&starting_tick);
  AsciiPrint("Waiting for 100 ms\n");
  gBS->WaitForEvent(1, &TimerEvent, &EventIndex);
  Timetick_GetCount(Timer, &ending_tick);
  AsciiPrint("100 ms timer event signaled\n");
  microseconds_taken = microseconds_passed(starting_tick, ending_tick);
  deviation = microseconds_taken - 100000;
  AsciiPrint("Deviation from 100 ms was (in usec): %d\n", (UINT32)deviation);


  // Test Stall
  AsciiPrint("Stalling for 100 ms\n");
  Timetick_GetCount(Timer, &starting_tick);
  gBS->Stall(100000);
  Timetick_GetCount(Timer, &ending_tick);
  AsciiPrint("100 ms stall complete\n");
  microseconds_taken = microseconds_passed(starting_tick, ending_tick);
  deviation = microseconds_taken - 100000;
  AsciiPrint("Deviation from 100 ms was (in usec): %d\n", (UINT32)deviation);

  TestStatus("TimerTest",Status);
  TEST_STOP("TimerTest");
  return Status;
}
