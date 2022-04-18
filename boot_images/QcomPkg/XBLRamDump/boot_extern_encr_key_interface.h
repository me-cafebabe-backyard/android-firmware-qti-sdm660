#ifndef BOOT_EXTERN_ENCR_KEY_INTERFACE_H
#define BOOT_EXTERN_ENCR_KEY_INTERFACE_H

/*===========================================================================

                    BOOT EXTERN EFS DRIVER DEFINITIONS

DESCRIPTION
  Contains wrapper definition for external encryption code

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
*   This api Must be called after the debug table is populated with all entries,
*   which needs to be encrypted 
*   
* @retval
*   None                                                               
* 
* @par Side Effects
*   None
* 
*/
void dload_debug_handle_encryption(void);

#endif  /* BOOT_EXTERN_ENCR_KEY_INTERFACE_H */