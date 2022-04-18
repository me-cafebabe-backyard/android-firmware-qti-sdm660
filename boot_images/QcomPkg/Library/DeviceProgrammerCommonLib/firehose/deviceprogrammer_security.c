/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

GENERAL DESCRIPTION
  This module contains the authentication and some calls to the hashing
  functions used by device programmer.

Copyright (c) 2013-2016 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/


/*===========================================================================

                        EDIT HISTORY FOR MODULE


when         who   what, where, why
----------   ---   ----------------------------------------------------------
2016-12-19   sb    Enable Device Programmer VIP.
2016-03-09   wek   Fix feature define for Hashing.
2015-10-02   wek   Move SHA functions from security to a new file.
2014-10-02   ah    Major code clean up 
2014-05-23   wek   Compile for 64 bit.
2013-06-03   ah    Added legal header
2013-05-31   ab    Initial checkin
 
===========================================================================*/


/*===========================================================================

                     INCLUDE FILES FOR MODULE

===========================================================================*/
#include <stdio.h>
#include <string.h>
//#include <basetypes.h>
//#include <basetypes_qcom.h>
//#include <memory.h>
#include <comdef.h>
#include "deviceprogrammer_security.h"
#include "deviceprogrammer_firehose.h"
#include "stringl/stringl.h"

#include "boot_util.h"
//#include "boot_sbl_if.h"
#include "secboot_hw.h"
#include "secboot.h"
#include BOOT_PBL_H

extern firehose_protocol_t fh;

#include "boot_authenticator.h"

#include "boot_fastcall_tz.h"
sec_img_auth_error_type boot_sec_img_auth_verify_signature(uint8 *buf, uint32 size, uint32 sw_id, uint32 sw_ver, uint32 code_segment)
{
  sec_img_auth_verified_info_s v_info_inst;
  sec_img_auth_verified_info_s *v_info = &v_info_inst;

  sec_img_auth_error_type auth_error_type = SEC_IMG_AUTH_FAILURE;

  boot_tz_indirect_arg_list_t indirect_arg_list;

  indirect_arg_list.arg[0] = (uintnt) sw_ver;
  indirect_arg_list.arg[1] = (uintnt) code_segment;
  indirect_arg_list.arg[2] = (uintnt) v_info;
  indirect_arg_list.arg[3] = (uintnt) sizeof(*v_info);

  auth_error_type = boot_fastcall_tz_no_rsp (TZ_PIL_SECBOOT_VERIFY_SIG_ID,
                                    TZ_PIL_SECBOOT_VERIFY_SIG_ID_PARAM_ID,
                                    buf,
                                    size,
                                    sw_id,
                                    &indirect_arg_list);

  return auth_error_type;
}

boolean AuthenticateImage_v2(uint8 *buf, uint32 size, uint32 sw_id, uint32 sw_ver, uint32 code_segment)
{
  sec_img_auth_error_type auth_error_type = SEC_IMG_AUTH_FAILURE;
  auth_error_type = boot_sec_img_auth_verify_signature(buf, size,  sw_id, sw_ver, code_segment);
  if (auth_error_type == SEC_IMG_AUTH_SUCCESS)
  {
    return TRUE;
  }
  return FALSE;
}

#ifdef FEATURE_DEVPRG_SOFTWARE_HASH
static void PerformSHA256_i(uint8* inputPtr, uint32 inputLen, uint8* outputPtr)
{
  struct __sechsh_ctx_s   context;

  sechsharm_sha256_init  (&context);
  sechsharm_sha256_update(&context,
                        context.leftover,
                        &(context.leftover_size),
                        inputPtr,
                        inputLen);

  sechsharm_sha256_final (&context,
                        context.leftover,
                        &(context.leftover_size),
                        outputPtr);

}

