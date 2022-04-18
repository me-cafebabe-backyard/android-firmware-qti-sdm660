;=========================================================================
;
;*//** @file startup.s
;  This file contains the implementation for HoneyBadger RPM to boot
;
;@par EXTERNALIZED FUNCTIONS
;  (none)
;
;@par INITIALIZATION AND SEQUENCING REQUIREMENTS
;  (none)
;
;Copyright (C) 2014 QUALCOMM Technologies Incorporated.
;All Rights Reserved. QUALCOMM Proprietary and Confidential.
;
;*//*=====================================================================

;=========================================================================
;                             Edit History
;$Header: //components/rel/rpm.bf/1.8/core/bsp/rpm/src/startup.s#2 $
;$Date: 2017/03/15 $
;
; when       who       what, where, why
; --------   ---       ---------------------------------------------------
;
;=========================================================================
#ifndef __clang__

                IMPORT  ||Image$$CODE_RAM_SAVE$$Base||

;-------------------------------------------------------------------------
;                           DATA
;-------------------------------------------------------------------------

                AREA    RPM_ENTRY, DATA, READONLY
__Vectors                               ; Minimal Vector Table entries at 0x0 for boot
                DCD     ||Image$$CODE_RAM_SAVE$$Base||
                                        ; Initial Main SP
                DCD     Reset_Handler   ; Reset Handler
               ;DCD     NMI_Handler       ?
               ;DCD     HardFault_Handler ?

;-------------------------------------------------------------------------
;                           FUNCTION DEFINITIONS
;-------------------------------------------------------------------------

                AREA    |.text|, CODE, READONLY
Reset_Handler
                IMPORT  __main
                LDR     R0, =__main
                BX      R0

                END

#else
                .extern  Image$$CODE_RAM_SAVE$$Base

; Vector Table Mapped to Address 0 at Reset

                .section .text, "a", %progbits
.p2align 2
__Vectors:
.word (Image$$CODE_RAM_SAVE$$Base)
.word Reset_Handler             ; Reset Handler


                .section .text, "ax", %progbits
.global Reset_Handler
.type Reset_Handler, %function

.code 16
; Reset Handler

Reset_Handler:
                ;.global  Reset_Handler
                .extern  __main
                LDR     R0, =__main
                BX      R0

                .end
#endif
