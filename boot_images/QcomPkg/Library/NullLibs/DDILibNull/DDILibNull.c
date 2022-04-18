/** @file DDRDebugImageLibNull.c
  
  DDR DebugImage Functions

  Copyright (c) 2015, Qualcomm Technologies, Inc. All rights reserved.
**/

/*=============================================================================
                              EDIT HISTORY


when       who       what, where, why
--------   ---       -----------------------------------------------------------
24/24/15   sng  Initial revision.

=============================================================================*/

#include "boot_sbl_if.h"

/*!
 * Stub for boot_hand_control_to_DDR_Debug_Image_main()
 *
 * @param bl_shared_data
 *    The shared bootloader information.
 *
*****************************************************************************/
void boot_ddr_sendDatatoDDI(void * buffer,uint32 size, void* targs, void *training_params_ptr)
{
        
  
}

void boot_ddr_changeDRAMSettingsforDDI(uint32 clk_in_khz)
{
    
}
