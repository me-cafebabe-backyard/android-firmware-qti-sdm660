/** @file TargetInitLib.c
 
  @brief Target Specific Initialization Functions
 
  Copyright (c) 2013 by Qualcomm Technologies, Inc. All Rights Reserved.

**/ 
 
/*=======================================================================
                        Edit History
  $Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/TargetInitLib/TargetInitLib.c#1 $
  $DateTime: 2016/05/23 02:27:48 $
  $Author: pwbldsvc $

  when       who     what, where, why
  --------   ----    ---------------------------------------------------
  11/15/13   vk      Disable DebugDisableFuse and Crash check
  03/04/13   niting  Add check for HLOS crash cookied address based on HW version
  01/28/13   vishalo Initial Version

========================================================================*/

#include <Uefi.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Library/PcdLib.h>


VOID
TargetEarlyInit (VOID)
{
}

VOID
TargetLateInit (VOID)
{
  return;
}

BOOLEAN
CheckDebugDisableFuse (VOID)
{
#if 0
  UINT8 AuthEnMask =  PcdGet32(PcdSecbootAuthEnMask);
  volatile UINT32* SecbootReg = (UINT32 *)PcdGet32(PcdSecbootRegAddr);
  BOOLEAN SecbootEnabledFlag = FALSE;

  // Check EFuse to see if secure boot is enabled (AuthEn bit is set)
  if ((*SecbootReg & AuthEnMask) == AuthEnMask)
    SecbootEnabledFlag = TRUE;
  else
    SecbootEnabledFlag = FALSE;

  return SecbootEnabledFlag;
#endif
  return FALSE;  
}

BOOLEAN
CheckCrashHappened (VOID)
{
#if 0  
  UINT32* HLOSCrashCookieAddr = (UINT32*)PcdGet32(PcdHLOSCrashCookieAddr);
  BOOLEAN CrashHappenedFlag = FALSE;

  if (CheckDebugDisableFuse() == FALSE)
  {
    if (*HLOSCrashCookieAddr == 1)
      CrashHappenedFlag = TRUE;
  }

  return CrashHappenedFlag;
#endif
  return FALSE;  
}

BOOLEAN
CheckCarvOutModeEnabled (VOID)
{
  return FALSE;
}

/* Perform target specific handling if crash happened*/
EFI_STATUS
CrashHappenedHandler (VOID)
{
  return EFI_SUCCESS;
}
