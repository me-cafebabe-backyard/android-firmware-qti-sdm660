/*=============================================================================

               Boot Rollback Version Check

GENERAL DESCRIPTION
  This module provides functionality for version roll back protection

Copyright 2012-2015 by Qualcomm Technologies Inc.  All Rights Reserved.
=============================================================================*/


/*=============================================================================

              EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who   what, where, why
--------   ---   ----------------------------------------------------------
10/05/15   ck    Corrected copyright
04/02/14   ck    Fixed KW issues
12/13/13   ck    Refactored for change in boot_is_auth_enabled parameters
12/09/13   ck    Removed functions for burning fuses as this is done post SBL in Bear family
12/06/13   ck    Fixed spanning bug in boot_rollback_calculate_fuse_version
10/25/12   dh    Initial creation for B family 
 
===========================================================================*/

/*===========================================================================

           INCLUDE FILES FOR MODULE

===========================================================================*/
#include "boot_rollback_version.h"
#include "boot_util.h"
#include "qfprom.h"
#include "IxErrno.h"
#include "boot_authenticator.h"

/*=========================================================================== 
 
                     Local Variables
 
===========================================================================*/
/*Internal pointer that points to the rollback image set table */
static struct boot_version_rollback_img_set *boot_rollback_version_img_set_table_ptr = NULL;
static uint32 boot_rollback_version_img_set_size = 0;

/* Internal boolean indicating if hw auth is enabled */
static boot_boolean is_auth_enabled = TRUE;

  
/*===========================================================================

                LOCAL FUNCTION DEFINITIONS

===========================================================================*/


/*===========================================================================

**  Function : boot_rollback_get_set_by_img_type

** ==========================================================================
*/
/*!
* 
* @brief
*    This function returns a pointer to the rollback image set given an image type
*
* @param[in] img_sw_type secboot image type
*
*
* @par Dependencies
*    None
* 
* @retval
*    boot_version_rollback_img_set*  Returns NULL if not found, returns pointer
*                                    to the image set if found                                    
* 
* 
*/
static struct boot_version_rollback_img_set *boot_rollback_get_set_by_img_type
(
  secboot_sw_type img_sw_type
)
{
  uint32 i,j;
  
  if(boot_rollback_version_img_set_table_ptr != NULL && 
     boot_rollback_version_img_set_size != 0)
  {
    /* Search through all entries of the img set table */
    for(i = 0; i < boot_rollback_version_img_set_size; i++)
    {
      /* Search through all the images each set contains */
      for(j = 0; j < BOOT_VERSION_ROLLBACK_MAX_IMG_NUM_PER_SET; j++ )
      {
        if (boot_rollback_version_img_set_table_ptr[i].sec_sw_img_list[j] == img_sw_type)
        {
          return &boot_rollback_version_img_set_table_ptr[i];
        }
      }
    }
  }
  
  return NULL;
}


/*===========================================================================

**  Function : boot_rollback_is_feature_enabled_on_set

** ==========================================================================
*/
/*!
* 
* @brief
*    This function determins if rollback protection feature is enabled given an image set
*
* @param[in] rollback_img_set pointer to a rollback protection image set
*
*
* @par Dependencies
*    None
* 
* @retval
*    boot_boolean  Returns True if rollback protection feature is enabled,
*                  False otherwise                  
* 
* 
*/
static boot_boolean boot_rollback_is_feature_enabled_on_set
(
  struct boot_version_rollback_img_set *rollback_img_set
)
{  
  boot_boolean rollback_enable = FALSE;
  
  /* Apply the bit mask on the fuse content, if result is nonzero then
     this feature is enabled */
  if( (rollback_img_set->feature_enable_base_addr != NULL) &&
      ((*rollback_img_set->feature_enable_base_addr &
       rollback_img_set->feature_enable_mask) != 0 ))
  {
      rollback_enable = TRUE;
  }
  
  return rollback_enable;
}


/*===========================================================================

**  Function : boot_rollback_calculate_fuse_version

** ==========================================================================
*/
/*!
* 
* @brief
*    This function returns the fuse version value given an image set
*
* @param[in] rollback_img_set pointer to a rollback protection image set
*
*
* @par Dependencies
*    None
* 
* @retval
*    fuse_version  Returns the fuse version value of this image set                 
* 
* 
*/
static uint32 boot_rollback_calculate_fuse_version
(
  struct boot_version_rollback_img_set *rollback_img_set
)
{
  uint32 fuse_version = 0;
  uint32 fuse_msb_val = 0;
  uint32 fuse_intermediate_val = 0;
  uint32 fuse_lsb_val = 0;

  uint32 * current_field = NULL;
  uint32 intermediate_bits = 0;

  
  if(rollback_img_set->version_lsb_base_addr != NULL)
  {
    /*Get the raw value of LSB fuse by applying the bit mask */
    fuse_lsb_val = *(rollback_img_set->version_lsb_base_addr) &
                   rollback_img_set->version_lsb_mask;
  }

  
  if(rollback_img_set->version_msb_base_addr != NULL)
  {
    /* There is a possibility with bitmasks 34 bits or larger that
       the fuses can span 3 uint32's.  We must account for this by
       looking at the address span between the lsb base address and
       msb base address.  If span is greater than 4 bytes there is an
       entire 32 bit field or more that must be evaluated. */
    if ((rollback_img_set->version_msb_base_addr -
         rollback_img_set->version_lsb_base_addr) > sizeof(uint32))
    {
      for (current_field = (uint32 *)(rollback_img_set->version_lsb_base_addr + 
                                      sizeof(uint32));
           current_field < rollback_img_set->version_msb_base_addr;
           current_field++)
      {
        BL_VERIFY(current_field,
                  BL_ERR_NULL_PTR_PASSED|BL_ERROR_GROUP_BOOT);

        intermediate_bits = *current_field;
        fuse_intermediate_val += boot_count_set_bits(intermediate_bits); 
      }
    }


    /*Get the raw value of MSB fuse by applying the bit mask */
    fuse_msb_val = *(rollback_img_set->version_msb_base_addr) &
                   rollback_img_set->version_msb_mask;
  }
  

  /* Count the bits that are set in each fuse and add them up,
     that will be the version number of current set */
  fuse_version = boot_count_set_bits(fuse_lsb_val) +
                 fuse_intermediate_val +
                 boot_count_set_bits(fuse_msb_val);

  
  return fuse_version;
}


