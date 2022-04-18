/*=============================================================================
  @file pdf_avs.cpp

  This file contains AVS MDF PDR handling

 *******************************************************************************
 * Copyright (c) 2017 Qualcomm Technologies, Inc.  All Rights Reserved
 * Qualcomm Technologies Confidential and Proprietary.
 ********************************************************************************/


/*============================================================================
  EDIT HISTORY FOR FILE

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------
 08/29/2017   MK   File Creation
============================================================================*/

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/

#include "pdr_ssr_avs.h"
#include "pdr_avs.h"
#include "servreg_monitor.h"
#include "servreg_monitor_qurt.h"
#include "servreg_locator.h"
#include "servreg_locator_qurt.h"
#include "qurt.h"
#include "adsp_core_api.h"


/*----------------------------------------------------------------------------
 *  Variables
 * -------------------------------------------------------------------------*/

#ifndef SIM
qurt_anysignal_t servreg_locator_avail_signal;
bool_t is_pdr_fwk_available = FALSE;
qurt_elite_thread_t       avs_pdr_thread_id;
/* AP PDR Service Thread Name */
static char AVS_PDR_SVC_THREAD_NAME[]               =  "AVS_PDR";

/* AP PDR Service Thread Stack size */
static const uint32_t AP_PDR_SVC_THREAD_STACK_SIZE = (2 * 1024);

#define SERVREG_LOCATOR_STATUS_MASK 0x1
#define AUDIO_MAX_SERVREG_CHAR_LENGTH 16

qurt_anysignal_t servreg_pdr_avs_status_signal;
/* AVS MDF service status signal mask */
#define MDSP_AVS_MDF_SERVICE_STATUS_MASK 0x1
#define SDSP_AVS_MDF_SERVICE_STATUS_MASK 0x2

#define AVS_MDF_PDR_INFO_NUM_ROWS 2

typedef struct avs_mdf_pdr_info_t
{
  uint32_t proc_id;
  SERVREG_DL_HANDLE remote_avs_mdf_mon_handle;
  uint32_t sig_mask;

}avs_mdf_pdr_info_t;

SERVREG_DL_HANDLE mdsp_avs_mdf_mon_handle;
SERVREG_DL_HANDLE sdsp_avs_mdf_mon_handle;

avs_mdf_pdr_info_t avs_mdf_pdr_info[AVS_MDF_PDR_INFO_NUM_ROWS] = {
    {MODEM_DSP_PROC_ID, mdsp_avs_mdf_mon_handle, MDSP_AVS_MDF_SERVICE_STATUS_MASK},
    {SENSOR_DSP_PROC_ID, sdsp_avs_mdf_mon_handle, SDSP_AVS_MDF_SERVICE_STATUS_MASK}
};

uint32_t signal_wait_mask;
#endif //#ifndef SIM

uint32_t pdr_thread_launch_cntr = 0;


//extern qurt_elite_queue_t  *avs_pdr_ssr_rsp_q = NULL;
/*----------------------------------------------------------------------------
 *  Function Implementations
 * -------------------------------------------------------------------------*/
