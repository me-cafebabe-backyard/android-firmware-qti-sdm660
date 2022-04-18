#ifndef _GP_PERSIST_OBJ_COMMON_H_
#define _GP_PERSIST_OBJ_COMMON_H_

/**
@file   gpPersistentObjectsInternal.h
@brief  Contains internal functions needed for the PersistentObject framework
        implementation.
*/

/*=============================================================================
 Copyright (c) 2015 Qualcomm Technologies Incorporated.
                      All Rights Reserved.
 Qualcomm Confidential and Proprietary.
=============================================================================*/

/*=============================================================================

                       EDIT HISTORY FOR MODULE

  $Header: //components/rel/core.tz/1.0.7.1/securemsm/trustzone/qsapps/libs/applib/common_applib/inc/gpPersistObjCommon.h#1 $ 
  $DateTime: 2020/01/14 12:35:09 $
  $Author: pwbldsvc $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
4/26/15    mr      Initial version
=============================================================================*/

/*===========================================================================

                     INCLUDE FILES FOR MODULE

===========================================================================*/

#include "gpTypes.h"
#include "gpPersistObjHandler.h"

#define GP_MAX_OBJECT_SIZE 0x7FFFFFFF

#define ROOT_PATH_PROP "cmnlib_gppo_root_path"

/**
   @addtogroupqsee_sfs_apis 
   @{
*/

/**
The TEE_OpenPersistentObject function opens a handle on an existing persistent object. 


@param[in]  storageID    The storage to use. It must be TEE_STORAGE_PRIVATE.
@param[in]  objectID     The object identifier. Note that this cannot reside in shared
                         memory.
@param[in]  objectIDLen  Length of objectID
@param[in]  flags        The flags which determine the settings under which the object
                         is opened.
@param[out] object       A pointer to the handle, which contains the opened handle upon 
                         successful completion. If this function fails for any reason, 
                         the value pointed to by object is set to TEE_HANDLE_NULL. When 
                         the object handle is no longer required, it MUST be closed using 
                         a call to the TEE_CloseObject function.

@return
TEE_SUCCESS:                     In case of success
TEE_ERROR_ITEM_NOT_FOUND:        If the storage denoted by storageID does not exist or if 
                                 the object identifier cannot be found in the storage
TEE_ERROR_ACCESS_CONFLICT:       If an access right conflict was detected while opening the
                                 object
TEE_ERROR_OUT_OF_MEMORY:         If there is not enough memory to complete the operation
TEE_ERROR_CORRUPT_OBJECT:        If the storage is corrupt
TEE_ERROR_STORAGE_NOT_AVAILABLE: If the persistent object is stored in a storage area which
                                 is currently inaccessible.

*/
TEE_Result gpCommon_Copy_Attributes
(
  TEE_ObjectHandle object,
  TEE_ObjectHandle attributes
);

TEE_Result gpCommon_Init_Handles
(
  gpHandle* handle,
  TEE_ObjectHandle object,
  void*            objectID,
  size_t           objectIDLen,
  uint32_t         flags,
  TEE_ObjectHandle attributes
);

TEE_Result gpCommon_Init_App_Info
(
  gpHandle* handle
);

void gpCommon_Clean_Attributes
(
  TEE_ObjectHandle object
);

void gpCommon_Clean_Object_Handle
(
  TEE_ObjectHandle object
);

TEE_Result gpCommon_Get_Object_Info
(
  TEE_ObjectHandle object,
  TEE_ObjectInfo* objectInfo
);

TEE_Result gpCommon_Close_Object
(
  TEE_ObjectHandle object
);

TEE_Result gpCommon_Get_File_Path
(
  gpHandle* handle,
  const char* filename,
  char*  path,
  uint32_t pathSize
);

#endif //_GP_PERSIST_OBJ_COMMON_H_
