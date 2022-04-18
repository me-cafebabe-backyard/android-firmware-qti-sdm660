/** @file app_sp_keymaster_test.c
 * @brief
 * This file contains the definition of QSEE SPCOM testing routines.
 */
/*===========================================================================
  Copyright (c) 2016 Qualcomm Technologies Incorporated.
  All Rights Reserved.
  Qualcomm Confidential and Proprietary
===========================================================================*/

/*===========================================================================

                      EDIT HISTORY FOR FILE

  $Header: //components/rel/core.tz/1.0.7.1/securemsm/trustzone/qsapps/sampleapp/src/app_sp_keymaster_test.c#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
07/14/15   rb      Created

===========================================================================*/

/*===========================================================================

                     INCLUDE FILES FOR MODULE

===========================================================================*/
#include <stdbool.h>
#include <stdint.h>
#include <stringl.h> /* secure_memset() */

#include "qsee_heap.h" /* qsee_malloc() */
#include "qsee_log.h"
#include "qsee_rsa.h"
#include "qsee_ecc.h"

#include "sp_keymaster.h"

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * ----------------------------------------------------------------------*/
#define LOGD(format, args...)        qsee_printf("sp_keymaster_tester dbg: [%s] " format, __func__, ##args)
#define LOGI(format, args...)        qsee_printf("sp_keymaster_tester inf: [%s] " format, __func__, ##args)
#define LOGE(format, args...)        qsee_printf("sp_keymaster_tester err: [%s] " format, __func__, ##args)

/*-------------------------------------------------------------------------
 * Static Functions
 * ----------------------------------------------------------------------*/

#define MSW (QSEE_BIGLEN - 1)
#define big_is_negative(a) ((int32_t)(a)->data[MSW] < 0)

/*
 * Converts bigval_t src to a network order (big-endian) binary (byte
 * vector) representation. The if tgtlen is longer that the bigval_t,
 * the value is written sign-extended.  If tgtlen is too small to hold
 * the value, high order bytes are silently dropped.
 */
static void bigval_to_binary(QSEE_bigval_t const *src, void *tgt, size_t tgtlen)
{
   size_t i;
   uint8_t v;
   uint8_t highbytes = big_is_negative(src) ? 0xff : 0;

   /* LSbyte to MS_byte */
   for (i = 0; i < 4 * QSEE_BIGLEN; ++i) {
      if (i < tgtlen) {
	 v = src->data[i/4] >> (8 * (i % 4));
	 ((uint8_t *)tgt)[tgtlen - 1 - i] = v;
      }
   }
   /* i is live */
   for (; i < tgtlen; ++i) {
      ((uint8_t *)tgt)[tgtlen - 1 - i] = highbytes;
   }
}

/*
 * Converts a network-order (big-endian) binary value (byte array) at
 * *src of length srclen to a bigval_t at *bn.  If srclen is larger
 * then the length of a bigval_t, the high order bytes are silently
 * dropped.
 */
static void binary_to_bigval(const void* src, QSEE_bigval_t *tgt, size_t srclen)
{
   size_t i;
   uint8_t v;

   /* zero the bigval_t */
   for (i = 0; i < QSEE_BIGLEN; ++i) {
      tgt->data[i] = 0;
   }
   /* scan from LSbyte to MSbyte */
   for (i = 0; i < srclen && i < 4 * QSEE_BIGLEN; ++i) {
      v = ((uint8_t *)src)[srclen - 1 - i];
      tgt->data[i/4] |= (uint32_t)v << (8 * (i % 4));
   }
}

static int init_bkey(QSEE_S_BIGINT **key, uint8_t *key_buff, int key_len)
{
   int ret = 0;
   
   *key = (QSEE_S_BIGINT *)qsee_malloc(sizeof(QSEE_S_BIGINT));
   if( NULL == *key )
   {
      ret = -1;
      goto exit_err;
   }
   ret = qsee_BIGINT_read_unsigned_bin(&(*key)->bi, key_buff, key_len);
   if (0 != ret) {
      goto exit_err;
   }
   (*key)->bi.n = key_len/sizeof(QSEE_BLONG);
   (*key)->sign = 0; /* Positive */

exit_err:
   return ret;
}

