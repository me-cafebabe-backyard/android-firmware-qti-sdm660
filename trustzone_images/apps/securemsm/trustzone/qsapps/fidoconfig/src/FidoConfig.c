/*
* Copyright (c) 2014-2015 Qualcomm Technologies, Inc.
* All Rights Reserved.
* Confidential and Proprietary - Qualcomm Technologies, Inc.
*/

#include <stddef.h>
#include "FidoConfig.h"

#define FIDO_CRYPTO_VERSION_MAJOR 2
#define FIDO_CRYPTO_VERSION_MINOR 0

#define PROVISIONING_AGENT_APP_NAME "chamomile"
#define NS_SAMPLEAUTH_APP_NAME      "nssampleauth"
#define NS_SAMPLEAUTH_AAID          "5143#0120"
#define NS_SAMPLEAUTH_USER_VERIF    0x00 /* USER_VERIFY_NONE 0x00 */
#define NS_IRISAUTH_APP_NAME        "nsirisauth"
#define NS_IRISAUTH_AAID            "5143#0220"
#define NS_IRISAUTH_USER_VERIF      0x00 /* USER_VERIFY_NONE 0x00 */
#define SAMPLEAUTH_APP_NAME         "sampleauth"
#define SAMPLEAUTH_AAID             "5143#0320"
#define SAMPLEAUTH_USER_VERIF       0x02 /* USER_VERIFY_FINGERPRINT 0x02 */
#define FINGERPRINT_APP_NAME        "fingerprint"
#define FINGERPRINT_AAID            "5143#0420"
#define FINGERPRINT_USER_VERIF      0x02 /* USER_VERIFY_FINGERPRINT (0x02) */
#define SAMPLEEXTAUTH_APP_NAME      "nsecureextauth"
#define SAMPLEEXTAUTH_AAID          ""
#define SAMPLEEXTAUTH_USER_VERIF    0x00 /* USER_VERIFY_NONE 0x00 */
#define SECUREEXTAUTH_APP_NAME      "sampleextauth"
#define SECUREEXTAUTH_AAID          ""
#define SECUREEXTAUTH_USER_VERIF    0x00 /* USER_VERIFY_NONE 0x00 */
#define DEVICEHEALTHAUTH_APP_NAME   "dhsecapp"
#define DEVICEHEALTHAUTH_AAID       ""
#define DEVICEHEALTHAUTH_USER_VERIF 0x00 /* USER_VERIFY_NONE 0x00 */
#define AUTH_TYPE                   0x0020 /* Expects TAG_APPID as arg (0x0020) */
#define CONTENT_TYPE_PNG            "image/png"
#define CONTENT_TYPE_TEXT           "text/plain"

#define QSAPP_PNG_DISPLAY_W 1600 /* FLUID_PANEL_8994_W */
#define QSAPP_PNG_DISPLAY_H 2704 /* FLUID_PANEL_8994_H */

// {48B07A18-A142-4517-B041-5EB426472FF6}
#define COOKIE { 0x48b07a18, 0xa142, 0x4517, { 0xb0, 0x41, 0x5e, 0xb4, 0x26, 0x47, 0x2f, 0xf6 } }

#define TL_SFS_ROOT "/persist/data/fidocrypto/"

