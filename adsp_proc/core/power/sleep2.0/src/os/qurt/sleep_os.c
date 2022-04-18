/*==============================================================================
  FILE:         sleep_os.c

  OVERVIEW:     This file provides the sleep task and OS-specific
                functionality for the processors with Qurt running on them.

  DEPENDENCIES: sleepOS_mainTask() is the entry point to the lowest-priority
                thread processing.

                Copyright (c) 2011-2017 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/sleep2.0/src/os/qurt/sleep_os.c#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include <stdlib.h>
#include "comdef.h"
#include "sleepi.h"
#include "rcinit.h"
#include "qurt.h"
#include "npa.h"
#include "DALDeviceId.h"
#include "DALStdErr.h"
#include "synthRegistry.h"
#include "timer.h"
#include "sleep_config.h"
#include "CoreIni.h"
#include "sleep_npa_scheduler.h"
#include "sleep_os.h"
#include "sleep_osi.h"
#include "sleep_pmi.h"
#include "sleep_idle_plugin.h"
#include "sleep_target.h"
#include "sleep_solveri.h"
#include "rpmclient.h"
#include "sleep_stats.h"
#include "sleep_statsi.h"
#include "DDIClock.h"
#include "sleep_utils.h"
#include "sleepActivei.h"

#ifdef USLEEP_ISLAND_MODE_ENABLE
#include "uSleep.h"
#include "uSleep_os.h"
#endif

/*==============================================================================
                          INTERNAL TYPE DEFINITIONS
 =============================================================================*/
/**
 * sleep_handles
 *
 * @brief Main sleep structure for various node and device handles used 
 *        during the current sleep cycle
 */
typedef struct sleep_handles_s
{
  /* DAL Client of Clock driver for requesting cpu frequency during Sleep */
  DalDeviceHandle   *dalClkHandle;

  /* Handle to vote on /npa/in_stm resource */
  npa_client_handle sleepInStmHandle;
  
  /* Query handle to the /clk/cpu resource */
  npa_query_handle  clkCpuQueryHandle;
}sleep_handles;

/**
 * sleep_state
 *
 * @brief Main sleep state structure used for current sleep 
 *        cycle data
 */
typedef struct sleep_state_s
{
  /* The synthLPRM to notify if the sleep duration changes.
   * This is the output mode of the solver */
  sleep_synth_lprm *selected_synthLPRM;

  /* Copy of hard deadline for NPA (expected sleep exit time) in absolute ticks */
  uint64 hard_deadline_copy;

  /* Solver input object containing various restrictions for a given
   * sleep cycle. */
  sleep_solver_input *solver_input;

  /* Object containing output from Sleep solver based on various
   * input restrictions. */
  sleep_solver_output *solver_output;

  /* Object containing various statistics related information from
   * the last complete sleep cycle.*/
  sleepStats_input cycle_stats;

  /* Flag to avoid unnecessary execution of Sleep exit path logic 
   *
   * This flag is useful in two scenarios:
   * 1. Sleep was bailed due to one of the many restrictions.
   * 2. Target(Q6) woke up from APCR based low power modes and by the time
   *    control comes to Sleep task, exit logic is already executed from
   *    IST context. We don't need to execute it again.
   *
   * Must be set to TRUE if we were to enter solver based low power modes
   * at idle time and to FALSE while executing exit logic.
   */
  boolean execute_sleep_exit_path;

  /* Flag to indicate if processor is running in sleep context. */
  boolean processor_in_stm;

}sleep_state;

/*==============================================================================
                           EXTERNAL GLOBAL VARIABLES
 =============================================================================*/
extern sleep_idle_entry_ptr_type g_sleepIdleEntryTable[];
extern volatile sleep_idle_entry_ptr_type * volatile g_idleEntryPtr;
extern volatile sleep_PMI_handler_ptr_type g_PMIFncPtr;
extern uint8 g_sleepTaskStack[];
extern uint8 g_sleepPMITaskStack[];