#else /* No hardware SHA, use software. */
static void PerformSHA256_i(uint8* inputPtr, uint32 inputLen, uint8* outputPtr)
{
    CeMLCntxHandle*     cntx = NULL;
    CEMLIovecListType   ioVecIn;
    CEMLIovecListType   ioVecOut;
    CEMLIovecType       IovecIn;
    CEMLIovecType       IovecOut;
    uint32              digest_len = CEML_HASH_DIGEST_SIZE_SHA256;

    /* Input IOVEC */
    ioVecIn.size = 1;
    ioVecIn.iov = &IovecIn;
    ioVecIn.iov[0].dwLen = inputLen; //msg_len;
    ioVecIn.iov[0].pvBase = inputPtr; //msg;

    /* Output IOVEC */
    ioVecOut.size = 1;
    ioVecOut.iov = &IovecOut;
    ioVecOut.iov[0].dwLen = digest_len;
    ioVecOut.iov[0].pvBase = outputPtr; //result_digest;


    CeMLInit();
    CeMLHashInit(&cntx, CEML_HASH_ALGO_SHA256);
    CeMLHashUpdate(cntx, ioVecIn);

    CeMLHashFinal(cntx, &ioVecOut);

    CeMLHashDeInit(&cntx);

    CeMLDeInit();
}
#endif

void PerformSHA256(uint8* inputPtr, uint32 inputLen, uint8* outputPtr)
{
  PerformSHA256_i(inputPtr, inputLen, outputPtr);
}

extern boot_pbl_shared_data_type *pbl_shared_global;

ALIGN(32)  secboot_image_info_type     image_info;

#ifdef FEATURE_BOOT_EXTERN_SECBOOT_COMPLETED
ALIGN(32)  secboot_verified_info_type  verified_info;
#else
ALIGN(32)  pbl_secboot_verified_info_type  verified_info;
#endif

// return serial number of chip
uint32 getChipSerialNum(void)
{
    static uint32 serialNum = 0;

    secboot_hw_etype err;

    if (serialNum == 0)
    {
        err = secboot_hw_get_serial_num(&serialNum);
        if (err != E_SECBOOT_HW_SUCCESS)
        {
            logMessage("Cannot get chip serial number, secboot_hw_get_serial_num() returned errno=%d",err);
            MyErrorMessage(FAILURE_CHIP_SERIAL_NUMBER);
        }
    }
    return serialNum;
}

boolean isSecureBootEnabled(void)
{
  boot_boolean enabled;
  if (boot_is_auth_enabled(&enabled) == E_SECBOOT_HW_SUCCESS ) {
    if (enabled == 1)
      return TRUE;
  }
  return FALSE;
}