/*lint -esym(506,g_config) */
fido_config_t  g_fido_config = {
  FIDO_CRYPTO_VERSION_MAJOR,
  FIDO_CRYPTO_VERSION_MINOR,
  COOKIE,
  0, /**< useSecureUI */
  1000, /**< minimum_time_on_display */
  QSAPP_PNG_DISPLAY_W, /**< displayW */
  QSAPP_PNG_DISPLAY_H, /**< displayH */
  PROVISIONING_AGENT_APP_NAME,
  0, /**< surrogateAttestation */
  1, /**< uvtVersion */
  32, /**< nonceLen */
  0, /**< sessionInKHAccessToken */
  {0x0103, 0x0105, 0x0181, 0x2102, 0x0200},
  {
    {
      SAMPLEAUTH_APP_NAME,
      1,
      1, /**< allowReprovisioning */
      0, /**< lifespan */
      SAMPLEAUTH_AAID,
      AUTH_TYPE,
      MATCHER_PROTECTION_TEE,
      1, /**< useBiolib */
      0, /**< secureDisplayAuthToken */
      0, /**< secureDisplayJointTokens */
      SAMPLEAUTH_USER_VERIF,
      1, /**< useTLoc */
      0, /**< forceLoc */
      CONTENT_TYPE_TEXT,
      {0}
    },
    {
      FINGERPRINT_APP_NAME,
      1,
      0, /**< allowReprovisioning */
      10000, /**< lifespan */
      FINGERPRINT_AAID,
      AUTH_TYPE,
      MATCHER_PROTECTION_TEE,
      1, /**< useBiolib */
      0, /**< secureDisplayAuthToken */
      0, /**< secureDisplayJointTokens */
      FINGERPRINT_USER_VERIF,
      1, /**< useTLoc */
      0, /**< forceLoc */
      CONTENT_TYPE_TEXT,
      {0}
    },
    {
      NS_IRISAUTH_APP_NAME,
      1,
      1, /**< allowReprovisioning */
      0, /**< lifespan */
      NS_IRISAUTH_AAID,
      AUTH_TYPE,
      MATCHER_PROTECTION_SOFTWARE,
      0, /**< useBiolib */
      0, /**< secureDisplayAuthToken */
      0, /**< secureDisplayJointTokens */
      NS_IRISAUTH_USER_VERIF,
      1, /**< useTLoc */
      0, /**< forceLoc */
      CONTENT_TYPE_TEXT,
      {0}
    },
    {
      NS_SAMPLEAUTH_APP_NAME,
      1,
      1, /**< allowReprovisioning */
      0, /**< lifespan */
      NS_SAMPLEAUTH_AAID,
      AUTH_TYPE,
      MATCHER_PROTECTION_SOFTWARE,
      0, /**< useBiolib */
      0, /**< secureDisplayAuthToken */
      0, /**< secureDisplayJointTokens */
      NS_SAMPLEAUTH_USER_VERIF,
      1, /**< useTLoc */
      0, /**< forceLoc */
      CONTENT_TYPE_PNG,
      {0}
    },
    {
      SAMPLEAUTH_APP_NAME,
      1,
      1, /**< allowReprovisioning */
      0, /**< lifespan */
      SAMPLEAUTH_AAID,
      AUTH_TYPE,
      MATCHER_PROTECTION_TEE,
      0, /**< useBiolib */
      0, /**< secureDisplayAuthToken */
      0, /**< secureDisplayJointTokens */
      SAMPLEAUTH_USER_VERIF,
      1, /**< useTLoc */
      0, /**< forceLoc */
      CONTENT_TYPE_TEXT,
      {0}
    },
    {
      SAMPLEEXTAUTH_APP_NAME,
      1,
      1, /**< allowReprovisioning */
      0, /**< lifespan */
      SAMPLEEXTAUTH_AAID,
      AUTH_TYPE,
      MATCHER_PROTECTION_SOFTWARE,
      0, /**< useBiolib */
      0, /**< secureDisplayAuthToken */
      0, /**< secureDisplayJointTokens */
      SAMPLEEXTAUTH_USER_VERIF,
      0, /**< useTLoc */
      0, /**< forceLoc */
      CONTENT_TYPE_TEXT,
      {0}
    },
    {
      SECUREEXTAUTH_APP_NAME,
      1,
      1, /**< allowReprovisioning */
      0, /**< lifespan */
      SECUREEXTAUTH_AAID,
      AUTH_TYPE,
      MATCHER_PROTECTION_TEE,
      0, /**< useBiolib */
      0, /**< secureDisplayAuthToken */
      0, /**< secureDisplayJointTokens */
      SECUREEXTAUTH_USER_VERIF,
      0, /**< useTLoc */
      0, /**< forceLoc */
      CONTENT_TYPE_TEXT,
      {0}
    },
    {
      DEVICEHEALTHAUTH_APP_NAME,
      1,
      1, /**< allowReprovisioning */
      0, /**< lifespan */
      DEVICEHEALTHAUTH_AAID,
      AUTH_TYPE,
      MATCHER_PROTECTION_TEE,
      0, /**< useBiolib */
      0, /**< secureDisplayAuthToken */
      0, /**< secureDisplayJointTokens */
      DEVICEHEALTHAUTH_USER_VERIF,
      0, /**< useTLoc */
      0, /**< forceLoc */
      CONTENT_TYPE_TEXT,
      {0}
    },
  },
  TL_SFS_ROOT, /* sfsRoot */
};


