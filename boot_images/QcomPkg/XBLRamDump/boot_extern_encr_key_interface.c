
/*===========================================================================

                    BOOT ENCRYPTION EXTERN  DEFINITIONS

DESCRIPTION
  Contains wrapper definition for external AES key management code

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
Copyright 2017 by QUALCOMM Technologies Incorporated.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.
    
    
when       who     what, where, why
--------   ---     ----------------------------------------------------------
25/04/17   bd      Initial Creation.

===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/

#include "boot_extern_encr_key_interface.h"
#include "boot_dload_debug.h"
#include "boot_dload.h"
#include "boot_shared_functions.h"

#include <cil_ramdump.h>
#include <xbl_minidump_oem_public_key.h>

#include "LoaderUtils.h"
#include "boot_logger.h"


#if defined(PRODMODE)
#define DBG_MSG(x)  
#else
#define DBG_MSG(x)  boot_log_message(x)
#endif


#ifdef QCOM_XBL_MINIDUMP



static void dload_debug_encr_all_regions(void)
{
  uint32 i = 0;
  uint32 real_num_regions = dload_mem_debug_num_ent() % NUM_REGIONS;
  uint64 r_base, r_len ;
  char dbg_info[100];
  
  cil_md_crypto_init();
  
  for(i=0; i < real_num_regions; i++)
  {    
    r_base = dload_mem_debug_mem_base(i);
    r_len = dload_mem_debug_mem_length(i);
    
    snprintf(dbg_info, 100, "Encrypting region=%d base=0x%lx len=0x%lx", i, r_base, r_len);
    DBG_MSG(dbg_info);  
    
    cil_md_encrypt_region(r_base, r_len, i);
  } 
}


static void dload_debug_check_oem_key(void)
{
  int i ;
  uint32 real_num_regions = dload_mem_debug_num_ent() % NUM_REGIONS;
  uint64 r_base, r_len ;
  
  if(xbl_minidump_oem_public_key.n == NULL)
  {
    // if OEM key is absent zero out all regions
    for(i=0; i < real_num_regions; i++)
    {
      r_base = dload_mem_debug_mem_base(i);
      r_len = dload_mem_debug_mem_length(i);      
      memset((void*)r_base, 0, r_len);
    } 
  }
}


/*===========================================================================

**  Function :  dload_debug_handle_encryption

** ==========================================================================
*/
/*!
* 
* @brief
*   Perform encryption if secure device and OEM key is provided
*   If OEM key is not provided zero out all regions.
*
* @par Dependencies
*   This api must be called AFTER the debug table is populated with all entries,
*   which needs to be encrypted 
*   
* @retval
*   None                                                               
* 
* @par Side Effects
*   None
* 
*/
void dload_debug_handle_encryption(void)
{
  boot_boolean         is_auth_enabled = FALSE;  
  uint32 dload_flag  = boot_dload_read_saved_cookie() & (SBL_MINIDUMP_MODE_BIT_MASK | SBL_DLOAD_MODE_BIT_MASK);

  if(dload_flag == SBL_MINIDUMP_MODE_BIT_MASK)
  {
    /* Perform encryption for minidump mode ONLY; No encryption when both FD & MD bits are set */
    boot_is_auth_enabled(&is_auth_enabled);
    if(TRUE == is_auth_enabled)
    {
      DBG_MSG("handle_encryption : check oem key");
      dload_debug_check_oem_key(); 
      
      DBG_MSG("handle_encryption : encrypt all regions");
      dload_debug_encr_all_regions();
      
      DBG_MSG("handle_encryption : add unencrypted regions to dump table");
      cil_md_add_unencr_regions();      
    }
    
    DBG_MSG("handle_encryption : add DLOAD buffers to dump table");  
    /* no encryption for non-secure device */
    dload_debug_add_region(MANDATORY, (uint64)SCL_RAMDUMP_DLOAD_BUFFERS_BASE, SCL_RAMDUMP_DLOAD_BUFFERS_SIZE,
      "Debug table addr", "md_dbg_table.BIN"); 
  }   
  
  DBG_MSG("handle_encryption : end");  
}

#else
void dload_debug_handle_encryption(void)
{

}
 
#endif