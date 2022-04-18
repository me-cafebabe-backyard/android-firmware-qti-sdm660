//------------------------------------------------------------------------------ 
//
//  Copyright (c) 2016, Qualcomm Technologies Inc. All rights reserved.
//  Portions Copyright (c) 2011-2013, ARM Limited. All rights reserved.
//
//  This program and the accompanying materials
//  are licensed and made available under the terms and conditions of the BSD License
//  which accompanies this distribution.  The full text of the license may be found at
//  http://opensource.org/licenses/bsd-license.php
//
//  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
//  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
//
//------------------------------------------------------------------------------

//=============================================================================
//                              EDIT HISTORY
//
//
// when       who     what, where, why
// --------   ---     ---------------------------------------------------------
// 11/29/16   aus     Added support for 32 bit LLVM compilation
//
//============================================================================

#include <AsmMacroIoLib.h>
#include <Library/PcdLib.h>
#include <AutoGen.h>

.text
.align 2

GCC_ASM_IMPORT (_ModuleEntryPoint)
GCC_ASM_IMPORT (InitStackCanary)

GCC_ASM_EXPORT (_QCModuleEntry)

_QCModuleEntry:
  cmp r0, #0
  beq entry_point
  
  // Save and restore passed parameters before initialization of stack canary
  push {r0-r3,r14}
  bl InitStackCanary 
  pop {r0-r3,r14}

entry_point: 
  b _ModuleEntryPoint
 
