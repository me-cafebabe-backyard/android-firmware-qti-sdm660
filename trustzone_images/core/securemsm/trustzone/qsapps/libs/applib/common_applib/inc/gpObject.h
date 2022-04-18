#ifndef GPOBJECT_H
#define GPOBJECT_H

/**
@file gpObject.h
@brief Internal object definition for Crypto and Persistent Object objects
*/

/*=============================================================================
Copyright (c) 2015 QUALCOMM Technologies Incorporated.
All Rights Reserved.
Qualcomm Confidential and Proprietary

=============================================================================*/

/*=========================================================================
                              Edit History

  $Header: //components/rel/core.tz/1.0.7.1/securemsm/trustzone/qsapps/libs/applib/common_applib/inc/gpObject.h#1 $
  $DateTime: 2020/01/14 12:35:09 $
  $Author: pwbldsvc $


when       who     what, where, why
--------   ---     --------------------------------------------------------
4/26/2015  mr     Initial version.

=========================================================================== */

/*----------------------------------------------------------------------------
 * Include files
 * -------------------------------------------------------------------------*/
#include "gpTypes.h"

/*----------------------------------------------------------------------------
 * External Variable Declarations
 * -------------------------------------------------------------------------*/

#define __TEE_OBJECT_MAGIC  0x4A424F51 // "QOBJ"

/* The object to which TEE_ObjectHandles point to. Objects can be either Transient or Persistent. */

#define __TEE_Object __TEE_ObjectHandle
struct __TEE_Object
{
  uint32_t magic;
  TEE_ObjectInfo info;
  TEE_Attribute* attrs;
  uint32_t attrCount;
  uint32_t attrCountMax;
  uint32_t keySize;
  void* handle;
  void* chandle;
};

#define __TEE_ObjectEnum __TEE_ObjectEnumHandle
struct __TEE_ObjectEnum
{
  uint32_t magic;
  bool     isStarted;
  uint32_t storageID;
  uint32_t indexPos;
  uint32_t objectCount;
  void*    handle;
};

#endif /* GPOBJECT_H */