#ifndef SIM
static ADSPResult avs_pdr ( void* param)
{
  ADSPResult result = ADSP_EOK;
  uint32_t signal = 0;
  SERVREG_SERVICE_STATE avs_state;
  uint32_t sig_mask;
  SERVREG_DL_HANDLE remote_avs_mdf_mon_handle = NULL;


  for (;;)
  {
    signal = ( uint32_t )qurt_anysignal_wait(&servreg_pdr_avs_status_signal, signal_wait_mask );

    if(MDSP_AVS_MDF_SERVICE_STATUS_MASK & signal)
    {
      sig_mask = MDSP_AVS_MDF_SERVICE_STATUS_MASK;
      remote_avs_mdf_mon_handle = mdsp_avs_mdf_mon_handle;
    }
    else if (SDSP_AVS_MDF_SERVICE_STATUS_MASK & signal)
    {
      sig_mask = SDSP_AVS_MDF_SERVICE_STATUS_MASK;
      remote_avs_mdf_mon_handle = mdsp_avs_mdf_mon_handle;
    }
    else
    {
      continue;
    }

    MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "avs_pdr():service registry notified Audio PD status");

    qurt_anysignal_clear(&servreg_pdr_avs_status_signal,sig_mask);

    avs_state = servreg_get_service_curr_state(remote_avs_mdf_mon_handle);

    switch (avs_state)
    {
      case SERVREG_SERVICE_STATE_DOWN:
      {
        MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO,
              "avs_pdr: avs_pdr received down AVS state =(0x%08x) ",
              avs_state);

        avs_pdr_ssr_avs_mdf_before_shutdown_handler();
      }
      break;
      case SERVREG_SERVICE_STATE_UP:
      {
        MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "avs_pdr(): received AVS up state =(0x%08x) ",
              avs_state );
      }
      break;
      default:
        MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "avs_pdr(): avs_pdr recieved invalid AVS state =(0x%08x)",
              avs_state );
        break;
    }
  }


  /* ack to service registry on completion on handling the signal */
  SERVREG_RESULT ret;
  uint32_t transaction_id = servreg_get_transaction_id(remote_avs_mdf_mon_handle);
  ret = servreg_set_ack(remote_avs_mdf_mon_handle, transaction_id);
  MSG_1( MSG_SSID_QDSP6, DBG_HIGH_PRIO,"sent ack to servreg with transaction id %d.", transaction_id );
  if(SERVREG_SUCCESS != ret)
  {
    MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "avs_pdr(): %d, servreg_set_ack() failed");
  }
  return result;
}
#endif //SIM avs_pdr()

ADSPResult avs_pdr_monitor_init(uint32_t proc_id)

{
#ifndef SIM
  SERVREG_DL_HANDLE pdr_handle = NULL;
  SERVREG_NAME domain = (SERVREG_NAME)SERVREG_NULL;
  SERVREG_NAME local_soc_scope = (SERVREG_NAME)SERVREG_NULL;
  SERVREG_RESULT result;
  uint32_t i = 0;
  uint32_t idx;
  SERVREG_DL_HANDLE remote_avs_mdf_mon_handle;
  uint32_t sig_mask;


  pdr_handle = servreg_alloc_domainlist_handle();

  if(SERVREG_NULL == pdr_handle)
  {
    MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "avs_pdr_monitor_init(): servreg_alloc_domainlist_handle() failed" );
    return ADSP_EFAILED;
  }

  for(idx = 0; idx < AVS_MDF_PDR_INFO_NUM_ROWS; idx++)
  {
    if(proc_id == avs_mdf_pdr_info[idx].proc_id)
    {
      remote_avs_mdf_mon_handle = avs_mdf_pdr_info[idx].remote_avs_mdf_mon_handle;
      sig_mask = avs_mdf_pdr_info[idx].sig_mask;
      break;
    }
  }

  if(idx == AVS_MDF_PDR_INFO_NUM_ROWS)
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "avs_pdr_monitor_init() Failed to avs_mdf_pdr_info for the proc id %ld", proc_id);
    return ADSP_EUNEXPECTED;
  }

  switch (proc_id)
  {
    case MODEM_DSP_PROC_ID:
    {
	   result = servreg_get_domainlist("audio/avs_mdf_mdsp", pdr_handle);
       break;
    }
    case SENSOR_DSP_PROC_ID:
    {
	   result = servreg_get_domainlist("audio/avs_mdf_sdsp", pdr_handle);
       break;
    }
    default:
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "avs_pdr_monitor_init() invalid proc id %ld", proc_id);
      return ADSP_EUNEXPECTED;
      break;
	}
  }

  if(SERVREG_SUCCESS == result)
  {
    for (i = 0; i < servreg_get_num_entries(pdr_handle); i++)
    {
      result = servreg_get_entry(pdr_handle, (i + 1), &domain);

      if ((SERVREG_SUCCESS != result)|| (SERVREG_NULL == domain))
      {
        MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "avs_pdr_monitor_init(): servreg_get_entry() failed" );
        return ADSP_EFAILED;
      }
    }
  }


    MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "avs_pdr_monitor_init(): found expected domain of AVS MDF service: "
          "AVS MDF soc: %s, AVS domain: %s", local_soc_scope ,domain);

  remote_avs_mdf_mon_handle = servreg_alloc_monitor_handle(domain, avs_mdf_svc_name);

  if(SERVREG_NULL != remote_avs_mdf_mon_handle)
  {
    /* Free the domain list handle once monitor allocation is done */
    if(SERVREG_SUCCESS != servreg_free_domainlist_handle(pdr_handle))
    {
      MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "avs_pdr_monitor_init(): pdr_handle free failed after finding "
          "expected domain" );
      return ADSP_EFAILED;
    }

    result = servreg_register_listener_qurt(remote_avs_mdf_mon_handle, &servreg_pdr_avs_status_signal,
                                            sig_mask);

    if(SERVREG_SUCCESS == result)
    {
      signal_wait_mask |= sig_mask;
      MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "avs_pdr_monitor_init(): AVS MDF Client registration successful with servreg_register_listener_qurt() via QDI to check AVS status" );
    }
    else
    {
      MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "avs_pdr_monitor_init(): AVS MDF Client registration failed with servreg_register_listener_qurt() via QDI to check AVS status" );

      result = servreg_free_monitor_handle(remote_avs_mdf_mon_handle);
      if(SERVREG_SUCCESS != result)
      {
        MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "avs_pdr_monitor_init(): could not free the monitor handle \n" );
      }
      return ADSP_EFAILED;
    }

    /* Have the current status of avs service for debugging purpose */
    SERVREG_SERVICE_STATE avs_state = servreg_get_service_curr_state(remote_avs_mdf_mon_handle);
    MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "avs_pdr_monitor_init(): vs_pdr recieved DOWN CVD state =(0x%08x)", avs_state );

  }
  else
  {
    MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "avs_pdr_monitor_init(): servreg_alloc_monitor_handle failed" );
    result = servreg_free_domainlist_handle( pdr_handle );
    if( SERVREG_SUCCESS != result )
    {
      MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "avs_pdr_monitor_init(): pdr_handle free failed while exiting since servreg_alloc_monitor_handle failed" );
    }
    return ADSP_EFAILED;
  }

  ADSPResult ret = ADSP_EOK;

  /* Launch this thread only one time */
  if(0 == pdr_thread_launch_cntr)
  {
    /* Launch AP PDR thread to monitor status of AVS */
    if (ADSP_FAILED (ret = qurt_elite_thread_launch(&avs_pdr_thread_id,
                                                       AVS_PDR_SVC_THREAD_NAME, \
                                                       NULL, AP_PDR_SVC_THREAD_STACK_SIZE, \
                                                       elite_get_thrd_prio(ELITETHREAD_STAT_DSP_PDR_SVC_PRIO_ID), \
                                                       avs_pdr, NULL, \
                                                       QURT_ELITE_HEAP_DEFAULT)))
    {
      MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "APPDRSvc: Failed to create the AP Thread");
    }
  }
  pdr_thread_launch_cntr++;


