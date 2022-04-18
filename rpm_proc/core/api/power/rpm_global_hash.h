/*==============================================================================

FILE:        rpm_global_hash.h

DESCRIPTION: Hashing functions for RPM resource state

      Copyright (c) 2011-2014 Qualcomm Technologies, Inc.
               All Rights Reserved.
         QUALCOMM Proprietary and Confidential

$Header: //components/rel/rpm.bf/1.8/core/api/power/rpm_global_hash.h#1 $
$Author: pwbldsvc $
$DateTime: 2016/11/03 00:13:13 $

==============================================================================*/

#ifndef RPM_GLOBAL_HASH_H
#define RPM_GLOBAL_HASH_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

uint32_t rpm_hash(uint32_t length, const void *data);

#ifdef __cplusplus
};
#endif // __cplusplus

#endif // RPM_GLOBAL_HASH_H
