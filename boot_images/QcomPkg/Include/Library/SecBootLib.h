#ifndef __SECBOOTLIB_H__
#define __SECBOOTLIB_H__

/** @file  
                             SecBootLib.h

  This is for function declaration of PE/COFF authentication.

  Copyright (c) 2011 Qualcomm Technologies, Inc. All rights reserved.

**/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ----------------------------------------------------------
08/12/81   shl     Added more APIs for authenticating iamge
05/15/12   shl     Added support for OEM FW update authentication 
07/18/11   shl     Initial version.
===========================================================================*/

/**
  This is the function registeres SecBootVerifyPeImage as a callback in 
  security framework, so it will be called to verify the PE/COFF image.

  @param[in]  VOID

  @retval EFI_SUCCESS              The handlers were registered successfully.
**/

EFI_STATUS EFIAPI RegisterSecBootVerifyPeImage( VOID );

/**
  This is the function to set the flag to indicate this is OEM FW update.

  @param[in]  VOID

  @retval EFI_SUCCESS              Updated successfully.
**/
EFI_STATUS SecBootSetOemFwUpdateFlag( VOID );

/**
This the function verifies PE/COFF image against all databases.

  @param[in]  AuthenticationStatus  Not really used. Legacy format.
  @param[in]  *File                 Not really used. Legacy format.
  @param[in]  *FileBuffer           Points to PE/COFF image.
  @param[in]  FileSize              PE/COFF image size

  @retval EFI_SUCCESS               Verified successfully.
  @retval EFI_INVALID_PARAMETER     Parmeter is not right or data not recoginized
  @retval EFI_SECURITY_VIOLATION    Verification not supported.
**/

EFI_STATUS EFIAPI SecBootVerifyPeImage
(
  IN  OUT   UINT32                      AuthenticationStatus,
  IN  CONST EFI_DEVICE_PATH_PROTOCOL   *File,
  IN  VOID                             *FileBuffer,
  IN  UINTN                             FileSize
);

/**
This is the function will be return secure boot enabled or not.

  @param[in/out]            secure boot enable state.

  @retval EFI_SUCCESS       query successfully.
  @retval EFI_INTERNAL_     query failed

**/

EFI_STATUS EFIAPI SecBootEnabled( BOOLEAN *Enabled );

#endif /* __SECBOOTLIB_H__ */
