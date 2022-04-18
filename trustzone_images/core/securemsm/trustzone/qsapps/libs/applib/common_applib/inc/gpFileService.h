#ifndef _GP_FILE_SERVICE_H_
#define _GP_FILE_SERVICE_H_

/**
@file   gpFileService.h
@brief  Definitions for the gp File Service which provides file IO from gp File
        Listener.
*/

/*=============================================================================
Copyright (c) 2015 QUALCOMM Technologies Incorporated.
All Rights Reserved.
Qualcomm Confidential and Proprietary

=============================================================================*/

/*=============================================================================

EDIT HISTORY FOR MODULE

$Header: //components/rel/core.tz/1.0.7.1/securemsm/trustzone/qsapps/libs/applib/common_applib/inc/gpFileService.h#1 $
$DateTime: 2020/01/14 12:35:09 $
$Author: pwbldsvc $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
03/25/15   mr      Initial Implementation
=============================================================================*/

#include "gpTypes.h"
#include "services_defs.h"

#define OVERFLOWS(type, ptr, len)  ((type) (ptr) > ((type) (ptr)+len))
#define UNDERFLOWS(type, ptr, len) ((type) (ptr) < ((type) (ptr)-len))

/* Size of largest data size request from listener */
#define TZ_GPFS_FILE_SIZE     500*1024

/* Size of max path name support in GP Listener */
#define TZ_CM_MAX_NAME_LEN    256

/* GP File request/response structures */
typedef enum
{
  /* TZ to HLOS commands -
  ** Following commands represent services that TZ could request from the HLOS.
  ** Essentially, in these instances, TZ will be the client and HLOS will service the requests.
  */
  TZ_GPFS_MSG_CMD_FILE_READ,      /**< Read from a file */
  TZ_GPFS_MSG_CMD_FILE_WRITE,     /**< Write to a file */
  TZ_GPFS_MSG_CMD_FILE_REMOVE,     /**< Remove a file */
  TZ_GPFS_MSG_CMD_FILE_RENAME,     /**< Rename a file */
  TZ_GPFS_MSG_CMD_UNKNOWN = 0x7FFFFFFF
} tz_gpfs_msg_cmd_type;

typedef struct tz_gpfile_read_req_s
{
  /** First 4 bytes are always command id */
  tz_gpfs_msg_cmd_type    cmd_id;
  /** Pathname of file */
  const char              pathname[TZ_CM_MAX_NAME_LEN];
  /** New offset */
  int32_t                 offset;
  /** Number of bytes to read */
  uint32_t                count;
}  __attribute__((packed)) tz_gpfile_read_req_t;

typedef struct tz_gpfile_read_rsp_s
{
  /** First 4 bytes are always command id */
  tz_gpfs_msg_cmd_type    cmd_id;
  /** 0 if success */
  int32_t                 err;
  /**<-- Number of bytes read, valid only if err is success */
  uint32_t                num_bytes_read;
  /** Buffer containing read data */
  uint8_t                 buf[TZ_GPFS_FILE_SIZE];
}  __attribute__((packed)) tz_gpfile_read_rsp_t;

/** Command structure for gp file write
*/
typedef struct tz_gpfile_write_req_s
{
  /** First 4 bytes are always command id */
  tz_gpfs_msg_cmd_type    cmd_id;
  /** Pathname of file */
  const char              pathname[TZ_CM_MAX_NAME_LEN];
  /** New offset */
  int32_t                 offset;
  /** Number of bytes to write */
  uint32_t                count;
  /** Whether to Backup or Not */
  uint32_t                backup;
  /** Buffer to write from */
  uint8_t                 buf[TZ_GPFS_FILE_SIZE];
}  __attribute__((packed)) tz_gpfile_write_req_t;

typedef struct tz_gpfile_write_rsp_s
{
  /** First 4 bytes are always command id */
  tz_gpfs_msg_cmd_type    cmd_id;
  /** 0 if success */
  int32_t                 err;
  /**<-- Number of bytes written, valid only if err is success */
  uint32_t                num_bytes_written;
}   __attribute__((packed)) tz_gpfile_write_rsp_t;

/** Command structure for file remove
*/
typedef struct tz_gpfile_remove_req_s
{
  /** First 4 bytes are always command id */
  tz_gpfs_msg_cmd_type    cmd_id;
  /** Pathname of directory */
  const char              pathname[TZ_CM_MAX_NAME_LEN];
}  __attribute__((packed)) tz_gpfile_remove_req_t;

typedef struct tz_gpfile_remove_rsp_s
{
  /** First 4 bytes are always command id */
  tz_gpfs_msg_cmd_type    cmd_id;
  /** 0 if success */
  int32_t                 err;
}  __attribute__((packed)) tz_gpfile_remove_rsp_t;

/** Command structure for file rename
*/
typedef struct tz_gpfile_rename_req_s
{
  /** First 4 bytes are always command id */
  tz_gpfs_msg_cmd_type    cmd_id;
  /** Pathname of file to change */
  const char              from[TZ_CM_MAX_NAME_LEN];
  /** New pathname of file */
  const char              to[TZ_CM_MAX_NAME_LEN];
}  __attribute__((packed)) tz_gpfile_rename_req_t;

typedef struct tz_gpfile_rename_rsp_s
{
  /** First 4 bytes are always command id */
  tz_gpfs_msg_cmd_type    cmd_id;
  /** 0 if success */
  int32_t                 err;
}  __attribute__((packed)) tz_gpfile_rename_rsp_t;

typedef struct tz_gpfile_err_rsp_s
{
  /** First 4 bytes are always command id */
  tz_gpfs_msg_cmd_type      cmd_id;
  /** Success/failure value */
  int32_t                   err;
}  __attribute__((packed)) tz_gpfile_err_rsp_t;

/* Read File from HLOS GP File Listener */
int gpFileRead
(
  const char* name,
  void*     buf,
  size_t    size,
  size_t    offset,
  uint32_t* count
);

/* Write File to HLOS GP File Listener */
int gpFileWrite
(
  const char* name,
  void*     buf,
  size_t    size,
  size_t    offset,
  uint32_t* count,
  uint32_t  backup
);

/* Remove File from HLOS GP File Listener */
int gpFileRemove
(
  const char* name
);

/* Rename File from HLOS GP File Listener */
int gpFileRename
(
  const char* from,
  const char* to
);

#endif //_GP_FILE_SERVICE_H_