/*==============================================================================
                           FORWARD DECLARATIONS
 =============================================================================*/
static void sleepOS_performLPMExit(void);

void sleepHoldoff_registerRCinitCompletionEvent(void);
static void sleepOS_inStmNodeAvailableCb( void *context,
                                          unsigned int event_type,
                                          void *data,
                                          unsigned int data_size );

/*==============================================================================
                           EXTERNAL VARIABLES
 =============================================================================*/
/* Stores target specific config */
extern sleep_target_config g_sleepTargetConfig;

/*==============================================================================
                           INTERNAL VARIABLES
 =============================================================================*/
/* Global sleep state that contains various pieces of data used in the current sleep cycle */
static sleep_state g_sleepState = {0};

/* Various node and device handles */
static sleep_handles g_sleepHandles;

/* Boolean that provides a mechanism to disable sleep (from cold boot), or only allow the
 * most basic (ATS default) low power mode.
 * 
 * Note that in production code, the default is to allow (set to TRUE) all low power modes.
 * 
 * If initially set to FALSE from cold boot (from Main()), sleep will remain in a 'hold off' mode,
 * and will forever spin in a while(1) equivalent loop.  Changing at runtime has no further effect.
 * 
 * If initially set to TRUE from cold boot, and later set to FALSE during runtime, the change will
 * only be recognized upon a restriction change (i.e. ATS is triggered to run).  The solver will
 * be bypassed, and ATS will remain in the 'default' mode, which is typically clock gating. It can
 * then be set back to TRUE to allow all power modes again when the change is recognized as stated
 * above. */
#ifdef FEATURE_DISABLE_SLEEP_MODES
volatile boolean g_sleepAllowLowPowerModes = FALSE;
#else
volatile boolean g_sleepAllowLowPowerModes = TRUE;
#endif

/*==============================================================================
                       INTERNAL FUNCTION DEFINITIONS
 =============================================================================*/
/**
 * sleepOS_inStmNodeAvailableCb
 *
 * @brief Obtains the client handle for /npa/in_stm node when it
 *        becomes available.
 */
static void sleepOS_inStmNodeAvailableCb( void *context,
                                          unsigned int event_type,
                                          void *data,
                                          unsigned int data_size )
{
  CORE_VERIFY_PTR( g_sleepHandles.sleepInStmHandle =
                   npa_create_sync_client("/npa/in_stm", "sleep_in_stm_client",
                                          NPA_CLIENT_REQUIRED ) );
}

/**
 * sleepOS_clkCpuNodeAvailableCb
 *
 * @brief Creates a query handle to /clk/cpu when it becomes available.
 */
static void sleepOS_clkCpuNodeAvailableCb( void *context,
                                           unsigned int event_type,
                                           void *data,
                                           unsigned int data_size )
{
  CORE_VERIFY_PTR( g_sleepHandles.clkCpuQueryHandle =
                   npa_create_query_handle( "/clk/cpu" ) );
}

/**
 * sleepOS_registerPMIHandler
 *
 * @brief As part interrupt registration with QuRT, this function creates 
 *        a thread that will execute function to handle the Power Management
 *        Interrupt (PMI).
 *
 * @note As per pthread specifics, must be called from thread which does not terminate
 *       before the newly created thread does i.e. usually from Sleep task entry 
 *       function.
 */
