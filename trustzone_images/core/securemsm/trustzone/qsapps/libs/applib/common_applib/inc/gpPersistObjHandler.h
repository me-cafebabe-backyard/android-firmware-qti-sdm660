#ifndef _GP_PERSIST_OBJ_HANDLER_H_
#define _GP_PERSIST_OBJ_HANDLER_H_

/**
@file   gpPersistObjHandler.h
@brief  Definitions for the gp Handler module which manages open object handles.
*/

/*=============================================================================
Copyright (c) 2015 QUALCOMM Technologies Incorporated.
All Rights Reserved.
Qualcomm Confidential and Proprietary
=============================================================================*/

/*=============================================================================

EDIT HISTORY FOR MODULE

$Header: //components/rel/core.tz/1.0.7.1/securemsm/trustzone/qsapps/libs/applib/common_applib/inc/gpPersistObjHandler.h#1 $
$DateTime: 2020/01/14 12:35:09 $
$Author: pwbldsvc $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
03/25/15   mr      Initial Implementation
=============================================================================*/

#include "gpTypes.h"
#include "qsee_cipher.h"
#include "gpObject.h"

#define MAX_OPEN_CLIENT_HANDLES 52
#define FILE_NAME_SIZE 42
#define APP_NAME_SIZE 36

typedef struct
{
  bool      used;
  uint8_t   objectID[TEE_OBJECT_ID_MAX_LEN];
  size_t    objectIDLen;
  uint32_t  refCount;
  uint8_t   accessMetaCount;
  uint8_t   accessReadCount;
  uint8_t   accessWriteCount;
  uint8_t   shareReadCount;
  uint8_t   shareWriteCount;
} htableEntry;

typedef struct
{
  /* Object Info */
  uint8_t   objectID[TEE_OBJECT_ID_MAX_LEN];
  size_t    objectIDLen;
  uint32_t  flags;

  /* App Info */
  char      appName[APP_NAME_SIZE];
  bool      appInfoInit;
  uint64_t  appID;

  /* File Info */
  char      fileName[FILE_NAME_SIZE+1];
  uint32_t  version;
  uint32_t  fd;
  bool      backup;

  /* Crypto Info */
  uint8_t   cKey[QSEE_AES256_KEY_SIZE];
  uint8_t   hKey[QSEE_AES256_KEY_SIZE];
  bool      keyInit;

} gpHandle;

TEE_Result gpHandler_Create_Handle
(
  gpHandle* handle,
  TEE_ObjectHandle object
);

TEE_Result gpHandler_Delete_Handle
(
  gpHandle* handle,
  TEE_ObjectHandle object
);

TEE_Result gpHandler_Open_Handle
(
  gpHandle* handle,
  TEE_ObjectHandle object
);

TEE_Result gpHandler_Close_Handle
(
  gpHandle* handle,
  TEE_ObjectHandle object
);

TEE_Result gpHandler_Update_Handle
(
  gpHandle* handle,
  TEE_ObjectHandle object
);

TEE_Result gpHandler_Rename_Handle
(
  gpHandle* handle,
  void* newObjectID,
  uint32_t newObjectIDLen,
  TEE_ObjectHandle object
);

#endif //_GP_PERSIST_OBJ_HANDLER_H_
