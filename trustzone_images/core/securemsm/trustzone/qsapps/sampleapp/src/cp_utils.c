
/**
@file security_stream_checker.c
@brief No description
*/

/*===========================================================================
   Copyright (c) 2014 by QUALCOMM Technologies, Incorporated.  All Rights Reserved.
   Qualcomm Confidential and Proprietary
===========================================================================*/

/*===========================================================================

                            EDIT HISTORY FOR FILE


when       who      what, where, why
--------   ---      ------------------------------------
02/14/14    wt      Created

===========================================================================*/

/*===========================================================================
                           INCLUDE FILES
===========================================================================*/
#include "cp_utils.h"
#include "qsee_alias.h"
#include <ACCommon.h>

/*===========================================================================
                              DEFINES
===========================================================================*/


int cp_utils_tag_mem(uint32 tag, tz_mem_array_s_t *bufferHandle, uint32 buffLen)
{
  int ret = 0;

#ifdef USES_NO_CP 

  uintptr_t start;
  uintptr_t end;
  uint8* bufferPtr = NULL;
  uint32 size = 0;
  uint32 segNum = 0;

  TZ_APPS_LOG( TZ_LOG_MSG_DEBUG,"cp_utils_tag_mem is starting...");

  do
  {
    //check params
    if(tag >= AC_VM_MAX || NULL == bufferHandle || 0 == buffLen)
    {
      qsee_log(QSEE_LOG_MSG_ERROR, "%s Error: Invalid paramters!", __FUNCTION__);
      ret = -1;
      break;
    }

    bufferPtr = (uint8*)(((bufferHandle->_tz_mem_seg)[segNum])._address);
    size = ((bufferHandle->_tz_mem_seg)[segNum])._size;

    //if size is 0, there is only one segment, use buffLen for length
    if(0 == size)
    {
      start = (uintptr_t)bufferPtr;
      end = (uintptr_t)(bufferPtr + buffLen);
      ret = qsee_tag_mem(tag, start, end);
      if(ret)
      {
        qsee_log(QSEE_LOG_MSG_ERROR,"%s Error: qsee_tag_mem failed. Returned %d", __FUNCTION__, ret);
        break;
      }
      break;
    }

    //else loop through memory segments and tag them
    do
    {
      //tag memory
      start = (uintptr_t)bufferPtr;
      end = (uintptr_t)(bufferPtr + size);
      ret = qsee_tag_mem(tag, start, end);

      if(ret)
      {
        qsee_log(QSEE_LOG_MSG_ERROR, "%s Error: qsee_tag_mem failed. Returned %d", __FUNCTION__, ret);
        break;
      }

      //update segment index and ptrs
      segNum++;
      bufferPtr = (uint8*)(((bufferHandle->_tz_mem_seg)[segNum])._address);
      size = ((bufferHandle->_tz_mem_seg)[segNum])._size;

      //break when size is 0 or if address is garbage - no more segments to copy to
      if(0 == size || 0 >= bufferPtr)
      {
        break;
      }

    } while(1);
    //end of tag segment loop

  } while(0);
  
  if(ret)
  {
    qsee_log(QSEE_LOG_MSG_ERROR, "%s Error: Failed. Returning %d", __FUNCTION__, ret);
  }

#else
  ret = -1;
  qsee_log(QSEE_LOG_MSG_ERROR, "%s:This feature is not supported on external builds",__FUNCTION__);
#endif

  qsee_log(QSEE_LOG_MSG_ERROR,"%s Returns %d", __FUNCTION__, ret);
  return ret;
}
