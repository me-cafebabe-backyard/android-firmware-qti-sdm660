/*==============================================================================
  FILE:         uSleep_target.c

  OVERVIEW:     This file provides uSleep target specfic functions while in
                normal operational mode

  DEPENDENCIES: Object file generated from source is marked as island section
  
                Copyright (c) 2014-2017 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/uSleep/src/target/ddr/uSleep_target.c#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include "DALStdDef.h"
#include "CoreVerify.h"
#include "uSleep.h"
#include "uSleep_os.h"
#include "sleep_pmi.h"
#include "vmpm_utils.h"
#include "uSleep_ddr_log.h"
#include "uSleep_target.h"
#include "DDITimetick.h"
#include "npa.h"
#include "pmapp_npa.h"
#include "uSleep_HALhwio.h"
#include "uSleep_hwio.h"

/*==============================================================================
                               GLOBAL VARIABLES
 =============================================================================*/
/* DAL handle for time tick driver to sync the SSC AON QTimer with global
 * QTimer. This is SSC specific requirement whenever we wakeup from
 * xo shutdown or exit from island mode. */
static DalDeviceHandle *g_uSleepTimerSyncHandle;

/* NPA client to CX rail to support debugging in island mode */
static npa_client_handle g_uSleepCXRailClient = NULL;

/* NPA dependencies for target specific needs */
static const char *g_uSleepTargetDependencies[] =
{
  PMIC_NPA_GROUP_ID_RAIL_CX
};

/* If TRUE, allows island debugging by keeping the JTAG port active. */
static volatile boolean g_usleepEnableIslandDebug = FALSE;

/*==============================================================================
                       INTERNAL FUNCTION DEFINITIONS
 =============================================================================*/
/**
 * uSleepTarget_registerCB
 * 
 * @brief Creates a client to the CX rail to ensure it's enabled for
 *        island debug
 * 
 * @param see npa_callback defintion for function parameters
 */
static void uSleepTarget_registerCB(void         *context,
                                    unsigned int  eventType,
                                    void         *data,
                                    unsigned int  dataSize)
{
  /* Create client to CX rail to support debugging in island mode */
  CORE_VERIFY_PTR(g_uSleepCXRailClient = 
                  npa_create_sync_client(PMIC_NPA_GROUP_ID_RAIL_CX,
                                         "uSleep/CXRail", 
                                         NPA_CLIENT_REQUIRED));

  return;
}

/*==============================================================================
                       EXTERNAL FUNCTION DEFINITIONS
 =============================================================================*/
/*
 * uSleepTarget_transitionNotificationCB
 */
void uSleepTarget_transitionNotificationCB(uSleep_state_notification state)
{
  if(USLEEP_STATE_EXIT == state)
  {
     uSleepDDRLog_printf(USLEEP_DDR_LOG_LEVEL_TRANSITION, 0,
                         "Syncing SSC QTimer");

    /* Syncing local AON Qtimer with global Qtimer. */
    CORE_DAL_VERIFY(DalTimetick_SyncSSCTimer(g_uSleepTimerSyncHandle));
  }
  else
  {
    /* Clear any stale RPM wakeup time data on entry */
    vmpm_SetWakeupTimetick(0);
  }

  return;
}

/*
 * uSleepTarget_setPMIHandler
 */
void uSleepTarget_setPMIHandler(void)
{
  /* Use main sleep's API to set the PMI function pointer */
  sleepPMI_setHandlerFunctionPTR(uSleepOS_PMIPerformer);
  return;
}

/*
 * uSleepTarget_initialize
 */
void uSleepTarget_initialize(void)
{
  /* Obtain a DAL handle to time tick driver to sync local qtimer with global
   * one. */
  DalTimetick_Attach("SystemTimer", &g_uSleepTimerSyncHandle);
  CORE_VERIFY_PTR(g_uSleepTimerSyncHandle);

  npa_resources_available_cb(NPA_ARRAY(g_uSleepTargetDependencies),
                             uSleepTarget_registerCB, NULL);

  /* Registration for the standalone wakeup timer is done as part of the normal
   * sleep init.  It would be done here otherwise. */

  return;
}

/*
 * uSleepTarget_enableIslandDebug
 */
void uSleepTarget_enableIslandDebug(boolean enable)
{
  static boolean allowed = FALSE;

  //if(NULL != g_uSleepCXRailClient)
  //{
    if((TRUE == g_usleepEnableIslandDebug) && (TRUE == enable))
    {
      allowed = TRUE;

      /* CX rail must be on for island debug */
      //npa_issue_required_request(g_uSleepCXRailClient, PMIC_NPA_MODE_ID_CORE_RAIL_LOW_MINUS);
     
      /* Clear bus clamping bit to enable the JTAG port in island mode.
       * If bits are ever 0, vdd_cx MUST be on, when the entry sequence is executed
       * or it could damage the SoC */
      HWIO_OUT(LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP,
               HWIO_FVAL(LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP, AXIM_CLAMP_E_CLEAR, 1)   |
               HWIO_FVAL(LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP, AXIM_CLAMP_E_SET,   0)   |
               HWIO_FVAL(LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP, AXIM_CLAMP_L_CLEAR, 1)   |
               HWIO_FVAL(LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP, AXIM_CLAMP_L_SET,   0));
      
      /* Do not isolate the CNOC AHB slave to SSC in island mode.*/
      HWIO_OUTF(LPASS_SCSR_IEC_CTL, ISO_AHB_SLAVE_BYPASS, 1);
    }
    else if(TRUE == allowed)
    {
      allowed = FALSE;

      //npa_complete_request(g_uSleepCXRailClient);

      HWIO_OUT(LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP,
         HWIO_FVAL(LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP, AXIM_CLAMP_E_CLEAR, 1)   |
         HWIO_FVAL(LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP, AXIM_CLAMP_E_SET,   1)   |
         HWIO_FVAL(LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP, AXIM_CLAMP_L_CLEAR, 1)   |
         HWIO_FVAL(LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP, AXIM_CLAMP_L_SET,   1));

      HWIO_OUTF(LPASS_SCSR_IEC_CTL, ISO_AHB_SLAVE_BYPASS, 0);
    }
  //}

  return;
}

