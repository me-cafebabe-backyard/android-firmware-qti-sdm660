/** @file ClockAppEFIProtocol.c 
   
  This file contains application test code for clock driver. 
  The code uses clock EFI protocol interface to make appropriate 
  function calls.   

  Copyright (c) 2010-2012, Qualcomm Technologies Inc. All rights reserved.
  
**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 01/25/13   vk      Fix warning
 07/03/12   aus     Replaced DEBUG with AsciiPrint
 12/23/10   vs      Created.

=============================================================================*/


/*=========================================================================
      Include Files
==========================================================================*/

#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/EFIClock.h>
#include "ClockTestUEFI.h"


/*=========================================================================
      Functions
==========================================================================*/

/**
  Clock test using EFI protocol only. 

  @param 
  None. 

  @return
  None.
**/

void ClockTestUsingEFIProtocol()
{
  EFI_STATUS          eResult;
  EFI_CLOCK_PROTOCOL  *mClockProtocol;
  CONST CHAR8         *szClockName;  
  UINT32              nCount, nClockID, nFreqHz;
  BOOLEAN             nFlag, bIsEnabled;

  eResult = gBS->LocateProtocol (
                  &gEfiClockProtocolGuid,
                  NULL,
                  (VOID **) &mClockProtocol
                  );
  ASSERT_EFI_ERROR(eResult);


  AsciiPrint ("\n==================o===================\n");
  AsciiPrint ("Clock Application Driver - EFI Protocol\n");
  AsciiPrint ("========================================\n");
  nCount = 0; 
  while(1)
  {
    /*
     * Get clock name
     */
    szClockName = ClockTestList[nCount].szName;
    if(szClockName[0] == '\0') 
    {
       /*
        * Reached the end of clock test array
        */
       break;
    }
    else
    {
      AsciiPrint ("Checking clock \"%a\" ...\n", szClockName);
    }

    /*
     *  For each clock get the ID
     */
    eResult = mClockProtocol->GetClockID(mClockProtocol, szClockName, &nClockID);
    if(eResult != EFI_SUCCESS) 
    {
      /*
       * This clock is either not found or something has gone wrong. 
       * Either way we can't do rest of the tests so try the next clock. 
       */

      AsciiPrint ("WARNING: Clock \"%a\" ID not obtained!\n", szClockName);
      AsciiPrint ("========================================\n");
      nCount++;
      continue;
    }

    /*
     * Check IsClockOn
     */
    eResult = mClockProtocol->IsClockOn(mClockProtocol, nClockID, &nFlag);
    if(eResult != EFI_SUCCESS) 
    {
      AsciiPrint ("WARNING: IsClockOn: returned an error!\n");
    }
    else
    {
      AsciiPrint ("IsClockOn: %a\n", (nFlag == TRUE) ? "TRUE":"FALSE");
    }

    /*
     *  Check IsClockEnabled   
     */
    eResult = mClockProtocol->IsClockEnabled(mClockProtocol, nClockID, &nFlag);
    bIsEnabled = nFlag;
    if(eResult != EFI_SUCCESS) 
    {
      AsciiPrint ("WARNING: IsClockEnabled: returned an error!\n");
    }
    else
    {
      AsciiPrint ("IsClockEnabled: %a\n", (nFlag == TRUE) ? "TRUE":"FALSE");
    }

    /*
     * If clock is not enabled, then enable it
     */
    if(!bIsEnabled)
    {    
      eResult = mClockProtocol->EnableClock(mClockProtocol, nClockID);
      if(eResult != EFI_SUCCESS) 
      {
        AsciiPrint ("WARNING: EnableClock: returned an error!\n");
      }
      else
      {
        AsciiPrint ("EnableClock: SUCCESS\n");
      }

      /*
       * Recheck IsClockEnabled
       */
      eResult = mClockProtocol->IsClockEnabled(mClockProtocol, nClockID, &nFlag);
      if(eResult != EFI_SUCCESS) 
      {
        AsciiPrint ("WARNING: Rechecking IsClockEnabled: returned an error!\n");
      }
      else
      {
        AsciiPrint ("Rechecking IsClockEnabled: %a\n", (nFlag == TRUE) ? "TRUE":"FALSE");
      }

      /*
       * Recheck IsClockOn
       */
      eResult = mClockProtocol->IsClockOn(mClockProtocol, nClockID, &nFlag);
      if(eResult != EFI_SUCCESS) 
      {
        AsciiPrint ("WARNING: Rechecking IsClockOn: returned an error!\n");
      }
      else
      {
        AsciiPrint ("Rechecking IsClockOn: %a\n", (nFlag == TRUE) ? "TRUE":"FALSE");
      }

      /*
       * Only change/set clock frequency of the clocks that were enabled by us
       */
      if(ClockTestList[nCount].nFreqHz > 0)
      {
        //Try exact frequency match
        eResult = mClockProtocol->SetClockFreqHz(mClockProtocol, nClockID, 
                                                 ClockTestList[nCount].nFreqHz, 
                                                 EFI_CLOCK_FREQUENCY_HZ_EXACT, &nFreqHz);
        if(eResult != EFI_SUCCESS) 
        {
          AsciiPrint ("WARNING: SetClockFreqHz: returned an error!\n");
        }
        else
        {
          AsciiPrint ("SetClockFreqHz: %d\n", nFreqHz);
        }
    
        /*
         * Get clock frequency
         */
        eResult = mClockProtocol->GetClockFreqHz(mClockProtocol, nClockID, &nFreqHz);
        if(eResult != EFI_SUCCESS) 
        {
          AsciiPrint ("WARNING: GetClockFreqHz: returned an error!\n");
        }
        else
        {
          AsciiPrint ("GetClockFreqHz: %d\n", nFreqHz);
        }
      }
    }

    /*
     * Get clock frequency
     */
    eResult = mClockProtocol->CalcClockFreqHz(mClockProtocol, nClockID, &nFreqHz);
    if(eResult != EFI_SUCCESS) 
    {
      AsciiPrint ("WARNING: CalcClockFreqHz: returned an error!\n");
    }
    else
    {
      AsciiPrint ("CalcClockFreqHz: %d\n", nFreqHz);
    }

    /*
     * Only disable clocks that weren't enabled by us
     */
    if(!bIsEnabled)
    {
      eResult = mClockProtocol->DisableClock(mClockProtocol, nClockID);
      if(eResult != EFI_SUCCESS) 
      {
        /*
         * DisableClock 
         */
        AsciiPrint ("WARNING: DisableClock: returned an error!\n");
      }
      else
      {
        AsciiPrint ("DisableClock: SUCCESS\n");
      }
  
      /*
       * Recheck IsClockEnabled
       */
      eResult = mClockProtocol->IsClockEnabled(mClockProtocol, nClockID, &nFlag);
      if(eResult != EFI_SUCCESS) 
      {
        AsciiPrint ("WARNING: Rechecking IsClockEnabled: returned an error!\n");
      }
      else
      {
        AsciiPrint ("Rechecking IsClockEnabled: %a\n", (nFlag == TRUE) ? "TRUE":"FALSE");
      }
  
      /*
       * Recheck IsClockOn
       */
      eResult = mClockProtocol->IsClockOn(mClockProtocol, nClockID, &nFlag);
      if(eResult != EFI_SUCCESS) 
      {
        AsciiPrint ("WARNING: Rechecking IsClockOn: returned an error!\n");
      }
      else
      {
        AsciiPrint ("Rechecking IsClockOn: %a\n", (nFlag == TRUE) ? "TRUE":"FALSE");
      }
    }

    AsciiPrint ("========================================\n");
    nCount++;
  }

  AsciiPrint ("\n");
}
