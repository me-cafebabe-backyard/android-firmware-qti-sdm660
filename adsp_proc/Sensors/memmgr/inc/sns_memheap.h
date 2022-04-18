#ifndef SNS_MEMHEAP_H
#define SNS_MEMHEAP_H
/*============================================================================
  @file sns_memheap.h

  @brief
  Defines Sensors heap interfaces

  <br><br>

  DEPENDENCIES:

  Copyright (c) 2014-2016 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
  ============================================================================*/

/*=====================================================================
                       INCLUDES
=======================================================================*/
#include <stdint.h>
#include <stdbool.h>

/*=====================================================================
                          FUNCTIONS
=======================================================================*/

sns_err_code_e sns_heap_create(void);
sns_err_code_e sns_heap_destroy(void);
void* sns_heap_malloc(uint32_t size);
void sns_heap_free(void *ptr);

#endif /* SNS_MEMHEAP_H */
