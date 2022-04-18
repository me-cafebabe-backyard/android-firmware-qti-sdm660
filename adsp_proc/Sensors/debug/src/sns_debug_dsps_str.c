/*============================================================================

@file
sns_debug_dsps_str.c

@brief
Contains main implementation of receiving and processing
debug strings on DSPS.

Copyright (c) 2010-2016 Qualcomm Technologies, Inc.
All Rights Reserved.
Confidential and Proprietary - Qualcomm Technologies, Inc.

============================================================================*/

/*=====================================================================
                 INCLUDE FILES
=======================================================================*/
#include "sns_common.h"
#include "sns_debug_str.h"
#include "sns_debug_api.h"
#include "sns_memmgr.h"
#include "sns_debug_interface_v01.h"
#include "qmi_csi.h"
#include "qmi_csi_common.h"
#include "qmi_csi_target_ext.h"

/* debug mask to filter debug messages on DSPS */
sns_debug_mask_t sns_diag_dsps_debug_mask = 0xffffffffffffffffULL;

/*===========================================================================
                  FUNCTIONS
============================================================================*/

/*===========================================================================

  FUNCTION:   sns_diag_dsps_set_debug_mask

===========================================================================*/
/*!
  @brief
  Sets the debug mask on the DSPS processor

  @param[i]
  msg_ptr: pointer to message containing debug mask that indicates which
           debug messages are enabled/disabled.

  @return
  none
*/
/*=========================================================================*/
void sns_diag_dsps_set_debug_mask(sns_diag_set_debug_mask_req_msg_v01* msg_ptr)
{
  if (msg_ptr != NULL)
  {
    sns_diag_dsps_debug_mask = msg_ptr->debug_mask.mask;
  }
}

/*===========================================================================

  FUNCTION:   sns_debug_is_module_disabled

===========================================================================*/
/*===========================================================================*/
/*!
  @brief
  Returns 1 if the the module's debug strings need to be filtered.

  @param[i] module_id        : Debug module id

  @return
  uint8_t : 1 - Module's messages should be filtered
            0 - Module's messages should NOT be filtered
*/
/*=========================================================================*/
uint8_t sns_debug_is_module_disabled(sns_debug_module_id_e module_id)
{
  uint64_t   temp_i=1;
  uint8_t    ret_value=0;

  /* Check if the messages from the module are enabled
   * based on the debug string filter mask
   */
  if ( SNS_DBG_MOD_DSPS_SAM == module_id )
  {
    ret_value = 0;
  }
  else if ((sns_diag_dsps_debug_mask & (temp_i << module_id)) != 0)
  {
    ret_value = 1;
  }

  return ret_value;
}