#endif //#ifndef SIM

  return ADSP_EOK;
}

ADSPResult avs_pdr_monitor_deinit(uint32_t proc_id)

{
  ADSPResult result = ADSP_EOK;
#ifndef SIM
  uint32_t idx;
  SERVREG_DL_HANDLE remote_avs_mdf_mon_handle;
  uint32_t sig_mask;

  for(idx = 0; idx < AVS_MDF_PDR_INFO_NUM_ROWS; idx++)
  {
    if(proc_id == avs_mdf_pdr_info[idx].proc_id)
    {
      remote_avs_mdf_mon_handle = avs_mdf_pdr_info[idx].remote_avs_mdf_mon_handle;
      sig_mask = avs_mdf_pdr_info[idx].sig_mask;
      break;
    }
  }

  if(idx == AVS_MDF_PDR_INFO_NUM_ROWS)
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "avs_pdr_monitor_init() Failed to avs_mdf_pdr_info for the proc id %ld", proc_id);
    return ADSP_EUNEXPECTED;
  }

  pdr_thread_launch_cntr--;

  if (NULL != remote_avs_mdf_mon_handle)
  {
    /* Unregister for service register PDR signal. */
    SERVREG_RESULT ret;

    ret = servreg_deregister_listener_qurt( remote_avs_mdf_mon_handle, &servreg_pdr_avs_status_signal,
                                            sig_mask );
    if ( SERVREG_SUCCESS != ret )
    {
      MSG_1( MSG_SSID_QDSP6, DBG_ERROR_PRIO,"avs_pdr_monitor_deinit(): servreg_deregister_listener_qurt() failed", ret );
      result = ADSP_EFAILED;
    }

    signal_wait_mask ^= sig_mask;

    result = servreg_free_monitor_handle( remote_avs_mdf_mon_handle );
    if( SERVREG_SUCCESS != result )
    {
      MSG( MSG_SSID_QDSP6, DBG_ERROR_PRIO, "vs_voc_pdr_deinit(): could not free the monitor handle \n" );
    }
  }

  /* join on the last deinit */
  if(0 == pdr_thread_launch_cntr)
  {
    qurt_elite_thread_join(avs_pdr_thread_id, &result);
    qurt_anysignal_destroy(&servreg_locator_avail_signal);
    qurt_anysignal_destroy(&servreg_pdr_avs_status_signal);
  }

