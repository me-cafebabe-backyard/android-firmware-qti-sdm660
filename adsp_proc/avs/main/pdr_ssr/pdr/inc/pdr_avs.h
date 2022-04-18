/*=============================================================================
  @file pdf_avs.h

  This file contains AVS PDR handling

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
   This function initializes handler for PD restart of Client DSP

    @return
      ADSPResult Error Code
*/
ADSPResult avs_pdr_init(uint32_t proc_id);

/**
   This function deinitializes handler for PD restart of Client DSP

    @return
      ADSPResult Error Code
*/
ADSPResult avs_pdr_deinit(uint32_t proc_id);
