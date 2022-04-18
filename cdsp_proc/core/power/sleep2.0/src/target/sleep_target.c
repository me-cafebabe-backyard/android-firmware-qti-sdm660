/*==============================================================================
  FILE:         sleep_target.c

  OVERVIEW:     This file provides target-specific functionality for the
                subsystem.

  DEPENDENCIES: None

                Copyright (c) 2011-2016 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/sleep2.0/src/target/sleep_target.c#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include <stdint.h>
#include "comdef.h"
#include "sleep_target.h"
#include "timer.h"
#include "CoreTime.h"
#include "CoreVerify.h"
#include "sleep_log.h"
#include "com_dtypes.h"
#include "npa_resource.h"
#include "sleep_lpri.h"
#include "atomic_ops.h"
#include "DDIInterruptController.h"
#include "DALDeviceId.h"
#include "DALStdErr.h"
#include "sleepi.h"
#include "vmpm.h"
#include "synthTypes.h"
#include "synthLPR.h"
#include "synthLPI.h"
#include "sleep_stats_global.h"
#include "sleep_npa_scheduler.h"
#include "sleep_statsi.h"
#include "spm.h"
#include "q6_lpm_config.h"
#include "sleep_solveri.h"
#include "sleepActivei.h"
#include "sleepActive.h"
#include "sleep_os.h"
#include "sleep_osi.h"
#include "sleep_npa.h"
#include "rpm_messageram.h"

#ifdef USLEEP_ISLAND_MODE_ENABLE
#include "utimer.h"
#endif

#ifdef CDSP_BUILD
#include "vmpm_utils.h"
#include "vmpm_types.h"
#include "CoreIntrinsics.h"
#endif

/*==============================================================================
                             INTERNAL DEFINITIONS
 =============================================================================*/
/* Interrupt vector value for the wakeup trigger from RPM */
#ifdef CDSP_BUILD
#define RPM_WAKEUP_INTERRUPT_VALUE 40
#else
#define RPM_WAKEUP_INTERRUPT_VALUE 30	
#endif

/*==============================================================================
                               GLOBAL VARIABLES
 =============================================================================*/
/*
 * Sleep Target configuration parameters
 * target-specific TCM size defined by cust_config.xml
 */
sleep_target_config g_sleepTargetConfig = 
{
  .chip_family    = DALCHIPINFO_FAMILY_UNKNOWN,
  .chip_ver       = 0,
  .l2_mask        = 0xFFFF,
  .tcm_mask       = 0x0000,
};

/* Variable for indication of entry to RPM assisted modes */
static boolean g_synthLPRMisRPMAssisted = FALSE;

/* Dependencies to wait on before registering any LPRs. */
static const char *g_LPRDependencies[] =
{
  SLEEP_LPR_NODE_NAME
};

/* Dal data struct to hold DAL Interrupt Controller Handle */
static DalDeviceHandle *g_DALInterruptCtrlHndl;

/* Handle to the DAL "WakeupTimer" timetick driver, for calculating the
 * wakeup tick during sleep. This timer is used by the DAL and timer services
 * to provide "sleep time". */
static DalDeviceHandle *g_DALWakeTimerHandle;

/* SPM handle */
static spm_handle g_sleepSPMHandle[1] = {0};

/* Handle used to sync the AON timer to the global MPM timer */
static DalDeviceHandle *g_DALTimerSyncHandle;

/*==============================================================================
                           EXTERNAL REFERENCES
 =============================================================================*/
/* deferrable timer groups */
extern timer_group_type timer_null_group;

/* target-specific nodes that are implemented & initialized in this module */
extern sleep_synth_lpr SleepLPR_synth;
extern sleep_synth_lpi SleepLPI_synth;

extern npa_node_definition sleep_cpu_vdd_node;
extern npa_node_definition sleep_rpm_sync_node;
extern npa_node_definition sleep_l2cache_node;

/*==============================================================================
                                  MACROS
 =============================================================================*/
#define SPM_HANDLE_REFERENCE  g_sleepSPMHandle[0]

/*==============================================================================
                           FORWARD DECLARATIONS
 =============================================================================*/
void sleepTarget_wakeupHandler(uint32 param);
void sleepTarget_RPMWakeupHandler(uint32 param);

static uint64 sleepTarget_enableWakeupTimer(uint64 wakeupTick);
static void sleepTarget_disableWakeupTimer(void);
static void sleepTarget_initSPM(void);

/*==============================================================================
                          INTERNAL FUNCTION DECLARATIONS
 =============================================================================*/