static void sleepOS_registerPMIHandler(void)
{
  qurt_thread_t      pmiHandlerThread;
  qurt_thread_attr_t pmiHandlerAttr;
  
  /* Set default handler */
  sleepPMI_setHandlerFunctionPTR(sleepOS_PMIPerformer);

  /* Initialize attribute */
  qurt_thread_attr_init(&pmiHandlerAttr);

  /* setting up attributes for pmi handler thread */
  qurt_thread_attr_set_name(&pmiHandlerAttr, PMI_HANDLER_THREAD_NAME);
  qurt_thread_attr_set_tcb_partition(&pmiHandlerAttr, 1); /* locate in uImage */
  qurt_thread_attr_set_priority(&pmiHandlerAttr, SLEEP_PMI_TASK_PRI );
  qurt_thread_attr_set_stack_size(&pmiHandlerAttr, SLEEP_PMI_STACK_SIZE);
  qurt_thread_attr_set_stack_addr(&pmiHandlerAttr, (void *)g_sleepPMITaskStack);
  
  /* Fill in the stack with a marker to try and find overflows */
  memset(g_sleepPMITaskStack, 0xF8, sizeof(uint8) * SLEEP_PMI_STACK_SIZE);

  /* Creating thread to run PMI handler */
  CORE_VERIFY(QURT_EOK == qurt_thread_create(&pmiHandlerThread, &pmiHandlerAttr,
                                             sleepOS_pmiHandler, NULL));

  return;
}

/**
 * sleepOS_qurtInit
 * 
 * @brief Initialize the sleep subsystem.
 */
static void sleepOS_qurtInit( void )
{
  /* Initialize the logging subsystem. */
  sleepLog_initialize();
  sleepLog_setLevel( SLEEP_LOG_LEVEL_MAX );

  /* Initialize target-independent NPA nodes. */
  sleepNPA_initialize();

  /* Initialize LPR / LPRM tracking subsystem. */
  sleepLPR_initialize();

  /* Initialize statistical data system */
  sleepStats_init();

  /* Initialize target-dependent stuff (nodes, modes, etc.). */
  sleepTarget_initialize();

  /* Register for RCInit completion event */
  sleepHoldoff_registerRCinitCompletionEvent();

  /* Register interrupt handler for interrupt 0 (also known as Power 
   * Management Interrupt) */
  sleepOS_registerPMIHandler();

  npa_resource_available_cb( "/npa/in_stm",
                             sleepOS_inStmNodeAvailableCb, NULL );
                             
  npa_resource_available_cb( "/clk/cpu",
                             sleepOS_clkCpuNodeAvailableCb, NULL );

  /* Setup the solver configuration. Must be done after LPR init or wherever the
   * registry is initialized. */
  sleepSolver_init();

  /* Initialize the uSleep system. Must be done after solver lookup tables are initialized
   * so latencies can be accessed */
#ifdef USLEEP_ISLAND_MODE_ENABLE
  uSleepOS_initialize();
#endif

  /* Attaching Dal handle to clock driver for frequency requests */
  CORE_DAL_VERIFY(DAL_DeviceAttach(DALDEVICEID_CLOCK, 
                                   &g_sleepHandles.dalClkHandle));
  return;
}

/**
 * sleepOS_waitForIdle 
 *
 * @brief Suspend Sleep until processor is idle
 *  
 * @note  This call prepares for power collapse and masks the 
 *        global interrupt if HW threads are all wait
 *  
 * @return Enum type indicating if all hardware threads are idle and we entered STM 
 *         or if a return from the kernel call was forced and we are not in STM. 
 */
static idle_status sleepOS_waitForIdle(void)
{
  return (qurt_power_wait_for_idle() ? WAIT_FOR_IDLE_FORCED_EXIT : WAIT_FOR_IDLE_ENTERED_STM);
}

/**
 * sleepOS_performLPMEnter
 * 
 * @brief Function to Enter low-power mode selected by Full Active Time
 *        solver.
 *
 * @param context: Reference to the context from which it is being called. 
 *  
 * @return TRUE if sleep mode was entered 
 *         FALSE if any error or early exit occured 
 */
