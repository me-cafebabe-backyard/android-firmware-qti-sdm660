/*===========================================================================
  Copyright (c) 2011-2015 Qualcomm Technologies, Incorporated.
  All Rights Reserved.
  Qualcomm Technologies Confidential and Proprietary
===========================================================================*/

/*===========================================================================

                      EDIT HISTORY FOR FILE

  $Header: //components/rel/core.tz/1.0.7.1/securemsm/trustzone/qsapps/sampleapp/src/app_content_protection.c#1 $

when       who    what, where, why
--------   ---    ----------------------------------------------------------
05/08/15   cz     Changed tz_buf_seg address to 64 bits, and removed qsee_is_s_tag_area
                  check per MM Shalaj request
03/05/15   cz     Fix the issue: secure buffer is non-contiguous, need to check seg size
01/29/15   kr     Fixed CP COPY API bugs
09/04/14   ck     Added cache update calls
12/20/13   wt     Created

===========================================================================*/

/*===========================================================================

                     INCLUDE FILES FOR MODULE

===========================================================================*/
/** @addtogroup Content_Protection
  @} */

#include "app_content_protection.h"
#include "stdint.h" 
#include <comdef.h>

#define CHECK_INTEGER_OVERFLOW(a, b)                                           \
{                                                                              \
    if( sizeof(long) == 4 && (uint32)(a)>UINT32_MAX-(uint32)(b))               \
    {                                                                          \
      TZ_APPS_LOG(TZ_LOG_MSG_ERROR, "Error: Int overflow %d+%d",a,b);          \
      status = SAMPLE_CLIENT_ERROR_NSS_COPY_FAILED;                            \
    }                                                                          \
    if( sizeof(long) == 8 && (uint64)(a)>UINT64_MAX-(uint64)(b))               \
    {                                                                          \
      TZ_APPS_LOG(TZ_LOG_MSG_ERROR, "Error: Int overflow %d+%d",a,b);          \
      status = SAMPLE_CLIENT_ERROR_NSS_COPY_FAILED;                            \
    }                                                                          \
}

#define CHECK_INTEGER_UNDERFLOW(a, b)                                          \
{                                                                              \
    if((uint64)(a) < (uint64)(b))                                                              \
    {                                                                          \
      TZ_APPS_LOG(TZ_LOG_MSG_ERROR, "Error: Int underflow %d+%d",a,b);         \
      status = SAMPLE_CLIENT_ERROR_NSS_COPY_FAILED;                            \
    }                                                                          \
}

