/*===========================================================================
                              lpr_definition_uber.c

SERVICES:

DESCRIPTION:

INITIALIZATION AND SEQUENCING REQUIREMENTS:
  Description...

Copyright (c) 2005,2014 QUALCOMM Technologies Incorporated.  All Rights Reserved.
QUALCOMM Proprietary.  Export of this technology or software is regulated
by the U.S. Government. Diversion contrary to U.S. law prohibited.
===========================================================================*/


//===========================================================================
//                     Includes and Variable Definitions
//===========================================================================

//---------------------------------------------------------------------------
// Include Files
//---------------------------------------------------------------------------
#include "mpm.h"
#include "vmpm.h"
#include "time_service.h"
#include "comdef.h"
#include "Clock.h"
#include "npa.h"
#include "npa_resource.h"
#include "ddr_drivers.h"
#include "rpm_hwio.h"
#include "rpm_definitions.h"
#include "cortex-m3.h"
#include "swevent.h"
#include "ClockDefs.h"
#include "system_db.h"
#include "system_db_rpm.h"
#include "dog.h"
#include "cpu.h"
#include "rob.h"
#include "image_layout.h"
#include "railway.h"
#include "pmapp_npa.h"
#include "CoreVerify.h"
#include "gpio_debug.h"
#include "pm_clk_sleep.h"
#include "rpm_messageram.h"
#include "saw2_hwio.h"
#include "etm.h"
#include "cpr.h"
#include "cpr_isr.h"

#include "qfprom_pte_lpass_hwio.h"

#include "pm_pon.h"

#include "pm_sleep.h"
#include "Chipinfo.h"

#ifdef SLEEP_B_CLAMP
#include "tcsr_hwio.h"
#endif

#include "mpm2_pshold_hwio.h"
#include "apcs_gic_hwio.h"

//---------------------------------------------------------------------------
// Constant / Define Declarations
//--------------------------------------------------------------------------
#define MAX_XO_CLIENTS  8
#define INTERNAL_XO_CLIENT_ID   (MAX_XO_CLIENTS - 1)

//---------------------------------------------------------------------------
// Type Declarations
//---------------------------------------------------------------------------
typedef struct sleep_stats_type
{
  uint32 stat_type;
  uint32 count;
  uint64 last_entered_at;
  uint64 last_exited_at;
  uint64 accumulated_duration;
  uint64 client_votes; /* Log 8 histories of xo vote state */
  uint32 reserved[2];
} sleep_stats_type;

typedef enum
{
  SLEEP_STATS_VDD_LOW = MPM_SLEEP_MODE_VDD_LOW,
  SLEEP_STATS_VDD_MIN = MPM_SLEEP_MODE_VDD_MIN,
  SLEEP_STATS_COUNT
} sleep_stats_modes;

typedef enum
{
  SLEEP_SUCCESS = 0,

  SLEEP_ERROR_NOT_ENOUGH_TIME,
  SLEEP_ERROR_PENDING_INTERRUPT,

  SLEEP_RESULT_COUNT,
} sleep_result_type;

//---------------------------------------------------------------------------
// Global Constant Definitions
//---------------------------------------------------------------------------
uint64 enter_deep_sleep_time;

//---------------------------------------------------------------------------
// Local Object Definitions
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Static Variable Definitions
//---------------------------------------------------------------------------
static const unsigned MPM_IRQ = 42;
static const unsigned QTIMER_IRQ = 50;

static uint32 deep_sleep_bail_count;
static sleep_result_type sleep_result;
static ClockPowerDomainIdType nPowerDomainId;
static uint8 BIMC_PC_CFG;

static npa_client_handle cnoc_handle;
static const char sleep_npa_client_name[] = "rpm internal";

__attribute__((section("sleep_stats")))
static sleep_stats_type sleep_stats[2] =
{
  {
      /* .stat_type    */ 0x776f6c76, // "vlow" in little endian
      /* .client_votes */ 0,
  },
  {
      /* .stat_type    */ 0x6E696D76, // "vmin" in little endian
      /* .client_votes */ 0,
  }
};

uint64 mpm_enter_latency =0;

static struct
{
  uint64 exit_latency;
  uint64 enter_latency;
  mpm_sleep_mode_type deep_sleep_mode;
} sleep_mode;