/** 
 * sleepTarget_registerLPRs 
 *  
 * @brief  Register the LPRs & nodes that are owned by sleep.
*/
static void sleepTarget_registerLPRs( void         *context,
                                      unsigned int  event_type,
                                      void         *data,
                                      unsigned int  data_size )
{
  npa_resource_state  initialStateEnable  = SLEEP_LPR_ENABLE_ALL;
  npa_client_handle   cpuWakeupSyncClient = NULL;
  npa_client_handle   cpuConfigSyncClient = NULL;
  npa_client_handle   qtmrSyncClient      = NULL;

  /* Register NPA nodes that this module currently owns. */
  npa_define_node(&sleep_cpu_vdd_node,  &initialStateEnable, NULL);
  npa_define_node(&sleep_rpm_sync_node, &initialStateEnable, NULL);
  npa_define_node(&sleep_l2cache_node,  &initialStateEnable, NULL);

  /* Register cpu wakeup lpr */
  CORE_VERIFY_PTR(cpuWakeupSyncClient =
                  npa_create_sync_client(SLEEP_LPR_NODE_NAME,
                                         "/core/cpu/wakeup",
                                         NPA_CLIENT_REQUIRED));

  sleepLPR_define("cpu_wakeup", cpuWakeupSyncClient);
  npa_issue_required_request(cpuWakeupSyncClient, SLEEP_ALL_LPRMS);

  /* Register cpu config lpr */
  CORE_VERIFY_PTR(cpuConfigSyncClient =
                  npa_create_sync_client(SLEEP_LPR_NODE_NAME,
                                         "/core/cpu/power_config",
                                         NPA_CLIENT_REQUIRED));

  sleepLPR_define("cpu_power_config", cpuConfigSyncClient);
  npa_issue_required_request(cpuConfigSyncClient, SLEEP_ALL_LPRMS);

  /* Register qtmr lpr */
  CORE_VERIFY_PTR(qtmrSyncClient =
                  npa_create_sync_client(SLEEP_LPR_NODE_NAME,
                                         "qtmr", 
                                         NPA_CLIENT_REQUIRED));

  sleepLPR_define( "qtmr", qtmrSyncClient );
  npa_issue_required_request(qtmrSyncClient, SLEEP_ALL_LPRMS);

  return;
}

/*==============================================================================
                          EXTERNAL FUNCTION DECLARATIONS
 =============================================================================*/
/**
 * sleepTarget_initialize
 */
void sleepTarget_initialize(void)
{
  uint32  timerIntN;
  uint32  islandMode  = 0;

#ifdef USLEEP_ISLAND_MODE_ENABLE
  islandMode = 1;
#endif

  /* Register a callback for when the necessary dependencies are available,
   * in order to register the nodes and LPRs that sleep owns. */
  npa_resources_available_cb( NPA_ARRAY( g_LPRDependencies ),
                              sleepTarget_registerLPRs, NULL );

  /* set below groups as deferrable */
  timer_group_set_deferrable( &timer_null_group, TRUE );

  /* use qtimer frame that is available on all other targets */
  DalTimetick_Attach( "WakeUpTimer", &g_DALWakeTimerHandle );
  CORE_VERIFY_PTR( g_DALWakeTimerHandle );

  DalTimetick_GetInterruptVectorNum(g_DALWakeTimerHandle, &timerIntN);

  /* Attaching to interrupt controller and registering interrupt handlers */
  CORE_VERIFY( DAL_DeviceAttach( DALDEVICEID_INTERRUPTCONTROLLER,
                                 &g_DALInterruptCtrlHndl ) == DAL_SUCCESS );

  CORE_VERIFY(DAL_SUCCESS == DalInterruptController_RegisterISR(
                              g_DALInterruptCtrlHndl,
                              timerIntN,
                              (DALIRQ)sleepTarget_wakeupHandler,
                              (const DALIRQCtx) 0,
                              DALINTRCTRL_ENABLE_CONFIG_EX(DALINTRCTRL_ENABLE_LEVEL_HIGH_TRIGGER,
                                                           0, islandMode)));

  CORE_VERIFY(DAL_SUCCESS == DalInterruptController_RegisterISR(
                              g_DALInterruptCtrlHndl,
                              RPM_WAKEUP_INTERRUPT_VALUE,
                              (DALIRQ)sleepTarget_RPMWakeupHandler,
                              (const DALIRQCtx) 0,
                              DALINTRCTRL_ENABLE_CONFIG_EX(DALINTRCTRL_ENABLE_RISING_EDGE_TRIGGER,
                                                           0, 0)));

  /* Initialize sleep NPA scheduler */
  sleepNPAScheduler_init();

  /* Get the timer sync handle */
  DalTimetick_Attach("SystemTimer", &g_DALTimerSyncHandle);
  CORE_VERIFY_PTR(g_DALTimerSyncHandle);

  /* Init the SPM driver system */
  sleepTarget_initSPM();

  return;
}

