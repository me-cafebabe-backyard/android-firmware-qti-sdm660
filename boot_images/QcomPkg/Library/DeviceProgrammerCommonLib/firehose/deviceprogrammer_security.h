/*==================================================================

GENERAL DESCRIPTION
  This module contains the authentication and some calls to the hashing
  functions used by device programmer.

Copyright (c) 2013-2015 by Qualcomm Technologies, Incorporated.
All Rights Reserved.
=========================================================================*/

/*=========================================================================

                      EDIT HISTORY FOR FILE

  This section contains comments describing changes made to the
  module. Notice that changes are listed in reverse chronological
  order.

  $Header: //components/rel/boot.xf/1.4/QcomPkg/Library/DeviceProgrammerCommonLib/firehose/deviceprogrammer_security.h#2 $ 
  $DateTime: 2016/08/19 05:58:45 $ $Author: c_mvanim $

YYYY-MM-DD   who   what, where, why
----------   ---   ----------------------------------------------
2015-08-04   wek   Move Sha functions to a separate file.
2014-10-02   ah    Major code clean up
2013-06-03   ah    Added legal header
2013-05-31   ab    Initial checkin

=========================================================================*/

#ifndef DEVICEPROGRAMMER_SECURITY_H
#define DEVICEPROGRAMMER_SECURITY_H

#include "deviceprogrammer_utils.h"
#include "deviceprogrammer_sha.h"

void PerformSHA256(uint8* inputPtr, uint32 inputLen,uint8* outputPtr);

uint32 getChipSerialNum(void);

boolean authenticateSignedHash(byte *buffer,
                               SIZE_T length,
                               byte** hash_position_address,
                               SIZE_T *signed_payload_size);

boolean isSecureBootEnabled(void);

#endif
