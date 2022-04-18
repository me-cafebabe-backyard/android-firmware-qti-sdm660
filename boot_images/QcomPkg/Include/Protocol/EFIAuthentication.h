/**
  @file EFIAuthentication.h
  @brief Declaration of PE/COFF image authentication Interface  
*/
/*=============================================================================
  Copyright (c) 2012 Qualcomm Technologies, Inc.
  All rights reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
=============================================================================*/

/*=============================================================================
                              EDIT HISTORY


 when        who     what, where, why
 --------    ---    -----------------------------------------------------------
 10/09/12    llg    (Tech Pubs) Edited/added Doxygen comments and markup.
 08/31/12    shl     Initial version.

=============================================================================*/
#ifndef __EFI_AUTHENTICATION_PROTOCOL_H__
#define __EFI_AUTHENTICATION_PROTOCOL_H__

/** @cond */
typedef struct _EFI_QCOM_AUTHENTICATION_PROTOCOL EFI_QCOM_AUTHENTICATION_PROTOCOL;
/** @endcond */

/*===========================================================================
  FUNCTION DEFINITIONS
===========================================================================*/
/* EFI_AUTHENTICATION_PE_IMAGE */
/** @ingroup efi_auth_pe_image
  @par Summary
  Verifies a PE/COFF image.   

  @param[in]     This        Pointer to the EFI_QCOM_AUTHENTICATION_PROTOCOL 
                             instance.
  @param[in,out] Buffer      Pointer to the start of the file buffer.
  @param[in]     BufferSize  Size of the file.

  @par Description
  This function is a shortcut of the existing security framework and it 
  implements exactly what the security framework does. The caller can locate 
  the protocol and then call this function to verify the image. 
  @par
  If the secure boot is not enabled, the function returns EFI_SUCCESS. 
  If the secure boot is enabled, it returns the result from the authentication 
  routine. If the secure boot is unknown, it returns a security violation for 
  conservation. 

  @return
  EFI_SUCCESS            -- Authentication passed.
  @par
  EFI_SECURITY_VIOLATION -- Authentication failed.
  @par
  EFI_INVALID_PARAMETER  -- Either the Buffer parameter is NULL or the 
                            BufferSize parameter \n
                            is 0. 
*/
typedef EFI_STATUS (EFIAPI *EFI_AUTHENTICATION_PE_IMAGE)(
    IN EFI_QCOM_AUTHENTICATION_PROTOCOL *This,
    IN OUT UINT8                        *Buffer,
    IN UINTN                             BufferSize);

/*===========================================================================
  PROTOCOL INTERFACE
===========================================================================*/
/** @ingroup efi_authentication_protocol
  @par Summary
  Qualcomm Authentication Protocol interface.

  @par Parameters
  @inputprotoparams{authentication_proto_params.tex} 
*/
struct _EFI_QCOM_AUTHENTICATION_PROTOCOL
{
  UINT64                          Revision;
  EFI_AUTHENTICATION_PE_IMAGE     AuthenticatePeImage;
}; 

/** @ingroup efi_authentication_constants */
/** Protocol version. */
#define AUTHENTICATION_REVISION 0x0000000000010000

/** @ingroup efi_authentication_protocol */
extern EFI_GUID gQcomAuthenticationProtocolGuid;

#endif
