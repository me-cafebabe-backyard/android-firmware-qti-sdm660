#ifndef BOOT_EXTERN_SEC_IMG_INTERFACE_H
#define BOOT_EXTERN_SEC_IMG_INTERFACE_H
/*===========================================================================

                    BOOT EXTERN SECURE IMAGE AUTH DRIVER DEFINITIONS

DESCRIPTION
  Contains wrapper definition for external image authentication drivers

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
Copyright 2014 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.
    
    
when       who     what, where, why
--------   ---     ----------------------------------------------------------
08/15/15   kpa     Added boot_sec_img_auth_re_enable_debug
09/12/14   plc     Add support for engineering certificates
05/05/14   wg      Initial Creation.

===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/

#include "boot_comdef.h"
#include "sec_img_auth.h"
#include "boot_sbl_shared.h"
#include "boot_sbl_if.h"

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
#ifdef FEATURE_BOOT_EXTERN_SECIMG_AUTH_COMPLETED
  sec_img_auth_error_type boot_sec_img_auth_verify_metadata(uint32 sec_img_id, 
                                 const sec_img_auth_elf_info_type *sec_img_data,
                                 sec_img_auth_whitelist_area_param_t *whitelist_area,
                                 sec_img_auth_verified_info_s *v_info);
#else
  static __inline sec_img_auth_error_type boot_sec_img_auth_verify_metadata(uint32 sec_img_id, 
                                 const sec_img_auth_elf_info_type *sec_img_data,
                                 sec_img_auth_whitelist_area_param_t *whitelist_area,
                                 sec_img_auth_verified_info_s *v_info)
  {
    return SEC_IMG_AUTH_SUCCESS;
  }
#endif

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
#ifdef FEATURE_BOOT_EXTERN_SECIMG_AUTH_COMPLETED
  sec_img_auth_error_type boot_sec_img_auth_hash_elf_segments(uint32 sec_img_id,
                                      sec_img_auth_verified_info_s *v_info);
#else
  static __inline sec_img_auth_error_type boot_sec_img_auth_hash_elf_segments(uint32 sec_img_id,
                                      sec_img_auth_verified_info_s *v_info)
  {
    return SEC_IMG_AUTH_SUCCESS;
  }
#endif 

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
#ifdef FEATURE_BOOT_EXTERN_SECIMG_AUTH_COMPLETED
  sec_img_auth_error_type boot_sec_img_auth_validate_elf(uint32 format, const void *elf_hdr);
#else
  static __inline sec_img_auth_error_type boot_sec_img_auth_validate_elf(uint32 format, const void *elf_hdr)
  {
    return SEC_IMG_AUTH_SUCCESS;
  }
#endif 

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
#ifdef FEATURE_BOOT_EXTERN_SECIMG_AUTH_COMPLETED
  boolean boot_sec_img_auth_is_valid_segment(uint32 format, const void *entry);
#else
  static __inline boolean boot_sec_img_auth_is_valid_segment(uint32 format, const void *entry)
  {
    return TRUE;
  }
#endif

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
#ifdef FEATURE_BOOT_EXTERN_SECIMG_AUTH_COMPLETED
  sec_img_auth_error_type boot_sec_img_auth_is_auth_enabled(uint32 code_seg, 
																										uint32 *is_auth_enabled);
#else
  static __inline sec_img_auth_error_type boot_sec_img_auth_is_auth_enabled(uint32 code_seg, 
																																		uint32 *is_auth_enabled)
  {
    return SEC_IMG_AUTH_SUCCESS;
  }
#endif  

/**
 * @brief send pbl debug information to sec img auth library
 *
 * @param[in] bl_shared_data - pbl shared data
 *
 * @return 0 on success, negative on failure
 */
#ifdef FEATURE_BOOT_EXTERN_SECIMG_AUTH_COMPLETED
  void boot_sec_img_auth_init(bl_shared_data_type * bl_shared_data);
#else
  static __inline void boot_sec_img_auth_init(bl_shared_data_type * bl_shared_data)
  {}
#endif  


/**
 * @brief sec img auth library api to re-enable debug
 *
 * @param[in] secboot_verified_info_type - secboot info
 */
 #ifdef FEATURE_BOOT_EXTERN_SECIMG_AUTH_COMPLETED
  void boot_sec_img_auth_re_enable_debug(secboot_verified_info_type v_info);
#else
  static __inline void boot_sec_img_auth_re_enable_debug(secboot_verified_info_type v_info)
 {}
#endif

#endif /* BOOT_EXTERN_SEC_IMG_INTERFACE_H */
