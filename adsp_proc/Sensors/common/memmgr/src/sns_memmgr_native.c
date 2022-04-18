/*============================================================================
  @file sns_memmgr_native.c

  @brief
  Implements SNS memory manager interfaces.

  Copyright (c) 2016 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
  ===========================================================================*/

/*===========================================================================
  Include Files
  ===========================================================================*/
#include <stdbool.h>
#include <string.h>
#include "stdlib.h"
#include "sns_memmgr.h"

/*===========================================================================
  Public Function Definitions
  ===========================================================================*/

void* SNS_OS_MEMCOPY(void *dest, const void *source, size_t size)
{
  return memcpy(dest, source, size);
}

void* SNS_OS_MEMSET(void *ptr, int value, size_t size)
{
  return memset(ptr, value, size);
}

void* SNS_OS_MEMZERO(void *ptr, size_t size)
{
  return memset(ptr, 0, size);
}

int SNS_OS_MEMCMP(const void *ptr1, const void *ptr2, size_t size)
{
  return memcmp(ptr1, ptr2, size);
}

size_t SNS_OS_MEMSCPY(void *dest, size_t dest_size, const void *source, size_t source_size)
{
  memcpy(dest, source, dest_size);
  return dest_size;
}

void* SNS_OS_MALLOC(uint8_t module, uint32_t size)
{
  return memset(malloc(size), 0, size);

}

void* SNS_OS_SENSOR_HEAP_MALLOC(uint8_t module, uint32_t size)
{
  return memset(malloc(size), 0, size);
}

void* SNS_OS_U_MALLOC(uint8_t module, uint32_t size)
{
  return memset(malloc(size), 0, size);
}

void* SNS_OS_ANY_MALLOC(uint8_t module, uint32_t size)
{
  return memset(malloc(size), 0, size);
}

bool SNS_OS_IS_UIMG_ADDR(void const *addr)
{
  return false;
}

void SNS_OS_FREE(void *ptr)
{
  free(ptr);
}

void* sns_memmgr_int_any_malloc(uint8_t module, uint32_t size, uint32_t calldepth)
{
  return memset(malloc(size), 0, size);
}

sns_err_code_e sns_memmgr_lowmem_cb_register(sns_memmgr_lowmem_cb_t cb)
{
  return SNS_SUCCESS;
}

sns_err_code_e sns_heap_init(void)
{
  return SNS_SUCCESS;
}
