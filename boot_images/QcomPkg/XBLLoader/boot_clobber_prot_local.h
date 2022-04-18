#ifndef BOOT_CLOBBER_PROTECTION_LOCAL_H
#define BOOT_CLOBBER_PROTECTION_LOCAL_H

/*=============================================================================

                    Boot Loader Clobber Protection

GENERAL DESCRIPTION
  This function contains the implementation for the boot-specific clobber
  protection module, to facilitate preventing the bootloader address spaces
  from being overwritten by a flash load.

Copyright 2007, 2010, 2014, 2016 by QUALCOMM Technologies Inc.  All Rights Reserved.
=============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ----------------------------------------------------------
03/17/16   bd      Add clobber hole removal API
08/05/14   ck      Modified logic to support 64/32 bit architectures
08/04/10   aus     Clean-up for secboot 3
02/06/07   MJS     Initial revision.

============================================================================*/

/*===========================================================================
 
                           INCLUDE FILES

===========================================================================*/
#include "boot_comdef.h"
#include "boot_clobber_prot.h"
#include "boot_msm.h"


/*===========================================================================

                      PUBLIC DATA DECLARATIONS
                      
===========================================================================*/

/* This defines the maximum number of local holes in a local protection array */
#ifndef BOOT_CLOBBER_MAX_LOCAL_REGION_HOLES
#define BOOT_CLOBBER_MAX_LOCAL_REGION_HOLES 4
#endif /* BOOT_CLOBBER_MAX_LOCAL_REGION_HOLES */

/* Local clobber protection data structure defines array of protection holes */
typedef struct boot_clobber_local_type
{
  uint32 num_holes;  /* Number of holes present in the array */

  struct
  {
    const uint8 *start_addr;  /* Start address of a hole */
    uintnt size;              /* Size of a hole */
  } region_hole[BOOT_CLOBBER_MAX_LOCAL_REGION_HOLES];
  
} boot_clobber_local_type;

/*===========================================================================

                      PUBLIC FUNCTION DECLARATIONS

===========================================================================*/

/*=========================================================================

**  Function :  boot_clobber_local_init

** ==========================================================================
*/
/*!
* 
* @brief
*   Function to initialize a local clobber protection data structure.
* 
* @param[in] clobber_tbl_ptr Pointer to the local table
*
* @par Dependencies
*   None
*   
* @retval
*   None
* 
* @par Side Effects
*   None
* 
*/
void boot_clobber_local_init
(
  boot_clobber_local_type *clobber_tbl_ptr  /* Pointer to the local table */
);

/*=========================================================================

**  Function :  boot_clobber_add_local_hole

** ==========================================================================
*/
/*!
* 
* @brief
*   Function to add a local hole to the bootloader overwrite protection regions.
* 
* @param[in] clobber_tbl_ptr Pointer to the local table
* @param[in] start_addr Start address of the local hole to add
* @param[in] size Size of the local hole to add in bytes
*
* @par Dependencies
*   None
*   
* @retval
*   TRUE if there was space left in the local array, FALSE otherwise
* 
* @par Side Effects
*   None
* 
*/
boolean boot_clobber_add_local_hole
(
  boot_clobber_local_type *clobber_tbl_ptr,  /* Pointer to the local table */
  const void *start_addr,  /* Start address of the local hole to add */
  uintnt size              /* Size of the local hole to add in bytes */
);

/*=========================================================================

**  Function :  boot_clobber_remove_local_hole

** ==========================================================================
*/
/*!
* 
* @brief
*   Function to remove a previously added local hole.
* 
* @param[in] clobber_tbl_ptr Pointer to the local table
* @param[in] start_addr Start address of the local hole to remove
* @param[in] size Size of the local hole to remove in bytes
*
* @par Dependencies
*   None
*   
* @retval
*   None
* 
* @par Side Effects
*   None
* 
*/
void boot_clobber_remove_local_hole
(
  boot_clobber_local_type *clobber_tbl_ptr,  /* Pointer to the local table */
  const void *start_addr,  /* Start address of the local hole to remove */
  uintnt size              /* Size of the local hole to remove in bytes */
);

/*=========================================================================

**  Function :  boot_clobber_check_local_address_range

** ==========================================================================
*/
/*!
*
* @brief
*   Function to check that the given address range either fits inside one of
*   the local holes defined in the protected address regions, or that the
*   given address range does not overlap any of the protected address regions.
* 
* @param[in] clobber_tbl_ptr Pointer to the local table
* @param[in] start_addr Start address of the region to check
* @param[in] size Size of the region to check in bytes
*
* @par Dependencies
*   None
*   
* @retval
*   TRUE if the given address range completely falls within a local hole or
*   if the given address range does not overlap with a protected region,
*   FALSE otherwise
* 
* @par Side Effects
*   None
* 
*/
boolean boot_clobber_check_local_address_range
(
  boot_clobber_local_type *clobber_tbl_ptr,  /* Pointer to the local table */
  const void *start_addr,  /* Start address of the region to check */
  uintnt size              /* Size of the region to check in bytes */
);

#endif /* BOOT_CLOBBER_PROTECTION_LOCAL_H */

