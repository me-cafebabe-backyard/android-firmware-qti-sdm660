#ifndef FAST_PLAYBACK_PARSE_H_
#define FAST_PLAYBACK_PARSE_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sns_common.h"
#include "comdef.h"
#include "sns_osa.h"
#include "sns_smgr.h"

#define FPB_MAX_DIAG_STRING_SIZE        500
#define FPB_MAX_BYTE_STRING_SIZE        (FPB_MAX_DIAG_STRING_SIZE / 4)
#define FPB_DIAG_STRING_COMMENT_CHAR    '#'
#define FPB_DIAG_STRING_DELIMS          " "

/* Each signal should use a unique bit */
#define FPB_RESUME_CLIENT_INIT_SIG      0x01

char *line_save;

typedef enum fast_playback_sensor1_req_type
{
  FPB_SENSOR1_OPEN  = 1,
  FPB_SENSOR1_WRITE = 2,
  FPB_SENSOR1_CLOSE = 3
} fast_playback_sensor1_req_type;

typedef PACK(struct)
{
  /* byteX values are defined in SRTRunNative.pm in the SRT Framework */
  uint8_t byte0; // Should be 128
  uint8_t byte1; // Should be 64
  uint8_t byte2; // Originator of the request? (usually 2, for APPS)
  uint8_t byte3; // Should be 0
  uint8_t byte4; // Should be 2
  fast_playback_sensor1_req_type req_type;
} fast_playback_sensor1_req_hdr;

typedef enum fast_playback_session_hdr_msg_type
{
  FPB_QMI_IDL_REQUEST    = 0,
  FPB_QMI_IDL_RESPONSE   = 1,
  FPB_QMI_IDL_INDICATION = 2
} fast_playback_session_hdr_msg_type;

typedef PACK(struct)
{
  /* see SRTRunNative.pm in the SRT Framework */
  uint32_t cb_data; // Call-back data
  uint8_t srvc_num; // Service number (see sns_common_v01.h)
  uint16_t msg_id; // Message ID
  fast_playback_session_hdr_msg_type msg_type; // Message Type
  uint8_t txn_id; // Transaction ID (should be 0)
  uint16_t qmi_msg_size; // Size of the QMI message
} fast_playback_session_hdr;

typedef PACK(struct)
{
  fast_playback_sensor1_req_hdr req_hdr;            // Sensor1 Diag request header
  fast_playback_session_hdr     session_hdr;        // QMI session header
  uint8_t                       qmi_message_body[1]; // QMI message body
} fast_playback_sensor1_diag_req;



sns_err_code_e fast_playback_parse_send_diag_req( const char* sns_diag_filename,
    fast_playback_sensor1_diag_req** diag_req_ptr);

sns_err_code_e fast_playback_parse_client_init( const fast_playback_sensor1_diag_req * diag_req );
sns_err_code_e fast_playback_disable_client( const fast_playback_sensor1_diag_req * diag_req );
sns_err_code_e fast_playback_send_cal_reset(smgr_sensor_id_e sensor_id);
qmi_idl_service_object_type fpb_parse_get_service_obj( uint8_t service_num );
sns_err_code_e fast_playback_send_cal_mode_switch(smgr_sensor_id_e sensor_id, q16_t phone_mode );
#endif /* FAST_PLAYBACK_PARSE_H_*/