boolean AuthenticateImage(byte* src_ptr)
{
    secboot_error_type sec_status = E_SECBOOT_SUCCESS;

    secboot_handle_type  secboot_handle;

    secboot_hw_ftbl_type *hw_ftbl_ptr;

    // The purpose of this block is to store the ftables into hw_ftbl_ptr and
    // ftbl_ptr. Note that ftbl_ptr is a different type based on the ifdef.
#ifdef FEATURE_BOOT_EXTERN_SECBOOT_COMPLETED
    secboot_hw_etype sec_hw_status;

    secboot_hw_ftbl_type hw_ftbl;
    secboot_ftbl_type ftbl;

    hw_ftbl_ptr = &hw_ftbl;
    secboot_ftbl_type *ftbl_ptr = &ftbl;

    /* If we have a local secboot lib compiled in, use sbl's secboot lib */
    sec_status = secboot_get_ftbl(&ftbl);
    if (sec_status != E_SECBOOT_SUCCESS)
    {
        logMessage("secboot_get_ftbl(&ftbl) == %d (E_SECBOOT_SUCCESS == %d)", sec_status, E_SECBOOT_SUCCESS);
        MyErrorMessage(AUTHENTICATE_IMAGE_FAILURE);
        return FALSE;
    }
    sec_hw_status = secboot_hw_get_ftbl(&hw_ftbl);
    if (sec_hw_status != E_SECBOOT_HW_SUCCESS)
    {
        logMessage("secboot_hw_get_ftbl(&ftbl) == %d (E_SECBOOT_HW_SUCCESS == %d)", sec_hw_status, E_SECBOOT_HW_SUCCESS);
        MyErrorMessage(AUTHENTICATE_IMAGE_FAILURE);
        return FALSE;
    }
#else
    hw_ftbl_ptr = &(pbl_shared_global->secboot_shared_data->pbl_secboot_hw_ftbl);
    pbl_secboot_ftbl_type *ftbl_ptr = &(pbl_shared_global->secboot_shared_data->pbl_secboot_ftbl);

    if(hw_ftbl_ptr == NULL || ftbl_ptr == NULL)
    {
        logMessage("hw_ftbl_ptr == NULL || ftbl_ptr == NULL");
        MyErrorMessage(AUTHENTICATE_IMAGE_FAILURE);
        return FALSE;
    }
#endif

    if(isSecureBootEnabled() == FALSE)
    {
        logMessage("Secure Boot is not enabled on the HW, so no need to check the Digital Signature on this digest table");
        logMessage("This is okay, this can be used to test VIP");
        return TRUE;
    }

    // To be this far means secure boot is enabled, and this programmer must be signed.
    // Therefore check the signature of the digest table as well

    //memset(&verified_info, 0, sizeof(secboot_verified_info_type)); // change below for klocwork fix
    memset(&verified_info, 0, sizeof(verified_info));

    // Initializes the secboot handle and Crypto HW engine
    sec_status = ftbl_ptr->secboot_init(NULL, &secboot_handle);
    if (E_SECBOOT_SUCCESS != sec_status)
    {
        logMessage("AuthenticateImage() Returning FALSE, pbl_secboot_ftbl_ptr->secboot_init(NULL, &secboot_handle) returned 0x%0X, not (E_SECBOOT_SUCCESS == 0x%0X)", sec_status, E_SECBOOT_SUCCESS);
        MyErrorMessage(AUTHENTICATE_IMAGE_FAILURE);
        return FALSE;
    }

    if(fh.attrs.Verbose == TRUE)
    {
        logMessage("Calling ftbl_ptr->secboot_authenticate with image_info.signature_len = 0x%X",image_info.signature_len);
        logMessage("Calling ftbl_ptr->secboot_authenticate with image_info.sw_type = 0x%X",image_info.sw_type);
        logMessage("Calling ftbl_ptr->secboot_authenticate with image_info.sw_version = 0x%X",image_info.sw_version);
    }

    sec_status = ftbl_ptr->secboot_authenticate(&secboot_handle,
                                                    SECBOOT_HW_APPS_CODE_SEGMENT,
                                                    &image_info,
                                                    &verified_info);
    if (E_SECBOOT_SUCCESS != sec_status)
    {
        logMessage("AuthenticateImage() Returning FALSE, secboot_authenticate() returned 0x%X (not E_SECBOOT_SUCCESS=0x%X)", sec_status,E_SECBOOT_SUCCESS);
        MyErrorMessage(AUTHENTICATE_IMAGE_FAILURE);

        ftbl_ptr->secboot_deinit(&secboot_handle);
        return FALSE;
    }

    // Deinitializes the secboot handle and Crypto HW engine
    ftbl_ptr->secboot_deinit(&secboot_handle);

    return TRUE;
}

