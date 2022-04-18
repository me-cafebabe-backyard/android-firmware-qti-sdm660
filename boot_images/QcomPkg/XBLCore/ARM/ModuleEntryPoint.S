//------------------------------------------------------------------------------ 
//
//  Copyright (c) 2012-2016, Qualcomm Technologies Inc. All rights reserved.
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

.global gUEFIStartCounter

GCC_ASM_EXPORT (_ModuleEntryPoint)

GCC_ASM_IMPORT (CEntryPoint)
GCC_ASM_IMPORT (_ReleaseInfo)

GCC_ASM_IMPORT (ArmDisableInterrupts)
GCC_ASM_IMPORT (ArmDisableCachesAndMmu)
GCC_ASM_IMPORT (ArmInvalidateInstructionCache)
GCC_ASM_IMPORT (ArmInvalidateTlb)
GCC_ASM_IMPORT (ArmInvalidateDataCache)
GCC_ASM_IMPORT (ArmEnableInstructionCache)
GCC_ASM_IMPORT (ArmEnableDataCache)
GCC_ASM_IMPORT (InitStackCanary)

gUEFIStartCounter:
  .long 0

_ModuleEntryPoint:
  mov r0, #0

  /* First ensure all interrupts are disabled */
  bl ArmDisableInterrupts

  /* Ensure that the MMU and caches are off */
  bl ArmDisableCachesAndMmu
  
  /* Invalidate Instruction Cache and TLB */ 
  bl ArmInvalidateInstructionCache

  /* Setup stack */
  LoadConstantToReg (FixedPcdGet32(PcdPrePiStackBase) ,r0)    // stack base arg0  
  LoadConstantToReg (FixedPcdGet32(PcdPrePiStackSize) ,r1)    // stack size arg1  
  add     r4, r0, r1

  /* Enter SVC mode and set up SVC stack pointer */
  mov     r5,#0xD3
  msr     CPSR_c,r5
  mov     r13,r4


  bl ArmInvalidateDataCache
  bl ArmInvalidateTlb

  /* Enable NEON register in case folks want to use them for optimizations (CopyMem) */
  mrc     p15, 0, r0, c1, c0, 2
  orr     r0, r0, #0x00f00000   // Enable VPF access (V* instructions)
  mcr     p15, 0, r0, c1, c0, 2
  mov     r0, #0x40000000       // Set EN bit in FPEXC

  /* Fill vector table with branchs to current pc (jmp $) */
  LoadConstantToReg (FixedPcdGet32(PcdCpuVectorBaseAddress) ,r0)
  ldr     r1, ShouldNeverGetHere
  movs    r2, #0
FillVectors:
  str     r1, [r0, r2]
  adds    r2, r2, #4
  cmp     r2, #32
  bne     FillVectors

  /* Write Vector base address to VBAR */
  LoadConstantToReg (FixedPcdGet32(PcdCpuVectorBaseAddress) ,r0)
  mcr     p15, 0, r0, c12, c0, 0
  isb                               /* Sync changes to control registers */

  bl ArmInvalidateDataCache
  bl ArmEnableInstructionCache
  bl ArmEnableDataCache

  // Initialize Stack Canary
  bl InitStackCanary
  
  /* before we call C code, lets setup the stack pointer in internal RAM */
  LoadConstantToReg (FixedPcdGet32(PcdPrePiStackBase) ,r0)    // stack base arg0  
  LoadConstantToReg (FixedPcdGet32(PcdPrePiStackSize) ,r1)    // stack size arg1

  /* Call C entry point */
  blx     CEntryPoint                                         /* Assume C code is thumb */

ShouldNeverGetHere:
  /* _CEntryPoint should never return */
  b       ShouldNeverGetHere
  b       _ReleaseInfo
  

