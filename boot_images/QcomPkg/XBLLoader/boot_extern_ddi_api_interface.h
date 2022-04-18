#ifndef BOOT_EXTERN_DDRDEBUGIMAGE_API_INTERFACE_H
#define BOOT_EXTERN_DDRDEBUGIMAGE_API_INTERFACE_H

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




/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/ 




void boot_ddr_sendDatatoDDI(void * buffer,uint32 size, void* targs , void *training_params_ptr);
void boot_ddr_changeDRAMSettingsforDDI(uint32 clk_in_khz);

/* =============================================================================
**  Function : boot_ddr_retrain_from_ddi
** =============================================================================
*/
/**
*   @brief
*   do DDR PHY training. This fuction is called
*   only when DDI is loaded.
*
*   @param  None
*
*   @retval NONE
*			
*
*   @dependencies
*   
*
*   @sideeffects
*   None
*
*   @sa
*   None
*/

void boot_ddr_retrain_from_ddi();


#endif  /* BOOT_EXTERN_DDRDEBUGIMAGE_INTERFACE_H */