/**
 * sleepTarget_getCPUArchitecture
 */
void sleepTarget_getCPUArchitecture(DalChipInfoFamilyType   *chipFamily,
                                    DalChipInfoVersionType  *chipVer)
{
  static uint32 init = 0;

  if(init == 0)
  {
    DalDeviceHandle *hChipInfo;

    /* Get global chip architecture  */
    if( DAL_DeviceAttach(DALDEVICEID_CHIPINFO, &hChipInfo) == DAL_SUCCESS )
    {
      DalDevice_Open(hChipInfo, DAL_OPEN_SHARED);
      DalChipInfo_GetChipFamily(hChipInfo, &g_sleepTargetConfig.chip_family);
      DalChipInfo_GetChipVersion(hChipInfo, &g_sleepTargetConfig.chip_ver);
      DalDevice_Close(hChipInfo);
      init = 1;
    }
  }

  if(chipFamily != NULL)
    *chipFamily = g_sleepTargetConfig.chip_family;

  if(chipVer != NULL)
    *chipVer    = g_sleepTargetConfig.chip_ver;

  return;
}

/*
 * sleepTarget_initializeLPR
 */
void sleepTarget_initializeLPR(void)
{
  /* Register the pre-synthesized LPRMs here.  This must be done
   * before any of the component LPRMs are registered, so we do
   * it when the /sleep/lpr node is being initialized. */
  synthLPR_define( &SleepLPR_synth );
#ifdef USLEEP_ISLAND_MODE_ENABLE
  synthLPI_define( &SleepLPI_synth );
#endif

  return;
}

/*
 * sleepTarget_enableSleepTimer 
 */
uint64 sleepTarget_enableSleepTimer(uint64 wakeupTick)
{
  uint64 matchTick;
  uint64 now;

  /* Ensure that wakeup_tick is in the future */
  if(CoreTimetick_Get64() >= wakeupTick)
  {
    sleepLog_printf(SLEEP_LOG_LEVEL_INFO, 0,
                    " Wakeup time already in past, skipping programming");

    /* Signal ATS to pickup the latest duration since the current one is expired already */
    sleepActive_SetSignal(SLEEP_SIGNAL_HARD_DURATION);
    return wakeupTick;
  }

  now = CoreTimetick_Get64();

  /* Setting up a new match value */
  DalTimetick_SetNextInterrupt64(g_DALWakeTimerHandle,
                                 wakeupTick,
                                 now, &matchTick);

  /* Re-enable wakeup timer interrupt */
  CORE_VERIFY(DalTimetick_Enable(g_DALWakeTimerHandle, 1) == DAL_SUCCESS);

  sleepLog_printf(SLEEP_LOG_LEVEL_INFO, (1*2),
                  " Program QTMR (match tick: 0x%llx)",
                  ULOG64_DATA(matchTick) );

  return matchTick;
}

/*
 * sleepTarget_disableSleepTimer
 */
void sleepTarget_disableSleepTimer( void )
{
    /* Disables wakeup timer interrupt */
    CORE_VERIFY(DalTimetick_Enable(g_DALWakeTimerHandle, 0) == DAL_SUCCESS);

  return;
}

/*
 * sleepTarget_enableWatchdog 
 */
void sleepTarget_enableWatchdog(void)
{
  return;
}

/*
 * sleepTarget_disableWatchdog 
 */
void sleepTarget_disableWatchdog(void)
{
  return;
}

/*
 * sleepTarget_setRPMAssistedMode
 */
void sleepTarget_setRPMAssistedMode( boolean value )
{
  g_synthLPRMisRPMAssisted = value;
  return;
}

/*
 * sleepTarget_getRPMAssistedMode
 */
boolean sleepTarget_getRPMAssistedMode( void )
{
  return(g_synthLPRMisRPMAssisted);
}

/*
 * sleepTarget_getRPMStatisticsAddress
 */
void *sleepTarget_getRPMStatisticsAddress(void)
{
  return(rpm_message_ram_master_stats(VMPM_MASTER));
}

/*
 * sleepTarget_getHardWakeupTime
 */
