#ifndef _GP_PERSIST_OBJ_FILEIO_H_
#define _GP_PERSIST_OBJ_FILEIO_H_

/**
@file   gpPersistObjFileIO.h
@brief  Definitions for the gp File IO module which interfaces with storing
        file data in HLOS vfs through the gp File Listener.
*/

/*=============================================================================
Copyright (c) 2015 QUALCOMM Technologies Incorporated.
All Rights Reserved.
Qualcomm Confidential and Proprietary
=============================================================================*/

/*=============================================================================

EDIT HISTORY FOR MODULE

$Header: //components/rel/core.tz/1.0.7.1/securemsm/trustzone/qsapps/libs/applib/common_applib/inc/gpPersistObjFileIO.h#1 $
$DateTime: 2020/01/14 12:35:09 $
$Author: pwbldsvc $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
03/25/15   mr      Initial Implementation
=============================================================================*/

/*===========================================================================
===
=== The gpPersistObjFileIO module provides an interface for persistent storage
=== of transparent data. This transparent data is stored in the HLOS virtual
=== file system, so its the responsibility of the caller to provide the 
=== necessary security on top of the transparent data. Data is transferred to
=== an HLOS listener which interacts directly with the virtual file system,
=== and because there is overhead in the transfer of data between secure and 
=== non-secure context it is advised to reduce the amount of calls to these
=== APIs by increasing data sizes.
===
=== Version 1.0
===   As part of version 1.0, there are some restrictions on the usage of 
===   these APIs. 
===     1. Files should ONLY be written in one-shot, meaning the write call
===        should be made with a buf equal to the size of the file. This will
===        guarantee power cycle protection provided by the virtual file
===        system.
===     2. As a consequence of restriction 1. the offset provided to a write
===        should also be 0, and this is the only acceptable input for version 
===        1.0.
===     3. The only valid value of handle in each of the APIs provided below
===        is NULL. This parameter will be used for further expansion and
===        GP use cases.
===
===========================================================================*/

#include "gpPersistObjHandler.h"  /* gpHandle */
#include "gpTypes.h"              /* size_t   */

/* Maximum File Name Size */
#define MAX_NAME_LENGTH     128

/*===========================================================================
=== gpFileIO_Read_File
===
=== Read data from the specified file.
===
=== Parameters:
===   - [in]handle    Used by GP Persistent Object Framework to specify meta
===                   data for additional functionality. Pass NULL for non-GP
===                   use cases.
===   - [in]name      File name which is used to identify the file in the virtual
===                   file system.
===   - [out]buffer   Buffer in which the file data will be copied to. Caller is 
===                   responsible for memory management of buffer.
===   - [in]size      Size of buffer which was allocated from the caller.
===   - [in]offset    The offset in the file to start reading size bytes from.
===   - [out]count    Returns the number of bytes actually read.
===
=== Returns
===   - TEE_SUCCESS         On successful read operation.
===   - TEE_ERROR_GENERIC   On failure of read operation.
===
===========================================================================*/
TEE_Result gpFileIO_Read_File
(
  gpHandle*   handle,
  const char* name,
  void*       buffer,
  size_t      size,
  size_t      offset,
  uint32_t*   count
);

/*===========================================================================
=== gpFileIO_Write_File
===
=== Write data to the specified file.
===
=== Parameters:
===   - [in]handle    Used by GP Persistent Object Framework to specify meta
===                   data for additional functionality. Pass NULL for non-GP
===                   use cases.
===   - [in]name      File name which is used to identify the file in the virtual
===                   file system.
===   - [in]buffer    Buffer which contains the data to be written to the file.
===                   Caller is responsible for memory management of buffer.
===   - [in]size      Size of buffer which was allocated from the caller.
===   - [in]offset    The offset in the file to start writing size bytes to.
===   - [out]count    Returns the number of bytes actually written.
===
=== Returns
===   - TEE_SUCCESS         On successful write operation.
===   - TEE_ERROR_GENERIC   On failure of write operation.
===
===========================================================================*/
TEE_Result gpFileIO_Write_File
(
  gpHandle*   handle,
  const char* name,
  void*       buffer,
  size_t      size,
  size_t      offset,
  uint32_t*   count
);

/*===========================================================================
=== gpFileIO_Remove_File
===
=== Remove the file specified from the HLOS virtual file system.
===
=== Parameters:
===   - [in]handle    Used by GP Persistent Object Framework to specify meta
===                   data for additional functionality. Pass NULL for non-GP
===                   use cases.
===   - [in]name      File name which is used to identify the file in the virtual
===                   file system.
===
=== Returns
===   - TEE_SUCCESS         On successful remove operation.
===   - TEE_ERROR_GENERIC   On failure of remove operation.
===
===========================================================================*/
TEE_Result gpFileIO_Remove_File
(
  gpHandle*   handle,
  const char* name
);

/*===========================================================================
=== gpFileIO_Rename_File
===
=== Rename the file specified by 'from' to the name provided by 'to' 
===
=== Parameters:
===   - [in]handle    Used by GP Persistent Object Framework to specify meta
===                   data for additional functionality. Pass NULL for non-GP
===                   use cases.
===   - [in]from      File name which is used to identify the file in the virtual
===                   file system.
===   - [in]to        New name of file specified by from.
===
=== Returns
===   - TEE_SUCCESS         On successful rename operation.
===   - TEE_ERROR_GENERIC   On failure of rename operation.
===
===========================================================================*/
TEE_Result gpFileIO_Rename_File
(
  gpHandle*   handle,
  const char* from,
  const char* to
);

#endif //_GP_PERSIST_OBJ_FILEIO_H_
