#ifndef HAP_MEM_H
#define HAP_MEM_H
/*==============================================================================
  Copyright (c) 2012-2013 Qualcomm Technologies, Inc.
  All rights reserved. Qualcomm Proprietary and Confidential.
==============================================================================*/

#include "AEEStdDef.h"

#ifdef __cplusplus
extern "C" {
#endif

#define HAP_MEM_CONTEXT_DEFAULT (void*)0

int HAP_cx_malloc(void* pctx, uint32 bytes, void** pptr);
int HAP_cx_free(void* pctx, void* ptr);

static inline int HAP_malloc(uint32 bytes, void** pptr)
{
  return HAP_cx_malloc(HAP_MEM_CONTEXT_DEFAULT, bytes, pptr);
}

static inline int HAP_free(void* ptr)
{
  return HAP_cx_free(HAP_MEM_CONTEXT_DEFAULT, ptr);
}

struct HAP_mem_stats {
   uint64 bytes_free; /** number of bytes free from all the segments,
                        * may not be available for a single alloc
                        */
   uint64 bytes_used; /** number of bytes used */
   uint64 seg_free;   /** number of segments free */
   uint64 seg_used;   /** number of segments used */
   uint64 min_grow_bytes; /** minimum number of bytes to grow the heap by when creating a new segment */
};

/**
 * Get the current statistics from the heap.
 * 
 * @param stats, the stats structure
 * @retval, 0 on success
 */
int HAP_mem_get_stats(struct HAP_mem_stats *stats);

/**
 * Set the minimum and maximum grow size.
 *
 * The heap will grow the memeory by at least min and at most max.
 *
 * @param min, minimum bytes to grow the heap by when requesting a new segment
 * @param max, maximum bytes to grow the heap by when requesting a new segment
 * @retval, 0 on success
 *
 * min_grow_bytes = MIN(max,MAX(min,min_grow_bytes));
 *
 * The value will be aligned to the next 1MB boundary.
 *
 * actual_grow_bytes = min_grow_bytes + request_size
 * actual_grow_bytes = ALIGN(actual_grow_bytes,0x100000)
 *
 * default is HAP_mem_set_grow_size(0x100000/2, MAX_UINT64);
 */
int HAP_mem_set_grow_size(uint64 min, uint64 max);


#ifdef __cplusplus
}
#endif

#endif // HAP_MEM_H

