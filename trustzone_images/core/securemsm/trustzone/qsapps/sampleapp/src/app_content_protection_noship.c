/*===========================================================================
  Copyright (c) 2011-2015 Qualcomm Technologies, Incorporated.
  All Rights Reserved.
  Qualcomm Technologies Confidential and Proprietary
===========================================================================*/

/*===========================================================================

                      EDIT HISTORY FOR FILE

  $Header: //components/rel/core.tz/1.0.7.1/securemsm/trustzone/qsapps/sampleapp/src/app_content_protection_noship.c#1 $

when       who    what, where, why
--------   ---    ----------------------------------------------------------
01/06/15   vv     added qsee_is_s_tag_area check with modified tags
05/08/15   cz     Removed qsee_is_s_tag_area check per MM Shalaj request
03/05/15   ck     Allow coping smaller size as much as output buffer size.
01/29/15   kr     Fixed CP COPY API bugs
02/19/14   wt     Created

===========================================================================*/

/*===========================================================================

                     INCLUDE FILES FOR MODULE

===========================================================================*/
/** @addtogroup Content_Protection
  @} */

#include "app_content_protection.h"
#include <comdef.h>
#include <ACCommon.h>
SampleClientResult Content_Protection_Copy_SecureToNonsecure
(
  const uint8       *nonSecBuffer,
  const uint32       nonSecBufferLength,
  tz_mem_array_s_t  *secBufferHandle,
  uint32             secBufferOffset,
  uint32            *secBufferLength
)
{
  SampleClientResult status              = SAMPLE_CLIENT_SUCCESS;
  
#ifdef USES_NO_CP
  
  uint32             size                = 0;
  uint8*             secBufferPtr        = NULL;
  uint8*             nonSecBufferPtr     = (uint8*)(uintnt)nonSecBuffer;
  uint32             segNum              = 0;
  uint32             sizeCopied          = 0;
  uint32             spaceLeft           = 0;

  TZ_APPS_LOG( TZ_LOG_MSG_DEBUG,"TZ Content_Protection_Copy_SecureToNonsecure is starting...");

  do
  {
    //error checking
    if(NULL == nonSecBuffer || 0 == nonSecBufferLength || NULL == secBufferHandle || NULL == secBufferLength)
    {
      TZ_APPS_LOG( TZ_LOG_MSG_ERROR, "%s Error: Invalid parameters.",
                  __FUNCTION__);
      status = SAMPLE_CLIENT_ERROR_INVALID_PARAMS;
      break;
    }
    
    /* check if the nonSecBuffer memory is not protected */
    if(qsee_is_ns_range(nonSecBuffer,nonSecBufferLength) == FALSE)
    {
      TZ_APPS_LOG( TZ_LOG_MSG_ERROR, "%s Error: trying to access secure memory region.",
                  __FUNCTION__);
      status = SAMPLE_CLIENT_ERROR_SNS_COPY_FAILED;
      break;
    }

    //only copy as much as output (non-secure buffer) size
    *secBufferLength = nonSecBufferLength;

    //get address and size of memory segment to copy
    secBufferPtr = (uint8*)(uintnt)(((secBufferHandle->_tz_mem_seg)[segNum])._address);
    size = ((secBufferHandle->_tz_mem_seg)[segNum])._size;

    //0 size means only one contiguous buffer
    if(0 == size)
    {
      /* check if the secBuffer memory is protected */
      if(qsee_is_s_tag_area(AC_VM_CP_BITSTREAM, (uint32)secBufferPtr, (uint32)(secBufferPtr + *secBufferLength)) == FALSE &&
         qsee_is_s_tag_area(AC_VM_CP_NON_PIXEL, (uint32)secBufferPtr, (uint32)(secBufferPtr + *secBufferLength)) == FALSE &&
         qsee_is_s_tag_area(AC_VM_CP_PIXEL, (uint32)secBufferPtr, (uint32)(secBufferPtr + *secBufferLength)) == FALSE)
      {
        TZ_APPS_LOG( TZ_LOG_MSG_ERROR, "Error: Failed is s tag area check.");
        status = SAMPLE_CLIENT_ERROR_NSS_COPY_FAILED;
        break;
      }
      
      //copy entire secure buff into non secure buff
      status = mem_seg_copy(nonSecBufferPtr, (uint32)nonSecBufferLength, (uint8*)(uintnt)secBufferPtr, *secBufferLength);
      if(status != SAMPLE_CLIENT_SUCCESS)
      {
        TZ_APPS_LOG(TZ_LOG_MSG_ERROR, "%s Error: copy to non-secure buffer failed! Returned %ld", __FUNCTION__, status);
        status = SAMPLE_CLIENT_ERROR_SNS_COPY_FAILED;
      }
      break;
    }

    //size was not 0. Need to copy multiple memory segments
    do
    {
      //break when size is 0 or if address is garbage - no more segments to copy
      if(0 == size || 0 >= secBufferPtr)
      {
        break;
      }

      //make sure we're not copying past our destination buffer's end
      sizeCopied = nonSecBufferPtr - nonSecBuffer;
      spaceLeft = nonSecBufferLength - sizeCopied;
      if(spaceLeft == 0)
      {
        TZ_APPS_LOG(TZ_LOG_MSG_ERROR, "No space left.");
        break;
      }
      TZ_APPS_LOG( TZ_LOG_MSG_DEBUG,"copy multiple memory segments, size=%d,sizeCopied=%d,spaceLeft=%d", size, sizeCopied, spaceLeft);
      if(sizeCopied >= nonSecBufferLength)
      {
        TZ_APPS_LOG(TZ_LOG_MSG_ERROR, "Error: Trying to copy past end of non-secure buffer. Failed!");
        status = SAMPLE_CLIENT_ERROR_SNS_COPY_FAILED;
        break;
      }

      if(size > spaceLeft)
      {
        TZ_APPS_LOG(TZ_LOG_MSG_ERROR, "Truncating copy size:%d to %d as remained buffer", size, spaceLeft);
        size = spaceLeft;
      }

      /* check if the secBuffer memory is protected */
      if(qsee_is_s_tag_area(AC_VM_CP_BITSTREAM, (uint32)secBufferPtr, (uint32)(secBufferPtr + size)) == FALSE &&
         qsee_is_s_tag_area(AC_VM_CP_NON_PIXEL, (uint32)secBufferPtr, (uint32)(secBufferPtr + size)) == FALSE &&
         qsee_is_s_tag_area(AC_VM_CP_PIXEL, (uint32)secBufferPtr, (uint32)(secBufferPtr + size)) == FALSE)
      {
        TZ_APPS_LOG( TZ_LOG_MSG_ERROR, "Error: Failed is s tag area check.");
        status = SAMPLE_CLIENT_ERROR_NSS_COPY_FAILED;
        break;
      }
      
      //copy segment of secure buff into non secure buff
      status = mem_seg_copy(nonSecBufferPtr, (uint32)spaceLeft, (uint8*)(uintnt)secBufferPtr, size);
      if(status != SAMPLE_CLIENT_SUCCESS)
      {
        TZ_APPS_LOG(TZ_LOG_MSG_ERROR, "%s Error: copy to non-secure buffer failed! Returned %ld", __FUNCTION__, status);
        status = SAMPLE_CLIENT_ERROR_SNS_COPY_FAILED;
        break;
      }

      //update destination pointer and segment number
      nonSecBufferPtr += size;
      segNum++;

      //don't go past max number of segments
      if(segNum >= TZ_OUT_BUF_MAX)
      {
        TZ_APPS_LOG(TZ_LOG_MSG_DEBUG, "Copied from maximum number of segments!");
        break;
      }

      //get next address and size of memory segment
      secBufferPtr = (uint8*)(uintnt)(((secBufferHandle->_tz_mem_seg)[segNum])._address);
      size = ((secBufferHandle->_tz_mem_seg)[segNum])._size;

    }while(1);
    //end of copy segments loop
   
  }while(0);

  if(status != SAMPLE_CLIENT_SUCCESS)
  {
    TZ_APPS_LOG(TZ_LOG_MSG_ERROR, "%s failed and returns %d!", __FUNCTION__, status);
  }

#else
  status = SAMPLE_CLIENT_ERROR_FEATURE_NOT_SUPPORTED;
  TZ_APPS_LOG(TZ_LOG_MSG_ERROR, "This feature is not supported on external builds");
#endif

  TZ_APPS_LOG(TZ_LOG_MSG_DEBUG,"%s Returns %d", __FUNCTION__, status);
  return status;
}
