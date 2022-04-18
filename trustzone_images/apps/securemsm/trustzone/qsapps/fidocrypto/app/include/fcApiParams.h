/**
 * Copyright (c) 2014-2015 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#pragma once

#include <stdint.h>
#include <auth_fido.h>

#ifdef __RVCT__
#pragma anon_unions
#endif

#define MAX_KEY_HANDLES   32
#define MAX_EXTENSIONS     5

#define QSAPP_OPTIONAL_PARTNERS_MAX  8

#define QC_PROVISION_RESPONSE_MAX 5000


#pragma pack(push, params, 1)

/******************************************************************************/
/* (1) Initialize */
/******************************************************************************/
typedef struct {
  uint32_t version;
} cmdInitialize_t;
typedef struct {
  uint32_t version;
} rspInitialize_t;
/******************************************************************************/
/* (2) GetInfo */
/******************************************************************************/
typedef struct {
  uint8_t cookie[16];
} cmdGetInfo_t;
/** GetInfo Response */
typedef struct {
  uint16_t statusCode;
  uint8_t apiVersion;
  uint8_t authListLen;
  qc_authentication_info_t authInfo[QSAPP_OPTIONAL_PARTNERS_MAX];
} rspGetInfo_t;
/******************************************************************************/
/* (3) Register */
/******************************************************************************/
/** Register command */
typedef struct {
  uint8_t cookie[16];
  uint32_t finalChallengeLen;
  uint8_t finalChallenge[UAFV1_FINAL_CHALLENGE_MAX_LEN];
  uint32_t khAccessTokenLen;
  uint8_t khAccessToken[UAFV1_KH_ACCESS_TOKEN_MAX_LEN];
  uint32_t authIndex;
  uint32_t useTloc;
  qc_user_verification_token_t token;
  uint8_t appIdHash[32];
  qc_user_verification_token_t extensions[MAX_EXTENSIONS];
  uint16_t attestationType;
  char username[QC_USERNAME_MAX_LEN+1]; /**< Username for the remote server */
  uint64_t session;
} cmdRegister_t;
/** Register response */
typedef struct {
  qc_key_handle_t keyHandle;
  uint32_t fido_rv;
  uint64_t session;
  struct {
    uint32_t len;
    uint8_t value[QC_REG_CMD_RESP_MAX_LEN]; /**< TAG_UAFV1_REG_CMD_RESP */
  } tlv;
} rspRegister_t;
/******************************************************************************/
/* (4) Sign */
/******************************************************************************/
/** Sign command */
typedef struct {
  uint8_t cookie[16];
  uint32_t finalChallengeLen;
  uint8_t finalChallenge[UAFV1_FINAL_CHALLENGE_MAX_LEN];
  uint32_t khAccessTokenLen;
  uint8_t khAccessToken[UAFV1_KH_ACCESS_TOKEN_MAX_LEN];
  uint32_t authIndex;
  uint32_t useTloc;
  uint32_t handlesLen;
  qc_key_handle_t handles[MAX_KEY_HANDLES];
  qc_user_verification_token_t token;
  uint8_t appIdHash[32];
  uint8_t transactionHash[32];
  qc_user_verification_token_t extensions[MAX_EXTENSIONS];
  uint64_t session;
} cmdSign_t;
/** Sign response */
typedef struct {
  uint32_t fido_rv;
  uint64_t session;
  struct {
    uint32_t len;
    uint8_t value[QC_SIGN_CMD_RESP_MAX_LEN]; /**< TAG_UAFV1_SIGN_CMD_RESP */
  } tlv;
} rspSign_t;
/******************************************************************************/
/* (5) SetChallenge */
/******************************************************************************/
/** SetChallenge command */
typedef struct {
  uint32_t finalChallengeLen;
  uint8_t finalChallenge[UAFV1_FINAL_CHALLENGE_MAX_LEN];
} cmdSetChallenge_t;
/** SetChallenge response */
typedef struct {
  uint32_t reserved;
} rspSetChallenge_t;
/******************************************************************************/
/* (99) Provision */
/******************************************************************************/
/** Provision command */
typedef struct {
  uint32_t dataLen;
  uint32_t dataBuffer;
  uint64_t dataBuffer64;
} cmdProvision_t;
/** Provision response */
typedef struct {
  uint32_t responseLen;
  uint8_t response[QC_PROVISION_RESPONSE_MAX];
} rspProvision_t;

#pragma pack(pop, params)
