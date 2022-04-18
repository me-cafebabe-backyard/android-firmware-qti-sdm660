#ifndef _GP_PERSIST_OBJ_INDEX_H_
#define _GP_PERSIST_OBJ_INDEX_H_

/**
@file   gpPersistObjIndex.h
@brief  Defintions for index file management module for the gp Persistent
        Object implementation.
*/

/*=============================================================================
Copyright (c) 2015 QUALCOMM Technologies Incorporated.
All Rights Reserved.
Qualcomm Confidential and Proprietary
=============================================================================*/

/*=============================================================================

EDIT HISTORY FOR MODULE

$Header: //components/rel/core.tz/1.0.7.1/securemsm/trustzone/qsapps/libs/applib/common_applib/inc/gpPersistObjIndex.h#1 $
$DateTime: 2020/01/14 12:35:09 $
$Author: pwbldsvc $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
03/25/15   mr      Initial Implementation
=============================================================================*/

#include "gpTypes.h"
#include "gpPersistObjHandler.h"
#include "gpPersistObjData.h"
#include "gpPersistObjCrypto.h"
#include "gpPersistObjFileIO.h"
#include "gpObject.h"

#define INDEX_FILE_SIZE (8 * 1024)

typedef struct
{
  uint8_t   hmac[GPCRYPTO_HMAC_SIZE];
  //uint8_t iv[GPCRYPTO_IV_SIZE]; TODO: QPSI said no encrypt needed
  uint32_t  version;
  char      fileName[FILE_NAME_SIZE + 1];
} __attribute__((packed)) indexMetaData;

typedef struct
{
  uint8_t   used;
  uint8_t   objectID[TEE_OBJECT_ID_MAX_LEN];
  size_t    objectIDLen;
  uint32_t  objectSize;
  uint32_t  maxObjectSize;
  char      fileName[FILE_NAME_SIZE + 1];
  uint32_t  dataSize;
  uint32_t  objectVersion;
  uint32_t  objectType;
  uint32_t  objectUsage;
  uint32_t  attrCount;
  uint32_t  attrCoutMax;
  uint32_t  keySize;
  uint32_t  mode;
  uint8_t   formatVersion;
} __attribute__((packed)) indexEntry;

TEE_Result gpIndex_Create_Entry
(
  gpHandle* handle,
  TEE_ObjectHandle object
);

TEE_Result gpIndex_Delete_Entry
(
  gpHandle* handle,
  TEE_ObjectHandle object
);

TEE_Result gpIndex_Get_Entry
(
  gpHandle* handle,
  TEE_ObjectHandle object
);

TEE_Result gpIndex_Set_Entry
(
  gpHandle* handle,
  TEE_ObjectHandle object
);

TEE_Result gpIndex_Rename_Entry
(
  gpHandle* handle,
  void* newObjectID,
  uint32_t newObjectIDLen,
  TEE_ObjectHandle object
);

TEE_Result gpIndex_Get_Enum_Entry
(
  gpHandle* handle,
  TEE_ObjectInfo* objectInfo,
  void* objectID,
  size_t* objectIDLen,
  TEE_ObjectEnumHandle objectEnumerator
);

TEE_Result gpIndex_Get_Index_Info
(
  gpHandle* handle,
  TEE_ObjectEnumHandle objectEnumerator
);

#endif //_GP_PERSIST_OBJ_INDEX_H_
