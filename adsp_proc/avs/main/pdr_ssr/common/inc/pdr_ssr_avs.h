/*=============================================================================
  @file pdr_ssr_avs.h

  This file contains handling of PD restart or SSR of Client DSP.

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
#include "Elite.h"

/*----------------------------------------------------------------------------
 *  Function Declarations
 * -------------------------------------------------------------------------*/
/**
   This function initializes handler for PD restart or SSR of Client DSP

    @return
      ADSPResult Error Code
*/
ADSPResult avs_pdr_ssr_init(uint32_t proc_id);

/**
   This function deinitializes handler for PD restart or SSR of Client DSP

    @return
      ADSPResult Error Code
*/
 ADSPResult avs_pdr_ssr_deinit(uint32_t proc_id);

 /**
    This function is for handling the shutdown of Client DSP

     @return
       ADSPResult Error Code
 */
 ADSPResult avs_pdr_ssr_avs_mdf_before_shutdown_handler (void);

 ADSPResult avs_pdr_ssr_remote_service_up_handler(
   elite_apr_handle_t hAprHandle,
   elite_apr_packet_t *pPkt
 );
