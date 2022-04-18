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
// 09/02/16   ai      Correct UEFI start time
// 06/07/16   vk      Use PCD for vectors
// 02/18/16   bh      Use offsets based on FD base
// 01/21/16   vk      Do not mask D and A bit for EL1
// 10/11/15   vk      Zero out stack
// 03/15/15   jb      Add support for starting in EL2 or EL1
// 02/11/15   vk      Fix Q register access crash
// 12/11/14   bh      Invalidate TLB
// 11/13/16   jb      Add Early cache init skip
// 10/18/14   jb      Add EL2 support and update PCDs to 64bits
// 09/18/14   vk      Invalidate Cache
// 05/05/14   vk      Setup exception vectors
// 04/30/14   vk      Add PRE_SIL for 8916
// 03/03/14   vk      Disable MMU and interrupts first
// 02/14/14   vk      Initial revision
//
//============================================================================


#include <Library/PcdLib.h>
#include <AsmMacroIoLibV8.h>
#include <Chipset/AArch64.h>

#define  VECTOR_TABLE_SIZE    #0x800

.text
.align 3

.global _StackBase 
.global _StackSize
.global CNTFRQ 
.global gUEFIStartCounter

GCC_ASM_EXPORT (_ModuleEntryPoint)

GCC_ASM_IMPORT (CEntryPoint)
GCC_ASM_IMPORT (ArmWriteCpacr)
GCC_ASM_IMPORT (ArmEnableInstructionCache)
GCC_ASM_IMPORT (ArmInvalidateInstructionCache)
GCC_ASM_IMPORT (ArmInvalidateTlb)
GCC_ASM_IMPORT (ArmEnableDataCache)
GCC_ASM_IMPORT (InitStackCanary)

gUEFIStartCounter:
  .quad 0

_StackBase:
  .quad FixedPcdGet64(PcdEmbeddedFdBaseAddress) + 0x00390000

_StackSize:
  .quad 0x00040000

CNTFRQ:
  .quad FixedPcdGet32(PcdArmArchTimerFreqInHz)

_ModuleEntryPoint:
  mov x0, #0

  /* Save UEFI Start Time */
  mrs   x0, cntpct_el0          /* Read CNTPCT */
  ldr   x1, =gUEFIStartCounter
  str   x0, [x1]

  /* Clear x0 for function calls below */
  mov x0, #0
  mov x1, #0

  /* First ensure all interrupts are disabled */
  bl ASM_PFX(ArmDisableInterrupts)

  /* Ensure that the MMU and caches are off */
  bl ASM_PFX(ArmDisableCachesAndMmu)
  
  /* Invalidate Instruction Cache and TLB */ 
  bl ASM_PFX(ArmInvalidateInstructionCache)

  bl ASM_PFX(ArmInvalidateTlb)

  /* Get current EL in x0 */
  EL1_OR_EL2_OR_EL3(x0)

1:  b _Start
2:  b _Start

  /* Do not trap any access to Floating Point and Advanced SIMD in EL3. */
  /* Note this works only in EL3, x0 has current EL mode */
3:  mov x0, #0
  bl ArmWriteCptr

