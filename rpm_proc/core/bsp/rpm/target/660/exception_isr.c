#include "HALhwio.h"
#include "coredump.h"
#include "swevent.h"
#include "apcs_hang_status_hwio.h"

#ifdef RPM_BASE
#undef RPM_BASE
#endif

#define RPM_BASE    0x60000000

#define GLADIATOR_HANG_STATUS_MASK  (HWIO_APCS_COMMON_GLADIATOR_HANG_CONFIG_PCIO_COUNTER_STS_BMSK |\
                                     HWIO_APCS_COMMON_GLADIATOR_HANG_CONFIG_M2_COUNTER_STS_BMSK   |\
                                     HWIO_APCS_COMMON_GLADIATOR_HANG_CONFIG_M1_COUNTER_STS_BMSK   |\
                                     HWIO_APCS_COMMON_GLADIATOR_HANG_CONFIG_IO_COUNTER_STS_BMSK   |\
                                     HWIO_APCS_COMMON_GLADIATOR_HANG_CONFIG_ACE_COUNTER_STS_BMSK )

#define GIC_ERR_STATUS_MASK  (HWIO_APCS_COMMON_GIC_ERR_IPC_ECC_FATAL_BMSK |\
                              HWIO_APCS_COMMON_GIC_ERR_IPC_AXIM_ERROR_BMSK)

#define APSS_ACS_SIZE               (APCS_ALIAS1_APSS_ACS_REG_BASE - APCS_ALIAS0_APSS_ACS_REG_BASE)


static struct
{
    uint32 APCS_COMMON_FIRST_CORE_HANG;         /* CPU Core hang status */
    uint32 APCS_COMMON_GLADIATOR_HANG_CONFIG;   /* Gladiator hang status */
    uint32 APCS_COMMON_GIC_ERR_IPC;             /* GIC error status */
    uint32 APCS_WDT_TMR1_WDOG_STATUS;           /* APPS non-sec wd status */
} apps_hang_status_regs;


void tz_abort_sw_event(void)
{
    SWEVENT(RPM_TZ_HALT_INT_RECEIVED);
}

__asm void abort_isr(void) __irq
{
	#ifdef __clang__
		__asm__("b abort\n");
	#else
    IMPORT abort
    b abort             // Use b to not overwrite EXEC_RETURN value to make rpm_parse_faults.cmm work
	#endif
}

#ifdef __clang__
__asm void tz_abort_isr(void) __irq {
  __asm__("sub sp, sp, #0x8 //  Eight byte stack alignment is a requirement of AAPCS\n"
           "str lr, [sp] //  Save EXEC_RETURN value \n"
           "bl tz_abort_sw_event\n"
           "ldr lr, [sp] // Restore EXEC_RETURN value\n"
           "add sp, sp, #0x8\n"
           "b abort // Use b to not overwrite EXEC_RETURN value to make rpm_parse_faults.cmm work\n"
      );
}
#else
__asm void tz_abort_isr(void) __irq
{
    IMPORT tz_abort_sw_event
    IMPORT abort

    sub sp, sp, #0x8    // Eight byte stack alignment is a requirement of AAPCS
    str lr, [sp]        // Save EXEC_RETURN value

    bl tz_abort_sw_event

    ldr lr, [sp]        // Restore EXEC_RETURN value
    add sp, sp, #0x8

    b abort             // Use b to not overwrite EXEC_RETURN value to make rpm_parse_faults.cmm work
}
#endif

void dcc_crc_error_abort_isr(void) __irq
{
    SWEVENT(RPM_DCC_CRC_ERR_INT_RECEIVED);
    abort();
}

