#ifndef __IHDCPENCRYPTION_H
#define __IHDCPENCRYPTION_H

// AUTOGENERATED FILE: DO NOT EDIT

#include <stdint.h>
#include "object.h"

// Copyright (c) 2016 Qualcomm Technologies, Inc.  All Rights Reserved.

// Qualcomm Technologies Proprietary and Confidential.

/**
 * @brief
 * Hdcp Encryption interface controls hardware blocks that implement HDCP
 * ecnryption (HDMI, DP, ...) and keeps track of the minimum encryption level
 * given by the DRM policy.
 *
 */

#define IHdcpEncryption_HDCP_VERSION_14 UINT32_C(0x2001)
#define IHdcpEncryption_HDCP_VERSION_22 UINT32_C(0x2002)
#define IHdcpEncryption_HDCP_TXMTR_HDMI UINT32_C(0x8001)
#define IHdcpEncryption_HDCP_TXMTR_DP UINT32_C(0x8002)

#define IHdcpEncryption_ERROR_GENERIC INT32_C(10)
#define IHdcpEncryption_ERROR_HW_NOT_SUPPORTED INT32_C(11)
#define IHdcpEncryption_ERROR_HW_NOT_AVAILABLE INT32_C(12)
#define IHdcpEncryption_ERROR_HW_CLOCK_OFF INT32_C(13)
#define IHdcpEncryption_ERROR_BAD_PARAMETER INT32_C(14)
#define IHdcpEncryption_ERROR_VERSION_NOT_SUPPORTED INT32_C(15)

#define IHdcpEncryption_OP_enable 0
#define IHdcpEncryption_OP_disable 1

static inline int32_t
IHdcpEncryption_release(Object self)
{
  return Object_invoke(self, Object_OP_release, 0, 0);
}

static inline int32_t
IHdcpEncryption_retain(Object self)
{
  return Object_invoke(self, Object_OP_retain, 0, 0);
}

static inline int32_t
IHdcpEncryption_enable(Object self, uint32_t hdcpVersion_val, uint32_t deviceType_val, const void *key_ptr, size_t key_len, const void *randomIV_ptr, size_t randomIV_len)
{
  ObjectArg a[3];
  struct {
    uint32_t m_hdcpVersion;
    uint32_t m_deviceType;
  } i;
  a[0].b = (ObjectBuf) { &i, 8 };
  i.m_hdcpVersion = hdcpVersion_val;
  i.m_deviceType = deviceType_val;
  a[1].bi = (ObjectBufIn) { key_ptr, key_len * 1 };
  a[2].bi = (ObjectBufIn) { randomIV_ptr, randomIV_len * 1 };

  return Object_invoke(self, IHdcpEncryption_OP_enable, a, ObjectCounts_pack(3, 0, 0, 0));
}

static inline int32_t
IHdcpEncryption_disable(Object self, uint32_t hdcpVersion_val, uint32_t deviceType_val)
{
  ObjectArg a[1];
  struct {
    uint32_t m_hdcpVersion;
    uint32_t m_deviceType;
  } i;
  a[0].b = (ObjectBuf) { &i, 8 };
  i.m_hdcpVersion = hdcpVersion_val;
  i.m_deviceType = deviceType_val;

  return Object_invoke(self, IHdcpEncryption_OP_disable, a, ObjectCounts_pack(1, 0, 0, 0));
}


#endif /* __IHDCPENCRYPTION_H */