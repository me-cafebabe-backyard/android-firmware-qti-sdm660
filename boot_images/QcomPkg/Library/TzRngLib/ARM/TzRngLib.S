//============================================================================
//
//                 TzRngLib
//
// Copyright (c) 2016 Copyright Qualcomm Technologies, Inc.  All Rights Reserved.
// Qualcomm Technologies Proprietary and Confidential.
//   
//============================================================================

//============================================================================
//
//                           EDIT HISTORY FOR FILE
//
// This section contains comments describing changes made to the module.
// Notice that changes are listed in reverse chronological order.
//
//
// when       who     what, where, why
// --------   ---     --------------------------------------------------------
// 11/29/16   aus     Added support for 32 bit LLVM compilation
//
//============================================================================

//============================================================================
//                             MODULE EXPORTS
//============================================================================

  GCC_ASM_EXPORT(GetRNGVal)

  GCC_ASM_IMPORT(ArmCleanDataCacheEntryByMVA)
  GCC_ASM_IMPORT(ArmInvalidateDataCacheEntryByMVA)


//============================================================================
//                                 MACROS 
//============================================================================

#define SmcCall(func)                 \
smc_loop_##func:                  ;   \
    smc           #0x0            ;   \
    adds          r0, #0          ;   \
    bgt           smc_loop_##func

#define ZeroBuffer           \
    ldr r0, =BUFFER        ; \
    mov r2, #0             ; \
    str r2, [r0]           ; \
    bl ArmCleanDataCacheEntryByMVA 

#define InvalidateBuffer        \
    ldr r0, =BUFFER           ; \
    bl ArmInvalidateDataCacheEntryByMVA

//============================================================================
//                                FUNCTIONS
//============================================================================

.text
.align 2

#define NUM_BYTES 8

//============================================================================
//
//  UINTN GetRNGVal_armv7 (VOID)//
//
//============================================================================

#define CMD_ID    0x02801202 // (0x2801 << 12) | (2 << 8) | 2

GetRNGVal_armv7:
    ZeroBuffer
    ldr r0, =CMD_ID  
    ldr r2, =BUFFER
    mov r3, #NUM_BYTES
    SmcCall(armv7)
    cmp r0, #0
    bne loop0
    InvalidateBuffer
    ldr r1, =BUFFER
    ldr r0, [r1]
loop0:
    pop {pc}

//============================================================================
//
//  UINTN GetRNGVal_armv8 (VOID)//
//
//============================================================================

#define SMC_ID    0x02000A01
#define PARAM_ID  0x00000022
    
GetRNGVal_armv8: 
    ZeroBuffer
    ldr r0, =SMC_ID
    mov r1, #PARAM_ID
    ldr r2, =BUFFER
    mov r3, #NUM_BYTES
    SmcCall(armv8)
    cmp r0, #0
    bne loop1
    InvalidateBuffer
    ldr r1, =BUFFER
    ldr r0, [r1]
loop1:
    pop {pc}

//============================================================================
//
//  UINTN GetRNGVal (VOID)//
//
//============================================================================

#define IS_ARMV8_SMC_ID   0x02000601
#define IS_ARMV8_PARAM_ID 0x00000001
#define IS_ARMV8_PARAM    0x02000602

// UINTN GetRNGVal(VOID)
GetRNGVal:
    push {lr}           // Use tail recursion
    ldr r0, =JUMP_OFFSET
    ldr r0, [r0]
    adr r1, jumptable
    ldr pc, [r1, r0]
jumptable:
    .long check_armv8
    .long GetRNGVal_armv7
    .long GetRNGVal_armv8
check_armv8:
    ldr r0, =IS_ARMV8_SMC_ID
    mov r1, #IS_ARMV8_PARAM_ID
    ldr r2, =IS_ARMV8_PARAM
    SmcCall(check_armv8)
    cmp r0, #0
    ldr r1, =JUMP_OFFSET
    bne is_armv7
    mov r0, #8 // Set jump offset to GetRNGVal_armv8
    str r0, [r1]
    b GetRNGVal_armv8
is_armv7:
    mov r0, #4 // Set jump offset to GetRNGVal_armv7
    str r0, [r1]
    b GetRNGVal_armv7

//============================================================================
//                                 DATA
//============================================================================

   .data
   .align 2
BUFFER:
    .long 0
JUMP_OFFSET:
    .long 0
