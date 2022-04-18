#ifndef _GP_PERSIST_OBJ_VERSION_H_
#define _GP_PERSIST_OBJ_VERSION_H_

/**
@file   gpPersistObjVersion.h
@brief  Definitions for version/rollback protection module for the gp Persistent
        Object implementation.
*/

/*=============================================================================
Copyright (c) 2015 QUALCOMM Technologies Incorporated.
All Rights Reserved.
Qualcomm Confidential and Proprietary
=============================================================================*/

/*=============================================================================

EDIT HISTORY FOR MODULE

$Header: //components/rel/core.tz/1.0.7.1/securemsm/trustzone/qsapps/libs/applib/common_applib/inc/gpPersistObjVersion.h#1 $
$DateTime: 2020/01/14 12:35:09 $
$Author: pwbldsvc $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
03/25/15   mr      Initial Implementation
=============================================================================*/

#include "gpTypes.h"
#include "gpPersistObjHandler.h"
#include "gpPersistObjCrypto.h"

#define MAX_VTABLE_ENTRIES (506 / sizeof(versionEntry))

typedef struct
{
  uint8_t   used;
  uint64_t  id;
  uint32_t  version;
} __attribute__((packed)) versionEntry;

typedef struct
{
  uint8_t  numEntries;
  uint8_t  maxEntries;
  uint32_t maxVersion;
  versionEntry entries[MAX_VTABLE_ENTRIES];
  uint8_t  filler[12]; // Has to be 512 bytes
} __attribute__((packed)) versionTable;

typedef struct
{
  uint8_t      hmac[GPCRYPTO_HMAC_SIZE];
  char         appName[APP_NAME_SIZE];
  versionTable vTable;
  uint8_t      verifyHMAC;
} __attribute__((packed)) versionTableFile;

TEE_Result gpVersion_Get_Version
(
  gpHandle* handle,
  void*     id,
  size_t    idLen,
  uint32_t* version
);

TEE_Result gpVersion_Set_Version
(
  gpHandle* handle,
  void*     id,
  size_t    idLen,
  uint32_t  version
);

TEE_Result gpVersion_Inc_Version
(
  uint32_t* version
);

TEE_Result gpVersion_Delete_Version
(
  gpHandle* handle,
  void*     id,
  size_t    idLen
);

#endif //_GP_PERSIST_OBJ_VERSION_H_