static int *enabled_interrupts = NULL;

static volatile unsigned gicd_ctlr_reg_val; // CR 2006056: used to save/restore GICD_CTLR register


//---------------------------------------------------------------------------
// Forward Declarations
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// External References
//---------------------------------------------------------------------------
extern uint64_t sched_get_next_start(void);
extern uint64_t sched_get_next_required_start(void);
extern int mx_id;

extern int rpm_npa_get_ee_client_id(const npa_client* client);
extern void message_ram_update_master_stats_periodic(void);

#ifdef DDR_LPR_TRACING
extern void pull_ddr_regs(void);
#endif  //DDR_LPR_TRACING

#if DAL_CONFIG_TARGET_ID==0x8998
// CR 1069786 - Support Vdd Min with display workaround
static bool mmss_gdsc_enabled;

//CR 1054128 - Display issue workaround
extern void HAL_clk_MMSSPowerDomainRestore (bool);
#endif /* DAL_CONFIG_TARGET_ID==0x8998 */


//===========================================================================
//                             Macro Definitions
//===========================================================================
#define BIMC_PC_ENABLE 2
#define BIMC_PC_DISABLE 1

//===========================================================================
//                           Function Definitions
//===========================================================================

bool debugger_connected(void);

static boolean prepare_interrupts(void)
{
  DALBOOL retval = TRUE;
  int     num_masks = ((SCS.IntCtrlType & 0x1F) + 1);
  int     i;

  // Configure the MPM to honor the system's wakeup interrupts
  vmpm_prepare_for_sleep();

  // Check to see if an interrupt came in before we switched over to the MPM
  // If so, we need to abort the xo shutdown process
  if(is_any_interrupt_pending())
  {
    retval = FALSE;
  }

  if (!enabled_interrupts)
  {
    enabled_interrupts = (int *)malloc(num_masks * sizeof(int));

    if (NULL == enabled_interrupts)
    {
      ERR_FATAL("malloc failed to allocate memmory:", 0, 0, 0);
    }
  }



  // Save and disable all enabled interrupts
  for (i = 0; i < num_masks; i++)
  {
    enabled_interrupts[i] = SCS.NVIC.Enable[i];
    SCS.NVIC.Disable[i] = 0xFFFFFFFF;
  }

  // Enable the MPM interrupt so we can wake from sleep.
  interrupt_clear(MPM_IRQ);
  interrupt_enable(MPM_IRQ);

  return retval;
}

static void restore_interrupts(void)
{
  int num_masks = ((SCS.IntCtrlType & 0x1F) + 1);
  int i;

  CORE_VERIFY_PTR(enabled_interrupts);

  // Enable all interrupts previously stored
  for (i = 0; i < num_masks; i++)
  {
    SCS.NVIC.Enable[i] = enabled_interrupts[i];
  }

  // distribute any external wakeup interrupts to interested masters
  vmpm_propogate_interrupts();

  interrupt_disable(MPM_IRQ);
}

static uint64 calculate_halt_wakeup_time(void)
{
  return (sched_get_next_start() - sleep_mode.exit_latency);
}

static uint64 calculate_wakeup_time(void)
{
  uint64 task_start = sched_get_next_required_start();
  if(task_start <= sleep_mode.exit_latency)
  {
    return 0;
  }
  else
  {
    return (task_start - sleep_mode.exit_latency);
  }
}

static uint64 calculate_sleep_duration(void)
{
  uint64 wakeup_time = calculate_wakeup_time();
  uint64 sleep_start = time_service_now() + sleep_mode.enter_latency;

  if(wakeup_time <= sleep_start)
      return 0;
  else
      return wakeup_time - sleep_start;
}