static boolean sleepOS_performLPMEnter(void* context)
{
  uint64               sleepStart;
  sleepOS_IdleModeType idleModeCfg = (sleepOS_IdleModeType)context;

  /* Execute common sleep entry checks */
  if(0 == (sleepStart = sleepOS_prepareForSleep(idleModeCfg)))
  {
    return FALSE;
  }

  /* Query for pointer to solver input parameters to the Active time solver  */
  g_sleepState.solver_input = sleepActive_GetSolverInput();

  /* Query for pointer to the last selected mode by Active time solver */
  g_sleepState.solver_output = sleepActive_GetSolverOutput();

  /* synth lprm to notify if sleep duration changes */
  g_sleepState.selected_synthLPRM = g_sleepState.solver_output->selected_synthLPRM;

  /* Set selected mode for later use in statistics */
  g_sleepState.cycle_stats.mode = g_sleepState.solver_output->selected_synthLPRM;

  /* Set fLUT for later use in statistics */
  g_sleepState.cycle_stats.fLUT = g_sleepState.solver_input->fLUT;

  /* Setting a flag to indicate that after this point we will need to
   * perform exit logic */
  g_sleepState.execute_sleep_exit_path = TRUE;

  /* Copy hard_deadline value used for solver input to local copy for use
   * by NPA */
  g_sleepState.hard_deadline_copy = g_sleepState.solver_input->hard_deadlines.overall_min;

  /* Calculate the backoff deadline, and pass that to the enter functions. */
  g_sleepState.cycle_stats.backoff_deadline = 
    g_sleepState.hard_deadline_copy - *g_sleepState.solver_output->backoff_ptr;
 
  /* Sleep overhead time */
  sleepStart = CoreTimetick_Get64() - sleepStart;

  sleepLog_printf(SLEEP_LOG_LEVEL_INFO, 2 + (2*2),
                  "Entering modes (hard deadline: 0x%llx) "
                  "(backoff deadline: 0x%llx) "
                  "(backoff: 0x%x) "
                  "(Sleep entry time: %d)",
                  ULOG64_DATA(g_sleepState.hard_deadline_copy),
                  ULOG64_DATA(g_sleepState.cycle_stats.backoff_deadline),
                  *g_sleepState.solver_output->backoff_ptr,
                  (uint32)sleepStart);

  synthLPRM_enter(g_sleepState.solver_output->selected_synthLPRM, 
                  g_sleepState.cycle_stats.backoff_deadline, 
                  g_sleepState.cycle_stats.fLUT);

  return TRUE;
}

/** 
 * sleepOS_performLPMExit 
 *  
 * @brief Function to execute Exit path while coming out of solver based 
 *        low power modes during idle time.
 *
 * Depending on the low power modes we enter, this could be called either
 * from Sleep or an IST context.
 *
 * @param context: Reference to context from which it is being called 
 *                 (unused for now - more for complying with prototype
 *                 of interrupt handler). But if we need to differentiate
 *                 this could be used.
 *
 * @return none
 */
