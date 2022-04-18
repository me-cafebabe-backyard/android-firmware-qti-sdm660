/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

                        A D S P _ L P M _ V O T I N G _ V 0 1  . C

GENERAL DESCRIPTION
  This is the file which defines the pgs service Data structures.

  Copyright (c) 2019 Qualcomm Technologies, Inc.
 All rights reserved.
 Confidential and Proprietary - Qualcomm Technologies, Inc.


  $Header: //components/rel/qmimsgs.adsp/2.6/adsp_lpm_voting/src/adsp_lpm_voting_v01.c#1 $
 *====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/
/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*
 *THIS IS AN AUTO GENERATED FILE. DO NOT ALTER IN ANY WAY
 *====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/

/* This file was generated with Tool version 6.14.9 
   It was generated on: Fri Sep 20 2019 (Spin 0)
   From IDL File: adsp_lpm_voting_v01.idl */

#include "stdint.h"
#include "qmi_idl_lib_internal.h"
#include "adsp_lpm_voting_v01.h"
#include "common_v01.h"


/*Type Definitions*/
/*Message Definitions*/
static const uint8_t prod_set_lpm_vote_req_msg_data_v01[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(prod_set_lpm_vote_req_msg_v01, keep_adsp_out_of_lpm)
};

static const uint8_t prod_set_lpm_vote_resp_msg_data_v01[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x02,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(prod_set_lpm_vote_resp_msg_v01, resp),
  QMI_IDL_TYPE88(1, 0)
};

/* Type Table */
/* No Types Defined in IDL */

/* Message Table */
static const qmi_idl_message_table_entry pgs_message_table_v01[] = {
  {sizeof(prod_set_lpm_vote_req_msg_v01), prod_set_lpm_vote_req_msg_data_v01},
  {sizeof(prod_set_lpm_vote_resp_msg_v01), prod_set_lpm_vote_resp_msg_data_v01}
};

/* Range Table */
/* No Ranges Defined in IDL */

/* Predefine the Type Table Object */
static const qmi_idl_type_table_object pgs_qmi_idl_type_table_object_v01;

/*Referenced Tables Array*/
static const qmi_idl_type_table_object *pgs_qmi_idl_type_table_object_referenced_tables_v01[] =
{&pgs_qmi_idl_type_table_object_v01, &common_qmi_idl_type_table_object_v01};

/*Type Table Object*/
static const qmi_idl_type_table_object pgs_qmi_idl_type_table_object_v01 = {
  0,
  sizeof(pgs_message_table_v01)/sizeof(qmi_idl_message_table_entry),
  1,
  NULL,
  pgs_message_table_v01,
  pgs_qmi_idl_type_table_object_referenced_tables_v01,
  NULL
};

/*Arrays of service_message_table_entries for commands, responses and indications*/
static const qmi_idl_service_message_table_entry pgs_service_command_messages_v01[] = {
  {PROD_SET_LPM_VOTE_REQ_V01, QMI_IDL_TYPE16(0, 0), 4}
};

static const qmi_idl_service_message_table_entry pgs_service_response_messages_v01[] = {
  {PROD_SET_LPM_VOTE_RESP_V01, QMI_IDL_TYPE16(0, 1), 7}
};

/*Service Object*/
struct qmi_idl_service_object pgs_qmi_idl_service_object_v01 = {
  0x06,
  0x01,
  0x428,
  7,
  { sizeof(pgs_service_command_messages_v01)/sizeof(qmi_idl_service_message_table_entry),
    sizeof(pgs_service_response_messages_v01)/sizeof(qmi_idl_service_message_table_entry),
    0 },
  { pgs_service_command_messages_v01, pgs_service_response_messages_v01, NULL},
  &pgs_qmi_idl_type_table_object_v01,
  0x00,
  NULL
};

/* Service Object Accessor */
qmi_idl_service_object_type pgs_get_service_object_internal_v01
 ( int32_t idl_maj_version, int32_t idl_min_version, int32_t library_version ){
  if ( PGS_V01_IDL_MAJOR_VERS != idl_maj_version || PGS_V01_IDL_MINOR_VERS != idl_min_version
       || PGS_V01_IDL_TOOL_VERS != library_version)
  {
    return NULL;
  }
  return (qmi_idl_service_object_type)&pgs_qmi_idl_service_object_v01;
}

