/*=============================================================================
  @file pdf_avs_mdf.cpp

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
/*----------------------------------------------------------------------------
 *  Variables
 * -------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 *  Function Implementations
 * -------------------------------------------------------------------------*/
/**
   This function initializes handler for PD restart of Client DSP

    @return
      ADSPResult Error Code
*/
ADSPResult avs_pdr_init(uint32_t proc_id)
{
	return ADSP_EUNSUPPORTED;
}

/**
   This function deinitializes handler for PD restart of Client DSP

    @return
      ADSPResult Error Code
*/
ADSPResult avs_pdr_deinit(uint32_t proc_id)
{
  return ADSP_EUNSUPPORTED;
}