void vdd_min_latency()
{
  //Calculate latency for current clock speed.
  const cpu_mode_id rpm_cpu_speed = cpu_current_speed();

  sleep_mode.enter_latency = rob_get_duration (ROB_DURATION_VDD_MIN_ENTER, rpm_cpu_speed);
  mpm_enter_latency =  mpm_deep_sleep_enter_latency();
  if (sleep_mode.enter_latency == 0)
  {
    sleep_mode.enter_latency = 0xC000 + mpm_enter_latency; //  2.56mS + mpm latency - conservative default value
  }
  else
  {
    sleep_mode.enter_latency += mpm_enter_latency;
  }

  //vdd_min exit latency = PXO warm up time
  //                     + time from ROB_EVENT_MPM_PRE_SW_DONE to ROB_EVENT_VDD_MIN_EXIT
  //                     + constant for other processing in getting out of vdd_min.

  // Current value based on pronto profiling
  // sleep_mode.exit_latency = 0x2A00;
  sleep_mode.exit_latency = rob_get_duration (ROB_DURATION_VDD_MIN_EXIT, rpm_cpu_speed);
  if (sleep_mode.exit_latency == 0)
  {
    sleep_mode.exit_latency = 0xC000 + mpm_deep_sleep_exit_latency(); //  2.56mS + mpm latency - conservative default value
  }
  else
  {
    sleep_mode.exit_latency += mpm_deep_sleep_exit_latency();
  }
}

boolean rpm_halt_latency()
{
  unsigned switch_time = cpu_get_switch_time();
  sleep_mode.enter_latency = switch_time + SLEEP_HALT_ENTER_LATENCY;
  sleep_mode.exit_latency = switch_time + SLEEP_HALT_EXIT_LATENCY;
  return ((time_service_now() + sleep_mode.enter_latency + sleep_mode.exit_latency) < sched_get_next_start());
}

__attribute__((section("sleep_cram_reclaim_pool")))
void sleep_modes_init(void)
{
  sleep_mode.enter_latency = 0;
  sleep_mode.exit_latency = 0;
  sleep_mode.deep_sleep_mode = MPM_SLEEP_MODE_VDD_MIN;

  Clock_GetPowerDomainId("VDD_BIMC", &nPowerDomainId);

  deep_sleep_bail_count = 0;
#ifdef MSM_DISABLE_BIMC_PC
  BIMC_PC_CFG = BIMC_PC_DISABLE;
#else
  BIMC_PC_CFG = BIMC_PC_ENABLE;
#endif

  interrupt_configure(MPM_IRQ,    LEVEL_HIGH);
  interrupt_configure(QTIMER_IRQ, LEVEL_HIGH);

  CORE_VERIFY_PTR(cnoc_handle = npa_create_sync_client("/clk/cnoc", sleep_npa_client_name, NPA_CLIENT_REQUIRED));
  npa_issue_required_request(cnoc_handle, 37500);
}

#ifndef __clang__
__asm static void halt(void)
{
    ; Lock interrupts via primask instead of basepri during sleep, or else we never wake up.
    mrs r0, basepri
    cpsid i
    mov r1, #0
    msr basepri, r1

    ; Do the halt, using ISB to clear the M3 store buffer
    dsb
    isb
    wfi

    ; Revert interrupt lock to basepri-based.
    msr basepri, r0
    cpsie i
    bx r14
}
#else
__attribute__((naked)) static void halt(void)
{
  asm("mrs r0, basepri");
  asm("cpsid i");
  asm("mov r1, #0");
  asm("msr basepri, r1");
  asm("dsb");
  asm("isb");
  asm("wfi");
  asm("msr basepri, r0");
  asm("cpsie i");
  asm("bx r14");
}
#endif

static void rpm_sleep_enter_workarounds(void)
{
#ifdef SLEEP_B_CLAMP
//CR735970
  if(Chipinfo_GetVersion() >= CHIPINFO_VERSION(2,0))
  {
    HWIO_OUTF(TCSR_VREF_QREFS_VBG_PWRDOWN_CTRL, PWRDN_B, 0);
  }
#endif

  /*
   * CR 2006056 - disable/enable non-secure interrupts targeted to GIC on Vdd Min entry/exit.
   *
   * In addition to turning off/on gcc_hmss_ahb_clk to the GIC (intenral memories) on Vdd Min entry/exit,
   * it is recommended to disable/enable non-secure interrupts targeted to GIC on Vdd Min entry/exit.
   */
  uint32 mask = HWIO_FMSK(APCS_GICD_CTLR, ENABLE_GRP1_SEC) | \
                HWIO_FMSK(APCS_GICD_CTLR, ENABLE_GRP1) | \
                HWIO_FMSK(APCS_GICD_CTLR, ENABLE_GRP0);

  // Save current status
  gicd_ctlr_reg_val = HWIO_IN(APCS_GICD_CTLR);

  SWEVENT(RPM_GIC_DISABLE, gicd_ctlr_reg_val);

  // Disable GIC
  HWIO_OUTM(APCS_GICD_CTLR, mask, 0x0);

  // Wait for completion
  while( HWIO_INF(APCS_GICD_CTLR, RWP) != 0 );
}

