/** @file QseeComDxe.c
   
  QseeComDxe.c provides QSEECOM interface in uefi environment. 

  Copyright (c) 2012-2017 Copyright Qualcomm Technologies, Inc. 
  All Rights Reserved. Qualcomm Technologies Proprietary and 
  Confidential. 
   
**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 04/21/17   ys     Moved QseecomStartAppByGuid to end of Protocol structure
 02/20/17   ys     Added new API to load App by Guid
 01/25/17   rj     Added functionality for showing qsee logs (tz apps logs)
 07/12/16   rj     Initial revision
 =============================================================================*/

#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/EFIQseecom.h>
#include <Protocol/EFIScm.h>
#include <Protocol/EFITzeLoader.h>
#include <Include/scm_qsee_interface.h>
#include <Library/BaseLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/SerialPortLib.h>
#include "QcomLib.h"
#include "LoaderUtils.h"
#include "QseeComDxe.h"

extern QCOM_SCM_PROTOCOL      *QcomScmProtocol;
extern UINT64 *log_buffer;

#define SUFFIX_64BIT_TA ("64")
#define SUFFIX_SIZE_64BIT_TA (2)
// Including NULL
#define SUFFIX_SIZE (3)

extern
EFI_STATUS
LoadImageFromPartition(
    IN  EFI_TZE_LOADER_PROTOCOL        *This,
    IN  EFI_GUID                       *pPartitionGuid,
    IN  UINT16                         *pPartitionLabel,
    OUT UINT32                         *AppIdPtr
 );

int DisplayQseeLog(UINT32 startOffset, UINT32 endOffset)
{
  UINT32 MaxBufSize = 0;
  UINT32 LogBufSize = 0;
  UINT32 LogBufFirstHalf = 0;
  EFI_STATUS  ret = EFI_SUCCESS;
  void *pLogBuf = NULL;
  tzdbg_log_t *log = (tzdbg_log_t *)log_buffer;

  MaxBufSize = QSEE_LOG_BUF_SIZE - sizeof(struct tzdbg_log_pos_t);
  if (startOffset < endOffset)
  {
    LogBufSize = endOffset - startOffset;
    pLogBuf = AllocatePool(LogBufSize);
    if (NULL == pLogBuf)
    {
      ret = EFI_DEVICE_ERROR;
      DEBUG ((EFI_D_ERROR, "Failed to alloc buffer to print TZ Log:%u\n", LogBufSize));
      goto Exit;
    }
    SetMem(pLogBuf, LogBufSize, 0);
    memscpy(pLogBuf, LogBufSize, (void *)(log->log_buf + startOffset), LogBufSize);
  }
  else if ( endOffset < startOffset)
  {
    LogBufSize =  MaxBufSize - (startOffset - endOffset);
    LogBufFirstHalf = MaxBufSize - startOffset;
    pLogBuf = AllocatePool(LogBufSize);
    if (NULL == pLogBuf)
    {
      ret = EFI_DEVICE_ERROR;
      DEBUG ((EFI_D_ERROR, "Failed to alloc buffer to print TZ Log:%u\n", LogBufSize));
      goto Exit;
    }
    SetMem(pLogBuf, LogBufSize, 0);
    memscpy(pLogBuf, LogBufSize, (void *)(log->log_buf + startOffset), LogBufFirstHalf);
    memscpy((void *)(pLogBuf+ LogBufFirstHalf), (LogBufSize - LogBufFirstHalf), log->log_buf, endOffset);
  }
  else //endOffset == startOffset (no log is updated)
  {
    ret = EFI_SUCCESS;
    goto Exit;
  }

  SerialPortWrite((UINT8 *)pLogBuf, (UINTN)(LogBufSize));
  FreePool(pLogBuf);
Exit:
  return ret;
}


UINT32 QueryAppId(CHAR8 *AppName)
{
  EFI_STATUS    Status;
  UINT32        AppId = 0;

  Status = QcomScmProtocol->ScmSendCommand(
                                             QcomScmProtocol, 
                                             APP_QUERY_APPID_CMD, 
                                             &AppId,
                                             AppName,
                                             AsciiStrnLenS(AppName, QSEE_MAX_NAME_SIZE),
                                             NULL,
                                             0
                                            );
  if (EFI_ERROR(Status)) 
  {
    DEBUG ((EFI_D_INFO, "QueryAppId for (%a) Failed: Status =  %d\n", AppName, Status));
    AppId = 0;
    goto Exit;
  }

Exit:
  return AppId;
}

