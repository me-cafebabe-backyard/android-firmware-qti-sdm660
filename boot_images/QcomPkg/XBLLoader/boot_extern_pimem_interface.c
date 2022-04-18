/*===========================================================================

                    BOOT EXTERN PIMEM DRIVER DEFINITIONS

DESCRIPTION
  Contains wrapper definition for external pimem drivers

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
Copyright 2015 by Qualcomm Technologies Incorporated.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.
    
    
when       who     what, where, why
--------   ---     ----------------------------------------------------------
05/18/15   kedara  Added pimem_get_status
02/11/15   kedara  Initial Creation.
=============================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include "boot_extern_pimem_interface.h"


/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/ 


/* ============================================================================
**  Function : boot_pimem_init
** ============================================================================
*/
/*!
*   @brief
*   Initialize pimem for operation
*
*   @details
*
*   @param
*   None
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval  None
*
*   @sa None
*/

void boot_pimem_init(uint64 pimem_mmu_addr, uint64 pimem_mmu_entry)
{
  pimem_init(pimem_mmu_addr, pimem_mmu_entry);
}

/* ============================================================================
**  Function : boot_pimem_debug_init
** ============================================================================
*/
/*!
*   @brief
*   Initialize pimem for debug operation
*
*   @details
*
*   @param
*   None
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval  None
*
*   @sa None
*/

void boot_pimem_debug_init(uint64 pimem_mmu_addr, uint64 pimem_mmu_entry)
{
  pimem_debug_init(pimem_mmu_addr, pimem_mmu_entry);
}
/* ============================================================================
**  Function : boot_pimem_get_status
** ============================================================================
*/
/*!
*   @brief
*   Return current pimem status
*
*   @details
*
*   @param size_in_mb   -   [OUT] pointer to fill with actual pimem vault size
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval  PIMEM_STATUS - return the current status of pimem
*
*   @sa None
*/

PIMEM_STATUS boot_pimem_get_status(uint32 * size_in_mb)
{
  return pimem_get_status(size_in_mb);
}
