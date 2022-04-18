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

#include "qsee_log.h"
#include "qsee_message.h"
#include "qsee_timer.h"
#include "auth.h"
#include "stringl.h"
#include "biometric_result.h"

#define SECURE_AUTH_CMD_VERIFY_USER           1
#define SECURE_AUTH_CMD_GET_ENROLLMENT_STATUS 2
#define SECURE_AUTH_CMD_VERIFY_USER_BIOLIB    3

#define USER_ID 12345

#ifdef ENABLE_QSEE_LOG_MSG_DEBUG
#undef ENABLE_QSEE_LOG_MSG_DEBUG
#define ENABLE_QSEE_LOG_MSG_DEBUG 1
#endif

#pragma pack(push, params, 1)

struct send_cmd{
  uint32_t cmd_id;
  union {
    /** VerifyUserCmd **/
    struct {
      char secAppName[QC_SEC_APP_NAME_LEN];
      uint8_t nonce[QC_AUTH_NONCE];
    };
    /** VerifyUserBiolibCmd **/
    // TODO: nothing now. Maybe group id?
    /** GetEnrollmentStatusCmd **/
    uint64_t userId;
  };
};
struct send_cmd_rsp{
  union {
    /** VerifyUserRsp **/
    struct {
      uint16_t result;
      uint64_t userId;
      qc_user_verification_token_t token;
    } verifyUserRsp;
    /** VerifyUserBiolibRsp **/
    struct {
      uint16_t result;
      uint64_t userId;
    } verifyUserBiolibRsp;
    /** EnrollmentStatusRsp **/
    uint32_t status;
  };
};

#pragma pack(pop, params)

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

void tz_app_init(void) {
  qsee_log(QSEE_LOG_MSG_DEBUG, "%s", __func__);
}

void tz_app_cmd_handler(void* cmd, uint32_t cmdlen,
                        void* rsp, uint32_t rsplen)
{
  struct send_cmd *cmd_ptr = (struct send_cmd *)cmd;
  struct send_cmd_rsp *rsp_ptr = (struct send_cmd_rsp *)rsp;

  int rv = 0;
  uint32_t status = 0;
  int result = 1;
  uint64_t messageLen = 0;
  uint8_t extension[] = {
    //0x03, 0x01, 0x04, 0x00, 0x01, 0x02, 0x03, 0x04, // UVI
    0x81, 0x01, 0x01, 0x00, 0x02, // authenticator version
    0x05, 0x01, 0x02, 0x00, 0x01, 0x02 // UVS
    };
  BIO_ERROR_CODE brv = BIO_NO_ERROR;
  bio_buffer extData = {extension, sizeof(extension)};
  bio_result bioResult = {
    BIO_FINGERPRINT_MATCHING,
    true,
    USER_ID,
    12,
    BIO_NA
    };

  /* Default hard coded auth token values */
  qc_authentication_token_t authToken = {
    {1, 0},
    (qc_auth_code_t)0,
    USER_ID,
    0,
    {0},
    19,
    {
      0x03, 0x01, 0x04, 0x00, 0x01, 0x02, 0x03, 0x04, // UVI
      0x81, 0x01, 0x01, 0x00, 0x02, // authenticator version
      0x05, 0x01, 0x02, 0x00, 0x01, 0x02 // UVS
    }
  };

  qsee_log(QSEE_LOG_MSG_DEBUG, "%s+", __func__);

  if (cmd == NULL || rsp == NULL) {
    qsee_log(QSEE_LOG_MSG_ERROR, "%s: req == NULL || rsp == NULL", __func__);
    return;
  }
  if ((cmdlen < sizeof(struct send_cmd)) || (rsplen < sizeof(struct send_cmd_rsp))) {
    qsee_log(QSEE_LOG_MSG_ERROR, "%s: size error. %u vs %u || %u vs %u", __func__,
      cmdlen, sizeof(struct send_cmd),
      rsplen, sizeof(struct send_cmd_rsp));
    return;
  }

  switch (cmd_ptr->cmd_id) {
    case SECURE_AUTH_CMD_VERIFY_USER:
      do{
        cmd_ptr->secAppName[sizeof(cmd_ptr->secAppName) - 1] = 0;
        qsee_log(QSEE_LOG_MSG_DEBUG, "cmd: SECURE_AUTH_CMD_VERIFY_USER for: %s", cmd_ptr->secAppName);
        authToken.uptime = qsee_get_uptime();
        memscpy(authToken.nonce, QC_AUTH_NONCE, cmd_ptr->nonce, QC_AUTH_NONCE);

        // encapsulate it
        messageLen = sizeof(rsp_ptr->verifyUserRsp.token.message);
        result = qsee_encapsulate_inter_app_message(
          cmd_ptr->secAppName,
          (uint8_t*)&authToken,
          sizeof(authToken)- sizeof(authToken.extData) + authToken.extDataLength,
          rsp_ptr->verifyUserRsp.token.message,
          (uint32_t*)&messageLen);
        if (result) {
         qsee_log(QSEE_LOG_MSG_ERROR, "Error in qsee_encapsulate_inter_app_message: %x", result);
         rv = 1;
         break;
        }
        rsp_ptr->verifyUserRsp.token.messageLen = messageLen;
        rsp_ptr->verifyUserRsp.userId = authToken.userId;

      } while(0);
      rsp_ptr->verifyUserRsp.result = rv;
      break;
    case SECURE_AUTH_CMD_GET_ENROLLMENT_STATUS:
    qsee_log(QSEE_LOG_MSG_DEBUG, "cmd: SECURE_AUTH_CMD_GET_ENROLLMENT_STATUS: %llu", cmd_ptr->userId);
      if(cmd_ptr->userId == USER_ID){
      status = 1;
      }
    rsp_ptr->status = status;
      break;
    case SECURE_AUTH_CMD_VERIFY_USER_BIOLIB:
      do{
        qsee_log(QSEE_LOG_MSG_DEBUG, "cmd: SECURE_AUTH_CMD_VERIFY_USER_BIOLIB");
        brv = bio_set_auth_result(&bioResult, &extData);
        if (brv) {
          qsee_log(QSEE_LOG_MSG_ERROR, "Error in bio_set_auth_result: %d", brv);
           rv = 1;
           break;
          }
        rsp_ptr->verifyUserBiolibRsp.userId = bioResult.user_id;
      } while(0);
      rsp_ptr->verifyUserBiolibRsp.result = rv;
      break;
    default:
    qsee_log(QSEE_LOG_MSG_DEBUG, "Unsupported command");
      break;
  }
  qsee_log(QSEE_LOG_MSG_DEBUG, "%s-", __func__);
}

void tz_app_shutdown(void) {
  qsee_log(QSEE_LOG_MSG_DEBUG, "%s", __func__);
}