SampleClientResult mem_seg_copy(uint8* outBuff, uint32 outBuffLen, uint8* inBuff, uint32 inBuffLen)
{
  SampleClientResult status = SAMPLE_CLIENT_SUCCESS;
  int                ret    = 0;

  TZ_APPS_LOG( TZ_LOG_MSG_DEBUG,"TZ mem_seg_copy is starting...");

  do
  {
    //sanity check
    if(NULL == outBuff || NULL == inBuff || 0 >= outBuffLen || 0 >= inBuffLen)
    {
      TZ_APPS_LOG( TZ_LOG_MSG_ERROR, "%s Error: Invalid parameters!", __FUNCTION__);
      status = SAMPLE_CLIENT_ERROR_INVALID_PARAMS;
      break;
    }


    //register buffers for copying
    ret = qsee_register_shared_buffer(inBuff, inBuffLen);
    if(ret)
    {
      TZ_APPS_LOG( TZ_LOG_MSG_ERROR, "%s Error: qsee_register_shared_buffer for input buffer failed.", __FUNCTION__);
      TZ_APPS_LOG( TZ_LOG_MSG_ERROR, "ret = %d, inBuff  = %x, inBuffLen = %d",ret, inBuff, inBuffLen);
      status = SAMPLE_CLIENT_ERROR_MEM_SEG_COPY_FAILED;
      break;
    }
    ret = qsee_register_shared_buffer(outBuff, outBuffLen);
    if(ret)
    {
      TZ_APPS_LOG( TZ_LOG_MSG_ERROR, "%s Error: qsee_register_shared_buffer for output buffer failed.", __FUNCTION__);
      TZ_APPS_LOG( TZ_LOG_MSG_ERROR, "ret = %d, outBuff  = %x, outBuffLen = %d",ret, outBuff, outBuffLen);
      status = SAMPLE_CLIENT_ERROR_MEM_SEG_COPY_FAILED;
      break;
    }

    // prepare cache for secure read
    if ( qsee_prepare_shared_buf_for_secure_read(inBuff, inBuffLen) != 0 )
    {
      TZ_APPS_LOG(TZ_LOG_MSG_ERROR,
					"Error: qsee_prepare_shared_buf_for_secure_read failed! input=%p,inputlen=%d",
					inBuff,
					inBuffLen);
	  status = SAMPLE_CLIENT_ERROR_MEM_SEG_COPY_FAILED;
      break;
    }
    if ( qsee_prepare_shared_buf_for_secure_read(outBuff, outBuffLen) != 0 )
    {
      TZ_APPS_LOG(TZ_LOG_MSG_ERROR,
					"Error: qsee_prepare_shared_buf_for_secure_read failed! output=%p,outputlen=%d",
					outBuff,
					outBuffLen);
	  status = SAMPLE_CLIENT_ERROR_MEM_SEG_COPY_FAILED;
      break;
    }

    //copy
    ret = memscpy(outBuff, outBuffLen, inBuff, inBuffLen);

  }while(0);


  //flush cache
  if (qsee_prepare_shared_buf_for_nosecure_read(inBuff, inBuffLen) != 0 )
  {
    TZ_APPS_LOG(TZ_LOG_MSG_ERROR,
	  			"Error: qsee_prepare_shared_buf_for_nosecure_read input failed! input=%p,inputlen=%d",
	  			inBuff,
	  			inBuffLen);
    status = SAMPLE_CLIENT_ERROR_MEM_SEG_COPY_FAILED;
  }
  if (qsee_prepare_shared_buf_for_nosecure_read(outBuff, outBuffLen) != 0 )
  {
    TZ_APPS_LOG(TZ_LOG_MSG_ERROR,
	  			"qsee_prepare_shared_buf_for_nosecure_read output failed! output=%p,outputlen=%d",
	  			outBuff,
	  			outBuffLen);
    status = SAMPLE_CLIENT_ERROR_MEM_SEG_COPY_FAILED;
  }

  //deregister buffers
  ret = qsee_deregister_shared_buffer(inBuff);
  if(ret)
  {
    TZ_APPS_LOG( TZ_LOG_MSG_ERROR, "%s Error: qsee_deregister_shared_buffer for input buffer failed.", __FUNCTION__);
    status = SAMPLE_CLIENT_ERROR_MEM_SEG_COPY_FAILED;
  }
  ret = qsee_deregister_shared_buffer(outBuff);
  if(ret)
  {
    TZ_APPS_LOG( TZ_LOG_MSG_ERROR, "%s Error: qsee_deregister_shared_buffer for output buffer failed.", __FUNCTION__);
    status = SAMPLE_CLIENT_ERROR_MEM_SEG_COPY_FAILED;
  }

  if(status != SAMPLE_CLIENT_SUCCESS)
  {
    TZ_APPS_LOG(TZ_LOG_MSG_ERROR, "%s failed and returns %d!", __FUNCTION__, (int)status);
  }

  TZ_APPS_LOG(TZ_LOG_MSG_DEBUG,"%s Returns %d", __FUNCTION__, status);
  return status;

}

