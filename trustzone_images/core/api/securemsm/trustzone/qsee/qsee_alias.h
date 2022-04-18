#ifndef QSEE_ALIAS_H
#define QSEE_ALIAS_H

/*============================================================================
Copyright (c) 2012 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
=========================================================================== */

/*=========================================================================
                              Edit History

  $Header: //components/rel/core.tz/1.0.7.1/api/securemsm/trustzone/qsee/qsee_alias.h#1 $
  $DateTime: 2020/01/14 12:35:09 $
  $Author: pwbldsvc $


when       who     what, where, why
--------   ---     --------------------------------------------------------
08/04/11    rv     Initial Revision

=========================================================================== */

#define TZOS_VERSION_MAJOR QSEE_VERSION_MAJOR
#define TZOS_VERSION_MINOR QSEE_VERSION_MINOR


#define tzos_get_uptime qsee_get_uptime
#define tzos_wdog_stop qsee_wdog_stop
#define tzos_wdog_pet qsee_wdog_pet

#define tzos_sc_ss_e_type qsee_sc_ss_e_type
#define tzos_secure_message qsee_secure_message
#define tzos_authenticate_decrypt_message qsee_authenticate_decrypt_message

#define TZOS_MAX_PRNG QSEE_MAX_PRNG
#define tzos_prng_getdata qsee_prng_getdata

#define tzos_printf qsee_printf

#define TZOS_HMAC_SHA1 QSEE_HMAC_SHA1
#define TZOS_HMAC_SHA256 QSEE_HMAC_SHA256
#define TZOS_HMAC_ALGO_ET QSEE_HMAC_ALGO_ET
#define tzos_hmac qsee_hmac

#define tzos_malloc qsee_malloc
#define tzos_free qsee_free

#define TZOS_SHA1_HASH_SZ    QSEE_SHA1_HASH_SZ
#define TZOS_SHA256_HASH_SZ  QSEE_SHA1_HASH_SZ
#define tzos_hash_ctx qsee_hash_ctx
#define TZOS_HASH_NULL QSEE_HASH_NULL
#define TZOS_HASH_SHA1 QSEE_HASH_SHA1
#define TZOS_HASH_SHA256 QSEE_HASH_SHA256
#define TZOS_HASH_ALGO_ET QSEE_HASH_ALGO_ET
#define tzos_hash qsee_hash
#define tzos_hash_init qsee_hash_init
#define tzos_hash_update qsee_hash_update
#define tzos_hash_final qsee_hash_final
#define tzos_hash_free_ctx qsee_hash_free_ctx

#define TZOS_HLOS_IMG_TAMPER_FUSE QSEE_HLOS_IMG_TAMPER_FUSE
#define TZOS_NUM_SW_FUSES QSEE_NUM_SW_FUSES
#define tzos_sw_fuse_t qsee_sw_fuse_t
#define tzos_is_sw_fuse_blown qsee_is_sw_fuse_blown
#define tzos_blow_sw_fuse qsee_blow_sw_fuse
#define tzos_fuse_write qsee_fuse_write
#define tzos_fuse_read qsee_fuse_read

#define tzos_crypto_lock_engine qsee_crypto_lock_engine

#define TZOS_MEM_TAG_USECASE_CP QSEE_MEM_TAG_USECASE_CP
#define TZOS_MEM_TAG_USECASE_MAX QSEE_MEM_TAG_USECASE_MAX
#define tzos_mem_usecase_tag_id_t qsee_mem_usecase_tag_id_t

#define tzos_exec_protect_memory qsee_exec_protect_memory
#define tzos_read_jtag_id qsee_read_jtag_id
#define tzos_read_serial_num qsee_read_serial_num
#define tzos_jtag_override qsee_jtag_override
#define tzos_is_ns_range qsee_is_ns_range
#define tzos_is_s_tag_area qsee_is_s_tag_area

#define tzos_request_service qsee_request_service

#define tzos_strnicmp qsee_strnicmp
#define tzos_strlcpy qsee_strlcpy
#define tzos_strlcat qsee_strlcat
#define tzos_wstrlen qsee_wstrlen
#define tzos_wstrlcat qsee_wstrlcat
#define tzos_strtowstr qsee_strtowstr
#define tzos_wstrtostr qsee_wstrtostr
#define tzos_floattowstr qsee_floattowstr
#define tzos_wstrchr qsee_wstrchr
#define tzos_wstrcmp qsee_wstrcmp

#define TZOS_AES128_IV_SIZE         QSEE_AES128_IV_SIZE
#define TZOS_AES128_KEY_SIZE        QSEE_AES128_KEY_SIZE
#define TZOS_AES256_IV_SIZE         QSEE_AES256_IV_SIZE
#define TZOS_AES256_KEY_SIZE        QSEE_AES256_KEY_SIZE
#define tzos_cipher_ctx qsee_cipher_ctx
#define TZOS_CIPHER_ALGO_AES_128 QSEE_CIPHER_ALGO_AES_128
#define TZOS_CIPHER_ALGO_AES_256 QSEE_CIPHER_ALGO_AES_256
#define TZOS_CIPHER_ALGO_ET QSEE_CIPHER_ALGO_ET
#define TZOS_CIPHER_PARAM_KEY QSEE_CIPHER_PARAM_KEY
#define TZOS_CIPHER_PARAM_IV QSEE_CIPHER_PARAM_IV
#define TZOS_CIPHER_PARAM_MODE QSEE_CIPHER_PARAM_MODE
#define TZOS_CIPHER_PARAM_PAD QSEE_CIPHER_PARAM_PAD
#define TZOS_CIPHER_PARAM_ET QSEE_CIPHER_PARAM_ET
#define TZOS_CIPHER_MODE_ECB QSEE_CIPHER_MODE_ECB
#define TZOS_CIPHER_MODE_CBC QSEE_CIPHER_MODE_CBC
#define TZOS_CIPHER_MODE_CTR QSEE_CIPHER_MODE_CTR
#define TZOS_CIPHER_MODE_ET QSEE_CIPHER_MODE_ET
#define TZOS_CIPHER_PAD_ISO10126 QSEE_CIPHER_PAD_ISO10126
#define TZOS_CIPHER_PAD_PKCS7 QSEE_CIPHER_PAD_PKCS7
#define TZOS_CIPHER_PAD_NO_PAD QSEE_CIPHER_PAD_NO_PAD
#define TZOS_CIPHER_PAD_ET QSEE_CIPHER_PAD_ET
#define tzos_cipher_init qsee_cipher_init
#define tzos_cipher_free_ctx qsee_cipher_free_ctx
#define tzos_cipher_set_param qsee_cipher_set_param
#define tzos_cipher_get_param qsee_cipher_get_param
#define tzos_cipher_encrypt qsee_cipher_encrypt
#define tzos_cipher_decrypt qsee_cipher_decrypt

#endif /*QSEE_ALIAS_H*/

