/*===========================================================================

                    BOOT EXTERN SECURE IMAGE AUTH DRIVER DEFINITIONS

DESCRIPTION
  Contains wrapper definition for external image authentication drivers

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
Copyright 2014-2016 by Qualcomm Technologies, Incorporated.  
All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.
    
    
when       who     what, where, why
--------   ---     ----------------------------------------------------------
08/17/16   yps     Remove Sec lib
07/21/16   digant  Authentication delta time logging
12/15/15   plc     Enable SMC calls for sec_img_auth when in EL1
11/20/15   kpa     Added boot_sec_img_auth_re_enable_debug.
11/03/15   plc     Add support for calling into XBL-SEC via SCM call if we 
                   are currently executing from Exception Level 1
09/12/14   plc     Add support for engineering certificates
05/05/14   wg      Initial Creation.

===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/

#include "boot_extern_sec_img_interface.h"
#include "boot_fastcall_tz.h"
#include "boot_logger.h"

/*===========================================================================
                           DEFINITIONS
===========================================================================*/


/*===========================================================================
                      FUNCTION DEFINITIONS
===========================================================================*/ 

/**
 * @brief This function authenticates image Metadata
 *      
 *
 * @param[in,out] sec_img_id           	SW Image ID
 *                sec_img_data          Pointer to ELF header         
 *                                     
 * 				  
 * @return SEC_IMG_AUTH_SUCCESS on success. Appropriate error code on failure.
 *
 * @sideeffects  None
 *
 *
 */
sec_img_auth_error_type boot_sec_img_auth_verify_metadata(uint32 sec_img_id, 
							 const sec_img_auth_elf_info_type *sec_img_data,
							 sec_img_auth_whitelist_area_param_t *whitelist_area,
							 sec_img_auth_verified_info_s *v_info)
{
  sec_img_auth_error_type auth_error_type = SEC_IMG_AUTH_FAILURE;
  uint32 start_time = boot_log_get_time();

  boot_tz_indirect_arg_list_t indirect_arg_list;

  indirect_arg_list.arg[0] = (uintnt) whitelist_area->count;
  indirect_arg_list.arg[1] = (uintnt) whitelist_area->area;
  indirect_arg_list.arg[2] = (uintnt) sizeof(*whitelist_area->area) * whitelist_area->count;
  indirect_arg_list.arg[3] = (uintnt) v_info;
  indirect_arg_list.arg[4] = (uintnt) sizeof(*v_info);

  auth_error_type = boot_fastcall_tz_no_rsp (TZ_PIL_SEC_IMG_VERIFY_METADATA_ID,
                                    TZ_PIL_SEC_IMG_VERIFY_METADATA_ID_PARAM_ID,
                                    sec_img_id,
                                    sec_img_data,
                                    sizeof(*sec_img_data),
                                    &indirect_arg_list);
  
  boot_log_delta_time(start_time, "Auth Metadata");
  
  return auth_error_type;
}

/**
 * @brief This function authenticates an ELF images hash segments
 *      
 *
 * @param[in,out] sec_img_id              SW Image ID
 *                v_info                  Pointer to location for verifed info
 *                                   
 *
 * @return SEC_IMG_AUTH_SUCCESS on success. Appropriate error code on failure.
 *
 * @sideeffects  None
 *
 *
 */
sec_img_auth_error_type boot_sec_img_auth_hash_elf_segments(uint32 sec_img_id,
								  sec_img_auth_verified_info_s *v_info)
{
  sec_img_auth_error_type auth_error_type = SEC_IMG_AUTH_FAILURE;
  uint32 start_time = boot_log_get_time();
  
  auth_error_type = boot_fastcall_tz_no_rsp (TZ_PIL_SEC_IMG_HASH_SEGMENTS_ID,
                                    TZ_PIL_SEC_IMG_HASH_SEGMENTS_ID_PARAM_ID,
                                    sec_img_id,
                                    v_info,
                                    sizeof(*v_info),
                                    0);
  boot_log_delta_time(start_time, "Segments hash check");
  
  return auth_error_type;      
}								  
								
								  
/**
 * @brief This function validates the ELF image
 *      
 *
 * @param[in,out] elf_hdr               Pointer to ELF header
 *                                    
 *                        
 *
 * @return SEC_IMG_AUTH_SUCCESS on success. Appropriate error code on failure.
 *
 * @sideeffects  None
 *
 *
 */
sec_img_auth_error_type boot_sec_img_auth_validate_elf(uint32 format, const void *elf_hdr)
{
  uint64 elf_hdr_size = (format == ELF_CLASS_64) ? sizeof(Elf64_Ehdr) : sizeof(Elf32_Ehdr);
    
  return boot_fastcall_tz_no_rsp (TZ_PIL_SEC_IMG_VALIDATE_ELF_ID,
                                    TZ_PIL_SEC_IMG_VALIDATE_ELF_ID_PARAM_ID,
                                    format,
                                    (uint32) elf_hdr,
                                    elf_hdr_size,
                                    0);
}


/**
 * @brief This function checks if the image segment is valid
 *
 *
 * @param[in,out] format              File format
 *                entry               Pointer to hash segment to be checked
 *                     
 *
 * @return \c TRUE if the segment is valid, \c FALSE otherwise.
 *
 * @sideeffects  None
 *
 *
 */
boolean boot_sec_img_auth_is_valid_segment(uint32 format, const void *entry)
{
  boot_tzt_result_regs_t result;
  uint64 prog_hdr_size = (format == ELF_CLASS_64) ? sizeof(Elf64_Phdr) : sizeof(Elf32_Phdr);

  boot_fastcall_tz (TZ_PIL_SEC_IMG_VALID_SEG_ID,
                      TZ_PIL_SEC_IMG_VALID_SEG_ID_PARAM_ID,
                      format,
                      entry,
                      prog_hdr_size,
                      0,
                      &result);

  return result.reg[0];
}


/**
 * @brief This function checks whether authentication is enabled
 *      
 *
 * @param[in,out] code_seg            Type of code segment descriptor
 *                *is_auth_enabled    Pointer to store auth_en flag. 
 *                                                           
 *
 * @return SEC_IMG_AUTH_SUCCESS on success. Appropriate error code on failure.
 *
 * @sideeffects  None
 *
 *
 */
sec_img_auth_error_type boot_sec_img_auth_is_auth_enabled(uint32 code_seg, uint32 *is_auth_enabled)
{
  /* will be something like 
  return boot_fastcall_tz_2arg (TZ_SEC_IMG_AUTH_IS_AUTH_ENABLED_CMD, 
                                            TZ_SEC_IMG_AUTH_IS_AUTH_ENABLED_CMD_PARAM_ID,
                                            code_seg,
					    is_auth_enabled);*/
  return SEC_IMG_AUTH_SUCCESS;				    
}

