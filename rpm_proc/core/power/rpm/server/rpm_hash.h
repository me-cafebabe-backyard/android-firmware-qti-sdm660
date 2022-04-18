/*==============================================================================

FILE:        rpm_hash.h

DESCRIPTION: Hashing functions for RPM resource state

      Copyright (c) 2011-2012 Qualcomm Technologies Incorporated.
               All Rights Reserved.
         QUALCOMM Proprietary and Confidential

$Header: //components/rel/rpm.bf/1.8/core/power/rpm/server/rpm_hash.h#2 $
$Author: pwbldsvc $
$DateTime: 2017/03/15 09:06:36 $

==============================================================================*/

#ifndef RPM_HASH_H
#define RPM_HASH_H

#include <stdint.h>
#include "rpm.h"
#include "rpm_config.h"
#include "rpm_global_hash.h"

#ifdef __cplusplus
extern "C" {
#endif

extern uint32_t rpm_system_hash;
#ifdef __clang__
inline static unsigned __ror(unsigned v, unsigned amt) {
  unsigned ret;
  __asm__("ror %[Rd], %[Rm], %[Rs]" : [Rd] "=r"(ret) : [Rm] "r" (v), [Rs] "r" (amt));
  return ret;
}
#endif
//
// Unrolled variants
//
#define rpm_hash64(x,y) rpm_hash64s(0,(x),(y))
uint32_t rpm_hash64s(uint32_t seed, uint32_t val1, uint32_t val2) __pure;

uint32_t rpm_resource_hash(uint32_t hash, ResourceData *r, uint32_t length, const void *oldValue, const void *newValue);

#ifdef __cplusplus
};
#endif // __cplusplus

#endif // RPM_HASH_H