void detect_apps_hang(void)
{
    /*
     * Log RPM received the interrupt before reading the APPS regsiters
     * in case CPUSS AHB register access path hang and RPM is not able to read the registers 
     */
    SWEVENT(RPM_NON_SECURE_WD_BITE_INT_RECEIVED);

    /*
     * Set chip reset flag before reading status registers because
     * if bus fault happens while reading registers, RPM jumps to abort_isr().
     * Assume bus fault means APPS hanged and need to reset chip.
     */
    rpm_core_dump.chip_reset_en = 1;

    /*
     * Read the hang status registers.
     */
    apps_hang_status_regs.APCS_COMMON_FIRST_CORE_HANG       = HWIO_IN(APCS_COMMON_FIRST_CORE_HANG);
    apps_hang_status_regs.APCS_COMMON_GLADIATOR_HANG_CONFIG = HWIO_IN(APCS_COMMON_GLADIATOR_HANG_CONFIG);
    apps_hang_status_regs.APCS_COMMON_GIC_ERR_IPC           = HWIO_IN(APCS_COMMON_GIC_ERR_IPC);
    apps_hang_status_regs.APCS_WDT_TMR1_WDOG_STATUS         = HWIO_IN(APCS_WDT_TMR1_WDOG_STATUS);

    SWEVENT(RPM_APPS_HANG_STATUS,
            apps_hang_status_regs.APCS_COMMON_FIRST_CORE_HANG,
            apps_hang_status_regs.APCS_COMMON_GLADIATOR_HANG_CONFIG,
            apps_hang_status_regs.APCS_COMMON_GIC_ERR_IPC,
            apps_hang_status_regs.APCS_WDT_TMR1_WDOG_STATUS);

    /*
     * CR 901848 & 901842:
     * Pull PS_HOLD low for the following conditions:
     * - Core hang
     * - Gladiator hang
     * - GIC erros (axim_err or ecc_fatal)
     */
    if( (apps_hang_status_regs.APCS_COMMON_FIRST_CORE_HANG != 0) ||
        ((apps_hang_status_regs.APCS_COMMON_GLADIATOR_HANG_CONFIG & GLADIATOR_HANG_STATUS_MASK) != 0) ||
        ((apps_hang_status_regs.APCS_COMMON_GIC_ERR_IPC & GIC_ERR_STATUS_MASK) != 0) )
    {
        uint32 i;

        /*
         * APPS hang detected. Log optional hang status registers to help debugging
         */

        // Log Core hang threshold, Core hang value, and Core hang config registers for Core 0 - 7
        for(i = 0; i < 8; i++)
        {
            uint32 addr;
            uint32 j;

            if(i < 4)
            {
                addr = HWIO_ADDR(APCS_ALIAS0_CORE_HANG_THRESHOLD) + i * APSS_ACS_SIZE;
            }
            else
            {
                addr = HWIO_ADDR(APCS_ALIAS4_CORE_HANG_THRESHOLD) + (i-4) * APSS_ACS_SIZE;
            }

            for(j = 0; j < 3; j++)
            {
                addr += (j * sizeof(uint32));

                SWEVENT(RPM_LOG_REGISTER, addr - RPM_BASE, in_dword(addr));
            }
        }

        // Log Gladiator hang thresholds
        for(i = 0; i <= HWIO_APCS_COMMON_THRESHOLD_n_MAXn; i++)
        {
            uint32 addr = HWIO_ADDRI(APCS_COMMON_THRESHOLD_n, i);
            uint32 val  = HWIO_INI(APCS_COMMON_THRESHOLD_n, i);

            SWEVENT(RPM_LOG_REGISTER, addr - RPM_BASE, val);
        }

        // Log Gladiator hang counters
        for(i = 0; i <= HWIO_APCS_COMMON_GLADIATOR_HANG_COUNTER_n_MAXn; i++)
        {
            uint32 addr = HWIO_ADDRI(APCS_COMMON_GLADIATOR_HANG_COUNTER_n, i);
            uint32 val  = HWIO_INI(APCS_COMMON_GLADIATOR_HANG_COUNTER_n, i);

            SWEVENT(RPM_LOG_REGISTER, addr - RPM_BASE, val);
        }
    }
    else
    {
        /*
         * It's non-secure wdog bite, not hang. No need to reset chip.
         */
        rpm_core_dump.chip_reset_en = 0;
    }
}

#ifndef __clang__
__asm void apps_non_secure_wd_bite_abort_isr(void) __irq
{
    IMPORT detect_apps_hang
    IMPORT abort

    sub sp, sp, #0x8    // Eight byte stack alignment is a requirement of AAPCS
    str lr, [sp]        // Save EXEC_RETURN value

    bl detect_apps_hang

    ldr lr, [sp]        // Restore EXEC_RETURN value
    add sp, sp, #0x8

    b abort             // Use b to not overwrite EXEC_RETURN value to make rpm_parse_faults.cmm work
}
#else
__asm void apps_non_secure_wd_bite_abort_isr(void) __irq
{
	 __asm__(	"sub sp, sp, #0x8    // Eight byte stack alignment is a requirement of AAPCS\n"
				"str lr, [sp]        // Save EXEC_RETURN value\n"
				"bl detect_apps_hang\n"
				"ldr lr, [sp]        // Restore EXEC_RETURN value\n"
				"add sp, sp, #0x8\n"
				"b abort             // Use b to not overwrite EXEC_RETURN value to make rpm_parse_faults.cmm work\n" );
}
#endif
