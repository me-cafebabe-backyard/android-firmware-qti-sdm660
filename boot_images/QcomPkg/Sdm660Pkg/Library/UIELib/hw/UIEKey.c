/*===========================================================================
                Unified Image Encryption (UIE) L1 Fuse Key 

GENERAL DESCRIPTION
  Chipset-specific key source retrieval

Copyright (c) 2014 QUALCOMM Technologies Incorporated.  All Rights Reserved.
===========================================================================*/

/*===========================================================================
                                 INCLUDE FILES
===========================================================================*/
//#include <stddef.h>
#include <string.h>
#include "HALhwio.h"
#include "secboot_hwio.h"
#include "secboot_hw.h"
#include "UIE.h"
#include "UIEPriv.h"
#include "UIEEnv.h"

#define BREAKIF_SETSTATUS(cond, status_code) \
  if (cond) { ret = status_code; break; }

#define UIE_KEY_IMAGE_ENCR_ENABLED (0x1)
#define UIE_LEN_4BYTES (0x4)

bool uie_is_image_encryption_fuse_enabled(void)
{
  bool ret = false;
  uint32 encryption_enabled = 0;

  uie_map_fuse_area(HWIO_ADDR(OEM_CONFIG0), 0x1000);

  encryption_enabled = HWIO_INF(OEM_CONFIG0, IMAGE_ENCRYPTION_ENABLE);
    
  if (encryption_enabled == UIE_KEY_IMAGE_ENCR_ENABLED)
  {
    ret = true;
  }

  uie_unmap_fuse_area(HWIO_ADDR(OEM_CONFIG0), 0x1000);

  return ret;
}

int uie_get_l1_fuse_key(uie_key_src_t key_source, uint8 *key, uint32 keylen)
{
  int ret = UIE_STATUS_FAILURE;
  uint32 index = 0;
  uint32 fuse_row_value = 0;

  uint32 code_segment = uie_get_secboot_hw_code_segment();
  
  do
  {
    BREAKIF_SETSTATUS(key == NULL || keylen != UIE_KEY_LEN ||
                      (key_source != UIE_KEY_SRC_OTP_OEM &&
                       key_source != UIE_KEY_SRC_OTP_QC),
                      UIE_STATUS_INVALID_PARAM);

    uie_map_fuse_area(HWIO_ADDRI(OEM_IMAGE_ENCR_KEYn, 0), 0x1000);
    uie_map_fuse_area(HWIO_ADDR(IMAGE_ENCR_KEY1_0), 0x1000);

    /* OEM table */
    for (index=0; index < 4; index++)
    {
      /* Read image encryption key LSB */
      fuse_row_value =  HWIO_INI (OEM_IMAGE_ENCR_KEYn, index);
      UIE_MEMSCPY(&(key[4*index]), UIE_LEN_4BYTES, &fuse_row_value, UIE_LEN_4BYTES);
    }

    /* get the key and the function could return */
    ret = UIE_STATUS_SUCCESS;
    BREAKIF_SETSTATUS(uie_fec_error_occurred(), UIE_STATUS_KEY_READ_FAIL);
  } while(0);

  uie_unmap_fuse_area(HWIO_ADDRI(OEM_IMAGE_ENCR_KEYn, 0), 0x1000);
  uie_unmap_fuse_area(HWIO_ADDR(IMAGE_ENCR_KEY1_0), 0x1000);

  return ret;  
}

uint16 uie_get_fec()
{
  // Get the FEC out
  return HWIO_INM(FEC_ESR, HWIO_FMSK(FEC_ESR, CORR_SEEN));
}

void uie_clear_fec()
{
  // Writing a 0x1 clears the FEC
  HWIO_OUT(FEC_ESR, 0x1);
}