int run_sp_keymaster_test(void)
{
	sp_km_result_e ret = 0;
	sp_km_ecdsa_key_blob_s *ecdsa_key_blob = NULL;
	sp_km_rsa_key_blob_s *rsa_key_blob = NULL;
	sp_km_ecdsa_signature *signature = NULL;
	unsigned char label[5] = "test";
	uint8_t *sig = NULL;
	uint8_t *plain = NULL;
	uint8_t digest[32] = {
		/* 0,    1,    2,    3,    4,    5,    6,    7,    8,    9,    A,    B,    C,    D,    E,    F */
		0x63, 0x8a, 0x8b, 0xd1, 0xfd, 0x6a, 0x35, 0x05, 0x3c, 0x16, 0x08, 0x4c, 0x8e, 0xf0, 0x71, 0x24, 
		0xee, 0xe9, 0x54, 0x9b, 0xd1, 0x67, 0xc8, 0x20, 0x6c, 0x17, 0xa2, 0xdf, 0xa1, 0x8a, 0x94, 0xcc
	};
	uint8_t cipher[256] = { 0 };
	sp_km_rsa_padding_type pad_type;
	sp_km_rsa_pss_pad_info pss_info;
	sp_km_rsa_oaep_pad_info oaep_info;
	sp_km_rsa_oaep_pad_info *oaep_info_ptr = NULL;
	uint8_t pad_buff[32] = { 0 };
	uint32_t key_blob_len = 0;
	uint32_t sig_len = 0;
	uint32_t plain_len = 0;
	uint32_t pub_exp = 0;
	uint32_t i = 0;
	int chiper_len = 0;

	int internal_ret = 0;
	QSEE_RSA_KEY qsee_rsa_key;
	QSEE_RSA_OAEP_PAD_INFO oaep_pad_info;
	QSEE_RSA_PSS_PAD_INFO pss_pad_info;
	QSEE_S_BIGINT qsee_e;
	QSEE_S_BIGINT qsee_d;
	QSEE_S_BIGINT qsee_n;

	QSEE_bigval_t qsee_ecda_priv_key;
	QSEE_affine_point_t qsee_ecda_pub_key;
	QSEE_bigval_t qsee_digest;
	QSEE_ECDSA_sig_t qsee_ecdsa_sig;

	LOGI("++++ SP-TZ KM tests started +++++.\n");
	ret = sp_km_init();
	if (SP_KM_SUCCESS != ret) {
		LOGE("sp_km_init() failed, ret [%d].\n", ret);
		ret = 1;
		goto exit_err;
	}

	LOGI("++++ ECDSA Test +++++.\n");

	/* ECDSA private key operations tests */
	LOGD("before sp_km_ecdsa_gen_key_blob().\n");
	ret = sp_km_ecdsa_gen_key_blob(&ecdsa_key_blob, &key_blob_len,
			SP_KM_CRYPTO_ECC_CURVE_P256);
	LOGD("after sp_km_ecdsa_gen_key_blob().\n");
	if (SP_KM_SUCCESS != ret) {
		LOGE("error during sp_km_ecdsa_gen_key_blob ret = %d\n", ret);
		ret = 1;
		goto exit_err;
	}

	LOGD("before sp_km_ecdsa_sign().\n");
	ret = sp_km_ecdsa_sign(ecdsa_key_blob, digest, 32, &signature, &sig_len);
	LOGD("after sp_km_ecdsa_sign().\n");
	if (SP_KM_SUCCESS != ret) {
		LOGE("during sp_km_ecdsa_sign ret = %d\n", ret);
		ret = 1;
		goto exit_err;
	}

	/* Crafting qsee key blob to verify sp keymaster signature */
	internal_ret = qsee_SW_ECC_PubPrivate_Key_generate(&qsee_ecda_pub_key, &qsee_ecda_priv_key);
	if (internal_ret) {
	   LOGE("qsee_SW_ECC_PubPrivate_Key_generate ret = %d\n", internal_ret);
		ret = 1;
		goto exit_err;
	}

	/* Converting binaries into bigval's for qsee */
	binary_to_bigval((const uint8_t *)ecdsa_key_blob + ecdsa_key_blob->public_key_x, 
		&(qsee_ecda_pub_key.x), ecdsa_key_blob->public_key_x_size);
	binary_to_bigval((const uint8_t *)ecdsa_key_blob + ecdsa_key_blob->public_key_y, 
		&(qsee_ecda_pub_key.y), ecdsa_key_blob->public_key_y_size);
	qsee_ecda_pub_key.infinity = 0;

	binary_to_bigval((const uint8_t *)signature + signature->r, 
		&(qsee_ecdsa_sig.r), signature->r_size);
	binary_to_bigval((const uint8_t *)signature + signature->s, 
		&(qsee_ecdsa_sig.s), signature->s_size);

	qsee_ECC_hash_to_bigval(&(qsee_digest), digest, 32);

	/* Verify the signature using qsee API */
	internal_ret = qsee_SW_ECDSA_Verify(&qsee_digest, &qsee_ecda_pub_key, &qsee_ecdsa_sig);
	if (0 != internal_ret) {
		LOGE("qsee_SW_ECDSA_Verify ret = %d\n", internal_ret);
		ret = 1;
		goto exit_err;
	};

	LOGI("ECDSA signature P256 generated by SP and verified by qsee successfully\n");

	qsee_free(signature);
	qsee_free(ecdsa_key_blob);

	LOGI("++++ RSA 1024 Test +++++.\n");

	/* RSA private key operations tests */
	
	/* Initiate default public exponent */
	pub_exp = 65537; /* 0x10001 */
	LOGD("use pub_exp [%d]\n", (int) pub_exp);
	
	LOGD("before sp_km_rsa_gen_key_blob().\n");
	ret = sp_km_rsa_gen_key_blob(&rsa_key_blob, &key_blob_len,
			SP_KM_CRYPTO_RSA_KEY_1024_LEN, &pub_exp, sizeof(pub_exp));
	LOGD("after sp_km_rsa_gen_key_blob().\n");
	if (SP_KM_SUCCESS != ret) {
		LOGE("error during sp_km_rsa_gen_key_blob ret = %d\n", ret);
		ret = 1;
		goto exit_err;
	}

	/* Crafting qsee key blob to encrypt disget for sp keymaster to decrypt */
	secure_memset(&qsee_rsa_key, 0x0, sizeof(qsee_rsa_key));
	qsee_rsa_key.type = QSEE_RSA_KEY_PUBLIC;

	internal_ret = init_bkey(&(qsee_rsa_key.N), (uint8_t*)rsa_key_blob + rsa_key_blob->modulus, rsa_key_blob->modulus_size);
	if (0 != internal_ret) {
		LOGE("during init_bkey ret = %d\n", internal_ret);
		ret = 1;
		goto exit_err;
	};

	LOGD("RSA 1024 blob, public e exponent , offset [%d], size [%d]\n", rsa_key_blob->public_exponent , rsa_key_blob->public_exponent_size);
	LOGD("RSA 1024 blob, public N modulus , offset [%d], size [%d]\n", rsa_key_blob->modulus , rsa_key_blob->modulus_size);

	internal_ret = init_bkey(&(qsee_rsa_key.e), ((uint8_t*)rsa_key_blob) + rsa_key_blob->public_exponent, rsa_key_blob->public_exponent_size);
	if (0 != internal_ret) {
		LOGE("during init_bkey ret = %d\n", internal_ret);
		ret = 1;
		goto exit_err;
	}

	/* The maximum size of the cipher buffer is 128 bytes, as the key len. */
	chiper_len = 128;
	internal_ret = qsee_rsa_encrypt(&qsee_rsa_key, QSEE_RSA_PAD_PKCS1_V1_5_ENC, NULL, 
			(const unsigned char*)digest, 32, (unsigned char*)&cipher, &chiper_len);
	if (0 != internal_ret) {
		LOGE("during qsee_rsa_encrypt ret = %d, chiper_len = %d\n", internal_ret, chiper_len);
		ret = 1;
		goto exit_err;
	}

	/* Initiating the pad type for PKCS 1_5 decryption by the sp keymaster */
	pad_type = SP_KM_CRYPTO_RSA_ENC_PADDING_1_5;

	LOGD("before sp_km_rsa_decrypt().\n");
	ret = sp_km_rsa_decrypt(rsa_key_blob, pad_type, NULL, 0,
			SP_KM_HASH_IDX_SHA256,
			cipher, chiper_len,
			&plain, &plain_len);
	LOGD("after sp_km_rsa_decrypt().\n");
	if (SP_KM_SUCCESS != ret) {
		LOGE("error during sp_km_rsa_decrypt ret = %d\n", ret);
		ret = 1;
		goto exit_err;
	}

	internal_ret = memcmp(plain, digest, plain_len);
	if (0 != internal_ret) {
		LOGE("error plain not as expected\n");
		ret = 1;
		goto exit_err;
	} else {
		LOGI("RSA1024/PKCS1_V1_5 - plaintext encrypted using qsee_encrypt and decrypted using sp_keymaster successfully\n");
	}
	qsee_free(plain);

	/* Initiating the pad type for OAEP encryption by the qsee */
	oaep_pad_info.hashidx = QSEE_HASH_IDX_SHA256;
	oaep_pad_info.label = NULL;
	oaep_pad_info.labellen = 0;

	/* The maximum size of the cipher buffer is 128 bytes, as the key len. */
	chiper_len = 128;
	internal_ret = qsee_rsa_encrypt(&qsee_rsa_key, QSEE_RSA_PAD_PKCS1_OAEP, &oaep_pad_info, 
		(const unsigned char*)digest, 32, (unsigned char*)&cipher, &chiper_len);
		
	if (0 != internal_ret) {
		LOGE("during qsee_rsa_encrypt ret = %d, chiper_len = %d\n", internal_ret, chiper_len);
		ret = 1;
		goto exit_err;
	}
	/* Initiating the pad type for OAEP decryption by sp keymaster */
	pad_type = SP_KM_CRYPTO_RSA_ENC_PADDING_OAEP;
	oaep_info.label_len = 0;
	oaep_info.label = 0;

	LOGD("before sp_km_rsa_decrypt().\n");
	ret = sp_km_rsa_decrypt(rsa_key_blob, pad_type, &oaep_info, sizeof(oaep_info),
			SP_KM_HASH_IDX_SHA256,
			cipher, chiper_len,
			&plain, &plain_len);
	LOGD("after sp_km_rsa_decrypt().\n");
	if (SP_KM_SUCCESS != ret) {
		LOGE("error during sp_km_rsa_decrypt ret = %d\n", ret);
		ret = 1;
		goto exit_err;
	}

	internal_ret = memcmp(plain, digest, plain_len);
	if (0 != internal_ret) {
		LOGE("error plain not as expected\n");
		ret = 1;
		goto exit_err;
	} else {
		LOGI("RSA1024/PKCS1_OAEP - plaintext encrypted using qsee_encrypt and decrypted using sp_keymaster successfully\n");
	}
	qsee_free(plain);

	/* Initiating the pad type for PKCS 1_5 signature by sp keymaster */
	pad_type = SP_KM_CRYPTO_RSA_SIGN_PADDING_1_5;

	LOGD("before sp_km_rsa_sign().\n");
	ret = sp_km_rsa_sign(rsa_key_blob, pad_type, NULL, 0,
			SP_KM_HASH_IDX_SHA256, digest, 32, &sig, &sig_len);
	LOGD("after sp_km_rsa_sign().\n");
	if (SP_KM_SUCCESS != ret) {
		LOGE("error during sp_km_ecdsa_sign ret = %d\n", ret);
		ret = 1;
		goto exit_err;
	}

	internal_ret = qsee_rsa_verify_signature(&qsee_rsa_key, QSEE_RSA_PAD_PKCS1_V1_5_SIG, NULL, QSEE_HASH_IDX_SHA256,
		digest, 32, sig, sig_len);
	if (0 != internal_ret) {
		LOGE("during qqsee_rsa_verify_signature ret = %d\n", internal_ret);
		ret = 1;
		goto exit_err;
	}
	LOGI("RSA1024/PKCS1_V1_5 - signature verified by qsee successfully\n");

	qsee_free(sig);

	/* Initiating the pad type for PSS signature by sp keymaster */
	pad_type = SP_KM_CRYPTO_RSA_SIGN_PADDING_PSS;
	pss_info.salt_len = 4;

	LOGD("before sp_km_rsa_sign().\n");
	ret = sp_km_rsa_sign(rsa_key_blob, pad_type, (void*)(&pss_info), sizeof(pss_info),
			SP_KM_HASH_IDX_SHA256, digest, 32, &sig, &sig_len);
	LOGD("after sp_km_rsa_sign().\n");
	if (SP_KM_SUCCESS != ret) {
		LOGE("error during sp_km_ecdsa_sign ret = %d\n", ret);
		ret = 1;
		goto exit_err;
	}

	/* Initiating the pad type for PSS verification by qsee */
	pss_pad_info.hashidx = QSEE_HASH_IDX_SHA256;
	pss_pad_info.saltlen = 4;

	internal_ret = qsee_rsa_verify_signature(&qsee_rsa_key, QSEE_RSA_PAD_PKCS1_PSS, &pss_pad_info, QSEE_HASH_IDX_SHA256,
		digest, 32, sig, sig_len);
	if (0 != internal_ret) {
		LOGE("during qsee_rsa_verify_signature ret = %d\n", internal_ret);
		ret = 1;
		goto exit_err;
	}
	LOGI("RSA1024/PKCS1_PSS - signature verified by qsee successfully\n");
	qsee_free(sig);
	qsee_free(rsa_key_blob);
	free_key(qsee_rsa_key.N);
	free_key(qsee_rsa_key.e);

	LOGI("++++ RSA 2048 Test +++++.\n");

	pub_exp = 65537;
	LOGD("use pub_exp [%d]\n", (int) pub_exp);
	LOGD("before sp_km_rsa_gen_key_blob().\n");
	ret = sp_km_rsa_gen_key_blob(&rsa_key_blob, &key_blob_len, SP_KM_CRYPTO_RSA_KEY_2048_LEN, &pub_exp, sizeof(pub_exp));
	LOGD("after sp_km_rsa_gen_key_blob().\n");
	if (SP_KM_SUCCESS != ret) {
		LOGE("error during sp_km_rsa_gen_key_blob ret = %d\n", ret);
		ret = 1;
		goto exit_err;
	}

	LOGD("RSA 2048 blob, public e exponent , offset [%d], size [%d]\n", rsa_key_blob->public_exponent , rsa_key_blob->public_exponent_size);
	LOGD("RSA 2048 blob, public N modulus , offset [%d], size [%d]\n", rsa_key_blob->modulus , rsa_key_blob->modulus_size);

	/* Crafting qsee key blob to encrypt disget for sp keymaster to decrypt */
	secure_memset(&qsee_rsa_key, 0x0, sizeof(qsee_rsa_key));
	qsee_rsa_key.type = QSEE_RSA_KEY_PUBLIC;
	internal_ret = init_bkey(&(qsee_rsa_key.N), (uint8_t*)rsa_key_blob + rsa_key_blob->modulus, rsa_key_blob->modulus_size);
	if (0 != internal_ret) {
		LOGE("during qsee_rsa_encrypt ret = %d\n", internal_ret);
		ret = 1;
		goto exit_err;
	};

	internal_ret = init_bkey(&(qsee_rsa_key.e), ((uint8_t*)rsa_key_blob) + rsa_key_blob->public_exponent, rsa_key_blob->public_exponent_size);
	
	if (0 != internal_ret) {
		LOGE("during qsee_rsa_encrypt ret = %d\n", internal_ret);
		ret = 1;
		goto exit_err;
	}

	/* The maximum size of the chiper buffer is 256 bytes, as the key len. */
	chiper_len = 256;
	internal_ret = qsee_rsa_encrypt(&qsee_rsa_key, QSEE_RSA_PAD_PKCS1_V1_5_ENC, NULL, 
			(const unsigned char*)digest, 32, (unsigned char*)&cipher, &chiper_len);
	if (0 != internal_ret) {
		LOGE("during qsee_rsa_encrypt ret = %d, chiper_len = %d\n", internal_ret, chiper_len);
		ret = 1;
		goto exit_err;
	}

	/* Initiating the pad type for PKCS 1_5 decryption by sp keymaster */
	pad_type = SP_KM_CRYPTO_RSA_ENC_PADDING_1_5;

	ret = sp_km_rsa_decrypt(rsa_key_blob, pad_type, NULL, 0,
			SP_KM_HASH_IDX_SHA256,
			cipher, 256,
			&plain, &plain_len);
	if (SP_KM_SUCCESS != ret) {
		LOGE("error during sp_km_rsa_decrypt ret = %d\n", ret);
		ret = 1;
		goto exit_err;
	}

	LOGI("rsa plain_len = %d\n", plain_len);
	internal_ret = memcmp(plain, digest, plain_len);
	if (0 != internal_ret) {
		LOGE("error plain not as expected\n");
		ret = 1;
		goto exit_err;
	} else {
		LOGI("RSA2048/PKCS1_V1_5 - plaintext encrypted using qsee_encrypt and decrypted using sp_keymaster successfully\n");
	}
	qsee_free(plain);

	oaep_pad_info.hashidx = QSEE_HASH_IDX_SHA256;
	oaep_pad_info.label = label;
	oaep_pad_info.labellen = 4;

	/* The maximum size of the chiper buffer is 256 bytes, as the key len. */
	chiper_len = 256;
	internal_ret = qsee_rsa_encrypt(&qsee_rsa_key, QSEE_RSA_PAD_PKCS1_OAEP, &oaep_pad_info, 
			(const unsigned char*)digest, 32, (unsigned char*)&cipher, &chiper_len);
	if (0 != internal_ret) {
		LOGE("during qsee_rsa_encrypt ret = %d, chiper_len = %d\n", internal_ret, chiper_len);
		ret = 1;
		goto exit_err;
	}

	/* Initiating the pad type for OAEP decryption by sp keymaster */
	pad_type = SP_KM_CRYPTO_RSA_ENC_PADDING_OAEP;
	oaep_info_ptr = (sp_km_rsa_oaep_pad_info*)pad_buff;
	oaep_info_ptr->label_len = 4;
	oaep_info_ptr->label = sizeof(sp_km_rsa_oaep_pad_info);
	memcpy((uint8_t*)oaep_info_ptr + oaep_info_ptr->label, label, oaep_info_ptr->label_len);

	ret = sp_km_rsa_decrypt(rsa_key_blob, pad_type, oaep_info_ptr, 
			sizeof(sp_km_rsa_oaep_pad_info) + oaep_info_ptr->label_len,
			SP_KM_HASH_IDX_SHA256,
			cipher, chiper_len,
			&plain, &plain_len);
	if (SP_KM_SUCCESS != ret) {
		LOGE("error during sp_km_rsa_decrypt ret = %d\n", ret);
		ret = 1;
		goto exit_err;
	}

	internal_ret = memcmp(plain, digest, plain_len);
	if (0 != internal_ret) {
		LOGE("error plain not as expected\n");
		ret = 1;
		goto exit_err;
	} else {
		LOGI("RSA2048/PKCS1_OAEP - plaintext encrypted using qsee_encrypt and decrypted using sp_keymaster successfully\n");
	}
	qsee_free(plain);

	/* Initiating the pad type for PKCS 1_5 signature by sp keymaster */
	pad_type = SP_KM_CRYPTO_RSA_SIGN_PADDING_1_5;

	ret = sp_km_rsa_sign(rsa_key_blob, pad_type, NULL, 0,
			SP_KM_HASH_IDX_SHA256, digest, 32, &sig, &sig_len);
	if (SP_KM_SUCCESS != ret) {
		LOGE("error during sp_km_ecdsa_sign ret = %d\n", ret);
		ret = 1;
		goto exit_err;
	}

	internal_ret = qsee_rsa_verify_signature(&qsee_rsa_key, QSEE_RSA_PAD_PKCS1_V1_5_SIG, NULL, QSEE_HASH_IDX_SHA256,
		digest, 32, sig, sig_len);
	if (0 != internal_ret) {
		LOGE("during qqsee_rsa_verify_signature ret = %d\n", internal_ret);
		ret = 1;
		goto exit_err;
	}
	LOGI("RSA2048/PKCS1_V1_5 - signature verified by qsee successfully\n");
	qsee_free(sig);

	/* Initiating the pad type for PSS signature by sp keymaster */
	pad_type = SP_KM_CRYPTO_RSA_SIGN_PADDING_PSS;
	pss_info.salt_len = 4;

	ret = sp_km_rsa_sign(rsa_key_blob, pad_type, (void*)(&pss_info), sizeof(pss_info),
			SP_KM_HASH_IDX_SHA256, digest, 32, &sig, &sig_len);
	if (SP_KM_SUCCESS != ret) {
		LOGE("error during sp_km_ecdsa_sign ret = %d\n", ret);
		ret = 1;
		goto exit_err;
	}

	/* Initiating the pad type for PSS veification by qsee */
	pss_pad_info.hashidx = QSEE_HASH_IDX_SHA256;
	pss_pad_info.saltlen = 4;

	internal_ret = qsee_rsa_verify_signature(&qsee_rsa_key, QSEE_RSA_PAD_PKCS1_PSS, &pss_pad_info, QSEE_HASH_IDX_SHA256,
		digest, 32, sig, sig_len);
	if (0 != internal_ret) {
		LOGE("during qqsee_rsa_verify_signature ret = %d\n", internal_ret);
		ret = 1;
		goto exit_err;
	}

	LOGI("RSA2048/PKCS1_PSS - signature verified by qsee successfully\n");
	qsee_free(sig);
	qsee_free(rsa_key_blob);

exit_ok:
	sp_km_exit();
	LOGI("++++ tests finished successfully +++++.\n");
	return 0;

exit_err:
	sp_km_exit();
	LOGI("++++ tests Failed +++++.\n");
	return -1;
}