static void sleepOS_performLPMExit(void)
{
  uint32        usedBackoff;
  uint64        currTick;
  static uint32 WBCount      = 0;

  CORE_VERIFY(TRUE == g_sleepState.execute_sleep_exit_path);

  /* Perform any target specific exit requimrents before calling LPR exit
   * routines */
  sleepTarget_performInitialLPRExit();

  /* Continue exit process by getting current time */
  currTick = CoreTimetick_Get64();
  
  sleepLog_printf(SLEEP_LOG_LEVEL_INFO, 0, "Exiting modes");

  usedBackoff = *g_sleepState.solver_output->backoff_ptr;

  /* Logging point of return to stats module */
  sleepStats_putLprTimeData(currTick, SLEEP_STATS_TIME_MSTR_RETURN_TYPE);

  /* Setting the flag to FALSE to avoid any unnecessary execution 
   * of the exit path afterwards. */
  g_sleepState.execute_sleep_exit_path = FALSE;

  /* Get VID register value to report last interrupt that fired */
  g_sleepState.cycle_stats.master_interrupt = qurt_system_vid_get();

  g_sleepState.selected_synthLPRM = NULL;

  /* Exit functions of low power modes */
  synthLPRM_exit(g_sleepState.solver_output->selected_synthLPRM, 
                 g_sleepState.cycle_stats.fLUT);

  /* NPA scheduler can update the hard dealine as part of the enter function. 
   * Set backoff deadline to updated value while still in STM */
  g_sleepState.cycle_stats.backoff_deadline = 
    g_sleepState.hard_deadline_copy - usedBackoff;

  /* Get sleep wakeup time & reason as recorded from standalone or RPM modes */ 
  g_sleepState.cycle_stats.actual_wakeup_time = 
    sleepStats_getLprTimeData(SLEEP_STATS_TIME_WAKEUP_TYPE);

  g_sleepState.cycle_stats.master_wakeup_reason = 
    (sleepStats_wakeup_reason)sleepStats_getMiscData(SLEEP_STATS_MISC_WAKEUP_REASON_TYPE);

  /* Fill in remaining stat input data for logging */ 
  g_sleepState.cycle_stats.hard_deadline = g_sleepState.hard_deadline_copy;

  /* Get last OS boot statistics */
  g_sleepState.cycle_stats.os_overhead.count =     
    qurt_power_shutdown_get_hw_ticks(&g_sleepState.cycle_stats.os_overhead.sleep_time,
                                     &g_sleepState.cycle_stats.os_overhead.awake_time);

  /* Set count to 0 if we performed APCR and WB didn't run which would mean
   * the timestamps are not valid */
  if(WBCount == g_sleepState.cycle_stats.os_overhead.count)
  {
    g_sleepState.cycle_stats.os_overhead.count = 0;
  }
  else
  {
    WBCount = g_sleepState.cycle_stats.os_overhead.count;
  }
  
  /* Update time in power collapse if tracking is enabled. This must be done after 
   * setting the wakeup time at the point of sleep code execution after PC. */
  sleepStats_updatePCTime();

  /* Sleep Exit STM */
  sleepLog_QDSSPrintf(SLEEP_LOG_LEVEL_PROFILING, 
                      SLEEP_EXIT_STM_NUM_ARGS,
                      SLEEP_EXIT_STM_STR, 
                      SLEEP_EXIT_STM);

  /* Actual sleep exit STM time */ 
  g_sleepState.cycle_stats.sleep_exit_stm = CoreTimetick_Get64();
  
  /* Exit STM and perform any final sleep cleanup */
  sleepOS_completeSleep(TRUE);
    
  sleepLog_QDSSPrintf(SLEEP_LOG_LEVEL_PROFILING, 
                      SLEEP_EXIT_IDLE_NUM_ARGS, 
                      SLEEP_EXIT_IDLE_STR, 
                      SLEEP_EXIT_IDLE,
                      ULOG64_DATA(g_sleepState.cycle_stats.sleep_exit_stm));
  
  return;
}

/*==============================================================================
                       EXTERNAL FUNCTION DEFINITIONS
 =============================================================================*/
/*
 * sleepOS_completeSleep
 */
void sleepOS_completeSleep(boolean exitStm)
{
  /* We are about to exit from Sleep context - set flag to false */
  g_sleepState.processor_in_stm = FALSE;

  /* Exit STM
   * All statistical data must be filled in prior to exiting STM or a race
   * condition will be created between processing in the sleep task and the
   * PMI exit handler.
   * In certain cases (like island exit) we want to perform everything EXCEPT actually
   * exiting STM, so check the given parameter */ 
  if(TRUE == exitStm)
  {
     qurt_power_exit();
  }
  else
  {
     sleepLog_printf(SLEEP_LOG_LEVEL_INFO, 0, " STM EXIT BYPASS");
  }
  
  if(NULL != g_sleepHandles.sleepInStmHandle)
  {
    /* Allow NPA to trigger Event callbacks */
    npa_complete_request(g_sleepHandles.sleepInStmHandle);
  }

  sleepTarget_enableWatchdog();

  return;
}

