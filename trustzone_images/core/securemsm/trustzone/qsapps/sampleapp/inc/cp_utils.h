#ifndef _CP_UTILS_H_
#define _CP_UTILS_H_

/*===========================================================================
   Copyright (c) 2014 by QUALCOMM Technologies, Incorporated.  All Rights Reserved.
   Qualcomm Confidential and Proprietary
===========================================================================*/

/*===========================================================================

                      EDIT HISTORY FOR FILE

when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
02/14/14    wt     Created.

===========================================================================*/

/*===========================================================================

                     INCLUDE FILES FOR MODULE

===========================================================================*/
#include <comdef.h>
#include "stdlib.h"
#include "qsee_core.h"
#include "IxErrno.h"
#include "qsee_log.h"
#include "app_content_protection.h"

#define TZ_OUT_BUF_MAX                512

//TZ send command structures
typedef struct tz_cp_tag_mem_req_s
{
  /** First 4 bytes should always be command id */
  uint32                          cmd_id;
  uint32                          tag;
  tz_mem_array_s_t                secBufferHandle;
  uint32                          secBuffLength;
} __attribute__ ((packed)) tz_cp_tag_mem_req_t;

typedef struct tz_cp_tag_mem_rsp_s
{
  /** First 4 bytes should always be command id */
  uint32                          cmd_id;
  long                            ret;
} __attribute__ ((packed)) tz_cp_tag_mem_rsp_t;


int cp_utils_tag_mem(uint32 tag, tz_mem_array_s_t *bufferHandle, uint32 buffLen);

#endif /* _CP_UTILS_H_ */


