/*==================================================================

GENERAL DESCRIPTION
  This module contains the software implementation for sha256.

Copyright (c) 2015 by Qualcomm Technologies, Incorporated.
All Rights Reserved.
=========================================================================*/

/*=========================================================================

                      EDIT HISTORY FOR FILE

  This section contains comments describing changes made to the
  module. Notice that changes are listed in reverse chronological
  order.

  $Header: //components/rel/boot.xf/1.4/QcomPkg/Library/DeviceProgrammerCommonLib/firehose/deviceprogrammer_sha.h#2 $ 
  $DateTime: 2016/08/19 05:58:45 $ $Author: c_mvanim $

YYYY-MM-DD   who   what, where, why
----------   ---   ----------------------------------------------
2015-08-04   wek   Create. Move SHA functions from security to a new file.

=========================================================================*/

#ifndef DEVICEPROGRAMMER_SHA_H
#define DEVICEPROGRAMMER_SHA_H

#include "deviceprogrammer_utils.h"
#include "stringl/stringl.h"

#define CONTEXT_LEFTOVER_FIELD_SIZE 64

/* This is the state of a running hash, known by all platforms */
struct __sechsh_ctx_s
{
    uint32  counter[2];
    uint32  iv[16];  // is 64 byte for SHA2-512
    uint8   leftover[CONTEXT_LEFTOVER_FIELD_SIZE];
    uint32  leftover_size;
};

void sechsharm_sha256_init(   struct __sechsh_ctx_s* );
void sechsharm_sha256_update( struct __sechsh_ctx_s*, uint8*, uint32*, uint8*, uint32 );
void sechsharm_sha256_final(  struct __sechsh_ctx_s*, uint8*, uint32*, uint8* );


#endif
