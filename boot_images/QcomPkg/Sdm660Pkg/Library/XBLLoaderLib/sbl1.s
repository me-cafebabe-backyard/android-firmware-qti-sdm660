;*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*
;
;                              SBL1
;
; GENERAL DESCRIPTION
;   This file bootstraps the processor. The Start-up Primary Bootloader
;   (SBL1) performs the following functions:
;
;      - Set up the hardware to continue boot process.
;      - Initialize DDR memory
;      - Load Trust-Zone OS
;      - Load RPM firmware
;      - Load APPSBL and continue boot process
;
;   The SBL1 is written to perform the above functions with optimal speed.
;   It also attempts to minimize the execution time and hence reduce boot time.
;
; Copyright 2014 by Qualcomm Technologies, Incorporated.All Rights Reserved.
;*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

;*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*
;
;                           EDIT HISTORY FOR FILE
;
; This section contains comments describing changes made to the module.
; Notice that changes are listed in reverse chronological order.
;
; $Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/XBLLoaderLib/sbl1.s#1 $
;
; when       who     what, where, why
; --------   ---     --------------------------------------------------------
; 05/14/14   kedara  Export sbl1_entry api for 8996 XBL Loader.
; 03/19/14   ck      Fixed stack base issue.  Now using proper address which is "Limit" of SBL1_STACK 
; 03/07/14   ck      Removed -4 logic from check_for_nesting as bear SBL has its own vector table
; 03/03/14   ck      Updated vector table with branches as VBAR is being used in Bear family 
; 11/15/12   dh      Add boot_read_l2esr for 8974
; 08/31/12   dh      Correct the stack base in check_for_nesting, remove unused code
; 07/16/12   dh      Remove watchdog reset code
; 02/06/12   dh      Update start up code
; 01/31/12   dh      Initial revision for 8974
;*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*


;============================================================================
;
;                            MODULE INCLUDES
;
;============================================================================
#include "boot_msm.h"
#include "boot_target.h"

;============================================================================
;
;                             MODULE DEFINES
;
;============================================================================
;
Mode_SVC                EQU    0x13
Mode_ABT                EQU    0x17
Mode_UND                EQU    0x1b
Mode_USR                EQU    0x10
Mode_FIQ                EQU    0x11
Mode_IRQ                EQU    0x12
Mode_SYS                EQU    0x1F

I_Bit                   EQU    0x80
F_Bit                   EQU    0x40


;============================================================================
;
;                             MODULE IMPORTS
;
;============================================================================

    ; Import the external symbols that are referenced in this module.
    IMPORT |Image$$SBL1_STACK$$ZI$$Limit|
    IMPORT boot_undefined_instruction_c_handler
    IMPORT boot_swi_c_handler
    IMPORT boot_prefetch_abort_c_handler
    IMPORT boot_data_abort_c_handler
    IMPORT boot_reserved_c_handler
    IMPORT boot_irq_c_handler
    IMPORT boot_fiq_c_handler
    IMPORT boot_nested_exception_c_handler
    IMPORT sbl1_main_ctl


;============================================================================
;
;                             MODULE EXPORTS
;
;============================================================================

    ; Export the external symbols that are referenced in this module.
    EXPORT sbl_loop_here
    EXPORT boot_read_l2esr
   
    ; Export the symbols __main and _main to prevent the linker from
    ; including the standard runtime library and startup routine.
    EXPORT   __main
    EXPORT   _main
    EXPORT   sbl1_entry
;============================================================================
;
;                             MODULE DATA AREA
;
;============================================================================


    PRESERVE8
    AREA    SBL1_VECTORS, CODE, READONLY, ALIGN=4
    CODE32
unused_reset_vector
    B     0x00000000
undefined_instruction_vector
    B     sbl1_undefined_instruction_nested_handler
swi_vector
    B     boot_swi_c_handler
prefetch_abort_vector
    B     sbl1_prefetch_abort_nested_handler
data_abort_vector
    B     sbl1_data_abort_nested_handler
reserved_vector
    B     boot_reserved_c_handler
irq_vector
    B     boot_irq_c_handler
fiq_vector
    B     boot_fiq_c_handler


;============================================================================
; Qualcomm SECONDARY BOOT LOADER 1 ENTRY POINT
;============================================================================

    AREA  SBL1_ENTRY, CODE, READONLY, ALIGN=4
    CODE32
    ENTRY
    
