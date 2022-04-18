#ifndef QSEE_MMSS_HDCP2P2_H
#define QSEE_MMSS_HDCP2P2_H

/*============================================================================
Copyright (c) 2015-2016 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
=========================================================================== */

/*=========================================================================
                              Edit History

  $Header: //components/rel/core.tz/1.0.7.1/securemsm/trustzone/qsee/include/qsee_mmss_hdcp2p2.h#1 $
  $DateTime: 2020/01/14 12:35:09 $
  $Author: pwbldsvc $


when       who     what, where, why
--------   ---     --------------------------------------------------------
06/29/16   sh      add mink api internal function qsee_write_key_riv_enable()
04/06/15   sk      Initial Revision

=========================================================================== */
#include <comdef.h>
#include <stdint.h>
#include <stdbool.h>

typedef enum {
    HDCP_VERSION_1_4 = 0x2001,
    HDCP_VERSION_2_2 = 0x2002
} qsee_hdcp_version_t;

typedef enum {
    HDCP_TX_HDMI = 0x8001,
    HDCP_TX_DP   = 0x8002
} qsee_hdcp_device_t;

/*
  Set/reset and enable/disable the key and riv for hdcp-hdmi
  Parameters:
    uKs           - (in) key to write on HDMI h/w in HDCP2.2 registers
    uKsLen        - (in) length of key (we could hardcode the length of uKs[uKsLen] to 16 bytes as per HDCP 2.2 spec)
    uRiv          - (in) random IV to set to HDCP h/w
    uRivLev       - (in) length of random IV (we could hardcode the length of uRiv[uRivLen] to 8 bytes as per HDCP 2.2 spec)
    enc_enable    - (in) 1 for enable; 0 for disable
*/
int qsee_write_hdcp2p2_key_riv_enable(const uint8 *uKs, size_t uKsLen, const uint8 *uRiv, size_t uRivLen, uint8 enc_Enable);


/* 
  Read HDCP minimum encryption level
  Parameters:
    min_enc_level   - (out) minimum enc-level
*/
int qsee_read_hdcp2p2_min_encryption_level(uint8* min_enc_level);

/* 
  Write HDCP minimum encryption level
  Parameters:
    min_enc_level        - (in) minimum enc-level
*/
int qsee_write_hdcp2p2_min_encryption_level(uint8 min_enc_level);

/*
  Set/reset and enable/disable the key and riv for hdcp-hdmi
  Parameters:
    hdcpVersion   - (in) HDCP version to write key
    deviceType    - (in) HDCP HW type(hdmi,dp) to write key
    enableEncryption- (in) true for enable; false for disable
    key           - (in) key to write on H/W in HDCP registers
    keyLen        - (in) length of key
    riv           - (in) random IV to set to HDCP h/w
    rivLen        - (in) length of random IV   
*/
int32_t qsee_write_hdcp_key_riv_enable(const uint32_t hdcpVersion,
                                       const uint32_t deviceType,
                                       const bool enableEncryption,
                                       const void *key, size_t keyLen,
                                       const void *riv, size_t rivLen);

#endif /*QSEE_MMSS_HDCP2P2_H*/

