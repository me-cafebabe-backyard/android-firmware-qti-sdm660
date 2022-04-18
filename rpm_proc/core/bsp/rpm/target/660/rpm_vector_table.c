/*=============================================================================

                               rpm_vector_table.c

GENERAL DESCRIPTION
  This file defines the RPM vector table.

EXTERNALIZED FUNCTIONS

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None

Copyright (c) 2015 by Qualcomm Technologies, Inc.  All Rights Reserved.

  $Header: //components/rel/rpm.bf/1.8/core/bsp/rpm/target/660/rpm_vector_table.c#2 $
  $Author: pwbldsvc $
  $DateTime: 2017/03/15 09:06:36 $
=============================================================================*/
#include "rpm_vector_table.h"

extern __asm void abort_isr(void) __irq;
extern __asm void tz_abort_isr(void) __irq;
extern void dcc_crc_error_abort_isr(void) __irq;
extern void apps_non_secure_wd_bite_abort_isr(void) __irq;
extern void xport_rpm_isr(void) __irq;
extern void dog_bark_isr(void) __irq;
extern __weak void vmpm_isr(void) __irq;
extern __weak void settling_timer_isr(void) __irq;
extern void __main(void);


//This needs to be aligned to at least 0x200 bytes (see arm documentation for why).
#ifdef __clang__
ExecFuncPtr vector_table[NUM_EXCEPTIONS+NUM_INTERRUPTS] __attribute__((at(0x090800))) =
#else
ExecFuncPtr vector_table[NUM_EXCEPTIONS+NUM_INTERRUPTS] =
#endif
{
  // RPM's standard system-level Cortex-M3 exceptions come first.
  (ExecFuncPtr)0,       // Initial stack pointer - not used
  (ExecFuncPtr)__main,  // Image entry point
  abort_isr,            // NMI
  abort_isr,            // Hard fault
  abort_isr,            // Memory management
  abort_isr,            // Bus fault
  abort_isr,            // Usage fault
  0, 0, 0, 0,           // Reserved
  abort_isr,            // SVC
  abort_isr,            // Debug Monitor
  0,                    // Reserved
  abort_isr,            // PendSVC
  abort_isr,            // SysTick

  // RPM's NVIC interrupts start here.
  abort_isr,                         //  0 - HYP SMD interrupt
  abort_isr,                         //  1 - HYP VMPM interrupt
  abort_isr,                         //  2 - HYP reserved interrupt
  abort_isr,                         //  3 - Hydra L3 shutdown_req
  dcc_crc_error_abort_isr,           //  4 - dcc_crc_fail_int
  vmpm_isr,                          //  5 - MPSS VMPM interrupt
  abort_isr,                         //  6 - Monaco bringup_req
  apps_non_secure_wd_bite_abort_isr, //  7 - APPS sysWdogBiteInt
  xport_rpm_isr,                     //  8 - APPS HLOS SMD interrupt
  vmpm_isr,                          //  9 - APPS HLOS VMPM interrupt
  abort_isr,                         // 10 - APPS HLOS reserved interrupt
  xport_rpm_isr,                     // 11 - TZ SMD interrupt
  tz_abort_isr,                      // 12 - TZ HALT interrupt
  abort_isr,                         // 13 - TZ reserved interrupt
  abort_isr,                         // 14 - Monaco shutdown_req
  abort_isr,                         // 15 - dcc_task_done_int
  abort_isr,                         // 16 - APCS_dbgCorePwrUpInt
  abort_isr,                         // 17 - cpr_irq[0] (MX domain)
  abort_isr,                         // 18 - LPASS shutdown_req
  abort_isr,                         // 19 - LPASS bringup_req
  xport_rpm_isr,                     // 20 - LPASS SMD interrupt
  vmpm_isr,                          // 21 - LPASS VMPM interrupt
  abort_isr,                         // 22 - LPASS reserved interrupt
  abort_isr,                         // 23 - cpr_irq[1] (MX domain)
  abort_isr,                         // 24 - Hydra L2 bringup_req
  abort_isr,                         // 25 - Hydra L2 shutdown_req
  abort_isr,                         // 26 - Hydra L2 bringup_req
  abort_isr,                         // 27 - Hydra L2 shutdown_req
  abort_isr,                         // 28 - Hydra L3 bringup_req
  abort_isr,                         // 29 - bimc_intr[2]
  abort_isr,                         // 30 - Not used
  abort_isr,                         // 31 - Not used
  abort_isr,                         // 32 - Not used
  abort_isr,                         // 33 - MPSS bringup_req
  abort_isr,                         // 34 - vense_rpm_alarm_irq
  abort_isr,                         // 35 - o_tcsr_qdss_summary_intr
  xport_rpm_isr,                     // 36 - CDSP GLINK interrupt
  vmpm_isr,                         // 37 - CDSP VMPM interrupt
  abort_isr,                         // 38 - bimc_intr[3]
  abort_isr,                         // 39 - tlmm summary_irq
  abort_isr,                         // 40 - tlmm dir_conn_irq
  abort_isr,                         // 41 - MPM tsens1_upper_lower_int
  abort_isr,                         // 42 - MPM summary interrupt
  abort_isr,                         // 43 - MPSS shutdown_req
  abort_isr,                         // 44 - Not used
  abort_isr,                         // 45 - cpr_irq[2] (MX domain)
  xport_rpm_isr,                     // 46 - MPSS SMD interrupt
  abort_isr,                         // 47 - cpr_irq[1] ( cpr3_wrapper_cx)
  abort_isr,                         // 48 - PMIC spmi_periph_irq[4]
  dog_bark_isr,                      // 49 - WDOG bark IRQ
  abort_isr,                         // 50 - QTimer[0] IRQ
  settling_timer_isr,                // 51 - QTimer[1] IRQ
  abort_isr,                         // 52 - Not used
  abort_isr,                         // 53 - Not used
  abort_isr,                         // 54 - cpr_irq[0] (CX domain)
  abort_isr,                         // 55 - cpr_irq[3] (MX domain)
  abort_isr,                         // 56 - LPASS bringup_req
  abort_isr,                         // 57 - LPASS shutdown_req
  abort_isr,                         // 58 - MPSS reserved interrupt
  abort_isr,                         // 59 - bus_timeout_irq
  abort_isr,                         // 60 - SPSS reserved interrupt
  abort_isr,                         // 61 - MPM tsens0_upper_lower_int
  abort_isr,                         // 62 - MPM tsens1_tsens_critical_int
  abort_isr,                         // 63 - MPM tsens0_tsens_critical_int
};