static void rpm_sleep_exit_workarounds(void)
{
#ifdef SLEEP_B_CLAMP
//CR735970
  if(Chipinfo_GetVersion() >= CHIPINFO_VERSION(2,0))
  {
    HWIO_OUTF(TCSR_VREF_QREFS_VBG_PWRDOWN_CTRL, PWRDN_B, 1);
  }

#endif

  /*
   * CR 2006056 - disable/enable non-secure interrupts targeted to GIC on Vdd Min entry/exit.
   *
   * In addition to turning off/on gcc_hmss_ahb_clk to the GIC (intenral memories) on Vdd Min entry/exit,
   * it is recommended to disable/enable non-secure interrupts targeted to GIC on Vdd Min entry/exit.
   */
  SWEVENT(RPM_GIC_ENABLE);

  // Restore GIC
  HWIO_OUT(APCS_GICD_CTLR, gicd_ctlr_reg_val);

  // Wait for completion
  while( HWIO_INF(APCS_GICD_CTLR, RWP) != 0 );
}


#ifdef DDR_LPR_TRACING
static bool sleep_ddr_active()
{
    ddr_interface_state ddr_status = ddr_get_status();
    return (((ddr_status.sdram0_cs0 == DDR_ACTIVE) || (ddr_status.sdram0_cs1 == DDR_ACTIVE)) &&
            ((ddr_status.sdram1_cs0 == DDR_ACTIVE) || (ddr_status.sdram1_cs1 == DDR_ACTIVE)));
}
#endif  //DDR_LPR_TRACING

void rpm_halt_enter(void)
{
  uint64 wakeup_time, wakeup_lo, wakeup_hi;
  uint32 temp_lo, temp_hi;
  bool re_enter_wfi;
  railway_settings cx_settings;

  sleep_result = SLEEP_ERROR_NOT_ENOUGH_TIME;
  
  message_ram_update_master_stats_periodic();

  if(rpm_halt_latency())
  {
    sleep_result = SLEEP_SUCCESS;
    rob_set_recording_speed(cpu_current_speed());
    rob_mark_event (ROB_EVENT_RPM_HALT_ENTER);

    // pet the dog everytime we go to sleep to ensure the max for sleep
    pmic_wdog_pet(1);

#ifdef DDR_LPR_TRACING
    if(sleep_ddr_active())
    {
      pull_ddr_regs();
    }
#endif //DDR_LPR_TRACING

    npa_issue_required_request(cnoc_handle, 19200);

    // Allow RPM speed to settle first before computing the halt wake up time, set the floor to SVS2
    cpu_update_idle(true);

    do
    {
        uint32 cpr_interrupt = cpr_isr_get_interrupt(CPR_RAIL_CX);
        re_enter_wfi = false;
        wakeup_time = calculate_halt_wakeup_time();
        wakeup_lo   = wakeup_time & 0xFFFFFFFFU;
        wakeup_hi   = wakeup_time >> 32;


        // Set wakeup time.
        HWIO_OUT(RPM_F0_QTMR_V1_CNTP_CVAL_LO, wakeup_lo);
        HWIO_OUT(RPM_F0_QTMR_V1_CNTP_CVAL_HI, wakeup_hi);
        HWIO_OUT(RPM_F0_QTMR_V1_CNTP_CTL, 1);
        interrupt_enable(QTIMER_IRQ);
        temp_lo = HWIO_IN(RPM_F0_QTMR_V1_CNTP_CVAL_LO);
        temp_hi = HWIO_IN(RPM_F0_QTMR_V1_CNTP_CVAL_HI);
        SWEVENT(SLEEP_RPM_HALT_ENTER, temp_hi, temp_lo);

        dog_enable(false);
        rob_mark_event (ROB_EVENT_RPM_HALT_PRE_CLKOFF);
        halt();
        rob_mark_event (ROB_EVENT_RPM_HALT_POST_CLKOFF);
        dog_enable(true);



        railway_get_current_settings(cx_id, &cx_settings);

        //CPR check if:
        //   1.  in SVS2
        //   2.  CPR interrupt pending
        //   3.  enough time between now and the next wakeup to finish CPR handling
        if((cx_settings.mode == RAILWAY_SVS_LOW) &&
           interrupt_is_pending(cpr_interrupt) &&
           ((time_service_now() + rob_get_duration(ROB_DURATION_RPM_CPR_UPDATE, cpu_current_speed())) < wakeup_time))
        {
            rob_mark_event (ROB_EVENT_RPM_CPR_UPDATE_START);
            //CPR function will clear the CPR interrupt so its no longer pending
            cpr_isr_process(CPR_RAIL_CX);
            SWEVENT(SLEEP_CPR_SVS2_PROCESS);
            rob_mark_event (ROB_EVENT_RPM_CPR_UPDATE_END);
        }
        if((!is_any_interrupt_pending()) && rpm_halt_latency())
        {
            re_enter_wfi = true;
        }

    }while(re_enter_wfi);

    cpu_update_idle(false); //set the floor back to SVS

    //defensive check to make sure we didn't enter svs2 accidentally
    CORE_VERIFY(cpu_current_speed() != CPU_SLOW2);

    npa_issue_required_request(cnoc_handle, 37500);

    // Stop timer; it did its job of waking us up, but we don't need it anymore.
    interrupt_disable(QTIMER_IRQ);
    HWIO_OUT(RPM_F0_QTMR_V1_CNTP_CTL, 2);

    system_db_statehandler(SYSTEMDB_ENTER_HALT);
  }
}