#endif //#ifndef SIM
  return result;
}

ADSPResult avs_pdr_pre_init()
{
  ADSPResult ret = ADSP_EOK;
#ifndef SIM
  SERVREG_RESULT result;


  /* Register for service registry PDR signals. */
  qurt_anysignal_init (&servreg_locator_avail_signal);

  //register with service registry. Service registry locator UP notification comes on servreg_locator_avail_signal
  result = servreg_register_servloc_availability_signal_qurt(&servreg_locator_avail_signal,SERVREG_LOCATOR_STATUS_MASK);

  if(SERVREG_SUCCESS != result)
  {
    /* Either service registry locator is not present or there is some issue in service locator */
    MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO," service locator signal registration failed: %d ", result);
    is_pdr_fwk_available = FALSE;
    ret = ADSP_EUNSUPPORTED;
  }
  else
  {
    MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO," service locator signal registration passed: %d ", result);
    is_pdr_fwk_available = TRUE;
    ret = ADSP_EOK;
  }
#endif //SIM
  return ret;

}

ADSPResult avs_pdr_monitor_avs_mdf()
{
  ADSPResult result = ADSP_EOK;
  return result;

}

/**
   This function initializes handler for PD restart of Client DSP

    @return
      ADSPResult Error Code
 */
ADSPResult avs_pdr_init(uint32_t proc_id)
{
  ADSPResult result = ADSP_EOK;
#ifndef SIM
  uint32_t signal_wait_mask = SERVREG_LOCATOR_STATUS_MASK;

  /* Initializing PDR/SSR handling framework*/
  {
    result = avs_pdr_pre_init( );

    if( ADSP_EOK != result )
    {
      MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO,
            " something went wrong in avs_pdr_pre_init.result %d", result );
      return result;
    }

    /* wait for serv registry locator up */
    if(SERVREG_SERVICE_STATE_UP == servreg_get_servloc_availability())
    {
      MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "AP service registry locatory is UP. Can Proceed with PDR registration" );
    }
    else  //wait on a signal till service loc is up and register with PDR if service locator state is UP
    {
      MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "avs_pdr_monitor_avs():waiting on service registry availability signal:(0x%08x)", signal_wait_mask );
      uint32_t signal = ( uint32_t )qurt_anysignal_wait(&servreg_locator_avail_signal, signal_wait_mask );

      if (SERVREG_LOCATOR_STATUS_MASK & signal)
      {
        MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "avs_pdr_monitor_avs():service registry available. status :(0x%08x)",signal);
        qurt_anysignal_clear(&servreg_locator_avail_signal,signal_wait_mask);

        SERVREG_SERVICE_STATE servreg_state = servreg_get_servloc_availability();
        if (servreg_state != SERVREG_SERVICE_STATE_UP)
        {
          MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "PDR:service locator is not UP(state=0x%08x). Do not proceed with PDR registration", servreg_state );
          return ADSP_EFAILED;
        }
        else
        {
          MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "PDR:service locator status is UP. (state=0x%08x)",servreg_state );
        }
      }
    }

    /* Register to monitor AVS MDF service */
    if (ADSP_FAILED (result = avs_pdr_monitor_init(proc_id)))
    {
      MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "avs_pdr_monitor_init failed ");
      return result;
    }

  }
#endif //SIM


  return result;
}

/**
   This function deinitializes handler for PD restart of Client DSP

    @return
      ADSPResult Error Code
 */
ADSPResult avs_pdr_deinit(uint32_t proc_id)
{
  ADSPResult result = ADSP_EOK;

  /* register to monitor avs */
  if(ADSP_EOK == (result = avs_pdr_monitor_deinit(proc_id)))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "PDR monitor avs failed with result %d",result);
    return result;
  }


  return result;
}




