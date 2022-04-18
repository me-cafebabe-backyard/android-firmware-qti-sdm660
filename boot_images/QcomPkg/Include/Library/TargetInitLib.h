/** @file TargetInitLib.h
   
  Contains TargetInit specific library functions.

  Copyright (c) 2013 by Qualcomm Technologies, Inc. All Rights Reserved.

**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 01/22/13   vk      Initial Version
=============================================================================*/
#ifndef __TARGET_INIT_LIB_H__
#define __TARGET_INIT_LIB_H__

#include <Uefi.h>

VOID
TargetEarlyInit (VOID);

VOID
TargetLateInit (VOID);

BOOLEAN
CheckDebugDisableFuse (VOID);

BOOLEAN
CheckCarvOutModeEnabled (VOID);

BOOLEAN
CheckCrashHappened(VOID);

EFI_STATUS
CrashHappenedHandler (VOID);

#endif /* __TARGET_INIT_LIB_H_ */
