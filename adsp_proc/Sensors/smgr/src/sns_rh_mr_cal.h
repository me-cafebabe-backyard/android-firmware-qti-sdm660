#ifndef SNS_RH_MR_CAL_H_
#define SNS_RH_MR_CAL_H_
/*============================================================================

  @file sns_rh_mr_cal.h

  @brief
  This file contains definition for calibration  message routing functionality

  Copyright (c) 2016 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.

=============================================================================*/
/*============================================================================
  EDIT HISTORY FOR FILE

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------
 2016-11-01   np   Adding back enum type for update request.
 2016-07-05   np   SMR interface for calibration service.
 ============================================================================*/
#include "sns_osa.h"
#include "sns_usmr.h"
#include "sns_queue.h"
#include "sns_sam_cal_v01.h"
/*============================================================================

                   DEFINITIONS AND TYPES

=============================================================================*/
#define SNS_RH_MR_INIT_CLIENT_TIMEOUT_US 60000000 // 30 Seconds
#define SNS_RH_MR_INIT_REG_TIMEOUT_US    60000000 // 60 Seconds
#define SNS_RH_MR_SAM_MAX_CAL_ALGO_NUM   2
/*===========================================================================

                   STRUCTURE DEFINITIONS

===========================================================================*/
typedef enum {
  RH_SAM_IND_MSG,
  RH_SAM_RESP_MSG
} sns_rh_msg_type_e;

typedef enum
{
  SNS_RH_REG_ITEM_TYPE_NONE,
  SNS_RH_REG_ITEM_TYPE_SINGLE,
  SNS_RH_REG_ITEM_TYPE_GROUP
} sns_rh_reg_item_type_e;

typedef enum
{
   SNS_RH_CAL_ALGO_ENABLING,
   SNS_RH_CAL_ALGO_ENABLED,
   SNS_RH_CAL_ALGO_DISABLING,
   SNS_RH_CAL_ALGO_DISABLED,
   SNS_RH_CAL_ALGO_REG_WRITE
} sns_rh_cal_algo_status_e;

struct sns_rh_cal_q_item_s
{
  sns_q_link_s       q_link;
  unsigned int       msg_id;
  uint8_t            sensor_id;
  sns_rh_msg_type_e rh_msg_type;
  void               *body_ptr;
} ;

typedef struct
{
  /* SMR Client handle used to send/receive messages for this stream */
  smr_client_hndl client_hndl[SNS_RH_MR_SAM_MAX_CAL_ALGO_NUM];
  sns_q_s         sam_q;
  OS_EVENT*       mutex_ptr;
} sns_rh_mr_c;

/*===========================================================================

                          FUNCTIONS

===========================================================================*/

extern sns_err_code_e   sns_rh_mr_cal_send_enable_req(
 smr_client_hndl           smr_hndl,
 uint8_t                   msg_id,
 uint8_t                   svc_id,
 uint8_t                   cal_phone_mode);

extern sns_err_code_e   sns_rh_mr_cal_send_disable_req(
 smr_client_hndl           smr_hndl,
 uint8_t                   msg_id,
 int32_t                   inst_id,
 uint8_t                   svc_id);

extern sns_err_code_e   sns_rh_mr_cal_send_update_req(
 smr_client_hndl                smr_hndl,
 uint8_t                        msg_id,
 int32_t                        inst_id,
 uint8_t                        sensor_id,
 sns_sam_cal_update_type_e_v01  update_type);

extern smr_err          sns_rh_mr_cal_smr_client_check(
 qmi_idl_service_object_type  service_obj,
 uint32_t                     timeout);

extern void             sns_rh_mr_cal_init(void);

#endif /* SMGR_SRC_SNS_RH_MR_CAL_H_ */
