/*===========================================================================

  Copyright (c) 2013 Qualcomm Technologies, Inc.
  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ===========================================================================*/

#ifndef PAGE_SELECT_H
#define PAGE_SELECT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "comdef.h"

/**
 * This function updates the page select bits and returns the RPM address 
 * needed to access the specified DDR address
 *
 * Note: For targets without LPAE, the address passed will simply be truncated
 *          to 32 bits and reutned.
 *
 * Arguments:
 * uint64_t address - 64 bit DDR address
 *
 * Return:
 * uint32_t - the local RPM address cooresponding to the address requested.
 */
uint32_t set_ddr_access(uint64_t address);

/**
 * This function updates the page select bits to the specified value
 *
 * Arguments:
 * uint8_t address - destired page select value
 *  
 * Return:
 */

void set_page_select(uint8_t page_select_val);

#ifdef __cplusplus
}
#endif

#endif // GPIO_DEBUG_H

