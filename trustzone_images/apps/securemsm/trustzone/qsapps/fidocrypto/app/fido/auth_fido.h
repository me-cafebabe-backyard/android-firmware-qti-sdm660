/*
 * Copyright (c) 2014 Qualcomm Technologies, Inc. All Rights Reserved.
 * Qualcomm Technologies Proprietary and Confidential.
*/

#pragma once

#include "qso.h"
#include "fidot.h"
#include <auth.h>

#ifdef __RVCT__
#pragma anon_unions
#endif

#define QC_ECC_256_PRV_KEY_LEN 36 /**< 9 uint32 */

#pragma pack(push, auth_fido, 1)

/** Raw Key Handle
 * */
typedef struct {
  uint32_t khAccessTokenLen;
  uint8_t khAccessToken[UAFV1_KH_ACCESS_TOKEN_MAX_LEN];
  uint8_t key[QC_ECC_256_PRV_KEY_LEN];
  uint64_t userId;
  char username[QC_USERNAME_MAX_LEN+1];
} qc_raw_key_handle_t;

/** Key as stored as a AES GCM secure object
 * Union-object designed to be used as:
 * - an opaque blob
 * - a clear Raw Key Handle
 * - a wrapped key handle, with separate header/ct/signature
 * */
typedef union {
  uint8_t value[QSO_SIZE(0,sizeof(qc_raw_key_handle_t))];
  qc_raw_key_handle_t rawKeyHandle;
  struct {
    QSoHeader_t header;
    qc_raw_key_handle_t rawKeyHandle;
    uint8_t tag[SW_AES_BLOCK_BYTE_LEN];
  } wrapped;
} qc_key_handle_t;

#pragma pack(pop, auth_fido)

#ifdef __cplusplus
/** C++ wrapper for key handles, to use them in STL containers */
class KeyHandle {
public:
  qc_key_handle_t handle;

  KeyHandle(const KeyHandle &other) {
    this->handle = other.handle;
  }
  KeyHandle(const qc_key_handle_t &handle_) {
    this->handle = handle_;
  }
  KeyHandle & operator= (const KeyHandle & other) {
    if (this != &other) {
      this->handle = other.handle;
    }
    return *this;
  }
};
#endif

typedef struct {
  uint16_t authType;
  uint8_t maxKeyHandles;
  uint32_t userVerification;
  uint16_t keyProtection;
  uint16_t matcherProtection;
  uint16_t transactionConfirmationDisplay;
  uint16_t authAlg;
} qc_authentication_metadata_t;

typedef struct {
  uint32_t width;
  uint32_t height;
  uint8_t bitDepth;
  uint8_t colorType;
  uint8_t compression;
  uint8_t filter;
  uint8_t interlace;
} qc_display_png_characteristics_t;

typedef struct {
  uint8_t authIndex;
  uint8_t aaid[QC_AAID_MAX_LEN];
  qc_authentication_metadata_t authMetadata;
  uint8_t contentType[QC_CONTENT_TYPE_MAX_LEN];
  uint8_t displayCharacteristicsListLen;
  qc_display_png_characteristics_t displayCharacteristics[QC_MAX_PNG_CHARACTERISTICS];
  uint8_t assertionScheme[QC_ASSERTION_SCHEME_MAX_LEN];
  uint8_t attestationTypeListLen;
  uint16_t attestationType[QC_MAX_ATTESTATION_TYPES];
  uint8_t supportedExtListLen;
  uint8_t supportedExtId[QC_MAX_SUPPORTED_EXTENSIONS][QC_SUPPORTED_EXTENSION_ID_MAX_LEN];
} qc_authentication_info_t;