/*===========================================================================

                PUBLIC FUNCTION DEFINITIONS

===========================================================================*/
/*===========================================================================

**  Function : boot_rollback_init_img_set_table

** ==========================================================================
*/
/*!
* 
* @brief
*    This function initializes the rollback version image set table.
*
* @param[in] img_set_table pointer to the table
*
* @param[in] img_set_num number of images sets the table contains
*
*
* @par Dependencies
*    None
* 
* @retval None                                 
* 
* 
*/
void boot_rollback_init_img_set_table
(
  bl_shared_data_type *bl_shared_data,
  struct boot_version_rollback_img_set *img_set_table,
  uint32 img_set_num
)
{
  boot_rollback_version_img_set_table_ptr = img_set_table;
  boot_rollback_version_img_set_size = img_set_num;
  
  /* Determin if hw auth is enabled or not */  
  boot_is_auth_enabled(&is_auth_enabled);
}


/*===========================================================================

**  Function : boot_rollback_get_fuse_version

** ==========================================================================
*/
/*!
* 
* @brief
*    This function returns the image version that's stored on the fuse given a
*    image type
*
* @param[in] img_sw_type secure image type
*
* @param[out] fuse_version pointer to the image version to be populated
*
*
* @par Dependencies
*    None
* 
*    bl_error_boot_type Returns error code in case of error
*                  Returns BL_ERR_NONE in case of no error                              
* 
* 
*/
bl_error_boot_type boot_rollback_get_fuse_version
(
  secboot_sw_type img_sw_type,
  uint32 *fuse_version
)
{
  bl_error_boot_type status = BL_ERR_NONE;
  
  /* First get the set the target image belongs to */
  struct boot_version_rollback_img_set *rollback_img_set = 
                boot_rollback_get_set_by_img_type(img_sw_type);
                      
  if (rollback_img_set != NULL)
  {
    /* First check if rollback feature fuse and auth are both enabled */
    if(is_auth_enabled == TRUE &&
       boot_rollback_is_feature_enabled_on_set(rollback_img_set))
    {
      *fuse_version = boot_rollback_calculate_fuse_version(rollback_img_set);
    }
    else
    {
      /* If rollback feature fuse is not enabled on this set then default to 0*/
      *fuse_version = 0;
    }
  }
  else
  {
    /* Error if can't find this image */
    status = BL_ERR_CODE_ROLLBACK_VERSION_VERIFY_FAIL;
  }
  
  return status;
}


/*===========================================================================

**  Function : boot_rollback_update_img_version

** ==========================================================================
*/
/*!
* 
* @brief
*    This function updates the current image version obtained from cert 
*    in the image set table given an image type
*
* @param[in] img_sw_type secure image type
*
* @param[out] img_version  the latest image versio obtained from cert
*
*
* @par Dependencies
*    None
* 
*    bl_error_boot_type Returns error code in case of error
*                  Returns BL_ERR_NONE in case of no error                              
* 
* 
*/
bl_error_boot_type boot_rollback_update_img_version
(
  secboot_sw_type img_sw_type,
  uint32 img_version
)
{
  bl_error_boot_type status = BL_ERR_NONE;
  
  /* First get the set the target image belongs to */
  struct boot_version_rollback_img_set *rollback_img_set = 
                boot_rollback_get_set_by_img_type(img_sw_type);

  if (rollback_img_set != NULL)
  {
    /* First check if rollback feature fuse is enabled */
    /* First check if rollback feature fuse and auth are both enabled */
    if(is_auth_enabled == TRUE &&
       boot_rollback_is_feature_enabled_on_set(rollback_img_set))
    {
      /* Only update if current image version is greater than set version */
      if(img_version > rollback_img_set->current_set_version_num)
      {
        rollback_img_set->current_set_version_num = img_version;
      }
    }
  }
  else
  {
    /* Error if can't find this image */
    status = BL_ERR_CODE_ROLLBACK_VERSION_VERIFY_FAIL;
  }
  
  return status;
}