/*
 * sleepOS_prepareForSleep
 */
uint64 sleepOS_prepareForSleep(sleepOS_IdleModeType idleModeCfg)
{
  uint64 sleepStart;

  /* Wait for all other HW threads to go idle. If the override setting is 
   * disabled, this function will return and the system will already be in
   * STM. */
  if(WAIT_FOR_IDLE_FORCED_EXIT == sleepOS_waitForIdle())
  {
    sleepLog_printf(SLEEP_LOG_LEVEL_DEBUG, 0,
                    "Sleep preparation function exiting "
                    "(Reason: Forced idle exit requested)");

    /* An exit was explicitly requested from the wait for idle call.  When kernel
     * returns, we will not be in STM in this case */
    return 0;
  }

  /* Mark start of this sleep cycle */
  sleepStart = CoreTimetick_Get64();
  sleepLog_QDSSPrintf(SLEEP_LOG_LEVEL_PROFILING, SLEEP_ENTER_IDLE_NUM_ARGS,
                      SLEEP_ENTER_IDLE_STR, 
                      SLEEP_ENTER_IDLE,
                      (uint32)idleModeCfg);

  /* Ensure that sleep mode function has not changed */
  if(FALSE == sleepOS_verifyIdleModeConfig(idleModeCfg))
  {
    sleepLog_QDSSEvent(SLEEP_EARLY_EXIT_STM_NUM_ARGS,
                       SLEEP_EARLY_EXIT_STM);

    sleepLog_printf(SLEEP_LOG_LEVEL_DEBUG, 0,
                    "Sleep cycle skipped "
                    "(Reason: Idle Plugin state changed)");

    sleepStart = 0;
    qurt_power_exit();
  }
  else
  {
    /* Set in stm state */
    g_sleepState.processor_in_stm = TRUE;

    if(NULL != g_sleepHandles.sleepInStmHandle)
    {
      /* Prevent NPA from triggering Event Callbacks */
      npa_issue_required_request(g_sleepHandles.sleepInStmHandle, 1);
    }

    sleepTarget_disableWatchdog();
  }

  return sleepStart;
}

/* 
 * sleepOS_setFrequency 
 */
uint32 sleepOS_setFrequency(void)
{
  uint32  cpuFreqHz;
  uint32  cpuFreqKhz;
  bool    bRequired = TRUE;

  CORE_VERIFY_PTR(g_sleepHandles.dalClkHandle);

  CORE_DAL_VERIFY(DalClock_SetCPUMaxFrequencyAtCurrentVoltage(
                   g_sleepHandles.dalClkHandle,
                   bRequired,
                   &cpuFreqHz) );

  cpuFreqKhz = cpuFreqHz / 1000;
  
  sleepLog_printf(SLEEP_LOG_LEVEL_INFO, 1, 
                  "Sleep CPU frequency set (%u Khz)", cpuFreqKhz);

  return cpuFreqKhz;
}

/*
 * sleepOS_unsetFrequency 
 */
void sleepOS_unsetFrequency(void)
{
  uint32  cpuFreqHz;
  bool    bRequired = FALSE;

  CORE_DAL_VERIFY(DalClock_SetCPUMaxFrequencyAtCurrentVoltage(
                   g_sleepHandles.dalClkHandle,
                   bRequired,
                   &cpuFreqHz) );

  return;
}

/*
 * sleepOS_getFrequency
 */
uint32 sleepOS_getFrequency(void)
{
  /* Initialize to a base frequency, just in case this routine
   * is invoked before a query handle to "/clk/cpu" is created */
  uint32           cpuFreqKHz = 115200;
  npa_query_type   result;
  npa_query_status status;
  
  status = npa_query( g_sleepHandles.clkCpuQueryHandle, 
                      NPA_QUERY_CURRENT_STATE, &result );
                      
  if ( status == NPA_QUERY_SUCCESS )
  {
    cpuFreqKHz = result.data.state;
    CORE_VERIFY( cpuFreqKHz );
  }

  return cpuFreqKHz;
}