typedef struct
{
  uint32  codeword;            /* Codeword/magic number defining flash type
                                  information. */
  uint32  magic;               /* Magic number */
  uint32  RESERVED_0;          /* RESERVED */
  uint32  RESERVED_1;          /* RESERVED */
  uint32  RESERVED_2;          /* RESERVED */
  uint32  image_src;             /* Location of RPM_SBL in flash or e-hostdl in RAM. This is given in
                                  byte offset from beginning of flash/RAM.  */
  uint32 image_dest_ptr;        /* Pointer to location to store RPM_SBL/e-hostdl in RAM.
                                  Also, entry point at which execution begins.
                                  */
  uint32  image_size;      /* Size of RPM_SBL image in bytes */
  uint32  code_size;       /* Size of code region in RPM_SBL image in bytes */
  uint32  signature_ptr;         /* Pointer to images attestation signature */
  uint32  signature_size;        /* Size of the attestation signature in
                                  bytes */
  uint32  cert_chain_ptr;  /* Pointer to the chain of attestation
                                  certificates associated with the image. */
  uint32  cert_chain_size; /* Size of the attestation chain in bytes */

  uint32  oem_root_cert_sel;  /* Root certificate to use for authentication.
                                 Only used if SECURE_BOOT1 table_sel fuse is
                                 OEM_TABLE. 1 indicates the first root
                                 certificate in the chain should be used, etc */
  uint32  oem_num_root_certs; /* Number of root certificates in image.
                                 Only used if SECURE_BOOT1 table_sel fuse is
                                 OEM_TABLE. Denotes the number of certificates
                                 OEM has provisioned                          */

  uint32  RESERVED_5;          /* RESERVED */
  uint32  RESERVED_6;          /* RESERVED */
  uint32  RESERVED_7;          /* RESERVED */
  uint32  RESERVED_8;          /* RESERVED */
  uint32  RESERVED_9;          /* RESERVED */
} eighty_byte_header_type;

typedef struct
{
  uint32 image_id;       /* Identifies the type of image this header
                                 represents (OEM SBL, AMSS, Apps boot loader,
                                 etc.). */
  uint32 header_vsn_num;     /* Header version number. */
  uint32 image_src;          /* Location of image in flash: Address of
                                 image in NOR or page/sector offset to image
                                 from page/sector 0 in NAND/SUPERAND. */
  uint32 image_dest_ptr;     /* Pointer to location to store image in RAM.
                                 Also, entry point at which image execution
                                 begins. */
  uint32 image_size;         /* Size of complete image in bytes */
  uint32 code_size;          /* Size of code region of image in bytes */
  uint32 signature_ptr;      /* Pointer to images attestation signature */
  uint32 signature_size;     /* Size of the attestation signature in
                                 bytes */
  uint32 cert_chain_ptr;     /* Pointer to the chain of attestation
                                 certificates associated with the image. */
  uint32 cert_chain_size;    /* Size of the attestation chain in bytes */

} forty_byte_header_type;