void rpm_halt_exit(void)
{
  if (sleep_result == SLEEP_SUCCESS)
  {
    //this log happens extremely often right now. Disable for the time being
    SWEVENT(SLEEP_RPM_HALT_EXIT);
    system_db_statehandler(SYSTEMDB_EXIT_HALT);
    // Record the timestamp
    rob_mark_event (ROB_EVENT_RPM_HALT_EXIT);
    rob_mark_duration (ROB_DURATION_RPM_HALT_ENTER);
    rob_mark_duration (ROB_DURATION_RPM_HALT_EXIT);
  }
  message_ram_update_master_stats_periodic();
}

static void update_deep_sleep_residencies(bool entering_sleep, bool mock_vdd_min)
{
  railway_settings cx_settings, mx_settings;
  railway_corner sleep_mode_cx, sleep_mode_mx;

  if(mock_vdd_min)
  {
    return;
  }

  railway_get_sleep_modes(cx_id, mx_id, &sleep_mode_cx, &sleep_mode_mx);

  railway_get_current_settings(cx_id, &cx_settings);
  railway_get_current_settings(mx_id, &mx_settings);

  if (sleep_mode_cx != cx_settings.mode)
  {
    if(entering_sleep)
        railway_track_rail_residence(cx_id, sleep_mode_cx, cx_settings.mode);
    else
        railway_track_rail_residence(cx_id, cx_settings.mode, sleep_mode_cx);
  }

  if (sleep_mode_mx != mx_settings.mode)
  {
    if(entering_sleep)
        railway_track_rail_residence(mx_id, sleep_mode_mx, mx_settings.mode);
    else
        railway_track_rail_residence(mx_id, mx_settings.mode, sleep_mode_mx);
  }
}