/*
 * sleepOS_PMIPerformer
 */
void sleepOS_PMIPerformer(void)
{
  /* Calling PMI handler */
  sleepOS_performLPMExit();
  return;
}

/*
 * sleepOS_getLastTimerDeadline
 */
uint64 sleepOS_getLastTimerDeadline(void)
{
  return ( g_sleepState.solver_input->hard_deadlines.normal_timer );
}

/*
 * sleepOS_offsetSleepDuration
 */
void sleepOS_offsetSleepDuration(uint64 offset)
{
  /* Adjust the sleep duration, so that the new duration gets passed
   * to the rest of the enter functions. */
  if(NULL != g_sleepState.selected_synthLPRM)
  {
    g_sleepState.selected_synthLPRM->wakeup_tick += offset;
  }

  /* Adjust the hard deadline as well, in order to correctly calculate
   * whether we woke up late before exiting sleep. */
  g_sleepState.hard_deadline_copy += offset;

  return;
}

/*
 * sleepOS_getHardDeadline 
 */
uint64 sleepOS_getHardDeadline(void)
{
  return ( g_sleepState.hard_deadline_copy );
}

/*
 * sleepOS_verifyIdleModeConfig
 */
boolean sleepOS_verifyIdleModeConfig(sleepOS_IdleModeType idleMode)
{
  CORE_VERIFY(idleMode < SLEEP_OS_IDLE_MODE_NUM_STATES);
  return (*g_idleEntryPtr == g_sleepIdleEntryTable[idleMode])? TRUE : FALSE;
}

/*
 * sleepOS_configIdleMode
 */
void sleepOS_configIdleMode(sleepOS_IdleModeType newIdleMode)
{
  CORE_VERIFY(newIdleMode < SLEEP_OS_IDLE_MODE_NUM_STATES);
  
  /* Update sleep function pointer */
  g_idleEntryPtr = &g_sleepIdleEntryTable[newIdleMode];

  /* Mode specific action */
  if( SLEEP_OS_IDLE_MODE_OVERRIDE == newIdleMode )
  {
    /* No Sleep task intervention - Kernel performs all wait directly. */
    qurt_power_override_wait_for_idle(TRUE);
  }
  else
  {
    sleepLog_printf(SLEEP_LOG_LEVEL_INFO, 1, 
                    "Setting sleep function (Idle Mode: %d)",
                    newIdleMode);

    /* Sleep task needs to be scheduled. */
    qurt_power_override_wait_for_idle(FALSE);
  }

  return;
}

/*
 * sleepPMI_setHandlerFunctionPTR
 */
void sleepPMI_setHandlerFunctionPTR(sleep_PMI_handler_ptr_type newPMIPtr)
{
  g_PMIFncPtr = newPMIPtr;
  return;
}

/*
 * sleepOS_holdoffNoMode
 */
uint32 sleepOS_holdoffNoMode(void)
{
  /* Due to some holdoff client, we cannot simply perform any low power modes.
   * Simply return. At some point, sleep function pointer would change when all
   * holdoff requests are released. Until then, we will keep coming here. */
  return 0;
}

/*
 * sleepOS_createConfigHandle
 */
CoreConfigHandle sleepOS_createConfigHandle(void)
{
#if 0
  char path[MAX_INI_PATH_LEN];

  /* Build the path to the sleep_config.ini file */
  snprintf(path, MAX_INI_PATH_LEN,
           "/nv/item_files/sleep/core0/sleep_config.ini");

  return(CoreIni_ConfigCreate(path));
#else
  return NULL;
#endif
}

/*
 * sleepOS_destroyConfigHandle
 */
void sleepOS_destroyConfigHandle(CoreConfigHandle config)
{
  /*CoreIni_ConfigDestroy(config);*/
  return;
}

