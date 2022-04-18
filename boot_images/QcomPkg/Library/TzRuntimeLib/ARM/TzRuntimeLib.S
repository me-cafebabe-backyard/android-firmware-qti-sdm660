//============================================================================
//
//            TzRuntimeLib
//
// GENERAL DESCRIPTION
//   collection of TZ call routines in assembly
//
// Copyright 2016, by Qualcomm Technologies, Inc.  All Rights Reserved 
//============================================================================

//============================================================================
//
//                       EDIT HISTORY FOR MODULE
//
//
// This section contains comments describing changes made to the module.
// Notice that changes are listed in reverse chronological order.
//
//
// when      who     what, where, why
// --------  -----   ----------------------------------------------------------
// 11/29/16  aus     Added support for 32 bit LLVM compilation
//
//============================================================================

.text
.align 2

//============================================================================
//                             MODULE EXPORTS
//============================================================================

  GCC_ASM_EXPORT(fastcall)
  GCC_ASM_EXPORT(newsmccall)

//============================================================================
//
//                        MACROS AND FUNCTIONS
//
//============================================================================

#define smc_call(func)                \
smc_loop_##func:                  ;   \
    smc           #0x0            ;   \
    cmp           r0, #0          ;   \
    bgt           smc_loop_##func


//============================================================================
//
//  UINT32 fastcall (UINT32 id, UINT32 token, UINT32 r0, UINT32 r1, ...)//
//      r0  - id, TZ SYSCALL id, lowest nibble contains the number of arguments.
//      r1  - token, SMP token.
//      r2  - First argument to TZ syscall (R0, optional).
//      r3  - Second argument to TZ syscall (R1, optional).
//      r4  - Third argument to TZ syscall.
//      r5  - Fourth argument to TZ syscall.
//      r6  - Fifth argument to TZ syscall.
//      r7  - Sixth argument to TZ syscall.
//
//============================================================================

fastcall:
    push    {lr}
    orr     r0, r0, #(2 << 8)   // val 2 in bits 8-11 means fastcall
    and     lr, r0, #0xff       // last nibble is the arg count

    cmp     lr, #2      // if (args <= 2)
    bgt     three
    smc_call(three)
    pop     {pc}
three:
    cmp     lr, #3      // if (args == 3)
    bne     four
    push    {r4}
    add     lr, sp, #8
    ldmia   lr, {r4}
    smc_call(four)
    pop     {r4, pc}
four:
    cmp     lr, #4      // if (args == 4)
    bne     five
    push    {r4-r5}
    add     lr, sp, #12
    ldmia   lr, {r4-r5}
    smc_call(five)
    pop     {r4-r5, pc}
five:
    cmp     lr, #5      // if (args == 5)
    bne     six
    push    {r4-r6}
    add     lr, sp, #16
    ldmia   lr, {r4-r6}
    smc_call(six)
    pop     {r4-r6, pc}
six:
    cmp     lr, #6      // if (args == 6)
    bne     seven
    push    {r4-r7}
    add     lr, sp, #20
    ldmia   lr, {r4-r7}
    smc_call(seven)
    pop     {r4-r7, pc}
seven:
    cmp     lr, #7      // if (args == 7)
    bne     eight
    push    {r4-r8}
    add     lr, sp, #24
    ldmia   lr, {r4-r8}
    smc_call(eight)
    pop     {r4-r8, pc}
eight:
    cmp     lr, #8      // if (args == 8)
    bne     nine
    push    {r4-r9}
    add     lr, sp, #28
    ldmia   lr, {r4-r9}
    smc_call(nine)
    pop     {r4-r9, pc}
nine:
    cmp     lr, #9      // if (args == 9)
    bne     ten
    push    {r4-r10}
    add     lr, sp, #32
    ldmia   lr, {r4-r10}
    smc_call(ten)
    pop     {r4-r10, pc}
ten:
    cmp     lr, #10     // if (args == 10)
    bne     eleven
    push    {r4-r11}
    add     lr, sp, #36
    ldmia   lr, {r4-r11}
    smc_call(eleven)
    pop     {r4-r11, pc}
eleven:
    mvn     r0, #0      // Too many args
    pop     {pc}
    
//============================================================================
//
//  int newsmccall(uint32 smc_id, uint32 param_id, uint32 parameters[4], uint32 *trusted_os_id)//
//      r0  - SmcId: Owner, IRQ, Architecture, Command ID
//      r1  - ParamId, lowest nibble contains the number of arguments.
//      r2  - First argument to TZ syscall.
//      r3  - Second argument to TZ syscall.
//      r4  - Third argument to TZ syscall.
//      r5  - Fourth argument to TZ syscall or Indirect Parameter List
//      r6  - Trusted OS ID.
//
//============================================================================
newsmccall:
    push    {r10,r9,lr}
    and     lr, r1, 0xf  // last bit determines number of args
    cmp     lr, #10
    bgt     twelve

    push    {r4-r6}
    mov     lr, r2
    mov     r10, r2
    mov     r9, r3
    ldmia   lr, {r2-r5}
    smc_call(twelve)
    stmia   r10, {r1-r3}
    str     r6, [r9]
    pop     {r4-r6}
    b       thirteen

twelve:
    mvn     r0, #0      // Too many args
    b       thirteen

thirteen:
    pop     {r10,r9,pc}

