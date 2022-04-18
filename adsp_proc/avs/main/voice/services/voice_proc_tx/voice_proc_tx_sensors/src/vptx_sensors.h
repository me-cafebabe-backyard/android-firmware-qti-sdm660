#ifndef VPTX_SENSORS_H
#define VPTX_SENSORS_H

/*============================================================================
  FILE:          vptx_sensors.h

  OVERVIEW:      This file has the data structure for sensors interface for fpro v2 algorithm.

  DEPENDENCIES:  None

Copyright (c) 2014 Qualcomm Technologies, Inc.  All Rights Reserved.
Confidential and Proprietary - Qualcomm Technologies, Inc.
============================================================================*/

/*============================================================================
  EDIT HISTORY FOR MODULE

  $Header: //components/rel/avs.adsp/2.8/voice/services/voice_proc_tx/voice_proc_tx_sensors/src/vptx_sensors.h#2 $

  when       who     what, where, why
  ---------- ------- ---------------------------------------------------------
  2014-07-14 rishabht   Initial revision.
============================================================================*/

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/

#include "vptx_sensors_api.h"
#include "sns_sam_facing_v01.h"
#include "EliteQmiClientIf.h"



// structure used to request for registration to qmi
typedef struct qmi_obj_t
{
   sns_sam_facing_enable_req_msg_v01*  data_req;
   sns_sam_facing_enable_resp_msg_v01* data_resp;                   // Registration response for status/error codes. This must be successful
                                                                    // for Vptx to start accepting indications.
   elite_qmi_client_type               user_handle;                 // User handle issued by QMI.
   qurt_elite_signal_t*                reg_sig;                     // Signal used to complete registration with Sensors service
   qurt_elite_signal_t*                ind_sig;                     // Signal set each time there's an indication from Sensors
   sns_sam_facing_event_e_v01          holding_pattern;             // Holding pattern information received from Sensors.
   uint8_t                             instance_id;                 // Instance ID issued by Sensors manager, for the client (Vptx)
                                                                    // to maintain and cross-reference.
   uint32_t                            session_num;                 // vptx session number
} qmi_obj_t;

#endif /* #ifndef VPTX_SENSORS_H */
