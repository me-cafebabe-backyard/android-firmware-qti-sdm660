/*
@file app_main.c
@brief QSEE Sample Authenticator App main entry point.
*/

/*===========================================================================
 Copyright (c) 2015 Qualcomm Technologies, Inc.
 All Rights Reserved.
 Qualcomm Technologies Proprietary and Confidential.
===========================================================================*/

/*===========================================================================

                            EDIT HISTORY FOR FILE

# when       who     what, where, why
# --------   ---     ---------------------------------------------------------
 02/11/15    ts      Initial Version
===========================================================================*/

#include <qsee_log.h>
#include <qsee_message.h>
#include <qsee_timer.h>
#include <auth.h>
#include <stringl.h>

#define SECURE_EXT_AUTH_CMD_GET_TOKEN           1

#ifdef ENABLE_QSEE_LOG_MSG_DEBUG
#undef ENABLE_QSEE_LOG_MSG_DEBUG
#define ENABLE_QSEE_LOG_MSG_DEBUG 1
#endif

struct send_cmd{
  uint32_t cmd_id;
  union {
    /** VerifyUserCmd **/
    struct {
      char secAppName[QC_SEC_APP_NAME_LEN];
      uint8_t nonce[QC_AUTH_NONCE];
    };
    /** GetEnrollmentStatusCmd **/
    uint64_t userId;
  };
} __attribute__ ((packed));
struct send_cmd_rsp{
  union {
    /** VerifyUserRsp **/
    struct {
      uint16_t result;
      qc_user_verification_token_t token;
      uint64_t userId;
    };
    /** EnrollmentStatusRsp **/
    uint32_t status;
  };
} __attribute__ ((packed));


void dumpHex(const char *tag, const uint8_t *buffer, unsigned int len) {
  char output[256];
  memset(output,0,sizeof(output));
  qsee_log(QSEE_LOG_MSG_DEBUG, "dumpHex %s (%d bytes @ 0x%08X)",tag,len, (unsigned int)buffer);
  unsigned int j=0;
  for (unsigned int i=0; i<len; i++) {
    snprintf(output+j*3,4,"%02X ",buffer[i]);
    *(output+j*3+3)=0;
    if (j == 15) {
      qsee_log(QSEE_LOG_MSG_DEBUG, "%s",output);
      j=0;
    } else {
      j++;
    }
  }
  if (j>0 && j<=15) {
    qsee_log(QSEE_LOG_MSG_DEBUG, "%s",output);
  }
}

void tz_app_init(void){
  qsee_log(QSEE_LOG_MSG_DEBUG, "%s", __func__);
}

void tz_app_cmd_handler(void* cmd, uint32_t cmdlen,
                        void* rsp, uint32_t rsplen)
{
  struct send_cmd *cmd_ptr = (struct send_cmd *)cmd;
  struct send_cmd_rsp *rsp_ptr = (struct send_cmd_rsp *)rsp;

  int rv = 0;
  int result = 1;
  uint64_t messageLen = 0;
  uint32_t status = 0;

  /* Default hard coded auth token values */
  qc_authentication_token_t authToken = {
    {1, 0},
    (qc_auth_code_t)0,
    12345,
    0,
    {0},
    8,
    { 0x01, 0x01, 0x04, 0x00, 0x01, 0x02, 0x03, 0x04 }
  };

  qsee_log(QSEE_LOG_MSG_DEBUG, "%s+", __func__);

  switch (cmd_ptr->cmd_id) {
  case SECURE_EXT_AUTH_CMD_GET_TOKEN:
    do{
      cmd_ptr->secAppName[sizeof(cmd_ptr->secAppName) - 1] = 0;
      authToken.uptime = qsee_get_uptime();
      memscpy(authToken.nonce, QC_AUTH_NONCE, cmd_ptr->nonce, QC_AUTH_NONCE);

      qsee_log(QSEE_LOG_MSG_DEBUG, "SECURE_AUTH_CMD_VERIFY_USER: secAppName=%s", cmd_ptr->secAppName);

      dumpHex("token", (uint8_t*)&authToken, sizeof(authToken)- sizeof(authToken.extData) + authToken.extDataLength);
      // encapsulate it
      messageLen = sizeof(rsp_ptr->token.message);
      result = qsee_encapsulate_inter_app_message(
        cmd_ptr->secAppName,
        (uint8_t*)&authToken,
        sizeof(authToken)- sizeof(authToken.extData) + authToken.extDataLength,
        rsp_ptr->token.message,
        (uint32_t*)&messageLen);
      if (result) {
        qsee_log(QSEE_LOG_MSG_ERROR, "Error in qsee_encapsulate_inter_app_message: %x", result);
        rv = 1;
        break;
      }
      rsp_ptr->token.messageLen = messageLen;
      rsp_ptr->userId = authToken.userId;

    } while(0);
    rsp_ptr->result = rv;
    break;
  default:
    qsee_log(QSEE_LOG_MSG_DEBUG, "Unsupported command");
    break;
  }
  qsee_log(QSEE_LOG_MSG_DEBUG, "%s-", __func__);
}

void tz_app_shutdown(void)
{
}
