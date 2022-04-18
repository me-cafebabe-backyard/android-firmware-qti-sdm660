
#include "coredump.h"
#include "HALhwio.h"
#include "rpm_hwio.h"

#include "rpm_ulog.h"
#include "swevent.h"

#include "hw_version.h"
#include "Chipinfo.h"
#include "gcc_reset_hwio.h"
#include "mpm2_pshold_hwio.h"

#define APPS_NON_SEC_WD_IRQ     7

//To Avoid recursive call of SWevent when Qtimer becomes zero
uint32 rpm_in_core_dump_ctx;

extern RPM_LOG_CONTEXT rpm_ulogContext;

__attribute__((section("rpm_core_dump")))
m3_core_dump_t rpm_core_dump =
{
    .cookie = 0xbaff1ed,
    .chip_reset_en = 0,
    .ulog_state = &rpm_ulogContext,
};

void notify_apss(void)
{
    HWIO_OUT(RPM_IPC, (1 << 6) | (1 << 22));
}

void err_fatal_sw_event(unsigned lr, unsigned ipsr)
{
	rpm_in_core_dump_ctx = 1;
    uint32 gcc_reset = 0;	
    SWEVENT(RPM_ERR_FATAL, lr, ipsr);
    gcc_reset = HWIO_IN(GCC_RESET_STATUS);
    if(gcc_reset != 0)
    {
      SWEVENT(GCC_RESET, gcc_reset);
    }
}

void reset_chip(void)
{
    if(rpm_core_dump.chip_reset_en)
    {
        SWEVENT(RPM_RESET_CHIP);

        HWIO_OUT(MPM2_MPM_PS_HOLD, 0);
    }
}

void rpm_core_dump_init(void)
{
    rpm_core_dump.hw_version.v = HWIO_IN(TCSR_SOC_HW_VERSION);

    interrupt_configure(APPS_NON_SEC_WD_IRQ, LEVEL_HIGH);
}

#ifndef __clang__
__asm void abort(void)
{
  IMPORT rpm_core_dump
  IMPORT notify_apss
  IMPORT err_fatal_sw_event
  IMPORT reset_chip
  IMPORT rbcpr_core_dump
#ifdef DDR_ABORT_REG_DUMP
  IMPORT ddr_store_status_regs_error_fatal
#endif

  ; Disable all interrupts except NMI
  cpsid f
      
  ; We are going to use r0-r3 as scratch registers for a while, so save them first.
  push  {r0-r3}

  ; Get the address of the core dump structure.
  ldr   r0, =rpm_core_dump

  ; If we have already dumped registers on this run, stop here.
  ldr   r1, [r0, #4] ; rpm_core_dump.dumped_at first chunk
  cbnz  r1, hang     ; if nonzero, previous dump performed
  ldr   r1, [r0, #8] ; rpm_core_dump.dumped_at second chunk
  cbnz  r1, hang     ; if nonzero, previous dump performed

  ; Read the timetick and store it
  ldr   r1, =timer_addr
  ldr   r1, [r1]     ; r1 now points to "lo" word of timetick
retry
  ldr   r3, [r1, #4] ; read "hi" word
  ldr   r2, [r1]     ; read "lo" word
  str   r2, [r0, #4] ; save "lo" word
  ldr   r2, [r1, #4] ; read "hi" word again
  cmp   r2, r3       ; if "hi" word rolled over while we dumped
  bne   retry        ;   we must retry
  str   r2, [r0, #8] ; save "hi" word

  ; Store r4-r12
  add   r0, r0, #28 ; skip cookie, dump timestamp, and r0-r3
  stmia r0!, {r4-r12}

  ; Go back and get r0-r3
  pop   {r2-r5}
  ldr   r1, =rpm_core_dump  ; get a fresh pointer to the core dump [r0 is just past registers, we need that later]
  add   r1, r1, #12         ; move past cookie and timestamp to where r0-r3 should be stored
  stm   r1!, {r2-r5}

  ; Grab the remaining registers.
  mrs   r1, MSP
  mrs   r2, PSP
  mov   r3, lr
  ldr   r4, =abort
  mrs   r5, XPSR
  mrs   r6, PRIMASK
  mrs   r7, FAULTMASK
  mrs   r8, BASEPRI
  mrs   r9, CONTROL
  stmia r0!, {r1-r9}

  ; Grab and save all the auxiliary fault status registers
  ldr   r1, =0xE000ED24
  ldmia r1!, {r2-r8}
  stmia r0!, {r2-r8}
  
  ; Add something useful to the log
  mov   r0, lr
  mrs   r1, IPSR
  push  {r0, lr}            ; push lr so we can pop later and preserve the stack for the debugger. Need to push 8 bytes
  bl    err_fatal_sw_event
  bl    rbcpr_core_dump

#ifdef DDR_ABORT_REG_DUMP
  bl    ddr_store_status_regs_error_fatal
#endif

  bl    notify_apss
  
  bl    reset_chip

  ; Do this last
  pop   {r0, lr}

hang
  b     hang

  ALIGN 4
timer_addr
  dcd   HWIO_RPM_F0_QTMR_V1_CNTPCT_LO_ADDR 
}

#else
__attribute__((naked)) void abort(void)
{
  asm("cpsid f");
  asm("push  {r0-r3}");
  asm("ldr   r0, =rpm_core_dump");
  asm("ldr   r1, [r0, #4]");
  asm("cbnz  r1, hang");
  asm("ldr   r1, [r0, #8]");
  asm("cbnz  r1, hang");

  asm("ldr   r1, =timer_addr");
  asm("ldr   r1, [r1]");
  asm("retry:");
  asm("ldr   r3, [r1, #4]");
  asm("ldr   r2, [r1]");
  asm("str   r2, [r0, #4]");
  asm("ldr   r2, [r1, #4]");
  asm("cmp   r2, r3");
  asm("bne   retry");
  asm("str   r2, [r0, #8]");

  asm("add   r0, r0, #28");
  asm("stmia r0!, {r4-r12}");

  asm("pop   {r2-r5}");
  asm("ldr   r1, =rpm_core_dump");
  asm("add   r1, r1, #12");
  asm("stm   r1!, {r2-r5}");

  asm("mrs   r1, MSP");
  asm("mrs   r2, PSP");
  asm("mov   r3, lr");
  asm("ldr   r4, =abort");
  asm("mrs   r5, XPSR");
  asm("mrs   r6, PRIMASK");
  asm("mrs   r7, FAULTMASK");
  asm("mrs   r8, BASEPRI");
  asm("mrs   r9, CONTROL");
  asm("stmia r0!, {r1-r9}");

  asm("ldr   r1, =0xE000ED24");
  asm("ldmia r1!, {r2-r8}");
  asm("stmia r0!, {r2-r8}");

  asm("mov   r0, lr");
  asm("mrs   r1, IPSR");
  asm("push  {r0, lr}");
  asm("bl    err_fatal_sw_event");
  asm("bl    rbcpr_core_dump");

#ifdef DDR_ABORT_REG_DUMP
  asm("bl    ddr_store_status_regs_error_fatal");
#endif
  
  asm("bl    notify_apss");
  asm("bl    reset_chip");
  asm("pop   {r0, lr}");

  asm("hang:");
  asm("b     hang");

  asm(".p2align 4");
  asm("timer_addr:");
  asm(".word 0x00080000 + 0x00003000 " );
// Note: Here we replace HWIO_RPM_F0_QTMR_V1_CNTPCT_LO_ADDR with its value
// (0x83000) obtained after the preprocess phase.
}
#endif