/*
* Load app using TZ qsee scm command
*/
UINT32 
QseeAppStartSyscall (
  UINTN mdt_len,
  UINTN img_len,
  VOID *pa,
  CHAR8 img_name[QSEE_MAX_NAME_SIZE])
{
   qsee_app_start_req_t *qsee_syscallp;
   UINT32         app_id = 0;
   EFI_STATUS     Status;
   
   qsee_syscallp= (qsee_app_start_req_t *)AllocatePool(sizeof(qsee_app_start_req_t));
   if (NULL == qsee_syscallp)
   {
      return app_id;
   }

   SetMem(qsee_syscallp, sizeof(qsee_app_start_req_t), 0x0);
   qsee_syscallp->mdt_len = (UINT32)mdt_len;
   qsee_syscallp->img_len = (UINT32)img_len;
   qsee_syscallp->pa = (UINT32)(UINTN)pa;
   CopyMem((VOID *)qsee_syscallp->app_name, img_name, QSEE_MAX_NAME_SIZE); 

   Status = QcomScmProtocol->ScmSendCommand(QcomScmProtocol,
                                            APP_START_APP_CMD,
                                            &(app_id),
                                            qsee_syscallp,
                                            sizeof(qsee_app_start_req_t),
                                            NULL,
                                            0);
   if (Status != EFI_SUCCESS)
   { 
     app_id = 0;
   }
   FreePool(qsee_syscallp);
   return app_id;
}

/** 
  This function ?????
   
  @param[in/out]    .

  @return  EFI_SUCCESS:   Function completed successfully.
           EFI_DEVICE_ERROR:   Failed 
*/
EFI_STATUS
EFI_QseecomStartApp(
  IN     QCOM_QSEECOM_PROTOCOL      *This, 
  IN     CHAR8                       *AppName,
  OUT    UINT32                   *handleId
)
{
  EFI_STATUS Status = EFI_SUCCESS;
  UINT32 AppId = 0;
  UINT16 *AppNameL = NULL;

  DEBUG ((EFI_D_INFO, "EFI_QseecomStartApp: AppName %a\n", AppName));

  /* Check all the input parameters */
  if(AppName == NULL || This ==NULL || (AsciiStrnLenS(AppName, QSEE_MAX_NAME_SIZE) >= QSEE_MAX_NAME_SIZE))
  {
    DEBUG ((EFI_D_WARN, "EFI_QseecomStartApp: Invalid Parameters AppName: %a\n", AppName));
    Status = EFI_INVALID_PARAMETER;
    return Status;
  }

  /* Validate if SCM protocol is initialized */
  if(QcomScmProtocol == NULL )
  {
    Status = EFI_LOAD_ERROR;
    return Status;
  }

  /* Querry if app is already loaded */
  AppId = QueryAppId(AppName);
  if (AppId != 0)
  {
      *handleId = AppId;
      return Status;
  }

  if(strlen(AppName) < (QSEE_MAX_NAME_SIZE - SUFFIX_SIZE)) {
      CHAR8 AppName64[QSEE_MAX_NAME_SIZE];

      memset(AppName64, 0, QSEE_MAX_NAME_SIZE);
      memscpy(AppName64, QSEE_MAX_NAME_SIZE, AppName, strlen(AppName));
      memscpy(AppName64 + strlen(AppName), (QSEE_MAX_NAME_SIZE - strlen(AppName) - 1),
            SUFFIX_64BIT_TA, SUFFIX_SIZE_64BIT_TA);
      AppId = QueryAppId(AppName64);
      if (AppId != 0)
      {
          *handleId = AppId;
          return Status;
      }
  }

  AppNameL = AllocatePool(QSEE_MAX_NAME_SIZE * sizeof(UINT16));
  if(!AppNameL)
  {
    DEBUG ((EFI_D_ERROR, "AppNameL allocation failed"));
    return EFI_DEVICE_ERROR;
  }
  AsciiStrToUnicodeStr(AppName, AppNameL);

  /* Load the app from partion */
  Status = LoadImageFromPartition (( EFI_TZE_LOADER_PROTOCOL*)This,
                                     NULL,
                                     AppNameL,
                                     &AppId);
  if(EFI_ERROR(Status))
  {
    DEBUG ((EFI_D_WARN, "EFI_QseecomStartApp: Load from partition (%a)Failed:  Status(0x%p), appId(%d)\n", AppName, Status, AppId));
    AppId = 0;
  }
  *handleId = AppId;
  FreePool(AppNameL);
  return Status;
}

