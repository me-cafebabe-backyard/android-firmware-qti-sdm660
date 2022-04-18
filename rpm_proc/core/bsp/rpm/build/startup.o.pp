# 1 "/local/mnt/workspace/CRMBuilds/RPM.BF.1.8-00067-SDM660AAAAANAZR-1_20200203_034924/b/rpm_proc/core/bsp/rpm/src/startup.s"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 324 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "/local/mnt/workspace/CRMBuilds/RPM.BF.1.8-00067-SDM660AAAAANAZR-1_20200203_034924/b/rpm_proc/core/bsp/rpm/src/startup.s" 2
;=========================================================================
;
;*
; This file contains the implementation for HoneyBadger RPM to boot
;
;@par EXTERNALIZED FUNCTIONS
; (none)
;
;@par INITIALIZATION AND SEQUENCING REQUIREMENTS
; (none)
;
;Copyright (C) 2014 QUALCOMM Technologies Incorporated.
;All Rights Reserved. QUALCOMM Proprietary and Confidential.
;
;*

;=========================================================================
; Edit History
;$Header:
;$Date: 2017/03/15 $
;
; when who what, where, why
; -------- --- ---------------------------------------------------
;
;=========================================================================
# 55 "/local/mnt/workspace/CRMBuilds/RPM.BF.1.8-00067-SDM660AAAAANAZR-1_20200203_034924/b/rpm_proc/core/bsp/rpm/src/startup.s"
                .extern Image$$CODE_RAM_SAVE$$Base

; Vector Table Mapped to Address 0 at Reset

                .section .text, "a", %progbits
.p2align 2
__Vectors:
.word (Image$$CODE_RAM_SAVE$$Base)
.word Reset_Handler ; Reset Handler


                .section .text, "ax", %progbits
.global Reset_Handler
.type Reset_Handler, %function

.code 16
; Reset Handler

Reset_Handler:
                ;.global Reset_Handler
                .extern __main
                LDR R0, =__main
                BX R0

                .end
