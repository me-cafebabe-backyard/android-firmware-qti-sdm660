#include "HALhwio.h"
#include "rpm_hwio.h"
#include "vmpm_target.h"
#include "HALmpm.h"


/* functions to send interrupts to the various masters */
void send_cdsp_vmpm_interrupt(void)
{
  HWIO_OUT(RPM_IPC, (1<<1));
}

void send_apss_vmpm_interrupt(void)
{
  HWIO_OUT(RPM_IPC, (1<<5));
}

void send_lpass_vmpm_interrupt(void)
{
  HWIO_OUT(RPM_IPC, (1<<9));
}

void send_mpss_vmpm_interrupt(void)
{
  HWIO_OUT(RPM_IPC, (1<<13));
}

void send_ssc_vmpm_interrupt(void)
{
  HWIO_OUT(RPM_IPC, (1<<25));
}

void send_cdsp_wakeup_interrupt(void)
{
  HWIO_OUT(RPM_IPC, (1<<3));
}

void send_apss_wakeup_interrupt(void)
{
  HWIO_OUT(RPM_IPC, (1<<7));
}

void send_lpass_wakeup_interrupt(void)
{
  HWIO_OUT(RPM_IPC, (1<<11));
}

void send_mpss_wakeup_interrupt(void)
{
  HWIO_OUT(RPM_IPC, (1<<15)); 
}

void send_ssc_wakeup_interrupt(void)
{
  HWIO_OUT(RPM_IPC, (1<<27));
}

/*
 * TODO: check when MPM Interrupts are available on IPCat
 * Need to add config for LPASS wakeup
 */
/* MPM wakeup interrupts with RPM as the destination. <MPM index>, <rpm_interrupt index> */
mpm_rpm_interrupt_type rpm_wakeup_ints[NUM_RPM_WAKEUP_INTS] = {
    {HAL_MPMINT_LPASS_SPM_BRINGUP_REQ_ISR, 56 /* LPASS bringup_req */},
    {HAL_MPMINT_WCSS_MPM_WAKEUP_ISR,       33 /* MPSS bringup_req */ },
};

/* these addresses map to the end of the master's request section for enable
 * and clear, and to the end of the master's ack section for status
 */
const vmpm_master_info_type vmpm_masters_info[VMPM_NUM_MASTERS] =
{
  /* APSS */
  {
    GPIO_TARGET_PROC_ID_HMSS,       /* target_id, TLMM_GPIO_INTR_CFGn[TARGET_PROC] */
    send_apss_wakeup_interrupt,     /* pfnSendWakeup */
    send_apss_vmpm_interrupt,       /* pfnSendInterrupt */
    9                               /* APPS HLOS VMPM interrupt */
  },

  /* MSS */
  {
    GPIO_TARGET_PROC_ID_MSS,        /* target_id, TLMM_GPIO_INTR_CFGn[TARGET_PROC] */ // ? not clear
    send_mpss_wakeup_interrupt,     /* pfnSendWakeup */
    send_mpss_vmpm_interrupt,       /* pfnSendInterrupt */
    5                               /* MSS VMPM interrupt */ 
  },

  /* LPASS */
  {
    GPIO_TARGET_PROC_ID_LPASS,      /* target_id, TLMM_GPIO_INTR_CFGn[TARGET_PROC] */
    send_lpass_wakeup_interrupt,    /* pfnSendWakeup */
    send_lpass_vmpm_interrupt,      /* pfnSendInterrupt */
    21                              /* LPASS VMPM interrupt */
  },

  /* CDSP */
  {
    GPIO_TARGET_PROC_ID_CDSP,        /* target_id, TLMM_GPIO_INTR_CFGn[TARGET_PROC] */
    send_cdsp_wakeup_interrupt,      /* pfnSendWakeup */
    send_cdsp_vmpm_interrupt,        /* pfnSendInterrupt */
    37                              /*  CDSP VMPM interrupt */
  },
};

