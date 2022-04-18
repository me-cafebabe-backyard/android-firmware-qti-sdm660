/*===========================================================================

  page_select.c - handle setting page select register for LPAE targets

  Copyright (c) 2013 Qualcomm Technologies, Inc.  
  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ===========================================================================*/

#include "page_select.h"
#include "comdef.h"
#include <stdlib.h>
#include "CoreVerify.h"
#include "msmhwio.h"
#include "rpm_dec_hwio.h"

uint32_t set_ddr_access(uint64_t address)
{
    /* Handle DDR paged memory addressing */
    // bits 31-34 are used to set the page select bits
    HWIO_RPM_PAGE_SELECT_OUT((uint32)((address)>>30));
    
    // truncate address down to 32 bits, 
    // truncate to 1GB address range
    // offset to 0 at 0x60000000 - DDR is mapped starting at 0x60000000 on LPAE targets
    return ((((uint32)address)&0x3FFFFFFF)+0x60000000);
    //return (void*)(((uint32)smem_imem_entry->smem_base_phys_addr)+0x60000000);
}

void set_page_select(uint8_t page_select_val)
{
    CORE_VERIFY(page_select_val < 64);

    // directly set the page select value
    HWIO_RPM_PAGE_SELECT_OUT(page_select_val);
}

