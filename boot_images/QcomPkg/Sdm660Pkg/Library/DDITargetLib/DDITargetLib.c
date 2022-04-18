/** @file DDRDebugImageLib.c
  
  DDR DebugImage Functions

  Copyright (c) 2015, Qualcomm Technologies, Inc. All rights reserved.
**/

/*=============================================================================
                              EDIT HISTORY


when       who       what, where, why
--------   ---       -----------------------------------------------------------
24/06/15   sng  Initial revision.

=============================================================================*/

#include "boot_sbl_if.h"
#include "boot_cache_mmu.h"
#include "boot_page_table_armv8.h"
#include "ddi_initialize.h"
#include "../../../Library/DDILib/ddi/ddi_tool.h"


/*!
 * Stub for boot_hand_control_to_DDR_Debug_Image_main()
 *
 * @param bl_shared_data
 *    The shared bootloader information.
 *
*****************************************************************************/
void boot_hand_control_to_DDR_Debug_Image_main (bl_shared_data_type *bl_shared_data)
{
  ddi_entry(bl_shared_data->sbl_shared_data->pbl_shared_data);
}

void boot_ddr_sendDatatoDDI(void * buffer,uint32 size, void* targs, void *training_params_ptr)
{
   displayData(buffer,size,targs, training_params_ptr);
}

void boot_ddr_changeDRAMSettingsforDDI(uint32 clk_in_khz)
{
    changeDRAMSettings(clk_in_khz);
}