/*
 * sleepOS_readEFSConfig 
 */
void sleepOS_readEFSConfig(void)
{
#if 0
  boolean       sleep_config_value  = FALSE;
  unsigned int  ret                 = FALSE;

  /* Check to see if we should do any LPRMs at all. */
  ret = sleepConfig_readBool((char *)"all_lprms", 
                             NULL,
                             (char *)"disable", 
                             &sleep_config_value );

  if(ret)
  {
    g_sleepAllowLowPowerModes = !sleep_config_value;
  }

  if(g_sleepAllowLowPowerModes == FALSE)
  {
    sleepLog_printf(SLEEP_LOG_LEVEL_WARNING, 0,
                    "WARNING (message: \"All sleep modes are disabled"
                    " in the global config\")" );
  }
#endif

  return;
}

/*
 * sleepOS_performLPM
 */ 
uint32 sleepOS_performLPM(void)
{
  boolean sleepModeEntered;
  void    *context = (void *)(SLEEP_OS_IDLE_MODE_DEFAULT);

  sleepModeEntered = sleepOS_performLPMEnter(context);

  /* Check if we need to execute exit path from here. It might already 
   * have been executed from other context.
   *
   * @Note
   * We are relying on a fact that when we come out of low power mode after
   * idle solver based Sleep, only one HW thread is running any SW. For modes,
   * that trigger PMI from SPM, exit path must be executed from IST context.
   * This is currently ensured by QuRT. If it changes, we will have to insert
   * additional check so that we don't execute exit path from here if we
   * had entered in to any mode with PMI.
   */
  if(TRUE == g_sleepState.execute_sleep_exit_path)
  {
    sleepOS_performLPMExit();
  }

  if(TRUE == sleepModeEntered)
  {
    /* Log and update any statistic data in sleep task context, but only if
     * a low power mode was actually entered. */
    sleepStats_logWakeup(&g_sleepState.cycle_stats);
  }

  return 0;
}

/*
 * sleepOS_isProcessorInSTM
 */
uint32 sleepOS_isProcessorInSTM(void)
{
  return (TRUE == g_sleepState.processor_in_stm ? 1 : 0);
}

/**
 * sleepOS_taskInit
 * 
 * @brief RCInit function that will create the main sleep task and initilize 
 *        all of the sleep data structures 
 */
void sleepOS_taskInit(void)
{
  qurt_thread_t       sleepHandlerThread;
  qurt_thread_attr_t  sleepHandlerAttr;
  uint32              locateInIsland = 0;

#ifdef USLEEP_ISLAND_MODE_ENABLE
  locateInIsland = 1;
#endif

  /* Initialize the sleep subsystem */
  sleepOS_qurtInit();

  /* Initialize main sleep thread which needs to be located in the island
   * section */ 
  qurt_thread_attr_init(&sleepHandlerAttr);

  /* setting up attributes for the sleep thread */
  qurt_thread_attr_set_name(&sleepHandlerAttr, "sleep");
  qurt_thread_attr_set_tcb_partition(&sleepHandlerAttr, locateInIsland); /* locate in uImage */
  qurt_thread_attr_set_priority(&sleepHandlerAttr, SLEEP_TASK_PRI);

  /* Stack memory has to be statically allocated due to island section location requirement */
  qurt_thread_attr_set_stack_size(&sleepHandlerAttr, SLEEP_STACK_SIZE);
  qurt_thread_attr_set_stack_addr(&sleepHandlerAttr, (void *)g_sleepTaskStack);
  
  /* Fill in the stack with a marker to try and find overflows */
  memset(g_sleepTaskStack, 0xF8, sizeof(uint8) * SLEEP_STACK_SIZE);

  /* Create the main sleep task in island section memory */
  CORE_VERIFY(QURT_EOK == qurt_thread_create(&sleepHandlerThread, &sleepHandlerAttr,
                                             sleepOS_mainTask, NULL));

  return;
}

