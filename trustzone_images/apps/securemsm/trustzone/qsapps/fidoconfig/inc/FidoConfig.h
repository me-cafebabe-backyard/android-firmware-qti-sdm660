/*
* Copyright (c) 2014-2015 Qualcomm Technologies, Inc.
* All Rights Reserved.
* Confidential and Proprietary - Qualcomm Technologies, Inc.
*/

#pragma once

#include <stdint.h>
#include "fcApiParams.h"

#define FIDO_CRYPTO_VERSION_MAJOR 2
#define FIDO_CRYPTO_VERSION_MINOR 0

#pragma pack(push, config, 1)

typedef struct {
  uint32_t data1;
  uint16_t data2;
  uint16_t data3;
  uint8_t  data4[8];
} guid_t;

typedef struct {
  uint16_t version_major;
  uint16_t version_minor;
  guid_t cookie;
  uint32_t useSecureUI;
  uint64_t minimum_time_on_display;
  uint32_t displayW;
  uint32_t displayH;
  char provisioning_agent[32];          /** zero terminated */
  uint32_t surrogateAttestation;
  uint16_t uvtVersion;
  uint16_t nonceLen;
  uint32_t sessionInKHAccessToken;      /** use session in KHAccessToken */
  uint16_t extensions[QC_MAX_SUPPORTED_EXTENSIONS];
  struct {
    char name[32];                      /** zero terminated */
    uint8_t version;
    uint16_t allowReprovisioning;
    uint64_t lifespan;
    char aaid[QC_AAID_MAX_LEN];
    uint16_t authType;
    uint16_t matcherProtection;
    uint32_t useBiolib;
    uint16_t secureDisplayAuthToken;
    uint16_t secureDisplayJointTokens;
    uint32_t userVerification;
    uint32_t useTLoc;
    uint32_t forceLoc;
    char contentType[QC_CONTENT_TYPE_MAX_LEN];
    char supportedExtId[QC_MAX_SUPPORTED_EXTENSIONS][QC_SUPPORTED_EXTENSION_ID_MAX_LEN];
  } authenticators[QSAPP_OPTIONAL_PARTNERS_MAX];
  /* SFS location */
  char sfsRoot[64];
} fido_config_t;

#pragma pack(pop, config)