void sleepTarget_getHardWakeupTime(sleep_solver_deadlines *deadlines)
{
  uint64 npaDeadline;
  
  /* Retrieve the time (in ticks) of the next normal mode scheduled timer expiry. */
  deadlines->normal_timer = (uint64)timer_get_first_non_deferrable_timer_expiry();
  
  /* Retreive the NPA deadline */
  npaDeadline = sleepNPAScheduler_getDeadline();

  /* Retrieve the island mode deadline */
#ifdef USLEEP_ISLAND_MODE_ENABLE
  deadlines->island_timer = (uint64)utimer_get_first_non_deferrable_timer_expiry();
#else
  deadlines->island_timer = -1;
#endif

  sleepLog_printf(SLEEP_LOG_LEVEL_DEBUG, 2*3,
                  "Hard deadlines (Normal Timer: 0x%llx) "
                  "(Island Timer: 0x%llx) "
                  "(NPA Scheduler: 0x%llx)",
                  ULOG64_DATA(deadlines->normal_timer),
                  ULOG64_DATA(deadlines->island_timer),
                  ULOG64_DATA(npaDeadline) );

  /* Set first normal mode timer to expire */
  deadlines->normal_min = MIN(deadlines->normal_timer, npaDeadline);

  /* Set the earliest wakeup time of all timers */
  deadlines->overall_min = MIN(deadlines->island_timer, deadlines->normal_min);

  return;
}

/*
 * sleepTarget_performInitialLPRExit
 */
void sleepTarget_performInitialLPRExit(void)
{
#ifdef CDSP_BUILD
  /* For CDSP, syncing local timers to the global is not required after coming out PC. 
   * Hence, this function is empty for CDSP.
  */ 
  return;
#else  // For ADSP 
  /* When comming out of XO power collapse, sync the local timers to the global 
   * as soon as possible and before getting any current time stamps. */
  if(TRUE == sleepTarget_getRPMAssistedMode())
  {
    CORE_DAL_VERIFY(DalTimetick_SyncSSCTimer(g_DALTimerSyncHandle));
  }

  return;
#endif  
}

/*
 * sleepTarget_initSPM
 */
static void sleepTarget_initSPM(void)
{
  /* Initialize SPM driver */
  spm_driver_init();

  /* Get handle to [only] spm */
  CORE_VERIFY(1 == spm_driver_get_handles(SPM_DEFAULT_INSTANCE_NAME, 
                                          1, g_sleepSPMHandle));

  /* Initialize & enable the SPM module */
  spm_instance_init(SPM_HANDLE_REFERENCE);
  spm_instance_enable(SPM_HANDLE_REFERENCE, TRUE);
  return;
}

/*
 * sleepTarget_setRpmHandshake
 */
spm_result_t sleepTarget_setRpmHandshake(boolean performHandshake)
{
  /* Set internal state to requested setting */
  sleepTarget_setRPMAssistedMode(performHandshake);
  return(spm_instance_set_rpm_handshake(SPM_HANDLE_REFERENCE, performHandshake));
}

/*
 * sleepTarget_setSpmLowPowerMode
 */
spm_result_t sleepTarget_setSpmLowPowerMode(spm_low_power_mode_type coreMode)
{
  return(spm_instance_set_lpm(SPM_HANDLE_REFERENCE, (uint8)coreMode));
}

/*
 * sleepTarget_isInterruptPending
 */
boolean sleepTarget_isInterruptPending(uint32 intNumber)
{
  uint32 state = 0; 

  DalInterruptController_IsInterruptPending(g_DALInterruptCtrlHndl, intNumber, &state);
  return (0 != state) ? TRUE : FALSE;
}

/*
 * sleepTarget_setDefaultPowerMode
 */
void sleepTarget_setDefaultPowerMode(boolean enable)
{
  sleep_solver_output *solverOutput = sleepActive_GetSolverOutput();

  if(TRUE == enable)
  {
    /* Enable clock gating mode as the default.  If this changes, clock gating will need
     * to be added back to the cpu_vdd LPR */
    q6LPMConfig_setupModeConfig(SPM_MODE_CLK_GATE, TRUE);

    /* Enable kernel override directly to enter the default mode immediately at idle */
    sleepOS_configIdleMode(SLEEP_OS_IDLE_MODE_OVERRIDE);
  }
  else if(NULL != solverOutput->selected_synthLPRM)
  {
    /* Unconfigure clock gating mode which effectivly enables the currently selected and configured
     * low power mode. Note that the currently selected mode will never be clock gating
     * itself. */
    q6LPMConfig_setupModeConfig(SPM_MODE_CLK_GATE, FALSE);

    /* Allow ATS to correctly configure the sleep task for the current power mode. */
    sleepActive_configureIdleMode(solverOutput->selected_synthLPRM);
  }

  return;
}

#ifdef CDSP_BUILD
/* GPIO interrupt controller driver is not supported in CDSP. Hence, virtual MPM driver
 * is also disabled. So, the function which writes wakeup time in RPM message RAM has
 * been moved here for CDSP.
 * 
 * vmpm_SetWakeupTimetick
 */
void vmpm_SetWakeupTimetick(uint64_t wakeupTick)
{
  volatile vmpm_data_t *g_messageRamBase = 0;
  
  g_messageRamBase = rpm_message_ram_vmpm(VMPM_MASTER);
  g_messageRamBase->wakeup_time = wakeupTick;

  return;
}
#endif
