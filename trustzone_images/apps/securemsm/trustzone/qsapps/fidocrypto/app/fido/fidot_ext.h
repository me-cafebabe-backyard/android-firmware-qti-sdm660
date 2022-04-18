/*
 * Copyright (c) 2015 Qualcomm Technologies, Inc. All Rights Reserved.
 * Qualcomm Technologies Proprietary and Confidential.
*/

#pragma once

/** Definitions FIDO extensions
 */

/** Multi Exact Fingerprint
 *
 * Extension included in UVT:
 * TAG    (2): AFI_RAW_USER_VERIFICATION_INDEX
 * LEN    (2): n <= 32
 * DATA   (n): raw user verification index
 *
 * Extension included in TLV payload (Register / Sign)
 * TAG    (2): AFI_USER_VERIFICATION_INDEX
 * LEN    (2): 32
 * DATA  (32): SHA256(keyID | raw index)
 * */
#define AFI_RAW_USER_VERIFICATION_INDEX   0x0103
#define AFI_USER_VERIFICATION_INDEX       0x0104

/** User Verification State
 *
 * Extension included in UVT:
 * TAG    (2): AFI_RAW_USER_VERIFICATION_STATE
 * LEN    (2): n <= 32
 * DATA   (n): raw user verification state
 *
 * Extension included in TLV payload (Register / Sign)
 * TAG    (2): AFI_USER_VERIFICATION_STATE
 * LEN    (2): 32
 * DATA  (32): SHA256(keyID | raw state)
 * */
#define AFI_RAW_USER_VERIFICATION_STATE   0x0105
#define AFI_USER_VERIFICATION_STATE       0x0106

/** Authenticator (TA) version
 *
 * Extension included in UVT:
 * TAG    (2): TA_AUTHENTICATOR_VERSION
 * LEN    (2): n = 1
 * DATA   (1): single byte version
 *
 * Data from the extension will be merged as the MSB
 * of the authenticator version in TAG_ASSERTION_INFO
 * */
#define TA_AUTHENTICATOR_VERSION          0x0181

/** Trusted Location
 *            | A | B | C | C |
 * ----------------------------
 * useTloc    | 0 | 1 | 1 | 1 | <-- fidocrypto config, per auth
 * forceLoc   | X | 0 | 1 | 0 | <-- fidocrypto config, per auth
 * hlosTloc   | X | 0 | X | 1 | <-- from HLOS, via FIDOCryptoService

 *
 * A: TAG_LOCATION not present
 * B: TAG_LOCATION present, length=0
 * C: TAG_LOCATION present, followed by sequence of {TAG_LOCATION_FIX}
 *
 * 1. (optional) Extension included in TLV payload (Register / Sign)
 * TAG    (2): TAG_LOCATION
 * LEN    (2): n ( = X * 57)
 * 1.1 (Optional sequence of the following TAG)
 * TAG    (2): TAG_LOCATION_FIX
 * LEN    (2): n (= 53)
 * DATA   (1): 1=trusted, 0=untrusted
 * DATA   (1): latitude valid: 1=valid, 0=not valid
 * DATA   (8): latitude, [-90.0...90.0], normalized to [0...UINT64_MAX]
 * DATA   (1): longitude valid: 1=valid, 0=not valid
 * DATA   (8): longitude, [-180.0...180.0], normalized to [0...UINT64_MAX]
 * DATA   (1): horizontal accuracy valid: 1=valid, 0=not valid
 * DATA   (4): horizontal accuracy, in m
 * DATA   (1): technology valid: 1=valid, 0=not valid
 * DATA   (4): technology used for the fix, as a bitmask (see note below)
 * DATA   (1): time valid: 1=valid, 0=not valid
 * DATA   (8): UTC timestamp, in milliseconds since 1 Jan 1970
 * DATA   (1): altitude  valid: 1=valid, 0=not valid
 * DATA   (4): altitude, in m
 * DATA   (1): bearing  valid: 1=valid, 0=not valid
 * DATA   (4): bearing, [0...359.999], normalized to [0...UINT32_MAX]
 * DATA   (1): speed  valid: 1=valid, 0=not valid
 * DATA   (4): speed, in m/s
 *
 * @note Technologies used for the fix:
 * SATELLITE                = (0x00000001)
 * CELLID                   = (0x00000002)
 * WIFI                     = (0x00000004)
 * SENSORS                  = (0x00000008)
 * REFERENCE_LOCATION       = (0x00000010)
 * INJECTED_COARSE_POSITION = (0x00000020)
 * AFLT                     = (0x00000040)
 * HYBRID                   = (0x00000080)
 * */
#define TAG_LOCATION        0x11A0
#define TAG_LOCATION_FIX    0x01A1

