/*=============================================================================
  @file ssr_avs.cpp

  This file contains AVS MDF SSR handling

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
#include "ssr_avs.h"

#include "sys_m_messages.h"
#include "rcecb.h"
#include "adsp_core_api.h"


/*----------------------------------------------------------------------------
 *  Variables
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *  Function Implementations
 * -------------------------------------------------------------------------*/
#ifndef SIM
static void avs_ssr_rem_dsp_before_shutdown_handler()
{
  ADSPResult result = ADSP_EOK;
  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "In avs_ssr_rem_dsp_before_shutdown_handler");
  if(ADSP_EOK != (result = avs_pdr_ssr_avs_mdf_before_shutdown_handler()))
  {
    MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "failure in avs_pdr_ssr_avs_mdf_before_shutdown_handler");
  }
}
#endif


/**
   This function initializes handler for SSR of Client DSP

    @return
      ADSPResult Error Code
 */
ADSPResult avs_ssr_init(uint32_t proc_id)
{
  ADSPResult result = ADSP_EOK;
#ifndef SIM
  RCECB_HANDLE ssr_handle = NULL;

  switch (proc_id)
  {
    case MODEM_DSP_PROC_ID:
    {

      /* Register for system monitor SSR callbacks. */
      ssr_handle = rcecb_register_name( SYS_M_SSR_MODEM_BEFORE_SHUTDOWN,

                                        (RCECB_CALLBACK_FNSIG const)avs_ssr_rem_dsp_before_shutdown_handler );
      break;
    }
    case SENSOR_DSP_PROC_ID:
    {

      /* Register for system monitor SSR callbacks. */
      ssr_handle = rcecb_register_name( SYS_M_SSR_SLPI_BEFORE_SHUTDOWN,

                                        (RCECB_CALLBACK_FNSIG const)avs_ssr_rem_dsp_before_shutdown_handler );
      break;

    }
  }
  if ( ssr_handle == NULL )
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "avs_ssr_init() Failed to register for "
          " proce ID %ld shutdown callback", proc_id);

    return ADSP_EFAILED;
  }
#endif //SIM

  return result;
}

/**
   This function deinitializes handler for SSR of Client DSP

    @return
      ADSPResult Error Code
 */
ADSPResult avs_ssr_deinit(uint32_t proc_id)
{
  ADSPResult result = ADSP_EOK;
#ifndef SIM
  RCECB_HANDLE ssr_handle;

  switch (proc_id)
  {
    case MODEM_DSP_PROC_ID:
    {

      /* Register for system monitor SSR callbacks. */
      ssr_handle = rcecb_unregister_name( SYS_M_SSR_MODEM_BEFORE_SHUTDOWN,

                                          (RCECB_CALLBACK_FNSIG const)avs_ssr_rem_dsp_before_shutdown_handler );
      break;
    }
    case SENSOR_DSP_PROC_ID:
    {

      /* Register for system monitor SSR callbacks. */
      ssr_handle = rcecb_unregister_name( SYS_M_SSR_SLPI_BEFORE_SHUTDOWN,

                                          (RCECB_CALLBACK_FNSIG const)avs_ssr_rem_dsp_before_shutdown_handler );
      break;

    }
  }


#endif //SIM
  return result;
}

