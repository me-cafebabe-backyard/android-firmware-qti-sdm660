/*=============================================================================
  @file pd_audio_restart.c

  This file contains audio PD restart code.

 *******************************************************************************
 * Copyright (c) 2012-2015 Qualcomm Technologies, Inc.  All Rights Reserved
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
#include "qurt.h"
#include "qurt_elite.h"
#include "qurt_event.h"
#include "pdr_avs.h"
#include "ssr_avs.h"
#include "ap_server_api.h"



/*----------------------------------------------------------------------------
 *  Variables
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *  Function Implementations
 * -------------------------------------------------------------------------*/

/**
   This function is for handling the shutdown of Client DSP

    @return
      ADSPResult Error Code
 */
ADSPResult avs_pdr_ssr_avs_mdf_before_shutdown_handler (void)
{

  ADSPResult           result = ADSP_EOK;
  
  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "In avs_pdr_ssr_avs_mdf_before_shutdown_handler");

  /* Crash AVS */
  qurt_exception_raise_fatal();

  return result;
}

/**
   This function initializes handler for PD restart or SSR of Client DSP

    @return
      ADSPResult Error Code
 */
ADSPResult avs_pdr_ssr_init(uint32_t proc_id)
{
  ADSPResult result = ADSP_EOK;

  if(ADSP_EOK != (result = avs_pdr_init(proc_id)))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "PDR Init is not successful with result %ld", result);
  }

  if (ADSP_EUNSUPPORTED == result)
  {
    /* Incase of failure on above, do SSR init */
    MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "PDR framework is not available trying with SSR");
    if(ADSP_EOK != (result = avs_ssr_init(proc_id)))
    {
      MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "SSR Init is not successful");
      return result;
    }
  }
  else
  {
    return result;
  }

  return result;
}

/**
   This function deinitializes handler for PD restart or SSR of Client DSP

    @return
      ADSPResult Error Code
 */
ADSPResult avs_pdr_ssr_deinit(uint32_t proc_id)
{
  ADSPResult result = ADSP_EOK;

  if(ADSP_EOK != (result = avs_pdr_deinit(proc_id)))
  {
    MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "PDR deInit is not successful");
  }

  if (ADSP_EUNSUPPORTED == result)
  {
    /* Incase of failure on above, do SSR init */
    MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "PDR framework is not available trying with SSR");
    if(ADSP_EOK != (result = avs_ssr_deinit(proc_id)))
    {
      MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "SSR deInit is not successful");
      return result;
    }
  }

  return result;
}

/* This function is currently called from elite_mem_remote_service_event_handler().
   Do not free the packet inside this call. Just return the result */
ADSPResult avs_pdr_ssr_remote_service_up_handler(
  elite_apr_handle_t hAprHandle,
  elite_apr_packet_t *pPkt
)
{
    //The incoming pPkt is freed in the caller function in AVCS

    ap_event_static_service_up_v1_t* pPayload;
    ADSPResult rc;

    elite_apr_if_get_payload( (void**)&pPayload, pPkt );

    ap_server_stat_cmn_header_t *pHeader = (ap_server_stat_cmn_header_t*)pPayload;

    if(pHeader->param_version > AP_PARAM_SERVICE_STATUS_VERSION || (0 == pHeader->param_version))
    {
      MSG_1( MSG_SSID_QDSP6, DBG_ERROR_PRIO, "AVS PDR SSR: remote_service_event_handler,"
             "received invalid version 0x%x",pHeader->param_version );
      return ADSP_EBADPARAM;
    }

    pPayload = ( ap_event_static_service_up_v1_t* )( ( uint8_t* )pPayload + sizeof( ap_server_stat_cmn_header_t ) );

    if(ADSP_EOK != (rc = avs_pdr_ssr_init(pPayload->proc_id)))
    {
      MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "AVS PDR SSR init with proc id %ld is not successful result %ld", pPayload->proc_id, rc);
      return rc;
    }

    return ADSP_EOK;
}