void deep_sleep_enter(bool mock_vdd_min)
{
  uint64 sleep_duration;
  pm_err_flag_type pmic_err;

#if DAL_CONFIG_TARGET_ID==0x8998
  // CR 1069786 - Support Vdd Min with display workaround
  vmpm_data_t *vmpm = message_ram_vmpm(VMPM_APPS);

  mmss_gdsc_enabled = (bool)vmpm->mpm_proxy_register;
#endif

  sleep_result = SLEEP_SUCCESS;

  rob_set_recording_speed (cpu_current_speed());
  rob_mark_event (ROB_EVENT_VDD_MIN_ENTER);

#ifdef DDR_LPR_TRACING
  if(sleep_ddr_active())
  {
    pull_ddr_regs();
  }
#endif //DDR_LPR_TRACING

  do
  {
    sleep_duration = calculate_sleep_duration();
    if (!sleep_duration)
    {
      //log that we bailed early
      SWEVENT(SLEEP_NO_DEEP_SLEEP, sleep_mode.deep_sleep_mode, 0);
      sleep_result = SLEEP_ERROR_NOT_ENOUGH_TIME;
      deep_sleep_bail_count++;
      break;
    }

    //sleep Duration should include mpm enter latency as this will also be part of MPM sleep time
    sleep_duration += mpm_enter_latency;

    if(!prepare_interrupts())
    {
      //log that we bailed early
      SWEVENT(SLEEP_NO_DEEP_SLEEP, sleep_mode.deep_sleep_mode, 1);
      sleep_result = SLEEP_ERROR_PENDING_INTERRUPT;
      deep_sleep_bail_count++;
      break;
    }

    // pet the dog everytime we go to sleep to ensure the max for sleep
    pmic_wdog_pet(1);

    /* Start of the timing profiling*/
    /* GPIO LOW */
    gpio_test_low(GPIO_DEEP_SLEEP,GPIO_SLEEP_TRANSITION);


    // Ensure that we don't exceed sleep_stats array bounds --
    CORE_VERIFY(sleep_mode.deep_sleep_mode < SLEEP_STATS_COUNT);
    // update sleep_stats here to avoid updating if we bail out.
    sleep_stats[sleep_mode.deep_sleep_mode].count ++;
    sleep_stats[sleep_mode.deep_sleep_mode].last_entered_at = time_service_now ();
    // Log sleep enter here to avoid claiming we went to sleep if we bail out.
    SWEVENT(SLEEP_DEEP_SLEEP_ENTER, sleep_mode.deep_sleep_mode, sleep_stats[sleep_mode.deep_sleep_mode].count);

    rpm_sleep_enter_workarounds();

    ETM_save_state();

    cpr_enter_sleep();

    // put ddr into self refresh and power collapse bimc if its configured to do so
    Clock_ProcessorSleep(CLOCK_SLEEP_MODE_POWER_COLLAPSE, BIMC_PC_CFG);

    // Configure voltage to sleep.
    pmic_err = pm_rpm_enter_sleep(PM_SLEEP_MODE_VDD_MIN);
    CORE_VERIFY(pmic_err == PM_ERR_FLAG__SUCCESS);

    // put all (capable) clocks to sleep except bimc
    Clock_ProcessorSleep(CLOCK_SLEEP_MODE_POWER_COLLAPSE, 0);

#if DAL_CONFIG_TARGET_ID==0x8998
    //CR 1054128 - Display issue workaround
    //CR 1069786 - Support Vdd Min with display workaround
    if(!mmss_gdsc_enabled)
    {
      HAL_clk_MMSSPowerDomainRestore(FALSE);
    }
#endif /* DAL_CONFIG_TARGET_ID==0x8998 */

    update_deep_sleep_residencies(true, mock_vdd_min);

    SWEVENT(SLEEP_DEEP_SLEEP_ENTER_COMPLETE, sleep_mode.deep_sleep_mode, sleep_duration);
    mpm_sw_done(sleep_duration);
  } while(FALSE);
}