EFI_STATUS
EFI_QseecomStartAppByGuid(
  IN     QCOM_QSEECOM_PROTOCOL      *This,
  IN     EFI_GUID                  * EfiGuid,
  OUT    UINT32                   *handleId
)
{
  EFI_STATUS Status = EFI_SUCCESS;
  UINT32 AppId = 0;


  /* Check all the input parameters */
  if( This ==NULL)
  {
    DEBUG ((EFI_D_WARN, "EFI_QseecomStartApp: Invalid Parameters\n"));
    Status = EFI_INVALID_PARAMETER;
    return Status;
  }

  /* Validate if SCM protocol is initialized */
  if(QcomScmProtocol == NULL )
  {
    Status = EFI_LOAD_ERROR;
    return Status;
  }

  /* Load the app from partion */
  Status = LoadImageFromFileSystem (( EFI_TZE_LOADER_PROTOCOL*)This,
                                     EfiGuid,
                                     NULL,
                                     &AppId);
  if(EFI_ERROR(Status))
  {
    DEBUG ((EFI_D_WARN, "EFI_QseecomStartApp: Load Failed:  Status(0x%p)\n", Status));
    AppId = 0;
  }
  *handleId = AppId;
  return Status;
}

/** 
  This function ?????
   
  @param[in/out]    .

  @return  EFI_SUCCESS:   Function completed successfully.
           EFI_DEVICE_ERROR:   Failed 
*/
EFI_STATUS
EFI_QseecomShutdownApp(
  IN     QCOM_QSEECOM_PROTOCOL      *This, 
  IN    UINT32                   HandleId
)
{
  EFI_STATUS Status;

  /* Validate if SCM protocol is initialized */
  if(QcomScmProtocol == NULL )
  {
    Status = EFI_LOAD_ERROR;
    return Status;
  }

  Status = QcomScmProtocol->ScmSendCommand(QcomScmProtocol,
                                       APP_SHUTDOWN_CMD,
                                       &HandleId,
                                       NULL,
                                       0,
                                       NULL,
                                       0);
  return Status;
}


/** 
  This function ?????
   
  @param[in/out]    .

  @return  EFI_SUCCESS:   Function completed successfully.
           EFI_DEVICE_ERROR:   Failed 
*/
EFI_STATUS
EFI_QseecomSendCmd(
  IN     QCOM_QSEECOM_PROTOCOL      *This, 
  IN     UINT32                  HandleId,
  IN     UINT8                   *send_buf,
  IN     UINT32                  sbuf_len,
  IN OUT UINT8                   *rsp_buf,
  IN     UINT32                  rbuf_len
)
{
  EFI_STATUS Status;

  /* Validate if SCM protocol is initialized */
  if(QcomScmProtocol == NULL )
  {
    Status = EFI_LOAD_ERROR;
    return Status;
  }

  Status = QcomScmProtocol->ScmSendCommand(  QcomScmProtocol, 
                                             APP_SEND_DATA_CMD, 
                                             &HandleId,
                                             send_buf,
                                             sbuf_len,
                                             rsp_buf,
                                             rbuf_len
                                            );
  return Status;
}

static QCOM_QSEECOM_PROTOCOL QcomQseecomProtocolImpl = 
{

  QCOM_QSEECOM_PROTOCOL_REVISION,
  EFI_QseecomStartApp,
  EFI_QseecomShutdownApp,
  EFI_QseecomSendCmd,
  EFI_QseecomStartAppByGuid
};


// ScmQseeCom protocol implementation
// Protocol initialization
EFI_STATUS
QseeComProtocolInit (
  IN EFI_HANDLE          ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
)
{
  EFI_STATUS              Status;

  /* Validate if SCM protocol is initialized (Dependency)*/
  if(QcomScmProtocol == NULL )
  {
    Status = EFI_LOAD_ERROR;
    return Status;
  }

  // publish protocol
  Status = gBS->InstallMultipleProtocolInterfaces(
           &ImageHandle,
           &gQcomQseecomProtocolGuid,
           (void **)&QcomQseecomProtocolImpl,
           NULL);
    
  return Status;
}