boolean authenticateSignedHash(byte *buffer, SIZE_T length, byte** hash_position_address, SIZE_T *signed_payload_size)
{
    boolean retval,HeaderIs80Bytes=0;

    //uint32 sec_cert_chain_size = 6144;
    uint32 eighty_byte_header_magic = 0x73D71034;

    forty_byte_header_type *forty_byte_header_ptr = (forty_byte_header_type *) buffer;
    eighty_byte_header_type *eighty_byte_header_ptr = (eighty_byte_header_type *) buffer;

    if (length < sizeof(eighty_byte_header_type) || hash_position_address == NULL)
    {
        logMessage("Length (== %lld) < sizeof(eighty_byte_header_type) || hash_position_address (==%p) == NULL", length, hash_position_address);
        return FALSE;
    }

    memset(&image_info, 0, sizeof(secboot_image_info_type));
    
    //image_info.sw_version      = NumOfOneBitsIn(TZ_ANTI_REPLAY_FUSES);
    image_info.sw_type         = DEVICEPROGRAMMER_SW_ID; //Type identifier for image during signing
    image_info.header_ptr_1    = buffer;

    if (eighty_byte_header_ptr->magic == eighty_byte_header_magic) 
    {
        HeaderIs80Bytes = 1;
        image_info.header_len_1    = sizeof(eighty_byte_header_type);
        image_info.code_ptr_1      = &buffer[eighty_byte_header_ptr->image_src];
        image_info.code_len_1      = eighty_byte_header_ptr->code_size;
        image_info.x509_chain_ptr  = &buffer[eighty_byte_header_ptr->image_src + eighty_byte_header_ptr->cert_chain_ptr];
        image_info.x509_chain_len  = eighty_byte_header_ptr->cert_chain_size;
        image_info.signature_ptr   = &buffer[eighty_byte_header_ptr->image_src + eighty_byte_header_ptr->signature_ptr];
        image_info.signature_len   = eighty_byte_header_ptr->signature_size;
    }
    else 
    {
        HeaderIs80Bytes = 0;
        image_info.header_len_1    = sizeof(forty_byte_header_type);
        image_info.code_ptr_1      = &buffer[forty_byte_header_ptr->image_src];
        image_info.code_len_1      = forty_byte_header_ptr->code_size;
        image_info.x509_chain_ptr  = &buffer[forty_byte_header_ptr->image_src + forty_byte_header_ptr->cert_chain_ptr];
        image_info.x509_chain_len  = forty_byte_header_ptr->cert_chain_size;
        image_info.signature_ptr   = &buffer[forty_byte_header_ptr->image_src + forty_byte_header_ptr->signature_ptr];
        image_info.signature_len   = forty_byte_header_ptr->signature_size;
    }

    logMessage("Image Total Size          = 0x%X (%lld)",length,length);
    logMessage("HeaderIs80Bytes           = 0x%X",HeaderIs80Bytes);
    logMessage("image_info.sw_type        = 0x%X (DeviceProgrammer *insists* on this)",image_info.sw_type);
    logMessage("image_info.sw_version     = 0x%X",image_info.sw_version);
    logMessage("image_info.header_len_1   = 0x%X",image_info.header_len_1);
    logMessage("image_info.code_ptr_1     = 0x%X",image_info.code_ptr_1);
    logMessage("image_info.code_len_1     = 0x%X",image_info.code_len_1);
    logMessage("image_info.x509_chain_ptr = 0x%X",image_info.x509_chain_ptr);
    logMessage("image_info.x509_chain_len = 0x%X",image_info.x509_chain_len);
    logMessage("image_info.signature_ptr  = 0x%X",image_info.signature_ptr);
    logMessage("image_info.signature_len  = 0x%X",image_info.signature_len);
    logMessage("image_info.header_ptr_1   = 0x%X",image_info.header_ptr_1);
    
/*
    if (image_info.code_len_1 > sizeof(fh.validation_hash_buffer))
    {
       logMessage("The HEADER indicates that this packet is > fh.validation_hash_buffer capacity");
       return FALSE;
    }
*/
    if(isSecureBootEnabled() == FALSE)
    {
        *hash_position_address  = (byte *) image_info.code_ptr_1;
        *signed_payload_size    = image_info.code_len_1;
        logMessage("Secure Boot *not* enabled BUT VIP *is* enabled. Therefore will *not* check digital signature on Digest Table. This allows easier testing on non-secure targets");
        return TRUE;
    }


    if(fh.attrs.Verbose == TRUE)
        logMessage("Calling AuthenticateImage");

    retval = AuthenticateImage_v2(buffer, length,  image_info.sw_type, image_info.sw_version, SECBOOT_HW_APPS_CODE_SEGMENT);
//    retval = AuthenticateImage(buffer);
    logMessage("Back from AuthenticateImage, retval=0x%X",retval);

    if(fh.attrs.Verbose == TRUE)
        logMessage("Back from AuthenticateImage, retval=0x%X",retval);

    if (retval == TRUE)
    {
        *hash_position_address  = (byte *) image_info.code_ptr_1;
        *signed_payload_size    = image_info.code_len_1;

        if(fh.attrs.Verbose == TRUE)
            logMessage("signed_payload_size=0x%X",*signed_payload_size);
    }

    return retval;
}