void deep_sleep_exit(void)
{
  pm_err_flag_type pmic_err;
  uint64 deep_sleep_time = (time_service_now() - enter_deep_sleep_time);

  SWEVENT(SLEEP_DEEP_SLEEP_EXIT, sleep_mode.deep_sleep_mode);


  if(sleep_result == SLEEP_SUCCESS)
  {
    //restore everything except bimc
    Clock_ProcessorRestore(CLOCK_SLEEP_MODE_POWER_COLLAPSE, 0);

#if DAL_CONFIG_TARGET_ID==0x8998
    //CR 1054128 - Display issue workaround
    //CR 1069786 - Support Vdd Min with display workaround
    if(!mmss_gdsc_enabled)
    {
      HAL_clk_MMSSPowerDomainRestore(TRUE);
    }
#endif /* DAL_CONFIG_TARGET_ID==0x8998 */

    // restore voltage
    pmic_err = pm_rpm_exit_sleep(PM_SLEEP_MODE_VDD_MIN);
    CORE_VERIFY(pmic_err == PM_ERR_FLAG__SUCCESS);

    //take ddr out of self-refresh and restore bimc if its configured to do bimc power collapse
    Clock_ProcessorRestore(CLOCK_SLEEP_MODE_POWER_COLLAPSE, BIMC_PC_CFG);

    cpr_exit_sleep();

    ETM_restore_state();

    rpm_sleep_exit_workarounds();
  }

  /*
   * restore_interrupts() should be called only after prepare_interrupts() has been called
   */
  if(sleep_result != SLEEP_ERROR_NOT_ENOUGH_TIME)
  {
      restore_interrupts();
  }

  mpm_teardown_sleep();

  /* GPIO HIGH */
  gpio_test_high(GPIO_DEEP_SLEEP, GPIO_ACTIVE_TRANSITION);
  /*End of the timing profiling*/
  SWEVENT(SLEEP_DEEP_SLEEP_EXIT_COMPLETE, sleep_mode.deep_sleep_mode);

  // mark the event
  rob_mark_event (ROB_EVENT_VDD_MIN_EXIT);
  rob_mark_duration (ROB_DURATION_VDD_MIN_ENTER);
  rob_mark_duration (ROB_DURATION_VDD_MIN_EXIT);

  if(sleep_result == SLEEP_SUCCESS)
  {
    sleep_stats[sleep_mode.deep_sleep_mode].last_exited_at = time_service_now ();
    sleep_stats[sleep_mode.deep_sleep_mode].accumulated_duration += (sleep_stats[sleep_mode.deep_sleep_mode].last_exited_at - sleep_stats[sleep_mode.deep_sleep_mode].last_entered_at);
  }
  message_ram_update_master_stats_periodic();
}

// CR 1065344 - Remove wlan freeze io workaround since APPS also accesses to the register and caused race condition.
// The workaround was moved to APPS side.
#if 0
static uint32_t mpm_wcssaon_config_register; // CR 1054128: used for debugging in case
                                             // mpm wcssaon config register is not programmed as expected.
/*
 * CR 1052292: WLAN freeze io support
 */
static void sleep_wlan_freeze_io_workaround(void)
{
  vmpm_data_t *vmpm = message_ram_vmpm(VMPM_MODEM);
  uint32  proxy_reg_val = vmpm->mpm_proxy_register;
  uint32  new_reg_val;

  mpm_wcssaon_config_register = HWIO_IN(MPM2_MPM_WCSSAON_CONFIG);

  new_reg_val = ((~proxy_reg_val) & mpm_wcssaon_config_register) | proxy_reg_val;

  SWEVENT(SLEEP_WLAN_FREEZE_IO_WORKAROUND, mpm_wcssaon_config_register, new_reg_val);

  HWIO_OUT(MPM2_MPM_WCSSAON_CONFIG, new_reg_val);

  /*
   * Update proxy register with the current register value
   */
  mpm_wcssaon_config_register = HWIO_IN(MPM2_MPM_WCSSAON_CONFIG);
  vmpm->mpm_proxy_register = mpm_wcssaon_config_register;
}
#endif

void vdd_min_enter(bool mock_vdd_min)
{
  railway_settings cx_settings;
  railway_settings mx_settings;
  railway_corner sleep_mode_mx, sleep_mode_cx;

  railway_get_current_settings(cx_id, &cx_settings);
  railway_get_current_settings(mx_id, &mx_settings);

  railway_get_sleep_modes(cx_id, mx_id, &sleep_mode_cx, &sleep_mode_mx);

  if(mock_vdd_min)
  {
    mpm_set_vmin_voltages(mx_settings.microvolts, mx_settings.microvolts,
                          cx_settings.microvolts, cx_settings.microvolts);

    sleep_mode.deep_sleep_mode = MPM_SLEEP_MODE_VDD_LOW;
  }
  else
  {
    CORE_VERIFY(sleep_mode_mx <= mx_settings.mode);
    CORE_VERIFY(sleep_mode_cx <= cx_settings.mode);
    mpm_set_vmin_voltages(railway_get_corner_voltage(mx_id, sleep_mode_mx), mx_settings.microvolts,
                          railway_get_corner_voltage(cx_id, sleep_mode_cx), cx_settings.microvolts);

    if (sleep_mode_cx >  RAILWAY_RETENTION)
      sleep_mode.deep_sleep_mode = MPM_SLEEP_MODE_VDD_LOW;
    else
      sleep_mode.deep_sleep_mode = MPM_SLEEP_MODE_VDD_MIN;
  }

  if(sleep_mode.deep_sleep_mode == MPM_SLEEP_MODE_VDD_LOW)
  {
    system_db_statehandler(SYSTEMDB_ENTER_XO);
    /*
     * Prevent freeze IOs during vdd_low for MIPI static display
     */
    mpm_config_freeze_ios(FALSE);
  }
  else
  {
    system_db_statehandler(SYSTEMDB_ENTER_VDDMIN);
    /*
     * Use the BSP config data for freeze IOs enablement
     */
    mpm_config_freeze_ios(TRUE);

// CR 1065344 - Remove wlan freeze io workaround since APPS also accesses to the register and caused race condition.
// The workaround was moved to APPS side.
#if 0
    sleep_wlan_freeze_io_workaround();
#endif
  }

  /*
   * Must be before vdd_min_latency() since it calculates MPM latencies based on SPMI commands
   */
  mpm_setup_chip_sleep();

  vdd_min_latency();

  deep_sleep_enter(mock_vdd_min);
}

