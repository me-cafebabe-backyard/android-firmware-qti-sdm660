#ifndef BOOT_EXTERN_DDRDEBUGIMAGE_INTERFACE_H
#define BOOT_EXTERN_DDRDEBUGIMAGE_INTERFACE_H

/*===========================================================================

                    BOOT EXTERN DDEDEBUGIMAGE DRIVER DEFINITIONS

DESCRIPTION
  Contains wrapper definition for DDEDEBUGIMAGE main function

INITIALIZATION AND SEQUENCING REQUIREMENTS
  DDR must be initialized
  
Copyright (C) 2015 by Qualcomm Technologies, Inc. All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.
    
    
when       who     what, where, why
--------   ---     ----------------------------------------------------------

06/24/15   sng      Initial Creation.

===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/

#include "boot_sbl_if.h"

/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/ 

/*===========================================================================

**  Function :  boot_hand_control_to_DDR_Debug_Image_main

** ==========================================================================
*/
/*!
 * Run DDI after ddr has been initialized.
 *
 * @param bl_shared_data
 *    The shared bootloader information.
 *
 * @return
 *   
 *
*****************************************************************************/

  void boot_hand_control_to_DDR_Debug_Image_main(bl_shared_data_type *bl_shared_data);


 
 


#endif  /* BOOT_EXTERN_DDRDEBUGIMAGE_INTERFACE_H */
