#ifndef _GP_PERSIST_OBJ_H_
#define _GP_PERSIST_OBJ_H_

/**
@file   gpPersistObj.h
@brief  Definitions for data management module of the GP Persistent Object
        implementation.
*/

/*=============================================================================
Copyright (c) 2015 QUALCOMM Technologies Incorporated.
All Rights Reserved.
Qualcomm Confidential and Proprietary
=============================================================================*/

/*=============================================================================

EDIT HISTORY FOR MODULE

$Header: //components/rel/core.tz/1.0.7.1/securemsm/trustzone/qsapps/libs/applib/common_applib/inc/gpPersistObjData.h#1 $
$DateTime: 2020/01/14 12:35:09 $
$Author: pwbldsvc $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
03/25/15   mr      Initial Implementation
=============================================================================*/
#include <stdint.h>

#include "gpTypes.h"
#include "gpPersistObjHandler.h"
#include "gpPersistObjCrypto.h"
#include "gpPersistObjFileIO.h"

#include "qsee_log.h"
#include "qsee_timer.h"

#define ROOT_DIR "/persist/data/"

#define GPLOG_MARKER_START() \
  //qsee_log(QSEE_LOG_MSG_ERROR, "[%llu ms] %s:%d (Start)", qsee_get_uptime(), __FUNCTION__, __LINE__)
#define GPLOG_MARKER_STOP()  \
  //qsee_log(QSEE_LOG_MSG_ERROR, "[%llu ms] %s:%d (Stop)", qsee_get_uptime(), __FUNCTION__, __LINE__)

//#define TEE_Panic(res) while (1) {} // TEE_Panic(res)

#define MAX_ROOT_PATH_LENGTH 32

#define MIN_SEG_SIZE      (4 * 1024)
#define MIN_ATTR_SEG_SIZE (4 * 1024)

#define META_DATA_BLOCK_SIZE (4 * 1024)
#define MAX_NUM_SEGS ((META_DATA_BLOCK_SIZE - 91) / sizeof(segInfo))

#define CREATE_ACCESS_FLAGS (TEE_DATA_FLAG_ACCESS_READ | TEE_DATA_FLAG_ACCESS_WRITE | \
                      TEE_DATA_FLAG_ACCESS_WRITE_META | TEE_DATA_FLAG_SHARE_READ | \
                      TEE_DATA_FLAG_SHARE_WRITE | TEE_DATA_FLAG_OVERWRITE)
#define OPEN_ACCESS_FLAGS (TEE_DATA_FLAG_ACCESS_READ | TEE_DATA_FLAG_ACCESS_WRITE | \
                      TEE_DATA_FLAG_ACCESS_WRITE_META | TEE_DATA_FLAG_SHARE_READ | \
                      TEE_DATA_FLAG_SHARE_WRITE)

typedef struct
{
  uint32_t offset;
  uint32_t size;
  uint8_t  iv[GPCRYPTO_IV_SIZE];
  uint8_t  hash[GPCRYPTO_HASH_SIZE];
} __attribute__((packed)) segInfo;

typedef struct
{
  /* Crypto Data */
  uint8_t hmac[GPCRYPTO_HMAC_SIZE];   //32
  uint32_t version;                   //4
  char  fileName[FILE_NAME_SIZE+1];   //43

  /* Attribute Info */
  uint32_t attrCount;                 //4
  uint32_t attrSize;                  //4

  /* Segment Info */
  uint32_t  numSegs;                  //4
  segInfo segs[MAX_NUM_SEGS];

}  __attribute__((packed)) dataMetaData;

typedef struct
{
  uint32_t attributeID;
  uint32_t a;
  uint32_t b;
} __attribute__((packed)) attrValue;

typedef struct
{
  uint32_t attributeID;
  uint32_t length;
  uint8_t  buffer[1];
} __attribute__((packed)) attrRef;

TEE_Result gpData_Create_Object
(
  gpHandle* handle,
  TEE_ObjectHandle object
);

TEE_Result gpData_Delete_Object
(
  gpHandle* handle,
  TEE_ObjectHandle object
);

TEE_Result gpData_Open_Object
(
  gpHandle* handle,
  TEE_ObjectHandle object
);

TEE_Result gpData_Close_Object
(
  gpHandle* handle,
  TEE_ObjectHandle object
);

TEE_Result gpData_Write_Data
(
  gpHandle* handle,
  void* initialData,
  size_t initialDataLen,
  TEE_ObjectHandle object
);

TEE_Result gpData_Read_Data
(
  gpHandle* handle,
  void* buffer,
  size_t size,
  uint32_t* count,
  TEE_ObjectHandle object
);

TEE_Result gpData_Trunc_Data
(
  gpHandle* handle,
  uint32_t size,
  TEE_ObjectHandle object
);

TEE_Result gpData_Seek_Data
(
  gpHandle* handle,
  int32_t offset,
  TEE_Whence whence,
  TEE_ObjectHandle object
);

#endif //_GP_PERSIST_OBJ_H_