void vdd_min_exit(bool mock_vdd_min)
{
  update_deep_sleep_residencies(false, mock_vdd_min);

  deep_sleep_exit();

  if(sleep_mode.deep_sleep_mode == MPM_SLEEP_MODE_VDD_LOW)
  {
    system_db_statehandler(SYSTEMDB_EXIT_XO);
  }
  else
  {
    system_db_statehandler(SYSTEMDB_EXIT_VDDMIN);
  }
}

void sleep_update_xo_stats(const npa_client *xo_clients, const npa_client *client_updated)
{
    int client_id = -1;
    int vote = 0;
    const npa_client *client = NULL;

    if(client_updated->type != NPA_CLIENT_REQUIRED)
    {
        return;
    }

    client_id = rpm_npa_get_ee_client_id(client_updated);

    if(client_id < 0)
    {
        /*
         * ignore clock driver's xo vote change
         */
        return;
    }

    vote = client_updated->work[client_updated->index^1].state; // index is not updated yet. Need to XOR to get correct index

    /*
     * The Least Significant Byte contains the last xo stats.
     * Check if the client's vote is changed from the last one
     */
    if(!(vote ^ (0x1 & (sleep_stats[0].client_votes >> client_id))))
    {
        /*
         * xo stats is not changed
         */
        return;
    }

    /*
     * update xo stats in MSG RAM
     */
    message_ram_update_master_xo_stats(client_id, vote);

    /*
     * update xo stats in sleep stats
     */
    // allocate space for current vote state
    sleep_stats[0].client_votes <<= MAX_XO_CLIENTS;

    // traverse client list and store the current XO votes
    for(client = xo_clients; client != NULL; client = client->next)
    {
        if(client->type != NPA_CLIENT_REQUIRED)
            continue;

        if(client != client_updated)
            vote = client->work[client->index].state;
        else
            vote = client->work[client->index^1].state; // index is not updated yet. Need to XOR to get correct index

        if(vote)
        {
            client_id = rpm_npa_get_ee_client_id(client);

            if(client_id >= 0)
                sleep_stats[0].client_votes |= (1 << client_id);
            else
                sleep_stats[0].client_votes |= (1 << INTERNAL_XO_CLIENT_ID);
        }
    }
}
/*===========================================================================
FUNCTION: sleep_is_any_interrupt_pending

DESCRIPTION:
This is the same function as is_any_interrupt_pending in exceptions.c.
The main difference is that by the time this function is called, we would have
already cleared the NVIC Enabled register. Instead, we use the backup taken in
a global array.

RETURN VALUE: True if any interrupt is pending
===========================================================================*/
bool sleep_is_any_interrupt_pending(void)
{
  int num_ints, i;
  bool result = false;
  num_ints = ((SCS.IntCtrlType & 0x1F) + 1) << 5;
  CORE_VERIFY_PTR(enabled_interrupts);
  for(i = 0; ((i < num_ints / 32) && !result); i++)
  {
    if (enabled_interrupts[i] & SCS.NVIC.Set[i])
      result = true;
  }
  return result;
}