_SetupELx:
  mov x0, #0x30           /* RES1 */
  orr x0, x0, #(1 << 0)   /* Non-secure bit */
  orr x0, x0, #(1 << 8)   /* HVC enable */
  orr x0, x0, #(1 << 10)  /* 64-bit EL2 */
  msr scr_el3, x0

  msr cptr_el3, xzr       /* Disable copro. traps to EL3 */

  ldr x0, CNTFRQ
  msr cntfrq_el0, x0

  msr sctlr_el2, xzr

  /* Now setup our EL1. Controlled by EL2 config on Model */
  mrs x0, hcr_el2         /* Read EL2 Hypervisor configuration Register */
  orr x0, x0, #(1 << 31)  /* Set EL1 to be 64bit */

  /* Send all interrupts to their respective Exception levels for EL2 */
  mov x5, #(1 << 3)
  bic x0, x0, x5          /* Disable virtual FIQ */

  mov x5, #(1 << 4)
  bic x0, x0, x5          /* Disable virtual IRQ */

  mov x5, #(1 << 5)
  bic x0, x0, x5          /* Disable virtual SError and Abort */

  msr hcr_el2, x0         /* Write back our settings */

  /* Enable architected timer access */
  mrs x0, cnthctl_el2
  orr x0, x0, #3          /* Enable EL1 access to timers */
  msr cnthctl_el2, x0

  mrs x0, cntkctl_el1
  orr x0, x0, #3          /* EL0 access to counters */
  msr cntkctl_el1, x0

  /* Set ID regs */
  mrs x0, midr_el1
  mrs x1, mpidr_el1
  msr vpidr_el2, x0
  msr vmpidr_el2, x1

  /* Coprocessor traps. */
  mov x0, #0x33ff
  msr cptr_el2, x0        /* Disable copro. traps to EL2 */

  msr hstr_el2, xzr       /* Disable CP15 traps to EL2 */

  mov x0, #CPACR_CP_FULL_ACCESS
  bl ArmWriteCpacr        /* Disable copro traps to EL1 */

  /* Switch to ELx NS */
  bl ArmDisableAlignmentCheck

  adr x0, _Start          /* Load start address for ELx */
  msr elr_el3, x0

  LoadConstantToReg (FixedPcdGetBool(PcdSwitchToEL1), x1)
  cmp x1, #0
  bne EL1
EL2:
  mov x1, #0x3c9 /* DAIF, EL2, EL specific SP */
  msr spsr_el3, x1
  eret

EL1:
  mov x1, #0xc5 /* IF, EL1, EL specific SP */
  msr spsr_el3, x1
  eret

_Start:
  /* Get current EL in x0 */
  EL1_OR_EL2(x0)
1:  b _SetupExceptionVector

2:  mov x0, #ARM_HCR_IMO
    bl ArmWriteHcr  

_SetupExceptionVector:
  LoadConstantToReg (FixedPcdGet64(PcdCpuVectorBaseAddress), x0)
  ldr x1, dead
  add x2, x0, VECTOR_TABLE_SIZE 
  mov x3, x0
_FillVectors:
  stp     x1, x1, [x3], #16 /* Fill every 16 byte */
  cmp     x3, x2 
  b.lt    _FillVectors
  
  /* Update VBAR */
  bl ArmWriteVBar

_DonNotTrap_VFP_SIMD:
  mrs x0, CPACR_EL1
  orr x0, x0, #0x300000  /* Set FPEN Bits 20 and 21 for not trapping 
                            FP and Advanced SIMD instructions */
  msr CPACR_EL1, x0
    
_SetupPrimaryCoreStack:
  ldr x0, _StackBase     /* Stack base arg0 */
  ldr x1, _StackSize     /* Stack size arg1 */
  
  /*Zero Init stack */
  add x2, x0, x1 
  mov x3, x0

  mov v4.d[0], xzr
  mov v4.d[1], xzr
  mov v5.2d, v4.2d 
  mov v6.2d, v4.2d
  mov v7.2d, v4.2d 
  
_ClearStack: 
  /* Assumes StackBase is 128-bit aligned, StackSize is a multiple of 64B */
  st4     {v4.2d, v5.2d, v6.2d, v7.2d}, [x3], #64  /* Fill every 64 bytes */
  cmp     x3, x2                                   /* Compare Size */ 
  b.lt     _ClearStack 
  
  add sp, x2, xzr                                  /* Initalize SP */

_EnableCache:
#ifdef PRE_SIL
  LoadConstantToReg (FixedPcdGet32(PcdSkipEarlyCacheMaint), x0)
  cmn x0, #0
  b.ne _PrepareArguments
#endif
  bl ArmInvalidateDataCache
  bl ASM_PFX(ArmEnableInstructionCache)
  bl ASM_PFX(ArmEnableDataCache)

_PrepareArguments:
  /* Initialize Stack Canary */
  bl ASM_PFX(InitStackCanary)

  /* x0 = _StackBase and x1 = _StackSize */
  ldr x0, _StackBase     /* Stack base arg0 */
  ldr x1, _StackSize     /* Stack size arg1 */
  bl CEntryPoint

.align 3
dead:  
  b dead                      /* We should never get here */