__main
_main

;============================================================================
;   We contiue to disable interrupt and watch dog until we jump to SBL3
;============================================================================
sbl1_entry

    ;Change to Supervisor Mode
    msr     CPSR_c, #Mode_SVC:OR:I_Bit:OR:F_Bit

    ; Save the passing parameter from PBL
    mov     r7, r0

    ; Set VBAR (Vector Base Address Register) to SBL vector table
    ldr     r0, =SCL_SBL1_VECTOR_BASE
    MCR     p15, 0, r0, c12, c0, 0
	
    ; Setup the supervisor mode stack
    ldr     r0, =|Image$$SBL1_STACK$$ZI$$Limit|
    mov     r13, r0

    ; Switch to undefined mode and setup the undefined mode stack
    msr     CPSR_c, #Mode_UND:OR:I_Bit:OR:F_Bit
    mov     r13, r0

    ; Switch to abort mode and setup the abort mode stack
    msr     CPSR_c, #Mode_ABT:OR:I_Bit:OR:F_Bit
    mov     r13, r0

    ; Return to supervisor mode
    msr     CPSR_c, #Mode_SVC:OR:I_Bit:OR:F_Bit

    ; Restore the passing parameter
    mov     r0, r7
    
    ; ------------------------------------------------------------------
    ; Call functions external to perform SBL1 function.
    ; It should never return.
    ; ------------------------------------------------------------------
    ldr    r5, =sbl1_main_ctl
    blx    r5

    ; For safety
    bl loophere  ; never returns, keep lr in r14 for debug



;======================================================================
; Called by sbl1_error_handler only. We clean up the registers and loop
; here until JTAG is connected.
;======================================================================
sbl_loop_here
    mov r0,#0
    mov r1,#0
    mov r2,#0
    mov r3,#0
    mov r4,#0
    mov r5,#0
    mov r6,#0
    mov r7,#0
    mov r8,#0
    mov r9,#0
    mov r10,#0
    mov r11,#0
    mov r12,#0
loophere
    b loophere


;======================================================================
; SBL1 exception handlers that can have nested calls to them.  These
; handlers check for nesting and if it is the first exception they
; call a "C" exception handler that calls the SBL1 error handler.
; If it is a nested exception, the "C" exception handler is not
; re-entered and the JTAG interface is enabled immediately. Nesting
; is only a concern for undefined instruction and abort exceptions.
; Note, a separate exception handler is used for each exception to
; provide additional debug information (see sbl1_error_handler.c for
; more information).
;======================================================================
sbl1_undefined_instruction_nested_handler
    ldr r5,=boot_undefined_instruction_c_handler
    b   check_for_nesting

sbl1_prefetch_abort_nested_handler
    ldr r5,=boot_prefetch_abort_c_handler
    b   check_for_nesting

sbl1_data_abort_nested_handler
    ldr r5,=boot_data_abort_c_handler
    b   check_for_nesting

;======================================================================
; Checks for nested exceptions and then calls the "C" exception
; handler pointed to by R5 if this is the first time this exception
; has occurred, otherwise it calls the "C" nested exception handler
; that just enables JTAG debug access.  The mode stack pointer is used
; to determine if a nested exception or a second abort exception has
; occurred.  This is accomplished by comparing the mode stack pointer
; to the top of the stack that was initially assigned to the stack.
; If they are equal, it is a first time exception.
;======================================================================
check_for_nesting

    ;Initial stack base will be Image$$SBL1_STACK$$ZI$$Limit
    ldr r6,=|Image$$SBL1_STACK$$ZI$$Limit|
    mov r7, r13                            ; Save current stack ptr
    cmp r6, r7                             ; Compare initial and actual
    blxeq r5                               ; First time exception
    ldr r5,=boot_nested_exception_c_handler; This is a nested exception
    blx r5

boot_read_l2esr
    mov r1, #0x204    ;Indirect address of L2ESR
    isb
    mcr p15,3,r1,c15,c0,6 ;Write the L2CPUCPSELR with the indirect address of the L2ESR
    isb
    mrc p15,3,r0,c15,c0,7 ;store L2ESR to r0
    isb
    bx lr
    
    END