SampleClientResult Content_Protection_Copy_NonsecureToSecure
(
  const uint8       *nonSecBuffer,
  const uint32       nonSecBufferLength,
  tz_mem_array_s_t  *secBufferHandle,
  uint32             secBufferOffset,
  uint32            *secBufferLength
)
{
  SampleClientResult status              = SAMPLE_CLIENT_SUCCESS;
  uint32             size                = 0;
  uint8*             secBufferPtr        = NULL;
  uint8*             nonSecBufferPtr     = (uint8*)(uintnt)nonSecBuffer;
  uint32             segNum              = 0;
  uint32             sizeCopied          = 0;
  int64              nonSecBufLenLeft    = nonSecBufferLength;
  uint32             secBufLen           = 0;

  TZ_APPS_LOG( TZ_LOG_MSG_DEBUG,"TZ Content_Protection_Copy_NonsecureToSecure is starting...");

  do
  {
    //sanity check
    if(NULL == nonSecBuffer || 0 == nonSecBufferLength || NULL == secBufferHandle || NULL == secBufferLength)
    {
      TZ_APPS_LOG( TZ_LOG_MSG_ERROR, "%s Error: Invalid paramters!", __FUNCTION__);
      status = SAMPLE_CLIENT_ERROR_INVALID_PARAMS;
      break;	
    }
    
    /* check if the nonSecBuffer memory is not protected */
    if(qsee_is_ns_range(nonSecBuffer,nonSecBufferLength) == FALSE)
    {
      TZ_APPS_LOG( TZ_LOG_MSG_ERROR, "Error: trying to access secure memory region ");
      status = SAMPLE_CLIENT_ERROR_NSS_COPY_FAILED;
      break;
    }

    //get address and size of memory segment to copy
    secBufferPtr = (uint8*)(uintnt)(((secBufferHandle->_tz_mem_seg)[segNum])._address);
    size = ((secBufferHandle->_tz_mem_seg)[segNum])._size;

    //0 size means only one contiguous buffer
    if(0 == size)
    {
      secBufLen = nonSecBufferLength;
  
      TZ_APPS_LOG( TZ_LOG_MSG_DEBUG,"TZ Content_Protection_Copy_NonsecureToSecure size == 0, call mem_seg_copy()");
      //copy entire non-secure buff into secure buff
      status = mem_seg_copy(secBufferPtr, secBufLen, (uint8*)(uintnt)nonSecBufferPtr, (uint32)nonSecBufferLength);
      if(status != SAMPLE_CLIENT_SUCCESS)
      {
        TZ_APPS_LOG(TZ_LOG_MSG_ERROR, "%s Error: copy to secure buffer failed! Returned %ld", __FUNCTION__, status);
        status = SAMPLE_CLIENT_ERROR_SNS_COPY_FAILED;
      }
      break;
    }

    //size was not 0. Need to copy to multiple memory segments
    do
    {
      //break when size is 0 or if address is garbage - no more segments to copy to
      if(0 == size || NULL == secBufferPtr)
      {
        TZ_APPS_LOG(TZ_LOG_MSG_ERROR, "Error: secure buffer size < non-secure buffer size %ld", nonSecBufferLength);
        TZ_APPS_LOG(TZ_LOG_MSG_ERROR, "or secBufferPtr 0x%x  = NULL", secBufferPtr);
        status = SAMPLE_CLIENT_ERROR_BUFFER_TOO_SHORT;
        break;
      }

      sizeCopied = size < nonSecBufLenLeft ? size : nonSecBufLenLeft;
      TZ_APPS_LOG( TZ_LOG_MSG_DEBUG,"TZ Content_Protection_Copy_NonsecureToSecure multiple memory segments, call mem_seg_copy()");
      //copy segment of non-secure buff into secure buff segment
      status = mem_seg_copy(secBufferPtr, sizeCopied, (uint8*)(uintnt)nonSecBufferPtr, sizeCopied);
      if(status != SAMPLE_CLIENT_SUCCESS)
      {
        TZ_APPS_LOG(TZ_LOG_MSG_ERROR, "%s Error: copy to secure buffer failed! Returned %ld", __FUNCTION__, status);
        status = SAMPLE_CLIENT_ERROR_NSS_COPY_FAILED;
        break;
      }

      //update destination pointer and segment number
      CHECK_INTEGER_OVERFLOW(nonSecBufferPtr, sizeCopied);
      nonSecBufferPtr += sizeCopied;
      CHECK_INTEGER_UNDERFLOW(nonSecBufLenLeft, sizeCopied);
      nonSecBufLenLeft -= sizeCopied;
      CHECK_INTEGER_OVERFLOW(secBufLen, sizeCopied);
      secBufLen += sizeCopied;
      segNum++;

      //don't go past max number of segments
      if(segNum >= TZ_OUT_BUF_MAX)
      {
        TZ_APPS_LOG(TZ_LOG_MSG_DEBUG, "Copied to maximum number of segments!");
        break;
      }

      //get next address and size of memory segment to copy to
      secBufferPtr = (uint8*)(uintnt)(secBufferHandle->_tz_mem_seg[segNum]._address);
      size = secBufferHandle->_tz_mem_seg[segNum]._size;

    }while(nonSecBufLenLeft > 0);
    //end of copy segments loop
       
  } while(0);

  // return the sec buf size copied
  if (secBufferLength != NULL)
  {
    *secBufferLength = secBufLen;
  }
      
  if(status != SAMPLE_CLIENT_SUCCESS)
    TZ_APPS_LOG(TZ_LOG_MSG_ERROR, "%s failed and returns %d!", __FUNCTION__, (int) status);
  
  TZ_APPS_LOG(TZ_LOG_MSG_DEBUG,"%s Returns %d", __FUNCTION__, status);
  return status;
}
